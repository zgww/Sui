package Orc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

import * from "./List.orc"
import * from "./Map.orc"
import * from "./Math.orc"
import * from "./ScopeData.orc"

//字符串需要用对象管理起来
//直接用char@ xx = ""  会导致内存异常释放
class String {
    char *str = NULL
    // -1表示为脏，未赋值
    int _charSize = -1
    int _runeSize = -1 //字符数
    int capacity = 0 //容量
    // int *indexes = NULL //字符索引 
    void dtor(){
        // if (self.indexes == NULL){
        //     free(self.indexes)
        //     self.indexes = NULL
        // }
        // printf("释放掉String:%p, %s\n", self, self.str)
        if (self.str){
            free(self.str)
        }
    }
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

String@ String_join(List* list, const char *dep){
    String@ ret = str("")
    if list {
        int l = list.size()
        for int i = 0; i < l; i++{
            String* part = (String*)list.get(i)
            ret.addString(part)
            if i < l - 1 {
                ret.add(dep)
            }
        }
    }
    return ret
}

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
bool String_endsWithIgnoreCase(const char *s, const char *find){
    if !s {
        return false
    }
    int findlen = strlen(find)
    int slen = strlen(s)
    //长度不足,肯定false
    if slen < findlen {
        return false
    }
    const char *tmp = s + slen - findlen;
    bool ok = stricmp(tmp, find) == 0
    return ok
}
bool String_endsWith(const char *s, const char *find){
        if !s {
            return false
        }
        int findlen = strlen(find)
        int slen = strlen(s)
        //长度不足,肯定false
        if slen < findlen {
            return false
        }
        const char *tmp = s + slen - findlen;
        bool ok = strcmp(tmp, find) == 0
        return ok
}

// str表示 char*, String表示封装的String类

bool strEq(const char *a, const char *b){
    return strcmp(a, b) == 0;
}

// extern String@ strf(const char *fmt)

String@ str(const char *data){
    String@ ret = new String()
    ret.add(data)
    
    return ret
}

extension String {
    int toInt(){
        if !self.str {
            return 0
        }
        return atoi(self.str)
    }
    float toFloat(){
        if !self.str {
            return 0
        }
        return atof(self.str)
    }
    String* addPtr(void *p){
        char data[100];
        snprintf(data, 99, "%p", p);
        self.add(data);
        return self;
    }
    String* addll(long long i){
        char data[200];
        snprintf(data, 199, "%lld", i);
        self.add(data);
        return self;
    }
    String* addc(char c){
        char data[20];
        snprintf(data, 19, "%c", c);
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
    String *addDouble(double i){
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

        // if count <= 0 || str == NULL || str[0] == 0 {
        //     return self
        // }

        if str {
            memcpy(self.str + self.charSize(), str, addSize) //+1是为了最后的'\0'
        }
        self._charSize = newSize
        self.str[newSize] = 0
        self._runeSize = -1
        return self
    }
    String * add(const char *str){
        if (self.str == NULL){
            self.str = _strdup(str)
            self.capacity = strlen(self.str) + 1
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
        self.capacity = strlen(str) + 1
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
        if self == null{
            return 0
        }
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
            self.capacity = needSize;
            return
        }
        int x2 = self.capacity * 2
        if x2 < 10000 && x2 > needSize {
            needSize = x2;
        }
        self.str = realloc(self.str, needSize)
        self.capacity = needSize;
    }

    String@ trimLeft(){
        return self.trimChars(" \t\n\r", true, false)
    }
    String@ trimRight(){
        return self.trimChars(" \t\n\r", false, true)
    }
    String@ trim(){
        return self.trimChars(" \t\n\r", true, true)
    }
    String@ trimChars(const char *chars, bool trimLeft, bool trimRight){
        int start = 0;
        int l = self.charSize()
        int cl = strlen(chars)
        if trimLeft{
            for (int i = 0; i < l; i++){
                bool found = false;
                for (int j = 0; j < cl; j++){
                    if (self.str[i] == chars[j]){
                        found = true;
                        break;
                    }
                }  
                if !found {
                    start = i;
                    break;
                }
            }
        }

        int end = l;
        if trimRight{
            for (int i = l - 1; i >= 0; i--){
                bool found = false;
                for (int j = 0; j < cl; j++){
                    if (self.str[i] == chars[j]){
                        found = true;
                        break;
                    }
                }
                if !found {
                    end = i + 1;
                    break;
                }
            }
        }
        return self.substringByByteRange(start, end)
    }



    //utf8符号数
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
    String@ substringByByteCount(int start, int count){
        String@ ret = new String();
        return ret.addBytesWithCount(self.str + start, count);
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
        return ((long long)tmp) - ((long long)self.str)
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

    List@ splitToLines(){
        List@ ret = new List()
        int start = 0
        int len = self.charSize()
        for int i = 0; i < len; i++{
            if (self.str[i] == '\n' || self.str[i] == '\r'){
                String@ line = self.substringByByteRange(start, i);
                ret.add(line);

                if (self.str[i] == '\r' && i + 1 < len && self.str[i + 1] == '\n'){
                    i++
                }
                start = i + 1; //跳过换行符
            }       
        }

        return ret
    }

    String@ clone(){
        return str(self.str ? self.str : "")
    }


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
    bool equalsIgnoreCase(const char *str){
        if (self.str == str){
            return true;
        }
        if (str == null || self.str == null){
            return false;
        }
        int ret = _stricmp(self.str, str);
        return ret == 0
    }
    bool equals(const char *str){
        if self == null {
            return str == null
        }
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
        if str == null {
            return null == self
        }
        return self.equals(str.str);
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
    bool startsWith(const char *find){
        return String_startsWith(self.str, find)
    }
    bool endsWith(const char *find){ 
        return String_endsWith(self.str, find)
    }
}

struct PrintStyle {
    
    int color;
    int bg;
    //0 终端默认设置（黑底白字）
    // 1 高亮显示
    // 4 使用下划线
    // 5 闪烁
    // 7 反白显示
    // 8 不可见
    int code; 

    ScopeData (*__exit__)(void*_self);
}
static ScopeData PrintStyle__exit__(PrintStyle *_self){
    if _self.color {
        printf("\033[0;0;0m\033[%d;%dm", _self.code, _self.color);
    }
    return mkScopeData(_self, (void*)PrintStyle_exit)
}
extension PrintStyle {
    PrintStyle* black(){
        self.color = 30;
        return self
    }
    PrintStyle* red(){
        self.color = 31;
        return self
    }
    PrintStyle* green(){
        self.color = 32;
        return self
    }
    PrintStyle* yellow(){
        self.color = 33;
        return self
    }
    PrintStyle* blue(){
        self.color = 34;
        return self
    }
    PrintStyle* purple(){
        self.color = 35;
        return self
    }
    PrintStyle* cyan(){
        self.color = 36;
        return self
    }
    PrintStyle* white(){
        self.color = 37;
        return self
    }
    PrintStyle* bgblack(){
        self.color = 40;
        return self
    }
    PrintStyle* bgred(){
        self.color = 41;
        return self
    }
    PrintStyle* bggreen(){
        self.color = 42;
        return self
    }
    PrintStyle* bgyellow(){
        self.color = 43;
        return self
    }
    PrintStyle* bgblue(){
        self.color = 44;
        return self
    }
    PrintStyle* bgpurple(){
        self.color = 45;
        return self
    }
    PrintStyle* bgcyan(){
        self.color = 46;
        return self
    }
    PrintStyle* bgwhite(){
        self.color = 47;
        return self
    }
}
PrintStyle mkPrintStyle(){
    PrintStyle r
    r.bg = 0
    r.color = 31
    r.code = 1;
    r.__exit__ = PrintStyle__exit__
    return r
}
void PrintStyle_exit(ScopeData  *scopeData){
    printf("\033[0m\n");
}

void testOk(bool ok, const char *msg){
    if !ok {
        printf("\033[1;31mtest fail: %s\033[0m\n", msg);
    }
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

    String@ tmp = (String@)map.get("key")
    String@ tmp2 = (String@)list.get(0)
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
    {
        mkPrintStyle().red().{
            printf("hi")
        }
    }
}