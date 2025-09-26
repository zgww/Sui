package Sgl

#include <stdio.h>
#include <stdlib.h>

#include "./UnitOpengl.h"
import * from "../Orc/Path.orc"
import * from "../Orc/String.orc"
import * from "../Sui/Core/Timer.orc"

//主类
class Program{

    GLuint id;
    // GLuint vsId;
    // GLuint fsId;

    String@ vsPath;
    String@ fsPath;

    void dtor(){
        if self.id {
            GLuint id = self.id
            //确保在主线程释放
            mkTimerTimeout(^void(){
                deleteProgram(id);
            }, 0)

            // self.clear()
        }
    }

    extern void use()

    // extern void clear()

    const char * getVsPathCstr(){
        if self.vsPath {
            return self.vsPath.str
        }
        return "";
    }
    const char * getFsPathCstr(){
        if self.fsPath {
            return self.fsPath.str
        }
        return "";
    }

    extern bool compile(const char *vs, const char *fs);
    bool compileByPathCstr(const char *vsPath, const char *fsPath){
        String@ vs = Path_readText(vsPath)
        String@ fs = Path_readText(fsPath)

        self.vsPath = str(vsPath)
        self.fsPath = str(fsPath)

        bool ok = self.compile(vs.str, fs.str)
        if !ok {
            printf("编译shader失败. path:%s/.fs\n", vsPath);
            exit(0)
        }
        return ok
    }

    extern void uniform1i(const char *key, int i);
    extern void uniform2f(const char *key, float x, float y);
    extern void uniform3f(const char *key, float x, float y, float z);
    extern void uniform4f(const char *key, float x, float y, float z, float w);
    void uniformMatrix4f(const char *key, float *data){
        self.uniformMatrix4fv(key, data, 1)

    }
    extern void uniformMatrix4fv(const char *key, float *data, int matrixCnt);
}
extern void deleteProgram(GLuint id)