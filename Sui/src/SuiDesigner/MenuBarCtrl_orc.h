
typedef struct tagSuiDesigner$MenuBarCtrl SuiDesigner$MenuBarCtrl;
typedef struct tagVtable_SuiDesigner$MenuBarCtrl Vtable_SuiDesigner$MenuBarCtrl;


#ifndef define_struct___SuiDesigner__MenuBarCtrl_orc_h__
#define define_struct___SuiDesigner__MenuBarCtrl_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__MenuBarCtrl_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__MenuBarCtrl_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__MenuBarCtrl_orc_h__
#define __SuiDesigner__MenuBarCtrl_orc_h__

//include  importHeadCode
#include "../Sui/View/Button_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/Core/App_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Mouse_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Inset_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/View/Checkbox_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/Slider_orc.h"
#include "../Sui/View/ProgressView_orc.h"
#include "../Sui/View/TableView_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/ColorPalete_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/View/Select_orc.h"
#include "../Sui/View/DockLayout_orc.h"
#include "../Sui/View/SystemTrayIcon_orc.h"
#include "../SuiDesigner/Asset/FileWatcher_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/Serial/BiJson_orc.h"
#include "../SuiDesigner/SceneView_orc.h"
#include "../SuiDesigner/SceneHierView_orc.h"
#include "../SuiDesigner/Inspector_orc.h"
#include "../SuiDesigner/InspectorView_orc.h"
#include "../SuiDesigner/Theme_orc.h"
#include "../SuiDesigner/Project_orc.h"
#include "../SuiDesigner/UiAction_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$MenuBarCtrl {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$MenuBarCtrl _vtable_SuiDesigner$MenuBarCtrl;

// class refc:0
struct tagSuiDesigner$MenuBarCtrl {
	Object super; 
	Orc$String*  status ;
	SuiView$MenuButton*  curMenu ;
	SuiView$MenuButton*  nextMenu ;
	SuiView$MenuNative*  popup ;
	SuiView$MenuNativeItem*  (**cbCreateMenuNativeItem)(SuiView$MenuNativeItem **  __outRef__, void *  self, SuiView$MenuButton *  mbutton);
	void  (*showPopup) (SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  mbutton);
	void  (*onclick) (SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  mbutton, SuiCore$MouseEvent *  me);
	void  (*onmove) (SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  menu, SuiCore$MouseEvent *  me);
	void  (*setPopup) (SuiDesigner$MenuBarCtrl *  self, SuiView$MenuNative*  popup, SuiView$MenuButton*  curMenu);
	void  (*onPopupDismiss) (SuiDesigner$MenuBarCtrl *  self);
};
Vtable_SuiDesigner$MenuBarCtrl* Vtable_SuiDesigner$MenuBarCtrl_init(Vtable_SuiDesigner$MenuBarCtrl* pvt);
void SuiDesigner$MenuBarCtrl_init_fields(SuiDesigner$MenuBarCtrl *self);
void SuiDesigner$MenuBarCtrl_init(SuiDesigner$MenuBarCtrl *self, void *pOwner);
SuiDesigner$MenuBarCtrl * SuiDesigner$MenuBarCtrl_new(void *pOwner);
void SuiDesigner$MenuBarCtrl_fini(SuiDesigner$MenuBarCtrl *self);

void  SuiDesigner$MenuBarCtrl$dtor(SuiDesigner$MenuBarCtrl *  self);
void  SuiDesigner$MenuBarCtrl$showPopup(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  mbutton);
void  SuiDesigner$MenuBarCtrl$onclick(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  mbutton, SuiCore$MouseEvent *  me);
void  SuiDesigner$MenuBarCtrl$onmove(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  menu, SuiCore$MouseEvent *  me);
void  SuiDesigner$MenuBarCtrl$setPopup(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuNative*  popup, SuiView$MenuButton*  curMenu);
void  SuiDesigner$MenuBarCtrl$onPopupDismiss(SuiDesigner$MenuBarCtrl *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
