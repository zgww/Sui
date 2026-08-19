#include "Clipboard.h"

#ifdef _WIN32
#include <windows.h>

void Clipboard_setText(const char* text) {
	if (!OpenClipboard(nullptr)) return;
	EmptyClipboard();
	int wlen = MultiByteToWideChar(CP_UTF8, 0, text, -1, nullptr, 0);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, wlen * sizeof(WCHAR));
	if (hMem) {
		WCHAR* p = (WCHAR*)GlobalLock(hMem);
		MultiByteToWideChar(CP_UTF8, 0, text, -1, p, wlen);
		GlobalUnlock(hMem);
		SetClipboardData(CF_UNICODETEXT, hMem);
	}
	CloseClipboard();
}

std::string Clipboard_getText() {
	if (!OpenClipboard(nullptr)) return "";
	HANDLE h = GetClipboardData(CF_UNICODETEXT);
	if (!h) { CloseClipboard(); return ""; }
	WCHAR* p = (WCHAR*)GlobalLock(h);
	std::string result;
	if (p) {
		int alen = WideCharToMultiByte(CP_UTF8, 0, p, -1, nullptr, 0, nullptr, nullptr);
		if (alen > 0) {
			result.resize(alen - 1);
			WideCharToMultiByte(CP_UTF8, 0, p, -1, &result[0], alen, nullptr, nullptr);
		}
		GlobalUnlock(h);
	}
	CloseClipboard();
	return result;
}
#else
void Clipboard_setText(const char* text) {}
std::string Clipboard_getText() { return ""; }
#endif
