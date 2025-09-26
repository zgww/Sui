#pragma once
#include "./ActorByThread.h"
#include "json.hpp"
#include "Symbol.h"
#include <string>
#include "CodeCompletion.h"

using namespace nlohmann;


template <typename V>
class SafeVector {
public:
	int size() {
		return vec.size();
	}

	void clear() {
		std::lock_guard<std::mutex> g(mutex_);
		vec.clear();
	}
	void push_back(V v) {
		std::lock_guard<std::mutex> g(mutex_);
		vec.push_back(v);
	}

	V get(int i) {
		std::lock_guard<std::mutex> g(mutex_);
		if (i >= 0 && i < vec.size()) {
			return vec[i];
		}
		return nullptr;
	}

	std::mutex mutex_;
	std::vector<V> vec;
};

template <typename K, typename V>
class SafeMap {
public:
	bool contains(K key) {
		std::lock_guard<std::mutex> g(mutex_);
		bool ret = map.contains(key);
		return ret;
	}
	void set(K key, V v) {
		std::lock_guard<std::mutex> g(mutex_);
		map[key] = v;
	}

	V get(K key) {
		std::lock_guard<std::mutex> g(mutex_);
		if (map.contains(key)) {
			return map[key];
		}
		return nullptr;
	}

	std::mutex mutex_;
	std::unordered_map<K, V> map;
};


struct ShowMessageParams {
	//Error=1
	//Warning=2
	//Info=3
	//Log=4
	//Debug=5
	int type = 3;
	std::string message;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ShowMessageParams, type, message);
};

struct TextEdit {
	Range range;

	/**
	 * The string to be inserted. For delete operations use an
	 * empty string.
	 */
	std::string newText;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TextEdit, range, newText);
};
struct WorkspaceEdit {
	std::unordered_map<std::string, std::vector<TextEdit>> changes;
	//std::vector<TextEdit> documentChanges; // 错误，但是暂时不用，所以忽略
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(WorkspaceEdit, changes
		//, documentChanges
	);

};
struct ApplyWorkspaceEditParams {
	std::string label;
	WorkspaceEdit edit;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ApplyWorkspaceEditParams, label, edit);
};
struct ContentChange {
	std::string text;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ContentChange, text);
};


struct TextDocumentWithUriVersion {
	std::string uri;
	int version;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TextDocumentWithUriVersion, uri, version);
};
struct TextDocumentDidChange {
	std::vector<ContentChange> contentChanges;
	TextDocumentWithUriVersion textDocument;

	int version;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TextDocumentDidChange, contentChanges, textDocument);
};
struct TextDocumentDidOpen {
	std::string languageId;
	std::string text;
	std::string uri;
	int version;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TextDocumentDidOpen, languageId, text, uri, version);
};

struct Location {
	std::string uri;
	Range range;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Location, uri, range);
};

struct LocationLink {
	Range originSelectionRange;
	std::string targetUri;
	Range targetRange;
	Range targetSelectionRange;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(LocationLink, originSelectionRange, targetUri, targetRange, targetSelectionRange);
};
enum SymbolKind {
	SymbolKind_File = 1,
	SymbolKind_Module = 2,
	SymbolKind_Namespace = 3,
	SymbolKind_Package = 4,
	SymbolKind_Class = 5,
	SymbolKind_Method = 6,
	SymbolKind_Property = 7,
	SymbolKind_Field = 8,
	SymbolKind_Constructor = 9,
	SymbolKind_Enum = 10,
	SymbolKind_Interface = 11,
	SymbolKind_Function = 12,
	SymbolKind_Variable = 13,
	SymbolKind_Constant = 14,
	SymbolKind_String = 15,
	SymbolKind_Number = 16,
	SymbolKind_Boolean = 17,
	SymbolKind_Array = 18,
	SymbolKind_Object = 19,
	SymbolKind_Key = 20,
	SymbolKind_Null = 21,
	SymbolKind_EnumMember = 22,
	SymbolKind_Struct = 23,
	SymbolKind_Event = 24,
	SymbolKind_Operator = 25,
	SymbolKind_TypeParameter = 26,
};
struct SymbolInformation {
	std::string name;
	//File=1 Module=2 Namespace=3 Package=4 Class=5
	// Method = 6 Property = 7 Field=8 Constructor=9 Enum=10
	// Interface= 11 Function=12 Variable=13 Constant=14 String=15

	SymbolKind kind;
	Location location;

	void setLocation(std::string uri, int startLine, int startChar, int endLine, int endChar) {
		this->location.uri = uri;
		this->location.range.start.line = startLine;
		this->location.range.start.character = startChar;
		this->location.range.end.line = endLine;
		this->location.range.end.character = endChar;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(SymbolInformation, name, kind, location);
};


struct DocumentSymbol {
	std::string name;
	std::string detail;
	//File=1 Module=2 Namespace=3 Package=4 Class=5
	// Method = 6 Property = 7 Field=8 Constructor=9 Enum=10
	// Interface= 11 Function=12 Variable=13 Constant=14 String=15

	SymbolKind kind;
	Range range;
	Range selectionRange;
	std::vector<DocumentSymbol> children;

	void setRangeByRange(Range range) {
		this->range = range;
		this->selectionRange = range;
	}
	void setRange(std::string uri, int startLine, int startChar, int endLine, int endChar) {
		this->range.start.line = startLine;
		this->range.start.character = startChar;
		this->range.end.line = endLine;
		this->range.end.character = endChar;

		this->selectionRange.start.line = startLine;
		this->selectionRange.start.character = startChar;
		this->selectionRange.end.line = endLine;
		this->selectionRange.end.character = endChar;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DocumentSymbol, name, detail, kind, range, selectionRange, children);
};

struct TextDocumentWithUri {
	std::string uri;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TextDocumentWithUri, uri);
};
enum TriggerKind {
	/**
	 * Completion was triggered by typing an identifier (24x7 code
	 * complete), manual invocation (e.g Ctrl+Space) or via API.
	 * 可以提示变量或者类型?
	 */
	TriggerKind_Invoked = 1,
	/**
	 * Completion was triggered by a trigger character specified by
	 * the `triggerCharacters` properties of the
	 * `CompletionRegistrationOptions`.
	 */
	TriggerKind_TriggerCharacter = 2,
	/**
	 * Completion was re-triggered as the current completion list is incomplete.
	 */
	TriggerKind_TriggerForIncompleteCompletions = 3,
};
struct Command {
	std::string title;
	std::string command;
	std::vector<json> arguments;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Command, title, command, arguments);
};

//代码完成
struct CompletionItem {
	std::string label;
	int kind;
	std::string sortText;
	//TextEdit textEdit;
	//json command;
	//Command command; //不希望响应里带上空的command，可以让字段为json command
	std::vector<TextEdit> additionalTextEdits;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CompletionItem, label, kind, sortText,  additionalTextEdits);
};
struct CompletionContext {
	std::string triggerCharacter;
	TriggerKind triggerKind;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CompletionContext, triggerCharacter, triggerKind);
};
struct CompletionParams {
	CompletionContext context;
	Position position;
	TextDocumentWithUri textDocument;


	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CompletionParams, context, position, textDocument);
};

struct TextDocumentPositionParams {
	Position position;
	TextDocumentWithUri textDocument;


	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(TextDocumentPositionParams, position, textDocument);
};
struct HoverParams : public TextDocumentPositionParams {
	/*Position position;
	TextDocumentWithUri textDocument;*/

	//NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(HoverParams);
};
struct CodeDescription {
	std::string href; //URI
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CodeDescription, href);
};
struct DiagnosticRelatedInformation {
	Location location; //URI
	std::string message; //URI
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DiagnosticRelatedInformation, location, message);
};
struct Diagnostic {
	Range range;
	///**
	 //* Reports an error.
	 //*/
	//export const Error : 1 = 1;
	///**
	// * Reports a warning.
	// */
	//export const Warning : 2 = 2;
	///**
	// * Reports an information.
	// */
	//export const Information : 3 = 3;
	///**
	// * Reports a hint.
	// */
	//export const Hint : 4 = 4;
	int severity;
	int code;
	CodeDescription codeDescription;
	std::string source;
	std::string message;

	///**
 //* Unused or unnecessary code.
 //*
 //* Clients are allowed to render diagnostics with this tag faded out
 //* instead of having an error squiggle.
 //*/
	//export const Unnecessary : 1 = 1;
	///**
	// * Deprecated or obsolete code.
	// *
	// * Clients are allowed to rendered diagnostics with this tag strike through.
	// */
	//export const Deprecated : 2 = 2;
	std::vector<int> tags;
	std::vector< DiagnosticRelatedInformation> relatedInformation;


	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Diagnostic, range, severity, code, codeDescription, source, message, tags, relatedInformation);
};


struct PublishDiagnosticsParams {
	std::string uri;
	int version;
	std::vector<Diagnostic> diagnostics;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(PublishDiagnosticsParams, uri, version, diagnostics);
};
struct CodeActionContext {
	std::vector< Diagnostic> diagnostics;
	std::vector<std::string> only;

	///**
 //* Code actions were explicitly requested by the user or by an extension.
 //*/
	//export const Invoked : 1 = 1;

	///**
	// * Code actions were requested automatically.
	// *
	// * This typically happens when current selection in a file changes, but can
	// * also be triggered when file content changes.
	// */
	//export const Automatic : 2 = 2;
	int triggerKind;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CodeActionContext, diagnostics, only, triggerKind);
};

struct CodeActionParams {
	Range range;
	CodeActionContext context;
	TextDocumentWithUri textDocument;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CodeActionParams, range, context, textDocument);
};
struct ImportUriParams {
	std::string curUri; //当前
	std::string importUri; //要导入的uri

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ImportUriParams, curUri, importUri);
};


struct ExecuteCommandParams {
	std::string command;
	json arguments;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ExecuteCommandParams, command, arguments);
};
struct CodeAction {
	std::string title;
	std::string kind;
	std::vector< Diagnostic> diagnostics;
	bool isPrefered;
	Command command;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CodeAction, title, kind, diagnostics, isPrefered, command);
};

struct MarkupContent {
	std::string kind = "plaintext"; // plaintext|markdown
	std::string value = "";


	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(MarkupContent, kind, value);
};

struct HoverResponse {
	MarkupContent contents;
	Range range;
	/*Position position;
	TextDocumentWithUri textDocument;*/

	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(HoverResponse, contents, range);
};


class TextDocumentSymbolInfo {
public:
	std::shared_ptr<TextDocumentDidOpen> textDocument;
	std::shared_ptr<SymbolSpace> symbolSpace;

	AstBuilder fullAst;
	OrcRuleContext* program = NULL;

	AstMake mk;
	tree::ParseTreeTracker _tracker;

	void buildSymbolInfomations_bySymbols(std::vector<std::shared_ptr<SymbolDefinition>>& symbols,
		std::vector<SymbolInformation>& ret);
	std::vector<SymbolInformation> buildSymbolInfomations();

	void buildDocumentSymbols_bySymbols(std::vector<std::shared_ptr<SymbolDefinition>>& symbols,
		std::vector<DocumentSymbol>& ret);
	std::vector<DocumentSymbol> buildDocumentSymbols();

	//查找最后的import的所在行
	int findLastImportLine();
	//查找要播放的import的所在行
	int findInsertImportLine_afteLastImport();
};


extern SafeMap<std::string, std::shared_ptr<TextDocumentSymbolInfo>> textDocumentSymbolInfoMap;
extern std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader;


class LspMail : public ActorMail {
public:
	json jo;


	virtual void handle(std::shared_ptr<ActorByThread> actor) override;

};

class LspActor :public ActorByThread
{
public:

};
class DiagnosticsActor :public ActorByThread
{
public:

	virtual void doRun() override;
	virtual void route(std::shared_ptr<ActorMail>& msg) override;

};

void log(std::string s);

void writeResponse(json& result, int id);

int writeRequest(std::string method, json& params, std::function<void(json&)> onResponse);

bool initialize(int id, std::string method, json& params);
bool initialized(int id, std::string method, json& params);

void writeNotification(std::string method, json& params);



bool didOpen(int id, std::string method, json& params);

void updateTextDocumentSymbolInfo(std::shared_ptr<TextDocumentDidOpen> textDocument);


template <typename T, typename Key>
std::shared_ptr<T> map_get(std::unordered_map<Key, std::shared_ptr<T>> map, Key key) {
	if (map.contains(key)) {
		return map[key];
	}
	return nullptr;
}

std::shared_ptr<SymbolSpace> buildSymbolSpace_byTextDocument(std::shared_ptr<TextDocumentSymbolInfo> info, std::shared_ptr<TextDocumentDidOpen> textDocument);



void doDiagnostic(std::string uri);

bool didChange(int id, std::string method, json& params);


void updateTextDocumentCodeAndSymbolInfo(std::string uri, int version, std::string code);

extern int newline;

class SymbolActor;
class ProjectScanActor;

//负责诊断、符号表的构建 
extern std::shared_ptr<SymbolActor> symbolActor;
//负责诊断、符号表的构建 
extern std::shared_ptr<ActorByThread> diagnosticsActor;
//项目扫描符号表的actor
extern std::shared_ptr<ProjectScanActor> projectScanActor;
//定时器
extern std::shared_ptr<ActorTimer> timerActor;
//lsp路由处理器 与lsp的交互都在这里
extern std::shared_ptr<LspActor> lspActor;


std::string SymbolSpace_mkImportRelativePathByAbsPath(std::shared_ptr<SymbolSpace> space, std::string abspath);



void showMessage(std::string msg, int type=3);


void printOnLspActor(std::string str);