#pragma once
#include "OrcBaseVisitor.h"
#include <filesystem>
#include "OrcLexer.h"

#include <Windows.h>
#include "md5.h"
#include "Closure.h"
#include <FsUtil.h>
#include <StrUtil.h>
#include "ReturnStringVisitor.h"
#include <vector>
#include <string>
#include "Symbol.h"

using namespace antlrcpptest;
using namespace antlr4;

class SymbolDefinitionClass;
class SymbolType;
class SymbolSpace;

class TypeError {
public:
	std::string message;
	Range range;
	//暂不用
	std::string type;
};

//类型检查器
class TypeCheckerVisitor : public ReturnStringVisitor
{
public:
	std::shared_ptr<SymbolSpace> space = nullptr;
	std::vector<TypeError> typeErrors;

	void addTypeError(Range range, std::string message);
	void addTypeErrorByParseTree(antlr4::tree::ParseTree *tree, std::string message);

	bool doCheck(tree::ParseTree* tree);
	std::string buildErrorWithLine(std::string errmsg, OrcRuleContext* tree);

	//判断是否有
	bool isAssignable_byClassDefinition(
		std::shared_ptr< SymbolDefinitionClass> left,
		std::shared_ptr< SymbolDefinitionClass> right
	);

	//判断类型是否可以赋值
	bool isAssignableByType(
		std::shared_ptr<SymbolType> left,
		std::shared_ptr<SymbolType> right,
		std::shared_ptr<SymbolSpace> leftSpace,
		std::shared_ptr<SymbolSpace> rightSpace);

	bool isAssignable(
		std::shared_ptr<SymbolType> left,
		OrcParser::SingleExpressionContext* rightExpr,
		std::shared_ptr<SymbolSpace> leftSpace);

	bool isNumber(OrcParser::SingleExpressionContext* ctx);
	bool isOr_number_pointer_ref_array(OrcParser::SingleExpressionContext* ctx);
	bool isOr_pointer_ref_array(OrcParser::SingleExpressionContext* ctx);

	//类型是否有定义
	bool isTypeNameDefined(std::string typeName);


	void checkIsNumber(OrcParser::SingleExpressionContext* ctx);


	virtual std::any visitChildren(antlr4::tree::ParseTree* node) override;

	virtual std::any visitLogicalAndExpression(OrcParser::LogicalAndExpressionContext* ctx) override;
	virtual std::any visitLogicalOrExpression(OrcParser::LogicalOrExpressionContext* ctx) override;

	virtual std::any visitMemberDotExpression(OrcParser::MemberDotExpressionContext* ctx) override;

	virtual std::any visitMemberIndexExpression(OrcParser::MemberIndexExpressionContext* ctx) override;
	virtual std::any visitPreIncrementExpression(OrcParser::PreIncrementExpressionContext* ctx) override;


	virtual std::any visitNotExpression(OrcParser::NotExpressionContext* ctx) override;

	virtual std::any visitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext* ctx) override;

	virtual std::any visitThisExpression(OrcParser::ThisExpressionContext* ctx) override;

	virtual std::any visitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext* ctx) override;

	virtual std::any visitAssignmentExpression(OrcParser::AssignmentExpressionContext* ctx) override;

	virtual std::any visitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext* ctx) override;

	virtual std::any visitInstanceofExpression(OrcParser::InstanceofExpressionContext* ctx) override;

	virtual std::any visitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext* ctx) override;

	//virtual std::any visitEqualityExpression(OrcParser::EqualityExpressionContext* ctx) override;

	virtual std::any visitBitXOrExpression(OrcParser::BitXOrExpressionContext* ctx) override;

	virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext* ctx) override;

	virtual std::any visitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext* ctx) override;


	/*
	- 调用父类方法 super.fn() = > super_fn_fullname(self)    ~~转为全局函数
	- 调用扩展方法 a.b() = > fullname_b(a)        ~~转为全局函数
	*/
	virtual std::any visitCallExpression(OrcParser::CallExpressionContext* ctx) override;

	virtual std::any visitRelationalExpression(OrcParser::RelationalExpressionContext* ctx) override;

	virtual std::any visitPostIncrementExpression(OrcParser::PostIncrementExpressionContext* ctx) override;

	virtual std::any visitBitNotExpression(OrcParser::BitNotExpressionContext* ctx) override;

	virtual std::any visitDerefExpression(OrcParser::DerefExpressionContext* ctx) override;

	virtual std::any visitGetAddressExpression(OrcParser::GetAddressExpressionContext* ctx) override;

	virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx) override;

	virtual std::any visitBitAndExpression(OrcParser::BitAndExpressionContext* ctx) override;

	virtual std::any visitBitOrExpression(OrcParser::BitOrExpressionContext* ctx) override;

	virtual std::any visitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext* ctx) override;

	virtual std::any visitCastExpression(OrcParser::CastExpressionContext* ctx) override;

	// ?? 表达式，暂不支持
	//virtual std::any visitCoalesceExpression(OrcParser::CoalesceExpressionContext* ctx) override;

	virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext* ctx) override;

	virtual std::any visitReturnStatement(OrcParser::ReturnStatementContext* ctx) override;

	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) override;

	virtual std::any visitExtensionBlock(OrcParser::ExtensionBlockContext* ctx) override;



	virtual std::any visitType(OrcParser::TypeContext* ctx) override;


	virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* ctx) override;

	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override;

	//virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx) override;

	//生成函数声明
	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override;


	//virtual std::any visitClosureType(OrcParser::ClosureTypeContext* ctx) override;
};

