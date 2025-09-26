
#include "DrawCtx_orc.h" 

#include <stdlib.h>
#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Math_orc.h"
#include "./Scene_orc.h"
#include "./Camera_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./GeometryLine_orc.h"
#include "./Light_orc.h"
#include "./Mat_orc.h"
#include "./PointLight_orc.h"
#include "./DirLight_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Color_orc.h"


// static struct 


// static function declaration
static int  cmpObj3dDepth(const void *  a, const void *  b);



//vtable instance
Vtable_Sgl$DrawCtx _vtable_Sgl$DrawCtx;

// init meta

void Sgl$DrawCtx_initMeta(Vtable_Sgl$DrawCtx *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "lights", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$DrawCtx, lights), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(Sgl$DrawCtx, scene), false, true, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$Camera_init(0)), offsetof(Sgl$DrawCtx, camera), false, true, 1);
	orc_metaField_struct(&pNext, "frameSize", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(Sgl$DrawCtx, frameSize), false, false, 0);
	orc_metaField_primitive(&pNext, "prevTickMs", OrcMetaType_long_long, offsetof(Sgl$DrawCtx, prevTickMs), 0, 0, 0, 0);//longlong
	orc_metaField_primitive(&pNext, "dtMs", OrcMetaType_long_long, offsetof(Sgl$DrawCtx, dtMs), 0, 0, 0, 0);//longlong
	orc_metaField_primitive(&pNext, "dtSec", OrcMetaType_float, offsetof(Sgl$DrawCtx, dtSec), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "passSec", OrcMetaType_float, offsetof(Sgl$DrawCtx, passSec), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "depthMatl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$DrawCtx, depthMatl), true, false, 1);
	orc_metaField_class(&pNext, "lineMatl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$DrawCtx, lineMatl), true, false, 1);
	orc_metaField_class(&pNext, "lineGeometry", ((Vtable_Object*)Vtable_Sgl$GeometryLine_init(0)), offsetof(Sgl$DrawCtx, lineGeometry), true, false, 1);
	orc_metaField_class(&pNext, "transparentObj3ds", ((Vtable_Object*)Vtable_Orc$PointerArray_init(0)), offsetof(Sgl$DrawCtx, transparentObj3ds), true, false, 1);

	orc_metaField_method(&pNext, "addTransparentObj3dIfIsTransparent", offsetof(Sgl$DrawCtx, addTransparentObj3dIfIsTransparent));
	orc_metaField_method(&pNext, "collectLights", offsetof(Sgl$DrawCtx, collectLights));
	orc_metaField_method(&pNext, "_collectLight", offsetof(Sgl$DrawCtx, _collectLight));
	orc_metaField_method(&pNext, "tick", offsetof(Sgl$DrawCtx, tick));
	orc_metaField_method(&pNext, "tickObj3d", offsetof(Sgl$DrawCtx, tickObj3d));
	orc_metaField_method(&pNext, "drawDepth", offsetof(Sgl$DrawCtx, drawDepth));
	orc_metaField_method(&pNext, "_drawNodeDepth", offsetof(Sgl$DrawCtx, _drawNodeDepth));
	orc_metaField_method(&pNext, "updateViewport", offsetof(Sgl$DrawCtx, updateViewport));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$DrawCtx, draw));
	orc_metaField_method(&pNext, "drawTransparentObj3ds", offsetof(Sgl$DrawCtx, drawTransparentObj3ds));
	orc_metaField_method(&pNext, "setMvpToMaterial", offsetof(Sgl$DrawCtx, setMvpToMaterial));
	orc_metaField_method(&pNext, "setGlobalInfosToMaterial", offsetof(Sgl$DrawCtx, setGlobalInfosToMaterial));
	orc_metaField_method(&pNext, "setLightsToMaterial", offsetof(Sgl$DrawCtx, setLightsToMaterial));
}


// vtable init


Vtable_Sgl$DrawCtx* Vtable_Sgl$DrawCtx_init(Vtable_Sgl$DrawCtx* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$DrawCtx;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$DrawCtx_new;
    ((Vtable_Object*)pvt)->className = "Sgl$DrawCtx";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$DrawCtx_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$DrawCtx_fini(Sgl$DrawCtx *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$DrawCtx_init_fields(Sgl$DrawCtx *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$DrawCtx_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DrawCtx*)self)->lights, Orc$List_new(&tmpNewOwner_1) );
	((Sgl$DrawCtx*)self)->frameSize = SuiCore$mkVec2(500, 500) ;
	((Sgl$DrawCtx*)self)->prevTickMs = 0;
	((Sgl$DrawCtx*)self)->dtMs = 0;
	((Sgl$DrawCtx*)self)->dtSec = 0.0;
	((Sgl$DrawCtx*)self)->passSec = 0.0;
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DrawCtx*)self)->depthMatl, Sgl$Material_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DrawCtx*)self)->lineMatl, Sgl$Material_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DrawCtx*)self)->lineGeometry, Sgl$GeometryLine_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS Orc$PointerArray*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DrawCtx*)self)->transparentObj3ds, Orc$PointerArray_new(&tmpNewOwner_5) );
	urgc_set_field(self, (void**)&((Sgl$DrawCtx*)self)->cbAfterDraw, NULL);
    }
	((Object*)self)->ctor = (void*)Sgl$DrawCtx$ctor;
	((Sgl$DrawCtx*)self)->addTransparentObj3dIfIsTransparent = (void*)Sgl$DrawCtx$addTransparentObj3dIfIsTransparent;
	((Sgl$DrawCtx*)self)->collectLights = (void*)Sgl$DrawCtx$collectLights;
	((Sgl$DrawCtx*)self)->_collectLight = (void*)Sgl$DrawCtx$_collectLight;
	((Sgl$DrawCtx*)self)->tick = (void*)Sgl$DrawCtx$tick;
	((Sgl$DrawCtx*)self)->tickObj3d = (void*)Sgl$DrawCtx$tickObj3d;
	((Sgl$DrawCtx*)self)->drawDepth = (void*)Sgl$DrawCtx$drawDepth;
	((Sgl$DrawCtx*)self)->_drawNodeDepth = (void*)Sgl$DrawCtx$_drawNodeDepth;
	((Sgl$DrawCtx*)self)->updateViewport = (void*)Sgl$DrawCtx$updateViewport;
	((Sgl$DrawCtx*)self)->draw = (void*)Sgl$DrawCtx$draw;
	((Sgl$DrawCtx*)self)->drawTransparentObj3ds = (void*)Sgl$DrawCtx$drawTransparentObj3ds;
	((Sgl$DrawCtx*)self)->setMvpToMaterial = (void*)Sgl$DrawCtx$setMvpToMaterial;
	((Sgl$DrawCtx*)self)->setGlobalInfosToMaterial = (void*)Sgl$DrawCtx$setGlobalInfosToMaterial;
	((Sgl$DrawCtx*)self)->setLightsToMaterial = (void*)Sgl$DrawCtx$setLightsToMaterial;
}

// init function

void Sgl$DrawCtx_init(Sgl$DrawCtx *self, void *pOwner){
    Vtable_Sgl$DrawCtx_init(&_vtable_Sgl$DrawCtx);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$DrawCtx;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$DrawCtx_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$DrawCtx * Sgl$DrawCtx_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$DrawCtx *self = calloc(1, sizeof(Sgl$DrawCtx));
	
    Sgl$DrawCtx_init(self, pOwner);
    return self;
}


// class members
void  Sgl$DrawCtx$ctor(Sgl$DrawCtx *  self){
	self->depthMatl->load(self->depthMatl, "../asset/depth.matl.json") ;
	self->lineMatl->load(self->lineMatl, "../asset/line.matl.json") ;
}


bool  Sgl$DrawCtx$addTransparentObj3dIfIsTransparent(Sgl$DrawCtx *  self, Sgl$Obj3d *  obj3d, Sgl$Material *  matl){
	if (matl && matl->transparent) {
		self->transparentObj3ds->add(self->transparentObj3ds, obj3d) ;
		return true; 
	}
	return false; 
}


void  Sgl$DrawCtx$collectLights(Sgl$DrawCtx *  self){
	if (!self->scene) {
		return ; 
	}
	self->lights->clear(self->lights) ;
	SuiCore$Node$walk((SuiCore$Node * )self->scene, self->_collectLight, self) ;
}


void  Sgl$DrawCtx$_collectLight(Sgl$DrawCtx *  self, SuiCore$Node *  n){
	if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Light_init(NULL))) {
		self->lights->add(self->lights, (Sgl$Light * )n) ;
	}
}


void  Sgl$DrawCtx$tick(Sgl$DrawCtx *  self, Sgl$Scene *  scene){
	long long  nowMs = Orc$Time_unixMs() ;
	self->dtMs = 0;
	self->dtSec = 0;
	if (self->prevTickMs > 0) {
		self->dtMs = nowMs - self->prevTickMs;
		self->dtSec = self->dtMs / 1000.0;
	}
	self->passSec += self->dtSec;
	self->prevTickMs = nowMs;
	SuiCore$Node$walkIf((SuiCore$Node * )scene, self->tickObj3d, self) ;
}


bool  Sgl$DrawCtx$tickObj3d(Sgl$DrawCtx *  self, SuiCore$Node *  n){
	if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		Sgl$Obj3d *  obj3d = (Sgl$Obj3d * )n;
		if (!obj3d->visible) {
			return false; 
		}
		obj3d->tick(obj3d, self) ;
		return true; 
	}
	return false; 
}


void  Sgl$DrawCtx$drawDepth(Sgl$DrawCtx *  self, Sgl$Scene *  scene, Sgl$Camera *  camera){
	if (scene) {
		self->scene = scene;
		self->camera = camera;
		self->tick(self, scene) ;
		self->collectLights(self) ;
		glViewport((int )(self->camera->viewport.x * self->frameSize.x), (int )(self->camera->viewport.y * self->frameSize.y), (int )(self->camera->viewport.w * self->frameSize.x), (int )(self->camera->viewport.h * self->frameSize.y)) ;
		((Sgl$Obj3d * )scene)->updateWorldTransformAndSubtree(scene) ;
		self->camera->updateProjectionMat(self->camera) ;
		self->camera->updateViewMat(self->camera) ;
		self->depthMatl->view = camera->view;
		self->depthMatl->projection = camera->projection;
		SuiCore$Node$walk((SuiCore$Node * )scene, self->_drawNodeDepth, self) ;
	}
}


void  Sgl$DrawCtx$_drawNodeDepth(Sgl$DrawCtx *  self, SuiCore$Node *  n){
	if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		Sgl$Obj3d *  o3d = (Sgl$Obj3d * )n;
		self->depthMatl->model = o3d->_world_transform;
		o3d->drawDepth(o3d, self) ;
	}
}


void  Sgl$DrawCtx$updateViewport(Sgl$DrawCtx *  self){
	glViewport((int )(self->camera->viewport.x * self->frameSize.x), (int )(self->camera->viewport.y * self->frameSize.y), (int )(self->camera->viewport.w * self->frameSize.x), (int )(self->camera->viewport.h * self->frameSize.y)) ;
}


void  Sgl$DrawCtx$draw(Sgl$DrawCtx *  self, Sgl$Scene *  scene, Sgl$Camera *  camera){
	if (!scene) {
		printf("DrawCtx fail. no scene\n") ;
		return ; 
	}
	self->scene = scene;
	if (camera) {
		self->camera = camera;
	}
	if (!self->camera) {
		self->camera = SuiCore$Node$findNodeByClass((SuiCore$Node * )scene, Vtable_Sgl$Camera_init(NULL)) ;
		if (!self->camera) {
			printf("DrawCtx fail. no camera\n") ;
			return ; 
		}
	}
	self->transparentObj3ds->clear(self->transparentObj3ds) ;
	self->tick(self, scene) ;
	self->collectLights(self) ;
	self->updateViewport(self) ;
	((Sgl$Obj3d * )scene)->updateWorldTransformAndSubtree(scene) ;
	self->camera->updateProjectionMat(self->camera) ;
	self->camera->updateViewMat(self->camera) ;
	self->lineGeometry->clear(self->lineGeometry) ;
	{
		{
			Sgl$GeometryLine*  o = self->lineGeometry;
			
		
			o->color = 0xffff0000;
			o->moveTo(o, -100000, 0, 0) ;
			o->lineTo(o, 100000, 0, 0) ;
			o->color = 0xff00ff00;
			o->moveTo(o, 0, -100000, 0) ;
			o->lineTo(o, 0, 100000, 0) ;
			o->color = 0xff0000ff;
			o->moveTo(o, 0, 0, -100000) ;
			o->lineTo(o, 0, 0, 100000) ;
		}
	}
	((Sgl$Obj3d * )scene)->draw(scene, self) ;
	self->drawTransparentObj3ds(self) ;
	if (self->cbAfterDraw) {
		(*(self->cbAfterDraw))((void * )(self->cbAfterDraw)) ;
	}
	self->setMvpToMaterial(self, NULL, self->lineMatl) ;
	self->lineGeometry->draw(self->lineGeometry, self->lineMatl) ;
}


void  Sgl$DrawCtx$drawTransparentObj3ds(Sgl$DrawCtx *  self){
	int  size = self->transparentObj3ds->size(self->transparentObj3ds) ;
	if (size <= 0) {
		return ; 
	}
	Sgl$Mat view = self->camera->view;
	for (int  i = 0; i < size; i++) {
		Sgl$Obj3d *  obj3d = self->transparentObj3ds->get(self->transparentObj3ds, i) ;
		if (obj3d) {
			SuiCore$Vec3 worldPos = obj3d->localToWorld(obj3d, SuiCore$mkVec3(0, 0, 0) ) ;
			obj3d->_viewPosition = Sgl$Mat$mulVec3(&view, worldPos) ;
		}
	}
	qsort(self->transparentObj3ds->data, size, Orc$pointerSize() , cmpObj3dDepth) ;
	for (int  i = 0; i < size; i++) {
		Sgl$Obj3d *  obj3d = self->transparentObj3ds->get(self->transparentObj3ds, i) ;
		if (obj3d) {
			obj3d->drawTransparent(obj3d, self) ;
		}
	}
}


void  Sgl$DrawCtx$setMvpToMaterial(Sgl$DrawCtx *  self, Sgl$Obj3d *  obj3d, Sgl$Material *  material){
	material->setMvp(material, obj3d ? obj3d->_world_transform : Sgl$mkMatIdentity() , self->camera->view, self->camera->projection) ;
}


void  Sgl$DrawCtx$setGlobalInfosToMaterial(Sgl$DrawCtx *  self, Sgl$Material *  matl){
	matl->setUniform4f(matl, "time", self->passSec, self->dtSec, 0, 0) ;
	self->setLightsToMaterial(self, matl) ;
}


void  Sgl$DrawCtx$setLightsToMaterial(Sgl$DrawCtx *  self, Sgl$Material *  matl){
	for (int  i = 0; i < self->lights->size(self->lights) ; i++) {
		Sgl$Light *  light = (Sgl$Light * )self->lights->get(self->lights, i) ;
		if (Orc_instanceof((Object*)light, (Vtable_Object*)Vtable_Sgl$PointLight_init(NULL))) {
			Sgl$PointLight *  pl = (Sgl$PointLight * )light;
			SuiCore$Rgbaf c = SuiCore$mkRgbafByInt(pl->color) ;
			SuiCore$Vec3 pos = ((Sgl$Obj3d * )light)->localToWorld(light, SuiCore$mkVec3(0, 0, 0) ) ;
			matl->setUniform3f(matl, "pointLight.position", pos.x, pos.y, pos.z) ;
			matl->setUniform3f(matl, "pointLight.color", c.r, c.g, c.b) ;
			matl->setUniform1f(matl, "pointLight.intensity", pl->intensity) ;
			matl->setUniform1f(matl, "pointLight.distance", pl->distance) ;
			matl->setUniform1f(matl, "pointLight.decay", pl->decay) ;
		}
		else if (Orc_instanceof((Object*)light, (Vtable_Object*)Vtable_Sgl$DirLight_init(NULL))) {
			Sgl$DirLight *  pl = (Sgl$DirLight * )light;
			SuiCore$Rgbaf ambient = SuiCore$mkRgbafByInt(pl->ambient) ;
			SuiCore$Rgbaf diffuse = SuiCore$mkRgbafByInt(pl->diffuse) ;
			SuiCore$Rgbaf specular = SuiCore$mkRgbafByInt(pl->specular) ;
			SuiCore$Vec3 pos = ((Sgl$Obj3d * )light)->localToWorld(light, SuiCore$mkVec3(0, 0, 0) ) ;
			pos = SuiCore$Vec3$scale(&pos, -1) ;
			pos = SuiCore$Vec3$normal(&pos) ;
			matl->setUniformVec3(matl, "dirLight.direction", pos) ;
			matl->setUniform3f(matl, "dirLight.ambient", ambient.r, ambient.g, ambient.b) ;
			matl->setUniform3f(matl, "dirLight.diffuse", diffuse.r, diffuse.g, diffuse.b) ;
			matl->setUniform3f(matl, "dirLight.specular", specular.r, specular.g, specular.b) ;
		}
	}
}



static int  cmpObj3dDepth(const void *  a, const void *  b){
	Sgl$Obj3d *  aobj = a;
	Sgl$Obj3d *  bobj = b;
	float  dz = aobj->_viewPosition.z - bobj->_viewPosition.z;
	return dz <= 0 ? -1 : 0; 
}



