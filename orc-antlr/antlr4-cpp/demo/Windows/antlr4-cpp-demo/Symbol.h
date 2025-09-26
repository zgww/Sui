// Generated from Orc.g4 by ANTLR 4.13.2

#pragma once


#include <typeinfo>
#include "OrcParserBase.h"

#include "antlr4-runtime.h"
#include "OrcParser.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <format>
#include <functional>
#include "Closure.h"

#include "json.hpp"
#include "./ReturnStringVisitor.h"

#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using string = std::string;

//符号/符号表

class SymbolSpace;

struct Position {
	int line;
	int character;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Position, line, character);
};
struct Range {
	Position start;
	Position end;

	void set(int sline, int schar, int eline, int echar) {
		start.line = sline;
		start.character = schar;
		end.line = eline;
		end.character = echar;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Range, start, end);
};


class AstMake {
public:
	antlr4::tree::ParseTreeTracker* tracker;


	OrcParser::ClassDefinitionContext* mkClass(std::string name, std::string superName = "");
	OrcParser::ClassFieldDeclarationContext* mkClassField(
		OrcParser::TypeContext* type,
		std::string name,
		OrcParser::SingleExpressionContext* init
	);

	OrcParser::StructDefinitionContext* mkStruct(std::string name);
	OrcParser::StructMemberContext* mkStructMember(
		OrcParser::TypeContext* type,
		std::string name
	);
	OrcParser::StructMemberContext* mkStructMember_forFunctionPointerMember(
		OrcParser::FunctionPointerVarDeclarationContext* fn
	);



	OrcParser::FunctionPointerVarDeclarationContext* functionPointerMember(OrcParser::TypeContext *retType, int pointLevel, std::string memberName, bool createArgumentsDeclaration=true);

	OrcParser::ArgumentDeclarationContext* argDecl();
	OrcParser::ArgumentsDeclarationContext* argumentsDeclaration();
	OrcParser::StatementContext* statement();
	OrcParser::ReturnStatementContext* returnStatement();
	OrcParser::ArraySizeDeclarationContext* arrayLength(int size=-1);
	OrcParser::BlockContext* block();


	OrcParser::EosContext* eos();
	
	
	
	
	OrcParser::PrimitiveTypeContext* primitiveType(std::string text);
	OrcParser::ClosureTypeContext* closureType(OrcParser::TypeContext* retType,  bool createArgumentsDeclaration = true);
	OrcParser::TypeContext* type(antlr4::tree::ParseTree* kid);
	OrcParser::SingleExpressionContext* singleExpression();
	OrcParser::CallExpressionContext* callExpression();

	OrcParser::CallExpressionContext* callExpression_byFunctionName_withArguments(string fnName);
	OrcParser::CastExpressionContext* castExpression(OrcParser::TypeContext* type, OrcParser::SingleExpressionContext* expr);
	OrcParser::ArgumentsContext* arguments();
	OrcParser::AssignmentExpressionContext* assignmentExpression();
	OrcParser::MemberDotExpressionContext* memberDotExpr(OrcParser::SingleExpressionContext *expr, std::string propName, std::string op=".");

	OrcParser::ParenthesizedExpressionContext* parenthesizedExpression(OrcParser::SingleExpressionContext* expr=NULL);
	OrcParser::ExpressionSequenceContext* expressionSequence();

	OrcParser::VarDeclarationContext* varDeclaration(OrcParser::TypeContext* type, string varName, OrcParser::SingleExpressionContext* initExpr);

	OrcParser::VarDeclarationContext* varDeclaration_nake();

	
	
	OrcParser::IdentifierExpressionContext* identifierExpression(string varName);

	OrcParser::LiteralExpressionContext* nullLiteralExpression();


	OrcParser::LiteralContext* literal_NullLiteral();


	OrcParser::LiteralExpressionContext* intLiteralExpression(int number);


	OrcParser::OrcParser::DerefExpressionContext* deref(antlr4::tree::ParseTree* expr);
	OrcParser::OrcParser::GetAddressExpressionContext* getAddress(antlr4::tree::ParseTree* expr);
	OrcParser::PointerContext* pointer(antlr4::tree::ParseTree* type, int pointerLevel = 1);
	OrcParser::PointerContext* pointerByTypeName(std::string typeName, int pointerLevel = 1);

	OrcParser::RefContext* ref(antlr4::tree::ParseTree* type);

	OrcParser::RefContext* refByTypeName(std::string typeName);

	antlr4::tree::TerminalNode* Id(string text);
	antlr4::tree::TerminalNode* mkTerminal(int type, string text);
	antlr4::tree::TerminalNode* mkStatic();

	std::vector<std::shared_ptr<antlr4::Token>> tokens;



	OrcParser::GlobalFunctionDefinitionContext* globalFunctionDefinition();
	OrcParser::FunctionDefinitionContext* functionDefinition();
};



class Object;


//只遍历 根规则 
class  OnlyRootsVisitor : public ReturnStringVisitor {
public:

	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) override;
	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override;
	virtual std::any visitStructDefinition(OrcParser::StructDefinitionContext* context) override;

	//不进入，加快解析
	virtual std::any visitGlobalFunctionDefinition(OrcParser::GlobalFunctionDefinitionContext* context) override;

	//不进入，加快解析
	virtual std::any visitGlobalVarDeclaration(OrcParser::GlobalVarDeclarationContext* context) override;

	//不进入，加快解析
	virtual std::any visitEnumDefinition(OrcParser::EnumDefinitionContext* ctx) override;

	//不进入，加快解析
	virtual std::any visitVarDeclaration(OrcParser::VarDeclarationContext* context) override;
};
//添加self参数
class  AddSelfArgumentVisitor : public OnlyRootsVisitor {
public:
	//需要初始化
	AstMake* mk = NULL;

	OrcParser::ClassDefinitionContext* curClass = NULL;
	OrcParser::ExtensionDefinitionContext* curExtension = NULL;
	virtual std::any visitClassDefinition(OrcParser::ClassDefinitionContext* ctx) override;
	virtual std::any visitExtensionDefinition(OrcParser::ExtensionDefinitionContext* ctx) override;
	virtual std::any visitMethodDeclaration(OrcParser::MethodDeclarationContext* ctx) override;
};

// 注册元数据。 用来序列化反序列化的
class Meta {
public:
	std::string key;
	std::string name;
	std::function<std::shared_ptr<Object >()> createObject;
};
class MetaLib {
public:
	std::unordered_map<std::string, Meta> lib;
	std::unordered_map<std::string, Meta> keylib;

	Meta* findMetaByObject(Object* obj);
	Meta* findMetaByClassName(std::string name);
	Meta* findMetaByKey(std::string key);
	static MetaLib* gocInstance();
};
template <class T>
bool registerMeta(std::string name) {
	auto lib = MetaLib::gocInstance();
	std::string key = typeid(T).name();
	if (lib->lib.contains(name)) {
		return false;
	}
	Meta meta;
	meta.key = key;
	meta.name = name;
	meta.createObject = []()->std::shared_ptr<Object> {
		//return new T();
		return std::dynamic_pointer_cast<Object>(std::make_shared<T>());
	};
	lib->lib[name] = meta;
	lib->keylib[key] = meta;
	return true;
}
#define REGISTER_META(CLASSNAME) registerMeta<CLASSNAME>(#CLASSNAME)
nlohmann::json dumpJson(Object* obj);
std::shared_ptr<Object> parseJsonToObject(nlohmann::json& jo);


template<class T>
std::shared_ptr<T> parseJsonToT(nlohmann::json& jo) {
	auto obj = parseJsonToObject(jo);
	if (obj != nullptr) {
		auto ret = std::dynamic_pointer_cast<T>(obj);
		return ret;
	}
	return nullptr;
}

template<class T>
void parseJsonToObjectArray(nlohmann::json& jo, std::vector<std::shared_ptr<T>> &ret) {
	ret.clear();
	if (!jo.is_array()) {
		return ;
	}
	for (int i = 0; i < jo.size(); i++) {
		auto& kid = jo[i];
		auto obj = parseJsonToObject(kid);
		auto targetObj = std::dynamic_pointer_cast<T>(obj);
		if (targetObj != nullptr) {
			ret.push_back(targetObj);
		}
	}
}
template<class T>
std::vector<std::shared_ptr<T>> parseJsonReturnObjectArray(nlohmann::json& jo) {
	std::vector<std::shared_ptr<T>> ret;
	if (!jo.is_array()) {
		return ret;
	}
	for (int i = 0; i < jo.size(); i++) {
		auto& kid = jo[i];
		auto obj = parseJsonToObject(kid);
		auto targetObj = std::dynamic_pointer_cast<T>(obj);
		if (targetObj != nullptr) {
			ret.push_back(targetObj);
		}
	}
	return ret;
}

template<typename T>
nlohmann::json dumpJsonAsObjectArray(std::vector<std::shared_ptr<T>> vec) {
	nlohmann::json ret = nlohmann::json::array();
	for (int i = 0; i < vec.size(); i++) {
		auto& ele = vec[i];
		auto eleJo = dumpJson(ele.get());
		ret.push_back(eleJo);
	}
	return ret;
}


std::string json_getString(nlohmann::json& jo, std::string key);
int json_getInt(nlohmann::json& jo, std::string key);

class Object {
public:
	virtual void fromJson(nlohmann::json& jo) {};
	virtual void toJson(nlohmann::json& jo) {
	};
};

//符号类型
class SymbolType : public Object{
public:
	virtual std::string getNakeTypeName();
	//symbolType转AstType
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) = 0;

	virtual std::string toString() { return getNakeTypeName(); };

	virtual bool isAssignable(
		std::shared_ptr<SymbolType> rightType,
		std::shared_ptr<SymbolSpace> leftSpace,
		std::shared_ptr<SymbolSpace> rightSpace
	);
};

class SymbolTypeWithTypeName : public SymbolType {
public:
	std::string typeName;

	virtual std::string getNakeTypeName() override;
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) override;

	virtual void fromJson(nlohmann::json& jo);
	virtual void toJson(nlohmann::json& jo);

	virtual bool isAssignable(
		std::shared_ptr<SymbolType> rightType,
		std::shared_ptr<SymbolSpace> leftSpace,
		std::shared_ptr<SymbolSpace> rightSpace
	) override;
};
class SymbolTypePointer : public SymbolTypeWithTypeName {
public:
	int pointerLevel = 1; //几级指针
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) override;

	virtual std::string toString() { 
		auto s = getNakeTypeName();
		for (int i = 0; i < pointerLevel; i++) {
			s += "*";
		}
		return s;
	};

	virtual void fromJson(nlohmann::json& jo) {
		SymbolTypeWithTypeName::fromJson(jo);
		pointerLevel = json_getInt(jo, "pointerLevel");
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolTypeWithTypeName::toJson(jo);
		jo["pointerLevel"] = pointerLevel;
	}
	virtual bool is_nakeTypeName_isPrimitiveType();


	virtual bool isAssignable(
		std::shared_ptr<SymbolType> rightType,
		std::shared_ptr<SymbolSpace> leftSpace,
		std::shared_ptr<SymbolSpace> rightSpace
	) override;
};

class SymbolTypeArray : public SymbolType {
public:
	std::shared_ptr<SymbolType> type = nullptr;
	int length = -1; //数组长度，-1表示未指定
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) override;

	virtual std::string getNakeTypeName() override;

	virtual std::string toString() {
		auto s = getNakeTypeName() + "[]";
		return s;
	};


	virtual void fromJson(nlohmann::json& jo) {
		SymbolType::fromJson(jo);
		length = json_getInt(jo, "length");
		type = parseJsonToT<SymbolType>(jo["type"]);
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolType::toJson(jo);
		jo["length"] = length;
		jo["type"] = dumpJson(type.get());
	}
	virtual bool isAssignable(
		std::shared_ptr<SymbolType> rightType,
		std::shared_ptr<SymbolSpace> leftSpace,
		std::shared_ptr<SymbolSpace> rightSpace
	) override;
};
class SymbolTypeRef : public SymbolTypeWithTypeName {
public:
	bool isWeak = false; //用于closureType. 表示，不需要为此生成urgc的设置代码.一般用于临时变量暂存用的
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) override;
	virtual std::shared_ptr<SymbolTypePointer> toSymbolTypePointer() ;

	virtual std::string toString() {
		auto s = getNakeTypeName() + "@";
		return s;
	};
	virtual bool isAssignable(
		std::shared_ptr<SymbolType> rightType,
		std::shared_ptr<SymbolSpace> leftSpace,
		std::shared_ptr<SymbolSpace> rightSpace
	) override;
};
class SymbolTypePrimitiveType : public SymbolTypeWithTypeName {
public:
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) override;
	bool isUnsigned();

	std::string getOrcMetaTypeName();
	virtual bool isAssignable(
		std::shared_ptr<SymbolType> rightType,
		std::shared_ptr<SymbolSpace> leftSpace,
		std::shared_ptr<SymbolSpace> rightSpace
	) override;
};

std::string ast_getOrcMetaTypeName_byNakeTypeName(std::string);

class SymbolTypeArg: public Object {
public:
	std::shared_ptr<SymbolType> type = nullptr;
	std::string name;

	virtual void fromJson(nlohmann::json& jo) {
		Object::fromJson(jo);
		type = parseJsonToT<SymbolType>(jo["type"]);
		name = json_getString(jo, "name");
	}
	virtual void toJson(nlohmann::json& jo) {
		Object::toJson(jo);
		jo["type"] = dumpJson(type.get());
		jo["name"] = name;
	}
	virtual std::string toString() {
		return std::format("{} {}",
			type ? type->toString() : std::string(""),
			name
		);
	}
	static std::vector<std::shared_ptr<SymbolTypeArg>> buildByAstArgumentsDeclaration(
		OrcParser::ArgumentsDeclarationContext *argsDecl
	);

	static OrcParser::ArgumentsDeclarationContext* buildAstArgumentsDeclaration(
		std::vector<std::shared_ptr<SymbolTypeArg>> &args,
		AstMake *mk
	);
};
class SymbolTypeFunction : public SymbolTypeWithTypeName {
public:
	std::shared_ptr<SymbolType> returnType = nullptr;
	std::vector<std::shared_ptr<SymbolTypeArg>> args;
	//std::vector<std::shared_ptr<SymbolType>> argTypes;
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) override;


	virtual std::string toString() {
		auto argsStr = std::string("");
		for (auto arg : args) {
			argsStr += arg->toString();
			if (args.back() != arg) {
				argsStr += ", ";
			}
		}

		auto s = std::format("{} (*) ({})", returnType ? returnType->toString() : std::string(""), argsStr
		);
		return s;
	};

	virtual void fromJson(nlohmann::json& jo) {
		SymbolTypeWithTypeName::fromJson(jo);
		returnType = parseJsonToT<SymbolType>(jo["returnType"]);
		parseJsonToObjectArray<SymbolTypeArg>(jo["args"], args);
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolTypeWithTypeName::toJson(jo);
		jo["returnType"] = dumpJson(returnType.get());
		jo["args"] = dumpJsonAsObjectArray(args);
	}
};

static OrcParser::FunctionPointerVarDeclarationContext* 
ast_createAstFunctionPointerVarDeclaration(
	AstMake* mk,
	std::shared_ptr<SymbolType> returnType,
	std::string varName,
	std::vector<std::shared_ptr<SymbolTypeArg>>& args,
	int pointerLevel=1
);

class SymbolTypeClosure : public SymbolTypeRef {
public:
	std::shared_ptr<SymbolType> returnType = nullptr;
	std::vector<std::shared_ptr<SymbolTypeArg>> args;
	//std::vector<std::shared_ptr<SymbolType>> argTypes;
	virtual antlr4::tree::ParseTree* toAstType(AstMake* mk) override;


	virtual std::string toString() {
		auto argsStr = std::string("");
		for (auto arg : args) {
			argsStr += arg->toString();
			if (args.back() != arg) {
				argsStr += ", ";
			}
		}

		auto s = std::format("{} (*) ({})", returnType ? returnType->toString() : std::string(""), argsStr
		);
		return s;
	};

	virtual void fromJson(nlohmann::json& jo) {
		SymbolTypeRef::fromJson(jo);
		returnType = parseJsonToT<SymbolType>(jo["returnType"]);
		parseJsonToObjectArray<SymbolTypeArg>(jo["args"], args);
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolTypeRef::toJson(jo);
		jo["returnType"] = dumpJson(returnType.get());
		jo["args"] = dumpJsonAsObjectArray(args);
	}
};

//符号引用
class Symbol: public Object, public std::enable_shared_from_this< Symbol> {
public:
	std::string name;
	virtual std::string toString() {
		return std::format("Symbol({}, {})",
			name, typeid(*this).name());
	}



	virtual void fromJson(nlohmann::json& jo) {
		name = json_getString(jo, "name");
	}
	virtual void toJson(nlohmann::json& jo) {
		jo["name"] = name;
	}
};



//符号定义。 符号跟符号定义什么区别。
class SymbolDefinition : public Symbol {
public:
	std::string fullname;
	bool isStatic = false;

	Range range;
	

	//所在的空间,在load时初始化
	std::shared_ptr<SymbolSpace> hostSpace = NULL;

	virtual void setHostSpace(SymbolSpace *space);
	virtual std::string toString() override;
	virtual std::shared_ptr<SymbolType> getType() { return nullptr; };

	virtual void setRangeByRuleContext(antlr4::tree::ParseTree* ctx);

	virtual void fromJson(nlohmann::json& jo) {
		Symbol::fromJson(jo);
		fullname = json_getString(jo, "fullname");
		isStatic = json_getInt(jo, "isStatic");
		if (jo.contains("range")) {
			range = jo["range"].get<Range>();
		}
	}
	virtual void toJson(nlohmann::json& jo) {
		Symbol::toJson(jo);

		jo["fullname"] = fullname;
		jo["isStatic"] = isStatic;

		jo["range"] = range;
	}
};

class SymbolDefinitionPrimitiveType : public SymbolDefinition {
public:
};
class SymbolDefinitionHasMembers : public SymbolDefinition {
public:
	std::vector<std::shared_ptr<SymbolDefinition>> members;


	virtual void setHostSpace(SymbolSpace* space) override;

	virtual std::shared_ptr<SymbolDefinition> findMemberByName(std::string name);

	virtual std::vector<std::shared_ptr<SymbolDefinition>> listAllMembers_includeSupers() { return members; }

	virtual void fromJson(nlohmann::json& jo) {
		SymbolDefinition::fromJson(jo);

		parseJsonToObjectArray(jo["members"], members);
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolDefinition::toJson(jo);

		jo["members"] = dumpJsonAsObjectArray(members);
	}
};
class SymbolDefinitionClass;

class ClassMemberDto {
public :
	std::shared_ptr<SymbolDefinition> member = nullptr;
	std::shared_ptr<SymbolDefinitionClass> classDef = nullptr;
};
//类
class SymbolDefinitionClass : public SymbolDefinitionHasMembers {
public:
	std::string superName;

	bool refc = false; //是否采用引用计数

	virtual std::shared_ptr<SymbolType> getType() {
		auto pointer = std::make_shared<SymbolTypePointer>();
		pointer->typeName = "Vtable_Object";
		return pointer;
	};
	virtual std::shared_ptr<SymbolDefinitionClass> findSuperSymbolDefinition();

	virtual std::shared_ptr<ClassMemberDto> findMemberByName_includeSupers(std::string name);
	//查找 成员的初始定义
	virtual std::shared_ptr<ClassMemberDto> findOriginalDefinedMemberByName_includeSupers(std::string name);
	virtual std::vector<std::shared_ptr<SymbolDefinition>> listAllMembers_includeSupers() override;

	//检查是否可用refc. 如果自己、父类都没有引用类型，说明必定不成环，可以采用refc
	virtual bool hasField_typeIsRef();
	//指针也可能会成环的，因为可以手动调用urgc的函数。。如list/map.所以严格一点。 只有基本类型的才会被自动识别
	//如果业务上明确不成环的，也可以用手动标记 class refc 来指定
	virtual bool hasField_typeIsRef_orPointer();
	virtual void autoDetecRefc();

	virtual void fromJson(nlohmann::json& jo) {
		SymbolDefinitionHasMembers::fromJson(jo);

		superName = json_getString(jo, "superName");
		refc = json_getInt(jo, "refc");
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolDefinitionHasMembers::toJson(jo);

		jo["superName"] = superName;
		jo["refc"] = refc;
	}
};
//枚举
class SymbolDefinitionEnum : public SymbolDefinition {
public:
};
//结构体
class SymbolDefinitionStruct : public SymbolDefinitionHasMembers {
public:
};
//枚举项
class SymbolDefinitionEnumItem : public SymbolDefinition {
public:
	std::shared_ptr<SymbolType> type = nullptr;
	virtual std::shared_ptr<SymbolType> getType() { return type; }

	virtual void fromJson(nlohmann::json& jo) {
		SymbolDefinition::fromJson(jo);
		if (jo.contains("type")) {
			type = std::dynamic_pointer_cast<SymbolType>( parseJsonToObject(jo["type"]));
		}
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolDefinition::toJson(jo);

		jo["type"] = dumpJson(type.get());
	}
};
//扩展
class SymbolDefinitionExtension : public SymbolDefinitionHasMembers {
public:
};
//函数
class SymbolDefinitionFunction : public SymbolDefinition {
public:
	std::shared_ptr<SymbolTypeFunction> type = nullptr;
	virtual std::shared_ptr<SymbolType> getReturnType();
	virtual std::shared_ptr<SymbolType> getType();


	virtual void fromJson(nlohmann::json& jo) {
		SymbolDefinition::fromJson(jo);

		type = parseJsonToT<SymbolTypeFunction>(jo["type"]);
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolDefinition::toJson(jo);

		jo["type"] = dumpJson(type.get());
	}
};
//变量
class SymbolDefinitionVar : public SymbolDefinition {
public:
	std::shared_ptr<SymbolType> type = nullptr;
	virtual std::shared_ptr<SymbolType> getType();


	virtual void fromJson(nlohmann::json& jo) {
		SymbolDefinition::fromJson(jo);

		type = parseJsonToT<SymbolType>(jo["type"]);
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolDefinition::toJson(jo);

		jo["type"] = dumpJson(type.get());
	}
};

// 类型定义, 即别名
class SymbolDefinitionTypedef : public SymbolDefinition {
public:
	std::shared_ptr<SymbolType> type = nullptr;
	virtual std::shared_ptr<SymbolType> getType();


	virtual void fromJson(nlohmann::json& jo) {
		SymbolDefinition::fromJson(jo);

		type = parseJsonToT<SymbolType>(jo["type"]);
	}
	virtual void toJson(nlohmann::json& jo) {
		SymbolDefinition::toJson(jo);

		jo["type"] = dumpJson(type.get());
	}
};

class SymbolDefinitionClassField : public SymbolDefinitionVar {
public:
};
class SymbolDefinitionMethod : public SymbolDefinitionFunction {
public:
};
class Import: public Object {
public:
	std::string path;
	bool isAllImport = true;
	// alias
	bool isInclude = false;
	std::string includeCode;
	int line = 0; //不序列化

	std::string abspath;

	std::string gocAbspath(std::string orcAbspath);

	inline bool isIncludeFromGlobal() {
		return includeCode.ends_with(">");
	}

	std::string toString() {
		return std::format("Import(isInclude:{}, isAllImport:{}, path:{})", 
			isInclude, isAllImport, path);
	}

	virtual void fromJson(nlohmann::json& jo) {
		path = json_getString(jo, "path");
		includeCode = json_getString(jo, "includeCode");
		isAllImport = json_getInt(jo, "isAllImport");
		isInclude = json_getInt(jo, "isInclude");
	}
	virtual void toJson(nlohmann::json& jo) {
		jo["path"] = path;
		jo["isAllImport"] = isAllImport;
		jo["isInclude"] = isInclude;
		jo["includeCode"] = includeCode;
	}
};
//符号空间加载，可以通过路径，加载符号空间。 用来帮助查找 import中的符号
/*
头文件怎么更新符号表
区分状态:
- #include <>   这是外部依赖，不用比较，只要有符号文件，就用，也不用更新
- #include ".开头的相对路径"  可以找到头文件，采用头文件的mtime来判断要不要更新符号文件
- #include "无法明确的地址"
	a 尝试在源文件目录下搜索， 如果有搜索到头文件，就用头文件的mtime来判断要不要更新符号文件
	b 尝试在配置的C_INCLUDE_PATH中搜索， 如果有搜索到头文件，就用头文件的mtime来判断要不要更新符号文件
	c 跟外部依赖一样，不比较，有符号文件就用，不更新
最终是看能不能找到源文件了吧。
如果头文件的头文件有变化呢？不管,后续可以优化跟踪头文件的依赖变化。前期，依靠手动清理符号文件来处理
*/
class SymbolSpaceLoader: public std::enable_shared_from_this<SymbolSpaceLoader> {
public:
	std::unordered_map<std::string, std::shared_ptr<SymbolSpace>> lib;
	virtual void unload(std::string path);
	//加载符号表
	virtual std::shared_ptr<SymbolSpace> load(std::string path);
	//加载符号表，基于某个空间
	virtual std::shared_ptr<SymbolSpace> load_baseOnSymbolSpace(SymbolSpace* space, Import *imp);

	//加载c头文件的符号表. [includeCode]形如#include "xx.h"，或者 #include <xx.h>. headerPath是头文件的路径。 如果文件存在，就会比较mtime
	// 否则，只生成一次符号表. headerPath
	virtual std::shared_ptr<SymbolSpace> load_cHeader(std::string includeCode, std::string basepath, std::string headerpath, std::string absHeaderPath);

	//加载.orc文件的符号表
	virtual std::shared_ptr<SymbolSpace> load_orcModule(std::string absPath);

	// 查找目标文件路径
	// 
	// [basepath] 表示在哪个文件里导入了[path]. [basepath]最好传入绝对路径。这样内部在查找时，判断文件是否存在，就不会受cwd影响
	// [fromGlobalFilePath] 用来表示c 中的 #include <path>, 
	//virtual std::string findTargetFilePath(std::string basepath, std::string path, bool fromGlobalIncludePath);


	// 计算orc的符号文件路径
	virtual std::string mkSymbolPath_forOrc(std::string orcAbsPath);
	virtual void saveSymbolFile_forOrc(std::string orcAbsPath, SymbolSpace *space);
};
class ExtensionMemberInfo {
public:
	std::shared_ptr<SymbolDefinitionMethod> methodDef = nullptr;
	std::shared_ptr<SymbolDefinitionExtension> extensionDef = nullptr;

};
//符号空间/符号表,一个符号空间就对应一个文件
class SymbolSpace : public Object, public std::enable_shared_from_this<SymbolSpace>{
public:
	std::string packageName;
	std::string path;
	std::string _abspath;

	std::vector<std::shared_ptr<Import>> imports;
	//由于扩展的存在， 在解析如 self.margin.hor()函数调用时，会被转为((Inset*)null).hor(self.margin). 此时对Inset产生了引用
	//如果没有hiddenImport,就会找不到Inset的符号。  所以在转换self.margin.hor时， 生成对Inset的hiddenImport
	//查询符号时，也会到hiddenImports中查找。仅用于编译生成，不需要持久化。
	std::vector<std::shared_ptr<Import>> hiddenImports;

	//导出的符号定义
	std::vector<std::shared_ptr<SymbolDefinition>> symbols;
	//符号空间加载
	std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = nullptr;
	////静态的符号定义
	//std::vector<SymbolDefinition> staticSymbols;

	//将自己和import进来的合成列表
	std::vector<std::shared_ptr<SymbolSpace>> listSymbolSpace_includeSelfAndImports();


	virtual void fromJson(nlohmann::json& jo) {
		packageName = json_getString(jo, "packageName");
		path = json_getString(jo, "path");
		parseJsonToObjectArray(jo["symbols"], symbols);
		parseJsonToObjectArray(jo["imports"], imports);
	}
	virtual void toJson(nlohmann::json& jo) {
		jo["packageName"] = packageName;
		jo["path"] = path;

		jo["symbols"] = dumpJsonAsObjectArray(symbols);
		jo["imports"] = dumpJsonAsObjectArray(imports);
	}


	//对子树填充全名称
	static void fulfillFullname(antlr4::tree::ParseTree* tree);

	//从路径和语法树中构建符号表
	std::shared_ptr<SymbolSpace> buildSymbolSpace(std::string path, antlr4::tree::ParseTree* tree,
		std::shared_ptr<OrcParser> parser);

	//从路径和语法树中构建符号表，编译生成代码
	bool startBuild(std::string path, antlr4::tree::ParseTree* tree,
		std::shared_ptr<OrcParser> parser, CostUs& cost);
	//从路径和语法树中构建符号表
	static std::shared_ptr<SymbolSpace> build(std::string path, antlr4::tree::ParseTree* tree,
		std::shared_ptr<OrcParser> parser);

	//从include构建符号表
	//为每个include构建符号表
	static std::shared_ptr<SymbolSpace>  buildSymbolSpace_forInclude(std::string orcPath, std::string path, std::string includeSegment,
		std::shared_ptr<SymbolSpaceLoader> loader);

	static std::shared_ptr<SymbolSpace>  buildSymbolSpace_forImport(
		std::string absPath,
		std::shared_ptr<SymbolSpaceLoader> loader);


	//从ast json文件中构建符号表。  主要是从clang生成的ast.json中提取
	static std::shared_ptr<SymbolSpace> buildFromAstJson(std::string path, std::string headerPath,
		std::shared_ptr<SymbolSpaceLoader> loader);

	std::shared_ptr<SymbolDefinition> findSymbolDefinitionByName_includeImports(std::string name);
	std::shared_ptr<SymbolDefinition> findSymbolDefinitionByName_exportedInThisSpace(std::string name);

	std::shared_ptr<SymbolDefinitionClass> findSuperClassSymbolDefinitionByAstClassDefinition(OrcParser::ClassDefinitionContext *ctx);


	//在当前空间中定义的扩展中寻找指定类型的指定名称的扩展方法
	ExtensionMemberInfo findExtensionMemberByTypeNameAndMemberName_exportedInThisSpace(std::string name, std::string memberName);
	ExtensionMemberInfo findExtensionMemberByTypeNameAndMemberName_includeImports(std::string name, std::string memberName);

	void addSymbolOnce(std::shared_ptr<SymbolDefinition> sym);

	//隐藏的Import
	void addHiddenImport_byPath(std::string abspath);
	void addHiddenImport(std::shared_ptr<Import> refImport);
	bool existsImport(std::string abspath);
	std::shared_ptr<Import> findImportByAbspath(std::string abspath);
	void addHiddenImport_byPath_ifNeed(std::string abspath);
	std::string gocAbspath();

	std::string toString() {
		std::string out = std::format("============符号表[{}, package:{}]============\n", path, packageName);

		out += "Imports:";
		for (auto& imp : imports) {
			out += "\n\t" + imp->toString();
		}

		out += "\nSymbols:";
		for (auto& imp : symbols) {
			out += "\n\t" + imp->toString();
		}

		return out;
	}
};

//通过类型，查找祖先节点,含自己
template <class T>
T* ast_findAncestorByType(antlr4::tree::ParseTree *tree) {
	while (tree) {
		auto ret = dynamic_cast<T*>(tree);
		if (ret) {
			return ret;
		}
		tree = tree->parent;
	}
	return NULL;
}

//向上找父类，两种类型都可以
template <class T, class T2>
antlr4::tree::ParseTree* ast_findFirstAncestorByTwoType(antlr4::tree::ParseTree* tree) {
	while (tree) {
		auto ret = dynamic_cast<T*>(tree);
		if (ret) {
			return ret;
		}
		{
			auto ret = dynamic_cast<T2*>(tree);
			if (ret) {
				return ret;
			}
		}
		tree = tree->parent;
	}
	return NULL;
}
//判断是否有祖辈关系

bool ast_isAncestorOf(antlr4::tree::ParseTree* ancestor, antlr4::tree::ParseTree* kid);
//提取pointer类型的指针 星星数 => **
std::string ast_pointerStarText(antlr4::tree::ParseTree* ctx);

class SymbolTypeWithHostSpace {
public:
	std::shared_ptr<SymbolType> type = nullptr;
	std::shared_ptr < SymbolSpace> hostSpace = NULL; //在该空间下，可以找到type的定义
	static std::shared_ptr<SymbolTypeWithHostSpace> mk(std::shared_ptr<SymbolType> type,
		std::shared_ptr < SymbolSpace> hostSpace
	);
	std::shared_ptr<SymbolDefinition> findSymbolDefinition();
	//获取类型的指针级别
	int getPointLevel_ofType();
	// 按类型的指针级别，返回'**'
	std::string getPointStarText_ofType();
};

class VarInfo {
public:
	std::string varName;
	bool isFound = false;
	OrcParser::VarDeclarationContext* varDeclaration = NULL;
	//参数
	OrcParser::ArgumentDeclarationContext* argumentDeclaration = NULL;
	//用于scopeStatement
	OrcParser::ScopeStatementContext* scopeStatement = NULL;
	//全局变量或者导入的符号,或者原始类型(如int)
	std::shared_ptr<SymbolDefinition> symbolDefinition = NULL;

	//void findSymbolDefinitionByVarDeclaration(SymbolSpace* space);
	//void findSymbolDefinitionByArgumentDeclaration(SymbolSpace* space);

	//void findSymbolDefinitionByScopeStatement(SymbolSpace* space);
	//void findSymbolDefinitionByType(SymbolSpace* space, OrcParser::TypeContext* type);

	std::shared_ptr<SymbolTypeWithHostSpace> calcSymbolType(std::shared_ptr < SymbolSpace> space);


	//变量定义是否在函数内
	bool isInFunction();
};
std::string ast_mkFullname_byPrefix(std::string packageName, std::string name);

std::shared_ptr<SymbolTypeFunction> ast_createSymbolTypeFunction(
	OrcParser::TypeContext* returnType,
	OrcParser::ArgumentsDeclarationContext* argumentsDeclaration
);
VarInfo ast_findVarInfoByVarName(
	antlr4::tree::ParseTree* tree, string varName,
	std::shared_ptr<SymbolSpace> space //如果有传入，就会顺着找导入的其他变量
);

//在for语句内包一层block
OrcParser::BlockContext* ast_wrapBlock_outOfForStatement(
	antlr4::tree::ParseTree* tree, 
	AstMake *mk);

bool ast_replaceChild_specificParent(
	antlr4::tree::ParseTree* parent,
	antlr4::tree::ParseTree* ctx,
	antlr4::tree::ParseTree* newnode
);
bool ast_replaceChild(
	antlr4::tree::ParseTree* ctx,
	antlr4::tree::ParseTree* newnode
);

//scopeStatement创建返回值的TypeContext
OrcParser::TypeContext * ast_mkTypeContext_forScopeStatement(
	OrcParser::ScopeStatementContext *ctx,
	std::shared_ptr<SymbolSpace> space,
	AstMake *mk
);

OrcParser::TypeContext* ast_mkTypeContext_SingleExpression(
	OrcParser::SingleExpressionContext* ctx,
	std::shared_ptr<SymbolSpace> space,
	AstMake* mk
);

//克隆typecontext
OrcParser::TypeContext* ast_cloneTypeContext(
	OrcParser::TypeContext* ctx,
	AstMake* mk
);

void ast_printTree(
	antlr4::tree::ParseTree* tree,
	OrcParser* parser);


void Symbol$registerMetas();


class MemberInfo {
public:
	std::shared_ptr<SymbolTypeWithHostSpace> typeInfo = nullptr;
	std::shared_ptr<SymbolDefinition> typeDef = nullptr;

	//真成员才会有此字段
	std::shared_ptr<SymbolDefinition> memberDef = nullptr;

	std::shared_ptr<SymbolDefinitionMethod> methodDef = nullptr;
	std::shared_ptr<SymbolDefinitionClassField> fieldDef = nullptr;

	std::shared_ptr<SymbolDefinitionStruct> structDef = nullptr;
	std::shared_ptr<SymbolDefinitionClass> classDef = nullptr; //实际member所在的类。 可能不是查询时的类，而是父类
	std::shared_ptr<SymbolDefinitionExtension> extensionDef = nullptr;
	bool isFound = false;

	static MemberInfo findMemberInfo(
		OrcParser::SingleExpressionContext* objExpr, string propName,
		std::shared_ptr<SymbolSpace> space);
};
class ReturnStringVisitor;
std::string ast_closureType_genCode(OrcParser::ClosureTypeContext* closureType,
	ReturnStringVisitor* vi,
	std::string varName,
	AstMake* mk);



//表达式树中，是否有用到变量
bool ast_isVarNameUsedInExprSubtree(antlr4::tree::ParseTree* tree, std::string varName);

//是不是普通的访问表达式,不含副作用
// id 表达式， 普通的memberDot, memberIndex表达式, 字面量
bool ast_isPureAccessExpression(antlr4::tree::ParseTree* tree);


//判断子树中是否含有节点
bool ast_subtreeContainsNode(antlr4::tree::ParseTree* tree, antlr4::tree::ParseTree* dst);


//生成临时变量tmpReturn时，需要记录numberReturn,那就需要找到numberReturn的共同宿主
OrcRuleContext* ast_findHostAstNode_forNumberReturn(antlr4::tree::ParseTree* ctx);

//是否含有text的terminal
bool ast_hasTerminal_inChildren(antlr4::tree::ParseTree* tree, std::string text);


std::shared_ptr<SymbolTypeWithHostSpace> ast_calcSymbolTypeOfExpressionResult(OrcParser::SingleExpressionContext* expr,
	std::shared_ptr<SymbolSpace> space);


// [basepath] 表示在哪个文件里导入了[path]. [basepath]最好传入绝对路径。这样内部在查找时，判断文件是否存在，就不会受cwd影响
// [fromGlobalFilePath] 用来表示c 中的 #include <path>, 
std::string findTargetFilePath(std::string basepath, std::string path, bool fromGlobalIncludePath);

//通过typeContext,判断是不是Class@
std::shared_ptr<SymbolDefinitionClass> ast_findSymbolDefinitionClass_byTypeContext(
	OrcParser::TypeContext* ctx, std::shared_ptr<SymbolSpace> space);

std::shared_ptr<SymbolDefinitionClass> ast_findSymbolDefinitionClass_byTypeName(std::string typeName, std::shared_ptr<SymbolSpace> space);



//将ast节点转为符号类型
std::shared_ptr<SymbolType> typeContext_toSymbolType(OrcParser::TypeContext* type);

//
bool ast_isAssignable_byClassName(
	std::string leftName, std::string rightName,
	std::shared_ptr<SymbolSpace> leftSpace,
	std::shared_ptr<SymbolSpace> rightSpace
);



//将ast节点转为符号类型
std::shared_ptr<SymbolType> createSymbolType_fromFunctionPointerVarDeclaration(OrcParser::FunctionPointerVarDeclarationContext* type);


string ast_getNakeTypeName_fromTypeContext(OrcParser::TypeContext* type);


bool isNakeTypeName_isPrimitiveType(std::string nakeTypeName);



std::shared_ptr<SymbolType> structMember_typeContext_toSymbolType(OrcParser::StructMemberContext* ctx);
std::shared_ptr<SymbolType> classFieldDeclaration_typeContext_toSymbolType(OrcParser::ClassFieldDeclarationContext* ctx);