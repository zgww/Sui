
#include "SceneTransform_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../nanovg/nanovg.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Json/cJSON.h"
#include "../Orc/Orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Number_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Mat2d_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../SuiDesigner/Serial/BiJson_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Json/Json_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/RegisterNodes_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "../SuiDesigner/UiAction_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/Gizmo_orc.h"
#include "../SuiDesigner/EditCtx_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "./Horo2dSceneView_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_HoroEditor$SceneTransform _vtable_HoroEditor$SceneTransform;

// init meta

void HoroEditor$SceneTransform_initMeta(Vtable_HoroEditor$SceneTransform *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "_translate", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(HoroEditor$SceneTransform, _translate), false, false, 0);
	orc_metaField_primitive(&pNext, "_scale", OrcMetaType_float, offsetof(HoroEditor$SceneTransform, _scale), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "mat", SuiCore$Mat2d_getOrInitMetaStruct(), offsetof(HoroEditor$SceneTransform, mat), false, false, 0);

	orc_metaField_method(&pNext, "setScale", offsetof(HoroEditor$SceneTransform, setScale));
	orc_metaField_method(&pNext, "updateMat", offsetof(HoroEditor$SceneTransform, updateMat));
	orc_metaField_method(&pNext, "translate", offsetof(HoroEditor$SceneTransform, translate));
	orc_metaField_method(&pNext, "setTranslate", offsetof(HoroEditor$SceneTransform, setTranslate));
	orc_metaField_method(&pNext, "identity", offsetof(HoroEditor$SceneTransform, identity));
	orc_metaField_method(&pNext, "performScaleByWheelEventAndSceneView", offsetof(HoroEditor$SceneTransform, performScaleByWheelEventAndSceneView));
}


// vtable init


Vtable_HoroEditor$SceneTransform* Vtable_HoroEditor$SceneTransform_init(Vtable_HoroEditor$SceneTransform* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$SceneTransform;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$SceneTransform_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$SceneTransform";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$SceneTransform_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void HoroEditor$SceneTransform_fini(HoroEditor$SceneTransform *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void HoroEditor$SceneTransform_init_fields(HoroEditor$SceneTransform *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)HoroEditor$SceneTransform_fini;
	//fields
    {
	((HoroEditor$SceneTransform*)self)->_scale = 1;
	((HoroEditor$SceneTransform*)self)->mat = SuiCore$mkMat2d() ;
    }
	((HoroEditor$SceneTransform*)self)->setScale = (void*)HoroEditor$SceneTransform$setScale;
	((HoroEditor$SceneTransform*)self)->updateMat = (void*)HoroEditor$SceneTransform$updateMat;
	((HoroEditor$SceneTransform*)self)->translate = (void*)HoroEditor$SceneTransform$translate;
	((HoroEditor$SceneTransform*)self)->setTranslate = (void*)HoroEditor$SceneTransform$setTranslate;
	((HoroEditor$SceneTransform*)self)->identity = (void*)HoroEditor$SceneTransform$identity;
	((HoroEditor$SceneTransform*)self)->performScaleByWheelEventAndSceneView = (void*)HoroEditor$SceneTransform$performScaleByWheelEventAndSceneView;
}

// init function

void HoroEditor$SceneTransform_init(HoroEditor$SceneTransform *self, void *pOwner){
    Vtable_HoroEditor$SceneTransform_init(&_vtable_HoroEditor$SceneTransform);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$SceneTransform;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$SceneTransform_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$SceneTransform * HoroEditor$SceneTransform_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$SceneTransform *self = calloc(1, sizeof(HoroEditor$SceneTransform));
	
    HoroEditor$SceneTransform_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$SceneTransform$setScale(HoroEditor$SceneTransform *  self, float  s){
	self->_scale = s;
	self->updateMat(self) ;
}


void  HoroEditor$SceneTransform$updateMat(HoroEditor$SceneTransform *  self){
	SuiCore$Mat2d$identity(&self->mat) ;
	SuiCore$Mat2d$translate(&self->mat, self->_translate.x, self->_translate.y, self->_translate.z) ;
	SuiCore$Mat2d$scale(&self->mat, self->_scale, self->_scale, self->_scale) ;
}


void  HoroEditor$SceneTransform$translate(HoroEditor$SceneTransform *  self, float  x, float  y, float  z){
	self->_translate = SuiCore$Vec3$add3f(&self->_translate, x, y, z) ;
	self->updateMat(self) ;
}


void  HoroEditor$SceneTransform$setTranslate(HoroEditor$SceneTransform *  self, float  x, float  y, float  z){
	SuiCore$Vec3$set(&self->_translate, x, y, z) ;
	self->updateMat(self) ;
}


void  HoroEditor$SceneTransform$identity(HoroEditor$SceneTransform *  self){
	SuiCore$Vec3$set(&self->_translate, 0, 0, 0) ;
	self->_scale = 1;
	self->updateMat(self) ;
}


void  HoroEditor$SceneTransform$performScaleByWheelEventAndSceneView(HoroEditor$SceneTransform *  self, SuiCore$WheelEvent *  we, HoroEditor$Horo2dSceneView *  v){
	SuiCore$Vec2 viewPos = ((SuiCore$ViewBase * )v)->worldToLocal(v, ((SuiCore$MouseEvent * )we)->clientX, ((SuiCore$MouseEvent * )we)->clientY) ;
	SuiCore$Mat2d invMat = SuiCore$Mat2d$inverseNew(&self->mat) ;
	SuiCore$Vec3 scenePos = SuiCore$Mat2d$transformPoint(&invMat, viewPos.x, viewPos.y, 0) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  opt = v->degree->findAndReturnOffset((opt = NULL,&opt), v->degree, self->_scale, we->deltaY > 0 ? 1 : -1) ;
	urgc_set_field_class(v->degree, (void * )offsetof(SuiDesigner$DrawDegree, curOption) , opt) ;
	v->degree->curScale = opt->value;
	self->setScale(self, opt->value) ;
	SuiCore$Vec3 newViewPos = SuiCore$Mat2d$transformPoint(&self->mat, scenePos.x, scenePos.y, 0) ;
	printf("scale. client:%d,%d, viewPos:%f,%f, scenePos:%f,%f,newViewPos:%f,%f, delta:%f,%f\n", ((SuiCore$MouseEvent * )we)->clientX, ((SuiCore$MouseEvent * )we)->clientY, viewPos.x, viewPos.y, scenePos.x, scenePos.y, newViewPos.x, newViewPos.y, viewPos.x - newViewPos.x, viewPos.y - newViewPos.y) ;
	self->translate(self, viewPos.x - newViewPos.x, viewPos.y - newViewPos.y, 0) ;
	printf("wheel. result:%f opt:%f,degree:%f\n", self->_scale, opt->value, opt->degree) ;
}





