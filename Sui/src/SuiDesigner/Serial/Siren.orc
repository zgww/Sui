package SuiDesigner

#include "../../Orc/Orc.h"
#include <stdio.h>
#include <string.h>

import * from "../../Orc/Path.orc"
import * from "../../Orc/String.orc"
import * from "../../Orc/List.orc"
import * from "../../Orc/Map.orc"
import * from "../../Json/Json.orc"
import * from "./BiJson.orc"

// Core imports
import * from "../../Sui/Core/Node.orc"

// 3D Scene serialization imports
import * from "../../Sgl/Scene.orc"
import * from "../../Sgl/Obj3d.orc"
import * from "../../Sgl/Mesh.orc"
import * from "../../Sgl/Camera.orc"
import * from "../../Sgl/PerspectiveCamera.orc"
import * from "../../Sgl/Light.orc"
import * from "../../Sgl/PointLight.orc"
import * from "../../Sgl/DirLight.orc"
import * from "../../Sgl/SpotLight.orc"
import * from "../../Sui/Core/Vec3.orc"
import * from "../../Sui/Core/Vec4.orc"
import * from "../../Sui/Core/Color.orc"
import * from "../../Sui/Core/Quaternion.orc"
import * from "../../Sui/Core/Rect.orc"

// 基于反射的通用序列化器
class ReflectionSerializer {

    // 序列化任意值到JSON（支持number, bool, null, string, list, object）
    Json@ serializeObject(Object@ obj) {
        if (!obj) {
            return Json_mkNull()
        }

        // 特殊处理String类型
        if (obj instanceof String) {
            String* str = (String*)obj
            return Json_mkStringByCstr(str.str)
        }

        // 特殊处理List类型
        if (obj instanceof List) {
            Json@ listJson = Json_mkArray()
            List* list = (List*)obj
            int size = list.size()
            for (int i = 0; i < size; i++) {
                Object@ item = list.get(i)
                Json@ itemJson = self.serializeObject(item)
                listJson.add(itemJson)
            }
            return listJson
        }

        // 特殊处理Map类型
        if (obj instanceof Map) {
            Json@ mapJson = Json_mkObject()
            Map* map = (Map*)obj
            List@ keys = map.keys()
            int size = keys.size()
            for (int i = 0; i < size; i++) {
                String* key = (String*)keys.get(i)
                Object@ value = map.get(key.str)
                Json@ valueJson = self.serializeObject(value)
                mapJson.put(key.str, valueJson)
            }
            return mapJson
        }

        // 处理普通对象类型
        Json@ json = Json_mkObject()

        // 添加类型信息
        const char* className = Object_getClassName(obj)
        json.putCstr("__class", className)

        // 获取对象的虚表和反射信息
        Vtable_Object* vt = orc_getVtableByObject(obj)
        OrcMetaField* mf = orc_getOrInitMeta(vt)

        // 序列化所有字段
        self.serializeFields(json, obj, mf)

        // 序列化父类字段
        Vtable_Object* superVt = Vtable_getSuper(vt)
        while (superVt) {
            OrcMetaField* superMf = orc_getOrInitMeta(superVt)
            self.serializeFields(json, obj, superMf)
            superVt = Vtable_getSuper(superVt)
        }

        return json
    }

    // 序列化基础类型值（支持number, bool, null）
    Json@ serializePrimitiveValue(void* ptr, OrcMetaType type) {
        if (!ptr) {
            return Json_mkNull()
        }

        if (type == OrcMetaType_bool) {
            bool* pv = (bool*)ptr
            return Json_mkBool(*pv)
        } else if (type == OrcMetaType_char) {
            char* pv = (char*)ptr
            return Json_mkNumber((double)*pv)
        } else if (type == OrcMetaType_short) {
            short* pv = (short*)ptr
            return Json_mkNumber((double)*pv)
        } else if (type == OrcMetaType_int) {
            int* pv = (int*)ptr
            return Json_mkNumber((double)*pv)
        } else if (type == OrcMetaType_long) {
            long* pv = (long*)ptr
            return Json_mkNumber((double)*pv)
        } else if (type == OrcMetaType_long_long) {
            long long* pv = (long long*)ptr
            return Json_mkNumber((double)*pv)
        } else if (type == OrcMetaType_float) {
            float* pv = (float*)ptr
            return Json_mkNumber((double)*pv)
        } else if (type == OrcMetaType_double) {
            double* pv = (double*)ptr
            return Json_mkNumber(*pv)
        }

        return Json_mkNull()
    }

    // 判断字段是否应该被序列化
    bool shouldSerializeField(Object@ obj, const char* fieldName) {
        if (!obj || !fieldName) {
            return false
        }

        // 默认过滤下划线开头的私有字段
        if (fieldName[0] == '_') {
            return false
        }

        // 通过反射检查对象是否有shouldSerializeField方法
        Vtable_Object* vt = orc_getVtableByObject(obj)
        if (vt) {
            // 查找shouldSerializeField方法
            // OrcMetaField* method = orc_findMethodByName(vt, "shouldSerializeField")
            // if (method) {
            //     // 调用对象的shouldSerializeField方法
            //     typedef bool (*ShouldSerializeFunc)(Object*, const char*)
            //     ShouldSerializeFunc func = (ShouldSerializeFunc)OrcMetaField_getMethodPtr(method)
            //     if (func) {
            //         return func(obj, fieldName)
            //     }
            // }
        }

        // 默认序列化所有字段
        return true
    }

    // 序列化对象字段
    void serializeFields(Json@ json, Object@ obj, OrcMetaField* mf) {
        if (!json || !obj || !mf) {
            return
        }

        OrcMetaField* cur = mf
        while (cur) {
            const char* fieldName = OrcMetaField_getName(cur)
            if (self.shouldSerializeField(obj, fieldName)) {
                self.serializeField(json, obj, cur, fieldName)
            }
            cur = OrcMetaField_getNext(cur)
        }
    }

    // 序列化单个字段
    void serializeField(Json@ json, Object@ obj, OrcMetaField* mf, const char* fieldName) {
        if (!json || !obj || !mf || !fieldName) {
            return
        }

        OrcMetaType type = (OrcMetaType)OrcMetaField_getType(mf)
        void* fieldPtr = OrcMetaField_getPtr(mf, obj)

        if (OrcMetaField_isPrimitive(mf)) {
            self.serializePrimitiveField(json, fieldPtr, mf, fieldName, type)
        } else if (type == OrcMetaType_class) {
            // 检查是否是List类型
            if (mf.classVtable && strcmp(mf.classVtable.className, "List") == 0) {
                self.serializeListField(json, fieldPtr, mf, fieldName)
            } else {
                self.serializeClassField(json, fieldPtr, mf, fieldName)
            }
        } else if (type == OrcMetaType_struct) {
            self.serializeStructField(json, fieldPtr, mf, fieldName)
        }
    }

    // 序列化基础类型字段
    void serializePrimitiveField(Json@ json, void* fieldPtr, OrcMetaField* mf, const char* fieldName, OrcMetaType type) {
        if (!json || !fieldPtr || !fieldName) {
            return
        }

        Json@ value = self.serializePrimitiveValue(fieldPtr, type)
        json.put(fieldName, value)
    }

    // 序列化List字段
    void serializeListField(Json@ json, void* fieldPtr, OrcMetaField* mf, const char* fieldName) {
        if (!json || !fieldPtr || !fieldName) {
            return
        }

        if (mf.isRef || mf.isPointer) {
            List** listPtr = (List**)fieldPtr
            List* list = *listPtr
            if (list) {
                Json@ listJson = Json_mkArray()
                int size = list.size()
                for (int i = 0; i < size; i++) {
                    Object@ item = list.get(i)
                    if (item) {
                        Json@ itemJson = self.serializeObject(item)
                        listJson.add(itemJson)
                    } else {
                        listJson.add(Json_mkNull())
                    }
                }
                json.put(fieldName, listJson)
            } else {
                json.put(fieldName, Json_mkNull())
            }
        }
    }

    // 序列化类字段
    void serializeClassField(Json@ json, void* fieldPtr, OrcMetaField* mf, const char* fieldName) {
        if (!json || !fieldPtr || !fieldName) {
            return
        }

        if (mf.isRef || mf.isPointer) {
            Object** objPtr = (Object**)fieldPtr
            Object@ childObj = *objPtr
            if (childObj) {
                Json@ childJson = self.serializeObject(childObj)
                json.put(fieldName, childJson)
            } else {
                json.put(fieldName, Json_mkNull())
            }
        }
    }

    // 序列化结构体字段
    void serializeStructField(Json@ json, void* fieldPtr, OrcMetaField* mf, const char* fieldName) {
        if (!json || !fieldPtr || !fieldName || !mf.metaStruct) {
            return
        }

        Json@ structJson = Json_mkObject()

        // 获取结构体的字段信息
        OrcMetaField* structMf = mf.metaStruct.headMetaField

        while (structMf) {
            const char* structFieldName = OrcMetaField_getName(structMf)
            if (structFieldName) {
                void* structFieldPtr = (void*)((char*)fieldPtr + OrcMetaField_getAddress(structMf))
                OrcMetaType structFieldType = (OrcMetaType)OrcMetaField_getType(structMf)

                if (OrcMetaField_isPrimitive(structMf)) {
                    self.serializePrimitiveField(structJson, structFieldPtr, structMf, structFieldName, structFieldType)
                } else if (structFieldType == OrcMetaType_struct) {
                    // 递归处理嵌套的结构体
                    self.serializeStructField(structJson, structFieldPtr, structMf, structFieldName)
                } else if (structFieldType == OrcMetaType_class) {
                    // 处理结构体中的类引用
                    self.serializeClassField(structJson, structFieldPtr, structMf, structFieldName)
                }
            }
            structMf = OrcMetaField_getNext(structMf)
        }

        json.put(fieldName, structJson)
    }

    // 序列化场景（包含子节点）
    Json@ serializeSceneWithChildren(Scene@ scene) {
        if (!scene) {
            return Json_mkNull()
        }

        Json@ sceneJson = self.serializeObject((Object@)scene)

        // 序列化子节点
        if (scene.firstChild) {
            Json@ childrenJson = Json_mkArray()
            self.serializeNodeChildren(childrenJson, (Node@)scene)
            sceneJson.put("children", childrenJson)
        }

        return sceneJson
    }

    // 递归序列化子节点
    void serializeNodeChildren(Json@ childrenArray, Node@ parent) {
        if (!parent || !childrenArray) {
            return
        }

        Node@ child = parent.firstChild
        while (child) {
            Json@ childJson = null

            if (child instanceof Scene) {
                childJson = self.serializeSceneWithChildren((Scene@)child)
            } else {
                childJson = self.serializeObject((Object@)child)

                // 如果有子节点，继续序列化
                if (child.firstChild) {
                    Json@ grandChildrenJson = Json_mkArray()
                    self.serializeNodeChildren(grandChildrenJson, child)
                    childJson.put("children", grandChildrenJson)
                }
            }

            if (childJson) {
                childrenArray.add(childJson)
            }

            child = child.next
        }
    }

    // 保存场景到文件
    bool saveSceneToFile(Scene@ scene, const char* filepath) {
        Json@ jsonObj = self.serializeSceneWithChildren(scene)
        if (!jsonObj) {
            return false
        }

        jsonObj.dumpToFileByPathCstr(filepath)
        return true
    }

    // 获取场景的JSON字符串
    String@ serializeSceneToString(Scene@ scene) {
        Json@ jsonObj = self.serializeSceneWithChildren(scene)
        if (!jsonObj) {
            return str("{}")
        }
        return jsonObj.dump()
    }
}

// 基于反射的通用反序列化器
class ReflectionDeserializer {

    // 从JSON反序列化对象
    Object@ deserializeObject(Json@ json) {
        if (!json) {
            return null
        }

        // 特殊处理数组类型（对应List）
        if (json.isArray()) {
            List@ list = new List()
            int arraySize = json.arraySize()
            for (int i = 0; i < arraySize; i++) {
                Json@ itemJson = json.at(i)
                if (itemJson && !itemJson.isNull()) {
                    Object@ item = self.deserializeObject(itemJson)
                    if (item) {
                        list.add(item)
                    }
                }
            }
            return (Object@)list
        }

        if (!json.isObject()) {
            return null
        }

        // 获取类型信息
        String@ className = json.getString("__class")
        if (!className) {
            return null
        }

        // 查找类型
        Vtable_Object* vt = BiJson_findClass(className.str)
        if (!vt) {
            return null
        }

        // 创建对象实例
        Object@ obj = null
        vt.make(&obj)
        if (!obj) {
            return null
        }

        // 反序列化字段
        self.deserializeFields(json, obj, vt)

        return obj
    }

    // 反序列化对象字段
    void deserializeFields(Json@ json, Object@ obj, Vtable_Object* vt) {
        if (!json || !obj || !vt) {
            return
        }

        // 反序列化当前类的字段
        OrcMetaField* mf = orc_getOrInitMeta(vt)
        self.deserializeFieldsByMetaField(json, obj, mf)

        // 反序列化父类字段
        Vtable_Object* superVt = Vtable_getSuper(vt)
        while (superVt) {
            OrcMetaField* superMf = orc_getOrInitMeta(superVt)
            self.deserializeFieldsByMetaField(json, obj, superMf)
            superVt = Vtable_getSuper(superVt)
        }
    }

    // 根据元字段反序列化
    void deserializeFieldsByMetaField(Json@ json, Object@ obj, OrcMetaField* mf) {
        if (!json || !obj || !mf) {
            return
        }

        OrcMetaField* cur = mf
        while (cur) {
            const char* fieldName = OrcMetaField_getName(cur)
            if (fieldName && strcmp(fieldName, "ctor") != 0 && strcmp(fieldName, "dtor") != 0) {
                if (json.hasKey(fieldName)) {
                    Json@ fieldJson = json.get(fieldName)
                    if (fieldJson) {
                        self.deserializeField(obj, cur, fieldName, fieldJson)
                    }
                }
            }
            cur = OrcMetaField_getNext(cur)
        }
    }

    // 反序列化单个字段
    void deserializeField(Object@ obj, OrcMetaField* mf, const char* fieldName, Json@ fieldJson) {
        if (!obj || !mf || !fieldName || !fieldJson) {
            return
        }

        OrcMetaType type = (OrcMetaType)OrcMetaField_getType(mf)
        void* fieldPtr = OrcMetaField_getPtr(mf, obj)

        if (OrcMetaField_isPrimitive(mf)) {
            self.deserializePrimitiveField(fieldPtr, mf, type, fieldJson)
        } else if (type == OrcMetaType_class) {
            // 检查是否是List类型
            if (mf.classVtable && strcmp(mf.classVtable.className, "List") == 0) {
                // self.deserializeListField(fieldPtr, mf, fieldJson)
            } else {
                // self.deserializeClassField(fieldPtr, mf, fieldJson)
            }
        } else if (type == OrcMetaType_struct) {
            self.deserializeStructField(fieldPtr, mf, fieldJson)
        }
    }

    // 反序列化基础类型字段
    void deserializePrimitiveField(void* fieldPtr, OrcMetaField* mf, OrcMetaType type, Json@ fieldJson) {
        if (!fieldPtr || !fieldJson) {
            return
        }

        if (type == OrcMetaType_bool) {
            bool* pv = (bool*)fieldPtr
            *pv = fieldJson.asBool()
        } else if (type == OrcMetaType_char) {
            char* pv = (char*)fieldPtr
            *pv = (char)fieldJson.asInt()
        } else if (type == OrcMetaType_short) {
            short* pv = (short*)fieldPtr
            *pv = (short)fieldJson.asInt()
        } else if (type == OrcMetaType_int) {
            int* pv = (int*)fieldPtr
            *pv = fieldJson.asInt()
        } else if (type == OrcMetaType_long) {
            long* pv = (long*)fieldPtr
            *pv = (long)fieldJson.asNumber()
        } else if (type == OrcMetaType_long_long) {
            long long* pv = (long long*)fieldPtr
            *pv = (long long)fieldJson.asNumber()
        } else if (type == OrcMetaType_float) {
            float* pv = (float*)fieldPtr
            *pv = (float)fieldJson.asNumber()
        } else if (type == OrcMetaType_double) {
            double* pv = (double*)fieldPtr
            *pv = fieldJson.asNumber()
        }
    }

    // 反序列化类字段
    void deserializeClassField(void* fieldPtr, OrcMetaField* mf, Json@ fieldJson) {
        if (!fieldPtr || !mf || !fieldJson) {
            return
        }

        if (mf.isRef || mf.isPointer) {
            if (fieldJson.isNull()) {
                return
            }

            Object** objPtr = (Object**)fieldPtr
            Object@ childObj = self.deserializeObject(fieldJson)
            if (childObj) {
                *objPtr = childObj
            }
        }
    }

    // 反序列化结构体字段
    void deserializeStructField(void* fieldPtr, OrcMetaField* mf, Json@ fieldJson) {
        if (!fieldPtr || !mf || !fieldJson || !fieldJson.isObject() || !mf.metaStruct) {
            return
        }

        // 遍历结构体字段
        OrcMetaField* structMf = mf.metaStruct.headMetaField

        while (structMf) {
            const char* structFieldName = OrcMetaField_getName(structMf)
            if (structFieldName && fieldJson.hasKey(structFieldName)) {
                Json@ structFieldJson = fieldJson.get(structFieldName)
                if (structFieldJson) {
                    void* structFieldPtr = (void*)((char*)fieldPtr + OrcMetaField_getAddress(structMf))
                    OrcMetaType structFieldType = (OrcMetaType)OrcMetaField_getType(structMf)

                    if (OrcMetaField_isPrimitive(structMf)) {
                        self.deserializePrimitiveField(structFieldPtr, structMf, structFieldType, structFieldJson)
                    }
                }
            }
            structMf = OrcMetaField_getNext(structMf)
        }
    }

    // 反序列化场景（包含子节点）
    Scene@ deserializeSceneWithChildren(Json@ json) {
        if (!json) {
            return null
        }

        Object@ obj = self.deserializeObject(json)
        if (!obj || !(obj instanceof Scene)) {
            return null
        }

        Scene* scene = (Scene*)obj

        // 反序列化子节点
        Json@ childrenJson = json.get("children")
        if (childrenJson && childrenJson.isArray()) {
            self.deserializeNodeChildren((Node@)scene, childrenJson)
        }

        return scene
    }

    // 递归反序列化子节点
    void deserializeNodeChildren(Node@ parent, Json@ childrenArray) {
        if (!parent || !childrenArray || !childrenArray.isArray()) {
            return
        }

        int arraySize = childrenArray.arraySize()
        for (int i = 0; i < arraySize; i++) {
            Json@ childJson = childrenArray.at(i)
            if (childJson) {
                Object@ childObj = self.deserializeObject(childJson)
                if (childObj && childObj instanceof Node) {
                    Node* childNode = (Node*)childObj
                    parent.appendChild(childNode)

                    // 如果有子节点，继续反序列化
                    Json@ grandChildrenJson = childJson.get("children")
                    if (grandChildrenJson && grandChildrenJson.isArray()) {
                        self.deserializeNodeChildren(childNode, grandChildrenJson)
                    }
                }
            }
        }
    }

    // 从文件加载场景
    Scene@ loadSceneFromFile(const char* filepath) {
        Json@ json = Json_parseByPathCstr(filepath)
        if (!json) {
            return null
        }

        return self.deserializeSceneWithChildren(json)
    }

    // 从字符串反序列化场景
    Scene@ deserializeScene(const char* jsonString) {
        if (!jsonString) {
            return null
        }

        Json@ json = Json_parse(jsonString)
        if (!json) {
            return null
        }

        return self.deserializeSceneWithChildren(json)
    }
}

// 全局序列化器和反序列化器实例
ReflectionSerializer reflectionSerializer;
ReflectionDeserializer reflectionDeserializer;

// 注册3D相关的类型
void registerSglClasses() {
    BiJson_registerClass(Scene)
    BiJson_registerClass(Obj3d)
    BiJson_registerClass(Mesh)
    BiJson_registerClass(Camera)
    BiJson_registerClass(PerspectiveCamera)
    BiJson_registerClass(Light)
    BiJson_registerClass(PointLight)
    BiJson_registerClass(DirLight)
    BiJson_registerClass(SpotLight)
}

// 便捷函数
String@ serializeSceneToString(Scene@ scene) {
    return reflectionSerializer.serializeSceneToString(scene)
}

bool saveSceneToFile(Scene@ scene, const char* filepath) {
    return reflectionSerializer.saveSceneToFile(scene, filepath)
}

Scene@ loadSceneFromFile(const char* filepath) {
    return reflectionDeserializer.loadSceneFromFile(filepath)
}

Scene@ deserializeSceneFromString(const char* jsonString) {
    return reflectionDeserializer.deserializeScene(jsonString)
}