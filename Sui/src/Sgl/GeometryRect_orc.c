
#include "GeometryRect_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryRect _vtable_Sgl$GeometryRect;

// init meta

void Sgl$GeometryRect_initMeta(Vtable_Sgl$GeometryRect *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(Sgl$GeometryRect, width), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "height", OrcMetaType_float, offsetof(Sgl$GeometryRect, height), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryRect, build));
}


// vtable init


Vtable_Sgl$GeometryRect* Vtable_Sgl$GeometryRect_init(Vtable_Sgl$GeometryRect* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryRect;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryRect_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryRect";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryRect_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryRect_fini(Sgl$GeometryRect *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放
	

}

// init fields function


void Sgl$GeometryRect_init_fields(Sgl$GeometryRect *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryRect_fini;
	//fields
    {
	((Sgl$GeometryRect*)self)->width = 100;
	((Sgl$GeometryRect*)self)->height = 100;
    }
	((Sgl$GeometryRect*)self)->build = (void*)Sgl$GeometryRect$build;
}

// init function

void Sgl$GeometryRect_init(Sgl$GeometryRect *self, void *pOwner){
    Vtable_Sgl$GeometryRect_init(&_vtable_Sgl$GeometryRect);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryRect;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryRect_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryRect * Sgl$GeometryRect_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryRect *self = calloc(1, sizeof(Sgl$GeometryRect));
	
    Sgl$GeometryRect_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryRect$build(Sgl$GeometryRect *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = (buf=NULL,urgc_init_var_class((void**)&buf, Sgl$Buffer_new(&buf) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  normal = (normal=NULL,urgc_init_var_class((void**)&normal, Sgl$Buffer_new(&normal) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv = (uv=NULL,urgc_init_var_class((void**)&uv, Sgl$Buffer_new(&uv) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	float  startX = -self->width / 2.0;
	float  startY = -self->width / 2.0;
	float  startZ = 0;
	Sgl$Buffer$appendFloat3(buf, startX, startY, startZ) ;
	Sgl$Buffer$appendFloat3(normal, 0, 1, 0) ;
	Sgl$Buffer$appendFloat2(uv, 0, 0) ;
	Sgl$Buffer$appendFloat3(buf, startX + self->width, startY, startZ) ;
	Sgl$Buffer$appendFloat3(normal, 0, 1, 0) ;
	Sgl$Buffer$appendFloat2(uv, 1, 0) ;
	Sgl$Buffer$appendFloat3(buf, startX + self->width, startY + self->height, startZ) ;
	Sgl$Buffer$appendFloat3(normal, 0, 1, 0) ;
	Sgl$Buffer$appendFloat2(uv, 1, 1) ;
	Sgl$Buffer$appendFloat3(buf, startX, startY + self->height, startZ) ;
	Sgl$Buffer$appendFloat3(normal, 0, 1, 0) ;
	Sgl$Buffer$appendFloat2(uv, 0, 1) ;
	Sgl$Buffer$appendInt3(face, 0, 1, 2) ;
	Sgl$Buffer$appendInt3(face, 0, 2, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", buf, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", normal, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uv, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





