
typedef struct tagSgl$DepthFloatPixlesReader Sgl$DepthFloatPixlesReader;
typedef struct tagVtable_Sgl$DepthFloatPixlesReader Vtable_Sgl$DepthFloatPixlesReader;
typedef struct tagSgl$RgbaPixelsReader Sgl$RgbaPixelsReader;
typedef struct tagVtable_Sgl$RgbaPixelsReader Vtable_Sgl$RgbaPixelsReader;


#ifndef define_struct___Sgl__PixelsReader_orc_h__
#define define_struct___Sgl__PixelsReader_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__PixelsReader_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__PixelsReader_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__PixelsReader_orc_h__
#define __Sgl__PixelsReader_orc_h__

//include  importHeadCode
#include "./Buffer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$DepthFloatPixlesReader {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$DepthFloatPixlesReader _vtable_Sgl$DepthFloatPixlesReader;

// class refc:0
struct tagSgl$DepthFloatPixlesReader {
	Object super; 
	Sgl$Buffer*  buffer ;
	int  x ;
	int  y ;
	int  w ;
	int  h ;
	float *  (*read) (Sgl$DepthFloatPixlesReader *  self, int  x, int  y, int  w, int  h);
};
Vtable_Sgl$DepthFloatPixlesReader* Vtable_Sgl$DepthFloatPixlesReader_init(Vtable_Sgl$DepthFloatPixlesReader* pvt);
void Sgl$DepthFloatPixlesReader_init_fields(Sgl$DepthFloatPixlesReader *self);
void Sgl$DepthFloatPixlesReader_init(Sgl$DepthFloatPixlesReader *self, void *pOwner);
Sgl$DepthFloatPixlesReader * Sgl$DepthFloatPixlesReader_new(void *pOwner);
void Sgl$DepthFloatPixlesReader_fini(Sgl$DepthFloatPixlesReader *self);

float *  Sgl$DepthFloatPixlesReader$read(Sgl$DepthFloatPixlesReader *  self, int  x, int  y, int  w, int  h);


// 虚表
struct tagVtable_Sgl$RgbaPixelsReader {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$RgbaPixelsReader _vtable_Sgl$RgbaPixelsReader;

// class refc:0
struct tagSgl$RgbaPixelsReader {
	Object super; 
	Sgl$Buffer*  buffer ;
	int  x ;
	int  y ;
	int  w ;
	int  h ;
	unsigned char *  (*readFromColorAttachment) (Sgl$RgbaPixelsReader *  self, int  attachmentIndex, int  x, int  y, int  w, int  h);
	unsigned char *  (*read) (Sgl$RgbaPixelsReader *  self, int  x, int  y, int  w, int  h);
};
Vtable_Sgl$RgbaPixelsReader* Vtable_Sgl$RgbaPixelsReader_init(Vtable_Sgl$RgbaPixelsReader* pvt);
void Sgl$RgbaPixelsReader_init_fields(Sgl$RgbaPixelsReader *self);
void Sgl$RgbaPixelsReader_init(Sgl$RgbaPixelsReader *self, void *pOwner);
Sgl$RgbaPixelsReader * Sgl$RgbaPixelsReader_new(void *pOwner);
void Sgl$RgbaPixelsReader_fini(Sgl$RgbaPixelsReader *self);

unsigned char *  Sgl$RgbaPixelsReader$readFromColorAttachment(Sgl$RgbaPixelsReader *  self, int  attachmentIndex, int  x, int  y, int  w, int  h);
unsigned char *  Sgl$RgbaPixelsReader$read(Sgl$RgbaPixelsReader *  self, int  x, int  y, int  w, int  h);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
