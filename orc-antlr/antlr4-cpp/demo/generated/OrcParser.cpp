
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
  	4,1,115,757,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,1,0,5,0,120,8,0,10,0,12,0,123,9,0,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,135,8,1,1,2,1,2,1,2,1,2,5,2,141,8,2,10,
  	2,12,2,144,9,2,1,2,3,2,147,8,2,3,2,149,8,2,1,2,1,2,1,3,1,3,1,3,5,3,156,
  	8,3,10,3,12,3,159,9,3,1,4,1,4,1,4,3,4,164,8,4,1,4,1,4,1,4,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,203,8,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,268,8,5,1,5,5,5,271,8,5,10,
  	5,12,5,274,9,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,5,8,284,8,8,10,8,12,8,
  	287,9,8,1,8,1,8,1,9,1,9,1,9,3,9,294,8,9,1,9,1,9,1,9,1,9,1,9,3,9,301,8,
  	9,1,10,1,10,1,10,1,10,1,11,3,11,308,8,11,1,11,1,11,1,11,3,11,313,8,11,
  	1,11,1,11,3,11,317,8,11,1,11,3,11,320,8,11,1,11,3,11,323,8,11,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,
  	12,1,12,1,12,1,12,3,12,344,8,12,1,13,1,13,1,13,1,14,1,14,1,14,1,15,1,
  	15,1,15,1,15,1,16,1,16,3,16,358,8,16,1,16,1,16,1,17,1,17,1,17,1,17,1,
  	18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,
  	18,380,8,18,1,19,3,19,383,8,19,1,19,1,19,3,19,387,8,19,1,19,1,19,3,19,
  	391,8,19,1,20,1,20,3,20,395,8,20,1,21,1,21,1,21,1,21,5,21,401,8,21,10,
  	21,12,21,404,9,21,1,22,1,22,3,22,408,8,22,1,22,1,22,3,22,412,8,22,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,5,23,421,8,23,10,23,12,23,424,9,23,1,23,
  	1,23,3,23,428,8,23,1,24,1,24,1,24,4,24,433,8,24,11,24,12,24,434,1,24,
  	3,24,438,8,24,1,24,1,24,1,24,1,24,3,24,444,8,24,1,25,1,25,1,25,1,25,3,
  	25,450,8,25,1,25,1,25,1,25,1,26,1,26,1,26,1,27,1,27,5,27,460,8,27,10,
  	27,12,27,463,9,27,1,27,1,27,1,28,3,28,468,8,28,1,28,1,28,3,28,472,8,28,
  	1,28,1,28,1,28,1,28,3,28,478,8,28,1,28,3,28,481,8,28,1,28,3,28,484,8,
  	28,1,29,1,29,1,29,1,29,1,30,1,30,3,30,492,8,30,1,31,1,31,1,31,1,31,1,
  	31,1,31,1,31,1,32,1,32,1,32,5,32,504,8,32,10,32,12,32,507,9,32,1,33,1,
  	33,1,34,3,34,512,8,34,1,34,1,34,3,34,516,8,34,1,34,3,34,519,8,34,1,34,
  	5,34,522,8,34,10,34,12,34,525,9,34,1,34,1,34,5,34,529,8,34,10,34,12,34,
  	532,9,34,4,34,534,8,34,11,34,12,34,535,1,35,3,35,539,8,35,1,35,1,35,1,
  	35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,
  	36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,567,8,36,1,37,1,
  	37,1,37,1,37,1,37,1,37,5,37,575,8,37,10,37,12,37,578,9,37,1,37,3,37,581,
  	8,37,1,37,1,37,1,37,1,38,1,38,1,38,3,38,589,8,38,1,39,1,39,1,39,1,39,
  	1,40,1,40,5,40,597,8,40,10,40,12,40,600,9,40,1,40,1,40,1,41,1,41,3,41,
  	606,8,41,1,41,1,41,1,41,3,41,611,8,41,1,41,1,41,1,41,1,42,1,42,1,42,5,
  	42,619,8,42,10,42,12,42,622,9,42,1,42,1,42,1,43,1,43,1,43,3,43,629,8,
  	43,1,43,3,43,632,8,43,1,43,1,43,1,43,1,43,3,43,638,8,43,1,43,1,43,3,43,
  	642,8,43,1,44,1,44,3,44,646,8,44,1,45,1,45,1,45,1,46,1,46,3,46,653,8,
  	46,1,46,3,46,656,8,46,1,47,1,47,1,47,1,47,5,47,662,8,47,10,47,12,47,665,
  	9,47,3,47,667,8,47,1,47,3,47,670,8,47,1,47,1,47,3,47,674,8,47,1,48,1,
  	48,1,48,4,48,679,8,48,11,48,12,48,680,1,48,3,48,684,8,48,1,48,1,48,1,
  	48,5,48,689,8,48,10,48,12,48,692,9,48,1,49,1,49,1,49,1,49,1,49,1,50,3,
  	50,700,8,50,1,50,1,50,3,50,704,8,50,1,50,3,50,707,8,50,1,51,1,51,1,51,
  	1,52,1,52,1,52,1,52,1,52,1,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,
  	1,53,1,53,3,53,728,8,53,1,54,1,54,1,54,1,54,1,55,1,55,5,55,736,8,55,10,
  	55,12,55,739,9,55,1,55,1,55,3,55,743,8,55,1,56,1,56,1,56,1,56,1,57,1,
  	57,1,58,1,58,1,58,1,58,3,58,755,8,58,1,58,0,1,10,59,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,
  	62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,
  	106,108,110,112,114,116,0,11,2,0,13,13,18,19,1,0,14,15,1,0,21,23,1,0,
  	24,27,1,0,28,31,1,0,9,10,1,0,38,50,2,0,9,9,16,16,2,0,55,57,95,95,1,0,
  	25,25,1,0,102,109,847,0,121,1,0,0,0,2,134,1,0,0,0,4,136,1,0,0,0,6,152,
  	1,0,0,0,8,160,1,0,0,0,10,202,1,0,0,0,12,275,1,0,0,0,14,277,1,0,0,0,16,
  	279,1,0,0,0,18,300,1,0,0,0,20,302,1,0,0,0,22,322,1,0,0,0,24,343,1,0,0,
  	0,26,345,1,0,0,0,28,348,1,0,0,0,30,351,1,0,0,0,32,355,1,0,0,0,34,361,
  	1,0,0,0,36,379,1,0,0,0,38,382,1,0,0,0,40,394,1,0,0,0,42,396,1,0,0,0,44,
  	405,1,0,0,0,46,413,1,0,0,0,48,443,1,0,0,0,50,445,1,0,0,0,52,454,1,0,0,
  	0,54,457,1,0,0,0,56,483,1,0,0,0,58,485,1,0,0,0,60,489,1,0,0,0,62,493,
  	1,0,0,0,64,500,1,0,0,0,66,508,1,0,0,0,68,511,1,0,0,0,70,538,1,0,0,0,72,
  	566,1,0,0,0,74,568,1,0,0,0,76,585,1,0,0,0,78,590,1,0,0,0,80,594,1,0,0,
  	0,82,603,1,0,0,0,84,615,1,0,0,0,86,641,1,0,0,0,88,645,1,0,0,0,90,647,
  	1,0,0,0,92,655,1,0,0,0,94,673,1,0,0,0,96,675,1,0,0,0,98,693,1,0,0,0,100,
  	706,1,0,0,0,102,708,1,0,0,0,104,711,1,0,0,0,106,727,1,0,0,0,108,729,1,
  	0,0,0,110,742,1,0,0,0,112,744,1,0,0,0,114,748,1,0,0,0,116,754,1,0,0,0,
  	118,120,3,2,1,0,119,118,1,0,0,0,120,123,1,0,0,0,121,119,1,0,0,0,121,122,
  	1,0,0,0,122,1,1,0,0,0,123,121,1,0,0,0,124,135,3,112,56,0,125,135,3,108,
  	54,0,126,135,3,106,53,0,127,135,3,16,8,0,128,135,3,74,37,0,129,135,3,
  	82,41,0,130,135,3,78,39,0,131,135,3,102,51,0,132,135,3,100,50,0,133,135,
  	3,14,7,0,134,124,1,0,0,0,134,125,1,0,0,0,134,126,1,0,0,0,134,127,1,0,
  	0,0,134,128,1,0,0,0,134,129,1,0,0,0,134,130,1,0,0,0,134,131,1,0,0,0,134,
  	132,1,0,0,0,134,133,1,0,0,0,135,3,1,0,0,0,136,148,5,1,0,0,137,142,3,10,
  	5,0,138,139,5,2,0,0,139,141,3,10,5,0,140,138,1,0,0,0,141,144,1,0,0,0,
  	142,140,1,0,0,0,142,143,1,0,0,0,143,146,1,0,0,0,144,142,1,0,0,0,145,147,
  	5,2,0,0,146,145,1,0,0,0,146,147,1,0,0,0,147,149,1,0,0,0,148,137,1,0,0,
  	0,148,149,1,0,0,0,149,150,1,0,0,0,150,151,5,3,0,0,151,5,1,0,0,0,152,157,
  	3,10,5,0,153,154,5,2,0,0,154,156,3,10,5,0,155,153,1,0,0,0,156,159,1,0,
  	0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,7,1,0,0,0,159,157,1,0,0,0,160,
  	161,5,4,0,0,161,163,3,56,28,0,162,164,5,110,0,0,163,162,1,0,0,0,163,164,
  	1,0,0,0,164,165,1,0,0,0,165,166,3,94,47,0,166,167,3,54,27,0,167,9,1,0,
  	0,0,168,169,6,5,-1,0,169,203,3,8,4,0,170,171,5,75,0,0,171,172,5,110,0,
  	0,172,203,3,4,2,0,173,174,5,12,0,0,174,203,3,10,5,29,175,176,5,13,0,0,
  	176,203,3,10,5,28,177,178,5,5,0,0,178,203,3,10,5,27,179,180,5,6,0,0,180,
  	203,3,10,5,26,181,182,5,14,0,0,182,203,3,10,5,25,183,184,5,15,0,0,184,
  	203,3,10,5,24,185,186,5,16,0,0,186,203,3,10,5,23,187,188,5,17,0,0,188,
  	203,3,10,5,22,189,190,5,1,0,0,190,191,3,56,28,0,191,192,5,3,0,0,192,193,
  	3,10,5,8,193,203,1,0,0,0,194,203,5,83,0,0,195,203,5,110,0,0,196,203,5,
  	93,0,0,197,203,3,114,57,0,198,199,5,1,0,0,199,200,3,6,3,0,200,201,5,3,
  	0,0,201,203,1,0,0,0,202,168,1,0,0,0,202,170,1,0,0,0,202,173,1,0,0,0,202,
  	175,1,0,0,0,202,177,1,0,0,0,202,179,1,0,0,0,202,181,1,0,0,0,202,183,1,
  	0,0,0,202,185,1,0,0,0,202,187,1,0,0,0,202,189,1,0,0,0,202,194,1,0,0,0,
  	202,195,1,0,0,0,202,196,1,0,0,0,202,197,1,0,0,0,202,198,1,0,0,0,203,272,
  	1,0,0,0,204,205,10,21,0,0,205,206,7,0,0,0,206,271,3,10,5,22,207,208,10,
  	20,0,0,208,209,7,1,0,0,209,271,3,10,5,21,210,211,10,19,0,0,211,212,5,
  	20,0,0,212,271,3,10,5,20,213,214,10,18,0,0,214,215,7,2,0,0,215,271,3,
  	10,5,19,216,217,10,17,0,0,217,218,7,3,0,0,218,271,3,10,5,18,219,220,10,
  	16,0,0,220,221,5,72,0,0,221,271,3,10,5,17,222,223,10,15,0,0,223,224,7,
  	4,0,0,224,271,3,10,5,16,225,226,10,14,0,0,226,227,5,12,0,0,227,271,3,
  	10,5,15,228,229,10,13,0,0,229,230,5,4,0,0,230,271,3,10,5,14,231,232,10,
  	12,0,0,232,233,5,32,0,0,233,271,3,10,5,13,234,235,10,11,0,0,235,236,5,
  	33,0,0,236,271,3,10,5,12,237,238,10,10,0,0,238,239,5,34,0,0,239,271,3,
  	10,5,11,240,241,10,9,0,0,241,242,5,35,0,0,242,243,3,10,5,0,243,244,5,
  	36,0,0,244,245,3,10,5,10,245,271,1,0,0,0,246,247,10,7,0,0,247,248,5,37,
  	0,0,248,271,3,10,5,7,249,250,10,6,0,0,250,251,3,12,6,0,251,252,3,10,5,
  	6,252,271,1,0,0,0,253,254,10,36,0,0,254,271,3,4,2,0,255,256,10,35,0,0,
  	256,271,5,5,0,0,257,258,10,34,0,0,258,271,5,6,0,0,259,260,10,32,0,0,260,
  	261,5,7,0,0,261,262,3,10,5,0,262,263,5,8,0,0,263,271,1,0,0,0,264,265,
  	10,31,0,0,265,267,7,5,0,0,266,268,5,11,0,0,267,266,1,0,0,0,267,268,1,
  	0,0,0,268,269,1,0,0,0,269,271,5,110,0,0,270,204,1,0,0,0,270,207,1,0,0,
  	0,270,210,1,0,0,0,270,213,1,0,0,0,270,216,1,0,0,0,270,219,1,0,0,0,270,
  	222,1,0,0,0,270,225,1,0,0,0,270,228,1,0,0,0,270,231,1,0,0,0,270,234,1,
  	0,0,0,270,237,1,0,0,0,270,240,1,0,0,0,270,246,1,0,0,0,270,249,1,0,0,0,
  	270,253,1,0,0,0,270,255,1,0,0,0,270,257,1,0,0,0,270,259,1,0,0,0,270,264,
  	1,0,0,0,271,274,1,0,0,0,272,270,1,0,0,0,272,273,1,0,0,0,273,11,1,0,0,
  	0,274,272,1,0,0,0,275,276,7,6,0,0,276,13,1,0,0,0,277,278,5,51,0,0,278,
  	15,1,0,0,0,279,280,5,88,0,0,280,281,5,110,0,0,281,285,5,52,0,0,282,284,
  	3,18,9,0,283,282,1,0,0,0,284,287,1,0,0,0,285,283,1,0,0,0,285,286,1,0,
  	0,0,286,288,1,0,0,0,287,285,1,0,0,0,288,289,5,111,0,0,289,17,1,0,0,0,
  	290,291,3,56,28,0,291,293,5,110,0,0,292,294,3,20,10,0,293,292,1,0,0,0,
  	293,294,1,0,0,0,294,295,1,0,0,0,295,296,3,116,58,0,296,301,1,0,0,0,297,
  	298,3,96,48,0,298,299,3,116,58,0,299,301,1,0,0,0,300,290,1,0,0,0,300,
  	297,1,0,0,0,301,19,1,0,0,0,302,303,5,7,0,0,303,304,5,104,0,0,304,305,
  	5,8,0,0,305,21,1,0,0,0,306,308,5,98,0,0,307,306,1,0,0,0,307,308,1,0,0,
  	0,308,309,1,0,0,0,309,310,3,56,28,0,310,312,5,110,0,0,311,313,3,20,10,
  	0,312,311,1,0,0,0,312,313,1,0,0,0,313,316,1,0,0,0,314,315,5,37,0,0,315,
  	317,3,10,5,0,316,314,1,0,0,0,316,317,1,0,0,0,317,323,1,0,0,0,318,320,
  	5,98,0,0,319,318,1,0,0,0,319,320,1,0,0,0,320,321,1,0,0,0,321,323,3,96,
  	48,0,322,307,1,0,0,0,322,319,1,0,0,0,323,23,1,0,0,0,324,325,3,8,4,0,325,
  	326,3,116,58,0,326,344,1,0,0,0,327,328,3,22,11,0,328,329,3,116,58,0,329,
  	344,1,0,0,0,330,344,3,34,17,0,331,344,3,54,27,0,332,344,3,26,13,0,333,
  	344,3,28,14,0,334,344,3,30,15,0,335,344,3,46,23,0,336,344,3,32,16,0,337,
  	344,3,36,18,0,338,344,3,48,24,0,339,340,3,10,5,0,340,341,3,116,58,0,341,
  	344,1,0,0,0,342,344,3,14,7,0,343,324,1,0,0,0,343,327,1,0,0,0,343,330,
  	1,0,0,0,343,331,1,0,0,0,343,332,1,0,0,0,343,333,1,0,0,0,343,334,1,0,0,
  	0,343,335,1,0,0,0,343,336,1,0,0,0,343,337,1,0,0,0,343,338,1,0,0,0,343,
  	339,1,0,0,0,343,342,1,0,0,0,344,25,1,0,0,0,345,346,5,80,0,0,346,347,3,
  	116,58,0,347,27,1,0,0,0,348,349,5,70,0,0,349,350,3,116,58,0,350,29,1,
  	0,0,0,351,352,5,85,0,0,352,353,3,10,5,0,353,354,3,116,58,0,354,31,1,0,
  	0,0,355,357,5,78,0,0,356,358,3,10,5,0,357,356,1,0,0,0,357,358,1,0,0,0,
  	358,359,1,0,0,0,359,360,3,116,58,0,360,33,1,0,0,0,361,362,3,10,5,0,362,
  	363,7,7,0,0,363,364,3,54,27,0,364,35,1,0,0,0,365,366,5,82,0,0,366,367,
  	3,10,5,0,367,368,3,54,27,0,368,380,1,0,0,0,369,370,5,81,0,0,370,371,5,
  	1,0,0,371,372,3,38,19,0,372,373,5,3,0,0,373,374,3,54,27,0,374,380,1,0,
  	0,0,375,376,5,81,0,0,376,377,3,38,19,0,377,378,3,54,27,0,378,380,1,0,
  	0,0,379,365,1,0,0,0,379,369,1,0,0,0,379,375,1,0,0,0,380,37,1,0,0,0,381,
  	383,3,40,20,0,382,381,1,0,0,0,382,383,1,0,0,0,383,384,1,0,0,0,384,386,
  	5,51,0,0,385,387,3,10,5,0,386,385,1,0,0,0,386,387,1,0,0,0,387,388,1,0,
  	0,0,388,390,5,51,0,0,389,391,3,10,5,0,390,389,1,0,0,0,390,391,1,0,0,0,
  	391,39,1,0,0,0,392,395,3,42,21,0,393,395,3,10,5,0,394,392,1,0,0,0,394,
  	393,1,0,0,0,395,41,1,0,0,0,396,397,3,56,28,0,397,402,3,44,22,0,398,399,
  	5,2,0,0,399,401,3,44,22,0,400,398,1,0,0,0,401,404,1,0,0,0,402,400,1,0,
  	0,0,402,403,1,0,0,0,403,43,1,0,0,0,404,402,1,0,0,0,405,407,5,110,0,0,
  	406,408,3,20,10,0,407,406,1,0,0,0,407,408,1,0,0,0,408,411,1,0,0,0,409,
  	410,5,37,0,0,410,412,3,10,5,0,411,409,1,0,0,0,411,412,1,0,0,0,412,45,
  	1,0,0,0,413,414,5,84,0,0,414,415,3,10,5,0,415,422,3,54,27,0,416,417,5,
  	53,0,0,417,418,3,10,5,0,418,419,3,54,27,0,419,421,1,0,0,0,420,416,1,0,
  	0,0,421,424,1,0,0,0,422,420,1,0,0,0,422,423,1,0,0,0,423,427,1,0,0,0,424,
  	422,1,0,0,0,425,426,5,74,0,0,426,428,3,54,27,0,427,425,1,0,0,0,427,428,
  	1,0,0,0,428,47,1,0,0,0,429,430,5,86,0,0,430,432,3,54,27,0,431,433,3,50,
  	25,0,432,431,1,0,0,0,433,434,1,0,0,0,434,432,1,0,0,0,434,435,1,0,0,0,
  	435,437,1,0,0,0,436,438,3,52,26,0,437,436,1,0,0,0,437,438,1,0,0,0,438,
  	444,1,0,0,0,439,440,5,86,0,0,440,441,3,54,27,0,441,442,3,52,26,0,442,
  	444,1,0,0,0,443,429,1,0,0,0,443,439,1,0,0,0,444,49,1,0,0,0,445,446,5,
  	76,0,0,446,447,5,1,0,0,447,449,3,70,35,0,448,450,5,110,0,0,449,448,1,
  	0,0,0,449,450,1,0,0,0,450,451,1,0,0,0,451,452,5,3,0,0,452,453,3,54,27,
  	0,453,51,1,0,0,0,454,455,5,77,0,0,455,456,3,54,27,0,456,53,1,0,0,0,457,
  	461,5,52,0,0,458,460,3,24,12,0,459,458,1,0,0,0,460,463,1,0,0,0,461,459,
  	1,0,0,0,461,462,1,0,0,0,462,464,1,0,0,0,463,461,1,0,0,0,464,465,5,111,
  	0,0,465,55,1,0,0,0,466,468,3,66,33,0,467,466,1,0,0,0,467,468,1,0,0,0,
  	468,469,1,0,0,0,469,471,3,72,36,0,470,472,3,20,10,0,471,470,1,0,0,0,471,
  	472,1,0,0,0,472,484,1,0,0,0,473,484,3,58,29,0,474,484,3,68,34,0,475,484,
  	3,70,35,0,476,478,3,66,33,0,477,476,1,0,0,0,477,478,1,0,0,0,478,480,1,
  	0,0,0,479,481,5,88,0,0,480,479,1,0,0,0,480,481,1,0,0,0,481,482,1,0,0,
  	0,482,484,5,110,0,0,483,467,1,0,0,0,483,473,1,0,0,0,483,474,1,0,0,0,483,
  	475,1,0,0,0,483,477,1,0,0,0,484,57,1,0,0,0,485,486,5,4,0,0,486,487,3,
  	56,28,0,487,488,3,94,47,0,488,59,1,0,0,0,489,491,3,56,28,0,490,492,5,
  	110,0,0,491,490,1,0,0,0,491,492,1,0,0,0,492,61,1,0,0,0,493,494,5,54,0,
  	0,494,495,5,1,0,0,495,496,5,1,0,0,496,497,5,110,0,0,497,498,5,3,0,0,498,
  	499,5,3,0,0,499,63,1,0,0,0,500,501,3,56,28,0,501,505,3,94,47,0,502,504,
  	3,62,31,0,503,502,1,0,0,0,504,507,1,0,0,0,505,503,1,0,0,0,505,506,1,0,
  	0,0,506,65,1,0,0,0,507,505,1,0,0,0,508,509,7,8,0,0,509,67,1,0,0,0,510,
  	512,3,66,33,0,511,510,1,0,0,0,511,512,1,0,0,0,512,518,1,0,0,0,513,519,
  	3,72,36,0,514,516,5,88,0,0,515,514,1,0,0,0,515,516,1,0,0,0,516,517,1,
  	0,0,0,517,519,5,110,0,0,518,513,1,0,0,0,518,515,1,0,0,0,519,533,1,0,0,
  	0,520,522,3,66,33,0,521,520,1,0,0,0,522,525,1,0,0,0,523,521,1,0,0,0,523,
  	524,1,0,0,0,524,526,1,0,0,0,525,523,1,0,0,0,526,530,5,13,0,0,527,529,
  	3,66,33,0,528,527,1,0,0,0,529,532,1,0,0,0,530,528,1,0,0,0,530,531,1,0,
  	0,0,531,534,1,0,0,0,532,530,1,0,0,0,533,523,1,0,0,0,534,535,1,0,0,0,535,
  	533,1,0,0,0,535,536,1,0,0,0,536,69,1,0,0,0,537,539,5,88,0,0,538,537,1,
  	0,0,0,538,539,1,0,0,0,539,540,1,0,0,0,540,541,5,110,0,0,541,542,5,58,
  	0,0,542,71,1,0,0,0,543,567,5,59,0,0,544,567,5,60,0,0,545,567,5,61,0,0,
  	546,567,5,62,0,0,547,567,5,63,0,0,548,567,5,64,0,0,549,567,5,79,0,0,550,
  	567,5,65,0,0,551,552,5,65,0,0,552,567,5,65,0,0,553,554,5,65,0,0,554,567,
  	5,62,0,0,555,556,5,66,0,0,556,567,5,63,0,0,557,558,5,66,0,0,558,567,5,
  	59,0,0,559,560,5,66,0,0,560,567,5,60,0,0,561,562,5,66,0,0,562,567,5,65,
  	0,0,563,564,5,66,0,0,564,565,5,65,0,0,565,567,5,65,0,0,566,543,1,0,0,
  	0,566,544,1,0,0,0,566,545,1,0,0,0,566,546,1,0,0,0,566,547,1,0,0,0,566,
  	548,1,0,0,0,566,549,1,0,0,0,566,550,1,0,0,0,566,551,1,0,0,0,566,553,1,
  	0,0,0,566,555,1,0,0,0,566,557,1,0,0,0,566,559,1,0,0,0,566,561,1,0,0,0,
  	566,563,1,0,0,0,567,73,1,0,0,0,568,569,5,90,0,0,569,570,5,110,0,0,570,
  	571,5,52,0,0,571,576,3,76,38,0,572,573,5,2,0,0,573,575,3,76,38,0,574,
  	572,1,0,0,0,575,578,1,0,0,0,576,574,1,0,0,0,576,577,1,0,0,0,577,580,1,
  	0,0,0,578,576,1,0,0,0,579,581,5,2,0,0,580,579,1,0,0,0,580,581,1,0,0,0,
  	581,582,1,0,0,0,582,583,5,111,0,0,583,584,3,116,58,0,584,75,1,0,0,0,585,
  	588,5,110,0,0,586,587,5,37,0,0,587,589,5,104,0,0,588,586,1,0,0,0,588,
  	589,1,0,0,0,589,77,1,0,0,0,590,591,5,94,0,0,591,592,5,110,0,0,592,593,
  	3,80,40,0,593,79,1,0,0,0,594,598,5,52,0,0,595,597,3,88,44,0,596,595,1,
  	0,0,0,597,600,1,0,0,0,598,596,1,0,0,0,598,599,1,0,0,0,599,601,1,0,0,0,
  	600,598,1,0,0,0,601,602,5,111,0,0,602,81,1,0,0,0,603,605,5,89,0,0,604,
  	606,5,101,0,0,605,604,1,0,0,0,605,606,1,0,0,0,606,607,1,0,0,0,607,610,
  	5,110,0,0,608,609,5,91,0,0,609,611,5,110,0,0,610,608,1,0,0,0,610,611,
  	1,0,0,0,611,612,1,0,0,0,612,613,3,84,42,0,613,614,3,116,58,0,614,83,1,
  	0,0,0,615,620,5,52,0,0,616,619,3,86,43,0,617,619,3,88,44,0,618,616,1,
  	0,0,0,618,617,1,0,0,0,619,622,1,0,0,0,620,618,1,0,0,0,620,621,1,0,0,0,
  	621,623,1,0,0,0,622,620,1,0,0,0,623,624,5,111,0,0,624,85,1,0,0,0,625,
  	626,3,56,28,0,626,628,5,110,0,0,627,629,3,20,10,0,628,627,1,0,0,0,628,
  	629,1,0,0,0,629,631,1,0,0,0,630,632,3,90,45,0,631,630,1,0,0,0,631,632,
  	1,0,0,0,632,633,1,0,0,0,633,634,3,116,58,0,634,642,1,0,0,0,635,637,3,
  	96,48,0,636,638,3,90,45,0,637,636,1,0,0,0,637,638,1,0,0,0,638,639,1,0,
  	0,0,639,640,3,116,58,0,640,642,1,0,0,0,641,625,1,0,0,0,641,635,1,0,0,
  	0,642,87,1,0,0,0,643,646,3,98,49,0,644,646,3,104,52,0,645,643,1,0,0,0,
  	645,644,1,0,0,0,646,89,1,0,0,0,647,648,5,37,0,0,648,649,3,10,5,0,649,
  	91,1,0,0,0,650,652,3,56,28,0,651,653,5,110,0,0,652,651,1,0,0,0,652,653,
  	1,0,0,0,653,656,1,0,0,0,654,656,3,96,48,0,655,650,1,0,0,0,655,654,1,0,
  	0,0,656,93,1,0,0,0,657,666,5,1,0,0,658,663,3,92,46,0,659,660,5,2,0,0,
  	660,662,3,92,46,0,661,659,1,0,0,0,662,665,1,0,0,0,663,661,1,0,0,0,663,
  	664,1,0,0,0,664,667,1,0,0,0,665,663,1,0,0,0,666,658,1,0,0,0,666,667,1,
  	0,0,0,667,669,1,0,0,0,668,670,5,2,0,0,669,668,1,0,0,0,669,670,1,0,0,0,
  	670,671,1,0,0,0,671,674,5,3,0,0,672,674,1,0,0,0,673,657,1,0,0,0,673,672,
  	1,0,0,0,674,95,1,0,0,0,675,676,3,56,28,0,676,678,5,1,0,0,677,679,5,13,
  	0,0,678,677,1,0,0,0,679,680,1,0,0,0,680,678,1,0,0,0,680,681,1,0,0,0,681,
  	683,1,0,0,0,682,684,5,110,0,0,683,682,1,0,0,0,683,684,1,0,0,0,684,685,
  	1,0,0,0,685,686,5,3,0,0,686,690,3,94,47,0,687,689,3,62,31,0,688,687,1,
  	0,0,0,689,692,1,0,0,0,690,688,1,0,0,0,690,691,1,0,0,0,691,97,1,0,0,0,
  	692,690,1,0,0,0,693,694,3,56,28,0,694,695,5,110,0,0,695,696,3,94,47,0,
  	696,697,3,54,27,0,697,99,1,0,0,0,698,700,5,98,0,0,699,698,1,0,0,0,699,
  	700,1,0,0,0,700,701,1,0,0,0,701,707,3,98,49,0,702,704,5,98,0,0,703,702,
  	1,0,0,0,703,704,1,0,0,0,704,705,1,0,0,0,705,707,3,104,52,0,706,699,1,
  	0,0,0,706,703,1,0,0,0,707,101,1,0,0,0,708,709,3,22,11,0,709,710,3,116,
  	58,0,710,103,1,0,0,0,711,712,5,92,0,0,712,713,3,56,28,0,713,714,5,110,
  	0,0,714,715,3,94,47,0,715,716,3,116,58,0,716,105,1,0,0,0,717,718,5,97,
  	0,0,718,719,5,13,0,0,719,720,5,87,0,0,720,721,5,108,0,0,721,728,3,116,
  	58,0,722,723,5,67,0,0,723,724,5,13,0,0,724,725,5,87,0,0,725,726,5,108,
  	0,0,726,728,3,116,58,0,727,717,1,0,0,0,727,722,1,0,0,0,728,107,1,0,0,
  	0,729,730,5,68,0,0,730,731,3,110,55,0,731,732,3,116,58,0,732,109,1,0,
  	0,0,733,737,5,24,0,0,734,736,8,9,0,0,735,734,1,0,0,0,736,739,1,0,0,0,
  	737,735,1,0,0,0,737,738,1,0,0,0,738,740,1,0,0,0,739,737,1,0,0,0,740,743,
  	5,25,0,0,741,743,5,108,0,0,742,733,1,0,0,0,742,741,1,0,0,0,743,111,1,
  	0,0,0,744,745,5,69,0,0,745,746,5,110,0,0,746,747,3,116,58,0,747,113,1,
  	0,0,0,748,749,7,10,0,0,749,115,1,0,0,0,750,755,5,51,0,0,751,755,5,0,0,
  	1,752,755,4,58,20,0,753,755,4,58,21,0,754,750,1,0,0,0,754,751,1,0,0,0,
  	754,752,1,0,0,0,754,753,1,0,0,0,755,117,1,0,0,0,80,121,134,142,146,148,
  	157,163,202,267,270,272,285,293,300,307,312,316,319,322,343,357,379,382,
  	386,390,394,402,407,411,422,427,434,437,443,449,461,467,471,477,480,483,
  	491,505,511,515,518,523,530,535,538,566,576,580,588,598,605,610,618,620,
  	628,631,637,641,645,652,655,663,666,669,673,680,683,690,699,703,706,727,
  	737,742,754
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
    setState(121);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -322007373356990448) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70398121115711) != 0)) {
      setState(118);
      rootDeclaration();
      setState(123);
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
    setState(134);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(124);
      packageStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(125);
      includeStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(126);
      importStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(127);
      structDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(128);
      enumDefinition();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(129);
      classDefinition();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(130);
      extensionDefinition();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(131);
      globalVarDeclaration();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(132);
      globalFunctionDefinition();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(133);
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
    setState(136);
    match(OrcParser::T__0);
    setState(148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 68585521409) != 0)) {
      setState(137);
      singleExpression(0);
      setState(142);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(138);
          match(OrcParser::T__1);
          setState(139);
          singleExpression(0); 
        }
        setState(144);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      }
      setState(146);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__1) {
        setState(145);
        match(OrcParser::T__1);
      }
    }
    setState(150);
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
    setState(152);
    singleExpression(0);
    setState(157);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__1) {
      setState(153);
      match(OrcParser::T__1);
      setState(154);
      singleExpression(0);
      setState(159);
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
    setState(160);
    match(OrcParser::T__3);
    setState(161);
    type();
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(162);
      match(OrcParser::Id);
    }
    setState(165);
    argumentsDeclaration();
    setState(166);
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
    setState(202);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<LabelClosureExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(169);
      closureExpression();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NewExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(170);
      match(OrcParser::New);
      setState(171);
      match(OrcParser::Id);
      setState(172);
      arguments();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<GetAddressExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(173);
      match(OrcParser::T__11);
      setState(174);
      singleExpression(29);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<DerefExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(175);
      match(OrcParser::T__12);
      setState(176);
      singleExpression(28);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PreIncrementExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(177);
      match(OrcParser::T__4);
      setState(178);
      singleExpression(27);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PreDecreaseExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(179);
      match(OrcParser::T__5);
      setState(180);
      singleExpression(26);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<UnaryPlusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(181);
      match(OrcParser::T__13);
      setState(182);
      singleExpression(25);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<UnaryMinusExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(183);
      match(OrcParser::T__14);
      setState(184);
      singleExpression(24);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<BitNotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(185);
      match(OrcParser::T__15);
      setState(186);
      singleExpression(23);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<NotExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(187);
      match(OrcParser::T__16);
      setState(188);
      singleExpression(22);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<CastExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(189);
      match(OrcParser::T__0);
      setState(190);
      type();
      setState(191);
      match(OrcParser::T__2);
      setState(192);
      singleExpression(8);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<ThisExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(194);
      match(OrcParser::This);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<IdentifierExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(195);
      match(OrcParser::Id);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<SuperExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(196);
      match(OrcParser::Super);
      break;
    }

    case 15: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(197);
      literal();
      break;
    }

    case 16: {
      _localctx = _tracker.createInstance<ParenthesizedExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(198);
      match(OrcParser::T__0);
      setState(199);
      expressionSequence();
      setState(200);
      match(OrcParser::T__2);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(272);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(270);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MultiplicativeExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(204);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(205);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 794624) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(206);
          singleExpression(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AdditiveExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(207);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(208);
          _la = _input->LA(1);
          if (!(_la == OrcParser::T__13

          || _la == OrcParser::T__14)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(209);
          singleExpression(21);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CoalesceExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(210);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(211);
          match(OrcParser::T__19);
          setState(212);
          singleExpression(20);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BitShiftExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(213);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(214);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 14680064) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(215);
          singleExpression(19);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<RelationalExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(216);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(217);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 251658240) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(218);
          singleExpression(18);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<InstanceofExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(219);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(220);
          match(OrcParser::Instanceof);
          setState(221);
          singleExpression(17);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<EqualityExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(222);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(223);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4026531840) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(224);
          singleExpression(16);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BitAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(225);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(226);
          match(OrcParser::T__11);
          setState(227);
          singleExpression(15);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BitXOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(228);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(229);
          match(OrcParser::T__3);
          setState(230);
          singleExpression(14);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BitOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(231);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(232);
          match(OrcParser::T__31);
          setState(233);
          singleExpression(13);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<LogicalAndExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(234);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(235);
          match(OrcParser::T__32);
          setState(236);
          singleExpression(12);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<LogicalOrExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(237);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(238);
          match(OrcParser::T__33);
          setState(239);
          singleExpression(11);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<TernaryExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(240);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(241);
          match(OrcParser::T__34);
          setState(242);
          singleExpression(0);
          setState(243);
          match(OrcParser::T__35);
          setState(244);
          singleExpression(10);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<AssignmentExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(246);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(247);
          match(OrcParser::T__36);
          setState(248);
          singleExpression(7);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<AssignmentOperatorExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(249);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(250);
          assignmentOperator();
          setState(251);
          singleExpression(6);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<CallExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(253);

          if (!(precpred(_ctx, 36))) throw FailedPredicateException(this, "precpred(_ctx, 36)");
          setState(254);
          arguments();
          break;
        }

        case 17: {
          auto newContext = _tracker.createInstance<PostIncrementExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(255);

          if (!(precpred(_ctx, 35))) throw FailedPredicateException(this, "precpred(_ctx, 35)");
          setState(256);
          match(OrcParser::T__4);
          break;
        }

        case 18: {
          auto newContext = _tracker.createInstance<PostDecreaseExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(257);

          if (!(precpred(_ctx, 34))) throw FailedPredicateException(this, "precpred(_ctx, 34)");
          setState(258);
          match(OrcParser::T__5);
          break;
        }

        case 19: {
          auto newContext = _tracker.createInstance<MemberIndexExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(259);

          if (!(precpred(_ctx, 32))) throw FailedPredicateException(this, "precpred(_ctx, 32)");
          setState(260);
          match(OrcParser::T__6);
          setState(261);
          singleExpression(0);
          setState(262);
          match(OrcParser::T__7);
          break;
        }

        case 20: {
          auto newContext = _tracker.createInstance<MemberDotExpressionContext>(_tracker.createInstance<SingleExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleSingleExpression);
          setState(264);

          if (!(precpred(_ctx, 31))) throw FailedPredicateException(this, "precpred(_ctx, 31)");
          setState(265);
          _la = _input->LA(1);
          if (!(_la == OrcParser::T__8

          || _la == OrcParser::T__9)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(267);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == OrcParser::T__10) {
            setState(266);
            match(OrcParser::T__10);
          }
          setState(269);
          match(OrcParser::Id);
          break;
        }

        default:
          break;
        } 
      }
      setState(274);
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
    setState(275);
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
    setState(277);
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
    setState(279);
    match(OrcParser::Struct);
    setState(280);
    match(OrcParser::Id);
    setState(281);
    match(OrcParser::T__51);
    setState(285);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70370908471303) != 0)) {
      setState(282);
      structMember();
      setState(287);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(288);
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
    setState(300);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(290);
      type();
      setState(291);
      match(OrcParser::Id);
      setState(293);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
      case 1: {
        setState(292);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(295);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(297);
      functionPointerVarDeclaration();
      setState(298);
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
    setState(302);
    match(OrcParser::T__6);
    setState(303);
    match(OrcParser::DecimalLiteral);
    setState(304);
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
    setState(322);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(307);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(306);
        match(OrcParser::Static);
      }
      setState(309);
      type();
      setState(310);
      match(OrcParser::Id);
      setState(312);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(311);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(316);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(314);
        match(OrcParser::T__36);
        setState(315);
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
      setState(319);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(318);
        match(OrcParser::Static);
      }
      setState(321);
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
    setState(343);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(324);
      closureExpression();
      setState(325);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(327);
      varDeclaration();
      setState(328);
      eos();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(330);
      scopeStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(331);
      block();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(332);
      continueStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(333);
      breakStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(334);
      throwStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(335);
      selectionStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(336);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(337);
      iterationStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(338);
      tryStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(339);
      singleExpression(0);
      setState(340);
      eos();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(342);
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
    setState(345);
    match(OrcParser::Continue);
    setState(346);
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
    setState(348);
    match(OrcParser::Break);
    setState(349);
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
    setState(351);
    match(OrcParser::Throw);
    setState(352);
    singleExpression(0);
    setState(353);
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
    setState(355);
    match(OrcParser::Return);
    setState(357);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(356);
      singleExpression(0);
      break;
    }

    default:
      break;
    }
    setState(359);
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
    setState(361);
    singleExpression(0);
    setState(362);
    _la = _input->LA(1);
    if (!(_la == OrcParser::T__8

    || _la == OrcParser::T__15)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(363);
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
    setState(379);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(365);
      match(OrcParser::While);
      setState(366);
      singleExpression(0);
      setState(367);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(369);
      match(OrcParser::For);
      setState(370);
      match(OrcParser::T__0);
      setState(371);
      forCondition();
      setState(372);
      match(OrcParser::T__2);
      setState(373);
      block();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(375);
      match(OrcParser::For);
      setState(376);
      forCondition();
      setState(377);
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
    setState(382);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170417550) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 140465312139271) != 0)) {
      setState(381);
      forInit();
    }
    setState(384);
    match(OrcParser::T__50);
    setState(386);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 68585521409) != 0)) {
      setState(385);
      singleExpression(0);
    }
    setState(388);
    match(OrcParser::T__50);
    setState(390);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 258162) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & 68585521409) != 0)) {
      setState(389);
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

//----------------- ForInitContext ------------------------------------------------------------------

OrcParser::ForInitContext::ForInitContext(ParserRuleContext *parent, size_t invokingState)
  : OrcRuleContext(parent, invokingState) {
}

OrcParser::ForVarDeclarationContext* OrcParser::ForInitContext::forVarDeclaration() {
  return getRuleContext<OrcParser::ForVarDeclarationContext>(0);
}

OrcParser::SingleExpressionContext* OrcParser::ForInitContext::singleExpression() {
  return getRuleContext<OrcParser::SingleExpressionContext>(0);
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
    setState(394);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(392);
      forVarDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(393);
      singleExpression(0);
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
    setState(396);
    type();
    setState(397);
    forVarInitDeclarator();
    setState(402);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__1) {
      setState(398);
      match(OrcParser::T__1);
      setState(399);
      forVarInitDeclarator();
      setState(404);
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
    setState(405);
    match(OrcParser::Id);
    setState(407);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__6) {
      setState(406);
      arraySizeDeclaration();
    }
    setState(411);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__36) {
      setState(409);
      match(OrcParser::T__36);
      setState(410);
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
    setState(413);
    match(OrcParser::If);
    setState(414);
    singleExpression(0);
    setState(415);
    block();
    setState(422);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__52) {
      setState(416);
      match(OrcParser::T__52);
      setState(417);
      singleExpression(0);
      setState(418);
      block();
      setState(424);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(427);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Else) {
      setState(425);
      match(OrcParser::Else);
      setState(426);
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
    setState(443);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(429);
      match(OrcParser::Try);
      setState(430);
      block();
      setState(432); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(431);
        catchClause();
        setState(434); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == OrcParser::Catch);
      setState(437);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Finally) {
        setState(436);
        finallyClause();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(439);
      match(OrcParser::Try);
      setState(440);
      block();
      setState(441);
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
    setState(445);
    match(OrcParser::Catch);
    setState(446);
    match(OrcParser::T__0);
    setState(447);
    ref();
    setState(449);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(448);
      match(OrcParser::Id);
    }
    setState(451);
    match(OrcParser::T__2);
    setState(452);
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
    setState(454);
    match(OrcParser::Finally);
    setState(455);
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
    setState(457);
    match(OrcParser::T__51);
    setState(461);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -317503773729361806) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 140482499823687) != 0)) {
      setState(458);
      statement();
      setState(463);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(464);
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
    setState(483);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(467);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
        setState(466);
        typeQualifier();
      }
      setState(469);
      primitiveType();
      setState(471);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__6) {
        setState(470);
        arraySizeDeclaration();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(473);
      closureType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(474);
      pointer();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(475);
      ref();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(477);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
        setState(476);
        typeQualifier();
      }
      setState(480);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Struct) {
        setState(479);
        match(OrcParser::Struct);
      }
      setState(482);
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
    setState(485);
    match(OrcParser::T__3);
    setState(486);
    type();
    setState(487);
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
    setState(489);
    type();
    setState(491);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(490);
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
    setState(493);
    match(OrcParser::T__53);
    setState(494);
    match(OrcParser::T__0);
    setState(495);
    match(OrcParser::T__0);
    setState(496);
    match(OrcParser::Id);
    setState(497);
    match(OrcParser::T__2);
    setState(498);
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
    setState(500);
    type();
    setState(501);
    argumentsDeclaration();
    setState(505);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == OrcParser::T__53) {
      setState(502);
      attribute();
      setState(507);
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
    setState(508);
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
    setState(511);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
      setState(510);
      typeQualifier();
    }
    setState(518);
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
        setState(513);
        primitiveType();
        break;
      }

      case OrcParser::Struct:
      case OrcParser::Id: {
        setState(515);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == OrcParser::Struct) {
          setState(514);
          match(OrcParser::Struct);
        }
        setState(517);
        match(OrcParser::Id);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(533); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(523);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 1099511627783) != 0)) {
        setState(520);
        typeQualifier();
        setState(525);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(526);
      match(OrcParser::T__12);
      setState(530);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(527);
          typeQualifier(); 
        }
        setState(532);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      }
      setState(535); 
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
    setState(538);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Struct) {
      setState(537);
      match(OrcParser::Struct);
    }
    setState(540);
    match(OrcParser::Id);
    setState(541);
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
    setState(566);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(543);
      match(OrcParser::T__58);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(544);
      match(OrcParser::T__59);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(545);
      match(OrcParser::T__60);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(546);
      match(OrcParser::T__61);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(547);
      match(OrcParser::T__62);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(548);
      match(OrcParser::T__63);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(549);
      match(OrcParser::Void);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(550);
      match(OrcParser::T__64);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(551);
      match(OrcParser::T__64);
      setState(552);
      match(OrcParser::T__64);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(553);
      match(OrcParser::T__64);
      setState(554);
      match(OrcParser::T__61);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(555);
      match(OrcParser::T__65);
      setState(556);
      match(OrcParser::T__62);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(557);
      match(OrcParser::T__65);
      setState(558);
      match(OrcParser::T__58);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(559);
      match(OrcParser::T__65);
      setState(560);
      match(OrcParser::T__59);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(561);
      match(OrcParser::T__65);
      setState(562);
      match(OrcParser::T__64);
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(563);
      match(OrcParser::T__65);
      setState(564);
      match(OrcParser::T__64);
      setState(565);
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
    setState(568);
    match(OrcParser::Enum);
    setState(569);
    match(OrcParser::Id);
    setState(570);
    match(OrcParser::T__51);
    setState(571);
    enumItem();
    setState(576);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(572);
        match(OrcParser::T__1);
        setState(573);
        enumItem(); 
      }
      setState(578);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    }
    setState(580);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__1) {
      setState(579);
      match(OrcParser::T__1);
    }
    setState(582);
    match(OrcParser::CloseBrace);
    setState(583);
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
    setState(585);
    match(OrcParser::Id);
    setState(588);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::T__36) {
      setState(586);
      match(OrcParser::T__36);
      setState(587);
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
    setState(590);
    match(OrcParser::Extension);
    setState(591);
    match(OrcParser::Id);
    setState(592);
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
    setState(594);
    match(OrcParser::T__51);
    setState(598);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70371176906759) != 0)) {
      setState(595);
      methodDeclaration();
      setState(600);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(601);
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
    setState(603);
    match(OrcParser::Class);
    setState(605);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Refc) {
      setState(604);
      match(OrcParser::Refc);
    }
    setState(607);
    match(OrcParser::Id);
    setState(610);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Extends) {
      setState(608);
      match(OrcParser::Extends);
      setState(609);
      match(OrcParser::Id);
    }
    setState(612);
    classDefinitionBlock();
    setState(613);
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
    setState(615);
    match(OrcParser::T__51);
    setState(620);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 70371176906759) != 0)) {
      setState(618);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
      case 1: {
        setState(616);
        classFieldDeclaration();
        break;
      }

      case 2: {
        setState(617);
        methodDeclaration();
        break;
      }

      default:
        break;
      }
      setState(622);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(623);
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
    setState(641);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(625);
      type();
      setState(626);
      match(OrcParser::Id);
      setState(628);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
      case 1: {
        setState(627);
        arraySizeDeclaration();
        break;
      }

      default:
        break;
      }
      setState(631);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
      case 1: {
        setState(630);
        assignRightPart();
        break;
      }

      default:
        break;
      }
      setState(633);
      eos();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(635);
      functionPointerVarDeclaration();
      setState(637);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
      case 1: {
        setState(636);
        assignRightPart();
        break;
      }

      default:
        break;
      }
      setState(639);
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
    setState(645);
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
        setState(643);
        functionDefinition();
        break;
      }

      case OrcParser::Extern: {
        enterOuterAlt(_localctx, 2);
        setState(644);
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
    setState(647);
    match(OrcParser::T__36);
    setState(648);
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
    setState(655);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(650);
      type();
      setState(652);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Id) {
        setState(651);
        match(OrcParser::Id);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(654);
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
    setState(673);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(657);
      match(OrcParser::T__0);
      setState(666);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & -324259173170675696) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & 70370908471303) != 0)) {
        setState(658);
        argumentDeclaration();
        setState(663);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(659);
            match(OrcParser::T__1);
            setState(660);
            argumentDeclaration(); 
          }
          setState(665);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
        }
      }
      setState(669);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::T__1) {
        setState(668);
        match(OrcParser::T__1);
      }
      setState(671);
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
    setState(675);
    type();
    setState(676);
    match(OrcParser::T__0);
    setState(678); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(677);
      match(OrcParser::T__12);
      setState(680); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == OrcParser::T__12);
    setState(683);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == OrcParser::Id) {
      setState(682);
      match(OrcParser::Id);
    }
    setState(685);
    match(OrcParser::T__2);
    setState(686);
    argumentsDeclaration();
    setState(690);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(687);
        attribute(); 
      }
      setState(692);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
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
    setState(693);
    type();
    setState(694);
    match(OrcParser::Id);
    setState(695);
    argumentsDeclaration();
    setState(696);
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
  enterRule(_localctx, 100, OrcParser::RuleGlobalFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(706);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(699);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(698);
        match(OrcParser::Static);
      }
      setState(701);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(703);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == OrcParser::Static) {
        setState(702);
        match(OrcParser::Static);
      }
      setState(705);
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
  enterRule(_localctx, 102, OrcParser::RuleGlobalVarDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(708);
    varDeclaration();
    setState(709);
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
  enterRule(_localctx, 104, OrcParser::RuleExternFunctionDeclaration);

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
    match(OrcParser::Extern);
    setState(712);
    type();
    setState(713);
    match(OrcParser::Id);
    setState(714);
    argumentsDeclaration();
    setState(715);
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
  enterRule(_localctx, 106, OrcParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(727);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::Import: {
        enterOuterAlt(_localctx, 1);
        setState(717);
        match(OrcParser::Import);
        setState(718);
        match(OrcParser::T__12);
        setState(719);
        match(OrcParser::From);
        setState(720);
        match(OrcParser::StringLiteral);
        setState(721);
        eos();
        break;
      }

      case OrcParser::T__66: {
        enterOuterAlt(_localctx, 2);
        setState(722);
        match(OrcParser::T__66);
        setState(723);
        match(OrcParser::T__12);
        setState(724);
        match(OrcParser::From);
        setState(725);
        match(OrcParser::StringLiteral);
        setState(726);
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
  enterRule(_localctx, 108, OrcParser::RuleIncludeStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(729);
    match(OrcParser::T__67);
    setState(730);
    includePathCharacters();
    setState(731);
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
  enterRule(_localctx, 110, OrcParser::RuleIncludePathCharacters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(742);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case OrcParser::T__23: {
        enterOuterAlt(_localctx, 1);
        setState(733);
        match(OrcParser::T__23);
        setState(737);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & -33554434) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & 4503599627370495) != 0)) {
          setState(734);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == OrcParser::T__24)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(739);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(740);
        match(OrcParser::T__24);
        break;
      }

      case OrcParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(741);
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
  enterRule(_localctx, 112, OrcParser::RulePackageStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(744);
    match(OrcParser::T__68);
    setState(745);
    match(OrcParser::Id);
    setState(746);
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
  enterRule(_localctx, 114, OrcParser::RuleLiteral);
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
    setState(748);
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
  enterRule(_localctx, 116, OrcParser::RuleEos);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(754);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(750);
      match(OrcParser::T__50);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(751);
      match(OrcParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(752);

      if (!(this->lineTerminatorAhead())) throw FailedPredicateException(this, "this->lineTerminatorAhead()");
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(753);

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
    case 58: return eosSempred(antlrcpp::downCast<EosContext *>(context), predicateIndex);

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
