#include "./BiJson_orc.h"
#include "../../Json/cJSON.h"
#include "Orc/Orc.h"
#include "Orc/String_orc.h"
#include "Json/cJSON.h"
#include <unordered_map>
#include <string>
#include <stdatomic.h>

_Atomic int refC;


static void setPrimitiveValue(cJSON* jo, void *obj, OrcMetaField *mf){
    if (mf->type == OrcMetaType_bool){
        bool *pv = (bool*)(((char *)obj) + mf->address);
        *pv = cJSON_IsTrue(jo);
    }
    else if (mf->type == OrcMetaType_char){
        char *pv = (char*)(((char *)obj) + mf->address);
        *pv = (char)cJSON_GetNumberValue(jo);
    }
    else if (mf->type == OrcMetaType_short){
        short *pv = (short*)(((char *)obj) + mf->address);
        *pv = (short)cJSON_GetNumberValue(jo);
    }
    else if (mf->type == OrcMetaType_int){
        int *pv = (int*)(((char *)obj) + mf->address);
        *pv = (int)cJSON_GetNumberValue(jo);
    }
    else if (mf->type == OrcMetaType_long){
        long *pv = (long*) (((char *)obj) + mf->address);
        *pv = (long)cJSON_GetNumberValue(jo);
    }
    else if (mf->type == OrcMetaType_long_long){
        long long *pv = (long long *)(((char *)obj) + mf->address);
        *pv = (long long)cJSON_GetNumberValue(jo);
    }
    else if (mf->type == OrcMetaType_float){
        float *pv = (float *)(((char *)obj) + mf->address);
        *pv = (float)cJSON_GetNumberValue(jo);
    }
    else if (mf->type == OrcMetaType_double){
        double *pv = (double *) (((char *)obj) + mf->address);
        *pv = (double)cJSON_GetNumberValue(jo);
    }
}
static Object *getObject_byMetaField(Object *host, OrcMetaField *mf){
    Object **v = (Object**) (((char*)host) + mf->address);
    return *v;
}
//填充结构体值。 支持普通的嵌套结构体，不支持结构体指针字段
static void setStructValue(cJSON*jo, void *pStruct, OrcMetaField*mf){
    if (!cJSON_IsObject(jo)){
        return;
    }

    //遍历子节点
    cJSON *child = jo->child;
    OrcMetaField *headMetaField = mf->metaStruct->headMetaField;

    while (child){
        const char *key = child->string;
        OrcMetaField *mf = orc_getMetaField_byHeadMetaField(headMetaField, key);

        if (mf){//有字段
            setPrimitiveValue(child, pStruct, mf);

            //嵌套结构体
            if (mf->type == OrcMetaType_struct){
                //只支持普通的struct
                if (!(mf->isPointer || mf->isArray || mf->isRef)){
                    setStructValue(child, ((char*)pStruct) + mf->address, mf);
                }
            }
        }
        child = child->next;
    }
}

static std::unordered_map<std::string, Vtable_Object*> classLib;
void SuiDesigner$BiJson_registerClass(Vtable_Object * vt){
    classLib[vt->className] = vt;
}
Vtable_Object * SuiDesigner$BiJson_findClass(char const * className){
    auto it = classLib.find(className);
    if (it == classLib.end()){//不存在
        return NULL;
    }
    return it->second;
}

static void fromJSONObject(cJSON* jo, Object *obj){
    if (cJSON_IsNull(jo)){
        return;
    }
    Vtable_Object * vt = obj->vtable;
    // OrcMetaField* mf = orc_getOrInitMeta(vt);
    // orc_getMetaField(vt, "name");

    //遍历子节点
    cJSON *child = jo->child;
    while (child){
        const char *key = child->string;
        OrcMetaField *mf = orc_getMetaField(vt, key);

        if (mf){//有字段
            setPrimitiveValue(child, obj, mf);
            if (mf->type == OrcMetaType_class){
                //暂只支持Class@
                if (mf->isRef){
                    if (cJSON_IsNull(child)){//赋空即可
                        urgc_set_field_by_offset(obj, mf->address, NULL);
                    }
                    //字符串类型
                    else if (mf->classVtable == (void*)Vtable_Orc$String_init(NULL)){
                        if (cJSON_IsString(child)){
                            const char *strVal = cJSON_GetStringValue(child);

                            URGC_VAR_CLEANUP_CLASS Orc$String * str = NULL;
                            Orc$str(&str, strVal);

                            urgc_set_field_by_offset(obj, mf->address, str);
                        }
                        else {
                            printf("ignore string type for field:%s. child is not string\n", key);
                        }
                    }
                    else {
                        //如果json里有指定了类型，需要判断类型符不符合
                        cJSON *__class = cJSON_GetObjectItem(child, "__class");
                        Vtable_Object *targetVtable = mf->classVtable;
                        Object* v = getObject_byMetaField(obj, mf);
                        bool needCreateNewInstance = v == NULL;
                        
                        if (__class){
                            char *__className = cJSON_GetStringValue(__class);
                            if (strcmp(__className, targetVtable->className) == 0){//正好与字段的类型一样
                            } else {//不一样，就需要切换
                                //从注册的类型库中查找vtable
                                Vtable_Object* findVtable = SuiDesigner$BiJson_findClass(__className);
                                if (findVtable) {
                                    targetVtable = findVtable;
                                    needCreateNewInstance = true;
                                }
                                else {
                                    //失败
                                    printf("解析__className:%s失败，未找到目标类型\n", __className);
                                }
                            }
                        }

                        if (needCreateNewInstance){//原字段是空，实例化一下
                            Object *tmp = targetVtable->make(&tmp);
                            v = tmp;
                            // Object *po = ((char *)obj) + mf->address;
                            //赋值
                            urgc_set_field_by_offset(obj, mf->address, v);
                        }
                        //属性设置
                        fromJSONObject(child, v);
                        // Object *po = ((char *)obj) + mf->address;
                        // urgc_set_field_by_offset(obj, mf->address, nv);
                    }
                }
            }
            if (mf->type == OrcMetaType_struct){
                //只支持普通的struct
                if (!(mf->isPointer || mf->isArray || mf->isRef)){
                    setStructValue(child, ((char*)obj) + mf->address, mf);
                }
            }
        }

        child = child->next;
    }
}
Object* SuiDesigner$BiJson_fromJsonStringAndVtable(Object * * __outRef__, char const * text, Vtable_Object * vt)
// Object * SuiDesigner$BiJson_fromJsonStringAndVtable(char const * text, Vtable_Object * vt)
{
    Object *ret = NULL;
    cJSON* jo = cJSON_Parse(text);

    if (cJSON_IsNull(jo)){
        goto end;
    }
    if (!cJSON_IsObject(jo)){//得是对象
        goto end;
    }

    ret = vt->make(&ret);

    fromJSONObject(jo, ret);

end:
    cJSON_Delete(jo);

    // return ret;
	return (Object*)urgc_set_var_for_return((void**)__outRef__, ret);
}


cJSON* SuiDesigner$BiJson_toJsonObject_needToDelete(Object * obj)
{
    if (obj == NULL){
        return cJSON_CreateNull();
    }
    // URGC_NEW_VAR(Orc$String *, ret, Orc$String_new());
    // URGC_NEW_VAR(SuiDesigner$BiJsonExporter*, exp, SuiDesigner$BiJsonExporter_new(&exp));
    NEW_CLASS_VAR(SuiDesigner$BiJsonExporter, exp);


    cJSON *jo = cJSON_CreateObject();
    auto className  = Object_getClassName(obj);
    //添加类名
    cJSON_AddStringToObject(jo, "__class", className);

    exp->jo = jo;//!所有权
    exp->obj = obj;

    //如果对象有自定义的exportFields函数,就直接调用，没有就走统一的导出
    OrcMetaField *mf = orc_getMetaField(obj->vtable, "exportFields");
    if (mf){
        void (**fn)(Object*, SuiDesigner$BiJsonExporter*) = (void (**)(Object*, SuiDesigner$BiJsonExporter*))(((char*)obj)+mf->address);
        (*fn)(obj, exp);
    } else {
        //走通用的导出函数
        //遍历 字段，导出primitive, 嵌套的结构体和类

        OrcMetaField *cur = orc_getOrInitMeta(obj->vtable);
        while (cur){
            //导出
            exp->exportFieldByOrcMetaField(exp, cur);

            cur = cur->next;
            if (cur == NULL && obj->vtable->super){//有父类，遍历 父类的字段
                cur = orc_getOrInitMeta(obj->vtable->super);
            }
        }

    }

    return jo;
}

Orc$String* SuiDesigner$BiJson_toJsonString(Orc$String * * __outRef__, Object * obj)
{
    cJSON* jo = SuiDesigner$BiJson_toJsonObject_needToDelete(obj);

    char *str = cJSON_Print(jo);

    cJSON_Delete(jo);

    NEW_CLASS_VAR(Orc$String, ret);
    Orc$String$set_as_own(ret, str);

    return (Orc$String*)URGC_RETURN_CLASS(ret);
}
void SuiDesigner$BiJsonExporter$exportField(SuiDesigner$BiJsonExporter * self, char const * fieldStr)
{
    OrcMetaField* mf = orc_getMetaField(self->obj->vtable, fieldStr);
    if (mf){
        self->exportFieldByOrcMetaField(self, mf);
    }
}
static void _exportFieldByOrcMetaField(void *obj, cJSON*jo, OrcMetaField*mf)
{
    const char *name = mf->name;

    if (mf->type == OrcMetaType_bool){
        bool *pv = (bool*)(((char *)obj) + mf->address);
        cJSON_AddBoolToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_char){
        char *pv = (char*)(((char *)obj) + mf->address);
        cJSON_AddNumberToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_short){
        short *pv = (short*)(((char *)obj) + mf->address);
        cJSON_AddNumberToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_int){
        int *pv = (int*)(((char *)obj) + mf->address);
        cJSON_AddNumberToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_long){
        long *pv = (long*) (((char *)obj) + mf->address);
        cJSON_AddNumberToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_long_long){
        long long *pv = (long long *)(((char *)obj) + mf->address);
        cJSON_AddNumberToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_float){
        float *pv = (float *)(((char *)obj) + mf->address);
        cJSON_AddNumberToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_double){
        double *pv = (double *) (((char *)obj) + mf->address);
        cJSON_AddNumberToObject(jo, name, *pv);
    }
    else if (mf->type == OrcMetaType_struct){
        if (!(mf->isRef || mf->isPointer || mf->isArray)){
            //普通的嵌入式结构体
            //创建新的json object
            cJSON* kid = cJSON_AddObjectToObject(jo, name);
            //遍历
            OrcMetaField* cur = mf->metaStruct->headMetaField;
            void* pStruct = (void*)(((char*)obj) + mf->address);
            while (cur){
                _exportFieldByOrcMetaField(pStruct, kid, cur);
                cur = cur->next;
            }
        }
    }
    else if (mf->type == OrcMetaType_class){
        //引用的对象
        if (mf->isRef){
            Object** fieldObj = (Object**)( ((char*) obj) + mf->address );
            Object* objVal = *fieldObj;
            //说明是String类型
            if (objVal && objVal->vtable == (void*)Vtable_Orc$String_init(NULL)){
                Orc$String* str = (Orc$String*)objVal;
                cJSON_AddStringToObject(jo, name, str->str);
            }
            else {
                cJSON* kid = SuiDesigner$BiJson_toJsonObject_needToDelete(*fieldObj);
                cJSON_AddItemToObject(jo, name, kid);
            }
        }
    }
}
void SuiDesigner$BiJsonExporter$exportFieldByOrcMetaField(SuiDesigner$BiJsonExporter * self, OrcMetaField*mf)
{
    Object *obj = self->obj;
    cJSON *jo = self->jo;
    const char *name = mf->name;
    _exportFieldByOrcMetaField(obj, jo, mf);
}