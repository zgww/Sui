
#include "Geometry_orc.h" 

#include <stdlib.h>
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


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeoAttr _vtable_Sgl$GeoAttr;

// init meta

void Sgl$GeoAttr_initMeta(Vtable_Sgl$GeoAttr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "key", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$GeoAttr, key), true, false, 1);
	orc_metaField_class(&pNext, "vbo", ((Vtable_Object*)Vtable_Sgl$Vbo_init(0)), offsetof(Sgl$GeoAttr, vbo), true, false, 1);

	orc_metaField_method(&pNext, "bindVertexAttrib", offsetof(Sgl$GeoAttr, bindVertexAttrib));
}


// vtable init


Vtable_Sgl$GeoAttr* Vtable_Sgl$GeoAttr_init(Vtable_Sgl$GeoAttr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeoAttr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeoAttr_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeoAttr";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeoAttr_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeoAttr_fini(Sgl$GeoAttr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$GeoAttr*)self)->key);
	urgc_fini_field_class(self, (void**)&((Sgl$GeoAttr*)self)->vbo);

}

// init fields function


void Sgl$GeoAttr_init_fields(Sgl$GeoAttr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$GeoAttr_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$GeoAttr*)self)->key, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$GeoAttr*)self)->vbo, NULL);
    }
	((Sgl$GeoAttr*)self)->bindVertexAttrib = (void*)Sgl$GeoAttr$bindVertexAttrib;
}

// init function

void Sgl$GeoAttr_init(Sgl$GeoAttr *self, void *pOwner){
    Vtable_Sgl$GeoAttr_init(&_vtable_Sgl$GeoAttr);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeoAttr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeoAttr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeoAttr * Sgl$GeoAttr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeoAttr *self = calloc(1, sizeof(Sgl$GeoAttr));
	
    Sgl$GeoAttr_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_Sgl$Geometry _vtable_Sgl$Geometry;

// init meta

void Sgl$Geometry_initMeta(Vtable_Sgl$Geometry *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "attrs", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(Sgl$Geometry, attrs), true, false, 1);
	orc_metaField_class(&pNext, "ibo", ((Vtable_Object*)Vtable_Sgl$Vbo_init(0)), offsetof(Sgl$Geometry, ibo), true, false, 1);
	orc_metaField_class(&pNext, "instanceVbo", ((Vtable_Object*)Vtable_Sgl$Vbo_init(0)), offsetof(Sgl$Geometry, instanceVbo), true, false, 1);
	orc_metaField_primitive(&pNext, "version", OrcMetaType_int, offsetof(Sgl$Geometry, version), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "build", offsetof(Sgl$Geometry, build));
	orc_metaField_method(&pNext, "setIboByBuffer", offsetof(Sgl$Geometry, setIboByBuffer));
	orc_metaField_method(&pNext, "setAttrByBuffer", offsetof(Sgl$Geometry, setAttrByBuffer));
	orc_metaField_method(&pNext, "setIboByInts", offsetof(Sgl$Geometry, setIboByInts));
	orc_metaField_method(&pNext, "setIboByShorts", offsetof(Sgl$Geometry, setIboByShorts));
	orc_metaField_method(&pNext, "applyAttrByBuffer", offsetof(Sgl$Geometry, applyAttrByBuffer));
	orc_metaField_method(&pNext, "setAttrByFloats", offsetof(Sgl$Geometry, setAttrByFloats));
	orc_metaField_method(&pNext, "setInstanceAttrByBuffer", offsetof(Sgl$Geometry, setInstanceAttrByBuffer));
	orc_metaField_method(&pNext, "getAttr", offsetof(Sgl$Geometry, getAttr));
	orc_metaField_method(&pNext, "setAttr", offsetof(Sgl$Geometry, setAttr));
	orc_metaField_method(&pNext, "gocInstanceAttr", offsetof(Sgl$Geometry, gocInstanceAttr));
	orc_metaField_method(&pNext, "gocAttr", offsetof(Sgl$Geometry, gocAttr));
	orc_metaField_method(&pNext, "bindVertexAttribs", offsetof(Sgl$Geometry, bindVertexAttribs));
}


// vtable init


Vtable_Sgl$Geometry* Vtable_Sgl$Geometry_init(Vtable_Sgl$Geometry* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Geometry;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Geometry_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Geometry";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Geometry_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Geometry_fini(Sgl$Geometry *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Geometry*)self)->attrs);
	urgc_fini_field_class(self, (void**)&((Sgl$Geometry*)self)->ibo);
	urgc_fini_field_class(self, (void**)&((Sgl$Geometry*)self)->instanceVbo);

}

// init fields function


void Sgl$Geometry_init_fields(Sgl$Geometry *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Geometry_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Geometry*)self)->attrs, Orc$Map_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((Sgl$Geometry*)self)->ibo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Geometry*)self)->instanceVbo, NULL);
	((Sgl$Geometry*)self)->version = 1;
    }
	((Sgl$Geometry*)self)->build = (void*)Sgl$Geometry$build;
	((Sgl$Geometry*)self)->setIboByBuffer = (void*)Sgl$Geometry$setIboByBuffer;
	((Sgl$Geometry*)self)->setAttrByBuffer = (void*)Sgl$Geometry$setAttrByBuffer;
	((Sgl$Geometry*)self)->setIboByInts = (void*)Sgl$Geometry$setIboByInts;
	((Sgl$Geometry*)self)->setIboByShorts = (void*)Sgl$Geometry$setIboByShorts;
	((Sgl$Geometry*)self)->applyAttrByBuffer = (void*)Sgl$Geometry$applyAttrByBuffer;
	((Sgl$Geometry*)self)->setAttrByFloats = (void*)Sgl$Geometry$setAttrByFloats;
	((Sgl$Geometry*)self)->setInstanceAttrByBuffer = (void*)Sgl$Geometry$setInstanceAttrByBuffer;
	((Sgl$Geometry*)self)->getAttr = (void*)Sgl$Geometry$getAttr;
	((Sgl$Geometry*)self)->setAttr = (void*)Sgl$Geometry$setAttr;
	((Sgl$Geometry*)self)->gocInstanceAttr = (void*)Sgl$Geometry$gocInstanceAttr;
	((Sgl$Geometry*)self)->gocAttr = (void*)Sgl$Geometry$gocAttr;
	((Sgl$Geometry*)self)->bindVertexAttribs = (void*)Sgl$Geometry$bindVertexAttribs;
}

// init function

void Sgl$Geometry_init(Sgl$Geometry *self, void *pOwner){
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Geometry;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Geometry_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Geometry * Sgl$Geometry_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Geometry *self = calloc(1, sizeof(Sgl$Geometry));
	
    Sgl$Geometry_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Geometry$build(Sgl$Geometry *  self){
	
}


void  Sgl$Geometry$setIboByBuffer(Sgl$Geometry *  self, Sgl$Buffer *  buffer){
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Geometry, ibo) , Sgl$Vbo_new(&tmpNewOwner_1) ) ;
	self->ibo->elementBuffer(self->ibo, buffer) ;
	self->version++;
}


void  Sgl$Geometry$setAttrByBuffer(Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCountPerVertex){
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
	vbo->arrayBuffer(vbo, buffer) ;
	vbo->elementCount = elementCountPerVertex;
	self->setAttr(self, name, vbo) ;
}


void  Sgl$Geometry$setIboByInts(Sgl$Geometry *  self, int *  data, int  cnt){
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Geometry, ibo) , Sgl$Vbo_new(&tmpNewOwner_1) ) ;
	self->ibo->elementBufferData(self->ibo, cnt * 4, data) ;
	self->version++;
}


void  Sgl$Geometry$setIboByShorts(Sgl$Geometry *  self, short *  data, int  cnt){
	int *  ints = malloc(cnt * 4) ;
	for (int  i = 0; i < cnt; i++) {
		ints[i] = data[i];
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Geometry, ibo) , Sgl$Vbo_new(&tmpNewOwner_1) ) ;
	self->ibo->elementBufferData(self->ibo, cnt * 4, ints) ;
	free(ints) ;
	self->version++;
}


void  Sgl$Geometry$applyAttrByBuffer(Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCountPerVertex){
	Sgl$GeoAttr *  ga = self->getAttr(self, name) ;
	if (ga != NULL && ga->vbo->byteSize >= buffer->size) {
		ga->vbo->arrayBuffer(ga->vbo, buffer) ;
	}
	else {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		ga = self->setAttr(self, name, vbo) ;
		ga->vbo->elementCount = elementCountPerVertex;
		ga->vbo->usage = GL_DYNAMIC_DRAW;
		ga->vbo->arrayBuffer(ga->vbo, buffer) ;
	}
}


void  Sgl$Geometry$setAttrByFloats(Sgl$Geometry *  self, const char *  name, float *  data, int  floatCount, int  elementCountPerVertex){
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
	vbo->arrayBufferData(vbo, floatCount * 4, data) ;
	vbo->elementCount = elementCountPerVertex;
	self->setAttr(self, name, vbo) ;
}


void  Sgl$Geometry$setInstanceAttrByBuffer(Sgl$Geometry *  self, const char *  name, Sgl$Buffer *  buffer, int  elementCount){
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
	vbo->arrayBuffer(vbo, buffer) ;
	vbo->elementCount = elementCount;
	vbo->divide = 1;
	self->setAttr(self, name, vbo) ;
}


Sgl$GeoAttr *  Sgl$Geometry$getAttr(Sgl$Geometry *  self, const char *  key){
	Sgl$GeoAttr *  a = (Sgl$GeoAttr * )self->attrs->get(self->attrs, key) ;
	return a; 
}


Sgl$GeoAttr *  Sgl$Geometry$setAttr(Sgl$Geometry *  self, const char *  key, Sgl$Vbo*  vbo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(vbo);

	self->version++;
	URGC_VAR_CLEANUP_CLASS Sgl$GeoAttr*  a = (a=NULL,urgc_init_var_class((void**)&a, Sgl$GeoAttr_new(&a) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(a, (void * )offsetof(Sgl$GeoAttr, key) , Orc$str(&tmpReturn_1, key) ) ;
	urgc_set_field_class(a, (void * )offsetof(Sgl$GeoAttr, vbo) , vbo) ;
	if (vbo->divide > 0) {
		urgc_set_field_class(self, (void * )offsetof(Sgl$Geometry, instanceVbo) , vbo) ;
	}
	self->attrs->put(self->attrs, key, a) ;
	return a; 
}


Sgl$GeoAttr *  Sgl$Geometry$gocInstanceAttr(Sgl$Geometry *  self, const char *  key){
	Sgl$GeoAttr *  a = self->gocAttr(self, key) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Geometry, instanceVbo) , a->vbo) ;
	return a; 
}


Sgl$GeoAttr *  Sgl$Geometry$gocAttr(Sgl$Geometry *  self, const char *  key){
	Sgl$GeoAttr *  a = (Sgl$GeoAttr * )self->attrs->get(self->attrs, key) ;
	if (a == NULL) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		a = self->setAttr(self, key, vbo) ;
	}
	return a; 
}


bool  Sgl$Geometry$bindVertexAttribs(Sgl$Geometry *  self, Sgl$Material *  matl){
	URGC_VAR_CLEANUP_CLASS Orc$List*  keys = self->attrs->keys((keys = NULL,&keys), self->attrs) ;
	int  l = keys->size(keys) ;
	for (int  i = 0; i < l; i++) {
		Orc$String *  key = (Orc$String * )keys->get(keys, i) ;
		Sgl$GeoAttr *  ga = (Sgl$GeoAttr * )self->attrs->get(self->attrs, key->str) ;
		if (ga) {
			bool  ok = ga->bindVertexAttrib(ga, matl) ;
			if (!ok) {
				return false; 
			}
		}
	}
	return true; 
}



Sgl$Buffer*  Sgl$Geometry_computeVertexNormals(Sgl$Buffer **  __outRef__, Sgl$Buffer *  face, Sgl$Buffer *  position){
	float *  floats = (float * )position->data;
	int *  indexes = (int * )face->data;
	int  floatCount = Sgl$Buffer$floatSize(position) ;
	int  indexCount = Sgl$Buffer$intSize(face) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  normal = (normal=NULL,urgc_init_var_class((void**)&normal, Sgl$Buffer_new(&normal) ));
	Sgl$Buffer$initSize(normal, position->size) ;
	float *  normals = (float * )normal->data;
	SuiCore$Vec3 pA;
	SuiCore$Vec3 pB;
	SuiCore$Vec3 pC;
	SuiCore$Vec3 nA;
	SuiCore$Vec3 nB;
	SuiCore$Vec3 nC;
	for (int  i = 0; i < indexCount; i += 3) {
		int  vA = indexes[i] * 3;
		int  vB = indexes[i + 1] * 3;
		int  vC = indexes[i + 2] * 3;
		SuiCore$Vec3$fromArray(&pA, floats, vA) ;
		SuiCore$Vec3$fromArray(&pB, floats, vB) ;
		SuiCore$Vec3$fromArray(&pC, floats, vC) ;
		SuiCore$Vec3 cb = SuiCore$Vec3$sub(&pC, pB) ;
		SuiCore$Vec3 ab = SuiCore$Vec3$sub(&pA, pB) ;
		SuiCore$Vec3 nml = SuiCore$Vec3$cross(&cb, ab) ;
		SuiCore$Vec3$fromArray(&nA, normals, vA) ;
		SuiCore$Vec3$fromArray(&nB, normals, vB) ;
		SuiCore$Vec3$fromArray(&nC, normals, vC) ;
		SuiCore$Vec3$addLocal(&nA, nml) ;
		SuiCore$Vec3$addLocal(&nB, nml) ;
		SuiCore$Vec3$addLocal(&nC, nml) ;
		SuiCore$Vec3$toArray(&nA, normals, vA) ;
		SuiCore$Vec3$toArray(&nB, normals, vB) ;
		SuiCore$Vec3$toArray(&nC, normals, vC) ;
	}
	Sgl$Geometry_normalNormals(normal) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, normal) ; 
}

void  Sgl$Geometry_normalNormals(Sgl$Buffer *  buffer){
	float *  floats = (float * )buffer->data;
	int  floatCount = Sgl$Buffer$floatSize(buffer) ;
	SuiCore$Vec3 v3;
	for (int  i = 0; i < floatCount; i += 3) {
		v3.x = floats[i];
		v3.y = floats[i + 1];
		v3.z = floats[i + 2];
		SuiCore$Vec3 r = SuiCore$Vec3$normal(&v3) ;
		floats[i] = r.x;
		floats[i + 1] = r.y;
		floats[i + 2] = r.z;
	}
}

void  Sgl$testGeometry(){
	printf("====================test Geometry\n") ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  b = (b=NULL,urgc_init_var_class((void**)&b, Sgl$Buffer_new(&b) ));
		Sgl$Buffer$appendFloat3(b, 10, 10, 10) ;
		Sgl$Buffer$appendFloat3(b, 20, 20, 20) ;
		Sgl$Buffer$appendFloat3(b, 2, 0, 0) ;
		Sgl$Buffer$appendFloat3(b, 0, 1, 0) ;
		Sgl$Buffer$appendFloat3(b, 0, 0, 1) ;
		Sgl$Buffer$appendFloat3(b, 0, 0, 0) ;
		Sgl$Geometry_normalNormals(b) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("b:%s\n", Sgl$Buffer$toFloatString(&tmpReturn_1, b) ->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  b = (b=NULL,urgc_init_var_class((void**)&b, Sgl$Buffer_new(&b) ));
		Sgl$Buffer$appendFloat3(b, -0.5, -0.5, 0) ;
		Sgl$Buffer$appendFloat3(b, 0.5, -0.5, 0) ;
		Sgl$Buffer$appendFloat3(b, 0.5, 0.5, 0) ;
		Sgl$Buffer$appendFloat3(b, -0.5, 0.5, 0) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  f = (f=NULL,urgc_init_var_class((void**)&f, Sgl$Buffer_new(&f) ));
		Sgl$Buffer$appendInt3(f, 0, 1, 3) ;
		Sgl$Buffer$appendInt3(f, 1, 2, 3) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = Sgl$Geometry_computeVertexNormals((nmls = NULL,&nmls), f, b) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		printf("nmls:%s\n", Sgl$Buffer$toFloatString(&tmpReturn_2, nmls) ->str) ;
	}
}



