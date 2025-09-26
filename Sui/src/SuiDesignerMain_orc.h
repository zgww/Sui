
typedef struct tagMenuBarCtrl MenuBarCtrl;
typedef struct tagVtable_MenuBarCtrl Vtable_MenuBarCtrl;
typedef struct tagTmp Tmp;
typedef struct tagVtable_Tmp Vtable_Tmp;
typedef struct tagTmpListener TmpListener;
typedef struct tagVtable_TmpListener Vtable_TmpListener;
typedef struct tagTmpListener2 TmpListener2;
typedef struct tagVtable_TmpListener2 Vtable_TmpListener2;
typedef struct tagClickListener ClickListener;
typedef struct tagVtable_ClickListener Vtable_ClickListener;
typedef struct tagTmp3 Tmp3;
typedef struct tagVtable_Tmp3 Vtable_Tmp3;
typedef struct tagTmp2 Tmp2;
typedef struct tagVtable_Tmp2 Vtable_Tmp2;


#ifndef define_struct_____SuiDesignerMain_orc_h__
#define define_struct_____SuiDesignerMain_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE_____SuiDesignerMain_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./Orc/Orc.h"
#include "../UrgcDll/urgc_api.h"
#include "../include/miniaudio.h"




#ifdef INCLUDE_ONLY_TYPE_____SuiDesignerMain_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef ____SuiDesignerMain_orc_h__
#define ____SuiDesignerMain_orc_h__

//include  importHeadCode
#include "./Sui/View/Button_orc.h"
#include "./Sui/Core/Image_orc.h"
#include "./Sui/View/ImageView_orc.h"
#include "./Sui/View/TextView_orc.h"
#include "./Sui/View/ViewBuilder_orc.h"
#include "./Sui/Core/App_orc.h"
#include "./Sui/Core/Timer_orc.h"
#include "./Sui/Core/Window_orc.h"
#include "./Orc/Time_orc.h"
#include "./Orc/String_orc.h"
#include "./Orc/Path_orc.h"
#include "./Orc/List_orc.h"
#include "./Orc/Map_orc.h"
#include "./Orc/Math_orc.h"
#include "./Sui/Core/Node_orc.h"
#include "./Sui/Core/Emitter_orc.h"
#include "./Sui/Core/Event_orc.h"
#include "./Sui/Core/ViewBase_orc.h"
#include "./Sui/Core/Mouse_orc.h"
#include "./Sui/Core/MouseEvent_orc.h"
#include "./Sui/Core/View_orc.h"
#include "./Sui/Core/Rect_orc.h"
#include "./Sui/Core/Vec2_orc.h"
#include "./Sui/Core/Inset_orc.h"
#include "./Sui/Core/Frame_orc.h"
#include "./Sui/Dialog/MessageDialog_orc.h"
#include "./Sui/Layout/LayoutLinear_orc.h"
#include "./Sui/Layout/LayoutAlign_orc.h"
#include "./Sui/View/Checkbox_orc.h"
#include "./Sui/View/Switch_orc.h"
#include "./Sui/View/Slider_orc.h"
#include "./Sui/View/ProgressView_orc.h"
#include "./Sui/View/EditText_orc.h"
#include "./Sui/View/TableView_orc.h"
#include "./Sui/View/ScrollArea_orc.h"
#include "./Sui/View/ColorPalete_orc.h"
#include "./Sui/View/TreeView_orc.h"
#include "./Sui/View/MenuNative_orc.h"
#include "./Sui/View/Select_orc.h"
#include "./Sui/View/DockLayout_orc.h"
#include "./Sui/View/SystemTrayIcon_orc.h"
#include "./SuiDesigner/Asset/FileWatcher_orc.h"
#include "./SuiDesigner/Asset/AssetDirView_orc.h"
#include "./SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "./SuiDesigner/Serial/BiJson_orc.h"
#include "./SuiDesigner/SceneView_orc.h"
#include "./SuiDesigner/SceneHierView_orc.h"
#include "./SuiDesigner/Inspector_orc.h"
#include "./SuiDesigner/InspectorView_orc.h"
#include "./SuiDesigner/Theme_orc.h"
#include "./SuiDesigner/Project_orc.h"
#include "./SuiDesigner/UiAction_orc.h"
#include "./Json/Json_orc.h"
#include "./MainProject_orc.h"
#include "./SuiDesigner/EditCtx_orc.h"
#include "./SuiDesigner/SpriteSheetEditor_orc.h"
#include "./SuiDesigner/TileEditor_orc.h"
#include "./SuiDesigner/W3eEditor_orc.h"
#include "./SuiDesigner/SglEditor_orc.h"
#include "./SuiDesigner/MdxReader_orc.h"
#include "./SuiDesigner/Insp_orc.h"
#include "./Sgl/Material_orc.h"
#include "./Sgl/Buffer_orc.h"
#include "./Sgl/Geometry_orc.h"
#include "./Sgl/GeometryHeightMap_orc.h"
#include "./Sui/Core/TestMath_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern SuiView$DockLayout*  dockLayoutIns;

// 虚表
struct tagVtable_MenuBarCtrl {
	Vtable_Object super;
};
//虚表实例
extern Vtable_MenuBarCtrl _vtable_MenuBarCtrl;

// class refc:0
struct tagMenuBarCtrl {
	Object super; 
	Orc$String*  status ;
	SuiView$MenuButton*  curMenu ;
	SuiView$MenuButton*  nextMenu ;
	SuiView$MenuNative*  popup ;
	Sui$Window*  window ;
	void  (*showPopup) (MenuBarCtrl *  self, SuiView$MenuButton*  mbutton);
	void  (*onclick) (MenuBarCtrl *  self, SuiView$MenuButton*  mbutton, SuiCore$MouseEvent *  me);
	void  (*onmove) (MenuBarCtrl *  self, SuiView$MenuButton*  menu, SuiCore$MouseEvent *  me);
	void  (*setPopup) (MenuBarCtrl *  self, SuiView$MenuNative*  popup, SuiView$MenuButton*  curMenu);
	void  (*onPopupDismiss) (MenuBarCtrl *  self);
};
Vtable_MenuBarCtrl* Vtable_MenuBarCtrl_init(Vtable_MenuBarCtrl* pvt);
void MenuBarCtrl_init_fields(MenuBarCtrl *self);
void MenuBarCtrl_init(MenuBarCtrl *self, void *pOwner);
MenuBarCtrl * MenuBarCtrl_new(void *pOwner);
void MenuBarCtrl_fini(MenuBarCtrl *self);

void  MenuBarCtrl$dtor(MenuBarCtrl *  self);
void  MenuBarCtrl$showPopup(MenuBarCtrl *  self, SuiView$MenuButton*  mbutton);
void  MenuBarCtrl$onclick(MenuBarCtrl *  self, SuiView$MenuButton*  mbutton, SuiCore$MouseEvent *  me);
void  MenuBarCtrl$onmove(MenuBarCtrl *  self, SuiView$MenuButton*  menu, SuiCore$MouseEvent *  me);
void  MenuBarCtrl$setPopup(MenuBarCtrl *  self, SuiView$MenuNative*  popup, SuiView$MenuButton*  curMenu);
void  MenuBarCtrl$onPopupDismiss(MenuBarCtrl *  self);


// 虚表
struct tagVtable_Tmp {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Tmp _vtable_Tmp;

// class refc:1
struct tagTmp {
	Object super; 
	int  i ;
	int  j ;
	double  dv ;
};
Vtable_Tmp* Vtable_Tmp_init(Vtable_Tmp* pvt);
void Tmp_init_fields(Tmp *self);
void Tmp_init(Tmp *self, void *pOwner);
Tmp * Tmp_new(void *pOwner);
void Tmp_fini(Tmp *self);


void  testMeta();
void  testWindow2();

// 虚表
struct tagVtable_TmpListener {
	Vtable_SuiCore$Listener super;
};
//虚表实例
extern Vtable_TmpListener _vtable_TmpListener;

// class refc:1
struct tagTmpListener {
	SuiCore$Listener super; 
	
};
Vtable_TmpListener* Vtable_TmpListener_init(Vtable_TmpListener* pvt);
void TmpListener_init_fields(TmpListener *self);
void TmpListener_init(TmpListener *self, void *pOwner);
TmpListener * TmpListener_new(void *pOwner);
void TmpListener_fini(TmpListener *self);

void  TmpListener$onListenerEvent(TmpListener *  self, SuiCore$Event *  ev);


// 虚表
struct tagVtable_TmpListener2 {
	Vtable_SuiCore$Listener super;
};
//虚表实例
extern Vtable_TmpListener2 _vtable_TmpListener2;

// class refc:1
struct tagTmpListener2 {
	SuiCore$Listener super; 
	
};
Vtable_TmpListener2* Vtable_TmpListener2_init(Vtable_TmpListener2* pvt);
void TmpListener2_init_fields(TmpListener2 *self);
void TmpListener2_init(TmpListener2 *self, void *pOwner);
TmpListener2 * TmpListener2_new(void *pOwner);
void TmpListener2_fini(TmpListener2 *self);

void  TmpListener2$onListenerEvent(TmpListener2 *  self, SuiCore$Event *  ev);


// 虚表
struct tagVtable_ClickListener {
	Vtable_SuiCore$MouseEventListener super;
};
//虚表实例
extern Vtable_ClickListener _vtable_ClickListener;

// class refc:1
struct tagClickListener {
	SuiCore$MouseEventListener super; 
	
};
Vtable_ClickListener* Vtable_ClickListener_init(Vtable_ClickListener* pvt);
void ClickListener_init_fields(ClickListener *self);
void ClickListener_init(ClickListener *self, void *pOwner);
ClickListener * ClickListener_new(void *pOwner);
void ClickListener_fini(ClickListener *self);

void  ClickListener$onEvent(ClickListener *  self, SuiCore$MouseEvent *  ev);

void  show_newWindow(Sui$Window *  parent);
void  startSuiDesigner();
extern void  windowInit();

// 虚表
struct tagVtable_Tmp3 {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Tmp3 _vtable_Tmp3;

// class refc:1
struct tagTmp3 {
	Object super; 
	int  tmp ;
};
Vtable_Tmp3* Vtable_Tmp3_init(Vtable_Tmp3* pvt);
void Tmp3_init_fields(Tmp3 *self);
void Tmp3_init(Tmp3 *self, void *pOwner);
Tmp3 * Tmp3_new(void *pOwner);
void Tmp3_fini(Tmp3 *self);



// 虚表
struct tagVtable_Tmp2 {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Tmp2 _vtable_Tmp2;

// class refc:0
struct tagTmp2 {
	Object super; 
	int  a ;
	Tmp3*  tmp3 ;
	void  (*print) (Tmp2 *  self);
};
Vtable_Tmp2* Vtable_Tmp2_init(Vtable_Tmp2* pvt);
void Tmp2_init_fields(Tmp2 *self);
void Tmp2_init(Tmp2 *self, void *pOwner);
Tmp2 * Tmp2_new(void *pOwner);
void Tmp2_fini(Tmp2 *self);

void  Tmp2$print(Tmp2 *  self);
void  Tmp2$ctor(Tmp2 *  self);
void  Tmp2$dtor(Tmp2 *  self);

void  test_tmp2();
extern void  test_tgfx();
int  testAudio();
int  main();
void  testTransparency();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
