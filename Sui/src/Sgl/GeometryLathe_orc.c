
#include "GeometryLathe_orc.h" 

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
Vtable_Sgl$GeometryLathe _vtable_Sgl$GeometryLathe;

// init meta

void Sgl$GeometryLathe_initMeta(Vtable_Sgl$GeometryLathe *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "segments", OrcMetaType_int, offsetof(Sgl$GeometryLathe, segments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "phiStart", OrcMetaType_float, offsetof(Sgl$GeometryLathe, phiStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "phiLength", OrcMetaType_float, offsetof(Sgl$GeometryLathe, phiLength), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "points", ((Vtable_Object*)Vtable_Sgl$Vec3Array_init(0)), offsetof(Sgl$GeometryLathe, points), true, false, 1);

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryLathe, build));
}


// vtable init


Vtable_Sgl$GeometryLathe* Vtable_Sgl$GeometryLathe_init(Vtable_Sgl$GeometryLathe* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryLathe;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryLathe_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryLathe";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryLathe_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryLathe_fini(Sgl$GeometryLathe *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放


}

// init fields function


void Sgl$GeometryLathe_init_fields(Sgl$GeometryLathe *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryLathe_fini;
	//fields
    {
	((Sgl$GeometryLathe*)self)->segments = 12;
	((Sgl$GeometryLathe*)self)->phiStart = 0;
	((Sgl$GeometryLathe*)self)->phiLength = Orc$PI * 2;
	URGC_VAR_CLEANUP_CLASS Sgl$Vec3Array*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryLathe*)self)->points, Sgl$Vec3Array_new(&tmpNewOwner_1) );
    }
	((Sgl$GeometryLathe*)self)->build = (void*)Sgl$GeometryLathe$build;
}

// init function

void Sgl$GeometryLathe_init(Sgl$GeometryLathe *self, void *pOwner){
    Vtable_Sgl$GeometryLathe_init(&_vtable_Sgl$GeometryLathe);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryLathe;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryLathe_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryLathe * Sgl$GeometryLathe_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryLathe *self = calloc(1, sizeof(Sgl$GeometryLathe));
	
    Sgl$GeometryLathe_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryLathe$build(Sgl$GeometryLathe *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  pos = (pos=NULL,urgc_init_var_class((void**)&pos, Sgl$Buffer_new(&pos) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = (nmls=NULL,urgc_init_var_class((void**)&nmls, Sgl$Buffer_new(&nmls) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	float  inverseSegments = 1.0 / (float )self->segments;
	SuiCore$Vec3 vertex;
	SuiCore$Vec2 uv;
	SuiCore$Vec3 normal;
	SuiCore$Vec3 curNormal;
	SuiCore$Vec3 prevNormal;
	Sgl$Vec3Array *  points = self->points;
	URGC_VAR_CLEANUP_CLASS Sgl$FloatArray*  initNormals = (initNormals=NULL,urgc_init_var_class((void**)&initNormals, Sgl$FloatArray_new(&initNormals) ));
	float  dx = 0;
	float  dy = 0;
	for (int  j = 0; j <= (((Sgl$StructArrayBase * )self->points)->size - 1); j++) {
		if (j == 0) {
			dx = points->get(points, j + 1) .x - points->get(points, j) .x;
			dy = points->get(points, j + 1) .y - points->get(points, j) .y;
			normal.x = dy * 1.0;
			normal.y = -dx;
			normal.z = dy * 0.0;
			SuiCore$Vec3$copy(&prevNormal, normal) ;
			normal = SuiCore$Vec3$normal(&normal) ;
			initNormals->appendFloat3(initNormals, normal.x, normal.y, normal.z) ;
		}
		else if (j == ((Sgl$StructArrayBase * )self->points)->size - 1) {
			initNormals->appendFloat3(initNormals, prevNormal.x, prevNormal.y, prevNormal.z) ;
		}
		else {
			dx = points->get(points, j + 1) .x - points->get(points, j) .x;
			dy = points->get(points, j + 1) .y - points->get(points, j) .y;
			normal.x = dy * 1.0;
			normal.y = -dx;
			normal.z = dy * 0.0;
			SuiCore$Vec3$copy(&curNormal, normal) ;
			normal.x += prevNormal.x;
			normal.y += prevNormal.y;
			normal.z += prevNormal.z;
			normal = SuiCore$Vec3$normal(&normal) ;
			initNormals->appendFloat3(initNormals, normal.x, normal.y, normal.z) ;
			SuiCore$Vec3$copy(&prevNormal, curNormal) ;
		}
	}
	for (int  i = 0; i < segments; i++) {
		float  phi = self->phiStart + i * inverseSegments * self->phiLength;
		float  cosPhi = cos(phi) ;
		float  sinPhi = sin(phi) ;
		for (int  j = 0; j < ((Sgl$StructArrayBase * )points)->size; j++) {
			vertex.x = points->get(points, j) .x * sinPhi;
			vertex.y = points->get(points, j) .y;
			vertex.z = points->get(points, j) .x * cosPhi;
			Sgl$Buffer$appendFloat3(pos, vertex.x, vertex.y, vertex.z) ;
			{
				float  x = initNormals->get(initNormals, 3 * j + 0)  * sinPhi;
				float  y = initNormals->get(initNormals, 3 * j + 1) ;
				float  z = initNormals->get(initNormals, 3 * j + 0)  * cosPhi;
				Sgl$Buffer$appendFloat3(nmls, x, y, z) ;
			}
			uv.x = (float )i / (float )self->segments;
			uv.y = (float )j / (float )(((Sgl$StructArrayBase * )points)->size - 1);
			Sgl$Buffer$appendFloat2(uvs, uv.x, uv.y) ;
		}
	}
	for (int  i = 0; i < self->segments; i++) {
		for (int  j = 0; j < ((Sgl$StructArrayBase * )points)->size - 1; j++) {
			int  base = j + i * ((Sgl$StructArrayBase * )points)->size;
			int  a = base;
			int  b = base + ((Sgl$StructArrayBase * )points)->size;
			int  c = base + ((Sgl$StructArrayBase * )points)->size + 1;
			int  d = base + 1;
			Sgl$Buffer$appendInt3(face, a, b, d) ;
			Sgl$Buffer$appendInt3(face, c, d, b) ;
		}
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", pos, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nmls, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 3) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





