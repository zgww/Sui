
#include "SuiDesignerMain_orc.h" 

#include <stdio.h>
#include "./Orc/Orc.h"
#include "../UrgcDll/urgc_api.h"
#include "../include/miniaudio.h"
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
#include "./HoroEditor/HoroEditor_orc.h"


// static struct 
typedef struct tag__Block_92_39 __Block_92_39;

typedef struct tag__Block_141_43 __Block_141_43;

typedef struct tag__Block_431_35 __Block_431_35;

typedef struct tag__Block_442_43 __Block_442_43;

typedef struct tag__Block_385_23 __Block_385_23;

typedef struct tag__Block_1139_16 __Block_1139_16;

typedef struct tag__Closure_onActive_98 __Closure_onActive_98;

typedef struct tag__Closure_222_28 __Closure_222_28;

typedef struct tag__Closure_446_44 __Closure_446_44;

typedef struct tag__Closure_450_39 __Closure_450_39;

typedef struct tag__Closure_481_39 __Closure_481_39;

typedef struct tag__Closure_523_49 __Closure_523_49;

typedef struct tag__Closure_556_52 __Closure_556_52;

typedef struct tag__Closure_say_1141 __Closure_say_1141;



struct tag__Block_92_39 {
	MenuBarCtrl*  self ;
};





struct tag__Block_141_43 {
	SuiView$MenuNativeItem*  o ;
};





struct tag__Block_431_35 {
	MenuBarCtrl*  group ;
};





struct tag__Block_442_43 {
	SuiView$MenuButton*  mbutton ;
};





struct tag__Block_385_23 {
	SuiDesigner$Theme *  t ;
};





struct tag__Block_1139_16 {
	Tmp2*  a ;
};





struct tag__Closure_onActive_98 {
	void  (*invoke)(__Closure_onActive_98 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	__Block_92_39*  __var___Block_92_39 ;
};





struct tag__Closure_222_28 {
	void  (*invoke)(__Closure_222_28 *  self);
	Vtable_Object *  vtable ;
	__Block_92_39*  __var___Block_92_39 ;
	__Block_141_43*  __var___Block_141_43 ;
};





struct tag__Closure_446_44 {
	void  (*invoke)(__Closure_446_44 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	__Block_431_35*  __var___Block_431_35 ;
	__Block_442_43*  __var___Block_442_43 ;
};





struct tag__Closure_450_39 {
	void  (*invoke)(__Closure_450_39 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	__Block_431_35*  __var___Block_431_35 ;
	__Block_442_43*  __var___Block_442_43 ;
};





struct tag__Closure_481_39 {
	void  (*invoke)(__Closure_481_39 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tag__Closure_523_49 {
	void  (*invoke)(__Closure_523_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
	Vtable_Object *  vtable ;
	__Block_385_23*  __var___Block_385_23 ;
};





struct tag__Closure_556_52 {
	SuiCore$ViewBase *  (*invoke)(__Closure_556_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
	Vtable_Object *  vtable ;
	__Block_385_23*  __var___Block_385_23 ;
};





struct tag__Closure_say_1141 {
	void  (*invoke)(__Closure_say_1141 *  self);
	Vtable_Object *  vtable ;
	__Block_1139_16*  __var___Block_1139_16 ;
};





// static function declaration
static void  __finiBlock___Block_92_39(__Block_92_39 *  self);
static void  __finiBlock___Block_141_43(__Block_141_43 *  self);
static void  __finiBlock___Block_431_35(__Block_431_35 *  self);
static void  __finiBlock___Block_442_43(__Block_442_43 *  self);
static void  __finiBlock___Block_385_23(__Block_385_23 *  self);
static void  __finiBlock___Block_1139_16(__Block_1139_16 *  self);
static void  __fn___Closure_onActive_98(__Closure_onActive_98 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_98(__Closure_onActive_98 *  self);
static __Closure_onActive_98*  __make___Closure_onActive_98(__Closure_onActive_98 **  __outRef__, __Block_92_39 *  __var___Block_92_39);
static void  __fn___Closure_222_28(__Closure_222_28 *  self);
static void  __fini___Closure_222_28(__Closure_222_28 *  self);
static __Closure_222_28*  __make___Closure_222_28(__Closure_222_28 **  __outRef__, __Block_92_39 *  __var___Block_92_39, __Block_141_43 *  __var___Block_141_43);
static void  __fn___Closure_446_44(__Closure_446_44 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_446_44(__Closure_446_44 *  self);
static __Closure_446_44*  __make___Closure_446_44(__Closure_446_44 **  __outRef__, __Block_431_35 *  __var___Block_431_35, __Block_442_43 *  __var___Block_442_43);
static void  __fn___Closure_450_39(__Closure_450_39 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_450_39(__Closure_450_39 *  self);
static __Closure_450_39*  __make___Closure_450_39(__Closure_450_39 **  __outRef__, __Block_431_35 *  __var___Block_431_35, __Block_442_43 *  __var___Block_442_43);
static void  __fn___Closure_481_39(__Closure_481_39 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_481_39(__Closure_481_39 *  self);
static __Closure_481_39*  __make___Closure_481_39(__Closure_481_39 **  __outRef__);
static void  __fn___Closure_523_49(__Closure_523_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
static void  __fini___Closure_523_49(__Closure_523_49 *  self);
static __Closure_523_49*  __make___Closure_523_49(__Closure_523_49 **  __outRef__, __Block_385_23 *  __var___Block_385_23);
static SuiCore$ViewBase *  __fn___Closure_556_52(__Closure_556_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
static void  __fini___Closure_556_52(__Closure_556_52 *  self);
static __Closure_556_52*  __make___Closure_556_52(__Closure_556_52 **  __outRef__, __Block_385_23 *  __var___Block_385_23);
static void  __fn___Closure_say_1141(__Closure_say_1141 *  self);
static void  __fini___Closure_say_1141(__Closure_say_1141 *  self);
static __Closure_say_1141*  __make___Closure_say_1141(__Closure_say_1141 **  __outRef__, __Block_1139_16 *  __var___Block_1139_16);


URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  dockLayoutIns = NULL;

//vtable instance
Vtable_MenuBarCtrl _vtable_MenuBarCtrl;

// init meta

void MenuBarCtrl_initMeta(Vtable_MenuBarCtrl *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "status", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(MenuBarCtrl, status), true, false, 1);
	orc_metaField_class(&pNext, "curMenu", ((Vtable_Object*)Vtable_SuiView$MenuButton_init(0)), offsetof(MenuBarCtrl, curMenu), true, false, 1);
	orc_metaField_class(&pNext, "nextMenu", ((Vtable_Object*)Vtable_SuiView$MenuButton_init(0)), offsetof(MenuBarCtrl, nextMenu), true, false, 1);
	orc_metaField_class(&pNext, "popup", ((Vtable_Object*)Vtable_SuiView$MenuNative_init(0)), offsetof(MenuBarCtrl, popup), true, false, 1);
	orc_metaField_class(&pNext, "window", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(MenuBarCtrl, window), true, false, 1);

	orc_metaField_method(&pNext, "showPopup", offsetof(MenuBarCtrl, showPopup));
	orc_metaField_method(&pNext, "onclick", offsetof(MenuBarCtrl, onclick));
	orc_metaField_method(&pNext, "onmove", offsetof(MenuBarCtrl, onmove));
	orc_metaField_method(&pNext, "setPopup", offsetof(MenuBarCtrl, setPopup));
	orc_metaField_method(&pNext, "onPopupDismiss", offsetof(MenuBarCtrl, onPopupDismiss));
}


// vtable init


Vtable_MenuBarCtrl* Vtable_MenuBarCtrl_init(Vtable_MenuBarCtrl* pvt){
    if (pvt == NULL){
        pvt = &_vtable_MenuBarCtrl;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&MenuBarCtrl_new;
    ((Vtable_Object*)pvt)->className = "MenuBarCtrl";

    ((Vtable_Object*)pvt)->initMeta = (void*)MenuBarCtrl_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void MenuBarCtrl_fini(MenuBarCtrl *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void MenuBarCtrl_init_fields(MenuBarCtrl *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)MenuBarCtrl_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((MenuBarCtrl*)self)->status, Orc$str(&tmpReturn_1, "idle") );
	urgc_set_field_class(self, (void**)&((MenuBarCtrl*)self)->curMenu, NULL);
	urgc_set_field_class(self, (void**)&((MenuBarCtrl*)self)->nextMenu, NULL);
	urgc_set_field_class(self, (void**)&((MenuBarCtrl*)self)->popup, NULL);
	urgc_set_field_class(self, (void**)&((MenuBarCtrl*)self)->window, NULL);
    }
	((Object*)self)->dtor = (void*)MenuBarCtrl$dtor;
	((MenuBarCtrl*)self)->showPopup = (void*)MenuBarCtrl$showPopup;
	((MenuBarCtrl*)self)->onclick = (void*)MenuBarCtrl$onclick;
	((MenuBarCtrl*)self)->onmove = (void*)MenuBarCtrl$onmove;
	((MenuBarCtrl*)self)->setPopup = (void*)MenuBarCtrl$setPopup;
	((MenuBarCtrl*)self)->onPopupDismiss = (void*)MenuBarCtrl$onPopupDismiss;
}

// init function

void MenuBarCtrl_init(MenuBarCtrl *self, void *pOwner){
    Vtable_MenuBarCtrl_init(&_vtable_MenuBarCtrl);

    ((Object*)self)->vtable = (void*)&_vtable_MenuBarCtrl;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    MenuBarCtrl_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
MenuBarCtrl * MenuBarCtrl_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    MenuBarCtrl *self = calloc(1, sizeof(MenuBarCtrl));
	
    MenuBarCtrl_init(self, pOwner);
    return self;
}


// class members
void  MenuBarCtrl$dtor(MenuBarCtrl *  self){
	printf("~MenuBarCtrl\n") ;
}


void  MenuBarCtrl$showPopup(MenuBarCtrl *  self, SuiView$MenuButton*  mbutton){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(mbutton);

	URGC_VAR_CLEANUP __Block_92_39*  __var___Block_92_39 = (__var___Block_92_39=NULL,urgc_init_var((void**)&__var___Block_92_39, orc_alloc_and_set_deleter(sizeof(__Block_92_39) , __finiBlock___Block_92_39) ));
	urgc_set_field_class(__var___Block_92_39, (void * )offsetof(__Block_92_39, self) , self) ;
	printf("set Trigging:%p\n", mbutton) ;
	urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, curMenu) , mbutton) ;
	urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, nextMenu) , NULL) ;
	URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
	URGC_VAR_CLEANUP __Closure_onActive_98*  tmpReturn_1 = NULL;
	(urgc_set_var(&onActive, __make___Closure_onActive_98(&tmpReturn_1, __var___Block_92_39) ) );
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
	{
		SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, NULL, NULL) ;
		
	
		URGC_VAR_CLEANUP __Block_141_43*  __var___Block_141_43 = (__var___Block_141_43=NULL,urgc_init_var((void**)&__var___Block_141_43, orc_alloc_and_set_deleter(sizeof(__Block_141_43) , __finiBlock___Block_141_43) ));
		urgc_set_field_class(__var___Block_141_43, (void * )offsetof(__Block_141_43, o) , o) ;
		if (Orc$String$equals(mbutton->text, "文件") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_3, __var___Block_141_43->o, Orc$str(&tmpReturn_4, "新建场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_5 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_5, __var___Block_141_43->o, Orc$str(&tmpReturn_6, "打开场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_7 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_7, __var___Block_141_43->o, Orc$str(&tmpReturn_8, "保存场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_9, __var___Block_141_43->o, Orc$str(&tmpReturn_10, "最近打开") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_11 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
				SuiView$mkMenuNativeItem(&tmpReturn_11, o, Orc$str(&tmpReturn_12, "场景1") , onActive) ;
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_13 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
				SuiView$mkMenuNativeItem(&tmpReturn_13, o, Orc$str(&tmpReturn_14, "场景2") , onActive) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_15 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_15, __var___Block_141_43->o, Orc$str(&tmpReturn_16, "另存为场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_17 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_17, __var___Block_141_43->o, Orc$str(&tmpReturn_18, "保存所有场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_19 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_19, __var___Block_141_43->o, Orc$str(&tmpReturn_20, "关闭场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_21 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_21, __var___Block_141_43->o, Orc$str(&tmpReturn_22, "重载已保存的场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_23 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_23, __var___Block_141_43->o, Orc$str(&tmpReturn_24, "设置") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_25 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_25, __var___Block_141_43->o, Orc$str(&tmpReturn_26, "退出") , onActive) ;
		}
		else if (Orc$String$equals(mbutton->text, "项目") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_27 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_27, __var___Block_141_43->o, Orc$str(&tmpReturn_28, "退出到项目列表") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_29 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_29, __var___Block_141_43->o, Orc$str(&tmpReturn_30, "重新加载当前项目") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_31 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_32 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_31, __var___Block_141_43->o, Orc$str(&tmpReturn_32, "项目设置") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_33 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_34 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_33, __var___Block_141_43->o, Orc$str(&tmpReturn_34, "导出") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_35 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_36 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_35, __var___Block_141_43->o, Orc$str(&tmpReturn_36, "工具-孤立资源浏览器") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_37 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_38 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_37, __var___Block_141_43->o, Orc$str(&tmpReturn_38, "打开用户数据目录") , onActive) ;
		}
		else if (Orc$String$equals(mbutton->text, "帮助") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_39 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_40 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_39, __var___Block_141_43->o, Orc$str(&tmpReturn_40, "在线文档") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_41 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_42 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_41, __var___Block_141_43->o, Orc$str(&tmpReturn_42, "社区") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_43 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_44 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_43, __var___Block_141_43->o, Orc$str(&tmpReturn_44, "问与答") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_45 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_46 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_45, __var___Block_141_43->o, Orc$str(&tmpReturn_46, "搜索帮助") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_47 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_48 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_47, __var___Block_141_43->o, Orc$str(&tmpReturn_48, "报告问题") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_49 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_50 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_49, __var___Block_141_43->o, Orc$str(&tmpReturn_50, "支持Sui开发") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_51 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_52 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_51, __var___Block_141_43->o, Orc$str(&tmpReturn_52, "关于Sui") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_53 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_54 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_53, __var___Block_141_43->o, Orc$str(&tmpReturn_54, "关于OrcLang") , onActive) ;
		}
		else if (Orc$String$equals(mbutton->text, "调试") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_55 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_56 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_55, __var___Block_141_43->o, Orc$str(&tmpReturn_56, "运行预览") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_57 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_58 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_57, __var___Block_141_43->o, Orc$str(&tmpReturn_58, "使用远程调试器") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_59 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_60 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_59, __var___Block_141_43->o, Orc$str(&tmpReturn_60, "显示网格") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_61 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_62 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_61, __var___Block_141_43->o, Orc$str(&tmpReturn_62, "显示路径") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_63 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_64 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_63, __var___Block_141_43->o, Orc$str(&tmpReturn_64, "显示避障") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_65 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_66 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_65, __var___Block_141_43->o, Orc$str(&tmpReturn_66, "显示碰撞区域") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_67 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_68 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_67, __var___Block_141_43->o, Orc$str(&tmpReturn_68, "附加到进程") , onActive) ;
		}
		else if (Orc$String$equals(mbutton->text, "窗口") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_69 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_70 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_69, __var___Block_141_43->o, Orc$str(&tmpReturn_70, "NewWindow") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_71 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_72 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_71, __var___Block_141_43->o, Orc$str(&tmpReturn_72, "MaxWindow") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_73 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_74 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_73, __var___Block_141_43->o, Orc$str(&tmpReturn_74, "重置布局") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_75 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_76 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_75, __var___Block_141_43->o, Orc$str(&tmpReturn_76, "保存布局") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_77 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_78 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_77, __var___Block_141_43->o, Orc$str(&tmpReturn_78, "加载布局") , onActive) ;
		}
		else if (Orc$String$equals(mbutton->text, "视图") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_79 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_80 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_79, __var___Block_141_43->o, Orc$str(&tmpReturn_80, "Node") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_81 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_81, "AddView_Node") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_82 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_83 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_82, __var___Block_141_43->o, Orc$str(&tmpReturn_83, "ViewBase") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_84 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_85 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_84, __var___Block_141_43->o, Orc$str(&tmpReturn_85, "View") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_86 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_87 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_86, __var___Block_141_43->o, Orc$str(&tmpReturn_87, "Button") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_88 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_89 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_88, __var___Block_141_43->o, Orc$str(&tmpReturn_89, "Slider") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_90 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_91 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_90, __var___Block_141_43->o, Orc$str(&tmpReturn_91, "Switch") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_92 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_93 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_92, __var___Block_141_43->o, Orc$str(&tmpReturn_93, "ImageView") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_94 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_95 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_94, __var___Block_141_43->o, Orc$str(&tmpReturn_95, "TextView") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_96 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_97 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_96, __var___Block_141_43->o, Orc$str(&tmpReturn_97, "EditText") , onActive) ;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_98 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_99 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_98, __var___Block_141_43->o, Orc$str(&tmpReturn_99, "ListView") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_100 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_101 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_202_20 = SuiView$mkMenuNativeItem(&tmpReturn_100, o, Orc$str(&tmpReturn_101, "TreeView") , onActive) , *o = __scopeVar_202_20;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_102 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_103 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_203_20 = SuiView$mkMenuNativeItem(&tmpReturn_102, o, Orc$str(&tmpReturn_103, "TableView") , onActive) , *o = __scopeVar_203_20;
					
				
					
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_104 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_105 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_104, __var___Block_141_43->o, Orc$str(&tmpReturn_105, "ProgressView") , onActive) ;
				
			
				
			}
		}
		else {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_106 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_107 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_106, __var___Block_141_43->o, Orc$str(&tmpReturn_107, "About") , onActive) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
		urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, popup) , n) ;
		URGC_VAR_CLEANUP __Closure_222_28*  tmpReturn_108 = NULL;
		urgc_set_field(n, (void * )offsetof(SuiView$MenuNative, cbOnDismiss) , __make___Closure_222_28(&tmpReturn_108, __var___Block_92_39, __var___Block_141_43) ) ;
		n->create(n, __var___Block_141_43->o) ;
		SuiCore$Rect r = ((SuiCore$ViewBase * )mbutton)->get_abs_rect(mbutton) ;
		n->showAt(n, r.x, SuiCore$Rect$bottom(&r) ) ;
	}
}


void  MenuBarCtrl$onclick(MenuBarCtrl *  self, SuiView$MenuButton*  mbutton, SuiCore$MouseEvent *  me){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(mbutton);

	self->showPopup(self, mbutton) ;
}


void  MenuBarCtrl$onmove(MenuBarCtrl *  self, SuiView$MenuButton*  menu, SuiCore$MouseEvent *  me){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(menu);

	if (!self->popup) {
		return ; 
	}
	if (!self->curMenu) {
		return ; 
	}
	if (menu == self->curMenu) {
		return ; 
	}
	if (self->popup) {
		printf("destroy popup:%p, %p\n", self->popup, self->curMenu) ;
		if (self->curMenu) {
			((SuiCore$ViewBase * )self->curMenu)->hover = false;
			((SuiCore$Node * )self->curMenu)->react(self->curMenu) ;
		}
		self->popup->destroy(self->popup) ;
		urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, popup) , NULL) ;
		urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, curMenu) , NULL) ;
	}
	if (menu && self->curMenu == NULL) {
		((SuiCore$ViewBase * )menu)->hover = true;
		((SuiCore$Node * )menu)->react(menu) ;
		urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, nextMenu) , menu) ;
		printf("menu.onClick\n") ;
	}
}


void  MenuBarCtrl$setPopup(MenuBarCtrl *  self, SuiView$MenuNative*  popup, SuiView$MenuButton*  curMenu){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(popup);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(curMenu);

	printf("setPopup:%p, %p\n", popup, curMenu) ;
	urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, curMenu) , curMenu) ;
	urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, popup) , popup) ;
}


void  MenuBarCtrl$onPopupDismiss(MenuBarCtrl *  self){
	printf("onPopupDismiss:%p next:%p\n", self->popup, self->nextMenu) ;
	if (self->nextMenu) {
		URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  m = (m=NULL,urgc_init_var_class((void**)&m, self->nextMenu));
		urgc_set_field_class(self, (void * )offsetof(MenuBarCtrl, nextMenu) , NULL) ;
		self->showPopup(self, m) ;
	}
}




//vtable instance
Vtable_Tmp _vtable_Tmp;

// init meta

void Tmp_initMeta(Vtable_Tmp *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "i", OrcMetaType_int, offsetof(Tmp, i), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "j", OrcMetaType_int, offsetof(Tmp, j), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dv", OrcMetaType_double, offsetof(Tmp, dv), 0, 0, 0, 0);//double

	
}


// vtable init


Vtable_Tmp* Vtable_Tmp_init(Vtable_Tmp* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Tmp;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Tmp_new;
    ((Vtable_Object*)pvt)->className = "Tmp";

    ((Vtable_Object*)pvt)->initMeta = (void*)Tmp_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Tmp_fini(Tmp *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Tmp_init_fields(Tmp *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Tmp_fini;
	//fields
    {
	((Tmp*)self)->i = 0;
	((Tmp*)self)->j = 123;
	((Tmp*)self)->dv = 123.03;
    }
	
}

// init function

void Tmp_init(Tmp *self, void *pOwner){
    Vtable_Tmp_init(&_vtable_Tmp);

    ((Object*)self)->vtable = (void*)&_vtable_Tmp;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Tmp_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Tmp * Tmp_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Tmp *self = calloc(1, sizeof(Tmp));
	
    Tmp_init(self, pOwner);
    return self;
}


// class members

void  testMeta(){
	URGC_VAR_CLEANUP_CLASS Tmp*  tmp = (tmp=NULL,urgc_init_var_class((void**)&tmp, Tmp_new(&tmp) ));
	OrcMetaField *  f = orc_getMetaField(Vtable_Tmp_init(NULL), "dv") ;
	double *  pdouble = ((char * )tmp) + OrcMetaField_getAddress(f) ;
	*pdouble = 23.2;
	printf("get mf :%p dv:%f %f\n", f, tmp->dv, *pdouble) ;
}

void  testWindow2(){
	printf("TestWindow from orc\n") ;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	long long  ms = Orc$Time_unixMs() ;
	printf("now ms:%lld\n", ms) ;
	Orc$Time_sleepMs(1000 * 2) ;
	{
		long long  ms = Orc$Time_unixMs() ;
		printf("now ms:%lld\n", ms) ;
	}
	printf("done\n") ;
}


//vtable instance
Vtable_TmpListener _vtable_TmpListener;

// init meta

void TmpListener_initMeta(Vtable_TmpListener *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_TmpListener* Vtable_TmpListener_init(Vtable_TmpListener* pvt){
    if (pvt == NULL){
        pvt = &_vtable_TmpListener;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Listener_init(&_vtable_SuiCore$Listener);

	// init by super vtable init function
    Vtable_SuiCore$Listener_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Listener;
    ((Vtable_Object*)pvt)->make = (void*)&TmpListener_new;
    ((Vtable_Object*)pvt)->className = "TmpListener";

    ((Vtable_Object*)pvt)->initMeta = (void*)TmpListener_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void TmpListener_fini(TmpListener *self){
	//super fini
    SuiCore$Listener_fini((SuiCore$Listener *)self);

    //字段释放


}

// init fields function


void TmpListener_init_fields(TmpListener *self){
	//super class
    SuiCore$Listener_init_fields((SuiCore$Listener*)self);

    ((Object*)self)->fini = (void*)TmpListener_fini;
	//fields
    {
	
    }
	((SuiCore$Listener*)self)->onListenerEvent = (void*)TmpListener$onListenerEvent;
}

// init function

void TmpListener_init(TmpListener *self, void *pOwner){
    Vtable_TmpListener_init(&_vtable_TmpListener);

    ((Object*)self)->vtable = (void*)&_vtable_TmpListener;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    TmpListener_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
TmpListener * TmpListener_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    TmpListener *self = calloc(1, sizeof(TmpListener));
	
    TmpListener_init(self, pOwner);
    return self;
}


// class members
void  TmpListener$onListenerEvent(TmpListener *  self, SuiCore$Event *  ev){
	const char *  className = Object_getClassName(ev) ;
	printf("监听到事件:%s\n", className) ;
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("\t鼠标事件:%s\n", me->toString(&tmpReturn_1, me) ->str) ;
		if (me->isClickInBubble(me) ) {
			SuiDialog$MessageDialog_alert("你1点击了我", "标题") ;
			((SuiCore$Event * )me)->stopPropagation(me) ;
		}
	}
}




//vtable instance
Vtable_TmpListener2 _vtable_TmpListener2;

// init meta

void TmpListener2_initMeta(Vtable_TmpListener2 *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_TmpListener2* Vtable_TmpListener2_init(Vtable_TmpListener2* pvt){
    if (pvt == NULL){
        pvt = &_vtable_TmpListener2;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Listener_init(&_vtable_SuiCore$Listener);

	// init by super vtable init function
    Vtable_SuiCore$Listener_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Listener;
    ((Vtable_Object*)pvt)->make = (void*)&TmpListener2_new;
    ((Vtable_Object*)pvt)->className = "TmpListener2";

    ((Vtable_Object*)pvt)->initMeta = (void*)TmpListener2_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void TmpListener2_fini(TmpListener2 *self){
	//super fini
    SuiCore$Listener_fini((SuiCore$Listener *)self);

    //字段释放


}

// init fields function


void TmpListener2_init_fields(TmpListener2 *self){
	//super class
    SuiCore$Listener_init_fields((SuiCore$Listener*)self);

    ((Object*)self)->fini = (void*)TmpListener2_fini;
	//fields
    {
	
    }
	((SuiCore$Listener*)self)->onListenerEvent = (void*)TmpListener2$onListenerEvent;
}

// init function

void TmpListener2_init(TmpListener2 *self, void *pOwner){
    Vtable_TmpListener2_init(&_vtable_TmpListener2);

    ((Object*)self)->vtable = (void*)&_vtable_TmpListener2;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    TmpListener2_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
TmpListener2 * TmpListener2_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    TmpListener2 *self = calloc(1, sizeof(TmpListener2));
	
    TmpListener2_init(self, pOwner);
    return self;
}


// class members
void  TmpListener2$onListenerEvent(TmpListener2 *  self, SuiCore$Event *  ev){
	printf("监听到事件2:%s\n", Object_getClassName(ev) ) ;
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("\t鼠标事件2:%s\n", me->toString(&tmpReturn_1, me) ->str) ;
		if (me->isClickInBubble(me) ) {
			SuiDialog$MessageDialog_alert("你2点击了我", "标题") ;
			((SuiCore$Event * )me)->stopPropagation(me) ;
		}
	}
}




//vtable instance
Vtable_ClickListener _vtable_ClickListener;

// init meta

void ClickListener_initMeta(Vtable_ClickListener *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_ClickListener* Vtable_ClickListener_init(Vtable_ClickListener* pvt){
    if (pvt == NULL){
        pvt = &_vtable_ClickListener;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$MouseEventListener_init(&_vtable_SuiCore$MouseEventListener);

	// init by super vtable init function
    Vtable_SuiCore$MouseEventListener_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$MouseEventListener;
    ((Vtable_Object*)pvt)->make = (void*)&ClickListener_new;
    ((Vtable_Object*)pvt)->className = "ClickListener";

    ((Vtable_Object*)pvt)->initMeta = (void*)ClickListener_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void ClickListener_fini(ClickListener *self){
	//super fini
    SuiCore$MouseEventListener_fini((SuiCore$MouseEventListener *)self);

    //字段释放


}

// init fields function


void ClickListener_init_fields(ClickListener *self){
	//super class
    SuiCore$MouseEventListener_init_fields((SuiCore$MouseEventListener*)self);

    ((Object*)self)->fini = (void*)ClickListener_fini;
	//fields
    {
	
    }
	((SuiCore$MouseEventListener*)self)->onEvent = (void*)ClickListener$onEvent;
}

// init function

void ClickListener_init(ClickListener *self, void *pOwner){
    Vtable_ClickListener_init(&_vtable_ClickListener);

    ((Object*)self)->vtable = (void*)&_vtable_ClickListener;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    ClickListener_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
ClickListener * ClickListener_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    ClickListener *self = calloc(1, sizeof(ClickListener));
	
    ClickListener_init(self, pOwner);
    return self;
}


// class members
void  ClickListener$onEvent(ClickListener *  self, SuiCore$MouseEvent *  ev){
	if (ev->isClickInBubble(ev) ) {
		((SuiCore$Event * )ev)->stopPropagation(ev) ;
		printf("按钮点击事件 capture:%d\n", ((SuiCore$ViewEvent * )ev)->isCapture) ;
		SuiDialog$MessageDialog_alert("点击了按钮。你2点击了我", "标题") ;
	}
}



void  show_newWindow(Sui$Window *  parent){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	win->setSize(win, 300, 300) ;
	{
		Sui$Window*  o = win;
		
	
		{
			SuiCore$ViewBase*  o = win->rootView;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_361_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$str(&tmpReturn_1, "rootDiv") ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_363_12 = SuiLayout$layoutLinear(&tmpReturn_2, o, 0) , *o = __scopeVar_363_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_363_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
				{
					SuiView$TextView*  __scopeVar_364_16 = SuiView$mkTextView(&tmpReturn_3, o, 0) , *o = __scopeVar_364_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_364_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Inset$setAll(&((SuiCore$View * )o)->margin, 10) ;
					((SuiCore$View * )o)->backgroundColor = 0xffeecccc;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
					o->setText(o, Orc$str(&tmpReturn_4, "hello world2") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_5 = NULL;
				{
					SuiView$TextView*  __scopeVar_369_16 = SuiView$mkTextView(&tmpReturn_5, o, 0) , *o = __scopeVar_369_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_369_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Inset$setAll(&((SuiCore$View * )o)->margin, 10) ;
					((SuiCore$View * )o)->backgroundColor = 0xffeecccc;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
					o->setText(o, Orc$str(&tmpReturn_6, "hello world2") ) ;
				}
			}
		}
		o->setTitle(o, "SuiDesigner") ;
		printf("setTitle\n") ;
		o->setRect(o, 100, 100, 800, 400) ;
		o->setOwner(o, parent) ;
		o->show(o) ;
	}
}

void  startSuiDesigner(){
	URGC_VAR_CLEANUP __Block_385_23*  __var___Block_385_23 = (__var___Block_385_23=NULL,urgc_init_var((void**)&__var___Block_385_23, orc_alloc_and_set_deleter(sizeof(__Block_385_23) , __finiBlock___Block_385_23) ));
	if (false) {
		printf("testWindow  \n") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  projectDirPath = (projectDirPath=NULL,urgc_init_var_class((void**)&projectDirPath, Orc$String$add(Orc$Path_dirname(&tmpReturn_1, Orc$Path_getExecutionPath(&tmpReturn_2) ->str) , "/asset") ));
	printf("projectDirPath:%s\n", projectDirPath->str) ;
	SuiDesigner$Project *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_3 = NULL;
	(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_3) )->init(tmpThis_1, projectDirPath->str) ;
	SuiDesigner$EditCtx *  tmpThis_2 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_4 = NULL;
	(tmpThis_2 = SuiDesigner$EditCtx_ins(&tmpReturn_4) )->init(tmpThis_2) ;
	__var___Block_385_23->t = SuiDesigner$themeIns() ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_5 = NULL;
	{
		SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_5) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_405_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_6, "column") ) ;
		((SuiCore$View * )o)->backgroundColor = __var___Block_385_23->t->bg1;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_7, "stretch") ) ;
		win->setRootView(win, o) ;
	}
	{
		Sui$Window*  o = win;
		
	
		if (1) {
			{
				SuiCore$ViewBase*  o = win->rootView;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_419_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$str(&tmpReturn_8, "rootDiv") ) ;
				if (1) {
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_9 = NULL;
					{
						SuiLayout$LayoutLinear*  __scopeVar_431_16 = SuiLayout$layoutLinear(&tmpReturn_9, o, 0) , *o = __scopeVar_431_16;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_431_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP __Block_431_35*  __var___Block_431_35 = (__var___Block_431_35=NULL,urgc_init_var((void**)&__var___Block_431_35, orc_alloc_and_set_deleter(sizeof(__Block_431_35) , __finiBlock___Block_431_35) ));
						((SuiCore$View * )o)->backgroundColor = __var___Block_385_23->t->menubar_bg;
						SuiCore$Inset$setAxis(&((SuiCore$View * )o)->padding, 0, 6) ;
						URGC_VAR_CLEANUP_CLASS Orc$String*  btnsStr = Orc$str((btnsStr = NULL,&btnsStr), "文件,项目,视图,调试,窗口,帮助") ;
						URGC_VAR_CLEANUP_CLASS Orc$List*  btns = Orc$String$splitByRe((btns = NULL,&btns), btnsStr, ",") ;
						URGC_VAR_CLEANUP_CLASS MenuBarCtrl*  tmpNewOwner_10 = NULL;
						urgc_set_field_class(__var___Block_431_35, (void * )offsetof(__Block_431_35, group) , MenuBarCtrl_new(&tmpNewOwner_10) ) ;
						urgc_set_field_class(__var___Block_431_35->group, (void * )offsetof(MenuBarCtrl, window) , win) ;
						for (int  i = 0; i < btns->size(btns) ; i++) {
							URGC_VAR_CLEANUP_CLASS Orc$String*  btn = (btn=NULL,urgc_init_var_class((void**)&btn, (Orc$String* )btns->get(btns, i) ));
							URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  tmpReturn_11 = NULL;
							{
								SuiView$MenuButton*  __scopeVar_442_24 = SuiView$mkMenuButton(&tmpReturn_11, o, i) , *o = __scopeVar_442_24;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_442_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP __Block_442_43*  __var___Block_442_43 = (__var___Block_442_43=NULL,urgc_init_var((void**)&__var___Block_442_43, orc_alloc_and_set_deleter(sizeof(__Block_442_43) , __finiBlock___Block_442_43) ));
								urgc_set_field_class(__var___Block_442_43, (void * )offsetof(__Block_442_43, mbutton) , o) ;
								urgc_set_field_class(o, (void * )offsetof(SuiView$MenuButton, text) , btn) ;
								URGC_VAR_CLEANUP __Closure_446_44*  tmpReturn_12 = NULL;
								urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onMouseMove) , __make___Closure_446_44(&tmpReturn_12, __var___Block_431_35, __var___Block_442_43) ) ;
								URGC_VAR_CLEANUP __Closure_450_39*  tmpReturn_13 = NULL;
								urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onClick) , __make___Closure_450_39(&tmpReturn_13, __var___Block_431_35, __var___Block_442_43) ) ;
							}
						}
					}
					if (1) {
						URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_14 = NULL;
						{
							SuiLayout$LayoutLinear*  __scopeVar_461_16 = SuiLayout$layoutLinear(&tmpReturn_14, o, 0) , *o = __scopeVar_461_16;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_461_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							((SuiCore$View * )o)->backgroundColor = __var___Block_385_23->t->toolbar_bg;
							SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 6) ;
							URGC_VAR_CLEANUP_CLASS Orc$String*  btnsStr = Orc$str((btnsStr = NULL,&btnsStr), "more,更多,购物车,profile_light,search,play,print,login,share,back,close,add,loading,refresh1,loading2,sub,upload,content_doc") ;
							URGC_VAR_CLEANUP_CLASS Orc$List*  btns = Orc$String$splitByRe((btns = NULL,&btns), btnsStr, ",") ;
							for (int  i = 0; i < btns->size(btns) ; i++) {
								URGC_VAR_CLEANUP_CLASS Orc$String*  btn = (btn=NULL,urgc_init_var_class((void**)&btn, (Orc$String* )btns->get(btns, i) ));
								URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_15 = NULL;
								{
									SuiView$DrawButton*  __scopeVar_472_24 = SuiView$mkDrawButton(&tmpReturn_15, o, i) , *o = __scopeVar_472_24;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_472_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									URGC_VAR_CLEANUP_CLASS Orc$String*  path = Orc$str((path = NULL,&path), "asset/icon/") ;
									Orc$String$add(Orc$String$addString(path, btn) , ".png") ;
									o->normalBg = __var___Block_385_23->t->toolbar_menubutton_bg;
									o->hoverBg = __var___Block_385_23->t->toolbar_menubutton_bg_hover;
									urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , path) ;
									URGC_VAR_CLEANUP __Closure_481_39*  tmpReturn_16 = NULL;
									urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_481_39(&tmpReturn_16) ) ;
								}
							}
						}
					}
					if (1) {
						URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpReturn_17 = NULL;
						{
							SuiView$DockLayout*  __scopeVar_507_16 = SuiView$dockLayout(&tmpReturn_17, o, 0) , *o = __scopeVar_507_16;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_507_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							urgc_set_var_class(&dockLayoutIns, o) ;
							o->tabHeadBg = __var___Block_385_23->t->dock_headbar_bg;
							((SuiCore$View * )o)->radius->setAll(((SuiCore$View * )o)->radius, 6) ;
							((SuiCore$View * )o)->backgroundColor = 0x00000000;
							((SuiCore$View * )o)->width = 100;
							((SuiCore$View * )o)->height = 20;
							((SuiCore$View * )o)->needClip = true;
							if (((SuiCore$Node * )o)->isNewForReact) {
								URGC_VAR_CLEANUP __Closure_523_49*  tmpReturn_18 = NULL;
								urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemHeadView) , __make___Closure_523_49(&tmpReturn_18, __var___Block_385_23) ) ;
								URGC_VAR_CLEANUP __Closure_556_52*  tmpReturn_19 = NULL;
								urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemContentView) , __make___Closure_556_52(&tmpReturn_19, __var___Block_385_23) ) ;
								SuiView$DockItem *  root = o->root;
								URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_20 = NULL;
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_21 = NULL;
								{
									SuiView$DockItem*  o = SuiView$mkDockItemTab(&tmpReturn_20, root, Orc$str(&tmpReturn_21, "tab-project") ) ;
									
								
									o->width = 150;
									URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_22 = NULL;
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_23 = NULL;
									{
										SuiView$DockItem*  __scopeVar_619_28 = SuiView$mkDockItem(&tmpReturn_22, o, Orc$str(&tmpReturn_23, "hier") ) , *o = __scopeVar_619_28;
										
									
										o->intId = 0;
									}
								}
								URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_24 = NULL;
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_25 = NULL;
								{
									SuiView$DockItem*  o = SuiView$mkDockItemSplitter(&tmpReturn_24, root, Orc$str(&tmpReturn_25, "center") , false) ;
									
								
									URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_26 = NULL;
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_27 = NULL;
									{
										SuiView$DockItem*  __scopeVar_637_28 = SuiView$mkDockItemTab(&tmpReturn_26, o, Orc$str(&tmpReturn_27, "center") ) , *o = __scopeVar_637_28;
										
									
										o->intId = 10;
										URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_28 = NULL;
										URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_29 = NULL;
										{
											SuiView$DockItem*  __scopeVar_640_32 = SuiView$mkDockItem(&tmpReturn_28, o, Orc$str(&tmpReturn_29, "scene") ) , *o = __scopeVar_640_32;
											
										
											o->intId = 3;
										}
										URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_30 = NULL;
										URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_31 = NULL;
										{
											SuiView$DockItem*  __scopeVar_641_32 = SuiView$mkDockItem(&tmpReturn_30, o, Orc$str(&tmpReturn_31, "tab1") ) , *o = __scopeVar_641_32;
											
										
											o->intId = 3;
										}
									}
									URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_32 = NULL;
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_33 = NULL;
									{
										SuiView$DockItem*  __scopeVar_643_28 = SuiView$mkDockItemSplitter(&tmpReturn_32, o, Orc$str(&tmpReturn_33, "center") , true) , *o = __scopeVar_643_28;
										
									
										URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_34 = NULL;
										URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_35 = NULL;
										{
											SuiView$DockItem*  __scopeVar_644_32 = SuiView$mkDockItemTab(&tmpReturn_34, o, Orc$str(&tmpReturn_35, "tab-project") ) , *o = __scopeVar_644_32;
											
										
											o->width = 150;
											URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_36 = NULL;
											URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_37 = NULL;
											{
												SuiView$DockItem*  __scopeVar_646_36 = SuiView$mkDockItem(&tmpReturn_36, o, Orc$str(&tmpReturn_37, "project") ) , *o = __scopeVar_646_36;
												
											
												o->intId = 30;
											}
										}
										URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_38 = NULL;
										URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_39 = NULL;
										{
											SuiView$DockItem*  __scopeVar_650_32 = SuiView$mkDockItem(&tmpReturn_38, o, Orc$str(&tmpReturn_39, "dir") ) , *o = __scopeVar_650_32;
											
										
											o->intId = 3;
										}
									}
								}
								URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_40 = NULL;
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_41 = NULL;
								{
									SuiView$DockItem*  o = SuiView$mkDockItemTab(&tmpReturn_40, root, Orc$str(&tmpReturn_41, "tab-inspector") ) ;
									
								
									o->width = 250;
									URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_42 = NULL;
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_43 = NULL;
									{
										SuiView$DockItem*  __scopeVar_656_28 = SuiView$mkDockItem(&tmpReturn_42, o, Orc$str(&tmpReturn_43, "inspector") ) , *o = __scopeVar_656_28;
										
									
										o->intId = 2;
									}
								}
							}
							URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_44 = NULL;
							{
								SuiLayout$LayoutLinearCell*  __scopeVar_663_20 = SuiLayout$layoutLinearCell(&tmpReturn_44, o, 0) , *o = __scopeVar_663_20;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_663_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								o->grow = 1;
							}
						}
					}
				}
				if (0) {
					
				}
			}
		}
		printf("initData\n") ;
		o->setTitle(o, "SuiDesigner") ;
		printf("setTitle\n") ;
		o->setRect(o, 100, 300, 800, 400) ;
		printf("setRect\n") ;
		o->show(o) ;
		printf("show\n") ;
	}
}


//vtable instance
Vtable_Tmp3 _vtable_Tmp3;

// init meta

void Tmp3_initMeta(Vtable_Tmp3 *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "tmp", OrcMetaType_int, offsetof(Tmp3, tmp), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Tmp3* Vtable_Tmp3_init(Vtable_Tmp3* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Tmp3;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Tmp3_new;
    ((Vtable_Object*)pvt)->className = "Tmp3";

    ((Vtable_Object*)pvt)->initMeta = (void*)Tmp3_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Tmp3_fini(Tmp3 *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Tmp3_init_fields(Tmp3 *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Tmp3_fini;
	//fields
    {
	((Tmp3*)self)->tmp = 30;
    }
	
}

// init function

void Tmp3_init(Tmp3 *self, void *pOwner){
    Vtable_Tmp3_init(&_vtable_Tmp3);

    ((Object*)self)->vtable = (void*)&_vtable_Tmp3;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Tmp3_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Tmp3 * Tmp3_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Tmp3 *self = calloc(1, sizeof(Tmp3));
	
    Tmp3_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_Tmp2 _vtable_Tmp2;

// init meta

void Tmp2_initMeta(Vtable_Tmp2 *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "a", OrcMetaType_int, offsetof(Tmp2, a), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "tmp3", ((Vtable_Object*)Vtable_Tmp3_init(0)), offsetof(Tmp2, tmp3), true, false, 1);

	orc_metaField_method(&pNext, "print", offsetof(Tmp2, print));
}


// vtable init


Vtable_Tmp2* Vtable_Tmp2_init(Vtable_Tmp2* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Tmp2;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Tmp2_new;
    ((Vtable_Object*)pvt)->className = "Tmp2";

    ((Vtable_Object*)pvt)->initMeta = (void*)Tmp2_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Tmp2_fini(Tmp2 *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Tmp2_init_fields(Tmp2 *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Tmp2_fini;
	//fields
    {
	((Tmp2*)self)->a = 10;
	urgc_set_field_class(self, (void**)&((Tmp2*)self)->tmp3, NULL);
    }
	((Tmp2*)self)->print = (void*)Tmp2$print;
	((Object*)self)->ctor = (void*)Tmp2$ctor;
	((Object*)self)->dtor = (void*)Tmp2$dtor;
}

// init function

void Tmp2_init(Tmp2 *self, void *pOwner){
    Vtable_Tmp2_init(&_vtable_Tmp2);

    ((Object*)self)->vtable = (void*)&_vtable_Tmp2;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Tmp2_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Tmp2 * Tmp2_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Tmp2 *self = calloc(1, sizeof(Tmp2));
	
    Tmp2_init(self, pOwner);
    return self;
}


// class members
void  Tmp2$print(Tmp2 *  self){
	printf("tmp.a = %d\n", self->a) ;
}


void  Tmp2$ctor(Tmp2 *  self){
	printf("Tmp()\n") ;
}


void  Tmp2$dtor(Tmp2 *  self){
	printf("~Tmp()\n") ;
}



void  test_tmp2(){
	URGC_VAR_CLEANUP __Block_1139_16*  __var___Block_1139_16 = (__var___Block_1139_16=NULL,urgc_init_var((void**)&__var___Block_1139_16, orc_alloc_and_set_deleter(sizeof(__Block_1139_16) , __finiBlock___Block_1139_16) ));
	URGC_VAR_CLEANUP_CLASS Tmp2*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(__var___Block_1139_16, (void * )offsetof(__Block_1139_16, a) , Tmp2_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP void  (**say)(void *  self) = NULL;
	URGC_VAR_CLEANUP __Closure_say_1141*  tmpReturn_2 = NULL;
	(urgc_set_var(&say, __make___Closure_say_1141(&tmpReturn_2, __var___Block_1139_16) ) );
	__var___Block_1139_16->a->a = 323;
	__var___Block_1139_16->a->print(__var___Block_1139_16->a) ;
	(*(say))((void * )(say)) ;
	__var___Block_1139_16->a->print(__var___Block_1139_16->a) ;
}

static void  __finiBlock___Block_92_39(__Block_92_39 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_92_39, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_141_43(__Block_141_43 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_141_43, o) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_431_35(__Block_431_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_431_35, group) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_442_43(__Block_442_43 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_442_43, mbutton) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_385_23(__Block_385_23 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1139_16(__Block_1139_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_1139_16, a) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_onActive_98(__Closure_onActive_98 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu:%s\n", item->label->str) ;
	if (Orc$String$equals(item->label, "Close") ) {
		exit(0) ;
	}
	if (Orc$String$equals(item->label, "保存场景") ) {
		SuiDesigner$UiAction_savePrefab() ;
	}
	if (Orc$String$equals(item->label, "关闭场景") ) {
		SuiDesigner$UiAction_closeCurrentPrefab() ;
	}
	if (Orc$String$equals(item->label, "退出") ) {
		exit(0) ;
	}
	if (Orc$String$equals(item->label, "NewWindow") ) {
		show_newWindow(NULL) ;
	}
	else if (Orc$String$equals(item->label, "MaxWindow") ) {
		self->__var___Block_92_39->self->window->maximize(self->__var___Block_92_39->self->window) ;
	}
	else if (Orc$String$equals(item->label, "SaveDockLayout") ) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  jo = dockLayoutIns->root->toJson((jo = NULL,&jo), dockLayoutIns->root) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  s = jo->dump((s = NULL,&s), jo) ;
		printf("docklayout:\n%s\n", s->str) ;
		Orc$Path_writeText("mainlayout.json", s->str) ;
	}
	else if (Orc$String$equals(item->label, "LoadDockLayout") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  text = Orc$Path_readText((text = NULL,&text), "mainlayout.json") ;
		printf("text:%s\n", text->str) ;
		URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), text->str) ;
		URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  root = SuiView$DockItem_fromJson((root = NULL,&root), jo) ;
		urgc_set_field_class(dockLayoutIns, (void * )offsetof(SuiView$DockLayout, root) , root) ;
		((SuiCore$Node * )dockLayoutIns)->trigger_react(dockLayoutIns) ;
	}
	else {
		SuiDialog$MessageDialog_alert(item->label->str, "tip") ;
	}
}

static void  __fini___Closure_onActive_98(__Closure_onActive_98 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_onActive_98, __var___Block_92_39) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_onActive_98*  __make___Closure_onActive_98(__Closure_onActive_98 **  __outRef__, __Block_92_39 *  __var___Block_92_39){
	URGC_VAR_CLEANUP __Closure_onActive_98*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_onActive_98) , __fini___Closure_onActive_98) ));
	self->invoke = __fn___Closure_onActive_98;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_onActive_98, __var___Block_92_39) , __var___Block_92_39) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_222_28(__Closure_222_28 *  self){
	printf("\ncbOnDismiss:%p\n\n", self->__var___Block_92_39->self) ;
	self->__var___Block_92_39->self->onPopupDismiss(self->__var___Block_92_39->self) ;
	urgc_set_field_class(self->__var___Block_141_43, (void * )offsetof(__Block_141_43, o) , NULL) ;
}

static void  __fini___Closure_222_28(__Closure_222_28 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_222_28, __var___Block_92_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(__Closure_222_28, __var___Block_141_43) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_222_28*  __make___Closure_222_28(__Closure_222_28 **  __outRef__, __Block_92_39 *  __var___Block_92_39, __Block_141_43 *  __var___Block_141_43){
	URGC_VAR_CLEANUP __Closure_222_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_222_28) , __fini___Closure_222_28) ));
	self->invoke = __fn___Closure_222_28;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_222_28, __var___Block_92_39) , __var___Block_92_39) ;
	urgc_set_field(self, (void * )offsetof(__Closure_222_28, __var___Block_141_43) , __var___Block_141_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_446_44(__Closure_446_44 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_431_35->group->onmove(self->__var___Block_431_35->group, self->__var___Block_442_43->mbutton, me) ;
}

static void  __fini___Closure_446_44(__Closure_446_44 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_446_44, __var___Block_431_35) , NULL) ;
	urgc_set_field(self, (void * )offsetof(__Closure_446_44, __var___Block_442_43) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_446_44*  __make___Closure_446_44(__Closure_446_44 **  __outRef__, __Block_431_35 *  __var___Block_431_35, __Block_442_43 *  __var___Block_442_43){
	URGC_VAR_CLEANUP __Closure_446_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_446_44) , __fini___Closure_446_44) ));
	self->invoke = __fn___Closure_446_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_446_44, __var___Block_431_35) , __var___Block_431_35) ;
	urgc_set_field(self, (void * )offsetof(__Closure_446_44, __var___Block_442_43) , __var___Block_442_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_450_39(__Closure_450_39 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_431_35->group->onclick(self->__var___Block_431_35->group, self->__var___Block_442_43->mbutton, me) ;
}

static void  __fini___Closure_450_39(__Closure_450_39 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_450_39, __var___Block_431_35) , NULL) ;
	urgc_set_field(self, (void * )offsetof(__Closure_450_39, __var___Block_442_43) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_450_39*  __make___Closure_450_39(__Closure_450_39 **  __outRef__, __Block_431_35 *  __var___Block_431_35, __Block_442_43 *  __var___Block_442_43){
	URGC_VAR_CLEANUP __Closure_450_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_450_39) , __fini___Closure_450_39) ));
	self->invoke = __fn___Closure_450_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_450_39, __var___Block_431_35) , __var___Block_431_35) ;
	urgc_set_field(self, (void * )offsetof(__Closure_450_39, __var___Block_442_43) , __var___Block_442_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_481_39(__Closure_481_39 *  self, SuiCore$MouseEvent *  me){
	((SuiCore$Event * )me)->stopPropagation(me) ;
}

static void  __fini___Closure_481_39(__Closure_481_39 *  self){
	urgc_free_later(self) ;
}

static __Closure_481_39*  __make___Closure_481_39(__Closure_481_39 **  __outRef__){
	URGC_VAR_CLEANUP __Closure_481_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_481_39) , __fini___Closure_481_39) ));
	self->invoke = __fn___Closure_481_39;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_523_49(__Closure_523_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex){
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpItem = (tmpItem=NULL,urgc_init_var_class((void**)&tmpItem, item));
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpDock = (tmpDock=NULL,urgc_init_var_class((void**)&tmpDock, dockLayoutIns));
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_528_28 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_528_28;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_528_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_2, "pointer") ) ;
		o->setText(o, item->id) ;
		o->color = self->__var___Block_385_23->t->dock_head_c;
		((SuiCore$View * )o)->padding.top = 4;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->padding, 8) ;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 0.0f, 0xffaeaeb2) ;
		bool  active = item->parent->tabActiveIndex == kidIndex;
		if (active) {
			((SuiCore$View * )o)->border->t->w = 2.f;
			((SuiCore$View * )o)->border->t->color = self->__var___Block_385_23->t->c_main;
		}
		if (kidIndex < item->parent->children->size(item->parent->children)  - 1) {
			((SuiCore$View * )o)->border->r->w = 1.f;
		}
		((SuiCore$View * )o)->backgroundColor = active ? self->__var___Block_385_23->t->dock_head_bg_active : self->__var___Block_385_23->t->dock_head_bg;
	}
}

static void  __fini___Closure_523_49(__Closure_523_49 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_523_49, __var___Block_385_23) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_523_49*  __make___Closure_523_49(__Closure_523_49 **  __outRef__, __Block_385_23 *  __var___Block_385_23){
	URGC_VAR_CLEANUP __Closure_523_49*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_523_49) , __fini___Closure_523_49) ));
	self->invoke = __fn___Closure_523_49;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_523_49, __var___Block_385_23) , __var___Block_385_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$ViewBase *  __fn___Closure_556_52(__Closure_556_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o){
	if (Orc$String$equals(item->id, "project") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirTreeView*  tmpReturn_1 = NULL;
		{
			SuiDesigner$AssetDirTreeView*  __scopeVar_558_32 = SuiDesigner$mkAssetDirTreeView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_558_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_558_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_385_23->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "hier") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SceneHierView*  tmpReturn_2 = NULL;
		{
			SuiDesigner$SceneHierView*  __scopeVar_564_32 = SuiDesigner$mkSceneHierView(&tmpReturn_2, o, (long long )item) , *o = __scopeVar_564_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_564_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_385_23->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "inspector") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorView*  tmpReturn_3 = NULL;
		{
			SuiDesigner$InspectorView*  __scopeVar_570_32 = SuiDesigner$mkInspectorView(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_570_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_570_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_385_23->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "dir") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirView*  tmpReturn_4 = NULL;
		{
			SuiDesigner$AssetDirView*  __scopeVar_576_32 = SuiDesigner$mkAssetDirView(&tmpReturn_4, o, (long long )item) , *o = __scopeVar_576_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_576_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_385_23->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "scene") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SceneView*  tmpReturn_5 = NULL;
		{
			SuiDesigner$SceneView*  __scopeVar_582_32 = SuiDesigner$mkSceneView(&tmpReturn_5, o, (long long )item) , *o = __scopeVar_582_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_582_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_385_23->t->dock_content_bg;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_584_36 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_584_36;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_584_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
			return o; 
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
	{
		SuiView$TextView*  __scopeVar_592_28 = SuiView$mkTextView(&tmpReturn_7, o, (long long )item) , *o = __scopeVar_592_28;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_592_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->needClip = true;
		printf("render dock content:%d, %s\n", item->intId, item->id->str) ;
		o->setText(o, item->id) ;
		o->font_size = 30;
		o->color = 0xff000000;
		((SuiCore$View * )o)->radius->setAll(((SuiCore$View * )o)->radius, 6) ;
		SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 6) ;
		((SuiCore$View * )o)->backgroundColor = item->intId == 0 ? 0x53ff0000 : item->intId == 1 ? 0x53f0ff00 : item->intId == 2 ? 0x5330ffff : 0x5300ffff;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_8 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_608_32 = SuiLayout$layoutLinearCell(&tmpReturn_8, o, 0) , *o = __scopeVar_608_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_608_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		return o; 
	}
}

static void  __fini___Closure_556_52(__Closure_556_52 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_556_52, __var___Block_385_23) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_556_52*  __make___Closure_556_52(__Closure_556_52 **  __outRef__, __Block_385_23 *  __var___Block_385_23){
	URGC_VAR_CLEANUP __Closure_556_52*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_556_52) , __fini___Closure_556_52) ));
	self->invoke = __fn___Closure_556_52;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_556_52, __var___Block_385_23) , __var___Block_385_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_say_1141(__Closure_say_1141 *  self){
	printf("say a.a:%d \n", self->__var___Block_1139_16->a->a) ;
	self->__var___Block_1139_16->a->a = -1;
}

static void  __fini___Closure_say_1141(__Closure_say_1141 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_say_1141, __var___Block_1139_16) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_say_1141*  __make___Closure_say_1141(__Closure_say_1141 **  __outRef__, __Block_1139_16 *  __var___Block_1139_16){
	URGC_VAR_CLEANUP __Closure_say_1141*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_say_1141) , __fini___Closure_say_1141) ));
	self->invoke = __fn___Closure_say_1141;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_say_1141, __var___Block_1139_16) , __var___Block_1139_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

int  testAudio(){
	{
		ma_result result;
		ma_engine engine;
		result = ma_engine_init(NULL, &engine) ;
		printf("hi. result:%d MA_SUCCESS:%d\n", result, MA_SUCCESS) ;
		if (result != MA_SUCCESS) {
			return result; 
		}
		const char *  path = "../asset/a.mp3";
		printf("play sound:%s\n", path) ;
		ma_engine_play_sound(&engine, path, NULL) ;
		getchar() ;
	}
	return 0; 
}

int  main(){
	urgc_start_process_thread() ;
	windowInit() ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d$HoroEditor*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner3d$HoroEditor*  o = SuiDesigner3d$HoroEditor_new(&tmpNewOwner_1) ;
		
	
		o->openProject(o, "../DemoProject") ;
	}
	SuiCore$App *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  tmpReturn_2 = NULL;
	(tmpThis_1 = SuiCore$App_use(&tmpReturn_2) )->runEventLoop(tmpThis_1) ;
	return 0; 
}

void  testTransparency(){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpNewOwner_1 = NULL;
	{
		SuiLayout$LayoutAlign*  o = SuiLayout$LayoutAlign_new(&tmpNewOwner_1) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1255_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = 0x33afafff;
		SuiCore$Vec2$set(&o->anchor, 0.5, 0.5) ;
		SuiCore$Vec2$set(&o->align, 0.5, 0.5) ;
		urgc_set_field_class(win, (void * )offsetof(Sui$Window, rootView) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_2 = NULL;
		{
			SuiCore$View*  __scopeVar_1262_8 = SuiView$mkView(&tmpReturn_2, o, 0) , *o = __scopeVar_1262_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1262_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->backgroundColor = 0xffefefff;
			o->width = 100;
			o->height = 100;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
		{
			SuiView$TextView*  __scopeVar_1267_8 = SuiView$mkTextView(&tmpReturn_3, o, 0) , *o = __scopeVar_1267_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1267_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			o->setText(o, Orc$str(&tmpReturn_4, "你好呀， Sui") ) ;
		}
	}
	win->setTitle(win, "hi transparency") ;
	win->setSize(win, 800, 600) ;
	win->show(win) ;
}



