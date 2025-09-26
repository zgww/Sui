
#include "Raycaster_orc.h" 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "./Sphere_orc.h"
#include "./Box3_orc.h"
#include "./Mat_orc.h"
#include "./Geometry_orc.h"
#include "./Ray_orc.h"
#include "./Obj3d_orc.h"
#include "./Buffer_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$RayCheckResult_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$RayCheckResult", sizeof( Sgl$RayCheckResult ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "succ", OrcMetaType_bool, offsetof(Sgl$RayCheckResult, succ), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "distance", OrcMetaType_float, offsetof(Sgl$RayCheckResult, distance), 0, 0, 0, 0);//float
		orc_metaField_struct(&pNext, "point", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$RayCheckResult, point), false, false, 0);
		orc_metaField_class(&pNext, "obj", ((Vtable_Object*)Vtable_Sgl$Obj3d_init(0)), offsetof(Sgl$RayCheckResult, obj), false, true, 1);
		orc_metaField_primitive(&pNext, "desc", OrcMetaType_char, offsetof(Sgl$RayCheckResult, desc), 0, 0, 1, 1);//char
    }
	return meta;
}
Sgl$RayCheckResult Sgl$mkRayCheckResultFail(){
	Sgl$RayCheckResult r;
	memset(&r, 0, sizeof(Sgl$RayCheckResult) ) ;
	return r; 
}


//vtable instance
Vtable_Sgl$Raycaster _vtable_Sgl$Raycaster;

// init meta

void Sgl$Raycaster_initMeta(Vtable_Sgl$Raycaster *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "nearDistance", OrcMetaType_float, offsetof(Sgl$Raycaster, nearDistance), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "farDistance", OrcMetaType_float, offsetof(Sgl$Raycaster, farDistance), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "ray", Sgl$Ray_getOrInitMetaStruct(), offsetof(Sgl$Raycaster, ray), false, false, 0);
	orc_metaField_struct(&pNext, "result", Sgl$RayCheckResult_getOrInitMetaStruct(), offsetof(Sgl$Raycaster, result), false, false, 0);

	orc_metaField_method(&pNext, "raycastTree", offsetof(Sgl$Raycaster, raycastTree));
	orc_metaField_method(&pNext, "raycastNode", offsetof(Sgl$Raycaster, raycastNode));
	orc_metaField_method(&pNext, "checkIntersection", offsetof(Sgl$Raycaster, checkIntersection));
	orc_metaField_method(&pNext, "raycastGeometry", offsetof(Sgl$Raycaster, raycastGeometry));
}


// vtable init


Vtable_Sgl$Raycaster* Vtable_Sgl$Raycaster_init(Vtable_Sgl$Raycaster* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Raycaster;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Raycaster_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Raycaster";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Raycaster_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Sgl$Raycaster_fini(Sgl$Raycaster *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Raycaster_init_fields(Sgl$Raycaster *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Raycaster_fini;
	//fields
    {
	((Sgl$Raycaster*)self)->nearDistance = 1;
	((Sgl$Raycaster*)self)->farDistance = 10000;
    }
	((Sgl$Raycaster*)self)->raycastTree = (void*)Sgl$Raycaster$raycastTree;
	((Sgl$Raycaster*)self)->raycastNode = (void*)Sgl$Raycaster$raycastNode;
	((Sgl$Raycaster*)self)->checkIntersection = (void*)Sgl$Raycaster$checkIntersection;
	((Sgl$Raycaster*)self)->raycastGeometry = (void*)Sgl$Raycaster$raycastGeometry;
}

// init function

void Sgl$Raycaster_init(Sgl$Raycaster *self, void *pOwner){
    Vtable_Sgl$Raycaster_init(&_vtable_Sgl$Raycaster);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Raycaster;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Raycaster_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Raycaster * Sgl$Raycaster_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Raycaster *self = calloc(1, sizeof(Sgl$Raycaster));
	
    Sgl$Raycaster_init(self, pOwner);
    return self;
}


// class members
Sgl$RayCheckResult Sgl$Raycaster$raycastTree(Sgl$Raycaster *  self, Sgl$Obj3d *  root){
	self->result = Sgl$mkRayCheckResultFail() ;
	self->raycastNode(self, root) ;
	return self->result; 
}


bool  Sgl$Raycaster$raycastNode(Sgl$Raycaster *  self, SuiCore$Node *  n){
	if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		Sgl$Obj3d *  obj3d = (Sgl$Obj3d * )n;
		if (obj3d->hitTestSelfByRaycaster(obj3d, self) ) {
			return true; 
		}
		for (int  i = 0; i < n->children->size(n->children) ; i++) {
			SuiCore$Node *  kid = (SuiCore$Node * )n->children->get(n->children, i) ;
			if (self->raycastNode(self, kid) ) {
				return true; 
			}
		}
	}
	return false; 
}


Sgl$RayCheckResult Sgl$Raycaster$checkIntersection(Sgl$Raycaster *  self, Sgl$Obj3d *  obj, Sgl$Ray localRay, SuiCore$Vec3 pA, SuiCore$Vec3 pB, SuiCore$Vec3 pC){
	Sgl$IntersectResult intersect;
	intersect = Sgl$Ray$intersectTriangle(&localRay, pA, pB, pC, false) ;
	if (!intersect.succ) {
		return Sgl$mkRayCheckResultFail() ; 
	}
	SuiCore$Vec3 _intersectionPointWorld;
	SuiCore$Vec3$copy(&_intersectionPointWorld, intersect.point) ;
	SuiCore$Vec3$applyMatrix4Local(&_intersectionPointWorld, obj->_world_transform) ;
	float  distance = SuiCore$Vec3$distanceTo(&self->ray.origin, _intersectionPointWorld) ;
	if (distance < self->nearDistance || distance > self->farDistance) {
		return Sgl$mkRayCheckResultFail() ; 
	}
	Sgl$RayCheckResult r;
	memset(&r, 0, sizeof(Sgl$RayCheckResult) ) ;
	r.succ = true;
	r.distance = distance;
	r.point = _intersectionPointWorld;
	r.obj = obj;
	return r; 
}


Sgl$RayCheckResult Sgl$Raycaster$raycastGeometry(Sgl$Raycaster *  self, Sgl$Obj3d *  obj, Sgl$Geometry *  geom){
	if (geom->ibo == NULL) {
		return Sgl$mkRayCheckResultFail() ; 
	}
	Sgl$GeoAttr *  positionAttr = geom->getAttr(geom, "position") ;
	if (positionAttr == NULL) {
		{
			Sgl$RayCheckResult o = Sgl$mkRayCheckResultFail() ;
			
		
			o.desc = "no positionAttr";
			return o; 
		}
	}
	Sgl$Buffer *  buf = positionAttr->vbo->buf;
	if (buf == NULL) {
		{
			Sgl$RayCheckResult o = Sgl$mkRayCheckResultFail() ;
			
		
			o.desc = "no positionAttr.vbo.buf";
			return o; 
		}
	}
	Sgl$Buffer *  idxBuf = geom->ibo->buf;
	if (idxBuf == NULL) {
		{
			Sgl$RayCheckResult o = Sgl$mkRayCheckResultFail() ;
			
		
			o.desc = "no ibo.buf";
			return o; 
		}
	}
	int  indexCount = geom->ibo->calcIndexCount(geom->ibo) ;
	if (indexCount % 3 != 0) {
		Sgl$RayCheckResult r = Sgl$mkRayCheckResultFail() ;
		r.desc = "invalid indexCount";
		return r; 
	}
	int *  indexInts = (int * )idxBuf->data;
	float *  vtxFloats = (int * )buf->data;
	SuiCore$Vec3 a;
	SuiCore$Vec3 b;
	SuiCore$Vec3 c;
	Sgl$Ray localRay = self->ray;
	Sgl$Ray$applyMatrix4Local(&localRay, Sgl$Mat$invert(&obj->_world_transform) ) ;
	for (int  i = 0; i < indexCount; i += 3) {
		int  indexA = indexInts[i];
		int  indexB = indexInts[i + 1];
		int  indexC = indexInts[i + 2];
		SuiCore$Vec3$fromArray(&a, vtxFloats, indexA * 3) ;
		SuiCore$Vec3$fromArray(&b, vtxFloats, indexB * 3) ;
		SuiCore$Vec3$fromArray(&c, vtxFloats, indexC * 3) ;
		Sgl$RayCheckResult r = self->checkIntersection(self, obj, localRay, a, b, c) ;
		if (r.succ) {
			return r; 
		}
	}
	{
		Sgl$RayCheckResult o = Sgl$mkRayCheckResultFail() ;
		
	
		return o; 
	}
}





