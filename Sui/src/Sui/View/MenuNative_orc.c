
#include "MenuNative_orc.h" 

#include <stdio.h>
#include "../../../UrgcDll/urgc_api.h"
#include "../../Orc/Orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/Vec2_orc.h"
#include "../../Orc/Time_orc.h"
#include "../Core/Timer_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../Core/App_orc.h"
#include "../Core/Window_orc.h"


// static struct 
typedef struct tagSuiView$__Closure_117_33 SuiView$__Closure_117_33;



struct tagSuiView$__Closure_117_33 {
	void  (*invoke)(SuiView$__Closure_117_33 *  self);
	Vtable_Object *  vtable ;
};





// static function declaration
static void  __fn___Closure_117_33(SuiView$__Closure_117_33 *  self);
static void  __fini___Closure_117_33(SuiView$__Closure_117_33 *  self);
static SuiView$__Closure_117_33*  __make___Closure_117_33(SuiView$__Closure_117_33 **  __outRef__);


static int  gMenuId = 10000;
static URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  currentMenuNative = NULL;

//vtable instance
Vtable_SuiView$MenuNativeItem _vtable_SuiView$MenuNativeItem;

// init meta

void SuiView$MenuNativeItem_initMeta(Vtable_SuiView$MenuNativeItem *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "commandId", OrcMetaType_int, offsetof(SuiView$MenuNativeItem, commandId), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "id", OrcMetaType_int, offsetof(SuiView$MenuNativeItem, id), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "cmd", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$MenuNativeItem, cmd), true, false, 1);
	orc_metaField_class(&pNext, "label", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$MenuNativeItem, label), true, false, 1);
	orc_metaField_class(&pNext, "children", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiView$MenuNativeItem, children), true, false, 1);

	orc_metaField_method(&pNext, "append", offsetof(SuiView$MenuNativeItem, append));
}


// vtable init


Vtable_SuiView$MenuNativeItem* Vtable_SuiView$MenuNativeItem_init(Vtable_SuiView$MenuNativeItem* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$MenuNativeItem;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$MenuNativeItem_new;
    ((Vtable_Object*)pvt)->className = "SuiView$MenuNativeItem";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$MenuNativeItem_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$MenuNativeItem_fini(SuiView$MenuNativeItem *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$MenuNativeItem_init_fields(SuiView$MenuNativeItem *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$MenuNativeItem_fini;
	//fields
    {
	((SuiView$MenuNativeItem*)self)->commandId = 0;
	((SuiView$MenuNativeItem*)self)->id = 0;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$MenuNativeItem*)self)->cmd, Orc$str(&tmpReturn_1, "") );
	urgc_set_field_class(self, (void**)&((SuiView$MenuNativeItem*)self)->label, NULL);
	urgc_set_field(self, (void**)&((SuiView$MenuNativeItem*)self)->onActive, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$MenuNativeItem*)self)->children, Orc$List_new(&tmpNewOwner_2) );
    }
	((Object*)self)->ctor = (void*)SuiView$MenuNativeItem$ctor;
	((Object*)self)->dtor = (void*)SuiView$MenuNativeItem$dtor;
	((SuiView$MenuNativeItem*)self)->append = (void*)SuiView$MenuNativeItem$append;
}

// init function

void SuiView$MenuNativeItem_init(SuiView$MenuNativeItem *self, void *pOwner){
    Vtable_SuiView$MenuNativeItem_init(&_vtable_SuiView$MenuNativeItem);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$MenuNativeItem;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$MenuNativeItem_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$MenuNativeItem * SuiView$MenuNativeItem_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$MenuNativeItem *self = calloc(1, sizeof(SuiView$MenuNativeItem));
	
    SuiView$MenuNativeItem_init(self, pOwner);
    return self;
}


// class members
void  SuiView$MenuNativeItem$ctor(SuiView$MenuNativeItem *  self){
	self->commandId = gMenuId;
	self->id = gMenuId;
	gMenuId = gMenuId + 1;
}


void  SuiView$MenuNativeItem$dtor(SuiView$MenuNativeItem *  self){
	
}


void  SuiView$MenuNativeItem$append(SuiView$MenuNativeItem *  self, SuiView$MenuNativeItem *  item){
	self->children->add(self->children, item) ;
}



SuiView$MenuNativeItem*  SuiView$mkMenuNativeItem(SuiView$MenuNativeItem **  __outRef__, SuiView$MenuNativeItem *  parent, Orc$String*  label, void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item)){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(label);
	URGC_REF_ARG_WITH_CLEANUP(onActive);

	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  ins = (ins=NULL,urgc_init_var_class((void**)&ins, SuiView$MenuNativeItem_new(&ins) ));
	urgc_set_field_class(ins, (void * )offsetof(SuiView$MenuNativeItem, label) , label) ;
	if (label) {
		Orc$String$set(ins->cmd, label->str) ;
	}
	urgc_set_field(ins, (void * )offsetof(SuiView$MenuNativeItem, onActive) , onActive) ;
	if (parent) {
		parent->append(parent, ins) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ins) ; 
}


//vtable instance
Vtable_SuiView$MenuNative _vtable_SuiView$MenuNative;

// init meta

void SuiView$MenuNative_initMeta(Vtable_SuiView$MenuNative *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "id", OrcMetaType_long_long, offsetof(SuiView$MenuNative, id), 0, 0, 0, 0);//longlong
	orc_metaField_class(&pNext, "root", ((Vtable_Object*)Vtable_SuiView$MenuNativeItem_init(0)), offsetof(SuiView$MenuNative, root), true, false, 1);
	orc_metaField_primitive(&pNext, "windowId", OrcMetaType_long_long, offsetof(SuiView$MenuNative, windowId), 0, 0, 0, 0);//longlong

	orc_metaField_method(&pNext, "create", offsetof(SuiView$MenuNative, create));
	orc_metaField_method(&pNext, "buildNativeMenu", offsetof(SuiView$MenuNative, buildNativeMenu));
	orc_metaField_method(&pNext, "show", offsetof(SuiView$MenuNative, show));
	orc_metaField_method(&pNext, "showAt", offsetof(SuiView$MenuNative, showAt));
	orc_metaField_method(&pNext, "showAtScreenPosition", offsetof(SuiView$MenuNative, showAtScreenPosition));
	orc_metaField_method(&pNext, "showAtMouse", offsetof(SuiView$MenuNative, showAtMouse));
	orc_metaField_method(&pNext, "onDismiss", offsetof(SuiView$MenuNative, onDismiss));
	orc_metaField_method(&pNext, "destroy", offsetof(SuiView$MenuNative, destroy));
	orc_metaField_method(&pNext, "dispatchCommand", offsetof(SuiView$MenuNative, dispatchCommand));
}


// vtable init


Vtable_SuiView$MenuNative* Vtable_SuiView$MenuNative_init(Vtable_SuiView$MenuNative* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$MenuNative;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$MenuNative_new;
    ((Vtable_Object*)pvt)->className = "SuiView$MenuNative";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$MenuNative_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$MenuNative_fini(SuiView$MenuNative *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$MenuNative_init_fields(SuiView$MenuNative *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$MenuNative_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiView$MenuNative*)self)->root, NULL);
	urgc_set_field(self, (void**)&((SuiView$MenuNative*)self)->cbOnDismiss, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$MenuNative$ctor;
	((Object*)self)->dtor = (void*)SuiView$MenuNative$dtor;
	((SuiView$MenuNative*)self)->create = (void*)SuiView$MenuNative$create;
	((SuiView$MenuNative*)self)->buildNativeMenu = (void*)SuiView$MenuNative$buildNativeMenu;
	((SuiView$MenuNative*)self)->show = (void*)SuiView$MenuNative$show;
	((SuiView$MenuNative*)self)->showAt = (void*)SuiView$MenuNative$showAt;
	((SuiView$MenuNative*)self)->showAtScreenPosition = (void*)SuiView$MenuNative$showAtScreenPosition;
	((SuiView$MenuNative*)self)->showAtMouse = (void*)SuiView$MenuNative$showAtMouse;
	((SuiView$MenuNative*)self)->onDismiss = (void*)SuiView$MenuNative$onDismiss;
	((SuiView$MenuNative*)self)->destroy = (void*)SuiView$MenuNative$destroy;
	((SuiView$MenuNative*)self)->dispatchCommand = (void*)SuiView$MenuNative$dispatchCommand;
}

// init function

void SuiView$MenuNative_init(SuiView$MenuNative *self, void *pOwner){
    Vtable_SuiView$MenuNative_init(&_vtable_SuiView$MenuNative);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$MenuNative;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$MenuNative_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$MenuNative * SuiView$MenuNative_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$MenuNative *self = calloc(1, sizeof(SuiView$MenuNative));
	
    SuiView$MenuNative_init(self, pOwner);
    return self;
}


// class members
void  SuiView$MenuNative$ctor(SuiView$MenuNative *  self){
	urgc_set_var_class(&currentMenuNative, self) ;
}


void  SuiView$MenuNative$dtor(SuiView$MenuNative *  self){
	printf("~MenuNative\n") ;
}


void  SuiView$MenuNative$create(SuiView$MenuNative *  self, SuiView$MenuNativeItem *  root){
	urgc_set_field_class(self, (void * )offsetof(SuiView$MenuNative, root) , root) ;
	self->id = self->buildNativeMenu(self, root) ;
}


void  SuiView$MenuNative$show(SuiView$MenuNative *  self){
	SuiCore$Vec2 s = SuiCore$Mouse_getPos() ;
	self->showAtScreenPosition(self, s.x, s.y) ;
}


void  SuiView$MenuNative$showAtMouse(SuiView$MenuNative *  self){
	SuiCore$Vec2 p = SuiCore$Mouse_getPos() ;
	self->showAtScreenPosition(self, p.x, p.y) ;
}


void  SuiView$MenuNative$onDismiss(SuiView$MenuNative *  self){
	printf("\n\nMenuNative菜单已经消失.\n") ;
	if (self->cbOnDismiss) {
		(*(self->cbOnDismiss))((void * )(self->cbOnDismiss)) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP SuiView$__Closure_117_33*  tmpReturn_2 = NULL;
	SuiCore$Timer *  t = SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_117_33(&tmpReturn_2) , 200) ;
}


bool  SuiView$MenuNative$dispatchCommand(SuiView$MenuNative *  self, SuiView$MenuNativeItem *  item, Sui$Window *  win, int  commandId){
	if (item->commandId == commandId) {
		if (item->onActive) {
			(*(item->onActive))((void * )(item->onActive), item) ;
		}
		return true; 
	}
	int  l = item->children->size(item->children) ;
	for (int  i = 0; i < l; i++) {
		SuiView$MenuNativeItem *  kid = (SuiView$MenuNativeItem * )item->children->get(item->children, i) ;
		bool  succ = self->dispatchCommand(self, kid, win, commandId) ;
		if (succ) {
			return true; 
		}
	}
	return false; 
}



static void  __fn___Closure_117_33(SuiView$__Closure_117_33 *  self){
	printf("\nMenuNative.onDismiss Timeout\n") ;
	urgc_set_var_class(&currentMenuNative, NULL) ;
}

static void  __fini___Closure_117_33(SuiView$__Closure_117_33 *  self){
	urgc_free_later(self) ;
}

static SuiView$__Closure_117_33*  __make___Closure_117_33(SuiView$__Closure_117_33 **  __outRef__){
	URGC_VAR_CLEANUP SuiView$__Closure_117_33*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_117_33) , __fini___Closure_117_33) ));
	self->invoke = __fn___Closure_117_33;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

void  SuiView$MenuNative_doCommand(long long  windowId, int  commandId){
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, windowId) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("windowId:%lld win:%s, command:%d\n", windowId, win == NULL ? "Null" : win->getTitle(&tmpReturn_1, win) ->str, commandId) ;
	if (currentMenuNative) {
		currentMenuNative->dispatchCommand(currentMenuNative, currentMenuNative->root, win, commandId) ;
	}
}



