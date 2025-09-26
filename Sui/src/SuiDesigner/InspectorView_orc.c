
#include "InspectorView_orc.h" 

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
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./SceneView_orc.h"
#include "./SceneHierView_orc.h"
#include "./ANode_orc.h"
#include "./EditCtx_orc.h"
#include "./Inspector_orc.h"
#include "./EventANodeChanged_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$InspectorView _vtable_SuiDesigner$InspectorView;

// init meta

void SuiDesigner$InspectorView_initMeta(Vtable_SuiDesigner$InspectorView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "inspector", ((Vtable_Object*)Vtable_SuiDesigner$Inspector_init(0)), offsetof(SuiDesigner$InspectorView, inspector), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$InspectorView* Vtable_SuiDesigner$InspectorView_init(Vtable_SuiDesigner$InspectorView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspectorView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspectorView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspectorView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspectorView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspectorView_fini(SuiDesigner$InspectorView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspectorView_init_fields(SuiDesigner$InspectorView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspectorView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Inspector*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspectorView*)self)->inspector, SuiDesigner$Inspector_new(&tmpNewOwner_1) );
    }
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiDesigner$InspectorView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$InspectorView$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiDesigner$InspectorView$onUnmounting;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$InspectorView$react;
}

// init function

void SuiDesigner$InspectorView_init(SuiDesigner$InspectorView *self, void *pOwner){
    Vtable_SuiDesigner$InspectorView_init(&_vtable_SuiDesigner$InspectorView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspectorView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspectorView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspectorView * SuiDesigner$InspectorView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspectorView *self = calloc(1, sizeof(SuiDesigner$InspectorView));
	
    SuiDesigner$InspectorView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspectorView$onListenerEvent(SuiDesigner$InspectorView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiDesigner$EditEventSelectedChanged_init(NULL))) {
		((SuiCore$Node * )self)->invalidReact(self) ;
	}
	else if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiDesigner$EventANodeAttrChanged_init(NULL))) {
		SuiDesigner$EventANodeAttrChanged *  e = (SuiDesigner$EventANodeAttrChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiDesigner$InspectorView$onMounted(SuiDesigner$InspectorView *  self){
	SuiDesigner$EditCtx *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
	((SuiCore$Emitter * )(tmpThis_1 = SuiDesigner$EditCtx_ins(&tmpReturn_1) ))->addListenerOnce(tmpThis_1, self) ;
	SuiCore$Emitter *  tmpThis_2 = NULL;
	(tmpThis_2 = SuiCore$useEbus() )->addListener(tmpThis_2, self) ;
}


void  SuiDesigner$InspectorView$onUnmounting(SuiDesigner$InspectorView *  self){
	SuiDesigner$EditCtx *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
	((SuiCore$Emitter * )(tmpThis_1 = SuiDesigner$EditCtx_ins(&tmpReturn_1) ))->removeListener(tmpThis_1, self) ;
	SuiCore$Emitter *  tmpThis_2 = NULL;
	(tmpThis_2 = SuiCore$useEbus() )->removeListener(tmpThis_2, self) ;
}


void  SuiDesigner$InspectorView$react(SuiDesigner$InspectorView *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_78_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_78_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_78_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
	URGC_VAR_CLEANUP_CLASS Object*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, (Object* )ctx->state->getFirstSelected(ctx->state) ));
	if (!(Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_SuiDesigner$ANode_init(NULL)))) {
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
		{
			SuiView$TextView*  __scopeVar_86_12 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_86_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_86_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			o->setText(o, Orc$str(&tmpReturn_5, "no anode") ) ;
		}
	}
	else {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  anode = (anode=NULL,urgc_init_var_class((void**)&anode, (SuiDesigner$ANode* )ctx->state->getFirstSelected(ctx->state) ));
		URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_6 = NULL;
		{
			SuiView$ScrollArea*  __scopeVar_94_12 = SuiView$mkScrollArea(&tmpReturn_6, o, 0) , *o = __scopeVar_94_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_94_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_7, "stretch") ) ;
			o->useMinWidthConstraint = true;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_8 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_102_16 = SuiLayout$layoutLinearCell(&tmpReturn_8, o, 0) , *o = __scopeVar_102_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_102_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				
			}
			if (anode && anode->node) {
				self->inspector->inspect(self->inspector, o, anode->node) ;
			}
			else {
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_9 = NULL;
				{
					SuiView$TextView*  __scopeVar_112_20 = SuiView$mkTextView(&tmpReturn_9, o, 0) , *o = __scopeVar_112_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_112_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					o->setText(o, Orc$str(&tmpReturn_10, "no data") ) ;
				}
			}
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



SuiDesigner$InspectorView*  SuiDesigner$mkInspectorView(SuiDesigner$InspectorView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$InspectorView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$InspectorView_init(NULL)) ) ; 
}



