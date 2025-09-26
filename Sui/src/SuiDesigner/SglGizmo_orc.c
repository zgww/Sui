
#include "SglGizmo_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../Orc/Math_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryRect_orc.h"
#include "../Sgl/GeometryLine_orc.h"
#include "../Sgl/GeometryCone_orc.h"
#include "../Sgl/GeometryTorus_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Ray_orc.h"
#include "../Sgl/Raycaster_orc.h"
#include "../Sgl/Billboard_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_137_65 SuiDesigner$__Block_137_65;

typedef struct tagSuiDesigner$__Block_162_69 SuiDesigner$__Block_162_69;

typedef struct tagSuiDesigner$__Block_207_62 SuiDesigner$__Block_207_62;

typedef struct tagSuiDesigner$__Block_233_69 SuiDesigner$__Block_233_69;

typedef struct tagSuiDesigner$__Block_303_69 SuiDesigner$__Block_303_69;

typedef struct tagSuiDesigner$__Closure_cbOnEvent_156 SuiDesigner$__Closure_cbOnEvent_156;

typedef struct tagSuiDesigner$__Closure_166_38 SuiDesigner$__Closure_166_38;

typedef struct tagSuiDesigner$__Closure_cbOnEvent_227 SuiDesigner$__Closure_cbOnEvent_227;

typedef struct tagSuiDesigner$__Closure_237_38 SuiDesigner$__Closure_237_38;

typedef struct tagSuiDesigner$__Closure_cbOnEvent_297 SuiDesigner$__Closure_cbOnEvent_297;

typedef struct tagSuiDesigner$__Closure_307_38 SuiDesigner$__Closure_307_38;



struct tagSuiDesigner$__Block_137_65 {
	Sgl$Obj3d*  target ;
};





struct tagSuiDesigner$__Block_162_69 {
	Sgl$Mesh*  mesh ;
};





struct tagSuiDesigner$__Block_207_62 {
	Sgl$Obj3d*  target ;
};





struct tagSuiDesigner$__Block_233_69 {
	Sgl$Mesh*  mesh ;
};





struct tagSuiDesigner$__Block_303_69 {
	Sgl$Mesh*  mesh ;
};





struct tagSuiDesigner$__Closure_cbOnEvent_156 {
	void  (*invoke)(SuiDesigner$__Closure_cbOnEvent_156 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_137_65*  __var___Block_137_65 ;
};





struct tagSuiDesigner$__Closure_166_38 {
	void  (*invoke)(SuiDesigner$__Closure_166_38 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_162_69*  __var___Block_162_69 ;
	SuiDesigner$__Block_137_65*  __var___Block_137_65 ;
};





struct tagSuiDesigner$__Closure_cbOnEvent_227 {
	void  (*invoke)(SuiDesigner$__Closure_cbOnEvent_227 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_207_62*  __var___Block_207_62 ;
};





struct tagSuiDesigner$__Closure_237_38 {
	void  (*invoke)(SuiDesigner$__Closure_237_38 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_233_69*  __var___Block_233_69 ;
	SuiDesigner$__Block_207_62*  __var___Block_207_62 ;
};





struct tagSuiDesigner$__Closure_cbOnEvent_297 {
	void  (*invoke)(SuiDesigner$__Closure_cbOnEvent_297 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_307_38 {
	void  (*invoke)(SuiDesigner$__Closure_307_38 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_303_69*  __var___Block_303_69 ;
};





// static function declaration
static void  __finiBlock___Block_137_65(SuiDesigner$__Block_137_65 *  self);
static void  __finiBlock___Block_162_69(SuiDesigner$__Block_162_69 *  self);
static void  __finiBlock___Block_207_62(SuiDesigner$__Block_207_62 *  self);
static void  __finiBlock___Block_233_69(SuiDesigner$__Block_233_69 *  self);
static void  __finiBlock___Block_303_69(SuiDesigner$__Block_303_69 *  self);
static void  __fn___Closure_cbOnEvent_156(SuiDesigner$__Closure_cbOnEvent_156 *  self, SuiCore$Event *  e);
static void  __fini___Closure_cbOnEvent_156(SuiDesigner$__Closure_cbOnEvent_156 *  self);
static SuiDesigner$__Closure_cbOnEvent_156*  __make___Closure_cbOnEvent_156(SuiDesigner$__Closure_cbOnEvent_156 **  __outRef__, SuiDesigner$__Block_137_65 *  __var___Block_137_65);
static void  __fn___Closure_166_38(SuiDesigner$__Closure_166_38 *  self, SuiView$Drag *  d);
static void  __fini___Closure_166_38(SuiDesigner$__Closure_166_38 *  self);
static SuiDesigner$__Closure_166_38*  __make___Closure_166_38(SuiDesigner$__Closure_166_38 **  __outRef__, SuiDesigner$__Block_162_69 *  __var___Block_162_69, SuiDesigner$__Block_137_65 *  __var___Block_137_65);
static void  __fn___Closure_cbOnEvent_227(SuiDesigner$__Closure_cbOnEvent_227 *  self, SuiCore$Event *  e);
static void  __fini___Closure_cbOnEvent_227(SuiDesigner$__Closure_cbOnEvent_227 *  self);
static SuiDesigner$__Closure_cbOnEvent_227*  __make___Closure_cbOnEvent_227(SuiDesigner$__Closure_cbOnEvent_227 **  __outRef__, SuiDesigner$__Block_207_62 *  __var___Block_207_62);
static void  __fn___Closure_237_38(SuiDesigner$__Closure_237_38 *  self, SuiView$Drag *  d);
static void  __fini___Closure_237_38(SuiDesigner$__Closure_237_38 *  self);
static SuiDesigner$__Closure_237_38*  __make___Closure_237_38(SuiDesigner$__Closure_237_38 **  __outRef__, SuiDesigner$__Block_233_69 *  __var___Block_233_69, SuiDesigner$__Block_207_62 *  __var___Block_207_62);
static void  __fn___Closure_cbOnEvent_297(SuiDesigner$__Closure_cbOnEvent_297 *  self, SuiCore$Event *  e);
static void  __fini___Closure_cbOnEvent_297(SuiDesigner$__Closure_cbOnEvent_297 *  self);
static SuiDesigner$__Closure_cbOnEvent_297*  __make___Closure_cbOnEvent_297(SuiDesigner$__Closure_cbOnEvent_297 **  __outRef__);
static void  __fn___Closure_307_38(SuiDesigner$__Closure_307_38 *  self, SuiView$Drag *  d);
static void  __fini___Closure_307_38(SuiDesigner$__Closure_307_38 *  self);
static SuiDesigner$__Closure_307_38*  __make___Closure_307_38(SuiDesigner$__Closure_307_38 **  __outRef__, SuiDesigner$__Block_303_69 *  __var___Block_303_69);



//vtable instance
Vtable_SuiDesigner$SglGizmo _vtable_SuiDesigner$SglGizmo;

// init meta

void SuiDesigner$SglGizmo_initMeta(Vtable_SuiDesigner$SglGizmo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(SuiDesigner$SglGizmo, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(SuiDesigner$SglGizmo, camera), true, false, 1);
	orc_metaField_class(&pNext, "raycaster", ((Vtable_Object*)Vtable_Sgl$Raycaster_init(0)), offsetof(SuiDesigner$SglGizmo, raycaster), true, false, 1);

	orc_metaField_method(&pNext, "dispatchMouseEvent", offsetof(SuiDesigner$SglGizmo, dispatchMouseEvent));
	orc_metaField_method(&pNext, "hitTest", offsetof(SuiDesigner$SglGizmo, hitTest));
	orc_metaField_method(&pNext, "onEvent", offsetof(SuiDesigner$SglGizmo, onEvent));
	orc_metaField_method(&pNext, "draw", offsetof(SuiDesigner$SglGizmo, draw));
}


// vtable init


Vtable_SuiDesigner$SglGizmo* Vtable_SuiDesigner$SglGizmo_init(Vtable_SuiDesigner$SglGizmo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SglGizmo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SglGizmo_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SglGizmo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SglGizmo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SglGizmo_fini(SuiDesigner$SglGizmo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$SglGizmo_init_fields(SuiDesigner$SglGizmo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SglGizmo_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglGizmo*)self)->scene, Sgl$Scene_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglGizmo*)self)->camera, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Raycaster*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SglGizmo*)self)->raycaster, Sgl$Raycaster_new(&tmpNewOwner_2) );
	urgc_set_field(self, (void**)&((SuiDesigner$SglGizmo*)self)->getNdcPos, NULL);
    }
	((SuiDesigner$SglGizmo*)self)->dispatchMouseEvent = (void*)SuiDesigner$SglGizmo$dispatchMouseEvent;
	((SuiDesigner$SglGizmo*)self)->hitTest = (void*)SuiDesigner$SglGizmo$hitTest;
	((SuiDesigner$SglGizmo*)self)->onEvent = (void*)SuiDesigner$SglGizmo$onEvent;
	((SuiDesigner$SglGizmo*)self)->draw = (void*)SuiDesigner$SglGizmo$draw;
}

// init function

void SuiDesigner$SglGizmo_init(SuiDesigner$SglGizmo *self, void *pOwner){
    Vtable_SuiDesigner$SglGizmo_init(&_vtable_SuiDesigner$SglGizmo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SglGizmo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SglGizmo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SglGizmo * SuiDesigner$SglGizmo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SglGizmo *self = calloc(1, sizeof(SuiDesigner$SglGizmo));
	
    SuiDesigner$SglGizmo_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SglGizmo$dispatchMouseEvent(SuiDesigner$SglGizmo *  self, SuiCore$MouseEvent *  e){
	self->hitTest(self, e) ;
}


void  SuiDesigner$SglGizmo$hitTest(SuiDesigner$SglGizmo *  self, SuiCore$MouseEvent *  e){
	self->raycaster->ray = ((Sgl$Camera * )self->camera)->mkRay(self->camera, e->ndcPos) ;
	Sgl$RayCheckResult r = self->raycaster->raycastTree(self->raycaster, self->scene) ;
	if (r.succ) {
		SuiCore$Node *  cur = r.obj;
		urgc_set_field_class(e, (void * )offsetof(SuiCore$ViewEvent, target) , cur) ;
		while (cur) {
			urgc_set_field_class(e, (void * )offsetof(SuiCore$ViewEvent, currentTarget) , cur) ;
			((SuiCore$Emitter * )cur)->emit(cur, e) ;
			if (((SuiCore$Event * )e)->isStopPropagation) {
				break;
			}
			cur = cur->parent;
		}
	}
}


void  SuiDesigner$SglGizmo$onEvent(SuiDesigner$SglGizmo *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		self->dispatchMouseEvent(self, (SuiCore$MouseEvent * )e) ;
	}
}


void  SuiDesigner$SglGizmo$draw(SuiDesigner$SglGizmo *  self, Sgl$DrawCtx *  ctx){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SglGizmo, camera) , ctx->camera) ;
	ctx->tick(ctx, self->scene) ;
	((Sgl$Obj3d * )self->scene)->updateWorldTransformAndSubtree(self->scene) ;
	((Sgl$Obj3d * )self->scene)->draw(self->scene, ctx) ;
	{
		Sgl$GeometryLine*  o = ctx->lineGeometry;
		
	
		o->color = 0xffff00ff;
		o->moveTo(o, 0, 0, 0) ;
		o->lineTo(o, 100, 10000, 0) ;
	}
}



Sgl$Obj3d*  SuiDesigner$SglGizmo_translate(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, Sgl$Obj3d*  target){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(target);

	URGC_VAR_CLEANUP SuiDesigner$__Block_137_65*  __var___Block_137_65 = (__var___Block_137_65=NULL,urgc_init_var((void**)&__var___Block_137_65, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_137_65) , __finiBlock___Block_137_65) ));
	urgc_set_field_class(__var___Block_137_65, (void * )offsetof(SuiDesigner$__Block_137_65, target) , target) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_1 = NULL;
	{
		Sgl$Mesh*  __scopeVar_138_4 = Sgl$mkMesh(&tmpReturn_1, o, key ? key : (long long )__builtin_return_address(0) ) , *o = __scopeVar_138_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_138_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		float  w = 100;
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryLine_new(&geom) ));
			geom->color = 0xffff0000;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, w, 0, 0) ;
			geom->color = 0xff00ff00;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, 0, w, 0) ;
			geom->color = 0xff0000ff;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, 0, 0, w) ;
			urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
			o->material->load(o->material, "../asset/line.matl.json") ;
		}
		Sgl$Mat$decompose(&__var___Block_137_65->target->_world_transform, &((Sgl$Obj3d * )o)->position, &((Sgl$Obj3d * )o)->quaternion, &((Sgl$Obj3d * )o)->scale) ;
		URGC_VAR_CLEANUP void  (**cbOnEvent)(void *  self, SuiCore$Event *  e) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_156*  tmpReturn_3 = NULL;
		(urgc_set_var(&cbOnEvent, __make___Closure_cbOnEvent_156(&tmpReturn_3, __var___Block_137_65) ) );
		Sgl$Mesh *  mesh;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_4 = NULL;
		mesh = SuiDesigner$SglGizmo_cone(&tmpReturn_4, o, 0, 60, SuiCore$mkVec3(w, 0, 0) , 0xffff0000) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "xArrow") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		((Sgl$Obj3d * )mesh)->rotation.z = -Orc$PI / 2;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_5 = NULL;
		mesh = SuiDesigner$SglGizmo_cone(&tmpReturn_5, o, 0, 60, SuiCore$mkVec3(0, w, 0) , 0xff00ff00) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "yArrow") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_6 = NULL;
		mesh = SuiDesigner$SglGizmo_cone(&tmpReturn_6, o, 0, 60, SuiCore$mkVec3(0, 0, w) , 0xff0000ff) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "zArrow") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		((Sgl$Obj3d * )mesh)->rotation.x = Orc$PI / 2;
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}

Sgl$Obj3d*  SuiDesigner$SglGizmo_rotate(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, Sgl$Obj3d*  target){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(target);

	URGC_VAR_CLEANUP SuiDesigner$__Block_207_62*  __var___Block_207_62 = (__var___Block_207_62=NULL,urgc_init_var((void**)&__var___Block_207_62, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_207_62) , __finiBlock___Block_207_62) ));
	urgc_set_field_class(__var___Block_207_62, (void * )offsetof(SuiDesigner$__Block_207_62, target) , target) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_1 = NULL;
	{
		Sgl$Mesh*  __scopeVar_208_4 = Sgl$mkMesh(&tmpReturn_1, o, key ? key : (long long )__builtin_return_address(0) ) , *o = __scopeVar_208_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_208_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		float  w = 100;
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryLine_new(&geom) ));
			geom->color = 0xffff0000;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, w, 0, 0) ;
			geom->color = 0xff00ff00;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, 0, w, 0) ;
			geom->color = 0xff0000ff;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, 0, 0, w) ;
			urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
			o->material->load(o->material, "../asset/line.matl.json") ;
		}
		Sgl$Mat$decompose(&__var___Block_207_62->target->_world_transform, &((Sgl$Obj3d * )o)->position, &((Sgl$Obj3d * )o)->quaternion, &((Sgl$Obj3d * )o)->scale) ;
		((Sgl$Obj3d * )o)->rotation = SuiCore$Quaternion$toVec3AsEuler(&((Sgl$Obj3d * )o)->quaternion, NULL) ;
		URGC_VAR_CLEANUP void  (**cbOnEvent)(void *  self, SuiCore$Event *  e) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_227*  tmpReturn_3 = NULL;
		(urgc_set_var(&cbOnEvent, __make___Closure_cbOnEvent_227(&tmpReturn_3, __var___Block_207_62) ) );
		Sgl$Mesh *  mesh;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_4 = NULL;
		mesh = SuiDesigner$SglGizmo_torus(&tmpReturn_4, o, 0, 60, SuiCore$mkVec3(0, 0, 0) , 0xffff0000) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "xTorus") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		((Sgl$Obj3d * )mesh)->rotation.y = Orc$PI / 2;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_5 = NULL;
		mesh = SuiDesigner$SglGizmo_torus(&tmpReturn_5, o, 0, 60, SuiCore$mkVec3(0, 0, 0) , 0xff00ff00) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "yTorus") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		((Sgl$Obj3d * )mesh)->rotation.x = Orc$PI / 2;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_6 = NULL;
		mesh = SuiDesigner$SglGizmo_torus(&tmpReturn_6, o, 0, 60, SuiCore$mkVec3(0, 0, 0) , 0xff0000ff) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "zTorus") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}

Sgl$Obj3d*  SuiDesigner$SglGizmo_scale(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, Sgl$Obj3d*  target){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(target);

	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_1 = NULL;
	{
		Sgl$Mesh*  __scopeVar_279_4 = Sgl$mkMesh(&tmpReturn_1, o, key ? key : (long long )__builtin_return_address(0) ) , *o = __scopeVar_279_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_279_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		float  w = 100;
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryLine_new(&geom) ));
			geom->color = 0xffff0000;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, w, 0, 0) ;
			geom->color = 0xff00ff00;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, 0, w, 0) ;
			geom->color = 0xff0000ff;
			geom->moveTo(geom, 0, 0, 0) ;
			geom->lineTo(geom, 0, 0, w) ;
			urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
			o->material->load(o->material, "../asset/line.matl.json") ;
		}
		Sgl$Mat$decompose(&target->_world_transform, &((Sgl$Obj3d * )o)->position, &((Sgl$Obj3d * )o)->quaternion, &((Sgl$Obj3d * )o)->scale) ;
		URGC_VAR_CLEANUP void  (**cbOnEvent)(void *  self, SuiCore$Event *  e) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_297*  tmpReturn_3 = NULL;
		(urgc_set_var(&cbOnEvent, __make___Closure_cbOnEvent_297(&tmpReturn_3) ) );
		Sgl$Mesh *  mesh;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_4 = NULL;
		mesh = SuiDesigner$SglGizmo_box(&tmpReturn_4, o, 0, 40, SuiCore$mkVec3(w, 0, 0) , 0xffff0000) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "xCube") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_5 = NULL;
		mesh = SuiDesigner$SglGizmo_box(&tmpReturn_5, o, 0, 40, SuiCore$mkVec3(0, w, 0) , 0xff00ff00) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "yCube") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_6 = NULL;
		mesh = SuiDesigner$SglGizmo_box(&tmpReturn_6, o, 0, 40, SuiCore$mkVec3(0, 0, w) , 0xff0000ff) ;
		Orc$String$set(((SuiCore$Node * )mesh)->name, "zCube") ;
		urgc_set_field(mesh, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , cbOnEvent) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}

static void  __finiBlock___Block_137_65(SuiDesigner$__Block_137_65 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_137_65, target) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_162_69(SuiDesigner$__Block_162_69 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_162_69, mesh) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_207_62(SuiDesigner$__Block_207_62 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_207_62, target) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_233_69(SuiDesigner$__Block_233_69 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_233_69, mesh) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_303_69(SuiDesigner$__Block_303_69 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_303_69, mesh) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_cbOnEvent_156(SuiDesigner$__Closure_cbOnEvent_156 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("mouse event:%s\n", me->toString(&tmpReturn_1, me) ->str) ;
		if (me->button == 1 && me->isMouseDown && ((SuiCore$ViewEvent * )me)->isBubble(me) ) {
			URGC_VAR_CLEANUP SuiDesigner$__Block_162_69*  __var___Block_162_69 = (__var___Block_162_69=NULL,urgc_init_var((void**)&__var___Block_162_69, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_162_69) , __finiBlock___Block_162_69) ));
			urgc_set_field_class(__var___Block_162_69, (void * )offsetof(SuiDesigner$__Block_162_69, mesh) , (Sgl$Mesh* )((SuiCore$ViewEvent * )me)->currentTarget) ;
			if (Orc_instanceof((Object*)__var___Block_162_69->mesh, (Vtable_Object*)Vtable_Sgl$Mesh_init(NULL))) {
				URGC_VAR_CLEANUP_CLASS SuiView$Drag*  drag = (drag=NULL,urgc_init_var_class((void**)&drag, SuiView$Drag_new(&drag) ));
				URGC_VAR_CLEANUP SuiDesigner$__Closure_166_38*  tmpReturn_2 = NULL;
				urgc_set_field(drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_166_38(&tmpReturn_2, __var___Block_162_69, self->__var___Block_137_65) ) ;
				drag->onMouseDown(drag, me) ;
			}
		}
	}
}

static void  __fini___Closure_cbOnEvent_156(SuiDesigner$__Closure_cbOnEvent_156 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_156, __var___Block_137_65) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_cbOnEvent_156*  __make___Closure_cbOnEvent_156(SuiDesigner$__Closure_cbOnEvent_156 **  __outRef__, SuiDesigner$__Block_137_65 *  __var___Block_137_65){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_156*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_cbOnEvent_156) , __fini___Closure_cbOnEvent_156) ));
	self->invoke = __fn___Closure_cbOnEvent_156;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_156, __var___Block_137_65) , __var___Block_137_65) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_166_38(SuiDesigner$__Closure_166_38 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("dragging...%s %f\n", ((SuiCore$Node * )self->__var___Block_162_69->mesh)->name->str, d->deltaPos.x) ;
		if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_162_69->mesh)->name, "xArrow") ) {
			self->__var___Block_137_65->target->position.x += d->deltaPos.x;
		}
		else if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_162_69->mesh)->name, "yArrow") ) {
			self->__var___Block_137_65->target->position.y += d->deltaPos.x;
		}
		else if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_162_69->mesh)->name, "zArrow") ) {
			self->__var___Block_137_65->target->position.z += d->deltaPos.x;
		}
	}
}

static void  __fini___Closure_166_38(SuiDesigner$__Closure_166_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_166_38, __var___Block_162_69) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_166_38, __var___Block_137_65) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_166_38*  __make___Closure_166_38(SuiDesigner$__Closure_166_38 **  __outRef__, SuiDesigner$__Block_162_69 *  __var___Block_162_69, SuiDesigner$__Block_137_65 *  __var___Block_137_65){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_166_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_166_38) , __fini___Closure_166_38) ));
	self->invoke = __fn___Closure_166_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_166_38, __var___Block_162_69) , __var___Block_162_69) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_166_38, __var___Block_137_65) , __var___Block_137_65) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_cbOnEvent_227(SuiDesigner$__Closure_cbOnEvent_227 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("mouse event:%s\n", me->toString(&tmpReturn_1, me) ->str) ;
		if (me->button == 1 && me->isMouseDown && ((SuiCore$ViewEvent * )me)->isBubble(me) ) {
			URGC_VAR_CLEANUP SuiDesigner$__Block_233_69*  __var___Block_233_69 = (__var___Block_233_69=NULL,urgc_init_var((void**)&__var___Block_233_69, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_233_69) , __finiBlock___Block_233_69) ));
			urgc_set_field_class(__var___Block_233_69, (void * )offsetof(SuiDesigner$__Block_233_69, mesh) , (Sgl$Mesh* )((SuiCore$ViewEvent * )me)->currentTarget) ;
			if (Orc_instanceof((Object*)__var___Block_233_69->mesh, (Vtable_Object*)Vtable_Sgl$Mesh_init(NULL))) {
				URGC_VAR_CLEANUP_CLASS SuiView$Drag*  drag = (drag=NULL,urgc_init_var_class((void**)&drag, SuiView$Drag_new(&drag) ));
				URGC_VAR_CLEANUP SuiDesigner$__Closure_237_38*  tmpReturn_2 = NULL;
				urgc_set_field(drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_237_38(&tmpReturn_2, __var___Block_233_69, self->__var___Block_207_62) ) ;
				drag->onMouseDown(drag, me) ;
			}
		}
	}
}

static void  __fini___Closure_cbOnEvent_227(SuiDesigner$__Closure_cbOnEvent_227 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_227, __var___Block_207_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_cbOnEvent_227*  __make___Closure_cbOnEvent_227(SuiDesigner$__Closure_cbOnEvent_227 **  __outRef__, SuiDesigner$__Block_207_62 *  __var___Block_207_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_227*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_cbOnEvent_227) , __fini___Closure_cbOnEvent_227) ));
	self->invoke = __fn___Closure_cbOnEvent_227;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_227, __var___Block_207_62) , __var___Block_207_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_237_38(SuiDesigner$__Closure_237_38 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("dragging...%s %f\n", ((SuiCore$Node * )self->__var___Block_233_69->mesh)->name->str, d->deltaPos.x) ;
		if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_233_69->mesh)->name, "xTorus") ) {
			self->__var___Block_207_62->target->rotation.x += d->deltaPos.x / 180.0 * Orc$PI;
		}
		else if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_233_69->mesh)->name, "yTorus") ) {
			self->__var___Block_207_62->target->rotation.y += d->deltaPos.x / 180.0 * Orc$PI;
		}
		else if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_233_69->mesh)->name, "zTorus") ) {
			self->__var___Block_207_62->target->rotation.z += d->deltaPos.x / 180.0 * Orc$PI;
		}
	}
}

static void  __fini___Closure_237_38(SuiDesigner$__Closure_237_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_237_38, __var___Block_233_69) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_237_38, __var___Block_207_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_237_38*  __make___Closure_237_38(SuiDesigner$__Closure_237_38 **  __outRef__, SuiDesigner$__Block_233_69 *  __var___Block_233_69, SuiDesigner$__Block_207_62 *  __var___Block_207_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_237_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_237_38) , __fini___Closure_237_38) ));
	self->invoke = __fn___Closure_237_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_237_38, __var___Block_233_69) , __var___Block_233_69) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_237_38, __var___Block_207_62) , __var___Block_207_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_cbOnEvent_297(SuiDesigner$__Closure_cbOnEvent_297 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("mouse event:%s\n", me->toString(&tmpReturn_1, me) ->str) ;
		if (me->button == 1 && me->isMouseDown && ((SuiCore$ViewEvent * )me)->isBubble(me) ) {
			URGC_VAR_CLEANUP SuiDesigner$__Block_303_69*  __var___Block_303_69 = (__var___Block_303_69=NULL,urgc_init_var((void**)&__var___Block_303_69, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_303_69) , __finiBlock___Block_303_69) ));
			urgc_set_field_class(__var___Block_303_69, (void * )offsetof(SuiDesigner$__Block_303_69, mesh) , (Sgl$Mesh* )((SuiCore$ViewEvent * )me)->currentTarget) ;
			if (Orc_instanceof((Object*)__var___Block_303_69->mesh, (Vtable_Object*)Vtable_Sgl$Mesh_init(NULL))) {
				URGC_VAR_CLEANUP_CLASS SuiView$Drag*  drag = (drag=NULL,urgc_init_var_class((void**)&drag, SuiView$Drag_new(&drag) ));
				URGC_VAR_CLEANUP SuiDesigner$__Closure_307_38*  tmpReturn_2 = NULL;
				urgc_set_field(drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_307_38(&tmpReturn_2, __var___Block_303_69) ) ;
				drag->onMouseDown(drag, me) ;
			}
		}
	}
}

static void  __fini___Closure_cbOnEvent_297(SuiDesigner$__Closure_cbOnEvent_297 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_cbOnEvent_297*  __make___Closure_cbOnEvent_297(SuiDesigner$__Closure_cbOnEvent_297 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_297*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_cbOnEvent_297) , __fini___Closure_cbOnEvent_297) ));
	self->invoke = __fn___Closure_cbOnEvent_297;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_307_38(SuiDesigner$__Closure_307_38 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("dragging...%s\n", ((SuiCore$Node * )self->__var___Block_303_69->mesh)->name->str) ;
		if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_303_69->mesh)->name, "xCube") ) {
			
		}
		else if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_303_69->mesh)->name, "yCube") ) {
			
		}
		else if (Orc$String$equals(((SuiCore$Node * )self->__var___Block_303_69->mesh)->name, "zCube") ) {
			
		}
	}
}

static void  __fini___Closure_307_38(SuiDesigner$__Closure_307_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_307_38, __var___Block_303_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_307_38*  __make___Closure_307_38(SuiDesigner$__Closure_307_38 **  __outRef__, SuiDesigner$__Block_303_69 *  __var___Block_303_69){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_307_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_307_38) , __fini___Closure_307_38) ));
	self->invoke = __fn___Closure_307_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_307_38, __var___Block_303_69) , __var___Block_303_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

Sgl$Obj3d*  SuiDesigner$SglGizmo_image(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, const char *  imgPath){
	URGC_VAR_CLEANUP_CLASS Sgl$Billboard*  tmpReturn_1 = NULL;
	{
		Sgl$Billboard*  __scopeVar_343_4 = Sgl$mkBillboard(&tmpReturn_1, o, key ? key : (long long )__builtin_return_address(0) ) , *o = __scopeVar_343_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_343_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(Sgl$Billboard, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
			o->material->load(o->material, "../asset/hi.matl.json") ;
			URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = Sgl$mkTex2dByPathCstr((tex = NULL,&tex), imgPath) ;
			o->material->setUniformTex2d(o->material, "tex", tex) ;
			URGC_VAR_CLEANUP_CLASS Sgl$GeometryRect*  box = (box=NULL,urgc_init_var_class((void**)&box, Sgl$GeometryRect_new(&box) ));
			box->build(box) ;
			urgc_set_field(o, (void * )offsetof(Sgl$Billboard, geometry) , box) ;
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}

Sgl$Obj3d*  SuiDesigner$SglGizmo_button(Sgl$Obj3d **  __outRef__, SuiCore$Node *  o, long long  key, const char *  label, void  (**onClick)(void *  self)){
	URGC_REF_ARG_WITH_CLEANUP(onClick);

	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}

Sgl$Obj3d*  SuiDesigner$SglGizmo_text(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, const char *  label){
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}

Sgl$Mesh*  SuiDesigner$SglGizmo_box(Sgl$Mesh **  __outRef__, Sgl$Obj3d *  o, long long  key, float  size, SuiCore$Vec3 pos, int  color){
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_1 = NULL;
	{
		Sgl$Mesh*  __scopeVar_372_4 = Sgl$mkMesh(&tmpReturn_1, o, key ? key : (long long )__builtin_return_address(0) ) , *o = __scopeVar_372_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_372_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
			o->material->load(o->material, "../asset/basic.matl.json") ;
			URGC_VAR_CLEANUP_CLASS Sgl$GeometryBox*  box = (box=NULL,urgc_init_var_class((void**)&box, Sgl$GeometryBox_new(&box) ));
			box->width = size;
			box->height = size;
			box->depth = size;
			box->color = color;
			box->build(box) ;
			urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , box) ;
		}
		o->material->setUniform4fByInt32Color(o->material, "color", color) ;
		((Sgl$Obj3d * )o)->position = pos;
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}

Sgl$Mesh*  SuiDesigner$SglGizmo_cone(Sgl$Mesh **  __outRef__, Sgl$Obj3d *  o, long long  key, float  size, SuiCore$Vec3 pos, int  color){
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_1 = NULL;
	{
		Sgl$Mesh*  __scopeVar_394_4 = Sgl$mkMesh(&tmpReturn_1, o, key ? key : (long long )__builtin_return_address(0) ) , *o = __scopeVar_394_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_394_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
			o->material->load(o->material, "../asset/basic.matl.json") ;
			URGC_VAR_CLEANUP_CLASS Sgl$GeometryCone*  cone = (cone=NULL,urgc_init_var_class((void**)&cone, Sgl$GeometryCone_new(&cone) ));
			((Sgl$GeometryCylinder * )cone)->height = size;
			((Sgl$GeometryCylinder * )cone)->radiusBottom = size / 4.0;
			((Sgl$GeometryCylinder * )cone)->build(cone) ;
			urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , cone) ;
		}
		o->material->setUniform4fByInt32Color(o->material, "color", color) ;
		((Sgl$Obj3d * )o)->position = pos;
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}

Sgl$Mesh*  SuiDesigner$SglGizmo_torus(Sgl$Mesh **  __outRef__, Sgl$Obj3d *  o, long long  key, float  size, SuiCore$Vec3 pos, int  color){
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_1 = NULL;
	{
		Sgl$Mesh*  __scopeVar_413_4 = Sgl$mkMesh(&tmpReturn_1, o, key ? key : (long long )__builtin_return_address(0) ) , *o = __scopeVar_413_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_413_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
			o->material->load(o->material, "../asset/basic.matl.json") ;
			URGC_VAR_CLEANUP_CLASS Sgl$GeometryTorus*  cone = (cone=NULL,urgc_init_var_class((void**)&cone, Sgl$GeometryTorus_new(&cone) ));
			cone->build(cone) ;
			urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , cone) ;
		}
		o->material->setUniform4fByInt32Color(o->material, "color", color) ;
		((Sgl$Obj3d * )o)->position = pos;
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}



