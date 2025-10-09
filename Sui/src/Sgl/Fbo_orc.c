
#include "Fbo_orc.h" 

#include "./UnitOpengl.h"
#include <stdio.h>
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "./Tex2d_orc.h"


// static struct 
typedef struct tagSgl$__Block_46_19 Sgl$__Block_46_19;

typedef struct tagSgl$__Block_198_19 Sgl$__Block_198_19;

typedef struct tagSgl$__Closure_49_27 Sgl$__Closure_49_27;

typedef struct tagSgl$__Closure_201_27 Sgl$__Closure_201_27;



struct tagSgl$__Block_46_19 {
	GLuint id ;
};





struct tagSgl$__Block_198_19 {
	GLuint id ;
};





struct tagSgl$__Closure_49_27 {
	void  (*invoke)(Sgl$__Closure_49_27 *  self);
	Vtable_Object *  vtable ;
	Sgl$__Block_46_19*  __var___Block_46_19 ;
};





struct tagSgl$__Closure_201_27 {
	void  (*invoke)(Sgl$__Closure_201_27 *  self);
	Vtable_Object *  vtable ;
	Sgl$__Block_198_19*  __var___Block_198_19 ;
};





// static function declaration
static void  __finiBlock___Block_46_19(Sgl$__Block_46_19 *  self);
static void  __finiBlock___Block_198_19(Sgl$__Block_198_19 *  self);
static void  __fn___Closure_49_27(Sgl$__Closure_49_27 *  self);
static void  __fini___Closure_49_27(Sgl$__Closure_49_27 *  self);
static Sgl$__Closure_49_27*  __make___Closure_49_27(Sgl$__Closure_49_27 **  __outRef__, Sgl$__Block_46_19 *  __var___Block_46_19);
static void  __fn___Closure_201_27(Sgl$__Closure_201_27 *  self);
static void  __fini___Closure_201_27(Sgl$__Closure_201_27 *  self);
static Sgl$__Closure_201_27*  __make___Closure_201_27(Sgl$__Closure_201_27 **  __outRef__, Sgl$__Block_198_19 *  __var___Block_198_19);



//vtable instance
Vtable_Sgl$Fbo _vtable_Sgl$Fbo;

// init meta

void Sgl$Fbo_initMeta(Vtable_Sgl$Fbo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "tex2d", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Fbo, tex2d), true, false, 1);
	orc_metaField_class(&pNext, "depthTex2d", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Fbo, depthTex2d), true, false, 1);
	orc_metaField_class(&pNext, "stencilTex2d", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Fbo, stencilTex2d), true, false, 1);
	orc_metaField_class(&pNext, "depthStencilRbo", ((Vtable_Object*)Vtable_Sgl$Rbo_init(0)), offsetof(Sgl$Fbo, depthStencilRbo), true, false, 1);

	orc_metaField_method(&pNext, "getSize", offsetof(Sgl$Fbo, getSize));
	orc_metaField_method(&pNext, "gen", offsetof(Sgl$Fbo, gen));
	orc_metaField_method(&pNext, "bind", offsetof(Sgl$Fbo, bind));
	orc_metaField_method(&pNext, "unbind", offsetof(Sgl$Fbo, unbind));
	orc_metaField_method(&pNext, "isStatusComplete", offsetof(Sgl$Fbo, isStatusComplete));
	orc_metaField_method(&pNext, "checkStatus", offsetof(Sgl$Fbo, checkStatus));
	orc_metaField_method(&pNext, "statusDesc", offsetof(Sgl$Fbo, statusDesc));
	orc_metaField_method(&pNext, "startDraw", offsetof(Sgl$Fbo, startDraw));
	orc_metaField_method(&pNext, "endDraw", offsetof(Sgl$Fbo, endDraw));
	orc_metaField_method(&pNext, "setGlDrawBufferNone", offsetof(Sgl$Fbo, setGlDrawBufferNone));
	orc_metaField_method(&pNext, "setGlReadBufferNone", offsetof(Sgl$Fbo, setGlReadBufferNone));
	orc_metaField_method(&pNext, "setGlDrawBufferDefault", offsetof(Sgl$Fbo, setGlDrawBufferDefault));
	orc_metaField_method(&pNext, "setGlReadBufferDefault", offsetof(Sgl$Fbo, setGlReadBufferDefault));
	orc_metaField_method(&pNext, "attachColorTex2d", offsetof(Sgl$Fbo, attachColorTex2d));
	orc_metaField_method(&pNext, "attachDepthTex2d", offsetof(Sgl$Fbo, attachDepthTex2d));
	orc_metaField_method(&pNext, "attachStencilTex2d", offsetof(Sgl$Fbo, attachStencilTex2d));
	orc_metaField_method(&pNext, "attachRenderBuffer_asDepthStencil", offsetof(Sgl$Fbo, attachRenderBuffer_asDepthStencil));
	orc_metaField_method(&pNext, "_attachColorTex2d", offsetof(Sgl$Fbo, _attachColorTex2d));
	orc_metaField_method(&pNext, "_attachDepthTex2d", offsetof(Sgl$Fbo, _attachDepthTex2d));
	orc_metaField_method(&pNext, "_attachDepthStencilTex2d", offsetof(Sgl$Fbo, _attachDepthStencilTex2d));
	orc_metaField_method(&pNext, "_attachStencilTex2d", offsetof(Sgl$Fbo, _attachStencilTex2d));
	orc_metaField_method(&pNext, "_attachRenderBuffer_asDepthStencil", offsetof(Sgl$Fbo, _attachRenderBuffer_asDepthStencil));
	orc_metaField_method(&pNext, "buildWithColorDepth32fStencil8Texture", offsetof(Sgl$Fbo, buildWithColorDepth32fStencil8Texture));
	orc_metaField_method(&pNext, "buildWithColorDepth24Stencil8Texture", offsetof(Sgl$Fbo, buildWithColorDepth24Stencil8Texture));
	orc_metaField_method(&pNext, "buildWithColorDepthStencilTexture", offsetof(Sgl$Fbo, buildWithColorDepthStencilTexture));
	orc_metaField_method(&pNext, "buildWithColorDepthStencil", offsetof(Sgl$Fbo, buildWithColorDepthStencil));
}


// vtable init


Vtable_Sgl$Fbo* Vtable_Sgl$Fbo_init(Vtable_Sgl$Fbo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Fbo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Fbo_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Fbo";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Fbo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Fbo_fini(Sgl$Fbo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Fbo*)self)->tex2d);
	urgc_fini_field_class(self, (void**)&((Sgl$Fbo*)self)->depthTex2d);
	urgc_fini_field_class(self, (void**)&((Sgl$Fbo*)self)->stencilTex2d);
	urgc_fini_field_class(self, (void**)&((Sgl$Fbo*)self)->depthStencilRbo);

}

// init fields function


void Sgl$Fbo_init_fields(Sgl$Fbo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Fbo_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Fbo*)self)->tex2d, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Fbo*)self)->depthTex2d, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Fbo*)self)->stencilTex2d, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Fbo*)self)->depthStencilRbo, NULL);
    }
	((Object*)self)->ctor = (void*)Sgl$Fbo$ctor;
	((Object*)self)->dtor = (void*)Sgl$Fbo$dtor;
	((Sgl$Fbo*)self)->getSize = (void*)Sgl$Fbo$getSize;
	((Sgl$Fbo*)self)->gen = (void*)Sgl$Fbo$gen;
	((Sgl$Fbo*)self)->bind = (void*)Sgl$Fbo$bind;
	((Sgl$Fbo*)self)->unbind = (void*)Sgl$Fbo$unbind;
	((Sgl$Fbo*)self)->isStatusComplete = (void*)Sgl$Fbo$isStatusComplete;
	((Sgl$Fbo*)self)->checkStatus = (void*)Sgl$Fbo$checkStatus;
	((Sgl$Fbo*)self)->statusDesc = (void*)Sgl$Fbo$statusDesc;
	((Sgl$Fbo*)self)->startDraw = (void*)Sgl$Fbo$startDraw;
	((Sgl$Fbo*)self)->endDraw = (void*)Sgl$Fbo$endDraw;
	((Sgl$Fbo*)self)->setGlDrawBufferNone = (void*)Sgl$Fbo$setGlDrawBufferNone;
	((Sgl$Fbo*)self)->setGlReadBufferNone = (void*)Sgl$Fbo$setGlReadBufferNone;
	((Sgl$Fbo*)self)->setGlDrawBufferDefault = (void*)Sgl$Fbo$setGlDrawBufferDefault;
	((Sgl$Fbo*)self)->setGlReadBufferDefault = (void*)Sgl$Fbo$setGlReadBufferDefault;
	((Sgl$Fbo*)self)->attachColorTex2d = (void*)Sgl$Fbo$attachColorTex2d;
	((Sgl$Fbo*)self)->attachDepthTex2d = (void*)Sgl$Fbo$attachDepthTex2d;
	((Sgl$Fbo*)self)->attachStencilTex2d = (void*)Sgl$Fbo$attachStencilTex2d;
	((Sgl$Fbo*)self)->attachRenderBuffer_asDepthStencil = (void*)Sgl$Fbo$attachRenderBuffer_asDepthStencil;
	((Sgl$Fbo*)self)->_attachColorTex2d = (void*)Sgl$Fbo$_attachColorTex2d;
	((Sgl$Fbo*)self)->_attachDepthTex2d = (void*)Sgl$Fbo$_attachDepthTex2d;
	((Sgl$Fbo*)self)->_attachDepthStencilTex2d = (void*)Sgl$Fbo$_attachDepthStencilTex2d;
	((Sgl$Fbo*)self)->_attachStencilTex2d = (void*)Sgl$Fbo$_attachStencilTex2d;
	((Sgl$Fbo*)self)->_attachRenderBuffer_asDepthStencil = (void*)Sgl$Fbo$_attachRenderBuffer_asDepthStencil;
	((Sgl$Fbo*)self)->buildWithColorDepth32fStencil8Texture = (void*)Sgl$Fbo$buildWithColorDepth32fStencil8Texture;
	((Sgl$Fbo*)self)->buildWithColorDepth24Stencil8Texture = (void*)Sgl$Fbo$buildWithColorDepth24Stencil8Texture;
	((Sgl$Fbo*)self)->buildWithColorDepthStencilTexture = (void*)Sgl$Fbo$buildWithColorDepthStencilTexture;
	((Sgl$Fbo*)self)->buildWithColorDepthStencil = (void*)Sgl$Fbo$buildWithColorDepthStencil;
}

// init function

void Sgl$Fbo_init(Sgl$Fbo *self, void *pOwner){
    Vtable_Sgl$Fbo_init(&_vtable_Sgl$Fbo);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Fbo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Fbo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Fbo * Sgl$Fbo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Fbo *self = calloc(1, sizeof(Sgl$Fbo));
	
    Sgl$Fbo_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Fbo$ctor(Sgl$Fbo *  self){
	self->gen(self) ;
}


void  Sgl$Fbo$dtor(Sgl$Fbo *  self){
	if (self->id) {
		URGC_VAR_CLEANUP Sgl$__Block_46_19*  __var___Block_46_19 = (__var___Block_46_19=NULL,urgc_init_var((void**)&__var___Block_46_19, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_46_19) , __finiBlock___Block_46_19) ));
		__var___Block_46_19->id = self->id;
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP Sgl$__Closure_49_27*  tmpReturn_2 = NULL;
		SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_49_27(&tmpReturn_2, __var___Block_46_19) , 0) ;
	}
}


SuiCore$Vec2 Sgl$Fbo$getSize(Sgl$Fbo *  self){
	if (self->tex2d) {
		return SuiCore$mkVec2(self->tex2d->width, self->tex2d->height) ; 
	}
	if (self->depthTex2d) {
		return SuiCore$mkVec2(self->depthTex2d->width, self->depthTex2d->height) ; 
	}
	return SuiCore$mkVec2(0, 0) ; 
}


void  Sgl$Fbo$attachColorTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d, int  colorAttachmentIndex){
	urgc_set_field_class(self, (void * )offsetof(Sgl$Fbo, tex2d) , tex2d) ;
	self->_attachColorTex2d(self, tex2d, colorAttachmentIndex) ;
}


void  Sgl$Fbo$attachDepthTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d){
	urgc_set_field_class(self, (void * )offsetof(Sgl$Fbo, depthTex2d) , tex2d) ;
	self->_attachDepthTex2d(self, tex2d) ;
}


void  Sgl$Fbo$attachStencilTex2d(Sgl$Fbo *  self, Sgl$Tex2d *  tex2d){
	urgc_set_field_class(self, (void * )offsetof(Sgl$Fbo, stencilTex2d) , tex2d) ;
	self->_attachStencilTex2d(self, tex2d) ;
}


void  Sgl$Fbo$attachRenderBuffer_asDepthStencil(Sgl$Fbo *  self, Sgl$Rbo *  rbo){
	urgc_set_field_class(self, (void * )offsetof(Sgl$Fbo, depthStencilRbo) , rbo) ;
	self->_attachRenderBuffer_asDepthStencil(self, rbo) ;
}


void  Sgl$Fbo$buildWithColorDepth32fStencil8Texture(Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthStencilTex){
	self->bind(self) ;
	if (colorTex) {
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  c = (c=NULL,urgc_init_var_class((void**)&c, Sgl$Tex2d_new(&c) ));
		c->initZerosRgba(c, w, h) ;
		self->attachColorTex2d(self, c, 0) ;
	}
	if (depthStencilTex) {
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  c = (c=NULL,urgc_init_var_class((void**)&c, Sgl$Tex2d_new(&c) ));
		c->initForDepth32fStencil8Attachment(c, w, h) ;
		self->_attachDepthStencilTex2d(self, c) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Fbo, depthTex2d) , c) ;
	}
	printf("FBO status:%d. %s %x\n", self->isStatusComplete(self) , self->statusDesc(self) , self->checkStatus(self) ) ;
	self->unbind(self) ;
}


void  Sgl$Fbo$buildWithColorDepth24Stencil8Texture(Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthStencilTex){
	self->bind(self) ;
	if (colorTex) {
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  c = (c=NULL,urgc_init_var_class((void**)&c, Sgl$Tex2d_new(&c) ));
		c->initZerosRgba(c, w, h) ;
		self->attachColorTex2d(self, c, 0) ;
	}
	if (depthStencilTex) {
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  c = (c=NULL,urgc_init_var_class((void**)&c, Sgl$Tex2d_new(&c) ));
		c->initForDepth24Stencil8Attachment(c, w, h) ;
		self->_attachDepthStencilTex2d(self, c) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Fbo, depthTex2d) , c) ;
	}
	printf("FBO status:%d. %s %x\n", self->isStatusComplete(self) , self->statusDesc(self) , self->checkStatus(self) ) ;
	self->unbind(self) ;
}


void  Sgl$Fbo$buildWithColorDepthStencilTexture(Sgl$Fbo *  self, int  w, int  h, bool  colorTex, bool  depthTex, bool  stencilTex){
	self->bind(self) ;
	if (colorTex) {
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  c = (c=NULL,urgc_init_var_class((void**)&c, Sgl$Tex2d_new(&c) ));
		c->initZerosRgba(c, w, h) ;
		self->attachColorTex2d(self, c, 0) ;
	}
	if (depthTex) {
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  c = (c=NULL,urgc_init_var_class((void**)&c, Sgl$Tex2d_new(&c) ));
		c->setWrapClampToEdge(c) ;
		c->updateParameters(c) ;
		c->initForDepthAttachment(c, w, h) ;
		self->attachDepthTex2d(self, c) ;
	}
	if (stencilTex) {
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  c = (c=NULL,urgc_init_var_class((void**)&c, Sgl$Tex2d_new(&c) ));
		c->initForStencilAttachment(c, w, h) ;
		self->attachStencilTex2d(self, c) ;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Fbo, stencilTex2d) , c) ;
	}
	printf("FBO status:%d. %s %x\n", self->isStatusComplete(self) , self->statusDesc(self) , self->checkStatus(self) ) ;
	self->unbind(self) ;
}


void  Sgl$Fbo$buildWithColorDepthStencil(Sgl$Fbo *  self, int  w, int  h){
	self->bind(self) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  colorTex = (colorTex=NULL,urgc_init_var_class((void**)&colorTex, Sgl$Tex2d_new(&colorTex) ));
	colorTex->initZerosRgba(colorTex, w, h) ;
	self->attachColorTex2d(self, colorTex, 0) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Rbo*  rbo = (rbo=NULL,urgc_init_var_class((void**)&rbo, Sgl$Rbo_new(&rbo) ));
	rbo->storageAs_DEPTH24_STENCIL8(rbo, w, h) ;
	self->attachRenderBuffer_asDepthStencil(self, rbo) ;
	printf("FBO status:%d, %s\n", self->isStatusComplete(self) , self->statusDesc(self) ) ;
	self->unbind(self) ;
}




//vtable instance
Vtable_Sgl$Rbo _vtable_Sgl$Rbo;

// init meta

void Sgl$Rbo_initMeta(Vtable_Sgl$Rbo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "gen", offsetof(Sgl$Rbo, gen));
	orc_metaField_method(&pNext, "bind", offsetof(Sgl$Rbo, bind));
	orc_metaField_method(&pNext, "unbind", offsetof(Sgl$Rbo, unbind));
	orc_metaField_method(&pNext, "storageAs_DEPTH24_STENCIL8", offsetof(Sgl$Rbo, storageAs_DEPTH24_STENCIL8));
}


// vtable init


Vtable_Sgl$Rbo* Vtable_Sgl$Rbo_init(Vtable_Sgl$Rbo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Rbo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Rbo_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Rbo";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Rbo_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Sgl$Rbo_fini(Sgl$Rbo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void Sgl$Rbo_init_fields(Sgl$Rbo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Rbo_fini;
	//fields
    {
	
    }
	((Object*)self)->ctor = (void*)Sgl$Rbo$ctor;
	((Object*)self)->dtor = (void*)Sgl$Rbo$dtor;
	((Sgl$Rbo*)self)->gen = (void*)Sgl$Rbo$gen;
	((Sgl$Rbo*)self)->bind = (void*)Sgl$Rbo$bind;
	((Sgl$Rbo*)self)->unbind = (void*)Sgl$Rbo$unbind;
	((Sgl$Rbo*)self)->storageAs_DEPTH24_STENCIL8 = (void*)Sgl$Rbo$storageAs_DEPTH24_STENCIL8;
}

// init function

void Sgl$Rbo_init(Sgl$Rbo *self, void *pOwner){
    Vtable_Sgl$Rbo_init(&_vtable_Sgl$Rbo);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Rbo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Rbo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Rbo * Sgl$Rbo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Rbo *self = calloc(1, sizeof(Sgl$Rbo));
	
    Sgl$Rbo_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Rbo$ctor(Sgl$Rbo *  self){
	self->gen(self) ;
}


void  Sgl$Rbo$dtor(Sgl$Rbo *  self){
	if (self->id) {
		URGC_VAR_CLEANUP Sgl$__Block_198_19*  __var___Block_198_19 = (__var___Block_198_19=NULL,urgc_init_var((void**)&__var___Block_198_19, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_198_19) , __finiBlock___Block_198_19) ));
		__var___Block_198_19->id = self->id;
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP Sgl$__Closure_201_27*  tmpReturn_2 = NULL;
		SuiCore$mkTimerTimeout(&tmpReturn_1, __make___Closure_201_27(&tmpReturn_2, __var___Block_198_19) , 0) ;
	}
}



static void  __finiBlock___Block_46_19(Sgl$__Block_46_19 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_198_19(Sgl$__Block_198_19 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_49_27(Sgl$__Closure_49_27 *  self){
	Sgl$deleteFrameBuffer(self->__var___Block_46_19->id) ;
}

static void  __fini___Closure_49_27(Sgl$__Closure_49_27 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_49_27, __var___Block_46_19) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_49_27*  __make___Closure_49_27(Sgl$__Closure_49_27 **  __outRef__, Sgl$__Block_46_19 *  __var___Block_46_19){
	URGC_VAR_CLEANUP Sgl$__Closure_49_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_49_27) , __fini___Closure_49_27) ));
	self->invoke = __fn___Closure_49_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_49_27, __var___Block_46_19) , __var___Block_46_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_201_27(Sgl$__Closure_201_27 *  self){
	Sgl$deleteRenderBuffer(self->__var___Block_198_19->id) ;
}

static void  __fini___Closure_201_27(Sgl$__Closure_201_27 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_201_27, __var___Block_198_19) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_201_27*  __make___Closure_201_27(Sgl$__Closure_201_27 **  __outRef__, Sgl$__Block_198_19 *  __var___Block_198_19){
	URGC_VAR_CLEANUP Sgl$__Closure_201_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_201_27) , __fini___Closure_201_27) ));
	self->invoke = __fn___Closure_201_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_201_27, __var___Block_198_19) , __var___Block_198_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



