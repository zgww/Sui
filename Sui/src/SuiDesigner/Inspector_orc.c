
#include "Inspector_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include "../Json/cJSON.h"
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


// static struct 
typedef struct tagSuiDesigner$__Block_338_82 SuiDesigner$__Block_338_82;

typedef struct tagSuiDesigner$__Block_410_87 SuiDesigner$__Block_410_87;

typedef struct tagSuiDesigner$__Block_702_43 SuiDesigner$__Block_702_43;

typedef struct tagSuiDesigner$__Closure_349_30 SuiDesigner$__Closure_349_30;

typedef struct tagSuiDesigner$__Closure_354_32 SuiDesigner$__Closure_354_32;

typedef struct tagSuiDesigner$__Closure_427_38 SuiDesigner$__Closure_427_38;

typedef struct tagSuiDesigner$__Closure_448_38 SuiDesigner$__Closure_448_38;

typedef struct tagSuiDesigner$__Closure_477_42 SuiDesigner$__Closure_477_42;

typedef struct tagSuiDesigner$__Closure_485_54 SuiDesigner$__Closure_485_54;

typedef struct tagSuiDesigner$__Closure_520_40 SuiDesigner$__Closure_520_40;

typedef struct tagSuiDesigner$__Closure_526_46 SuiDesigner$__Closure_526_46;

typedef struct tagSuiDesigner$__Closure_565_58 SuiDesigner$__Closure_565_58;

typedef struct tagSuiDesigner$__Closure_577_38 SuiDesigner$__Closure_577_38;

typedef struct tagSuiDesigner$__Closure_609_54 SuiDesigner$__Closure_609_54;

typedef struct tagSuiDesigner$__Closure_618_39 SuiDesigner$__Closure_618_39;

typedef struct tagSuiDesigner$__Closure_639_54 SuiDesigner$__Closure_639_54;

typedef struct tagSuiDesigner$__Closure_647_45 SuiDesigner$__Closure_647_45;

typedef struct tagSuiDesigner$__Closure_660_43 SuiDesigner$__Closure_660_43;

typedef struct tagSuiDesigner$__Closure_680_43 SuiDesigner$__Closure_680_43;

typedef struct tagSuiDesigner$__Closure_710_39 SuiDesigner$__Closure_710_39;

typedef struct tagSuiDesigner$__Closure_723_39 SuiDesigner$__Closure_723_39;

typedef struct tagSuiDesigner$__Closure_756_34 SuiDesigner$__Closure_756_34;



struct tagSuiDesigner$__Block_338_82 {
	Vtable_Object *  vtable ;
	OrcMetaField *  headmf ;
	SuiDesigner$Inspector*  self ;
	Object*  obj ;
};





struct tagSuiDesigner$__Block_410_87 {
	char *  name ;
	OrcMetaField *  mf ;
	Object *  obj ;
	SuiDesigner$Inspector*  self ;
	Object *  tmpObj ;
};





struct tagSuiDesigner$__Block_702_43 {
	SuiCore$Vec2 v ;
};





struct tagSuiDesigner$__Closure_349_30 {
	void  (*invoke)(SuiDesigner$__Closure_349_30 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_338_82*  __var___Block_338_82 ;
};





struct tagSuiDesigner$__Closure_354_32 {
	void  (*invoke)(SuiDesigner$__Closure_354_32 *  self, SuiCore$Node *  parent);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_338_82*  __var___Block_338_82 ;
};





struct tagSuiDesigner$__Closure_427_38 {
	void  (*invoke)(SuiDesigner$__Closure_427_38 *  self, int  i, Orc$String*  label);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_448_38 {
	void  (*invoke)(SuiDesigner$__Closure_448_38 *  self, int  i, Orc$String*  label);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_477_42 {
	void  (*invoke)(SuiDesigner$__Closure_477_42 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_485_54 {
	void  (*invoke)(SuiDesigner$__Closure_485_54 *  self, Orc$String*  newpath);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_520_40 {
	void  (*invoke)(SuiDesigner$__Closure_520_40 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_526_46 {
	void  (*invoke)(SuiDesigner$__Closure_526_46 *  self, Orc$String*  newpath);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_565_58 {
	void  (*invoke)(SuiDesigner$__Closure_565_58 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_577_38 {
	void  (*invoke)(SuiDesigner$__Closure_577_38 *  self, int  newcolor);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_609_54 {
	void  (*invoke)(SuiDesigner$__Closure_609_54 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_618_39 {
	void  (*invoke)(SuiDesigner$__Closure_618_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_639_54 {
	void  (*invoke)(SuiDesigner$__Closure_639_54 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_647_45 {
	void  (*invoke)(SuiDesigner$__Closure_647_45 *  self, SuiView$Switch *  v);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_660_43 {
	void  (*invoke)(SuiDesigner$__Closure_660_43 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_680_43 {
	void  (*invoke)(SuiDesigner$__Closure_680_43 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_710_39 {
	void  (*invoke)(SuiDesigner$__Closure_710_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_702_43*  __var___Block_702_43 ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_723_39 {
	void  (*invoke)(SuiDesigner$__Closure_723_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_702_43*  __var___Block_702_43 ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





struct tagSuiDesigner$__Closure_756_34 {
	void  (*invoke)(SuiDesigner$__Closure_756_34 *  self, SuiDesigner$BezierEditView *  view);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_410_87*  __var___Block_410_87 ;
};





// static function declaration
static void  __finiBlock___Block_338_82(SuiDesigner$__Block_338_82 *  self);
static void  __finiBlock___Block_410_87(SuiDesigner$__Block_410_87 *  self);
static void  __finiBlock___Block_702_43(SuiDesigner$__Block_702_43 *  self);
static void  __fn___Closure_349_30(SuiDesigner$__Closure_349_30 *  self, SuiCore$Node *  o);
static void  __fini___Closure_349_30(SuiDesigner$__Closure_349_30 *  self);
static SuiDesigner$__Closure_349_30*  __make___Closure_349_30(SuiDesigner$__Closure_349_30 **  __outRef__, SuiDesigner$__Block_338_82 *  __var___Block_338_82);
static void  __fn___Closure_354_32(SuiDesigner$__Closure_354_32 *  self, SuiCore$Node *  parent);
static void  __fini___Closure_354_32(SuiDesigner$__Closure_354_32 *  self);
static SuiDesigner$__Closure_354_32*  __make___Closure_354_32(SuiDesigner$__Closure_354_32 **  __outRef__, SuiDesigner$__Block_338_82 *  __var___Block_338_82);
static void  __fn___Closure_427_38(SuiDesigner$__Closure_427_38 *  self, int  i, Orc$String*  label);
static void  __fini___Closure_427_38(SuiDesigner$__Closure_427_38 *  self);
static SuiDesigner$__Closure_427_38*  __make___Closure_427_38(SuiDesigner$__Closure_427_38 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_448_38(SuiDesigner$__Closure_448_38 *  self, int  i, Orc$String*  label);
static void  __fini___Closure_448_38(SuiDesigner$__Closure_448_38 *  self);
static SuiDesigner$__Closure_448_38*  __make___Closure_448_38(SuiDesigner$__Closure_448_38 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_477_42(SuiDesigner$__Closure_477_42 *  self, SuiCore$Event *  e);
static void  __fini___Closure_477_42(SuiDesigner$__Closure_477_42 *  self);
static SuiDesigner$__Closure_477_42*  __make___Closure_477_42(SuiDesigner$__Closure_477_42 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_485_54(SuiDesigner$__Closure_485_54 *  self, Orc$String*  newpath);
static void  __fini___Closure_485_54(SuiDesigner$__Closure_485_54 *  self);
static SuiDesigner$__Closure_485_54*  __make___Closure_485_54(SuiDesigner$__Closure_485_54 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_520_40(SuiDesigner$__Closure_520_40 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_520_40(SuiDesigner$__Closure_520_40 *  self);
static SuiDesigner$__Closure_520_40*  __make___Closure_520_40(SuiDesigner$__Closure_520_40 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_526_46(SuiDesigner$__Closure_526_46 *  self, Orc$String*  newpath);
static void  __fini___Closure_526_46(SuiDesigner$__Closure_526_46 *  self);
static SuiDesigner$__Closure_526_46*  __make___Closure_526_46(SuiDesigner$__Closure_526_46 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_565_58(SuiDesigner$__Closure_565_58 *  self, SuiCore$Node *  o);
static void  __fini___Closure_565_58(SuiDesigner$__Closure_565_58 *  self);
static SuiDesigner$__Closure_565_58*  __make___Closure_565_58(SuiDesigner$__Closure_565_58 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_577_38(SuiDesigner$__Closure_577_38 *  self, int  newcolor);
static void  __fini___Closure_577_38(SuiDesigner$__Closure_577_38 *  self);
static SuiDesigner$__Closure_577_38*  __make___Closure_577_38(SuiDesigner$__Closure_577_38 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_609_54(SuiDesigner$__Closure_609_54 *  self, SuiCore$Node *  o);
static void  __fini___Closure_609_54(SuiDesigner$__Closure_609_54 *  self);
static SuiDesigner$__Closure_609_54*  __make___Closure_609_54(SuiDesigner$__Closure_609_54 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_618_39(SuiDesigner$__Closure_618_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_618_39(SuiDesigner$__Closure_618_39 *  self);
static SuiDesigner$__Closure_618_39*  __make___Closure_618_39(SuiDesigner$__Closure_618_39 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_639_54(SuiDesigner$__Closure_639_54 *  self, SuiCore$Node *  o);
static void  __fini___Closure_639_54(SuiDesigner$__Closure_639_54 *  self);
static SuiDesigner$__Closure_639_54*  __make___Closure_639_54(SuiDesigner$__Closure_639_54 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_647_45(SuiDesigner$__Closure_647_45 *  self, SuiView$Switch *  v);
static void  __fini___Closure_647_45(SuiDesigner$__Closure_647_45 *  self);
static SuiDesigner$__Closure_647_45*  __make___Closure_647_45(SuiDesigner$__Closure_647_45 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_660_43(SuiDesigner$__Closure_660_43 *  self, SuiView$EditText *  et);
static void  __fini___Closure_660_43(SuiDesigner$__Closure_660_43 *  self);
static SuiDesigner$__Closure_660_43*  __make___Closure_660_43(SuiDesigner$__Closure_660_43 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_680_43(SuiDesigner$__Closure_680_43 *  self, SuiView$EditText *  et);
static void  __fini___Closure_680_43(SuiDesigner$__Closure_680_43 *  self);
static SuiDesigner$__Closure_680_43*  __make___Closure_680_43(SuiDesigner$__Closure_680_43 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_710_39(SuiDesigner$__Closure_710_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_710_39(SuiDesigner$__Closure_710_39 *  self);
static SuiDesigner$__Closure_710_39*  __make___Closure_710_39(SuiDesigner$__Closure_710_39 **  __outRef__, SuiDesigner$__Block_702_43 *  __var___Block_702_43, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_723_39(SuiDesigner$__Closure_723_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_723_39(SuiDesigner$__Closure_723_39 *  self);
static SuiDesigner$__Closure_723_39*  __make___Closure_723_39(SuiDesigner$__Closure_723_39 **  __outRef__, SuiDesigner$__Block_702_43 *  __var___Block_702_43, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  __fn___Closure_756_34(SuiDesigner$__Closure_756_34 *  self, SuiDesigner$BezierEditView *  view);
static void  __fini___Closure_756_34(SuiDesigner$__Closure_756_34 *  self);
static SuiDesigner$__Closure_756_34*  __make___Closure_756_34(SuiDesigner$__Closure_756_34 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87);
static void  setAttr(const char *  name, Json$Json*  jv);



//vtable instance
Vtable_SuiDesigner$InspectorOption _vtable_SuiDesigner$InspectorOption;

// init meta

void SuiDesigner$InspectorOption_initMeta(Vtable_SuiDesigner$InspectorOption *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_int, offsetof(SuiDesigner$InspectorOption, value), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "label", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$InspectorOption, label), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$InspectorOption* Vtable_SuiDesigner$InspectorOption_init(Vtable_SuiDesigner$InspectorOption* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspectorOption;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspectorOption_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspectorOption";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspectorOption_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspectorOption_fini(SuiDesigner$InspectorOption *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$InspectorOption*)self)->label);

}

// init fields function


void SuiDesigner$InspectorOption_init_fields(SuiDesigner$InspectorOption *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspectorOption_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspectorOption*)self)->label, NULL);
    }
	
}

// init function

void SuiDesigner$InspectorOption_init(SuiDesigner$InspectorOption *self, void *pOwner){
    Vtable_SuiDesigner$InspectorOption_init(&_vtable_SuiDesigner$InspectorOption);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspectorOption;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspectorOption_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspectorOption * SuiDesigner$InspectorOption_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspectorOption *self = calloc(1, sizeof(SuiDesigner$InspectorOption));
	
    SuiDesigner$InspectorOption_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$InspectorAttrInfo _vtable_SuiDesigner$InspectorAttrInfo;

// init meta

void SuiDesigner$InspectorAttrInfo_initMeta(Vtable_SuiDesigner$InspectorAttrInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "key", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$InspectorAttrInfo, key), true, false, 1);
	orc_metaField_primitive(&pNext, "bColor", OrcMetaType_bool, offsetof(SuiDesigner$InspectorAttrInfo, bColor), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "bImageSrc", OrcMetaType_bool, offsetof(SuiDesigner$InspectorAttrInfo, bImageSrc), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "bFileSrc", OrcMetaType_bool, offsetof(SuiDesigner$InspectorAttrInfo, bFileSrc), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "bSelect", OrcMetaType_bool, offsetof(SuiDesigner$InspectorAttrInfo, bSelect), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "bSlider", OrcMetaType_bool, offsetof(SuiDesigner$InspectorAttrInfo, bSlider), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "fromValue", OrcMetaType_float, offsetof(SuiDesigner$InspectorAttrInfo, fromValue), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "toValue", OrcMetaType_float, offsetof(SuiDesigner$InspectorAttrInfo, toValue), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "options", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$InspectorAttrInfo, options), true, false, 1);

	orc_metaField_method(&pNext, "gocOptions", offsetof(SuiDesigner$InspectorAttrInfo, gocOptions));
	orc_metaField_method(&pNext, "setOption", offsetof(SuiDesigner$InspectorAttrInfo, setOption));
	orc_metaField_method(&pNext, "getOptionLabels", offsetof(SuiDesigner$InspectorAttrInfo, getOptionLabels));
}


// vtable init


Vtable_SuiDesigner$InspectorAttrInfo* Vtable_SuiDesigner$InspectorAttrInfo_init(Vtable_SuiDesigner$InspectorAttrInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspectorAttrInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspectorAttrInfo_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspectorAttrInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspectorAttrInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspectorAttrInfo_fini(SuiDesigner$InspectorAttrInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$InspectorAttrInfo*)self)->key);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$InspectorAttrInfo*)self)->options);

}

// init fields function


void SuiDesigner$InspectorAttrInfo_init_fields(SuiDesigner$InspectorAttrInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspectorAttrInfo_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspectorAttrInfo*)self)->key, Orc$str(&tmpReturn_1, "") );
	((SuiDesigner$InspectorAttrInfo*)self)->bColor = false;
	((SuiDesigner$InspectorAttrInfo*)self)->bImageSrc = false;
	((SuiDesigner$InspectorAttrInfo*)self)->bFileSrc = false;
	((SuiDesigner$InspectorAttrInfo*)self)->bSelect = false;
	((SuiDesigner$InspectorAttrInfo*)self)->bSlider = false;
	((SuiDesigner$InspectorAttrInfo*)self)->fromValue = 0.0;
	((SuiDesigner$InspectorAttrInfo*)self)->toValue = 0.0;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspectorAttrInfo*)self)->options, NULL);
    }
	((SuiDesigner$InspectorAttrInfo*)self)->gocOptions = (void*)SuiDesigner$InspectorAttrInfo$gocOptions;
	((SuiDesigner$InspectorAttrInfo*)self)->setOption = (void*)SuiDesigner$InspectorAttrInfo$setOption;
	((SuiDesigner$InspectorAttrInfo*)self)->getOptionLabels = (void*)SuiDesigner$InspectorAttrInfo$getOptionLabels;
}

// init function

void SuiDesigner$InspectorAttrInfo_init(SuiDesigner$InspectorAttrInfo *self, void *pOwner){
    Vtable_SuiDesigner$InspectorAttrInfo_init(&_vtable_SuiDesigner$InspectorAttrInfo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspectorAttrInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspectorAttrInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspectorAttrInfo * SuiDesigner$InspectorAttrInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspectorAttrInfo *self = calloc(1, sizeof(SuiDesigner$InspectorAttrInfo));
	
    SuiDesigner$InspectorAttrInfo_init(self, pOwner);
    return self;
}


// class members
Orc$List*  SuiDesigner$InspectorAttrInfo$gocOptions(Orc$List **  __outRef__, SuiDesigner$InspectorAttrInfo *  self){
	if (!self->options) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$InspectorAttrInfo, options) , Orc$List_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, self->options) ; 
}


void  SuiDesigner$InspectorAttrInfo$setOption(SuiDesigner$InspectorAttrInfo *  self, int  value, const char *  label){
	URGC_VAR_CLEANUP_CLASS Orc$List*  opts = self->gocOptions((opts = NULL,&opts), self) ;
	for (int  i = 0; i < opts->size(opts) ; i++) {
		SuiDesigner$InspectorOption *  opt = (SuiDesigner$InspectorOption * )opts->get(opts, i) ;
		if (opt->value == value) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_field_class(opt, (void * )offsetof(SuiDesigner$InspectorOption, label) , Orc$str(&tmpReturn_1, label) ) ;
			return ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorOption*  opt = (opt=NULL,urgc_init_var_class((void**)&opt, SuiDesigner$InspectorOption_new(&opt) ));
	opt->value = value;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(opt, (void * )offsetof(SuiDesigner$InspectorOption, label) , Orc$str(&tmpReturn_2, label) ) ;
	opts->add(opts, opt) ;
}


Orc$List*  SuiDesigner$InspectorAttrInfo$getOptionLabels(Orc$List **  __outRef__, SuiDesigner$InspectorAttrInfo *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  labels = (labels=NULL,urgc_init_var_class((void**)&labels, Orc$List_new(&labels) ));
	if (self->options) {
		for (int  i = 0; i < self->options->size(self->options) ; i++) {
			SuiDesigner$InspectorOption *  opt = (SuiDesigner$InspectorOption * )self->options->get(self->options, i) ;
			labels->add(labels, opt->label) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, labels) ; 
}




//vtable instance
Vtable_SuiDesigner$Inspector _vtable_SuiDesigner$Inspector;

// init meta

void SuiDesigner$Inspector_initMeta(Vtable_SuiDesigner$Inspector *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "obj", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiDesigner$Inspector, obj), true, false, 1);
	orc_metaField_class(&pNext, "parentNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$Inspector, parentNode), true, false, 1);
	orc_metaField_class(&pNext, "attrInfoMap", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiDesigner$Inspector, attrInfoMap), true, false, 1);
	orc_metaField_primitive(&pNext, "useDefaultInspect", OrcMetaType_bool, offsetof(SuiDesigner$Inspector, useDefaultInspect), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "reset", offsetof(SuiDesigner$Inspector, reset));
	orc_metaField_method(&pNext, "getAttrInfo", offsetof(SuiDesigner$Inspector, getAttrInfo));
	orc_metaField_method(&pNext, "gocAttrInfo", offsetof(SuiDesigner$Inspector, gocAttrInfo));
	orc_metaField_method(&pNext, "markAttrAsColor", offsetof(SuiDesigner$Inspector, markAttrAsColor));
	orc_metaField_method(&pNext, "markAttrAsImageSrc", offsetof(SuiDesigner$Inspector, markAttrAsImageSrc));
	orc_metaField_method(&pNext, "markAttrAsFileSrc", offsetof(SuiDesigner$Inspector, markAttrAsFileSrc));
	orc_metaField_method(&pNext, "markAttrAsSlider", offsetof(SuiDesigner$Inspector, markAttrAsSlider));
	orc_metaField_method(&pNext, "markAttrAsSelect", offsetof(SuiDesigner$Inspector, markAttrAsSelect));
	orc_metaField_method(&pNext, "clearAttrInfoMap", offsetof(SuiDesigner$Inspector, clearAttrInfoMap));
	orc_metaField_method(&pNext, "setField", offsetof(SuiDesigner$Inspector, setField));
	orc_metaField_method(&pNext, "reactObject_withExtendsChain", offsetof(SuiDesigner$Inspector, reactObject_withExtendsChain));
	orc_metaField_method(&pNext, "reactObject", offsetof(SuiDesigner$Inspector, reactObject));
	orc_metaField_method(&pNext, "inspect", offsetof(SuiDesigner$Inspector, inspect));
	orc_metaField_method(&pNext, "callOnInspect", offsetof(SuiDesigner$Inspector, callOnInspect));
	orc_metaField_method(&pNext, "countFieldsOfVtable", offsetof(SuiDesigner$Inspector, countFieldsOfVtable));
	orc_metaField_method(&pNext, "reactObject_byVtable", offsetof(SuiDesigner$Inspector, reactObject_byVtable));
	orc_metaField_method(&pNext, "reactObjectField", offsetof(SuiDesigner$Inspector, reactObjectField));
	orc_metaField_method(&pNext, "reactObjectFieldName", offsetof(SuiDesigner$Inspector, reactObjectFieldName));
	orc_metaField_method(&pNext, "reactObjectFieldRow", offsetof(SuiDesigner$Inspector, reactObjectFieldRow));
	orc_metaField_method(&pNext, "reactObjectField_do", offsetof(SuiDesigner$Inspector, reactObjectField_do));
}


// vtable init


Vtable_SuiDesigner$Inspector* Vtable_SuiDesigner$Inspector_init(Vtable_SuiDesigner$Inspector* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Inspector;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Inspector_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Inspector";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Inspector_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$Inspector_fini(SuiDesigner$Inspector *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Inspector*)self)->obj);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Inspector*)self)->parentNode);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Inspector*)self)->attrInfoMap);

}

// init fields function


void SuiDesigner$Inspector_init_fields(SuiDesigner$Inspector *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Inspector_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$Inspector*)self)->obj, NULL);
	urgc_set_field(self, (void**)&((SuiDesigner$Inspector*)self)->cbSetField, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$Inspector*)self)->parentNode, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Inspector*)self)->attrInfoMap, Orc$Map_new(&tmpNewOwner_1) );
	((SuiDesigner$Inspector*)self)->useDefaultInspect = true;
	urgc_set_field(self, (void**)&((SuiDesigner$Inspector*)self)->setAttr, NULL);
    }
	((SuiDesigner$Inspector*)self)->reset = (void*)SuiDesigner$Inspector$reset;
	((SuiDesigner$Inspector*)self)->getAttrInfo = (void*)SuiDesigner$Inspector$getAttrInfo;
	((SuiDesigner$Inspector*)self)->gocAttrInfo = (void*)SuiDesigner$Inspector$gocAttrInfo;
	((SuiDesigner$Inspector*)self)->markAttrAsColor = (void*)SuiDesigner$Inspector$markAttrAsColor;
	((SuiDesigner$Inspector*)self)->markAttrAsImageSrc = (void*)SuiDesigner$Inspector$markAttrAsImageSrc;
	((SuiDesigner$Inspector*)self)->markAttrAsFileSrc = (void*)SuiDesigner$Inspector$markAttrAsFileSrc;
	((SuiDesigner$Inspector*)self)->markAttrAsSlider = (void*)SuiDesigner$Inspector$markAttrAsSlider;
	((SuiDesigner$Inspector*)self)->markAttrAsSelect = (void*)SuiDesigner$Inspector$markAttrAsSelect;
	((SuiDesigner$Inspector*)self)->clearAttrInfoMap = (void*)SuiDesigner$Inspector$clearAttrInfoMap;
	((SuiDesigner$Inspector*)self)->setField = (void*)SuiDesigner$Inspector$setField;
	((SuiDesigner$Inspector*)self)->reactObject_withExtendsChain = (void*)SuiDesigner$Inspector$reactObject_withExtendsChain;
	((SuiDesigner$Inspector*)self)->reactObject = (void*)SuiDesigner$Inspector$reactObject;
	((SuiDesigner$Inspector*)self)->inspect = (void*)SuiDesigner$Inspector$inspect;
	((SuiDesigner$Inspector*)self)->callOnInspect = (void*)SuiDesigner$Inspector$callOnInspect;
	((SuiDesigner$Inspector*)self)->countFieldsOfVtable = (void*)SuiDesigner$Inspector$countFieldsOfVtable;
	((SuiDesigner$Inspector*)self)->reactObject_byVtable = (void*)SuiDesigner$Inspector$reactObject_byVtable;
	((SuiDesigner$Inspector*)self)->reactObjectField = (void*)SuiDesigner$Inspector$reactObjectField;
	((SuiDesigner$Inspector*)self)->reactObjectFieldName = (void*)SuiDesigner$Inspector$reactObjectFieldName;
	((SuiDesigner$Inspector*)self)->reactObjectFieldRow = (void*)SuiDesigner$Inspector$reactObjectFieldRow;
	((SuiDesigner$Inspector*)self)->reactObjectField_do = (void*)SuiDesigner$Inspector$reactObjectField_do;
}

// init function

void SuiDesigner$Inspector_init(SuiDesigner$Inspector *self, void *pOwner){
    Vtable_SuiDesigner$Inspector_init(&_vtable_SuiDesigner$Inspector);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Inspector;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Inspector_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Inspector * SuiDesigner$Inspector_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Inspector *self = calloc(1, sizeof(SuiDesigner$Inspector));
	
    SuiDesigner$Inspector_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$Inspector$reset(SuiDesigner$Inspector *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Inspector, obj) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Inspector, parentNode) , NULL) ;
	self->useDefaultInspect = false;
}


SuiDesigner$InspectorAttrInfo *  SuiDesigner$Inspector$getAttrInfo(SuiDesigner$Inspector *  self, const char *  key){
	return (SuiDesigner$InspectorAttrInfo * )self->attrInfoMap->get(self->attrInfoMap, key) ; 
}


SuiDesigner$InspectorAttrInfo*  SuiDesigner$Inspector$gocAttrInfo(SuiDesigner$InspectorAttrInfo **  __outRef__, SuiDesigner$Inspector *  self, const char *  key){
	{
		SuiDesigner$InspectorAttrInfo *  exist = self->getAttrInfo(self, key) ;
		if (exist) {
			return urgc_set_var_for_return_class((void ** )__outRef__, exist) ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorAttrInfo*  info = (info=NULL,urgc_init_var_class((void**)&info, SuiDesigner$InspectorAttrInfo_new(&info) ));
	Orc$String$set(info->key, key) ;
	self->attrInfoMap->put(self->attrInfoMap, key, info) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, info) ; 
}


void  SuiDesigner$Inspector$markAttrAsColor(SuiDesigner$Inspector *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorAttrInfo*  info = self->gocAttrInfo((info = NULL,&info), self, key) ;
	info->bColor = true;
}


void  SuiDesigner$Inspector$markAttrAsImageSrc(SuiDesigner$Inspector *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorAttrInfo*  info = self->gocAttrInfo((info = NULL,&info), self, key) ;
	info->bImageSrc = true;
}


void  SuiDesigner$Inspector$markAttrAsFileSrc(SuiDesigner$Inspector *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorAttrInfo*  info = self->gocAttrInfo((info = NULL,&info), self, key) ;
	info->bFileSrc = true;
}


void  SuiDesigner$Inspector$markAttrAsSlider(SuiDesigner$Inspector *  self, const char *  key, float  fromValue, float  toValue){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorAttrInfo*  info = self->gocAttrInfo((info = NULL,&info), self, key) ;
	info->bSlider = true;
	info->fromValue = fromValue;
	info->toValue = toValue;
}


SuiDesigner$InspectorAttrInfo*  SuiDesigner$Inspector$markAttrAsSelect(SuiDesigner$InspectorAttrInfo **  __outRef__, SuiDesigner$Inspector *  self, const char *  key){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspectorAttrInfo*  info = self->gocAttrInfo((info = NULL,&info), self, key) ;
	info->bSelect = true;
	return urgc_set_var_for_return_class((void ** )__outRef__, info) ; 
}


void  SuiDesigner$Inspector$clearAttrInfoMap(SuiDesigner$Inspector *  self){
	self->attrInfoMap->clear(self->attrInfoMap) ;
}


void  SuiDesigner$Inspector$setField(SuiDesigner$Inspector *  self, Object *  obj, const char *  key, Object *  value){
	if (self->cbSetField) {
		(*(self->cbSetField))((void * )(self->cbSetField), obj, key, value) ;
		return ; 
	}
	OrcMetaField *  mf = orc_getMetaFieldByObject(obj, key) ;
	if (mf) {
		int  addr = OrcMetaField_getAddress(mf) ;
		int  type = OrcMetaField_getType(mf) ;
		void *  p = ((char * )obj) + addr;
		if (Orc_instanceof((Object*)value, (Vtable_Object*)Vtable_Orc$Number_init(NULL))) {
			Orc$Number *  num = (Orc$Number * )value;
			if (type == OrcMetaType_bool) {
				bool *  pv = (bool * )p;
				*pv = num->toInt(num)  != 0;
			}
			else if (type == OrcMetaType_int) {
				int *  pv = (int * )p;
				*pv = num->toInt(num) ;
			}
			else if (type == OrcMetaType_float) {
				float *  pv = (float * )p;
				*pv = num->toDouble(num) ;
			}
		}
		if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_SuiCore$Node_init(NULL))) {
			SuiCore$Node *  node = (SuiCore$Node * )obj;
			node->invalidReact(node) ;
		}
	}
}


void  SuiDesigner$Inspector$reactObject_withExtendsChain(SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode, Object *  obj, Vtable_Object *  vt){
	if (obj == NULL) {
		return ; 
	}
	int  idx = 0;
	while (vt) {
		self->reactObject_byVtable(self, parentNode, self->obj, vt, idx) ;
		idx++;
		vt = Vtable_getSuper(vt) ;
	}
}


void  SuiDesigner$Inspector$reactObject(SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Inspector, parentNode) , parentNode) ;
	Vtable_Object *  vt = orc_getVtableByObject(self->obj) ;
	self->reactObject_withExtendsChain(self, parentNode, self->obj, vt) ;
}


void  SuiDesigner$Inspector$inspect(SuiDesigner$Inspector *  self, SuiCore$Node *  parentNode, Object *  obj){
	self->reset(self) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Inspector, obj) , obj) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Inspector, parentNode) , parentNode) ;
	self->clearAttrInfoMap(self) ;
	self->callOnInspect(self) ;
	if (self->useDefaultInspect) {
		self->reactObject(self, parentNode) ;
	}
}


void  SuiDesigner$Inspector$callOnInspect(SuiDesigner$Inspector *  self){
	void **  ptr = orc_getFieldPtr(self->obj, "onInspect") ;
	if (ptr != NULL) {
		void  (*onInspect)(Object *  _self, SuiDesigner$Inspector *  insp);
		onInspect = *ptr;
		if (onInspect) {
			onInspect(self->obj, self) ;
		}
	}
}


int  SuiDesigner$Inspector$countFieldsOfVtable(SuiDesigner$Inspector *  self, Vtable_Object *  vt){
	int  cnt = 0;
	OrcMetaField *  mf = orc_getOrInitMeta(vt) ;
	while (mf) {
		const char *  name = OrcMetaField_getName(mf) ;
		if (Orc$String_startsWith(name, "_") ) {
			
		}
		else {
			cnt++;
		}
		mf = OrcMetaField_getNext(mf) ;
	}
	return cnt; 
}


void  SuiDesigner$Inspector$reactObject_byVtable(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  _obj, Vtable_Object *  vt, int  vtIdx){
	URGC_VAR_CLEANUP SuiDesigner$__Block_338_82*  __var___Block_338_82 = (__var___Block_338_82=NULL,urgc_init_var((void**)&__var___Block_338_82, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_338_82) , __finiBlock___Block_338_82) ));
	urgc_set_field_class(__var___Block_338_82, (void * )offsetof(SuiDesigner$__Block_338_82, self) , self) ;
	urgc_set_field_class(__var___Block_338_82, (void * )offsetof(SuiDesigner$__Block_338_82, obj) , _obj) ;
	__var___Block_338_82->vtable = vt;
	__var___Block_338_82->headmf = orc_getOrInitMeta(vt) ;
	URGC_VAR_CLEANUP_CLASS SuiView$Panel*  tmpReturn_1 = NULL;
	{
		SuiView$Panel*  __scopeVar_348_8 = SuiView$mkPanel(&tmpReturn_1, o, ((long long )_obj) + vtIdx) , *o = __scopeVar_348_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_348_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP SuiDesigner$__Closure_349_30*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$Panel, cbRenderTitle) , __make___Closure_349_30(&tmpReturn_2, __var___Block_338_82) ) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_354_32*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$Panel, cbRenderContent) , __make___Closure_354_32(&tmpReturn_3, __var___Block_338_82) ) ;
	}
}


void  SuiDesigner$Inspector$reactObjectField(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf){
	const char *  name = OrcMetaField_getName(mf) ;
	Object *  tmpObj = obj;
	if (Orc$String_startsWith(name, "_") ) {
		return ; 
	}
	self->reactObjectField_do(self, o, obj, vt, mf) ;
}


void  SuiDesigner$Inspector$reactObjectFieldName(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf){
	const char *  name = OrcMetaField_getName(mf) ;
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_381_8 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_381_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_381_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setText(o, Orc$str(&tmpReturn_2, name) ) ;
		((SuiCore$View * )o)->width = 120;
		((SuiCore$View * )o)->margin.right = 10;
	}
}


void  SuiDesigner$Inspector$reactObjectFieldRow(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf, void  (**renderBody)(void *  self, SuiCore$Node *  o)){
	URGC_REF_ARG_WITH_CLEANUP(renderBody);

	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_389_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )mf) , *o = __scopeVar_389_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_389_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		self->reactObjectFieldName(self, o, obj, vt, mf) ;
		(*(renderBody))((void * )(renderBody), o) ;
	}
}


void  SuiDesigner$Inspector$reactObjectField_do(SuiDesigner$Inspector *  self, SuiCore$Node *  o, Object *  obj, Vtable_Object *  vt, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_410_87*  __var___Block_410_87 = (__var___Block_410_87=NULL,urgc_init_var((void**)&__var___Block_410_87, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_410_87) , __finiBlock___Block_410_87) ));
	urgc_set_field_class(__var___Block_410_87, (void * )offsetof(SuiDesigner$__Block_410_87, self) , self) ;
	__var___Block_410_87->obj = obj;
	__var___Block_410_87->mf = mf;
	__var___Block_410_87->tmpObj = __var___Block_410_87->obj;
	__var___Block_410_87->name = OrcMetaField_getName(__var___Block_410_87->mf) ;
	SuiDesigner$InspectorAttrInfo *  info = self->getAttrInfo(self, __var___Block_410_87->name) ;
	if (info) {
		if (info->bSlider) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_419_16 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_419_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_419_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				self->reactObjectFieldName(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf) ;
				URGC_VAR_CLEANUP_CLASS SuiView$Slider*  tmpReturn_2 = NULL;
				{
					SuiView$Slider*  __scopeVar_422_20 = SuiView$mkSlider(&tmpReturn_2, o, 0) , *o = __scopeVar_422_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_422_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->fromValue = info->fromValue;
					o->toValue = info->toValue;
					URGC_VAR_CLEANUP SuiDesigner$__Closure_427_38*  tmpReturn_3 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$Slider, onChanged) , __make___Closure_427_38(&tmpReturn_3, __var___Block_410_87) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) ;
				}
			}
			return ; 
		}
		if (info->bSelect) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_443_16 = SuiLayout$layoutLinear(&tmpReturn_5, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_443_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_443_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				self->reactObjectFieldName(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf) ;
				URGC_VAR_CLEANUP_CLASS SuiView$Select*  tmpReturn_6 = NULL;
				{
					SuiView$Select*  __scopeVar_446_20 = SuiView$mkSelect(&tmpReturn_6, o, 0) , *o = __scopeVar_446_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_446_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_7 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$Select, options) , info->getOptionLabels(&tmpReturn_7, info) ) ;
					URGC_VAR_CLEANUP SuiDesigner$__Closure_448_38*  tmpReturn_8 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$Select, onChanged) , __make___Closure_448_38(&tmpReturn_8, __var___Block_410_87) ) ;
				}
			}
			return ; 
		}
		if (info->bImageSrc) {
			if (0) {
				return ; 
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_462_16 = SuiLayout$layoutLinear(&tmpReturn_9, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_462_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_462_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				self->reactObjectFieldName(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_10 = NULL;
				{
					SuiLayout$LayoutLinear*  __scopeVar_465_20 = SuiLayout$layoutLinear(&tmpReturn_10, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_465_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_465_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					Orc$String$set(o->direction, "column") ;
					Orc$String$set(o->alignItems, "start") ;
					Orc$String *  src = *((Orc$String ** )OrcMetaField_getPtr(__var___Block_410_87->mf, __var___Block_410_87->obj) );
					URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_11 = NULL;
					{
						SuiView$ImageView*  __scopeVar_470_24 = SuiView$mkImageView(&tmpReturn_11, o, 0) , *o = __scopeVar_470_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_470_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						((SuiCore$View * )o)->width = 100;
						((SuiCore$View * )o)->height = 100;
						o->setImageMode(o, SuiView$WrapContent) ;
						((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff999999) ;
						o->setSrc(o, src) ;
						Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_477_42*  tmpReturn_12 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_477_42(&tmpReturn_12, __var___Block_410_87) ) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_13 = NULL;
					{
						SuiView$TextView*  __scopeVar_494_24 = SuiView$mkTextView(&tmpReturn_13, o, 0) , *o = __scopeVar_494_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_494_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->setText(o, src) ;
					}
				}
			}
			return ; 
		}
		if (info->bFileSrc) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_14 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_505_16 = SuiLayout$layoutLinear(&tmpReturn_14, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_505_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_505_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				self->reactObjectFieldName(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_15 = NULL;
				{
					SuiLayout$LayoutLinear*  __scopeVar_508_20 = SuiLayout$layoutLinear(&tmpReturn_15, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_508_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_508_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					Orc$String$set(o->direction, "column") ;
					Orc$String$set(o->alignItems, "start") ;
					Orc$String *  src = *((Orc$String ** )OrcMetaField_getPtr(__var___Block_410_87->mf, __var___Block_410_87->obj) );
					URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_16 = NULL;
					{
						SuiView$DrawButton*  __scopeVar_513_24 = SuiView$mkDrawButton(&tmpReturn_16, o, 0) , *o = __scopeVar_513_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_513_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						if (src && Orc$String$notEmpty(src) ) {
							urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , src) ;
						}
						else {
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_17, "null") ) ;
						}
						URGC_VAR_CLEANUP SuiDesigner$__Closure_520_40*  tmpReturn_18 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_520_40(&tmpReturn_18, __var___Block_410_87) ) ;
					}
				}
			}
			return ; 
		}
		if (info->bColor) {
			URGC_VAR_CLEANUP SuiDesigner$__Closure_565_58*  tmpReturn_19 = NULL;
			self->reactObjectFieldRow(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf, __make___Closure_565_58(&tmpReturn_19, __var___Block_410_87) ) ;
			return ; 
		}
	}
	if (OrcMetaField_isStringRef(__var___Block_410_87->mf) ) {
		URGC_VAR_CLEANUP SuiDesigner$__Closure_609_54*  tmpReturn_20 = NULL;
		self->reactObjectFieldRow(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf, __make___Closure_609_54(&tmpReturn_20, __var___Block_410_87) ) ;
	}
	else if (OrcMetaField_isPrimitive(__var___Block_410_87->mf) ) {
		URGC_VAR_CLEANUP SuiDesigner$__Closure_639_54*  tmpReturn_21 = NULL;
		self->reactObjectFieldRow(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf, __make___Closure_639_54(&tmpReturn_21, __var___Block_410_87) ) ;
	}
	if (__var___Block_410_87->mf->metaStruct == metaStructOf(SuiCore$Vec2) ) {
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_22 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_702_12 = SuiLayout$layoutLinear(&tmpReturn_22, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_702_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_702_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP SuiDesigner$__Block_702_43*  __var___Block_702_43 = (__var___Block_702_43=NULL,urgc_init_var((void**)&__var___Block_702_43, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_702_43) , __finiBlock___Block_702_43) ));
			self->reactObjectFieldName(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf) ;
			__var___Block_702_43->v = *((SuiCore$Vec2 * )OrcMetaField_getPtr(__var___Block_410_87->mf, __var___Block_410_87->obj) );
			URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_23 = NULL;
			{
				SuiView$EditText*  __scopeVar_707_16 = SuiView$mkEditText(&tmpReturn_23, o, 0) , *o = __scopeVar_707_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_707_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->padding.left = 4;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
				o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_24, "") , __var___Block_702_43->v.x) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_710_39*  tmpReturn_25 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_710_39(&tmpReturn_25, __var___Block_702_43, __var___Block_410_87) ) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_26 = NULL;
				{
					SuiLayout$LayoutLinearCell*  __scopeVar_718_20 = SuiLayout$layoutLinearCell(&tmpReturn_26, o, 0) , *o = __scopeVar_718_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_718_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->grow = 1;
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_27 = NULL;
			{
				SuiView$EditText*  __scopeVar_720_16 = SuiView$mkEditText(&tmpReturn_27, o, 0) , *o = __scopeVar_720_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_720_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->padding.left = 4;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
				o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_28, "") , __var___Block_702_43->v.y) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_723_39*  tmpReturn_29 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_723_39(&tmpReturn_29, __var___Block_702_43, __var___Block_410_87) ) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_30 = NULL;
				{
					SuiLayout$LayoutLinearCell*  __scopeVar_732_20 = SuiLayout$layoutLinearCell(&tmpReturn_30, o, 0) , *o = __scopeVar_732_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_732_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->grow = 1;
				}
			}
		}
		return ; 
	}
	if (__var___Block_410_87->mf->metaStruct == metaStructOf(SuiCore$Bezier) ) {
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_31 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_740_12 = SuiLayout$layoutLinear(&tmpReturn_31, o, (long long )__var___Block_410_87->mf) , *o = __scopeVar_740_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_740_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			self->reactObjectFieldName(self, o, __var___Block_410_87->obj, vt, __var___Block_410_87->mf) ;
			SuiCore$Bezier v = *((SuiCore$Bezier * )OrcMetaField_getPtr(__var___Block_410_87->mf, __var___Block_410_87->obj) );
			URGC_VAR_CLEANUP_CLASS SuiDesigner$BezierEditView*  tmpReturn_32 = NULL;
			{
				SuiDesigner$BezierEditView*  __scopeVar_746_16 = SuiDesigner$mkBezierEditView(&tmpReturn_32, o, 0) , *o = __scopeVar_746_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_746_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				if (!o->drag->isDragging) {
					o->start = v.start;
					o->c0 = v.c0;
					o->c1 = v.c1;
					o->end = v.end;
				}
				SuiCore$Inset$setHor(&((SuiCore$View * )o)->margin, 10) ;
				SuiCore$Inset$setVer(&((SuiCore$View * )o)->margin, 10) ;
				((SuiCore$View * )o)->height = 60;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_756_34*  tmpReturn_33 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiDesigner$BezierEditView, onChanged) , __make___Closure_756_34(&tmpReturn_33, __var___Block_410_87) ) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_34 = NULL;
				{
					SuiLayout$LayoutLinearCell*  __scopeVar_783_20 = SuiLayout$layoutLinearCell(&tmpReturn_34, o, 0) , *o = __scopeVar_783_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_783_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->grow = 1;
				}
			}
		}
		return ; 
	}
}



static void  __finiBlock___Block_338_82(SuiDesigner$__Block_338_82 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_338_82, self) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_338_82, obj) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_410_87(SuiDesigner$__Block_410_87 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_410_87, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_702_43(SuiDesigner$__Block_702_43 *  self){
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_349_30(SuiDesigner$__Closure_349_30 *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_350_16 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_350_16;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_350_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setText(o, Orc$str(&tmpReturn_2, Vtable_getClassName(self->__var___Block_338_82->vtable) ) ) ;
	}
}

static void  __fini___Closure_349_30(SuiDesigner$__Closure_349_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_349_30, __var___Block_338_82) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_349_30*  __make___Closure_349_30(SuiDesigner$__Closure_349_30 **  __outRef__, SuiDesigner$__Block_338_82 *  __var___Block_338_82){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_349_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_349_30) , __fini___Closure_349_30) ));
	self->invoke = __fn___Closure_349_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_349_30, __var___Block_338_82) , __var___Block_338_82) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_354_32(SuiDesigner$__Closure_354_32 *  self, SuiCore$Node *  parent){
	OrcMetaField *  mf = self->__var___Block_338_82->headmf;
	while (mf) {
		self->__var___Block_338_82->self->reactObjectField(self->__var___Block_338_82->self, parent, self->__var___Block_338_82->obj, self->__var___Block_338_82->vtable, mf) ;
		mf = OrcMetaField_getNext(mf) ;
	}
}

static void  __fini___Closure_354_32(SuiDesigner$__Closure_354_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_354_32, __var___Block_338_82) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_354_32*  __make___Closure_354_32(SuiDesigner$__Closure_354_32 **  __outRef__, SuiDesigner$__Block_338_82 *  __var___Block_338_82){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_354_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_354_32) , __fini___Closure_354_32) ));
	self->invoke = __fn___Closure_354_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_354_32, __var___Block_338_82) , __var___Block_338_82) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_427_38(SuiDesigner$__Closure_427_38 *  self, int  i, Orc$String*  label){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(label);

	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	setAttr(self->__var___Block_410_87->name, Json$Json_mkString(&tmpReturn_1, label) ) ;
}

static void  __fini___Closure_427_38(SuiDesigner$__Closure_427_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_427_38, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_427_38*  __make___Closure_427_38(SuiDesigner$__Closure_427_38 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_427_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_427_38) , __fini___Closure_427_38) ));
	self->invoke = __fn___Closure_427_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_427_38, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_448_38(SuiDesigner$__Closure_448_38 *  self, int  i, Orc$String*  label){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(label);

	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	setAttr(self->__var___Block_410_87->name, Json$Json_mkString(&tmpReturn_1, label) ) ;
}

static void  __fini___Closure_448_38(SuiDesigner$__Closure_448_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_448_38, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_448_38*  __make___Closure_448_38(SuiDesigner$__Closure_448_38 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_448_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_448_38) , __fini___Closure_448_38) ));
	self->invoke = __fn___Closure_448_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_448_38, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_477_42(SuiDesigner$__Closure_477_42 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$FileChooser*  fc = (fc=NULL,urgc_init_var_class((void**)&fc, SuiDesigner$FileChooser_new(&fc) ));
			fc->use_filterImage(fc) ;
			fc->loadPaths(fc) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_485_54*  tmpReturn_1 = NULL;
			urgc_set_field(fc, (void * )offsetof(SuiDesigner$FileChooser, onChoose) , __make___Closure_485_54(&tmpReturn_1, self->__var___Block_410_87) ) ;
			fc->showWindow(fc) ;
		}
	}
}

static void  __fini___Closure_477_42(SuiDesigner$__Closure_477_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_477_42, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_477_42*  __make___Closure_477_42(SuiDesigner$__Closure_477_42 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_477_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_477_42) , __fini___Closure_477_42) ));
	self->invoke = __fn___Closure_477_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_477_42, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_485_54(SuiDesigner$__Closure_485_54 *  self, Orc$String*  newpath){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newpath);

	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	setAttr(self->__var___Block_410_87->name, Json$Json_mkString(&tmpReturn_1, newpath) ) ;
}

static void  __fini___Closure_485_54(SuiDesigner$__Closure_485_54 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_485_54, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_485_54*  __make___Closure_485_54(SuiDesigner$__Closure_485_54 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_485_54*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_485_54) , __fini___Closure_485_54) ));
	self->invoke = __fn___Closure_485_54;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_485_54, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_520_40(SuiDesigner$__Closure_520_40 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileChooser*  fc = (fc=NULL,urgc_init_var_class((void**)&fc, SuiDesigner$FileChooser_new(&fc) ));
	Orc$String$set(fc->dir, "./asset") ;
	fc->loadPaths(fc) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_526_46*  tmpReturn_1 = NULL;
	urgc_set_field(fc, (void * )offsetof(SuiDesigner$FileChooser, onChoose) , __make___Closure_526_46(&tmpReturn_1, self->__var___Block_410_87) ) ;
	fc->showWindow(fc) ;
}

static void  __fini___Closure_520_40(SuiDesigner$__Closure_520_40 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_520_40, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_520_40*  __make___Closure_520_40(SuiDesigner$__Closure_520_40 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_520_40*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_520_40) , __fini___Closure_520_40) ));
	self->invoke = __fn___Closure_520_40;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_520_40, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_526_46(SuiDesigner$__Closure_526_46 *  self, Orc$String*  newpath){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newpath);

	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	setAttr(self->__var___Block_410_87->name, Json$Json_mkString(&tmpReturn_1, newpath) ) ;
}

static void  __fini___Closure_526_46(SuiDesigner$__Closure_526_46 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_526_46, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_526_46*  __make___Closure_526_46(SuiDesigner$__Closure_526_46 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_526_46*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_526_46) , __fini___Closure_526_46) ));
	self->invoke = __fn___Closure_526_46;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_526_46, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_565_58(SuiDesigner$__Closure_565_58 *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_1 = NULL;
	{
		SuiView$ColorPicker*  __scopeVar_573_20 = SuiView$mkColorPicker(&tmpReturn_1, o, 0) , *o = __scopeVar_573_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_573_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		int *  pColor = OrcMetaField_getIntPtr(self->__var___Block_410_87->mf, self->__var___Block_410_87->obj) ;
		((SuiCore$View * )o)->backgroundColor = *pColor;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_577_38*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_577_38(&tmpReturn_2, self->__var___Block_410_87) ) ;
	}
}

static void  __fini___Closure_565_58(SuiDesigner$__Closure_565_58 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_565_58, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_565_58*  __make___Closure_565_58(SuiDesigner$__Closure_565_58 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_565_58*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_565_58) , __fini___Closure_565_58) ));
	self->invoke = __fn___Closure_565_58;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_565_58, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_577_38(SuiDesigner$__Closure_577_38 *  self, int  newcolor){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
	SuiDesigner$ANode *  sel = (SuiDesigner$ANode * )ctx->state->getFirstSelected(ctx->state) ;
	if (sel) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		sel->setAttr(sel, self->__var___Block_410_87->name, Json$Json_mkNumber(&tmpReturn_1, newcolor) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeAttrChanged*  tmpNewOwner_2 = NULL;
		{
			SuiDesigner$EventANodeAttrChanged*  o = SuiDesigner$EventANodeAttrChanged_new(&tmpNewOwner_2) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeAttrChanged, anode) , sel) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}

static void  __fini___Closure_577_38(SuiDesigner$__Closure_577_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_577_38, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_577_38*  __make___Closure_577_38(SuiDesigner$__Closure_577_38 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_577_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_577_38) , __fini___Closure_577_38) ));
	self->invoke = __fn___Closure_577_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_577_38, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_609_54(SuiDesigner$__Closure_609_54 *  self, SuiCore$Node *  o){
	int  addr = OrcMetaField_getAddress(self->__var___Block_410_87->mf) ;
	void *  p = ((char * )self->__var___Block_410_87->obj) + addr;
	Orc$String *  s = *(Orc$String ** )p;
	URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_1 = NULL;
	{
		SuiView$EditText*  __scopeVar_615_16 = SuiView$mkEditText(&tmpReturn_1, o, 0) , *o = __scopeVar_615_16;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_615_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->padding.left = 4;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setValue(o, s == NULL ? Orc$str(&tmpReturn_2, "")  : s) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_618_39*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_618_39(&tmpReturn_3, self->__var___Block_410_87) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_634_20 = SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) , *o = __scopeVar_634_20;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_634_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
}

static void  __fini___Closure_609_54(SuiDesigner$__Closure_609_54 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_609_54, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_609_54*  __make___Closure_609_54(SuiDesigner$__Closure_609_54 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_609_54*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_609_54) , __fini___Closure_609_54) ));
	self->invoke = __fn___Closure_609_54;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_609_54, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_618_39(SuiDesigner$__Closure_618_39 *  self, SuiView$EditText *  et){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
	SuiDesigner$ANode *  sel = (SuiDesigner$ANode * )ctx->state->getFirstSelected(ctx->state) ;
	if (sel) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		sel->setAttr(sel, self->__var___Block_410_87->name, Json$Json_mkString(&tmpReturn_1, et->value) ) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeAttrChanged*  tmpNewOwner_2 = NULL;
		{
			SuiDesigner$EventANodeAttrChanged*  o = SuiDesigner$EventANodeAttrChanged_new(&tmpNewOwner_2) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeAttrChanged, anode) , sel) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}

static void  __fini___Closure_618_39(SuiDesigner$__Closure_618_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_618_39, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_618_39*  __make___Closure_618_39(SuiDesigner$__Closure_618_39 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_618_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_618_39) , __fini___Closure_618_39) ));
	self->invoke = __fn___Closure_618_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_618_39, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_639_54(SuiDesigner$__Closure_639_54 *  self, SuiCore$Node *  o){
	int  type = OrcMetaField_getType(self->__var___Block_410_87->mf) ;
	int  addr = OrcMetaField_getAddress(self->__var___Block_410_87->mf) ;
	void *  p = ((char * )self->__var___Block_410_87->obj) + addr;
	if (type == OrcMetaType_bool) {
		bool *  pv = (bool * )p;
		URGC_VAR_CLEANUP_CLASS SuiView$Switch*  tmpReturn_1 = NULL;
		{
			SuiView$Switch*  __scopeVar_645_20 = SuiView$mkSwitch(&tmpReturn_1, o, 0) , *o = __scopeVar_645_20;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_645_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->setChecked(o, *pv) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_647_45*  tmpReturn_2 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$Switch, onCheckedChanged) , __make___Closure_647_45(&tmpReturn_2, self->__var___Block_410_87) ) ;
		}
	}
	else if (type == OrcMetaType_int) {
		int *  pv = (int * )p;
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_3 = NULL;
		{
			SuiView$EditText*  __scopeVar_655_20 = SuiView$mkEditText(&tmpReturn_3, o, 0) , *o = __scopeVar_655_20;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_655_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  val = Orc$str((val = NULL,&val), "") ;
			Orc$String$addi(val, *pv) ;
			o->setValue(o, val) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_660_43*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_660_43(&tmpReturn_4, self->__var___Block_410_87) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_668_24 = SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) , *o = __scopeVar_668_24;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_668_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
	}
	else if (type == OrcMetaType_float) {
		float *  pv = (float * )p;
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_673_20 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_673_20;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_673_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  val = Orc$str((val = NULL,&val), "") ;
			Orc$String$addf(val, *pv) ;
			((SuiCore$View * )o)->padding.left = 4;
			o->setValue(o, val) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_680_43*  tmpReturn_7 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_680_43(&tmpReturn_7, self->__var___Block_410_87) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_8 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_688_24 = SuiLayout$layoutLinearCell(&tmpReturn_8, o, 0) , *o = __scopeVar_688_24;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_688_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
	}
	else {
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_9 = NULL;
		{
			SuiView$EditText*  __scopeVar_692_20 = SuiView$mkEditText(&tmpReturn_9, o, 0) , *o = __scopeVar_692_20;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_692_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_10 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_694_24 = SuiLayout$layoutLinearCell(&tmpReturn_10, o, 0) , *o = __scopeVar_694_24;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_694_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
	}
}

static void  __fini___Closure_639_54(SuiDesigner$__Closure_639_54 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_639_54, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_639_54*  __make___Closure_639_54(SuiDesigner$__Closure_639_54 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_639_54*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_639_54) , __fini___Closure_639_54) ));
	self->invoke = __fn___Closure_639_54;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_639_54, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_647_45(SuiDesigner$__Closure_647_45 *  self, SuiView$Switch *  v){
	URGC_VAR_CLEANUP_CLASS Orc$Boolean*  tmpReturn_1 = NULL;
	self->__var___Block_410_87->self->setField(self->__var___Block_410_87->self, self->__var___Block_410_87->tmpObj, self->__var___Block_410_87->name, Orc$mkBoolean(&tmpReturn_1, v->checked) ) ;
}

static void  __fini___Closure_647_45(SuiDesigner$__Closure_647_45 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_647_45, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_647_45*  __make___Closure_647_45(SuiDesigner$__Closure_647_45 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_647_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_647_45) , __fini___Closure_647_45) ));
	self->invoke = __fn___Closure_647_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_647_45, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_660_43(SuiDesigner$__Closure_660_43 *  self, SuiView$EditText *  et){
	printf("onValueChanged:%s\n", et->value->str) ;
	double  nv = atoi(et->value->str) ;
	printf("\t  int value:%f\n", nv) ;
	URGC_VAR_CLEANUP_CLASS Orc$Integer*  tmpReturn_1 = NULL;
	self->__var___Block_410_87->self->setField(self->__var___Block_410_87->self, self->__var___Block_410_87->tmpObj, self->__var___Block_410_87->name, Orc$mkInteger(&tmpReturn_1, nv) ) ;
}

static void  __fini___Closure_660_43(SuiDesigner$__Closure_660_43 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_660_43, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_660_43*  __make___Closure_660_43(SuiDesigner$__Closure_660_43 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_660_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_660_43) , __fini___Closure_660_43) ));
	self->invoke = __fn___Closure_660_43;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_660_43, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_680_43(SuiDesigner$__Closure_680_43 *  self, SuiView$EditText *  et){
	printf("onValueChanged:%s\n", et->value->str) ;
	double  nv = atof(et->value->str) ;
	printf("\t  double value:%f\n", nv) ;
	URGC_VAR_CLEANUP_CLASS Orc$Double*  tmpReturn_1 = NULL;
	self->__var___Block_410_87->self->setField(self->__var___Block_410_87->self, self->__var___Block_410_87->tmpObj, self->__var___Block_410_87->name, Orc$mkDouble(&tmpReturn_1, nv) ) ;
}

static void  __fini___Closure_680_43(SuiDesigner$__Closure_680_43 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_680_43, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_680_43*  __make___Closure_680_43(SuiDesigner$__Closure_680_43 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_680_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_680_43) , __fini___Closure_680_43) ));
	self->invoke = __fn___Closure_680_43;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_680_43, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_710_39(SuiDesigner$__Closure_710_39 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_702_43->v.x, nv) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->putNumber(jo, "x", nv) ;
	jo->putNumber(jo, "y", self->__var___Block_702_43->v.y) ;
	setAttr(self->__var___Block_410_87->name, jo) ;
}

static void  __fini___Closure_710_39(SuiDesigner$__Closure_710_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_710_39, __var___Block_702_43) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_710_39, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_710_39*  __make___Closure_710_39(SuiDesigner$__Closure_710_39 **  __outRef__, SuiDesigner$__Block_702_43 *  __var___Block_702_43, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_710_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_710_39) , __fini___Closure_710_39) ));
	self->invoke = __fn___Closure_710_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_710_39, __var___Block_702_43) , __var___Block_702_43) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_710_39, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_723_39(SuiDesigner$__Closure_723_39 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set y:%f=>%f\n", self->__var___Block_702_43->v.y, nv) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->putNumber(jo, "x", self->__var___Block_702_43->v.x) ;
	jo->putNumber(jo, "y", nv) ;
	setAttr(self->__var___Block_410_87->name, jo) ;
}

static void  __fini___Closure_723_39(SuiDesigner$__Closure_723_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_723_39, __var___Block_702_43) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_723_39, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_723_39*  __make___Closure_723_39(SuiDesigner$__Closure_723_39 **  __outRef__, SuiDesigner$__Block_702_43 *  __var___Block_702_43, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_723_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_723_39) , __fini___Closure_723_39) ));
	self->invoke = __fn___Closure_723_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_723_39, __var___Block_702_43) , __var___Block_702_43) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_723_39, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_756_34(SuiDesigner$__Closure_756_34 *  self, SuiDesigner$BezierEditView *  view){
	URGC_VAR_CLEANUP_CLASS Json$Json*  start = Json$Json_mkObject((start = NULL,&start)) ;
	start->putNumber(start, "x", view->start.x) ;
	start->putNumber(start, "y", view->start.y) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  c0 = Json$Json_mkObject((c0 = NULL,&c0)) ;
	c0->putNumber(c0, "x", view->c0.x) ;
	c0->putNumber(c0, "y", view->c0.y) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  c1 = Json$Json_mkObject((c1 = NULL,&c1)) ;
	c1->putNumber(c1, "x", view->c1.x) ;
	c1->putNumber(c1, "y", view->c1.y) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  end = Json$Json_mkObject((end = NULL,&end)) ;
	end->putNumber(end, "x", view->end.x) ;
	end->putNumber(end, "y", view->end.y) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_mkObject((jo = NULL,&jo)) ;
	jo->put(jo, "start", start) ;
	jo->put(jo, "c0", c0) ;
	jo->put(jo, "c1", c1) ;
	jo->put(jo, "end", end) ;
	setAttr(self->__var___Block_410_87->name, jo) ;
}

static void  __fini___Closure_756_34(SuiDesigner$__Closure_756_34 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_756_34, __var___Block_410_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_756_34*  __make___Closure_756_34(SuiDesigner$__Closure_756_34 **  __outRef__, SuiDesigner$__Block_410_87 *  __var___Block_410_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_756_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_756_34) , __fini___Closure_756_34) ));
	self->invoke = __fn___Closure_756_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_756_34, __var___Block_410_87) , __var___Block_410_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  setAttr(const char *  name, Json$Json*  jv){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(jv);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
	SuiDesigner$ANode *  sel = (SuiDesigner$ANode * )ctx->state->getFirstSelected(ctx->state) ;
	if (sel) {
		sel->setAttr(sel, name, jv) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeAttrChanged*  tmpNewOwner_1 = NULL;
		{
			SuiDesigner$EventANodeAttrChanged*  o = SuiDesigner$EventANodeAttrChanged_new(&tmpNewOwner_1) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeAttrChanged, anode) , sel) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}



