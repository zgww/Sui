
#include "ToolBase_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Camera_orc.h"
#include "../Sgl/Raycaster_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Light_orc.h"
#include "../Sgl/SpotLight_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Billboard_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryLine_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "./SglEditCtx_orc.h"
#include "./SglGizmo_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_72_19 SuiDesigner$__Block_72_19;

typedef struct tagSuiDesigner$__Block_145_29 SuiDesigner$__Block_145_29;

typedef struct tagSuiDesigner$__Closure_74_28 SuiDesigner$__Closure_74_28;

typedef struct tagSuiDesigner$__Closure_cbOnEvent_163 SuiDesigner$__Closure_cbOnEvent_163;



struct tagSuiDesigner$__Block_72_19 {
	SuiDesigner$ToolSelect*  self ;
};





struct tagSuiDesigner$__Block_145_29 {
	SuiDesigner$ToolSelect*  self ;
	bool  dragging ;
};





struct tagSuiDesigner$__Closure_74_28 {
	void  (*invoke)(SuiDesigner$__Closure_74_28 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_72_19*  __var___Block_72_19 ;
};





struct tagSuiDesigner$__Closure_cbOnEvent_163 {
	void  (*invoke)(SuiDesigner$__Closure_cbOnEvent_163 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_145_29*  __var___Block_145_29 ;
};





// static function declaration
static void  __finiBlock___Block_72_19(SuiDesigner$__Block_72_19 *  self);
static void  __finiBlock___Block_145_29(SuiDesigner$__Block_145_29 *  self);
static void  __fn___Closure_74_28(SuiDesigner$__Closure_74_28 *  self, SuiView$Drag *  d);
static void  __fini___Closure_74_28(SuiDesigner$__Closure_74_28 *  self);
static SuiDesigner$__Closure_74_28*  __make___Closure_74_28(SuiDesigner$__Closure_74_28 **  __outRef__, SuiDesigner$__Block_72_19 *  __var___Block_72_19);
static void  __fn___Closure_cbOnEvent_163(SuiDesigner$__Closure_cbOnEvent_163 *  self, SuiCore$Event *  e);
static void  __fini___Closure_cbOnEvent_163(SuiDesigner$__Closure_cbOnEvent_163 *  self);
static SuiDesigner$__Closure_cbOnEvent_163*  __make___Closure_cbOnEvent_163(SuiDesigner$__Closure_cbOnEvent_163 **  __outRef__, SuiDesigner$__Block_145_29 *  __var___Block_145_29);



//vtable instance
Vtable_SuiDesigner$ToolBase _vtable_SuiDesigner$ToolBase;

// init meta

void SuiDesigner$ToolBase_initMeta(Vtable_SuiDesigner$ToolBase *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ToolBase, name), true, false, 1);
	orc_metaField_class(&pNext, "iconPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ToolBase, iconPath), true, false, 1);
	orc_metaField_class(&pNext, "mgr", ((Vtable_Object*)Vtable_SuiDesigner$ToolMgr_init(0)), offsetof(SuiDesigner$ToolBase, mgr), true, false, 1);

	orc_metaField_method(&pNext, "onEnable", offsetof(SuiDesigner$ToolBase, onEnable));
	orc_metaField_method(&pNext, "onDisable", offsetof(SuiDesigner$ToolBase, onDisable));
	orc_metaField_method(&pNext, "reactGizmo", offsetof(SuiDesigner$ToolBase, reactGizmo));
	orc_metaField_method(&pNext, "onEvent", offsetof(SuiDesigner$ToolBase, onEvent));
	orc_metaField_method(&pNext, "draw2d", offsetof(SuiDesigner$ToolBase, draw2d));
	orc_metaField_method(&pNext, "reactGizmosView", offsetof(SuiDesigner$ToolBase, reactGizmosView));
}


// vtable init


Vtable_SuiDesigner$ToolBase* Vtable_SuiDesigner$ToolBase_init(Vtable_SuiDesigner$ToolBase* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ToolBase;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ToolBase_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ToolBase";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ToolBase_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ToolBase_fini(SuiDesigner$ToolBase *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$ToolBase_init_fields(SuiDesigner$ToolBase *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ToolBase_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->name, Orc$str(&tmpReturn_1, "") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->iconPath, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->mgr, NULL);
    }
	((SuiDesigner$ToolBase*)self)->onEnable = (void*)SuiDesigner$ToolBase$onEnable;
	((SuiDesigner$ToolBase*)self)->onDisable = (void*)SuiDesigner$ToolBase$onDisable;
	((SuiDesigner$ToolBase*)self)->reactGizmo = (void*)SuiDesigner$ToolBase$reactGizmo;
	((SuiDesigner$ToolBase*)self)->onEvent = (void*)SuiDesigner$ToolBase$onEvent;
	((SuiDesigner$ToolBase*)self)->draw2d = (void*)SuiDesigner$ToolBase$draw2d;
	((SuiDesigner$ToolBase*)self)->reactGizmosView = (void*)SuiDesigner$ToolBase$reactGizmosView;
}

// init function

void SuiDesigner$ToolBase_init(SuiDesigner$ToolBase *self, void *pOwner){
    Vtable_SuiDesigner$ToolBase_init(&_vtable_SuiDesigner$ToolBase);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ToolBase;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ToolBase_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ToolBase * SuiDesigner$ToolBase_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ToolBase *self = calloc(1, sizeof(SuiDesigner$ToolBase));
	
    SuiDesigner$ToolBase_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ToolBase$onEnable(SuiDesigner$ToolBase *  self){
	
}


void  SuiDesigner$ToolBase$onDisable(SuiDesigner$ToolBase *  self){
	
}


void  SuiDesigner$ToolBase$reactGizmo(SuiDesigner$ToolBase *  self, Sgl$Obj3d *  gizmoScene){
	
}


void  SuiDesigner$ToolBase$onEvent(SuiDesigner$ToolBase *  self, SuiCore$Event *  e){
	
}


void  SuiDesigner$ToolBase$draw2d(SuiDesigner$ToolBase *  self, SuiCore$Canvas *  canvas){
	
}


void  SuiDesigner$ToolBase$reactGizmosView(SuiDesigner$ToolBase *  self, SuiCore$Node *  o){
	
}




//vtable instance
Vtable_SuiDesigner$ToolSelect _vtable_SuiDesigner$ToolSelect;

// init meta

void SuiDesigner$ToolSelect_initMeta(Vtable_SuiDesigner$ToolSelect *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "leftPos", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner$ToolSelect, leftPos), false, false, 0);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$ToolSelect, drag), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$ToolSelect* Vtable_SuiDesigner$ToolSelect_init(Vtable_SuiDesigner$ToolSelect* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ToolSelect;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$ToolBase_init(&_vtable_SuiDesigner$ToolBase);

	// init by super vtable init function
    Vtable_SuiDesigner$ToolBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$ToolBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ToolSelect_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ToolSelect";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ToolSelect_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ToolSelect_fini(SuiDesigner$ToolSelect *self){
	//super fini
    SuiDesigner$ToolBase_fini((SuiDesigner$ToolBase *)self);

    //字段释放


}

// init fields function


void SuiDesigner$ToolSelect_init_fields(SuiDesigner$ToolSelect *self){
	//super class
    SuiDesigner$ToolBase_init_fields((SuiDesigner$ToolBase*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ToolSelect_fini;
	//fields
    {
	((SuiDesigner$ToolSelect*)self)->leftPos = SuiCore$mkVec3(-200, 0, -200) ;
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolSelect*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$ToolBase*)self)->onEnable = (void*)SuiDesigner$ToolSelect$onEnable;
	((SuiDesigner$ToolBase*)self)->onDisable = (void*)SuiDesigner$ToolSelect$onDisable;
	((SuiDesigner$ToolBase*)self)->draw2d = (void*)SuiDesigner$ToolSelect$draw2d;
	((SuiDesigner$ToolBase*)self)->reactGizmosView = (void*)SuiDesigner$ToolSelect$reactGizmosView;
	((SuiDesigner$ToolBase*)self)->onEvent = (void*)SuiDesigner$ToolSelect$onEvent;
	((SuiDesigner$ToolBase*)self)->reactGizmo = (void*)SuiDesigner$ToolSelect$reactGizmo;
}

// init function

void SuiDesigner$ToolSelect_init(SuiDesigner$ToolSelect *self, void *pOwner){
    Vtable_SuiDesigner$ToolSelect_init(&_vtable_SuiDesigner$ToolSelect);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ToolSelect;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ToolSelect_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ToolSelect * SuiDesigner$ToolSelect_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ToolSelect *self = calloc(1, sizeof(SuiDesigner$ToolSelect));
	
    SuiDesigner$ToolSelect_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ToolSelect$onEnable(SuiDesigner$ToolSelect *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_72_19*  __var___Block_72_19 = (__var___Block_72_19=NULL,urgc_init_var((void**)&__var___Block_72_19, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_72_19) , __finiBlock___Block_72_19) ));
	urgc_set_field_class(__var___Block_72_19, (void * )offsetof(SuiDesigner$__Block_72_19, self) , self) ;
	printf("onEnable ToolSelect\n.") ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_74_28*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_74_28(&tmpReturn_1, __var___Block_72_19) ) ;
}


void  SuiDesigner$ToolSelect$onDisable(SuiDesigner$ToolSelect *  self){
	printf("onDisable ToolSelect\n.") ;
}


void  SuiDesigner$ToolSelect$draw2d(SuiDesigner$ToolSelect *  self, SuiCore$Canvas *  canvas){
	
}


void  SuiDesigner$ToolSelect$reactGizmosView(SuiDesigner$ToolSelect *  self, SuiCore$Node *  o){
	
}


void  SuiDesigner$ToolSelect$onEvent(SuiDesigner$ToolSelect *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP_CLASS Sgl$Raycaster*  raycaster = (raycaster=NULL,urgc_init_var_class((void**)&raycaster, Sgl$Raycaster_new(&raycaster) ));
			raycaster->ray = ((SuiDesigner$ToolBase * )self)->mgr->camera->mkRay(((SuiDesigner$ToolBase * )self)->mgr->camera, me->ndcPos) ;
			Sgl$RayCheckResult r = raycaster->raycastTree(raycaster, ((SuiDesigner$ToolBase * )self)->mgr->scene) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			printf("\n\nToolSelect. ndcPos:%s onClick succ:%d dist:%f, point:%s, name:%s\n", SuiCore$Vec2$toString(&tmpReturn_1, &me->ndcPos) ->str, r.succ, r.distance, SuiCore$Vec3$toString(&tmpReturn_2, &r.point) ->str, r.obj ? ((SuiCore$Node * )r.obj)->name->str : "null") ;
			if (r.succ) {
				((SuiDesigner$ToolBase * )self)->mgr->editCtx->state->setSelected(((SuiDesigner$ToolBase * )self)->mgr->editCtx->state, r.obj) ;
				printf("选中对象....") ;
			}
		}
	}
}


void  SuiDesigner$ToolSelect$reactGizmo(SuiDesigner$ToolSelect *  self, Sgl$Obj3d *  o){
	URGC_VAR_CLEANUP SuiDesigner$__Block_145_29*  __var___Block_145_29 = (__var___Block_145_29=NULL,urgc_init_var((void**)&__var___Block_145_29, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_145_29) , __finiBlock___Block_145_29) ));
	urgc_set_field_class(__var___Block_145_29, (void * )offsetof(SuiDesigner$__Block_145_29, self) , self) ;
	__var___Block_145_29->dragging = false;
	URGC_VAR_CLEANUP void  (**cbOnEvent)(void *  self, SuiCore$Event *  e) = NULL;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_163*  tmpReturn_1 = NULL;
	(urgc_set_var(&cbOnEvent, __make___Closure_cbOnEvent_163(&tmpReturn_1, __var___Block_145_29) ) );
	Sgl$Obj3d *  obj3d = ((SuiDesigner$ToolBase * )self)->mgr->selectNode;
	if (Orc_instanceof((Object*)obj3d, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_2 = NULL;
		SuiDesigner$SglGizmo_rotate(&tmpReturn_2, o, 0, obj3d) ;
	}
	if (Orc_instanceof((Object*)((SuiDesigner$ToolBase * )self)->mgr->selectNode, (Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(NULL))) {
		Sgl$PerspectiveCamera *  cam = (Sgl$PerspectiveCamera * )((SuiDesigner$ToolBase * )self)->mgr->selectNode;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_3 = NULL;
		{
			Sgl$Mesh*  __scopeVar_227_12 = Sgl$mkMesh(&tmpReturn_3, o, 0) , *o = __scopeVar_227_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_227_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryLine_new(&geom) ));
				((Sgl$Camera * )cam)->updateProjectionMat(cam) ;
				((Sgl$Camera * )cam)->updateViewMat(cam) ;
				geom->buildCameraHelper(geom, cam) ;
				urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_4 = NULL;
				urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_4) ) ;
				o->material->load(o->material, "../asset/line.matl.json") ;
			}
			((Sgl$Obj3d * )o)->position = ((Sgl$Obj3d * )cam)->localToWorld(cam, SuiCore$mkVec3(0, 0, 0) ) ;
			Sgl$Mat$decompose(&((Sgl$Obj3d * )cam)->_world_transform, &((Sgl$Obj3d * )o)->position, &((Sgl$Obj3d * )o)->quaternion, &((Sgl$Obj3d * )o)->scale) ;
			((Sgl$Obj3d * )o)->rotation = SuiCore$Quaternion$toVec3AsEuler(&((Sgl$Obj3d * )o)->quaternion, NULL) ;
		}
	}
	else if (Orc_instanceof((Object*)((SuiDesigner$ToolBase * )self)->mgr->selectNode, (Vtable_Object*)Vtable_Sgl$SpotLight_init(NULL))) {
		Sgl$SpotLight *  l = (Sgl$SpotLight * )((SuiDesigner$ToolBase * )self)->mgr->selectNode;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_5 = NULL;
		{
			Sgl$Mesh*  __scopeVar_252_12 = Sgl$mkMesh(&tmpReturn_5, o, 0) , *o = __scopeVar_252_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_252_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryLine_new(&geom) ));
				geom->buildSpotLightHelper(geom, l) ;
				urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_6 = NULL;
				urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_6) ) ;
				o->material->load(o->material, "../asset/line.matl.json") ;
			}
			((Sgl$Obj3d * )o)->position = ((Sgl$Obj3d * )l)->localToWorld(l, SuiCore$mkVec3(0, 0, 0) ) ;
		}
	}
	else if (Orc_instanceof((Object*)((SuiDesigner$ToolBase * )self)->mgr->selectNode, (Vtable_Object*)Vtable_Sgl$PointLight_init(NULL))) {
		Sgl$PointLight *  l = (Sgl$PointLight * )((SuiDesigner$ToolBase * )self)->mgr->selectNode;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_7 = NULL;
		{
			Sgl$Mesh*  __scopeVar_267_12 = Sgl$mkMesh(&tmpReturn_7, o, 0) , *o = __scopeVar_267_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_267_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP_CLASS Sgl$GeometrySphere*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometrySphere_new(&geom) ));
				geom->radius = l->distance;
				geom->widthSegments = 8;
				geom->heightSegments = 8;
				geom->build(geom) ;
				urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_8 = NULL;
				urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_8) ) ;
				o->material->load(o->material, "../asset/box.matl.json") ;
				o->material->wireframe = true;
			}
			((Sgl$Obj3d * )o)->position = ((Sgl$Obj3d * )l)->localToWorld(l, SuiCore$mkVec3(0, 0, 0) ) ;
		}
	}
}



static void  __finiBlock___Block_72_19(SuiDesigner$__Block_72_19 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_72_19, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_145_29(SuiDesigner$__Block_145_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_145_29, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_74_28(SuiDesigner$__Closure_74_28 *  self, SuiView$Drag *  d){
	printf("on drag gizmo left\n") ;
	SuiCore$Vec3$add3fLocal(&self->__var___Block_72_19->self->leftPos, d->deltaPos.x, -d->deltaPos.y, 0) ;
}

static void  __fini___Closure_74_28(SuiDesigner$__Closure_74_28 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_74_28, __var___Block_72_19) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_74_28*  __make___Closure_74_28(SuiDesigner$__Closure_74_28 **  __outRef__, SuiDesigner$__Block_72_19 *  __var___Block_72_19){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_74_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_74_28) , __fini___Closure_74_28) ));
	self->invoke = __fn___Closure_74_28;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_74_28, __var___Block_72_19) , __var___Block_72_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_cbOnEvent_163(SuiDesigner$__Closure_cbOnEvent_163 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$ViewEvent_init(NULL))) {
		SuiCore$ViewEvent *  ve = (SuiCore$ViewEvent * )e;
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		self->__var___Block_145_29->self->drag->onMouseDown(self->__var___Block_145_29->self->drag, me) ;
		if (((SuiCore$ViewEvent * )me)->isCapture) {
			printf("box gizmo.cbOnEvent:%s. %s. dragging:%d isCapture:%d\n", e->name->str, ((SuiCore$ViewEvent * )me)->target->name->str, self->__var___Block_145_29->dragging, ((SuiCore$ViewEvent * )me)->isCapture) ;
		}
	}
}

static void  __fini___Closure_cbOnEvent_163(SuiDesigner$__Closure_cbOnEvent_163 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_163, __var___Block_145_29) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_cbOnEvent_163*  __make___Closure_cbOnEvent_163(SuiDesigner$__Closure_cbOnEvent_163 **  __outRef__, SuiDesigner$__Block_145_29 *  __var___Block_145_29){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_163*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_cbOnEvent_163) , __fini___Closure_cbOnEvent_163) ));
	self->invoke = __fn___Closure_cbOnEvent_163;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_163, __var___Block_145_29) , __var___Block_145_29) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}


//vtable instance
Vtable_SuiDesigner$ToolMgr _vtable_SuiDesigner$ToolMgr;

// init meta

void SuiDesigner$ToolMgr_initMeta(Vtable_SuiDesigner$ToolMgr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "tool", ((Vtable_Object*)Vtable_SuiDesigner$ToolBase_init(0)), offsetof(SuiDesigner$ToolMgr, tool), true, false, 1);
	orc_metaField_class(&pNext, "selectNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$ToolMgr, selectNode), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(SuiDesigner$ToolMgr, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$Camera_init(0)), offsetof(SuiDesigner$ToolMgr, camera), true, false, 1);
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_SuiDesigner$SglEditCtx_init(0)), offsetof(SuiDesigner$ToolMgr, editCtx), true, false, 1);
	orc_metaField_class(&pNext, "gizmosView", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$ToolMgr, gizmosView), false, true, 1);

	orc_metaField_method(&pNext, "setTool", offsetof(SuiDesigner$ToolMgr, setTool));
	orc_metaField_method(&pNext, "onEvent", offsetof(SuiDesigner$ToolMgr, onEvent));
	orc_metaField_method(&pNext, "reactGizmo", offsetof(SuiDesigner$ToolMgr, reactGizmo));
	orc_metaField_method(&pNext, "_reactGizmosForNode", offsetof(SuiDesigner$ToolMgr, _reactGizmosForNode));
	orc_metaField_method(&pNext, "reactGizmosView", offsetof(SuiDesigner$ToolMgr, reactGizmosView));
	orc_metaField_method(&pNext, "draw2d", offsetof(SuiDesigner$ToolMgr, draw2d));
}


// vtable init


Vtable_SuiDesigner$ToolMgr* Vtable_SuiDesigner$ToolMgr_init(Vtable_SuiDesigner$ToolMgr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ToolMgr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ToolMgr_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ToolMgr";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ToolMgr_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ToolMgr_fini(SuiDesigner$ToolMgr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$ToolMgr_init_fields(SuiDesigner$ToolMgr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ToolMgr_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->tool, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->selectNode, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->camera, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->editCtx, NULL);
    }
	((SuiDesigner$ToolMgr*)self)->setTool = (void*)SuiDesigner$ToolMgr$setTool;
	((SuiDesigner$ToolMgr*)self)->onEvent = (void*)SuiDesigner$ToolMgr$onEvent;
	((SuiDesigner$ToolMgr*)self)->reactGizmo = (void*)SuiDesigner$ToolMgr$reactGizmo;
	((SuiDesigner$ToolMgr*)self)->_reactGizmosForNode = (void*)SuiDesigner$ToolMgr$_reactGizmosForNode;
	((SuiDesigner$ToolMgr*)self)->reactGizmosView = (void*)SuiDesigner$ToolMgr$reactGizmosView;
	((SuiDesigner$ToolMgr*)self)->draw2d = (void*)SuiDesigner$ToolMgr$draw2d;
}

// init function

void SuiDesigner$ToolMgr_init(SuiDesigner$ToolMgr *self, void *pOwner){
    Vtable_SuiDesigner$ToolMgr_init(&_vtable_SuiDesigner$ToolMgr);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ToolMgr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ToolMgr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ToolMgr * SuiDesigner$ToolMgr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ToolMgr *self = calloc(1, sizeof(SuiDesigner$ToolMgr));
	
    SuiDesigner$ToolMgr_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ToolMgr$setTool(SuiDesigner$ToolMgr *  self, SuiDesigner$ToolBase *  tool){
	if (self->tool == tool) {
		return ; 
	}
	if (self->tool) {
		self->tool->onDisable(self->tool) ;
	}
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ToolMgr, tool) , tool) ;
	if (self->tool) {
		urgc_set_field_class(self->tool, (void * )offsetof(SuiDesigner$ToolBase, mgr) , self) ;
		self->tool->onEnable(self->tool) ;
	}
}


void  SuiDesigner$ToolMgr$onEvent(SuiDesigner$ToolMgr *  self, SuiCore$Event *  e){
	if (self->tool) {
		self->tool->onEvent(self->tool, e) ;
	}
}


void  SuiDesigner$ToolMgr$reactGizmo(SuiDesigner$ToolMgr *  self, SuiDesigner$SglGizmo *  gizmoScene){
	if (self->tool) {
		{
			Sgl$Scene*  o = gizmoScene->scene;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_321_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			self->tool->reactGizmo(self->tool, gizmoScene->scene) ;
		}
	}
}


void  SuiDesigner$ToolMgr$_reactGizmosForNode(SuiDesigner$ToolMgr *  self, SuiCore$Node *  n){
	SuiCore$Node *  o = self->gizmosView;
	if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		Sgl$Obj3d *  obj3d = (Sgl$Obj3d * )n;
		if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Light_init(NULL))) {
			URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_1 = NULL;
			{
				SuiView$ImageView*  __scopeVar_332_16 = SuiView$mkImageView(&tmpReturn_1, o, (long long )n) , *o = __scopeVar_332_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_332_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
				o->setSrc(o, Orc$str(&tmpReturn_2, "../asset/gizmo/light.png") ) ;
				((SuiCore$View * )o)->width = 32;
				o->setImageMode(o, SuiView$WidthFix) ;
				SuiCore$Vec3 worldPos = obj3d->localToWorld(obj3d, SuiCore$mkVec3(0, 0, 0) ) ;
				SuiCore$Vec3 clientPos = self->camera->project(self->camera, worldPos) ;
				SuiCore$Vec2 clientSize = SuiCore$Frame$getSize(&((SuiCore$ViewBase * )self->editCtx->sceneView)->frame) ;
				((SuiCore$ViewBase * )o)->frame.x = SuiCore$Vec2$width(&clientSize)  * (clientPos.x + 1.0) / 2.0 - ((SuiCore$ViewBase * )o)->frame.width / 2.0;
				((SuiCore$ViewBase * )o)->frame.y = SuiCore$Vec2$height(&clientSize)  * (1.0 - (clientPos.y + 1.0) / 2.0) - ((SuiCore$ViewBase * )o)->frame.height / 2.0;
			}
		}
		else if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Camera_init(NULL))) {
			URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_3 = NULL;
			{
				SuiView$ImageView*  __scopeVar_348_16 = SuiView$mkImageView(&tmpReturn_3, o, (long long )n) , *o = __scopeVar_348_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_348_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				o->setSrc(o, Orc$str(&tmpReturn_4, "../asset/gizmo/camera.png") ) ;
				((SuiCore$View * )o)->width = 32;
				o->setImageMode(o, SuiView$WidthFix) ;
				SuiCore$Vec3 worldPos = obj3d->localToWorld(obj3d, SuiCore$mkVec3(0, 0, 0) ) ;
				SuiCore$Vec3 clientPos = self->camera->project(self->camera, worldPos) ;
				SuiCore$Vec2 clientSize = SuiCore$Frame$getSize(&((SuiCore$ViewBase * )self->editCtx->sceneView)->frame) ;
				((SuiCore$ViewBase * )o)->frame.x = SuiCore$Vec2$width(&clientSize)  * (clientPos.x + 1.0) / 2.0 - ((SuiCore$ViewBase * )o)->frame.width / 2.0;
				((SuiCore$ViewBase * )o)->frame.y = SuiCore$Vec2$height(&clientSize)  * (1.0 - (clientPos.y + 1.0) / 2.0) - ((SuiCore$ViewBase * )o)->frame.height / 2.0;
			}
		}
	}
}


void  SuiDesigner$ToolMgr$reactGizmosView(SuiDesigner$ToolMgr *  self, SuiCore$Node *  o){
	self->gizmosView = o;
	SuiCore$Node$walk((SuiCore$Node * )self->scene, self->_reactGizmosForNode, self) ;
	if (self->tool) {
		self->tool->reactGizmosView(self->tool, o) ;
	}
}


void  SuiDesigner$ToolMgr$draw2d(SuiDesigner$ToolMgr *  self, SuiCore$Canvas *  canvas){
	if (self->tool) {
		self->tool->draw2d(self->tool, canvas) ;
	}
}





