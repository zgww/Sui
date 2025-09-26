#include "./FileDialog_orc.h"


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <string>


#include <Naga/StrUtil.h>
#include <Naga/Utf8Util.h>

Orc$List* SuiDialog$fileDialog_getOpenFileName(Orc$List** __outRef__, char const* dir, char const* title) {
	wchar_t szFile[1024] = L"";
	//auto win = App::ins()->windowMgr->windows->get(0);
	//auto hwnd = win->hwnd; // win ? win->get_wm_info().info.win.window : NULL;

	//dir = "c:/ws/far";
	AutoFree<char*> dupdir = StrUtil_replace_by_re(dir, "/", "\\");

	OPENFILENAMEW param = { 0 };
	param.lStructSize = sizeof(param);
	param.hwndOwner = NULL;
	param.lpstrFile = szFile;
	param.nMaxFile = sizeof(szFile);
	param.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	param.nFilterIndex = 1;
	param.lpstrFileTitle = NULL;
	param.nMaxFileTitle = 0;
	AutoFree<wchar_t*> wtitle = new_Utf8Util_toutf16(title);
	AutoFree<wchar_t*> wdir = new_Utf8Util_toutf16(dupdir.data);
	param.lpstrTitle = std::string(title) == "" ? NULL : wtitle.data;// "thisis title";
	param.lpstrInitialDir = wdir.data;
	param.Flags = OFN_NOVALIDATE
		| OFN_PATHMUSTEXIST
		//| OFN_FILEMUSTEXIST
		;

	NEW_CLASS_VAR( Orc$List, list );

	if (GetOpenFileNameW(&param)) {

		printf("打开文件:%ws\n", param.lpstrFile);
		//vector<string> names;
		//names.push_back(new_Utf8Util_toutf8(param.lpstrFile));
		char* utf8 = new_Utf8Util_toutf8(param.lpstrFile);
		NEW_CLASS_VAR(Orc$String, string);
		Orc$String$add(string, utf8);
		free(utf8);

		list->add(list, (Object*)string);
	}

	return (Orc$List*)urgc_set_var_for_return((void**)__outRef__, (void*)list);
	//auto err = CommDlgExtendedError();
}
Orc$String* SuiDialog$fileDialog_getSaveFileName(Orc$String** __outRef__, char const* dir, char const* title) {
	wchar_t szFile[1024] = L"";
	//auto win = App::ins()->windowMgr->windows->get(0);
	//auto hwnd = win->hwnd;// win ? win->get_wm_info().info.win.window : NULL;

	//dir = "c:/ws/far";
	AutoFree<char*> dupdir ( StrUtil_replace_by_re(dir, "/", "\\"));


	OPENFILENAMEW param = { 0 };
	param.lStructSize = sizeof(param);
	param.hwndOwner = NULL;
	param.lpstrFile = szFile;
	param.nMaxFile = sizeof(szFile);
	param.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	param.nFilterIndex = 1;
	param.lpstrFileTitle = NULL;
	param.nMaxFileTitle = 0;

	AutoFree<wchar_t*> wtitle = new_Utf8Util_toutf16(title);
	AutoFree<wchar_t*> wdir = new_Utf8Util_toutf16(dir);
	param.lpstrTitle = std::string(title) == "" ? NULL : wtitle.data;// "thisis title";

	param.lpstrInitialDir = wdir.data;
	param.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetSaveFileNameW(&param)) {
		printf("保存文件到:%ws\n", param.lpstrFile);
		AutoFree<char*> utf8 = new_Utf8Util_toutf8(param.lpstrFile);

		NEW_CLASS_VAR(Orc$String, ret);
		Orc$String$add(ret, utf8.data);
		return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, (void*)ret);
	}
	return NULL;
}
Orc$String * SuiDialog$fileDialog_getExistingDirectory(Orc$String * *__outRef__, char const* dir, char const* title) {
	////CoInitialize( NULL );
	AutoFree<wchar_t*> wtitle = new_Utf8Util_toutf16(title);

	AutoFree<wchar_t*> buffer = new wchar_t[1024];
	BROWSEINFOW bi = { 0 };
	bi.hwndOwner = NULL;
	bi.pszDisplayName = buffer.data;
	bi.lpszTitle = std::string(title).empty() ? NULL : wtitle.data;
	bi.ulFlags = BIF_USENEWUI;
	LPITEMIDLIST idl = SHBrowseForFolderW(&bi);
	if (idl != NULL) {
		if (SHGetPathFromIDListW(idl, buffer.data)) {
			AutoFree<char*> utf8 = new_Utf8Util_toutf8(buffer.data);

			NEW_CLASS_VAR(Orc$String, ret);
			Orc$String$add(ret, utf8.data);
			return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, (void*)ret);
		}
	}
	return NULL;
}
extern "C" void testFileDialog() {
	SuiDialog$fileDialog_getExistingDirectory(NULL, "./", "标题自定义的");

}