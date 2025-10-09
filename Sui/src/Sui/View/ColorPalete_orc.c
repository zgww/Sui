
#include "ColorPalete_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "../Core/ViewBase_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/Vec2_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Image_orc.h"
#include "../Core/Color_orc.h"
#include "../Core/Canvas_orc.h"
#include "../Core/Event_orc.h"
#include "../Core/MouseEvent_orc.h"
#include "../View/TextView_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "./Drag_orc.h"
#include "./ViewBuilder_orc.h"


// static struct 
typedef struct tagSuiView$__Block_89_34 SuiView$__Block_89_34;

typedef struct tagSuiView$__Block_315_13 SuiView$__Block_315_13;

typedef struct tagSuiView$__Closure_91_22 SuiView$__Closure_91_22;

typedef struct tagSuiView$__Closure_337_18 SuiView$__Closure_337_18;

typedef struct tagSuiView$__Closure_356_18 SuiView$__Closure_356_18;

typedef struct tagSuiView$__Closure_372_18 SuiView$__Closure_372_18;



struct tagSuiView$__Block_89_34 {
	SuiView$ColorPalete*  self ;
};





struct tagSuiView$__Block_315_13 {
	SuiView$ColorView*  self ;
};





struct tagSuiView$__Closure_91_22 {
	void  (*invoke)(SuiView$__Closure_91_22 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiView$__Block_89_34*  __var___Block_89_34 ;
};





struct tagSuiView$__Closure_337_18 {
	void  (*invoke)(SuiView$__Closure_337_18 *  self, SuiCore$Vec2 ratio);
	Vtable_Object *  vtable ;
	SuiView$__Block_315_13*  __var___Block_315_13 ;
};





struct tagSuiView$__Closure_356_18 {
	void  (*invoke)(SuiView$__Closure_356_18 *  self, SuiCore$Vec2 ratio);
	Vtable_Object *  vtable ;
	SuiView$__Block_315_13*  __var___Block_315_13 ;
};





struct tagSuiView$__Closure_372_18 {
	void  (*invoke)(SuiView$__Closure_372_18 *  self, SuiCore$Vec2 ratio);
	Vtable_Object *  vtable ;
	SuiView$__Block_315_13*  __var___Block_315_13 ;
};





// static function declaration
static char *  new_createChessBg_inMemory(int  w, int  h, int  r, int  g, int  b, int  a);
static SuiCore$Image *  gocChessBgImage(SuiCore$Canvas *  canvas);
static void  __finiBlock___Block_89_34(SuiView$__Block_89_34 *  self);
static void  __finiBlock___Block_315_13(SuiView$__Block_315_13 *  self);
static void  __fn___Closure_91_22(SuiView$__Closure_91_22 *  self, SuiView$Drag *  d);
static void  __fini___Closure_91_22(SuiView$__Closure_91_22 *  self);
static SuiView$__Closure_91_22*  __make___Closure_91_22(SuiView$__Closure_91_22 **  __outRef__, SuiView$__Block_89_34 *  __var___Block_89_34);
static void  __fn___Closure_337_18(SuiView$__Closure_337_18 *  self, SuiCore$Vec2 ratio);
static void  __fini___Closure_337_18(SuiView$__Closure_337_18 *  self);
static SuiView$__Closure_337_18*  __make___Closure_337_18(SuiView$__Closure_337_18 **  __outRef__, SuiView$__Block_315_13 *  __var___Block_315_13);
static void  __fn___Closure_356_18(SuiView$__Closure_356_18 *  self, SuiCore$Vec2 ratio);
static void  __fini___Closure_356_18(SuiView$__Closure_356_18 *  self);
static SuiView$__Closure_356_18*  __make___Closure_356_18(SuiView$__Closure_356_18 **  __outRef__, SuiView$__Block_315_13 *  __var___Block_315_13);
static void  __fn___Closure_372_18(SuiView$__Closure_372_18 *  self, SuiCore$Vec2 ratio);
static void  __fini___Closure_372_18(SuiView$__Closure_372_18 *  self);
static SuiView$__Closure_372_18*  __make___Closure_372_18(SuiView$__Closure_372_18 **  __outRef__, SuiView$__Block_315_13 *  __var___Block_315_13);


static char *  new_createChessBg_inMemory(int  w, int  h, int  r, int  g, int  b, int  a){
	char *  data = malloc(w * h * 4) ;
	int  hw = w / 2;
	int  hh = h / 2;
	for (int  y = 0; y < h; y++) {
		for (int  x = 0; x < w; x++) {
			int  i = (y * w + x) * 4;
			data[i] = r;
			data[i + 1] = g;
			data[i + 2] = b;
			data[i + 3] = (x < hw && y < hh) || (x >= hw && y >= hh) ? a : 0;
		}
	}
	return data; 
}

static SuiCore$Image *  gocChessBgImage(SuiCore$Canvas *  canvas){
	static URGC_VAR_CLEANUP_CLASS SuiCore$Image*  img = NULL;
	if (img == NULL) {
		int  w = 16;
		int  h = 16;
		char *  imgData = new_createChessBg_inMemory(w, h, 128, 128, 128, 255) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_1 = NULL;
		urgc_set_var_class(&img, SuiCore$Canvas$createImageRGBA(&tmpReturn_1, canvas, w, h, (const unsigned char * )imgData) ) ;
		free(imgData) ;
	}
	return img; 
}


//vtable instance
Vtable_SuiView$ColorPalete _vtable_SuiView$ColorPalete;

// init meta

void SuiView$ColorPalete_initMeta(Vtable_SuiView$ColorPalete *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "indicatorPos", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiView$ColorPalete, indicatorPos), false, false, 0);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiView$ColorPalete, drag), true, false, 1);
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(SuiView$ColorPalete, color), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "xDraggale", OrcMetaType_bool, offsetof(SuiView$ColorPalete, xDraggale), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "yDraggale", OrcMetaType_bool, offsetof(SuiView$ColorPalete, yDraggale), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "kind", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$ColorPalete, kind), true, false, 1);
	orc_metaField_class(&pNext, "indicatorKind", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiView$ColorPalete, indicatorKind), true, false, 1);

	orc_metaField_method(&pNext, "calcIndicatorPosInPixel", offsetof(SuiView$ColorPalete, calcIndicatorPosInPixel));
	orc_metaField_method(&pNext, "onMouseEvent", offsetof(SuiView$ColorPalete, onMouseEvent));
	orc_metaField_method(&pNext, "onDrag", offsetof(SuiView$ColorPalete, onDrag));
	orc_metaField_method(&pNext, "drawCircle", offsetof(SuiView$ColorPalete, drawCircle));
	orc_metaField_method(&pNext, "drawMark", offsetof(SuiView$ColorPalete, drawMark));
	orc_metaField_method(&pNext, "drawHue", offsetof(SuiView$ColorPalete, drawHue));
	orc_metaField_method(&pNext, "drawAlpha", offsetof(SuiView$ColorPalete, drawAlpha));
	orc_metaField_method(&pNext, "drawSv", offsetof(SuiView$ColorPalete, drawSv));
}


// vtable init


Vtable_SuiView$ColorPalete* Vtable_SuiView$ColorPalete_init(Vtable_SuiView$ColorPalete* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ColorPalete;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ColorPalete_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ColorPalete";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ColorPalete_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ColorPalete_fini(SuiView$ColorPalete *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiView$ColorPalete*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiView$ColorPalete*)self)->kind);
	urgc_fini_field_class(self, (void**)&((SuiView$ColorPalete*)self)->indicatorKind);

}

// init fields function


void SuiView$ColorPalete_init_fields(SuiView$ColorPalete *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiView$ColorPalete_fini;
	//fields
    {
	((SuiView$ColorPalete*)self)->indicatorPos = SuiCore$mkVec2(0, 0) ;
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ColorPalete*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	((SuiView$ColorPalete*)self)->color = 0xffff0000;
	((SuiView$ColorPalete*)self)->xDraggale = true;
	((SuiView$ColorPalete*)self)->yDraggale = true;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ColorPalete*)self)->kind, Orc$str(&tmpReturn_2, "sv") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiView$ColorPalete*)self)->indicatorKind, Orc$str(&tmpReturn_3, "rect") );
	urgc_set_field(self, (void**)&((SuiView$ColorPalete*)self)->onChanged, NULL);
    }
	((SuiView$ColorPalete*)self)->calcIndicatorPosInPixel = (void*)SuiView$ColorPalete$calcIndicatorPosInPixel;
	((SuiCore$Emitter*)self)->onEvent = (void*)SuiView$ColorPalete$onEvent;
	((SuiView$ColorPalete*)self)->onMouseEvent = (void*)SuiView$ColorPalete$onMouseEvent;
	((SuiView$ColorPalete*)self)->onDrag = (void*)SuiView$ColorPalete$onDrag;
	((SuiView$ColorPalete*)self)->drawCircle = (void*)SuiView$ColorPalete$drawCircle;
	((SuiView$ColorPalete*)self)->drawMark = (void*)SuiView$ColorPalete$drawMark;
	((SuiView$ColorPalete*)self)->drawHue = (void*)SuiView$ColorPalete$drawHue;
	((SuiView$ColorPalete*)self)->drawAlpha = (void*)SuiView$ColorPalete$drawAlpha;
	((SuiView$ColorPalete*)self)->drawSv = (void*)SuiView$ColorPalete$drawSv;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$ColorPalete$draw_self;
}

// init function

void SuiView$ColorPalete_init(SuiView$ColorPalete *self, void *pOwner){
    Vtable_SuiView$ColorPalete_init(&_vtable_SuiView$ColorPalete);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ColorPalete;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ColorPalete_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ColorPalete * SuiView$ColorPalete_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ColorPalete *self = calloc(1, sizeof(SuiView$ColorPalete));
	
    SuiView$ColorPalete_init(self, pOwner);
    return self;
}


// class members
SuiCore$Vec2 SuiView$ColorPalete$calcIndicatorPosInPixel(SuiView$ColorPalete *  self){
	SuiCore$Rect r = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	return SuiCore$mkVec2(r.w * self->indicatorPos.x, r.h * (1.0 - self->indicatorPos.y)) ; 
}


void  SuiView$ColorPalete$onEvent(SuiView$ColorPalete *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		self->onMouseEvent(self, (SuiCore$MouseEvent * )e) ;
	}
}


void  SuiView$ColorPalete$onMouseEvent(SuiView$ColorPalete *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP SuiView$__Block_89_34*  __var___Block_89_34 = (__var___Block_89_34=NULL,urgc_init_var((void**)&__var___Block_89_34, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_89_34) , __finiBlock___Block_89_34) ));
	urgc_set_field_class(__var___Block_89_34, (void * )offsetof(SuiView$__Block_89_34, self) , self) ;
	if (me->isMouseDown) {
		URGC_VAR_CLEANUP SuiView$__Closure_91_22*  tmpReturn_1 = NULL;
		urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_91_22(&tmpReturn_1, __var___Block_89_34) ) ;
		self->drag->onMouseDown(self->drag, me) ;
	}
}


void  SuiView$ColorPalete$onDrag(SuiView$ColorPalete *  self, SuiView$Drag *  d){
	if (d->isDragging || d->isDragStart || d->isDragChecking) {
		SuiCore$Rect r = ((SuiCore$View * )self)->getContentLocalRect(self) ;
		SuiCore$Vec2 pos = self->calcIndicatorPosInPixel(self) ;
		int  tox = pos.x + d->deltaPos.x;
		int  toy = pos.y + d->deltaPos.y;
		{
			SuiCore$Rect r = ((SuiCore$View * )self)->getContentClientRect(self) ;
			tox = d->currentClientPos.x - r.x;
			toy = d->currentClientPos.y - r.y;
			printf("tox:%d, toy:%d cur:%f, %f, r:%f,%f\n", tox, toy, d->currentClientPos.x, d->currentClientPos.y, r.x, r.y) ;
		}
		printf("tox:%d, toy:%d\n", tox, toy) ;
		tox = Orc$clampInt(tox, 0, r.w) ;
		toy = Orc$clampInt(toy, 0, r.h) ;
		float  xRatio = 0;
		if (r.w > 0) {
			xRatio = tox / r.w;
		}
		float  yRatio = 0;
		if (r.h > 0) {
			yRatio = toy / r.h;
		}
		if (self->xDraggale) {
			self->indicatorPos.x = xRatio;
		}
		if (self->yDraggale) {
			self->indicatorPos.y = 1.0 - yRatio;
		}
		if (self->onChanged) {
			(*(self->onChanged))((void * )(self->onChanged), self->indicatorPos) ;
		}
		((SuiCore$ViewBase * )self)->invalidDraw(self) ;
	}
}


void  SuiView$ColorPalete$drawCircle(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  x, int  y){
	SuiCore$Canvas$strokeWidth(canvas, 2.0f) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$circle(canvas, x, y, 4) ;
	SuiCore$Canvas$strokeColor(canvas, 255, 255, 255, 192) ;
	SuiCore$Canvas$stroke(canvas) ;
}


void  SuiView$ColorPalete$drawMark(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  y){
	int  h = 8;
	SuiCore$Canvas$strokeWidth(canvas, 2.0f) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, -2.f, y - h / 2, w + 4.f, h) ;
	SuiCore$Canvas$strokeColor(canvas, 255, 255, 255, 192) ;
	SuiCore$Canvas$stroke(canvas) ;
}


void  SuiView$ColorPalete$drawHue(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h){
	float  seg = h / 6.0;
	for (int  i = 0; i < 6; i++) {
		float  y = i * seg;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$rect(canvas, 0, y, w, seg + (i == 5 ? 0 : 1)) ;
		SuiCore$Hsla tmpStructThis1;
		SuiCore$Hsla tmpStructThis2;
		SuiCore$Canvas$linearGradient(canvas, true, 0, y, 0, y + seg, SuiCore$Hsla$toRgbaInt((tmpStructThis1 = SuiCore$mkHsla(1.0 - (i / 6.0), 1.0f, 0.55, 255) ,&tmpStructThis1)) , SuiCore$Hsla$toRgbaInt((tmpStructThis2 = SuiCore$mkHsla(1.0 - ((i + 1) / 6.0), 1.0f, 0.55, 255) ,&tmpStructThis2)) ) ;
		SuiCore$Canvas$fill(canvas) ;
	}
}


void  SuiView$ColorPalete$drawAlpha(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h){
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, 0, w, h) ;
	SuiCore$Image *  bg = gocChessBgImage(canvas) ;
	SuiCore$Canvas$imagePattern(canvas, true, 0, 0, 16, 16, 0, bg, 1) ;
	SuiCore$Canvas$fill(canvas) ;
	SuiCore$Canvas$linearGradient(canvas, true, 0.0, 0.0, 0.0, h, SuiCore$mkIntByRgba(255, 255, 255, 255) , SuiCore$mkIntByRgba(0, 0, 0, 200) ) ;
	SuiCore$Canvas$fill(canvas) ;
}


void  SuiView$ColorPalete$drawSv(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas, int  w, int  h){
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, 0, w, h) ;
	SuiCore$Canvas$fillColorByInt32(canvas, self->color) ;
	SuiCore$Canvas$fill(canvas) ;
	SuiCore$Canvas$linearGradient(canvas, true, 0.0, 0.0, w, 0.0, SuiCore$mkIntByRgba(255, 255, 255, 255) , SuiCore$mkIntByRgba(255, 255, 255, 0) ) ;
	SuiCore$Canvas$fill(canvas) ;
	{
		SuiCore$Canvas$linearGradient(canvas, true, 0.0, 0.0, 0.0, h, SuiCore$mkIntByRgba(0, 0, 0, 0) , SuiCore$mkIntByRgba(0, 0, 0, 255) ) ;
		SuiCore$Canvas$fill(canvas) ;
	}
}


void  SuiView$ColorPalete$draw_self(SuiView$ColorPalete *  self, SuiCore$Canvas *  canvas){
	SuiCore$Rect r = ((SuiCore$View * )self)->getContentLocalRect(self) ;
	int  w = r.w;
	int  h = r.h;
	((SuiCore$View * )self)->backgroundColor = 0xff000000;
	SuiCore$View$draw_self(self, canvas) ;
	if (Orc$String$equals(self->kind, "sv") ) {
		self->drawSv(self, canvas, w, h) ;
	}
	if (Orc$String$equals(self->kind, "alpha") ) {
		self->drawAlpha(self, canvas, w, h) ;
	}
	if (Orc$String$equals(self->kind, "hue") ) {
		self->drawHue(self, canvas, w, h) ;
	}
	SuiCore$Vec2 indiPos = self->calcIndicatorPosInPixel(self) ;
	if (Orc$String$equals(self->indicatorKind, "rect") ) {
		self->drawMark(self, canvas, w, indiPos.y) ;
	}
	if (Orc$String$equals(self->indicatorKind, "circle") ) {
		self->drawCircle(self, canvas, indiPos.x, indiPos.y) ;
	}
}




//vtable instance
Vtable_SuiView$ColorView _vtable_SuiView$ColorView;

// init meta

void SuiView$ColorView_initMeta(Vtable_SuiView$ColorView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "hsva", SuiCore$Hsva_getOrInitMetaStruct(), offsetof(SuiView$ColorView, hsva), false, false, 0);
	orc_metaField_primitive(&pNext, "showRgba", OrcMetaType_bool, offsetof(SuiView$ColorView, showRgba), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "showHsva", OrcMetaType_bool, offsetof(SuiView$ColorView, showHsva), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "showHsla", OrcMetaType_bool, offsetof(SuiView$ColorView, showHsla), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "fire_onChanged", offsetof(SuiView$ColorView, fire_onChanged));
	orc_metaField_method(&pNext, "setColor", offsetof(SuiView$ColorView, setColor));
}


// vtable init


Vtable_SuiView$ColorView* Vtable_SuiView$ColorView_init(Vtable_SuiView$ColorView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiView$ColorView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiLayout$LayoutLinear_init(&_vtable_SuiLayout$LayoutLinear);

	// init by super vtable init function
    Vtable_SuiLayout$LayoutLinear_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiLayout$LayoutLinear;
    ((Vtable_Object*)pvt)->make = (void*)&SuiView$ColorView_new;
    ((Vtable_Object*)pvt)->className = "SuiView$ColorView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiView$ColorView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiView$ColorView_fini(SuiView$ColorView *self){
	//super fini
    SuiLayout$LayoutLinear_fini((SuiLayout$LayoutLinear *)self);

    //字段释放
	

}

// init fields function


void SuiView$ColorView_init_fields(SuiView$ColorView *self){
	//super class
    SuiLayout$LayoutLinear_init_fields((SuiLayout$LayoutLinear*)self);

    ((Object*)self)->fini = (void*)SuiView$ColorView_fini;
	//fields
    {
	((SuiView$ColorView*)self)->hsva = SuiCore$mkHsva(0.0, 1.0, 1.0, 255) ;
	((SuiView$ColorView*)self)->showRgba = true;
	((SuiView$ColorView*)self)->showHsva = false;
	((SuiView$ColorView*)self)->showHsla = false;
	urgc_set_field(self, (void**)&((SuiView$ColorView*)self)->onChanged, NULL);
    }
	((SuiView$ColorView*)self)->fire_onChanged = (void*)SuiView$ColorView$fire_onChanged;
	((SuiView$ColorView*)self)->setColor = (void*)SuiView$ColorView$setColor;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiView$ColorView$draw_self;
	((SuiCore$Node*)self)->react = (void*)SuiView$ColorView$react;
}

// init function

void SuiView$ColorView_init(SuiView$ColorView *self, void *pOwner){
    Vtable_SuiView$ColorView_init(&_vtable_SuiView$ColorView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiView$ColorView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiView$ColorView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiView$ColorView * SuiView$ColorView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiView$ColorView *self = calloc(1, sizeof(SuiView$ColorView));
	
    SuiView$ColorView_init(self, pOwner);
    return self;
}


// class members
void  SuiView$ColorView$fire_onChanged(SuiView$ColorView *  self){
	if (self->onChanged) {
		int  color = SuiCore$Hsva$toRgbaInt(&self->hsva) ;
		(*(self->onChanged))((void * )(self->onChanged), color) ;
	}
}


void  SuiView$ColorView$setColor(SuiView$ColorView *  self, int  c){
	SuiCore$Rgba rgba = SuiCore$mkRgbaByInt(c) ;
	self->hsva = SuiCore$rgbaToHsva(rgba) ;
}


void  SuiView$ColorView$draw_self(SuiView$ColorView *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
}


void  SuiView$ColorView$react(SuiView$ColorView *  self){
	URGC_VAR_CLEANUP SuiView$__Block_315_13*  __var___Block_315_13 = (__var___Block_315_13=NULL,urgc_init_var((void**)&__var___Block_315_13, orc_alloc_and_set_deleter(sizeof(SuiView$__Block_315_13) , __finiBlock___Block_315_13) ));
	urgc_set_field_class(__var___Block_315_13, (void * )offsetof(SuiView$__Block_315_13, self) , self) ;
	((SuiCore$Node * )self)->startInnerReact(self) ;
	SuiView$ColorView *  o = self;
	SuiCore$Hsva sv = SuiCore$mkHsva(self->hsva.h, 1.0, 1.0, 255) ;
	int  svColor = SuiCore$Hsva$toRgbaInt(&sv) ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->direction, "column") ;
	Orc$String$set(((SuiLayout$LayoutLinear * )self)->alignItems, "stretch") ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_326_2 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_326_2;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_326_2 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$ColorPalete*  tmpReturn_2 = NULL;
		{
			SuiView$ColorPalete*  __scopeVar_327_3 = SuiView$mkColorPalete(&tmpReturn_2, o, 0) , *o = __scopeVar_327_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_327_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			SuiCore$Vec2$set(&o->indicatorPos, self->hsva.s, self->hsva.v) ;
			o->color = svColor;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$ColorPalete, kind) , Orc$str(&tmpReturn_3, "sv") ) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$ColorPalete, indicatorKind) , Orc$str(&tmpReturn_4, "circle") ) ;
			((SuiCore$View * )o)->width = 200;
			((SuiCore$View * )o)->height = 200;
			((SuiCore$View * )o)->margin.right = 6;
			URGC_VAR_CLEANUP SuiView$__Closure_337_18*  tmpReturn_5 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$ColorPalete, onChanged) , __make___Closure_337_18(&tmpReturn_5, __var___Block_315_13) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$ColorPalete*  tmpReturn_6 = NULL;
		{
			SuiView$ColorPalete*  __scopeVar_348_3 = SuiView$mkColorPalete(&tmpReturn_6, o, 0) , *o = __scopeVar_348_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_348_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->indicatorPos.y = self->hsva.h / 360.0;
			printf("hue:%f\n", self->hsva.h) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$ColorPalete, kind) , Orc$str(&tmpReturn_7, "hue") ) ;
			((SuiCore$View * )o)->width = 20;
			((SuiCore$View * )o)->height = 200;
			((SuiCore$View * )o)->margin.right = 6;
			URGC_VAR_CLEANUP SuiView$__Closure_356_18*  tmpReturn_8 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$ColorPalete, onChanged) , __make___Closure_356_18(&tmpReturn_8, __var___Block_315_13) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$ColorPalete*  tmpReturn_9 = NULL;
		{
			SuiView$ColorPalete*  __scopeVar_366_3 = SuiView$mkColorPalete(&tmpReturn_9, o, 0) , *o = __scopeVar_366_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_366_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->indicatorPos.y = self->hsva.a / 255.0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$ColorPalete, kind) , Orc$str(&tmpReturn_10, "alpha") ) ;
			((SuiCore$View * )o)->width = 20;
			((SuiCore$View * )o)->height = 200;
			URGC_VAR_CLEANUP SuiView$__Closure_372_18*  tmpReturn_11 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$ColorPalete, onChanged) , __make___Closure_372_18(&tmpReturn_11, __var___Block_315_13) ) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_12 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_386_2 = SuiLayout$layoutLinear(&tmpReturn_12, o, 0) , *o = __scopeVar_386_2;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_386_2 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_13 = NULL;
		{
			SuiCore$View*  __scopeVar_387_3 = SuiView$mkView(&tmpReturn_13, o, 0) , *o = __scopeVar_387_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_387_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->backgroundColor = SuiCore$Hsva$toRgbaInt(&self->hsva) ;
			o->width = 16;
			o->height = 16;
			o->border->setAll(o->border, 1, 0xff000000) ;
			SuiCore$Inset$setAll(&o->padding, 1) ;
			SuiCore$Inset$setVer(&o->margin, 6) ;
			o->margin.right = 6;
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_14 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_396_3 = SuiLayout$layoutLinear(&tmpReturn_14, o, 0) , *o = __scopeVar_396_3;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_396_3 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "start") ;
			if (self->showHsva) {
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_15 = NULL;
				{
					SuiView$TextView*  __scopeVar_400_5 = SuiView$mkTextView(&tmpReturn_15, o, 0) , *o = __scopeVar_400_5;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_400_5 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  s = SuiCore$Hsva$toString((s = NULL,&s), &self->hsva) ;
					o->setText(o, s) ;
				}
			}
			if (self->showRgba) {
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_16 = NULL;
				{
					SuiView$TextView*  __scopeVar_406_5 = SuiView$mkTextView(&tmpReturn_16, o, 0) , *o = __scopeVar_406_5;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_406_5 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Rgba r = SuiCore$Hsva$toRgba(&self->hsva) ;
					URGC_VAR_CLEANUP_CLASS Orc$String*  s = SuiCore$Rgba$toString((s = NULL,&s), &r) ;
					o->setText(o, s) ;
				}
			}
			if (self->showHsla) {
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_17 = NULL;
				{
					SuiView$TextView*  __scopeVar_413_5 = SuiView$mkTextView(&tmpReturn_17, o, 0) , *o = __scopeVar_413_5;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_413_5 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Rgba r = SuiCore$Hsva$toRgba(&self->hsva) ;
					SuiCore$Hsla hsl = SuiCore$rgbaToHsla(r) ;
					URGC_VAR_CLEANUP_CLASS Orc$String*  s = SuiCore$Hsla$toString((s = NULL,&s), &hsl) ;
					o->setText(o, s) ;
				}
			}
		}
	}
	((SuiCore$Node * )self)->endInnerReact(self) ;
}



static void  __finiBlock___Block_89_34(SuiView$__Block_89_34 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_89_34, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_315_13(SuiView$__Block_315_13 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiView$__Block_315_13, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_91_22(SuiView$__Closure_91_22 *  self, SuiView$Drag *  d){
	self->__var___Block_89_34->self->onDrag(self->__var___Block_89_34->self, d) ;
}

static void  __fini___Closure_91_22(SuiView$__Closure_91_22 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_91_22, __var___Block_89_34) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_91_22*  __make___Closure_91_22(SuiView$__Closure_91_22 **  __outRef__, SuiView$__Block_89_34 *  __var___Block_89_34){
	URGC_VAR_CLEANUP SuiView$__Closure_91_22*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_91_22) , __fini___Closure_91_22) ));
	self->invoke = __fn___Closure_91_22;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_91_22, __var___Block_89_34) , __var___Block_89_34) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_337_18(SuiView$__Closure_337_18 *  self, SuiCore$Vec2 ratio){
	printf("ratio:%f,%f\n", ratio.x, ratio.y) ;
	self->__var___Block_315_13->self->hsva.s = ratio.x;
	self->__var___Block_315_13->self->hsva.v = ratio.y;
	self->__var___Block_315_13->self->fire_onChanged(self->__var___Block_315_13->self) ;
	((SuiCore$Node * )self->__var___Block_315_13->self)->trigger_react(self->__var___Block_315_13->self) ;
}

static void  __fini___Closure_337_18(SuiView$__Closure_337_18 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_337_18, __var___Block_315_13) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_337_18*  __make___Closure_337_18(SuiView$__Closure_337_18 **  __outRef__, SuiView$__Block_315_13 *  __var___Block_315_13){
	URGC_VAR_CLEANUP SuiView$__Closure_337_18*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_337_18) , __fini___Closure_337_18) ));
	self->invoke = __fn___Closure_337_18;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_337_18, __var___Block_315_13) , __var___Block_315_13) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_356_18(SuiView$__Closure_356_18 *  self, SuiCore$Vec2 ratio){
	self->__var___Block_315_13->self->hsva.h = ratio.y * 360.0;
	printf("hue ratio:%f,%f. hue:%f\n", ratio.x, ratio.y, self->__var___Block_315_13->self->hsva.h) ;
	self->__var___Block_315_13->self->fire_onChanged(self->__var___Block_315_13->self) ;
	((SuiCore$Node * )self->__var___Block_315_13->self)->trigger_react(self->__var___Block_315_13->self) ;
}

static void  __fini___Closure_356_18(SuiView$__Closure_356_18 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_356_18, __var___Block_315_13) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_356_18*  __make___Closure_356_18(SuiView$__Closure_356_18 **  __outRef__, SuiView$__Block_315_13 *  __var___Block_315_13){
	URGC_VAR_CLEANUP SuiView$__Closure_356_18*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_356_18) , __fini___Closure_356_18) ));
	self->invoke = __fn___Closure_356_18;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_356_18, __var___Block_315_13) , __var___Block_315_13) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_372_18(SuiView$__Closure_372_18 *  self, SuiCore$Vec2 ratio){
	self->__var___Block_315_13->self->hsva.a = ratio.y * 255.0;
	self->__var___Block_315_13->self->fire_onChanged(self->__var___Block_315_13->self) ;
	printf("alpha ratio:%f,%f. alpha:%d\n", ratio.x, ratio.y, self->__var___Block_315_13->self->hsva.a) ;
	((SuiCore$Node * )self->__var___Block_315_13->self)->trigger_react(self->__var___Block_315_13->self) ;
}

static void  __fini___Closure_372_18(SuiView$__Closure_372_18 *  self){
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_372_18, __var___Block_315_13) , NULL) ;
	urgc_free_later(self) ;
}

static SuiView$__Closure_372_18*  __make___Closure_372_18(SuiView$__Closure_372_18 **  __outRef__, SuiView$__Block_315_13 *  __var___Block_315_13){
	URGC_VAR_CLEANUP SuiView$__Closure_372_18*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiView$__Closure_372_18) , __fini___Closure_372_18) ));
	self->invoke = __fn___Closure_372_18;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiView$__Closure_372_18, __var___Block_315_13) , __var___Block_315_13) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

SuiView$ColorPalete*  SuiView$mkColorPalete(SuiView$ColorPalete **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$ColorPalete* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$ColorPalete_init(NULL)) ) ; 
}

SuiView$ColorView*  SuiView$mkColorView(SuiView$ColorView **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiView$ColorView* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiView$ColorView_init(NULL)) ) ; 
}



