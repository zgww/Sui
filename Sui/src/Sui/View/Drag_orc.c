
#include "Drag_orc.h" 

#include <stdio.h>
#include "../Core/ViewBase_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../Core/Emitter_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Cursor_orc.h"
#include "../../Orc/String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$Drag _vtable_SuiView$Drag;

// init meta

void SuiView$Drag_initMeta(Vtable_SuiView$Drag *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "currentClientPos", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiView$Drag, currentClientPos), false, false, 0);
	orc_metaField_struct(&pNext, "downClientPos", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiView$Drag, downClientPos), false, false, 0);
	orc_metaField_struct(&pNext, "deltaPos", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiView$Drag, deltaPos), false, false, 0);
	orc_metaField_class(&pNext, "cursor", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$Drag, cursor), true, false, 1);
	orc_metaField_primitive(&pNext, "isDragChecking", OrcMetaType_bool, offsetof(SuiView$Drag, isDragChecking), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isDragEnd", OrcMetaType_bool, offsetof(SuiView$Drag, isDragEnd), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isDragStart", OrcMetaType_bool, offsetof(SuiView$Drag, isDragStart), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isDragging", OrcMetaType_bool, offsetof(SuiView$Drag, isDragging), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "moveThreshold", OrcMetaType_float, offsetof(SuiView$Drag, moveThreshold), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "data", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiView$Drag, data), true, false, 1);
	orc_metaField_class(&pNext, "mouseEvent", ((Vtable_Object*)Vtable_SuiCore$MouseEvent_init(0)), offsetof(SuiView$Drag, mouseEvent), false, true, 1);
	orc_metaField_primitive(&pNext, "mouseDownButton", OrcMetaType_int, offsetof(SuiView$Drag, mouseDownButton), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "setStatus", offsetof(SuiView$Drag, setStatus));
	orc_metaField_method(&pNext, "onMouseDown_byPrefer", offsetof(SuiView$Drag, onMouseDown_byPrefer));
	orc_metaField_method(&pNext, "onMouseDownIf", offsetof(SuiView$Drag, onMouseDownIf));
	orc_metaField_method(&pNext, "onMouseDown", offsetof(SuiView$Drag, onMouseDown));
}


// vtable init


Vtable_SuiView$Drag* Vtable_SuiView$Drag_init(Vtable_SuiView$Drag* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Drag;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Listener_init(&_vtable_SuiCore$Listener);

	// init by super vtable init function
    Vtable_SuiCore$Listener_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Listener;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Drag_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Drag";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Drag_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Drag_fini(SuiView$Drag *self){
	//super fini
    SuiCore$Listener_fini((SuiCore$Listener *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$Drag*)self)->cursor);
	urgc_fini_field_class(self, (void**)&((SuiView$Drag*)self)->data);

}

// init fields function


void SuiView$Drag_init_fields(SuiView$Drag *self){
	//super class
    SuiCore$Listener_init_fields((SuiCore$Listener*)self);

    ((Object*)self)->fini = (void*)SuiView$Drag_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((SuiView$Drag*)self)->onDrag, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$Drag*)self)->cursor, NULL);
	((SuiView$Drag*)self)->isDragChecking = false;
	((SuiView$Drag*)self)->isDragEnd = false;
	((SuiView$Drag*)self)->isDragStart = false;
	((SuiView$Drag*)self)->isDragging = false;
	((SuiView$Drag*)self)->moveThreshold = 5;
	urgc_set_field_class(self, (void**)&((SuiView$Drag*)self)->data, NULL);
	((SuiView$Drag*)self)->mouseEvent = NULL;
	((SuiView$Drag*)self)->mouseDownButton = 1;
    }
	((Object*)self)->dtor = (void*)SuiView$Drag$dtor;
	((SuiView$Drag*)self)->setStatus = (void*)SuiView$Drag$setStatus;
	((SuiView$Drag*)self)->onMouseDown_byPrefer = (void*)SuiView$Drag$onMouseDown_byPrefer;
	((SuiView$Drag*)self)->onMouseDownIf = (void*)SuiView$Drag$onMouseDownIf;
	((SuiView$Drag*)self)->onMouseDown = (void*)SuiView$Drag$onMouseDown;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiView$Drag$onListenerEvent;
}

// init function

void SuiView$Drag_init(SuiView$Drag *self, void *pOwner){
    Vtable_SuiView$Drag_init(&_vtable_SuiView$Drag);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Drag;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Drag_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Drag * SuiView$Drag_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Drag *self = calloc(1, sizeof(SuiView$Drag));
	
    SuiView$Drag_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Drag$dtor(SuiView$Drag *  self){
	printf(".Drag\n") ;
}


void  SuiView$Drag$setStatus(SuiView$Drag *  self, const char *  status){
	self->isDragEnd = Orc$strEq(status, "end") ;
	self->isDragStart = Orc$strEq(status, "start") ;
	self->isDragging = Orc$strEq(status, "dragging") ;
	self->isDragChecking = Orc$strEq(status, "checking") ;
	if (self->cursor) {
		if (self->isDragStart) {
			SuiCore$Cursor *  tmpThis_1 = NULL;
			URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  tmpReturn_1 = NULL;
			(tmpThis_1 = SuiCore$Cursor_ins(&tmpReturn_1) )->setCursor(tmpThis_1, self->cursor->str) ;
			SuiCore$Cursor *  tmpThis_2 = NULL;
			URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  tmpReturn_2 = NULL;
			(tmpThis_2 = SuiCore$Cursor_ins(&tmpReturn_2) )->setIsLocked(tmpThis_2, true) ;
		}
		else if (self->isDragEnd) {
			SuiCore$Cursor *  tmpThis_3 = NULL;
			URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  tmpReturn_3 = NULL;
			(tmpThis_3 = SuiCore$Cursor_ins(&tmpReturn_3) )->setCursor(tmpThis_3, "normal") ;
			SuiCore$Cursor *  tmpThis_4 = NULL;
			URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  tmpReturn_4 = NULL;
			(tmpThis_4 = SuiCore$Cursor_ins(&tmpReturn_4) )->setIsLocked(tmpThis_4, false) ;
		}
	}
}


void  SuiView$Drag$onMouseDown_byPrefer(SuiView$Drag *  self, SuiCore$Event *  e, int  button, bool  cap, bool  bubble){
	SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	if (me == NULL || !(Orc_instanceof((Object*)me, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL)))) {
		return ; 
	}
	if (!me->isMouseDown) {
		return ; 
	}
	if (me->button != button) {
		return ; 
	}
	if (((SuiCore$ViewEvent * )me)->isCapture && !cap) {
		return ; 
	}
	if (((SuiCore$ViewEvent * )me)->isBubble(me)  && !bubble) {
		return ; 
	}
	self->onMouseDown(self, e) ;
}


void  SuiView$Drag$onMouseDownIf(SuiView$Drag *  self, SuiCore$Event *  e){
	
}


void  SuiView$Drag$onMouseDown(SuiView$Drag *  self, SuiCore$Event *  e){
	SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	if (me == NULL || !(Orc_instanceof((Object*)me, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL)))) {
		return ; 
	}
	if (!me->isMouseDown) {
		return ; 
	}
	self->mouseDownButton = me->button;
	self->mouseEvent = me;
	printf("\n\nDrag onMouseDown\n") ;
	SuiCore$ViewBase *  rv = me->window->rootView;
	if (rv != NULL) {
		((SuiCore$Emitter * )rv)->removeListener(rv, self) ;
		((SuiCore$Emitter * )rv)->addListener(rv, self) ;
	}
	self->deltaPos.x = 0;
	self->deltaPos.y = 0;
	self->downClientPos.x = me->clientX;
	self->downClientPos.y = me->clientY;
	self->currentClientPos = self->downClientPos;
	self->setStatus(self, "checking") ;
	if (self->onDrag != NULL) {
		(*(self->onDrag))((void * )(self->onDrag), self) ;
	}
}


void  SuiView$Drag$onListenerEvent(SuiView$Drag *  self, SuiCore$Event *  ev){
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		self->mouseEvent = me;
		if (((SuiCore$ViewEvent * )me)->isCapture) {
			if (me->isMouseUp) {
				printf("\n\nDrag onMouseUp\n") ;
				SuiCore$ViewBase *  rv = me->window->rootView;
				((SuiCore$Emitter * )rv)->removeListener(rv, self) ;
				if (self->isDragging) {
					((SuiCore$Event * )me)->stopPropagation(me) ;
					self->setStatus(self, "end") ;
					if (self->onDrag != NULL) {
						(*(self->onDrag))((void * )(self->onDrag), self) ;
					}
				}
				self->setStatus(self, "idle") ;
				return ; 
			}
			else if (me->isMouseMove) {
				if (self->isDragging) {
					((SuiCore$Event * )me)->stopImmediatePropagation(me) ;
				}
				else {
					((SuiCore$Event * )me)->stopPropagation(me) ;
				}
				self->deltaPos.x = me->clientX - self->currentClientPos.x;
				self->deltaPos.y = me->clientY - self->currentClientPos.y;
				self->currentClientPos.x = me->clientX;
				self->currentClientPos.y = me->clientY;
				if (self->isDragChecking) {
					float  moveX = me->clientX - self->downClientPos.x;
					float  moveY = me->clientY - self->downClientPos.y;
					float  moveDistance = moveX * moveX + moveY * moveY;
					if (moveDistance >= self->moveThreshold * self->moveThreshold) {
						((SuiCore$Event * )me)->stopImmediatePropagation(me) ;
						self->setStatus(self, "start") ;
						if (self->onDrag != NULL) {
							(*(self->onDrag))((void * )(self->onDrag), self) ;
						}
						self->setStatus(self, "dragging") ;
						return ; 
					}
				}
				if (0) {
					printf("drag status:%d,%d,%d,%d\n", self->isDragStart, self->isDragChecking, self->isDragging, self->isDragEnd) ;
				}
				if (self->onDrag != NULL) {
					(*(self->onDrag))((void * )(self->onDrag), self) ;
				}
			}
		}
	}
}





