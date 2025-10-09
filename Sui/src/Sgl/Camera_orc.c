
#include "Camera_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "./Mat_orc.h"
#include "./Ray_orc.h"
#include "./Obj3d_orc.h"
#include "./Scene_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Camera _vtable_Sgl$Camera;

// init meta

void Sgl$Camera_initMeta(Vtable_Sgl$Camera *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "viewport", SuiCore$Rect_getOrInitMetaStruct(), offsetof(Sgl$Camera, viewport), false, false, 0);
	orc_metaField_struct(&pNext, "view", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Camera, view), false, false, 0);
	orc_metaField_struct(&pNext, "projection", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Camera, projection), false, false, 0);

	orc_metaField_method(&pNext, "calcVp", offsetof(Sgl$Camera, calcVp));
	orc_metaField_method(&pNext, "updateProjectionMat", offsetof(Sgl$Camera, updateProjectionMat));
	orc_metaField_method(&pNext, "updateViewMat", offsetof(Sgl$Camera, updateViewMat));
	orc_metaField_method(&pNext, "updateMat", offsetof(Sgl$Camera, updateMat));
	orc_metaField_method(&pNext, "mkRay", offsetof(Sgl$Camera, mkRay));
	orc_metaField_method(&pNext, "project", offsetof(Sgl$Camera, project));
	orc_metaField_method(&pNext, "unproject", offsetof(Sgl$Camera, unproject));
	orc_metaField_method(&pNext, "unprojectToView", offsetof(Sgl$Camera, unprojectToView));
}


// vtable init


Vtable_Sgl$Camera* Vtable_Sgl$Camera_init(Vtable_Sgl$Camera* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Camera;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Camera_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Camera";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Camera_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Camera_fini(Sgl$Camera *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	

}

// init fields function


void Sgl$Camera_init_fields(Sgl$Camera *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Camera_fini;
	//fields
    {
	((Sgl$Camera*)self)->viewport = SuiCore$mkRect(0, 0, 1, 1) ;
    }
	((SuiCore$Node*)self)->onMounted = (void*)Sgl$Camera$onMounted;
	((Sgl$Camera*)self)->calcVp = (void*)Sgl$Camera$calcVp;
	((Sgl$Camera*)self)->updateProjectionMat = (void*)Sgl$Camera$updateProjectionMat;
	((Sgl$Camera*)self)->updateViewMat = (void*)Sgl$Camera$updateViewMat;
	((Sgl$Camera*)self)->updateMat = (void*)Sgl$Camera$updateMat;
	((Sgl$Camera*)self)->mkRay = (void*)Sgl$Camera$mkRay;
	((Sgl$Camera*)self)->project = (void*)Sgl$Camera$project;
	((Sgl$Camera*)self)->unproject = (void*)Sgl$Camera$unproject;
	((Sgl$Camera*)self)->unprojectToView = (void*)Sgl$Camera$unprojectToView;
	((Sgl$Obj3d*)self)->lookAt = (void*)Sgl$Camera$lookAt;
}

// init function

void Sgl$Camera_init(Sgl$Camera *self, void *pOwner){
    Vtable_Sgl$Camera_init(&_vtable_Sgl$Camera);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Camera;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Camera_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Camera * Sgl$Camera_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Camera *self = calloc(1, sizeof(Sgl$Camera));
	
    Sgl$Camera_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Camera$onMounted(Sgl$Camera *  self){
	Sgl$sceneGlobal.cameraDirty = true;
}


Sgl$Mat Sgl$Camera$calcVp(Sgl$Camera *  self){
	Sgl$Mat vp;
	Sgl$Mat$mul(&vp, &self->projection, &self->view) ;
	SuiCore$Vec3 v0 = Sgl$Mat$mulVec3(&self->view, SuiCore$mkVec3(0, 0, 0) ) ;
	SuiCore$Vec3 v = Sgl$Mat$mulVec3(&vp, SuiCore$mkVec3(0, 0, 0) ) ;
	return vp; 
}


void  Sgl$Camera$updateProjectionMat(Sgl$Camera *  self){
	
}


void  Sgl$Camera$updateViewMat(Sgl$Camera *  self){
	
}


void  Sgl$Camera$updateMat(Sgl$Camera *  self){
	self->updateProjectionMat(self) ;
	self->updateViewMat(self) ;
}


Sgl$Ray Sgl$Camera$mkRay(Sgl$Camera *  self, SuiCore$Vec2 ndcPos){
	Sgl$Ray r;
	memset(&r, 0, sizeof(Sgl$Ray) ) ;
	return r; 
}


SuiCore$Vec3 Sgl$Camera$project(Sgl$Camera *  self, SuiCore$Vec3 worldPos){
	SuiCore$Vec3$applyMatrix4Local(SuiCore$Vec3$applyMatrix4Local(&worldPos, self->view) , self->projection) ;
	return worldPos; 
}


SuiCore$Vec3 Sgl$Camera$unproject(Sgl$Camera *  self, SuiCore$Vec3 ndcPos){
	Sgl$Mat projectionInverse = self->projection;
	Sgl$Mat$invertLocal(&projectionInverse) ;
	SuiCore$Vec3$applyMatrix4Local(&ndcPos, projectionInverse) ;
	SuiCore$Vec3$applyMatrix4Local(&ndcPos, ((Sgl$Obj3d * )self)->_world_transform) ;
	return ndcPos; 
}


SuiCore$Vec3 Sgl$Camera$unprojectToView(Sgl$Camera *  self, SuiCore$Vec3 ndcPos){
	Sgl$Mat projectionInverse = self->projection;
	Sgl$Mat$invertLocal(&projectionInverse) ;
	SuiCore$Vec3$applyMatrix4Local(&ndcPos, projectionInverse) ;
	return ndcPos; 
}


void  Sgl$Camera$lookAt(Sgl$Camera *  self, float  x, float  y, float  z){
	Sgl$Obj3d$lookAtByDir((Sgl$Obj3d * )self, true, x, y, z) ;
}





