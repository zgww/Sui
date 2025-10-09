
#include "SystemTrayIcon_orc.h" 

#include <stdio.h>
#include <stdlib.h>
#include "../Core/ViewBase_orc.h"
#include "../Core/Mouse_orc.h"
#include "../Core/Vec2_orc.h"
#include "../../Orc/Time_orc.h"
#include "../Core/Timer_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../Core/App_orc.h"
#include "../View/MenuNative_orc.h"
#include "../Core/Window_orc.h"


// static struct 
typedef struct tagSuiView$__Block_106_45 SuiView$__Block_106_45;

typedef struct tagSuiView$__Closure_onActive_113 SuiView$__Closure_onActive_113;



struct tagSuiView$__Block_106_45 {
	SuiView$SystemTrayIcon*  tray ;
};





struct tagSuiView$__Closure_onActive_113 {
	void  (*invoke)(SuiView$__Closure_onActive_113 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiView$__Block_106_45*  __var___Block_106_45 ;
};





// static function declaration
static void  onappexit();
static void  __finiBlock___Block_106_45(SuiView$__Block_106_45 *  self);
static void  __fn___Closure_onActive_113(SuiView$__Closure_onActive_113 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_113(SuiView$__Closure_onActive_113 *  self);
static SuiView$__Closure_onActive_113*  __make___Closure_onActive_113(SuiView$__Closure_onActive_113 **  __outRef__, SuiView$__Block_106_45 *  __var___Block_106_45);



//vtable instance
Vtable_SuiView$SystemTrayIcon _vtable_SuiView$SystemTrayIcon;

// init meta

void SuiView$SystemTrayIcon_initMeta(Vtable_SuiView$SystemTrayIcon *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "uid", OrcMetaType_int, offsetof(SuiView$SystemTrayIcon, uid), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(SuiView$SystemTrayIcon, data), 0, 0, 1, 1);//void
	orc_metaField_class(&pNext, "iconPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$SystemTrayIcon, iconPath), true, false, 1);

	orc_metaField_method(&pNext, "setIconPath", offsetof(SuiView$SystemTrayIcon, setIconPath));
	orc_metaField_method(&pNext, "initData", offsetof(SuiView$SystemTrayIcon, initData));
	orc_metaField_method(&pNext, "init", offsetof(SuiView$SystemTrayIcon, init));
	orc_metaField_method(&pNext, "doDestroy", offsetof(SuiView$SystemTrayIcon, doDestroy));
	orc_metaField_method(&pNext, "destroy", offsetof(SuiView$SystemTrayIcon, destroy));
}


// vtable init


Vtable_SuiView$SystemTrayIcon* Vtable_SuiView$SystemTrayIcon_init(Vtable_SuiView$SystemTrayIcon* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$SystemTrayIcon;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$SystemTrayIcon_new;
    ((Vtable_Object*)pvt)->className = "SuiView$SystemTrayIcon";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$SystemTrayIcon_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$SystemTrayIcon_fini(SuiView$SystemTrayIcon *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$SystemTrayIcon*)self)->iconPath);

}

// init fields function


void SuiView$SystemTrayIcon_init_fields(SuiView$SystemTrayIcon *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$SystemTrayIcon_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiView$SystemTrayIcon*)self)->iconPath, NULL);
    }
	((SuiView$SystemTrayIcon*)self)->setIconPath = (void*)SuiView$SystemTrayIcon$setIconPath;
	((Object*)self)->ctor = (void*)SuiView$SystemTrayIcon$ctor;
	((Object*)self)->dtor = (void*)SuiView$SystemTrayIcon$dtor;
	((SuiView$SystemTrayIcon*)self)->initData = (void*)SuiView$SystemTrayIcon$initData;
	((SuiView$SystemTrayIcon*)self)->init = (void*)SuiView$SystemTrayIcon$init;
	((SuiView$SystemTrayIcon*)self)->doDestroy = (void*)SuiView$SystemTrayIcon$doDestroy;
	((SuiView$SystemTrayIcon*)self)->destroy = (void*)SuiView$SystemTrayIcon$destroy;
}

// init function

void SuiView$SystemTrayIcon_init(SuiView$SystemTrayIcon *self, void *pOwner){
    Vtable_SuiView$SystemTrayIcon_init(&_vtable_SuiView$SystemTrayIcon);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$SystemTrayIcon;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$SystemTrayIcon_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$SystemTrayIcon * SuiView$SystemTrayIcon_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$SystemTrayIcon *self = calloc(1, sizeof(SuiView$SystemTrayIcon));
	
    SuiView$SystemTrayIcon_init(self, pOwner);
    return self;
}


// class members
void  SuiView$SystemTrayIcon$setIconPath(SuiView$SystemTrayIcon *  self, const char *  iconPath){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiView$SystemTrayIcon, iconPath) , Orc$str(&tmpReturn_1, iconPath) ) ;
}


void  SuiView$SystemTrayIcon$ctor(SuiView$SystemTrayIcon *  self){
	static int  id = 100;
	id++;
	self->uid = id;
}


bool  SuiView$SystemTrayIcon$init(SuiView$SystemTrayIcon *  self){
	bool  ok = self->initData(self) ;
	if (ok) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  trays = SuiView$SystemTrayIcons_use((trays = NULL,&trays)) ;
		trays->add(trays, self) ;
	}
	return ok; 
}


void  SuiView$SystemTrayIcon$destroy(SuiView$SystemTrayIcon *  self){
	bool  ok = self->doDestroy(self) ;
	if (ok) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  trays = SuiView$SystemTrayIcons_use((trays = NULL,&trays)) ;
		trays->remove(trays, self) ;
	}
}



static void  onappexit(){
	printf("on app exit\n") ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  list = SuiView$SystemTrayIcons_use((list = NULL,&list)) ;
	for (int  i = list->size(list)  - 1; i >= 0; i--) {
		URGC_VAR_CLEANUP_CLASS SuiView$SystemTrayIcon*  tray = (tray=NULL,urgc_init_var_class((void**)&tray, (SuiView$SystemTrayIcon* )list->get(list, i) ));
		if (tray) {
			tray->destroy(tray) ;
		}
	}
}

Orc$List*  SuiView$SystemTrayIcons_use(Orc$List **  __outRef__){
	static URGC_VAR_CLEANUP_CLASS Orc$List*  list = NULL;
	if (!list) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&list, Orc$List_new(&tmpNewOwner_1) ) ;
		atexit(onappexit) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, list) ; 
}

SuiView$SystemTrayIcon*  SuiView$SystemTrayIcons_findByUid(SuiView$SystemTrayIcon **  __outRef__, int  uid){
	URGC_VAR_CLEANUP_CLASS Orc$List*  list = SuiView$SystemTrayIcons_use((list = NULL,&list)) ;
	for (int  i = 0; i < list->size(list) ; i++) {
		URGC_VAR_CLEANUP_CLASS SuiView$SystemTrayIcon*  tray = (tray=NULL,urgc_init_var_class((void**)&tray, (SuiView$SystemTrayIcon* )list->get(list, i) ));
		if (tray && tray->uid == uid) {
			return urgc_set_var_for_return_class((void ** )__outRef__, tray) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}

void  SuiView$SystemTrayIcon_onMouseData(SuiCore$MouseData md){
	URGC_VAR_CLEANUP SuiView$__Block_106_45*  __var___Block_106_45 = (__var___Block_106_45=NULL,urgc_init_var((void**)&__var___Block_106_45, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_106_45) , __finiBlock___Block_106_45) ));
	printf("on SystemTrayIcon mouseData. uid:%d\n", md.uid) ;
	URGC_VAR_CLEANUP_CLASS SuiView$SystemTrayIcon*  tmpReturn_1 = NULL;
	urgc_set_field_class(__var___Block_106_45, (void * )offsetof(SuiView$__Block_106_45, tray) , SuiView$SystemTrayIcons_findByUid(&tmpReturn_1, md.uid) ) ;
	if (__var___Block_106_45->tray) {
		printf("finded. tray. uid:%d\n", __var___Block_106_45->tray->uid) ;
		if (md.isDoubleClick) {
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP SuiView$__Closure_onActive_113*  tmpReturn_2 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_113(&tmpReturn_2, __var___Block_106_45) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_3, NULL, Orc$str(&tmpReturn_4, "") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_5 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_123_16 = SuiView$mkMenuNativeItem(&tmpReturn_5, o, Orc$str(&tmpReturn_6, "exit") , onActive) , *o = __scopeVar_123_16;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_7 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_124_16 = SuiView$mkMenuNativeItem(&tmpReturn_7, o, Orc$str(&tmpReturn_8, "delete icon") , onActive) , *o = __scopeVar_124_16;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_125_16 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "menu3") , onActive) , *o = __scopeVar_125_16;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_11 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_126_16 = SuiView$mkMenuNativeItem(&tmpReturn_11, o, Orc$str(&tmpReturn_12, "menu4") , onActive) , *o = __scopeVar_126_16;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_13 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_127_16 = SuiView$mkMenuNativeItem(&tmpReturn_13, o, Orc$str(&tmpReturn_14, "menu5") , onActive) , *o = __scopeVar_127_16;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
				n->windowId = md.windowId;
				n->create(n, o) ;
				SuiCore$Vec2 p = SuiCore$Mouse_getPos() ;
				printf("show At:%f, %f\n", p.x, p.y) ;
				n->showAtMouse(n) ;
			}
		}
	}
}

static void  __finiBlock___Block_106_45(SuiView$__Block_106_45 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_106_45, tray) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_onActive_113(SuiView$__Closure_onActive_113 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->label, "delete icon") ) {
		self->__var___Block_106_45->tray->destroy(self->__var___Block_106_45->tray) ;
	}
	if (Orc$String$equals(item->label, "exit") ) {
		exit(0) ;
	}
}

static void  __fini___Closure_onActive_113(SuiView$__Closure_onActive_113 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_onActive_113, __var___Block_106_45) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_onActive_113*  __make___Closure_onActive_113(SuiView$__Closure_onActive_113 **  __outRef__, SuiView$__Block_106_45 *  __var___Block_106_45){
	URGC_VAR_CLEANUP SuiView$__Closure_onActive_113*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_onActive_113) , __fini___Closure_onActive_113) ));
	self->invoke = __fn___Closure_onActive_113;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_onActive_113, __var___Block_106_45) , __var___Block_106_45) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



