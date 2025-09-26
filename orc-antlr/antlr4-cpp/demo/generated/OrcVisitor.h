
    #include "OrcParserBase.h"


// Generated from Orc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "OrcParser.h"


namespace antlrcpptest {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by OrcParser.
 */
class  OrcVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by OrcParser.
   */
    virtual std::any visitProgram(OrcParser::ProgramContext *context) = 0;

    virtual std::any visitRootDeclaration(OrcParser::RootDeclarationContext *context) = 0;

    virtual std::any visitArguments(OrcParser::ArgumentsContext *context) = 0;

    virtual std::any visitExpressionSequence(OrcParser::ExpressionSequenceContext *context) = 0;

    virtual std::any visitClosureExpression(OrcParser::ClosureExpressionContext *context) = 0;

    virtual std::any visitTernaryExpression(OrcParser::TernaryExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(OrcParser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitPreIncrementExpression(OrcParser::PreIncrementExpressionContext *context) = 0;

    virtual std::any visitGetAddressExpression(OrcParser::GetAddressExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(OrcParser::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitNotExpression(OrcParser::NotExpressionContext *context) = 0;

    virtual std::any visitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext *context) = 0;

    virtual std::any visitThisExpression(OrcParser::ThisExpressionContext *context) = 0;

    virtual std::any visitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext *context) = 0;

    virtual std::any visitAssignmentExpression(OrcParser::AssignmentExpressionContext *context) = 0;

    virtual std::any visitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext *context) = 0;

    virtual std::any visitInstanceofExpression(OrcParser::InstanceofExpressionContext *context) = 0;

    virtual std::any visitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext *context) = 0;

    virtual std::any visitEqualityExpression(OrcParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitBitXOrExpression(OrcParser::BitXOrExpressionContext *context) = 0;

    virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitCallExpression(OrcParser::CallExpressionContext *context) = 0;

    virtual std::any visitBitShiftExpression(OrcParser::BitShiftExpressionContext *context) = 0;

    virtual std::any visitParenthesizedExpression(OrcParser::ParenthesizedExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(OrcParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitRelationalExpression(OrcParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitPostIncrementExpression(OrcParser::PostIncrementExpressionContext *context) = 0;

    virtual std::any visitBitNotExpression(OrcParser::BitNotExpressionContext *context) = 0;

    virtual std::any visitNewExpression(OrcParser::NewExpressionContext *context) = 0;

    virtual std::any visitLiteralExpression(OrcParser::LiteralExpressionContext *context) = 0;

    virtual std::any visitMemberDotExpression(OrcParser::MemberDotExpressionContext *context) = 0;

    virtual std::any visitMemberIndexExpression(OrcParser::MemberIndexExpressionContext *context) = 0;

    virtual std::any visitDerefExpression(OrcParser::DerefExpressionContext *context) = 0;

    virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext *context) = 0;

    virtual std::any visitBitAndExpression(OrcParser::BitAndExpressionContext *context) = 0;

    virtual std::any visitBitOrExpression(OrcParser::BitOrExpressionContext *context) = 0;

    virtual std::any visitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext *context) = 0;

    virtual std::any visitCastExpression(OrcParser::CastExpressionContext *context) = 0;

    virtual std::any visitCoalesceExpression(OrcParser::CoalesceExpressionContext *context) = 0;

    virtual std::any visitLabelClosureExpression(OrcParser::LabelClosureExpressionContext *context) = 0;

    virtual std::any visitAssignmentOperator(OrcParser::AssignmentOperatorContext *context) = 0;

    virtual std::any visitEmptyStatement(OrcParser::EmptyStatementContext *context) = 0;

    virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext *context) = 0;

    virtual std::any visitStructMember(OrcParser::StructMemberContext *context) = 0;

    virtual std::any visitArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext *context) = 0;

    virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext *context) = 0;

    virtual std::any visitStatement(OrcParser::StatementContext *context) = 0;

    virtual std::any visitContinueStatement(OrcParser::ContinueStatementContext *context) = 0;

    virtual std::any visitBreakStatement(OrcParser::BreakStatementContext *context) = 0;

    virtual std::any visitReturnStatement(OrcParser::ReturnStatementContext *context) = 0;

    virtual std::any visitScopeStatement(OrcParser::ScopeStatementContext *context) = 0;

    virtual std::any visitIterationStatement(OrcParser::IterationStatementContext *context) = 0;

    virtual std::any visitForCondition(OrcParser::ForConditionContext *context) = 0;

    virtual std::any visitSelectionStatement(OrcParser::SelectionStatementContext *context) = 0;

    virtual std::any visitBlock(OrcParser::BlockContext *context) = 0;

    virtual std::any visitType(OrcParser::TypeContext *context) = 0;

    virtual std::any visitClosureType(OrcParser::ClosureTypeContext *context) = 0;

    virtual std::any visitFunctionTypeArg(OrcParser::FunctionTypeArgContext *context) = 0;

    virtual std::any visitAttribute(OrcParser::AttributeContext *context) = 0;

    virtual std::any visitFunctionType(OrcParser::FunctionTypeContext *context) = 0;

    virtual std::any visitTypeQualifier(OrcParser::TypeQualifierContext *context) = 0;

    virtual std::any visitPointer(OrcParser::PointerContext *context) = 0;

    virtual std::any visitRef(OrcParser::RefContext *context) = 0;

    virtual std::any visitPrimitiveType(OrcParser::PrimitiveTypeContext *context) = 0;

    virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext *context) = 0;

    virtual std::any visitEnumItem(OrcParser::EnumItemContext *context) = 0;

    virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext *context) = 0;

    virtual std::any visitExtensionBlock(OrcParser::ExtensionBlockContext *context) = 0;

    virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext *context) = 0;

    virtual std::any visitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext *context) = 0;

    virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext *context) = 0;

    virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext *context) = 0;

    virtual std::any visitAssignRightPart(OrcParser::AssignRightPartContext *context) = 0;

    virtual std::any visitArgumentDeclaration(OrcParser::ArgumentDeclarationContext *context) = 0;

    virtual std::any visitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext *context) = 0;

    virtual std::any visitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext *context) = 0;

    virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext *context) = 0;

    virtual std::any visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext *context) = 0;

    virtual std::any visitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext *context) = 0;

    virtual std::any visitImportStatement(OrcParser::ImportStatementContext *context) = 0;

    virtual std::any visitIncludeStatement(OrcParser::IncludeStatementContext *context) = 0;

    virtual std::any visitIncludePathCharacters(OrcParser::IncludePathCharactersContext *context) = 0;

    virtual std::any visitPackageStatement(OrcParser::PackageStatementContext *context) = 0;

    virtual std::any visitLiteral(OrcParser::LiteralContext *context) = 0;

    virtual std::any visitEos(OrcParser::EosContext *context) = 0;


};

}  // namespace antlrcpptest
