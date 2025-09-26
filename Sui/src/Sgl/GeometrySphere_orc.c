
#include "GeometrySphere_orc.h" 

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
Vtable_Sgl$GeometrySphere _vtable_Sgl$GeometrySphere;

// init meta

void Sgl$GeometrySphere_initMeta(Vtable_Sgl$GeometrySphere *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "radius", OrcMetaType_float, offsetof(Sgl$GeometrySphere, radius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "widthSegments", OrcMetaType_int, offsetof(Sgl$GeometrySphere, widthSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "heightSegments", OrcMetaType_int, offsetof(Sgl$GeometrySphere, heightSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "phiStart", OrcMetaType_float, offsetof(Sgl$GeometrySphere, phiStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "phiLength", OrcMetaType_float, offsetof(Sgl$GeometrySphere, phiLength), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaStart", OrcMetaType_float, offsetof(Sgl$GeometrySphere, thetaStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaLength", OrcMetaType_float, offsetof(Sgl$GeometrySphere, thetaLength), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometrySphere, build));
}


// vtable init


Vtable_Sgl$GeometrySphere* Vtable_Sgl$GeometrySphere_init(Vtable_Sgl$GeometrySphere* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometrySphere;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometrySphere_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometrySphere";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometrySphere_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometrySphere_fini(Sgl$GeometrySphere *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放


}

// init fields function


void Sgl$GeometrySphere_init_fields(Sgl$GeometrySphere *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometrySphere_fini;
	//fields
    {
	((Sgl$GeometrySphere*)self)->radius = 100;
	((Sgl$GeometrySphere*)self)->widthSegments = 32;
	((Sgl$GeometrySphere*)self)->heightSegments = 32;
	((Sgl$GeometrySphere*)self)->phiStart = 0.0;
	((Sgl$GeometrySphere*)self)->phiLength = Orc$PI * 2;
	((Sgl$GeometrySphere*)self)->thetaStart = 0.0;
	((Sgl$GeometrySphere*)self)->thetaLength = Orc$PI;
    }
	((Sgl$GeometrySphere*)self)->build = (void*)Sgl$GeometrySphere$build;
}

// init function

void Sgl$GeometrySphere_init(Sgl$GeometrySphere *self, void *pOwner){
    Vtable_Sgl$GeometrySphere_init(&_vtable_Sgl$GeometrySphere);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometrySphere;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometrySphere_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometrySphere * Sgl$GeometrySphere_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometrySphere *self = calloc(1, sizeof(Sgl$GeometrySphere));
	
    Sgl$GeometrySphere_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometrySphere$build(Sgl$GeometrySphere *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  pos = (pos=NULL,urgc_init_var_class((void**)&pos, Sgl$Buffer_new(&pos) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = (nmls=NULL,urgc_init_var_class((void**)&nmls, Sgl$Buffer_new(&nmls) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
	float  thetaEnd = Orc$minFloat(self->thetaStart + self->thetaLength, Orc$PI) ;
	int  index = 0;
	SuiCore$Vec3 vertex;
	SuiCore$Vec3 normal;
	int  heightSegments = self->heightSegments;
	int  widthSegments = self->widthSegments;
	URGC_VAR_CLEANUP_CLASS Orc$List*  grid = (grid=NULL,urgc_init_var_class((void**)&grid, Orc$List_new(&grid) ));
	for (int  iy = 0; iy <= heightSegments; iy++) {
		URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  verticesRow = (verticesRow=NULL,urgc_init_var_class((void**)&verticesRow, Sgl$IntArray_new(&verticesRow) ));
		float  v = iy / (float )heightSegments;
		float  uOffset = 0;
		if (iy == 0 && self->thetaStart == 0) {
			uOffset = 0.5 / widthSegments;
		}
		else if (iy == heightSegments && thetaEnd == Orc$PI) {
			uOffset = -0.5 / widthSegments;
		}
		for (int  ix = 0; ix <= widthSegments; ix++) {
			float  u = ix / (float )widthSegments;
			float  theta = self->thetaStart + v * self->thetaLength;
			float  phi = self->phiStart + u * self->phiLength;
			vertex.x = -self->radius * cos(phi)  * sin(theta) ;
			vertex.y = self->radius * cos(theta) ;
			vertex.z = self->radius * sin(phi)  * sin(theta) ;
			normal.x = vertex.x / self->radius;
			normal.y = vertex.y / self->radius;
			normal.z = vertex.z / self->radius;
			Sgl$Buffer$appendFloat3(pos, vertex.x, vertex.y, vertex.z) ;
			Sgl$Buffer$appendFloat3(nmls, normal.x, normal.y, normal.z) ;
			Sgl$Buffer$appendFloat2(uvs, u + uOffset, 1 - v) ;
			Sgl$IntArray$append(verticesRow, index) ;
			index++;
		}
		grid->add(grid, verticesRow) ;
	}
	for (int  iy = 0; iy < heightSegments; iy++) {
		for (int  ix = 0; ix < widthSegments; ix++) {
			Sgl$IntArray *  iyRow = grid->get(grid, iy) ;
			Sgl$IntArray *  iyRow1 = grid->get(grid, iy + 1) ;
			int  a = Sgl$IntArray$at(iyRow, ix + 1) ;
			int  b = Sgl$IntArray$at(iyRow, ix + 0) ;
			int  c = Sgl$IntArray$at(iyRow1, ix + 0) ;
			int  d = Sgl$IntArray$at(iyRow1, ix + 1) ;
			if (iy != 0 || self->thetaStart > 0) {
				Sgl$Buffer$appendInt3(face, a, b, d) ;
			}
			if (iy != heightSegments - 1 || thetaEnd < Orc$PI) {
				Sgl$Buffer$appendInt3(face, b, c, d) ;
			}
		}
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", pos, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nmls, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





