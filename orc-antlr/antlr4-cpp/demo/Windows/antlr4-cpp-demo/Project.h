#pragma once

#include "Symbol.h"
#include "FsWatcher.h"

#include <vector>

#include <mutex>

class ProjectLoadRequest {
public:
	// unload|build
	std::string action;
	std::string path; //绝对路径
	uint64_t actAtUnixMs;
};

class Project
{
public:
	std::shared_ptr<SymbolSpaceLoader> symbolSpaceLoader = std::make_shared<SymbolSpaceLoader>();
	std::shared_ptr<FsWatch> fsWatch = FsWatch::createInstance();

	void watch(std::string dir);
	void onWatchEvent(std::shared_ptr<FsWatchEvent> ev);

	bool compile(std::string absPath);
	void recompileAll();

	std::vector<ProjectLoadRequest> loadPathQueue;

	void pushPathQueue(std::string action, std::string fullpath);

	std::mutex pathQueueMutex;
};

