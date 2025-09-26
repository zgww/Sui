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

using namespace antlrcpptest;
using namespace antlr4;
// 当前ast树生成.orc源码。便于调试
class  GenOrcCodeVisitor : public ReturnStringVisitor {
public:
	//std::vector<std::string> segs;

	//void append(std::string v) {
	//	segs.push_back(v);
	//}


	virtual std::any visitTerminal(antlr4::tree::TerminalNode* node) override;
	virtual std::any visitClosureType(OrcParser::ClosureTypeContext* ctx) override;

	//virtual std::any visitProgram(OrcParser::ProgramContext* ctx) override {
	//	
	//}
	virtual std::any visitClosureExpression(OrcParser::ClosureExpressionContext* ctx) override;


	virtual std::any visitArguments(OrcParser::ArgumentsContext* ctx) override;

	virtual std::any visitExpressionSequence(OrcParser::ExpressionSequenceContext* ctx) override;


	virtual std::any visitTernaryExpression(OrcParser::TernaryExpressionContext* ctx) override;

	virtual std::any visitLogicalAndExpression(OrcParser::LogicalAndExpressionContext* ctx) override;

	virtual std::any visitMemberDotExpression(OrcParser::MemberDotExpressionContext* ctx) override;

	virtual std::any visitMemberIndexExpression(OrcParser::MemberIndexExpressionContext* ctx) override;
	virtual std::any visitPreIncrementExpression(OrcParser::PreIncrementExpressionContext* ctx) override;

	virtual std::any visitLogicalOrExpression(OrcParser::LogicalOrExpressionContext* ctx) override;

	virtual std::any visitNotExpression(OrcParser::NotExpressionContext* ctx) override;

	virtual std::any visitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext* ctx) override;

	virtual std::any visitThisExpression(OrcParser::ThisExpressionContext* ctx) override;

	virtual std::any visitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext* ctx) override;

	virtual std::any visitAssignmentExpression(OrcParser::AssignmentExpressionContext* ctx) override;

	virtual std::any visitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext* ctx) override;

	virtual std::any visitInstanceofExpression(OrcParser::InstanceofExpressionContext* ctx) override;

	virtual std::any visitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext* ctx) override;

	virtual std::any visitEqualityExpression(OrcParser::EqualityExpressionContext* ctx) override;

	virtual std::any visitBitXOrExpression(OrcParser::BitXOrExpressionContext* ctx) override;

	virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext* ctx) override;

	virtual std::any visitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext* ctx) override;


	/*
	- 调用父类方法 super.fn() = > super_fn_fullname(self)    ~~转为全局函数
	- 调用扩展方法 a.b() = > fullname_b(a)        ~~转为全局函数
	*/
	virtual std::any visitCallExpression(OrcParser::CallExpressionContext* ctx) override;

	virtual std::any visitBitShiftExpression(OrcParser::BitShiftExpressionContext* ctx) override;

	//不支持逗号语句
	virtual std::any visitParenthesizedExpression(OrcParser::ParenthesizedExpressionContext* ctx) override;

	virtual std::any visitAdditiveExpression(OrcParser::AdditiveExpressionContext* ctx) override;

	virtual std::any visitRelationalExpression(OrcParser::RelationalExpressionContext* ctx) override;

	virtual std::any visitPostIncrementExpression(OrcParser::PostIncrementExpressionContext* ctx) override;

	virtual std::any visitBitNotExpression(OrcParser::BitNotExpressionContext* ctx) override;

	virtual std::any visitNewExpression(OrcParser::NewExpressionContext* ctx) override;

	virtual std::any visitLiteralExpression(OrcParser::LiteralExpressionContext* ctx) override;

	virtual std::any visitDerefExpression(OrcParser::DerefExpressionContext* ctx) override;

	virtual std::any visitGetAddressExpression(OrcParser::GetAddressExpressionContext* ctx) override;

	virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx) override;

	virtual std::any visitBitAndExpression(OrcParser::BitAndExpressionContext* ctx) override;

	virtual std::any visitBitOrExpression(OrcParser::BitOrExpressionContext* ctx) override;

	virtual std::any visitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext* ctx) override;

	virtual std::any visitCastExpression(OrcParser::CastExpressionContext* ctx) override;

	// ?? 表达式，暂不支持
	virtual std::any visitCoalesceExpression(OrcParser::CoalesceExpressionContext* ctx) override;

	virtual std::any visitLabelClosureExpression(OrcParser::LabelClosureExpressionContext* ctx) override;

	virtual std::any visitAssignmentOperator(OrcParser::AssignmentOperatorContext* ctx) override;

	virtual std::any visitEmptyStatement(OrcParser::EmptyStatementContext* ctx) override;

	virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext* ctx) override;

	virtual std::any visitStructMember(OrcParser::StructMemberContext* ctx) override;

	virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext* ctx) override;

	virtual std::any visitStatement(OrcParser::StatementContext* ctx) override;

	virtual std::any visitContinueStatement(OrcParser::ContinueStatementContext* ctx) override;

	virtual std::any visitBreakStatement(OrcParser::BreakStatementContext* ctx) override;

	virtual std::any visitReturnStatement(OrcParser::ReturnStatementContext* ctx) override;

	virtual std::any visitScopeStatement(OrcParser::ScopeStatementContext* ctx) override;

	virtual std::any visitIterationStatement(OrcParser::IterationStatementContext* ctx) override;

	virtual std::any visitForCondition(OrcParser::ForConditionContext* ctx) override;

	virtual std::any visitSelectionStatement(OrcParser::SelectionStatementContext* ctx) override;

	virtual std::any visitBlock(OrcParser::BlockContext* ctx) override;

	virtual std::any visitType(OrcParser::TypeContext* ctx) override;

	virtual std::any visitTypeQualifier(OrcParser::TypeQualifierContext* ctx) override;

	virtual std::any visitPointer(OrcParser::PointerContext* ctx) override;

	virtual std::any visitRef(OrcParser::RefContext* ctx) override;

	virtual std::any visitPrimitiveType(OrcParser::PrimitiveTypeContext* ctx) override;

	virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext* ctx) override;

	virtual std::any visitEnumItem(OrcParser::EnumItemContext* ctx) override;

	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) override;

	virtual std::any visitExtensionBlock(OrcParser::ExtensionBlockContext* ctx) override;
	
	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override;

	virtual std::any visitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext* ctx) override;

	virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* ctx) override;

	virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx) override;

	virtual std::any visitAssignRightPart(OrcParser::AssignRightPartContext* ctx) override;

	virtual std::any visitArgumentDeclaration(OrcParser::ArgumentDeclarationContext* ctx) override;

	virtual std::any visitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext* ctx) override;

	virtual std::any visitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext* ctx) override;


	//生成函数声明
	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override;

	//生成函数声明
	virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* ctx) override;

	virtual std::any visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* ctx) override;

	virtual std::any visitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext* ctx) override;

	virtual std::any visitImportStatement(OrcParser::ImportStatementContext* ctx) override;

	virtual std::any visitIncludeStatement(OrcParser::IncludeStatementContext* ctx) override;

	virtual std::any visitIncludePathCharacters(OrcParser::IncludePathCharactersContext* ctx) override;

	virtual std::any visitPackageStatement(OrcParser::PackageStatementContext* ctx) override;

	virtual std::any visitLiteral(OrcParser::LiteralContext* ctx) override;

	virtual std::any visitEos(OrcParser::EosContext* ctx) override;

};
