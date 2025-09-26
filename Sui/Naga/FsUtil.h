#pragma once

#include "NagaPredef.h"



#ifdef __cplusplus
extern "C" {
#endif

    //class NAGA_DLLAPI FsUtil : public GcObj {
    //public:

        ///API_SYNC
    NAGA_DLLAPI void FsUtil_write_all_text(const char* path, const char* content, const char* flag);
        NAGA_DLLAPI char* new_FsUtil_getExecutionPath();
        ///API_SYNC$


        //static void FsUtil_clear_text_cache();
        NAGA_DLLAPI char* new_FsUtil_read_all_text(const char* path, const char* flag);
        NAGA_DLLAPI char* new_FsUtil_getcwd();


    //    static json5pp::value read_json5(std::string path);
    //};

    //class NAGA_DLLAPI Path : public GcObj {
    //public:
    //    ///API_SYNC
    //    ///API_SYNC$
    //    Path();
    //    Path(std::string path);
    //    Path(std::wstring path);

    //    FILE* fopen(std::string mode);
    //    void touch(); //创建文件
    //    //删除文件
    //    void removeFile();
    //    //递归删除目录
    //    void removeDirs();
    //    //删除目录，不递归
    //    void removeDir();
    //    //不管文件还是目录，直接删.目录是递归删
    //    void remove();
    //    Path rename(Path toPath);
    //    Path rename(std::string toPath);
    //    bool moveToDir(std::string toDir);
    //    bool moveToDir(Path toDir);

    //    Path copyTo(Path toPath);
    //    Result<Path> copyToDir(Path dir);

    //    //是不是child的上级目录
    //    bool isAncestorOf(Path child);

    //    //把filename换了
    //    Path replaceFilename(std::string filename);

    //    //列出子文件/子目录
    //    std::vector<std::string> list();
    //    //递归子树
    //    std::vector<std::string> listSubtree();

    //    bool isFile();
    //    bool isDirectory();
    //    bool exists();
    //    void mkdirs();

    //    Path append(std::string filename);
    //    //文件名
    //    std::string basename();
    //    //文件名，不含后缀
    //    std::string filenameWithoutExt();

    //    std::string ext_with_dot();
    //    std::string ext_without_dot();

    //    //格式化 分隔符'\'
    //    Path normal();
    //    Path dirname();


    //    //utf8 string
    //    std::string path();

    //    //用宽字符存放
    //    std::wstring _wpath;//wstring string
    //    //缓存
    //    std::string _basename;
    //    //-1:未知, 0: 非dir, 1: 是dir  缓存用的
    //    char _dirType = -1;
    //    char _fileType = -1;

    //    static void test();
    //};
    //void FsUtil_registerMeta();





#ifdef __cplusplus
}
#endif
