// Generated from e:/luwa/oms_ts/orc-antlr/antlr4-cpp/demo/Orc.g4 by ANTLR 4.13.1

    #include "OrcParserBase.h"

import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link OrcParser}.
 */
public interface OrcListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link OrcParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(OrcParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(OrcParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#rootDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterRootDeclaration(OrcParser.RootDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#rootDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitRootDeclaration(OrcParser.RootDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#arguments}.
	 * @param ctx the parse tree
	 */
	void enterArguments(OrcParser.ArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#arguments}.
	 * @param ctx the parse tree
	 */
	void exitArguments(OrcParser.ArgumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#expressionSequence}.
	 * @param ctx the parse tree
	 */
	void enterExpressionSequence(OrcParser.ExpressionSequenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#expressionSequence}.
	 * @param ctx the parse tree
	 */
	void exitExpressionSequence(OrcParser.ExpressionSequenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#closureExpression}.
	 * @param ctx the parse tree
	 */
	void enterClosureExpression(OrcParser.ClosureExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#closureExpression}.
	 * @param ctx the parse tree
	 */
	void exitClosureExpression(OrcParser.ClosureExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TernaryExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterTernaryExpression(OrcParser.TernaryExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TernaryExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitTernaryExpression(OrcParser.TernaryExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicalAndExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalAndExpression(OrcParser.LogicalAndExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicalAndExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalAndExpression(OrcParser.LogicalAndExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PreIncrementExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterPreIncrementExpression(OrcParser.PreIncrementExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PreIncrementExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitPreIncrementExpression(OrcParser.PreIncrementExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code GetAddressExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterGetAddressExpression(OrcParser.GetAddressExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code GetAddressExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitGetAddressExpression(OrcParser.GetAddressExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicalOrExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterLogicalOrExpression(OrcParser.LogicalOrExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicalOrExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitLogicalOrExpression(OrcParser.LogicalOrExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code NotExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterNotExpression(OrcParser.NotExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code NotExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitNotExpression(OrcParser.NotExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PreDecreaseExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterPreDecreaseExpression(OrcParser.PreDecreaseExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PreDecreaseExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitPreDecreaseExpression(OrcParser.PreDecreaseExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ThisExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterThisExpression(OrcParser.ThisExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ThisExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitThisExpression(OrcParser.ThisExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnaryMinusExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryMinusExpression(OrcParser.UnaryMinusExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnaryMinusExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryMinusExpression(OrcParser.UnaryMinusExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AssignmentExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentExpression(OrcParser.AssignmentExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AssignmentExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentExpression(OrcParser.AssignmentExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PostDecreaseExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterPostDecreaseExpression(OrcParser.PostDecreaseExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PostDecreaseExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitPostDecreaseExpression(OrcParser.PostDecreaseExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code InstanceofExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterInstanceofExpression(OrcParser.InstanceofExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code InstanceofExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitInstanceofExpression(OrcParser.InstanceofExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code UnaryPlusExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterUnaryPlusExpression(OrcParser.UnaryPlusExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code UnaryPlusExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitUnaryPlusExpression(OrcParser.UnaryPlusExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code EqualityExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterEqualityExpression(OrcParser.EqualityExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code EqualityExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitEqualityExpression(OrcParser.EqualityExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BitXOrExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitXOrExpression(OrcParser.BitXOrExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BitXOrExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitXOrExpression(OrcParser.BitXOrExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code SuperExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterSuperExpression(OrcParser.SuperExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code SuperExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitSuperExpression(OrcParser.SuperExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MultiplicativeExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicativeExpression(OrcParser.MultiplicativeExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MultiplicativeExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicativeExpression(OrcParser.MultiplicativeExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code CallExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterCallExpression(OrcParser.CallExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code CallExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitCallExpression(OrcParser.CallExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BitShiftExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitShiftExpression(OrcParser.BitShiftExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BitShiftExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitShiftExpression(OrcParser.BitShiftExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ParenthesizedExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterParenthesizedExpression(OrcParser.ParenthesizedExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ParenthesizedExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitParenthesizedExpression(OrcParser.ParenthesizedExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AdditiveExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterAdditiveExpression(OrcParser.AdditiveExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AdditiveExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitAdditiveExpression(OrcParser.AdditiveExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code RelationalExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterRelationalExpression(OrcParser.RelationalExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code RelationalExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitRelationalExpression(OrcParser.RelationalExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code PostIncrementExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterPostIncrementExpression(OrcParser.PostIncrementExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code PostIncrementExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitPostIncrementExpression(OrcParser.PostIncrementExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BitNotExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitNotExpression(OrcParser.BitNotExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BitNotExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitNotExpression(OrcParser.BitNotExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code NewExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterNewExpression(OrcParser.NewExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code NewExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitNewExpression(OrcParser.NewExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LiteralExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterLiteralExpression(OrcParser.LiteralExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LiteralExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitLiteralExpression(OrcParser.LiteralExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MemberDotExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterMemberDotExpression(OrcParser.MemberDotExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MemberDotExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitMemberDotExpression(OrcParser.MemberDotExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code MemberIndexExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterMemberIndexExpression(OrcParser.MemberIndexExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code MemberIndexExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitMemberIndexExpression(OrcParser.MemberIndexExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DerefExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterDerefExpression(OrcParser.DerefExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DerefExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitDerefExpression(OrcParser.DerefExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code IdentifierExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterIdentifierExpression(OrcParser.IdentifierExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code IdentifierExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitIdentifierExpression(OrcParser.IdentifierExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BitAndExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitAndExpression(OrcParser.BitAndExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BitAndExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitAndExpression(OrcParser.BitAndExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code BitOrExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterBitOrExpression(OrcParser.BitOrExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code BitOrExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitBitOrExpression(OrcParser.BitOrExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code AssignmentOperatorExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentOperatorExpression(OrcParser.AssignmentOperatorExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code AssignmentOperatorExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentOperatorExpression(OrcParser.AssignmentOperatorExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code CastExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterCastExpression(OrcParser.CastExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code CastExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitCastExpression(OrcParser.CastExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code CoalesceExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterCoalesceExpression(OrcParser.CoalesceExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code CoalesceExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitCoalesceExpression(OrcParser.CoalesceExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code labelClosureExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void enterLabelClosureExpression(OrcParser.LabelClosureExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code labelClosureExpression}
	 * labeled alternative in {@link OrcParser#singleExpression}.
	 * @param ctx the parse tree
	 */
	void exitLabelClosureExpression(OrcParser.LabelClosureExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#assignmentOperator}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentOperator(OrcParser.AssignmentOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#assignmentOperator}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentOperator(OrcParser.AssignmentOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatement(OrcParser.EmptyStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatement(OrcParser.EmptyStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#structDefinition}.
	 * @param ctx the parse tree
	 */
	void enterStructDefinition(OrcParser.StructDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#structDefinition}.
	 * @param ctx the parse tree
	 */
	void exitStructDefinition(OrcParser.StructDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#structMember}.
	 * @param ctx the parse tree
	 */
	void enterStructMember(OrcParser.StructMemberContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#structMember}.
	 * @param ctx the parse tree
	 */
	void exitStructMember(OrcParser.StructMemberContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#arraySizeDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterArraySizeDeclaration(OrcParser.ArraySizeDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#arraySizeDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitArraySizeDeclaration(OrcParser.ArraySizeDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#varDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVarDeclaration(OrcParser.VarDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#varDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVarDeclaration(OrcParser.VarDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(OrcParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(OrcParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void enterContinueStatement(OrcParser.ContinueStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#continueStatement}.
	 * @param ctx the parse tree
	 */
	void exitContinueStatement(OrcParser.ContinueStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void enterBreakStatement(OrcParser.BreakStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#breakStatement}.
	 * @param ctx the parse tree
	 */
	void exitBreakStatement(OrcParser.BreakStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void enterReturnStatement(OrcParser.ReturnStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#returnStatement}.
	 * @param ctx the parse tree
	 */
	void exitReturnStatement(OrcParser.ReturnStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#scopeStatement}.
	 * @param ctx the parse tree
	 */
	void enterScopeStatement(OrcParser.ScopeStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#scopeStatement}.
	 * @param ctx the parse tree
	 */
	void exitScopeStatement(OrcParser.ScopeStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void enterIterationStatement(OrcParser.IterationStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#iterationStatement}.
	 * @param ctx the parse tree
	 */
	void exitIterationStatement(OrcParser.IterationStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#forCondition}.
	 * @param ctx the parse tree
	 */
	void enterForCondition(OrcParser.ForConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#forCondition}.
	 * @param ctx the parse tree
	 */
	void exitForCondition(OrcParser.ForConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#selectionStatement}.
	 * @param ctx the parse tree
	 */
	void enterSelectionStatement(OrcParser.SelectionStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#selectionStatement}.
	 * @param ctx the parse tree
	 */
	void exitSelectionStatement(OrcParser.SelectionStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#block}.
	 * @param ctx the parse tree
	 */
	void enterBlock(OrcParser.BlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#block}.
	 * @param ctx the parse tree
	 */
	void exitBlock(OrcParser.BlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(OrcParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(OrcParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#closureType}.
	 * @param ctx the parse tree
	 */
	void enterClosureType(OrcParser.ClosureTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#closureType}.
	 * @param ctx the parse tree
	 */
	void exitClosureType(OrcParser.ClosureTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#functionTypeArg}.
	 * @param ctx the parse tree
	 */
	void enterFunctionTypeArg(OrcParser.FunctionTypeArgContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#functionTypeArg}.
	 * @param ctx the parse tree
	 */
	void exitFunctionTypeArg(OrcParser.FunctionTypeArgContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#attribute}.
	 * @param ctx the parse tree
	 */
	void enterAttribute(OrcParser.AttributeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#attribute}.
	 * @param ctx the parse tree
	 */
	void exitAttribute(OrcParser.AttributeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#functionType}.
	 * @param ctx the parse tree
	 */
	void enterFunctionType(OrcParser.FunctionTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#functionType}.
	 * @param ctx the parse tree
	 */
	void exitFunctionType(OrcParser.FunctionTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#typeQualifier}.
	 * @param ctx the parse tree
	 */
	void enterTypeQualifier(OrcParser.TypeQualifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#typeQualifier}.
	 * @param ctx the parse tree
	 */
	void exitTypeQualifier(OrcParser.TypeQualifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#pointer}.
	 * @param ctx the parse tree
	 */
	void enterPointer(OrcParser.PointerContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#pointer}.
	 * @param ctx the parse tree
	 */
	void exitPointer(OrcParser.PointerContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#ref}.
	 * @param ctx the parse tree
	 */
	void enterRef(OrcParser.RefContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#ref}.
	 * @param ctx the parse tree
	 */
	void exitRef(OrcParser.RefContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#primitiveType}.
	 * @param ctx the parse tree
	 */
	void enterPrimitiveType(OrcParser.PrimitiveTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#primitiveType}.
	 * @param ctx the parse tree
	 */
	void exitPrimitiveType(OrcParser.PrimitiveTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#enumDefinition}.
	 * @param ctx the parse tree
	 */
	void enterEnumDefinition(OrcParser.EnumDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#enumDefinition}.
	 * @param ctx the parse tree
	 */
	void exitEnumDefinition(OrcParser.EnumDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#enumItem}.
	 * @param ctx the parse tree
	 */
	void enterEnumItem(OrcParser.EnumItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#enumItem}.
	 * @param ctx the parse tree
	 */
	void exitEnumItem(OrcParser.EnumItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#extensionDefinition}.
	 * @param ctx the parse tree
	 */
	void enterExtensionDefinition(OrcParser.ExtensionDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#extensionDefinition}.
	 * @param ctx the parse tree
	 */
	void exitExtensionDefinition(OrcParser.ExtensionDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#extensionBlock}.
	 * @param ctx the parse tree
	 */
	void enterExtensionBlock(OrcParser.ExtensionBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#extensionBlock}.
	 * @param ctx the parse tree
	 */
	void exitExtensionBlock(OrcParser.ExtensionBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#classDefinition}.
	 * @param ctx the parse tree
	 */
	void enterClassDefinition(OrcParser.ClassDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#classDefinition}.
	 * @param ctx the parse tree
	 */
	void exitClassDefinition(OrcParser.ClassDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#classDefinitionBlock}.
	 * @param ctx the parse tree
	 */
	void enterClassDefinitionBlock(OrcParser.ClassDefinitionBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#classDefinitionBlock}.
	 * @param ctx the parse tree
	 */
	void exitClassDefinitionBlock(OrcParser.ClassDefinitionBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#classFieldDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterClassFieldDeclaration(OrcParser.ClassFieldDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#classFieldDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitClassFieldDeclaration(OrcParser.ClassFieldDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#methodDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterMethodDeclaration(OrcParser.MethodDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#methodDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitMethodDeclaration(OrcParser.MethodDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#assignRightPart}.
	 * @param ctx the parse tree
	 */
	void enterAssignRightPart(OrcParser.AssignRightPartContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#assignRightPart}.
	 * @param ctx the parse tree
	 */
	void exitAssignRightPart(OrcParser.AssignRightPartContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#argumentDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterArgumentDeclaration(OrcParser.ArgumentDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#argumentDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitArgumentDeclaration(OrcParser.ArgumentDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#argumentsDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterArgumentsDeclaration(OrcParser.ArgumentsDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#argumentsDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitArgumentsDeclaration(OrcParser.ArgumentsDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#functionPointerVarDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterFunctionPointerVarDeclaration(OrcParser.FunctionPointerVarDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#functionPointerVarDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitFunctionPointerVarDeclaration(OrcParser.FunctionPointerVarDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#functionDefinition}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDefinition(OrcParser.FunctionDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#functionDefinition}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDefinition(OrcParser.FunctionDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#globalFunctionDefinition}.
	 * @param ctx the parse tree
	 */
	void enterGlobalFunctionDefinition(OrcParser.GlobalFunctionDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#globalFunctionDefinition}.
	 * @param ctx the parse tree
	 */
	void exitGlobalFunctionDefinition(OrcParser.GlobalFunctionDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#globalVarDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterGlobalVarDeclaration(OrcParser.GlobalVarDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#globalVarDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitGlobalVarDeclaration(OrcParser.GlobalVarDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#externFunctionDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterExternFunctionDeclaration(OrcParser.ExternFunctionDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#externFunctionDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitExternFunctionDeclaration(OrcParser.ExternFunctionDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void enterImportStatement(OrcParser.ImportStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void exitImportStatement(OrcParser.ImportStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#includeStatement}.
	 * @param ctx the parse tree
	 */
	void enterIncludeStatement(OrcParser.IncludeStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#includeStatement}.
	 * @param ctx the parse tree
	 */
	void exitIncludeStatement(OrcParser.IncludeStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#includePathCharacters}.
	 * @param ctx the parse tree
	 */
	void enterIncludePathCharacters(OrcParser.IncludePathCharactersContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#includePathCharacters}.
	 * @param ctx the parse tree
	 */
	void exitIncludePathCharacters(OrcParser.IncludePathCharactersContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#packageStatement}.
	 * @param ctx the parse tree
	 */
	void enterPackageStatement(OrcParser.PackageStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#packageStatement}.
	 * @param ctx the parse tree
	 */
	void exitPackageStatement(OrcParser.PackageStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteral(OrcParser.LiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteral(OrcParser.LiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link OrcParser#eos}.
	 * @param ctx the parse tree
	 */
	void enterEos(OrcParser.EosContext ctx);
	/**
	 * Exit a parse tree produced by {@link OrcParser#eos}.
	 * @param ctx the parse tree
	 */
	void exitEos(OrcParser.EosContext ctx);
}