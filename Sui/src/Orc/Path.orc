package Orc

#include <stdio.h>
#include <string.h>
#include <time.h>
import * from "./String.orc"
import * from "./Math.orc"
import * from "./List.orc"


//返回文件名，含后缀
String@ Path_basename(const char *s){
    String@ tmp = Path_normal(s);
    int idx = tmp.lastIndexByteOf("/")
    if idx == -1 {
        return str(s)
    }
    String@ ret = tmp.substringByByteStart(idx + 1)
    return ret
}
String@ Path_dirname(const char *s){
    String@ tmp = Path_normal(s);
    int idx = tmp.lastIndexByteOf("/")
    if idx == -1 {
        return str(".")
    }
    String@ ret = tmp.substringByByteRange(0, idx)
    return ret
}
//计算[path]相对于[relFilePath]的相对路径
//[relFilePath]是文件路径
String@ Path_relPathToFile(const char *path, const char *relFilePath){
    String@ abspath = Path_toAbsolute(path)
    String@ absTargetPath = Path_toAbsolute(relFilePath)

    List@ parts = abspath.splitByRe("/|\\\\")
    List@ targetParts = absTargetPath.splitByRe("/|\\\\")

    int l0 = parts.size()
    int l1 = targetParts.size()
    int minl = minInt(l0, l1)
    int samel = 0
    //计算共同组成长度
    for int i = 0; i < minl; i++{
        String* a = (String*)parts.get(i)
        String* b = (String*)targetParts.get(i)
        if !a.equalsString(b){
            samel = i;
            break
        }
    }


    
    List@ segs = new List()
    //去掉共同点。 从不同点开始， 
    //添加'..'; -1是因为 relFilePath是文件路径，不是目录路径
    for int i = samel; i < l1 - 1; i++{
        segs.add(str(".."))
    }
    //添加不同点
    for int i = samel; i < l0; i++{
        String* part = (String*)parts.get(i)
        segs.add(part)
    }
    String@ result = String_join(segs, "/")
    return result;
}

List@ Path_splitString(String* p){
    List@ parts = p.splitByRe("/|\\\\")
    return parts
}

//转为绝对路径
String@ Path_toAbsolute(const char *p){
    if String_startsWith(p, "/"){
        return str(p)
    }
    //windows 盘符
    if strlen(p) >= 2 && p[1] == ':'{
        return str(p)
    }

    String @abs = Path_getcwd();
    abs.add("/").add(p)
    
    // String@ nmlpath = Path_normal(abs.str);
    List@ parts = abs.splitByRe("/|\\\\")
    List@ segs = new List();
    for int i = 0; i < parts.size(); i++{
        String* part = (String*)parts.get(i)
        printf("part:%s\n", part.str)
        if part.equals("."){
            continue
        }
        else if part.equals(".."){
            if segs.size() > 0 {
                segs.removeAt(segs.size() - 1)
            }
        }
        else {
            segs.add(part)
        }
    }
    String@ ret = String_join(segs, "/")
    return ret
}

//归一化，统一分隔符为'/'
String@ Path_normal(const char *s){
    String@ ret = str(s)
    String@ newPath = ret.replaceAllByRe("\\\\+", "/")
    String@ newPath2 = newPath.replaceAllByRe("^\\./|/\\.$", "") //去掉前后的'.'
    String@ newPath3 = newPath2.replaceAllByRe("/\\./", "/") // 替换中间的/./ 为 /
    return newPath3
}
//替换basename
String@ Path_withBasename(const char *path, const char *newbasename){
    String@ dirname = Path_dirname(path)
    dirname.add("/").add(newbasename)
    return dirname
}
//替换最后一个后缀. newExt: .jpg, 带有'.'
String@ Path_withLastExt(const char *path, const char *newExt){
    String@ tmp = str(path);
    int idx = tmp.lastIndexByteOf(".")
    String@ ret = tmp.substringByByteRange(0, idx)
    ret.add(newExt)
    return ret
}
String@ Path_withExt(const char *path, const char *newExt){
    String@ dirname = Path_dirname(path)
    String@ pureFilename = Path_pureFilename(path)
    dirname.add("/").addString(pureFilename).add(newExt)
    return dirname
}

//返回文件名,不含后缀
String@ Path_filename(const char *s){
    String@ tmp = Path_basename(s)
    int idx = tmp.lastIndexByteOf(".")
    String@ ret = tmp.substringByByteRange(0, idx)
    return ret
}
//不含多级的ext
String@ Path_pureFilename(const char *s){
    String@ tmp = Path_basename(s)
    int idx = tmp.indexByteOf(".")
    String@ ret = tmp.substringByByteRange(0, idx)
    return ret
}
//含'.', 只返回最后的ext. 对于多级ext,前面的不算
String@ Path_ext(const char *s){
    String@ tmp = Path_basename(s)
    int idx = tmp.lastIndexByteOf(".")
    String@ ret = tmp.substringByByteStart(idx)
    return ret
}
//含'.', 含多级的ext, 如： filename.a.b.c => '.a.b.c'
String@ Path_fullExt(const char *s){
    String@ tmp = Path_basename(s)
    int idx = tmp.indexByteOf(".")
    String@ ret = tmp.substringByByteStart(idx)
    return ret
}

bool Path_isFile(const char *path){
    bool ret = Path_exists(path) && !Path_isDirectory(path)
    return ret
}
extern bool Path_isDirectory(const char *path);
extern bool Path_mkdirs(const char *dirpath);
extern bool Path_exists(const char *path);

String@ Path_append(const char *path, const char *path2){
    String@ ret = str(path)
    ret.add("/").add(path2)
    return ret;
}

bool Path_copyToDir(const char *src, const char *dir){
    if (!Path_isDirectory(dir)){
        return false;
    }
    String@ basename = Path_basename(src);
    String@ newPath = Path_append(dir, basename.str)
    bool ok = Path_copyTo(src, newPath.str)
    return ok
}
bool Path_moveToDir(const char *src, const char *dir){
    if (!Path_isDirectory(dir)){
        return false;
    }
    String@ basename = Path_basename(src);
    String@ newPath = Path_append(dir, basename.str)
    bool ok = Path_rename(src, newPath.str)
    return ok
}

//修改时间
extern long long Path_mtimeMs(const char *src);
String@ Path_mtimeStr(const char *src){
    long long ms = Path_mtimeMs(src)
    long long sec = ms / 1000L;
    struct tm *t = localtime(&sec);

    char buf[100];
    sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d",
        t.tm_year+1900,
        t.tm_mon + 1,
        t.tm_mday,
        t.tm_hour,
        t.tm_min,
        t.tm_sec,
    )
    String@ s = str(buf)
    return s;
}


extern bool Path_copyTo(const char *src, const char *dst);
extern bool Path_rename(const char *src, const char *dst);
extern bool Path_remove(const char *src);
extern bool Path_removeDir(const char *src);
extern bool Path_removeDirs(const char *src);
extern bool Path_removeFile(const char *src);
//不存在，就创建
extern bool Path_touch(const char *src);
//打开文件，主要是为了支持utf8编码
extern bool Path_fopen(const char *src, const char *mode);

//List<String@>@ 只列出目录下的
extern List@ Path_list(const char *path);
//List<String@>@ 列出子树
List@ Path_listSubtree(const char *path){
    List@ ret = new List()
    Path_listSubtree_toList(path, ret)
    return ret
}
void Path_listSubtree_toList(const char *path, List* outList){
    List@ lst = Path_list(path);
    int l = lst.size()
    for (int i = 0; i < l; i++){
        String *curpath = (String*)lst.get(i)
        outList.add(curpath)

        if (Path_isDirectory(curpath.str)){
            Path_listSubtree_toList(curpath.str, outList)
        }
    }
}

//当前工作目录
extern String@ Path_getcwd();
//设置当前工作目录
extern void Path_setcwd(const char *path);
//取得执行文件的路径
extern String@ Path_getExecutionPath();

extern String@ Path_readText(const char *path);
extern bool Path_writeText(const char *path, const char *text);

bool Path_isUsualImage(const char *path){
    return String_endsWith(path, ".jpg")
    || String_endsWith(path, ".png")
    // || String_endsWith(path, ".webp")
    // || String_endsWith(path, ".gif")
    || String_endsWith(path, ".jpeg")

}
String@ Path_resolveRelativeFromFile(const char *path, const char *basefilepath){
    if path && basefilepath{
        String@ tmp = Path_dirname(basefilepath)
        tmp.add("/").add(path)
        String@ ret = Path_normal(tmp.str)
        return ret
    }
    return null
}

void testPath(){
    {
        String@ bname = Path_basename("/a/b/csdfjsie")
        printf("bname:%s\n", bname.str);
    }
    {
        String@ bname = Path_dirname("/a/b/csdfjsie")
        printf("dirname:%s\n", bname.str);
    }
    {
        String@ bname = Path_filename("/a/b/openfile.json.orc")
        printf("filename:%s\n", bname.str);
    }
    {
        String@ bname = Path_ext("/a/b/openfile.json.orc")
        printf("ext:%s\n", bname.str);
    }
    {
        String@ bname = Path_pureFilename("/a/b/openfile.json.orc")
        printf("pure filename:%s\n", bname.str);
    }
    {
        String@ bname = Path_fullExt("/a/b/openfile.json.orc")
        printf("full ext:%s\n", bname.str);
    }
    {
        List@ paths = Path_list("d:/ws")
        for (int i = 0; i < paths.size(); i++){
            String@ path = (String@)paths.get(i)
            printf("\t%s\n", path.str)
        }
    }
    {
        bool isDir = Path_isDirectory("/ws")
        bool isFile = Path_isFile("/ws")
        bool exists = Path_exists("/ws")
        printf("isDir:%d %d, %d\n", isDir, isFile, exists);
    }
    {
        List@ paths = Path_listSubtree("./")
        for (int i = 0; i < paths.size(); i++){
            String@ path = (String@)paths.get(i)
            printf("\t%s\n", path.str)
        }
    }
    {
        Path_mkdirs("/ws/a/b/c/d")
    }
    {
        String@ p = Path_resolveRelativeFromFile("a.png", "./a/././../b/c.matl.json")
        printf("p:%s\n", p.str)
    }
}