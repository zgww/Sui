// Generated from e:/luwa/oms_ts/orc-antlr/antlr4-cpp/demo/Orc.g4 by ANTLR 4.13.1

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
		Else=74, New=75, Return=76, Void=77, Continue=78, For=79, While=80, This=81, 
		If=82, From=83, Struct=84, Class=85, Enum=86, Extends=87, Extern=88, Super=89, 
		Extension=90, Const=91, Export=92, Import=93, Static=94, Async=95, Await=96, 
		Refc=97, NullLiteral=98, BooleanLiteral=99, DecimalLiteral=100, HexIntegerLiteral=101, 
		OctalIntegerLiteral=102, BinaryIntegerLiteral=103, StringLiteral=104, 
		CharLiteral=105, Id=106, CloseBrace=107, LineTerminator=108, Whitespace=109, 
		BlockComment=110, LineComment=111;
	public static final int
		RULE_program = 0, RULE_rootDeclaration = 1, RULE_arguments = 2, RULE_expressionSequence = 3, 
		RULE_closureExpression = 4, RULE_singleExpression = 5, RULE_assignmentOperator = 6, 
		RULE_emptyStatement = 7, RULE_structDefinition = 8, RULE_structMember = 9, 
		RULE_arraySizeDeclaration = 10, RULE_varDeclaration = 11, RULE_statement = 12, 
		RULE_continueStatement = 13, RULE_breakStatement = 14, RULE_returnStatement = 15, 
		RULE_scopeStatement = 16, RULE_iterationStatement = 17, RULE_forCondition = 18, 
		RULE_selectionStatement = 19, RULE_block = 20, RULE_type = 21, RULE_closureType = 22, 
		RULE_functionTypeArg = 23, RULE_attribute = 24, RULE_functionType = 25, 
		RULE_typeQualifier = 26, RULE_pointer = 27, RULE_ref = 28, RULE_primitiveType = 29, 
		RULE_enumDefinition = 30, RULE_enumItem = 31, RULE_extensionDefinition = 32, 
		RULE_extensionBlock = 33, RULE_classDefinition = 34, RULE_classDefinitionBlock = 35, 
		RULE_classFieldDeclaration = 36, RULE_methodDeclaration = 37, RULE_assignRightPart = 38, 
		RULE_argumentDeclaration = 39, RULE_argumentsDeclaration = 40, RULE_functionPointerVarDeclaration = 41, 
		RULE_functionDefinition = 42, RULE_globalFunctionDefinition = 43, RULE_globalVarDeclaration = 44, 
		RULE_externFunctionDeclaration = 45, RULE_importStatement = 46, RULE_includeStatement = 47, 
		RULE_includePathCharacters = 48, RULE_packageStatement = 49, RULE_literal = 50, 
		RULE_eos = 51;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "rootDeclaration", "arguments", "expressionSequence", "closureExpression", 
			"singleExpression", "assignmentOperator", "emptyStatement", "structDefinition", 
			"structMember", "arraySizeDeclaration", "varDeclaration", "statement", 
			"continueStatement", "breakStatement", "returnStatement", "scopeStatement", 
			"iterationStatement", "forCondition", "selectionStatement", "block", 
			"type", "closureType", "functionTypeArg", "attribute", "functionType", 
			"typeQualifier", "pointer", "ref", "primitiveType", "enumDefinition", 
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
			"'else'", "'new'", "'return'", "'void'", "'continue'", "'for'", "'while'", 
			"'self'", "'if'", "'from'", "'struct'", "'class'", "'enum'", "'extends'", 
			"'extern'", "'super'", "'extension'", "'const'", "'export'", "'import'", 
			"'static'", "'async'", "'await'", "'refc'", null, null, null, null, null, 
			null, null, null, null, "'}'"
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
			"Do", "Instanceof", "Case", "Else", "New", "Return", "Void", "Continue", 
			"For", "While", "This", "If", "From", "Struct", "Class", "Enum", "Extends", 
			"Extern", "Super", "Extension", "Const", "Export", "Import", "Static", 
			"Async", "Await", "Refc", "NullLiteral", "BooleanLiteral", "DecimalLiteral", 
			"HexIntegerLiteral", "OctalIntegerLiteral", "BinaryIntegerLiteral", "StringLiteral", 
			"CharLiteral", "Id", "CloseBrace", "LineTerminator", "Whitespace", "BlockComment", 
			"LineComment"
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
			setState(107);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -322007373356990448L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 4399882575935L) != 0)) {
				{
				{
				setState(104);
				rootDeclaration();
				}
				}
				setState(109);
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
			setState(120);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(110);
				packageStatement();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(111);
				includeStatement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(112);
				importStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(113);
				structDefinition();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(114);
				enumDefinition();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(115);
				classDefinition();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(116);
				extensionDefinition();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(117);
				globalVarDeclaration();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(118);
				globalFunctionDefinition();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(119);
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
			setState(122);
			match(T__0);
			setState(134);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 4286595137L) != 0)) {
				{
				setState(123);
				singleExpression(0);
				setState(128);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(124);
						match(T__1);
						setState(125);
						singleExpression(0);
						}
						} 
					}
					setState(130);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
				}
				setState(132);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(131);
					match(T__1);
					}
				}

				}
			}

			setState(136);
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
			setState(138);
			singleExpression(0);
			setState(143);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(139);
				match(T__1);
				setState(140);
				singleExpression(0);
				}
				}
				setState(145);
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
			setState(146);
			match(T__3);
			setState(147);
			type();
			setState(149);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(148);
				match(Id);
				}
			}

			setState(151);
			argumentsDeclaration();
			setState(152);
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
			setState(188);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				{
				_localctx = new LabelClosureExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(155);
				closureExpression();
				}
				break;
			case 2:
				{
				_localctx = new NewExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(156);
				match(New);
				setState(157);
				match(Id);
				setState(158);
				arguments();
				}
				break;
			case 3:
				{
				_localctx = new GetAddressExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(159);
				match(T__11);
				setState(160);
				singleExpression(29);
				}
				break;
			case 4:
				{
				_localctx = new DerefExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(161);
				match(T__12);
				setState(162);
				singleExpression(28);
				}
				break;
			case 5:
				{
				_localctx = new PreIncrementExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(163);
				match(T__4);
				setState(164);
				singleExpression(27);
				}
				break;
			case 6:
				{
				_localctx = new PreDecreaseExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(165);
				match(T__5);
				setState(166);
				singleExpression(26);
				}
				break;
			case 7:
				{
				_localctx = new UnaryPlusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(167);
				match(T__13);
				setState(168);
				singleExpression(25);
				}
				break;
			case 8:
				{
				_localctx = new UnaryMinusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(169);
				match(T__14);
				setState(170);
				singleExpression(24);
				}
				break;
			case 9:
				{
				_localctx = new BitNotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(171);
				match(T__15);
				setState(172);
				singleExpression(23);
				}
				break;
			case 10:
				{
				_localctx = new NotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(173);
				match(T__16);
				setState(174);
				singleExpression(22);
				}
				break;
			case 11:
				{
				_localctx = new CastExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(175);
				match(T__0);
				setState(176);
				type();
				setState(177);
				match(T__2);
				setState(178);
				singleExpression(8);
				}
				break;
			case 12:
				{
				_localctx = new ThisExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(180);
				match(This);
				}
				break;
			case 13:
				{
				_localctx = new IdentifierExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(181);
				match(Id);
				}
				break;
			case 14:
				{
				_localctx = new SuperExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(182);
				match(Super);
				}
				break;
			case 15:
				{
				_localctx = new LiteralExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(183);
				literal();
				}
				break;
			case 16:
				{
				_localctx = new ParenthesizedExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(184);
				match(T__0);
				setState(185);
				expressionSequence();
				setState(186);
				match(T__2);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(258);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(256);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
					case 1:
						{
						_localctx = new MultiplicativeExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(190);
						if (!(precpred(_ctx, 21))) throw new FailedPredicateException(this, "precpred(_ctx, 21)");
						setState(191);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 794624L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(192);
						singleExpression(22);
						}
						break;
					case 2:
						{
						_localctx = new AdditiveExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(193);
						if (!(precpred(_ctx, 20))) throw new FailedPredicateException(this, "precpred(_ctx, 20)");
						setState(194);
						_la = _input.LA(1);
						if ( !(_la==T__13 || _la==T__14) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(195);
						singleExpression(21);
						}
						break;
					case 3:
						{
						_localctx = new CoalesceExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(196);
						if (!(precpred(_ctx, 19))) throw new FailedPredicateException(this, "precpred(_ctx, 19)");
						setState(197);
						match(T__19);
						setState(198);
						singleExpression(20);
						}
						break;
					case 4:
						{
						_localctx = new BitShiftExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(199);
						if (!(precpred(_ctx, 18))) throw new FailedPredicateException(this, "precpred(_ctx, 18)");
						setState(200);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 14680064L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(201);
						singleExpression(19);
						}
						break;
					case 5:
						{
						_localctx = new RelationalExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(202);
						if (!(precpred(_ctx, 17))) throw new FailedPredicateException(this, "precpred(_ctx, 17)");
						setState(203);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 251658240L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(204);
						singleExpression(18);
						}
						break;
					case 6:
						{
						_localctx = new InstanceofExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(205);
						if (!(precpred(_ctx, 16))) throw new FailedPredicateException(this, "precpred(_ctx, 16)");
						setState(206);
						match(Instanceof);
						setState(207);
						singleExpression(17);
						}
						break;
					case 7:
						{
						_localctx = new EqualityExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(208);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(209);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 4026531840L) != 0)) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(210);
						singleExpression(16);
						}
						break;
					case 8:
						{
						_localctx = new BitAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(211);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(212);
						match(T__11);
						setState(213);
						singleExpression(15);
						}
						break;
					case 9:
						{
						_localctx = new BitXOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(214);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(215);
						match(T__3);
						setState(216);
						singleExpression(14);
						}
						break;
					case 10:
						{
						_localctx = new BitOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(217);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(218);
						match(T__31);
						setState(219);
						singleExpression(13);
						}
						break;
					case 11:
						{
						_localctx = new LogicalAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(220);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(221);
						match(T__32);
						setState(222);
						singleExpression(12);
						}
						break;
					case 12:
						{
						_localctx = new LogicalOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(223);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(224);
						match(T__33);
						setState(225);
						singleExpression(11);
						}
						break;
					case 13:
						{
						_localctx = new TernaryExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(226);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(227);
						match(T__34);
						setState(228);
						singleExpression(0);
						setState(229);
						match(T__35);
						setState(230);
						singleExpression(10);
						}
						break;
					case 14:
						{
						_localctx = new AssignmentExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(232);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(233);
						match(T__36);
						setState(234);
						singleExpression(7);
						}
						break;
					case 15:
						{
						_localctx = new AssignmentOperatorExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(235);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(236);
						assignmentOperator();
						setState(237);
						singleExpression(6);
						}
						break;
					case 16:
						{
						_localctx = new CallExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(239);
						if (!(precpred(_ctx, 36))) throw new FailedPredicateException(this, "precpred(_ctx, 36)");
						setState(240);
						arguments();
						}
						break;
					case 17:
						{
						_localctx = new PostIncrementExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(241);
						if (!(precpred(_ctx, 35))) throw new FailedPredicateException(this, "precpred(_ctx, 35)");
						setState(242);
						match(T__4);
						}
						break;
					case 18:
						{
						_localctx = new PostDecreaseExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(243);
						if (!(precpred(_ctx, 34))) throw new FailedPredicateException(this, "precpred(_ctx, 34)");
						setState(244);
						match(T__5);
						}
						break;
					case 19:
						{
						_localctx = new MemberIndexExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(245);
						if (!(precpred(_ctx, 32))) throw new FailedPredicateException(this, "precpred(_ctx, 32)");
						setState(246);
						match(T__6);
						setState(247);
						singleExpression(0);
						setState(248);
						match(T__7);
						}
						break;
					case 20:
						{
						_localctx = new MemberDotExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(250);
						if (!(precpred(_ctx, 31))) throw new FailedPredicateException(this, "precpred(_ctx, 31)");
						setState(251);
						_la = _input.LA(1);
						if ( !(_la==T__8 || _la==T__9) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(253);
						_errHandler.sync(this);
						_la = _input.LA(1);
						if (_la==T__10) {
							{
							setState(252);
							match(T__10);
							}
						}

						setState(255);
						match(Id);
						}
						break;
					}
					} 
				}
				setState(260);
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
			setState(261);
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
			setState(263);
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
			setState(265);
			match(Struct);
			setState(266);
			match(Id);
			setState(267);
			match(T__51);
			setState(271);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 4398181785607L) != 0)) {
				{
				{
				setState(268);
				structMember();
				}
				}
				setState(273);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(274);
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
			setState(286);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(276);
				type();
				setState(277);
				match(Id);
				setState(279);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
				case 1:
					{
					setState(278);
					arraySizeDeclaration();
					}
					break;
				}
				setState(281);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(283);
				functionPointerVarDeclaration();
				setState(284);
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
			setState(288);
			match(T__6);
			setState(289);
			match(DecimalLiteral);
			setState(290);
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
			setState(308);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(293);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(292);
					match(Static);
					}
				}

				setState(295);
				type();
				setState(296);
				match(Id);
				setState(298);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,15,_ctx) ) {
				case 1:
					{
					setState(297);
					arraySizeDeclaration();
					}
					break;
				}
				setState(302);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
				case 1:
					{
					setState(300);
					match(T__36);
					setState(301);
					singleExpression(0);
					}
					break;
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(305);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(304);
					match(Static);
					}
				}

				setState(307);
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
		public SelectionStatementContext selectionStatement() {
			return getRuleContext(SelectionStatementContext.class,0);
		}
		public ReturnStatementContext returnStatement() {
			return getRuleContext(ReturnStatementContext.class,0);
		}
		public IterationStatementContext iterationStatement() {
			return getRuleContext(IterationStatementContext.class,0);
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
			setState(327);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(310);
				closureExpression();
				setState(311);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(313);
				varDeclaration();
				setState(314);
				eos();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(316);
				scopeStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(317);
				block();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(318);
				continueStatement();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(319);
				breakStatement();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(320);
				selectionStatement();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(321);
				returnStatement();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(322);
				iterationStatement();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(323);
				singleExpression(0);
				setState(324);
				eos();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(326);
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
			setState(329);
			match(Continue);
			setState(330);
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
			setState(332);
			match(Break);
			setState(333);
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
		enterRule(_localctx, 30, RULE_returnStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(335);
			match(Return);
			setState(337);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
			case 1:
				{
				setState(336);
				singleExpression(0);
				}
				break;
			}
			setState(339);
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
		enterRule(_localctx, 32, RULE_scopeStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(341);
			singleExpression(0);
			setState(342);
			_la = _input.LA(1);
			if ( !(_la==T__8 || _la==T__15) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(343);
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
		enterRule(_localctx, 34, RULE_iterationStatement);
		try {
			setState(359);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(345);
				match(While);
				setState(346);
				singleExpression(0);
				setState(347);
				block();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(349);
				match(For);
				setState(350);
				match(T__0);
				setState(351);
				forCondition();
				setState(352);
				match(T__2);
				setState(353);
				block();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(355);
				match(For);
				setState(356);
				forCondition();
				setState(357);
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
		enterRule(_localctx, 36, RULE_forCondition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(365);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				{
				setState(361);
				varDeclaration();
				}
				break;
			case 2:
				{
				setState(363);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 4286595137L) != 0)) {
					{
					setState(362);
					singleExpression(0);
					}
				}

				}
				break;
			}
			setState(367);
			match(T__50);
			setState(369);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 4286595137L) != 0)) {
				{
				setState(368);
				singleExpression(0);
				}
			}

			setState(371);
			match(T__50);
			setState(373);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 258162L) != 0) || ((((_la - 75)) & ~0x3f) == 0 && ((1L << (_la - 75)) & 4286595137L) != 0)) {
				{
				setState(372);
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
		enterRule(_localctx, 38, RULE_selectionStatement);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(375);
			match(If);
			setState(376);
			singleExpression(0);
			setState(377);
			block();
			setState(384);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__52) {
				{
				{
				setState(378);
				match(T__52);
				setState(379);
				singleExpression(0);
				setState(380);
				block();
				}
				}
				setState(386);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(389);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Else) {
				{
				setState(387);
				match(Else);
				setState(388);
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
		enterRule(_localctx, 40, RULE_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(391);
			match(T__51);
			setState(395);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -317503773729361806L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 8780156237895L) != 0)) {
				{
				{
				setState(392);
				statement();
				}
				}
				setState(397);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(398);
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
		enterRule(_localctx, 42, RULE_type);
		int _la;
		try {
			setState(417);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,33,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(401);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 68719476743L) != 0)) {
					{
					setState(400);
					typeQualifier();
					}
				}

				setState(403);
				primitiveType();
				setState(405);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__6) {
					{
					setState(404);
					arraySizeDeclaration();
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(407);
				closureType();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(408);
				pointer();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(409);
				ref();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(411);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 68719476743L) != 0)) {
					{
					setState(410);
					typeQualifier();
					}
				}

				setState(414);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Struct) {
					{
					setState(413);
					match(Struct);
					}
				}

				setState(416);
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
		enterRule(_localctx, 44, RULE_closureType);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(419);
			match(T__3);
			setState(420);
			type();
			setState(421);
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
		enterRule(_localctx, 46, RULE_functionTypeArg);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(423);
			type();
			setState(425);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(424);
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
		enterRule(_localctx, 48, RULE_attribute);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(427);
			match(T__53);
			setState(428);
			match(T__0);
			setState(429);
			match(T__0);
			setState(430);
			match(Id);
			setState(431);
			match(T__2);
			setState(432);
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
		enterRule(_localctx, 50, RULE_functionType);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(434);
			type();
			setState(435);
			argumentsDeclaration();
			setState(439);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__53) {
				{
				{
				setState(436);
				attribute();
				}
				}
				setState(441);
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
		enterRule(_localctx, 52, RULE_typeQualifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(442);
			_la = _input.LA(1);
			if ( !(((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 68719476743L) != 0)) ) {
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
		enterRule(_localctx, 54, RULE_pointer);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(445);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 68719476743L) != 0)) {
				{
				setState(444);
				typeQualifier();
				}
			}

			setState(452);
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
				setState(447);
				primitiveType();
				}
				break;
			case Struct:
			case Id:
				{
				{
				setState(449);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Struct) {
					{
					setState(448);
					match(Struct);
					}
				}

				setState(451);
				match(Id);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(467); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(457);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (((((_la - 55)) & ~0x3f) == 0 && ((1L << (_la - 55)) & 68719476743L) != 0)) {
					{
					{
					setState(454);
					typeQualifier();
					}
					}
					setState(459);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(460);
				match(T__12);
				setState(464);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,40,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(461);
						typeQualifier();
						}
						} 
					}
					setState(466);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,40,_ctx);
				}
				}
				}
				setState(469); 
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
		enterRule(_localctx, 56, RULE_ref);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(472);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Struct) {
				{
				setState(471);
				match(Struct);
				}
			}

			setState(474);
			match(Id);
			setState(475);
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
		enterRule(_localctx, 58, RULE_primitiveType);
		try {
			setState(500);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,43,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(477);
				match(T__58);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(478);
				match(T__59);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(479);
				match(T__60);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(480);
				match(T__61);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(481);
				match(T__62);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(482);
				match(T__63);
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(483);
				match(Void);
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(484);
				match(T__64);
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(485);
				match(T__64);
				setState(486);
				match(T__64);
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(487);
				match(T__64);
				setState(488);
				match(T__61);
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(489);
				match(T__65);
				setState(490);
				match(T__62);
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(491);
				match(T__65);
				setState(492);
				match(T__58);
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(493);
				match(T__65);
				setState(494);
				match(T__59);
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(495);
				match(T__65);
				setState(496);
				match(T__64);
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(497);
				match(T__65);
				setState(498);
				match(T__64);
				setState(499);
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
		enterRule(_localctx, 60, RULE_enumDefinition);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(502);
			match(Enum);
			setState(503);
			match(Id);
			setState(504);
			match(T__51);
			setState(505);
			enumItem();
			setState(510);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(506);
					match(T__1);
					setState(507);
					enumItem();
					}
					} 
				}
				setState(512);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
			}
			setState(514);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(513);
				match(T__1);
				}
			}

			setState(516);
			match(CloseBrace);
			setState(517);
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
		enterRule(_localctx, 62, RULE_enumItem);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(519);
			match(Id);
			setState(522);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__36) {
				{
				setState(520);
				match(T__36);
				setState(521);
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
		enterRule(_localctx, 64, RULE_extensionDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(524);
			match(Extension);
			setState(525);
			match(Id);
			setState(526);
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
		enterRule(_localctx, 66, RULE_extensionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(528);
			match(T__51);
			setState(532);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 4398198562823L) != 0)) {
				{
				{
				setState(529);
				methodDeclaration();
				}
				}
				setState(534);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(535);
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
		enterRule(_localctx, 68, RULE_classDefinition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(537);
			match(Class);
			setState(539);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Refc) {
				{
				setState(538);
				match(Refc);
				}
			}

			setState(541);
			match(Id);
			setState(544);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Extends) {
				{
				setState(542);
				match(Extends);
				setState(543);
				match(Id);
				}
			}

			setState(546);
			classDefinitionBlock();
			setState(547);
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
		enterRule(_localctx, 70, RULE_classDefinitionBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(549);
			match(T__51);
			setState(554);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 4398198562823L) != 0)) {
				{
				setState(552);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,50,_ctx) ) {
				case 1:
					{
					setState(550);
					classFieldDeclaration();
					}
					break;
				case 2:
					{
					setState(551);
					methodDeclaration();
					}
					break;
				}
				}
				setState(556);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(557);
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
		enterRule(_localctx, 72, RULE_classFieldDeclaration);
		try {
			setState(575);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,55,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(559);
				type();
				setState(560);
				match(Id);
				setState(562);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,52,_ctx) ) {
				case 1:
					{
					setState(561);
					arraySizeDeclaration();
					}
					break;
				}
				setState(565);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,53,_ctx) ) {
				case 1:
					{
					setState(564);
					assignRightPart();
					}
					break;
				}
				setState(567);
				eos();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(569);
				functionPointerVarDeclaration();
				setState(571);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,54,_ctx) ) {
				case 1:
					{
					setState(570);
					assignRightPart();
					}
					break;
				}
				setState(573);
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
		enterRule(_localctx, 74, RULE_methodDeclaration);
		try {
			setState(579);
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
				setState(577);
				functionDefinition();
				}
				break;
			case Extern:
				enterOuterAlt(_localctx, 2);
				{
				setState(578);
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
		enterRule(_localctx, 76, RULE_assignRightPart);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(581);
			match(T__36);
			setState(582);
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
		enterRule(_localctx, 78, RULE_argumentDeclaration);
		int _la;
		try {
			setState(589);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,58,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(584);
				type();
				setState(586);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Id) {
					{
					setState(585);
					match(Id);
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(588);
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
		enterRule(_localctx, 80, RULE_argumentsDeclaration);
		int _la;
		try {
			int _alt;
			setState(607);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,62,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(591);
				match(T__0);
				setState(600);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -324259173170675696L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 4398181785607L) != 0)) {
					{
					setState(592);
					argumentDeclaration();
					setState(597);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,59,_ctx);
					while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
						if ( _alt==1 ) {
							{
							{
							setState(593);
							match(T__1);
							setState(594);
							argumentDeclaration();
							}
							} 
						}
						setState(599);
						_errHandler.sync(this);
						_alt = getInterpreter().adaptivePredict(_input,59,_ctx);
					}
					}
				}

				setState(603);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__1) {
					{
					setState(602);
					match(T__1);
					}
				}

				setState(605);
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
		enterRule(_localctx, 82, RULE_functionPointerVarDeclaration);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(609);
			type();
			setState(610);
			match(T__0);
			setState(612); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(611);
				match(T__12);
				}
				}
				setState(614); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__12 );
			setState(617);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Id) {
				{
				setState(616);
				match(Id);
				}
			}

			setState(619);
			match(T__2);
			setState(620);
			argumentsDeclaration();
			setState(624);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,65,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(621);
					attribute();
					}
					} 
				}
				setState(626);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,65,_ctx);
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
		enterRule(_localctx, 84, RULE_functionDefinition);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(627);
			type();
			setState(628);
			match(Id);
			setState(629);
			argumentsDeclaration();
			setState(630);
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
		enterRule(_localctx, 86, RULE_globalFunctionDefinition);
		int _la;
		try {
			setState(640);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,68,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(633);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(632);
					match(Static);
					}
				}

				setState(635);
				functionDefinition();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(637);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==Static) {
					{
					setState(636);
					match(Static);
					}
				}

				setState(639);
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
		enterRule(_localctx, 88, RULE_globalVarDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(642);
			varDeclaration();
			setState(643);
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
		enterRule(_localctx, 90, RULE_externFunctionDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(645);
			match(Extern);
			setState(646);
			type();
			setState(647);
			match(Id);
			setState(648);
			argumentsDeclaration();
			setState(649);
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
		enterRule(_localctx, 92, RULE_importStatement);
		try {
			setState(661);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Import:
				enterOuterAlt(_localctx, 1);
				{
				setState(651);
				match(Import);
				setState(652);
				match(T__12);
				setState(653);
				match(From);
				setState(654);
				match(StringLiteral);
				setState(655);
				eos();
				}
				break;
			case T__66:
				enterOuterAlt(_localctx, 2);
				{
				setState(656);
				match(T__66);
				setState(657);
				match(T__12);
				setState(658);
				match(From);
				setState(659);
				match(StringLiteral);
				setState(660);
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
		enterRule(_localctx, 94, RULE_includeStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(663);
			match(T__67);
			setState(664);
			includePathCharacters();
			setState(665);
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
		enterRule(_localctx, 96, RULE_includePathCharacters);
		int _la;
		try {
			setState(676);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__23:
				enterOuterAlt(_localctx, 1);
				{
				setState(667);
				match(T__23);
				setState(671);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & -33554434L) != 0) || ((((_la - 64)) & ~0x3f) == 0 && ((1L << (_la - 64)) & 281474976710655L) != 0)) {
					{
					{
					setState(668);
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
					setState(673);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(674);
				match(T__24);
				}
				break;
			case StringLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(675);
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
		enterRule(_localctx, 98, RULE_packageStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(678);
			match(T__68);
			setState(679);
			match(Id);
			setState(680);
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
		enterRule(_localctx, 100, RULE_literal);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(682);
			_la = _input.LA(1);
			if ( !(((((_la - 98)) & ~0x3f) == 0 && ((1L << (_la - 98)) & 255L) != 0)) ) {
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
		enterRule(_localctx, 102, RULE_eos);
		try {
			setState(688);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,72,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(684);
				match(T__50);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(685);
				match(EOF);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(686);
				if (!(this->lineTerminatorAhead())) throw new FailedPredicateException(this, "this->lineTerminatorAhead()");
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(687);
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
		case 51:
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
		"\u0004\u0001o\u02b3\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
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
		"2\u00072\u00023\u00073\u0001\u0000\u0005\u0000j\b\u0000\n\u0000\f\u0000"+
		"m\t\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0003\u0001"+
		"y\b\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0005\u0002"+
		"\u007f\b\u0002\n\u0002\f\u0002\u0082\t\u0002\u0001\u0002\u0003\u0002\u0085"+
		"\b\u0002\u0003\u0002\u0087\b\u0002\u0001\u0002\u0001\u0002\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0005\u0003\u008e\b\u0003\n\u0003\f\u0003\u0091"+
		"\t\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0003\u0004\u0096\b\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0003\u0005\u00bd\b\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0003\u0005\u00fe\b\u0005\u0001\u0005\u0005\u0005\u0101\b\u0005\n\u0005"+
		"\f\u0005\u0104\t\u0005\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007"+
		"\u0001\b\u0001\b\u0001\b\u0001\b\u0005\b\u010e\b\b\n\b\f\b\u0111\t\b\u0001"+
		"\b\u0001\b\u0001\t\u0001\t\u0001\t\u0003\t\u0118\b\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0003\t\u011f\b\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001"+
		"\u000b\u0003\u000b\u0126\b\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0003"+
		"\u000b\u012b\b\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u012f\b\u000b"+
		"\u0001\u000b\u0003\u000b\u0132\b\u000b\u0001\u000b\u0003\u000b\u0135\b"+
		"\u000b\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f"+
		"\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0003\f\u0148\b\f\u0001\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000f\u0001\u000f\u0003\u000f\u0152\b\u000f\u0001\u000f\u0001"+
		"\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0003\u0011\u0168\b\u0011\u0001\u0012\u0001\u0012\u0003\u0012\u016c"+
		"\b\u0012\u0003\u0012\u016e\b\u0012\u0001\u0012\u0001\u0012\u0003\u0012"+
		"\u0172\b\u0012\u0001\u0012\u0001\u0012\u0003\u0012\u0176\b\u0012\u0001"+
		"\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0013\u0005\u0013\u017f\b\u0013\n\u0013\f\u0013\u0182\t\u0013\u0001\u0013"+
		"\u0001\u0013\u0003\u0013\u0186\b\u0013\u0001\u0014\u0001\u0014\u0005\u0014"+
		"\u018a\b\u0014\n\u0014\f\u0014\u018d\t\u0014\u0001\u0014\u0001\u0014\u0001"+
		"\u0015\u0003\u0015\u0192\b\u0015\u0001\u0015\u0001\u0015\u0003\u0015\u0196"+
		"\b\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0015\u0003\u0015\u019c"+
		"\b\u0015\u0001\u0015\u0003\u0015\u019f\b\u0015\u0001\u0015\u0003\u0015"+
		"\u01a2\b\u0015\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0017"+
		"\u0001\u0017\u0003\u0017\u01aa\b\u0017\u0001\u0018\u0001\u0018\u0001\u0018"+
		"\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0019\u0001\u0019"+
		"\u0001\u0019\u0005\u0019\u01b6\b\u0019\n\u0019\f\u0019\u01b9\t\u0019\u0001"+
		"\u001a\u0001\u001a\u0001\u001b\u0003\u001b\u01be\b\u001b\u0001\u001b\u0001"+
		"\u001b\u0003\u001b\u01c2\b\u001b\u0001\u001b\u0003\u001b\u01c5\b\u001b"+
		"\u0001\u001b\u0005\u001b\u01c8\b\u001b\n\u001b\f\u001b\u01cb\t\u001b\u0001"+
		"\u001b\u0001\u001b\u0005\u001b\u01cf\b\u001b\n\u001b\f\u001b\u01d2\t\u001b"+
		"\u0004\u001b\u01d4\b\u001b\u000b\u001b\f\u001b\u01d5\u0001\u001c\u0003"+
		"\u001c\u01d9\b\u001c\u0001\u001c\u0001\u001c\u0001\u001c\u0001\u001d\u0001"+
		"\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001"+
		"\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001"+
		"\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0001"+
		"\u001d\u0001\u001d\u0001\u001d\u0001\u001d\u0003\u001d\u01f5\b\u001d\u0001"+
		"\u001e\u0001\u001e\u0001\u001e\u0001\u001e\u0001\u001e\u0001\u001e\u0005"+
		"\u001e\u01fd\b\u001e\n\u001e\f\u001e\u0200\t\u001e\u0001\u001e\u0003\u001e"+
		"\u0203\b\u001e\u0001\u001e\u0001\u001e\u0001\u001e\u0001\u001f\u0001\u001f"+
		"\u0001\u001f\u0003\u001f\u020b\b\u001f\u0001 \u0001 \u0001 \u0001 \u0001"+
		"!\u0001!\u0005!\u0213\b!\n!\f!\u0216\t!\u0001!\u0001!\u0001\"\u0001\""+
		"\u0003\"\u021c\b\"\u0001\"\u0001\"\u0001\"\u0003\"\u0221\b\"\u0001\"\u0001"+
		"\"\u0001\"\u0001#\u0001#\u0001#\u0005#\u0229\b#\n#\f#\u022c\t#\u0001#"+
		"\u0001#\u0001$\u0001$\u0001$\u0003$\u0233\b$\u0001$\u0003$\u0236\b$\u0001"+
		"$\u0001$\u0001$\u0001$\u0003$\u023c\b$\u0001$\u0001$\u0003$\u0240\b$\u0001"+
		"%\u0001%\u0003%\u0244\b%\u0001&\u0001&\u0001&\u0001\'\u0001\'\u0003\'"+
		"\u024b\b\'\u0001\'\u0003\'\u024e\b\'\u0001(\u0001(\u0001(\u0001(\u0005"+
		"(\u0254\b(\n(\f(\u0257\t(\u0003(\u0259\b(\u0001(\u0003(\u025c\b(\u0001"+
		"(\u0001(\u0003(\u0260\b(\u0001)\u0001)\u0001)\u0004)\u0265\b)\u000b)\f"+
		")\u0266\u0001)\u0003)\u026a\b)\u0001)\u0001)\u0001)\u0005)\u026f\b)\n"+
		")\f)\u0272\t)\u0001*\u0001*\u0001*\u0001*\u0001*\u0001+\u0003+\u027a\b"+
		"+\u0001+\u0001+\u0003+\u027e\b+\u0001+\u0003+\u0281\b+\u0001,\u0001,\u0001"+
		",\u0001-\u0001-\u0001-\u0001-\u0001-\u0001-\u0001.\u0001.\u0001.\u0001"+
		".\u0001.\u0001.\u0001.\u0001.\u0001.\u0001.\u0003.\u0296\b.\u0001/\u0001"+
		"/\u0001/\u0001/\u00010\u00010\u00050\u029e\b0\n0\f0\u02a1\t0\u00010\u0001"+
		"0\u00030\u02a5\b0\u00011\u00011\u00011\u00011\u00012\u00012\u00013\u0001"+
		"3\u00013\u00013\u00033\u02b1\b3\u00013\u0000\u0001\n4\u0000\u0002\u0004"+
		"\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e \""+
		"$&(*,.02468:<>@BDFHJLNPRTVXZ\\^`bdf\u0000\u000b\u0002\u0000\r\r\u0012"+
		"\u0013\u0001\u0000\u000e\u000f\u0001\u0000\u0015\u0017\u0001\u0000\u0018"+
		"\u001b\u0001\u0000\u001c\u001f\u0001\u0000\t\n\u0001\u0000&2\u0002\u0000"+
		"\t\t\u0010\u0010\u0002\u000079[[\u0001\u0000\u0019\u0019\u0001\u0000b"+
		"i\u030b\u0000k\u0001\u0000\u0000\u0000\u0002x\u0001\u0000\u0000\u0000"+
		"\u0004z\u0001\u0000\u0000\u0000\u0006\u008a\u0001\u0000\u0000\u0000\b"+
		"\u0092\u0001\u0000\u0000\u0000\n\u00bc\u0001\u0000\u0000\u0000\f\u0105"+
		"\u0001\u0000\u0000\u0000\u000e\u0107\u0001\u0000\u0000\u0000\u0010\u0109"+
		"\u0001\u0000\u0000\u0000\u0012\u011e\u0001\u0000\u0000\u0000\u0014\u0120"+
		"\u0001\u0000\u0000\u0000\u0016\u0134\u0001\u0000\u0000\u0000\u0018\u0147"+
		"\u0001\u0000\u0000\u0000\u001a\u0149\u0001\u0000\u0000\u0000\u001c\u014c"+
		"\u0001\u0000\u0000\u0000\u001e\u014f\u0001\u0000\u0000\u0000 \u0155\u0001"+
		"\u0000\u0000\u0000\"\u0167\u0001\u0000\u0000\u0000$\u016d\u0001\u0000"+
		"\u0000\u0000&\u0177\u0001\u0000\u0000\u0000(\u0187\u0001\u0000\u0000\u0000"+
		"*\u01a1\u0001\u0000\u0000\u0000,\u01a3\u0001\u0000\u0000\u0000.\u01a7"+
		"\u0001\u0000\u0000\u00000\u01ab\u0001\u0000\u0000\u00002\u01b2\u0001\u0000"+
		"\u0000\u00004\u01ba\u0001\u0000\u0000\u00006\u01bd\u0001\u0000\u0000\u0000"+
		"8\u01d8\u0001\u0000\u0000\u0000:\u01f4\u0001\u0000\u0000\u0000<\u01f6"+
		"\u0001\u0000\u0000\u0000>\u0207\u0001\u0000\u0000\u0000@\u020c\u0001\u0000"+
		"\u0000\u0000B\u0210\u0001\u0000\u0000\u0000D\u0219\u0001\u0000\u0000\u0000"+
		"F\u0225\u0001\u0000\u0000\u0000H\u023f\u0001\u0000\u0000\u0000J\u0243"+
		"\u0001\u0000\u0000\u0000L\u0245\u0001\u0000\u0000\u0000N\u024d\u0001\u0000"+
		"\u0000\u0000P\u025f\u0001\u0000\u0000\u0000R\u0261\u0001\u0000\u0000\u0000"+
		"T\u0273\u0001\u0000\u0000\u0000V\u0280\u0001\u0000\u0000\u0000X\u0282"+
		"\u0001\u0000\u0000\u0000Z\u0285\u0001\u0000\u0000\u0000\\\u0295\u0001"+
		"\u0000\u0000\u0000^\u0297\u0001\u0000\u0000\u0000`\u02a4\u0001\u0000\u0000"+
		"\u0000b\u02a6\u0001\u0000\u0000\u0000d\u02aa\u0001\u0000\u0000\u0000f"+
		"\u02b0\u0001\u0000\u0000\u0000hj\u0003\u0002\u0001\u0000ih\u0001\u0000"+
		"\u0000\u0000jm\u0001\u0000\u0000\u0000ki\u0001\u0000\u0000\u0000kl\u0001"+
		"\u0000\u0000\u0000l\u0001\u0001\u0000\u0000\u0000mk\u0001\u0000\u0000"+
		"\u0000ny\u0003b1\u0000oy\u0003^/\u0000py\u0003\\.\u0000qy\u0003\u0010"+
		"\b\u0000ry\u0003<\u001e\u0000sy\u0003D\"\u0000ty\u0003@ \u0000uy\u0003"+
		"X,\u0000vy\u0003V+\u0000wy\u0003\u000e\u0007\u0000xn\u0001\u0000\u0000"+
		"\u0000xo\u0001\u0000\u0000\u0000xp\u0001\u0000\u0000\u0000xq\u0001\u0000"+
		"\u0000\u0000xr\u0001\u0000\u0000\u0000xs\u0001\u0000\u0000\u0000xt\u0001"+
		"\u0000\u0000\u0000xu\u0001\u0000\u0000\u0000xv\u0001\u0000\u0000\u0000"+
		"xw\u0001\u0000\u0000\u0000y\u0003\u0001\u0000\u0000\u0000z\u0086\u0005"+
		"\u0001\u0000\u0000{\u0080\u0003\n\u0005\u0000|}\u0005\u0002\u0000\u0000"+
		"}\u007f\u0003\n\u0005\u0000~|\u0001\u0000\u0000\u0000\u007f\u0082\u0001"+
		"\u0000\u0000\u0000\u0080~\u0001\u0000\u0000\u0000\u0080\u0081\u0001\u0000"+
		"\u0000\u0000\u0081\u0084\u0001\u0000\u0000\u0000\u0082\u0080\u0001\u0000"+
		"\u0000\u0000\u0083\u0085\u0005\u0002\u0000\u0000\u0084\u0083\u0001\u0000"+
		"\u0000\u0000\u0084\u0085\u0001\u0000\u0000\u0000\u0085\u0087\u0001\u0000"+
		"\u0000\u0000\u0086{\u0001\u0000\u0000\u0000\u0086\u0087\u0001\u0000\u0000"+
		"\u0000\u0087\u0088\u0001\u0000\u0000\u0000\u0088\u0089\u0005\u0003\u0000"+
		"\u0000\u0089\u0005\u0001\u0000\u0000\u0000\u008a\u008f\u0003\n\u0005\u0000"+
		"\u008b\u008c\u0005\u0002\u0000\u0000\u008c\u008e\u0003\n\u0005\u0000\u008d"+
		"\u008b\u0001\u0000\u0000\u0000\u008e\u0091\u0001\u0000\u0000\u0000\u008f"+
		"\u008d\u0001\u0000\u0000\u0000\u008f\u0090\u0001\u0000\u0000\u0000\u0090"+
		"\u0007\u0001\u0000\u0000\u0000\u0091\u008f\u0001\u0000\u0000\u0000\u0092"+
		"\u0093\u0005\u0004\u0000\u0000\u0093\u0095\u0003*\u0015\u0000\u0094\u0096"+
		"\u0005j\u0000\u0000\u0095\u0094\u0001\u0000\u0000\u0000\u0095\u0096\u0001"+
		"\u0000\u0000\u0000\u0096\u0097\u0001\u0000\u0000\u0000\u0097\u0098\u0003"+
		"P(\u0000\u0098\u0099\u0003(\u0014\u0000\u0099\t\u0001\u0000\u0000\u0000"+
		"\u009a\u009b\u0006\u0005\uffff\uffff\u0000\u009b\u00bd\u0003\b\u0004\u0000"+
		"\u009c\u009d\u0005K\u0000\u0000\u009d\u009e\u0005j\u0000\u0000\u009e\u00bd"+
		"\u0003\u0004\u0002\u0000\u009f\u00a0\u0005\f\u0000\u0000\u00a0\u00bd\u0003"+
		"\n\u0005\u001d\u00a1\u00a2\u0005\r\u0000\u0000\u00a2\u00bd\u0003\n\u0005"+
		"\u001c\u00a3\u00a4\u0005\u0005\u0000\u0000\u00a4\u00bd\u0003\n\u0005\u001b"+
		"\u00a5\u00a6\u0005\u0006\u0000\u0000\u00a6\u00bd\u0003\n\u0005\u001a\u00a7"+
		"\u00a8\u0005\u000e\u0000\u0000\u00a8\u00bd\u0003\n\u0005\u0019\u00a9\u00aa"+
		"\u0005\u000f\u0000\u0000\u00aa\u00bd\u0003\n\u0005\u0018\u00ab\u00ac\u0005"+
		"\u0010\u0000\u0000\u00ac\u00bd\u0003\n\u0005\u0017\u00ad\u00ae\u0005\u0011"+
		"\u0000\u0000\u00ae\u00bd\u0003\n\u0005\u0016\u00af\u00b0\u0005\u0001\u0000"+
		"\u0000\u00b0\u00b1\u0003*\u0015\u0000\u00b1\u00b2\u0005\u0003\u0000\u0000"+
		"\u00b2\u00b3\u0003\n\u0005\b\u00b3\u00bd\u0001\u0000\u0000\u0000\u00b4"+
		"\u00bd\u0005Q\u0000\u0000\u00b5\u00bd\u0005j\u0000\u0000\u00b6\u00bd\u0005"+
		"Y\u0000\u0000\u00b7\u00bd\u0003d2\u0000\u00b8\u00b9\u0005\u0001\u0000"+
		"\u0000\u00b9\u00ba\u0003\u0006\u0003\u0000\u00ba\u00bb\u0005\u0003\u0000"+
		"\u0000\u00bb\u00bd\u0001\u0000\u0000\u0000\u00bc\u009a\u0001\u0000\u0000"+
		"\u0000\u00bc\u009c\u0001\u0000\u0000\u0000\u00bc\u009f\u0001\u0000\u0000"+
		"\u0000\u00bc\u00a1\u0001\u0000\u0000\u0000\u00bc\u00a3\u0001\u0000\u0000"+
		"\u0000\u00bc\u00a5\u0001\u0000\u0000\u0000\u00bc\u00a7\u0001\u0000\u0000"+
		"\u0000\u00bc\u00a9\u0001\u0000\u0000\u0000\u00bc\u00ab\u0001\u0000\u0000"+
		"\u0000\u00bc\u00ad\u0001\u0000\u0000\u0000\u00bc\u00af\u0001\u0000\u0000"+
		"\u0000\u00bc\u00b4\u0001\u0000\u0000\u0000\u00bc\u00b5\u0001\u0000\u0000"+
		"\u0000\u00bc\u00b6\u0001\u0000\u0000\u0000\u00bc\u00b7\u0001\u0000\u0000"+
		"\u0000\u00bc\u00b8\u0001\u0000\u0000\u0000\u00bd\u0102\u0001\u0000\u0000"+
		"\u0000\u00be\u00bf\n\u0015\u0000\u0000\u00bf\u00c0\u0007\u0000\u0000\u0000"+
		"\u00c0\u0101\u0003\n\u0005\u0016\u00c1\u00c2\n\u0014\u0000\u0000\u00c2"+
		"\u00c3\u0007\u0001\u0000\u0000\u00c3\u0101\u0003\n\u0005\u0015\u00c4\u00c5"+
		"\n\u0013\u0000\u0000\u00c5\u00c6\u0005\u0014\u0000\u0000\u00c6\u0101\u0003"+
		"\n\u0005\u0014\u00c7\u00c8\n\u0012\u0000\u0000\u00c8\u00c9\u0007\u0002"+
		"\u0000\u0000\u00c9\u0101\u0003\n\u0005\u0013\u00ca\u00cb\n\u0011\u0000"+
		"\u0000\u00cb\u00cc\u0007\u0003\u0000\u0000\u00cc\u0101\u0003\n\u0005\u0012"+
		"\u00cd\u00ce\n\u0010\u0000\u0000\u00ce\u00cf\u0005H\u0000\u0000\u00cf"+
		"\u0101\u0003\n\u0005\u0011\u00d0\u00d1\n\u000f\u0000\u0000\u00d1\u00d2"+
		"\u0007\u0004\u0000\u0000\u00d2\u0101\u0003\n\u0005\u0010\u00d3\u00d4\n"+
		"\u000e\u0000\u0000\u00d4\u00d5\u0005\f\u0000\u0000\u00d5\u0101\u0003\n"+
		"\u0005\u000f\u00d6\u00d7\n\r\u0000\u0000\u00d7\u00d8\u0005\u0004\u0000"+
		"\u0000\u00d8\u0101\u0003\n\u0005\u000e\u00d9\u00da\n\f\u0000\u0000\u00da"+
		"\u00db\u0005 \u0000\u0000\u00db\u0101\u0003\n\u0005\r\u00dc\u00dd\n\u000b"+
		"\u0000\u0000\u00dd\u00de\u0005!\u0000\u0000\u00de\u0101\u0003\n\u0005"+
		"\f\u00df\u00e0\n\n\u0000\u0000\u00e0\u00e1\u0005\"\u0000\u0000\u00e1\u0101"+
		"\u0003\n\u0005\u000b\u00e2\u00e3\n\t\u0000\u0000\u00e3\u00e4\u0005#\u0000"+
		"\u0000\u00e4\u00e5\u0003\n\u0005\u0000\u00e5\u00e6\u0005$\u0000\u0000"+
		"\u00e6\u00e7\u0003\n\u0005\n\u00e7\u0101\u0001\u0000\u0000\u0000\u00e8"+
		"\u00e9\n\u0007\u0000\u0000\u00e9\u00ea\u0005%\u0000\u0000\u00ea\u0101"+
		"\u0003\n\u0005\u0007\u00eb\u00ec\n\u0006\u0000\u0000\u00ec\u00ed\u0003"+
		"\f\u0006\u0000\u00ed\u00ee\u0003\n\u0005\u0006\u00ee\u0101\u0001\u0000"+
		"\u0000\u0000\u00ef\u00f0\n$\u0000\u0000\u00f0\u0101\u0003\u0004\u0002"+
		"\u0000\u00f1\u00f2\n#\u0000\u0000\u00f2\u0101\u0005\u0005\u0000\u0000"+
		"\u00f3\u00f4\n\"\u0000\u0000\u00f4\u0101\u0005\u0006\u0000\u0000\u00f5"+
		"\u00f6\n \u0000\u0000\u00f6\u00f7\u0005\u0007\u0000\u0000\u00f7\u00f8"+
		"\u0003\n\u0005\u0000\u00f8\u00f9\u0005\b\u0000\u0000\u00f9\u0101\u0001"+
		"\u0000\u0000\u0000\u00fa\u00fb\n\u001f\u0000\u0000\u00fb\u00fd\u0007\u0005"+
		"\u0000\u0000\u00fc\u00fe\u0005\u000b\u0000\u0000\u00fd\u00fc\u0001\u0000"+
		"\u0000\u0000\u00fd\u00fe\u0001\u0000\u0000\u0000\u00fe\u00ff\u0001\u0000"+
		"\u0000\u0000\u00ff\u0101\u0005j\u0000\u0000\u0100\u00be\u0001\u0000\u0000"+
		"\u0000\u0100\u00c1\u0001\u0000\u0000\u0000\u0100\u00c4\u0001\u0000\u0000"+
		"\u0000\u0100\u00c7\u0001\u0000\u0000\u0000\u0100\u00ca\u0001\u0000\u0000"+
		"\u0000\u0100\u00cd\u0001\u0000\u0000\u0000\u0100\u00d0\u0001\u0000\u0000"+
		"\u0000\u0100\u00d3\u0001\u0000\u0000\u0000\u0100\u00d6\u0001\u0000\u0000"+
		"\u0000\u0100\u00d9\u0001\u0000\u0000\u0000\u0100\u00dc\u0001\u0000\u0000"+
		"\u0000\u0100\u00df\u0001\u0000\u0000\u0000\u0100\u00e2\u0001\u0000\u0000"+
		"\u0000\u0100\u00e8\u0001\u0000\u0000\u0000\u0100\u00eb\u0001\u0000\u0000"+
		"\u0000\u0100\u00ef\u0001\u0000\u0000\u0000\u0100\u00f1\u0001\u0000\u0000"+
		"\u0000\u0100\u00f3\u0001\u0000\u0000\u0000\u0100\u00f5\u0001\u0000\u0000"+
		"\u0000\u0100\u00fa\u0001\u0000\u0000\u0000\u0101\u0104\u0001\u0000\u0000"+
		"\u0000\u0102\u0100\u0001\u0000\u0000\u0000\u0102\u0103\u0001\u0000\u0000"+
		"\u0000\u0103\u000b\u0001\u0000\u0000\u0000\u0104\u0102\u0001\u0000\u0000"+
		"\u0000\u0105\u0106\u0007\u0006\u0000\u0000\u0106\r\u0001\u0000\u0000\u0000"+
		"\u0107\u0108\u00053\u0000\u0000\u0108\u000f\u0001\u0000\u0000\u0000\u0109"+
		"\u010a\u0005T\u0000\u0000\u010a\u010b\u0005j\u0000\u0000\u010b\u010f\u0005"+
		"4\u0000\u0000\u010c\u010e\u0003\u0012\t\u0000\u010d\u010c\u0001\u0000"+
		"\u0000\u0000\u010e\u0111\u0001\u0000\u0000\u0000\u010f\u010d\u0001\u0000"+
		"\u0000\u0000\u010f\u0110\u0001\u0000\u0000\u0000\u0110\u0112\u0001\u0000"+
		"\u0000\u0000\u0111\u010f\u0001\u0000\u0000\u0000\u0112\u0113\u0005k\u0000"+
		"\u0000\u0113\u0011\u0001\u0000\u0000\u0000\u0114\u0115\u0003*\u0015\u0000"+
		"\u0115\u0117\u0005j\u0000\u0000\u0116\u0118\u0003\u0014\n\u0000\u0117"+
		"\u0116\u0001\u0000\u0000\u0000\u0117\u0118\u0001\u0000\u0000\u0000\u0118"+
		"\u0119\u0001\u0000\u0000\u0000\u0119\u011a\u0003f3\u0000\u011a\u011f\u0001"+
		"\u0000\u0000\u0000\u011b\u011c\u0003R)\u0000\u011c\u011d\u0003f3\u0000"+
		"\u011d\u011f\u0001\u0000\u0000\u0000\u011e\u0114\u0001\u0000\u0000\u0000"+
		"\u011e\u011b\u0001\u0000\u0000\u0000\u011f\u0013\u0001\u0000\u0000\u0000"+
		"\u0120\u0121\u0005\u0007\u0000\u0000\u0121\u0122\u0005d\u0000\u0000\u0122"+
		"\u0123\u0005\b\u0000\u0000\u0123\u0015\u0001\u0000\u0000\u0000\u0124\u0126"+
		"\u0005^\u0000\u0000\u0125\u0124\u0001\u0000\u0000\u0000\u0125\u0126\u0001"+
		"\u0000\u0000\u0000\u0126\u0127\u0001\u0000\u0000\u0000\u0127\u0128\u0003"+
		"*\u0015\u0000\u0128\u012a\u0005j\u0000\u0000\u0129\u012b\u0003\u0014\n"+
		"\u0000\u012a\u0129\u0001\u0000\u0000\u0000\u012a\u012b\u0001\u0000\u0000"+
		"\u0000\u012b\u012e\u0001\u0000\u0000\u0000\u012c\u012d\u0005%\u0000\u0000"+
		"\u012d\u012f\u0003\n\u0005\u0000\u012e\u012c\u0001\u0000\u0000\u0000\u012e"+
		"\u012f\u0001\u0000\u0000\u0000\u012f\u0135\u0001\u0000\u0000\u0000\u0130"+
		"\u0132\u0005^\u0000\u0000\u0131\u0130\u0001\u0000\u0000\u0000\u0131\u0132"+
		"\u0001\u0000\u0000\u0000\u0132\u0133\u0001\u0000\u0000\u0000\u0133\u0135"+
		"\u0003R)\u0000\u0134\u0125\u0001\u0000\u0000\u0000\u0134\u0131\u0001\u0000"+
		"\u0000\u0000\u0135\u0017\u0001\u0000\u0000\u0000\u0136\u0137\u0003\b\u0004"+
		"\u0000\u0137\u0138\u0003f3\u0000\u0138\u0148\u0001\u0000\u0000\u0000\u0139"+
		"\u013a\u0003\u0016\u000b\u0000\u013a\u013b\u0003f3\u0000\u013b\u0148\u0001"+
		"\u0000\u0000\u0000\u013c\u0148\u0003 \u0010\u0000\u013d\u0148\u0003(\u0014"+
		"\u0000\u013e\u0148\u0003\u001a\r\u0000\u013f\u0148\u0003\u001c\u000e\u0000"+
		"\u0140\u0148\u0003&\u0013\u0000\u0141\u0148\u0003\u001e\u000f\u0000\u0142"+
		"\u0148\u0003\"\u0011\u0000\u0143\u0144\u0003\n\u0005\u0000\u0144\u0145"+
		"\u0003f3\u0000\u0145\u0148\u0001\u0000\u0000\u0000\u0146\u0148\u0003\u000e"+
		"\u0007\u0000\u0147\u0136\u0001\u0000\u0000\u0000\u0147\u0139\u0001\u0000"+
		"\u0000\u0000\u0147\u013c\u0001\u0000\u0000\u0000\u0147\u013d\u0001\u0000"+
		"\u0000\u0000\u0147\u013e\u0001\u0000\u0000\u0000\u0147\u013f\u0001\u0000"+
		"\u0000\u0000\u0147\u0140\u0001\u0000\u0000\u0000\u0147\u0141\u0001\u0000"+
		"\u0000\u0000\u0147\u0142\u0001\u0000\u0000\u0000\u0147\u0143\u0001\u0000"+
		"\u0000\u0000\u0147\u0146\u0001\u0000\u0000\u0000\u0148\u0019\u0001\u0000"+
		"\u0000\u0000\u0149\u014a\u0005N\u0000\u0000\u014a\u014b\u0003f3\u0000"+
		"\u014b\u001b\u0001\u0000\u0000\u0000\u014c\u014d\u0005F\u0000\u0000\u014d"+
		"\u014e\u0003f3\u0000\u014e\u001d\u0001\u0000\u0000\u0000\u014f\u0151\u0005"+
		"L\u0000\u0000\u0150\u0152\u0003\n\u0005\u0000\u0151\u0150\u0001\u0000"+
		"\u0000\u0000\u0151\u0152\u0001\u0000\u0000\u0000\u0152\u0153\u0001\u0000"+
		"\u0000\u0000\u0153\u0154\u0003f3\u0000\u0154\u001f\u0001\u0000\u0000\u0000"+
		"\u0155\u0156\u0003\n\u0005\u0000\u0156\u0157\u0007\u0007\u0000\u0000\u0157"+
		"\u0158\u0003(\u0014\u0000\u0158!\u0001\u0000\u0000\u0000\u0159\u015a\u0005"+
		"P\u0000\u0000\u015a\u015b\u0003\n\u0005\u0000\u015b\u015c\u0003(\u0014"+
		"\u0000\u015c\u0168\u0001\u0000\u0000\u0000\u015d\u015e\u0005O\u0000\u0000"+
		"\u015e\u015f\u0005\u0001\u0000\u0000\u015f\u0160\u0003$\u0012\u0000\u0160"+
		"\u0161\u0005\u0003\u0000\u0000\u0161\u0162\u0003(\u0014\u0000\u0162\u0168"+
		"\u0001\u0000\u0000\u0000\u0163\u0164\u0005O\u0000\u0000\u0164\u0165\u0003"+
		"$\u0012\u0000\u0165\u0166\u0003(\u0014\u0000\u0166\u0168\u0001\u0000\u0000"+
		"\u0000\u0167\u0159\u0001\u0000\u0000\u0000\u0167\u015d\u0001\u0000\u0000"+
		"\u0000\u0167\u0163\u0001\u0000\u0000\u0000\u0168#\u0001\u0000\u0000\u0000"+
		"\u0169\u016e\u0003\u0016\u000b\u0000\u016a\u016c\u0003\n\u0005\u0000\u016b"+
		"\u016a\u0001\u0000\u0000\u0000\u016b\u016c\u0001\u0000\u0000\u0000\u016c"+
		"\u016e\u0001\u0000\u0000\u0000\u016d\u0169\u0001\u0000\u0000\u0000\u016d"+
		"\u016b\u0001\u0000\u0000\u0000\u016e\u016f\u0001\u0000\u0000\u0000\u016f"+
		"\u0171\u00053\u0000\u0000\u0170\u0172\u0003\n\u0005\u0000\u0171\u0170"+
		"\u0001\u0000\u0000\u0000\u0171\u0172\u0001\u0000\u0000\u0000\u0172\u0173"+
		"\u0001\u0000\u0000\u0000\u0173\u0175\u00053\u0000\u0000\u0174\u0176\u0003"+
		"\n\u0005\u0000\u0175\u0174\u0001\u0000\u0000\u0000\u0175\u0176\u0001\u0000"+
		"\u0000\u0000\u0176%\u0001\u0000\u0000\u0000\u0177\u0178\u0005R\u0000\u0000"+
		"\u0178\u0179\u0003\n\u0005\u0000\u0179\u0180\u0003(\u0014\u0000\u017a"+
		"\u017b\u00055\u0000\u0000\u017b\u017c\u0003\n\u0005\u0000\u017c\u017d"+
		"\u0003(\u0014\u0000\u017d\u017f\u0001\u0000\u0000\u0000\u017e\u017a\u0001"+
		"\u0000\u0000\u0000\u017f\u0182\u0001\u0000\u0000\u0000\u0180\u017e\u0001"+
		"\u0000\u0000\u0000\u0180\u0181\u0001\u0000\u0000\u0000\u0181\u0185\u0001"+
		"\u0000\u0000\u0000\u0182\u0180\u0001\u0000\u0000\u0000\u0183\u0184\u0005"+
		"J\u0000\u0000\u0184\u0186\u0003(\u0014\u0000\u0185\u0183\u0001\u0000\u0000"+
		"\u0000\u0185\u0186\u0001\u0000\u0000\u0000\u0186\'\u0001\u0000\u0000\u0000"+
		"\u0187\u018b\u00054\u0000\u0000\u0188\u018a\u0003\u0018\f\u0000\u0189"+
		"\u0188\u0001\u0000\u0000\u0000\u018a\u018d\u0001\u0000\u0000\u0000\u018b"+
		"\u0189\u0001\u0000\u0000\u0000\u018b\u018c\u0001\u0000\u0000\u0000\u018c"+
		"\u018e\u0001\u0000\u0000\u0000\u018d\u018b\u0001\u0000\u0000\u0000\u018e"+
		"\u018f\u0005k\u0000\u0000\u018f)\u0001\u0000\u0000\u0000\u0190\u0192\u0003"+
		"4\u001a\u0000\u0191\u0190\u0001\u0000\u0000\u0000\u0191\u0192\u0001\u0000"+
		"\u0000\u0000\u0192\u0193\u0001\u0000\u0000\u0000\u0193\u0195\u0003:\u001d"+
		"\u0000\u0194\u0196\u0003\u0014\n\u0000\u0195\u0194\u0001\u0000\u0000\u0000"+
		"\u0195\u0196\u0001\u0000\u0000\u0000\u0196\u01a2\u0001\u0000\u0000\u0000"+
		"\u0197\u01a2\u0003,\u0016\u0000\u0198\u01a2\u00036\u001b\u0000\u0199\u01a2"+
		"\u00038\u001c\u0000\u019a\u019c\u00034\u001a\u0000\u019b\u019a\u0001\u0000"+
		"\u0000\u0000\u019b\u019c\u0001\u0000\u0000\u0000\u019c\u019e\u0001\u0000"+
		"\u0000\u0000\u019d\u019f\u0005T\u0000\u0000\u019e\u019d\u0001\u0000\u0000"+
		"\u0000\u019e\u019f\u0001\u0000\u0000\u0000\u019f\u01a0\u0001\u0000\u0000"+
		"\u0000\u01a0\u01a2\u0005j\u0000\u0000\u01a1\u0191\u0001\u0000\u0000\u0000"+
		"\u01a1\u0197\u0001\u0000\u0000\u0000\u01a1\u0198\u0001\u0000\u0000\u0000"+
		"\u01a1\u0199\u0001\u0000\u0000\u0000\u01a1\u019b\u0001\u0000\u0000\u0000"+
		"\u01a2+\u0001\u0000\u0000\u0000\u01a3\u01a4\u0005\u0004\u0000\u0000\u01a4"+
		"\u01a5\u0003*\u0015\u0000\u01a5\u01a6\u0003P(\u0000\u01a6-\u0001\u0000"+
		"\u0000\u0000\u01a7\u01a9\u0003*\u0015\u0000\u01a8\u01aa\u0005j\u0000\u0000"+
		"\u01a9\u01a8\u0001\u0000\u0000\u0000\u01a9\u01aa\u0001\u0000\u0000\u0000"+
		"\u01aa/\u0001\u0000\u0000\u0000\u01ab\u01ac\u00056\u0000\u0000\u01ac\u01ad"+
		"\u0005\u0001\u0000\u0000\u01ad\u01ae\u0005\u0001\u0000\u0000\u01ae\u01af"+
		"\u0005j\u0000\u0000\u01af\u01b0\u0005\u0003\u0000\u0000\u01b0\u01b1\u0005"+
		"\u0003\u0000\u0000\u01b11\u0001\u0000\u0000\u0000\u01b2\u01b3\u0003*\u0015"+
		"\u0000\u01b3\u01b7\u0003P(\u0000\u01b4\u01b6\u00030\u0018\u0000\u01b5"+
		"\u01b4\u0001\u0000\u0000\u0000\u01b6\u01b9\u0001\u0000\u0000\u0000\u01b7"+
		"\u01b5\u0001\u0000\u0000\u0000\u01b7\u01b8\u0001\u0000\u0000\u0000\u01b8"+
		"3\u0001\u0000\u0000\u0000\u01b9\u01b7\u0001\u0000\u0000\u0000\u01ba\u01bb"+
		"\u0007\b\u0000\u0000\u01bb5\u0001\u0000\u0000\u0000\u01bc\u01be\u0003"+
		"4\u001a\u0000\u01bd\u01bc\u0001\u0000\u0000\u0000\u01bd\u01be\u0001\u0000"+
		"\u0000\u0000\u01be\u01c4\u0001\u0000\u0000\u0000\u01bf\u01c5\u0003:\u001d"+
		"\u0000\u01c0\u01c2\u0005T\u0000\u0000\u01c1\u01c0\u0001\u0000\u0000\u0000"+
		"\u01c1\u01c2\u0001\u0000\u0000\u0000\u01c2\u01c3\u0001\u0000\u0000\u0000"+
		"\u01c3\u01c5\u0005j\u0000\u0000\u01c4\u01bf\u0001\u0000\u0000\u0000\u01c4"+
		"\u01c1\u0001\u0000\u0000\u0000\u01c5\u01d3\u0001\u0000\u0000\u0000\u01c6"+
		"\u01c8\u00034\u001a\u0000\u01c7\u01c6\u0001\u0000\u0000\u0000\u01c8\u01cb"+
		"\u0001\u0000\u0000\u0000\u01c9\u01c7\u0001\u0000\u0000\u0000\u01c9\u01ca"+
		"\u0001\u0000\u0000\u0000\u01ca\u01cc\u0001\u0000\u0000\u0000\u01cb\u01c9"+
		"\u0001\u0000\u0000\u0000\u01cc\u01d0\u0005\r\u0000\u0000\u01cd\u01cf\u0003"+
		"4\u001a\u0000\u01ce\u01cd\u0001\u0000\u0000\u0000\u01cf\u01d2\u0001\u0000"+
		"\u0000\u0000\u01d0\u01ce\u0001\u0000\u0000\u0000\u01d0\u01d1\u0001\u0000"+
		"\u0000\u0000\u01d1\u01d4\u0001\u0000\u0000\u0000\u01d2\u01d0\u0001\u0000"+
		"\u0000\u0000\u01d3\u01c9\u0001\u0000\u0000\u0000\u01d4\u01d5\u0001\u0000"+
		"\u0000\u0000\u01d5\u01d3\u0001\u0000\u0000\u0000\u01d5\u01d6\u0001\u0000"+
		"\u0000\u0000\u01d67\u0001\u0000\u0000\u0000\u01d7\u01d9\u0005T\u0000\u0000"+
		"\u01d8\u01d7\u0001\u0000\u0000\u0000\u01d8\u01d9\u0001\u0000\u0000\u0000"+
		"\u01d9\u01da\u0001\u0000\u0000\u0000\u01da\u01db\u0005j\u0000\u0000\u01db"+
		"\u01dc\u0005:\u0000\u0000\u01dc9\u0001\u0000\u0000\u0000\u01dd\u01f5\u0005"+
		";\u0000\u0000\u01de\u01f5\u0005<\u0000\u0000\u01df\u01f5\u0005=\u0000"+
		"\u0000\u01e0\u01f5\u0005>\u0000\u0000\u01e1\u01f5\u0005?\u0000\u0000\u01e2"+
		"\u01f5\u0005@\u0000\u0000\u01e3\u01f5\u0005M\u0000\u0000\u01e4\u01f5\u0005"+
		"A\u0000\u0000\u01e5\u01e6\u0005A\u0000\u0000\u01e6\u01f5\u0005A\u0000"+
		"\u0000\u01e7\u01e8\u0005A\u0000\u0000\u01e8\u01f5\u0005>\u0000\u0000\u01e9"+
		"\u01ea\u0005B\u0000\u0000\u01ea\u01f5\u0005?\u0000\u0000\u01eb\u01ec\u0005"+
		"B\u0000\u0000\u01ec\u01f5\u0005;\u0000\u0000\u01ed\u01ee\u0005B\u0000"+
		"\u0000\u01ee\u01f5\u0005<\u0000\u0000\u01ef\u01f0\u0005B\u0000\u0000\u01f0"+
		"\u01f5\u0005A\u0000\u0000\u01f1\u01f2\u0005B\u0000\u0000\u01f2\u01f3\u0005"+
		"A\u0000\u0000\u01f3\u01f5\u0005A\u0000\u0000\u01f4\u01dd\u0001\u0000\u0000"+
		"\u0000\u01f4\u01de\u0001\u0000\u0000\u0000\u01f4\u01df\u0001\u0000\u0000"+
		"\u0000\u01f4\u01e0\u0001\u0000\u0000\u0000\u01f4\u01e1\u0001\u0000\u0000"+
		"\u0000\u01f4\u01e2\u0001\u0000\u0000\u0000\u01f4\u01e3\u0001\u0000\u0000"+
		"\u0000\u01f4\u01e4\u0001\u0000\u0000\u0000\u01f4\u01e5\u0001\u0000\u0000"+
		"\u0000\u01f4\u01e7\u0001\u0000\u0000\u0000\u01f4\u01e9\u0001\u0000\u0000"+
		"\u0000\u01f4\u01eb\u0001\u0000\u0000\u0000\u01f4\u01ed\u0001\u0000\u0000"+
		"\u0000\u01f4\u01ef\u0001\u0000\u0000\u0000\u01f4\u01f1\u0001\u0000\u0000"+
		"\u0000\u01f5;\u0001\u0000\u0000\u0000\u01f6\u01f7\u0005V\u0000\u0000\u01f7"+
		"\u01f8\u0005j\u0000\u0000\u01f8\u01f9\u00054\u0000\u0000\u01f9\u01fe\u0003"+
		">\u001f\u0000\u01fa\u01fb\u0005\u0002\u0000\u0000\u01fb\u01fd\u0003>\u001f"+
		"\u0000\u01fc\u01fa\u0001\u0000\u0000\u0000\u01fd\u0200\u0001\u0000\u0000"+
		"\u0000\u01fe\u01fc\u0001\u0000\u0000\u0000\u01fe\u01ff\u0001\u0000\u0000"+
		"\u0000\u01ff\u0202\u0001\u0000\u0000\u0000\u0200\u01fe\u0001\u0000\u0000"+
		"\u0000\u0201\u0203\u0005\u0002\u0000\u0000\u0202\u0201\u0001\u0000\u0000"+
		"\u0000\u0202\u0203\u0001\u0000\u0000\u0000\u0203\u0204\u0001\u0000\u0000"+
		"\u0000\u0204\u0205\u0005k\u0000\u0000\u0205\u0206\u0003f3\u0000\u0206"+
		"=\u0001\u0000\u0000\u0000\u0207\u020a\u0005j\u0000\u0000\u0208\u0209\u0005"+
		"%\u0000\u0000\u0209\u020b\u0005d\u0000\u0000\u020a\u0208\u0001\u0000\u0000"+
		"\u0000\u020a\u020b\u0001\u0000\u0000\u0000\u020b?\u0001\u0000\u0000\u0000"+
		"\u020c\u020d\u0005Z\u0000\u0000\u020d\u020e\u0005j\u0000\u0000\u020e\u020f"+
		"\u0003B!\u0000\u020fA\u0001\u0000\u0000\u0000\u0210\u0214\u00054\u0000"+
		"\u0000\u0211\u0213\u0003J%\u0000\u0212\u0211\u0001\u0000\u0000\u0000\u0213"+
		"\u0216\u0001\u0000\u0000\u0000\u0214\u0212\u0001\u0000\u0000\u0000\u0214"+
		"\u0215\u0001\u0000\u0000\u0000\u0215\u0217\u0001\u0000\u0000\u0000\u0216"+
		"\u0214\u0001\u0000\u0000\u0000\u0217\u0218\u0005k\u0000\u0000\u0218C\u0001"+
		"\u0000\u0000\u0000\u0219\u021b\u0005U\u0000\u0000\u021a\u021c\u0005a\u0000"+
		"\u0000\u021b\u021a\u0001\u0000\u0000\u0000\u021b\u021c\u0001\u0000\u0000"+
		"\u0000\u021c\u021d\u0001\u0000\u0000\u0000\u021d\u0220\u0005j\u0000\u0000"+
		"\u021e\u021f\u0005W\u0000\u0000\u021f\u0221\u0005j\u0000\u0000\u0220\u021e"+
		"\u0001\u0000\u0000\u0000\u0220\u0221\u0001\u0000\u0000\u0000\u0221\u0222"+
		"\u0001\u0000\u0000\u0000\u0222\u0223\u0003F#\u0000\u0223\u0224\u0003f"+
		"3\u0000\u0224E\u0001\u0000\u0000\u0000\u0225\u022a\u00054\u0000\u0000"+
		"\u0226\u0229\u0003H$\u0000\u0227\u0229\u0003J%\u0000\u0228\u0226\u0001"+
		"\u0000\u0000\u0000\u0228\u0227\u0001\u0000\u0000\u0000\u0229\u022c\u0001"+
		"\u0000\u0000\u0000\u022a\u0228\u0001\u0000\u0000\u0000\u022a\u022b\u0001"+
		"\u0000\u0000\u0000\u022b\u022d\u0001\u0000\u0000\u0000\u022c\u022a\u0001"+
		"\u0000\u0000\u0000\u022d\u022e\u0005k\u0000\u0000\u022eG\u0001\u0000\u0000"+
		"\u0000\u022f\u0230\u0003*\u0015\u0000\u0230\u0232\u0005j\u0000\u0000\u0231"+
		"\u0233\u0003\u0014\n\u0000\u0232\u0231\u0001\u0000\u0000\u0000\u0232\u0233"+
		"\u0001\u0000\u0000\u0000\u0233\u0235\u0001\u0000\u0000\u0000\u0234\u0236"+
		"\u0003L&\u0000\u0235\u0234\u0001\u0000\u0000\u0000\u0235\u0236\u0001\u0000"+
		"\u0000\u0000\u0236\u0237\u0001\u0000\u0000\u0000\u0237\u0238\u0003f3\u0000"+
		"\u0238\u0240\u0001\u0000\u0000\u0000\u0239\u023b\u0003R)\u0000\u023a\u023c"+
		"\u0003L&\u0000\u023b\u023a\u0001\u0000\u0000\u0000\u023b\u023c\u0001\u0000"+
		"\u0000\u0000\u023c\u023d\u0001\u0000\u0000\u0000\u023d\u023e\u0003f3\u0000"+
		"\u023e\u0240\u0001\u0000\u0000\u0000\u023f\u022f\u0001\u0000\u0000\u0000"+
		"\u023f\u0239\u0001\u0000\u0000\u0000\u0240I\u0001\u0000\u0000\u0000\u0241"+
		"\u0244\u0003T*\u0000\u0242\u0244\u0003Z-\u0000\u0243\u0241\u0001\u0000"+
		"\u0000\u0000\u0243\u0242\u0001\u0000\u0000\u0000\u0244K\u0001\u0000\u0000"+
		"\u0000\u0245\u0246\u0005%\u0000\u0000\u0246\u0247\u0003\n\u0005\u0000"+
		"\u0247M\u0001\u0000\u0000\u0000\u0248\u024a\u0003*\u0015\u0000\u0249\u024b"+
		"\u0005j\u0000\u0000\u024a\u0249\u0001\u0000\u0000\u0000\u024a\u024b\u0001"+
		"\u0000\u0000\u0000\u024b\u024e\u0001\u0000\u0000\u0000\u024c\u024e\u0003"+
		"R)\u0000\u024d\u0248\u0001\u0000\u0000\u0000\u024d\u024c\u0001\u0000\u0000"+
		"\u0000\u024eO\u0001\u0000\u0000\u0000\u024f\u0258\u0005\u0001\u0000\u0000"+
		"\u0250\u0255\u0003N\'\u0000\u0251\u0252\u0005\u0002\u0000\u0000\u0252"+
		"\u0254\u0003N\'\u0000\u0253\u0251\u0001\u0000\u0000\u0000\u0254\u0257"+
		"\u0001\u0000\u0000\u0000\u0255\u0253\u0001\u0000\u0000\u0000\u0255\u0256"+
		"\u0001\u0000\u0000\u0000\u0256\u0259\u0001\u0000\u0000\u0000\u0257\u0255"+
		"\u0001\u0000\u0000\u0000\u0258\u0250\u0001\u0000\u0000\u0000\u0258\u0259"+
		"\u0001\u0000\u0000\u0000\u0259\u025b\u0001\u0000\u0000\u0000\u025a\u025c"+
		"\u0005\u0002\u0000\u0000\u025b\u025a\u0001\u0000\u0000\u0000\u025b\u025c"+
		"\u0001\u0000\u0000\u0000\u025c\u025d\u0001\u0000\u0000\u0000\u025d\u0260"+
		"\u0005\u0003\u0000\u0000\u025e\u0260\u0001\u0000\u0000\u0000\u025f\u024f"+
		"\u0001\u0000\u0000\u0000\u025f\u025e\u0001\u0000\u0000\u0000\u0260Q\u0001"+
		"\u0000\u0000\u0000\u0261\u0262\u0003*\u0015\u0000\u0262\u0264\u0005\u0001"+
		"\u0000\u0000\u0263\u0265\u0005\r\u0000\u0000\u0264\u0263\u0001\u0000\u0000"+
		"\u0000\u0265\u0266\u0001\u0000\u0000\u0000\u0266\u0264\u0001\u0000\u0000"+
		"\u0000\u0266\u0267\u0001\u0000\u0000\u0000\u0267\u0269\u0001\u0000\u0000"+
		"\u0000\u0268\u026a\u0005j\u0000\u0000\u0269\u0268\u0001\u0000\u0000\u0000"+
		"\u0269\u026a\u0001\u0000\u0000\u0000\u026a\u026b\u0001\u0000\u0000\u0000"+
		"\u026b\u026c\u0005\u0003\u0000\u0000\u026c\u0270\u0003P(\u0000\u026d\u026f"+
		"\u00030\u0018\u0000\u026e\u026d\u0001\u0000\u0000\u0000\u026f\u0272\u0001"+
		"\u0000\u0000\u0000\u0270\u026e\u0001\u0000\u0000\u0000\u0270\u0271\u0001"+
		"\u0000\u0000\u0000\u0271S\u0001\u0000\u0000\u0000\u0272\u0270\u0001\u0000"+
		"\u0000\u0000\u0273\u0274\u0003*\u0015\u0000\u0274\u0275\u0005j\u0000\u0000"+
		"\u0275\u0276\u0003P(\u0000\u0276\u0277\u0003(\u0014\u0000\u0277U\u0001"+
		"\u0000\u0000\u0000\u0278\u027a\u0005^\u0000\u0000\u0279\u0278\u0001\u0000"+
		"\u0000\u0000\u0279\u027a\u0001\u0000\u0000\u0000\u027a\u027b\u0001\u0000"+
		"\u0000\u0000\u027b\u0281\u0003T*\u0000\u027c\u027e\u0005^\u0000\u0000"+
		"\u027d\u027c\u0001\u0000\u0000\u0000\u027d\u027e\u0001\u0000\u0000\u0000"+
		"\u027e\u027f\u0001\u0000\u0000\u0000\u027f\u0281\u0003Z-\u0000\u0280\u0279"+
		"\u0001\u0000\u0000\u0000\u0280\u027d\u0001\u0000\u0000\u0000\u0281W\u0001"+
		"\u0000\u0000\u0000\u0282\u0283\u0003\u0016\u000b\u0000\u0283\u0284\u0003"+
		"f3\u0000\u0284Y\u0001\u0000\u0000\u0000\u0285\u0286\u0005X\u0000\u0000"+
		"\u0286\u0287\u0003*\u0015\u0000\u0287\u0288\u0005j\u0000\u0000\u0288\u0289"+
		"\u0003P(\u0000\u0289\u028a\u0003f3\u0000\u028a[\u0001\u0000\u0000\u0000"+
		"\u028b\u028c\u0005]\u0000\u0000\u028c\u028d\u0005\r\u0000\u0000\u028d"+
		"\u028e\u0005S\u0000\u0000\u028e\u028f\u0005h\u0000\u0000\u028f\u0296\u0003"+
		"f3\u0000\u0290\u0291\u0005C\u0000\u0000\u0291\u0292\u0005\r\u0000\u0000"+
		"\u0292\u0293\u0005S\u0000\u0000\u0293\u0294\u0005h\u0000\u0000\u0294\u0296"+
		"\u0003f3\u0000\u0295\u028b\u0001\u0000\u0000\u0000\u0295\u0290\u0001\u0000"+
		"\u0000\u0000\u0296]\u0001\u0000\u0000\u0000\u0297\u0298\u0005D\u0000\u0000"+
		"\u0298\u0299\u0003`0\u0000\u0299\u029a\u0003f3\u0000\u029a_\u0001\u0000"+
		"\u0000\u0000\u029b\u029f\u0005\u0018\u0000\u0000\u029c\u029e\b\t\u0000"+
		"\u0000\u029d\u029c\u0001\u0000\u0000\u0000\u029e\u02a1\u0001\u0000\u0000"+
		"\u0000\u029f\u029d\u0001\u0000\u0000\u0000\u029f\u02a0\u0001\u0000\u0000"+
		"\u0000\u02a0\u02a2\u0001\u0000\u0000\u0000\u02a1\u029f\u0001\u0000\u0000"+
		"\u0000\u02a2\u02a5\u0005\u0019\u0000\u0000\u02a3\u02a5\u0005h\u0000\u0000"+
		"\u02a4\u029b\u0001\u0000\u0000\u0000\u02a4\u02a3\u0001\u0000\u0000\u0000"+
		"\u02a5a\u0001\u0000\u0000\u0000\u02a6\u02a7\u0005E\u0000\u0000\u02a7\u02a8"+
		"\u0005j\u0000\u0000\u02a8\u02a9\u0003f3\u0000\u02a9c\u0001\u0000\u0000"+
		"\u0000\u02aa\u02ab\u0007\n\u0000\u0000\u02abe\u0001\u0000\u0000\u0000"+
		"\u02ac\u02b1\u00053\u0000\u0000\u02ad\u02b1\u0005\u0000\u0000\u0001\u02ae"+
		"\u02b1\u00043\u0014\u0000\u02af\u02b1\u00043\u0015\u0000\u02b0\u02ac\u0001"+
		"\u0000\u0000\u0000\u02b0\u02ad\u0001\u0000\u0000\u0000\u02b0\u02ae\u0001"+
		"\u0000\u0000\u0000\u02b0\u02af\u0001\u0000\u0000\u0000\u02b1g\u0001\u0000"+
		"\u0000\u0000Ikx\u0080\u0084\u0086\u008f\u0095\u00bc\u00fd\u0100\u0102"+
		"\u010f\u0117\u011e\u0125\u012a\u012e\u0131\u0134\u0147\u0151\u0167\u016b"+
		"\u016d\u0171\u0175\u0180\u0185\u018b\u0191\u0195\u019b\u019e\u01a1\u01a9"+
		"\u01b7\u01bd\u01c1\u01c4\u01c9\u01d0\u01d5\u01d8\u01f4\u01fe\u0202\u020a"+
		"\u0214\u021b\u0220\u0228\u022a\u0232\u0235\u023b\u023f\u0243\u024a\u024d"+
		"\u0255\u0258\u025b\u025f\u0266\u0269\u0270\u0279\u027d\u0280\u0295\u029f"+
		"\u02a4\u02b0";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}