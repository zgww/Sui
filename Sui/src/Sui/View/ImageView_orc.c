
#include "ImageView_orc.h" 

#include <stdio.h>
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Bezier_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Global_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/Node_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Map_orc.h"
#include "./ViewBuilder_orc.h"
#include "../Core/Image_orc.h"
#include "../../SuiDesigner/Inspector_orc.h"
#include "../../SuiDesigner/Insp_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiView$ImageModeCalc _vtable_SuiView$ImageModeCalc;

// init meta

void SuiView$ImageModeCalc_initMeta(Vtable_SuiView$ImageModeCalc *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "sw", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, sw), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "sh", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, sh), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dw", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, dw), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dh", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, dh), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "sx", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, sx), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "sy", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, sy), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dx", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, dx), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dy", OrcMetaType_int, offsetof(SuiView$ImageModeCalc, dy), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "sr", OrcMetaType_float, offsetof(SuiView$ImageModeCalc, sr), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "dr", OrcMetaType_float, offsetof(SuiView$ImageModeCalc, dr), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "scale", OrcMetaType_float, offsetof(SuiView$ImageModeCalc, scale), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "getSrcRect", offsetof(SuiView$ImageModeCalc, getSrcRect));
	orc_metaField_method(&pNext, "getDstRect", offsetof(SuiView$ImageModeCalc, getDstRect));
	orc_metaField_method(&pNext, "calc", offsetof(SuiView$ImageModeCalc, calc));
	orc_metaField_method(&pNext, "calc_contain", offsetof(SuiView$ImageModeCalc, calc_contain));
	orc_metaField_method(&pNext, "calc_cover", offsetof(SuiView$ImageModeCalc, calc_cover));
}


// vtable init


Vtable_SuiView$ImageModeCalc* Vtable_SuiView$ImageModeCalc_init(Vtable_SuiView$ImageModeCalc* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ImageModeCalc;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ImageModeCalc_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ImageModeCalc";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ImageModeCalc_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiView$ImageModeCalc_fini(SuiView$ImageModeCalc *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiView$ImageModeCalc_init_fields(SuiView$ImageModeCalc *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiView$ImageModeCalc_fini;
	//fields
    {
	((SuiView$ImageModeCalc*)self)->sw = 0;
	((SuiView$ImageModeCalc*)self)->sh = 0;
	((SuiView$ImageModeCalc*)self)->dw = 0;
	((SuiView$ImageModeCalc*)self)->dh = 0;
	((SuiView$ImageModeCalc*)self)->sx = 0;
	((SuiView$ImageModeCalc*)self)->sy = 0;
	((SuiView$ImageModeCalc*)self)->dx = 0;
	((SuiView$ImageModeCalc*)self)->dy = 0;
	((SuiView$ImageModeCalc*)self)->sr = 0.f;
	((SuiView$ImageModeCalc*)self)->dr = 0.f;
	((SuiView$ImageModeCalc*)self)->scale = 1.f;
    }
	((SuiView$ImageModeCalc*)self)->getSrcRect = (void*)SuiView$ImageModeCalc$getSrcRect;
	((SuiView$ImageModeCalc*)self)->getDstRect = (void*)SuiView$ImageModeCalc$getDstRect;
	((SuiView$ImageModeCalc*)self)->calc = (void*)SuiView$ImageModeCalc$calc;
	((SuiView$ImageModeCalc*)self)->calc_contain = (void*)SuiView$ImageModeCalc$calc_contain;
	((SuiView$ImageModeCalc*)self)->calc_cover = (void*)SuiView$ImageModeCalc$calc_cover;
}

// init function

void SuiView$ImageModeCalc_init(SuiView$ImageModeCalc *self, void *pOwner){
    Vtable_SuiView$ImageModeCalc_init(&_vtable_SuiView$ImageModeCalc);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ImageModeCalc;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ImageModeCalc_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ImageModeCalc * SuiView$ImageModeCalc_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ImageModeCalc *self = calloc(1, sizeof(SuiView$ImageModeCalc));
	
    SuiView$ImageModeCalc_init(self, pOwner);
    return self;
}


// class members
SuiCore$Rect SuiView$ImageModeCalc$getSrcRect(SuiView$ImageModeCalc *  self){
	return SuiCore$mkRect(self->sx, self->sy, self->sw, self->sh) ; 
}


SuiCore$Rect SuiView$ImageModeCalc$getDstRect(SuiView$ImageModeCalc *  self){
	return SuiCore$mkRect(self->dx, self->dy, self->dw, self->dh) ; 
}


void  SuiView$ImageModeCalc$calc(SuiView$ImageModeCalc *  self, int  sw, int  sh, int  dw, int  dh, SuiView$ImageMode mode){
	self->sw = sw;
	self->sh = sh;
	self->dw = dw;
	self->dh = dh;
	if (sw == 0 || sh == 0 || dw == 0 || dh == 0) {
		return ; 
	}
	self->sr = sw / (float )sh;
	self->dr = dw / (float )dh;
	if (mode == SuiView$Cover) {
		self->calc_cover(self) ;
	}
	else if (mode == SuiView$Contain) {
		self->calc_contain(self) ;
	}
}


void  SuiView$ImageModeCalc$calc_contain(SuiView$ImageModeCalc *  self){
	float  w_scale = self->dw / (float )self->sw;
	float  h_scale = self->dh / (float )self->sh;
	float  scale = Orc$minFloat(w_scale, h_scale) ;
	float  tw = scale * self->sw;
	float  th = scale * self->sh;
	self->dx = (self->dw - tw) / 2.f;
	self->dy = (self->dh - th) / 2.f;
	self->dw = tw;
	self->dh = th;
	self->scale = scale;
}


void  SuiView$ImageModeCalc$calc_cover(SuiView$ImageModeCalc *  self){
	float  w_scale = self->sw / (float )self->dw;
	float  h_scale = self->sh / (float )self->dh;
	float  scale = Orc$minFloat(w_scale, h_scale) ;
	float  tw = scale * self->dw;
	float  th = scale * self->dh;
	self->sx = (self->sw - tw) / 2.f;
	self->sy = (self->sh - th) / 2.f;
	self->sw = tw;
	self->sh = th;
	self->scale = scale;
}




//vtable instance
Vtable_SuiView$ImageView _vtable_SuiView$ImageView;

// init meta

void SuiView$ImageView_initMeta(Vtable_SuiView$ImageView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "bezier", SuiCore$Bezier_getOrInitMetaStruct(), offsetof(SuiView$ImageView, bezier), false, false, 0);
	orc_metaField_struct(&pNext, "pos", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiView$ImageView, pos), false, false, 0);
	orc_metaField_primitive(&pNext, "ratio", OrcMetaType_float, offsetof(SuiView$ImageView, ratio), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "src", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$ImageView, src), true, false, 1);
	orc_metaField_class(&pNext, "calc", ((Vtable_Object*)Vtable_SuiView$ImageModeCalc_init(0)), offsetof(SuiView$ImageView, calc), true, false, 1);
	orc_metaField_class(&pNext, "_img", ((Vtable_Object*)Vtable_SuiCore$Image_init(0)), offsetof(SuiView$ImageView, _img), true, false, 1);

	orc_metaField_method(&pNext, "setRatio", offsetof(SuiView$ImageView, setRatio));
	orc_metaField_method(&pNext, "insp", offsetof(SuiView$ImageView, insp));
	orc_metaField_method(&pNext, "onInspect", offsetof(SuiView$ImageView, onInspect));
	orc_metaField_method(&pNext, "setSrc", offsetof(SuiView$ImageView, setSrc));
	orc_metaField_method(&pNext, "setImageMode", offsetof(SuiView$ImageView, setImageMode));
	orc_metaField_method(&pNext, "_isImageValid", offsetof(SuiView$ImageView, _isImageValid));
}


// vtable init


Vtable_SuiView$ImageView* Vtable_SuiView$ImageView_init(Vtable_SuiView$ImageView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ImageView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ImageView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ImageView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ImageView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ImageView_fini(SuiView$ImageView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiView$ImageView_init_fields(SuiView$ImageView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$ImageView_fini;
	//fields
    {
	((SuiView$ImageView*)self)->bezier = SuiCore$mkBezier() ;
	((SuiView$ImageView*)self)->ratio = 10.0;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ImageView*)self)->src, Orc$str(&tmpReturn_1, "") );
	((SuiView$ImageView*)self)->imageMode = SuiView$WrapContent;
	URGC_VAR_CLEANUP_CLASS SuiView$ImageModeCalc*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ImageView*)self)->calc, SuiView$ImageModeCalc_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((SuiView$ImageView*)self)->_img, NULL);
    }
	((SuiView$ImageView*)self)->setRatio = (void*)SuiView$ImageView$setRatio;
	((SuiView$ImageView*)self)->insp = (void*)SuiView$ImageView$insp;
	((SuiView$ImageView*)self)->onInspect = (void*)SuiView$ImageView$onInspect;
	((SuiCore$ViewBase*)self)->layout = (void*)SuiView$ImageView$layout;
	((SuiView$ImageView*)self)->setSrc = (void*)SuiView$ImageView$setSrc;
	((SuiView$ImageView*)self)->setImageMode = (void*)SuiView$ImageView$setImageMode;
	((SuiView$ImageView*)self)->_isImageValid = (void*)SuiView$ImageView$_isImageValid;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$ImageView$draw_self;
}

// init function

void SuiView$ImageView_init(SuiView$ImageView *self, void *pOwner){
    Vtable_SuiView$ImageView_init(&_vtable_SuiView$ImageView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ImageView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ImageView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ImageView * SuiView$ImageView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ImageView *self = calloc(1, sizeof(SuiView$ImageView));
	
    SuiView$ImageView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$ImageView$setRatio(SuiView$ImageView *  self, float  v){
	self->ratio = v;
	printf("set ratio:%f\n", self->ratio) ;
}


void  SuiView$ImageView$insp(SuiView$ImageView *  self, SuiDesigner$Insp *  insp){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttrImageSrc*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$InspAttrImageSrc*  o = SuiDesigner$InspAttrImageSrc_new(&tmpNewOwner_1) ;
		
	
		((SuiDesigner$InspAttr * )o)->bind(o, insp, "src", "图片") ;
	}
}


void  SuiView$ImageView$onInspect(SuiView$ImageView *  self, SuiDesigner$Inspector *  insp){
	insp->markAttrAsImageSrc(insp, "src") ;
	insp->markAttrAsSlider(insp, "ratio", 10, 20) ;
}


void  SuiView$ImageView$layout(SuiView$ImageView *  self, SuiCore$Frame *  ctx){
	SuiCore$Frame$incTimesInOneLayout(ctx) ;
	((SuiCore$View * )self)->updateFrame_forSelfWidthHeight(self, ctx) ;
	((SuiCore$View * )self)->initLayoutSize(self, ctx) ;
	if (((SuiCore$View * )self)->cb && ((SuiCore$View * )self)->cb->cbLayout(((SuiCore$View * )self)->cb, self, ctx) ) {
		return ; 
	}
	if (self->_isImageValid(self) ) {
		if (self->imageMode == SuiView$WrapContent) {
			SuiCore$Frame$setSize(ctx, self->_img->width(self->_img)  + SuiCore$Inset$hor(&((SuiCore$View * )self)->margin) , self->_img->height(self->_img)  + SuiCore$Inset$ver(&((SuiCore$View * )self)->margin) ) ;
		}
		else if (self->imageMode == SuiView$WidthFix) {
			SuiCore$Frame$setHeight(ctx, self->_img->height(self->_img)  / self->_img->width(self->_img)  * ctx->width) ;
		}
		else if (self->imageMode == SuiView$HeightFix) {
			SuiCore$Frame$setWidth(ctx, self->_img->width(self->_img)  / self->_img->height(self->_img)  * ctx->height) ;
		}
	}
	SuiCore$Frame tmp = *ctx;
	((SuiCore$View * )self)->layoutContent_fromOutBox(self, &tmp) ;
	SuiCore$Frame$setSize(ctx, ctx->width + SuiCore$Inset$hor(&((SuiCore$View * )self)->margin) , ctx->height + SuiCore$Inset$ver(&((SuiCore$View * )self)->margin) ) ;
}


void  SuiView$ImageView$setSrc(SuiView$ImageView *  self, Orc$String*  src){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(src);

	if (self->src && src && Orc$String$equals(self->src, src->str) ) {
		return ; 
	}
	urgc_set_field_class(self, (void * )offsetof(SuiView$ImageView, src) , src) ;
	if (src) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ImageView, _img) , SuiCore$loadImage(&tmpReturn_1, src->str) ) ;
	}
	else {
		urgc_set_field_class(self, (void * )offsetof(SuiView$ImageView, _img) , NULL) ;
	}
}


void  SuiView$ImageView$setImageMode(SuiView$ImageView *  self, SuiView$ImageMode mode){
	if (self->imageMode != mode) {
		self->imageMode = mode;
		((SuiCore$ViewBase * )self)->invalidLayout(self) ;
	}
}


bool  SuiView$ImageView$_isImageValid(SuiView$ImageView *  self){
	return self->_img != NULL; 
}


void  SuiView$ImageView$draw_self(SuiView$ImageView *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
	if (self->_isImageValid(self) ) {
		SuiCore$Rect r = ((SuiCore$View * )self)->getViewRect(self) ;
		float  w = r.w;
		float  h = r.h;
		self->calc->calc(self->calc, self->_img->width(self->_img) , self->_img->height(self->_img) , w, h, self->imageMode) ;
		SuiView$drawImage_atRect(canvas, self->_img, self->calc->sx, self->calc->sy, self->calc->sw, self->calc->sh, self->calc->dx, self->calc->dy, self->calc->dw, self->calc->dh) ;
		SuiCore$Canvas$fill(canvas) ;
	}
}



void  SuiView$drawImage_atRect(SuiCore$Canvas *  canvas, SuiCore$Image *  imgId, float  sx, float  sy, float  sw, float  sh, float  dx, float  dy, float  dw, float  dh){
	int  imgW = imgId->width(imgId) ;
	int  imgH = imgId->height(imgId) ;
	float  wscale = dw / sw;
	float  hscale = dh / sh;
	float  imgScaleW = imgW * wscale;
	float  imgScaleH = imgH * hscale;
	float  ox = -sx * wscale + dx;
	float  oy = -sy * hscale + dy;
	SuiCore$Canvas$imagePattern(canvas, true, ox, oy, imgScaleW, imgScaleH, 0.f, imgId, 1.f) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, dx, dy, dw, dh) ;
}

SuiView$ImageView*  SuiView$mkImageView(SuiView$ImageView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$ImageView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiView$ImageView_init(NULL)) ) ; 
}



