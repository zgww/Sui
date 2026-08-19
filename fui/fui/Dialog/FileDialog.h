#pragma once

#include "../Core/Predef.h"
#include <string>
#include <vector>

class FileDialog {
public:
	virtual const char* getClassName() const { return "FileDialog"; }
};

std::vector<std::string> FileDialog_getOpenFileName(const char* dir, const char* title);
std::string FileDialog_getFirstOpenFileName(const char* dir, const char* title);
std::string FileDialog_getSaveFileName(const char* dir, const char* title);
std::string FileDialog_getExistingDirectory(const char* dir, const char* title);
