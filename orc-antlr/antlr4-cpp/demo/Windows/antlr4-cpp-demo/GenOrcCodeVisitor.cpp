#include "GenOrcCodeVisitor.h"
#include "Symbol.h"

//virtual std::any visitProgram(OrcParser::ProgramContext* ctx) override {
//	
//}

std::any GenOrcCodeVisitor::visitClosureType(OrcParser::ClosureTypeContext* ctx) {
	auto type = visitReturnString(ctx->type());
	auto args = visitReturnString(ctx->argumentsDeclaration());
	auto ret = std::format("^{}{}", type, args);
	return ret;
}

std::any GenOrcCodeVisitor::visitClosureExpression(OrcParser::ClosureExpressionContext* ctx) {
	auto args = visitReturnString(ctx->argumentsDeclaration());
	auto type = visitReturnString(ctx->type());
	auto block = visitReturnString(ctx->block());
	return std::format("^{} {}{}{}", type, ctx->Id() ? ctx->Id()->getText() : std::string(""), args, block);
}

std::any GenOrcCodeVisitor::visitArguments(OrcParser::ArgumentsContext* ctx) {
	string ret = "(";
	auto args = ctx->singleExpression();
	for (int i = 0, l = args.size(); i < l; i++) {
		auto code = visitReturnString(args[i]);
		ret += code;
		if (i < l - 1) {
			ret += ", ";
		}
	}
	return ret + ") ";
	//return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitExpressionSequence(OrcParser::ExpressionSequenceContext* ctx) {
	return visitChildrenReturnString(ctx);
}


std::any GenOrcCodeVisitor::visitTernaryExpression(OrcParser::TernaryExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));
	auto s2 = visitReturnString(ctx->singleExpression(2));
	return std::format("{} ? {} : {}", s0, s1, s2);
}

std::any GenOrcCodeVisitor::visitLogicalAndExpression(OrcParser::LogicalAndExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));

	return std::format("{} && {}", s0, s1);
}

std::any GenOrcCodeVisitor::visitMemberDotExpression(OrcParser::MemberDotExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());
	string dot = ".";
	auto propName = ctx->Id()->getText();
	return std::format("{}{}{}", s0, dot, propName);
}

std::any GenOrcCodeVisitor::visitMemberIndexExpression(OrcParser::MemberIndexExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));

	return std::format("{}[{}]", s0, s1);
}

std::any GenOrcCodeVisitor::visitPreIncrementExpression(OrcParser::PreIncrementExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("++{}", s0);
}

std::any GenOrcCodeVisitor::visitLogicalOrExpression(OrcParser::LogicalOrExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));

	return std::format("{} || {}", s0, s1);
}

std::any GenOrcCodeVisitor::visitNotExpression(OrcParser::NotExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("!{}", s0);
}

std::any GenOrcCodeVisitor::visitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("--{}", s0);
}

std::any GenOrcCodeVisitor::visitThisExpression(OrcParser::ThisExpressionContext* ctx) {
	return ctx->getText();
}

std::any GenOrcCodeVisitor::visitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("-{}", s0);
}

std::any GenOrcCodeVisitor::visitAssignmentExpression(OrcParser::AssignmentExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));

	return std::format("{} = {}", s0, s1);
}

std::any GenOrcCodeVisitor::visitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("{}--", s0);
}

std::any GenOrcCodeVisitor::visitInstanceofExpression(OrcParser::InstanceofExpressionContext* ctx) {
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("+{}", s0);
}

std::any GenOrcCodeVisitor::visitEqualityExpression(OrcParser::EqualityExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));
	auto op = ctx->children[1]->getText();

	return std::format("{} {} {}", s0, op, s1);
}

std::any GenOrcCodeVisitor::visitBitXOrExpression(OrcParser::BitXOrExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));

	return std::format("{} ^ {}", s0, s1);
}

std::any GenOrcCodeVisitor::visitSuperExpression(OrcParser::SuperExpressionContext* ctx) {
	return string("super");
}

std::any GenOrcCodeVisitor::visitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));
	auto op = ctx->children[1]->getText();

	return std::format("{} {} {}", s0, op, s1);
}

/*
- 调用父类方法 super.fn() = > super_fn_fullname(self)    ~~转为全局函数
- 调用扩展方法 a.b() = > fullname_b(a)        ~~转为全局函数
*/

std::any GenOrcCodeVisitor::visitCallExpression(OrcParser::CallExpressionContext* ctx) {
	auto fn = visitReturnString(ctx->singleExpression());
	auto args = visitReturnString(ctx->arguments());
	return fn + args;
}

std::any GenOrcCodeVisitor::visitBitShiftExpression(OrcParser::BitShiftExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));
	auto op = ctx->children[1]->getText();

	return std::format("{} {} {}", s0, op, s1); // >> << >>>
}

//不支持逗号语句

std::any GenOrcCodeVisitor::visitParenthesizedExpression(OrcParser::ParenthesizedExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->expressionSequence()->singleExpression(0));

	return std::format("({})", s0); // >> << >>>
}

std::any GenOrcCodeVisitor::visitAdditiveExpression(OrcParser::AdditiveExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));
	auto op = ctx->children[1]->getText();

	return std::format("{} {} {}", s0, op, s1); // + -
}

std::any GenOrcCodeVisitor::visitRelationalExpression(OrcParser::RelationalExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));
	auto op = ctx->children[1]->getText();

	return std::format("{} {} {}", s0, op, s1); // < > >= <= 
}

std::any GenOrcCodeVisitor::visitPostIncrementExpression(OrcParser::PostIncrementExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("{}++", s0);
}

std::any GenOrcCodeVisitor::visitBitNotExpression(OrcParser::BitNotExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("~{}", s0);
}

std::any GenOrcCodeVisitor::visitNewExpression(OrcParser::NewExpressionContext* ctx) {
	auto className = ctx->Id()->getText();
	auto args = visitReturnString(ctx->arguments());

	return std::format("new {}{}", className, args);
}

std::any GenOrcCodeVisitor::visitLiteralExpression(OrcParser::LiteralExpressionContext* ctx) {
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitDerefExpression(OrcParser::DerefExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("*{}", s0);
}

std::any GenOrcCodeVisitor::visitGetAddressExpression(OrcParser::GetAddressExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());

	return std::format("&{}", s0);
}

std::any GenOrcCodeVisitor::visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx) {
	auto varName = ctx->getText();
	return varName;
}

std::any GenOrcCodeVisitor::visitBitAndExpression(OrcParser::BitAndExpressionContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression(0));
	auto s1 = visitReturnString(ctx->singleExpression(1));

	return std::format("{} & {}", s0, s1); // 
}

std::any GenOrcCodeVisitor::visitBitOrExpression(OrcParser::BitOrExpressionContext* ctx) {
	auto left = visitReturnString(ctx->singleExpression(0));
	auto right = visitReturnString(ctx->singleExpression(1));
	return left + " | " + right;
}

std::any GenOrcCodeVisitor::visitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext* ctx) {
	auto left = visitReturnString(ctx->singleExpression(0));
	auto right = visitReturnString(ctx->singleExpression(1));

	return left + " " + ctx->assignmentOperator()->getText() + " " + right;
}

std::any GenOrcCodeVisitor::visitCastExpression(OrcParser::CastExpressionContext* ctx) {
	auto type = visitReturnString(ctx->type());
	auto expr = visitReturnString(ctx->singleExpression());
	return std::format("({}){}", type, expr);
	//return visitChildrenReturnString(ctx);
}

// ?? 表达式，暂不支持

std::any GenOrcCodeVisitor::visitCoalesceExpression(OrcParser::CoalesceExpressionContext* ctx) {
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitLabelClosureExpression(OrcParser::LabelClosureExpressionContext* ctx) {
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitAssignmentOperator(OrcParser::AssignmentOperatorContext* ctx) {
	return ctx->getText();
}

std::any GenOrcCodeVisitor::visitEmptyStatement(OrcParser::EmptyStatementContext* ctx) {
	return string("");
}

std::any GenOrcCodeVisitor::visitStructDefinition(OrcParser::StructDefinitionContext* ctx) {
	if (ctx->isStaticStruct) { //静态结构体，只在.c实现文件中产生，不在头文件中产生
	}


	auto name = ctx->Id()->getText();
	std::string members = "";
	for (auto& mem : ctx->structMember()) {
		members += "\t" + visitReturnString(mem) + "\n";
	}

	return std::format(R"({}struct {} {{
{}
}}
)", ctx->isStaticStruct ? "static " : "", name, members);
}

std::any GenOrcCodeVisitor::visitStructMember(OrcParser::StructMemberContext* ctx) {
	if (ctx->functionPointerVarDeclaration()) {
		auto ret = visitReturnString(ctx->functionPointerVarDeclaration());
		return ret;
	}
	if (ctx->type()) {
		auto varName = ctx->Id()->getText();
		auto t = visitReturnString(ctx->type());
		return std::format("{} {}", t, varName);
	}



	return std::string("(invalid var declaration)");
}

std::any GenOrcCodeVisitor::visitVarDeclaration(OrcParser::VarDeclarationContext* ctx) {
	std::string staticStr = ctx->Static()?"static ":"";
	if (ctx->functionPointerVarDeclaration()) {
		auto ret = visitReturnString(ctx->functionPointerVarDeclaration());
		return staticStr + ret;
	}
	if (ctx->type()) {
		auto t = visitReturnString(ctx->type());
		auto init = ctx->singleExpression();
		auto varName = ctx->Id()->getText();
		if (init) {
			auto initCode = visitReturnString(init);
			return std::format("{}{} {} = {}", staticStr, t, varName, initCode);
		}
		return std::format("{}{} {}", staticStr, t, varName);
	}
	return std::string("(invalid var declaration)");
}

std::any GenOrcCodeVisitor::visitStatement(OrcParser::StatementContext* ctx) {
	auto ret = visitChildrenReturnString(ctx);
	if (ctx->singleExpression() || ctx->varDeclaration()) {
		return ret + ";\n";
	}
	return ret;
}

std::any GenOrcCodeVisitor::visitContinueStatement(OrcParser::ContinueStatementContext* ctx) {
	return string("continue;\n");
}

std::any GenOrcCodeVisitor::visitBreakStatement(OrcParser::BreakStatementContext* ctx) {
	return string("break;\n");
}

std::any GenOrcCodeVisitor::visitReturnStatement(OrcParser::ReturnStatementContext* ctx) {
	auto expr = visitReturnString(ctx->singleExpression());
	return string("return ") + expr + "; \n";
}

std::any GenOrcCodeVisitor::visitScopeStatement(OrcParser::ScopeStatementContext* ctx) {
	auto expr = visitReturnString(ctx->singleExpression());
	auto block = visitReturnString(ctx->block());

	auto scopeCode = std::format(R"({}.{})"
		, expr
		, block
	);
	return scopeCode;
}

std::any GenOrcCodeVisitor::visitIterationStatement(OrcParser::IterationStatementContext* ctx) {
	if (ctx->While()) {
		auto exprText = visitReturnString(ctx->singleExpression());
		if (exprText.c_str()[0] != '(') {
			exprText = std::format("({})", exprText);
		}
		auto blockText = visitReturnString(ctx->block());
		auto ret = std::format("while {} {}", exprText, blockText);
		return ret;
	}
	if (ctx->For()) {
		//auto hasParenthesis = ctx->children[1]->getText() == "(";
		auto forConditionText = visitReturnString(ctx->forCondition());
		auto blockText = visitReturnString(ctx->block());

		auto ret = std::format("for ({}) {}", forConditionText, blockText);
		return ret;

	}
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitForCondition(OrcParser::ForConditionContext* ctx) {
	string declText;
	string condText;
	string incText;

	int st = 0;
	for (int i = 0; i < ctx->children.size(); i++) {
		auto kid = ctx->children[i];

		if (kid->getText() == ";") {
			st++;
		}
		else {
			if (st == 0) {
				declText = visitReturnString(kid);
			}
			else if (st == 1) {
				condText = visitReturnString(kid);
			}
			else if (st == 2) {
				incText = visitReturnString(kid);
			}
		}
	}
	auto ret = std::format("{}; {}; {}", declText, condText, incText);
	return ret;
}

std::any GenOrcCodeVisitor::visitSelectionStatement(OrcParser::SelectionStatementContext* ctx) {
	auto exprs = ctx->singleExpression();
	auto blocks = ctx->block();
	string text;
	for (int i = 0, l = blocks.size(); i < l; i++) {
		auto block = blocks[i];
		auto blockText = visitReturnString(block);
		if (i == 0 || i < l - 1) {

			auto expr = exprs[i];
			auto exprText = visitReturnString(expr);
			//没有自带了括号
			if (dynamic_cast<OrcParser::ParenthesizedExpressionContext*>(expr) == NULL) {
				exprText = std::format("({})", exprText);
			}

			text += std::format("{} {} {}", i == 0 ? string("if") : string("else if"), exprText, blockText);
		}
		else {
			text += std::format("else {}", blockText);
		}

	}
	return text;
}

std::any GenOrcCodeVisitor::visitBlock(OrcParser::BlockContext* ctx) {
	auto content = visitChildrenReturnString(ctx);
	auto indentContent = StrUtil::addPrefixPerLine(content, "\t");
	return "{\n" + indentContent + "\n}\n";
}

std::any GenOrcCodeVisitor::visitType(OrcParser::TypeContext* ctx) {
	if (ctx->Id()) {
		return ctx->Id()->getText();
	}
	auto ret =  visitChildrenReturnString(ctx);
	return ret;
}

std::any GenOrcCodeVisitor::visitTypeQualifier(OrcParser::TypeQualifierContext* ctx) {
	return ctx->getText() + " ";
}
std::any GenOrcCodeVisitor::visitTerminal(antlr4::tree::TerminalNode* node) {
	//return node->getText();
	return defaultResult();
}


std::any GenOrcCodeVisitor::visitPointer(OrcParser::PointerContext* ctx) {
	auto star = ast_pointerStarText(ctx);
	if (ctx->primitiveType()) {
		auto t = visitReturnString(ctx->primitiveType());
		return std::format("{} {}", t, star);
	}
	auto t = ctx->Id()->getText();
	return std::format("{} {}", t, star);
}

std::any GenOrcCodeVisitor::visitRef(OrcParser::RefContext* ctx) {
	auto type = (ctx->Id()->getText());
	return std::format("{}@ ", type);
}

std::any GenOrcCodeVisitor::visitPrimitiveType(OrcParser::PrimitiveTypeContext* ctx) {
	return ctx->getText();
}

std::any GenOrcCodeVisitor::visitEnumDefinition(OrcParser::EnumDefinitionContext* ctx) {
	std::string mem;
	for (auto& tmp : ctx->enumItem()) {
		mem += "\t" + visitReturnString(tmp);
	}

	return std::format(R"(enum {} {{
{}
}})", ctx->Id()->getText(), mem);
}

std::any GenOrcCodeVisitor::visitEnumItem(OrcParser::EnumItemContext* ctx) {
	if (ctx->DecimalLiteral()) {
		return std::format("\t{} = {}, \n", ctx->fullname, ctx->DecimalLiteral()->getText());
	}
	return std::format("\t{}, \n", ctx->fullname);
}

std::any GenOrcCodeVisitor::visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) {
	auto ret = visitReturnString(ctx->extensionBlock());
	return std::format(R"(extension {} {{
{}
}}
)"
, ctx->Id()->getText()
, ret);
}

std::any GenOrcCodeVisitor::visitExtensionBlock(OrcParser::ExtensionBlockContext* ctx) {
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) {
	//虚表
	auto className = ctx->Id(0)->getText();
	auto superName = ctx->Id().size() > 1 ? ctx->Id(1)->getText() : std::string("");

	auto block = visitReturnString(ctx->classDefinitionBlock());

	//类的结构定义
	string tag = std::format(R"(class {} {} {}
)"
, className
, superName.empty() ? "" : std::format("extends {}", superName)
, block);
	//类的函数定义

	return tag;
}

std::any GenOrcCodeVisitor::visitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext* ctx) {
	auto code =  visitChildrenReturnString(ctx);
	return std::format(R"({{
{}
}})", code);
}

std::any GenOrcCodeVisitor::visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* ctx) {
	/*auto code = visitChildrenReturnString(ctx);
	return std::format("	{};\n", code);*/


	if (ctx->functionPointerVarDeclaration()) {
		auto ret = visitReturnString(ctx->functionPointerVarDeclaration());
		return ret;
	}
	if (ctx->type()) {
		auto t = visitReturnString(ctx->type());
		auto init = ctx->assignRightPart();
		auto varName = ctx->Id()->getText();
		if (init) {
			auto initCode = visitReturnString(init->singleExpression());
			return std::format("	{} {} = {};\n",  t, varName, initCode);
		}
		return std::format("	{} {};\n",  t, varName);
	}
	return std::string("(invalid var declaration)");
}

std::any GenOrcCodeVisitor::visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx) {
	auto code = visitChildrenReturnString(ctx);
	return StrUtil::addPrefixPerLine(code, "\t");
}

std::any GenOrcCodeVisitor::visitAssignRightPart(OrcParser::AssignRightPartContext* ctx) {
	auto s0 = visitReturnString(ctx->singleExpression());
	return std::format("= {}", s0);
}

std::any GenOrcCodeVisitor::visitArgumentDeclaration(OrcParser::ArgumentDeclarationContext* ctx) {
	if (ctx->type()) {

		auto text = ctx->type()->getText();

		auto s0 = visitReturnString(ctx->type());
		return std::format("{} {}", s0, ctx->Id()->getText());
	}
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext* ctx) {
	std::string s = "(";
	auto args = ctx->argumentDeclaration();
	for (int i = 0, l = args.size(); i < l; i++) {
		s += visitReturnString(args[i]);
		if (i < l - 1) {
			s += ", ";
		}
	}
	return s + ")";
}

std::any GenOrcCodeVisitor::visitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext* ctx) {
	auto type = visitReturnString(ctx->type());
	auto args = visitReturnString(ctx->argumentsDeclaration());
	auto ret = std::format("{} (*{}){}", type, ctx->Id() ? ctx->Id()->getText() : std::string(""), args);
	return ret;
}

//生成函数声明

std::any GenOrcCodeVisitor::visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) {
	auto type = visitReturnString(ctx->type());
	auto args = visitReturnString(ctx->argumentsDeclaration());
	auto name = ctx->fullname.empty() ? ctx->Id()->getText() : ctx->fullname;
	auto block = visitReturnString(ctx->block());

	return type + " " + name + args + block + "\n";
}

//生成函数声明

std::any GenOrcCodeVisitor::visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* ctx) {
	auto staticCode = ctx->Static() ? std::string("static ") : std::string("");
	return staticCode + visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* ctx) {
	auto t = visitChildrenReturnString(ctx) + ";\n";
	return t;
}

std::any GenOrcCodeVisitor::visitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext* ctx) {
	auto type = visitReturnString(ctx->type());
	auto args = visitReturnString(ctx->argumentsDeclaration());
	auto name = ctx->fullname.empty() ? ctx->Id()->getText() : ctx->fullname;

	return std::string("extern ") + type + " " + name + args + "\n";
}

std::any GenOrcCodeVisitor::visitImportStatement(OrcParser::ImportStatementContext* ctx) {
	auto t = ctx->getText();
	return t;
}

std::any GenOrcCodeVisitor::visitIncludeStatement(OrcParser::IncludeStatementContext* ctx) {
	auto inc = visitReturnString(ctx->includePathCharacters());
	return std::format("#include {}\n", inc);
}

std::any GenOrcCodeVisitor::visitIncludePathCharacters(OrcParser::IncludePathCharactersContext* ctx) {
	auto t = ctx->getText();
	return t;
}

std::any GenOrcCodeVisitor::visitPackageStatement(OrcParser::PackageStatementContext* ctx) {
	return visitChildrenReturnString(ctx);
}

std::any GenOrcCodeVisitor::visitLiteral(OrcParser::LiteralContext* ctx) {
	auto nullLiteral = ctx->NullLiteral();
	if (nullLiteral) {
		return string("null");
	}
	return ctx->getText();
}

std::any GenOrcCodeVisitor::visitEos(OrcParser::EosContext* ctx) {
	//return string(";//eos\n");
	return string("");
}
