
#include "GeometryCapsule_orc.h" 

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Math_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryCapsule _vtable_Sgl$GeometryCapsule;

// init meta

void Sgl$GeometryCapsule_initMeta(Vtable_Sgl$GeometryCapsule *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "radius", OrcMetaType_float, offsetof(Sgl$GeometryCapsule, radius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "segments", OrcMetaType_int, offsetof(Sgl$GeometryCapsule, segments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "thetaStart", OrcMetaType_float, offsetof(Sgl$GeometryCapsule, thetaStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaLength", OrcMetaType_float, offsetof(Sgl$GeometryCapsule, thetaLength), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_Sgl$GeometryCapsule* Vtable_Sgl$GeometryCapsule_init(Vtable_Sgl$GeometryCapsule* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryCapsule;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryCapsule_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryCapsule";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryCapsule_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryCapsule_fini(Sgl$GeometryCapsule *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放
	

}

// init fields function


void Sgl$GeometryCapsule_init_fields(Sgl$GeometryCapsule *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryCapsule_fini;
	//fields
    {
	((Sgl$GeometryCapsule*)self)->radius = 100;
	((Sgl$GeometryCapsule*)self)->segments = 20;
	((Sgl$GeometryCapsule*)self)->thetaStart = 0.0;
	((Sgl$GeometryCapsule*)self)->thetaLength = 3.141592653589793 * 2;
    }
	((Sgl$Geometry*)self)->build = (void*)Sgl$GeometryCapsule$build;
}

// init function

void Sgl$GeometryCapsule_init(Sgl$GeometryCapsule *self, void *pOwner){
    Vtable_Sgl$GeometryCapsule_init(&_vtable_Sgl$GeometryCapsule);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryCapsule;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryCapsule_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryCapsule * Sgl$GeometryCapsule_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryCapsule *self = calloc(1, sizeof(Sgl$GeometryCapsule));
	
    Sgl$GeometryCapsule_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryCapsule$build(Sgl$GeometryCapsule *  self){
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
		int  s = 0;
		for (int  i = 3; s <= self->segments; i += 3) {
			float  segment = self->thetaStart + s / self->segments * self->thetaLength;
			float  x = radius * cos(segment) ;
			float  y = radius * sin(segment) ;
			Sgl$Buffer$appendFloat3(pos, x, y, 0) ;
			Sgl$Buffer$appendFloat3(nmls, 0, 0, 1) ;
			Sgl$Buffer$appendFloat2(uvs, (x / radius + 1) / 2.0, (y / radius + 1) / 2.0) ;
			s++;
		}
	}
	for (int  i = 1; i < segments; i++) {
		Sgl$Buffer$appendInt3(face, i, i + 1, 0) ;
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", pos, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nmls, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





