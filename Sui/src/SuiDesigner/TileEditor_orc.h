
typedef struct tagSuiDesigner$Tile SuiDesigner$Tile;
typedef struct tagVtable_SuiDesigner$Tile Vtable_SuiDesigner$Tile;
typedef struct tagSuiDesigner$SpecialTile SuiDesigner$SpecialTile;
typedef struct tagVtable_SuiDesigner$SpecialTile Vtable_SuiDesigner$SpecialTile;
typedef struct tagSuiDesigner$RuleInfo SuiDesigner$RuleInfo;
typedef struct tagVtable_SuiDesigner$RuleInfo Vtable_SuiDesigner$RuleInfo;
typedef struct tagSuiDesigner$AutoTile SuiDesigner$AutoTile;
typedef struct tagVtable_SuiDesigner$AutoTile Vtable_SuiDesigner$AutoTile;
typedef struct tagSuiDesigner$RandomTile SuiDesigner$RandomTile;
typedef struct tagVtable_SuiDesigner$RandomTile Vtable_SuiDesigner$RandomTile;
typedef struct tagSuiDesigner$AnimTile SuiDesigner$AnimTile;
typedef struct tagVtable_SuiDesigner$AnimTile Vtable_SuiDesigner$AnimTile;
typedef struct tagSuiDesigner$Tileset SuiDesigner$Tileset;
typedef struct tagVtable_SuiDesigner$Tileset Vtable_SuiDesigner$Tileset;
typedef struct tagSuiDesigner$Layer SuiDesigner$Layer;
typedef struct tagVtable_SuiDesigner$Layer Vtable_SuiDesigner$Layer;
typedef struct tagSuiDesigner$TileLayer SuiDesigner$TileLayer;
typedef struct tagVtable_SuiDesigner$TileLayer Vtable_SuiDesigner$TileLayer;
typedef struct tagSuiDesigner$TileMap SuiDesigner$TileMap;
typedef struct tagVtable_SuiDesigner$TileMap Vtable_SuiDesigner$TileMap;
typedef struct tagSuiDesigner$ElapsedMs SuiDesigner$ElapsedMs;
typedef struct tagVtable_SuiDesigner$ElapsedMs Vtable_SuiDesigner$ElapsedMs;
typedef struct tagSuiDesigner$TileMapEditView SuiDesigner$TileMapEditView;
typedef struct tagVtable_SuiDesigner$TileMapEditView Vtable_SuiDesigner$TileMapEditView;
typedef struct tagSuiDesigner$SceneViewCb SuiDesigner$SceneViewCb;
typedef struct tagVtable_SuiDesigner$SceneViewCb Vtable_SuiDesigner$SceneViewCb;
typedef struct tagSuiDesigner$SceneCtrl SuiDesigner$SceneCtrl;
typedef struct tagVtable_SuiDesigner$SceneCtrl Vtable_SuiDesigner$SceneCtrl;
typedef struct tagSuiDesigner$TileEditor SuiDesigner$TileEditor;
typedef struct tagVtable_SuiDesigner$TileEditor Vtable_SuiDesigner$TileEditor;


#ifndef define_struct___SuiDesigner__TileEditor_orc_h__
#define define_struct___SuiDesigner__TileEditor_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__TileEditor_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__TileEditor_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__TileEditor_orc_h__
#define __SuiDesigner__TileEditor_orc_h__

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
#include "../Sui/Core/Mat2d_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Mouse_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Dialog/FileDialog_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/View/DockLayout_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "./ChessBgViewCallback_orc.h"
#include "./Theme_orc.h"
#include "./InvalidReact_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$Tile {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Tile _vtable_SuiDesigner$Tile;

// class refc:1
struct tagSuiDesigner$Tile {
	Object super; 
	int  gid ;
};
Vtable_SuiDesigner$Tile* Vtable_SuiDesigner$Tile_init(Vtable_SuiDesigner$Tile* pvt);
void SuiDesigner$Tile_init_fields(SuiDesigner$Tile *self);
void SuiDesigner$Tile_init(SuiDesigner$Tile *self, void *pOwner);
SuiDesigner$Tile * SuiDesigner$Tile_new(void *pOwner);
void SuiDesigner$Tile_fini(SuiDesigner$Tile *self);



// 虚表
struct tagVtable_SuiDesigner$SpecialTile {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SpecialTile _vtable_SuiDesigner$SpecialTile;

// class refc:1
struct tagSuiDesigner$SpecialTile {
	Object super; 
	int  (*getGid) (SuiDesigner$SpecialTile *  self);
	void  (*setTileAtGid) (SuiDesigner$SpecialTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex);
};
Vtable_SuiDesigner$SpecialTile* Vtable_SuiDesigner$SpecialTile_init(Vtable_SuiDesigner$SpecialTile* pvt);
void SuiDesigner$SpecialTile_init_fields(SuiDesigner$SpecialTile *self);
void SuiDesigner$SpecialTile_init(SuiDesigner$SpecialTile *self, void *pOwner);
SuiDesigner$SpecialTile * SuiDesigner$SpecialTile_new(void *pOwner);
void SuiDesigner$SpecialTile_fini(SuiDesigner$SpecialTile *self);

int  SuiDesigner$SpecialTile$getGid(SuiDesigner$SpecialTile *  self);
void  SuiDesigner$SpecialTile$setTileAtGid(SuiDesigner$SpecialTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex);


// 虚表
struct tagVtable_SuiDesigner$RuleInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$RuleInfo _vtable_SuiDesigner$RuleInfo;

// class refc:0
struct tagSuiDesigner$RuleInfo {
	Object super; 
	int  gid ;
	int  cid ;
	Sgl$IntArray*  neighborIdArr ;
	int  ruleInt ;
	bool  (*hasByNeighPos) (SuiDesigner$RuleInfo *  self, SuiDesigner$Tileset *  ts, int  x, int  y);
	void  (*buildRuleInt) (SuiDesigner$RuleInfo *  self, SuiDesigner$Tileset *  ts);
};
Vtable_SuiDesigner$RuleInfo* Vtable_SuiDesigner$RuleInfo_init(Vtable_SuiDesigner$RuleInfo* pvt);
void SuiDesigner$RuleInfo_init_fields(SuiDesigner$RuleInfo *self);
void SuiDesigner$RuleInfo_init(SuiDesigner$RuleInfo *self, void *pOwner);
SuiDesigner$RuleInfo * SuiDesigner$RuleInfo_new(void *pOwner);
void SuiDesigner$RuleInfo_fini(SuiDesigner$RuleInfo *self);

bool  SuiDesigner$RuleInfo$hasByNeighPos(SuiDesigner$RuleInfo *  self, SuiDesigner$Tileset *  ts, int  x, int  y);
void  SuiDesigner$RuleInfo$buildRuleInt(SuiDesigner$RuleInfo *  self, SuiDesigner$Tileset *  ts);

int  SuiDesigner$RuleInfo_mkRuleInt(bool  lt, bool  ct, bool  rt, bool  lm, bool  cm, bool  rm, bool  lb, bool  cb, bool  rb);

// 虚表
struct tagVtable_SuiDesigner$AutoTile {
	Vtable_SuiDesigner$SpecialTile super;
};
//虚表实例
extern Vtable_SuiDesigner$AutoTile _vtable_SuiDesigner$AutoTile;

// class refc:0
struct tagSuiDesigner$AutoTile {
	SuiDesigner$SpecialTile super; 
	int  gid ;
	Sgl$IntArray*  neighborIdArr ;
	int  (*neighborIdToCid) (SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts, int  neighborId);
	int  (*neighborIdToGid) (SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, int  neighborId);
	bool  (*isAutoTileByGid) (SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts, int  gid);
	bool  (*isAutoTileByLayerPos) (SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  x, int  y);
	int  (*getMatchedRuleGid) (SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex);
	Orc$List*  ruleInfos ;
	SuiDesigner$RuleInfo *  (*gocRuleInfoByCid) (SuiDesigner$AutoTile *  self, int  cid);
	SuiDesigner$RuleInfo *  (*findRuleInfoByCid) (SuiDesigner$AutoTile *  self, int  cid);
	void  (*buildRuleInfos) (SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts);
	int  (*mkRuleIntOfTile) (SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  cellIndex);
};
Vtable_SuiDesigner$AutoTile* Vtable_SuiDesigner$AutoTile_init(Vtable_SuiDesigner$AutoTile* pvt);
void SuiDesigner$AutoTile_init_fields(SuiDesigner$AutoTile *self);
void SuiDesigner$AutoTile_init(SuiDesigner$AutoTile *self, void *pOwner);
SuiDesigner$AutoTile * SuiDesigner$AutoTile_new(void *pOwner);
void SuiDesigner$AutoTile_fini(SuiDesigner$AutoTile *self);

int  SuiDesigner$AutoTile$getGid(SuiDesigner$AutoTile *  self);
int  SuiDesigner$AutoTile$neighborIdToCid(SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts, int  neighborId);
int  SuiDesigner$AutoTile$neighborIdToGid(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, int  neighborId);
bool  SuiDesigner$AutoTile$isAutoTileByGid(SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts, int  gid);
bool  SuiDesigner$AutoTile$isAutoTileByLayerPos(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  x, int  y);
void  SuiDesigner$AutoTile$setTileAtGid(SuiDesigner$AutoTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex);
int  SuiDesigner$AutoTile$getMatchedRuleGid(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex);
SuiDesigner$RuleInfo *  SuiDesigner$AutoTile$gocRuleInfoByCid(SuiDesigner$AutoTile *  self, int  cid);
SuiDesigner$RuleInfo *  SuiDesigner$AutoTile$findRuleInfoByCid(SuiDesigner$AutoTile *  self, int  cid);
void  SuiDesigner$AutoTile$buildRuleInfos(SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts);
int  SuiDesigner$AutoTile$mkRuleIntOfTile(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  cellIndex);


// 虚表
struct tagVtable_SuiDesigner$RandomTile {
	Vtable_SuiDesigner$SpecialTile super;
};
//虚表实例
extern Vtable_SuiDesigner$RandomTile _vtable_SuiDesigner$RandomTile;

// class refc:0
struct tagSuiDesigner$RandomTile {
	SuiDesigner$SpecialTile super; 
	Sgl$IntArray*  gidArr ;
};
Vtable_SuiDesigner$RandomTile* Vtable_SuiDesigner$RandomTile_init(Vtable_SuiDesigner$RandomTile* pvt);
void SuiDesigner$RandomTile_init_fields(SuiDesigner$RandomTile *self);
void SuiDesigner$RandomTile_init(SuiDesigner$RandomTile *self, void *pOwner);
SuiDesigner$RandomTile * SuiDesigner$RandomTile_new(void *pOwner);
void SuiDesigner$RandomTile_fini(SuiDesigner$RandomTile *self);

int  SuiDesigner$RandomTile$getGid(SuiDesigner$RandomTile *  self);
void  SuiDesigner$RandomTile$setTileAtGid(SuiDesigner$RandomTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  tileLayer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex);


// 虚表
struct tagVtable_SuiDesigner$AnimTile {
	Vtable_SuiDesigner$SpecialTile super;
};
//虚表实例
extern Vtable_SuiDesigner$AnimTile _vtable_SuiDesigner$AnimTile;

// class refc:0
struct tagSuiDesigner$AnimTile {
	SuiDesigner$SpecialTile super; 
	Sgl$IntArray*  gidArr ;
	int  (*getDrawGid) (SuiDesigner$AnimTile *  self, int  frameId);
};
Vtable_SuiDesigner$AnimTile* Vtable_SuiDesigner$AnimTile_init(Vtable_SuiDesigner$AnimTile* pvt);
void SuiDesigner$AnimTile_init_fields(SuiDesigner$AnimTile *self);
void SuiDesigner$AnimTile_init(SuiDesigner$AnimTile *self, void *pOwner);
SuiDesigner$AnimTile * SuiDesigner$AnimTile_new(void *pOwner);
void SuiDesigner$AnimTile_fini(SuiDesigner$AnimTile *self);

int  SuiDesigner$AnimTile$getGid(SuiDesigner$AnimTile *  self);
void  SuiDesigner$AnimTile$setTileAtGid(SuiDesigner$AnimTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  tileLayer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex);
int  SuiDesigner$AnimTile$getDrawGid(SuiDesigner$AnimTile *  self, int  frameId);


// 虚表
struct tagVtable_SuiDesigner$Tileset {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Tileset _vtable_SuiDesigner$Tileset;

// class refc:0
struct tagSuiDesigner$Tileset {
	Object super; 
	Orc$String*  imgPath ;
	int  startGid ;
	int  rows ;
	int  cols ;
	SuiCore$Vec2 _imgSize ;
	int  _tileWidth ;
	int  _tileHeight ;
	Orc$List*  specialTiles ;
	SuiDesigner$SpecialTile *  (*getSpecialTileAtGid) (SuiDesigner$Tileset *  self, int  gid);
	void  (*fromJson) (SuiDesigner$Tileset *  self, Json$Json *  jo);
	void  (*toJson) (SuiDesigner$Tileset *  self, Json$Json *  jo);
	int  (*calcEndGid) (SuiDesigner$Tileset *  self);
	bool  (*isGidBelong) (SuiDesigner$Tileset *  self, int  gid);
	int  (*calcGid) (SuiDesigner$Tileset *  self, SuiCore$Vec2 gridPos);
	SuiCore$Vec2 (*dissolveGidToGridPos) (SuiDesigner$Tileset *  self, int  gid);
	SuiCore$Image*  img ;
	SuiCore$Image *  (*loadImage) (SuiDesigner$Tileset *  self);
	void  (*calcRowsCols) (SuiDesigner$Tileset *  self, SuiCore$Vec2 imgSize, int  tileWidth, int  tileHeight);
};
Vtable_SuiDesigner$Tileset* Vtable_SuiDesigner$Tileset_init(Vtable_SuiDesigner$Tileset* pvt);
void SuiDesigner$Tileset_init_fields(SuiDesigner$Tileset *self);
void SuiDesigner$Tileset_init(SuiDesigner$Tileset *self, void *pOwner);
SuiDesigner$Tileset * SuiDesigner$Tileset_new(void *pOwner);
void SuiDesigner$Tileset_fini(SuiDesigner$Tileset *self);

SuiDesigner$SpecialTile *  SuiDesigner$Tileset$getSpecialTileAtGid(SuiDesigner$Tileset *  self, int  gid);
void  SuiDesigner$Tileset$fromJson(SuiDesigner$Tileset *  self, Json$Json *  jo);
void  SuiDesigner$Tileset$toJson(SuiDesigner$Tileset *  self, Json$Json *  jo);
int  SuiDesigner$Tileset$calcEndGid(SuiDesigner$Tileset *  self);
bool  SuiDesigner$Tileset$isGidBelong(SuiDesigner$Tileset *  self, int  gid);
int  SuiDesigner$Tileset$calcGid(SuiDesigner$Tileset *  self, SuiCore$Vec2 gridPos);
SuiCore$Vec2 SuiDesigner$Tileset$dissolveGidToGridPos(SuiDesigner$Tileset *  self, int  gid);
SuiCore$Image *  SuiDesigner$Tileset$loadImage(SuiDesigner$Tileset *  self);
void  SuiDesigner$Tileset$calcRowsCols(SuiDesigner$Tileset *  self, SuiCore$Vec2 imgSize, int  tileWidth, int  tileHeight);


// 虚表
struct tagVtable_SuiDesigner$Layer {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Layer _vtable_SuiDesigner$Layer;

// class refc:0
struct tagSuiDesigner$Layer {
	Object super; 
	Orc$String*  name ;
	void  (*fromJson) (SuiDesigner$Layer *  self, Json$Json *  jo);
	void  (*toJson) (SuiDesigner$Layer *  self, Json$Json *  jo);
};
Vtable_SuiDesigner$Layer* Vtable_SuiDesigner$Layer_init(Vtable_SuiDesigner$Layer* pvt);
void SuiDesigner$Layer_init_fields(SuiDesigner$Layer *self);
void SuiDesigner$Layer_init(SuiDesigner$Layer *self, void *pOwner);
SuiDesigner$Layer * SuiDesigner$Layer_new(void *pOwner);
void SuiDesigner$Layer_fini(SuiDesigner$Layer *self);

void  SuiDesigner$Layer$fromJson(SuiDesigner$Layer *  self, Json$Json *  jo);
void  SuiDesigner$Layer$toJson(SuiDesigner$Layer *  self, Json$Json *  jo);


// 虚表
struct tagVtable_SuiDesigner$TileLayer {
	Vtable_SuiDesigner$Layer super;
};
//虚表实例
extern Vtable_SuiDesigner$TileLayer _vtable_SuiDesigner$TileLayer;

// class refc:0
struct tagSuiDesigner$TileLayer {
	SuiDesigner$Layer super; 
	Sgl$IntArray*  data ;
};
Vtable_SuiDesigner$TileLayer* Vtable_SuiDesigner$TileLayer_init(Vtable_SuiDesigner$TileLayer* pvt);
void SuiDesigner$TileLayer_init_fields(SuiDesigner$TileLayer *self);
void SuiDesigner$TileLayer_init(SuiDesigner$TileLayer *self, void *pOwner);
SuiDesigner$TileLayer * SuiDesigner$TileLayer_new(void *pOwner);
void SuiDesigner$TileLayer_fini(SuiDesigner$TileLayer *self);

void  SuiDesigner$TileLayer$fromJson(SuiDesigner$TileLayer *  self, Json$Json *  jo);
void  SuiDesigner$TileLayer$toJson(SuiDesigner$TileLayer *  self, Json$Json *  jo);


// 虚表
struct tagVtable_SuiDesigner$TileMap {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$TileMap _vtable_SuiDesigner$TileMap;

// class refc:0
struct tagSuiDesigner$TileMap {
	Object super; 
	int  fps ;
	int  width ;
	int  height ;
	int  tileWidth ;
	int  tileHeight ;
	Orc$List*  tilesets ;
	Orc$List*  layers ;
	void  (*fromJson) (SuiDesigner$TileMap *  self, Json$Json *  jo);
	void  (*toJson) (SuiDesigner$TileMap *  self, Json$Json *  jo);
	SuiDesigner$Tileset *  (*findTilesetByGid) (SuiDesigner$TileMap *  self, int  gid);
	int  (*findFreeStartGid) (SuiDesigner$TileMap *  self);
};
Vtable_SuiDesigner$TileMap* Vtable_SuiDesigner$TileMap_init(Vtable_SuiDesigner$TileMap* pvt);
void SuiDesigner$TileMap_init_fields(SuiDesigner$TileMap *self);
void SuiDesigner$TileMap_init(SuiDesigner$TileMap *self, void *pOwner);
SuiDesigner$TileMap * SuiDesigner$TileMap_new(void *pOwner);
void SuiDesigner$TileMap_fini(SuiDesigner$TileMap *self);

void  SuiDesigner$TileMap$fromJson(SuiDesigner$TileMap *  self, Json$Json *  jo);
void  SuiDesigner$TileMap$toJson(SuiDesigner$TileMap *  self, Json$Json *  jo);
void  SuiDesigner$TileMap$ctor(SuiDesigner$TileMap *  self);
SuiDesigner$Tileset *  SuiDesigner$TileMap$findTilesetByGid(SuiDesigner$TileMap *  self, int  gid);
int  SuiDesigner$TileMap$findFreeStartGid(SuiDesigner$TileMap *  self);


// 虚表
struct tagVtable_SuiDesigner$ElapsedMs {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ElapsedMs _vtable_SuiDesigner$ElapsedMs;

// class refc:1
struct tagSuiDesigner$ElapsedMs {
	Object super; 
	long long  prevMs ;
	long long  accumMs ;
	void  (*tick) (SuiDesigner$ElapsedMs *  self);
	long long  (*calcFrameIndex) (SuiDesigner$ElapsedMs *  self, int  fps);
};
Vtable_SuiDesigner$ElapsedMs* Vtable_SuiDesigner$ElapsedMs_init(Vtable_SuiDesigner$ElapsedMs* pvt);
void SuiDesigner$ElapsedMs_init_fields(SuiDesigner$ElapsedMs *self);
void SuiDesigner$ElapsedMs_init(SuiDesigner$ElapsedMs *self, void *pOwner);
SuiDesigner$ElapsedMs * SuiDesigner$ElapsedMs_new(void *pOwner);
void SuiDesigner$ElapsedMs_fini(SuiDesigner$ElapsedMs *self);

void  SuiDesigner$ElapsedMs$tick(SuiDesigner$ElapsedMs *  self);
long long  SuiDesigner$ElapsedMs$calcFrameIndex(SuiDesigner$ElapsedMs *  self, int  fps);


// 虚表
struct tagVtable_SuiDesigner$TileMapEditView {
	Vtable_SuiCore$ViewBase super;
};
//虚表实例
extern Vtable_SuiDesigner$TileMapEditView _vtable_SuiDesigner$TileMapEditView;

// class refc:0
struct tagSuiDesigner$TileMapEditView {
	SuiCore$ViewBase super; 
	SuiDesigner$TileMap*  map ;
	SuiCore$ViewBase*  viewportView ;
	SuiCore$Vec2 mousePosInViewport ;
	SuiDesigner$SceneCtrl*  sceneCtrl ;
	SuiDesigner$TileEditor*  tileEditor ;
	SuiView$Drag*  drag ;
	SuiDesigner$ElapsedMs*  elapsedMs ;
	SuiCore$Vec2 (*getMouseScenePos) (SuiDesigner$TileMapEditView *  self);
	void  (*setTileAtGrid) (SuiDesigner$TileMapEditView *  self, SuiCore$Vec2 gridPos);
	int  (*gridPosToCellIndex) (SuiDesigner$TileMapEditView *  self, SuiCore$Vec2 gridPos);
	bool  (*onViewportEvent) (SuiDesigner$TileMapEditView *  self, SuiCore$Event *  e);
	SuiCore$Vec2 (*calcMouseGridPos) (SuiDesigner$TileMapEditView *  self);
	void  (*draw_tileLayer) (SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas, SuiDesigner$TileLayer *  layer);
	void  (*draw_map) (SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas);
};
Vtable_SuiDesigner$TileMapEditView* Vtable_SuiDesigner$TileMapEditView_init(Vtable_SuiDesigner$TileMapEditView* pvt);
void SuiDesigner$TileMapEditView_init_fields(SuiDesigner$TileMapEditView *self);
void SuiDesigner$TileMapEditView_init(SuiDesigner$TileMapEditView *self, void *pOwner);
SuiDesigner$TileMapEditView * SuiDesigner$TileMapEditView_new(void *pOwner);
void SuiDesigner$TileMapEditView_fini(SuiDesigner$TileMapEditView *self);

void  SuiDesigner$TileMapEditView$ctor(SuiDesigner$TileMapEditView *  self);
SuiCore$Vec2 SuiDesigner$TileMapEditView$getMouseScenePos(SuiDesigner$TileMapEditView *  self);
void  SuiDesigner$TileMapEditView$setTileAtGrid(SuiDesigner$TileMapEditView *  self, SuiCore$Vec2 gridPos);
int  SuiDesigner$TileMapEditView$gridPosToCellIndex(SuiDesigner$TileMapEditView *  self, SuiCore$Vec2 gridPos);
bool  SuiDesigner$TileMapEditView$onViewportEvent(SuiDesigner$TileMapEditView *  self, SuiCore$Event *  e);
SuiCore$Vec2 SuiDesigner$TileMapEditView$calcMouseGridPos(SuiDesigner$TileMapEditView *  self);
void  SuiDesigner$TileMapEditView$draw_tileLayer(SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas, SuiDesigner$TileLayer *  layer);
void  SuiDesigner$TileMapEditView$draw_map(SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas);
void  SuiDesigner$TileMapEditView$draw_self(SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas);

SuiDesigner$TileMapEditView*  SuiDesigner$mkTileMapEditView(SuiDesigner$TileMapEditView **  __outRef__, void *  parent, long long  key);

// 虚表
struct tagVtable_SuiDesigner$SceneViewCb {
	Vtable_SuiDesigner$ChessBgViewCallback super;
};
//虚表实例
extern Vtable_SuiDesigner$SceneViewCb _vtable_SuiDesigner$SceneViewCb;

// class refc:0
struct tagSuiDesigner$SceneViewCb {
	SuiDesigner$ChessBgViewCallback super; 
	SuiDesigner$SceneCtrl*  ctrl ;
};
Vtable_SuiDesigner$SceneViewCb* Vtable_SuiDesigner$SceneViewCb_init(Vtable_SuiDesigner$SceneViewCb* pvt);
void SuiDesigner$SceneViewCb_init_fields(SuiDesigner$SceneViewCb *self);
void SuiDesigner$SceneViewCb_init(SuiDesigner$SceneViewCb *self, void *pOwner);
SuiDesigner$SceneViewCb * SuiDesigner$SceneViewCb_new(void *pOwner);
void SuiDesigner$SceneViewCb_fini(SuiDesigner$SceneViewCb *self);

void  SuiDesigner$SceneViewCb$afterDrawSelf(SuiDesigner$SceneViewCb *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas);


// 虚表
struct tagVtable_SuiDesigner$SceneCtrl {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$SceneCtrl _vtable_SuiDesigner$SceneCtrl;

// class refc:0
struct tagSuiDesigner$SceneCtrl {
	Object super; 
	SuiCore$Vec3 _translate ;
	float  _scale ;
	SuiCore$Mat2d mat ;
	SuiView$Drag*  drag ;
	SuiDesigner$DrawDegree*  degree ;
	SuiCore$View*  contentView ;
	SuiDesigner$SceneViewCb*  sceneViewCb ;
	bool  (*onEvent) (SuiDesigner$SceneCtrl *  self, SuiCore$Event *  e);
	void  (*setScale) (SuiDesigner$SceneCtrl *  self, float  s);
	void  (*updateMat) (SuiDesigner$SceneCtrl *  self);
	SuiCore$Vec2 (*localToWorld) (SuiDesigner$SceneCtrl *  self, float  x, float  y);
	SuiCore$Vec2 (*worldToLocal) (SuiDesigner$SceneCtrl *  self, float  x, float  y);
	SuiCore$Vec2 (*clientToWorld) (SuiDesigner$SceneCtrl *  self, float  x, float  y);
	SuiCore$Vec2 (*clientToLocal) (SuiDesigner$SceneCtrl *  self, float  x, float  y);
	void  (*translate) (SuiDesigner$SceneCtrl *  self, float  x, float  y, float  z);
	void  (*setTranslate) (SuiDesigner$SceneCtrl *  self, float  x, float  y, float  z);
	void  (*identity) (SuiDesigner$SceneCtrl *  self);
	void  (*performScaleByWheelEventAndSceneView) (SuiDesigner$SceneCtrl *  self, SuiCore$WheelEvent *  we, SuiCore$ViewBase *  v);
};
Vtable_SuiDesigner$SceneCtrl* Vtable_SuiDesigner$SceneCtrl_init(Vtable_SuiDesigner$SceneCtrl* pvt);
void SuiDesigner$SceneCtrl_init_fields(SuiDesigner$SceneCtrl *self);
void SuiDesigner$SceneCtrl_init(SuiDesigner$SceneCtrl *self, void *pOwner);
SuiDesigner$SceneCtrl * SuiDesigner$SceneCtrl_new(void *pOwner);
void SuiDesigner$SceneCtrl_fini(SuiDesigner$SceneCtrl *self);

void  SuiDesigner$SceneCtrl$ctor(SuiDesigner$SceneCtrl *  self);
bool  SuiDesigner$SceneCtrl$onEvent(SuiDesigner$SceneCtrl *  self, SuiCore$Event *  e);
void  SuiDesigner$SceneCtrl$setScale(SuiDesigner$SceneCtrl *  self, float  s);
void  SuiDesigner$SceneCtrl$updateMat(SuiDesigner$SceneCtrl *  self);
SuiCore$Vec2 SuiDesigner$SceneCtrl$localToWorld(SuiDesigner$SceneCtrl *  self, float  x, float  y);
SuiCore$Vec2 SuiDesigner$SceneCtrl$worldToLocal(SuiDesigner$SceneCtrl *  self, float  x, float  y);
SuiCore$Vec2 SuiDesigner$SceneCtrl$clientToWorld(SuiDesigner$SceneCtrl *  self, float  x, float  y);
SuiCore$Vec2 SuiDesigner$SceneCtrl$clientToLocal(SuiDesigner$SceneCtrl *  self, float  x, float  y);
void  SuiDesigner$SceneCtrl$translate(SuiDesigner$SceneCtrl *  self, float  x, float  y, float  z);
void  SuiDesigner$SceneCtrl$setTranslate(SuiDesigner$SceneCtrl *  self, float  x, float  y, float  z);
void  SuiDesigner$SceneCtrl$identity(SuiDesigner$SceneCtrl *  self);
void  SuiDesigner$SceneCtrl$performScaleByWheelEventAndSceneView(SuiDesigner$SceneCtrl *  self, SuiCore$WheelEvent *  we, SuiCore$ViewBase *  v);


// 虚表
struct tagVtable_SuiDesigner$TileEditor {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$TileEditor _vtable_SuiDesigner$TileEditor;

// class refc:0
struct tagSuiDesigner$TileEditor {
	Object super; 
	Sui$Window*  win ;
	SuiLayout$LayoutAlignPositionCell*  imgCell ;
	SuiLayout$LayoutAlignPositionCell*  previewCell ;
	SuiDesigner$InvalidReact*  invalidReact ;
	Orc$String*  path ;
	SuiDesigner$TileMap*  map ;
	SuiDesigner$Layer*  curLayer ;
	SuiDesigner$Tileset*  curTileset ;
	SuiDesigner$AutoTile*  editingAutoTile ;
	Orc$String*  tilesetStatus ;
	SuiDesigner$SceneCtrl*  tilesetSceneCtrl ;
	SuiDesigner$SceneCtrl*  sceneCtrl ;
	SuiDesigner$TileMapEditView*  tileMapEditView ;
	Sgl$Vec2Array*  curTilePosArr ;
	SuiView$Drag*  tilesetDrag ;
	void  (*editAutoTile) (SuiDesigner$TileEditor *  self, SuiDesigner$AutoTile *  at);
	void  (*printSceneTree) (SuiDesigner$TileEditor *  self);
	int  (*getFrameIndex) (SuiDesigner$TileEditor *  self, int  x, int  y);
	SuiDesigner$ChessBgViewCallback*  chessBg ;
	void  (*ui_addtileset) (SuiDesigner$TileEditor *  self);
	void  (*addTileLayer) (SuiDesigner$TileEditor *  self);
	void  (*delLayer) (SuiDesigner$TileEditor *  self, SuiDesigner$Layer *  layer);
	SuiCore$ViewBase *  (*reactPreview) (SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*showDialog_renameLayer) (SuiDesigner$TileEditor *  self, SuiDesigner$Layer*  layer);
	SuiCore$ViewBase *  (*reactTilesetsNames) (SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	SuiCore$ViewBase *  (*reactLayers) (SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	SuiCore$ViewBase *  (*reactScene) (SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	SuiCore$ViewBase *  (*reactTilesetView) (SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
	void  (*ui_createAnimTile) (SuiDesigner$TileEditor *  self);
	void  (*ui_createRandomTile) (SuiDesigner$TileEditor *  self);
	void  (*ui_createAutoTile) (SuiDesigner$TileEditor *  self);
	void  (*react) (SuiDesigner$TileEditor *  self);
	void  (*showWindow_mapSetting) (SuiDesigner$TileEditor *  self);
	void  (*showWindow) (SuiDesigner$TileEditor *  self);
};
Vtable_SuiDesigner$TileEditor* Vtable_SuiDesigner$TileEditor_init(Vtable_SuiDesigner$TileEditor* pvt);
void SuiDesigner$TileEditor_init_fields(SuiDesigner$TileEditor *self);
void SuiDesigner$TileEditor_init(SuiDesigner$TileEditor *self, void *pOwner);
SuiDesigner$TileEditor * SuiDesigner$TileEditor_new(void *pOwner);
void SuiDesigner$TileEditor_fini(SuiDesigner$TileEditor *self);

void  SuiDesigner$TileEditor$editAutoTile(SuiDesigner$TileEditor *  self, SuiDesigner$AutoTile *  at);
void  SuiDesigner$TileEditor$printSceneTree(SuiDesigner$TileEditor *  self);
int  SuiDesigner$TileEditor$getFrameIndex(SuiDesigner$TileEditor *  self, int  x, int  y);
void  SuiDesigner$TileEditor$ctor(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$ui_addtileset(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$addTileLayer(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$delLayer(SuiDesigner$TileEditor *  self, SuiDesigner$Layer *  layer);
SuiCore$ViewBase *  SuiDesigner$TileEditor$reactPreview(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner$TileEditor$showDialog_renameLayer(SuiDesigner$TileEditor *  self, SuiDesigner$Layer*  layer);
SuiCore$ViewBase *  SuiDesigner$TileEditor$reactTilesetsNames(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
SuiCore$ViewBase *  SuiDesigner$TileEditor$reactLayers(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
SuiCore$ViewBase *  SuiDesigner$TileEditor$reactScene(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
SuiCore$ViewBase *  SuiDesigner$TileEditor$reactTilesetView(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item);
void  SuiDesigner$TileEditor$ui_createAnimTile(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$ui_createRandomTile(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$ui_createAutoTile(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$react(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$showWindow_mapSetting(SuiDesigner$TileEditor *  self);
void  SuiDesigner$TileEditor$showWindow(SuiDesigner$TileEditor *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
