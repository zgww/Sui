
#include "Horo2dSceneView_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Mat2d_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../SuiDesigner/Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Json/Json_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/RegisterNodes_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "../SuiDesigner/UiAction_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/Gizmo_orc.h"
#include "../SuiDesigner/EditCtx_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "./ImageChessBg_orc.h"
#include "./SceneTransform_orc.h"
#include "./HoroEditor_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_86_15 HoroEditor$__Block_86_15;

typedef struct tagHoroEditor$__Block_205_37 HoroEditor$__Block_205_37;

typedef struct tagHoroEditor$__Block_298_29 HoroEditor$__Block_298_29;

typedef struct tagHoroEditor$__Block_338_23 HoroEditor$__Block_338_23;

typedef struct tagHoroEditor$__Block_344_58 HoroEditor$__Block_344_58;

typedef struct tagHoroEditor$__Closure_89_27 HoroEditor$__Closure_89_27;

typedef struct tagHoroEditor$__Closure_onActive_208 HoroEditor$__Closure_onActive_208;

typedef struct tagHoroEditor$__Closure_305_30 HoroEditor$__Closure_305_30;

typedef struct tagHoroEditor$__Closure_324_32 HoroEditor$__Closure_324_32;

typedef struct tagHoroEditor$__Closure_363_38 HoroEditor$__Closure_363_38;



struct tagHoroEditor$__Block_86_15 {
	HoroEditor$Horo2dSceneView*  self ;
};





struct tagHoroEditor$__Block_205_37 {
	HoroEditor$Horo2dSceneView*  self ;
};





struct tagHoroEditor$__Block_298_29 {
	HoroEditor$Horo2dSceneView*  self ;
};





struct tagHoroEditor$__Block_338_23 {
	SuiDesigner$ANode *  sel ;
};





struct tagHoroEditor$__Block_344_58 {
	SuiCore$View *  selView ;
};





struct tagHoroEditor$__Closure_89_27 {
	void  (*invoke)(HoroEditor$__Closure_89_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_86_15*  __var___Block_86_15 ;
};





struct tagHoroEditor$__Closure_onActive_208 {
	void  (*invoke)(HoroEditor$__Closure_onActive_208 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_205_37*  __var___Block_205_37 ;
};





struct tagHoroEditor$__Closure_305_30 {
	bool  (*invoke)(HoroEditor$__Closure_305_30 *  self);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_298_29*  __var___Block_298_29 ;
};





struct tagHoroEditor$__Closure_324_32 {
	void  (*invoke)(HoroEditor$__Closure_324_32 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_363_38 {
	void  (*invoke)(HoroEditor$__Closure_363_38 *  self, SuiCore$Rect newr);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_338_23*  __var___Block_338_23 ;
	HoroEditor$__Block_344_58*  __var___Block_344_58 ;
};





// static function declaration
static void  __finiBlock___Block_86_15(HoroEditor$__Block_86_15 *  self);
static void  __finiBlock___Block_205_37(HoroEditor$__Block_205_37 *  self);
static void  __finiBlock___Block_298_29(HoroEditor$__Block_298_29 *  self);
static void  __finiBlock___Block_338_23(HoroEditor$__Block_338_23 *  self);
static void  __finiBlock___Block_344_58(HoroEditor$__Block_344_58 *  self);
static void  __fn___Closure_89_27(HoroEditor$__Closure_89_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_89_27(HoroEditor$__Closure_89_27 *  self);
static HoroEditor$__Closure_89_27*  __make___Closure_89_27(HoroEditor$__Closure_89_27 **  __outRef__, HoroEditor$__Block_86_15 *  __var___Block_86_15);
static void  __fn___Closure_onActive_208(HoroEditor$__Closure_onActive_208 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_208(HoroEditor$__Closure_onActive_208 *  self);
static HoroEditor$__Closure_onActive_208*  __make___Closure_onActive_208(HoroEditor$__Closure_onActive_208 **  __outRef__, HoroEditor$__Block_205_37 *  __var___Block_205_37);
static bool  __fn___Closure_305_30(HoroEditor$__Closure_305_30 *  self);
static void  __fini___Closure_305_30(HoroEditor$__Closure_305_30 *  self);
static HoroEditor$__Closure_305_30*  __make___Closure_305_30(HoroEditor$__Closure_305_30 **  __outRef__, HoroEditor$__Block_298_29 *  __var___Block_298_29);
static void  __fn___Closure_324_32(HoroEditor$__Closure_324_32 *  self, SuiView$Drag *  d);
static void  __fini___Closure_324_32(HoroEditor$__Closure_324_32 *  self);
static HoroEditor$__Closure_324_32*  __make___Closure_324_32(HoroEditor$__Closure_324_32 **  __outRef__);
static void  __fn___Closure_363_38(HoroEditor$__Closure_363_38 *  self, SuiCore$Rect newr);
static void  __fini___Closure_363_38(HoroEditor$__Closure_363_38 *  self);
static HoroEditor$__Closure_363_38*  __make___Closure_363_38(HoroEditor$__Closure_363_38 **  __outRef__, HoroEditor$__Block_338_23 *  __var___Block_338_23, HoroEditor$__Block_344_58 *  __var___Block_344_58);



//vtable instance
Vtable_HoroEditor$Horo2dSceneView _vtable_HoroEditor$Horo2dSceneView;

// init meta

void HoroEditor$Horo2dSceneView_initMeta(Vtable_HoroEditor$Horo2dSceneView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "chessBg", ((Vtable_Object*)Vtable_HoroEditor$ImageChessBg_init(0)), offsetof(HoroEditor$Horo2dSceneView, chessBg), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(HoroEditor$Horo2dSceneView, drag), true, false, 1);
	orc_metaField_class(&pNext, "sceneTransform", ((Vtable_Object*)Vtable_HoroEditor$SceneTransform_init(0)), offsetof(HoroEditor$Horo2dSceneView, sceneTransform), true, false, 1);
	orc_metaField_class(&pNext, "degree", ((Vtable_Object*)Vtable_SuiDesigner$DrawDegree_init(0)), offsetof(HoroEditor$Horo2dSceneView, degree), true, false, 1);
	orc_metaField_class(&pNext, "editor", ((Vtable_Object*)Vtable_HoroEditor$HoroEditor_init(0)), offsetof(HoroEditor$Horo2dSceneView, editor), true, false, 1);
	orc_metaField_class(&pNext, "root", ((Vtable_Object*)Vtable_SuiDesigner$ANode_init(0)), offsetof(HoroEditor$Horo2dSceneView, root), true, false, 1);
	orc_metaField_class(&pNext, "rootNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(HoroEditor$Horo2dSceneView, rootNode), true, false, 1);
	orc_metaField_class(&pNext, "gizmoRoot", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(HoroEditor$Horo2dSceneView, gizmoRoot), true, false, 1);
	orc_metaField_class(&pNext, "gizmoDrag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(HoroEditor$Horo2dSceneView, gizmoDrag), true, false, 1);
	orc_metaField_primitive(&pNext, "_reactGizmosDirty", OrcMetaType_bool, offsetof(HoroEditor$Horo2dSceneView, _reactGizmosDirty), 0, 0, 0, 0);//bool
	orc_metaField_struct(&pNext, "_sceneWorldMat", SuiCore$Mat2d_getOrInitMetaStruct(), offsetof(HoroEditor$Horo2dSceneView, _sceneWorldMat), false, false, 0);

	orc_metaField_method(&pNext, "onUnmouting", offsetof(HoroEditor$Horo2dSceneView, onUnmouting));
	orc_metaField_method(&pNext, "onLeftClickInCapture", offsetof(HoroEditor$Horo2dSceneView, onLeftClickInCapture));
	orc_metaField_method(&pNext, "_routeRightMenu", offsetof(HoroEditor$Horo2dSceneView, _routeRightMenu));
	orc_metaField_method(&pNext, "onRightClick", offsetof(HoroEditor$Horo2dSceneView, onRightClick));
	orc_metaField_method(&pNext, "removeRootNode", offsetof(HoroEditor$Horo2dSceneView, removeRootNode));
	orc_metaField_method(&pNext, "triggerReactGizmos", offsetof(HoroEditor$Horo2dSceneView, triggerReactGizmos));
	orc_metaField_method(&pNext, "reactGizmos", offsetof(HoroEditor$Horo2dSceneView, reactGizmos));
	orc_metaField_method(&pNext, "drawRect_forANode", offsetof(HoroEditor$Horo2dSceneView, drawRect_forANode));
}


// vtable init


Vtable_HoroEditor$Horo2dSceneView* Vtable_HoroEditor$Horo2dSceneView_init(Vtable_HoroEditor$Horo2dSceneView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$Horo2dSceneView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$Horo2dSceneView_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$Horo2dSceneView";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$Horo2dSceneView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$Horo2dSceneView_fini(HoroEditor$Horo2dSceneView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->chessBg);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->drag);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->sceneTransform);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->degree);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->editor);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->root);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->rootNode);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->gizmoRoot);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->gizmoDrag);

}

// init fields function


void HoroEditor$Horo2dSceneView_init_fields(HoroEditor$Horo2dSceneView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)HoroEditor$Horo2dSceneView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS HoroEditor$ImageChessBg*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->chessBg, HoroEditor$ImageChessBg_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS HoroEditor$SceneTransform*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->sceneTransform, HoroEditor$SceneTransform_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegree*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->degree, SuiDesigner$DrawDegree_new(&tmpNewOwner_4) );
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->editor, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->root, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->rootNode, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->gizmoRoot, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo2dSceneView*)self)->gizmoDrag, SuiView$Drag_new(&tmpNewOwner_5) );
	((HoroEditor$Horo2dSceneView*)self)->_reactGizmosDirty = false;
	((HoroEditor$Horo2dSceneView*)self)->_sceneWorldMat = SuiCore$mkMat2d() ;
    }
	((Object*)self)->ctor = (void*)HoroEditor$Horo2dSceneView$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)HoroEditor$Horo2dSceneView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)HoroEditor$Horo2dSceneView$onMounted;
	((HoroEditor$Horo2dSceneView*)self)->onUnmouting = (void*)HoroEditor$Horo2dSceneView$onUnmouting;
	((SuiCore$Emitter*)self)->onEvent = (void*)HoroEditor$Horo2dSceneView$onEvent;
	((HoroEditor$Horo2dSceneView*)self)->onLeftClickInCapture = (void*)HoroEditor$Horo2dSceneView$onLeftClickInCapture;
	((HoroEditor$Horo2dSceneView*)self)->_routeRightMenu = (void*)HoroEditor$Horo2dSceneView$_routeRightMenu;
	((HoroEditor$Horo2dSceneView*)self)->onRightClick = (void*)HoroEditor$Horo2dSceneView$onRightClick;
	((HoroEditor$Horo2dSceneView*)self)->removeRootNode = (void*)HoroEditor$Horo2dSceneView$removeRootNode;
	((SuiCore$Node*)self)->react = (void*)HoroEditor$Horo2dSceneView$react;
	((HoroEditor$Horo2dSceneView*)self)->triggerReactGizmos = (void*)HoroEditor$Horo2dSceneView$triggerReactGizmos;
	((HoroEditor$Horo2dSceneView*)self)->reactGizmos = (void*)HoroEditor$Horo2dSceneView$reactGizmos;
	((SuiCore$ViewBase*)self)->draw_children = (void*)HoroEditor$Horo2dSceneView$draw_children;
	((SuiCore$ViewBase*)self)->draw_self = (void*)HoroEditor$Horo2dSceneView$draw_self;
	((SuiCore$View*)self)->drawSelfBorder = (void*)HoroEditor$Horo2dSceneView$drawSelfBorder;
	((HoroEditor$Horo2dSceneView*)self)->drawRect_forANode = (void*)HoroEditor$Horo2dSceneView$drawRect_forANode;
}

// init function

void HoroEditor$Horo2dSceneView_init(HoroEditor$Horo2dSceneView *self, void *pOwner){
    Vtable_HoroEditor$Horo2dSceneView_init(&_vtable_HoroEditor$Horo2dSceneView);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$Horo2dSceneView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$Horo2dSceneView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$Horo2dSceneView * HoroEditor$Horo2dSceneView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$Horo2dSceneView *self = calloc(1, sizeof(HoroEditor$Horo2dSceneView));
	
    HoroEditor$Horo2dSceneView_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$Horo2dSceneView$ctor(HoroEditor$Horo2dSceneView *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_86_15*  __var___Block_86_15 = (__var___Block_86_15=NULL,urgc_init_var((void**)&__var___Block_86_15, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_86_15) , __finiBlock___Block_86_15) ));
	urgc_set_field_class(__var___Block_86_15, (void * )offsetof(HoroEditor$__Block_86_15, self) , self) ;
	((SuiCore$View * )self)->needClip = true;
	self->sceneTransform->translate(self->sceneTransform, 0, 0, 0) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_89_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_89_27(&tmpReturn_1, __var___Block_86_15) ) ;
}


void  HoroEditor$Horo2dSceneView$onListenerEvent(HoroEditor$Horo2dSceneView *  self, SuiCore$Event *  event){
	if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeAttrChanged_init(NULL))) {
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeChanged_init(NULL))) {
		SuiDesigner$EventANodeChanged *  e = (SuiDesigner$EventANodeChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventFileItemChanged_init(NULL))) {
		SuiDesigner$EventFileItemChanged *  e = (SuiDesigner$EventFileItemChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  HoroEditor$Horo2dSceneView$onMounted(HoroEditor$Horo2dSceneView *  self){
	SuiCore$Node$onMounted(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  HoroEditor$Horo2dSceneView$onUnmouting(HoroEditor$Horo2dSceneView *  self){
	SuiCore$Node$onUnmounting(self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  HoroEditor$Horo2dSceneView$onEvent(HoroEditor$Horo2dSceneView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$WheelEvent_init(NULL))) {
		SuiCore$WheelEvent *  we = (SuiCore$WheelEvent * )e;
		if (((SuiCore$ViewEvent * )we)->isCapture) {
			self->sceneTransform->performScaleByWheelEventAndSceneView(self->sceneTransform, we, self) ;
		}
		return ; 
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		self->drag->onMouseDown_byPrefer(self->drag, me, 3, true, false) ;
		if (((SuiCore$ViewEvent * )me)->isBubble(me)  && me->button == 3) {
			if (me->isMouseDown) {
				printf("mouse down scene\n") ;
			}
			if (me->isMouseUp) {
				printf("mouse up scene\n") ;
			}
		}
		if (me->isMouseDown && ((SuiCore$ViewEvent * )me)->isCapture) {
			((SuiCore$Event * )me)->stopPropagation(me) ;
		}
		if (me->isClickInBubble(me)  && me->button == 3) {
			self->onRightClick(self, me) ;
		}
		if (me->button == 1 && ((SuiCore$ViewEvent * )me)->isCapture && me->isClick(me) ) {
			self->onLeftClickInCapture(self, me) ;
		}
	}
}


void  HoroEditor$Horo2dSceneView$onLeftClickInCapture(HoroEditor$Horo2dSceneView *  self, SuiCore$MouseEvent *  me){
	if (self->root && Orc_instanceof((Object*)self->root->node, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  rootView = (SuiCore$ViewBase * )self->root->node;
		SuiCore$ViewBase *  found = rootView->hitTestChildren(rootView, me->clientX, me->clientY) ;
		if (found) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  vnode = self->editor->editCtx->findANodeByNode((vnode = NULL,&vnode), self->editor->editCtx, found) ;
			if (vnode) {
				((SuiCore$Event * )me)->stopPropagation(me) ;
				self->editor->editCtx->state->setAncestorsOpen(self->editor->editCtx->state, vnode) ;
				self->editor->editCtx->state->setSelected(self->editor->editCtx->state, vnode) ;
			}
		}
		else {
			SuiCore$Vec2 viewPos = ((SuiCore$ViewBase * )self)->worldToLocal(self, me->clientX, me->clientY) ;
			SuiCore$Mat2d invMat = SuiCore$Mat2d$inverseNew(&self->sceneTransform->mat) ;
			SuiCore$Vec3 scenePos = SuiCore$Mat2d$transformPoint(&invMat, viewPos.x, viewPos.y, 0) ;
			printf("\n\n========================================left click. viewPos:%f,%f, scenePos:%f,%f\n\n", viewPos.x, viewPos.y, scenePos.x, scenePos.y) ;
		}
	}
}


void  HoroEditor$Horo2dSceneView$_routeRightMenu(HoroEditor$Horo2dSceneView *  self, SuiView$MenuNativeItem *  item){
	if (item->cmd) {
		if (Orc$String$equals(item->cmd, "ResetSceneTransform") ) {
			self->sceneTransform->identity(self->sceneTransform) ;
			return ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = (s=NULL,urgc_init_var_class((void**)&s, Orc$String$addString(Orc$str(&tmpReturn_1, "选中菜单") , item->cmd) ));
	SuiDialog$MessageDialog_alert(s->str, "tip") ;
}


void  HoroEditor$Horo2dSceneView$onRightClick(HoroEditor$Horo2dSceneView *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP HoroEditor$__Block_205_37*  __var___Block_205_37 = (__var___Block_205_37=NULL,urgc_init_var((void**)&__var___Block_205_37, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_205_37) , __finiBlock___Block_205_37) ));
	urgc_set_field_class(__var___Block_205_37, (void * )offsetof(HoroEditor$__Block_205_37, self) , self) ;
	printf("on right click scene\n") ;
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
	{
		SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
		
	
		URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
		URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_208*  tmpReturn_2 = NULL;
		(urgc_set_var(&onActive, __make___Closure_onActive_208(&tmpReturn_2, __var___Block_205_37) ) );
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		{
			SuiView$MenuNativeItem*  __scopeVar_217_12 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "重置场景坐标") , onActive) , *o = __scopeVar_217_12;
			
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "ResetSceneTransform") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
		{
			SuiView$MenuNativeItem*  __scopeVar_218_12 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "hi") , onActive) , *o = __scopeVar_218_12;
			
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "Hi") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
		n->create(n, o) ;
		n->showAtMouse(n) ;
	}
}


void  HoroEditor$Horo2dSceneView$removeRootNode(HoroEditor$Horo2dSceneView *  self){
	if (self->rootNode) {
		self->rootNode->removeSelf(self->rootNode) ;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$Horo2dSceneView, rootNode) , NULL) ;
	}
}


void  HoroEditor$Horo2dSceneView$react(HoroEditor$Horo2dSceneView *  self){
	SuiCore$Node *  o = self;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  root = (root=NULL,urgc_init_var_class((void**)&root, self->root));
	if (root && root->node) {
		SuiCore$Node$placeKid((SuiCore$Node * )self, root->node) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS SuiCore$View*  v = SuiView$mkView((v = NULL,&v), o, 0) ;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$Horo2dSceneView, gizmoRoot) , v) ;
		Orc$String$set(((SuiCore$ViewBase * )v)->hitTestType, "onlychildren") ;
		URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpReturn_1 = NULL;
		SuiCore$get_unusedMapForReact(&tmpReturn_1, v) ;
		URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpReturn_2 = NULL;
		SuiCore$get_mapForReact(&tmpReturn_2, v) ;
		v->backgroundColor = 0x0000ff00;
		SuiCore$Node$endReact((SuiCore$Node * )v) ;
	}
	((SuiCore$View * )self)->backgroundColor = 0xcc000000;
	((SuiCore$Node * )self)->endInnerReact(self) ;
	self->reactGizmos(self) ;
}


void  HoroEditor$Horo2dSceneView$triggerReactGizmos(HoroEditor$Horo2dSceneView *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_298_29*  __var___Block_298_29 = (__var___Block_298_29=NULL,urgc_init_var((void**)&__var___Block_298_29, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_298_29) , __finiBlock___Block_298_29) ));
	urgc_set_field_class(__var___Block_298_29, (void * )offsetof(HoroEditor$__Block_298_29, self) , self) ;
	if (self->_reactGizmosDirty) {
		return ; 
	}
	self->_reactGizmosDirty = true;
	URGC_VAR_CLEANUP HoroEditor$__Closure_305_30*  tmpReturn_1 = NULL;
	SuiCore$requestAnimationFrame(__make___Closure_305_30(&tmpReturn_1, __var___Block_298_29) ) ;
}


void  HoroEditor$Horo2dSceneView$reactGizmos(HoroEditor$Horo2dSceneView *  self){
	if (!self->editor) {
		return ; 
	}
	SuiDesigner$ANode *  sel = self->editor->editCtx->state->getFirstSelected(self->editor->editCtx->state) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_324_32*  tmpReturn_1 = NULL;
	urgc_set_field(self->gizmoDrag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_324_32(&tmpReturn_1) ) ;
	SuiCore$View *  inner = NULL;
	Object *  prevfirst = NULL;
	int  prevSize = self->gizmoRoot->_unusedMapForReact->size(self->gizmoRoot->_unusedMapForReact) ;
	if (self->gizmoRoot->_unusedMapForReact->size(self->gizmoRoot->_unusedMapForReact)  > 0) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  keys = self->gizmoRoot->_unusedMapForReact->keys((keys = NULL,&keys), self->gizmoRoot->_unusedMapForReact) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, keys->get(keys, 0) ));
		prevfirst = self->gizmoRoot->_unusedMapForReact->get(self->gizmoRoot->_unusedMapForReact, key->str) ;
	}
	{
		SuiCore$Node*  o = self->gizmoRoot;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_338_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP HoroEditor$__Block_338_23*  __var___Block_338_23 = (__var___Block_338_23=NULL,urgc_init_var((void**)&__var___Block_338_23, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_338_23) , __finiBlock___Block_338_23) ));
		__var___Block_338_23->sel = self->editor->editCtx->state->getFirstSelected(self->editor->editCtx->state) ;
		if (__var___Block_338_23->sel && __var___Block_338_23->sel->node && Orc_instanceof((Object*)__var___Block_338_23->sel->node, (Vtable_Object*)Vtable_SuiCore$View_init(NULL))) {
			URGC_VAR_CLEANUP HoroEditor$__Block_344_58*  __var___Block_344_58 = (__var___Block_344_58=NULL,urgc_init_var((void**)&__var___Block_344_58, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_344_58) , __finiBlock___Block_344_58) ));
			__var___Block_344_58->selView = (SuiCore$View * )__var___Block_338_23->sel->node;
			SuiCore$Frame *  f = &((SuiCore$ViewBase * )__var___Block_344_58->selView)->frame;
			SuiCore$Mat2d invMat = SuiCore$Mat2d$inverseNew(&self->_sceneWorldMat) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner$GizmoRectView*  tmpReturn_2 = NULL;
			{
				SuiDesigner$GizmoRectView*  __scopeVar_359_16 = SuiDesigner$mkGizmoRectView(&tmpReturn_2, o, 0) , *o = __scopeVar_359_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_359_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				SuiCore$Vec3 lt = SuiCore$Mat2d$localToLocal(&((SuiCore$ViewBase * )__var___Block_344_58->selView)->_world_transform, &invMat, 0, 0, 0) ;
				SuiCore$Vec3 rb = SuiCore$Mat2d$localToLocal(&((SuiCore$ViewBase * )__var___Block_344_58->selView)->_world_transform, &invMat, f->width, f->height, 0) ;
				SuiCore$Rect$set_ltrb(&o->targetRect, lt.x, lt.y, rb.x, rb.y) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_363_38*  tmpReturn_3 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiDesigner$GizmoRectView, onRectChanged) , __make___Closure_363_38(&tmpReturn_3, __var___Block_338_23, __var___Block_344_58) ) ;
			}
		}
	}
	Object *  first = NULL;
	if (self->gizmoRoot->_unusedMapForReact->size(self->gizmoRoot->_unusedMapForReact)  > 0) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  keys = self->gizmoRoot->_unusedMapForReact->keys((keys = NULL,&keys), self->gizmoRoot->_unusedMapForReact) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, keys->get(keys, 0) ));
		first = self->gizmoRoot->_unusedMapForReact->get(self->gizmoRoot->_unusedMapForReact, key->str) ;
	}
}


void  HoroEditor$Horo2dSceneView$draw_children(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas){
	SuiCore$Canvas$save(canvas) ;
	SuiCore$Canvas$transform(canvas, self->sceneTransform->mat) ;
	SuiCore$Canvas$currentTransform(canvas, &self->_sceneWorldMat) ;
	SuiCore$ViewBase$draw_children(self, canvas) ;
	SuiCore$Canvas$restore(canvas) ;
}


void  HoroEditor$Horo2dSceneView$draw_self(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas){
	SuiCore$Image *  bg = self->chessBg->gocChessBgImage(self->chessBg, canvas) ;
	SuiCore$Rect r = ((SuiCore$View * )self)->getViewRect(self) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, 0, r.w, r.h) ;
	SuiCore$Canvas$imagePattern(canvas, true, 0, 0, self->chessBg->width, self->chessBg->height, 0, bg, 1) ;
	SuiCore$Canvas$fill(canvas) ;
	self->degree->draw(self->degree, canvas, self->sceneTransform->mat, r.w, r.h, 0, 0) ;
}


void  HoroEditor$Horo2dSceneView$drawSelfBorder(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas){
	if (!self->editor) {
		return ; 
	}
	SuiCore$View$drawSelfBorder(self, canvas) ;
	self->drawRect_forANode(self, canvas, NULL) ;
	SuiDesigner$ANode *  sel = self->editor->editCtx->state->getFirstSelected(self->editor->editCtx->state) ;
	if (sel) {
		self->drawRect_forANode(self, canvas, sel) ;
	}
}


void  HoroEditor$Horo2dSceneView$drawRect_forANode(HoroEditor$Horo2dSceneView *  self, SuiCore$Canvas *  canvas, SuiDesigner$ANode *  sel){
	if (!sel) {
		return ; 
	}
	SuiCore$Node *  n = sel->node;
	if (n && Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )n;
		SuiCore$Frame *  f = &vb->frame;
		SuiCore$Rect myrect = ((SuiCore$ViewBase * )self)->get_abs_rect(self) ;
		SuiCore$Rect rect = vb->get_abs_rect(vb) ;
		int  x = rect.x - myrect.x;
		int  y = rect.y - myrect.y;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$rect(canvas, x, y, rect.w, rect.h) ;
		SuiCore$Canvas$fillColorByInt32(canvas, SuiCore$mkIntByRgba(255, 128, 255, 64) ) ;
		SuiCore$Canvas$fill(canvas) ;
		SuiCore$Canvas$strokeWidth(canvas, 1) ;
		SuiCore$Canvas$strokeColorByInt32(canvas, SuiCore$mkIntByRgba(0, 128, 255, 192) ) ;
		SuiCore$Canvas$stroke(canvas) ;
	}
}



static void  __finiBlock___Block_86_15(HoroEditor$__Block_86_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_86_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_205_37(HoroEditor$__Block_205_37 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_205_37, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_298_29(HoroEditor$__Block_298_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_298_29, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_338_23(HoroEditor$__Block_338_23 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_344_58(HoroEditor$__Block_344_58 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_89_27(HoroEditor$__Closure_89_27 *  self, SuiView$Drag *  d){
	printf("on drag. dx:%f,%f\n", d->deltaPos.x, d->deltaPos.y) ;
	self->__var___Block_86_15->self->sceneTransform->translate(self->__var___Block_86_15->self->sceneTransform, d->deltaPos.x, d->deltaPos.y, 0) ;
}

static void  __fini___Closure_89_27(HoroEditor$__Closure_89_27 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_89_27, __var___Block_86_15) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_89_27*  __make___Closure_89_27(HoroEditor$__Closure_89_27 **  __outRef__, HoroEditor$__Block_86_15 *  __var___Block_86_15){
	URGC_VAR_CLEANUP HoroEditor$__Closure_89_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_89_27) , __fini___Closure_89_27) ));
	self->invoke = __fn___Closure_89_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_89_27, __var___Block_86_15) , __var___Block_86_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_208(HoroEditor$__Closure_onActive_208 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n", item->cmd->str, item->label->str) ;
	self->__var___Block_205_37->self->_routeRightMenu(self->__var___Block_205_37->self, item) ;
}

static void  __fini___Closure_onActive_208(HoroEditor$__Closure_onActive_208 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_208, __var___Block_205_37) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_onActive_208*  __make___Closure_onActive_208(HoroEditor$__Closure_onActive_208 **  __outRef__, HoroEditor$__Block_205_37 *  __var___Block_205_37){
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_208*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_onActive_208) , __fini___Closure_onActive_208) ));
	self->invoke = __fn___Closure_onActive_208;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_208, __var___Block_205_37) , __var___Block_205_37) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_305_30(HoroEditor$__Closure_305_30 *  self){
	self->__var___Block_298_29->self->_reactGizmosDirty = false;
	self->__var___Block_298_29->self->reactGizmos(self->__var___Block_298_29->self) ;
	return true; 
}

static void  __fini___Closure_305_30(HoroEditor$__Closure_305_30 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_305_30, __var___Block_298_29) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_305_30*  __make___Closure_305_30(HoroEditor$__Closure_305_30 **  __outRef__, HoroEditor$__Block_298_29 *  __var___Block_298_29){
	URGC_VAR_CLEANUP HoroEditor$__Closure_305_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_305_30) , __fini___Closure_305_30) ));
	self->invoke = __fn___Closure_305_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_305_30, __var___Block_298_29) , __var___Block_298_29) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_324_32(HoroEditor$__Closure_324_32 *  self, SuiView$Drag *  d){
	
}

static void  __fini___Closure_324_32(HoroEditor$__Closure_324_32 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_324_32*  __make___Closure_324_32(HoroEditor$__Closure_324_32 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_324_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_324_32) , __fini___Closure_324_32) ));
	self->invoke = __fn___Closure_324_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_363_38(HoroEditor$__Closure_363_38 *  self, SuiCore$Rect newr){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("gizmo rect. set new rect:%s\n", SuiCore$Rect$toString(&tmpReturn_1, &newr) ->str) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
	self->__var___Block_338_23->sel->setAttr(self->__var___Block_338_23->sel, "width", Json$Json_mkNumber(&tmpReturn_2, newr.w) ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
	self->__var___Block_338_23->sel->setAttr(self->__var___Block_338_23->sel, "height", Json$Json_mkNumber(&tmpReturn_3, newr.h) ) ;
	self->__var___Block_344_58->selView->width = newr.w;
	self->__var___Block_344_58->selView->height = newr.h;
	((SuiCore$ViewBase * )self->__var___Block_344_58->selView)->frame.x = newr.x;
	((SuiCore$ViewBase * )self->__var___Block_344_58->selView)->frame.y = newr.y;
	((SuiCore$ViewBase * )self->__var___Block_344_58->selView)->invalidLayout(self->__var___Block_344_58->selView) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeAttrChanged*  tmpNewOwner_4 = NULL;
	{
		SuiDesigner$EventANodeAttrChanged*  o = SuiDesigner$EventANodeAttrChanged_new(&tmpNewOwner_4) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeAttrChanged, anode) , self->__var___Block_338_23->sel) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

static void  __fini___Closure_363_38(HoroEditor$__Closure_363_38 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_363_38, __var___Block_338_23) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_363_38, __var___Block_344_58) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_363_38*  __make___Closure_363_38(HoroEditor$__Closure_363_38 **  __outRef__, HoroEditor$__Block_338_23 *  __var___Block_338_23, HoroEditor$__Block_344_58 *  __var___Block_344_58){
	URGC_VAR_CLEANUP HoroEditor$__Closure_363_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_363_38) , __fini___Closure_363_38) ));
	self->invoke = __fn___Closure_363_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_363_38, __var___Block_338_23) , __var___Block_338_23) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_363_38, __var___Block_344_58) , __var___Block_344_58) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

HoroEditor$Horo2dSceneView*  HoroEditor$mkHoro2dSceneView(HoroEditor$Horo2dSceneView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (HoroEditor$Horo2dSceneView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_HoroEditor$Horo2dSceneView_init(NULL)) ) ; 
}



