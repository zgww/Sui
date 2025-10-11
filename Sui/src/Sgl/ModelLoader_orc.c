
#include "ModelLoader_orc.h" 

#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "./Obj3d_orc.h"
#include "./Mesh_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$ModelLoader _vtable_Sgl$ModelLoader;

// init meta

void Sgl$ModelLoader_initMeta(Vtable_Sgl$ModelLoader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "vertices", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, vertices), true, false, 1);
	orc_metaField_class(&pNext, "normals", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, normals), true, false, 1);
	orc_metaField_class(&pNext, "texCoords", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, texCoords), true, false, 1);
	orc_metaField_class(&pNext, "faces", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, faces), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$ModelLoader, path), true, false, 1);
	orc_metaField_class(&pNext, "mesh", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(Sgl$ModelLoader, mesh), true, false, 1);

	orc_metaField_method(&pNext, "setPath", offsetof(Sgl$ModelLoader, setPath));
	orc_metaField_method(&pNext, "_load", offsetof(Sgl$ModelLoader, _load));
	orc_metaField_method(&pNext, "buildGeometry", offsetof(Sgl$ModelLoader, buildGeometry));
}


// vtable init


Vtable_Sgl$ModelLoader* Vtable_Sgl$ModelLoader_init(Vtable_Sgl$ModelLoader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$ModelLoader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$ModelLoader_new;
    ((Vtable_Object*)pvt)->className = "Sgl$ModelLoader";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$ModelLoader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$ModelLoader_fini(Sgl$ModelLoader *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->vertices);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->normals);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->texCoords);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->faces);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->path);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->mesh);

}

// init fields function


void Sgl$ModelLoader_init_fields(Sgl$ModelLoader *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$ModelLoader_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->vertices, Sgl$Buffer_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->normals, Sgl$Buffer_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->texCoords, Sgl$Buffer_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->faces, Sgl$Buffer_new(&tmpNewOwner_4) );
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->path, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->mesh, Sgl$Mesh_new(&tmpNewOwner_5) );
    }
	((Sgl$ModelLoader*)self)->setPath = (void*)Sgl$ModelLoader$setPath;
	((Sgl$ModelLoader*)self)->_load = (void*)Sgl$ModelLoader$_load;
	((Sgl$ModelLoader*)self)->buildGeometry = (void*)Sgl$ModelLoader$buildGeometry;
}

// init function

void Sgl$ModelLoader_init(Sgl$ModelLoader *self, void *pOwner){
    Vtable_Sgl$ModelLoader_init(&_vtable_Sgl$ModelLoader);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$ModelLoader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$ModelLoader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$ModelLoader * Sgl$ModelLoader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$ModelLoader *self = calloc(1, sizeof(Sgl$ModelLoader));
	
    Sgl$ModelLoader_init(self, pOwner);
    return self;
}


// class members
void  Sgl$ModelLoader$setPath(Sgl$ModelLoader *  self, Orc$String*  path){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(path);

	urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, path) , path) ;
	if (path) {
		self->_load(self) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpReturn_1 = NULL;
		urgc_set_field_class(self->mesh, (void * )offsetof(Sgl$Mesh, geometry) , self->buildGeometry(&tmpReturn_1, self) ) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
		{
			Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_2) ;
			
		
			o->load(o, "../asset/basic.matl.json") ;
			urgc_set_field_class(self->mesh, (void * )offsetof(Sgl$Mesh, material) , o) ;
		}
		((SuiCore$Node * )self)->appendChild(self, self->mesh) ;
	}
}


Sgl$Geometry*  Sgl$ModelLoader$buildGeometry(Sgl$Geometry **  __outRef__, Sgl$ModelLoader *  self){
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





