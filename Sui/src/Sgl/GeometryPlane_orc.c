
#include "GeometryPlane_orc.h" 

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
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryPlane _vtable_Sgl$GeometryPlane;

// init meta

void Sgl$GeometryPlane_initMeta(Vtable_Sgl$GeometryPlane *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(Sgl$GeometryPlane, width), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "height", OrcMetaType_float, offsetof(Sgl$GeometryPlane, height), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "widthSegments", OrcMetaType_int, offsetof(Sgl$GeometryPlane, widthSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "heightSegments", OrcMetaType_int, offsetof(Sgl$GeometryPlane, heightSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "planeType", OrcMetaType_int, offsetof(Sgl$GeometryPlane, planeType), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryPlane, build));
}


// vtable init


Vtable_Sgl$GeometryPlane* Vtable_Sgl$GeometryPlane_init(Vtable_Sgl$GeometryPlane* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryPlane;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryPlane_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryPlane";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryPlane_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryPlane_fini(Sgl$GeometryPlane *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放


}

// init fields function


void Sgl$GeometryPlane_init_fields(Sgl$GeometryPlane *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryPlane_fini;
	//fields
    {
	((Sgl$GeometryPlane*)self)->width = 1000;
	((Sgl$GeometryPlane*)self)->height = 1000;
	((Sgl$GeometryPlane*)self)->widthSegments = 10;
	((Sgl$GeometryPlane*)self)->heightSegments = 10;
	((Sgl$GeometryPlane*)self)->planeType = 0;
    }
	((Sgl$GeometryPlane*)self)->build = (void*)Sgl$GeometryPlane$build;
}

// init function

void Sgl$GeometryPlane_init(Sgl$GeometryPlane *self, void *pOwner){
    Vtable_Sgl$GeometryPlane_init(&_vtable_Sgl$GeometryPlane);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryPlane;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryPlane_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryPlane * Sgl$GeometryPlane_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryPlane *self = calloc(1, sizeof(Sgl$GeometryPlane));
	
    Sgl$GeometryPlane_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryPlane$build(Sgl$GeometryPlane *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  vtxs = (vtxs=NULL,urgc_init_var_class((void**)&vtxs, Sgl$Buffer_new(&vtxs) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = (nmls=NULL,urgc_init_var_class((void**)&nmls, Sgl$Buffer_new(&nmls) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
	float  widthHalf = self->width / 2.0;
	float  heightHalf = self->height / 2.0;
	int  gridX = self->widthSegments;
	int  gridY = self->heightSegments;
	int  gridX1 = self->widthSegments + 1;
	int  gridY1 = self->heightSegments + 1;
	float  segWidth = self->width / gridX;
	float  segHeight = self->width / gridY;
	for (int  j = 0; j < gridY1; j++) {
		float  y = j * segHeight - heightHalf;
		for (int  i = 0; i < gridX1; i++) {
			float  x = i * segWidth - widthHalf;
			if (self->planeType == 0) {
				Sgl$Buffer$appendFloat3(vtxs, x, y, 0) ;
				Sgl$Buffer$appendFloat3(nmls, 0, 0, 1) ;
			}
			else if (self->planeType == 1) {
				Sgl$Buffer$appendFloat3(vtxs, x, 0, y) ;
				Sgl$Buffer$appendFloat3(nmls, 0, 1, 0) ;
			}
			else {
				Sgl$Buffer$appendFloat3(vtxs, 0, x, y) ;
				Sgl$Buffer$appendFloat3(nmls, 1, 0, 0) ;
			}
			Sgl$Buffer$appendFloat2(uvs, i / (float )gridX, 1 - (j / (float )gridY)) ;
		}
	}
	for (int  j = 0; j < gridY1 - 1; j++) {
		for (int  i = 0; i < gridX1 - 1; i++) {
			int  a = i + j * gridX1;
			int  b = i + 1 + j * gridX1;
			int  c = i + 1 + (j + 1) * gridX1;
			int  d = i + (j + 1) * gridX1;
			Sgl$Buffer$appendInt3(face, a, b, c) ;
			Sgl$Buffer$appendInt3(face, a, c, d) ;
		}
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", vtxs, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nmls, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





