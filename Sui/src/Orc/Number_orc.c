
#include "Number_orc.h" 

#include "./Orc.h"
#include <string.h>
#include <stdio.h>
#include "./String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Orc$Number _vtable_Orc$Number;

// init meta

void Orc$Number_initMeta(Vtable_Orc$Number *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "toString", offsetof(Orc$Number, toString));
	orc_metaField_method(&pNext, "toLongLong", offsetof(Orc$Number, toLongLong));
	orc_metaField_method(&pNext, "toInt", offsetof(Orc$Number, toInt));
	orc_metaField_method(&pNext, "toDouble", offsetof(Orc$Number, toDouble));
	orc_metaField_method(&pNext, "toFloat", offsetof(Orc$Number, toFloat));
}


// vtable init


Vtable_Orc$Number* Vtable_Orc$Number_init(Vtable_Orc$Number* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Number;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Number_new;
    ((Vtable_Object*)pvt)->className = "Orc$Number";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Number_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Orc$Number_fini(Orc$Number *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Orc$Number_init_fields(Orc$Number *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$Number_fini;
	//fields
    {
	
    }
	((Orc$Number*)self)->toString = (void*)Orc$Number$toString;
	((Orc$Number*)self)->toLongLong = (void*)Orc$Number$toLongLong;
	((Orc$Number*)self)->toInt = (void*)Orc$Number$toInt;
	((Orc$Number*)self)->toDouble = (void*)Orc$Number$toDouble;
	((Orc$Number*)self)->toFloat = (void*)Orc$Number$toFloat;
}

// init function

void Orc$Number_init(Orc$Number *self, void *pOwner){
    Vtable_Orc$Number_init(&_vtable_Orc$Number);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Number;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Number_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Number * Orc$Number_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Number *self = calloc(1, sizeof(Orc$Number));
	
    Orc$Number_init(self, pOwner);
    return self;
}


// class members
Orc$String*  Orc$Number$toString(Orc$String **  __outRef__, Orc$Number *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, "") ) ; 
}


long long  Orc$Number$toLongLong(Orc$Number *  self){
	return 0; 
}


int  Orc$Number$toInt(Orc$Number *  self){
	return 0; 
}


double  Orc$Number$toDouble(Orc$Number *  self){
	return 0; 
}


float  Orc$Number$toFloat(Orc$Number *  self){
	return 0; 
}




//vtable instance
Vtable_Orc$Integer _vtable_Orc$Integer;

// init meta

void Orc$Integer_initMeta(Vtable_Orc$Integer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_int, offsetof(Orc$Integer, value), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Orc$Integer* Vtable_Orc$Integer_init(Vtable_Orc$Integer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Integer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Orc$Number_init(&_vtable_Orc$Number);

	// init by super vtable init function
    Vtable_Orc$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Orc$Number;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Integer_new;
    ((Vtable_Object*)pvt)->className = "Orc$Integer";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Integer_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Orc$Integer_fini(Orc$Integer *self){
	//super fini
    Orc$Number_fini((Orc$Number *)self);

    //字段释放


}

// init fields function


void Orc$Integer_init_fields(Orc$Integer *self){
	//super class
    Orc$Number_init_fields((Orc$Number*)self);

    ((Object*)self)->fini = (void*)Orc$Integer_fini;
	//fields
    {
	((Orc$Integer*)self)->value = 0;
    }
	((Orc$Number*)self)->toString = (void*)Orc$Integer$toString;
	((Orc$Number*)self)->toLongLong = (void*)Orc$Integer$toLongLong;
	((Orc$Number*)self)->toInt = (void*)Orc$Integer$toInt;
	((Orc$Number*)self)->toDouble = (void*)Orc$Integer$toDouble;
	((Orc$Number*)self)->toFloat = (void*)Orc$Integer$toFloat;
}

// init function

void Orc$Integer_init(Orc$Integer *self, void *pOwner){
    Vtable_Orc$Integer_init(&_vtable_Orc$Integer);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Integer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Integer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Integer * Orc$Integer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Integer *self = calloc(1, sizeof(Orc$Integer));
	
    Orc$Integer_init(self, pOwner);
    return self;
}


// class members
Orc$String*  Orc$Integer$toString(Orc$String **  __outRef__, Orc$Integer *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addi(Orc$str(&tmpReturn_1, "") , self->value) ) ; 
}


int  Orc$Integer$toLongLong(Orc$Integer *  self){
	return self->value; 
}


int  Orc$Integer$toInt(Orc$Integer *  self){
	return self->value; 
}


double  Orc$Integer$toDouble(Orc$Integer *  self){
	return (double )self->value; 
}


float  Orc$Integer$toFloat(Orc$Integer *  self){
	return (float )self->value; 
}




//vtable instance
Vtable_Orc$Boolean _vtable_Orc$Boolean;

// init meta

void Orc$Boolean_initMeta(Vtable_Orc$Boolean *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_bool, offsetof(Orc$Boolean, value), 0, 0, 0, 0);//bool

	
}


// vtable init


Vtable_Orc$Boolean* Vtable_Orc$Boolean_init(Vtable_Orc$Boolean* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Boolean;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Orc$Number_init(&_vtable_Orc$Number);

	// init by super vtable init function
    Vtable_Orc$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Orc$Number;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Boolean_new;
    ((Vtable_Object*)pvt)->className = "Orc$Boolean";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Boolean_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Orc$Boolean_fini(Orc$Boolean *self){
	//super fini
    Orc$Number_fini((Orc$Number *)self);

    //字段释放


}

// init fields function


void Orc$Boolean_init_fields(Orc$Boolean *self){
	//super class
    Orc$Number_init_fields((Orc$Number*)self);

    ((Object*)self)->fini = (void*)Orc$Boolean_fini;
	//fields
    {
	((Orc$Boolean*)self)->value = false;
    }
	((Orc$Number*)self)->toString = (void*)Orc$Boolean$toString;
	((Orc$Number*)self)->toLongLong = (void*)Orc$Boolean$toLongLong;
	((Orc$Number*)self)->toInt = (void*)Orc$Boolean$toInt;
	((Orc$Number*)self)->toDouble = (void*)Orc$Boolean$toDouble;
	((Orc$Number*)self)->toFloat = (void*)Orc$Boolean$toFloat;
}

// init function

void Orc$Boolean_init(Orc$Boolean *self, void *pOwner){
    Vtable_Orc$Boolean_init(&_vtable_Orc$Boolean);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Boolean;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Boolean_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Boolean * Orc$Boolean_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Boolean *self = calloc(1, sizeof(Orc$Boolean));
	
    Orc$Boolean_init(self, pOwner);
    return self;
}


// class members
Orc$String*  Orc$Boolean$toString(Orc$String **  __outRef__, Orc$Boolean *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$add(Orc$str(&tmpReturn_1, "") , self->value ? "true" : "false") ) ; 
}


long long  Orc$Boolean$toLongLong(Orc$Boolean *  self){
	return self->value; 
}


int  Orc$Boolean$toInt(Orc$Boolean *  self){
	return self->value; 
}


double  Orc$Boolean$toDouble(Orc$Boolean *  self){
	return self->value; 
}


float  Orc$Boolean$toFloat(Orc$Boolean *  self){
	return (float )self->value; 
}




//vtable instance
Vtable_Orc$Float _vtable_Orc$Float;

// init meta

void Orc$Float_initMeta(Vtable_Orc$Float *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_float, offsetof(Orc$Float, value), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_Orc$Float* Vtable_Orc$Float_init(Vtable_Orc$Float* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Float;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Orc$Number_init(&_vtable_Orc$Number);

	// init by super vtable init function
    Vtable_Orc$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Orc$Number;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Float_new;
    ((Vtable_Object*)pvt)->className = "Orc$Float";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Float_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Orc$Float_fini(Orc$Float *self){
	//super fini
    Orc$Number_fini((Orc$Number *)self);

    //字段释放


}

// init fields function


void Orc$Float_init_fields(Orc$Float *self){
	//super class
    Orc$Number_init_fields((Orc$Number*)self);

    ((Object*)self)->fini = (void*)Orc$Float_fini;
	//fields
    {
	((Orc$Float*)self)->value = 0;
    }
	((Orc$Number*)self)->toString = (void*)Orc$Float$toString;
	((Orc$Number*)self)->toLongLong = (void*)Orc$Float$toLongLong;
	((Orc$Number*)self)->toInt = (void*)Orc$Float$toInt;
	((Orc$Number*)self)->toDouble = (void*)Orc$Float$toDouble;
	((Orc$Number*)self)->toFloat = (void*)Orc$Float$toFloat;
}

// init function

void Orc$Float_init(Orc$Float *self, void *pOwner){
    Vtable_Orc$Float_init(&_vtable_Orc$Float);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Float;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Float_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Float * Orc$Float_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Float *self = calloc(1, sizeof(Orc$Float));
	
    Orc$Float_init(self, pOwner);
    return self;
}


// class members
Orc$String*  Orc$Float$toString(Orc$String **  __outRef__, Orc$Float *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addf(Orc$str(&tmpReturn_1, "") , self->value) ) ; 
}


long long  Orc$Float$toLongLong(Orc$Float *  self){
	return self->value; 
}


int  Orc$Float$toInt(Orc$Float *  self){
	return self->value; 
}


double  Orc$Float$toDouble(Orc$Float *  self){
	return self->value; 
}


float  Orc$Float$toFloat(Orc$Float *  self){
	return (float )self->value; 
}




//vtable instance
Vtable_Orc$Double _vtable_Orc$Double;

// init meta

void Orc$Double_initMeta(Vtable_Orc$Double *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_double, offsetof(Orc$Double, value), 0, 0, 0, 0);//double

	
}


// vtable init


Vtable_Orc$Double* Vtable_Orc$Double_init(Vtable_Orc$Double* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$Double;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Orc$Number_init(&_vtable_Orc$Number);

	// init by super vtable init function
    Vtable_Orc$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Orc$Number;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$Double_new;
    ((Vtable_Object*)pvt)->className = "Orc$Double";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$Double_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Orc$Double_fini(Orc$Double *self){
	//super fini
    Orc$Number_fini((Orc$Number *)self);

    //字段释放


}

// init fields function


void Orc$Double_init_fields(Orc$Double *self){
	//super class
    Orc$Number_init_fields((Orc$Number*)self);

    ((Object*)self)->fini = (void*)Orc$Double_fini;
	//fields
    {
	((Orc$Double*)self)->value = 0;
    }
	((Orc$Number*)self)->toString = (void*)Orc$Double$toString;
	((Orc$Number*)self)->toLongLong = (void*)Orc$Double$toLongLong;
	((Orc$Number*)self)->toInt = (void*)Orc$Double$toInt;
	((Orc$Number*)self)->toDouble = (void*)Orc$Double$toDouble;
	((Orc$Number*)self)->toFloat = (void*)Orc$Double$toFloat;
}

// init function

void Orc$Double_init(Orc$Double *self, void *pOwner){
    Vtable_Orc$Double_init(&_vtable_Orc$Double);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$Double;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$Double_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$Double * Orc$Double_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$Double *self = calloc(1, sizeof(Orc$Double));
	
    Orc$Double_init(self, pOwner);
    return self;
}


// class members
Orc$String*  Orc$Double$toString(Orc$String **  __outRef__, Orc$Double *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addf(Orc$str(&tmpReturn_1, "") , self->value) ) ; 
}


long long  Orc$Double$toLongLong(Orc$Double *  self){
	return self->value; 
}


int  Orc$Double$toInt(Orc$Double *  self){
	return self->value; 
}


double  Orc$Double$toDouble(Orc$Double *  self){
	return self->value; 
}


float  Orc$Double$toFloat(Orc$Double *  self){
	return (float )self->value; 
}




//vtable instance
Vtable_Orc$StructObj _vtable_Orc$StructObj;

// init meta

void Orc$StructObj_initMeta(Vtable_Orc$StructObj *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "pStruct", OrcMetaType_void, offsetof(Orc$StructObj, pStruct), 0, 0, 1, 1);//void

	orc_metaField_method(&pNext, "copyTo", offsetof(Orc$StructObj, copyTo));
}


// vtable init


Vtable_Orc$StructObj* Vtable_Orc$StructObj_init(Vtable_Orc$StructObj* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Orc$StructObj;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Orc$StructObj_new;
    ((Vtable_Object*)pvt)->className = "Orc$StructObj";

    ((Vtable_Object*)pvt)->initMeta = (void*)Orc$StructObj_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Orc$StructObj_fini(Orc$StructObj *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Orc$StructObj_init_fields(Orc$StructObj *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Orc$StructObj_fini;
	//fields
    {
	
    }
	((Object*)self)->dtor = (void*)Orc$StructObj$dtor;
	((Orc$StructObj*)self)->copyTo = (void*)Orc$StructObj$copyTo;
}

// init function

void Orc$StructObj_init(Orc$StructObj *self, void *pOwner){
    Vtable_Orc$StructObj_init(&_vtable_Orc$StructObj);

    ((Object*)self)->vtable = (void*)&_vtable_Orc$StructObj;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Orc$StructObj_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Orc$StructObj * Orc$StructObj_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Orc$StructObj *self = calloc(1, sizeof(Orc$StructObj));
	
    Orc$StructObj_init(self, pOwner);
    return self;
}


// class members
void  Orc$StructObj$dtor(Orc$StructObj *  self){
	if (self->pStruct) {
		free(self->pStruct) ;
		self->pStruct = NULL;
	}
}


void  Orc$StructObj$copyTo(Orc$StructObj *  self, void *  dst){
	if (dst) {
		memcpy(dst, self->pStruct, self->metaStruct->size) ;
	}
}



Orc$StructObj*  Orc$mkStructObj(Orc$StructObj **  __outRef__, MetaStruct *  metaStruct, void *  pStruct){
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  sobj = (sobj=NULL,urgc_init_var_class((void**)&sobj, Orc$StructObj_new(&sobj) ));
	sobj->pStruct = MetaStruct_dupStruct(metaStruct, pStruct) ;
	sobj->metaStruct = metaStruct;
	return urgc_set_var_for_return_class((void ** )__outRef__, sobj) ; 
}

Orc$Integer*  Orc$mkInteger(Orc$Integer **  __outRef__, int  v){
	URGC_VAR_CLEANUP_CLASS Orc$Integer*  o = (o=NULL,urgc_init_var_class((void**)&o, Orc$Integer_new(&o) ));
	o->value = v;
	return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
}

Orc$Boolean*  Orc$mkBoolean(Orc$Boolean **  __outRef__, bool  v){
	URGC_VAR_CLEANUP_CLASS Orc$Boolean*  o = (o=NULL,urgc_init_var_class((void**)&o, Orc$Boolean_new(&o) ));
	o->value = v;
	return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
}

Orc$Double*  Orc$mkDouble(Orc$Double **  __outRef__, double  v){
	URGC_VAR_CLEANUP_CLASS Orc$Double*  o = (o=NULL,urgc_init_var_class((void**)&o, Orc$Double_new(&o) ));
	o->value = v;
	return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
}

Orc$Float*  Orc$mkFloat(Orc$Float **  __outRef__, float  val){
	URGC_VAR_CLEANUP_CLASS Orc$Float*  v = (v=NULL,urgc_init_var_class((void**)&v, Orc$Float_new(&v) ));
	v->value = val;
	return urgc_set_var_for_return_class((void ** )__outRef__, v) ; 
}

void  Orc$Orc_setField(Object *  obj, OrcMetaField *  mf, Object *  value){
	void *  p = OrcMetaField_getPtr(mf, obj) ;
	int  type = OrcMetaField_getType(mf) ;
	if (Orc_instanceof((Object*)value, (Vtable_Object*)Vtable_Orc$Number_init(NULL))) {
		Orc$Number *  num = (Orc$Number * )value;
		if (type == OrcMetaType_float) {
			*((float * )p) = num->toFloat(num) ;
		}
		else if (type == OrcMetaType_double) {
			*((double * )p) = num->toDouble(num) ;
		}
		else if (type == OrcMetaType_long_long) {
			*((long long * )p) = (long long )num->toLongLong(num) ;
		}
		else if (type == OrcMetaType_long) {
			*((long * )p) = (long )num->toLongLong(num) ;
		}
		else if (type == OrcMetaType_int) {
			*((int * )p) = num->toInt(num) ;
		}
		else if (type == OrcMetaType_char) {
			*((char * )p) = num->toInt(num) ;
		}
		else if (type == OrcMetaType_bool) {
			*((bool * )p) = num->toInt(num) ;
		}
	}
	else if (type == OrcMetaType_class) {
		if (mf->isRef) {
			urgc_set_field_class(obj, (void ** )p, value) ;
		}
		else if (mf->isPointer) {
			*((void ** )p) = value;
		}
	}
	else if (!mf->isPointer && !mf->isRef && Orc_instanceof((Object*)value, (Vtable_Object*)Vtable_Orc$StructObj_init(NULL))) {
		Orc$StructObj *  sobj = (Orc$StructObj * )value;
		sobj->copyTo(sobj, p) ;
	}
}



