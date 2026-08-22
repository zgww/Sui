#include "Path.h"

#include <filesystem>
#include "Naga/Utf8Util.h"
#include "Naga/FsUtil.h"

//归一化，统一分隔符为'/'
std::string Path_normal(std::string s) {
    std::string newPath = Str::replaceAllByRe(s, "\\\\+", "/");
    std::string newPath2 = Str::replaceAllByRe(newPath, "^\\./|/\\.$", ""); //去掉前后的'.'
    std::string newPath3 = Str::replaceAllByRe(newPath2, "/\\./", "/"); // 替换中间的/./ 为 /
    return newPath3;
}

//返回文件名，含后缀
std::string Path_basename(std::string s) {
    std::string tmp = Path_normal(s);
    int idx = Str::lastIndexByteOf(tmp, "/");
    if (idx == -1) {
        return s;
    }

    std::string ret = tmp.substr(idx + 1);//tmp.substringByByteStart(idx + 1);
    return ret;
}

std::string Path_dirname(std::string s) {
    std::string tmp = Path_normal(s);
    int idx = Str::lastIndexByteOf(tmp, "/");
    if (idx == -1) {
        return (".");
    }
    std::string ret = tmp.substr(0, idx);//tmp.substringByByteRange(0, idx);
    return ret;
}


//std::string Path_relPathToCwd(const char* path) {
//    std::string cwd = Path_getcwd();
//    return Path_relPathToDir(path, cwd.str)
//}
////计算[path]相对于[relFilePath]的相对路径
////[relFilePath]是文件路径
//// 返回相对路径
//// 例： ("/a/b/c.png", "/a/b/d.json") => "c.png"
//std::string Path_relPathToDir(const char* path, const char* relDirPath) {
//    std::string abspath = Path_toAbsolute(path)
//        std::string absTargetPath = Path_toAbsolute(relDirPath)
//
//        List@ parts = abspath.splitByRe("/|\\\\")
//        List@ targetParts = absTargetPath.splitByRe("/|\\\\")
//
//        int l0 = parts.size()
//        int l1 = targetParts.size()
//        int minl = minInt(l0, l1)
//        int samel = minl//如果前缀都相同
//        //计算共同组成长度
//        for int i = 0; i < minl; i++{
//            String* a = (String*)parts.get(i)
//                String * b = (String*)targetParts.get(i)
//                if !a.equalsString(b) {
//                    samel = i;
//                    break
//                }
//        }
//
//
//
//    List@ segs = new List()
//        //去掉共同点。 从不同点开始， 
//        //添加'..'; 和relPathToFile的主要是 -0,还是-1
//        for int i = samel; i < l1 - 0; i++{
//            segs.add(str(".."))
//        }
//    //添加不同点
//    for int i = samel; i < l0; i++{
//        String* part = (String*)parts.get(i)
//            segs.add(part)
//    }
//    std::string result = String_join(segs, "/")
//        return result;
//}
//
////计算[path]相对于[relFilePath]的相对路径
////[relFilePath]是文件路径
//// 返回相对路径
//// 例： ("/a/b/c.png", "/a/b/d.json") => "c.png"
//std::string Path_relPathToFile(const char* path, const char* relFilePath) {
//    std::string abspath = Path_toAbsolute(path)
//        std::string absTargetPath = Path_toAbsolute(relFilePath)
//
//        List@ parts = abspath.splitByRe("/|\\\\")
//        List@ targetParts = absTargetPath.splitByRe("/|\\\\")
//
//        int l0 = parts.size()
//        int l1 = targetParts.size()
//        int minl = minInt(l0, l1)
//        int samel = minl
//        //计算共同组成长度
//        for int i = 0; i < minl; i++{
//            String* a = (String*)parts.get(i)
//                String * b = (String*)targetParts.get(i)
//                if !a.equalsString(b) {
//                    samel = i;
//                    break
//                }
//        }
//
//
//
//    List@ segs = new List()
//        //去掉共同点。 从不同点开始， 
//        //添加'..'; -1是因为 relFilePath是文件路径，不是目录路径
//        for int i = samel; i < l1 - 1; i++{
//            segs.add(str(".."))
//        }
//    //添加不同点
//    for int i = samel; i < l0; i++{
//        String* part = (String*)parts.get(i)
//            segs.add(part)
//    }
//    std::string result = String_join(segs, "/")
//        return result;
//}
//
//List@ Path_splitString(String* p) {
//    List@ parts = p.splitByRe("/|\\\\")
//        return parts
//}
//bool Path_isAbsolute(const char* p) {
//    if String_startsWith(p, "/") {
//        return true
//    }
//    //windows 盘符
//    if strlen(p) >= 2 && p[1] == ':'{
//        return true
//    }
//    return false
//}
//
////转为绝对路径
//std::string Path_toAbsolute(const char* p) {
//    if String_startsWith(p, "/") {
//        return str(p)
//    }
//    //windows 盘符
//    if strlen(p) >= 2 && p[1] == ':'{
//        return str(p)
//    }
//
//    String @abs = Path_getcwd();
//    abs.add("/").add(p)
//
//        // std::string nmlpath = Path_normal(abs.str);
//        List@ parts = abs.splitByRe("/|\\\\")
//        List@ segs = new List();
//    for int i = 0; i < parts.size(); i++{
//        String* part = (String*)parts.get(i)
//            printf("part:%s\n", part.str)
//            if part.equals(".") {
//                continue
//            }
//            else if part.equals("..") {
//                if segs.size() > 0 {
//                    segs.removeAt(segs.size() - 1)
//                }
//            }
//            else {
//                segs.add(part)
//            }
//    }
//    std::string ret = String_join(segs, "/")
//        return ret
//}
//
////替换basename
//std::string Path_withBasename(const char* path, const char* newbasename) {
//    std::string dirname = Path_dirname(path)
//        dirname.add("/").add(newbasename)
//        return dirname
//}
////替换最后一个后缀. newExt: .jpg, 带有'.'
//std::string Path_withLastExt(const char* path, const char* newExt) {
//    std::string tmp = str(path);
//    int idx = tmp.lastIndexByteOf(".")
//        std::string ret = tmp.substringByByteRange(0, idx)
//        ret.add(newExt)
//        return ret
//}
//std::string Path_withExt(const char* path, const char* newExt) {
//    std::string dirname = Path_dirname(path)
//        std::string pureFilename = Path_pureFilename(path)
//        dirname.add("/").addString(pureFilename).add(newExt)
//        return dirname
//}
//
////返回文件名,不含后缀
//std::string Path_filename(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.lastIndexByteOf(".")
//        std::string ret = tmp.substringByByteRange(0, idx)
//        return ret
//}
////不含多级的ext
//std::string Path_pureFilename(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.indexByteOf(".")
//        std::string ret = tmp.substringByByteRange(0, idx)
//        return ret
//}
////含'.', 只返回最后的ext. 对于多级ext,前面的不算
//std::string Path_ext(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.lastIndexByteOf(".")
//        std::string ret = tmp.substringByByteStart(idx)
//        return ret
//}
////含'.', 含多级的ext, 如： filename.a.b.c => '.a.b.c'
//std::string Path_fullExt(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.indexByteOf(".")
//        std::string ret = tmp.substringByByteStart(idx)
//        return ret
//}
//
//bool Path_isFile(const char* path) {
//    bool ret = Path_exists(path) && !Path_isDirectory(path)
//        return ret
//}
//extern bool Path_isDirectory(const char* path);
//extern bool Path_mkdirs(const char* dirpath);
//extern bool Path_exists(const char* path);
//
//bool Path_mkdirsByFilePath(const char* filepath) {
//    std::string dirpath = Path_dirname(filepath)
//        return Path_mkdirs(dirpath.str)
//}
//
//std::string Path_append(const char* path, const char* path2) {
//    std::string ret = str(path)
//        ret.add("/").add(path2)
//        return ret;
//}
//
//bool Path_copyToDir(const char* src, const char* dir) {
//    if (!Path_isDirectory(dir)) {
//        return false;
//    }
//    std::string basename = Path_basename(src);
//    std::string newPath = Path_append(dir, basename.str)
//        bool ok = Path_copyTo(src, newPath.str)
//        return ok
//}
//bool Path_moveToDir(const char* src, const char* dir) {
//    if (!Path_isDirectory(dir)) {
//        return false;
//    }
//    std::string basename = Path_basename(src);
//    std::string newPath = Path_append(dir, basename.str)
//        bool ok = Path_rename(src, newPath.str)
//        return ok
//}
//
////修改时间
//extern long long Path_mtimeMs(const char* src);
//std::string Path_mtimeStr(const char* src) {
//    long long ms = Path_mtimeMs(src)
//        long long sec = ms / 1000L;
//    struct tm* t = localtime(&sec);
//
//    char buf[100];
//    sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d",
//        t.tm_year + 1900,
//        t.tm_mon + 1,
//        t.tm_mday,
//        t.tm_hour,
//        t.tm_min,
//        t.tm_sec,
//        )
//        std::string s = str(buf)
//        return s;
//}
//
//
//extern bool Path_copyTo(const char* src, const char* dst);
//extern bool Path_rename(const char* src, const char* dst);
//extern bool Path_remove(const char* src);
//extern bool Path_removeDir(const char* src);
//extern bool Path_removeDirs(const char* src);
//extern bool Path_removeFile(const char* src);
////不存在，就创建
//extern bool Path_touch(const char* src);
////打开文件，主要是为了支持utf8编码
//extern bool Path_fopen(const char* src, const char* mode);
//
////List<std::string>@ 只列出目录下的
//extern List@ Path_list(const char* path);
////List<std::string>@ 列出子树
//List@ Path_listSubtree(const char* path) {
//    List@ ret = new List()
//        Path_listSubtree_toList(path, ret)
//        return ret
//}
//void Path_listSubtree_toList(const char* path, List* outList) {
//    List@ lst = Path_list(path);
//    int l = lst.size()
//        for (int i = 0; i < l; i++) {
//            String* curpath = (String*)lst.get(i)
//                outList.add(curpath)
//
//                if (Path_isDirectory(curpath.str)) {
//                    Path_listSubtree_toList(curpath.str, outList)
//                }
//        }
//}
//
////当前工作目录
//extern std::string Path_getcwd();
////设置当前工作目录
//extern void Path_setcwd(const char* path);
////取得执行文件的路径
//extern std::string Path_getExecutionPath();
//
// 解码相对路径。 相对于.exe目录
std::string Path_resolveFromExecutionDir(std::string path) {
    static std::string exeDir;
    if (exeDir == "") {
        exeDir = Path_dirname(Path_getExecutionPath());
    }
    std::string ret = exeDir + "/" + path;
    return ret;
}

//std::string Path_dirname(const char* s) {
//    std::string tmp = Path_normal(s);
//    int idx = tmp.lastIndexByteOf("/")
//        if idx == -1 {
//            return str(".")
//        }
//    std::string ret = tmp.substringByByteRange(0, idx)
//        return ret
//}
//std::string Path_relPathToCwd(const char* path) {
//    std::string cwd = Path_getcwd();
//    return Path_relPathToDir(path, cwd.str)
//}
////计算[path]相对于[relFilePath]的相对路径
////[relFilePath]是文件路径
//// 返回相对路径
//// 例： ("/a/b/c.png", "/a/b/d.json") => "c.png"
//std::string Path_relPathToDir(const char* path, const char* relDirPath) {
//    std::string abspath = Path_toAbsolute(path)
//        std::string absTargetPath = Path_toAbsolute(relDirPath)
//
//        List@ parts = abspath.splitByRe("/|\\\\")
//        List@ targetParts = absTargetPath.splitByRe("/|\\\\")
//
//        int l0 = parts.size()
//        int l1 = targetParts.size()
//        int minl = minInt(l0, l1)
//        int samel = minl//如果前缀都相同
//        //计算共同组成长度
//        for int i = 0; i < minl; i++{
//            String* a = (String*)parts.get(i)
//                String * b = (String*)targetParts.get(i)
//                if !a.equalsString(b) {
//                    samel = i;
//                    break
//                }
//        }
//
//
//
//    List@ segs = new List()
//        //去掉共同点。 从不同点开始， 
//        //添加'..'; 和relPathToFile的主要是 -0,还是-1
//        for int i = samel; i < l1 - 0; i++{
//            segs.add(str(".."))
//        }
//    //添加不同点
//    for int i = samel; i < l0; i++{
//        String* part = (String*)parts.get(i)
//            segs.add(part)
//    }
//    std::string result = String_join(segs, "/")
//        return result;
//}
//
////计算[path]相对于[relFilePath]的相对路径
////[relFilePath]是文件路径
//// 返回相对路径
//// 例： ("/a/b/c.png", "/a/b/d.json") => "c.png"
//std::string Path_relPathToFile(const char* path, const char* relFilePath) {
//    std::string abspath = Path_toAbsolute(path)
//        std::string absTargetPath = Path_toAbsolute(relFilePath)
//
//        List@ parts = abspath.splitByRe("/|\\\\")
//        List@ targetParts = absTargetPath.splitByRe("/|\\\\")
//
//        int l0 = parts.size()
//        int l1 = targetParts.size()
//        int minl = minInt(l0, l1)
//        int samel = minl
//        //计算共同组成长度
//        for int i = 0; i < minl; i++{
//            String* a = (String*)parts.get(i)
//                String * b = (String*)targetParts.get(i)
//                if !a.equalsString(b) {
//                    samel = i;
//                    break
//                }
//        }
//
//
//
//    List@ segs = new List()
//        //去掉共同点。 从不同点开始， 
//        //添加'..'; -1是因为 relFilePath是文件路径，不是目录路径
//        for int i = samel; i < l1 - 1; i++{
//            segs.add(str(".."))
//        }
//    //添加不同点
//    for int i = samel; i < l0; i++{
//        String* part = (String*)parts.get(i)
//            segs.add(part)
//    }
//    std::string result = String_join(segs, "/")
//        return result;
//}
//
//List@ Path_splitString(String* p) {
//    List@ parts = p.splitByRe("/|\\\\")
//        return parts
//}
//bool Path_isAbsolute(const char* p) {
//    if String_startsWith(p, "/") {
//        return true
//    }
//    //windows 盘符
//    if strlen(p) >= 2 && p[1] == ':'{
//        return true
//    }
//    return false
//}
//
////转为绝对路径
//std::string Path_toAbsolute(const char* p) {
//    if String_startsWith(p, "/") {
//        return str(p)
//    }
//    //windows 盘符
//    if strlen(p) >= 2 && p[1] == ':'{
//        return str(p)
//    }
//
//    String @abs = Path_getcwd();
//    abs.add("/").add(p)
//
//        // std::string nmlpath = Path_normal(abs.str);
//        List@ parts = abs.splitByRe("/|\\\\")
//        List@ segs = new List();
//    for int i = 0; i < parts.size(); i++{
//        String* part = (String*)parts.get(i)
//            printf("part:%s\n", part.str)
//            if part.equals(".") {
//                continue
//            }
//            else if part.equals("..") {
//                if segs.size() > 0 {
//                    segs.removeAt(segs.size() - 1)
//                }
//            }
//            else {
//                segs.add(part)
//            }
//    }
//    std::string ret = String_join(segs, "/")
//        return ret
//}
//
////替换basename
//std::string Path_withBasename(const char* path, const char* newbasename) {
//    std::string dirname = Path_dirname(path)
//        dirname.add("/").add(newbasename)
//        return dirname
//}
////替换最后一个后缀. newExt: .jpg, 带有'.'
//std::string Path_withLastExt(const char* path, const char* newExt) {
//    std::string tmp = str(path);
//    int idx = tmp.lastIndexByteOf(".")
//        std::string ret = tmp.substringByByteRange(0, idx)
//        ret.add(newExt)
//        return ret
//}
//std::string Path_withExt(const char* path, const char* newExt) {
//    std::string dirname = Path_dirname(path)
//        std::string pureFilename = Path_pureFilename(path)
//        dirname.add("/").addString(pureFilename).add(newExt)
//        return dirname
//}
//
////返回文件名,不含后缀
//std::string Path_filename(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.lastIndexByteOf(".")
//        std::string ret = tmp.substringByByteRange(0, idx)
//        return ret
//}
////不含多级的ext
//std::string Path_pureFilename(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.indexByteOf(".")
//        std::string ret = tmp.substringByByteRange(0, idx)
//        return ret
//}
////含'.', 只返回最后的ext. 对于多级ext,前面的不算
//std::string Path_ext(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.lastIndexByteOf(".")
//        std::string ret = tmp.substringByByteStart(idx)
//        return ret
//}
////含'.', 含多级的ext, 如： filename.a.b.c => '.a.b.c'
//std::string Path_fullExt(const char* s) {
//    std::string tmp = Path_basename(s)
//        int idx = tmp.indexByteOf(".")
//        std::string ret = tmp.substringByByteStart(idx)
//        return ret
//}
//
//bool Path_isFile(const char* path) {
//    bool ret = Path_exists(path) && !Path_isDirectory(path)
//        return ret
//}
//extern bool Path_isDirectory(const char* path);
//extern bool Path_mkdirs(const char* dirpath);
//extern bool Path_exists(const char* path);
//
//bool Path_mkdirsByFilePath(const char* filepath) {
//    std::string dirpath = Path_dirname(filepath)
//        return Path_mkdirs(dirpath.str)
//}
//
//std::string Path_append(const char* path, const char* path2) {
//    std::string ret = str(path)
//        ret.add("/").add(path2)
//        return ret;
//}
//
//bool Path_copyToDir(const char* src, const char* dir) {
//    if (!Path_isDirectory(dir)) {
//        return false;
//    }
//    std::string basename = Path_basename(src);
//    std::string newPath = Path_append(dir, basename.str)
//        bool ok = Path_copyTo(src, newPath.str)
//        return ok
//}
//bool Path_moveToDir(const char* src, const char* dir) {
//    if (!Path_isDirectory(dir)) {
//        return false;
//    }
//    std::string basename = Path_basename(src);
//    std::string newPath = Path_append(dir, basename.str)
//        bool ok = Path_rename(src, newPath.str)
//        return ok
//}
//
////修改时间
//extern long long Path_mtimeMs(const char* src);
//std::string Path_mtimeStr(const char* src) {
//    long long ms = Path_mtimeMs(src)
//        long long sec = ms / 1000L;
//    struct tm* t = localtime(&sec);
//
//    char buf[100];
//    sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d",
//        t.tm_year + 1900,
//        t.tm_mon + 1,
//        t.tm_mday,
//        t.tm_hour,
//        t.tm_min,
//        t.tm_sec,
//        )
//        std::string s = str(buf)
//        return s;
//}
//
//
//extern bool Path_copyTo(const char* src, const char* dst);
//extern bool Path_rename(const char* src, const char* dst);
//extern bool Path_remove(const char* src);
//extern bool Path_removeDir(const char* src);
//extern bool Path_removeDirs(const char* src);
//extern bool Path_removeFile(const char* src);
////不存在，就创建
//extern bool Path_touch(const char* src);
////打开文件，主要是为了支持utf8编码
//extern bool Path_fopen(const char* src, const char* mode);
//
////List<std::string>@ 只列出目录下的
//extern List@ Path_list(const char* path);
////List<std::string>@ 列出子树
//List@ Path_listSubtree(const char* path) {
//    List@ ret = new List()
//        Path_listSubtree_toList(path, ret)
//        return ret
//}
//void Path_listSubtree_toList(const char* path, List* outList) {
//    List@ lst = Path_list(path);
//    int l = lst.size()
//        for (int i = 0; i < l; i++) {
//            String* curpath = (String*)lst.get(i)
//                outList.add(curpath)
//
//                if (Path_isDirectory(curpath.str)) {
//                    Path_listSubtree_toList(curpath.str, outList)
//                }
//        }
//}
//
////当前工作目录
//extern std::string Path_getcwd();
////设置当前工作目录
//extern void Path_setcwd(const char* path);
////取得执行文件的路径
//extern std::string Path_getExecutionPath();
//
//// 解码相对路径。 相对于.exe目录
//std::string Path_resolveFromExecutionDir(const char* path) {
//    static std::string exeDir = null
//        if exeDir == null{
//            exeDir = Path_dirname(Path_getExecutionPath().str)
//        }
//            std::string ret = str(exeDir.str).add("/").add(path)
//            return ret
//}
//
//extern std::string Path_readText(const char* path);
//extern bool Path_writeText(const char* path, const char* text);
//
//bool Path_isUsualImage(const char* path) {
//    return String_endsWith(path, ".jpg")
//        || String_endsWith(path, ".png")
//        // || String_endsWith(path, ".webp")
//        // || String_endsWith(path, ".gif")
//        || String_endsWith(path, ".jpeg")
//
//}
//// 解码相对路径， 相对于basefilepath 文件路径
//std::string Path_resolveRelativeFromFile(const char* path, const char* basefilepath) {
//    if path&& basefilepath {
//        if Path_isAbsolute(path) {
//            return str(path)
//        }
//
//
//        std::string tmp = Path_dirname(basefilepath)
//            tmp.add("/").add(path)
//            std::string ret = Path_normal(tmp.str)
//            return ret
//    }
//    return null
//}
//
//void testPath() {
//    {
//        std::string bname = Path_basename("/a/b/csdfjsie")
//            printf("bname:%s\n", bname.str);
//    }
//    {
//        std::string bname = Path_dirname("/a/b/csdfjsie")
//            printf("dirname:%s\n", bname.str);
//    }
//    {
//        std::string bname = Path_filename("/a/b/openfile.json.orc")
//            printf("filename:%s\n", bname.str);
//    }
//    {
//        std::string bname = Path_ext("/a/b/openfile.json.orc")
//            printf("ext:%s\n", bname.str);
//    }
//    {
//        std::string bname = Path_pureFilename("/a/b/openfile.json.orc")
//            printf("pure filename:%s\n", bname.str);
//    }
//    {
//        std::string bname = Path_fullExt("/a/b/openfile.json.orc")
//            printf("full ext:%s\n", bname.str);
//    }
//    {
//        List@ paths = Path_list("d:/ws")
//            for (int i = 0; i < paths.size(); i++) {
//                std::string path = (std::string)paths.get(i)
//                    printf("\t%s\n", path.str)
//            }
//    }
//    {
//        bool isDir = Path_isDirectory("/ws")
//            bool isFile = Path_isFile("/ws")
//            bool exists = Path_exists("/ws")
//            printf("isDir:%d %d, %d\n", isDir, isFile, exists);
//    }
//    {
//        List@ paths = Path_listSubtree("./")
//            for (int i = 0; i < paths.size(); i++) {
//                std::string path = (std::string)paths.get(i)
//                    printf("\t%s\n", path.str)
//            }
//    }
//    {
//        Path_mkdirs("/ws/a/b/c/d")
//    }
//    {
//        std::string p = Path_resolveRelativeFromFile("a.png", "./a/././../b/c.matl.json")
//            printf("p:%s\n", p.str)
//    }
//}
//
//long long Path_mtimeMs(const char* src) {
//    std::filesystem::path p(src);
//
//    //得到是的file time
//
//    auto lstTime = std::filesystem::last_write_time(p);
//    // std::time_t cftime = std::file_time_type::clock::to_time_t(ftime);
//
//    auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(
//        std::filesystem::file_time_type::clock::now().time_since_epoch()
//        - std::chrono::system_clock::now().time_since_epoch()).count();
//
//    auto systemTime = std::chrono::duration_cast<std::chrono::milliseconds>(
//        lstTime.time_since_epoch()).count() - elapse;
//    // tm* lsystemTime = localtime(&systemTime); 
//    // std::cout << "localtime: " << lsystemTime->tm_year << " " << lsystemTime->tm_mon << " " << lsystemTime->tm_mday << " " << lsystemTime->tm_hour << " " << lsystemTime->tm_min << " " << lsystemTime->tm_sec << std::endl;
//
//    return systemTime;
//}
//
//
//
//
//String* Path_readText(String** __outRef__, char const* path) {
//    NEW_CLASS_VAR(String, ret);
//    char* s = new_FsUtil_read_all_text(path, "r");
//
//
//
//    String$set_as_own(ret, s);
//
//    return (String*)URGC_RETURN_CLASS(ret);
//}
//bool Path_writeText(char const* path, char const* text) {
//    try {
//        FsUtil_write_all_text(path, text, "w+");
//        return true;
//    }
//    catch (...) {
//        return false;
//    }
//}
std::string Path_getExecutionPath() {
    char* s = new_FsUtil_getExecutionPath();
    std::string ret(s);
    free(s);
    return ret;
}
