
#include "LayoutGrid_orc.h" 

#include <stdio.h>
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


// static struct 


// static function declaration



//vtable instance
Vtable_SuiLayout$LayoutGridItem _vtable_SuiLayout$LayoutGridItem;

// init meta

void SuiLayout$LayoutGridItem_initMeta(Vtable_SuiLayout$LayoutGridItem *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "view", ((Vtable_Object*)Vtable_SuiCore$ViewBase_init(0)), offsetof(SuiLayout$LayoutGridItem, view), false, true, 1);
	orc_metaField_primitive(&pNext, "col", OrcMetaType_int, offsetof(SuiLayout$LayoutGridItem, col), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "row", OrcMetaType_int, offsetof(SuiLayout$LayoutGridItem, row), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "rowSpan", OrcMetaType_int, offsetof(SuiLayout$LayoutGridItem, rowSpan), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "colSpan", OrcMetaType_int, offsetof(SuiLayout$LayoutGridItem, colSpan), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(SuiLayout$LayoutGridItem, width), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "x", OrcMetaType_float, offsetof(SuiLayout$LayoutGridItem, x), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "desiredHeight", OrcMetaType_float, offsetof(SuiLayout$LayoutGridItem, desiredHeight), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_SuiLayout$LayoutGridItem* Vtable_SuiLayout$LayoutGridItem_init(Vtable_SuiLayout$LayoutGridItem* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutGridItem;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutGridItem_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutGridItem";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutGridItem_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiLayout$LayoutGridItem_fini(SuiLayout$LayoutGridItem *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutGridItem_init_fields(SuiLayout$LayoutGridItem *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutGridItem_fini;
	//fields
    {
	((SuiLayout$LayoutGridItem*)self)->width = 0.f;
	((SuiLayout$LayoutGridItem*)self)->x = 0.f;
	((SuiLayout$LayoutGridItem*)self)->desiredHeight = 0.f;
    }
	
}

// init function

void SuiLayout$LayoutGridItem_init(SuiLayout$LayoutGridItem *self, void *pOwner){
    Vtable_SuiLayout$LayoutGridItem_init(&_vtable_SuiLayout$LayoutGridItem);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutGridItem;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutGridItem_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutGridItem * SuiLayout$LayoutGridItem_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutGridItem *self = calloc(1, sizeof(SuiLayout$LayoutGridItem));
	
    SuiLayout$LayoutGridItem_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiLayout$LayoutGridRowInfo _vtable_SuiLayout$LayoutGridRowInfo;

// init meta

void SuiLayout$LayoutGridRowInfo_initMeta(Vtable_SuiLayout$LayoutGridRowInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "height", OrcMetaType_float, offsetof(SuiLayout$LayoutGridRowInfo, height), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "y", OrcMetaType_float, offsetof(SuiLayout$LayoutGridRowInfo, y), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_SuiLayout$LayoutGridRowInfo* Vtable_SuiLayout$LayoutGridRowInfo_init(Vtable_SuiLayout$LayoutGridRowInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutGridRowInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutGridRowInfo_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutGridRowInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutGridRowInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiLayout$LayoutGridRowInfo_fini(SuiLayout$LayoutGridRowInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutGridRowInfo_init_fields(SuiLayout$LayoutGridRowInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutGridRowInfo_fini;
	//fields
    {
	((SuiLayout$LayoutGridRowInfo*)self)->height = 0.f;
	((SuiLayout$LayoutGridRowInfo*)self)->y = 0.f;
    }
	
}

// init function

void SuiLayout$LayoutGridRowInfo_init(SuiLayout$LayoutGridRowInfo *self, void *pOwner){
    Vtable_SuiLayout$LayoutGridRowInfo_init(&_vtable_SuiLayout$LayoutGridRowInfo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutGridRowInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutGridRowInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutGridRowInfo * SuiLayout$LayoutGridRowInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutGridRowInfo *self = calloc(1, sizeof(SuiLayout$LayoutGridRowInfo));
	
    SuiLayout$LayoutGridRowInfo_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiLayout$LayoutGridOccupyCell _vtable_SuiLayout$LayoutGridOccupyCell;

// init meta

void SuiLayout$LayoutGridOccupyCell_initMeta(Vtable_SuiLayout$LayoutGridOccupyCell *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "occupy", OrcMetaType_bool, offsetof(SuiLayout$LayoutGridOccupyCell, occupy), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "desiredHeight", OrcMetaType_float, offsetof(SuiLayout$LayoutGridOccupyCell, desiredHeight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "restRowSpan", OrcMetaType_int, offsetof(SuiLayout$LayoutGridOccupyCell, restRowSpan), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiLayout$LayoutGridOccupyCell* Vtable_SuiLayout$LayoutGridOccupyCell_init(Vtable_SuiLayout$LayoutGridOccupyCell* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutGridOccupyCell;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutGridOccupyCell_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutGridOccupyCell";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutGridOccupyCell_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiLayout$LayoutGridOccupyCell_fini(SuiLayout$LayoutGridOccupyCell *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutGridOccupyCell_init_fields(SuiLayout$LayoutGridOccupyCell *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutGridOccupyCell_fini;
	//fields
    {
	((SuiLayout$LayoutGridOccupyCell*)self)->occupy = 0;
	((SuiLayout$LayoutGridOccupyCell*)self)->desiredHeight = 0.f;
	((SuiLayout$LayoutGridOccupyCell*)self)->restRowSpan = 0;
    }
	
}

// init function

void SuiLayout$LayoutGridOccupyCell_init(SuiLayout$LayoutGridOccupyCell *self, void *pOwner){
    Vtable_SuiLayout$LayoutGridOccupyCell_init(&_vtable_SuiLayout$LayoutGridOccupyCell);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutGridOccupyCell;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutGridOccupyCell_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutGridOccupyCell * SuiLayout$LayoutGridOccupyCell_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutGridOccupyCell *self = calloc(1, sizeof(SuiLayout$LayoutGridOccupyCell));
	
    SuiLayout$LayoutGridOccupyCell_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiLayout$LayoutGridCell _vtable_SuiLayout$LayoutGridCell;

// init meta

void SuiLayout$LayoutGridCell_initMeta(Vtable_SuiLayout$LayoutGridCell *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "colSpan", OrcMetaType_int, offsetof(SuiLayout$LayoutGridCell, colSpan), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "rowSpan", OrcMetaType_int, offsetof(SuiLayout$LayoutGridCell, rowSpan), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiLayout$LayoutGridCell* Vtable_SuiLayout$LayoutGridCell_init(Vtable_SuiLayout$LayoutGridCell* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutGridCell;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$LayoutCell_init(&_vtable_SuiCore$LayoutCell);

	// init by super vtable init function
    Vtable_SuiCore$LayoutCell_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$LayoutCell;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutGridCell_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutGridCell";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutGridCell_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$LayoutGridCell_fini(SuiLayout$LayoutGridCell *self){
	//super fini
    SuiCore$LayoutCell_fini((SuiCore$LayoutCell *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutGridCell_init_fields(SuiLayout$LayoutGridCell *self){
	//super class
    SuiCore$LayoutCell_init_fields((SuiCore$LayoutCell*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutGridCell_fini;
	//fields
    {
	((SuiLayout$LayoutGridCell*)self)->colSpan = 1;
	((SuiLayout$LayoutGridCell*)self)->rowSpan = 1;
    }
	
}

// init function

void SuiLayout$LayoutGridCell_init(SuiLayout$LayoutGridCell *self, void *pOwner){
    Vtable_SuiLayout$LayoutGridCell_init(&_vtable_SuiLayout$LayoutGridCell);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutGridCell;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutGridCell_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutGridCell * SuiLayout$LayoutGridCell_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutGridCell *self = calloc(1, sizeof(SuiLayout$LayoutGridCell));
	
    SuiLayout$LayoutGridCell_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiLayout$LayoutGrid _vtable_SuiLayout$LayoutGrid;

// init meta

void SuiLayout$LayoutGrid_initMeta(Vtable_SuiLayout$LayoutGrid *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "occupyGrid", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiLayout$LayoutGrid, occupyGrid), true, false, 1);
	orc_metaField_primitive(&pNext, "maxCrossSize", OrcMetaType_float, offsetof(SuiLayout$LayoutGrid, maxCrossSize), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "colSpan", OrcMetaType_int, offsetof(SuiLayout$LayoutGrid, colSpan), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "rowSpan", OrcMetaType_int, offsetof(SuiLayout$LayoutGrid, rowSpan), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "colCount", OrcMetaType_int, offsetof(SuiLayout$LayoutGrid, colCount), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "rowSize", OrcMetaType_float, offsetof(SuiLayout$LayoutGrid, rowSize), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "rowSizeRatio", OrcMetaType_float, offsetof(SuiLayout$LayoutGrid, rowSizeRatio), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "rowCount", OrcMetaType_int, offsetof(SuiLayout$LayoutGrid, rowCount), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "colGap", OrcMetaType_float, offsetof(SuiLayout$LayoutGrid, colGap), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "rowGap", OrcMetaType_float, offsetof(SuiLayout$LayoutGrid, rowGap), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "resetOccupyGrid", offsetof(SuiLayout$LayoutGrid, resetOccupyGrid));
	orc_metaField_method(&pNext, "extendOccupyGrid", offsetof(SuiLayout$LayoutGrid, extendOccupyGrid));
	orc_metaField_method(&pNext, "occupy", offsetof(SuiLayout$LayoutGrid, occupy));
	orc_metaField_method(&pNext, "checkFreeSpace", offsetof(SuiLayout$LayoutGrid, checkFreeSpace));
	orc_metaField_method(&pNext, "findNextAvailableGridPos", offsetof(SuiLayout$LayoutGrid, findNextAvailableGridPos));
	orc_metaField_method(&pNext, "updateOccupyViewInfo", offsetof(SuiLayout$LayoutGrid, updateOccupyViewInfo));
	orc_metaField_method(&pNext, "calcMaxHeight_ofRow", offsetof(SuiLayout$LayoutGrid, calcMaxHeight_ofRow));
	orc_metaField_method(&pNext, "adjustRestRowsDesiredHeight", offsetof(SuiLayout$LayoutGrid, adjustRestRowsDesiredHeight));
}


// vtable init


Vtable_SuiLayout$LayoutGrid* Vtable_SuiLayout$LayoutGrid_init(Vtable_SuiLayout$LayoutGrid* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiLayout$LayoutGrid;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiLayout$LayoutGrid_new;
    ((Vtable_Object*)pvt)->className = "SuiLayout$LayoutGrid";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiLayout$LayoutGrid_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiLayout$LayoutGrid_fini(SuiLayout$LayoutGrid *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放


}

// init fields function


void SuiLayout$LayoutGrid_init_fields(SuiLayout$LayoutGrid *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiLayout$LayoutGrid_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiLayout$LayoutGrid*)self)->occupyGrid, Orc$List_new(&tmpNewOwner_1) );
	((SuiLayout$LayoutGrid*)self)->maxCrossSize = 0.f;
	((SuiLayout$LayoutGrid*)self)->colSpan = 1;
	((SuiLayout$LayoutGrid*)self)->rowSpan = 1;
	((SuiLayout$LayoutGrid*)self)->colCount = 3;
	((SuiLayout$LayoutGrid*)self)->rowSize = 0.f;
	((SuiLayout$LayoutGrid*)self)->rowSizeRatio = 0.f;
	((SuiLayout$LayoutGrid*)self)->rowCount = 0;
	((SuiLayout$LayoutGrid*)self)->colGap = 4;
	((SuiLayout$LayoutGrid*)self)->rowGap = 4;
    }
	((SuiCore$ViewBase*)self)->layout = (void*)SuiLayout$LayoutGrid$layout;
	((SuiLayout$LayoutGrid*)self)->resetOccupyGrid = (void*)SuiLayout$LayoutGrid$resetOccupyGrid;
	((SuiLayout$LayoutGrid*)self)->extendOccupyGrid = (void*)SuiLayout$LayoutGrid$extendOccupyGrid;
	((SuiLayout$LayoutGrid*)self)->occupy = (void*)SuiLayout$LayoutGrid$occupy;
	((SuiLayout$LayoutGrid*)self)->checkFreeSpace = (void*)SuiLayout$LayoutGrid$checkFreeSpace;
	((SuiLayout$LayoutGrid*)self)->findNextAvailableGridPos = (void*)SuiLayout$LayoutGrid$findNextAvailableGridPos;
	((SuiLayout$LayoutGrid*)self)->updateOccupyViewInfo = (void*)SuiLayout$LayoutGrid$updateOccupyViewInfo;
	((SuiLayout$LayoutGrid*)self)->calcMaxHeight_ofRow = (void*)SuiLayout$LayoutGrid$calcMaxHeight_ofRow;
	((SuiLayout$LayoutGrid*)self)->adjustRestRowsDesiredHeight = (void*)SuiLayout$LayoutGrid$adjustRestRowsDesiredHeight;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiLayout$LayoutGrid$layoutContent;
}

// init function

void SuiLayout$LayoutGrid_init(SuiLayout$LayoutGrid *self, void *pOwner){
    Vtable_SuiLayout$LayoutGrid_init(&_vtable_SuiLayout$LayoutGrid);

    ((Object*)self)->vtable = (void*)&_vtable_SuiLayout$LayoutGrid;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiLayout$LayoutGrid_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiLayout$LayoutGrid * SuiLayout$LayoutGrid_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiLayout$LayoutGrid *self = calloc(1, sizeof(SuiLayout$LayoutGrid));
	
    SuiLayout$LayoutGrid_init(self, pOwner);
    return self;
}


// class members
void  SuiLayout$LayoutGrid$layout(SuiLayout$LayoutGrid *  self, SuiCore$Frame *  ctx){
	((SuiCore$View * )self)->updateFrame_forSelfWidthHeight(self, ctx) ;
	((SuiCore$View * )self)->initLayoutSize(self, ctx) ;
	if (!SuiCore$Frame$isTightWidth(ctx) ) {
		return ; 
	}
	if (self->rowCount > 0 && !SuiCore$Frame$isTightHeight(ctx) ) {
		return ; 
	}
	SuiCore$View$layout(self, ctx) ;
}


void  SuiLayout$LayoutGrid$resetOccupyGrid(SuiLayout$LayoutGrid *  self){
	int  l = self->occupyGrid->size(self->occupyGrid) ;
	for (int  i = 0; i < l; i++) {
		SuiLayout$LayoutGridOccupyCell *  ele = (SuiLayout$LayoutGridOccupyCell * )self->occupyGrid->get(self->occupyGrid, i) ;
		ele->occupy = 0;
	}
}


void  SuiLayout$LayoutGrid$extendOccupyGrid(SuiLayout$LayoutGrid *  self, int  row, bool  erase){
	int  cnt = row * self->colCount;
	if (cnt > self->occupyGrid->size(self->occupyGrid) ) {
		for (int  i = self->occupyGrid->size(self->occupyGrid) ; i < cnt; i++) {
			SuiLayout$LayoutGridOccupyCell *  cell = SuiLayout$LayoutGridOccupyCell_new(&cell) ;
			self->occupyGrid->add(self->occupyGrid, (Object * )cell) ;
		}
	}
	else if (erase && cnt < self->occupyGrid->size(self->occupyGrid) ) {
		self->occupyGrid->removeFromStart(self->occupyGrid, cnt) ;
	}
}


void  SuiLayout$LayoutGrid$occupy(SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan){
	for (int  r = 0; r < rowSpan; r++) {
		for (int  c = 0; c < colSpan; c++) {
			int  posR = r + _r;
			int  posC = c + _c;
			int  idx = posR * self->colCount + posC;
			SuiLayout$LayoutGridOccupyCell *  cell = (SuiLayout$LayoutGridOccupyCell * )self->occupyGrid->get(self->occupyGrid, idx) ;
			cell->occupy = 1;
		}
	}
}


bool  SuiLayout$LayoutGrid$checkFreeSpace(SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan){
	int  gridRowCount = self->occupyGrid->size(self->occupyGrid)  / self->colCount;
	for (int  r = 0; r < rowSpan; r++) {
		for (int  c = 0; c < colSpan; c++) {
			int  posR = r + _r;
			int  posC = c + _c;
			if (posR >= gridRowCount || posC >= self->colCount) {
				return false; 
			}
			int  idx = posR * self->colCount + posC;
			SuiLayout$LayoutGridOccupyCell *  cell = (SuiLayout$LayoutGridOccupyCell * )self->occupyGrid->get(self->occupyGrid, idx) ;
			int  occupy = cell->occupy;
			if (occupy) {
				return false; 
			}
		}
	}
	return true; 
}


bool  SuiLayout$LayoutGrid$findNextAvailableGridPos(SuiLayout$LayoutGrid *  self, int  _c, int  _r, int  colSpan, int  rowSpan, int *  outC, int *  outR){
	int  c = _c;
	for (int  ri = 0; true; ri++) {
		int  r = ri + _r;
		if (self->rowCount < 1) {
			self->extendOccupyGrid(self, r + rowSpan, true) ;
		}
		else if (r >= self->rowCount) {
			break;
		}
		for (; c < self->colCount; c++) {
			if (self->checkFreeSpace(self, c, r, colSpan, rowSpan) ) {
				*outC = c;
				*outR = r;
				return true; 
			}
		}
		c = 0;
	}
	return false; 
}


void  SuiLayout$LayoutGrid$updateOccupyViewInfo(SuiLayout$LayoutGrid *  self, SuiCore$Frame *  kidctx, int  c, int  r, int  colSpan, int  rowSpan){
	float  desiredHeight = (kidctx->height - (rowSpan - 1) * self->rowGap) / rowSpan;
	for (int  j = 0; j < rowSpan; j++) {
		for (int  i = 0; i < colSpan; i++) {
			int  idx = (j + r) * self->colCount + c + i;
			SuiLayout$LayoutGridOccupyCell *  occupy = (SuiLayout$LayoutGridOccupyCell * )self->occupyGrid->get(self->occupyGrid, idx) ;
			occupy->desiredHeight = desiredHeight;
			occupy->restRowSpan = rowSpan - 1 - j;
		}
	}
}


float  SuiLayout$LayoutGrid$calcMaxHeight_ofRow(SuiLayout$LayoutGrid *  self, int  r){
	float  maxHeight = 0.f;
	for (int  c = 0; c < self->colCount; c++) {
		int  idx = r * self->colCount + c;
		SuiLayout$LayoutGridOccupyCell *  occupy = (SuiLayout$LayoutGridOccupyCell * )self->occupyGrid->get(self->occupyGrid, idx) ;
		maxHeight = Orc$maxFloat(maxHeight, occupy->desiredHeight) ;
	}
	return maxHeight; 
}


void  SuiLayout$LayoutGrid$adjustRestRowsDesiredHeight(SuiLayout$LayoutGrid *  self, int  r, float  maxHeight){
	for (int  c = 0; c < self->colCount; c++) {
		int  idx = r * self->colCount + c;
		SuiLayout$LayoutGridOccupyCell *  occupy = (SuiLayout$LayoutGridOccupyCell * )self->occupyGrid->get(self->occupyGrid, idx) ;
		float  delta = maxHeight - occupy->desiredHeight;
		if (delta > 0.001f && occupy->restRowSpan > 0) {
			float  averDelta = delta / occupy->restRowSpan;
			for (int  j = 0; j < occupy->restRowSpan; j++) {
				int  restIdx = (r + j + 1) * self->colCount + c;
				SuiLayout$LayoutGridOccupyCell *  target = (SuiLayout$LayoutGridOccupyCell * )self->occupyGrid->get(self->occupyGrid, restIdx) ;
				target->desiredHeight = Orc$maxFloat(0.f, target->desiredHeight - averDelta) ;
			}
		}
	}
}


void  SuiLayout$LayoutGrid$layoutContent(SuiLayout$LayoutGrid *  self, SuiCore$Frame *  ctx){
	if (self->colCount < 1) {
		printf("warning: LayoutGrid invalid colCount:%d, rowCount:%d\n", self->colCount, self->rowCount) ;
		return ; 
	}
	float  colSize = (ctx->width - self->colGap * (self->colCount - 1)) / self->colCount;
	float  rowSize = 10.f;
	bool  wrapHeight = false;
	if (self->rowSizeRatio > 0.001f) {
		rowSize = colSize * self->rowSizeRatio;
	}
	else if (self->rowSize > 0.001f) {
		rowSize = self->rowSize;
	}
	else if (self->rowCount > 0 && SuiCore$Frame$isTightHeight(ctx) ) {
		rowSize = (ctx->height - self->rowGap * (self->rowCount - 1)) / self->rowCount;
	}
	else {
		wrapHeight = true;
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  items = (items=NULL,urgc_init_var_class((void**)&items, Orc$List_new(&items) ));
	self->resetOccupyGrid(self) ;
	if (self->rowCount > 0) {
		self->extendOccupyGrid(self, self->rowCount, true) ;
	}
	int  c = 0;
	int  r = 0;
	int  maxRowCount = 0;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  view = ((SuiCore$ViewBase * )self)->getChildAsView(self, i) ;
		if (view && view->canLayoutByParent(view) ) {
			int  colSpan = self->colSpan;
			int  rowSpan = self->rowSpan;
			SuiLayout$LayoutGridCell *  cell = (SuiLayout$LayoutGridCell * )((SuiCore$Node * )view)->getChildByType(view, Vtable_SuiLayout$LayoutGridCell_init(NULL)) ;
			if (cell) {
				colSpan = cell->colSpan;
				rowSpan = cell->rowSpan;
			}
			if (colSpan < 1) {
				colSpan = 1;
			}
			if (rowSpan < 1) {
				rowSpan = 1;
			}
			if (self->findNextAvailableGridPos(self, c, r, colSpan, rowSpan, &c, &r) ) {
				self->occupy(self, c, r, colSpan, rowSpan) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutGridItem*  item = (item=NULL,urgc_init_var_class((void**)&item, SuiLayout$LayoutGridItem_new(&item) ));
				items->add(items, (Object * )item) ;
				item->col = c;
				item->row = r;
				item->colSpan = colSpan;
				item->rowSpan = rowSpan;
				item->view = view;
				item->width = colSpan * colSize + (colSpan - 1) * self->colGap;
				item->x = item->col * colSize + (item->col - 1) * self->colGap;
				maxRowCount = Orc$maxFloat(r + rowSpan, maxRowCount) ;
				c = c + colSpan;
			}
			else {
				SuiCore$Frame$setTight(&view->frame, 0, 0) ;
			}
		}
	}
	float  maxHeight = 0.f;
	if (wrapHeight) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  rowHeights = (rowHeights=NULL,urgc_init_var_class((void**)&rowHeights, Orc$List_new(&rowHeights) ));
		for (int  i = 0; i < maxRowCount; i++) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutGridRowInfo*  ele = (ele=NULL,urgc_init_var_class((void**)&ele, SuiLayout$LayoutGridRowInfo_new(&ele) ));
			rowHeights->add(rowHeights, (Object * )ele) ;
		}
		for (int  i = 0; i < items->size(items) ; i++) {
			SuiLayout$LayoutGridItem *  item = (SuiLayout$LayoutGridItem * )items->get(items, i) ;
			SuiCore$ViewBase *  view = item->view;
			float  colSpan = item->colSpan;
			float  rowSpan = item->rowSpan;
			SuiCore$Frame$setTightWidth(&view->frame, item->width) ;
			SuiCore$Frame$setHeightConstraint(&view->frame, 0.f, ctx->maxHeight) ;
			view->layout(view, &view->frame) ;
			item->desiredHeight = view->frame.height;
			self->updateOccupyViewInfo(self, &view->frame, item->col, item->row, item->colSpan, item->rowSpan) ;
		}
		for (int  j = 0; j < rowHeights->size(rowHeights) ; j++) {
			SuiLayout$LayoutGridRowInfo *  rowHeight = (SuiLayout$LayoutGridRowInfo * )rowHeights->get(rowHeights, j) ;
			float  height = self->calcMaxHeight_ofRow(self, j) ;
			rowHeight->height = height;
			self->adjustRestRowsDesiredHeight(self, j, height) ;
		}
		float  y = 0.f;
		for (int  j = 0; j < rowHeights->size(rowHeights) ; j++) {
			SuiLayout$LayoutGridRowInfo *  rowHeight = (SuiLayout$LayoutGridRowInfo * )rowHeights->get(rowHeights, j) ;
			rowHeight->y = y;
			y = y + rowHeight->height + self->rowGap;
		}
		for (int  i = 0; i < items->size(items) ; i++) {
			SuiLayout$LayoutGridItem *  item = (SuiLayout$LayoutGridItem * )items->get(items, i) ;
			float  actualHeight = (item->rowSpan - 1) * self->rowGap;
			int  l = item->row + item->rowSpan;
			for (int  _r = item->row; _r < l; _r++) {
				SuiLayout$LayoutGridRowInfo *  rowHeight = (SuiLayout$LayoutGridRowInfo * )rowHeights->get(rowHeights, r) ;
				actualHeight = actualHeight + rowHeight->height;
			}
			if (actualHeight != item->desiredHeight) {
				SuiCore$Frame$setTight(&item->view->frame, item->width, actualHeight) ;
				item->view->layout(item->view, &item->view->frame) ;
			}
			SuiLayout$LayoutGridRowInfo *  rowHeightOfRow = (SuiLayout$LayoutGridRowInfo * )rowHeights->get(rowHeights, item->row) ;
			SuiCore$Frame$setPosition(&item->view->frame, item->x, rowHeightOfRow->y) ;
			maxHeight = Orc$maxFloat(maxHeight, SuiCore$Frame$getBottom(&item->view->frame) ) ;
		}
	}
	else {
		for (int  i = 0; i < items->size(items) ; i++) {
			SuiLayout$LayoutGridItem *  item = (SuiLayout$LayoutGridItem * )items->get(items, i) ;
			SuiCore$ViewBase *  view = item->view;
			float  colSpan = item->colSpan;
			float  rowSpan = item->rowSpan;
			SuiCore$Frame$setTight(&view->frame, item->width, rowSpan * rowSize + (rowSpan - 1) * self->rowGap) ;
			view->layout(view, &view->frame) ;
			SuiCore$Frame$setPosition(&view->frame, item->x, item->row * rowSize + (item->row - 1) * self->rowGap) ;
			maxHeight = Orc$maxFloat(maxHeight, SuiCore$Frame$getBottom(&view->frame) ) ;
		}
	}
	SuiCore$Frame$setHeight(ctx, maxHeight) ;
}



SuiLayout$LayoutGrid*  SuiLayout$mkLayoutGrid(SuiLayout$LayoutGrid **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$LayoutGrid* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$LayoutGrid_init(NULL)) ) ; 
}

SuiLayout$LayoutGridCell*  SuiLayout$mkLayoutGridCell(SuiLayout$LayoutGridCell **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiLayout$LayoutGridCell* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiLayout$LayoutGridCell_init(NULL)) ) ; 
}



