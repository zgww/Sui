
    #include "OrcParserBase.h"


// Generated from Orc.g4 by ANTLR 4.13.2


#include "OrcListener.h"
#include "OrcVisitor.h"

#include "OrcParser.h"


using namespace antlrcpp;
using namespace antlrcpptest;

using namespace antlr4;

namespace {

struct OrcParserStaticData final {
  OrcParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  OrcParserStaticData(const OrcParserStaticData&) = delete;
  OrcParserStaticData(OrcParserStaticData&&) = delete;
  OrcParserStaticData& operator=(const OrcParserStaticData&) = delete;
  OrcParserStaticData& operator=(OrcParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag orcParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<OrcParserStaticData> orcParserStaticData = nullptr;

void orcParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (orcParserStaticData != nullptr) {
    return;
  }
#else
  assert(orcParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<OrcParserStaticData>(
    std::vector<std::string>{
      "program", "rootDeclaration", "arguments", "expressionSequence", "closureExpression", 
      "singleExpression", "assignmentOperator", "emptyStatement", "structDefinition", 
      "structMember", "arraySizeDeclaration", "varDeclaration", "statement", 
      "continueStatement", "breakStatement", "returnStatement", "scopeStatement", 
      "iterationStatement", "forCondition", "selectionStatement", "block", 
      "type", "closureType", "functionTypeArg", "attribute", "functionType", 
      "typeQualifier", "pointer", "ref", "primitiveType", "enumDefinition", 
      "enumItem", "extensionDefinition", "extensionBlock", "classDefinition", 
      "classDefinitionBlock", "classFieldDeclaration", "methodDeclaration", 
      "assignRightPart", "argumentDeclaration", "argumentsDeclaration", 
      "functionPointerVarDeclaration", "functionDefinition", "globalFunctionDefinition", 
      "globalVarDeclaration", "externFunctionDeclaration", "importStatement", 
      "includeStatement", "includePathCharacters", "packageStatement", "literal", 
      "eos"
    },
    std::vector<std::string>{
      "", "'('", "','", "')'", "'^'", "'++'", "'--'", "'['", "']'", "'.'", 
      "'->'", "'#'", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", 
      "'\\u003F\\u003F'", "'<<'", "'>>'", "'>>>'", "'<'", "'>'", "'<='", 
      "'>='", "'=='", "'!='", "'==='", "'!=='", "'|'", "'&&'", "'||'", "'\\u003F'", 
      "':'", "'='", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", 
      "'>>>='", "'&='", "'^='", "'|='", "'**='", "'\\u003F\\u003F='", "';'", 
      "'{'", "'else if'", "'__attribute__'", "'restrict'", "'volatile'", 
      "'_Atomic'", "'@'", "'int'", "'short'", "'float'", "'double'", "'char'", 
      "'bool'", "'long'", "'unsigned'", "'import type'", "'#include'", "'package'", 
      "'break'", "'do'", "'instanceof'", "'case'", "'else'", "'new'", "'return'", 
      "'void'", "'continue'", "'for'", "'while'", "'self'", "'if'", "'from'", 
      "'struct'", "'class'", "'enum'", "'extends'", "'extern'", "'super'", 
      "'extension'", "'const'", "'export'", "'import'", "'static'", "'async'", 
      "'await'", "'refc'", "", "", "", "", "", "", "", "", "", "'}'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "Break", "Do", "Instanceof", "Case", "Else", "New", "Return", 
      "Void", "Continue", "For", "While", "This", "If", "From", "Struct", 
      "Class", "Enum", "Extends", "Extern", "Super", "Extension", "Const", 
      "Export", "Import", "Static", "Async", "Await", "Refc", "NullLiteral", 
      "BooleanLiteral", "DecimalLiteral", "HexIntegerLiteral", "OctalIntegerLiteral", 
      "BinaryIntegerLiteral", "StringLiteral", "CharLiteral", "Id", "CloseBrace", 
      "LineTerminator", "Whitespace", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,111,691,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,1,0,5,0,106,8,0,10,0,12,0,109,9,0,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,121,8,1,1,2,1,2,1,2,1,2,5,2,127,8,2,10,
  	2,12,2,130,9,2,1,2,3,2,133,8,2,3,2,135,8,2,1,2,1,2,1,3,1,3,1,3,5,3,142,
  	8,3,10,3,12,3,145,9,3,1,4,1,4,1,4,3,4,150,8,4,1,4,1,4,1,4,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,189,8,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,254,8,5,1,5,5,5,257,8,5,10,
  	5,12,5,260,9,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,5,8,270,8,8,10,8,12,8,
  	273,9,8,1,8,1,8,1,9,1,9,1,9,3,9,280,8,9,1,9,1,9,1,9,1,9,1,9,3,9,287,8,
  	9,1,10,1,10,1,10,1,10,1,11,3,11,294,8,11,1,11,1,11,1,11,3,11,299,8,11,
  	1,11,1,11,3,11,303,8,11,1,11,3,11,306,8,11,1,11,3,11,309,8,11,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,
  	12,1,12,3,12,328,8,12,1,13,1,13,1,13,1,14,1,14,1,14,1,15,1,15,3,15,338,
  	8,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,360,8,17,1,18,1,18,3,18,364,8,
  	18,3,18,366,8,18,1,18,1,18,3,18,370,8,18,1,18,1,18,3,18,374,8,18,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,5,19,383,8,19,10,19,12,19,386,9,19,1,19,
  	1,19,3,19,390,8,19,1,20,1,20,5,20,394,8,20,10,20,12,20,397,9,20,1,20,
  	1,20,1,21,3,21,402,8,21,1,21,1,21,3,21,406,8,21,1,21,1,21,1,21,1,21,3,
  	21,412,8,21,1,21,3,21,415,8,21,1,21,3,21,418,8,21,1,22,1,22,1,22,1,22,
  	1,23,1,23,3,23,426,8,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,
  	1,25,5,25,438,8,25,10,25,12,25,441,9,25,1,26,1,26,1,27,3,27,446,8,27,
  	1,27,1,27,3,27,450,8,27,1,27,3,27,453,8,27,1,27,5,27,456,8,27,10,27,12,
  	27,459,9,27,1,27,1,27,5,27,463,8,27,10,27,12,27,466,9,27,4,27,468,8,27,
  	11,27,12,27,469,1,28,3,28,473,8,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,3,29,501,8,29,1,30,1,30,1,30,1,30,1,30,1,30,
  	5,30,509,8,30,10,30,12,30,512,9,30,1,30,3,30,515,8,30,1,30,1,30,1,30,
  	1,31,1,31,1,31,3,31,523,8,31,1,32,1,32,1,32,1,32,1,33,1,33,5,33,531,8,
  	33,10,33,12,33,534,9,33,1,33,1,33,1,34,1,34,3,34,540,8,34,1,34,1,34,1,
  	34,3,34,545,8,34,1,34,1,34,1,34,1,35,1,35,1,35,5,35,553,8,35,10,35,12,
  	35,556,9,35,1,35,1,35,1,36,1,36,1,36,3,36,563,8,36,1,36,3,36,566,8,36,
  	1,36,1,36,1,36,1,36,3,36,572,8,36,1,36,1,36,3,36,576,8,36,1,37,1,37,3,
  	37,580,8,37,1,38,1,38,1,38,1,39,1,39,3,39,587,8,39,1,39,3,39,590,8,39,
  	1,40,1,40,1,40,1,40,5,40,596,8,40,10,40,12,40,599,9,40,3,40,601,8,40,
  	1,40,3,40,604,8,40,1,40,1,40,3,40,608,8,40,1,41,1,41,1,41,4,41,613,8,
  	41,11,41,12,41,614,1,41,3,41,618,8,41,1,41,1,41,1,41,5,41,623,8,41,10,
  	41,12,41,626,9,41,1,42,1,42,1,42,1,42,1,42,1,43,3,43,634,8,43,1,43,1,
  	43,3,43,638,8,43,1,43,3,43,641,8,43,1,44,1,44,1,44,1,45,1,45,1,45,1,45,
  	1,45,1,45,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,1,46,3,46,662,
  	8,46,1,47,1,47,1,47,1,47,1,48,1,48,5,48,670,8,48,10,48,12,48,673,9,48,
  	1,48,1,48,3,48,677,8,48,1,49,1,49,1,49,1,49,1,50,1,50,1,51,1,51,1,51,
  	1,51,3,51,689,8,51,1,51,0,1,10,52,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,
  	74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,0,11,2,0,13,13,18,19,1,
  	0,14,15,1,0,21,23,1,0,24,27,1,0,28,31,1,0,9,10,1,0,38,50,2,0,9,9,16,16,
  	2,0,55,57,91,91,1,0,25,25,1,0,98,105,779,0,107,1,0,0,0,2,120,1,0,0,0,
  	4,122,1,0,0,0,6,138,1,0,0,0,8,146,1,0,0,0,10,188,1,0,0,0,12,261,1,0,0,
  	0,14,263,1,0,0,0,16,265,1,0,0,0,18,286,1,0,0,0,20,288,1,0,0,0,22,308,
  	1,0,0,0,24,327,1,0,0,0,26,329,1,0,0,0,28,332,1,0,0,0,30,335,1,0,0,0,32,
  	341,1,0,0,0,34,359,1,0,0,0,36,365,1,0,0,0,38,375,1,0,0,0,40,391,1,0,0,
  	0,42,417,1,0,0,0,44,419,1,0,0,0,46,423,1,0,0,0,48,427,1,0,0,0,50,434,
  	1,0,0,0,52,442,1,0,0,0,54,445,1,0,0,0,56,472,1,0,0,0,58,500,1,0,0,0,60,
  	502,1,0,0,0,62,519,1,0,0,0,64,524,1,0,0,0,66,528,1,0,0,0,68,537,1,0,0,
  	0,70,549,1,0,0,0,72,575,1,0,0,0,74,579,1,0,0,0,76,581,1,0,0,0,78,589,
  	1,0,0,0,80,607,1,0,0,0,82,609,1,0,0,0,84,627,1,0,0,0,86,640,1,0,0,0,88,
  	642,1,0,0,0,90,645,1,0,0,0,92,661,1,0,0,0,94,663,1,0,0,0,96,676,1,0,0,
  	0,98,678,1,0,0,0,100,682,1,0,0,0,102,688,1,0,0,0,104,106,3,2,1,0,105,
  	104,1,0,0,0,106,109,1,0,0,0,107,105,1,0,0,0,107,108,1,0,0,0,108,1,1,0,
  	0,0,109,107,1,0,0,0,110,121,3,98,49,0,111,121,3,94,47,0,112,121,3,92,
  	46,0,113,121,3,16,8,0,114,121,3,60,30,0,115,121,3,68,34,0,116,121,3,64,
  	32,0,117,121,3,88,44,0,118,121,3,86,43,0,119,121,3,14,7,0,120,110,1,0,
  	0,0,120,111,1,0,0,0,120,112,1,0,0,0,120,113,1,0,0,0,120,114,1,0,0,0,120,
  	115,1,0,0,0,120,116,1,0,0,0,120,117,1,0,0,0,120,118,1,0,0,0,120,119,1,
  	0,0,0,121,3,1,0,0,0,122,134,5,1,0,0,123,128,3,10,5,0,124,125,5,2,0,0,
  	125,127,3,10,5,0,126,124,1,0,0,0,127,130,1,0,0,0,128,126,1,0,0,0,128,
  	129,1,0,0,0,129,132,1,0,0,0,130,128,1,0,0,0,131,133,5,2,0,0,132,131,1,
  	0,0,0,132,133,1,0,0,0,133,135,1,0,0,0,134,123,1,0,0,0,134,135,1,0,0,0,
  	135,136,1,0,0,0,136,137,5,3,0,0,137,5,1,0,0,0,138,143,3,10,5,0,139,140,
  	5,2,0,0,140,142,3,10,5,0,141,139,1,0,0,0,142,145,1,0,0,0,143,141,1,0,
  	0,0,143,144,1,0,0,0,144,7,1,0,0,0,145,143,1,0,0,0,146,147,5,4,0,0,147,
  	149,3,42,21,0,148,150,5,106,0,0,149,148,1,0,0,0,149,150,1,0,0,0,150,151,
  	1,0,0,0,151,152,3,80,40,0,152,153,3,40,20,0,153,9,1,0,0,0,154,155,6,5,
  	-1,0,155,189,3,8,4,0,156,157,5,75,0,0,157,158,5,106,0,0,158,189,3,4,2,
  	0,159,160,5,12,0,0,160,189,3,10,5,29,161,162,5,13,0,0,162,189,3,10,5,
  	28,163,164,5,5,0,0,164,189,3,10,5,27,165,166,5,6,0,0,166,189,3,10,5,26,
  	167,168,5,14,0,0,168,189,3,10,5,25,169,170,5,15,0,0,170,189,3,10,5,24,
  	171,172,5,16,0,0,172,189,3,10,5,23,173,174,5,17,0,0,174,189,3,10,5,22,
  	175,176,5,1,0,0,176,177,3,42,21,0,177,178,5,3,0,0,178,179,3,10,5,8,179,
  	189,1,0,0,0,180,189,5,81,0,0,181,189,5,106,0,0,182,189,5,89,0,0,183,189,
  	3,100,50,0,184,185,5,1,0,0,185,186,3,6,3,0,186,187,5,3,0,0,187,189,1,
  	0,0,0,188,154,1,0,0,0,188,156,1,0,0,0,188,159,1,0,0,0,188,161,1,0,0,0,
  	188,163,1,0,0,0,188,165,1,0,0,0,188,167,1,0,0,0,188,169,1,0,0,0,188,171,
  	1,0,0,0,188,173,1,0,0,0,188,175,1,0,0,0,188,180,1,0,0,0,188,181,1,0,0,
  	0,188,182,1,0,0,0,188,183,1,0,0,0,188,184,1,0,0,0,189,258,1,0,0,0,190,
  	191,10,21,0,0,191,192,7,0,0,0,192,257,3,10,5,22,193,194,10,20,0,0,194,
  	195,7,1,0,0,195,257,3,10,5,21,196,197,10,19,0,0,197,198,5,20,0,0,198,
  	257,3,10,5,20,199,200,10,18,0,0,200,201,7,2,0,0,201,257,3,10,5,19,202,
  	203,10,17,0,0,203,204,7,3,0,0,204,257,3,10,5,18,205,206,10,16,0,0,206,
  	207,5,72,0,0,207,257,3,10,5,17,208,209,10,15,0,0,209,210,7,4,0,0,210,
  	257,3,10,5,16,211,212,10,14,0,0,212,213,5,12,0,0,213,257,3,10,5,15,214,
  	215,10,13,0,0,215,216,5,4,0,0,216,257,3,10,5,14,217,218,10,12,0,0,218,
  	219,5,32,0,0,219,257,3,10,5,13,220,221,10,11,0,0,221,222,5,33,0,0,222,
  	257,3,10,5,12,223,224,10,10,0,0,224,225,5,34,0,0,225,257,3,10,5,11,226,
  	227,10,9,0,0,227,228,5,35,0,0,228,229,3,10,5,0,229,230,5,36,0,0,230,231,
  	3,10,5,10,231,257,1,0,0,0,232,233,10,7,0,0,233,234,5,37,0,0,234,257,3,
  	10,5,7,235,236,10,6,0,0,236,237,3,12,6,0,237,238,3,10,5,6,238,257,1,0,
  	0,0,239,240,10,36,0,0,240,257,3,4,2,0,241,242,10,35,0,0,242,257,5,5,0,
  	0,243,244,10,34,0,0,244,257,5,6,0,0,245,246,10,32,0,0,246,247,5,7,0,0,
  	247,248,3,10,5,0,248,249,5,8,0,0,249,257,1,0,0,0,250,251,10,31,0,0,251,
  	253,7,5,0,0,252,254,5,11,0,0,253,252,1,0,0,0,253,254,1,0,0,0,254,255,
  	1,0,0,0,255,257,5,106,0,0,256,190,1,0,0,0,256,193,1,0,0,0,256,196,1,0,
  	0,0,256,199,1,0,0,0,256,202,1,0,0,0,256,205,1,0,0,0,256,208,1,0,0,0,256,
  	211,1,0,0,0,256,214,1,0,0,0,256,217,1,0,0,0,256,220,1,0,0,0,256,223,1,
  	0,0,0,256,226,1,0,0,0,256,232,1,0,0,0,256,235,1,0,0,0,256,239,1,0,0,0,
  	256,241,1,0,0,0,256,243,1,0,0,0,256,245,1,0,0,0,256,250,1,0,0,0,257,260,
  	1,0,0,0,258,256,1,0,0,0,258,259,1,0,0,0,259,11,1,0,0,0,260,258,1,0,0,
  	0,261,262,7,6,0,0,262,13,1,0,0,0,263,264,5,51,0,0,264,15,1,0,0,0,265,
  	266,5,84,0,0,266,267,5,106,0,0,267,271,5,52,0,0,268,270,3,18,9,0,269,
  	268,1,0,0,0,270,273,1,0,0,0,271,269,1,0,0,0,271,272,1,0,0,0,272,274,1,
  	0,0,0,273,271,1,0,0,0,274,275,5,107,0,0,275,17,1,0,0,0,276,277,3,42,21,
  	0,277,279,5,106,0,0,278,280,3,20,10,0,279,278,1,0,0,0,279,280,1,0,0,0,
  	280,281,1,0,0,0,281,282,3,102,51,0,282,287,1,0,0,0,283,284,3,82,41,0,
  	284,285,3,102,51,0,285,287,1,0,0,0,286,276,1,0,0,0,286,283,1,0,0,0,287,
  	19,1,0,0,0,288,289,5,7,0,0,289,290,5,100,0,0,290,291,5,8,0,0,291,21,1,
  	0,0,0,292,294,5,94,0,0,293,292,1,0,0,0,293,294,1,0,0,0,294,295,1,0,0,
  	0,295,296,3,42,21,0,296,298,5,106,0,0,297,299,3,20,10,0,298,297,1,0,0,
  	0,298,299,1,0,0,0,299,302,1,0,0,0,300,301,5,37,0,0,301,303,3,10,5,0,302,
  	300,1,0,0,0,302,303,1,0,0,0,303,309,1,0,0,0,304,306,5,94,0,0,305,304,
  	1,0,0,0,305,306,1,0,0,0,306,307,1,0,0,0,307,309,3,82,41,0,308,293,1,0,
  	0,0,308,305,1,0,0,0,309,23,1,0,0,0,310,311,3,8,4,0,311,312,3,102,51,0,
  	312,328,1,0,0,0,313,314,3,22,11,0,314,315,3,102,51,0,315,328,1,0,0,0,
  	316,328,3,32,16,0,317,328,3,40,20,0,318,328,3,26,13,0,319,328,3,28,14,
  	0,320,328,3,38,19,0,321,328,3,30,15,0,322,328,3,34,17,0,323,324,3,10,
  	5,0,324,325,3,102,51,0,325,328,1,0,0,0,326,328,3,14,7,0,327,310,1,0,0,
  	0,327,313,1,0,0,0,327,316,1,0,0,0,327,317,1,0,0,0,327,318,1,0,0,0,327,
  	319,1,0,0,0,327,320,1,0,0,0,327,321,1,0,0,0,327,322,1,0,0,0,327,323,1,
  	0,0,0,327,326,1,0,0,0,328,25,1,0,0,0,329,330,5,78,0,0,330,331,3,102,51,
  	0,331,27,1,0,0,0,332,333,5,70,0,0,333,334,3,102,51,0,334,29,1,0,0,0,335,
  	337,5,76,0,0,336,338,3,10,5,0,337,336,1,0,0,0,337,338,1,0,0,0,338,339,
  	1,0,0,0,339,340,3,102,51,0,340,31,1,0,0,0,341,342,3,10,5,0,342,343,7,
  	7,0,0,343,344,3,40,20,0,344,33,1,0,0,0,345,346,5,80,0,0,346,347,3,10,
  	5,0,347,348,3,40,20,0,348,360,1,0,0,0,349,350,5,79,0,0,350,351,5,1,0,
  	0,351,352,3,36,18,0,352,353,5,3,0,0,353,354,3,40,20,0,354,360,1,0,0,0,
  	355,356,5,79,0,0,356,357,3,36,18,0,357,358,3,40,20,0,358,360,1,0,0,0,
  	359,345,1,0,0,0,359,349,1,0,0,0,359,355,1,0,0,0,360,35,1,0,0,0,361,366,
  	3,22,11,0,362,364,3,10,5,0,363,362,1,0,0,0,363,364,1,0,0,0,364,366,1,
  	0,0,0,365,361,1,0,0,0,365,363,1,0,0,0,366,367,1,0,0,0,367,369,5,51,0,
  	0,368,370,3,10,5,0,369,368,1,0,0,0,369,370,1,0,0,0,370,371,1,0,0,0,371,
  	373,5,51,0,0,372,374,3,10,5,0,373,372,1,0,0,0,373,374,1,0,0,0,374,37,
  	1,0,0,0,375,376,5,82,0,0,376,377,3,10,5,0,377,384,3,40,20,0,378,379,5,
  	53,0,0,379,380,3,10,5,0,380,381,3,40,20,0,381,383,1,0,0,0,382,378,1,0,
  	0,0,383,386,1,0,0,0,384,382,1,0,0,0,384,385,1,0,0,0,385,389,1,0,0,0,386,
  	384,1,0,0,0,387,388,5,74,0,0,388,390,3,40,20,0,389,387,1,0,0,0,389,390,
  	1,0,0,0,390,39,1,0,0,0,391,395,5,52,0,0,392,394,3,24,12,0,393,392,1,0,
  	0,0,394,397,1,0,0,0,395,393,1,0,0,0,395,396,1,0,0,0,396,398,1,0,0,0,397,
  	395,1,0,0,0,398,399,5,107,0,0,399,41,1,0,0,0,400,402,3,52,26,0,401,400,
  	1,0,0,0,401,402,1,0,0,0,402,403,1,0,0,0,403,405,3,58,29,0,404,406,3,20,
  	10,0,405,404,1,0,0,0,405,406,1,0,0,0,406,418,1,0,0,0,407,418,3,44,22,
  	0,408,418,3,54,27,0,409,418,3,56,28,0,410,412,3,52,26,0,411,410,1,0,0,
  	0,411,412,1,0,0,0,412,414,1,0,0,0,413,415,5,84,0,0,414,413,1,0,0,0,414,
  	415,1,0,0,0,415,416,1,0,0,0,416,418,5,106,0,0,417,401,1,0,0,0,417,407,
  	1,0,0,0,417,408,1,0,0,0,417,409,1,0,0,0,417,411,1,0,0,0,418,43,1,0,0,
  	0,419,420,5,4,0,0,420,421,3,42,21,0,421,422,3,80,40,0,422,45,1,0,0,0,
  	423,425,3,42,21,0,424,426,5,106,0,0,425,424,1,0,0,0,425,426,1,0,0,0,426,
  	47,1,0,0,0,427,428,5,54,0,0,428,429,5,1,0,0,429,430,5,1,0,0,430,431,5,
  	106,0,0,431,432,5,3,0,0,432,433,5,3,0,0,433,49,1,0,0,0,434,435,3,42,21,
  	0,435,439,3,80,40,0,436,438,3,48,24,0,437,436,1,0,0,0,438,441,1,0,0,0,
  	439,437,1,0,0,0,439,440,1,0,0,0,440,51,1,0,0,0,441,439,1,0,0,0,442,443,
  	7,8,0,0,443,53,1,0,0,0,444,446,3,52,26,0,445,444,1,0,0,0,445,446,1,0,
  	0,0,446,452,1,0,0,0,447,453,3,58,29,0,448,450,5,84,0,0,449,448,1,0,0,
  	0,449,450,1,0,0,0,450,451,1,0,0,0,451,453,5,106,0,0,452,447,1,0,0,0,452,
  	449,1,0,0,0,453,467,1,0,0,0,454,456,3,52,26,0,455,454,1,0,0,0,456,459,
  	1,0,0,0,457,455,1,0,0,0,457,458,1,0,0,0,458,460,1,0,0,0,459,457,1,0,0,
  	0,460,464,5,13,0,0,461,463,3,52,26,0,462,461,1,0,0,0,463,466,1,0,0,0,
  	464,462,1,0,0,0,464,465,1,0,0,0,465,468,1,0,0,0,466,464,1,0,0,0,467,457,
  	1,0,0,0,468,469,1,0,0,0,469,467,1,0,0,0,469,470,1,0,0,0,470,55,1,0,0,
  	0,471,473,5,84,0,0,472,471,1,0,0,0,472,473,1,0,0,0,473,474,1,0,0,0,474,
  	475,5,106,0,0,475,476,5,58,0,0,476,57,1,0,0,0,477,501,5,59,0,0,478,501,
  	5,60,0,0,479,501,5,61,0,0,480,501,5,62,0,0,481,501,5,63,0,0,482,501,5,
  	64,0,0,483,501,5,77,0,0,484,501,5,65,0,0,485,486,5,65,0,0,486,501,5,65,
  	0,0,487,488,5,65,0,0,488,501,5,62,0,0,489,490,5,66,0,0,490,501,5,63,0,
  	0,491,492,5,66,0,0,492,501,5,59,0,0,493,494,5,66,0,0,494,501,5,60,0,0,
  	495,496,5,66,0,0,496,501,5,65,0,0,497,498,5,66,0,0,498,499,5,65,0,0,499,
  	501,5,65,0,0,500,477,1,0,0,0,500,478,1,0,0,0,500,479,1,0,0,0,500,480,
  	1,0,0,0,500,481,1,0,0,0,500,482,1,0,0,0,500,483,1,0,0,0,500,484,1,0,0,
  	0,500,485,1,0,0,0,500,487,1,0,0,0,500,489,1,0,0,0,500,491,1,0,0,0,500,
  	493,1,0,0,0,500,495,1,0,0,0,500,497,1,0,0,0,501,59,1,0,0,0,502,503,5,
  	86,0,0,503,504,5,106,0,0,504,505,5,52,0,0,505,510,3,62,31,0,506,507,5,
  	2,0,0,507,509,3,62,31,0,508,506,1,0,0,0,509,512,1,0,0,0,510,508,1,0,0,
  	0,510,511,1,0,0,0,511,514,1,0,0,0,512,510,1,0,0,0,513,515,5,2,0,0,514,
  	513,1,0,0,0,514,515,1,0,0,0,515,516,1,0,0,0,516,517,5,107,0,0,517,518,
  	3,102,51,0,518,61,1,0,0,0,519,522,5,106,0,0,520,521,5,37,0,0,521,523,
  	5,100,0,0,522,520,1,0,0,0,522,523,1,0,0,0,523,63,1,0,0,0,524,525,5,90,
  	0,0,525,526,5,106,0,0,526,527,3,66,33,0,527,65,1,0,0,0,528,532,5,52,0,
  	0,529,531,3,74,37,0,530,529,1,0,0,0,531,534,1,0,0,0,532,530,1,0,0,0,532,
  	533,1,0,0,0,533,535,1,0,0,0,534,532,1,0,0,0,535,536,5,107,0,0,536,67,
  	1,0,0,0,537,539,5,85,0,0,538,540,5,97,0,0,539,538,1,0,0,0,539,540,1,0,
  	0,0,540,541,1,0,0,0,541,544,5,106,0,0,542,543,5,87,0,0,543,545,5,106,
  	0,0,544,542,1,0,0,0,544,545,1,0,0,0,545,546,1,0,0,0,546,547,3,70,35,0,
  	547,548,3,102,51,0,548,69,1,0,0,0,549,554,5,52,0,0,550,553,3,72,36,0,
  	551,553,3,74,37,0,552,550,1,0,0,0,552,551,1,0,0,0,553,556,1,0,0,0,554,
  	552,1,0,0,0,554,555,1,0,0,0,555,557,1,0,0,0,556,554,1,0,0,0,557,558,5,
  	107,0,0,558,71,1,0,0,0,559,560,3,42,21,0,560,562,5,106,0,0,561,563,3,
  	20,10,0,562,561,1,0,0,0,562,563,1,0,0,0,563,565,1,0,0,0,564,566,3,76,
  	38,0,565,564,1,0,0,0,565,566,1,0,0,0,566,567,1,0,0,0,567,568,3,102,51,
  	0,568,576,1,0,0,0,569,571,3,82,41,0,570,572,3,76,38,0,571,570,1,0,0,0,
  	571,572,1,0,0,0,572,573,1,0,0,0,573,574,3,102,51,0,574,576,1,0,0,0,575,
  	559,1,0,0,0,575,569,1,0,0,0,576,73,1,0,0,0,577,580,3,84,42,0,578,580,
  	3,90,45,0,579,577,1,0,0,0,579,578,1,0,0,0,580,75,1,0,0,0,581,582,5,37,
  	0,0,582,583,3,10,5,0,583,77,1,0,0,0,584,586,3,42,21,0,585,587,5,106,0,
  	0,586,585,1,0,0,0,586,587,1,0,0,0,587,590,1,0,0,0,588,590,3,82,41,0,589,
  	584,1,0,0,0,589,588,1,0,0,0,590,79,1,0,0,0,591,600,5,1,0,0,592,597,3,
  	78,39,0,593,594,5,2,0,0,594,596,3,78,39,0,595,593,1,0,0,0,596,599,1,0,
  	0,0,597,595,1,0,0,0,597,598,1,0,0,0,598,601,1,0,0,0,599,597,1,0,0,0,600,
  	592,1,0,0,0,600,601,1,0,0,0,601,603,1,0,0,0,602,604,5,2,0,0,603,602,1,
  	0,0,0,603,604,1,0,0,0,604,605,1,0,0,0,605,608,5,3,0,0,606,608,1,0,0,0,
  	607,591,1,0,0,0,607,606,1,0,0,0,608,81,1,0,0,0,609,610,3,42,21,0,610,
  	612,5,1,0,0,611,613,5,13,0,0,612,611,1,0,0,0,613,614,1,0,0,0,614,612,
  	1,0,0,0,614,615,1,0,0,0,615,617,1,0,0,0,616,618,5,106,0,0,617,616,1,0,
  	0,0,617,618,1,0,0,0,618,619,1,0,0,0,619,620,5,3,0,0,620,624,3,80,40,0,
  	621,623,3,48,24,0,622,621,1,0,0,0,623,626,1,0,0,0,624,622,1,0,0,0,624,
  	625,1,0,0,0,625,83,1,0,0,0,626,624,1,0,0,0,627,628,3,42,21,0,628,629,
  	5,106,0,0,629,630,3,80,40,0,630,631,3,40,20,0,631,85,1,0,0,0,632,634,
  	5,94,0,0,633,632,1,0,0,0,633,634,1,0,0,0,634,635,1,0,0,0,635,641,3,84,
  	42,0,636,638,5,94,0,0,637,636,1,0,0,0,637,638,1,0,0,0,638,639,1,0,0,0,
  	639,641,3,90,45,0,640,633,1,0,0,0,640,637,1,0,0,0,641,87,1,0,0,0,642,
  	643,3,22,11,0,643,644,3,102,51,0,644,89,1,0,0,0,645,646,5,88,0,0,646,
  	647,3,42,21,0,647,648,5,106,0,0,648,649,3,80,40,0,649,650,3,102,51,0,
  	650,91,1,0,0,0,651,652,5,93,0,0,652,653,5,13,0,0,653,654,5,83,0,0,654,
  	655,5,104,0,0,655,662,3,102,51,0,656,657,5,67,0,0,657,658,5,13,0,0,658,
  	659,5,83,0,0,659,660,5,104,0,0,660,662,3,102,51,0,661,651,1,0,0,0,661,
  	656,1,0,0,0,662,93,1,0,0,0,663,664,5,68,0,0,664,665,3,96,48,0,665,666,
  	3,102,51,0,666,95,1,0,0,0,667,671,5,24,0,0,668,670,8,9,0,0,669,668,1,
  	0,0,0,670,673,1,0,0,0,671,669,1,0,0,0,671,672,1,0,0,0,672,674,1,0,0,0,
  	673,671,1,0,0,0,674,677,5,25,0,0,675,677,5,104,0,0,676,667,1,0,0,0,676,
  	675,1,0,0,0,677,97,1,0,0,0,678,679,5,69,0,0,679,680,5,106,0,0,680,681,
  	3,102,51,0,681,99,1,0,0,0,682,683,7,10,0,0,683,101,1,0,0,0,684,689,5,
  	51,0,0,685,689,5,0,0,1,686,689,4,51,20,0,687,689,4,51,21,0,688,684,1,
  	0,0,0,688,685,1,0,0,0,688,686,1,0,0,0,688,687,1,0,0,0,689,103,1,0,0,0,
  	73,107,120,128,132,134,143,149,188,253,256,258,271,279,286,293,298,302,
  	305,308,327,337,359,363,365,369,373,384,389,395,401,405,411,414,417,425,
  	439,445,449,452,457,464,469,472,500,510,514,522,532,539,544,552,554,562,
  	565,571,575,579,586,589,597,600,603,607,614,617,624,633,637,640,661,671,
  	676,688
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  orcParserStaticData = std::move(staticData);
}

}

OrcParser::OrcParser(TokenStream *input) : OrcParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

OrcParser::OrcParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : OrcParserBase(input) {
  OrcParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *orcParserStaticData->atn, orcParserStaticData->decisionToDFA, orcParserStaticData->sharedContextCache, options);
}

OrcParser::~OrcParser() {
  delete _interpreter;
}

const atn::ATN& OrcParser::getATN() const {
  return *orcParserStaticData->atn;
}

std::string OrcParser::getGrammarFileName() const {
  return "Orc.g4";
}

const std::vector<std::string>& OrcParser::getRuleNames() const {
  return orcParserStaticData->ruleNames;
}

const dfa::Vocabulary& OrcParser::getVocabulary() const {
  return orcParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView OrcParser::getSerializedATN() const {
  return orcParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

OrcParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

std::vector<OrcParser::RootDeclarationContext *> OrcParser::ProgramContext::rootDeclaration() {
  return getRuleContexts<OrcParser::RootDeclarationContext>();
}

OrcParser::RootDeclarationContext* OrcParser::ProgramContext::rootDeclaration(size_t i) {
  return getRuleContext<OrcParser::RootDeclarationContext>(i);
}


size_t OrcParser::ProgramContext::getRuleIndex() const {
  return OrcParser::RuleProgram;
}

void OrcParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void OrcParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any OrcParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ProgramContext* OrcParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, OrcParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -322007373356990448) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 4399882575935) != 0)) {
      setState(104);
      rootDeclaration();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RootDeclarationContext ------------------------------------------------------------------

OrcParser::RootDeclarationContext::RootDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::PackageStatementContext* OrcParser::RootDeclarationContext::packageStatement() {
  return getRuleContext<OrcParser::PackageStatementContext>(0);
}

OrcParser::IncludeStatementContext* OrcParser::RootDeclarationContext::includeStatement() {
  return getRuleContext<OrcParser::IncludeStatementContext>(0);
}

OrcParser::ImportStatementContext* OrcParser::RootDeclarationContext::importStatement() {
  return getRuleContext<OrcParser::ImportStatementContext>(0);
}

OrcParser::StructDefinitionContext* OrcParser::RootDeclarationContext::structDefinition() {
  return getRuleContext<OrcParser::StructDefinitionContext>(0);
}

OrcParser::EnumDefinitionContext* OrcParser::RootDeclarationContext::enumDefinition() {
  return getRuleContext<OrcParser::EnumDefinitionContext>(0);
}

OrcParser::ClassDefinitionContext* OrcParser::RootDeclarationContext::classDefinition() {
  return getRuleContext<OrcParser::ClassDefinitionContext>(0);
}

OrcParser::ExtensionDefinitionContext* OrcParser::RootDeclarationContext::extensionDefinition() {
  return getRuleContext<OrcParser::ExtensionDefinitionContext>(0);
}

OrcParser::GlobalVarDeclarationContext* OrcParser::RootDeclarationContext::globalVarDeclaration() {
  return getRuleContext<OrcParser::GlobalVarDeclarationContext>(0);
}

OrcParser::GlobalFunctionDefinitionContext* OrcParser::RootDeclarationContext::globalFunctionDefinition() {
  return getRuleContext<OrcParser::GlobalFunctionDefinitionContext>(0);
}

OrcParser::EmptyStatementContext* OrcParser::RootDeclarationContext::emptyStatement() {
  return getRuleContext<OrcParser::EmptyStatementContext>(0);
}


size_t OrcParser::RootDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleRootDeclaration;
}

void OrcParser::RootDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRootDeclaration(this);
}

void OrcParser::RootDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRootDeclaration(this);
}


std::any OrcParser::RootDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitRootDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::RootDeclarationContext* OrcParser::rootDeclaration() {
  RootDeclarationContext *_localctx = _tracker.createInstance<RootDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, OrcParser::RuleRootDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(120);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(110);
      packageStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(111);
      includeStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(112);
      importStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(113);
      structDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(114);
      enumDefinition();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(115);
      classDefinition();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(116);
      extensionDefinition();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(117);
      globalVarDeclaration();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(118);
      globalFunctionDefinition();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(119);
      emptyStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

OrcParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

std::vector<OrcParser::SingleExpressionContext *> OrcParser::ArgumentsContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::ArgumentsContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}


size_t OrcParser::ArgumentsContext::getRuleIndex() const {
  return OrcParser::RuleArguments;
}

void OrcParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void OrcParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


std::any OrcParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ArgumentsContext* OrcParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 4, OrcParser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(OrcParser::T__0);
    setState(134);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 4286595137) != 0)) {
      setState(123);
      singleExpression(0);
      setState(128);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(124);
          match(OrcParser::T__1);
          setState(125);
          singleExpression(0); 
        }
        setState(130);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      }
      setState(132);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__1) {
        setState(131);
        match(OrcParser::T__1);
      }
    }
    setState(136);
    match(OrcParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionSequenceContext ------------------------------------------------------------------

OrcParser::ExpressionSequenceContext::ExpressionSequenceContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

std::vector<OrcParser::SingleExpressionContext *> OrcParser::ExpressionSequenceContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::ExpressionSequenceContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}


size_t OrcParser::ExpressionSequenceContext::getRuleIndex() const {
  return OrcParser::RuleExpressionSequence;
}

void OrcParser::ExpressionSequenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionSequence(this);
}

void OrcParser::ExpressionSequenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionSequence(this);
}


std::any OrcParser::ExpressionSequenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitExpressionSequence(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ExpressionSequenceContext* OrcParser::expressionSequence() {
  ExpressionSequenceContext *_localctx = _tracker.createInstance<ExpressionSequenceContext>(_ctx, getState());
  enterRule(_localctx, 6, OrcParser::RuleExpressionSequence);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    singleExpression(0);
    setState(143);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__1) {
      setState(139);
      match(OrcParser::T__1);
      setState(140);
      singleExpression(0);
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClosureExpressionContext ------------------------------------------------------------------

OrcParser::ClosureExpressionContext::ClosureExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::ClosureExpressionContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::ClosureExpressionContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}

OrcParser::BlockContext* OrcParser::ClosureExpressionContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}

tree::TerminalNode* OrcParser::ClosureExpressionContext::Id() {
  return getToken(OrcParser::Id, 0);
}


size_t OrcParser::ClosureExpressionContext::getRuleIndex() const {
  return OrcParser::RuleClosureExpression;
}

void OrcParser::ClosureExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClosureExpression(this);
}

void OrcParser::ClosureExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClosureExpression(this);
}


std::any OrcParser::ClosureExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitClosureExpression(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ClosureExpressionContext* OrcParser::closureExpression() {
  ClosureExpressionContext *_localctx = _tracker.createInstance<ClosureExpressionContext>(_ctx, getState());
  enterRule(_localctx, 8, OrcParser::RuleClosureExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(OrcParser::T__3);
    setState(147);
    type();
    setState(149);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(148);
      match(OrcParser::Id);
    }
    setState(151);
    argumentsDeclaration();
    setState(152);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SingleExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext::SingleExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}


size_t OrcParser::SingleExpressionContext::getRuleIndex() const {
  return OrcParser::RuleSingleExpression;
}

void OrcParser::SingleExpressionContext::copyFrom(SingleExpressionContext *ctx) {
  OrcRuleContext::copyFrom(ctx);
}

//----------------- TernaryExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::TernaryExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::TernaryExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::TernaryExpressionContext::TernaryExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::TernaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTernaryExpression(this);
}
void OrcParser::TernaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTernaryExpression(this);
}

std::any OrcParser::TernaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitTernaryExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::LogicalAndExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::LogicalAndExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::LogicalAndExpressionContext::LogicalAndExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}
void OrcParser::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}

std::any OrcParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PreIncrementExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::PreIncrementExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::PreIncrementExpressionContext::PreIncrementExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::PreIncrementExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPreIncrementExpression(this);
}
void OrcParser::PreIncrementExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPreIncrementExpression(this);
}

std::any OrcParser::PreIncrementExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitPreIncrementExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GetAddressExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::GetAddressExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::GetAddressExpressionContext::GetAddressExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::GetAddressExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGetAddressExpression(this);
}
void OrcParser::GetAddressExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGetAddressExpression(this);
}

std::any OrcParser::GetAddressExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitGetAddressExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::LogicalOrExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::LogicalOrExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::LogicalOrExpressionContext::LogicalOrExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}
void OrcParser::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}

std::any OrcParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::NotExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::NotExpressionContext::NotExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::NotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotExpression(this);
}
void OrcParser::NotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotExpression(this);
}

std::any OrcParser::NotExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitNotExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PreDecreaseExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::PreDecreaseExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::PreDecreaseExpressionContext::PreDecreaseExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::PreDecreaseExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPreDecreaseExpression(this);
}
void OrcParser::PreDecreaseExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPreDecreaseExpression(this);
}

std::any OrcParser::PreDecreaseExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitPreDecreaseExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ThisExpressionContext ------------------------------------------------------------------

tree::TerminalNode* OrcParser::ThisExpressionContext::This() {
  return getToken(OrcParser::This, 0);
}

OrcParser::ThisExpressionContext::ThisExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::ThisExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThisExpression(this);
}
void OrcParser::ThisExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThisExpression(this);
}

std::any OrcParser::ThisExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitThisExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryMinusExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::UnaryMinusExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::UnaryMinusExpressionContext::UnaryMinusExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::UnaryMinusExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryMinusExpression(this);
}
void OrcParser::UnaryMinusExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryMinusExpression(this);
}

std::any OrcParser::UnaryMinusExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitUnaryMinusExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::AssignmentExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::AssignmentExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::AssignmentExpressionContext::AssignmentExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}
void OrcParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}

std::any OrcParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PostDecreaseExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::PostDecreaseExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::PostDecreaseExpressionContext::PostDecreaseExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::PostDecreaseExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostDecreaseExpression(this);
}
void OrcParser::PostDecreaseExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostDecreaseExpression(this);
}

std::any OrcParser::PostDecreaseExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitPostDecreaseExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InstanceofExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::InstanceofExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::InstanceofExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

tree::TerminalNode* OrcParser::InstanceofExpressionContext::Instanceof() {
  return getToken(OrcParser::Instanceof, 0);
}

OrcParser::InstanceofExpressionContext::InstanceofExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::InstanceofExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInstanceofExpression(this);
}
void OrcParser::InstanceofExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInstanceofExpression(this);
}

std::any OrcParser::InstanceofExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitInstanceofExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryPlusExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::UnaryPlusExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::UnaryPlusExpressionContext::UnaryPlusExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::UnaryPlusExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryPlusExpression(this);
}
void OrcParser::UnaryPlusExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryPlusExpression(this);
}

std::any OrcParser::UnaryPlusExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitUnaryPlusExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EqualityExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::EqualityExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::EqualityExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::EqualityExpressionContext::EqualityExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}
void OrcParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}

std::any OrcParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitXOrExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::BitXOrExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::BitXOrExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::BitXOrExpressionContext::BitXOrExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::BitXOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitXOrExpression(this);
}
void OrcParser::BitXOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitXOrExpression(this);
}

std::any OrcParser::BitXOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitBitXOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SuperExpressionContext ------------------------------------------------------------------

tree::TerminalNode* OrcParser::SuperExpressionContext::Super() {
  return getToken(OrcParser::Super, 0);
}

OrcParser::SuperExpressionContext::SuperExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::SuperExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSuperExpression(this);
}
void OrcParser::SuperExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSuperExpression(this);
}

std::any OrcParser::SuperExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitSuperExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::MultiplicativeExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::MultiplicativeExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}
void OrcParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}

std::any OrcParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::CallExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::ArgumentsContext* OrcParser::CallExpressionContext::arguments() {
  return getRuleContext<OrcParser::ArgumentsContext>(0);
}

OrcParser::CallExpressionContext::CallExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::CallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallExpression(this);
}
void OrcParser::CallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallExpression(this);
}

std::any OrcParser::CallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitCallExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitShiftExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::BitShiftExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::BitShiftExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::BitShiftExpressionContext::BitShiftExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::BitShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitShiftExpression(this);
}
void OrcParser::BitShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitShiftExpression(this);
}

std::any OrcParser::BitShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitBitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesizedExpressionContext ------------------------------------------------------------------

OrcParser::ExpressionSequenceContext* OrcParser::ParenthesizedExpressionContext::expressionSequence() {
  return getRuleContext<OrcParser::ExpressionSequenceContext>(0);
}

OrcParser::ParenthesizedExpressionContext::ParenthesizedExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::ParenthesizedExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesizedExpression(this);
}
void OrcParser::ParenthesizedExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesizedExpression(this);
}

std::any OrcParser::ParenthesizedExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitParenthesizedExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AdditiveExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::AdditiveExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::AdditiveExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::AdditiveExpressionContext::AdditiveExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}
void OrcParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}

std::any OrcParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelationalExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::RelationalExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::RelationalExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::RelationalExpressionContext::RelationalExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}
void OrcParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}

std::any OrcParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PostIncrementExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::PostIncrementExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::PostIncrementExpressionContext::PostIncrementExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::PostIncrementExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostIncrementExpression(this);
}
void OrcParser::PostIncrementExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostIncrementExpression(this);
}

std::any OrcParser::PostIncrementExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitPostIncrementExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitNotExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::BitNotExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::BitNotExpressionContext::BitNotExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::BitNotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitNotExpression(this);
}
void OrcParser::BitNotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitNotExpression(this);
}

std::any OrcParser::BitNotExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitBitNotExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NewExpressionContext ------------------------------------------------------------------

tree::TerminalNode* OrcParser::NewExpressionContext::New() {
  return getToken(OrcParser::New, 0);
}

tree::TerminalNode* OrcParser::NewExpressionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::ArgumentsContext* OrcParser::NewExpressionContext::arguments() {
  return getRuleContext<OrcParser::ArgumentsContext>(0);
}

OrcParser::NewExpressionContext::NewExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::NewExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewExpression(this);
}
void OrcParser::NewExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewExpression(this);
}

std::any OrcParser::NewExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitNewExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExpressionContext ------------------------------------------------------------------

OrcParser::LiteralContext* OrcParser::LiteralExpressionContext::literal() {
  return getRuleContext<OrcParser::LiteralContext>(0);
}

OrcParser::LiteralExpressionContext::LiteralExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::LiteralExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpression(this);
}
void OrcParser::LiteralExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpression(this);
}

std::any OrcParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberDotExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::MemberDotExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

tree::TerminalNode* OrcParser::MemberDotExpressionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::MemberDotExpressionContext::MemberDotExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::MemberDotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemberDotExpression(this);
}
void OrcParser::MemberDotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemberDotExpression(this);
}

std::any OrcParser::MemberDotExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitMemberDotExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberIndexExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::MemberIndexExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::MemberIndexExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::MemberIndexExpressionContext::MemberIndexExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::MemberIndexExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemberIndexExpression(this);
}
void OrcParser::MemberIndexExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemberIndexExpression(this);
}

std::any OrcParser::MemberIndexExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitMemberIndexExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DerefExpressionContext ------------------------------------------------------------------

OrcParser::SingleExpressionContext* OrcParser::DerefExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::DerefExpressionContext::DerefExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::DerefExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDerefExpression(this);
}
void OrcParser::DerefExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDerefExpression(this);
}

std::any OrcParser::DerefExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitDerefExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierExpressionContext ------------------------------------------------------------------

tree::TerminalNode* OrcParser::IdentifierExpressionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::IdentifierExpressionContext::IdentifierExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::IdentifierExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierExpression(this);
}
void OrcParser::IdentifierExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierExpression(this);
}

std::any OrcParser::IdentifierExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitIdentifierExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitAndExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::BitAndExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::BitAndExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::BitAndExpressionContext::BitAndExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::BitAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitAndExpression(this);
}
void OrcParser::BitAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitAndExpression(this);
}

std::any OrcParser::BitAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitBitAndExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitOrExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::BitOrExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::BitOrExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::BitOrExpressionContext::BitOrExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::BitOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitOrExpression(this);
}
void OrcParser::BitOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitOrExpression(this);
}

std::any OrcParser::BitOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitBitOrExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentOperatorExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::AssignmentOperatorExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::AssignmentOperatorExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::AssignmentOperatorContext* OrcParser::AssignmentOperatorExpressionContext::assignmentOperator() {
  return getRuleContext<OrcParser::AssignmentOperatorContext>(0);
}

OrcParser::AssignmentOperatorExpressionContext::AssignmentOperatorExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::AssignmentOperatorExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperatorExpression(this);
}
void OrcParser::AssignmentOperatorExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperatorExpression(this);
}

std::any OrcParser::AssignmentOperatorExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperatorExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CastExpressionContext ------------------------------------------------------------------

OrcParser::TypeContext* OrcParser::CastExpressionContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

OrcParser::SingleExpressionContext* OrcParser::CastExpressionContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::CastExpressionContext::CastExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::CastExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCastExpression(this);
}
void OrcParser::CastExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCastExpression(this);
}

std::any OrcParser::CastExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitCastExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CoalesceExpressionContext ------------------------------------------------------------------

std::vector<OrcParser::SingleExpressionContext *> OrcParser::CoalesceExpressionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::CoalesceExpressionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

OrcParser::CoalesceExpressionContext::CoalesceExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::CoalesceExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCoalesceExpression(this);
}
void OrcParser::CoalesceExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCoalesceExpression(this);
}

std::any OrcParser::CoalesceExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitCoalesceExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LabelClosureExpressionContext ------------------------------------------------------------------

OrcParser::ClosureExpressionContext* OrcParser::LabelClosureExpressionContext::closureExpression() {
  return getRuleContext<OrcParser::ClosureExpressionContext>(0);
}

OrcParser::LabelClosureExpressionContext::LabelClosureExpressionContext(SingleExpressionContext *ctx) { copyFrom(ctx); }

void OrcParser::LabelClosureExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabelClosureExpression(this);
}
void OrcParser::LabelClosureExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabelClosureExpression(this);
}

std::any OrcParser::LabelClosureExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitLabelClosureExpression(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::SingleExpressionContext* OrcParser::singleExpression() {
   return singleExpression(0);
}

OrcParser::SingleExpressionContext* OrcParser::singleExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  OrcParser::SingleExpressionContext *_localctx = _tracker.createInstance<SingleExpressionContext>(_ctx, parentState);
  OrcParser::SingleExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, OrcParser::RuleSingleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(188);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<LabelClosureExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(155);
      closureExpression();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NewExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(156);
      match(OrcParser::New);
      setState(157);
      match(OrcParser::Id);
      setState(158);
      arguments();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<GetAddressExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(159);
      match(OrcParser::T__11);
      setState(160);
      singleExpression(29);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<DerefExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(161);
      match(OrcParser::T__12);
      setState(162);
      singleExpression(28);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PreIncrementExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(163);
      match(OrcParser::T__4);
      setState(164);
      singleExpression(27);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PreDecreaseExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(165);
      match(OrcParser::T__5);
      setState(166);
      singleExpression(26);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<UnaryPlusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(167);
      match(OrcParser::T__13);
      setState(168);
      singleExpression(25);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<UnaryMinusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(169);
      match(OrcParser::T__14);
      setState(170);
      singleExpression(24);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BitNotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(171);
      match(OrcParser::T__15);
      setState(172);
      singleExpression(23);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<NotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(173);
      match(OrcParser::T__16);
      setState(174);
      singleExpression(22);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<CastExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(175);
      match(OrcParser::T__0);
      setState(176);
      type();
      setState(177);
      match(OrcParser::T__2);
      setState(178);
      singleExpression(8);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<ThisExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(180);
      match(OrcParser::This);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<IdentifierExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(181);
      match(OrcParser::Id);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<SuperExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(182);
      match(OrcParser::Super);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(183);
      literal();
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<ParenthesizedExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(184);
      match(OrcParser::T__0);
      setState(185);
      expressionSequence();
      setState(186);
      match(OrcParser::T__2);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(258);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(256);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MultiplicativeExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(190);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(191);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 794624) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(192);
          singleExpression(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AdditiveExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(193);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(194);
          _la = _input->LA(1);
          if (!(_la == OrcParser::T__13

          || _la == OrcParser::T__14)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(195);
          singleExpression(21);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CoalesceExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(196);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(197);
          match(OrcParser::T__19);
          setState(198);
          singleExpression(20);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BitShiftExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(199);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(200);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 14680064) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(201);
          singleExpression(19);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<RelationalExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(202);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(203);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 251658240) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(204);
          singleExpression(18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<InstanceofExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(205);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(206);
          match(OrcParser::Instanceof);
          setState(207);
          singleExpression(17);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<EqualityExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(208);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(209);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4026531840) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(210);
          singleExpression(16);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BitAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(211);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(212);
          match(OrcParser::T__11);
          setState(213);
          singleExpression(15);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BitXOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(214);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(215);
          match(OrcParser::T__3);
          setState(216);
          singleExpression(14);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BitOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(217);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(218);
          match(OrcParser::T__31);
          setState(219);
          singleExpression(13);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<LogicalAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(220);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(221);
          match(OrcParser::T__32);
          setState(222);
          singleExpression(12);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<LogicalOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(223);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(224);
          match(OrcParser::T__33);
          setState(225);
          singleExpression(11);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<TernaryExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(226);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(227);
          match(OrcParser::T__34);
          setState(228);
          singleExpression(0);
          setState(229);
          match(OrcParser::T__35);
          setState(230);
          singleExpression(10);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<AssignmentExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(232);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(233);
          match(OrcParser::T__36);
          setState(234);
          singleExpression(7);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<AssignmentOperatorExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(235);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(236);
          assignmentOperator();
          setState(237);
          singleExpression(6);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<CallExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(239);

          if (!(precpred(_ctx, 36))) throw FailedPredicateException(this, "precpred(_ctx, 36)");
          setState(240);
          arguments();
          break;
        }

        case 17: {
          auto newContext = _tracker.createInstance<PostIncrementExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(241);

          if (!(precpred(_ctx, 35))) throw FailedPredicateException(this, "precpred(_ctx, 35)");
          setState(242);
          match(OrcParser::T__4);
          break;
        }

        case 18: {
          auto newContext = _tracker.createInstance<PostDecreaseExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(243);

          if (!(precpred(_ctx, 34))) throw FailedPredicateException(this, "precpred(_ctx, 34)");
          setState(244);
          match(OrcParser::T__5);
          break;
        }

        case 19: {
          auto newContext = _tracker.createInstance<MemberIndexExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(245);

          if (!(precpred(_ctx, 32))) throw FailedPredicateException(this, "precpred(_ctx, 32)");
          setState(246);
          match(OrcParser::T__6);
          setState(247);
          singleExpression(0);
          setState(248);
          match(OrcParser::T__7);
          break;
        }

        case 20: {
          auto newContext = _tracker.createInstance<MemberDotExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(250);

          if (!(precpred(_ctx, 31))) throw FailedPredicateException(this, "precpred(_ctx, 31)");
          setState(251);
          _la = _input->LA(1);
          if (!(_la == OrcParser::T__8

          || _la == OrcParser::T__9)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(253);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == OrcParser::T__10) {
            setState(252);
            match(OrcParser::T__10);
          }
          setState(255);
          match(OrcParser::Id);
          break;
        }

        default:
          break;
        } 
      }
      setState(260);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

OrcParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}


size_t OrcParser::AssignmentOperatorContext::getRuleIndex() const {
  return OrcParser::RuleAssignmentOperator;
}

void OrcParser::AssignmentOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperator(this);
}

void OrcParser::AssignmentOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperator(this);
}


std::any OrcParser::AssignmentOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperator(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::AssignmentOperatorContext* OrcParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 12, OrcParser::RuleAssignmentOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(261);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2251524935778304) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmptyStatementContext ------------------------------------------------------------------

OrcParser::EmptyStatementContext::EmptyStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}


size_t OrcParser::EmptyStatementContext::getRuleIndex() const {
  return OrcParser::RuleEmptyStatement;
}

void OrcParser::EmptyStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmptyStatement(this);
}

void OrcParser::EmptyStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmptyStatement(this);
}


std::any OrcParser::EmptyStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitEmptyStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::EmptyStatementContext* OrcParser::emptyStatement() {
  EmptyStatementContext *_localctx = _tracker.createInstance<EmptyStatementContext>(_ctx, getState());
  enterRule(_localctx, 14, OrcParser::RuleEmptyStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    match(OrcParser::T__50);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDefinitionContext ------------------------------------------------------------------

OrcParser::StructDefinitionContext::StructDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::StructDefinitionContext::Struct() {
  return getToken(OrcParser::Struct, 0);
}

tree::TerminalNode* OrcParser::StructDefinitionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

tree::TerminalNode* OrcParser::StructDefinitionContext::CloseBrace() {
  return getToken(OrcParser::CloseBrace, 0);
}

std::vector<OrcParser::StructMemberContext *> OrcParser::StructDefinitionContext::structMember() {
  return getRuleContexts<OrcParser::StructMemberContext>();
}

OrcParser::StructMemberContext* OrcParser::StructDefinitionContext::structMember(size_t i) {
  return getRuleContext<OrcParser::StructMemberContext>(i);
}


size_t OrcParser::StructDefinitionContext::getRuleIndex() const {
  return OrcParser::RuleStructDefinition;
}

void OrcParser::StructDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDefinition(this);
}

void OrcParser::StructDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDefinition(this);
}


std::any OrcParser::StructDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitStructDefinition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::StructDefinitionContext* OrcParser::structDefinition() {
  StructDefinitionContext *_localctx = _tracker.createInstance<StructDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 16, OrcParser::RuleStructDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(265);
    match(OrcParser::Struct);
    setState(266);
    match(OrcParser::Id);
    setState(267);
    match(OrcParser::T__51);
    setState(271);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 4398181785607) != 0)) {
      setState(268);
      structMember();
      setState(273);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(274);
    match(OrcParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructMemberContext ------------------------------------------------------------------

OrcParser::StructMemberContext::StructMemberContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::StructMemberContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::StructMemberContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::EosContext* OrcParser::StructMemberContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}

OrcParser::ArraySizeDeclarationContext* OrcParser::StructMemberContext::arraySizeDeclaration() {
  return getRuleContext<OrcParser::ArraySizeDeclarationContext>(0);
}

OrcParser::FunctionPointerVarDeclarationContext* OrcParser::StructMemberContext::functionPointerVarDeclaration() {
  return getRuleContext<OrcParser::FunctionPointerVarDeclarationContext>(0);
}


size_t OrcParser::StructMemberContext::getRuleIndex() const {
  return OrcParser::RuleStructMember;
}

void OrcParser::StructMemberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructMember(this);
}

void OrcParser::StructMemberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructMember(this);
}


std::any OrcParser::StructMemberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitStructMember(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::StructMemberContext* OrcParser::structMember() {
  StructMemberContext *_localctx = _tracker.createInstance<StructMemberContext>(_ctx, getState());
  enterRule(_localctx, 18, OrcParser::RuleStructMember);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(286);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(276);
      type();
      setState(277);
      match(OrcParser::Id);
      setState(279);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
      case 1: {
        setState(278);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(281);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(283);
      functionPointerVarDeclaration();
      setState(284);
      eos();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArraySizeDeclarationContext ------------------------------------------------------------------

OrcParser::ArraySizeDeclarationContext::ArraySizeDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ArraySizeDeclarationContext::DecimalLiteral() {
  return getToken(OrcParser::DecimalLiteral, 0);
}


size_t OrcParser::ArraySizeDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleArraySizeDeclaration;
}

void OrcParser::ArraySizeDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArraySizeDeclaration(this);
}

void OrcParser::ArraySizeDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArraySizeDeclaration(this);
}


std::any OrcParser::ArraySizeDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitArraySizeDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ArraySizeDeclarationContext* OrcParser::arraySizeDeclaration() {
  ArraySizeDeclarationContext *_localctx = _tracker.createInstance<ArraySizeDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 20, OrcParser::RuleArraySizeDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    match(OrcParser::T__6);
    setState(289);
    match(OrcParser::DecimalLiteral);
    setState(290);
    match(OrcParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclarationContext ------------------------------------------------------------------

OrcParser::VarDeclarationContext::VarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::VarDeclarationContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::VarDeclarationContext::Id() {
  return getToken(OrcParser::Id, 0);
}

tree::TerminalNode* OrcParser::VarDeclarationContext::Static() {
  return getToken(OrcParser::Static, 0);
}

OrcParser::ArraySizeDeclarationContext* OrcParser::VarDeclarationContext::arraySizeDeclaration() {
  return getRuleContext<OrcParser::ArraySizeDeclarationContext>(0);
}

OrcParser::SingleExpressionContext* OrcParser::VarDeclarationContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::FunctionPointerVarDeclarationContext* OrcParser::VarDeclarationContext::functionPointerVarDeclaration() {
  return getRuleContext<OrcParser::FunctionPointerVarDeclarationContext>(0);
}


size_t OrcParser::VarDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleVarDeclaration;
}

void OrcParser::VarDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDeclaration(this);
}

void OrcParser::VarDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDeclaration(this);
}


std::any OrcParser::VarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::VarDeclarationContext* OrcParser::varDeclaration() {
  VarDeclarationContext *_localctx = _tracker.createInstance<VarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 22, OrcParser::RuleVarDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(308);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(293);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(292);
        match(OrcParser::Static);
      }
      setState(295);
      type();
      setState(296);
      match(OrcParser::Id);
      setState(298);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(297);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(302);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(300);
        match(OrcParser::T__36);
        setState(301);
        singleExpression(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(305);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(304);
        match(OrcParser::Static);
      }
      setState(307);
      functionPointerVarDeclaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

OrcParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::ClosureExpressionContext* OrcParser::StatementContext::closureExpression() {
  return getRuleContext<OrcParser::ClosureExpressionContext>(0);
}

OrcParser::EosContext* OrcParser::StatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}

OrcParser::VarDeclarationContext* OrcParser::StatementContext::varDeclaration() {
  return getRuleContext<OrcParser::VarDeclarationContext>(0);
}

OrcParser::ScopeStatementContext* OrcParser::StatementContext::scopeStatement() {
  return getRuleContext<OrcParser::ScopeStatementContext>(0);
}

OrcParser::BlockContext* OrcParser::StatementContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}

OrcParser::ContinueStatementContext* OrcParser::StatementContext::continueStatement() {
  return getRuleContext<OrcParser::ContinueStatementContext>(0);
}

OrcParser::BreakStatementContext* OrcParser::StatementContext::breakStatement() {
  return getRuleContext<OrcParser::BreakStatementContext>(0);
}

OrcParser::SelectionStatementContext* OrcParser::StatementContext::selectionStatement() {
  return getRuleContext<OrcParser::SelectionStatementContext>(0);
}

OrcParser::ReturnStatementContext* OrcParser::StatementContext::returnStatement() {
  return getRuleContext<OrcParser::ReturnStatementContext>(0);
}

OrcParser::IterationStatementContext* OrcParser::StatementContext::iterationStatement() {
  return getRuleContext<OrcParser::IterationStatementContext>(0);
}

OrcParser::SingleExpressionContext* OrcParser::StatementContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::EmptyStatementContext* OrcParser::StatementContext::emptyStatement() {
  return getRuleContext<OrcParser::EmptyStatementContext>(0);
}


size_t OrcParser::StatementContext::getRuleIndex() const {
  return OrcParser::RuleStatement;
}

void OrcParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void OrcParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any OrcParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::StatementContext* OrcParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 24, OrcParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(327);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(310);
      closureExpression();
      setState(311);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(313);
      varDeclaration();
      setState(314);
      eos();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(316);
      scopeStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(317);
      block();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(318);
      continueStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(319);
      breakStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(320);
      selectionStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(321);
      returnStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(322);
      iterationStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(323);
      singleExpression(0);
      setState(324);
      eos();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(326);
      emptyStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

OrcParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ContinueStatementContext::Continue() {
  return getToken(OrcParser::Continue, 0);
}

OrcParser::EosContext* OrcParser::ContinueStatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::ContinueStatementContext::getRuleIndex() const {
  return OrcParser::RuleContinueStatement;
}

void OrcParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void OrcParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}


std::any OrcParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ContinueStatementContext* OrcParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, OrcParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    match(OrcParser::Continue);
    setState(330);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

OrcParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::BreakStatementContext::Break() {
  return getToken(OrcParser::Break, 0);
}

OrcParser::EosContext* OrcParser::BreakStatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::BreakStatementContext::getRuleIndex() const {
  return OrcParser::RuleBreakStatement;
}

void OrcParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void OrcParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}


std::any OrcParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::BreakStatementContext* OrcParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, OrcParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(332);
    match(OrcParser::Break);
    setState(333);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

OrcParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ReturnStatementContext::Return() {
  return getToken(OrcParser::Return, 0);
}

OrcParser::EosContext* OrcParser::ReturnStatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}

OrcParser::SingleExpressionContext* OrcParser::ReturnStatementContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}


size_t OrcParser::ReturnStatementContext::getRuleIndex() const {
  return OrcParser::RuleReturnStatement;
}

void OrcParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void OrcParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


std::any OrcParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ReturnStatementContext* OrcParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, OrcParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    match(OrcParser::Return);
    setState(337);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(336);
      singleExpression(0);
      break;
    }

    default:
      break;
    }
    setState(339);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopeStatementContext ------------------------------------------------------------------

OrcParser::ScopeStatementContext::ScopeStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::SingleExpressionContext* OrcParser::ScopeStatementContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::BlockContext* OrcParser::ScopeStatementContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}


size_t OrcParser::ScopeStatementContext::getRuleIndex() const {
  return OrcParser::RuleScopeStatement;
}

void OrcParser::ScopeStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScopeStatement(this);
}

void OrcParser::ScopeStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScopeStatement(this);
}


std::any OrcParser::ScopeStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitScopeStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ScopeStatementContext* OrcParser::scopeStatement() {
  ScopeStatementContext *_localctx = _tracker.createInstance<ScopeStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, OrcParser::RuleScopeStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    singleExpression(0);
    setState(342);
    _la = _input->LA(1);
    if (!(_la == OrcParser::T__8

    || _la == OrcParser::T__15)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(343);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

OrcParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::IterationStatementContext::While() {
  return getToken(OrcParser::While, 0);
}

OrcParser::SingleExpressionContext* OrcParser::IterationStatementContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::BlockContext* OrcParser::IterationStatementContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}

tree::TerminalNode* OrcParser::IterationStatementContext::For() {
  return getToken(OrcParser::For, 0);
}

OrcParser::ForConditionContext* OrcParser::IterationStatementContext::forCondition() {
  return getRuleContext<OrcParser::ForConditionContext>(0);
}


size_t OrcParser::IterationStatementContext::getRuleIndex() const {
  return OrcParser::RuleIterationStatement;
}

void OrcParser::IterationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIterationStatement(this);
}

void OrcParser::IterationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIterationStatement(this);
}


std::any OrcParser::IterationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitIterationStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::IterationStatementContext* OrcParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, OrcParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(359);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(345);
      match(OrcParser::While);
      setState(346);
      singleExpression(0);
      setState(347);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(349);
      match(OrcParser::For);
      setState(350);
      match(OrcParser::T__0);
      setState(351);
      forCondition();
      setState(352);
      match(OrcParser::T__2);
      setState(353);
      block();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(355);
      match(OrcParser::For);
      setState(356);
      forCondition();
      setState(357);
      block();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForConditionContext ------------------------------------------------------------------

OrcParser::ForConditionContext::ForConditionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::VarDeclarationContext* OrcParser::ForConditionContext::varDeclaration() {
  return getRuleContext<OrcParser::VarDeclarationContext>(0);
}

std::vector<OrcParser::SingleExpressionContext *> OrcParser::ForConditionContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::ForConditionContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}


size_t OrcParser::ForConditionContext::getRuleIndex() const {
  return OrcParser::RuleForCondition;
}

void OrcParser::ForConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForCondition(this);
}

void OrcParser::ForConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForCondition(this);
}


std::any OrcParser::ForConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitForCondition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ForConditionContext* OrcParser::forCondition() {
  ForConditionContext *_localctx = _tracker.createInstance<ForConditionContext>(_ctx, getState());
  enterRule(_localctx, 36, OrcParser::RuleForCondition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(365);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(361);
      varDeclaration();
      break;
    }

    case 2: {
      setState(363);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 75)) & 4286595137) != 0)) {
        setState(362);
        singleExpression(0);
      }
      break;
    }

    default:
      break;
    }
    setState(367);
    match(OrcParser::T__50);
    setState(369);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 4286595137) != 0)) {
      setState(368);
      singleExpression(0);
    }
    setState(371);
    match(OrcParser::T__50);
    setState(373);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 4286595137) != 0)) {
      setState(372);
      singleExpression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionStatementContext ------------------------------------------------------------------

OrcParser::SelectionStatementContext::SelectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::SelectionStatementContext::If() {
  return getToken(OrcParser::If, 0);
}

std::vector<OrcParser::SingleExpressionContext *> OrcParser::SelectionStatementContext::singleExpression() {
  return getRuleContexts<OrcParser::SingleExpressionContext>();
}

OrcParser::SingleExpressionContext* OrcParser::SelectionStatementContext::singleExpression(size_t i) {
  return getRuleContext<OrcParser::SingleExpressionContext>(i);
}

std::vector<OrcParser::BlockContext *> OrcParser::SelectionStatementContext::block() {
  return getRuleContexts<OrcParser::BlockContext>();
}

OrcParser::BlockContext* OrcParser::SelectionStatementContext::block(size_t i) {
  return getRuleContext<OrcParser::BlockContext>(i);
}

tree::TerminalNode* OrcParser::SelectionStatementContext::Else() {
  return getToken(OrcParser::Else, 0);
}


size_t OrcParser::SelectionStatementContext::getRuleIndex() const {
  return OrcParser::RuleSelectionStatement;
}

void OrcParser::SelectionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectionStatement(this);
}

void OrcParser::SelectionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectionStatement(this);
}


std::any OrcParser::SelectionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitSelectionStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::SelectionStatementContext* OrcParser::selectionStatement() {
  SelectionStatementContext *_localctx = _tracker.createInstance<SelectionStatementContext>(_ctx, getState());
  enterRule(_localctx, 38, OrcParser::RuleSelectionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(375);
    match(OrcParser::If);
    setState(376);
    singleExpression(0);
    setState(377);
    block();
    setState(384);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__52) {
      setState(378);
      match(OrcParser::T__52);
      setState(379);
      singleExpression(0);
      setState(380);
      block();
      setState(386);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(389);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Else) {
      setState(387);
      match(OrcParser::Else);
      setState(388);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

OrcParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::BlockContext::CloseBrace() {
  return getToken(OrcParser::CloseBrace, 0);
}

std::vector<OrcParser::StatementContext *> OrcParser::BlockContext::statement() {
  return getRuleContexts<OrcParser::StatementContext>();
}

OrcParser::StatementContext* OrcParser::BlockContext::statement(size_t i) {
  return getRuleContext<OrcParser::StatementContext>(i);
}


size_t OrcParser::BlockContext::getRuleIndex() const {
  return OrcParser::RuleBlock;
}

void OrcParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void OrcParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any OrcParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::BlockContext* OrcParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 40, OrcParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(391);
    match(OrcParser::T__51);
    setState(395);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -317503773729361806) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 8780156237895) != 0)) {
      setState(392);
      statement();
      setState(397);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(398);
    match(OrcParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

OrcParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::PrimitiveTypeContext* OrcParser::TypeContext::primitiveType() {
  return getRuleContext<OrcParser::PrimitiveTypeContext>(0);
}

OrcParser::TypeQualifierContext* OrcParser::TypeContext::typeQualifier() {
  return getRuleContext<OrcParser::TypeQualifierContext>(0);
}

OrcParser::ArraySizeDeclarationContext* OrcParser::TypeContext::arraySizeDeclaration() {
  return getRuleContext<OrcParser::ArraySizeDeclarationContext>(0);
}

OrcParser::ClosureTypeContext* OrcParser::TypeContext::closureType() {
  return getRuleContext<OrcParser::ClosureTypeContext>(0);
}

OrcParser::PointerContext* OrcParser::TypeContext::pointer() {
  return getRuleContext<OrcParser::PointerContext>(0);
}

OrcParser::RefContext* OrcParser::TypeContext::ref() {
  return getRuleContext<OrcParser::RefContext>(0);
}

tree::TerminalNode* OrcParser::TypeContext::Id() {
  return getToken(OrcParser::Id, 0);
}

tree::TerminalNode* OrcParser::TypeContext::Struct() {
  return getToken(OrcParser::Struct, 0);
}


size_t OrcParser::TypeContext::getRuleIndex() const {
  return OrcParser::RuleType;
}

void OrcParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void OrcParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


std::any OrcParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::TypeContext* OrcParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 42, OrcParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(417);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(401);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 68719476743) != 0)) {
        setState(400);
        typeQualifier();
      }
      setState(403);
      primitiveType();
      setState(405);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__6) {
        setState(404);
        arraySizeDeclaration();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(407);
      closureType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(408);
      pointer();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(409);
      ref();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(411);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 68719476743) != 0)) {
        setState(410);
        typeQualifier();
      }
      setState(414);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Struct) {
        setState(413);
        match(OrcParser::Struct);
      }
      setState(416);
      match(OrcParser::Id);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClosureTypeContext ------------------------------------------------------------------

OrcParser::ClosureTypeContext::ClosureTypeContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::ClosureTypeContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::ClosureTypeContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}


size_t OrcParser::ClosureTypeContext::getRuleIndex() const {
  return OrcParser::RuleClosureType;
}

void OrcParser::ClosureTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClosureType(this);
}

void OrcParser::ClosureTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClosureType(this);
}


std::any OrcParser::ClosureTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitClosureType(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ClosureTypeContext* OrcParser::closureType() {
  ClosureTypeContext *_localctx = _tracker.createInstance<ClosureTypeContext>(_ctx, getState());
  enterRule(_localctx, 44, OrcParser::RuleClosureType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(419);
    match(OrcParser::T__3);
    setState(420);
    type();
    setState(421);
    argumentsDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeArgContext ------------------------------------------------------------------

OrcParser::FunctionTypeArgContext::FunctionTypeArgContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::FunctionTypeArgContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::FunctionTypeArgContext::Id() {
  return getToken(OrcParser::Id, 0);
}


size_t OrcParser::FunctionTypeArgContext::getRuleIndex() const {
  return OrcParser::RuleFunctionTypeArg;
}

void OrcParser::FunctionTypeArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionTypeArg(this);
}

void OrcParser::FunctionTypeArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionTypeArg(this);
}


std::any OrcParser::FunctionTypeArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitFunctionTypeArg(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::FunctionTypeArgContext* OrcParser::functionTypeArg() {
  FunctionTypeArgContext *_localctx = _tracker.createInstance<FunctionTypeArgContext>(_ctx, getState());
  enterRule(_localctx, 46, OrcParser::RuleFunctionTypeArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(423);
    type();
    setState(425);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(424);
      match(OrcParser::Id);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeContext ------------------------------------------------------------------

OrcParser::AttributeContext::AttributeContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::AttributeContext::Id() {
  return getToken(OrcParser::Id, 0);
}


size_t OrcParser::AttributeContext::getRuleIndex() const {
  return OrcParser::RuleAttribute;
}

void OrcParser::AttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttribute(this);
}

void OrcParser::AttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttribute(this);
}


std::any OrcParser::AttributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitAttribute(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::AttributeContext* OrcParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 48, OrcParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    match(OrcParser::T__53);
    setState(428);
    match(OrcParser::T__0);
    setState(429);
    match(OrcParser::T__0);
    setState(430);
    match(OrcParser::Id);
    setState(431);
    match(OrcParser::T__2);
    setState(432);
    match(OrcParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeContext ------------------------------------------------------------------

OrcParser::FunctionTypeContext::FunctionTypeContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::FunctionTypeContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::FunctionTypeContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}

std::vector<OrcParser::AttributeContext *> OrcParser::FunctionTypeContext::attribute() {
  return getRuleContexts<OrcParser::AttributeContext>();
}

OrcParser::AttributeContext* OrcParser::FunctionTypeContext::attribute(size_t i) {
  return getRuleContext<OrcParser::AttributeContext>(i);
}


size_t OrcParser::FunctionTypeContext::getRuleIndex() const {
  return OrcParser::RuleFunctionType;
}

void OrcParser::FunctionTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionType(this);
}

void OrcParser::FunctionTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionType(this);
}


std::any OrcParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::FunctionTypeContext* OrcParser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 50, OrcParser::RuleFunctionType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(434);
    type();
    setState(435);
    argumentsDeclaration();
    setState(439);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__53) {
      setState(436);
      attribute();
      setState(441);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeQualifierContext ------------------------------------------------------------------

OrcParser::TypeQualifierContext::TypeQualifierContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::TypeQualifierContext::Const() {
  return getToken(OrcParser::Const, 0);
}


size_t OrcParser::TypeQualifierContext::getRuleIndex() const {
  return OrcParser::RuleTypeQualifier;
}

void OrcParser::TypeQualifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeQualifier(this);
}

void OrcParser::TypeQualifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeQualifier(this);
}


std::any OrcParser::TypeQualifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitTypeQualifier(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::TypeQualifierContext* OrcParser::typeQualifier() {
  TypeQualifierContext *_localctx = _tracker.createInstance<TypeQualifierContext>(_ctx, getState());
  enterRule(_localctx, 52, OrcParser::RuleTypeQualifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(442);
    _la = _input->LA(1);
    if (!(((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & 68719476743) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PointerContext ------------------------------------------------------------------

OrcParser::PointerContext::PointerContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::PrimitiveTypeContext* OrcParser::PointerContext::primitiveType() {
  return getRuleContext<OrcParser::PrimitiveTypeContext>(0);
}

std::vector<OrcParser::TypeQualifierContext *> OrcParser::PointerContext::typeQualifier() {
  return getRuleContexts<OrcParser::TypeQualifierContext>();
}

OrcParser::TypeQualifierContext* OrcParser::PointerContext::typeQualifier(size_t i) {
  return getRuleContext<OrcParser::TypeQualifierContext>(i);
}

tree::TerminalNode* OrcParser::PointerContext::Id() {
  return getToken(OrcParser::Id, 0);
}

tree::TerminalNode* OrcParser::PointerContext::Struct() {
  return getToken(OrcParser::Struct, 0);
}


size_t OrcParser::PointerContext::getRuleIndex() const {
  return OrcParser::RulePointer;
}

void OrcParser::PointerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointer(this);
}

void OrcParser::PointerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointer(this);
}


std::any OrcParser::PointerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitPointer(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::PointerContext* OrcParser::pointer() {
  PointerContext *_localctx = _tracker.createInstance<PointerContext>(_ctx, getState());
  enterRule(_localctx, 54, OrcParser::RulePointer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(445);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & 68719476743) != 0)) {
      setState(444);
      typeQualifier();
    }
    setState(452);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::T__58:
      case OrcParser::T__59:
      case OrcParser::T__60:
      case OrcParser::T__61:
      case OrcParser::T__62:
      case OrcParser::T__63:
      case OrcParser::T__64:
      case OrcParser::T__65:
      case OrcParser::Void: {
        setState(447);
        primitiveType();
        break;
      }

      case OrcParser::Struct:
      case OrcParser::Id: {
        setState(449);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == OrcParser::Struct) {
          setState(448);
          match(OrcParser::Struct);
        }
        setState(451);
        match(OrcParser::Id);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(467); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(457);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 68719476743) != 0)) {
        setState(454);
        typeQualifier();
        setState(459);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(460);
      match(OrcParser::T__12);
      setState(464);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(461);
          typeQualifier(); 
        }
        setState(466);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
      }
      setState(469); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 252201579132755968) != 0) || _la == OrcParser::Const);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RefContext ------------------------------------------------------------------

OrcParser::RefContext::RefContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::RefContext::Id() {
  return getToken(OrcParser::Id, 0);
}

tree::TerminalNode* OrcParser::RefContext::Struct() {
  return getToken(OrcParser::Struct, 0);
}


size_t OrcParser::RefContext::getRuleIndex() const {
  return OrcParser::RuleRef;
}

void OrcParser::RefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRef(this);
}

void OrcParser::RefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRef(this);
}


std::any OrcParser::RefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitRef(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::RefContext* OrcParser::ref() {
  RefContext *_localctx = _tracker.createInstance<RefContext>(_ctx, getState());
  enterRule(_localctx, 56, OrcParser::RuleRef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(472);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Struct) {
      setState(471);
      match(OrcParser::Struct);
    }
    setState(474);
    match(OrcParser::Id);
    setState(475);
    match(OrcParser::T__57);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimitiveTypeContext ------------------------------------------------------------------

OrcParser::PrimitiveTypeContext::PrimitiveTypeContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::PrimitiveTypeContext::Void() {
  return getToken(OrcParser::Void, 0);
}


size_t OrcParser::PrimitiveTypeContext::getRuleIndex() const {
  return OrcParser::RulePrimitiveType;
}

void OrcParser::PrimitiveTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimitiveType(this);
}

void OrcParser::PrimitiveTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimitiveType(this);
}


std::any OrcParser::PrimitiveTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitPrimitiveType(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::PrimitiveTypeContext* OrcParser::primitiveType() {
  PrimitiveTypeContext *_localctx = _tracker.createInstance<PrimitiveTypeContext>(_ctx, getState());
  enterRule(_localctx, 58, OrcParser::RulePrimitiveType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(500);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(477);
      match(OrcParser::T__58);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(478);
      match(OrcParser::T__59);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(479);
      match(OrcParser::T__60);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(480);
      match(OrcParser::T__61);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(481);
      match(OrcParser::T__62);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(482);
      match(OrcParser::T__63);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(483);
      match(OrcParser::Void);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(484);
      match(OrcParser::T__64);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(485);
      match(OrcParser::T__64);
      setState(486);
      match(OrcParser::T__64);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(487);
      match(OrcParser::T__64);
      setState(488);
      match(OrcParser::T__61);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(489);
      match(OrcParser::T__65);
      setState(490);
      match(OrcParser::T__62);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(491);
      match(OrcParser::T__65);
      setState(492);
      match(OrcParser::T__58);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(493);
      match(OrcParser::T__65);
      setState(494);
      match(OrcParser::T__59);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(495);
      match(OrcParser::T__65);
      setState(496);
      match(OrcParser::T__64);
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(497);
      match(OrcParser::T__65);
      setState(498);
      match(OrcParser::T__64);
      setState(499);
      match(OrcParser::T__64);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumDefinitionContext ------------------------------------------------------------------

OrcParser::EnumDefinitionContext::EnumDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::EnumDefinitionContext::Enum() {
  return getToken(OrcParser::Enum, 0);
}

tree::TerminalNode* OrcParser::EnumDefinitionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

std::vector<OrcParser::EnumItemContext *> OrcParser::EnumDefinitionContext::enumItem() {
  return getRuleContexts<OrcParser::EnumItemContext>();
}

OrcParser::EnumItemContext* OrcParser::EnumDefinitionContext::enumItem(size_t i) {
  return getRuleContext<OrcParser::EnumItemContext>(i);
}

tree::TerminalNode* OrcParser::EnumDefinitionContext::CloseBrace() {
  return getToken(OrcParser::CloseBrace, 0);
}

OrcParser::EosContext* OrcParser::EnumDefinitionContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::EnumDefinitionContext::getRuleIndex() const {
  return OrcParser::RuleEnumDefinition;
}

void OrcParser::EnumDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumDefinition(this);
}

void OrcParser::EnumDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumDefinition(this);
}


std::any OrcParser::EnumDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitEnumDefinition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::EnumDefinitionContext* OrcParser::enumDefinition() {
  EnumDefinitionContext *_localctx = _tracker.createInstance<EnumDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 60, OrcParser::RuleEnumDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(502);
    match(OrcParser::Enum);
    setState(503);
    match(OrcParser::Id);
    setState(504);
    match(OrcParser::T__51);
    setState(505);
    enumItem();
    setState(510);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(506);
        match(OrcParser::T__1);
        setState(507);
        enumItem(); 
      }
      setState(512);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    }
    setState(514);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__1) {
      setState(513);
      match(OrcParser::T__1);
    }
    setState(516);
    match(OrcParser::CloseBrace);
    setState(517);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumItemContext ------------------------------------------------------------------

OrcParser::EnumItemContext::EnumItemContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::EnumItemContext::Id() {
  return getToken(OrcParser::Id, 0);
}

tree::TerminalNode* OrcParser::EnumItemContext::DecimalLiteral() {
  return getToken(OrcParser::DecimalLiteral, 0);
}


size_t OrcParser::EnumItemContext::getRuleIndex() const {
  return OrcParser::RuleEnumItem;
}

void OrcParser::EnumItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumItem(this);
}

void OrcParser::EnumItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumItem(this);
}


std::any OrcParser::EnumItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitEnumItem(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::EnumItemContext* OrcParser::enumItem() {
  EnumItemContext *_localctx = _tracker.createInstance<EnumItemContext>(_ctx, getState());
  enterRule(_localctx, 62, OrcParser::RuleEnumItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(519);
    match(OrcParser::Id);
    setState(522);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__36) {
      setState(520);
      match(OrcParser::T__36);
      setState(521);
      match(OrcParser::DecimalLiteral);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExtensionDefinitionContext ------------------------------------------------------------------

OrcParser::ExtensionDefinitionContext::ExtensionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ExtensionDefinitionContext::Extension() {
  return getToken(OrcParser::Extension, 0);
}

tree::TerminalNode* OrcParser::ExtensionDefinitionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::ExtensionBlockContext* OrcParser::ExtensionDefinitionContext::extensionBlock() {
  return getRuleContext<OrcParser::ExtensionBlockContext>(0);
}


size_t OrcParser::ExtensionDefinitionContext::getRuleIndex() const {
  return OrcParser::RuleExtensionDefinition;
}

void OrcParser::ExtensionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtensionDefinition(this);
}

void OrcParser::ExtensionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtensionDefinition(this);
}


std::any OrcParser::ExtensionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitExtensionDefinition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ExtensionDefinitionContext* OrcParser::extensionDefinition() {
  ExtensionDefinitionContext *_localctx = _tracker.createInstance<ExtensionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 64, OrcParser::RuleExtensionDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(524);
    match(OrcParser::Extension);
    setState(525);
    match(OrcParser::Id);
    setState(526);
    extensionBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExtensionBlockContext ------------------------------------------------------------------

OrcParser::ExtensionBlockContext::ExtensionBlockContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ExtensionBlockContext::CloseBrace() {
  return getToken(OrcParser::CloseBrace, 0);
}

std::vector<OrcParser::MethodDeclarationContext *> OrcParser::ExtensionBlockContext::methodDeclaration() {
  return getRuleContexts<OrcParser::MethodDeclarationContext>();
}

OrcParser::MethodDeclarationContext* OrcParser::ExtensionBlockContext::methodDeclaration(size_t i) {
  return getRuleContext<OrcParser::MethodDeclarationContext>(i);
}


size_t OrcParser::ExtensionBlockContext::getRuleIndex() const {
  return OrcParser::RuleExtensionBlock;
}

void OrcParser::ExtensionBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtensionBlock(this);
}

void OrcParser::ExtensionBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtensionBlock(this);
}


std::any OrcParser::ExtensionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitExtensionBlock(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ExtensionBlockContext* OrcParser::extensionBlock() {
  ExtensionBlockContext *_localctx = _tracker.createInstance<ExtensionBlockContext>(_ctx, getState());
  enterRule(_localctx, 66, OrcParser::RuleExtensionBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(528);
    match(OrcParser::T__51);
    setState(532);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 4398198562823) != 0)) {
      setState(529);
      methodDeclaration();
      setState(534);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(535);
    match(OrcParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDefinitionContext ------------------------------------------------------------------

OrcParser::ClassDefinitionContext::ClassDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ClassDefinitionContext::Class() {
  return getToken(OrcParser::Class, 0);
}

std::vector<tree::TerminalNode *> OrcParser::ClassDefinitionContext::Id() {
  return getTokens(OrcParser::Id);
}

tree::TerminalNode* OrcParser::ClassDefinitionContext::Id(size_t i) {
  return getToken(OrcParser::Id, i);
}

OrcParser::ClassDefinitionBlockContext* OrcParser::ClassDefinitionContext::classDefinitionBlock() {
  return getRuleContext<OrcParser::ClassDefinitionBlockContext>(0);
}

OrcParser::EosContext* OrcParser::ClassDefinitionContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}

tree::TerminalNode* OrcParser::ClassDefinitionContext::Refc() {
  return getToken(OrcParser::Refc, 0);
}

tree::TerminalNode* OrcParser::ClassDefinitionContext::Extends() {
  return getToken(OrcParser::Extends, 0);
}


size_t OrcParser::ClassDefinitionContext::getRuleIndex() const {
  return OrcParser::RuleClassDefinition;
}

void OrcParser::ClassDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDefinition(this);
}

void OrcParser::ClassDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDefinition(this);
}


std::any OrcParser::ClassDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitClassDefinition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ClassDefinitionContext* OrcParser::classDefinition() {
  ClassDefinitionContext *_localctx = _tracker.createInstance<ClassDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 68, OrcParser::RuleClassDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(537);
    match(OrcParser::Class);
    setState(539);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Refc) {
      setState(538);
      match(OrcParser::Refc);
    }
    setState(541);
    match(OrcParser::Id);
    setState(544);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Extends) {
      setState(542);
      match(OrcParser::Extends);
      setState(543);
      match(OrcParser::Id);
    }
    setState(546);
    classDefinitionBlock();
    setState(547);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDefinitionBlockContext ------------------------------------------------------------------

OrcParser::ClassDefinitionBlockContext::ClassDefinitionBlockContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ClassDefinitionBlockContext::CloseBrace() {
  return getToken(OrcParser::CloseBrace, 0);
}

std::vector<OrcParser::ClassFieldDeclarationContext *> OrcParser::ClassDefinitionBlockContext::classFieldDeclaration() {
  return getRuleContexts<OrcParser::ClassFieldDeclarationContext>();
}

OrcParser::ClassFieldDeclarationContext* OrcParser::ClassDefinitionBlockContext::classFieldDeclaration(size_t i) {
  return getRuleContext<OrcParser::ClassFieldDeclarationContext>(i);
}

std::vector<OrcParser::MethodDeclarationContext *> OrcParser::ClassDefinitionBlockContext::methodDeclaration() {
  return getRuleContexts<OrcParser::MethodDeclarationContext>();
}

OrcParser::MethodDeclarationContext* OrcParser::ClassDefinitionBlockContext::methodDeclaration(size_t i) {
  return getRuleContext<OrcParser::MethodDeclarationContext>(i);
}


size_t OrcParser::ClassDefinitionBlockContext::getRuleIndex() const {
  return OrcParser::RuleClassDefinitionBlock;
}

void OrcParser::ClassDefinitionBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDefinitionBlock(this);
}

void OrcParser::ClassDefinitionBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDefinitionBlock(this);
}


std::any OrcParser::ClassDefinitionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitClassDefinitionBlock(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ClassDefinitionBlockContext* OrcParser::classDefinitionBlock() {
  ClassDefinitionBlockContext *_localctx = _tracker.createInstance<ClassDefinitionBlockContext>(_ctx, getState());
  enterRule(_localctx, 70, OrcParser::RuleClassDefinitionBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(549);
    match(OrcParser::T__51);
    setState(554);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 4398198562823) != 0)) {
      setState(552);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
      case 1: {
        setState(550);
        classFieldDeclaration();
        break;
      }

      case 2: {
        setState(551);
        methodDeclaration();
        break;
      }

      default:
        break;
      }
      setState(556);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(557);
    match(OrcParser::CloseBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassFieldDeclarationContext ------------------------------------------------------------------

OrcParser::ClassFieldDeclarationContext::ClassFieldDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::ClassFieldDeclarationContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::ClassFieldDeclarationContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::EosContext* OrcParser::ClassFieldDeclarationContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}

OrcParser::ArraySizeDeclarationContext* OrcParser::ClassFieldDeclarationContext::arraySizeDeclaration() {
  return getRuleContext<OrcParser::ArraySizeDeclarationContext>(0);
}

OrcParser::AssignRightPartContext* OrcParser::ClassFieldDeclarationContext::assignRightPart() {
  return getRuleContext<OrcParser::AssignRightPartContext>(0);
}

OrcParser::FunctionPointerVarDeclarationContext* OrcParser::ClassFieldDeclarationContext::functionPointerVarDeclaration() {
  return getRuleContext<OrcParser::FunctionPointerVarDeclarationContext>(0);
}


size_t OrcParser::ClassFieldDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleClassFieldDeclaration;
}

void OrcParser::ClassFieldDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassFieldDeclaration(this);
}

void OrcParser::ClassFieldDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassFieldDeclaration(this);
}


std::any OrcParser::ClassFieldDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitClassFieldDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ClassFieldDeclarationContext* OrcParser::classFieldDeclaration() {
  ClassFieldDeclarationContext *_localctx = _tracker.createInstance<ClassFieldDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 72, OrcParser::RuleClassFieldDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(575);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(559);
      type();
      setState(560);
      match(OrcParser::Id);
      setState(562);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
      case 1: {
        setState(561);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(565);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
      case 1: {
        setState(564);
        assignRightPart();
        break;
      }

      default:
        break;
      }
      setState(567);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(569);
      functionPointerVarDeclaration();
      setState(571);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
      case 1: {
        setState(570);
        assignRightPart();
        break;
      }

      default:
        break;
      }
      setState(573);
      eos();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodDeclarationContext ------------------------------------------------------------------

OrcParser::MethodDeclarationContext::MethodDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::FunctionDefinitionContext* OrcParser::MethodDeclarationContext::functionDefinition() {
  return getRuleContext<OrcParser::FunctionDefinitionContext>(0);
}

OrcParser::ExternFunctionDeclarationContext* OrcParser::MethodDeclarationContext::externFunctionDeclaration() {
  return getRuleContext<OrcParser::ExternFunctionDeclarationContext>(0);
}


size_t OrcParser::MethodDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleMethodDeclaration;
}

void OrcParser::MethodDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodDeclaration(this);
}

void OrcParser::MethodDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodDeclaration(this);
}


std::any OrcParser::MethodDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitMethodDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::MethodDeclarationContext* OrcParser::methodDeclaration() {
  MethodDeclarationContext *_localctx = _tracker.createInstance<MethodDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 74, OrcParser::RuleMethodDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(579);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::T__3:
      case OrcParser::T__54:
      case OrcParser::T__55:
      case OrcParser::T__56:
      case OrcParser::T__58:
      case OrcParser::T__59:
      case OrcParser::T__60:
      case OrcParser::T__61:
      case OrcParser::T__62:
      case OrcParser::T__63:
      case OrcParser::T__64:
      case OrcParser::T__65:
      case OrcParser::Void:
      case OrcParser::Struct:
      case OrcParser::Const:
      case OrcParser::Id: {
        enterOuterAlt(_localctx, 1);
        setState(577);
        functionDefinition();
        break;
      }

      case OrcParser::Extern: {
        enterOuterAlt(_localctx, 2);
        setState(578);
        externFunctionDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignRightPartContext ------------------------------------------------------------------

OrcParser::AssignRightPartContext::AssignRightPartContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::SingleExpressionContext* OrcParser::AssignRightPartContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}


size_t OrcParser::AssignRightPartContext::getRuleIndex() const {
  return OrcParser::RuleAssignRightPart;
}

void OrcParser::AssignRightPartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignRightPart(this);
}

void OrcParser::AssignRightPartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignRightPart(this);
}


std::any OrcParser::AssignRightPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitAssignRightPart(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::AssignRightPartContext* OrcParser::assignRightPart() {
  AssignRightPartContext *_localctx = _tracker.createInstance<AssignRightPartContext>(_ctx, getState());
  enterRule(_localctx, 76, OrcParser::RuleAssignRightPart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(581);
    match(OrcParser::T__36);
    setState(582);
    singleExpression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentDeclarationContext ------------------------------------------------------------------

OrcParser::ArgumentDeclarationContext::ArgumentDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::ArgumentDeclarationContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::ArgumentDeclarationContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::FunctionPointerVarDeclarationContext* OrcParser::ArgumentDeclarationContext::functionPointerVarDeclaration() {
  return getRuleContext<OrcParser::FunctionPointerVarDeclarationContext>(0);
}


size_t OrcParser::ArgumentDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleArgumentDeclaration;
}

void OrcParser::ArgumentDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentDeclaration(this);
}

void OrcParser::ArgumentDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentDeclaration(this);
}


std::any OrcParser::ArgumentDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitArgumentDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ArgumentDeclarationContext* OrcParser::argumentDeclaration() {
  ArgumentDeclarationContext *_localctx = _tracker.createInstance<ArgumentDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 78, OrcParser::RuleArgumentDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(589);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(584);
      type();
      setState(586);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Id) {
        setState(585);
        match(OrcParser::Id);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(588);
      functionPointerVarDeclaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsDeclarationContext ------------------------------------------------------------------

OrcParser::ArgumentsDeclarationContext::ArgumentsDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

std::vector<OrcParser::ArgumentDeclarationContext *> OrcParser::ArgumentsDeclarationContext::argumentDeclaration() {
  return getRuleContexts<OrcParser::ArgumentDeclarationContext>();
}

OrcParser::ArgumentDeclarationContext* OrcParser::ArgumentsDeclarationContext::argumentDeclaration(size_t i) {
  return getRuleContext<OrcParser::ArgumentDeclarationContext>(i);
}


size_t OrcParser::ArgumentsDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleArgumentsDeclaration;
}

void OrcParser::ArgumentsDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentsDeclaration(this);
}

void OrcParser::ArgumentsDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentsDeclaration(this);
}


std::any OrcParser::ArgumentsDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitArgumentsDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::argumentsDeclaration() {
  ArgumentsDeclarationContext *_localctx = _tracker.createInstance<ArgumentsDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 80, OrcParser::RuleArgumentsDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(607);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(591);
      match(OrcParser::T__0);
      setState(600);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & 4398181785607) != 0)) {
        setState(592);
        argumentDeclaration();
        setState(597);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(593);
            match(OrcParser::T__1);
            setState(594);
            argumentDeclaration(); 
          }
          setState(599);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
        }
      }
      setState(603);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__1) {
        setState(602);
        match(OrcParser::T__1);
      }
      setState(605);
      match(OrcParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);

      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionPointerVarDeclarationContext ------------------------------------------------------------------

OrcParser::FunctionPointerVarDeclarationContext::FunctionPointerVarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::FunctionPointerVarDeclarationContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::FunctionPointerVarDeclarationContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}

tree::TerminalNode* OrcParser::FunctionPointerVarDeclarationContext::Id() {
  return getToken(OrcParser::Id, 0);
}

std::vector<OrcParser::AttributeContext *> OrcParser::FunctionPointerVarDeclarationContext::attribute() {
  return getRuleContexts<OrcParser::AttributeContext>();
}

OrcParser::AttributeContext* OrcParser::FunctionPointerVarDeclarationContext::attribute(size_t i) {
  return getRuleContext<OrcParser::AttributeContext>(i);
}


size_t OrcParser::FunctionPointerVarDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleFunctionPointerVarDeclaration;
}

void OrcParser::FunctionPointerVarDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionPointerVarDeclaration(this);
}

void OrcParser::FunctionPointerVarDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionPointerVarDeclaration(this);
}


std::any OrcParser::FunctionPointerVarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitFunctionPointerVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::FunctionPointerVarDeclarationContext* OrcParser::functionPointerVarDeclaration() {
  FunctionPointerVarDeclarationContext *_localctx = _tracker.createInstance<FunctionPointerVarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 82, OrcParser::RuleFunctionPointerVarDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(609);
    type();
    setState(610);
    match(OrcParser::T__0);
    setState(612); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(611);
      match(OrcParser::T__12);
      setState(614); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == OrcParser::T__12);
    setState(617);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(616);
      match(OrcParser::Id);
    }
    setState(619);
    match(OrcParser::T__2);
    setState(620);
    argumentsDeclaration();
    setState(624);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(621);
        attribute(); 
      }
      setState(626);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

OrcParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::FunctionDefinitionContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::FunctionDefinitionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::FunctionDefinitionContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}

OrcParser::BlockContext* OrcParser::FunctionDefinitionContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}


size_t OrcParser::FunctionDefinitionContext::getRuleIndex() const {
  return OrcParser::RuleFunctionDefinition;
}

void OrcParser::FunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDefinition(this);
}

void OrcParser::FunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDefinition(this);
}


std::any OrcParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::FunctionDefinitionContext* OrcParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 84, OrcParser::RuleFunctionDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(627);
    type();
    setState(628);
    match(OrcParser::Id);
    setState(629);
    argumentsDeclaration();
    setState(630);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalFunctionDefinitionContext ------------------------------------------------------------------

OrcParser::GlobalFunctionDefinitionContext::GlobalFunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::FunctionDefinitionContext* OrcParser::GlobalFunctionDefinitionContext::functionDefinition() {
  return getRuleContext<OrcParser::FunctionDefinitionContext>(0);
}

tree::TerminalNode* OrcParser::GlobalFunctionDefinitionContext::Static() {
  return getToken(OrcParser::Static, 0);
}

OrcParser::ExternFunctionDeclarationContext* OrcParser::GlobalFunctionDefinitionContext::externFunctionDeclaration() {
  return getRuleContext<OrcParser::ExternFunctionDeclarationContext>(0);
}


size_t OrcParser::GlobalFunctionDefinitionContext::getRuleIndex() const {
  return OrcParser::RuleGlobalFunctionDefinition;
}

void OrcParser::GlobalFunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobalFunctionDefinition(this);
}

void OrcParser::GlobalFunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobalFunctionDefinition(this);
}


std::any OrcParser::GlobalFunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitGlobalFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::GlobalFunctionDefinitionContext* OrcParser::globalFunctionDefinition() {
  GlobalFunctionDefinitionContext *_localctx = _tracker.createInstance<GlobalFunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 86, OrcParser::RuleGlobalFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(640);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(633);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(632);
        match(OrcParser::Static);
      }
      setState(635);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(637);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(636);
        match(OrcParser::Static);
      }
      setState(639);
      externFunctionDeclaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalVarDeclarationContext ------------------------------------------------------------------

OrcParser::GlobalVarDeclarationContext::GlobalVarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::VarDeclarationContext* OrcParser::GlobalVarDeclarationContext::varDeclaration() {
  return getRuleContext<OrcParser::VarDeclarationContext>(0);
}

OrcParser::EosContext* OrcParser::GlobalVarDeclarationContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::GlobalVarDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleGlobalVarDeclaration;
}

void OrcParser::GlobalVarDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobalVarDeclaration(this);
}

void OrcParser::GlobalVarDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobalVarDeclaration(this);
}


std::any OrcParser::GlobalVarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitGlobalVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::GlobalVarDeclarationContext* OrcParser::globalVarDeclaration() {
  GlobalVarDeclarationContext *_localctx = _tracker.createInstance<GlobalVarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 88, OrcParser::RuleGlobalVarDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(642);
    varDeclaration();
    setState(643);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternFunctionDeclarationContext ------------------------------------------------------------------

OrcParser::ExternFunctionDeclarationContext::ExternFunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ExternFunctionDeclarationContext::Extern() {
  return getToken(OrcParser::Extern, 0);
}

OrcParser::TypeContext* OrcParser::ExternFunctionDeclarationContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::ExternFunctionDeclarationContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::ExternFunctionDeclarationContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}

OrcParser::EosContext* OrcParser::ExternFunctionDeclarationContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::ExternFunctionDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleExternFunctionDeclaration;
}

void OrcParser::ExternFunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternFunctionDeclaration(this);
}

void OrcParser::ExternFunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternFunctionDeclaration(this);
}


std::any OrcParser::ExternFunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitExternFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ExternFunctionDeclarationContext* OrcParser::externFunctionDeclaration() {
  ExternFunctionDeclarationContext *_localctx = _tracker.createInstance<ExternFunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 90, OrcParser::RuleExternFunctionDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(645);
    match(OrcParser::Extern);
    setState(646);
    type();
    setState(647);
    match(OrcParser::Id);
    setState(648);
    argumentsDeclaration();
    setState(649);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

OrcParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ImportStatementContext::Import() {
  return getToken(OrcParser::Import, 0);
}

tree::TerminalNode* OrcParser::ImportStatementContext::From() {
  return getToken(OrcParser::From, 0);
}

tree::TerminalNode* OrcParser::ImportStatementContext::StringLiteral() {
  return getToken(OrcParser::StringLiteral, 0);
}

OrcParser::EosContext* OrcParser::ImportStatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::ImportStatementContext::getRuleIndex() const {
  return OrcParser::RuleImportStatement;
}

void OrcParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void OrcParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}


std::any OrcParser::ImportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitImportStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ImportStatementContext* OrcParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 92, OrcParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(661);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::Import: {
        enterOuterAlt(_localctx, 1);
        setState(651);
        match(OrcParser::Import);
        setState(652);
        match(OrcParser::T__12);
        setState(653);
        match(OrcParser::From);
        setState(654);
        match(OrcParser::StringLiteral);
        setState(655);
        eos();
        break;
      }

      case OrcParser::T__66: {
        enterOuterAlt(_localctx, 2);
        setState(656);
        match(OrcParser::T__66);
        setState(657);
        match(OrcParser::T__12);
        setState(658);
        match(OrcParser::From);
        setState(659);
        match(OrcParser::StringLiteral);
        setState(660);
        eos();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IncludeStatementContext ------------------------------------------------------------------

OrcParser::IncludeStatementContext::IncludeStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::IncludePathCharactersContext* OrcParser::IncludeStatementContext::includePathCharacters() {
  return getRuleContext<OrcParser::IncludePathCharactersContext>(0);
}

OrcParser::EosContext* OrcParser::IncludeStatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::IncludeStatementContext::getRuleIndex() const {
  return OrcParser::RuleIncludeStatement;
}

void OrcParser::IncludeStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIncludeStatement(this);
}

void OrcParser::IncludeStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIncludeStatement(this);
}


std::any OrcParser::IncludeStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitIncludeStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::IncludeStatementContext* OrcParser::includeStatement() {
  IncludeStatementContext *_localctx = _tracker.createInstance<IncludeStatementContext>(_ctx, getState());
  enterRule(_localctx, 94, OrcParser::RuleIncludeStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(663);
    match(OrcParser::T__67);
    setState(664);
    includePathCharacters();
    setState(665);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IncludePathCharactersContext ------------------------------------------------------------------

OrcParser::IncludePathCharactersContext::IncludePathCharactersContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::IncludePathCharactersContext::StringLiteral() {
  return getToken(OrcParser::StringLiteral, 0);
}


size_t OrcParser::IncludePathCharactersContext::getRuleIndex() const {
  return OrcParser::RuleIncludePathCharacters;
}

void OrcParser::IncludePathCharactersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIncludePathCharacters(this);
}

void OrcParser::IncludePathCharactersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIncludePathCharacters(this);
}


std::any OrcParser::IncludePathCharactersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitIncludePathCharacters(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::IncludePathCharactersContext* OrcParser::includePathCharacters() {
  IncludePathCharactersContext *_localctx = _tracker.createInstance<IncludePathCharactersContext>(_ctx, getState());
  enterRule(_localctx, 96, OrcParser::RuleIncludePathCharacters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(676);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::T__23: {
        enterOuterAlt(_localctx, 1);
        setState(667);
        match(OrcParser::T__23);
        setState(671);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & -33554434) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & 281474976710655) != 0)) {
          setState(668);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == OrcParser::T__24)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(673);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(674);
        match(OrcParser::T__24);
        break;
      }

      case OrcParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(675);
        match(OrcParser::StringLiteral);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PackageStatementContext ------------------------------------------------------------------

OrcParser::PackageStatementContext::PackageStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::PackageStatementContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::EosContext* OrcParser::PackageStatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::PackageStatementContext::getRuleIndex() const {
  return OrcParser::RulePackageStatement;
}

void OrcParser::PackageStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPackageStatement(this);
}

void OrcParser::PackageStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPackageStatement(this);
}


std::any OrcParser::PackageStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitPackageStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::PackageStatementContext* OrcParser::packageStatement() {
  PackageStatementContext *_localctx = _tracker.createInstance<PackageStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, OrcParser::RulePackageStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(678);
    match(OrcParser::T__68);
    setState(679);
    match(OrcParser::Id);
    setState(680);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

OrcParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::LiteralContext::NullLiteral() {
  return getToken(OrcParser::NullLiteral, 0);
}

tree::TerminalNode* OrcParser::LiteralContext::BooleanLiteral() {
  return getToken(OrcParser::BooleanLiteral, 0);
}

tree::TerminalNode* OrcParser::LiteralContext::DecimalLiteral() {
  return getToken(OrcParser::DecimalLiteral, 0);
}

tree::TerminalNode* OrcParser::LiteralContext::HexIntegerLiteral() {
  return getToken(OrcParser::HexIntegerLiteral, 0);
}

tree::TerminalNode* OrcParser::LiteralContext::OctalIntegerLiteral() {
  return getToken(OrcParser::OctalIntegerLiteral, 0);
}

tree::TerminalNode* OrcParser::LiteralContext::BinaryIntegerLiteral() {
  return getToken(OrcParser::BinaryIntegerLiteral, 0);
}

tree::TerminalNode* OrcParser::LiteralContext::StringLiteral() {
  return getToken(OrcParser::StringLiteral, 0);
}

tree::TerminalNode* OrcParser::LiteralContext::CharLiteral() {
  return getToken(OrcParser::CharLiteral, 0);
}


size_t OrcParser::LiteralContext::getRuleIndex() const {
  return OrcParser::RuleLiteral;
}

void OrcParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void OrcParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any OrcParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::LiteralContext* OrcParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 100, OrcParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(682);
    _la = _input->LA(1);
    if (!(((((_la - 98) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 98)) & 255) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EosContext ------------------------------------------------------------------

OrcParser::EosContext::EosContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::EosContext::EOF() {
  return getToken(OrcParser::EOF, 0);
}


size_t OrcParser::EosContext::getRuleIndex() const {
  return OrcParser::RuleEos;
}

void OrcParser::EosContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEos(this);
}

void OrcParser::EosContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEos(this);
}


std::any OrcParser::EosContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitEos(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::EosContext* OrcParser::eos() {
  EosContext *_localctx = _tracker.createInstance<EosContext>(_ctx, getState());
  enterRule(_localctx, 102, OrcParser::RuleEos);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(688);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(684);
      match(OrcParser::T__50);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(685);
      match(OrcParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(686);

      if (!(this->lineTerminatorAhead())) throw FailedPredicateException(this, "this->lineTerminatorAhead()");
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(687);

      if (!(this->closeBrace())) throw FailedPredicateException(this, "this->closeBrace()");
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool OrcParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 5: return singleExpressionSempred(antlrcpp::downCast<SingleExpressionContext *>(context), predicateIndex);
    case 51: return eosSempred(antlrcpp::downCast<EosContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool OrcParser::singleExpressionSempred(SingleExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 21);
    case 1: return precpred(_ctx, 20);
    case 2: return precpred(_ctx, 19);
    case 3: return precpred(_ctx, 18);
    case 4: return precpred(_ctx, 17);
    case 5: return precpred(_ctx, 16);
    case 6: return precpred(_ctx, 15);
    case 7: return precpred(_ctx, 14);
    case 8: return precpred(_ctx, 13);
    case 9: return precpred(_ctx, 12);
    case 10: return precpred(_ctx, 11);
    case 11: return precpred(_ctx, 10);
    case 12: return precpred(_ctx, 9);
    case 13: return precpred(_ctx, 7);
    case 14: return precpred(_ctx, 6);
    case 15: return precpred(_ctx, 36);
    case 16: return precpred(_ctx, 35);
    case 17: return precpred(_ctx, 34);
    case 18: return precpred(_ctx, 32);
    case 19: return precpred(_ctx, 31);

  default:
    break;
  }
  return true;
}

bool OrcParser::eosSempred(EosContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 20: return this->lineTerminatorAhead();
    case 21: return this->closeBrace();

  default:
    break;
  }
  return true;
}

void OrcParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  orcParserInitialize();
#else
  ::antlr4::internal::call_once(orcParserOnceFlag, orcParserInitialize);
#endif
}
