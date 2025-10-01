
#include "ANode_orc.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Orc/Orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Json/Json_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"


// static struct 


// static function declaration
static void  _setPrimitive(OrcMetaField *  mf, void *  obj, Json$Json *  value);
static void  _setStructField(void *  pStruct, MetaStruct *  metaStruct, const char *  key, Json$Json*  value);
static void  _setStructByJsonObject(void *  pStruct, MetaStruct *  metaStruct, Json$Json*  value);


Orc$String*  SuiDesigner$mkSetterName(Orc$String **  __outRef__, const char *  fieldName){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$add(Orc$String$addc(Orc$str(&tmpReturn_1, "set") , toupper(fieldName[0]) ) , fieldName + 1) ) ; 
}

static void  _setPrimitive(OrcMetaField *  mf, void *  obj, Json$Json *  value){
	if (mf->metaStruct != NULL && !mf->isPointer && !mf->isRef && !mf->isArray) {
		void *  p = OrcMetaField_getPtr(mf, obj) ;
		_setStructByJsonObject(p, mf->metaStruct, value) ;
		return ; 
	}
	if (!OrcMetaField_isPrimitive(mf) ) {
		return ; 
	}
	int  type = OrcMetaField_getType(mf) ;
	void *  p = OrcMetaField_getPtr(mf, obj) ;
	if (type == OrcMetaType_bool) {
		bool *  pv = (bool * )p;
		*pv = value->asBool(value) ;
	}
	else if (type == OrcMetaType_char) {
		char *  pv = (char * )p;
		*pv = (char )value->asInt(value) ;
	}
	else if (type == OrcMetaType_short) {
		short *  pv = (short * )p;
		*pv = (short )value->asInt(value) ;
	}
	else if (type == OrcMetaType_int) {
		int *  pv = (int * )p;
		*pv = value->asInt(value) ;
	}
	else if (type == OrcMetaType_long) {
		long *  pv = (long * )p;
		*pv = (long )value->asInt(value) ;
	}
	else if (type == OrcMetaType_long_long) {
		long long *  pv = (long long * )p;
		*pv = (long long )value->asInt(value) ;
	}
	else if (type == OrcMetaType_float) {
		float *  pv = (float * )p;
		*pv = (float )value->asNumber(value) ;
	}
	else if (type == OrcMetaType_double) {
		double *  pv = (double * )p;
		*pv = value->asNumber(value) ;
	}
}

static void  _setStructField(void *  pStruct, MetaStruct *  metaStruct, const char *  key, Json$Json*  value){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(value);

	OrcMetaField *  mf = MetaStruct_getMetaFieldByFieldName(metaStruct, key) ;
	if (mf != NULL) {
		_setPrimitive(mf, pStruct, value) ;
	}
}

static void  _setStructByJsonObject(void *  pStruct, MetaStruct *  metaStruct, Json$Json*  value){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(value);

	if (!value->isObject(value) ) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  keys = value->keys((keys = NULL,&keys), value) ;
	for (int  i = 0; i < keys->size(keys) ; i++) {
		Orc$String *  key = (Orc$String * )keys->get(keys, i) ;
		URGC_VAR_CLEANUP_CLASS Json$Json*  fieldValue = value->get((fieldValue = NULL,&fieldValue), value, key->str) ;
		_setStructField(pStruct, metaStruct, key->str, fieldValue) ;
	}
}

void  SuiDesigner$meta_setPrimitive(Object *  obj, const char *  fieldName, Json$Json*  value){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(value);

	if (!obj) {
		return ; 
	}
	Vtable_Object *  vt = orc_getVtableByObject(obj) ;
	OrcMetaField *  mf = orc_getMetaField(vt, fieldName) ;
	int  type = OrcMetaField_getType(mf) ;
	int  addr = OrcMetaField_getAddress(mf) ;
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  setterName = SuiDesigner$mkSetterName((setterName = NULL,&setterName), fieldName) ;
		OrcMetaField *  setterMf = orc_getMetaField(vt, setterName->str) ;
		if (setterMf) {
			int  setterType = OrcMetaField_getType(setterMf) ;
			if (setterType == OrcMetaType_method) {
				void *  pMethod = *((void ** )OrcMetaField_getPtr(setterMf, obj) );
				if (OrcMetaField_isStringRef(mf) ) {
					void *  pMethod2 = (void * )OrcMetaField_getPtr(setterMf, obj) ;
					void  (*set)(void *  obj, void *  val);
					set = pMethod;
					set(obj, value->stringValue) ;
				}
				if (type == OrcMetaType_bool) {
					void  (*set)(void *  obj, bool  val);
					set = pMethod;
					set(obj, value->boolValue) ;
				}
				else if (type == OrcMetaType_char) {
					void  (*set)(void *  obj, char  val);
					set = pMethod;
					set(obj, (char )value->numberValue) ;
				}
				else if (type == OrcMetaType_short) {
					void  (*set)(void *  obj, short  val);
					set = pMethod;
					set(obj, (short )value->numberValue) ;
				}
				else if (type == OrcMetaType_int) {
					void  (*set)(void *  obj, int  val);
					set = pMethod;
					set(obj, (int )value->numberValue) ;
				}
				else if (type == OrcMetaType_long) {
					void  (*set)(void *  obj, long  val);
					set = pMethod;
					set(obj, (long )value->numberValue) ;
				}
				else if (type == OrcMetaType_long_long) {
					void  (*set)(void *  obj, long long  val);
					set = pMethod;
					set(obj, (long long )value->numberValue) ;
				}
				else if (type == OrcMetaType_float) {
					void  (*set)(void *  obj, float  val);
					set = pMethod;
					set(obj, (float )value->numberValue) ;
				}
				else if (type == OrcMetaType_double) {
					void  (*set)(void *  obj, double  val);
					set = pMethod;
					set(obj, value->numberValue) ;
				}
			}
			else {
				printf("call setter for %s:%s error\n", fieldName, setterName->str) ;
			}
			return ; 
		}
	}
	if (mf == NULL) {
		return ; 
	}
	if (mf->metaStruct != NULL && !mf->isPointer && !mf->isRef && !mf->isArray) {
		void *  p = OrcMetaField_getPtr(mf, obj) ;
		_setStructByJsonObject(p, mf->metaStruct, value) ;
		return ; 
	}
	if (OrcMetaField_isStringRef(mf) ) {
		urgc_set_field_by_offset(obj, addr, value->stringValue) ;
		return ; 
	}
	_setPrimitive(mf, obj, value) ;
}


//vtable instance
Vtable_SuiDesigner$ANodeAttr _vtable_SuiDesigner$ANodeAttr;

// init meta

void SuiDesigner$ANodeAttr_initMeta(Vtable_SuiDesigner$ANodeAttr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ANodeAttr, name), true, false, 1);
	orc_metaField_class(&pNext, "value", ((Vtable_Object*)Vtable_Json$Json_init(0)), offsetof(SuiDesigner$ANodeAttr, value), true, false, 1);

	orc_metaField_method(&pNext, "updateNodeAttr", offsetof(SuiDesigner$ANodeAttr, updateNodeAttr));
}


// vtable init


Vtable_SuiDesigner$ANodeAttr* Vtable_SuiDesigner$ANodeAttr_init(Vtable_SuiDesigner$ANodeAttr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ANodeAttr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ANodeAttr_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ANodeAttr";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ANodeAttr_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ANodeAttr_fini(SuiDesigner$ANodeAttr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$ANodeAttr_init_fields(SuiDesigner$ANodeAttr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ANodeAttr_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANodeAttr*)self)->name, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANodeAttr*)self)->value, Json$Json_mkNull(&tmpReturn_2) );
    }
	((SuiDesigner$ANodeAttr*)self)->updateNodeAttr = (void*)SuiDesigner$ANodeAttr$updateNodeAttr;
}

// init function

void SuiDesigner$ANodeAttr_init(SuiDesigner$ANodeAttr *self, void *pOwner){
    Vtable_SuiDesigner$ANodeAttr_init(&_vtable_SuiDesigner$ANodeAttr);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ANodeAttr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ANodeAttr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ANodeAttr * SuiDesigner$ANodeAttr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ANodeAttr *self = calloc(1, sizeof(SuiDesigner$ANodeAttr));
	
    SuiDesigner$ANodeAttr_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ANodeAttr$updateNodeAttr(SuiDesigner$ANodeAttr *  self, SuiCore$Node*  n){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(n);

	if (n) {
		SuiDesigner$meta_setPrimitive(n, self->name->str, self->value) ;
		n->trigger_react(n) ;
	}
}




//vtable instance
Vtable_SuiDesigner$ANode _vtable_SuiDesigner$ANode;

// init meta

void SuiDesigner$ANode_initMeta(Vtable_SuiDesigner$ANode *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "id", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ANode, id), true, false, 1);
	orc_metaField_class(&pNext, "tag", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ANode, tag), true, false, 1);
	orc_metaField_class(&pNext, "attrs", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$ANode, attrs), true, false, 1);
	orc_metaField_class(&pNext, "children", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$ANode, children), true, false, 1);
	orc_metaField_class(&pNext, "node", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$ANode, node), true, false, 1);
	orc_metaField_class(&pNext, "parent", ((Vtable_Object*)Vtable_SuiDesigner$ANode_init(0)), offsetof(SuiDesigner$ANode, parent), true, false, 1);

	orc_metaField_method(&pNext, "getId", offsetof(SuiDesigner$ANode, getId));
	orc_metaField_method(&pNext, "getName", offsetof(SuiDesigner$ANode, getName));
	orc_metaField_method(&pNext, "clone", offsetof(SuiDesigner$ANode, clone));
	orc_metaField_method(&pNext, "setAttrValueObject", offsetof(SuiDesigner$ANode, setAttrValueObject));
	orc_metaField_method(&pNext, "setAttr", offsetof(SuiDesigner$ANode, setAttr));
	orc_metaField_method(&pNext, "getAttrByName", offsetof(SuiDesigner$ANode, getAttrByName));
	orc_metaField_method(&pNext, "getAttrValueByName", offsetof(SuiDesigner$ANode, getAttrValueByName));
	orc_metaField_method(&pNext, "getAttrStringValueByName", offsetof(SuiDesigner$ANode, getAttrStringValueByName));
	orc_metaField_method(&pNext, "updateSubTreeNodes", offsetof(SuiDesigner$ANode, updateSubTreeNodes));
	orc_metaField_method(&pNext, "updateNode", offsetof(SuiDesigner$ANode, updateNode));
	orc_metaField_method(&pNext, "updateNodeAttr", offsetof(SuiDesigner$ANode, updateNodeAttr));
	orc_metaField_method(&pNext, "updateNode_syncIndex", offsetof(SuiDesigner$ANode, updateNode_syncIndex));
	orc_metaField_method(&pNext, "findANodeByNode", offsetof(SuiDesigner$ANode, findANodeByNode));
	orc_metaField_method(&pNext, "removeChild", offsetof(SuiDesigner$ANode, removeChild));
	orc_metaField_method(&pNext, "removeSelf", offsetof(SuiDesigner$ANode, removeSelf));
	orc_metaField_method(&pNext, "appendChild", offsetof(SuiDesigner$ANode, appendChild));
	orc_metaField_method(&pNext, "indexOf", offsetof(SuiDesigner$ANode, indexOf));
	orc_metaField_method(&pNext, "setChildren", offsetof(SuiDesigner$ANode, setChildren));
	orc_metaField_method(&pNext, "printTree", offsetof(SuiDesigner$ANode, printTree));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$ANode, toJson));
	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$ANode, fromJson));
}


// vtable init


Vtable_SuiDesigner$ANode* Vtable_SuiDesigner$ANode_init(Vtable_SuiDesigner$ANode* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ANode;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ANode_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ANode";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ANode_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ANode_fini(SuiDesigner$ANode *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$ANode_init_fields(SuiDesigner$ANode *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ANode_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANode*)self)->id, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANode*)self)->tag, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANode*)self)->attrs, Orc$List_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANode*)self)->children, Orc$List_new(&tmpNewOwner_3) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANode*)self)->node, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ANode*)self)->parent, NULL);
    }
	((SuiDesigner$ANode*)self)->getId = (void*)SuiDesigner$ANode$getId;
	((SuiDesigner$ANode*)self)->getName = (void*)SuiDesigner$ANode$getName;
	((SuiDesigner$ANode*)self)->clone = (void*)SuiDesigner$ANode$clone;
	((SuiDesigner$ANode*)self)->setAttrValueObject = (void*)SuiDesigner$ANode$setAttrValueObject;
	((SuiDesigner$ANode*)self)->setAttr = (void*)SuiDesigner$ANode$setAttr;
	((SuiDesigner$ANode*)self)->getAttrByName = (void*)SuiDesigner$ANode$getAttrByName;
	((SuiDesigner$ANode*)self)->getAttrValueByName = (void*)SuiDesigner$ANode$getAttrValueByName;
	((SuiDesigner$ANode*)self)->getAttrStringValueByName = (void*)SuiDesigner$ANode$getAttrStringValueByName;
	((SuiDesigner$ANode*)self)->updateSubTreeNodes = (void*)SuiDesigner$ANode$updateSubTreeNodes;
	((SuiDesigner$ANode*)self)->updateNode = (void*)SuiDesigner$ANode$updateNode;
	((SuiDesigner$ANode*)self)->updateNodeAttr = (void*)SuiDesigner$ANode$updateNodeAttr;
	((SuiDesigner$ANode*)self)->updateNode_syncIndex = (void*)SuiDesigner$ANode$updateNode_syncIndex;
	((SuiDesigner$ANode*)self)->findANodeByNode = (void*)SuiDesigner$ANode$findANodeByNode;
	((SuiDesigner$ANode*)self)->removeChild = (void*)SuiDesigner$ANode$removeChild;
	((SuiDesigner$ANode*)self)->removeSelf = (void*)SuiDesigner$ANode$removeSelf;
	((SuiDesigner$ANode*)self)->appendChild = (void*)SuiDesigner$ANode$appendChild;
	((SuiDesigner$ANode*)self)->indexOf = (void*)SuiDesigner$ANode$indexOf;
	((SuiDesigner$ANode*)self)->setChildren = (void*)SuiDesigner$ANode$setChildren;
	((SuiDesigner$ANode*)self)->printTree = (void*)SuiDesigner$ANode$printTree;
	((SuiDesigner$ANode*)self)->toJson = (void*)SuiDesigner$ANode$toJson;
	((SuiDesigner$ANode*)self)->fromJson = (void*)SuiDesigner$ANode$fromJson;
}

// init function

void SuiDesigner$ANode_init(SuiDesigner$ANode *self, void *pOwner){
    Vtable_SuiDesigner$ANode_init(&_vtable_SuiDesigner$ANode);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ANode;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ANode_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ANode * SuiDesigner$ANode_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ANode *self = calloc(1, sizeof(SuiDesigner$ANode));
	
    SuiDesigner$ANode_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiDesigner$ANode$getId(Orc$String **  __outRef__, SuiDesigner$ANode *  self){
	if (!self->id) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ANode, id) , Orc$str(&tmpReturn_1, "") ) ;
		Orc$String$addll(self->id, (long long )self) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, self->id) ; 
}


Orc$String*  SuiDesigner$ANode$getName(Orc$String **  __outRef__, SuiDesigner$ANode *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = self->getAttrStringValueByName((ret = NULL,&ret), self, "name") ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


SuiDesigner$ANode*  SuiDesigner$ANode$clone(SuiDesigner$ANode **  __outRef__, SuiDesigner$ANode *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = self->toJson((jo = NULL,&jo), self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiDesigner$ANode_new(&n) ));
	n->fromJson(n, jo) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, n) ; 
}


void  SuiDesigner$ANode$setAttrValueObject(SuiDesigner$ANode *  self, const char *  name, Object *  value){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_toJson((jo = NULL,&jo), value) ;
	self->setAttr(self, name, jo) ;
}


void  SuiDesigner$ANode$setAttr(SuiDesigner$ANode *  self, const char *  name, Json$Json*  value){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(value);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  a = self->getAttrByName((a = NULL,&a), self, name) ;
	if (a) {
		urgc_set_field_class(a, (void * )offsetof(SuiDesigner$ANodeAttr, value) , value) ;
	}
	else {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&a, SuiDesigner$ANodeAttr_new(&tmpNewOwner_1) ) ;
		Orc$String$set(a->name, name) ;
		urgc_set_field_class(a, (void * )offsetof(SuiDesigner$ANodeAttr, value) , value) ;
		self->attrs->add(self->attrs, a) ;
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	printf("\tanode 收到属性设置请求。 name:%s, value:%s\n", name, value->dump(&tmpReturn_2, value) ->str) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeAttrChanged*  tmpNewOwner_3 = NULL;
	{
		SuiDesigner$EventANodeAttrChanged*  o = SuiDesigner$EventANodeAttrChanged_new(&tmpNewOwner_3) ;
		
	
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
	a->updateNodeAttr(a, self->node) ;
}


SuiDesigner$ANodeAttr*  SuiDesigner$ANode$getAttrByName(SuiDesigner$ANodeAttr **  __outRef__, SuiDesigner$ANode *  self, const char *  name){
	for (int  i = 0; i < self->attrs->size(self->attrs) ; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  a = (a=NULL,urgc_init_var_class((void**)&a, (SuiDesigner$ANodeAttr* )self->attrs->get(self->attrs, i) ));
		if (Orc$String$equals(a->name, name) ) {
			return urgc_set_var_for_return_class((void ** )__outRef__, a) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


Json$Json*  SuiDesigner$ANode$getAttrValueByName(Json$Json **  __outRef__, SuiDesigner$ANode *  self, const char *  name){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  a = self->getAttrByName((a = NULL,&a), self, name) ;
	if (a) {
		return urgc_set_var_for_return_class((void ** )__outRef__, a->value) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


Orc$String*  SuiDesigner$ANode$getAttrStringValueByName(Orc$String **  __outRef__, SuiDesigner$ANode *  self, const char *  name){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  a = self->getAttrByName((a = NULL,&a), self, name) ;
	if (a && a->value) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, a->value->asString(&tmpReturn_1, a->value) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_2, "") ) ; 
}


void  SuiDesigner$ANode$updateSubTreeNodes(SuiDesigner$ANode *  self){
	self->updateNode(self) ;
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiDesigner$ANode *  kid = (SuiDesigner$ANode * )self->children->get(self->children, i) ;
		kid->updateSubTreeNodes(kid) ;
	}
}


void  SuiDesigner$ANode$updateNode(SuiDesigner$ANode *  self){
	if (!self->node) {
		SuiCore$NodeLib *  tmpThis_1 = NULL;
		URGC_VAR_CLEANUP_CLASS SuiCore$NodeRegisterInfo*  registerInfo = (tmpThis_1 = SuiCore$NodeLib_use() )->findByClassName((registerInfo = NULL,&registerInfo), tmpThis_1, self->tag->str) ;
		if (registerInfo) {
			URGC_VAR_CLEANUP_CLASS Object*  tmp = registerInfo->mk((tmp = NULL,&tmp), registerInfo) ;
			if (Orc_instanceof((Object*)tmp, (Vtable_Object*)Vtable_SuiCore$Node_init(NULL))) {
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ANode, node) , tmp) ;
				self->updateNodeAttr(self) ;
			}
			else {
				printf("WARN; className[%s] not a node", self->tag->str) ;
			}
		}
	}
	self->updateNode_syncIndex(self) ;
}


void  SuiDesigner$ANode$updateNodeAttr(SuiDesigner$ANode *  self){
	for (int  i = 0; i < self->attrs->size(self->attrs) ; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  attr = (attr=NULL,urgc_init_var_class((void**)&attr, (SuiDesigner$ANodeAttr* )self->attrs->get(self->attrs, i) ));
		attr->updateNodeAttr(attr, self->node) ;
	}
	if (Orc_instanceof((Object*)self->node, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )self->node;
		((SuiCore$Node * )vb)->invalidReact(vb) ;
	}
}


void  SuiDesigner$ANode$updateNode_syncIndex(SuiDesigner$ANode *  self){
	if (self->parent && self->node) {
		SuiCore$Node *  parentNode = self->parent->node;
		if (parentNode) {
			int  idx = self->parent->indexOf(self->parent, self) ;
			if (idx != -1 && parentNode->getChild(parentNode, idx)  != self->node) {
				parentNode->insertChild(parentNode, self->node, idx) ;
			}
		}
	}
}


SuiDesigner$ANode*  SuiDesigner$ANode$findANodeByNode(SuiDesigner$ANode **  __outRef__, SuiDesigner$ANode *  self, SuiCore$Node *  node){
	if (self->node == node) {
		return urgc_set_var_for_return_class((void ** )__outRef__, self) ; 
	}
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiDesigner$ANode *  kid = (SuiDesigner$ANode * )self->children->get(self->children, i) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  found = kid->findANodeByNode((found = NULL,&found), kid, node) ;
		if (found) {
			return urgc_set_var_for_return_class((void ** )__outRef__, found) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


void  SuiDesigner$ANode$removeChild(SuiDesigner$ANode *  self, SuiDesigner$ANode*  child){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(child);

	if (child->parent == self) {
		if (child->node) {
			child->node->removeSelf(child->node) ;
		}
		self->children->remove(self->children, child) ;
		urgc_set_field_class(child, (void * )offsetof(SuiDesigner$ANode, parent) , NULL) ;
	}
}


void  SuiDesigner$ANode$removeSelf(SuiDesigner$ANode *  self){
	if (self->parent) {
		self->parent->removeChild(self->parent, self) ;
	}
}


void  SuiDesigner$ANode$appendChild(SuiDesigner$ANode *  self, SuiDesigner$ANode*  n){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(n);

	n->removeSelf(n) ;
	self->children->add(self->children, n) ;
	urgc_set_field_class(n, (void * )offsetof(SuiDesigner$ANode, parent) , self) ;
}


int  SuiDesigner$ANode$indexOf(SuiDesigner$ANode *  self, SuiDesigner$ANode *  child){
	int  idx = self->children->indexOf(self->children, child) ;
	return idx; 
}


void  SuiDesigner$ANode$setChildren(SuiDesigner$ANode *  self, Orc$List*  children){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(children);

	self->children->clear(self->children) ;
	for (int  i = 0; i < children->size(children) ; i++) {
		SuiDesigner$ANode *  kid = (SuiDesigner$ANode * )children->get(children, i) ;
		self->appendChild(self, kid) ;
	}
}


void  SuiDesigner$ANode$printTree(SuiDesigner$ANode *  self, int  tab){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$str((tmp = NULL,&tmp), "") ;
	Orc$String$fillCount(tmp, "\t", tab) ;
	printf("%s%s\n", tmp->str, self->tag->str) ;
	for (int  i = 0; i < self->attrs->size(self->attrs) ; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  attr = (attr=NULL,urgc_init_var_class((void**)&attr, (SuiDesigner$ANodeAttr* )self->attrs->get(self->attrs, i) ));
		URGC_VAR_CLEANUP_CLASS Orc$String*  valueStr = attr->value->toString((valueStr = NULL,&valueStr), attr->value) ;
		printf("%s\t%s=%s\n", tmp->str, attr->name->str, valueStr->str) ;
	}
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiDesigner$ANode *  kid = (SuiDesigner$ANode * )self->children->get(self->children, i) ;
		kid->printTree(kid, tab + 1) ;
	}
}


Json$Json*  SuiDesigner$ANode$toJson(Json$Json **  __outRef__, SuiDesigner$ANode *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->putString(jo, "tag", self->tag) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  attrsJo = Json$Json_mkObject((attrsJo = NULL,&attrsJo)) ;
	jo->put(jo, "attrs", attrsJo) ;
	for (int  i = 0; i < self->attrs->size(self->attrs) ; i++) {
		SuiDesigner$ANodeAttr *  attr = (SuiDesigner$ANodeAttr * )self->attrs->get(self->attrs, i) ;
		attrsJo->put(attrsJo, attr->name->str, attr->value) ;
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  kidsJo = Json$Json_mkArray((kidsJo = NULL,&kidsJo)) ;
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiDesigner$ANode *  o = (SuiDesigner$ANode * )self->children->get(self->children, i) ;
		URGC_VAR_CLEANUP_CLASS Json$Json*  kidJo = o->toJson((kidJo = NULL,&kidJo), o) ;
		kidsJo->add(kidsJo, kidJo) ;
	}
	jo->put(jo, "children", kidsJo) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
}


void  SuiDesigner$ANode$fromJson(SuiDesigner$ANode *  self, Json$Json *  jo){
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = jo->getString((s = NULL,&s), jo, "tag") ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ANode, tag) , s) ;
	{
		self->attrs->clear(self->attrs) ;
		URGC_VAR_CLEANUP_CLASS Json$Json*  attrsJo = jo->get((attrsJo = NULL,&attrsJo), jo, "attrs") ;
		if (attrsJo) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  keys = attrsJo->keys((keys = NULL,&keys), attrsJo) ;
			for (int  i = 0; i < keys->size(keys) ; i++) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, (Orc$String* )keys->at(keys, i) ));
				URGC_VAR_CLEANUP_CLASS Json$Json*  value = attrsJo->get((value = NULL,&value), attrsJo, key->str) ;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$ANodeAttr*  attr = (attr=NULL,urgc_init_var_class((void**)&attr, SuiDesigner$ANodeAttr_new(&attr) ));
				urgc_set_field_class(attr, (void * )offsetof(SuiDesigner$ANodeAttr, name) , key) ;
				urgc_set_field_class(attr, (void * )offsetof(SuiDesigner$ANodeAttr, value) , value) ;
				self->attrs->add(self->attrs, attr) ;
			}
		}
	}
	{
		URGC_VAR_CLEANUP_CLASS Json$Json*  kidsJo = jo->get((kidsJo = NULL,&kidsJo), jo, "children") ;
		if (kidsJo) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  kids = SuiDesigner$ANode_parseByJsonArray((kids = NULL,&kids), kidsJo) ;
			self->setChildren(self, kids) ;
		}
	}
}



Orc$List*  SuiDesigner$ANode_parseByJsonArray(Orc$List **  __outRef__, Json$Json*  kidsJo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(kidsJo);

	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
	for (int  i = 0; i < kidsJo->size(kidsJo) ; i++) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  kidJo = kidsJo->at((kidJo = NULL,&kidJo), kidsJo, i) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  anode = (anode=NULL,urgc_init_var_class((void**)&anode, SuiDesigner$ANode_new(&anode) ));
		anode->fromJson(anode, kidJo) ;
		ret->add(ret, anode) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}



