package SuiDesigner

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Orc/Orc.h"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Number.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/NodeLib.orc"
import * from "../Json/Json.orc"
// import * from "./Serial/BiJson.orc"


// void meta_getSetter(Object *obj, ){
// }

String@ mkSetterName(const char *fieldName){
    return str("set").addc(toupper(fieldName[0])).add(fieldName+1)
}


static void _setPrimitive(OrcMetaField *mf, void *obj, Json* value){
    //结构体
    if mf.metaStruct != null && !mf.isPointer && !mf.isRef && !mf.isArray {
        void *p = OrcMetaField_getPtr(mf, obj)
        _setStructByJsonObject(p, mf.metaStruct, value)
        return
    }

    //只处理基类型
    if (!OrcMetaField_isPrimitive(mf)){
        return;
    }

    int type = OrcMetaField_getType(mf)
    void *p = OrcMetaField_getPtr(mf, obj);

    if (type == OrcMetaType_bool){
        bool *pv = (bool*)p;
        // *pv = value instanceof Boolean ? ((Boolean*)value).value : false;
        *pv = value.asBool()
    }
    else if (type == OrcMetaType_char){
        char *pv = (char*)p;
        // *pv = value instanceof Boolean ? ((Boolean*)value).value : false;
        *pv = (char)value.asInt()
    }
    else if (type == OrcMetaType_short){
        short *pv = (short*)p;
        // *pv = value instanceof Number ? ((Number*)value).toInt() : 0
        *pv = (short)value.asInt()
    }
    else if (type == OrcMetaType_int){
        int *pv = (int*)p;
        // *pv = value instanceof Number ? ((Number*)value).toInt() : 0
        *pv = value.asInt()
    }
    else if (type == OrcMetaType_long){
        long *pv = (long*)p;
        // *pv = value instanceof Number ? ((Number*)value).toLongLong() : 0
        *pv = (long)value.asInt()
    }
    else if (type == OrcMetaType_long_long){
        long long *pv = (long long *)p;
        // *pv = value instanceof Number ? ((Number*)value).toLongLong() : 0
        *pv = (long long)value.asInt()
    }
    else if (type == OrcMetaType_float){
        float *pv = (float *)p;
        // *pv = value instanceof Number ? ((Number*)value).toDouble() : 0
        *pv = (float)value.asNumber()
    }
    else if (type == OrcMetaType_double){
        double *pv = (double *)p;
        // *pv = value instanceof Number ? ((Number*)value).toDouble() : 0
        *pv = value.asNumber()
    }
}
static void _setStructField(void *pStruct, MetaStruct *metaStruct, const char *key, Json@ value){
    OrcMetaField* mf = MetaStruct_getMetaFieldByFieldName(metaStruct, key)
    if (mf != NULL){
        _setPrimitive(mf, pStruct, value)
    }
}
static void _setStructByJsonObject(void *pStruct, MetaStruct *metaStruct, Json@ value){
    if !value.isObject(){
        return
    }
    List@ keys = value.keys()
    for int i = 0; i < keys.size(); i++{
        String* key = (String*)keys.get(i)
        Json@ fieldValue = value.get(key.str)
        _setStructField(pStruct, metaStruct, key.str, fieldValue)
    }
}
//字符串也算进去吧
void meta_setPrimitive(Object *obj, const char *fieldName, Json@ value){
    if (!obj){
        return
    }
    Vtable_Object *vt = orc_getVtableByObject(obj);
    OrcMetaField *mf = orc_getMetaField(vt, fieldName);
    int type = OrcMetaField_getType(mf)
    int addr = OrcMetaField_getAddress(mf)
    { // setter

        String@ setterName = mkSetterName(fieldName)
        OrcMetaField *setterMf = orc_getMetaField(vt, setterName.str);
        //有setter优先使用
        if setterMf{
            int setterType = OrcMetaField_getType(setterMf)

            if setterType == OrcMetaType_method {
                void *pMethod =  *((void**)OrcMetaField_getPtr(setterMf, obj));
                if (OrcMetaField_isStringRef(mf)){
                    void *pMethod2 =  (void*)OrcMetaField_getPtr(setterMf, obj);
                    void (*set)(void *obj, void *val);
                    set = pMethod;
                    set(obj, value.stringValue);
                }
                if (type == OrcMetaType_bool){
                    void (*set)(void *obj, bool val);
                    set  = pMethod;
                    set(obj, value.boolValue);
                }
                else if (type == OrcMetaType_char){
                    void (*set)(void *obj, char val);
                    set = pMethod;
                    set(obj, (char)value.numberValue);
                }
                else if (type == OrcMetaType_short){
                    void (*set)(void *obj, short val);
                    set = pMethod;
                    set(obj, (short)value.numberValue);
                }
                else if (type == OrcMetaType_int){
                    void (*set)(void *obj, int val);
                    set = pMethod;
                    set(obj, (int)value.numberValue);
                }
                else if (type == OrcMetaType_long){
                    void (*set)(void *obj, long val);
                    set = pMethod;
                    set(obj, (long)value.numberValue);
                }
                else if (type == OrcMetaType_long_long){
                    void (*set)(void *obj, long long val);
                    set = pMethod;
                    set(obj, (long long)value.numberValue);
                }
                else if (type == OrcMetaType_float){
                    void (*set)(void *obj, float val);
                    set = pMethod;
                    set(obj, (float)value.numberValue);
                }
                else if (type == OrcMetaType_double){
                    void (*set)(void *obj, double val);
                    set = pMethod;
                    set(obj, value.numberValue);
                }
            }
            else {
                printf("call setter for %s:%s error\n", fieldName, setterName.str)
            }
            return
        }
    }

    if (mf == null){//找不到字段
        return
    }

    //结构体
    if mf.metaStruct != null && !mf.isPointer && !mf.isRef && !mf.isArray {
        void *p = OrcMetaField_getPtr(mf, obj)
        _setStructByJsonObject(p, mf.metaStruct, value)
        return
    }


    //字符串引用
    if (OrcMetaField_isStringRef(mf)){
        urgc_set_field_by_offset(obj, addr, value.stringValue);
        return;
    }

    // void * p = ((char*)obj)+addr
    _setPrimitive(mf, obj, value)
    
}

// A表示abstract
class ANodeAttr {
    String@ name = str("")
    Json@ value = Json_mkNull()

    void updateNodeAttr(Node@ n){
        if n{
            meta_setPrimitive(n, self.name.str, self.value)
            n.trigger_react()
        }
    }
}
class ANode {
    String@ id = null
    String@ getId(){

        if (!self.id){
            self.id = str("")
            self.id.addll((long long)self)
        }
        return self.id
    }

    String@ tag = str("")
    // Json@ attrs = Json_mkObject()
    List@ attrs = new List()
    // List@ exprs = new List()
    List@ children = new List()

    //=======================================>渲染用
    Node@ node = null
    ANode@ parent = null

    ANode@ clone(){
        Json@ jo = self.toJson()
        ANode@ n = new ANode()
        n.fromJson(jo)
        return n
    }

    void setAttr(const char *name, Json@ value){
        ANodeAttr@ a = self.getAttrByName(name)
        if a {
            a.value = value
        }
        else {
            //添加属性
            a = new ANodeAttr()
            a.name.set(name)
            a.value = value
            self.attrs.add(a)
        }
        a.updateNodeAttr(self.node)
    }
    ANodeAttr@ getAttrByName(const char *name){
        for int i = 0; i < self.attrs.size(); i++ {
            ANodeAttr@ a = (ANodeAttr@)self.attrs.get(i)
            if a.name.equals(name){
                return a
            }
        }
        return null
    }
    Json@ getAttrValueByName(const char *name){
        ANodeAttr@ a = self.getAttrByName(name)
        if a {
            return a.value
        }
        return null
    }
    String@ getAttrStringValueByName(const char *name){
        ANodeAttr@ a = self.getAttrByName(name)
        if a && a.value {
            return a.value.asString()
        }
        return str("")
    }

    void updateSubTreeNodes(){
        self.updateNode()
        for (int i = 0; i < self.children.size(); i++){
            ANode* kid = (ANode*)self.children.get(i)
            kid.updateSubTreeNodes()
        }
    }
    void updateNode(){
        if !self.node {
            NodeRegisterInfo@ registerInfo = NodeLib_use().findByClassName(self.tag.str)
            if registerInfo {
                Object@ tmp = registerInfo.mk()
                if tmp instanceof Node {
                    self.node = tmp;
                    self.updateNodeAttr()
                }
                else {
                    printf("WARN; className[%s] not a node", self.tag.str)
                }
            }
        }

        self.updateNode_syncIndex()
    }
    //同步属性到视图节点
    void updateNodeAttr(){
        for (int i = 0; i < self.attrs.size(); i++){
            ANodeAttr@ attr = (ANodeAttr@)self.attrs.get(i)
            attr.updateNodeAttr(self.node)
        }

        if (self.node instanceof ViewBase){
            ViewBase *vb = (ViewBase*)self.node
            vb.invalidReact()
        }
    }
    //同步视图树
    void updateNode_syncIndex(){
        if (self.parent && self.node){
            Node* parentNode = self.parent.node
            if (parentNode){
                int idx = self.parent.indexOf(self)
                if idx != -1 && parentNode.getChild(idx) != self.node){
                    parentNode.insertChild(self.node, idx)
                }
            }
        }
    }

    ANode@ findANodeByNode(Node* node){
        if self.node == node {
            return self
        }
        for (int i = 0; i < self.children.size(); i++){
            ANode* kid = (ANode*)self.children.get(i)
            ANode@ found = kid.findANodeByNode(node)
            if found {
                return found
            }
        }
        return null
    }
    void removeChild(ANode@ child){
        if (child.parent == self){
            if child.node {
                child.node.removeSelf()
            }

            self.children.remove(child)
            child.parent = null
        }
    }
    void removeSelf(){
        if (self.parent){
            self.parent.removeChild(self)
        }
    }
    void appendChild(ANode@ n){
        n.removeSelf()
        self.children.add(n)
        n.parent = self
    }
    int indexOf(ANode* child){
        int idx = self.children.indexOf(child)
        return idx
    }
    void setChildren(List@ children){
        self.children.clear()
        for (int i = 0; i < children.size(); i++){
            ANode* kid = (ANode*)children.get(i)
            self.appendChild(kid)
        }
    }

    void printTree(int tab){
        String@ tmp = str("")
        tmp.fillCount("\t", tab)

        printf("%s%s\n", tmp.str, self.tag.str)

        for (int i = 0; i < self.attrs.size(); i++){
            ANodeAttr@ attr = (ANodeAttr@)self.attrs.get(i)
            String@ valueStr = attr.value.toString()
            // String@ valueStr = str("[?]")
            // if (attr.value instanceof String){
            //     valueStr = attr.value;
            // }
            // if (attr.value instanceof Number){
            //     Number* num = (Number*)attr.value;
            //     valueStr = num.toString()
            // }
            printf("%s\t%s=%s\n", tmp.str, attr.name.str, valueStr.str);
        }
        for (int i = 0; i < self.children.size(); i++){
            ANode* kid = (ANode*)self.children.get(i)
            kid.printTree(tab + 1);
        }
    }


    Json@ toJson(){
        Json@ jo = Json_mkObject()
        jo.putString("tag", self.tag)
        // jo.put("attrs", self.attrs)
        //attr
        Json@ attrsJo = Json_mkObject()
        jo.put("attrs", attrsJo)
        for int i = 0; i < self.attrs.size(); i++{
            ANodeAttr* attr = (ANodeAttr*)self.attrs.get(i)
            attrsJo.put(attr.name.str, attr.value)
        }

        // children
        Json@ kidsJo = Json_mkArray()
        for int i = 0; i < self.children.size(); i++{
            ANode *o = (ANode*)self.children.get(i)
            Json@ kidJo = o.toJson()
            kidsJo.add(kidJo)
        }
        jo.put("children", kidsJo)
        return jo
    }
    void fromJson(Json* jo){
        String@ s = jo.getString("tag")
        self.tag = s
        // self.attrs = jo.get("attrs")
        // if !self.attrs{
        //     self.attrs = Json_mkObject()
        // }
        //加载属性
        {
            self.attrs.clear()
            Json@ attrsJo = jo.get("attrs")
            if attrsJo {
                List@ keys = attrsJo.keys()
                for int i = 0; i < keys.size(); i++{
                    String@ key = (String@)keys.at(i)
                    Json@ value = attrsJo.get(key.str)
                    ANodeAttr@ attr = new ANodeAttr()
                    attr.name = key
                    attr.value = value
                    self.attrs.add(attr)
                }
            }
        }
        //加载children
        {
            Json@ kidsJo = jo.get("children")
            if kidsJo {
                List@ kids = ANode_parseByJsonArray(kidsJo)
                self.setChildren(kids)
            }
            // self.children.clear()
            // if kidsJo{
            //     for int i = 0; i < kidsJo.size(); i++{
            //         Json@ kidJo = kidsJo.at(i)
            //         ANode@ anode = new ANode()
            //         anode.fromJson(kidJo)
            //         self.appendChild(anode)
            //         // self.children.add(anode)
            //     }
            // }
        }

    }
}


List@ ANode_parseByJsonArray(Json@ kidsJo){
    List@ ret = new List()
    for int i = 0; i < kidsJo.size(); i++{
        Json@ kidJo = kidsJo.at(i)
        ANode@ anode = new ANode()
        anode.fromJson(kidJo)
        ret.add(anode)
        // self.children.add(anode)
    }
    return ret
}
