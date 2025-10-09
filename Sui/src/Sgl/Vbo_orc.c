
#include "Vbo_orc.h" 

#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "../Sui/Core/Timer_orc.h"


// static struct 
typedef struct tagSgl$__Block_65_19 Sgl$__Block_65_19;

typedef struct tagSgl$__Closure_68_27 Sgl$__Closure_68_27;



struct tagSgl$__Block_65_19 {
	GLuint id ;
};





struct tagSgl$__Closure_68_27 {
	void  (*invoke)(Sgl$__Closure_68_27 *  self);
	Vtable_Object *  vtable ;
	Sgl$__Block_65_19*  __var___Block_65_19 ;
};





// static function declaration
static void  __finiBlock___Block_65_19(Sgl$__Block_65_19 *  self);
static void  __fn___Closure_68_27(Sgl$__Closure_68_27 *  self);
static void  __fini___Closure_68_27(Sgl$__Closure_68_27 *  self);
static Sgl$__Closure_68_27*  __make___Closure_68_27(Sgl$__Closure_68_27 **  __outRef__, Sgl$__Block_65_19 *  __var___Block_65_19);



//vtable instance
Vtable_Sgl$Vbo _vtable_Sgl$Vbo;

// init meta

void Sgl$Vbo_initMeta(Vtable_Sgl$Vbo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "byteSize", OrcMetaType_int, offsetof(Sgl$Vbo, byteSize), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "elementCount", OrcMetaType_int, offsetof(Sgl$Vbo, elementCount), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "isFloat", OrcMetaType_bool, offsetof(Sgl$Vbo, isFloat), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isInt", OrcMetaType_bool, offsetof(Sgl$Vbo, isInt), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "vaIndex", OrcMetaType_int, offsetof(Sgl$Vbo, vaIndex), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "vaCount", OrcMetaType_int, offsetof(Sgl$Vbo, vaCount), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "divide", OrcMetaType_int, offsetof(Sgl$Vbo, divide), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "drawInstanceCount", OrcMetaType_int, offsetof(Sgl$Vbo, drawInstanceCount), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "isIndices", OrcMetaType_bool, offsetof(Sgl$Vbo, isIndices), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "buf", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$Vbo, buf), true, false, 1);

	orc_metaField_method(&pNext, "setInstancedRender", offsetof(Sgl$Vbo, setInstancedRender));
	orc_metaField_method(&pNext, "calcInstanceCount", offsetof(Sgl$Vbo, calcInstanceCount));
	orc_metaField_method(&pNext, "calcIndexCount", offsetof(Sgl$Vbo, calcIndexCount));
	orc_metaField_method(&pNext, "bind", offsetof(Sgl$Vbo, bind));
	orc_metaField_method(&pNext, "genBuffer", offsetof(Sgl$Vbo, genBuffer));
	orc_metaField_method(&pNext, "setVertexAttrib", offsetof(Sgl$Vbo, setVertexAttrib));
	orc_metaField_method(&pNext, "intArrayBuffer", offsetof(Sgl$Vbo, intArrayBuffer));
	orc_metaField_method(&pNext, "arrayBuffer", offsetof(Sgl$Vbo, arrayBuffer));
	orc_metaField_method(&pNext, "elementBuffer", offsetof(Sgl$Vbo, elementBuffer));
	orc_metaField_method(&pNext, "arrayBufferData", offsetof(Sgl$Vbo, arrayBufferData));
	orc_metaField_method(&pNext, "elementBufferData", offsetof(Sgl$Vbo, elementBufferData));
}


// vtable init


Vtable_Sgl$Vbo* Vtable_Sgl$Vbo_init(Vtable_Sgl$Vbo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Vbo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Vbo_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Vbo";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Vbo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Vbo_fini(Sgl$Vbo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Vbo*)self)->buf);

}

// init fields function


void Sgl$Vbo_init_fields(Sgl$Vbo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Vbo_fini;
	//fields
    {
	((Sgl$Vbo*)self)->usage = GL_STATIC_DRAW;
	((Sgl$Vbo*)self)->byteSize = 0;
	((Sgl$Vbo*)self)->elementCount = 3;
	((Sgl$Vbo*)self)->isFloat = true;
	((Sgl$Vbo*)self)->isInt = false;
	((Sgl$Vbo*)self)->vaIndex = 0;
	((Sgl$Vbo*)self)->vaCount = 1;
	((Sgl$Vbo*)self)->divide = 0;
	((Sgl$Vbo*)self)->drawInstanceCount = -1;
	((Sgl$Vbo*)self)->isIndices = false;
	urgc_set_field_class(self, (void**)&((Sgl$Vbo*)self)->buf, NULL);
    }
	((Sgl$Vbo*)self)->setInstancedRender = (void*)Sgl$Vbo$setInstancedRender;
	((Sgl$Vbo*)self)->calcInstanceCount = (void*)Sgl$Vbo$calcInstanceCount;
	((Sgl$Vbo*)self)->calcIndexCount = (void*)Sgl$Vbo$calcIndexCount;
	((Object*)self)->ctor = (void*)Sgl$Vbo$ctor;
	((Object*)self)->dtor = (void*)Sgl$Vbo$dtor;
	((Sgl$Vbo*)self)->bind = (void*)Sgl$Vbo$bind;
	((Sgl$Vbo*)self)->genBuffer = (void*)Sgl$Vbo$genBuffer;
	((Sgl$Vbo*)self)->setVertexAttrib = (void*)Sgl$Vbo$setVertexAttrib;
	((Sgl$Vbo*)self)->intArrayBuffer = (void*)Sgl$Vbo$intArrayBuffer;
	((Sgl$Vbo*)self)->arrayBuffer = (void*)Sgl$Vbo$arrayBuffer;
	((Sgl$Vbo*)self)->elementBuffer = (void*)Sgl$Vbo$elementBuffer;
	((Sgl$Vbo*)self)->arrayBufferData = (void*)Sgl$Vbo$arrayBufferData;
	((Sgl$Vbo*)self)->elementBufferData = (void*)Sgl$Vbo$elementBufferData;
}

// init function

void Sgl$Vbo_init(Sgl$Vbo *self, void *pOwner){
    Vtable_Sgl$Vbo_init(&_vtable_Sgl$Vbo);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Vbo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Vbo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Vbo * Sgl$Vbo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Vbo *self = calloc(1, sizeof(Sgl$Vbo));
	
    Sgl$Vbo_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Vbo$setInstancedRender(Sgl$Vbo *  self, int  elementCount, int  drawInstanceCount){
	self->elementCount = elementCount;
	self->divide = 1;
	self->usage = GL_DYNAMIC_DRAW;
	self->drawInstanceCount = drawInstanceCount;
}


int  Sgl$Vbo$calcInstanceCount(Sgl$Vbo *  self){
	if (self->drawInstanceCount >= 0) {
		return self->drawInstanceCount; 
	}
	if (self->divide > 0 && !self->isIndices) {
		if (self->isFloat || self->isInt) {
			int  totalVertexCount = self->byteSize / (self->elementCount * 4);
			return totalVertexCount; 
		}
	}
	return 1; 
}


int  Sgl$Vbo$calcIndexCount(Sgl$Vbo *  self){
	return self->byteSize / 4; 
}


void  Sgl$Vbo$ctor(Sgl$Vbo *  self){
	self->genBuffer(self) ;
}


void  Sgl$Vbo$dtor(Sgl$Vbo *  self){
	if (self->id) {
		URGC_VAR_CLEANUP Sgl$__Block_65_19*  __var___Block_65_19 = (__var___Block_65_19=NULL,urgc_init_var((void**)&__var___Block_65_19, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_65_19) , __finiBlock___Block_65_19) ));
		__var___Block_65_19->id = self->id;
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP Sgl$__Closure_68_27*  tmpReturn_2 = NULL;
		SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_68_27(&tmpReturn_2, __var___Block_65_19) , 0) ;
	}
}


void  Sgl$Vbo$intArrayBuffer(Sgl$Vbo *  self, Sgl$Buffer *  buf){
	if (buf && buf->data) {
		urgc_set_field_class(self, (void * )offsetof(Sgl$Vbo, buf) , buf) ;
		self->isInt = true;
		self->isFloat = false;
		self->arrayBufferData(self, buf->size, (float * )buf->data) ;
	}
}


void  Sgl$Vbo$arrayBuffer(Sgl$Vbo *  self, Sgl$Buffer *  buf){
	if (buf && buf->data && buf->size > 0) {
		urgc_set_field_class(self, (void * )offsetof(Sgl$Vbo, buf) , buf) ;
		self->arrayBufferData(self, buf->size, (float * )buf->data) ;
	}
}


void  Sgl$Vbo$elementBuffer(Sgl$Vbo *  self, Sgl$Buffer *  buf){
	if (buf && buf->data && buf->size > 0) {
		urgc_set_field_class(self, (void * )offsetof(Sgl$Vbo, buf) , buf) ;
		self->elementBufferData(self, buf->size, (int * )buf->data) ;
	}
}



static void  __finiBlock___Block_65_19(Sgl$__Block_65_19 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_68_27(Sgl$__Closure_68_27 *  self){
	Sgl$deleteBuffer(self->__var___Block_65_19->id) ;
}

static void  __fini___Closure_68_27(Sgl$__Closure_68_27 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_68_27, __var___Block_65_19) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_68_27*  __make___Closure_68_27(Sgl$__Closure_68_27 **  __outRef__, Sgl$__Block_65_19 *  __var___Block_65_19){
	URGC_VAR_CLEANUP Sgl$__Closure_68_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_68_27) , __fini___Closure_68_27) ));
	self->invoke = __fn___Closure_68_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_68_27, __var___Block_65_19) , __var___Block_65_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



