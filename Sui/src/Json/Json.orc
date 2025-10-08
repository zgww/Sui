package Json

#include "./cJSON.h"
#include "../Orc/Orc.h"
#include <stdio.h>
#include <string.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Number.orc"


class Json {
    // 0:null,1:bool, 2: number, 3:string, 4: object, 5: array
    int kind = 0
    bool boolValue
    double numberValue
    String@ stringValue
    List@ list = null
    Map@ map = null

    void dtor(){
        // printf("~Json. kind:%d\n", self.kind)
    }

    // 序列化
    extern String@ dump()

    //写入文件
    void dumpToFileByPathCstr(const char *path){
        String@ text = self.dump()
        Path_writeText(path, text.str)
    }

    String@ toString(){
        return self.dump()
    }


    void setNull(){
        self.kind = 0
    }

    bool isBool(){
        return self.kind == 1
    }
    bool isNumber(){
        return self.kind == 2
    }
    bool isString(){
        return self.kind == 3
    }
    bool isObject(){
        return self.kind == 4
    }
    bool isArray(){
        return self.kind == 5
    }
    bool isNull(){
        if self.kind == 0 {
            return true
        }
        if self.kind == 4 && !self.map {
            return true;
        }
        if self.kind == 5 && !self.list {
            return true;
        }
        return false
    }
    String@ asString(){
        if self.kind == 1 {
            return str(self.boolValue ? "true":"false");
        }
        if self.kind == 2 {
            return str("").addDouble(self.numberValue)
        }
        if self.kind == 3 {
            return self.stringValue ? self.stringValue: str("")
        }
        return str("")
    }
    bool asBool(){
        if self.kind == 0 {
            return false
        }
        if self.kind == 1 {
            return self.boolValue 
        }
        if self.kind == 2 {
            return self.numberValue? true: false
        }
        return false;
    }
    int asInt(){
        if self.kind == 0 {
            return 0
        }
        if self.kind == 1 {
            return self.boolValue ? 1 : 0;
        }
        if self.kind == 2 {
            return (int)self.numberValue
        }
        return 0;
    }
    double asNumber(){
        if self.kind == 0 {
            return 0
        }
        if self.kind == 1 {
            return self.boolValue ? 1 : 0;
        }
        if self.kind == 2 {
            return self.numberValue
        }
        return 0;
    }
    int size(){
        if self.kind == 5 {
            return self.arraySize()
        }
        if self.kind == 4 {
            return self.keySize()
        }
        return 0
    }
    int arraySize(){
        if self.kind == 5 {
            if self.list == null{
                return 0
            }
            return self.list.size()
        }
        return 0
    }
    int keySize(){
        if self.kind == 4 {
            if self.map == null{
                return 0
            }
            return self.map.size()
        }
        return 0
    }
    List@ keys(){
        if self.kind == 4 {
            if self.map != null{
                return self.map.keys()
            }
        }
        return new List()
    }
    int atAsInt(int i){
        Json@ ret = self.at(i)
        return ret.asInt()
    }
    double atAsNumber(int i){
        Json@ ret = self.at(i)
        return ret.asNumber()
    }
    bool atAsBool(int i){
        Json@ ret = self.at(i)
        return ret.asBool()
    }
    String@ atAsString(int i){
        Json@ ret = self.at(i)
        return ret.asString()
    }
    Json@ at(int i){
        if self.kind == 5 {
            if self.list !=null{
                return (Json@)self.list.get(i)
            }
        }
        return null
    }
    bool hasKey(const char *key){
        if self.kind == 4 {
            if self.map != null{
                bool b = self.map.has(key)
                return b
            }
        }
        return false
    }
    Json@ get(const char* key){
        if self.kind == 4 {
            if self.map !=null{
                return (Json@)self.map.get(key)
            }
        }
        return null
    }
    int getInt(const char *key){
        Json@ ret = self.get(key)
        if !ret {
            return 0
        }
        return ret.asInt()
    }
    double getNumber(const char *key){
        Json@ ret = self.get(key)
        if !ret {
            return 0.0
        }
        return ret.asNumber()
    }
    //有键才会更新值
    void getToBool(const char *key,  bool *p){
        if self.hasKey(key){
            *p = self.getBool(key)
        }
    }
    void getToInt(const char *key,  int *p){
        if self.hasKey(key){
            *p = (int)self.getNumber(key)
        }
    }
    void getToFloat(const char *key,  float *p){
        if self.hasKey(key){
            *p = (float)self.getNumber(key)
        }
    }
    bool getBool(const char *key){
        Json@ ret = self.get(key)
        if !ret {
            return false
        }

        return ret.asBool()
    }
    String@ getString(const char *key){
        Json@ ret = self.get(key)
        if ret {
            return ret.asString()
        }
        return null
    }
    void getToInts(const char *key, int *pInts, int maxCount){
        if self.hasKey(key){
            Json* kid = self.get(key)
            kid.toInts(pInts, maxCount)
        }
    }
    void getToFloats(const char *key, float *pInts, int maxCount){
        if self.hasKey(key){
            Json* kid = self.get(key)
            kid.toFloats(pInts, maxCount)
        }
    }

    void setNumber(double v){
        self.kind = 2
        self.numberValue = v
    }
    void setBool(bool v){
        self.kind = 1
        self.boolValue = v
    }
    void setString(String@ v){
        self.kind = 3
        self.stringValue = v
    }
    void setCstr(const char* v){
        self.kind = 3
        self.stringValue = str(v)
    }
    void initList(){
        if !self.list{
            self.kind = 5
            self.list = new List()
        }
    }
    void initMap(){
        if !self.map{
            self.kind = 4
            self.map = new Map()
        }
    }
    void add(Json@ jo){
        self.initList()
        self.list.add(jo)
    }
    void addNumber(double v){
        Json@ obj = new Json()
        obj.setNumber(v)
        self.add(obj)
    }
    void addBool(bool v){
        Json@ obj = new Json()
        obj.setBool(v)
        self.add(obj)
    }
    void addString(String@ v){
        Json@ obj = new Json()
        obj.setString(v)
        self.add(obj)
    }
    void putNumber(const char *key, double v){
        self.put(key, Json_mkNumber(v))
    }
    void putBool(const char *key, double v){
        self.put(key, Json_mkBool(v))
    }
    void putString(const char *key, String@ v){
        self.put(key, Json_mkString(v))
    }
    void putCstr(const char *key, const char * v){
        self.put(key, Json_mkStringByCstr(v))
    }
    void put(const char *key, Json@ jo){
        self.initMap()
        self.map.put(key, jo)
    }
    void putObject(const char *key, Object* jo){
        self.put(key, Json_toJson(jo))
    }
    //适用于数组和对象
    void mergeToSelf(Json@ jo){
        if jo.isNull(){
            return
        }
        if jo.isArray(){
            int l = jo.arraySize()
            for int i = 0; i < l; i++){
                Json@ item = jo.at(i)
                self.add(item)
            }
            return
        }
        if jo.isObject(){
            List@ keys = jo.keys()
            int l = keys.size()
            for int i = 0; i < l; i++ {
                String@ key = (String@)keys.get(i)
                Json@ item = jo.get(key.str)
                self.put(key.str, item)
            }
            return
        }
    }

    void toObject(Object *obj){
        OrcMetaField *mf = orc_getMetaFieldByObject(obj, "fromJson")
        if mf {
            //调用函数
            void **ptr = (void**)OrcMetaField_getPtr(mf, obj)
            void (*p_fromJson)(Object *_self, Json* jo);
            p_fromJson = *ptr;
            if (p_fromJson){
                p_fromJson(obj, self);
            }
        }
    }
    //反射到对象
    //会调用fromJson(Json*jo)
    Object @ toObjectByVtable(Vtable_Object *vt){
        if self.kind == 5 {
            return self.toObjectsByVtable(vt)
        }

        if self.kind == 4 && self.map != null{
            //对象
            Object@ obj = null;
            vt.make(&obj)

            self.toObject(obj)

            return obj
        }

        return null;
    }
    List@ getObjectsByVtable(const char *key, Vtable_Object *vt){
        Json@ sub = self.get(key)
        List@ list = sub.toObjectsByVtable(vt)
        return list
    }
    List@ toObjectsByVtable(Vtable_Object *vt){
        if self.kind != 5 || self.list == null {
            return null
        }
        List@ list = new List()
        int l = self.size()
        for int i = 0; i < l; i++{
            Json* jo = self.at(i)
            Object@ obj = jo.toObjectByVtable(vt)
            list.add(obj)
        }
        return list
    }
    void toInts(int *pInts, int maxCount){
        if self.kind != 5 || self.list == null {
            return 
        }

        int l = self.size()
        for int i = 0; i < l && i < maxCount; i++{
            int v = self.atAsInt(i);
            pInts[i] = v;
        }
    }
    void toFloats(float *pInts, int maxCount){
        if self.kind != 5 || self.list == null {
            return 
        }

        int l = self.size()
        for int i = 0; i < l && i < maxCount; i++{
            float v = self.atAsNumber(i);
            pInts[i] = v;
        }
    }
}
Json@ Json_mkNull(){
    Json@ obj = new Json()
    obj.setNull()
    return obj
}
Json@ Json_mkNumber(double v){
    Json@ obj = new Json()
    obj.setNumber(v)
    return obj
}
Json@ Json_mkBool(bool v){
    Json@ obj = new Json()
    obj.setBool(v)
    return obj
}
Json@ Json_mkStringByCstr(const char * v){
    Json@ obj = new Json()
    obj.setCstr(v)
    return obj
}
Json@ Json_mkString(String@ v){
    Json@ obj = new Json()
    obj.setString(v)
    return obj
}
Json@ Json_mkArray(){
    Json@ obj = new Json()
    obj.initList()
    return obj
}
Json@ Json_mkObject(){
    Json@ obj = new Json()
    obj.initMap()
    return obj
}
extern Json@ Json_parse(const char *s);


Json@ Json_toJsonNumberArrayByInts(int *ints, int count){
    if !ints{
        return Json_mkNull()
    }
    Json@ ja = Json_mkArray()

    for int i = 0; i < count; i++{
        ja.addNumber(ints[i])
    }

    return ja
}
Json@ Json_toJsonNumberArrayByFloats(float *ints, int count){
    if !ints{
        return Json_mkNull()
    }
    Json@ ja = Json_mkArray()

    for int i = 0; i < count; i++{
        ja.addNumber(ints[i])
    }

    return ja
}
Json@ Json_toJsonByMetaStruct(void *pStruct, MetaStruct* metaStruct){
    if metaStruct == null || pStruct == null {
        return null
    }

    OrcMetaField *mf = metaStruct.headMetaField;
    Json@ jo = Json_mkObject()
    while mf {
        jo.putCstr("__struct", metaStruct.structName)
        if !(mf.isPointer || mf.isRef || mf.isArray){//非指针、引用、数组 

            if mf.type == OrcMetaType_float {
                float* pv = (float*)OrcMetaField_getPtr(mf, pStruct);
                jo.putNumber(mf.name, *pv)
            }
            else if mf.type == OrcMetaType_double {
                double* pv = (double*)OrcMetaField_getPtr(mf, pStruct);
                jo.putNumber(mf.name, *pv)
            }
            else if mf.type == OrcMetaType_int {
                int* pv = (int*)OrcMetaField_getPtr(mf, pStruct);
                jo.putNumber(mf.name, *pv)
            }
            else if mf.type == OrcMetaType_bool {
                bool* pv = (bool*)OrcMetaField_getPtr(mf, pStruct);
                jo.putBool(mf.name, *pv)
            }
            else if mf.type == OrcMetaType_struct {//嵌套结构体，非指针
                if mf.metaStruct {
                    void* pFieldStruct = OrcMetaField_getPtr(mf, pStruct);
                    Json@ nest = Json_toJsonByMetaStruct(pFieldStruct, mf.metaStruct)
                    jo.put(mf.name, nest)
                }
            }
        }

        mf = mf.next
    }
    return jo;
}
Json@ Json_toJson(Object* obj){
    if obj == null {
        return Json_mkNull()
    }
    if obj instanceof String {
        String *sobj = (String*)obj;
        return Json_mkString(sobj)
    }
    if obj instanceof Boolean {
        Boolean *bobj = (Boolean*)obj;
        return Json_mkBool(bobj.value)
    }
    if obj instanceof Number {
        Number *nobj = (Number*)obj;
        return Json_mkNumber(nobj.toDouble())
    }
    if obj instanceof StructObj {//只处理简单的结构体...
        StructObj* so = (StructObj*)obj
        Json@ jo = Json_toJsonByMetaStruct(so.pStruct, so.metaStruct);
        return jo;

    }
    if obj instanceof List {
        return Json_toJsonArray((List*)obj)
    }
    if obj instanceof Map{
        Json@ jo = Json_mkObject()
        Map* m = (Map*)obj;
        List@ keys = m.keys()
        int l = keys.size()
        for int i = 0; i < l; i++{
            String* key = (String*)keys.get(i)
            Object *kidObj = m.get(key)
            Json@ kidJo = Json_toJson(kidObj)
            jo.put(key.str, kidJo)
        }
        return jo
    }

    Json@ jo = Json_mkObject()
    const char* className = Object_getClassName(obj);
    jo.putCstr("__class", className)

    OrcMetaField *mf = orc_getMetaFieldByObject(obj, "toJson")
    if mf {
        //调用函数
        void **ptr = (void**)OrcMetaField_getPtr(mf, obj)
        void (*p_toJson)(Object *_self, Json* jo);
        p_toJson = *ptr;
        if (p_toJson){
            p_toJson(obj, jo);
        }
    }
    return jo
}
Json@ Json_toJsonArray(List* list){
    if !list{
        return Json_mkNull()
    }
    Json@ ja = Json_mkArray()

    int l = list.size()
    for int i = 0; i < l; i++{
        Object* obj = list.get(i)
        Json@ kidJo = Json_toJson(obj)
        ja.add(kidJo)
    }
    return ja
}


Json@ Json_parseByPathCstr(const char *path){
    String@ text = Path_readText(path)
    Json@ ret = Json_parse(text.str)
    return ret
}
void testJson(){
    String@ s = str("{\"id\":1, \"name\":\"zgww\"}")
    Json@ jo = Json_parse(s.str)
    jo.dumpToFileByPathCstr("./testJson.json")
    {
        Json@ tmp = Json_parseByPathCstr("./testJson.json")
        String@ d = tmp.dump()
        printf("from json. d:%s\n", d.str)
        Path_remove("./testJson.json")
    }
}