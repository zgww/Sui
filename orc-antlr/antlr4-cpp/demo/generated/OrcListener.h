
    #include "OrcParserBase.h"


// Generated from Orc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "OrcParser.h"


namespace antlrcpptest {

/**
 * This interface defines an abstract listener for a parse tree produced by OrcParser.
 */
class  OrcListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(OrcParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(OrcParser::ProgramContext *ctx) = 0;

  virtual void enterRootDeclaration(OrcParser::RootDeclarationContext *ctx) = 0;
  virtual void exitRootDeclaration(OrcParser::RootDeclarationContext *ctx) = 0;

  virtual void enterArguments(OrcParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(OrcParser::ArgumentsContext *ctx) = 0;

  virtual void enterExpressionSequence(OrcParser::ExpressionSequenceContext *ctx) = 0;
  virtual void exitExpressionSequence(OrcParser::ExpressionSequenceContext *ctx) = 0;

  virtual void enterClosureExpression(OrcParser::ClosureExpressionContext *ctx) = 0;
  virtual void exitClosureExpression(OrcParser::ClosureExpressionContext *ctx) = 0;

  virtual void enterTernaryExpression(OrcParser::TernaryExpressionContext *ctx) = 0;
  virtual void exitTernaryExpression(OrcParser::TernaryExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(OrcParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(OrcParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterPreIncrementExpression(OrcParser::PreIncrementExpressionContext *ctx) = 0;
  virtual void exitPreIncrementExpression(OrcParser::PreIncrementExpressionContext *ctx) = 0;

  virtual void enterGetAddressExpression(OrcParser::GetAddressExpressionContext *ctx) = 0;
  virtual void exitGetAddressExpression(OrcParser::GetAddressExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(OrcParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(OrcParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterNotExpression(OrcParser::NotExpressionContext *ctx) = 0;
  virtual void exitNotExpression(OrcParser::NotExpressionContext *ctx) = 0;

  virtual void enterPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext *ctx) = 0;
  virtual void exitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext *ctx) = 0;

  virtual void enterThisExpression(OrcParser::ThisExpressionContext *ctx) = 0;
  virtual void exitThisExpression(OrcParser::ThisExpressionContext *ctx) = 0;

  virtual void enterUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext *ctx) = 0;
  virtual void exitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(OrcParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(OrcParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext *ctx) = 0;
  virtual void exitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext *ctx) = 0;

  virtual void enterInstanceofExpression(OrcParser::InstanceofExpressionContext *ctx) = 0;
  virtual void exitInstanceofExpression(OrcParser::InstanceofExpressionContext *ctx) = 0;

  virtual void enterUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext *ctx) = 0;
  virtual void exitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(OrcParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(OrcParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterBitXOrExpression(OrcParser::BitXOrExpressionContext *ctx) = 0;
  virtual void exitBitXOrExpression(OrcParser::BitXOrExpressionContext *ctx) = 0;

  virtual void enterSuperExpression(OrcParser::SuperExpressionContext *ctx) = 0;
  virtual void exitSuperExpression(OrcParser::SuperExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterCallExpression(OrcParser::CallExpressionContext *ctx) = 0;
  virtual void exitCallExpression(OrcParser::CallExpressionContext *ctx) = 0;

  virtual void enterBitShiftExpression(OrcParser::BitShiftExpressionContext *ctx) = 0;
  virtual void exitBitShiftExpression(OrcParser::BitShiftExpressionContext *ctx) = 0;

  virtual void enterParenthesizedExpression(OrcParser::ParenthesizedExpressionContext *ctx) = 0;
  virtual void exitParenthesizedExpression(OrcParser::ParenthesizedExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(OrcParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(OrcParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(OrcParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(OrcParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterPostIncrementExpression(OrcParser::PostIncrementExpressionContext *ctx) = 0;
  virtual void exitPostIncrementExpression(OrcParser::PostIncrementExpressionContext *ctx) = 0;

  virtual void enterBitNotExpression(OrcParser::BitNotExpressionContext *ctx) = 0;
  virtual void exitBitNotExpression(OrcParser::BitNotExpressionContext *ctx) = 0;

  virtual void enterNewExpression(OrcParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(OrcParser::NewExpressionContext *ctx) = 0;

  virtual void enterLiteralExpression(OrcParser::LiteralExpressionContext *ctx) = 0;
  virtual void exitLiteralExpression(OrcParser::LiteralExpressionContext *ctx) = 0;

  virtual void enterMemberDotExpression(OrcParser::MemberDotExpressionContext *ctx) = 0;
  virtual void exitMemberDotExpression(OrcParser::MemberDotExpressionContext *ctx) = 0;

  virtual void enterMemberIndexExpression(OrcParser::MemberIndexExpressionContext *ctx) = 0;
  virtual void exitMemberIndexExpression(OrcParser::MemberIndexExpressionContext *ctx) = 0;

  virtual void enterDerefExpression(OrcParser::DerefExpressionContext *ctx) = 0;
  virtual void exitDerefExpression(OrcParser::DerefExpressionContext *ctx) = 0;

  virtual void enterIdentifierExpression(OrcParser::IdentifierExpressionContext *ctx) = 0;
  virtual void exitIdentifierExpression(OrcParser::IdentifierExpressionContext *ctx) = 0;

  virtual void enterBitAndExpression(OrcParser::BitAndExpressionContext *ctx) = 0;
  virtual void exitBitAndExpression(OrcParser::BitAndExpressionContext *ctx) = 0;

  virtual void enterBitOrExpression(OrcParser::BitOrExpressionContext *ctx) = 0;
  virtual void exitBitOrExpression(OrcParser::BitOrExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext *ctx) = 0;
  virtual void exitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext *ctx) = 0;

  virtual void enterCastExpression(OrcParser::CastExpressionContext *ctx) = 0;
  virtual void exitCastExpression(OrcParser::CastExpressionContext *ctx) = 0;

  virtual void enterCoalesceExpression(OrcParser::CoalesceExpressionContext *ctx) = 0;
  virtual void exitCoalesceExpression(OrcParser::CoalesceExpressionContext *ctx) = 0;

  virtual void enterLabelClosureExpression(OrcParser::LabelClosureExpressionContext *ctx) = 0;
  virtual void exitLabelClosureExpression(OrcParser::LabelClosureExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(OrcParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(OrcParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterEmptyStatement(OrcParser::EmptyStatementContext *ctx) = 0;
  virtual void exitEmptyStatement(OrcParser::EmptyStatementContext *ctx) = 0;

  virtual void enterStructDefinition(OrcParser::StructDefinitionContext *ctx) = 0;
  virtual void exitStructDefinition(OrcParser::StructDefinitionContext *ctx) = 0;

  virtual void enterStructMember(OrcParser::StructMemberContext *ctx) = 0;
  virtual void exitStructMember(OrcParser::StructMemberContext *ctx) = 0;

  virtual void enterArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext *ctx) = 0;
  virtual void exitArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext *ctx) = 0;

  virtual void enterVarDeclaration(OrcParser::VarDeclarationContext *ctx) = 0;
  virtual void exitVarDeclaration(OrcParser::VarDeclarationContext *ctx) = 0;

  virtual void enterStatement(OrcParser::StatementContext *ctx) = 0;
  virtual void exitStatement(OrcParser::StatementContext *ctx) = 0;

  virtual void enterContinueStatement(OrcParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(OrcParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(OrcParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(OrcParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(OrcParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(OrcParser::ReturnStatementContext *ctx) = 0;

  virtual void enterScopeStatement(OrcParser::ScopeStatementContext *ctx) = 0;
  virtual void exitScopeStatement(OrcParser::ScopeStatementContext *ctx) = 0;

  virtual void enterIterationStatement(OrcParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(OrcParser::IterationStatementContext *ctx) = 0;

  virtual void enterForCondition(OrcParser::ForConditionContext *ctx) = 0;
  virtual void exitForCondition(OrcParser::ForConditionContext *ctx) = 0;

  virtual void enterSelectionStatement(OrcParser::SelectionStatementContext *ctx) = 0;
  virtual void exitSelectionStatement(OrcParser::SelectionStatementContext *ctx) = 0;

  virtual void enterBlock(OrcParser::BlockContext *ctx) = 0;
  virtual void exitBlock(OrcParser::BlockContext *ctx) = 0;

  virtual void enterType(OrcParser::TypeContext *ctx) = 0;
  virtual void exitType(OrcParser::TypeContext *ctx) = 0;

  virtual void enterClosureType(OrcParser::ClosureTypeContext *ctx) = 0;
  virtual void exitClosureType(OrcParser::ClosureTypeContext *ctx) = 0;

  virtual void enterFunctionTypeArg(OrcParser::FunctionTypeArgContext *ctx) = 0;
  virtual void exitFunctionTypeArg(OrcParser::FunctionTypeArgContext *ctx) = 0;

  virtual void enterAttribute(OrcParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(OrcParser::AttributeContext *ctx) = 0;

  virtual void enterFunctionType(OrcParser::FunctionTypeContext *ctx) = 0;
  virtual void exitFunctionType(OrcParser::FunctionTypeContext *ctx) = 0;

  virtual void enterTypeQualifier(OrcParser::TypeQualifierContext *ctx) = 0;
  virtual void exitTypeQualifier(OrcParser::TypeQualifierContext *ctx) = 0;

  virtual void enterPointer(OrcParser::PointerContext *ctx) = 0;
  virtual void exitPointer(OrcParser::PointerContext *ctx) = 0;

  virtual void enterRef(OrcParser::RefContext *ctx) = 0;
  virtual void exitRef(OrcParser::RefContext *ctx) = 0;

  virtual void enterPrimitiveType(OrcParser::PrimitiveTypeContext *ctx) = 0;
  virtual void exitPrimitiveType(OrcParser::PrimitiveTypeContext *ctx) = 0;

  virtual void enterEnumDefinition(OrcParser::EnumDefinitionContext *ctx) = 0;
  virtual void exitEnumDefinition(OrcParser::EnumDefinitionContext *ctx) = 0;

  virtual void enterEnumItem(OrcParser::EnumItemContext *ctx) = 0;
  virtual void exitEnumItem(OrcParser::EnumItemContext *ctx) = 0;

  virtual void enterExtensionDefinition(OrcParser::ExtensionDefinitionContext *ctx) = 0;
  virtual void exitExtensionDefinition(OrcParser::ExtensionDefinitionContext *ctx) = 0;

  virtual void enterExtensionBlock(OrcParser::ExtensionBlockContext *ctx) = 0;
  virtual void exitExtensionBlock(OrcParser::ExtensionBlockContext *ctx) = 0;

  virtual void enterClassDefinition(OrcParser::ClassDefinitionContext *ctx) = 0;
  virtual void exitClassDefinition(OrcParser::ClassDefinitionContext *ctx) = 0;

  virtual void enterClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext *ctx) = 0;
  virtual void exitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext *ctx) = 0;

  virtual void enterClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext *ctx) = 0;
  virtual void exitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext *ctx) = 0;

  virtual void enterMethodDeclaration(OrcParser::MethodDeclarationContext *ctx) = 0;
  virtual void exitMethodDeclaration(OrcParser::MethodDeclarationContext *ctx) = 0;

  virtual void enterAssignRightPart(OrcParser::AssignRightPartContext *ctx) = 0;
  virtual void exitAssignRightPart(OrcParser::AssignRightPartContext *ctx) = 0;

  virtual void enterArgumentDeclaration(OrcParser::ArgumentDeclarationContext *ctx) = 0;
  virtual void exitArgumentDeclaration(OrcParser::ArgumentDeclarationContext *ctx) = 0;

  virtual void enterArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext *ctx) = 0;
  virtual void exitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext *ctx) = 0;

  virtual void enterFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext *ctx) = 0;
  virtual void exitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext *ctx) = 0;

  virtual void enterFunctionDefinition(OrcParser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(OrcParser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext *ctx) = 0;
  virtual void exitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext *ctx) = 0;

  virtual void enterGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext *ctx) = 0;
  virtual void exitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext *ctx) = 0;

  virtual void enterExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext *ctx) = 0;
  virtual void exitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext *ctx) = 0;

  virtual void enterImportStatement(OrcParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(OrcParser::ImportStatementContext *ctx) = 0;

  virtual void enterIncludeStatement(OrcParser::IncludeStatementContext *ctx) = 0;
  virtual void exitIncludeStatement(OrcParser::IncludeStatementContext *ctx) = 0;

  virtual void enterIncludePathCharacters(OrcParser::IncludePathCharactersContext *ctx) = 0;
  virtual void exitIncludePathCharacters(OrcParser::IncludePathCharactersContext *ctx) = 0;

  virtual void enterPackageStatement(OrcParser::PackageStatementContext *ctx) = 0;
  virtual void exitPackageStatement(OrcParser::PackageStatementContext *ctx) = 0;

  virtual void enterLiteral(OrcParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(OrcParser::LiteralContext *ctx) = 0;

  virtual void enterEos(OrcParser::EosContext *ctx) = 0;
  virtual void exitEos(OrcParser::EosContext *ctx) = 0;


};

}  // namespace antlrcpptest
