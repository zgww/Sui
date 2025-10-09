
#include "GeometryCircle_orc.h" 

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
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryCircle _vtable_Sgl$GeometryCircle;

// init meta

void Sgl$GeometryCircle_initMeta(Vtable_Sgl$GeometryCircle *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "radius", OrcMetaType_float, offsetof(Sgl$GeometryCircle, radius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "segments", OrcMetaType_int, offsetof(Sgl$GeometryCircle, segments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "thetaStart", OrcMetaType_float, offsetof(Sgl$GeometryCircle, thetaStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaLength", OrcMetaType_float, offsetof(Sgl$GeometryCircle, thetaLength), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryCircle, build));
}


// vtable init


Vtable_Sgl$GeometryCircle* Vtable_Sgl$GeometryCircle_init(Vtable_Sgl$GeometryCircle* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryCircle;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryCircle_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryCircle";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryCircle_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryCircle_fini(Sgl$GeometryCircle *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放
	

}

// init fields function


void Sgl$GeometryCircle_init_fields(Sgl$GeometryCircle *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryCircle_fini;
	//fields
    {
	((Sgl$GeometryCircle*)self)->radius = 100;
	((Sgl$GeometryCircle*)self)->segments = 120;
	((Sgl$GeometryCircle*)self)->thetaStart = 0.0;
	((Sgl$GeometryCircle*)self)->thetaLength = 3.141592653589793 * 2;
    }
	((Sgl$GeometryCircle*)self)->build = (void*)Sgl$GeometryCircle$build;
}

// init function

void Sgl$GeometryCircle_init(Sgl$GeometryCircle *self, void *pOwner){
    Vtable_Sgl$GeometryCircle_init(&_vtable_Sgl$GeometryCircle);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryCircle;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryCircle_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryCircle * Sgl$GeometryCircle_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryCircle *self = calloc(1, sizeof(Sgl$GeometryCircle));
	
    Sgl$GeometryCircle_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryCircle$build(Sgl$GeometryCircle *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  pos = (pos=NULL,urgc_init_var_class((void**)&pos, Sgl$Buffer_new(&pos) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = (nmls=NULL,urgc_init_var_class((void**)&nmls, Sgl$Buffer_new(&nmls) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
	int  segments = Orc$maxInt(3, self->segments) ;
	float  radius = self->radius;
	Sgl$Buffer$appendFloat3(pos, 0, 0, 0) ;
	Sgl$Buffer$appendFloat3(nmls, 0, 0, 1) ;
	Sgl$Buffer$appendFloat2(uvs, 0.5, 0.5) ;
	{
		for (int  i = 0; i <= segments + 1; i++) {
			float  segment = self->thetaStart + i / (float )segments * self->thetaLength;
			float  x = radius * cos(segment) ;
			float  y = radius * sin(segment) ;
			Sgl$Buffer$appendFloat3(pos, x, y, 0) ;
			Sgl$Buffer$appendFloat3(nmls, 0, 0, 1) ;
			Sgl$Buffer$appendFloat2(uvs, (x / radius + 1) / 2.0, (y / radius + 1) / 2.0) ;
		}
	}
	for (int  i = 0; i <= segments; i++) {
		Sgl$Buffer$appendInt3(face, i, i + 1, 0) ;
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", pos, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nmls, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





