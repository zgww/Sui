module;
#include <Windows.h>
#include <string>
#include <vector>
#include <Shlobj.h>

export module ShellExt;

export namespace shellExt {

inline std::wstring toWstr(const std::string& s) {
	int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
	std::wstring w(len, 0);
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, w.data(), len);
	if (len > 0) w.pop_back();
	return w;
}

inline bool registerFileType(LPCWSTR ext, LPCWSTR menuLabel, LPCWSTR exePath) {
	// HKCU\Software\Classes\SystemFileAssociations\.ext\shell\ImageViewer
	std::wstring baseKey = L"Software\\Classes\\SystemFileAssociations\\";
	baseKey += ext;
	baseKey += L"\\shell\\ImageViewer";

	HKEY hMenuKey = nullptr;
	if (RegCreateKeyExW(HKEY_CURRENT_USER, baseKey.c_str(), 0, nullptr, 0,
		KEY_WRITE, nullptr, &hMenuKey, nullptr) != ERROR_SUCCESS) return false;

	// Set menu display name
	RegSetValueExW(hMenuKey, nullptr, 0, REG_SZ, (const BYTE*)menuLabel,
		(DWORD)((wcslen(menuLabel) + 1) * sizeof(wchar_t)));

	// command subkey
	HKEY hCmdKey = nullptr;
	if (RegCreateKeyExW(hMenuKey, L"command", 0, nullptr, 0,
		KEY_WRITE, nullptr, &hCmdKey, nullptr) != ERROR_SUCCESS) {
		RegCloseKey(hMenuKey);
		return false;
	}

	std::wstring cmdLine = std::wstring(L"\"") + exePath + L"\" \"%1\"";
	RegSetValueExW(hCmdKey, nullptr, 0, REG_SZ, (const BYTE*)cmdLine.c_str(),
		(DWORD)((cmdLine.size() + 1) * sizeof(wchar_t)));

	RegCloseKey(hCmdKey);
	RegCloseKey(hMenuKey);
	return true;
}

inline bool unregisterFileType(LPCWSTR ext) {
	std::wstring baseKey = L"Software\\Classes\\SystemFileAssociations\\";
	baseKey += ext;
	baseKey += L"\\shell";

	HKEY hShellKey = nullptr;
	if (RegOpenKeyExW(HKEY_CURRENT_USER, baseKey.c_str(), 0, KEY_WRITE, &hShellKey) == ERROR_SUCCESS) {
		// Delete command subkey first, then the menu key
		HKEY hMenuKey = nullptr;
		if (RegOpenKeyExW(hShellKey, L"ImageViewer", 0, KEY_WRITE, &hMenuKey) == ERROR_SUCCESS) {
			RegDeleteKeyW(hMenuKey, L"command");
			RegCloseKey(hMenuKey);
		}
		RegDeleteKeyW(hShellKey, L"ImageViewer");
		RegCloseKey(hShellKey);
		return true;
	}
	return false;
}

inline void registerShellMenu(const std::string& exePath) {
	auto wpath = toWstr(exePath);
	LPCWSTR menuLabel = L"用 ImageViewer 打开";
	LPCWSTR exts[] = {
		L".jpg", L".jpeg", L".png", L".bmp", L".gif",
		L".webp", L".tga", L".tiff", L".tif", L".ico", L".psd"
	};
	for (auto ext : exts) {
		registerFileType(ext, menuLabel, wpath.c_str());
	}
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
}

inline void unregisterShellMenu() {
	LPCWSTR exts[] = {
		L".jpg", L".jpeg", L".png", L".bmp", L".gif",
		L".webp", L".tga", L".tiff", L".tif", L".ico", L".psd"
	};
	for (auto ext : exts) {
		unregisterFileType(ext);
	}
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
}

}
