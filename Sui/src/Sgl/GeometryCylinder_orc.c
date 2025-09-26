
#include "GeometryCylinder_orc.h" 

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
Vtable_Sgl$GeometryCylinder _vtable_Sgl$GeometryCylinder;

// init meta

void Sgl$GeometryCylinder_initMeta(Vtable_Sgl$GeometryCylinder *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "radiusTop", OrcMetaType_float, offsetof(Sgl$GeometryCylinder, radiusTop), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "radiusBottom", OrcMetaType_float, offsetof(Sgl$GeometryCylinder, radiusBottom), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "height", OrcMetaType_float, offsetof(Sgl$GeometryCylinder, height), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "radialSegments", OrcMetaType_int, offsetof(Sgl$GeometryCylinder, radialSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "heightSegments", OrcMetaType_int, offsetof(Sgl$GeometryCylinder, heightSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "openEnded", OrcMetaType_bool, offsetof(Sgl$GeometryCylinder, openEnded), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "thetaStart", OrcMetaType_float, offsetof(Sgl$GeometryCylinder, thetaStart), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "thetaLength", OrcMetaType_float, offsetof(Sgl$GeometryCylinder, thetaLength), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "positions", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryCylinder, positions), true, false, 1);
	orc_metaField_class(&pNext, "normals", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryCylinder, normals), true, false, 1);
	orc_metaField_class(&pNext, "face", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryCylinder, face), true, false, 1);
	orc_metaField_class(&pNext, "uvs", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryCylinder, uvs), true, false, 1);

	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryCylinder, build));
	orc_metaField_method(&pNext, "generateTorso", offsetof(Sgl$GeometryCylinder, generateTorso));
	orc_metaField_method(&pNext, "generateCap", offsetof(Sgl$GeometryCylinder, generateCap));
}


// vtable init


Vtable_Sgl$GeometryCylinder* Vtable_Sgl$GeometryCylinder_init(Vtable_Sgl$GeometryCylinder* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryCylinder;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryCylinder_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryCylinder";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryCylinder_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryCylinder_fini(Sgl$GeometryCylinder *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放


}

// init fields function


void Sgl$GeometryCylinder_init_fields(Sgl$GeometryCylinder *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryCylinder_fini;
	//fields
    {
	((Sgl$GeometryCylinder*)self)->radiusTop = 10;
	((Sgl$GeometryCylinder*)self)->radiusBottom = 10;
	((Sgl$GeometryCylinder*)self)->height = 20;
	((Sgl$GeometryCylinder*)self)->radialSegments = 32;
	((Sgl$GeometryCylinder*)self)->heightSegments = 1;
	((Sgl$GeometryCylinder*)self)->openEnded = false;
	((Sgl$GeometryCylinder*)self)->thetaStart = 0;
	((Sgl$GeometryCylinder*)self)->thetaLength = Orc$PI * 2;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryCylinder*)self)->positions, Sgl$Buffer_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryCylinder*)self)->normals, Sgl$Buffer_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryCylinder*)self)->face, Sgl$Buffer_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryCylinder*)self)->uvs, Sgl$Buffer_new(&tmpNewOwner_4) );
    }
	((Sgl$GeometryCylinder*)self)->build = (void*)Sgl$GeometryCylinder$build;
	((Sgl$GeometryCylinder*)self)->generateTorso = (void*)Sgl$GeometryCylinder$generateTorso;
	((Sgl$GeometryCylinder*)self)->generateCap = (void*)Sgl$GeometryCylinder$generateCap;
}

// init function

void Sgl$GeometryCylinder_init(Sgl$GeometryCylinder *self, void *pOwner){
    Vtable_Sgl$GeometryCylinder_init(&_vtable_Sgl$GeometryCylinder);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryCylinder;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryCylinder_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryCylinder * Sgl$GeometryCylinder_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryCylinder *self = calloc(1, sizeof(Sgl$GeometryCylinder));
	
    Sgl$GeometryCylinder_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryCylinder$build(Sgl$GeometryCylinder *  self){
	float  halfHeight = self->height / 2.0;
	int  groupStart = 0;
	int  index = 0;
	self->generateTorso(self, &index) ;
	if (self->openEnded == false) {
		if (self->radiusTop > 0) {
			self->generateCap(self, true, &index) ;
		}
		if (self->radiusBottom > 0) {
			self->generateCap(self, false, &index) ;
		}
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", self->positions, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", self->normals, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", self->uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, self->face) ;
}


void  Sgl$GeometryCylinder$generateTorso(Sgl$GeometryCylinder *  self, int *  index){
	float  halfHeight = self->height / 2.0;
	SuiCore$Vec3 normal;
	SuiCore$Vec3 vertex;
	float  slope = (self->radiusBottom - self->radiusTop) / self->height;
	URGC_VAR_CLEANUP_CLASS Orc$List*  indexArray = (indexArray=NULL,urgc_init_var_class((void**)&indexArray, Orc$List_new(&indexArray) ));
	for (int  y = 0; y <= self->heightSegments; y++) {
		URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  indexRow = (indexRow=NULL,urgc_init_var_class((void**)&indexRow, Sgl$IntArray_new(&indexRow) ));
		float  v = y / (float )self->heightSegments;
		float  radius = v * (self->radiusBottom - self->radiusTop) + self->radiusTop;
		for (int  x = 0; x <= self->radialSegments; x++) {
			float  u = x / (float )self->radialSegments;
			float  theta = u * self->thetaLength + self->thetaStart;
			float  sinTheta = sin(theta) ;
			float  cosTheta = cos(theta) ;
			Sgl$Buffer$appendFloat3(self->positions, radius * sinTheta, -v * self->height + halfHeight, radius * cosTheta) ;
			normal = SuiCore$Vec3$normal(SuiCore$Vec3$set(&normal, sinTheta, slope, cosTheta) ) ;
			Sgl$Buffer$appendFloat3(self->normals, normal.x, normal.y, normal.z) ;
			Sgl$Buffer$appendFloat2(self->uvs, u, 1 - v) ;
			Sgl$IntArray$append(indexRow, *index) ;
			(*index)++;
		}
		indexArray->add(indexArray, indexRow) ;
	}
	for (int  x = 0; x < self->radialSegments; x++) {
		for (int  y = 0; y < self->heightSegments; y++) {
			Sgl$IntArray *  row0 = (Sgl$IntArray * )indexArray->get(indexArray, y) ;
			Sgl$IntArray *  row1 = (Sgl$IntArray * )indexArray->get(indexArray, y + 1) ;
			int  a = Sgl$IntArray$at(row0, x) ;
			int  b = Sgl$IntArray$at(row1, x) ;
			int  c = Sgl$IntArray$at(row1, x + 1) ;
			int  d = Sgl$IntArray$at(row0, x + 1) ;
			Sgl$Buffer$appendInt3(self->face, a, b, d) ;
			Sgl$Buffer$appendInt3(self->face, b, c, d) ;
		}
	}
}


void  Sgl$GeometryCylinder$generateCap(Sgl$GeometryCylinder *  self, bool  top, int *  index){
	float  halfHeight = self->height / 2.0;
	int  centerIndexStart = *index;
	SuiCore$Vec2 uv;
	SuiCore$Vec3 vertex;
	int  groupCount = 0;
	float  radius = top == true ? self->radiusTop : self->radiusBottom;
	float  sign = top == true ? 1 : -1;
	for (int  x = 0; x <= self->radialSegments; x++) {
		Sgl$Buffer$appendFloat3(self->positions, 0, halfHeight * sign, 0) ;
		Sgl$Buffer$appendFloat3(self->normals, 0, sign, 0) ;
		Sgl$Buffer$appendFloat2(self->uvs, 0.5, 0.5) ;
		(*index)++;
	}
	int  centerIndexEnd = *index;
	for (int  x = 0; x <= self->radialSegments; x++) {
		float  u = x / (float )self->radialSegments;
		float  theta = u * self->thetaLength + self->thetaStart;
		float  cosTheta = cos(theta) ;
		float  sinTheta = sin(theta) ;
		Sgl$Buffer$appendFloat3(self->positions, radius * sinTheta, halfHeight * sign, radius * cosTheta) ;
		Sgl$Buffer$appendFloat3(self->normals, 0, sign, 0) ;
		Sgl$Buffer$appendFloat2(self->uvs, cosTheta * 0.5 + 0.5, sinTheta * 0.5 * sign + 0.5) ;
		(*index)++;
	}
	for (int  x = 0; x < self->radialSegments; x++) {
		int  c = centerIndexStart + x;
		int  i = centerIndexEnd + x;
		if (top == true) {
			Sgl$Buffer$appendInt3(self->face, i, i + 1, c) ;
		}
		else {
			Sgl$Buffer$appendInt3(self->face, i + 1, i, c) ;
		}
	}
}





