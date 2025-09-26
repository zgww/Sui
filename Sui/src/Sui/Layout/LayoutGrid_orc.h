
typedef struct tagSuiLayout$LayoutGridItem SuiLayout$LayoutGridItem;
typedef struct tagVtable_SuiLayout$LayoutGridItem Vtable_SuiLayout$LayoutGridItem;
typedef struct tagSuiLayout$LayoutGridRowInfo SuiLayout$LayoutGridRowInfo;
typedef struct tagVtable_SuiLayout$LayoutGridRowInfo Vtable_SuiLayout$LayoutGridRowInfo;
typedef struct tagSuiLayout$LayoutGridOccupyCell SuiLayout$LayoutGridOccupyCell;
typedef struct tagVtable_SuiLayout$LayoutGridOccupyCell Vtable_SuiLayout$LayoutGridOccupyCell;
typedef struct tagSuiLayout$LayoutGridCell SuiLayout$LayoutGridCell;
typedef struct tagVtable_SuiLayout$LayoutGridCell Vtable_SuiLayout$LayoutGridCell;
typedef struct tagSuiLayout$LayoutGrid SuiLayout$LayoutGrid;
typedef struct tagVtable_SuiLayout$LayoutGrid Vtable_SuiLayout$LayoutGrid;


#ifndef define_struct___SuiLayout__LayoutGrid_orc_h__
#define define_struct___SuiLayout__LayoutGrid_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiLayout__LayoutGrid_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiLayout__LayoutGrid_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiLayout__LayoutGrid_orc_h__
#define __SuiLayout__LayoutGrid_orc_h__

//include  importHeadCode
#include "../Core/ViewBase_orc.h"
#include "../Core/Node_orc.h"
#include "../Core/View_orc.h"
#include "../Core/Rect_orc.h"
#include "../Core/Inset_orc.h"
#include "../Core/Frame_orc.h"
#include "../Core/LayoutCell_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/List_orc.h"
#include "../View/ViewBuilder_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiLayout$LayoutGridItem {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutGridItem _vtable_SuiLayout$LayoutGridItem;

// class refc:1
struct tagSuiLayout$LayoutGridItem {
	Object super; 
	SuiCore$ViewBase *  view ;
	int  col ;
	int  row ;
	int  rowSpan ;
	int  colSpan ;
	float  width ;
	float  x ;
	float  desiredHeight ;
};
Vtable_SuiLayout$LayoutGridItem* Vtable_SuiLayout$LayoutGridItem_init(Vtable_SuiLayout$LayoutGridItem* pvt);
void SuiLayout$LayoutGridItem_init_fields(SuiLayout$LayoutGridItem *self);
void SuiLayout$LayoutGridItem_init(SuiLayout$LayoutGridItem *self, void *pOwner);
SuiLayout$LayoutGridItem * SuiLayout$LayoutGridItem_new(void *pOwner);
void SuiLayout$LayoutGridItem_fini(SuiLayout$LayoutGridItem *self);



// 虚表
struct tagVtable_SuiLayout$LayoutGridRowInfo {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutGridRowInfo _vtable_SuiLayout$LayoutGridRowInfo;

// class refc:1
struct tagSuiLayout$LayoutGridRowInfo {
	Object super; 
	float  height ;
	float  y ;
};
Vtable_SuiLayout$LayoutGridRowInfo* Vtable_SuiLayout$LayoutGridRowInfo_init(Vtable_SuiLayout$LayoutGridRowInfo* pvt);
void SuiLayout$LayoutGridRowInfo_init_fields(SuiLayout$LayoutGridRowInfo *self);
void SuiLayout$LayoutGridRowInfo_init(SuiLayout$LayoutGridRowInfo *self, void *pOwner);
SuiLayout$LayoutGridRowInfo * SuiLayout$LayoutGridRowInfo_new(void *pOwner);
void SuiLayout$LayoutGridRowInfo_fini(SuiLayout$LayoutGridRowInfo *self);



// 虚表
struct tagVtable_SuiLayout$LayoutGridOccupyCell {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutGridOccupyCell _vtable_SuiLayout$LayoutGridOccupyCell;

// class refc:1
struct tagSuiLayout$LayoutGridOccupyCell {
	Object super; 
	bool  occupy ;
	float  desiredHeight ;
	int  restRowSpan ;
};
Vtable_SuiLayout$LayoutGridOccupyCell* Vtable_SuiLayout$LayoutGridOccupyCell_init(Vtable_SuiLayout$LayoutGridOccupyCell* pvt);
void SuiLayout$LayoutGridOccupyCell_init_fields(SuiLayout$LayoutGridOccupyCell *self);
void SuiLayout$LayoutGridOccupyCell_init(SuiLayout$LayoutGridOccupyCell *self, void *pOwner);
SuiLayout$LayoutGridOccupyCell * SuiLayout$LayoutGridOccupyCell_new(void *pOwner);
void SuiLayout$LayoutGridOccupyCell_fini(SuiLayout$LayoutGridOccupyCell *self);



// 虚表
struct tagVtable_SuiLayout$LayoutGridCell {
	Vtable_SuiCore$LayoutCell super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutGridCell _vtable_SuiLayout$LayoutGridCell;

// class refc:0
struct tagSuiLayout$LayoutGridCell {
	SuiCore$LayoutCell super; 
	int  colSpan ;
	int  rowSpan ;
};
Vtable_SuiLayout$LayoutGridCell* Vtable_SuiLayout$LayoutGridCell_init(Vtable_SuiLayout$LayoutGridCell* pvt);
void SuiLayout$LayoutGridCell_init_fields(SuiLayout$LayoutGridCell *self);
void SuiLayout$LayoutGridCell_init(SuiLayout$LayoutGridCell *self, void *pOwner);
SuiLayout$LayoutGridCell * SuiLayout$LayoutGridCell_new(void *pOwner);
void SuiLayout$LayoutGridCell_fini(SuiLayout$LayoutGridCell *self);



// 虚表
struct tagVtable_SuiLayout$LayoutGrid {
	Vtable_SuiCore$View super;
};
//虚表实例
extern Vtable_SuiLayout$LayoutGrid _vtable_SuiLayout$LayoutGrid;

// class refc:0
struct tagSuiLayout$LayoutGrid {
	SuiCore$View super; 
	void  (*resetOccupyGrid) (SuiLayout$LayoutGrid *  self);
	void  (*extendOccupyGrid) (SuiLayout$LayoutGrid *  self, int  row, bool  erase);
	void  (*occupy) (SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan);
	bool  (*checkFreeSpace) (SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan);
	bool  (*findNextAvailableGridPos) (SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan, int *  outC, int *  outR);
	void  (*updateOccupyViewInfo) (SuiLayout$LayoutGrid *  self, SuiCore$Frame *  kidctx, int  c, int  r, int  colSpan, int  rowSpan);
	float  (*calcMaxHeight_ofRow) (SuiLayout$LayoutGrid *  self, int  r);
	void  (*adjustRestRowsDesiredHeight) (SuiLayout$LayoutGrid *  self, int  r, float  maxHeight);
	Orc$List*  occupyGrid ;
	float  maxCrossSize ;
	int  colSpan ;
	int  rowSpan ;
	int  colCount ;
	float  rowSize ;
	float  rowSizeRatio ;
	int  rowCount ;
	float  colGap ;
	float  rowGap ;
};
Vtable_SuiLayout$LayoutGrid* Vtable_SuiLayout$LayoutGrid_init(Vtable_SuiLayout$LayoutGrid* pvt);
void SuiLayout$LayoutGrid_init_fields(SuiLayout$LayoutGrid *self);
void SuiLayout$LayoutGrid_init(SuiLayout$LayoutGrid *self, void *pOwner);
SuiLayout$LayoutGrid * SuiLayout$LayoutGrid_new(void *pOwner);
void SuiLayout$LayoutGrid_fini(SuiLayout$LayoutGrid *self);

void  SuiLayout$LayoutGrid$layout(SuiLayout$LayoutGrid *  self, SuiCore$Frame *  ctx);
void  SuiLayout$LayoutGrid$resetOccupyGrid(SuiLayout$LayoutGrid *  self);
void  SuiLayout$LayoutGrid$extendOccupyGrid(SuiLayout$LayoutGrid *  self, int  row, bool  erase);
void  SuiLayout$LayoutGrid$occupy(SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan);
bool  SuiLayout$LayoutGrid$checkFreeSpace(SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan);
bool  SuiLayout$LayoutGrid$findNextAvailableGridPos(SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan, int *  outC, int *  outR);
void  SuiLayout$LayoutGrid$updateOccupyViewInfo(SuiLayout$LayoutGrid *  self, SuiCore$Frame *  kidctx, int  c, int  r, int  colSpan, int  rowSpan);
float  SuiLayout$LayoutGrid$calcMaxHeight_ofRow(SuiLayout$LayoutGrid *  self, int  r);
void  SuiLayout$LayoutGrid$adjustRestRowsDesiredHeight(SuiLayout$LayoutGrid *  self, int  r, float  maxHeight);
void  SuiLayout$LayoutGrid$layoutContent(SuiLayout$LayoutGrid *  self, SuiCore$Frame *  ctx);

SuiLayout$LayoutGrid*  SuiLayout$mkLayoutGrid(SuiLayout$LayoutGrid **  __outRef__, void *  parent, long long  key);
SuiLayout$LayoutGridCell*  SuiLayout$mkLayoutGridCell(SuiLayout$LayoutGridCell **  __outRef__, void *  parent, long long  key);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
