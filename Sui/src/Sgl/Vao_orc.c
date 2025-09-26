
#include "Vao_orc.h" 

#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "../Sui/Core/Timer_orc.h"


// static struct 
typedef struct tagSgl$__Block_33_19 Sgl$__Block_33_19;

typedef struct tagSgl$__Closure_36_27 Sgl$__Closure_36_27;



struct tagSgl$__Block_33_19 {
	GLuint id ;
};





struct tagSgl$__Closure_36_27 {
	void  (*invoke)(Sgl$__Closure_36_27 *  self);
	Vtable_Object *  vtable ;
	Sgl$__Block_33_19*  __var___Block_33_19 ;
};





// static function declaration
static void  __finiBlock___Block_33_19(Sgl$__Block_33_19 *  self);
static void  __fn___Closure_36_27(Sgl$__Closure_36_27 *  self);
static void  __fini___Closure_36_27(Sgl$__Closure_36_27 *  self);
static Sgl$__Closure_36_27*  __make___Closure_36_27(Sgl$__Closure_36_27 **  __outRef__, Sgl$__Block_33_19 *  __var___Block_33_19);



//vtable instance
Vtable_Sgl$Vao _vtable_Sgl$Vao;

// init meta

void Sgl$Vao_initMeta(Vtable_Sgl$Vao *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "material", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$Vao, material), true, false, 1);
	orc_metaField_class(&pNext, "geometry", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(Sgl$Vao, geometry), true, false, 1);
	orc_metaField_primitive(&pNext, "geometryVersion", OrcMetaType_int, offsetof(Sgl$Vao, geometryVersion), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "regen", offsetof(Sgl$Vao, regen));
	orc_metaField_method(&pNext, "isNeedBuild", offsetof(Sgl$Vao, isNeedBuild));
	orc_metaField_method(&pNext, "build", offsetof(Sgl$Vao, build));
	orc_metaField_method(&pNext, "gen", offsetof(Sgl$Vao, gen));
	orc_metaField_method(&pNext, "bind", offsetof(Sgl$Vao, bind));
	orc_metaField_method(&pNext, "unbind", offsetof(Sgl$Vao, unbind));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$Vao, draw));
	orc_metaField_method(&pNext, "drawInstanced", offsetof(Sgl$Vao, drawInstanced));
}


// vtable init


Vtable_Sgl$Vao* Vtable_Sgl$Vao_init(Vtable_Sgl$Vao* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Vao;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Vao_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Vao";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Vao_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Vao_fini(Sgl$Vao *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Vao_init_fields(Sgl$Vao *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Vao_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Vao*)self)->material, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Vao*)self)->geometry, NULL);
	((Sgl$Vao*)self)->id = 0;
	((Sgl$Vao*)self)->geometryVersion = 0;
    }
	((Sgl$Vao*)self)->regen = (void*)Sgl$Vao$regen;
	((Object*)self)->dtor = (void*)Sgl$Vao$dtor;
	((Sgl$Vao*)self)->isNeedBuild = (void*)Sgl$Vao$isNeedBuild;
	((Sgl$Vao*)self)->build = (void*)Sgl$Vao$build;
	((Sgl$Vao*)self)->gen = (void*)Sgl$Vao$gen;
	((Sgl$Vao*)self)->bind = (void*)Sgl$Vao$bind;
	((Sgl$Vao*)self)->unbind = (void*)Sgl$Vao$unbind;
	((Sgl$Vao*)self)->draw = (void*)Sgl$Vao$draw;
	((Sgl$Vao*)self)->drawInstanced = (void*)Sgl$Vao$drawInstanced;
}

// init function

void Sgl$Vao_init(Sgl$Vao *self, void *pOwner){
    Vtable_Sgl$Vao_init(&_vtable_Sgl$Vao);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Vao;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Vao_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Vao * Sgl$Vao_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Vao *self = calloc(1, sizeof(Sgl$Vao));
	
    Sgl$Vao_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Vao$regen(Sgl$Vao *  self){
	if (self->id) {
		Sgl$deleteVertexArray(self->id) ;
	}
	self->gen(self) ;
}


void  Sgl$Vao$dtor(Sgl$Vao *  self){
	if (self->id) {
		URGC_VAR_CLEANUP Sgl$__Block_33_19*  __var___Block_33_19 = (__var___Block_33_19=NULL,urgc_init_var((void**)&__var___Block_33_19, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_33_19) , __finiBlock___Block_33_19) ));
		__var___Block_33_19->id = self->id;
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP Sgl$__Closure_36_27*  tmpReturn_2 = NULL;
		SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_36_27(&tmpReturn_2, __var___Block_33_19) , 0) ;
	}
}


bool  Sgl$Vao$isNeedBuild(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  material){
	return material && geometry && (self->material != material || self->geometry != geometry || geometry->version != self->geometryVersion); 
}


bool  Sgl$Vao$build(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  material){
	if (self->isNeedBuild(self, geometry, material) ) {
		self->regen(self) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Vao, material) , material) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Vao, geometry) , geometry) ;
		self->material->program->use(self->material->program) ;
		self->bind(self) ;
		bool  ok = geometry->bindVertexAttribs(geometry, material) ;
		if (geometry->ibo) {
			geometry->ibo->bind(geometry->ibo) ;
		}
		self->geometryVersion = geometry->version;
		self->unbind(self) ;
		return ok; 
	}
	return true; 
}


void  Sgl$Vao$draw(Sgl$Vao *  self, Sgl$Geometry *  geometry, Sgl$Material *  matl){
	self->build(self, geometry, matl) ;
	self->material->program->use(self->material->program) ;
	self->bind(self) ;
	self->material->prepareDraw(self->material) ;
	self->material->updateUniforms(self->material) ;
	if (geometry->instanceVbo) {
		self->drawInstanced(self, geometry, matl) ;
	}
	else {
		int  indexCount = geometry->ibo->calcIndexCount(geometry->ibo) ;
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0) ;
	}
	self->material->endDraw(self->material) ;
	self->unbind(self) ;
}



static void  __finiBlock___Block_33_19(Sgl$__Block_33_19 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_36_27(Sgl$__Closure_36_27 *  self){
	Sgl$deleteVertexArray(self->__var___Block_33_19->id) ;
}

static void  __fini___Closure_36_27(Sgl$__Closure_36_27 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_36_27, __var___Block_33_19) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_36_27*  __make___Closure_36_27(Sgl$__Closure_36_27 **  __outRef__, Sgl$__Block_33_19 *  __var___Block_33_19){
	URGC_VAR_CLEANUP Sgl$__Closure_36_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_36_27) , __fini___Closure_36_27) ));
	self->invoke = __fn___Closure_36_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_36_27, __var___Block_33_19) , __var___Block_33_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



