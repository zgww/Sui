
typedef struct tagSuiDesigner$InspectorView SuiDesigner$InspectorView;
typedef struct tagVtable_SuiDesigner$InspectorView Vtable_SuiDesigner$InspectorView;


#ifndef define_struct___SuiDesigner__InspectorView_orc_h__
#define define_struct___SuiDesigner__InspectorView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__InspectorView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include "../Json/cJSON.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__InspectorView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__InspectorView_orc_h__
#define __SuiDesigner__InspectorView_orc_h__

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
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./SceneView_orc.h"
#include "./SceneHierView_orc.h"
#include "./ANode_orc.h"
#include "./EditCtx_orc.h"
#include "./Inspector_orc.h"
#include "./EventANodeChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$InspectorView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiDesigner$InspectorView _vtable_SuiDesigner$InspectorView;

// class refc:0
struct tagSuiDesigner$InspectorView {
	SuiLayout$LayoutLinear super; 
	SuiDesigner$Inspector*  inspector ;
};
Vtable_SuiDesigner$InspectorView* Vtable_SuiDesigner$InspectorView_init(Vtable_SuiDesigner$InspectorView* pvt);
void SuiDesigner$InspectorView_init_fields(SuiDesigner$InspectorView *self);
void SuiDesigner$InspectorView_init(SuiDesigner$InspectorView *self, void *pOwner);
SuiDesigner$InspectorView * SuiDesigner$InspectorView_new(void *pOwner);
void SuiDesigner$InspectorView_fini(SuiDesigner$InspectorView *self);

void  SuiDesigner$InspectorView$onListenerEvent(SuiDesigner$InspectorView *  self, SuiCore$Event *  e);
void  SuiDesigner$InspectorView$onMounted(SuiDesigner$InspectorView *  self);
void  SuiDesigner$InspectorView$onUnmounting(SuiDesigner$InspectorView *  self);
void  SuiDesigner$InspectorView$react(SuiDesigner$InspectorView *  self);

SuiDesigner$InspectorView*  SuiDesigner$mkInspectorView(SuiDesigner$InspectorView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
