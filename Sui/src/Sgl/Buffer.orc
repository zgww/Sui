
package Sgl

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

import * from "../Orc/String.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Quat.orc"
import * from "../Json/Json.orc"
import * from "./Mat.orc"

//结构体数组，基类
class StructArrayBase{
    //元素数
    int size = 0
    int capacity = 0
    int elementSize = 1

    //需要继承
    void **getPtrData(){
        return null
    }

    //需要继承
    char *getRaw(){
        return NULL
    }

    bool equalsRaw(char *a, char *b){
        for int j = 0; j < self.elementSize; j++{
            if b[j] != a[j]{
                return false
            }
        }
        return true
    }

    //去除重复
    void distinct(){
        char *raw = self.getRaw()
        for int i = 0; i < self.size; i++{
            char *ele = raw + (i * self.elementSize)

            for int j = self.size - 1; j >= i + 1; j++{
                char *b = raw + (i * self.elementSize)
                if self.equalsRaw(ele, b) { //需要去掉
                    // memmove()
                    memmove(b, b + self.elementSize, (self.size - 1 - j) * self.elementSize);
                    self.size--
                }
            }
        }
    }

    bool hasByRaw(char *data){
        char *raw = self.getRaw()
        for int i = 0; i < self.size; i++{
            char *ele = raw + (i * self.elementSize)
            bool eq = true
            for int j = 0; j < self.elementSize; j++{
                if ele[j] != data[j]{
                    eq = false
                    break;
                }
            }
            if eq {
                return true
            }
        }
        return false
    }
    char *getPtrRawAtElement(int index){
        return self.getRaw() + index * self.elementSize
    }
    void setRawAtElement(int index, char *data){
        char *p = self.getRaw() + index * self.elementSize
        memcpy(p, data, self.elementSize)
    }
    void setByPtr(int index, void *data){
        char *p = self.getRaw() + index * self.elementSize
        memcpy(p, data, self.elementSize)
    }
    void appendByCount(void *data, int count){
        self.expandIfNeed(count);
        memcpy(self.getRaw() + self.size * self.elementSize, data, count * self.elementSize)
        self.size += count
    }
    void clear(){
        self.size = 0
    }
    //扩展，直到size >= toSize
    void expandToSize(int toSize){
        if self.size < toSize {
            self.expandIfNeed(toSize - self.size)
            self.size = toSize;
        }
    }
    void expandIfNeed(int addEleSize){
        int newSize = self.size + addEleSize
        if newSize > self.capacity {
            int cap = maxInt(self.capacity * 2, 32)
            // printf("cap:%d, self.cap:%d, newSize:%d\n", cap, self.capacity, newSize)
            if self.capacity < 1000 && cap >= newSize{//翻倍增长
                self.expandCapacity(cap)
            }
            else {
                int exp = maxInt(addEleSize, 10240)
                int toCap = self.size + exp
                self.expandCapacity(toCap)
            }
        }
    }
    void expandCapacity(int needSize){
        if needSize > self.capacity {
            // printf("expandCapacity:%d\n", needSize)
            self.capacity = needSize
            void **pp = self.getPtrData();
            if (*pp == null){
                *pp = calloc(1, needSize * self.elementSize);
                return;
            }
            *pp = realloc(*pp, needSize * self.elementSize)
        }
    }
}

class CharArray extends StructArrayBase{
    char *data

    void ctor(){
        self.elementSize = 1
    }
    String@ toString(){
        String@ ret = str("")
        char *tmp = self.data;
        int l = self.size
        for int i = 0; i < l; i++{
            ret.addi(tmp[i]).add(" ")
        }
        return ret
    }

    void **getPtrData(){
        return (void**)(&self.data)
    }

    //需要继承
    char *getRaw(){
        return (char*)self.data
    }
    char get(int i){
        if i >= self.size {
            return 0.0
        }
        return self.data[i]
    }
    bool set(int i, char v){
        if i < self.size {
            self.data[i] = v
            return true
        }
        return false
    }
    void add(char v){
        self.expandIfNeed(1)
        self.data[self.size] = v;
        self.size++
    }
    bool has(char v){
        return self.hasByRaw((char*)&v)
    }
}
class ShortArray extends StructArrayBase{
    short *data

    void ctor(){
        self.elementSize = 2
    }

    void **getPtrData(){
        return (void**)(&self.data)
    }

    //需要继承
    char *getRaw(){
        return (char*)self.data
    }
    short get(int i){
        if i >= self.size {
            return 0.0
        }
        return self.data[i]
    }
    bool set(int i, short v){
        if i < self.size {
            self.data[i] = v
            return true
        }
        return false
    }
    void add(short v){
        self.expandIfNeed(1)
        self.data[self.size] = v;
        self.size++
    }
    bool has(short v){
        return self.hasByRaw((char*)&v)
    }
}
class FloatArray extends StructArrayBase{
    float *data

    void ctor(){
        self.elementSize = 4
    }

    void **getPtrData(){
        return (void**)(&self.data)
    }

    //需要继承
    char *getRaw(){
        return (char*)self.data
    }
    float get(int i){
        if i >= self.size {
            return 0.0
        }
        return self.data[i]
    }
    bool set(int i, float v){
        if i < self.size {
            self.data[i] = v
            return true
        }
        return false
    }
    void appendFloat3(float a, float b, float c){
        self.add(a)
        self.add(b)
        self.add(c)
    }
    void add(float v){
        self.expandIfNeed(1)
        self.data[self.size] = v;
        self.size++
    }
    bool has(float v){
        return self.hasByRaw((char*)&v)
    }
}
class MatArray extends StructArrayBase{
    Mat *data

    void ctor(){
        self.elementSize = sizeof(Mat)
    }

    void **getPtrData(){
        return (void**)(&self.data)
    }

    //需要继承
    char *getRaw(){
        return (char*)self.data
    }
    Mat get(int i){
        if i >= self.size {
            Mat m;
            m.identity();
            return m
        }
        return self.data[i]
    }
    bool set(int i, Mat v){
        if i >= self.size {
            self.expandToSize(i + 1)
        }
        if i < self.size {
            self.data[i] = v
            return true
        }
        return false
    }
    void add(Mat v){
        self.expandIfNeed(1)
        self.data[self.size] = v;
        self.size++
    }
    bool has(Mat v){
        return self.hasByRaw((char*)&v)
    }
}

class Vec4Array extends StructArrayBase{
    Vec4 *data

    void ctor(){
        self.elementSize = sizeof(Vec4)
    }

    void **getPtrData(){
        return (void**)(&self.data)
    }

    //需要继承
    char *getRaw(){
        return (char*)self.data
    }
    Vec4 get(int i){
        if i >= self.size {
            return mkVec4(0, 0, 0, 0)
        }
        return self.data[i]
    }
    bool set(int i, Vec4 v){
        if i < self.size {
            self.data[i] = v
            return true
        }
        return false
    }
    void add(Vec4 v){
        self.expandIfNeed(1)
        self.data[self.size] = v;
        self.size++
    }
    bool has(Vec4 v){
        return self.hasByRaw((char*)&v)
    }
}

class Vec3Array extends StructArrayBase{
    Vec3 *data

    String@ toString(){
        String@ s = str("")
        for int i = 0; i < self.size; i++{
            Vec3 v = self.get(i)
            s.addf(v.x)
            s.add(",")
            s.addf(v.y)
            s.add(",")
            s.addf(v.z)
            s.add("; ")
            if i % 3 == 2 {
                s.add("\n")
            }
        }
        return s
    }

    void ctor(){
        self.elementSize = sizeof(Vec3)
    }

    void **getPtrData(){
        return (void**)(&self.data)
    }

    //需要继承
    char *getRaw(){
        return (char*)self.data
    }
    Vec3 get(int i){
        if i >= self.size {
            return mkVec3(0, 0, 0)
        }
        return self.data[i]
    }
    bool set(int i, Vec3 v){
        if i < self.size {
            self.data[i] = v
            return true
        }
        return false
    }
    void add(Vec3 v){
        self.expandIfNeed(1)
        self.data[self.size] = v;
        self.size++
    }
    bool has(Vec3 v){
        return self.hasByRaw((char*)&v)
    }
}

class Vec2Array extends StructArrayBase{
    Vec2 *data

    void ctor(){
        self.elementSize = sizeof(Vec2)
    }

    void **getPtrData(){
        return (void**)(&self.data)
    }

    //需要继承
    char *getRaw(){
        return (char*)self.data
    }
    Vec2 get(int i){
        if i >= self.size {
            return mkVec2(0, 0)
        }
        return self.data[i]
    }
    bool set(int i, Vec2 v){
        if i < self.size {
            self.data[i] = v
            return true
        }
        return false
    }
    void add(Vec2 v){
        self.expandIfNeed(1)
        self.data[self.size] = v;
        self.size++
    }
    bool has(Vec2 v){
        return self.hasByRaw((char*)&v)
    }
}

class IntArray {
    int *data;
    int size = 0
    int capacity = 0

    void dtor(){
        if self.data {
            free(self.data)
            self.data = null
        }
    }
}

extension IntArray {
    String@ toString(){
        String@ ret = str("")
        int *tmp = (int*)self.data;
        int l = self.size
        for int i = 0; i < l; i++{
            ret.addi(tmp[i]).add(" ")
        }
        return ret
    }

    bool removeFirst(int v){
        for int i = 0; i < self.size; i++{
            int cv = self.data[i]
            if cv == v {
                self.removeRange(i, i + 1)
                return true
            }
        }
        return false
    }
    bool has(int v){
        for int i = 0; i < self.size; i++{
            int cv = self.data[i]
            if cv == v {
                return true
            }
        }
        return false
    }
    int get(int idx){
        return self.at(idx)
    }
    int at(int idx){
        if idx >= self.size {
            return 0
        }
        return self.data[idx]
    }
    void set(int idx, int v){
        if idx >= self.size {
            self.appendValueByCount(0, idx - self.size + 1)
        }
        self.data[idx] = v
    }
    void clear(){
        self.size = 0
    }
    void pop(int count){
        self.size = maxInt(self.size - count, 0)
    }
    void initSize(int size){
        self.expandCapacity(size)
        self.size = size
    }

    IntArray* appendByCount(void *data, int cnt){
        self.expandIfNeed(cnt)
        memcpy(self.data + self.size, data, cnt * 4)
        self.size += cnt
        return self
    }
    IntArray* appendValueByCount(int v, int cnt){
        self.expandIfNeed(cnt)
        if v != 0 {
            for int i = 0; i < cnt; i++ {
                self.data[self.size + i] = v
            }
        }
        self.size += cnt
        return self
    }
    IntArray* append(int v){
        self.expandIfNeed(1)
        self.data[self.size] = v
        self.size++
        return self
    }
    //左闭右开
    bool removeRange(int fromIndex, int to){
        if fromIndex < 0 {
            return false
        }
        if to > self.size{
            return false
        }
        int cnt = to - fromIndex;
        if cnt == self.size {
            self.size = 0
            return true
        }

        memmove(self.data + fromIndex, self.data + to, (self.size - to) * 4);

        self.size -= cnt
        return true
    }

    void expandIfNeed(int addIntSize){
        int newSize = self.size + addIntSize
        if newSize > self.capacity {
            int cap = self.capacity * 2
            // printf("cap:%d, self.cap:%d, newSize:%d\n", cap, self.capacity, newSize)
            if self.capacity < 1000 && cap >= newSize{//翻倍增长
                self.expandCapacity(cap)
            }
            else {
                int exp = maxInt(addIntSize, 10240)
                int toCap = self.size + exp
                self.expandCapacity(toCap)
            }
        }
    }
    void expandCapacity(int needSize){
        if needSize > self.capacity {
            // printf("expandCapacity:%d, cap:%d\n", needSize, self.capacity)
            self.capacity = needSize
            if (self.data == null){
                self.data = calloc(1, needSize * 4);
                return;
            }
            self.data = realloc(self.data, needSize * 4)
        }
    }

    void fromJson(Json* ja){
        if ja.isArray(){
            self.clear()
            self.expandCapacity(ja.size())
            int l = ja.size()
            for int i = 0; i < l; i++{
                int v = ja.atAsInt(i)
                self.append(v)
            }
        }
    }
    Json@ mkJson(){
        Json@ ja = Json_mkArray()
        for int i = 0; i < self.size; i++{
            ja.addNumber(self.data[i])
        }
        return ja
    }
}

//内存里的区域
class Buffer {
    unsigned char *data;
    int size = 0
    int capacity = 0
    void dtor(){
        if self.data {
            free(self.data)
            self.data = null
        }
    }

    // float *floatView(){
    //     return (float*)self.data;
    // }
}
extension Buffer {
    void initSize(int size){
        self.expandCapacity(size)
        self.size = size
    }

    String@ toFloatString(){
        String@ ret = str("")
        float *tmp = (float*)self.data;
        int l = self.floatSize()
        for int i = 0; i < l; i++{
            ret.addf(tmp[i]).add(" ")
        }
        return ret
    }
    String@ toIntString(){
        String@ ret = str("")
        int *tmp = (int*)self.data;
        int l = self.intSize()
        for int i = 0; i < l; i++{
            ret.addi(tmp[i]).add(" ")
        }
        return ret
    }
    int doubleSize(){
        return self.size / doubleSize()
    }
    int floatSize(){
        return self.size / floatSize()
    }

    int intSize(){
        return self.size / intSize()
    }

    Buffer* appendBuffer(Buffer* buf){
        if buf.data{
            self.append(buf.data, buf.size)
        }
        return self
    }

    Buffer* appendChars(char *data, int size){
        self.append((unsigned char*)data, size)
        return self
    }
    Buffer* append(unsigned char *data, int size){
        self.expandIfNeed(size)
        memcpy(self.data + self.size, data, size)
        self.size += size
        return self
    }
    Buffer* appendFloat(float v){
        self.expandIfNeed(4)
        float *p = (float*)(self.data+self.size);
        *p = v;
        self.size +=4
        return self
    }
    Buffer* appendFloat4(float a, float b, float c, float d){
        self.expandIfNeed(16)
        float *p = (float*)(self.data+self.size);
        *p = a;
        *(p+1) = b;
        *(p+2) = c;
        *(p+3) = d;
        self.size += 16
        return self
    }
    Buffer* appendVec3(Vec3 v3){
        self.expandIfNeed(12)
        float *p = (float*)(self.data+self.size);
        *p = v3.x;
        *(p+1) = v3.y;
        *(p+2) = v3.z;
        self.size += 12
        return self
    }
    Buffer* appendFloat3(float a, float b, float c){
        self.expandIfNeed(12)
        float *p = (float*)(self.data+self.size);
        *p = a;
        *(p+1) = b;
        *(p+2) = c;
        self.size += 12
        return self
    }
    Buffer* appendFloat2(float v, float b){
        self.expandIfNeed(8)
        float *p = (float*)(self.data+self.size);
        *p = v;
        *(p+1) = b;
        self.size += 8
        return self
    }
    Buffer* appendFloats(float *data, int floatCount){
        self.append((unsigned char *)data, floatCount * 4)
        return self
    }
    Buffer* appendCstr(char * str){
        int len = strlen(str);
        self.expandIfNeed(len + 1)//含最后的'\0'. 但是'\0'不计入数量
        memcpy(self.data + self.size, str, len + 1);
        self.size += len
        return self
    }
    Buffer* appendInt(int v){
        self.expandIfNeed(4)
        int *p = (int*)(self.data+self.size);
        *p = v;
        self.size +=4
        return self
    }
    Buffer* appendInt3(int a, int b, int c){
        self.expandIfNeed(12)
        int *p = (int*)(self.data+self.size);
        *p = a;
        *(p+1) = b;
        *(p+2) = c;
        self.size +=12
        return self
    }
    Buffer* appendInts(int *data, int intCount){
        self.append((unsigned char *)data, intCount * 4)
        return self
    }

    void clear(){
        self.size = 0
    }
    void pop(int count){
        self.size = maxInt(self.size - count, 0)
    }

    //左闭右开
    bool removeRange(int fromIndex, int to){
        if fromIndex < 0 {
            return false
        }
        if to > self.size{
            return false
        }
        int cnt = to - fromIndex;
        if cnt == self.size {
            self.size = 0
            return true
        }

        memmove(self.data + fromIndex, self.data + to, self.size - to);

        self.size -= cnt
        return true
    }


    void expandIfNeed(int addByteSize){
        int newSize = self.size + addByteSize
        if newSize > self.capacity {
            int cap = self.capacity * 2
            if cap < 10000 && cap >= newSize{//翻倍增长
                self.expandCapacity(cap)
            }
            else {
                self.expandCapacity(newSize)
            }
        }
    }


    void expandCapacity(int needSize){
        self.capacity = needSize
        if (self.data == null){
            self.data = calloc(1, needSize);
            return;
        }
        self.data = realloc(self.data, needSize)
    }
}

extern Buffer@ Buffer_readFile(const char *path)

//输入Buffer
class BufferReader {
    Buffer@ buffer;
    int index = 0

    BufferReader * init(Buffer* buffer){
        self.buffer = buffer
        return self
    }

    int remaining(){
        return self.buffer.size - self.index
    }

    void advance(int byteLen){
        self.index += byteLen;
    }

    void readBinary(void *p, int byteLen){
        unsigned char *pdata = self.buffer.data+self.index
        memcpy(p, pdata, byteLen);
        self.index += byteLen
    }
    String@ readString(int byteLen){
        String@ r = str("")
        unsigned char *pdata = self.buffer.data+self.index
        r.addBytesWithCount((char*)pdata, byteLen)
        self.index += byteLen
        return r
    }

    unsigned char readUint8(){
        unsigned char c = self.buffer.data[self.index]
        self.index++
        return c;
    }
    void readChars(char *dst, int cnt, bool setNullTail){
        memcpy(dst, self.buffer.data + self.index, cnt)
        if setNullTail {
            dst[cnt] = 0;
        }
        self.index += cnt
    }
    unsigned char readByte(){
        unsigned char c = self.buffer.data[self.index]
        self.index++
        return c;
    }
    short readInt16(){
        short *p = (short *)(self.buffer.data+self.index)
        short v = *p;
        self.index+= 2
        return v;
    }
    short readShort(){
        short *p = (short *)(self.buffer.data+self.index)
        short v = *p;
        self.index+= 2
        return v;
    }
    int readInt(){
        int *p = (int *)(self.buffer.data+self.index)
        int v = *p;
        self.index+= 4
        return v;
    }
    long long readLongLong(){
        long long *p = (long long *)(self.buffer.data+self.index)
        long long v = *p;
        self.index+= 8
        return v;
    }
    CharArray@ readCharArray(int cnt){
        CharArray@ r = new CharArray()
        r.appendByCount(self.buffer.data + self.index, cnt)
        self.index += cnt * 1
        return r
    }
    ShortArray@ readShortArray(int cnt){
        ShortArray@ r = new ShortArray()
        r.appendByCount(self.buffer.data + self.index, cnt)
        self.index += cnt * 2
        return r
    }
    IntArray@ readIntArray(int cnt){
        IntArray@ r = new IntArray()
        r.appendByCount(self.buffer.data + self.index, cnt)
        self.index += cnt * 4
        return r
    }
    Vec2Array@ readVec2Array(int cnt){
        Vec2Array@ r = new Vec2Array()
        r.appendByCount(self.buffer.data + self.index, cnt)
        self.index += cnt * 8
        return r
    }
    Vec4Array@ readVec4Array(int cnt){
        Vec4Array@ r = new Vec4Array()
        r.appendByCount(self.buffer.data + self.index, cnt)
        self.index += cnt * 16
        return r
    }
    Vec3Array@ readVec3Array(int cnt){
        Vec3Array@ r = new Vec3Array()
        r.appendByCount(self.buffer.data + self.index, cnt)
        self.index += cnt * 12
        return r
    }
    Vec3 readVec3(){
        Vec3 r;
        float *p = (float *)(self.buffer.data+self.index)
        memcpy(&r, p, 12);
        self.index+= 12
        return r;
    }
    Vec4 readVec4(){
        Vec4 r;
        float *p = (float *)(self.buffer.data+self.index)
        memcpy(&r, p, 16);
        self.index+= 16
        return r;
    }
    Quat readQuat(){
        Quat r;
        float *p = (float *)(self.buffer.data+self.index)
        memcpy(&r, p, 16);
        self.index+= 16
        return r;
    }
    float readFloat(){
        float *p = (float *)(self.buffer.data+self.index)
        float v = *p;
        self.index+= 4
        return v;
    }
    double readDouble(){
        double *p = (double *)(self.buffer.data+self.index)
        double v = *p;
        self.index += 8
        return v;
    }
}
BufferReader@ mkBufferReader(Buffer* buffer){
    BufferReader@ r = new BufferReader()
    r.buffer = buffer
    return r
}

Buffer@ mkBufferFloatByJsonArray(Json@ jo){
    Buffer@ buf = new Buffer()

    if jo.isArray(){
        int l = jo.size()
        for int i = 0; i < l; i++{
            float v = (float)jo.atAsNumber(i)
            buf.appendFloats(&v, 1)
        }
    }

    return buf
}

Buffer@ mkBufferIntByJsonArray(Json@ jo){
    Buffer@ buf = new Buffer()

    if jo.isArray(){
        int l = jo.size()
        for int i = 0; i < l; i++{
            int v = (int)jo.atAsNumber(i)
            buf.appendInts(&v, 1)
        }
    }

    return buf
}

struct FloatsProxy {
    float *data
    int capacity
    int size
}
FloatsProxy mkFloatsProxy(float *floats, int capacity){
    FloatsProxy r
    r.data = floats
    r.capacity = capacity
    r.size = 0
    return r
}

extension FloatsProxy{
    void fillRemainsByValue(float v){
        for int i = self.size; i < self.capacity; i++{
            self.data[i] = v
        }
    }
    void appendFloats(float *a, int cnt){
        if self.size + cnt <= self.capacity {
            for int i = 0 ; i < cnt; i++{
                self.data[self.size] = a[i]
                self.size++
            }
        }
    }
    void appendFloat(float v){
        if self.size + 1 <= self.capacity {
            self.data[self.size] = v
            self.size++
        }
    }
    void appendFloat2(float a, float b){
        if self.size + 2 <= self.capacity {
            self.data[self.size] = a
            self.size++

            self.data[self.size] = b
            self.size++
        }
    }
    void appendFloat3(float a, float b, float c){
        if self.size + 3 <= self.capacity {
            self.data[self.size] = a
            self.size++

            self.data[self.size] = b
            self.size++

            self.data[self.size] = c
            self.size++
        }
    }
    void appendFloat4(float a, float b, float c, float d){
        if self.size + 4 <= self.capacity {
            self.data[self.size] = a
            self.size++

            self.data[self.size] = b
            self.size++

            self.data[self.size] = c
            self.size++

            self.data[self.size] = d
            self.size++
        }
    }
    void distinctSelf(){
        self.size = Floats_distinct(self.data, self.size)
    }
    bool distinctTo(FloatsProxy *fp){
        if fp.capacity < self.size {
            return false
        }
        fp.size = Floats_distinctTo(self.data, fp.data, self.size)
        return true
    }
    bool has(float v){
        return Floats_has(self.data, self.size, v)
    }
    void setAllCapacity(float v){
        Floats_set(self.data, self.capacity, v)
        self.size = self.capacity
    }
    void set(int i, float v){
        if i < self.size {
            self.data[i] = v
        }
    }
    void append(float v){
        if self.size < self.capacity {
            self.data[self.size] = v
            self.size++
        }
    }
    void clear(){
        self.size = 0
    }
    bool removeRange(int fromIndex, int toExcludeIndex){
        toExcludeIndex = minInt(self.size, toExcludeIndex)
        fromIndex = maxInt(0, fromIndex)

        //异常
        if fromIndex > toExcludeIndex {
            return false
        }
        if fromIndex == toExcludeIndex {
            return true
        }

        int cnt = self.size - toExcludeIndex
        memmove(self.data + fromIndex, self.data + toExcludeIndex, cnt)
        self.size -= cnt

        return true
    }
}


// 冒泡排序函数
void Floats_bubbleSort(float *arr, int len, bool asc){
    if asc { //升序
        for (int i = 0; i < len - 1; i++) {
            for (int j = 0; j < len - 1 - i; j++) {
                // 交换元素位置
                if (arr[j] > arr[j + 1]) {
                    float temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
    else { //降序
        for (int i = 0; i < len - 1; i++) {
            for (int j = 0; j < len - 1 - i; j++) {
                // 交换元素位置
                if (arr[j] < arr[j + 1]) {
                    float temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}
int Floats_distinct(float *floats, int cnt){
    int dstIdx = 0
    for int i = 0; i < cnt; i++{
        float v = floats[i]
        if !Floats_has(floats, dstIdx, v){
            floats[dstIdx] = v;
            dstIdx++
        }
    }
    return dstIdx
}
int Floats_distinctTo(float *floats, float *target, int cnt){
    int targetCnt = 0
    for int i = 0; i < cnt; i++{
        float v = floats[i]
        if !Floats_has(target, targetCnt, v){
            target[targetCnt] = v;
            targetCnt++
        }
    }
    return targetCnt
}
bool Floats_has(float *floats, int cnt, float value){
    for int i = 0; i < cnt; i++{
        if floats[i] == value{
            return true
        }
    }
    return false
}
void Floats_set(float *floats, int cnt, float value){
    for int i = 0; i < cnt; i++{
        floats[i] = value
    }
}

void testIntArray(){
    IntArray@ ia = new IntArray()
    ia.expandCapacity(1500)
    for int i = 0; i < 2000; i++{
        ia.append(i)
    }
    printf("ia:%s\n", ia.toString().str)
}

void testBuffer(){
    Buffer@ buf = Buffer_readFile("../asset/100.w3e")
    buf.appendChars("", 1)
    printf("content:%s\n", buf.data)

    BufferReader@ br = mkBufferReader(buf)
    String@ head = br.readString(4)
    printf("head:%s. eq:%d\n", head.str, head.equals("W3E!"))
}