
#define _CRT_SECURE_NO_WARNINGS

#include "./Path_orc.h"
#include "Naga/Utf8Util.h"
#include "Naga/FsUtil.h"

#include <string>
#include <filesystem>

static std::wstring toutf16(const char* path) {
	wchar_t* tmp = new_Utf8Util_toutf16(path);
	std::wstring ret(tmp);
	free(tmp);
	return ret;
}
static std::string toutf8(std::wstring wstr) {
	char* tmp = new_Utf8Util_toutf8(wstr.c_str());
	std::string ret(tmp);
	free(tmp);
	return ret;
}
static std::string toacp(const char *path){
    char *tmp = new_Utf8Util_utf8_to_active_code_page(path);
    std::string ret(tmp);
    free(tmp);
    return ret;
}

bool OrcLang$Path_isDirectory(char const * path){
    std::filesystem::path p(toutf16(path));
    auto ret = std::filesystem::is_directory(p);
    return ret;
    // _dirType = ret ? 1 : 0;
}
bool OrcLang$Path_mkdirs(char const * dirpath){
	std::filesystem::path p(toutf16(dirpath));
	bool ret = std::filesystem::create_directories(p);
	return ret;
}
bool OrcLang$Path_exists(char const * path){
	std::filesystem::path p(toutf16(path));
	bool ret = std::filesystem::exists(p);
    return ret;
}
bool OrcLang$Path_copyTo(char const * src, char const * dst){
	std::filesystem::path p(toutf16(src));
	std::filesystem::path np(toutf16(dst));
	std::filesystem::copy(p, np);
	return true;
}
bool OrcLang$Path_rename(char const * src, char const * dst){
	std::filesystem::path p(toutf16(src));
	std::filesystem::path np(toutf16(dst));
	std::filesystem::rename(p, np);
	return true;
}
bool OrcLang$Path_remove(char const * src){
	std::filesystem::path p(toutf16(src));
	std::filesystem::remove_all(p);
	return true;
}
bool OrcLang$Path_removeDir(char const * src){
	if (OrcLang$Path_isDirectory(src)) {
		std::filesystem::path p(toutf16(src));
		std::filesystem::remove(p);
	}
	return true;
}
bool OrcLang$Path_removeDirs(char const * src){
	if (OrcLang$Path_isDirectory(src)) {
		std::filesystem::path p(toutf16(src));
		std::filesystem::remove_all(p);
	}
	return true;

}
bool OrcLang$Path_removeFile(char const * src){
	if (OrcLang$Path_isFile(src)) {
		std::filesystem::path p(toutf16(src));
		std::filesystem::remove(p);
	}
	return true;
}
bool OrcLang$Path_touch(char const * src){
	if (!OrcLang$Path_exists(src)) {
        auto acpPath = toacp(src);
		auto f = ::fopen(acpPath.c_str(), "w+");
		fclose(f);
	}
	return true;
}
bool OrcLang$Path_fopen(char const * src, const char *mode){
	auto acpPath = toacp(src);
	auto f = ::fopen(acpPath.c_str(), mode);//"w+");
	return f;

}
// bool OrcLang$Path_copyToDir(char const * src, char const * dir){
// 	if (! OrcLang$Path_isDirectory(dir)) {
// 		return false;
// 	}
// 	auto newPath = dir.append(basename());
// 	if (newPath.exists()) {
// 		return false;
// 	}
// 	bool ret = OrcLang$Path_copyTo(src, newPath);
// 	return ret;
// }
// bool OrcLang$Path_moveToDir(char const * src, char const * dir){

// }
OrcLang$List* OrcLang$Path_list(OrcLang$List * * __outRef__, char const * path){
	OrcLang$List* list = OrcLang$List_new();
	std::filesystem::path p(toutf16(path));
	if (std::filesystem::exists(p)) {
		for (auto& it : std::filesystem::directory_iterator(p)) {
			auto kidPath = toutf8(it.path().wstring());
			URGC_VAR_CLEANUP OrcLang$String* ret = NULL;// OrcLang$String_new();
			OrcLang$Path_normal(&ret, kidPath.c_str());
			//ret->add(ret, kidPath.c_str());
			list->add(list, (Object*)ret);
		}

	}
	return (OrcLang$List*)urgc_set_var_for_return((void**)__outRef__, list);
}
OrcLang$String* OrcLang$Path_getcwd(OrcLang$String * * __outRef__){
    auto cp = std::filesystem::current_path();
	std::string utf8str = toutf8(cp.wstring());
    OrcLang$String *ret = OrcLang$String_new();

    // char *s = new_FsUtil_getcwd();
    ret->add(ret, utf8str.c_str());
    // free(s);

	return (OrcLang$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}
void OrcLang$Path_setcwd(OrcLang$String * * __outRef__, char const * path){
	std::filesystem::path p(toutf16(path));
	std::filesystem::current_path(p);
}
OrcLang$String* OrcLang$Path_getExecutionPath(OrcLang$String * * __outRef__){
    OrcLang$String *ret = OrcLang$String_new();

    char *s = new_FsUtil_getExecutionPath();
    ret->set_as_own(ret, s);

	return (OrcLang$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}

void myfree(void *p) {
	free(p);
}
//char* new_read_all_text(const char* path2, const char* flag) {
//	__attribute__((cleanup(myfree))) char* path = new_Utf8Util_utf8_to_active_code_page(path2);
//	//if (text_cache.find(path) != text_cache.end()) {
//	//	return text_cache[path];
//	//}
//
//	FILE* f = fopen(path, flag);
//	if (f == NULL) {
//		return _strdup("");
//	}
//	if (true) {
//		return NULL;
//	}
//	char buf[10240] = { 0 };
//	std::string content;
//	while (!feof(f)) {
//		int cnt = fread(buf, 1, sizeof(buf) - 1, f);
//		buf[cnt] = 0;
//
//		content += buf;
//	}
//	fclose(f);
//	//text_cache[path] = content;
//	char* ret = _strdup(content.c_str());
//	return ret;
//}
OrcLang$String* OrcLang$Path_readText(OrcLang$String * * __outRef__, char const * path){
    OrcLang$String *ret = OrcLang$String_new();
	char *s = new_FsUtil_read_all_text(path, "r");



	ret->set_as_own(ret, s);

	return (OrcLang$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}
void OrcLang$Path_writeText(char const * path, char const * text){
	FsUtil_write_all_text(path, text, "w+");
}