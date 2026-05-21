
    #include "OrcParserBase.h"


// Generated from Orc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace antlrcpptest {


class  OrcParser : public OrcParserBase {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, T__61 = 62, 
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, T__67 = 68, 
    T__68 = 69, Break = 70, Do = 71, Instanceof = 72, Case = 73, Else = 74, 
    New = 75, Catch = 76, Finally = 77, Return = 78, Void = 79, Continue = 80, 
    For = 81, While = 82, This = 83, If = 84, Throw = 85, Try = 86, From = 87, 
    Struct = 88, Class = 89, Enum = 90, Extends = 91, Extern = 92, Super = 93, 
    Extension = 94, Const = 95, Export = 96, Import = 97, Static = 98, Async = 99, 
    Await = 100, Refc = 101, NullLiteral = 102, BooleanLiteral = 103, DecimalLiteral = 104, 
    HexIntegerLiteral = 105, OctalIntegerLiteral = 106, BinaryIntegerLiteral = 107, 
    StringLiteral = 108, CharLiteral = 109, Id = 110, CloseBrace = 111, 
    LineTerminator = 112, Whitespace = 113, BlockComment = 114, LineComment = 115
  };

  enum {
    RuleProgram = 0, RuleRootDeclaration = 1, RuleArguments = 2, RuleExpressionSequence = 3, 
    RuleClosureExpression = 4, RuleSingleExpression = 5, RuleAssignmentOperator = 6, 
    RuleEmptyStatement = 7, RuleStructDefinition = 8, RuleStructMember = 9, 
    RuleArraySizeDeclaration = 10, RuleVarDeclaration = 11, RuleStatement = 12, 
    RuleContinueStatement = 13, RuleBreakStatement = 14, RuleThrowStatement = 15, 
    RuleReturnStatement = 16, RuleScopeStatement = 17, RuleIterationStatement = 18, 
    RuleForCondition = 19, RuleSelectionStatement = 20, RuleTryStatement = 21, 
    RuleCatchClause = 22, RuleFinallyClause = 23, RuleBlock = 24, RuleType = 25, 
    RuleClosureType = 26, RuleFunctionTypeArg = 27, RuleAttribute = 28, 
    RuleFunctionType = 29, RuleTypeQualifier = 30, RulePointer = 31, RuleRef = 32, 
    RulePrimitiveType = 33, RuleEnumDefinition = 34, RuleEnumItem = 35, 
    RuleExtensionDefinition = 36, RuleExtensionBlock = 37, RuleClassDefinition = 38, 
    RuleClassDefinitionBlock = 39, RuleClassFieldDeclaration = 40, RuleMethodDeclaration = 41, 
    RuleAssignRightPart = 42, RuleArgumentDeclaration = 43, RuleArgumentsDeclaration = 44, 
    RuleFunctionPointerVarDeclaration = 45, RuleFunctionDefinition = 46, 
    RuleGlobalFunctionDefinition = 47, RuleGlobalVarDeclaration = 48, RuleExternFunctionDeclaration = 49, 
    RuleImportStatement = 50, RuleIncludeStatement = 51, RuleIncludePathCharacters = 52, 
    RulePackageStatement = 53, RuleLiteral = 54, RuleEos = 55
  };

  explicit OrcParser(antlr4::TokenStream *input);

  OrcParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~OrcParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class RootDeclarationContext;
  class ArgumentsContext;
  class ExpressionSequenceContext;
  class ClosureExpressionContext;
  class SingleExpressionContext;
  class AssignmentOperatorContext;
  class EmptyStatementContext;
  class StructDefinitionContext;
  class StructMemberContext;
  class ArraySizeDeclarationContext;
  class VarDeclarationContext;
  class StatementContext;
  class ContinueStatementContext;
  class BreakStatementContext;
  class ThrowStatementContext;
  class ReturnStatementContext;
  class ScopeStatementContext;
  class IterationStatementContext;
  class ForConditionContext;
  class SelectionStatementContext;
  class TryStatementContext;
  class CatchClauseContext;
  class FinallyClauseContext;
  class BlockContext;
  class TypeContext;
  class ClosureTypeContext;
  class FunctionTypeArgContext;
  class AttributeContext;
  class FunctionTypeContext;
  class TypeQualifierContext;
  class PointerContext;
  class RefContext;
  class PrimitiveTypeContext;
  class EnumDefinitionContext;
  class EnumItemContext;
  class ExtensionDefinitionContext;
  class ExtensionBlockContext;
  class ClassDefinitionContext;
  class ClassDefinitionBlockContext;
  class ClassFieldDeclarationContext;
  class MethodDeclarationContext;
  class AssignRightPartContext;
  class ArgumentDeclarationContext;
  class ArgumentsDeclarationContext;
  class FunctionPointerVarDeclarationContext;
  class FunctionDefinitionContext;
  class GlobalFunctionDefinitionContext;
  class GlobalVarDeclarationContext;
  class ExternFunctionDeclarationContext;
  class ImportStatementContext;
  class IncludeStatementContext;
  class IncludePathCharactersContext;
  class PackageStatementContext;
  class LiteralContext;
  class EosContext; 

  class  ProgramContext : public OrcRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RootDeclarationContext *> rootDeclaration();
    RootDeclarationContext* rootDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  RootDeclarationContext : public OrcRuleContext {
  public:
    RootDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PackageStatementContext *packageStatement();
    IncludeStatementContext *includeStatement();
    ImportStatementContext *importStatement();
    StructDefinitionContext *structDefinition();
    EnumDefinitionContext *enumDefinition();
    ClassDefinitionContext *classDefinition();
    ExtensionDefinitionContext *extensionDefinition();
    GlobalVarDeclarationContext *globalVarDeclaration();
    GlobalFunctionDefinitionContext *globalFunctionDefinition();
    EmptyStatementContext *emptyStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RootDeclarationContext* rootDeclaration();

  class  ArgumentsContext : public OrcRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  ExpressionSequenceContext : public OrcRuleContext {
  public:
    ExpressionSequenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionSequenceContext* expressionSequence();

  class  ClosureExpressionContext : public OrcRuleContext {
  public:
    ClosureExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    ArgumentsDeclarationContext *argumentsDeclaration();
    BlockContext *block();
    antlr4::tree::TerminalNode *Id();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosureExpressionContext* closureExpression();

  class  SingleExpressionContext : public OrcRuleContext {
  public:
    SingleExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    SingleExpressionContext() = default;
    void copyFrom(SingleExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TernaryExpressionContext : public SingleExpressionContext {
  public:
    TernaryExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalAndExpressionContext : public SingleExpressionContext {
  public:
    LogicalAndExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PreIncrementExpressionContext : public SingleExpressionContext {
  public:
    PreIncrementExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GetAddressExpressionContext : public SingleExpressionContext {
  public:
    GetAddressExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalOrExpressionContext : public SingleExpressionContext {
  public:
    LogicalOrExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotExpressionContext : public SingleExpressionContext {
  public:
    NotExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PreDecreaseExpressionContext : public SingleExpressionContext {
  public:
    PreDecreaseExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ThisExpressionContext : public SingleExpressionContext {
  public:
    ThisExpressionContext(SingleExpressionContext *ctx);

    antlr4::tree::TerminalNode *This();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryMinusExpressionContext : public SingleExpressionContext {
  public:
    UnaryMinusExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignmentExpressionContext : public SingleExpressionContext {
  public:
    AssignmentExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PostDecreaseExpressionContext : public SingleExpressionContext {
  public:
    PostDecreaseExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InstanceofExpressionContext : public SingleExpressionContext {
  public:
    InstanceofExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    antlr4::tree::TerminalNode *Instanceof();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryPlusExpressionContext : public SingleExpressionContext {
  public:
    UnaryPlusExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EqualityExpressionContext : public SingleExpressionContext {
  public:
    EqualityExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitXOrExpressionContext : public SingleExpressionContext {
  public:
    BitXOrExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SuperExpressionContext : public SingleExpressionContext {
  public:
    SuperExpressionContext(SingleExpressionContext *ctx);

    antlr4::tree::TerminalNode *Super();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MultiplicativeExpressionContext : public SingleExpressionContext {
  public:
    MultiplicativeExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CallExpressionContext : public SingleExpressionContext {
  public:
    CallExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    ArgumentsContext *arguments();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitShiftExpressionContext : public SingleExpressionContext {
  public:
    BitShiftExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesizedExpressionContext : public SingleExpressionContext {
  public:
    ParenthesizedExpressionContext(SingleExpressionContext *ctx);

    ExpressionSequenceContext *expressionSequence();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AdditiveExpressionContext : public SingleExpressionContext {
  public:
    AdditiveExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RelationalExpressionContext : public SingleExpressionContext {
  public:
    RelationalExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PostIncrementExpressionContext : public SingleExpressionContext {
  public:
    PostIncrementExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitNotExpressionContext : public SingleExpressionContext {
  public:
    BitNotExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NewExpressionContext : public SingleExpressionContext {
  public:
    NewExpressionContext(SingleExpressionContext *ctx);

    antlr4::tree::TerminalNode *New();
    antlr4::tree::TerminalNode *Id();
    ArgumentsContext *arguments();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralExpressionContext : public SingleExpressionContext {
  public:
    LiteralExpressionContext(SingleExpressionContext *ctx);

    LiteralContext *literal();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MemberDotExpressionContext : public SingleExpressionContext {
  public:
    MemberDotExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    antlr4::tree::TerminalNode *Id();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MemberIndexExpressionContext : public SingleExpressionContext {
  public:
    MemberIndexExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DerefExpressionContext : public SingleExpressionContext {
  public:
    DerefExpressionContext(SingleExpressionContext *ctx);

    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdentifierExpressionContext : public SingleExpressionContext {
  public:
    IdentifierExpressionContext(SingleExpressionContext *ctx);

    antlr4::tree::TerminalNode *Id();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitAndExpressionContext : public SingleExpressionContext {
  public:
    BitAndExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitOrExpressionContext : public SingleExpressionContext {
  public:
    BitOrExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignmentOperatorExpressionContext : public SingleExpressionContext {
  public:
    AssignmentOperatorExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    AssignmentOperatorContext *assignmentOperator();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CastExpressionContext : public SingleExpressionContext {
  public:
    CastExpressionContext(SingleExpressionContext *ctx);

    TypeContext *type();
    SingleExpressionContext *singleExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CoalesceExpressionContext : public SingleExpressionContext {
  public:
    CoalesceExpressionContext(SingleExpressionContext *ctx);

    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LabelClosureExpressionContext : public SingleExpressionContext {
  public:
    LabelClosureExpressionContext(SingleExpressionContext *ctx);

    ClosureExpressionContext *closureExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  SingleExpressionContext* singleExpression();
  SingleExpressionContext* singleExpression(int precedence);
  class  AssignmentOperatorContext : public OrcRuleContext {
  public:
    AssignmentOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentOperatorContext* assignmentOperator();

  class  EmptyStatementContext : public OrcRuleContext {
  public:
    EmptyStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmptyStatementContext* emptyStatement();

  class  StructDefinitionContext : public OrcRuleContext {
  public:
    StructDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Struct();
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *CloseBrace();
    std::vector<StructMemberContext *> structMember();
    StructMemberContext* structMember(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDefinitionContext* structDefinition();

  class  StructMemberContext : public OrcRuleContext {
  public:
    StructMemberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *Id();
    EosContext *eos();
    ArraySizeDeclarationContext *arraySizeDeclaration();
    FunctionPointerVarDeclarationContext *functionPointerVarDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructMemberContext* structMember();

  class  ArraySizeDeclarationContext : public OrcRuleContext {
  public:
    ArraySizeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DecimalLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArraySizeDeclarationContext* arraySizeDeclaration();

  class  VarDeclarationContext : public OrcRuleContext {
  public:
    VarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *Static();
    ArraySizeDeclarationContext *arraySizeDeclaration();
    SingleExpressionContext *singleExpression();
    FunctionPointerVarDeclarationContext *functionPointerVarDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDeclarationContext* varDeclaration();

  class  StatementContext : public OrcRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClosureExpressionContext *closureExpression();
    EosContext *eos();
    VarDeclarationContext *varDeclaration();
    ScopeStatementContext *scopeStatement();
    BlockContext *block();
    ContinueStatementContext *continueStatement();
    BreakStatementContext *breakStatement();
    ThrowStatementContext *throwStatement();
    SelectionStatementContext *selectionStatement();
    ReturnStatementContext *returnStatement();
    IterationStatementContext *iterationStatement();
    TryStatementContext *tryStatement();
    SingleExpressionContext *singleExpression();
    EmptyStatementContext *emptyStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ContinueStatementContext : public OrcRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Continue();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  BreakStatementContext : public OrcRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Break();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ThrowStatementContext : public OrcRuleContext {
  public:
    ThrowStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Throw();
    SingleExpressionContext *singleExpression();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ThrowStatementContext* throwStatement();

  class  ReturnStatementContext : public OrcRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Return();
    EosContext *eos();
    SingleExpressionContext *singleExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  ScopeStatementContext : public OrcRuleContext {
  public:
    ScopeStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SingleExpressionContext *singleExpression();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScopeStatementContext* scopeStatement();

  class  IterationStatementContext : public OrcRuleContext {
  public:
    IterationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *While();
    SingleExpressionContext *singleExpression();
    BlockContext *block();
    antlr4::tree::TerminalNode *For();
    ForConditionContext *forCondition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IterationStatementContext* iterationStatement();

  class  ForConditionContext : public OrcRuleContext {
  public:
    ForConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarDeclarationContext *varDeclaration();
    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForConditionContext* forCondition();

  class  SelectionStatementContext : public OrcRuleContext {
  public:
    SelectionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *If();
    std::vector<SingleExpressionContext *> singleExpression();
    SingleExpressionContext* singleExpression(size_t i);
    std::vector<BlockContext *> block();
    BlockContext* block(size_t i);
    antlr4::tree::TerminalNode *Else();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectionStatementContext* selectionStatement();

  class  TryStatementContext : public OrcRuleContext {
  public:
    TryStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Try();
    BlockContext *block();
    std::vector<CatchClauseContext *> catchClause();
    CatchClauseContext* catchClause(size_t i);
    FinallyClauseContext *finallyClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TryStatementContext* tryStatement();

  class  CatchClauseContext : public OrcRuleContext {
  public:
    CatchClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Catch();
    RefContext *ref();
    BlockContext *block();
    antlr4::tree::TerminalNode *Id();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CatchClauseContext* catchClause();

  class  FinallyClauseContext : public OrcRuleContext {
  public:
    FinallyClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Finally();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FinallyClauseContext* finallyClause();

  class  BlockContext : public OrcRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CloseBrace();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  TypeContext : public OrcRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimitiveTypeContext *primitiveType();
    TypeQualifierContext *typeQualifier();
    ArraySizeDeclarationContext *arraySizeDeclaration();
    ClosureTypeContext *closureType();
    PointerContext *pointer();
    RefContext *ref();
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *Struct();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  ClosureTypeContext : public OrcRuleContext {
  public:
    ClosureTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    ArgumentsDeclarationContext *argumentsDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClosureTypeContext* closureType();

  class  FunctionTypeArgContext : public OrcRuleContext {
  public:
    FunctionTypeArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *Id();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionTypeArgContext* functionTypeArg();

  class  AttributeContext : public OrcRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Id();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeContext* attribute();

  class  FunctionTypeContext : public OrcRuleContext {
  public:
    FunctionTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    ArgumentsDeclarationContext *argumentsDeclaration();
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionTypeContext* functionType();

  class  TypeQualifierContext : public OrcRuleContext {
  public:
    TypeQualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeQualifierContext* typeQualifier();

  class  PointerContext : public OrcRuleContext {
  public:
    PointerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimitiveTypeContext *primitiveType();
    std::vector<TypeQualifierContext *> typeQualifier();
    TypeQualifierContext* typeQualifier(size_t i);
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *Struct();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PointerContext* pointer();

  class  RefContext : public OrcRuleContext {
  public:
    RefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *Struct();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RefContext* ref();

  class  PrimitiveTypeContext : public OrcRuleContext {
  public:
    PrimitiveTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimitiveTypeContext* primitiveType();

  class  EnumDefinitionContext : public OrcRuleContext {
  public:
    EnumDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Enum();
    antlr4::tree::TerminalNode *Id();
    std::vector<EnumItemContext *> enumItem();
    EnumItemContext* enumItem(size_t i);
    antlr4::tree::TerminalNode *CloseBrace();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumDefinitionContext* enumDefinition();

  class  EnumItemContext : public OrcRuleContext {
  public:
    EnumItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Id();
    antlr4::tree::TerminalNode *DecimalLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumItemContext* enumItem();

  class  ExtensionDefinitionContext : public OrcRuleContext {
  public:
    ExtensionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Extension();
    antlr4::tree::TerminalNode *Id();
    ExtensionBlockContext *extensionBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExtensionDefinitionContext* extensionDefinition();

  class  ExtensionBlockContext : public OrcRuleContext {
  public:
    ExtensionBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CloseBrace();
    std::vector<MethodDeclarationContext *> methodDeclaration();
    MethodDeclarationContext* methodDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExtensionBlockContext* extensionBlock();

  class  ClassDefinitionContext : public OrcRuleContext {
  public:
    ClassDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Class();
    std::vector<antlr4::tree::TerminalNode *> Id();
    antlr4::tree::TerminalNode* Id(size_t i);
    ClassDefinitionBlockContext *classDefinitionBlock();
    EosContext *eos();
    antlr4::tree::TerminalNode *Refc();
    antlr4::tree::TerminalNode *Extends();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassDefinitionContext* classDefinition();

  class  ClassDefinitionBlockContext : public OrcRuleContext {
  public:
    ClassDefinitionBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CloseBrace();
    std::vector<ClassFieldDeclarationContext *> classFieldDeclaration();
    ClassFieldDeclarationContext* classFieldDeclaration(size_t i);
    std::vector<MethodDeclarationContext *> methodDeclaration();
    MethodDeclarationContext* methodDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassDefinitionBlockContext* classDefinitionBlock();

  class  ClassFieldDeclarationContext : public OrcRuleContext {
  public:
    ClassFieldDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *Id();
    EosContext *eos();
    ArraySizeDeclarationContext *arraySizeDeclaration();
    AssignRightPartContext *assignRightPart();
    FunctionPointerVarDeclarationContext *functionPointerVarDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassFieldDeclarationContext* classFieldDeclaration();

  class  MethodDeclarationContext : public OrcRuleContext {
  public:
    MethodDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDefinitionContext *functionDefinition();
    ExternFunctionDeclarationContext *externFunctionDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MethodDeclarationContext* methodDeclaration();

  class  AssignRightPartContext : public OrcRuleContext {
  public:
    AssignRightPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SingleExpressionContext *singleExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignRightPartContext* assignRightPart();

  class  ArgumentDeclarationContext : public OrcRuleContext {
  public:
    ArgumentDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *Id();
    FunctionPointerVarDeclarationContext *functionPointerVarDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentDeclarationContext* argumentDeclaration();

  class  ArgumentsDeclarationContext : public OrcRuleContext {
  public:
    ArgumentsDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentDeclarationContext *> argumentDeclaration();
    ArgumentDeclarationContext* argumentDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsDeclarationContext* argumentsDeclaration();

  class  FunctionPointerVarDeclarationContext : public OrcRuleContext {
  public:
    FunctionPointerVarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    ArgumentsDeclarationContext *argumentsDeclaration();
    antlr4::tree::TerminalNode *Id();
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionPointerVarDeclarationContext* functionPointerVarDeclaration();

  class  FunctionDefinitionContext : public OrcRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *Id();
    ArgumentsDeclarationContext *argumentsDeclaration();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  GlobalFunctionDefinitionContext : public OrcRuleContext {
  public:
    GlobalFunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDefinitionContext *functionDefinition();
    antlr4::tree::TerminalNode *Static();
    ExternFunctionDeclarationContext *externFunctionDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlobalFunctionDefinitionContext* globalFunctionDefinition();

  class  GlobalVarDeclarationContext : public OrcRuleContext {
  public:
    GlobalVarDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarDeclarationContext *varDeclaration();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlobalVarDeclarationContext* globalVarDeclaration();

  class  ExternFunctionDeclarationContext : public OrcRuleContext {
  public:
    ExternFunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Extern();
    TypeContext *type();
    antlr4::tree::TerminalNode *Id();
    ArgumentsDeclarationContext *argumentsDeclaration();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExternFunctionDeclarationContext* externFunctionDeclaration();

  class  ImportStatementContext : public OrcRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Import();
    antlr4::tree::TerminalNode *From();
    antlr4::tree::TerminalNode *StringLiteral();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportStatementContext* importStatement();

  class  IncludeStatementContext : public OrcRuleContext {
  public:
    IncludeStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IncludePathCharactersContext *includePathCharacters();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IncludeStatementContext* includeStatement();

  class  IncludePathCharactersContext : public OrcRuleContext {
  public:
    IncludePathCharactersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IncludePathCharactersContext* includePathCharacters();

  class  PackageStatementContext : public OrcRuleContext {
  public:
    PackageStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Id();
    EosContext *eos();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PackageStatementContext* packageStatement();

  class  LiteralContext : public OrcRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NullLiteral();
    antlr4::tree::TerminalNode *BooleanLiteral();
    antlr4::tree::TerminalNode *DecimalLiteral();
    antlr4::tree::TerminalNode *HexIntegerLiteral();
    antlr4::tree::TerminalNode *OctalIntegerLiteral();
    antlr4::tree::TerminalNode *BinaryIntegerLiteral();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *CharLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  EosContext : public OrcRuleContext {
  public:
    EosContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EosContext* eos();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool singleExpressionSempred(SingleExpressionContext *_localctx, size_t predicateIndex);
  bool eosSempred(EosContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace antlrcpptest
