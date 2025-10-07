
#include "HoroInspView_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include "../Json/cJSON.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../SuiDesigner/Insp_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Json/Json_orc.h"
#include "./HoroEditCtx_orc.h"
#include "./HoroEditor_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_46_15 HoroEditor$__Block_46_15;

typedef struct tagHoroEditor$__Closure_47_30 HoroEditor$__Closure_47_30;



struct tagHoroEditor$__Block_46_15 {
	HoroEditor$HoroInspView*  self ;
};





struct tagHoroEditor$__Closure_47_30 {
	void  (*invoke)(HoroEditor$__Closure_47_30 *  self, Object *  obj, OrcMetaField *  mf, Object *  inspValue);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_46_15*  __var___Block_46_15 ;
};





// static function declaration
static void  __finiBlock___Block_46_15(HoroEditor$__Block_46_15 *  self);
static void  __fn___Closure_47_30(HoroEditor$__Closure_47_30 *  self, Object *  obj, OrcMetaField *  mf, Object *  inspValue);
static void  __fini___Closure_47_30(HoroEditor$__Closure_47_30 *  self);
static HoroEditor$__Closure_47_30*  __make___Closure_47_30(HoroEditor$__Closure_47_30 **  __outRef__, HoroEditor$__Block_46_15 *  __var___Block_46_15);



//vtable instance
Vtable_HoroEditor$HoroInspView _vtable_HoroEditor$HoroInspView;

// init meta

void HoroEditor$HoroInspView_initMeta(Vtable_HoroEditor$HoroInspView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "insp", ((Vtable_Object*)Vtable_SuiDesigner$Insp_init(0)), offsetof(HoroEditor$HoroInspView, insp), true, false, 1);
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_HoroEditor$HoroEditCtx_init(0)), offsetof(HoroEditor$HoroInspView, editCtx), true, false, 1);
	orc_metaField_class(&pNext, "editor", ((Vtable_Object*)Vtable_HoroEditor$HoroEditor_init(0)), offsetof(HoroEditor$HoroInspView, editor), true, false, 1);

	
}


// vtable init


Vtable_HoroEditor$HoroInspView* Vtable_HoroEditor$HoroInspView_init(Vtable_HoroEditor$HoroInspView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroInspView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroInspView_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroInspView";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroInspView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroInspView_fini(HoroEditor$HoroInspView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void HoroEditor$HoroInspView_init_fields(HoroEditor$HoroInspView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroInspView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Insp*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroInspView*)self)->insp, SuiDesigner$Insp_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroInspView*)self)->editCtx, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroInspView*)self)->editor, NULL);
    }
	((Object*)self)->ctor = (void*)HoroEditor$HoroInspView$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)HoroEditor$HoroInspView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)HoroEditor$HoroInspView$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)HoroEditor$HoroInspView$onUnmounting;
	((SuiCore$Node*)self)->react = (void*)HoroEditor$HoroInspView$react;
}

// init function

void HoroEditor$HoroInspView_init(HoroEditor$HoroInspView *self, void *pOwner){
    Vtable_HoroEditor$HoroInspView_init(&_vtable_HoroEditor$HoroInspView);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroInspView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroInspView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroInspView * HoroEditor$HoroInspView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroInspView *self = calloc(1, sizeof(HoroEditor$HoroInspView));
	
    HoroEditor$HoroInspView_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroInspView$ctor(HoroEditor$HoroInspView *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_46_15*  __var___Block_46_15 = (__var___Block_46_15=NULL,urgc_init_var((void**)&__var___Block_46_15, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_46_15) , __finiBlock___Block_46_15) ));
	urgc_set_field_class(__var___Block_46_15, (void * )offsetof(HoroEditor$__Block_46_15, self) , self) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_47_30*  tmpReturn_1 = NULL;
	urgc_set_field(self->insp, (void * )offsetof(SuiDesigner$Insp, cbSetAttr) , __make___Closure_47_30(&tmpReturn_1, __var___Block_46_15) ) ;
}


void  HoroEditor$HoroInspView$onListenerEvent(HoroEditor$HoroInspView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_HoroEditor$EventHoroSceneChanged_init(NULL))) {
		((SuiCore$Node * )self)->invalidReact(self) ;
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_HoroEditor$EventHoroSelectedChanged_init(NULL))) {
		((SuiCore$Node * )self)->invalidReact(self) ;
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiDesigner$EventANodeAttrChanged_init(NULL))) {
		((SuiCore$Node * )self)->invalidReact(self) ;
	}
}


void  HoroEditor$HoroInspView$onMounted(HoroEditor$HoroInspView *  self){
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  HoroEditor$HoroInspView$onUnmounting(HoroEditor$HoroInspView *  self){
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  HoroEditor$HoroInspView$react(HoroEditor$HoroInspView *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_101_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_101_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_101_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		
	}
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroEditCtx*  ctx = (ctx=NULL,urgc_init_var_class((void**)&ctx, self->editCtx));
	if (ctx && ctx->state) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  anode = (anode=NULL,urgc_init_var_class((void**)&anode, (SuiDesigner$ANode* )ctx->state->getFirstSelected(ctx->state) ));
		if (anode) {
			SuiCore$Node *  node = anode->node;
			if (!(Orc_instanceof((Object*)node, (Vtable_Object*)Vtable_SuiCore$Node_init(NULL)))) {
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
				{
					SuiView$TextView*  __scopeVar_112_20 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_112_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_112_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
					o->setText(o, Orc$str(&tmpReturn_5, "no node??") ) ;
				}
			}
			else {
				URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, (Sgl$Obj3d* )node));
				URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_6 = NULL;
				{
					SuiView$ScrollArea*  __scopeVar_120_20 = SuiView$mkScrollArea(&tmpReturn_6, o, 0) , *o = __scopeVar_120_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_120_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_7, "stretch") ) ;
					o->useMinWidthConstraint = true;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_8 = NULL;
					{
						SuiLayout$LayoutLinearCell*  __scopeVar_129_24 = SuiLayout$layoutLinearCell(&tmpReturn_8, o, 0) , *o = __scopeVar_129_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_129_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						
					}
					if (obj) {
						self->insp->insp(self->insp, o, obj) ;
					}
					else {
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_9 = NULL;
						{
							SuiView$TextView*  __scopeVar_137_28 = SuiView$mkTextView(&tmpReturn_9, o, 0) , *o = __scopeVar_137_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_137_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
							o->setText(o, Orc$str(&tmpReturn_10, "no data") ) ;
						}
					}
				}
			}
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



static void  __finiBlock___Block_46_15(HoroEditor$__Block_46_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_46_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_47_30(HoroEditor$__Closure_47_30 *  self, Object *  obj, OrcMetaField *  mf, Object *  inspValue){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("设置属性:%s value:%s\n", mf->name, Orc$Object$toString(&tmpReturn_1, inspValue) ->str) ;
	SuiCore$Node *  sel = self->__var___Block_46_15->self->editCtx->state->getFirstSelected(self->__var___Block_46_15->self->editCtx->state) ;
	if (Orc_instanceof((Object*)sel, (Vtable_Object*)Vtable_SuiDesigner$ANode_init(NULL))) {
		SuiDesigner$ANode *  anode = (SuiDesigner$ANode * )sel;
		Json$Json *  tmpThis_1 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
		printf("给anode设置属性:%s\n", (tmpThis_1 = anode->toJson(&tmpReturn_3, anode) )->dump(&tmpReturn_2, tmpThis_1) ->str) ;
		anode->setAttrValueObject(anode, mf->name, inspValue) ;
	}
}

static void  __fini___Closure_47_30(HoroEditor$__Closure_47_30 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_47_30, __var___Block_46_15) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_47_30*  __make___Closure_47_30(HoroEditor$__Closure_47_30 **  __outRef__, HoroEditor$__Block_46_15 *  __var___Block_46_15){
	URGC_VAR_CLEANUP HoroEditor$__Closure_47_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_47_30) , __fini___Closure_47_30) ));
	self->invoke = __fn___Closure_47_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_47_30, __var___Block_46_15) , __var___Block_46_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

HoroEditor$HoroInspView*  HoroEditor$mkHoroInspView(HoroEditor$HoroInspView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (HoroEditor$HoroInspView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_HoroEditor$HoroInspView_init(NULL)) ) ; 
}



