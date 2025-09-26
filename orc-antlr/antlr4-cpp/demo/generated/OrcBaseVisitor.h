
    #include "OrcParserBase.h"


// Generated from Orc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "OrcVisitor.h"


namespace antlrcpptest {

/**
 * This class provides an empty implementation of OrcVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  OrcBaseVisitor : public OrcVisitor {
public:

  virtual std::any visitProgram(OrcParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRootDeclaration(OrcParser::RootDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(OrcParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionSequence(OrcParser::ExpressionSequenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosureExpression(OrcParser::ClosureExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTernaryExpression(OrcParser::TernaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(OrcParser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPreIncrementExpression(OrcParser::PreIncrementExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGetAddressExpression(OrcParser::GetAddressExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(OrcParser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotExpression(OrcParser::NotExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThisExpression(OrcParser::ThisExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentExpression(OrcParser::AssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstanceofExpression(OrcParser::InstanceofExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpression(OrcParser::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitXOrExpression(OrcParser::BitXOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallExpression(OrcParser::CallExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitShiftExpression(OrcParser::BitShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesizedExpression(OrcParser::ParenthesizedExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(OrcParser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(OrcParser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostIncrementExpression(OrcParser::PostIncrementExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitNotExpression(OrcParser::BitNotExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewExpression(OrcParser::NewExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpression(OrcParser::LiteralExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberDotExpression(OrcParser::MemberDotExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemberIndexExpression(OrcParser::MemberIndexExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDerefExpression(OrcParser::DerefExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitAndExpression(OrcParser::BitAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBitOrExpression(OrcParser::BitOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCastExpression(OrcParser::CastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCoalesceExpression(OrcParser::CoalesceExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabelClosureExpression(OrcParser::LabelClosureExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOperator(OrcParser::AssignmentOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyStatement(OrcParser::EmptyStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructMember(OrcParser::StructMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(OrcParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(OrcParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(OrcParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(OrcParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScopeStatement(OrcParser::ScopeStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterationStatement(OrcParser::IterationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForCondition(OrcParser::ForConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectionStatement(OrcParser::SelectionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(OrcParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(OrcParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClosureType(OrcParser::ClosureTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionTypeArg(OrcParser::FunctionTypeArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute(OrcParser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionType(OrcParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeQualifier(OrcParser::TypeQualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointer(OrcParser::PointerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRef(OrcParser::RefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimitiveType(OrcParser::PrimitiveTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumItem(OrcParser::EnumItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExtensionBlock(OrcParser::ExtensionBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignRightPart(OrcParser::AssignRightPartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentDeclaration(OrcParser::ArgumentDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportStatement(OrcParser::ImportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIncludeStatement(OrcParser::IncludeStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIncludePathCharacters(OrcParser::IncludePathCharactersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPackageStatement(OrcParser::PackageStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(OrcParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEos(OrcParser::EosContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace antlrcpptest
