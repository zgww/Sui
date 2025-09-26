#pragma once
#include <iostream>
#include "./Symbol.h"
#include "OrcBaseVisitor.h"
#include <filesystem>
#include "OrcLexer.h"

#include <Windows.h>
#include "md5.h"
#include "Closure.h"
#include <FsUtil.h>
#include <StrUtil.h>
#include "ReturnStringVisitor.h"
#include <GenOrcCodeVisitor.h>
#include <memory>
#include "./TypeCheckerVisitor.h"


#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using namespace antlr4;
using string = std::string;



class AstBuilder
{
public:
	std::shared_ptr<ANTLRInputStream> input;
	std::shared_ptr<OrcLexer> lexer;
	std::shared_ptr<CommonTokenStream> tokens;;
	std::shared_ptr<OrcParser> parser;

	std::string code;

	void initByCode(std::string code);
};

// 包含指定位置的 ast 节点栈
class  ContainPositionNodeStackVisitor : public OrcBaseVisitor {
public:
	std::vector < antlr4::tree::ParseTree* > nodeStack;
	Position position;

	bool containsPosition(OrcRuleContext* ctx);

	virtual std::any visitChildren(tree::ParseTree* node) override;
};

class CodeCompletion
{

public:
	std::string code;


	void initByCode(std::string code);

	//代码提示
	OrcParser::SingleExpressionContext* codeCompleteAtPosition_forDot(Position pos, AstBuilder& b);
};

void test_codeCompleteAtPosition_forDot();


void test_Position_toCharIndex();

void test_ContainPositionNodeStackVisitor();

int Position_toCharIndex(std::string code, Position pos);