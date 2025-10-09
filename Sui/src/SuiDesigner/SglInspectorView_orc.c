
#include "SglInspectorView_orc.h" 

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
#include "./SglEditCtx_orc.h"
#include "./Inspector_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "./EventANodeChanged_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$SglInspectorView _vtable_SuiDesigner$SglInspectorView;

// init meta

void SuiDesigner$SglInspectorView_initMeta(Vtable_SuiDesigner$SglInspectorView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "inspector", ((Vtable_Object*)Vtable_SuiDesigner$Inspector_init(0)), offsetof(SuiDesigner$SglInspectorView, inspector), true, false, 1);
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_SuiDesigner$SglEditCtx_init(0)), offsetof(SuiDesigner$SglInspectorView, editCtx), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$SglInspectorView* Vtable_SuiDesigner$SglInspectorView_init(Vtable_SuiDesigner$SglInspectorView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SglInspectorView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SglInspectorView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SglInspectorView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SglInspectorView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SglInspectorView_fini(SuiDesigner$SglInspectorView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SglInspectorView*)self)->inspector);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SglInspectorView*)self)->editCtx);

}

// init fields function


void SuiDesigner$SglInspectorView_init_fields(SuiDesigner$SglInspectorView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SglInspectorView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Inspector*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglInspectorView*)self)->inspector, SuiDesigner$Inspector_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglInspectorView*)self)->editCtx, NULL);
    }
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiDesigner$SglInspectorView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$SglInspectorView$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiDesigner$SglInspectorView$onUnmounting;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$SglInspectorView$react;
}

// init function

void SuiDesigner$SglInspectorView_init(SuiDesigner$SglInspectorView *self, void *pOwner){
    Vtable_SuiDesigner$SglInspectorView_init(&_vtable_SuiDesigner$SglInspectorView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SglInspectorView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SglInspectorView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SglInspectorView * SuiDesigner$SglInspectorView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SglInspectorView *self = calloc(1, sizeof(SuiDesigner$SglInspectorView));
	
    SuiDesigner$SglInspectorView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SglInspectorView$onListenerEvent(SuiDesigner$SglInspectorView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiDesigner$EventSglSceneChanged_init(NULL))) {
		((SuiCore$Node * )self)->invalidReact(self) ;
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiDesigner$EventSglSelectedChanged_init(NULL))) {
		((SuiCore$Node * )self)->invalidReact(self) ;
	}
}


void  SuiDesigner$SglInspectorView$onMounted(SuiDesigner$SglInspectorView *  self){
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  SuiDesigner$SglInspectorView$onUnmounting(SuiDesigner$SglInspectorView *  self){
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  SuiDesigner$SglInspectorView$react(SuiDesigner$SglInspectorView *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, direction) , Orc$str(&tmpReturn_1, "column") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_2, "stretch") ) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiCore$Node *  o = self;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutLinearCell*  __scopeVar_86_8 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_86_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_86_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SglEditCtx*  ctx = (ctx=NULL,urgc_init_var_class((void**)&ctx, self->editCtx));
	if (ctx && ctx->state) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Node*  node = (node=NULL,urgc_init_var_class((void**)&node, (SuiCore$Node* )ctx->state->getFirstSelected(ctx->state) ));
		if (!(Orc_instanceof((Object*)node, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL)))) {
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
			{
				SuiView$TextView*  __scopeVar_96_16 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_96_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_96_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				o->setText(o, Orc$str(&tmpReturn_5, "no anode") ) ;
			}
		}
		else {
			URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  obj = (obj=NULL,urgc_init_var_class((void**)&obj, (Sgl$Obj3d* )node));
			URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_6 = NULL;
			{
				SuiView$ScrollArea*  __scopeVar_104_16 = SuiView$mkScrollArea(&tmpReturn_6, o, 0) , *o = __scopeVar_104_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_104_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinear, alignItems) , Orc$str(&tmpReturn_7, "stretch") ) ;
				o->useMinWidthConstraint = true;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_8 = NULL;
				{
					SuiLayout$LayoutLinearCell*  __scopeVar_112_20 = SuiLayout$layoutLinearCell(&tmpReturn_8, o, 0) , *o = __scopeVar_112_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_112_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					
				}
				if (obj) {
					urgc_set_field_class(self->inspector, (void * )offsetof(SuiDesigner$Inspector, obj) , obj) ;
					self->inspector->reactObject(self->inspector, o) ;
				}
				else {
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_9 = NULL;
					{
						SuiView$TextView*  __scopeVar_121_24 = SuiView$mkTextView(&tmpReturn_9, o, 0) , *o = __scopeVar_121_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_121_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
						o->setText(o, Orc$str(&tmpReturn_10, "no data") ) ;
					}
				}
			}
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



SuiDesigner$SglInspectorView*  SuiDesigner$mkSglInspectorView(SuiDesigner$SglInspectorView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$SglInspectorView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$SglInspectorView_init(NULL)) ) ; 
}



