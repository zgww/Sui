
#include "Button_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/ImageView_orc.h"
#include "../Core/Canvas_orc.h"
#include "../View/TextView_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/Inset_orc.h"
#include "../../SuiDesigner/Inspector_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$Button _vtable_SuiView$Button;

// init meta

void SuiView$Button_initMeta(Vtable_SuiView$Button *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "labelColor", OrcMetaType_int, offsetof(SuiView$Button, labelColor), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "label", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$Button, label), true, false, 1);
	orc_metaField_class(&pNext, "src", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$Button, src), true, false, 1);
	orc_metaField_primitive(&pNext, "in_group", OrcMetaType_bool, offsetof(SuiView$Button, in_group), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "checked", OrcMetaType_bool, offsetof(SuiView$Button, checked), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "setLabel", offsetof(SuiView$Button, setLabel));
	orc_metaField_method(&pNext, "setSrc", offsetof(SuiView$Button, setSrc));
	orc_metaField_method(&pNext, "setIn_group", offsetof(SuiView$Button, setIn_group));
	orc_metaField_method(&pNext, "setChecked", offsetof(SuiView$Button, setChecked));
}


// vtable init


Vtable_SuiView$Button* Vtable_SuiView$Button_init(Vtable_SuiView$Button* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Button;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Button_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Button";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Button_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Button_fini(SuiView$Button *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$Button*)self)->label);
	urgc_fini_field_class(self, (void**)&((SuiView$Button*)self)->src);

}

// init fields function


void SuiView$Button_init_fields(SuiView$Button *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$Button_fini;
	//fields
    {
	((SuiView$Button*)self)->labelColor = 0xffffffff;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$Button*)self)->label, Orc$str(&tmpReturn_1, "submit") );
	urgc_set_field_class(self, (void**)&((SuiView$Button*)self)->src, NULL);
	((SuiView$Button*)self)->in_group = false;
	((SuiView$Button*)self)->checked = false;
	urgc_set_field(self, (void**)&((SuiView$Button*)self)->onClick, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$Button$ctor;
	((SuiCore$Node*)self)->react = (void*)SuiView$Button$react;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$Button$onEvent;
	((SuiView$Button*)self)->setLabel = (void*)SuiView$Button$setLabel;
	((SuiView$Button*)self)->setSrc = (void*)SuiView$Button$setSrc;
	((SuiView$Button*)self)->setIn_group = (void*)SuiView$Button$setIn_group;
	((SuiView$Button*)self)->setChecked = (void*)SuiView$Button$setChecked;
}

// init function

void SuiView$Button_init(SuiView$Button *self, void *pOwner){
    Vtable_SuiView$Button_init(&_vtable_SuiView$Button);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Button;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Button_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Button * SuiView$Button_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Button *self = calloc(1, sizeof(SuiView$Button));
	
    SuiView$Button_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Button$ctor(SuiView$Button *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_1, "pointer") ) ;
}


void  SuiView$Button$react(SuiView$Button *  self){
	Orc$String$set(((SuiCore$ViewBase * )self)->cursor, "pointer") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->direction, "row") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->justifyContent, "center") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "center") ;
	((SuiCore$View * )self)->radius->setAll(((SuiCore$View * )self)->radius, 6) ;
	SuiCore$Inset$setAxis(&((SuiCore$View * )self)->padding, 5, 16) ;
	SuiCore$Node *  o = (SuiCore$Node * )self;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	if (self->src != NULL) {
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_1 = NULL;
		{
			SuiView$ImageView*  __scopeVar_48_3 = SuiView$mkImageView(&tmpReturn_1, o, 0) , *o = __scopeVar_48_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_48_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->setSrc(o, self->src) ;
		}
	}
	if (self->label != NULL) {
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
		{
			SuiView$TextView*  __scopeVar_55_3 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_55_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_55_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->color = self->labelColor;
			o->setText(o, self->label) ;
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiView$Button$onEvent(SuiView$Button *  self, SuiCore$Event *  ev){
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEnterEvent_init(NULL))) {
		((SuiCore$View * )self)->backgroundColor = 0xffff8888;
		self->labelColor = 0xff0000ff;
		((SuiCore$Node * )self)->react(self) ;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseLeaveEvent_init(NULL))) {
		((SuiCore$View * )self)->backgroundColor = 0xffff0000;
		self->labelColor = 0xffffffff;
		((SuiCore$Node * )self)->react(self) ;
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		if (me->isClickInBubble(me) ) {
			if (self->onClick) {
				(*(self->onClick))((void * )(self->onClick), me) ;
			}
		}
	}
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$ViewEvent_init(NULL))) {
		SuiCore$ViewEvent *  ve = (SuiCore$ViewEvent * )ev;
	}
}


void  SuiView$Button$setLabel(SuiView$Button *  self, Orc$String*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	if (v != self->label) {
		urgc_set_field_class(self, (void * )offsetof(SuiView$Button, label) , v) ;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiView$Button$setSrc(SuiView$Button *  self, Orc$String*  v){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(v);

	if (v != self->src) {
		urgc_set_field_class(self, (void * )offsetof(SuiView$Button, src) , v) ;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiView$Button$setIn_group(SuiView$Button *  self, bool  v){
	if (v != self->in_group) {
		self->in_group = v;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiView$Button$setChecked(SuiView$Button *  self, bool  v){
	if (v != self->checked) {
		self->checked = v;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}




//vtable instance
Vtable_SuiView$DrawButton _vtable_SuiView$DrawButton;

// init meta

void SuiView$DrawButton_initMeta(Vtable_SuiView$DrawButton *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "text", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$DrawButton, text), true, false, 1);
	orc_metaField_class(&pNext, "src", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$DrawButton, src), true, false, 1);
	orc_metaField_primitive(&pNext, "normalBg", OrcMetaType_int, offsetof(SuiView$DrawButton, normalBg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "hoverBg", OrcMetaType_int, offsetof(SuiView$DrawButton, hoverBg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "activeBg", OrcMetaType_int, offsetof(SuiView$DrawButton, activeBg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(SuiView$DrawButton, color), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "activeColor", OrcMetaType_int, offsetof(SuiView$DrawButton, activeColor), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "hoverColor", OrcMetaType_int, offsetof(SuiView$DrawButton, hoverColor), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "isActive", OrcMetaType_bool, offsetof(SuiView$DrawButton, isActive), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "typePrimary", offsetof(SuiView$DrawButton, typePrimary));
}


// vtable init


Vtable_SuiView$DrawButton* Vtable_SuiView$DrawButton_init(Vtable_SuiView$DrawButton* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$DrawButton;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$DrawButton_new;
    ((Vtable_Object*)pvt)->className = "SuiView$DrawButton";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$DrawButton_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$DrawButton_fini(SuiView$DrawButton *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$DrawButton*)self)->text);
	urgc_fini_field_class(self, (void**)&((SuiView$DrawButton*)self)->src);

}

// init fields function


void SuiView$DrawButton_init_fields(SuiView$DrawButton *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$DrawButton_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiView$DrawButton*)self)->text, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$DrawButton*)self)->src, NULL);
	((SuiView$DrawButton*)self)->normalBg = SuiDesigner$themeIns() ->button_bg;
	((SuiView$DrawButton*)self)->hoverBg = SuiDesigner$themeIns() ->button_bgHover;
	((SuiView$DrawButton*)self)->activeBg = SuiDesigner$themeIns() ->button_bgActive;
	((SuiView$DrawButton*)self)->color = SuiDesigner$themeIns() ->button_color;
	((SuiView$DrawButton*)self)->activeColor = SuiDesigner$themeIns() ->button_colorActive;
	((SuiView$DrawButton*)self)->hoverColor = SuiDesigner$themeIns() ->button_colorHover;
	((SuiView$DrawButton*)self)->isActive = false;
	urgc_set_field(self, (void**)&((SuiView$DrawButton*)self)->onClick, NULL);
    }
	((SuiView$DrawButton*)self)->typePrimary = (void*)SuiView$DrawButton$typePrimary;
	((Object*)self)->ctor = (void*)SuiView$DrawButton$ctor;
	((SuiCore$ViewBase*)self)->onHoverChanged = (void*)SuiView$DrawButton$onHoverChanged;
	((SuiCore$Node*)self)->react = (void*)SuiView$DrawButton$react;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$DrawButton$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$DrawButton$onEvent;
}

// init function

void SuiView$DrawButton_init(SuiView$DrawButton *self, void *pOwner){
    Vtable_SuiView$DrawButton_init(&_vtable_SuiView$DrawButton);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$DrawButton;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$DrawButton_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$DrawButton * SuiView$DrawButton_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$DrawButton *self = calloc(1, sizeof(SuiView$DrawButton));
	
    SuiView$DrawButton_init(self, pOwner);
    return self;
}


// class members
void  SuiView$DrawButton$typePrimary(SuiView$DrawButton *  self){
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	self->normalBg = t->button_primary_bg;
	self->hoverBg = t->button_primary_bgHover;
	self->color = t->button_primary_color;
	self->hoverColor = t->button_primary_color;
}


void  SuiView$DrawButton$ctor(SuiView$DrawButton *  self){
	SuiCore$Inset$setHor(&((SuiCore$View * )self)->padding, 8) ;
	((SuiCore$View * )self)->height = 30;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->justifyContent, "center") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "center") ;
	Orc$String$set(((SuiCore$ViewBase * )self)->cursor, "pointer") ;
}


void  SuiView$DrawButton$onHoverChanged(SuiView$DrawButton *  self){
	((SuiCore$Node * )self)->invalidReact(self) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$DrawButton$react(SuiView$DrawButton *  self){
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	if (self->src) {
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_1 = NULL;
		{
			SuiView$ImageView*  o = SuiView$mkImageView(&tmpReturn_1, self, 0) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_233_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 20;
			((SuiCore$View * )o)->height = 20;
			o->setSrc(o, self->src) ;
		}
	}
	if (self->text) {
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
		{
			SuiView$TextView*  o = SuiView$mkTextView(&tmpReturn_2, self, 0) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_240_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->setFont_size(o, t->button_fontSize) ;
			o->setText(o, self->text) ;
			o->color = self->isActive ? self->activeColor : ((SuiCore$ViewBase * )self)->hover ? self->hoverColor : self->color;
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiView$DrawButton$draw_self(SuiView$DrawButton *  self, SuiCore$Canvas *  canvas){
	SuiCore$Rect vr = ((SuiCore$View * )self)->getViewRect(self) ;
	int  x = 0;
	int  y = 0;
	int  w = vr.w;
	int  h = vr.h;
	int  cornerRadius = 5;
	int  r = 156;
	int  g = 156;
	int  b = 156;
	SuiCore$Canvas$fillColorByInt32(canvas, self->isActive ? self->activeBg : (((SuiCore$ViewBase * )self)->hover ? self->hoverBg : self->normalBg)) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$roundRect(canvas, x + 1, y + 1, w - 2, h - 2, cornerRadius - 1) ;
	SuiCore$Canvas$fill(canvas) ;
}


void  SuiView$DrawButton$onEvent(SuiView$DrawButton *  self, SuiCore$Event *  ev){
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		if (me->isClickInBubble(me) ) {
			if (self->onClick) {
				(*(self->onClick))((void * )(self->onClick), me) ;
			}
		}
	}
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$ViewEvent_init(NULL))) {
		SuiCore$ViewEvent *  ve = (SuiCore$ViewEvent * )ev;
	}
}




//vtable instance
Vtable_SuiView$MenuButton _vtable_SuiView$MenuButton;

// init meta

void SuiView$MenuButton_initMeta(Vtable_SuiView$MenuButton *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "text", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$MenuButton, text), true, false, 1);
	orc_metaField_primitive(&pNext, "normalBackgroundcolor", OrcMetaType_int, offsetof(SuiView$MenuButton, normalBackgroundcolor), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "hoverBackgroundcolor", OrcMetaType_int, offsetof(SuiView$MenuButton, hoverBackgroundcolor), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiView$MenuButton* Vtable_SuiView$MenuButton_init(Vtable_SuiView$MenuButton* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$MenuButton;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$MenuButton_new;
    ((Vtable_Object*)pvt)->className = "SuiView$MenuButton";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$MenuButton_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$MenuButton_fini(SuiView$MenuButton *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$MenuButton*)self)->text);

}

// init fields function


void SuiView$MenuButton_init_fields(SuiView$MenuButton *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$MenuButton_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiView$MenuButton*)self)->text, NULL);
	((SuiView$MenuButton*)self)->normalBackgroundcolor = 0x00999999;
	((SuiView$MenuButton*)self)->hoverBackgroundcolor = 0x33999999;
	urgc_set_field(self, (void**)&((SuiView$MenuButton*)self)->onClick, NULL);
	urgc_set_field(self, (void**)&((SuiView$MenuButton*)self)->onMouseMove, NULL);
    }
	((Object*)self)->ctor = (void*)SuiView$MenuButton$ctor;
	((Object*)self)->dtor = (void*)SuiView$MenuButton$dtor;
	((SuiCore$ViewBase*)self)->onHoverChanged = (void*)SuiView$MenuButton$onHoverChanged;
	((SuiCore$ViewBase*)self)->draw = (void*)SuiView$MenuButton$draw;
	((SuiCore$Node*)self)->react = (void*)SuiView$MenuButton$react;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$MenuButton$onEvent;
}

// init function

void SuiView$MenuButton_init(SuiView$MenuButton *self, void *pOwner){
    Vtable_SuiView$MenuButton_init(&_vtable_SuiView$MenuButton);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$MenuButton;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$MenuButton_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$MenuButton * SuiView$MenuButton_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$MenuButton *self = calloc(1, sizeof(SuiView$MenuButton));
	
    SuiView$MenuButton_init(self, pOwner);
    return self;
}


// class members
void  SuiView$MenuButton$ctor(SuiView$MenuButton *  self){
	SuiCore$Inset$setHor(&((SuiCore$View * )self)->padding, 8) ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->justifyContent, "center") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "center") ;
	Orc$String$set(((SuiCore$ViewBase * )self)->cursor, "pointer") ;
}


void  SuiView$MenuButton$dtor(SuiView$MenuButton *  self){
	printf("~MenuButton:%s. %p\n", self->text ? self->text->str : "(null text)", self) ;
}


void  SuiView$MenuButton$onHoverChanged(SuiView$MenuButton *  self){
	((SuiCore$Node * )self)->invalidReact(self) ;
	((SuiCore$ViewBase * )self)->invalidDraw(self) ;
}


void  SuiView$MenuButton$draw(SuiView$MenuButton *  self, void *  canvas){
	((SuiCore$View * )self)->backgroundColor = ((SuiCore$ViewBase * )self)->hover ? self->hoverBackgroundcolor : self->normalBackgroundcolor;
	SuiCore$View$draw(self, canvas) ;
}


void  SuiView$MenuButton$react(SuiView$MenuButton *  self){
	((SuiCore$Node * )self)->startInnerReact(self) ;
	if (self->text) {
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
		{
			SuiView$TextView*  o = SuiView$mkTextView(&tmpReturn_1, self, 0) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_336_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->setFont_size(o, 12) ;
			o->setText(o, self->text) ;
			o->color = ((SuiCore$ViewBase * )self)->hover ? 0xffffffff : 0x99ffffff;
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}


void  SuiView$MenuButton$onEvent(SuiView$MenuButton *  self, SuiCore$Event *  ev){
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )ev;
		if (me->isMouseMove) {
			if (self->onMouseMove) {
				(*(self->onMouseMove))((void * )(self->onMouseMove), me) ;
			}
		}
		if (me->isClickInBubble(me) ) {
			if (self->onClick) {
				(*(self->onClick))((void * )(self->onClick), me) ;
			}
		}
	}
	if (Orc_instanceof((Object*)ev, (Vtable_Object*)Vtable_SuiCore$ViewEvent_init(NULL))) {
		SuiCore$ViewEvent *  ve = (SuiCore$ViewEvent * )ev;
	}
}



SuiView$Button*  SuiView$mkButton(SuiView$Button **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$Button* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$Button_init(NULL)) ) ; 
}

SuiView$DrawButton*  SuiView$mkDrawButton(SuiView$DrawButton **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$DrawButton* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$DrawButton_init(NULL)) ) ; 
}

SuiView$MenuButton*  SuiView$mkMenuButton(SuiView$MenuButton **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$MenuButton* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$MenuButton_init(NULL)) ) ; 
}



