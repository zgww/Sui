
#include "AssetDirTreeView_orc.h" 

#include <stdio.h>
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
#include "../Project_orc.h"
#include "../EventANodeChanged_orc.h"
#include "../EventFileItemChanged_orc.h"
#include "./AssetDirView_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_81_43 SuiDesigner$__Block_81_43;

typedef struct tagSuiDesigner$__Block_113_49 SuiDesigner$__Block_113_49;

typedef struct tagSuiDesigner$__Block_143_16 SuiDesigner$__Block_143_16;

typedef struct tagSuiDesigner$__Block_181_29 SuiDesigner$__Block_181_29;

typedef struct tagSuiDesigner$__Closure_onActive_85 SuiDesigner$__Closure_onActive_85;

typedef struct tagSuiDesigner$__Closure_onActive_120 SuiDesigner$__Closure_onActive_120;

typedef struct tagSuiDesigner$__Closure_188_32 SuiDesigner$__Closure_188_32;

typedef struct tagSuiDesigner$__Closure_192_42 SuiDesigner$__Closure_192_42;

typedef struct tagSuiDesigner$__Closure_201_46 SuiDesigner$__Closure_201_46;

typedef struct tagSuiDesigner$__Closure_212_42 SuiDesigner$__Closure_212_42;

typedef struct tagSuiDesigner$__Closure_217_30 SuiDesigner$__Closure_217_30;

typedef struct tagSuiDesigner$__Closure_238_45 SuiDesigner$__Closure_238_45;



struct tagSuiDesigner$__Block_81_43 {
	SuiDesigner$AssetDirTreeView*  self ;
};





struct tagSuiDesigner$__Block_113_49 {
	SuiDesigner$FileItem*  fi ;
	SuiDesigner$AssetDirTreeView*  self ;
};





struct tagSuiDesigner$__Block_143_16 {
	SuiDesigner$AssetDirTreeView*  self ;
};





struct tagSuiDesigner$__Block_181_29 {
	SuiView$TreeView*  treeView ;
};





struct tagSuiDesigner$__Closure_onActive_85 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_85 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_81_43*  __var___Block_81_43 ;
};





struct tagSuiDesigner$__Closure_onActive_120 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_120 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_113_49*  __var___Block_113_49 ;
};





struct tagSuiDesigner$__Closure_188_32 {
	Orc$String*  (*invoke)(SuiDesigner$__Closure_188_32 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_192_42 {
	Orc$List*  (*invoke)(SuiDesigner$__Closure_192_42 *  self, Object *  item);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_201_46 {
	void  (*invoke)(SuiDesigner$__Closure_201_46 *  self, SuiView$TreeState *  state);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_212_42 {
	void  (*invoke)(SuiDesigner$__Closure_212_42 *  self, SuiCore$Event *  e, SuiCore$ViewBase *  v, Object *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_143_16*  __var___Block_143_16 ;
};





struct tagSuiDesigner$__Closure_217_30 {
	void  (*invoke)(SuiDesigner$__Closure_217_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_181_29*  __var___Block_181_29 ;
};





struct tagSuiDesigner$__Closure_238_45 {
	void  (*invoke)(SuiDesigner$__Closure_238_45 *  self, SuiCore$ViewBase *  v);
	Vtable_Object *  vtable ;
};





// static function declaration
static void  __finiBlock___Block_81_43(SuiDesigner$__Block_81_43 *  self);
static void  __finiBlock___Block_113_49(SuiDesigner$__Block_113_49 *  self);
static void  __finiBlock___Block_143_16(SuiDesigner$__Block_143_16 *  self);
static void  __finiBlock___Block_181_29(SuiDesigner$__Block_181_29 *  self);
static void  __fn___Closure_onActive_85(SuiDesigner$__Closure_onActive_85 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_85(SuiDesigner$__Closure_onActive_85 *  self);
static SuiDesigner$__Closure_onActive_85*  __make___Closure_onActive_85(SuiDesigner$__Closure_onActive_85 **  __outRef__, SuiDesigner$__Block_81_43 *  __var___Block_81_43);
static void  __fn___Closure_onActive_120(SuiDesigner$__Closure_onActive_120 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_120(SuiDesigner$__Closure_onActive_120 *  self);
static SuiDesigner$__Closure_onActive_120*  __make___Closure_onActive_120(SuiDesigner$__Closure_onActive_120 **  __outRef__, SuiDesigner$__Block_113_49 *  __var___Block_113_49);
static Orc$String*  __fn___Closure_188_32(Orc$String **  __outRef__, SuiDesigner$__Closure_188_32 *  self, Object *  item);
static void  __fini___Closure_188_32(SuiDesigner$__Closure_188_32 *  self);
static SuiDesigner$__Closure_188_32*  __make___Closure_188_32(SuiDesigner$__Closure_188_32 **  __outRef__);
static Orc$List*  __fn___Closure_192_42(Orc$List **  __outRef__, SuiDesigner$__Closure_192_42 *  self, Object *  item);
static void  __fini___Closure_192_42(SuiDesigner$__Closure_192_42 *  self);
static SuiDesigner$__Closure_192_42*  __make___Closure_192_42(SuiDesigner$__Closure_192_42 **  __outRef__);
static void  __fn___Closure_201_46(SuiDesigner$__Closure_201_46 *  self, SuiView$TreeState *  state);
static void  __fini___Closure_201_46(SuiDesigner$__Closure_201_46 *  self);
static SuiDesigner$__Closure_201_46*  __make___Closure_201_46(SuiDesigner$__Closure_201_46 **  __outRef__);
static void  __fn___Closure_212_42(SuiDesigner$__Closure_212_42 *  self, SuiCore$Event *  e, SuiCore$ViewBase *  v, Object *  item);
static void  __fini___Closure_212_42(SuiDesigner$__Closure_212_42 *  self);
static SuiDesigner$__Closure_212_42*  __make___Closure_212_42(SuiDesigner$__Closure_212_42 **  __outRef__, SuiDesigner$__Block_143_16 *  __var___Block_143_16);
static void  __fn___Closure_217_30(SuiDesigner$__Closure_217_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep);
static void  __fini___Closure_217_30(SuiDesigner$__Closure_217_30 *  self);
static SuiDesigner$__Closure_217_30*  __make___Closure_217_30(SuiDesigner$__Closure_217_30 **  __outRef__, SuiDesigner$__Block_181_29 *  __var___Block_181_29);
static void  __fn___Closure_238_45(SuiDesigner$__Closure_238_45 *  self, SuiCore$ViewBase *  v);
static void  __fini___Closure_238_45(SuiDesigner$__Closure_238_45 *  self);
static SuiDesigner$__Closure_238_45*  __make___Closure_238_45(SuiDesigner$__Closure_238_45 **  __outRef__);



//vtable instance
Vtable_SuiDesigner$AssetDirTreeView _vtable_SuiDesigner$AssetDirTreeView;

// init meta

void SuiDesigner$AssetDirTreeView_initMeta(Vtable_SuiDesigner$AssetDirTreeView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "_routeMenuNativeItem", offsetof(SuiDesigner$AssetDirTreeView, _routeMenuNativeItem));
	orc_metaField_method(&pNext, "_self_onRightClick", offsetof(SuiDesigner$AssetDirTreeView, _self_onRightClick));
	orc_metaField_method(&pNext, "_dirItem_onEvent", offsetof(SuiDesigner$AssetDirTreeView, _dirItem_onEvent));
}


// vtable init


Vtable_SuiDesigner$AssetDirTreeView* Vtable_SuiDesigner$AssetDirTreeView_init(Vtable_SuiDesigner$AssetDirTreeView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$AssetDirTreeView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$AssetDirTreeView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$AssetDirTreeView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$AssetDirTreeView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$AssetDirTreeView_fini(SuiDesigner$AssetDirTreeView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiDesigner$AssetDirTreeView_init_fields(SuiDesigner$AssetDirTreeView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$AssetDirTreeView_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)SuiDesigner$AssetDirTreeView$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiDesigner$AssetDirTreeView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$AssetDirTreeView$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiDesigner$AssetDirTreeView$onUnmounting;
	((SuiDesigner$AssetDirTreeView*)self)->_routeMenuNativeItem = (void*)SuiDesigner$AssetDirTreeView$_routeMenuNativeItem;
	((SuiDesigner$AssetDirTreeView*)self)->_self_onRightClick = (void*)SuiDesigner$AssetDirTreeView$_self_onRightClick;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiDesigner$AssetDirTreeView$onEvent;
	((SuiDesigner$AssetDirTreeView*)self)->_dirItem_onEvent = (void*)SuiDesigner$AssetDirTreeView$_dirItem_onEvent;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$AssetDirTreeView$react;
}

// init function

void SuiDesigner$AssetDirTreeView_init(SuiDesigner$AssetDirTreeView *self, void *pOwner){
    Vtable_SuiDesigner$AssetDirTreeView_init(&_vtable_SuiDesigner$AssetDirTreeView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$AssetDirTreeView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$AssetDirTreeView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$AssetDirTreeView * SuiDesigner$AssetDirTreeView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$AssetDirTreeView *self = calloc(1, sizeof(SuiDesigner$AssetDirTreeView));
	
    SuiDesigner$AssetDirTreeView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$AssetDirTreeView$ctor(SuiDesigner$AssetDirTreeView *  self){
	SuiCore$Listener$ctor(self) ;
}


void  SuiDesigner$AssetDirTreeView$onListenerEvent(SuiDesigner$AssetDirTreeView *  self, SuiCore$Event *  event){
	if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeChanged_init(NULL))) {
		SuiDesigner$EventANodeChanged *  e = (SuiDesigner$EventANodeChanged * )e;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventFileItemChanged_init(NULL))) {
		SuiDesigner$EventFileItemChanged *  e = (SuiDesigner$EventFileItemChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiDesigner$AssetDirTreeView$onMounted(SuiDesigner$AssetDirTreeView *  self){
	SuiCore$Node$onMounted(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  SuiDesigner$AssetDirTreeView$onUnmounting(SuiDesigner$AssetDirTreeView *  self){
	SuiCore$Node$onUnmounting(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  SuiDesigner$AssetDirTreeView$_routeMenuNativeItem(SuiDesigner$AssetDirTreeView *  self, SuiView$MenuNativeItem *  item, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	if (!item->cmd) {
		return ; 
	}
	{
		if (Orc$String$equals(item->cmd, "DeleteDirectory") ) {
			SuiDesigner$UiAction_deleteDirectory(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "CreateDirectory") ) {
			SuiDesigner$UiAction_createDirectory(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "RenameDirectory") ) {
			SuiDesigner$UiAction_renameFileItem(fi) ;
			return ; 
		}
		if (Orc$String$equals(item->cmd, "CreatePrefab") ) {
			SuiDesigner$UiAction_createPrefab(fi) ;
			return ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_alert(Orc$String$addString(Orc$String$clone(&tmpReturn_1, item->label) , fi->path) ->str, "tip") ;
}


void  SuiDesigner$AssetDirTreeView$_self_onRightClick(SuiDesigner$AssetDirTreeView *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP SuiDesigner$__Block_81_43*  __var___Block_81_43 = (__var___Block_81_43=NULL,urgc_init_var((void**)&__var___Block_81_43, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_81_43) , __finiBlock___Block_81_43) ));
	urgc_set_field_class(__var___Block_81_43, (void * )offsetof(SuiDesigner$__Block_81_43, self) , self) ;
	((SuiCore$Event * )me)->stopPropagation(me) ;
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
	{
		SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
		
	
		URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_85*  tmpReturn_2 = NULL;
		(urgc_set_var(&onActive, __make___Closure_onActive_85(&tmpReturn_2, __var___Block_81_43) ) );
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		{
			SuiView$MenuNativeItem*  __scopeVar_96_12 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "创建目录") , onActive) , *o = __scopeVar_96_12;
			
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "CreateDirectory") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
		n->create(n, o) ;
		n->showAtMouse(n) ;
	}
}


void  SuiDesigner$AssetDirTreeView$onEvent(SuiDesigner$AssetDirTreeView *  self, SuiCore$Event *  e){
	SuiCore$Emitter$onEvent(self, e) ;
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			self->_self_onRightClick(self, me) ;
		}
	}
}


void  SuiDesigner$AssetDirTreeView$_dirItem_onEvent(SuiDesigner$AssetDirTreeView *  self, SuiCore$Event *  e, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP SuiDesigner$__Block_113_49*  __var___Block_113_49 = (__var___Block_113_49=NULL,urgc_init_var((void**)&__var___Block_113_49, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_113_49) , __finiBlock___Block_113_49) ));
	urgc_set_field_class(__var___Block_113_49, (void * )offsetof(SuiDesigner$__Block_113_49, self) , self) ;
	urgc_set_field_class(__var___Block_113_49, (void * )offsetof(SuiDesigner$__Block_113_49, fi) , fi) ;
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			e->stopPropagation(e) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
				
			
				URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_120*  tmpReturn_2 = NULL;
				(urgc_set_var(&onActive, __make___Closure_onActive_120(&tmpReturn_2, __var___Block_113_49) ) );
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_131_20 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "删除目录") , onActive) , *o = __scopeVar_131_20;
					
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "DeleteDirectory") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_132_20 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "创建目录") , onActive) , *o = __scopeVar_132_20;
					
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "CreateDirectory") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_133_20 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "重命名目录") , onActive) , *o = __scopeVar_133_20;
					
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_11, "RenameDirectory") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_12 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_134_20 = SuiView$mkMenuNativeItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "创建Prefab") , onActive) , *o = __scopeVar_134_20;
					
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_14, "CreatePrefab") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
				n->create(n, o) ;
				n->showAtMouse(n) ;
			}
		}
	}
}


void  SuiDesigner$AssetDirTreeView$react(SuiDesigner$AssetDirTreeView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_143_16*  __var___Block_143_16 = (__var___Block_143_16=NULL,urgc_init_var((void**)&__var___Block_143_16, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_143_16) , __finiBlock___Block_143_16) ));
	urgc_set_field_class(__var___Block_143_16, (void * )offsetof(SuiDesigner$__Block_143_16, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  project = SuiDesigner$Project_ins((project = NULL,&project)) ;
	SuiDesigner$AssetDirTreeView *  o = (SuiDesigner$AssetDirTreeView * )self;
	((SuiCore$View * )o)->backgroundColor = 0x33ffffff;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_158_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_158_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_158_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->grow = 1;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_4 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_168_8 = SuiView$mkScrollArea(&tmpReturn_4, o, 0) , *o = __scopeVar_168_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_168_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_5, "stretch") ) ;
		o->useMinWidthConstraint = true;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_177_12 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_177_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_177_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TreeView*  tmpReturn_7 = NULL;
		{
			SuiView$TreeView*  __scopeVar_181_12 = SuiView$mkTreeView(&tmpReturn_7, o, 0) , *o = __scopeVar_181_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_181_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP SuiDesigner$__Block_181_29*  __var___Block_181_29 = (__var___Block_181_29=NULL,urgc_init_var((void**)&__var___Block_181_29, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_181_29) , __finiBlock___Block_181_29) ));
			urgc_set_field_class(__var___Block_181_29, (void * )offsetof(SuiDesigner$__Block_181_29, treeView) , o) ;
			URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_8 = NULL;
			urgc_set_field_class(o->state, (void * )offsetof(SuiView$TreeState, roots) , project->dirFileItem->getSubDirectoryChildren(&tmpReturn_8, project->dirFileItem) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_188_32*  tmpReturn_9 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getId) , __make___Closure_188_32(&tmpReturn_9) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_192_42*  tmpReturn_10 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, getItemChildren) , __make___Closure_192_42(&tmpReturn_10) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_201_46*  tmpReturn_11 = NULL;
			urgc_set_field(o->state, (void * )offsetof(SuiView$TreeState, cbSelectedIdChanged) , __make___Closure_201_46(&tmpReturn_11) ) ;
			Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "maxOrStretch") ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_212_42*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, cbOnEvent_forItemView) , __make___Closure_212_42(&tmpReturn_12, __var___Block_143_16) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_217_30*  tmpReturn_13 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$TreeView, reactItem) , __make___Closure_217_30(&tmpReturn_13, __var___Block_181_29) ) ;
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



static void  __finiBlock___Block_81_43(SuiDesigner$__Block_81_43 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_81_43, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_113_49(SuiDesigner$__Block_113_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_113_49, fi) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_113_49, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_143_16(SuiDesigner$__Block_143_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_143_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_181_29(SuiDesigner$__Block_181_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_181_29, treeView) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_onActive_85(SuiDesigner$__Closure_onActive_85 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu cmd:%s item:%s\n", item->cmd->str, item->label->str) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  project = SuiDesigner$Project_ins((project = NULL,&project)) ;
	self->__var___Block_81_43->self->_routeMenuNativeItem(self->__var___Block_81_43->self, item, project->dirFileItem) ;
}

static void  __fini___Closure_onActive_85(SuiDesigner$__Closure_onActive_85 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_85, __var___Block_81_43) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_85*  __make___Closure_onActive_85(SuiDesigner$__Closure_onActive_85 **  __outRef__, SuiDesigner$__Block_81_43 *  __var___Block_81_43){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_85*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_85) , __fini___Closure_onActive_85) ));
	self->invoke = __fn___Closure_onActive_85;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_85, __var___Block_81_43) , __var___Block_81_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_120(SuiDesigner$__Closure_onActive_120 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu cmd:%s item:%s, fi:%s\n", item->cmd->str, item->label->str, self->__var___Block_113_49->fi->path->str) ;
	self->__var___Block_113_49->self->_routeMenuNativeItem(self->__var___Block_113_49->self, item, self->__var___Block_113_49->fi) ;
}

static void  __fini___Closure_onActive_120(SuiDesigner$__Closure_onActive_120 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_120, __var___Block_113_49) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_120*  __make___Closure_onActive_120(SuiDesigner$__Closure_onActive_120 **  __outRef__, SuiDesigner$__Block_113_49 *  __var___Block_113_49){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_120*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_120) , __fini___Closure_onActive_120) ));
	self->invoke = __fn___Closure_onActive_120;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_120, __var___Block_113_49) , __var___Block_113_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$String*  __fn___Closure_188_32(Orc$String **  __outRef__, SuiDesigner$__Closure_188_32 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$FileItem* )item));
	return urgc_set_var_for_return_class((void ** )__outRef__, s->path) ; 
}

static void  __fini___Closure_188_32(SuiDesigner$__Closure_188_32 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_188_32*  __make___Closure_188_32(SuiDesigner$__Closure_188_32 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_188_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_188_32) , __fini___Closure_188_32) ));
	self->invoke = __fn___Closure_188_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static Orc$List*  __fn___Closure_192_42(Orc$List **  __outRef__, SuiDesigner$__Closure_192_42 *  self, Object *  item){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$FileItem* )item));
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, s->getSubDirectoryChildren(&tmpReturn_1, s) ) ; 
}

static void  __fini___Closure_192_42(SuiDesigner$__Closure_192_42 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_192_42*  __make___Closure_192_42(SuiDesigner$__Closure_192_42 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_192_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_192_42) , __fini___Closure_192_42) ));
	self->invoke = __fn___Closure_192_42;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_201_46(SuiDesigner$__Closure_201_46 *  self, SuiView$TreeState *  state){
	Object *  sel = state->getFirstSelected(state) ;
	if (sel) {
		if (SuiDesigner$curAssetDirView) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  fi = (fi=NULL,urgc_init_var_class((void**)&fi, (SuiDesigner$FileItem * )sel));
			SuiDesigner$curAssetDirView->_openDirectory(SuiDesigner$curAssetDirView, fi) ;
		}
	}
}

static void  __fini___Closure_201_46(SuiDesigner$__Closure_201_46 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_201_46*  __make___Closure_201_46(SuiDesigner$__Closure_201_46 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_201_46*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_201_46) , __fini___Closure_201_46) ));
	self->invoke = __fn___Closure_201_46;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_212_42(SuiDesigner$__Closure_212_42 *  self, SuiCore$Event *  e, SuiCore$ViewBase *  v, Object *  item){
	if (Orc_instanceof((Object*)item, (Vtable_Object*)Vtable_SuiDesigner$FileItem_init(NULL))) {
		self->__var___Block_143_16->self->_dirItem_onEvent(self->__var___Block_143_16->self, e, (SuiDesigner$FileItem * )item) ;
	}
}

static void  __fini___Closure_212_42(SuiDesigner$__Closure_212_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_212_42, __var___Block_143_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_212_42*  __make___Closure_212_42(SuiDesigner$__Closure_212_42 **  __outRef__, SuiDesigner$__Block_143_16 *  __var___Block_143_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_212_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_212_42) , __fini___Closure_212_42) ));
	self->invoke = __fn___Closure_212_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_212_42, __var___Block_143_16) , __var___Block_143_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_217_30(SuiDesigner$__Closure_217_30 *  self, SuiCore$Node *  parentNode, Object *  item, int  deep){
	SuiCore$Node *  o = parentNode;
	int  idx = -1;
	if (Orc_instanceof((Object*)parentNode, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )parentNode;
		idx = vb->viewIndexInParent(vb) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  s = (s=NULL,urgc_init_var_class((void**)&s, (SuiDesigner$FileItem* )item));
	bool  isSelected = self->__var___Block_181_29->treeView->state->isSelected(self->__var___Block_181_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_1 = NULL;
	{
		SuiView$HoverViewEffect*  __scopeVar_228_20 = SuiView$mkHoverViewEffect(&tmpReturn_1, o, 0) , *o = __scopeVar_228_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_228_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->border->l->w = 0.f;
		o->border->r->w = 0.f;
		o->hoverBorder->l->w = 0.f;
		o->hoverBorder->r->w = 0.f;
		o->activeBorder->l->w = 0.f;
		o->activeBorder->r->w = 0.f;
		o->backgroundColor = idx % 2 == 1 ? 0x09000000 : 0;
		o->isActive = isSelected;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_238_45*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, cbOnHoverChanged) , __make___Closure_238_45(&tmpReturn_2) ) ;
	}
	bool  hasKids = s->hasSubDirectory(s) ;
	bool  isOpend = self->__var___Block_181_29->treeView->state->isOpend(self->__var___Block_181_29->treeView->state, item) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_3 = NULL;
	{
		SuiView$ImageView*  __scopeVar_245_20 = SuiView$mkImageView(&tmpReturn_3, o, 0) , *o = __scopeVar_245_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_245_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->width = 12;
		((SuiCore$View * )o)->height = 12;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		o->setSrc(o, hasKids ? isOpend ? Orc$str(&tmpReturn_4, "asset/icon/arrow-down.png")  : Orc$str(&tmpReturn_5, "asset/icon/arrow-right.png")  : NULL) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_6 = NULL;
	{
		SuiView$TextView*  __scopeVar_270_20 = SuiView$mkTextView(&tmpReturn_6, o, 0) , *o = __scopeVar_270_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_270_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->setText(o, s->filename) ;
	}
}

static void  __fini___Closure_217_30(SuiDesigner$__Closure_217_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_217_30, __var___Block_181_29) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_217_30*  __make___Closure_217_30(SuiDesigner$__Closure_217_30 **  __outRef__, SuiDesigner$__Block_181_29 *  __var___Block_181_29){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_217_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_217_30) , __fini___Closure_217_30) ));
	self->invoke = __fn___Closure_217_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_217_30, __var___Block_181_29) , __var___Block_181_29) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_238_45(SuiDesigner$__Closure_238_45 *  self, SuiCore$ViewBase *  v){
	printf("DirTree.cbOnHoverChanged:%d\n", v->hover) ;
}

static void  __fini___Closure_238_45(SuiDesigner$__Closure_238_45 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_238_45*  __make___Closure_238_45(SuiDesigner$__Closure_238_45 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_238_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_238_45) , __fini___Closure_238_45) ));
	self->invoke = __fn___Closure_238_45;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

void  SuiDesigner$testAsset(){
	{
		URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  root = SuiDesigner$FileItem_loadDirectoryTree((root = NULL,&root), "D:/ws/oms_ts/omsdeploy") ;
		root->printTree(root, 0) ;
	}
}

SuiDesigner$AssetDirTreeView*  SuiDesigner$mkAssetDirTreeView(SuiDesigner$AssetDirTreeView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$AssetDirTreeView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$AssetDirTreeView_init(NULL)) ) ; 
}



