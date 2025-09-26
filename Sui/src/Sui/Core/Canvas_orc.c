
#include "Canvas_orc.h" 

#include "./Mat2d_orc.h"
#include "./Image_orc.h"
#include "./Color_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$Canvas _vtable_SuiCore$Canvas;

// init meta

void SuiCore$Canvas_initMeta(Vtable_SuiCore$Canvas *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "data", OrcMetaType_void, offsetof(SuiCore$Canvas, data), 0, 0, 1, 1);//void

	orc_metaField_method(&pNext, "init", offsetof(SuiCore$Canvas, init));
}


// vtable init


Vtable_SuiCore$Canvas* Vtable_SuiCore$Canvas_init(Vtable_SuiCore$Canvas* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Canvas;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Canvas_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Canvas";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Canvas_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$Canvas_fini(SuiCore$Canvas *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiCore$Canvas_init_fields(SuiCore$Canvas *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Canvas_fini;
	//fields
    {
	
    }
	((Object*)self)->dtor = (void*)SuiCore$Canvas$dtor;
	((SuiCore$Canvas*)self)->init = (void*)SuiCore$Canvas$init;
}

// init function

void SuiCore$Canvas_init(SuiCore$Canvas *self, void *pOwner){
    Vtable_SuiCore$Canvas_init(&_vtable_SuiCore$Canvas);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Canvas;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Canvas_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Canvas * SuiCore$Canvas_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Canvas *self = calloc(1, sizeof(SuiCore$Canvas));
	
    SuiCore$Canvas_init(self, pOwner);
    return self;
}


// class members

void  SuiCore$Canvas$strokeColorByInt32(SuiCore$Canvas *  self, int  c){
	SuiCore$Canvas$strokeColor(self, SuiCore$colorGetR(c) , SuiCore$colorGetG(c) , SuiCore$colorGetB(c) , SuiCore$colorGetA(c) ) ;
}

void  SuiCore$Canvas$fillColorByInt32(SuiCore$Canvas *  self, int  c){
	SuiCore$Canvas$fillColor(self, SuiCore$colorGetR(c) , SuiCore$colorGetG(c) , SuiCore$colorGetB(c) , SuiCore$colorGetA(c) ) ;
}

SuiCore$Image*  SuiCore$Canvas$createImageRGBA(SuiCore$Image **  __outRef__, SuiCore$Canvas *  self, int  w, int  h, const unsigned char *  imgData){
	URGC_VAR_CLEANUP_CLASS SuiCore$Image*  img = (img=NULL,urgc_init_var_class((void**)&img, SuiCore$Image_new(&img) ));
	img->_img = SuiCore$Canvas$_createImageRGBA(self, w, h, 0, imgData) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, img) ; 
}

SuiCore$Image*  SuiCore$Canvas$createImage(SuiCore$Image **  __outRef__, SuiCore$Canvas *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS SuiCore$Image*  img = (img=NULL,urgc_init_var_class((void**)&img, SuiCore$Image_new(&img) ));
	img->_img = SuiCore$Canvas$_createImage(self, path) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, img) ; 
}



