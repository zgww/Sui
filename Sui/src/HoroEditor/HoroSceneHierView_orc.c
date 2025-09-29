
#include "HoroSceneHierView_orc.h" 

#include <stdio.h>
#include <string.h>
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
#include "../SuiDesigner/Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/RegisterNodes_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "../SuiDesigner/UiAction_orc.h"
#include "../SuiDesigner/EditCtx_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "./HoroEditCtx_orc.h"
#include "./HoroEditor_orc.h"
#include "./UiAct_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Camera_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_131_68 HoroEditor$__Block_131_68;

typedef struct tagHoroEditor$__Block_133_33 HoroEditor$__Block_133_33;

typedef struct tagHoroEditor$__Block_204_23 HoroEditor$__Block_204_23;

typedef struct tagHoroEditor$__Block_251_29 HoroEditor$__Block_251_29;

typedef struct tagHoroEditor$__Block_272_78 HoroEditor$__Block_272_78;

typedef struct tagHoroEditor$__Closure_onActive_137 HoroEditor$__Closure_onActive_137;

typedef struct tagHoroEditor$__Closure_259_32 HoroEditor$__Closure_259_32;

typedef struct tagHoroEditor$__Closure_263_42 HoroEditor$__Closure_263_42;

typedef struct tagHoroEditor$__Closure_269_42 HoroEditor$__Closure_269_42;

typedef struct tagHoroEditor$__Closure_272_30 HoroEditor$__Closure_272_30;

typedef struct tagHoroEditor$__Closure_288_45 HoroEditor$__Closure_288_45;

typedef struct tagHoroEditor$__Closure_hi_289 HoroEditor$__Closure_hi_289;



struct tagHoroEditor$__Block_131_68 {
	HoroEditor$HoroSceneHierView*  self ;
};





struct tagHoroEditor$__Block_133_33 {
	SuiDesigner$ANode*  node ;
};





struct tagHoroEditor$__Block_204_23 {
	HoroEditor$HoroSceneHierView*  self ;
	int  xxx ;
};





struct tagHoroEditor$__Block_251_29 {
	SuiView$TreeView*  treeView ;
};





struct tagHoroEditor$__Block_272_78 {
	SuiDesigner$ANode*  s ;
};





struct tagHoroEditor$__Closure_onActive_137 {
	void  (*invoke)(HoroEditor$__Closure_onActive_137 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_131_68*  __var___Block_131_68 ;
	HoroEditor$__Block_133_33*  __var___Block_133_33 ;
};





struct tagHoroEditor$__Closure_259_32 {
	Orc$String*  (*invoke)(HoroEditor$__Closure_259_32 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_263_42 {
	Orc$List*  (*invoke)(HoroEditor$__Closure_263_42 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_269_42 {
	void  (*invoke)(HoroEditor$__Closure_269_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_204_23*  __var___Block_204_23 ;
};





struct tagHoroEditor$__Closure_272_30 {
	void  (*invoke)(HoroEditor$__Closure_272_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_251_29*  __var___Block_251_29 ;
	HoroEditor$__Block_204_23*  __var___Block_204_23 ;
};





struct tagHoroEditor$__Closure_288_45 {
	void  (*invoke)(HoroEditor$__Closure_288_45 *  self, SuiCore$ViewBase *  v);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_204_23*  __var___Block_204_23 ;
	HoroEditor$__Block_272_78*  __var___Block_272_78 ;
};





struct tagHoroEditor$__Closure_hi_289 {
	void  (*invoke)(HoroEditor$__Closure_hi_289 *  self);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_204_23*  __var___Block_204_23 ;
};





// static function declaration
static void  __finiBlock___Block_131_68(HoroEditor$__Block_131_68 *  self);
static void  __finiBlock___Block_133_33(HoroEditor$__Block_133_33 *  self);
static void  __finiBlock___Block_204_23(HoroEditor$__Block_204_23 *  self);
static void  __finiBlock___Block_251_29(HoroEditor$__Block_251_29 *  self);
static void  __finiBlock___Block_272_78(HoroEditor$__Block_272_78 *  self);
static void  __fn___Closure_onActive_137(HoroEditor$__Closure_onActive_137 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_137(HoroEditor$__Closure_onActive_137 *  self);
static HoroEditor$__Closure_onActive_137*  __make___Closure_onActive_137(HoroEditor$__Closure_onActive_137 **  __outRef__, HoroEditor$__Block_131_68 *  __var___Block_131_68, HoroEditor$__Block_133_33 *  __var___Block_133_33);
static Orc$String*  __fn___Closure_259_32(Orc$String **  __outRef__, HoroEditor$__Closure_259_32 *  self, Object *  item);
static void  __fini___Closure_259_32(HoroEditor$__Closure_259_32 *  self);
static HoroEditor$__Closure_259_32*  __make___Closure_259_32(HoroEditor$__Closure_259_32 **  __outRef__);
static Orc$List*  __fn___Closure_263_42(Orc$List **  __outRef__, HoroEditor$__Closure_263_42 *  self, Object *  item);
static void  __fini___Closure_263_42(HoroEditor$__Closure_263_42 *  self);
static HoroEditor$__Closure_263_42*  __make___Closure_263_42(HoroEditor$__Closure_263_42 **  __outRef__);
static void  __fn___Closure_269_42(HoroEditor$__Closure_269_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item);
static void  __fini___Closure_269_42(HoroEditor$__Closure_269_42 *  self);
static HoroEditor$__Closure_269_42*  __make___Closure_269_42(HoroEditor$__Closure_269_42 **  __outRef__, HoroEditor$__Block_204_23 *  __var___Block_204_23);
static void  __fn___Closure_272_30(HoroEditor$__Closure_272_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
static void  __fini___Closure_272_30(HoroEditor$__Closure_272_30 *  self);
static HoroEditor$__Closure_272_30*  __make___Closure_272_30(HoroEditor$__Closure_272_30 **  __outRef__, HoroEditor$__Block_251_29 *  __var___Block_251_29, HoroEditor$__Block_204_23 *  __var___Block_204_23);
static void  __fn___Closure_288_45(HoroEditor$__Closure_288_45 *  self, SuiCore$ViewBase *  v);
static void  __fini___Closure_288_45(HoroEditor$__Closure_288_45 *  self);
static HoroEditor$__Closure_288_45*  __make___Closure_288_45(HoroEditor$__Closure_288_45 **  __outRef__, HoroEditor$__Block_204_23 *  __var___Block_204_23, HoroEditor$__Block_272_78 *  __var___Block_272_78);
static void  __fn___Closure_hi_289(HoroEditor$__Closure_hi_289 *  self);
static void  __fini___Closure_hi_289(HoroEditor$__Closure_hi_289 *  self);
static HoroEditor$__Closure_hi_289*  __make___Closure_hi_289(HoroEditor$__Closure_hi_289 **  __outRef__, HoroEditor$__Block_204_23 *  __var___Block_204_23);



//vtable instance
Vtable_HoroEditor$HoroSceneHierView _vtable_HoroEditor$HoroSceneHierView;

// init meta

void HoroEditor$HoroSceneHierView_initMeta(Vtable_HoroEditor$HoroSceneHierView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_HoroEditor$HoroEditCtx_init(0)), offsetof(HoroEditor$HoroSceneHierView, editCtx), true, false, 1);
	orc_metaField_class(&pNext, "editor", ((Vtable_Object*)Vtable_HoroEditor$HoroEditor_init(0)), offsetof(HoroEditor$HoroSceneHierView, editor), true, false, 1);

	orc_metaField_method(&pNext, "onUnmouting", offsetof(HoroEditor$HoroSceneHierView, onUnmouting));
	orc_metaField_method(&pNext, "_routeRightMenu", offsetof(HoroEditor$HoroSceneHierView, _routeRightMenu));
	orc_metaField_method(&pNext, "_onItemRightClick", offsetof(HoroEditor$HoroSceneHierView, _onItemRightClick));
	orc_metaField_method(&pNext, "_onEvent_forItemView", offsetof(HoroEditor$HoroSceneHierView, _onEvent_forItemView));
}


// vtable init


Vtable_HoroEditor$HoroSceneHierView* Vtable_HoroEditor$HoroSceneHierView_init(Vtable_HoroEditor$HoroSceneHierView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroSceneHierView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroSceneHierView_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroSceneHierView";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroSceneHierView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroSceneHierView_fini(HoroEditor$HoroSceneHierView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void HoroEditor$HoroSceneHierView_init_fields(HoroEditor$HoroSceneHierView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroSceneHierView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroSceneHierView*)self)->editCtx, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroSceneHierView*)self)->editor, NULL);
    }
	((Object*)self)->ctor = (void*)HoroEditor$HoroSceneHierView$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)HoroEditor$HoroSceneHierView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)HoroEditor$HoroSceneHierView$onMounted;
	((HoroEditor$HoroSceneHierView*)self)->onUnmouting = (void*)HoroEditor$HoroSceneHierView$onUnmouting;
	((HoroEditor$HoroSceneHierView*)self)->_routeRightMenu = (void*)HoroEditor$HoroSceneHierView$_routeRightMenu;
	((HoroEditor$HoroSceneHierView*)self)->_onItemRightClick = (void*)HoroEditor$HoroSceneHierView$_onItemRightClick;
	((HoroEditor$HoroSceneHierView*)self)->_onEvent_forItemView = (void*)HoroEditor$HoroSceneHierView$_onEvent_forItemView;
	((SuiCore$Node*)self)->react = (void*)HoroEditor$HoroSceneHierView$react;
}

// init function

void HoroEditor$HoroSceneHierView_init(HoroEditor$HoroSceneHierView *self, void *pOwner){
    Vtable_HoroEditor$HoroSceneHierView_init(&_vtable_HoroEditor$HoroSceneHierView);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroSceneHierView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroSceneHierView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroSceneHierView * HoroEditor$HoroSceneHierView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroSceneHierView *self = calloc(1, sizeof(HoroEditor$HoroSceneHierView));
	
    HoroEditor$HoroSceneHierView_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroSceneHierView$ctor(HoroEditor$HoroSceneHierView *  self){
	SuiCore$Listener$ctor(self) ;
}


void  HoroEditor$HoroSceneHierView$onListenerEvent(HoroEditor$HoroSceneHierView *  self, SuiCore$Event *  event){
	if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_HoroEditor$EventHoroSceneChanged_init(NULL))) {
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  HoroEditor$HoroSceneHierView$onMounted(HoroEditor$HoroSceneHierView *  self){
	SuiCore$Node$onMounted(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  HoroEditor$HoroSceneHierView$onUnmouting(HoroEditor$HoroSceneHierView *  self){
	SuiCore$Node$onUnmounting(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  HoroEditor$HoroSceneHierView$_routeRightMenu(HoroEditor$HoroSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$ANode*  node){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(node);

	if (!item->cmd) {
		return ; 
	}
	if (Orc$String$startsWith(item->cmd, "PreviewCamera") ) {
		SuiDesigner$UiAction_previewCamera(self->editCtx->sceneView->drawCtx, (Sgl$Camera * )node) ;
	}
	if (Orc$String$startsWith(item->cmd, "AddView/") ) {
		SuiDialog$MessageDialog_alert(item->cmd->str, "tip") ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  viewName = Orc$Path_basename((viewName = NULL,&viewName), item->cmd->str) ;
		HoroEditor$UiAct_addView(self->editor, node, viewName) ;
		return ; 
	}
	if (Orc$String$equals(item->cmd, "RenameView") ) {
		return ; 
	}
	if (Orc$String$equals(item->cmd, "DeleteView") ) {
		node->removeSelf(node) ;
		SuiCore$Emitter *  tmpThis_1 = NULL;
		URGC_VAR_CLEANUP_CLASS HoroEditor$EventHoroSceneChanged*  tmpNewOwner_1 = NULL;
		(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, HoroEditor$EventHoroSceneChanged_new(&tmpNewOwner_1) ) ;
		return ; 
	}
	else if (Orc$String$equals(item->cmd, "LocateView") ) {
		
	}
	else if (Orc$String$equals(item->cmd, "CopyView") ) {
		
	}
	else if (Orc$String$equals(item->cmd, "PasteView") ) {
		
	}
	else if (Orc$String$equals(item->cmd, "CutView") ) {
		
	}
}


void  HoroEditor$HoroSceneHierView$_onItemRightClick(HoroEditor$HoroSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item){
	URGC_VAR_CLEANUP HoroEditor$__Block_131_68*  __var___Block_131_68 = (__var___Block_131_68=NULL,urgc_init_var((void**)&__var___Block_131_68, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_131_68) , __finiBlock___Block_131_68) ));
	urgc_set_field_class(__var___Block_131_68, (void * )offsetof(HoroEditor$__Block_131_68, self) , self) ;
	((SuiCore$Event * )me)->stopPropagation(me) ;
	if (Orc_instanceof((Object*)item, (Vtable_Object*)Vtable_SuiDesigner$ANode_init(NULL))) {
		URGC_VAR_CLEANUP HoroEditor$__Block_133_33*  __var___Block_133_33 = (__var___Block_133_33=NULL,urgc_init_var((void**)&__var___Block_133_33, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_133_33) , __finiBlock___Block_133_33) ));
		urgc_set_field_class(__var___Block_133_33, (void * )offsetof(HoroEditor$__Block_133_33, node) , (SuiDesigner$ANode* )item) ;
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
		{
			SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
			
		
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_137*  tmpReturn_2 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_137(&tmpReturn_2, __var___Block_131_68, __var___Block_133_33) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_147_16 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "重命名") , onActive) , *o = __scopeVar_147_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "RenameView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_148_16 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "添加") , onActive) , *o = __scopeVar_148_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "RenameView") ) ;
				URGC_VAR_CLEANUP_CLASS SuiCore$NodeLib*  lib = (lib=NULL,urgc_init_var_class((void**)&lib, SuiCore$NodeLib_use() ));
				for (int  i = 0; i < lib->list->size(lib->list) ; i++) {
					SuiCore$NodeRegisterInfo *  info = (SuiCore$NodeRegisterInfo * )lib->list->get(lib->list, i) ;
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_154_24 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, info->className) , onActive) , *o = __scopeVar_154_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$String$add(Orc$str(&tmpReturn_11, "AddView/") , info->className) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_12 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_175_16 = SuiView$mkMenuNativeItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "删除") , onActive) , *o = __scopeVar_175_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_14, "DeleteView") ) ;
			}
			if (Orc_instanceof((Object*)__var___Block_133_33->node, (Vtable_Object*)Vtable_Sgl$Camera_init(NULL))) {
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_15 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_178_20 = SuiView$mkMenuNativeItem(&tmpReturn_15, o, Orc$str(&tmpReturn_16, "预览相机") , onActive) , *o = __scopeVar_178_20;
					
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_17, "PreviewCamera") ) ;
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_18 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_19 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_182_16 = SuiView$mkMenuNativeItem(&tmpReturn_18, o, Orc$str(&tmpReturn_19, "定位") , onActive) , *o = __scopeVar_182_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_20, "LocateView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_21 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_183_16 = SuiView$mkMenuNativeItem(&tmpReturn_21, o, Orc$str(&tmpReturn_22, "复制") , onActive) , *o = __scopeVar_183_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_23 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_23, "CopyView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_24 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_25 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_184_16 = SuiView$mkMenuNativeItem(&tmpReturn_24, o, Orc$str(&tmpReturn_25, "粘贴") , onActive) , *o = __scopeVar_184_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_26, "PasteView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_27 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_185_16 = SuiView$mkMenuNativeItem(&tmpReturn_27, o, Orc$str(&tmpReturn_28, "剪切") , onActive) , *o = __scopeVar_185_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_29 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_29, "CutView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
			n->create(n, o) ;
			n->showAtMouse(n) ;
		}
	}
}


void  HoroEditor$HoroSceneHierView$_onEvent_forItemView(HoroEditor$HoroSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			self->_onItemRightClick(self, me, view, item) ;
			return ; 
		}
	}
}


void  HoroEditor$HoroSceneHierView$react(HoroEditor$HoroSceneHierView *  self, int  xxx){
	URGC_VAR_CLEANUP HoroEditor$__Block_204_23*  __var___Block_204_23 = (__var___Block_204_23=NULL,urgc_init_var((void**)&__var___Block_204_23, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_204_23) , __finiBlock___Block_204_23) ));
	__var___Block_204_23->xxx = xxx;
	urgc_set_field_class(__var___Block_204_23, (void * )offsetof(HoroEditor$__Block_204_23, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	HoroEditor$HoroSceneHierView *  o = (HoroEditor$HoroSceneHierView * )self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_221_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_221_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_221_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->grow = 1;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_4 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_231_8 = SuiView$mkScrollArea(&tmpReturn_4, o, 0) , *o = __scopeVar_231_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_231_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_5, "stretch") ) ;
		o->useMinWidthConstraint = true;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_240_12 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_240_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_240_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TreeView*  tmpReturn_7 = NULL;
		{
			SuiView$TreeView*  __scopeVar_251_12 = SuiView$mkTreeView(&tmpReturn_7, o, 0) , *o = __scopeVar_251_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_251_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Block_251_29*  __var___Block_251_29 = (__var___Block_251_29=NULL,urgc_init_var((void**)&__var___Block_251_29, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_251_29) , __finiBlock___Block_251_29) ));
			urgc_set_field_class(__var___Block_251_29, (void * )offsetof(HoroEditor$__Block_251_29, treeView) , o) ;
			self->editCtx->setState(self->editCtx, o->state) ;
			urgc_set_field_class(o->state, (void * )offsetof(SuiView$TreeState, roots) , self->editCtx->roots) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_259_32*  tmpReturn_8 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getId) , __make___Closure_259_32(&tmpReturn_8) ) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_263_42*  tmpReturn_9 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getItemChildren) , __make___Closure_263_42(&tmpReturn_9) ) ;
			Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "maxOrStretch") ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_269_42*  tmpReturn_10 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, cbOnEvent_forItemView) , __make___Closure_269_42(&tmpReturn_10, __var___Block_204_23) ) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_272_30*  tmpReturn_11 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, reactItem) , __make___Closure_272_30(&tmpReturn_11, __var___Block_251_29, __var___Block_204_23) ) ;
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



static void  __finiBlock___Block_131_68(HoroEditor$__Block_131_68 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_131_68, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_133_33(HoroEditor$__Block_133_33 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_133_33, node) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_204_23(HoroEditor$__Block_204_23 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_204_23, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_251_29(HoroEditor$__Block_251_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_251_29, treeView) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_272_78(HoroEditor$__Block_272_78 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_272_78, s) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_onActive_137(HoroEditor$__Closure_onActive_137 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n", item->cmd->str, item->label->str) ;
	self->__var___Block_131_68->self->_routeRightMenu(self->__var___Block_131_68->self, item, self->__var___Block_133_33->node) ;
}

static void  __fini___Closure_onActive_137(HoroEditor$__Closure_onActive_137 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_137, __var___Block_131_68) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_137, __var___Block_133_33) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_onActive_137*  __make___Closure_onActive_137(HoroEditor$__Closure_onActive_137 **  __outRef__, HoroEditor$__Block_131_68 *  __var___Block_131_68, HoroEditor$__Block_133_33 *  __var___Block_133_33){
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_137*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_onActive_137) , __fini___Closure_onActive_137) ));
	self->invoke = __fn___Closure_onActive_137;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_137, __var___Block_131_68) , __var___Block_131_68) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_137, __var___Block_133_33) , __var___Block_133_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$String*  __fn___Closure_259_32(Orc$String **  __outRef__, HoroEditor$__Closure_259_32 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$ANode* )item));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, s->getId(&tmpReturn_1, s) ) ; 
}

static void  __fini___Closure_259_32(HoroEditor$__Closure_259_32 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_259_32*  __make___Closure_259_32(HoroEditor$__Closure_259_32 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_259_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_259_32) , __fini___Closure_259_32) ));
	self->invoke = __fn___Closure_259_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$List*  __fn___Closure_263_42(Orc$List **  __outRef__, HoroEditor$__Closure_263_42 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$ANode* )item));
	return urgc_set_var_for_return_class((void ** )__outRef__, s->children) ; 
}

static void  __fini___Closure_263_42(HoroEditor$__Closure_263_42 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_263_42*  __make___Closure_263_42(HoroEditor$__Closure_263_42 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_263_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_263_42) , __fini___Closure_263_42) ));
	self->invoke = __fn___Closure_263_42;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_269_42(HoroEditor$__Closure_269_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item){
	self->__var___Block_204_23->self->_onEvent_forItemView(self->__var___Block_204_23->self, e, n, item) ;
}

static void  __fini___Closure_269_42(HoroEditor$__Closure_269_42 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_269_42, __var___Block_204_23) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_269_42*  __make___Closure_269_42(HoroEditor$__Closure_269_42 **  __outRef__, HoroEditor$__Block_204_23 *  __var___Block_204_23){
	URGC_VAR_CLEANUP HoroEditor$__Closure_269_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_269_42) , __fini___Closure_269_42) ));
	self->invoke = __fn___Closure_269_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_269_42, __var___Block_204_23) , __var___Block_204_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_272_30(HoroEditor$__Closure_272_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep){
	URGC_VAR_CLEANUP HoroEditor$__Block_272_78*  __var___Block_272_78 = (__var___Block_272_78=NULL,urgc_init_var((void**)&__var___Block_272_78, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_272_78) , __finiBlock___Block_272_78) ));
	SuiCore$Node *  o = parentNode;
	urgc_set_field_class(__var___Block_272_78, (void * )offsetof(HoroEditor$__Block_272_78, s) , (SuiDesigner$ANode* )item) ;
	int  idx = -1;
	if (Orc_instanceof((Object*)parentNode, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )parentNode;
		idx = vb->viewIndexInParent(vb) ;
	}
	bool  isSelected = self->__var___Block_251_29->treeView->state->isSelected(self->__var___Block_251_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_1 = NULL;
	{
		SuiView$HoverViewEffect*  __scopeVar_284_20 = SuiView$mkHoverViewEffect(&tmpReturn_1, o, 0) , *o = __scopeVar_284_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_284_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->isActive = isSelected;
		URGC_VAR_CLEANUP HoroEditor$__Closure_288_45*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, cbOnHoverChanged) , __make___Closure_288_45(&tmpReturn_2, self->__var___Block_204_23, __var___Block_272_78) ) ;
	}
	bool  hasKids = __var___Block_272_78->s->children->size(__var___Block_272_78->s->children)  > 0;
	bool  isOpend = self->__var___Block_251_29->treeView->state->isOpend(self->__var___Block_251_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_3 = NULL;
	{
		SuiView$ImageView*  __scopeVar_307_20 = SuiView$mkImageView(&tmpReturn_3, o, 0) , *o = __scopeVar_307_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_307_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->width = 12;
		((SuiCore$View * )o)->height = 12;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		o->setSrc(o, hasKids ? isOpend ? Orc$Path_resolveFromExecutionDir(&tmpReturn_4, "asset/icon/arrow-down.png")  : Orc$Path_resolveFromExecutionDir(&tmpReturn_5, "asset/icon/arrow-right.png")  : NULL) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_6 = NULL;
	{
		SuiView$TextView*  __scopeVar_331_20 = SuiView$mkTextView(&tmpReturn_6, o, 0) , *o = __scopeVar_331_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_331_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		Vtable_Object *  vt = orc_getVtableByObject(__var___Block_272_78->s) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  name = __var___Block_272_78->s->getName((name = NULL,&name), __var___Block_272_78->s) ;
		if (name && Orc$String$notEmpty(name) ) {
			o->setText(o, name) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setText(o, Orc$str(&tmpReturn_7, vt->className) ) ;
		}
	}
}

static void  __fini___Closure_272_30(HoroEditor$__Closure_272_30 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_272_30, __var___Block_251_29) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_272_30, __var___Block_204_23) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_272_30*  __make___Closure_272_30(HoroEditor$__Closure_272_30 **  __outRef__, HoroEditor$__Block_251_29 *  __var___Block_251_29, HoroEditor$__Block_204_23 *  __var___Block_204_23){
	URGC_VAR_CLEANUP HoroEditor$__Closure_272_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_272_30) , __fini___Closure_272_30) ));
	self->invoke = __fn___Closure_272_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_272_30, __var___Block_251_29) , __var___Block_251_29) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_272_30, __var___Block_204_23) , __var___Block_204_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_288_45(HoroEditor$__Closure_288_45 *  self, SuiCore$ViewBase *  v){
	URGC_VAR_CLEANUP void  (**hi)(void *  self) = NULL;
	URGC_VAR_CLEANUP HoroEditor$__Closure_hi_289*  tmpReturn_1 = NULL;
	(urgc_set_var(&hi, __make___Closure_hi_289(&tmpReturn_1, self->__var___Block_204_23) ) );
	if (v->hover) {
		urgc_set_field_class(self->__var___Block_204_23->self->editCtx, (void * )offsetof(HoroEditor$HoroEditCtx, hoverNode) , self->__var___Block_272_78->s) ;
	}
	else {
		urgc_set_field_class(self->__var___Block_204_23->self->editCtx, (void * )offsetof(HoroEditor$HoroEditCtx, hoverNode) , NULL) ;
	}
	printf("Scene.cbOnHoverChanged:%d\n", v->hover) ;
}

static void  __fini___Closure_288_45(HoroEditor$__Closure_288_45 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_288_45, __var___Block_204_23) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_288_45, __var___Block_272_78) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_288_45*  __make___Closure_288_45(HoroEditor$__Closure_288_45 **  __outRef__, HoroEditor$__Block_204_23 *  __var___Block_204_23, HoroEditor$__Block_272_78 *  __var___Block_272_78){
	URGC_VAR_CLEANUP HoroEditor$__Closure_288_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_288_45) , __fini___Closure_288_45) ));
	self->invoke = __fn___Closure_288_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_288_45, __var___Block_204_23) , __var___Block_204_23) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_288_45, __var___Block_272_78) , __var___Block_272_78) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_hi_289(HoroEditor$__Closure_hi_289 *  self){
	printf("xxx:%d\n", self->__var___Block_204_23->xxx) ;
}

static void  __fini___Closure_hi_289(HoroEditor$__Closure_hi_289 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_hi_289, __var___Block_204_23) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_hi_289*  __make___Closure_hi_289(HoroEditor$__Closure_hi_289 **  __outRef__, HoroEditor$__Block_204_23 *  __var___Block_204_23){
	URGC_VAR_CLEANUP HoroEditor$__Closure_hi_289*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_hi_289) , __fini___Closure_hi_289) ));
	self->invoke = __fn___Closure_hi_289;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_hi_289, __var___Block_204_23) , __var___Block_204_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

HoroEditor$HoroSceneHierView*  HoroEditor$mkHoroSceneHierView(HoroEditor$HoroSceneHierView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (HoroEditor$HoroSceneHierView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_HoroEditor$HoroSceneHierView_init(NULL)) ) ; 
}

void  HoroEditor$testHoroSceneHier(){
	printf("testScene\n") ;
}



