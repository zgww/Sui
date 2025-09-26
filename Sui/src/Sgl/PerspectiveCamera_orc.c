
#include "PerspectiveCamera_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Euler_orc.h"
#include "../Sui/Core/Quaternion_orc.h"
#include "../Orc/Math_orc.h"
#include "./Camera_orc.h"
#include "./Mat_orc.h"
#include "./Ray_orc.h"
#include "./Obj3d_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$PerspectiveCamera _vtable_Sgl$PerspectiveCamera;

// init meta

void Sgl$PerspectiveCamera_initMeta(Vtable_Sgl$PerspectiveCamera *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "fov", OrcMetaType_float, offsetof(Sgl$PerspectiveCamera, fov), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "aspect", OrcMetaType_float, offsetof(Sgl$PerspectiveCamera, aspect), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "nearPlane", OrcMetaType_float, offsetof(Sgl$PerspectiveCamera, nearPlane), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "farPlane", OrcMetaType_float, offsetof(Sgl$PerspectiveCamera, farPlane), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "target", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$PerspectiveCamera, target), false, false, 0);

	orc_metaField_method(&pNext, "moveForward", offsetof(Sgl$PerspectiveCamera, moveForward));
	orc_metaField_method(&pNext, "moveBackward", offsetof(Sgl$PerspectiveCamera, moveBackward));
	orc_metaField_method(&pNext, "rotateLeft", offsetof(Sgl$PerspectiveCamera, rotateLeft));
	orc_metaField_method(&pNext, "rotateRight", offsetof(Sgl$PerspectiveCamera, rotateRight));
	orc_metaField_method(&pNext, "rise", offsetof(Sgl$PerspectiveCamera, rise));
	orc_metaField_method(&pNext, "fall", offsetof(Sgl$PerspectiveCamera, fall));
}


// vtable init


Vtable_Sgl$PerspectiveCamera* Vtable_Sgl$PerspectiveCamera_init(Vtable_Sgl$PerspectiveCamera* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$PerspectiveCamera;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Camera_init(&_vtable_Sgl$Camera);

	// init by super vtable init function
    Vtable_Sgl$Camera_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Camera;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$PerspectiveCamera_new;
    ((Vtable_Object*)pvt)->className = "Sgl$PerspectiveCamera";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$PerspectiveCamera_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$PerspectiveCamera_fini(Sgl$PerspectiveCamera *self){
	//super fini
    Sgl$Camera_fini((Sgl$Camera *)self);

    //字段释放


}

// init fields function


void Sgl$PerspectiveCamera_init_fields(Sgl$PerspectiveCamera *self){
	//super class
    Sgl$Camera_init_fields((Sgl$Camera*)self);

    ((Object*)self)->fini = (void*)Sgl$PerspectiveCamera_fini;
	//fields
    {
	((Sgl$PerspectiveCamera*)self)->fov = 45 / 180.0 * Orc$PI;
	((Sgl$PerspectiveCamera*)self)->aspect = 1.0;
	((Sgl$PerspectiveCamera*)self)->nearPlane = 300.1;
	((Sgl$PerspectiveCamera*)self)->farPlane = 500;
	((Sgl$PerspectiveCamera*)self)->target = SuiCore$mkVec3(0, 0, 0) ;
    }
	((Sgl$Camera*)self)->updateProjectionMat = (void*)Sgl$PerspectiveCamera$updateProjectionMat;
	((Sgl$Camera*)self)->updateViewMat = (void*)Sgl$PerspectiveCamera$updateViewMat;
	((Sgl$PerspectiveCamera*)self)->moveForward = (void*)Sgl$PerspectiveCamera$moveForward;
	((Sgl$PerspectiveCamera*)self)->moveBackward = (void*)Sgl$PerspectiveCamera$moveBackward;
	((Sgl$PerspectiveCamera*)self)->rotateLeft = (void*)Sgl$PerspectiveCamera$rotateLeft;
	((Sgl$PerspectiveCamera*)self)->rotateRight = (void*)Sgl$PerspectiveCamera$rotateRight;
	((Sgl$PerspectiveCamera*)self)->rise = (void*)Sgl$PerspectiveCamera$rise;
	((Sgl$PerspectiveCamera*)self)->fall = (void*)Sgl$PerspectiveCamera$fall;
	((Sgl$Camera*)self)->mkRay = (void*)Sgl$PerspectiveCamera$mkRay;
}

// init function

void Sgl$PerspectiveCamera_init(Sgl$PerspectiveCamera *self, void *pOwner){
    Vtable_Sgl$PerspectiveCamera_init(&_vtable_Sgl$PerspectiveCamera);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$PerspectiveCamera;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$PerspectiveCamera_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$PerspectiveCamera * Sgl$PerspectiveCamera_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$PerspectiveCamera *self = calloc(1, sizeof(Sgl$PerspectiveCamera));
	
    Sgl$PerspectiveCamera_init(self, pOwner);
    return self;
}


// class members
void  Sgl$PerspectiveCamera$updateProjectionMat(Sgl$PerspectiveCamera *  self){
	Sgl$Mat$perspective(&((Sgl$Camera * )self)->projection, self->fov, self->aspect, self->nearPlane, self->farPlane) ;
}


void  Sgl$PerspectiveCamera$updateViewMat(Sgl$PerspectiveCamera *  self){
	Sgl$Obj3d$updateWorldMatrixUptoRoot((Sgl$Obj3d * )self) ;
	Sgl$Mat$invertLocal(Sgl$Mat$copy(&((Sgl$Camera * )self)->view, ((Sgl$Obj3d * )self)->_world_transform) ) ;
}


void  Sgl$PerspectiveCamera$moveForward(Sgl$PerspectiveCamera *  self){
	float  step = 10;
	SuiCore$Vec3 worldPos = ((Sgl$Obj3d * )self)->localToWorld(self, SuiCore$mkVec3(0, 0, 0) ) ;
	SuiCore$Vec3 viewDir = SuiCore$Vec3$sub(&self->target, worldPos) ;
	viewDir = SuiCore$Vec3$normal(&viewDir) ;
	viewDir = SuiCore$Vec3$scale(&viewDir, step) ;
	SuiCore$Vec3 newWorldPos = SuiCore$Vec3$add(&worldPos, viewDir) ;
	((Sgl$Obj3d * )self)->position = newWorldPos;
	self->target = SuiCore$Vec3$add(&self->target, viewDir) ;
}


void  Sgl$PerspectiveCamera$moveBackward(Sgl$PerspectiveCamera *  self){
	float  step = 10;
	SuiCore$Vec3 worldPos = ((Sgl$Obj3d * )self)->localToWorld(self, SuiCore$mkVec3(0, 0, 0) ) ;
	SuiCore$Vec3 viewDir = SuiCore$Vec3$sub(&self->target, worldPos) ;
	viewDir = SuiCore$Vec3$normal(&viewDir) ;
	viewDir = SuiCore$Vec3$scale(&viewDir, -1 * step) ;
	SuiCore$Vec3 newWorldPos = SuiCore$Vec3$add(&worldPos, viewDir) ;
	((Sgl$Obj3d * )self)->position = newWorldPos;
	self->target = SuiCore$Vec3$add(&self->target, viewDir) ;
}


void  Sgl$PerspectiveCamera$rotateLeft(Sgl$PerspectiveCamera *  self){
	((Sgl$Obj3d * )self)->_world_transform = Sgl$Mat$invert(&((Sgl$Camera * )self)->view) ;
	SuiCore$Vec3 localTarget = ((Sgl$Obj3d * )self)->worldToLocal(self, self->target) ;
	Sgl$Mat rot;
	Sgl$Mat$identity(&rot) ;
	Sgl$Mat$rotateY(&rot, 1.1 / 180.0 * Orc$PI) ;
	SuiCore$Vec3 newLocalTarget = Sgl$Mat$mulVec3(&rot, localTarget) ;
	SuiCore$Vec3 newTarget = ((Sgl$Obj3d * )self)->localToWorld(self, newLocalTarget) ;
	self->target = newTarget;
}


void  Sgl$PerspectiveCamera$rotateRight(Sgl$PerspectiveCamera *  self){
	((Sgl$Obj3d * )self)->_world_transform = Sgl$Mat$invert(&((Sgl$Camera * )self)->view) ;
	SuiCore$Vec3 localTarget = ((Sgl$Obj3d * )self)->worldToLocal(self, self->target) ;
	Sgl$Mat rot;
	Sgl$Mat$identity(&rot) ;
	Sgl$Mat$rotateY(&rot, -1.1 / 180.0 * Orc$PI) ;
	SuiCore$Vec3 newLocalTarget = Sgl$Mat$mulVec3(&rot, localTarget) ;
	SuiCore$Vec3 newTarget = ((Sgl$Obj3d * )self)->localToWorld(self, newLocalTarget) ;
	self->target = newTarget;
}


void  Sgl$PerspectiveCamera$rise(Sgl$PerspectiveCamera *  self){
	((Sgl$Obj3d * )self)->position.y += 10;
}


void  Sgl$PerspectiveCamera$fall(Sgl$PerspectiveCamera *  self){
	((Sgl$Obj3d * )self)->position.y -= 10;
}


Sgl$Ray Sgl$PerspectiveCamera$mkRay(Sgl$PerspectiveCamera *  self, SuiCore$Vec2 ndcPos){
	Sgl$Ray r;
	SuiCore$Vec3$setFromMatrixPosition(&r.origin, ((Sgl$Obj3d * )self)->_world_transform) ;
	SuiCore$Vec3 wp = ((Sgl$Camera * )self)->unproject(self, SuiCore$mkVec3(ndcPos.x, ndcPos.y, 0.5) ) ;
	SuiCore$Vec3 dir = SuiCore$Vec3$sub(&wp, r.origin) ;
	r.direction = SuiCore$Vec3$normal(&dir) ;
	return r; 
}





