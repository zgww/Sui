package SuiDialog

#include <stdio.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Path.orc"

/// 布局上下文
class FileDialog {


}

//返回 List<String>@
//什么，会修改cwd
extern List@ fileDialog_getOpenFileName(const char *dir, const char *title)
extern String@ fileDialog_getSaveFileName(const char *dir, const char *title)
extern String@ fileDialog_getExistingDirectory(const char *dir, const char *title)

List@ FileDialog_getOpenFileName(const char *dir, const char *title){
    String@ cwd = Path_getcwd()
    List@ ret = fileDialog_getOpenFileName(dir, title)
    Path_setcwd(cwd.str)
    return ret
}


void test(){
    String@ saveFileName = fileDialog_getSaveFileName(".", "title");
    printf("save fileName:%s\n", saveFileName.str);
}