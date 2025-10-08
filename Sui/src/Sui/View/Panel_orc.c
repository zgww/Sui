
#include "Panel_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../Orc/Path_orc.h"
#include "../../Orc/String_orc.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/ImageView_orc.h"
#include "../View/TextView_orc.h"
#include "../Core/View_orc.h"
#include "../View/ViewBuilder_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../SuiDesigner/Theme_orc.h"


// static struct 
typedef struct tagSuiView$__Block_53_16 SuiView$__Block_53_16;

typedef struct tagSuiView$__Block_146_16 SuiView$__Block_146_16;

typedef struct tagSuiView$__Closure_64_26 SuiView$__Closure_64_26;

typedef struct tagSuiView$__Closure_157_26 SuiView$__Closure_157_26;



struct tagSuiView$__Block_53_16 {
	SuiView$Panel*  self ;
};





struct tagSuiView$__Block_146_16 {
	SuiView$Panel2*  self ;
};





struct tagSuiView$__Closure_64_26 {
	void  (*invoke)(SuiView$__Closure_64_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiView$__Block_53_16*  __var___Block_53_16 ;
};





struct tagSuiView$__Closure_157_26 {
	void  (*invoke)(SuiView$__Closure_157_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiView$__Block_146_16*  __var___Block_146_16 ;
};





// static function declaration
static void  __finiBlock___Block_53_16(SuiView$__Block_53_16 *  self);
static void  __finiBlock___Block_146_16(SuiView$__Block_146_16 *  self);
static void  __fn___Closure_64_26(SuiView$__Closure_64_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_64_26(SuiView$__Closure_64_26 *  self);
static SuiView$__Closure_64_26*  __make___Closure_64_26(SuiView$__Closure_64_26 **  __outRef__, SuiView$__Block_53_16 *  __var___Block_53_16);
static void  __fn___Closure_157_26(SuiView$__Closure_157_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_157_26(SuiView$__Closure_157_26 *  self);
static SuiView$__Closure_157_26*  __make___Closure_157_26(SuiView$__Closure_157_26 **  __outRef__, SuiView$__Block_146_16 *  __var___Block_146_16);



//vtable instance
Vtable_SuiView$Panel _vtable_SuiView$Panel;

// init meta

void SuiView$Panel_initMeta(Vtable_SuiView$Panel *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "title", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$Panel, title), true, false, 1);
	orc_metaField_primitive(&pNext, "open", OrcMetaType_bool, offsetof(SuiView$Panel, open), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "body", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiView$Panel, body), true, false, 1);
	orc_metaField_primitive(&pNext, "titleColor", OrcMetaType_int, offsetof(SuiView$Panel, titleColor), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "titleFontSize", OrcMetaType_int, offsetof(SuiView$Panel, titleFontSize), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "onEvent_forHead", offsetof(SuiView$Panel, onEvent_forHead));
	orc_metaField_method(&pNext, "onClick_inHead", offsetof(SuiView$Panel, onClick_inHead));
	orc_metaField_method(&pNext, "setOpen", offsetof(SuiView$Panel, setOpen));
}


// vtable init


Vtable_SuiView$Panel* Vtable_SuiView$Panel_init(Vtable_SuiView$Panel* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Panel;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Panel_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Panel";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Panel_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Panel_fini(SuiView$Panel *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiView$Panel_init_fields(SuiView$Panel *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$Panel_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((SuiView$Panel*)self)->cbRenderTitle, NULL);
	urgc_set_field(self, (void**)&((SuiView$Panel*)self)->cbRenderContent, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$Panel*)self)->title, NULL);
	((SuiView$Panel*)self)->open = true;
	urgc_set_field_class(self, (void**)&((SuiView$Panel*)self)->body, NULL);
	((SuiView$Panel*)self)->titleColor = SuiDesigner$themeIns() ->panel_titleColor;
	((SuiView$Panel*)self)->titleFontSize = SuiDesigner$themeIns() ->panel_titleFontSize;
    }
	((SuiView$Panel*)self)->onEvent_forHead = (void*)SuiView$Panel$onEvent_forHead;
	((SuiView$Panel*)self)->onClick_inHead = (void*)SuiView$Panel$onClick_inHead;
	((SuiView$Panel*)self)->setOpen = (void*)SuiView$Panel$setOpen;
	((SuiCore$Node*)self)->react = (void*)SuiView$Panel$react;
}

// init function

void SuiView$Panel_init(SuiView$Panel *self, void *pOwner){
    Vtable_SuiView$Panel_init(&_vtable_SuiView$Panel);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Panel;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Panel_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Panel * SuiView$Panel_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Panel *self = calloc(1, sizeof(SuiView$Panel));
	
    SuiView$Panel_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Panel$onEvent_forHead(SuiView$Panel *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		self->onClick_inHead(self, (SuiCore$MouseEvent * )e) ;
	}
}


void  SuiView$Panel$onClick_inHead(SuiView$Panel *  self, SuiCore$MouseEvent *  e){
	if (e->isClickInBubble(e) ) {
		self->setOpen(self, !self->open) ;
	}
}


void  SuiView$Panel$setOpen(SuiView$Panel *  self, bool  v){
	if (v == self->open) {
		return ; 
	}
	self->open = v;
	((SuiCore$Node * )self)->invalidReact(self) ;
}


void  SuiView$Panel$react(SuiView$Panel *  self){
	URGC_VAR_CLEANUP SuiView$__Block_53_16*  __var___Block_53_16 = (__var___Block_53_16=NULL,urgc_init_var((void**)&__var___Block_53_16, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_53_16) , __finiBlock___Block_53_16) ));
	urgc_set_field_class(__var___Block_53_16, (void * )offsetof(SuiView$__Block_53_16, self) , self) ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->direction, "column") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "stretch") ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_63_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_63_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_63_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP SuiView$__Closure_64_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_64_26(&tmpReturn_2, __var___Block_53_16) ) ;
		((SuiCore$View * )o)->backgroundColor = 0x0d000000;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0x33000000) ;
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_3 = NULL;
		{
			SuiView$ImageView*  __scopeVar_71_12 = SuiView$mkImageView(&tmpReturn_3, o, 0) , *o = __scopeVar_71_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_71_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 16;
			((SuiCore$View * )o)->height = 16;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			o->setSrc(o, self->open ? Orc$Path_resolveFromExecutionDir(&tmpReturn_4, "../asset/icon/light-arrow-down.png")  : Orc$Path_resolveFromExecutionDir(&tmpReturn_5, "../asset/icon/light-arrow-right.png") ) ;
			((SuiCore$View * )o)->margin.right = 4;
		}
		if (self->title) {
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_6 = NULL;
			{
				SuiView$TextView*  __scopeVar_84_16 = SuiView$mkTextView(&tmpReturn_6, o, 0) , *o = __scopeVar_84_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_84_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->setText(o, self->title) ;
				o->color = self->titleColor;
				o->setFont_size(o, self->titleFontSize) ;
			}
		}
		else if (self->cbRenderTitle) {
			(*(self->cbRenderTitle))((void * )(self->cbRenderTitle), o) ;
		}
	}
	if (self->cbRenderContent) {
		if (self->open) {
			if (self->cbRenderContent) {
				(*(self->cbRenderContent))((void * )(self->cbRenderContent), o) ;
			}
		}
	}
	else {
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_7 = NULL;
		SuiLayout$LayoutLinear *  tmp = SuiLayout$layoutLinear(&tmpReturn_7, o, 0) ;
		Orc$String$set(tmp->direction, "column") ;
		((SuiCore$ViewBase * )tmp)->visible = self->open;
		urgc_set_field_class(self, (void * )offsetof(SuiView$Panel, body) , tmp) ;
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}




//vtable instance
Vtable_SuiView$Panel2 _vtable_SuiView$Panel2;

// init meta

void SuiView$Panel2_initMeta(Vtable_SuiView$Panel2 *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "title", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$Panel2, title), true, false, 1);
	orc_metaField_primitive(&pNext, "open", OrcMetaType_bool, offsetof(SuiView$Panel2, open), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "onEvent_forHead", offsetof(SuiView$Panel2, onEvent_forHead));
	orc_metaField_method(&pNext, "onClick_inHead", offsetof(SuiView$Panel2, onClick_inHead));
	orc_metaField_method(&pNext, "setOpen", offsetof(SuiView$Panel2, setOpen));
}


// vtable init


Vtable_SuiView$Panel2* Vtable_SuiView$Panel2_init(Vtable_SuiView$Panel2* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$Panel2;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$Panel2_new;
    ((Vtable_Object*)pvt)->className = "SuiView$Panel2";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$Panel2_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$Panel2_fini(SuiView$Panel2 *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiView$Panel2_init_fields(SuiView$Panel2 *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$Panel2_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((SuiView$Panel2*)self)->cbRenderTitle, NULL);
	urgc_set_field_class(self, (void**)&((SuiView$Panel2*)self)->title, NULL);
	((SuiView$Panel2*)self)->open = true;
    }
	((Object*)self)->ctor = (void*)SuiView$Panel2$ctor;
	((SuiView$Panel2*)self)->onEvent_forHead = (void*)SuiView$Panel2$onEvent_forHead;
	((SuiView$Panel2*)self)->onClick_inHead = (void*)SuiView$Panel2$onClick_inHead;
	((SuiView$Panel2*)self)->setOpen = (void*)SuiView$Panel2$setOpen;
	((SuiCore$Node*)self)->react = (void*)SuiView$Panel2$react;
}

// init function

void SuiView$Panel2_init(SuiView$Panel2 *self, void *pOwner){
    Vtable_SuiView$Panel2_init(&_vtable_SuiView$Panel2);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$Panel2;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$Panel2_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$Panel2 * SuiView$Panel2_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$Panel2 *self = calloc(1, sizeof(SuiView$Panel2));
	
    SuiView$Panel2_init(self, pOwner);
    return self;
}


// class members
void  SuiView$Panel2$ctor(SuiView$Panel2 *  self){
	((SuiCore$Node * )self)->hasInnerReact = true;
}


void  SuiView$Panel2$onEvent_forHead(SuiView$Panel2 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		self->onClick_inHead(self, (SuiCore$MouseEvent * )e) ;
	}
}


void  SuiView$Panel2$onClick_inHead(SuiView$Panel2 *  self, SuiCore$MouseEvent *  e){
	if (e->isClickInBubble(e) ) {
		self->setOpen(self, !self->open) ;
	}
}


void  SuiView$Panel2$setOpen(SuiView$Panel2 *  self, bool  v){
	if (v == self->open) {
		return ; 
	}
	self->open = v;
	((SuiCore$Node * )self)->invalidReact(self) ;
}


void  SuiView$Panel2$react(SuiView$Panel2 *  self){
	URGC_VAR_CLEANUP SuiView$__Block_146_16*  __var___Block_146_16 = (__var___Block_146_16=NULL,urgc_init_var((void**)&__var___Block_146_16, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_146_16) , __finiBlock___Block_146_16) ));
	urgc_set_field_class(__var___Block_146_16, (void * )offsetof(SuiView$__Block_146_16, self) , self) ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->direction, "column") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "stretch") ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_156_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_156_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_156_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP SuiView$__Closure_157_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_157_26(&tmpReturn_2, __var___Block_146_16) ) ;
		((SuiCore$View * )o)->backgroundColor = 0x0d000000;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0x33000000) ;
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_3 = NULL;
		{
			SuiView$ImageView*  __scopeVar_164_12 = SuiView$mkImageView(&tmpReturn_3, o, 0) , *o = __scopeVar_164_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_164_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 16;
			((SuiCore$View * )o)->height = 16;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			o->setSrc(o, self->open ? Orc$Path_resolveFromExecutionDir(&tmpReturn_4, "../asset/icon/light-arrow-down.png")  : Orc$Path_resolveFromExecutionDir(&tmpReturn_5, "../asset/icon/light-arrow-right.png") ) ;
			((SuiCore$View * )o)->margin.right = 4;
		}
		if (self->title) {
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_6 = NULL;
			{
				SuiView$TextView*  __scopeVar_177_16 = SuiView$mkTextView(&tmpReturn_6, o, 0) , *o = __scopeVar_177_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_177_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->setText(o, self->title) ;
			}
		}
		else if (self->cbRenderTitle) {
			(*(self->cbRenderTitle))((void * )(self->cbRenderTitle), o) ;
		}
	}
	if (self->open) {
		SuiCore$Node$placeKids((SuiCore$Node * )self, ((SuiCore$Node * )self)->outKids) ;
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



static void  __finiBlock___Block_53_16(SuiView$__Block_53_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_53_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_146_16(SuiView$__Block_146_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_146_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_64_26(SuiView$__Closure_64_26 *  self, SuiCore$Event *  e){
	self->__var___Block_53_16->self->onEvent_forHead(self->__var___Block_53_16->self, e) ;
}

static void  __fini___Closure_64_26(SuiView$__Closure_64_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_64_26, __var___Block_53_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_64_26*  __make___Closure_64_26(SuiView$__Closure_64_26 **  __outRef__, SuiView$__Block_53_16 *  __var___Block_53_16){
	URGC_VAR_CLEANUP SuiView$__Closure_64_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_64_26) , __fini___Closure_64_26) ));
	self->invoke = __fn___Closure_64_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_64_26, __var___Block_53_16) , __var___Block_53_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_157_26(SuiView$__Closure_157_26 *  self, SuiCore$Event *  e){
	self->__var___Block_146_16->self->onEvent_forHead(self->__var___Block_146_16->self, e) ;
}

static void  __fini___Closure_157_26(SuiView$__Closure_157_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_157_26, __var___Block_146_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_157_26*  __make___Closure_157_26(SuiView$__Closure_157_26 **  __outRef__, SuiView$__Block_146_16 *  __var___Block_146_16){
	URGC_VAR_CLEANUP SuiView$__Closure_157_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_157_26) , __fini___Closure_157_26) ));
	self->invoke = __fn___Closure_157_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_157_26, __var___Block_146_16) , __var___Block_146_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$Panel*  SuiView$mkPanel(SuiView$Panel **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$Panel* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$Panel_init(NULL)) ) ; 
}

SuiView$Panel2*  SuiView$mkPanel2(SuiView$Panel2 **  __outRef__, void *  parent, long long  key){
	void *  sp = key ? (void * )key : __builtin_return_address(0) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$Panel2* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$Panel2_init(NULL)) ) ; 
}



