
#include "TypeCheckerVisitor.h"
#include "Symbol.h"

bool TypeCheckerVisitor::doCheck(tree::ParseTree*tree)
{
	try {
		this->visit(tree);
		return true;
	}
	catch (std::string errmsg) {
		printf("type check error:%s\n", errmsg.c_str());
		throw errmsg;
	}
	return false;
}

std::string TypeCheckerVisitor::buildErrorWithLine(std::string errmsg, OrcRuleContext* ctx)
{
	return std::format("{} at{}#{}", errmsg, space->path, ctx->getStart()->getLine());
}

bool TypeCheckerVisitor::isAssignable_byClassDefinition(
	std::shared_ptr< SymbolDefinitionClass> left,
	std::shared_ptr< SymbolDefinitionClass> right
	)
{

	while (left && right) {
		if (left->fullname == right->fullname) {
			return true;
		}
		right = right->findSuperSymbolDefinition();
	}

	return false;
}
static bool isNullLiteral(OrcParser::SingleExpressionContext* rightExpr) {
	auto ex = dynamic_cast<OrcParser::LiteralExpressionContext*>(rightExpr);
	if (ex) {
		auto literal = ex->literal();
		if (literal) {
			if (literal->NullLiteral()) {
				return true;
			}
		}
	}
	return false;
}

bool TypeCheckerVisitor::isAssignable(std::shared_ptr<SymbolType> left,  OrcParser::SingleExpressionContext* rightExpr,
	std::shared_ptr<SymbolSpace> leftSpace)
{
	//��������Ĵ���
	// null ��ֵ

	if (isNullLiteral(rightExpr)) {
		auto ref = std::dynamic_pointer_cast<SymbolTypeRef>(left);
		if (ref) {
			return true;
		}
		auto pointer = std::dynamic_pointer_cast<SymbolTypePointer>(left);
		if (pointer) {
			return true;
		}
		return false;
	}

	//���������. Vtable_Object* xx = Checkbox;




	auto right = ast_calcSymbolTypeOfExpressionResult(rightExpr, space);
	if (right) {
		auto ret = left->isAssignable(right->type, leftSpace, right->hostSpace);
		return ret;
	}

	return false;
}

bool TypeCheckerVisitor::isAssignableByType(std::shared_ptr<SymbolType> left, std::shared_ptr<SymbolType> right,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace)
{
	auto ret = left->isAssignable(right, leftSpace, rightSpace);
	return ret;
}

bool TypeCheckerVisitor::isNumber(OrcParser::SingleExpressionContext* ctx)
{
	auto info = ast_calcSymbolTypeOfExpressionResult(ctx, space);
	if (info && info->type) {
		auto typePrimitiveType = std::dynamic_pointer_cast<SymbolTypePrimitiveType>(info->type);
		if (typePrimitiveType) {
			return true;
		}
	}
	return false;
}

bool TypeCheckerVisitor::isOr_number_pointer_ref_array(OrcParser::SingleExpressionContext* ctx)
{
	auto info = ast_calcSymbolTypeOfExpressionResult(ctx, space);
	if (info) {
		auto typePrimitiveType = std::dynamic_pointer_cast<SymbolTypePrimitiveType>(info->type);
		if (typePrimitiveType) { //��������
			return true;
		}
		//ָ���������
		auto typePointer = std::dynamic_pointer_cast<SymbolTypePointer>(info->type);
		auto typeRef = std::dynamic_pointer_cast<SymbolTypeRef>(info->type);
		auto typeArr = std::dynamic_pointer_cast<SymbolTypeArray>(info->type);
		if (typePointer || typeRef || typeArr) {
			return true;
		}
	}
	return false;
}

bool TypeCheckerVisitor::isOr_pointer_ref_array(OrcParser::SingleExpressionContext* ctx)
{
	auto info = ast_calcSymbolTypeOfExpressionResult(ctx, space);
	if (info && info->type) {
		//ָ���������
		auto typePointer = std::dynamic_pointer_cast<SymbolTypePointer>(info->type);
		auto typeRef = std::dynamic_pointer_cast<SymbolTypeRef>(info->type);
		auto typeArr = std::dynamic_pointer_cast<SymbolTypeArray>(info->type);
		if (typePointer || typeRef || typeArr) {
			return true;
		}
	}
	return false;
}

bool TypeCheckerVisitor::isTypeNameDefined(std::string typeName)
{
	//����Closure�ȿ�����
	if (typeName == "Closure") {
		return true;
	}
	if (isNakeTypeName_isPrimitiveType(typeName) || typeName == "Object") {
		return true;
	}

	//��������Ƿ����
	auto typeSymDef = space->findSymbolDefinitionByName_includeImports(typeName);
	if (!typeSymDef) {
		//addTypeErrorByParseTree(ctx, std::format("undefined Type:{}", typeName));
		return false;
	}
	return true;
}

void TypeCheckerVisitor::checkIsNumber(OrcParser::SingleExpressionContext* ctx)
{
	if (!isNumber(ctx)) {
		isNumber(ctx);
		addTypeErrorByParseTree(ctx, "not number type");
		throw buildErrorWithLine("not number type", ctx);
	}
}

std::any TypeCheckerVisitor::visitChildren(antlr4::tree::ParseTree* node)
{
	try {
		return ReturnStringVisitor::visitChildren(node);
	}
	catch (std::string msg)
	{
	}
	return std::string("");
}

std::any TypeCheckerVisitor::visitLogicalAndExpression(OrcParser::LogicalAndExpressionContext* ctx)
{
	//�������: ָ�롢���á����֡�bool
	if (!isOr_number_pointer_ref_array(ctx->singleExpression(0))) {
		isOr_number_pointer_ref_array(ctx->singleExpression(0));
		addTypeErrorByParseTree(ctx, "not number|pointer|ref|array type");
		throw buildErrorWithLine("not number|pointer|ref|array type", ctx);
	}
	if (!isOr_number_pointer_ref_array(ctx->singleExpression(1))) {
		isOr_number_pointer_ref_array(ctx->singleExpression(1));
		addTypeErrorByParseTree(ctx, "not number|pointer|ref|array type");
		throw buildErrorWithLine("not number|pointer|ref|array type", ctx);
	}

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitLogicalOrExpression(OrcParser::LogicalOrExpressionContext* ctx)
{
	//�������: ָ�롢���á����֡�bool
	if (!isOr_number_pointer_ref_array(ctx->singleExpression(0))) {
		addTypeErrorByParseTree(ctx, "not number|pointer|ref|array type");
		throw buildErrorWithLine("not number|pointer|ref|array type", ctx);
	}
	if (!isOr_number_pointer_ref_array(ctx->singleExpression(1))) {
		addTypeErrorByParseTree(ctx, "not number|pointer|ref|array type");
		throw buildErrorWithLine("not number|pointer|ref|array type", ctx);
	}

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitMemberDotExpression(OrcParser::MemberDotExpressionContext* ctx)
{
	//����Ա����
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitMemberIndexExpression(OrcParser::MemberIndexExpressionContext* ctx)
{
	//����������������ָ��
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitPreIncrementExpression(OrcParser::PreIncrementExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression());
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitNotExpression(OrcParser::NotExpressionContext* ctx)
{
	//�������ƥ��:��������,bool����
	if (
		!isOr_number_pointer_ref_array(ctx->singleExpression())) {
		isOr_number_pointer_ref_array(ctx->singleExpression());
		addTypeErrorByParseTree(ctx, "not expr: not number|pointer|ref|array type");
		throw buildErrorWithLine("not number|pointer|ref|array type", ctx);
	}
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression());
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitThisExpression(OrcParser::ThisExpressionContext* ctx)
{
	auto varInfo = ast_findVarInfoByVarName(ctx, "self", space);;
	if (!varInfo.isFound) {
		addTypeErrorByParseTree(ctx, "self not found");
		throw buildErrorWithLine("self not found", ctx);
	}
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression());
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitAssignmentExpression(OrcParser::AssignmentExpressionContext* ctx)
{
	//�������ƥ��
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression());
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitInstanceofExpression(OrcParser::InstanceofExpressionContext* ctx)
{
	//?
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression());
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitBitXOrExpression(OrcParser::BitXOrExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression(0));
	checkIsNumber(ctx->singleExpression(1));
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitSuperExpression(OrcParser::SuperExpressionContext* ctx)
{
	//���
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression(0));
	checkIsNumber(ctx->singleExpression(1));
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitCallExpression(OrcParser::CallExpressionContext* ctx)
{
	//����Ǻ���
	auto fnInfo = ast_calcSymbolTypeOfExpressionResult(ctx->singleExpression(), space);
	auto symFnType = std::dynamic_pointer_cast<SymbolTypeFunction>(fnInfo->type);
	auto closureType = std::dynamic_pointer_cast<SymbolTypeClosure>(fnInfo->type);


	if (!symFnType && !closureType) {
		addTypeErrorByParseTree(ctx, "not a function or closure");
		throw buildErrorWithLine("not a function or closure", ctx);
	}
	//���������void. ��getchar(void)
	if (symFnType) {
		if (symFnType->args.size() == 1) {
			if (symFnType->args[0]->name == "") {
				auto ret = visitChildren(ctx);
				return ret;
			}
		}
	}

	std::vector<std::shared_ptr<SymbolTypeArg>> args;

	if (symFnType) {
		args = symFnType->args;
	}
	else {
		args = closureType->args;
	}

	//����������ƥ��
	int i = 0;
	for (auto typeArg : args) {
		auto actualArg = ctx->arguments()->singleExpression(i);
		auto actualArgInfo = ast_calcSymbolTypeOfExpressionResult(actualArg, space);
		if (!actualArgInfo) {
			addTypeErrorByParseTree(ctx, std::format("arg {} type error. {} <- find actual arg type fail ",
				i, typeArg->type->toString()));
			throw buildErrorWithLine(
				std::format("arg {} type error. {} <- find actual arg type fail ", i, typeArg->type->toString())
				, ctx);
		}
		if (!isAssignable(typeArg->type, actualArg, fnInfo->hostSpace)) {
			isAssignable(typeArg->type, actualArg, fnInfo->hostSpace);
			addTypeErrorByParseTree(ctx, std::format("arg {} type error. {} <- {} ", 
				i, typeArg->type->toString(), actualArgInfo->type->toString()));
			throw buildErrorWithLine(std::format("arg {} type error ", i), ctx);
		}
		i++;
	}

	auto ret = visitChildren(ctx);
	return ret;
}

// > < >= <= 
std::any TypeCheckerVisitor::visitRelationalExpression(OrcParser::RelationalExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression(0));
	checkIsNumber(ctx->singleExpression(1));
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitPostIncrementExpression(OrcParser::PostIncrementExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression());
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitBitNotExpression(OrcParser::BitNotExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression());
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitDerefExpression(OrcParser::DerefExpressionContext* ctx)
{
	//�������֧�ֽ�����
	if (!isOr_pointer_ref_array(ctx->singleExpression())) {
		isOr_pointer_ref_array(ctx->singleExpression());
		addTypeErrorByParseTree(ctx, std::format("no pointer|ref|array"));
		throw buildErrorWithLine("no pointer|ref|array", ctx);
	}
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitGetAddressExpression(OrcParser::GetAddressExpressionContext* ctx)
{
	//�����ֵ
	auto callExpr = dynamic_cast<OrcParser::CallExpressionContext*>(ctx->singleExpression());
	if (callExpr) {
		addTypeErrorByParseTree(ctx, std::format("can not get address for right value"));
		throw buildErrorWithLine("can not get address for right value", ctx);
	}

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx)
{
	auto varName = ctx->Id()->getText();
	if (varName.starts_with("__builtin")
		|| varName.starts_with("sizeof")
		|| varName.starts_with("offsetof")
		|| varName.starts_with("metaStructOf")
		
		) { //���õ�

	}
	else {
		auto varInfo = ast_findVarInfoByVarName(ctx, ctx->Id()->getText(), space);
		if (!varInfo.isFound) {
			auto varInfo = ast_findVarInfoByVarName(ctx, ctx->Id()->getText(), space);;
			addTypeErrorByParseTree(ctx, std::format("{} not found", varInfo.varName));
			throw buildErrorWithLine(std::format("{} not found", varInfo.varName), ctx);
		}
	}
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitBitAndExpression(OrcParser::BitAndExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression(0));
	checkIsNumber(ctx->singleExpression(1));
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitBitOrExpression(OrcParser::BitOrExpressionContext* ctx)
{
	//�������ƥ��:��������
	checkIsNumber(ctx->singleExpression(0));
	checkIsNumber(ctx->singleExpression(1));
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext* ctx)
{
	//�������ƥ��
	checkIsNumber(ctx->singleExpression(0));
	checkIsNumber(ctx->singleExpression(1));

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitCastExpression(OrcParser::CastExpressionContext* ctx)
{
	auto declType = typeContext_toSymbolType(ctx->type());

	//��������Ƿ����
	if (!isTypeNameDefined(declType->getNakeTypeName())) {
		addTypeErrorByParseTree(ctx, std::format("undefined Type:{}", declType->getNakeTypeName()));
		throw buildErrorWithLine(std::format("undefined Type:{}", declType->getNakeTypeName()), ctx);
	}

	//�������ƥ��

	//��������ת��
	//ָ��cast
	//����cast
	auto ret = visitChildren(ctx);
	return ret;
}


std::any TypeCheckerVisitor::visitVarDeclaration(OrcParser::VarDeclarationContext* ctx)
{
	auto declType = typeContext_toSymbolType(ctx->type());
	//��������Ƿ����
	if (declType && !isTypeNameDefined(declType->getNakeTypeName())) {
		isTypeNameDefined(declType->getNakeTypeName());
		addTypeErrorByParseTree(ctx, std::format("undefined Type:{}", declType->getNakeTypeName()));
		throw buildErrorWithLine(std::format("undefined Type:{}", declType->getNakeTypeName()), ctx);
	}


	//��� ��ʼ�����������ƥ��
	if (ctx->singleExpression()) { //�г�ֵ
		auto typeInfo = ast_calcSymbolTypeOfExpressionResult(ctx->singleExpression(), space);

		if (!typeInfo || !declType) {
			addTypeErrorByParseTree(ctx, std::format("find var declaration type error"));
			throw buildErrorWithLine("find var declaration type error", ctx);
		}
	
		if (!isAssignable(declType, ctx->singleExpression(), space)) {
			isAssignable(declType, ctx->singleExpression(), space);
			addTypeErrorByParseTree(ctx, std::format("init type error"));
			throw buildErrorWithLine("init type error", ctx);
		}
	}

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitThrowStatement(OrcParser::ThrowStatementContext* ctx)
{
	auto typeInfo = ast_calcSymbolTypeOfExpressionResult(ctx->singleExpression(), space);
	if (!typeInfo || !typeInfo->type) {
		addTypeErrorByParseTree(ctx, std::format("throw expression type error"));
		throw buildErrorWithLine("throw expression type error", ctx);
	}
	auto refType = std::dynamic_pointer_cast<SymbolTypeRef>(typeInfo->type);
	if (!refType) {
		addTypeErrorByParseTree(ctx, std::format("throw only supports ref type"));
		throw buildErrorWithLine("throw only supports ref type", ctx);
	}
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitTryStatement(OrcParser::TryStatementContext* ctx)
{
	for (auto catchClause : ctx->catchClause()) {
		auto refCtx = catchClause->ref();
		if (!refCtx) {
			addTypeErrorByParseTree(catchClause, std::format("catch requires ref type"));
			throw buildErrorWithLine("catch requires ref type", catchClause);
		}
		auto catchType = std::make_shared<SymbolTypeRef>();
		catchType->typeName = refCtx->Id()->getText();
		if (!isTypeNameDefined(catchType->getNakeTypeName())) {
			addTypeErrorByParseTree(catchClause, std::format("undefined catch type:{}", catchType->getNakeTypeName()));
			throw buildErrorWithLine(std::format("undefined catch type:{}", catchType->getNakeTypeName()), catchClause);
		}
	}
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitReturnStatement(OrcParser::ReturnStatementContext* ctx)
{

	auto fn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(ctx);
	auto closure = ast_findAncestorByType<OrcParser::ClosureExpressionContext>(ctx);

	OrcParser::TypeContext* returnType = NULL;
	if (fn) {
		returnType = fn->type();
	}
	if (closure) {
		returnType = closure->type();
	}

	if (returnType->getText() == "void") { //����void
		if (ctx->singleExpression()) {
			addTypeErrorByParseTree(ctx, std::format("return expression for void"));
			throw buildErrorWithLine("return expression for void", ctx);
		}

	}
	else {
		//û�з���ֵ
		if (ctx->singleExpression() == NULL) {
			addTypeErrorByParseTree(ctx, std::format("return void error"));
			throw buildErrorWithLine("return void error", ctx);
		}

		//��� ����ƥ��
		auto typeInfo = ast_calcSymbolTypeOfExpressionResult(ctx->singleExpression(), space);

		auto fnReturnType = typeContext_toSymbolType(returnType);

		if (!typeInfo || !fnReturnType ){
			addTypeErrorByParseTree(ctx, std::format("find return type error " ));
			throw buildErrorWithLine("find return type error", ctx);
		}
		if (!isAssignable(fnReturnType, ctx->singleExpression(), space)) {
			isAssignable(fnReturnType, ctx->singleExpression(), space);
			addTypeErrorByParseTree(ctx, std::format("return type error {}<-{}", fnReturnType->toString() , typeInfo->type->toString()  ));
			throw buildErrorWithLine("return type error", ctx);
		}
	}

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx)
{
	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitExtensionBlock(OrcParser::ExtensionBlockContext* ctx)
{
	//����ض���

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitType(OrcParser::TypeContext* ctx)
{
	auto declType = typeContext_toSymbolType(ctx);
	//��������Ƿ����
	if (declType && !isTypeNameDefined(declType->getNakeTypeName())) {
		addTypeErrorByParseTree(ctx, std::format("undefined Type:{}", declType->getNakeTypeName()));
		throw buildErrorWithLine(std::format("undefined Type:{}", declType->getNakeTypeName()), ctx);
	}
	return defaultResult();
}

std::any TypeCheckerVisitor::visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* ctx)
{
	auto declType = typeContext_toSymbolType(ctx->type());
	//��������Ƿ����
	if (declType && !isTypeNameDefined(declType->getNakeTypeName())) {
		addTypeErrorByParseTree(ctx, std::format("undefined Type:{}", declType->getNakeTypeName()));
		throw buildErrorWithLine(std::format("undefined Type:{}", declType->getNakeTypeName()), ctx);
	}

	//����ض���
	auto id = ctx->Id();
	if (id) {
		auto fieldName = id->getText();
		auto classCtx = ast_findAncestorByType<OrcParser::ClassDefinitionContext>(ctx);
		if (classCtx) {
			auto classId = classCtx->Id(0);
			if (classId) {
				auto className = classId->getText();
				auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(space->findSymbolDefinitionByName_includeImports(className));
				if (classDef) {
					int cnt = 0;
					for (auto mem : classDef->members) {
						if (mem->name == fieldName) {
							cnt++;
						}
					}
					if (cnt > 1) {
						addTypeErrorByParseTree(ctx, std::format("class field redefinition"));
					}
				}
			}
		}
		else {
			addTypeErrorByParseTree(ctx, std::format("not in class block"));
		}
	}

	//���ɸ�ֵ
	//��� ��ʼ�����������ƥ��
	if (ctx->assignRightPart() && ctx->assignRightPart()->singleExpression()) { //�г�ֵ
		auto expr = ctx->assignRightPart()->singleExpression();
		auto typeInfo = ast_calcSymbolTypeOfExpressionResult(expr, space);

		if (!typeInfo || !declType) {
			auto typeInfo = ast_calcSymbolTypeOfExpressionResult(expr, space);
			addTypeErrorByParseTree(ctx, std::format("class field find var declaration type error"));
			throw buildErrorWithLine("class field find var declaration type error", ctx);
		}

		if (!isAssignable(declType, expr, space)) {
			isAssignable(declType, expr, space);
			addTypeErrorByParseTree(ctx, std::format("class field init type error"));
			throw buildErrorWithLine("class field init type error", ctx);
		}
	}

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitClassDefinition(OrcParser::ClassDefinitionContext* ctx)
{
	//��� �����ʹ���
	auto superId = ctx->Id(1);
	if (superId) {
		auto className = superId->getText();
		auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(space->findSymbolDefinitionByName_includeImports(className));
		if (!classDef) {
			addTypeErrorByParseTree(superId, std::format("super class {} not definied", className));
		}
	}

	auto ret = visitChildren(ctx);
	return ret;
}

std::any TypeCheckerVisitor::visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx)
{
	//����Ƿ��ض���
	auto ret = visitChildren(ctx);
	return ret;
}

void TypeCheckerVisitor::addTypeError(Range range, std::string message) {
	TypeError err;
	err.message = message;
	err.range = range;
	typeErrors.push_back(err);
}

void TypeCheckerVisitor::addTypeErrorByParseTree(antlr4::tree::ParseTree* tree, std::string message)
{
	Range r;
	do {
		auto term = dynamic_cast<antlr4::tree::TerminalNode*>(tree);
		if (term) {
			auto l = term->getSymbol()->getLine() - 1;
			auto c = term->getSymbol()->getCharPositionInLine();
			r.set(l, c, l, c + term->getText().size());
			break;
		}

		auto ctx = dynamic_cast<OrcRuleContext*>(tree);
		if (ctx) {
			auto start = ctx->getStart();
			if (start) {
				r.start.line = start->getLine() - 1;
				r.start.character = start->getCharPositionInLine();
				r.end.line = r.start.line;
				r.end.character = r.start.character + start->getText().size();
			}

			auto stop = ctx->getStop();
			if (stop) {
				r.end.line = stop->getLine() - 1;
				r.end.character = stop->getCharPositionInLine();
			}
			break;
		}

	} while (0);

	addTypeError(r, message);
}
