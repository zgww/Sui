
#include "HoroIconMgr_orc.h" 

#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/PixelsReader_orc.h"
#include "../Sgl/ModelLoader_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_HoroEditor$HoroMaterialIconCreator _vtable_HoroEditor$HoroMaterialIconCreator;

// init meta

void HoroEditor$HoroMaterialIconCreator_initMeta(Vtable_HoroEditor$HoroMaterialIconCreator *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(HoroEditor$HoroMaterialIconCreator, fbo), true, false, 1);
	orc_metaField_struct(&pNext, "size", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(HoroEditor$HoroMaterialIconCreator, size), false, false, 0);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(HoroEditor$HoroMaterialIconCreator, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(HoroEditor$HoroMaterialIconCreator, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(HoroEditor$HoroMaterialIconCreator, camera), true, false, 1);
	orc_metaField_class(&pNext, "materialPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroMaterialIconCreator, materialPath), true, false, 1);

	orc_metaField_method(&pNext, "create", offsetof(HoroEditor$HoroMaterialIconCreator, create));
	orc_metaField_method(&pNext, "showTextureWindow", offsetof(HoroEditor$HoroMaterialIconCreator, showTextureWindow));
	orc_metaField_method(&pNext, "saveAsPng", offsetof(HoroEditor$HoroMaterialIconCreator, saveAsPng));
	orc_metaField_method(&pNext, "draw", offsetof(HoroEditor$HoroMaterialIconCreator, draw));
	orc_metaField_method(&pNext, "mkScene", offsetof(HoroEditor$HoroMaterialIconCreator, mkScene));
}


// vtable init


Vtable_HoroEditor$HoroMaterialIconCreator* Vtable_HoroEditor$HoroMaterialIconCreator_init(Vtable_HoroEditor$HoroMaterialIconCreator* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroMaterialIconCreator;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroMaterialIconCreator_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroMaterialIconCreator";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroMaterialIconCreator_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroMaterialIconCreator_fini(HoroEditor$HoroMaterialIconCreator *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->fbo);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->scene);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->camera);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->materialPath);

}

// init fields function


void HoroEditor$HoroMaterialIconCreator_init_fields(HoroEditor$HoroMaterialIconCreator *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroMaterialIconCreator_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->fbo, Sgl$Fbo_new(&tmpNewOwner_1) );
	((HoroEditor$HoroMaterialIconCreator*)self)->size = SuiCore$mkVec2(128, 128) ;
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->drawCtx, Sgl$DrawCtx_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->camera, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->materialPath, NULL);
    }
	((HoroEditor$HoroMaterialIconCreator*)self)->create = (void*)HoroEditor$HoroMaterialIconCreator$create;
	((HoroEditor$HoroMaterialIconCreator*)self)->showTextureWindow = (void*)HoroEditor$HoroMaterialIconCreator$showTextureWindow;
	((HoroEditor$HoroMaterialIconCreator*)self)->saveAsPng = (void*)HoroEditor$HoroMaterialIconCreator$saveAsPng;
	((HoroEditor$HoroMaterialIconCreator*)self)->draw = (void*)HoroEditor$HoroMaterialIconCreator$draw;
	((HoroEditor$HoroMaterialIconCreator*)self)->mkScene = (void*)HoroEditor$HoroMaterialIconCreator$mkScene;
}

// init function

void HoroEditor$HoroMaterialIconCreator_init(HoroEditor$HoroMaterialIconCreator *self, void *pOwner){
    Vtable_HoroEditor$HoroMaterialIconCreator_init(&_vtable_HoroEditor$HoroMaterialIconCreator);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroMaterialIconCreator;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroMaterialIconCreator_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroMaterialIconCreator * HoroEditor$HoroMaterialIconCreator_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroMaterialIconCreator *self = calloc(1, sizeof(HoroEditor$HoroMaterialIconCreator));
	
    HoroEditor$HoroMaterialIconCreator_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroMaterialIconCreator$create(HoroEditor$HoroMaterialIconCreator *  self, const char *  materialPath){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroMaterialIconCreator, materialPath) , Orc$str(&tmpReturn_1, materialPath) ) ;
	self->mkScene(self) ;
	self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )SuiCore$Vec2$width(&self->size) , (int )SuiCore$Vec2$height(&self->size) , true, true, false) ;
	self->draw(self) ;
	self->saveAsPng(self, "materialicon.png") ;
}


void  HoroEditor$HoroMaterialIconCreator$showTextureWindow(HoroEditor$HoroMaterialIconCreator *  self){
	Sgl$SglSceneView_showTextureWindow(self->fbo->tex2d, self->size.x, self->size.y) ;
}


void  HoroEditor$HoroMaterialIconCreator$saveAsPng(HoroEditor$HoroMaterialIconCreator *  self, const char *  path){
	self->fbo->bind(self->fbo) ;
	URGC_VAR_CLEANUP_CLASS Sgl$RgbaPixelsReader*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$RgbaPixelsReader_new(&r) ));
	unsigned char *  floats = r->readFromColorAttachment(r, 0, 0, 0, self->size.x, self->size.y) ;
	self->fbo->unbind(self->fbo) ;
	SuiCore$Image_writeRgbas_toPng(path, SuiCore$Vec2$width(&self->size) , SuiCore$Vec2$height(&self->size) , floats) ;
}


void  HoroEditor$HoroMaterialIconCreator$draw(HoroEditor$HoroMaterialIconCreator *  self){
	SuiCore$Vec2 fboSize = self->fbo->getSize(self->fbo) ;
	self->camera->aspect = fboSize.x / fboSize.y;
	self->fbo->startDraw(self->fbo, 0.0, 0.0, 0.0, 0.0, true, true, true) ;
	self->drawCtx->frameSize = fboSize;
	self->drawCtx->draw(self->drawCtx, self->scene, self->camera) ;
	self->fbo->endDraw(self->fbo) ;
}


void  HoroEditor$HoroMaterialIconCreator$mkScene(HoroEditor$HoroMaterialIconCreator *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroMaterialIconCreator, scene) , Sgl$Scene_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroMaterialIconCreator, camera) , Sgl$PerspectiveCamera_new(&tmpNewOwner_2) ) ;
	((Sgl$Obj3d * )self->camera)->up = SuiCore$mkVec3(0, 1, 0) ;
	self->camera->fov = 45 / 180.0 * Orc$PI;
	self->camera->aspect = 1.0;
	self->camera->nearPlane = 100.1;
	self->camera->farPlane = 5000;
	((Sgl$Obj3d * )self->camera)->position = SuiCore$mkVec3(0, 0, 300) ;
	Sgl$Obj3d$updateWorldMatrixUptoRoot((Sgl$Obj3d * )self->camera) ;
	((Sgl$Obj3d * )self->camera)->lookAt(self->camera, 0, 0, 0) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, self->camera) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  mesh = (mesh=NULL,urgc_init_var_class((void**)&mesh, Sgl$Mesh_new(&mesh) ));
	URGC_VAR_CLEANUP_CLASS Sgl$GeometrySphere*  tmpNewOwner_3 = NULL;
	{
		Sgl$GeometrySphere*  o = Sgl$GeometrySphere_new(&tmpNewOwner_3) ;
		
	
		((Sgl$Geometry * )o)->build(o) ;
		urgc_set_field_class(mesh, (void * )offsetof(Sgl$Mesh, geometry) , o) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_4 = NULL;
	{
		Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_4) ;
		
	
		o->load(o, self->materialPath->str) ;
		urgc_set_field_class(mesh, (void * )offsetof(Sgl$Mesh, material) , o) ;
	}
	((SuiCore$Node * )self->scene)->appendChild(self->scene, mesh) ;
}




//vtable instance
Vtable_HoroEditor$HoroModelIconCreator _vtable_HoroEditor$HoroModelIconCreator;

// init meta

void HoroEditor$HoroModelIconCreator_initMeta(Vtable_HoroEditor$HoroModelIconCreator *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(HoroEditor$HoroModelIconCreator, fbo), true, false, 1);
	orc_metaField_struct(&pNext, "size", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(HoroEditor$HoroModelIconCreator, size), false, false, 0);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(HoroEditor$HoroModelIconCreator, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(HoroEditor$HoroModelIconCreator, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(HoroEditor$HoroModelIconCreator, camera), true, false, 1);
	orc_metaField_class(&pNext, "modelPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroModelIconCreator, modelPath), true, false, 1);

	orc_metaField_method(&pNext, "create", offsetof(HoroEditor$HoroModelIconCreator, create));
	orc_metaField_method(&pNext, "showTextureWindow", offsetof(HoroEditor$HoroModelIconCreator, showTextureWindow));
	orc_metaField_method(&pNext, "saveAsPng", offsetof(HoroEditor$HoroModelIconCreator, saveAsPng));
	orc_metaField_method(&pNext, "draw", offsetof(HoroEditor$HoroModelIconCreator, draw));
	orc_metaField_method(&pNext, "mkScene", offsetof(HoroEditor$HoroModelIconCreator, mkScene));
}


// vtable init


Vtable_HoroEditor$HoroModelIconCreator* Vtable_HoroEditor$HoroModelIconCreator_init(Vtable_HoroEditor$HoroModelIconCreator* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroModelIconCreator;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroModelIconCreator_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroModelIconCreator";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroModelIconCreator_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroModelIconCreator_fini(HoroEditor$HoroModelIconCreator *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->fbo);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->scene);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->camera);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->modelPath);

}

// init fields function


void HoroEditor$HoroModelIconCreator_init_fields(HoroEditor$HoroModelIconCreator *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroModelIconCreator_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->fbo, Sgl$Fbo_new(&tmpNewOwner_1) );
	((HoroEditor$HoroModelIconCreator*)self)->size = SuiCore$mkVec2(256, 256) ;
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->drawCtx, Sgl$DrawCtx_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->camera, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->modelPath, NULL);
    }
	((HoroEditor$HoroModelIconCreator*)self)->create = (void*)HoroEditor$HoroModelIconCreator$create;
	((HoroEditor$HoroModelIconCreator*)self)->showTextureWindow = (void*)HoroEditor$HoroModelIconCreator$showTextureWindow;
	((HoroEditor$HoroModelIconCreator*)self)->saveAsPng = (void*)HoroEditor$HoroModelIconCreator$saveAsPng;
	((HoroEditor$HoroModelIconCreator*)self)->draw = (void*)HoroEditor$HoroModelIconCreator$draw;
	((HoroEditor$HoroModelIconCreator*)self)->mkScene = (void*)HoroEditor$HoroModelIconCreator$mkScene;
}

// init function

void HoroEditor$HoroModelIconCreator_init(HoroEditor$HoroModelIconCreator *self, void *pOwner){
    Vtable_HoroEditor$HoroModelIconCreator_init(&_vtable_HoroEditor$HoroModelIconCreator);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroModelIconCreator;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroModelIconCreator_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroModelIconCreator * HoroEditor$HoroModelIconCreator_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroModelIconCreator *self = calloc(1, sizeof(HoroEditor$HoroModelIconCreator));
	
    HoroEditor$HoroModelIconCreator_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroModelIconCreator$create(HoroEditor$HoroModelIconCreator *  self, const char *  modelPath){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroModelIconCreator, modelPath) , Orc$str(&tmpReturn_1, modelPath) ) ;
	self->mkScene(self) ;
	self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )SuiCore$Vec2$width(&self->size) , (int )SuiCore$Vec2$height(&self->size) , true, true, false) ;
	self->draw(self) ;
	self->saveAsPng(self, "modelicon.png") ;
	self->showTextureWindow(self) ;
}


void  HoroEditor$HoroModelIconCreator$showTextureWindow(HoroEditor$HoroModelIconCreator *  self){
	Sgl$SglSceneView_showTextureWindow(self->fbo->tex2d, self->size.x, self->size.y) ;
}


void  HoroEditor$HoroModelIconCreator$saveAsPng(HoroEditor$HoroModelIconCreator *  self, const char *  path){
	self->fbo->bind(self->fbo) ;
	URGC_VAR_CLEANUP_CLASS Sgl$RgbaPixelsReader*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$RgbaPixelsReader_new(&r) ));
	unsigned char *  floats = r->readFromColorAttachment(r, 0, 0, 0, self->size.x, self->size.y) ;
	r->flipY(r) ;
	self->fbo->unbind(self->fbo) ;
	SuiCore$Image_writeRgbas_toPng(path, SuiCore$Vec2$width(&self->size) , SuiCore$Vec2$height(&self->size) , floats) ;
}


void  HoroEditor$HoroModelIconCreator$draw(HoroEditor$HoroModelIconCreator *  self){
	SuiCore$Vec2 fboSize = self->fbo->getSize(self->fbo) ;
	self->camera->aspect = fboSize.x / fboSize.y;
	self->fbo->startDraw(self->fbo, 1.0, 10.0, 1.0, 0.0, true, true, true) ;
	self->drawCtx->frameSize = fboSize;
	self->drawCtx->draw(self->drawCtx, self->scene, self->camera) ;
	self->fbo->endDraw(self->fbo) ;
}


void  HoroEditor$HoroModelIconCreator$mkScene(HoroEditor$HoroModelIconCreator *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroModelIconCreator, scene) , Sgl$Scene_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroModelIconCreator, camera) , Sgl$PerspectiveCamera_new(&tmpNewOwner_2) ) ;
	((Sgl$Obj3d * )self->camera)->up = SuiCore$mkVec3(0, 1, 0) ;
	self->camera->fov = 45 / 180.0 * Orc$PI;
	self->camera->aspect = 1.0;
	self->camera->nearPlane = 100.1;
	self->camera->farPlane = 5000;
	((Sgl$Obj3d * )self->camera)->position = SuiCore$mkVec3(500, 300, 500) ;
	Sgl$Obj3d$updateWorldMatrixUptoRoot((Sgl$Obj3d * )self->camera) ;
	((Sgl$Obj3d * )self->camera)->lookAt(self->camera, 0, 100, 0) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, self->camera) ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$PointLight*  tmpNewOwner_3 = NULL;
		{
			Sgl$PointLight*  o = Sgl$PointLight_new(&tmpNewOwner_3) ;
			
		
			SuiCore$Vec3$set(&((Sgl$Obj3d * )o)->position, 500, 500, 500) ;
			((SuiCore$Node * )self->scene)->appendChild(self->scene, o) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS Sgl$AssimpLoader*  l = (l=NULL,urgc_init_var_class((void**)&l, Sgl$AssimpLoader_new(&l) ));
	l->load(l, self->modelPath->str) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  root = l->buildSglTree((root = NULL,&root), l) ;
	SuiCore$Vec3$set(&root->scale, 100, 100, 100) ;
	root->updateWorldTransformAndSubtree(root) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, root) ;
}




//vtable instance
Vtable_HoroEditor$HoroIconMgr _vtable_HoroEditor$HoroIconMgr;

// init meta

void HoroEditor$HoroIconMgr_initMeta(Vtable_HoroEditor$HoroIconMgr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "request", offsetof(HoroEditor$HoroIconMgr, request));
}


// vtable init


Vtable_HoroEditor$HoroIconMgr* Vtable_HoroEditor$HoroIconMgr_init(Vtable_HoroEditor$HoroIconMgr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroIconMgr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroIconMgr_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroIconMgr";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroIconMgr_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void HoroEditor$HoroIconMgr_fini(HoroEditor$HoroIconMgr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void HoroEditor$HoroIconMgr_init_fields(HoroEditor$HoroIconMgr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroIconMgr_fini;
	//fields
    {
	
    }
	((HoroEditor$HoroIconMgr*)self)->request = (void*)HoroEditor$HoroIconMgr$request;
}

// init function

void HoroEditor$HoroIconMgr_init(HoroEditor$HoroIconMgr *self, void *pOwner){
    Vtable_HoroEditor$HoroIconMgr_init(&_vtable_HoroEditor$HoroIconMgr);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroIconMgr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroIconMgr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroIconMgr * HoroEditor$HoroIconMgr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroIconMgr *self = calloc(1, sizeof(HoroEditor$HoroIconMgr));
	
    HoroEditor$HoroIconMgr_init(self, pOwner);
    return self;
}


// class members
SuiCore$Image *  HoroEditor$HoroIconMgr$request(HoroEditor$HoroIconMgr *  self, const char *  path){
	
}



void  HoroEditor$testHoroMaterialIconCreator(){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroMaterialIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroMaterialIconCreator_new(&c) ));
	c->create(c, "../asset/basic.matl.json") ;
}

void  HoroEditor$testHoroModelIconCreator(){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroModelIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroModelIconCreator_new(&c) ));
	c->create(c, "halloween/obj/fence.obj") ;
}



