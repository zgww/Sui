
#include "Orc.h"
#include "Scope_orc.h" 



// static struct 


// static function declaration



//vtable instance
Vtable_Test$User _vtable_Test$User;

// init meta

void Test$User_initMeta(Vtable_Test$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "__exit__", offsetof(Test$User, __exit__));
}


// vtable init


Vtable_Test$User* Vtable_Test$User_init(Vtable_Test$User* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Test$User;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Test$User_new;
    ((Vtable_Object*)pvt)->className = "Test$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)Test$User_initMeta;

    return pvt;
}


// fini function

void Test$User_fini(Test$User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Test$User_init_fields(Test$User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Test$User_fini;
	//fields
    {
	
    }
	((Test$User*)self)->__exit__ = (void*)Test$User$__exit__;
}

// init function

void Test$User_init(Test$User *self){
    Vtable_Test$User_init(&_vtable_Test$User);

    ((Object*)self)->vtable = (void*)&_vtable_Test$User;

    urgc_guard(self, (void*)orc_delete);

    Test$User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    urgc_deguard(self);
}

// new function
Test$User * Test$User_new(){
    Test$User *self = calloc(1, sizeof(Test$User));
    Test$User_init(self);
    return self;
}


// class members
void *  Test$User$__exit__(Test$User *  self){
	
}



Test$User*  Test$div(Test$User **  __outRef__){
	return urgc_set_var_for_return((void ** )__outRef__, Test$User_new() ) ; 
}

void  Test$main(){
	URGC_VAR_CLEANUP Test$User*  tmpReturn_1 = NULL;
	{
		Test$User* __scopeVar_13_4 = Test$div(&tmpReturn_1) ; *o = __scopeVar_13_4;
		UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_13_4 = ((Test$User*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP Test$User*  tmpReturn_2 = NULL;
		{
			Test$User* __scopeVar_14_8 = Test$div(&tmpReturn_2) ; *o = __scopeVar_14_8;
			UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_14_8 = ((Test$User*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP Test$User*  tmpReturn_3 = NULL;
			{
				Test$User* __scopeVar_15_12 = Test$div(&tmpReturn_3, o) ; *o = __scopeVar_15_12;
				UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_15_12 = ((Test$User*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP Test$User*  tmpReturn_4 = NULL;
			{
				Test$User* __scopeVar_16_12 = Test$div(&tmpReturn_4) ; *o = __scopeVar_16_12;
				UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_16_12 = ((Test$User*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP Test$User*  tmpReturn_5 = NULL;
			{
				Test$User* __scopeVar_17_12 = Test$div(&tmpReturn_5) ; *o = __scopeVar_17_12;
				UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_17_12 = ((Test$User*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP Test$User*  tmpReturn_6 = NULL;
			{
				Test$User* __scopeVar_18_12 = Test$div(&tmpReturn_6) ; *o = __scopeVar_18_12;
				UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_18_12 = ((Test$User*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP Test$User*  tmpReturn_7 = NULL;
			{
				Test$User* __scopeVar_19_12 = Test$div(&tmpReturn_7) ; *o = __scopeVar_19_12;
				UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_19_12 = ((Test$User*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP Test$User*  tmpReturn_8 = NULL;
			{
				Test$User* __scopeVar_20_12 = Test$div(&tmpReturn_8) ; *o = __scopeVar_20_12;
				UNUSED DEFER(Orc_scopeExit) OrcLang$ScopeData __scopeObj_20_12 = ((Test$User*)o)->__exit__((void*)o);
			
				
			}
		}
	}
}



