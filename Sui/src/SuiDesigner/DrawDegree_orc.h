
typedef struct tagSuiDesigner$DrawDegreeItem SuiDesigner$DrawDegreeItem;
typedef struct tagVtable_SuiDesigner$DrawDegreeItem Vtable_SuiDesigner$DrawDegreeItem;
typedef struct tagSuiDesigner$DrawDegree SuiDesigner$DrawDegree;
typedef struct tagVtable_SuiDesigner$DrawDegree Vtable_SuiDesigner$DrawDegree;


#ifndef define_struct___SuiDesigner__DrawDegree_orc_h__
#define define_struct___SuiDesigner__DrawDegree_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__DrawDegree_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <math.h>
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__DrawDegree_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__DrawDegree_orc_h__
#define __SuiDesigner__DrawDegree_orc_h__

//include  importHeadCode
#include "../Orc/Math_orc.h"
#include "../Orc/List_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Mat2d_orc.h"
#include "../Sui/Core/Vec3_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$DrawDegreeItem {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$DrawDegreeItem _vtable_SuiDesigner$DrawDegreeItem;

// class refc:1
struct tagSuiDesigner$DrawDegreeItem {
	Object super; 
	float  value ;
	float  degree ;
};
Vtable_SuiDesigner$DrawDegreeItem* Vtable_SuiDesigner$DrawDegreeItem_init(Vtable_SuiDesigner$DrawDegreeItem* pvt);
void SuiDesigner$DrawDegreeItem_init_fields(SuiDesigner$DrawDegreeItem *self);
void SuiDesigner$DrawDegreeItem_init(SuiDesigner$DrawDegreeItem *self, void *pOwner);
SuiDesigner$DrawDegreeItem * SuiDesigner$DrawDegreeItem_new(void *pOwner);
void SuiDesigner$DrawDegreeItem_fini(SuiDesigner$DrawDegreeItem *self);



// 虚表
struct tagVtable_SuiDesigner$DrawDegree {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$DrawDegree _vtable_SuiDesigner$DrawDegree;

// class refc:0
struct tagSuiDesigner$DrawDegree {
	Object super; 
	Orc$List*  options ;
	Orc$List*  levelOptions ;
	float  curScale ;
	SuiDesigner$DrawDegreeItem*  curOption ;
	void  (*genLevels) (SuiDesigner$DrawDegree *  self, int  count);
	SuiDesigner$DrawDegreeItem*  (*findAndReturnOffset) (SuiDesigner$DrawDegreeItem **  __outRef__, SuiDesigner$DrawDegree *  self, float  scale, int  offset);
	SuiDesigner$DrawDegreeItem*  (*findAndUpdateCurOption) (SuiDesigner$DrawDegreeItem **  __outRef__, SuiDesigner$DrawDegree *  self, float  scale);
	void  (*setScale) (SuiDesigner$DrawDegree *  self, float  scale);
	void  (*draw) (SuiDesigner$DrawDegree *  self, SuiCore$Canvas *  canvas, SuiCore$Mat2d sceneMat2d, float  w, float  h, float  mouseX, float  mouseY);
};
Vtable_SuiDesigner$DrawDegree* Vtable_SuiDesigner$DrawDegree_init(Vtable_SuiDesigner$DrawDegree* pvt);
void SuiDesigner$DrawDegree_init_fields(SuiDesigner$DrawDegree *self);
void SuiDesigner$DrawDegree_init(SuiDesigner$DrawDegree *self, void *pOwner);
SuiDesigner$DrawDegree * SuiDesigner$DrawDegree_new(void *pOwner);
void SuiDesigner$DrawDegree_fini(SuiDesigner$DrawDegree *self);

void  SuiDesigner$DrawDegree$ctor(SuiDesigner$DrawDegree *  self);
void  SuiDesigner$DrawDegree$genLevels(SuiDesigner$DrawDegree *  self, int  count);
SuiDesigner$DrawDegreeItem*  SuiDesigner$DrawDegree$findAndReturnOffset(SuiDesigner$DrawDegreeItem **  __outRef__, SuiDesigner$DrawDegree *  self, float  scale, int  offset);
SuiDesigner$DrawDegreeItem*  SuiDesigner$DrawDegree$findAndUpdateCurOption(SuiDesigner$DrawDegreeItem **  __outRef__, SuiDesigner$DrawDegree *  self, float  scale);
void  SuiDesigner$DrawDegree$setScale(SuiDesigner$DrawDegree *  self, float  scale);
void  SuiDesigner$DrawDegree$draw(SuiDesigner$DrawDegree *  self, SuiCore$Canvas *  canvas, SuiCore$Mat2d sceneMat2d, float  w, float  h, float  mouseX, float  mouseY);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
