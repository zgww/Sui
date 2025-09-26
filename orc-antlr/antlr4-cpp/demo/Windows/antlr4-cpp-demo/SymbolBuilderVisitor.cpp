#include "SymbolBuilderVisitor.h"



void SymbolBuilderVisitor::init(std::string path) {
	space->path = path;
}
//后处理
void SymbolBuilderVisitor::postProcess() {
	for (auto& def : space->symbols) {
		def->setHostSpace(space.get());
		auto defClass = std::dynamic_pointer_cast<SymbolDefinitionClass>(def);
		if (defClass) {
			//自动检测refc
			defClass->autoDetecRefc();
		}
	}
}

std::any SymbolBuilderVisitor::visitPackageStatement(OrcParser::PackageStatementContext* n) {
	space->packageName = n->Id()->getText();
	//printf("找到包名:%s\n", space->packageName.c_str());
	return defaultResult();
}

std::any SymbolBuilderVisitor::visitImportStatement(OrcParser::ImportStatementContext* n) {
	//printf("找到import:%s\n", n->StringLiteral()->getText().c_str());

	auto imp = std::make_shared<Import>();
	imp->isAllImport = true;
	auto text = n->StringLiteral()->getText();
	imp->path = text.substr(1, text.size() - 2);
	imp->line = n->getStart()->getLine() - 1;

	imp->gocAbspath(space->path);

	space->imports.push_back(imp);

	return defaultResult();
}

std::any SymbolBuilderVisitor::visitIncludeStatement(OrcParser::IncludeStatementContext* n) {
	//printf("找到include:%s\n", n->includePathCharacters()->getText().c_str());

	auto imp = std::make_shared<Import>();
	imp->isInclude = true;
	auto text = n->includePathCharacters()->getText();
	imp->path = text.substr(1, text.size() - 2);
	imp->includeCode = text;

	space->imports.push_back(imp);

	return defaultResult();
}

std::any SymbolBuilderVisitor::visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* n) {

	//printf("找到扩展的全名:%s\n", n->Id()->getText().c_str());

	auto def = std::make_shared<SymbolDefinitionExtension>();
	def->name = n->Id()->getText();
	def->fullname = ast_mkFullname_byPrefix(space->packageName, def->name);

	def->setRangeByRuleContext(n);


	space->symbols.push_back(def);

	curHost = def;
	auto ret = visitChildren(n);
	curHost = NULL;
	return ret;
}
std::any SymbolBuilderVisitor::visitClassDefinition(OrcParser::ClassDefinitionContext* n) {

	auto def = std::make_shared<SymbolDefinitionClass>();
	def->name = n->Id(0)->getText();
	//有父类
	if (n->Id(1)) {
		def->superName = n->Id(1)->getText();
	}
	if (n->Refc()) {
		def->refc = true;
	}
	def->fullname = ast_mkFullname_byPrefix(space->packageName, def->name);
	def->setRangeByRuleContext(n->Id(0));
	//printf("找到类的全名:%s =>%s\n", n->Id(0)->getText().c_str(), def->fullname.c_str());
	space->symbols.push_back(def);

	curHost = def;
	auto ret = visitChildren(n);
	curHost = NULL;
	return ret;
}

std::any SymbolBuilderVisitor::visitClassFieldDeclaration(OrcParser::ClassFieldDeclarationContext* n) {

	if (n->Id()) {
		//printf("找到类字段声明的全名:%s \n", n->Id()->getText().c_str());
		auto def = std::make_shared<SymbolDefinitionClassField>();
		def->type = classFieldDeclaration_typeContext_toSymbolType (n);
		def->name = n->Id()->getText();
		def->fullname = def->name;
		def->setRangeByRuleContext(n->Id());
		curHost->members.push_back(def);

		return defaultResult();
	}

	//函数指针型字段 
	auto fn = n->functionPointerVarDeclaration();
	if (fn) {
		//printf("找到类字段(函数指针类型)声明的全名:%s \n", fn->Id() ? fn->Id()->getText().c_str():"(null)");
		auto def = std::make_shared<SymbolDefinitionClassField>();

		def->type = createSymbolType_fromFunctionPointerVarDeclaration(fn);
		def->name = fn->Id() ? fn->Id()->getText() : "";

		def->setRangeByRuleContext(fn);

		curHost->members.push_back(def);
		return defaultResult();
	}



	return defaultResult();
}


std::any SymbolBuilderVisitor::visitMethodDeclaration(OrcParser::MethodDeclarationContext* n) {


	auto fn = n->functionDefinition();
	if (fn) {

		auto def = std::make_shared<SymbolDefinitionMethod>();
		def->type = ast_createSymbolTypeFunction(fn->type(), fn->argumentsDeclaration());
		//def->setHostSpace(space.get());
		def->name = fn->Id()->getText();
		def->setRangeByRuleContext(fn->Id());
		def->fullname = curHost->fullname + "$" + def->name;
		//printf("找到类方法声明的全名:%s => %s\n", fn->Id()->getText().c_str(), def->fullname.c_str());
		curHost->members.push_back(def);
	}

	{ //外部函数声明
		auto fn = n->externFunctionDeclaration();
		if (fn) {
			//printf("找到全局外部函数声明的全名:%s isStatic:%d\n", fn->Id()->getText().c_str());

			auto def = std::make_shared<SymbolDefinitionMethod>();
			//def->setHostSpace(space.get());
			def->type = ast_createSymbolTypeFunction(fn->type(), fn->argumentsDeclaration());
			def->name = fn->Id()->getText();
			def->setRangeByRuleContext(fn->Id());
			def->fullname = curHost->fullname + "$" + def->name;
			curHost->members.push_back(def);

			return defaultResult();
		}
	}

	return defaultResult();
}



std::any SymbolBuilderVisitor::visitStructDefinition(OrcParser::StructDefinitionContext* n) {

	auto def = std::make_shared<SymbolDefinitionStruct>();
	def->name = n->Id()->getText();
	def->setRangeByRuleContext(n->Id());
	def->fullname = ast_mkFullname_byPrefix(space->packageName, def->name);
	space->symbols.push_back(def);

	//printf("找到结构体的全名:%s %s\n", n->Id()->getText().c_str(), def->fullname.c_str());

	curHost = def;
	auto ret = visitChildren(n);
	curHost = NULL;
	return ret;
}


std::any SymbolBuilderVisitor::visitStructMember(OrcParser::StructMemberContext* n) {
	if (n->Id()) {
		//printf("找到结构字段声明的全名:%s \n", n->Id()->getText().c_str());

		auto def = std::make_shared<SymbolDefinitionClassField>();

		def->type = structMember_typeContext_toSymbolType(n);
		def->name = n->Id()->getText();
		def->setRangeByRuleContext(n->Id());
		curHost->members.push_back(def);

		return defaultResult();
	}
	auto fn = n->functionPointerVarDeclaration();
	if (fn) {
		auto def = std::make_shared<SymbolDefinitionClassField>();

		def->type = createSymbolType_fromFunctionPointerVarDeclaration(fn);
		def->name = fn->Id() ? fn->Id()->getText() : "";
		def->setRangeByRuleContext(fn->Id());
		curHost->members.push_back(def);
		return defaultResult();
	}

	return defaultResult();
}
std::any SymbolBuilderVisitor::visitEnumDefinition(OrcParser::EnumDefinitionContext* n) {
	//printf("找到枚举的全名:%s\n", n->Id()->getText().c_str());

	auto def = std::make_shared<SymbolDefinitionEnum>();
	def->name = n->Id()->getText();
	def->setRangeByRuleContext(n->Id());
	def->fullname = ast_mkFullname_byPrefix(space->packageName, def->name);
	space->symbols.push_back(def);

	return visitChildren(n);
}


std::any SymbolBuilderVisitor::visitEnumItem(OrcParser::EnumItemContext* n) {
	//printf("找到枚举项的全名:%s\n", n->Id()->getText().c_str());


	auto enumCtx = ast_findAncestorByType<OrcParser::EnumDefinitionContext>(n);

	auto type = std::make_shared<SymbolTypeWithTypeName>();
	type->typeName = enumCtx->Id()->getText();


	auto def = std::make_shared<SymbolDefinitionEnumItem>();
	def->name = n->Id()->getText();
	def->setRangeByRuleContext(n->Id());
	def->fullname = ast_mkFullname_byPrefix(space->packageName, def->name);
	def->type = type;
	space->symbols.push_back(def);
	return defaultResult();
}
//不进入，加快解析
std::any SymbolBuilderVisitor::visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* n) {
	bool isStatic = n->Static() != NULL; //是否静态
	{ //函数定义
		auto fn = n->functionDefinition();
		if (fn) {

			auto typeFn = ast_createSymbolTypeFunction(
				fn->type(), fn->argumentsDeclaration()
			);
			//auto typeFn = std::make_shared<SymbolTypeFunction>();
			//typeFn->returnType = typeContext_toSymbolType(fn->type());

			auto def = std::make_shared<SymbolDefinitionFunction>();
			def->type = typeFn;
			def->name = fn->Id()->getText();
			def->setRangeByRuleContext(fn->Id());
			def->fullname = isStatic ? def->name : ast_mkFullname_byPrefix(space->packageName, def->name);
			space->symbols.push_back(def);
			//printf("找到全局函数定义的全名:%s =>%s static=%d\n", fn->Id()->getText().c_str(), def->fullname.c_str(), isStatic);


			return defaultResult();
		}
	}

	{ //外部函数声明
		auto fn = n->externFunctionDeclaration();
		if (fn) {
			//printf("找到全局外部函数声明的全名:%s isStatic:%d\n", fn->Id()->getText().c_str(), isStatic);


			auto typeFn = ast_createSymbolTypeFunction(
				fn->type(), fn->argumentsDeclaration()
			);
			/*auto typeFn = std::make_shared<SymbolTypeFunction>();
			typeFn->returnType = typeContext_toSymbolType(fn->type());*/

			auto def = std::make_shared<SymbolDefinitionFunction>();

			def->type = typeFn;
			def->name = fn->Id()->getText();
			def->setRangeByRuleContext(fn->Id());
			def->fullname = ast_mkFullname_byPrefix(space->packageName, def->name);
			space->symbols.push_back(def);


			return defaultResult();
		}
	}
}

//不进入，加快解析
std::any SymbolBuilderVisitor::visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* n) {
	bool isStatic = n->varDeclaration()->Static() != NULL; //是否静态
	auto var = n->varDeclaration();
	if (var) {


		auto def = std::make_shared<SymbolDefinitionVar>();
		def->type = typeContext_toSymbolType(var->type());
		def->name = var->Id()->getText();
		def->setRangeByRuleContext(var->Id());
		def->fullname =
			isStatic ? def->name :
			ast_mkFullname_byPrefix(space->packageName, def->name);
		space->symbols.push_back(def);

		//printf("找到全局变量声明的全名:%s =>%s static=%d\n", var->Id()->getText().c_str(), def->fullname.c_str(), isStatic);


		return defaultResult();
	}
}


//不进入，加快解析
std::any SymbolBuilderVisitor::visitVarDeclaration(OrcParser::VarDeclarationContext* context) {
	return defaultResult();
}
