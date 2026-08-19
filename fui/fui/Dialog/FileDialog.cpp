#include "FileDialog.h"

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>

std::vector<std::string> FileDialog_getOpenFileName(const char* dir, const char* title) {
	std::vector<std::string> result;
	OPENFILENAMEW ofn = {0};
	wchar_t szFile[MAX_PATH * 32] = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH * 32;
	ofn.lpstrFilter = L"All Files\0*.*\0\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

	wchar_t wtitle[256] = {0};
	wchar_t wdir[MAX_PATH] = {0};
	if (title) MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, 256);
	if (dir) MultiByteToWideChar(CP_UTF8, 0, dir, -1, wdir, MAX_PATH);
	ofn.lpstrTitle = wtitle;
	ofn.lpstrInitialDir = wdir[0] ? wdir : nullptr;

	if (GetOpenFileNameW(&ofn)) {
		std::wstring ws(szFile);
		if (ws.empty()) return result;

		std::wstring path = ws;
		size_t pos = 0;
		bool first = true;
		std::wstring basePath;

		size_t nulPos = ws.find(L'\0');
		if (nulPos == std::wstring::npos || nulPos == ws.length() - 1) {
			int alen = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
			if (alen > 0) {
				std::string s(alen - 1, '\0');
				WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, &s[0], alen, nullptr, nullptr);
				result.push_back(s);
			}
		} else {
			basePath = ws.substr(0, nulPos);
			size_t start = nulPos + 1;
			while (start < ws.length()) {
				size_t end = ws.find(L'\0', start);
				if (end == std::wstring::npos) end = ws.length();
				std::wstring file = ws.substr(start, end - start);
				if (!file.empty()) {
					std::wstring full = basePath + L"\\" + file;
					int alen = WideCharToMultiByte(CP_UTF8, 0, full.c_str(), -1, nullptr, 0, nullptr, nullptr);
					if (alen > 0) {
						std::string s(alen - 1, '\0');
						WideCharToMultiByte(CP_UTF8, 0, full.c_str(), -1, &s[0], alen, nullptr, nullptr);
						result.push_back(s);
					}
				}
				start = end + 1;
				if (start >= ws.length()) break;
			}
			if (result.empty()) {
				int alen = WideCharToMultiByte(CP_UTF8, 0, basePath.c_str(), -1, nullptr, 0, nullptr, nullptr);
				if (alen > 0) {
					std::string s(alen - 1, '\0');
					WideCharToMultiByte(CP_UTF8, 0, basePath.c_str(), -1, &s[0], alen, nullptr, nullptr);
					result.push_back(s);
				}
			}
		}
	}
	return result;
}

std::string FileDialog_getFirstOpenFileName(const char* dir, const char* title) {
	auto list = FileDialog_getOpenFileName(dir, title);
	if (!list.empty()) return list[0];
	return "";
}

std::string FileDialog_getSaveFileName(const char* dir, const char* title) {
	OPENFILENAMEW ofn = {0};
	wchar_t szFile[MAX_PATH] = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"All Files\0*.*\0\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

	wchar_t wtitle[256] = {0};
	wchar_t wdir[MAX_PATH] = {0};
	if (title) MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, 256);
	if (dir) MultiByteToWideChar(CP_UTF8, 0, dir, -1, wdir, MAX_PATH);
	ofn.lpstrTitle = wtitle;
	ofn.lpstrInitialDir = wdir[0] ? wdir : nullptr;

	if (GetSaveFileNameW(&ofn)) {
		int alen = WideCharToMultiByte(CP_UTF8, 0, szFile, -1, nullptr, 0, nullptr, nullptr);
		if (alen > 0) {
			std::string s(alen - 1, '\0');
			WideCharToMultiByte(CP_UTF8, 0, szFile, -1, &s[0], alen, nullptr, nullptr);
			return s;
		}
	}
	return "";
}

std::string FileDialog_getExistingDirectory(const char* dir, const char* title) {
	wchar_t wtitle[256] = {0};
	wchar_t wdir[MAX_PATH] = {0};
	if (title) MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, 256);
	if (dir) MultiByteToWideChar(CP_UTF8, 0, dir, -1, wdir, MAX_PATH);

	BROWSEINFOW bi = {0};
	bi.hwndOwner = nullptr;
	bi.pszDisplayName = wdir;
	bi.lpszTitle = wtitle[0] ? wtitle : nullptr;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;

	LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);
	if (pidl) {
		wchar_t path[MAX_PATH] = {0};
		if (SHGetPathFromIDListW(pidl, path)) {
			CoTaskMemFree(pidl);
			int alen = WideCharToMultiByte(CP_UTF8, 0, path, -1, nullptr, 0, nullptr, nullptr);
			if (alen > 0) {
				std::string s(alen - 1, '\0');
				WideCharToMultiByte(CP_UTF8, 0, path, -1, &s[0], alen, nullptr, nullptr);
				return s;
			}
		}
		CoTaskMemFree(pidl);
	}
	return "";
}
#else
std::vector<std::string> FileDialog_getOpenFileName(const char* dir, const char* title) { return {}; }
std::string FileDialog_getFirstOpenFileName(const char* dir, const char* title) { return ""; }
std::string FileDialog_getSaveFileName(const char* dir, const char* title) { return ""; }
std::string FileDialog_getExistingDirectory(const char* dir, const char* title) { return ""; }
#endif
