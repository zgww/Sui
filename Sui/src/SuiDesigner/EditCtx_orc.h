
typedef struct tagSuiDesigner$EditEventBase SuiDesigner$EditEventBase;
typedef struct tagVtable_SuiDesigner$EditEventBase Vtable_SuiDesigner$EditEventBase;
typedef struct tagSuiDesigner$EditEventSelectedChanged SuiDesigner$EditEventSelectedChanged;
typedef struct tagVtable_SuiDesigner$EditEventSelectedChanged Vtable_SuiDesigner$EditEventSelectedChanged;
typedef struct tagSuiDesigner$EditCtx SuiDesigner$EditCtx;
typedef struct tagVtable_SuiDesigner$EditCtx Vtable_SuiDesigner$EditCtx;


#ifndef define_struct___SuiDesigner__EditCtx_orc_h__
#define define_struct___SuiDesigner__EditCtx_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__EditCtx_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__EditCtx_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__EditCtx_orc_h__
#define __SuiDesigner__EditCtx_orc_h__

//include  importHeadCode
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Json/Json_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "./RegisterNodes_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "./ANode_orc.h"
#include "./Prefab_orc.h"
#include "./SceneView_orc.h"
#include "./SceneHierView_orc.h"
#include "./EventANodeChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$EditEventBase {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiDesigner$EditEventBase _vtable_SuiDesigner$EditEventBase;

// class refc:0
struct tagSuiDesigner$EditEventBase {
	SuiCore$Event super; 
	
};
Vtable_SuiDesigner$EditEventBase* Vtable_SuiDesigner$EditEventBase_init(Vtable_SuiDesigner$EditEventBase* pvt);
void SuiDesigner$EditEventBase_init_fields(SuiDesigner$EditEventBase *self);
void SuiDesigner$EditEventBase_init(SuiDesigner$EditEventBase *self, void *pOwner);
SuiDesigner$EditEventBase * SuiDesigner$EditEventBase_new(void *pOwner);
void SuiDesigner$EditEventBase_fini(SuiDesigner$EditEventBase *self);



// 虚表
struct tagVtable_SuiDesigner$EditEventSelectedChanged {
	Vtable_SuiDesigner$EditEventBase super;
};
//虚表实例
extern Vtable_SuiDesigner$EditEventSelectedChanged _vtable_SuiDesigner$EditEventSelectedChanged;

// class refc:0
struct tagSuiDesigner$EditEventSelectedChanged {
	SuiDesigner$EditEventBase super; 
	
};
Vtable_SuiDesigner$EditEventSelectedChanged* Vtable_SuiDesigner$EditEventSelectedChanged_init(Vtable_SuiDesigner$EditEventSelectedChanged* pvt);
void SuiDesigner$EditEventSelectedChanged_init_fields(SuiDesigner$EditEventSelectedChanged *self);
void SuiDesigner$EditEventSelectedChanged_init(SuiDesigner$EditEventSelectedChanged *self, void *pOwner);
SuiDesigner$EditEventSelectedChanged * SuiDesigner$EditEventSelectedChanged_new(void *pOwner);
void SuiDesigner$EditEventSelectedChanged_fini(SuiDesigner$EditEventSelectedChanged *self);



// 虚表
struct tagVtable_SuiDesigner$EditCtx {
	Vtable_SuiCore$Emitter super;
};
//虚表实例
extern Vtable_SuiDesigner$EditCtx _vtable_SuiDesigner$EditCtx;

// class refc:0
struct tagSuiDesigner$EditCtx {
	SuiCore$Emitter super; 
	SuiDesigner$ANode*  root ;
	Orc$List*  roots ;
	SuiView$TreeState*  state ;
	SuiDesigner$ANode*  hoverNode ;
	SuiDesigner$Prefab*  prefab ;
	SuiDesigner$SceneView*  sceneView ;
	SuiDesigner$ANode*  (*findANodeByNode) (SuiDesigner$ANode **  __outRef__, SuiDesigner$EditCtx *  self, SuiCore$Node *  node);
	void  (*setState) (SuiDesigner$EditCtx *  self, SuiView$TreeState*  state);
	void  (*onSelectedChanged) (SuiDesigner$EditCtx *  self);
	void  (*closeCurrentPrefab) (SuiDesigner$EditCtx *  self);
	void  (*openPrefab) (SuiDesigner$EditCtx *  self, const char *  path);
	void  (*init) (SuiDesigner$EditCtx *  self);
};
Vtable_SuiDesigner$EditCtx* Vtable_SuiDesigner$EditCtx_init(Vtable_SuiDesigner$EditCtx* pvt);
void SuiDesigner$EditCtx_init_fields(SuiDesigner$EditCtx *self);
void SuiDesigner$EditCtx_init(SuiDesigner$EditCtx *self, void *pOwner);
SuiDesigner$EditCtx * SuiDesigner$EditCtx_new(void *pOwner);
void SuiDesigner$EditCtx_fini(SuiDesigner$EditCtx *self);

SuiDesigner$ANode*  SuiDesigner$EditCtx$findANodeByNode(SuiDesigner$ANode **  __outRef__, SuiDesigner$EditCtx *  self, SuiCore$Node *  node);
void  SuiDesigner$EditCtx$setState(SuiDesigner$EditCtx *  self, SuiView$TreeState*  state);
void  SuiDesigner$EditCtx$onSelectedChanged(SuiDesigner$EditCtx *  self);
void  SuiDesigner$EditCtx$closeCurrentPrefab(SuiDesigner$EditCtx *  self);
void  SuiDesigner$EditCtx$openPrefab(SuiDesigner$EditCtx *  self, const char *  path);
void  SuiDesigner$EditCtx$init(SuiDesigner$EditCtx *  self);

SuiDesigner$EditCtx*  SuiDesigner$EditCtx_ins(SuiDesigner$EditCtx **  __outRef__);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
