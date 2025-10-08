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
#define _CRT_SECURE_NO_WARNINGS
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
#include "./TypeCheckerVisitor.h"


#include "./SymbolBuilderVisitor.h"


using namespace std; 
using namespace nlohmann;


#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using namespace antlr4;
using string = std::string;

OrcParser* gParser;
static int cnt_calcSymbolTypeOfExpr = 0;
static int cnt_calcSymbolTypeOfExprCache = 0;

static std::shared_ptr<SymbolDefinitionClass> gocSymbolDefinitionClass_Object(
	std::shared_ptr<SymbolSpaceLoader> loader);

std::wstring Utf8Util$acpToUtf16(char* str0)
{
	std::string str(str0);
	if (str == "") return (L"");

	// 计算缓冲区需要的大小, 如果函数成功, 则返回 UTF-8 字符数量, 所以无法确定具体字节数
	int cBuf = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (cBuf == 0) return (L"");

	wchar_t* buf = new wchar_t[cBuf * 4];// malloc(cBuf * 4);
	if (cBuf != MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buf, cBuf)) {
		delete[] buf;
		return L"";
	}
	std::wstring ret = buf;
	delete[] buf;
	return ret;
}

std::string Utf8Util$toUtf8(const wchar_t* str) {
#ifdef _WIN32
	if (str == L"") return "";
	// 计算缓冲区需要的大小, 如果函数成功, 则返回具体字节数, 所以 cBuf 至少是 1 (UTF-8以0x00结尾)
	int cBuf = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
	if (cBuf < 1) return ("");
	char* buf = new char[cBuf]; // 分配缓冲区
	if (cBuf != WideCharToMultiByte(CP_UTF8, 0, str, -1, buf, cBuf, NULL, NULL)) {
		delete[] buf;
		return ("");
	}
	std::string ret = buf;
	delete[] buf;
	return ret;
#else
	return "";
#endif
}
std::string Utf8Util$acpToUtf8(char* str0)
{
	auto wstr = Utf8Util$acpToUtf16(str0);
	auto ret = Utf8Util$toUtf8(wstr.c_str());
	return ret;
}

std::wstring Utf8Util$toUtf16(const char* str) {
#ifdef _WIN32
	if (str == "") return (L"");

	// 计算缓冲区需要的大小, 如果函数成功, 则返回 UTF-8 字符数量, 所以无法确定具体字节数
	int cBuf = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	if (cBuf == 0) return (L"(null)");
	wchar_t* buf = (wchar_t*)calloc(cBuf * 4, 1);// malloc(cBuf * 4);
	if (cBuf != MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, cBuf)) {
		delete[] buf;
		return (L"");
	}
	std::wstring ret = buf;
	delete [] buf;
	return ret;
#else//其他平台统一走utf8
	return _strdup_wstring(L"");
#endif
}
std::string Utf8Util$utf16ToAcp(const wchar_t* str) {
#ifdef _WIN32
	if (str == L"") return ("");
	// 计算缓冲区需要的大小, 如果函数成功, 则返回具体字节数, 所以 cBuf 至少是 1 (UTF-8以0x00结尾)
	int cBuf = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	if (cBuf < 1) return ("");
	char* buf = (char*)calloc(cBuf, 1); // 分配缓冲区
	if (cBuf != WideCharToMultiByte(CP_ACP, 0, str, -1, buf, cBuf, NULL, NULL)) {
		//delete[] buf;
		free(buf);
		return ("");
	}
	std::string ret = buf;
	delete[] buf;
	return ret;
#else
	return "";
#endif
}
std::string Utf8Util$utf8ToAcp(const char* str) {
	auto utf16 = Utf8Util$toUtf16(str);
	auto ret = Utf8Util$utf16ToAcp(utf16.c_str());
	return ret;
}
std::string FsUtil$read_all_text(const char* path2, const char* flag) {
	auto path = Utf8Util$utf8ToAcp(path2);
	//if (text_cache.find(path) != text_cache.end()) {
	//	return text_cache[path];
	//}

	FILE* f = fopen(path.c_str(), flag);

	if (f == NULL) {
		return ("");
	}
	char buf[10240] = { 0 };
	std::string content;
	while (!feof(f)) {
		int cnt = fread(buf, 1, sizeof(buf) - 1, f);
		buf[cnt] = 0;

		content += buf;
	}
	fclose(f);
	//text_cache[path] = content;
	return content;
}

void FsUtil$write_all_text(const char* path2, const char* content, const char* flag) {
	auto path = Utf8Util$utf8ToAcp(path2);
	FILE* f = fopen(path.c_str(), flag);
	if (f == NULL) {
		throw std::invalid_argument("EOpenFile");
	}

	fwrite(content, 1, strlen(content), f);
	fclose(f);
}

string genCode(antlr4::tree::ParseTree* ctx, std::shared_ptr<SymbolSpace> space);

string ast_primitiveTypeToText(OrcParser::PrimitiveTypeContext* ctx) {
	auto text = ctx->getText();
	if (text == "longlong") {
		return "long long";
	}
	if (text == "unsignedlonglong") {
		return "unsigned long long";
	}
	if (text == "unsignedchar") {
		return "unsigned char";
	}
	if (text == "unsignedshort") {
		return "unsigned short";
	}
	if (text == "unsignedint") {
		return "unsigned int";
	}
	if (text == "unsignedlong") {
		return "unsigned long";
	}
	return text;
}

//从类型声明中，提取最原始的类型名，去掉指针、引用、修饰等
//如User** => User
string ast_getNakeTypeName_fromTypeContext(OrcParser::TypeContext* type) {
	if (type) {
		if (type->Id()) {
			return type->Id()->getText();
		}
		if (type->pointer()) {
			return type->pointer()->Id()->getText();
		}
		if (type->ref()) {
			return type->ref()->Id()->getText();
		}
		if (type->primitiveType()) {
			return type->primitiveType()->getText();
		}

	}
	return "";
}
bool isNakeTypeName_isPrimitiveType(std::string typeName)
{
	//暂不考虑unsigned 
	if (
		typeName == "unsignedchar" ||
		typeName == "unsignedshort" ||
		typeName == "unsignedint" ||
		typeName == "unsignedlong" ||
		typeName == "unsignedlonglong" ||
		typeName == "unsignedlong long" ||

		typeName == "char" ||
		typeName == "short" ||
		typeName == "int" ||
		typeName == "bool" ||
		typeName == "void" ||
		typeName == "long" ||
		typeName == "longlong" ||
		typeName == "long long" ||
		typeName == "float" ||
		typeName == "double"

		)
	{
		return true;
	}
	return false;
}
std::shared_ptr<SymbolType> literalToSymbolType(OrcParser::LiteralContext* literal) {
	if (literal->NullLiteral()) {
		auto ret = std::make_shared<SymbolTypePointer>();
		ret->typeName = "Object";
		ret->pointerLevel = 1;
		return ret;
	}
	else if (literal->BooleanLiteral()) {
		auto ret = std::make_shared<SymbolTypePrimitiveType>();
		ret->typeName = "bool";
		return ret;
	}
	else if (literal->DecimalLiteral()) {
		auto ret = std::make_shared<SymbolTypePrimitiveType>();
		ret->typeName = "int";
		return ret;
	}
	else if (literal->HexIntegerLiteral()) {
		auto ret = std::make_shared<SymbolTypePrimitiveType>();
		ret->typeName = "int";
		return ret;
	}
	else if (literal->OctalIntegerLiteral()) {
		auto ret = std::make_shared<SymbolTypePrimitiveType>();
		ret->typeName = "int";
		return ret;
	}
	else if (literal->BinaryIntegerLiteral()) {
		auto ret = std::make_shared<SymbolTypePrimitiveType>();
		ret->typeName = "int";
		return ret;
	}
	else if (literal->StringLiteral()) {
		auto str = std::make_shared<SymbolTypePointer>();
		str->typeName = "char";
		str->pointerLevel = 1;
		return str;
	}
	else if (literal->CharLiteral()) {
		auto ret = std::make_shared<SymbolTypePrimitiveType>();
		ret->typeName = "char";
		return ret;
	}

	throw std::format("unknown literal type");
	return nullptr;
}
int calcPointerLevel_ofPointContext(OrcParser::PointerContext *pointerContext){
	int pointerLevel = 0;
	for (auto kid : pointerContext->children) {
		if (kid->getText() == "*") {
			pointerLevel++;
		}
	}
	return pointerLevel;
}


//将ast节点转为符号类型
std::shared_ptr<SymbolType> typeContext_toSymbolType(OrcParser::TypeContext* type) {

	if (type) {
		//暂只支持一维数组
		auto arr = type->arraySizeDeclaration();
		if (arr) {
			auto ret = std::make_shared<SymbolTypePointer>();
			ret->typeName = type->primitiveType()->getText();
			ret->pointerLevel = 1;
			return ret;
		}
		auto pointer = type->pointer();
		auto ref = type->ref();
		if (type->Id()) {
			auto ret = std::make_shared<SymbolTypeWithTypeName>();
			ret->typeName = type->Id()->getText();
			return ret;
		}



		if (pointer) {
			auto ret = std::make_shared<SymbolTypePointer>();
			if (pointer->Id()) {
				ret->typeName = pointer->Id()->getText();
			}
			else {
				ret->typeName = pointer->primitiveType()->getText();
			}
			ret->pointerLevel = calcPointerLevel_ofPointContext(pointer);
			return ret;
		}


		// closure
		{
			auto closureType = type->closureType();
			if (closureType) {
				auto ret = std::make_shared<SymbolTypeClosure>();
				ret->isWeak = closureType->isTmpThisVarForClosure;
				ret->typeName = "Closure";
				ret->returnType = typeContext_toSymbolType(closureType->type());
				ret->args = SymbolTypeArg::buildByAstArgumentsDeclaration(closureType->argumentsDeclaration());
				return ret;
			}
		}


		if (type->ref()) {
			auto ret = std::make_shared<SymbolTypeRef>();
			ret->typeName = type->ref()->Id()->getText();
			return ret;
		}
		if (type->primitiveType()) {
			auto ret = std::make_shared<SymbolTypePrimitiveType>();
			ret->typeName = type->primitiveType()->getText();
			return ret;
		}

	}
	return nullptr;
}

//将ast节点转为符号类型
//由于语法的设计原因，structMember/classField的arraySizeDeclaration不在typeContext中，需要额外处理
std::shared_ptr<SymbolType> structMember_typeContext_toSymbolType(OrcParser::StructMemberContext* ctx) {
	auto arr = ctx->arraySizeDeclaration();
	if (arr) {
		auto ret = std::make_shared<SymbolTypePointer>();
		ret->typeName = ctx->type()->primitiveType()->getText();
		ret->pointerLevel = 1;
		return ret;
	}

	return typeContext_toSymbolType(ctx->type());
}
std::shared_ptr<SymbolType> classFieldDeclaration_typeContext_toSymbolType(OrcParser::ClassFieldDeclarationContext* ctx) {
	auto arr = ctx->arraySizeDeclaration();
	if (arr) {
		auto ret = std::make_shared<SymbolTypePointer>();
		ret->typeName = ctx->type()->primitiveType()->getText();
		ret->pointerLevel = 1;
		return ret;
	}

	return typeContext_toSymbolType(ctx->type());
}
//将ast节点转为符号类型
std::shared_ptr<SymbolType> createSymbolType_fromFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext* type) {

	if (type) {
		auto ret = ast_createSymbolTypeFunction(
			type->type(),
			type->argumentsDeclaration()
		);
		/*auto ret = std::make_shared<SymbolTypeFunction>();
		ret->typeName = "Function";
		ret->returnType = typeContext_toSymbolType(type->type());*/
		return ret;
	}
	return nullptr;
}


std::shared_ptr<SymbolTypeWithHostSpace> SymbolTypeWithHostSpace::mk(std::shared_ptr<SymbolType> type,
	std::shared_ptr < SymbolSpace> hostSpace
	) {
	auto ret = std::make_shared< SymbolTypeWithHostSpace>();
	ret->type = type;
	ret->hostSpace = hostSpace;
	return ret;
}
std::shared_ptr<SymbolDefinition> SymbolTypeWithHostSpace::findSymbolDefinition() {
	if (type) {
		auto typeName = type->getNakeTypeName();
		if (!typeName.empty()) {
			auto typePrimitiveType = std::dynamic_pointer_cast<SymbolTypePrimitiveType>(type);
			if (typePrimitiveType) {
				return NULL;
			}

			auto def = hostSpace->findSymbolDefinitionByName_includeImports(typeName);
			return def;
		}
	}
	return NULL;
}
int SymbolTypeWithHostSpace::getPointLevel_ofType()
{
	auto p = dynamic_cast<SymbolTypePointer*>(type.get());
	if (p) {
		return p->pointerLevel;
	}
	auto ref = dynamic_cast<SymbolTypeRef*>(type.get());
	if (ref) {
		return 1;
	}
	return 0;
}
std::string SymbolTypeWithHostSpace::getPointStarText_ofType()
{
	int level = this->getPointLevel_ofType();
	std::string ret;
	for (int i = 0; i < level; i++) {
		ret += "*";
	}
	return ret;
}

// 计算表达式结果的类型符号定义
// 如果是四则运算，返回数字类型
std::shared_ptr<SymbolTypeWithHostSpace> ast__calcSymbolTypeOfExpressionResult(OrcParser::SingleExpressionContext *expr, 
	std::shared_ptr<SymbolSpace> space) {

	//CostUs cost;
	cnt_calcSymbolTypeOfExpr++;

	//auto tt = expr->getText();
	//printf("ast_calcSymbolTypeOfExpressionResult: %7d %s\n", cnt_calcSymbolTypeOfExpr, tt.c_str());
	//cost.stat("print");
	//对每种具体的表达式进行求解结果类型的符号定义
	{ // fn()
		auto ex = dynamic_cast<OrcParser::CallExpressionContext*>(expr);
		if (ex) {
			auto caller = ex->singleExpression();
			//取得函数的符号定义
			auto fn = ast_calcSymbolTypeOfExpressionResult(caller, space);
			if (fn && fn->type) {
				auto fnType = std::dynamic_pointer_cast<SymbolTypeFunction>(fn->type);
				//auto fnDef = dynamic_cast<SymbolDefinitionFunction*>(fn->findSymbolDefinition());
				//返回 函数返回值 的符号定义
				if (fnType && fnType->returnType) {
					auto ret = SymbolTypeWithHostSpace::mk(fnType->returnType, fn->hostSpace);
					return ret;
				}

				{ //闭包
					auto closureType = std::dynamic_pointer_cast<SymbolTypeClosure>(fn->type);
					if (closureType && closureType->returnType) {
						auto ret = SymbolTypeWithHostSpace::mk(closureType->returnType, fn->hostSpace);
						return ret;
					}
				}
			}
			else {
				printf("未找到符号:%s\n", caller->getText().c_str());
			}
		}
	}
	{ // ++
		auto ex = dynamic_cast<OrcParser::PostIncrementExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			return type;
		}
	}
	{ // --
		auto ex = dynamic_cast<OrcParser::PostDecreaseExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			return type;
		}
	}
	{// 闭包 不用处理。 闭包会被提前处理成普通的表达式

	}
	{// 数组索引 
		auto ex = dynamic_cast<OrcParser::MemberIndexExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto exType = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			//数组类型
			auto arrSymType = std::dynamic_pointer_cast<SymbolTypeArray>(exType->type);

			if (arrSymType) {
				auto ret = SymbolTypeWithHostSpace::mk(arrSymType->type, exType->hostSpace);
				return ret;
			}
			//指针类型
			auto pointType = std::dynamic_pointer_cast<SymbolTypePointer>(exType->type);
			if (pointType) {
				if (pointType->pointerLevel > 1) {
					auto type = std::make_shared<SymbolTypePointer>();
					type->typeName = pointType->typeName;
					type->pointerLevel = pointType->pointerLevel - 1;
					auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
					return ret;
				}
				else {
					auto type = std::make_shared<SymbolTypeWithTypeName>();
					type->typeName = pointType->typeName;
					auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
					return ret;
				}
			}
		}
	}
	{// a.b 
		auto ex = dynamic_cast<OrcParser::MemberDotExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			if (type != nullptr) {
				auto propName = ex->Id()->getText();
				auto memberInfo = MemberInfo::findMemberInfo(ex->singleExpression(), propName, space);
				auto def = type->findSymbolDefinition();
				{//扩展 的方法
					if (memberInfo.extensionDef && memberInfo.methodDef) {
						MemberInfo::findMemberInfo(ex->singleExpression(), propName, space);
						auto memberType = memberInfo.methodDef->getType();
						auto ret = SymbolTypeWithHostSpace::mk(memberType, memberInfo.methodDef->hostSpace);
						return ret;
					}
				}
				{
					//类
					auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(def);
					if (classDef) {
						auto memberDto = classDef->findMemberByName_includeSupers(propName);
						if (memberDto) {
							auto ret = SymbolTypeWithHostSpace::mk(memberDto->member->getType(), memberDto->classDef->hostSpace);
							return ret;
						}
					}
				}

				{
					//类
					auto structDef = 
						memberInfo.structDef ? memberInfo.structDef
						: std::dynamic_pointer_cast<SymbolDefinitionStruct>(def);
					if (structDef) {
						auto member = structDef->findMemberByName(propName);
						if (member) {
							auto ret = SymbolTypeWithHostSpace::mk(member->getType(), structDef->hostSpace);
							return ret;
						}
					}
				}
			}
		}
	}
	{// new  
		auto ex = dynamic_cast<OrcParser::NewExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto className = ex->Id()->getText();
			auto symDef = space->findSymbolDefinitionByName_includeImports(className);
			auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(symDef);
			if (classDef) {
				auto type = std::make_shared<SymbolTypeRef>();
				type->typeName = className;
				auto ret = SymbolTypeWithHostSpace::mk(type, classDef->hostSpace);
				return ret;
			}
		}
	}
	{// *expr  解引用  
		auto ex = dynamic_cast<OrcParser::DerefExpressionContext*>(expr);
		if (ex) {
			auto exType = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			if (!exType) {
				exType = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			}
			auto pointType = std::dynamic_pointer_cast<SymbolTypePointer>(exType->type);
			if (pointType) {
				if (pointType->pointerLevel > 1) {
					auto type = std::make_shared<SymbolTypePointer>();
					type->typeName = pointType->typeName;
					type->pointerLevel = pointType->pointerLevel - 1;
					auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
					return ret;
				}
				else {
					auto type = std::make_shared<SymbolTypeWithTypeName>();
					type->typeName = pointType->typeName;
					auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
					return ret;
				}
			}

			//闭包
			auto fnType = std::dynamic_pointer_cast<SymbolTypeFunction>(exType->type);
			if (fnType) { //对闭包解引用，还是返回闭包
				auto ret = SymbolTypeWithHostSpace::mk(fnType, exType->hostSpace);
				return ret;
			}
			//闭包
			auto closureType = std::dynamic_pointer_cast<SymbolTypeClosure>(exType->type);
			if (closureType) { //对闭包解引用，还是返回闭包
				auto ret = SymbolTypeWithHostSpace::mk(closureType, exType->hostSpace);
				return ret;
			}

			auto refType = std::dynamic_pointer_cast<SymbolTypeRef>(exType->type);
			if (refType) {
				auto type = std::make_shared<SymbolTypeWithTypeName>();
				type->typeName = refType->typeName;
				auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
				return ret;
			}
			// 数组 
			auto arrType = std::dynamic_pointer_cast<SymbolTypeArray>(exType->type);
			if (arrType) {
				auto ret = SymbolTypeWithHostSpace::mk(arrType->type, exType->hostSpace);
				return ret;
			}
		}
	}

	{// &expr  取地址  
		auto ex = dynamic_cast<OrcParser::GetAddressExpressionContext*>(expr);
		if (ex) {
			auto exType = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);

			//指针
			auto pointType = std::dynamic_pointer_cast<SymbolTypePointer>(exType->type);
			if (pointType) {
				auto type = std::make_shared<SymbolTypePointer>();
				type->typeName = pointType->typeName;
				type->pointerLevel = pointType->pointerLevel + 1;
				auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
				return ret;
			}
			//引用
			auto refType = std::dynamic_pointer_cast<SymbolTypeRef>(exType->type);
			if (refType) {
				auto type = std::make_shared<SymbolTypePointer>();
				type->typeName = refType->typeName;
				type->pointerLevel = 2;
				auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
				return ret;
			}

			//基类型
			auto nameType = std::dynamic_pointer_cast <SymbolTypeWithTypeName>(exType->type);
			if (nameType) {
				auto type = std::make_shared<SymbolTypePointer>();
				type->typeName = nameType->typeName;
				type->pointerLevel = 1;
				auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
				return ret;
			}
			// 数组 ,转为指针
			auto arrType = std::dynamic_pointer_cast<SymbolTypeArray>(exType->type);
			if (arrType) {
				auto type = std::make_shared<SymbolTypePointer>();
				type->typeName = arrType->type->getNakeTypeName();
				type->pointerLevel = 2;
				auto ret = SymbolTypeWithHostSpace::mk(type, exType->hostSpace);
				return ret;
			}
		}
	}

	{ // ++
		auto ex = dynamic_cast<OrcParser::PreIncrementExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			return type;
		}
	}

	{ // --
		auto ex = dynamic_cast<OrcParser::PreDecreaseExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			return type;
		}
	}
	{ // +
		auto ex = dynamic_cast<OrcParser::UnaryPlusExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			return type;
		}
	}
	{ // -
		auto ex = dynamic_cast<OrcParser::UnaryMinusExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			return type;
		}
	}
	{ // ~
		auto ex = dynamic_cast<OrcParser::BitNotExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(), space);
			return type;
		}
	}
	{ // !
		auto ex = dynamic_cast<OrcParser::NotExpressionContext*>(expr);
		if (ex) {
			auto type = std::make_shared<SymbolTypePrimitiveType>();
			type->typeName = "bool";
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}
	{ // * / %
		auto ex = dynamic_cast<OrcParser::MultiplicativeExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}
	{ // + -
		auto ex = dynamic_cast<OrcParser::AdditiveExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}
	{ // << >> 
		auto ex = dynamic_cast<OrcParser::BitShiftExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}

	{ // > >= < <= 
		auto ex = dynamic_cast<OrcParser::RelationalExpressionContext*>(expr);
		if (ex) {
			auto type = std::make_shared<SymbolTypePrimitiveType>();
			type->typeName = "bool";
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}
	{ // instanceof
		auto ex = dynamic_cast<OrcParser::InstanceofExpressionContext*>(expr);
		if (ex) {
			auto type = std::make_shared<SymbolTypePrimitiveType>();
			type->typeName = "bool";
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}
	{ // == !=
		auto ex = dynamic_cast<OrcParser::EqualityExpressionContext*>(expr);
		if (ex) {
			auto type = std::make_shared<SymbolTypePrimitiveType>();
			type->typeName = "bool";
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}
	{ // &
		auto ex = dynamic_cast<OrcParser::BitAndExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}
	{ // ^
		auto ex = dynamic_cast<OrcParser::BitXOrExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}
	{ // |
		auto ex = dynamic_cast<OrcParser::BitXOrExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}
	{ // &&
		auto ex = dynamic_cast<OrcParser::LogicalAndExpressionContext*>(expr);
		if (ex) {
			auto type = std::make_shared<SymbolTypePrimitiveType>();
			type->typeName = "bool";
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}
	{ // ||
		auto ex = dynamic_cast<OrcParser::LogicalOrExpressionContext*>(expr);
		if (ex) {
			auto type = std::make_shared<SymbolTypePrimitiveType>();
			type->typeName = "bool";
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}
	{ // ? : 
		auto ex = dynamic_cast<OrcParser::TernaryExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(1), space);
			return type;
		}
	}

	{ // (type) expr      cast
		auto ex = dynamic_cast<OrcParser::CastExpressionContext*>(expr);
		if (ex) {
			auto type = typeContext_toSymbolType(ex->type());
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}


	{ // =
		auto ex = dynamic_cast<OrcParser::AssignmentExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}

	{ // +=
		auto ex = dynamic_cast<OrcParser::AssignmentOperatorExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto type = ast_calcSymbolTypeOfExpressionResult(ex->singleExpression(0), space);
			return type;
		}
	}


	{ // this
		auto ex = dynamic_cast<OrcParser::ThisExpressionContext*>(expr);
		if (ex) {
			auto varInfo = ast_findVarInfoByVarName(expr, "self", space);
			auto type = varInfo.calcSymbolType(space);
			if (type) {
				return type;
			}
		}
	}

	{ // super
		auto ex = dynamic_cast<OrcParser::SuperExpressionContext*>(expr);
		if (ex) {
			auto varInfo = ast_findVarInfoByVarName(expr, "self", space);
			auto type = varInfo.calcSymbolType(space);
			if (type) {
				auto classType = std::dynamic_pointer_cast<SymbolTypePointer>(type->type);
				if (classType) {
					auto def = type->hostSpace->findSymbolDefinitionByName_includeImports(classType->typeName);
					auto classDef = std::dynamic_pointer_cast <SymbolDefinitionClass>(def);
					if (classDef) {
						auto superClassDef = classDef->findSuperSymbolDefinition();
						if (superClassDef) {
							classType->typeName = superClassDef->name;
							type->hostSpace = superClassDef->hostSpace;
						}
					}
				}
				return type;
			}
		}
	}

	{ // Id
		//cost.stat("start id cast");
		auto ex = dynamic_cast<OrcParser::IdentifierExpressionContext*>(expr);
		if (ex) {
			//cost.stat("is id");
			auto varName = ex->Id()->getText();
			//cost.stat(std::string("Id()->getText()") + varName);

			if (varName == "__builtin_return_address") {
				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePointer>();
				retType->typeName = "void";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				//cost.stat("__builtin_return_address");
				//cost.print("__builtin_return_address");
				return ret;
			}
			if (varName == "urgc_free_later") {

				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePrimitiveType>();
				retType->typeName = "void";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				return ret;
			}
			if (varName == "orc_alloc_and_set_deleter") {

				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePointer>();
				retType->typeName = "void";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				//cost.stat("orc_alloc_and_set_deleter");
				//cost.print("orc_alloc_and_set_deleter");
				return ret;
			}
			if (varName == "orc_Vtable_Closure_init") {
				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePointer>();
				retType->typeName = "Vtable_Object";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				return ret;
			}

			if (varName == "malloc") {
				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePointer>();
				retType->typeName = "void";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				//cost.stat("malloc");
				//cost.print("malloc");
				return ret;
			}
			if (varName == "metaStructOf") {
				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePointer>();
				retType->typeName = "MetaStruct";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				//cost.stat("sizeof");
				//cost.print("sizeof");
				return ret;
			}
			if (varName == "sizeof") {
				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePrimitiveType>();
				retType->typeName = "long long";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				//cost.stat("sizeof");
				//cost.print("sizeof");
				return ret;
			}
			if (varName == "offsetof") {
				auto symbolType = std::make_shared<SymbolTypeFunction>();
				auto retType = std::make_shared<SymbolTypePrimitiveType>();
				retType->typeName = "long long";
				symbolType->returnType = retType;
				auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
				//cost.stat("offsetof");
				//cost.print("offsetof");
				return ret;
			}

			//cost.stat("check bultin func");

			auto varInfo = ast_findVarInfoByVarName(expr, varName, space);
			//cost.stat("ast_findVarInfoByVarName");
			auto type = varInfo.calcSymbolType(space);
			//cost.stat("calcSymbolType");

			//cost.print("id expr");
			if (type) {
				return type;
			}
		}
	}
	{ // Literal
		auto ex = dynamic_cast<OrcParser::LiteralExpressionContext*>(expr);
		if (ex) {
			auto type = literalToSymbolType(ex->literal());
			auto ret = SymbolTypeWithHostSpace::mk(type, space);
			return ret;
		}
	}

	{ // ( expr )
		auto ex = dynamic_cast<OrcParser::ParenthesizedExpressionContext*>(expr);
		if (ex) {
			//取得函数的符号定义
			auto exprs = ex->expressionSequence()->singleExpression();
			auto type = ast_calcSymbolTypeOfExpressionResult(exprs.back(), space);
			return type;
		}
	}
	//std::cout << "不识别的表达式，无法求取类型: " << expr->getText() << "\n";

	//auto root = ast_findAncestorByType<OrcParser::ProgramContext>(expr);
	//ast_printTree(root, nullptr);
	//ast_calcSymbolTypeOfExpressionResult(expr, space);
	throw std::format("不识别的表达式，无法求取类型:{} #{}", expr->getText(), expr->getStart() ? expr->getStart()->getLine():-1);
	//ast_calcSymbolTypeOfExpressionResult(expr, space);

	return NULL;
}


std::shared_ptr<SymbolTypeWithHostSpace> ast_calcSymbolTypeOfExpressionResult(OrcParser::SingleExpressionContext* expr,
	std::shared_ptr<SymbolSpace> space)
{
	if (expr == nullptr) {
		return nullptr;
	}
	
	if (0&&expr->symbolTypeWithHostSpace) {
		cnt_calcSymbolTypeOfExprCache++;
		printf("ast_calcSymbolTypeOfExpressionResult use cache. text:%7d %s\n"
			, cnt_calcSymbolTypeOfExprCache, expr->getText().c_str());
		return expr->symbolTypeWithHostSpace;
	}



	//long long ms = std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::system_clock::now().time_since_epoch()).count();
	auto ret = ast__calcSymbolTypeOfExpressionResult(expr, space);
	//long long ms2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	if (!ret->type) {
		return nullptr;
	}
	//todo 不严谨。 先简单处理 cJSON_bool 这类typedef的问题
	{
		auto typeWithTypeName = std::dynamic_pointer_cast<SymbolTypeWithTypeName>(ret->type);
		auto typePointer = std::dynamic_pointer_cast<SymbolTypePointer>(ret->type);
		auto typeRef = std::dynamic_pointer_cast<SymbolTypeRef>(ret->type);
		if (typeWithTypeName && !typePointer && !typeRef) {
			auto def = ret->findSymbolDefinition();
			if (def) {
				auto typeDef = std::dynamic_pointer_cast<SymbolDefinitionTypedef>(def);
				if (typeDef) {
					ret->type = typeDef->getType();
				}
			}
		}
	}

	//printf("\t\tcost us:%lld\n", ms2 - ms);
	expr->symbolTypeWithHostSpace = ret;
	//缓存结果
	return ret;
}

/*
提取pointer 星号数量，转为字符串
*/
string ast_pointerStarText(antlr4::tree::ParseTree* ctx) {
	auto text = string("");
	for (int i = 0; i < ctx->children.size(); i++) {
		auto kidText = ctx->children[i]->getText();
		if (kidText == "*") {
			text += "*";
		}
	}
	return text;
}

string ast_buildCode_forPointer(OrcParser::PointerContext* ctx, SymbolSpace *space) {

	auto ctxtext = ctx->getText();

	auto qualifier = ctx->typeQualifier();
	std::string qualiferCode;


	if (ctx->Struct()) {
		qualiferCode +=  "struct ";
	}

	for (auto qual : qualifier) {
		if (qual) {
			qualiferCode += qual->getText() + " ";
		}
	}

	auto id = ctx->Id();

	string typeName;
	if (id) {
		typeName = id->getText();
		auto def = space->findSymbolDefinitionByName_includeImports(typeName);
		if (def) {
			typeName = def->fullname;
		}
	}
	auto primitiveType = ctx->primitiveType();
	if (primitiveType) {
		typeName = ast_primitiveTypeToText(primitiveType);
	}

	auto starText = ast_pointerStarText(ctx);
	auto text = qualiferCode + typeName + " " + starText;
	return text;
}

string ast_buildCode_forRef(OrcParser::RefContext* ctx, SymbolSpace* space) {

	auto ctxtext = ctx->getText();

	auto id = ctx->Id();

	string typeName;
	if (id) {
		typeName = id->getText();
		auto def = space->findSymbolDefinitionByName_includeImports(typeName);
		if (!def) {
			throw std::format("ast_buildCode_forRef error. 通过类型名{}找不到定义", typeName);
		}
		typeName = def->fullname;
	}


	std::string qualiferCode;
	if (ctx->Struct()) {
		qualiferCode += "struct ";
	}


	auto text = qualiferCode + typeName + "*";
	return text;
}

/*
void VarInfo::findSymbolDefinitionByVarDeclaration(SymbolSpace* space) {
	if (varDeclaration) {
		auto type = varDeclaration->type();
		findSymbolDefinitionByType(space, type);
	}
}
void VarInfo::findSymbolDefinitionByArgumentDeclaration(SymbolSpace* space) {
	if (argumentDeclaration) {
		auto type = argumentDeclaration->type();
		findSymbolDefinitionByType(space, type);
	}
}

void VarInfo::findSymbolDefinitionByScopeStatement(SymbolSpace* space) {
	if (scopeStatement) {
		auto expr = scopeStatement->singleExpression();
		//symbol = ast_calcSymbolDefinitionOfExpressionResult(expr, space);
	}
}
void VarInfo::findSymbolDefinitionByType(SymbolSpace* space, OrcParser::TypeContext *type) {
	if (type) {
		auto nakeTypeName = ast_getNakeTypeName_fromTypeContext(type);
		if (!nakeTypeName.empty()) {
			auto def = space->findSymbolDefinitionByName_includeImports(nakeTypeName);
			symbol = def.get();
			return;
		}
	}
}
*/
std::shared_ptr<SymbolTypeWithHostSpace> VarInfo::calcSymbolType(std::shared_ptr<SymbolSpace> space)
{
	//CostUs cost;
	if (varDeclaration) {
		//数组类型
		auto arr = varDeclaration->arraySizeDeclaration();
		{
			auto type = varDeclaration->type();
			if (type) {
				auto symbolType = typeContext_toSymbolType(type);
				//cost.stat("typeContext_toSymbolType");
				if (symbolType) {
					if (arr && type->primitiveType()) {  //一维基础类型数组
						auto typePointer = std::make_shared<SymbolTypePointer>();
						typePointer->typeName = type->primitiveType()->getText();
						typePointer->pointerLevel = 1;
						auto ret = SymbolTypeWithHostSpace::mk(typePointer, space);
						//cost.stat("一维基础类型数组");
						//cost.print("VarInfo::calcSymbolType");
						return ret;
					}



					auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
					//cost.stat("SymbolTypeWithHostSpace::mk");
					//cost.print("VarInfo::calcSymbolType");
					return ret;
				}
			}
		}


		{ //函数指针型
			auto fn = varDeclaration->functionPointerVarDeclaration();
			if (fn) {
				auto symbolType = createSymbolType_fromFunctionPointerVarDeclaration(fn);
				//cost.stat("createSymbolType_fromFunctionPointerVarDeclaration");
				if (symbolType) {
					auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
					//cost.stat("SymbolTypeWithHostSpace::mk");
					//cost.print("VarInfo::calcSymbolType");
					return ret;
				}
			}
		}

	}
	if (argumentDeclaration) {
		auto symbolType = typeContext_toSymbolType(argumentDeclaration->type());
		//cost.stat("typeContext_toSymbolType");
		if (symbolType) {
			auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
			//cost.stat("SymbolTypeWithHostSpace::mk");
			//cost.print("VarInfo::calcSymbolType");
			return ret;
		}

		{ //函数指针型
			auto fn = argumentDeclaration->functionPointerVarDeclaration();
			if (fn) {
				auto symbolType = createSymbolType_fromFunctionPointerVarDeclaration(fn);
				//cost.stat("createSymbolType_fromFunctionPointerVarDeclaration");
				if (symbolType) {
					auto ret = SymbolTypeWithHostSpace::mk(symbolType, space);
					//cost.stat("SymbolTypeWithHostSpace::mk");
					//cost.print("VarInfo::calcSymbolType");
					return ret;
				}
			}
		}
	}
	if (scopeStatement) {
		auto ret = ast_calcSymbolTypeOfExpressionResult(scopeStatement->singleExpression(), space);
		//cost.stat("ast_calcSymbolTypeOfExpressionResult");
		//cost.print("VarInfo::calcSymbolType");
		return ret;
	}
	if (symbolDefinition) {
		auto symbolType = symbolDefinition->getType();
		auto ret = SymbolTypeWithHostSpace::mk(symbolType, symbolDefinition->hostSpace);
		//cost.stat("symbolDefinition");
		//cost.print("VarInfo::calcSymbolType");
		return ret;
	}

	return nullptr;
}
bool VarInfo::isInFunction()
{
	//参数，说明肯定在函数内
	if (argumentDeclaration) {
		return true;
	}
	//scope语句，也只在函数内有
	if (scopeStatement) {
		return true;
	}
	//变量，要向上找到函数定义，有找到才算
	if (varDeclaration) {
		auto def = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(varDeclaration);
		return def != nullptr;
	}

	return false;
}
nlohmann::json dumpJson(Object* obj)
{
	if (obj == NULL) {
		return nullptr;
	}
	auto jo = nlohmann::json::object();
	auto meta = MetaLib::gocInstance()->findMetaByObject(obj);
	if (meta == nullptr) {
		meta = MetaLib::gocInstance()->findMetaByObject(obj);
		throw std::format("未找到对象的meta信息。 obj typeid:{}\n", typeid(*obj).name());
	}
	jo["__class"] = meta->name;
	obj->toJson(jo);
	return jo;
}

std::shared_ptr<Object> parseJsonToObject(nlohmann::json &jo) {
	if (!jo.is_object()) {
		return nullptr;
	}
	auto className = jo.contains("__class") ? jo["__class"].get<string>() : "";
	if (className.empty()) {
		return nullptr;
	}
	auto meta = MetaLib::gocInstance()->findMetaByClassName(className);
	if (meta == NULL) {
		return nullptr;
	}

	auto pobj = meta->createObject();
	std::shared_ptr<Object> obj(pobj); //交给智能指针管理
	obj->fromJson(jo);

	return obj;
}
// 查找变量的符号定义
// 
// 注意：需要提前注入self参数
// 
// 通过变量名查找
// 局部变量 [v]
// for语句定义的局部变量 [v] [TODO 多变量声明]
// scopeStatement.o   [v] 返回表达式    怎么返回没有实际定义的变量咧？ 如self/super/o
// self [?] 直接返回NULL
// super [?] 直接返回NULL
// 参数 [v]
// 全局变量
// 全局静态变量
// 导入的其他变量
// @return VarDeclarationContext, ArgumentDeclaration, SingleExpression(for scopeStatement)
VarInfo ast_findVarInfoByVarName(
	antlr4::tree::ParseTree* tree, string varName,
	std::shared_ptr<SymbolSpace> space //如果有传入，就会顺着找导入的其他变量
) {
	auto node = tree;
	VarInfo info;
	info.varName = varName;
	if (varName == "tmpClosure1") {
		printf("find tmpClosure\n");
	}

	// 没有实际的定义，要怎么返回?
	// self是有的,self是可以从参数中找到的。 这就要求执行此函数前，需要给Method填充self参数
	/*if (varName == "self") {
		return info;
	}*/
	// 没有实际的定义，要怎么返回
	if (varName == "super") {  //super一直从参数中查找self参数
		varName = "self"; 
	}
	while (tree) {
		//ast_printTree(tree, nullptr);
		{ //到根了
			auto root = dynamic_cast<OrcParser::RootDeclarationContext*>(tree);
			if (root) {
				break;
			}
		}
		{
			auto block = dynamic_cast<OrcParser::BlockContext*>(tree);
			if (block) {
				//遍历子语句，查找变量声明
				auto stmts = block->statement();
				for (auto stmt : stmts) {
					auto varDecl = stmt->varDeclaration();
					//找到同名的定义
					if (varDecl) {
						if (varDecl->Id()) {
							if (varDecl->Id()->getText() == varName) {
								info.isFound = true;
								info.varDeclaration = varDecl;
								return info;
							}
						}
						//函数指针型的变量
						auto func = varDecl->functionPointerVarDeclaration();
						if (func && func->Id()->getText() == varName) {
							info.isFound = true;
							info.varDeclaration = varDecl;
							return info;
						}
					}
				}
			}
		}
		{ // 在for中声明变量
			auto iteration = dynamic_cast<OrcParser::IterationStatementContext*>(tree);
			auto forCtx = iteration ? iteration->forCondition(): NULL;
			if (forCtx) {
				//遍历子语句，查找变量声明
				//TODO支持多变量声明语句
				auto varDecl = forCtx->varDeclaration();
				//找到同名的定义
				if (varDecl && varDecl->Id()->getText() == varName) {
					info.isFound = true;
					info.varDeclaration = varDecl;
					return info;
				}
			}
		}

		{ // 闭包的参数
			auto closure = dynamic_cast<OrcParser::ClosureExpressionContext*>(tree);
			auto argsDecl = closure ? closure->argumentsDeclaration() : NULL;
			if (argsDecl) {
				auto args = argsDecl->argumentDeclaration();
				for (int i = 0, l = args.size(); i < l; i++) {
					auto arg = args[i];
					if (arg->Id()->getText() == varName) {
						info.isFound = true;
						info.argumentDeclaration = arg;
						return info;
					}
				}
			}
		}

		{ // 函数的参数
			auto fn = dynamic_cast<OrcParser::FunctionDefinitionContext*>(tree);
			auto argsDecl = fn ? fn->argumentsDeclaration() : NULL;
			if (argsDecl) {
				auto args = argsDecl->argumentDeclaration();
				for (int i = 0, l = args.size(); i < l; i++) {
					auto arg = args[i];
					if (arg->Id() && arg->Id()->getText() == varName) {
						info.isFound = true;
						info.argumentDeclaration = arg;
						return info;
					}
					//函数指针型参数
					if (arg->functionPointerVarDeclaration() && arg->functionPointerVarDeclaration()->Id()->getText() == varName) {
						info.isFound = true;
						info.argumentDeclaration = arg;
						return info;
					}
				}
			}
		}
		if (varName == "o") { // scopeStatement.o
			auto scope = dynamic_cast<OrcParser::ScopeStatementContext*>(tree);
			if (scope) {
				//如果node就在scope的表达式中，那就需要跳过
				auto isInScopeExpr = ast_subtreeContainsNode(scope->singleExpression(), node);
				if (isInScopeExpr) {

				}
				else {
					info.isFound = true;
					info.scopeStatement = scope;
					return info;
				}

			}
		}

		tree = tree->parent;
	}
	
	// 没找到，需要从符号表中查找了
	if (space) {
		auto symbol = space->findSymbolDefinitionByName_includeImports(varName);
		if (symbol) {
			info.symbolDefinition = symbol;
			info.isFound = true;
		}
	}
	
	return info;

}


OrcParser::BlockContext* ast_wrapBlock_outOfForStatement(antlr4::tree::ParseTree* tree, AstMake* mk)
{
	auto st = ast_findAncestorByType<OrcParser::IterationStatementContext>(tree);
	if (st
		&& !st->forWrappedBlock //还没有包过，可以包一下
		) {
		auto blockSt = mk->statement();
		auto block = mk->block();
		blockSt->insert(block);

		ast_replaceChild(st, blockSt);

		block->insert(st);

		//标记已经外包了一层
		st->forWrappedBlock = true;
		return block;
	}
	return nullptr;
}
//
////用来构建符号的
//class LambdaVisitor : public antlr4::tree::AbstractParseTreeVisitor {
//public:
//	std::function<void (antlr4::tree::ParseTree* tree, LambdaVisitor* visitor)> cbVisit;
//
//	/// The default implementation calls <seealso cref="ParseTree#accept"/> on the
//	/// specified tree.
//	virtual std::any visitChildren(antlr4::tree::ParseTree* tree) override {
//		cbVisit(tree, this);
//		//auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
//		return defaultResult();
//	}
//	// 在闭包内部，如果决定要访问子树， 就可以使用visitKids。 不能用visitChildren,
//	// 因为visitChildren已被重写
//	virtual std::any visitKids(antlr4::tree::ParseTree* tree) {
//		auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
//		return ret;
//	}
//};

//判断是不是扩展函数
//ExtensionMemberInfo ExtensionMemberInfo::findExtensionMemberInfoByAst(
//	OrcParser::SingleExpressionContext *objExpr, string propName, 
//	std::shared_ptr<SymbolSpace> space) {
//
//
//	auto typeInfo = ast_calcSymbolTypeOfExpressionResult(objExpr, space);
//	if (typeInfo) {
//		auto ret = space->findExtensionMemberByTypeNameAndMemberName_includeImports(
//			typeInfo->type->getNakeTypeName()
//			, propName);
//
//		return ret;
//	}
//	ExtensionMemberInfo ret;
//	return ret;
//}
//判断是不是扩展函数
 MemberInfo MemberInfo::findMemberInfo(
		OrcParser::SingleExpressionContext* objExpr, string propName,
		std::shared_ptr<SymbolSpace> space) {

	MemberInfo ret;

	auto typeInfo = ast_calcSymbolTypeOfExpressionResult(objExpr, space);
	if (typeInfo) {
		ret.typeInfo = typeInfo;

		auto typeDef = typeInfo->findSymbolDefinition();
		ret.typeDef = typeDef;

		//结构体
		auto structDef = std::dynamic_pointer_cast<SymbolDefinitionStruct>(typeDef);
		if (structDef) {
			auto member = structDef->findMemberByName(propName);
			if (member) {
				ret.isFound = true;
				ret.memberDef = member;
				ret.structDef = structDef;
				ret.fieldDef = std::dynamic_pointer_cast<SymbolDefinitionClassField>(member);
				return ret;
			}
		}

		//是类
		auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(typeDef);
		if (classDef) {
			auto memberDto = classDef->findMemberByName_includeSupers(propName);
			if (memberDto) {
				ret.isFound = true;
				ret.memberDef = memberDto->member;
				ret.classDef = memberDto->classDef;
				ret.fieldDef = std::dynamic_pointer_cast <SymbolDefinitionClassField>(memberDto->member);
				ret.methodDef = std::dynamic_pointer_cast <SymbolDefinitionMethod>(memberDto->member);
				return ret;
			}
		}

		//扩展
		auto memberInfo = space->findExtensionMemberByTypeNameAndMemberName_includeImports(
			typeInfo->type->getNakeTypeName()
			, propName);

		if (memberInfo.methodDef) {
			ret.methodDef = memberInfo.methodDef;
			ret.extensionDef = memberInfo.extensionDef;
			ret.isFound = true;
			return ret;
		}

		//从类型定义所在的符号空间寻找扩展函数
		{
			auto memberInfo = typeInfo->hostSpace->findExtensionMemberByTypeNameAndMemberName_includeImports(
				typeInfo->type->getNakeTypeName()
				, propName);

			if (memberInfo.methodDef) {
				ret.methodDef = memberInfo.methodDef;
				ret.extensionDef = memberInfo.extensionDef;
				ret.isFound = true;
				return ret;
			}
		}


		//类型重定义
		auto typedefDef = std::dynamic_pointer_cast<SymbolDefinitionTypedef>(typeDef);
		if (typedefDef) {
			//TODO暂只支持一级的typedef
			auto toType = std::dynamic_pointer_cast<SymbolTypeWithTypeName>(typedefDef->type);
			if (toType) {
				auto actualDef = space->findSymbolDefinitionByName_includeImports(toType->typeName);

				auto defStruct = std::dynamic_pointer_cast<SymbolDefinitionStruct>(actualDef);

				if (defStruct) {
					auto member = defStruct->findMemberByName(propName);
					if (member) {
						ret.isFound = true;
						ret.memberDef = member;
						ret.structDef = defStruct;
						ret.fieldDef = std::dynamic_pointer_cast<SymbolDefinitionClassField>(member);
						return ret;
					}
				}
			}
		}
	}
	return ret;
}
bool ast_replaceChild(
	antlr4::tree::ParseTree* ctx,
	antlr4::tree::ParseTree* newnode
) {
	auto ret = ast_replaceChild_specificParent(ctx->parent, ctx, newnode);
	return ret;
}
//指定父结点 。因为实际开发中，ctx可能丢失父结点了
bool ast_replaceChild_specificParent(
	antlr4::tree::ParseTree* parent,
	antlr4::tree::ParseTree* ctx,
	antlr4::tree::ParseTree* newnode
) {
	if (parent) {
		for (int i = 0; i < parent->children.size(); i++) {
			auto cur = parent->children[i];
			if (cur == ctx) {
				parent->children.erase(parent->children.begin() + i);
				parent->children.insert(parent->children.begin() + i, newnode);
				if (ctx->parent == parent) { //只有当ctx->parent还是原来的，才有必要置空。 如果已经是别的父结点了，说明归属权变了
					ctx->parent = NULL;
				}
				newnode->parent = parent;
				return true;
			}
		}
	}
	return false;
}
OrcParser::TypeContext* ast_mkTypeContext_forScopeStatement(OrcParser::ScopeStatementContext* ctx, std::shared_ptr<SymbolSpace> space, AstMake* mk)
{
	auto expr = ctx->singleExpression();
	auto type = ast_mkTypeContext_SingleExpression(expr, space, mk);
	return type;
}

OrcParser::TypeContext* ast_mkTypeContext_SingleExpression(OrcParser::SingleExpressionContext* ctx, std::shared_ptr<SymbolSpace> space, AstMake* mk)
{
	auto symbolTypeInfo = ast_calcSymbolTypeOfExpressionResult(ctx, space);
	auto astType = symbolTypeInfo->type->toAstType(mk);

	auto type = mk->type(astType);
	return type;
}

bool ast_insertChild_before(
	antlr4::tree::ParseTree* relNode, //参考节点
	antlr4::tree::ParseTree* newnode
	
) {
	auto parent = relNode->parent;
	if (parent) {
		for (int i = 0; i < parent->children.size(); i++) {
			auto cur = parent->children[i];
			if (cur == relNode) {
				parent->children.insert(parent->children.begin() + i, newnode);
				newnode->parent = parent;
				return true;
			}
		}
	}
	return false;
}

template <typename T>
void vector_addOnce(std::vector<T> &vec, T item) {
	for (auto& e : vec) {
		if (e == item) {
			return;
		}
	}
	vec.push_back(item);
}

/*
收集usedExpr. 如果变量被捕获，那就收集该变量所有用到的地方
*/
class ClosureCollectVarRefInfoVisitor : public OrcBaseVisitor {
public:
	//当前所在的closure栈中
	//std::vector<ClosureInfo*> closureStack;

	virtual std::any visitClosureExpression(OrcParser::ClosureExpressionContext* ctx) override {
		//auto info = ctx->goc_closureInfo();
		//info->ctx = ctx;


		////关联父闭包
		//if (closureStack.size() > 0) {
		//	info->parent = closureStack.back();
		//}

		//closureStack.push_back(info.get());
		auto ret = visitChildren(ctx);
		//closureStack.pop_back();

		return ret;
	}
	virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx) override {

		do {
			//不在闭包内,记录哪些变量用到了被捕获的变量

			auto varName = ctx->Id()->getText();

			//只需要查找本域的变量
			auto varInfo = ast_findVarInfoByVarName(ctx, varName, nullptr);
			//如果变量是本函数内的变量
			if (varInfo.isFound && varInfo.isInFunction()) {
				auto capInfo = varInfo.varDeclaration ? varInfo.varDeclaration->captureInfo
					: nullptr;
				if (varInfo.argumentDeclaration) {
					capInfo = varInfo.argumentDeclaration->captureInfo;
				}
				else if (varInfo.scopeStatement) {
					capInfo = varInfo.scopeStatement->captureInfo;
				}
				if (capInfo) {
					capInfo->addUsedExpr_once(ctx, nullptr); //登记为使用了捕获的变量
				}
			}
			
		} while (0);

		return visitChildren(ctx);
	}

	//super要怎么处理啊
	virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext* ctx) override {

		////在闭包内
		//if (closureStack.size() > 0) {
		//}
		return visitChildren(ctx);
	}
	virtual std::any visitThisExpression(OrcParser::ThisExpressionContext* ctx) override {
		////在闭包内
		//if (closureStack.size() > 0) {
		//}
		return visitChildren(ctx);
	}
	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override {
		return visitChildren(ctx);
	}

};


/*
收集闭包捕获的变量的信息

*/
class ClosureCollectCaptureInfoVisitor : public OrcBaseVisitor {
public:
	//当前所在的closure栈中
	std::vector<ClosureInfo*> closureStack;
	std::vector<ClosureInfo*> allClosures;
	AstMake* mk = NULL;
	std::shared_ptr<SymbolSpace> space = nullptr;

	AbstractParseTreeVisitor* symbolBuilder = NULL;
	OrcParser::RootDeclarationContext* rootDeclarationCtx = NULL;

	std::vector<OrcParser::FunctionDefinitionContext*> functionDefinitionContextList;

	antlr4::tree::ParseTree* tree = NULL;
	

	virtual std::any visitProgram(OrcParser::ProgramContext* ctx) override {
		this->tree = ctx;
		return OrcBaseVisitor::visitProgram(ctx);
	}

	void init_rootDeclarationCtx() {
		if (allClosures.size() > 0) {
			rootDeclarationCtx = ast_findAncestorByType
				<OrcParser::RootDeclarationContext>(allClosures.back()->ctx);
		}
	}

	//收集到信息后，可以做转译了
	void translate() {
		// 收集对被捕获的变量的使用
		for (auto fn : functionDefinitionContextList) {
			ClosureCollectVarRefInfoVisitor collUsedVi;
			collUsedVi.visit(fn);
		}

		//找到根列表
		init_rootDeclarationCtx();

		// 生成block class
		// 创建block 引用变量
		createBlockClass_each();
		// 替换变量声明语句
		// 替换对变量的访问
		createBlockVar_each();

		GenOrcCodeVisitor orcVi2;
		//printf("after closure block:%s\n", orcVi2.visitReturnString(tree).c_str());

		// 生成闭包结构体
		// 生成闭包创建函数
		createClosureStruct_each();
		// 替换闭包字面量

		replaceClosureLiteral_each();


		//GenOrcCodeVisitor orcVi;
		//auto s = orcVi.visitReturnString(tree);
		//printf("\n======================转换后的orc代码为:\n%s\n\n", s.c_str());
	}
	void replaceClosureLiteral_each() {
		for (auto closure : allClosures) {
			replaceClosureLiteral(closure);
		}
	}
	void replaceClosureLiteral(ClosureInfo* closureInfo) {
		auto call = mk->callExpression_byFunctionName_withArguments(closureInfo->goc_closureMakeFunctionName());
		auto args = call->arguments();

		// 依赖的block作为参数加入
		// 嵌套的闭包，访问block，需要用self
		for (auto& blockInfo : closureInfo->captureBlockInfos) {
			auto argName = blockInfo->calc_blockVarName();
			//嵌套的闭包，访问block，如果该block不在当前闭包，需要用self
			auto closureThatIn = blockInfo->getOrFind_closureThatBlockIsIn();
			if (closureInfo->parent && closureThatIn != closureInfo->parent->ctx) {
				auto dot = mk->memberDotExpr(
					mk->identifierExpression("self"),
					argName
				);
				args->insert(dot);
			} else {
				args->insert(mk->identifierExpression(argName));
			}
		}

		// 如果是具名的closure
		if (closureInfo->ctx->Id()) {
			auto closureType = mk->closureType(
				closureInfo->ctx->type(),
				false
			);
			closureType->insert(closureInfo->ctx->argumentsDeclaration());
			auto type = mk->type(
				//mk->refByTypeName(closureInfo->goc_closureClassName())
				closureType
			);
			auto closureName = closureInfo->ctx->Id()->getText();
			//创建同名的变量来接收实例
			auto varDecl = mk->varDeclaration(type, closureName, mk->nullLiteralExpression());
			auto stmt = mk->statement();
			stmt->insert(varDecl);
			stmt->insert(mk->eos());
			auto curStmt = ast_findAncestorByType<OrcParser::StatementContext>(closureInfo->ctx);
			ast_insertChild_before(curStmt, stmt);

			//  closureName = makeClosure()
			auto assign = mk->assignmentExpression();
			assign->insert(mk->identifierExpression(closureName));
			assign->insert(call);
			auto quote = mk->parenthesizedExpression(assign);

			// ctx:是ClosureExpression,不是LabelClosureExpression, 要替换的是 LabelClosureExpression
			if (dynamic_cast<OrcParser::LabelClosureExpressionContext*>(closureInfo->ctx->parent)) {
				ast_replaceChild(closureInfo->ctx->parent, quote);
			}
			else {
				ast_replaceChild(closureInfo->ctx, quote);
			}
		}
		else {
			// ctx:是ClosureExpression,不是LabelClosureExpression, 要替换的是 LabelClosureExpression
			if (dynamic_cast<OrcParser::LabelClosureExpressionContext*>(closureInfo->ctx->parent)) {
				ast_replaceChild(closureInfo->ctx->parent, call);
			}
			else {
				ast_replaceChild(closureInfo->ctx, call);
			}
		}

	}
	void createClosureStruct_each() {
		for (auto closure : allClosures) {
			createClosureStruct(closure);
		}
	}
	//创建闭包的结构体
	void createClosureStruct(ClosureInfo* closureInfo) {

		auto ctx = closureInfo->ctx;
		auto name = closureInfo->goc_closureClassName();
		auto structCtx = mk->mkStruct(name);
		structCtx->isStaticStruct = true;
		structCtx->fullname = ast_mkFullname_byPrefix(space->packageName, name);
		//加到根作用域中
		rootDeclarationCtx->insert(structCtx);
		//闭包函数声明 
		{
			auto fnMember = mk->functionPointerMember(
				ctx->type(),
				1, 
				"invoke", true
			);
			auto fnArgsDecl = fnMember->argumentsDeclaration();
			auto selfArgDecl = mk->argDecl();
			selfArgDecl->insert(
				mk->type(mk->pointerByTypeName(name))
			);
			selfArgDecl->insert(mk->Id("self"));
			fnArgsDecl->insert(selfArgDecl);
			for (auto argDecl : ctx->argumentsDeclaration()->argumentDeclaration()) {
				fnArgsDecl->insert(argDecl);
			}
			//fnMember->insert(ctx->argumentsDeclaration());

			auto fieldCtx = mk->mkStructMember_forFunctionPointerMember(fnMember);
			structCtx->insert(fieldCtx);

			{ //vtable
				auto type = mk->type(
					mk->pointerByTypeName("Vtable_Object")
				);
				auto fieldCtx = mk->mkStructMember(type, "vtable");
				structCtx->insert(fieldCtx);
			}
		}

		//auto defBlock = classCtx->classDefinitionBlock();
		//添加字段
		for (auto& blockInfo : closureInfo->captureBlockInfos) {
			auto blockName = blockInfo->goc_blockClassName();
			auto type = mk->type(mk->refByTypeName(blockName));

			auto fieldCtx = mk->mkStructMember(type, blockInfo->calc_blockVarName());

			structCtx->insert(fieldCtx);
		}

		// 登记符号到空间
		symbolBuilder->visit(structCtx);

		{
			// 闭包函数体外置
			auto globalFn = mk->globalFunctionDefinition();
			globalFn->insert(mk->mkStatic()); //静态函数
			auto fn = mk->functionDefinition();
			fn->insert(ctx->type());
			fn->insert(mk->Id(closureInfo->goc_closureFunctionName()));

			auto args = mk->argumentsDeclaration();
			{//添加self参数
				auto ptr = mk->pointerByTypeName(closureInfo->goc_closureClassName());
				auto type = mk->type(ptr);
				auto arg = mk->argDecl();
				arg->insert(type);
				arg->insert(mk->Id("self"));
				args->insert(arg);
			}
			{ //参数
				for (auto& arg : ctx->argumentsDeclaration()->argumentDeclaration()) {
					args->insert(arg);
				}
				fn->insert(args);
			}
			fn->insert(ctx->block());
			
			fn->fullname = closureInfo->goc_closureFunctionName();// ast_mkFullname_byPrefix(space->packageName, closureInfo->goc_closureFunctionName());

			globalFn->insert(fn);
			
			//加到根作用域中
			rootDeclarationCtx->insert(globalFn);
			// 登记符号到空间
			symbolBuilder->visit(globalFn);
		}

		// 生成析构闭包的函数
		{
			/*
			void _fini_Closure..(_Closure*self){
				self->b1 = NULL;
				self->b2 = NULL;
			}
			*/
			auto globalFn = mk->globalFunctionDefinition();
			globalFn->insert(mk->mkStatic()); //静态函数
			auto fn = mk->functionDefinition();
			fn->fullname = closureInfo->goc_closureFiniFunctionName();//  ast_mkFullname_byPrefix(space->packageName, closureInfo->goc_closureMakeFunctionName());

			fn->insert(mk->type(mk->primitiveType("void")));
			fn->insert(mk->Id(closureInfo->goc_closureFiniFunctionName()));

			auto args = mk->argumentsDeclaration();
			fn->insert(args);

			//参数
			auto selfType = mk->type(
				mk->pointerByTypeName(closureInfo->goc_closureClassName())
			);
			auto argDecl = mk->argDecl();
			argDecl->insert(selfType);
			argDecl->insert(mk->Id("self"));
			args->insert(argDecl);


			auto block = mk->block();

			fn->insert(block);
			{ //函数体
				//依赖的block作为参数加入
				for (auto& blockInfo : closureInfo->captureBlockInfos) {
					auto argName = blockInfo->calc_blockVarName();

					// 赋值语句
					auto memberDot = mk->memberDotExpr(mk->identifierExpression("self"), argName);

					auto assignExpr = mk->assignmentExpression();
					assignExpr->insert(memberDot);
					assignExpr->insert(mk->nullLiteralExpression());

					auto stmt = mk->statement();
					stmt->insert(assignExpr);
					stmt->insert(mk->eos());
					block->insert(stmt);
				}

			}
			{
				// free self
				auto returnStmt = mk->statement();
				auto free_later = mk->callExpression_byFunctionName_withArguments("urgc_free_later");
				free_later->arguments()->insert(mk->identifierExpression("self"));
				returnStmt->insert(free_later);
				returnStmt->insert(mk->eos());
				auto stmt = mk->statement();
				stmt->insert(returnStmt);
				block->insert(stmt);
			}

			globalFn->insert(fn);
			//加到根作用域中
			rootDeclarationCtx->insert(globalFn);
			// 登记符号到空间
			symbolBuilder->visit(globalFn);
		}
		// 生成创建闭包的函数
		{
			/*
			__Closure@ _make_Closure..(block1 b1, block2 b2...){
				//__Closure@ self = malloc(sizeof(__Closure));
				__Closure@ self = orc_alloc_and_set_deleter(sizeof(__Closure));
				self->b1 = b1;
				self->b2 = b2;
				return self;
			}
			*/
			auto globalFn = mk->globalFunctionDefinition();
			globalFn->insert(mk->mkStatic()); //静态函数
			auto fn = mk->functionDefinition();
			fn->fullname = closureInfo->goc_closureMakeFunctionName();//  ast_mkFullname_byPrefix(space->packageName, closureInfo->goc_closureMakeFunctionName());

			auto retType = mk->type(
				mk->refByTypeName(closureInfo->goc_closureClassName())
			);
			fn->insert(retType);
			fn->insert(mk->Id(closureInfo->goc_closureMakeFunctionName()));

			auto args = mk->argumentsDeclaration();
			fn->insert(args);
			auto block = mk->block();

			fn->insert(block);
			{ //函数体
				{ //malloc self
					auto refType =  mk->refByTypeName(closureInfo->goc_closureClassName());
					auto type = mk->type(refType);
					auto mallocCall = mk->callExpression_byFunctionName_withArguments("orc_alloc_and_set_deleter");
					{
						auto sizeofCall= mk->callExpression_byFunctionName_withArguments("sizeof");
						sizeofCall->arguments()->insert(mk->identifierExpression(closureInfo->goc_closureClassName()));
						mallocCall->arguments()->insert(sizeofCall);
						mallocCall->arguments()->insert(mk->identifierExpression(closureInfo->goc_closureFiniFunctionName())); 
					}

					auto varDecl = mk->varDeclaration(type, "self", mallocCall);
					auto stmt = mk->statement();
					stmt->insert(varDecl);
					stmt->insert(mk->eos());
					block->insert(stmt);
				}

				{ //赋值函数体


					// 赋值语句
					auto memberDot = mk->memberDotExpr(mk->identifierExpression("self"), "invoke", "->");

					auto assignExpr = mk->assignmentExpression();
					assignExpr->insert(memberDot);
					assignExpr->insert(mk->identifierExpression(closureInfo->goc_closureFunctionName()));

					auto stmt = mk->statement();
					stmt->insert(assignExpr);
					stmt->insert(mk->eos());
					block->insert(stmt);

				}
				{//赋值self->vtable = orc_Vtable_Closure_init();
					// 赋值语句
					auto memberDot = mk->memberDotExpr(mk->identifierExpression("self"), "vtable", "->");

					auto assignExpr = mk->assignmentExpression();
					assignExpr->insert(memberDot);
					assignExpr->insert(
						mk->callExpression_byFunctionName_withArguments("orc_Vtable_Closure_init")
					);

					auto stmt = mk->statement();
					stmt->insert(assignExpr);
					stmt->insert(mk->eos());
					block->insert(stmt);
				}

				//依赖的block作为参数加入
				for (auto& blockInfo : closureInfo->captureBlockInfos) {
					auto argName = blockInfo->calc_blockVarName();
					//参数
					auto blockName = blockInfo->goc_blockClassName();
					auto type = mk->type(mk->pointerByTypeName(blockName));
					auto argDecl = mk->argDecl();
					argDecl->insert(type);
					argDecl->insert(mk->Id(argName));
					args->insert(argDecl);

					// 赋值语句
					auto memberDot = mk->memberDotExpr(mk->identifierExpression("self"), argName);

					auto assignExpr = mk->assignmentExpression();
					assignExpr->insert(memberDot);
					assignExpr->insert(mk->identifierExpression(argName));

					auto stmt = mk->statement();
					stmt->insert(assignExpr);
					stmt->insert(mk->eos());
					block->insert(stmt);
				}

			}
			{
				// 返回语句
				auto returnStmt = mk->returnStatement();
				returnStmt->insert(mk->identifierExpression("self"));
				returnStmt->insert(mk->eos());
				auto stmt = mk->statement();
				stmt->insert(returnStmt);
				block->insert(stmt);
			}

			globalFn->insert(fn);
			//加到根作用域中
			rootDeclarationCtx->insert(globalFn);
			// 登记符号到空间
			symbolBuilder->visit(globalFn);
		}
		// 
	}
	void createBlockVar_each() {
		for (auto closure : allClosures) {
			for (auto blockInfo : closure->captureBlockInfos) {
				createBlockVar(blockInfo);
			}
		}
	}

	//创建block 变量
	void createBlockVar(std::shared_ptr<CaptureBlockInfo> blockInfo) {
		if (blockInfo->flag_blockVarGenerated) {
			return;
		}
		//阻止重复处理
		blockInfo->flag_blockVarGenerated = true;


		//calloc(1, sizeof());
		auto init = mk->callExpression_byFunctionName_withArguments("orc_alloc_and_set_deleter");
		auto args = init->arguments();

		//args->insert(mk->intLiteralExpression(1));

		auto expr_sizeof = mk->callExpression_byFunctionName_withArguments("sizeof");
		auto typeExpr = mk->identifierExpression(blockInfo->goc_blockClassName());
		expr_sizeof->arguments()->insert(typeExpr);

		args->insert(expr_sizeof);
		args->insert(mk->identifierExpression(blockInfo->calc_blockFiniFunctionName()));


		auto ptr = mk->refByTypeName(blockInfo->goc_blockClassName());
		auto type = mk->type(ptr);

		auto varDecl = mk->varDeclaration(
			type,
			blockInfo->calc_blockVarName(),
			init
		);
		auto varStmt = mk->statement();
		varStmt->insert(varDecl);

		//在block的第一行插入 __tagBlock@ __var___tagBlock = calloc(1, sizeof(__tagBlock));
		blockInfo->blockCtx->insert(varStmt, 0);

		// 处理变量
		for (auto& e : blockInfo->captureVarInfos) {
			auto access = mk->memberDotExpr(mk->identifierExpression(blockInfo->calc_blockVarName()), e->varName);
			// 替换变量声明
			{
				if (e->varDeclaration) { //for语句已经在前面处理过了。 之前已经把forCond.init 提取出来了
					//替换变量声明为  blockVar->varName = init
					auto assign = mk->assignmentExpression();
					assign->insert(access);
					assign->insert(e->varDeclaration->singleExpression());
					ast_replaceChild(e->varDeclaration, assign);
				}
				else if (e->argumentDeclaration) {
					//在函数开始插入 blockVar->argName = argName
					auto assign = mk->assignmentExpression();
					assign->insert(access);
					assign->insert(mk->identifierExpression(e->varName));
					auto stmt = mk->statement();
					stmt->insert(assign);
					blockInfo->blockCtx->insert(stmt, 1);//为什么是1呢，因为0是block var
				}
				else if (e->scopeStatement) {
					// 在scopeStatement块开始插入blockVar->o = o;
					auto assign = mk->assignmentExpression();
					assign->insert(access);
					assign->insert(mk->identifierExpression("o"));
					auto stmt = mk->statement();
					stmt->insert(assign);
					blockInfo->blockCtx->insert(stmt, 1);
				}
				else if (e->thisExpression) {
					// 在scopeStatement块开始插入blockVar->o = o;
					auto assign = mk->assignmentExpression();
					assign->insert(access);
					assign->insert(mk->identifierExpression("self"));
					auto stmt = mk->statement();
					stmt->insert(assign);
					blockInfo->blockCtx->insert(stmt, 1);
				}
			}

			// 替换变量的访问
			{

				for (auto& usedInfo : e->usedExprs) {
					auto inClosureCtx = blockInfo->getOrFind_closureThatBlockIsIn();
					// 在闭包里使用的 
					// 且跟block不在同一个闭包里
					// 实质上这里要判断是，  如果在子闭包里访问变量，就需要添加self,
					// 如果同级，也是不需要的
					if (usedInfo.closureInfo && usedInfo.closureInfo->ctx != inClosureCtx) {
						auto access2 = mk->memberDotExpr(
							mk->memberDotExpr(
								mk->identifierExpression("self"),
								blockInfo->calc_blockVarName()
							),
							e->varName);

						ast_replaceChild(
							usedInfo.getExpr()
							, access2
						);
					}
					// 跟变量在同一个闭包里声明的
					// 不在闭包里使用？
					else {
						ast_replaceChild(
							usedInfo.getExpr()
							, access
						);
					}
				}
			}
		}
	}


	void createBlockClass_each() {
		for (auto closure : allClosures) {
			for (auto blockInfo: closure->captureBlockInfos) {
				createBlockClass(blockInfo);
			}
		}
	}

	//生成字段时需要
	OrcParser::TypeContext* getTypeCtx_ofCaptureVarInfo(CaptureVarInfo*info) {
		if (info->varDeclaration) {
			auto type = info->varDeclaration->type();
			auto retType = ast_cloneTypeContext(type, mk);
			return retType;
		}
		if (info->argumentDeclaration) {
			auto type = info->argumentDeclaration->type();
			auto retType = ast_cloneTypeContext(type, mk);
			return retType;
		}
		if (info->scopeStatement) {
			auto type = ast_mkTypeContext_forScopeStatement(info->scopeStatement, space, mk);
			return type;
		}
		if (info->superExpression) {
			auto type = ast_mkTypeContext_SingleExpression(info->superExpression, space, mk);
			return type;
		}
		if (info->thisExpression) {

			auto symbolTypeInfo = ast_calcSymbolTypeOfExpressionResult(info->thisExpression, space);
			auto typeName = symbolTypeInfo->type->getNakeTypeName();

			auto type = mk->type(
				mk->refByTypeName(typeName)
				);
			//auto type = ast_mkTypeContext_SingleExpression(info->thisExpression, space, mk);
			return type;
		}

		auto err = std::format("can not getTypeCtx_ofCaptureVarInfo for var:{}", info->varName);
		throw err;
	}
	void createBlockClass(std::shared_ptr<CaptureBlockInfo> blockInfo) {
		if (blockInfo->flag_blockClassGenerated) {
			return;
		}
		//阻止重复处理
		blockInfo->flag_blockClassGenerated = true;
		auto name =blockInfo->goc_blockClassName();
		auto structCtx = mk->mkStruct(name);
		structCtx->isStaticStruct = true;
		structCtx->fullname = ast_mkFullname_byPrefix(space->packageName , name);
		//加到根作用域中
		rootDeclarationCtx->insert(structCtx);


		//auto defBlock = classCtx->classDefinitionBlock();
		//添加字段
		for (auto& varInfo : blockInfo->captureVarInfos) {
			auto type = getTypeCtx_ofCaptureVarInfo(varInfo.get());
			auto init = mk->nullLiteralExpression();

			auto fieldCtx = mk->mkStructMember(type, varInfo->varName);

			structCtx->insert(fieldCtx);
		}

		// 登记符号到空间
		symbolBuilder->visit(structCtx);



		// 生成析构Block的函数
		{
			/*
			void _finiBlock..(_Closure*self){
				self->b1 = NULL;
				self->b2 = NULL;
			}
			*/
			auto globalFn = mk->globalFunctionDefinition();
			globalFn->insert(mk->mkStatic()); //静态函数
			auto fn = mk->functionDefinition();
			fn->fullname = blockInfo->calc_blockFiniFunctionName();//  ast_mkFullname_byPrefix(space->packageName, closureInfo->goc_closureMakeFunctionName());

			fn->insert(mk->type(mk->primitiveType("void")));
			fn->insert(mk->Id(blockInfo->calc_blockFiniFunctionName()));

			auto args = mk->argumentsDeclaration();
			fn->insert(args);

			//参数
			auto selfType = mk->type(
				mk->pointerByTypeName(blockInfo->goc_blockClassName())
			);
			auto argDecl = mk->argDecl();
			argDecl->insert(selfType);
			argDecl->insert(mk->Id("self"));
			args->insert(argDecl);


			auto block = mk->block();

			fn->insert(block);
			{ //函数体
				//依赖的block作为参数加入
				for (auto& varInfo : blockInfo->captureVarInfos) {
					auto type = getTypeCtx_ofCaptureVarInfo(varInfo.get());
					if (type->ref()) {
						auto argName = varInfo->varName;

						// 赋值语句
						auto memberDot = mk->memberDotExpr(mk->identifierExpression("self"), argName);

						auto assignExpr = mk->assignmentExpression();
						assignExpr->insert(memberDot);
						assignExpr->insert(mk->nullLiteralExpression());

						auto stmt = mk->statement();
						stmt->insert(assignExpr);
						stmt->insert(mk->eos());
						block->insert(stmt);
					}
				}
			}
			{
				// free self
				auto returnStmt = mk->returnStatement();
				auto free_later = mk->callExpression_byFunctionName_withArguments("urgc_free_later");
				free_later->arguments()->insert(mk->identifierExpression("self"));
				returnStmt->insert(free_later);
				returnStmt->insert(mk->eos());
				auto stmt = mk->statement();
				stmt->insert(returnStmt);
				block->insert(stmt);
			}

			globalFn->insert(fn);
			//加到根作用域中
			rootDeclarationCtx->insert(globalFn);
			// 登记符号到空间
			symbolBuilder->visit(globalFn);
		}
	}

	virtual std::any visitClosureExpression(OrcParser::ClosureExpressionContext* ctx) override {
		auto info = ctx->goc_closureInfo();
		info->ctx = ctx;
		info->closureOriginalName = ctx->Id() ? ctx->Id()->getText() : "";

		allClosures.push_back(info.get());

		//关联父闭包
		if (closureStack.size() > 0) { //有父闭包
			info->parent = closureStack.back();
		}


		else { // 无父闭包
			// 记录存在闭包的函数
			auto fn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(ctx);
			vector_addOnce(functionDefinitionContextList, fn);
		}

		closureStack.push_back(info.get());
		auto ret = visitChildren(ctx);
		closureStack.pop_back();

		return ret;
	}
	virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx) override {

		do {
			//不在闭包内,记录哪些变量用到了被捕获的变量
			if (closureStack.size() == 0) {
				//auto varName = ctx->Id()->getText();
				////只需要查找本域的变量
				//auto varInfo = ast_findVarInfoByVarName(ctx, varName, nullptr);
				////如果变量是本函数内的变量
				//if (varInfo.isFound && varInfo.isInFunction()) {


				//	auto capInfo = varInfo.varDeclaration ? varInfo.varDeclaration->captureInfo
				//			: nullptr;
				//	if (varInfo.argumentDeclaration) {
				//		capInfo = varInfo.argumentDeclaration->captureInfo;
				//	}
				//	else if (varInfo.scopeStatement) {
				//		capInfo = varInfo.scopeStatement->captureInfo;
				//	}
				//	if (capInfo) {
				//		capInfo->addUsedExpr_once(ctx, nullptr); //登记为使用了捕获的变量
				//	}
				//}
			}
			//说明在闭包内
			if (closureStack.size() > 0) {

				auto lastClosure = closureStack.back();
				auto varName = ctx->Id()->getText();
				//只需要查找本域的变量
				auto varInfo = ast_findVarInfoByVarName(ctx, varName, nullptr);

				//全局变量，直接访问

				//如果变量是本函数内的变量
				if (varInfo.isFound && varInfo.isInFunction()) {
					//静态变量，需要考虑嵌套。  所以可能要改造成 指针;复杂,少见。暂不支持捕获 
					if (varInfo.varDeclaration && varInfo.varDeclaration->Static() != NULL) {
						//禁止同名字段
						auto errInfo = std::format("cloure can not use static var:{}", varInfo.varName);
						throw errInfo;
						break;
					}

					if (varInfo.varDeclaration) {
						auto isInClosure = ast_isAncestorOf(lastClosure->ctx, varInfo.varDeclaration);
						if (isInClosure) { //变量没有跨闭包
							break;
						}

						auto capInfo = varInfo.varDeclaration->goc_captureInfo();
						capInfo->varDeclaration = varInfo.varDeclaration;
						capInfo->type = "var";
						capInfo->varName = varInfo.varName;
						capInfo->addUsedExpr_once(ctx, closureStack.back());
						//记录到闭包内
						closureStack.back()->addCaptureVarInfo_once(capInfo);

						//块信息
						//需要特别考虑for语句
						{
							auto forCond = dynamic_cast<OrcParser::ForConditionContext*>(varInfo.varDeclaration->parent);
							if (forCond) { //捕获到的变量声明在for init condition内
								//for外面包一层
								auto blockCtx = ast_wrapBlock_outOfForStatement(forCond, mk);
								if (!blockCtx) {
									auto errInfo = std::format("upfind block failed.:{}", varInfo.varName);
									throw errInfo;
								}
								//变量声明提到外层的blockCtx中
								forCond->removeChild(varInfo.varDeclaration);
								blockCtx->insert(varInfo.varDeclaration, 0);

								auto blockInfo = blockCtx->goc_captureBlockInfo();
								blockInfo->addCaptureVarInfos_once(capInfo);
								//记录到闭包内
								//closureStack.back()->addBlockInfo_once(blockInfo);
								addBlockInfo_once_toUpClosures(blockInfo);
							}
							else { //普通的变量
								auto blockCtx = ast_findAncestorByType<OrcParser::BlockContext>(varInfo.varDeclaration);
								if (!blockCtx) {
									auto errInfo = std::format("upfind block failed.:{}", varInfo.varName);
									throw errInfo;
								}

								auto blockInfo = blockCtx->goc_captureBlockInfo();
								blockInfo->addCaptureVarInfos_once(capInfo);
								//记录到闭包内
								//closureStack.back()->addBlockInfo_once(blockInfo);
								addBlockInfo_once_toUpClosures(blockInfo);
							}
						}
					}

					// 如果变量来自scopeStatement
					else if (varInfo.scopeStatement) {
						auto isInClosure = ast_isAncestorOf(lastClosure->ctx, varInfo.scopeStatement);
						if (isInClosure) { //变量没有跨闭包
							break;
						}

						auto capInfo = varInfo.scopeStatement->goc_captureInfo();
						capInfo->scopeStatement = varInfo.scopeStatement;
						capInfo->type = "scope";
						capInfo->varName = varInfo.varName;
						capInfo->addUsedExpr_once(ctx, closureStack.back());
						//记录到闭包内
						closureStack.back()->addCaptureVarInfo_once(capInfo);

						//块信息
						auto blockInfo = varInfo.scopeStatement->block()->goc_captureBlockInfo();
						blockInfo->addCaptureVarInfos_once(capInfo);
						//记录到闭包内
						//closureStack.back()->addBlockInfo_once(blockInfo);
						addBlockInfo_once_toUpClosures(blockInfo);
					}
					// 如果变量来自参数
					else if (varInfo.argumentDeclaration) {
						auto isInClosure = ast_isAncestorOf(lastClosure->ctx, varInfo.argumentDeclaration);
						if (isInClosure) { //变量没有跨闭包
							break;
						}

						//那就需要把变量放到堆上，并修改对变量的访问。等于是加了间接的一层

						auto capInfo = varInfo.argumentDeclaration->goc_captureInfo();
						capInfo->argumentDeclaration = varInfo.argumentDeclaration;
						capInfo->type = "arg";
						capInfo->varName = varInfo.varName;
						capInfo->addUsedExpr_once(ctx, closureStack.back());
						//记录到闭包内
						closureStack.back()->addCaptureVarInfo_once(capInfo);

						auto parent = ast_findFirstAncestorByTwoType<OrcParser::FunctionDefinitionContext, OrcParser::ClosureExpressionContext>(
							varInfo.argumentDeclaration);

						//如果参数属于函数
						auto fn = dynamic_cast<OrcParser::FunctionDefinitionContext*>(parent);
						if (fn) {
							//auto fn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(varInfo.argumentDeclaration);
							//块信息
							auto blockInfo = fn->block()->goc_captureBlockInfo();
							blockInfo->addCaptureVarInfos_once(capInfo);
							//记录到闭包内
							//closureStack.back()->addBlockInfo_once(blockInfo);
							addBlockInfo_once_toUpClosures(blockInfo);
						}

						//如果参数属于闭包
						auto closure = dynamic_cast<OrcParser::ClosureExpressionContext*>(parent);
						if (closure) {
							//块信息
							auto blockInfo = closure->block()->goc_captureBlockInfo();
							blockInfo->addCaptureVarInfos_once(capInfo);
							//记录到闭包内
							//closureStack.back()->addBlockInfo_once(blockInfo);
							addBlockInfo_once_toUpClosures(blockInfo);
						}
					}


				}
			}
		} while (0);


		return visitChildren(ctx);
	}

	void addBlockInfo_once_toUpClosures(std::shared_ptr<CaptureBlockInfo> blockInfo) {
		for (int i = closureStack.size() - 1; i >= 0; i--) {
			auto closure = closureStack[i];
			auto isAncestor = ast_isAncestorOf(closure->ctx, blockInfo->blockCtx);
			if (isAncestor) {//blockInfo在closure里，就不用再捕获了
				break;
			}
			//记录到闭包内
			closure->addBlockInfo_once(blockInfo);
		}
	}

	//super要怎么处理啊
	virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext* ctx) override {

		//在闭包内
		if (closureStack.size() > 0) {
			//在闭包内
			if (closureStack.size() > 0) {
				auto cap = ctx->goc_captureInfo();
				cap->superExpression = ctx;
				cap->type = "super";
				cap->varName = "super";
				//记录到闭包内
				closureStack.back()->captureVarInfos.push_back(cap);
			}
		}
		return visitChildren(ctx);
	}
	virtual std::any visitThisExpression(OrcParser::ThisExpressionContext* ctx) override {
		//在闭包内
		if (closureStack.size() > 0) {
			auto fn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(
				ctx);
			//如果参数属于函数
			if (fn) {

				auto cap = fn->block()->goc_captureInfo();
				cap->thisExpression = ctx;
				cap->type = "self";
				cap->varName = "self";

				cap->addUsedThisExpr_once(ctx, closureStack.back());

				//记录到闭包内
				closureStack.back()->captureVarInfos.push_back(cap);



				//auto fn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(varInfo.argumentDeclaration);
				//块信息
				auto blockInfo = fn->block()->goc_captureBlockInfo();
				blockInfo->addCaptureVarInfos_once(cap);
				//记录到闭包内
				//closureStack.back()->addBlockInfo_once(blockInfo);
				addBlockInfo_once_toUpClosures(blockInfo);
			}
		}
		return visitChildren(ctx);
	}
	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override {
		return visitChildren(ctx);
	}
};
//只遍历 根规则 

std::any OnlyRootsVisitor::visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx)  {
	return defaultResult();
}
std::any OnlyRootsVisitor::visitClassDefinition(OrcParser::ClassDefinitionContext* ctx)  {
	return defaultResult();
}
std::any OnlyRootsVisitor::visitStructDefinition(OrcParser::StructDefinitionContext* context)  {
	return defaultResult();
}

//不进入，加快解析
std::any OnlyRootsVisitor::visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* context)  {
	return defaultResult();
}

//不进入，加快解析
std::any OnlyRootsVisitor::visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* context)  {
	return defaultResult();
}

//不进入，加快解析
std::any OnlyRootsVisitor::visitEnumDefinition(OrcParser::EnumDefinitionContext* ctx)  {
	return defaultResult();
}

//不进入，加快解析
std::any OnlyRootsVisitor::visitVarDeclaration(OrcParser::VarDeclarationContext* context)  {
	return defaultResult();
}

//类型预声明; 结构体和类的预声明， 例：
//类型预声明，可以处理循环引用的问题
//typedef struct tagSuiCore$AppEventLoopMessage SuiCore$AppEventLoopMessage;
//typedef struct tagVtable_SuiCore$AppEventLoopMessage Vtable_SuiCore$AppEventLoopMessage;
//typedef struct tagSuiCore$App SuiCore$App;
//typedef struct tagVtable_SuiCore$App Vtable_SuiCore$App;
class  TypePreDeclarationVisitor : public OnlyRootsVisitor {
public:
	bool needMakeStaticStructCode = true;

	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override {
		string ret =  std::format("typedef struct tag{} {};\n", ctx->fullname, ctx->fullname);
		//虚表
		ret += std::format("typedef struct tagVtable_{} Vtable_{};\n", ctx->fullname, ctx->fullname);
		return ret;
		//return visitChildrenReturnString(ctx);
	}
	virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext* context) override {
		if (context->isStaticStruct) { //闭包会产生static struct
			if (!needMakeStaticStructCode) { //不需要产生代码
				return std::string("");
			}
		}
		auto ret = std::format("typedef struct tag{} {};\n", context->fullname, context->fullname);
		return ret;
	}

	//不进入，加快解析
	virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext* ctx) override {
		auto ret = std::format("typedef enum enum{} {};\n", ctx->fullname, ctx->fullname);
		return ret;
	}
};

//添加self参数
std::any AddSelfArgumentVisitor::visitClassDefinition(OrcParser::ClassDefinitionContext* ctx)  {
	curClass = ctx;
	auto ret = visitChildrenReturnString(ctx);
	curClass = NULL;
	return ret;
}
std::any AddSelfArgumentVisitor::visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx)  {
	curExtension = ctx;
	auto ret = visitChildrenReturnString(ctx);
	curExtension = NULL;
	return ret;
}
std::any AddSelfArgumentVisitor::visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx)  {
	auto typeName = curExtension 
		? curExtension->Id()->getText() 
		: curClass->Id(0)->getText();
	auto fn = ctx->functionDefinition();
	auto ext = ctx->externFunctionDeclaration();


	auto arg = mk->argDecl();
	auto typeId = mk->Id(typeName);
	auto text = typeId->getText();
	auto typePointer = mk->pointer(typeId);
	text = typePointer->getText();
	auto type = mk->type(typePointer);
	text = type->getText();
	arg->insert(type);
	arg->insert(mk->Id("self"));

	if (fn) {
		auto args = fn->argumentsDeclaration();

		args->insert(arg, 0);
	}
	else if (ext) {
		auto args = ext->argumentsDeclaration();
		args->insert(arg, 0);
	}
	return defaultResult();
}

//添加OutRef参数用来接收引用类型的返回值
class  AddOutRefArgumentVisitor : public OnlyRootsVisitor {
public:
	//需要初始化
	AstMake* mk = NULL;

	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override {
		auto ret = visitChildrenReturnString(ctx);
		return ret;
	}
	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) override {
		auto ret = visitChildrenReturnString(ctx);
		return ret;
	}

	virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}


	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override {
		auto type = ctx->type();
		auto ref = type->ref();
		if (ref) { //返回值是引用
			auto arg = mk->argDecl();
			auto typeId = mk->Id(ref->Id()->getText());
			auto typePointer = mk->pointer(typeId, 2);
			auto type = mk->type(typePointer);
			arg->insert(type);
			arg->insert(mk->Id("__outRef__"));

			ctx->argumentsDeclaration()->insert(arg, 0);
		}
		return defaultResult();
	}


	virtual std::any visitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext* ctx) override {
		auto type = ctx->type();
		auto ref = type->ref();
		if (ref) { //返回值是引用
			auto arg = mk->argDecl();
			auto typeId = mk->Id(ref->Id()->getText());
			auto typePointer = mk->pointer(typeId, 2);
			auto type = mk->type(typePointer);
			arg->insert(type);
			arg->insert(mk->Id("__outRef__"));

			ctx->argumentsDeclaration()->insert(arg, 0);
		}
		
		return defaultResult();
	}
};

class TerminalNodeInfo {
public:
	antlr4::tree::ParseTree* parent;
	antlr4::tree :: TerminalNode * term = NULL;
	int index = 0; 
	static TerminalNodeInfo findTerminalNodeInfoByText(antlr4::tree::ParseTree* ctx, string text) {
		TerminalNodeInfo info;
		info.parent = ctx;

		for (int i = 0; i < ctx->children.size(); i++) {
			auto kid = ctx->children[i];
			auto term = dynamic_cast<antlr4::tree::TerminalNode*>(kid);
			if (term && term->getText() == text) {
				info.index = i;
				info.term = term;
				break;
			}
		}
		return info;
	}
};

//语法转译

/*
- [v] 属性访问 a.b =>  如果a是1级指针 a->b 
- [v] 成员方法 class A{ void fn()} =>  class A{void fn(A*self)}
- [v] 扩展方法 extension A{void fn()} => extension A{void fn(A*self)}
- [v] 函数返回值是引用  A@ fn() => A@ fn(A** __outRef__)  
- [v] 父类成员 aa.xx =>  ((Super *)aa).xx
- [v] 成员赋值 a.b = c => 如果a.b是引用,  urgc_set_field(a, &a.b, c)
- [v] 引用类型的变量赋值 a = b => 如果a是引用， urgc_set_var(&a, b)

- 调用父类方法 super.fn() => super_fn_fullname(self)    ~~转为全局函数，代码生成时再转换吧。 提前转换的话，就丢失语义信息了
- 调用扩展方法 a.b() => fullname_b(a)        ~~转为全局函数，代码生成时再转换吧.提前转换的话，就丢失语义信息了

- [v] 调用方法  a.b() =>
	a.b(a)

- [v] 调用方法  super.b() =>
	super.b(self)

- 调用扩展方法  a.b.c() =>  
	a.b.c(a.b)  
	此时语义是有变化的，因为a.b调用了两次。 所以在后续生成代码时， a.b.c会被替换成扩展全局函数?,就回归正常了


- [v] 调用方法  a.b.c() =>  
	Type * tmpForThis = NULL;
	(tmpForThis = a.b).c(tmpForThis)
	[v] 需要区分扩展方法。 扩展方法不用额外处理. 


- [v] 调用返回值是引用的函数  a() => 
	Type@ tmpForReturn = NULL;
	a(&tmpForReturn);


- scope语句 a~{}  =>
	{	
		Type* o = a();
		
		o.__exit__();
	}
- 闭包 ^void (){}  =>  createClosure()
- 有名闭包 ^void fn(){} => 
	Closure@ fn = null;
	fn = createClosure()
- 调用闭包 fn() => fn.invoke(fn)
*/
class  TranslateVisitor : public OrcBaseVisitor {
public:
	//需要初始化
	AstMake* mk = NULL;
	std::shared_ptr<SymbolSpace> space = NULL; //用来查找符号

	//virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx) override {
	//	return visitChildren(ctx);
	//}


	//赋值语句, 需要支持引用
	virtual std::any visitAssignmentExpression(OrcParser::AssignmentExpressionContext* ctx) override {
		if (ctx->translateVisited) { //标记为不用处理
			return defaultResult();
		}

		auto left = ctx->singleExpression(0);

		//printf("left:%s\n", ctx->getText().c_str());

		auto exprType = ast_calcSymbolTypeOfExpressionResult(left, space);
		if (exprType) {

			auto typeRef = std::dynamic_pointer_cast<SymbolTypeRef>(exprType->type);
			//左值则引用类型
			if (typeRef ) {
				auto typeDefClass = ast_findSymbolDefinitionClass_byTypeName(typeRef->getNakeTypeName(), space);
				//左值是变量 
				//-引用类型的变量赋值 a = b = > 如果a是引用， urgc_set_var(&a, b)
				{
					auto identifierExpr = dynamic_cast<OrcParser::IdentifierExpressionContext*>(left);
				
					if (identifierExpr) {
						if (typeRef->isWeak) {//用于tmpClosure_xx.临时变量，不需要走Urgc记录
							printf("Translate assign typeRef\n");
							//return visitChildren(ctx);
						}
						else {
							auto call = mk->callExpression_byFunctionName_withArguments(
								typeDefClass ? "urgc_set_var_class": "urgc_set_var");
							auto arguments = call->arguments();

							// &a
							arguments->insert(mk->getAddress(identifierExpr));
							arguments->insert(ctx->singleExpression(1));

							ast_replaceChild(ctx, call);
							return visitChildren(call);
						}
					}
				}


				//左值是成员
				//成员赋值 a.b = c => 如果a.b是引用,  urgc_set_field(a, &a.b, c)

				auto dotExpr = dynamic_cast<OrcParser::MemberDotExpressionContext*>(left);
				if (dotExpr) {
					auto objExpr = dotExpr->singleExpression();
					//改为 urgc_set_field(obj, offsetof(Class, propName), valExp);
					auto objTypeInfo = ast_calcSymbolTypeOfExpressionResult(objExpr, space);
					if (objTypeInfo) {
						auto call = mk->callExpression_byFunctionName_withArguments(typeDefClass ? "urgc_set_field_class":"urgc_set_field");
						auto arguments = call->arguments();
						// a
						arguments->insert(dotExpr->singleExpression());
						// (void*)offsetof(Class, b); 需要考虑继承关系。 如果b是在父类定义的话
						auto offsetFieldName = dotExpr->Id()->getText();
						auto offsetofCall = mk->callExpression_byFunctionName_withArguments("offsetof");
						auto objDef = objTypeInfo->findSymbolDefinition();
						auto offsetClassName = objTypeInfo->type->getNakeTypeName();
						{
							auto objClassDef = dynamic_cast<SymbolDefinitionClass*>(objDef.get());
							if (objClassDef) {
								auto originalDef = objClassDef->findOriginalDefinedMemberByName_includeSupers(offsetFieldName);
								offsetClassName = originalDef->classDef->fullname;
							}
						}
						
						auto idClassName = mk->identifierExpression(offsetClassName);
						idClassName->prevent_classNameIdExpr_translate = true;
						offsetofCall->arguments()->insert(idClassName);
						offsetofCall->arguments()->insert(mk->identifierExpression(offsetFieldName));
						arguments->insert(
							mk->castExpression(
								mk->type(
									mk->pointer(
										mk->primitiveType("void")
										, 1)
								),
								//mk->getAddress(left)
								offsetofCall
							)
						);
						// c
						arguments->insert(ctx->singleExpression(1));

						ast_replaceChild(ctx, call);
						return visitChildren(call);
					}
					else {
						//如果左值中的a是普通的变量
						auto identifierExpr = dynamic_cast<OrcParser::IdentifierExpressionContext*>(objExpr);
						if (identifierExpr) {
							auto call = mk->callExpression_byFunctionName_withArguments(typeDefClass ? "urgc_set_field_class" : "urgc_set_field");
							auto arguments = call->arguments();

							// a
							arguments->insert(dotExpr->singleExpression());
							// &a.b
							arguments->insert(
								mk->castExpression(
									mk->type(
										mk->pointer(
											mk->primitiveType("void")
											, 2)
									),
									mk->getAddress(left)));
							// c
							arguments->insert(ctx->singleExpression(1));


							ast_replaceChild(ctx, call);
							return visitChildren(call);
						}
						//其他情况，就需要创建临时变量暂存了
						{
							auto hostFn = ast_findHostAstNode_forNumberReturn(ctx);
							hostFn->numberReturn++;
							auto tmpMemberDot_varName = std::format("tmpValue_{}", hostFn->numberReturn);


							auto exprType = ast_calcSymbolTypeOfExpressionResult(dotExpr->singleExpression(), space);
							auto refType = std::dynamic_pointer_cast<SymbolTypeRef>(exprType->type) ;
							if (refType) { //只是临时接收而已，如果是引用，直接改为指针即可
								exprType->type = refType->toSymbolTypePointer();
							}
							auto isPointer = std::dynamic_pointer_cast<SymbolTypePointer>(exprType->type) != nullptr;
							//声明 User@ tmpMemberDot_varName = NULL;
							auto astType = exprType->type->toAstType(mk);
							auto type = mk->type(astType);
							auto varDecl = mk->varDeclaration(type, tmpMemberDot_varName, mk->nullLiteralExpression());

							auto statement = ast_findAncestorByType<OrcParser::StatementContext>(ctx);
							if (statement) {
								//临时变量声明语句
								auto varDeclarationStatement = mk->statement();
								varDeclarationStatement->insert(varDecl);
								varDeclarationStatement->translateVisited = true;
								statement->translateVisited = true;
								ast_insertChild_before(statement, varDeclarationStatement);

								//a->b()->c 改成：
								//type* tmpVar = null;
								// urgc_set_field(tmpVar = a->b()), &tmpVar->c, value)

								auto call = mk->callExpression_byFunctionName_withArguments(typeDefClass ? "urgc_set_field_class" : "urgc_set_field");
								auto arguments = call->arguments();

								auto assign = mk->assignmentExpression();
								assign->insert(mk->identifierExpression(tmpMemberDot_varName));
								assign->insert(dotExpr->singleExpression());

								auto memberDotFromTmp = mk->memberDotExpr(
									mk->identifierExpression(tmpMemberDot_varName),
									dotExpr->Id()->getText(),
									isPointer  ? "->":"."
								);

								// a
								arguments->insert(assign);
								// &a.b
								arguments->insert(mk->getAddress(memberDotFromTmp));
								// c
								arguments->insert(ctx->singleExpression(1));


								ast_replaceChild(ctx, call);
								return visitChildren(call);
							}

							else {
								std::cout << "没找到statement\n";
							}
						}
					}

				}
			}
		}

		auto ret = visitChildren(ctx);
		return ret;
	}


	virtual std::any visitStatement(OrcParser::StatementContext* ctx) override {
		auto code = ctx->getText();
		if (ctx->translateVisited) { //表示是否已处理过。  在callExpression处理中，会添加新的statement,导致遍历index错位
			return defaultResult();
		}
		auto ret = visitChildren(ctx);
		return ret;
	}

	virtual std::any visitClosureType(OrcParser::ClosureTypeContext* ctx) override {
		//添加self参数
		auto args = ctx->argumentsDeclaration();
		auto argSelf = mk->argDecl();
		args->insert(argSelf, 0);

		argSelf->insert(
			mk->type(
				mk->pointerByTypeName("void")
			)
		);
		argSelf->insert(mk->Id("self"));
		return defaultResult();
	}
	//函数调用， 需要支持扩展函数
	virtual std::any visitCallExpression(OrcParser::CallExpressionContext* ctx) override {

		auto code = ctx->getText();
		printf("code:%s\n", code.c_str());
		auto expr = ctx->singleExpression();
		auto args = ctx->arguments();

		auto exprTypeInfo = ast_calcSymbolTypeOfExpressionResult(expr, space);
		if (!exprTypeInfo) {
			throw std::format("visitCallExpression failed.  calcSymbolTypeOf expr failed.  code:{}", code);
		}
		//exprTypeInfo->findSymbolDefinition
		//如果调用者是 闭包
		{
			//TODO 闭包的类型，也要考虑转化return @的情况
			auto typeClosure = std::dynamic_pointer_cast<SymbolTypeClosure>(exprTypeInfo->type);
			if (typeClosure) {
				//如果访问表达式是纯的，就不需要生成tmp变量暂存
				auto isPure = ast_isPureAccessExpression(expr);
				if (isPure) {

					//添加参数
					{

						auto quoteExpr = mk->parenthesizedExpression();
						auto seqExpr = mk->expressionSequence();
						quoteExpr->insert(seqExpr);
						seqExpr->addChild(expr);
						auto closureSelf = mk->castExpression(
							mk->type(
								mk->pointer(
									mk->primitiveType("void")
								)
							), 
							quoteExpr
						);
						args->insert(closureSelf, 0);
					}


					auto quoteAssignExpr = mk->parenthesizedExpression(expr);
					// call closure: a.b.c() => (*a.b.c)((void*)a.b.c, ...)
					auto derefExpr = mk->deref(quoteAssignExpr);
					auto quoteExpr = mk->parenthesizedExpression(derefExpr);
					ast_replaceChild_specificParent(ctx, expr, quoteExpr);

				}
				else {
					auto ownFn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(ctx);
					ownFn->numberTmpThis++;
					auto tmpVarName = std::format("tmpClosure{}", ownFn->numberTmpThis);
					printf("闭包\n");
					auto stmt = mk->statement();
					auto statement = ast_findAncestorByType<OrcParser::StatementContext>(ctx);
					//临时变量声明语句
					auto astClosureType = dynamic_cast<OrcRuleContext*>(typeClosure->toAstType(mk));
					astClosureType->isTmpThisVarForClosure = true; //记为临时的变量，不需要记录引用
					auto varDecl = mk->varDeclaration(
						mk->type(astClosureType), tmpVarName, NULL
					);
					/*auto fnVarDecl = ast_createAstFunctionPointerVarDeclaration(
						mk,
						typeClosure->returnType,
						tmpVarName,
						typeClosure->args,
						2
					);*/
					//{
					//	//额外添加self参数
					//	auto selfArgDecl = mk->argDecl();
					//	selfArgDecl->insert(
					//		mk->type(
					//			mk->pointer(mk->primitiveType("void"))
					//		));
					//	selfArgDecl->insert(mk->Id("self"));
					//	fnVarDecl->argumentsDeclaration()->insert(selfArgDecl, 0);
					//}

					//auto varDecl = mk->varDeclaration_nake();
					//varDecl->insert(fnVarDecl);
					auto varDeclarationStatement = mk->statement();
					varDeclarationStatement->insert(varDecl);

					varDeclarationStatement->translateVisited = true;
					statement->translateVisited = true;
				
					ast_insertChild_before(statement, varDeclarationStatement);
					auto assign = mk->assignmentExpression();
					assign->insert(mk->identifierExpression(tmpVarName));
					assign->insert(expr);

					auto quoteAssignExpr = mk->parenthesizedExpression(assign);
					// call closure: closure() => (*(tmp = closure))(tmp)
					auto derefExpr = mk->deref(quoteAssignExpr);
					auto quoteExpr = mk->parenthesizedExpression(derefExpr);
					ast_replaceChild_specificParent(ctx, expr, quoteExpr);

					//添加参数
					{
						auto closureSelf = mk->castExpression(
							mk->type(
								mk->pointer(
									mk->primitiveType("void")
								)
							),
							mk->identifierExpression(tmpVarName)
						);
						args->insert(closureSelf, 0);
					}

					expr = quoteExpr;
				}

			}
		}

		// 调用方法
		{
			auto dotExpr = dynamic_cast<OrcParser::MemberDotExpressionContext*>(expr);
			if (dotExpr) {
				auto objExpr = dotExpr->singleExpression();
				auto propName = dotExpr->Id()->getText();
				if (propName == "invalidReact") {
					printf("invalidReact\n");
				}


				//printf("prev call\n");
				//ast_printTree(ctx, NULL);

				auto isExtensionMethod = false;
				auto memberInfo = MemberInfo::findMemberInfo(objExpr, propName, space);

				if (memberInfo.typeDef == nullptr) {
					throw std::format("未找到成员类型的定义:{}\n", code);
				}
				//判断是不是扩展方法. 扩展方法调用。 objExpr转为null
				if (memberInfo.extensionDef) { // 是扩展函数; 加完后，程序语义实际上是变了的？
					
					auto objExprSymType = ast_calcSymbolTypeOfExpressionResult(objExpr, space);
					
					auto newObjExpr = mk->castExpression(
						mk->type(
							memberInfo.typeInfo->type->toAstType(mk)
						),
						mk->nullLiteralExpression()
					);
					ast_replaceChild_specificParent(dotExpr, objExpr, newObjExpr); //变为 a.b => ((Type*)null).b(a); 这样语义就没有变化了

					//如果import列表中，不存在该路径的话，就需要加入hiddenImports中
					space->addHiddenImport_byPath_ifNeed(memberInfo.methodDef->hostSpace->path);
					
					class GenCodeVisitor;

					//printf("prev call2\n");
					//ast_printTree(ctx, NULL);
					if (std::dynamic_pointer_cast<SymbolTypeRef>(objExprSymType->type) 
						|| 
						std::dynamic_pointer_cast<SymbolTypePointer>(objExprSymType->type)

						) {
						//如果是类的直接扩展
						if (memberInfo.extensionDef->name == memberInfo.typeDef->name) {
							args->insert(objExpr, 0); //添加self
						}
						else {// 说明是父类的
							auto _classDef = memberInfo.extensionDef->hostSpace->findSymbolDefinitionByName_includeImports(
								memberInfo.extensionDef->name
							);
							auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(_classDef);


							auto pointer = std::make_shared<SymbolTypePointer>();
							pointer->typeName = memberInfo.extensionDef->name;
							auto type = pointer->toAstType(mk);
							auto selfObjExpr = mk->castExpression(
								mk->type(
									type
								),
								objExpr
							);
							args->insert(selfObjExpr, 0); //添加self
						}

					}
					else {
						// 调用者是不是指针。 可能是结构体...
						// 
						//扩展方法还有一个特例： fnReturnStruct().extensionFunc()   caller是函数，且返回值是结构体的情况下
						if (1&&dynamic_cast<OrcParser::CallExpressionContext*>(objExpr)) {
							//需要有临时变量来承载结构体

							auto ownFn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(ctx);
							ownFn->numberTmpThis++;
							auto tmpVarName = std::format("tmpStructThis{}", ownFn->numberTmpThis);

							auto objExprAstType = objExprSymType->type->toAstType(mk);
							auto varDecl = mk->varDeclaration(
								mk->type(objExprAstType), tmpVarName, NULL
							);

							auto varDeclarationStatement = mk->statement();
							varDeclarationStatement->insert(varDecl);


							//插入变量声明
							auto statement = ast_findAncestorByType<OrcParser::StatementContext>(ctx);
							statement->translateVisited = true;
							ast_insertChild_before(statement, varDeclarationStatement);

							//前面已经改造 a().ext() 到  ((Type*)null).ext(a())
							//这里要改造((Type*)null).ext(a())为  ((Type*)null).ext((tmpStructThis=a(), &tmpStructThis))
							auto assign = mk->assignmentExpression();
							assign->insert(mk->identifierExpression(tmpVarName));
							assign->insert(objExpr);

							auto getAddr = mk->getAddress(mk->identifierExpression(tmpVarName));
							auto seq = mk->expressionSequence();
							seq->insert(assign);
							seq->insert(getAddr);
							auto quote = mk->parenthesizedExpression();
							quote->insert(seq);
							args->insert(quote, 0); //添加self

							//printf("\n\n扩展函数==================. %d\n", args->singleExpression().size());
							//ast_printTree(ctx, NULL);
						}
						else {
							args->insert(mk->getAddress(objExpr), 0); //添加self
						}
					}
					//auto str = genCode(ctx, space);
					//printf("lala:%s\n", str.c_str());
				}
				else if (memberInfo.extensionDef == nullptr) { //不是扩展函数，才需要添加self
					// -调用方法  a.b() = >
					// a.b(a)
					if (memberInfo.methodDef != nullptr) { //只有方法，才需要添加self
						auto done = false;
						{
							auto identExpr = dynamic_cast<OrcParser::IdentifierExpressionContext*>(objExpr);
							auto superExpr = dynamic_cast<OrcParser::SuperExpressionContext*>(objExpr);
							auto thisExpr = dynamic_cast<OrcParser::ThisExpressionContext*>(objExpr);
							if (identExpr) {
								//	- 调用方法  super.b() = >
								//	super.b(self)
								auto idText = identExpr->getText();
								if (idText == "super" || idText == "self") {
									args->insert(mk->identifierExpression("self"), 0); //添加se
								}
								else {
									args->insert(identExpr, 0); //添加self
								}
								done = true;
							}
							else if (thisExpr) {
								args->insert(mk->identifierExpression("self"), 0); //添加self
								done = true;
							}
							else if (superExpr) {
								args->insert(mk->identifierExpression("self"), 0); //添加self
								done = true;
							}
						}
						//	- 调用方法  a.b.c() = >
						//	Type * tmpThis = NULL;
						//(tmpForThis = a.b).c(tmpThis)
						if (!done) {
							auto typeInfo = ast_calcSymbolTypeOfExpressionResult(objExpr, space);
							if (typeInfo) {
								auto isPure = ast_isPureAccessExpression(objExpr);
								if (isPure) { // obj表达式无副作用
									args->insert(objExpr, 0, false); //添加self
								}
								else {
									//临时变量，不需要采用引用
									if (std::dynamic_pointer_cast<SymbolTypeRef>(typeInfo->type)) {
										auto pointerType = std::make_shared<SymbolTypePointer>();
										pointerType->typeName = typeInfo->type->getNakeTypeName();
										typeInfo->type = pointerType;
									}
									auto curFunc = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(objExpr);
									curFunc->numberTmpThis++;
									// 起个名字
									string tmpForThis_varName = std::format("tmpThis_{}", curFunc->numberTmpThis);
	

									auto astType = typeInfo->type->toAstType(mk);
									auto type = mk->type(astType);
									auto varDecl = mk->varDeclaration(type, tmpForThis_varName, mk->nullLiteralExpression());

									auto statement = ast_findAncestorByType<OrcParser::StatementContext>(ctx);
									if (statement) {
										//临时变量声明语句
										auto varDeclarationStatement = mk->statement();
										varDeclarationStatement->insert(varDecl);
										auto code = statement->getText();
										statement->translateVisited = true;
										varDeclarationStatement->translateVisited = true;
										ast_insertChild_before(statement, varDeclarationStatement);

										// 赋值临时变量
										{
										
											auto tmpAssignmentExpr = mk->assignmentExpression();
											auto quoteExpr = mk->parenthesizedExpression(tmpAssignmentExpr);
											ast_replaceChild_specificParent(dotExpr, objExpr, quoteExpr);

											tmpAssignmentExpr->insert(mk->identifierExpression(tmpForThis_varName));
											tmpAssignmentExpr->insert(objExpr);
										}

										//使用临时变量，作为self参数
										args->insert(mk->identifierExpression(tmpForThis_varName), 0); //添加se
									}	
									else {
										std::cout << "没找到statement\n";
									}

								}
							}

						}
					}
				}
			}
		}

		// 返回值是引用
		/*-调用返回值是引用的函数  a() = >
			Type@ tmpReturn = NULL;
			a(&tmpReturn);
		*/
		auto returnType = ast_calcSymbolTypeOfExpressionResult(ctx, space);
		if (returnType) {
			auto returnRefType = std::dynamic_pointer_cast<SymbolTypeRef>(returnType->type);
			if (returnRefType) {
				//特殊情况处理
				// 如果此函数调用，属于varDecl的init表达式，就可以直接使用var使用return
				auto found = ast_findFirstAncestorByTwoType<OrcParser::VarDeclarationContext, OrcParser::StatementContext>(ctx);
				auto foundVarDeclarationCtx = dynamic_cast<OrcParser::VarDeclarationContext*>(found);
				if (foundVarDeclarationCtx && foundVarDeclarationCtx->singleExpression() == ctx 
					&& foundVarDeclarationCtx->type() 
					&& foundVarDeclarationCtx->type()->ref() //并且是引用类型
					) {
					// User@ tmp = createUser() =>  URGC_VAR_CLEANUP User* tmp = createUser((tmp = NULL, &tmp))

					
						//添加outRef变量：    fn(&tmpReturn_0_0)
					auto returnVarName = foundVarDeclarationCtx->Id()->getText();

					auto quote = mk->parenthesizedExpression();
					auto seq = mk->expressionSequence();
					quote->insert(seq);
					auto assignNull = mk->assignmentExpression();
					assignNull->insert(mk->identifierExpression(returnVarName));
					assignNull->insert(mk->nullLiteralExpression());
					assignNull->translateVisited = true;

					seq->insert( assignNull );
					seq->insert(
						mk->getAddress(
							mk->identifierExpression(returnVarName)
						)
					);
					args->insert(quote, 0); //添加se
				}  
				else {

					//auto start = ctx->getStart();
						// 起个名字, 名字在所在的function唯一
					auto hostFn = ast_findHostAstNode_forNumberReturn(ctx);
					hostFn->numberReturn++;
					auto tmpReturn_varName = std::format("tmpReturn_{}", hostFn->numberReturn);

					//声明 User@ tmpReturn_line_col = NULL;
					auto astType = returnRefType->toAstType(mk);
					auto type = mk->type(astType);
					auto varDecl = mk->varDeclaration(type, tmpReturn_varName, mk->nullLiteralExpression());
					//临时变量声明语句
					auto varDeclarationStatement = mk->statement();
					varDeclarationStatement->insert(varDecl);
					varDeclarationStatement->translateVisited = true;

					//添加outRef变量：    fn(&tmpReturn_0_0)
					args->insert(
						mk->getAddress(
							mk->identifierExpression(tmpReturn_varName)
						)
						, 0); //添加se


					//不在函数内部，在成员变量的初始化表达式,需要特别处理tmpReturn变量的位置
					auto found = ast_findAncestorByType<OrcParser::ClassFieldDeclarationContext>(ctx);
					
					if (found && found->assignRightPart() && ast_isAncestorOf(found->assignRightPart(), ctx)) {
						found->translateVisited = true;
						//所以ClassDefinitionBlock里，就存在有ClassFieldDeclarationContext, StatementContext, MethodContext, 需要在生成时特殊处理
						//statement->translateVisited = true;
						ast_insertChild_before(found, varDeclarationStatement);
					}
					else {
						//在函数内部

						auto statement = ast_findAncestorByType<OrcParser::StatementContext>(ctx);
						if (statement) {
							statement->translateVisited = true;
							ast_insertChild_before(statement, varDeclarationStatement);
						}

						else {
							std::cout << "没找到statement\n";
						}
					}

				}

			}
		}

		//printf("last call\n");
		//ast_printTree(ctx, NULL);

		auto ret = visitChildren(ctx);

		//printf("last call2\n");
		//ast_printTree(ctx, NULL);

		return ret;
	}

	/*
	new ClassName()的几种转义:
	- Type *a = new Type()  => Type *a = Type_new(&a);
	其他情况一律添加临时变量，用来接收new出来的对象

	*/
	virtual std::any visitNewExpression(OrcParser::NewExpressionContext* ctx) override {
		auto className = ctx->Id()->getText();
		//情况1, 属于变量声明的初始化表达式中,可以直接使用变量，作为pOwner
		{
			auto n = ast_findFirstAncestorByTwoType<
				OrcParser::StatementContext,
				OrcParser::VarDeclarationContext
			>(ctx);
			auto varDecl = dynamic_cast<OrcParser::VarDeclarationContext*>(n);
			if (varDecl && varDecl->singleExpression() == ctx) {
				// 添加参数 &varName
				auto varName = varDecl->Id()->getText();
				auto args = ctx->arguments();
				auto arg0 = mk->getAddress(
					mk->identifierExpression(varName)
				);
				args->insert(arg0, 0);
				return defaultResult();
			}
		}
		
		//其他情况，统一创建临时变量
		auto stmt = dynamic_cast<OrcRuleContext*>(ast_findFirstAncestorByTwoType<
			OrcParser::ClassFieldDeclarationContext,
			OrcParser::StatementContext>(ctx));
		stmt->translateVisited = true;
		auto varStmt = mk->statement();
		varStmt->translateVisited = true;
		ast_insertChild_before(stmt, varStmt);

		// 起个名字, 名字在所在的function唯一
		auto hostFn = ast_findHostAstNode_forNumberReturn(ctx);
		hostFn->numberReturn++;
		auto tmpReturn_varName = std::format("tmpNewOwner_{}", hostFn->numberReturn);

		auto type = mk->type( mk->refByTypeName(className) );
		auto varDecl = mk->varDeclaration(type, tmpReturn_varName, mk->nullLiteralExpression());
		//添加临时变量声明
		varStmt->insert(varDecl);

		auto arg0 = mk->getAddress(
			mk->identifierExpression(tmpReturn_varName)
		);
		ctx->arguments()->insert(arg0, 0);

		return defaultResult();
	}

	virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* ctx) override {
		if (ctx->translateVisited) {
			return defaultResult();
		}
		return visitChildren(ctx);
	}

	//成员访问，需要支持父类属性和方法
	virtual std::any visitMemberDotExpression(OrcParser::MemberDotExpressionContext* ctx) override {
		auto expr = ctx->singleExpression();
		auto tt = ctx->getText();
		auto exprtt = expr->getText();
		auto exprType = ast_calcSymbolTypeOfExpressionResult(expr, space);

		//处理'.', 根据类型变成'->'
		if (exprType != nullptr) {
			auto typePointer = std::dynamic_pointer_cast <SymbolTypePointer>(exprType->type);
			if (typePointer 
				|| std::dynamic_pointer_cast<SymbolTypeRef>(exprType->type)
				) {
				//替换终结符'.' 为'->'
				auto info = TerminalNodeInfo::findTerminalNodeInfoByText(ctx, ".");
				if (info.term) {
					auto opTerm = mk->mkTerminal(0, "->");
					ctx->replaceChild(info.term, opTerm);
				}
			}
		}


		auto propName = ctx->Id()->getText();
		//auto identifierExpr = dynamic_cast<OrcParser::IdentifierExpressionContext*>(expr);
		if (propName == "layout") {
			//printf("propName:%s\n", propName.c_str());
		}

		auto superExpr = dynamic_cast<OrcParser::SuperExpressionContext*>(expr);
		if (exprType != nullptr 
			&& superExpr == nullptr // super.xx 要保留着,不用变换。在GenCodeVisitor Class_method(self, ...)
			) {//- 父类成员 aa.xx =>  ((Super *)aa).xx
			auto symbolDef = exprType->findSymbolDefinition();
			auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(symbolDef);
			//获取父类的成员
			if (classDef) {
				//这里不用考虑扩展
				auto memberDto = classDef->findOriginalDefinedMemberByName_includeSupers(propName);
				if (memberDto) {
					//成员来自父类
					if (memberDto->classDef->name != classDef->name) {
						auto castType = mk->type(
							mk->pointer(
								mk->Id(memberDto->classDef->name),
								1
							)
						);
						auto cast = mk->castExpression(castType, expr);
						auto quote = mk->parenthesizedExpression(cast);
						ctx->insert(quote, 0);
						ctx->removeChild(expr);


						//如果import列表中，不存在该路径的话，就需要加入hiddenImports中
						space->addHiddenImport_byPath_ifNeed(
							memberDto->classDef->hostSpace->path);

					}
				}
			}
		}
		auto ret = visitChildren(ctx);
		return ret;
	}

	//函数定义，需要支持ref类型的参数
	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override {
		return visitChildren(ctx);
	}
	//变量声明，需要支持ref类型
	virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext* ctx) override {
		auto ret = visitChildren(ctx);
		return ret;
	}

	//对于 (row)*a 可以解释为类型转换(row)(*a), 也可以理解为 乘法。 结合语义进行消歧。判断row的类型
	virtual std::any visitCastExpression(OrcParser::CastExpressionContext* ctx) override {
		auto id = ctx->type()->Id();
		//TODO 有bug (id) 的情况
		if (0 && id && ctx->type()->children.size() == 1) {
			auto typeName = id->getText();
			auto varInfo = ast_findVarInfoByVarName(ctx, typeName, space);
			if (varInfo.isFound && (varInfo.argumentDeclaration || varInfo.varDeclaration || varInfo.scopeStatement)) { //说明是变量。 不是类型。 需要转写为
				auto varExpr = mk->expressionSequence();
				auto idExpr = mk->identifierExpression(typeName);
				varExpr->addChild(idExpr);

				auto expr = ctx->singleExpression();
				// 如果expr是解引用 *expr
				{
					auto deref = dynamic_cast<OrcParser::DerefExpressionContext*>(expr);
					if (deref) {

						auto ins = mk->tracker->createInstance<OrcParser::MultiplicativeExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
						ins->insert(varExpr);
						ins->insert(mk->mkTerminal(OrcParser::T__0, "*"));
						ins->insert(deref->singleExpression());
						ast_replaceChild(ctx, ins); //替换cast expression 为 expr+expr
					}
				}
				// 如果expr是+expr
				{
					auto unary = dynamic_cast<OrcParser::UnaryPlusExpressionContext*>(expr);
					if (unary) {

						auto ins = mk->tracker->createInstance<OrcParser::AdditiveExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
						ins->insert(varExpr);
						ins->insert(mk->mkTerminal(OrcParser::T__0, "+"));
						ins->insert(unary->singleExpression());
						ast_replaceChild(ctx, ins); //替换cast expression 为 expr+expr
					}
				}
				// 如果expr是-expr
				{
					auto unary = dynamic_cast<OrcParser::UnaryPlusExpressionContext*>(expr);
					if (unary) {

						auto ins = mk->tracker->createInstance<OrcParser::AdditiveExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
						ins->insert(varExpr);
						ins->insert(mk->mkTerminal(OrcParser::T__0, "-"));
						ins->insert(unary->singleExpression());
						ast_replaceChild(ctx, ins); //替换cast expression 为 expr+expr
					}
				}

			}
		}

		auto ret = visitChildren(ctx);
		return ret;
	}
	//返回语句改写，需要支持ref类型
	virtual std::any visitReturnStatement(OrcParser::ReturnStatementContext* ctx) override {
		auto ret = visitChildren(ctx);
		auto fn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(ctx);
		if (fn) { //返回值类型是引用
			auto ref = fn->type()->ref();
			if (ref) {
				//转为
				//return urgc_set_var_for_return((void**)__outRef__, gApp);
				auto defClass = ast_findSymbolDefinitionClass_byTypeContext(fn->type(), space);

				auto expr = mk->singleExpression();
				ctx->insert(expr);

				auto call = mk->callExpression();
				expr->insert(call);
				auto fnName = mk->identifierExpression(
					defClass?"urgc_set_var_for_return_class" : "urgc_set_var_for_return");
				call->insert(fnName);

				auto arguments = mk->arguments();
				call->insert(arguments);

				auto outRef = mk->identifierExpression("__outRef__");
				auto castType= mk->type(
					mk->pointer(mk->primitiveType("void"), 2))
					;
				auto cast = mk->castExpression(
					castType, outRef
				);
				arguments->insert(cast);

				auto oriExpr = ctx->singleExpression();
				ctx->removeChild(oriExpr);
				arguments->insert(oriExpr);
			}
		}
		return ret;
	}

};





//import 生成头文件
class  GenImportHeadCodeVisitor : public OnlyRootsVisitor {
public:
	bool includeOnlyType = true;
	bool forceIncludeOnlyType = false;

	std::string includes;
	std::string imports;

	virtual std::any visitIncludeStatement(OrcParser::IncludeStatementContext* context) {
		std::string ret = string("#include ") + context->includePathCharacters()->getText() + "\n";
		includes += ret;
		return ret;
	}

	virtual std::any visitImportStatement(OrcParser::ImportStatementContext* context) {
		auto str = context->StringLiteral()->getText();
		auto path = str.substr(1, str.size() - 2 - 4); //去掉外面的'"', 再去掉.orc

		if (forceIncludeOnlyType) {
			auto ret = std::format(R"(#define INCLUDE_ONLY_TYPE
#include "{}_orc.h"
#undef INCLUDE_ONLY_TYPE
)", path);
			imports += ret;
			return ret;
		}

		if (includeOnlyType && ast_hasTerminal_inChildren(context, "import type")) { //只引入 类型声明
			auto ret = std::format(R"(#define INCLUDE_ONLY_TYPE
#include "{}_orc.h"
#undef INCLUDE_ONLY_TYPE
)", path);
			imports += ret;
			return ret;
		}
		auto ret = std::format("#include \"{}_orc.h\"\n", path);
		imports += ret;
		return ret;
	}
};

class  GenHeadCodeVisitor : public ReturnStringVisitor {
public:
	std::string path;
	std::shared_ptr<SymbolSpace> space = nullptr;
	std::string structHeadCode;
	//结构体所依赖的其他结构体。 需要提前include进来。  
	// 之所以结构体声明要前置，是因为结构体本身的依赖是无环的。但是函数里的参数或者返回值也是结构体的话，就可能导致循环依赖
	std::string includeDependentStructCode; //结构体对import的依赖

	AstMake* mk = NULL;
	virtual std::any visitProgram(OrcParser::ProgramContext* ctx) override {
		std::filesystem::path p(path);
		// __Appc
		auto includeOnce = string("__") + space->packageName + "__" + p.filename().stem().string() + "_orc_h__";

		//类型预声明
		TypePreDeclarationVisitor vi;
		vi.needMakeStaticStructCode = false;
		auto typePreDeclaration = vi.visitReturnString(ctx);


		//include
		GenImportHeadCodeVisitor importVi;
		auto importHeadCode = importVi.visitReturnString(ctx);

		//include plain
		GenImportHeadCodeVisitor importViPlain;
		importViPlain.forceIncludeOnlyType = true;
		auto importHeadCodePlain = importViPlain.visitReturnString(ctx);
		
		auto kidsRet = visitChildrenReturnString(ctx);
		auto ret = std::format(R"(
{}

#ifndef define_struct_{}
#define define_struct_{}


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE_{}
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

{}
{}


#ifdef INCLUDE_ONLY_TYPE_{}
#define INCLUDE_ONLY_TYPE
#endif

{}
#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef {}
#define {}

//include  importHeadCode
{}

#ifdef __cplusplus
extern "C"{{
#endif

//代码内容
{}


#ifdef __cplusplus
}}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
)", 
typePreDeclaration,

includeOnce, includeOnce, includeOnce,
importVi.includes,
includeDependentStructCode, includeOnce,
structHeadCode,

includeOnce, includeOnce, 
importVi.imports,
kidsRet);
		return ret;
	}

	virtual std::any visitArguments(OrcParser::ArgumentsContext* ctx) override {
		string ret;
		auto args = ctx->singleExpression();
		for (int i = 0, l = args.size(); i < l; i++) {
			auto code = visitReturnString(args[i]);
			ret += code;
			if (i < l - 1) {
				ret += ", ";
			}
		}
		return ret;
		//return visitChildrenReturnString(ctx);
	}



	//数组索引
	virtual std::any visitArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext* ctx) override {
		auto decimal = ctx->DecimalLiteral();
		return std::format("[{}]", decimal? decimal->getText() : "");
	}

	virtual std::any visitThisExpression(OrcParser::ThisExpressionContext* ctx) override {
		return ctx->getText();
	}


	virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext* ctx) override {
		return string("super");
	}



	virtual std::any visitLiteralExpression(OrcParser::LiteralExpressionContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}


	virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx) override {
		auto text = ctx->getText();
		return text;
	}


	// ?? 表达式，暂不支持
	virtual std::any visitCoalesceExpression(OrcParser::CoalesceExpressionContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitLabelClosureExpression(OrcParser::LabelClosureExpressionContext* ctx) override {
		return string("");
	}

	virtual std::any visitAssignmentOperator(OrcParser::AssignmentOperatorContext* ctx) override {
		return ctx->getText();
	}

	virtual std::any visitEmptyStatement(OrcParser::EmptyStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext* ctx) override {
		if (ctx->isStaticStruct) {
			return string("");
		}

		auto structName = ctx->fullname;
		auto members = visitChildrenReturnString(ctx);
		members = StrUtil::addPrefixPerLine(members, "\t");

		std::string metaFn = "";
		if (ctx->needCreateMeta) { //需要生成元数据
			metaFn = std::format(R"(
//结构体元数据获取即初始化
MetaStruct* {}_getOrInitMetaStruct();
)", structName);
		}

		//结构体所依赖的其他结构体。 需要提前include进来。  
		// 之所以结构体声明要前置，是因为结构体本身的依赖是无环的。但是函数里的参数或者返回值也是结构体的话，就可能导致循环依赖
		auto structSymDef = std::dynamic_pointer_cast<SymbolDefinitionStruct>(  this->space->findSymbolDefinitionByName_exportedInThisSpace(ctx->Id()->getText()));
		//遍历成员，查找成员类型所在的空间
		if (structSymDef) {
			std::unordered_map<std::string, bool> doneMap;
			std::vector<std::string> symTypeWithTypeNames;

			//收集类型
			for (auto pMember : structSymDef->members) {
				auto pVar = std::dynamic_pointer_cast<SymbolDefinitionVar>(pMember);
				if (pVar) { //成员
					auto symTypeFunction = std::dynamic_pointer_cast<SymbolTypeFunction>(pVar->getType());
					if (symTypeFunction) {
						auto typeName = symTypeFunction->returnType->getNakeTypeName();
						symTypeWithTypeNames.push_back(typeName);
						for (auto arg : symTypeFunction->args) {
							typeName = arg->type->getNakeTypeName();
							symTypeWithTypeNames.push_back(typeName);
						}
						continue;
					}

					auto symTypeClosure = std::dynamic_pointer_cast<SymbolTypeClosure>(pVar->getType());
					if (symTypeClosure) {
						auto typeName = symTypeClosure->returnType->getNakeTypeName();
						symTypeWithTypeNames.push_back(typeName);
						for (auto arg : symTypeClosure->args) {
							typeName = arg->type->getNakeTypeName();
							symTypeWithTypeNames.push_back(typeName);
						}
						continue;
					}

					//普通的类型
					auto symTypeWithTypeName = std::dynamic_pointer_cast<SymbolTypeWithTypeName>(pVar->getType());
					if (symTypeWithTypeName) {
						symTypeWithTypeNames.push_back(symTypeWithTypeName->getNakeTypeName());
					}
				}
			}

			for (auto typeName : symTypeWithTypeNames) {
				if(doneMap.contains(typeName)) { //已处理
					continue;
				}
				if (typeName == "Object") { //内置的类
					continue;
				}

				auto memberTypeSymDef = space->findSymbolDefinitionByName_includeImports(typeName);
				if (memberTypeSymDef) {
					//同一个space中
					if (memberTypeSymDef->hostSpace == this->space) {
						continue;
					}
					//不是.orc
					if (!memberTypeSymDef->hostSpace->path.ends_with(".orc")) {
						continue;
					}
					auto imp = this->space->findImportByAbspath(memberTypeSymDef->hostSpace->gocAbspath());
					if (!imp) {
						imp = this->space->findImportByAbspath(memberTypeSymDef->hostSpace->gocAbspath());
						throw std::format("{}查找依赖的Import失败.{}", 
							this->space->gocAbspath(), memberTypeSymDef->hostSpace->gocAbspath());
					}
					auto str = imp->path;
					auto path = str.substr(0, str.size() - 4); //去掉外面的'"', 再去掉.orc
					//生成依赖code
					auto code = std::format(R"(#define INCLUDE_ONLY_TYPE
#include "{}_orc.h"
#undef INCLUDE_ONLY_TYPE
)", path);
					includeDependentStructCode += code;

					doneMap[typeName] = true;
				}
			}

		}

		structHeadCode += std::format(R"(
struct tag{} {{
{}
}};

)", structName,  members);

//#ifndef DEFINED_STRUCT_{}
//#define DEFINED_STRUCT_{}
//		struct tag {} {{
//			{}
//			}};
//#endif
		return std::format(R"(
{}
)", 
//structName, structName, structName, members, 
metaFn);
	}

	virtual std::any visitStructMember(OrcParser::StructMemberContext* ctx) override {
		//普通字段
		if (ctx->type()) {
			//闭包
			auto typeCtx = ctx->type();
			//闭包
			if (typeCtx) {
				auto closureType = typeCtx->closureType();

				if (closureType) {
					//auto returnTypeCode = visitReturnString(closureType->type());
					auto nameCode = ctx->Id()->getText();
					//auto argsCode = visitReturnString(closureType->argumentsDeclaration());
					auto closureTypeCode = ast_closureType_genCode(closureType, this, nameCode, mk);

					auto code = std::format("{};\n"
						, closureTypeCode
					);
					return code;
				}
			}


			auto typeCode = visitReturnString(ctx->type());
			std::string arraySizeCode = "";
			if (ctx->arraySizeDeclaration()){
				arraySizeCode = visitReturnString(ctx->arraySizeDeclaration());
			}
			return typeCode + " " + ctx->Id()->getText() + arraySizeCode + " ;\n";
		}
		//函数指针
		if (ctx->functionPointerVarDeclaration()) {
			auto ret = visitReturnString(ctx->functionPointerVarDeclaration()) + ";\n";
			return ret;
		}
		return std::format(" // invalid member :{}\n", ctx->Id()->getText());
	}

	virtual std::any visitStatement(OrcParser::StatementContext* ctx) override {
		auto ret = visitChildrenReturnString(ctx);
		return ret;
	}


	virtual std::any visitBlock(OrcParser::BlockContext* ctx) override {
		auto content = visitChildrenReturnString(ctx);
		return "{\n" + content + "\n}\n";
	}

	virtual std::any visitType(OrcParser::TypeContext* ctx) override {

		auto id = ctx->Id();
		if (id) {
			auto typeName = id->getText();
			auto def = space->findSymbolDefinitionByName_includeImports(typeName);
			if (!def) {
				throw std::format("GenHeadCode.  visitType. findSymbolDefiniteByName failed. typeName={}", typeName);
			}
			typeName = def->fullname;
			return typeName;
		}
		return visitChildrenReturnString(ctx) + " ";
		//return ctx->getText() + " ";
	}

	virtual std::any visitTypeQualifier(OrcParser::TypeQualifierContext* ctx) override {
		return ctx->getText() + " ";
	}

	virtual std::any visitPointer(OrcParser::PointerContext* ctx) override {
		auto ret = ast_buildCode_forPointer(ctx, space.get());
		return ret;
	}

	virtual std::any visitRef(OrcParser::RefContext* ctx) override {
		auto ret = ast_buildCode_forRef(ctx, space.get());
		return ret;
	}

	virtual std::any visitPrimitiveType(OrcParser::PrimitiveTypeContext* ctx) override {
		return ast_primitiveTypeToText(ctx);
	}

	virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext* ctx) override {

		auto text = string("");
		for (auto kid : ctx->children) {
			if (dynamic_cast<OrcParser::EosContext*>(kid)) {
				continue;
			}
			auto cur = visitReturnString(kid);
			text += cur;
		}
		return std::format(R"(enum enum{} {{
{}
}};
)", ctx->fullname, text);
	}

	virtual std::any visitEnumItem(OrcParser::EnumItemContext* ctx) override {
		if (ctx->DecimalLiteral()) {
			return std::format("\t{} = {}, \n", ctx->fullname, ctx->DecimalLiteral()->getText());
		}
		return std::format("\t{}, \n", ctx->fullname);
	}

	OrcParser::ExtensionDefinitionContext* curExtension = NULL;
	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) override {
		curExtension = ctx;
		auto ret = visitChildrenReturnString(ctx);
		curExtension = NULL;
		return ret;
	}

	virtual std::any visitExtensionBlock(OrcParser::ExtensionBlockContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}
	std::shared_ptr<SymbolDefinitionClass> superClassDefinition = nullptr;
	std::shared_ptr<SymbolDefinitionClass> classDefinition = nullptr;
	std::string classMethodDeclarationCode = "";

	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override {
		auto className = ctx->Id(0)->getText();
		auto classDef = space->findSymbolDefinitionByName_exportedInThisSpace(className);
		classDefinition = std::dynamic_pointer_cast<SymbolDefinitionClass>(classDef);
			
		std::string refcFlag = classDefinition->refc ? "refc:1" : "refc:0";

		superClassDefinition = space->findSuperClassSymbolDefinitionByAstClassDefinition(ctx);
		auto superFullname = superClassDefinition ? superClassDefinition->fullname : "Object";

		classMethodDeclarationCode = "";
		auto block = visitReturnString(ctx->classDefinitionBlock());

		superClassDefinition = nullptr;
		classDefinition = nullptr;


		//虚表
		string vtable = std::format(R"(
// 虚表
struct tagVtable_{} {{
	Vtable_{} super;
}};
//虚表实例
extern Vtable_{} _vtable_{};
)", ctx->fullname, superFullname, ctx->fullname, ctx->fullname);

		//类的结构定义
		string tag = std::format(R"(
// class {}
struct tag{} {{
	{} super; 
{}
}};
Vtable_{}* Vtable_{}_init(Vtable_{}* pvt);
void {}_init_fields({} *self);
void {}_init({} *self, void *pOwner);
{} * {}_new(void *pOwner);
void {}_fini({} *self);

{}
)"
, refcFlag
, ctx->fullname
, superFullname
, block
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, ctx->fullname
, classMethodDeclarationCode);
		//类的函数定义
		classMethodDeclarationCode = "";

		return vtable + tag;
		//return visitChildrenReturnString(ctx);
	}

	virtual std::any visitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext* ctx) override {
		std::string ret;
		for (auto kid : ctx->children) {
			auto field = dynamic_cast<OrcParser::ClassFieldDeclarationContext*>(kid);
			if (field) {
				auto code = visitReturnString(field);
				ret += code;
				continue;
			}
			auto method = dynamic_cast<OrcParser::MethodDeclarationContext*>(kid);
			if (method) {
				auto code = visitReturnString(method);
				ret += code;
				continue;
			}
		}
		//auto ret = visitChildrenReturnString(ctx);
		ret = StrUtil::addPrefixPerLine(ret, "\t");
		return ret;
	}

	virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* ctx) override {
		

		auto typeCtx = ctx->type();
		//闭包
		if (typeCtx) {
			auto closureType = typeCtx->closureType();

			if (closureType) {
				//auto returnTypeCode = visitReturnString(closureType->type());
				auto nameCode = ctx->Id()->getText();
				//auto argsCode = visitReturnString(closureType->argumentsDeclaration());
				auto closureTypeCode = ast_closureType_genCode(closureType, this, nameCode, mk);

				auto code = std::format("{};\n"
					, closureTypeCode
				);
				return code;
			}
		}
		

		//普通字段
		if (typeCtx) {
			auto typeCode = visitReturnString(typeCtx);
			auto arrayCode = std::string("");
			if (ctx->arraySizeDeclaration()) {
				arrayCode = visitReturnString(ctx->arraySizeDeclaration());
			}
			return typeCode + " " + ctx->Id()->getText() + arrayCode +" ;\n";
		}
		////函数指针
		//if (ctx->functionPointerMember()) {
		//	auto ret = visitReturnString(ctx->functionPointerMember()) + ";\n";
		//	return ret;
		//}

		////函数指针
		auto fn = ctx->functionPointerVarDeclaration();
		if (fn) {
			auto returnTypeCode = visitReturnString(fn->type());
			auto nameCode = fn -> Id() ? fn->Id()->getText():"";
			auto argsCode = visitReturnString(fn->argumentsDeclaration());
			auto starText = ast_pointerStarText(fn);
			auto code = std::format("{} ({}{}){};\n"
				, returnTypeCode
				, starText
				, nameCode
				, argsCode
			);
			return code;
		}
		return std::format(" // invalid member :{}\n", ctx->Id()?ctx->Id()->getText():"(unknown name)");
		//return visitChildrenReturnString(ctx);
	}

	virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx) override {


		if (classDefinition != nullptr) { //需要增加此判断。因为extension里也是method

			auto declCode = visitChildrenReturnString(ctx);
			classMethodDeclarationCode += declCode;

			//todo 考虑是不是父类已经存在
			auto fn = ctx->functionDefinition();
			if (fn) {
				auto name = fn->Id()->getText();


				auto member = classDefinition->findOriginalDefinedMemberByName_includeSupers(name);
				if (member != nullptr && member->classDef != classDefinition) { //说明是重载
					return std::string("");
				}

				auto returnType = visitReturnString(fn->type());



				auto args = visitReturnString(fn->argumentsDeclaration());
				return std::format("{} (*{}) {};\n", returnType, name, args);
			}
			auto exFn = ctx->externFunctionDeclaration();
			if (exFn) {
				auto name = exFn->Id()->getText();

				auto member = classDefinition->findOriginalDefinedMemberByName_includeSupers(name);
				if (member != nullptr && member->classDef != classDefinition) { //说明是重载
					return std::string("");
				}

				auto returnType = visitReturnString(exFn->type());
				auto args = visitReturnString(exFn->argumentsDeclaration());
				return std::format("{} (*{}) {};\n", returnType, name, args);
			}
		}
		auto declCode = visitChildrenReturnString(ctx);
		return declCode;
	}


	virtual std::any visitArgumentDeclaration(OrcParser::ArgumentDeclarationContext* ctx) override {

		auto type = ctx->type();
		if (type) {
			auto argName = ctx->Id()->getText();
			{ //闭包类型
				auto closureType = type->closureType();
				if (closureType) {
					auto returnCode = visitReturnString(closureType->type());
					auto args = visitReturnString(closureType->argumentsDeclaration());
					return std::format("{} (**{}){}", returnCode, argName, args);
				}
			}


			auto text = type->getText();
			auto s0 = visitReturnString(ctx->type());
			return std::format("{} {}", s0, argName);
		}
		

		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext* ctx) override {
		std::string s = "(";
		auto args = ctx->argumentDeclaration();
		for (int i = 0, l = args.size(); i < l; i++) {
			s += visitReturnString(args[i]);
			if (i < l - 1) {
				s += ", ";
			}
		}
		return s + ")";
	}

	virtual std::any visitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext* ctx) override {

		auto type = visitReturnString(ctx->type());
		auto id = ctx->Id() ? ctx->Id()->getText():"";
		auto args = visitReturnString(ctx->argumentsDeclaration());
		std::string ptrs = "";
		for (int i = 1; i < ctx->children.size(); i++) {
			auto kid = ctx->children[i];
			auto term = dynamic_cast<antlr4::tree::TerminalNode*>(kid);
			if (term && term->getText() == "*") {
				ptrs += "*";
			}
		}
		

		return std::format("{} ({}{}){}", type, ptrs, id, args);
	}

	//生成函数声明
	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override {
		auto typeCtx = ctx->type();
		auto typeCode = typeCtx->getText();
		auto type = visitReturnString(ctx->type());
		auto args = visitReturnString(ctx->argumentsDeclaration());
		auto name = ctx->fullname.empty() ? ctx->Id()->getText() : ctx->fullname;
		return type + " " + name + args + ";\n";
	}

	//生成函数声明
	virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* ctx) override {
		if (ctx->Static()) {
			return string(""); // 静态函数，不体现在头文件中
		}

		if (ctx->functionDefinition()) {
			return visitReturnString(ctx->functionDefinition());
		}
		return visitReturnString(ctx->externFunctionDeclaration());
	}

	virtual std::any visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* ctx) override {
		//静态成员不需要在头文件中显示;
		auto varDecl = ctx->varDeclaration();
		auto staticNode = varDecl->Static();
		auto text = varDecl->getText();
		if (staticNode) {
			return string(""); 
		}
		auto type = varDecl->type();
		if (type->getText() == "longlong") {
			printf("longlong\n");
		}
		if (type) {
			auto typeStr = visitReturnString(type);
			return std::format("extern {} {};\n", typeStr, varDecl->fullname);
		}

		return string("");
		//return visitChildrenReturnString(ctx);
	}

	virtual std::any visitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext* ctx) override {
		auto type = visitReturnString(ctx->type());
		auto args = visitReturnString(ctx->argumentsDeclaration());
		auto name = ctx->fullname.empty() ? ctx->Id()->getText() : ctx->fullname;
		return std::string("extern ") + type + " " + name + args + ";\n";
	}

	virtual std::any visitImportStatement(OrcParser::ImportStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitIncludeStatement(OrcParser::IncludeStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitIncludePathCharacters(OrcParser::IncludePathCharactersContext* ctx) override {
		return string("");
	}

	virtual std::any visitPackageStatement(OrcParser::PackageStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitLiteral(OrcParser::LiteralContext* ctx) override {
		return ctx->getText();
	}

	virtual std::any visitEos(OrcParser::EosContext* ctx) override {
		//return string(";//eos\n");
		return string(";//eos\n");
	}

};


//实现文件生成
class  GenCodeVisitor : public ReturnStringVisitor {
public:
	AstMake* mk = NULL;
	std::string  path;
	std::string staticFunctionDeclaratonsCode = ""; //静态函数预声明
	std::string staticStructPredeclarationCode = ""; //静态结构体的类型预声明
	std::string staticStructCode = ""; //静态结构体的代码;
	std::shared_ptr<SymbolSpace> space = nullptr;


	//virtual std::any visitClosureType(OrcParser::ClosureTypeContext* ctx) override {
	//	auto type = visitReturnString(ctx->type());
	//	std::format();
	//	return visitChildren(ctx);
	//}

	virtual std::any visitProgram(OrcParser::ProgramContext* ctx) override {
		std::filesystem::path p(path);
		// __App_orc_h__
		auto fname = p.filename().stem().string();

		//include
		GenImportHeadCodeVisitor importVi;
		importVi.includeOnlyType = false;
		auto importHeadCode = importVi.visitReturnString(ctx);

		auto kidsRet = visitChildrenReturnString(ctx);

		startUs();
		auto ret = std::format(R"(
#include "{}_orc.h" 

{}

// static struct 
{}
{}
// static function declaration
{}

{}

)"
, fname
, importHeadCode
, staticStructPredeclarationCode
, staticStructCode
, staticFunctionDeclaratonsCode
, kidsRet
);
		endUs();
		return ret;
	}

	virtual std::any visitArguments(OrcParser::ArgumentsContext* ctx) override {
		string ret = "(";
		auto args = ctx->singleExpression();
		//printf("Args:\n\n");
		//ast_printTree(ctx, NULL);
		for (int i = 0, l = args.size(); i < l; i++) {
			auto code = visitReturnString(args[i]);

			startUs();
			ret += code;
			if (i < l - 1) {
				ret += ", ";
			}
			endUs();
		}

		startUs();
		auto result = ret + ") ";
		endUs();
		return result;
		//return visitChildrenReturnString(ctx);
	}

	virtual std::any visitExpressionSequence(OrcParser::ExpressionSequenceContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitClosureExpression(OrcParser::ClosureExpressionContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitTernaryExpression(OrcParser::TernaryExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));
		auto s2 = visitReturnString(ctx->singleExpression(2));

		CostUsGuard g(this);
		auto ret = std::format("{} ? {} : {}", s0, s1, s2);
		return ret;
	}

	virtual std::any visitLogicalAndExpression(OrcParser::LogicalAndExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));

		CostUsGuard g(this);
		return std::format("{} && {}", s0, s1);
	}

	virtual std::any visitMemberDotExpression(OrcParser::MemberDotExpressionContext* ctx) override {

		auto propName = ctx->Id()->getText();
		auto s0 = visitReturnString(ctx->singleExpression());
		auto typeInfo = ast_calcSymbolTypeOfExpressionResult(ctx->singleExpression(), space);
		string dot = ".";
		if (std::dynamic_pointer_cast<SymbolTypeRef>(typeInfo->type)
			||
			std::dynamic_pointer_cast<SymbolTypePointer>(typeInfo->type)
			) {
			dot = "->";

		}
		CostUsGuard g(this);
		return std::format("{}{}{}", s0, dot, propName);
	}

	virtual std::any visitMemberIndexExpression(OrcParser::MemberIndexExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));

		CostUsGuard g(this);
		return std::format("{}[{}]", s0, s1);
	}
	virtual std::any visitPreIncrementExpression(OrcParser::PreIncrementExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("++{}", s0);
	}

	virtual std::any visitLogicalOrExpression(OrcParser::LogicalOrExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));

		CostUsGuard g(this);
		return std::format("{} || {}", s0, s1);
	}

	virtual std::any visitNotExpression(OrcParser::NotExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("!{}", s0);
	}

	virtual std::any visitPreDecreaseExpression(OrcParser::PreDecreaseExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("--{}", s0);
	}

	virtual std::any visitThisExpression(OrcParser::ThisExpressionContext* ctx) override {
		return ctx->getText();
	}

	virtual std::any visitUnaryMinusExpression(OrcParser::UnaryMinusExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("-{}", s0);
	}

	virtual std::any visitAssignmentExpression(OrcParser::AssignmentExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));

		CostUsGuard g(this);
		return std::format("{} = {}", s0, s1);
	}

	virtual std::any visitPostDecreaseExpression(OrcParser::PostDecreaseExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("{}--", s0);
	}

	virtual std::any visitInstanceofExpression(OrcParser::InstanceofExpressionContext* ctx) override {
		auto obj = visitReturnString(ctx->singleExpression(0));
		auto expr = ctx->singleExpression(1);
		std::string clazz = "";

		{//id 
			auto id = dynamic_cast<OrcParser::IdentifierExpressionContext*>(expr);
			if (id) {
				auto var = ast_findVarInfoByVarName(ctx, id->getText(), space);
				if (var.isFound) {
					if (var.symbolDefinition) {
						auto defClass = std::dynamic_pointer_cast<SymbolDefinitionClass>(var.symbolDefinition);
						if (defClass) { // 如果instanceof 类名
							clazz = std::format("Vtable_{}_init(NULL)", defClass->fullname);
						}
					}
				}
			}
		}
		//其他情况，直接当变量处理
		if (clazz.empty()) {
			clazz = visitReturnString(expr);

		}

		CostUsGuard g(this);
		return std::format("Orc_instanceof((Object*){}, (Vtable_Object*){})", obj, clazz);
	}

	virtual std::any visitUnaryPlusExpression(OrcParser::UnaryPlusExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("+{}", s0);
	}

	virtual std::any visitEqualityExpression(OrcParser::EqualityExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));
		auto op = ctx->children[1]->getText();

		CostUsGuard g(this);
		return std::format("{} {} {}", s0, op, s1);
	}

	virtual std::any visitBitXOrExpression(OrcParser::BitXOrExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));

		CostUsGuard g(this);
		return std::format("{} ^ {}", s0, s1);
	}

	virtual std::any visitSuperExpression(OrcParser::SuperExpressionContext* ctx) override {
		return string("super");
	}

	virtual std::any visitMultiplicativeExpression(OrcParser::MultiplicativeExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));
		auto op = ctx->children[1]->getText();

		CostUsGuard g(this);
		return std::format("{} {} {}", s0, op, s1);
	}


	/*
	- 调用父类方法 super.fn() = > super_fn_fullname(self)    ~~转为全局函数
	- 调用扩展方法 a.b() = > fullname_b(a)        ~~转为全局函数
	*/
	virtual std::any visitCallExpression(OrcParser::CallExpressionContext* ctx) override {
		auto expr = ctx->singleExpression();
		//auto args = ctx->arguments();

		{
			//*-调用父类方法 super.fn() = > super_fn_fullname(self)
			//只需要转换super.fn => super_fn_fullname,  不用考虑self, self参数在TranslateVisitor处理了
			auto dotExpr = dynamic_cast<OrcParser::MemberDotExpressionContext*>(expr);
			if (dotExpr) {
				auto objExpr = dotExpr->singleExpression();
				auto propName = dotExpr->Id()->getText();
				
				auto superExpr = dynamic_cast<OrcParser::SuperExpressionContext*>(objExpr);

				//如果是super.xx
				if (superExpr) {
					auto selfVarInfo = ast_findVarInfoByVarName(ctx, "self", space);
					if (selfVarInfo.isFound && selfVarInfo.argumentDeclaration) {
						auto selfType = selfVarInfo.argumentDeclaration->type();
						auto pointer = selfType->pointer();
						if (pointer) {
							auto typeName = pointer->Id()->getText();
							auto symbolDef = space->findSymbolDefinitionByName_includeImports(typeName);
							auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(symbolDef);
							if (classDef) { //找到了self的类
								//找到了父类
								auto superClassDef = classDef->findSuperSymbolDefinition();

								auto memberDto = superClassDef->findMemberByName_includeSupers(propName);
								auto args = visitReturnString(ctx->arguments());
								return memberDto->member->fullname + args;
							}
						}

					}
				}
			

				auto memberInfo = MemberInfo::findMemberInfo(objExpr, propName, space);

				if (memberInfo.extensionDef && memberInfo.methodDef) {
					//- 调用扩展方法 a.b() = > fullname_b(a)        ~~转为全局函数
					//只需要转换a.b => fullname_b(a)
					//printf("打印GenCode 扩展函数调用\n");
					//ast_printTree(ctx, NULL);
					auto fn = memberInfo.methodDef->fullname;
					auto args = visitReturnString(ctx->arguments());
					return fn + args;
				}
			}
		}


		auto fn = visitReturnString(ctx->singleExpression());
		auto args = visitReturnString(ctx->arguments());

		CostUsGuard g(this);
		return fn + args;
	}

	virtual std::any visitBitShiftExpression(OrcParser::BitShiftExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));
		auto op = ctx->children[1]->getText();

		CostUsGuard g(this);
		return std::format("{} {} {}", s0, op, s1); // >> << >>>
	}

	//不支持逗号语句
	virtual std::any visitParenthesizedExpression(OrcParser::ParenthesizedExpressionContext* ctx) override {
		auto kids = ctx->expressionSequence()->singleExpression();
		std::string ret;
		int i = 0;
		for (auto& kid : kids) {
			auto s0 = visitReturnString(kid);
			ret += s0;
			if (i < kids.size() - 1) {
				ret += ",";
			}
			i++;
		}

		CostUsGuard g(this);
		return std::format("({})", ret); // >> << >>>
	}

	//数组索引
	virtual std::any visitArraySizeDeclaration(OrcParser::ArraySizeDeclarationContext* ctx) override {
		auto decimal = ctx->DecimalLiteral();
		CostUsGuard g(this);
		return std::format("[{}]", decimal ? decimal->getText() : "");
	}

	virtual std::any visitAdditiveExpression(OrcParser::AdditiveExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));
		auto op = ctx->children[1]->getText();

		CostUsGuard g(this);
		return std::format("{} {} {}", s0, op, s1); // + -
	}

	virtual std::any visitRelationalExpression(OrcParser::RelationalExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));
		auto op = ctx->children[1]->getText();

		CostUsGuard g(this);
		return std::format("{} {} {}", s0, op, s1); // < > >= <= 
	}

	virtual std::any visitPostIncrementExpression(OrcParser::PostIncrementExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("{}++", s0);
	}

	virtual std::any visitBitNotExpression(OrcParser::BitNotExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("~{}", s0);
	}

	virtual std::any visitNewExpression(OrcParser::NewExpressionContext* ctx) override {
		auto className = ctx->Id()->getText();
		auto def = space->findSymbolDefinitionByName_includeImports(className);

		auto argsCode = visitReturnString(ctx->arguments());
		CostUsGuard g(this);
		return std::format("{}_new{}", def->fullname, argsCode);
	}

	virtual std::any visitLiteralExpression(OrcParser::LiteralExpressionContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitDerefExpression(OrcParser::DerefExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("*{}", s0);
	}

	virtual std::any visitGetAddressExpression(OrcParser::GetAddressExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("&{}", s0);
	}

	virtual std::any visitIdentifierExpression(OrcParser::IdentifierExpressionContext* ctx) override {
		auto varName =  ctx->getText();


		if (varName == "nan") {
			return std::string("NAN");
		}
		if (varName == "infinity") {
			return std::string("INFINITY");
		}

		auto varInfo = ast_findVarInfoByVarName(ctx, varName, space);
		if (varInfo.isFound && varInfo.symbolDefinition) {

			//对于类的访问， 返回  虚表。
			//不用考虑结构体?
			auto defClass = std::dynamic_pointer_cast<SymbolDefinitionClass>(varInfo.symbolDefinition);
			if (defClass
				&& !ctx->prevent_classNameIdExpr_translate
				) { // 如果instanceof 类名
				CostUsGuard g(this);
				auto ret = std::format("Vtable_{}_init(NULL)", defClass->fullname);
				return ret;
			}
			//{//结果是结构体
			//	auto defStruct= std::dynamic_pointer_cast<SymbolDefinitionStruct>(varInfo.symbolDefinition);
			//	if (defStruct
			//		&& !ctx->prevent_classNameIdExpr_translate
			//		) { // 如果instanceof 类名
			//		CostUsGuard g(this);
			//		auto ret = std::format("{}_getOrInitMetaStruct()", defStruct->fullname);
			//		return ret;
			//	}
			//}
			return varInfo.symbolDefinition->fullname;
		}
		return varName;
	}

	virtual std::any visitBitAndExpression(OrcParser::BitAndExpressionContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression(0));
		auto s1 = visitReturnString(ctx->singleExpression(1));

		CostUsGuard g(this);
		return std::format("{} & {}", s0, s1); // 
	}

	virtual std::any visitBitOrExpression(OrcParser::BitOrExpressionContext* ctx) override {
		auto left = visitReturnString(ctx->singleExpression(0));
		auto right = visitReturnString(ctx->singleExpression(1));


		CostUsGuard g(this);
		return left + " | " + right;
	}

	virtual std::any visitAssignmentOperatorExpression(OrcParser::AssignmentOperatorExpressionContext* ctx) override {
		auto left = visitReturnString(ctx->singleExpression(0));
		auto right = visitReturnString(ctx->singleExpression(1));

		CostUsGuard g(this);
		return left + " " + ctx->assignmentOperator()->getText() + " " + right;
	}

	virtual std::any visitCastExpression(OrcParser::CastExpressionContext* ctx) override {
		auto typeCtx = ctx->type();
		auto closureType = typeCtx->closureType();
		std::string type;
		if (closureType) {
			type = ast_closureType_genCode(closureType, this, "", mk);
		}
		else {
			type = visitReturnString(ctx->type());
		}
		auto expr = visitReturnString(ctx->singleExpression());

		CostUsGuard g(this);
		return std::format("({}){}", type, expr);
		//return visitChildrenReturnString(ctx);
	}

	// ?? 表达式，暂不支持
	virtual std::any visitCoalesceExpression(OrcParser::CoalesceExpressionContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitLabelClosureExpression(OrcParser::LabelClosureExpressionContext* ctx) override {
		return string("");
	}

	virtual std::any visitAssignmentOperator(OrcParser::AssignmentOperatorContext* ctx) override {
		return ctx->getText();
	}

	virtual std::any visitEmptyStatement(OrcParser::EmptyStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext* ctx) override {
		if (ctx->isStaticStruct) { //静态结构体，只在.c实现文件中产生，不在头文件中产生
			ctx->isStaticStruct = false;

			{
				//类型预声明
				TypePreDeclarationVisitor vi;
				auto typePreDeclaration = vi.visitReturnString(ctx);
				this->staticStructPredeclarationCode += typePreDeclaration + "\n";
			}


			GenHeadCodeVisitor vi;
			vi.mk = this->mk;
			vi.space = space;
			vi.path = this->path;
			auto code = vi.visitReturnString(ctx);
			staticStructCode += vi.structHeadCode + code + "\n";
			ctx->isStaticStruct = true;
		}


		if (ctx->needCreateMeta) { //需要生成元数据
			std::string memberMetas = "";
			auto name = ctx->Id()->getText();
			auto symbolDefinitionStruct = std::dynamic_pointer_cast<SymbolDefinitionStruct>(
				space->findSymbolDefinitionByName_exportedInThisSpace(name));

			for (auto& mem : symbolDefinitionStruct->members) {
				//字段符号
				auto fieldSymbolType = mem->getType();
				memberMetas += buildCode_forMeta(fieldSymbolType, symbolDefinitionStruct->fullname, mem->name);
			}
			auto fullname = symbolDefinitionStruct->fullname;

			CostUsGuard g(this);
			memberMetas = StrUtil::addPrefixPerLine(memberMetas, "\t\t");


			auto code = std::format(R"(
// get or init meta 
MetaStruct* {}_getOrInitMetaStruct(){{
    static MetaStruct *meta = NULL;
    if (meta == NULL){{
        //init
        orc_initMetaStruct(&meta, "{}", sizeof( {} ));
        OrcMetaField **pNext = &meta->headMetaField;

{}
    }}
	return meta;
}}
)", fullname, fullname, fullname, memberMetas);
		
			return code;

		}
		return string("");
	}

	virtual std::any visitStructMember(OrcParser::StructMemberContext* ctx) override {
		return string("");
	}

	virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext* ctx) override {
		//函数指针的 变量声明
		auto staticCtx = ctx->Static();
		string staticStr = "";
		if (staticCtx) {
			staticStr = "static ";
		}

		auto typeCtx = ctx->type();
		//闭包
		if (typeCtx) {
			auto closureType = typeCtx->closureType();
			if (closureType) {
				//auto returnTypeCode = visitReturnString(closureType->type());
				auto nameCode = ctx->Id()->getText();
				//auto argsCode = visitReturnString(closureType->argumentsDeclaration());
				auto closureTypeCode = ast_closureType_genCode(closureType, this, nameCode, mk);
				
				startUs();
				auto code = std::format("{}{}{}"
					, staticStr
					, closureType->isTmpThisVarForClosure ? "":"URGC_VAR_CLEANUP "
					, closureTypeCode
					);
				endUs();
				auto init = ctx->singleExpression();
				std::string initCode = "NULL";
				if (init) {
					initCode = visitReturnString(init);
					if (initCode != "NULL") {
						startUs();
						initCode = std::format("urgc_init_var((void**)&{}, {})"
							, nameCode
							, initCode
						);
						endUs();
					}
				}
				if (!initCode.empty()) {
					startUs();
					code += " = " + initCode;
					endUs();
				}
				return code;
			}
		}

		auto fnVar = ctx->functionPointerVarDeclaration();
		if (fnVar) {
			// 函数指针的变量声明

			auto returnTypeCode = visitReturnString(fnVar->type());
			auto nameCode = fnVar->Id()->getText();
			auto argsCode = visitReturnString(fnVar->argumentsDeclaration());
			auto starText = ast_pointerStarText(fnVar);
			auto initCode = visitReturnString(ctx->singleExpression());
			CostUsGuard g(this);
			auto code = std::format("{}{} ({}{}){}"
				, staticStr
				, returnTypeCode
				, starText
				, nameCode
				, argsCode
			);
			if (!initCode.empty()) {
				code += " = " + initCode;
			}
			return code;
		}
		else { //普通的变量声明
			auto typeCtx = ctx->type();


			auto refCtx = typeCtx->ref(); //引用

			auto type = visitReturnString(typeCtx);
			auto init = ctx->singleExpression();

			auto varName = ctx->fullname.empty() ? ctx->Id()->getText() : ctx->fullname;
			
			//    URGC_VAR_CLEANUP SuiCore$TimerMgr* mgr = urgc_init_var((void**)&mgr, $init);
			if (refCtx) { //如果变量是引用，则生成
				auto classDef = ast_findSymbolDefinitionClass_byTypeContext(typeCtx, space);
				string initCode = "NULL";
				if (init) {
					//如果初值值是 xx@ call(...) 返回引用的函数调用，就可以不用生成tmpReturn
					//Usr@ tmpUser3 = createUser()
					//转译为
					//URGC_VAR_CLEANUP User* tmpUser3 = createUser((tmpUser3 = NULL, &tmpUser3));
					auto callExpr = dynamic_cast<OrcParser::CallExpressionContext*>(init);
					bool handled = false;
					if (callExpr) {
						auto initReturnTypeInfo = ast_calcSymbolTypeOfExpressionResult(init, space);
						//返回引用
						if (initReturnTypeInfo && dynamic_cast<SymbolTypeRef*>(initReturnTypeInfo->type.get())) {
							initCode = visitReturnString(init);
							handled = true;
						}
					}


					if (!handled) {
						auto tmpInitCode = visitReturnString(init);
						if (tmpInitCode != "NULL") {
							initCode = std::format("({}=NULL,{}((void**)&{}, {}))"
								, varName
								, classDef ? "urgc_init_var_class":"urgc_init_var"
								, varName
								, tmpInitCode
							);
						}
					}
				}

				auto decl = std::format("{}{} {} {} = {}"
					, staticStr
					, classDef ? "URGC_VAR_CLEANUP_CLASS" : "URGC_VAR_CLEANUP"
					, type
					, varName
					, initCode
				);
				return decl;
			}

			//如果是数组
			auto arraySizeCode = visitReturnString(ctx->arraySizeDeclaration());

			auto decl = staticStr + type + " " + varName + arraySizeCode;

			if (init) {
				decl += " = " + visitReturnString(init);
			}
			decl += "";
			return decl;
		}
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitStatement(OrcParser::StatementContext* ctx) override {
		auto ret = visitChildrenReturnString(ctx);
		CostUsGuard g(this);
		if (ctx->singleExpression() || ctx->varDeclaration()) {
			return ret + ";\n";
		}
		return ret;
	}

	virtual std::any visitContinueStatement(OrcParser::ContinueStatementContext* ctx) override {
		return string("continue;\n");
	}

	virtual std::any visitBreakStatement(OrcParser::BreakStatementContext* ctx) override {
		return string("break;\n");
	}

	virtual std::any visitReturnStatement(OrcParser::ReturnStatementContext* ctx) override {
		auto expr = visitReturnString(ctx->singleExpression());
		CostUsGuard g(this);
		return string("return ") + expr + "; \n";
	}

	std::string visitReturnString_inSpace(OrcRuleContext *ctx, std::shared_ptr<SymbolSpace> space) {
		auto prevSpace = this->space;
		this->space = space;
		auto ret = visitReturnString(ctx);
		this->space = prevSpace;
		return ret;
	}

	virtual std::any visitScopeStatement(OrcParser::ScopeStatementContext* ctx) override {
		auto block = ctx->block();
		auto expr = ctx->singleExpression();

		auto symbolTypeInfo = ast_calcSymbolTypeOfExpressionResult(expr, space);
		auto astType = mk->type(symbolTypeInfo->type->toAstType(mk));

		auto typeCode = visitReturnString_inSpace(astType, symbolTypeInfo->hostSpace);

		auto code = visitReturnString(block);
		auto exprCode = visitReturnString(expr);
		string exitCode = "";

		auto symDef = symbolTypeInfo->findSymbolDefinition();
		auto symDefClass = std::dynamic_pointer_cast<SymbolDefinitionClass>(symDef);
		//支持__exit__ 退出作用的回调
		if (symDefClass) {
			auto memberInfo = symDefClass->findMemberByName_includeSupers("__exit__");
			//auto classAstType = memberInfo->clas->getType()->toAstType(mk);
			//auto classTypeCode = visitReturnString(classAstType);
			if (memberInfo) {
				CostUsGuard g(this);
				auto scopeObjName = std::format("__scopeObj_{}_{}", ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine());
				exitCode = std::format("UNUSED DEFER(Orc_scopeExit) Orc$ScopeData {} = (({}*)o)->__exit__((void*)o);"
					, scopeObjName
					, memberInfo->classDef->fullname
				);
			}
		}
		{
			auto symDefStruct = std::dynamic_pointer_cast<SymbolDefinitionStruct>(symDef);

			//支持__exit__ 退出作用的回调
			if (symDefStruct) {
				auto memberSymDef = symDefStruct->findMemberByName("__exit__");
				//auto classAstType = memberInfo->clas->getType()->toAstType(mk);
				//auto classTypeCode = visitReturnString(classAstType);
				if (memberSymDef) {
					CostUsGuard g(this);
					int pointLevel = symbolTypeInfo->getPointLevel_ofType();

					auto scopeObjName = std::format("__scopeObj_{}_{}", ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine());
					if (pointLevel == 0) {
						exitCode = std::format("UNUSED DEFER(Orc_scopeExit) Orc$ScopeData {} = o.__exit__(&o);"
							, scopeObjName
						);
					}
					else {
						exitCode = std::format("UNUSED DEFER(Orc_scopeExit) Orc$ScopeData {} = o->__exit__(o);"
							, scopeObjName
						);
					}
				}
			}
		}
		auto starText = symbolTypeInfo->getPointStarText_ofType();

		auto usedVarOInExpr = ast_isVarNameUsedInExprSubtree(expr, std::string("o"));
		std::string scopeCode;
		CostUsGuard g(this);
		if (usedVarOInExpr) { //如果表达式里有用到o变量

			//生成临时变量接收. 为什么要生成临时变量，是因为如果表达式里也用到了o,那么就会导致o变量引用错误了
			auto scopeVarName = std::format("__scopeVar_{}_{}", ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine());

			scopeCode = std::format(R"(
	{} {} = {}, {}o = {};
	{}
)"
, typeCode
, scopeVarName
, exprCode
, starText
, scopeVarName
, exitCode
);
		}
		else {
			scopeCode = std::format(R"(
	{} o = {};
	{}
)"
, typeCode
, exprCode
, exitCode
);
		}

		return code.substr(0, 1) + scopeCode + code.substr(1);
	}

	virtual std::any visitIterationStatement(OrcParser::IterationStatementContext* ctx) override {
		if (ctx->While()) {
			auto exprText = visitReturnString(ctx->singleExpression());
			if (exprText.c_str()[0] != '(') {
				exprText = std::format("({})", exprText);
			}
			auto blockText = visitReturnString(ctx->block());
			CostUsGuard g(this);
			auto ret = std::format("while {} {}", exprText, blockText);
			return ret;
		}
		if (ctx->For()) {
			//auto hasParenthesis = ctx->children[1]->getText() == "(";
			auto forConditionText = visitReturnString(ctx->forCondition());
			auto blockText = visitReturnString(ctx->block());

			CostUsGuard g(this);
			auto ret = std::format("for ({}) {}", forConditionText, blockText);
			return ret;
			
		}
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitForCondition(OrcParser::ForConditionContext* ctx) override {
		string declText;
		string condText;
		string incText;

		int st = 0;
		for (int i = 0; i < ctx->children.size(); i++) {
			auto kid = ctx->children[i];

			if (kid->getText() == ";") {
				st++;
			}
			else {
				if (st == 0) {
					declText = visitReturnString(kid);
				}
				else if (st == 1) {
					condText = visitReturnString(kid);
				}
				else if (st == 2) {
					incText = visitReturnString(kid);
				}
			}
		}
		CostUsGuard g(this);
		auto ret = std::format("{}; {}; {}", declText, condText, incText);
		return ret;
	}

	virtual std::any visitSelectionStatement(OrcParser::SelectionStatementContext* ctx) override {
		auto exprs = ctx->singleExpression();
		auto blocks = ctx->block();
		int exprSize = exprs.size();
		string text;
		for (int i = 0, l = blocks.size(); i < l; i++) {
			auto block = blocks[i];
			auto blockText = visitReturnString(block);

			auto expr = i < exprSize ? exprs[i] : NULL;
			if (expr) { // 有条件表达式
				auto exprText = visitReturnString(expr);
				//没有自带了括号
				if (dynamic_cast<OrcParser::ParenthesizedExpressionContext*>(expr) == NULL) {
					exprText = std::format("({})", exprText);
				}

				CostUsGuard g(this);
				text += std::format("{} {} {}", i == 0 ? string("if") : string("else if"), exprText, blockText);
			}
			else {
				CostUsGuard g(this);
				text += std::format("else {}",  blockText);
			}

		}
		return text;
	}

	virtual std::any visitBlock(OrcParser::BlockContext* ctx) override {
		auto content = visitChildrenReturnString(ctx);
		auto indentContent = StrUtil::addPrefixPerLine(content, "\t");
		CostUsGuard g(this);
		return "{\n" + indentContent + "\n}\n";
	}

	virtual std::any visitType(OrcParser::TypeContext* ctx) override {
		//return visitChildrenReturnString(ctx);

		auto id = ctx->Id();
		if (id) {
			auto typeName =  id->getText();
			auto def = space->findSymbolDefinitionByName_includeImports(typeName);
			if (!def) {
				auto def = space->findSymbolDefinitionByName_includeImports(typeName);
				throw std::format("find symbol definitionByName in visitType fail. typeName:{}", typeName);
			}
			typeName = def->fullname;
			return typeName;
		}
		auto ret = visitChildrenReturnString(ctx);
		CostUsGuard g(this);
		return ret + " ";
	}

	virtual std::any visitTypeQualifier(OrcParser::TypeQualifierContext* ctx) override {
		return ctx->getText() + " ";
	}

	virtual std::any visitPointer(OrcParser::PointerContext* ctx) override {
		auto ret = ast_buildCode_forPointer(ctx, space.get());
		return ret;
	}

	virtual std::any visitRef(OrcParser::RefContext* ctx) override {
		auto ret = ast_buildCode_forRef(ctx, space.get());
		return ret;
	}

	virtual std::any visitPrimitiveType(OrcParser::PrimitiveTypeContext* ctx) override {
		return ast_primitiveTypeToText(ctx);
	}

	virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext* ctx) override {
		return string("");
	}

	virtual std::any visitEnumItem(OrcParser::EnumItemContext* ctx) override {
		if (ctx->DecimalLiteral()) {
			CostUsGuard g(this);
			return std::format("\t{} = {}, \n", ctx->fullname, ctx->DecimalLiteral()->getText());
		}
		CostUsGuard g(this);
		return std::format("\t{}, \n", ctx->fullname);
	}

	OrcParser::ExtensionDefinitionContext* curExtension = NULL;
	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) override {
		curExtension = ctx;
		auto ret = visitChildrenReturnString(ctx);
		curExtension = NULL;
		return ret;
	}

	virtual std::any visitExtensionBlock(OrcParser::ExtensionBlockContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}
	//取得字段所属的类的全名
	string ast_getMemberOwnedClassFullname_bySuperClassDefinition(
		std::shared_ptr<SymbolDefinitionClass> superClassDefinition,
		string classFullname, //第一类的全名
		string fieldName
	) {
		auto memberInfo_inSuper = superClassDefinition ? superClassDefinition->findOriginalDefinedMemberByName_includeSupers(fieldName) : nullptr;
		auto ownedClassFullname = classFullname;
		//确认字段实际归属的类名
		if (memberInfo_inSuper && memberInfo_inSuper->classDef) {
			ownedClassFullname = memberInfo_inSuper->classDef->fullname;
		}
		return ownedClassFullname;
	}
	std::string buildCode_forMeta(std::shared_ptr<SymbolType> fieldSymbolType, std::string fullname, std::string fieldName) {

		//字段类型为指针
		auto pointerType = std::dynamic_pointer_cast<SymbolTypePointer>(fieldSymbolType);
		//字段类型为引用
		auto refType = std::dynamic_pointer_cast<SymbolTypeRef>(fieldSymbolType);
		auto isPointer = pointerType != nullptr;
		auto isRef = refType != nullptr;
		int pointerLevel = isRef ? 1
			: isPointer ? pointerType->pointerLevel
			: 0;


		 //生成元数据
		//字段类型为基本类型
		auto primitiveType = std::dynamic_pointer_cast<SymbolTypePrimitiveType>(fieldSymbolType);
		if (primitiveType) {
			bool isUnsigned = primitiveType->isUnsigned();
			CostUsGuard g(this);
			auto ret = std::format(
				"orc_metaField_primitive(&pNext, \"{}\", {}, offsetof({}, {}), {}, {}, {}, {});//{}\n"
				, fieldName // value
				, primitiveType->getOrcMetaTypeName() // OrcMetaType_float
				, fullname // OrcView$Slider
				, fieldName // value
				, isUnsigned ? 1 : 0
				, isRef ? 1 : 0
				, isPointer ? 1 : 0
				, pointerLevel
				, primitiveType->getNakeTypeName() // float
			);
			return ret;
		}

		//基本类型指针 如 char *.
		if (isPointer && pointerType->is_nakeTypeName_isPrimitiveType()) {
			bool isUnsigned = false; //TODO 暂不考虑unsigned
			CostUsGuard g(this);
			auto ret = std::format(
				"orc_metaField_primitive(&pNext, \"{}\", {}, offsetof({}, {}), {}, {}, {}, {});//{}\n"
				, fieldName // value
				, ast_getOrcMetaTypeName_byNakeTypeName(pointerType->getNakeTypeName()) // OrcMetaType_float
				, fullname // OrcView$Slider
				, fieldName // value
				, isUnsigned ? 1 : 0
				, isRef ? 1 : 0
				, isPointer ? 1 : 0
				, pointerLevel
				, pointerType->getNakeTypeName() // float
			);
			return ret;
		}

		auto typeName = fieldSymbolType->getNakeTypeName();
		auto symbolDefinition_ofType = space->findSymbolDefinitionByName_includeImports(typeName);
		auto symbolDefinitionClass_ofType = std::dynamic_pointer_cast<SymbolDefinitionClass>(symbolDefinition_ofType);
		auto symbolDefinitionStruct_ofType = std::dynamic_pointer_cast<SymbolDefinitionStruct>(symbolDefinition_ofType);

		// 字段的类型是类
		if (symbolDefinitionClass_ofType != nullptr) {
			CostUsGuard g(this);
			auto ret = std::format(
				"orc_metaField_class(&pNext, \"{}\", ((Vtable_Object*)Vtable_{}_init(0)), offsetof({}, {}), {}, {}, {});\n"
				, fieldName // drag
				, symbolDefinitionClass_ofType->fullname
				, fullname // OrcView$Slider
				, fieldName // drag
				, isRef ? "true" : "false"
				, isPointer ? "true" : "false"
				, pointerLevel
			);
			return ret;
		}
		// 字段的类型是结构体
		else if (symbolDefinitionStruct_ofType != nullptr) {
			// 结构体如果是引用了c里的结构体，就没有meta的,只有orc里的结构体才会生成MetaStruct
			if (symbolDefinitionStruct_ofType->hostSpace->path.ends_with(".orc")) {
				CostUsGuard g(this);
				auto ret = std::format(
					"orc_metaField_struct(&pNext, \"{}\", {}_getOrInitMetaStruct(), offsetof({}, {}), {}, {}, {});\n"
					, fieldName // frame
					, symbolDefinitionStruct_ofType->fullname
					, fullname // OrcCore$View
					, fieldName // frame
					, isRef ? "true" : "false"
					, isPointer ? "true" : "false"
					, pointerLevel
				);
				return ret;
			}
			// 结构体如果是引用了c里的结构体，就没有meta的
			else {
				CostUsGuard g(this);
				auto ret = std::format(
					"orc_metaField_plainStruct(&pNext, \"{}\", sizeof({}), offsetof({}, {}), {}, {}, {});\n"
					, fieldName // frame
					, symbolDefinitionStruct_ofType->fullname
					, fullname // OrcCore$View
					, fieldName // frame
					, isRef ? "true" : "false"
					, isPointer ? "true" : "false"
					, pointerLevel
				);
				return ret;
			}
		}
		return "";
	}
	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override {
		//虚表
		auto className = ctx->Id(0)->getText();
		auto fullname = ctx->fullname;
		//auto classDef = space->findSymbolDefinitionByName_includeImports(className);
		auto superClassDefinition = space->findSuperClassSymbolDefinitionByAstClassDefinition(ctx);
		auto superFullname = superClassDefinition ? superClassDefinition->fullname : "Object";

		auto thisClassSymbol = std::dynamic_pointer_cast<SymbolDefinitionClass>(space->findSymbolDefinitionByName_exportedInThisSpace(className));
		std::string refcInitCode = thisClassSymbol->refc ? "1" : "0";

		auto block = ctx->classDefinitionBlock();
		auto fields = block->classFieldDeclaration();
		auto methods = block->methodDeclaration();

		// 字段初始化
		auto fieldsInitCode = string("");
		// 字段释放
		auto fieldsFiniCode = string("");
		// 字段meta初始化:基本类型、类类型、结构体类型
		auto fieldsMetaCode = string("");
		for (int i = 0, l = block->children.size(); i < l; i++) {
		//for (int i = 0, l = fields.size(); i < l; i++) {
			auto kid = block->children[i];

			//由于tmpReturn的存在， 所以block里可能额外存在StatementContenxt
			auto statement = dynamic_cast<OrcParser::StatementContext*>(kid);
			if (statement) {
				auto statCode = visitReturnString(statement);
				fieldsInitCode += statCode;
				continue;
			}

			//auto field = fields[i];
			auto field = dynamic_cast<OrcParser::ClassFieldDeclarationContext*>(kid);
			if (field) {

				//函数指针型字段 
				auto fnVar = field->functionPointerVarDeclaration();
				std::string fieldName;
				bool isPlainField = fnVar == nullptr;//普通的字段
				if (fnVar) {
					fieldName = fnVar->Id() ? fnVar->Id()->getText() : "";
				}
				else {
					fieldName = field->Id()->getText();
				}
			

				//确认字段实际归属的类名
				auto ownedClassFullname = ast_getMemberOwnedClassFullname_bySuperClassDefinition(superClassDefinition, fullname, fieldName);

				if (ownedClassFullname != fullname) {
					//禁止同名字段
					auto errInfo = std::format("can not declare same same field:{} at class {}, original declaration is in {} ", fieldName, fullname, ownedClassFullname);
					throw errInfo;
				}
				if (isPlainField) {// TODO 函数型指针，暂不生成元数据
					if (ctx->needCreateMeta ) { //元数据
						//字段符号
						auto fieldSymbol = std::dynamic_pointer_cast<SymbolDefinitionClassField>(thisClassSymbol->findMemberByName(fieldName));
						if (fieldSymbol) {
							auto fieldSymbolType = fieldSymbol->getType();
							auto metaCode = buildCode_forMeta(fieldSymbolType, fullname, fieldName);
							CostUsGuard g(this);
							fieldsMetaCode += metaCode;
						}
					}
				}
				auto ref = isPlainField ? field->type()->ref() : nullptr;
				auto closure = isPlainField ? field->type()->closureType() : nullptr;
				if (ref || closure) { // 引用需要特殊处理
					//字段的类  的符号定义。 用来判断是不是类
					auto fieldClassDef = ast_findSymbolDefinitionClass_byTypeContext(field->type(), space);
					auto right = string("NULL");
					if (field->assignRightPart() ){
						right = visitReturnString(field->assignRightPart()->singleExpression());
					}

					CostUsGuard g(this);
					auto fieldInitCode = std::format("{}(self, (void**)&(({}*)self)->{}, {});\n",
						fieldClassDef ? "urgc_set_field_class":"urgc_set_field",
						ownedClassFullname,
						field->Id()->getText(),
						right
					);
					fieldsInitCode += fieldInitCode;

					auto fieldFiniCode = std::format("{}(self, (void**)&(({}*)self)->{}, NULL);\n"
						, fieldClassDef ? "urgc_set_field_class" : "urgc_set_field"
						, ownedClassFullname, fieldName);
					fieldsFiniCode += fieldFiniCode;
				}
				else { //普通值
					if (field->assignRightPart()) { //有初值
						auto rightPartCode =
							field->assignRightPart() ? visitReturnString(field->assignRightPart()) : string("");
						CostUsGuard g(this);
						auto fieldInitCode = std::format("(({}*)self)->{} {};\n",
							ownedClassFullname, fieldName,
							rightPartCode
							);
						fieldsInitCode += fieldInitCode;
					}
				}
				continue;
			}
		}

		fieldsFiniCode = StrUtil::addPrefixPerLine(fieldsFiniCode, "\t");
		//好像FieldsFiniCode没有必要。因为都走到FiniCode了，都决定释放了， 内部的引用关系又不会影响urgc的处理.
		fieldsFiniCode = "";

		// 成员函数实现
		auto methodsCode = string("");
		// 初始化成员函数
		auto methodsInitCode = string(""); 

		auto methodsMetaCode = string("");
		for (int i = 0, l = methods.size(); i < l; i++) {
			auto method = methods[i];
			auto funcDef = method->functionDefinition();
			auto externFuncDef = method->externFunctionDeclaration();

			// 成员函数定义
			if (funcDef) {
				auto methodCode = visitReturnString(funcDef);
				CostUsGuard g(this);
				methodsCode += methodCode + "\n";
			}

			// 设置成员函数
			if (funcDef) {
				auto fieldName = funcDef->Id()->getText();
				//确认字段实际归属的类名
				auto ownedClassFullname = ast_getMemberOwnedClassFullname_bySuperClassDefinition(superClassDefinition, fullname, fieldName);

				auto methodInitCode = std::format("(({}*)self)->{} = (void*){};"
					, ownedClassFullname, fieldName, funcDef->fullname);
				methodsInitCode += methodInitCode + "\n";


				if (ctx->needCreateMeta  //需要生成元数据
					&& ownedClassFullname == fullname // 不是重载的方法
					) { //元数据
					CostUsGuard g(this);
					auto methodMetaCode = std::format("orc_metaField_method(&pNext, \"{}\", offsetof({}, {}));\n"
						, fieldName, fullname, fieldName);
					methodsMetaCode += methodMetaCode;
				}
			}
			else if (externFuncDef) {
				auto fieldName = externFuncDef->Id()->getText();
				//确认字段实际归属的类名
				auto ownedClassFullname = ast_getMemberOwnedClassFullname_bySuperClassDefinition(superClassDefinition, fullname, fieldName);

				CostUsGuard g(this);
				auto methodInitCode = std::format("(({}*)self)->{} = (void*){};"
					, ownedClassFullname, fieldName, externFuncDef->fullname);
				methodsInitCode += methodInitCode + "\n";


				if (ctx->needCreateMeta  //需要生成元数据
					&& ownedClassFullname == fullname // 不是重载的方法
					) { //元数据
					auto methodMetaCode = std::format("orc_metaField_method(&pNext, \"{}\", offsetof({}, {}));\n"
						, fieldName, fullname, fieldName);
					methodsMetaCode += methodMetaCode;
				}
			}
		}


		CostUsGuard g(this);
		methodsMetaCode = StrUtil::addPrefixPerLine(methodsMetaCode, "\t");
		fieldsMetaCode = StrUtil::addPrefixPerLine(fieldsMetaCode, "\t");
		fieldsInitCode = StrUtil::addPrefixPerLine(fieldsInitCode, "\t");
		methodsInitCode = StrUtil::addPrefixPerLine(methodsInitCode, "\t");
		
		

		auto vtableInstance = std::format(R"(Vtable_{} _vtable_{};)", ctx->fullname, ctx->fullname);
		auto newFunc = std::format(R"({} * {}_new(void *pOwner){{
	if (pOwner == NULL){{ return NULL;}}
    {} *self = calloc(1, sizeof({}));
	
    {}_init(self, pOwner);
    return self;
}}
)", fullname, fullname, fullname, fullname, fullname);
		auto initFunc = std::format(R"(
void {}_init({} *self, void *pOwner){{
    Vtable_{}_init(&_vtable_{});

    ((Object*)self)->vtable = (void*)&_vtable_{};
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    {}_init_fields(self);

    if (((Object*)self)->ctor){{
        ((Object*)self)->ctor((void*)self);
    }}

    //urgc_deguard(self);
}}
)"
, fullname
, fullname
, fullname
, fullname
, fullname
, fullname
);
		auto initFields = std::format(R"(

void {}_init_fields({} *self){{
	//super class
    {}_init_fields(({}*)self);

    ((Object*)self)->fini = (void*){}_fini;
	//fields
    {{
{}
    }}
{}
}}
)"	
, fullname, fullname, superFullname, superFullname, fullname, fieldsInitCode, methodsInitCode);

		auto finiFunc = std::format(R"(
void {}_fini({} *self){{
	//super fini
    {}_fini(({} *)self);

    //字段释放
{}

}}
)", fullname, fullname, superFullname, superFullname, fieldsFiniCode);
		auto vtableInit = std::format(R"(

Vtable_{}* Vtable_{}_init(Vtable_{}* pvt){{
    if (pvt == NULL){{
        pvt = &_vtable_{};
    }}
    if (((Vtable_Object*)pvt)->inited){{
        return pvt;
    }}
	// init super vtable
    Vtable_{}_init(&_vtable_{});

	// init by super vtable init function
    Vtable_{}_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_{};
    ((Vtable_Object*)pvt)->make = (void*)&{}_new;
    ((Vtable_Object*)pvt)->className = "{}";

    ((Vtable_Object*)pvt)->initMeta = (void*){}_initMeta;

    ((Vtable_Object*)pvt)->refc = {};

    return pvt;
}}
)"
, fullname, fullname, fullname
, fullname
, superFullname, superFullname
, superFullname
, superFullname
, fullname
, fullname
, fullname
, refcInitCode
);
		auto initMeta = string("");

		if (ctx->needCreateMeta) { //元数据
			initMeta = std::format(R"(
void {}_initMeta(Vtable_{} *pvt){{
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
{}

{}
}}
)", fullname, fullname, fieldsMetaCode, methodsMetaCode);
		}
		//类的结构定义
		string tag = std::format(R"(
//vtable instance
{}

// init meta
{}

// vtable init
{}

// fini function
{}
// init fields function
{}
// init function
{}
// new function
{}

// class members
{}
)"
, vtableInstance
, initMeta
, vtableInit
, finiFunc
, initFields
, initFunc
, newFunc
, methodsCode);
		//类的函数定义

		return tag;
		//return visitChildrenReturnString(ctx);
	}

	virtual std::any visitClassDefinitionBlock(OrcParser::ClassDefinitionBlockContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx) override {
		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitAssignRightPart(OrcParser::AssignRightPartContext* ctx) override {
		auto s0 = visitReturnString(ctx->singleExpression());
		return std::format("= {}", s0);
	}

	virtual std::any visitArgumentDeclaration(OrcParser::ArgumentDeclarationContext* ctx) override {
		auto type = ctx->type();
		if (type) {
			auto argName = ctx->Id()->getText();
			{ //闭包类型
				auto closureType = type->closureType();
				if (closureType) {
					auto returnCode = visitReturnString(closureType->type());
					auto args = visitReturnString(closureType->argumentsDeclaration());
					CostUsGuard g(this);
					return std::format("{} (**{}){}", returnCode, argName, args);
				}
			}

			auto text = type->getText();
			auto s0 = visitReturnString(ctx->type());
			CostUsGuard g(this);
			return std::format("{} {}", s0, argName);
		}


		return visitChildrenReturnString(ctx);
	}

	virtual std::any visitArgumentsDeclaration(OrcParser::ArgumentsDeclarationContext* ctx) override {
		std::string s = "(";
		auto args = ctx->argumentDeclaration();
		for (int i = 0, l = args.size(); i < l; i++) {
			auto tmp = visitReturnString(args[i]);
			CostUsGuard g(this);
			s += tmp;
			if (i < l - 1) {
				s += ", ";
			}
		}
		return s + ")";
	}

	virtual std::any visitFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext* ctx) override {
		//return visitChildrenReturnString(ctx);

		auto type = visitReturnString(ctx->type());
		auto id = ctx->Id() ? ctx->Id()->getText() : "";
		auto args = visitReturnString(ctx->argumentsDeclaration());
		std::string ptrs = "";
		for (int i = 1; i < ctx->children.size(); i++) {
			auto kid = ctx->children[i];
			auto term = dynamic_cast<antlr4::tree::TerminalNode*>(kid);
			if (term && term->getText() == "*") {
				ptrs += "*";
			}
		}


		return std::format("{} ({}{}){}", type, ptrs, id, args);
	}


	//生成函数声明
	virtual std::any visitFunctionDefinition(OrcParser::FunctionDefinitionContext* ctx) override {
		auto type = visitReturnString(ctx->type());
		auto args = visitReturnString(ctx->argumentsDeclaration());
		auto name = ctx->fullname.empty() ? ctx->Id()->getText() : ctx->fullname;
		auto block = visitReturnString(ctx->block());

		//生成对ref类型的arg的处理
		auto argDecls = ctx->argumentsDeclaration()->argumentDeclaration();
		string refArgCode = "";
		for (auto argDecl : argDecls) {
			auto symbolType = typeContext_toSymbolType(argDecl->type());
			//ref类型的参数
			if (std::dynamic_pointer_cast<SymbolTypeRef>(symbolType)) {
				auto defClass = ast_findSymbolDefinitionClass_byTypeContext(argDecl->type(), space);
				refArgCode += std::format("\t{}({});\n", 
					defClass ? "URGC_REF_ARG_WITH_CLEANUP_CLASS":"URGC_REF_ARG_WITH_CLEANUP",
					
					argDecl->Id()->getText());
			}
		}
		if (!refArgCode.empty()) {
			block = block.substr(0, 1) + "\n" + refArgCode + block.substr(1);
		}

		return type + " " + name + args + block + "\n";
	}

	//生成函数声明
	virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* ctx) override {
		//外部函数，不需要有实现
		if (ctx->externFunctionDeclaration()) {
			return string("");
		}
		if (ctx->functionDefinition()) {
			auto functionCode = visitReturnString(ctx->functionDefinition());

			//静态函数，需要预声明
			if (ctx->Static()) {
				//需要有预声明
				GenHeadCodeVisitor declVi;
				declVi.mk = this->mk;
				declVi.space = space;
				auto declarationCode = declVi.visitFunctionDefinition(ctx->functionDefinition());
				CostUsGuard g(this);
				auto declarationCodeStr = std::any_cast<string>(declarationCode);
				staticFunctionDeclaratonsCode += string("static ") + declarationCodeStr;
				return string("static ") + functionCode;
			}
			return functionCode;
		}
		return string("invalid global function definition:") + ctx->getText();
	}

	virtual std::any visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* ctx) override {
		//if (ctx->varDeclaration()->Static()) {

		//	return string("static ") + visitChildrenReturnString(ctx) + ";\n";
		//}
		return visitChildrenReturnString(ctx) + ";\n";
	}

	virtual std::any visitExternFunctionDeclaration(OrcParser::ExternFunctionDeclarationContext* ctx) override {
		return string("");
	}

	virtual std::any visitImportStatement(OrcParser::ImportStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitIncludeStatement(OrcParser::IncludeStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitIncludePathCharacters(OrcParser::IncludePathCharactersContext* ctx) override {
		return string("");
	}

	virtual std::any visitPackageStatement(OrcParser::PackageStatementContext* ctx) override {
		return string("");
	}

	virtual std::any visitLiteral(OrcParser::LiteralContext* ctx) override {
		auto nullLiteral = ctx->NullLiteral();
		if (nullLiteral) {
			return string("NULL");
		}
		//{//处理INFINITY/NAN
		//	auto lit = ctx->DecimalLiteral();
		//	if (lit) {
		//		auto text = lit->getText();
		//		if (text == "infinity") {
		//			return string("infinity");
		//		}
		//		if (text == "nan") {
		//			return string("NAN");
		//		}
		//	}
		//}
		auto text = ctx->getText();
		//return ctx->getText();
		if (text == "nan") {
			return string("NAN");
		}
		if (text == "infinity") {
			return string("INFINITY");
		}
		return text;
	}

	virtual std::any visitEos(OrcParser::EosContext* ctx) override {
		//return string(";//eos\n");
		return string("");
	}


};


class  FullnameVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:
	//block deep,判断是否在类中、extension中、结构体中 
	int deep = 0;
	std::string packageName;
	OrcParser::ExtensionDefinitionContext* curExtension = NULL;
	OrcParser::ClassDefinitionContext* curClass = NULL;
	OrcParser::StructDefinitionContext* curStruct = NULL;
	std::string ownedSpaceName; //所属的空间名称

	bool isInClassOrExtension() {
		return curClass != NULL || curExtension != NULL;
	}

	/// The default implementation calls <seealso cref="ParseTree#accept"/> on the
	/// specified tree.
	virtual std::any visitChildren(antlr4::tree::ParseTree* tree) override {
		int deepOffset = 0;
		{
			auto n = dynamic_cast<OrcParser::PackageStatementContext*>(tree);
			if (n) {
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				packageName = n->Id()->getText();
				ownedSpaceName = packageName;
				//printf("找到包名:%s\n", packageName.c_str());
			}
		}

		{
			auto n = dynamic_cast<OrcParser::EnumDefinitionContext*>(tree);
			if (n) {
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				n->fullname = ast_mkFullname_byPrefix(packageName , n->Id()->getText());
				ownedSpaceName = n->fullname;
				//printf("找到枚举的全名:%s\n", n->fullname.c_str());

				auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
				return ret;
			}
		}
		{
			auto n = dynamic_cast<OrcParser::EnumItemContext*>(tree);
			if (n) {
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				n->fullname = ast_mkFullname_byPrefix(packageName , n->Id()->getText());
				ownedSpaceName = n->fullname;
				//printf("找到枚举项的全名:%s\n", n->fullname.c_str());

				auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);

				ownedSpaceName = packageName;
				return ret;
			}
		}

		{
			auto n = dynamic_cast<OrcParser::EnumDefinitionContext*>(tree);
			if (n) {
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				n->fullname = ast_mkFullname_byPrefix(packageName , n->Id()->getText());
				ownedSpaceName = n->fullname;
				//printf("找到枚举的全名:%s\n", n->fullname.c_str());

				auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
				ownedSpaceName = packageName;
				return ret;
			}
		}
		{
			auto n = dynamic_cast<OrcParser::ClassDefinitionContext*>(tree);
			if (n) {
				if (!n->Id(0)) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				n->needCreateMeta = true; //标记需要创建meta元数据
				deepOffset = 1;
				n->fullname = ast_mkFullname_byPrefix(packageName , n->Id(0)->getText() );
				ownedSpaceName = n->fullname;
				//printf("找到类的全名:%s\n", n->fullname.c_str());

				curClass = n;
				auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
				curClass = NULL;
				ownedSpaceName = packageName;
				return ret;
			}
		}
		{
			auto n = dynamic_cast<OrcParser::ExtensionDefinitionContext*>(tree);
			if (n) {
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				n->fullname = ast_mkFullname_byPrefix(packageName , n->Id()->getText() );
				ownedSpaceName = n->fullname;
				//printf("找到扩展的全名:%s\n", n->fullname.c_str());

				curExtension = n;
				auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
				curExtension = NULL;
				ownedSpaceName = packageName;
				return ret;
			}
		}
		{
			auto n = dynamic_cast<OrcParser::StructDefinitionContext*>(tree);
			if (n) {
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				deepOffset = 1;
				n->needCreateMeta = true; //标记需要创建meta元数据
				n->fullname = ast_mkFullname_byPrefix(packageName , n->Id()->getText());
				//printf("找到结构体的全名:%s\n", n->fullname.c_str());

				curStruct = n;
				auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
				curStruct = NULL;
				ownedSpaceName = packageName;
				return ret;
			}
		}

		{ //全局函数声明
			auto n = dynamic_cast<OrcParser::GlobalFunctionDefinitionContext*>(tree);
			if (n) {
				if (n->Static()) { //静态函数不用处理名称

				}
				else {
					{ //函数定义
						auto fn = n->functionDefinition();
						if (fn) {
							if (!fn->Id()) {
								throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
							}
							fn->fullname = ast_mkFullname_byPrefix(ownedSpaceName , fn->Id()->getText());
							//printf("找到全局函数定义的全名:%s\n", fn->fullname.c_str());
						}
					}

					{ //外部函数声明
						auto fn = n->externFunctionDeclaration();
						if (fn) {
							if (!fn->Id()) {
								throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
							}
							fn->fullname = ast_mkFullname_byPrefix(ownedSpaceName , fn->Id()->getText());
							//printf("找到全局外部函数声明的全名:%s\n", fn->fullname.c_str());
						}
					}
				}
			}
		}


		{ //函数定义
			auto n = dynamic_cast<OrcParser::FunctionDefinitionContext*>(tree);
			if (n && isInClassOrExtension()) { //内部的函数
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				n->fullname = ast_mkFullname_byPrefix(ownedSpaceName , n->Id()->getText());
				//printf("找到函数定义的全名:%s\n", n->fullname.c_str());
			}
		}

		{ //外部函数声明
			auto n = dynamic_cast<OrcParser::ExternFunctionDeclarationContext*>(tree);
			if (n && isInClassOrExtension()) { //内部的函数
				if (!n->Id()) {
					throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
				}
				n->fullname = ast_mkFullname_byPrefix(ownedSpaceName , n->Id()->getText());
				//printf("找到外部函数声明的全名:%s\n", n->fullname.c_str());
			}
		}

		{ //全局变量声明
			auto n = dynamic_cast<OrcParser::GlobalVarDeclarationContext*>(tree);
			if (n) {
				if (n->varDeclaration()->Static()) { //静态全局变量

					//printf("找到静态全局变量声明的全名:%s\n", n->getText().c_str());
				}
				else { //全局变量
					auto var = n->varDeclaration();
					if (var) {
						if (!var->Id()) {
							throw std::format("exception: Fullname visit error. {} do not have n->Id()", tree->getText());
						}
						var->fullname = ast_mkFullname_byPrefix(ownedSpaceName , var->Id()->getText());
						//printf("找到全局变量声明的全名:%s\n", var->fullname.c_str());
					}
				}

			}
		}

		deep += deepOffset; //深度
		auto ret = antlr4::tree::AbstractParseTreeVisitor::visitChildren(tree);
		deep -= deepOffset;
		return ret;
	}
};


std::vector<std::shared_ptr<SymbolSpace>> SymbolSpace::listSymbolSpace_includeSelfAndImports()
{
	std::vector<std::shared_ptr<SymbolSpace>> ret;

	ret.push_back(this->shared_from_this());
	for (auto& imp : imports) {
		auto impSpace = this->symbolSpaceLoader->load_baseOnSymbolSpace(this, imp.get());
		if (impSpace) {
			ret.push_back(impSpace);
		}
	}

	return ret;
}

void SymbolSpace::fulfillFullname(antlr4::tree::ParseTree* tree)
{
	FullnameVisitor fullnameVisitor;
	fullnameVisitor.visit(tree);
}


std::shared_ptr<SymbolSpace> SymbolSpace::buildSymbolSpace(std::string path, antlr4::tree::ParseTree* tree,
	std::shared_ptr<OrcParser> parser) {
	SymbolSpace::fulfillFullname(tree);

	AstMake mk;
	tree::ParseTreeTracker _tracker;
	mk.tracker = &_tracker;

	printf("构建符号表:%s\n", path.c_str());

	SymbolBuilderVisitor vi;

	vi.init(path);
	vi.space = this->shared_from_this();
	vi.visit(tree);
	vi.postProcess();

	//printf("\n%s\n", vi.space->toString().c_str());

	return vi.space;
}

bool SymbolSpace::startBuild(std::string path, antlr4::tree::ParseTree* tree,
	std::shared_ptr<OrcParser> parser, CostUs &cost) {

	ast_printTree(tree, parser.get());

	cnt_calcSymbolTypeOfExpr = 0;
	cnt_calcSymbolTypeOfExprCache = 0;

	//CostUs cost;

	gParser = parser.get();

	SymbolSpace::fulfillFullname(tree);
	cost.stat("fulfillFullname");

	AstMake mk;
	tree::ParseTreeTracker _tracker;
	mk.tracker = &_tracker;

	printf("编译:%s\n", path.c_str());

	SymbolBuilderVisitor vi;

	vi.init(path);
	vi.space = this->shared_from_this();
	vi.visit(tree);
	vi.postProcess();
	cost.stat("SymbolBuilderVisitor");

	//类型检查
	if (0) {
		TypeCheckerVisitor checkVi;
		checkVi.space = this->shared_from_this();
		checkVi.doCheck(tree);
	}

	//printf("\n%s\n", vi.space->toString().c_str());

	try {
		//ast_printTree(tree, parser.get());

		//给方法添加self参数
		AddSelfArgumentVisitor addSelfArgumentVisitor;
		addSelfArgumentVisitor.mk = &mk;
		addSelfArgumentVisitor.visit(tree);
		cost.stat("addSelfArgumentVisitor");


		ClosureCollectCaptureInfoVisitor closureVi;
		closureVi.mk = &mk;
		closureVi.space = vi.space;
		closureVi.symbolBuilder = &vi;
		closureVi.visit(tree);
		cost.stat("closureVi");

		//ast_printTree(tree, parser.get());


		closureVi.translate();
		cost.stat("closureVi translate");

		GenOrcCodeVisitor orcVi;

		//printf("after closure translate:%s\n", orcVi.visitReturnString(tree).c_str());

		//ast_printTree(tree, parser.get());


		AddOutRefArgumentVisitor addOutRefArgumentVisitor;
		addOutRefArgumentVisitor.mk = &mk;
		addOutRefArgumentVisitor.visit(tree);
		cost.stat("AddOutRefArgumentVisitor");

		//转译 
		TranslateVisitor translateVisitor;
		translateVisitor.mk = &mk;
		translateVisitor.space = vi.space;
		translateVisitor.visit(tree);
		cost.stat("TranslateVisitor");


		//ast_printTree(tree, parser.get());

		GenHeadCodeVisitor hcVi;
		hcVi.path = vi.space->path;
		hcVi.mk = &mk;
		hcVi.space = vi.space;
		auto headCode = hcVi.visitReturnString(tree);

		cost.stat("headCode");
		//printf("====================head code:%s\n", headCode.c_str());

		GenCodeVisitor codeVi;
		codeVi.mk = &mk;
		codeVi.space = vi.space;
		codeVi.path = path;// "src/Sui/App.orc";
		auto code = codeVi.visitReturnString(tree);
		cost.stat("code");
		//printf("====================code:%s\n", code.c_str());
		//printf("生成代码耗时us:%lld\n", codeVi.aggregateCostUs);

		std::filesystem::path pathObj(path);

		auto stemWithDir = pathObj.parent_path() / pathObj.stem();
		auto hPath = stemWithDir.string() + "_orc.h";
		auto cPath = stemWithDir.string() + "_orc.c";

		//去重
		if (Path(hPath).exists()) {
			auto oldHeaderCode = FsUtil::read_all_text(hPath);
			auto changed = oldHeaderCode != headCode;
			cost.stat("check head changed");
			if (changed) {
				FsUtil::write_all_text(hPath, headCode);
			}
		}
		else { //头文件不存在，就直接写入
			FsUtil::write_all_text(hPath, headCode);
		}
		cost.stat("write_all_text header");
		FsUtil::write_all_text(cPath, code);
		cost.stat("write_all_text code");
		//cost.print("startBuild");
		return true;
	}
	catch (string e) {
		extern void log(std::string msg);
		log(std::format("\t编译异常:{}\n", e));
		//return vi.space;
		throw e;
		return false;
	}
}

std::shared_ptr<SymbolSpace> SymbolSpace::build(std::string path, antlr4::tree::ParseTree* tree,
	std::shared_ptr<OrcParser> parser) {
	SymbolSpace::fulfillFullname(tree);

	AstMake mk;
	tree::ParseTreeTracker _tracker;
	mk.tracker = &_tracker;

	printf("构建符号表\n");

	SymbolBuilderVisitor vi;
	
	vi.init(path);
	vi.visit(tree);
	vi.postProcess();

	printf("\n%s\n", vi.space->toString().c_str());

	try {
		//ast_printTree(tree, parser.get());

		ClosureCollectCaptureInfoVisitor closureVi;
		closureVi.mk = &mk;
		closureVi.space = vi.space;
		closureVi.symbolBuilder = &vi;
		closureVi.visit(tree);

		//ast_printTree(tree, parser.get());

		closureVi.translate();

		//ast_printTree(tree, parser.get());

		//给方法添加self参数
		AddSelfArgumentVisitor addSelfArgumentVisitor;
		addSelfArgumentVisitor.mk = &mk;
		addSelfArgumentVisitor.visit(tree);


		AddOutRefArgumentVisitor addOutRefArgumentVisitor;
		addOutRefArgumentVisitor.mk = &mk;
		addOutRefArgumentVisitor.visit(tree);

		//转译 
		TranslateVisitor translateVisitor;
		translateVisitor.mk = &mk;
		translateVisitor.space = vi.space;
			translateVisitor.visit(tree);
	
		GenHeadCodeVisitor hcVi;
		hcVi.mk = &mk;
		hcVi.space = vi.space;
		auto headCode = hcVi.visitReturnString(tree);
		printf("====================head code:%s\n", headCode.c_str());

		GenCodeVisitor codeVi;
		codeVi.mk = &mk;
		codeVi.space = vi.space;
		codeVi.path = path;// "src/Sui/App.orc";
		auto code = codeVi.visitReturnString(tree);
		printf("====================code:%s\n", code.c_str());

		std::filesystem::path pathObj(path);
		
		auto stemWithDir = pathObj.parent_path() / pathObj.stem();
		auto hPath = stemWithDir.string() + "_orc.h";
		auto cPath = stemWithDir.string() + "_orc.c";

		FsUtil::write_all_text(hPath, headCode);
		FsUtil::write_all_text(cPath, code);
		return vi.space;
	}
	catch (string e) {
		printf("编译异常:%s\n", e.c_str());
		return vi.space;
	}
}

std::shared_ptr<SymbolSpace>  SymbolSpace::buildSymbolSpace_forInclude(std::string orcPath, std::string path, std::string includeSegment,
	std::shared_ptr<SymbolSpaceLoader> loader)
{
	std::filesystem::path orcPath_fs(orcPath);
	std::filesystem::path path_fs(path);
	auto fname = path_fs.stem().string();
	auto orcPathStem = orcPath_fs.stem().string();


	//创建c临时文件
	auto tmpCPath = orcPath_fs.parent_path() / (fname + "-tmp.c");
	FsUtil$write_all_text(tmpCPath.string().c_str(), includeSegment.c_str(), "w+");
	printf("创建c临时文件成功:%s %s\n", tmpCPath.string().c_str(), includeSegment.c_str());

	//调用clang生成 ast json
	auto synJsonPath = orcPath_fs.parent_path() / (fname + "-symbol.json");
	auto cmdline = std::format("clang -I.. -Xclang -ast-dump=json -fsyntax-only \"{}\" > \"{}\"", tmpCPath.string(), synJsonPath.string());
	printf("使用clang生成符号文件. cmdline=%s\n", cmdline.c_str());
	int exitCode = system(cmdline.c_str());
	if (exitCode != 0) {
		auto err = std::format("通过符号Json文件失败:%s", synJsonPath.string().c_str());
		throw err;
	}
	printf("生成符号json文件%s成功\n", synJsonPath.string().c_str());

	auto ret = buildFromAstJson(synJsonPath.string(), path, loader);


	std::filesystem::remove(synJsonPath);
	std::filesystem::remove(tmpCPath);

	return ret;
	//return nullptr;
}

class AstJsonVisitor {
public:
	std::function<bool (json&)> visitCb;
	std::function<void(json&)> cbLeave;

	void visit(json &jo) {
		bool dive = visitCb(jo);
		if (dive) {
			visitArray(jo);
			visitObject(jo);
		}
		if (cbLeave) {
			cbLeave(jo);
		}
	}
	void visitArray(json& jo) {
		if (jo.is_array()) {
			for (int i = 0, l = jo.size(); i < l; i++) {
				auto& kid = jo[i];
				visit(kid);
			}
		}
	}
	void visitObject(json& jo) {
		if (jo.is_object()) {
			for (auto& it : jo.items()) {
				visit(it.value());
			}
		}
	}
};


class AstParser {
public:
	std::shared_ptr<ANTLRInputStream> input;
	std::shared_ptr<OrcLexer> lexer;
	std::shared_ptr<CommonTokenStream> tokens;
	std::shared_ptr<OrcParser> parser;

	AstParser* init(const char* str) {
		input = std::make_shared<ANTLRInputStream>(str);
		lexer = std::make_shared<OrcLexer>(input.get());
		tokens = std::make_shared<CommonTokenStream>(lexer.get());

		//auto tokenStr = tokens->getText();
		//std::cout << "Parse tokens: " << tokenStr << std::endl;
		//auto tokenVec = tokens->getTokens();
		//for (auto token : tokenVec) {
		//	std::cout << "\t" << token->getType() << ":" << token->getText() << std::endl;
		//}

		parser = std::make_shared<OrcParser>(tokens.get());
		return this;
	}

	void printTree(
		tree::ParseTree* tree) {
		auto s = tree->toStringTree(this->parser.get(), true);

		std::cout << "Parse Tree: " << s << std::endl;
	}
};
std::shared_ptr<SymbolSpace> SymbolSpace::buildFromAstJson(std::string path, std::string headerPath, 
	
	std::shared_ptr<SymbolSpaceLoader> loader)
{
	//path = "E:\\luwa\\oms_ts\\orc-antlr\\antlr4-cpp\\demo\\test.json";
	auto text = FsUtil$read_all_text(path.c_str(), "r+");
	json jo = nlohmann::json::parse(text);
	AstJsonVisitor vi;

	auto space = std::make_shared<SymbolSpace>();
	space->path = headerPath;
	space->symbolSpaceLoader = loader;

	//std::vector< AstJsonStackItem> stack;

	auto  getTypeFromTypeJo = [](json& type)->std::string {
		if (type.is_object()) {
			auto& desugaredQualType = type["desugaredQualType"];
			auto& qualType = type["qualType"];
			auto typeString = !desugaredQualType.empty() ? desugaredQualType.get<string>()
				: !qualType.empty() ? qualType.get<string>() : "";
			return typeString;
		}
		return "";
	};

	vi.cbLeave = [&](json& jo) {
	};
	vi.visitCb = [&](json& jo) -> bool {
		if (jo.is_object()) {
			if (jo.contains("kind")) {
				auto kind = jo["kind"].get < std::string>();

				if (kind == "FunctionDecl") {
					auto type = jo["type"];
					auto desugaredQualType = type["desugaredQualType"] ;
					if (!desugaredQualType.is_null()) { //不处理c++的引用
						auto str = desugaredQualType.get<string>();
						if (str.find("&") != -1) {
							return false;
						}
					}
					auto qualType = type["qualType"];
					if (!qualType.is_null()) { //不处理c++的引用
						auto str = qualType.get<string>();
						if (str.find("&") != -1) {
							return false;
						}
					}
					auto typeString = desugaredQualType.empty() ? qualType.get<string>() : desugaredQualType.get<string>();


					auto nameJo = jo["name"];
					auto name = nameJo.is_string() ? nameJo.get<string>() : "";
					//printf("kind:%s type:%s; name:%s, full:\n", kind.c_str(), typeString.c_str() , name.c_str(), jo.dump().c_str());
					if (!name.empty()) { //构建符号
						auto sym = std::make_shared<SymbolDefinitionFunction>();
						//auto fnType = std::make_shared<SymbolTypeFunction>();

						AstParser p;
						p.init(typeString.c_str());
						auto astFunctionType = p.parser->functionType();
						if (p.parser->getNumberOfSyntaxErrors() > 0) {
							printf("err kind:%s type:%s; name:%s, full:\n", kind.c_str(), typeString.c_str(), name.c_str(), jo.dump().c_str());
						}

						auto fnType = ast_createSymbolTypeFunction(
							astFunctionType->type(), astFunctionType->argumentsDeclaration()
						);
						//fnType->returnType = typeContext_toSymbolType(astFunctionType->type());

						sym->name = name;
						sym->fullname = name;
						sym->type = fnType;
						space->addSymbolOnce(sym);
					}
				}
				else if (kind == "TypedefDecl") {
					auto type = jo["type"];
					if (type.is_object()) {
						auto& desugaredQualType = type["desugaredQualType"];
						auto& qualType = type["qualType"];
						auto nameJo = jo["name"];
						auto name = nameJo.is_string() ? nameJo.get<string>() : "";

						auto typeString = !desugaredQualType.empty() ? desugaredQualType.get<string>()
							: !qualType.empty() ? qualType.get<string>() : "";
						

						if (desugaredQualType.is_string()) {
							printf("kind:%s %s:desugared %s => %s \n", kind.c_str(), name.c_str(), qualType.get<string>().c_str(),
								desugaredQualType.get<string>().c_str());
						}
						else if (qualType.is_string()) {
							printf("kind:%s %s:%s\n", kind.c_str(), name.c_str(), qualType.get<string>().c_str());
						}
						else {
							printf("kind:%s. no qualType:%s\n", kind.c_str(), jo.dump().c_str());
						}
						//TODO 不处理_Atomic(bool...的情况
						if (typeString.starts_with("_Atomic(")) {
							typeString = "";
						}

						if (!typeString.empty()) {
							if (!name.empty()) { //构建符号
								AstParser p;
								p.init(typeString.c_str());
								auto astType = p.parser->type();
								if (p.parser->getNumberOfSyntaxErrors() > 0) {
									printf("err kind:%s %s:%s\n", kind.c_str(), name.c_str(), typeString.c_str());
								}

								auto sym = std::make_shared<SymbolDefinitionTypedef>();
								sym->name = name;
								sym->fullname = name;
								sym->type = typeContext_toSymbolType(astType);
								space->addSymbolOnce(sym);
							}
						}
					}
					else {
						//printf("kind:%s. no type:%s\n", kind.c_str(), jo.dump().c_str());
					}

				}

				else if (kind == "RecordDecl") { //结构体声明
					auto completeDefinition = jo["completeDefinition"]; //是否有完整 的声明
					if (completeDefinition.is_boolean() && completeDefinition.get<bool>()
						&& jo.contains("name")
						&& jo.contains("inner")
						) {
						auto structName = jo["name"].get<std::string>();
						auto structSymDef = std::make_shared<SymbolDefinitionStruct>();
						structSymDef->name = structName;
						structSymDef->fullname = structName;
						space->addSymbolOnce(structSymDef);

						printf("解析ast.json中的结构体声明. structName:%s\n", structName.c_str());
						AstJsonVisitor innervi;
						innervi.visitCb = [&](json &jo)->bool {
							auto kind =  jo.contains("kind") ? jo["kind"].get<std::string>():std::string("");
							if (kind == "FieldDecl" && jo.contains("name")) {
								auto name = jo["name"].get<std::string>();
								auto type = jo["type"];
								auto typeString = getTypeFromTypeJo(type);

								if (!typeString.empty()) {
									if (!name.empty()) { //构建符号
										AstParser p;
										p.init(typeString.c_str());
										auto astType = p.parser->type();
										auto stopIndex = astType->getStop()->getStopIndex();
										if (p.parser->getNumberOfSyntaxErrors() == 0
											&& stopIndex == typeString.size() - 1 
											) {
											//printf("err kind:%s %s:%s\n", kind.c_str(), name.c_str(), typeString.c_str());

											auto sym = std::make_shared<SymbolDefinitionClassField>();
											sym->name = name;
											sym->fullname = name;
											sym->type = typeContext_toSymbolType(astType);
											structSymDef->members.push_back(sym);
										}
										else {
											AstParser p;
											p.init(typeString.c_str());
											auto fnType = p.parser->functionPointerVarDeclaration();
											
											if (p.parser->getNumberOfSyntaxErrors() > 0) {
												printf("err kind:%s %s:%s\n", kind.c_str(), name.c_str(), typeString.c_str());
											}
											else { //解析到函数指针型类型
												auto sym = std::make_shared<SymbolDefinitionClassField>();
												sym->name = name;
												sym->fullname = name;
												sym->type = ast_createSymbolTypeFunction(
													fnType->type(), fnType->argumentsDeclaration()
												);
												structSymDef->members.push_back(sym);
											}
										}
									}
								}
								return false;
							}
							return true;
						};
						innervi.visit(jo["inner"]);
					}
					else {
						//printf("kind:%s. no type:%s\n", kind.c_str(), jo.dump().c_str());
					}
				}
				else if (kind == "EnumDecl") {
					printf("EnumDecl kind:%s\n", kind.c_str());

					if (jo.contains("name")) {
						auto name = jo["name"].get<std::string>();
						auto def = std::make_shared<SymbolDefinitionEnum>();
						def->name = name;
						def->fullname = name;
						space->addSymbolOnce(def);
					}

					if (jo.contains("inner")) {

						AstJsonVisitor innervi;
						innervi.visitCb = [&](json& jo)->bool {
							auto kind = jo.contains("kind") ? jo["kind"].get<std::string>() : std::string("");
							if (kind == "EnumConstantDecl" && jo.contains("name")) {
								auto name = jo["name"].get<std::string>();
								auto type = jo["type"];
								auto typeString = getTypeFromTypeJo(type);

								if (!typeString.empty()) {
									if (!name.empty()) { //构建符号

										AstParser p;
										p.init(typeString.c_str());
										auto astType = p.parser->type();
										if (p.parser->getNumberOfSyntaxErrors() > 0) {
											printf("err kind:%s %s:%s\n", kind.c_str(), name.c_str(), typeString.c_str());
										}

										auto sym = std::make_shared<SymbolDefinitionEnumItem>();
										sym->name = name;
										sym->fullname = name;
										sym->type = typeContext_toSymbolType(astType);
										space->addSymbolOnce(sym);
									}
								}
								return false;
							}
							return true;
						};
						innervi.visit(jo["inner"]);
					}
				}
				else if (kind == "VarDecl") {
					auto nameJo = jo["name"];
					auto name = nameJo.is_string() ? nameJo.get<string>() : "";
					auto type = jo["type"];
					auto &desugaredQualType = type["desugaredQualType"];
					auto &qualType = type["qualType"];

					if (!desugaredQualType.is_null()
						|| !qualType.is_null()) { //具有类型
						auto str = !desugaredQualType.is_null() ? desugaredQualType.get<string>(): qualType.get<string>();
						if (str.find("&") != -1) {
							return false;
						}

						auto typeString = desugaredQualType.empty() ? qualType.get<string>() : desugaredQualType.get<string>();
						//printf("kind:%s %s desugaredQualType:%s %s\n", kind.c_str(), name.c_str(), typeString.c_str(), jo.dump().c_str());



						if (!typeString.empty()) {
							if (!name.empty()) { //构建符号
								AstParser p;
								p.init(typeString.c_str());
								auto astType = p.parser->type();
								if (p.parser->getNumberOfSyntaxErrors() > 0) {
									printf("err kind:%s %s:%s\n", kind.c_str(), name.c_str(), typeString.c_str());
								}

								auto sym = std::make_shared<SymbolDefinitionVar>();
								sym->name = name;
								sym->fullname = name;
								sym->type = typeContext_toSymbolType(astType);
								space->addSymbolOnce(sym);
							}
						}
					}
					else {
						printf("kind:%s no desugaredQualType:%s\n", kind.c_str(), jo.dump().c_str());

					}
				}

			}
		}
		return true;
	};
	vi.visit(jo);

	return space;
}

//通过名称去查找符号定义,不是全局名称。 全局名称其实只在生成代码时有用,符号查找都是用名称的
//只查找本空间导出的符号
std::shared_ptr<SymbolDefinition> SymbolSpace::findSymbolDefinitionByName_exportedInThisSpace(std::string name)
{
	for (auto& def : symbols) {
		if (def->name == name) {
			def->setHostSpace(this);
			return def;
		}
	}
	return nullptr;
}

std::shared_ptr<SymbolDefinitionClass> SymbolSpace::findSuperClassSymbolDefinitionByAstClassDefinition(OrcParser::ClassDefinitionContext* ctx) {

	auto superNameId = ctx->Id(1);
	if (superNameId) {
		auto superName = superNameId->getText();
		auto superClassDef = this->findSymbolDefinitionByName_includeImports(superName);
		if (superClassDef) {
			return std::dynamic_pointer_cast<SymbolDefinitionClass>(superClassDef);
		}
	}
	//采用默认的继承Object
	return gocSymbolDefinitionClass_Object(this->symbolSpaceLoader);
}

ExtensionMemberInfo SymbolSpace::findExtensionMemberByTypeNameAndMemberName_exportedInThisSpace(std::string name, std::string memberName)
{
	ExtensionMemberInfo ret;
	for (auto& def : symbols) {
		auto extensionDef = std::dynamic_pointer_cast<SymbolDefinitionExtension>(def);
		if (extensionDef && extensionDef->name == name) {
			for (auto& member : extensionDef->members) {
				auto memberMethod = std::dynamic_pointer_cast<SymbolDefinitionMethod>(member);
				if (memberMethod->name == memberName) {
					memberMethod->setHostSpace(this);
					extensionDef->setHostSpace(this);
					ret.methodDef = (memberMethod);
					ret.extensionDef = ( extensionDef );
				}
			}
		}
	}
	return ret;
}

ExtensionMemberInfo SymbolSpace::findExtensionMemberByTypeNameAndMemberName_includeImports(std::string name, std::string memberName)
{
	auto def = this->findExtensionMemberByTypeNameAndMemberName_exportedInThisSpace(name, memberName);
	if (def.methodDef) {
		return def;
	}
	//从import中查找
	//TODO 考虑alias
	if (this->symbolSpaceLoader) {
		std::vector<std::vector<std::shared_ptr<Import>>*> importsList{ &imports, &hiddenImports };
		for (auto imps : importsList) {
			for (auto& imp : *imps) {
				auto impSpace = this->symbolSpaceLoader->load_baseOnSymbolSpace(this, imp.get());
				if (impSpace) { //加载符号表成功
					auto impDef = impSpace->findExtensionMemberByTypeNameAndMemberName_exportedInThisSpace(name, memberName);
					if (impDef.methodDef) {
						return impDef;
					}
				}
			}
		}
	}
	{

		auto def = this->findSymbolDefinitionByName_includeImports(name);
		//类
		auto classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(def);
		//考虑父类
		while (classDef) {
			auto super = classDef->findSuperSymbolDefinition();
			if (!super) { // 没有父类
				break;
			}
			auto memInfo = this->findExtensionMemberByTypeNameAndMemberName_includeImports(super->name, memberName);
			if (memInfo.methodDef) {
				return memInfo;
			}
			classDef = super;
		}
	}
	return ExtensionMemberInfo{};
}

void SymbolSpace::addSymbolOnce(std::shared_ptr<SymbolDefinition> sym)
{
	if (sym != nullptr) {
		auto found = findSymbolDefinitionByName_exportedInThisSpace(sym->name);
		if (found != nullptr) {
			return;
		}
		symbols.push_back(sym);
	}
}

void SymbolSpace::addHiddenImport_byPath(std::string abspath)
{
	std::shared_ptr<Import> imp = std::make_shared<Import>();
	imp->path = abspath;
	addHiddenImport(imp);
}

void SymbolSpace::addHiddenImport(std::shared_ptr<Import> refImport)
{
	hiddenImports.push_back(refImport);
}


std::string SymbolSpace::gocAbspath() {

	if (this->_abspath.empty()) {

		Path p(this->path);
		if (!p.isAbsolute()) {
			_abspath = p.getAbsolute().path();
		}
		else {
			_abspath = this->path;
		}
	}
	return this->_abspath;
}
std::shared_ptr<Import> SymbolSpace::findImportByAbspath(std::string abspath) {

	for (auto imp : imports) {
		Path p(imp->abspath);
		if (p.getAbsolute().path()  == abspath || imp->path == abspath) {
			return imp;
		}
	}
	for (auto imp : hiddenImports) {
		Path p(imp->abspath);
		if (p.getAbsolute().path() == abspath || imp->path == abspath) {
			return imp;
		}
	}
	return nullptr;
}

bool SymbolSpace::existsImport(std::string abspath)
{
	for (auto imp : imports) {
		if (imp->path == abspath) {
			return true;
		}
	}
	for (auto imp : hiddenImports) {
		if (imp->path == abspath) {
			return true;
		}
	}
	return false;
}

void SymbolSpace::addHiddenImport_byPath_ifNeed(std::string abspath)
{
	Path p(abspath);
	if (!p.isAbsolute()) {
		abspath = p.getAbsolute().path();
	}
	if (existsImport(abspath)) {
		return;
	}
	addHiddenImport_byPath(abspath);
}

//查找符号定义，从本空间中查找，也从Import/include中查找
std::shared_ptr<SymbolDefinition> SymbolSpace::findSymbolDefinitionByName_includeImports(std::string name)
{
	//CostUs cost;
	if (name == "Object") { //内置类型
		auto defObj = gocSymbolDefinitionClass_Object(this->symbolSpaceLoader);
		return defObj;
	}


	auto def = this->findSymbolDefinitionByName_exportedInThisSpace(name);
	//cost.stat("findSymbolDefinitionByName_exportedInThisSpace");
	if (def) {
		//cost.print("findSymbolDefinitionByName_includeImports");
		return def;
	}
	//从import中查找
	//TODO 考虑alias
	if (this->symbolSpaceLoader) {

		std::vector<std::vector<std::shared_ptr<Import>>*> importsList{ &imports, &hiddenImports };
		for (auto imps : importsList) {
			for (auto& imp : *imps) {
				auto impSpace = this->symbolSpaceLoader->load_baseOnSymbolSpace(this, imp.get());
				//cost.stat("load_baseOnSymbolSpace");
				if (impSpace) { //加载符号表成功
					auto impDef = impSpace->findSymbolDefinitionByName_exportedInThisSpace(name);
					if (impDef) {
						//cost.print("findSymbolDefinitionByName_includeImports");
						return impDef;
					}
				}
			}
		}
	}
	else {
		throw std::format("findSymbolDefinitionByName_includeImports :{}, {} error. no symbolSpaceLoader",
			path,
			name
		);
	}
	//cost.print("findSymbolDefinitionByName_includeImports null");
	return nullptr;
}


void SymbolDefinition::setHostSpace(SymbolSpace* space)
{
	this->hostSpace = space->shared_from_this();
	if (!space->symbolSpaceLoader) {
		throw std::format("setHostSpace error. space->symbolSpaceLoader is empty. path={}", space->path);
	}
	//if (!this->hostSpace->symbolSpaceLoader) {
	//	this->hostSpace->symbolSpaceLoader = space->symbolSpaceLoader;
	//}
}

std::string SymbolDefinition::toString()  {
	return std::format("Symbol({}, {}, {})",
		name, fullname, typeid(*this).name());
}

std::shared_ptr<SymbolSpace> SymbolSpaceLoader::load(std::string path)
{
	return std::shared_ptr<SymbolSpace>();
}

// [fromGlobalFilePath] 用来表示c 中的 #include <path>, 
std::string findTargetFilePath(std::string basepath, std::string path, bool fromGlobalIncludePath) {
	//导入路径的查找顺序

	/*
	1. 从basepath所在的目录
	2. 从-I
	3. 从C_INCLUDE_PATH/CPLUS_INCLUDE_PATH
	4. 内定路径
	*/
	// 如果指定了[fromGlobalIncludePath],则跳过1, 从2开始

	// 本身就是绝对路径
	if (path.empty()) {
		throw std::format("findTargetFilePath异常. basepath:{}, path:{}, fromGlobalIncludePath:{}", basepath, path, fromGlobalIncludePath);
	}
	auto c = path[0];
	auto isLetter = 
		c >= 'a' && c <= 'z'
		|| c >= 'A' && c <= 'Z';
	if (path.starts_with("/")
		||
		// windows的盘符
		path.size() > 1
		&& path[1] == ':' && isLetter
		
		) {
		return path;
	}

	//CostUs cost;
	if (!fromGlobalIncludePath) {
		auto p = Path(basepath);
		//cost.stat("Path");
		auto p2 = p.dirname();
		//cost.stat("dirname");
		auto p3 = p2.append(path);
		//cost.stat("append");
		auto p4 = p3.eliminateDotDir();
		//cost.stat("eliminateDotDir");
		//auto abspath = Path(basepath).dirname().append(path).eliminateDotDir().path();
		auto abspath = p4.path();
		//cost.stat("path");
		
		std::filesystem::path fsPath(abspath);
		//cost.stat("fsPath");
		//文件存在
		if (std::filesystem::exists(fsPath)) {
			//cost.stat("exists");
			//cost.print("findTargetFilePath");
			return abspath;
		}
	}

	// 2, 3, 4, 暂不实现
	//cost.print("findTargetFilePath null");
	return "";
}

std::shared_ptr<SymbolDefinitionClass> ast_findSymbolDefinitionClass_byTypeContext(OrcParser::TypeContext* ctx, std::shared_ptr<SymbolSpace> space)
{
	auto typeName = ast_getNakeTypeName_fromTypeContext(ctx);
	auto sym = space->findSymbolDefinitionByName_includeImports(typeName);
	auto def = std::dynamic_pointer_cast<SymbolDefinitionClass>(sym);
	return def;
}
std::shared_ptr<SymbolDefinitionClass> ast_findSymbolDefinitionClass_byTypeName(std::string typeName, std::shared_ptr<SymbolSpace> space)
{
	auto sym = space->findSymbolDefinitionByName_includeImports(typeName);
	auto def = std::dynamic_pointer_cast<SymbolDefinitionClass>(sym);
	return def;
}

//加载c头文件的符号表
std::shared_ptr<SymbolSpace> SymbolSpaceLoader::load_cHeader(std::string includeCode, std::string basepath, std::string headerpath, std::string absHeaderPath) {

	if (!headerpath.ends_with(".h")) {
		throw std::format("加载c文件符号表异常。 headerpath:{}", headerpath);
	}

	auto keyPath = absHeaderPath.empty() ? headerpath : absHeaderPath;
	auto md5Path = MD5(keyPath).toStr();
	auto symPath = std::format("_orc/{}_{}.symbols.json", Path(headerpath).basename(), md5Path);

	//是否需要生成符号文件
	bool needBuildSymbolFile = true;

	//只有当符号文件存在时，才需要进一步判断
	if (Path(symPath).exists()) {
		if (absHeaderPath.empty()) { //说明未明确找到头文件，也就没办法比较修改时间
			needBuildSymbolFile = false; //不需要生成
		}
		else {
			if (!Path(absHeaderPath).exists()) {
				throw std::format("头文件绝对路径无效:{}", absHeaderPath);
			}
			//比较文件修改时间，如果没有更新，就直接使用符号表文件，不用再生成

			auto symMtime = Path(symPath).mtimeMs();
			auto impPath = Path(absHeaderPath).dirname().path();
			auto srcMtime = Path(impPath).mtimeMs();


			//无更新，直接读符号表文件
			if (srcMtime <= symMtime) {
				needBuildSymbolFile = false; //不需要生成
			}
		}
	}
	//不用构建符号表，直接读原符号表文件
	if (!needBuildSymbolFile) {
		auto symText = FsUtil::read_all_text(symPath);
		auto jo = nlohmann::json::parse(symText);
		auto obj = parseJsonToObject(jo);
		auto space = std::dynamic_pointer_cast<SymbolSpace>(obj);
		if (space) {
			lib[keyPath] = space;//缓存起来
			return space;
		}
	}

	//auto it = lib.find(headerpath);
	//if (it != lib.end()) {
	//	auto ret = it->second;
	//	return ret;
	//}

	//需要构建 

	Path(symPath).dirname().mkdirs();

	//auto inc = std::format("#include \"{}\"", path);
	auto ret = SymbolSpace::buildSymbolSpace_forInclude(basepath, headerpath, includeCode, this->shared_from_this());
	//缓存起来
	lib[keyPath] = ret;

	//把符号表写文件
	auto jo = dumpJson(ret.get());
	auto joText = jo.dump(4);
	FsUtil::write_all_text(Path(symPath).getAbsolute().path(), joText);

	return ret;
}

std::string SymbolSpaceLoader::mkSymbolPath_forOrc(std::string orcAbsPath) {
	auto md5Path = MD5(orcAbsPath).toStr();
	auto symPath = std::format("_orc/{}_{}.symbols.json", Path(orcAbsPath).basename(), md5Path);
	return symPath;
}

void SymbolSpaceLoader::saveSymbolFile_forOrc(std::string orcAbsPath, SymbolSpace* space) {
	auto symPath = mkSymbolPath_forOrc(orcAbsPath);// std::format("_orc/{}_{}.symbols.json", md5Path, Path(absPath).basename());

	//把符号表写文件
	auto jo = dumpJson(space);
	auto joText = jo.dump(4);
	FsUtil::write_all_text(Path(symPath).getAbsolute().path(), joText);
}

//加载.orc文件的符号表
std::shared_ptr<SymbolSpace> SymbolSpaceLoader::load_orcModule(std::string absPath) {
	if (!absPath.ends_with(".orc")) {
		throw std::format("加载orc文件符号表异常。 absPath:{}", absPath);
	}

	//auto md5Path = MD5(absPath).toStr();
	auto symPath = mkSymbolPath_forOrc(absPath);// std::format("_orc/{}_{}.symbols.json", md5Path, Path(absPath).basename());

	//符号文件已存在
	if (Path(symPath).exists()) {
		auto symMtime = Path(symPath).mtimeMs();
		auto srcMtime = Path(absPath).mtimeMs();
		if (srcMtime <= symMtime) {
			//源文件无更新
			auto symText = FsUtil::read_all_text(symPath);
			auto jo = nlohmann::json::parse(symText);
			auto obj = parseJsonToObject(jo);
			auto space = std::dynamic_pointer_cast<SymbolSpace>(obj);
			if (space) {
				lib[absPath] = space->shared_from_this();
				return space;
			}
		}
	}

	//需要构建符号表

	Path(symPath).dirname().mkdirs();


	auto ret = SymbolSpace::buildSymbolSpace_forImport(absPath, this->shared_from_this());

	//把符号表写文件
	//auto jo = dumpJson(ret.get());
	//auto joText = jo.dump(4);
	//FsUtil::write_all_text(symPath, joText);
	saveSymbolFile_forOrc(absPath, ret.get());

	return ret;
}
std::shared_ptr<SymbolSpace> SymbolSpaceLoader::load_baseOnSymbolSpace(SymbolSpace* space, Import* imp)
{
	//CostUs cost;
	if (imp == NULL) {
		throw std::format("load_baseOnSymbolSpace参数异常, imp == NULL");
	}
	if (imp->path == "Object.orc") {
		auto objDef = gocSymbolDefinitionClass_Object(this->shared_from_this());
		return objDef->hostSpace;
	}

	//auto it = lib.find(path);
	//if (it != lib.end()) {
	//	auto ret = it->second;
	//	return ret;
	//}


	// include c header
	if (imp->isInclude) {

		// 计算头文件的绝对路径
		//auto absPath = this->findTargetFilePath(space->path, imp->path, imp->isIncludeFromGlobal());
		auto absPath = imp->gocAbspath(space->path);
		//cost.stat("c header findTargetFilePath");
		auto keyPath = absPath.empty() ? imp->path : absPath;

		//缓存中有，直接取
		auto it = lib.find(keyPath);
		if (it != lib.end()) {
			auto ret = it->second;
			//cost.print("load_baseOnSymbolSpace head");
			return ret;
		}

		auto includeCode = std::format("#include {}", imp->includeCode);
		auto ret = this->load_cHeader(
			includeCode,
			space->path,
			imp->path,
			absPath
		);
		//cost.stat("orc load_cHeader");

		//cost.print("load_baseOnSymbolSpace head");
		ret->symbolSpaceLoader = this->shared_from_this();
		return ret;
	}

	// include orc module
	{
		// path暂时只支持相对路径
		//auto absPath = this->findTargetFilePath(space->path, imp->path, false);
		auto absPath = imp->gocAbspath(space->path);
		//cost.stat("orc findTargetFilePath");
		if (absPath.empty()) {
			imp->gocAbspath(space->path);
			findTargetFilePath(space->path, imp->path, false);
			throw std::format("加载orc文件符号表异常。计算模块绝对路径异常basepath:{} path:{}, abspath:{}", space->path, imp->path, absPath);
		}

		//缓存中有，直接取
		auto it = lib.find(absPath);
		if (it != lib.end()) {
			auto ret = it->second;
			//cost.print("use cache");
			return ret;
		}

		auto ret = this->load_orcModule(absPath);
		//cost.stat("orc load_orcModule");

		//cost.print("load_baseOnSymbolSpace orc");
		ret->symbolSpaceLoader = this->shared_from_this();
		return ret;
	}

	//auto it = lib.find(path);
	//if (it != lib.end()) {
	//	auto ret = it->second;
	//	return ret;
	//}

	//auto md5Path = MD5(path).toStr();
	//auto symPath = std::format("_orc/{}_{}.symbols.json", md5Path, Path(path).basename());
	//Path(symPath).dirname().mkdirs();



	////加载c头文件
	//if (path.ends_with(".h")) { 
	//	auto comparePath = space->path;
	//	if (path.starts_with(".")) {//相对路径,可以计算
	//		comparePath = Path(Path(space->path).path() + "/" + path).normal().path();
	//	}

	//	//符号文件已存在
	//	//TODO 头文件判断要不要更新符号表的标准
	//	if (Path(symPath).exists()) {

	//		auto symMtime = Path(symPath).mtimeMs();
	//		auto impPath = Path(space->path).dirname().path();
	//		auto srcMtime = Path(impPath).mtimeMs();
	//		if (srcMtime <= symMtime) {
	//			//符号文件更新
	//			auto symText = FsUtil::read_all_text(symPath);
	//			auto jo = nlohmann::json::parse(symText);
	//			auto obj = parseJsonToObject(jo);
	//			auto space = std::dynamic_pointer_cast<SymbolSpace>(obj);
	//			if (space) {
	//				return space;
	//			}
	//		}
	//	}

	//	//Path p(path);

	//	auto inc = std::format("#include \"{}\"", path);
	//	auto ret = SymbolSpace::buildSymbolSpace_forInclude(space->path, path, inc);
	//	//缓存起来
	//	lib[path] = ret;

	//	//把符号表写文件
	//	auto jo = dumpJson(ret.get());
	//	auto joText = jo.dump(4);
	//	FsUtil::write_all_text(symPath, joText);

	//	return ret;
	//}
	//// 加载.orc模块
	//if (path.ends_with(".orc")) {


	//	//符号文件已存在
	//	if (Path(symPath).exists()) {
	//		auto symMtime = Path(symPath).mtimeMs();
	//		auto impPath = Path(space->path).dirname().path() + "/" + path;
	//		auto srcMtime = Path(impPath).mtimeMs();
	//		if (srcMtime <= symMtime) {
	//			//符号文件更新
	//			auto symText = FsUtil::read_all_text(symPath);
	//			auto jo = nlohmann::json::parse(symText);
	//			auto obj = parseJsonToObject(jo);
	//			auto space = std::dynamic_pointer_cast<SymbolSpace>(obj);
	//			if (space) {
	//				space->shared_from_this();
	//				return space;
	//			}
	//		}
	//	}



	//	auto ret = SymbolSpace::buildSymbolSpace_forImport(space->path, path, this->shared_from_this());
	//	//缓存起来
	//	lib[path] = ret;

	//	//把符号表写文件
	//	auto jo = dumpJson(ret.get());
	//	auto joText = jo.dump(4);
	//	FsUtil::write_all_text(symPath, joText);

	//	return ret;
	//}

	return nullptr;
}

std::shared_ptr<SymbolSpace>  SymbolSpace::buildSymbolSpace_forImport(
	std::string absPath,
	std::shared_ptr<SymbolSpaceLoader> loader)
{
	//auto impPath = Path(orcPath).dirname().path() + "/" + path;
	auto impPath = absPath;
	auto code = FsUtil::read_all_text(impPath);
	//printf("buildSymbolSpace_forImport %s code:\n%s\n\n", impPath.c_str(), code.c_str());
	printf("\tbuildSymbolSpace_forImport %s \n", impPath.c_str());


	std::shared_ptr<ANTLRInputStream> input;
	std::shared_ptr<OrcLexer> lexer;
	std::shared_ptr<CommonTokenStream> tokens;
	std::shared_ptr<OrcParser> parser;


	input = std::make_shared<ANTLRInputStream>(code);
	lexer = std::make_shared<OrcLexer>(input.get());
	tokens = std::make_shared<CommonTokenStream>(lexer.get());


	parser = std::make_shared<OrcParser>(tokens.get());


	auto tree = parser->program();
	auto space = std::make_shared<SymbolSpace>();

	//立即 缓存起来， 阻止循环import,导致死循环
	loader->lib[absPath] = space;

	space->symbolSpaceLoader = loader;
	space->path = impPath;
	space->buildSymbolSpace(impPath, tree, parser);
	return space;
}


void SymbolSpaceLoader::unload(std::string path)
{
	auto it = lib.find(path);
	if (it != lib.end()) {
		lib.erase(it);
	}
}

void SymbolDefinitionHasMembers::setHostSpace(SymbolSpace* space)
{
	if (hostSpace.get() == space) {
		return;
	}
	SymbolDefinition::setHostSpace(space);
	//成员也要更新
	for (auto& mem : members) {
		mem->setHostSpace(space);
	}
}

std::shared_ptr<SymbolDefinition> SymbolDefinitionHasMembers::findMemberByName(std::string name)
{
	/*if (name == "ctor" || name == "dtor") {
		auto def = std::make_shared<SymbolDefinitionMethod>();
		def->name = name;
		def->fullname = name;
		return def;
	}*/
	

	for (auto& member : members) {
		if (member->name == name) {
			member->setHostSpace(hostSpace.get());
			return member;
		}
	}
	return nullptr;
}

std::string SymbolTypeWithTypeName::getNakeTypeName()
{
	return typeName;
}

antlr4::tree::ParseTree* SymbolTypeWithTypeName::toAstType(AstMake *mk)
{
	auto type = mk->mkTerminal(OrcParser::Id, this->typeName);
	return type;
}

std::string SymbolType::getNakeTypeName()
{
	return std::string();
}

bool SymbolType::isAssignable(std::shared_ptr<SymbolType> rightType,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace)
{
	auto ok = this->getNakeTypeName() == rightType->getNakeTypeName();
	return ok;
}

/// <summary>
/// 内置的对象
/// </summary>
/// <returns></returns>
static std::shared_ptr<SymbolDefinitionClass> gocSymbolDefinitionClass_Object(
	std::shared_ptr<SymbolSpaceLoader> loader
) {
	static  std::shared_ptr<SymbolDefinitionClass> def = nullptr;
	if (def == nullptr) {
		auto space = std::make_shared<SymbolSpace>();
		space->path = "Object.orc";
		space->symbolSpaceLoader = loader;
		
		def = std::make_shared<SymbolDefinitionClass>();
		def->name = "Object";
		def->fullname = "Object";
		def->setHostSpace(space.get());

		{
			auto method = std::make_shared<SymbolDefinitionMethod>();
			method->name = "ctor";
			method->fullname = "ctor";
			def->members.push_back(method);
		}
		{
			auto method = std::make_shared<SymbolDefinitionMethod>();
			method->name = "dtor";
			method->fullname = "dtor";
			def->members.push_back(method);
		}
	}
	return def;
}
std::shared_ptr<SymbolDefinitionClass> SymbolDefinitionClass::findSuperSymbolDefinition()
{
	if (this->name == "Object") {
		return nullptr;
	}

	if (superName == "Object" || this->superName.empty()) { //默认继承Object
		return gocSymbolDefinitionClass_Object(this->hostSpace->symbolSpaceLoader);
	}

	auto super = this->hostSpace->findSymbolDefinitionByName_includeImports(this->superName);
	if (super) {
		return std::dynamic_pointer_cast<SymbolDefinitionClass>(super);
	}
	return nullptr;
}

std::shared_ptr<ClassMemberDto> SymbolDefinitionClass::findMemberByName_includeSupers(std::string name)
{
	auto member = findMemberByName(name);
	if (member) {
		auto dto = std::make_shared<ClassMemberDto>();
		dto->classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>( this->shared_from_this());
		dto->member = member;
		return dto;
	}
	auto superClass = findSuperSymbolDefinition();
	if (superClass) {
		auto superMember = superClass->findMemberByName_includeSupers(name);
		return superMember;
	}

	return nullptr;
}

std::shared_ptr<ClassMemberDto> SymbolDefinitionClass::findOriginalDefinedMemberByName_includeSupers(std::string name)
{
	auto superClass = findSuperSymbolDefinition();
	if (superClass) {
		auto superMember = superClass->findOriginalDefinedMemberByName_includeSupers(name);
		if (superMember) {
			return superMember;
		}
	}

	auto member = findMemberByName(name);
	if (member) {
		auto dto = std::make_shared<ClassMemberDto>();
		dto->classDef = std::dynamic_pointer_cast<SymbolDefinitionClass>(this->shared_from_this());
		dto->member = member;
		return dto;
	}
	return nullptr;
}

std::vector<std::shared_ptr<SymbolDefinition>> SymbolDefinitionClass::listAllMembers_includeSupers()
{
	std::vector<std::shared_ptr<SymbolDefinition>> ret;
	auto cur = this;
	std::unordered_set<std::string> hasSet;
	while (cur) {
		for (auto mem : cur->members) {
			if (hasSet.contains(mem->name)) {
				continue;
			}
			hasSet.insert(mem->name);
			ret.push_back(mem);
		}
		cur = cur->findSuperSymbolDefinition().get();
	}
	return ret;
}


bool SymbolDefinitionClass::hasField_typeIsRef_orPointer()
{
	SymbolDefinitionClass* curClass = this;
	while (curClass) {

		for (auto mem : curClass->members) {
			auto field = std::dynamic_pointer_cast<SymbolDefinitionClassField>(mem);
			if (field) {
				auto type = field->getType();

				auto pointerType = std::dynamic_pointer_cast<SymbolTypePointer>(type);
				if (pointerType) {
					return true;
				}

				auto refType = std::dynamic_pointer_cast<SymbolTypeRef>(type);
				if (refType) {
					return true;
				}
			}
		}
		auto superClass = curClass->findSuperSymbolDefinition();
		curClass = superClass ? superClass.get() : NULL;
	}
	return false;
}

bool SymbolDefinitionClass::hasField_typeIsRef()
{
	SymbolDefinitionClass* curClass = this;
	while (curClass) {

		for (auto mem : curClass->members) {
			auto field = std::dynamic_pointer_cast<SymbolDefinitionClassField>(mem);
			if (field) {
				auto type = field->getType();
				auto refType = std::dynamic_pointer_cast<SymbolTypeRef>(type);
				if (refType) {
					return true;
				}
			}
		}
		auto superClass = curClass->findSuperSymbolDefinition();
		curClass = superClass ? superClass.get() : NULL;
	}
	return false;
}

void SymbolDefinitionClass::autoDetecRefc()
{
	//手工标记的
	bool refcFlag = this->refc;
	if (!this->refc) {
		this->refc = !this->hasField_typeIsRef_orPointer();
	}
	printf("auto detect refc  name:%40s    refc:%d. flag:%d\n", this->fullname.c_str(), refc, refcFlag);
}

std::shared_ptr<SymbolType> SymbolDefinitionFunction::getReturnType()
{
	auto retType =this->type->returnType;
	return retType;
}

std::shared_ptr<SymbolType> SymbolDefinitionFunction::getType()
{
	return this->type;
}

std::shared_ptr<SymbolType> SymbolDefinitionVar::getType()
{
	return this->type;
}

std::shared_ptr<SymbolType> SymbolDefinitionTypedef::getType()
{
	return this->type;
}


OrcParser::FunctionPointerVarDeclarationContext* AstMake::functionPointerMember(
	OrcParser::TypeContext* retType, int pointerLevel, std::string memberName, bool createArgumentsDeclaration )
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::FunctionPointerVarDeclarationContext>((antlr4::ParserRuleContext*)NULL, 0);


	ins->insert(retType);
	for (int i = 0; i < pointerLevel; i ++) {
		ins->insert(this->mkTerminal(0, "*"));
	}
	ins->insert(this->Id(memberName));
	if (createArgumentsDeclaration) {
		ins->insert(this->argumentsDeclaration());
	}
	 
	return ins;
}

OrcParser::ArgumentDeclarationContext* AstMake::argDecl() {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ArgumentDeclarationContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}
OrcParser::ArgumentsDeclarationContext* AstMake::argumentsDeclaration()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ArgumentsDeclarationContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}
OrcParser::StatementContext* AstMake::statement()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::StatementContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}
OrcParser::ReturnStatementContext* AstMake::returnStatement()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ReturnStatementContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}
OrcParser::ArraySizeDeclarationContext* AstMake::arrayLength(int size)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ArraySizeDeclarationContext>((antlr4::ParserRuleContext*)NULL, 0);
	if (size >= 0) {
		auto sizeTerm = this->mkTerminal(OrcParser::DecimalLiteral, std::to_string(size));
		ins->insert(sizeTerm);
	}
	return ins;
}
OrcParser::BlockContext* AstMake::block()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::BlockContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}
OrcParser::EosContext* AstMake::eos()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::EosContext>((antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(this->mkTerminal(0, ";"));
	return ins;
}
OrcParser::ClassDefinitionContext* AstMake::mkClass(std::string name, std::string superName)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ClassDefinitionContext>((antlr4::ParserRuleContext*)NULL, 0);
	auto className = this->Id(name);
	ins->insert(className);
	if (!superName.empty()) {
		auto superNameId = this->Id(superName);
		ins->insert(superNameId);
	}
	auto block = tracker->createInstance<OrcParser::ClassDefinitionBlockContext>((antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(block);

	return ins;
}
OrcParser::ClassFieldDeclarationContext* AstMake::mkClassField(
	OrcParser::TypeContext* type, std::string name, OrcParser::SingleExpressionContext* init)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ClassFieldDeclarationContext>((antlr4::ParserRuleContext*)NULL, 0);

	ins->insert(type);
	ins->insert(this->Id(name));
	if (init) {
		auto rightPart = tracker->createInstance<OrcParser::AssignRightPartContext>((antlr4::ParserRuleContext*)NULL, 0);
		rightPart->insert(init);

		ins->insert(rightPart);
	}
	ins->insert(this->eos());

	return ins;
}
OrcParser::StructDefinitionContext* AstMake::mkStruct(std::string name)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::StructDefinitionContext>((antlr4::ParserRuleContext*)NULL, 0);
	auto structName = this->Id(name);
	ins->insert(structName);

	return ins;
}
OrcParser::StructMemberContext* AstMake::mkStructMember(
	OrcParser::TypeContext* type,
	std::string name)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::StructMemberContext>((antlr4::ParserRuleContext*)NULL, 0);

	ins->insert(type);
	ins->insert(this->Id(name));
	ins->insert(this->eos());

	return ins;
}
OrcParser::StructMemberContext* AstMake::mkStructMember_forFunctionPointerMember(

	OrcParser::FunctionPointerVarDeclarationContext* fn
)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::StructMemberContext>((antlr4::ParserRuleContext*)NULL, 0);

	ins->insert(fn);
	ins->insert(this->eos());

	return ins;
}
OrcParser::PrimitiveTypeContext* AstMake::primitiveType(std::string text) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::PrimitiveTypeContext>(
		(antlr4::ParserRuleContext*)NULL, 0);
	auto term = mkTerminal(0, text);
	ins->insert(term);
	return ins;
}
OrcParser::ClosureTypeContext* AstMake::closureType(OrcParser::TypeContext* retType, bool createArgumentsDeclaration) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ClosureTypeContext>(
		(antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(retType);
	if (createArgumentsDeclaration) {
		ins->insert(this->argumentsDeclaration());
	}
	return ins;
}
OrcParser::TypeContext* AstMake::type(antlr4::tree::ParseTree* kid) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::TypeContext>((antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(kid);
	return ins;
}
OrcParser::SingleExpressionContext* AstMake::singleExpression() {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::SingleExpressionContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}
OrcParser::CallExpressionContext* AstMake::callExpression() {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::CallExpressionContext>((OrcParser::SingleExpressionContext*)NULL);

	return ins;
}

OrcParser::CallExpressionContext* AstMake::callExpression_byFunctionName_withArguments(string fnName) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::CallExpressionContext>((OrcParser::SingleExpressionContext*)NULL);

	auto fnNameExpr = identifierExpression(fnName);
	ins->insert(fnNameExpr);

	auto arguments = this->arguments();
	ins->insert(arguments);

	return ins;
}
OrcParser::CastExpressionContext* AstMake::castExpression(OrcParser::TypeContext* type, OrcParser::SingleExpressionContext* expr) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::CastExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	ins->insert(type);
	ins->insert(expr);
	return ins;
}
OrcParser::ArgumentsContext* AstMake::arguments() {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ArgumentsContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}

OrcParser::AssignmentExpressionContext* AstMake::assignmentExpression()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::AssignmentExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	return ins;
}

OrcParser::MemberDotExpressionContext* AstMake::memberDotExpr(OrcParser::SingleExpressionContext* expr, std::string propName, std::string op)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::MemberDotExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	ins->insert(expr);
	ins->insert(this->mkTerminal(0, op));
	ins->insert(this->Id(propName));
	return ins;
}

OrcParser::ParenthesizedExpressionContext* AstMake::parenthesizedExpression(
	OrcParser::SingleExpressionContext* expr)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ParenthesizedExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	if (expr) {
		auto seq = expressionSequence();
		seq->insert(expr);
		ins->insert(seq);
	}
	return ins;
}
OrcParser::ExpressionSequenceContext* AstMake::expressionSequence()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::ExpressionSequenceContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}


OrcParser::VarDeclarationContext* AstMake::varDeclaration_nake() {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::VarDeclarationContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}
OrcParser::VarDeclarationContext* AstMake::varDeclaration(OrcParser::TypeContext* type, string varName, OrcParser::SingleExpressionContext* initExpr) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::VarDeclarationContext>((antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(type);
	ins->insert(this->Id(varName));
	if (initExpr) {
		ins->insert(initExpr);
	}
	return ins;
}
OrcParser::IdentifierExpressionContext* AstMake::identifierExpression(string varName) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::IdentifierExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	auto id = Id(varName);
	ins->insert(id);
	return ins;
}

OrcParser::LiteralExpressionContext* AstMake::nullLiteralExpression() {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::LiteralExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	ins->insert(literal_NullLiteral());
	return ins;
}

OrcParser::LiteralContext* AstMake::literal_NullLiteral() {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::LiteralContext>((antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(mkTerminal(OrcParser::NullLiteral, "null"));
	return ins;
}

OrcParser::LiteralExpressionContext* AstMake::intLiteralExpression(int number)
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::LiteralExpressionContext>((OrcParser::SingleExpressionContext*)NULL);


	auto intStr = std::format("{}", number);
	auto intLiteral = tracker->createInstance<OrcParser::LiteralContext>((antlr4::ParserRuleContext*)NULL, 0);
	intLiteral->insert(
		mkTerminal(
			OrcParser::DecimalLiteral,
			intStr)
	);

	ins->insert(intLiteral);
	return ins;
}

OrcParser::OrcParser::DerefExpressionContext* AstMake::deref(antlr4::tree::ParseTree* expr) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::DerefExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	ins->insert(expr);
	return ins;
}


OrcParser::OrcParser::GetAddressExpressionContext* AstMake::getAddress(antlr4::tree::ParseTree* expr) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::GetAddressExpressionContext>((OrcParser::SingleExpressionContext*)NULL);
	ins->insert(expr);
	return ins;
}
OrcParser::PointerContext* AstMake::pointer(antlr4::tree::ParseTree* type, int pointerLevel) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::PointerContext>((antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(type);
	for (int i = 0; i < pointerLevel; i++) {
		auto term = mkTerminal(0, "*");
		ins->insert(term);
	}
	return ins;
}
OrcParser::PointerContext* AstMake::pointerByTypeName(std::string typeName, int pointerLevel)
{
	auto id = this->Id(typeName);
	auto type = this->pointer(id, pointerLevel);
	return type;
}
OrcParser::RefContext* AstMake::refByTypeName(std::string typeName)
{
	auto id = this->Id(typeName);
	auto type = this->ref(id);
	return type;
}
OrcParser::RefContext* AstMake::ref(antlr4::tree::ParseTree* type ) {
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::RefContext>((antlr4::ParserRuleContext*)NULL, 0);
	ins->insert(type);
	return ins;
}
antlr4::tree::TerminalNode* AstMake::Id(string text) {
	return mkTerminal(OrcLexer::Id, text);
}

antlr4::tree::TerminalNode* AstMake::mkTerminal(int type, string text) {
	if (!tracker) {
		return NULL;
	}

	std::shared_ptr<Token> token = std::make_shared<CommonToken>(type, text);
	tokens.push_back(token);
	auto tn = tracker->createInstance<antlr4::tree::TerminalNodeImpl>(token.get());
	return tn;
}

antlr4::tree::TerminalNode* AstMake::mkStatic()
{
	auto ret = mkTerminal(OrcParser::Static, "static");
	return ret;
}

OrcParser::GlobalFunctionDefinitionContext* AstMake::globalFunctionDefinition()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::GlobalFunctionDefinitionContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}

OrcParser::FunctionDefinitionContext* AstMake::functionDefinition()
{
	if (!tracker) { return NULL; }
	auto ins = tracker->createInstance<OrcParser::FunctionDefinitionContext>((antlr4::ParserRuleContext*)NULL, 0);
	return ins;
}


antlr4::tree::ParseTree* SymbolTypePointer::toAstType(AstMake*mk)
{
	auto type = mk->mkTerminal(OrcParser::Id, this->typeName);
	auto ret = mk->pointer(
		type,
		this->pointerLevel
	);
	return ret;
}

bool SymbolTypePointer::is_nakeTypeName_isPrimitiveType()
{
	//暂不考虑unsigned 
	if (typeName == "unsignedchar" ||
		typeName == "unsignedshort" ||
		typeName == "unsignedint" ||
		typeName == "unsignedlong" ||
		typeName == "unsignedlonglong" ||
		typeName == "unsignedlong long" ||

		typeName == "bool" ||
		typeName == "char" ||
		typeName == "short" ||
		typeName == "int" ||
		typeName == "void" ||
		typeName == "long" ||
		typeName == "longlong" ||
		typeName == "long long" ||
		typeName == "float" ||
		typeName == "double"
		
		)
	{
		return true;
	}
	return false;
}

bool SymbolTypePointer::isAssignable(std::shared_ptr<SymbolType> rightType,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace
)
{
	//void*可以接受所有的指针
	auto isVoidStar = this->pointerLevel == 1 && this->getNakeTypeName() == "void";
	auto r = std::dynamic_pointer_cast<SymbolTypePointer>(rightType);
	if (r) {
		//void*可以接受所有的指针
		if (isVoidStar) {
			return true;
		}
		auto rIsVoidStar = r->pointerLevel == 1 && r->getNakeTypeName() == "void";
		if (rIsVoidStar) { //void*可以赋值给任意的指针
			return true;
		}

		if (r->pointerLevel == this->pointerLevel) {
			auto ret = ast_isAssignable_byClassName(this->getNakeTypeName(), r->getNakeTypeName(), leftSpace, rightSpace);
			return ret;
		}
	}
	{
		auto r = std::dynamic_pointer_cast<SymbolTypeRef>(rightType);
		if (r && this->pointerLevel == 1) {

			if (isVoidStar) {
				return true;
			}

			auto ret = ast_isAssignable_byClassName(this->getNakeTypeName(), r->getNakeTypeName(), leftSpace, rightSpace);
			return ret;
		}
	}
	{
		auto r = std::dynamic_pointer_cast<SymbolTypeArray>(rightType);
		if (r && this->pointerLevel == 1) {
			if (isVoidStar) {
				return true;
			}
			auto ret = ast_isAssignable_byClassName(this->getNakeTypeName(), r->getNakeTypeName(), leftSpace, rightSpace);
			return ret;
		}
	}
	return false;
}

antlr4::tree::ParseTree* SymbolTypeRef::toAstType(AstMake* mk)
{
	auto type = mk->mkTerminal(OrcParser::Id, this->typeName);
	auto ret = mk->ref(
		type
	);
	return ret;
}

antlr4::tree::ParseTree* SymbolTypePrimitiveType::toAstType(AstMake* mk)
{
	auto type = mk->primitiveType(this->typeName);
	return type;
}

bool SymbolTypePrimitiveType::isUnsigned()
{
	auto name = this->getNakeTypeName();
	auto idx = name.find("unsigned");
	return idx == 0;
}
std::string SymbolTypePrimitiveType::getOrcMetaTypeName()
{
	auto name = this->getNakeTypeName();
	auto ret = ast_getOrcMetaTypeName_byNakeTypeName(name);
	return ret;
}

bool SymbolTypePrimitiveType::isAssignable(std::shared_ptr<SymbolType> rightType,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace)
{
	{
		auto r = std::dynamic_pointer_cast<SymbolTypePrimitiveType>(rightType);
		if (r) {
			return true;
		}
		{
			auto r = std::dynamic_pointer_cast<SymbolTypeWithTypeName>(rightType);
			if (r) {
				if (isNakeTypeName_isPrimitiveType(r->getNakeTypeName())) {
					return true;
				}
			}
		}
	}
	return false;
}

std::string ast_getOrcMetaTypeName_byNakeTypeName(std::string name)
{
	auto idx = name.find("unsigned");
	if (idx == 0) {
		name = name.substr(8);
	}
	if (name == "bool") return "OrcMetaType_bool";
	if (name == "char") return "OrcMetaType_char";
	if (name == "short") return "OrcMetaType_short";
	if (name == "int") return "OrcMetaType_int";
	if (name == "long") return "OrcMetaType_long";
	if (name == "longlong") return "OrcMetaType_long_long";
	if (name == "float") return "OrcMetaType_float";
	if (name == "double") return "OrcMetaType_double";
	if (name == "void") return "OrcMetaType_void";

	throw std::format("Invalid primitive type name:{}", name);
}


antlr4::tree::ParseTree* SymbolTypeFunction::toAstType(AstMake* mk)
{
	//TODO 
	return nullptr;
}


OrcParser::FunctionPointerVarDeclarationContext* ast_createAstFunctionPointerVarDeclaration(
	AstMake* mk,
	std::shared_ptr<SymbolType> returnType,
	std::string varName,
	std::vector<std::shared_ptr<SymbolTypeArg>>& args,
	int pointerLevel
) {
	auto ctx = mk->functionPointerMember(
		mk->type(
			returnType->toAstType(mk)
		),
		pointerLevel, varName, true
	);
	auto argsDecl = ctx->argumentsDeclaration();
	for (auto& arg : args) {
		auto argDecl = mk->argDecl();
		argsDecl->insert(argDecl);
		auto argFn = std::dynamic_pointer_cast<SymbolTypeFunction>(arg->type);
		// 函数指针型的参数
		if (argFn) {
			auto astArgFn = ast_createAstFunctionPointerVarDeclaration(mk, 
				argFn->returnType,
				arg->name,
				argFn->args);
			argDecl->insert(astArgFn);
		}
		else {
			argDecl->insert(
				mk->type(arg->type->toAstType(mk))
			);
			argDecl->insert(mk->Id(arg->name));
		}
	}
	return ctx;
}

antlr4::tree::ParseTree* SymbolTypeClosure::toAstType(AstMake* mk)
{
	auto ret = mk->closureType(
		mk->type(
			this->returnType->toAstType(mk)
		), false
		);
	auto argsDecl = SymbolTypeArg::buildAstArgumentsDeclaration(args, mk);
	ret->insert(argsDecl);
	return ret;
}

string genCode(antlr4::tree::ParseTree* ctx, std::shared_ptr<SymbolSpace> space) {
	GenCodeVisitor  vi;
	vi.space = space;
	auto str = vi.visitReturnString(ctx);
	return str;
}



void ast_printTree(
	antlr4::tree::ParseTree* tree,
	OrcParser* parser)
{
	if (!gParser) {
		gParser = parser;
	}
	if (!parser) {
		parser = gParser;
	}
	if (!tree) {
		std::cout << "Parse Tree: is NULL" << std::endl;
		return;
	}
	auto s = tree->toStringTree(parser, true);

	std::cout << "Parse Tree: " << s << std::endl;
}
OrcParser::TypeContext* ast_cloneTypeContext(
	OrcParser::TypeContext* type,
	AstMake* mk
)
{
	auto symType = typeContext_toSymbolType(type);
	auto astType = symType->toAstType(mk);
	auto retType = mk->type(astType);
	return retType;
}

Meta* MetaLib::findMetaByObject(Object* obj)
{
	std::string key = typeid(*obj).name();
	auto ret = findMetaByKey(key);
	return ret;
}
Meta* MetaLib::findMetaByClassName(string name)
{

	if (lib.contains(name)) {
		return &lib[name];
	}
	return nullptr;
}

Meta* MetaLib::findMetaByKey(string key)
{

	if (keylib.contains(key)) {
		return &keylib[key];
	}
	return nullptr;
}

MetaLib* MetaLib::gocInstance()
{
	static MetaLib* metaLib = NULL;
	if (metaLib == NULL) {
		metaLib = new MetaLib();
	} 
	return metaLib;
}



void SymbolTypeWithTypeName::fromJson(nlohmann::json& jo) {
	typeName = json_getString(jo, "typeName");
};
void SymbolTypeWithTypeName::toJson(nlohmann::json& jo) {
	jo["typeName"] = typeName;
}
bool SymbolTypeWithTypeName::isAssignable(std::shared_ptr<SymbolType> rightType,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace)
{
	auto r = std::dynamic_pointer_cast<SymbolTypeWithTypeName>(rightType);
	if (r) {
		auto ok = this->getNakeTypeName() == r->getNakeTypeName();
		return ok;
	}
	return false;
}
std::string json_getString(nlohmann::json& jo, std::string key) {
	auto v = jo[key];
	if (v.is_string()) {
		return v.get<string>();
	}
	return "";
}
int json_getInt(nlohmann::json& jo, std::string key) {
	auto v = jo[key];
	if (v.is_boolean()) {
		auto b = v.get<bool>();
		return b ? 1 : 0;
	}
	if (v.is_number()) {
		return v.get<int>();
	}
	return 0;
}


void Symbol$registerMetas() {
	REGISTER_META(Symbol);
    REGISTER_META(SymbolDefinition);
	REGISTER_META(SymbolDefinitionClass);
	REGISTER_META(SymbolDefinitionClassField);
	REGISTER_META(SymbolDefinitionEnum);
	REGISTER_META(SymbolDefinitionEnumItem);
	REGISTER_META(SymbolDefinitionExtension);
	REGISTER_META(SymbolDefinitionFunction);
	REGISTER_META(SymbolDefinitionHasMembers);
	REGISTER_META(SymbolDefinitionMethod);
	REGISTER_META(SymbolDefinitionPrimitiveType);
	REGISTER_META(SymbolDefinitionStruct);
	REGISTER_META(SymbolDefinitionTypedef);
	REGISTER_META(SymbolDefinitionVar);
	//registerMeta<SymbolType);
	REGISTER_META(SymbolTypeFunction);
	REGISTER_META(SymbolTypeClosure);
	REGISTER_META(SymbolTypePointer);
	REGISTER_META(SymbolTypePrimitiveType);
	REGISTER_META(SymbolTypeRef);
	//registerMeta<SymbolTypeWithHostSpace);
	REGISTER_META(SymbolTypeWithTypeName);

	REGISTER_META(SymbolSpace);
	REGISTER_META(Import);
	REGISTER_META(SymbolTypeArg);
}

antlr4::tree::ParseTree* SymbolTypeArray::toAstType(AstMake* mk)
{
	auto tree = type->toAstType(mk);
	auto arrLen = mk->arrayLength(length);
	auto ctx = dynamic_cast<OrcRuleContext*>(tree);
	if (ctx) {
		ctx->insert(arrLen);
		return ctx;
	}
	else {
		auto err = std::format("SymbolTypeArray::toAstType failed. tree(=type->toAstType) is not typeof OrcRuleContext");
		throw err;
	}
	//auto type = mk->primitiveType(this->typeName);
	//return type;
	return nullptr;
}

std::string SymbolTypeArray::getNakeTypeName()
{
	if (this->type) {
		auto typeName = this->type->getNakeTypeName();
		return typeName;
	}
	return "";
}

bool SymbolTypeArray::isAssignable(std::shared_ptr<SymbolType> rightType,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace)
{
	{
		auto r = std::dynamic_pointer_cast<SymbolTypeArray>(rightType);
		if (r) {
			if (ast_isAssignable_byClassName(this->getNakeTypeName(), r->getNakeTypeName(), leftSpace, rightSpace)) {
				return true;
			}
		}
	}
	{
		auto r = std::dynamic_pointer_cast<SymbolTypePointer>(rightType);
		if (r && r->pointerLevel == 1) {
			if (ast_isAssignable_byClassName(this->getNakeTypeName(), r->getNakeTypeName(), leftSpace, rightSpace)) {
				return true;
			}
		}
	}
	return false;
}

std::vector<std::shared_ptr<SymbolTypeArg>> SymbolTypeArg::buildByAstArgumentsDeclaration(
	OrcParser::ArgumentsDeclarationContext* argsDecl
) {
	if (argsDecl == nullptr) {
		throw std::format("argsDecl为null");
	}

	std::vector<std::shared_ptr<SymbolTypeArg>> ret;
	//构建参数
	for (auto& argDecl : argsDecl->argumentDeclaration()) {
		auto arg = std::make_shared<SymbolTypeArg>();
		auto fnPointer = argDecl->functionPointerVarDeclaration();
		if (fnPointer) {
			arg->name = fnPointer->Id() ? fnPointer->Id()->getText() : "";
			arg->type = ast_createSymbolTypeFunction(
				fnPointer->type(),
				fnPointer->argumentsDeclaration()
			);
		}
		else {
			arg->name = argDecl->Id() ? argDecl->Id()->getText() : "";
			arg->type = typeContext_toSymbolType(argDecl->type());
		}
		ret.push_back(arg);
	}
	return ret;
}

std::shared_ptr<SymbolTypeFunction> ast_createSymbolTypeFunction(
	OrcParser::TypeContext* returnType,
	OrcParser::ArgumentsDeclarationContext* argumentsDeclaration
) {
	auto t = std::make_shared<SymbolTypeFunction>();
	t->returnType = typeContext_toSymbolType(returnType);
	//构建参数
	t->args = SymbolTypeArg::buildByAstArgumentsDeclaration(argumentsDeclaration);
	return t;
}

std::shared_ptr<SymbolTypePointer> SymbolTypeRef::toSymbolTypePointer() {
	auto ret = std::make_shared<SymbolTypePointer>();
	ret->typeName = this->typeName;
	ret->pointerLevel = 1;
	return ret;
}

bool SymbolTypeRef::isAssignable(std::shared_ptr<SymbolType> rightType,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace)
{
	{
		auto r = std::dynamic_pointer_cast<SymbolTypeRef>(rightType);
		if (r) {
			if (ast_isAssignable_byClassName(this->getNakeTypeName(), r->getNakeTypeName(), leftSpace, rightSpace)) {
				return true;
			}
		}
	}
	{
		auto r = std::dynamic_pointer_cast<SymbolTypePointer>(rightType);
		if (r && r->pointerLevel == 1) {
			if (ast_isAssignable_byClassName(this->getNakeTypeName(), r->getNakeTypeName(), leftSpace, rightSpace)) {
				return true;
			}
		}
	}
	return false;
}


std::string ast_mkFullname_byPrefix(std::string packageName, std::string name)
{
	if (packageName.empty()) {
		return name;
	}
	return packageName + "$" + name;
}



bool ast_isAncestorOf(antlr4::tree::ParseTree* ancestor, antlr4::tree::ParseTree* kid) {
	while (kid) {
		if (kid == ancestor) {
			return true;
		}
		kid = kid->parent;
	}
	return false;
}


std::string ast_closureType_genCode(OrcParser::ClosureTypeContext* closureType, 
	ReturnStringVisitor *vi,
	std::string varName,
	AstMake* mk)
{
	auto returnTypeCode = vi->visitReturnString(closureType->type());
	auto argsDecl = mk->argumentsDeclaration();
	//如果是引用
	if (closureType->type()->ref()) {
		auto outRef = mk->argDecl();
		argsDecl->insert(outRef, 0);
		outRef->addChild(
			mk->type(
				mk->pointerByTypeName(closureType->type()->ref()->Id()->getText(), 2)
			)
		);
		outRef->addChild(mk->Id("__outRef__"));
	}
	////添加self. 在TranslateVisitor中添加
	//{
	//	auto selfArg = mk->argDecl();
	//	argsDecl->addChild(selfArg);
	//	selfArg->addChild(
	//		mk->type(
	//			mk->pointer(
	//				mk->primitiveType("void")
	//			)
	//		)
	//	);
	//	selfArg->addChild(mk->Id("self"));
	//}

	//创建临时的argsDecl,用来附带self, __outRef__
	for (auto& argDecl : closureType->argumentsDeclaration()->argumentDeclaration()) {
		argsDecl->addChild(argDecl);
	}
	auto argsCode = vi->visitReturnString(argsDecl);
	auto code = std::format("{} (**{}){}"
		, returnTypeCode
		, varName
		, argsCode
	);
	return code;
}


OrcParser::ArgumentsDeclarationContext* SymbolTypeArg::buildAstArgumentsDeclaration(
	std::vector<std::shared_ptr<SymbolTypeArg>>& args,
	AstMake* mk
) {
	auto argsDecl = mk->argumentsDeclaration();
	for (auto& arg : args) {
		auto argDecl = mk->argDecl();
		argsDecl->insert(argDecl);

		{//函数指针类型
			auto symTypeFn = dynamic_cast<SymbolTypeFunction*>(arg->type.get());
			if (symTypeFn) {
				auto varDecl = ast_createAstFunctionPointerVarDeclaration(mk, symTypeFn->returnType, arg->name, symTypeFn->args);
				argDecl->insert(varDecl);
				continue;
			}
		}

		auto astType = arg->type->toAstType(mk);
		argDecl->insert(mk->type(astType));
		argDecl->insert(mk->Id(arg->name));
	}
	return argsDecl;
}
//表达式树中，是否有用到变量
bool ast_isVarNameUsedInExprSubtree(antlr4::tree::ParseTree* tree, std::string varName) {
	if (!tree) {
		return false;
	}
	{
		auto idExpr = dynamic_cast<OrcParser::IdentifierExpressionContext*>(tree);
		if (idExpr && idExpr->getText() == varName) {
			return true;
		}
	}

	for (auto& kid : tree->children) {
		auto used = ast_isVarNameUsedInExprSubtree(kid, varName);
		if (used) {
			return true;
		}
	}
	return false;
}
//是不是普通的访问表达式,不含副作用
// id 表达式， 普通的memberDot, memberIndex表达式, 字面量
bool ast_isPureAccessExpression(antlr4::tree::ParseTree *tree) {
	if (dynamic_cast<OrcParser::LiteralContext*>(tree)) {
		return true;
	}
	if (dynamic_cast<OrcParser::IdentifierExpressionContext*>(tree)) {
		return true;
	}
	if (dynamic_cast<OrcParser::ThisExpressionContext*>(tree)) {
		return true;
	}
	if (dynamic_cast<OrcParser::SuperExpressionContext*>(tree)) {
		return true;
	}
	// member dot
	{
		auto dot = dynamic_cast<OrcParser::MemberDotExpressionContext*>(tree);
		if (dot) {
			auto isObjExprPure = ast_isPureAccessExpression(dot->singleExpression());
			return isObjExprPure;
		}
	}
	// member index
	{
		auto dot = dynamic_cast<OrcParser::MemberIndexExpressionContext*>(tree);
		if (dot) {
			auto isObjExprPure = ast_isPureAccessExpression(dot->singleExpression(0));
			//对象表达式是纯的
			if (isObjExprPure) {
				//索引表达式也是纯的
				auto isIndexExprPure = dot->singleExpression(1);
				return isIndexExprPure;
			}
			return isObjExprPure;
		}
	}
	return false;
}


//判断子树中是否含有节点
bool ast_subtreeContainsNode(antlr4::tree::ParseTree* tree, antlr4::tree::ParseTree* dst) {
	if (!tree) {
		return false;
	}
	if (tree == dst) {
		return true;
	}
	for (auto& kid : tree->children) {
		bool yes = ast_subtreeContainsNode(kid, dst);
		if (yes) {
			return yes;
		}
	}
	return false;
}


//生成临时变量tmpReturn时，需要记录numberReturn,那就需要找到numberReturn的共同宿主
OrcRuleContext* ast_findHostAstNode_forNumberReturn(antlr4::tree::ParseTree*ctx) {

	{
		auto hostFn = ast_findAncestorByType<OrcParser::FunctionDefinitionContext>(ctx);
		if (hostFn) {
			return hostFn;
		}
	}
	{
		auto hostFn = ast_findAncestorByType<OrcParser::ClassDefinitionContext>(ctx);
		if (hostFn) {
			return hostFn;
		}
	}
	throw std::format("findHostAstNode_forNumberReturn fail");
	return NULL;
}
bool ast_hasTerminal_inChildren(antlr4::tree::ParseTree* tree, std::string text) {
	for (auto kid : tree->children) {
		auto term = dynamic_cast<antlr4::tree::TerminalNode*>(kid);
		if (term) {
			if (term->getText() == text) {
				return true;
			}

		}
	}
	return false;

}

std::string Import::gocAbspath(std::string orcAbspath)
{

	if (this->abspath.empty()) {
		abspath = findTargetFilePath(orcAbspath, this->path, this->isIncludeFromGlobal());
	}
	return abspath;
}

bool isNakeTypeName_isInt(std::string typeName) {
	return typeName == "bool" || typeName == "char" || typeName == "short" || typeName == "int" || typeName == "long" || typeName == "long long" || typeName == "longlong";
}

bool ast_isAssignable_byClassName(
	std::string leftName, std::string rightName,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace
)
{

	if (isNakeTypeName_isPrimitiveType(leftName) && isNakeTypeName_isPrimitiveType(rightName)) {
		/*if (leftName == rightName) {
			return true;
		}*/
		//基础数据类型有隐式转换
		return true;
	}
	if (leftName == "Vtable_Object" && rightName == leftName) {
		return true;
	}

	if (leftName == rightName) {
		return true;
	}

	std::shared_ptr< SymbolDefinitionClass> left = ast_findSymbolDefinitionClass_byTypeName(leftName, leftSpace);
	std::shared_ptr< SymbolDefinitionClass> right = ast_findSymbolDefinitionClass_byTypeName(rightName, rightSpace);
	while (left && right) {
		if (left->fullname == right->fullname) {
			return true;
		}
		right = right->findSuperSymbolDefinition();
	}

	return false;
}





void SymbolDefinition::setRangeByRuleContext(tree::ParseTree* ctx) {
	if (!ctx) {
		return;
	}
	auto rule = dynamic_cast<OrcRuleContext*>(ctx);
	if (rule) {
		auto start = rule->getStart();
		if (start) {
			range.start.line = start->getLine() - 1; // -1是跟vscode一致，从0开始算
			range.start.character = start->getCharPositionInLine() - 0;
		}
		auto end = rule->getStop();
		if (end) {
			range.end.line = end->getLine() - 1;
			range.end.character = end->getCharPositionInLine() - 0;
		}
	}

	{
		auto text = dynamic_cast<antlr4::tree::TerminalNode*>(ctx);
		if (text) {
			auto sym = text->getSymbol();
			if (sym) {
				range.start.line = sym->getLine() - 1;
				range.start.character = sym->getCharPositionInLine() - 0;

				range.end.line = sym->getLine() - 1;
				range.end.character = sym->getCharPositionInLine() + sym->getText().size() - 0;
			}
		}
	}
}