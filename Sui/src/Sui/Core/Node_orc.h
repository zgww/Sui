
typedef struct tagSuiCore$InnerReact SuiCore$InnerReact;
typedef struct tagVtable_SuiCore$InnerReact Vtable_SuiCore$InnerReact;
typedef struct tagSuiCore$Node SuiCore$Node;
typedef struct tagVtable_SuiCore$Node Vtable_SuiCore$Node;


#ifndef define_struct___SuiCore__Node_orc_h__
#define define_struct___SuiCore__Node_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiCore__Node_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../../Orc/Orc.h"
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiCore__Node_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiCore__Node_orc_h__
#define __SuiCore__Node_orc_h__

//include  importHeadCode
#include "./Emitter_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/ScopeData_orc.h"
#include "../../Orc/String_orc.h"
#define INCLUDE_ONLY_TYPE
#include "./Window_orc.h"
#undef INCLUDE_ONLY_TYPE
#include "./Timer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern int  SuiCore$Node_gReactDirty;

// 虚表
struct tagVtable_SuiCore$InnerReact {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiCore$InnerReact _vtable_SuiCore$InnerReact;

// class refc:0
struct tagSuiCore$InnerReact {
	Object super; 
	Orc$Map*  old_unusedMap ;
	Orc$Map*  old_map ;
	Orc$Map*  unusedMap ;
	Orc$Map*  map ;
	int  _appendIndexForReact ;
};
Vtable_SuiCore$InnerReact* Vtable_SuiCore$InnerReact_init(Vtable_SuiCore$InnerReact* pvt);
void SuiCore$InnerReact_init_fields(SuiCore$InnerReact *self);
void SuiCore$InnerReact_init(SuiCore$InnerReact *self, void *pOwner);
SuiCore$InnerReact * SuiCore$InnerReact_new(void *pOwner);
void SuiCore$InnerReact_fini(SuiCore$InnerReact *self);



// 虚表
struct tagVtable_SuiCore$Node {
	Vtable_SuiCore$Emitter super;
};
//虚表实例
extern Vtable_SuiCore$Node _vtable_SuiCore$Node;

// class refc:0
struct tagSuiCore$Node {
	SuiCore$Emitter super; 
	char  key[32] ;
	Orc$List*  children ;
	SuiCore$Node*  parent ;
	Orc$Map*  _mapForReact ;
	Orc$Map*  _unusedMapForReact ;
	int  _appendIndexForReact ;
	bool  isNewForReact ;
	Orc$String*  name ;
	SuiCore$InnerReact*  innerReact ;
	Object*  userdata ;
	bool  hasInnerReact ;
	Orc$List*  outKids ;
	void  (*startInnerReact) (SuiCore$Node *  self);
	void  (*endInnerReact) (SuiCore$Node *  self);
	bool  mounted ;
	void  (*setMounted) (SuiCore$Node *  self, bool  mounted);
	void  (*baseOnMounted) (SuiCore$Node *  self);
	void  (*baseOnUnmounting) (SuiCore$Node *  self);
	void  (*onMounted) (SuiCore$Node *  self);
	void  (*onUnmounting) (SuiCore$Node *  self);
	Sui$Window*  ownerWindow ;
	void  (*setOwnerWindow) (SuiCore$Node *  self, Sui$Window *  win);
	SuiCore$Node *  (*getChild) (SuiCore$Node *  self, int  i);
	Sui$Window *  (*getWindow) (SuiCore$Node *  self);
	Object *  (*getChildByType) (SuiCore$Node *  self, Vtable_Object *  vt);
	int  (*getChildrenCount) (SuiCore$Node *  self);
	void  (*appendChild) (SuiCore$Node *  self, SuiCore$Node *  child);
	void  (*insertChild) (SuiCore$Node *  self, SuiCore$Node *  child, int  at);
	void  (*removeChild) (SuiCore$Node *  self, SuiCore$Node *  child);
	int  (*indexOf) (SuiCore$Node *  self, SuiCore$Node *  child);
	void  (*removeSelf) (SuiCore$Node *  self);
	void  (*dissolveSubtree) (SuiCore$Node *  self);
	Orc$List*  (*getAncients) (Orc$List **  __outRef__, SuiCore$Node *  self, bool  includeSelf);
	void  (*react) (SuiCore$Node *  self);
	void  (*invalidReact) (SuiCore$Node *  self);
	void  (*trigger_react) (SuiCore$Node *  self);
	bool  _reactDirty ;
	Orc$String*  (*toString) (Orc$String **  __outRef__, SuiCore$Node *  self);
	Orc$ScopeData (*__exit__) (SuiCore$Node *  self);
};
Vtable_SuiCore$Node* Vtable_SuiCore$Node_init(Vtable_SuiCore$Node* pvt);
void SuiCore$Node_init_fields(SuiCore$Node *self);
void SuiCore$Node_init(SuiCore$Node *self, void *pOwner);
SuiCore$Node * SuiCore$Node_new(void *pOwner);
void SuiCore$Node_fini(SuiCore$Node *self);

void  SuiCore$Node$startInnerReact(SuiCore$Node *  self);
void  SuiCore$Node$endInnerReact(SuiCore$Node *  self);
void  SuiCore$Node$setMounted(SuiCore$Node *  self, bool  mounted);
void  SuiCore$Node$baseOnMounted(SuiCore$Node *  self);
void  SuiCore$Node$baseOnUnmounting(SuiCore$Node *  self);
void  SuiCore$Node$onMounted(SuiCore$Node *  self);
void  SuiCore$Node$onUnmounting(SuiCore$Node *  self);
void  SuiCore$Node$setOwnerWindow(SuiCore$Node *  self, Sui$Window *  win);
SuiCore$Node *  SuiCore$Node$getChild(SuiCore$Node *  self, int  i);
Sui$Window *  SuiCore$Node$getWindow(SuiCore$Node *  self);
Object *  SuiCore$Node$getChildByType(SuiCore$Node *  self, Vtable_Object *  vt);
int  SuiCore$Node$getChildrenCount(SuiCore$Node *  self);
void  SuiCore$Node$appendChild(SuiCore$Node *  self, SuiCore$Node *  child);
void  SuiCore$Node$insertChild(SuiCore$Node *  self, SuiCore$Node *  child, int  at);
void  SuiCore$Node$removeChild(SuiCore$Node *  self, SuiCore$Node *  child);
int  SuiCore$Node$indexOf(SuiCore$Node *  self, SuiCore$Node *  child);
void  SuiCore$Node$removeSelf(SuiCore$Node *  self);
void  SuiCore$Node$dissolveSubtree(SuiCore$Node *  self);
Orc$List*  SuiCore$Node$getAncients(Orc$List **  __outRef__, SuiCore$Node *  self, bool  includeSelf);
void  SuiCore$Node$react(SuiCore$Node *  self);
void  SuiCore$Node$invalidReact(SuiCore$Node *  self);
void  SuiCore$Node$trigger_react(SuiCore$Node *  self);
Orc$String*  SuiCore$Node$toString(Orc$String **  __outRef__, SuiCore$Node *  self);
Orc$ScopeData SuiCore$Node$__exit__(SuiCore$Node *  self);

void  SuiCore$node_exit(Orc$ScopeData *  scopeData);
Orc$Map*  SuiCore$get_mapForReact(Orc$Map **  __outRef__, SuiCore$Node *  n);
Orc$Map*  SuiCore$get_unusedMapForReact(Orc$Map **  __outRef__, SuiCore$Node *  n);
void  SuiCore$clearInnerUnusedKids(SuiCore$Node *  n);
void  SuiCore$printNodesTree(Orc$List *  nodes, int  tab);
void  SuiCore$printNodeTree(SuiCore$Node *  n, int  tab);
void  SuiCore$Node$walkIf(SuiCore$Node *  self, bool  (*fn)(void *  data, SuiCore$Node *  n), void *  ud);
void  SuiCore$Node$walk(SuiCore$Node *  self, void  (*fn)(void *  data, SuiCore$Node *  n), void *  ud);
SuiCore$Node *  SuiCore$Node$getTopest(SuiCore$Node *  self);
SuiCore$Node *  SuiCore$Node$getAncestorByClass(SuiCore$Node *  self, Vtable_Object *  o);
SuiCore$Node *  SuiCore$Node$findNodeByClass(SuiCore$Node *  self, Vtable_Object *  o);
void  SuiCore$Node$endReact(SuiCore$Node *  self);
void  SuiCore$Node$end(SuiCore$Node *  self);
void  SuiCore$Node$clearUnusedKids(SuiCore$Node *  self);
void  SuiCore$Node$placeKid(SuiCore$Node *  self, SuiCore$Node *  n);
void  SuiCore$Node$placeKids(SuiCore$Node *  self, Orc$List*  kids);
bool  SuiCore$Node$isInInnerReact(SuiCore$Node *  self);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
