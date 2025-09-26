/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

 //
 //  main.cpp
 //  antlr4-cpp-demo
 //
 //  Created by Mike Lischke on 13.03.16.
 //

#include <iostream>

#include "antlr4-runtime.h"
#include "OrcLexer.h"
#include "OrcParser.h"
#include "OrcBaseVisitor.h"
#include "ActorByThread.h"

#include <Windows.h>
#include "Symbol.h"
#include <Project.h>
#include "FsUtil.h"
#include "md5.h"
#include <setjmp.h>
#include <conio.h>
#include <OrcLsp.h>
#include "./CodeCompletionCore.hpp"
#include "./CodeCompletion.h"

using namespace nlohmann;


#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using namespace antlr4;


class  MyOrcVisitor : public OrcBaseVisitor {
public:
	std::shared_ptr<TokenStreamRewriter> rewriter = nullptr;

	std::string code;
	virtual std::any visitStatement(OrcParser::StatementContext* ctx) override {
		printf("visit statement %s\n", ctx->getText().c_str());
		return visitChildren(ctx);
	}

	virtual std::any visitProgram(OrcParser::ProgramContext* ctx) override {
		printf("visitProgram  %s\n", ctx->getText().c_str());
		return visitChildren(ctx);
	}

	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override {
		printf("visitClassDefinition %s\n", ctx->getText().c_str());
		return visitChildren(ctx);
	}
	virtual std::any visitRef(OrcParser::RefContext* ctx) override {
		visitChildren(ctx);

		rewriter->replace(
			ctx->getStart(), ctx->getStop(), 
			std::string("URGC_VAR_CLEANUP ") + ctx->Id()->getText() + " *");

		//code += 
		//	ctx->Id()->getText() + 
		//	"*";

		return defaultResult();
	}
};


class NoRecoveryErrorStrategy : public ANTLRErrorStrategy
{
public:

	virtual void reset(Parser* recognizer) {}

	virtual Token* recoverInline(Parser* recognizer) {
		return NULL;
	}
	virtual void recover(Parser* recognizer, std::exception_ptr e) {}

	virtual void sync(Parser* recognizer) {}
	virtual bool inErrorRecoveryMode(Parser* recognizer) { return false; }

	/// <summary>
	/// This method is called by when the parser successfully matches an input
	/// symbol.
	/// </summary>
	/// <param name="recognizer"> the parser instance </param>
	virtual void reportMatch(Parser* recognizer) {}

	/// <summary>
	/// Report any kind of <seealso cref="RecognitionException"/>. This method is called by
	/// the default exception handler generated for a rule method.
	/// </summary>
	/// <param name="recognizer"> the parser instance </param>
	/// <param name="e"> the recognition exception to report </param>
	virtual void reportError(Parser* recognizer, const RecognitionException& e) {}
};

class Test {
public:
	std::shared_ptr<ANTLRInputStream> input;
	std::shared_ptr<OrcLexer> lexer;
	std::shared_ptr<CommonTokenStream> tokens;
	std::shared_ptr<OrcParser> parser;
	
	Test* init(const char *str) {
		input = std::make_shared<ANTLRInputStream>(str);
		lexer = std::make_shared<OrcLexer>(input.get());
		tokens = std::make_shared<CommonTokenStream>(lexer.get());

		auto tokenStr = tokens->getText();
		std::cout << "Parse tokens: " << tokenStr << std::endl;
		auto tokenVec = tokens->getTokens();
		for (auto token : tokenVec) {
			std::cout << "\t" << token->getType() << ":" << token->getText() << std::endl;
		}

		parser = std::make_shared<OrcParser>(tokens.get());


		auto errStrategy= std::make_shared<NoRecoveryErrorStrategy>();
		parser->setErrorHandler(errStrategy);

		return this;
	}

	void printTree(
		tree::ParseTree* tree) {
		auto s = tree->toStringTree(this->parser.get(), true);
		
		std::cout << "Parse Tree: " << s << std::endl;
	}
};
std::shared_ptr<Test> mkTest(const char* str) {
	auto ret = std::make_shared<Test>();
	ret->init(str);
	return ret;
}
int main2(int argc, const char* argv[]) {
	SetConsoleOutputCP(65001);
	printf("你好\n");

	Symbol$registerMetas();


	char buf[1024];
	GetCurrentDirectoryA(sizeof(buf), buf);
	printf("cwd:%s\n", buf);
	//ANTLRInputStream input("a = b + \"c\";(((x * d))) * e + f; a + (x * (y ? 0 : 1) + z);");
	auto str = "char *data";
	str = "package SuiCore";
	str = "package SuiCore;";
	str = "#include 'stdio.h';";

	str = "#include 'stdio.h'";
	str = "#include <stdio.h>";
	//ANTLRInputStream input(R"(char *data)");
	/*ANTLRInputStream input(str);
	OrcLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	OrcParser parser(&tokens);
	tree::ParseTree* tree = parser.includeStatement();

	auto s = tree->toStringTree(&parser);
	std::cout << "Parse Tree: " << s << std::endl;*/

	std::shared_ptr<Test> t;
	antlr4::tree::ParseTree* tree = NULL;

	//t = mkTest("package SuiCore"); t->printTree(t->parser->packageStatement());
	if (1) {

		t = mkTest(R"(^void onActive(MenuNativeItem *item){
	})"); t->printTree(t->parser->closureExpression());

		t = mkTest(R"(
void hi(){
	^void onActive(MenuNativeItem *item){
	}
}
)"); t->printTree(t->parser->functionDefinition());

		t = mkTest("User@ type = str(item)"); t->printTree(t->parser->varDeclaration());
		//t = mkTest("type"); t->printTree(t->parser->singleExpression());
		t = mkTest("char _key[256]"); t->printTree(t->parser->classFieldDeclaration());

    
		t = mkTest("const _float_const"); t->printTree(t->parser->type());
		t = mkTest("Object*(*)()"); t->printTree(t->parser->functionPointerVarDeclaration());
		t = mkTest("#include \"stdio.h\""); t->printTree(t->parser->includeStatement());
		t = mkTest("import \"stdio.h\""); t->printTree(t->parser->importStatement());
		t = mkTest("1"); t->printTree(t->parser->literal());
		t = mkTest("\"sdf\""); t->printTree(t->parser->literal());
		t = mkTest("null"); t->printTree(t->parser->literal());
		t = mkTest("true"); t->printTree(t->parser->literal());
		t = mkTest("false"); t->printTree(t->parser->literal());
		t = mkTest("'a'"); t->printTree(t->parser->literal());
		t = mkTest("'\\u0020'"); t->printTree(t->parser->literal());

		t = mkTest("1+1"); t->printTree(t->parser->singleExpression());
		t = mkTest("1*2"); t->printTree(t->parser->singleExpression());
		t = mkTest("1/2+1"); t->printTree(t->parser->singleExpression());
		t = mkTest("1+1*4"); t->printTree(t->parser->singleExpression());
		t = mkTest("1+2*3+2"); t->printTree(t->parser->singleExpression());
		t = mkTest("++i"); t->printTree(t->parser->singleExpression());
		t = mkTest("--i"); t->printTree(t->parser->singleExpression());
		t = mkTest("i++"); t->printTree(t->parser->singleExpression());
		t = mkTest("i--"); t->printTree(t->parser->singleExpression());
		t = mkTest("!i"); t->printTree(t->parser->singleExpression());
		t = mkTest("a = 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("a = 1+2"); t->printTree(t->parser->singleExpression());
		t = mkTest("a += 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("a /= 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("a == 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("a > 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("a != 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("a | 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("a >> 1"); t->printTree(t->parser->singleExpression());
		t = mkTest("~a"); t->printTree(t->parser->singleExpression());
		t = mkTest("(1, 2, 3)"); t->printTree(t->parser->singleExpression());
		t = mkTest("b = a = 1"); t->printTree(t->parser->singleExpression());

		t = mkTest("(1, 2, 3,)"); t->printTree(t->parser->arguments());
		t = mkTest("(a, 2*3, 3,)"); t->printTree(t->parser->arguments());
		t = mkTest("a()"); t->printTree(t->parser->singleExpression());
		t = mkTest("a(2,)"); t->printTree(t->parser->singleExpression());
		t = mkTest("a(2,c)"); t->printTree(t->parser->singleExpression());

		t = mkTest("int a = 1"); t->printTree(t->parser->varDeclaration());
		t = mkTest("int a = 1;"); t->printTree(t->parser->varDeclaration());
		t = mkTest("int a;"); t->printTree(t->parser->varDeclaration());
		t = mkTest("User user;"); t->printTree(t->parser->varDeclaration());
		t = mkTest("User *user;"); t->printTree(t->parser->varDeclaration());
		t = mkTest("User * const user;"); t->printTree(t->parser->varDeclaration());
		t = mkTest("User @user;"); t->printTree(t->parser->varDeclaration());

		t = mkTest("if 1 {}"); t->printTree(t->parser->selectionStatement());
		t = mkTest("if 1 {} else {}"); t->printTree(t->parser->selectionStatement());
		t = mkTest("if 1 {} else if 0 {} else {}"); t->printTree(t->parser->selectionStatement());
		t = mkTest("if 1 {} else if 0 {} else if 0 {} else {}"); t->printTree(t->parser->selectionStatement());

		t = mkTest("if (1) {}"); t->printTree(t->parser->selectionStatement());

		t = mkTest("for ; ; {}"); t->printTree(t->parser->iterationStatement());
		t = mkTest("for (int i = 0; i < 10 ; i++) {}"); t->printTree(t->parser->iterationStatement());
		t = mkTest("while 1 {}"); t->printTree(t->parser->iterationStatement());



		t = mkTest(R"(enum Type{
		Type_a = 1,
		Type_b,
	})"); t->printTree(t->parser->enumDefinition());

		t = mkTest(R"(enum Type{
		Type_a,
		Type_b,
	})"); t->printTree(t->parser->enumDefinition());
		t = mkTest(R"(enum Type{
		Type_a,
	})"); t->printTree(t->parser->enumDefinition());
		t = mkTest(R"(enum Type{
		Type_a
	})"); t->printTree(t->parser->enumDefinition());
		t = mkTest(R"(enum Type{
		Type_a = 2
	})"); t->printTree(t->parser->enumDefinition());

		t = mkTest(R"(struct Type{
		int a
	})"); t->printTree(t->parser->structDefinition());
		t = mkTest(R"(struct Type{
		int b
		float a
		char *name
	})"); t->printTree(t->parser->structDefinition());
		t = mkTest(R"(struct Type{
	})"); t->printTree(t->parser->structDefinition());

		t = mkTest(R"(class User{
	})"); t->printTree(t->parser->classDefinition());
		t = mkTest(R"(class User extends Goo{
	})"); 
		t->printTree(t->parser->classDefinition());

		t = mkTest(R"(class User extends Goo{
		int age;
		char *name
		User@ kid
		User* parent = null
	})"); t->printTree(t->parser->classDefinition());


		t = mkTest(R"(void say(){})");  t->printTree(t->parser->functionDefinition());
		t = mkTest(R"(void say(int a){})");  t->printTree(t->parser->functionDefinition());
		t = mkTest(R"(char* say(int a){})");  t->printTree(t->parser->functionDefinition());
		t = mkTest(R"(char* say(int a, int b){})");  t->printTree(t->parser->functionDefinition());
		t = mkTest(R"(char* say(int a, int b, char *data){})");  t->printTree(t->parser->functionDefinition());
		t = mkTest(R"(extern char* say(int a, int b, char *data))");  t->printTree(t->parser->externFunctionDeclaration());

		t = mkTest(R"(class User extends Goo{
		int age;
		char *name
		User@ kid
		User* parent = null
		void say(){
		}
		int level;
		void nice(){
		}
		extern int _outSay()
		int level
	})"); t->printTree(t->parser->classDefinition());

		t = mkTest(R"(extension User {
		void nice(){
		}
		int nice2(){
		}
		extern int _outSay()
	})"); t->printTree(t->parser->extensionDefinition());

		t = mkTest(R"(int a)");  t->printTree(t->parser->statement());
		t = mkTest(R"(int a=1)");  t->printTree(t->parser->statement());
		t = mkTest(R"(a=1)");  t->printTree(t->parser->statement());
		t = mkTest(R"(if 1 {a=1})");  t->printTree(t->parser->statement());
		t = mkTest(R"({if 1 {a=1}  int a; int c = 234})");  t->printTree(t->parser->block());


		t = mkTest(R"(void say(){if 1 {a=1}  int a; int c = 234})");  t->printTree(t->parser->functionDefinition());
		t = mkTest(R"(extension User {void say(){if 1 {a=1}  int a; int c = 234}})");  t->printTree(t->parser->extensionDefinition());

		t = mkTest(R"(class User {void say(){if 1 {a=1}  int a; int c = 234}})");  t->printTree(t->parser->classDefinition());

		t = mkTest(R"(class User {
		int age
		char *name
		User@ parent = null
		void print(){
			printf("hi\n")
		}
		void say(){
			if 1 {
				a=1
			}  
			int a; 
			int c = 234
		}
	})");  t->printTree(t->parser->classDefinition());
	
		t = mkTest(R"(user~{})");  t->printTree(t->parser->scopeStatement());
		t = mkTest(R"(mkDiv(o, 0)~{})");  t->printTree(t->parser->scopeStatement());
		t = mkTest(R"(^void(){})");  t->printTree(t->parser->singleExpression());
		t = mkTest(R"(^void onHi(){})");  t->printTree(t->parser->singleExpression());

		t = mkTest(R"(a = "sdfsd")");  t->printTree(t->parser->singleExpression());
		t = mkTest(R"(a = 's')");  t->printTree(t->parser->singleExpression());

		t = mkTest(R"(static char a = 's')");  t->printTree(t->parser->globalVarDeclaration());
		t = mkTest(R"(static char say(){})");  t->printTree(t->parser->globalFunctionDefinition());
		t = mkTest(R"(extern char say())");  t->printTree(t->parser->globalFunctionDefinition());

		t = mkTest(R"((int)a)");  t->printTree(t->parser->singleExpression());

		t = mkTest(R"((long)1.0f)");  t->printTree(t->parser->singleExpression());

		t = mkTest(R"(a = (long)1.0f)");  t->printTree(t->parser->singleExpression());

		t = mkTest(R"(user.{})");  t->printTree(t->parser->scopeStatement());

		t = mkTest(R"(new User())");  t->printTree(t->parser->singleExpression());
		t = mkTest(R"(new User(1,2,'s',))");  t->printTree(t->parser->singleExpression());

		t = mkTest(R"(*a)");  t->printTree(t->parser->singleExpression());

		t = mkTest(R"(break)");  t->printTree(t->parser->statement());
		t = mkTest(R"(continue)");  t->printTree(t->parser->statement());

		t = mkTest(R"(return 1)");
		tree = t->parser->statement();
		t->printTree(tree);


	}

	if (0) {

		t = mkTest(R"(
	package SuiCore
	#include "stdio.h"
	#include <string.h>
	import * from "a.orc"

	enum Type{
		Type_id = 10,
		Type_name
	}
	void goo(int a, int sdk){
		int i = 10 + 1;
		int b = 12 * 3 + 2;
	}
	extern void googo();
	static int getAge(){
		return 0;
	}

	static void getAge2(){
		printf("slkfjd");
		printf("slkfjd:%d", 1);
		printf("slkfjd");
	}
	extension User{
		void extensionFunction(){
		printf("slkfjd");
		}
		void extensionFunction2(){
		printf("slkfjd");
		}
		extern void externExtensionFunction()
	}
	struct Nake{
		int a
		bool isOk
		void (*a)()
	}
	int a;
	static int b = 10 + 1;

	class User {
		int age
		char *name
		User@ parent = null
		void print(){
			printf("hi\n")
		}

		void say(){
			if 1 {
				a=1
			}  
			int a; 
			int /*asdf*/c = 234

			//lala  
			User@ u = null;
			u.age = 10
		}
		User@ returnSelf(){
			return self;
		}
	}
	User@ getUser(){}
	extern User@ getUser2()

	)");  
		tree = t->parser->program();
		t->printTree(tree);

		/*MyOrcVisitor vis;
		vis.rewriter = std::make_shared<TokenStreamRewriter>(t->tokens.get());
		vis.visit(tree);
		printf("code:%s\n", vis.code.c_str());
		printf("code:%s\n", vis.rewriter->getText().c_str());*/


		SymbolSpace::fulfillFullname(tree);

		SymbolSpace::build("a.orc", tree, t->parser);


	}

	t = mkTest(R"(
package SuiCore
//#include "stdio.h"
//#include <string.h>
//import * from "a.orc" 
//
//int a = 0;
//int b;
//short count = 123
//long long veryLongValue = 3423420398
//char *name = "sdf";
//double pricision = 1.23
//float dis = 3.0
//
//static bool isOk = false;	
//
//static void staticHi(){
//}
//struct User {
//	int age;
//char *name;
//};


struct ScopeData{
    void * data;
    void * onExitScope;
};

class Super{
	int superLevel = 0;
	void superSay(){
	}
	ScopeData __exit__(){
		ScopeData xx;
		return b;
	}
}
class User2 extends Super{
	int age = 10;
	char *name;
	//int superLevel = 0;
	void say(){
	}
	int getAge(){
	}
	void superSay(){
	}
}
//extension User {
//	void saySomething(){
//	}
//}

extension User2 {
	void saySomething(){
	}
}
//enum UserType {
//	UserType_ok,
//	UserType_no = 2,
//}
//int add(int a, int b){
//return a + b
//}
//int getArg(){
//	return 10;
//}
//char *getName(){
//	return "hi";
//}
User2@ newUser2(){
	return new User2()
}
long long hi(User@ tmp){
	//int a;
	//static int b = 12;
	//a = 10 + 1 * 3 + (234 % 34 * (2 + 3 / 4));
	//b = 343 + 23 * a;
	//staticHi()
	//invalidFn()
	//int result = add(getArg(), 10)
	//char *astr = (char *)&a;
	//if (1) {
	//	int a = 23
	//} else if 0{
	//} else if 1{
	//} else {
	//	if 0 {
	//		int a = 23
	//
	//	} else {
	//		int a = 23
	//	}
	//}
	//while 1 {
	//	break;
	//	continue;
	//}
	//for int i = 10; i < 10; i++ {
	//}


	User2@ user = null;
	User2@ user = new User2();
	//user = new User2();
	//user.saySomething();
	int age = user.getAge()
	user->getAge()
	int age2 = user->getAge()
	User@ u2 = newUser2()
	int age2 = newUser2()->getAge();
	int l = user.superLevel
	user.superSay()

	user.{
		int l2 = o.superLevel;
	}
	return 34;
}


	)");

	t = mkTest(R"(
package SuiCore

struct Padding {
	int left;
	float top;
	unsigned int bottom;
	unsigned long long right;
}
class User {
	int age
}
class A{
	Padding padding;
	User@ user;
	Padding * tmpPadding;
	
	int a  = 10;
	void say(){
	}
}

void hi(){
	int i = 10;
	//i = 1;
	//int d = i * 2;
	^ void cb(){
		i = 102;
	}
	//i = 12;
	//int b = i * 2;
	//if i  {
	//	i = i * 3;
	//}
}


	)");
	//tree = t->parser->program();
	//t->printTree(tree);


	auto testType = [](std::string code) {
		auto t = mkTest(code.c_str());
		auto tree = t->parser->type();
		printf("============%s:\n", code.c_str());
		t->printTree(tree);
	};

	auto testFnType = [](std::string code) {
		auto t = mkTest(code.c_str());
		auto tree = t->parser->functionType();
		printf("============%s:\n", code.c_str());
		t->printTree(tree);
	};

	testType("char");
	testType("bool");
	testType("short");
	testType("int");
	testType("long");
	testType("long long");
	testType("unsigned char");
	testType("unsigned short");
	testType("unsigned int");
	testType("unsigned long");
	testType("unsigned long long");
	testType("float");
	testType("double");
	testType("char *");
	testType("unsigned char *");
	testType("int *");
	testType("unsigned int *");
	testType("void *");
	testType("void");
	testType("unsigned int **");

	testType("struct _User");
	testType("struct _User *");
	testType("struct _User **");
	testType("_User");
	testType("_User *");
	testType("_User **");
	testType("_User@");
	testType("struct _User@");
	testFnType("void ()");
	testFnType("char ()");
	testFnType("char *()");
	testFnType("void (int)");
	testFnType("char (int)");
	testFnType("char *(int)");
	testFnType("void (int, char *)");
	testFnType("char (int, char *, char *)");
	testFnType("char *(int, char *, char *, char *)");
	testFnType("char **(int, char *, char *)");
	testFnType("char ***(int, char *, char *, char *)");
	testFnType("User ***(int, char *, char *, char *)");
	testFnType("struct User ***(int, char *, char *, char *)");
	testFnType("const struct User ***(int, char *, char *, char *)");
	testFnType("const struct User ***(int, const char *, char *, char *)");
	testFnType("const struct User ***(int, const char *, const char *, const char *)");
	testFnType("const struct User ***(int, const char const *, const char *, const char *)");

	testType("long double");
	testFnType("char *(int, char *, char *, char *) __attribute__((cdel))");



	/*MyOrcVisitor vis;
	vis.rewriter = std::make_shared<TokenStreamRewriter>(t->tokens.get());
	vis.visit(tree);
	printf("code:%s\n", vis.code.c_str());
	printf("code:%s\n", vis.rewriter->getText().c_str());*/

	//SymbolSpace::fulfillFullname(tree);
	//SymbolSpace::build("a.orc", tree, t->parser);


	// 序列化反序列化
	SymbolTypePrimitiveType pt;
	pt.typeName = "unsigned char";
	auto jo = dumpJson(&pt);
	printf("jo:%s\n", jo.dump().c_str());
	auto tmpJo = parseJsonToObject(jo);

	auto arrText = "[" + jo.dump() + "]";
	auto ja = nlohmann::json::parse(arrText);
	std::vector<std::shared_ptr<SymbolType>> vec;
	parseJsonToObjectArray(ja, vec);

	//SymbolSpace::buildFromAstJson("", "");

	std::filesystem::path p("/a/b/c.d");
	printf("dir:%s\n", p.parent_path().string().c_str());

	std::filesystem::path orcPath_fs("/a/b/c.d");
	auto tmpCPath = orcPath_fs.parent_path() / (orcPath_fs.stem().string() + "-tmp.c");
	printf("dir:%s\n", tmpCPath.string().c_str());


	printf("stem:%s\n", std::filesystem::path("/a/b/stdio.h").stem().string().c_str());
	////p.replace_filename(p.filename().string() + "-tmp");// .replace_extension(".c");
	//p.replace_filename(
	//	p.stem().string() + "-tmp.c"
	//);
	//printf("path:%s\n", p.string().c_str());

	SymbolSpace::buildSymbolSpace_forInclude("a.orc", "stdlib.h", "#include <stdlib.h>", nullptr);

	Project project;
	//project.watch("./");

	return 0;
}


void compile_withLoader(std::string path, std::shared_ptr< SymbolSpaceLoader> loader) {
	auto code = FsUtil::read_all_text(path);
	printf("%s code:\n%s\n\n", path.c_str(), code.c_str());


	std::shared_ptr<ANTLRInputStream> input;
	std::shared_ptr<OrcLexer> lexer;
	std::shared_ptr<CommonTokenStream> tokens;
	std::shared_ptr<OrcParser> parser;


	input = std::make_shared<ANTLRInputStream>(code);
	lexer = std::make_shared<OrcLexer>(input.get());
	tokens = std::make_shared<CommonTokenStream>(lexer.get());


	parser = std::make_shared<OrcParser>(tokens.get());


	auto tree = parser->program();

	CostUs cost;

	auto space = std::make_shared<SymbolSpace>();
	space->symbolSpaceLoader = loader;
	space->path = path;
	space->startBuild(path, tree, parser, cost);
}

void compile(std::string path) {
	auto code = FsUtil::read_all_text(path);
	auto loader = std::make_shared<SymbolSpaceLoader>();
	compile_withLoader(path, loader);
	compile_withLoader(path, loader);
}
/*
测试步骤
读取文件，解析生成.h/.c

*/
void test() {
	//compile("orc/Package.orc");
	//compile("orc/Include.orc");
	//compile("orc/GlobalVar.orc");
	//compile("orc/GlobalFunc.orc");
	//compile("orc/Struct.orc");
	//compile("orc/StructWithExtension.orc");
	//compile("orc/StructWithExtension.orc");
	//compile("orc/Enum.orc");
	//compile("orc/StructFields.orc");
	//compile("orc/StaticVar.orc");
	//compile("orc/StaticFunc.orc");
	//compile("orc/VarDecl.orc");
	//compile("orc/Extension.orc");
	//compile("orc/ExtensionFunc.orc");
	//compile("orc/Class.orc");
	//compile("orc/ClassExtends.orc");
	//compile("orc/classExtern.orc");
	//compile("orc/ClassField.orc");
	//compile("orc/UrgcRef.orc");

	//compile("orc/If.orc");
	//compile("orc/While.orc");
	//compile("orc/For.orc");
	//compile("orc/Break.orc");
	//compile("orc/binaryOpAndFunctionCall.orc");
	//compile("orc/Deref.orc");
	//compile("orc/NewExpr.orc");
	//compile("orc/PostUnaryOp.orc");
	//compile("orc/setExpr.orc");
	//compile("orc/typeConvert.orc");
	//compile("orc/unaryOp.orc");
	//compile("orc/Scope.orc");

	//compile("orc/Mod.orc");


	//compile("orc/accessProp.orc");
	//compile("orc/Include.orc");
	//compile("orc/Closure.orc");
	//compile("orc/Closure_Named_Assign.orc");
	//compile("orc/Closure_Named.orc");
	//compile("orc/Closure_VarDecl.orc");

	//compile("orc/FuncPointer_Var.orc");
	//compile("orc/FuncPointer_Struct.orc");
	//compile("orc/FuncPointer_Class.orc");

	//compile("orc/printf.orc");
	//compile("orc/Import.orc");
	compile("orc/Include.orc");
	
}
class JmpBuf {
public:
	jmp_buf env;
	bool jumpped = false;
};
std::vector<JmpBuf> envs;
class JmpPointGuard {
public:
	JmpBuf* jmpBuf;
	JmpPointGuard();
	~JmpPointGuard();
};
JmpPointGuard::JmpPointGuard() {
	envs.push_back(JmpBuf{});
	jmpBuf = &envs.back();
}
JmpPointGuard::~JmpPointGuard() {
	printf("~JmpPointGuard\n");
	envs.pop_back();
}
void longJmp(int val) {
	for (int i = envs.size() - 1; i >= 0; i--) {
		if (!envs[i].jumpped) {
			envs[i].jumpped = true;
			longjmp(envs[i].env, val);
		}
	}
	throw std::format("longJmp error. no envs");
}
void docleanup(int *v) {
	printf("docleanup:%d\n", *v);
}
void gogo() {
	__attribute__((cleanup(docleanup))) int tmpv = 10;
	//throwManager.longJmp(999);
	longJmp(343);
	printf("after long jmp\n");
}
void testThrow() {
	{
		//int jmpCode = setjmp(env);
		//if (jmpCode == 0) { //第一次
		//	printf("jmpCode == 0\n");
		//	gogo();
		//}
		//else {
		//	printf("jump others %d\n", jmpCode);
		//}
		JmpPointGuard jmpBuf;
		auto jmpCode = setjmp(jmpBuf.jmpBuf->env);
		if (jmpCode == 0) { //第一次
			printf("jmpCode == 0\n");
			JmpPointGuard j;
			auto c = setjmp(j.jmpBuf->env);
			if (c == 0) {
				printf("nest try\n");
				gogo();
			}
			else {
				printf("nest throw:%d\n", c);
				longJmp(c + 1);
			}
		}
		else {
			printf("jump others %d\n", jmpCode);
			//如果在这里继续pop
		}
		printf("finally  . jmppoint size:%d\n", envs.size());
	}
	printf("outer . jmppoint size:%d\n", envs.size());
}
int caretPosition2TokenIndex(std::shared_ptr<CommonTokenStream> tokens, int line, int character) {
	for (int i = 0, l = tokens->size() - 1; i < l; i++) {
		auto token = tokens->get(i);

		if (token->getLine() - 1 == line) {
			int c = token->getCharPositionInLine();
			int len = token->getText().size();
			if (c <= character && character <= c + len) {//同一行的最后一个token
				return i;
			}
		}
	}
	return 0;
}

tree::ParseTree* getParseTree_hasToken(tree::ParseTree *n, Token* token) {
	auto term = dynamic_cast<tree::TerminalNode*>(n);
	if (term) {
		if (term->getSymbol() == token) {
			return term;
		}
	}
	for (int i = 0; i < n->children.size(); i++) {
		auto kid = n->children[i];


		auto found = getParseTree_hasToken(kid, token);
		if (found) {
			return found;
		}
	}
	return NULL;
}
void testCompletion() {

	std::string code = R"(class User{
	int age
	void say(){
self.
	}
}
)";

	std::shared_ptr<ANTLRInputStream> input = std::make_shared<ANTLRInputStream>(code);
	std::shared_ptr<OrcLexer> lexer = std::make_shared<OrcLexer>(input.get());
	std::shared_ptr<CommonTokenStream> tokens = std::make_shared<CommonTokenStream>(lexer.get());
	std::shared_ptr<OrcParser> parser = std::make_shared<OrcParser>(tokens.get());



	auto tree = parser->program();
	auto tokenIndex = caretPosition2TokenIndex(tokens, 3, 5);
	auto token = tokens->get(tokenIndex);
	auto target = getParseTree_hasToken(tree, token);
	auto prevtoken = tokens->get(tokenIndex - 1);
	auto prevtarget = getParseTree_hasToken(tree, prevtoken);
	

	printf("测试代码完成 tokenIndex:%d, token:%s prev:%s\n", tokenIndex, token->getText().c_str(), prevtoken->getText().c_str());

	std::shared_ptr<c3::CodeCompletionCore> c3 = std::make_shared<c3::CodeCompletionCore>(parser.get());
	c3->preferredRules.insert( OrcParser::RuleSingleExpression );
	//c3->preferredRules.insert( OrcParser::RuleType);
	//c3->preferredRules.insert( OrcParser::RuleLiteral);
	//c3->preferredRules.insert( OrcParser::RuleTypeQualifier);
	//c3->preferredRules.insert( OrcParser::Id);
	auto cands = c3->collectCandidates(tokenIndex);
	
	for (auto it : cands.rules) {
		auto rule = it.first;
		if (rule == OrcParser::RuleSingleExpression) {

		}
	}
}
tree::ParseTree* getLastLeaf(tree::ParseTree *n) {
	if (n->children.size() == 0) {
		return n;
	}
	return getLastLeaf(n->children.back());
}
// 不使用c3。 可以令光标后的删除，然后生成ast树.  再根据最后一个子节点的类型，去判断要提示什么
// 同时如果要优化性能。。可以以statement为单位缓存，识别上一条statement的位置，从而明确当前statement的开始位置
// 去识别statement即可
// 不行啊。。 antlr4只在ast中放了个ErrorNode
void testCompletion2() {

	std::string code = R"(class User{
	int age
	void say(){
		self.a)";

	std::shared_ptr<ANTLRInputStream> input = std::make_shared<ANTLRInputStream>(code);
	std::shared_ptr<OrcLexer> lexer = std::make_shared<OrcLexer>(input.get());
	std::shared_ptr<CommonTokenStream> tokens = std::make_shared<CommonTokenStream>(lexer.get());
	std::shared_ptr<OrcParser> parser = std::make_shared<OrcParser>(tokens.get());


	auto tree = parser->program();
	auto tokenIndex = caretPosition2TokenIndex(tokens, 3, 7);
	auto token = tokens->get(tokenIndex);

	auto lastLeaf = getLastLeaf(tree);
	auto eos = dynamic_cast<OrcParser::EosContext*>(lastLeaf->parent);
	if (eos) {
		auto p = dynamic_cast<OrcRuleContext*>(eos->parent);
		p->removeChild(eos);
		lastLeaf = getLastLeaf(tree);
	}

	printf("测试代码完成 tokenIndex:%d, token:%s\n", tokenIndex, token->getText().c_str());
	printf("last leaf %s\n", lastLeaf->getText().c_str());

}

long WINAPI onUnhandledException(EXCEPTION_POINTERS *exceptionInfo) {
	MessageBoxW(NULL, L"崩溃了", L"提示", MB_ICONERROR|MB_DEFBUTTON1);
	return EXCEPTION_EXECUTE_HANDLER;
}
int main(int argc, const char* argv[]) {
	SetConsoleOutputCP(65001);
	// main2(argc, argv);
	//std::this_thread::sleep_for(std::chrono::seconds(5));

	SetUnhandledExceptionFilter(onUnhandledException);
	//int* a = NULL;
	//*a = 1;
	//printf("a:%d\n", a);

	if (0) { 
		test_ActorByThread();
		return 0;
	}
	if (0) {
		test_ContainPositionNodeStackVisitor();
		return 0;
	}
	if (0) {
		test_codeCompleteAtPosition_forDot();
		//test_Position_toCharIndex();
		return 0;
	}
	if (0) {
		testCompletion();
		return 0;
	}
	if (0) { //失败
		testCompletion2();
		return 0;
	}

	Symbol$registerMetas();
	//testThrow();

	/*
	参数格式
	exe cmd ...args
	*/
	std::string help = R"(
参数格式:
.exe cmd ...args

cmd指令如下所示。

# help 
显示帮助

# watch [dir]
# w [dir]
监听指定的目录[dir], 并在文件有变更时，重新编译
[dir]可以不填写， 默认为当前目录

# compile path/to/orc
# c path/to/orc
编译指定的文件[path/to/orc],并生成符号文件

)";
	do {
		//无参数，直接输出 help
		if (argc == 1) {
			if (1) {
				OrcLsp lsp;
				lsp.run();

				return 0;
			}

			printf("%s\n", help.c_str());
			break;
		}

		if (argc >= 2) {
			std::string cmd = argv[1];
			if (cmd == "lsp" || cmd == "-lsp") {
				std::this_thread::sleep_for(std::chrono::milliseconds(4000));

				//进入src目录
				Path cwd(FsUtil::getcwd());
				//如果当前目录不是src,且子目标有src,
				if (cwd.basename() != "src") {
					auto subsrc = cwd.append("src");
					if (subsrc.exists()) {
						FsUtil::setcwd(subsrc.path());
						auto nowcwd = FsUtil::getcwd();
						extern void log(std::string msg);
						log(std::format("nowcwd:{}\n", nowcwd));
					}
				}


				OrcLsp lsp;
				lsp.run();
				break;
			}

			if (cmd == "version") {
				auto version = std::string("0.8.1");
#ifdef NDEBUG
				printf("version:%s debug:0\n", version.c_str());
#else
				printf("version:%s debug:1\n", version.c_str());
#endif
				break;
			}
			if (cmd == "help") {
				printf("%s\n", help.c_str());
				break;
			}
			if (cmd == "watch" || cmd == "w") {
				std::string dir = ".";
				if (argc >= 3) {
					dir = argv[2];
				}

				auto absdir = Path(dir).getAbsolute().eliminateDotDir().path();
				printf("监听目录:%s; abs:%s\n", dir.c_str(), absdir.c_str());
				Project p;
				p.watch(absdir);
				break;
			}
			if (cmd == "recompileAll") {

				Project p;
				p.recompileAll();
				break;
			}
			if (cmd == "compile" || cmd == "c") {
				if (argc < 3) {
					printf("需要指定文件路径\n");
					break;
				}
				std::string path = argv[2];
				std::string abspath = path;
				if (!Path(abspath).isAbsolute()) {
					abspath = Path(FsUtil::getcwd()).append(abspath).path();
				}

				printf("编译:%s; 绝对路径为:%s\n", path.c_str(), abspath.c_str());

				Project p;
				p.compile(path);
				break;
			}

			{
				printf("未识别的指令\n");
				break;
			}
		}
	} while (0);

	//test();
	return 0;
}