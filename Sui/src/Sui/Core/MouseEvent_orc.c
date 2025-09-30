
#include "MouseEvent_orc.h" 

#include <stdio.h>
#include "./Event_orc.h"
#include "./Emitter_orc.h"
#include "./Window_orc.h"
#include "./Node_orc.h"
#include "./Cursor_orc.h"
#include "./Vec2_orc.h"
#include "./ViewBase_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$ViewEvent _vtable_SuiCore$ViewEvent;

// init meta

void SuiCore$ViewEvent_initMeta(Vtable_SuiCore$ViewEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "target", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiCore$ViewEvent, target), true, false, 1);
	orc_metaField_class(&pNext, "currentTarget", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiCore$ViewEvent, currentTarget), true, false, 1);
	orc_metaField_primitive(&pNext, "isCapture", OrcMetaType_bool, offsetof(SuiCore$ViewEvent, isCapture), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "isBubble", offsetof(SuiCore$ViewEvent, isBubble));
}


// vtable init


Vtable_SuiCore$ViewEvent* Vtable_SuiCore$ViewEvent_init(Vtable_SuiCore$ViewEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$ViewEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$ViewEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$ViewEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$ViewEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$ViewEvent_fini(SuiCore$ViewEvent *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void SuiCore$ViewEvent_init_fields(SuiCore$ViewEvent *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiCore$ViewEvent_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiCore$ViewEvent*)self)->target, NULL);
	urgc_set_field_class(self, (void**)&((SuiCore$ViewEvent*)self)->currentTarget, NULL);
	((SuiCore$ViewEvent*)self)->isCapture = false;
    }
	((SuiCore$ViewEvent*)self)->isBubble = (void*)SuiCore$ViewEvent$isBubble;
}

// init function

void SuiCore$ViewEvent_init(SuiCore$ViewEvent *self, void *pOwner){
    Vtable_SuiCore$ViewEvent_init(&_vtable_SuiCore$ViewEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$ViewEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$ViewEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$ViewEvent * SuiCore$ViewEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$ViewEvent *self = calloc(1, sizeof(SuiCore$ViewEvent));
	
    SuiCore$ViewEvent_init(self, pOwner);
    return self;
}


// class members
bool  SuiCore$ViewEvent$isBubble(SuiCore$ViewEvent *  self){
	return !self->isCapture; 
}




// get or init meta 
MetaStruct* SuiCore$ClickRecord_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$ClickRecord", sizeof( SuiCore$ClickRecord ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "clientX", OrcMetaType_int, offsetof(SuiCore$ClickRecord, clientX), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "clientY", OrcMetaType_int, offsetof(SuiCore$ClickRecord, clientY), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "clickUnixMs", OrcMetaType_long_long, offsetof(SuiCore$ClickRecord, clickUnixMs), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "button", OrcMetaType_int, offsetof(SuiCore$ClickRecord, button), 0, 0, 0, 0);//int
    }
	return meta;
}
static SuiCore$ClickRecord clickRecord;

//vtable instance
Vtable_SuiCore$MouseEvent _vtable_SuiCore$MouseEvent;

// init meta

void SuiCore$MouseEvent_initMeta(Vtable_SuiCore$MouseEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "clientX", OrcMetaType_int, offsetof(SuiCore$MouseEvent, clientX), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "clientY", OrcMetaType_int, offsetof(SuiCore$MouseEvent, clientY), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "window", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiCore$MouseEvent, window), true, false, 1);
	orc_metaField_struct(&pNext, "ndcPos", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiCore$MouseEvent, ndcPos), false, false, 0);
	orc_metaField_primitive(&pNext, "button", OrcMetaType_int, offsetof(SuiCore$MouseEvent, button), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "mouseDownClientX", OrcMetaType_int, offsetof(SuiCore$MouseEvent, mouseDownClientX), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "mouseDownClientY", OrcMetaType_int, offsetof(SuiCore$MouseEvent, mouseDownClientY), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "isMouseDown", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, isMouseDown), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isMouseUp", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, isMouseUp), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isMouseMove", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, isMouseMove), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isWheel", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, isWheel), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "ctrl", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, ctrl), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "shift", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, shift), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "alt", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, alt), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isDblClick", OrcMetaType_bool, offsetof(SuiCore$MouseEvent, isDblClick), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "isClick", offsetof(SuiCore$MouseEvent, isClick));
	orc_metaField_method(&pNext, "isClickInBubble", offsetof(SuiCore$MouseEvent, isClickInBubble));
	orc_metaField_method(&pNext, "isDblClickInBubble", offsetof(SuiCore$MouseEvent, isDblClickInBubble));
	orc_metaField_method(&pNext, "toString", offsetof(SuiCore$MouseEvent, toString));
}


// vtable init


Vtable_SuiCore$MouseEvent* Vtable_SuiCore$MouseEvent_init(Vtable_SuiCore$MouseEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$MouseEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewEvent_init(&_vtable_SuiCore$ViewEvent);

	// init by super vtable init function
    Vtable_SuiCore$ViewEvent_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewEvent;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$MouseEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$MouseEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$MouseEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$MouseEvent_fini(SuiCore$MouseEvent *self){
	//super fini
    SuiCore$ViewEvent_fini((SuiCore$ViewEvent *)self);

    //字段释放


}

// init fields function


void SuiCore$MouseEvent_init_fields(SuiCore$MouseEvent *self){
	//super class
    SuiCore$ViewEvent_init_fields((SuiCore$ViewEvent*)self);

    ((Object*)self)->fini = (void*)SuiCore$MouseEvent_fini;
	//fields
    {
	((SuiCore$MouseEvent*)self)->clientX = 0;
	((SuiCore$MouseEvent*)self)->clientY = 0;
	urgc_set_field_class(self, (void**)&((SuiCore$MouseEvent*)self)->window, NULL);
	((SuiCore$MouseEvent*)self)->button = 0;
	((SuiCore$MouseEvent*)self)->mouseDownClientX = 0;
	((SuiCore$MouseEvent*)self)->mouseDownClientY = 0;
	((SuiCore$MouseEvent*)self)->isMouseDown = false;
	((SuiCore$MouseEvent*)self)->isMouseUp = false;
	((SuiCore$MouseEvent*)self)->isMouseMove = false;
	((SuiCore$MouseEvent*)self)->isWheel = false;
	((SuiCore$MouseEvent*)self)->ctrl = false;
	((SuiCore$MouseEvent*)self)->shift = false;
	((SuiCore$MouseEvent*)self)->alt = false;
	((SuiCore$MouseEvent*)self)->isDblClick = false;
    }
	((SuiCore$MouseEvent*)self)->isClick = (void*)SuiCore$MouseEvent$isClick;
	((SuiCore$MouseEvent*)self)->isClickInBubble = (void*)SuiCore$MouseEvent$isClickInBubble;
	((SuiCore$MouseEvent*)self)->isDblClickInBubble = (void*)SuiCore$MouseEvent$isDblClickInBubble;
	((SuiCore$MouseEvent*)self)->toString = (void*)SuiCore$MouseEvent$toString;
}

// init function

void SuiCore$MouseEvent_init(SuiCore$MouseEvent *self, void *pOwner){
    Vtable_SuiCore$MouseEvent_init(&_vtable_SuiCore$MouseEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$MouseEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$MouseEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$MouseEvent * SuiCore$MouseEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$MouseEvent *self = calloc(1, sizeof(SuiCore$MouseEvent));
	
    SuiCore$MouseEvent_init(self, pOwner);
    return self;
}


// class members
bool  SuiCore$MouseEvent$isClick(SuiCore$MouseEvent *  self){
	if (self->isMouseUp) {
		int  dx = self->clientX - self->mouseDownClientX;
		int  dy = self->clientY - self->mouseDownClientY;
		return dx * dx + dy * dy < SuiCore$MouseEvent_clickOffsetThreshold * SuiCore$MouseEvent_clickOffsetThreshold; 
	}
	return false; 
}


bool  SuiCore$MouseEvent$isClickInBubble(SuiCore$MouseEvent *  self){
	return !((SuiCore$ViewEvent * )self)->isCapture && self->isClick(self) ; 
}


bool  SuiCore$MouseEvent$isDblClickInBubble(SuiCore$MouseEvent *  self){
	return !((SuiCore$ViewEvent * )self)->isCapture && self->isDblClick; 
}


Orc$String*  SuiCore$MouseEvent$toString(Orc$String **  __outRef__, SuiCore$MouseEvent *  self){
	char  buffer[1024];
	snprintf(buffer, 1023, "MouseEvent(%s,window:%p, pos:%d,%d, downPos:%d,%d, type:%s)", ((SuiCore$Event * )self)->name->str, self->window, self->clientX, self->clientY, self->mouseDownClientX, self->mouseDownClientY, self->isMouseDown ? "mousedown" : self->isMouseUp ? "mouseup" : self->isMouseMove ? "mousemove" : self->isWheel ? "wheel" : "none") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), buffer) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}




//vtable instance
Vtable_SuiCore$MouseEnterEvent _vtable_SuiCore$MouseEnterEvent;

// init meta

void SuiCore$MouseEnterEvent_initMeta(Vtable_SuiCore$MouseEnterEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiCore$MouseEnterEvent* Vtable_SuiCore$MouseEnterEvent_init(Vtable_SuiCore$MouseEnterEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$MouseEnterEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$MouseEvent_init(&_vtable_SuiCore$MouseEvent);

	// init by super vtable init function
    Vtable_SuiCore$MouseEvent_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$MouseEvent;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$MouseEnterEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$MouseEnterEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$MouseEnterEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$MouseEnterEvent_fini(SuiCore$MouseEnterEvent *self){
	//super fini
    SuiCore$MouseEvent_fini((SuiCore$MouseEvent *)self);

    //字段释放


}

// init fields function


void SuiCore$MouseEnterEvent_init_fields(SuiCore$MouseEnterEvent *self){
	//super class
    SuiCore$MouseEvent_init_fields((SuiCore$MouseEvent*)self);

    ((Object*)self)->fini = (void*)SuiCore$MouseEnterEvent_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiCore$MouseEnterEvent_init(SuiCore$MouseEnterEvent *self, void *pOwner){
    Vtable_SuiCore$MouseEnterEvent_init(&_vtable_SuiCore$MouseEnterEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$MouseEnterEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$MouseEnterEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$MouseEnterEvent * SuiCore$MouseEnterEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$MouseEnterEvent *self = calloc(1, sizeof(SuiCore$MouseEnterEvent));
	
    SuiCore$MouseEnterEvent_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiCore$MouseLeaveEvent _vtable_SuiCore$MouseLeaveEvent;

// init meta

void SuiCore$MouseLeaveEvent_initMeta(Vtable_SuiCore$MouseLeaveEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiCore$MouseLeaveEvent* Vtable_SuiCore$MouseLeaveEvent_init(Vtable_SuiCore$MouseLeaveEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$MouseLeaveEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$MouseEvent_init(&_vtable_SuiCore$MouseEvent);

	// init by super vtable init function
    Vtable_SuiCore$MouseEvent_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$MouseEvent;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$MouseLeaveEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$MouseLeaveEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$MouseLeaveEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$MouseLeaveEvent_fini(SuiCore$MouseLeaveEvent *self){
	//super fini
    SuiCore$MouseEvent_fini((SuiCore$MouseEvent *)self);

    //字段释放


}

// init fields function


void SuiCore$MouseLeaveEvent_init_fields(SuiCore$MouseLeaveEvent *self){
	//super class
    SuiCore$MouseEvent_init_fields((SuiCore$MouseEvent*)self);

    ((Object*)self)->fini = (void*)SuiCore$MouseLeaveEvent_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiCore$MouseLeaveEvent_init(SuiCore$MouseLeaveEvent *self, void *pOwner){
    Vtable_SuiCore$MouseLeaveEvent_init(&_vtable_SuiCore$MouseLeaveEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$MouseLeaveEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$MouseLeaveEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$MouseLeaveEvent * SuiCore$MouseLeaveEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$MouseLeaveEvent *self = calloc(1, sizeof(SuiCore$MouseLeaveEvent));
	
    SuiCore$MouseLeaveEvent_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiCore$WheelEvent _vtable_SuiCore$WheelEvent;

// init meta

void SuiCore$WheelEvent_initMeta(Vtable_SuiCore$WheelEvent *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "deltaY", OrcMetaType_int, offsetof(SuiCore$WheelEvent, deltaY), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "deltaX", OrcMetaType_int, offsetof(SuiCore$WheelEvent, deltaX), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiCore$WheelEvent* Vtable_SuiCore$WheelEvent_init(Vtable_SuiCore$WheelEvent* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$WheelEvent;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$MouseEvent_init(&_vtable_SuiCore$MouseEvent);

	// init by super vtable init function
    Vtable_SuiCore$MouseEvent_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$MouseEvent;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$WheelEvent_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$WheelEvent";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$WheelEvent_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$WheelEvent_fini(SuiCore$WheelEvent *self){
	//super fini
    SuiCore$MouseEvent_fini((SuiCore$MouseEvent *)self);

    //字段释放


}

// init fields function


void SuiCore$WheelEvent_init_fields(SuiCore$WheelEvent *self){
	//super class
    SuiCore$MouseEvent_init_fields((SuiCore$MouseEvent*)self);

    ((Object*)self)->fini = (void*)SuiCore$WheelEvent_fini;
	//fields
    {
	((SuiCore$WheelEvent*)self)->deltaY = 0;
	((SuiCore$WheelEvent*)self)->deltaX = 0;
    }
	
}

// init function

void SuiCore$WheelEvent_init(SuiCore$WheelEvent *self, void *pOwner){
    Vtable_SuiCore$WheelEvent_init(&_vtable_SuiCore$WheelEvent);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$WheelEvent;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$WheelEvent_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$WheelEvent * SuiCore$WheelEvent_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$WheelEvent *self = calloc(1, sizeof(SuiCore$WheelEvent));
	
    SuiCore$WheelEvent_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiCore$MouseEventListener _vtable_SuiCore$MouseEventListener;

// init meta

void SuiCore$MouseEventListener_initMeta(Vtable_SuiCore$MouseEventListener *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "onEvent", offsetof(SuiCore$MouseEventListener, onEvent));
}


// vtable init


Vtable_SuiCore$MouseEventListener* Vtable_SuiCore$MouseEventListener_init(Vtable_SuiCore$MouseEventListener* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$MouseEventListener;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$MouseEventListener_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$MouseEventListener";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$MouseEventListener_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$MouseEventListener_fini(SuiCore$MouseEventListener *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiCore$MouseEventListener_init_fields(SuiCore$MouseEventListener *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$MouseEventListener_fini;
	//fields
    {
	
    }
	((SuiCore$MouseEventListener*)self)->onEvent = (void*)SuiCore$MouseEventListener$onEvent;
}

// init function

void SuiCore$MouseEventListener_init(SuiCore$MouseEventListener *self, void *pOwner){
    Vtable_SuiCore$MouseEventListener_init(&_vtable_SuiCore$MouseEventListener);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$MouseEventListener;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$MouseEventListener_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$MouseEventListener * SuiCore$MouseEventListener_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$MouseEventListener *self = calloc(1, sizeof(SuiCore$MouseEventListener));
	
    SuiCore$MouseEventListener_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$MouseEventListener$onEvent(SuiCore$MouseEventListener *  self, SuiCore$MouseEvent *  ev){
	
}



int  SuiCore$MouseEvent_clickOffsetThreshold = 10;

//vtable instance
Vtable_SuiCore$HoverSentive _vtable_SuiCore$HoverSentive;

// init meta

void SuiCore$HoverSentive_initMeta(Vtable_SuiCore$HoverSentive *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "hoverings", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$HoverSentive, hoverings), true, false, 1);

	orc_metaField_method(&pNext, "clear", offsetof(SuiCore$HoverSentive, clear));
	orc_metaField_method(&pNext, "setHover", offsetof(SuiCore$HoverSentive, setHover));
	orc_metaField_method(&pNext, "onmousemove", offsetof(SuiCore$HoverSentive, onmousemove));
	orc_metaField_method(&pNext, "onmouseleave", offsetof(SuiCore$HoverSentive, onmouseleave));
}


// vtable init


Vtable_SuiCore$HoverSentive* Vtable_SuiCore$HoverSentive_init(Vtable_SuiCore$HoverSentive* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$HoverSentive;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$HoverSentive_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$HoverSentive";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$HoverSentive_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$HoverSentive_fini(SuiCore$HoverSentive *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiCore$HoverSentive_init_fields(SuiCore$HoverSentive *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$HoverSentive_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$HoverSentive*)self)->hoverings, Orc$List_new(&tmpNewOwner_1) );
    }
	((SuiCore$HoverSentive*)self)->clear = (void*)SuiCore$HoverSentive$clear;
	((SuiCore$HoverSentive*)self)->setHover = (void*)SuiCore$HoverSentive$setHover;
	((SuiCore$HoverSentive*)self)->onmousemove = (void*)SuiCore$HoverSentive$onmousemove;
	((SuiCore$HoverSentive*)self)->onmouseleave = (void*)SuiCore$HoverSentive$onmouseleave;
}

// init function

void SuiCore$HoverSentive_init(SuiCore$HoverSentive *self, void *pOwner){
    Vtable_SuiCore$HoverSentive_init(&_vtable_SuiCore$HoverSentive);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$HoverSentive;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$HoverSentive_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$HoverSentive * SuiCore$HoverSentive_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$HoverSentive *self = calloc(1, sizeof(SuiCore$HoverSentive));
	
    SuiCore$HoverSentive_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$HoverSentive$clear(SuiCore$HoverSentive *  self){
	self->hoverings->clear(self->hoverings) ;
}


void  SuiCore$HoverSentive$setHover(SuiCore$HoverSentive *  self, SuiCore$Node *  node, bool  hover){
	if (Orc_instanceof((Object*)node, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )node;
		vb->setHover(vb, hover) ;
	}
}


void  SuiCore$HoverSentive$onmousemove(SuiCore$HoverSentive *  self, SuiCore$MouseEvent *  e, SuiCore$ViewBase *  hitTestView){
	URGC_VAR_CLEANUP_CLASS Orc$List*  addlist = (addlist=NULL,urgc_init_var_class((void**)&addlist, Orc$List_new(&addlist) ));
	URGC_VAR_CLEANUP_CLASS Orc$List*  dellist = (dellist=NULL,urgc_init_var_class((void**)&dellist, Orc$List_new(&dellist) ));
	Orc$List *  hoverings = self->hoverings;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$List*  parents = (parents=NULL,urgc_init_var_class((void**)&parents, hitTestView ? ((SuiCore$Node * )hitTestView)->getAncients(&tmpReturn_1, hitTestView, true)  : Orc$List_new(&tmpNewOwner_2) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  cursor = Orc$str((cursor = NULL,&cursor), "unset") ;
	for (int  i = hoverings->size(hoverings)  - 1; i >= 0; i--) {
		SuiCore$ViewBase *  v = (SuiCore$ViewBase * )hoverings->get(hoverings, i) ;
		if (!parents->has(parents, v) ) {
			dellist->add(dellist, v) ;
			hoverings->removeAt(hoverings, i) ;
			self->setHover(self, v, false) ;
		}
	}
	for (int  i = 0; i < parents->size(parents) ; i++) {
		SuiCore$ViewBase *  v = (SuiCore$ViewBase * )parents->get(parents, i) ;
		if (Orc_instanceof((Object*)v, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
			if (Orc$String$notEquals(v->cursor, "")  && !Orc$String$equals(v->cursor, "unset") ) {
				urgc_set_var_class(&cursor, v->cursor) ;
			}
			if (v && !hoverings->has(hoverings, v) ) {
				addlist->add(addlist, v) ;
				hoverings->add(hoverings, v) ;
				self->setHover(self, v, true) ;
			}
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$MouseLeaveEvent*  leave = (leave=NULL,urgc_init_var_class((void**)&leave, SuiCore$MouseLeaveEvent_new(&leave) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(leave, (void * )offsetof(SuiCore$Event, name) , Orc$str(&tmpReturn_3, "mouseleave") ) ;
	((SuiCore$MouseEvent * )leave)->clientX = e->clientX;
	((SuiCore$MouseEvent * )leave)->clientY = e->clientY;
	((SuiCore$MouseEvent * )leave)->button = 0;
	urgc_set_field_class(leave, (void * )offsetof(SuiCore$MouseEvent, window) , e->window) ;
	int  l = dellist->size(dellist) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = (SuiCore$ViewBase * )dellist->get(dellist, i) ;
		((SuiCore$Emitter * )v)->emit(v, leave) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$MouseEnterEvent*  enter = (enter=NULL,urgc_init_var_class((void**)&enter, SuiCore$MouseEnterEvent_new(&enter) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	urgc_set_field_class(enter, (void * )offsetof(SuiCore$Event, name) , Orc$str(&tmpReturn_4, "mouseenter") ) ;
	((SuiCore$MouseEvent * )enter)->clientX = e->clientX;
	((SuiCore$MouseEvent * )enter)->clientY = e->clientY;
	((SuiCore$MouseEvent * )enter)->button = 0;
	urgc_set_field_class(enter, (void * )offsetof(SuiCore$MouseEvent, window) , e->window) ;
	l = addlist->size(addlist) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = (SuiCore$ViewBase * )addlist->get(addlist, i) ;
		((SuiCore$Emitter * )v)->emit(v, enter) ;
	}
	SuiCore$Cursor *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$Cursor*  tmpReturn_5 = NULL;
	(tmpThis_1 = SuiCore$Cursor_ins(&tmpReturn_5) )->setCursor(tmpThis_1, cursor->str) ;
}


void  SuiCore$HoverSentive$onmouseleave(SuiCore$HoverSentive *  self, Sui$Window *  win){
	URGC_VAR_CLEANUP_CLASS SuiCore$MouseEvent*  leave = (leave=NULL,urgc_init_var_class((void**)&leave, SuiCore$MouseEvent_new(&leave) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(leave, (void * )offsetof(SuiCore$Event, name) , Orc$str(&tmpReturn_1, "mouseleave") ) ;
	leave->clientX = 0;
	leave->clientY = 0;
	leave->button = 0;
	urgc_set_field_class(leave, (void * )offsetof(SuiCore$MouseEvent, window) , win) ;
	int  l = self->hoverings->size(self->hoverings) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = (SuiCore$ViewBase * )self->hoverings->get(self->hoverings, i) ;
		if (Orc_instanceof((Object*)v, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
			self->setHover(self, v, false) ;
			((SuiCore$Emitter * )v)->emit(v, leave) ;
		}
	}
	self->hoverings->clear(self->hoverings) ;
}



SuiCore$HoverSentive *  SuiCore$sinsHoverSentive(){
	static URGC_VAR_CLEANUP_CLASS SuiCore$HoverSentive*  ins = NULL;
	if (ins == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$HoverSentive*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ins, SuiCore$HoverSentive_new(&tmpNewOwner_1) ) ;
	}
	return ins; 
}

void  SuiCore$preprocessMouseEvent(SuiCore$MouseEvent *  ev){
	if (ev->isClick(ev) ) {
		long long  nowMs = Orc$Time_unixMs() ;
		int  dx = ev->clientX - clickRecord.clientX;
		int  dy = ev->clientY - clickRecord.clientY;
		int  threshold = 10 * 10;
		long long  msThreshold = 400;
		long long  msGap = nowMs - clickRecord.clickUnixMs;
		printf("\n\n预处理鼠标事件. dx:%d, dy:%d, msGap:%lld\n", dx, dy, msGap) ;
		if (clickRecord.button == ev->button && msGap < msThreshold && dx * dx < threshold && dy * dy < threshold) {
			ev->isDblClick = true;
		}
		else {
			ev->isDblClick = false;
		}
		if (ev->isDblClick) {
			printf("触了了双击事件\n\n") ;
		}
		clickRecord.clientX = ev->clientX;
		clickRecord.clientY = ev->clientY;
		clickRecord.clickUnixMs = nowMs;
		clickRecord.button = ev->button;
	}
}

void  SuiCore$propagateViewEvent(SuiCore$ViewBase *  view, SuiCore$ViewEvent *  ev){
	bool  isBreak = false;
	URGC_VAR_CLEANUP_CLASS Orc$List*  nodes = ((SuiCore$Node * )view)->getAncients((nodes = NULL,&nodes), view, true) ;
	ev->isCapture = true;
	for (int  i = nodes->size(nodes)  - 1; i >= 0; i--) {
		SuiCore$ViewBase *  n = (SuiCore$ViewBase * )nodes->get(nodes, i) ;
		urgc_set_field_class(ev, (void * )offsetof(SuiCore$ViewEvent, currentTarget) , n) ;
		((SuiCore$Emitter * )n)->emit(n, ev) ;
		if (((SuiCore$Event * )ev)->isStopPropagation) {
			break;
		}
	}
	if (!((SuiCore$Event * )ev)->isStopPropagation) {
		ev->isCapture = false;
		int  l = nodes->size(nodes) ;
		for (int  i = 0; i < l; i++) {
			SuiCore$ViewBase *  n = (SuiCore$ViewBase * )nodes->get(nodes, i) ;
			urgc_set_field_class(ev, (void * )offsetof(SuiCore$ViewEvent, currentTarget) , n) ;
			((SuiCore$Emitter * )n)->emit(n, ev) ;
			if (((SuiCore$Event * )ev)->isStopPropagation) {
				break;
			}
		}
	}
	urgc_set_field_class(ev, (void * )offsetof(SuiCore$ViewEvent, currentTarget) , NULL) ;
}



