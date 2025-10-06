
#include "ImageChessBg_orc.h" 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Orc/String_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Color_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_HoroEditor$ImageChessBg _vtable_HoroEditor$ImageChessBg;

// init meta

void HoroEditor$ImageChessBg_initMeta(Vtable_HoroEditor$ImageChessBg *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "width", OrcMetaType_int, offsetof(HoroEditor$ImageChessBg, width), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "height", OrcMetaType_int, offsetof(HoroEditor$ImageChessBg, height), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color0", OrcMetaType_int, offsetof(HoroEditor$ImageChessBg, color0), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color1", OrcMetaType_int, offsetof(HoroEditor$ImageChessBg, color1), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "img", ((Vtable_Object*)Vtable_SuiCore$Image_init(0)), offsetof(HoroEditor$ImageChessBg, img), true, false, 1);

	orc_metaField_method(&pNext, "new_createChessBg_inMemory", offsetof(HoroEditor$ImageChessBg, new_createChessBg_inMemory));
	orc_metaField_method(&pNext, "gocChessBgImage", offsetof(HoroEditor$ImageChessBg, gocChessBgImage));
}


// vtable init


Vtable_HoroEditor$ImageChessBg* Vtable_HoroEditor$ImageChessBg_init(Vtable_HoroEditor$ImageChessBg* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$ImageChessBg;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$ImageChessBg_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$ImageChessBg";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$ImageChessBg_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$ImageChessBg_fini(HoroEditor$ImageChessBg *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void HoroEditor$ImageChessBg_init_fields(HoroEditor$ImageChessBg *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$ImageChessBg_fini;
	//fields
    {
	((HoroEditor$ImageChessBg*)self)->width = 32;
	((HoroEditor$ImageChessBg*)self)->height = 32;
	((HoroEditor$ImageChessBg*)self)->color0 = 0xff333333;
	((HoroEditor$ImageChessBg*)self)->color1 = 0xff000000;
	urgc_set_field_class(self, (void**)&((HoroEditor$ImageChessBg*)self)->img, NULL);
    }
	((HoroEditor$ImageChessBg*)self)->new_createChessBg_inMemory = (void*)HoroEditor$ImageChessBg$new_createChessBg_inMemory;
	((HoroEditor$ImageChessBg*)self)->gocChessBgImage = (void*)HoroEditor$ImageChessBg$gocChessBgImage;
}

// init function

void HoroEditor$ImageChessBg_init(HoroEditor$ImageChessBg *self, void *pOwner){
    Vtable_HoroEditor$ImageChessBg_init(&_vtable_HoroEditor$ImageChessBg);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$ImageChessBg;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$ImageChessBg_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$ImageChessBg * HoroEditor$ImageChessBg_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$ImageChessBg *self = calloc(1, sizeof(HoroEditor$ImageChessBg));
	
    HoroEditor$ImageChessBg_init(self, pOwner);
    return self;
}


// class members
char *  HoroEditor$ImageChessBg$new_createChessBg_inMemory(HoroEditor$ImageChessBg *  self, int  w, int  h){
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


SuiCore$Image *  HoroEditor$ImageChessBg$gocChessBgImage(HoroEditor$ImageChessBg *  self, SuiCore$Canvas *  canvas){
	if (self->img == NULL) {
		int  w = self->width;
		int  h = self->height;
		char *  imgData = self->new_createChessBg_inMemory(self, w, h) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$ImageChessBg, img) , SuiCore$Canvas$createImageRGBA(&tmpReturn_1, canvas, w, h, (const unsigned char * )imgData) ) ;
		free(imgData) ;
	}
	return self->img; 
}





