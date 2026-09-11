// Converted from ShellExt.ixx (C++20 module) to classic header/source.
#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <string>
#include <vector>
#include <Shlobj.h>

namespace shellExt {

std::wstring toWstr(const std::string& s);

bool registerFileType(LPCWSTR ext, LPCWSTR menuLabel, LPCWSTR exePath);

bool unregisterFileType(LPCWSTR ext);

void registerShellMenu(const std::string& exePath);

void unregisterShellMenu();

}
