
#include "ViewBase_orc.h" 

#include <stdio.h>
#include "../../Orc/Orc.h"
#include "../../nanovg/nanovg.h"
#include "./Node_orc.h"
#include "./Rect_orc.h"
#include "./Frame_orc.h"
#include "./LayoutCell_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Math_orc.h"
#include "./Vec2_orc.h"
#include "./Vec3_orc.h"
#include "./Mat2d_orc.h"
#include "./Inset_orc.h"
#include "./Window_orc.h"
#include "./App_orc.h"
#include "./Color_orc.h"
#include "./Canvas_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiCore$ViewBase _vtable_SuiCore$ViewBase;

// init meta

void SuiCore$ViewBase_initMeta(Vtable_SuiCore$ViewBase *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "hitTestType", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$ViewBase, hitTestType), true, false, 1);
	orc_metaField_struct(&pNext, "hitTestPadding", SuiCore$Inset_getOrInitMetaStruct(), offsetof(SuiCore$ViewBase, hitTestPadding), false, false, 0);
	orc_metaField_struct(&pNext, "frame", SuiCore$Frame_getOrInitMetaStruct(), offsetof(SuiCore$ViewBase, frame), false, false, 0);
	orc_metaField_class(&pNext, "layoutCells", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$ViewBase, layoutCells), true, false, 1);
	orc_metaField_struct(&pNext, "transform", SuiCore$Mat2d_getOrInitMetaStruct(), offsetof(SuiCore$ViewBase, transform), false, false, 0);
	orc_metaField_struct(&pNext, "_world_transform", SuiCore$Mat2d_getOrInitMetaStruct(), offsetof(SuiCore$ViewBase, _world_transform), false, false, 0);
	orc_metaField_primitive(&pNext, "visible", OrcMetaType_bool, offsetof(SuiCore$ViewBase, visible), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "cursor", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$ViewBase, cursor), true, false, 1);
	orc_metaField_primitive(&pNext, "hover", OrcMetaType_bool, offsetof(SuiCore$ViewBase, hover), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "z", OrcMetaType_int, offsetof(SuiCore$ViewBase, z), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "gocLayoutCells", offsetof(SuiCore$ViewBase, gocLayoutCells));
	orc_metaField_method(&pNext, "getLayoutCellByType", offsetof(SuiCore$ViewBase, getLayoutCellByType));
	orc_metaField_method(&pNext, "getChildViewAt", offsetof(SuiCore$ViewBase, getChildViewAt));
	orc_metaField_method(&pNext, "getChildAsView", offsetof(SuiCore$ViewBase, getChildAsView));
	orc_metaField_method(&pNext, "getChildrenViewCount", offsetof(SuiCore$ViewBase, getChildrenViewCount));
	orc_metaField_method(&pNext, "getScreenRect", offsetof(SuiCore$ViewBase, getScreenRect));
	orc_metaField_method(&pNext, "get_abs_rect", offsetof(SuiCore$ViewBase, get_abs_rect));
	orc_metaField_method(&pNext, "_hitTestClientRect", offsetof(SuiCore$ViewBase, _hitTestClientRect));
	orc_metaField_method(&pNext, "_hitTestSelf", offsetof(SuiCore$ViewBase, _hitTestSelf));
	orc_metaField_method(&pNext, "_on_invalidLayout", offsetof(SuiCore$ViewBase, _on_invalidLayout));
	orc_metaField_method(&pNext, "_on_invalidDraw", offsetof(SuiCore$ViewBase, _on_invalidDraw));
	orc_metaField_method(&pNext, "resetViewTreeDirty", offsetof(SuiCore$ViewBase, resetViewTreeDirty));
	orc_metaField_method(&pNext, "localToWorld", offsetof(SuiCore$ViewBase, localToWorld));
	orc_metaField_method(&pNext, "worldToLocal", offsetof(SuiCore$ViewBase, worldToLocal));
	orc_metaField_method(&pNext, "hitTest", offsetof(SuiCore$ViewBase, hitTest));
	orc_metaField_method(&pNext, "hitTestChildren", offsetof(SuiCore$ViewBase, hitTestChildren));
	orc_metaField_method(&pNext, "viewIndexOf", offsetof(SuiCore$ViewBase, viewIndexOf));
	orc_metaField_method(&pNext, "viewIndexInParent", offsetof(SuiCore$ViewBase, viewIndexInParent));
	orc_metaField_method(&pNext, "markLayoutStart", offsetof(SuiCore$ViewBase, markLayoutStart));
	orc_metaField_method(&pNext, "printLayoutTimes", offsetof(SuiCore$ViewBase, printLayoutTimes));
	orc_metaField_method(&pNext, "layoutContent", offsetof(SuiCore$ViewBase, layoutContent));
	orc_metaField_method(&pNext, "layout", offsetof(SuiCore$ViewBase, layout));
	orc_metaField_method(&pNext, "invalidLayout", offsetof(SuiCore$ViewBase, invalidLayout));
	orc_metaField_method(&pNext, "draw", offsetof(SuiCore$ViewBase, draw));
	orc_metaField_method(&pNext, "draw_children", offsetof(SuiCore$ViewBase, draw_children));
	orc_metaField_method(&pNext, "draw_self", offsetof(SuiCore$ViewBase, draw_self));
	orc_metaField_method(&pNext, "invalidDraw", offsetof(SuiCore$ViewBase, invalidDraw));
	orc_metaField_method(&pNext, "canLayoutByParent", offsetof(SuiCore$ViewBase, canLayoutByParent));
	orc_metaField_method(&pNext, "setVisible", offsetof(SuiCore$ViewBase, setVisible));
	orc_metaField_method(&pNext, "setHover", offsetof(SuiCore$ViewBase, setHover));
	orc_metaField_method(&pNext, "onHoverChanged", offsetof(SuiCore$ViewBase, onHoverChanged));
}


// vtable init


Vtable_SuiCore$ViewBase* Vtable_SuiCore$ViewBase_init(Vtable_SuiCore$ViewBase* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$ViewBase;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Node_init(&_vtable_SuiCore$Node);

	// init by super vtable init function
    Vtable_SuiCore$Node_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Node;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$ViewBase_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$ViewBase";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$ViewBase_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$ViewBase_fini(SuiCore$ViewBase *self){
	//super fini
    SuiCore$Node_fini((SuiCore$Node *)self);

    //字段释放


}

// init fields function


void SuiCore$ViewBase_init_fields(SuiCore$ViewBase *self){
	//super class
    SuiCore$Node_init_fields((SuiCore$Node*)self);

    ((Object*)self)->fini = (void*)SuiCore$ViewBase_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$ViewBase*)self)->hitTestType, Orc$str(&tmpReturn_1, "normal") );
	((SuiCore$ViewBase*)self)->hitTestPadding = SuiCore$mkInset0() ;
	((SuiCore$ViewBase*)self)->frame = SuiCore$mkFrame() ;
	urgc_set_field_class(self, (void**)&((SuiCore$ViewBase*)self)->layoutCells, NULL);
	((SuiCore$ViewBase*)self)->transform = SuiCore$mkMat2d() ;
	((SuiCore$ViewBase*)self)->_world_transform = SuiCore$mkMat2d() ;
	((SuiCore$ViewBase*)self)->visible = true;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$ViewBase*)self)->cursor, Orc$str(&tmpReturn_2, "unset") );
	((SuiCore$ViewBase*)self)->hover = false;
	((SuiCore$ViewBase*)self)->z = 0;
	urgc_set_field(self, (void**)&((SuiCore$ViewBase*)self)->cbOnHoverChanged, NULL);
    }
	((SuiCore$ViewBase*)self)->gocLayoutCells = (void*)SuiCore$ViewBase$gocLayoutCells;
	((SuiCore$ViewBase*)self)->getLayoutCellByType = (void*)SuiCore$ViewBase$getLayoutCellByType;
	((SuiCore$ViewBase*)self)->getChildViewAt = (void*)SuiCore$ViewBase$getChildViewAt;
	((SuiCore$ViewBase*)self)->getChildAsView = (void*)SuiCore$ViewBase$getChildAsView;
	((SuiCore$ViewBase*)self)->getChildrenViewCount = (void*)SuiCore$ViewBase$getChildrenViewCount;
	((SuiCore$ViewBase*)self)->getScreenRect = (void*)SuiCore$ViewBase$getScreenRect;
	((SuiCore$ViewBase*)self)->get_abs_rect = (void*)SuiCore$ViewBase$get_abs_rect;
	((SuiCore$ViewBase*)self)->_hitTestClientRect = (void*)SuiCore$ViewBase$_hitTestClientRect;
	((SuiCore$ViewBase*)self)->_hitTestSelf = (void*)SuiCore$ViewBase$_hitTestSelf;
	((SuiCore$ViewBase*)self)->_on_invalidLayout = (void*)SuiCore$ViewBase$_on_invalidLayout;
	((SuiCore$ViewBase*)self)->_on_invalidDraw = (void*)SuiCore$ViewBase$_on_invalidDraw;
	((SuiCore$ViewBase*)self)->resetViewTreeDirty = (void*)SuiCore$ViewBase$resetViewTreeDirty;
	((SuiCore$Node*)self)->invalidReact = (void*)SuiCore$ViewBase$invalidReact;
	((SuiCore$ViewBase*)self)->localToWorld = (void*)SuiCore$ViewBase$localToWorld;
	((SuiCore$ViewBase*)self)->worldToLocal = (void*)SuiCore$ViewBase$worldToLocal;
	((SuiCore$ViewBase*)self)->hitTest = (void*)SuiCore$ViewBase$hitTest;
	((SuiCore$ViewBase*)self)->hitTestChildren = (void*)SuiCore$ViewBase$hitTestChildren;
	((SuiCore$ViewBase*)self)->viewIndexOf = (void*)SuiCore$ViewBase$viewIndexOf;
	((SuiCore$ViewBase*)self)->viewIndexInParent = (void*)SuiCore$ViewBase$viewIndexInParent;
	((SuiCore$ViewBase*)self)->markLayoutStart = (void*)SuiCore$ViewBase$markLayoutStart;
	((SuiCore$ViewBase*)self)->printLayoutTimes = (void*)SuiCore$ViewBase$printLayoutTimes;
	((SuiCore$ViewBase*)self)->layoutContent = (void*)SuiCore$ViewBase$layoutContent;
	((SuiCore$ViewBase*)self)->layout = (void*)SuiCore$ViewBase$layout;
	((SuiCore$ViewBase*)self)->invalidLayout = (void*)SuiCore$ViewBase$invalidLayout;
	((SuiCore$ViewBase*)self)->draw = (void*)SuiCore$ViewBase$draw;
	((SuiCore$ViewBase*)self)->draw_children = (void*)SuiCore$ViewBase$draw_children;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiCore$ViewBase$draw_self;
	((SuiCore$ViewBase*)self)->invalidDraw = (void*)SuiCore$ViewBase$invalidDraw;
	((SuiCore$ViewBase*)self)->canLayoutByParent = (void*)SuiCore$ViewBase$canLayoutByParent;
	((SuiCore$ViewBase*)self)->setVisible = (void*)SuiCore$ViewBase$setVisible;
	((SuiCore$ViewBase*)self)->setHover = (void*)SuiCore$ViewBase$setHover;
	((SuiCore$ViewBase*)self)->onHoverChanged = (void*)SuiCore$ViewBase$onHoverChanged;
	((SuiCore$Node*)self)->toString = (void*)SuiCore$ViewBase$toString;
}

// init function

void SuiCore$ViewBase_init(SuiCore$ViewBase *self, void *pOwner){
    Vtable_SuiCore$ViewBase_init(&_vtable_SuiCore$ViewBase);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$ViewBase;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$ViewBase_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$ViewBase * SuiCore$ViewBase_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$ViewBase *self = calloc(1, sizeof(SuiCore$ViewBase));
	
    SuiCore$ViewBase_init(self, pOwner);
    return self;
}


// class members
Orc$List *  SuiCore$ViewBase$gocLayoutCells(SuiCore$ViewBase *  self){
	if (self->layoutCells == NULL) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiCore$ViewBase, layoutCells) , Orc$List_new(&tmpNewOwner_1) ) ;
	}
	return self->layoutCells; 
}


SuiCore$LayoutCell *  SuiCore$ViewBase$getLayoutCellByType(SuiCore$ViewBase *  self, Vtable_Object *  vt){
	Orc$List *  cells = self->gocLayoutCells(self) ;
	for (int  i = 0; i < cells->size(cells) ; i++) {
		Object *  cell = cells->get(cells, i) ;
		if (Orc_instanceof((Object*)cell, (Vtable_Object*)vt)) {
			return (SuiCore$LayoutCell * )cell; 
		}
	}
	return NULL; 
}


SuiCore$ViewBase *  SuiCore$ViewBase$getChildViewAt(SuiCore$ViewBase *  self, int  at){
	int  count = 0;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  view = self->getChildAsView(self, i) ;
		if (view) {
			at--;
			if (at < 0) {
				return view; 
			}
		}
	}
	return NULL; 
}


SuiCore$ViewBase *  SuiCore$ViewBase$getChildAsView(SuiCore$ViewBase *  self, int  at){
	Object *  o = ((SuiCore$Node * )self)->children->get(((SuiCore$Node * )self)->children, at) ;
	if (Orc_instanceof((Object*)o, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		return (SuiCore$ViewBase * )o; 
	}
	return NULL; 
}


int  SuiCore$ViewBase$getChildrenViewCount(SuiCore$ViewBase *  self){
	int  count = 0;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  view = self->getChildAsView(self, i) ;
		if (view && view->visible) {
			count++;
		}
	}
	return count; 
}


SuiCore$Rect SuiCore$ViewBase$getScreenRect(SuiCore$ViewBase *  self){
	SuiCore$Rect r = self->get_abs_rect(self) ;
	Sui$Window *  win = ((SuiCore$Node * )self)->getWindow(self) ;
	if (win) {
		SuiCore$Vec2 wr = win->getPos(win) ;
		SuiCore$Rect$offset(&r, wr.x, wr.y) ;
	}
	return r; 
}


SuiCore$Rect SuiCore$ViewBase$get_abs_rect(SuiCore$ViewBase *  self){
	SuiCore$Vec2 pos = self->localToWorld(self, 0.f, 0.f) ;
	SuiCore$Vec2 sizePos = self->localToWorld(self, self->frame.width, self->frame.height) ;
	SuiCore$Vec2 size = SuiCore$Vec2$sub(&sizePos, pos) ;
	return SuiCore$mkRect(pos.x, pos.y, size.x, size.y) ; 
}


bool  SuiCore$ViewBase$_hitTestClientRect(SuiCore$ViewBase *  self, SuiCore$Rect *  r, float  x, float  y){
	r->x = r->x - self->hitTestPadding.left;
	r->y = r->y - self->hitTestPadding.top;
	r->w = r->w + SuiCore$Inset$hor(&self->hitTestPadding) ;
	r->h = r->h + SuiCore$Inset$ver(&self->hitTestPadding) ;
	if (SuiCore$Rect$containsPosition(r, x, y) ) {
		return true; 
	}
	return false; 
}


bool  SuiCore$ViewBase$_hitTestSelf(SuiCore$ViewBase *  self, float  x, float  y){
	SuiCore$Rect r = self->get_abs_rect(self) ;
	return self->_hitTestClientRect(self, &r, x, y) ; 
}


void  SuiCore$ViewBase$_on_invalidLayout(SuiCore$ViewBase *  self){
	
}


void  SuiCore$ViewBase$_on_invalidDraw(SuiCore$ViewBase *  self){
	
}


void  SuiCore$ViewBase$resetViewTreeDirty(SuiCore$ViewBase *  self){
	
}


void  SuiCore$ViewBase$invalidReact(SuiCore$ViewBase *  self){
	SuiCore$Node$invalidReact(self) ;
	self->invalidLayout(self) ;
}


SuiCore$Vec2 SuiCore$ViewBase$localToWorld(SuiCore$ViewBase *  self, float  x, float  y){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	SuiCore$Vec3 p = SuiCore$Mat2d$transformPoint(&self->_world_transform, x, y, 0.f) ;
	ret.x = p.x;
	ret.y = p.y;
	return ret; 
}


SuiCore$Vec2 SuiCore$ViewBase$worldToLocal(SuiCore$ViewBase *  self, float  x, float  y){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	SuiCore$Mat2d inv = self->_world_transform;
	SuiCore$Mat2d$inverse(&inv) ;
	SuiCore$Vec3 p = SuiCore$Mat2d$transformPoint(&inv, x, y, 0.f) ;
	ret.x = p.x;
	ret.y = p.y;
	return ret; 
}


SuiCore$ViewBase *  SuiCore$ViewBase$hitTest(SuiCore$ViewBase *  self, float  x, float  y){
	if (Orc$String$equals(self->hitTestType, "none") ) {
		return NULL; 
	}
	if (Orc$String$equals(self->hitTestType, "nochildren") ) {
		if (self->_hitTestSelf(self, x, y) ) {
			return self; 
		}
		return NULL; 
	}
	SuiCore$ViewBase *  found = self->hitTestChildren(self, x, y) ;
	if (found) {
		return found; 
	}
	if (Orc$String$equals(self->hitTestType, "onlychildren") ) {
		return NULL; 
	}
	if (self->_hitTestSelf(self, x, y) ) {
		return self; 
	}
	return NULL; 
}


SuiCore$ViewBase *  SuiCore$ViewBase$hitTestChildren(SuiCore$ViewBase *  self, float  x, float  y){
	int  l = ((SuiCore$Node * )self)->children->size(((SuiCore$Node * )self)->children) ;
	for (int  i = l - 1; i >= 0; i--) {
		SuiCore$ViewBase *  kid_view = self->getChildAsView(self, i) ;
		if (kid_view && kid_view->visible) {
			SuiCore$ViewBase *  found = kid_view->hitTest(kid_view, x, y) ;
			if (found) {
				return found; 
			}
		}
	}
	return NULL; 
}


int  SuiCore$ViewBase$viewIndexOf(SuiCore$ViewBase *  self, SuiCore$Node *  child){
	if (!(Orc_instanceof((Object*)child, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL)))) {
		return -1; 
	}
	int  at = -1;
	int  l = ((SuiCore$Node * )self)->children->size(((SuiCore$Node * )self)->children) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Node *  n = (SuiCore$Node * )((SuiCore$Node * )self)->children->get(((SuiCore$Node * )self)->children, i) ;
		if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
			at++;
		}
		if (n == child) {
			return at; 
		}
	}
	return -1; 
}


int  SuiCore$ViewBase$viewIndexInParent(SuiCore$ViewBase *  self){
	if (Orc_instanceof((Object*)((SuiCore$Node * )self)->parent, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
		SuiCore$ViewBase *  vb = (SuiCore$ViewBase * )((SuiCore$Node * )self)->parent;
		return vb->viewIndexOf(vb, self) ; 
	}
	return -1; 
}


void  SuiCore$ViewBase$markLayoutStart(SuiCore$ViewBase *  self){
	self->frame.timesInOneLayout = 0;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = self->getChildAsView(self, i) ;
		if (v) {
			v->markLayoutStart(v) ;
		}
	}
}


void  SuiCore$ViewBase$printLayoutTimes(SuiCore$ViewBase *  self, int  tab){
	for (int  i = 0; i < tab; i++) {
		printf("\t") ;
	}
	const char *  className = Object_getClassName(self) ;
	printf("%s:%d\n", className, self->frame.timesInOneLayout) ;
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = self->getChildAsView(self, i) ;
		if (v) {
			v->printLayoutTimes(v, tab + 1) ;
		}
	}
}


void  SuiCore$ViewBase$layoutContent(SuiCore$ViewBase *  self, SuiCore$Frame *  contentCtx){
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  v = self->getChildAsView(self, i) ;
		if (v) {
			v->frame.minWidth = 0;
			v->frame.minHeight = 0;
			v->frame.maxWidth = INFINITY;
			v->frame.maxHeight = INFINITY;
			v->layout(v, &v->frame) ;
		}
	}
}


void  SuiCore$ViewBase$layout(SuiCore$ViewBase *  self, SuiCore$Frame *  ctx){
	SuiCore$Frame$incTimesInOneLayout(ctx) ;
	self->layoutContent(self, ctx) ;
}


void  SuiCore$ViewBase$invalidLayout(SuiCore$ViewBase *  self){
	SuiCore$App *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiCore$App_use(&tmpReturn_1) )->invalidLayout(tmpThis_1) ;
}


void  SuiCore$ViewBase$draw(SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas){
	SuiCore$Canvas$save(canvas) ;
	float  l = self->frame.x;
	float  t = self->frame.y;
	SuiCore$Canvas$translate(canvas, l, t) ;
	SuiCore$Canvas$transform(canvas, self->transform) ;
	SuiCore$Canvas$currentTransform(canvas, &self->_world_transform) ;
	{
		self->draw_self(self, canvas) ;
		self->draw_children(self, canvas) ;
	}
	SuiCore$Canvas$restore(canvas) ;
}


void  SuiCore$ViewBase$draw_children(SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas){
	int  l = ((SuiCore$Node * )self)->getChildrenCount(self) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$ViewBase *  view = self->getChildAsView(self, i) ;
		if (view && view->visible) {
			view->draw(view, canvas) ;
		}
	}
}


void  SuiCore$ViewBase$draw_self(SuiCore$ViewBase *  self, SuiCore$Canvas *  canvas){
	SuiCore$Canvas$fillColorByInt32(canvas, (0xff00ff33)) ;
	SuiCore$Canvas$strokeColorByInt32(canvas, (0xffff0033)) ;
	SuiCore$Canvas$strokeWidth(canvas, 10) ;
	SuiCore$Canvas$beginPath(canvas) ;
	SuiCore$Canvas$rect(canvas, 10, 10, 100, 100) ;
	SuiCore$Canvas$fill(canvas) ;
	SuiCore$Canvas$stroke(canvas) ;
}


void  SuiCore$ViewBase$invalidDraw(SuiCore$ViewBase *  self){
	SuiCore$App *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiCore$App_use(&tmpReturn_1) )->invalidDraw(tmpThis_1) ;
}


bool  SuiCore$ViewBase$canLayoutByParent(SuiCore$ViewBase *  self){
	return self->visible; 
}


void  SuiCore$ViewBase$setVisible(SuiCore$ViewBase *  self, bool  v){
	if (v != self->visible) {
		self->visible = v;
		self->invalidLayout(self) ;
	}
}


void  SuiCore$ViewBase$setHover(SuiCore$ViewBase *  self, bool  v){
	if (self->hover != v) {
		self->hover = v;
		self->onHoverChanged(self) ;
	}
}


void  SuiCore$ViewBase$onHoverChanged(SuiCore$ViewBase *  self){
	if (self->cbOnHoverChanged) {
		(*(self->cbOnHoverChanged))((void * )(self->cbOnHoverChanged)) ;
	}
}


Orc$String*  SuiCore$ViewBase$toString(Orc$String **  __outRef__, SuiCore$ViewBase *  self){
	const char *  className = Object_getClassName(self) ;
	char  tmp[256];
	snprintf(tmp, sizeof(tmp) , "[%f,%f,%f,%f]", self->frame.x, self->frame.y, self->frame.width, self->frame.height) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$add(Orc$String$addString(Orc$String$add(Orc$str(&tmpReturn_1, className) , ":") , ((SuiCore$Node * )self)->name) , tmp) ) ; 
}



SuiCore$ViewBase *  SuiCore$hitTestChildren_withZ(SuiCore$ViewBase *  ins, float  x, float  y){
	int  l = ((SuiCore$Node * )ins)->children->size(((SuiCore$Node * )ins)->children) ;
	SuiCore$ViewBase *  ret = NULL;
	for (int  i = l - 1; i >= 0; i--) {
		SuiCore$ViewBase *  kid_view = ins->getChildAsView(ins, i) ;
		if (kid_view && kid_view->visible) {
			SuiCore$ViewBase *  found = kid_view->hitTest(kid_view, x, y) ;
			if (found) {
				if (ret == NULL || found->z > ret->z) {
					ret = found;
				}
			}
		}
	}
	return ret; 
}



