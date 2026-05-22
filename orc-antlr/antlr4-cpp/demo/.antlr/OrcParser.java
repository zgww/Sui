// Generated from d:/ws/Sui/orc-antlr/antlr4-cpp/demo/Orc.g4 by ANTLR 4.13.1

    #include "OrcParserBase.h"

import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class OrcParser extends OrcParserBase {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		T__24=25, T__25=26, T__26=27, T__27=28, T__28=29, T__29=30, T__30=31, 
		T__31=32, T__32=33, T__33=34, T__34=35, T__35=36, T__36=37, T__37=38, 
		T__38=39, T__39=40, T__40=41, T__41=42, T__42=43, T__43=44, T__44=45, 
		T__45=46, T__46=47, T__47=48, T__48=49, T__49=50, T__50=51, T__51=52, 
		T__52=53, T__53=54, T__54=55, T__55=56, T__56=57, T__57=58, T__58=59, 
		T__59=60, T__60=61, T__61=62, T__62=63, T__63=64, T__64=65, T__65=66, 
		T__66=67, T__67=68, T__68=69, Break=70, Do=71, Instanceof=72, Case=73, 
		Else=74, New=75, Catch=76, Finally=77, Return=78, Void=79, Continue=80, 
		For=81, While=82, This=83, If=84, Throw=85, Try=86, From=87, Struct=88, 
		Class=89, Enum=90, Extends=91, Extern=92, Super=93, Extension=94, Const=95, 
		Export=96, Import=97, Static=98, Async=99, Await=100, Refc=101, NullLiteral=102, 
		BooleanLiteral=103, DecimalLiteral=104, HexIntegerLiteral=105, OctalIntegerLiteral=106, 
		BinaryIntegerLiteral=107, StringLiteral=108, CharLiteral=109, Id=110, 
		CloseBrace=111, LineTerminator=112, Whitespace=113, BlockComment=114, 
		LineComment=115;
	public static final int
		RULE_program = 0, RULE_rootDeclaration = 1, RULE_arguments = 2, RULE_expressionSequence = 3, 
		RULE_closureExpression = 4, RULE_singleExpression = 5, RULE_assignmentOperator = 6, 
		RULE_emptyStatement = 7, RULE_structDefinition = 8, RULE_structMember = 9, 
		RULE_arraySizeDeclaration = 10, RULE_varDeclaration = 11, RULE_statement = 12, 
		RULE_continueStatement = 13, RULE_breakStatement = 14, RULE_throwStatement = 15, 
		RULE_returnStatement = 16, RULE_scopeStatement = 17, RULE_iterationStatement = 18, 
		RULE_forCondition = 19, RULE_forInit = 20, RULE_forVarDeclaration = 21, 
		RULE_forVarInitDeclarator = 22, RULE_selectionStatement = 23, RULE_tryStatement = 24, 
		RULE_catchClause = 25, RULE_finallyClause = 26, RULE_block = 27, RULE_type = 28, 
		RULE_closureType = 29, RULE_functionTypeArg = 30, RULE_attribute = 31, 
		RULE_functionType = 32, RULE_typeQualifier = 33, RULE_pointer = 34, RULE_ref = 35, 
		RULE_primitiveType = 36, RULE_enumDefinition = 37, RULE_enumItem = 38, 
		RULE_extensionDefinition = 39, RULE_extensionBlock = 40, RULE_classDefinition = 41, 
		RULE_classDefinitionBlock = 42, RULE_classFieldDeclaration = 43, RULE_methodDeclaration = 44, 
		RULE_assignRightPart = 45, RULE_argumentDeclaration = 46, RULE_argumentsDeclaration = 47, 
		RULE_functionPointerVarDeclaration = 48, RULE_functionDefinition = 49, 
		RULE_globalFunctionDefinition = 50, RULE_globalVarDeclaration = 51, RULE_externFunctionDeclaration = 52, 
		RULE_importStatement = 53, RULE_includeStatement = 54, RULE_includePathCharacters = 55, 
		RULE_packageStatement = 56, RULE_literal = 57, RULE_eos = 58;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "rootDeclaration", "arguments", "expressionSequence", "closureExpression", 
			"singleExpression", "assignmentOperator", "emptyStatement", "structDefinition", 
			"structMember", "arraySizeDeclaration", "varDeclaration", "statement", 
			"continueStatement", "breakStatement", "throwStatement", "returnStatement", 
			"scopeStatement", "iterationStatement", "forCondition", "forInit", "forVarDeclaration", 
			"forVarInitDeclarator", "selectionStatement", "tryStatement", "catchClause", 
			"finallyClause", "block", "type", "closureType", "functionTypeArg", "attribute", 
			"functionType", "typeQualifier", "pointer", "ref", "primitiveType", "enumDefinition", 
			"enumItem", "extensionDefinition", "extensionBlock", "classDefinition", 
			"classDefinitionBlock", "classFieldDeclaration", "methodDeclaration", 
			"assignRightPart", "argumentDeclaration", "argumentsDeclaration", "functionPointerVarDeclaration", 
			"functionDefinition", "globalFunctionDefinition", "globalVarDeclaration", 
			"externFunctionDeclaration", "importStatement", "includeStatement", "includePathCharacters", 
			"packageStatement", "literal", "eos"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "','", "')'", "'^'", "'++'", "'--'", "'['", "']'", "'.'", 
			"'->'", "'#'", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", 
			"'??'", "'<<'", "'>>'", "'>>>'", "'<'", "'>'", "'<='", "'>='", "'=='", 
			"'!='", "'==='", "'!=='", "'|'", "'&&'", "'||'", "'?'", "':'", "'='", 
			"'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", "'>>>='", "'&='", 
			"'^='", "'|='", "'**='", "'??='", "';'", "'{'", "'else if'", "'__attribute__'", 
			"'restrict'", "'volatile'", "'_Atomic'", "'@'", "'int'", "'short'", "'float'", 
			"'double'", "'char'", "'bool'", "'long'", "'unsigned'", "'import type'", 
			"'#include'", "'package'", "'break'", "'do'", "'instanceof'", "'case'", 
			"'else'", "'new'", "'catch'", "'finally'", "'return'", "'void'", "'continue'", 
			"'for'", "'while'", "'self'", "'if'", "'throw'", "'try'", "'from'", "'struct'", 
			"'class'", "'enum'", "'extends'", "'extern'", "'super'", "'extension'", 
			"'const'", "'export'", "'import'", "'static'", "'async'", "'await'", 
			"'refc'", null, null, null, null, null, null, null, null, null, "'}'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, "Break", 
			"Do", "Instanceof", "Case", "Else", "New", "Catch", "Finally", "Return", 
			"Void", "Continue", "For", "While", "This", "If", "Throw", "Try", "From", 
			"Struct", "Class", "Enum", "Extends", "Extern", "Super", "Extension", 
			"Const", "Export", "Import", "Static", "Async", "Await", "Refc", "NullLiteral", 
			"BooleanLiteral", "DecimalLiteral", "HexIntegerLiteral", "OctalIntegerLiteral", 
			"BinaryIntegerLiteral", "StringLiteral", "CharLiteral", "Id", "CloseBrace", 
			"LineTerminator", "Whitespace", "BlockComment", "LineComment"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Orc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public OrcParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends OrcRuleContext {
		public List<RootDeclarationContext> rootDeclaration() {
			return getRuleContexts(RootDeclarationContext.class);
		}
		public RootDeclarationContext rootDeclaration(int i) {
			return getRuleContext(RootDeclarationContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -322007373356990448L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70398121115711L) != 0)) {
				{
				{
				setState(118);
				rootDeclaration();
				}
				}
				setState(123);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RootDeclarationContext extends OrcRuleContext {
		public PackageStatementContext packageStatement() {
			return getRuleContext(PackageStatementContext.class,0);
		}
		public IncludeStatementContext includeStatement() {
			return getRuleContext(IncludeStatementContext.class,0);
		}
		public ImportStatementContext importStatement() {
			return getRuleContext(ImportStatementContext.class,0);
		}
		public StructDefinitionContext structDefinition() {
			return getRuleContext(StructDefinitionContext.class,0);
		}
		public EnumDefinitionContext enumDefinition() {
			return getRuleContext(EnumDefinitionContext.class,0);
		}
		public ClassDefinitionContext classDefinition() {
			return getRuleContext(ClassDefinitionContext.class,0);
		}
		public ExtensionDefinitionContext extensionDefinition() {
			return getRuleContext(ExtensionDefinitionContext.class,0);
		}
		public GlobalVarDeclarationContext globalVarDeclaration() {
			return getRuleContext(GlobalVarDeclarationContext.class,0);
		}
		public GlobalFunctionDefinitionContext globalFunctionDefinition() {
			return getRuleContext(GlobalFunctionDefinitionContext.class,0);
		}
		public EmptyStatementContext emptyStatement() {
			return getRuleContext(EmptyStatementContext.class,0);
		}
		public RootDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rootDeclaration; }
	}

	public final RootDeclarationContext rootDeclaration() throws RecognitionException {
		RootDeclarationContext _localctx = new RootDeclarationContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_rootDeclaration);
		try {
			setState(134);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(124);
				packageStatement();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(125);
				includeStatement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(126);
				importStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(127);
				structDefinition();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(128);
				enumDefinition();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(129);
				classDefinition();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(130);
				extensionDefinition();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(131);
				globalVarDeclaration();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(132);
				globalFunctionDefinition();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(133);
				emptyStatement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgumentsContext extends OrcRuleContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public ArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arguments; }
	}

	public final ArgumentsContext arguments() throws RecognitionException {
		ArgumentsContext _localctx = new ArgumentsContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_arguments);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(136);
			match(T__0);
			setState(148);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 68585521409L) != 0)) {
				{
				setState(137);
				singleExpression(0);
				setState(142);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(138);
						match(T__1);
						setState(139);
						singleExpression(0);
						}
						} 
					}
					setState(144);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				}
				setState(146);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(145);
					match(T__1);
					}
				}

				}
			}

			setState(150);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionSequenceContext extends OrcRuleContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public ExpressionSequenceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressionSequence; }
	}

	public final ExpressionSequenceContext expressionSequence() throws RecognitionException {
		ExpressionSequenceContext _localctx = new ExpressionSequenceContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_expressionSequence);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(152);
			singleExpression(0);
			setState(157);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(153);
				match(T__1);
				setState(154);
				singleExpression(0);
				}
				}
				setState(159);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClosureExpressionContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ArgumentsDeclarationContext argumentsDeclaration() {
			return getRuleContext(ArgumentsDeclarationContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public ClosureExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_closureExpression; }
	}

	public final ClosureExpressionContext closureExpression() throws RecognitionException {
		ClosureExpressionContext _localctx = new ClosureExpressionContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_closureExpression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(160);
			match(T__3);
			setState(161);
			type();
			setState(163);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(162);
				match(Id);
				}
			}

			setState(165);
			argumentsDeclaration();
			setState(166);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SingleExpressionContext extends OrcRuleContext {
		public SingleExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_singleExpression; }
	 
		public SingleExpressionContext() { }
		public void copyFrom(SingleExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TernaryExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public TernaryExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicalAndExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public LogicalAndExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class PreIncrementExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PreIncrementExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class GetAddressExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public GetAddressExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicalOrExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public LogicalOrExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NotExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public NotExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class PreDecreaseExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PreDecreaseExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ThisExpressionContext extends SingleExpressionContext {
		public TerminalNode This() { return getToken(OrcParser.This, 0); }
		public ThisExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnaryMinusExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public UnaryMinusExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AssignmentExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public AssignmentExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class PostDecreaseExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PostDecreaseExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class InstanceofExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public TerminalNode Instanceof() { return getToken(OrcParser.Instanceof, 0); }
		public InstanceofExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class UnaryPlusExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public UnaryPlusExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class EqualityExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public EqualityExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BitXOrExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitXOrExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class SuperExpressionContext extends SingleExpressionContext {
		public TerminalNode Super() { return getToken(OrcParser.Super, 0); }
		public SuperExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MultiplicativeExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public MultiplicativeExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CallExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public CallExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BitShiftExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitShiftExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParenthesizedExpressionContext extends SingleExpressionContext {
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public ParenthesizedExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AdditiveExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public AdditiveExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class RelationalExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public RelationalExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class PostIncrementExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PostIncrementExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BitNotExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public BitNotExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NewExpressionContext extends SingleExpressionContext {
		public TerminalNode New() { return getToken(OrcParser.New, 0); }
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public NewExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LiteralExpressionContext extends SingleExpressionContext {
		public LiteralContext literal() {
			return getRuleContext(LiteralContext.class,0);
		}
		public LiteralExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MemberDotExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public MemberDotExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MemberIndexExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public MemberIndexExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DerefExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public DerefExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IdentifierExpressionContext extends SingleExpressionContext {
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public IdentifierExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BitAndExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitAndExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class BitOrExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitOrExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AssignmentOperatorExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public AssignmentOperatorContext assignmentOperator() {
			return getRuleContext(AssignmentOperatorContext.class,0);
		}
		public AssignmentOperatorExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CastExpressionContext extends SingleExpressionContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public CastExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CoalesceExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public CoalesceExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LabelClosureExpressionContext extends SingleExpressionContext {
		public ClosureExpressionContext closureExpression() {
			return getRuleContext(ClosureExpressionContext.class,0);
		}
		public LabelClosureExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
	}

	public final SingleExpressionContext singleExpression() throws RecognitionException {
		return singleExpression(0);
	}

	private SingleExpressionContext singleExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		SingleExpressionContext _localctx = new SingleExpressionContext(_ctx, _parentState);
		SingleExpressionContext _prevctx = _localctx;
		int _startState = 10;
		enterRecursionRule(_localctx, 10, RULE_singleExpression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(202);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				{
				_localctx = new LabelClosureExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(169);
				closureExpression();
				}
				break;
			case 2:
				{
				_localctx = new NewExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(170);
				match(New);
				setState(171);
				match(Id);
				setState(172);
				arguments();
				}
				break;
			case 3:
				{
				_localctx = new GetAddressExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(173);
				match(T__11);
				setState(174);
				singleExpression(29);
				}
				break;
			case 4:
				{
				_localctx = new DerefExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(175);
				match(T__12);
				setState(176);
				singleExpression(28);
				}
				break;
			case 5:
				{
				_localctx = new PreIncrementExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(177);
				match(T__4);
				setState(178);
				singleExpression(27);
				}
				break;
			case 6:
				{
				_localctx = new PreDecreaseExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(179);
				match(T__5);
				setState(180);
				singleExpression(26);
				}
				break;
			case 7:
				{
				_localctx = new UnaryPlusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(181);
				match(T__13);
				setState(182);
				singleExpression(25);
				}
				break;
			case 8:
				{
				_localctx = new UnaryMinusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(183);
				match(T__14);
				setState(184);
				singleExpression(24);
				}
				break;
			case 9:
				{
				_localctx = new BitNotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(185);
				match(T__15);
				setState(186);
				singleExpression(23);
				}
				break;
			case 10:
				{
				_localctx = new NotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(187);
				match(T__16);
				setState(188);
				singleExpression(22);
				}
				break;
			case 11:
				{
				_localctx = new CastExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(189);
				match(T__0);
				setState(190);
				type();
				setState(191);
				match(T__2);
				setState(192);
				singleExpression(8);
				}
				break;
			case 12:
				{
				_localctx = new ThisExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(194);
				match(This);
				}
				break;
			case 13:
				{
				_localctx = new IdentifierExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(195);
				match(Id);
				}
				break;
			case 14:
				{
				_localctx = new SuperExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(196);
				match(Super);
				}
				break;
			case 15:
				{
				_localctx = new LiteralExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(197);
				literal();
				}
				break;
			case 16:
				{
				_localctx = new ParenthesizedExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(198);
				match(T__0);
				setState(199);
				expressionSequence();
				setState(200);
				match(T__2);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(272);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(270);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
					case 1:
						{
						_localctx = new MultiplicativeExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(204);
						if (!(precpred(_ctx, 21))) throw new FailedPredicateException(this, "precpred(_ctx, 21)");
						setState(205);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 794624L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(206);
						singleExpression(22);
						}
						break;
					case 2:
						{
						_localctx = new AdditiveExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(207);
						if (!(precpred(_ctx, 20))) throw new FailedPredicateException(this, "precpred(_ctx, 20)");
						setState(208);
						_la = _input.LA(1);
						if ( !(_la==T__13 || _la==T__14) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(209);
						singleExpression(21);
						}
						break;
					case 3:
						{
						_localctx = new CoalesceExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(210);
						if (!(precpred(_ctx, 19))) throw new FailedPredicateException(this, "precpred(_ctx, 19)");
						setState(211);
						match(T__19);
						setState(212);
						singleExpression(20);
						}
						break;
					case 4:
						{
						_localctx = new BitShiftExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(213);
						if (!(precpred(_ctx, 18))) throw new FailedPredicateException(this, "precpred(_ctx, 18)");
						setState(214);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 14680064L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(215);
						singleExpression(19);
						}
						break;
					case 5:
						{
						_localctx = new RelationalExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(216);
						if (!(precpred(_ctx, 17))) throw new FailedPredicateException(this, "precpred(_ctx, 17)");
						setState(217);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 251658240L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(218);
						singleExpression(18);
						}
						break;
					case 6:
						{
						_localctx = new InstanceofExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(219);
						if (!(precpred(_ctx, 16))) throw new FailedPredicateException(this, "precpred(_ctx, 16)");
						setState(220);
						match(Instanceof);
						setState(221);
						singleExpression(17);
						}
						break;
					case 7:
						{
						_localctx = new EqualityExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(222);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(223);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4026531840L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(224);
						singleExpression(16);
						}
						break;
					case 8:
						{
						_localctx = new BitAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(225);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(226);
						match(T__11);
						setState(227);
						singleExpression(15);
						}
						break;
					case 9:
						{
						_localctx = new BitXOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(228);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(229);
						match(T__3);
						setState(230);
						singleExpression(14);
						}
						break;
					case 10:
						{
						_localctx = new BitOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(231);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(232);
						match(T__31);
						setState(233);
						singleExpression(13);
						}
						break;
					case 11:
						{
						_localctx = new LogicalAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(234);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(235);
						match(T__32);
						setState(236);
						singleExpression(12);
						}
						break;
					case 12:
						{
						_localctx = new LogicalOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(237);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(238);
						match(T__33);
						setState(239);
						singleExpression(11);
						}
						break;
					case 13:
						{
						_localctx = new TernaryExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(240);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(241);
						match(T__34);
						setState(242);
						singleExpression(0);
						setState(243);
						match(T__35);
						setState(244);
						singleExpression(10);
						}
						break;
					case 14:
						{
						_localctx = new AssignmentExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(246);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(247);
						match(T__36);
						setState(248);
						singleExpression(7);
						}
						break;
					case 15:
						{
						_localctx = new AssignmentOperatorExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(249);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(250);
						assignmentOperator();
						setState(251);
						singleExpression(6);
						}
						break;
					case 16:
						{
						_localctx = new CallExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(253);
						if (!(precpred(_ctx, 36))) throw new FailedPredicateException(this, "precpred(_ctx, 36)");
						setState(254);
						arguments();
						}
						break;
					case 17:
						{
						_localctx = new PostIncrementExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(255);
						if (!(precpred(_ctx, 35))) throw new FailedPredicateException(this, "precpred(_ctx, 35)");
						setState(256);
						match(T__4);
						}
						break;
					case 18:
						{
						_localctx = new PostDecreaseExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(257);
						if (!(precpred(_ctx, 34))) throw new FailedPredicateException(this, "precpred(_ctx, 34)");
						setState(258);
						match(T__5);
						}
						break;
					case 19:
						{
						_localctx = new MemberIndexExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(259);
						if (!(precpred(_ctx, 32))) throw new FailedPredicateException(this, "precpred(_ctx, 32)");
						setState(260);
						match(T__6);
						setState(261);
						singleExpression(0);
						setState(262);
						match(T__7);
						}
						break;
					case 20:
						{
						_localctx = new MemberDotExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(264);
						if (!(precpred(_ctx, 31))) throw new FailedPredicateException(this, "precpred(_ctx, 31)");
						setState(265);
						_la = _input.LA(1);
						if ( !(_la==T__8 || _la==T__9) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(267);
						_errHandler.sync(this);
						_la = _input.LA(1);
						if (_la==T__10) {
							{
							setState(266);
							match(T__10);
							}
						}

						setState(269);
						match(Id);
						}
						break;
					}
					} 
				}
				setState(274);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssignmentOperatorContext extends OrcRuleContext {
		public AssignmentOperatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignmentOperator; }
	}

	public final AssignmentOperatorContext assignmentOperator() throws RecognitionException {
		AssignmentOperatorContext _localctx = new AssignmentOperatorContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_assignmentOperator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(275);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 2251524935778304L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class EmptyStatementContext extends OrcRuleContext {
		public EmptyStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_emptyStatement; }
	}

	public final EmptyStatementContext emptyStatement() throws RecognitionException {
		EmptyStatementContext _localctx = new EmptyStatementContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_emptyStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(277);
			match(T__50);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StructDefinitionContext extends OrcRuleContext {
		public TerminalNode Struct() { return getToken(OrcParser.Struct, 0); }
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public TerminalNode CloseBrace() { return getToken(OrcParser.CloseBrace, 0); }
		public List<StructMemberContext> structMember() {
			return getRuleContexts(StructMemberContext.class);
		}
		public StructMemberContext structMember(int i) {
			return getRuleContext(StructMemberContext.class,i);
		}
		public StructDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_structDefinition; }
	}

	public final StructDefinitionContext structDefinition() throws RecognitionException {
		StructDefinitionContext _localctx = new StructDefinitionContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_structDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(279);
			match(Struct);
			setState(280);
			match(Id);
			setState(281);
			match(T__51);
			setState(285);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70370908471303L) != 0)) {
				{
				{
				setState(282);
				structMember();
				}
				}
				setState(287);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(288);
			match(CloseBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StructMemberContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ArraySizeDeclarationContext arraySizeDeclaration() {
			return getRuleContext(ArraySizeDeclarationContext.class,0);
		}
		public FunctionPointerVarDeclarationContext functionPointerVarDeclaration() {
			return getRuleContext(FunctionPointerVarDeclarationContext.class,0);
		}
		public StructMemberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_structMember; }
	}

	public final StructMemberContext structMember() throws RecognitionException {
		StructMemberContext _localctx = new StructMemberContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_structMember);
		try {
			setState(300);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(290);
				type();
				setState(291);
				match(Id);
				setState(293);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
				case 1:
					{
					setState(292);
					arraySizeDeclaration();
					}
					break;
				}
				setState(295);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(297);
				functionPointerVarDeclaration();
				setState(298);
				eos();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArraySizeDeclarationContext extends OrcRuleContext {
		public TerminalNode DecimalLiteral() { return getToken(OrcParser.DecimalLiteral, 0); }
		public ArraySizeDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arraySizeDeclaration; }
	}

	public final ArraySizeDeclarationContext arraySizeDeclaration() throws RecognitionException {
		ArraySizeDeclarationContext _localctx = new ArraySizeDeclarationContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_arraySizeDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(302);
			match(T__6);
			setState(303);
			match(DecimalLiteral);
			setState(304);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VarDeclarationContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public TerminalNode Static() { return getToken(OrcParser.Static, 0); }
		public ArraySizeDeclarationContext arraySizeDeclaration() {
			return getRuleContext(ArraySizeDeclarationContext.class,0);
		}
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public FunctionPointerVarDeclarationContext functionPointerVarDeclaration() {
			return getRuleContext(FunctionPointerVarDeclarationContext.class,0);
		}
		public VarDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varDeclaration; }
	}

	public final VarDeclarationContext varDeclaration() throws RecognitionException {
		VarDeclarationContext _localctx = new VarDeclarationContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_varDeclaration);
		int _la;
		try {
			setState(322);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(307);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(306);
					match(Static);
					}
				}

				setState(309);
				type();
				setState(310);
				match(Id);
				setState(312);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
				case 1:
					{
					setState(311);
					arraySizeDeclaration();
					}
					break;
				}
				setState(316);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
				case 1:
					{
					setState(314);
					match(T__36);
					setState(315);
					singleExpression(0);
					}
					break;
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(319);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(318);
					match(Static);
					}
				}

				setState(321);
				functionPointerVarDeclaration();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends OrcRuleContext {
		public ClosureExpressionContext closureExpression() {
			return getRuleContext(ClosureExpressionContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public VarDeclarationContext varDeclaration() {
			return getRuleContext(VarDeclarationContext.class,0);
		}
		public ScopeStatementContext scopeStatement() {
			return getRuleContext(ScopeStatementContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public ContinueStatementContext continueStatement() {
			return getRuleContext(ContinueStatementContext.class,0);
		}
		public BreakStatementContext breakStatement() {
			return getRuleContext(BreakStatementContext.class,0);
		}
		public ThrowStatementContext throwStatement() {
			return getRuleContext(ThrowStatementContext.class,0);
		}
		public SelectionStatementContext selectionStatement() {
			return getRuleContext(SelectionStatementContext.class,0);
		}
		public ReturnStatementContext returnStatement() {
			return getRuleContext(ReturnStatementContext.class,0);
		}
		public IterationStatementContext iterationStatement() {
			return getRuleContext(IterationStatementContext.class,0);
		}
		public TryStatementContext tryStatement() {
			return getRuleContext(TryStatementContext.class,0);
		}
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public EmptyStatementContext emptyStatement() {
			return getRuleContext(EmptyStatementContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_statement);
		try {
			setState(343);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(324);
				closureExpression();
				setState(325);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(327);
				varDeclaration();
				setState(328);
				eos();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(330);
				scopeStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(331);
				block();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(332);
				continueStatement();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(333);
				breakStatement();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(334);
				throwStatement();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(335);
				selectionStatement();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(336);
				returnStatement();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(337);
				iterationStatement();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(338);
				tryStatement();
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(339);
				singleExpression(0);
				setState(340);
				eos();
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(342);
				emptyStatement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ContinueStatementContext extends OrcRuleContext {
		public TerminalNode Continue() { return getToken(OrcParser.Continue, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ContinueStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_continueStatement; }
	}

	public final ContinueStatementContext continueStatement() throws RecognitionException {
		ContinueStatementContext _localctx = new ContinueStatementContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_continueStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(345);
			match(Continue);
			setState(346);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BreakStatementContext extends OrcRuleContext {
		public TerminalNode Break() { return getToken(OrcParser.Break, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public BreakStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_breakStatement; }
	}

	public final BreakStatementContext breakStatement() throws RecognitionException {
		BreakStatementContext _localctx = new BreakStatementContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_breakStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(348);
			match(Break);
			setState(349);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ThrowStatementContext extends OrcRuleContext {
		public TerminalNode Throw() { return getToken(OrcParser.Throw, 0); }
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ThrowStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_throwStatement; }
	}

	public final ThrowStatementContext throwStatement() throws RecognitionException {
		ThrowStatementContext _localctx = new ThrowStatementContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_throwStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(351);
			match(Throw);
			setState(352);
			singleExpression(0);
			setState(353);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ReturnStatementContext extends OrcRuleContext {
		public TerminalNode Return() { return getToken(OrcParser.Return, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public ReturnStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_returnStatement; }
	}

	public final ReturnStatementContext returnStatement() throws RecognitionException {
		ReturnStatementContext _localctx = new ReturnStatementContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_returnStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(355);
			match(Return);
			setState(357);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
			case 1:
				{
				setState(356);
				singleExpression(0);
				}
				break;
			}
			setState(359);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ScopeStatementContext extends OrcRuleContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public ScopeStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_scopeStatement; }
	}

	public final ScopeStatementContext scopeStatement() throws RecognitionException {
		ScopeStatementContext _localctx = new ScopeStatementContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_scopeStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(361);
			singleExpression(0);
			setState(362);
			_la = _input.LA(1);
			if ( !(_la==T__8 || _la==T__15) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(363);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IterationStatementContext extends OrcRuleContext {
		public TerminalNode While() { return getToken(OrcParser.While, 0); }
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode For() { return getToken(OrcParser.For, 0); }
		public ForConditionContext forCondition() {
			return getRuleContext(ForConditionContext.class,0);
		}
		public IterationStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_iterationStatement; }
	}

	public final IterationStatementContext iterationStatement() throws RecognitionException {
		IterationStatementContext _localctx = new IterationStatementContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_iterationStatement);
		try {
			setState(379);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(365);
				match(While);
				setState(366);
				singleExpression(0);
				setState(367);
				block();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(369);
				match(For);
				setState(370);
				match(T__0);
				setState(371);
				forCondition();
				setState(372);
				match(T__2);
				setState(373);
				block();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(375);
				match(For);
				setState(376);
				forCondition();
				setState(377);
				block();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ForConditionContext extends OrcRuleContext {
		public ForInitContext forInit() {
			return getRuleContext(ForInitContext.class,0);
		}
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public ForConditionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forCondition; }
	}

	public final ForConditionContext forCondition() throws RecognitionException {
		ForConditionContext _localctx = new ForConditionContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_forCondition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(382);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170417550L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 140465312139271L) != 0)) {
				{
				setState(381);
				forInit();
				}
			}

			setState(384);
			match(T__50);
			setState(386);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 68585521409L) != 0)) {
				{
				setState(385);
				singleExpression(0);
				}
			}

			setState(388);
			match(T__50);
			setState(390);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 68585521409L) != 0)) {
				{
				setState(389);
				singleExpression(0);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ForInitContext extends OrcRuleContext {
		public ForVarDeclarationContext forVarDeclaration() {
			return getRuleContext(ForVarDeclarationContext.class,0);
		}
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public ForInitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forInit; }
	}

	public final ForInitContext forInit() throws RecognitionException {
		ForInitContext _localctx = new ForInitContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_forInit);
		try {
			setState(394);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,25,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(392);
				forVarDeclaration();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(393);
				singleExpression(0);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ForVarDeclarationContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public List<ForVarInitDeclaratorContext> forVarInitDeclarator() {
			return getRuleContexts(ForVarInitDeclaratorContext.class);
		}
		public ForVarInitDeclaratorContext forVarInitDeclarator(int i) {
			return getRuleContext(ForVarInitDeclaratorContext.class,i);
		}
		public ForVarDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forVarDeclaration; }
	}

	public final ForVarDeclarationContext forVarDeclaration() throws RecognitionException {
		ForVarDeclarationContext _localctx = new ForVarDeclarationContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_forVarDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(396);
			type();
			setState(397);
			forVarInitDeclarator();
			setState(402);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(398);
				match(T__1);
				setState(399);
				forVarInitDeclarator();
				}
				}
				setState(404);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ForVarInitDeclaratorContext extends OrcRuleContext {
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public ArraySizeDeclarationContext arraySizeDeclaration() {
			return getRuleContext(ArraySizeDeclarationContext.class,0);
		}
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public ForVarInitDeclaratorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_forVarInitDeclarator; }
	}

	public final ForVarInitDeclaratorContext forVarInitDeclarator() throws RecognitionException {
		ForVarInitDeclaratorContext _localctx = new ForVarInitDeclaratorContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_forVarInitDeclarator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(405);
			match(Id);
			setState(407);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__6) {
				{
				setState(406);
				arraySizeDeclaration();
				}
			}

			setState(411);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__36) {
				{
				setState(409);
				match(T__36);
				setState(410);
				singleExpression(0);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SelectionStatementContext extends OrcRuleContext {
		public TerminalNode If() { return getToken(OrcParser.If, 0); }
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public List<BlockContext> block() {
			return getRuleContexts(BlockContext.class);
		}
		public BlockContext block(int i) {
			return getRuleContext(BlockContext.class,i);
		}
		public TerminalNode Else() { return getToken(OrcParser.Else, 0); }
		public SelectionStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_selectionStatement; }
	}

	public final SelectionStatementContext selectionStatement() throws RecognitionException {
		SelectionStatementContext _localctx = new SelectionStatementContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_selectionStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(413);
			match(If);
			setState(414);
			singleExpression(0);
			setState(415);
			block();
			setState(422);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__52) {
				{
				{
				setState(416);
				match(T__52);
				setState(417);
				singleExpression(0);
				setState(418);
				block();
				}
				}
				setState(424);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(427);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Else) {
				{
				setState(425);
				match(Else);
				setState(426);
				block();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TryStatementContext extends OrcRuleContext {
		public TerminalNode Try() { return getToken(OrcParser.Try, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public List<CatchClauseContext> catchClause() {
			return getRuleContexts(CatchClauseContext.class);
		}
		public CatchClauseContext catchClause(int i) {
			return getRuleContext(CatchClauseContext.class,i);
		}
		public FinallyClauseContext finallyClause() {
			return getRuleContext(FinallyClauseContext.class,0);
		}
		public TryStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tryStatement; }
	}

	public final TryStatementContext tryStatement() throws RecognitionException {
		TryStatementContext _localctx = new TryStatementContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_tryStatement);
		int _la;
		try {
			setState(443);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,33,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(429);
				match(Try);
				setState(430);
				block();
				setState(432); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(431);
					catchClause();
					}
					}
					setState(434); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==Catch );
				setState(437);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Finally) {
					{
					setState(436);
					finallyClause();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(439);
				match(Try);
				setState(440);
				block();
				setState(441);
				finallyClause();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CatchClauseContext extends OrcRuleContext {
		public TerminalNode Catch() { return getToken(OrcParser.Catch, 0); }
		public RefContext ref() {
			return getRuleContext(RefContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public CatchClauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_catchClause; }
	}

	public final CatchClauseContext catchClause() throws RecognitionException {
		CatchClauseContext _localctx = new CatchClauseContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_catchClause);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(445);
			match(Catch);
			setState(446);
			match(T__0);
			setState(447);
			ref();
			setState(449);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(448);
				match(Id);
				}
			}

			setState(451);
			match(T__2);
			setState(452);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FinallyClauseContext extends OrcRuleContext {
		public TerminalNode Finally() { return getToken(OrcParser.Finally, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public FinallyClauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_finallyClause; }
	}

	public final FinallyClauseContext finallyClause() throws RecognitionException {
		FinallyClauseContext _localctx = new FinallyClauseContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_finallyClause);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(454);
			match(Finally);
			setState(455);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockContext extends OrcRuleContext {
		public TerminalNode CloseBrace() { return getToken(OrcParser.CloseBrace, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(457);
			match(T__51);
			setState(461);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -317503773729361806L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 140482499823687L) != 0)) {
				{
				{
				setState(458);
				statement();
				}
				}
				setState(463);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(464);
			match(CloseBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TypeContext extends OrcRuleContext {
		public PrimitiveTypeContext primitiveType() {
			return getRuleContext(PrimitiveTypeContext.class,0);
		}
		public TypeQualifierContext typeQualifier() {
			return getRuleContext(TypeQualifierContext.class,0);
		}
		public ArraySizeDeclarationContext arraySizeDeclaration() {
			return getRuleContext(ArraySizeDeclarationContext.class,0);
		}
		public ClosureTypeContext closureType() {
			return getRuleContext(ClosureTypeContext.class,0);
		}
		public PointerContext pointer() {
			return getRuleContext(PointerContext.class,0);
		}
		public RefContext ref() {
			return getRuleContext(RefContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public TerminalNode Struct() { return getToken(OrcParser.Struct, 0); }
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_type);
		int _la;
		try {
			setState(483);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,40,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(467);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
					{
					setState(466);
					typeQualifier();
					}
				}

				setState(469);
				primitiveType();
				setState(471);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__6) {
					{
					setState(470);
					arraySizeDeclaration();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(473);
				closureType();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(474);
				pointer();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(475);
				ref();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(477);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
					{
					setState(476);
					typeQualifier();
					}
				}

				setState(480);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Struct) {
					{
					setState(479);
					match(Struct);
					}
				}

				setState(482);
				match(Id);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClosureTypeContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ArgumentsDeclarationContext argumentsDeclaration() {
			return getRuleContext(ArgumentsDeclarationContext.class,0);
		}
		public ClosureTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_closureType; }
	}

	public final ClosureTypeContext closureType() throws RecognitionException {
		ClosureTypeContext _localctx = new ClosureTypeContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_closureType);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(485);
			match(T__3);
			setState(486);
			type();
			setState(487);
			argumentsDeclaration();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionTypeArgContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public FunctionTypeArgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionTypeArg; }
	}

	public final FunctionTypeArgContext functionTypeArg() throws RecognitionException {
		FunctionTypeArgContext _localctx = new FunctionTypeArgContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_functionTypeArg);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(489);
			type();
			setState(491);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(490);
				match(Id);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AttributeContext extends OrcRuleContext {
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public AttributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attribute; }
	}

	public final AttributeContext attribute() throws RecognitionException {
		AttributeContext _localctx = new AttributeContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_attribute);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(493);
			match(T__53);
			setState(494);
			match(T__0);
			setState(495);
			match(T__0);
			setState(496);
			match(Id);
			setState(497);
			match(T__2);
			setState(498);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionTypeContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ArgumentsDeclarationContext argumentsDeclaration() {
			return getRuleContext(ArgumentsDeclarationContext.class,0);
		}
		public List<AttributeContext> attribute() {
			return getRuleContexts(AttributeContext.class);
		}
		public AttributeContext attribute(int i) {
			return getRuleContext(AttributeContext.class,i);
		}
		public FunctionTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionType; }
	}

	public final FunctionTypeContext functionType() throws RecognitionException {
		FunctionTypeContext _localctx = new FunctionTypeContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_functionType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(500);
			type();
			setState(501);
			argumentsDeclaration();
			setState(505);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__53) {
				{
				{
				setState(502);
				attribute();
				}
				}
				setState(507);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TypeQualifierContext extends OrcRuleContext {
		public TerminalNode Const() { return getToken(OrcParser.Const, 0); }
		public TypeQualifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_typeQualifier; }
	}

	public final TypeQualifierContext typeQualifier() throws RecognitionException {
		TypeQualifierContext _localctx = new TypeQualifierContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_typeQualifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(508);
			_la = _input.LA(1);
			if ( !(((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PointerContext extends OrcRuleContext {
		public PrimitiveTypeContext primitiveType() {
			return getRuleContext(PrimitiveTypeContext.class,0);
		}
		public List<TypeQualifierContext> typeQualifier() {
			return getRuleContexts(TypeQualifierContext.class);
		}
		public TypeQualifierContext typeQualifier(int i) {
			return getRuleContext(TypeQualifierContext.class,i);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public TerminalNode Struct() { return getToken(OrcParser.Struct, 0); }
		public PointerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pointer; }
	}

	public final PointerContext pointer() throws RecognitionException {
		PointerContext _localctx = new PointerContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_pointer);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(511);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
				{
				setState(510);
				typeQualifier();
				}
			}

			setState(518);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__58:
			case T__59:
			case T__60:
			case T__61:
			case T__62:
			case T__63:
			case T__64:
			case T__65:
			case Void:
				{
				setState(513);
				primitiveType();
				}
				break;
			case Struct:
			case Id:
				{
				{
				setState(515);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Struct) {
					{
					setState(514);
					match(Struct);
					}
				}

				setState(517);
				match(Id);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(533); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(523);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
					{
					{
					setState(520);
					typeQualifier();
					}
					}
					setState(525);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(526);
				match(T__12);
				setState(530);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,47,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(527);
						typeQualifier();
						}
						} 
					}
					setState(532);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,47,_ctx);
				}
				}
				}
				setState(535); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & 252201579132755968L) != 0) || _la==Const );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RefContext extends OrcRuleContext {
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public TerminalNode Struct() { return getToken(OrcParser.Struct, 0); }
		public RefContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ref; }
	}

	public final RefContext ref() throws RecognitionException {
		RefContext _localctx = new RefContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_ref);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(538);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Struct) {
				{
				setState(537);
				match(Struct);
				}
			}

			setState(540);
			match(Id);
			setState(541);
			match(T__57);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PrimitiveTypeContext extends OrcRuleContext {
		public TerminalNode Void() { return getToken(OrcParser.Void, 0); }
		public PrimitiveTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primitiveType; }
	}

	public final PrimitiveTypeContext primitiveType() throws RecognitionException {
		PrimitiveTypeContext _localctx = new PrimitiveTypeContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_primitiveType);
		try {
			setState(566);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,50,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(543);
				match(T__58);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(544);
				match(T__59);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(545);
				match(T__60);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(546);
				match(T__61);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(547);
				match(T__62);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(548);
				match(T__63);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(549);
				match(Void);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(550);
				match(T__64);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(551);
				match(T__64);
				setState(552);
				match(T__64);
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(553);
				match(T__64);
				setState(554);
				match(T__61);
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(555);
				match(T__65);
				setState(556);
				match(T__62);
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(557);
				match(T__65);
				setState(558);
				match(T__58);
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(559);
				match(T__65);
				setState(560);
				match(T__59);
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(561);
				match(T__65);
				setState(562);
				match(T__64);
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(563);
				match(T__65);
				setState(564);
				match(T__64);
				setState(565);
				match(T__64);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class EnumDefinitionContext extends OrcRuleContext {
		public TerminalNode Enum() { return getToken(OrcParser.Enum, 0); }
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public List<EnumItemContext> enumItem() {
			return getRuleContexts(EnumItemContext.class);
		}
		public EnumItemContext enumItem(int i) {
			return getRuleContext(EnumItemContext.class,i);
		}
		public TerminalNode CloseBrace() { return getToken(OrcParser.CloseBrace, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public EnumDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enumDefinition; }
	}

	public final EnumDefinitionContext enumDefinition() throws RecognitionException {
		EnumDefinitionContext _localctx = new EnumDefinitionContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_enumDefinition);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(568);
			match(Enum);
			setState(569);
			match(Id);
			setState(570);
			match(T__51);
			setState(571);
			enumItem();
			setState(576);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,51,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(572);
					match(T__1);
					setState(573);
					enumItem();
					}
					} 
				}
				setState(578);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,51,_ctx);
			}
			setState(580);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(579);
				match(T__1);
				}
			}

			setState(582);
			match(CloseBrace);
			setState(583);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class EnumItemContext extends OrcRuleContext {
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public TerminalNode DecimalLiteral() { return getToken(OrcParser.DecimalLiteral, 0); }
		public EnumItemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_enumItem; }
	}

	public final EnumItemContext enumItem() throws RecognitionException {
		EnumItemContext _localctx = new EnumItemContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_enumItem);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(585);
			match(Id);
			setState(588);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__36) {
				{
				setState(586);
				match(T__36);
				setState(587);
				match(DecimalLiteral);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExtensionDefinitionContext extends OrcRuleContext {
		public TerminalNode Extension() { return getToken(OrcParser.Extension, 0); }
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public ExtensionBlockContext extensionBlock() {
			return getRuleContext(ExtensionBlockContext.class,0);
		}
		public ExtensionDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_extensionDefinition; }
	}

	public final ExtensionDefinitionContext extensionDefinition() throws RecognitionException {
		ExtensionDefinitionContext _localctx = new ExtensionDefinitionContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_extensionDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(590);
			match(Extension);
			setState(591);
			match(Id);
			setState(592);
			extensionBlock();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExtensionBlockContext extends OrcRuleContext {
		public TerminalNode CloseBrace() { return getToken(OrcParser.CloseBrace, 0); }
		public List<MethodDeclarationContext> methodDeclaration() {
			return getRuleContexts(MethodDeclarationContext.class);
		}
		public MethodDeclarationContext methodDeclaration(int i) {
			return getRuleContext(MethodDeclarationContext.class,i);
		}
		public ExtensionBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_extensionBlock; }
	}

	public final ExtensionBlockContext extensionBlock() throws RecognitionException {
		ExtensionBlockContext _localctx = new ExtensionBlockContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_extensionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(594);
			match(T__51);
			setState(598);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70371176906759L) != 0)) {
				{
				{
				setState(595);
				methodDeclaration();
				}
				}
				setState(600);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(601);
			match(CloseBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClassDefinitionContext extends OrcRuleContext {
		public TerminalNode Class() { return getToken(OrcParser.Class, 0); }
		public List<TerminalNode> Id() { return getTokens(OrcParser.Id); }
		public TerminalNode Id(int i) {
			return getToken(OrcParser.Id, i);
		}
		public ClassDefinitionBlockContext classDefinitionBlock() {
			return getRuleContext(ClassDefinitionBlockContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public TerminalNode Refc() { return getToken(OrcParser.Refc, 0); }
		public TerminalNode Extends() { return getToken(OrcParser.Extends, 0); }
		public ClassDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classDefinition; }
	}

	public final ClassDefinitionContext classDefinition() throws RecognitionException {
		ClassDefinitionContext _localctx = new ClassDefinitionContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_classDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(603);
			match(Class);
			setState(605);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Refc) {
				{
				setState(604);
				match(Refc);
				}
			}

			setState(607);
			match(Id);
			setState(610);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Extends) {
				{
				setState(608);
				match(Extends);
				setState(609);
				match(Id);
				}
			}

			setState(612);
			classDefinitionBlock();
			setState(613);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClassDefinitionBlockContext extends OrcRuleContext {
		public TerminalNode CloseBrace() { return getToken(OrcParser.CloseBrace, 0); }
		public List<ClassFieldDeclarationContext> classFieldDeclaration() {
			return getRuleContexts(ClassFieldDeclarationContext.class);
		}
		public ClassFieldDeclarationContext classFieldDeclaration(int i) {
			return getRuleContext(ClassFieldDeclarationContext.class,i);
		}
		public List<MethodDeclarationContext> methodDeclaration() {
			return getRuleContexts(MethodDeclarationContext.class);
		}
		public MethodDeclarationContext methodDeclaration(int i) {
			return getRuleContext(MethodDeclarationContext.class,i);
		}
		public ClassDefinitionBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classDefinitionBlock; }
	}

	public final ClassDefinitionBlockContext classDefinitionBlock() throws RecognitionException {
		ClassDefinitionBlockContext _localctx = new ClassDefinitionBlockContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_classDefinitionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(615);
			match(T__51);
			setState(620);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70371176906759L) != 0)) {
				{
				setState(618);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,57,_ctx) ) {
				case 1:
					{
					setState(616);
					classFieldDeclaration();
					}
					break;
				case 2:
					{
					setState(617);
					methodDeclaration();
					}
					break;
				}
				}
				setState(622);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(623);
			match(CloseBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClassFieldDeclarationContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ArraySizeDeclarationContext arraySizeDeclaration() {
			return getRuleContext(ArraySizeDeclarationContext.class,0);
		}
		public AssignRightPartContext assignRightPart() {
			return getRuleContext(AssignRightPartContext.class,0);
		}
		public FunctionPointerVarDeclarationContext functionPointerVarDeclaration() {
			return getRuleContext(FunctionPointerVarDeclarationContext.class,0);
		}
		public ClassFieldDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_classFieldDeclaration; }
	}

	public final ClassFieldDeclarationContext classFieldDeclaration() throws RecognitionException {
		ClassFieldDeclarationContext _localctx = new ClassFieldDeclarationContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_classFieldDeclaration);
		try {
			setState(641);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,62,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(625);
				type();
				setState(626);
				match(Id);
				setState(628);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,59,_ctx) ) {
				case 1:
					{
					setState(627);
					arraySizeDeclaration();
					}
					break;
				}
				setState(631);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,60,_ctx) ) {
				case 1:
					{
					setState(630);
					assignRightPart();
					}
					break;
				}
				setState(633);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(635);
				functionPointerVarDeclaration();
				setState(637);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,61,_ctx) ) {
				case 1:
					{
					setState(636);
					assignRightPart();
					}
					break;
				}
				setState(639);
				eos();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MethodDeclarationContext extends OrcRuleContext {
		public FunctionDefinitionContext functionDefinition() {
			return getRuleContext(FunctionDefinitionContext.class,0);
		}
		public ExternFunctionDeclarationContext externFunctionDeclaration() {
			return getRuleContext(ExternFunctionDeclarationContext.class,0);
		}
		public MethodDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_methodDeclaration; }
	}

	public final MethodDeclarationContext methodDeclaration() throws RecognitionException {
		MethodDeclarationContext _localctx = new MethodDeclarationContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_methodDeclaration);
		try {
			setState(645);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__3:
			case T__54:
			case T__55:
			case T__56:
			case T__58:
			case T__59:
			case T__60:
			case T__61:
			case T__62:
			case T__63:
			case T__64:
			case T__65:
			case Void:
			case Struct:
			case Const:
			case Id:
				enterOuterAlt(_localctx, 1);
				{
				setState(643);
				functionDefinition();
				}
				break;
			case Extern:
				enterOuterAlt(_localctx, 2);
				{
				setState(644);
				externFunctionDeclaration();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssignRightPartContext extends OrcRuleContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public AssignRightPartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignRightPart; }
	}

	public final AssignRightPartContext assignRightPart() throws RecognitionException {
		AssignRightPartContext _localctx = new AssignRightPartContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_assignRightPart);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(647);
			match(T__36);
			setState(648);
			singleExpression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgumentDeclarationContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public FunctionPointerVarDeclarationContext functionPointerVarDeclaration() {
			return getRuleContext(FunctionPointerVarDeclarationContext.class,0);
		}
		public ArgumentDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argumentDeclaration; }
	}

	public final ArgumentDeclarationContext argumentDeclaration() throws RecognitionException {
		ArgumentDeclarationContext _localctx = new ArgumentDeclarationContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_argumentDeclaration);
		int _la;
		try {
			setState(655);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,65,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(650);
				type();
				setState(652);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Id) {
					{
					setState(651);
					match(Id);
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(654);
				functionPointerVarDeclaration();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgumentsDeclarationContext extends OrcRuleContext {
		public List<ArgumentDeclarationContext> argumentDeclaration() {
			return getRuleContexts(ArgumentDeclarationContext.class);
		}
		public ArgumentDeclarationContext argumentDeclaration(int i) {
			return getRuleContext(ArgumentDeclarationContext.class,i);
		}
		public ArgumentsDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argumentsDeclaration; }
	}

	public final ArgumentsDeclarationContext argumentsDeclaration() throws RecognitionException {
		ArgumentsDeclarationContext _localctx = new ArgumentsDeclarationContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_argumentsDeclaration);
		int _la;
		try {
			int _alt;
			setState(673);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,69,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(657);
				match(T__0);
				setState(666);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70370908471303L) != 0)) {
					{
					setState(658);
					argumentDeclaration();
					setState(663);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,66,_ctx);
					while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
						if ( _alt==1 ) {
							{
							{
							setState(659);
							match(T__1);
							setState(660);
							argumentDeclaration();
							}
							} 
						}
						setState(665);
						_errHandler.sync(this);
						_alt = getInterpreter().adaptivePredict(_input,66,_ctx);
					}
					}
				}

				setState(669);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(668);
					match(T__1);
					}
				}

				setState(671);
				match(T__2);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionPointerVarDeclarationContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ArgumentsDeclarationContext argumentsDeclaration() {
			return getRuleContext(ArgumentsDeclarationContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public List<AttributeContext> attribute() {
			return getRuleContexts(AttributeContext.class);
		}
		public AttributeContext attribute(int i) {
			return getRuleContext(AttributeContext.class,i);
		}
		public FunctionPointerVarDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionPointerVarDeclaration; }
	}

	public final FunctionPointerVarDeclarationContext functionPointerVarDeclaration() throws RecognitionException {
		FunctionPointerVarDeclarationContext _localctx = new FunctionPointerVarDeclarationContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_functionPointerVarDeclaration);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(675);
			type();
			setState(676);
			match(T__0);
			setState(678); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(677);
				match(T__12);
				}
				}
				setState(680); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__12 );
			setState(683);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(682);
				match(Id);
				}
			}

			setState(685);
			match(T__2);
			setState(686);
			argumentsDeclaration();
			setState(690);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,72,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(687);
					attribute();
					}
					} 
				}
				setState(692);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,72,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionDefinitionContext extends OrcRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public ArgumentsDeclarationContext argumentsDeclaration() {
			return getRuleContext(ArgumentsDeclarationContext.class,0);
		}
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public FunctionDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionDefinition; }
	}

	public final FunctionDefinitionContext functionDefinition() throws RecognitionException {
		FunctionDefinitionContext _localctx = new FunctionDefinitionContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_functionDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(693);
			type();
			setState(694);
			match(Id);
			setState(695);
			argumentsDeclaration();
			setState(696);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class GlobalFunctionDefinitionContext extends OrcRuleContext {
		public FunctionDefinitionContext functionDefinition() {
			return getRuleContext(FunctionDefinitionContext.class,0);
		}
		public TerminalNode Static() { return getToken(OrcParser.Static, 0); }
		public ExternFunctionDeclarationContext externFunctionDeclaration() {
			return getRuleContext(ExternFunctionDeclarationContext.class,0);
		}
		public GlobalFunctionDefinitionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_globalFunctionDefinition; }
	}

	public final GlobalFunctionDefinitionContext globalFunctionDefinition() throws RecognitionException {
		GlobalFunctionDefinitionContext _localctx = new GlobalFunctionDefinitionContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_globalFunctionDefinition);
		int _la;
		try {
			setState(706);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,75,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(699);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(698);
					match(Static);
					}
				}

				setState(701);
				functionDefinition();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(703);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(702);
					match(Static);
					}
				}

				setState(705);
				externFunctionDeclaration();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class GlobalVarDeclarationContext extends OrcRuleContext {
		public VarDeclarationContext varDeclaration() {
			return getRuleContext(VarDeclarationContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public GlobalVarDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_globalVarDeclaration; }
	}

	public final GlobalVarDeclarationContext globalVarDeclaration() throws RecognitionException {
		GlobalVarDeclarationContext _localctx = new GlobalVarDeclarationContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_globalVarDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(708);
			varDeclaration();
			setState(709);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExternFunctionDeclarationContext extends OrcRuleContext {
		public TerminalNode Extern() { return getToken(OrcParser.Extern, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public ArgumentsDeclarationContext argumentsDeclaration() {
			return getRuleContext(ArgumentsDeclarationContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ExternFunctionDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_externFunctionDeclaration; }
	}

	public final ExternFunctionDeclarationContext externFunctionDeclaration() throws RecognitionException {
		ExternFunctionDeclarationContext _localctx = new ExternFunctionDeclarationContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_externFunctionDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(711);
			match(Extern);
			setState(712);
			type();
			setState(713);
			match(Id);
			setState(714);
			argumentsDeclaration();
			setState(715);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ImportStatementContext extends OrcRuleContext {
		public TerminalNode Import() { return getToken(OrcParser.Import, 0); }
		public TerminalNode From() { return getToken(OrcParser.From, 0); }
		public TerminalNode StringLiteral() { return getToken(OrcParser.StringLiteral, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ImportStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_importStatement; }
	}

	public final ImportStatementContext importStatement() throws RecognitionException {
		ImportStatementContext _localctx = new ImportStatementContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_importStatement);
		try {
			setState(727);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Import:
				enterOuterAlt(_localctx, 1);
				{
				setState(717);
				match(Import);
				setState(718);
				match(T__12);
				setState(719);
				match(From);
				setState(720);
				match(StringLiteral);
				setState(721);
				eos();
				}
				break;
			case T__66:
				enterOuterAlt(_localctx, 2);
				{
				setState(722);
				match(T__66);
				setState(723);
				match(T__12);
				setState(724);
				match(From);
				setState(725);
				match(StringLiteral);
				setState(726);
				eos();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IncludeStatementContext extends OrcRuleContext {
		public IncludePathCharactersContext includePathCharacters() {
			return getRuleContext(IncludePathCharactersContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public IncludeStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_includeStatement; }
	}

	public final IncludeStatementContext includeStatement() throws RecognitionException {
		IncludeStatementContext _localctx = new IncludeStatementContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_includeStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(729);
			match(T__67);
			setState(730);
			includePathCharacters();
			setState(731);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IncludePathCharactersContext extends OrcRuleContext {
		public TerminalNode StringLiteral() { return getToken(OrcParser.StringLiteral, 0); }
		public IncludePathCharactersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_includePathCharacters; }
	}

	public final IncludePathCharactersContext includePathCharacters() throws RecognitionException {
		IncludePathCharactersContext _localctx = new IncludePathCharactersContext(_ctx, getState());
		enterRule(_localctx, 110, RULE_includePathCharacters);
		int _la;
		try {
			setState(742);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__23:
				enterOuterAlt(_localctx, 1);
				{
				setState(733);
				match(T__23);
				setState(737);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -33554434L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 4503599627370495L) != 0)) {
					{
					{
					setState(734);
					_la = _input.LA(1);
					if ( _la <= 0 || (_la==T__24) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					}
					}
					setState(739);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(740);
				match(T__24);
				}
				break;
			case StringLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(741);
				match(StringLiteral);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PackageStatementContext extends OrcRuleContext {
		public TerminalNode Id() { return getToken(OrcParser.Id, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public PackageStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_packageStatement; }
	}

	public final PackageStatementContext packageStatement() throws RecognitionException {
		PackageStatementContext _localctx = new PackageStatementContext(_ctx, getState());
		enterRule(_localctx, 112, RULE_packageStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(744);
			match(T__68);
			setState(745);
			match(Id);
			setState(746);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LiteralContext extends OrcRuleContext {
		public TerminalNode NullLiteral() { return getToken(OrcParser.NullLiteral, 0); }
		public TerminalNode BooleanLiteral() { return getToken(OrcParser.BooleanLiteral, 0); }
		public TerminalNode DecimalLiteral() { return getToken(OrcParser.DecimalLiteral, 0); }
		public TerminalNode HexIntegerLiteral() { return getToken(OrcParser.HexIntegerLiteral, 0); }
		public TerminalNode OctalIntegerLiteral() { return getToken(OrcParser.OctalIntegerLiteral, 0); }
		public TerminalNode BinaryIntegerLiteral() { return getToken(OrcParser.BinaryIntegerLiteral, 0); }
		public TerminalNode StringLiteral() { return getToken(OrcParser.StringLiteral, 0); }
		public TerminalNode CharLiteral() { return getToken(OrcParser.CharLiteral, 0); }
		public LiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal; }
	}

	public final LiteralContext literal() throws RecognitionException {
		LiteralContext _localctx = new LiteralContext(_ctx, getState());
		enterRule(_localctx, 114, RULE_literal);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(748);
			_la = _input.LA(1);
			if ( !(((((_la - 102)) & ~0x3f) == 0 && ((1L << (_la - 102)) & 255L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class EosContext extends OrcRuleContext {
		public TerminalNode EOF() { return getToken(OrcParser.EOF, 0); }
		public EosContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_eos; }
	}

	public final EosContext eos() throws RecognitionException {
		EosContext _localctx = new EosContext(_ctx, getState());
		enterRule(_localctx, 116, RULE_eos);
		try {
			setState(754);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,79,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(750);
				match(T__50);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(751);
				match(EOF);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(752);
				if (!(this->lineTerminatorAhead())) throw new FailedPredicateException(this, "this->lineTerminatorAhead()");
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(753);
				if (!(this->closeBrace())) throw new FailedPredicateException(this, "this->closeBrace()");
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 5:
			return singleExpression_sempred((SingleExpressionContext)_localctx, predIndex);
		case 58:
			return eos_sempred((EosContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean singleExpression_sempred(SingleExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 21);
		case 1:
			return precpred(_ctx, 20);
		case 2:
			return precpred(_ctx, 19);
		case 3:
			return precpred(_ctx, 18);
		case 4:
			return precpred(_ctx, 17);
		case 5:
			return precpred(_ctx, 16);
		case 6:
			return precpred(_ctx, 15);
		case 7:
			return precpred(_ctx, 14);
		case 8:
			return precpred(_ctx, 13);
		case 9:
			return precpred(_ctx, 12);
		case 10:
			return precpred(_ctx, 11);
		case 11:
			return precpred(_ctx, 10);
		case 12:
			return precpred(_ctx, 9);
		case 13:
			return precpred(_ctx, 7);
		case 14:
			return precpred(_ctx, 6);
		case 15:
			return precpred(_ctx, 36);
		case 16:
			return precpred(_ctx, 35);
		case 17:
			return precpred(_ctx, 34);
		case 18:
			return precpred(_ctx, 32);
		case 19:
			return precpred(_ctx, 31);
		}
		return true;
	}
	private boolean eos_sempred(EosContext _localctx, int predIndex) {
		switch (predIndex) {
		case 20:
			return this->lineTerminatorAhead();
		case 21:
			return this->closeBrace();
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001s\u02f5\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007\u0018"+
		"\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007\u001b"+
		"\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002\u001e\u0007\u001e"+
		"\u0002\u001f\u0007\u001f\u0002 \u0007 \u0002!\u0007!\u0002\"\u0007\"\u0002"+
		"#\u0007#\u0002$\u0007$\u0002%\u0007%\u0002&\u0007&\u0002\'\u0007\'\u0002"+
		"(\u0007(\u0002)\u0007)\u0002*\u0007*\u0002+\u0007+\u0002,\u0007,\u0002"+
		"-\u0007-\u0002.\u0007.\u0002/\u0007/\u00020\u00070\u00021\u00071\u0002"+
		"2\u00072\u00023\u00073\u00024\u00074\u00025\u00075\u00026\u00076\u0002"+
		"7\u00077\u00028\u00078\u00029\u00079\u0002:\u0007:\u0001\u0000\u0005\u0000"+
		"x\b\u0000\n\u0000\f\u0000{\t\u0000\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0003\u0001\u0087\b\u0001\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0005\u0002\u008d\b\u0002\n\u0002\f\u0002\u0090\t\u0002\u0001"+
		"\u0002\u0003\u0002\u0093\b\u0002\u0003\u0002\u0095\b\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0005\u0003\u009c\b\u0003"+
		"\n\u0003\f\u0003\u009f\t\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0003"+
		"\u0004\u00a4\b\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0003\u0005\u00cb\b\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0003\u0005\u010c\b\u0005\u0001\u0005\u0005\u0005\u010f"+
		"\b\u0005\n\u0005\f\u0005\u0112\t\u0005\u0001\u0006\u0001\u0006\u0001\u0007"+
		"\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001\b\u0005\b\u011c\b\b\n\b\f\b"+
		"\u011f\t\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0003\t\u0126\b\t\u0001"+
		"\t\u0001\t\u0001\t\u0001\t\u0001\t\u0003\t\u012d\b\t\u0001\n\u0001\n\u0001"+
		"\n\u0001\n\u0001\u000b\u0003\u000b\u0134\b\u000b\u0001\u000b\u0001\u000b"+
		"\u0001\u000b\u0003\u000b\u0139\b\u000b\u0001\u000b\u0001\u000b\u0003\u000b"+
		"\u013d\b\u000b\u0001\u000b\u0003\u000b\u0140\b\u000b\u0001\u000b\u0003"+
		"\u000b\u0143\b\u000b\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0001\f\u0001\f\u0001\f\u0003\f\u0158\b\f\u0001\r\u0001\r\u0001\r\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001"+
		"\u000f\u0001\u0010\u0001\u0010\u0003\u0010\u0166\b\u0010\u0001\u0010\u0001"+
		"\u0010\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0003\u0012\u017c\b\u0012\u0001\u0013\u0003\u0013\u017f\b\u0013"+
		"\u0001\u0013\u0001\u0013\u0003\u0013\u0183\b\u0013\u0001\u0013\u0001\u0013"+
		"\u0003\u0013\u0187\b\u0013\u0001\u0014\u0001\u0014\u0003\u0014\u018b\b"+
		"\u0014\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0005\u0015\u0191"+
		"\b\u0015\n\u0015\f\u0015\u0194\t\u0015\u0001\u0016\u0001\u0016\u0003\u0016"+
		"\u0198\b\u0016\u0001\u0016\u0001\u0016\u0003\u0016\u019c\b\u0016\u0001"+
		"\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001"+
		"\u0017\u0005\u0017\u01a5\b\u0017\n\u0017\f\u0017\u01a8\t\u0017\u0001\u0017"+
		"\u0001\u0017\u0003\u0017\u01ac\b\u0017\u0001\u0018\u0001\u0018\u0001\u0018"+
		"\u0004\u0018\u01b1\b\u0018\u000b\u0018\f\u0018\u01b2\u0001\u0018\u0003"+
		"\u0018\u01b6\b\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0003"+
		"\u0018\u01bc\b\u0018\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u0019\u0003"+
		"\u0019\u01c2\b\u0019\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u001a\u0001"+
		"\u001a\u0001\u001a\u0001\u001b\u0001\u001b\u0005\u001b\u01cc\b\u001b\n"+
		"\u001b\f\u001b\u01cf\t\u001b\u0001\u001b\u0001\u001b\u0001\u001c\u0003"+
		"\u001c\u01d4\b\u001c\u0001\u001c\u0001\u001c\u0003\u001c\u01d8\b\u001c"+
		"\u0001\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0003\u001c\u01de\b\u001c"+
		"\u0001\u001c\u0003\u001c\u01e1\b\u001c\u0001\u001c\u0003\u001c\u01e4\b"+
		"\u001c\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001e\u0001"+
		"\u001e\u0003\u001e\u01ec\b\u001e\u0001\u001f\u0001\u001f\u0001\u001f\u0001"+
		"\u001f\u0001\u001f\u0001\u001f\u0001\u001f\u0001 \u0001 \u0001 \u0005"+
		" \u01f8\b \n \f \u01fb\t \u0001!\u0001!\u0001\"\u0003\"\u0200\b\"\u0001"+
		"\"\u0001\"\u0003\"\u0204\b\"\u0001\"\u0003\"\u0207\b\"\u0001\"\u0005\""+
		"\u020a\b\"\n\"\f\"\u020d\t\"\u0001\"\u0001\"\u0005\"\u0211\b\"\n\"\f\""+
		"\u0214\t\"\u0004\"\u0216\b\"\u000b\"\f\"\u0217\u0001#\u0003#\u021b\b#"+
		"\u0001#\u0001#\u0001#\u0001$\u0001$\u0001$\u0001$\u0001$\u0001$\u0001"+
		"$\u0001$\u0001$\u0001$\u0001$\u0001$\u0001$\u0001$\u0001$\u0001$\u0001"+
		"$\u0001$\u0001$\u0001$\u0001$\u0001$\u0001$\u0003$\u0237\b$\u0001%\u0001"+
		"%\u0001%\u0001%\u0001%\u0001%\u0005%\u023f\b%\n%\f%\u0242\t%\u0001%\u0003"+
		"%\u0245\b%\u0001%\u0001%\u0001%\u0001&\u0001&\u0001&\u0003&\u024d\b&\u0001"+
		"\'\u0001\'\u0001\'\u0001\'\u0001(\u0001(\u0005(\u0255\b(\n(\f(\u0258\t"+
		"(\u0001(\u0001(\u0001)\u0001)\u0003)\u025e\b)\u0001)\u0001)\u0001)\u0003"+
		")\u0263\b)\u0001)\u0001)\u0001)\u0001*\u0001*\u0001*\u0005*\u026b\b*\n"+
		"*\f*\u026e\t*\u0001*\u0001*\u0001+\u0001+\u0001+\u0003+\u0275\b+\u0001"+
		"+\u0003+\u0278\b+\u0001+\u0001+\u0001+\u0001+\u0003+\u027e\b+\u0001+\u0001"+
		"+\u0003+\u0282\b+\u0001,\u0001,\u0003,\u0286\b,\u0001-\u0001-\u0001-\u0001"+
		".\u0001.\u0003.\u028d\b.\u0001.\u0003.\u0290\b.\u0001/\u0001/\u0001/\u0001"+
		"/\u0005/\u0296\b/\n/\f/\u0299\t/\u0003/\u029b\b/\u0001/\u0003/\u029e\b"+
		"/\u0001/\u0001/\u0003/\u02a2\b/\u00010\u00010\u00010\u00040\u02a7\b0\u000b"+
		"0\f0\u02a8\u00010\u00030\u02ac\b0\u00010\u00010\u00010\u00050\u02b1\b"+
		"0\n0\f0\u02b4\t0\u00011\u00011\u00011\u00011\u00011\u00012\u00032\u02bc"+
		"\b2\u00012\u00012\u00032\u02c0\b2\u00012\u00032\u02c3\b2\u00013\u0001"+
		"3\u00013\u00014\u00014\u00014\u00014\u00014\u00014\u00015\u00015\u0001"+
		"5\u00015\u00015\u00015\u00015\u00015\u00015\u00015\u00035\u02d8\b5\u0001"+
		"6\u00016\u00016\u00016\u00017\u00017\u00057\u02e0\b7\n7\f7\u02e3\t7\u0001"+
		"7\u00017\u00037\u02e7\b7\u00018\u00018\u00018\u00018\u00019\u00019\u0001"+
		":\u0001:\u0001:\u0001:\u0003:\u02f3\b:\u0001:\u0000\u0001\n;\u0000\u0002"+
		"\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e"+
		" \"$&(*,.02468:<>@BDFHJLNPRTVXZ\\^`bdfhjlnprt\u0000\u000b\u0002\u0000"+
		"\r\r\u0012\u0013\u0001\u0000\u000e\u000f\u0001\u0000\u0015\u0017\u0001"+
		"\u0000\u0018\u001b\u0001\u0000\u001c\u001f\u0001\u0000\t\n\u0001\u0000"+
		"&2\u0002\u0000\t\t\u0010\u0010\u0002\u000079__\u0001\u0000\u0019\u0019"+
		"\u0001\u0000fm\u034f\u0000y\u0001\u0000\u0000\u0000\u0002\u0086\u0001"+
		"\u0000\u0000\u0000\u0004\u0088\u0001\u0000\u0000\u0000\u0006\u0098\u0001"+
		"\u0000\u0000\u0000\b\u00a0\u0001\u0000\u0000\u0000\n\u00ca\u0001\u0000"+
		"\u0000\u0000\f\u0113\u0001\u0000\u0000\u0000\u000e\u0115\u0001\u0000\u0000"+
		"\u0000\u0010\u0117\u0001\u0000\u0000\u0000\u0012\u012c\u0001\u0000\u0000"+
		"\u0000\u0014\u012e\u0001\u0000\u0000\u0000\u0016\u0142\u0001\u0000\u0000"+
		"\u0000\u0018\u0157\u0001\u0000\u0000\u0000\u001a\u0159\u0001\u0000\u0000"+
		"\u0000\u001c\u015c\u0001\u0000\u0000\u0000\u001e\u015f\u0001\u0000\u0000"+
		"\u0000 \u0163\u0001\u0000\u0000\u0000\"\u0169\u0001\u0000\u0000\u0000"+
		"$\u017b\u0001\u0000\u0000\u0000&\u017e\u0001\u0000\u0000\u0000(\u018a"+
		"\u0001\u0000\u0000\u0000*\u018c\u0001\u0000\u0000\u0000,\u0195\u0001\u0000"+
		"\u0000\u0000.\u019d\u0001\u0000\u0000\u00000\u01bb\u0001\u0000\u0000\u0000"+
		"2\u01bd\u0001\u0000\u0000\u00004\u01c6\u0001\u0000\u0000\u00006\u01c9"+
		"\u0001\u0000\u0000\u00008\u01e3\u0001\u0000\u0000\u0000:\u01e5\u0001\u0000"+
		"\u0000\u0000<\u01e9\u0001\u0000\u0000\u0000>\u01ed\u0001\u0000\u0000\u0000"+
		"@\u01f4\u0001\u0000\u0000\u0000B\u01fc\u0001\u0000\u0000\u0000D\u01ff"+
		"\u0001\u0000\u0000\u0000F\u021a\u0001\u0000\u0000\u0000H\u0236\u0001\u0000"+
		"\u0000\u0000J\u0238\u0001\u0000\u0000\u0000L\u0249\u0001\u0000\u0000\u0000"+
		"N\u024e\u0001\u0000\u0000\u0000P\u0252\u0001\u0000\u0000\u0000R\u025b"+
		"\u0001\u0000\u0000\u0000T\u0267\u0001\u0000\u0000\u0000V\u0281\u0001\u0000"+
		"\u0000\u0000X\u0285\u0001\u0000\u0000\u0000Z\u0287\u0001\u0000\u0000\u0000"+
		"\\\u028f\u0001\u0000\u0000\u0000^\u02a1\u0001\u0000\u0000\u0000`\u02a3"+
		"\u0001\u0000\u0000\u0000b\u02b5\u0001\u0000\u0000\u0000d\u02c2\u0001\u0000"+
		"\u0000\u0000f\u02c4\u0001\u0000\u0000\u0000h\u02c7\u0001\u0000\u0000\u0000"+
		"j\u02d7\u0001\u0000\u0000\u0000l\u02d9\u0001\u0000\u0000\u0000n\u02e6"+
		"\u0001\u0000\u0000\u0000p\u02e8\u0001\u0000\u0000\u0000r\u02ec\u0001\u0000"+
		"\u0000\u0000t\u02f2\u0001\u0000\u0000\u0000vx\u0003\u0002\u0001\u0000"+
		"wv\u0001\u0000\u0000\u0000x{\u0001\u0000\u0000\u0000yw\u0001\u0000\u0000"+
		"\u0000yz\u0001\u0000\u0000\u0000z\u0001\u0001\u0000\u0000\u0000{y\u0001"+
		"\u0000\u0000\u0000|\u0087\u0003p8\u0000}\u0087\u0003l6\u0000~\u0087\u0003"+
		"j5\u0000\u007f\u0087\u0003\u0010\b\u0000\u0080\u0087\u0003J%\u0000\u0081"+
		"\u0087\u0003R)\u0000\u0082\u0087\u0003N\'\u0000\u0083\u0087\u0003f3\u0000"+
		"\u0084\u0087\u0003d2\u0000\u0085\u0087\u0003\u000e\u0007\u0000\u0086|"+
		"\u0001\u0000\u0000\u0000\u0086}\u0001\u0000\u0000\u0000\u0086~\u0001\u0000"+
		"\u0000\u0000\u0086\u007f\u0001\u0000\u0000\u0000\u0086\u0080\u0001\u0000"+
		"\u0000\u0000\u0086\u0081\u0001\u0000\u0000\u0000\u0086\u0082\u0001\u0000"+
		"\u0000\u0000\u0086\u0083\u0001\u0000\u0000\u0000\u0086\u0084\u0001\u0000"+
		"\u0000\u0000\u0086\u0085\u0001\u0000\u0000\u0000\u0087\u0003\u0001\u0000"+
		"\u0000\u0000\u0088\u0094\u0005\u0001\u0000\u0000\u0089\u008e\u0003\n\u0005"+
		"\u0000\u008a\u008b\u0005\u0002\u0000\u0000\u008b\u008d\u0003\n\u0005\u0000"+
		"\u008c\u008a\u0001\u0000\u0000\u0000\u008d\u0090\u0001\u0000\u0000\u0000"+
		"\u008e\u008c\u0001\u0000\u0000\u0000\u008e\u008f\u0001\u0000\u0000\u0000"+
		"\u008f\u0092\u0001\u0000\u0000\u0000\u0090\u008e\u0001\u0000\u0000\u0000"+
		"\u0091\u0093\u0005\u0002\u0000\u0000\u0092\u0091\u0001\u0000\u0000\u0000"+
		"\u0092\u0093\u0001\u0000\u0000\u0000\u0093\u0095\u0001\u0000\u0000\u0000"+
		"\u0094\u0089\u0001\u0000\u0000\u0000\u0094\u0095\u0001\u0000\u0000\u0000"+
		"\u0095\u0096\u0001\u0000\u0000\u0000\u0096\u0097\u0005\u0003\u0000\u0000"+
		"\u0097\u0005\u0001\u0000\u0000\u0000\u0098\u009d\u0003\n\u0005\u0000\u0099"+
		"\u009a\u0005\u0002\u0000\u0000\u009a\u009c\u0003\n\u0005\u0000\u009b\u0099"+
		"\u0001\u0000\u0000\u0000\u009c\u009f\u0001\u0000\u0000\u0000\u009d\u009b"+
		"\u0001\u0000\u0000\u0000\u009d\u009e\u0001\u0000\u0000\u0000\u009e\u0007"+
		"\u0001\u0000\u0000\u0000\u009f\u009d\u0001\u0000\u0000\u0000\u00a0\u00a1"+
		"\u0005\u0004\u0000\u0000\u00a1\u00a3\u00038\u001c\u0000\u00a2\u00a4\u0005"+
		"n\u0000\u0000\u00a3\u00a2\u0001\u0000\u0000\u0000\u00a3\u00a4\u0001\u0000"+
		"\u0000\u0000\u00a4\u00a5\u0001\u0000\u0000\u0000\u00a5\u00a6\u0003^/\u0000"+
		"\u00a6\u00a7\u00036\u001b\u0000\u00a7\t\u0001\u0000\u0000\u0000\u00a8"+
		"\u00a9\u0006\u0005\uffff\uffff\u0000\u00a9\u00cb\u0003\b\u0004\u0000\u00aa"+
		"\u00ab\u0005K\u0000\u0000\u00ab\u00ac\u0005n\u0000\u0000\u00ac\u00cb\u0003"+
		"\u0004\u0002\u0000\u00ad\u00ae\u0005\f\u0000\u0000\u00ae\u00cb\u0003\n"+
		"\u0005\u001d\u00af\u00b0\u0005\r\u0000\u0000\u00b0\u00cb\u0003\n\u0005"+
		"\u001c\u00b1\u00b2\u0005\u0005\u0000\u0000\u00b2\u00cb\u0003\n\u0005\u001b"+
		"\u00b3\u00b4\u0005\u0006\u0000\u0000\u00b4\u00cb\u0003\n\u0005\u001a\u00b5"+
		"\u00b6\u0005\u000e\u0000\u0000\u00b6\u00cb\u0003\n\u0005\u0019\u00b7\u00b8"+
		"\u0005\u000f\u0000\u0000\u00b8\u00cb\u0003\n\u0005\u0018\u00b9\u00ba\u0005"+
		"\u0010\u0000\u0000\u00ba\u00cb\u0003\n\u0005\u0017\u00bb\u00bc\u0005\u0011"+
		"\u0000\u0000\u00bc\u00cb\u0003\n\u0005\u0016\u00bd\u00be\u0005\u0001\u0000"+
		"\u0000\u00be\u00bf\u00038\u001c\u0000\u00bf\u00c0\u0005\u0003\u0000\u0000"+
		"\u00c0\u00c1\u0003\n\u0005\b\u00c1\u00cb\u0001\u0000\u0000\u0000\u00c2"+
		"\u00cb\u0005S\u0000\u0000\u00c3\u00cb\u0005n\u0000\u0000\u00c4\u00cb\u0005"+
		"]\u0000\u0000\u00c5\u00cb\u0003r9\u0000\u00c6\u00c7\u0005\u0001\u0000"+
		"\u0000\u00c7\u00c8\u0003\u0006\u0003\u0000\u00c8\u00c9\u0005\u0003\u0000"+
		"\u0000\u00c9\u00cb\u0001\u0000\u0000\u0000\u00ca\u00a8\u0001\u0000\u0000"+
		"\u0000\u00ca\u00aa\u0001\u0000\u0000\u0000\u00ca\u00ad\u0001\u0000\u0000"+
		"\u0000\u00ca\u00af\u0001\u0000\u0000\u0000\u00ca\u00b1\u0001\u0000\u0000"+
		"\u0000\u00ca\u00b3\u0001\u0000\u0000\u0000\u00ca\u00b5\u0001\u0000\u0000"+
		"\u0000\u00ca\u00b7\u0001\u0000\u0000\u0000\u00ca\u00b9\u0001\u0000\u0000"+
		"\u0000\u00ca\u00bb\u0001\u0000\u0000\u0000\u00ca\u00bd\u0001\u0000\u0000"+
		"\u0000\u00ca\u00c2\u0001\u0000\u0000\u0000\u00ca\u00c3\u0001\u0000\u0000"+
		"\u0000\u00ca\u00c4\u0001\u0000\u0000\u0000\u00ca\u00c5\u0001\u0000\u0000"+
		"\u0000\u00ca\u00c6\u0001\u0000\u0000\u0000\u00cb\u0110\u0001\u0000\u0000"+
		"\u0000\u00cc\u00cd\n\u0015\u0000\u0000\u00cd\u00ce\u0007\u0000\u0000\u0000"+
		"\u00ce\u010f\u0003\n\u0005\u0016\u00cf\u00d0\n\u0014\u0000\u0000\u00d0"+
		"\u00d1\u0007\u0001\u0000\u0000\u00d1\u010f\u0003\n\u0005\u0015\u00d2\u00d3"+
		"\n\u0013\u0000\u0000\u00d3\u00d4\u0005\u0014\u0000\u0000\u00d4\u010f\u0003"+
		"\n\u0005\u0014\u00d5\u00d6\n\u0012\u0000\u0000\u00d6\u00d7\u0007\u0002"+
		"\u0000\u0000\u00d7\u010f\u0003\n\u0005\u0013\u00d8\u00d9\n\u0011\u0000"+
		"\u0000\u00d9\u00da\u0007\u0003\u0000\u0000\u00da\u010f\u0003\n\u0005\u0012"+
		"\u00db\u00dc\n\u0010\u0000\u0000\u00dc\u00dd\u0005H\u0000\u0000\u00dd"+
		"\u010f\u0003\n\u0005\u0011\u00de\u00df\n\u000f\u0000\u0000\u00df\u00e0"+
		"\u0007\u0004\u0000\u0000\u00e0\u010f\u0003\n\u0005\u0010\u00e1\u00e2\n"+
		"\u000e\u0000\u0000\u00e2\u00e3\u0005\f\u0000\u0000\u00e3\u010f\u0003\n"+
		"\u0005\u000f\u00e4\u00e5\n\r\u0000\u0000\u00e5\u00e6\u0005\u0004\u0000"+
		"\u0000\u00e6\u010f\u0003\n\u0005\u000e\u00e7\u00e8\n\f\u0000\u0000\u00e8"+
		"\u00e9\u0005 \u0000\u0000\u00e9\u010f\u0003\n\u0005\r\u00ea\u00eb\n\u000b"+
		"\u0000\u0000\u00eb\u00ec\u0005!\u0000\u0000\u00ec\u010f\u0003\n\u0005"+
		"\f\u00ed\u00ee\n\n\u0000\u0000\u00ee\u00ef\u0005\"\u0000\u0000\u00ef\u010f"+
		"\u0003\n\u0005\u000b\u00f0\u00f1\n\t\u0000\u0000\u00f1\u00f2\u0005#\u0000"+
		"\u0000\u00f2\u00f3\u0003\n\u0005\u0000\u00f3\u00f4\u0005$\u0000\u0000"+
		"\u00f4\u00f5\u0003\n\u0005\n\u00f5\u010f\u0001\u0000\u0000\u0000\u00f6"+
		"\u00f7\n\u0007\u0000\u0000\u00f7\u00f8\u0005%\u0000\u0000\u00f8\u010f"+
		"\u0003\n\u0005\u0007\u00f9\u00fa\n\u0006\u0000\u0000\u00fa\u00fb\u0003"+
		"\f\u0006\u0000\u00fb\u00fc\u0003\n\u0005\u0006\u00fc\u010f\u0001\u0000"+
		"\u0000\u0000\u00fd\u00fe\n$\u0000\u0000\u00fe\u010f\u0003\u0004\u0002"+
		"\u0000\u00ff\u0100\n#\u0000\u0000\u0100\u010f\u0005\u0005\u0000\u0000"+
		"\u0101\u0102\n\"\u0000\u0000\u0102\u010f\u0005\u0006\u0000\u0000\u0103"+
		"\u0104\n \u0000\u0000\u0104\u0105\u0005\u0007\u0000\u0000\u0105\u0106"+
		"\u0003\n\u0005\u0000\u0106\u0107\u0005\b\u0000\u0000\u0107\u010f\u0001"+
		"\u0000\u0000\u0000\u0108\u0109\n\u001f\u0000\u0000\u0109\u010b\u0007\u0005"+
		"\u0000\u0000\u010a\u010c\u0005\u000b\u0000\u0000\u010b\u010a\u0001\u0000"+
		"\u0000\u0000\u010b\u010c\u0001\u0000\u0000\u0000\u010c\u010d\u0001\u0000"+
		"\u0000\u0000\u010d\u010f\u0005n\u0000\u0000\u010e\u00cc\u0001\u0000\u0000"+
		"\u0000\u010e\u00cf\u0001\u0000\u0000\u0000\u010e\u00d2\u0001\u0000\u0000"+
		"\u0000\u010e\u00d5\u0001\u0000\u0000\u0000\u010e\u00d8\u0001\u0000\u0000"+
		"\u0000\u010e\u00db\u0001\u0000\u0000\u0000\u010e\u00de\u0001\u0000\u0000"+
		"\u0000\u010e\u00e1\u0001\u0000\u0000\u0000\u010e\u00e4\u0001\u0000\u0000"+
		"\u0000\u010e\u00e7\u0001\u0000\u0000\u0000\u010e\u00ea\u0001\u0000\u0000"+
		"\u0000\u010e\u00ed\u0001\u0000\u0000\u0000\u010e\u00f0\u0001\u0000\u0000"+
		"\u0000\u010e\u00f6\u0001\u0000\u0000\u0000\u010e\u00f9\u0001\u0000\u0000"+
		"\u0000\u010e\u00fd\u0001\u0000\u0000\u0000\u010e\u00ff\u0001\u0000\u0000"+
		"\u0000\u010e\u0101\u0001\u0000\u0000\u0000\u010e\u0103\u0001\u0000\u0000"+
		"\u0000\u010e\u0108\u0001\u0000\u0000\u0000\u010f\u0112\u0001\u0000\u0000"+
		"\u0000\u0110\u010e\u0001\u0000\u0000\u0000\u0110\u0111\u0001\u0000\u0000"+
		"\u0000\u0111\u000b\u0001\u0000\u0000\u0000\u0112\u0110\u0001\u0000\u0000"+
		"\u0000\u0113\u0114\u0007\u0006\u0000\u0000\u0114\r\u0001\u0000\u0000\u0000"+
		"\u0115\u0116\u00053\u0000\u0000\u0116\u000f\u0001\u0000\u0000\u0000\u0117"+
		"\u0118\u0005X\u0000\u0000\u0118\u0119\u0005n\u0000\u0000\u0119\u011d\u0005"+
		"4\u0000\u0000\u011a\u011c\u0003\u0012\t\u0000\u011b\u011a\u0001\u0000"+
		"\u0000\u0000\u011c\u011f\u0001\u0000\u0000\u0000\u011d\u011b\u0001\u0000"+
		"\u0000\u0000\u011d\u011e\u0001\u0000\u0000\u0000\u011e\u0120\u0001\u0000"+
		"\u0000\u0000\u011f\u011d\u0001\u0000\u0000\u0000\u0120\u0121\u0005o\u0000"+
		"\u0000\u0121\u0011\u0001\u0000\u0000\u0000\u0122\u0123\u00038\u001c\u0000"+
		"\u0123\u0125\u0005n\u0000\u0000\u0124\u0126\u0003\u0014\n\u0000\u0125"+
		"\u0124\u0001\u0000\u0000\u0000\u0125\u0126\u0001\u0000\u0000\u0000\u0126"+
		"\u0127\u0001\u0000\u0000\u0000\u0127\u0128\u0003t:\u0000\u0128\u012d\u0001"+
		"\u0000\u0000\u0000\u0129\u012a\u0003`0\u0000\u012a\u012b\u0003t:\u0000"+
		"\u012b\u012d\u0001\u0000\u0000\u0000\u012c\u0122\u0001\u0000\u0000\u0000"+
		"\u012c\u0129\u0001\u0000\u0000\u0000\u012d\u0013\u0001\u0000\u0000\u0000"+
		"\u012e\u012f\u0005\u0007\u0000\u0000\u012f\u0130\u0005h\u0000\u0000\u0130"+
		"\u0131\u0005\b\u0000\u0000\u0131\u0015\u0001\u0000\u0000\u0000\u0132\u0134"+
		"\u0005b\u0000\u0000\u0133\u0132\u0001\u0000\u0000\u0000\u0133\u0134\u0001"+
		"\u0000\u0000\u0000\u0134\u0135\u0001\u0000\u0000\u0000\u0135\u0136\u0003"+
		"8\u001c\u0000\u0136\u0138\u0005n\u0000\u0000\u0137\u0139\u0003\u0014\n"+
		"\u0000\u0138\u0137\u0001\u0000\u0000\u0000\u0138\u0139\u0001\u0000\u0000"+
		"\u0000\u0139\u013c\u0001\u0000\u0000\u0000\u013a\u013b\u0005%\u0000\u0000"+
		"\u013b\u013d\u0003\n\u0005\u0000\u013c\u013a\u0001\u0000\u0000\u0000\u013c"+
		"\u013d\u0001\u0000\u0000\u0000\u013d\u0143\u0001\u0000\u0000\u0000\u013e"+
		"\u0140\u0005b\u0000\u0000\u013f\u013e\u0001\u0000\u0000\u0000\u013f\u0140"+
		"\u0001\u0000\u0000\u0000\u0140\u0141\u0001\u0000\u0000\u0000\u0141\u0143"+
		"\u0003`0\u0000\u0142\u0133\u0001\u0000\u0000\u0000\u0142\u013f\u0001\u0000"+
		"\u0000\u0000\u0143\u0017\u0001\u0000\u0000\u0000\u0144\u0145\u0003\b\u0004"+
		"\u0000\u0145\u0146\u0003t:\u0000\u0146\u0158\u0001\u0000\u0000\u0000\u0147"+
		"\u0148\u0003\u0016\u000b\u0000\u0148\u0149\u0003t:\u0000\u0149\u0158\u0001"+
		"\u0000\u0000\u0000\u014a\u0158\u0003\"\u0011\u0000\u014b\u0158\u00036"+
		"\u001b\u0000\u014c\u0158\u0003\u001a\r\u0000\u014d\u0158\u0003\u001c\u000e"+
		"\u0000\u014e\u0158\u0003\u001e\u000f\u0000\u014f\u0158\u0003.\u0017\u0000"+
		"\u0150\u0158\u0003 \u0010\u0000\u0151\u0158\u0003$\u0012\u0000\u0152\u0158"+
		"\u00030\u0018\u0000\u0153\u0154\u0003\n\u0005\u0000\u0154\u0155\u0003"+
		"t:\u0000\u0155\u0158\u0001\u0000\u0000\u0000\u0156\u0158\u0003\u000e\u0007"+
		"\u0000\u0157\u0144\u0001\u0000\u0000\u0000\u0157\u0147\u0001\u0000\u0000"+
		"\u0000\u0157\u014a\u0001\u0000\u0000\u0000\u0157\u014b\u0001\u0000\u0000"+
		"\u0000\u0157\u014c\u0001\u0000\u0000\u0000\u0157\u014d\u0001\u0000\u0000"+
		"\u0000\u0157\u014e\u0001\u0000\u0000\u0000\u0157\u014f\u0001\u0000\u0000"+
		"\u0000\u0157\u0150\u0001\u0000\u0000\u0000\u0157\u0151\u0001\u0000\u0000"+
		"\u0000\u0157\u0152\u0001\u0000\u0000\u0000\u0157\u0153\u0001\u0000\u0000"+
		"\u0000\u0157\u0156\u0001\u0000\u0000\u0000\u0158\u0019\u0001\u0000\u0000"+
		"\u0000\u0159\u015a\u0005P\u0000\u0000\u015a\u015b\u0003t:\u0000\u015b"+
		"\u001b\u0001\u0000\u0000\u0000\u015c\u015d\u0005F\u0000\u0000\u015d\u015e"+
		"\u0003t:\u0000\u015e\u001d\u0001\u0000\u0000\u0000\u015f\u0160\u0005U"+
		"\u0000\u0000\u0160\u0161\u0003\n\u0005\u0000\u0161\u0162\u0003t:\u0000"+
		"\u0162\u001f\u0001\u0000\u0000\u0000\u0163\u0165\u0005N\u0000\u0000\u0164"+
		"\u0166\u0003\n\u0005\u0000\u0165\u0164\u0001\u0000\u0000\u0000\u0165\u0166"+
		"\u0001\u0000\u0000\u0000\u0166\u0167\u0001\u0000\u0000\u0000\u0167\u0168"+
		"\u0003t:\u0000\u0168!\u0001\u0000\u0000\u0000\u0169\u016a\u0003\n\u0005"+
		"\u0000\u016a\u016b\u0007\u0007\u0000\u0000\u016b\u016c\u00036\u001b\u0000"+
		"\u016c#\u0001\u0000\u0000\u0000\u016d\u016e\u0005R\u0000\u0000\u016e\u016f"+
		"\u0003\n\u0005\u0000\u016f\u0170\u00036\u001b\u0000\u0170\u017c\u0001"+
		"\u0000\u0000\u0000\u0171\u0172\u0005Q\u0000\u0000\u0172\u0173\u0005\u0001"+
		"\u0000\u0000\u0173\u0174\u0003&\u0013\u0000\u0174\u0175\u0005\u0003\u0000"+
		"\u0000\u0175\u0176\u00036\u001b\u0000\u0176\u017c\u0001\u0000\u0000\u0000"+
		"\u0177\u0178\u0005Q\u0000\u0000\u0178\u0179\u0003&\u0013\u0000\u0179\u017a"+
		"\u00036\u001b\u0000\u017a\u017c\u0001\u0000\u0000\u0000\u017b\u016d\u0001"+
		"\u0000\u0000\u0000\u017b\u0171\u0001\u0000\u0000\u0000\u017b\u0177\u0001"+
		"\u0000\u0000\u0000\u017c%\u0001\u0000\u0000\u0000\u017d\u017f\u0003(\u0014"+
		"\u0000\u017e\u017d\u0001\u0000\u0000\u0000\u017e\u017f\u0001\u0000\u0000"+
		"\u0000\u017f\u0180\u0001\u0000\u0000\u0000\u0180\u0182\u00053\u0000\u0000"+
		"\u0181\u0183\u0003\n\u0005\u0000\u0182\u0181\u0001\u0000\u0000\u0000\u0182"+
		"\u0183\u0001\u0000\u0000\u0000\u0183\u0184\u0001\u0000\u0000\u0000\u0184"+
		"\u0186\u00053\u0000\u0000\u0185\u0187\u0003\n\u0005\u0000\u0186\u0185"+
		"\u0001\u0000\u0000\u0000\u0186\u0187\u0001\u0000\u0000\u0000\u0187\'\u0001"+
		"\u0000\u0000\u0000\u0188\u018b\u0003*\u0015\u0000\u0189\u018b\u0003\n"+
		"\u0005\u0000\u018a\u0188\u0001\u0000\u0000\u0000\u018a\u0189\u0001\u0000"+
		"\u0000\u0000\u018b)\u0001\u0000\u0000\u0000\u018c\u018d\u00038\u001c\u0000"+
		"\u018d\u0192\u0003,\u0016\u0000\u018e\u018f\u0005\u0002\u0000\u0000\u018f"+
		"\u0191\u0003,\u0016\u0000\u0190\u018e\u0001\u0000\u0000\u0000\u0191\u0194"+
		"\u0001\u0000\u0000\u0000\u0192\u0190\u0001\u0000\u0000\u0000\u0192\u0193"+
		"\u0001\u0000\u0000\u0000\u0193+\u0001\u0000\u0000\u0000\u0194\u0192\u0001"+
		"\u0000\u0000\u0000\u0195\u0197\u0005n\u0000\u0000\u0196\u0198\u0003\u0014"+
		"\n\u0000\u0197\u0196\u0001\u0000\u0000\u0000\u0197\u0198\u0001\u0000\u0000"+
		"\u0000\u0198\u019b\u0001\u0000\u0000\u0000\u0199\u019a\u0005%\u0000\u0000"+
		"\u019a\u019c\u0003\n\u0005\u0000\u019b\u0199\u0001\u0000\u0000\u0000\u019b"+
		"\u019c\u0001\u0000\u0000\u0000\u019c-\u0001\u0000\u0000\u0000\u019d\u019e"+
		"\u0005T\u0000\u0000\u019e\u019f\u0003\n\u0005\u0000\u019f\u01a6\u0003"+
		"6\u001b\u0000\u01a0\u01a1\u00055\u0000\u0000\u01a1\u01a2\u0003\n\u0005"+
		"\u0000\u01a2\u01a3\u00036\u001b\u0000\u01a3\u01a5\u0001\u0000\u0000\u0000"+
		"\u01a4\u01a0\u0001\u0000\u0000\u0000\u01a5\u01a8\u0001\u0000\u0000\u0000"+
		"\u01a6\u01a4\u0001\u0000\u0000\u0000\u01a6\u01a7\u0001\u0000\u0000\u0000"+
		"\u01a7\u01ab\u0001\u0000\u0000\u0000\u01a8\u01a6\u0001\u0000\u0000\u0000"+
		"\u01a9\u01aa\u0005J\u0000\u0000\u01aa\u01ac\u00036\u001b\u0000\u01ab\u01a9"+
		"\u0001\u0000\u0000\u0000\u01ab\u01ac\u0001\u0000\u0000\u0000\u01ac/\u0001"+
		"\u0000\u0000\u0000\u01ad\u01ae\u0005V\u0000\u0000\u01ae\u01b0\u00036\u001b"+
		"\u0000\u01af\u01b1\u00032\u0019\u0000\u01b0\u01af\u0001\u0000\u0000\u0000"+
		"\u01b1\u01b2\u0001\u0000\u0000\u0000\u01b2\u01b0\u0001\u0000\u0000\u0000"+
		"\u01b2\u01b3\u0001\u0000\u0000\u0000\u01b3\u01b5\u0001\u0000\u0000\u0000"+
		"\u01b4\u01b6\u00034\u001a\u0000\u01b5\u01b4\u0001\u0000\u0000\u0000\u01b5"+
		"\u01b6\u0001\u0000\u0000\u0000\u01b6\u01bc\u0001\u0000\u0000\u0000\u01b7"+
		"\u01b8\u0005V\u0000\u0000\u01b8\u01b9\u00036\u001b\u0000\u01b9\u01ba\u0003"+
		"4\u001a\u0000\u01ba\u01bc\u0001\u0000\u0000\u0000\u01bb\u01ad\u0001\u0000"+
		"\u0000\u0000\u01bb\u01b7\u0001\u0000\u0000\u0000\u01bc1\u0001\u0000\u0000"+
		"\u0000\u01bd\u01be\u0005L\u0000\u0000\u01be\u01bf\u0005\u0001\u0000\u0000"+
		"\u01bf\u01c1\u0003F#\u0000\u01c0\u01c2\u0005n\u0000\u0000\u01c1\u01c0"+
		"\u0001\u0000\u0000\u0000\u01c1\u01c2\u0001\u0000\u0000\u0000\u01c2\u01c3"+
		"\u0001\u0000\u0000\u0000\u01c3\u01c4\u0005\u0003\u0000\u0000\u01c4\u01c5"+
		"\u00036\u001b\u0000\u01c53\u0001\u0000\u0000\u0000\u01c6\u01c7\u0005M"+
		"\u0000\u0000\u01c7\u01c8\u00036\u001b\u0000\u01c85\u0001\u0000\u0000\u0000"+
		"\u01c9\u01cd\u00054\u0000\u0000\u01ca\u01cc\u0003\u0018\f\u0000\u01cb"+
		"\u01ca\u0001\u0000\u0000\u0000\u01cc\u01cf\u0001\u0000\u0000\u0000\u01cd"+
		"\u01cb\u0001\u0000\u0000\u0000\u01cd\u01ce\u0001\u0000\u0000\u0000\u01ce"+
		"\u01d0\u0001\u0000\u0000\u0000\u01cf\u01cd\u0001\u0000\u0000\u0000\u01d0"+
		"\u01d1\u0005o\u0000\u0000\u01d17\u0001\u0000\u0000\u0000\u01d2\u01d4\u0003"+
		"B!\u0000\u01d3\u01d2\u0001\u0000\u0000\u0000\u01d3\u01d4\u0001\u0000\u0000"+
		"\u0000\u01d4\u01d5\u0001\u0000\u0000\u0000\u01d5\u01d7\u0003H$\u0000\u01d6"+
		"\u01d8\u0003\u0014\n\u0000\u01d7\u01d6\u0001\u0000\u0000\u0000\u01d7\u01d8"+
		"\u0001\u0000\u0000\u0000\u01d8\u01e4\u0001\u0000\u0000\u0000\u01d9\u01e4"+
		"\u0003:\u001d\u0000\u01da\u01e4\u0003D\"\u0000\u01db\u01e4\u0003F#\u0000"+
		"\u01dc\u01de\u0003B!\u0000\u01dd\u01dc\u0001\u0000\u0000\u0000\u01dd\u01de"+
		"\u0001\u0000\u0000\u0000\u01de\u01e0\u0001\u0000\u0000\u0000\u01df\u01e1"+
		"\u0005X\u0000\u0000\u01e0\u01df\u0001\u0000\u0000\u0000\u01e0\u01e1\u0001"+
		"\u0000\u0000\u0000\u01e1\u01e2\u0001\u0000\u0000\u0000\u01e2\u01e4\u0005"+
		"n\u0000\u0000\u01e3\u01d3\u0001\u0000\u0000\u0000\u01e3\u01d9\u0001\u0000"+
		"\u0000\u0000\u01e3\u01da\u0001\u0000\u0000\u0000\u01e3\u01db\u0001\u0000"+
		"\u0000\u0000\u01e3\u01dd\u0001\u0000\u0000\u0000\u01e49\u0001\u0000\u0000"+
		"\u0000\u01e5\u01e6\u0005\u0004\u0000\u0000\u01e6\u01e7\u00038\u001c\u0000"+
		"\u01e7\u01e8\u0003^/\u0000\u01e8;\u0001\u0000\u0000\u0000\u01e9\u01eb"+
		"\u00038\u001c\u0000\u01ea\u01ec\u0005n\u0000\u0000\u01eb\u01ea\u0001\u0000"+
		"\u0000\u0000\u01eb\u01ec\u0001\u0000\u0000\u0000\u01ec=\u0001\u0000\u0000"+
		"\u0000\u01ed\u01ee\u00056\u0000\u0000\u01ee\u01ef\u0005\u0001\u0000\u0000"+
		"\u01ef\u01f0\u0005\u0001\u0000\u0000\u01f0\u01f1\u0005n\u0000\u0000\u01f1"+
		"\u01f2\u0005\u0003\u0000\u0000\u01f2\u01f3\u0005\u0003\u0000\u0000\u01f3"+
		"?\u0001\u0000\u0000\u0000\u01f4\u01f5\u00038\u001c\u0000\u01f5\u01f9\u0003"+
		"^/\u0000\u01f6\u01f8\u0003>\u001f\u0000\u01f7\u01f6\u0001\u0000\u0000"+
		"\u0000\u01f8\u01fb\u0001\u0000\u0000\u0000\u01f9\u01f7\u0001\u0000\u0000"+
		"\u0000\u01f9\u01fa\u0001\u0000\u0000\u0000\u01faA\u0001\u0000\u0000\u0000"+
		"\u01fb\u01f9\u0001\u0000\u0000\u0000\u01fc\u01fd\u0007\b\u0000\u0000\u01fd"+
		"C\u0001\u0000\u0000\u0000\u01fe\u0200\u0003B!\u0000\u01ff\u01fe\u0001"+
		"\u0000\u0000\u0000\u01ff\u0200\u0001\u0000\u0000\u0000\u0200\u0206\u0001"+
		"\u0000\u0000\u0000\u0201\u0207\u0003H$\u0000\u0202\u0204\u0005X\u0000"+
		"\u0000\u0203\u0202\u0001\u0000\u0000\u0000\u0203\u0204\u0001\u0000\u0000"+
		"\u0000\u0204\u0205\u0001\u0000\u0000\u0000\u0205\u0207\u0005n\u0000\u0000"+
		"\u0206\u0201\u0001\u0000\u0000\u0000\u0206\u0203\u0001\u0000\u0000\u0000"+
		"\u0207\u0215\u0001\u0000\u0000\u0000\u0208\u020a\u0003B!\u0000\u0209\u0208"+
		"\u0001\u0000\u0000\u0000\u020a\u020d\u0001\u0000\u0000\u0000\u020b\u0209"+
		"\u0001\u0000\u0000\u0000\u020b\u020c\u0001\u0000\u0000\u0000\u020c\u020e"+
		"\u0001\u0000\u0000\u0000\u020d\u020b\u0001\u0000\u0000\u0000\u020e\u0212"+
		"\u0005\r\u0000\u0000\u020f\u0211\u0003B!\u0000\u0210\u020f\u0001\u0000"+
		"\u0000\u0000\u0211\u0214\u0001\u0000\u0000\u0000\u0212\u0210\u0001\u0000"+
		"\u0000\u0000\u0212\u0213\u0001\u0000\u0000\u0000\u0213\u0216\u0001\u0000"+
		"\u0000\u0000\u0214\u0212\u0001\u0000\u0000\u0000\u0215\u020b\u0001\u0000"+
		"\u0000\u0000\u0216\u0217\u0001\u0000\u0000\u0000\u0217\u0215\u0001\u0000"+
		"\u0000\u0000\u0217\u0218\u0001\u0000\u0000\u0000\u0218E\u0001\u0000\u0000"+
		"\u0000\u0219\u021b\u0005X\u0000\u0000\u021a\u0219\u0001\u0000\u0000\u0000"+
		"\u021a\u021b\u0001\u0000\u0000\u0000\u021b\u021c\u0001\u0000\u0000\u0000"+
		"\u021c\u021d\u0005n\u0000\u0000\u021d\u021e\u0005:\u0000\u0000\u021eG"+
		"\u0001\u0000\u0000\u0000\u021f\u0237\u0005;\u0000\u0000\u0220\u0237\u0005"+
		"<\u0000\u0000\u0221\u0237\u0005=\u0000\u0000\u0222\u0237\u0005>\u0000"+
		"\u0000\u0223\u0237\u0005?\u0000\u0000\u0224\u0237\u0005@\u0000\u0000\u0225"+
		"\u0237\u0005O\u0000\u0000\u0226\u0237\u0005A\u0000\u0000\u0227\u0228\u0005"+
		"A\u0000\u0000\u0228\u0237\u0005A\u0000\u0000\u0229\u022a\u0005A\u0000"+
		"\u0000\u022a\u0237\u0005>\u0000\u0000\u022b\u022c\u0005B\u0000\u0000\u022c"+
		"\u0237\u0005?\u0000\u0000\u022d\u022e\u0005B\u0000\u0000\u022e\u0237\u0005"+
		";\u0000\u0000\u022f\u0230\u0005B\u0000\u0000\u0230\u0237\u0005<\u0000"+
		"\u0000\u0231\u0232\u0005B\u0000\u0000\u0232\u0237\u0005A\u0000\u0000\u0233"+
		"\u0234\u0005B\u0000\u0000\u0234\u0235\u0005A\u0000\u0000\u0235\u0237\u0005"+
		"A\u0000\u0000\u0236\u021f\u0001\u0000\u0000\u0000\u0236\u0220\u0001\u0000"+
		"\u0000\u0000\u0236\u0221\u0001\u0000\u0000\u0000\u0236\u0222\u0001\u0000"+
		"\u0000\u0000\u0236\u0223\u0001\u0000\u0000\u0000\u0236\u0224\u0001\u0000"+
		"\u0000\u0000\u0236\u0225\u0001\u0000\u0000\u0000\u0236\u0226\u0001\u0000"+
		"\u0000\u0000\u0236\u0227\u0001\u0000\u0000\u0000\u0236\u0229\u0001\u0000"+
		"\u0000\u0000\u0236\u022b\u0001\u0000\u0000\u0000\u0236\u022d\u0001\u0000"+
		"\u0000\u0000\u0236\u022f\u0001\u0000\u0000\u0000\u0236\u0231\u0001\u0000"+
		"\u0000\u0000\u0236\u0233\u0001\u0000\u0000\u0000\u0237I\u0001\u0000\u0000"+
		"\u0000\u0238\u0239\u0005Z\u0000\u0000\u0239\u023a\u0005n\u0000\u0000\u023a"+
		"\u023b\u00054\u0000\u0000\u023b\u0240\u0003L&\u0000\u023c\u023d\u0005"+
		"\u0002\u0000\u0000\u023d\u023f\u0003L&\u0000\u023e\u023c\u0001\u0000\u0000"+
		"\u0000\u023f\u0242\u0001\u0000\u0000\u0000\u0240\u023e\u0001\u0000\u0000"+
		"\u0000\u0240\u0241\u0001\u0000\u0000\u0000\u0241\u0244\u0001\u0000\u0000"+
		"\u0000\u0242\u0240\u0001\u0000\u0000\u0000\u0243\u0245\u0005\u0002\u0000"+
		"\u0000\u0244\u0243\u0001\u0000\u0000\u0000\u0244\u0245\u0001\u0000\u0000"+
		"\u0000\u0245\u0246\u0001\u0000\u0000\u0000\u0246\u0247\u0005o\u0000\u0000"+
		"\u0247\u0248\u0003t:\u0000\u0248K\u0001\u0000\u0000\u0000\u0249\u024c"+
		"\u0005n\u0000\u0000\u024a\u024b\u0005%\u0000\u0000\u024b\u024d\u0005h"+
		"\u0000\u0000\u024c\u024a\u0001\u0000\u0000\u0000\u024c\u024d\u0001\u0000"+
		"\u0000\u0000\u024dM\u0001\u0000\u0000\u0000\u024e\u024f\u0005^\u0000\u0000"+
		"\u024f\u0250\u0005n\u0000\u0000\u0250\u0251\u0003P(\u0000\u0251O\u0001"+
		"\u0000\u0000\u0000\u0252\u0256\u00054\u0000\u0000\u0253\u0255\u0003X,"+
		"\u0000\u0254\u0253\u0001\u0000\u0000\u0000\u0255\u0258\u0001\u0000\u0000"+
		"\u0000\u0256\u0254\u0001\u0000\u0000\u0000\u0256\u0257\u0001\u0000\u0000"+
		"\u0000\u0257\u0259\u0001\u0000\u0000\u0000\u0258\u0256\u0001\u0000\u0000"+
		"\u0000\u0259\u025a\u0005o\u0000\u0000\u025aQ\u0001\u0000\u0000\u0000\u025b"+
		"\u025d\u0005Y\u0000\u0000\u025c\u025e\u0005e\u0000\u0000\u025d\u025c\u0001"+
		"\u0000\u0000\u0000\u025d\u025e\u0001\u0000\u0000\u0000\u025e\u025f\u0001"+
		"\u0000\u0000\u0000\u025f\u0262\u0005n\u0000\u0000\u0260\u0261\u0005[\u0000"+
		"\u0000\u0261\u0263\u0005n\u0000\u0000\u0262\u0260\u0001\u0000\u0000\u0000"+
		"\u0262\u0263\u0001\u0000\u0000\u0000\u0263\u0264\u0001\u0000\u0000\u0000"+
		"\u0264\u0265\u0003T*\u0000\u0265\u0266\u0003t:\u0000\u0266S\u0001\u0000"+
		"\u0000\u0000\u0267\u026c\u00054\u0000\u0000\u0268\u026b\u0003V+\u0000"+
		"\u0269\u026b\u0003X,\u0000\u026a\u0268\u0001\u0000\u0000\u0000\u026a\u0269"+
		"\u0001\u0000\u0000\u0000\u026b\u026e\u0001\u0000\u0000\u0000\u026c\u026a"+
		"\u0001\u0000\u0000\u0000\u026c\u026d\u0001\u0000\u0000\u0000\u026d\u026f"+
		"\u0001\u0000\u0000\u0000\u026e\u026c\u0001\u0000\u0000\u0000\u026f\u0270"+
		"\u0005o\u0000\u0000\u0270U\u0001\u0000\u0000\u0000\u0271\u0272\u00038"+
		"\u001c\u0000\u0272\u0274\u0005n\u0000\u0000\u0273\u0275\u0003\u0014\n"+
		"\u0000\u0274\u0273\u0001\u0000\u0000\u0000\u0274\u0275\u0001\u0000\u0000"+
		"\u0000\u0275\u0277\u0001\u0000\u0000\u0000\u0276\u0278\u0003Z-\u0000\u0277"+
		"\u0276\u0001\u0000\u0000\u0000\u0277\u0278\u0001\u0000\u0000\u0000\u0278"+
		"\u0279\u0001\u0000\u0000\u0000\u0279\u027a\u0003t:\u0000\u027a\u0282\u0001"+
		"\u0000\u0000\u0000\u027b\u027d\u0003`0\u0000\u027c\u027e\u0003Z-\u0000"+
		"\u027d\u027c\u0001\u0000\u0000\u0000\u027d\u027e\u0001\u0000\u0000\u0000"+
		"\u027e\u027f\u0001\u0000\u0000\u0000\u027f\u0280\u0003t:\u0000\u0280\u0282"+
		"\u0001\u0000\u0000\u0000\u0281\u0271\u0001\u0000\u0000\u0000\u0281\u027b"+
		"\u0001\u0000\u0000\u0000\u0282W\u0001\u0000\u0000\u0000\u0283\u0286\u0003"+
		"b1\u0000\u0284\u0286\u0003h4\u0000\u0285\u0283\u0001\u0000\u0000\u0000"+
		"\u0285\u0284\u0001\u0000\u0000\u0000\u0286Y\u0001\u0000\u0000\u0000\u0287"+
		"\u0288\u0005%\u0000\u0000\u0288\u0289\u0003\n\u0005\u0000\u0289[\u0001"+
		"\u0000\u0000\u0000\u028a\u028c\u00038\u001c\u0000\u028b\u028d\u0005n\u0000"+
		"\u0000\u028c\u028b\u0001\u0000\u0000\u0000\u028c\u028d\u0001\u0000\u0000"+
		"\u0000\u028d\u0290\u0001\u0000\u0000\u0000\u028e\u0290\u0003`0\u0000\u028f"+
		"\u028a\u0001\u0000\u0000\u0000\u028f\u028e\u0001\u0000\u0000\u0000\u0290"+
		"]\u0001\u0000\u0000\u0000\u0291\u029a\u0005\u0001\u0000\u0000\u0292\u0297"+
		"\u0003\\.\u0000\u0293\u0294\u0005\u0002\u0000\u0000\u0294\u0296\u0003"+
		"\\.\u0000\u0295\u0293\u0001\u0000\u0000\u0000\u0296\u0299\u0001\u0000"+
		"\u0000\u0000\u0297\u0295\u0001\u0000\u0000\u0000\u0297\u0298\u0001\u0000"+
		"\u0000\u0000\u0298\u029b\u0001\u0000\u0000\u0000\u0299\u0297\u0001\u0000"+
		"\u0000\u0000\u029a\u0292\u0001\u0000\u0000\u0000\u029a\u029b\u0001\u0000"+
		"\u0000\u0000\u029b\u029d\u0001\u0000\u0000\u0000\u029c\u029e\u0005\u0002"+
		"\u0000\u0000\u029d\u029c\u0001\u0000\u0000\u0000\u029d\u029e\u0001\u0000"+
		"\u0000\u0000\u029e\u029f\u0001\u0000\u0000\u0000\u029f\u02a2\u0005\u0003"+
		"\u0000\u0000\u02a0\u02a2\u0001\u0000\u0000\u0000\u02a1\u0291\u0001\u0000"+
		"\u0000\u0000\u02a1\u02a0\u0001\u0000\u0000\u0000\u02a2_\u0001\u0000\u0000"+
		"\u0000\u02a3\u02a4\u00038\u001c\u0000\u02a4\u02a6\u0005\u0001\u0000\u0000"+
		"\u02a5\u02a7\u0005\r\u0000\u0000\u02a6\u02a5\u0001\u0000\u0000\u0000\u02a7"+
		"\u02a8\u0001\u0000\u0000\u0000\u02a8\u02a6\u0001\u0000\u0000\u0000\u02a8"+
		"\u02a9\u0001\u0000\u0000\u0000\u02a9\u02ab\u0001\u0000\u0000\u0000\u02aa"+
		"\u02ac\u0005n\u0000\u0000\u02ab\u02aa\u0001\u0000\u0000\u0000\u02ab\u02ac"+
		"\u0001\u0000\u0000\u0000\u02ac\u02ad\u0001\u0000\u0000\u0000\u02ad\u02ae"+
		"\u0005\u0003\u0000\u0000\u02ae\u02b2\u0003^/\u0000\u02af\u02b1\u0003>"+
		"\u001f\u0000\u02b0\u02af\u0001\u0000\u0000\u0000\u02b1\u02b4\u0001\u0000"+
		"\u0000\u0000\u02b2\u02b0\u0001\u0000\u0000\u0000\u02b2\u02b3\u0001\u0000"+
		"\u0000\u0000\u02b3a\u0001\u0000\u0000\u0000\u02b4\u02b2\u0001\u0000\u0000"+
		"\u0000\u02b5\u02b6\u00038\u001c\u0000\u02b6\u02b7\u0005n\u0000\u0000\u02b7"+
		"\u02b8\u0003^/\u0000\u02b8\u02b9\u00036\u001b\u0000\u02b9c\u0001\u0000"+
		"\u0000\u0000\u02ba\u02bc\u0005b\u0000\u0000\u02bb\u02ba\u0001\u0000\u0000"+
		"\u0000\u02bb\u02bc\u0001\u0000\u0000\u0000\u02bc\u02bd\u0001\u0000\u0000"+
		"\u0000\u02bd\u02c3\u0003b1\u0000\u02be\u02c0\u0005b\u0000\u0000\u02bf"+
		"\u02be\u0001\u0000\u0000\u0000\u02bf\u02c0\u0001\u0000\u0000\u0000\u02c0"+
		"\u02c1\u0001\u0000\u0000\u0000\u02c1\u02c3\u0003h4\u0000\u02c2\u02bb\u0001"+
		"\u0000\u0000\u0000\u02c2\u02bf\u0001\u0000\u0000\u0000\u02c3e\u0001\u0000"+
		"\u0000\u0000\u02c4\u02c5\u0003\u0016\u000b\u0000\u02c5\u02c6\u0003t:\u0000"+
		"\u02c6g\u0001\u0000\u0000\u0000\u02c7\u02c8\u0005\\\u0000\u0000\u02c8"+
		"\u02c9\u00038\u001c\u0000\u02c9\u02ca\u0005n\u0000\u0000\u02ca\u02cb\u0003"+
		"^/\u0000\u02cb\u02cc\u0003t:\u0000\u02cci\u0001\u0000\u0000\u0000\u02cd"+
		"\u02ce\u0005a\u0000\u0000\u02ce\u02cf\u0005\r\u0000\u0000\u02cf\u02d0"+
		"\u0005W\u0000\u0000\u02d0\u02d1\u0005l\u0000\u0000\u02d1\u02d8\u0003t"+
		":\u0000\u02d2\u02d3\u0005C\u0000\u0000\u02d3\u02d4\u0005\r\u0000\u0000"+
		"\u02d4\u02d5\u0005W\u0000\u0000\u02d5\u02d6\u0005l\u0000\u0000\u02d6\u02d8"+
		"\u0003t:\u0000\u02d7\u02cd\u0001\u0000\u0000\u0000\u02d7\u02d2\u0001\u0000"+
		"\u0000\u0000\u02d8k\u0001\u0000\u0000\u0000\u02d9\u02da\u0005D\u0000\u0000"+
		"\u02da\u02db\u0003n7\u0000\u02db\u02dc\u0003t:\u0000\u02dcm\u0001\u0000"+
		"\u0000\u0000\u02dd\u02e1\u0005\u0018\u0000\u0000\u02de\u02e0\b\t\u0000"+
		"\u0000\u02df\u02de\u0001\u0000\u0000\u0000\u02e0\u02e3\u0001\u0000\u0000"+
		"\u0000\u02e1\u02df\u0001\u0000\u0000\u0000\u02e1\u02e2\u0001\u0000\u0000"+
		"\u0000\u02e2\u02e4\u0001\u0000\u0000\u0000\u02e3\u02e1\u0001\u0000\u0000"+
		"\u0000\u02e4\u02e7\u0005\u0019\u0000\u0000\u02e5\u02e7\u0005l\u0000\u0000"+
		"\u02e6\u02dd\u0001\u0000\u0000\u0000\u02e6\u02e5\u0001\u0000\u0000\u0000"+
		"\u02e7o\u0001\u0000\u0000\u0000\u02e8\u02e9\u0005E\u0000\u0000\u02e9\u02ea"+
		"\u0005n\u0000\u0000\u02ea\u02eb\u0003t:\u0000\u02ebq\u0001\u0000\u0000"+
		"\u0000\u02ec\u02ed\u0007\n\u0000\u0000\u02eds\u0001\u0000\u0000\u0000"+
		"\u02ee\u02f3\u00053\u0000\u0000\u02ef\u02f3\u0005\u0000\u0000\u0001\u02f0"+
		"\u02f3\u0004:\u0014\u0000\u02f1\u02f3\u0004:\u0015\u0000\u02f2\u02ee\u0001"+
		"\u0000\u0000\u0000\u02f2\u02ef\u0001\u0000\u0000\u0000\u02f2\u02f0\u0001"+
		"\u0000\u0000\u0000\u02f2\u02f1\u0001\u0000\u0000\u0000\u02f3u\u0001\u0000"+
		"\u0000\u0000Py\u0086\u008e\u0092\u0094\u009d\u00a3\u00ca\u010b\u010e\u0110"+
		"\u011d\u0125\u012c\u0133\u0138\u013c\u013f\u0142\u0157\u0165\u017b\u017e"+
		"\u0182\u0186\u018a\u0192\u0197\u019b\u01a6\u01ab\u01b2\u01b5\u01bb\u01c1"+
		"\u01cd\u01d3\u01d7\u01dd\u01e0\u01e3\u01eb\u01f9\u01ff\u0203\u0206\u020b"+
		"\u0212\u0217\u021a\u0236\u0240\u0244\u024c\u0256\u025d\u0262\u026a\u026c"+
		"\u0274\u0277\u027d\u0281\u0285\u028c\u028f\u0297\u029a\u029d\u02a1\u02a8"+
		"\u02ab\u02b2\u02bb\u02bf\u02c2\u02d7\u02e1\u02e6\u02f2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}