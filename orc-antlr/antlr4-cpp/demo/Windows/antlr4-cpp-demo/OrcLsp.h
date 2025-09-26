#pragma once


#include <iostream>

#include "antlr4-runtime.h"
#include "OrcLexer.h"
#include "OrcParser.h"
#include "OrcBaseVisitor.h"

#include <Windows.h>
#include "Symbol.h"
#include <Project.h>
#include "FsUtil.h"
#include "md5.h"
#include <setjmp.h>
#include <conio.h>
using namespace nlohmann;

#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using namespace antlr4;



class OrcLsp
{
public:

	void run();
};

