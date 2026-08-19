#define _CRT_SECURE_NO_WARNINGS

#include "FsUtil.h"
#include <filesystem>
#include "Utf8Util.h"
#include "StrUtil.h"
#include "urgc_api.h"


#ifdef _WIN32
#include <windows.h>
#endif

using string = std::string;
using wstring = std::wstring;

//static unordered_map<string, string> text_cache;

//void FsUtil_clear_text_cache() {
//	text_cache.clear();
//}
//utf8写入
STATIC void FsUtil_write_all_text(const char* path2, const char* content, const char* flag/*="w+"*/) {
	// DEFER_FREE 
	char *path = new_Utf8Util_utf8_to_active_code_page(path2);
	FILE* f = fopen(path, flag);
	free(path);
	if (f == NULL) {
		throw std::invalid_argument("EOpenFile");
	}
	int len = strlen(content);
	fwrite(content, 1, len, f);
	fclose(f);
}
char * new_FsUtil_read_all_text(const char* path2, const char* flag) {
	char *path = new_Utf8Util_utf8_to_active_code_page(path2);
	//if (text_cache.find(path) != text_cache.end()) {
	//	return text_cache[path];
	//}

	FILE* f = fopen(path, flag);
	free(path);

	if (f == NULL) {
		return _strdup("");
	}
	char buf[10240] = { 0 };
	std::string content;
	while (!feof(f)) {
		int cnt = fread(buf, 1, sizeof(buf) - 1, f);
		buf[cnt] = 0;

		content += buf;
	}
	fclose(f);
	//text_cache[path] = content;
	char *ret = _strdup(content.c_str());
	return ret;
}

char * new_FsUtil_getcwd() {
	//static char* data = NULL;
	//static std::shared_ptr<char[64]> ptr = NULL;
	//long long t0 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//for (int i = 0; i < 10000000; i++) {
	//	data = new char[64];
	//	//data = (char*)calloc(1, 64);
	//	//data = (char*)malloc(64);
	//	//ptr = std::make_shared<char[64]>();
	//}
	//long long t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//printf("malloc cost:%lld\n", t1 - t0);
	////1kw 64字节 debug+in vs
	////malloc:18s
	////calloc:18.8s
	////new: 19.5s
	//if (1) {
	//	return data;
	//}

#ifdef _WIN32
	wchar_t buf[MAX_PATH + 1];
	//GetModuleFileName(NULL, buf, MAX_PATH);
 	GetCurrentDirectoryW(MAX_PATH, buf);
	return new_Utf8Util_toutf8(buf);
	//#else
	//    char buf[MAX_PATH + 1];
	//    getcwd(buf, MAX_PATH);
	//    return buf;
#else
//	char buff[250];
//	GetCurrentDir(buff, 250);
//	std::string current_working_directory(buff);
//	return current_working_directory;
	return "";
#endif
}

char * new_FsUtil_getExecutionPath() {
#ifdef _WIN32
	wchar_t buf[MAX_PATH + 1];
	//GetModuleFileName(NULL, buf, MAX_PATH);
	//GetCurrentDirectoryA(MAX_PATH, buf);

	GetModuleFileNameW(nullptr, buf, sizeof(buf) - 1);
	return new_Utf8Util_toutf8(buf);
	//#else
	//    char buf[MAX_PATH + 1];
	//    getcwd(buf, MAX_PATH);
	//    return buf;
#else
	//	char buff[250];
	//	GetCurrentDir(buff, 250);
	//	std::string current_working_directory(buff);
	//	return current_working_directory;
	return "";
#endif
}
//
//json5pp::value FsUtil::read_json5(std::string path)
//{
//	string text = read_all_text(path);
//	if (text != "") {
//		auto v = json5pp::parse5(text);
//		return v;
//	}
//	return nullptr;
//}
//
//Path::Path() {
//}
//
//Path::Path(std::string _path) {
//	_wpath = Utf8Util::toutf16(_path);
//}
//
//Path::Path(std::wstring path) {
//	_wpath = path;
//}
//
//FILE* Path::fopen(std::string mode) {
//	auto acpPath = Utf8Util::utf16_to_active_code_page(_wpath);
//	auto f = ::fopen(acpPath.c_str(), "w+");
//	return f;
//}
//
//void Path::touch() {
//	if (!exists()) {
//		auto acpPath = Utf8Util::utf16_to_active_code_page(_wpath);
//		auto f = ::fopen(acpPath.c_str(), "w+");
//		fclose(f);
//	}
//}
//
//void Path::removeFile() {
//	if (isFile()) {
//		std::filesystem::path p(_wpath);
//		std::filesystem::remove(p);
//	}
//}
//
//void Path::removeDirs() {
//	if (isDirectory()) {
//		std::filesystem::path p(_wpath);
//		std::filesystem::remove_all(p);
//	}
//}
//
//void Path::removeDir() {
//	if (isDirectory()) {
//		std::filesystem::path p(_wpath);
//		std::filesystem::remove(p);
//	}
//}
//
//void Path::remove() {
//	std::filesystem::path p(_wpath);
//	std::filesystem::remove_all(p);
//}
//
//Path Path::rename(Path toPath) {
//	std::filesystem::path p(_wpath);
//	std::filesystem::path np(toPath._wpath);
//	std::filesystem::rename(p, np);
//	return toPath;
//}
//
//Path Path::rename(string toPath) {
//	return rename(Path(toPath));
//}
//
//bool Path::moveToDir(string toDir) {
//	return moveToDir(Path(toDir));
//}
//
//bool Path::moveToDir(Path dir) {
//	if (!dir.isDirectory()) {
//		return false;
//	}
//	auto newPath = dir.append(basename());
//	if (newPath.exists()) {
//		return false;
//	}
//	rename(newPath);
//	return true;
//}
//
//Path Path::copyTo(Path toPath) {
//	std::filesystem::path p(_wpath);
//	std::filesystem::path np(toPath._wpath);
//	std::filesystem::copy(p, np);
//	return toPath;
//}
//
//Result<Path> Path::copyToDir(Path dir) {
//	if (!dir.isDirectory()) {
//		return Result<Path>();
//	}
//	auto newPath = dir.append(basename());
//	if (newPath.exists()) {
//		return {};
//	}
//	auto ret = copyTo(newPath);
//	return ret;
//}
//
//bool Path::isAncestorOf(Path child) {
//	auto shortPath = normal().path();
//	auto longPath = child.normal().path();
//	auto ret = StrUtil::starts_with(longPath, shortPath);
//	return ret;
//}
//
//Path Path::replaceFilename(string filename) {
//	auto tmp = normal();
//	auto parts = StrUtil::split_by_re(tmp.path(), "/");
//	if (parts.size() == 0) {
//		return filename;
//	}
//	parts.pop_back();
//	parts.push_back(filename);
//	auto ret = StrUtil::join(parts, "/");
//	return ret;
//}
//
//vector<string> Path::list() {
//	vector<string> ret;
//	std::filesystem::path p(_wpath);
//
//	for (auto& it : std::filesystem::directory_iterator(p)) {
//		auto kidPath = Utf8Util::toutf8(it.path().wstring());
//		ret.push_back(kidPath);
//	}
//	return ret;
//}
//
//vector<string> Path::listSubtree() {
//	vector<string> ret;
//	std::function<void(std::filesystem::path)> each;
//	each = [&](std::filesystem::path p) {
//
//		for (auto& it : std::filesystem::directory_iterator(p)) {
//			auto kidPath = Utf8Util::toutf8(it.path().wstring());
//			ret.push_back(kidPath);
//
//			if (std::filesystem::is_directory(it.path())) {
//				each(it.path());
//			}
//		}
//	};
//
//	std::filesystem::path p(_wpath);
//	each(p);
//
//	return ret;
//}
//
//bool Path::isFile() {
//	//std::filesystem::path p(Utf8Util::toutf16(path));
//	//auto ret = std::filesystem::is_regular_file(p);
//	//return ret;
//	if (_fileType == -1) {
//
//		auto ret = exists() && !isDirectory();
//		_fileType = ret ? 1 : 0;
//	}
//	return _fileType;
//}
//
//bool Path::isDirectory() {
//	if (_dirType == -1) {
//		std::filesystem::path p(_wpath);
//		auto ret = std::filesystem::is_directory(p);
//		_dirType = ret ? 1 : 0;
//	}
//
//	return _dirType;
//}
//
//bool Path::exists() {
//	std::filesystem::path p(_wpath);
//	auto ret = std::filesystem::exists(p);
//	return ret;
//}
//
//void Path::mkdirs() {
//	std::filesystem::path p(_wpath);
//	std::filesystem::create_directories(p);
//}
//
//Path Path::append(string filename) {
//	std::wstring f = Utf8Util::toutf16(filename);
//	if (_wpath == L"") {
//		return Path(f);
//	}
//	if (_wpath.size() > 0 && _wpath[_wpath.size() - 1] == L'/') {
//		return Path(_wpath + f);
//	}
//	return Path(_wpath + L"/" + f);
//}
//
//string Path::basename() {
//	if (_basename.empty()) {
//		std::filesystem::path p(_wpath);
//		_basename = Utf8Util::toutf8(p.filename().wstring());
//	}
//	return _basename;
//}
//
//string Path::filenameWithoutExt() {
//	auto name = basename();
//	auto parts = StrUtil::split_by_re(name, "\\.");
//	parts.pop_back();
//	auto ret = StrUtil::join(parts, ".");
//	return ret;
//}
//
//string Path::ext_with_dot() {
//	auto parts = StrUtil::split_by_re(path(), "\\.");
//	if (parts.size() == 0) {
//		return "";
//	}
//	string ret = string(".") + parts[parts.size() - 1];
//	return ret;
//}
//
//string Path::ext_without_dot() {
//	auto parts = StrUtil::split_by_re(path(), "\\.");
//	if (parts.size() == 0) {
//		return "";
//	}
//	string ret = parts[parts.size() - 1];
//	return ret;
//}
//
//Path Path::normal() {
//	auto newpath = StrUtil::replace_by_re(path(), R"(\\+)", "/");
//	newpath = StrUtil::replace_by_re(newpath, "/{2,}", "/");
//	return Path(newpath);
//}
//
//Path Path::dirname() {
//	auto np = normal();
//	auto parts = StrUtil::split_by_re(np.path(), "/");
//	parts.pop_back();
//	auto ret = StrUtil::join(parts, "/");
//	return ret;
//}
//
//string Path::path() {
//	return Utf8Util::toutf8(_wpath);
//}



//
//void Path::test() {
//	Path p("c:/ws/far/karui-vs-plain/tmp/a.txt");
//	assert(p.dirname().path() == "c:/ws/far/karui-vs-plain/tmp");
//	{
//		Path p("c:/ws/far/karui-vs-plain/src");
//		auto paths = p.list();
//		assert(paths.size() > 0);
//		auto allPaths = p.listSubtree();
//		assert(allPaths.size() > 0);
//		return;
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain//tmp//a.txt");
//		assert(p.normal().path() == "c:/ws/far/karui-vs-plain/tmp/a.txt");
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain//tmp//a.txt");
//		assert(p.basename() == "a.txt");
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain//tmp//a.txt");
//		assert(p.filenameWithoutExt() == "a");
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain//tmp//a.txt");
//		assert(p.ext_with_dot() == ".txt");
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain//tmp//a.txt");
//		assert(p.ext_without_dot() == "txt");
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain//tmp//a.txt");
//		assert(!p.exists());
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain");
//		assert(p.isDirectory());
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain/");
//		assert(p.isDirectory());
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain/testproj/中文");
//		assert(p.isDirectory());
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain/test.png");
//		assert(p.isFile());
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain/wsdkjftest.png");
//		assert(!p.isFile());
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain/中文.png");
//		assert(!p.isFile());
//		p.touch();
//		assert(p.isFile());
//
//		auto np = p.rename("c:/ws/far/karui-vs-plain/中文2.png");
//		assert(!p.exists());
//		assert(np.isFile());
//		np.remove();
//		assert(!np.exists());
//	}
//	{
//		Path p("c:/ws/far/karui-vs-plain/中文目录/目录2");
//		assert(!p.isFile());
//		assert(!p.isDirectory ());
//		p.mkdirs();
//		assert(p.isDirectory());
//		p.remove();
//		assert(!p.isFile());
//		assert(!p.isDirectory ());
//	}
//}
//
//void FsUtil_registerMeta(){
//    ///REGISTER_META
//	
//    ///REGISTER_META$
//}