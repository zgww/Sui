#pragma once

#include <string>
#include <memory>
#include <windows.h>
#include <functional>

class FsWatchEvent {
public:
	//add|remove|modify|rename
	std::string action;
	std::string path;
	std::string oldPath;//for rename
};



class FsWatch {
public:
	std::string watchDir = "./";
	std::function<void(std::shared_ptr<FsWatchEvent>)> onEvent;
	virtual int start() = 0;
	virtual ~FsWatch() {};

	static std::shared_ptr<FsWatch> createInstance();
};

