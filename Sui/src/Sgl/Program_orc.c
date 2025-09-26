
#include "Program_orc.h" 

#include <stdio.h>
#include <stdlib.h>
#include "./UnitOpengl.h"
#include "../Orc/Path_orc.h"
#include "../Orc/String_orc.h"
#include "../Sui/Core/Timer_orc.h"


// static struct 
typedef struct tagSgl$__Block_22_19 Sgl$__Block_22_19;

typedef struct tagSgl$__Closure_25_27 Sgl$__Closure_25_27;



struct tagSgl$__Block_22_19 {
	GLuint id ;
};





struct tagSgl$__Closure_25_27 {
	void  (*invoke)(Sgl$__Closure_25_27 *  self);
	Vtable_Object *  vtable ;
	Sgl$__Block_22_19*  __var___Block_22_19 ;
};





// static function declaration
static void  __finiBlock___Block_22_19(Sgl$__Block_22_19 *  self);
static void  __fn___Closure_25_27(Sgl$__Closure_25_27 *  self);
static void  __fini___Closure_25_27(Sgl$__Closure_25_27 *  self);
static Sgl$__Closure_25_27*  __make___Closure_25_27(Sgl$__Closure_25_27 **  __outRef__, Sgl$__Block_22_19 *  __var___Block_22_19);



//vtable instance
Vtable_Sgl$Program _vtable_Sgl$Program;

// init meta

void Sgl$Program_initMeta(Vtable_Sgl$Program *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "vsPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Program, vsPath), true, false, 1);
	orc_metaField_class(&pNext, "fsPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Program, fsPath), true, false, 1);

	orc_metaField_method(&pNext, "use", offsetof(Sgl$Program, use));
	orc_metaField_method(&pNext, "getVsPathCstr", offsetof(Sgl$Program, getVsPathCstr));
	orc_metaField_method(&pNext, "getFsPathCstr", offsetof(Sgl$Program, getFsPathCstr));
	orc_metaField_method(&pNext, "compile", offsetof(Sgl$Program, compile));
	orc_metaField_method(&pNext, "compileByPathCstr", offsetof(Sgl$Program, compileByPathCstr));
	orc_metaField_method(&pNext, "uniform1i", offsetof(Sgl$Program, uniform1i));
	orc_metaField_method(&pNext, "uniform2f", offsetof(Sgl$Program, uniform2f));
	orc_metaField_method(&pNext, "uniform3f", offsetof(Sgl$Program, uniform3f));
	orc_metaField_method(&pNext, "uniform4f", offsetof(Sgl$Program, uniform4f));
	orc_metaField_method(&pNext, "uniformMatrix4f", offsetof(Sgl$Program, uniformMatrix4f));
	orc_metaField_method(&pNext, "uniformMatrix4fv", offsetof(Sgl$Program, uniformMatrix4fv));
}


// vtable init


Vtable_Sgl$Program* Vtable_Sgl$Program_init(Vtable_Sgl$Program* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Program;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Program_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Program";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Program_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Program_fini(Sgl$Program *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Program_init_fields(Sgl$Program *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Program_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Program*)self)->vsPath, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Program*)self)->fsPath, NULL);
    }
	((Object*)self)->dtor = (void*)Sgl$Program$dtor;
	((Sgl$Program*)self)->use = (void*)Sgl$Program$use;
	((Sgl$Program*)self)->getVsPathCstr = (void*)Sgl$Program$getVsPathCstr;
	((Sgl$Program*)self)->getFsPathCstr = (void*)Sgl$Program$getFsPathCstr;
	((Sgl$Program*)self)->compile = (void*)Sgl$Program$compile;
	((Sgl$Program*)self)->compileByPathCstr = (void*)Sgl$Program$compileByPathCstr;
	((Sgl$Program*)self)->uniform1i = (void*)Sgl$Program$uniform1i;
	((Sgl$Program*)self)->uniform2f = (void*)Sgl$Program$uniform2f;
	((Sgl$Program*)self)->uniform3f = (void*)Sgl$Program$uniform3f;
	((Sgl$Program*)self)->uniform4f = (void*)Sgl$Program$uniform4f;
	((Sgl$Program*)self)->uniformMatrix4f = (void*)Sgl$Program$uniformMatrix4f;
	((Sgl$Program*)self)->uniformMatrix4fv = (void*)Sgl$Program$uniformMatrix4fv;
}

// init function

void Sgl$Program_init(Sgl$Program *self, void *pOwner){
    Vtable_Sgl$Program_init(&_vtable_Sgl$Program);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Program;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Program_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Program * Sgl$Program_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Program *self = calloc(1, sizeof(Sgl$Program));
	
    Sgl$Program_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Program$dtor(Sgl$Program *  self){
	if (self->id) {
		URGC_VAR_CLEANUP Sgl$__Block_22_19*  __var___Block_22_19 = (__var___Block_22_19=NULL,urgc_init_var((void**)&__var___Block_22_19, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_22_19) , __finiBlock___Block_22_19) ));
		__var___Block_22_19->id = self->id;
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP Sgl$__Closure_25_27*  tmpReturn_2 = NULL;
		SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_25_27(&tmpReturn_2, __var___Block_22_19) , 0) ;
	}
}


const char *  Sgl$Program$getVsPathCstr(Sgl$Program *  self){
	if (self->vsPath) {
		return self->vsPath->str; 
	}
	return ""; 
}


const char *  Sgl$Program$getFsPathCstr(Sgl$Program *  self){
	if (self->fsPath) {
		return self->fsPath->str; 
	}
	return ""; 
}


bool  Sgl$Program$compileByPathCstr(Sgl$Program *  self, const char *  vsPath, const char *  fsPath){
	URGC_VAR_CLEANUP_CLASS Orc$String*  vs = Orc$Path_readText((vs = NULL,&vs), vsPath) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  fs = Orc$Path_readText((fs = NULL,&fs), fsPath) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Program, vsPath) , Orc$str(&tmpReturn_1, vsPath) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Program, fsPath) , Orc$str(&tmpReturn_2, fsPath) ) ;
	bool  ok = self->compile(self, vs->str, fs->str) ;
	if (!ok) {
		printf("编译shader失败. path:%s/.fs\n", vsPath) ;
		exit(0) ;
	}
	return ok; 
}


void  Sgl$Program$uniformMatrix4f(Sgl$Program *  self, const char *  key, float *  data){
	self->uniformMatrix4fv(self, key, data, 1) ;
}



static void  __finiBlock___Block_22_19(Sgl$__Block_22_19 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_25_27(Sgl$__Closure_25_27 *  self){
	Sgl$deleteProgram(self->__var___Block_22_19->id) ;
}

static void  __fini___Closure_25_27(Sgl$__Closure_25_27 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_25_27, __var___Block_22_19) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_25_27*  __make___Closure_25_27(Sgl$__Closure_25_27 **  __outRef__, Sgl$__Block_22_19 *  __var___Block_22_19){
	URGC_VAR_CLEANUP Sgl$__Closure_25_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_25_27) , __fini___Closure_25_27) ));
	self->invoke = __fn___Closure_25_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_25_27, __var___Block_22_19) , __var___Block_22_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



