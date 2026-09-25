
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
      "continueStatement", "breakStatement", "throwStatement", "returnStatement", 
      "scopeStatement", "iterationStatement", "forCondition", "forInit", 
      "forVarDeclaration", "forVarInitDeclarator", "selectionStatement", 
      "tryStatement", "catchClause", "finallyClause", "block", "type", "closureType", 
      "functionTypeArg", "attribute", "functionType", "typeQualifier", "pointer", 
      "ref", "primitiveType", "enumDefinition", "enumItem", "extensionDefinition", 
      "extensionBlock", "classDefinition", "classDefinitionBlock", "classFieldDeclaration", 
      "methodDeclaration", "assignRightPart", "argumentDeclaration", "argumentsDeclaration", 
      "functionPointerVarDeclaration", "functionDefinition", "genericFunctionDefinition", 
      "genericExternFunctionDeclaration", "genericParameterList", "genericTypeUsage", 
      "globalFunctionDefinition", "globalVarDeclaration", "externFunctionDeclaration", 
      "importStatement", "includeStatement", "includePathCharacters", "packageStatement", 
      "literal", "eos"
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
      "'break'", "'do'", "'instanceof'", "'case'", "'else'", "'new'", "'catch'", 
      "'finally'", "'return'", "'void'", "'continue'", "'for'", "'while'", 
      "'self'", "'if'", "'throw'", "'try'", "'from'", "'struct'", "'class'", 
      "'enum'", "'extends'", "'extern'", "'super'", "'extension'", "'const'", 
      "'export'", "'import'", "'static'", "'async'", "'await'", "'refc'", 
      "", "", "", "", "", "", "", "", "", "'}'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "Break", "Do", "Instanceof", "Case", "Else", "New", "Catch", 
      "Finally", "Return", "Void", "Continue", "For", "While", "This", "If", 
      "Throw", "Try", "From", "Struct", "Class", "Enum", "Extends", "Extern", 
      "Super", "Extension", "Const", "Export", "Import", "Static", "Async", 
      "Await", "Refc", "NullLiteral", "BooleanLiteral", "DecimalLiteral", 
      "HexIntegerLiteral", "OctalIntegerLiteral", "BinaryIntegerLiteral", 
      "StringLiteral", "CharLiteral", "Id", "CloseBrace", "LineTerminator", 
      "Whitespace", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,115,800,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,1,0,5,
  	0,128,8,0,10,0,12,0,131,9,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,
  	1,143,8,1,1,2,1,2,1,2,1,2,5,2,149,8,2,10,2,12,2,152,9,2,1,2,3,2,155,8,
  	2,3,2,157,8,2,1,2,1,2,1,3,1,3,1,3,5,3,164,8,3,10,3,12,3,167,9,3,1,4,1,
  	4,1,4,3,4,172,8,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,211,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,3,5,276,8,5,1,5,5,5,279,8,5,10,5,12,5,282,9,5,1,6,1,6,1,7,1,
  	7,1,8,1,8,1,8,1,8,5,8,292,8,8,10,8,12,8,295,9,8,1,8,1,8,1,9,1,9,1,9,3,
  	9,302,8,9,1,9,1,9,1,9,1,9,1,9,3,9,309,8,9,1,10,1,10,1,10,1,10,1,11,3,
  	11,316,8,11,1,11,1,11,1,11,3,11,321,8,11,1,11,1,11,3,11,325,8,11,1,11,
  	3,11,328,8,11,1,11,3,11,331,8,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,352,8,
  	12,1,13,1,13,1,13,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,3,16,366,
  	8,16,1,16,1,16,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,388,8,18,1,19,3,19,391,8,19,1,
  	19,1,19,3,19,395,8,19,1,19,1,19,3,19,399,8,19,1,20,1,20,3,20,403,8,20,
  	1,21,1,21,1,21,1,21,5,21,409,8,21,10,21,12,21,412,9,21,1,22,1,22,3,22,
  	416,8,22,1,22,1,22,3,22,420,8,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,5,
  	23,429,8,23,10,23,12,23,432,9,23,1,23,1,23,3,23,436,8,23,1,24,1,24,1,
  	24,4,24,441,8,24,11,24,12,24,442,1,24,3,24,446,8,24,1,24,1,24,1,24,1,
  	24,3,24,452,8,24,1,25,1,25,1,25,1,25,3,25,458,8,25,1,25,1,25,1,25,1,26,
  	1,26,1,26,1,27,1,27,5,27,468,8,27,10,27,12,27,471,9,27,1,27,1,27,1,28,
  	3,28,476,8,28,1,28,1,28,3,28,480,8,28,1,28,1,28,1,28,1,28,3,28,486,8,
  	28,1,28,3,28,489,8,28,1,28,1,28,3,28,493,8,28,1,29,1,29,1,29,1,29,1,30,
  	1,30,3,30,501,8,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,
  	5,32,513,8,32,10,32,12,32,516,9,32,1,33,1,33,1,34,3,34,521,8,34,1,34,
  	1,34,3,34,525,8,34,1,34,1,34,3,34,529,8,34,1,34,5,34,532,8,34,10,34,12,
  	34,535,9,34,1,34,1,34,5,34,539,8,34,10,34,12,34,542,9,34,4,34,544,8,34,
  	11,34,12,34,545,1,35,3,35,549,8,35,1,35,1,35,3,35,553,8,35,1,35,1,35,
  	1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,
  	1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,580,8,36,1,37,1,37,
  	1,37,1,37,1,37,1,37,5,37,588,8,37,10,37,12,37,591,9,37,1,37,3,37,594,
  	8,37,1,37,1,37,1,37,1,38,1,38,1,38,3,38,602,8,38,1,39,1,39,1,39,1,39,
  	1,40,1,40,5,40,610,8,40,10,40,12,40,613,9,40,1,40,1,40,1,41,1,41,3,41,
  	619,8,41,1,41,1,41,1,41,3,41,624,8,41,1,41,1,41,1,41,1,42,1,42,1,42,5,
  	42,632,8,42,10,42,12,42,635,9,42,1,42,1,42,1,43,1,43,1,43,3,43,642,8,
  	43,1,43,3,43,645,8,43,1,43,1,43,1,43,1,43,3,43,651,8,43,1,43,1,43,3,43,
  	655,8,43,1,44,1,44,3,44,659,8,44,1,45,1,45,1,45,1,46,1,46,3,46,666,8,
  	46,1,46,3,46,669,8,46,1,47,1,47,1,47,1,47,5,47,675,8,47,10,47,12,47,678,
  	9,47,3,47,680,8,47,1,47,3,47,683,8,47,1,47,1,47,3,47,687,8,47,1,48,1,
  	48,1,48,4,48,692,8,48,11,48,12,48,693,1,48,3,48,697,8,48,1,48,1,48,1,
  	48,5,48,702,8,48,10,48,12,48,705,9,48,1,49,1,49,1,49,1,49,1,49,1,50,1,
  	50,1,50,1,50,1,50,1,50,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,52,1,52,1,
  	52,1,52,1,53,1,53,1,53,1,53,1,53,1,54,3,54,735,8,54,1,54,1,54,3,54,739,
  	8,54,1,54,1,54,3,54,743,8,54,1,54,1,54,3,54,747,8,54,1,54,3,54,750,8,
  	54,1,55,1,55,1,55,1,56,1,56,1,56,1,56,1,56,1,56,1,57,1,57,1,57,1,57,1,
  	57,1,57,1,57,1,57,1,57,1,57,3,57,771,8,57,1,58,1,58,1,58,1,58,1,59,1,
  	59,5,59,779,8,59,10,59,12,59,782,9,59,1,59,1,59,3,59,786,8,59,1,60,1,
  	60,1,60,1,60,1,61,1,61,1,62,1,62,1,62,1,62,3,62,798,8,62,1,62,0,1,10,
  	63,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,
  	48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,
  	94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,0,11,2,0,
  	13,13,18,19,1,0,14,15,1,0,21,23,1,0,24,27,1,0,28,31,1,0,9,10,1,0,38,50,
  	2,0,9,9,16,16,2,0,55,57,95,95,1,0,25,25,1,0,102,109,893,0,129,1,0,0,0,
  	2,142,1,0,0,0,4,144,1,0,0,0,6,160,1,0,0,0,8,168,1,0,0,0,10,210,1,0,0,
  	0,12,283,1,0,0,0,14,285,1,0,0,0,16,287,1,0,0,0,18,308,1,0,0,0,20,310,
  	1,0,0,0,22,330,1,0,0,0,24,351,1,0,0,0,26,353,1,0,0,0,28,356,1,0,0,0,30,
  	359,1,0,0,0,32,363,1,0,0,0,34,369,1,0,0,0,36,387,1,0,0,0,38,390,1,0,0,
  	0,40,402,1,0,0,0,42,404,1,0,0,0,44,413,1,0,0,0,46,421,1,0,0,0,48,451,
  	1,0,0,0,50,453,1,0,0,0,52,462,1,0,0,0,54,465,1,0,0,0,56,492,1,0,0,0,58,
  	494,1,0,0,0,60,498,1,0,0,0,62,502,1,0,0,0,64,509,1,0,0,0,66,517,1,0,0,
  	0,68,520,1,0,0,0,70,552,1,0,0,0,72,579,1,0,0,0,74,581,1,0,0,0,76,598,
  	1,0,0,0,78,603,1,0,0,0,80,607,1,0,0,0,82,616,1,0,0,0,84,628,1,0,0,0,86,
  	654,1,0,0,0,88,658,1,0,0,0,90,660,1,0,0,0,92,668,1,0,0,0,94,686,1,0,0,
  	0,96,688,1,0,0,0,98,706,1,0,0,0,100,711,1,0,0,0,102,717,1,0,0,0,104,724,
  	1,0,0,0,106,728,1,0,0,0,108,749,1,0,0,0,110,751,1,0,0,0,112,754,1,0,0,
  	0,114,770,1,0,0,0,116,772,1,0,0,0,118,785,1,0,0,0,120,787,1,0,0,0,122,
  	791,1,0,0,0,124,797,1,0,0,0,126,128,3,2,1,0,127,126,1,0,0,0,128,131,1,
  	0,0,0,129,127,1,0,0,0,129,130,1,0,0,0,130,1,1,0,0,0,131,129,1,0,0,0,132,
  	143,3,120,60,0,133,143,3,116,58,0,134,143,3,114,57,0,135,143,3,16,8,0,
  	136,143,3,74,37,0,137,143,3,82,41,0,138,143,3,78,39,0,139,143,3,110,55,
  	0,140,143,3,108,54,0,141,143,3,14,7,0,142,132,1,0,0,0,142,133,1,0,0,0,
  	142,134,1,0,0,0,142,135,1,0,0,0,142,136,1,0,0,0,142,137,1,0,0,0,142,138,
  	1,0,0,0,142,139,1,0,0,0,142,140,1,0,0,0,142,141,1,0,0,0,143,3,1,0,0,0,
  	144,156,5,1,0,0,145,150,3,10,5,0,146,147,5,2,0,0,147,149,3,10,5,0,148,
  	146,1,0,0,0,149,152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,154,1,
  	0,0,0,152,150,1,0,0,0,153,155,5,2,0,0,154,153,1,0,0,0,154,155,1,0,0,0,
  	155,157,1,0,0,0,156,145,1,0,0,0,156,157,1,0,0,0,157,158,1,0,0,0,158,159,
  	5,3,0,0,159,5,1,0,0,0,160,165,3,10,5,0,161,162,5,2,0,0,162,164,3,10,5,
  	0,163,161,1,0,0,0,164,167,1,0,0,0,165,163,1,0,0,0,165,166,1,0,0,0,166,
  	7,1,0,0,0,167,165,1,0,0,0,168,169,5,4,0,0,169,171,3,56,28,0,170,172,5,
  	110,0,0,171,170,1,0,0,0,171,172,1,0,0,0,172,173,1,0,0,0,173,174,3,94,
  	47,0,174,175,3,54,27,0,175,9,1,0,0,0,176,177,6,5,-1,0,177,211,3,8,4,0,
  	178,179,5,75,0,0,179,180,5,110,0,0,180,211,3,4,2,0,181,182,5,12,0,0,182,
  	211,3,10,5,29,183,184,5,13,0,0,184,211,3,10,5,28,185,186,5,5,0,0,186,
  	211,3,10,5,27,187,188,5,6,0,0,188,211,3,10,5,26,189,190,5,14,0,0,190,
  	211,3,10,5,25,191,192,5,15,0,0,192,211,3,10,5,24,193,194,5,16,0,0,194,
  	211,3,10,5,23,195,196,5,17,0,0,196,211,3,10,5,22,197,198,5,1,0,0,198,
  	199,3,56,28,0,199,200,5,3,0,0,200,201,3,10,5,8,201,211,1,0,0,0,202,211,
  	5,83,0,0,203,211,5,110,0,0,204,211,5,93,0,0,205,211,3,122,61,0,206,207,
  	5,1,0,0,207,208,3,6,3,0,208,209,5,3,0,0,209,211,1,0,0,0,210,176,1,0,0,
  	0,210,178,1,0,0,0,210,181,1,0,0,0,210,183,1,0,0,0,210,185,1,0,0,0,210,
  	187,1,0,0,0,210,189,1,0,0,0,210,191,1,0,0,0,210,193,1,0,0,0,210,195,1,
  	0,0,0,210,197,1,0,0,0,210,202,1,0,0,0,210,203,1,0,0,0,210,204,1,0,0,0,
  	210,205,1,0,0,0,210,206,1,0,0,0,211,280,1,0,0,0,212,213,10,21,0,0,213,
  	214,7,0,0,0,214,279,3,10,5,22,215,216,10,20,0,0,216,217,7,1,0,0,217,279,
  	3,10,5,21,218,219,10,19,0,0,219,220,5,20,0,0,220,279,3,10,5,20,221,222,
  	10,18,0,0,222,223,7,2,0,0,223,279,3,10,5,19,224,225,10,17,0,0,225,226,
  	7,3,0,0,226,279,3,10,5,18,227,228,10,16,0,0,228,229,5,72,0,0,229,279,
  	3,10,5,17,230,231,10,15,0,0,231,232,7,4,0,0,232,279,3,10,5,16,233,234,
  	10,14,0,0,234,235,5,12,0,0,235,279,3,10,5,15,236,237,10,13,0,0,237,238,
  	5,4,0,0,238,279,3,10,5,14,239,240,10,12,0,0,240,241,5,32,0,0,241,279,
  	3,10,5,13,242,243,10,11,0,0,243,244,5,33,0,0,244,279,3,10,5,12,245,246,
  	10,10,0,0,246,247,5,34,0,0,247,279,3,10,5,11,248,249,10,9,0,0,249,250,
  	5,35,0,0,250,251,3,10,5,0,251,252,5,36,0,0,252,253,3,10,5,10,253,279,
  	1,0,0,0,254,255,10,7,0,0,255,256,5,37,0,0,256,279,3,10,5,7,257,258,10,
  	6,0,0,258,259,3,12,6,0,259,260,3,10,5,6,260,279,1,0,0,0,261,262,10,36,
  	0,0,262,279,3,4,2,0,263,264,10,35,0,0,264,279,5,5,0,0,265,266,10,34,0,
  	0,266,279,5,6,0,0,267,268,10,32,0,0,268,269,5,7,0,0,269,270,3,10,5,0,
  	270,271,5,8,0,0,271,279,1,0,0,0,272,273,10,31,0,0,273,275,7,5,0,0,274,
  	276,5,11,0,0,275,274,1,0,0,0,275,276,1,0,0,0,276,277,1,0,0,0,277,279,
  	5,110,0,0,278,212,1,0,0,0,278,215,1,0,0,0,278,218,1,0,0,0,278,221,1,0,
  	0,0,278,224,1,0,0,0,278,227,1,0,0,0,278,230,1,0,0,0,278,233,1,0,0,0,278,
  	236,1,0,0,0,278,239,1,0,0,0,278,242,1,0,0,0,278,245,1,0,0,0,278,248,1,
  	0,0,0,278,254,1,0,0,0,278,257,1,0,0,0,278,261,1,0,0,0,278,263,1,0,0,0,
  	278,265,1,0,0,0,278,267,1,0,0,0,278,272,1,0,0,0,279,282,1,0,0,0,280,278,
  	1,0,0,0,280,281,1,0,0,0,281,11,1,0,0,0,282,280,1,0,0,0,283,284,7,6,0,
  	0,284,13,1,0,0,0,285,286,5,51,0,0,286,15,1,0,0,0,287,288,5,88,0,0,288,
  	289,5,110,0,0,289,293,5,52,0,0,290,292,3,18,9,0,291,290,1,0,0,0,292,295,
  	1,0,0,0,293,291,1,0,0,0,293,294,1,0,0,0,294,296,1,0,0,0,295,293,1,0,0,
  	0,296,297,5,111,0,0,297,17,1,0,0,0,298,299,3,56,28,0,299,301,5,110,0,
  	0,300,302,3,20,10,0,301,300,1,0,0,0,301,302,1,0,0,0,302,303,1,0,0,0,303,
  	304,3,124,62,0,304,309,1,0,0,0,305,306,3,96,48,0,306,307,3,124,62,0,307,
  	309,1,0,0,0,308,298,1,0,0,0,308,305,1,0,0,0,309,19,1,0,0,0,310,311,5,
  	7,0,0,311,312,5,104,0,0,312,313,5,8,0,0,313,21,1,0,0,0,314,316,5,98,0,
  	0,315,314,1,0,0,0,315,316,1,0,0,0,316,317,1,0,0,0,317,318,3,56,28,0,318,
  	320,5,110,0,0,319,321,3,20,10,0,320,319,1,0,0,0,320,321,1,0,0,0,321,324,
  	1,0,0,0,322,323,5,37,0,0,323,325,3,10,5,0,324,322,1,0,0,0,324,325,1,0,
  	0,0,325,331,1,0,0,0,326,328,5,98,0,0,327,326,1,0,0,0,327,328,1,0,0,0,
  	328,329,1,0,0,0,329,331,3,96,48,0,330,315,1,0,0,0,330,327,1,0,0,0,331,
  	23,1,0,0,0,332,333,3,8,4,0,333,334,3,124,62,0,334,352,1,0,0,0,335,336,
  	3,22,11,0,336,337,3,124,62,0,337,352,1,0,0,0,338,352,3,34,17,0,339,352,
  	3,54,27,0,340,352,3,26,13,0,341,352,3,28,14,0,342,352,3,30,15,0,343,352,
  	3,46,23,0,344,352,3,32,16,0,345,352,3,36,18,0,346,352,3,48,24,0,347,348,
  	3,10,5,0,348,349,3,124,62,0,349,352,1,0,0,0,350,352,3,14,7,0,351,332,
  	1,0,0,0,351,335,1,0,0,0,351,338,1,0,0,0,351,339,1,0,0,0,351,340,1,0,0,
  	0,351,341,1,0,0,0,351,342,1,0,0,0,351,343,1,0,0,0,351,344,1,0,0,0,351,
  	345,1,0,0,0,351,346,1,0,0,0,351,347,1,0,0,0,351,350,1,0,0,0,352,25,1,
  	0,0,0,353,354,5,80,0,0,354,355,3,124,62,0,355,27,1,0,0,0,356,357,5,70,
  	0,0,357,358,3,124,62,0,358,29,1,0,0,0,359,360,5,85,0,0,360,361,3,10,5,
  	0,361,362,3,124,62,0,362,31,1,0,0,0,363,365,5,78,0,0,364,366,3,10,5,0,
  	365,364,1,0,0,0,365,366,1,0,0,0,366,367,1,0,0,0,367,368,3,124,62,0,368,
  	33,1,0,0,0,369,370,3,10,5,0,370,371,7,7,0,0,371,372,3,54,27,0,372,35,
  	1,0,0,0,373,374,5,82,0,0,374,375,3,10,5,0,375,376,3,54,27,0,376,388,1,
  	0,0,0,377,378,5,81,0,0,378,379,5,1,0,0,379,380,3,38,19,0,380,381,5,3,
  	0,0,381,382,3,54,27,0,382,388,1,0,0,0,383,384,5,81,0,0,384,385,3,38,19,
  	0,385,386,3,54,27,0,386,388,1,0,0,0,387,373,1,0,0,0,387,377,1,0,0,0,387,
  	383,1,0,0,0,388,37,1,0,0,0,389,391,3,40,20,0,390,389,1,0,0,0,390,391,
  	1,0,0,0,391,392,1,0,0,0,392,394,5,51,0,0,393,395,3,6,3,0,394,393,1,0,
  	0,0,394,395,1,0,0,0,395,396,1,0,0,0,396,398,5,51,0,0,397,399,3,6,3,0,
  	398,397,1,0,0,0,398,399,1,0,0,0,399,39,1,0,0,0,400,403,3,42,21,0,401,
  	403,3,6,3,0,402,400,1,0,0,0,402,401,1,0,0,0,403,41,1,0,0,0,404,405,3,
  	56,28,0,405,410,3,44,22,0,406,407,5,2,0,0,407,409,3,44,22,0,408,406,1,
  	0,0,0,409,412,1,0,0,0,410,408,1,0,0,0,410,411,1,0,0,0,411,43,1,0,0,0,
  	412,410,1,0,0,0,413,415,5,110,0,0,414,416,3,20,10,0,415,414,1,0,0,0,415,
  	416,1,0,0,0,416,419,1,0,0,0,417,418,5,37,0,0,418,420,3,10,5,0,419,417,
  	1,0,0,0,419,420,1,0,0,0,420,45,1,0,0,0,421,422,5,84,0,0,422,423,3,10,
  	5,0,423,430,3,54,27,0,424,425,5,53,0,0,425,426,3,10,5,0,426,427,3,54,
  	27,0,427,429,1,0,0,0,428,424,1,0,0,0,429,432,1,0,0,0,430,428,1,0,0,0,
  	430,431,1,0,0,0,431,435,1,0,0,0,432,430,1,0,0,0,433,434,5,74,0,0,434,
  	436,3,54,27,0,435,433,1,0,0,0,435,436,1,0,0,0,436,47,1,0,0,0,437,438,
  	5,86,0,0,438,440,3,54,27,0,439,441,3,50,25,0,440,439,1,0,0,0,441,442,
  	1,0,0,0,442,440,1,0,0,0,442,443,1,0,0,0,443,445,1,0,0,0,444,446,3,52,
  	26,0,445,444,1,0,0,0,445,446,1,0,0,0,446,452,1,0,0,0,447,448,5,86,0,0,
  	448,449,3,54,27,0,449,450,3,52,26,0,450,452,1,0,0,0,451,437,1,0,0,0,451,
  	447,1,0,0,0,452,49,1,0,0,0,453,454,5,76,0,0,454,455,5,1,0,0,455,457,3,
  	70,35,0,456,458,5,110,0,0,457,456,1,0,0,0,457,458,1,0,0,0,458,459,1,0,
  	0,0,459,460,5,3,0,0,460,461,3,54,27,0,461,51,1,0,0,0,462,463,5,77,0,0,
  	463,464,3,54,27,0,464,53,1,0,0,0,465,469,5,52,0,0,466,468,3,24,12,0,467,
  	466,1,0,0,0,468,471,1,0,0,0,469,467,1,0,0,0,469,470,1,0,0,0,470,472,1,
  	0,0,0,471,469,1,0,0,0,472,473,5,111,0,0,473,55,1,0,0,0,474,476,3,66,33,
  	0,475,474,1,0,0,0,475,476,1,0,0,0,476,477,1,0,0,0,477,479,3,72,36,0,478,
  	480,3,20,10,0,479,478,1,0,0,0,479,480,1,0,0,0,480,493,1,0,0,0,481,493,
  	3,58,29,0,482,493,3,68,34,0,483,493,3,70,35,0,484,486,3,66,33,0,485,484,
  	1,0,0,0,485,486,1,0,0,0,486,488,1,0,0,0,487,489,5,88,0,0,488,487,1,0,
  	0,0,488,489,1,0,0,0,489,490,1,0,0,0,490,493,5,110,0,0,491,493,3,106,53,
  	0,492,475,1,0,0,0,492,481,1,0,0,0,492,482,1,0,0,0,492,483,1,0,0,0,492,
  	485,1,0,0,0,492,491,1,0,0,0,493,57,1,0,0,0,494,495,5,4,0,0,495,496,3,
  	56,28,0,496,497,3,94,47,0,497,59,1,0,0,0,498,500,3,56,28,0,499,501,5,
  	110,0,0,500,499,1,0,0,0,500,501,1,0,0,0,501,61,1,0,0,0,502,503,5,54,0,
  	0,503,504,5,1,0,0,504,505,5,1,0,0,505,506,5,110,0,0,506,507,5,3,0,0,507,
  	508,5,3,0,0,508,63,1,0,0,0,509,510,3,56,28,0,510,514,3,94,47,0,511,513,
  	3,62,31,0,512,511,1,0,0,0,513,516,1,0,0,0,514,512,1,0,0,0,514,515,1,0,
  	0,0,515,65,1,0,0,0,516,514,1,0,0,0,517,518,7,8,0,0,518,67,1,0,0,0,519,
  	521,3,66,33,0,520,519,1,0,0,0,520,521,1,0,0,0,521,528,1,0,0,0,522,529,
  	3,72,36,0,523,525,5,88,0,0,524,523,1,0,0,0,524,525,1,0,0,0,525,526,1,
  	0,0,0,526,529,5,110,0,0,527,529,3,106,53,0,528,522,1,0,0,0,528,524,1,
  	0,0,0,528,527,1,0,0,0,529,543,1,0,0,0,530,532,3,66,33,0,531,530,1,0,0,
  	0,532,535,1,0,0,0,533,531,1,0,0,0,533,534,1,0,0,0,534,536,1,0,0,0,535,
  	533,1,0,0,0,536,540,5,13,0,0,537,539,3,66,33,0,538,537,1,0,0,0,539,542,
  	1,0,0,0,540,538,1,0,0,0,540,541,1,0,0,0,541,544,1,0,0,0,542,540,1,0,0,
  	0,543,533,1,0,0,0,544,545,1,0,0,0,545,543,1,0,0,0,545,546,1,0,0,0,546,
  	69,1,0,0,0,547,549,5,88,0,0,548,547,1,0,0,0,548,549,1,0,0,0,549,550,1,
  	0,0,0,550,553,5,110,0,0,551,553,3,106,53,0,552,548,1,0,0,0,552,551,1,
  	0,0,0,553,554,1,0,0,0,554,555,5,58,0,0,555,71,1,0,0,0,556,580,5,59,0,
  	0,557,580,5,60,0,0,558,580,5,61,0,0,559,580,5,62,0,0,560,580,5,63,0,0,
  	561,580,5,64,0,0,562,580,5,79,0,0,563,580,5,65,0,0,564,565,5,65,0,0,565,
  	580,5,65,0,0,566,567,5,65,0,0,567,580,5,62,0,0,568,569,5,66,0,0,569,580,
  	5,63,0,0,570,571,5,66,0,0,571,580,5,59,0,0,572,573,5,66,0,0,573,580,5,
  	60,0,0,574,575,5,66,0,0,575,580,5,65,0,0,576,577,5,66,0,0,577,578,5,65,
  	0,0,578,580,5,65,0,0,579,556,1,0,0,0,579,557,1,0,0,0,579,558,1,0,0,0,
  	579,559,1,0,0,0,579,560,1,0,0,0,579,561,1,0,0,0,579,562,1,0,0,0,579,563,
  	1,0,0,0,579,564,1,0,0,0,579,566,1,0,0,0,579,568,1,0,0,0,579,570,1,0,0,
  	0,579,572,1,0,0,0,579,574,1,0,0,0,579,576,1,0,0,0,580,73,1,0,0,0,581,
  	582,5,90,0,0,582,583,5,110,0,0,583,584,5,52,0,0,584,589,3,76,38,0,585,
  	586,5,2,0,0,586,588,3,76,38,0,587,585,1,0,0,0,588,591,1,0,0,0,589,587,
  	1,0,0,0,589,590,1,0,0,0,590,593,1,0,0,0,591,589,1,0,0,0,592,594,5,2,0,
  	0,593,592,1,0,0,0,593,594,1,0,0,0,594,595,1,0,0,0,595,596,5,111,0,0,596,
  	597,3,124,62,0,597,75,1,0,0,0,598,601,5,110,0,0,599,600,5,37,0,0,600,
  	602,5,104,0,0,601,599,1,0,0,0,601,602,1,0,0,0,602,77,1,0,0,0,603,604,
  	5,94,0,0,604,605,5,110,0,0,605,606,3,80,40,0,606,79,1,0,0,0,607,611,5,
  	52,0,0,608,610,3,88,44,0,609,608,1,0,0,0,610,613,1,0,0,0,611,609,1,0,
  	0,0,611,612,1,0,0,0,612,614,1,0,0,0,613,611,1,0,0,0,614,615,5,111,0,0,
  	615,81,1,0,0,0,616,618,5,89,0,0,617,619,5,101,0,0,618,617,1,0,0,0,618,
  	619,1,0,0,0,619,620,1,0,0,0,620,623,5,110,0,0,621,622,5,91,0,0,622,624,
  	5,110,0,0,623,621,1,0,0,0,623,624,1,0,0,0,624,625,1,0,0,0,625,626,3,84,
  	42,0,626,627,3,124,62,0,627,83,1,0,0,0,628,633,5,52,0,0,629,632,3,86,
  	43,0,630,632,3,88,44,0,631,629,1,0,0,0,631,630,1,0,0,0,632,635,1,0,0,
  	0,633,631,1,0,0,0,633,634,1,0,0,0,634,636,1,0,0,0,635,633,1,0,0,0,636,
  	637,5,111,0,0,637,85,1,0,0,0,638,639,3,56,28,0,639,641,5,110,0,0,640,
  	642,3,20,10,0,641,640,1,0,0,0,641,642,1,0,0,0,642,644,1,0,0,0,643,645,
  	3,90,45,0,644,643,1,0,0,0,644,645,1,0,0,0,645,646,1,0,0,0,646,647,3,124,
  	62,0,647,655,1,0,0,0,648,650,3,96,48,0,649,651,3,90,45,0,650,649,1,0,
  	0,0,650,651,1,0,0,0,651,652,1,0,0,0,652,653,3,124,62,0,653,655,1,0,0,
  	0,654,638,1,0,0,0,654,648,1,0,0,0,655,87,1,0,0,0,656,659,3,98,49,0,657,
  	659,3,112,56,0,658,656,1,0,0,0,658,657,1,0,0,0,659,89,1,0,0,0,660,661,
  	5,37,0,0,661,662,3,10,5,0,662,91,1,0,0,0,663,665,3,56,28,0,664,666,5,
  	110,0,0,665,664,1,0,0,0,665,666,1,0,0,0,666,669,1,0,0,0,667,669,3,96,
  	48,0,668,663,1,0,0,0,668,667,1,0,0,0,669,93,1,0,0,0,670,679,5,1,0,0,671,
  	676,3,92,46,0,672,673,5,2,0,0,673,675,3,92,46,0,674,672,1,0,0,0,675,678,
  	1,0,0,0,676,674,1,0,0,0,676,677,1,0,0,0,677,680,1,0,0,0,678,676,1,0,0,
  	0,679,671,1,0,0,0,679,680,1,0,0,0,680,682,1,0,0,0,681,683,5,2,0,0,682,
  	681,1,0,0,0,682,683,1,0,0,0,683,684,1,0,0,0,684,687,5,3,0,0,685,687,1,
  	0,0,0,686,670,1,0,0,0,686,685,1,0,0,0,687,95,1,0,0,0,688,689,3,56,28,
  	0,689,691,5,1,0,0,690,692,5,13,0,0,691,690,1,0,0,0,692,693,1,0,0,0,693,
  	691,1,0,0,0,693,694,1,0,0,0,694,696,1,0,0,0,695,697,5,110,0,0,696,695,
  	1,0,0,0,696,697,1,0,0,0,697,698,1,0,0,0,698,699,5,3,0,0,699,703,3,94,
  	47,0,700,702,3,62,31,0,701,700,1,0,0,0,702,705,1,0,0,0,703,701,1,0,0,
  	0,703,704,1,0,0,0,704,97,1,0,0,0,705,703,1,0,0,0,706,707,3,56,28,0,707,
  	708,5,110,0,0,708,709,3,94,47,0,709,710,3,54,27,0,710,99,1,0,0,0,711,
  	712,3,56,28,0,712,713,5,110,0,0,713,714,3,104,52,0,714,715,3,94,47,0,
  	715,716,3,54,27,0,716,101,1,0,0,0,717,718,5,92,0,0,718,719,3,56,28,0,
  	719,720,5,110,0,0,720,721,3,104,52,0,721,722,3,94,47,0,722,723,3,124,
  	62,0,723,103,1,0,0,0,724,725,5,24,0,0,725,726,5,110,0,0,726,727,5,25,
  	0,0,727,105,1,0,0,0,728,729,5,110,0,0,729,730,5,24,0,0,730,731,5,110,
  	0,0,731,732,5,25,0,0,732,107,1,0,0,0,733,735,5,98,0,0,734,733,1,0,0,0,
  	734,735,1,0,0,0,735,736,1,0,0,0,736,750,3,98,49,0,737,739,5,98,0,0,738,
  	737,1,0,0,0,738,739,1,0,0,0,739,740,1,0,0,0,740,750,3,112,56,0,741,743,
  	5,98,0,0,742,741,1,0,0,0,742,743,1,0,0,0,743,744,1,0,0,0,744,750,3,100,
  	50,0,745,747,5,98,0,0,746,745,1,0,0,0,746,747,1,0,0,0,747,748,1,0,0,0,
  	748,750,3,102,51,0,749,734,1,0,0,0,749,738,1,0,0,0,749,742,1,0,0,0,749,
  	746,1,0,0,0,750,109,1,0,0,0,751,752,3,22,11,0,752,753,3,124,62,0,753,
  	111,1,0,0,0,754,755,5,92,0,0,755,756,3,56,28,0,756,757,5,110,0,0,757,
  	758,3,94,47,0,758,759,3,124,62,0,759,113,1,0,0,0,760,761,5,97,0,0,761,
  	762,5,13,0,0,762,763,5,87,0,0,763,764,5,108,0,0,764,771,3,124,62,0,765,
  	766,5,67,0,0,766,767,5,13,0,0,767,768,5,87,0,0,768,769,5,108,0,0,769,
  	771,3,124,62,0,770,760,1,0,0,0,770,765,1,0,0,0,771,115,1,0,0,0,772,773,
  	5,68,0,0,773,774,3,118,59,0,774,775,3,124,62,0,775,117,1,0,0,0,776,780,
  	5,24,0,0,777,779,8,9,0,0,778,777,1,0,0,0,779,782,1,0,0,0,780,778,1,0,
  	0,0,780,781,1,0,0,0,781,783,1,0,0,0,782,780,1,0,0,0,783,786,5,25,0,0,
  	784,786,5,108,0,0,785,776,1,0,0,0,785,784,1,0,0,0,786,119,1,0,0,0,787,
  	788,5,69,0,0,788,789,5,110,0,0,789,790,3,124,62,0,790,121,1,0,0,0,791,
  	792,7,10,0,0,792,123,1,0,0,0,793,798,5,51,0,0,794,798,5,0,0,1,795,798,
  	4,62,20,0,796,798,4,62,21,0,797,793,1,0,0,0,797,794,1,0,0,0,797,795,1,
  	0,0,0,797,796,1,0,0,0,798,125,1,0,0,0,83,129,142,150,154,156,165,171,
  	210,275,278,280,293,301,308,315,320,324,327,330,351,365,387,390,394,398,
  	402,410,415,419,430,435,442,445,451,457,469,475,479,485,488,492,500,514,
  	520,524,528,533,540,545,548,552,579,589,593,601,611,618,623,631,633,641,
  	644,650,654,658,665,668,676,679,682,686,693,696,703,734,738,742,746,749,
  	770,780,785,797
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
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -322007373356990448) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70398121115711) != 0)) {
      setState(126);
      rootDeclaration();
      setState(131);
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
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(132);
      packageStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(133);
      includeStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(134);
      importStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(135);
      structDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(136);
      enumDefinition();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(137);
      classDefinition();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(138);
      extensionDefinition();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(139);
      globalVarDeclaration();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(140);
      globalFunctionDefinition();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(141);
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
    setState(144);
    match(OrcParser::T__0);
    setState(156);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 68585521409) != 0)) {
      setState(145);
      singleExpression(0);
      setState(150);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(146);
          match(OrcParser::T__1);
          setState(147);
          singleExpression(0); 
        }
        setState(152);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      }
      setState(154);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__1) {
        setState(153);
        match(OrcParser::T__1);
      }
    }
    setState(158);
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
    setState(160);
    singleExpression(0);
    setState(165);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__1) {
      setState(161);
      match(OrcParser::T__1);
      setState(162);
      singleExpression(0);
      setState(167);
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
    setState(168);
    match(OrcParser::T__3);
    setState(169);
    type();
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(170);
      match(OrcParser::Id);
    }
    setState(173);
    argumentsDeclaration();
    setState(174);
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
    setState(210);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<LabelClosureExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(177);
      closureExpression();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NewExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(178);
      match(OrcParser::New);
      setState(179);
      match(OrcParser::Id);
      setState(180);
      arguments();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<GetAddressExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(181);
      match(OrcParser::T__11);
      setState(182);
      singleExpression(29);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<DerefExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(183);
      match(OrcParser::T__12);
      setState(184);
      singleExpression(28);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PreIncrementExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(185);
      match(OrcParser::T__4);
      setState(186);
      singleExpression(27);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PreDecreaseExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(187);
      match(OrcParser::T__5);
      setState(188);
      singleExpression(26);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<UnaryPlusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(189);
      match(OrcParser::T__13);
      setState(190);
      singleExpression(25);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<UnaryMinusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(191);
      match(OrcParser::T__14);
      setState(192);
      singleExpression(24);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BitNotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(193);
      match(OrcParser::T__15);
      setState(194);
      singleExpression(23);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<NotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(195);
      match(OrcParser::T__16);
      setState(196);
      singleExpression(22);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<CastExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(197);
      match(OrcParser::T__0);
      setState(198);
      type();
      setState(199);
      match(OrcParser::T__2);
      setState(200);
      singleExpression(8);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<ThisExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(202);
      match(OrcParser::This);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<IdentifierExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(203);
      match(OrcParser::Id);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<SuperExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(204);
      match(OrcParser::Super);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(205);
      literal();
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<ParenthesizedExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(206);
      match(OrcParser::T__0);
      setState(207);
      expressionSequence();
      setState(208);
      match(OrcParser::T__2);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(280);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(278);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MultiplicativeExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(212);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(213);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 794624) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(214);
          singleExpression(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AdditiveExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(215);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(216);
          _la = _input->LA(1);
          if (!(_la == OrcParser::T__13

          || _la == OrcParser::T__14)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(217);
          singleExpression(21);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CoalesceExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(218);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(219);
          match(OrcParser::T__19);
          setState(220);
          singleExpression(20);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BitShiftExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(221);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(222);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 14680064) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(223);
          singleExpression(19);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<RelationalExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(224);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(225);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 251658240) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(226);
          singleExpression(18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<InstanceofExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(227);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(228);
          match(OrcParser::Instanceof);
          setState(229);
          singleExpression(17);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<EqualityExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(230);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(231);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4026531840) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(232);
          singleExpression(16);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BitAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(233);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(234);
          match(OrcParser::T__11);
          setState(235);
          singleExpression(15);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BitXOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(236);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(237);
          match(OrcParser::T__3);
          setState(238);
          singleExpression(14);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BitOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(239);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(240);
          match(OrcParser::T__31);
          setState(241);
          singleExpression(13);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<LogicalAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(242);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(243);
          match(OrcParser::T__32);
          setState(244);
          singleExpression(12);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<LogicalOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(245);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(246);
          match(OrcParser::T__33);
          setState(247);
          singleExpression(11);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<TernaryExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(248);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(249);
          match(OrcParser::T__34);
          setState(250);
          singleExpression(0);
          setState(251);
          match(OrcParser::T__35);
          setState(252);
          singleExpression(10);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<AssignmentExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(254);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(255);
          match(OrcParser::T__36);
          setState(256);
          singleExpression(7);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<AssignmentOperatorExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(257);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(258);
          assignmentOperator();
          setState(259);
          singleExpression(6);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<CallExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(261);

          if (!(precpred(_ctx, 36))) throw FailedPredicateException(this, "precpred(_ctx, 36)");
          setState(262);
          arguments();
          break;
        }

        case 17: {
          auto newContext = _tracker.createInstance<PostIncrementExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(263);

          if (!(precpred(_ctx, 35))) throw FailedPredicateException(this, "precpred(_ctx, 35)");
          setState(264);
          match(OrcParser::T__4);
          break;
        }

        case 18: {
          auto newContext = _tracker.createInstance<PostDecreaseExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(265);

          if (!(precpred(_ctx, 34))) throw FailedPredicateException(this, "precpred(_ctx, 34)");
          setState(266);
          match(OrcParser::T__5);
          break;
        }

        case 19: {
          auto newContext = _tracker.createInstance<MemberIndexExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(267);

          if (!(precpred(_ctx, 32))) throw FailedPredicateException(this, "precpred(_ctx, 32)");
          setState(268);
          match(OrcParser::T__6);
          setState(269);
          singleExpression(0);
          setState(270);
          match(OrcParser::T__7);
          break;
        }

        case 20: {
          auto newContext = _tracker.createInstance<MemberDotExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(272);

          if (!(precpred(_ctx, 31))) throw FailedPredicateException(this, "precpred(_ctx, 31)");
          setState(273);
          _la = _input->LA(1);
          if (!(_la == OrcParser::T__8

          || _la == OrcParser::T__9)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(275);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == OrcParser::T__10) {
            setState(274);
            match(OrcParser::T__10);
          }
          setState(277);
          match(OrcParser::Id);
          break;
        }

        default:
          break;
        } 
      }
      setState(282);
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
    setState(283);
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
    setState(285);
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
    setState(287);
    match(OrcParser::Struct);
    setState(288);
    match(OrcParser::Id);
    setState(289);
    match(OrcParser::T__51);
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70370908471303) != 0)) {
      setState(290);
      structMember();
      setState(295);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(296);
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
    setState(308);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(298);
      type();
      setState(299);
      match(OrcParser::Id);
      setState(301);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
      case 1: {
        setState(300);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(303);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(305);
      functionPointerVarDeclaration();
      setState(306);
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
    setState(310);
    match(OrcParser::T__6);
    setState(311);
    match(OrcParser::DecimalLiteral);
    setState(312);
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
    setState(330);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(315);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(314);
        match(OrcParser::Static);
      }
      setState(317);
      type();
      setState(318);
      match(OrcParser::Id);
      setState(320);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(319);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(324);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(322);
        match(OrcParser::T__36);
        setState(323);
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
      setState(327);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(326);
        match(OrcParser::Static);
      }
      setState(329);
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

OrcParser::ThrowStatementContext* OrcParser::StatementContext::throwStatement() {
  return getRuleContext<OrcParser::ThrowStatementContext>(0);
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

OrcParser::TryStatementContext* OrcParser::StatementContext::tryStatement() {
  return getRuleContext<OrcParser::TryStatementContext>(0);
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
    setState(351);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(332);
      closureExpression();
      setState(333);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(335);
      varDeclaration();
      setState(336);
      eos();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(338);
      scopeStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(339);
      block();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(340);
      continueStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(341);
      breakStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(342);
      throwStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(343);
      selectionStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(344);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(345);
      iterationStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(346);
      tryStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(347);
      singleExpression(0);
      setState(348);
      eos();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(350);
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
    setState(353);
    match(OrcParser::Continue);
    setState(354);
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
    setState(356);
    match(OrcParser::Break);
    setState(357);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThrowStatementContext ------------------------------------------------------------------

OrcParser::ThrowStatementContext::ThrowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ThrowStatementContext::Throw() {
  return getToken(OrcParser::Throw, 0);
}

OrcParser::SingleExpressionContext* OrcParser::ThrowStatementContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}

OrcParser::EosContext* OrcParser::ThrowStatementContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::ThrowStatementContext::getRuleIndex() const {
  return OrcParser::RuleThrowStatement;
}

void OrcParser::ThrowStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThrowStatement(this);
}

void OrcParser::ThrowStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThrowStatement(this);
}


std::any OrcParser::ThrowStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitThrowStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ThrowStatementContext* OrcParser::throwStatement() {
  ThrowStatementContext *_localctx = _tracker.createInstance<ThrowStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, OrcParser::RuleThrowStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(359);
    match(OrcParser::Throw);
    setState(360);
    singleExpression(0);
    setState(361);
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
  enterRule(_localctx, 32, OrcParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(363);
    match(OrcParser::Return);
    setState(365);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(364);
      singleExpression(0);
      break;
    }

    default:
      break;
    }
    setState(367);
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
  enterRule(_localctx, 34, OrcParser::RuleScopeStatement);
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
    setState(369);
    singleExpression(0);
    setState(370);
    _la = _input->LA(1);
    if (!(_la == OrcParser::T__8

    || _la == OrcParser::T__15)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(371);
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
  enterRule(_localctx, 36, OrcParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(387);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(373);
      match(OrcParser::While);
      setState(374);
      singleExpression(0);
      setState(375);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(377);
      match(OrcParser::For);
      setState(378);
      match(OrcParser::T__0);
      setState(379);
      forCondition();
      setState(380);
      match(OrcParser::T__2);
      setState(381);
      block();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(383);
      match(OrcParser::For);
      setState(384);
      forCondition();
      setState(385);
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

OrcParser::ForInitContext* OrcParser::ForConditionContext::forInit() {
  return getRuleContext<OrcParser::ForInitContext>(0);
}

std::vector<OrcParser::ExpressionSequenceContext *> OrcParser::ForConditionContext::expressionSequence() {
  return getRuleContexts<OrcParser::ExpressionSequenceContext>();
}

OrcParser::ExpressionSequenceContext* OrcParser::ForConditionContext::expressionSequence(size_t i) {
  return getRuleContext<OrcParser::ExpressionSequenceContext>(i);
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
  enterRule(_localctx, 38, OrcParser::RuleForCondition);
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
    setState(390);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170417550) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 140465312139271) != 0)) {
      setState(389);
      forInit();
    }
    setState(392);
    match(OrcParser::T__50);
    setState(394);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 68585521409) != 0)) {
      setState(393);
      expressionSequence();
    }
    setState(396);
    match(OrcParser::T__50);
    setState(398);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 68585521409) != 0)) {
      setState(397);
      expressionSequence();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForInitContext ------------------------------------------------------------------

OrcParser::ForInitContext::ForInitContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::ForVarDeclarationContext* OrcParser::ForInitContext::forVarDeclaration() {
  return getRuleContext<OrcParser::ForVarDeclarationContext>(0);
}

OrcParser::ExpressionSequenceContext* OrcParser::ForInitContext::expressionSequence() {
  return getRuleContext<OrcParser::ExpressionSequenceContext>(0);
}


size_t OrcParser::ForInitContext::getRuleIndex() const {
  return OrcParser::RuleForInit;
}

void OrcParser::ForInitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForInit(this);
}

void OrcParser::ForInitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForInit(this);
}


std::any OrcParser::ForInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitForInit(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ForInitContext* OrcParser::forInit() {
  ForInitContext *_localctx = _tracker.createInstance<ForInitContext>(_ctx, getState());
  enterRule(_localctx, 40, OrcParser::RuleForInit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(402);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(400);
      forVarDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(401);
      expressionSequence();
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

//----------------- ForVarDeclarationContext ------------------------------------------------------------------

OrcParser::ForVarDeclarationContext::ForVarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::ForVarDeclarationContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

std::vector<OrcParser::ForVarInitDeclaratorContext *> OrcParser::ForVarDeclarationContext::forVarInitDeclarator() {
  return getRuleContexts<OrcParser::ForVarInitDeclaratorContext>();
}

OrcParser::ForVarInitDeclaratorContext* OrcParser::ForVarDeclarationContext::forVarInitDeclarator(size_t i) {
  return getRuleContext<OrcParser::ForVarInitDeclaratorContext>(i);
}


size_t OrcParser::ForVarDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleForVarDeclaration;
}

void OrcParser::ForVarDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForVarDeclaration(this);
}

void OrcParser::ForVarDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForVarDeclaration(this);
}


std::any OrcParser::ForVarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitForVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ForVarDeclarationContext* OrcParser::forVarDeclaration() {
  ForVarDeclarationContext *_localctx = _tracker.createInstance<ForVarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 42, OrcParser::RuleForVarDeclaration);
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
    setState(404);
    type();
    setState(405);
    forVarInitDeclarator();
    setState(410);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__1) {
      setState(406);
      match(OrcParser::T__1);
      setState(407);
      forVarInitDeclarator();
      setState(412);
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

//----------------- ForVarInitDeclaratorContext ------------------------------------------------------------------

OrcParser::ForVarInitDeclaratorContext::ForVarInitDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::ForVarInitDeclaratorContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::ArraySizeDeclarationContext* OrcParser::ForVarInitDeclaratorContext::arraySizeDeclaration() {
  return getRuleContext<OrcParser::ArraySizeDeclarationContext>(0);
}

OrcParser::SingleExpressionContext* OrcParser::ForVarInitDeclaratorContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
}


size_t OrcParser::ForVarInitDeclaratorContext::getRuleIndex() const {
  return OrcParser::RuleForVarInitDeclarator;
}

void OrcParser::ForVarInitDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForVarInitDeclarator(this);
}

void OrcParser::ForVarInitDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForVarInitDeclarator(this);
}


std::any OrcParser::ForVarInitDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitForVarInitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::ForVarInitDeclaratorContext* OrcParser::forVarInitDeclarator() {
  ForVarInitDeclaratorContext *_localctx = _tracker.createInstance<ForVarInitDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 44, OrcParser::RuleForVarInitDeclarator);
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
    setState(413);
    match(OrcParser::Id);
    setState(415);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__6) {
      setState(414);
      arraySizeDeclaration();
    }
    setState(419);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__36) {
      setState(417);
      match(OrcParser::T__36);
      setState(418);
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
  enterRule(_localctx, 46, OrcParser::RuleSelectionStatement);
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
    setState(421);
    match(OrcParser::If);
    setState(422);
    singleExpression(0);
    setState(423);
    block();
    setState(430);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__52) {
      setState(424);
      match(OrcParser::T__52);
      setState(425);
      singleExpression(0);
      setState(426);
      block();
      setState(432);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(435);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Else) {
      setState(433);
      match(OrcParser::Else);
      setState(434);
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

//----------------- TryStatementContext ------------------------------------------------------------------

OrcParser::TryStatementContext::TryStatementContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::TryStatementContext::Try() {
  return getToken(OrcParser::Try, 0);
}

OrcParser::BlockContext* OrcParser::TryStatementContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}

std::vector<OrcParser::CatchClauseContext *> OrcParser::TryStatementContext::catchClause() {
  return getRuleContexts<OrcParser::CatchClauseContext>();
}

OrcParser::CatchClauseContext* OrcParser::TryStatementContext::catchClause(size_t i) {
  return getRuleContext<OrcParser::CatchClauseContext>(i);
}

OrcParser::FinallyClauseContext* OrcParser::TryStatementContext::finallyClause() {
  return getRuleContext<OrcParser::FinallyClauseContext>(0);
}


size_t OrcParser::TryStatementContext::getRuleIndex() const {
  return OrcParser::RuleTryStatement;
}

void OrcParser::TryStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTryStatement(this);
}

void OrcParser::TryStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTryStatement(this);
}


std::any OrcParser::TryStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitTryStatement(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::TryStatementContext* OrcParser::tryStatement() {
  TryStatementContext *_localctx = _tracker.createInstance<TryStatementContext>(_ctx, getState());
  enterRule(_localctx, 48, OrcParser::RuleTryStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(451);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(437);
      match(OrcParser::Try);
      setState(438);
      block();
      setState(440); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(439);
        catchClause();
        setState(442); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == OrcParser::Catch);
      setState(445);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Finally) {
        setState(444);
        finallyClause();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(447);
      match(OrcParser::Try);
      setState(448);
      block();
      setState(449);
      finallyClause();
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

//----------------- CatchClauseContext ------------------------------------------------------------------

OrcParser::CatchClauseContext::CatchClauseContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::CatchClauseContext::Catch() {
  return getToken(OrcParser::Catch, 0);
}

OrcParser::RefContext* OrcParser::CatchClauseContext::ref() {
  return getRuleContext<OrcParser::RefContext>(0);
}

OrcParser::BlockContext* OrcParser::CatchClauseContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}

tree::TerminalNode* OrcParser::CatchClauseContext::Id() {
  return getToken(OrcParser::Id, 0);
}


size_t OrcParser::CatchClauseContext::getRuleIndex() const {
  return OrcParser::RuleCatchClause;
}

void OrcParser::CatchClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCatchClause(this);
}

void OrcParser::CatchClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCatchClause(this);
}


std::any OrcParser::CatchClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitCatchClause(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::CatchClauseContext* OrcParser::catchClause() {
  CatchClauseContext *_localctx = _tracker.createInstance<CatchClauseContext>(_ctx, getState());
  enterRule(_localctx, 50, OrcParser::RuleCatchClause);
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
    setState(453);
    match(OrcParser::Catch);
    setState(454);
    match(OrcParser::T__0);
    setState(455);
    ref();
    setState(457);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(456);
      match(OrcParser::Id);
    }
    setState(459);
    match(OrcParser::T__2);
    setState(460);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FinallyClauseContext ------------------------------------------------------------------

OrcParser::FinallyClauseContext::FinallyClauseContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::FinallyClauseContext::Finally() {
  return getToken(OrcParser::Finally, 0);
}

OrcParser::BlockContext* OrcParser::FinallyClauseContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}


size_t OrcParser::FinallyClauseContext::getRuleIndex() const {
  return OrcParser::RuleFinallyClause;
}

void OrcParser::FinallyClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFinallyClause(this);
}

void OrcParser::FinallyClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFinallyClause(this);
}


std::any OrcParser::FinallyClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitFinallyClause(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::FinallyClauseContext* OrcParser::finallyClause() {
  FinallyClauseContext *_localctx = _tracker.createInstance<FinallyClauseContext>(_ctx, getState());
  enterRule(_localctx, 52, OrcParser::RuleFinallyClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(462);
    match(OrcParser::Finally);
    setState(463);
    block();
   
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
  enterRule(_localctx, 54, OrcParser::RuleBlock);
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
    setState(465);
    match(OrcParser::T__51);
    setState(469);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -317503773729361806) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 140482499823687) != 0)) {
      setState(466);
      statement();
      setState(471);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(472);
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

OrcParser::GenericTypeUsageContext* OrcParser::TypeContext::genericTypeUsage() {
  return getRuleContext<OrcParser::GenericTypeUsageContext>(0);
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
  enterRule(_localctx, 56, OrcParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(492);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(475);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
        setState(474);
        typeQualifier();
      }
      setState(477);
      primitiveType();
      setState(479);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__6) {
        setState(478);
        arraySizeDeclaration();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(481);
      closureType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(482);
      pointer();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(483);
      ref();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(485);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
        setState(484);
        typeQualifier();
      }
      setState(488);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Struct) {
        setState(487);
        match(OrcParser::Struct);
      }
      setState(490);
      match(OrcParser::Id);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(491);
      genericTypeUsage();
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
  enterRule(_localctx, 58, OrcParser::RuleClosureType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(494);
    match(OrcParser::T__3);
    setState(495);
    type();
    setState(496);
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
  enterRule(_localctx, 60, OrcParser::RuleFunctionTypeArg);
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
    setState(498);
    type();
    setState(500);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(499);
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
  enterRule(_localctx, 62, OrcParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(502);
    match(OrcParser::T__53);
    setState(503);
    match(OrcParser::T__0);
    setState(504);
    match(OrcParser::T__0);
    setState(505);
    match(OrcParser::Id);
    setState(506);
    match(OrcParser::T__2);
    setState(507);
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
  enterRule(_localctx, 64, OrcParser::RuleFunctionType);
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
    setState(509);
    type();
    setState(510);
    argumentsDeclaration();
    setState(514);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__53) {
      setState(511);
      attribute();
      setState(516);
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
  enterRule(_localctx, 66, OrcParser::RuleTypeQualifier);
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
    setState(517);
    _la = _input->LA(1);
    if (!(((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & 1099511627783) != 0))) {
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

OrcParser::GenericTypeUsageContext* OrcParser::PointerContext::genericTypeUsage() {
  return getRuleContext<OrcParser::GenericTypeUsageContext>(0);
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
  enterRule(_localctx, 68, OrcParser::RulePointer);
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
    setState(520);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
      setState(519);
      typeQualifier();
    }
    setState(528);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(522);
      primitiveType();
      break;
    }

    case 2: {
      setState(524);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Struct) {
        setState(523);
        match(OrcParser::Struct);
      }
      setState(526);
      match(OrcParser::Id);
      break;
    }

    case 3: {
      setState(527);
      genericTypeUsage();
      break;
    }

    default:
      break;
    }
    setState(543); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(533);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
        setState(530);
        typeQualifier();
        setState(535);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(536);
      match(OrcParser::T__12);
      setState(540);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(537);
          typeQualifier(); 
        }
        setState(542);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      }
      setState(545); 
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

OrcParser::GenericTypeUsageContext* OrcParser::RefContext::genericTypeUsage() {
  return getRuleContext<OrcParser::GenericTypeUsageContext>(0);
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
  enterRule(_localctx, 70, OrcParser::RuleRef);
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
    setState(552);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      setState(548);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Struct) {
        setState(547);
        match(OrcParser::Struct);
      }
      setState(550);
      match(OrcParser::Id);
      break;
    }

    case 2: {
      setState(551);
      genericTypeUsage();
      break;
    }

    default:
      break;
    }
    setState(554);
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
  enterRule(_localctx, 72, OrcParser::RulePrimitiveType);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(556);
      match(OrcParser::T__58);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(557);
      match(OrcParser::T__59);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(558);
      match(OrcParser::T__60);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(559);
      match(OrcParser::T__61);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(560);
      match(OrcParser::T__62);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(561);
      match(OrcParser::T__63);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(562);
      match(OrcParser::Void);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(563);
      match(OrcParser::T__64);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(564);
      match(OrcParser::T__64);
      setState(565);
      match(OrcParser::T__64);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(566);
      match(OrcParser::T__64);
      setState(567);
      match(OrcParser::T__61);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(568);
      match(OrcParser::T__65);
      setState(569);
      match(OrcParser::T__62);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(570);
      match(OrcParser::T__65);
      setState(571);
      match(OrcParser::T__58);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(572);
      match(OrcParser::T__65);
      setState(573);
      match(OrcParser::T__59);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(574);
      match(OrcParser::T__65);
      setState(575);
      match(OrcParser::T__64);
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(576);
      match(OrcParser::T__65);
      setState(577);
      match(OrcParser::T__64);
      setState(578);
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
  enterRule(_localctx, 74, OrcParser::RuleEnumDefinition);
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
    setState(581);
    match(OrcParser::Enum);
    setState(582);
    match(OrcParser::Id);
    setState(583);
    match(OrcParser::T__51);
    setState(584);
    enumItem();
    setState(589);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(585);
        match(OrcParser::T__1);
        setState(586);
        enumItem(); 
      }
      setState(591);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    }
    setState(593);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__1) {
      setState(592);
      match(OrcParser::T__1);
    }
    setState(595);
    match(OrcParser::CloseBrace);
    setState(596);
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
  enterRule(_localctx, 76, OrcParser::RuleEnumItem);
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
    setState(598);
    match(OrcParser::Id);
    setState(601);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__36) {
      setState(599);
      match(OrcParser::T__36);
      setState(600);
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
  enterRule(_localctx, 78, OrcParser::RuleExtensionDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(603);
    match(OrcParser::Extension);
    setState(604);
    match(OrcParser::Id);
    setState(605);
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
  enterRule(_localctx, 80, OrcParser::RuleExtensionBlock);
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
    setState(607);
    match(OrcParser::T__51);
    setState(611);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70371176906759) != 0)) {
      setState(608);
      methodDeclaration();
      setState(613);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(614);
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
  enterRule(_localctx, 82, OrcParser::RuleClassDefinition);
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
    setState(616);
    match(OrcParser::Class);
    setState(618);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Refc) {
      setState(617);
      match(OrcParser::Refc);
    }
    setState(620);
    match(OrcParser::Id);
    setState(623);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Extends) {
      setState(621);
      match(OrcParser::Extends);
      setState(622);
      match(OrcParser::Id);
    }
    setState(625);
    classDefinitionBlock();
    setState(626);
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
  enterRule(_localctx, 84, OrcParser::RuleClassDefinitionBlock);
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
    setState(628);
    match(OrcParser::T__51);
    setState(633);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70371176906759) != 0)) {
      setState(631);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
      case 1: {
        setState(629);
        classFieldDeclaration();
        break;
      }

      case 2: {
        setState(630);
        methodDeclaration();
        break;
      }

      default:
        break;
      }
      setState(635);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(636);
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
  enterRule(_localctx, 86, OrcParser::RuleClassFieldDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(654);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(638);
      type();
      setState(639);
      match(OrcParser::Id);
      setState(641);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
      case 1: {
        setState(640);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(644);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
      case 1: {
        setState(643);
        assignRightPart();
        break;
      }

      default:
        break;
      }
      setState(646);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(648);
      functionPointerVarDeclaration();
      setState(650);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
      case 1: {
        setState(649);
        assignRightPart();
        break;
      }

      default:
        break;
      }
      setState(652);
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
  enterRule(_localctx, 88, OrcParser::RuleMethodDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(658);
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
        setState(656);
        functionDefinition();
        break;
      }

      case OrcParser::Extern: {
        enterOuterAlt(_localctx, 2);
        setState(657);
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
  enterRule(_localctx, 90, OrcParser::RuleAssignRightPart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(660);
    match(OrcParser::T__36);
    setState(661);
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
  enterRule(_localctx, 92, OrcParser::RuleArgumentDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(668);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(663);
      type();
      setState(665);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Id) {
        setState(664);
        match(OrcParser::Id);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(667);
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
  enterRule(_localctx, 94, OrcParser::RuleArgumentsDeclaration);
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
    setState(686);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(670);
      match(OrcParser::T__0);
      setState(679);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & 70370908471303) != 0)) {
        setState(671);
        argumentDeclaration();
        setState(676);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(672);
            match(OrcParser::T__1);
            setState(673);
            argumentDeclaration(); 
          }
          setState(678);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
        }
      }
      setState(682);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__1) {
        setState(681);
        match(OrcParser::T__1);
      }
      setState(684);
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
  enterRule(_localctx, 96, OrcParser::RuleFunctionPointerVarDeclaration);
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
    setState(688);
    type();
    setState(689);
    match(OrcParser::T__0);
    setState(691); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(690);
      match(OrcParser::T__12);
      setState(693); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == OrcParser::T__12);
    setState(696);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(695);
      match(OrcParser::Id);
    }
    setState(698);
    match(OrcParser::T__2);
    setState(699);
    argumentsDeclaration();
    setState(703);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(700);
        attribute(); 
      }
      setState(705);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
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
  enterRule(_localctx, 98, OrcParser::RuleFunctionDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(706);
    type();
    setState(707);
    match(OrcParser::Id);
    setState(708);
    argumentsDeclaration();
    setState(709);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericFunctionDefinitionContext ------------------------------------------------------------------

OrcParser::GenericFunctionDefinitionContext::GenericFunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::TypeContext* OrcParser::GenericFunctionDefinitionContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::GenericFunctionDefinitionContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::GenericParameterListContext* OrcParser::GenericFunctionDefinitionContext::genericParameterList() {
  return getRuleContext<OrcParser::GenericParameterListContext>(0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::GenericFunctionDefinitionContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}

OrcParser::BlockContext* OrcParser::GenericFunctionDefinitionContext::block() {
  return getRuleContext<OrcParser::BlockContext>(0);
}


size_t OrcParser::GenericFunctionDefinitionContext::getRuleIndex() const {
  return OrcParser::RuleGenericFunctionDefinition;
}

void OrcParser::GenericFunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericFunctionDefinition(this);
}

void OrcParser::GenericFunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericFunctionDefinition(this);
}


std::any OrcParser::GenericFunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitGenericFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::GenericFunctionDefinitionContext* OrcParser::genericFunctionDefinition() {
  GenericFunctionDefinitionContext *_localctx = _tracker.createInstance<GenericFunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 100, OrcParser::RuleGenericFunctionDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(711);
    type();
    setState(712);
    match(OrcParser::Id);
    setState(713);
    genericParameterList();
    setState(714);
    argumentsDeclaration();
    setState(715);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericExternFunctionDeclarationContext ------------------------------------------------------------------

OrcParser::GenericExternFunctionDeclarationContext::GenericExternFunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::GenericExternFunctionDeclarationContext::Extern() {
  return getToken(OrcParser::Extern, 0);
}

OrcParser::TypeContext* OrcParser::GenericExternFunctionDeclarationContext::type() {
  return getRuleContext<OrcParser::TypeContext>(0);
}

tree::TerminalNode* OrcParser::GenericExternFunctionDeclarationContext::Id() {
  return getToken(OrcParser::Id, 0);
}

OrcParser::GenericParameterListContext* OrcParser::GenericExternFunctionDeclarationContext::genericParameterList() {
  return getRuleContext<OrcParser::GenericParameterListContext>(0);
}

OrcParser::ArgumentsDeclarationContext* OrcParser::GenericExternFunctionDeclarationContext::argumentsDeclaration() {
  return getRuleContext<OrcParser::ArgumentsDeclarationContext>(0);
}

OrcParser::EosContext* OrcParser::GenericExternFunctionDeclarationContext::eos() {
  return getRuleContext<OrcParser::EosContext>(0);
}


size_t OrcParser::GenericExternFunctionDeclarationContext::getRuleIndex() const {
  return OrcParser::RuleGenericExternFunctionDeclaration;
}

void OrcParser::GenericExternFunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericExternFunctionDeclaration(this);
}

void OrcParser::GenericExternFunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericExternFunctionDeclaration(this);
}


std::any OrcParser::GenericExternFunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitGenericExternFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::GenericExternFunctionDeclarationContext* OrcParser::genericExternFunctionDeclaration() {
  GenericExternFunctionDeclarationContext *_localctx = _tracker.createInstance<GenericExternFunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 102, OrcParser::RuleGenericExternFunctionDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(717);
    match(OrcParser::Extern);
    setState(718);
    type();
    setState(719);
    match(OrcParser::Id);
    setState(720);
    genericParameterList();
    setState(721);
    argumentsDeclaration();
    setState(722);
    eos();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericParameterListContext ------------------------------------------------------------------

OrcParser::GenericParameterListContext::GenericParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

tree::TerminalNode* OrcParser::GenericParameterListContext::Id() {
  return getToken(OrcParser::Id, 0);
}


size_t OrcParser::GenericParameterListContext::getRuleIndex() const {
  return OrcParser::RuleGenericParameterList;
}

void OrcParser::GenericParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericParameterList(this);
}

void OrcParser::GenericParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericParameterList(this);
}


std::any OrcParser::GenericParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitGenericParameterList(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::GenericParameterListContext* OrcParser::genericParameterList() {
  GenericParameterListContext *_localctx = _tracker.createInstance<GenericParameterListContext>(_ctx, getState());
  enterRule(_localctx, 104, OrcParser::RuleGenericParameterList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(724);
    match(OrcParser::T__23);
    setState(725);
    match(OrcParser::Id);
    setState(726);
    match(OrcParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericTypeUsageContext ------------------------------------------------------------------

OrcParser::GenericTypeUsageContext::GenericTypeUsageContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> OrcParser::GenericTypeUsageContext::Id() {
  return getTokens(OrcParser::Id);
}

tree::TerminalNode* OrcParser::GenericTypeUsageContext::Id(size_t i) {
  return getToken(OrcParser::Id, i);
}


size_t OrcParser::GenericTypeUsageContext::getRuleIndex() const {
  return OrcParser::RuleGenericTypeUsage;
}

void OrcParser::GenericTypeUsageContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericTypeUsage(this);
}

void OrcParser::GenericTypeUsageContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<OrcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericTypeUsage(this);
}


std::any OrcParser::GenericTypeUsageContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<OrcVisitor*>(visitor))
    return parserVisitor->visitGenericTypeUsage(this);
  else
    return visitor->visitChildren(this);
}

OrcParser::GenericTypeUsageContext* OrcParser::genericTypeUsage() {
  GenericTypeUsageContext *_localctx = _tracker.createInstance<GenericTypeUsageContext>(_ctx, getState());
  enterRule(_localctx, 106, OrcParser::RuleGenericTypeUsage);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(728);
    match(OrcParser::Id);
    setState(729);
    match(OrcParser::T__23);
    setState(730);
    match(OrcParser::Id);
    setState(731);
    match(OrcParser::T__24);
   
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

OrcParser::GenericFunctionDefinitionContext* OrcParser::GlobalFunctionDefinitionContext::genericFunctionDefinition() {
  return getRuleContext<OrcParser::GenericFunctionDefinitionContext>(0);
}

OrcParser::GenericExternFunctionDeclarationContext* OrcParser::GlobalFunctionDefinitionContext::genericExternFunctionDeclaration() {
  return getRuleContext<OrcParser::GenericExternFunctionDeclarationContext>(0);
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
  enterRule(_localctx, 108, OrcParser::RuleGlobalFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(749);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(734);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(733);
        match(OrcParser::Static);
      }
      setState(736);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(738);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(737);
        match(OrcParser::Static);
      }
      setState(740);
      externFunctionDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(742);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(741);
        match(OrcParser::Static);
      }
      setState(744);
      genericFunctionDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(746);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(745);
        match(OrcParser::Static);
      }
      setState(748);
      genericExternFunctionDeclaration();
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
  enterRule(_localctx, 110, OrcParser::RuleGlobalVarDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(751);
    varDeclaration();
    setState(752);
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
  enterRule(_localctx, 112, OrcParser::RuleExternFunctionDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(754);
    match(OrcParser::Extern);
    setState(755);
    type();
    setState(756);
    match(OrcParser::Id);
    setState(757);
    argumentsDeclaration();
    setState(758);
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
  enterRule(_localctx, 114, OrcParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(770);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::Import: {
        enterOuterAlt(_localctx, 1);
        setState(760);
        match(OrcParser::Import);
        setState(761);
        match(OrcParser::T__12);
        setState(762);
        match(OrcParser::From);
        setState(763);
        match(OrcParser::StringLiteral);
        setState(764);
        eos();
        break;
      }

      case OrcParser::T__66: {
        enterOuterAlt(_localctx, 2);
        setState(765);
        match(OrcParser::T__66);
        setState(766);
        match(OrcParser::T__12);
        setState(767);
        match(OrcParser::From);
        setState(768);
        match(OrcParser::StringLiteral);
        setState(769);
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
  enterRule(_localctx, 116, OrcParser::RuleIncludeStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(772);
    match(OrcParser::T__67);
    setState(773);
    includePathCharacters();
    setState(774);
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
  enterRule(_localctx, 118, OrcParser::RuleIncludePathCharacters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(785);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::T__23: {
        enterOuterAlt(_localctx, 1);
        setState(776);
        match(OrcParser::T__23);
        setState(780);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & -33554434) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & 4503599627370495) != 0)) {
          setState(777);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == OrcParser::T__24)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(782);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(783);
        match(OrcParser::T__24);
        break;
      }

      case OrcParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(784);
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
  enterRule(_localctx, 120, OrcParser::RulePackageStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(787);
    match(OrcParser::T__68);
    setState(788);
    match(OrcParser::Id);
    setState(789);
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
  enterRule(_localctx, 122, OrcParser::RuleLiteral);
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
    setState(791);
    _la = _input->LA(1);
    if (!(((((_la - 102) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 102)) & 255) != 0))) {
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
  enterRule(_localctx, 124, OrcParser::RuleEos);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(797);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(793);
      match(OrcParser::T__50);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(794);
      match(OrcParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(795);

      if (!(this->lineTerminatorAhead())) throw FailedPredicateException(this, "this->lineTerminatorAhead()");
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(796);

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
    case 62: return eosSempred(antlrcpp::downCast<EosContext *>(context), predicateIndex);

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
