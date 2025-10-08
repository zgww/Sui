
typedef struct tagSuiDesigner$EventInspAttrChanged SuiDesigner$EventInspAttrChanged;
typedef struct tagVtable_SuiDesigner$EventInspAttrChanged Vtable_SuiDesigner$EventInspAttrChanged;
typedef struct tagSuiDesigner$InspOpt SuiDesigner$InspOpt;
typedef struct tagVtable_SuiDesigner$InspOpt Vtable_SuiDesigner$InspOpt;
typedef struct tagSuiDesigner$InspOpts SuiDesigner$InspOpts;
typedef struct tagVtable_SuiDesigner$InspOpts Vtable_SuiDesigner$InspOpts;
typedef struct tagSuiDesigner$TmpAttrInfo SuiDesigner$TmpAttrInfo;
typedef struct tagSuiDesigner$MethodInfo SuiDesigner$MethodInfo;
typedef struct tagSuiDesigner$InspAttr SuiDesigner$InspAttr;
typedef struct tagVtable_SuiDesigner$InspAttr Vtable_SuiDesigner$InspAttr;
typedef struct tagSuiDesigner$InspAttrColor SuiDesigner$InspAttrColor;
typedef struct tagVtable_SuiDesigner$InspAttrColor Vtable_SuiDesigner$InspAttrColor;
typedef struct tagSuiDesigner$InspAttrImageSrc SuiDesigner$InspAttrImageSrc;
typedef struct tagVtable_SuiDesigner$InspAttrImageSrc Vtable_SuiDesigner$InspAttrImageSrc;
typedef struct tagSuiDesigner$InspAttrFilePath SuiDesigner$InspAttrFilePath;
typedef struct tagVtable_SuiDesigner$InspAttrFilePath Vtable_SuiDesigner$InspAttrFilePath;
typedef struct tagSuiDesigner$InspAttrSelect SuiDesigner$InspAttrSelect;
typedef struct tagVtable_SuiDesigner$InspAttrSelect Vtable_SuiDesigner$InspAttrSelect;
typedef struct tagSuiDesigner$InspNode SuiDesigner$InspNode;
typedef struct tagVtable_SuiDesigner$InspNode Vtable_SuiDesigner$InspNode;
typedef struct tagSuiDesigner$InspAttrItem SuiDesigner$InspAttrItem;
typedef struct tagVtable_SuiDesigner$InspAttrItem Vtable_SuiDesigner$InspAttrItem;
typedef struct tagSuiDesigner$InspPanel SuiDesigner$InspPanel;
typedef struct tagVtable_SuiDesigner$InspPanel Vtable_SuiDesigner$InspPanel;
typedef struct tagSuiDesigner$Insp SuiDesigner$Insp;
typedef struct tagVtable_SuiDesigner$Insp Vtable_SuiDesigner$Insp;
typedef struct tagSuiDesigner$InspLibItem SuiDesigner$InspLibItem;
typedef struct tagVtable_SuiDesigner$InspLibItem Vtable_SuiDesigner$InspLibItem;
typedef struct tagSuiDesigner$InspLib SuiDesigner$InspLib;
typedef struct tagVtable_SuiDesigner$InspLib Vtable_SuiDesigner$InspLib;
typedef struct tagSuiDesigner$TestObjSuper SuiDesigner$TestObjSuper;
typedef struct tagVtable_SuiDesigner$TestObjSuper Vtable_SuiDesigner$TestObjSuper;
typedef struct tagSuiDesigner$TestObj SuiDesigner$TestObj;
typedef struct tagVtable_SuiDesigner$TestObj Vtable_SuiDesigner$TestObj;


#ifndef define_struct___SuiDesigner__Insp_orc_h__
#define define_struct___SuiDesigner__Insp_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__Insp_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
#include "../Json/cJSON.h"

#define INCLUDE_ONLY_TYPE
#include "../Orc/String_orc.h"
#undef INCLUDE_ONLY_TYPE



#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__Insp_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


struct tagSuiDesigner$TmpAttrInfo {
	Orc$String *  panelName ;
	int  hboxIdx ;
	bool  isPanelStart ;
	bool  isPanelEnd ;
	bool  isHboxStart ;
	bool  isHboxEnd ;
};


struct tagSuiDesigner$MethodInfo {
	int  hboxIdx ;
	bool  isMethod ;
};


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__Insp_orc_h__
#define __SuiDesigner__Insp_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Inset_orc.h"
#include "../Sui/Core/Bezier_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/Select_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/Slider_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ColorPicker_orc.h"
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./SceneView_orc.h"
#include "./SceneHierView_orc.h"
#include "./ANode_orc.h"
#include "./BezierEditView_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./FileChooser_orc.h"
#include "./Theme_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$EventInspAttrChanged {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiDesigner$EventInspAttrChanged _vtable_SuiDesigner$EventInspAttrChanged;

// class refc:0
struct tagSuiDesigner$EventInspAttrChanged {
	SuiCore$Event super; 
	OrcMetaField *  mf ;
	Object*  obj ;
	Object*  newValue ;
	SuiDesigner$InspAttr*  inspAttr ;
};
Vtable_SuiDesigner$EventInspAttrChanged* Vtable_SuiDesigner$EventInspAttrChanged_init(Vtable_SuiDesigner$EventInspAttrChanged* pvt);
void SuiDesigner$EventInspAttrChanged_init_fields(SuiDesigner$EventInspAttrChanged *self);
void SuiDesigner$EventInspAttrChanged_init(SuiDesigner$EventInspAttrChanged *self, void *pOwner);
SuiDesigner$EventInspAttrChanged * SuiDesigner$EventInspAttrChanged_new(void *pOwner);
void SuiDesigner$EventInspAttrChanged_fini(SuiDesigner$EventInspAttrChanged *self);



// 虚表
struct tagVtable_SuiDesigner$InspOpt {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InspOpt _vtable_SuiDesigner$InspOpt;

// class refc:0
struct tagSuiDesigner$InspOpt {
	Object super; 
	int  value ;
	Orc$String*  label ;
};
Vtable_SuiDesigner$InspOpt* Vtable_SuiDesigner$InspOpt_init(Vtable_SuiDesigner$InspOpt* pvt);
void SuiDesigner$InspOpt_init_fields(SuiDesigner$InspOpt *self);
void SuiDesigner$InspOpt_init(SuiDesigner$InspOpt *self, void *pOwner);
SuiDesigner$InspOpt * SuiDesigner$InspOpt_new(void *pOwner);
void SuiDesigner$InspOpt_fini(SuiDesigner$InspOpt *self);



// 虚表
struct tagVtable_SuiDesigner$InspOpts {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InspOpts _vtable_SuiDesigner$InspOpts;

// class refc:0
struct tagSuiDesigner$InspOpts {
	Object super; 
	Orc$List*  opts ;
	SuiDesigner$InspOpts *  (*set) (SuiDesigner$InspOpts *  self, int  value, const char *  label);
	int  (*getValueByLabel) (SuiDesigner$InspOpts *  self, const char *  label);
	Orc$List*  (*getLabels) (Orc$List **  __outRef__, SuiDesigner$InspOpts *  self);
};
Vtable_SuiDesigner$InspOpts* Vtable_SuiDesigner$InspOpts_init(Vtable_SuiDesigner$InspOpts* pvt);
void SuiDesigner$InspOpts_init_fields(SuiDesigner$InspOpts *self);
void SuiDesigner$InspOpts_init(SuiDesigner$InspOpts *self, void *pOwner);
SuiDesigner$InspOpts * SuiDesigner$InspOpts_new(void *pOwner);
void SuiDesigner$InspOpts_fini(SuiDesigner$InspOpts *self);

SuiDesigner$InspOpts *  SuiDesigner$InspOpts$set(SuiDesigner$InspOpts *  self, int  value, const char *  label);
int  SuiDesigner$InspOpts$getValueByLabel(SuiDesigner$InspOpts *  self, const char *  label);
Orc$List*  SuiDesigner$InspOpts$getLabels(Orc$List **  __outRef__, SuiDesigner$InspOpts *  self);



//结构体元数据获取即初始化
MetaStruct* SuiDesigner$TmpAttrInfo_getOrInitMetaStruct();



//结构体元数据获取即初始化
MetaStruct* SuiDesigner$MethodInfo_getOrInitMetaStruct();

void  SuiDesigner$TmpAttrInfo$init(SuiDesigner$TmpAttrInfo *  self);
void  SuiDesigner$TmpAttrInfo$proc(SuiDesigner$TmpAttrInfo *  self, OrcMetaField *  mf, SuiDesigner$InspAttr *  attr, SuiDesigner$Insp *  insp);
SuiDesigner$MethodInfo SuiDesigner$TmpAttrInfo$extractHboxIdx(SuiDesigner$TmpAttrInfo *  self, OrcMetaField *  mf);

// 虚表
struct tagVtable_SuiDesigner$InspAttr {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InspAttr _vtable_SuiDesigner$InspAttr;

// class refc:0
struct tagSuiDesigner$InspAttr {
	Object super; 
	Orc$String*  _name ;
	Orc$String*  _panelName ;
	bool  _hbox ;
	bool  _ignore ;
	void  (*bind) (SuiDesigner$InspAttr *  self, SuiDesigner$Insp *  insp, const char *  name, const char *  panelName);
	void  (*to) (SuiDesigner$InspAttr *  self, SuiDesigner$Insp *  insp);
	void  (*inspValue) (SuiDesigner$InspAttr *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);
};
Vtable_SuiDesigner$InspAttr* Vtable_SuiDesigner$InspAttr_init(Vtable_SuiDesigner$InspAttr* pvt);
void SuiDesigner$InspAttr_init_fields(SuiDesigner$InspAttr *self);
void SuiDesigner$InspAttr_init(SuiDesigner$InspAttr *self, void *pOwner);
SuiDesigner$InspAttr * SuiDesigner$InspAttr_new(void *pOwner);
void SuiDesigner$InspAttr_fini(SuiDesigner$InspAttr *self);

void  SuiDesigner$InspAttr$bind(SuiDesigner$InspAttr *  self, SuiDesigner$Insp *  insp, const char *  name, const char *  panelName);
void  SuiDesigner$InspAttr$to(SuiDesigner$InspAttr *  self, SuiDesigner$Insp *  insp);
void  SuiDesigner$InspAttr$inspValue(SuiDesigner$InspAttr *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);


// 虚表
struct tagVtable_SuiDesigner$InspAttrColor {
	Vtable_SuiDesigner$InspAttr super;
};
//虚表实例
extern Vtable_SuiDesigner$InspAttrColor _vtable_SuiDesigner$InspAttrColor;

// class refc:0
struct tagSuiDesigner$InspAttrColor {
	SuiDesigner$InspAttr super; 
	
};
Vtable_SuiDesigner$InspAttrColor* Vtable_SuiDesigner$InspAttrColor_init(Vtable_SuiDesigner$InspAttrColor* pvt);
void SuiDesigner$InspAttrColor_init_fields(SuiDesigner$InspAttrColor *self);
void SuiDesigner$InspAttrColor_init(SuiDesigner$InspAttrColor *self, void *pOwner);
SuiDesigner$InspAttrColor * SuiDesigner$InspAttrColor_new(void *pOwner);
void SuiDesigner$InspAttrColor_fini(SuiDesigner$InspAttrColor *self);

void  SuiDesigner$InspAttrColor$inspValue(SuiDesigner$InspAttrColor *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);


// 虚表
struct tagVtable_SuiDesigner$InspAttrImageSrc {
	Vtable_SuiDesigner$InspAttr super;
};
//虚表实例
extern Vtable_SuiDesigner$InspAttrImageSrc _vtable_SuiDesigner$InspAttrImageSrc;

// class refc:0
struct tagSuiDesigner$InspAttrImageSrc {
	SuiDesigner$InspAttr super; 
	
};
Vtable_SuiDesigner$InspAttrImageSrc* Vtable_SuiDesigner$InspAttrImageSrc_init(Vtable_SuiDesigner$InspAttrImageSrc* pvt);
void SuiDesigner$InspAttrImageSrc_init_fields(SuiDesigner$InspAttrImageSrc *self);
void SuiDesigner$InspAttrImageSrc_init(SuiDesigner$InspAttrImageSrc *self, void *pOwner);
SuiDesigner$InspAttrImageSrc * SuiDesigner$InspAttrImageSrc_new(void *pOwner);
void SuiDesigner$InspAttrImageSrc_fini(SuiDesigner$InspAttrImageSrc *self);

void  SuiDesigner$InspAttrImageSrc$inspValue(SuiDesigner$InspAttrImageSrc *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);


// 虚表
struct tagVtable_SuiDesigner$InspAttrFilePath {
	Vtable_SuiDesigner$InspAttr super;
};
//虚表实例
extern Vtable_SuiDesigner$InspAttrFilePath _vtable_SuiDesigner$InspAttrFilePath;

// class refc:0
struct tagSuiDesigner$InspAttrFilePath {
	SuiDesigner$InspAttr super; 
	
};
Vtable_SuiDesigner$InspAttrFilePath* Vtable_SuiDesigner$InspAttrFilePath_init(Vtable_SuiDesigner$InspAttrFilePath* pvt);
void SuiDesigner$InspAttrFilePath_init_fields(SuiDesigner$InspAttrFilePath *self);
void SuiDesigner$InspAttrFilePath_init(SuiDesigner$InspAttrFilePath *self, void *pOwner);
SuiDesigner$InspAttrFilePath * SuiDesigner$InspAttrFilePath_new(void *pOwner);
void SuiDesigner$InspAttrFilePath_fini(SuiDesigner$InspAttrFilePath *self);

void  SuiDesigner$InspAttrFilePath$inspValue(SuiDesigner$InspAttrFilePath *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);


// 虚表
struct tagVtable_SuiDesigner$InspAttrSelect {
	Vtable_SuiDesigner$InspAttr super;
};
//虚表实例
extern Vtable_SuiDesigner$InspAttrSelect _vtable_SuiDesigner$InspAttrSelect;

// class refc:0
struct tagSuiDesigner$InspAttrSelect {
	SuiDesigner$InspAttr super; 
	SuiDesigner$InspOpts*  opts ;
};
Vtable_SuiDesigner$InspAttrSelect* Vtable_SuiDesigner$InspAttrSelect_init(Vtable_SuiDesigner$InspAttrSelect* pvt);
void SuiDesigner$InspAttrSelect_init_fields(SuiDesigner$InspAttrSelect *self);
void SuiDesigner$InspAttrSelect_init(SuiDesigner$InspAttrSelect *self, void *pOwner);
SuiDesigner$InspAttrSelect * SuiDesigner$InspAttrSelect_new(void *pOwner);
void SuiDesigner$InspAttrSelect_fini(SuiDesigner$InspAttrSelect *self);

void  SuiDesigner$InspAttrSelect$inspValue(SuiDesigner$InspAttrSelect *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);


// 虚表
struct tagVtable_SuiDesigner$InspNode {
	Vtable_SuiCore$Node super;
};
//虚表实例
extern Vtable_SuiDesigner$InspNode _vtable_SuiDesigner$InspNode;

// class refc:0
struct tagSuiDesigner$InspNode {
	SuiCore$Node super; 
	
};
Vtable_SuiDesigner$InspNode* Vtable_SuiDesigner$InspNode_init(Vtable_SuiDesigner$InspNode* pvt);
void SuiDesigner$InspNode_init_fields(SuiDesigner$InspNode *self);
void SuiDesigner$InspNode_init(SuiDesigner$InspNode *self, void *pOwner);
SuiDesigner$InspNode * SuiDesigner$InspNode_new(void *pOwner);
void SuiDesigner$InspNode_fini(SuiDesigner$InspNode *self);



// 虚表
struct tagVtable_SuiDesigner$InspAttrItem {
	Vtable_SuiDesigner$InspNode super;
};
//虚表实例
extern Vtable_SuiDesigner$InspAttrItem _vtable_SuiDesigner$InspAttrItem;

// class refc:0
struct tagSuiDesigner$InspAttrItem {
	SuiDesigner$InspNode super; 
	SuiDesigner$InspAttr *  attr ;
	OrcMetaField *  mf ;
};
Vtable_SuiDesigner$InspAttrItem* Vtable_SuiDesigner$InspAttrItem_init(Vtable_SuiDesigner$InspAttrItem* pvt);
void SuiDesigner$InspAttrItem_init_fields(SuiDesigner$InspAttrItem *self);
void SuiDesigner$InspAttrItem_init(SuiDesigner$InspAttrItem *self, void *pOwner);
SuiDesigner$InspAttrItem * SuiDesigner$InspAttrItem_new(void *pOwner);
void SuiDesigner$InspAttrItem_fini(SuiDesigner$InspAttrItem *self);



// 虚表
struct tagVtable_SuiDesigner$InspPanel {
	Vtable_SuiDesigner$InspNode super;
};
//虚表实例
extern Vtable_SuiDesigner$InspPanel _vtable_SuiDesigner$InspPanel;

// class refc:0
struct tagSuiDesigner$InspPanel {
	SuiDesigner$InspNode super; 
	
};
Vtable_SuiDesigner$InspPanel* Vtable_SuiDesigner$InspPanel_init(Vtable_SuiDesigner$InspPanel* pvt);
void SuiDesigner$InspPanel_init_fields(SuiDesigner$InspPanel *self);
void SuiDesigner$InspPanel_init(SuiDesigner$InspPanel *self, void *pOwner);
SuiDesigner$InspPanel * SuiDesigner$InspPanel_new(void *pOwner);
void SuiDesigner$InspPanel_fini(SuiDesigner$InspPanel *self);



// 虚表
struct tagVtable_SuiDesigner$Insp {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Insp _vtable_SuiDesigner$Insp;

// class refc:0
struct tagSuiDesigner$Insp {
	Object super; 
	Orc$List*  curNodeStack ;
	Object*  obj ;
	Orc$Map*  attrMap ;
	SuiDesigner$InspLib*  lib ;
	SuiDesigner$InspAttr *  (*getAttr) (SuiDesigner$Insp *  self, const char *  key);
	void  (*excludes) (SuiDesigner$Insp *  self, const char *  keys);
	void  (*exclude) (SuiDesigner$Insp *  self, const char *  key);
	SuiCore$Node *  (*peekParent) (SuiDesigner$Insp *  self);
	void  (*call_insp) (SuiDesigner$Insp *  self);
	void  (**beforeInsp)(void *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
	void  (**afterInsp)(void *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
	void  (**cbInsp)(void *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
	void  (*insp) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj);
	void  (*inspObj) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj);
	void  (*inspExtends) (SuiDesigner$Insp *  self, Object *  obj, Vtable_Object *  vt);
	void  (*inspVt) (SuiDesigner$Insp *  self, Object *  obj, Vtable_Object *  vt);
	void  (*inspField) (SuiDesigner$Insp *  self, Object *  obj, OrcMetaField *  mf);
	const char *  (*queryAttrDirection) (SuiDesigner$Insp *  self, OrcMetaField *  mf);
	bool  (*isSkipAttr) (SuiDesigner$Insp *  self, Object *  obj, OrcMetaField *  mf);
	void  (*inspValueDefault) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspString) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspStringPath) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspInt) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspFloat) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspBool) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspVec2) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspVec3) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspVec4) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspInset) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspIntColor) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspRgbaf) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspRgba) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	bool  (*inspBezier) (SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
	void  (*mkFieldName) (SuiDesigner$Insp *  self, SuiCore$Node *  o, const char *  name);
	void  (**cbSetAttr)(void *  self, Object *  obj, OrcMetaField *  mf, Object *  inspValue);
	void  (*setAttrDefault) (SuiDesigner$Insp *  self, OrcMetaField *  mf, Object *  inspValue);
	void  (*setAttr) (SuiDesigner$Insp *  self, OrcMetaField *  mf, Object *  inspValue);
};
Vtable_SuiDesigner$Insp* Vtable_SuiDesigner$Insp_init(Vtable_SuiDesigner$Insp* pvt);
void SuiDesigner$Insp_init_fields(SuiDesigner$Insp *self);
void SuiDesigner$Insp_init(SuiDesigner$Insp *self, void *pOwner);
SuiDesigner$Insp * SuiDesigner$Insp_new(void *pOwner);
void SuiDesigner$Insp_fini(SuiDesigner$Insp *self);

SuiDesigner$InspAttr *  SuiDesigner$Insp$getAttr(SuiDesigner$Insp *  self, const char *  key);
void  SuiDesigner$Insp$excludes(SuiDesigner$Insp *  self, const char *  keys);
void  SuiDesigner$Insp$exclude(SuiDesigner$Insp *  self, const char *  key);
SuiCore$Node *  SuiDesigner$Insp$peekParent(SuiDesigner$Insp *  self);
void  SuiDesigner$Insp$call_insp(SuiDesigner$Insp *  self);
void  SuiDesigner$Insp$insp(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj);
void  SuiDesigner$Insp$inspObj(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj);
void  SuiDesigner$Insp$inspExtends(SuiDesigner$Insp *  self, Object *  obj, Vtable_Object *  vt);
void  SuiDesigner$Insp$inspVt(SuiDesigner$Insp *  self, Object *  obj, Vtable_Object *  vt);
void  SuiDesigner$Insp$inspField(SuiDesigner$Insp *  self, Object *  obj, OrcMetaField *  mf);
const char *  SuiDesigner$Insp$queryAttrDirection(SuiDesigner$Insp *  self, OrcMetaField *  mf);
bool  SuiDesigner$Insp$isSkipAttr(SuiDesigner$Insp *  self, Object *  obj, OrcMetaField *  mf);
void  SuiDesigner$Insp$inspValueDefault(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspString(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspStringPath(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspInt(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspFloat(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspBool(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspVec2(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspVec3(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspVec4(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspInset(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspIntColor(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspRgbaf(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspRgba(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
bool  SuiDesigner$Insp$inspBezier(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf);
void  SuiDesigner$Insp$mkFieldName(SuiDesigner$Insp *  self, SuiCore$Node *  o, const char *  name);
void  SuiDesigner$Insp$setAttrDefault(SuiDesigner$Insp *  self, OrcMetaField *  mf, Object *  inspValue);
void  SuiDesigner$Insp$setAttr(SuiDesigner$Insp *  self, OrcMetaField *  mf, Object *  inspValue);


// 虚表
struct tagVtable_SuiDesigner$InspLibItem {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InspLibItem _vtable_SuiDesigner$InspLibItem;

// class refc:0
struct tagSuiDesigner$InspLibItem {
	Object super; 
	Orc$String*  name ;
	void  (*inspValue) (SuiDesigner$InspLibItem *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);
};
Vtable_SuiDesigner$InspLibItem* Vtable_SuiDesigner$InspLibItem_init(Vtable_SuiDesigner$InspLibItem* pvt);
void SuiDesigner$InspLibItem_init_fields(SuiDesigner$InspLibItem *self);
void SuiDesigner$InspLibItem_init(SuiDesigner$InspLibItem *self, void *pOwner);
SuiDesigner$InspLibItem * SuiDesigner$InspLibItem_new(void *pOwner);
void SuiDesigner$InspLibItem_fini(SuiDesigner$InspLibItem *self);

void  SuiDesigner$InspLibItem$inspValue(SuiDesigner$InspLibItem *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp);


// 虚表
struct tagVtable_SuiDesigner$InspLib {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InspLib _vtable_SuiDesigner$InspLib;

// class refc:0
struct tagSuiDesigner$InspLib {
	Object super; 
	Orc$Map*  nameMap ;
	void  (*bind) (SuiDesigner$InspLib *  self, SuiDesigner$InspLibItem *  item);
	SuiDesigner$InspLibItem *  (*getByObject) (SuiDesigner$InspLib *  self, Object *  obj);
	SuiDesigner$InspLibItem *  (*getByVtable) (SuiDesigner$InspLib *  self, Vtable_Object *  vt);
};
Vtable_SuiDesigner$InspLib* Vtable_SuiDesigner$InspLib_init(Vtable_SuiDesigner$InspLib* pvt);
void SuiDesigner$InspLib_init_fields(SuiDesigner$InspLib *self);
void SuiDesigner$InspLib_init(SuiDesigner$InspLib *self, void *pOwner);
SuiDesigner$InspLib * SuiDesigner$InspLib_new(void *pOwner);
void SuiDesigner$InspLib_fini(SuiDesigner$InspLib *self);

void  SuiDesigner$InspLib$bind(SuiDesigner$InspLib *  self, SuiDesigner$InspLibItem *  item);
SuiDesigner$InspLibItem *  SuiDesigner$InspLib$getByObject(SuiDesigner$InspLib *  self, Object *  obj);
SuiDesigner$InspLibItem *  SuiDesigner$InspLib$getByVtable(SuiDesigner$InspLib *  self, Vtable_Object *  vt);

SuiDesigner$InspLib *  SuiDesigner$useInspLib();

// 虚表
struct tagVtable_SuiDesigner$TestObjSuper {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$TestObjSuper _vtable_SuiDesigner$TestObjSuper;

// class refc:1
struct tagSuiDesigner$TestObjSuper {
	Object super; 
	int  xx ;
	int  yy ;
	int  cc ;
	int  kk ;
	void  (*insp) (SuiDesigner$TestObjSuper *  self, SuiDesigner$Insp *  insp);
};
Vtable_SuiDesigner$TestObjSuper* Vtable_SuiDesigner$TestObjSuper_init(Vtable_SuiDesigner$TestObjSuper* pvt);
void SuiDesigner$TestObjSuper_init_fields(SuiDesigner$TestObjSuper *self);
void SuiDesigner$TestObjSuper_init(SuiDesigner$TestObjSuper *self, void *pOwner);
SuiDesigner$TestObjSuper * SuiDesigner$TestObjSuper_new(void *pOwner);
void SuiDesigner$TestObjSuper_fini(SuiDesigner$TestObjSuper *self);

void  SuiDesigner$TestObjSuper$insp(SuiDesigner$TestObjSuper *  self, SuiDesigner$Insp *  insp);


// 虚表
struct tagVtable_SuiDesigner$TestObj {
	Vtable_SuiDesigner$TestObjSuper super;
};
//虚表实例
extern Vtable_SuiDesigner$TestObj _vtable_SuiDesigner$TestObj;

// class refc:0
struct tagSuiDesigner$TestObj {
	SuiDesigner$TestObjSuper super; 
	int  age ;
	Orc$String*  name ;
	float  value ;
	bool  isMale ;
	SuiCore$Vec2 pos ;
	SuiCore$Vec3 rotation ;
	SuiCore$Vec4 quat ;
	void  (*insp1_say) (SuiDesigner$TestObj *  self);
	void  (*insp1_say2) (SuiDesigner$TestObj *  self);
	void  (*insp0_say2) (SuiDesigner$TestObj *  self);
};
Vtable_SuiDesigner$TestObj* Vtable_SuiDesigner$TestObj_init(Vtable_SuiDesigner$TestObj* pvt);
void SuiDesigner$TestObj_init_fields(SuiDesigner$TestObj *self);
void SuiDesigner$TestObj_init(SuiDesigner$TestObj *self, void *pOwner);
SuiDesigner$TestObj * SuiDesigner$TestObj_new(void *pOwner);
void SuiDesigner$TestObj_fini(SuiDesigner$TestObj *self);

void  SuiDesigner$TestObj$insp(SuiDesigner$TestObj *  self, SuiDesigner$Insp *  insp);
void  SuiDesigner$TestObj$insp1_say(SuiDesigner$TestObj *  self);
void  SuiDesigner$TestObj$insp1_say2(SuiDesigner$TestObj *  self);
void  SuiDesigner$TestObj$insp0_say2(SuiDesigner$TestObj *  self);

void  SuiDesigner$Insp_mkVec2(SuiCore$Node *  o, long long  key, SuiCore$Vec2 v, void  (**set)(void *  self, SuiCore$Vec2 nv));
void  SuiDesigner$Insp_mkVec3(SuiCore$Node *  o, long long  key, SuiCore$Vec3 v, void  (**set)(void *  self, SuiCore$Vec3 nv));
void  SuiDesigner$Insp_mkVec4(SuiCore$Node *  o, long long  key, SuiCore$Vec4 v, void  (**set)(void *  self, SuiCore$Vec4 nv));
void  SuiDesigner$testInsp();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
