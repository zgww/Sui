#pragma once


#include <iostream>

#include "antlr4-runtime.h"
#include "OrcLexer.h"
#include "OrcParser.h"
#include "OrcBaseVisitor.h"

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#endif
#include "Symbol.h"
#include <Project.h>
#include "FsUtil.h"
#include "md5.h"
#include <setjmp.h>
using namespace nlohmann;

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

using namespace antlrcpptest;
using namespace antlr4;



class OrcLsp
{
public:

	void run();
};

