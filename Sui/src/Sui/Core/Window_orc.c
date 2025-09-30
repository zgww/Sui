
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
#include "../Core/Timer_orc.h"
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
typedef struct tagSui$__Block_268_16 Sui$__Block_268_16;

typedef struct tagSui$__Closure_271_30 Sui$__Closure_271_30;



struct tagSui$__Block_268_16 {
	Sui$DragCrossWindowIndicator*  self ;
};





struct tagSui$__Closure_271_30 {
	bool  (*invoke)(Sui$__Closure_271_30 *  self);
	Vtable_Object *  vtable ;
	Sui$__Block_268_16*  __var___Block_268_16 ;
};





// static function declaration
static void  __finiBlock___Block_268_16(Sui$__Block_268_16 *  self);
static bool  __fn___Closure_271_30(Sui$__Closure_271_30 *  self);
static void  __fini___Closure_271_30(Sui$__Closure_271_30 *  self);
static Sui$__Closure_271_30*  __make___Closure_271_30(Sui$__Closure_271_30 **  __outRef__, Sui$__Block_268_16 *  __var___Block_268_16);



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


//vtable instance
Vtable_Sui$DragCrossWindowIndicator _vtable_Sui$DragCrossWindowIndicator;

// init meta

void Sui$DragCrossWindowIndicator_initMeta(Vtable_Sui$DragCrossWindowIndicator *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "dragging", OrcMetaType_bool, offsetof(Sui$DragCrossWindowIndicator, dragging), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "_start", offsetof(Sui$DragCrossWindowIndicator, _start));
	orc_metaField_method(&pNext, "_end", offsetof(Sui$DragCrossWindowIndicator, _end));
	orc_metaField_method(&pNext, "_dragMove", offsetof(Sui$DragCrossWindowIndicator, _dragMove));
	orc_metaField_method(&pNext, "start", offsetof(Sui$DragCrossWindowIndicator, start));
	orc_metaField_method(&pNext, "end", offsetof(Sui$DragCrossWindowIndicator, end));
	orc_metaField_method(&pNext, "onDragMove", offsetof(Sui$DragCrossWindowIndicator, onDragMove));
}


// vtable init


Vtable_Sui$DragCrossWindowIndicator* Vtable_Sui$DragCrossWindowIndicator_init(Vtable_Sui$DragCrossWindowIndicator* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sui$DragCrossWindowIndicator;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sui$DragCrossWindowIndicator_new;
    ((Vtable_Object*)pvt)->className = "Sui$DragCrossWindowIndicator";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sui$DragCrossWindowIndicator_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Sui$DragCrossWindowIndicator_fini(Sui$DragCrossWindowIndicator *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sui$DragCrossWindowIndicator_init_fields(Sui$DragCrossWindowIndicator *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sui$DragCrossWindowIndicator_fini;
	//fields
    {
	((Sui$DragCrossWindowIndicator*)self)->dragging = false;
    }
	((Sui$DragCrossWindowIndicator*)self)->_start = (void*)Sui$DragCrossWindowIndicator$_start;
	((Sui$DragCrossWindowIndicator*)self)->_end = (void*)Sui$DragCrossWindowIndicator$_end;
	((Sui$DragCrossWindowIndicator*)self)->_dragMove = (void*)Sui$DragCrossWindowIndicator$_dragMove;
	((Sui$DragCrossWindowIndicator*)self)->start = (void*)Sui$DragCrossWindowIndicator$start;
	((Sui$DragCrossWindowIndicator*)self)->end = (void*)Sui$DragCrossWindowIndicator$end;
	((Sui$DragCrossWindowIndicator*)self)->onDragMove = (void*)Sui$DragCrossWindowIndicator$onDragMove;
}

// init function

void Sui$DragCrossWindowIndicator_init(Sui$DragCrossWindowIndicator *self, void *pOwner){
    Vtable_Sui$DragCrossWindowIndicator_init(&_vtable_Sui$DragCrossWindowIndicator);

    ((Object*)self)->vtable = (void*)&_vtable_Sui$DragCrossWindowIndicator;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sui$DragCrossWindowIndicator_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sui$DragCrossWindowIndicator * Sui$DragCrossWindowIndicator_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sui$DragCrossWindowIndicator *self = calloc(1, sizeof(Sui$DragCrossWindowIndicator));
	
    Sui$DragCrossWindowIndicator_init(self, pOwner);
    return self;
}


// class members
void  Sui$DragCrossWindowIndicator$start(Sui$DragCrossWindowIndicator *  self){
	URGC_VAR_CLEANUP Sui$__Block_268_16*  __var___Block_268_16 = (__var___Block_268_16=NULL,urgc_init_var((void**)&__var___Block_268_16, orc_alloc_and_set_deleter(sizeof(Sui$__Block_268_16) , __finiBlock___Block_268_16) ));
	urgc_set_field_class(__var___Block_268_16, (void * )offsetof(Sui$__Block_268_16, self) , self) ;
	self->dragging = true;
	self->_start(self) ;
	URGC_VAR_CLEANUP Sui$__Closure_271_30*  tmpReturn_1 = NULL;
	SuiCore$requestAnimationFrame(__make___Closure_271_30(&tmpReturn_1, __var___Block_268_16) ) ;
}


void  Sui$DragCrossWindowIndicator$end(Sui$DragCrossWindowIndicator *  self){
	self->dragging = false;
	self->_end(self) ;
}


void  Sui$DragCrossWindowIndicator$onDragMove(Sui$DragCrossWindowIndicator *  self, SuiCore$Vec2 clientPos){
	self->_dragMove(self) ;
}



static void  __finiBlock___Block_268_16(Sui$__Block_268_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sui$__Block_268_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static bool  __fn___Closure_271_30(Sui$__Closure_271_30 *  self){
	self->__var___Block_268_16->self->onDragMove(self->__var___Block_268_16->self, SuiCore$mkVec2(0, 0) ) ;
	return !self->__var___Block_268_16->self->dragging; 
}

static void  __fini___Closure_271_30(Sui$__Closure_271_30 *  self){
	urgc_set_field(self, (void * )offsetof(Sui$__Closure_271_30, __var___Block_268_16) , NULL) ;
	urgc_free_later(self) ;
}

static Sui$__Closure_271_30*  __make___Closure_271_30(Sui$__Closure_271_30 **  __outRef__, Sui$__Block_268_16 *  __var___Block_268_16){
	URGC_VAR_CLEANUP Sui$__Closure_271_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sui$__Closure_271_30) , __fini___Closure_271_30) ));
	self->invoke = __fn___Closure_271_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sui$__Closure_271_30, __var___Block_268_16) , __var___Block_268_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



