package OrcLang

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

import * from "./List.orc"
import * from "./Map.orc"
import * from "./Math.orc"

//字符串需要用对象管理起来
//直接用char@ xx = ""  会导致内存异常释放
class String {

    char *str = NULL
    // -1表示为脏，未赋值
    int _charSize = -1
    int _runeSize = -1 //字符数
    // int *indexes = NULL //字符索引 
    void dtor(){
        // if (self.indexes == NULL){
        //     free(self.indexes)
        //     self.indexes = NULL
        // }
        if (self.str){
            // printf("释放掉String:%s\n", self.str)
            free(self.str)
        }
    }
    String* addll(long long i){
        char data[200];
        snprintf(data, 199, "%lld", i);
        self.add(data);
        return self;
    }
    String* addi(int i){
        char data[200];
        snprintf(data, 199, "%d", i);
        self.add(data);
        return self;
    }
    String *addf(float i){
        char data[200];
        snprintf(data, 199, "%f", i);
        self.add(data);
        return self;
    }
    String *addString(String* s){
        if (s){
            self.add(s.str);
        }
        return self;
    }
    //添加字符串中的一部分
    String * addBytesWithCount(const char *str, int count){
        int addSize = minInt(count, strlen(str))
        int newSize = self.charSize() + addSize
        self.expand(newSize+1)
        memcpy(self.str + self.charSize(), str, addSize) //+1是为了最后的'\0'
        self._charSize = newSize
        self.str[newSize] = 0
        self._runeSize = -1
        return self
    }
    String * add(const char *str){
        if (self.str == NULL){
            self.str = _strdup(str)
            return self
        }

        if (str){
            int addSize = strlen(str)
            int newSize = self.charSize() + addSize
            self.expand(newSize+1)
            memcpy(self.str + self.charSize(), str, addSize+1) //+1是为了最后的'\0'
            self._charSize = newSize
            self._runeSize = -1
        }

        return self
    }
    void fillCount(const char *s, int count){
        for (int i = 0; i < count; i++){
            self.add(s)
        }
    }
    //以转移所有权的方式设值
    String* set_as_own(char *str){
        if (self.str){
            free(self.str);
        }
        self.str = str;
        return self;
    }
    String* set(const char *str){
        if (self.equals(str)){//相等
            return self
        }
        self.clear()
        self.add(str)
        return self
    }


    //字符数,不考虑编码
    int charSize(){
        if (self.str == null){
            return 0
        }
        if (self._charSize == -1){
            self._charSize = strlen(self.str)
        }
        return self._charSize
    } 

    void expand(int needSize){
        if (self.str == null){
            self.str = calloc(1, needSize);
        }
        self.str = realloc(self.str, needSize)
    }
    bool notEquals(const char *str){
        return !self.equals(str)
    }
    bool empty(){
        return self.str == NULL || self.str[0] == 0
    }
    
    bool notEmpty(){
        return !self.empty()
    }

    bool equalsIgnoreCase(const char *str){
        if (self.str == str){
            return true;
        }
        if (str == null || self.str == null){
            return false;
        }
        int ret = stricmp(self.str, str);
        return ret == 0
    }
    bool equals(const char *str){
        if (self.str == str){
            return true;
        }
        if (str == null || self.str == null){
            return false;
        }
        int ret = strcmp(self.str, str);
        return ret == 0
    }
    bool equalsString(String *str){
        return self.equals(str.str);
    }

    //utf8符号数
    int runeSize(){
        if (self._runeSize == -1){
            self._runeSize = self.calcRuneSize()
        }
        return self._runeSize
    }
    extern int calcRuneSize()

    int size(){
        return self.runeSize()
    }    
    int length(){
        return self.runeSize()
    }
    //按utf8符号截取
    //以符号为单位
    String@ substring(int start, int end){
        return self.substringByCount(start, end - start)
    }
    //以符号为单位
    String@ substringToEnd(int start){
        return self.substringByCount(start, self.length() - start)
    }

    extern String@ _substringByCount(int start, int n)
    //以符号为单位
    String@ substringByCount(int start, int n){
        return self._substringByCount(start, n)
    }

    // 左闭右开
    String@ substringByByteRange(int start, int end){
        return self.substringByByteCount(start, end - start)
    }
    String@ substringByByteStart(int start){
        String@ ret = new String();
        return ret.addBytesWithCount(self.str + start, self.charSize() - start);
    }
    String@ substringByByteCount(int start, int end){
        String@ ret = new String();
        return ret.addBytesWithCount(self.str + start, end - start);
    }

    //注意，返回的是以字节为单位的
    int indexByteOf(const char *cstr){
        if (self.str == null){
            return -1
        }
        const char *tmp = strstr(self.str, cstr);
        if (tmp == null){
            return -1
        }
        return ((int)tmp) - ((int)self.str)
    }

    //注意，返回的是以字节为单位的
    int lastIndexByteOf(const char *cstr){
        if (self.str == null || cstr == null || strlen(cstr) == 0){
            return -1
        }
        for (int i = self.charSize() - 1; i >= 0; i--){
            bool ok = String_startsWith(self.str + i, cstr);
            if (ok){
                return i;
            }
        }
        return -1
    }

    extern String@ replaceAll(const char *find, const char *newStr)
    extern String@ replaceAllByRe(const char *pattern, const char *newStr)
    
    // //创建索引 
    // void createIndexes(){
    //     if (self.str && self.indexes == NULL){

    //     }
    // }

    
    void clear(){
        if (self.str){ 
            self.str[0] = 0 
            self._charSize = -1
            self._runeSize = -1
        }
    }

    // const char *c_str(){
    //     return self.str
    // }

    extern List@ splitByRe(const char *pattern)
}


// //以字符为单位
// class Utf8StringView {

// 	void enableRuneIndexes(){
//         if (self.runeIndexes != NULL) {
//             return;
//         }
//         self.updateRuneIndexes();
//     }
// 	void updateRuneIndexes(){
//         int _runeLength = self.length();
//         if (self.runeIndexes != NULL) {
//             free(self.runeIndexes)
//         }
//         self.runeIndexes = malloc(sizeof(int) * _runeLength)
//         const char* s = self.utf8string.str;
//         int charLen = self.utf8string.charSize();
//         int start = 0;
//         int runeIndex = 0;
//         while (start < charLen) {
//             self.runeIndexes[runeIndex] = start;
//             runeIndex++;
//             start = start + utf8CharLen(s + start);
//         }
//     }
// 	void ctor(std::string utf8string){

//     }
// 	void dtor(){
//         if (self.runeIndexes != NULL){
//             free(self.runeIndexes)
//         }
//     }

// 	int length(){
//         return self.utf8string.size()
//     }
// 	//可优化：可以添加位置数组，从而加快?
// 	std::string substr(int start, int len){
//         if (start < 0) {
//             start = 0;
//         }

//         if (self.runeIndexes != NULL) { //带索引
//             if (start >= length()) {
//                 return "";
//             }

//             int cstart = self.runeIndexes[start];

//             if (len == -1) {
//                 return self.utf8string.substr(cstart, self.utf8String.size());
//             }

//             int end = start + len;
//             end = std::min(length(), end);

//             int cend = runeIndexes[end - 1] + 1;
//             int clen = cend - cstart;
//             if (clen > 0) {
//                 return utf8string.substr(cstart, clen);
//             }
//             return "";
//         }
//         return Utf8Util::substr(utf8string, start, len);
//     }

// 	int _length = -1;
// 	String@ utf8string;

// 	int* runeIndexes = NULL;
// };

extern String@ strByWcs(const wchar_t *data)
//共几个字符
extern int utf8RuneLength(const char *data)
//一个字符几个字节
extern int utf8CharLen(const char *data)
//n个字符占几个字节
extern int utf8NumberCharLen(const char *data, int runeCnt)

//转为当前代码页的编码格式
extern String@ String_toActiveCodePage(const char *utf8);

bool String_startsWith(const char *s, const char *find){
    if (s == null || find == null){
        return false;
    }
    int slen = strlen(s);
    int findLen = strlen(find);
    if (slen < findLen){
        return false;
    }
    for (int i = 0; i < findLen; i++){
        if (s[i] != find[i]){
            return false;
        }
    }
    return true;
}

// str表示 char*, String表示封装的String类

bool strEq(const char *a, const char *b){
    return strcmp(a, b) == 0;
}


String@ str(const char *data){
    String@ ret = new String()
    ret.add(data)
    
    return ret
}
void testStr() {
    String@ s = str("你好吗");
    s.add("添加的字符串")

    s.add("-第二段-").add("??链式调用??").addf(123.f).add(" int:").addi(12389273)
    printf("testStr:%s\n", s.str)

     
    List@ list = new List()
    list.add(s) 

    Map@ map = new Map()
    map.put("key", s )
    String@ str2 = s
    str2.add("-str2-");
    printf(" str2:%s\n", str2.str)

    printf("list size:%d\n", list.size())
    printf("map size:%d\n", map.size())

    String@ tmp = map.get("key")
    String@ tmp2 = list.get(0)
    printf("map value:%s\n", tmp.str);
    printf("list value:%s\n", tmp2.str);

    list.remove(s)
    map.del("key")

    printf("list size:%d\n", list.size())
    printf("map size:%d\n", map.size())


    {
        String@ tmp = str("123$45^67^8")
        String@ out = tmp.replaceAll("^", "+^^+")
        printf("replaceAll :%s\n", out.str);
    }
    {
        String@ tmp = str("123$45^67^8")
        String@ out = tmp.replaceAllByRe("\\d+", "d")
        printf("replaceAllByRe :%s\n", out.str);
    }
    {
        String@ tmp = str("1\\23\\45^67^8")
        String@ out = tmp.replaceAllByRe("\\\\+", "/")
        printf("replaceAllByRe :%s\n", out.str);
    }
}