
#include "ChessBgViewCallback_orc.h" 

#include <stdio.h>
#include <stdlib.h>
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Canvas_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$ChessBgViewCallback _vtable_SuiDesigner$ChessBgViewCallback;

// init meta

void SuiDesigner$ChessBgViewCallback_initMeta(Vtable_SuiDesigner$ChessBgViewCallback *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "width", OrcMetaType_int, offsetof(SuiDesigner$ChessBgViewCallback, width), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "height", OrcMetaType_int, offsetof(SuiDesigner$ChessBgViewCallback, height), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color0", OrcMetaType_int, offsetof(SuiDesigner$ChessBgViewCallback, color0), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color1", OrcMetaType_int, offsetof(SuiDesigner$ChessBgViewCallback, color1), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "img", ((Vtable_Object*)Vtable_SuiCore$Image_init(0)), offsetof(SuiDesigner$ChessBgViewCallback, img), true, false, 1);
	orc_metaField_class(&pNext, "obj", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiDesigner$ChessBgViewCallback, obj), true, false, 1);

	orc_metaField_method(&pNext, "new_createChessBg_inMemory", offsetof(SuiDesigner$ChessBgViewCallback, new_createChessBg_inMemory));
	orc_metaField_method(&pNext, "gocChessBgImage", offsetof(SuiDesigner$ChessBgViewCallback, gocChessBgImage));
}


// vtable init


Vtable_SuiDesigner$ChessBgViewCallback* Vtable_SuiDesigner$ChessBgViewCallback_init(Vtable_SuiDesigner$ChessBgViewCallback* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ChessBgViewCallback;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewCallback_init(&_vtable_SuiCore$ViewCallback);

	// init by super vtable init function
    Vtable_SuiCore$ViewCallback_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewCallback;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ChessBgViewCallback_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ChessBgViewCallback";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ChessBgViewCallback_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ChessBgViewCallback_fini(SuiDesigner$ChessBgViewCallback *self){
	//super fini
    SuiCore$ViewCallback_fini((SuiCore$ViewCallback *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ChessBgViewCallback*)self)->img);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ChessBgViewCallback*)self)->obj);

}

// init fields function


void SuiDesigner$ChessBgViewCallback_init_fields(SuiDesigner$ChessBgViewCallback *self){
	//super class
    SuiCore$ViewCallback_init_fields((SuiCore$ViewCallback*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ChessBgViewCallback_fini;
	//fields
    {
	((SuiDesigner$ChessBgViewCallback*)self)->width = 32;
	((SuiDesigner$ChessBgViewCallback*)self)->height = 32;
	((SuiDesigner$ChessBgViewCallback*)self)->color0 = 0xff333333;
	((SuiDesigner$ChessBgViewCallback*)self)->color1 = 0xff000000;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ChessBgViewCallback*)self)->img, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ChessBgViewCallback*)self)->obj, NULL);
    }
	((Object*)self)->dtor = (void*)SuiDesigner$ChessBgViewCallback$dtor;
	((SuiCore$ViewCallback*)self)->cbLayout = (void*)SuiDesigner$ChessBgViewCallback$cbLayout;
	((SuiCore$ViewCallback*)self)->cbDraw = (void*)SuiDesigner$ChessBgViewCallback$cbDraw;
	((SuiDesigner$ChessBgViewCallback*)self)->new_createChessBg_inMemory = (void*)SuiDesigner$ChessBgViewCallback$new_createChessBg_inMemory;
	((SuiDesigner$ChessBgViewCallback*)self)->gocChessBgImage = (void*)SuiDesigner$ChessBgViewCallback$gocChessBgImage;
}

// init function

void SuiDesigner$ChessBgViewCallback_init(SuiDesigner$ChessBgViewCallback *self, void *pOwner){
    Vtable_SuiDesigner$ChessBgViewCallback_init(&_vtable_SuiDesigner$ChessBgViewCallback);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ChessBgViewCallback;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ChessBgViewCallback_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ChessBgViewCallback * SuiDesigner$ChessBgViewCallback_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ChessBgViewCallback *self = calloc(1, sizeof(SuiDesigner$ChessBgViewCallback));
	
    SuiDesigner$ChessBgViewCallback_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ChessBgViewCallback$dtor(SuiDesigner$ChessBgViewCallback *  self){
	printf(".Dtor ChessBgViewCallback\n") ;
}


bool  SuiDesigner$ChessBgViewCallback$cbLayout(SuiDesigner$ChessBgViewCallback *  self, SuiCore$View *  div, SuiCore$Frame *  ctx){
	return false; 
}


bool  SuiDesigner$ChessBgViewCallback$cbDraw(SuiDesigner$ChessBgViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas){
	SuiCore$Image *  bg = self->gocChessBgImage(self, canvas) ;
	SuiCore$Rect r = div->getViewRect(div) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 0, 0, r.w, r.h) ;
	SuiCore$Canvas$imagePattern(canvas, true, 0, 0, self->width, self->height, 0, bg, 1) ;
	SuiCore$Canvas$fill(canvas) ;
	return false; 
}


char *  SuiDesigner$ChessBgViewCallback$new_createChessBg_inMemory(SuiDesigner$ChessBgViewCallback *  self, int  w, int  h){
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


SuiCore$Image *  SuiDesigner$ChessBgViewCallback$gocChessBgImage(SuiDesigner$ChessBgViewCallback *  self, SuiCore$Canvas *  canvas){
	if (self->img == NULL) {
		int  w = self->width;
		int  h = self->height;
		char *  imgData = self->new_createChessBg_inMemory(self, w, h) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ChessBgViewCallback, img) , SuiCore$Canvas$createImageRGBA(&tmpReturn_1, canvas, w, h, (const unsigned char * )imgData) ) ;
		free(imgData) ;
	}
	return self->img; 
}





