#pragma once

//#include "json5pp.h"
#include "Result.h"
#include <vector>
#include <string>


class FsUtil {
public:

	///API_SYNC
	static void write_all_text(std::string path, std::string content, std::string flag="w+");
	static std::string getExecutionPath();
	///API_SYNC$


	static void clear_text_cache();
    static std::string read_all_text(std::string path, std::string flag = "r+");
    static std::string getcwd();
    static void setcwd(std::string cwd);
    //static json5pp::value read_json5(std::string path);
};

class Path {
public:
	///API_SYNC
	///API_SYNC$
    Path();
    Path(std::string path);
    Path(std::wstring path);



    int64_t mtimeSec();
    int64_t mtimeMs();

    FILE* fopen(std::string mode);
    void touch(); //创建文件
    //删除文件
    void removeFile();
    //递归删除目录
    void removeDirs();
    //删除目录，不递归
    void removeDir();
    //不管文件还是目录，直接删.目录是递归删
    void remove();
    Path rename(Path toPath);
    Path rename(std::string toPath);
    bool moveToDir(std::string toDir);
    bool moveToDir(Path toDir);

    Path copyTo(Path toPath);
    Result<Path> copyToDir(Path dir);


    Path getAbsolute();

    //是不是child的上级目录
    bool isAncestorOf(Path child);
      
    //把filename换了
    Path replaceFilename(std::string filename);

    //列出子文件/子目录
    std::vector<std::string> list();
    //递归子树
    std::vector<std::string> listSubtree();

    bool isAbsolute();
    bool isFile();
    bool isDirectory();
    bool exists();
    void mkdirs();

    //计算相对路径
    Path relativeToBaseDir(Path basedir);

    Path append(std::string filename);
    //文件名
    std::string basename();
    //文件名，不含后缀
    std::string filenameWithoutExt();

    std::string ext_with_dot();
    std::string ext_without_dot();

    //格式化 分隔符'\'
    Path normal();
    Path dirname();

    //消除路径中的'.', '..'
    Path eliminateDotDir();
    

    //utf8 string
    std::string path();

    //用宽字符存放
    std::wstring _wpath;//wstring string
    //缓存
    std::string _basename;
    //-1:未知, 0: 非dir, 1: 是dir  缓存用的
    char _dirType = -1; 
    char _fileType = -1;

    static void test();
};
void FsUtil_registerMeta();