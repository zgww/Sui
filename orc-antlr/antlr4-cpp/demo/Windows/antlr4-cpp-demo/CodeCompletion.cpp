#include "CodeCompletion.h"
#include "./ReturnStringVisitor.h"
#include <SymbolBuilderVisitor.h>
#include "LspActor.h"

// ����ָ��λ�õ� ast �ڵ�ջ
	bool ContainPositionNodeStackVisitor::containsPosition(OrcRuleContext *ctx) {
		auto start = ctx->getStart();
		auto stop = ctx->getStop();
		if (start && stop) {
			int startLine = start->getLine() - 1; // antlr line��1��ʼ
			int endLine = stop->getLine() - 1;
			int startC = start->getCharPositionInLine();
			int endC = stop->getCharPositionInLine() + stop->getText().size();


			if (
				(
					startLine < position.line
					||
					(startLine == position.line && startC <= position.character)
					)
				&&
				(
					position.line < endLine
					||
					(endLine == position.line && position.character <= endC)
					)
				) {
				return true;
			}
		}
		return false;
	}

	std::any ContainPositionNodeStackVisitor::visitChildren(tree::ParseTree* node) {
		auto ctx = dynamic_cast<OrcRuleContext*>(node);
		if (ctx) {
			//λ�ð���
			if (containsPosition(ctx)) {
				nodeStack.push_back(ctx);
				return OrcBaseVisitor::visitChildren(ctx);
			}
			return defaultResult();
		}
		return OrcBaseVisitor::visitChildren(node);
	}

void test_ContainPositionNodeStackVisitor() {
	std::string code = R"(package SuiCore
void main(){
	User@ user = new User();
	int age =34;
	say(user.
	int level = 234;
	User@ user2 = new User();
}
)";
	AstBuilder b;
	b.initByCode(code);
	auto tree = b.parser->program();
	ContainPositionNodeStackVisitor vi;
	vi.position = Position{ .line = 4, .character = 10};
	vi.visit(tree);
	printf("vi. nodeStack.size:%d\n", vi.nodeStack.size());
}
void AstBuilder::initByCode(std::string code)
{
	this->code = code;
	input = std::make_shared<ANTLRInputStream>(code);
	lexer = std::make_shared<OrcLexer>(input.get());
	tokens = std::make_shared<CommonTokenStream>(lexer.get());
	parser = std::make_shared<OrcParser>(tokens.get());
}

int Position_toCharIndex(std::string code, Position pos) {
	for (int i = 0, l = code.size(); i < l; i++) {
		auto c = code[i];
		if (pos.line > 0) { //�ȵ���
			if (c == '\n') {
				pos.line--;
			}
		}
		else {
			if (pos.character == 0) {
				return i;
			}
			pos.character--;
		}
	}
	return code.size();
}

void test_codeCompleteAtPosition_forDot()
{
	{
		std::string code = R"(package SuiCore
void main(){
	User@ user = new User();
	int age =34;
	say(user.
	int level = 234;
	User@ user2 = new User();
}
)";
		CodeCompletion cc;
		cc.initByCode(code);
		AstBuilder ast;
		ast.initByCode(code);
		auto p = ast.parser->program();
		ast_printTree(p, ast.parser.get());
	}

	std::string code = R"(package SuiCore
class User {
	int age;
	User* hi(){
		return self
	}
	void say(){
		self.hi().
	}
}
)";
	CodeCompletion cc;
	cc.initByCode(code);
	AstBuilder b;
	Position pos = {
		.line = 7, .character = 12
	};
	auto se = cc.codeCompleteAtPosition_forDot(pos, b);
	printf("tmp:[%p] [%s]\n", se, se->getText().c_str());


	AstBuilder fullAst;
	fullAst.initByCode(code);
	auto program = fullAst.parser->program();
	ContainPositionNodeStackVisitor vi;
	vi.position = pos;
	vi.visit(program);

	printf("vi. nodeStack.size:%d\n", vi.nodeStack.size());
	if (se && vi.nodeStack.size() > 0) {
		std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
		SymbolBuilderVisitor symBuilder;
		symBuilder.space->symbolSpaceLoader = symbolSpaceLoader;

		symBuilder.init("a.orc");
		symBuilder.visit(program);

		AstMake mk;
		tree::ParseTreeTracker _tracker;
		mk.tracker = &_tracker;

		//����������self����
		AddSelfArgumentVisitor addSelfArgumentVisitor;
		addSelfArgumentVisitor.mk = &mk;
		addSelfArgumentVisitor.visit(program);
		//cost.stat("addSelfArgumentVisitor");

		//se�ҵ������ctx��
		se->parent = vi.nodeStack.back();
		auto symType = ast_calcSymbolTypeOfExpressionResult(se, symBuilder.space);
		auto typePointer = std::dynamic_pointer_cast<SymbolTypePointer>(symType->type);
		printf("symType:%p\n", symType.get());
		if (typePointer) {
			auto def  = symBuilder.space->findSymbolDefinitionByName_includeImports(typePointer->getNakeTypeName());
			{
				auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(def);
				if (classDef) {
					for (auto mem : classDef->members) {
						printf("code complete:%s  full=%s\n", mem->name.c_str(), mem->fullname.c_str());
					}
				}
			}
		}
	}
}

void test_Position_toCharIndex() {
	std::string code = R"(package SuiCore
void main(){
	self.user.
}
)";
	int idx = Position_toCharIndex(code, Position{.line = 2, .character = 11});
	auto tmp = code.substr(idx - 10, 10);
	printf("tmp:[%s]\n", tmp.c_str());
}

//idxǰ�ƣ�ȥ��'.'��' '
int CodeCompletion_moveBack_skipSpaceAndDot(std::string code, int idx) {
	while (idx > 0) {
		char c = code[idx-1];
		if (c == ' ' || c == '.') {
			idx--;
		}
		else {
			break;
		}
	}
	return idx;
}

void CodeCompletion::initByCode(std::string code)
{
	this->code = code;
}

//������ʾ
/*
ԭ����

��λ����ǰ,���ַ�����ƥ��SingleExpression,
���û�д��󣬾ͼ�����ǰ��
����������
1. һֱ��ƥ����singleExpression,���Ǹ�SingleExpression����position��token,
Ȼ�󷵻�֮ǰƥ���SingleExpression,
2. ���ı���ͷ�ˣ�����֮ǰƥ���SingleExpression

���ԣ�������Ҫ��ƥ��ɹ�SingleExpression.
�Ƕ��� 'self.a.' �����ı���  Ҫ������position��Token,Ӧ����'a',����Ҫ��ǰ��ch,����ȥ������'.'
*/
OrcParser::SingleExpressionContext*  CodeCompletion::codeCompleteAtPosition_forDot(Position pos, AstBuilder &b) {
	if (0) {
		b.initByCode("self");
		auto tree = b.parser->singleExpression();
		return tree;
	}

	auto lines = StrUtil::split_by_re(this->code, "\r");
	//ȡ�����λ�õ��ַ�����
	auto idx0 = Position_toCharIndex(this->code, pos);
	//��� obj.say| �� obj.| ���Σ��򵥵ĵ���Ŀ��λ�ã�ʹ��ƥ����յ����ڵ�֮ǰ��
	//��֤ se ���ǡ���˱���ʽ�������ǰ������ʵĳ�Ա��ǰ׺��
	int idx;
	int dotIdx = idx0;
	bool hasDot = false;
	while (dotIdx > 0) {
		char c = this->code[dotIdx - 1];
		if (c == ' ') { dotIdx--; continue; }
		if (isalnum((unsigned char)c) || c == '_') { dotIdx--; continue; }
		if (c == '.') { dotIdx--; hasDot = true; break; }
		break;
	}
	if (hasDot) {
		idx = dotIdx;
	}
	else {
		idx = CodeCompletion_moveBack_skipSpaceAndDot(this->code, idx0);
	}
	//ƥ��SingleExpression
	int start = idx - 1;
	OrcParser::SingleExpressionContext* se = NULL;
	std::string seCode;
	while (start >= 0) {
		auto tmpcode = this->code.substr(start, idx - start);
		b.initByCode(tmpcode);
		b.parser->removeErrorListeners();
		b.parser->removeParseListeners();
		auto tree = b.parser->singleExpression();
		//�д�
		if (b.parser->getNumberOfSyntaxErrors() > 0) {
			start--;
			continue;
		}
		if (tree == NULL) {
			start--;
			continue;
		}
		auto seText = tree->getText();
		log(std::format("tmpcode:{}||| seText:{}\n", tmpcode.c_str(), seText.c_str()));
		//�ɹ�
		//�ж�tree�Ƿ������idx
		auto stop = tree->getStop();
		//����
		if (stop && stop->getStopIndex() >= tmpcode.size() - 1) {
			start--;
			seCode = tmpcode;
			se = tree;
		}
		else {
			//����ʶ��� expression û���ǵ� tmpcode ĩβ��˵���������ʽ�벹ȫ���Ӳ���
			//���֮ǰ�Ѿ�����һ���ǵ�ĩβ�ı���ʽ���򷵻���֮��ǰ����Ѱ��
			if (seCode != "") {
				b.initByCode(seCode);
				auto tree = b.parser->singleExpression();
				return tree;
			}
			start--;
			continue;
		}
	}
	return NULL;
}
