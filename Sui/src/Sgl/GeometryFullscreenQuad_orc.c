
#include "GeometryFullscreenQuad_orc.h" 

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Camera_orc.h"
#include "./Mat_orc.h"
#include "./Program_orc.h"
#include "./SpotLight_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryFullscreenQuad _vtable_Sgl$GeometryFullscreenQuad;

// init meta

void Sgl$GeometryFullscreenQuad_initMeta(Vtable_Sgl$GeometryFullscreenQuad *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "z", OrcMetaType_float, offsetof(Sgl$GeometryFullscreenQuad, z), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryFullscreenQuad, build));
}


// vtable init


Vtable_Sgl$GeometryFullscreenQuad* Vtable_Sgl$GeometryFullscreenQuad_init(Vtable_Sgl$GeometryFullscreenQuad* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryFullscreenQuad;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryFullscreenQuad_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryFullscreenQuad";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryFullscreenQuad_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryFullscreenQuad_fini(Sgl$GeometryFullscreenQuad *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放


}

// init fields function


void Sgl$GeometryFullscreenQuad_init_fields(Sgl$GeometryFullscreenQuad *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryFullscreenQuad_fini;
	//fields
    {
	((Sgl$GeometryFullscreenQuad*)self)->z = 0;
    }
	((Sgl$GeometryFullscreenQuad*)self)->build = (void*)Sgl$GeometryFullscreenQuad$build;
}

// init function

void Sgl$GeometryFullscreenQuad_init(Sgl$GeometryFullscreenQuad *self, void *pOwner){
    Vtable_Sgl$GeometryFullscreenQuad_init(&_vtable_Sgl$GeometryFullscreenQuad);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryFullscreenQuad;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryFullscreenQuad_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryFullscreenQuad * Sgl$GeometryFullscreenQuad_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryFullscreenQuad *self = calloc(1, sizeof(Sgl$GeometryFullscreenQuad));
	
    Sgl$GeometryFullscreenQuad_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryFullscreenQuad$build(Sgl$GeometryFullscreenQuad *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  vtx = (vtx=NULL,urgc_init_var_class((void**)&vtx, Sgl$Buffer_new(&vtx) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nml = (nml=NULL,urgc_init_var_class((void**)&nml, Sgl$Buffer_new(&nml) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv = (uv=NULL,urgc_init_var_class((void**)&uv, Sgl$Buffer_new(&uv) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	float  d = 3;
	Sgl$Buffer$appendFloat3(vtx, -1, d, self->z) ;
	Sgl$Buffer$appendFloat3(nml, 0, 0, 1) ;
	Sgl$Buffer$appendFloat2(uv, 0, 2) ;
	Sgl$Buffer$appendFloat3(vtx, -1, -1, self->z) ;
	Sgl$Buffer$appendFloat3(nml, 0, 0, 1) ;
	Sgl$Buffer$appendFloat2(uv, 0, 0) ;
	Sgl$Buffer$appendFloat3(vtx, d, -1, self->z) ;
	Sgl$Buffer$appendFloat3(nml, 0, 0, 1) ;
	Sgl$Buffer$appendFloat2(uv, 2, 0) ;
	Sgl$Buffer$appendInt3(face, 0, 1, 2) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", vtx, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nml, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uv, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





