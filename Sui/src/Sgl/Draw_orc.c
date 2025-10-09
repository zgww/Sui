
#include "Draw_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Vao_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Map_orc.h"
#include "../Json/Json_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Draw _vtable_Sgl$Draw;

// init meta

void Sgl$Draw_initMeta(Vtable_Sgl$Draw *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "material", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$Draw, material), true, false, 1);
	orc_metaField_class(&pNext, "geometry", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(Sgl$Draw, geometry), true, false, 1);
	orc_metaField_class(&pNext, "vao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$Draw, vao), true, false, 1);

	orc_metaField_method(&pNext, "needBuildVao", offsetof(Sgl$Draw, needBuildVao));
	orc_metaField_method(&pNext, "buildVaoIfNeed", offsetof(Sgl$Draw, buildVaoIfNeed));
	orc_metaField_method(&pNext, "buildVao", offsetof(Sgl$Draw, buildVao));
	orc_metaField_method(&pNext, "use", offsetof(Sgl$Draw, use));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$Draw, draw));
	orc_metaField_method(&pNext, "buildGeometryByJsonPathCstr", offsetof(Sgl$Draw, buildGeometryByJsonPathCstr));
}


// vtable init


Vtable_Sgl$Draw* Vtable_Sgl$Draw_init(Vtable_Sgl$Draw* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Draw;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Draw_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Draw";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Draw_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Draw_fini(Sgl$Draw *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Draw*)self)->material);
	urgc_fini_field_class(self, (void**)&((Sgl$Draw*)self)->geometry);
	urgc_fini_field_class(self, (void**)&((Sgl$Draw*)self)->vao);

}

// init fields function


void Sgl$Draw_init_fields(Sgl$Draw *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Draw_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Draw*)self)->material, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Draw*)self)->geometry, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Draw*)self)->vao, NULL);
    }
	((Sgl$Draw*)self)->needBuildVao = (void*)Sgl$Draw$needBuildVao;
	((Sgl$Draw*)self)->buildVaoIfNeed = (void*)Sgl$Draw$buildVaoIfNeed;
	((Sgl$Draw*)self)->buildVao = (void*)Sgl$Draw$buildVao;
	((Sgl$Draw*)self)->use = (void*)Sgl$Draw$use;
	((Sgl$Draw*)self)->draw = (void*)Sgl$Draw$draw;
	((Sgl$Draw*)self)->buildGeometryByJsonPathCstr = (void*)Sgl$Draw$buildGeometryByJsonPathCstr;
}

// init function

void Sgl$Draw_init(Sgl$Draw *self, void *pOwner){
    Vtable_Sgl$Draw_init(&_vtable_Sgl$Draw);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Draw;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Draw_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Draw * Sgl$Draw_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Draw *self = calloc(1, sizeof(Sgl$Draw));
	
    Sgl$Draw_init(self, pOwner);
    return self;
}


// class members
bool  Sgl$Draw$needBuildVao(Sgl$Draw *  self){
	return self->material && self->geometry && (!self->vao || (self->vao->material != self->material || self->vao->geometry != self->geometry)); 
}


bool  Sgl$Draw$buildVaoIfNeed(Sgl$Draw *  self){
	if (self->needBuildVao(self) ) {
		return self->buildVao(self) ; 
	}
	return true; 
}


bool  Sgl$Draw$buildVao(Sgl$Draw *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  vao = (vao=NULL,urgc_init_var_class((void**)&vao, Sgl$Vao_new(&vao) ));
	urgc_set_field_class(vao, (void * )offsetof(Sgl$Vao, material) , self->material) ;
	urgc_set_field_class(vao, (void * )offsetof(Sgl$Vao, geometry) , self->geometry) ;
	vao->gen(vao) ;
	vao->bind(vao) ;
	bool  ok = self->geometry->bindVertexAttribs(self->geometry, self->material) ;
	if (self->geometry->ibo) {
		self->geometry->ibo->bind(self->geometry->ibo) ;
	}
	vao->unbind(vao) ;
	if (ok) {
		urgc_set_field_class(self, (void * )offsetof(Sgl$Draw, vao) , vao) ;
	}
	return ok; 
}


void  Sgl$Draw$use(Sgl$Draw *  self){
	self->buildVaoIfNeed(self) ;
	if (self->material && self->material->program) {
		self->material->program->use(self->material->program) ;
	}
	if (self->vao) {
		self->vao->bind(self->vao) ;
	}
}


void  Sgl$Draw$buildGeometryByJsonPathCstr(Sgl$Draw *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Draw, geometry) , Sgl$Geometry_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  triJo = Json$Json_parseByPathCstr((triJo = NULL,&triJo), path) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  keys = triJo->keys((keys = NULL,&keys), triJo) ;
	printf("load JsonMesh %s\n", path) ;
	for (int  i = 0; i < keys->size(keys) ; i++) {
		Orc$String *  key = (Orc$String * )keys->get(keys, i) ;
		if (Orc$String$equals(key, "face") ) {
			URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
			URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  indicesBuf = Sgl$mkBufferIntByJsonArray((indicesBuf = NULL,&indicesBuf), triJo->get(&tmpReturn_2, triJo, "face") ) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  ibo = (ibo=NULL,urgc_init_var_class((void**)&ibo, Sgl$Vbo_new(&ibo) ));
			ibo->elementBuffer(ibo, indicesBuf) ;
			urgc_set_field_class(self->geometry, (void * )offsetof(Sgl$Geometry, ibo) , ibo) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			printf("\tload face:%s\n", Sgl$Buffer$toIntString(&tmpReturn_3, indicesBuf) ->str) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS Json$Json*  attrJo = triJo->get((attrJo = NULL,&attrJo), triJo, key->str) ;
			URGC_VAR_CLEANUP_CLASS Json$Json*  countJo = attrJo->get((countJo = NULL,&countJo), attrJo, "count") ;
			URGC_VAR_CLEANUP_CLASS Json$Json*  dataJo = attrJo->get((dataJo = NULL,&dataJo), attrJo, "data") ;
			if (countJo && dataJo) {
				int  count = countJo->asInt(countJo) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = Sgl$mkBufferFloatByJsonArray((buf = NULL,&buf), dataJo) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				printf("\tload %s:%s\n", key->str, Sgl$Buffer$toFloatString(&tmpReturn_4, buf) ->str) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
				vbo->arrayBuffer(vbo, buf) ;
				vbo->elementCount = count;
				self->geometry->setAttr(self->geometry, key->str, vbo) ;
			}
			else {
				printf("%s无效的顶点属性:%s\n", path, key->str) ;
			}
		}
	}
}




//vtable instance
Vtable_Sgl$ObjLoader _vtable_Sgl$ObjLoader;

// init meta

void Sgl$ObjLoader_initMeta(Vtable_Sgl$ObjLoader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "vertices", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ObjLoader, vertices), true, false, 1);
	orc_metaField_class(&pNext, "normals", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ObjLoader, normals), true, false, 1);
	orc_metaField_class(&pNext, "texCoords", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ObjLoader, texCoords), true, false, 1);
	orc_metaField_class(&pNext, "faces", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ObjLoader, faces), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$ObjLoader, path), true, false, 1);

	orc_metaField_method(&pNext, "load", offsetof(Sgl$ObjLoader, load));
	orc_metaField_method(&pNext, "_load", offsetof(Sgl$ObjLoader, _load));
	orc_metaField_method(&pNext, "buildGeometry", offsetof(Sgl$ObjLoader, buildGeometry));
}


// vtable init


Vtable_Sgl$ObjLoader* Vtable_Sgl$ObjLoader_init(Vtable_Sgl$ObjLoader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$ObjLoader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$ObjLoader_new;
    ((Vtable_Object*)pvt)->className = "Sgl$ObjLoader";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$ObjLoader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$ObjLoader_fini(Sgl$ObjLoader *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$ObjLoader*)self)->vertices);
	urgc_fini_field_class(self, (void**)&((Sgl$ObjLoader*)self)->normals);
	urgc_fini_field_class(self, (void**)&((Sgl$ObjLoader*)self)->texCoords);
	urgc_fini_field_class(self, (void**)&((Sgl$ObjLoader*)self)->faces);
	urgc_fini_field_class(self, (void**)&((Sgl$ObjLoader*)self)->path);

}

// init fields function


void Sgl$ObjLoader_init_fields(Sgl$ObjLoader *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$ObjLoader_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ObjLoader*)self)->vertices, Sgl$Buffer_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ObjLoader*)self)->normals, Sgl$Buffer_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ObjLoader*)self)->texCoords, Sgl$Buffer_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ObjLoader*)self)->faces, Sgl$Buffer_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ObjLoader*)self)->path, Orc$str(&tmpReturn_5, "") );
    }
	((Sgl$ObjLoader*)self)->load = (void*)Sgl$ObjLoader$load;
	((Sgl$ObjLoader*)self)->_load = (void*)Sgl$ObjLoader$_load;
	((Sgl$ObjLoader*)self)->buildGeometry = (void*)Sgl$ObjLoader$buildGeometry;
}

// init function

void Sgl$ObjLoader_init(Sgl$ObjLoader *self, void *pOwner){
    Vtable_Sgl$ObjLoader_init(&_vtable_Sgl$ObjLoader);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$ObjLoader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$ObjLoader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$ObjLoader * Sgl$ObjLoader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$ObjLoader *self = calloc(1, sizeof(Sgl$ObjLoader));
	
    Sgl$ObjLoader_init(self, pOwner);
    return self;
}


// class members
void  Sgl$ObjLoader$load(Sgl$ObjLoader *  self, const char *  path){
	Orc$String$set(self->path, path) ;
	self->_load(self) ;
}


Sgl$Geometry*  Sgl$ObjLoader$buildGeometry(Sgl$Geometry **  __outRef__, Sgl$ObjLoader *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  geo = (geo=NULL,urgc_init_var_class((void**)&geo, Sgl$Geometry_new(&geo) ));
	if (self->vertices->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		vbo->elementCount = 3;
		vbo->arrayBuffer(vbo, self->vertices) ;
		geo->setAttr(geo, "position", vbo) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("\tload %s:%s\n", "position", Sgl$Buffer$toFloatString(&tmpReturn_1, self->vertices) ->str) ;
	}
	if (self->normals->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		vbo->elementCount = 3;
		vbo->arrayBuffer(vbo, self->normals) ;
		geo->setAttr(geo, "normal", vbo) ;
	}
	if (self->texCoords->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		vbo->elementCount = 2;
		vbo->arrayBuffer(vbo, self->texCoords) ;
		geo->setAttr(geo, "texCoord", vbo) ;
	}
	if (self->faces->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  tmpNewOwner_2 = NULL;
		urgc_set_field_class(geo, (void * )offsetof(Sgl$Geometry, ibo) , Sgl$Vbo_new(&tmpNewOwner_2) ) ;
		geo->ibo->elementBuffer(geo->ibo, self->faces) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		printf("\tload face:%s\n", Sgl$Buffer$toIntString(&tmpReturn_3, self->faces) ->str) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, geo) ; 
}





