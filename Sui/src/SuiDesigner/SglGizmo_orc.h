
typedef struct tagSuiDesigner$SglGizmo SuiDesigner$SglGizmo;
typedef struct tagVtable_SuiDesigner$SglGizmo Vtable_SuiDesigner$SglGizmo;


#ifndef define_struct___SuiDesigner__SglGizmo_orc_h__
#define define_struct___SuiDesigner__SglGizmo_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__SglGizmo_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__SglGizmo_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__SglGizmo_orc_h__
#define __SuiDesigner__SglGizmo_orc_h__

//include  importHeadCode
#include "../Orc/Math_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryRect_orc.h"
#include "../Sgl/GeometryLine_orc.h"
#include "../Sgl/GeometryCone_orc.h"
#include "../Sgl/GeometryTorus_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Ray_orc.h"
#include "../Sgl/Raycaster_orc.h"
#include "../Sgl/Billboard_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$SglGizmo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SglGizmo _vtable_SuiDesigner$SglGizmo;

// class refc:0
struct tagSuiDesigner$SglGizmo {
	Object super; 
	Sgl$Scene*  scene ;
	Sgl$PerspectiveCamera*  camera ;
	Sgl$Raycaster*  raycaster ;
	SuiCore$Vec2 (**getNdcPos)(void *  self, SuiCore$Vec2 clientPos);
	void  (*dispatchMouseEvent) (SuiDesigner$SglGizmo *  self, SuiCore$MouseEvent *  e);
	void  (*hitTest) (SuiDesigner$SglGizmo *  self, SuiCore$MouseEvent *  e);
	void  (*onEvent) (SuiDesigner$SglGizmo *  self, SuiCore$Event *  e);
	void  (*draw) (SuiDesigner$SglGizmo *  self, Sgl$DrawCtx *  ctx);
};
Vtable_SuiDesigner$SglGizmo* Vtable_SuiDesigner$SglGizmo_init(Vtable_SuiDesigner$SglGizmo* pvt);
void SuiDesigner$SglGizmo_init_fields(SuiDesigner$SglGizmo *self);
void SuiDesigner$SglGizmo_init(SuiDesigner$SglGizmo *self, void *pOwner);
SuiDesigner$SglGizmo * SuiDesigner$SglGizmo_new(void *pOwner);
void SuiDesigner$SglGizmo_fini(SuiDesigner$SglGizmo *self);

void  SuiDesigner$SglGizmo$dispatchMouseEvent(SuiDesigner$SglGizmo *  self, SuiCore$MouseEvent *  e);
void  SuiDesigner$SglGizmo$hitTest(SuiDesigner$SglGizmo *  self, SuiCore$MouseEvent *  e);
void  SuiDesigner$SglGizmo$onEvent(SuiDesigner$SglGizmo *  self, SuiCore$Event *  e);
void  SuiDesigner$SglGizmo$draw(SuiDesigner$SglGizmo *  self, Sgl$DrawCtx *  ctx);

Sgl$Obj3d*  SuiDesigner$SglGizmo_translate(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, Sgl$Obj3d*  target);
Sgl$Obj3d*  SuiDesigner$SglGizmo_rotate(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, Sgl$Obj3d*  target);
Sgl$Obj3d*  SuiDesigner$SglGizmo_scale(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, Sgl$Obj3d*  target);
Sgl$Obj3d*  SuiDesigner$SglGizmo_image(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, const char *  imgPath);
Sgl$Obj3d*  SuiDesigner$SglGizmo_button(Sgl$Obj3d **  __outRef__, SuiCore$Node *  o, long long  key, const char *  label, void  (**onClick)(void *  self));
Sgl$Obj3d*  SuiDesigner$SglGizmo_text(Sgl$Obj3d **  __outRef__, Sgl$Obj3d *  o, long long  key, const char *  label);
Sgl$Mesh*  SuiDesigner$SglGizmo_box(Sgl$Mesh **  __outRef__, Sgl$Obj3d *  o, long long  key, float  size, SuiCore$Vec3 pos, int  color);
Sgl$Mesh*  SuiDesigner$SglGizmo_cone(Sgl$Mesh **  __outRef__, Sgl$Obj3d *  o, long long  key, float  size, SuiCore$Vec3 pos, int  color);
Sgl$Mesh*  SuiDesigner$SglGizmo_torus(Sgl$Mesh **  __outRef__, Sgl$Obj3d *  o, long long  key, float  size, SuiCore$Vec3 pos, int  color);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
