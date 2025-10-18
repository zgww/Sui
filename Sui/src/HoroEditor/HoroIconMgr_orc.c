
#include "HoroIconMgr_orc.h" 

#include <stdio.h>
#include <string.h>
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
#include "./HoroGeometryPreviewView_orc.h"


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
	orc_metaField_class(&pNext, "savePath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroMaterialIconCreator, savePath), true, false, 1);

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
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->savePath);

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
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroMaterialIconCreator*)self)->savePath, NULL);
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
void  HoroEditor$HoroMaterialIconCreator$create(HoroEditor$HoroMaterialIconCreator *  self, Orc$String *  materialPath){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroMaterialIconCreator, materialPath) , materialPath) ;
	self->mkScene(self) ;
	self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )SuiCore$Vec2$width(&self->size) , (int )SuiCore$Vec2$height(&self->size) , true, true, false) ;
	self->draw(self) ;
	self->saveAsPng(self, self->savePath ? self->savePath->str : "materialicon.png") ;
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
	orc_metaField_class(&pNext, "savePath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroModelIconCreator, savePath), true, false, 1);

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
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->savePath);

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
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroModelIconCreator*)self)->savePath, NULL);
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
void  HoroEditor$HoroModelIconCreator$create(HoroEditor$HoroModelIconCreator *  self, Orc$String *  modelPath){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroModelIconCreator, modelPath) , modelPath) ;
	self->mkScene(self) ;
	self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )SuiCore$Vec2$width(&self->size) , (int )SuiCore$Vec2$height(&self->size) , true, true, false) ;
	self->draw(self) ;
	self->saveAsPng(self, self->savePath ? self->savePath->str : "modelicon.png") ;
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
	self->fbo->startDraw(self->fbo, 1.0, 1.0, 1.0, 0.0, true, true, true) ;
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
Vtable_HoroEditor$HoroGeometryJsonIconCreator _vtable_HoroEditor$HoroGeometryJsonIconCreator;

// init meta

void HoroEditor$HoroGeometryJsonIconCreator_initMeta(Vtable_HoroEditor$HoroGeometryJsonIconCreator *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(HoroEditor$HoroGeometryJsonIconCreator, fbo), true, false, 1);
	orc_metaField_struct(&pNext, "size", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(HoroEditor$HoroGeometryJsonIconCreator, size), false, false, 0);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(HoroEditor$HoroGeometryJsonIconCreator, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(HoroEditor$HoroGeometryJsonIconCreator, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(HoroEditor$HoroGeometryJsonIconCreator, camera), true, false, 1);
	orc_metaField_class(&pNext, "modelPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroGeometryJsonIconCreator, modelPath), true, false, 1);
	orc_metaField_class(&pNext, "savePath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroGeometryJsonIconCreator, savePath), true, false, 1);

	orc_metaField_method(&pNext, "create", offsetof(HoroEditor$HoroGeometryJsonIconCreator, create));
	orc_metaField_method(&pNext, "showTextureWindow", offsetof(HoroEditor$HoroGeometryJsonIconCreator, showTextureWindow));
	orc_metaField_method(&pNext, "saveAsPng", offsetof(HoroEditor$HoroGeometryJsonIconCreator, saveAsPng));
	orc_metaField_method(&pNext, "draw", offsetof(HoroEditor$HoroGeometryJsonIconCreator, draw));
	orc_metaField_method(&pNext, "mkScene", offsetof(HoroEditor$HoroGeometryJsonIconCreator, mkScene));
}


// vtable init


Vtable_HoroEditor$HoroGeometryJsonIconCreator* Vtable_HoroEditor$HoroGeometryJsonIconCreator_init(Vtable_HoroEditor$HoroGeometryJsonIconCreator* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroGeometryJsonIconCreator;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroGeometryJsonIconCreator_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroGeometryJsonIconCreator";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroGeometryJsonIconCreator_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroGeometryJsonIconCreator_fini(HoroEditor$HoroGeometryJsonIconCreator *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->fbo);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->scene);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->camera);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->modelPath);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->savePath);

}

// init fields function


void HoroEditor$HoroGeometryJsonIconCreator_init_fields(HoroEditor$HoroGeometryJsonIconCreator *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroGeometryJsonIconCreator_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->fbo, Sgl$Fbo_new(&tmpNewOwner_1) );
	((HoroEditor$HoroGeometryJsonIconCreator*)self)->size = SuiCore$mkVec2(256, 256) ;
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->drawCtx, Sgl$DrawCtx_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->camera, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->modelPath, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryJsonIconCreator*)self)->savePath, NULL);
    }
	((HoroEditor$HoroGeometryJsonIconCreator*)self)->create = (void*)HoroEditor$HoroGeometryJsonIconCreator$create;
	((HoroEditor$HoroGeometryJsonIconCreator*)self)->showTextureWindow = (void*)HoroEditor$HoroGeometryJsonIconCreator$showTextureWindow;
	((HoroEditor$HoroGeometryJsonIconCreator*)self)->saveAsPng = (void*)HoroEditor$HoroGeometryJsonIconCreator$saveAsPng;
	((HoroEditor$HoroGeometryJsonIconCreator*)self)->draw = (void*)HoroEditor$HoroGeometryJsonIconCreator$draw;
	((HoroEditor$HoroGeometryJsonIconCreator*)self)->mkScene = (void*)HoroEditor$HoroGeometryJsonIconCreator$mkScene;
}

// init function

void HoroEditor$HoroGeometryJsonIconCreator_init(HoroEditor$HoroGeometryJsonIconCreator *self, void *pOwner){
    Vtable_HoroEditor$HoroGeometryJsonIconCreator_init(&_vtable_HoroEditor$HoroGeometryJsonIconCreator);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroGeometryJsonIconCreator;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroGeometryJsonIconCreator_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroGeometryJsonIconCreator * HoroEditor$HoroGeometryJsonIconCreator_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroGeometryJsonIconCreator *self = calloc(1, sizeof(HoroEditor$HoroGeometryJsonIconCreator));
	
    HoroEditor$HoroGeometryJsonIconCreator_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroGeometryJsonIconCreator$create(HoroEditor$HoroGeometryJsonIconCreator *  self, Orc$String *  modelPath){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryJsonIconCreator, modelPath) , modelPath) ;
	self->mkScene(self) ;
	self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )SuiCore$Vec2$width(&self->size) , (int )SuiCore$Vec2$height(&self->size) , true, true, false) ;
	self->draw(self) ;
	self->saveAsPng(self, self->savePath ? self->savePath->str : "geometryicon.png") ;
	self->showTextureWindow(self) ;
}


void  HoroEditor$HoroGeometryJsonIconCreator$showTextureWindow(HoroEditor$HoroGeometryJsonIconCreator *  self){
	Sgl$SglSceneView_showTextureWindow(self->fbo->tex2d, self->size.x, self->size.y) ;
}


void  HoroEditor$HoroGeometryJsonIconCreator$saveAsPng(HoroEditor$HoroGeometryJsonIconCreator *  self, const char *  path){
	self->fbo->bind(self->fbo) ;
	URGC_VAR_CLEANUP_CLASS Sgl$RgbaPixelsReader*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$RgbaPixelsReader_new(&r) ));
	unsigned char *  floats = r->readFromColorAttachment(r, 0, 0, 0, self->size.x, self->size.y) ;
	r->flipY(r) ;
	self->fbo->unbind(self->fbo) ;
	SuiCore$Image_writeRgbas_toPng(path, SuiCore$Vec2$width(&self->size) , SuiCore$Vec2$height(&self->size) , floats) ;
}


void  HoroEditor$HoroGeometryJsonIconCreator$draw(HoroEditor$HoroGeometryJsonIconCreator *  self){
	SuiCore$Vec2 fboSize = self->fbo->getSize(self->fbo) ;
	self->camera->aspect = fboSize.x / fboSize.y;
	self->fbo->startDraw(self->fbo, 1.0, 1.0, 1.0, 0.0, true, true, true) ;
	self->drawCtx->frameSize = fboSize;
	self->drawCtx->draw(self->drawCtx, self->scene, self->camera) ;
	self->fbo->endDraw(self->fbo) ;
}


void  HoroEditor$HoroGeometryJsonIconCreator$mkScene(HoroEditor$HoroGeometryJsonIconCreator *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryJsonIconCreator, scene) , Sgl$Scene_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryJsonIconCreator, camera) , Sgl$PerspectiveCamera_new(&tmpNewOwner_2) ) ;
	((Sgl$Obj3d * )self->camera)->up = SuiCore$mkVec3(0, 1, 0) ;
	self->camera->fov = 45 / 180.0 * Orc$PI;
	self->camera->aspect = 1.0;
	self->camera->nearPlane = 100.1;
	self->camera->farPlane = 5000;
	((Sgl$Obj3d * )self->camera)->position = SuiCore$mkVec3(500, 300, 500) ;
	Sgl$Obj3d$updateWorldMatrixUptoRoot((Sgl$Obj3d * )self->camera) ;
	((Sgl$Obj3d * )self->camera)->lookAt(self->camera, 0, 0, 0) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, self->camera) ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$PointLight*  tmpNewOwner_3 = NULL;
		{
			Sgl$PointLight*  o = Sgl$PointLight_new(&tmpNewOwner_3) ;
			
		
			SuiCore$Vec3$set(&((Sgl$Obj3d * )o)->position, 500, 500, 500) ;
			((SuiCore$Node * )self->scene)->appendChild(self->scene, o) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  mesh = (mesh=NULL,urgc_init_var_class((void**)&mesh, Sgl$Mesh_new(&mesh) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  geom = HoroEditor$HoroGeometry_parseGeometryJson((geom = NULL,&geom), self->modelPath->str) ;
	urgc_set_field_class(mesh, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_4 = NULL;
	{
		Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_4) ;
		
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		o->load(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_5, "../asset/basicWire.matl.json") ->str) ;
		urgc_set_field_class(mesh, (void * )offsetof(Sgl$Mesh, material) , o) ;
	}
	((SuiCore$Node * )self->scene)->appendChild(self->scene, mesh) ;
}



bool  HoroEditor$HoroIconMgr_checkPath(Orc$String *  path){
	return Orc$String$endsWith(path, ".obj")  || Orc$String$endsWith(path, ".matl.json")  || Orc$String$endsWith(path, ".geometry.json") ; 
}


//vtable instance
Vtable_HoroEditor$HoroIconMgr _vtable_HoroEditor$HoroIconMgr;

// init meta

void HoroEditor$HoroIconMgr_initMeta(Vtable_HoroEditor$HoroIconMgr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "cache", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(HoroEditor$HoroIconMgr, cache), true, false, 1);

	orc_metaField_method(&pNext, "load", offsetof(HoroEditor$HoroIconMgr, load));
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

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroIconMgr_fini(HoroEditor$HoroIconMgr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroIconMgr*)self)->cache);

}

// init fields function


void HoroEditor$HoroIconMgr_init_fields(HoroEditor$HoroIconMgr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroIconMgr_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroIconMgr*)self)->cache, Orc$Map_new(&tmpNewOwner_1) );
    }
	((HoroEditor$HoroIconMgr*)self)->load = (void*)HoroEditor$HoroIconMgr$load;
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
SuiCore$Image *  HoroEditor$HoroIconMgr$load(HoroEditor$HoroIconMgr *  self, Orc$String *  path){
	if (!(HoroEditor$HoroIconMgr_checkPath(path) )) {
		return NULL; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  key = Orc$String_md5((key = NULL,&key), path->str) ;
	{
		SuiCore$Image *  img = (SuiCore$Image * )self->cache->get(self->cache, key->str) ;
		if (img != NULL) {
			return img; 
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  iconPath = (iconPath=NULL,urgc_init_var_class((void**)&iconPath, Orc$String$add(Orc$String$add(Orc$str(&tmpReturn_1, ".horo/FileIcons/") , key->str) , ".png") ));
	if (!Orc$Path_exists(iconPath->str) ) {
		Orc$Path_mkdirsByFilePath(iconPath->str) ;
		if (Orc$String$endsWithIgnoreCase(path, ".matl.json") ) {
			URGC_VAR_CLEANUP_CLASS HoroEditor$HoroMaterialIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroMaterialIconCreator_new(&c) ));
			urgc_set_field_class(c, (void * )offsetof(HoroEditor$HoroMaterialIconCreator, savePath) , iconPath) ;
			c->create(c, path) ;
		}
		else if (Orc$String$endsWithIgnoreCase(path, ".obj") ) {
			URGC_VAR_CLEANUP_CLASS HoroEditor$HoroModelIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroModelIconCreator_new(&c) ));
			urgc_set_field_class(c, (void * )offsetof(HoroEditor$HoroModelIconCreator, savePath) , iconPath) ;
			c->create(c, path) ;
		}
		else if (Orc$String$endsWithIgnoreCase(path, ".geometry.json") ) {
			URGC_VAR_CLEANUP_CLASS HoroEditor$HoroGeometryJsonIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroGeometryJsonIconCreator_new(&c) ));
			urgc_set_field_class(c, (void * )offsetof(HoroEditor$HoroGeometryJsonIconCreator, savePath) , iconPath) ;
			c->create(c, path) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$Image*  img = SuiCore$loadImage((img = NULL,&img), iconPath->str) ;
	if (img) {
		
	}
	else {
		printf("加载图标失败。path:%s, iconPath:%s\n", path->str, iconPath->str) ;
	}
	self->cache->put(self->cache, key->str, img) ;
	return img; 
}



HoroEditor$HoroIconMgr *  HoroEditor$insHoroIconMgr(){
	static URGC_VAR_CLEANUP_CLASS HoroEditor$HoroIconMgr*  ins = NULL;
	if (ins == NULL) {
		URGC_VAR_CLEANUP_CLASS HoroEditor$HoroIconMgr*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ins, HoroEditor$HoroIconMgr_new(&tmpNewOwner_1) ) ;
	}
	return ins; 
}

void  HoroEditor$testHoroMaterialIconCreator(){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroMaterialIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroMaterialIconCreator_new(&c) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	c->create(c, Orc$str(&tmpReturn_1, "../asset/basic.matl.json") ) ;
}

void  HoroEditor$testHoroModelIconCreator(){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroModelIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroModelIconCreator_new(&c) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	c->create(c, Orc$str(&tmpReturn_1, "halloween/obj/fence.obj") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	printf("md5:%s\n", Orc$String_md5(&tmpReturn_2, "halloween/obj/fence.obj") ->str) ;
}

void  HoroEditor$testHoroGeometryJsonIconCreator(){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroGeometryJsonIconCreator*  c = (c=NULL,urgc_init_var_class((void**)&c, HoroEditor$HoroGeometryJsonIconCreator_new(&c) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	c->create(c, Orc$str(&tmpReturn_1, "Geometry/box2.geometry.json") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	printf("md5:%s\n", Orc$String_md5(&tmpReturn_2, "halloween/obj/fence.obj") ->str) ;
}

void  HoroEditor$testHoroIconMgr(){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroIconMgr*  mgr = (mgr=NULL,urgc_init_var_class((void**)&mgr, HoroEditor$HoroIconMgr_new(&mgr) ));
	mgr->load(mgr, "halloween/obj/fence.obj") ;
}



