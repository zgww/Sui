
#include "Obj3d_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Orc/String_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Euler_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/Quaternion_orc.h"
#include "./Mat_orc.h"
#include "./Ray_orc.h"
#include "./DrawCtx_orc.h"
#include "./Raycaster_orc.h"
#include "./Material_orc.h"
#include "./Vao_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Obj3d _vtable_Sgl$Obj3d;

// init meta

void Sgl$Obj3d_initMeta(Vtable_Sgl$Obj3d *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "objid", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Obj3d, objid), true, false, 1);
	orc_metaField_struct(&pNext, "position", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, position), false, false, 0);
	orc_metaField_struct(&pNext, "rotation", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, rotation), false, false, 0);
	orc_metaField_struct(&pNext, "scale", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, scale), false, false, 0);
	orc_metaField_struct(&pNext, "rgba", SuiCore$Rgba_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, rgba), false, false, 0);
	orc_metaField_primitive(&pNext, "textColor", OrcMetaType_int, offsetof(Sgl$Obj3d, textColor), 0, 0, 0, 0);//int
	orc_metaField_struct(&pNext, "quaternion", SuiCore$Quaternion_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, quaternion), false, false, 0);
	orc_metaField_struct(&pNext, "_viewPosition", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, _viewPosition), false, false, 0);
	orc_metaField_struct(&pNext, "up", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, up), false, false, 0);
	orc_metaField_struct(&pNext, "transform", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, transform), false, false, 0);
	orc_metaField_struct(&pNext, "_world_transform", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Obj3d, _world_transform), false, false, 0);
	orc_metaField_primitive(&pNext, "visible", OrcMetaType_bool, offsetof(Sgl$Obj3d, visible), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "gocId", offsetof(Sgl$Obj3d, gocId));
	orc_metaField_method(&pNext, "worldToLocal", offsetof(Sgl$Obj3d, worldToLocal));
	orc_metaField_method(&pNext, "localToWorld", offsetof(Sgl$Obj3d, localToWorld));
	orc_metaField_method(&pNext, "updateTransform", offsetof(Sgl$Obj3d, updateTransform));
	orc_metaField_method(&pNext, "updateWorldTransformAndSubtree", offsetof(Sgl$Obj3d, updateWorldTransformAndSubtree));
	orc_metaField_method(&pNext, "updateChildrenWorldTransform", offsetof(Sgl$Obj3d, updateChildrenWorldTransform));
	orc_metaField_method(&pNext, "drawDepth", offsetof(Sgl$Obj3d, drawDepth));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$Obj3d, draw));
	orc_metaField_method(&pNext, "drawTransparent", offsetof(Sgl$Obj3d, drawTransparent));
	orc_metaField_method(&pNext, "drawSelfRaw", offsetof(Sgl$Obj3d, drawSelfRaw));
	orc_metaField_method(&pNext, "drawSelf", offsetof(Sgl$Obj3d, drawSelf));
	orc_metaField_method(&pNext, "drawChildren", offsetof(Sgl$Obj3d, drawChildren));
	orc_metaField_method(&pNext, "tick", offsetof(Sgl$Obj3d, tick));
	orc_metaField_method(&pNext, "hitTestSelfByRaycaster", offsetof(Sgl$Obj3d, hitTestSelfByRaycaster));
	orc_metaField_method(&pNext, "lookAt", offsetof(Sgl$Obj3d, lookAt));
}


// vtable init


Vtable_Sgl$Obj3d* Vtable_Sgl$Obj3d_init(Vtable_Sgl$Obj3d* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Obj3d;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Node_init(&_vtable_SuiCore$Node);

	// init by super vtable init function
    Vtable_SuiCore$Node_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Node;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Obj3d_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Obj3d";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Obj3d_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Obj3d_fini(Sgl$Obj3d *self){
	//super fini
    SuiCore$Node_fini((SuiCore$Node *)self);

    //字段释放


}

// init fields function


void Sgl$Obj3d_init_fields(Sgl$Obj3d *self){
	//super class
    SuiCore$Node_init_fields((SuiCore$Node*)self);

    ((Object*)self)->fini = (void*)Sgl$Obj3d_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Obj3d*)self)->objid, NULL);
	((Sgl$Obj3d*)self)->scale = SuiCore$mkVec3(1.0, 1.0, 1) ;
	((Sgl$Obj3d*)self)->rgba = SuiCore$mkRgbaByInt(0xffff0000) ;
	((Sgl$Obj3d*)self)->textColor = 0xff00ff00;
	((Sgl$Obj3d*)self)->up = SuiCore$mkVec3(0, 1, 0) ;
	((Sgl$Obj3d*)self)->transform = Sgl$mkMatIdentity() ;
	((Sgl$Obj3d*)self)->_world_transform = Sgl$mkMatIdentity() ;
	((Sgl$Obj3d*)self)->visible = true;
    }
	((Sgl$Obj3d*)self)->gocId = (void*)Sgl$Obj3d$gocId;
	((Sgl$Obj3d*)self)->worldToLocal = (void*)Sgl$Obj3d$worldToLocal;
	((Sgl$Obj3d*)self)->localToWorld = (void*)Sgl$Obj3d$localToWorld;
	((Sgl$Obj3d*)self)->updateTransform = (void*)Sgl$Obj3d$updateTransform;
	((Sgl$Obj3d*)self)->updateWorldTransformAndSubtree = (void*)Sgl$Obj3d$updateWorldTransformAndSubtree;
	((Sgl$Obj3d*)self)->updateChildrenWorldTransform = (void*)Sgl$Obj3d$updateChildrenWorldTransform;
	((Sgl$Obj3d*)self)->drawDepth = (void*)Sgl$Obj3d$drawDepth;
	((Sgl$Obj3d*)self)->draw = (void*)Sgl$Obj3d$draw;
	((Sgl$Obj3d*)self)->drawTransparent = (void*)Sgl$Obj3d$drawTransparent;
	((Sgl$Obj3d*)self)->drawSelfRaw = (void*)Sgl$Obj3d$drawSelfRaw;
	((Sgl$Obj3d*)self)->drawSelf = (void*)Sgl$Obj3d$drawSelf;
	((Sgl$Obj3d*)self)->drawChildren = (void*)Sgl$Obj3d$drawChildren;
	((Sgl$Obj3d*)self)->tick = (void*)Sgl$Obj3d$tick;
	((Sgl$Obj3d*)self)->hitTestSelfByRaycaster = (void*)Sgl$Obj3d$hitTestSelfByRaycaster;
	((Sgl$Obj3d*)self)->lookAt = (void*)Sgl$Obj3d$lookAt;
}

// init function

void Sgl$Obj3d_init(Sgl$Obj3d *self, void *pOwner){
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Obj3d;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Obj3d_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Obj3d * Sgl$Obj3d_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Obj3d *self = calloc(1, sizeof(Sgl$Obj3d));
	
    Sgl$Obj3d_init(self, pOwner);
    return self;
}


// class members
Orc$String*  Sgl$Obj3d$gocId(Orc$String **  __outRef__, Sgl$Obj3d *  self){
	if (!self->objid) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Obj3d, objid) , Orc$str(&tmpReturn_1, "") ) ;
		Orc$String$addll(self->objid, (long long )self) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, self->objid) ; 
}


SuiCore$Vec3 Sgl$Obj3d$worldToLocal(Sgl$Obj3d *  self, SuiCore$Vec3 v3){
	SuiCore$Vec4 v4 = SuiCore$mkVec4(v3.x, v3.y, v3.z, 1.0) ;
	Sgl$Mat inv = Sgl$Mat$invert(&self->_world_transform) ;
	SuiCore$Vec4 ret = Sgl$Mat$mulVec4(&inv, v4) ;
	return SuiCore$mkVec3(ret.x, ret.y, ret.z) ; 
}


SuiCore$Vec3 Sgl$Obj3d$localToWorld(Sgl$Obj3d *  self, SuiCore$Vec3 v3){
	SuiCore$Vec4 v4 = SuiCore$mkVec4(v3.x, v3.y, v3.z, 1.0) ;
	SuiCore$Vec4 ret = Sgl$Mat$mulVec4(&self->_world_transform, v4) ;
	return SuiCore$mkVec3(ret.x, ret.y, ret.z) ; 
}


void  Sgl$Obj3d$updateTransform(Sgl$Obj3d *  self){
	SuiCore$Quaternion q;
	SuiCore$Euler e;
	SuiCore$Euler$set(&e, self->rotation.x, self->rotation.y, self->rotation.z, NULL) ;
	SuiCore$Quaternion$setFromEuler(&q, e) ;
	Sgl$Mat$compose(&self->transform, self->position, q, self->scale) ;
}


void  Sgl$Obj3d$updateWorldTransformAndSubtree(Sgl$Obj3d *  self){
	self->updateTransform(self) ;
	if (((SuiCore$Node * )self)->parent && Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		Sgl$Obj3d *  p = (Sgl$Obj3d * )((SuiCore$Node * )self)->parent;
		Sgl$Mat$mul(&self->_world_transform, &p->_world_transform, &self->transform) ;
	}
	else {
		self->_world_transform = self->transform;
	}
	self->updateChildrenWorldTransform(self) ;
}


void  Sgl$Obj3d$updateChildrenWorldTransform(Sgl$Obj3d *  self){
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  view = ((SuiCore$Node * )self)->getChild(self, i) ;
		if (Orc_instanceof((Object*)view, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
			Sgl$Obj3d *  obj = (Sgl$Obj3d * )view;
			if (obj->visible) {
				obj->updateWorldTransformAndSubtree(obj) ;
			}
		}
	}
}


void  Sgl$Obj3d$drawDepth(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx){
	
}


void  Sgl$Obj3d$draw(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx){
	self->drawSelf(self, ctx) ;
	self->drawChildren(self, ctx) ;
}


void  Sgl$Obj3d$drawTransparent(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx){
	self->drawSelf(self, ctx) ;
}


void  Sgl$Obj3d$drawSelfRaw(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx, Sgl$Vao *  vao, Sgl$Material *  matl){
	
}


void  Sgl$Obj3d$drawSelf(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx){
	
}


void  Sgl$Obj3d$drawChildren(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx){
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  view = ((SuiCore$Node * )self)->getChild(self, i) ;
		if (Orc_instanceof((Object*)view, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
			Sgl$Obj3d *  obj = (Sgl$Obj3d * )view;
			if (obj->visible) {
				obj->draw(obj, ctx) ;
			}
		}
	}
}


void  Sgl$Obj3d$tick(Sgl$Obj3d *  self, Sgl$DrawCtx *  ctx){
	
}


bool  Sgl$Obj3d$hitTestSelfByRaycaster(Sgl$Obj3d *  self, Sgl$Raycaster *  raycaster){
	return false; 
}


void  Sgl$Obj3d$lookAt(Sgl$Obj3d *  self, float  x, float  y, float  z){
	Sgl$Obj3d$lookAtByDir(self, false, x, y, z) ;
}



void  Sgl$Obj3d$updateWorldMatrixUptoRoot(Sgl$Obj3d *  self){
	self->updateTransform(self) ;
	Sgl$Obj3d *  parent = (Sgl$Obj3d * )((SuiCore$Node * )self)->parent;
	if (parent != NULL && Orc_instanceof((Object*)parent, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		Sgl$Obj3d$updateWorldMatrixUptoRoot(parent) ;
		Sgl$Mat$multiplyMatricesLocal(&self->_world_transform, parent->_world_transform, self->transform) ;
	}
	else {
		Sgl$Mat$copy(&self->_world_transform, self->transform) ;
	}
}

void  Sgl$Obj3d$lookAtByDir(Sgl$Obj3d *  self, bool  negativeZ, float  x, float  y, float  z){
	Sgl$Obj3d *  parent = (Sgl$Obj3d * )((SuiCore$Node * )self)->parent;
	if (!(Orc_instanceof((Object*)parent, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL)))) {
		return ; 
	}
	SuiCore$Vec3 _target = SuiCore$mkVec3(x, y, z) ;
	SuiCore$Vec3 _position;
	SuiCore$Vec3$setFromMatrixPosition(&_position, self->_world_transform) ;
	Sgl$Mat _m1;
	if (negativeZ) {
		Sgl$Mat$lookAtLocal(&_m1, _position, _target, self->up) ;
	}
	else {
		Sgl$Mat$lookAtLocal(&_m1, _target, _position, self->up) ;
	}
	SuiCore$Quaternion$setFromRotationMatrix(&self->quaternion, _m1) ;
	if (parent) {
		SuiCore$Quaternion _q1;
		Sgl$Mat$extractRotationLocal(&_m1, parent->_world_transform) ;
		SuiCore$Quaternion$setFromRotationMatrix(&_q1, _m1) ;
		SuiCore$Quaternion$premultiplyLocal(&self->quaternion, *SuiCore$Quaternion$invertLocal(&_q1) ) ;
	}
	SuiCore$Euler euler;
	SuiCore$Euler$setFromQuaternion(&euler, self->quaternion, SuiCore$Euler_Default) ;
	SuiCore$Vec3$setFromEuler(&self->rotation, euler) ;
}



