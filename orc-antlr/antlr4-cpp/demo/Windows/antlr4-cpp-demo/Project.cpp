#define _CRT_SECURE_NO_WARNINGS

#include "Project.h"
#include <chrono>
#include <thread>
#include <FsUtil.h>
#include "antlr4-runtime.h"
#include "OrcLexer.h"
#include "OrcParser.h"
#include "OrcBaseVisitor.h"
#include "Symbol.h"
#include <windows.h>
#include "resource.h"
#include <ReturnStringVisitor.h>
#include "Utf8Util.h"

#pragma execution_character_set("utf-8")

using namespace antlrcpptest;
using namespace antlr4;

// tray icon data
NOTIFYICONDATA m_NID;

BOOL CreateTrayIcon()
{
	memset(&m_NID, 0, sizeof(m_NID));
	m_NID.cbSize = sizeof(m_NID);

	m_NID.uID = IDI_ICON_MY;

	// set handle to the window that receives tray icon notifications
	m_NID.hWnd = GetForegroundWindow();

	// fields that are being set when adding tray icon 
	m_NID.uFlags = NIF_MESSAGE | NIF_ICON;
	//auto icon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));
	auto hInstance = GetModuleHandle(NULL);
	auto icon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON_MY);

	auto exePath = FsUtil::getExecutionPath();
	auto exeDir = Path(exePath).dirname().append("icon1.ico")._wpath;
	//auto icon2 = (HICON)LoadImage(NULL, exeDir.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	// set image
	m_NID.hIcon = icon;

	if (!m_NID.hIcon)
		return FALSE;

	m_NID.uVersion = NOTIFYICON_VERSION_4;

	if (!Shell_NotifyIcon(NIM_ADD, &m_NID))
		return FALSE;

	return Shell_NotifyIcon(NIM_SETVERSION, &m_NID);
}

BOOL ShowTrayIconBalloon(LPCTSTR pszTitle, LPCTSTR pszText, UINT unTimeout, DWORD dwInfoFlags)
{
	m_NID.uFlags |= NIF_INFO;
	m_NID.uTimeout = unTimeout;
	m_NID.dwInfoFlags = dwInfoFlags;
	wcsncpy(m_NID.szInfoTitle, pszTitle, sizeof(m_NID.szInfoTitle) / 2);
	wcsncpy(m_NID.szInfo, pszText, sizeof(m_NID.szInfo) / 2);

	return Shell_NotifyIcon(NIM_MODIFY, &m_NID);
}
void Project::watch(std::string dir)
{
	std::thread t([&]() {
		this->fsWatch->watchDir = dir;
		this->fsWatch->onEvent = [&](std::shared_ptr<FsWatchEvent> ev) {
			this->onWatchEvent(ev);
			};
		this->fsWatch->start();
	});
	t.detach();

	CreateTrayIcon();
	while (true) {
		std::vector<ProjectLoadRequest> reqs;
		{//取出要处理的请求，防止占用锁太多
			
			std::lock_guard<std::mutex> g(pathQueueMutex);

			auto now = std::chrono::system_clock::now().time_since_epoch();
			uint64_t nowUnixMs = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
		
			for (int i = 0; i < loadPathQueue.size(); i++) {
				auto& req = loadPathQueue[i];
				//吉时已到
				if (req.actAtUnixMs <= nowUnixMs) {
					//
					reqs.push_back(req);
					loadPathQueue.erase(loadPathQueue.begin() + i);
					i--;
				}
			}
		}
		//开始处理

		for (auto& req : reqs) {
			if (req.action == "unload") {
				symbolSpaceLoader->unload(req.path);
			}
			else if (req.action == "build") {
				printf("监听到文件变化，开始加载:%s\n", req.path.c_str());
				//symbolSpaceLoader->unload(req.path);
				//symbolSpaceLoader->load_orcModule(req.path);

				try {
					auto succ = compile(req.path);
					auto tip = std::wstring(succ ?  L"O 编译成功:" : L"X 编译失败") + Path(req.path)._wpath;
					ShowTrayIconBalloon(L"提示", tip.c_str(), 200, NULL);
				}
				catch (std::exception e) {
					printf("编译异常. path=%s, err:%s\n", req.path.c_str(), e.what());
					auto tip = std::wstring(L"X 编译失败:") + Path(req.path)._wpath;
					ShowTrayIconBalloon(L"提示", tip.c_str(), 1000, NULL);
				}
				catch (std::string msg) {
					printf("编译异常. path=%s, msg:%s\n", req.path.c_str(), msg.c_str());
					auto tip = std::wstring(L"X 编译失败:") + Path(req.path)._wpath + std::wstring(L" msg:") + Utf8Util::toutf16(msg);
					ShowTrayIconBalloon(L"提示", tip.c_str(), 1000, NULL);
				}
				catch (...) {
					printf("编译异常. path=%s, 未知错误类型\n", req.path.c_str());
					auto tip = std::wstring(L"X 编译失败:") + Path(req.path)._wpath;
					ShowTrayIconBalloon(L"提示", tip.c_str(), 1000, NULL);
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void Project::onWatchEvent(std::shared_ptr<FsWatchEvent> ev)
{
	auto act = ev->action;
	if (ev->path.ends_with(".orc")) {
		auto fullpath = Path( fsWatch->watchDir).append(ev->path).normal().path();
		//printf("file watch. fullpath:%s\n", fullpath.c_str());
		if (act == "add") {
			//symbolSpaceLoader->load(fullpath);
			//pushPathQueue(fullpath);
			pushPathQueue("build", fullpath);
		}
		else if (act == "remove") {
			//symbolSpaceLoader->unload(fullpath);
			//pushPathQueue("", fullpath);
			pushPathQueue("unload", fullpath);
		}
		else if (act == "modify") {
			//symbolSpaceLoader->unload(ev->path);
			//symbolSpaceLoader->load(fullpath);
			pushPathQueue("build", fullpath);
		}
		else if (act == "rename") {
			auto oldFullpath = fsWatch->watchDir + ev->oldPath;
		/*	symbolSpaceLoader->unload(oldFullpath);
			symbolSpaceLoader->load(fullpath);*/

			pushPathQueue("unload", oldFullpath);
			pushPathQueue("build", fullpath);
		}
	}

}

//编译文件
bool Project::compile(std::string absPath) {
	CostUs cost;
	auto code = FsUtil::read_all_text(absPath);
	cost.stat("read code");
	//printf("compile %s code:\n%s\n\n", absPath.c_str(), code.c_str());
	//printf("compile %s code:\n\n", absPath.c_str());


	std::shared_ptr<ANTLRInputStream> input;
	std::shared_ptr<OrcLexer> lexer;
	std::shared_ptr<CommonTokenStream> tokens;
	std::shared_ptr<OrcParser> parser;


	input = std::make_shared<ANTLRInputStream>(code);
	lexer = std::make_shared<OrcLexer>(input.get());
	tokens = std::make_shared<CommonTokenStream>(lexer.get());


	parser = std::make_shared<OrcParser>(tokens.get());

	cost.stat("create tokenstream");

	auto tree = parser->program();
	cost.stat("program");

	auto space = std::make_shared<SymbolSpace>();
	space->symbolSpaceLoader = symbolSpaceLoader;
	space->path = absPath;

	auto ok = space->startBuild(absPath, tree, parser, cost);
	cost.stat("startBuild");
	if (ok) {
		//注册缓存
		symbolSpaceLoader->lib[absPath] = space;

		//保存符号文件
		symbolSpaceLoader->saveSymbolFile_forOrc(absPath, space.get());
		cost.stat("saveSymbolFile_forOrc");
	}
	cost.print("compile");
	return ok;
}

void Project::recompileAll()
{
	std::vector<std::string> donePaths;
	std::vector<std::string> failPaths;
	try {

		Path p(".");
		auto paths = p.listSubtree();
		//allPaths = paths;
		for (auto& path : paths) {
			if (path.ends_with(".orc")) {

				if (compile(path)) {
					donePaths.push_back(path);
				}
				else {
					compile(path);
					failPaths.push_back(path);
				}
				//allPaths.erase(std::find(allPaths.begin(), allPaths.end(), path));
			}
		}
	}
	catch (std::string msg) {
		printf("recompile all error. msg:%s\n", msg.c_str());
	}
	catch (...) {
		printf("recompile all error\n");
	}
	printf("=========done===========\n");
	for (auto p : donePaths) {
		printf("o\t%s\n", p.c_str());
	}
	printf("=========fail===========\n");
	for (auto p : failPaths) {
		printf("x\t%s\n", p.c_str());
	}
}

void Project::pushPathQueue(std::string action, std::string fullpath)
{
	std::lock_guard<std::mutex> g(pathQueueMutex);

	auto now = std::chrono::system_clock::now().time_since_epoch();
	auto actAtUnixMs = std::chrono::duration_cast<std::chrono::milliseconds>(now).count()
		
		+ 30;

	//已存在，更新动作时间即可
	for (auto& req : loadPathQueue) {
		if (req.action == action && req.path == fullpath) {
			printf("update req:%s %s\n", action.c_str(), fullpath.c_str());
			req.actAtUnixMs = actAtUnixMs;
			return;
		}
	}
	printf("push req:%s %s\n", action.c_str(), fullpath.c_str());

	ProjectLoadRequest req;
	req.path = fullpath;
	req.action = action;
	req.actAtUnixMs = actAtUnixMs;
	loadPathQueue.push_back(req);
}

