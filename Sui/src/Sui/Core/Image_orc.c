
#include "Image_orc.h" 

#include <stdio.h>
#include "../../nanovg/nanovg.h"
#include "../../nanovg/stb_image_write.h"
#include "./Global_orc.h"
#include "./Vec2_orc.h"
#include "./Canvas_orc.h"
#include "../../Orc/Map_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Sgl/Buffer_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Image _vtable_SuiCore$Image;

// init meta

void SuiCore$Image_initMeta(Vtable_SuiCore$Image *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "_img", OrcMetaType_int, offsetof(SuiCore$Image, _img), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "size", offsetof(SuiCore$Image, size));
	orc_metaField_method(&pNext, "width", offsetof(SuiCore$Image, width));
	orc_metaField_method(&pNext, "height", offsetof(SuiCore$Image, height));
}


// vtable init


Vtable_SuiCore$Image* Vtable_SuiCore$Image_init(Vtable_SuiCore$Image* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Image;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Image_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Image";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Image_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$Image_fini(SuiCore$Image *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiCore$Image_init_fields(SuiCore$Image *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Image_fini;
	//fields
    {
	((SuiCore$Image*)self)->_img = 0;
    }
	((SuiCore$Image*)self)->size = (void*)SuiCore$Image$size;
	((SuiCore$Image*)self)->width = (void*)SuiCore$Image$width;
	((SuiCore$Image*)self)->height = (void*)SuiCore$Image$height;
}

// init function

void SuiCore$Image_init(SuiCore$Image *self, void *pOwner){
    Vtable_SuiCore$Image_init(&_vtable_SuiCore$Image);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Image;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Image_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Image * SuiCore$Image_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Image *self = calloc(1, sizeof(SuiCore$Image));
	
    SuiCore$Image_init(self, pOwner);
    return self;
}


// class members
SuiCore$Vec2 SuiCore$Image$size(SuiCore$Image *  self){
	return SuiCore$mkVec2(self->width(self) , self->height(self) ) ; 
}


float  SuiCore$Image$width(SuiCore$Image *  self){
	if (self->_img == 0) {
		return 0; 
	}
	int  w = 0;
	int  h = 0;
	nvgImageSize(SuiCore$Global_getVg() , self->_img, &w, &h) ;
	return (float )w; 
}


float  SuiCore$Image$height(SuiCore$Image *  self){
	if (self->_img == 0) {
		return 0; 
	}
	int  w = 0;
	int  h = 0;
	nvgImageSize(SuiCore$Global_getVg() , self->_img, &w, &h) ;
	return (float )h; 
}



void  SuiCore$Image_writeFloatsAsGrey_toPng(const char *  topath, int  w, int  h, float *  vs){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  b = (b=NULL,urgc_init_var_class((void**)&b, Sgl$Buffer_new(&b) ));
	SuiCore$Image_convertFloatsToGreyBuffer(b, w, h, vs) ;
	stbi_write_png(topath, w, h, 1, b->data, 0) ;
}

void  SuiCore$Image_convertFloatsToGreyBuffer(Sgl$Buffer *  b, int  w, int  h, float *  vs){
	int  cnt = w * h;
	Sgl$Buffer$initSize(b, cnt) ;
	for (int  i = 0; i < cnt; i++) {
		unsigned char  c = vs[i] * 255;
		b->data[i] = c;
	}
}

void  SuiCore$Image_convertFloatsToRgbaBuffer(Sgl$Buffer *  b, int  w, int  h, float *  vs){
	int  cnt = w * h;
	Sgl$Buffer$initSize(b, cnt * 4) ;
	for (int  i = 0; i < cnt; i++) {
		int  idx = i * 4;
		unsigned char  c = vs[i] * 255;
		b->data[idx] = c;
		b->data[idx + 1] = c;
		b->data[idx + 2] = c;
		b->data[idx + 3] = 255;
	}
}

Orc$Map*  SuiCore$getImageMap(Orc$Map **  __outRef__){
	static URGC_VAR_CLEANUP_CLASS Orc$Map*  imageMap = NULL;
	if (!imageMap) {
		URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&imageMap, Orc$Map_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, imageMap) ; 
}

SuiCore$Image*  SuiCore$loadImage(SuiCore$Image **  __outRef__, const char *  path){
	URGC_VAR_CLEANUP_CLASS Orc$Map*  cache = SuiCore$getImageMap((cache = NULL,&cache)) ;
	{
		int  size = cache->size(cache) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, (SuiCore$Image* )cache->get(cache, path) ));
		if (ret) {
			return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
		}
	}
	SuiCore$Canvas *  canvas = SuiCore$Global_getCanvas() ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  acpPath = Orc$String_toActiveCodePage((acpPath = NULL,&acpPath), path) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$Image*  ret = SuiCore$Canvas$createImage((ret = NULL,&ret), canvas, acpPath->str) ;
	cache->put(cache, path, ret) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}



