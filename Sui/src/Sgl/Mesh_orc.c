
#include "Mesh_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./GeometryLine_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Vao_orc.h"
#include "./Raycaster_orc.h"
#include "./DrawCtx_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/Map_orc.h"
#include "../Json/Json_orc.h"
#include "./GeometryBox_orc.h"
#include "./GeometryPlane_orc.h"
#include "./GeometrySphere_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Mesh _vtable_Sgl$Mesh;

// init meta

void Sgl$Mesh_initMeta(Vtable_Sgl$Mesh *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "material", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$Mesh, material), true, false, 1);
	orc_metaField_class(&pNext, "geometry", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(Sgl$Mesh, geometry), true, false, 1);
	orc_metaField_class(&pNext, "vao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$Mesh, vao), true, false, 1);
	orc_metaField_class(&pNext, "depthVao", ((Vtable_Object*)Vtable_Sgl$Vao_init(0)), offsetof(Sgl$Mesh, depthVao), true, false, 1);
	orc_metaField_class(&pNext, "geometryPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Mesh, geometryPath), true, false, 1);

	orc_metaField_method(&pNext, "setGeometryPath", offsetof(Sgl$Mesh, setGeometryPath));
}


// vtable init


Vtable_Sgl$Mesh* Vtable_Sgl$Mesh_init(Vtable_Sgl$Mesh* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Mesh;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Mesh_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Mesh";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Mesh_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Mesh_fini(Sgl$Mesh *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Mesh*)self)->material);
	urgc_fini_field_class(self, (void**)&((Sgl$Mesh*)self)->geometry);
	urgc_fini_field_class(self, (void**)&((Sgl$Mesh*)self)->vao);
	urgc_fini_field_class(self, (void**)&((Sgl$Mesh*)self)->depthVao);
	urgc_fini_field_class(self, (void**)&((Sgl$Mesh*)self)->geometryPath);

}

// init fields function


void Sgl$Mesh_init_fields(Sgl$Mesh *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Mesh_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Mesh*)self)->material, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Mesh*)self)->geometry, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Mesh*)self)->vao, Sgl$Vao_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Vao*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Mesh*)self)->depthVao, Sgl$Vao_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((Sgl$Mesh*)self)->geometryPath, NULL);
    }
	((Sgl$Mesh*)self)->setGeometryPath = (void*)Sgl$Mesh$setGeometryPath;
	((Sgl$Obj3d*)self)->tick = (void*)Sgl$Mesh$tick;
	((Sgl$Obj3d*)self)->draw = (void*)Sgl$Mesh$draw;
	((Sgl$Obj3d*)self)->drawSelfRaw = (void*)Sgl$Mesh$drawSelfRaw;
	((Sgl$Obj3d*)self)->drawSelf = (void*)Sgl$Mesh$drawSelf;
	((Sgl$Obj3d*)self)->drawDepth = (void*)Sgl$Mesh$drawDepth;
	((Sgl$Obj3d*)self)->hitTestSelfByRaycaster = (void*)Sgl$Mesh$hitTestSelfByRaycaster;
}

// init function

void Sgl$Mesh_init(Sgl$Mesh *self, void *pOwner){
    Vtable_Sgl$Mesh_init(&_vtable_Sgl$Mesh);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Mesh;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Mesh_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Mesh * Sgl$Mesh_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Mesh *self = calloc(1, sizeof(Sgl$Mesh));
	
    Sgl$Mesh_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Mesh$setGeometryPath(Sgl$Mesh *  self, Orc$String*  p){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(p);

	urgc_set_field_class(self, (void * )offsetof(Sgl$Mesh, geometryPath) , p) ;
	if (Orc$String$equals(p, "Geometry/Box.geometry.json") ) {
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryBox*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryBox_new(&geom) ));
		((Sgl$Geometry * )geom)->build(geom) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_1) ) ;
		self->material->load(self->material, "../asset/basic.matl.json") ;
	}
	else if (Orc$String$equals(p, "Geometry/Sphere.geometry.json") ) {
		URGC_VAR_CLEANUP_CLASS Sgl$GeometrySphere*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometrySphere_new(&geom) ));
		((Sgl$Geometry * )geom)->build(geom) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_2) ) ;
		self->material->load(self->material, "../asset/basic.matl.json") ;
	}
	else if (Orc$String$equals(p, "Geometry/Plane.geometry.json") ) {
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryPlane*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryPlane_new(&geom) ));
		((Sgl$Geometry * )geom)->build(geom) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_3 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_3) ) ;
		self->material->load(self->material, "../asset/basic.matl.json") ;
	}
	printf("设置几何路径:%s\n", p ? p->str : "null") ;
}


void  Sgl$Mesh$tick(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx){
	
}


void  Sgl$Mesh$draw(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx){
	if (self->material == NULL || self->geometry == NULL) {
		return ; 
	}
	if (ctx->addTransparentObj3dIfIsTransparent(ctx, self, self->material) ) {
		
	}
	else {
		((Sgl$Obj3d * )self)->drawSelf(self, ctx) ;
	}
	((Sgl$Obj3d * )self)->drawChildren(self, ctx) ;
}


void  Sgl$Mesh$drawSelfRaw(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx, Sgl$Vao *  vao, Sgl$Material *  material){
	ctx->setMvpToMaterial(ctx, self, material) ;
	ctx->setGlobalInfosToMaterial(ctx, material) ;
	if (Orc_instanceof((Object*)self->geometry, (Vtable_Object*)Vtable_Sgl$GeometryLine_init(NULL))) {
		Sgl$GeometryLine *  gl = (Sgl$GeometryLine * )self->geometry;
		gl->draw(gl, self->material) ;
		return ; 
	}
	vao->draw(vao, self->geometry, material) ;
}


void  Sgl$Mesh$drawSelf(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx){
	((Sgl$Obj3d * )self)->drawSelfRaw(self, ctx, self->vao, self->material) ;
}


void  Sgl$Mesh$drawDepth(Sgl$Mesh *  self, Sgl$DrawCtx *  ctx){
	Sgl$Material *  matl = ctx->depthMatl;
	matl->model = ((Sgl$Obj3d * )self)->_world_transform;
	matl->view = ctx->camera->view;
	matl->projection = ctx->camera->projection;
	matl->updateMvp(matl) ;
	ctx->setGlobalInfosToMaterial(ctx, matl) ;
	self->depthVao->draw(self->depthVao, self->geometry, matl) ;
}


bool  Sgl$Mesh$hitTestSelfByRaycaster(Sgl$Mesh *  self, Sgl$Raycaster *  raycaster){
	Sgl$RayCheckResult r = raycaster->raycastGeometry(raycaster, self, self->geometry) ;
	raycaster->result = r;
	return r.succ; 
}



Sgl$Mesh*  Sgl$mkMesh(Sgl$Mesh **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (Sgl$Mesh* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_Sgl$Mesh_init(NULL)) ) ; 
}



