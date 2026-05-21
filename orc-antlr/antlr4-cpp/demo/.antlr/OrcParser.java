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
		RULE_forCondition = 19, RULE_selectionStatement = 20, RULE_tryStatement = 21, 
		RULE_catchClause = 22, RULE_finallyClause = 23, RULE_block = 24, RULE_type = 25, 
		RULE_closureType = 26, RULE_functionTypeArg = 27, RULE_attribute = 28, 
		RULE_functionType = 29, RULE_typeQualifier = 30, RULE_pointer = 31, RULE_ref = 32, 
		RULE_primitiveType = 33, RULE_enumDefinition = 34, RULE_enumItem = 35, 
		RULE_extensionDefinition = 36, RULE_extensionBlock = 37, RULE_classDefinition = 38, 
		RULE_classDefinitionBlock = 39, RULE_classFieldDeclaration = 40, RULE_methodDeclaration = 41, 
		RULE_assignRightPart = 42, RULE_argumentDeclaration = 43, RULE_argumentsDeclaration = 44, 
		RULE_functionPointerVarDeclaration = 45, RULE_functionDefinition = 46, 
		RULE_globalFunctionDefinition = 47, RULE_globalVarDeclaration = 48, RULE_externFunctionDeclaration = 49, 
		RULE_importStatement = 50, RULE_includeStatement = 51, RULE_includePathCharacters = 52, 
		RULE_packageStatement = 53, RULE_literal = 54, RULE_eos = 55;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "rootDeclaration", "arguments", "expressionSequence", "closureExpression", 
			"singleExpression", "assignmentOperator", "emptyStatement", "structDefinition", 
			"structMember", "arraySizeDeclaration", "varDeclaration", "statement", 
			"continueStatement", "breakStatement", "throwStatement", "returnStatement", 
			"scopeStatement", "iterationStatement", "forCondition", "selectionStatement", 
			"tryStatement", "catchClause", "finallyClause", "block", "type", "closureType", 
			"functionTypeArg", "attribute", "functionType", "typeQualifier", "pointer", 
			"ref", "primitiveType", "enumDefinition", "enumItem", "extensionDefinition", 
			"extensionBlock", "classDefinition", "classDefinitionBlock", "classFieldDeclaration", 
			"methodDeclaration", "assignRightPart", "argumentDeclaration", "argumentsDeclaration", 
			"functionPointerVarDeclaration", "functionDefinition", "globalFunctionDefinition", 
			"globalVarDeclaration", "externFunctionDeclaration", "importStatement", 
			"includeStatement", "includePathCharacters", "packageStatement", "literal", 
			"eos"
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
			setState(115);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -322007373356990448L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70398121115711L) != 0)) {
				{
				{
				setState(112);
				rootDeclaration();
				}
				}
				setState(117);
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
			setState(128);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(118);
				packageStatement();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(119);
				includeStatement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(120);
				importStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(121);
				structDefinition();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(122);
				enumDefinition();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(123);
				classDefinition();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(124);
				extensionDefinition();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(125);
				globalVarDeclaration();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(126);
				globalFunctionDefinition();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(127);
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
			setState(130);
			match(T__0);
			setState(142);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 68585521409L) != 0)) {
				{
				setState(131);
				singleExpression(0);
				setState(136);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(132);
						match(T__1);
						setState(133);
						singleExpression(0);
						}
						} 
					}
					setState(138);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				}
				setState(140);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(139);
					match(T__1);
					}
				}

				}
			}

			setState(144);
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
			setState(146);
			singleExpression(0);
			setState(151);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(147);
				match(T__1);
				setState(148);
				singleExpression(0);
				}
				}
				setState(153);
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
			setState(154);
			match(T__3);
			setState(155);
			type();
			setState(157);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(156);
				match(Id);
				}
			}

			setState(159);
			argumentsDeclaration();
			setState(160);
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
			setState(196);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				{
				_localctx = new LabelClosureExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(163);
				closureExpression();
				}
				break;
			case 2:
				{
				_localctx = new NewExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(164);
				match(New);
				setState(165);
				match(Id);
				setState(166);
				arguments();
				}
				break;
			case 3:
				{
				_localctx = new GetAddressExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(167);
				match(T__11);
				setState(168);
				singleExpression(29);
				}
				break;
			case 4:
				{
				_localctx = new DerefExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(169);
				match(T__12);
				setState(170);
				singleExpression(28);
				}
				break;
			case 5:
				{
				_localctx = new PreIncrementExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(171);
				match(T__4);
				setState(172);
				singleExpression(27);
				}
				break;
			case 6:
				{
				_localctx = new PreDecreaseExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(173);
				match(T__5);
				setState(174);
				singleExpression(26);
				}
				break;
			case 7:
				{
				_localctx = new UnaryPlusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(175);
				match(T__13);
				setState(176);
				singleExpression(25);
				}
				break;
			case 8:
				{
				_localctx = new UnaryMinusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(177);
				match(T__14);
				setState(178);
				singleExpression(24);
				}
				break;
			case 9:
				{
				_localctx = new BitNotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(179);
				match(T__15);
				setState(180);
				singleExpression(23);
				}
				break;
			case 10:
				{
				_localctx = new NotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(181);
				match(T__16);
				setState(182);
				singleExpression(22);
				}
				break;
			case 11:
				{
				_localctx = new CastExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(183);
				match(T__0);
				setState(184);
				type();
				setState(185);
				match(T__2);
				setState(186);
				singleExpression(8);
				}
				break;
			case 12:
				{
				_localctx = new ThisExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(188);
				match(This);
				}
				break;
			case 13:
				{
				_localctx = new IdentifierExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(189);
				match(Id);
				}
				break;
			case 14:
				{
				_localctx = new SuperExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(190);
				match(Super);
				}
				break;
			case 15:
				{
				_localctx = new LiteralExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(191);
				literal();
				}
				break;
			case 16:
				{
				_localctx = new ParenthesizedExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(192);
				match(T__0);
				setState(193);
				expressionSequence();
				setState(194);
				match(T__2);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(266);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(264);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
					case 1:
						{
						_localctx = new MultiplicativeExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(198);
						if (!(precpred(_ctx, 21))) throw new FailedPredicateException(this, "precpred(_ctx, 21)");
						setState(199);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 794624L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(200);
						singleExpression(22);
						}
						break;
					case 2:
						{
						_localctx = new AdditiveExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(201);
						if (!(precpred(_ctx, 20))) throw new FailedPredicateException(this, "precpred(_ctx, 20)");
						setState(202);
						_la = _input.LA(1);
						if ( !(_la==T__13 || _la==T__14) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(203);
						singleExpression(21);
						}
						break;
					case 3:
						{
						_localctx = new CoalesceExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(204);
						if (!(precpred(_ctx, 19))) throw new FailedPredicateException(this, "precpred(_ctx, 19)");
						setState(205);
						match(T__19);
						setState(206);
						singleExpression(20);
						}
						break;
					case 4:
						{
						_localctx = new BitShiftExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(207);
						if (!(precpred(_ctx, 18))) throw new FailedPredicateException(this, "precpred(_ctx, 18)");
						setState(208);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 14680064L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(209);
						singleExpression(19);
						}
						break;
					case 5:
						{
						_localctx = new RelationalExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(210);
						if (!(precpred(_ctx, 17))) throw new FailedPredicateException(this, "precpred(_ctx, 17)");
						setState(211);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 251658240L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(212);
						singleExpression(18);
						}
						break;
					case 6:
						{
						_localctx = new InstanceofExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(213);
						if (!(precpred(_ctx, 16))) throw new FailedPredicateException(this, "precpred(_ctx, 16)");
						setState(214);
						match(Instanceof);
						setState(215);
						singleExpression(17);
						}
						break;
					case 7:
						{
						_localctx = new EqualityExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(216);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(217);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4026531840L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(218);
						singleExpression(16);
						}
						break;
					case 8:
						{
						_localctx = new BitAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(219);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(220);
						match(T__11);
						setState(221);
						singleExpression(15);
						}
						break;
					case 9:
						{
						_localctx = new BitXOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(222);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(223);
						match(T__3);
						setState(224);
						singleExpression(14);
						}
						break;
					case 10:
						{
						_localctx = new BitOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(225);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(226);
						match(T__31);
						setState(227);
						singleExpression(13);
						}
						break;
					case 11:
						{
						_localctx = new LogicalAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(228);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(229);
						match(T__32);
						setState(230);
						singleExpression(12);
						}
						break;
					case 12:
						{
						_localctx = new LogicalOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(231);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(232);
						match(T__33);
						setState(233);
						singleExpression(11);
						}
						break;
					case 13:
						{
						_localctx = new TernaryExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(234);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(235);
						match(T__34);
						setState(236);
						singleExpression(0);
						setState(237);
						match(T__35);
						setState(238);
						singleExpression(10);
						}
						break;
					case 14:
						{
						_localctx = new AssignmentExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(240);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(241);
						match(T__36);
						setState(242);
						singleExpression(7);
						}
						break;
					case 15:
						{
						_localctx = new AssignmentOperatorExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(243);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(244);
						assignmentOperator();
						setState(245);
						singleExpression(6);
						}
						break;
					case 16:
						{
						_localctx = new CallExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(247);
						if (!(precpred(_ctx, 36))) throw new FailedPredicateException(this, "precpred(_ctx, 36)");
						setState(248);
						arguments();
						}
						break;
					case 17:
						{
						_localctx = new PostIncrementExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(249);
						if (!(precpred(_ctx, 35))) throw new FailedPredicateException(this, "precpred(_ctx, 35)");
						setState(250);
						match(T__4);
						}
						break;
					case 18:
						{
						_localctx = new PostDecreaseExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(251);
						if (!(precpred(_ctx, 34))) throw new FailedPredicateException(this, "precpred(_ctx, 34)");
						setState(252);
						match(T__5);
						}
						break;
					case 19:
						{
						_localctx = new MemberIndexExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(253);
						if (!(precpred(_ctx, 32))) throw new FailedPredicateException(this, "precpred(_ctx, 32)");
						setState(254);
						match(T__6);
						setState(255);
						singleExpression(0);
						setState(256);
						match(T__7);
						}
						break;
					case 20:
						{
						_localctx = new MemberDotExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(258);
						if (!(precpred(_ctx, 31))) throw new FailedPredicateException(this, "precpred(_ctx, 31)");
						setState(259);
						_la = _input.LA(1);
						if ( !(_la==T__8 || _la==T__9) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(261);
						_errHandler.sync(this);
						_la = _input.LA(1);
						if (_la==T__10) {
							{
							setState(260);
							match(T__10);
							}
						}

						setState(263);
						match(Id);
						}
						break;
					}
					} 
				}
				setState(268);
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
			setState(269);
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
			setState(271);
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
			setState(273);
			match(Struct);
			setState(274);
			match(Id);
			setState(275);
			match(T__51);
			setState(279);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70370908471303L) != 0)) {
				{
				{
				setState(276);
				structMember();
				}
				}
				setState(281);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(282);
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
			setState(294);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(284);
				type();
				setState(285);
				match(Id);
				setState(287);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
				case 1:
					{
					setState(286);
					arraySizeDeclaration();
					}
					break;
				}
				setState(289);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(291);
				functionPointerVarDeclaration();
				setState(292);
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
			setState(296);
			match(T__6);
			setState(297);
			match(DecimalLiteral);
			setState(298);
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
			setState(316);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(301);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(300);
					match(Static);
					}
				}

				setState(303);
				type();
				setState(304);
				match(Id);
				setState(306);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
				case 1:
					{
					setState(305);
					arraySizeDeclaration();
					}
					break;
				}
				setState(310);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
				case 1:
					{
					setState(308);
					match(T__36);
					setState(309);
					singleExpression(0);
					}
					break;
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(313);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(312);
					match(Static);
					}
				}

				setState(315);
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
			setState(337);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(318);
				closureExpression();
				setState(319);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(321);
				varDeclaration();
				setState(322);
				eos();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(324);
				scopeStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(325);
				block();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(326);
				continueStatement();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(327);
				breakStatement();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(328);
				throwStatement();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(329);
				selectionStatement();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(330);
				returnStatement();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(331);
				iterationStatement();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(332);
				tryStatement();
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(333);
				singleExpression(0);
				setState(334);
				eos();
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(336);
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
			setState(339);
			match(Continue);
			setState(340);
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
			setState(342);
			match(Break);
			setState(343);
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
			setState(345);
			match(Throw);
			setState(346);
			singleExpression(0);
			setState(347);
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
			setState(349);
			match(Return);
			setState(351);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
			case 1:
				{
				setState(350);
				singleExpression(0);
				}
				break;
			}
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
			setState(355);
			singleExpression(0);
			setState(356);
			_la = _input.LA(1);
			if ( !(_la==T__8 || _la==T__15) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(357);
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
			setState(373);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(359);
				match(While);
				setState(360);
				singleExpression(0);
				setState(361);
				block();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(363);
				match(For);
				setState(364);
				match(T__0);
				setState(365);
				forCondition();
				setState(366);
				match(T__2);
				setState(367);
				block();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(369);
				match(For);
				setState(370);
				forCondition();
				setState(371);
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
		public VarDeclarationContext varDeclaration() {
			return getRuleContext(VarDeclarationContext.class,0);
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
			setState(379);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				{
				setState(375);
				varDeclaration();
				}
				break;
			case 2:
				{
				setState(377);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 68585521409L) != 0)) {
					{
					setState(376);
					singleExpression(0);
					}
				}

				}
				break;
			}
			setState(381);
			match(T__50);
			setState(383);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 68585521409L) != 0)) {
				{
				setState(382);
				singleExpression(0);
				}
			}

			setState(385);
			match(T__50);
			setState(387);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 68585521409L) != 0)) {
				{
				setState(386);
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
		enterRule(_localctx, 40, RULE_selectionStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(389);
			match(If);
			setState(390);
			singleExpression(0);
			setState(391);
			block();
			setState(398);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__52) {
				{
				{
				setState(392);
				match(T__52);
				setState(393);
				singleExpression(0);
				setState(394);
				block();
				}
				}
				setState(400);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(403);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Else) {
				{
				setState(401);
				match(Else);
				setState(402);
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
		enterRule(_localctx, 42, RULE_tryStatement);
		int _la;
		try {
			setState(419);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,30,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(405);
				match(Try);
				setState(406);
				block();
				setState(408); 
				_errHandler.sync(this);
				_la = _input.LA(1);
				do {
					{
					{
					setState(407);
					catchClause();
					}
					}
					setState(410); 
					_errHandler.sync(this);
					_la = _input.LA(1);
				} while ( _la==Catch );
				setState(413);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Finally) {
					{
					setState(412);
					finallyClause();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(415);
				match(Try);
				setState(416);
				block();
				setState(417);
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
		enterRule(_localctx, 44, RULE_catchClause);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(421);
			match(Catch);
			setState(422);
			match(T__0);
			setState(423);
			ref();
			setState(425);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(424);
				match(Id);
				}
			}

			setState(427);
			match(T__2);
			setState(428);
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
		enterRule(_localctx, 46, RULE_finallyClause);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(430);
			match(Finally);
			setState(431);
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
		enterRule(_localctx, 48, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(433);
			match(T__51);
			setState(437);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -317503773729361806L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 140482499823687L) != 0)) {
				{
				{
				setState(434);
				statement();
				}
				}
				setState(439);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(440);
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
		enterRule(_localctx, 50, RULE_type);
		int _la;
		try {
			setState(459);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,37,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(443);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
					{
					setState(442);
					typeQualifier();
					}
				}

				setState(445);
				primitiveType();
				setState(447);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__6) {
					{
					setState(446);
					arraySizeDeclaration();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(449);
				closureType();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(450);
				pointer();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(451);
				ref();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(453);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
					{
					setState(452);
					typeQualifier();
					}
				}

				setState(456);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Struct) {
					{
					setState(455);
					match(Struct);
					}
				}

				setState(458);
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
		enterRule(_localctx, 52, RULE_closureType);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(461);
			match(T__3);
			setState(462);
			type();
			setState(463);
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
		enterRule(_localctx, 54, RULE_functionTypeArg);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(465);
			type();
			setState(467);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(466);
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
		enterRule(_localctx, 56, RULE_attribute);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(469);
			match(T__53);
			setState(470);
			match(T__0);
			setState(471);
			match(T__0);
			setState(472);
			match(Id);
			setState(473);
			match(T__2);
			setState(474);
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
		enterRule(_localctx, 58, RULE_functionType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(476);
			type();
			setState(477);
			argumentsDeclaration();
			setState(481);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__53) {
				{
				{
				setState(478);
				attribute();
				}
				}
				setState(483);
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
		enterRule(_localctx, 60, RULE_typeQualifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(484);
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
		enterRule(_localctx, 62, RULE_pointer);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(487);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
				{
				setState(486);
				typeQualifier();
				}
			}

			setState(494);
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
				setState(489);
				primitiveType();
				}
				break;
			case Struct:
			case Id:
				{
				{
				setState(491);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Struct) {
					{
					setState(490);
					match(Struct);
					}
				}

				setState(493);
				match(Id);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(509); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(499);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 1099511627783L) != 0)) {
					{
					{
					setState(496);
					typeQualifier();
					}
					}
					setState(501);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(502);
				match(T__12);
				setState(506);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(503);
						typeQualifier();
						}
						} 
					}
					setState(508);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
				}
				}
				}
				setState(511); 
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
		enterRule(_localctx, 64, RULE_ref);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(514);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Struct) {
				{
				setState(513);
				match(Struct);
				}
			}

			setState(516);
			match(Id);
			setState(517);
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
		enterRule(_localctx, 66, RULE_primitiveType);
		try {
			setState(542);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,47,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(519);
				match(T__58);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(520);
				match(T__59);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(521);
				match(T__60);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(522);
				match(T__61);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(523);
				match(T__62);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(524);
				match(T__63);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(525);
				match(Void);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(526);
				match(T__64);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(527);
				match(T__64);
				setState(528);
				match(T__64);
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(529);
				match(T__64);
				setState(530);
				match(T__61);
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(531);
				match(T__65);
				setState(532);
				match(T__62);
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(533);
				match(T__65);
				setState(534);
				match(T__58);
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(535);
				match(T__65);
				setState(536);
				match(T__59);
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(537);
				match(T__65);
				setState(538);
				match(T__64);
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(539);
				match(T__65);
				setState(540);
				match(T__64);
				setState(541);
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
		enterRule(_localctx, 68, RULE_enumDefinition);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(544);
			match(Enum);
			setState(545);
			match(Id);
			setState(546);
			match(T__51);
			setState(547);
			enumItem();
			setState(552);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,48,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(548);
					match(T__1);
					setState(549);
					enumItem();
					}
					} 
				}
				setState(554);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,48,_ctx);
			}
			setState(556);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(555);
				match(T__1);
				}
			}

			setState(558);
			match(CloseBrace);
			setState(559);
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
		enterRule(_localctx, 70, RULE_enumItem);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(561);
			match(Id);
			setState(564);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__36) {
				{
				setState(562);
				match(T__36);
				setState(563);
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
		enterRule(_localctx, 72, RULE_extensionDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(566);
			match(Extension);
			setState(567);
			match(Id);
			setState(568);
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
		enterRule(_localctx, 74, RULE_extensionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(570);
			match(T__51);
			setState(574);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70371176906759L) != 0)) {
				{
				{
				setState(571);
				methodDeclaration();
				}
				}
				setState(576);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(577);
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
		enterRule(_localctx, 76, RULE_classDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(579);
			match(Class);
			setState(581);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Refc) {
				{
				setState(580);
				match(Refc);
				}
			}

			setState(583);
			match(Id);
			setState(586);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Extends) {
				{
				setState(584);
				match(Extends);
				setState(585);
				match(Id);
				}
			}

			setState(588);
			classDefinitionBlock();
			setState(589);
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
		enterRule(_localctx, 78, RULE_classDefinitionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(591);
			match(T__51);
			setState(596);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70371176906759L) != 0)) {
				{
				setState(594);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,54,_ctx) ) {
				case 1:
					{
					setState(592);
					classFieldDeclaration();
					}
					break;
				case 2:
					{
					setState(593);
					methodDeclaration();
					}
					break;
				}
				}
				setState(598);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(599);
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
		enterRule(_localctx, 80, RULE_classFieldDeclaration);
		try {
			setState(617);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,59,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(601);
				type();
				setState(602);
				match(Id);
				setState(604);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,56,_ctx) ) {
				case 1:
					{
					setState(603);
					arraySizeDeclaration();
					}
					break;
				}
				setState(607);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,57,_ctx) ) {
				case 1:
					{
					setState(606);
					assignRightPart();
					}
					break;
				}
				setState(609);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(611);
				functionPointerVarDeclaration();
				setState(613);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,58,_ctx) ) {
				case 1:
					{
					setState(612);
					assignRightPart();
					}
					break;
				}
				setState(615);
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
		enterRule(_localctx, 82, RULE_methodDeclaration);
		try {
			setState(621);
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
				setState(619);
				functionDefinition();
				}
				break;
			case Extern:
				enterOuterAlt(_localctx, 2);
				{
				setState(620);
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
		enterRule(_localctx, 84, RULE_assignRightPart);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(623);
			match(T__36);
			setState(624);
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
		enterRule(_localctx, 86, RULE_argumentDeclaration);
		int _la;
		try {
			setState(631);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,62,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(626);
				type();
				setState(628);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Id) {
					{
					setState(627);
					match(Id);
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(630);
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
		enterRule(_localctx, 88, RULE_argumentsDeclaration);
		int _la;
		try {
			int _alt;
			setState(649);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,66,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(633);
				match(T__0);
				setState(642);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 70370908471303L) != 0)) {
					{
					setState(634);
					argumentDeclaration();
					setState(639);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,63,_ctx);
					while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
						if ( _alt==1 ) {
							{
							{
							setState(635);
							match(T__1);
							setState(636);
							argumentDeclaration();
							}
							} 
						}
						setState(641);
						_errHandler.sync(this);
						_alt = getInterpreter().adaptivePredict(_input,63,_ctx);
					}
					}
				}

				setState(645);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(644);
					match(T__1);
					}
				}

				setState(647);
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
		enterRule(_localctx, 90, RULE_functionPointerVarDeclaration);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(651);
			type();
			setState(652);
			match(T__0);
			setState(654); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(653);
				match(T__12);
				}
				}
				setState(656); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__12 );
			setState(659);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(658);
				match(Id);
				}
			}

			setState(661);
			match(T__2);
			setState(662);
			argumentsDeclaration();
			setState(666);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,69,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(663);
					attribute();
					}
					} 
				}
				setState(668);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,69,_ctx);
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
		enterRule(_localctx, 92, RULE_functionDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(669);
			type();
			setState(670);
			match(Id);
			setState(671);
			argumentsDeclaration();
			setState(672);
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
		enterRule(_localctx, 94, RULE_globalFunctionDefinition);
		int _la;
		try {
			setState(682);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,72,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(675);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(674);
					match(Static);
					}
				}

				setState(677);
				functionDefinition();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(679);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(678);
					match(Static);
					}
				}

				setState(681);
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
		enterRule(_localctx, 96, RULE_globalVarDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(684);
			varDeclaration();
			setState(685);
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
		enterRule(_localctx, 98, RULE_externFunctionDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(687);
			match(Extern);
			setState(688);
			type();
			setState(689);
			match(Id);
			setState(690);
			argumentsDeclaration();
			setState(691);
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
		enterRule(_localctx, 100, RULE_importStatement);
		try {
			setState(703);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Import:
				enterOuterAlt(_localctx, 1);
				{
				setState(693);
				match(Import);
				setState(694);
				match(T__12);
				setState(695);
				match(From);
				setState(696);
				match(StringLiteral);
				setState(697);
				eos();
				}
				break;
			case T__66:
				enterOuterAlt(_localctx, 2);
				{
				setState(698);
				match(T__66);
				setState(699);
				match(T__12);
				setState(700);
				match(From);
				setState(701);
				match(StringLiteral);
				setState(702);
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
		enterRule(_localctx, 102, RULE_includeStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(705);
			match(T__67);
			setState(706);
			includePathCharacters();
			setState(707);
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
		enterRule(_localctx, 104, RULE_includePathCharacters);
		int _la;
		try {
			setState(718);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__23:
				enterOuterAlt(_localctx, 1);
				{
				setState(709);
				match(T__23);
				setState(713);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -33554434L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 4503599627370495L) != 0)) {
					{
					{
					setState(710);
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
					setState(715);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(716);
				match(T__24);
				}
				break;
			case StringLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(717);
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
		enterRule(_localctx, 106, RULE_packageStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(720);
			match(T__68);
			setState(721);
			match(Id);
			setState(722);
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
		enterRule(_localctx, 108, RULE_literal);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(724);
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
		enterRule(_localctx, 110, RULE_eos);
		try {
			setState(730);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,76,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(726);
				match(T__50);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(727);
				match(EOF);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(728);
				if (!(this->lineTerminatorAhead())) throw new FailedPredicateException(this, "this->lineTerminatorAhead()");
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(729);
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
		case 55:
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
		"\u0004\u0001s\u02dd\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
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
		"7\u00077\u0001\u0000\u0005\u0000r\b\u0000\n\u0000\f\u0000u\t\u0000\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0003\u0001\u0081\b\u0001\u0001"+
		"\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0005\u0002\u0087\b\u0002\n"+
		"\u0002\f\u0002\u008a\t\u0002\u0001\u0002\u0003\u0002\u008d\b\u0002\u0003"+
		"\u0002\u008f\b\u0002\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0005\u0003\u0096\b\u0003\n\u0003\f\u0003\u0099\t\u0003\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0003\u0004\u009e\b\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0003\u0005"+
		"\u00c5\b\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0003\u0005\u0106\b\u0005"+
		"\u0001\u0005\u0005\u0005\u0109\b\u0005\n\u0005\f\u0005\u010c\t\u0005\u0001"+
		"\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001"+
		"\b\u0005\b\u0116\b\b\n\b\f\b\u0119\t\b\u0001\b\u0001\b\u0001\t\u0001\t"+
		"\u0001\t\u0003\t\u0120\b\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0003"+
		"\t\u0127\b\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\u000b\u0003\u000b\u012e"+
		"\b\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u0133\b\u000b"+
		"\u0001\u000b\u0001\u000b\u0003\u000b\u0137\b\u000b\u0001\u000b\u0003\u000b"+
		"\u013a\b\u000b\u0001\u000b\u0003\u000b\u013d\b\u000b\u0001\f\u0001\f\u0001"+
		"\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0003\f\u0152"+
		"\b\f\u0001\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u0010\u0001\u0010\u0003"+
		"\u0010\u0160\b\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0001\u0012\u0003\u0012\u0176\b\u0012\u0001"+
		"\u0013\u0001\u0013\u0003\u0013\u017a\b\u0013\u0003\u0013\u017c\b\u0013"+
		"\u0001\u0013\u0001\u0013\u0003\u0013\u0180\b\u0013\u0001\u0013\u0001\u0013"+
		"\u0003\u0013\u0184\b\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0001\u0014\u0001\u0014\u0001\u0014\u0005\u0014\u018d\b\u0014\n\u0014"+
		"\f\u0014\u0190\t\u0014\u0001\u0014\u0001\u0014\u0003\u0014\u0194\b\u0014"+
		"\u0001\u0015\u0001\u0015\u0001\u0015\u0004\u0015\u0199\b\u0015\u000b\u0015"+
		"\f\u0015\u019a\u0001\u0015\u0003\u0015\u019e\b\u0015\u0001\u0015\u0001"+
		"\u0015\u0001\u0015\u0001\u0015\u0003\u0015\u01a4\b\u0015\u0001\u0016\u0001"+
		"\u0016\u0001\u0016\u0001\u0016\u0003\u0016\u01aa\b\u0016\u0001\u0016\u0001"+
		"\u0016\u0001\u0016\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0018\u0001"+
		"\u0018\u0005\u0018\u01b4\b\u0018\n\u0018\f\u0018\u01b7\t\u0018\u0001\u0018"+
		"\u0001\u0018\u0001\u0019\u0003\u0019\u01bc\b\u0019\u0001\u0019\u0001\u0019"+
		"\u0003\u0019\u01c0\b\u0019\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u0019"+
		"\u0003\u0019\u01c6\b\u0019\u0001\u0019\u0003\u0019\u01c9\b\u0019\u0001"+
		"\u0019\u0003\u0019\u01cc\b\u0019\u0001\u001a\u0001\u001a\u0001\u001a\u0001"+
		"\u001a\u0001\u001b\u0001\u001b\u0003\u001b\u01d4\b\u001b\u0001\u001c\u0001"+
		"\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0001"+
		"\u001d\u0001\u001d\u0001\u001d\u0005\u001d\u01e0\b\u001d\n\u001d\f\u001d"+
		"\u01e3\t\u001d\u0001\u001e\u0001\u001e\u0001\u001f\u0003\u001f\u01e8\b"+
		"\u001f\u0001\u001f\u0001\u001f\u0003\u001f\u01ec\b\u001f\u0001\u001f\u0003"+
		"\u001f\u01ef\b\u001f\u0001\u001f\u0005\u001f\u01f2\b\u001f\n\u001f\f\u001f"+
		"\u01f5\t\u001f\u0001\u001f\u0001\u001f\u0005\u001f\u01f9\b\u001f\n\u001f"+
		"\f\u001f\u01fc\t\u001f\u0004\u001f\u01fe\b\u001f\u000b\u001f\f\u001f\u01ff"+
		"\u0001 \u0003 \u0203\b \u0001 \u0001 \u0001 \u0001!\u0001!\u0001!\u0001"+
		"!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001"+
		"!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0001!\u0003"+
		"!\u021f\b!\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0001\"\u0005\"\u0227"+
		"\b\"\n\"\f\"\u022a\t\"\u0001\"\u0003\"\u022d\b\"\u0001\"\u0001\"\u0001"+
		"\"\u0001#\u0001#\u0001#\u0003#\u0235\b#\u0001$\u0001$\u0001$\u0001$\u0001"+
		"%\u0001%\u0005%\u023d\b%\n%\f%\u0240\t%\u0001%\u0001%\u0001&\u0001&\u0003"+
		"&\u0246\b&\u0001&\u0001&\u0001&\u0003&\u024b\b&\u0001&\u0001&\u0001&\u0001"+
		"\'\u0001\'\u0001\'\u0005\'\u0253\b\'\n\'\f\'\u0256\t\'\u0001\'\u0001\'"+
		"\u0001(\u0001(\u0001(\u0003(\u025d\b(\u0001(\u0003(\u0260\b(\u0001(\u0001"+
		"(\u0001(\u0001(\u0003(\u0266\b(\u0001(\u0001(\u0003(\u026a\b(\u0001)\u0001"+
		")\u0003)\u026e\b)\u0001*\u0001*\u0001*\u0001+\u0001+\u0003+\u0275\b+\u0001"+
		"+\u0003+\u0278\b+\u0001,\u0001,\u0001,\u0001,\u0005,\u027e\b,\n,\f,\u0281"+
		"\t,\u0003,\u0283\b,\u0001,\u0003,\u0286\b,\u0001,\u0001,\u0003,\u028a"+
		"\b,\u0001-\u0001-\u0001-\u0004-\u028f\b-\u000b-\f-\u0290\u0001-\u0003"+
		"-\u0294\b-\u0001-\u0001-\u0001-\u0005-\u0299\b-\n-\f-\u029c\t-\u0001."+
		"\u0001.\u0001.\u0001.\u0001.\u0001/\u0003/\u02a4\b/\u0001/\u0001/\u0003"+
		"/\u02a8\b/\u0001/\u0003/\u02ab\b/\u00010\u00010\u00010\u00011\u00011\u0001"+
		"1\u00011\u00011\u00011\u00012\u00012\u00012\u00012\u00012\u00012\u0001"+
		"2\u00012\u00012\u00012\u00032\u02c0\b2\u00013\u00013\u00013\u00013\u0001"+
		"4\u00014\u00054\u02c8\b4\n4\f4\u02cb\t4\u00014\u00014\u00034\u02cf\b4"+
		"\u00015\u00015\u00015\u00015\u00016\u00016\u00017\u00017\u00017\u0001"+
		"7\u00037\u02db\b7\u00017\u0000\u0001\n8\u0000\u0002\u0004\u0006\b\n\f"+
		"\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,.02468:"+
		"<>@BDFHJLNPRTVXZ\\^`bdfhjln\u0000\u000b\u0002\u0000\r\r\u0012\u0013\u0001"+
		"\u0000\u000e\u000f\u0001\u0000\u0015\u0017\u0001\u0000\u0018\u001b\u0001"+
		"\u0000\u001c\u001f\u0001\u0000\t\n\u0001\u0000&2\u0002\u0000\t\t\u0010"+
		"\u0010\u0002\u000079__\u0001\u0000\u0019\u0019\u0001\u0000fm\u0337\u0000"+
		"s\u0001\u0000\u0000\u0000\u0002\u0080\u0001\u0000\u0000\u0000\u0004\u0082"+
		"\u0001\u0000\u0000\u0000\u0006\u0092\u0001\u0000\u0000\u0000\b\u009a\u0001"+
		"\u0000\u0000\u0000\n\u00c4\u0001\u0000\u0000\u0000\f\u010d\u0001\u0000"+
		"\u0000\u0000\u000e\u010f\u0001\u0000\u0000\u0000\u0010\u0111\u0001\u0000"+
		"\u0000\u0000\u0012\u0126\u0001\u0000\u0000\u0000\u0014\u0128\u0001\u0000"+
		"\u0000\u0000\u0016\u013c\u0001\u0000\u0000\u0000\u0018\u0151\u0001\u0000"+
		"\u0000\u0000\u001a\u0153\u0001\u0000\u0000\u0000\u001c\u0156\u0001\u0000"+
		"\u0000\u0000\u001e\u0159\u0001\u0000\u0000\u0000 \u015d\u0001\u0000\u0000"+
		"\u0000\"\u0163\u0001\u0000\u0000\u0000$\u0175\u0001\u0000\u0000\u0000"+
		"&\u017b\u0001\u0000\u0000\u0000(\u0185\u0001\u0000\u0000\u0000*\u01a3"+
		"\u0001\u0000\u0000\u0000,\u01a5\u0001\u0000\u0000\u0000.\u01ae\u0001\u0000"+
		"\u0000\u00000\u01b1\u0001\u0000\u0000\u00002\u01cb\u0001\u0000\u0000\u0000"+
		"4\u01cd\u0001\u0000\u0000\u00006\u01d1\u0001\u0000\u0000\u00008\u01d5"+
		"\u0001\u0000\u0000\u0000:\u01dc\u0001\u0000\u0000\u0000<\u01e4\u0001\u0000"+
		"\u0000\u0000>\u01e7\u0001\u0000\u0000\u0000@\u0202\u0001\u0000\u0000\u0000"+
		"B\u021e\u0001\u0000\u0000\u0000D\u0220\u0001\u0000\u0000\u0000F\u0231"+
		"\u0001\u0000\u0000\u0000H\u0236\u0001\u0000\u0000\u0000J\u023a\u0001\u0000"+
		"\u0000\u0000L\u0243\u0001\u0000\u0000\u0000N\u024f\u0001\u0000\u0000\u0000"+
		"P\u0269\u0001\u0000\u0000\u0000R\u026d\u0001\u0000\u0000\u0000T\u026f"+
		"\u0001\u0000\u0000\u0000V\u0277\u0001\u0000\u0000\u0000X\u0289\u0001\u0000"+
		"\u0000\u0000Z\u028b\u0001\u0000\u0000\u0000\\\u029d\u0001\u0000\u0000"+
		"\u0000^\u02aa\u0001\u0000\u0000\u0000`\u02ac\u0001\u0000\u0000\u0000b"+
		"\u02af\u0001\u0000\u0000\u0000d\u02bf\u0001\u0000\u0000\u0000f\u02c1\u0001"+
		"\u0000\u0000\u0000h\u02ce\u0001\u0000\u0000\u0000j\u02d0\u0001\u0000\u0000"+
		"\u0000l\u02d4\u0001\u0000\u0000\u0000n\u02da\u0001\u0000\u0000\u0000p"+
		"r\u0003\u0002\u0001\u0000qp\u0001\u0000\u0000\u0000ru\u0001\u0000\u0000"+
		"\u0000sq\u0001\u0000\u0000\u0000st\u0001\u0000\u0000\u0000t\u0001\u0001"+
		"\u0000\u0000\u0000us\u0001\u0000\u0000\u0000v\u0081\u0003j5\u0000w\u0081"+
		"\u0003f3\u0000x\u0081\u0003d2\u0000y\u0081\u0003\u0010\b\u0000z\u0081"+
		"\u0003D\"\u0000{\u0081\u0003L&\u0000|\u0081\u0003H$\u0000}\u0081\u0003"+
		"`0\u0000~\u0081\u0003^/\u0000\u007f\u0081\u0003\u000e\u0007\u0000\u0080"+
		"v\u0001\u0000\u0000\u0000\u0080w\u0001\u0000\u0000\u0000\u0080x\u0001"+
		"\u0000\u0000\u0000\u0080y\u0001\u0000\u0000\u0000\u0080z\u0001\u0000\u0000"+
		"\u0000\u0080{\u0001\u0000\u0000\u0000\u0080|\u0001\u0000\u0000\u0000\u0080"+
		"}\u0001\u0000\u0000\u0000\u0080~\u0001\u0000\u0000\u0000\u0080\u007f\u0001"+
		"\u0000\u0000\u0000\u0081\u0003\u0001\u0000\u0000\u0000\u0082\u008e\u0005"+
		"\u0001\u0000\u0000\u0083\u0088\u0003\n\u0005\u0000\u0084\u0085\u0005\u0002"+
		"\u0000\u0000\u0085\u0087\u0003\n\u0005\u0000\u0086\u0084\u0001\u0000\u0000"+
		"\u0000\u0087\u008a\u0001\u0000\u0000\u0000\u0088\u0086\u0001\u0000\u0000"+
		"\u0000\u0088\u0089\u0001\u0000\u0000\u0000\u0089\u008c\u0001\u0000\u0000"+
		"\u0000\u008a\u0088\u0001\u0000\u0000\u0000\u008b\u008d\u0005\u0002\u0000"+
		"\u0000\u008c\u008b\u0001\u0000\u0000\u0000\u008c\u008d\u0001\u0000\u0000"+
		"\u0000\u008d\u008f\u0001\u0000\u0000\u0000\u008e\u0083\u0001\u0000\u0000"+
		"\u0000\u008e\u008f\u0001\u0000\u0000\u0000\u008f\u0090\u0001\u0000\u0000"+
		"\u0000\u0090\u0091\u0005\u0003\u0000\u0000\u0091\u0005\u0001\u0000\u0000"+
		"\u0000\u0092\u0097\u0003\n\u0005\u0000\u0093\u0094\u0005\u0002\u0000\u0000"+
		"\u0094\u0096\u0003\n\u0005\u0000\u0095\u0093\u0001\u0000\u0000\u0000\u0096"+
		"\u0099\u0001\u0000\u0000\u0000\u0097\u0095\u0001\u0000\u0000\u0000\u0097"+
		"\u0098\u0001\u0000\u0000\u0000\u0098\u0007\u0001\u0000\u0000\u0000\u0099"+
		"\u0097\u0001\u0000\u0000\u0000\u009a\u009b\u0005\u0004\u0000\u0000\u009b"+
		"\u009d\u00032\u0019\u0000\u009c\u009e\u0005n\u0000\u0000\u009d\u009c\u0001"+
		"\u0000\u0000\u0000\u009d\u009e\u0001\u0000\u0000\u0000\u009e\u009f\u0001"+
		"\u0000\u0000\u0000\u009f\u00a0\u0003X,\u0000\u00a0\u00a1\u00030\u0018"+
		"\u0000\u00a1\t\u0001\u0000\u0000\u0000\u00a2\u00a3\u0006\u0005\uffff\uffff"+
		"\u0000\u00a3\u00c5\u0003\b\u0004\u0000\u00a4\u00a5\u0005K\u0000\u0000"+
		"\u00a5\u00a6\u0005n\u0000\u0000\u00a6\u00c5\u0003\u0004\u0002\u0000\u00a7"+
		"\u00a8\u0005\f\u0000\u0000\u00a8\u00c5\u0003\n\u0005\u001d\u00a9\u00aa"+
		"\u0005\r\u0000\u0000\u00aa\u00c5\u0003\n\u0005\u001c\u00ab\u00ac\u0005"+
		"\u0005\u0000\u0000\u00ac\u00c5\u0003\n\u0005\u001b\u00ad\u00ae\u0005\u0006"+
		"\u0000\u0000\u00ae\u00c5\u0003\n\u0005\u001a\u00af\u00b0\u0005\u000e\u0000"+
		"\u0000\u00b0\u00c5\u0003\n\u0005\u0019\u00b1\u00b2\u0005\u000f\u0000\u0000"+
		"\u00b2\u00c5\u0003\n\u0005\u0018\u00b3\u00b4\u0005\u0010\u0000\u0000\u00b4"+
		"\u00c5\u0003\n\u0005\u0017\u00b5\u00b6\u0005\u0011\u0000\u0000\u00b6\u00c5"+
		"\u0003\n\u0005\u0016\u00b7\u00b8\u0005\u0001\u0000\u0000\u00b8\u00b9\u0003"+
		"2\u0019\u0000\u00b9\u00ba\u0005\u0003\u0000\u0000\u00ba\u00bb\u0003\n"+
		"\u0005\b\u00bb\u00c5\u0001\u0000\u0000\u0000\u00bc\u00c5\u0005S\u0000"+
		"\u0000\u00bd\u00c5\u0005n\u0000\u0000\u00be\u00c5\u0005]\u0000\u0000\u00bf"+
		"\u00c5\u0003l6\u0000\u00c0\u00c1\u0005\u0001\u0000\u0000\u00c1\u00c2\u0003"+
		"\u0006\u0003\u0000\u00c2\u00c3\u0005\u0003\u0000\u0000\u00c3\u00c5\u0001"+
		"\u0000\u0000\u0000\u00c4\u00a2\u0001\u0000\u0000\u0000\u00c4\u00a4\u0001"+
		"\u0000\u0000\u0000\u00c4\u00a7\u0001\u0000\u0000\u0000\u00c4\u00a9\u0001"+
		"\u0000\u0000\u0000\u00c4\u00ab\u0001\u0000\u0000\u0000\u00c4\u00ad\u0001"+
		"\u0000\u0000\u0000\u00c4\u00af\u0001\u0000\u0000\u0000\u00c4\u00b1\u0001"+
		"\u0000\u0000\u0000\u00c4\u00b3\u0001\u0000\u0000\u0000\u00c4\u00b5\u0001"+
		"\u0000\u0000\u0000\u00c4\u00b7\u0001\u0000\u0000\u0000\u00c4\u00bc\u0001"+
		"\u0000\u0000\u0000\u00c4\u00bd\u0001\u0000\u0000\u0000\u00c4\u00be\u0001"+
		"\u0000\u0000\u0000\u00c4\u00bf\u0001\u0000\u0000\u0000\u00c4\u00c0\u0001"+
		"\u0000\u0000\u0000\u00c5\u010a\u0001\u0000\u0000\u0000\u00c6\u00c7\n\u0015"+
		"\u0000\u0000\u00c7\u00c8\u0007\u0000\u0000\u0000\u00c8\u0109\u0003\n\u0005"+
		"\u0016\u00c9\u00ca\n\u0014\u0000\u0000\u00ca\u00cb\u0007\u0001\u0000\u0000"+
		"\u00cb\u0109\u0003\n\u0005\u0015\u00cc\u00cd\n\u0013\u0000\u0000\u00cd"+
		"\u00ce\u0005\u0014\u0000\u0000\u00ce\u0109\u0003\n\u0005\u0014\u00cf\u00d0"+
		"\n\u0012\u0000\u0000\u00d0\u00d1\u0007\u0002\u0000\u0000\u00d1\u0109\u0003"+
		"\n\u0005\u0013\u00d2\u00d3\n\u0011\u0000\u0000\u00d3\u00d4\u0007\u0003"+
		"\u0000\u0000\u00d4\u0109\u0003\n\u0005\u0012\u00d5\u00d6\n\u0010\u0000"+
		"\u0000\u00d6\u00d7\u0005H\u0000\u0000\u00d7\u0109\u0003\n\u0005\u0011"+
		"\u00d8\u00d9\n\u000f\u0000\u0000\u00d9\u00da\u0007\u0004\u0000\u0000\u00da"+
		"\u0109\u0003\n\u0005\u0010\u00db\u00dc\n\u000e\u0000\u0000\u00dc\u00dd"+
		"\u0005\f\u0000\u0000\u00dd\u0109\u0003\n\u0005\u000f\u00de\u00df\n\r\u0000"+
		"\u0000\u00df\u00e0\u0005\u0004\u0000\u0000\u00e0\u0109\u0003\n\u0005\u000e"+
		"\u00e1\u00e2\n\f\u0000\u0000\u00e2\u00e3\u0005 \u0000\u0000\u00e3\u0109"+
		"\u0003\n\u0005\r\u00e4\u00e5\n\u000b\u0000\u0000\u00e5\u00e6\u0005!\u0000"+
		"\u0000\u00e6\u0109\u0003\n\u0005\f\u00e7\u00e8\n\n\u0000\u0000\u00e8\u00e9"+
		"\u0005\"\u0000\u0000\u00e9\u0109\u0003\n\u0005\u000b\u00ea\u00eb\n\t\u0000"+
		"\u0000\u00eb\u00ec\u0005#\u0000\u0000\u00ec\u00ed\u0003\n\u0005\u0000"+
		"\u00ed\u00ee\u0005$\u0000\u0000\u00ee\u00ef\u0003\n\u0005\n\u00ef\u0109"+
		"\u0001\u0000\u0000\u0000\u00f0\u00f1\n\u0007\u0000\u0000\u00f1\u00f2\u0005"+
		"%\u0000\u0000\u00f2\u0109\u0003\n\u0005\u0007\u00f3\u00f4\n\u0006\u0000"+
		"\u0000\u00f4\u00f5\u0003\f\u0006\u0000\u00f5\u00f6\u0003\n\u0005\u0006"+
		"\u00f6\u0109\u0001\u0000\u0000\u0000\u00f7\u00f8\n$\u0000\u0000\u00f8"+
		"\u0109\u0003\u0004\u0002\u0000\u00f9\u00fa\n#\u0000\u0000\u00fa\u0109"+
		"\u0005\u0005\u0000\u0000\u00fb\u00fc\n\"\u0000\u0000\u00fc\u0109\u0005"+
		"\u0006\u0000\u0000\u00fd\u00fe\n \u0000\u0000\u00fe\u00ff\u0005\u0007"+
		"\u0000\u0000\u00ff\u0100\u0003\n\u0005\u0000\u0100\u0101\u0005\b\u0000"+
		"\u0000\u0101\u0109\u0001\u0000\u0000\u0000\u0102\u0103\n\u001f\u0000\u0000"+
		"\u0103\u0105\u0007\u0005\u0000\u0000\u0104\u0106\u0005\u000b\u0000\u0000"+
		"\u0105\u0104\u0001\u0000\u0000\u0000\u0105\u0106\u0001\u0000\u0000\u0000"+
		"\u0106\u0107\u0001\u0000\u0000\u0000\u0107\u0109\u0005n\u0000\u0000\u0108"+
		"\u00c6\u0001\u0000\u0000\u0000\u0108\u00c9\u0001\u0000\u0000\u0000\u0108"+
		"\u00cc\u0001\u0000\u0000\u0000\u0108\u00cf\u0001\u0000\u0000\u0000\u0108"+
		"\u00d2\u0001\u0000\u0000\u0000\u0108\u00d5\u0001\u0000\u0000\u0000\u0108"+
		"\u00d8\u0001\u0000\u0000\u0000\u0108\u00db\u0001\u0000\u0000\u0000\u0108"+
		"\u00de\u0001\u0000\u0000\u0000\u0108\u00e1\u0001\u0000\u0000\u0000\u0108"+
		"\u00e4\u0001\u0000\u0000\u0000\u0108\u00e7\u0001\u0000\u0000\u0000\u0108"+
		"\u00ea\u0001\u0000\u0000\u0000\u0108\u00f0\u0001\u0000\u0000\u0000\u0108"+
		"\u00f3\u0001\u0000\u0000\u0000\u0108\u00f7\u0001\u0000\u0000\u0000\u0108"+
		"\u00f9\u0001\u0000\u0000\u0000\u0108\u00fb\u0001\u0000\u0000\u0000\u0108"+
		"\u00fd\u0001\u0000\u0000\u0000\u0108\u0102\u0001\u0000\u0000\u0000\u0109"+
		"\u010c\u0001\u0000\u0000\u0000\u010a\u0108\u0001\u0000\u0000\u0000\u010a"+
		"\u010b\u0001\u0000\u0000\u0000\u010b\u000b\u0001\u0000\u0000\u0000\u010c"+
		"\u010a\u0001\u0000\u0000\u0000\u010d\u010e\u0007\u0006\u0000\u0000\u010e"+
		"\r\u0001\u0000\u0000\u0000\u010f\u0110\u00053\u0000\u0000\u0110\u000f"+
		"\u0001\u0000\u0000\u0000\u0111\u0112\u0005X\u0000\u0000\u0112\u0113\u0005"+
		"n\u0000\u0000\u0113\u0117\u00054\u0000\u0000\u0114\u0116\u0003\u0012\t"+
		"\u0000\u0115\u0114\u0001\u0000\u0000\u0000\u0116\u0119\u0001\u0000\u0000"+
		"\u0000\u0117\u0115\u0001\u0000\u0000\u0000\u0117\u0118\u0001\u0000\u0000"+
		"\u0000\u0118\u011a\u0001\u0000\u0000\u0000\u0119\u0117\u0001\u0000\u0000"+
		"\u0000\u011a\u011b\u0005o\u0000\u0000\u011b\u0011\u0001\u0000\u0000\u0000"+
		"\u011c\u011d\u00032\u0019\u0000\u011d\u011f\u0005n\u0000\u0000\u011e\u0120"+
		"\u0003\u0014\n\u0000\u011f\u011e\u0001\u0000\u0000\u0000\u011f\u0120\u0001"+
		"\u0000\u0000\u0000\u0120\u0121\u0001\u0000\u0000\u0000\u0121\u0122\u0003"+
		"n7\u0000\u0122\u0127\u0001\u0000\u0000\u0000\u0123\u0124\u0003Z-\u0000"+
		"\u0124\u0125\u0003n7\u0000\u0125\u0127\u0001\u0000\u0000\u0000\u0126\u011c"+
		"\u0001\u0000\u0000\u0000\u0126\u0123\u0001\u0000\u0000\u0000\u0127\u0013"+
		"\u0001\u0000\u0000\u0000\u0128\u0129\u0005\u0007\u0000\u0000\u0129\u012a"+
		"\u0005h\u0000\u0000\u012a\u012b\u0005\b\u0000\u0000\u012b\u0015\u0001"+
		"\u0000\u0000\u0000\u012c\u012e\u0005b\u0000\u0000\u012d\u012c\u0001\u0000"+
		"\u0000\u0000\u012d\u012e\u0001\u0000\u0000\u0000\u012e\u012f\u0001\u0000"+
		"\u0000\u0000\u012f\u0130\u00032\u0019\u0000\u0130\u0132\u0005n\u0000\u0000"+
		"\u0131\u0133\u0003\u0014\n\u0000\u0132\u0131\u0001\u0000\u0000\u0000\u0132"+
		"\u0133\u0001\u0000\u0000\u0000\u0133\u0136\u0001\u0000\u0000\u0000\u0134"+
		"\u0135\u0005%\u0000\u0000\u0135\u0137\u0003\n\u0005\u0000\u0136\u0134"+
		"\u0001\u0000\u0000\u0000\u0136\u0137\u0001\u0000\u0000\u0000\u0137\u013d"+
		"\u0001\u0000\u0000\u0000\u0138\u013a\u0005b\u0000\u0000\u0139\u0138\u0001"+
		"\u0000\u0000\u0000\u0139\u013a\u0001\u0000\u0000\u0000\u013a\u013b\u0001"+
		"\u0000\u0000\u0000\u013b\u013d\u0003Z-\u0000\u013c\u012d\u0001\u0000\u0000"+
		"\u0000\u013c\u0139\u0001\u0000\u0000\u0000\u013d\u0017\u0001\u0000\u0000"+
		"\u0000\u013e\u013f\u0003\b\u0004\u0000\u013f\u0140\u0003n7\u0000\u0140"+
		"\u0152\u0001\u0000\u0000\u0000\u0141\u0142\u0003\u0016\u000b\u0000\u0142"+
		"\u0143\u0003n7\u0000\u0143\u0152\u0001\u0000\u0000\u0000\u0144\u0152\u0003"+
		"\"\u0011\u0000\u0145\u0152\u00030\u0018\u0000\u0146\u0152\u0003\u001a"+
		"\r\u0000\u0147\u0152\u0003\u001c\u000e\u0000\u0148\u0152\u0003\u001e\u000f"+
		"\u0000\u0149\u0152\u0003(\u0014\u0000\u014a\u0152\u0003 \u0010\u0000\u014b"+
		"\u0152\u0003$\u0012\u0000\u014c\u0152\u0003*\u0015\u0000\u014d\u014e\u0003"+
		"\n\u0005\u0000\u014e\u014f\u0003n7\u0000\u014f\u0152\u0001\u0000\u0000"+
		"\u0000\u0150\u0152\u0003\u000e\u0007\u0000\u0151\u013e\u0001\u0000\u0000"+
		"\u0000\u0151\u0141\u0001\u0000\u0000\u0000\u0151\u0144\u0001\u0000\u0000"+
		"\u0000\u0151\u0145\u0001\u0000\u0000\u0000\u0151\u0146\u0001\u0000\u0000"+
		"\u0000\u0151\u0147\u0001\u0000\u0000\u0000\u0151\u0148\u0001\u0000\u0000"+
		"\u0000\u0151\u0149\u0001\u0000\u0000\u0000\u0151\u014a\u0001\u0000\u0000"+
		"\u0000\u0151\u014b\u0001\u0000\u0000\u0000\u0151\u014c\u0001\u0000\u0000"+
		"\u0000\u0151\u014d\u0001\u0000\u0000\u0000\u0151\u0150\u0001\u0000\u0000"+
		"\u0000\u0152\u0019\u0001\u0000\u0000\u0000\u0153\u0154\u0005P\u0000\u0000"+
		"\u0154\u0155\u0003n7\u0000\u0155\u001b\u0001\u0000\u0000\u0000\u0156\u0157"+
		"\u0005F\u0000\u0000\u0157\u0158\u0003n7\u0000\u0158\u001d\u0001\u0000"+
		"\u0000\u0000\u0159\u015a\u0005U\u0000\u0000\u015a\u015b\u0003\n\u0005"+
		"\u0000\u015b\u015c\u0003n7\u0000\u015c\u001f\u0001\u0000\u0000\u0000\u015d"+
		"\u015f\u0005N\u0000\u0000\u015e\u0160\u0003\n\u0005\u0000\u015f\u015e"+
		"\u0001\u0000\u0000\u0000\u015f\u0160\u0001\u0000\u0000\u0000\u0160\u0161"+
		"\u0001\u0000\u0000\u0000\u0161\u0162\u0003n7\u0000\u0162!\u0001\u0000"+
		"\u0000\u0000\u0163\u0164\u0003\n\u0005\u0000\u0164\u0165\u0007\u0007\u0000"+
		"\u0000\u0165\u0166\u00030\u0018\u0000\u0166#\u0001\u0000\u0000\u0000\u0167"+
		"\u0168\u0005R\u0000\u0000\u0168\u0169\u0003\n\u0005\u0000\u0169\u016a"+
		"\u00030\u0018\u0000\u016a\u0176\u0001\u0000\u0000\u0000\u016b\u016c\u0005"+
		"Q\u0000\u0000\u016c\u016d\u0005\u0001\u0000\u0000\u016d\u016e\u0003&\u0013"+
		"\u0000\u016e\u016f\u0005\u0003\u0000\u0000\u016f\u0170\u00030\u0018\u0000"+
		"\u0170\u0176\u0001\u0000\u0000\u0000\u0171\u0172\u0005Q\u0000\u0000\u0172"+
		"\u0173\u0003&\u0013\u0000\u0173\u0174\u00030\u0018\u0000\u0174\u0176\u0001"+
		"\u0000\u0000\u0000\u0175\u0167\u0001\u0000\u0000\u0000\u0175\u016b\u0001"+
		"\u0000\u0000\u0000\u0175\u0171\u0001\u0000\u0000\u0000\u0176%\u0001\u0000"+
		"\u0000\u0000\u0177\u017c\u0003\u0016\u000b\u0000\u0178\u017a\u0003\n\u0005"+
		"\u0000\u0179\u0178\u0001\u0000\u0000\u0000\u0179\u017a\u0001\u0000\u0000"+
		"\u0000\u017a\u017c\u0001\u0000\u0000\u0000\u017b\u0177\u0001\u0000\u0000"+
		"\u0000\u017b\u0179\u0001\u0000\u0000\u0000\u017c\u017d\u0001\u0000\u0000"+
		"\u0000\u017d\u017f\u00053\u0000\u0000\u017e\u0180\u0003\n\u0005\u0000"+
		"\u017f\u017e\u0001\u0000\u0000\u0000\u017f\u0180\u0001\u0000\u0000\u0000"+
		"\u0180\u0181\u0001\u0000\u0000\u0000\u0181\u0183\u00053\u0000\u0000\u0182"+
		"\u0184\u0003\n\u0005\u0000\u0183\u0182\u0001\u0000\u0000\u0000\u0183\u0184"+
		"\u0001\u0000\u0000\u0000\u0184\'\u0001\u0000\u0000\u0000\u0185\u0186\u0005"+
		"T\u0000\u0000\u0186\u0187\u0003\n\u0005\u0000\u0187\u018e\u00030\u0018"+
		"\u0000\u0188\u0189\u00055\u0000\u0000\u0189\u018a\u0003\n\u0005\u0000"+
		"\u018a\u018b\u00030\u0018\u0000\u018b\u018d\u0001\u0000\u0000\u0000\u018c"+
		"\u0188\u0001\u0000\u0000\u0000\u018d\u0190\u0001\u0000\u0000\u0000\u018e"+
		"\u018c\u0001\u0000\u0000\u0000\u018e\u018f\u0001\u0000\u0000\u0000\u018f"+
		"\u0193\u0001\u0000\u0000\u0000\u0190\u018e\u0001\u0000\u0000\u0000\u0191"+
		"\u0192\u0005J\u0000\u0000\u0192\u0194\u00030\u0018\u0000\u0193\u0191\u0001"+
		"\u0000\u0000\u0000\u0193\u0194\u0001\u0000\u0000\u0000\u0194)\u0001\u0000"+
		"\u0000\u0000\u0195\u0196\u0005V\u0000\u0000\u0196\u0198\u00030\u0018\u0000"+
		"\u0197\u0199\u0003,\u0016\u0000\u0198\u0197\u0001\u0000\u0000\u0000\u0199"+
		"\u019a\u0001\u0000\u0000\u0000\u019a\u0198\u0001\u0000\u0000\u0000\u019a"+
		"\u019b\u0001\u0000\u0000\u0000\u019b\u019d\u0001\u0000\u0000\u0000\u019c"+
		"\u019e\u0003.\u0017\u0000\u019d\u019c\u0001\u0000\u0000\u0000\u019d\u019e"+
		"\u0001\u0000\u0000\u0000\u019e\u01a4\u0001\u0000\u0000\u0000\u019f\u01a0"+
		"\u0005V\u0000\u0000\u01a0\u01a1\u00030\u0018\u0000\u01a1\u01a2\u0003."+
		"\u0017\u0000\u01a2\u01a4\u0001\u0000\u0000\u0000\u01a3\u0195\u0001\u0000"+
		"\u0000\u0000\u01a3\u019f\u0001\u0000\u0000\u0000\u01a4+\u0001\u0000\u0000"+
		"\u0000\u01a5\u01a6\u0005L\u0000\u0000\u01a6\u01a7\u0005\u0001\u0000\u0000"+
		"\u01a7\u01a9\u0003@ \u0000\u01a8\u01aa\u0005n\u0000\u0000\u01a9\u01a8"+
		"\u0001\u0000\u0000\u0000\u01a9\u01aa\u0001\u0000\u0000\u0000\u01aa\u01ab"+
		"\u0001\u0000\u0000\u0000\u01ab\u01ac\u0005\u0003\u0000\u0000\u01ac\u01ad"+
		"\u00030\u0018\u0000\u01ad-\u0001\u0000\u0000\u0000\u01ae\u01af\u0005M"+
		"\u0000\u0000\u01af\u01b0\u00030\u0018\u0000\u01b0/\u0001\u0000\u0000\u0000"+
		"\u01b1\u01b5\u00054\u0000\u0000\u01b2\u01b4\u0003\u0018\f\u0000\u01b3"+
		"\u01b2\u0001\u0000\u0000\u0000\u01b4\u01b7\u0001\u0000\u0000\u0000\u01b5"+
		"\u01b3\u0001\u0000\u0000\u0000\u01b5\u01b6\u0001\u0000\u0000\u0000\u01b6"+
		"\u01b8\u0001\u0000\u0000\u0000\u01b7\u01b5\u0001\u0000\u0000\u0000\u01b8"+
		"\u01b9\u0005o\u0000\u0000\u01b91\u0001\u0000\u0000\u0000\u01ba\u01bc\u0003"+
		"<\u001e\u0000\u01bb\u01ba\u0001\u0000\u0000\u0000\u01bb\u01bc\u0001\u0000"+
		"\u0000\u0000\u01bc\u01bd\u0001\u0000\u0000\u0000\u01bd\u01bf\u0003B!\u0000"+
		"\u01be\u01c0\u0003\u0014\n\u0000\u01bf\u01be\u0001\u0000\u0000\u0000\u01bf"+
		"\u01c0\u0001\u0000\u0000\u0000\u01c0\u01cc\u0001\u0000\u0000\u0000\u01c1"+
		"\u01cc\u00034\u001a\u0000\u01c2\u01cc\u0003>\u001f\u0000\u01c3\u01cc\u0003"+
		"@ \u0000\u01c4\u01c6\u0003<\u001e\u0000\u01c5\u01c4\u0001\u0000\u0000"+
		"\u0000\u01c5\u01c6\u0001\u0000\u0000\u0000\u01c6\u01c8\u0001\u0000\u0000"+
		"\u0000\u01c7\u01c9\u0005X\u0000\u0000\u01c8\u01c7\u0001\u0000\u0000\u0000"+
		"\u01c8\u01c9\u0001\u0000\u0000\u0000\u01c9\u01ca\u0001\u0000\u0000\u0000"+
		"\u01ca\u01cc\u0005n\u0000\u0000\u01cb\u01bb\u0001\u0000\u0000\u0000\u01cb"+
		"\u01c1\u0001\u0000\u0000\u0000\u01cb\u01c2\u0001\u0000\u0000\u0000\u01cb"+
		"\u01c3\u0001\u0000\u0000\u0000\u01cb\u01c5\u0001\u0000\u0000\u0000\u01cc"+
		"3\u0001\u0000\u0000\u0000\u01cd\u01ce\u0005\u0004\u0000\u0000\u01ce\u01cf"+
		"\u00032\u0019\u0000\u01cf\u01d0\u0003X,\u0000\u01d05\u0001\u0000\u0000"+
		"\u0000\u01d1\u01d3\u00032\u0019\u0000\u01d2\u01d4\u0005n\u0000\u0000\u01d3"+
		"\u01d2\u0001\u0000\u0000\u0000\u01d3\u01d4\u0001\u0000\u0000\u0000\u01d4"+
		"7\u0001\u0000\u0000\u0000\u01d5\u01d6\u00056\u0000\u0000\u01d6\u01d7\u0005"+
		"\u0001\u0000\u0000\u01d7\u01d8\u0005\u0001\u0000\u0000\u01d8\u01d9\u0005"+
		"n\u0000\u0000\u01d9\u01da\u0005\u0003\u0000\u0000\u01da\u01db\u0005\u0003"+
		"\u0000\u0000\u01db9\u0001\u0000\u0000\u0000\u01dc\u01dd\u00032\u0019\u0000"+
		"\u01dd\u01e1\u0003X,\u0000\u01de\u01e0\u00038\u001c\u0000\u01df\u01de"+
		"\u0001\u0000\u0000\u0000\u01e0\u01e3\u0001\u0000\u0000\u0000\u01e1\u01df"+
		"\u0001\u0000\u0000\u0000\u01e1\u01e2\u0001\u0000\u0000\u0000\u01e2;\u0001"+
		"\u0000\u0000\u0000\u01e3\u01e1\u0001\u0000\u0000\u0000\u01e4\u01e5\u0007"+
		"\b\u0000\u0000\u01e5=\u0001\u0000\u0000\u0000\u01e6\u01e8\u0003<\u001e"+
		"\u0000\u01e7\u01e6\u0001\u0000\u0000\u0000\u01e7\u01e8\u0001\u0000\u0000"+
		"\u0000\u01e8\u01ee\u0001\u0000\u0000\u0000\u01e9\u01ef\u0003B!\u0000\u01ea"+
		"\u01ec\u0005X\u0000\u0000\u01eb\u01ea\u0001\u0000\u0000\u0000\u01eb\u01ec"+
		"\u0001\u0000\u0000\u0000\u01ec\u01ed\u0001\u0000\u0000\u0000\u01ed\u01ef"+
		"\u0005n\u0000\u0000\u01ee\u01e9\u0001\u0000\u0000\u0000\u01ee\u01eb\u0001"+
		"\u0000\u0000\u0000\u01ef\u01fd\u0001\u0000\u0000\u0000\u01f0\u01f2\u0003"+
		"<\u001e\u0000\u01f1\u01f0\u0001\u0000\u0000\u0000\u01f2\u01f5\u0001\u0000"+
		"\u0000\u0000\u01f3\u01f1\u0001\u0000\u0000\u0000\u01f3\u01f4\u0001\u0000"+
		"\u0000\u0000\u01f4\u01f6\u0001\u0000\u0000\u0000\u01f5\u01f3\u0001\u0000"+
		"\u0000\u0000\u01f6\u01fa\u0005\r\u0000\u0000\u01f7\u01f9\u0003<\u001e"+
		"\u0000\u01f8\u01f7\u0001\u0000\u0000\u0000\u01f9\u01fc\u0001\u0000\u0000"+
		"\u0000\u01fa\u01f8\u0001\u0000\u0000\u0000\u01fa\u01fb\u0001\u0000\u0000"+
		"\u0000\u01fb\u01fe\u0001\u0000\u0000\u0000\u01fc\u01fa\u0001\u0000\u0000"+
		"\u0000\u01fd\u01f3\u0001\u0000\u0000\u0000\u01fe\u01ff\u0001\u0000\u0000"+
		"\u0000\u01ff\u01fd\u0001\u0000\u0000\u0000\u01ff\u0200\u0001\u0000\u0000"+
		"\u0000\u0200?\u0001\u0000\u0000\u0000\u0201\u0203\u0005X\u0000\u0000\u0202"+
		"\u0201\u0001\u0000\u0000\u0000\u0202\u0203\u0001\u0000\u0000\u0000\u0203"+
		"\u0204\u0001\u0000\u0000\u0000\u0204\u0205\u0005n\u0000\u0000\u0205\u0206"+
		"\u0005:\u0000\u0000\u0206A\u0001\u0000\u0000\u0000\u0207\u021f\u0005;"+
		"\u0000\u0000\u0208\u021f\u0005<\u0000\u0000\u0209\u021f\u0005=\u0000\u0000"+
		"\u020a\u021f\u0005>\u0000\u0000\u020b\u021f\u0005?\u0000\u0000\u020c\u021f"+
		"\u0005@\u0000\u0000\u020d\u021f\u0005O\u0000\u0000\u020e\u021f\u0005A"+
		"\u0000\u0000\u020f\u0210\u0005A\u0000\u0000\u0210\u021f\u0005A\u0000\u0000"+
		"\u0211\u0212\u0005A\u0000\u0000\u0212\u021f\u0005>\u0000\u0000\u0213\u0214"+
		"\u0005B\u0000\u0000\u0214\u021f\u0005?\u0000\u0000\u0215\u0216\u0005B"+
		"\u0000\u0000\u0216\u021f\u0005;\u0000\u0000\u0217\u0218\u0005B\u0000\u0000"+
		"\u0218\u021f\u0005<\u0000\u0000\u0219\u021a\u0005B\u0000\u0000\u021a\u021f"+
		"\u0005A\u0000\u0000\u021b\u021c\u0005B\u0000\u0000\u021c\u021d\u0005A"+
		"\u0000\u0000\u021d\u021f\u0005A\u0000\u0000\u021e\u0207\u0001\u0000\u0000"+
		"\u0000\u021e\u0208\u0001\u0000\u0000\u0000\u021e\u0209\u0001\u0000\u0000"+
		"\u0000\u021e\u020a\u0001\u0000\u0000\u0000\u021e\u020b\u0001\u0000\u0000"+
		"\u0000\u021e\u020c\u0001\u0000\u0000\u0000\u021e\u020d\u0001\u0000\u0000"+
		"\u0000\u021e\u020e\u0001\u0000\u0000\u0000\u021e\u020f\u0001\u0000\u0000"+
		"\u0000\u021e\u0211\u0001\u0000\u0000\u0000\u021e\u0213\u0001\u0000\u0000"+
		"\u0000\u021e\u0215\u0001\u0000\u0000\u0000\u021e\u0217\u0001\u0000\u0000"+
		"\u0000\u021e\u0219\u0001\u0000\u0000\u0000\u021e\u021b\u0001\u0000\u0000"+
		"\u0000\u021fC\u0001\u0000\u0000\u0000\u0220\u0221\u0005Z\u0000\u0000\u0221"+
		"\u0222\u0005n\u0000\u0000\u0222\u0223\u00054\u0000\u0000\u0223\u0228\u0003"+
		"F#\u0000\u0224\u0225\u0005\u0002\u0000\u0000\u0225\u0227\u0003F#\u0000"+
		"\u0226\u0224\u0001\u0000\u0000\u0000\u0227\u022a\u0001\u0000\u0000\u0000"+
		"\u0228\u0226\u0001\u0000\u0000\u0000\u0228\u0229\u0001\u0000\u0000\u0000"+
		"\u0229\u022c\u0001\u0000\u0000\u0000\u022a\u0228\u0001\u0000\u0000\u0000"+
		"\u022b\u022d\u0005\u0002\u0000\u0000\u022c\u022b\u0001\u0000\u0000\u0000"+
		"\u022c\u022d\u0001\u0000\u0000\u0000\u022d\u022e\u0001\u0000\u0000\u0000"+
		"\u022e\u022f\u0005o\u0000\u0000\u022f\u0230\u0003n7\u0000\u0230E\u0001"+
		"\u0000\u0000\u0000\u0231\u0234\u0005n\u0000\u0000\u0232\u0233\u0005%\u0000"+
		"\u0000\u0233\u0235\u0005h\u0000\u0000\u0234\u0232\u0001\u0000\u0000\u0000"+
		"\u0234\u0235\u0001\u0000\u0000\u0000\u0235G\u0001\u0000\u0000\u0000\u0236"+
		"\u0237\u0005^\u0000\u0000\u0237\u0238\u0005n\u0000\u0000\u0238\u0239\u0003"+
		"J%\u0000\u0239I\u0001\u0000\u0000\u0000\u023a\u023e\u00054\u0000\u0000"+
		"\u023b\u023d\u0003R)\u0000\u023c\u023b\u0001\u0000\u0000\u0000\u023d\u0240"+
		"\u0001\u0000\u0000\u0000\u023e\u023c\u0001\u0000\u0000\u0000\u023e\u023f"+
		"\u0001\u0000\u0000\u0000\u023f\u0241\u0001\u0000\u0000\u0000\u0240\u023e"+
		"\u0001\u0000\u0000\u0000\u0241\u0242\u0005o\u0000\u0000\u0242K\u0001\u0000"+
		"\u0000\u0000\u0243\u0245\u0005Y\u0000\u0000\u0244\u0246\u0005e\u0000\u0000"+
		"\u0245\u0244\u0001\u0000\u0000\u0000\u0245\u0246\u0001\u0000\u0000\u0000"+
		"\u0246\u0247\u0001\u0000\u0000\u0000\u0247\u024a\u0005n\u0000\u0000\u0248"+
		"\u0249\u0005[\u0000\u0000\u0249\u024b\u0005n\u0000\u0000\u024a\u0248\u0001"+
		"\u0000\u0000\u0000\u024a\u024b\u0001\u0000\u0000\u0000\u024b\u024c\u0001"+
		"\u0000\u0000\u0000\u024c\u024d\u0003N\'\u0000\u024d\u024e\u0003n7\u0000"+
		"\u024eM\u0001\u0000\u0000\u0000\u024f\u0254\u00054\u0000\u0000\u0250\u0253"+
		"\u0003P(\u0000\u0251\u0253\u0003R)\u0000\u0252\u0250\u0001\u0000\u0000"+
		"\u0000\u0252\u0251\u0001\u0000\u0000\u0000\u0253\u0256\u0001\u0000\u0000"+
		"\u0000\u0254\u0252\u0001\u0000\u0000\u0000\u0254\u0255\u0001\u0000\u0000"+
		"\u0000\u0255\u0257\u0001\u0000\u0000\u0000\u0256\u0254\u0001\u0000\u0000"+
		"\u0000\u0257\u0258\u0005o\u0000\u0000\u0258O\u0001\u0000\u0000\u0000\u0259"+
		"\u025a\u00032\u0019\u0000\u025a\u025c\u0005n\u0000\u0000\u025b\u025d\u0003"+
		"\u0014\n\u0000\u025c\u025b\u0001\u0000\u0000\u0000\u025c\u025d\u0001\u0000"+
		"\u0000\u0000\u025d\u025f\u0001\u0000\u0000\u0000\u025e\u0260\u0003T*\u0000"+
		"\u025f\u025e\u0001\u0000\u0000\u0000\u025f\u0260\u0001\u0000\u0000\u0000"+
		"\u0260\u0261\u0001\u0000\u0000\u0000\u0261\u0262\u0003n7\u0000\u0262\u026a"+
		"\u0001\u0000\u0000\u0000\u0263\u0265\u0003Z-\u0000\u0264\u0266\u0003T"+
		"*\u0000\u0265\u0264\u0001\u0000\u0000\u0000\u0265\u0266\u0001\u0000\u0000"+
		"\u0000\u0266\u0267\u0001\u0000\u0000\u0000\u0267\u0268\u0003n7\u0000\u0268"+
		"\u026a\u0001\u0000\u0000\u0000\u0269\u0259\u0001\u0000\u0000\u0000\u0269"+
		"\u0263\u0001\u0000\u0000\u0000\u026aQ\u0001\u0000\u0000\u0000\u026b\u026e"+
		"\u0003\\.\u0000\u026c\u026e\u0003b1\u0000\u026d\u026b\u0001\u0000\u0000"+
		"\u0000\u026d\u026c\u0001\u0000\u0000\u0000\u026eS\u0001\u0000\u0000\u0000"+
		"\u026f\u0270\u0005%\u0000\u0000\u0270\u0271\u0003\n\u0005\u0000\u0271"+
		"U\u0001\u0000\u0000\u0000\u0272\u0274\u00032\u0019\u0000\u0273\u0275\u0005"+
		"n\u0000\u0000\u0274\u0273\u0001\u0000\u0000\u0000\u0274\u0275\u0001\u0000"+
		"\u0000\u0000\u0275\u0278\u0001\u0000\u0000\u0000\u0276\u0278\u0003Z-\u0000"+
		"\u0277\u0272\u0001\u0000\u0000\u0000\u0277\u0276\u0001\u0000\u0000\u0000"+
		"\u0278W\u0001\u0000\u0000\u0000\u0279\u0282\u0005\u0001\u0000\u0000\u027a"+
		"\u027f\u0003V+\u0000\u027b\u027c\u0005\u0002\u0000\u0000\u027c\u027e\u0003"+
		"V+\u0000\u027d\u027b\u0001\u0000\u0000\u0000\u027e\u0281\u0001\u0000\u0000"+
		"\u0000\u027f\u027d\u0001\u0000\u0000\u0000\u027f\u0280\u0001\u0000\u0000"+
		"\u0000\u0280\u0283\u0001\u0000\u0000\u0000\u0281\u027f\u0001\u0000\u0000"+
		"\u0000\u0282\u027a\u0001\u0000\u0000\u0000\u0282\u0283\u0001\u0000\u0000"+
		"\u0000\u0283\u0285\u0001\u0000\u0000\u0000\u0284\u0286\u0005\u0002\u0000"+
		"\u0000\u0285\u0284\u0001\u0000\u0000\u0000\u0285\u0286\u0001\u0000\u0000"+
		"\u0000\u0286\u0287\u0001\u0000\u0000\u0000\u0287\u028a\u0005\u0003\u0000"+
		"\u0000\u0288\u028a\u0001\u0000\u0000\u0000\u0289\u0279\u0001\u0000\u0000"+
		"\u0000\u0289\u0288\u0001\u0000\u0000\u0000\u028aY\u0001\u0000\u0000\u0000"+
		"\u028b\u028c\u00032\u0019\u0000\u028c\u028e\u0005\u0001\u0000\u0000\u028d"+
		"\u028f\u0005\r\u0000\u0000\u028e\u028d\u0001\u0000\u0000\u0000\u028f\u0290"+
		"\u0001\u0000\u0000\u0000\u0290\u028e\u0001\u0000\u0000\u0000\u0290\u0291"+
		"\u0001\u0000\u0000\u0000\u0291\u0293\u0001\u0000\u0000\u0000\u0292\u0294"+
		"\u0005n\u0000\u0000\u0293\u0292\u0001\u0000\u0000\u0000\u0293\u0294\u0001"+
		"\u0000\u0000\u0000\u0294\u0295\u0001\u0000\u0000\u0000\u0295\u0296\u0005"+
		"\u0003\u0000\u0000\u0296\u029a\u0003X,\u0000\u0297\u0299\u00038\u001c"+
		"\u0000\u0298\u0297\u0001\u0000\u0000\u0000\u0299\u029c\u0001\u0000\u0000"+
		"\u0000\u029a\u0298\u0001\u0000\u0000\u0000\u029a\u029b\u0001\u0000\u0000"+
		"\u0000\u029b[\u0001\u0000\u0000\u0000\u029c\u029a\u0001\u0000\u0000\u0000"+
		"\u029d\u029e\u00032\u0019\u0000\u029e\u029f\u0005n\u0000\u0000\u029f\u02a0"+
		"\u0003X,\u0000\u02a0\u02a1\u00030\u0018\u0000\u02a1]\u0001\u0000\u0000"+
		"\u0000\u02a2\u02a4\u0005b\u0000\u0000\u02a3\u02a2\u0001\u0000\u0000\u0000"+
		"\u02a3\u02a4\u0001\u0000\u0000\u0000\u02a4\u02a5\u0001\u0000\u0000\u0000"+
		"\u02a5\u02ab\u0003\\.\u0000\u02a6\u02a8\u0005b\u0000\u0000\u02a7\u02a6"+
		"\u0001\u0000\u0000\u0000\u02a7\u02a8\u0001\u0000\u0000\u0000\u02a8\u02a9"+
		"\u0001\u0000\u0000\u0000\u02a9\u02ab\u0003b1\u0000\u02aa\u02a3\u0001\u0000"+
		"\u0000\u0000\u02aa\u02a7\u0001\u0000\u0000\u0000\u02ab_\u0001\u0000\u0000"+
		"\u0000\u02ac\u02ad\u0003\u0016\u000b\u0000\u02ad\u02ae\u0003n7\u0000\u02ae"+
		"a\u0001\u0000\u0000\u0000\u02af\u02b0\u0005\\\u0000\u0000\u02b0\u02b1"+
		"\u00032\u0019\u0000\u02b1\u02b2\u0005n\u0000\u0000\u02b2\u02b3\u0003X"+
		",\u0000\u02b3\u02b4\u0003n7\u0000\u02b4c\u0001\u0000\u0000\u0000\u02b5"+
		"\u02b6\u0005a\u0000\u0000\u02b6\u02b7\u0005\r\u0000\u0000\u02b7\u02b8"+
		"\u0005W\u0000\u0000\u02b8\u02b9\u0005l\u0000\u0000\u02b9\u02c0\u0003n"+
		"7\u0000\u02ba\u02bb\u0005C\u0000\u0000\u02bb\u02bc\u0005\r\u0000\u0000"+
		"\u02bc\u02bd\u0005W\u0000\u0000\u02bd\u02be\u0005l\u0000\u0000\u02be\u02c0"+
		"\u0003n7\u0000\u02bf\u02b5\u0001\u0000\u0000\u0000\u02bf\u02ba\u0001\u0000"+
		"\u0000\u0000\u02c0e\u0001\u0000\u0000\u0000\u02c1\u02c2\u0005D\u0000\u0000"+
		"\u02c2\u02c3\u0003h4\u0000\u02c3\u02c4\u0003n7\u0000\u02c4g\u0001\u0000"+
		"\u0000\u0000\u02c5\u02c9\u0005\u0018\u0000\u0000\u02c6\u02c8\b\t\u0000"+
		"\u0000\u02c7\u02c6\u0001\u0000\u0000\u0000\u02c8\u02cb\u0001\u0000\u0000"+
		"\u0000\u02c9\u02c7\u0001\u0000\u0000\u0000\u02c9\u02ca\u0001\u0000\u0000"+
		"\u0000\u02ca\u02cc\u0001\u0000\u0000\u0000\u02cb\u02c9\u0001\u0000\u0000"+
		"\u0000\u02cc\u02cf\u0005\u0019\u0000\u0000\u02cd\u02cf\u0005l\u0000\u0000"+
		"\u02ce\u02c5\u0001\u0000\u0000\u0000\u02ce\u02cd\u0001\u0000\u0000\u0000"+
		"\u02cfi\u0001\u0000\u0000\u0000\u02d0\u02d1\u0005E\u0000\u0000\u02d1\u02d2"+
		"\u0005n\u0000\u0000\u02d2\u02d3\u0003n7\u0000\u02d3k\u0001\u0000\u0000"+
		"\u0000\u02d4\u02d5\u0007\n\u0000\u0000\u02d5m\u0001\u0000\u0000\u0000"+
		"\u02d6\u02db\u00053\u0000\u0000\u02d7\u02db\u0005\u0000\u0000\u0001\u02d8"+
		"\u02db\u00047\u0014\u0000\u02d9\u02db\u00047\u0015\u0000\u02da\u02d6\u0001"+
		"\u0000\u0000\u0000\u02da\u02d7\u0001\u0000\u0000\u0000\u02da\u02d8\u0001"+
		"\u0000\u0000\u0000\u02da\u02d9\u0001\u0000\u0000\u0000\u02dbo\u0001\u0000"+
		"\u0000\u0000Ms\u0080\u0088\u008c\u008e\u0097\u009d\u00c4\u0105\u0108\u010a"+
		"\u0117\u011f\u0126\u012d\u0132\u0136\u0139\u013c\u0151\u015f\u0175\u0179"+
		"\u017b\u017f\u0183\u018e\u0193\u019a\u019d\u01a3\u01a9\u01b5\u01bb\u01bf"+
		"\u01c5\u01c8\u01cb\u01d3\u01e1\u01e7\u01eb\u01ee\u01f3\u01fa\u01ff\u0202"+
		"\u021e\u0228\u022c\u0234\u023e\u0245\u024a\u0252\u0254\u025c\u025f\u0265"+
		"\u0269\u026d\u0274\u0277\u027f\u0282\u0285\u0289\u0290\u0293\u029a\u02a3"+
		"\u02a7\u02aa\u02bf\u02c9\u02ce\u02da";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}