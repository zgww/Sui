
#include "SceneView_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Mat2d_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Json/Json_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./RegisterNodes_orc.h"
#include "./DrawDegree_orc.h"
#include "./UiAction_orc.h"
#include "./ANode_orc.h"
#include "./Gizmo_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_223_15 SuiDesigner$__Block_223_15;

typedef struct tagSuiDesigner$__Block_334_37 SuiDesigner$__Block_334_37;

typedef struct tagSuiDesigner$__Block_421_29 SuiDesigner$__Block_421_29;

typedef struct tagSuiDesigner$__Block_447_26 SuiDesigner$__Block_447_26;

typedef struct tagSuiDesigner$__Block_449_62 SuiDesigner$__Block_449_62;

typedef struct tagSuiDesigner$__Closure_226_27 SuiDesigner$__Closure_226_27;

typedef struct tagSuiDesigner$__Closure_onActive_337 SuiDesigner$__Closure_onActive_337;

typedef struct tagSuiDesigner$__Closure_399_26 SuiDesigner$__Closure_399_26;

typedef struct tagSuiDesigner$__Closure_429_30 SuiDesigner$__Closure_429_30;

typedef struct tagSuiDesigner$__Closure_438_32 SuiDesigner$__Closure_438_32;

typedef struct tagSuiDesigner$__Closure_460_42 SuiDesigner$__Closure_460_42;



struct tagSuiDesigner$__Block_223_15 {
	SuiDesigner$SceneView*  self ;
};





struct tagSuiDesigner$__Block_334_37 {
	SuiDesigner$SceneView*  self ;
};





struct tagSuiDesigner$__Block_421_29 {
	SuiDesigner$SceneView*  self ;
};





struct tagSuiDesigner$__Block_447_26 {
	SuiDesigner$ANode *  sel ;
};





struct tagSuiDesigner$__Block_449_62 {
	SuiCore$View *  selView ;
};





struct tagSuiDesigner$__Closure_226_27 {
	void  (*invoke)(SuiDesigner$__Closure_226_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_223_15*  __var___Block_223_15 ;
};





struct tagSuiDesigner$__Closure_onActive_337 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_337 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_334_37*  __var___Block_334_37 ;
};





struct tagSuiDesigner$__Closure_399_26 {
	void  (*invoke)(SuiDesigner$__Closure_399_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_429_30 {
	bool  (*invoke)(SuiDesigner$__Closure_429_30 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_421_29*  __var___Block_421_29 ;
};





struct tagSuiDesigner$__Closure_438_32 {
	void  (*invoke)(SuiDesigner$__Closure_438_32 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_460_42 {
	void  (*invoke)(SuiDesigner$__Closure_460_42 *  self, SuiCore$Rect newr);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_447_26*  __var___Block_447_26 ;
	SuiDesigner$__Block_449_62*  __var___Block_449_62 ;
};





// static function declaration
static void  __finiBlock___Block_223_15(SuiDesigner$__Block_223_15 *  self);
static void  __finiBlock___Block_334_37(SuiDesigner$__Block_334_37 *  self);
static void  __finiBlock___Block_421_29(SuiDesigner$__Block_421_29 *  self);
static void  __finiBlock___Block_447_26(SuiDesigner$__Block_447_26 *  self);
static void  __finiBlock___Block_449_62(SuiDesigner$__Block_449_62 *  self);
static void  __fn___Closure_226_27(SuiDesigner$__Closure_226_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_226_27(SuiDesigner$__Closure_226_27 *  self);
static SuiDesigner$__Closure_226_27*  __make___Closure_226_27(SuiDesigner$__Closure_226_27 **  __outRef__, SuiDesigner$__Block_223_15 *  __var___Block_223_15);
static void  __fn___Closure_onActive_337(SuiDesigner$__Closure_onActive_337 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_337(SuiDesigner$__Closure_onActive_337 *  self);
static SuiDesigner$__Closure_onActive_337*  __make___Closure_onActive_337(SuiDesigner$__Closure_onActive_337 **  __outRef__, SuiDesigner$__Block_334_37 *  __var___Block_334_37);
static void  __fn___Closure_399_26(SuiDesigner$__Closure_399_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_399_26(SuiDesigner$__Closure_399_26 *  self);
static SuiDesigner$__Closure_399_26*  __make___Closure_399_26(SuiDesigner$__Closure_399_26 **  __outRef__);
static bool  __fn___Closure_429_30(SuiDesigner$__Closure_429_30 *  self);
static void  __fini___Closure_429_30(SuiDesigner$__Closure_429_30 *  self);
static SuiDesigner$__Closure_429_30*  __make___Closure_429_30(SuiDesigner$__Closure_429_30 **  __outRef__, SuiDesigner$__Block_421_29 *  __var___Block_421_29);
static void  __fn___Closure_438_32(SuiDesigner$__Closure_438_32 *  self, SuiView$Drag *  d);
static void  __fini___Closure_438_32(SuiDesigner$__Closure_438_32 *  self);
static SuiDesigner$__Closure_438_32*  __make___Closure_438_32(SuiDesigner$__Closure_438_32 **  __outRef__);
static void  __fn___Closure_460_42(SuiDesigner$__Closure_460_42 *  self, SuiCore$Rect newr);
static void  __fini___Closure_460_42(SuiDesigner$__Closure_460_42 *  self);
static SuiDesigner$__Closure_460_42*  __make___Closure_460_42(SuiDesigner$__Closure_460_42 **  __outRef__, SuiDesigner$__Block_447_26 *  __var___Block_447_26, SuiDesigner$__Block_449_62 *  __var___Block_449_62);



//vtable instance
Vtable_SuiDesigner$ImageChessBg _vtable_SuiDesigner$ImageChessBg;

// init meta

void SuiDesigner$ImageChessBg_initMeta(Vtable_SuiDesigner$ImageChessBg *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "width", OrcMetaType_int, offsetof(SuiDesigner$ImageChessBg, width), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "height", OrcMetaType_int, offsetof(SuiDesigner$ImageChessBg, height), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color0", OrcMetaType_int, offsetof(SuiDesigner$ImageChessBg, color0), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color1", OrcMetaType_int, offsetof(SuiDesigner$ImageChessBg, color1), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "img", ((Vtable_Object*)Vtable_SuiCore$Image_init(0)), offsetof(SuiDesigner$ImageChessBg, img), true, false, 1);

	orc_metaField_method(&pNext, "new_createChessBg_inMemory", offsetof(SuiDesigner$ImageChessBg, new_createChessBg_inMemory));
	orc_metaField_method(&pNext, "gocChessBgImage", offsetof(SuiDesigner$ImageChessBg, gocChessBgImage));
}


// vtable init


Vtable_SuiDesigner$ImageChessBg* Vtable_SuiDesigner$ImageChessBg_init(Vtable_SuiDesigner$ImageChessBg* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ImageChessBg;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ImageChessBg_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ImageChessBg";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ImageChessBg_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ImageChessBg_fini(SuiDesigner$ImageChessBg *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ImageChessBg*)self)->img);

}

// init fields function


void SuiDesigner$ImageChessBg_init_fields(SuiDesigner$ImageChessBg *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ImageChessBg_fini;
	//fields
    {
	((SuiDesigner$ImageChessBg*)self)->width = 32;
	((SuiDesigner$ImageChessBg*)self)->height = 32;
	((SuiDesigner$ImageChessBg*)self)->color0 = 0xff333333;
	((SuiDesigner$ImageChessBg*)self)->color1 = 0xff000000;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ImageChessBg*)self)->img, NULL);
    }
	((SuiDesigner$ImageChessBg*)self)->new_createChessBg_inMemory = (void*)SuiDesigner$ImageChessBg$new_createChessBg_inMemory;
	((SuiDesigner$ImageChessBg*)self)->gocChessBgImage = (void*)SuiDesigner$ImageChessBg$gocChessBgImage;
}

// init function

void SuiDesigner$ImageChessBg_init(SuiDesigner$ImageChessBg *self, void *pOwner){
    Vtable_SuiDesigner$ImageChessBg_init(&_vtable_SuiDesigner$ImageChessBg);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ImageChessBg;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ImageChessBg_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ImageChessBg * SuiDesigner$ImageChessBg_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ImageChessBg *self = calloc(1, sizeof(SuiDesigner$ImageChessBg));
	
    SuiDesigner$ImageChessBg_init(self, pOwner);
    return self;
}


// class members
char *  SuiDesigner$ImageChessBg$new_createChessBg_inMemory(SuiDesigner$ImageChessBg *  self, int  w, int  h){
	char *  data = malloc(w * h * 4) ;
	int  hw = w / 2;
	int  hh = h / 2;
	int  a0 = SuiCore$colorGetA(self->color0) ;
	int  r0 = SuiCore$colorGetR(self->color0) ;
	int  g0 = SuiCore$colorGetG(self->color0) ;
	int  b0 = SuiCore$colorGetB(self->color0) ;
	int  a1 = SuiCore$colorGetA(self->color1) ;
	int  r1 = SuiCore$colorGetR(self->color1) ;
	int  g1 = SuiCore$colorGetG(self->color1) ;
	int  b1 = SuiCore$colorGetB(self->color1) ;
	for (int  y = 0; y < h; y++) {
		for (int  x = 0; x < w; x++) {
			int  i = (y * w + x) * 4;
			bool  mode = (x < hw && y < hh) || (x >= hw && y >= hh);
			if (mode) {
				data[i] = r0;
				data[i + 1] = g0;
				data[i + 2] = b0;
				data[i + 3] = a0;
			}
			else {
				data[i] = r1;
				data[i + 1] = g1;
				data[i + 2] = b1;
				data[i + 3] = a1;
			}
		}
	}
	return data; 
}


SuiCore$Image *  SuiDesigner$ImageChessBg$gocChessBgImage(SuiDesigner$ImageChessBg *  self, SuiCore$Canvas *  canvas){
	if (self->img == NULL) {
		int  w = self->width;
		int  h = self->height;
		char *  imgData = self->new_createChessBg_inMemory(self, w, h) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ImageChessBg, img) , SuiCore$Canvas$createImageRGBA(&tmpReturn_1, canvas, w, h, (const unsigned char * )imgData) ) ;
		free(imgData) ;
	}
	return self->img; 
}




//vtable instance
Vtable_SuiDesigner$SceneTransform _vtable_SuiDesigner$SceneTransform;

// init meta

void SuiDesigner$SceneTransform_initMeta(Vtable_SuiDesigner$SceneTransform *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "_translate", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner$SceneTransform, _translate), false, false, 0);
	orc_metaField_primitive(&pNext, "_scale", OrcMetaType_float, offsetof(SuiDesigner$SceneTransform, _scale), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "mat", SuiCore$Mat2d_getOrInitMetaStruct(), offsetof(SuiDesigner$SceneTransform, mat), false, false, 0);

	orc_metaField_method(&pNext, "setScale", offsetof(SuiDesigner$SceneTransform, setScale));
	orc_metaField_method(&pNext, "updateMat", offsetof(SuiDesigner$SceneTransform, updateMat));
	orc_metaField_method(&pNext, "translate", offsetof(SuiDesigner$SceneTransform, translate));
	orc_metaField_method(&pNext, "setTranslate", offsetof(SuiDesigner$SceneTransform, setTranslate));
	orc_metaField_method(&pNext, "identity", offsetof(SuiDesigner$SceneTransform, identity));
	orc_metaField_method(&pNext, "performScaleByWheelEventAndSceneView", offsetof(SuiDesigner$SceneTransform, performScaleByWheelEventAndSceneView));
}


// vtable init


Vtable_SuiDesigner$SceneTransform* Vtable_SuiDesigner$SceneTransform_init(Vtable_SuiDesigner$SceneTransform* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SceneTransform;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SceneTransform_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SceneTransform";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SceneTransform_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$SceneTransform_fini(SuiDesigner$SceneTransform *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$SceneTransform_init_fields(SuiDesigner$SceneTransform *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SceneTransform_fini;
	//fields
    {
	((SuiDesigner$SceneTransform*)self)->_scale = 1;
	((SuiDesigner$SceneTransform*)self)->mat = SuiCore$mkMat2d() ;
    }
	((SuiDesigner$SceneTransform*)self)->setScale = (void*)SuiDesigner$SceneTransform$setScale;
	((SuiDesigner$SceneTransform*)self)->updateMat = (void*)SuiDesigner$SceneTransform$updateMat;
	((SuiDesigner$SceneTransform*)self)->translate = (void*)SuiDesigner$SceneTransform$translate;
	((SuiDesigner$SceneTransform*)self)->setTranslate = (void*)SuiDesigner$SceneTransform$setTranslate;
	((SuiDesigner$SceneTransform*)self)->identity = (void*)SuiDesigner$SceneTransform$identity;
	((SuiDesigner$SceneTransform*)self)->performScaleByWheelEventAndSceneView = (void*)SuiDesigner$SceneTransform$performScaleByWheelEventAndSceneView;
}

// init function

void SuiDesigner$SceneTransform_init(SuiDesigner$SceneTransform *self, void *pOwner){
    Vtable_SuiDesigner$SceneTransform_init(&_vtable_SuiDesigner$SceneTransform);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SceneTransform;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SceneTransform_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SceneTransform * SuiDesigner$SceneTransform_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SceneTransform *self = calloc(1, sizeof(SuiDesigner$SceneTransform));
	
    SuiDesigner$SceneTransform_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SceneTransform$setScale(SuiDesigner$SceneTransform *  self, float  s){
	self->_scale = s;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneTransform$updateMat(SuiDesigner$SceneTransform *  self){
	SuiCore$Mat2d$identity(&self->mat) ;
	SuiCore$Mat2d$translate(&self->mat, self->_translate.x, self->_translate.y, self->_translate.z) ;
	SuiCore$Mat2d$scale(&self->mat, self->_scale, self->_scale, self->_scale) ;
}


void  SuiDesigner$SceneTransform$translate(SuiDesigner$SceneTransform *  self, float  x, float  y, float  z){
	self->_translate = SuiCore$Vec3$add3f(&self->_translate, x, y, z) ;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneTransform$setTranslate(SuiDesigner$SceneTransform *  self, float  x, float  y, float  z){
	SuiCore$Vec3$set(&self->_translate, x, y, z) ;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneTransform$identity(SuiDesigner$SceneTransform *  self){
	SuiCore$Vec3$set(&self->_translate, 0, 0, 0) ;
	self->_scale = 1;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneTransform$performScaleByWheelEventAndSceneView(SuiDesigner$SceneTransform *  self, SuiCore$WheelEvent *  we, SuiDesigner$SceneView *  v){
	SuiCore$Vec2 viewPos = ((SuiCore$ViewBase * )v)->worldToLocal(v, ((SuiCore$MouseEvent * )we)->clientX, ((SuiCore$MouseEvent * )we)->clientY) ;
	SuiCore$Mat2d invMat = SuiCore$Mat2d$inverseNew(&self->mat) ;
	SuiCore$Vec3 scenePos = SuiCore$Mat2d$transformPoint(&invMat, viewPos.x, viewPos.y, 0) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  opt = v->degree->findAndReturnOffset((opt = NULL,&opt), v->degree, self->_scale, we->deltaY > 0 ? 1 : -1) ;
	urgc_set_field_class(v->degree, (void * )offsetof(SuiDesigner$DrawDegree, curOption) , opt) ;
	v->degree->curScale = opt->value;
	self->setScale(self, opt->value) ;
	SuiCore$Vec3 newViewPos = SuiCore$Mat2d$transformPoint(&self->mat, scenePos.x, scenePos.y, 0) ;
	printf("scale. client:%d,%d, viewPos:%f,%f, scenePos:%f,%f,newViewPos:%f,%f, delta:%f,%f\n", ((SuiCore$MouseEvent * )we)->clientX, ((SuiCore$MouseEvent * )we)->clientY, viewPos.x, viewPos.y, scenePos.x, scenePos.y, newViewPos.x, newViewPos.y, viewPos.x - newViewPos.x, viewPos.y - newViewPos.y) ;
	self->translate(self, viewPos.x - newViewPos.x, viewPos.y - newViewPos.y, 0) ;
	printf("wheel. result:%f opt:%f,degree:%f\n", self->_scale, opt->value, opt->degree) ;
}




//vtable instance
Vtable_SuiDesigner$SceneView _vtable_SuiDesigner$SceneView;

// init meta

void SuiDesigner$SceneView_initMeta(Vtable_SuiDesigner$SceneView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "chessBg", ((Vtable_Object*)Vtable_SuiDesigner$ImageChessBg_init(0)), offsetof(SuiDesigner$SceneView, chessBg), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$SceneView, drag), true, false, 1);
	orc_metaField_class(&pNext, "sceneTransform", ((Vtable_Object*)Vtable_SuiDesigner$SceneTransform_init(0)), offsetof(SuiDesigner$SceneView, sceneTransform), true, false, 1);
	orc_metaField_class(&pNext, "degree", ((Vtable_Object*)Vtable_SuiDesigner$DrawDegree_init(0)), offsetof(SuiDesigner$SceneView, degree), true, false, 1);
	orc_metaField_class(&pNext, "rootNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$SceneView, rootNode), true, false, 1);
	orc_metaField_class(&pNext, "gizmoRoot", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$SceneView, gizmoRoot), true, false, 1);
	orc_metaField_class(&pNext, "gizmoDrag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$SceneView, gizmoDrag), true, false, 1);
	orc_metaField_primitive(&pNext, "_reactGizmosDirty", OrcMetaType_bool, offsetof(SuiDesigner$SceneView, _reactGizmosDirty), 0, 0, 0, 0);//bool
	orc_metaField_struct(&pNext, "_sceneWorldMat", SuiCore$Mat2d_getOrInitMetaStruct(), offsetof(SuiDesigner$SceneView, _sceneWorldMat), false, false, 0);

	orc_metaField_method(&pNext, "onUnmouting", offsetof(SuiDesigner$SceneView, onUnmouting));
	orc_metaField_method(&pNext, "onLeftClickInCapture", offsetof(SuiDesigner$SceneView, onLeftClickInCapture));
	orc_metaField_method(&pNext, "_routeRightMenu", offsetof(SuiDesigner$SceneView, _routeRightMenu));
	orc_metaField_method(&pNext, "onRightClick", offsetof(SuiDesigner$SceneView, onRightClick));
	orc_metaField_method(&pNext, "removeRootNode", offsetof(SuiDesigner$SceneView, removeRootNode));
	orc_metaField_method(&pNext, "triggerReactGizmos", offsetof(SuiDesigner$SceneView, triggerReactGizmos));
	orc_metaField_method(&pNext, "reactGizmos", offsetof(SuiDesigner$SceneView, reactGizmos));
	orc_metaField_method(&pNext, "drawRect_forANode", offsetof(SuiDesigner$SceneView, drawRect_forANode));
}


// vtable init


Vtable_SuiDesigner$SceneView* Vtable_SuiDesigner$SceneView_init(Vtable_SuiDesigner$SceneView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SceneView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SceneView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SceneView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SceneView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SceneView_fini(SuiDesigner$SceneView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->chessBg);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->sceneTransform);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->degree);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->rootNode);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->gizmoRoot);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->gizmoDrag);

}

// init fields function


void SuiDesigner$SceneView_init_fields(SuiDesigner$SceneView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SceneView_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ImageChessBg*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->chessBg, SuiDesigner$ImageChessBg_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SceneTransform*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->sceneTransform, SuiDesigner$SceneTransform_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegree*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->degree, SuiDesigner$DrawDegree_new(&tmpNewOwner_4) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->rootNode, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->gizmoRoot, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneView*)self)->gizmoDrag, SuiView$Drag_new(&tmpNewOwner_5) );
	((SuiDesigner$SceneView*)self)->_reactGizmosDirty = false;
	((SuiDesigner$SceneView*)self)->_sceneWorldMat = SuiCore$mkMat2d() ;
    }
	((Object*)self)->ctor = (void*)SuiDesigner$SceneView$ctor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)SuiDesigner$SceneView$onListenerEvent;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$SceneView$onMounted;
	((SuiDesigner$SceneView*)self)->onUnmouting = (void*)SuiDesigner$SceneView$onUnmouting;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiDesigner$SceneView$onEvent;
	((SuiDesigner$SceneView*)self)->onLeftClickInCapture = (void*)SuiDesigner$SceneView$onLeftClickInCapture;
	((SuiDesigner$SceneView*)self)->_routeRightMenu = (void*)SuiDesigner$SceneView$_routeRightMenu;
	((SuiDesigner$SceneView*)self)->onRightClick = (void*)SuiDesigner$SceneView$onRightClick;
	((SuiDesigner$SceneView*)self)->removeRootNode = (void*)SuiDesigner$SceneView$removeRootNode;
	((SuiCore$Node*)self)->react = (void*)SuiDesigner$SceneView$react;
	((SuiDesigner$SceneView*)self)->triggerReactGizmos = (void*)SuiDesigner$SceneView$triggerReactGizmos;
	((SuiDesigner$SceneView*)self)->reactGizmos = (void*)SuiDesigner$SceneView$reactGizmos;
	((SuiCore$ViewBase*)self)->draw_children = (void*)SuiDesigner$SceneView$draw_children;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiDesigner$SceneView$draw_self;
	((SuiCore$View*)self)->drawSelfBorder = (void*)SuiDesigner$SceneView$drawSelfBorder;
	((SuiDesigner$SceneView*)self)->drawRect_forANode = (void*)SuiDesigner$SceneView$drawRect_forANode;
}

// init function

void SuiDesigner$SceneView_init(SuiDesigner$SceneView *self, void *pOwner){
    Vtable_SuiDesigner$SceneView_init(&_vtable_SuiDesigner$SceneView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SceneView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SceneView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SceneView * SuiDesigner$SceneView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SceneView *self = calloc(1, sizeof(SuiDesigner$SceneView));
	
    SuiDesigner$SceneView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SceneView$ctor(SuiDesigner$SceneView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_223_15*  __var___Block_223_15 = (__var___Block_223_15=NULL,urgc_init_var((void**)&__var___Block_223_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_223_15) , __finiBlock___Block_223_15) ));
	urgc_set_field_class(__var___Block_223_15, (void * )offsetof(SuiDesigner$__Block_223_15, self) , self) ;
	((SuiCore$View * )self)->needClip = true;
	self->sceneTransform->translate(self->sceneTransform, 0, 0, 0) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_226_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_226_27(&tmpReturn_1, __var___Block_223_15) ) ;
}


void  SuiDesigner$SceneView$onListenerEvent(SuiDesigner$SceneView *  self, SuiCore$Event *  event){
	if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeAttrChanged_init(NULL))) {
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventANodeChanged_init(NULL))) {
		SuiDesigner$EventANodeChanged *  e = (SuiDesigner$EventANodeChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
	else if (Orc_instanceof((Object*)event, (Vtable_Object*)Vtable_SuiDesigner$EventFileItemChanged_init(NULL))) {
		SuiDesigner$EventFileItemChanged *  e = (SuiDesigner$EventFileItemChanged * )e;
		((SuiCore$Node * )self)->trigger_react(self) ;
	}
}


void  SuiDesigner$SceneView$onMounted(SuiDesigner$SceneView *  self){
	SuiCore$Node$onMounted(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
	urgc_set_field_class(SuiDesigner$EditCtx_ins(&tmpReturn_1) , (void * )offsetof(SuiDesigner$EditCtx, sceneView) , self) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->addListener(tmpThis_1, self) ;
}


void  SuiDesigner$SceneView$onUnmouting(SuiDesigner$SceneView *  self){
	SuiCore$Node$onUnmounting(self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
	urgc_set_field_class(SuiDesigner$EditCtx_ins(&tmpReturn_1) , (void * )offsetof(SuiDesigner$EditCtx, sceneView) , NULL) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  SuiDesigner$SceneView$onEvent(SuiDesigner$SceneView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$WheelEvent_init(NULL))) {
		SuiCore$WheelEvent *  we = (SuiCore$WheelEvent * )e;
		if (((SuiCore$ViewEvent * )we)->isCapture) {
			self->sceneTransform->performScaleByWheelEventAndSceneView(self->sceneTransform, we, self) ;
		}
		return ; 
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (((SuiCore$ViewEvent * )me)->isBubble(me)  && me->button == 3) {
			if (me->isMouseDown) {
				printf("mouse down scene\n") ;
			}
			if (me->isMouseUp) {
				printf("mouse up scene\n") ;
			}
		}
		if (me->isClickInBubble(me)  && me->button == 3) {
			self->onRightClick(self, me) ;
		}
		if (me->button == 1 && ((SuiCore$ViewEvent * )me)->isCapture && me->isClick(me) ) {
			self->onLeftClickInCapture(self, me) ;
		}
	}
}


void  SuiDesigner$SceneView$onLeftClickInCapture(SuiDesigner$SceneView *  self, SuiCore$MouseEvent *  me){
	if (self->rootNode && Orc_instanceof((Object*)self->rootNode, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  rootView = (SuiCore$ViewBase * )self->rootNode;
		SuiCore$ViewBase *  found = rootView->hitTestChildren(rootView, me->clientX, me->clientY) ;
		if (found) {
			SuiDesigner$EditCtx *  tmpThis_1 = NULL;
			URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
			URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  vnode = (tmpThis_1 = SuiDesigner$EditCtx_ins(&tmpReturn_1) )->findANodeByNode((vnode = NULL,&vnode), tmpThis_1, found) ;
			printf("findANode:%p, %p\n", vnode, found) ;
			if (vnode) {
				((SuiCore$Event * )me)->stopPropagation(me) ;
				SuiView$TreeState *  tmpThis_2 = NULL;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_2 = NULL;
				(tmpThis_2 = SuiDesigner$EditCtx_ins(&tmpReturn_2) ->state)->setSelected(tmpThis_2, vnode) ;
			}
		}
		else {
			SuiCore$Vec2 viewPos = ((SuiCore$ViewBase * )self)->worldToLocal(self, me->clientX, me->clientY) ;
			SuiCore$Mat2d invMat = SuiCore$Mat2d$inverseNew(&self->sceneTransform->mat) ;
			SuiCore$Vec3 scenePos = SuiCore$Mat2d$transformPoint(&invMat, viewPos.x, viewPos.y, 0) ;
			printf("\n\n========================================left click. viewPos:%f,%f, scenePos:%f,%f\n\n", viewPos.x, viewPos.y, scenePos.x, scenePos.y) ;
		}
	}
}


void  SuiDesigner$SceneView$_routeRightMenu(SuiDesigner$SceneView *  self, SuiView$MenuNativeItem *  item){
	if (item->cmd) {
		if (Orc$String$equals(item->cmd, "ResetSceneTransform") ) {
			self->sceneTransform->identity(self->sceneTransform) ;
			return ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = (s=NULL,urgc_init_var_class((void**)&s, Orc$String$addString(Orc$str(&tmpReturn_1, "选中菜单") , item->cmd) ));
	SuiDialog$MessageDialog_alert(s->str, "tip") ;
}


void  SuiDesigner$SceneView$onRightClick(SuiDesigner$SceneView *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP SuiDesigner$__Block_334_37*  __var___Block_334_37 = (__var___Block_334_37=NULL,urgc_init_var((void**)&__var___Block_334_37, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_334_37) , __finiBlock___Block_334_37) ));
	urgc_set_field_class(__var___Block_334_37, (void * )offsetof(SuiDesigner$__Block_334_37, self) , self) ;
	printf("on right click scene\n") ;
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_1 = NULL;
	{
		SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_1, NULL, NULL, NULL) ;
		
	
		URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_337*  tmpReturn_2 = NULL;
		(urgc_set_var(&onActive, __make___Closure_onActive_337(&tmpReturn_2, __var___Block_334_37) ) );
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		{
			SuiView$MenuNativeItem*  __scopeVar_346_12 = SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "重置场景坐标") , onActive) , *o = __scopeVar_346_12;
			
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_5, "ResetSceneTransform") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
		{
			SuiView$MenuNativeItem*  __scopeVar_347_12 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "hi") , onActive) , *o = __scopeVar_347_12;
			
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$MenuNativeItem, cmd) , Orc$str(&tmpReturn_8, "Hi") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
		n->create(n, o) ;
		n->showAtMouse(n) ;
	}
}


void  SuiDesigner$SceneView$removeRootNode(SuiDesigner$SceneView *  self){
	if (self->rootNode) {
		self->rootNode->removeSelf(self->rootNode) ;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SceneView, rootNode) , NULL) ;
	}
}


void  SuiDesigner$SceneView$react(SuiDesigner$SceneView *  self){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  root = (root=NULL,urgc_init_var_class((void**)&root, SuiDesigner$EditCtx_ins(&tmpReturn_1) ->root));
	if (!root) {
		self->removeRootNode(self) ;
	}
	else {
		if (root->node && (root->node->parent != self || root->node != self->rootNode)) {
			self->removeRootNode(self) ;
			((SuiCore$Node * )self)->insertChild(self, root->node, 0) ;
			urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SceneView, rootNode) , root->node) ;
		}
		root->updateSubTreeNodes(root) ;
	}
	if (!self->gizmoRoot) {
		URGC_VAR_CLEANUP_CLASS SuiCore$View*  o = (o=NULL,urgc_init_var_class((void**)&o, SuiCore$View_new(&o) ));
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SceneView, gizmoRoot) , o) ;
		((SuiCore$Node * )self)->appendChild(self, o) ;
		Orc$String$set(((SuiCore$ViewBase * )o)->hitTestType, "onlychildren") ;
		o->backgroundColor = 0x0000ff00;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_399_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_399_26(&tmpReturn_2) ) ;
	}
	self->reactGizmos(self) ;
	((SuiCore$View * )self)->backgroundColor = 0xcc000000;
}


void  SuiDesigner$SceneView$triggerReactGizmos(SuiDesigner$SceneView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_421_29*  __var___Block_421_29 = (__var___Block_421_29=NULL,urgc_init_var((void**)&__var___Block_421_29, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_421_29) , __finiBlock___Block_421_29) ));
	urgc_set_field_class(__var___Block_421_29, (void * )offsetof(SuiDesigner$__Block_421_29, self) , self) ;
	if (self->_reactGizmosDirty) {
		return ; 
	}
	self->_reactGizmosDirty = true;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_429_30*  tmpReturn_1 = NULL;
	SuiCore$requestAnimationFrame(__make___Closure_429_30(&tmpReturn_1, __var___Block_421_29) ) ;
}


void  SuiDesigner$SceneView$reactGizmos(SuiDesigner$SceneView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_438_32*  tmpReturn_1 = NULL;
	urgc_set_field(self->gizmoDrag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_438_32(&tmpReturn_1) ) ;
	{
		SuiCore$Node*  o = self->gizmoRoot;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_444_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
		if (ctx->state) {
			URGC_VAR_CLEANUP SuiDesigner$__Block_447_26*  __var___Block_447_26 = (__var___Block_447_26=NULL,urgc_init_var((void**)&__var___Block_447_26, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_447_26) , __finiBlock___Block_447_26) ));
			__var___Block_447_26->sel = (SuiDesigner$ANode * )ctx->state->getFirstSelected(ctx->state) ;
			if (__var___Block_447_26->sel && __var___Block_447_26->sel->node && Orc_instanceof((Object*)__var___Block_447_26->sel->node, (Vtable_Object*)Vtable_SuiCore$View_init(NULL))) {
				URGC_VAR_CLEANUP SuiDesigner$__Block_449_62*  __var___Block_449_62 = (__var___Block_449_62=NULL,urgc_init_var((void**)&__var___Block_449_62, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_449_62) , __finiBlock___Block_449_62) ));
				__var___Block_449_62->selView = (SuiCore$View * )__var___Block_447_26->sel->node;
				SuiCore$Frame *  f = &((SuiCore$ViewBase * )__var___Block_449_62->selView)->frame;
				SuiCore$Mat2d invMat = SuiCore$Mat2d$inverseNew(&self->_sceneWorldMat) ;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$GizmoRectView*  tmpReturn_2 = NULL;
				{
					SuiDesigner$GizmoRectView*  __scopeVar_456_20 = SuiDesigner$mkGizmoRectView(&tmpReturn_2, o, 0) , *o = __scopeVar_456_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_456_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Vec3 lt = SuiCore$Mat2d$localToLocal(&((SuiCore$ViewBase * )__var___Block_449_62->selView)->_world_transform, &invMat, 0, 0, 0) ;
					SuiCore$Vec3 rb = SuiCore$Mat2d$localToLocal(&((SuiCore$ViewBase * )__var___Block_449_62->selView)->_world_transform, &invMat, f->width, f->height, 0) ;
					SuiCore$Rect$set_ltrb(&o->targetRect, lt.x, lt.y, rb.x, rb.y) ;
					URGC_VAR_CLEANUP SuiDesigner$__Closure_460_42*  tmpReturn_3 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiDesigner$GizmoRectView, onRectChanged) , __make___Closure_460_42(&tmpReturn_3, __var___Block_447_26, __var___Block_449_62) ) ;
				}
			}
		}
	}
}


void  SuiDesigner$SceneView$draw_children(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas){
	SuiCore$Canvas$save(canvas) ;
	SuiCore$Canvas$transform(canvas, self->sceneTransform->mat) ;
	SuiCore$Canvas$currentTransform(canvas, &self->_sceneWorldMat) ;
	SuiCore$ViewBase$draw_children(self, canvas) ;
	SuiCore$Canvas$restore(canvas) ;
}


void  SuiDesigner$SceneView$draw_self(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas){
	self->triggerReactGizmos(self) ;
	SuiCore$Image *  bg = self->chessBg->gocChessBgImage(self->chessBg, canvas) ;
	SuiCore$Rect r = ((SuiCore$View * )self)->getViewRect(self) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, 0, r.w, r.h) ;
	SuiCore$Canvas$imagePattern(canvas, true, 0, 0, self->chessBg->width, self->chessBg->height, 0, bg, 1) ;
	SuiCore$Canvas$fill(canvas) ;
	self->degree->draw(self->degree, canvas, self->sceneTransform->mat, r.w, r.h, 0, 0) ;
}


void  SuiDesigner$SceneView$drawSelfBorder(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$drawSelfBorder(self, canvas) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
	self->drawRect_forANode(self, canvas, ctx->hoverNode) ;
	if (ctx->state) {
		SuiDesigner$ANode *  sel = (SuiDesigner$ANode * )ctx->state->getFirstSelected(ctx->state) ;
	}
}


void  SuiDesigner$SceneView$drawRect_forANode(SuiDesigner$SceneView *  self, SuiCore$Canvas *  canvas, SuiDesigner$ANode *  sel){
	if (!sel) {
		return ; 
	}
	SuiCore$Node *  n = sel->node;
	if (n && Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )n;
		SuiCore$Rect myrect = ((SuiCore$ViewBase * )self)->get_abs_rect(self) ;
		SuiCore$Rect rect = vb->get_abs_rect(vb) ;
		int  x = rect.x - myrect.x;
		int  y = rect.y - myrect.y;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$rect(canvas, x, y, rect.w, rect.h) ;
		SuiCore$Canvas$fillColorByInt32(canvas, SuiCore$mkIntByRgba(0, 255, 0, 64) ) ;
		SuiCore$Canvas$fill(canvas) ;
		SuiCore$Canvas$strokeWidth(canvas, 1) ;
		SuiCore$Canvas$strokeColorByInt32(canvas, SuiCore$mkIntByRgba(0, 255, 0, 192) ) ;
		SuiCore$Canvas$stroke(canvas) ;
	}
}



static void  __finiBlock___Block_223_15(SuiDesigner$__Block_223_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_223_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_334_37(SuiDesigner$__Block_334_37 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_334_37, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_421_29(SuiDesigner$__Block_421_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_421_29, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_447_26(SuiDesigner$__Block_447_26 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_449_62(SuiDesigner$__Block_449_62 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_226_27(SuiDesigner$__Closure_226_27 *  self, SuiView$Drag *  d){
	printf("on drag. dx:%f,%f\n", d->deltaPos.x, d->deltaPos.y) ;
	self->__var___Block_223_15->self->sceneTransform->translate(self->__var___Block_223_15->self->sceneTransform, d->deltaPos.x, d->deltaPos.y, 0) ;
}

static void  __fini___Closure_226_27(SuiDesigner$__Closure_226_27 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_226_27, __var___Block_223_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_226_27*  __make___Closure_226_27(SuiDesigner$__Closure_226_27 **  __outRef__, SuiDesigner$__Block_223_15 *  __var___Block_223_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_226_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_226_27) , __fini___Closure_226_27) ));
	self->invoke = __fn___Closure_226_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_226_27, __var___Block_223_15) , __var___Block_223_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_337(SuiDesigner$__Closure_onActive_337 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu on AssetDirView cmd:%s item:%s\n", item->cmd->str, item->label->str) ;
	self->__var___Block_334_37->self->_routeRightMenu(self->__var___Block_334_37->self, item) ;
}

static void  __fini___Closure_onActive_337(SuiDesigner$__Closure_onActive_337 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_337, __var___Block_334_37) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_337*  __make___Closure_onActive_337(SuiDesigner$__Closure_onActive_337 **  __outRef__, SuiDesigner$__Block_334_37 *  __var___Block_334_37){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_337*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_337) , __fini___Closure_onActive_337) ));
	self->invoke = __fn___Closure_onActive_337;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_337, __var___Block_334_37) , __var___Block_334_37) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_399_26(SuiDesigner$__Closure_399_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->isClickInBubble(me) ) {
			
		}
	}
}

static void  __fini___Closure_399_26(SuiDesigner$__Closure_399_26 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_399_26*  __make___Closure_399_26(SuiDesigner$__Closure_399_26 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_399_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_399_26) , __fini___Closure_399_26) ));
	self->invoke = __fn___Closure_399_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_429_30(SuiDesigner$__Closure_429_30 *  self){
	self->__var___Block_421_29->self->_reactGizmosDirty = false;
	self->__var___Block_421_29->self->reactGizmos(self->__var___Block_421_29->self) ;
	return true; 
}

static void  __fini___Closure_429_30(SuiDesigner$__Closure_429_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_429_30, __var___Block_421_29) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_429_30*  __make___Closure_429_30(SuiDesigner$__Closure_429_30 **  __outRef__, SuiDesigner$__Block_421_29 *  __var___Block_421_29){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_429_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_429_30) , __fini___Closure_429_30) ));
	self->invoke = __fn___Closure_429_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_429_30, __var___Block_421_29) , __var___Block_421_29) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_438_32(SuiDesigner$__Closure_438_32 *  self, SuiView$Drag *  d){
	
}

static void  __fini___Closure_438_32(SuiDesigner$__Closure_438_32 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_438_32*  __make___Closure_438_32(SuiDesigner$__Closure_438_32 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_438_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_438_32) , __fini___Closure_438_32) ));
	self->invoke = __fn___Closure_438_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_460_42(SuiDesigner$__Closure_460_42 *  self, SuiCore$Rect newr){
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	self->__var___Block_447_26->sel->setAttr(self->__var___Block_447_26->sel, "width", Json$Json_mkNumber(&tmpReturn_1, newr.w) ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
	self->__var___Block_447_26->sel->setAttr(self->__var___Block_447_26->sel, "height", Json$Json_mkNumber(&tmpReturn_2, newr.h) ) ;
	self->__var___Block_449_62->selView->width = newr.w;
	self->__var___Block_449_62->selView->height = newr.h;
	((SuiCore$ViewBase * )self->__var___Block_449_62->selView)->frame.x = newr.x;
	((SuiCore$ViewBase * )self->__var___Block_449_62->selView)->frame.y = newr.y;
	((SuiCore$ViewBase * )self->__var___Block_449_62->selView)->invalidLayout(self->__var___Block_449_62->selView) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeAttrChanged*  tmpNewOwner_3 = NULL;
	{
		SuiDesigner$EventANodeAttrChanged*  o = SuiDesigner$EventANodeAttrChanged_new(&tmpNewOwner_3) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeAttrChanged, anode) , self->__var___Block_447_26->sel) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

static void  __fini___Closure_460_42(SuiDesigner$__Closure_460_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_460_42, __var___Block_447_26) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_460_42, __var___Block_449_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_460_42*  __make___Closure_460_42(SuiDesigner$__Closure_460_42 **  __outRef__, SuiDesigner$__Block_447_26 *  __var___Block_447_26, SuiDesigner$__Block_449_62 *  __var___Block_449_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_460_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_460_42) , __fini___Closure_460_42) ));
	self->invoke = __fn___Closure_460_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_460_42, __var___Block_447_26) , __var___Block_447_26) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_460_42, __var___Block_449_62) , __var___Block_449_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiDesigner$SceneView*  SuiDesigner$mkSceneView(SuiDesigner$SceneView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$SceneView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$SceneView_init(NULL)) ) ; 
}



