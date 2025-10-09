
#include "BiJson_orc.h" 

#include "../../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
#include "../../Json/cJSON.h"
#include "../../Orc/Path_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Json/Json_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiDesigner$Inner_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiDesigner$Inner", sizeof( SuiDesigner$Inner ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "xx", OrcMetaType_int, offsetof(SuiDesigner$Inner, xx), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "yy", OrcMetaType_int, offsetof(SuiDesigner$Inner, yy), 0, 0, 0, 0);//int
    }
	return meta;
}

//vtable instance
Vtable_SuiDesigner$BiJsonExporter _vtable_SuiDesigner$BiJsonExporter;

// init meta

void SuiDesigner$BiJsonExporter_initMeta(Vtable_SuiDesigner$BiJsonExporter *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "obj", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiDesigner$BiJsonExporter, obj), false, true, 1);
	orc_metaField_plainStruct(&pNext, "jo", sizeof(cJSON), offsetof(SuiDesigner$BiJsonExporter, jo), false, true, 1);

	orc_metaField_method(&pNext, "exportFieldByOrcMetaField", offsetof(SuiDesigner$BiJsonExporter, exportFieldByOrcMetaField));
	orc_metaField_method(&pNext, "exportField", offsetof(SuiDesigner$BiJsonExporter, exportField));
	orc_metaField_method(&pNext, "exportFields", offsetof(SuiDesigner$BiJsonExporter, exportFields));
}


// vtable init


Vtable_SuiDesigner$BiJsonExporter* Vtable_SuiDesigner$BiJsonExporter_init(Vtable_SuiDesigner$BiJsonExporter* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$BiJsonExporter;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$BiJsonExporter_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$BiJsonExporter";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$BiJsonExporter_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$BiJsonExporter_fini(SuiDesigner$BiJsonExporter *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$BiJsonExporter_init_fields(SuiDesigner$BiJsonExporter *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$BiJsonExporter_fini;
	//fields
    {
	
    }
	((SuiDesigner$BiJsonExporter*)self)->exportFieldByOrcMetaField = (void*)SuiDesigner$BiJsonExporter$exportFieldByOrcMetaField;
	((SuiDesigner$BiJsonExporter*)self)->exportField = (void*)SuiDesigner$BiJsonExporter$exportField;
	((SuiDesigner$BiJsonExporter*)self)->exportFields = (void*)SuiDesigner$BiJsonExporter$exportFields;
}

// init function

void SuiDesigner$BiJsonExporter_init(SuiDesigner$BiJsonExporter *self, void *pOwner){
    Vtable_SuiDesigner$BiJsonExporter_init(&_vtable_SuiDesigner$BiJsonExporter);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$BiJsonExporter;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$BiJsonExporter_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$BiJsonExporter * SuiDesigner$BiJsonExporter_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$BiJsonExporter *self = calloc(1, sizeof(SuiDesigner$BiJsonExporter));
	
    SuiDesigner$BiJsonExporter_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$BiJsonExporter$exportFields(SuiDesigner$BiJsonExporter *  self, const char *  fieldsStr){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpstr = Orc$str((tmpstr = NULL,&tmpstr), fieldsStr) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  fields = Orc$String$splitByRe((fields = NULL,&fields), tmpstr, ",\\s*") ;
	for (int  i = 0; i < fields->size(fields) ; i++) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  field = (field=NULL,urgc_init_var_class((void**)&field, (Orc$String* )fields->get(fields, i) ));
		self->exportField(self, field->str) ;
	}
}




//vtable instance
Vtable_SuiDesigner$User _vtable_SuiDesigner$User;

// init meta

void SuiDesigner$User_initMeta(Vtable_SuiDesigner$User *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "go", OrcMetaType_float, offsetof(SuiDesigner$User, go), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "nice", OrcMetaType_double, offsetof(SuiDesigner$User, nice), 0, 0, 0, 0);//double

	orc_metaField_method(&pNext, "exportFields", offsetof(SuiDesigner$User, exportFields));
	orc_metaField_method(&pNext, "say", offsetof(SuiDesigner$User, say));
}


// vtable init


Vtable_SuiDesigner$User* Vtable_SuiDesigner$User_init(Vtable_SuiDesigner$User* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$User;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$User_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$User";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$User_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$User_fini(SuiDesigner$User *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$User_init_fields(SuiDesigner$User *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$User_fini;
	//fields
    {
	((SuiDesigner$User*)self)->go = 1.2;
	((SuiDesigner$User*)self)->nice = 234.2;
    }
	((SuiDesigner$User*)self)->exportFields = (void*)SuiDesigner$User$exportFields;
	((SuiDesigner$User*)self)->say = (void*)SuiDesigner$User$say;
}

// init function

void SuiDesigner$User_init(SuiDesigner$User *self, void *pOwner){
    Vtable_SuiDesigner$User_init(&_vtable_SuiDesigner$User);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$User;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$User_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$User * SuiDesigner$User_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$User *self = calloc(1, sizeof(SuiDesigner$User));
	
    SuiDesigner$User_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$User$exportFields(SuiDesigner$User *  self, SuiDesigner$BiJsonExporter *  exp){
	exp->exportFields(exp, "go,yy") ;
}


void  SuiDesigner$User$say(SuiDesigner$User *  self){
	printf(" iam user\n") ;
}




//vtable instance
Vtable_SuiDesigner$User2 _vtable_SuiDesigner$User2;

// init meta

void SuiDesigner$User2_initMeta(Vtable_SuiDesigner$User2 *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$User2* Vtable_SuiDesigner$User2_init(Vtable_SuiDesigner$User2* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$User2;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$User_init(&_vtable_SuiDesigner$User);

	// init by super vtable init function
    Vtable_SuiDesigner$User_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$User;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$User2_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$User2";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$User2_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$User2_fini(SuiDesigner$User2 *self){
	//super fini
    SuiDesigner$User_fini((SuiDesigner$User *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$User2_init_fields(SuiDesigner$User2 *self){
	//super class
    SuiDesigner$User_init_fields((SuiDesigner$User*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$User2_fini;
	//fields
    {
	
    }
	((SuiDesigner$User*)self)->say = (void*)SuiDesigner$User2$say;
}

// init function

void SuiDesigner$User2_init(SuiDesigner$User2 *self, void *pOwner){
    Vtable_SuiDesigner$User2_init(&_vtable_SuiDesigner$User2);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$User2;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$User2_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$User2 * SuiDesigner$User2_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$User2 *self = calloc(1, sizeof(SuiDesigner$User2));
	
    SuiDesigner$User2_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$User2$say(SuiDesigner$User2 *  self){
	printf(" iam user2\n") ;
}




//vtable instance
Vtable_SuiDesigner$TestBi _vtable_SuiDesigner$TestBi;

// init meta

void SuiDesigner$TestBi_initMeta(Vtable_SuiDesigner$TestBi *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "a", OrcMetaType_bool, offsetof(SuiDesigner$TestBi, a), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "b", OrcMetaType_char, offsetof(SuiDesigner$TestBi, b), 0, 0, 0, 0);//char
	orc_metaField_primitive(&pNext, "c", OrcMetaType_short, offsetof(SuiDesigner$TestBi, c), 0, 0, 0, 0);//short
	orc_metaField_primitive(&pNext, "d", OrcMetaType_int, offsetof(SuiDesigner$TestBi, d), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "e", OrcMetaType_long, offsetof(SuiDesigner$TestBi, e), 0, 0, 0, 0);//long
	orc_metaField_primitive(&pNext, "f", OrcMetaType_long_long, offsetof(SuiDesigner$TestBi, f), 0, 0, 0, 0);//longlong
	orc_metaField_primitive(&pNext, "g", OrcMetaType_float, offsetof(SuiDesigner$TestBi, g), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "h", OrcMetaType_double, offsetof(SuiDesigner$TestBi, h), 0, 0, 0, 0);//double
	orc_metaField_struct(&pNext, "inner", SuiDesigner$Inner_getOrInitMetaStruct(), offsetof(SuiDesigner$TestBi, inner), false, false, 0);
	orc_metaField_class(&pNext, "u", ((Vtable_Object*)Vtable_SuiDesigner$User_init(0)), offsetof(SuiDesigner$TestBi, u), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$TestBi* Vtable_SuiDesigner$TestBi_init(Vtable_SuiDesigner$TestBi* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$TestBi;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$TestBi_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$TestBi";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$TestBi_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$TestBi_fini(SuiDesigner$TestBi *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TestBi*)self)->u);

}

// init fields function


void SuiDesigner$TestBi_init_fields(SuiDesigner$TestBi *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$TestBi_fini;
	//fields
    {
	((SuiDesigner$TestBi*)self)->a = false;
	((SuiDesigner$TestBi*)self)->b = 0;
	((SuiDesigner$TestBi*)self)->c = 0;
	((SuiDesigner$TestBi*)self)->d = 0;
	((SuiDesigner$TestBi*)self)->e = 0;
	((SuiDesigner$TestBi*)self)->f = 0;
	((SuiDesigner$TestBi*)self)->g = 0;
	((SuiDesigner$TestBi*)self)->h = 0;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$User*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TestBi*)self)->u, SuiDesigner$User_new(&tmpNewOwner_1) );
    }
	
}

// init function

void SuiDesigner$TestBi_init(SuiDesigner$TestBi *self, void *pOwner){
    Vtable_SuiDesigner$TestBi_init(&_vtable_SuiDesigner$TestBi);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$TestBi;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$TestBi_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$TestBi * SuiDesigner$TestBi_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$TestBi *self = calloc(1, sizeof(SuiDesigner$TestBi));
	
    SuiDesigner$TestBi_init(self, pOwner);
    return self;
}


// class members

void  SuiDesigner$testBiJson(){
	SuiDesigner$BiJson_registerClass(Vtable_SuiDesigner$User2_init(NULL)) ;
	SuiDesigner$BiJson_registerClass(Vtable_SuiDesigner$User_init(NULL)) ;
	{
		printf("testBiJson 104\n") ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$TestBi*  t = (t=NULL,urgc_init_var_class((void**)&t, SuiDesigner$TestBi_new(&t) ));
		printf("testBiJson 106\n") ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  s = SuiDesigner$BiJson_toJsonString((s = NULL,&s), t) ;
		printf("testBiJson 108\n") ;
		Orc$Path_writeText("a.json", s->str) ;
		printf("testBiJson 110\n") ;
	}
	printf("testBiJson 111\n") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = Orc$Path_readText((text = NULL,&text), "a.json") ;
	printf("read Text:%s\n", text->str) ;
	URGC_VAR_CLEANUP_CLASS Object*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$TestBi*  bi = (bi=NULL,urgc_init_var_class((void**)&bi, (SuiDesigner$TestBi* )SuiDesigner$BiJson_fromJsonStringAndVtable(&tmpReturn_1, text->str, Vtable_SuiDesigner$TestBi_init(NULL)) ));
	printf("bi: a %d b %d  c %d d:%d, e:%ld, f:%lld, g:%f, h:%f. inner:%d,%d, u:%f,%f\n", bi->a, bi->b, bi->c, bi->d, bi->e, bi->f, bi->g, bi->h, bi->inner.xx, bi->inner.yy, bi->u->go, bi->u->nice) ;
	bi->u->say(bi->u) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = SuiDesigner$BiJson_toJsonString((s = NULL,&s), bi) ;
	printf("s:%s\n", s->str) ;
	if (0) {
		{
			URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "1") ;
			printf("jo kind:%d. %f\n", jo->kind, jo->numberValue) ;
		}
		{
			URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "true") ;
			printf("jo kind:%d, %d\n", jo->kind, jo->boolValue) ;
		}
		{
			URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "false") ;
			printf("jo kind:%d, %d\n", jo->kind, jo->boolValue) ;
		}
		{
			URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "null") ;
			printf("jo kind:%d\n", jo->kind) ;
		}
		{
			URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "\"hiskjdfsdfsd\"") ;
			printf("jo kind:%d, %s\n", jo->kind, jo->stringValue->str) ;
		}
		{
			URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "\"hiskjdfsdfs\\\"d\"") ;
			printf("jo kind:%d, %s\n", jo->kind, jo->stringValue->str) ;
		}
		{
			URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "[]") ;
			printf("jo kind:%d, %p. l:%d\n", jo->kind, jo->list, jo->arraySize(jo) ) ;
		}
	}
	{
		URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "[1, 2, 3]") ;
		printf("jo kind:%d, %p. l:%d items:%f,%f,%f; %d,%d,%d\n", jo->kind, jo->list, jo->arraySize(jo) , jo->atAsNumber(jo, 0) , jo->atAsNumber(jo, 1) , jo->atAsNumber(jo, 2) , jo->atAsInt(jo, 0) , jo->atAsInt(jo, 1) , jo->atAsInt(jo, 2) ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		printf("\tdump:%s\n", jo->dump(&tmpReturn_2, jo) ->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), "{\"id\":102, \"name\":34, \"pwd\":4}") ;
		printf("jo kind:%d, %p. l:%d items:%f,%f,%f; %d,%d,%d\n", jo->kind, jo->map, jo->keySize(jo) , jo->getNumber(jo, "id") , jo->getNumber(jo, "name") , jo->getNumber(jo, "pwd") , jo->getInt(jo, "id") , jo->getInt(jo, "name") , jo->getInt(jo, "pwd") ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		printf("\tdump:%s\n", jo->dump(&tmpReturn_3, jo) ->str) ;
	}
}



