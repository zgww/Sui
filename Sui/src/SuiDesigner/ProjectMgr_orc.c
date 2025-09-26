
#include "ProjectMgr_orc.h" 

#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/List_orc.h"
#include "../Json/Json_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$ProjectInfo _vtable_SuiDesigner$ProjectInfo;

// init meta

void SuiDesigner$ProjectInfo_initMeta(Vtable_SuiDesigner$ProjectInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ProjectInfo, path), true, false, 1);
	orc_metaField_class(&pNext, "version", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ProjectInfo, version), true, false, 1);
	orc_metaField_class(&pNext, "icon", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ProjectInfo, icon), true, false, 1);

	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$ProjectInfo, toJson));
	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$ProjectInfo, fromJson));
	orc_metaField_method(&pNext, "getName", offsetof(SuiDesigner$ProjectInfo, getName));
}


// vtable init


Vtable_SuiDesigner$ProjectInfo* Vtable_SuiDesigner$ProjectInfo_init(Vtable_SuiDesigner$ProjectInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ProjectInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ProjectInfo_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ProjectInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ProjectInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ProjectInfo_fini(SuiDesigner$ProjectInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$ProjectInfo_init_fields(SuiDesigner$ProjectInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ProjectInfo_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ProjectInfo*)self)->path, Orc$str(&tmpReturn_1, ".") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ProjectInfo*)self)->version, Orc$str(&tmpReturn_2, "1.0.0") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ProjectInfo*)self)->icon, Orc$str(&tmpReturn_3, "./asset/icon/dir.png") );
    }
	((SuiDesigner$ProjectInfo*)self)->toJson = (void*)SuiDesigner$ProjectInfo$toJson;
	((SuiDesigner$ProjectInfo*)self)->fromJson = (void*)SuiDesigner$ProjectInfo$fromJson;
	((SuiDesigner$ProjectInfo*)self)->getName = (void*)SuiDesigner$ProjectInfo$getName;
}

// init function

void SuiDesigner$ProjectInfo_init(SuiDesigner$ProjectInfo *self, void *pOwner){
    Vtable_SuiDesigner$ProjectInfo_init(&_vtable_SuiDesigner$ProjectInfo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ProjectInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ProjectInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ProjectInfo * SuiDesigner$ProjectInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ProjectInfo *self = calloc(1, sizeof(SuiDesigner$ProjectInfo));
	
    SuiDesigner$ProjectInfo_init(self, pOwner);
    return self;
}


// class members
Json$Json*  SuiDesigner$ProjectInfo$toJson(Json$Json **  __outRef__, SuiDesigner$ProjectInfo *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->putString(jo, "path", self->path) ;
	jo->putString(jo, "version", self->version) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
}


void  SuiDesigner$ProjectInfo$fromJson(SuiDesigner$ProjectInfo *  self, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ProjectInfo, path) , jo->getString(&tmpReturn_1, jo, "path") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ProjectInfo, version) , jo->getString(&tmpReturn_2, jo, "path") ) ;
}


Orc$String*  SuiDesigner$ProjectInfo$getName(Orc$String **  __outRef__, SuiDesigner$ProjectInfo *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$Path_basename(&tmpReturn_1, self->path->str) ) ; 
}




//vtable instance
Vtable_SuiDesigner$ProjectMgr _vtable_SuiDesigner$ProjectMgr;

// init meta

void SuiDesigner$ProjectMgr_initMeta(Vtable_SuiDesigner$ProjectMgr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "projects", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$ProjectMgr, projects), true, false, 1);

	orc_metaField_method(&pNext, "addTestProject", offsetof(SuiDesigner$ProjectMgr, addTestProject));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$ProjectMgr, toJson));
	orc_metaField_method(&pNext, "loadByJson", offsetof(SuiDesigner$ProjectMgr, loadByJson));
	orc_metaField_method(&pNext, "importProject", offsetof(SuiDesigner$ProjectMgr, importProject));
	orc_metaField_method(&pNext, "remove", offsetof(SuiDesigner$ProjectMgr, remove));
	orc_metaField_method(&pNext, "add", offsetof(SuiDesigner$ProjectMgr, add));
	orc_metaField_method(&pNext, "save", offsetof(SuiDesigner$ProjectMgr, save));
	orc_metaField_method(&pNext, "load", offsetof(SuiDesigner$ProjectMgr, load));
}


// vtable init


Vtable_SuiDesigner$ProjectMgr* Vtable_SuiDesigner$ProjectMgr_init(Vtable_SuiDesigner$ProjectMgr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ProjectMgr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ProjectMgr_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ProjectMgr";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ProjectMgr_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ProjectMgr_fini(SuiDesigner$ProjectMgr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$ProjectMgr_init_fields(SuiDesigner$ProjectMgr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ProjectMgr_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ProjectMgr*)self)->projects, Orc$List_new(&tmpNewOwner_1) );
    }
	((Object*)self)->ctor = (void*)SuiDesigner$ProjectMgr$ctor;
	((SuiDesigner$ProjectMgr*)self)->addTestProject = (void*)SuiDesigner$ProjectMgr$addTestProject;
	((SuiDesigner$ProjectMgr*)self)->toJson = (void*)SuiDesigner$ProjectMgr$toJson;
	((SuiDesigner$ProjectMgr*)self)->loadByJson = (void*)SuiDesigner$ProjectMgr$loadByJson;
	((SuiDesigner$ProjectMgr*)self)->importProject = (void*)SuiDesigner$ProjectMgr$importProject;
	((SuiDesigner$ProjectMgr*)self)->remove = (void*)SuiDesigner$ProjectMgr$remove;
	((SuiDesigner$ProjectMgr*)self)->add = (void*)SuiDesigner$ProjectMgr$add;
	((SuiDesigner$ProjectMgr*)self)->save = (void*)SuiDesigner$ProjectMgr$save;
	((SuiDesigner$ProjectMgr*)self)->load = (void*)SuiDesigner$ProjectMgr$load;
}

// init function

void SuiDesigner$ProjectMgr_init(SuiDesigner$ProjectMgr *self, void *pOwner){
    Vtable_SuiDesigner$ProjectMgr_init(&_vtable_SuiDesigner$ProjectMgr);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ProjectMgr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ProjectMgr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ProjectMgr * SuiDesigner$ProjectMgr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ProjectMgr *self = calloc(1, sizeof(SuiDesigner$ProjectMgr));
	
    SuiDesigner$ProjectMgr_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ProjectMgr$ctor(SuiDesigner$ProjectMgr *  self){
	self->addTestProject(self, "E:/luwa/oms_ts/Sui/asset/icon") ;
	self->addTestProject(self, "E:/luwa/oms_ts/Sui/asset") ;
	self->addTestProject(self, "E:/luwa/oms_ts/Sui") ;
	self->addTestProject(self, "E:/luwa/oms_ts") ;
	self->addTestProject(self, "E:/luwa/oms_ts/orc-antlr") ;
}


void  SuiDesigner$ProjectMgr$addTestProject(SuiDesigner$ProjectMgr *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectInfo*  p = (p=NULL,urgc_init_var_class((void**)&p, SuiDesigner$ProjectInfo_new(&p) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(p, (void * )offsetof(SuiDesigner$ProjectInfo, path) , Orc$str(&tmpReturn_1, path) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(p, (void * )offsetof(SuiDesigner$ProjectInfo, version) , Orc$str(&tmpReturn_2, "2.303.0") ) ;
	self->projects->add(self->projects, p) ;
}


Json$Json*  SuiDesigner$ProjectMgr$toJson(Json$Json **  __outRef__, SuiDesigner$ProjectMgr *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  projectsJa = Json$Json_mkArray((projectsJa = NULL,&projectsJa)) ;
	for (int  i = 0; i < self->projects->size(self->projects) ; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectInfo*  project = (project=NULL,urgc_init_var_class((void**)&project, (SuiDesigner$ProjectInfo* )self->projects->get(self->projects, i) ));
		URGC_VAR_CLEANUP_CLASS Json$Json*  projectJo = project->toJson((projectJo = NULL,&projectJo), project) ;
		projectsJa->add(projectsJa, projectJo) ;
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->put(jo, "projects", projectsJa) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, jo) ; 
}


void  SuiDesigner$ProjectMgr$loadByJson(SuiDesigner$ProjectMgr *  self, Json$Json*  jo){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jo);

	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ProjectMgr, projects) , Orc$List_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  projectsJa = jo->get((projectsJa = NULL,&projectsJa), jo, "projects") ;
	for (int  i = 0; i < projectsJa->arraySize(projectsJa) ; i++) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  projectJo = projectsJa->at((projectJo = NULL,&projectJo), projectsJa, i) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectInfo*  project = (project=NULL,urgc_init_var_class((void**)&project, SuiDesigner$ProjectInfo_new(&project) ));
		project->fromJson(project, projectJo) ;
		self->projects->add(self->projects, project) ;
	}
}


void  SuiDesigner$ProjectMgr$importProject(SuiDesigner$ProjectMgr *  self, Orc$String*  projectRootDirPath){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(projectRootDirPath);

	
}


void  SuiDesigner$ProjectMgr$remove(SuiDesigner$ProjectMgr *  self, SuiDesigner$ProjectInfo *  project){
	self->projects->remove(self->projects, project) ;
	self->save(self) ;
}


void  SuiDesigner$ProjectMgr$add(SuiDesigner$ProjectMgr *  self, SuiDesigner$ProjectInfo*  project){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(project);

	self->projects->add(self->projects, project) ;
	self->save(self) ;
}


void  SuiDesigner$ProjectMgr$save(SuiDesigner$ProjectMgr *  self){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = self->toJson((jo = NULL,&jo), self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = jo->dump((text = NULL,&text), jo) ;
	printf("save ProjectMgr. %s\n", text->str) ;
}


void  SuiDesigner$ProjectMgr$load(SuiDesigner$ProjectMgr *  self){
	
}





