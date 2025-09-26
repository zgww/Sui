
typedef struct tagSuiDesigner$SpriteSheetPlayerView SuiDesigner$SpriteSheetPlayerView;
typedef struct tagVtable_SuiDesigner$SpriteSheetPlayerView Vtable_SuiDesigner$SpriteSheetPlayerView;
typedef struct tagSuiDesigner$SpriteSheetFrameCoord SuiDesigner$SpriteSheetFrameCoord;
typedef struct tagVtable_SuiDesigner$SpriteSheetFrameCoord Vtable_SuiDesigner$SpriteSheetFrameCoord;
typedef struct tagSuiDesigner$SpriteSheetAnim SuiDesigner$SpriteSheetAnim;
typedef struct tagVtable_SuiDesigner$SpriteSheetAnim Vtable_SuiDesigner$SpriteSheetAnim;
typedef struct tagSuiDesigner$SpriteSheetInfo SuiDesigner$SpriteSheetInfo;
typedef struct tagVtable_SuiDesigner$SpriteSheetInfo Vtable_SuiDesigner$SpriteSheetInfo;
typedef struct tagSuiDesigner$SpriteSheetEditor SuiDesigner$SpriteSheetEditor;
typedef struct tagVtable_SuiDesigner$SpriteSheetEditor Vtable_SuiDesigner$SpriteSheetEditor;


#ifndef define_struct___SuiDesigner__SpriteSheetEditor_orc_h__
#define define_struct___SuiDesigner__SpriteSheetEditor_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__SpriteSheetEditor_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__SpriteSheetEditor_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__SpriteSheetEditor_orc_h__
#define __SuiDesigner__SpriteSheetEditor_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/View/DockLayout_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "./ChessBgViewCallback_orc.h"
#include "./Theme_orc.h"
#include "./InvalidReact_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$SpriteSheetPlayerView {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiDesigner$SpriteSheetPlayerView _vtable_SuiDesigner$SpriteSheetPlayerView;

// class refc:0
struct tagSuiDesigner$SpriteSheetPlayerView {
	SuiCore$View super; 
	int  coordIndex ;
	SuiCore$Timer*  timer ;
	SuiCore$Image*  _img ;
	Orc$String*  src ;
	void  (*setSrc) (SuiDesigner$SpriteSheetPlayerView *  self, Orc$String*  src);
	bool  (*_isImageValid) (SuiDesigner$SpriteSheetPlayerView *  self);
	void  (*updateAnim) (SuiDesigner$SpriteSheetPlayerView *  self);
	Orc$String*  animName ;
	void  (*setAnimName) (SuiDesigner$SpriteSheetPlayerView *  self, Orc$String*  animName);
	SuiDesigner$SpriteSheetAnim*  _anim ;
	SuiDesigner$SpriteSheetInfo*  info ;
};
Vtable_SuiDesigner$SpriteSheetPlayerView* Vtable_SuiDesigner$SpriteSheetPlayerView_init(Vtable_SuiDesigner$SpriteSheetPlayerView* pvt);
void SuiDesigner$SpriteSheetPlayerView_init_fields(SuiDesigner$SpriteSheetPlayerView *self);
void SuiDesigner$SpriteSheetPlayerView_init(SuiDesigner$SpriteSheetPlayerView *self, void *pOwner);
SuiDesigner$SpriteSheetPlayerView * SuiDesigner$SpriteSheetPlayerView_new(void *pOwner);
void SuiDesigner$SpriteSheetPlayerView_fini(SuiDesigner$SpriteSheetPlayerView *self);

void  SuiDesigner$SpriteSheetPlayerView$ctor(SuiDesigner$SpriteSheetPlayerView *  self);
void  SuiDesigner$SpriteSheetPlayerView$onMounted(SuiDesigner$SpriteSheetPlayerView *  self);
void  SuiDesigner$SpriteSheetPlayerView$onUnmounting(SuiDesigner$SpriteSheetPlayerView *  self);
void  SuiDesigner$SpriteSheetPlayerView$draw_self(SuiDesigner$SpriteSheetPlayerView *  self, SuiCore$Canvas *  canvas);
void  SuiDesigner$SpriteSheetPlayerView$setSrc(SuiDesigner$SpriteSheetPlayerView *  self, Orc$String*  src);
bool  SuiDesigner$SpriteSheetPlayerView$_isImageValid(SuiDesigner$SpriteSheetPlayerView *  self);
void  SuiDesigner$SpriteSheetPlayerView$updateAnim(SuiDesigner$SpriteSheetPlayerView *  self);
void  SuiDesigner$SpriteSheetPlayerView$setAnimName(SuiDesigner$SpriteSheetPlayerView *  self, Orc$String*  animName);

SuiDesigner$SpriteSheetPlayerView*  SuiDesigner$mkSpriteSheetPlayerView(SuiDesigner$SpriteSheetPlayerView **  __outRef__, void *  parent, long long  key);

// 虚表
struct tagVtable_SuiDesigner$SpriteSheetFrameCoord {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SpriteSheetFrameCoord _vtable_SuiDesigner$SpriteSheetFrameCoord;

// class refc:1
struct tagSuiDesigner$SpriteSheetFrameCoord {
	Object super; 
	int  x ;
	int  y ;
	void  (*fromJson) (SuiDesigner$SpriteSheetFrameCoord *  self, Json$Json *  jo);
	void  (*toJson) (SuiDesigner$SpriteSheetFrameCoord *  self, Json$Json *  jo);
};
Vtable_SuiDesigner$SpriteSheetFrameCoord* Vtable_SuiDesigner$SpriteSheetFrameCoord_init(Vtable_SuiDesigner$SpriteSheetFrameCoord* pvt);
void SuiDesigner$SpriteSheetFrameCoord_init_fields(SuiDesigner$SpriteSheetFrameCoord *self);
void SuiDesigner$SpriteSheetFrameCoord_init(SuiDesigner$SpriteSheetFrameCoord *self, void *pOwner);
SuiDesigner$SpriteSheetFrameCoord * SuiDesigner$SpriteSheetFrameCoord_new(void *pOwner);
void SuiDesigner$SpriteSheetFrameCoord_fini(SuiDesigner$SpriteSheetFrameCoord *self);

void  SuiDesigner$SpriteSheetFrameCoord$fromJson(SuiDesigner$SpriteSheetFrameCoord *  self, Json$Json *  jo);
void  SuiDesigner$SpriteSheetFrameCoord$toJson(SuiDesigner$SpriteSheetFrameCoord *  self, Json$Json *  jo);


// 虚表
struct tagVtable_SuiDesigner$SpriteSheetAnim {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SpriteSheetAnim _vtable_SuiDesigner$SpriteSheetAnim;

// class refc:0
struct tagSuiDesigner$SpriteSheetAnim {
	Object super; 
	Orc$String*  name ;
	Orc$List*  coords ;
	void  (*fromJson) (SuiDesigner$SpriteSheetAnim *  self, Json$Json *  jo);
	void  (*toJson) (SuiDesigner$SpriteSheetAnim *  self, Json$Json *  jo);
	int  (*getIndexOfFrame) (SuiDesigner$SpriteSheetAnim *  self, int  x, int  y);
	void  (*addFrame) (SuiDesigner$SpriteSheetAnim *  self, int  x, int  y);
	void  (*removeFrame) (SuiDesigner$SpriteSheetAnim *  self, int  x, int  y);
};
Vtable_SuiDesigner$SpriteSheetAnim* Vtable_SuiDesigner$SpriteSheetAnim_init(Vtable_SuiDesigner$SpriteSheetAnim* pvt);
void SuiDesigner$SpriteSheetAnim_init_fields(SuiDesigner$SpriteSheetAnim *self);
void SuiDesigner$SpriteSheetAnim_init(SuiDesigner$SpriteSheetAnim *self, void *pOwner);
SuiDesigner$SpriteSheetAnim * SuiDesigner$SpriteSheetAnim_new(void *pOwner);
void SuiDesigner$SpriteSheetAnim_fini(SuiDesigner$SpriteSheetAnim *self);

void  SuiDesigner$SpriteSheetAnim$fromJson(SuiDesigner$SpriteSheetAnim *  self, Json$Json *  jo);
void  SuiDesigner$SpriteSheetAnim$toJson(SuiDesigner$SpriteSheetAnim *  self, Json$Json *  jo);
int  SuiDesigner$SpriteSheetAnim$getIndexOfFrame(SuiDesigner$SpriteSheetAnim *  self, int  x, int  y);
void  SuiDesigner$SpriteSheetAnim$addFrame(SuiDesigner$SpriteSheetAnim *  self, int  x, int  y);
void  SuiDesigner$SpriteSheetAnim$removeFrame(SuiDesigner$SpriteSheetAnim *  self, int  x, int  y);


// 虚表
struct tagVtable_SuiDesigner$SpriteSheetInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SpriteSheetInfo _vtable_SuiDesigner$SpriteSheetInfo;

// class refc:0
struct tagSuiDesigner$SpriteSheetInfo {
	Object super; 
	float  fps ;
	int  rows ;
	int  cols ;
	Orc$List*  anims ;
	SuiDesigner$SpriteSheetAnim*  (*getAnimByName) (SuiDesigner$SpriteSheetAnim **  __outRef__, SuiDesigner$SpriteSheetInfo *  self, const char *  name);
	void  (*fromJson) (SuiDesigner$SpriteSheetInfo *  self, Json$Json *  jo);
	void  (*toJson) (SuiDesigner$SpriteSheetInfo *  self, Json$Json *  jo);
};
Vtable_SuiDesigner$SpriteSheetInfo* Vtable_SuiDesigner$SpriteSheetInfo_init(Vtable_SuiDesigner$SpriteSheetInfo* pvt);
void SuiDesigner$SpriteSheetInfo_init_fields(SuiDesigner$SpriteSheetInfo *self);
void SuiDesigner$SpriteSheetInfo_init(SuiDesigner$SpriteSheetInfo *self, void *pOwner);
SuiDesigner$SpriteSheetInfo * SuiDesigner$SpriteSheetInfo_new(void *pOwner);
void SuiDesigner$SpriteSheetInfo_fini(SuiDesigner$SpriteSheetInfo *self);

SuiDesigner$SpriteSheetAnim*  SuiDesigner$SpriteSheetInfo$getAnimByName(SuiDesigner$SpriteSheetAnim **  __outRef__, SuiDesigner$SpriteSheetInfo *  self, const char *  name);
void  SuiDesigner$SpriteSheetInfo$fromJson(SuiDesigner$SpriteSheetInfo *  self, Json$Json *  jo);
void  SuiDesigner$SpriteSheetInfo$toJson(SuiDesigner$SpriteSheetInfo *  self, Json$Json *  jo);


// 虚表
struct tagVtable_SuiDesigner$SpriteSheetEditor {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SpriteSheetEditor _vtable_SuiDesigner$SpriteSheetEditor;

// class refc:0
struct tagSuiDesigner$SpriteSheetEditor {
	Object super; 
	Sui$Window*  win ;
	SuiView$Drag*  drag ;
	SuiView$Drag*  dragPreview ;
	SuiView$Drag*  dragChoose ;
	SuiLayout$LayoutAlignPositionCell*  imgCell ;
	SuiLayout$LayoutAlignPositionCell*  previewCell ;
	SuiDesigner$InvalidReact*  invalidReact ;
	Orc$String*  path ;
	SuiDesigner$SpriteSheetInfo*  info ;
	SuiDesigner$SpriteSheetAnim*  curAnim ;
	SuiView$ImageView*  sceneImageView ;
	SuiDesigner$SpriteSheetPlayerView*  playerView ;
	void  (*printSceneTree) (SuiDesigner$SpriteSheetEditor *  self);
	int  (*getFrameIndex) (SuiDesigner$SpriteSheetEditor *  self, int  x, int  y);
	void  (*removeCurAnim) (SuiDesigner$SpriteSheetEditor *  self);
	SuiDesigner$ChessBgViewCallback*  chessBg ;
	SuiCore$ViewBase *  (*reactPreview) (SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*showDialog_rename) (SuiDesigner$SpriteSheetEditor *  self, SuiDesigner$SpriteSheetAnim*  anim);
	SuiCore$ViewBase *  (*reactAnimNames) (SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	SuiCore$ViewBase *  (*reactScene) (SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*react) (SuiDesigner$SpriteSheetEditor *  self);
	void  (*playCurAnim) (SuiDesigner$SpriteSheetEditor *  self);
	void  (*showWindow) (SuiDesigner$SpriteSheetEditor *  self);
};
Vtable_SuiDesigner$SpriteSheetEditor* Vtable_SuiDesigner$SpriteSheetEditor_init(Vtable_SuiDesigner$SpriteSheetEditor* pvt);
void SuiDesigner$SpriteSheetEditor_init_fields(SuiDesigner$SpriteSheetEditor *self);
void SuiDesigner$SpriteSheetEditor_init(SuiDesigner$SpriteSheetEditor *self, void *pOwner);
SuiDesigner$SpriteSheetEditor * SuiDesigner$SpriteSheetEditor_new(void *pOwner);
void SuiDesigner$SpriteSheetEditor_fini(SuiDesigner$SpriteSheetEditor *self);

void  SuiDesigner$SpriteSheetEditor$printSceneTree(SuiDesigner$SpriteSheetEditor *  self);
int  SuiDesigner$SpriteSheetEditor$getFrameIndex(SuiDesigner$SpriteSheetEditor *  self, int  x, int  y);
void  SuiDesigner$SpriteSheetEditor$ctor(SuiDesigner$SpriteSheetEditor *  self);
void  SuiDesigner$SpriteSheetEditor$removeCurAnim(SuiDesigner$SpriteSheetEditor *  self);
SuiCore$ViewBase *  SuiDesigner$SpriteSheetEditor$reactPreview(SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner$SpriteSheetEditor$showDialog_rename(SuiDesigner$SpriteSheetEditor *  self, SuiDesigner$SpriteSheetAnim*  anim);
SuiCore$ViewBase *  SuiDesigner$SpriteSheetEditor$reactAnimNames(SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
SuiCore$ViewBase *  SuiDesigner$SpriteSheetEditor$reactScene(SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner$SpriteSheetEditor$react(SuiDesigner$SpriteSheetEditor *  self);
void  SuiDesigner$SpriteSheetEditor$playCurAnim(SuiDesigner$SpriteSheetEditor *  self);
void  SuiDesigner$SpriteSheetEditor$showWindow(SuiDesigner$SpriteSheetEditor *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
