
#include "Number_orc.h" 

#include "./String_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_OrcLang$Number _vtable_OrcLang$Number;

// init meta

void OrcLang$Number_initMeta(Vtable_OrcLang$Number *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "toString", offsetof(OrcLang$Number, toString));
	orc_metaField_method(&pNext, "toLongLong", offsetof(OrcLang$Number, toLongLong));
	orc_metaField_method(&pNext, "toInt", offsetof(OrcLang$Number, toInt));
	orc_metaField_method(&pNext, "toDouble", offsetof(OrcLang$Number, toDouble));
}


// vtable init


Vtable_OrcLang$Number* Vtable_OrcLang$Number_init(Vtable_OrcLang$Number* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Number;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Number_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Number";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Number_initMeta;

    return pvt;
}


// fini function

void OrcLang$Number_fini(OrcLang$Number *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void OrcLang$Number_init_fields(OrcLang$Number *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)OrcLang$Number_fini;
	//fields
    {
	
    }
	((OrcLang$Number*)self)->toString = (void*)OrcLang$Number$toString;
	((OrcLang$Number*)self)->toLongLong = (void*)OrcLang$Number$toLongLong;
	((OrcLang$Number*)self)->toInt = (void*)OrcLang$Number$toInt;
	((OrcLang$Number*)self)->toDouble = (void*)OrcLang$Number$toDouble;
}

// init function

void OrcLang$Number_init(OrcLang$Number *self){
    Vtable_OrcLang$Number_init(&_vtable_OrcLang$Number);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Number;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Number_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Number * OrcLang$Number_new(){
    OrcLang$Number *self = calloc(1, sizeof(OrcLang$Number));
    OrcLang$Number_init(self);
    return self;
}


// class members
OrcLang$String*  OrcLang$Number$toString(OrcLang$String **  __outRef__, OrcLang$Number *  self){
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, OrcLang$str(&tmpReturn_1, "") ) ; 
}


long long  OrcLang$Number$toLongLong(OrcLang$Number *  self){
	return 0; 
}


int  OrcLang$Number$toInt(OrcLang$Number *  self){
	return 0; 
}


double  OrcLang$Number$toDouble(OrcLang$Number *  self){
	return 0; 
}




//vtable instance
Vtable_OrcLang$Integer _vtable_OrcLang$Integer;

// init meta

void OrcLang$Integer_initMeta(Vtable_OrcLang$Integer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_int, offsetof(OrcLang$Integer, value), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_OrcLang$Integer* Vtable_OrcLang$Integer_init(Vtable_OrcLang$Integer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Integer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_OrcLang$Number_init(&_vtable_OrcLang$Number);

	// init by super vtable init function
    Vtable_OrcLang$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_OrcLang$Number;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Integer_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Integer";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Integer_initMeta;

    return pvt;
}


// fini function

void OrcLang$Integer_fini(OrcLang$Integer *self){
	//super fini
    OrcLang$Number_fini((OrcLang$Number *)self);

    //字段释放


}

// init fields function


void OrcLang$Integer_init_fields(OrcLang$Integer *self){
	//super class
    OrcLang$Number_init_fields((OrcLang$Number*)self);

    ((Object*)self)->fini = (void*)OrcLang$Integer_fini;
	//fields
    {
	((OrcLang$Integer*)self)->value = 0;
    }
	((OrcLang$Number*)self)->toString = (void*)OrcLang$Integer$toString;
	((OrcLang$Number*)self)->toLongLong = (void*)OrcLang$Integer$toLongLong;
	((OrcLang$Number*)self)->toInt = (void*)OrcLang$Integer$toInt;
	((OrcLang$Number*)self)->toDouble = (void*)OrcLang$Integer$toDouble;
}

// init function

void OrcLang$Integer_init(OrcLang$Integer *self){
    Vtable_OrcLang$Integer_init(&_vtable_OrcLang$Integer);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Integer;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Integer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Integer * OrcLang$Integer_new(){
    OrcLang$Integer *self = calloc(1, sizeof(OrcLang$Integer));
    OrcLang$Integer_init(self);
    return self;
}


// class members
OrcLang$String*  OrcLang$Integer$toString(OrcLang$String **  __outRef__, OrcLang$Integer *  self){
	OrcLang$String *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, (tmpThis_1 = OrcLang$str(&tmpReturn_1, "") )->addi(tmpThis_1, self->value) ) ; 
}


int  OrcLang$Integer$toLongLong(OrcLang$Integer *  self){
	return self->value; 
}


int  OrcLang$Integer$toInt(OrcLang$Integer *  self){
	return self->value; 
}


double  OrcLang$Integer$toDouble(OrcLang$Integer *  self){
	return self->value; 
}




//vtable instance
Vtable_OrcLang$Boolean _vtable_OrcLang$Boolean;

// init meta

void OrcLang$Boolean_initMeta(Vtable_OrcLang$Boolean *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_bool, offsetof(OrcLang$Boolean, value), 0, 0, 0, 0);//bool

	
}


// vtable init


Vtable_OrcLang$Boolean* Vtable_OrcLang$Boolean_init(Vtable_OrcLang$Boolean* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Boolean;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_OrcLang$Number_init(&_vtable_OrcLang$Number);

	// init by super vtable init function
    Vtable_OrcLang$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_OrcLang$Number;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Boolean_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Boolean";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Boolean_initMeta;

    return pvt;
}


// fini function

void OrcLang$Boolean_fini(OrcLang$Boolean *self){
	//super fini
    OrcLang$Number_fini((OrcLang$Number *)self);

    //字段释放


}

// init fields function


void OrcLang$Boolean_init_fields(OrcLang$Boolean *self){
	//super class
    OrcLang$Number_init_fields((OrcLang$Number*)self);

    ((Object*)self)->fini = (void*)OrcLang$Boolean_fini;
	//fields
    {
	((OrcLang$Boolean*)self)->value = false;
    }
	((OrcLang$Number*)self)->toString = (void*)OrcLang$Boolean$toString;
	((OrcLang$Number*)self)->toLongLong = (void*)OrcLang$Boolean$toLongLong;
	((OrcLang$Number*)self)->toInt = (void*)OrcLang$Boolean$toInt;
	((OrcLang$Number*)self)->toDouble = (void*)OrcLang$Boolean$toDouble;
}

// init function

void OrcLang$Boolean_init(OrcLang$Boolean *self){
    Vtable_OrcLang$Boolean_init(&_vtable_OrcLang$Boolean);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Boolean;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Boolean_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Boolean * OrcLang$Boolean_new(){
    OrcLang$Boolean *self = calloc(1, sizeof(OrcLang$Boolean));
    OrcLang$Boolean_init(self);
    return self;
}


// class members
OrcLang$String*  OrcLang$Boolean$toString(OrcLang$String **  __outRef__, OrcLang$Boolean *  self){
	OrcLang$String *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, (tmpThis_1 = OrcLang$str(&tmpReturn_1, "") )->add(tmpThis_1, self->value ? "true" : "false") ) ; 
}


long long  OrcLang$Boolean$toLongLong(OrcLang$Boolean *  self){
	return self->value; 
}


int  OrcLang$Boolean$toInt(OrcLang$Boolean *  self){
	return self->value; 
}


double  OrcLang$Boolean$toDouble(OrcLang$Boolean *  self){
	return self->value; 
}




//vtable instance
Vtable_OrcLang$Float _vtable_OrcLang$Float;

// init meta

void OrcLang$Float_initMeta(Vtable_OrcLang$Float *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_float, offsetof(OrcLang$Float, value), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_OrcLang$Float* Vtable_OrcLang$Float_init(Vtable_OrcLang$Float* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Float;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_OrcLang$Number_init(&_vtable_OrcLang$Number);

	// init by super vtable init function
    Vtable_OrcLang$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_OrcLang$Number;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Float_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Float";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Float_initMeta;

    return pvt;
}


// fini function

void OrcLang$Float_fini(OrcLang$Float *self){
	//super fini
    OrcLang$Number_fini((OrcLang$Number *)self);

    //字段释放


}

// init fields function


void OrcLang$Float_init_fields(OrcLang$Float *self){
	//super class
    OrcLang$Number_init_fields((OrcLang$Number*)self);

    ((Object*)self)->fini = (void*)OrcLang$Float_fini;
	//fields
    {
	((OrcLang$Float*)self)->value = 0;
    }
	((OrcLang$Number*)self)->toString = (void*)OrcLang$Float$toString;
	((OrcLang$Number*)self)->toLongLong = (void*)OrcLang$Float$toLongLong;
	((OrcLang$Number*)self)->toInt = (void*)OrcLang$Float$toInt;
	((OrcLang$Number*)self)->toDouble = (void*)OrcLang$Float$toDouble;
}

// init function

void OrcLang$Float_init(OrcLang$Float *self){
    Vtable_OrcLang$Float_init(&_vtable_OrcLang$Float);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Float;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Float_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Float * OrcLang$Float_new(){
    OrcLang$Float *self = calloc(1, sizeof(OrcLang$Float));
    OrcLang$Float_init(self);
    return self;
}


// class members
OrcLang$String*  OrcLang$Float$toString(OrcLang$String **  __outRef__, OrcLang$Float *  self){
	OrcLang$String *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, (tmpThis_1 = OrcLang$str(&tmpReturn_1, "") )->addf(tmpThis_1, self->value) ) ; 
}


long long  OrcLang$Float$toLongLong(OrcLang$Float *  self){
	return self->value; 
}


int  OrcLang$Float$toInt(OrcLang$Float *  self){
	return self->value; 
}


double  OrcLang$Float$toDouble(OrcLang$Float *  self){
	return self->value; 
}




//vtable instance
Vtable_OrcLang$Double _vtable_OrcLang$Double;

// init meta

void OrcLang$Double_initMeta(Vtable_OrcLang$Double *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_double, offsetof(OrcLang$Double, value), 0, 0, 0, 0);//double

	
}


// vtable init


Vtable_OrcLang$Double* Vtable_OrcLang$Double_init(Vtable_OrcLang$Double* pvt){
    if (pvt == NULL){
        pvt = &_vtable_OrcLang$Double;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_OrcLang$Number_init(&_vtable_OrcLang$Number);

	// init by super vtable init function
    Vtable_OrcLang$Number_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_OrcLang$Number;
    ((Vtable_Object*)pvt)->make = (void*)&OrcLang$Double_new;
    ((Vtable_Object*)pvt)->className = "OrcLang$Double";

    ((Vtable_Object*)pvt)->initMeta = (void*)OrcLang$Double_initMeta;

    return pvt;
}


// fini function

void OrcLang$Double_fini(OrcLang$Double *self){
	//super fini
    OrcLang$Number_fini((OrcLang$Number *)self);

    //字段释放


}

// init fields function


void OrcLang$Double_init_fields(OrcLang$Double *self){
	//super class
    OrcLang$Number_init_fields((OrcLang$Number*)self);

    ((Object*)self)->fini = (void*)OrcLang$Double_fini;
	//fields
    {
	((OrcLang$Double*)self)->value = 0;
    }
	((OrcLang$Number*)self)->toString = (void*)OrcLang$Double$toString;
	((OrcLang$Number*)self)->toLongLong = (void*)OrcLang$Double$toLongLong;
	((OrcLang$Number*)self)->toInt = (void*)OrcLang$Double$toInt;
	((OrcLang$Number*)self)->toDouble = (void*)OrcLang$Double$toDouble;
}

// init function

void OrcLang$Double_init(OrcLang$Double *self){
    Vtable_OrcLang$Double_init(&_vtable_OrcLang$Double);

    ((Object*)self)->vtable = (void*)&_vtable_OrcLang$Double;

    urgc_guard(self, (void*)orc_delete);

    OrcLang$Double_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
OrcLang$Double * OrcLang$Double_new(){
    OrcLang$Double *self = calloc(1, sizeof(OrcLang$Double));
    OrcLang$Double_init(self);
    return self;
}


// class members
OrcLang$String*  OrcLang$Double$toString(OrcLang$String **  __outRef__, OrcLang$Double *  self){
	OrcLang$String *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP OrcLang$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return((void ** )__outRef__, (tmpThis_1 = OrcLang$str(&tmpReturn_1, "") )->addf(tmpThis_1, self->value) ) ; 
}


long long  OrcLang$Double$toLongLong(OrcLang$Double *  self){
	return self->value; 
}


int  OrcLang$Double$toInt(OrcLang$Double *  self){
	return self->value; 
}


double  OrcLang$Double$toDouble(OrcLang$Double *  self){
	return self->value; 
}



OrcLang$Integer*  OrcLang$mkInteger(OrcLang$Integer **  __outRef__, int  v){
	URGC_VAR_CLEANUP OrcLang$Integer*  o = urgc_init_var((void**)&o, OrcLang$Integer_new() );
	o->value = v;
	return urgc_set_var_for_return((void ** )__outRef__, o) ; 
}

OrcLang$Boolean*  OrcLang$mkBoolean(OrcLang$Boolean **  __outRef__, bool  v){
	URGC_VAR_CLEANUP OrcLang$Boolean*  o = urgc_init_var((void**)&o, OrcLang$Boolean_new() );
	o->value = v;
	return urgc_set_var_for_return((void ** )__outRef__, o) ; 
}

OrcLang$Double*  OrcLang$mkDouble(OrcLang$Double **  __outRef__, double  v){
	URGC_VAR_CLEANUP OrcLang$Double*  o = urgc_init_var((void**)&o, OrcLang$Double_new() );
	o->value = v;
	return urgc_set_var_for_return((void ** )__outRef__, o) ; 
}

OrcLang$Float*  OrcLang$mkFloat(OrcLang$Float **  __outRef__, float  val){
	URGC_VAR_CLEANUP OrcLang$Float*  v = urgc_init_var((void**)&v, OrcLang$Float_new() );
	v->value = val;
	return urgc_set_var_for_return((void ** )__outRef__, v) ; 
}



