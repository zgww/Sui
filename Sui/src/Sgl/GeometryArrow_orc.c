
#include "GeometryArrow_orc.h" 

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryArrow _vtable_Sgl$GeometryArrow;

// init meta

void Sgl$GeometryArrow_initMeta(Vtable_Sgl$GeometryArrow *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "cylinderRadius", OrcMetaType_float, offsetof(Sgl$GeometryArrow, cylinderRadius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "coneRadius", OrcMetaType_float, offsetof(Sgl$GeometryArrow, coneRadius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "cylinderHeight", OrcMetaType_float, offsetof(Sgl$GeometryArrow, cylinderHeight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "coneHeight", OrcMetaType_float, offsetof(Sgl$GeometryArrow, coneHeight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "radialSegments", OrcMetaType_int, offsetof(Sgl$GeometryArrow, radialSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "thetaStart", OrcMetaType_float, offsetof(Sgl$GeometryArrow, thetaStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaLength", OrcMetaType_float, offsetof(Sgl$GeometryArrow, thetaLength), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "vtxBuf", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryArrow, vtxBuf), true, false, 1);
	orc_metaField_class(&pNext, "nmlBuf", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryArrow, nmlBuf), true, false, 1);
	orc_metaField_class(&pNext, "face", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryArrow, face), true, false, 1);

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryArrow, build));
	orc_metaField_method(&pNext, "buildTorso", offsetof(Sgl$GeometryArrow, buildTorso));
	orc_metaField_method(&pNext, "buildCone", offsetof(Sgl$GeometryArrow, buildCone));
}


// vtable init


Vtable_Sgl$GeometryArrow* Vtable_Sgl$GeometryArrow_init(Vtable_Sgl$GeometryArrow* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryArrow;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryArrow_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryArrow";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryArrow_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryArrow_fini(Sgl$GeometryArrow *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$GeometryArrow*)self)->vtxBuf);
	urgc_fini_field_class(self, (void**)&((Sgl$GeometryArrow*)self)->nmlBuf);
	urgc_fini_field_class(self, (void**)&((Sgl$GeometryArrow*)self)->face);

}

// init fields function


void Sgl$GeometryArrow_init_fields(Sgl$GeometryArrow *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryArrow_fini;
	//fields
    {
	((Sgl$GeometryArrow*)self)->cylinderRadius = 10;
	((Sgl$GeometryArrow*)self)->coneRadius = 30;
	((Sgl$GeometryArrow*)self)->cylinderHeight = 50;
	((Sgl$GeometryArrow*)self)->coneHeight = 50;
	((Sgl$GeometryArrow*)self)->radialSegments = 32;
	((Sgl$GeometryArrow*)self)->thetaStart = 0;
	((Sgl$GeometryArrow*)self)->thetaLength = Orc$PI * 2;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryArrow*)self)->vtxBuf, Sgl$Buffer_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryArrow*)self)->nmlBuf, Sgl$Buffer_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryArrow*)self)->face, Sgl$Buffer_new(&tmpNewOwner_3) );
    }
	((Sgl$GeometryArrow*)self)->build = (void*)Sgl$GeometryArrow$build;
	((Sgl$GeometryArrow*)self)->buildTorso = (void*)Sgl$GeometryArrow$buildTorso;
	((Sgl$GeometryArrow*)self)->buildCone = (void*)Sgl$GeometryArrow$buildCone;
}

// init function

void Sgl$GeometryArrow_init(Sgl$GeometryArrow *self, void *pOwner){
    Vtable_Sgl$GeometryArrow_init(&_vtable_Sgl$GeometryArrow);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryArrow;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryArrow_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryArrow * Sgl$GeometryArrow_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryArrow *self = calloc(1, sizeof(Sgl$GeometryArrow));
	
    Sgl$GeometryArrow_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryArrow$build(Sgl$GeometryArrow *  self){
	self->buildTorso(self) ;
	self->buildCone(self) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$GeometryArrow, nmlBuf) , Sgl$Geometry_computeVertexNormals(&tmpReturn_1, self->face, self->vtxBuf) ) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", self->vtxBuf, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", self->nmlBuf, 3) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, self->face) ;
}


void  Sgl$GeometryArrow$buildTorso(Sgl$GeometryArrow *  self){
	float  radius = self->cylinderRadius;
	Sgl$Buffer$appendFloat3(self->vtxBuf, 0, 0, 0) ;
	for (int  x = 0; x <= self->radialSegments; x++) {
		float  u = x / (float )self->radialSegments;
		float  theta = -u * self->thetaLength + self->thetaStart;
		float  sinTheta = sin(theta) ;
		float  cosTheta = cos(theta) ;
		Sgl$Buffer$appendFloat3(self->vtxBuf, radius * cosTheta, 0, radius * sinTheta) ;
		if (x == self->radialSegments) {
			Sgl$Buffer$appendInt3(self->face, 0, 1, x + 1) ;
		}
		else {
			Sgl$Buffer$appendInt3(self->face, 0, x + 2, (x + 1)) ;
		}
	}
	int  start = Sgl$Buffer$floatSize(self->vtxBuf)  / 3;
	for (int  x = 0; x <= self->radialSegments; x++) {
		float  u = x / (float )self->radialSegments;
		float  theta = -u * self->thetaLength + self->thetaStart;
		float  sinTheta = sin(theta) ;
		float  cosTheta = cos(theta) ;
		Sgl$Buffer$appendFloat3(self->vtxBuf, radius * cosTheta, self->cylinderHeight, radius * sinTheta) ;
		int  bottomIdx = x + 1;
		int  a = bottomIdx;
		int  b = bottomIdx + 1;
		int  d = start + x;
		int  c = d + 1;
		if (x == self->radialSegments) {
			b = 1;
			c = start;
		}
		Sgl$Buffer$appendInt3(self->face, a, b, c) ;
		Sgl$Buffer$appendInt3(self->face, a, c, d) ;
	}
}


void  Sgl$GeometryArrow$buildCone(Sgl$GeometryArrow *  self){
	float  radius = self->coneRadius;
	int  start = Sgl$Buffer$floatSize(self->vtxBuf)  / 3;
	Sgl$Buffer$appendFloat3(self->vtxBuf, 0, self->cylinderHeight, 0) ;
	for (int  x = 0; x <= self->radialSegments; x++) {
		float  u = x / (float )self->radialSegments;
		float  theta = -u * self->thetaLength + self->thetaStart;
		float  sinTheta = sin(theta) ;
		float  cosTheta = cos(theta) ;
		Sgl$Buffer$appendFloat3(self->vtxBuf, radius * cosTheta, self->cylinderHeight, radius * sinTheta) ;
		if (x == self->radialSegments) {
			Sgl$Buffer$appendInt3(self->face, start, start + x + 1, start + 1) ;
		}
		else {
			Sgl$Buffer$appendInt3(self->face, start, start + x + 1, start + (x + 2)) ;
		}
	}
	int  topStart = Sgl$Buffer$floatSize(self->vtxBuf)  / 3;
	Sgl$Buffer$appendFloat3(self->vtxBuf, 0, self->cylinderHeight + self->coneHeight, 0) ;
	for (int  x = 0; x <= self->radialSegments; x++) {
		float  u = x / (float )self->radialSegments;
		float  theta = -u * self->thetaLength + self->thetaStart;
		float  sinTheta = sin(theta) ;
		float  cosTheta = cos(theta) ;
		Sgl$Buffer$appendFloat3(self->vtxBuf, radius * cosTheta, self->cylinderHeight, radius * sinTheta) ;
		if (x == self->radialSegments) {
			Sgl$Buffer$appendInt3(self->face, topStart, topStart + x + 1, topStart + 1) ;
		}
		else {
			Sgl$Buffer$appendInt3(self->face, topStart, topStart + x + 1, topStart + (x + 2)) ;
		}
	}
}





