package SuiDesigner

#include "../../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
#include "../../Json/cJSON.h"

import * from "../../Orc/Path.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Map.orc"

import * from "../../Json/Json.orc"


// 需要提前注册类
// 对于嵌套的对象，
// 如果对象本身就有实例，就判断是不是同名的类，如果是，直接使用
// 需要有__class属性来指明是哪个类
// 通过__class来还原
// 对于struct，只支持 直接使用struct,不支持指针。 这是struct的主要应用场景


//从虚表和json string 反序列化一个对象出来
extern Object@ BiJson_fromJsonStringAndVtable(const char *text, Vtable_Object *vt);
//返回值需要删除
extern cJSON* BiJson_toJsonObject_needToDelete(Object *obj)
extern String@ BiJson_toJsonString(Object *obj)


//类型注册
extern void BiJson_registerClass(Vtable_Object *vt);
//按全称查找类型
extern Vtable_Object* BiJson_findClass(const char *className);


struct Inner {
    int xx 
    int yy 
}

class BiJsonExporter {
    // OrcMetaField *metaField;
    Object* obj;
    cJSON* jo;//借用

    extern void exportFieldByOrcMetaField(OrcMetaField*mf)
    extern void exportField(const char *fieldStr)
    // void dtor(){
        // if (self.jo){
            // cJSON_Delete(self.jo);
        // }
    // }

    void exportFields(const char *fieldsStr){
        String@ tmpstr = str(fieldsStr)
        List@ fields = tmpstr.splitByRe(",\\s*")
        for (int i = 0; i < fields.size(); i++){
            String@ field = (String@)fields.get(i);
            self.exportField(field.str)
        }
    }
}

// BiJsonExporter@ mkBiJsonExporter(Object *obj){
//     BiJsonExporter@ ret = new BiJsonExporter()
//     ret.obj = obj;
//     return ret
// }

class User {
    float go = 1.2
    double nice = 234.2

    //声明需要需要导出的字段
    //通过反射调用的
    void exportFields(BiJsonExporter *exp){
        // return super.fieldsToExport().add(",xx,yy")
        exp.exportFields("go,yy")
    }
    void say(){
        printf(" iam user\n");
    }
}
class User2 extends User{
    void say(){
        printf(" iam user2\n");
    }
}

class TestBi{
    bool a = false;
    char b = 0;
    short c = 0;
    int d = 0;
    long e = 0;
    long long f = 0;
    float g = 0;
    double h = 0;

    Inner inner;
    User@ u = new User()
}

void testBiJson(){
    BiJson_registerClass(User2);
    BiJson_registerClass(User);
    {
        printf("testBiJson 104\n");
        TestBi@ t = new TestBi()
        printf("testBiJson 106\n");
        String@ s = BiJson_toJsonString(t)
        printf("testBiJson 108\n");

        Path_writeText("a.json", s.str)
        printf("testBiJson 110\n");
    }

    printf("testBiJson 111\n");
    String@ text = Path_readText("a.json");
    printf("read Text:%s\n", text.str);
    TestBi@ bi = (TestBi@)BiJson_fromJsonStringAndVtable(text.str, TestBi)
    printf("bi: a %d b %d  c %d d:%d, e:%ld, f:%lld, g:%f, h:%f. inner:%d,%d, u:%f,%f\n" ,
        bi.a,
        bi.b,
        bi.c,
        bi.d,
        bi.e,
        bi.f,
        bi.g,
        bi.h,
        bi.inner.xx,
        bi.inner.yy,

        bi.u.go,
        bi.u.nice,
    );
    bi.u.say()

    String@ s = BiJson_toJsonString(bi)
    printf("s:%s\n", s.str)

    if 0{

    {
        Json@ jo = Json_parse("1")
        printf("jo kind:%d. %f\n", jo.kind, jo.numberValue)
    }
    {
        Json@ jo = Json_parse("true")
        printf("jo kind:%d, %d\n", jo.kind, jo.boolValue)
    }
    {
        Json@ jo = Json_parse("false")
        printf("jo kind:%d, %d\n", jo.kind, jo.boolValue)
    }
    {
        Json@ jo = Json_parse("null")
        printf("jo kind:%d\n", jo.kind)
    }
    {
        Json@ jo = Json_parse("\"hiskjdfsdfsd\"")
        printf("jo kind:%d, %s\n", jo.kind, jo.stringValue.str)
    }
    {
        Json@ jo = Json_parse("\"hiskjdfsdfs\\\"d\"")
        printf("jo kind:%d, %s\n", jo.kind, jo.stringValue.str)
    }
    {
        Json@ jo = Json_parse("[]")
        printf("jo kind:%d, %p. l:%d\n", jo.kind, jo.list, jo.arraySize())
    }
    }
    {
        Json@ jo = Json_parse("[1, 2, 3]")
        printf("jo kind:%d, %p. l:%d items:%f,%f,%f; %d,%d,%d\n", jo.kind, jo.list, jo.arraySize()
        , jo.atAsNumber(0)
        , jo.atAsNumber(1)
        , jo.atAsNumber(2)
        , jo.atAsInt(0)
        , jo.atAsInt(1)
        , jo.atAsInt(2)
        )
        printf("\tdump:%s\n", jo.dump().str);
    }
    {
        Json@ jo = Json_parse("{\"id\":102, \"name\":34, \"pwd\":4}")
        printf("jo kind:%d, %p. l:%d items:%f,%f,%f; %d,%d,%d\n", 
        jo.kind
        , jo.map
        , jo.keySize()
        , jo.getNumber("id")
        , jo.getNumber("name")
        , jo.getNumber("pwd")
        , jo.getInt("id")
        , jo.getInt("name")
        , jo.getInt("pwd")
        )
        printf("\tdump:%s\n", jo.dump().str);
    }
}
