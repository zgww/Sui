
typedef struct tagSuiDesigner$ANodeAttr SuiDesigner$ANodeAttr;
typedef struct tagVtable_SuiDesigner$ANodeAttr Vtable_SuiDesigner$ANodeAttr;
typedef struct tagSuiDesigner$ANode SuiDesigner$ANode;
typedef struct tagVtable_SuiDesigner$ANode Vtable_SuiDesigner$ANode;


#ifndef define_struct___SuiDesigner__ANode_orc_h__
#define define_struct___SuiDesigner__ANode_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__ANode_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__ANode_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__ANode_orc_h__
#define __SuiDesigner__ANode_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Json/Json_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
Orc$String*  SuiDesigner$mkSetterName(Orc$String **  __outRef__, const char *  fieldName);
void  SuiDesigner$meta_setPrimitive(Object *  obj, const char *  fieldName, Json$Json*  value);

// 虚表
struct tagVtable_SuiDesigner$ANodeAttr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ANodeAttr _vtable_SuiDesigner$ANodeAttr;

// class refc:0
struct tagSuiDesigner$ANodeAttr {
	Object super; 
	Orc$String*  name ;
	Json$Json*  value ;
	void  (*updateNodeAttr) (SuiDesigner$ANodeAttr *  self, SuiCore$Node*  n);
};
Vtable_SuiDesigner$ANodeAttr* Vtable_SuiDesigner$ANodeAttr_init(Vtable_SuiDesigner$ANodeAttr* pvt);
void SuiDesigner$ANodeAttr_init_fields(SuiDesigner$ANodeAttr *self);
void SuiDesigner$ANodeAttr_init(SuiDesigner$ANodeAttr *self, void *pOwner);
SuiDesigner$ANodeAttr * SuiDesigner$ANodeAttr_new(void *pOwner);
void SuiDesigner$ANodeAttr_fini(SuiDesigner$ANodeAttr *self);

void  SuiDesigner$ANodeAttr$updateNodeAttr(SuiDesigner$ANodeAttr *  self, SuiCore$Node*  n);


// 虚表
struct tagVtable_SuiDesigner$ANode {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ANode _vtable_SuiDesigner$ANode;

// class refc:0
struct tagSuiDesigner$ANode {
	Object super; 
	Orc$String*  id ;
	Orc$String*  (*getId) (Orc$String **  __outRef__, SuiDesigner$ANode *  self);
	Orc$String*  tag ;
	Orc$List*  attrs ;
	Orc$List*  children ;
	SuiCore$Node*  node ;
	SuiDesigner$ANode*  parent ;
	Orc$String*  (*getName) (Orc$String **  __outRef__, SuiDesigner$ANode *  self);
	SuiDesigner$ANode*  (*clone) (SuiDesigner$ANode **  __outRef__, SuiDesigner$ANode *  self);
	void  (*setAttrValueObject) (SuiDesigner$ANode *  self, const char *  name, Object *  value);
	void  (*setAttr) (SuiDesigner$ANode *  self, const char *  name, Json$Json*  value);
	SuiDesigner$ANodeAttr*  (*getAttrByName) (SuiDesigner$ANodeAttr **  __outRef__, SuiDesigner$ANode *  self, const char *  name);
	Json$Json*  (*getAttrValueByName) (Json$Json **  __outRef__, SuiDesigner$ANode *  self, const char *  name);
	Orc$String*  (*getAttrStringValueByName) (Orc$String **  __outRef__, SuiDesigner$ANode *  self, const char *  name);
	void  (*updateSubTreeNodes) (SuiDesigner$ANode *  self);
	void  (*updateNode) (SuiDesigner$ANode *  self);
	void  (*updateNodeAttr) (SuiDesigner$ANode *  self);
	void  (*updateNode_syncIndex) (SuiDesigner$ANode *  self);
	SuiDesigner$ANode*  (*findANodeByNode) (SuiDesigner$ANode **  __outRef__, SuiDesigner$ANode *  self, SuiCore$Node *  node);
	void  (*removeChild) (SuiDesigner$ANode *  self, SuiDesigner$ANode*  child);
	void  (*removeSelf) (SuiDesigner$ANode *  self);
	void  (*appendChild) (SuiDesigner$ANode *  self, SuiDesigner$ANode*  n);
	int  (*indexOf) (SuiDesigner$ANode *  self, SuiDesigner$ANode *  child);
	void  (*setChildren) (SuiDesigner$ANode *  self, Orc$List*  children);
	void  (*printTree) (SuiDesigner$ANode *  self, int  tab);
	Json$Json*  (*toJson) (Json$Json **  __outRef__, SuiDesigner$ANode *  self);
	void  (*fromJson) (SuiDesigner$ANode *  self, Json$Json *  jo);
};
Vtable_SuiDesigner$ANode* Vtable_SuiDesigner$ANode_init(Vtable_SuiDesigner$ANode* pvt);
void SuiDesigner$ANode_init_fields(SuiDesigner$ANode *self);
void SuiDesigner$ANode_init(SuiDesigner$ANode *self, void *pOwner);
SuiDesigner$ANode * SuiDesigner$ANode_new(void *pOwner);
void SuiDesigner$ANode_fini(SuiDesigner$ANode *self);

Orc$String*  SuiDesigner$ANode$getId(Orc$String **  __outRef__, SuiDesigner$ANode *  self);
Orc$String*  SuiDesigner$ANode$getName(Orc$String **  __outRef__, SuiDesigner$ANode *  self);
SuiDesigner$ANode*  SuiDesigner$ANode$clone(SuiDesigner$ANode **  __outRef__, SuiDesigner$ANode *  self);
void  SuiDesigner$ANode$setAttrValueObject(SuiDesigner$ANode *  self, const char *  name, Object *  value);
void  SuiDesigner$ANode$setAttr(SuiDesigner$ANode *  self, const char *  name, Json$Json*  value);
SuiDesigner$ANodeAttr*  SuiDesigner$ANode$getAttrByName(SuiDesigner$ANodeAttr **  __outRef__, SuiDesigner$ANode *  self, const char *  name);
Json$Json*  SuiDesigner$ANode$getAttrValueByName(Json$Json **  __outRef__, SuiDesigner$ANode *  self, const char *  name);
Orc$String*  SuiDesigner$ANode$getAttrStringValueByName(Orc$String **  __outRef__, SuiDesigner$ANode *  self, const char *  name);
void  SuiDesigner$ANode$updateSubTreeNodes(SuiDesigner$ANode *  self);
void  SuiDesigner$ANode$updateNode(SuiDesigner$ANode *  self);
void  SuiDesigner$ANode$updateNodeAttr(SuiDesigner$ANode *  self);
void  SuiDesigner$ANode$updateNode_syncIndex(SuiDesigner$ANode *  self);
SuiDesigner$ANode*  SuiDesigner$ANode$findANodeByNode(SuiDesigner$ANode **  __outRef__, SuiDesigner$ANode *  self, SuiCore$Node *  node);
void  SuiDesigner$ANode$removeChild(SuiDesigner$ANode *  self, SuiDesigner$ANode*  child);
void  SuiDesigner$ANode$removeSelf(SuiDesigner$ANode *  self);
void  SuiDesigner$ANode$appendChild(SuiDesigner$ANode *  self, SuiDesigner$ANode*  n);
int  SuiDesigner$ANode$indexOf(SuiDesigner$ANode *  self, SuiDesigner$ANode *  child);
void  SuiDesigner$ANode$setChildren(SuiDesigner$ANode *  self, Orc$List*  children);
void  SuiDesigner$ANode$printTree(SuiDesigner$ANode *  self, int  tab);
Json$Json*  SuiDesigner$ANode$toJson(Json$Json **  __outRef__, SuiDesigner$ANode *  self);
void  SuiDesigner$ANode$fromJson(SuiDesigner$ANode *  self, Json$Json *  jo);

Orc$List*  SuiDesigner$ANode_parseByJsonArray(Orc$List **  __outRef__, Json$Json*  kidsJo);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
