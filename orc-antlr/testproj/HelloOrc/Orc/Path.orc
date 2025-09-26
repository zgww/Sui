package OrcLang

#include <stdio.h>
import * from "./String.orc"
import * from "./List.orc"


//返回文件名，含后缀
String@ Path_basename(const char *s){
    String@ tmp = Path_normal(s);
    int idx = tmp.lastIndexByteOf("/")
    String@ ret = tmp.substringByByteStart(idx + 1)
    return ret
}
String@ Path_dirname(const char *s){
    String@ tmp = Path_normal(s);
    int idx = tmp.lastIndexByteOf("/")
    String@ ret = tmp.substringByByteRange(0, idx)
    return ret
}

//归一化，统一分隔符为'/'
String@ Path_normal(const char *s){
    String@ ret = str(s)
    String@ newPath = ret.replaceAllByRe("\\\\+", "/")
    return newPath
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
    String@ newPath = Path_append(dir, basename)
    bool ok = Path_copyTo(src, newPath)
    return ok
}
bool Path_moveToDir(const char *src, const char *dir){
    if (!Path_isDirectory(dir)){
        return false;
    }
    String@ basename = Path_basename(src);
    String@ newPath = Path_append(dir, basename)
    bool ok = Path_rename(src, newPath.str)
    return ok
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
extern void Path_writeText(const char *path, const char *text);

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
}