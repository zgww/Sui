
typedef struct tagSuiDesigner$AssetDirTreeView SuiDesigner$AssetDirTreeView;
typedef struct tagVtable_SuiDesigner$AssetDirTreeView Vtable_SuiDesigner$AssetDirTreeView;


#ifndef define_struct___SuiDesigner__AssetDirTreeView_orc_h__
#define define_struct___SuiDesigner__AssetDirTreeView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__AssetDirTreeView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__AssetDirTreeView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__AssetDirTreeView_orc_h__
#define __SuiDesigner__AssetDirTreeView_orc_h__

//include  importHeadCode
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Path_orc.h"
#include "../../Sui/Core/View_orc.h"
#include "../../Sui/Core/ViewBase_orc.h"
#include "../../Sui/Core/Node_orc.h"
#include "../../Sui/Core/Event_orc.h"
#include "../../Sui/Core/Emitter_orc.h"
#include "../../Sui/Dialog/MessageDialog_orc.h"
#include "../../Sui/Core/MouseEvent_orc.h"
#include "../../Sui/View/TextView_orc.h"
#include "../../Sui/View/TreeView_orc.h"
#include "../../Sui/View/ImageView_orc.h"
#include "../../Sui/View/ViewBuilder_orc.h"
#include "../../Sui/View/ScrollArea_orc.h"
#include "../../Sui/View/MenuNative_orc.h"
#include "../../Sui/View/HoverViewEffect_orc.h"
#include "../../Sui/Layout/LayoutLinear_orc.h"
#include "../../Sui/Layout/RowWrap_orc.h"
#include "../../Sui/Layout/LayoutAlign_orc.h"
#include "../FileItem_orc.h"
#include "../UiAction_orc.h"
#include "../../HoroEditor/UiAct_orc.h"
#include "../Project_orc.h"
#include "../EventANodeChanged_orc.h"
#include "../EventFileItemChanged_orc.h"
#include "../Theme_orc.h"
#include "./AssetDirView_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$AssetDirTreeView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiDesigner$AssetDirTreeView _vtable_SuiDesigner$AssetDirTreeView;

// class refc:0
struct tagSuiDesigner$AssetDirTreeView {
	SuiLayout$LayoutLinear super; 
	void  (*_routeMenuNativeItem) (SuiDesigner$AssetDirTreeView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$FileItem*  fi);
	void  (*_self_onRightClick) (SuiDesigner$AssetDirTreeView *  self, SuiCore$MouseEvent *  me);
	void  (*_dirItem_onEvent) (SuiDesigner$AssetDirTreeView *  self, SuiCore$Event *  e, SuiDesigner$FileItem*  fi);
};
Vtable_SuiDesigner$AssetDirTreeView* Vtable_SuiDesigner$AssetDirTreeView_init(Vtable_SuiDesigner$AssetDirTreeView* pvt);
void SuiDesigner$AssetDirTreeView_init_fields(SuiDesigner$AssetDirTreeView *self);
void SuiDesigner$AssetDirTreeView_init(SuiDesigner$AssetDirTreeView *self, void *pOwner);
SuiDesigner$AssetDirTreeView * SuiDesigner$AssetDirTreeView_new(void *pOwner);
void SuiDesigner$AssetDirTreeView_fini(SuiDesigner$AssetDirTreeView *self);

void  SuiDesigner$AssetDirTreeView$ctor(SuiDesigner$AssetDirTreeView *  self);
void  SuiDesigner$AssetDirTreeView$onListenerEvent(SuiDesigner$AssetDirTreeView *  self, SuiCore$Event *  event);
void  SuiDesigner$AssetDirTreeView$onMounted(SuiDesigner$AssetDirTreeView *  self);
void  SuiDesigner$AssetDirTreeView$onUnmounting(SuiDesigner$AssetDirTreeView *  self);
void  SuiDesigner$AssetDirTreeView$_routeMenuNativeItem(SuiDesigner$AssetDirTreeView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$FileItem*  fi);
void  SuiDesigner$AssetDirTreeView$_self_onRightClick(SuiDesigner$AssetDirTreeView *  self, SuiCore$MouseEvent *  me);
void  SuiDesigner$AssetDirTreeView$onEvent(SuiDesigner$AssetDirTreeView *  self, SuiCore$Event *  e);
void  SuiDesigner$AssetDirTreeView$_dirItem_onEvent(SuiDesigner$AssetDirTreeView *  self, SuiCore$Event *  e, SuiDesigner$FileItem*  fi);
void  SuiDesigner$AssetDirTreeView$react(SuiDesigner$AssetDirTreeView *  self);

void  SuiDesigner$testAsset();
SuiDesigner$AssetDirTreeView*  SuiDesigner$mkAssetDirTreeView(SuiDesigner$AssetDirTreeView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
