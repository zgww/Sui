
#include "Mouse_orc.h" 

#include <stdio.h>
#include "./Vec2_orc.h"
#include "./Window_orc.h"
#include "./MouseEvent_orc.h"
#include "./Event_orc.h"
#include "./App_orc.h"
#include "./ViewBase_orc.h"
#include "./Node_orc.h"
#include "../../Orc/String_orc.h"
#include "./Emitter_orc.h"


// static struct 


// static function declaration


SuiCore$Vec2 SuiCore$Mouse_getPosOfWindow(Sui$Window *  window){
	if (window) {
		SuiCore$Vec2 pos = SuiCore$Mouse_getPos() ;
		SuiCore$Vec2 winPos = window->getPos(window) ;
		return SuiCore$mkVec2(pos.x - winPos.x, pos.y - winPos.y) ; 
	}
	return SuiCore$mkVec2(0.f, 0.f) ; 
}

void  SuiCore$testMouse(){
	SuiCore$Vec2 pos = SuiCore$Mouse_getPos() ;
	SuiCore$Vec2 winPos = SuiCore$Mouse_getPosOfWindow(NULL) ;
	printf("pos:%f,%f. winPos:%f,%f\n", pos.x, pos.y, winPos.x, winPos.y) ;
	SuiCore$Mouse_getPos() ;
}


// get or init meta 
MetaStruct* SuiCore$MouseData_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$MouseData", sizeof( SuiCore$MouseData ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "clientX", OrcMetaType_int, offsetof(SuiCore$MouseData, clientX), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "clientY", OrcMetaType_int, offsetof(SuiCore$MouseData, clientY), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "button", OrcMetaType_int, offsetof(SuiCore$MouseData, button), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "windowId", OrcMetaType_long_long, offsetof(SuiCore$MouseData, windowId), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "isMouseDown", OrcMetaType_bool, offsetof(SuiCore$MouseData, isMouseDown), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "isMouseMove", OrcMetaType_bool, offsetof(SuiCore$MouseData, isMouseMove), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "isMouseUp", OrcMetaType_bool, offsetof(SuiCore$MouseData, isMouseUp), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "isDoubleClick", OrcMetaType_bool, offsetof(SuiCore$MouseData, isDoubleClick), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "uid", OrcMetaType_int, offsetof(SuiCore$MouseData, uid), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "shift", OrcMetaType_bool, offsetof(SuiCore$MouseData, shift), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "alt", OrcMetaType_bool, offsetof(SuiCore$MouseData, alt), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "ctrl", OrcMetaType_bool, offsetof(SuiCore$MouseData, ctrl), 0, 0, 0, 0);//bool
    }
	return meta;
}
static int  mouseDownClientX = 0;
static int  mouseDownClientY = 0;
void  SuiCore$setMouseEventFromMouseData(SuiCore$MouseEvent *  ev, SuiCore$MouseData *  md){
	if (md->isMouseDown) {
		mouseDownClientX = md->clientX;
		mouseDownClientY = md->clientY;
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, md->windowId) ));
	ev->clientX = md->clientX;
	ev->clientY = md->clientY;
	urgc_set_field_class(ev, (void * )offsetof(SuiCore$MouseEvent, window) , win) ;
	ev->mouseDownClientX = mouseDownClientX;
	ev->mouseDownClientY = mouseDownClientY;
	ev->isMouseDown = md->isMouseDown;
	ev->isMouseMove = md->isMouseMove;
	ev->isMouseUp = md->isMouseUp;
	ev->button = md->button;
	ev->ctrl = md->ctrl;
	ev->shift = md->shift;
	ev->alt = md->alt;
}

SuiCore$MouseEvent*  SuiCore$newMouseEventFromMouseData(SuiCore$MouseEvent **  __outRef__, SuiCore$MouseData *  md){
	URGC_VAR_CLEANUP_CLASS SuiCore$MouseEvent*  ev = (ev=NULL,urgc_init_var_class((void**)&ev, SuiCore$MouseEvent_new(&ev) ));
	SuiCore$setMouseEventFromMouseData(ev, md) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ev) ; 
}

void  SuiCore$dispatchMouseEvent(SuiCore$MouseEvent*  ev){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(ev);

	if (!ev->window) {
		return ; 
	}
	if (!ev->window->rootView) {
		return ; 
	}
	SuiCore$ViewBase *  view = ev->window->rootView->hitTest(ev->window->rootView, ev->clientX, ev->clientY) ;
	if (!view) {
		view = ev->window->rootView;
	}
	SuiCore$preprocessMouseEvent(ev) ;
	SuiCore$propagateViewEvent(view, ev) ;
}

void  SuiCore$dispatchMouseMoveEvent(SuiCore$MouseEvent*  ev){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(ev);

	if (!ev->window) {
		return ; 
	}
	if (!ev->window->rootView) {
		return ; 
	}
	SuiCore$HoverSentive *  sen = SuiCore$sinsHoverSentive() ;
	SuiCore$ViewBase *  view = ev->window->rootView->hitTest(ev->window->rootView, ev->clientX, ev->clientY) ;
	if (!view) {
		view = ev->window->rootView;
		sen->onmousemove(sen, ev, NULL) ;
	}
	SuiCore$propagateViewEvent(view, ev) ;
	sen->onmousemove(sen, ev, view) ;
}

void  SuiCore$Mouse_onMouseDown(SuiCore$MouseData md){
	URGC_VAR_CLEANUP_CLASS SuiCore$MouseEvent*  ev = SuiCore$newMouseEventFromMouseData((ev = NULL,&ev), &md) ;
	Orc$String$set(((SuiCore$Event * )ev)->name, "mousedown") ;
	SuiCore$dispatchMouseEvent(ev) ;
}

void  SuiCore$Mouse_onMouseMove(SuiCore$MouseData md){
	URGC_VAR_CLEANUP_CLASS SuiCore$MouseEvent*  ev = SuiCore$newMouseEventFromMouseData((ev = NULL,&ev), &md) ;
	Orc$String$set(((SuiCore$Event * )ev)->name, "mousemove") ;
	SuiCore$dispatchMouseMoveEvent(ev) ;
}

void  SuiCore$Mouse_onMouseUp(SuiCore$MouseData md){
	URGC_VAR_CLEANUP_CLASS SuiCore$MouseEvent*  ev = SuiCore$newMouseEventFromMouseData((ev = NULL,&ev), &md) ;
	Orc$String$set(((SuiCore$Event * )ev)->name, "mouseup") ;
	SuiCore$dispatchMouseEvent(ev) ;
}

void  SuiCore$Mouse_onWheel(SuiCore$MouseData *  md, int  deltaX, int  deltaY){
	URGC_VAR_CLEANUP_CLASS SuiCore$WheelEvent*  ev = (ev=NULL,urgc_init_var_class((void**)&ev, SuiCore$WheelEvent_new(&ev) ));
	SuiCore$setMouseEventFromMouseData(ev, md) ;
	ev->deltaX = deltaX;
	ev->deltaY = deltaY;
	((SuiCore$MouseEvent * )ev)->isWheel = true;
	printf("滚轮事件; clientX:%d, clientY:%d, deltaX:%d, deltaY:%d\n", ((SuiCore$MouseEvent * )ev)->clientX, ((SuiCore$MouseEvent * )ev)->clientY, ev->deltaX, ev->deltaY) ;
	SuiCore$dispatchMouseEvent(ev) ;
}

void  SuiCore$printMouseData(SuiCore$MouseData *  md, const char *  prefix){
	printf("%s; windowId:%lld, button:%s, clientPos:%d,%d eventType:%s\n", prefix, md->windowId, md->button == 1 ? "left" : md->button == 2 ? "middle" : md->button == 3 ? "right" : "none", md->clientX, md->clientY, md->isMouseDown ? "mousedown" : md->isMouseMove ? "mousemove" : md->isDoubleClick ? "doubleclick" : "mouseup") ;
}



