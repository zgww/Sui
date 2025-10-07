
typedef struct tagSuiDesigner$SelectFileItems SuiDesigner$SelectFileItems;
typedef struct tagVtable_SuiDesigner$SelectFileItems Vtable_SuiDesigner$SelectFileItems;
typedef struct tagSuiDesigner$AssetDirView SuiDesigner$AssetDirView;
typedef struct tagVtable_SuiDesigner$AssetDirView Vtable_SuiDesigner$AssetDirView;


#ifndef define_struct___SuiDesigner__AssetDirView_orc_h__
#define define_struct___SuiDesigner__AssetDirView_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__AssetDirView_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__AssetDirView_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__AssetDirView_orc_h__
#define __SuiDesigner__AssetDirView_orc_h__

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
#include "../../Sui/Dialog/Toast_orc.h"
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
#include "../Theme_orc.h"
#include "../Project_orc.h"
#include "../EventANodeChanged_orc.h"
#include "../EventFileItemChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$SelectFileItems {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SelectFileItems _vtable_SuiDesigner$SelectFileItems;

// class refc:0
struct tagSuiDesigner$SelectFileItems {
	Object super; 
	Orc$List*  list ;
	Orc$List*  (**getAll)(Orc$List **  __outRef__, void *  self);
	void  (**onChanged)(void *  self);
	void  (*select) (SuiDesigner$SelectFileItems *  self, SuiDesigner$FileItem*  fi);
	void  (*fire_onChanged) (SuiDesigner$SelectFileItems *  self);
	void  (*selectMulti) (SuiDesigner$SelectFileItems *  self, SuiDesigner$FileItem*  fi, bool  ctrl, bool  shift);
};
Vtable_SuiDesigner$SelectFileItems* Vtable_SuiDesigner$SelectFileItems_init(Vtable_SuiDesigner$SelectFileItems* pvt);
void SuiDesigner$SelectFileItems_init_fields(SuiDesigner$SelectFileItems *self);
void SuiDesigner$SelectFileItems_init(SuiDesigner$SelectFileItems *self, void *pOwner);
SuiDesigner$SelectFileItems * SuiDesigner$SelectFileItems_new(void *pOwner);
void SuiDesigner$SelectFileItems_fini(SuiDesigner$SelectFileItems *self);

void  SuiDesigner$SelectFileItems$select(SuiDesigner$SelectFileItems *  self, SuiDesigner$FileItem*  fi);
void  SuiDesigner$SelectFileItems$fire_onChanged(SuiDesigner$SelectFileItems *  self);
void  SuiDesigner$SelectFileItems$selectMulti(SuiDesigner$SelectFileItems *  self, SuiDesigner$FileItem*  fi, bool  ctrl, bool  shift);

extern SuiDesigner$AssetDirView*  SuiDesigner$curAssetDirView;

// 虚表
struct tagVtable_SuiDesigner$AssetDirView {
	Vtable_SuiLayout$LayoutLinear super;
};
//虚表实例
extern Vtable_SuiDesigner$AssetDirView _vtable_SuiDesigner$AssetDirView;

// class refc:0
struct tagSuiDesigner$AssetDirView {
	SuiLayout$LayoutLinear super; 
	Orc$List*  activeFileItems ;
	SuiDesigner$FileItem*  parentFileItem ;
	SuiDesigner$SelectFileItems*  selectFileItems ;
	SuiDesigner$FileItem *  (*getCurrentDirFileItem) (SuiDesigner$AssetDirView *  self);
	void  (*_openDirectory) (SuiDesigner$AssetDirView *  self, SuiDesigner$FileItem*  fi);
	void  (*_routeMenuNativeItem) (SuiDesigner$AssetDirView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$FileItem*  fi);
	void  (*_self_onRightClick) (SuiDesigner$AssetDirView *  self, SuiCore$MouseEvent *  me);
	void  (*_fileItem_onEvent) (SuiDesigner$AssetDirView *  self, SuiCore$Event *  e, SuiDesigner$FileItem*  fi);
	void  (*reactFileItem) (SuiDesigner$AssetDirView *  self, SuiCore$Node *  o, SuiDesigner$FileItem*  fi);
};
Vtable_SuiDesigner$AssetDirView* Vtable_SuiDesigner$AssetDirView_init(Vtable_SuiDesigner$AssetDirView* pvt);
void SuiDesigner$AssetDirView_init_fields(SuiDesigner$AssetDirView *self);
void SuiDesigner$AssetDirView_init(SuiDesigner$AssetDirView *self, void *pOwner);
SuiDesigner$AssetDirView * SuiDesigner$AssetDirView_new(void *pOwner);
void SuiDesigner$AssetDirView_fini(SuiDesigner$AssetDirView *self);

void  SuiDesigner$AssetDirView$ctor(SuiDesigner$AssetDirView *  self);
SuiDesigner$FileItem *  SuiDesigner$AssetDirView$getCurrentDirFileItem(SuiDesigner$AssetDirView *  self);
void  SuiDesigner$AssetDirView$onListenerEvent(SuiDesigner$AssetDirView *  self, SuiCore$Event *  event);
void  SuiDesigner$AssetDirView$onMounted(SuiDesigner$AssetDirView *  self);
void  SuiDesigner$AssetDirView$onUnmounting(SuiDesigner$AssetDirView *  self);
void  SuiDesigner$AssetDirView$react(SuiDesigner$AssetDirView *  self);
void  SuiDesigner$AssetDirView$_openDirectory(SuiDesigner$AssetDirView *  self, SuiDesigner$FileItem*  fi);
void  SuiDesigner$AssetDirView$_routeMenuNativeItem(SuiDesigner$AssetDirView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$FileItem*  fi);
void  SuiDesigner$AssetDirView$_self_onRightClick(SuiDesigner$AssetDirView *  self, SuiCore$MouseEvent *  me);
void  SuiDesigner$AssetDirView$onEvent(SuiDesigner$AssetDirView *  self, SuiCore$Event *  e);
void  SuiDesigner$AssetDirView$_fileItem_onEvent(SuiDesigner$AssetDirView *  self, SuiCore$Event *  e, SuiDesigner$FileItem*  fi);
void  SuiDesigner$AssetDirView$reactFileItem(SuiDesigner$AssetDirView *  self, SuiCore$Node *  o, SuiDesigner$FileItem*  fi);

SuiDesigner$AssetDirView*  SuiDesigner$mkAssetDirView(SuiDesigner$AssetDirView **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
