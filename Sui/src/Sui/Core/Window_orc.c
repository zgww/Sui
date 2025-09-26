
#include "Window_orc.h" 

#include <stdio.h>
#include "../Core/Vec2_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Emitter_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Screen_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/Time_orc.h"
#include "./App_orc.h"
#include "./Event_orc.h"
#include "./KeyEvent_orc.h"
#include "./Focus_orc.h"
#include "./Fps_orc.h"
#include "./Canvas_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sui$Window _vtable_Sui$Window;

// init meta

void Sui$Window_initMeta(Vtable_Sui$Window *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "id", OrcMetaType_long_long, offsetof(Sui$Window, id), 0, 0, 0, 0);//longlong
	orc_metaField_struct(&pNext, "fps", SuiCore$Fps_getOrInitMetaStruct(), offsetof(Sui$Window, fps), false, false, 0);
	orc_metaField_class(&pNext, "rootView", ((Vtable_Object*)Vtable_SuiCore$ViewBase_init(0)), offsetof(Sui$Window, rootView), true, false, 1);
	orc_metaField_class(&pNext, "canvas", ((Vtable_Object*)Vtable_SuiCore$Canvas_init(0)), offsetof(Sui$Window, canvas), true, false, 1);
	orc_metaField_primitive(&pNext, "borderless", OrcMetaType_bool, offsetof(Sui$Window, borderless), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(Sui$Window, data), 0, 0, 1, 1);//void
	orc_metaField_primitive(&pNext, "layoutTimes", OrcMetaType_int, offsetof(Sui$Window, layoutTimes), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "setTransparent", offsetof(Sui$Window, setTransparent));
	orc_metaField_method(&pNext, "setRootView", offsetof(Sui$Window, setRootView));
	orc_metaField_method(&pNext, "cleanData", offsetof(Sui$Window, cleanData));
	orc_metaField_method(&pNext, "initData", offsetof(Sui$Window, initData));
	orc_metaField_method(&pNext, "show", offsetof(Sui$Window, show));
	orc_metaField_method(&pNext, "hide", offsetof(Sui$Window, hide));
	orc_metaField_method(&pNext, "maximize", offsetof(Sui$Window, maximize));
	orc_metaField_method(&pNext, "minimize", offsetof(Sui$Window, minimize));
	orc_metaField_method(&pNext, "normal", offsetof(Sui$Window, normal));
	orc_metaField_method(&pNext, "enable", offsetof(Sui$Window, enable));
	orc_metaField_method(&pNext, "close", offsetof(Sui$Window, close));
	orc_metaField_method(&pNext, "setOwner", offsetof(Sui$Window, setOwner));
	orc_metaField_method(&pNext, "layoutAndDraw", offsetof(Sui$Window, layoutAndDraw));
	orc_metaField_method(&pNext, "layout", offsetof(Sui$Window, layout));
	orc_metaField_method(&pNext, "draw", offsetof(Sui$Window, draw));
	orc_metaField_method(&pNext, "isVisible", offsetof(Sui$Window, isVisible));
	orc_metaField_method(&pNext, "onDestroy", offsetof(Sui$Window, onDestroy));
	orc_metaField_method(&pNext, "setTitle", offsetof(Sui$Window, setTitle));
	orc_metaField_method(&pNext, "getTitle", offsetof(Sui$Window, getTitle));
	orc_metaField_method(&pNext, "getPos", offsetof(Sui$Window, getPos));
	orc_metaField_method(&pNext, "setPos", offsetof(Sui$Window, setPos));
	orc_metaField_method(&pNext, "getSize", offsetof(Sui$Window, getSize));
	orc_metaField_method(&pNext, "setSize", offsetof(Sui$Window, setSize));
	orc_metaField_method(&pNext, "setRect", offsetof(Sui$Window, setRect));
	orc_metaField_method(&pNext, "getClientSize", offsetof(Sui$Window, getClientSize));
	orc_metaField_method(&pNext, "moveToCenter", offsetof(Sui$Window, moveToCenter));
	orc_metaField_method(&pNext, "getNonClientInset", offsetof(Sui$Window, getNonClientInset));
}


// vtable init


Vtable_Sui$Window* Vtable_Sui$Window_init(Vtable_Sui$Window* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sui$Window;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Emitter_init(&_vtable_SuiCore$Emitter);

	// init by super vtable init function
    Vtable_SuiCore$Emitter_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Emitter;
    ((Vtable_Object*)pvt)->make = (void*)&Sui$Window_new;
    ((Vtable_Object*)pvt)->className = "Sui$Window";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sui$Window_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sui$Window_fini(Sui$Window *self){
	//super fini
    SuiCore$Emitter_fini((SuiCore$Emitter *)self);

    //字段释放


}

// init fields function


void Sui$Window_init_fields(Sui$Window *self){
	//super class
    SuiCore$Emitter_init_fields((SuiCore$Emitter*)self);

    ((Object*)self)->fini = (void*)Sui$Window_fini;
	//fields
    {
	((Sui$Window*)self)->id = 0;
	URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sui$Window*)self)->rootView, SuiCore$View_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiCore$Canvas*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sui$Window*)self)->canvas, SuiCore$Canvas_new(&tmpNewOwner_2) );
	((Sui$Window*)self)->borderless = false;
	((Sui$Window*)self)->layoutTimes = 0;
    }
	((Object*)self)->ctor = (void*)Sui$Window$ctor;
	((Sui$Window*)self)->setTransparent = (void*)Sui$Window$setTransparent;
	((Sui$Window*)self)->setRootView = (void*)Sui$Window$setRootView;
	((Object*)self)->dtor = (void*)Sui$Window$dtor;
	((Sui$Window*)self)->cleanData = (void*)Sui$Window$cleanData;
	((Sui$Window*)self)->initData = (void*)Sui$Window$initData;
	((Sui$Window*)self)->show = (void*)Sui$Window$show;
	((Sui$Window*)self)->hide = (void*)Sui$Window$hide;
	((Sui$Window*)self)->maximize = (void*)Sui$Window$maximize;
	((Sui$Window*)self)->minimize = (void*)Sui$Window$minimize;
	((Sui$Window*)self)->normal = (void*)Sui$Window$normal;
	((Sui$Window*)self)->enable = (void*)Sui$Window$enable;
	((Sui$Window*)self)->close = (void*)Sui$Window$close;
	((Sui$Window*)self)->setOwner = (void*)Sui$Window$setOwner;
	((Sui$Window*)self)->layoutAndDraw = (void*)Sui$Window$layoutAndDraw;
	((Sui$Window*)self)->layout = (void*)Sui$Window$layout;
	((Sui$Window*)self)->draw = (void*)Sui$Window$draw;
	((Sui$Window*)self)->isVisible = (void*)Sui$Window$isVisible;
	((Sui$Window*)self)->onDestroy = (void*)Sui$Window$onDestroy;
	((Sui$Window*)self)->setTitle = (void*)Sui$Window$setTitle;
	((Sui$Window*)self)->getTitle = (void*)Sui$Window$getTitle;
	((Sui$Window*)self)->getPos = (void*)Sui$Window$getPos;
	((Sui$Window*)self)->setPos = (void*)Sui$Window$setPos;
	((Sui$Window*)self)->getSize = (void*)Sui$Window$getSize;
	((Sui$Window*)self)->setSize = (void*)Sui$Window$setSize;
	((Sui$Window*)self)->setRect = (void*)Sui$Window$setRect;
	((Sui$Window*)self)->getClientSize = (void*)Sui$Window$getClientSize;
	((Sui$Window*)self)->moveToCenter = (void*)Sui$Window$moveToCenter;
	((Sui$Window*)self)->getNonClientInset = (void*)Sui$Window$getNonClientInset;
}

// init function

void Sui$Window_init(Sui$Window *self, void *pOwner){
    Vtable_Sui$Window_init(&_vtable_Sui$Window);

    ((Object*)self)->vtable = (void*)&_vtable_Sui$Window;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sui$Window_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sui$Window * Sui$Window_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sui$Window *self = calloc(1, sizeof(Sui$Window));
	
    Sui$Window_init(self, pOwner);
    return self;
}


// class members
void  Sui$Window$ctor(Sui$Window *  self){
	((SuiCore$Node * )self->rootView)->setOwnerWindow(self->rootView, self) ;
	((SuiCore$Node * )self->rootView)->setMounted(self->rootView, true) ;
	if (Orc_instanceof((Object*)self->rootView, (Vtable_Object*)Vtable_SuiCore$View_init(NULL))) {
		SuiCore$View *  div = (SuiCore$View * )self->rootView;
		div->backgroundColor = 0x00000000;
		printf("bg :  %x\n", div->backgroundColor) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	app->addWindow(app, self) ;
	self->initData(self) ;
}


void  Sui$Window$setRootView(Sui$Window *  self, SuiCore$ViewBase *  v){
	if (v == self->rootView) {
		return ; 
	}
	if (self->rootView) {
		((SuiCore$Node * )self->rootView)->setMounted(self->rootView, false) ;
		((SuiCore$Node * )self->rootView)->setOwnerWindow(self->rootView, NULL) ;
	}
	urgc_set_field_class(self, (void * )offsetof(Sui$Window, rootView) , v) ;
	if (self->rootView) {
		((SuiCore$Node * )self->rootView)->setOwnerWindow(self->rootView, self) ;
		((SuiCore$Node * )self->rootView)->setMounted(self->rootView, true) ;
	}
}


void  Sui$Window$dtor(Sui$Window *  self){
	self->cleanData(self) ;
	printf("释放Window%p\n", self) ;
}


void  Sui$Window$layoutAndDraw(Sui$Window *  self){
	if (!self->isVisible(self) ) {
		return ; 
	}
	self->layoutTimes++;
	long long  t0 = Orc$Time_unixMs() ;
	{
		SuiCore$Fps$startFrame(&self->fps) ;
		{
			SuiCore$Fps$startLayout(&self->fps) ;
			self->layout(self) ;
			SuiCore$Fps$endLayout(&self->fps) ;
		}
		long long  t1 = Orc$Time_unixMs() ;
		{
			SuiCore$Fps$startDraw(&self->fps) ;
			self->draw(self) ;
			SuiCore$Fps$endDraw(&self->fps) ;
		}
		SuiCore$Fps$endFrame(&self->fps) ;
	}
	long long  t2 = Orc$Time_unixMs() ;
}


void  Sui$Window$onDestroy(Sui$Window *  self){
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	app->removeWindow(app, self) ;
}


void  Sui$Window$moveToCenter(Sui$Window *  self){
	SuiCore$Vec2 screenSize = SuiCore$Screen_get_usable_size() ;
	SuiCore$Vec2 size = self->getSize(self) ;
	self->setPos(self, (screenSize.x - size.x) / 2.0, (screenSize.y - size.y) / 2.0) ;
}



void  Sui$testWindow(){
	printf("test Window\n") ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	win->setTitle(win, "title from orc中文啊") ;
	win->setSize(win, 200, 200) ;
	win->setPos(win, 400, 400) ;
	win->show(win) ;
}

void  Sui$dispatchWindowFocusGainedEvent(long long  windowId){
	printf("取得窗口 焦点。。。。\n") ;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, windowId) ));
	URGC_VAR_CLEANUP_CLASS SuiCore$WindowFocusEvent*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiCore$WindowFocusEvent_new(&e) ));
	e->isFocus = true;
	e->isBlur = false;
	urgc_set_field_class(e, (void * )offsetof(SuiCore$WindowFocusEvent, window) , win) ;
	SuiCore$dispatchWindowFocusEvent(e) ;
}

void  Sui$dispatchWindowFocusLostEvent(long long  windowId){
	printf("丢失窗口 焦点。。。。\n") ;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, windowId) ));
	URGC_VAR_CLEANUP_CLASS SuiCore$WindowFocusEvent*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiCore$WindowFocusEvent_new(&e) ));
	e->isFocus = false;
	e->isBlur = true;
	urgc_set_field_class(e, (void * )offsetof(SuiCore$WindowFocusEvent, window) , win) ;
	SuiCore$dispatchWindowFocusEvent(e) ;
}



