
typedef struct tagSgl$UniformInfo Sgl$UniformInfo;
typedef struct tagVtable_Sgl$UniformInfo Vtable_Sgl$UniformInfo;
typedef struct tagSgl$Material Sgl$Material;
typedef struct tagVtable_Sgl$Material Vtable_Sgl$Material;
typedef struct tagSgl$MaterialInsp Sgl$MaterialInsp;
typedef struct tagVtable_Sgl$MaterialInsp Vtable_Sgl$MaterialInsp;
typedef struct tagSgl$UniformMeta Sgl$UniformMeta;
typedef struct tagVtable_Sgl$UniformMeta Vtable_Sgl$UniformMeta;
typedef struct tagSgl$ShaderMeta Sgl$ShaderMeta;
typedef struct tagVtable_Sgl$ShaderMeta Vtable_Sgl$ShaderMeta;
typedef struct tagSgl$MaterialPreviewView Sgl$MaterialPreviewView;
typedef struct tagVtable_Sgl$MaterialPreviewView Vtable_Sgl$MaterialPreviewView;


#ifndef define_struct___Sgl__Material_orc_h__
#define define_struct___Sgl__Material_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Material_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Material_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Material_orc_h__
#define __Sgl__Material_orc_h__

//include  importHeadCode
#include "./Mat_orc.h"
#include "./Program_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Math_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Focus_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Dialog/FileDialog_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/View/ColorPicker_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "./Tex2d_orc.h"
#include "./Fbo_orc.h"
#include "./Draw_orc.h"
#include "./Geometry_orc.h"
#include "./Buffer_orc.h"
#include "./Mat_orc.h"
#define INCLUDE_ONLY_TYPE
#include "../SuiDesigner/Insp_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$UniformInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$UniformInfo _vtable_Sgl$UniformInfo;

// class refc:0
struct tagSgl$UniformInfo {
	Object super; 
	Orc$String*  key ;
	int  kind ;
	int  count ;
	Sgl$Mat mat ;
	int  intValues[16] ;
	float  floatValues[16] ;
	int  texIndex ;
	Sgl$Tex2d*  tex ;
	Orc$String*  texPath ;
	Sgl$MatArray*  matArray ;
	void  (*inspAsValue) (Sgl$UniformInfo *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o, Sgl$Material *  matl);
	void  (*fromJson) (Sgl$UniformInfo *  self, Json$Json *  jo);
	void  (*toJson) (Sgl$UniformInfo *  self, Json$Json *  jo);
	SuiCore$Rgba (*getColor) (Sgl$UniformInfo *  self);
	bool  (*updateUniform) (Sgl$UniformInfo *  self, Sgl$Program *  program);
};
Vtable_Sgl$UniformInfo* Vtable_Sgl$UniformInfo_init(Vtable_Sgl$UniformInfo* pvt);
void Sgl$UniformInfo_init_fields(Sgl$UniformInfo *self);
void Sgl$UniformInfo_init(Sgl$UniformInfo *self, void *pOwner);
Sgl$UniformInfo * Sgl$UniformInfo_new(void *pOwner);
void Sgl$UniformInfo_fini(Sgl$UniformInfo *self);

void  Sgl$UniformInfo$inspAsValue(Sgl$UniformInfo *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o, Sgl$Material *  matl);
void  Sgl$UniformInfo$fromJson(Sgl$UniformInfo *  self, Json$Json *  jo);
void  Sgl$UniformInfo$toJson(Sgl$UniformInfo *  self, Json$Json *  jo);
SuiCore$Rgba Sgl$UniformInfo$getColor(Sgl$UniformInfo *  self);
bool  Sgl$UniformInfo$updateUniform(Sgl$UniformInfo *  self, Sgl$Program *  program);


// 虚表
struct tagVtable_Sgl$Material {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Material _vtable_Sgl$Material;

// class refc:0
struct tagSgl$Material {
	Object super; 
	Orc$String*  path ;
	Sgl$Program*  program ;
	bool  depthTest ;
	bool  depthWrite ;
	bool  transparent ;
	bool  stencilTest ;
	bool  alphaTest ;
	bool  scissorTest ;
	bool  blend ;
	bool  cullFace ;
	bool  wireframe ;
	Orc$List*  uniforms ;
	Sgl$Mat mvp ;
	Sgl$Mat model ;
	Sgl$Mat view ;
	Sgl$Mat projection ;
	Orc$String*  vsPath ;
	Orc$String*  fsPath ;
	void  (*insp) (Sgl$Material *  self, SuiDesigner$Insp *  insp);
	void  (*insp_hi) (Sgl$Material *  self);
	void  (*prepareDraw) (Sgl$Material *  self);
	void  (*endDraw) (Sgl$Material *  self);
	bool  (*load) (Sgl$Material *  self, const char *  path);
	bool  (*saveTo) (Sgl$Material *  self, Orc$String *  path);
	bool  (*save) (Sgl$Material *  self);
	void  (*fromJson) (Sgl$Material *  self, Json$Json *  jo);
	void  (*toJson) (Sgl$Material *  self, Json$Json *  jo);
	void  (*updateMvp) (Sgl$Material *  self);
	void  (*setMvp) (Sgl$Material *  self, Sgl$Mat model, Sgl$Mat view, Sgl$Mat projection);
	void  (*updateUniforms) (Sgl$Material *  self);
	Sgl$UniformInfo*  (*getUniformInfo) (Sgl$UniformInfo **  __outRef__, Sgl$Material *  self, const char *  key);
	Sgl$UniformInfo*  (*gocUniformInfo) (Sgl$UniformInfo **  __outRef__, Sgl$Material *  self, const char *  key);
	void  (*setUniformTex2dByPath) (Sgl$Material *  self, const char *  key, const char *  path);
	Sgl$UniformInfo *  (*setUniformTex2d) (Sgl$Material *  self, const char *  key, Sgl$Tex2d *  tex);
	void  (*setUniformMatArray) (Sgl$Material *  self, const char *  key, Sgl$MatArray*  matArray);
	void  (*setUniformMat4) (Sgl$Material *  self, const char *  key, Sgl$Mat mat);
	void  (*setUniform1i) (Sgl$Material *  self, const char *  key, int  v);
	void  (*setUniform1f) (Sgl$Material *  self, const char *  key, float  v);
	void  (*setUniform2f) (Sgl$Material *  self, const char *  key, float  x, float  y);
	void  (*setUniform3f) (Sgl$Material *  self, const char *  key, float  x, float  y, float  z);
	void  (*setUniform4f) (Sgl$Material *  self, const char *  key, float  x, float  y, float  z, float  w);
	void  (*setUniformColor4f) (Sgl$Material *  self, const char *  key, float  x, float  y, float  z, float  w);
	void  (*setUniformColor4fByInt32Color) (Sgl$Material *  self, const char *  key, int  color);
	void  (*setUniformVec2) (Sgl$Material *  self, const char *  key, SuiCore$Vec2 v);
	void  (*setUniformVec3) (Sgl$Material *  self, const char *  key, SuiCore$Vec3 v3);
	void  (*setUniformVec4) (Sgl$Material *  self, const char *  key, SuiCore$Vec4 v);
	bool  (*buildByShaderPathCstr) (Sgl$Material *  self, const char *  vsPath, const char *  fsPath);
	Sgl$ShaderMeta*  shaderMeta ;
};
Vtable_Sgl$Material* Vtable_Sgl$Material_init(Vtable_Sgl$Material* pvt);
void Sgl$Material_init_fields(Sgl$Material *self);
void Sgl$Material_init(Sgl$Material *self, void *pOwner);
Sgl$Material * Sgl$Material_new(void *pOwner);
void Sgl$Material_fini(Sgl$Material *self);

void  Sgl$Material$insp(Sgl$Material *  self, SuiDesigner$Insp *  insp);
void  Sgl$Material$insp_hi(Sgl$Material *  self);
extern void  Sgl$Material$prepareDraw(Sgl$Material *  self);
extern void  Sgl$Material$endDraw(Sgl$Material *  self);
bool  Sgl$Material$load(Sgl$Material *  self, const char *  path);
bool  Sgl$Material$saveTo(Sgl$Material *  self, Orc$String *  path);
bool  Sgl$Material$save(Sgl$Material *  self);
void  Sgl$Material$fromJson(Sgl$Material *  self, Json$Json *  jo);
void  Sgl$Material$toJson(Sgl$Material *  self, Json$Json *  jo);
void  Sgl$Material$updateMvp(Sgl$Material *  self);
void  Sgl$Material$setMvp(Sgl$Material *  self, Sgl$Mat model, Sgl$Mat view, Sgl$Mat projection);
void  Sgl$Material$updateUniforms(Sgl$Material *  self);
Sgl$UniformInfo*  Sgl$Material$getUniformInfo(Sgl$UniformInfo **  __outRef__, Sgl$Material *  self, const char *  key);
Sgl$UniformInfo*  Sgl$Material$gocUniformInfo(Sgl$UniformInfo **  __outRef__, Sgl$Material *  self, const char *  key);
void  Sgl$Material$setUniformTex2dByPath(Sgl$Material *  self, const char *  key, const char *  path);
Sgl$UniformInfo *  Sgl$Material$setUniformTex2d(Sgl$Material *  self, const char *  key, Sgl$Tex2d *  tex);
void  Sgl$Material$setUniformMatArray(Sgl$Material *  self, const char *  key, Sgl$MatArray*  matArray);
void  Sgl$Material$setUniformMat4(Sgl$Material *  self, const char *  key, Sgl$Mat mat);
void  Sgl$Material$setUniform1i(Sgl$Material *  self, const char *  key, int  v);
void  Sgl$Material$setUniform1f(Sgl$Material *  self, const char *  key, float  v);
void  Sgl$Material$setUniform2f(Sgl$Material *  self, const char *  key, float  x, float  y);
void  Sgl$Material$setUniform3f(Sgl$Material *  self, const char *  key, float  x, float  y, float  z);
void  Sgl$Material$setUniform4f(Sgl$Material *  self, const char *  key, float  x, float  y, float  z, float  w);
void  Sgl$Material$setUniformColor4f(Sgl$Material *  self, const char *  key, float  x, float  y, float  z, float  w);
void  Sgl$Material$setUniformColor4fByInt32Color(Sgl$Material *  self, const char *  key, int  color);
void  Sgl$Material$setUniformVec2(Sgl$Material *  self, const char *  key, SuiCore$Vec2 v);
void  Sgl$Material$setUniformVec3(Sgl$Material *  self, const char *  key, SuiCore$Vec3 v3);
void  Sgl$Material$setUniformVec4(Sgl$Material *  self, const char *  key, SuiCore$Vec4 v);
bool  Sgl$Material$buildByShaderPathCstr(Sgl$Material *  self, const char *  vsPath, const char *  fsPath);


// 虚表
struct tagVtable_Sgl$MaterialInsp {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$MaterialInsp _vtable_Sgl$MaterialInsp;

// class refc:0
struct tagSgl$MaterialInsp {
	Object super; 
	Sui$Window*  win ;
	Sgl$Material*  matl ;
	bool  _reactDirty ;
	void  (*invalidReact) (Sgl$MaterialInsp *  self);
	void  (*rowBool) (Sgl$MaterialInsp *  self, SuiCore$Node *  o, const char *  key);
	void  (*rowString) (Sgl$MaterialInsp *  self, SuiCore$Node *  o, const char *  key);
	void  (*react) (Sgl$MaterialInsp *  self);
	void  (*showWindow) (Sgl$MaterialInsp *  self, Sgl$Material*  matl);
	Sgl$MaterialPreviewView*  glPreviewView ;
};
Vtable_Sgl$MaterialInsp* Vtable_Sgl$MaterialInsp_init(Vtable_Sgl$MaterialInsp* pvt);
void Sgl$MaterialInsp_init_fields(Sgl$MaterialInsp *self);
void Sgl$MaterialInsp_init(Sgl$MaterialInsp *self, void *pOwner);
Sgl$MaterialInsp * Sgl$MaterialInsp_new(void *pOwner);
void Sgl$MaterialInsp_fini(Sgl$MaterialInsp *self);

void  Sgl$MaterialInsp$invalidReact(Sgl$MaterialInsp *  self);
void  Sgl$MaterialInsp$rowBool(Sgl$MaterialInsp *  self, SuiCore$Node *  o, const char *  key);
void  Sgl$MaterialInsp$rowString(Sgl$MaterialInsp *  self, SuiCore$Node *  o, const char *  key);
void  Sgl$MaterialInsp$react(Sgl$MaterialInsp *  self);
void  Sgl$MaterialInsp$showWindow(Sgl$MaterialInsp *  self, Sgl$Material*  matl);


// 虚表
struct tagVtable_Sgl$UniformMeta {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$UniformMeta _vtable_Sgl$UniformMeta;

// class refc:0
struct tagSgl$UniformMeta {
	Object super; 
	Orc$String*  name ;
	Orc$String*  type ;
	Orc$String*  editor ;
	Orc$String*  defaultValue ;
};
Vtable_Sgl$UniformMeta* Vtable_Sgl$UniformMeta_init(Vtable_Sgl$UniformMeta* pvt);
void Sgl$UniformMeta_init_fields(Sgl$UniformMeta *self);
void Sgl$UniformMeta_init(Sgl$UniformMeta *self, void *pOwner);
Sgl$UniformMeta * Sgl$UniformMeta_new(void *pOwner);
void Sgl$UniformMeta_fini(Sgl$UniformMeta *self);



// 虚表
struct tagVtable_Sgl$ShaderMeta {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$ShaderMeta _vtable_Sgl$ShaderMeta;

// class refc:0
struct tagSgl$ShaderMeta {
	Object super; 
	Orc$String*  vsPath ;
	Orc$String*  vsCode ;
	Orc$String*  fsPath ;
	Orc$String*  fsCode ;
	Orc$List*  uniformMetas ;
	Sgl$UniformMeta*  (*getUniformMeta) (Sgl$UniformMeta **  __outRef__, Sgl$ShaderMeta *  self, const char *  name);
	void  (*parseCode) (Sgl$ShaderMeta *  self, Orc$String *  code);
	void  (*parseFsByPathCstr) (Sgl$ShaderMeta *  self, const char *  path);
	void  (*parseVsByPathCstr) (Sgl$ShaderMeta *  self, const char *  path);
};
Vtable_Sgl$ShaderMeta* Vtable_Sgl$ShaderMeta_init(Vtable_Sgl$ShaderMeta* pvt);
void Sgl$ShaderMeta_init_fields(Sgl$ShaderMeta *self);
void Sgl$ShaderMeta_init(Sgl$ShaderMeta *self, void *pOwner);
Sgl$ShaderMeta * Sgl$ShaderMeta_new(void *pOwner);
void Sgl$ShaderMeta_fini(Sgl$ShaderMeta *self);

Sgl$UniformMeta*  Sgl$ShaderMeta$getUniformMeta(Sgl$UniformMeta **  __outRef__, Sgl$ShaderMeta *  self, const char *  name);
void  Sgl$ShaderMeta$parseCode(Sgl$ShaderMeta *  self, Orc$String *  code);
void  Sgl$ShaderMeta$parseFsByPathCstr(Sgl$ShaderMeta *  self, const char *  path);
void  Sgl$ShaderMeta$parseVsByPathCstr(Sgl$ShaderMeta *  self, const char *  path);


// 虚表
struct tagVtable_Sgl$MaterialPreviewView {
	Vtable_SuiView$ImageView super;
};
//虚表实例
extern Vtable_Sgl$MaterialPreviewView _vtable_Sgl$MaterialPreviewView;

// class refc:0
struct tagSgl$MaterialPreviewView {
	SuiView$ImageView super; 
	Sgl$Fbo*  fbo ;
	Sgl$Material*  matl ;
	Sgl$Draw*  drawObj ;
	void  (*buildDrawObj) (Sgl$MaterialPreviewView *  self);
	float  rotateY ;
	float  scale ;
	void  (*applyModel) (Sgl$MaterialPreviewView *  self);
	SuiView$Drag*  drag ;
};
Vtable_Sgl$MaterialPreviewView* Vtable_Sgl$MaterialPreviewView_init(Vtable_Sgl$MaterialPreviewView* pvt);
void Sgl$MaterialPreviewView_init_fields(Sgl$MaterialPreviewView *self);
void Sgl$MaterialPreviewView_init(Sgl$MaterialPreviewView *self, void *pOwner);
Sgl$MaterialPreviewView * Sgl$MaterialPreviewView_new(void *pOwner);
void Sgl$MaterialPreviewView_fini(Sgl$MaterialPreviewView *self);

void  Sgl$MaterialPreviewView$buildDrawObj(Sgl$MaterialPreviewView *  self);
void  Sgl$MaterialPreviewView$draw_self(Sgl$MaterialPreviewView *  self, SuiCore$Canvas *  canvas);
void  Sgl$MaterialPreviewView$onEvent(Sgl$MaterialPreviewView *  self, SuiCore$Event *  e);
void  Sgl$MaterialPreviewView$applyModel(Sgl$MaterialPreviewView *  self);

Sgl$MaterialPreviewView*  Sgl$mkMaterialPreviewView(Sgl$MaterialPreviewView **  __outRef__, void *  parent, long long  key);
void  Sgl$testMaterialMeta();
void  Sgl$testInspMaterial();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
