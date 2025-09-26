
#include "Orc/Orc.h"
#include <chrono>
#include <ratio>
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

bool Orc$Path_isDirectory(char const * path){
    std::filesystem::path p(toutf16(path));
    auto ret = std::filesystem::is_directory(p);
    return ret;
    // _dirType = ret ? 1 : 0;
}
bool Orc$Path_mkdirs(char const * dirpath){
	std::filesystem::path p(toutf16(dirpath));
	bool ret = std::filesystem::create_directories(p);
	return ret;
}
bool Orc$Path_exists(char const * path){
	std::filesystem::path p(toutf16(path));
	bool ret = std::filesystem::exists(p);
    return ret;
}
bool Orc$Path_copyTo(char const * src, char const * dst){
	std::filesystem::path p(toutf16(src));
	std::filesystem::path np(toutf16(dst));
	std::filesystem::copy(p, np);
	return true;
}
bool Orc$Path_rename(char const * src, char const * dst){
	std::filesystem::path p(toutf16(src));
	std::filesystem::path np(toutf16(dst));
	std::filesystem::rename(p, np);
	return true;
}
bool Orc$Path_remove(char const * src){
	std::filesystem::path p(toutf16(src));
	std::filesystem::remove_all(p);
	return true;
}
bool Orc$Path_removeDir(char const * src){
	if (Orc$Path_isDirectory(src)) {
		std::filesystem::path p(toutf16(src));
		std::filesystem::remove(p);
	}
	return true;
}
bool Orc$Path_removeDirs(char const * src){
	if (Orc$Path_isDirectory(src)) {
		std::filesystem::path p(toutf16(src));
		std::filesystem::remove_all(p);
	}
	return true;

}
bool Orc$Path_removeFile(char const * src){
	if (Orc$Path_isFile(src)) {
		std::filesystem::path p(toutf16(src));
		std::filesystem::remove(p);
	}
	return true;
}
bool Orc$Path_touch(char const * src){
	if (!Orc$Path_exists(src)) {
        auto acpPath = toacp(src);
		auto f = ::fopen(acpPath.c_str(), "w+");
		fclose(f);
	}
	return true;
}
bool Orc$Path_fopen(char const * src, const char *mode){
	auto acpPath = toacp(src);
	auto f = ::fopen(acpPath.c_str(), mode);//"w+");
	return f;

}
// bool Orc$Path_copyToDir(char const * src, char const * dir){
// 	if (! Orc$Path_isDirectory(dir)) {
// 		return false;
// 	}
// 	auto newPath = dir.append(basename());
// 	if (newPath.exists()) {
// 		return false;
// 	}
// 	bool ret = Orc$Path_copyTo(src, newPath);
// 	return ret;
// }
// bool Orc$Path_moveToDir(char const * src, char const * dir){

// }
Orc$List* Orc$Path_list(Orc$List * * __outRef__, char const * path){
	NEW_CLASS_VAR(Orc$List, list);
	std::filesystem::path p(toutf16(path));
	if (std::filesystem::exists(p)) {
		for (auto& it : std::filesystem::directory_iterator(p)) {
			auto kidPath = toutf8(it.path().wstring());
			URGC_VAR_CLEANUP Orc$String* ret = NULL;// Orc$String_new();
			Orc$Path_normal(&ret, kidPath.c_str());
			//ret->add(ret, kidPath.c_str());
			list->add(list, (Object*)ret);
		}

	}
	return (Orc$List*)urgc_set_var_for_return((void**)__outRef__, list);
}
Orc$String* Orc$Path_getcwd(Orc$String * * __outRef__){
    auto cp = std::filesystem::current_path();
	std::string utf8str = toutf8(cp.wstring());
	NEW_CLASS_VAR(Orc$String, ret);

    // char *s = new_FsUtil_getcwd();
    Orc$String$add(ret, utf8str.c_str());
    // free(s);

	return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}
void Orc$Path_setcwd(char const * path){
	std::filesystem::path p(toutf16(path));
	std::filesystem::current_path(p);
}
Orc$String* Orc$Path_getExecutionPath(Orc$String * * __outRef__){
	NEW_CLASS_VAR(Orc$String, ret);

    char *s = new_FsUtil_getExecutionPath();
    Orc$String$set_as_own(ret, s);

	return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, ret);
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
Orc$String* Orc$Path_readText(Orc$String * * __outRef__, char const * path){
	NEW_CLASS_VAR(Orc$String, ret);
	char *s = new_FsUtil_read_all_text(path, "r");



	Orc$String$set_as_own(ret, s);

	return (Orc$String*)urgc_set_var_for_return((void**)__outRef__, ret);
}
bool Orc$Path_writeText(char const * path, char const * text){
	try {
		FsUtil_write_all_text(path, text, "w+");
		return true;
	}
	catch (...){
		return false;
	}
}
long long Orc$Path_mtimeMs(const char *src){
	std::filesystem::path p(src);

	//得到是的file time

	auto lstTime = std::filesystem::last_write_time(p);
    // std::time_t cftime = std::file_time_type::clock::to_time_t(ftime);

	auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::filesystem::file_time_type::clock::now().time_since_epoch() 
		- std::chrono::system_clock::now().time_since_epoch()).count();

	auto systemTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		lstTime.time_since_epoch()).count() - elapse; 
	// tm* lsystemTime = localtime(&systemTime); 
	// std::cout << "localtime: " << lsystemTime->tm_year << " " << lsystemTime->tm_mon << " " << lsystemTime->tm_mday << " " << lsystemTime->tm_hour << " " << lsystemTime->tm_min << " " << lsystemTime->tm_sec << std::endl;

	return systemTime;
}