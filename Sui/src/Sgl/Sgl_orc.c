
#include "Sgl_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "./Vbo_orc.h"
#include "./Vao_orc.h"
#include "./Buffer_orc.h"
#include "./Program_orc.h"
#include "./Draw_orc.h"
#include "./Tex2d_orc.h"
#include "./Material_orc.h"
#include "./Geometry_orc.h"
#include "../Orc/String_orc.h"
#include "../Json/Json_orc.h"
#include "./Fbo_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$Sgl _vtable_Sgl$Sgl;

// init meta

void Sgl$Sgl_initMeta(Vtable_Sgl$Sgl *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_Sgl$Sgl* Vtable_Sgl$Sgl_init(Vtable_Sgl$Sgl* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Sgl;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Sgl_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Sgl";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Sgl_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void Sgl$Sgl_fini(Sgl$Sgl *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Sgl_init_fields(Sgl$Sgl *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Sgl_fini;
	//fields
    {
	
    }
	
}

// init function

void Sgl$Sgl_init(Sgl$Sgl *self, void *pOwner){
    Vtable_Sgl$Sgl_init(&_vtable_Sgl$Sgl);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Sgl;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Sgl_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Sgl * Sgl$Sgl_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Sgl *self = calloc(1, sizeof(Sgl$Sgl));
	
    Sgl$Sgl_init(self, pOwner);
    return self;
}


// class members

int  Sgl$fboTex;

//vtable instance
Vtable_Sgl$Test _vtable_Sgl$Test;

// init meta

void Sgl$Test_initMeta(Vtable_Sgl$Test *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "program", ((Vtable_Object*)Vtable_Sgl$Program_init(0)), offsetof(Sgl$Test, program), true, false, 1);
	orc_metaField_class(&pNext, "vbo", ((Vtable_Object*)Vtable_Sgl$Vbo_init(0)), offsetof(Sgl$Test, vbo), true, false, 1);
	orc_metaField_class(&pNext, "ibo", ((Vtable_Object*)Vtable_Sgl$Vbo_init(0)), offsetof(Sgl$Test, ibo), true, false, 1);
	orc_metaField_class(&pNext, "tbo", ((Vtable_Object*)Vtable_Sgl$Vbo_init(0)), offsetof(Sgl$Test, tbo), true, false, 1);
	orc_metaField_class(&pNext, "cbo", ((Vtable_Object*)Vtable_Sgl$Vbo_init(0)), offsetof(Sgl$Test, cbo), true, false, 1);
	orc_metaField_class(&pNext, "tex", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$Test, tex), true, false, 1);
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(Sgl$Test, fbo), true, false, 1);

	orc_metaField_method(&pNext, "init", offsetof(Sgl$Test, init));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$Test, draw));
}


// vtable init


Vtable_Sgl$Test* Vtable_Sgl$Test_init(Vtable_Sgl$Test* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Test;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Test_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Test";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Test_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Test_fini(Sgl$Test *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Test_init_fields(Sgl$Test *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Test_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$Test*)self)->program, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Test*)self)->vbo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Test*)self)->ibo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Test*)self)->tbo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Test*)self)->cbo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Test*)self)->tex, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$Test*)self)->fbo, NULL);
    }
	((Object*)self)->ctor = (void*)Sgl$Test$ctor;
	((Sgl$Test*)self)->init = (void*)Sgl$Test$init;
	((Sgl$Test*)self)->draw = (void*)Sgl$Test$draw;
}

// init function

void Sgl$Test_init(Sgl$Test *self, void *pOwner){
    Vtable_Sgl$Test_init(&_vtable_Sgl$Test);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Test;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Test_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Test * Sgl$Test_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Test *self = calloc(1, sizeof(Sgl$Test));
	
    Sgl$Test_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Test$ctor(Sgl$Test *  self){
	printf("init Test") ;
	self->init(self) ;
}


void  Sgl$Test$init(Sgl$Test *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Program*  p = (p=NULL,urgc_init_var_class((void**)&p, Sgl$Program_new(&p) ));
	urgc_set_field_class(self, (void * )offsetof(Sgl$Test, program) , p) ;
	bool  ok = p->compileByPathCstr(p, "./asset/a.vs", "./asset/a.fs") ;
	printf("compile program :%d\n", ok) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  triJo = Json$Json_parseByPathCstr((triJo = NULL,&triJo), "./asset/Triangle.json") ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  verBuf = Sgl$mkBufferFloatByJsonArray((verBuf = NULL,&verBuf), triJo->get(&tmpReturn_1, triJo, "position") ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  indicesBuf = Sgl$mkBufferIntByJsonArray((indicesBuf = NULL,&indicesBuf), triJo->get(&tmpReturn_2, triJo, "face") ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  cBuf = Sgl$mkBufferFloatByJsonArray((cBuf = NULL,&cBuf), triJo->get(&tmpReturn_3, triJo, "color") ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_4 = NULL;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tBuf = Sgl$mkBufferFloatByJsonArray((tBuf = NULL,&tBuf), triJo->get(&tmpReturn_4, triJo, "texCoord") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
	printf("ver:%s\n\nindices:%s\ntexCoord:%s\n", Sgl$Buffer$toFloatString(&tmpReturn_5, verBuf) ->str, Sgl$Buffer$toIntString(&tmpReturn_6, indicesBuf) ->str, Sgl$Buffer$toFloatString(&tmpReturn_7, tBuf) ->str) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
	vbo->arrayBuffer(vbo, verBuf) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Test, vbo) , vbo) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  tmpNewOwner_8 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Test, cbo) , Sgl$Vbo_new(&tmpNewOwner_8) ) ;
	self->cbo->arrayBuffer(self->cbo, cBuf) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  tmpNewOwner_9 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Test, tbo) , Sgl$Vbo_new(&tmpNewOwner_9) ) ;
	self->tbo->arrayBuffer(self->tbo, tBuf) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  ibo = (ibo=NULL,urgc_init_var_class((void**)&ibo, Sgl$Vbo_new(&ibo) ));
	ibo->elementBuffer(ibo, indicesBuf) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Test, ibo) , ibo) ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
		urgc_set_field_class(self, (void * )offsetof(Sgl$Test, tex) , tex) ;
		bool  ok = tex->loadImageByPathCstr(tex, "./asset/SpongeBob.png") ;
		printf("load tex :%d\n", ok) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_10 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Test, fbo) , Sgl$Fbo_new(&tmpNewOwner_10) ) ;
	self->fbo->bind(self->fbo) ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  colorTex = (colorTex=NULL,urgc_init_var_class((void**)&colorTex, Sgl$Tex2d_new(&colorTex) ));
		colorTex->initZerosRgba(colorTex, 800, 600) ;
		self->fbo->attachColorTex2d(self->fbo, colorTex, 0) ;
		Sgl$fboTex = colorTex->id;
		URGC_VAR_CLEANUP_CLASS Sgl$Rbo*  rbo = (rbo=NULL,urgc_init_var_class((void**)&rbo, Sgl$Rbo_new(&rbo) ));
		rbo->storageAs_DEPTH24_STENCIL8(rbo, 800, 600) ;
		self->fbo->attachRenderBuffer_asDepthStencil(self->fbo, rbo) ;
		printf("FBO status:%d\n", self->fbo->isStatusComplete(self->fbo) ) ;
	}
	self->fbo->unbind(self->fbo) ;
}




//vtable instance
Vtable_Sgl$TestDraw _vtable_Sgl$TestDraw;

// init meta

void Sgl$TestDraw_initMeta(Vtable_Sgl$TestDraw *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "tex", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$TestDraw, tex), true, false, 1);
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(Sgl$TestDraw, fbo), true, false, 1);
	orc_metaField_class(&pNext, "drawObj", ((Vtable_Object*)Vtable_Sgl$Draw_init(0)), offsetof(Sgl$TestDraw, drawObj), true, false, 1);

	orc_metaField_method(&pNext, "init", offsetof(Sgl$TestDraw, init));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$TestDraw, draw));
}


// vtable init


Vtable_Sgl$TestDraw* Vtable_Sgl$TestDraw_init(Vtable_Sgl$TestDraw* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$TestDraw;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$TestDraw_new;
    ((Vtable_Object*)pvt)->className = "Sgl$TestDraw";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$TestDraw_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$TestDraw_fini(Sgl$TestDraw *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$TestDraw_init_fields(Sgl$TestDraw *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$TestDraw_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$TestDraw*)self)->tex, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$TestDraw*)self)->fbo, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Draw*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$TestDraw*)self)->drawObj, Sgl$Draw_new(&tmpNewOwner_1) );
    }
	((Object*)self)->ctor = (void*)Sgl$TestDraw$ctor;
	((Sgl$TestDraw*)self)->init = (void*)Sgl$TestDraw$init;
	((Sgl$TestDraw*)self)->draw = (void*)Sgl$TestDraw$draw;
}

// init function

void Sgl$TestDraw_init(Sgl$TestDraw *self, void *pOwner){
    Vtable_Sgl$TestDraw_init(&_vtable_Sgl$TestDraw);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$TestDraw;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$TestDraw_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$TestDraw * Sgl$TestDraw_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$TestDraw *self = calloc(1, sizeof(Sgl$TestDraw));
	
    Sgl$TestDraw_init(self, pOwner);
    return self;
}


// class members
void  Sgl$TestDraw$ctor(Sgl$TestDraw *  self){
	printf("init Test") ;
}


void  Sgl$TestDraw$init(Sgl$TestDraw *  self){
	{
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
		urgc_set_field_class(self, (void * )offsetof(Sgl$TestDraw, tex) , tex) ;
		bool  ok = tex->loadImageByPathCstr(tex, "./asset/SpongeBob.png") ;
		printf("load tex :%d\n", ok) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Sgl$ObjLoader*  loader = (loader=NULL,urgc_init_var_class((void**)&loader, Sgl$ObjLoader_new(&loader) ));
		loader->load(loader, "../assimp/test/models/OBJ/spider.obj") ;
		URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpReturn_1 = NULL;
		urgc_set_field_class(self->drawObj, (void * )offsetof(Sgl$Draw, geometry) , loader->buildGeometry(&tmpReturn_1, loader) ) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
	{
		Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_2) ;
		
	
		o->buildByShaderPathCstr(o, "../asset/a.vs", "../asset/a.fs") ;
		urgc_set_field_class(self->drawObj, (void * )offsetof(Sgl$Draw, material) , o) ;
		o->setUniformTex2d(o, "tex", self->tex) ;
		Sgl$Mat$scale(&o->model, 0.02, 0.02, 0.02) ;
		Sgl$Mat$lookAtFake(&o->view, SuiCore$mkVec3(10, 10, 10) , SuiCore$mkVec3(0, 0, 0) , SuiCore$mkVec3(0, 1, 0) ) ;
		Sgl$Mat$perspective(&o->projection, 45 / 180.0 * 3.1415926, 1.0, 0.1, 1000) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$TestDraw, fbo) , Sgl$Fbo_new(&tmpNewOwner_3) ) ;
	self->fbo->buildWithColorDepthStencil(self->fbo, 800, 600) ;
	Sgl$fboTex = self->fbo->tex2d->id;
}



void  Sgl$testDrawSgl0(){
	static URGC_VAR_CLEANUP_CLASS Sgl$Test*  t = NULL;
	if (t == NULL) {
		URGC_VAR_CLEANUP_CLASS Sgl$Test*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&t, Sgl$Test_new(&tmpNewOwner_1) ) ;
	}
	t->draw(t) ;
}

void  Sgl$testDrawSgl(){
	static URGC_VAR_CLEANUP_CLASS Sgl$TestDraw*  t = NULL;
}



