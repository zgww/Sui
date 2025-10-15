
#include "FboView_orc.h" 

#include <stdio.h>
#include <math.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Number_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/GeometryPlane_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryCapsule_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/GeometryHeightMap_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DirLight_orc.h"
#include "../Sgl/PixelsReader_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/SplitterView_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Focus_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Euler_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/KeyEvent_orc.h"
#include "../SuiDesigner/Theme_orc.h"
#include "../SuiDesigner/Insp_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"


// static struct 
typedef struct tagSgl$__Block_91_15 Sgl$__Block_91_15;

typedef struct tagSgl$__Closure_95_27 Sgl$__Closure_95_27;



struct tagSgl$__Block_91_15 {
	Sgl$FboView*  self ;
};





struct tagSgl$__Closure_95_27 {
	void  (*invoke)(Sgl$__Closure_95_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	Sgl$__Block_91_15*  __var___Block_91_15 ;
};





// static function declaration
static void  __finiBlock___Block_91_15(Sgl$__Block_91_15 *  self);
static void  __fn___Closure_95_27(Sgl$__Closure_95_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_95_27(Sgl$__Closure_95_27 *  self);
static Sgl$__Closure_95_27*  __make___Closure_95_27(Sgl$__Closure_95_27 **  __outRef__, Sgl$__Block_91_15 *  __var___Block_91_15);



//vtable instance
Vtable_Sgl$FboView _vtable_Sgl$FboView;

// init meta

void Sgl$FboView_initMeta(Vtable_Sgl$FboView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(Sgl$FboView, fbo), true, false, 1);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(Sgl$FboView, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(Sgl$FboView, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(Sgl$FboView, camera), true, false, 1);
	orc_metaField_class(&pNext, "groundGrid", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(Sgl$FboView, groundGrid), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(Sgl$FboView, drag), true, false, 1);

	orc_metaField_method(&pNext, "dragOrbit", offsetof(Sgl$FboView, dragOrbit));
	orc_metaField_method(&pNext, "mkBaseScene", offsetof(Sgl$FboView, mkBaseScene));
}


// vtable init


Vtable_Sgl$FboView* Vtable_Sgl$FboView_init(Vtable_Sgl$FboView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$FboView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiView$ImageView_init(&_vtable_SuiView$ImageView);

	// init by super vtable init function
    Vtable_SuiView$ImageView_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiView$ImageView;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$FboView_new;
    ((Vtable_Object*)pvt)->className = "Sgl$FboView";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$FboView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$FboView_fini(Sgl$FboView *self){
	//super fini
    SuiView$ImageView_fini((SuiView$ImageView *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$FboView*)self)->fbo);
	urgc_fini_field_class(self, (void**)&((Sgl$FboView*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((Sgl$FboView*)self)->scene);
	urgc_fini_field_class(self, (void**)&((Sgl$FboView*)self)->camera);
	urgc_fini_field_class(self, (void**)&((Sgl$FboView*)self)->groundGrid);
	urgc_fini_field_class(self, (void**)&((Sgl$FboView*)self)->drag);

}

// init fields function


void Sgl$FboView_init_fields(Sgl$FboView *self){
	//super class
    SuiView$ImageView_init_fields((SuiView$ImageView*)self);

    ((Object*)self)->fini = (void*)Sgl$FboView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$FboView*)self)->fbo, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$FboView*)self)->drawCtx, Sgl$DrawCtx_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((Sgl$FboView*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$FboView*)self)->camera, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$FboView*)self)->groundGrid, Sgl$Mesh_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$FboView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_3) );
	urgc_set_field(self, (void**)&((Sgl$FboView*)self)->cbDraw, NULL);
    }
	((Sgl$FboView*)self)->dragOrbit = (void*)Sgl$FboView$dragOrbit;
	((Object*)self)->ctor = (void*)Sgl$FboView$ctor;
	((SuiCore$ViewBase*)self)->draw_self = (void*)Sgl$FboView$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)Sgl$FboView$onEvent;
	((Sgl$FboView*)self)->mkBaseScene = (void*)Sgl$FboView$mkBaseScene;
}

// init function

void Sgl$FboView_init(Sgl$FboView *self, void *pOwner){
    Vtable_Sgl$FboView_init(&_vtable_Sgl$FboView);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$FboView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$FboView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$FboView * Sgl$FboView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$FboView *self = calloc(1, sizeof(Sgl$FboView));
	
    Sgl$FboView_init(self, pOwner);
    return self;
}


// class members
void  Sgl$FboView$dragOrbit(Sgl$FboView *  self, SuiView$Drag *  d){
	SuiCore$Euler e;
	SuiCore$Euler$setFromVector3(&e, ((Sgl$Obj3d * )self->camera)->rotation, NULL) ;
	SuiCore$Euler$reorder(&e, "YXZ") ;
	e.y += d->deltaPos.x * 0.001;
	e.x += d->deltaPos.y * 0.001;
	SuiCore$Euler$reorder(&e, "XYZ") ;
	SuiCore$Vec3$setFromEuler(&((Sgl$Obj3d * )self->camera)->rotation, e) ;
}


void  Sgl$FboView$ctor(Sgl$FboView *  self){
	URGC_VAR_CLEANUP Sgl$__Block_91_15*  __var___Block_91_15 = (__var___Block_91_15=NULL,urgc_init_var((void**)&__var___Block_91_15, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_91_15) , __finiBlock___Block_91_15) ));
	urgc_set_field_class(__var___Block_91_15, (void * )offsetof(Sgl$__Block_91_15, self) , self) ;
	SuiCore$Listener$ctor(self) ;
	self->mkBaseScene(self) ;
	URGC_VAR_CLEANUP Sgl$__Closure_95_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_95_27(&tmpReturn_1, __var___Block_91_15) ) ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryPlane*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryPlane_new(&geom) ));
		geom->planeType = 1;
		geom->width = 10000;
		geom->height = 10000;
		geom->widthSegments = 100;
		geom->heightSegments = 100;
		((Sgl$Geometry * )geom)->build(geom) ;
		urgc_set_field_class(self->groundGrid, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		matl->load(matl, Orc$Path_resolveFromExecutionDir(&tmpReturn_2, "../asset/basic.matl.json") ->str) ;
		urgc_set_field_class(self->groundGrid, (void * )offsetof(Sgl$Mesh, material) , matl) ;
	}
}


void  Sgl$FboView$draw_self(Sgl$FboView *  self, SuiCore$Canvas *  canvas){
	if (((SuiCore$ViewBase * )self)->frame.width <= 0 || ((SuiCore$ViewBase * )self)->frame.height <= 0) {
		return ; 
	}
	if (1) {
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
			urgc_set_field_class(self, (void * )offsetof(Sgl$FboView, fbo) , Sgl$Fbo_new(&tmpNewOwner_1) ) ;
			self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )((SuiCore$ViewBase * )self)->frame.width, (int )((SuiCore$ViewBase * )self)->frame.height, true, true, false) ;
		}
	}
	((SuiCore$View * )self)->backgroundColor = 0xff00ff00;
	if (self->fbo) {
		SuiCore$Vec2 fboSize = self->fbo->getSize(self->fbo) ;
		self->camera->aspect = fboSize.x / fboSize.y;
		self->fbo->startDraw(self->fbo, 0.0, 0.0, 0.0, 1.0, true, true, true) ;
		self->drawCtx->frameSize = fboSize;
		self->drawCtx->draw(self->drawCtx, self->scene, self->camera) ;
		if (self->cbDraw) {
			(*(self->cbDraw))((void * )(self->cbDraw), self) ;
		}
		((Sgl$Obj3d * )self->groundGrid)->draw(self->groundGrid, self->drawCtx) ;
		self->fbo->endDraw(self->fbo) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ImageView, _img) , Sgl$loadImageByTex2d(&tmpReturn_2, self->fbo->tex2d) ) ;
	}
	SuiView$ImageView$draw_self(self, canvas) ;
}


void  Sgl$FboView$onEvent(Sgl$FboView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isMouseDown && ((SuiCore$ViewEvent * )me)->isBubble(me) ) {
			self->drag->onMouseDown(self->drag, me) ;
		}
	}
}


void  Sgl$FboView$mkBaseScene(Sgl$FboView *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$FboView, scene) , Sgl$Scene_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$FboView, camera) , Sgl$PerspectiveCamera_new(&tmpNewOwner_2) ) ;
	((Sgl$Obj3d * )self->camera)->up = SuiCore$mkVec3(0, 1, 0) ;
	self->camera->fov = 45 / 180.0 * Orc$PI;
	self->camera->aspect = 1.0;
	self->camera->nearPlane = 100.1;
	self->camera->farPlane = 5000;
	((Sgl$Obj3d * )self->camera)->position = SuiCore$mkVec3(100, 500, 500) ;
	Sgl$Obj3d$updateWorldMatrixUptoRoot((Sgl$Obj3d * )self->camera) ;
	((Sgl$Obj3d * )self->camera)->lookAt(self->camera, 0, 0, 0) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, self->camera) ;
	printf("Base scene and camera initialized\n") ;
}



static void  __finiBlock___Block_91_15(Sgl$__Block_91_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_91_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_95_27(Sgl$__Closure_95_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("dragging scene\n") ;
		self->__var___Block_91_15->self->dragOrbit(self->__var___Block_91_15->self, d) ;
	}
}

static void  __fini___Closure_95_27(Sgl$__Closure_95_27 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_95_27, __var___Block_91_15) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_95_27*  __make___Closure_95_27(Sgl$__Closure_95_27 **  __outRef__, Sgl$__Block_91_15 *  __var___Block_91_15){
	URGC_VAR_CLEANUP Sgl$__Closure_95_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_95_27) , __fini___Closure_95_27) ));
	self->invoke = __fn___Closure_95_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_95_27, __var___Block_91_15) , __var___Block_91_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

Sgl$FboView*  Sgl$mkFboView(Sgl$FboView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (Sgl$FboView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_Sgl$FboView_init(NULL)) ) ; 
}



