
#include "SglSceneView_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Orc/Orc.h"
#include "./Mat_orc.h"
#include "./Program_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Math_orc.h"
#include "../Json/Json_orc.h"
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
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/View/ColorPicker_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "./Tex2d_orc.h"
#include "./Fbo_orc.h"
#include "./Draw_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"
#include "./DrawCtx_orc.h"
#include "./Scene_orc.h"
#include "./Buffer_orc.h"
#include "./PointLight_orc.h"
#include "./DirLight_orc.h"
#include "./PixelsReader_orc.h"
#include "./PerspectiveCamera_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$SglSceneView _vtable_Sgl$SglSceneView;

// init meta

void Sgl$SglSceneView_initMeta(Vtable_Sgl$SglSceneView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(Sgl$SglSceneView, fbo), true, false, 1);
	orc_metaField_class(&pNext, "matl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$SglSceneView, matl), true, false, 1);
	orc_metaField_class(&pNext, "drawObj", ((Vtable_Object*)Vtable_Sgl$Draw_init(0)), offsetof(Sgl$SglSceneView, drawObj), true, false, 1);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(Sgl$SglSceneView, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(Sgl$SglSceneView, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(Sgl$SglSceneView, camera), true, false, 1);
	orc_metaField_class(&pNext, "depthPreview", ((Vtable_Object*)Vtable_Sgl$DepthTexturePreview_init(0)), offsetof(Sgl$SglSceneView, depthPreview), true, false, 1);
	orc_metaField_primitive(&pNext, "rotateY", OrcMetaType_float, offsetof(Sgl$SglSceneView, rotateY), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "scale", OrcMetaType_float, offsetof(Sgl$SglSceneView, scale), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(Sgl$SglSceneView, drag), true, false, 1);

	orc_metaField_method(&pNext, "buildDrawObj", offsetof(Sgl$SglSceneView, buildDrawObj));
	orc_metaField_method(&pNext, "applyModel", offsetof(Sgl$SglSceneView, applyModel));
	orc_metaField_method(&pNext, "mkBaseScene", offsetof(Sgl$SglSceneView, mkBaseScene));
}


// vtable init


Vtable_Sgl$SglSceneView* Vtable_Sgl$SglSceneView_init(Vtable_Sgl$SglSceneView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$SglSceneView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiView$ImageView_init(&_vtable_SuiView$ImageView);

	// init by super vtable init function
    Vtable_SuiView$ImageView_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiView$ImageView;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$SglSceneView_new;
    ((Vtable_Object*)pvt)->className = "Sgl$SglSceneView";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$SglSceneView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$SglSceneView_fini(Sgl$SglSceneView *self){
	//super fini
    SuiView$ImageView_fini((SuiView$ImageView *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->fbo);
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->matl);
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->drawObj);
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->scene);
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->camera);
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->depthPreview);
	urgc_fini_field_class(self, (void**)&((Sgl$SglSceneView*)self)->drag);

}

// init fields function


void Sgl$SglSceneView_init_fields(Sgl$SglSceneView *self){
	//super class
    SuiView$ImageView_init_fields((SuiView$ImageView*)self);

    ((Object*)self)->fini = (void*)Sgl$SglSceneView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->fbo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->matl, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->drawObj, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->drawCtx, Sgl$DrawCtx_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->camera, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$DepthTexturePreview*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->depthPreview, Sgl$DepthTexturePreview_new(&tmpNewOwner_2) );
	((Sgl$SglSceneView*)self)->rotateY = 0;
	((Sgl$SglSceneView*)self)->scale = 0.02;
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$SglSceneView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_3) );
    }
	((Sgl$SglSceneView*)self)->buildDrawObj = (void*)Sgl$SglSceneView$buildDrawObj;
	((SuiCore$ViewBase*)self)->draw_self = (void*)Sgl$SglSceneView$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)Sgl$SglSceneView$onEvent;
	((Sgl$SglSceneView*)self)->applyModel = (void*)Sgl$SglSceneView$applyModel;
	((Sgl$SglSceneView*)self)->mkBaseScene = (void*)Sgl$SglSceneView$mkBaseScene;
}

// init function

void Sgl$SglSceneView_init(Sgl$SglSceneView *self, void *pOwner){
    Vtable_Sgl$SglSceneView_init(&_vtable_Sgl$SglSceneView);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$SglSceneView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$SglSceneView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$SglSceneView * Sgl$SglSceneView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$SglSceneView *self = calloc(1, sizeof(Sgl$SglSceneView));
	
    Sgl$SglSceneView_init(self, pOwner);
    return self;
}


// class members
void  Sgl$SglSceneView$buildDrawObj(Sgl$SglSceneView *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Draw*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$SglSceneView, drawObj) , Sgl$Draw_new(&tmpNewOwner_1) ) ;
	urgc_set_field_class(self->drawObj, (void * )offsetof(Sgl$Draw, material) , self->matl) ;
}


void  Sgl$SglSceneView$draw_self(Sgl$SglSceneView *  self, SuiCore$Canvas *  canvas){
	{
		bool  mkFbo = false;
		if (self->drawObj && self->fbo == NULL) {
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
			urgc_set_field_class(self, (void * )offsetof(Sgl$SglSceneView, fbo) , Sgl$Fbo_new(&tmpNewOwner_1) ) ;
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


void  Sgl$SglSceneView$onEvent(Sgl$SglSceneView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isMouseDown && ((SuiCore$ViewEvent * )me)->isBubble(me) ) {
			self->drag->onMouseDown(self->drag, me) ;
		}
	}
}


void  Sgl$SglSceneView$applyModel(Sgl$SglSceneView *  self){
	if (self->drawObj && self->drawObj->material) {
		{
			Sgl$Mat *  o = &self->drawObj->material->model;
			
		
			Sgl$Mat$identity(o) ;
			Sgl$Mat$rotateY(o, self->rotateY) ;
			Sgl$Mat$scale(o, self->scale, self->scale, self->scale) ;
		}
	}
}


void  Sgl$SglSceneView$mkBaseScene(Sgl$SglSceneView *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$SglSceneView, scene) , Sgl$Scene_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$SglSceneView, camera) , Sgl$PerspectiveCamera_new(&tmpNewOwner_2) ) ;
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



Sgl$SglSceneView*  Sgl$mkSglSceneView(Sgl$SglSceneView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (Sgl$SglSceneView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_Sgl$SglSceneView_init(NULL)) ) ; 
}

void  Sgl$SglSceneView_showTextureWindow(Sgl$Tex2d *  tex, int  w, int  h){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  iv = (iv=NULL,urgc_init_var_class((void**)&iv, SuiView$ImageView_new(&iv) ));
		{
			SuiView$ImageView*  o = iv;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_328_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(win, (void * )offsetof(Sui$Window, rootView) , iv) ;
			URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_2 = NULL;
			urgc_set_field_class(iv, (void * )offsetof(SuiView$ImageView, _img) , Sgl$loadImageByTex2d(&tmpReturn_2, tex) ) ;
		}
		o->setTitle(o, "纹理预览") ;
		o->setSize(o, w, h) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


//vtable instance
Vtable_Sgl$DepthTexturePreview _vtable_Sgl$DepthTexturePreview;

// init meta

void Sgl$DepthTexturePreview_initMeta(Vtable_Sgl$DepthTexturePreview *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "depthTex", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$DepthTexturePreview, depthTex), true, false, 1);
	orc_metaField_class(&pNext, "depthRedBuffer", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$DepthTexturePreview, depthRedBuffer), true, false, 1);
	orc_metaField_class(&pNext, "depthPixelsReader", ((Vtable_Object*)Vtable_Sgl$DepthFloatPixlesReader_init(0)), offsetof(Sgl$DepthTexturePreview, depthPixelsReader), true, false, 1);

	orc_metaField_method(&pNext, "init_readPixels", offsetof(Sgl$DepthTexturePreview, init_readPixels));
	orc_metaField_method(&pNext, "init", offsetof(Sgl$DepthTexturePreview, init));
	orc_metaField_method(&pNext, "showTextureWindow", offsetof(Sgl$DepthTexturePreview, showTextureWindow));
	orc_metaField_method(&pNext, "readPixels", offsetof(Sgl$DepthTexturePreview, readPixels));
}


// vtable init


Vtable_Sgl$DepthTexturePreview* Vtable_Sgl$DepthTexturePreview_init(Vtable_Sgl$DepthTexturePreview* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$DepthTexturePreview;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$DepthTexturePreview_new;
    ((Vtable_Object*)pvt)->className = "Sgl$DepthTexturePreview";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$DepthTexturePreview_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$DepthTexturePreview_fini(Sgl$DepthTexturePreview *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$DepthTexturePreview*)self)->depthTex);
	urgc_fini_field_class(self, (void**)&((Sgl$DepthTexturePreview*)self)->depthRedBuffer);
	urgc_fini_field_class(self, (void**)&((Sgl$DepthTexturePreview*)self)->depthPixelsReader);

}

// init fields function


void Sgl$DepthTexturePreview_init_fields(Sgl$DepthTexturePreview *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$DepthTexturePreview_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$DepthTexturePreview*)self)->depthTex, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DepthTexturePreview*)self)->depthRedBuffer, Sgl$Buffer_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$DepthFloatPixlesReader*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$DepthTexturePreview*)self)->depthPixelsReader, Sgl$DepthFloatPixlesReader_new(&tmpNewOwner_2) );
    }
	((Sgl$DepthTexturePreview*)self)->init_readPixels = (void*)Sgl$DepthTexturePreview$init_readPixels;
	((Sgl$DepthTexturePreview*)self)->init = (void*)Sgl$DepthTexturePreview$init;
	((Sgl$DepthTexturePreview*)self)->showTextureWindow = (void*)Sgl$DepthTexturePreview$showTextureWindow;
	((Sgl$DepthTexturePreview*)self)->readPixels = (void*)Sgl$DepthTexturePreview$readPixels;
}

// init function

void Sgl$DepthTexturePreview_init(Sgl$DepthTexturePreview *self, void *pOwner){
    Vtable_Sgl$DepthTexturePreview_init(&_vtable_Sgl$DepthTexturePreview);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$DepthTexturePreview;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$DepthTexturePreview_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$DepthTexturePreview * Sgl$DepthTexturePreview_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$DepthTexturePreview *self = calloc(1, sizeof(Sgl$DepthTexturePreview));
	
    Sgl$DepthTexturePreview_init(self, pOwner);
    return self;
}


// class members
void  Sgl$DepthTexturePreview$init_readPixels(Sgl$DepthTexturePreview *  self, int  w, int  h){
	self->init(self, w, h) ;
	self->readPixels(self) ;
}


void  Sgl$DepthTexturePreview$init(Sgl$DepthTexturePreview *  self, int  width, int  height){
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$DepthTexturePreview, depthTex) , Sgl$Tex2d_new(&tmpNewOwner_1) ) ;
	self->depthTex->initZerosRgba(self->depthTex, width, height) ;
}


void  Sgl$DepthTexturePreview$showTextureWindow(Sgl$DepthTexturePreview *  self){
	Sgl$SglSceneView_showTextureWindow(self->depthTex, 400, 400) ;
}


void  Sgl$DepthTexturePreview$readPixels(Sgl$DepthTexturePreview *  self){
	SuiCore$Vec2 size = self->depthTex->Size(self->depthTex) ;
	Sgl$DepthFloatPixlesReader *  dr = self->depthPixelsReader;
	int  w = self->depthTex->width;
	int  h = self->depthTex->height;
	float *  floats = dr->read(dr, 0, 0, w, h) ;
	SuiCore$Image_convertFloatsToRgbaBuffer(self->depthRedBuffer, w, h, floats) ;
	self->depthTex->image2dRgba(self->depthTex, self->depthRedBuffer->data, w, h) ;
}





