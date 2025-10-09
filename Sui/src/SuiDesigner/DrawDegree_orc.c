
#include "DrawDegree_orc.h" 

#include <math.h>
#include <stdio.h>
#include "../Orc/Math_orc.h"
#include "../Orc/List_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Mat2d_orc.h"
#include "../Sui/Core/Vec3_orc.h"


// static struct 


// static function declaration
static SuiDesigner$DrawDegreeItem*  mkItem(SuiDesigner$DrawDegreeItem **  __outRef__, float  value, float  degree);



//vtable instance
Vtable_SuiDesigner$DrawDegreeItem _vtable_SuiDesigner$DrawDegreeItem;

// init meta

void SuiDesigner$DrawDegreeItem_initMeta(Vtable_SuiDesigner$DrawDegreeItem *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_float, offsetof(SuiDesigner$DrawDegreeItem, value), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "degree", OrcMetaType_float, offsetof(SuiDesigner$DrawDegreeItem, degree), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_SuiDesigner$DrawDegreeItem* Vtable_SuiDesigner$DrawDegreeItem_init(Vtable_SuiDesigner$DrawDegreeItem* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$DrawDegreeItem;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$DrawDegreeItem_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$DrawDegreeItem";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$DrawDegreeItem_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$DrawDegreeItem_fini(SuiDesigner$DrawDegreeItem *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$DrawDegreeItem_init_fields(SuiDesigner$DrawDegreeItem *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$DrawDegreeItem_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$DrawDegreeItem_init(SuiDesigner$DrawDegreeItem *self, void *pOwner){
    Vtable_SuiDesigner$DrawDegreeItem_init(&_vtable_SuiDesigner$DrawDegreeItem);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$DrawDegreeItem;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$DrawDegreeItem_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$DrawDegreeItem * SuiDesigner$DrawDegreeItem_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$DrawDegreeItem *self = calloc(1, sizeof(SuiDesigner$DrawDegreeItem));
	
    SuiDesigner$DrawDegreeItem_init(self, pOwner);
    return self;
}


// class members

static SuiDesigner$DrawDegreeItem*  mkItem(SuiDesigner$DrawDegreeItem **  __outRef__, float  value, float  degree){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  item = (item=NULL,urgc_init_var_class((void**)&item, SuiDesigner$DrawDegreeItem_new(&item) ));
	item->value = value;
	item->degree = degree;
	return urgc_set_var_for_return_class((void ** )__outRef__, item) ; 
}


//vtable instance
Vtable_SuiDesigner$DrawDegree _vtable_SuiDesigner$DrawDegree;

// init meta

void SuiDesigner$DrawDegree_initMeta(Vtable_SuiDesigner$DrawDegree *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "options", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$DrawDegree, options), true, false, 1);
	orc_metaField_class(&pNext, "levelOptions", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$DrawDegree, levelOptions), true, false, 1);
	orc_metaField_primitive(&pNext, "curScale", OrcMetaType_float, offsetof(SuiDesigner$DrawDegree, curScale), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "curOption", ((Vtable_Object*)Vtable_SuiDesigner$DrawDegreeItem_init(0)), offsetof(SuiDesigner$DrawDegree, curOption), true, false, 1);

	orc_metaField_method(&pNext, "genLevels", offsetof(SuiDesigner$DrawDegree, genLevels));
	orc_metaField_method(&pNext, "findAndReturnOffset", offsetof(SuiDesigner$DrawDegree, findAndReturnOffset));
	orc_metaField_method(&pNext, "findAndUpdateCurOption", offsetof(SuiDesigner$DrawDegree, findAndUpdateCurOption));
	orc_metaField_method(&pNext, "setScale", offsetof(SuiDesigner$DrawDegree, setScale));
	orc_metaField_method(&pNext, "draw", offsetof(SuiDesigner$DrawDegree, draw));
}


// vtable init


Vtable_SuiDesigner$DrawDegree* Vtable_SuiDesigner$DrawDegree_init(Vtable_SuiDesigner$DrawDegree* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$DrawDegree;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$DrawDegree_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$DrawDegree";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$DrawDegree_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$DrawDegree_fini(SuiDesigner$DrawDegree *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$DrawDegree*)self)->options);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$DrawDegree*)self)->levelOptions);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$DrawDegree*)self)->curOption);

}

// init fields function


void SuiDesigner$DrawDegree_init_fields(SuiDesigner$DrawDegree *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$DrawDegree_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$DrawDegree*)self)->options, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$DrawDegree*)self)->levelOptions, Orc$List_new(&tmpNewOwner_2) );
	((SuiDesigner$DrawDegree*)self)->curScale = 1.0;
	urgc_set_field_class(self, (void**)&((SuiDesigner$DrawDegree*)self)->curOption, NULL);
    }
	((Object*)self)->ctor = (void*)SuiDesigner$DrawDegree$ctor;
	((SuiDesigner$DrawDegree*)self)->genLevels = (void*)SuiDesigner$DrawDegree$genLevels;
	((SuiDesigner$DrawDegree*)self)->findAndReturnOffset = (void*)SuiDesigner$DrawDegree$findAndReturnOffset;
	((SuiDesigner$DrawDegree*)self)->findAndUpdateCurOption = (void*)SuiDesigner$DrawDegree$findAndUpdateCurOption;
	((SuiDesigner$DrawDegree*)self)->setScale = (void*)SuiDesigner$DrawDegree$setScale;
	((SuiDesigner$DrawDegree*)self)->draw = (void*)SuiDesigner$DrawDegree$draw;
}

// init function

void SuiDesigner$DrawDegree_init(SuiDesigner$DrawDegree *self, void *pOwner){
    Vtable_SuiDesigner$DrawDegree_init(&_vtable_SuiDesigner$DrawDegree);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$DrawDegree;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$DrawDegree_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$DrawDegree * SuiDesigner$DrawDegree_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$DrawDegree *self = calloc(1, sizeof(SuiDesigner$DrawDegree));
	
    SuiDesigner$DrawDegree_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$DrawDegree$ctor(SuiDesigner$DrawDegree *  self){
	{
		Orc$List*  o = self->options;
		
	
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_1 = NULL;
		o->add(o, mkItem(&tmpReturn_1, 0.2, 500) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_2 = NULL;
		o->add(o, mkItem(&tmpReturn_2, 0.5, 100) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_3 = NULL;
		o->add(o, mkItem(&tmpReturn_3, 0.8, 80) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_4 = NULL;
		o->add(o, mkItem(&tmpReturn_4, 1.0, 50) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_5 = NULL;
		o->add(o, mkItem(&tmpReturn_5, 1.2, 45) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_6 = NULL;
		o->add(o, mkItem(&tmpReturn_6, 1.4, 40) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_7 = NULL;
		o->add(o, mkItem(&tmpReturn_7, 1.6, 35) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_8 = NULL;
		o->add(o, mkItem(&tmpReturn_8, 1.8, 30) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_9 = NULL;
		o->add(o, mkItem(&tmpReturn_9, 2.0, 25) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_10 = NULL;
		o->add(o, mkItem(&tmpReturn_10, 4.0, 10) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_11 = NULL;
		o->add(o, mkItem(&tmpReturn_11, 6.0, 5) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_12 = NULL;
		o->add(o, mkItem(&tmpReturn_12, 10.0, 5) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_13 = NULL;
		o->add(o, mkItem(&tmpReturn_13, 16.0, 2) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_14 = NULL;
		o->add(o, mkItem(&tmpReturn_14, 26.0, 2) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_15 = NULL;
		o->add(o, mkItem(&tmpReturn_15, 60.0, 1) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_16 = NULL;
		o->add(o, mkItem(&tmpReturn_16, 100.0, 1) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_17 = NULL;
		o->add(o, mkItem(&tmpReturn_17, 150.0, 1) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_18 = NULL;
		o->add(o, mkItem(&tmpReturn_18, 200.0, 1) ) ;
	}
	self->genLevels(self, 4) ;
	self->setScale(self, 1.0) ;
}


void  SuiDesigner$DrawDegree$genLevels(SuiDesigner$DrawDegree *  self, int  count){
	URGC_VAR_CLEANUP_CLASS Orc$List*  opts = (opts=NULL,urgc_init_var_class((void**)&opts, Orc$List_new(&opts) ));
	printf("options.size:%d\n", self->options->size(self->options) ) ;
	for (int  i = 0; i < self->options->size(self->options)  - 1; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  cur = (cur=NULL,urgc_init_var_class((void**)&cur, (SuiDesigner$DrawDegreeItem* )self->options->get(self->options, i) ));
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  next = (next=NULL,urgc_init_var_class((void**)&next, (SuiDesigner$DrawDegreeItem* )self->options->get(self->options, i + 1) ));
		float  step = (next->value - cur->value) / (float )count;
		printf("\t\tnext.value.:%f\n", next->value) ;
		for (float  j = cur->value; j < next->value; j += step) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  item = mkItem((item = NULL,&item), j, cur->degree) ;
			opts->add(opts, item) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  last = (last=NULL,urgc_init_var_class((void**)&last, (SuiDesigner$DrawDegreeItem* )self->options->last(self->options) ));
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_1 = NULL;
	opts->add(opts, mkItem(&tmpReturn_1, last->value, last->degree) ) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$DrawDegree, levelOptions) , opts) ;
}


SuiDesigner$DrawDegreeItem*  SuiDesigner$DrawDegree$findAndReturnOffset(SuiDesigner$DrawDegreeItem **  __outRef__, SuiDesigner$DrawDegree *  self, float  scale, int  offset){
	for (int  i = self->levelOptions->size(self->levelOptions)  - 1; i >= 0; i--) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  cur = (cur=NULL,urgc_init_var_class((void**)&cur, (SuiDesigner$DrawDegreeItem* )self->levelOptions->get(self->levelOptions, i) ));
		if (cur->value <= scale) {
			int  retIndex = i + offset;
			retIndex = Orc$clampInt(retIndex, 0, self->levelOptions->size(self->levelOptions)  - 1) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, self->levelOptions->get(self->levelOptions, retIndex) ));
			return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


SuiDesigner$DrawDegreeItem*  SuiDesigner$DrawDegree$findAndUpdateCurOption(SuiDesigner$DrawDegreeItem **  __outRef__, SuiDesigner$DrawDegree *  self, float  scale){
	if (scale == self->curScale) {
		if (self->curOption) {
			return urgc_set_var_for_return_class((void ** )__outRef__, self->curOption) ; 
		}
	}
	for (int  i = self->levelOptions->size(self->levelOptions)  - 1; i >= 0; i--) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  cur = (cur=NULL,urgc_init_var_class((void**)&cur, (SuiDesigner$DrawDegreeItem* )self->levelOptions->get(self->levelOptions, i) ));
		if (cur->value <= scale) {
			urgc_set_field_class(self, (void * )offsetof(SuiDesigner$DrawDegree, curOption) , cur) ;
			break;
		}
	}
	self->curScale = scale;
	return urgc_set_var_for_return_class((void ** )__outRef__, self->curOption) ; 
}


void  SuiDesigner$DrawDegree$setScale(SuiDesigner$DrawDegree *  self, float  scale){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  tmpReturn_1 = NULL;
	self->findAndUpdateCurOption(&tmpReturn_1, self, scale) ;
}


void  SuiDesigner$DrawDegree$draw(SuiDesigner$DrawDegree *  self, SuiCore$Canvas *  canvas, SuiCore$Mat2d sceneMat2d, float  w, float  h, float  mouseX, float  mouseY){
	if (!self->curOption) {
		return ; 
	}
	SuiCore$Mat2d inv = SuiCore$Mat2d$inverseNew(&sceneMat2d) ;
	SuiCore$Vec3 leftTop = SuiCore$Mat2d$transformPoint(&inv, 0.f, 0.f, 0.f) ;
	SuiCore$Vec3 rightBottom = SuiCore$Mat2d$transformPoint(&inv, w, h, 0.f) ;
	float  degree = self->curOption->degree;
	float  startX = floor(leftTop.x / degree)  * degree - degree;
	float  startY = floor(leftTop.y / degree)  * degree - degree;
	float  endX = floor(rightBottom.x / degree)  * degree + degree;
	float  endY = floor(rightBottom.y / degree)  * degree + degree;
	{
		SuiCore$Vec3 left = SuiCore$Mat2d$transformPoint(&sceneMat2d, leftTop.x, 0.f, 0.f) ;
		SuiCore$Vec3 right = SuiCore$Mat2d$transformPoint(&sceneMat2d, rightBottom.x, 0.f, 0.f) ;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$moveTo(canvas, left.x + 0.0f, left.y + 0.5f) ;
		SuiCore$Canvas$lineTo(canvas, right.x + 0.0f, right.y + 0.5f) ;
		SuiCore$Canvas$strokeWidth(canvas, 1.f) ;
		SuiCore$Canvas$strokeColor(canvas, 255, 0, 0, 128) ;
		SuiCore$Canvas$stroke(canvas) ;
	}
	{
		SuiCore$Vec3 left = SuiCore$Mat2d$transformPoint(&sceneMat2d, 0.f, leftTop.y, 0.f) ;
		SuiCore$Vec3 right = SuiCore$Mat2d$transformPoint(&sceneMat2d, 0.f, rightBottom.y, 0.f) ;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$moveTo(canvas, left.x + 0.5f, left.y) ;
		SuiCore$Canvas$lineTo(canvas, right.x + 0.5f, right.y) ;
		SuiCore$Canvas$strokeColor(canvas, 0, 255, 0, 128) ;
		SuiCore$Canvas$stroke(canvas) ;
	}
	SuiCore$Canvas$fillColor(canvas, 255, 255, 255, 200) ;
	SuiCore$Canvas$fontSize(canvas, 12) ;
	for (float  x = startX; x <= endX; x += degree) {
		float  y = leftTop.y;
		SuiCore$Vec3 viewPoint = SuiCore$Mat2d$transformPoint(&sceneMat2d, x, y, 0.f) ;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$rect(canvas, viewPoint.x, viewPoint.y, 1.f, 12.f) ;
		SuiCore$Canvas$fill(canvas) ;
		char  tmp[20];
		sprintf(tmp, "%.0f", x) ;
		SuiCore$Canvas$text(canvas, viewPoint.x + 3, 10.f, tmp) ;
	}
	float  yDegree = endY >= startY ? degree : -degree;
	for (float  y = startY; y <= endY; y += yDegree) {
		float  x = leftTop.x;
		SuiCore$Vec3 viewPoint = SuiCore$Mat2d$transformPoint(&sceneMat2d, x, y, 0.f) ;
		SuiCore$Canvas$beginPath(canvas) ;
		SuiCore$Canvas$rect(canvas, viewPoint.x, viewPoint.y, 12.f, 1.f) ;
		SuiCore$Canvas$fill(canvas) ;
		char  tmp[20];
		sprintf(tmp, "%.0f", y) ;
		SuiCore$Canvas$text(canvas, 0.f, viewPoint.y + 12.f, tmp) ;
	}
}





