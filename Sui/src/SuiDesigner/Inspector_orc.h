
typedef struct tagSuiDesigner$InspectorOption SuiDesigner$InspectorOption;
typedef struct tagVtable_SuiDesigner$InspectorOption Vtable_SuiDesigner$InspectorOption;
typedef struct tagSuiDesigner$InspectorAttrInfo SuiDesigner$InspectorAttrInfo;
typedef struct tagVtable_SuiDesigner$InspectorAttrInfo Vtable_SuiDesigner$InspectorAttrInfo;
typedef struct tagSuiDesigner$Inspector SuiDesigner$Inspector;
typedef struct tagVtable_SuiDesigner$Inspector Vtable_SuiDesigner$Inspector;


#ifndef define_struct___SuiDesigner__Inspector_orc_h__
#define define_struct___SuiDesigner__Inspector_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__Inspector_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include "../Json/cJSON.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__Inspector_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__Inspector_orc_h__
#define __SuiDesigner__Inspector_orc_h__

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


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$InspectorOption {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InspectorOption _vtable_SuiDesigner$InspectorOption;

// class refc:0
struct tagSuiDesigner$InspectorOption {
	Object super; 
	int  value ;
	Orc$String*  label ;
};
Vtable_SuiDesigner$InspectorOption* Vtable_SuiDesigner$InspectorOption_init(Vtable_SuiDesigner$InspectorOption* pvt);
void SuiDesigner$InspectorOption_init_fields(SuiDesigner$InspectorOption *self);
void SuiDesigner$InspectorOption_init(SuiDesigner$InspectorOption *self, void *pOwner);
SuiDesigner$InspectorOption * SuiDesigner$InspectorOption_new(void *pOwner);
void SuiDesigner$InspectorOption_fini(SuiDesigner$InspectorOption *self);



// 虚表
struct tagVtable_SuiDesigner$InspectorAttrInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InspectorAttrInfo _vtable_SuiDesigner$InspectorAttrInfo;

// class refc:0
struct tagSuiDesigner$InspectorAttrInfo {
	Object super; 
	Orc$String*  key ;
	bool  bColor ;
	bool  bImageSrc ;
	bool  bFileSrc ;
	bool  bSelect ;
	bool  bSlider ;
	float  fromValue ;
	float  toValue ;
	Orc$List*  options ;
	Orc$List*  (*gocOptions) (Orc$List **  __outRef__, SuiDesigner$InspectorAttrInfo *  self);
	void  (*setOption) (SuiDesigner$InspectorAttrInfo *  self, int  value, const char *  label);
	Orc$List*  (*getOptionLabels) (Orc$List **  __outRef__, SuiDesigner$InspectorAttrInfo *  self);
};
Vtable_SuiDesigner$InspectorAttrInfo* Vtable_SuiDesigner$InspectorAttrInfo_init(Vtable_SuiDesigner$InspectorAttrInfo* pvt);
void SuiDesigner$InspectorAttrInfo_init_fields(SuiDesigner$InspectorAttrInfo *self);
void SuiDesigner$InspectorAttrInfo_init(SuiDesigner$InspectorAttrInfo *self, void *pOwner);
SuiDesigner$InspectorAttrInfo * SuiDesigner$InspectorAttrInfo_new(void *pOwner);
void SuiDesigner$InspectorAttrInfo_fini(SuiDesigner$InspectorAttrInfo *self);

Orc$List*  SuiDesigner$InspectorAttrInfo$gocOptions(Orc$List **  __outRef__, SuiDesigner$InspectorAttrInfo *  self);
void  SuiDesigner$InspectorAttrInfo$setOption(SuiDesigner$InspectorAttrInfo *  self, int  value, const char *  label);
Orc$List*  SuiDesigner$InspectorAttrInfo$getOptionLabels(Orc$List **  __outRef__, SuiDesigner$InspectorAttrInfo *  self);


// 虚表
struct tagVtable_SuiDesigner$Inspector {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Inspector _vtable_SuiDesigner$Inspector;

// class refc:0
struct tagSuiDesigner$Inspector {
	Object super; 
	Object*  obj ;
	void  (**cbSetField)(void *  self, Object *  obj, const char *  key, Object *  value);
	SuiCore$Node*  parentNode ;
	Orc$Map*  attrInfoMap ;
	bool  useDefaultInspect ;
	void  (*reset) (SuiDesigner$Inspector *  self);
	SuiDesigner$InspectorAttrInfo *  (*getAttrInfo) (SuiDesigner$Inspector *  self, const char *  key);
	SuiDesigner$InspectorAttrInfo*  (*gocAttrInfo) (SuiDesigner$InspectorAttrInfo **  __outRef__, SuiDesigner$Inspector *  self, const char *  key);
	void  (*markAttrAsColor) (SuiDesigner$Inspector *  self, const char *  key);
	void  (*markAttrAsImageSrc) (SuiDesigner$Inspector *  self, const char *  key);
	void  (*markAttrAsFileSrc) (SuiDesigner$Inspector *  self, const char *  key);
	void  (*markAttrAsSlider) (SuiDesigner$Inspector *  self, const char *  key, float  fromValue, float  toValue);
	SuiDesigner$InspectorAttrInfo*  (*markAttrAsSelect) (SuiDesigner$InspectorAttrInfo **  __outRef__, SuiDesigner$Inspector *  self, const char *  key);
	void  (*clearAttrInfoMap) (SuiDesigner$Inspector *  self);
	void  (*setField) (SuiDesigner$Inspector *  self, Object *  obj, const char *  key, Object *  value);
	void  (*reactObject_withExtendsChain) (SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode, Object *  obj, Vtable_Object *  vt);
	void  (*reactObject) (SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode);
	void  (*inspect) (SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode, Object *  obj);
	void  (*callOnInspect) (SuiDesigner$Inspector *  self);
	int  (*countFieldsOfVtable) (SuiDesigner$Inspector *  self, Vtable_Object *  vt);
	void  (*reactObject_byVtable) (SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  _obj, Vtable_Object *  vt, int  vtIdx);
	void  (*reactObjectField) (SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf);
	void  (*reactObjectFieldName) (SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf);
	void  (*reactObjectFieldRow) (SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf, void  (**renderBody)(void *  self, SuiCore$Node *  o));
	void  (*reactObjectField_do) (SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf);
	void  (**setAttr)(void *  self, const char *  name, Json$Json*  jv);
};
Vtable_SuiDesigner$Inspector* Vtable_SuiDesigner$Inspector_init(Vtable_SuiDesigner$Inspector* pvt);
void SuiDesigner$Inspector_init_fields(SuiDesigner$Inspector *self);
void SuiDesigner$Inspector_init(SuiDesigner$Inspector *self, void *pOwner);
SuiDesigner$Inspector * SuiDesigner$Inspector_new(void *pOwner);
void SuiDesigner$Inspector_fini(SuiDesigner$Inspector *self);

void  SuiDesigner$Inspector$reset(SuiDesigner$Inspector *  self);
SuiDesigner$InspectorAttrInfo *  SuiDesigner$Inspector$getAttrInfo(SuiDesigner$Inspector *  self, const char *  key);
SuiDesigner$InspectorAttrInfo*  SuiDesigner$Inspector$gocAttrInfo(SuiDesigner$InspectorAttrInfo **  __outRef__, SuiDesigner$Inspector *  self, const char *  key);
void  SuiDesigner$Inspector$markAttrAsColor(SuiDesigner$Inspector *  self, const char *  key);
void  SuiDesigner$Inspector$markAttrAsImageSrc(SuiDesigner$Inspector *  self, const char *  key);
void  SuiDesigner$Inspector$markAttrAsFileSrc(SuiDesigner$Inspector *  self, const char *  key);
void  SuiDesigner$Inspector$markAttrAsSlider(SuiDesigner$Inspector *  self, const char *  key, float  fromValue, float  toValue);
SuiDesigner$InspectorAttrInfo*  SuiDesigner$Inspector$markAttrAsSelect(SuiDesigner$InspectorAttrInfo **  __outRef__, SuiDesigner$Inspector *  self, const char *  key);
void  SuiDesigner$Inspector$clearAttrInfoMap(SuiDesigner$Inspector *  self);
void  SuiDesigner$Inspector$setField(SuiDesigner$Inspector *  self, Object *  obj, const char *  key, Object *  value);
void  SuiDesigner$Inspector$reactObject_withExtendsChain(SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode, Object *  obj, Vtable_Object *  vt);
void  SuiDesigner$Inspector$reactObject(SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode);
void  SuiDesigner$Inspector$inspect(SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode, Object *  obj);
void  SuiDesigner$Inspector$callOnInspect(SuiDesigner$Inspector *  self);
int  SuiDesigner$Inspector$countFieldsOfVtable(SuiDesigner$Inspector *  self, Vtable_Object *  vt);
void  SuiDesigner$Inspector$reactObject_byVtable(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  _obj, Vtable_Object *  vt, int  vtIdx);
void  SuiDesigner$Inspector$reactObjectField(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf);
void  SuiDesigner$Inspector$reactObjectFieldName(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf);
void  SuiDesigner$Inspector$reactObjectFieldRow(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf, void  (**renderBody)(void *  self, SuiCore$Node *  o));
void  SuiDesigner$Inspector$reactObjectField_do(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
