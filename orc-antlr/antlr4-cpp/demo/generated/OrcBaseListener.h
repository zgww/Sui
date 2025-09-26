
    #include "OrcParserBase.h"


// Generated from Orc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "OrcListener.h"


namespace antlrcpptest {

/**
 * This class provides an empty implementation of OrcListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  OrcBaseListener : public OrcListener {
public:

  virtual void enterProgram(OrcParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(OrcParser::ProgramContext * /*ctx*/) override { }

  virtual void enterRootDeclaration(OrcParser::RootDeclarationContext * /*ctx*/) override { }
  virtual void exitRootDeclaration(OrcParser::RootDeclarationContext * /*ctx*/) override { }

  virtual void enterArguments(OrcParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(OrcParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterExpressionSequence(OrcParser::ExpressionSequenceContext * /*ctx*/) override { }
  virtual void exitExpressionSequence(OrcParser::ExpressionSequenceContext * /*ctx*/) override { }

  virtual void enterClosureExpression(OrcParser::ClosureExpressionContext * /*ctx*/) override { }
  virtual void exitClosureExpression(OrcParser::ClosureExpressionContext * /*ctx*/) override { }

  virtual void enterTernaryExpression(OrcParser::TernaryExpressionContext * /*ctx*/) override { }
  virtual void exitTernaryExpression(OrcParser::TernaryExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(OrcParser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(OrcParser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterPreIncrementExpression(OrcParser::PreIncrementExpressionContext * /*ctx*/) override { }
  virtual void exitPreIncrementExpression(OrcParser::PreIncrementExpressionContext * /*ctx*/) override { }

  virtual void enterGetAddressExpression(OrcParser::GetAddressExpressionContext * /*ctx*/) override { }
  virtual void exitGetAddressExpression(OrcParser::GetAddressExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(OrcParser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(OrcParser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterNotExpression(OrcParser::NotExpressionContext * /*ctx*/) override { }
  virtual void exitNotExpression(OrcParser::NotExpressionContext * /*ctx*/) override { }

  virtual void enterPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext * /*ctx*/) override { }
  virtual void exitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext * /*ctx*/) override { }

  virtual void enterThisExpression(OrcParser::ThisExpressionContext * /*ctx*/) override { }
  virtual void exitThisExpression(OrcParser::ThisExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(OrcParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(OrcParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext * /*ctx*/) override { }
  virtual void exitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext * /*ctx*/) override { }

  virtual void enterInstanceofExpression(OrcParser::InstanceofExpressionContext * /*ctx*/) override { }
  virtual void exitInstanceofExpression(OrcParser::InstanceofExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(OrcParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(OrcParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterBitXOrExpression(OrcParser::BitXOrExpressionContext * /*ctx*/) override { }
  virtual void exitBitXOrExpression(OrcParser::BitXOrExpressionContext * /*ctx*/) override { }

  virtual void enterSuperExpression(OrcParser::SuperExpressionContext * /*ctx*/) override { }
  virtual void exitSuperExpression(OrcParser::SuperExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterCallExpression(OrcParser::CallExpressionContext * /*ctx*/) override { }
  virtual void exitCallExpression(OrcParser::CallExpressionContext * /*ctx*/) override { }

  virtual void enterBitShiftExpression(OrcParser::BitShiftExpressionContext * /*ctx*/) override { }
  virtual void exitBitShiftExpression(OrcParser::BitShiftExpressionContext * /*ctx*/) override { }

  virtual void enterParenthesizedExpression(OrcParser::ParenthesizedExpressionContext * /*ctx*/) override { }
  virtual void exitParenthesizedExpression(OrcParser::ParenthesizedExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(OrcParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(OrcParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(OrcParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(OrcParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterPostIncrementExpression(OrcParser::PostIncrementExpressionContext * /*ctx*/) override { }
  virtual void exitPostIncrementExpression(OrcParser::PostIncrementExpressionContext * /*ctx*/) override { }

  virtual void enterBitNotExpression(OrcParser::BitNotExpressionContext * /*ctx*/) override { }
  virtual void exitBitNotExpression(OrcParser::BitNotExpressionContext * /*ctx*/) override { }

  virtual void enterNewExpression(OrcParser::NewExpressionContext * /*ctx*/) override { }
  virtual void exitNewExpression(OrcParser::NewExpressionContext * /*ctx*/) override { }

  virtual void enterLiteralExpression(OrcParser::LiteralExpressionContext * /*ctx*/) override { }
  virtual void exitLiteralExpression(OrcParser::LiteralExpressionContext * /*ctx*/) override { }

  virtual void enterMemberDotExpression(OrcParser::MemberDotExpressionContext * /*ctx*/) override { }
  virtual void exitMemberDotExpression(OrcParser::MemberDotExpressionContext * /*ctx*/) override { }

  virtual void enterMemberIndexExpression(OrcParser::MemberIndexExpressionContext * /*ctx*/) override { }
  virtual void exitMemberIndexExpression(OrcParser::MemberIndexExpressionContext * /*ctx*/) override { }

  virtual void enterDerefExpression(OrcParser::DerefExpressionContext * /*ctx*/) override { }
  virtual void exitDerefExpression(OrcParser::DerefExpressionContext * /*ctx*/) override { }

  virtual void enterIdentifierExpression(OrcParser::IdentifierExpressionContext * /*ctx*/) override { }
  virtual void exitIdentifierExpression(OrcParser::IdentifierExpressionContext * /*ctx*/) override { }

  virtual void enterBitAndExpression(OrcParser::BitAndExpressionContext * /*ctx*/) override { }
  virtual void exitBitAndExpression(OrcParser::BitAndExpressionContext * /*ctx*/) override { }

  virtual void enterBitOrExpression(OrcParser::BitOrExpressionContext * /*ctx*/) override { }
  virtual void exitBitOrExpression(OrcParser::BitOrExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext * /*ctx*/) override { }

  virtual void enterCastExpression(OrcParser::CastExpressionContext * /*ctx*/) override { }
  virtual void exitCastExpression(OrcParser::CastExpressionContext * /*ctx*/) override { }

  virtual void enterCoalesceExpression(OrcParser::CoalesceExpressionContext * /*ctx*/) override { }
  virtual void exitCoalesceExpression(OrcParser::CoalesceExpressionContext * /*ctx*/) override { }

  virtual void enterLabelClosureExpression(OrcParser::LabelClosureExpressionContext * /*ctx*/) override { }
  virtual void exitLabelClosureExpression(OrcParser::LabelClosureExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(OrcParser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(OrcParser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterEmptyStatement(OrcParser::EmptyStatementContext * /*ctx*/) override { }
  virtual void exitEmptyStatement(OrcParser::EmptyStatementContext * /*ctx*/) override { }

  virtual void enterStructDefinition(OrcParser::StructDefinitionContext * /*ctx*/) override { }
  virtual void exitStructDefinition(OrcParser::StructDefinitionContext * /*ctx*/) override { }

  virtual void enterStructMember(OrcParser::StructMemberContext * /*ctx*/) override { }
  virtual void exitStructMember(OrcParser::StructMemberContext * /*ctx*/) override { }

  virtual void enterArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext * /*ctx*/) override { }
  virtual void exitArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext * /*ctx*/) override { }

  virtual void enterVarDeclaration(OrcParser::VarDeclarationContext * /*ctx*/) override { }
  virtual void exitVarDeclaration(OrcParser::VarDeclarationContext * /*ctx*/) override { }

  virtual void enterStatement(OrcParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(OrcParser::StatementContext * /*ctx*/) override { }

  virtual void enterContinueStatement(OrcParser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(OrcParser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterBreakStatement(OrcParser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(OrcParser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(OrcParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(OrcParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterScopeStatement(OrcParser::ScopeStatementContext * /*ctx*/) override { }
  virtual void exitScopeStatement(OrcParser::ScopeStatementContext * /*ctx*/) override { }

  virtual void enterIterationStatement(OrcParser::IterationStatementContext * /*ctx*/) override { }
  virtual void exitIterationStatement(OrcParser::IterationStatementContext * /*ctx*/) override { }

  virtual void enterForCondition(OrcParser::ForConditionContext * /*ctx*/) override { }
  virtual void exitForCondition(OrcParser::ForConditionContext * /*ctx*/) override { }

  virtual void enterSelectionStatement(OrcParser::SelectionStatementContext * /*ctx*/) override { }
  virtual void exitSelectionStatement(OrcParser::SelectionStatementContext * /*ctx*/) override { }

  virtual void enterBlock(OrcParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(OrcParser::BlockContext * /*ctx*/) override { }

  virtual void enterType(OrcParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(OrcParser::TypeContext * /*ctx*/) override { }

  virtual void enterClosureType(OrcParser::ClosureTypeContext * /*ctx*/) override { }
  virtual void exitClosureType(OrcParser::ClosureTypeContext * /*ctx*/) override { }

  virtual void enterFunctionTypeArg(OrcParser::FunctionTypeArgContext * /*ctx*/) override { }
  virtual void exitFunctionTypeArg(OrcParser::FunctionTypeArgContext * /*ctx*/) override { }

  virtual void enterAttribute(OrcParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(OrcParser::AttributeContext * /*ctx*/) override { }

  virtual void enterFunctionType(OrcParser::FunctionTypeContext * /*ctx*/) override { }
  virtual void exitFunctionType(OrcParser::FunctionTypeContext * /*ctx*/) override { }

  virtual void enterTypeQualifier(OrcParser::TypeQualifierContext * /*ctx*/) override { }
  virtual void exitTypeQualifier(OrcParser::TypeQualifierContext * /*ctx*/) override { }

  virtual void enterPointer(OrcParser::PointerContext * /*ctx*/) override { }
  virtual void exitPointer(OrcParser::PointerContext * /*ctx*/) override { }

  virtual void enterRef(OrcParser::RefContext * /*ctx*/) override { }
  virtual void exitRef(OrcParser::RefContext * /*ctx*/) override { }

  virtual void enterPrimitiveType(OrcParser::PrimitiveTypeContext * /*ctx*/) override { }
  virtual void exitPrimitiveType(OrcParser::PrimitiveTypeContext * /*ctx*/) override { }

  virtual void enterEnumDefinition(OrcParser::EnumDefinitionContext * /*ctx*/) override { }
  virtual void exitEnumDefinition(OrcParser::EnumDefinitionContext * /*ctx*/) override { }

  virtual void enterEnumItem(OrcParser::EnumItemContext * /*ctx*/) override { }
  virtual void exitEnumItem(OrcParser::EnumItemContext * /*ctx*/) override { }

  virtual void enterExtensionDefinition(OrcParser::ExtensionDefinitionContext * /*ctx*/) override { }
  virtual void exitExtensionDefinition(OrcParser::ExtensionDefinitionContext * /*ctx*/) override { }

  virtual void enterExtensionBlock(OrcParser::ExtensionBlockContext * /*ctx*/) override { }
  virtual void exitExtensionBlock(OrcParser::ExtensionBlockContext * /*ctx*/) override { }

  virtual void enterClassDefinition(OrcParser::ClassDefinitionContext * /*ctx*/) override { }
  virtual void exitClassDefinition(OrcParser::ClassDefinitionContext * /*ctx*/) override { }

  virtual void enterClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext * /*ctx*/) override { }
  virtual void exitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext * /*ctx*/) override { }

  virtual void enterClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext * /*ctx*/) override { }
  virtual void exitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext * /*ctx*/) override { }

  virtual void enterMethodDeclaration(OrcParser::MethodDeclarationContext * /*ctx*/) override { }
  virtual void exitMethodDeclaration(OrcParser::MethodDeclarationContext * /*ctx*/) override { }

  virtual void enterAssignRightPart(OrcParser::AssignRightPartContext * /*ctx*/) override { }
  virtual void exitAssignRightPart(OrcParser::AssignRightPartContext * /*ctx*/) override { }

  virtual void enterArgumentDeclaration(OrcParser::ArgumentDeclarationContext * /*ctx*/) override { }
  virtual void exitArgumentDeclaration(OrcParser::ArgumentDeclarationContext * /*ctx*/) override { }

  virtual void enterArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext * /*ctx*/) override { }
  virtual void exitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionDefinition(OrcParser::FunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitFunctionDefinition(OrcParser::FunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext * /*ctx*/) override { }
  virtual void exitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext * /*ctx*/) override { }

  virtual void enterExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterImportStatement(OrcParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(OrcParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterIncludeStatement(OrcParser::IncludeStatementContext * /*ctx*/) override { }
  virtual void exitIncludeStatement(OrcParser::IncludeStatementContext * /*ctx*/) override { }

  virtual void enterIncludePathCharacters(OrcParser::IncludePathCharactersContext * /*ctx*/) override { }
  virtual void exitIncludePathCharacters(OrcParser::IncludePathCharactersContext * /*ctx*/) override { }

  virtual void enterPackageStatement(OrcParser::PackageStatementContext * /*ctx*/) override { }
  virtual void exitPackageStatement(OrcParser::PackageStatementContext * /*ctx*/) override { }

  virtual void enterLiteral(OrcParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(OrcParser::LiteralContext * /*ctx*/) override { }

  virtual void enterEos(OrcParser::EosContext * /*ctx*/) override { }
  virtual void exitEos(OrcParser::EosContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace antlrcpptest
