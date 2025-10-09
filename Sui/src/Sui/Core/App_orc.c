
#include "App_orc.h" 

#include <stdlib.h>
#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Mutex_orc.h"
#include "./Window_orc.h"
#include "./Vec2_orc.h"
#include "./ViewBase_orc.h"
#include "./Node_orc.h"
#include "./Emitter_orc.h"
#include "./MouseEvent_orc.h"
#include "./Timer_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$AppEventLoopMessage _vtable_SuiCore$AppEventLoopMessage;

// init meta

void SuiCore$AppEventLoopMessage_initMeta(Vtable_SuiCore$AppEventLoopMessage *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiCore$AppEventLoopMessage* Vtable_SuiCore$AppEventLoopMessage_init(Vtable_SuiCore$AppEventLoopMessage* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$AppEventLoopMessage;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$AppEventLoopMessage_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$AppEventLoopMessage";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$AppEventLoopMessage_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$AppEventLoopMessage_fini(SuiCore$AppEventLoopMessage *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$AppEventLoopMessage_init_fields(SuiCore$AppEventLoopMessage *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$AppEventLoopMessage_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiCore$AppEventLoopMessage_init(SuiCore$AppEventLoopMessage *self, void *pOwner){
    Vtable_SuiCore$AppEventLoopMessage_init(&_vtable_SuiCore$AppEventLoopMessage);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$AppEventLoopMessage;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$AppEventLoopMessage_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$AppEventLoopMessage * SuiCore$AppEventLoopMessage_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$AppEventLoopMessage *self = calloc(1, sizeof(SuiCore$AppEventLoopMessage));
	
    SuiCore$AppEventLoopMessage_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiCore$App _vtable_SuiCore$App;

// init meta

void SuiCore$App_initMeta(Vtable_SuiCore$App *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "windows", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$App, windows), true, false, 1);
	orc_metaField_primitive(&pNext, "_invalidDraw", OrcMetaType_bool, offsetof(SuiCore$App, _invalidDraw), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "postMessageMutex", ((Vtable_Object*)Vtable_Orc$Mutex_init(0)), offsetof(SuiCore$App, postMessageMutex), true, false, 1);
	orc_metaField_class(&pNext, "messageList", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$App, messageList), true, false, 1);

	orc_metaField_method(&pNext, "findWindowById", offsetof(SuiCore$App, findWindowById));
	orc_metaField_method(&pNext, "addWindow", offsetof(SuiCore$App, addWindow));
	orc_metaField_method(&pNext, "eachWindow", offsetof(SuiCore$App, eachWindow));
	orc_metaField_method(&pNext, "removeWindow", offsetof(SuiCore$App, removeWindow));
	orc_metaField_method(&pNext, "layoutAndDrawAllWindows", offsetof(SuiCore$App, layoutAndDrawAllWindows));
	orc_metaField_method(&pNext, "quit", offsetof(SuiCore$App, quit));
	orc_metaField_method(&pNext, "invalidDraw", offsetof(SuiCore$App, invalidDraw));
	orc_metaField_method(&pNext, "invalidLayout", offsetof(SuiCore$App, invalidLayout));
	orc_metaField_method(&pNext, "processDirtyReacts", offsetof(SuiCore$App, processDirtyReacts));
	orc_metaField_method(&pNext, "processRecuDirtyReacts", offsetof(SuiCore$App, processRecuDirtyReacts));
	orc_metaField_method(&pNext, "postMessage_toEventLoop_threadSafe", offsetof(SuiCore$App, postMessage_toEventLoop_threadSafe));
	orc_metaField_method(&pNext, "peekFromMessageList", offsetof(SuiCore$App, peekFromMessageList));
	orc_metaField_method(&pNext, "processMessageList", offsetof(SuiCore$App, processMessageList));
	orc_metaField_method(&pNext, "init", offsetof(SuiCore$App, init));
	orc_metaField_method(&pNext, "runEventLoop", offsetof(SuiCore$App, runEventLoop));
}


// vtable init


Vtable_SuiCore$App* Vtable_SuiCore$App_init(Vtable_SuiCore$App* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$App;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$App_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$App";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$App_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$App_fini(SuiCore$App *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$App*)self)->windows);
	urgc_fini_field_class(self, (void**)&((SuiCore$App*)self)->postMessageMutex);
	urgc_fini_field_class(self, (void**)&((SuiCore$App*)self)->messageList);

}

// init fields function


void SuiCore$App_init_fields(SuiCore$App *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$App_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$App*)self)->windows, Orc$List_new(&tmpNewOwner_1) );
	((SuiCore$App*)self)->_invalidDraw = false;
	URGC_VAR_CLEANUP_CLASS Orc$Mutex*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$App*)self)->postMessageMutex, Orc$Mutex_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$App*)self)->messageList, Orc$List_new(&tmpNewOwner_3) );
    }
	((SuiCore$App*)self)->findWindowById = (void*)SuiCore$App$findWindowById;
	((SuiCore$App*)self)->addWindow = (void*)SuiCore$App$addWindow;
	((SuiCore$App*)self)->eachWindow = (void*)SuiCore$App$eachWindow;
	((SuiCore$App*)self)->removeWindow = (void*)SuiCore$App$removeWindow;
	((SuiCore$App*)self)->layoutAndDrawAllWindows = (void*)SuiCore$App$layoutAndDrawAllWindows;
	((SuiCore$App*)self)->quit = (void*)SuiCore$App$quit;
	((SuiCore$App*)self)->invalidDraw = (void*)SuiCore$App$invalidDraw;
	((SuiCore$App*)self)->invalidLayout = (void*)SuiCore$App$invalidLayout;
	((SuiCore$App*)self)->processDirtyReacts = (void*)SuiCore$App$processDirtyReacts;
	((SuiCore$App*)self)->processRecuDirtyReacts = (void*)SuiCore$App$processRecuDirtyReacts;
	((SuiCore$App*)self)->postMessage_toEventLoop_threadSafe = (void*)SuiCore$App$postMessage_toEventLoop_threadSafe;
	((SuiCore$App*)self)->peekFromMessageList = (void*)SuiCore$App$peekFromMessageList;
	((SuiCore$App*)self)->processMessageList = (void*)SuiCore$App$processMessageList;
	((SuiCore$App*)self)->init = (void*)SuiCore$App$init;
	((SuiCore$App*)self)->runEventLoop = (void*)SuiCore$App$runEventLoop;
}

// init function

void SuiCore$App_init(SuiCore$App *self, void *pOwner){
    Vtable_SuiCore$App_init(&_vtable_SuiCore$App);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$App;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$App_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$App * SuiCore$App_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$App *self = calloc(1, sizeof(SuiCore$App));
	
    SuiCore$App_init(self, pOwner);
    return self;
}


// class members
Sui$Window *  SuiCore$App$findWindowById(SuiCore$App *  self, long long  id){
	for (int  i = 0; i < self->windows->size(self->windows) ; i++) {
		Sui$Window *  window = (Sui$Window * )self->windows->get(self->windows, i) ;
		if (window->id == id) {
			return window; 
		}
	}
	return NULL; 
}


void  SuiCore$App$addWindow(SuiCore$App *  self, Sui$Window *  win){
	self->windows->add(self->windows, win) ;
}


void  SuiCore$App$eachWindow(SuiCore$App *  self, void  (**onWin)(void *  self, Sui$Window *  win)){
	URGC_REF_ARG_WITH_CLEANUP(onWin);

	for (int  i = 0; i < self->windows->size(self->windows) ; i++) {
		Sui$Window *  window = (Sui$Window * )self->windows->get(self->windows, i) ;
		(*(onWin))((void * )(onWin), window) ;
	}
}


void  SuiCore$App$removeWindow(SuiCore$App *  self, Sui$Window *  win){
	SuiCore$HoverSentive *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$sinsHoverSentive() )->clear(tmpThis_1) ;
	self->windows->remove(self->windows, win) ;
	((SuiCore$Node * )win->rootView)->dissolveSubtree(win->rootView) ;
	win->setRootView(win, NULL) ;
	if (self->windows->size(self->windows)  == 0) {
		printf("App.windows.size == 0\n") ;
		self->quit(self) ;
	}
}


void  SuiCore$App$layoutAndDrawAllWindows(SuiCore$App *  self){
	long long  t0 = Orc$Time_unixMs() ;
	for (int  i = 0; i < self->windows->size(self->windows) ; i++) {
		Sui$Window *  win = (Sui$Window * )self->windows->get(self->windows, i) ;
		win->layoutAndDraw(win) ;
	}
	long long  t1 = Orc$Time_unixMs() ;
}


void  SuiCore$App$quit(SuiCore$App *  self){
	exit(0) ;
}


void  SuiCore$App$invalidDraw(SuiCore$App *  self){
	self->_invalidDraw = true;
}


void  SuiCore$App$invalidLayout(SuiCore$App *  self){
	self->_invalidDraw = true;
}


void  SuiCore$App$processDirtyReacts(SuiCore$App *  self){
	if (1) {
		return ; 
	}
	for (int  i = 0; i < self->windows->size(self->windows) ; i++) {
		Sui$Window *  win = (Sui$Window * )self->windows->get(self->windows, i) ;
		self->processRecuDirtyReacts(self, win->rootView) ;
	}
}


void  SuiCore$App$processRecuDirtyReacts(SuiCore$App *  self, SuiCore$Node *  n){
	if (n->_reactDirty) {
		n->_reactDirty = false;
		n->react(n) ;
	}
	int  l = n->getChildrenCount(n) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  kid = n->getChild(n, i) ;
		if (kid) {
			self->processRecuDirtyReacts(self, kid) ;
		}
	}
}


void  SuiCore$App$postMessage_toEventLoop_threadSafe(SuiCore$App *  self, SuiCore$AppEventLoopMessage*  msg){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(msg);

	self->postMessageMutex->lock(self->postMessageMutex) ;
	self->messageList->add(self->messageList, msg) ;
	self->postMessageMutex->unlock(self->postMessageMutex) ;
}


SuiCore$AppEventLoopMessage*  SuiCore$App$peekFromMessageList(SuiCore$AppEventLoopMessage **  __outRef__, SuiCore$App *  self){
	self->postMessageMutex->lock(self->postMessageMutex) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$AppEventLoopMessage*  msg = NULL;
	if (self->messageList->size(self->messageList)  > 0) {
		urgc_set_var_class(&msg, self->messageList->get(self->messageList, 0) ) ;
		self->messageList->removeAt(self->messageList, 0) ;
	}
	self->postMessageMutex->unlock(self->postMessageMutex) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, msg) ; 
}


void  SuiCore$App$processMessageList(SuiCore$App *  self){
	while (true) {
		URGC_VAR_CLEANUP_CLASS SuiCore$AppEventLoopMessage*  msg = self->peekFromMessageList((msg = NULL,&msg), self) ;
		if (msg == NULL) {
			break;
		}
		printf("process AppEventLoopMessage %p\n", msg) ;
	}
	SuiCore$TimerMgr *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$TimerMgr*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiCore$insTimerMgr(&tmpReturn_1) )->fire(tmpThis_1) ;
	SuiCore$tickAnimationFrames() ;
}


void  SuiCore$App$init(SuiCore$App *  self){
	URGC_VAR_CLEANUP_CLASS SuiCore$TimerMgr*  mgr = SuiCore$insTimerMgr((mgr = NULL,&mgr)) ;
	mgr->startThreadTick(mgr) ;
}



static URGC_VAR_CLEANUP_CLASS SuiCore$App*  gApp = NULL;
SuiCore$App*  SuiCore$App_use(SuiCore$App **  __outRef__){
	if (gApp == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$App*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&gApp, SuiCore$App_new(&tmpNewOwner_1) ) ;
		gApp->init(gApp) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, gApp) ; 
}

void  SuiCore$App_onDestroyWindow(long long  id){
	Sui$Window *  tmp = NULL;
	{
		URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
		URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, id) ));
		tmp = win;
		if (!win) {
			return ; 
		}
		app->removeWindow(app, win) ;
	}
}

bool  SuiCore$App_repaintWindowById(long long  id){
	if (!id) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, id) ));
	if (!win) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  title = win->getTitle((title = NULL,&title), win) ;
	win->layoutAndDraw(win) ;
	return true; 
}

void  SuiCore$testApp(){
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	printf("testApp\n") ;
	app->runEventLoop(app) ;
}



