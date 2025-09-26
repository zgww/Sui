package OrcLang

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//字符串需要用对象管理起来
//直接用char@ xx = ""  会导致内存异常释放


class String {
    // -1表示为脏，未赋值
    int _size = -1
    char *data = NULL
    void dtor(){
        if (self.data){
            free(self.data)
        }
    }
    
    String * add(const char *str){
        if (str){
            int addSize = strlen(str)
            int newSize = self.size() + addSize
            self.expand(newSize+1)
            memcpy(self.data + self.size(), str, addSize)
            self._size = newSize
        }

        return self
    }

    int size(){
        if (self._size == -1){
            self._size = strlen(self.data)
        }
        return self._size
    }
    void expand(int needSize){
        self.data = realloc(needSize)
    }

}
String@ str(const char *data){
    String@ ret = new String()
    ret.add(data)
    
    return ret
}