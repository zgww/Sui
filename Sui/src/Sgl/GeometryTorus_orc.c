
#include "GeometryTorus_orc.h" 

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
Vtable_Sgl$GeometryTorus _vtable_Sgl$GeometryTorus;

// init meta

void Sgl$GeometryTorus_initMeta(Vtable_Sgl$GeometryTorus *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "radius", OrcMetaType_float, offsetof(Sgl$GeometryTorus, radius), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "tube", OrcMetaType_float, offsetof(Sgl$GeometryTorus, tube), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "radialSegments", OrcMetaType_float, offsetof(Sgl$GeometryTorus, radialSegments), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "tubularSegments", OrcMetaType_float, offsetof(Sgl$GeometryTorus, tubularSegments), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "arc", OrcMetaType_float, offsetof(Sgl$GeometryTorus, arc), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryTorus, build));
}


// vtable init


Vtable_Sgl$GeometryTorus* Vtable_Sgl$GeometryTorus_init(Vtable_Sgl$GeometryTorus* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryTorus;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryTorus_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryTorus";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryTorus_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryTorus_fini(Sgl$GeometryTorus *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放


}

// init fields function


void Sgl$GeometryTorus_init_fields(Sgl$GeometryTorus *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryTorus_fini;
	//fields
    {
	((Sgl$GeometryTorus*)self)->radius = 100;
	((Sgl$GeometryTorus*)self)->tube = 5.4;
	((Sgl$GeometryTorus*)self)->radialSegments = 12;
	((Sgl$GeometryTorus*)self)->tubularSegments = 48;
	((Sgl$GeometryTorus*)self)->arc = Orc$PI * 2;
    }
	((Sgl$GeometryTorus*)self)->build = (void*)Sgl$GeometryTorus$build;
}

// init function

void Sgl$GeometryTorus_init(Sgl$GeometryTorus *self, void *pOwner){
    Vtable_Sgl$GeometryTorus_init(&_vtable_Sgl$GeometryTorus);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryTorus;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryTorus_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryTorus * Sgl$GeometryTorus_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryTorus *self = calloc(1, sizeof(Sgl$GeometryTorus));
	
    Sgl$GeometryTorus_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryTorus$build(Sgl$GeometryTorus *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  pos = (pos=NULL,urgc_init_var_class((void**)&pos, Sgl$Buffer_new(&pos) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = (nmls=NULL,urgc_init_var_class((void**)&nmls, Sgl$Buffer_new(&nmls) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
	SuiCore$Vec3 center;
	SuiCore$Vec3 vertex;
	SuiCore$Vec3 normal;
	for (int  j = 0; j <= self->radialSegments; j++) {
		for (int  i = 0; i <= self->tubularSegments; i++) {
			float  u = i / self->tubularSegments * self->arc;
			float  v = j / self->radialSegments * Orc$PI * 2.0;
			vertex.x = (self->radius + self->tube * cos(v) ) * cos(u) ;
			vertex.y = (self->radius + self->tube * cos(v) ) * sin(u) ;
			vertex.z = self->tube * sin(v) ;
			Sgl$Buffer$appendFloat3(pos, vertex.x, vertex.y, vertex.z) ;
			center.x = self->radius * cos(u) ;
			center.y = self->radius * sin(u) ;
			SuiCore$Vec3$normalizeLocal(SuiCore$Vec3$subVectorsLocal(&normal, vertex, center) ) ;
			Sgl$Buffer$appendFloat3(nmls, normal.x, normal.y, normal.z) ;
			Sgl$Buffer$appendFloat2(uvs, i / self->tubularSegments, j / self->radialSegments) ;
		}
	}
	for (int  j = 1; j <= self->radialSegments; j++) {
		for (int  i = 1; i <= self->tubularSegments; i++) {
			int  a = (self->tubularSegments + 1) * j + i - 1;
			int  b = (self->tubularSegments + 1) * (j - 1) + i - 1;
			int  c = (self->tubularSegments + 1) * (j - 1) + i;
			int  d = (self->tubularSegments + 1) * j + i;
			Sgl$Buffer$appendInt3(face, a, b, d) ;
			Sgl$Buffer$appendInt3(face, b, c, d) ;
		}
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", pos, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nmls, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





