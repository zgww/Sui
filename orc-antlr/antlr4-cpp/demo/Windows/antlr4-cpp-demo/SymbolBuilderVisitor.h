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
#include "./TypeCheckerVisitor.h"


#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using namespace antlr4;
using string = std::string;

//符号表：类、枚举、结构体、扩展、全局变量、全局函数,静态全局变量，静态全局函数
//用来构建符号的
class SymbolBuilderVisitor : public OrcBaseVisitor {
public:
	std::shared_ptr<SymbolSpace> space = std::make_shared<SymbolSpace>();
	std::shared_ptr<SymbolDefinitionHasMembers> curHost = nullptr;

	void init(std::string path);

	//后处理
	void postProcess();

	virtual std::any visitPackageStatement(OrcParser::PackageStatementContext* n) override;
	virtual std::any visitImportStatement(OrcParser::ImportStatementContext* n) override;
	virtual std::any visitIncludeStatement(OrcParser::IncludeStatementContext* n) override;

	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* n) override;
	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* n) override;
	virtual std::any visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* n) override;

	virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext* n) override;

	virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext* n) override;


	virtual std::any visitStructMember(OrcParser::StructMemberContext* n) override;
	virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext* n) override;

	virtual std::any visitEnumItem(OrcParser::EnumItemContext* n) override;
	//不进入，加快解析
	virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* n) override;

	//不进入，加快解析
	virtual std::any visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* n) override;


	//不进入，加快解析
	virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext* context) override;

};
