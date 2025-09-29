
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
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Camera_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_127_68 SuiDesigner$__Block_127_68;

typedef struct tagSuiDesigner$__Block_129_32 SuiDesigner$__Block_129_32;

typedef struct tagSuiDesigner$__Block_200_23 SuiDesigner$__Block_200_23;

typedef struct tagSuiDesigner$__Block_247_29 SuiDesigner$__Block_247_29;

typedef struct tagSuiDesigner$__Block_268_78 SuiDesigner$__Block_268_78;

typedef struct tagSuiDesigner$__Closure_onActive_133 SuiDesigner$__Closure_onActive_133;

typedef struct tagSuiDesigner$__Closure_255_32 SuiDesigner$__Closure_255_32;

typedef struct tagSuiDesigner$__Closure_259_42 SuiDesigner$__Closure_259_42;

typedef struct tagSuiDesigner$__Closure_265_42 SuiDesigner$__Closure_265_42;

typedef struct tagSuiDesigner$__Closure_268_30 SuiDesigner$__Closure_268_30;

typedef struct tagSuiDesigner$__Closure_284_45 SuiDesigner$__Closure_284_45;

typedef struct tagSuiDesigner$__Closure_hi_285 SuiDesigner$__Closure_hi_285;



struct tagSuiDesigner$__Block_127_68 {
	SuiDesigner$HoroSceneHierView*  self ;
};





struct tagSuiDesigner$__Block_129_32 {
	SuiCore$Node*  node ;
};





struct tagSuiDesigner$__Block_200_23 {
	SuiDesigner$HoroSceneHierView*  self ;
	int  xxx ;
};





struct tagSuiDesigner$__Block_247_29 {
	SuiView$TreeView*  treeView ;
};





struct tagSuiDesigner$__Block_268_78 {
	SuiDesigner$ANode*  s ;
};





struct tagSuiDesigner$__Closure_onActive_133 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_133 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_127_68*  __var___Block_127_68 ;
	SuiDesigner$__Block_129_32*  __var___Block_129_32 ;
};





struct tagSuiDesigner$__Closure_255_32 {
	Orc$String*  (*invoke)(SuiDesigner$__Closure_255_32 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_259_42 {
	Orc$List*  (*invoke)(SuiDesigner$__Closure_259_42 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_265_42 {
	void  (*invoke)(SuiDesigner$__Closure_265_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_200_23*  __var___Block_200_23 ;
};





struct tagSuiDesigner$__Closure_268_30 {
	void  (*invoke)(SuiDesigner$__Closure_268_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_247_29*  __var___Block_247_29 ;
	SuiDesigner$__Block_200_23*  __var___Block_200_23 ;
};





struct tagSuiDesigner$__Closure_284_45 {
	void  (*invoke)(SuiDesigner$__Closure_284_45 *  self, SuiCore$ViewBase *  v);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_200_23*  __var___Block_200_23 ;
	SuiDesigner$__Block_268_78*  __var___Block_268_78 ;
};





struct tagSuiDesigner$__Closure_hi_285 {
	void  (*invoke)(SuiDesigner$__Closure_hi_285 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_200_23*  __var___Block_200_23 ;
};





// static function declaration
static void  __finiBlock___Block_127_68(SuiDesigner$__Block_127_68 *  self);
static void  __finiBlock___Block_129_32(SuiDesigner$__Block_129_32 *  self);
static void  __finiBlock___Block_200_23(SuiDesigner$__Block_200_23 *  self);
static void  __finiBlock___Block_247_29(SuiDesigner$__Block_247_29 *  self);
static void  __finiBlock___Block_268_78(SuiDesigner$__Block_268_78 *  self);
static void  __fn___Closure_onActive_133(SuiDesigner$__Closure_onActive_133 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_133(SuiDesigner$__Closure_onActive_133 *  self);
static SuiDesigner$__Closure_onActive_133*  __make___Closure_onActive_133(SuiDesigner$__Closure_onActive_133 **  __outRef__, SuiDesigner$__Block_127_68 *  __var___Block_127_68, SuiDesigner$__Block_129_32 *  __var___Block_129_32);
static Orc$String*  __fn___Closure_255_32(Orc$String **  __outRef__, SuiDesigner$__Closure_255_32 *  self, Object *  item);
static void  __fini___Closure_255_32(SuiDesigner$__Closure_255_32 *  self);
static SuiDesigner$__Closure_255_32*  __make___Closure_255_32(SuiDesigner$__Closure_255_32 **  __outRef__);
static Orc$List*  __fn___Closure_259_42(Orc$List **  __outRef__, SuiDesigner$__Closure_259_42 *  self, Object *  item);
static void  __fini___Closure_259_42(SuiDesigner$__Closure_259_42 *  self);
static SuiDesigner$__Closure_259_42*  __make___Closure_259_42(SuiDesigner$__Closure_259_42 **  __outRef__);
static void  __fn___Closure_265_42(SuiDesigner$__Closure_265_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item);
static void  __fini___Closure_265_42(SuiDesigner$__Closure_265_42 *  self);
static SuiDesigner$__Closure_265_42*  __make___Closure_265_42(SuiDesigner$__Closure_265_42 **  __outRef__, SuiDesigner$__Block_200_23 *  __var___Block_200_23);
static void  __fn___Closure_268_30(SuiDesigner$__Closure_268_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
static void  __fini___Closure_268_30(SuiDesigner$__Closure_268_30 *  self);
static SuiDesigner$__Closure_268_30*  __make___Closure_268_30(SuiDesigner$__Closure_268_30 **  __outRef__, SuiDesigner$__Block_247_29 *  __var___Block_247_29, SuiDesigner$__Block_200_23 *  __var___Block_200_23);
static void  __fn___Closure_284_45(SuiDesigner$__Closure_284_45 *  self, SuiCore$ViewBase *  v);
static void  __fini___Closure_284_45(SuiDesigner$__Closure_284_45 *  self);
static SuiDesigner$__Closure_284_45*  __make___Closure_284_45(SuiDesigner$__Closure_284_45 **  __outRef__, SuiDesigner$__Block_200_23 *  __var___Block_200_23, SuiDesigner$__Block_268_78 *  __var___Block_268_78);
static void  __fn___Closure_hi_285(SuiDesigner$__Closure_hi_285 *  self);
static void  __fini___Closure_hi_285(SuiDesigner$__Closure_hi_285 *  self);
static SuiDesigner$__Closure_hi_285*  __make___Closure_hi_285(SuiDesigner$__Closure_hi_285 **  __outRef__, SuiDesigner$__Block_200_23 *  __var___Block_200_23);



//vtable instance
Vtable_SuiDesigner$HoroSceneHierView _vtable_SuiDesigner$HoroSceneHierView;

// init meta

void SuiDesigner$HoroSceneHierView_initMeta(Vtable_SuiDesigner$HoroSceneHierView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_SuiDesigner$HoroEditCtx_init(0)), offsetof(SuiDesigner$HoroSceneHierView, editCtx), true, false, 1);

	orc_metaField_method(&pNext, "onUnmouting", offsetof(SuiDesigner$HoroSceneHierView, onUnmouting));
	orc_metaField_method(&pNext, "_routeRightMenu", offsetof(SuiDesigner$HoroSceneHierView, _routeRightMenu));
	orc_metaField_method(&pNext, "_onItemRightClick", offsetof(SuiDesigner$HoroSceneHierView, _onItemRightClick));
	orc_metaField_method(&pNext, "_onEvent_forItemView", offsetof(SuiDesigner$HoroSceneHierView, _onEvent_forItemView));
}


// vtable init


Vtable_SuiDesigner$HoroSceneHierView* Vtable_SuiDesigner$HoroSceneHierView_init(Vtable_SuiDesigner$HoroSceneHierView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$HoroSceneHierView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$HoroSceneHierView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$HoroSceneHierView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$HoroSceneHierView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$HoroSceneHierView_fini(SuiDesigner$HoroSceneHierView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiDesigner$HoroSceneHierView_init_fields(SuiDesigner$HoroSceneHierView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$HoroSceneHierView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$HoroSceneHierView*)self)->editCtx, NULL);
    }
	((Object*)self)->ctor = (void*)SuiDesigner$HoroSceneHierView$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiDesigner$HoroSceneHierView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$HoroSceneHierView$onMounted;
	((SuiDesigner$HoroSceneHierView*)self)->onUnmouting = (void*)SuiDesigner$HoroSceneHierView$onUnmouting;
	((SuiDesigner$HoroSceneHierView*)self)->_routeRightMenu = (void*)SuiDesigner$HoroSceneHierView$_routeRightMenu;
	((SuiDesigner$HoroSceneHierView*)self)->_onItemRightClick = (void*)SuiDesigner$HoroSceneHierView$_onItemRightClick;
	((SuiDesigner$HoroSceneHierView*)self)->_onEvent_forItemView = (void*)SuiDesigner$HoroSceneHierView$_onEvent_forItemView;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$HoroSceneHierView$react;
}

// init function

void SuiDesigner$HoroSceneHierView_init(SuiDesigner$HoroSceneHierView *self, void *pOwner){
    Vtable_SuiDesigner$HoroSceneHierView_init(&_vtable_SuiDesigner$HoroSceneHierView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$HoroSceneHierView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$HoroSceneHierView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$HoroSceneHierView * SuiDesigner$HoroSceneHierView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$HoroSceneHierView *self = calloc(1, sizeof(SuiDesigner$HoroSceneHierView));
	
    SuiDesigner$HoroSceneHierView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$HoroSceneHierView$ctor(SuiDesigner$HoroSceneHierView *  self){
	SuiCore$Listener$ctor(self) ;
}


void  SuiDesigner$HoroSceneHierView$onListenerEvent(SuiDesigner$HoroSceneHierView *  self, SuiCore$Event *  event){
	if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventHoroSceneChanged_init(NULL))) {
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiDesigner$HoroSceneHierView$onMounted(SuiDesigner$HoroSceneHierView *  self){
	SuiCore$Node$onMounted(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  SuiDesigner$HoroSceneHierView$onUnmouting(SuiDesigner$HoroSceneHierView *  self){
	SuiCore$Node$onUnmounting(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  SuiDesigner$HoroSceneHierView$_routeRightMenu(SuiDesigner$HoroSceneHierView *  self, SuiView$MenuNativeItem *  item, SuiCore$Node*  node){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(node);

	if (!item->cmd) {
		return ; 
	}
	if (Orc$String$startsWith(item->cmd, "PreviewCamera") ) {
		SuiDesigner$UiAction_previewCamera(self->editCtx->sceneView->drawCtx, (Sgl$Camera * )node) ;
	}
	if (Orc$String$startsWith(item->cmd, "AddView/") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  viewName = Orc$Path_basename((viewName = NULL,&viewName), item->cmd->str) ;
		return ; 
	}
	if (Orc$String$equals(item->cmd, "RenameView") ) {
		return ; 
	}
	if (Orc$String$equals(item->cmd, "DeleteView") ) {
		node->removeSelf(node) ;
		SuiCore$Emitter *  tmpThis_1 = NULL;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventHoroSceneChanged*  tmpNewOwner_1 = NULL;
		(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, SuiDesigner$EventHoroSceneChanged_new(&tmpNewOwner_1) ) ;
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


void  SuiDesigner$HoroSceneHierView$_onItemRightClick(SuiDesigner$HoroSceneHierView *  self, SuiCore$MouseEvent *  me, SuiCore$Node *  view, Object *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_127_68*  __var___Block_127_68 = (__var___Block_127_68=NULL,urgc_init_var((void**)&__var___Block_127_68, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_127_68) , __finiBlock___Block_127_68) ));
	urgc_set_field_class(__var___Block_127_68, (void * )offsetof(SuiDesigner$__Block_127_68, self) , self) ;
	((SuiCore$Event * )me)->stopPropagation(me) ;
	if (Orc_instanceof((Object*)item, (Vtable_Object*)Vtable_SuiCore$Node_init(NULL))) {
		URGC_VAR_CLEANUP SuiDesigner$__Block_129_32*  __var___Block_129_32 = (__var___Block_129_32=NULL,urgc_init_var((void**)&__var___Block_129_32, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_129_32) , __finiBlock___Block_129_32) ));
		urgc_set_field_class(__var___Block_129_32, (void * )offsetof(SuiDesigner$__Block_129_32, node) , (SuiCore$Node* )item) ;
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
		{
			SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
			
		
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_133*  tmpReturn_2 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_133(&tmpReturn_2, __var___Block_127_68, __var___Block_129_32) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_143_16 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "重命名") , onActive) , *o = __scopeVar_143_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "RenameView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_144_16 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "添加") , onActive) , *o = __scopeVar_144_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "RenameView") ) ;
				URGC_VAR_CLEANUP_CLASS SuiCore$NodeLib*  lib = (lib=NULL,urgc_init_var_class((void**)&lib, SuiCore$NodeLib_use() ));
				for (int  i = 0; i < lib->list->size(lib->list) ; i++) {
					SuiCore$NodeRegisterInfo *  info = (SuiCore$NodeRegisterInfo * )lib->list->get(lib->list, i) ;
					URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					{
						SuiView$MenuNativeItem*  __scopeVar_150_24 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, info->className) , onActive) , *o = __scopeVar_150_24;
						
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$String$add(Orc$str(&tmpReturn_11, "AddView/") , info->className) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_12 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_171_16 = SuiView$mkMenuNativeItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "删除") , onActive) , *o = __scopeVar_171_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_14, "DeleteView") ) ;
			}
			if (Orc_instanceof((Object*)__var___Block_129_32->node, (Vtable_Object*)Vtable_Sgl$Camera_init(NULL))) {
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_15 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_174_20 = SuiView$mkMenuNativeItem(&tmpReturn_15, o, Orc$str(&tmpReturn_16, "预览相机") , onActive) , *o = __scopeVar_174_20;
					
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_17, "PreviewCamera") ) ;
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_18 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_19 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_178_16 = SuiView$mkMenuNativeItem(&tmpReturn_18, o, Orc$str(&tmpReturn_19, "定位") , onActive) , *o = __scopeVar_178_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_20, "LocateView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_21 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_179_16 = SuiView$mkMenuNativeItem(&tmpReturn_21, o, Orc$str(&tmpReturn_22, "复制") , onActive) , *o = __scopeVar_179_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_23 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_23, "CopyView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_24 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_25 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_180_16 = SuiView$mkMenuNativeItem(&tmpReturn_24, o, Orc$str(&tmpReturn_25, "粘贴") , onActive) , *o = __scopeVar_180_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_26, "PasteView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_27 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_181_16 = SuiView$mkMenuNativeItem(&tmpReturn_27, o, Orc$str(&tmpReturn_28, "剪切") , onActive) , *o = __scopeVar_181_16;
				
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_29 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_29, "CutView") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
			n->create(n, o) ;
			n->showAtMouse(n) ;
		}
	}
}


void  SuiDesigner$HoroSceneHierView$_onEvent_forItemView(SuiDesigner$HoroSceneHierView *  self, SuiCore$Event *  e, SuiCore$Node *  view, Object *  item){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			self->_onItemRightClick(self, me, view, item) ;
			return ; 
		}
	}
}


void  SuiDesigner$HoroSceneHierView$react(SuiDesigner$HoroSceneHierView *  self, int  xxx){
	URGC_VAR_CLEANUP SuiDesigner$__Block_200_23*  __var___Block_200_23 = (__var___Block_200_23=NULL,urgc_init_var((void**)&__var___Block_200_23, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_200_23) , __finiBlock___Block_200_23) ));
	__var___Block_200_23->xxx = xxx;
	urgc_set_field_class(__var___Block_200_23, (void * )offsetof(SuiDesigner$__Block_200_23, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiDesigner$HoroSceneHierView *  o = (SuiDesigner$HoroSceneHierView * )self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_217_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_217_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_217_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->grow = 1;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_4 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_227_8 = SuiView$mkScrollArea(&tmpReturn_4, o, 0) , *o = __scopeVar_227_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_227_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_5, "stretch") ) ;
		o->useMinWidthConstraint = true;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_236_12 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_236_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_236_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TreeView*  tmpReturn_7 = NULL;
		{
			SuiView$TreeView*  __scopeVar_247_12 = SuiView$mkTreeView(&tmpReturn_7, o, 0) , *o = __scopeVar_247_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_247_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP SuiDesigner$__Block_247_29*  __var___Block_247_29 = (__var___Block_247_29=NULL,urgc_init_var((void**)&__var___Block_247_29, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_247_29) , __finiBlock___Block_247_29) ));
			urgc_set_field_class(__var___Block_247_29, (void * )offsetof(SuiDesigner$__Block_247_29, treeView) , o) ;
			self->editCtx->setState(self->editCtx, o->state) ;
			urgc_set_field_class(o->state, (void * )offsetof(SuiView$TreeState, roots) , self->editCtx->roots) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_255_32*  tmpReturn_8 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getId) , __make___Closure_255_32(&tmpReturn_8) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_259_42*  tmpReturn_9 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getItemChildren) , __make___Closure_259_42(&tmpReturn_9) ) ;
			Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "maxOrStretch") ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_265_42*  tmpReturn_10 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, cbOnEvent_forItemView) , __make___Closure_265_42(&tmpReturn_10, __var___Block_200_23) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_268_30*  tmpReturn_11 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, reactItem) , __make___Closure_268_30(&tmpReturn_11, __var___Block_247_29, __var___Block_200_23) ) ;
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



static void  __finiBlock___Block_127_68(SuiDesigner$__Block_127_68 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_127_68, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_129_32(SuiDesigner$__Block_129_32 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_129_32, node) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_200_23(SuiDesigner$__Block_200_23 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_200_23, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_247_29(SuiDesigner$__Block_247_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_247_29, treeView) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_268_78(SuiDesigner$__Block_268_78 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_268_78, s) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_onActive_133(SuiDesigner$__Closure_onActive_133 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n", item->cmd->str, item->label->str) ;
	self->__var___Block_127_68->self->_routeRightMenu(self->__var___Block_127_68->self, item, self->__var___Block_129_32->node) ;
}

static void  __fini___Closure_onActive_133(SuiDesigner$__Closure_onActive_133 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_133, __var___Block_127_68) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_133, __var___Block_129_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_133*  __make___Closure_onActive_133(SuiDesigner$__Closure_onActive_133 **  __outRef__, SuiDesigner$__Block_127_68 *  __var___Block_127_68, SuiDesigner$__Block_129_32 *  __var___Block_129_32){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_133*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_133) , __fini___Closure_onActive_133) ));
	self->invoke = __fn___Closure_onActive_133;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_133, __var___Block_127_68) , __var___Block_127_68) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_133, __var___Block_129_32) , __var___Block_129_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$String*  __fn___Closure_255_32(Orc$String **  __outRef__, SuiDesigner$__Closure_255_32 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$ANode* )item));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, s->getId(&tmpReturn_1, s) ) ; 
}

static void  __fini___Closure_255_32(SuiDesigner$__Closure_255_32 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_255_32*  __make___Closure_255_32(SuiDesigner$__Closure_255_32 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_255_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_255_32) , __fini___Closure_255_32) ));
	self->invoke = __fn___Closure_255_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$List*  __fn___Closure_259_42(Orc$List **  __outRef__, SuiDesigner$__Closure_259_42 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$ANode* )item));
	return urgc_set_var_for_return_class((void ** )__outRef__, s->children) ; 
}

static void  __fini___Closure_259_42(SuiDesigner$__Closure_259_42 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_259_42*  __make___Closure_259_42(SuiDesigner$__Closure_259_42 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_259_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_259_42) , __fini___Closure_259_42) ));
	self->invoke = __fn___Closure_259_42;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_265_42(SuiDesigner$__Closure_265_42 *  self, SuiCore$Event *  e, SuiCore$Node *  n, Object *  item){
	self->__var___Block_200_23->self->_onEvent_forItemView(self->__var___Block_200_23->self, e, n, item) ;
}

static void  __fini___Closure_265_42(SuiDesigner$__Closure_265_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_265_42, __var___Block_200_23) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_265_42*  __make___Closure_265_42(SuiDesigner$__Closure_265_42 **  __outRef__, SuiDesigner$__Block_200_23 *  __var___Block_200_23){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_265_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_265_42) , __fini___Closure_265_42) ));
	self->invoke = __fn___Closure_265_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_265_42, __var___Block_200_23) , __var___Block_200_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_268_30(SuiDesigner$__Closure_268_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep){
	URGC_VAR_CLEANUP SuiDesigner$__Block_268_78*  __var___Block_268_78 = (__var___Block_268_78=NULL,urgc_init_var((void**)&__var___Block_268_78, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_268_78) , __finiBlock___Block_268_78) ));
	SuiCore$Node *  o = parentNode;
	urgc_set_field_class(__var___Block_268_78, (void * )offsetof(SuiDesigner$__Block_268_78, s) , (SuiDesigner$ANode* )item) ;
	int  idx = -1;
	if (Orc_instanceof((Object*)parentNode, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )parentNode;
		idx = vb->viewIndexInParent(vb) ;
	}
	bool  isSelected = self->__var___Block_247_29->treeView->state->isSelected(self->__var___Block_247_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_1 = NULL;
	{
		SuiView$HoverViewEffect*  __scopeVar_280_20 = SuiView$mkHoverViewEffect(&tmpReturn_1, o, 0) , *o = __scopeVar_280_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_280_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->isActive = isSelected;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_284_45*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, cbOnHoverChanged) , __make___Closure_284_45(&tmpReturn_2, self->__var___Block_200_23, __var___Block_268_78) ) ;
	}
	bool  hasKids = __var___Block_268_78->s->children->size(__var___Block_268_78->s->children)  > 0;
	bool  isOpend = self->__var___Block_247_29->treeView->state->isOpend(self->__var___Block_247_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_3 = NULL;
	{
		SuiView$ImageView*  __scopeVar_303_20 = SuiView$mkImageView(&tmpReturn_3, o, 0) , *o = __scopeVar_303_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_303_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->width = 12;
		((SuiCore$View * )o)->height = 12;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		o->setSrc(o, hasKids ? isOpend ? Orc$Path_resolveFromExecutionDir(&tmpReturn_4, "asset/icon/arrow-down.png")  : Orc$Path_resolveFromExecutionDir(&tmpReturn_5, "asset/icon/arrow-right.png")  : NULL) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_6 = NULL;
	{
		SuiView$TextView*  __scopeVar_327_20 = SuiView$mkTextView(&tmpReturn_6, o, 0) , *o = __scopeVar_327_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_327_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		Vtable_Object *  vt = orc_getVtableByObject(__var___Block_268_78->s) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  name = __var___Block_268_78->s->getName((name = NULL,&name), __var___Block_268_78->s) ;
		if (name && Orc$String$notEmpty(name) ) {
			o->setText(o, name) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setText(o, Orc$str(&tmpReturn_7, vt->className) ) ;
		}
	}
}

static void  __fini___Closure_268_30(SuiDesigner$__Closure_268_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_268_30, __var___Block_247_29) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_268_30, __var___Block_200_23) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_268_30*  __make___Closure_268_30(SuiDesigner$__Closure_268_30 **  __outRef__, SuiDesigner$__Block_247_29 *  __var___Block_247_29, SuiDesigner$__Block_200_23 *  __var___Block_200_23){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_268_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_268_30) , __fini___Closure_268_30) ));
	self->invoke = __fn___Closure_268_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_268_30, __var___Block_247_29) , __var___Block_247_29) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_268_30, __var___Block_200_23) , __var___Block_200_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_284_45(SuiDesigner$__Closure_284_45 *  self, SuiCore$ViewBase *  v){
	URGC_VAR_CLEANUP void  (**hi)(void *  self) = NULL;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_hi_285*  tmpReturn_1 = NULL;
	(urgc_set_var(&hi, __make___Closure_hi_285(&tmpReturn_1, self->__var___Block_200_23) ) );
	if (v->hover) {
		urgc_set_field_class(self->__var___Block_200_23->self->editCtx, (void * )offsetof(SuiDesigner$HoroEditCtx, hoverNode) , self->__var___Block_268_78->s) ;
	}
	else {
		urgc_set_field_class(self->__var___Block_200_23->self->editCtx, (void * )offsetof(SuiDesigner$HoroEditCtx, hoverNode) , NULL) ;
	}
	printf("Scene.cbOnHoverChanged:%d\n", v->hover) ;
}

static void  __fini___Closure_284_45(SuiDesigner$__Closure_284_45 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_284_45, __var___Block_200_23) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_284_45, __var___Block_268_78) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_284_45*  __make___Closure_284_45(SuiDesigner$__Closure_284_45 **  __outRef__, SuiDesigner$__Block_200_23 *  __var___Block_200_23, SuiDesigner$__Block_268_78 *  __var___Block_268_78){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_284_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_284_45) , __fini___Closure_284_45) ));
	self->invoke = __fn___Closure_284_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_284_45, __var___Block_200_23) , __var___Block_200_23) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_284_45, __var___Block_268_78) , __var___Block_268_78) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_hi_285(SuiDesigner$__Closure_hi_285 *  self){
	printf("xxx:%d\n", self->__var___Block_200_23->xxx) ;
}

static void  __fini___Closure_hi_285(SuiDesigner$__Closure_hi_285 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_hi_285, __var___Block_200_23) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_hi_285*  __make___Closure_hi_285(SuiDesigner$__Closure_hi_285 **  __outRef__, SuiDesigner$__Block_200_23 *  __var___Block_200_23){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_hi_285*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_hi_285) , __fini___Closure_hi_285) ));
	self->invoke = __fn___Closure_hi_285;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_hi_285, __var___Block_200_23) , __var___Block_200_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiDesigner$HoroSceneHierView*  SuiDesigner$mkHoroSceneHierView(SuiDesigner$HoroSceneHierView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$HoroSceneHierView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$HoroSceneHierView_init(NULL)) ) ; 
}

void  SuiDesigner$testHoroSceneHier(){
	printf("testScene\n") ;
}



