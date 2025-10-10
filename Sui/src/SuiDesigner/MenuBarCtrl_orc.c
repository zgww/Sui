
#include "MenuBarCtrl_orc.h" 

#include <stdio.h>
#include "../Orc/Orc.h"
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


// static struct 
typedef struct tagSuiDesigner$__Block_79_39 SuiDesigner$__Block_79_39;

typedef struct tagSuiDesigner$__Closure_93_24 SuiDesigner$__Closure_93_24;



struct tagSuiDesigner$__Block_79_39 {
	SuiDesigner$MenuBarCtrl*  self ;
};





struct tagSuiDesigner$__Closure_93_24 {
	void  (*invoke)(SuiDesigner$__Closure_93_24 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_79_39*  __var___Block_79_39 ;
};





// static function declaration
static void  __finiBlock___Block_79_39(SuiDesigner$__Block_79_39 *  self);
static void  __fn___Closure_93_24(SuiDesigner$__Closure_93_24 *  self);
static void  __fini___Closure_93_24(SuiDesigner$__Closure_93_24 *  self);
static SuiDesigner$__Closure_93_24*  __make___Closure_93_24(SuiDesigner$__Closure_93_24 **  __outRef__, SuiDesigner$__Block_79_39 *  __var___Block_79_39);



//vtable instance
Vtable_SuiDesigner$MenuBarCtrl _vtable_SuiDesigner$MenuBarCtrl;

// init meta

void SuiDesigner$MenuBarCtrl_initMeta(Vtable_SuiDesigner$MenuBarCtrl *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "status", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$MenuBarCtrl, status), true, false, 1);
	orc_metaField_class(&pNext, "curMenu", ((Vtable_Object*)Vtable_SuiView$MenuButton_init(0)), offsetof(SuiDesigner$MenuBarCtrl, curMenu), true, false, 1);
	orc_metaField_class(&pNext, "nextMenu", ((Vtable_Object*)Vtable_SuiView$MenuButton_init(0)), offsetof(SuiDesigner$MenuBarCtrl, nextMenu), true, false, 1);
	orc_metaField_class(&pNext, "popup", ((Vtable_Object*)Vtable_SuiView$MenuNative_init(0)), offsetof(SuiDesigner$MenuBarCtrl, popup), true, false, 1);

	orc_metaField_method(&pNext, "showPopup", offsetof(SuiDesigner$MenuBarCtrl, showPopup));
	orc_metaField_method(&pNext, "onclick", offsetof(SuiDesigner$MenuBarCtrl, onclick));
	orc_metaField_method(&pNext, "onmove", offsetof(SuiDesigner$MenuBarCtrl, onmove));
	orc_metaField_method(&pNext, "setPopup", offsetof(SuiDesigner$MenuBarCtrl, setPopup));
	orc_metaField_method(&pNext, "onPopupDismiss", offsetof(SuiDesigner$MenuBarCtrl, onPopupDismiss));
}


// vtable init


Vtable_SuiDesigner$MenuBarCtrl* Vtable_SuiDesigner$MenuBarCtrl_init(Vtable_SuiDesigner$MenuBarCtrl* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$MenuBarCtrl;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$MenuBarCtrl_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$MenuBarCtrl";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$MenuBarCtrl_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$MenuBarCtrl_fini(SuiDesigner$MenuBarCtrl *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->status);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->curMenu);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->nextMenu);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->popup);

}

// init fields function


void SuiDesigner$MenuBarCtrl_init_fields(SuiDesigner$MenuBarCtrl *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$MenuBarCtrl_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->status, Orc$str(&tmpReturn_1, "idle") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->curMenu, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->nextMenu, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->popup, NULL);
	urgc_set_field(self, (void**)&((SuiDesigner$MenuBarCtrl*)self)->cbCreateMenuNativeItem, NULL);
    }
	((Object*)self)->dtor = (void*)SuiDesigner$MenuBarCtrl$dtor;
	((SuiDesigner$MenuBarCtrl*)self)->showPopup = (void*)SuiDesigner$MenuBarCtrl$showPopup;
	((SuiDesigner$MenuBarCtrl*)self)->onclick = (void*)SuiDesigner$MenuBarCtrl$onclick;
	((SuiDesigner$MenuBarCtrl*)self)->onmove = (void*)SuiDesigner$MenuBarCtrl$onmove;
	((SuiDesigner$MenuBarCtrl*)self)->setPopup = (void*)SuiDesigner$MenuBarCtrl$setPopup;
	((SuiDesigner$MenuBarCtrl*)self)->onPopupDismiss = (void*)SuiDesigner$MenuBarCtrl$onPopupDismiss;
}

// init function

void SuiDesigner$MenuBarCtrl_init(SuiDesigner$MenuBarCtrl *self, void *pOwner){
    Vtable_SuiDesigner$MenuBarCtrl_init(&_vtable_SuiDesigner$MenuBarCtrl);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$MenuBarCtrl;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$MenuBarCtrl_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$MenuBarCtrl * SuiDesigner$MenuBarCtrl_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$MenuBarCtrl *self = calloc(1, sizeof(SuiDesigner$MenuBarCtrl));
	
    SuiDesigner$MenuBarCtrl_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$MenuBarCtrl$dtor(SuiDesigner$MenuBarCtrl *  self){
	printf(".MenuBarCtrl\n") ;
}


void  SuiDesigner$MenuBarCtrl$showPopup(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  mbutton){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(mbutton);

	URGC_VAR_CLEANUP SuiDesigner$__Block_79_39*  __var___Block_79_39 = (__var___Block_79_39=NULL,urgc_init_var((void**)&__var___Block_79_39, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_79_39) , __finiBlock___Block_79_39) ));
	urgc_set_field_class(__var___Block_79_39, (void * )offsetof(SuiDesigner$__Block_79_39, self) , self) ;
	printf("set Trigging:%p\n", mbutton) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, curMenu) , mbutton) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, nextMenu) , NULL) ;
	if (!self->cbCreateMenuNativeItem) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  item = (*(self->cbCreateMenuNativeItem))((item = NULL,&item), (void * )(self->cbCreateMenuNativeItem), mbutton) ;
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, popup) , n) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_93_24*  tmpReturn_1 = NULL;
	urgc_set_field(n, (void * )offsetof(SuiView$MenuNative, cbOnDismiss) , __make___Closure_93_24(&tmpReturn_1, __var___Block_79_39) ) ;
	n->create(n, item) ;
	SuiCore$Rect r = ((SuiCore$ViewBase * )mbutton)->get_abs_rect(mbutton) ;
	n->showAt(n, r.x, SuiCore$Rect$bottom(&r) ) ;
}


void  SuiDesigner$MenuBarCtrl$onclick(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  mbutton, SuiCore$MouseEvent *  me){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(mbutton);

	self->showPopup(self, mbutton) ;
}


void  SuiDesigner$MenuBarCtrl$onmove(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuButton*  menu, SuiCore$MouseEvent *  me){
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
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, popup) , NULL) ;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, curMenu) , NULL) ;
	}
	if (menu && self->curMenu == NULL) {
		((SuiCore$ViewBase * )menu)->hover = true;
		((SuiCore$Node * )menu)->react(menu) ;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, nextMenu) , menu) ;
		printf("menu.onClick\n") ;
	}
}


void  SuiDesigner$MenuBarCtrl$setPopup(SuiDesigner$MenuBarCtrl *  self, SuiView$MenuNative*  popup, SuiView$MenuButton*  curMenu){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(popup);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(curMenu);

	printf("setPopup:%p, %p\n", popup, curMenu) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, curMenu) , curMenu) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, popup) , popup) ;
}


void  SuiDesigner$MenuBarCtrl$onPopupDismiss(SuiDesigner$MenuBarCtrl *  self){
	printf("onPopupDismiss:%p next:%p\n", self->popup, self->nextMenu) ;
	if (self->nextMenu) {
		URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  m = (m=NULL,urgc_init_var_class((void**)&m, self->nextMenu));
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$MenuBarCtrl, nextMenu) , NULL) ;
		self->showPopup(self, m) ;
	}
}



static void  __finiBlock___Block_79_39(SuiDesigner$__Block_79_39 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_79_39, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_93_24(SuiDesigner$__Closure_93_24 *  self){
	printf("\ncbOnDismiss:%p\n\n", self->__var___Block_79_39->self) ;
	self->__var___Block_79_39->self->onPopupDismiss(self->__var___Block_79_39->self) ;
}

static void  __fini___Closure_93_24(SuiDesigner$__Closure_93_24 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_93_24, __var___Block_79_39) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_93_24*  __make___Closure_93_24(SuiDesigner$__Closure_93_24 **  __outRef__, SuiDesigner$__Block_79_39 *  __var___Block_79_39){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_93_24*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_93_24) , __fini___Closure_93_24) ));
	self->invoke = __fn___Closure_93_24;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_93_24, __var___Block_79_39) , __var___Block_79_39) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



