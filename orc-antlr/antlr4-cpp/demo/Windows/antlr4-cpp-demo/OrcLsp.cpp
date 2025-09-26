#include "OrcLsp.h"
#include <unordered_map>
#include <functional>
#include "./SymbolBuilderVisitor.h"
#include <CodeCompletion.h>
#include "ActorByThread.h"
#include "ProjectScanActor.h"
#include "LspActor.h"
#include "SymbolActor.h"
#include "UrlUtil.h"


#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using namespace antlr4;

//负责符号表的构建 
std::shared_ptr<SymbolActor> symbolActor;
//诊断的actor
std::shared_ptr<ActorByThread> diagnosticsActor;
//项目扫描符号表的actor
std::shared_ptr<ProjectScanActor> projectScanActor;
//定时器
std::shared_ptr<ActorTimer> timerActor;
//lsp路由处理器 与lsp的交互都在这里
std::shared_ptr<LspActor> lspActor;


void initActors() {
	symbolActor = std::make_shared<SymbolActor>();
	projectScanActor = std::make_shared<ProjectScanActor>();
	timerActor = std::make_shared<ActorTimer>();
	lspActor = std::make_shared<LspActor>();
	diagnosticsActor = std::make_shared<ActorByThread>();


	symbolActor->startThread();
	projectScanActor->startThread();
	timerActor->startThread();
	lspActor->startThread();
	diagnosticsActor->startThread();
}



//void log(std::string s) {
//	static FILE* f;
//	if (!f) {
//		f = fopen("console.log", "w+");
//	}
//	fwrite(s.c_str(), 1, s.length(), f);
//	fflush(f);
//}

//static int newline = 1; // \n
//static std::unordered_map<int, std::function<void(json&)>> onResponseMap;





//void route(json& jo) {
//	auto id = json_getInt(jo, "id");
//	auto method = json_getString(jo, "method");
//
//	if (method == "") { //说明是响应
//		json result = jo.contains("result") ? jo["result"] : json::object();
//		log(std::format("\nroute. id:{}, json:{}, hasOnResponse:{}\n", id, 
//			jo.dump(4),
//			
//			onResponseMap.contains(id)?1:0));
//		if (id != 0) {
//			if (onResponseMap.contains(id)) {
//				auto fn = onResponseMap[id];
//				//log("call onResponse\n");
//				fn(result);
//
//				onResponseMap.erase(onResponseMap.find(id));
//				log(std::format("remain onResponseMap size:{}\n", onResponseMap.size()));
//			}
//		}
//		return;
//	}
//
//	json params = jo.contains("params") ? jo["params"] : json::object();
//	log(std::format("route. id:{}, method:{}, params:{}\n", id, method, params.dump(4)));
//
//	if (initialize(id, method, params)) return;
//	if (initialized(id, method, params)) return;
//	if (didOpen(id, method, params)) return;
//	if (documentSymbol(id, method, params)) return;
//	if (completion(id, method, params)) return;
//	if (didChange(id, method, params)) return;
//	if (hover(id, method, params)) return;
//	if (gotoDefinition(id, method, params)) return;
//	if (codeAction(id, method, params)) return;
//	if (executeCommand(id, method, params)) return;
//
//
//	{
//		json result = json::object();
//		writeResponse(result, id);
//	}
//}
std::string parseJsonRpc(std::string s) {
	auto idx = s.find("\n");
	if (idx == std::string::npos) {
		return s;
	}
	if (idx > 0 && s[idx - 1] == '\r') {
		newline = 2;
	}
	//Content-Length:
	int rn = newline * 2;
	int length = 0;
	sscanf(s.c_str() + 16, "%d", &length);
	if (s.size() >= idx + rn && length <= s.size() - idx - rn) {
		//log(std::format(" len={}, idx:{}, size:{}\n", length, idx, s.size()));
		auto content = s.substr(idx + rn, length);
		auto remain = s.substr(length + idx + rn);
		//log(std::format("recv msg. len={}, content:{}. \n remain size:{}\n", length, content, remain.size()));

		//json jo = json::parse(content);
		//route(jo);
		auto mail = std::make_shared<LspMail>();
		mail->jo = json::parse(content);
		lspActor->pushMail(mail);

		return remain;
		//return s.substr(idx + 2 + length);
	}
	//log(std::format("recv content-length:{}", length));
	return s;
}


void OrcLsp::run()
{
	initActors();

	//FreeConsole();
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	//SetConsoleOutputCP(65001);
	std::string s;
	log(std::format("start orclsp\n"));
	while (true) {
		char c = getchar();
		//printf("c:%c %d\n", c, c);
		//if (1) continue;
		//log(std::format("{}", c));
		s += c;
		//log(std::format("{}", c));

		s = parseJsonRpc(s);
	}

}
