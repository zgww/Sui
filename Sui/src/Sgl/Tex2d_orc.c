
#include "Tex2d_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../nanovg/stb_image.h"
#include "../Sui/Core/Global_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "./Vao_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Color_orc.h"


// static struct 
typedef struct tagSgl$__Block_60_19 Sgl$__Block_60_19;

typedef struct tagSgl$__Closure_63_27 Sgl$__Closure_63_27;



struct tagSgl$__Block_60_19 {
	GLuint id ;
};





struct tagSgl$__Closure_63_27 {
	void  (*invoke)(Sgl$__Closure_63_27 *  self);
	Vtable_Object *  vtable ;
	Sgl$__Block_60_19*  __var___Block_60_19 ;
};





// static function declaration
static void  __finiBlock___Block_60_19(Sgl$__Block_60_19 *  self);
static void  __fn___Closure_63_27(Sgl$__Closure_63_27 *  self);
static void  __fini___Closure_63_27(Sgl$__Closure_63_27 *  self);
static Sgl$__Closure_63_27*  __make___Closure_63_27(Sgl$__Closure_63_27 **  __outRef__, Sgl$__Block_60_19 *  __var___Block_60_19);



//vtable instance
Vtable_Sgl$Tex2d _vtable_Sgl$Tex2d;

// init meta

void Sgl$Tex2d_initMeta(Vtable_Sgl$Tex2d *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "width", OrcMetaType_int, offsetof(Sgl$Tex2d, width), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "height", OrcMetaType_int, offsetof(Sgl$Tex2d, height), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "format", OrcMetaType_int, offsetof(Sgl$Tex2d, format), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "channelCount", OrcMetaType_int, offsetof(Sgl$Tex2d, channelCount), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Tex2d, path), true, false, 1);

	orc_metaField_method(&pNext, "setWrapClampToEdge", offsetof(Sgl$Tex2d, setWrapClampToEdge));
	orc_metaField_method(&pNext, "setWrapClampToBorder", offsetof(Sgl$Tex2d, setWrapClampToBorder));
	orc_metaField_method(&pNext, "Size", offsetof(Sgl$Tex2d, Size));
	orc_metaField_method(&pNext, "updateParameters", offsetof(Sgl$Tex2d, updateParameters));
	orc_metaField_method(&pNext, "gen", offsetof(Sgl$Tex2d, gen));
	orc_metaField_method(&pNext, "bind", offsetof(Sgl$Tex2d, bind));
	orc_metaField_method(&pNext, "unbind", offsetof(Sgl$Tex2d, unbind));
	orc_metaField_method(&pNext, "active", offsetof(Sgl$Tex2d, active));
	orc_metaField_method(&pNext, "generateMipmap", offsetof(Sgl$Tex2d, generateMipmap));
	orc_metaField_method(&pNext, "image2dRgba", offsetof(Sgl$Tex2d, image2dRgba));
	orc_metaField_method(&pNext, "image2dRgb", offsetof(Sgl$Tex2d, image2dRgb));
	orc_metaField_method(&pNext, "image2dRed8", offsetof(Sgl$Tex2d, image2dRed8));
	orc_metaField_method(&pNext, "initZerosRgb", offsetof(Sgl$Tex2d, initZerosRgb));
	orc_metaField_method(&pNext, "initZerosRed8", offsetof(Sgl$Tex2d, initZerosRed8));
	orc_metaField_method(&pNext, "initZerosRgba", offsetof(Sgl$Tex2d, initZerosRgba));
	orc_metaField_method(&pNext, "initForDepthAttachment", offsetof(Sgl$Tex2d, initForDepthAttachment));
	orc_metaField_method(&pNext, "initForStencilAttachment", offsetof(Sgl$Tex2d, initForStencilAttachment));
	orc_metaField_method(&pNext, "initForDepth32fStencil8Attachment", offsetof(Sgl$Tex2d, initForDepth32fStencil8Attachment));
	orc_metaField_method(&pNext, "initForDepth24Stencil8Attachment", offsetof(Sgl$Tex2d, initForDepth24Stencil8Attachment));
	orc_metaField_method(&pNext, "loadImageByPathCstr", offsetof(Sgl$Tex2d, loadImageByPathCstr));
}


// vtable init


Vtable_Sgl$Tex2d* Vtable_Sgl$Tex2d_init(Vtable_Sgl$Tex2d* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Tex2d;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Tex2d_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Tex2d";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Tex2d_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Tex2d_fini(Sgl$Tex2d *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Tex2d_init_fields(Sgl$Tex2d *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Tex2d_fini;
	//fields
    {
	((Sgl$Tex2d*)self)->wrapS = GL_REPEAT;
	((Sgl$Tex2d*)self)->wrapT = GL_REPEAT;
	((Sgl$Tex2d*)self)->minFilter = GL_LINEAR;
	((Sgl$Tex2d*)self)->magFilter = GL_LINEAR;
	((Sgl$Tex2d*)self)->width = 0;
	((Sgl$Tex2d*)self)->height = 0;
	((Sgl$Tex2d*)self)->format = 4;
	((Sgl$Tex2d*)self)->channelCount = 4;
	urgc_set_field_class(self, (void**)&((Sgl$Tex2d*)self)->path, NULL);
    }
	((Sgl$Tex2d*)self)->setWrapClampToEdge = (void*)Sgl$Tex2d$setWrapClampToEdge;
	((Sgl$Tex2d*)self)->setWrapClampToBorder = (void*)Sgl$Tex2d$setWrapClampToBorder;
	((Object*)self)->ctor = (void*)Sgl$Tex2d$ctor;
	((Object*)self)->dtor = (void*)Sgl$Tex2d$dtor;
	((Sgl$Tex2d*)self)->Size = (void*)Sgl$Tex2d$Size;
	((Sgl$Tex2d*)self)->updateParameters = (void*)Sgl$Tex2d$updateParameters;
	((Sgl$Tex2d*)self)->gen = (void*)Sgl$Tex2d$gen;
	((Sgl$Tex2d*)self)->bind = (void*)Sgl$Tex2d$bind;
	((Sgl$Tex2d*)self)->unbind = (void*)Sgl$Tex2d$unbind;
	((Sgl$Tex2d*)self)->active = (void*)Sgl$Tex2d$active;
	((Sgl$Tex2d*)self)->generateMipmap = (void*)Sgl$Tex2d$generateMipmap;
	((Sgl$Tex2d*)self)->image2dRgba = (void*)Sgl$Tex2d$image2dRgba;
	((Sgl$Tex2d*)self)->image2dRgb = (void*)Sgl$Tex2d$image2dRgb;
	((Sgl$Tex2d*)self)->image2dRed8 = (void*)Sgl$Tex2d$image2dRed8;
	((Sgl$Tex2d*)self)->initZerosRgb = (void*)Sgl$Tex2d$initZerosRgb;
	((Sgl$Tex2d*)self)->initZerosRed8 = (void*)Sgl$Tex2d$initZerosRed8;
	((Sgl$Tex2d*)self)->initZerosRgba = (void*)Sgl$Tex2d$initZerosRgba;
	((Sgl$Tex2d*)self)->initForDepthAttachment = (void*)Sgl$Tex2d$initForDepthAttachment;
	((Sgl$Tex2d*)self)->initForStencilAttachment = (void*)Sgl$Tex2d$initForStencilAttachment;
	((Sgl$Tex2d*)self)->initForDepth32fStencil8Attachment = (void*)Sgl$Tex2d$initForDepth32fStencil8Attachment;
	((Sgl$Tex2d*)self)->initForDepth24Stencil8Attachment = (void*)Sgl$Tex2d$initForDepth24Stencil8Attachment;
	((Sgl$Tex2d*)self)->loadImageByPathCstr = (void*)Sgl$Tex2d$loadImageByPathCstr;
}

// init function

void Sgl$Tex2d_init(Sgl$Tex2d *self, void *pOwner){
    Vtable_Sgl$Tex2d_init(&_vtable_Sgl$Tex2d);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Tex2d;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Tex2d_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Tex2d * Sgl$Tex2d_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Tex2d *self = calloc(1, sizeof(Sgl$Tex2d));
	
    Sgl$Tex2d_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Tex2d$setWrapClampToEdge(Sgl$Tex2d *  self){
	self->wrapS = GL_CLAMP_TO_EDGE;
	self->wrapT = GL_CLAMP_TO_EDGE;
}


void  Sgl$Tex2d$setWrapClampToBorder(Sgl$Tex2d *  self, int  color){
	self->wrapS = GL_CLAMP_TO_BORDER;
	self->wrapT = GL_CLAMP_TO_BORDER;
	self->bind(self) ;
	SuiCore$Rgbaf c = SuiCore$mkRgbafByInt(color) ;
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (float * )&c) ;
}


void  Sgl$Tex2d$ctor(Sgl$Tex2d *  self){
	self->gen(self) ;
	self->updateParameters(self) ;
}


void  Sgl$Tex2d$dtor(Sgl$Tex2d *  self){
	if (self->id) {
		URGC_VAR_CLEANUP Sgl$__Block_60_19*  __var___Block_60_19 = (__var___Block_60_19=NULL,urgc_init_var((void**)&__var___Block_60_19, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_60_19) , __finiBlock___Block_60_19) ));
		__var___Block_60_19->id = self->id;
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP Sgl$__Closure_63_27*  tmpReturn_2 = NULL;
		SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_63_27(&tmpReturn_2, __var___Block_60_19) , 0) ;
	}
}


SuiCore$Vec2 Sgl$Tex2d$Size(Sgl$Tex2d *  self){
	return SuiCore$mkVec2(self->width, self->height) ; 
}


void  Sgl$Tex2d$initZerosRgb(Sgl$Tex2d *  self, int  w, int  h){
	self->bind(self) ;
	self->updateParameters(self) ;
	self->image2dRgb(self, NULL, w, h) ;
}


void  Sgl$Tex2d$initZerosRed8(Sgl$Tex2d *  self, int  w, int  h){
	self->bind(self) ;
	self->updateParameters(self) ;
	self->image2dRed8(self, NULL, w, h) ;
}


void  Sgl$Tex2d$initZerosRgba(Sgl$Tex2d *  self, int  w, int  h){
	self->bind(self) ;
	self->updateParameters(self) ;
	self->image2dRgba(self, NULL, w, h) ;
}


bool  Sgl$Tex2d$loadImageByPathCstr(Sgl$Tex2d *  self, const char *  path){
	int  width = 0;
	int  height = 0;
	int  channel = 0;
	stbi_set_flip_vertically_on_load(true) ;
	unsigned char *  data = stbi_load(path, &width, &height, &channel, 0) ;
	if (data) {
		printf("load image. data:%p,  width:%d, height:%d, ch:%d\n", data, width, height, channel) ;
		if (channel == 4) {
			self->bind(self) ;
			self->updateParameters(self) ;
			self->image2dRgba(self, data, width, height) ;
			self->unbind(self) ;
		}
		else if (channel == 3) {
			self->bind(self) ;
			self->updateParameters(self) ;
			self->image2dRgb(self, data, width, height) ;
			self->unbind(self) ;
		}
		stbi_image_free(data) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Tex2d, path) , Orc$str(&tmpReturn_1, path) ) ;
		return true; 
	}
	printf("\n\t\t加载纹理失败。 path:%s\n\n", path) ;
	return false; 
}



static void  __finiBlock___Block_60_19(Sgl$__Block_60_19 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_63_27(Sgl$__Closure_63_27 *  self){
	Sgl$deleteTexture(self->__var___Block_60_19->id) ;
}

static void  __fini___Closure_63_27(Sgl$__Closure_63_27 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_63_27, __var___Block_60_19) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_63_27*  __make___Closure_63_27(Sgl$__Closure_63_27 **  __outRef__, Sgl$__Block_60_19 *  __var___Block_60_19){
	URGC_VAR_CLEANUP Sgl$__Closure_63_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_63_27) , __fini___Closure_63_27) ));
	self->invoke = __fn___Closure_63_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_63_27, __var___Block_60_19) , __var___Block_60_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

Sgl$Tex2d*  Sgl$mkTex2dByPathCstr(Sgl$Tex2d **  __outRef__, const char *  path){
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$Tex2d_new(&r) ));
	r->loadImageByPathCstr(r, path) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}

SuiCore$Image*  Sgl$loadImageByTex2d(SuiCore$Image **  __outRef__, Sgl$Tex2d *  tex){
	static URGC_VAR_CLEANUP_CLASS Orc$Map*  imageMap = NULL;
	if (!imageMap) {
		URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&imageMap, Orc$Map_new(&tmpNewOwner_1) ) ;
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, Orc$String$addi(Orc$str(&tmpReturn_2, "") , tex->id) ));
	URGC_VAR_CLEANUP_CLASS SuiCore$Image*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, (SuiCore$Image* )imageMap->get(imageMap, key->str) ));
	if (ret) {
		return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
	}
	int  imgId = Sgl$__nvglCreateImageFromTexId(tex->id, tex->width, tex->height, true) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpNewOwner_3 = NULL;
	urgc_set_var_class(&ret, SuiCore$Image_new(&tmpNewOwner_3) ) ;
	ret->_img = imgId;
	imageMap->put(imageMap, key->str, ret) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}



