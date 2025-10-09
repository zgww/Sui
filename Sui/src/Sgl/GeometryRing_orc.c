
#include "GeometryRing_orc.h" 

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
Vtable_Sgl$GeometryRing _vtable_Sgl$GeometryRing;

// init meta

void Sgl$GeometryRing_initMeta(Vtable_Sgl$GeometryRing *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "innerRadius", OrcMetaType_float, offsetof(Sgl$GeometryRing, innerRadius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "outerRadius", OrcMetaType_float, offsetof(Sgl$GeometryRing, outerRadius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaSegments", OrcMetaType_int, offsetof(Sgl$GeometryRing, thetaSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "phiSegments", OrcMetaType_int, offsetof(Sgl$GeometryRing, phiSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "thetaStart", OrcMetaType_float, offsetof(Sgl$GeometryRing, thetaStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaLength", OrcMetaType_float, offsetof(Sgl$GeometryRing, thetaLength), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryRing, build));
}


// vtable init


Vtable_Sgl$GeometryRing* Vtable_Sgl$GeometryRing_init(Vtable_Sgl$GeometryRing* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryRing;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryRing_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryRing";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryRing_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryRing_fini(Sgl$GeometryRing *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放
	

}

// init fields function


void Sgl$GeometryRing_init_fields(Sgl$GeometryRing *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryRing_fini;
	//fields
    {
	((Sgl$GeometryRing*)self)->innerRadius = 50;
	((Sgl$GeometryRing*)self)->outerRadius = 100;
	((Sgl$GeometryRing*)self)->thetaSegments = 120;
	((Sgl$GeometryRing*)self)->phiSegments = 1;
	((Sgl$GeometryRing*)self)->thetaStart = 0.0;
	((Sgl$GeometryRing*)self)->thetaLength = 3.141592653589793 * 2;
    }
	((Sgl$GeometryRing*)self)->build = (void*)Sgl$GeometryRing$build;
}

// init function

void Sgl$GeometryRing_init(Sgl$GeometryRing *self, void *pOwner){
    Vtable_Sgl$GeometryRing_init(&_vtable_Sgl$GeometryRing);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryRing;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryRing_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryRing * Sgl$GeometryRing_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryRing *self = calloc(1, sizeof(Sgl$GeometryRing));
	
    Sgl$GeometryRing_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryRing$build(Sgl$GeometryRing *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  pos = (pos=NULL,urgc_init_var_class((void**)&pos, Sgl$Buffer_new(&pos) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nml = (nml=NULL,urgc_init_var_class((void**)&nml, Sgl$Buffer_new(&nml) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
	float  radius = self->innerRadius;
	float  radiusStep = (self->outerRadius - self->innerRadius) / self->phiSegments;
	SuiCore$Vec3 vertex;
	SuiCore$Vec2 uv;
	for (int  j = 0; j <= self->phiSegments; j++) {
		for (int  i = 0; i <= self->thetaSegments; i++) {
			float  segment = self->thetaStart + i / (float )self->thetaSegments * self->thetaLength;
			vertex.x = radius * cos(segment) ;
			vertex.y = radius * sin(segment) ;
			Sgl$Buffer$appendFloat3(pos, vertex.x, vertex.y, vertex.z) ;
			Sgl$Buffer$appendFloat3(nml, 0, 0, 1) ;
			uv.x = (vertex.x / self->outerRadius + 1) / 2.0;
			uv.y = (vertex.y / self->outerRadius + 1) / 2.0;
			Sgl$Buffer$appendFloat2(uvs, uv.x, uv.y) ;
		}
		radius += radiusStep;
	}
	for (int  j = 0; j < self->phiSegments; j++) {
		int  thetaSegmentLevel = j * (self->thetaSegments + 1);
		for (int  i = 0; i < self->thetaSegments; i++) {
			int  segment = i + thetaSegmentLevel;
			int  a = segment;
			int  b = segment + self->thetaSegments + 1;
			int  c = segment + self->thetaSegments + 2;
			int  d = segment + 1;
			Sgl$Buffer$appendInt3(face, a, b, d) ;
			Sgl$Buffer$appendInt3(face, b, c, d) ;
		}
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", pos, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nml, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





