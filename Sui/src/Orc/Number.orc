package Orc

#include "./Orc.h"
// #include <stdlib.h>
#include <string.h>

import * from "./String.orc"

//受urgc管理的列表

class Number {
    String@ toString(){
        return str("")
    }
    long long toLongLong(){
        return 0
    }
    int toInt(){
        return 0
    }
    double toDouble(){
        return 0
    }
    float toFloat(){
        return 0
    }
}
class Integer extends Number {
    int value = 0
    String@ toString(){
        return str("").addi(self.value)
    }
    int toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return (double)self.value
    }
    float toFloat(){
        return (float)self.value
    }
}
class Boolean extends Number {
    bool value = false;
    String@ toString(){
        return str("").add(self.value?"true":"false")
    }
    long long toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return self.value
    }
    float toFloat(){
        return (float)self.value
    }
}
class Float extends Number {
    float value = 0
    String@ toString(){
        return str("").addf(self.value)
    }
    long long toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return self.value
    }
    float toFloat(){
        return (float)self.value
    }
}
class Double extends Number {
    double value = 0;
    String@ toString(){
        return str("").addf(self.value)
    }
    long long toLongLong(){
        return self.value
    }
    int toInt(){
        return self.value
    }
    double toDouble(){
        return self.value
    }
    float toFloat(){
        return (float)self.value
    }
}
class StructObj {
    void *pStruct
    MetaStruct* metaStruct
    void dtor(){
        if self.pStruct {
            free(self.pStruct)
            self.pStruct = null
        }
    }
    void copyTo(void *dst){
        if dst {
            memcpy(dst, self.pStruct, self.metaStruct.size)
        }
    }
}
StructObj@ mkStructObj(MetaStruct* metaStruct, void *pStruct){
    StructObj@ sobj = new StructObj()
    sobj.pStruct = MetaStruct_dupStruct(metaStruct, pStruct)
    sobj.metaStruct = metaStruct
    return sobj
}

Integer@ mkInteger(int v){
    Integer@ o = new Integer();
    o.value = v
    return o
}
Boolean@ mkBoolean(bool v){
    Boolean@ o = new Boolean();
    o.value = v
    return o
}
Double@ mkDouble(double v){
    Double@ o = new Double();
    o.value = v
    return o
}
Float@ mkFloat(float val){
    Float@ v = new Float()
    v.value = val
    return v
}


void Orc_setField(Object *obj, OrcMetaField*mf, Object* value){
    void *p = OrcMetaField_getPtr(mf, obj)
    int type = OrcMetaField_getType(mf)

    if value instanceof Number {
        Number* num = (Number*) value

        if type == OrcMetaType_float {
            *((float*)p) = num.toFloat()
        }
        else if type == OrcMetaType_double {
            *((double*)p) = num.toDouble()
        }
        else if type == OrcMetaType_long_long {
            *((long long*)p) = (long long)num.toLongLong()
        }
        else if type == OrcMetaType_long {
            *((long*)p) = (long)num.toLongLong()
        }
        else if type == OrcMetaType_int {
            *((int*)p) = num.toInt()
        }
        else if type == OrcMetaType_char {
            *((char*)p) = num.toInt()
        }
        else if type == OrcMetaType_bool {
            *((bool*)p) = num.toInt()
        }
    }
    else if type == OrcMetaType_class{
        if mf.isRef {
            //引用
            urgc_set_field_class(obj, (void**)p, value);
        }
        else if mf.isPointer {
            //普通的指针
            *((void**)p) = value
        }
    }
        //普通的结构体
    else if !mf.isPointer && !mf.isRef && value instanceof StructObj{
        StructObj* sobj = (StructObj*)value
        sobj.copyTo(p)
    }
}