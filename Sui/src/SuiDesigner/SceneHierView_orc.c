
#include "SceneHierView_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./RegisterNodes_orc.h"
#include "./DrawDegree_orc.h"
#include "./UiAction_orc.h"
#include "./ANode_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_123_68 SuiDesigner$__Block_123_68;

typedef struct tagSuiDesigner$__Block_125_33 SuiDesigner$__Block_125_33;

typedef struct tagSuiDesigner$__Block_190_23 SuiDesigner$__Block_190_23;

typedef struct tagSuiDesigner$__Block_230_29 SuiDesigner$__Block_230_29;

typedef struct tagSuiDesigner$__Block_258_78 SuiDesigner$__Block_258_78;

typedef struct tagSuiDesigner$__Closure_onActive_129 SuiDesigner$__Closure_onActive_129;

typedef struct tagSuiDesigner$__Closure_238_32 SuiDesigner$__Closure_238_32;

typedef struct tagSuiDesigner$__Closure_243_42 SuiDesigner$__Closure_243_42;

typedef struct tagSuiDesigner$__Closure_255_42 SuiDesigner$__Closure_255_42;

typedef struct tagSuiDesigner$__Closure_258_30 SuiDesigner$__Closure_258_30;

typedef struct tagSuiDesigner$__Closure_274_45 SuiDesigner$__Closure_274_45;

typedef struct tagSuiDesigner$__Closure_hi_275 SuiDesigner$__Closure_hi_275;



struct tagSuiDesigner$__Block_123_68 {
	SuiDesigner$SceneHierView*  self ;
};





struct tagSuiDesigner$__Block_125_33 {
	SuiDesigner$ANode*  anode ;
};





struct tagSuiDesigner$__Block_190_23 {
	SuiDesigner$SceneHierView*  self ;
	int  xxx ;
};





struct tagSuiDesigner$__Block_230_29 {
	SuiView$TreeView*  treeView ;
};





struct tagSuiDesigner$__Block_258_78 {
	SuiDesigner$ANode*  s ;
};





struct tagSuiDesigner$__Closure_onActive_129 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_129 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_123_68*  __var___Block_123_68 ;
	SuiDesigner$__Block_125_33*  __var___Block_125_33 ;
};





struct tagSuiDesigner$__Closure_238_32 {
	Orc$String*  (*invoke)(SuiDesigner$__Closure_238_32 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_243_42 {
	Orc$List*  (*invoke)(SuiDesigner$__Closure_243_42 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_255_42 {
	void  (*invoke)(SuiDesigner$__Closure_255_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_190_23*  __var___Block_190_23 ;
};





struct tagSuiDesigner$__Closure_258_30 {
	void  (*invoke)(SuiDesigner$__Closure_258_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_230_29*  __var___Block_230_29 ;
	SuiDesigner$__Block_190_23*  __var___Block_190_23 ;
};





struct tagSuiDesigner$__Closure_274_45 {
	void  (*invoke)(SuiDesigner$__Closure_274_45 *  self, SuiCore$ViewBase *  v);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_190_23*  __var___Block_190_23 ;
	SuiDesigner$__Block_258_78*  __var___Block_258_78 ;
};





struct tagSuiDesigner$__Closure_hi_275 {
	void  (*invoke)(SuiDesigner$__Closure_hi_275 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_190_23*  __var___Block_190_23 ;
};





// static function declaration
static void  __finiBlock___Block_123_68(SuiDesigner$__Block_123_68 *  self);
static void  __finiBlock___Block_125_33(SuiDesigner$__Block_125_33 *  self);
static void  __finiBlock___Block_190_23(SuiDesigner$__Block_190_23 *  self);
static void  __finiBlock___Block_230_29(SuiDesigner$__Block_230_29 *  self);
static void  __finiBlock___Block_258_78(SuiDesigner$__Block_258_78 *  self);
static void  __fn___Closure_onActive_129(SuiDesigner$__Closure_onActive_129 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_129(SuiDesigner$__Closure_onActive_129 *  self);
static SuiDesigner$__Closure_onActive_129*  __make___Closure_onActive_129(SuiDesigner$__Closure_onActive_129 **  __outRef__, SuiDesigner$__Block_123_68 *  __var___Block_123_68, SuiDesigner$__Block_125_33 *  __var___Block_125_33);
static Orc$String*  __fn___Closure_238_32(Orc$String **  __outRef__, SuiDesigner$__Closure_238_32 *  self, Object *  item);
static void  __fini___Closure_238_32(SuiDesigner$__Closure_238_32 *  self);
static SuiDesigner$__Closure_238_32*  __make___Closure_238_32(SuiDesigner$__Closure_238_32 **  __outRef__);
static Orc$List*  __fn___Closure_243_42(Orc$List **  __outRef__, SuiDesigner$__Closure_243_42 *  self, Object *  item);
static void  __fini___Closure_243_42(SuiDesigner$__Closure_243_42 *  self);
static SuiDesigner$__Closure_243_42*  __make___Closure_243_42(SuiDesigner$__Closure_243_42 **  __outRef__);
static void  __fn___Closure_255_42(SuiDesigner$__Closure_255_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item);
static void  __fini___Closure_255_42(SuiDesigner$__Closure_255_42 *  self);
static SuiDesigner$__Closure_255_42*  __make___Closure_255_42(SuiDesigner$__Closure_255_42 **  __outRef__, SuiDesigner$__Block_190_23 *  __var___Block_190_23);
static void  __fn___Closure_258_30(SuiDesigner$__Closure_258_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
static void  __fini___Closure_258_30(SuiDesigner$__Closure_258_30 *  self);
static SuiDesigner$__Closure_258_30*  __make___Closure_258_30(SuiDesigner$__Closure_258_30 **  __outRef__, SuiDesigner$__Block_230_29 *  __var___Block_230_29, SuiDesigner$__Block_190_23 *  __var___Block_190_23);
static void  __fn___Closure_274_45(SuiDesigner$__Closure_274_45 *  self, SuiCore$ViewBase *  v);
static void  __fini___Closure_274_45(SuiDesigner$__Closure_274_45 *  self);
static SuiDesigner$__Closure_274_45*  __make___Closure_274_45(SuiDesigner$__Closure_274_45 **  __outRef__, SuiDesigner$__Block_190_23 *  __var___Block_190_23, SuiDesigner$__Block_258_78 *  __var___Block_258_78);
static void  __fn___Closure_hi_275(SuiDesigner$__Closure_hi_275 *  self);
static void  __fini___Closure_hi_275(SuiDesigner$__Closure_hi_275 *  self);
static SuiDesigner$__Closure_hi_275*  __make___Closure_hi_275(SuiDesigner$__Closure_hi_275 **  __outRef__, SuiDesigner$__Block_190_23 *  __var___Block_190_23);



//vtable instance
Vtable_SuiDesigner$SceneHierView _vtable_SuiDesigner$SceneHierView;

// init meta

void SuiDesigner$SceneHierView_initMeta(Vtable_SuiDesigner$SceneHierView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "onUnmouting", offsetof(SuiDesigner$SceneHierView, onUnmouting));
	orc_metaField_method(&pNext, "_routeRightMenu", offsetof(SuiDesigner$SceneHierView, _routeRightMenu));
	orc_metaField_method(&pNext, "_onItemRightClick", offsetof(SuiDesigner$SceneHierView, _onItemRightClick));
	orc_metaField_method(&pNext, "_onEvent_forItemView", offsetof(SuiDesigner$SceneHierView, _onEvent_forItemView));
}


// vtable init


Vtable_SuiDesigner$SceneHierView* Vtable_SuiDesigner$SceneHierView_init(Vtable_SuiDesigner$SceneHierView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SceneHierView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SceneHierView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SceneHierView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SceneHierView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SceneHierView_fini(SuiDesigner$SceneHierView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiDesigner$SceneHierView_init_fields(SuiDesigner$SceneHierView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SceneHierView_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)SuiDesigner$SceneHierView$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiDesigner$SceneHierView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$SceneHierView$onMounted;
	((SuiDesigner$SceneHierView*)self)->onUnmouting = (void*)SuiDesigner$SceneHierView$onUnmouting;
	((SuiDesigner$SceneHierView*)self)->_routeRightMenu = (void*)SuiDesigner$SceneHierView$_routeRightMenu;
	((SuiDesigner$SceneHierView*)self)->_onItemRightClick = (void*)SuiDesigner$SceneHierView$_onItemRightClick;
	((SuiDesigner$SceneHierView*)self)->_onEvent_forItemView = (void*)SuiDesigner$SceneHierView$_onEvent_forItemView;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$SceneHierView$react;
}

// init function

void SuiDesigner$SceneHierView_init(SuiDesigner$SceneHierView *self, void *pOwner){
    Vtable_SuiDesigner$SceneHierView_init(&_vtable_SuiDesigner$SceneHierView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SceneHierView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SceneHierView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SceneHierView * SuiDesigner$SceneHierView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SceneHierView *self = calloc(1, sizeof(SuiDesigner$SceneHierView));
	
    SuiDesigner$SceneHierView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SceneHierView$ctor(SuiDesigner$SceneHierView *  self){
	SuiCore$Listener$ctor(self) ;
}


void  SuiDesigner$SceneHierView$onListenerEvent(SuiDesigner$SceneHierView *  self, SuiCore$Event *  event){
	if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeAttrChanged_init(NULL))) {
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeChanged_init(NULL))) {
		SuiDesigner$EventANodeChanged *  e = (SuiDesigner$EventANodeChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventFileItemChanged_init(NULL))) {
		SuiDesigner$EventFileItemChanged *  e = (SuiDesigner$EventFileItemChanged * )e;
	}
}


void  SuiDesigner$SceneHierView$onMounted(SuiDesigner$SceneHierView *  self){
	SuiCore$Node$onMounted(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  SuiDesigner$SceneHierView$onUnmouting(SuiDesigner$SceneHierView *  self){
	SuiCore$Node$onUnmounting(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  SuiDesigner$SceneHierView$_routeRightMenu(SuiDesigner$SceneHierView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$ANode*  anode){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anode);

	if (!item->cmd) {
		return ; 
	}
	if (Orc$String$startsWith(item->cmd, "AddView/") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  viewName = Orc$Path_basename((viewName = NULL,&viewName), item->cmd->str) ;
		SuiDesigner$UiAction_addView(anode, viewName) ;
		return ; 
	}
	if (Orc$String$equals(item->cmd, "RenameView") ) {
		SuiDesigner$UiAction_renameANode(anode) ;
		return ; 
	}
	if (Orc$String$equals(item->cmd, "DeleteView") ) {
		SuiDesigner$UiAction_deleteANode(anode) ;
		return ; 
	}
	else if (Orc$String$equals(item->cmd, "LocateView") ) {
		SuiDesigner$UiAction_locateView(anode) ;
	}
	else if (Orc$String$equals(item->cmd, "CopyView") ) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  list = (list=NULL,urgc_init_var_class((void**)&list, Orc$List_new(&list) ));
		list->add(list, anode) ;
		SuiDesigner$UiAction_copyANodes(list) ;
	}
	else if (Orc$String$equals(item->cmd, "PasteView") ) {
		SuiDesigner$UiAction_pasteANodes(anode) ;
	}
	else if (Orc$String$equals(item->cmd, "CutView") ) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  list = (list=NULL,urgc_init_var_class((void**)&list, Orc$List_new(&list) ));
		list->add(list, anode) ;
		SuiDesigner$UiAction_cutANodes(list) ;
	}
}


void  SuiDesigner$SceneHierView$_onItemRightClick(SuiDesigner$SceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_123_68*  __var___Block_123_68 = (__var___Block_123_68=NULL,urgc_init_var((void**)&__var___Block_123_68, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_123_68) , __finiBlock___Block_123_68) ));
	urgc_set_field_class(__var___Block_123_68, (void * )offsetof(SuiDesigner$__Block_123_68, self) , self) ;
	((SuiCore$Event * )me)->stopPropagation(me) ;
	if (Orc_instanceof((Object*)item, (Vtable_Object*)Vtable_SuiDesigner$ANode_init(NULL))) {
		URGC_VAR_CLEANUP SuiDesigner$__Block_125_33*  __var___Block_125_33 = (__var___Block_125_33=NULL,urgc_init_var((void**)&__var___Block_125_33, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_125_33) , __finiBlock___Block_125_33) ));
		urgc_set_field_class(__var___Block_125_33, (void * )offsetof(SuiDesigner$__Block_125_33, anode) , (SuiDesigner$ANode* )item) ;
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
		{
			SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
			
		
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_129*  tmpReturn_2 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_129(&tmpReturn_2, __var___Block_123_68, __var___Block_125_33) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_139_16 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "重命名") , onActive) , *o = __scopeVar_139_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "RenameView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_140_16 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "添加") , onActive) , *o = __scopeVar_140_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "RenameView") ) ;
				URGC_VAR_CLEANUP_CLASS SuiCore$NodeLib*  lib = (lib=NULL,urgc_init_var_class((void**)&lib, SuiCore$NodeLib_use() ));
				for (int  i = 0; i < lib->list->size(lib->list) ; i++) {
					SuiCore$NodeRegisterInfo *  info = (SuiCore$NodeRegisterInfo * )lib->list->get(lib->list, i) ;
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_146_24 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, info->className) , onActive) , *o = __scopeVar_146_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$String$add(Orc$str(&tmpReturn_11, "AddView/") , info->className) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_12 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_167_16 = SuiView$mkMenuNativeItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "删除") , onActive) , *o = __scopeVar_167_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_14, "DeleteView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_15 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_168_16 = SuiView$mkMenuNativeItem(&tmpReturn_15, o, Orc$str(&tmpReturn_16, "定位") , onActive) , *o = __scopeVar_168_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_17, "LocateView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_18 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_19 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_169_16 = SuiView$mkMenuNativeItem(&tmpReturn_18, o, Orc$str(&tmpReturn_19, "复制") , onActive) , *o = __scopeVar_169_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_20, "CopyView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_21 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_170_16 = SuiView$mkMenuNativeItem(&tmpReturn_21, o, Orc$str(&tmpReturn_22, "粘贴") , onActive) , *o = __scopeVar_170_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_23 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_23, "PasteView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_24 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_25 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_171_16 = SuiView$mkMenuNativeItem(&tmpReturn_24, o, Orc$str(&tmpReturn_25, "剪切") , onActive) , *o = __scopeVar_171_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_26, "CutView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
			n->create(n, o) ;
			n->showAtMouse(n) ;
		}
	}
}


void  SuiDesigner$SceneHierView$_onEvent_forItemView(SuiDesigner$SceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			self->_onItemRightClick(self, me, view, item) ;
			return ; 
		}
	}
}


void  SuiDesigner$SceneHierView$react(SuiDesigner$SceneHierView *  self, int  xxx){
	URGC_VAR_CLEANUP SuiDesigner$__Block_190_23*  __var___Block_190_23 = (__var___Block_190_23=NULL,urgc_init_var((void**)&__var___Block_190_23, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_190_23) , __finiBlock___Block_190_23) ));
	__var___Block_190_23->xxx = xxx;
	urgc_set_field_class(__var___Block_190_23, (void * )offsetof(SuiDesigner$__Block_190_23, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
	SuiDesigner$SceneHierView *  o = (SuiDesigner$SceneHierView * )self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_207_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_207_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_207_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->grow = 1;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_4 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_217_8 = SuiView$mkScrollArea(&tmpReturn_4, o, 0) , *o = __scopeVar_217_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_217_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_5, "stretch") ) ;
		o->useMinWidthConstraint = true;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_226_12 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_226_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_226_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TreeView*  tmpReturn_7 = NULL;
		{
			SuiView$TreeView*  __scopeVar_230_12 = SuiView$mkTreeView(&tmpReturn_7, o, 0) , *o = __scopeVar_230_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_230_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP SuiDesigner$__Block_230_29*  __var___Block_230_29 = (__var___Block_230_29=NULL,urgc_init_var((void**)&__var___Block_230_29, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_230_29) , __finiBlock___Block_230_29) ));
			urgc_set_field_class(__var___Block_230_29, (void * )offsetof(SuiDesigner$__Block_230_29, treeView) , o) ;
			ctx->setState(ctx, o->state) ;
			urgc_set_field_class(o->state, (void * )offsetof(SuiView$TreeState, roots) , ctx->roots) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_238_32*  tmpReturn_8 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getId) , __make___Closure_238_32(&tmpReturn_8) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_243_42*  tmpReturn_9 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getItemChildren) , __make___Closure_243_42(&tmpReturn_9) ) ;
			Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "maxOrStretch") ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_255_42*  tmpReturn_10 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, cbOnEvent_forItemView) , __make___Closure_255_42(&tmpReturn_10, __var___Block_190_23) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_258_30*  tmpReturn_11 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, reactItem) , __make___Closure_258_30(&tmpReturn_11, __var___Block_230_29, __var___Block_190_23) ) ;
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



static void  __finiBlock___Block_123_68(SuiDesigner$__Block_123_68 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_123_68, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_125_33(SuiDesigner$__Block_125_33 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_125_33, anode) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_190_23(SuiDesigner$__Block_190_23 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_190_23, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_230_29(SuiDesigner$__Block_230_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_230_29, treeView) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_258_78(SuiDesigner$__Block_258_78 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_258_78, s) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_onActive_129(SuiDesigner$__Closure_onActive_129 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n", item->cmd->str, item->label->str) ;
	self->__var___Block_123_68->self->_routeRightMenu(self->__var___Block_123_68->self, item, self->__var___Block_125_33->anode) ;
}

static void  __fini___Closure_onActive_129(SuiDesigner$__Closure_onActive_129 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_129, __var___Block_123_68) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_129, __var___Block_125_33) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_129*  __make___Closure_onActive_129(SuiDesigner$__Closure_onActive_129 **  __outRef__, SuiDesigner$__Block_123_68 *  __var___Block_123_68, SuiDesigner$__Block_125_33 *  __var___Block_125_33){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_129*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_129) , __fini___Closure_onActive_129) ));
	self->invoke = __fn___Closure_onActive_129;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_129, __var___Block_123_68) , __var___Block_123_68) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_129, __var___Block_125_33) , __var___Block_125_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$String*  __fn___Closure_238_32(Orc$String **  __outRef__, SuiDesigner$__Closure_238_32 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$ANode* )item));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, s->getId(&tmpReturn_1, s) ) ; 
}

static void  __fini___Closure_238_32(SuiDesigner$__Closure_238_32 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_238_32*  __make___Closure_238_32(SuiDesigner$__Closure_238_32 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_238_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_238_32) , __fini___Closure_238_32) ));
	self->invoke = __fn___Closure_238_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$List*  __fn___Closure_243_42(Orc$List **  __outRef__, SuiDesigner$__Closure_243_42 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$ANode* )item));
	return urgc_set_var_for_return_class((void ** )__outRef__, s->children) ; 
}

static void  __fini___Closure_243_42(SuiDesigner$__Closure_243_42 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_243_42*  __make___Closure_243_42(SuiDesigner$__Closure_243_42 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_243_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_243_42) , __fini___Closure_243_42) ));
	self->invoke = __fn___Closure_243_42;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_255_42(SuiDesigner$__Closure_255_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item){
	self->__var___Block_190_23->self->_onEvent_forItemView(self->__var___Block_190_23->self, e, n, item) ;
}

static void  __fini___Closure_255_42(SuiDesigner$__Closure_255_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_255_42, __var___Block_190_23) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_255_42*  __make___Closure_255_42(SuiDesigner$__Closure_255_42 **  __outRef__, SuiDesigner$__Block_190_23 *  __var___Block_190_23){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_255_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_255_42) , __fini___Closure_255_42) ));
	self->invoke = __fn___Closure_255_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_255_42, __var___Block_190_23) , __var___Block_190_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_258_30(SuiDesigner$__Closure_258_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep){
	URGC_VAR_CLEANUP SuiDesigner$__Block_258_78*  __var___Block_258_78 = (__var___Block_258_78=NULL,urgc_init_var((void**)&__var___Block_258_78, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_258_78) , __finiBlock___Block_258_78) ));
	SuiCore$Node *  o = parentNode;
	urgc_set_field_class(__var___Block_258_78, (void * )offsetof(SuiDesigner$__Block_258_78, s) , (SuiDesigner$ANode* )item) ;
	int  idx = -1;
	if (Orc_instanceof((Object*)parentNode, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )parentNode;
		idx = vb->viewIndexInParent(vb) ;
	}
	bool  isSelected = self->__var___Block_230_29->treeView->state->isSelected(self->__var___Block_230_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_1 = NULL;
	{
		SuiView$HoverViewEffect*  __scopeVar_270_20 = SuiView$mkHoverViewEffect(&tmpReturn_1, o, 0) , *o = __scopeVar_270_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_270_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->isActive = isSelected;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_274_45*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, cbOnHoverChanged) , __make___Closure_274_45(&tmpReturn_2, self->__var___Block_190_23, __var___Block_258_78) ) ;
	}
	bool  hasKids = __var___Block_258_78->s->children->size(__var___Block_258_78->s->children)  > 0;
	bool  isOpend = self->__var___Block_230_29->treeView->state->isOpend(self->__var___Block_230_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_3 = NULL;
	{
		SuiView$ImageView*  __scopeVar_293_20 = SuiView$mkImageView(&tmpReturn_3, o, 0) , *o = __scopeVar_293_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_293_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->width = 12;
		((SuiCore$View * )o)->height = 12;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		o->setSrc(o, hasKids ? isOpend ? Orc$str(&tmpReturn_4, "asset/icon/arrow-down.png")  : Orc$str(&tmpReturn_5, "asset/icon/arrow-right.png")  : NULL) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_6 = NULL;
	{
		SuiView$TextView*  __scopeVar_317_20 = SuiView$mkTextView(&tmpReturn_6, o, 0) , *o = __scopeVar_317_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_317_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		if (__var___Block_258_78->s->node && __var___Block_258_78->s->node->name && Orc$String$notEmpty(__var___Block_258_78->s->node->name) ) {
			o->setText(o, __var___Block_258_78->s->node->name) ;
		}
		else {
			o->setText(o, __var___Block_258_78->s->tag) ;
		}
	}
}

static void  __fini___Closure_258_30(SuiDesigner$__Closure_258_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_258_30, __var___Block_230_29) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_258_30, __var___Block_190_23) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_258_30*  __make___Closure_258_30(SuiDesigner$__Closure_258_30 **  __outRef__, SuiDesigner$__Block_230_29 *  __var___Block_230_29, SuiDesigner$__Block_190_23 *  __var___Block_190_23){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_258_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_258_30) , __fini___Closure_258_30) ));
	self->invoke = __fn___Closure_258_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_258_30, __var___Block_230_29) , __var___Block_230_29) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_258_30, __var___Block_190_23) , __var___Block_190_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_274_45(SuiDesigner$__Closure_274_45 *  self, SuiCore$ViewBase *  v){
	URGC_VAR_CLEANUP void  (**hi)(void *  self) = NULL;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_hi_275*  tmpReturn_1 = NULL;
	(urgc_set_var(&hi, __make___Closure_hi_275(&tmpReturn_1, self->__var___Block_190_23) ) );
	if (v->hover) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_2 = NULL;
		urgc_set_field_class(SuiDesigner$EditCtx_ins(&tmpReturn_2) , (void * )offsetof(SuiDesigner$EditCtx, hoverNode) , self->__var___Block_258_78->s) ;
	}
	else {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_3 = NULL;
		urgc_set_field_class(SuiDesigner$EditCtx_ins(&tmpReturn_3) , (void * )offsetof(SuiDesigner$EditCtx, hoverNode) , NULL) ;
	}
	printf("Scene.cbOnHoverChanged:%d\n", v->hover) ;
}

static void  __fini___Closure_274_45(SuiDesigner$__Closure_274_45 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_274_45, __var___Block_190_23) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_274_45, __var___Block_258_78) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_274_45*  __make___Closure_274_45(SuiDesigner$__Closure_274_45 **  __outRef__, SuiDesigner$__Block_190_23 *  __var___Block_190_23, SuiDesigner$__Block_258_78 *  __var___Block_258_78){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_274_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_274_45) , __fini___Closure_274_45) ));
	self->invoke = __fn___Closure_274_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_274_45, __var___Block_190_23) , __var___Block_190_23) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_274_45, __var___Block_258_78) , __var___Block_258_78) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_hi_275(SuiDesigner$__Closure_hi_275 *  self){
	printf("xxx:%d\n", self->__var___Block_190_23->xxx) ;
}

static void  __fini___Closure_hi_275(SuiDesigner$__Closure_hi_275 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_hi_275, __var___Block_190_23) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_hi_275*  __make___Closure_hi_275(SuiDesigner$__Closure_hi_275 **  __outRef__, SuiDesigner$__Block_190_23 *  __var___Block_190_23){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_hi_275*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_hi_275) , __fini___Closure_hi_275) ));
	self->invoke = __fn___Closure_hi_275;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_hi_275, __var___Block_190_23) , __var___Block_190_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiDesigner$SceneHierView*  SuiDesigner$mkSceneHierView(SuiDesigner$SceneHierView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$SceneHierView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$SceneHierView_init(NULL)) ) ; 
}

void  SuiDesigner$testScene(){
	printf("testScene\n") ;
}



