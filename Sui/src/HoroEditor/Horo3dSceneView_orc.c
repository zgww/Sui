
#include "Horo3dSceneView_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DirLight_orc.h"
#include "../Sgl/PixelsReader_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Focus_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_HoroEditor$Horo3dSceneView _vtable_HoroEditor$Horo3dSceneView;

// init meta

void HoroEditor$Horo3dSceneView_initMeta(Vtable_HoroEditor$Horo3dSceneView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(HoroEditor$Horo3dSceneView, fbo), true, false, 1);
	orc_metaField_class(&pNext, "matl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(HoroEditor$Horo3dSceneView, matl), true, false, 1);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(HoroEditor$Horo3dSceneView, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(HoroEditor$Horo3dSceneView, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(HoroEditor$Horo3dSceneView, camera), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(HoroEditor$Horo3dSceneView, drag), true, false, 1);
	orc_metaField_primitive(&pNext, "rotateY", OrcMetaType_float, offsetof(HoroEditor$Horo3dSceneView, rotateY), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "scale", OrcMetaType_float, offsetof(HoroEditor$Horo3dSceneView, scale), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "mkBaseScene", offsetof(HoroEditor$Horo3dSceneView, mkBaseScene));
}


// vtable init


Vtable_HoroEditor$Horo3dSceneView* Vtable_HoroEditor$Horo3dSceneView_init(Vtable_HoroEditor$Horo3dSceneView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$Horo3dSceneView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiView$ImageView_init(&_vtable_SuiView$ImageView);

	// init by super vtable init function
    Vtable_SuiView$ImageView_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiView$ImageView;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$Horo3dSceneView_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$Horo3dSceneView";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$Horo3dSceneView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$Horo3dSceneView_fini(HoroEditor$Horo3dSceneView *self){
	//super fini
    SuiView$ImageView_fini((SuiView$ImageView *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->fbo);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->matl);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->scene);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->camera);
	urgc_fini_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->drag);

}

// init fields function


void HoroEditor$Horo3dSceneView_init_fields(HoroEditor$Horo3dSceneView *self){
	//super class
    SuiView$ImageView_init_fields((SuiView$ImageView*)self);

    ((Object*)self)->fini = (void*)HoroEditor$Horo3dSceneView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->fbo, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->matl, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->drawCtx, Sgl$DrawCtx_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->camera, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$Horo3dSceneView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_2) );
	((HoroEditor$Horo3dSceneView*)self)->rotateY = 0;
	((HoroEditor$Horo3dSceneView*)self)->scale = 0.02;
    }
	((SuiCore$ViewBase*)self)->draw_self = (void*)HoroEditor$Horo3dSceneView$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)HoroEditor$Horo3dSceneView$onEvent;
	((HoroEditor$Horo3dSceneView*)self)->mkBaseScene = (void*)HoroEditor$Horo3dSceneView$mkBaseScene;
}

// init function

void HoroEditor$Horo3dSceneView_init(HoroEditor$Horo3dSceneView *self, void *pOwner){
    Vtable_HoroEditor$Horo3dSceneView_init(&_vtable_HoroEditor$Horo3dSceneView);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$Horo3dSceneView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$Horo3dSceneView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$Horo3dSceneView * HoroEditor$Horo3dSceneView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$Horo3dSceneView *self = calloc(1, sizeof(HoroEditor$Horo3dSceneView));
	
    HoroEditor$Horo3dSceneView_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$Horo3dSceneView$draw_self(HoroEditor$Horo3dSceneView *  self, SuiCore$Canvas *  canvas){
	{
		bool  mkFbo = false;
		if (self->fbo == NULL) {
			mkFbo = true;
		}
		else if (self->fbo) {
			SuiCore$Vec2 size = self->fbo->getSize(self->fbo) ;
			if (size.x != (int )((SuiCore$ViewBase * )self)->frame.width || size.y != (int )((SuiCore$ViewBase * )self)->frame.height) {
				mkFbo = true;
			}
		}
		if (mkFbo) {
			printf("重建fbo. size:%f,%f\n", ((SuiCore$ViewBase * )self)->frame.width, ((SuiCore$ViewBase * )self)->frame.height) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_1 = NULL;
			urgc_set_field_class(self, (void * )offsetof(HoroEditor$Horo3dSceneView, fbo) , Sgl$Fbo_new(&tmpNewOwner_1) ) ;
			self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )((SuiCore$ViewBase * )self)->frame.width, (int )((SuiCore$ViewBase * )self)->frame.height, true, true, false) ;
		}
	}
	if (self->fbo) {
		SuiCore$Vec2 fboSize = self->fbo->getSize(self->fbo) ;
		self->camera->aspect = fboSize.x / fboSize.y;
		self->fbo->startDraw(self->fbo, 0.0, 0.0, 0.0, 1.0, true, true, true) ;
		self->drawCtx->frameSize = fboSize;
		self->drawCtx->draw(self->drawCtx, self->scene, self->camera) ;
		self->fbo->endDraw(self->fbo) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ImageView, _img) , Sgl$loadImageByTex2d(&tmpReturn_2, self->fbo->tex2d) ) ;
	}
	SuiView$ImageView$draw_self(self, canvas) ;
}


void  HoroEditor$Horo3dSceneView$onEvent(HoroEditor$Horo3dSceneView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isMouseDown && ((SuiCore$ViewEvent * )me)->isBubble(me) ) {
			self->drag->onMouseDown(self->drag, me) ;
		}
	}
}


void  HoroEditor$Horo3dSceneView$mkBaseScene(HoroEditor$Horo3dSceneView *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$Horo3dSceneView, scene) , Sgl$Scene_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$Horo3dSceneView, camera) , Sgl$PerspectiveCamera_new(&tmpNewOwner_2) ) ;
	self->camera->target = SuiCore$mkVec3(0, 0, 0) ;
	((Sgl$Obj3d * )self->camera)->up = SuiCore$mkVec3(0, 1, 0) ;
	self->camera->fov = 45 / 180.0 * Orc$PI;
	self->camera->aspect = 1.0;
	self->camera->nearPlane = 100.1;
	self->camera->farPlane = 5000;
	((Sgl$Obj3d * )self->camera)->position = SuiCore$mkVec3(0, -100, 1000) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, self->camera) ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$DirLight*  l = (l=NULL,urgc_init_var_class((void**)&l, Sgl$DirLight_new(&l) ));
		SuiCore$Vec3$set(&((Sgl$Obj3d * )l)->position, 0, 10, 0) ;
		((SuiCore$Node * )self->scene)->appendChild(self->scene, l) ;
	}
	printf("Base scene and camera initialized\n") ;
}



HoroEditor$Horo3dSceneView*  HoroEditor$mkHoro3dSceneView(HoroEditor$Horo3dSceneView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (HoroEditor$Horo3dSceneView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_HoroEditor$Horo3dSceneView_init(NULL)) ) ; 
}



