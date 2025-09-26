
typedef struct tagSgl$Sgl Sgl$Sgl;
typedef struct tagVtable_Sgl$Sgl Vtable_Sgl$Sgl;
typedef struct tagSgl$Test Sgl$Test;
typedef struct tagVtable_Sgl$Test Vtable_Sgl$Test;
typedef struct tagSgl$TestDraw Sgl$TestDraw;
typedef struct tagVtable_Sgl$TestDraw Vtable_Sgl$TestDraw;


#ifndef define_struct___Sgl__Sgl_orc_h__
#define define_struct___Sgl__Sgl_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Sgl_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Sgl_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Sgl_orc_h__
#define __Sgl__Sgl_orc_h__

//include  importHeadCode
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


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Sgl {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Sgl _vtable_Sgl$Sgl;

// class refc:1
struct tagSgl$Sgl {
	Object super; 
	
};
Vtable_Sgl$Sgl* Vtable_Sgl$Sgl_init(Vtable_Sgl$Sgl* pvt);
void Sgl$Sgl_init_fields(Sgl$Sgl *self);
void Sgl$Sgl_init(Sgl$Sgl *self, void *pOwner);
Sgl$Sgl * Sgl$Sgl_new(void *pOwner);
void Sgl$Sgl_fini(Sgl$Sgl *self);


extern int  Sgl$fboTex;

// 虚表
struct tagVtable_Sgl$Test {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Test _vtable_Sgl$Test;

// class refc:0
struct tagSgl$Test {
	Object super; 
	Sgl$Program*  program ;
	Sgl$Vbo*  vbo ;
	Sgl$Vbo*  ibo ;
	Sgl$Vbo*  tbo ;
	Sgl$Vbo*  cbo ;
	Sgl$Tex2d*  tex ;
	Sgl$Fbo*  fbo ;
	void  (*init) (Sgl$Test *  self);
	void  (*draw) (Sgl$Test *  self);
};
Vtable_Sgl$Test* Vtable_Sgl$Test_init(Vtable_Sgl$Test* pvt);
void Sgl$Test_init_fields(Sgl$Test *self);
void Sgl$Test_init(Sgl$Test *self, void *pOwner);
Sgl$Test * Sgl$Test_new(void *pOwner);
void Sgl$Test_fini(Sgl$Test *self);

void  Sgl$Test$ctor(Sgl$Test *  self);
void  Sgl$Test$init(Sgl$Test *  self);
extern void  Sgl$Test$draw(Sgl$Test *  self);


// 虚表
struct tagVtable_Sgl$TestDraw {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$TestDraw _vtable_Sgl$TestDraw;

// class refc:0
struct tagSgl$TestDraw {
	Object super; 
	Sgl$Tex2d*  tex ;
	Sgl$Fbo*  fbo ;
	Sgl$Draw*  drawObj ;
	void  (*init) (Sgl$TestDraw *  self);
	void  (*draw) (Sgl$TestDraw *  self);
};
Vtable_Sgl$TestDraw* Vtable_Sgl$TestDraw_init(Vtable_Sgl$TestDraw* pvt);
void Sgl$TestDraw_init_fields(Sgl$TestDraw *self);
void Sgl$TestDraw_init(Sgl$TestDraw *self, void *pOwner);
Sgl$TestDraw * Sgl$TestDraw_new(void *pOwner);
void Sgl$TestDraw_fini(Sgl$TestDraw *self);

void  Sgl$TestDraw$ctor(Sgl$TestDraw *  self);
void  Sgl$TestDraw$init(Sgl$TestDraw *  self);
extern void  Sgl$TestDraw$draw(Sgl$TestDraw *  self);

void  Sgl$testDrawSgl0();
void  Sgl$testDrawSgl();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
