
typedef struct tagHoroEditor$HoroInspView HoroEditor$HoroInspView;
typedef struct tagVtable_HoroEditor$HoroInspView Vtable_HoroEditor$HoroInspView;


#ifndef define_struct___HoroEditor__HoroInspView_orc_h__
#define define_struct___HoroEditor__HoroInspView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__HoroInspView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include "../Json/cJSON.h"




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__HoroInspView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__HoroInspView_orc_h__
#define __HoroEditor__HoroInspView_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../SuiDesigner/Insp_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Json/Json_orc.h"
#include "./HoroEditCtx_orc.h"
#include "./HoroEditor_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_HoroEditor$HoroInspView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_HoroEditor$HoroInspView _vtable_HoroEditor$HoroInspView;

// class refc:0
struct tagHoroEditor$HoroInspView {
	SuiLayout$LayoutLinear super; 
	SuiDesigner$Insp*  insp ;
	HoroEditor$HoroEditCtx*  editCtx ;
	HoroEditor$HoroEditor*  editor ;
};
Vtable_HoroEditor$HoroInspView* Vtable_HoroEditor$HoroInspView_init(Vtable_HoroEditor$HoroInspView* pvt);
void HoroEditor$HoroInspView_init_fields(HoroEditor$HoroInspView *self);
void HoroEditor$HoroInspView_init(HoroEditor$HoroInspView *self, void *pOwner);
HoroEditor$HoroInspView * HoroEditor$HoroInspView_new(void *pOwner);
void HoroEditor$HoroInspView_fini(HoroEditor$HoroInspView *self);

void  HoroEditor$HoroInspView$ctor(HoroEditor$HoroInspView *  self);
void  HoroEditor$HoroInspView$onListenerEvent(HoroEditor$HoroInspView *  self, SuiCore$Event *  e);
void  HoroEditor$HoroInspView$onMounted(HoroEditor$HoroInspView *  self);
void  HoroEditor$HoroInspView$onUnmounting(HoroEditor$HoroInspView *  self);
void  HoroEditor$HoroInspView$react(HoroEditor$HoroInspView *  self);

HoroEditor$HoroInspView*  HoroEditor$mkHoroInspView(HoroEditor$HoroInspView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
