
#include "Insp_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include <string.h>
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
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
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


// static struct 
typedef struct tagSuiDesigner$__Block_258_69 SuiDesigner$__Block_258_69;

typedef struct tagSuiDesigner$__Block_270_69 SuiDesigner$__Block_270_69;

typedef struct tagSuiDesigner$__Block_307_69 SuiDesigner$__Block_307_69;

typedef struct tagSuiDesigner$__Block_339_69 SuiDesigner$__Block_339_69;

typedef struct tagSuiDesigner$__Block_563_49 SuiDesigner$__Block_563_49;

typedef struct tagSuiDesigner$__Block_681_58 SuiDesigner$__Block_681_58;

typedef struct tagSuiDesigner$__Block_696_55 SuiDesigner$__Block_696_55;

typedef struct tagSuiDesigner$__Block_724_57 SuiDesigner$__Block_724_57;

typedef struct tagSuiDesigner$__Block_749_56 SuiDesigner$__Block_749_56;

typedef struct tagSuiDesigner$__Block_771_39 SuiDesigner$__Block_771_39;

typedef struct tagSuiDesigner$__Block_768_56 SuiDesigner$__Block_768_56;

typedef struct tagSuiDesigner$__Block_816_39 SuiDesigner$__Block_816_39;

typedef struct tagSuiDesigner$__Block_813_56 SuiDesigner$__Block_813_56;

typedef struct tagSuiDesigner$__Block_879_39 SuiDesigner$__Block_879_39;

typedef struct tagSuiDesigner$__Block_876_56 SuiDesigner$__Block_876_56;

typedef struct tagSuiDesigner$__Block_955_60 SuiDesigner$__Block_955_60;

typedef struct tagSuiDesigner$__Block_975_57 SuiDesigner$__Block_975_57;

typedef struct tagSuiDesigner$__Block_989_56 SuiDesigner$__Block_989_56;

typedef struct tagSuiDesigner$__Block_1003_58 SuiDesigner$__Block_1003_58;

typedef struct tagSuiDesigner$__Block_1219_68 SuiDesigner$__Block_1219_68;

typedef struct tagSuiDesigner$__Block_1262_68 SuiDesigner$__Block_1262_68;

typedef struct tagSuiDesigner$__Block_1320_68 SuiDesigner$__Block_1320_68;

typedef struct tagSuiDesigner$__Block_1405_31 SuiDesigner$__Block_1405_31;

typedef struct tagSuiDesigner$__Closure_263_26 SuiDesigner$__Closure_263_26;

typedef struct tagSuiDesigner$__Closure_283_30 SuiDesigner$__Closure_283_30;

typedef struct tagSuiDesigner$__Closure_291_42 SuiDesigner$__Closure_291_42;

typedef struct tagSuiDesigner$__Closure_320_28 SuiDesigner$__Closure_320_28;

typedef struct tagSuiDesigner$__Closure_326_34 SuiDesigner$__Closure_326_34;

typedef struct tagSuiDesigner$__Closure_342_26 SuiDesigner$__Closure_342_26;

typedef struct tagSuiDesigner$__Closure_579_32 SuiDesigner$__Closure_579_32;

typedef struct tagSuiDesigner$__Closure_688_31 SuiDesigner$__Closure_688_31;

typedef struct tagSuiDesigner$__Closure_711_31 SuiDesigner$__Closure_711_31;

typedef struct tagSuiDesigner$__Closure_737_31 SuiDesigner$__Closure_737_31;

typedef struct tagSuiDesigner$__Closure_758_37 SuiDesigner$__Closure_758_37;

typedef struct tagSuiDesigner$__Closure_781_35 SuiDesigner$__Closure_781_35;

typedef struct tagSuiDesigner$__Closure_798_35 SuiDesigner$__Closure_798_35;

typedef struct tagSuiDesigner$__Closure_826_35 SuiDesigner$__Closure_826_35;

typedef struct tagSuiDesigner$__Closure_844_35 SuiDesigner$__Closure_844_35;

typedef struct tagSuiDesigner$__Closure_862_35 SuiDesigner$__Closure_862_35;

typedef struct tagSuiDesigner$__Closure_889_35 SuiDesigner$__Closure_889_35;

typedef struct tagSuiDesigner$__Closure_906_35 SuiDesigner$__Closure_906_35;

typedef struct tagSuiDesigner$__Closure_924_35 SuiDesigner$__Closure_924_35;

typedef struct tagSuiDesigner$__Closure_940_35 SuiDesigner$__Closure_940_35;

typedef struct tagSuiDesigner$__Closure_969_26 SuiDesigner$__Closure_969_26;

typedef struct tagSuiDesigner$__Closure_982_26 SuiDesigner$__Closure_982_26;

typedef struct tagSuiDesigner$__Closure_996_26 SuiDesigner$__Closure_996_26;

typedef struct tagSuiDesigner$__Closure_1013_26 SuiDesigner$__Closure_1013_26;

typedef struct tagSuiDesigner$__Closure_1171_26 SuiDesigner$__Closure_1171_26;

typedef struct tagSuiDesigner$__Closure_1176_25 SuiDesigner$__Closure_1176_25;

typedef struct tagSuiDesigner$__Closure_1184_32 SuiDesigner$__Closure_1184_32;

typedef struct tagSuiDesigner$__Closure_1230_31 SuiDesigner$__Closure_1230_31;

typedef struct tagSuiDesigner$__Closure_1248_31 SuiDesigner$__Closure_1248_31;

typedef struct tagSuiDesigner$__Closure_1273_31 SuiDesigner$__Closure_1273_31;

typedef struct tagSuiDesigner$__Closure_1291_31 SuiDesigner$__Closure_1291_31;

typedef struct tagSuiDesigner$__Closure_1308_31 SuiDesigner$__Closure_1308_31;

typedef struct tagSuiDesigner$__Closure_1331_31 SuiDesigner$__Closure_1331_31;

typedef struct tagSuiDesigner$__Closure_1349_31 SuiDesigner$__Closure_1349_31;

typedef struct tagSuiDesigner$__Closure_1366_31 SuiDesigner$__Closure_1366_31;

typedef struct tagSuiDesigner$__Closure_1381_31 SuiDesigner$__Closure_1381_31;

typedef struct tagSuiDesigner$__Closure_1423_38 SuiDesigner$__Closure_1423_38;



struct tagSuiDesigner$__Block_258_69 {
	SuiDesigner$Insp *  insp ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_270_69 {
	SuiDesigner$Insp *  insp ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_307_69 {
	SuiDesigner$Insp *  insp ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_339_69 {
	SuiDesigner$InspAttrSelect*  self ;
	SuiDesigner$Insp *  insp ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_563_49 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_681_58 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_696_55 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_724_57 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_749_56 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_771_39 {
	SuiCore$Vec2 v ;
};





struct tagSuiDesigner$__Block_768_56 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_816_39 {
	SuiCore$Vec3 v ;
};





struct tagSuiDesigner$__Block_813_56 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_879_39 {
	SuiCore$Vec4 v ;
};





struct tagSuiDesigner$__Block_876_56 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_955_60 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_975_57 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_989_56 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_1003_58 {
	SuiDesigner$Insp*  self ;
	OrcMetaField *  mf ;
};





struct tagSuiDesigner$__Block_1219_68 {
	SuiCore$Vec2 v ;
	void  (**set)(void *  self, SuiCore$Vec2 nv);
};





struct tagSuiDesigner$__Block_1262_68 {
	SuiCore$Vec3 v ;
	void  (**set)(void *  self, SuiCore$Vec3 nv);
};





struct tagSuiDesigner$__Block_1320_68 {
	SuiCore$Vec4 v ;
	void  (**set)(void *  self, SuiCore$Vec4 nv);
};





struct tagSuiDesigner$__Block_1405_31 {
	SuiDesigner$TestObj*  obj ;
};





struct tagSuiDesigner$__Closure_263_26 {
	void  (*invoke)(SuiDesigner$__Closure_263_26 *  self, int  newcolor);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_258_69*  __var___Block_258_69 ;
};





struct tagSuiDesigner$__Closure_283_30 {
	void  (*invoke)(SuiDesigner$__Closure_283_30 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_270_69*  __var___Block_270_69 ;
};





struct tagSuiDesigner$__Closure_291_42 {
	void  (*invoke)(SuiDesigner$__Closure_291_42 *  self, Orc$String*  newpath);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_270_69*  __var___Block_270_69 ;
};





struct tagSuiDesigner$__Closure_320_28 {
	void  (*invoke)(SuiDesigner$__Closure_320_28 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_307_69*  __var___Block_307_69 ;
};





struct tagSuiDesigner$__Closure_326_34 {
	void  (*invoke)(SuiDesigner$__Closure_326_34 *  self, Orc$String*  newpath);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_307_69*  __var___Block_307_69 ;
};





struct tagSuiDesigner$__Closure_342_26 {
	void  (*invoke)(SuiDesigner$__Closure_342_26 *  self, int  i, Orc$String*  label);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_339_69*  __var___Block_339_69 ;
};





struct tagSuiDesigner$__Closure_579_32 {
	void  (*invoke)(SuiDesigner$__Closure_579_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_563_49*  __var___Block_563_49 ;
};





struct tagSuiDesigner$__Closure_688_31 {
	void  (*invoke)(SuiDesigner$__Closure_688_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_681_58*  __var___Block_681_58 ;
};





struct tagSuiDesigner$__Closure_711_31 {
	void  (*invoke)(SuiDesigner$__Closure_711_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_696_55*  __var___Block_696_55 ;
};





struct tagSuiDesigner$__Closure_737_31 {
	void  (*invoke)(SuiDesigner$__Closure_737_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_724_57*  __var___Block_724_57 ;
};





struct tagSuiDesigner$__Closure_758_37 {
	void  (*invoke)(SuiDesigner$__Closure_758_37 *  self, SuiView$Switch *  v);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_749_56*  __var___Block_749_56 ;
};





struct tagSuiDesigner$__Closure_781_35 {
	void  (*invoke)(SuiDesigner$__Closure_781_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_771_39*  __var___Block_771_39 ;
	SuiDesigner$__Block_768_56*  __var___Block_768_56 ;
};





struct tagSuiDesigner$__Closure_798_35 {
	void  (*invoke)(SuiDesigner$__Closure_798_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_771_39*  __var___Block_771_39 ;
	SuiDesigner$__Block_768_56*  __var___Block_768_56 ;
};





struct tagSuiDesigner$__Closure_826_35 {
	void  (*invoke)(SuiDesigner$__Closure_826_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_816_39*  __var___Block_816_39 ;
	SuiDesigner$__Block_813_56*  __var___Block_813_56 ;
};





struct tagSuiDesigner$__Closure_844_35 {
	void  (*invoke)(SuiDesigner$__Closure_844_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_816_39*  __var___Block_816_39 ;
	SuiDesigner$__Block_813_56*  __var___Block_813_56 ;
};





struct tagSuiDesigner$__Closure_862_35 {
	void  (*invoke)(SuiDesigner$__Closure_862_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_816_39*  __var___Block_816_39 ;
	SuiDesigner$__Block_813_56*  __var___Block_813_56 ;
};





struct tagSuiDesigner$__Closure_889_35 {
	void  (*invoke)(SuiDesigner$__Closure_889_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_879_39*  __var___Block_879_39 ;
	SuiDesigner$__Block_876_56*  __var___Block_876_56 ;
};





struct tagSuiDesigner$__Closure_906_35 {
	void  (*invoke)(SuiDesigner$__Closure_906_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_879_39*  __var___Block_879_39 ;
	SuiDesigner$__Block_876_56*  __var___Block_876_56 ;
};





struct tagSuiDesigner$__Closure_924_35 {
	void  (*invoke)(SuiDesigner$__Closure_924_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_879_39*  __var___Block_879_39 ;
	SuiDesigner$__Block_876_56*  __var___Block_876_56 ;
};





struct tagSuiDesigner$__Closure_940_35 {
	void  (*invoke)(SuiDesigner$__Closure_940_35 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_879_39*  __var___Block_879_39 ;
	SuiDesigner$__Block_876_56*  __var___Block_876_56 ;
};





struct tagSuiDesigner$__Closure_969_26 {
	void  (*invoke)(SuiDesigner$__Closure_969_26 *  self, int  newcolor);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_955_60*  __var___Block_955_60 ;
};





struct tagSuiDesigner$__Closure_982_26 {
	void  (*invoke)(SuiDesigner$__Closure_982_26 *  self, int  newcolor);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_975_57*  __var___Block_975_57 ;
};





struct tagSuiDesigner$__Closure_996_26 {
	void  (*invoke)(SuiDesigner$__Closure_996_26 *  self, int  newcolor);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_989_56*  __var___Block_989_56 ;
};





struct tagSuiDesigner$__Closure_1013_26 {
	void  (*invoke)(SuiDesigner$__Closure_1013_26 *  self, SuiDesigner$BezierEditView *  view);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1003_58*  __var___Block_1003_58 ;
};





struct tagSuiDesigner$__Closure_1171_26 {
	void  (*invoke)(SuiDesigner$__Closure_1171_26 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_1176_25 {
	void  (*invoke)(SuiDesigner$__Closure_1176_25 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_1184_32 {
	void  (*invoke)(SuiDesigner$__Closure_1184_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_1230_31 {
	void  (*invoke)(SuiDesigner$__Closure_1230_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1219_68*  __var___Block_1219_68 ;
};





struct tagSuiDesigner$__Closure_1248_31 {
	void  (*invoke)(SuiDesigner$__Closure_1248_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1219_68*  __var___Block_1219_68 ;
};





struct tagSuiDesigner$__Closure_1273_31 {
	void  (*invoke)(SuiDesigner$__Closure_1273_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1262_68*  __var___Block_1262_68 ;
};





struct tagSuiDesigner$__Closure_1291_31 {
	void  (*invoke)(SuiDesigner$__Closure_1291_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1262_68*  __var___Block_1262_68 ;
};





struct tagSuiDesigner$__Closure_1308_31 {
	void  (*invoke)(SuiDesigner$__Closure_1308_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1262_68*  __var___Block_1262_68 ;
};





struct tagSuiDesigner$__Closure_1331_31 {
	void  (*invoke)(SuiDesigner$__Closure_1331_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1320_68*  __var___Block_1320_68 ;
};





struct tagSuiDesigner$__Closure_1349_31 {
	void  (*invoke)(SuiDesigner$__Closure_1349_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1320_68*  __var___Block_1320_68 ;
};





struct tagSuiDesigner$__Closure_1366_31 {
	void  (*invoke)(SuiDesigner$__Closure_1366_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1320_68*  __var___Block_1320_68 ;
};





struct tagSuiDesigner$__Closure_1381_31 {
	void  (*invoke)(SuiDesigner$__Closure_1381_31 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1320_68*  __var___Block_1320_68 ;
};





struct tagSuiDesigner$__Closure_1423_38 {
	void  (*invoke)(SuiDesigner$__Closure_1423_38 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1405_31*  __var___Block_1405_31 ;
};





// static function declaration
static void  __finiBlock___Block_258_69(SuiDesigner$__Block_258_69 *  self);
static void  __finiBlock___Block_270_69(SuiDesigner$__Block_270_69 *  self);
static void  __finiBlock___Block_307_69(SuiDesigner$__Block_307_69 *  self);
static void  __finiBlock___Block_339_69(SuiDesigner$__Block_339_69 *  self);
static void  __finiBlock___Block_563_49(SuiDesigner$__Block_563_49 *  self);
static void  __finiBlock___Block_681_58(SuiDesigner$__Block_681_58 *  self);
static void  __finiBlock___Block_696_55(SuiDesigner$__Block_696_55 *  self);
static void  __finiBlock___Block_724_57(SuiDesigner$__Block_724_57 *  self);
static void  __finiBlock___Block_749_56(SuiDesigner$__Block_749_56 *  self);
static void  __finiBlock___Block_771_39(SuiDesigner$__Block_771_39 *  self);
static void  __finiBlock___Block_768_56(SuiDesigner$__Block_768_56 *  self);
static void  __finiBlock___Block_816_39(SuiDesigner$__Block_816_39 *  self);
static void  __finiBlock___Block_813_56(SuiDesigner$__Block_813_56 *  self);
static void  __finiBlock___Block_879_39(SuiDesigner$__Block_879_39 *  self);
static void  __finiBlock___Block_876_56(SuiDesigner$__Block_876_56 *  self);
static void  __finiBlock___Block_955_60(SuiDesigner$__Block_955_60 *  self);
static void  __finiBlock___Block_975_57(SuiDesigner$__Block_975_57 *  self);
static void  __finiBlock___Block_989_56(SuiDesigner$__Block_989_56 *  self);
static void  __finiBlock___Block_1003_58(SuiDesigner$__Block_1003_58 *  self);
static void  __finiBlock___Block_1219_68(SuiDesigner$__Block_1219_68 *  self);
static void  __finiBlock___Block_1262_68(SuiDesigner$__Block_1262_68 *  self);
static void  __finiBlock___Block_1320_68(SuiDesigner$__Block_1320_68 *  self);
static void  __finiBlock___Block_1405_31(SuiDesigner$__Block_1405_31 *  self);
static void  __fn___Closure_263_26(SuiDesigner$__Closure_263_26 *  self, int  newcolor);
static void  __fini___Closure_263_26(SuiDesigner$__Closure_263_26 *  self);
static SuiDesigner$__Closure_263_26*  __make___Closure_263_26(SuiDesigner$__Closure_263_26 **  __outRef__, SuiDesigner$__Block_258_69 *  __var___Block_258_69);
static void  __fn___Closure_283_30(SuiDesigner$__Closure_283_30 *  self, SuiCore$Event *  e);
static void  __fini___Closure_283_30(SuiDesigner$__Closure_283_30 *  self);
static SuiDesigner$__Closure_283_30*  __make___Closure_283_30(SuiDesigner$__Closure_283_30 **  __outRef__, SuiDesigner$__Block_270_69 *  __var___Block_270_69);
static void  __fn___Closure_291_42(SuiDesigner$__Closure_291_42 *  self, Orc$String*  newpath);
static void  __fini___Closure_291_42(SuiDesigner$__Closure_291_42 *  self);
static SuiDesigner$__Closure_291_42*  __make___Closure_291_42(SuiDesigner$__Closure_291_42 **  __outRef__, SuiDesigner$__Block_270_69 *  __var___Block_270_69);
static void  __fn___Closure_320_28(SuiDesigner$__Closure_320_28 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_320_28(SuiDesigner$__Closure_320_28 *  self);
static SuiDesigner$__Closure_320_28*  __make___Closure_320_28(SuiDesigner$__Closure_320_28 **  __outRef__, SuiDesigner$__Block_307_69 *  __var___Block_307_69);
static void  __fn___Closure_326_34(SuiDesigner$__Closure_326_34 *  self, Orc$String*  newpath);
static void  __fini___Closure_326_34(SuiDesigner$__Closure_326_34 *  self);
static SuiDesigner$__Closure_326_34*  __make___Closure_326_34(SuiDesigner$__Closure_326_34 **  __outRef__, SuiDesigner$__Block_307_69 *  __var___Block_307_69);
static void  __fn___Closure_342_26(SuiDesigner$__Closure_342_26 *  self, int  i, Orc$String*  label);
static void  __fini___Closure_342_26(SuiDesigner$__Closure_342_26 *  self);
static SuiDesigner$__Closure_342_26*  __make___Closure_342_26(SuiDesigner$__Closure_342_26 **  __outRef__, SuiDesigner$__Block_339_69 *  __var___Block_339_69);
static void  __fn___Closure_579_32(SuiDesigner$__Closure_579_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_579_32(SuiDesigner$__Closure_579_32 *  self);
static SuiDesigner$__Closure_579_32*  __make___Closure_579_32(SuiDesigner$__Closure_579_32 **  __outRef__, SuiDesigner$__Block_563_49 *  __var___Block_563_49);
static void  __fn___Closure_688_31(SuiDesigner$__Closure_688_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_688_31(SuiDesigner$__Closure_688_31 *  self);
static SuiDesigner$__Closure_688_31*  __make___Closure_688_31(SuiDesigner$__Closure_688_31 **  __outRef__, SuiDesigner$__Block_681_58 *  __var___Block_681_58);
static void  __fn___Closure_711_31(SuiDesigner$__Closure_711_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_711_31(SuiDesigner$__Closure_711_31 *  self);
static SuiDesigner$__Closure_711_31*  __make___Closure_711_31(SuiDesigner$__Closure_711_31 **  __outRef__, SuiDesigner$__Block_696_55 *  __var___Block_696_55);
static void  __fn___Closure_737_31(SuiDesigner$__Closure_737_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_737_31(SuiDesigner$__Closure_737_31 *  self);
static SuiDesigner$__Closure_737_31*  __make___Closure_737_31(SuiDesigner$__Closure_737_31 **  __outRef__, SuiDesigner$__Block_724_57 *  __var___Block_724_57);
static void  __fn___Closure_758_37(SuiDesigner$__Closure_758_37 *  self, SuiView$Switch *  v);
static void  __fini___Closure_758_37(SuiDesigner$__Closure_758_37 *  self);
static SuiDesigner$__Closure_758_37*  __make___Closure_758_37(SuiDesigner$__Closure_758_37 **  __outRef__, SuiDesigner$__Block_749_56 *  __var___Block_749_56);
static void  __fn___Closure_781_35(SuiDesigner$__Closure_781_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_781_35(SuiDesigner$__Closure_781_35 *  self);
static SuiDesigner$__Closure_781_35*  __make___Closure_781_35(SuiDesigner$__Closure_781_35 **  __outRef__, SuiDesigner$__Block_771_39 *  __var___Block_771_39, SuiDesigner$__Block_768_56 *  __var___Block_768_56);
static void  __fn___Closure_798_35(SuiDesigner$__Closure_798_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_798_35(SuiDesigner$__Closure_798_35 *  self);
static SuiDesigner$__Closure_798_35*  __make___Closure_798_35(SuiDesigner$__Closure_798_35 **  __outRef__, SuiDesigner$__Block_771_39 *  __var___Block_771_39, SuiDesigner$__Block_768_56 *  __var___Block_768_56);
static void  __fn___Closure_826_35(SuiDesigner$__Closure_826_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_826_35(SuiDesigner$__Closure_826_35 *  self);
static SuiDesigner$__Closure_826_35*  __make___Closure_826_35(SuiDesigner$__Closure_826_35 **  __outRef__, SuiDesigner$__Block_816_39 *  __var___Block_816_39, SuiDesigner$__Block_813_56 *  __var___Block_813_56);
static void  __fn___Closure_844_35(SuiDesigner$__Closure_844_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_844_35(SuiDesigner$__Closure_844_35 *  self);
static SuiDesigner$__Closure_844_35*  __make___Closure_844_35(SuiDesigner$__Closure_844_35 **  __outRef__, SuiDesigner$__Block_816_39 *  __var___Block_816_39, SuiDesigner$__Block_813_56 *  __var___Block_813_56);
static void  __fn___Closure_862_35(SuiDesigner$__Closure_862_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_862_35(SuiDesigner$__Closure_862_35 *  self);
static SuiDesigner$__Closure_862_35*  __make___Closure_862_35(SuiDesigner$__Closure_862_35 **  __outRef__, SuiDesigner$__Block_816_39 *  __var___Block_816_39, SuiDesigner$__Block_813_56 *  __var___Block_813_56);
static void  __fn___Closure_889_35(SuiDesigner$__Closure_889_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_889_35(SuiDesigner$__Closure_889_35 *  self);
static SuiDesigner$__Closure_889_35*  __make___Closure_889_35(SuiDesigner$__Closure_889_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56);
static void  __fn___Closure_906_35(SuiDesigner$__Closure_906_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_906_35(SuiDesigner$__Closure_906_35 *  self);
static SuiDesigner$__Closure_906_35*  __make___Closure_906_35(SuiDesigner$__Closure_906_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56);
static void  __fn___Closure_924_35(SuiDesigner$__Closure_924_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_924_35(SuiDesigner$__Closure_924_35 *  self);
static SuiDesigner$__Closure_924_35*  __make___Closure_924_35(SuiDesigner$__Closure_924_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56);
static void  __fn___Closure_940_35(SuiDesigner$__Closure_940_35 *  self, SuiView$EditText *  et);
static void  __fini___Closure_940_35(SuiDesigner$__Closure_940_35 *  self);
static SuiDesigner$__Closure_940_35*  __make___Closure_940_35(SuiDesigner$__Closure_940_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56);
static void  __fn___Closure_969_26(SuiDesigner$__Closure_969_26 *  self, int  newcolor);
static void  __fini___Closure_969_26(SuiDesigner$__Closure_969_26 *  self);
static SuiDesigner$__Closure_969_26*  __make___Closure_969_26(SuiDesigner$__Closure_969_26 **  __outRef__, SuiDesigner$__Block_955_60 *  __var___Block_955_60);
static void  __fn___Closure_982_26(SuiDesigner$__Closure_982_26 *  self, int  newcolor);
static void  __fini___Closure_982_26(SuiDesigner$__Closure_982_26 *  self);
static SuiDesigner$__Closure_982_26*  __make___Closure_982_26(SuiDesigner$__Closure_982_26 **  __outRef__, SuiDesigner$__Block_975_57 *  __var___Block_975_57);
static void  __fn___Closure_996_26(SuiDesigner$__Closure_996_26 *  self, int  newcolor);
static void  __fini___Closure_996_26(SuiDesigner$__Closure_996_26 *  self);
static SuiDesigner$__Closure_996_26*  __make___Closure_996_26(SuiDesigner$__Closure_996_26 **  __outRef__, SuiDesigner$__Block_989_56 *  __var___Block_989_56);
static void  __fn___Closure_1013_26(SuiDesigner$__Closure_1013_26 *  self, SuiDesigner$BezierEditView *  view);
static void  __fini___Closure_1013_26(SuiDesigner$__Closure_1013_26 *  self);
static SuiDesigner$__Closure_1013_26*  __make___Closure_1013_26(SuiDesigner$__Closure_1013_26 **  __outRef__, SuiDesigner$__Block_1003_58 *  __var___Block_1003_58);
static void  __fn___Closure_1171_26(SuiDesigner$__Closure_1171_26 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
static void  __fini___Closure_1171_26(SuiDesigner$__Closure_1171_26 *  self);
static SuiDesigner$__Closure_1171_26*  __make___Closure_1171_26(SuiDesigner$__Closure_1171_26 **  __outRef__);
static void  __fn___Closure_1176_25(SuiDesigner$__Closure_1176_25 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
static void  __fini___Closure_1176_25(SuiDesigner$__Closure_1176_25 *  self);
static SuiDesigner$__Closure_1176_25*  __make___Closure_1176_25(SuiDesigner$__Closure_1176_25 **  __outRef__);
static void  __fn___Closure_1184_32(SuiDesigner$__Closure_1184_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1184_32(SuiDesigner$__Closure_1184_32 *  self);
static SuiDesigner$__Closure_1184_32*  __make___Closure_1184_32(SuiDesigner$__Closure_1184_32 **  __outRef__);
static void  __fn___Closure_1230_31(SuiDesigner$__Closure_1230_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1230_31(SuiDesigner$__Closure_1230_31 *  self);
static SuiDesigner$__Closure_1230_31*  __make___Closure_1230_31(SuiDesigner$__Closure_1230_31 **  __outRef__, SuiDesigner$__Block_1219_68 *  __var___Block_1219_68);
static void  __fn___Closure_1248_31(SuiDesigner$__Closure_1248_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1248_31(SuiDesigner$__Closure_1248_31 *  self);
static SuiDesigner$__Closure_1248_31*  __make___Closure_1248_31(SuiDesigner$__Closure_1248_31 **  __outRef__, SuiDesigner$__Block_1219_68 *  __var___Block_1219_68);
static void  __fn___Closure_1273_31(SuiDesigner$__Closure_1273_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1273_31(SuiDesigner$__Closure_1273_31 *  self);
static SuiDesigner$__Closure_1273_31*  __make___Closure_1273_31(SuiDesigner$__Closure_1273_31 **  __outRef__, SuiDesigner$__Block_1262_68 *  __var___Block_1262_68);
static void  __fn___Closure_1291_31(SuiDesigner$__Closure_1291_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1291_31(SuiDesigner$__Closure_1291_31 *  self);
static SuiDesigner$__Closure_1291_31*  __make___Closure_1291_31(SuiDesigner$__Closure_1291_31 **  __outRef__, SuiDesigner$__Block_1262_68 *  __var___Block_1262_68);
static void  __fn___Closure_1308_31(SuiDesigner$__Closure_1308_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1308_31(SuiDesigner$__Closure_1308_31 *  self);
static SuiDesigner$__Closure_1308_31*  __make___Closure_1308_31(SuiDesigner$__Closure_1308_31 **  __outRef__, SuiDesigner$__Block_1262_68 *  __var___Block_1262_68);
static void  __fn___Closure_1331_31(SuiDesigner$__Closure_1331_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1331_31(SuiDesigner$__Closure_1331_31 *  self);
static SuiDesigner$__Closure_1331_31*  __make___Closure_1331_31(SuiDesigner$__Closure_1331_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68);
static void  __fn___Closure_1349_31(SuiDesigner$__Closure_1349_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1349_31(SuiDesigner$__Closure_1349_31 *  self);
static SuiDesigner$__Closure_1349_31*  __make___Closure_1349_31(SuiDesigner$__Closure_1349_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68);
static void  __fn___Closure_1366_31(SuiDesigner$__Closure_1366_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1366_31(SuiDesigner$__Closure_1366_31 *  self);
static SuiDesigner$__Closure_1366_31*  __make___Closure_1366_31(SuiDesigner$__Closure_1366_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68);
static void  __fn___Closure_1381_31(SuiDesigner$__Closure_1381_31 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1381_31(SuiDesigner$__Closure_1381_31 *  self);
static SuiDesigner$__Closure_1381_31*  __make___Closure_1381_31(SuiDesigner$__Closure_1381_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68);
static void  __fn___Closure_1423_38(SuiDesigner$__Closure_1423_38 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1423_38(SuiDesigner$__Closure_1423_38 *  self);
static SuiDesigner$__Closure_1423_38*  __make___Closure_1423_38(SuiDesigner$__Closure_1423_38 **  __outRef__, SuiDesigner$__Block_1405_31 *  __var___Block_1405_31);



//vtable instance
Vtable_SuiDesigner$EventInspAttrChanged _vtable_SuiDesigner$EventInspAttrChanged;

// init meta

void SuiDesigner$EventInspAttrChanged_initMeta(Vtable_SuiDesigner$EventInspAttrChanged *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "obj", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiDesigner$EventInspAttrChanged, obj), true, false, 1);
	orc_metaField_class(&pNext, "newValue", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiDesigner$EventInspAttrChanged, newValue), true, false, 1);
	orc_metaField_class(&pNext, "inspAttr", ((Vtable_Object*)Vtable_SuiDesigner$InspAttr_init(0)), offsetof(SuiDesigner$EventInspAttrChanged, inspAttr), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$EventInspAttrChanged* Vtable_SuiDesigner$EventInspAttrChanged_init(Vtable_SuiDesigner$EventInspAttrChanged* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$EventInspAttrChanged;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Event_init(&_vtable_SuiCore$Event);

	// init by super vtable init function
    Vtable_SuiCore$Event_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Event;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$EventInspAttrChanged_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$EventInspAttrChanged";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$EventInspAttrChanged_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$EventInspAttrChanged_fini(SuiDesigner$EventInspAttrChanged *self){
	//super fini
    SuiCore$Event_fini((SuiCore$Event *)self);

    //字段释放


}

// init fields function


void SuiDesigner$EventInspAttrChanged_init_fields(SuiDesigner$EventInspAttrChanged *self){
	//super class
    SuiCore$Event_init_fields((SuiCore$Event*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$EventInspAttrChanged_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$EventInspAttrChanged*)self)->obj, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$EventInspAttrChanged*)self)->newValue, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$EventInspAttrChanged*)self)->inspAttr, NULL);
    }
	
}

// init function

void SuiDesigner$EventInspAttrChanged_init(SuiDesigner$EventInspAttrChanged *self, void *pOwner){
    Vtable_SuiDesigner$EventInspAttrChanged_init(&_vtable_SuiDesigner$EventInspAttrChanged);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$EventInspAttrChanged;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$EventInspAttrChanged_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$EventInspAttrChanged * SuiDesigner$EventInspAttrChanged_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$EventInspAttrChanged *self = calloc(1, sizeof(SuiDesigner$EventInspAttrChanged));
	
    SuiDesigner$EventInspAttrChanged_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$InspOpt _vtable_SuiDesigner$InspOpt;

// init meta

void SuiDesigner$InspOpt_initMeta(Vtable_SuiDesigner$InspOpt *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_int, offsetof(SuiDesigner$InspOpt, value), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "label", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$InspOpt, label), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$InspOpt* Vtable_SuiDesigner$InspOpt_init(Vtable_SuiDesigner$InspOpt* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspOpt;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspOpt_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspOpt";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspOpt_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspOpt_fini(SuiDesigner$InspOpt *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspOpt_init_fields(SuiDesigner$InspOpt *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspOpt_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspOpt*)self)->label, NULL);
    }
	
}

// init function

void SuiDesigner$InspOpt_init(SuiDesigner$InspOpt *self, void *pOwner){
    Vtable_SuiDesigner$InspOpt_init(&_vtable_SuiDesigner$InspOpt);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspOpt;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspOpt_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspOpt * SuiDesigner$InspOpt_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspOpt *self = calloc(1, sizeof(SuiDesigner$InspOpt));
	
    SuiDesigner$InspOpt_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$InspOpts _vtable_SuiDesigner$InspOpts;

// init meta

void SuiDesigner$InspOpts_initMeta(Vtable_SuiDesigner$InspOpts *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "opts", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$InspOpts, opts), true, false, 1);

	orc_metaField_method(&pNext, "set", offsetof(SuiDesigner$InspOpts, set));
	orc_metaField_method(&pNext, "getValueByLabel", offsetof(SuiDesigner$InspOpts, getValueByLabel));
	orc_metaField_method(&pNext, "getLabels", offsetof(SuiDesigner$InspOpts, getLabels));
}


// vtable init


Vtable_SuiDesigner$InspOpts* Vtable_SuiDesigner$InspOpts_init(Vtable_SuiDesigner$InspOpts* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspOpts;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspOpts_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspOpts";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspOpts_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspOpts_fini(SuiDesigner$InspOpts *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspOpts_init_fields(SuiDesigner$InspOpts *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspOpts_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspOpts*)self)->opts, Orc$List_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$InspOpts*)self)->set = (void*)SuiDesigner$InspOpts$set;
	((SuiDesigner$InspOpts*)self)->getValueByLabel = (void*)SuiDesigner$InspOpts$getValueByLabel;
	((SuiDesigner$InspOpts*)self)->getLabels = (void*)SuiDesigner$InspOpts$getLabels;
}

// init function

void SuiDesigner$InspOpts_init(SuiDesigner$InspOpts *self, void *pOwner){
    Vtable_SuiDesigner$InspOpts_init(&_vtable_SuiDesigner$InspOpts);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspOpts;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspOpts_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspOpts * SuiDesigner$InspOpts_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspOpts *self = calloc(1, sizeof(SuiDesigner$InspOpts));
	
    SuiDesigner$InspOpts_init(self, pOwner);
    return self;
}


// class members
SuiDesigner$InspOpts *  SuiDesigner$InspOpts$set(SuiDesigner$InspOpts *  self, int  value, const char *  label){
	for (int  i = 0; i < self->opts->size(self->opts) ; i++) {
		SuiDesigner$InspOpt *  opt = (SuiDesigner$InspOpt * )self->opts->get(self->opts, i) ;
		if (opt->value == value) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_field_class(opt, (void * )offsetof(SuiDesigner$InspOpt, label) , Orc$str(&tmpReturn_1, label) ) ;
			return self; 
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspOpt*  opt = (opt=NULL,urgc_init_var_class((void**)&opt, SuiDesigner$InspOpt_new(&opt) ));
	opt->value = value;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(opt, (void * )offsetof(SuiDesigner$InspOpt, label) , Orc$str(&tmpReturn_2, label) ) ;
	self->opts->add(self->opts, opt) ;
	return self; 
}


int  SuiDesigner$InspOpts$getValueByLabel(SuiDesigner$InspOpts *  self, const char *  label){
	for (int  i = 0; i < self->opts->size(self->opts) ; i++) {
		SuiDesigner$InspOpt *  opt = (SuiDesigner$InspOpt * )self->opts->get(self->opts, i) ;
		if (Orc$String$equals(opt->label, label) ) {
			return opt->value; 
		}
	}
	return -1; 
}


Orc$List*  SuiDesigner$InspOpts$getLabels(Orc$List **  __outRef__, SuiDesigner$InspOpts *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  labels = (labels=NULL,urgc_init_var_class((void**)&labels, Orc$List_new(&labels) ));
	if (self->opts) {
		for (int  i = 0; i < self->opts->size(self->opts) ; i++) {
			SuiDesigner$InspOpt *  opt = (SuiDesigner$InspOpt * )self->opts->get(self->opts, i) ;
			labels->add(labels, opt->label) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, labels) ; 
}




// get or init meta 
MetaStruct* SuiDesigner$TmpAttrInfo_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiDesigner$TmpAttrInfo", sizeof( SuiDesigner$TmpAttrInfo ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_class(&pNext, "panelName", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$TmpAttrInfo, panelName), false, true, 1);
		orc_metaField_primitive(&pNext, "hboxIdx", OrcMetaType_int, offsetof(SuiDesigner$TmpAttrInfo, hboxIdx), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "isPanelStart", OrcMetaType_bool, offsetof(SuiDesigner$TmpAttrInfo, isPanelStart), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "isPanelEnd", OrcMetaType_bool, offsetof(SuiDesigner$TmpAttrInfo, isPanelEnd), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "isHboxStart", OrcMetaType_bool, offsetof(SuiDesigner$TmpAttrInfo, isHboxStart), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "isHboxEnd", OrcMetaType_bool, offsetof(SuiDesigner$TmpAttrInfo, isHboxEnd), 0, 0, 0, 0);//bool
    }
	return meta;
}

// get or init meta 
MetaStruct* SuiDesigner$MethodInfo_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiDesigner$MethodInfo", sizeof( SuiDesigner$MethodInfo ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "hboxIdx", OrcMetaType_int, offsetof(SuiDesigner$MethodInfo, hboxIdx), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "isMethod", OrcMetaType_bool, offsetof(SuiDesigner$MethodInfo, isMethod), 0, 0, 0, 0);//bool
    }
	return meta;
}
void  SuiDesigner$TmpAttrInfo$init(SuiDesigner$TmpAttrInfo *  self){
	memset(self, 0, sizeof(*self) ) ;
}

void  SuiDesigner$TmpAttrInfo$proc(SuiDesigner$TmpAttrInfo *  self, OrcMetaField *  mf, SuiDesigner$InspAttr *  attr, SuiDesigner$Insp *  insp){
	SuiDesigner$MethodInfo methodInfo = SuiDesigner$TmpAttrInfo$extractHboxIdx(self, mf) ;
	OrcMetaField *  nextMf = OrcMetaField_getNext(mf) ;
	SuiDesigner$MethodInfo nextMethodInfo = SuiDesigner$TmpAttrInfo$extractHboxIdx(self, nextMf) ;
	int  curHboxIdx = methodInfo.hboxIdx;
	int  nextHboxIdx = nextMethodInfo.hboxIdx;
	Orc$String *  curPanelName = attr ? attr->_panelName : NULL;
	Orc$String *  nextPanelName = NULL;
	if (nextMf) {
		SuiDesigner$InspAttr *  nextAttr = insp->getAttr(insp, nextMf->name) ;
		nextPanelName = nextAttr ? nextAttr->_panelName : NULL;
	}
	self->isHboxStart = self->hboxIdx != curHboxIdx && curHboxIdx > 0;
	self->isHboxEnd = curHboxIdx != nextHboxIdx && curHboxIdx > 0;
	if (!self->isHboxStart && !self->isHboxEnd && methodInfo.isMethod) {
		self->isHboxStart = true;
		self->isHboxEnd = true;
	}
	self->isPanelStart = !Orc$String$equalsString(self->panelName, curPanelName)  && curPanelName;
	self->isPanelEnd = !Orc$String$equalsString(curPanelName, nextPanelName)  && curPanelName;
	self->panelName = curPanelName;
	self->hboxIdx = curHboxIdx;
}

SuiDesigner$MethodInfo SuiDesigner$TmpAttrInfo$extractHboxIdx(SuiDesigner$TmpAttrInfo *  self, OrcMetaField *  mf){
	SuiDesigner$MethodInfo r;
	memset(&r, 0, sizeof(r) ) ;
	if (mf && mf->type == OrcMetaType_method && Orc$String_startsWith(mf->name, "insp")  && strlen(mf->name)  > 5) {
		r.isMethod = true;
		sscanf(mf->name, "insp%d", &r.hboxIdx) ;
	}
	return r; 
}


//vtable instance
Vtable_SuiDesigner$InspAttr _vtable_SuiDesigner$InspAttr;

// init meta

void SuiDesigner$InspAttr_initMeta(Vtable_SuiDesigner$InspAttr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "_name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$InspAttr, _name), true, false, 1);
	orc_metaField_class(&pNext, "_panelName", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$InspAttr, _panelName), true, false, 1);
	orc_metaField_primitive(&pNext, "_hbox", OrcMetaType_bool, offsetof(SuiDesigner$InspAttr, _hbox), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "_ignore", OrcMetaType_bool, offsetof(SuiDesigner$InspAttr, _ignore), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "bind", offsetof(SuiDesigner$InspAttr, bind));
	orc_metaField_method(&pNext, "to", offsetof(SuiDesigner$InspAttr, to));
	orc_metaField_method(&pNext, "inspValue", offsetof(SuiDesigner$InspAttr, inspValue));
}


// vtable init


Vtable_SuiDesigner$InspAttr* Vtable_SuiDesigner$InspAttr_init(Vtable_SuiDesigner$InspAttr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspAttr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspAttr_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspAttr";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspAttr_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspAttr_fini(SuiDesigner$InspAttr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspAttr_init_fields(SuiDesigner$InspAttr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspAttr_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspAttr*)self)->_name, Orc$str(&tmpReturn_1, "") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspAttr*)self)->_panelName, NULL);
	((SuiDesigner$InspAttr*)self)->_hbox = false;
	((SuiDesigner$InspAttr*)self)->_ignore = false;
    }
	((SuiDesigner$InspAttr*)self)->bind = (void*)SuiDesigner$InspAttr$bind;
	((SuiDesigner$InspAttr*)self)->to = (void*)SuiDesigner$InspAttr$to;
	((SuiDesigner$InspAttr*)self)->inspValue = (void*)SuiDesigner$InspAttr$inspValue;
}

// init function

void SuiDesigner$InspAttr_init(SuiDesigner$InspAttr *self, void *pOwner){
    Vtable_SuiDesigner$InspAttr_init(&_vtable_SuiDesigner$InspAttr);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspAttr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspAttr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspAttr * SuiDesigner$InspAttr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspAttr *self = calloc(1, sizeof(SuiDesigner$InspAttr));
	
    SuiDesigner$InspAttr_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspAttr$bind(SuiDesigner$InspAttr *  self, SuiDesigner$Insp *  insp, const char *  name, const char *  panelName){
	Orc$String$set(self->_name, name) ;
	if (panelName) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$InspAttr, _panelName) , Orc$str(&tmpReturn_1, panelName) ) ;
	}
	insp->attrMap->put(insp->attrMap, self->_name->str, self) ;
}


void  SuiDesigner$InspAttr$to(SuiDesigner$InspAttr *  self, SuiDesigner$Insp *  insp){
	insp->attrMap->put(insp->attrMap, self->_name->str, self) ;
}


void  SuiDesigner$InspAttr$inspValue(SuiDesigner$InspAttr *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp){
	insp->inspValueDefault(insp, o, obj, mf) ;
}




//vtable instance
Vtable_SuiDesigner$InspAttrColor _vtable_SuiDesigner$InspAttrColor;

// init meta

void SuiDesigner$InspAttrColor_initMeta(Vtable_SuiDesigner$InspAttrColor *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$InspAttrColor* Vtable_SuiDesigner$InspAttrColor_init(Vtable_SuiDesigner$InspAttrColor* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspAttrColor;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$InspAttr_init(&_vtable_SuiDesigner$InspAttr);

	// init by super vtable init function
    Vtable_SuiDesigner$InspAttr_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$InspAttr;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspAttrColor_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspAttrColor";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspAttrColor_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspAttrColor_fini(SuiDesigner$InspAttrColor *self){
	//super fini
    SuiDesigner$InspAttr_fini((SuiDesigner$InspAttr *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspAttrColor_init_fields(SuiDesigner$InspAttrColor *self){
	//super class
    SuiDesigner$InspAttr_init_fields((SuiDesigner$InspAttr*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspAttrColor_fini;
	//fields
    {
	
    }
	((SuiDesigner$InspAttr*)self)->inspValue = (void*)SuiDesigner$InspAttrColor$inspValue;
}

// init function

void SuiDesigner$InspAttrColor_init(SuiDesigner$InspAttrColor *self, void *pOwner){
    Vtable_SuiDesigner$InspAttrColor_init(&_vtable_SuiDesigner$InspAttrColor);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspAttrColor;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspAttrColor_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspAttrColor * SuiDesigner$InspAttrColor_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspAttrColor *self = calloc(1, sizeof(SuiDesigner$InspAttrColor));
	
    SuiDesigner$InspAttrColor_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspAttrColor$inspValue(SuiDesigner$InspAttrColor *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp){
	URGC_VAR_CLEANUP SuiDesigner$__Block_258_69*  __var___Block_258_69 = (__var___Block_258_69=NULL,urgc_init_var((void**)&__var___Block_258_69, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_258_69) , __finiBlock___Block_258_69) ));
	__var___Block_258_69->mf = mf;
	__var___Block_258_69->insp = insp;
	URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_1 = NULL;
	{
		SuiView$ColorPicker*  __scopeVar_259_8 = SuiView$mkColorPicker(&tmpReturn_1, o, 0) , *o = __scopeVar_259_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_259_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		int *  pColor = OrcMetaField_getIntPtr(__var___Block_258_69->mf, obj) ;
		((SuiCore$View * )o)->backgroundColor = *pColor;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_263_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_263_26(&tmpReturn_2, __var___Block_258_69) ) ;
	}
}




//vtable instance
Vtable_SuiDesigner$InspAttrImageSrc _vtable_SuiDesigner$InspAttrImageSrc;

// init meta

void SuiDesigner$InspAttrImageSrc_initMeta(Vtable_SuiDesigner$InspAttrImageSrc *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$InspAttrImageSrc* Vtable_SuiDesigner$InspAttrImageSrc_init(Vtable_SuiDesigner$InspAttrImageSrc* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspAttrImageSrc;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$InspAttr_init(&_vtable_SuiDesigner$InspAttr);

	// init by super vtable init function
    Vtable_SuiDesigner$InspAttr_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$InspAttr;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspAttrImageSrc_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspAttrImageSrc";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspAttrImageSrc_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspAttrImageSrc_fini(SuiDesigner$InspAttrImageSrc *self){
	//super fini
    SuiDesigner$InspAttr_fini((SuiDesigner$InspAttr *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspAttrImageSrc_init_fields(SuiDesigner$InspAttrImageSrc *self){
	//super class
    SuiDesigner$InspAttr_init_fields((SuiDesigner$InspAttr*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspAttrImageSrc_fini;
	//fields
    {
	
    }
	((SuiDesigner$InspAttr*)self)->inspValue = (void*)SuiDesigner$InspAttrImageSrc$inspValue;
}

// init function

void SuiDesigner$InspAttrImageSrc_init(SuiDesigner$InspAttrImageSrc *self, void *pOwner){
    Vtable_SuiDesigner$InspAttrImageSrc_init(&_vtable_SuiDesigner$InspAttrImageSrc);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspAttrImageSrc;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspAttrImageSrc_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspAttrImageSrc * SuiDesigner$InspAttrImageSrc_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspAttrImageSrc *self = calloc(1, sizeof(SuiDesigner$InspAttrImageSrc));
	
    SuiDesigner$InspAttrImageSrc_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspAttrImageSrc$inspValue(SuiDesigner$InspAttrImageSrc *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp){
	URGC_VAR_CLEANUP SuiDesigner$__Block_270_69*  __var___Block_270_69 = (__var___Block_270_69=NULL,urgc_init_var((void**)&__var___Block_270_69, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_270_69) , __finiBlock___Block_270_69) ));
	__var___Block_270_69->mf = mf;
	__var___Block_270_69->insp = insp;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_271_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )__var___Block_270_69->mf) , *o = __scopeVar_271_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_271_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		Orc$String$set(o->direction, "column") ;
		Orc$String$set(o->alignItems, "start") ;
		Orc$String *  src = *((Orc$String ** )OrcMetaField_getPtr(__var___Block_270_69->mf, obj) );
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_2 = NULL;
		{
			SuiView$ImageView*  __scopeVar_276_12 = SuiView$mkImageView(&tmpReturn_2, o, 0) , *o = __scopeVar_276_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_276_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 100;
			((SuiCore$View * )o)->height = 100;
			o->setImageMode(o, SuiView$WrapContent) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff999999) ;
			o->setSrc(o, src) ;
			Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_283_30*  tmpReturn_3 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_283_30(&tmpReturn_3, __var___Block_270_69) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
		{
			SuiView$TextView*  __scopeVar_300_12 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_300_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_300_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->setText(o, src) ;
		}
	}
}




//vtable instance
Vtable_SuiDesigner$InspAttrFilePath _vtable_SuiDesigner$InspAttrFilePath;

// init meta

void SuiDesigner$InspAttrFilePath_initMeta(Vtable_SuiDesigner$InspAttrFilePath *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$InspAttrFilePath* Vtable_SuiDesigner$InspAttrFilePath_init(Vtable_SuiDesigner$InspAttrFilePath* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspAttrFilePath;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$InspAttr_init(&_vtable_SuiDesigner$InspAttr);

	// init by super vtable init function
    Vtable_SuiDesigner$InspAttr_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$InspAttr;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspAttrFilePath_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspAttrFilePath";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspAttrFilePath_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspAttrFilePath_fini(SuiDesigner$InspAttrFilePath *self){
	//super fini
    SuiDesigner$InspAttr_fini((SuiDesigner$InspAttr *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspAttrFilePath_init_fields(SuiDesigner$InspAttrFilePath *self){
	//super class
    SuiDesigner$InspAttr_init_fields((SuiDesigner$InspAttr*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspAttrFilePath_fini;
	//fields
    {
	
    }
	((SuiDesigner$InspAttr*)self)->inspValue = (void*)SuiDesigner$InspAttrFilePath$inspValue;
}

// init function

void SuiDesigner$InspAttrFilePath_init(SuiDesigner$InspAttrFilePath *self, void *pOwner){
    Vtable_SuiDesigner$InspAttrFilePath_init(&_vtable_SuiDesigner$InspAttrFilePath);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspAttrFilePath;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspAttrFilePath_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspAttrFilePath * SuiDesigner$InspAttrFilePath_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspAttrFilePath *self = calloc(1, sizeof(SuiDesigner$InspAttrFilePath));
	
    SuiDesigner$InspAttrFilePath_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspAttrFilePath$inspValue(SuiDesigner$InspAttrFilePath *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp){
	URGC_VAR_CLEANUP SuiDesigner$__Block_307_69*  __var___Block_307_69 = (__var___Block_307_69=NULL,urgc_init_var((void**)&__var___Block_307_69, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_307_69) , __finiBlock___Block_307_69) ));
	__var___Block_307_69->mf = mf;
	__var___Block_307_69->insp = insp;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_308_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )__var___Block_307_69->mf) , *o = __scopeVar_308_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_308_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		Orc$String$set(o->direction, "column") ;
		Orc$String$set(o->alignItems, "start") ;
		Orc$String *  src = *((Orc$String ** )OrcMetaField_getPtr(__var___Block_307_69->mf, obj) );
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_2 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_313_12 = SuiView$mkDrawButton(&tmpReturn_2, o, 0) , *o = __scopeVar_313_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_313_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (src && Orc$String$notEmpty(src) ) {
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , src) ;
			}
			else {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_3, "null") ) ;
			}
			URGC_VAR_CLEANUP SuiDesigner$__Closure_320_28*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_320_28(&tmpReturn_4, __var___Block_307_69) ) ;
		}
	}
}




//vtable instance
Vtable_SuiDesigner$InspAttrSelect _vtable_SuiDesigner$InspAttrSelect;

// init meta

void SuiDesigner$InspAttrSelect_initMeta(Vtable_SuiDesigner$InspAttrSelect *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "opts", ((Vtable_Object*)Vtable_SuiDesigner$InspOpts_init(0)), offsetof(SuiDesigner$InspAttrSelect, opts), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$InspAttrSelect* Vtable_SuiDesigner$InspAttrSelect_init(Vtable_SuiDesigner$InspAttrSelect* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspAttrSelect;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$InspAttr_init(&_vtable_SuiDesigner$InspAttr);

	// init by super vtable init function
    Vtable_SuiDesigner$InspAttr_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$InspAttr;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspAttrSelect_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspAttrSelect";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspAttrSelect_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspAttrSelect_fini(SuiDesigner$InspAttrSelect *self){
	//super fini
    SuiDesigner$InspAttr_fini((SuiDesigner$InspAttr *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspAttrSelect_init_fields(SuiDesigner$InspAttrSelect *self){
	//super class
    SuiDesigner$InspAttr_init_fields((SuiDesigner$InspAttr*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspAttrSelect_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspOpts*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspAttrSelect*)self)->opts, SuiDesigner$InspOpts_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$InspAttr*)self)->inspValue = (void*)SuiDesigner$InspAttrSelect$inspValue;
}

// init function

void SuiDesigner$InspAttrSelect_init(SuiDesigner$InspAttrSelect *self, void *pOwner){
    Vtable_SuiDesigner$InspAttrSelect_init(&_vtable_SuiDesigner$InspAttrSelect);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspAttrSelect;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspAttrSelect_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspAttrSelect * SuiDesigner$InspAttrSelect_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspAttrSelect *self = calloc(1, sizeof(SuiDesigner$InspAttrSelect));
	
    SuiDesigner$InspAttrSelect_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspAttrSelect$inspValue(SuiDesigner$InspAttrSelect *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp){
	URGC_VAR_CLEANUP SuiDesigner$__Block_339_69*  __var___Block_339_69 = (__var___Block_339_69=NULL,urgc_init_var((void**)&__var___Block_339_69, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_339_69) , __finiBlock___Block_339_69) ));
	__var___Block_339_69->mf = mf;
	__var___Block_339_69->insp = insp;
	urgc_set_field_class(__var___Block_339_69, (void * )offsetof(SuiDesigner$__Block_339_69, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiView$Select*  tmpReturn_1 = NULL;
	{
		SuiView$Select*  __scopeVar_340_8 = SuiView$mkSelect(&tmpReturn_1, o, 0) , *o = __scopeVar_340_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_340_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiView$Select, options) , self->opts->getLabels(&tmpReturn_2, self->opts) ) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_342_26*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$Select, onChanged) , __make___Closure_342_26(&tmpReturn_3, __var___Block_339_69) ) ;
	}
}




//vtable instance
Vtable_SuiDesigner$InspNode _vtable_SuiDesigner$InspNode;

// init meta

void SuiDesigner$InspNode_initMeta(Vtable_SuiDesigner$InspNode *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$InspNode* Vtable_SuiDesigner$InspNode_init(Vtable_SuiDesigner$InspNode* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspNode;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Node_init(&_vtable_SuiCore$Node);

	// init by super vtable init function
    Vtable_SuiCore$Node_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Node;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspNode_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspNode";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspNode_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspNode_fini(SuiDesigner$InspNode *self){
	//super fini
    SuiCore$Node_fini((SuiCore$Node *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspNode_init_fields(SuiDesigner$InspNode *self){
	//super class
    SuiCore$Node_init_fields((SuiCore$Node*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspNode_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$InspNode_init(SuiDesigner$InspNode *self, void *pOwner){
    Vtable_SuiDesigner$InspNode_init(&_vtable_SuiDesigner$InspNode);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspNode;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspNode_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspNode * SuiDesigner$InspNode_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspNode *self = calloc(1, sizeof(SuiDesigner$InspNode));
	
    SuiDesigner$InspNode_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$InspAttrItem _vtable_SuiDesigner$InspAttrItem;

// init meta

void SuiDesigner$InspAttrItem_initMeta(Vtable_SuiDesigner$InspAttrItem *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "attr", ((Vtable_Object*)Vtable_SuiDesigner$InspAttr_init(0)), offsetof(SuiDesigner$InspAttrItem, attr), false, true, 1);

	
}


// vtable init


Vtable_SuiDesigner$InspAttrItem* Vtable_SuiDesigner$InspAttrItem_init(Vtable_SuiDesigner$InspAttrItem* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspAttrItem;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$InspNode_init(&_vtable_SuiDesigner$InspNode);

	// init by super vtable init function
    Vtable_SuiDesigner$InspNode_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$InspNode;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspAttrItem_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspAttrItem";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspAttrItem_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspAttrItem_fini(SuiDesigner$InspAttrItem *self){
	//super fini
    SuiDesigner$InspNode_fini((SuiDesigner$InspNode *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspAttrItem_init_fields(SuiDesigner$InspAttrItem *self){
	//super class
    SuiDesigner$InspNode_init_fields((SuiDesigner$InspNode*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspAttrItem_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$InspAttrItem_init(SuiDesigner$InspAttrItem *self, void *pOwner){
    Vtable_SuiDesigner$InspAttrItem_init(&_vtable_SuiDesigner$InspAttrItem);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspAttrItem;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspAttrItem_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspAttrItem * SuiDesigner$InspAttrItem_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspAttrItem *self = calloc(1, sizeof(SuiDesigner$InspAttrItem));
	
    SuiDesigner$InspAttrItem_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$InspPanel _vtable_SuiDesigner$InspPanel;

// init meta

void SuiDesigner$InspPanel_initMeta(Vtable_SuiDesigner$InspPanel *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$InspPanel* Vtable_SuiDesigner$InspPanel_init(Vtable_SuiDesigner$InspPanel* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspPanel;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$InspNode_init(&_vtable_SuiDesigner$InspNode);

	// init by super vtable init function
    Vtable_SuiDesigner$InspNode_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$InspNode;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspPanel_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspPanel";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspPanel_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspPanel_fini(SuiDesigner$InspPanel *self){
	//super fini
    SuiDesigner$InspNode_fini((SuiDesigner$InspNode *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspPanel_init_fields(SuiDesigner$InspPanel *self){
	//super class
    SuiDesigner$InspNode_init_fields((SuiDesigner$InspNode*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspPanel_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$InspPanel_init(SuiDesigner$InspPanel *self, void *pOwner){
    Vtable_SuiDesigner$InspPanel_init(&_vtable_SuiDesigner$InspPanel);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspPanel;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspPanel_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspPanel * SuiDesigner$InspPanel_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspPanel *self = calloc(1, sizeof(SuiDesigner$InspPanel));
	
    SuiDesigner$InspPanel_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$Insp _vtable_SuiDesigner$Insp;

// init meta

void SuiDesigner$Insp_initMeta(Vtable_SuiDesigner$Insp *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "curNodeStack", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$Insp, curNodeStack), true, false, 1);
	orc_metaField_class(&pNext, "obj", ((Vtable_Object*)Vtable_Object_init(0)), offsetof(SuiDesigner$Insp, obj), true, false, 1);
	orc_metaField_class(&pNext, "attrMap", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiDesigner$Insp, attrMap), true, false, 1);
	orc_metaField_class(&pNext, "lib", ((Vtable_Object*)Vtable_SuiDesigner$InspLib_init(0)), offsetof(SuiDesigner$Insp, lib), true, false, 1);

	orc_metaField_method(&pNext, "getAttr", offsetof(SuiDesigner$Insp, getAttr));
	orc_metaField_method(&pNext, "excludes", offsetof(SuiDesigner$Insp, excludes));
	orc_metaField_method(&pNext, "exclude", offsetof(SuiDesigner$Insp, exclude));
	orc_metaField_method(&pNext, "peekParent", offsetof(SuiDesigner$Insp, peekParent));
	orc_metaField_method(&pNext, "call_insp", offsetof(SuiDesigner$Insp, call_insp));
	orc_metaField_method(&pNext, "insp", offsetof(SuiDesigner$Insp, insp));
	orc_metaField_method(&pNext, "inspObj", offsetof(SuiDesigner$Insp, inspObj));
	orc_metaField_method(&pNext, "inspExtends", offsetof(SuiDesigner$Insp, inspExtends));
	orc_metaField_method(&pNext, "inspVt", offsetof(SuiDesigner$Insp, inspVt));
	orc_metaField_method(&pNext, "inspField", offsetof(SuiDesigner$Insp, inspField));
	orc_metaField_method(&pNext, "queryAttrDirection", offsetof(SuiDesigner$Insp, queryAttrDirection));
	orc_metaField_method(&pNext, "isSkipAttr", offsetof(SuiDesigner$Insp, isSkipAttr));
	orc_metaField_method(&pNext, "inspValueDefault", offsetof(SuiDesigner$Insp, inspValueDefault));
	orc_metaField_method(&pNext, "inspString", offsetof(SuiDesigner$Insp, inspString));
	orc_metaField_method(&pNext, "inspInt", offsetof(SuiDesigner$Insp, inspInt));
	orc_metaField_method(&pNext, "inspFloat", offsetof(SuiDesigner$Insp, inspFloat));
	orc_metaField_method(&pNext, "inspBool", offsetof(SuiDesigner$Insp, inspBool));
	orc_metaField_method(&pNext, "inspVec2", offsetof(SuiDesigner$Insp, inspVec2));
	orc_metaField_method(&pNext, "inspVec3", offsetof(SuiDesigner$Insp, inspVec3));
	orc_metaField_method(&pNext, "inspVec4", offsetof(SuiDesigner$Insp, inspVec4));
	orc_metaField_method(&pNext, "inspIntColor", offsetof(SuiDesigner$Insp, inspIntColor));
	orc_metaField_method(&pNext, "inspRgbaf", offsetof(SuiDesigner$Insp, inspRgbaf));
	orc_metaField_method(&pNext, "inspRgba", offsetof(SuiDesigner$Insp, inspRgba));
	orc_metaField_method(&pNext, "inspBezier", offsetof(SuiDesigner$Insp, inspBezier));
	orc_metaField_method(&pNext, "mkFieldName", offsetof(SuiDesigner$Insp, mkFieldName));
	orc_metaField_method(&pNext, "setAttrDefault", offsetof(SuiDesigner$Insp, setAttrDefault));
	orc_metaField_method(&pNext, "setAttr", offsetof(SuiDesigner$Insp, setAttr));
}


// vtable init


Vtable_SuiDesigner$Insp* Vtable_SuiDesigner$Insp_init(Vtable_SuiDesigner$Insp* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Insp;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Insp_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Insp";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Insp_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$Insp_fini(SuiDesigner$Insp *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$Insp_init_fields(SuiDesigner$Insp *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Insp_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Insp*)self)->curNodeStack, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$Insp*)self)->obj, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Insp*)self)->attrMap, Orc$Map_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$Insp*)self)->lib, SuiDesigner$useInspLib() );
	urgc_set_field(self, (void**)&((SuiDesigner$Insp*)self)->beforeInsp, NULL);
	urgc_set_field(self, (void**)&((SuiDesigner$Insp*)self)->afterInsp, NULL);
	urgc_set_field(self, (void**)&((SuiDesigner$Insp*)self)->cbInsp, NULL);
	urgc_set_field(self, (void**)&((SuiDesigner$Insp*)self)->cbSetAttr, NULL);
    }
	((SuiDesigner$Insp*)self)->getAttr = (void*)SuiDesigner$Insp$getAttr;
	((SuiDesigner$Insp*)self)->excludes = (void*)SuiDesigner$Insp$excludes;
	((SuiDesigner$Insp*)self)->exclude = (void*)SuiDesigner$Insp$exclude;
	((SuiDesigner$Insp*)self)->peekParent = (void*)SuiDesigner$Insp$peekParent;
	((SuiDesigner$Insp*)self)->call_insp = (void*)SuiDesigner$Insp$call_insp;
	((SuiDesigner$Insp*)self)->insp = (void*)SuiDesigner$Insp$insp;
	((SuiDesigner$Insp*)self)->inspObj = (void*)SuiDesigner$Insp$inspObj;
	((SuiDesigner$Insp*)self)->inspExtends = (void*)SuiDesigner$Insp$inspExtends;
	((SuiDesigner$Insp*)self)->inspVt = (void*)SuiDesigner$Insp$inspVt;
	((SuiDesigner$Insp*)self)->inspField = (void*)SuiDesigner$Insp$inspField;
	((SuiDesigner$Insp*)self)->queryAttrDirection = (void*)SuiDesigner$Insp$queryAttrDirection;
	((SuiDesigner$Insp*)self)->isSkipAttr = (void*)SuiDesigner$Insp$isSkipAttr;
	((SuiDesigner$Insp*)self)->inspValueDefault = (void*)SuiDesigner$Insp$inspValueDefault;
	((SuiDesigner$Insp*)self)->inspString = (void*)SuiDesigner$Insp$inspString;
	((SuiDesigner$Insp*)self)->inspInt = (void*)SuiDesigner$Insp$inspInt;
	((SuiDesigner$Insp*)self)->inspFloat = (void*)SuiDesigner$Insp$inspFloat;
	((SuiDesigner$Insp*)self)->inspBool = (void*)SuiDesigner$Insp$inspBool;
	((SuiDesigner$Insp*)self)->inspVec2 = (void*)SuiDesigner$Insp$inspVec2;
	((SuiDesigner$Insp*)self)->inspVec3 = (void*)SuiDesigner$Insp$inspVec3;
	((SuiDesigner$Insp*)self)->inspVec4 = (void*)SuiDesigner$Insp$inspVec4;
	((SuiDesigner$Insp*)self)->inspIntColor = (void*)SuiDesigner$Insp$inspIntColor;
	((SuiDesigner$Insp*)self)->inspRgbaf = (void*)SuiDesigner$Insp$inspRgbaf;
	((SuiDesigner$Insp*)self)->inspRgba = (void*)SuiDesigner$Insp$inspRgba;
	((SuiDesigner$Insp*)self)->inspBezier = (void*)SuiDesigner$Insp$inspBezier;
	((SuiDesigner$Insp*)self)->mkFieldName = (void*)SuiDesigner$Insp$mkFieldName;
	((SuiDesigner$Insp*)self)->setAttrDefault = (void*)SuiDesigner$Insp$setAttrDefault;
	((SuiDesigner$Insp*)self)->setAttr = (void*)SuiDesigner$Insp$setAttr;
}

// init function

void SuiDesigner$Insp_init(SuiDesigner$Insp *self, void *pOwner){
    Vtable_SuiDesigner$Insp_init(&_vtable_SuiDesigner$Insp);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Insp;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Insp_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Insp * SuiDesigner$Insp_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Insp *self = calloc(1, sizeof(SuiDesigner$Insp));
	
    SuiDesigner$Insp_init(self, pOwner);
    return self;
}


// class members
SuiDesigner$InspAttr *  SuiDesigner$Insp$getAttr(SuiDesigner$Insp *  self, const char *  key){
	SuiDesigner$InspAttr *  a = (SuiDesigner$InspAttr * )self->attrMap->get(self->attrMap, key) ;
	return a; 
}


void  SuiDesigner$Insp$excludes(SuiDesigner$Insp *  self, const char *  keys){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$List*  parts = Orc$String$splitByRe((parts = NULL,&parts), Orc$String$trim(&tmpReturn_1, Orc$str(&tmpReturn_2, keys) ) , "\\s+") ;
	int  size = parts->size(parts) ;
	for (int  i = 0; i < size; i++) {
		Orc$String *  key = (Orc$String * )parts->get(parts, i) ;
		self->exclude(self, key->str) ;
	}
}


void  SuiDesigner$Insp$exclude(SuiDesigner$Insp *  self, const char *  key){
	SuiDesigner$InspAttr *  a = self->getAttr(self, key) ;
	if (a) {
		a->_ignore = true;
	}
	else {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_1 = NULL;
		{
			SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_1) ;
			
		
			o->bind(o, self, key, NULL) ;
			o->_ignore = true;
		}
	}
}


SuiCore$Node *  SuiDesigner$Insp$peekParent(SuiDesigner$Insp *  self){
	return self->curNodeStack->last(self->curNodeStack) ; 
}


void  SuiDesigner$Insp$call_insp(SuiDesigner$Insp *  self){
	void **  ptr = orc_getFieldPtr(self->obj, "insp") ;
	if (ptr != NULL) {
		void  (*onInspect)(Object *  _self, SuiDesigner$Insp *  insp);
		onInspect = *ptr;
		if (onInspect) {
			onInspect(self->obj, self) ;
		}
	}
}


void  SuiDesigner$Insp$insp(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Insp, obj) , obj) ;
	self->curNodeStack->clear(self->curNodeStack) ;
	self->call_insp(self) ;
	if (self->beforeInsp) {
		(*(self->beforeInsp))((void * )(self->beforeInsp), self, o) ;
	}
	if (self->cbInsp) {
		(*(self->cbInsp))((void * )(self->cbInsp), self, o) ;
	}
	else {
		self->inspObj(self, o, obj) ;
	}
	if (self->afterInsp) {
		(*(self->afterInsp))((void * )(self->afterInsp), self, o) ;
	}
}


void  SuiDesigner$Insp$inspObj(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj){
	self->curNodeStack->push(self->curNodeStack, o) ;
	Vtable_Object *  vt = orc_getVtableByObject(obj) ;
	self->inspExtends(self, obj, vt) ;
	self->curNodeStack->pop(self->curNodeStack) ;
}


void  SuiDesigner$Insp$inspExtends(SuiDesigner$Insp *  self, Object *  obj, Vtable_Object *  vt){
	if (vt == NULL) {
		return ; 
	}
	Vtable_Object *  superVt = Vtable_getSuper(vt) ;
	self->inspExtends(self, obj, superVt) ;
	self->inspVt(self, obj, vt) ;
}


void  SuiDesigner$Insp$inspVt(SuiDesigner$Insp *  self, Object *  obj, Vtable_Object *  vt){
	OrcMetaField *  mf = orc_getOrInitMeta(vt) ;
	SuiDesigner$TmpAttrInfo tmp;
	SuiDesigner$TmpAttrInfo$init(&tmp) ;
	SuiView$Panel *  panel = NULL;
	SuiLayout$LayoutLinear *  ll = NULL;
	while (mf) {
		SuiDesigner$InspAttr *  attr = self->getAttr(self, mf->name) ;
		if (attr && attr->_ignore) {
			mf = OrcMetaField_getNext(mf) ;
			continue;
		}
		SuiDesigner$TmpAttrInfo$proc(&tmp, mf, attr, self) ;
		if (tmp.isPanelStart) {
			SuiCore$Node *  parent = self->peekParent(self) ;
			URGC_VAR_CLEANUP_CLASS SuiView$Panel*  tmpReturn_1 = NULL;
			panel = SuiView$mkPanel(&tmpReturn_1, parent, (long long )mf) ;
			if (((SuiCore$Node * )panel)->isNewForReact) {
				panel->open = false;
			}
			urgc_set_field_class(panel, (void * )offsetof(SuiView$Panel, title) , tmp.panelName) ;
			((SuiCore$Node * )panel)->react(panel) ;
			self->curNodeStack->push(self->curNodeStack, panel->body) ;
		}
		if (tmp.isHboxStart) {
			SuiCore$Node *  parent = self->peekParent(self) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
			ll = SuiLayout$layoutLinear(&tmpReturn_2, parent, (long long )mf) ;
			SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
			(tmpThis_1 = ll->row(ll) )->jcsb(tmpThis_1) ;
			self->curNodeStack->push(self->curNodeStack, ll) ;
		}
		self->inspField(self, obj, mf) ;
		if (tmp.isPanelEnd && panel) {
			SuiCore$Node$end((SuiCore$Node * )panel) ;
			self->curNodeStack->pop(self->curNodeStack) ;
		}
		if (tmp.isHboxEnd && ll) {
			SuiCore$Node$end((SuiCore$Node * )ll) ;
			self->curNodeStack->pop(self->curNodeStack) ;
		}
		mf = OrcMetaField_getNext(mf) ;
	}
}


void  SuiDesigner$Insp$inspField(SuiDesigner$Insp *  self, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_563_49*  __var___Block_563_49 = (__var___Block_563_49=NULL,urgc_init_var((void**)&__var___Block_563_49, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_563_49) , __finiBlock___Block_563_49) ));
	__var___Block_563_49->mf = mf;
	urgc_set_field_class(__var___Block_563_49, (void * )offsetof(SuiDesigner$__Block_563_49, self) , self) ;
	if (self->isSkipAttr(self, obj, __var___Block_563_49->mf) ) {
		return ; 
	}
	SuiDesigner$InspAttr *  attr = self->getAttr(self, __var___Block_563_49->mf->name) ;
	SuiCore$Node *  o = self->peekParent(self) ;
	if (__var___Block_563_49->mf->type == OrcMetaType_method) {
		if (Orc$String_startsWith(__var___Block_563_49->mf->name, "insp_") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_1 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_575_16 = SuiView$mkDrawButton(&tmpReturn_1, o, (long long )__var___Block_563_49->mf) , *o = __scopeVar_575_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_575_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_2, __var___Block_563_49->mf->name + 5) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_579_32*  tmpReturn_3 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_579_32(&tmpReturn_3, __var___Block_563_49) ) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
				{
					SuiLayout$LayoutLinearCell*  __scopeVar_589_20 = SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) , *o = __scopeVar_589_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_589_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->grow = 1;
					Orc$String$set(o->alignSelf, "stretch") ;
				}
			}
		}
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_5 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_599_8 = SuiLayout$layoutLinear(&tmpReturn_5, o, (long long )__var___Block_563_49->mf) , *o = __scopeVar_599_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_599_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		const char *  dir = self->queryAttrDirection(self, __var___Block_563_49->mf) ;
		((SuiCore$View * )o)->border->b->set(((SuiCore$View * )o)->border->b, 1, 0x13000000) ;
		Orc$String$set(o->direction, dir) ;
		self->mkFieldName(self, o, __var___Block_563_49->mf->name) ;
		if (attr) {
			attr->inspValue(attr, o, obj, __var___Block_563_49->mf, self) ;
		}
		else {
			self->inspValueDefault(self, o, obj, __var___Block_563_49->mf) ;
		}
	}
}


const char *  SuiDesigner$Insp$queryAttrDirection(SuiDesigner$Insp *  self, OrcMetaField *  mf){
	if (mf) {
		if (mf->metaStruct == metaStructOf(SuiCore$Bezier) ) {
			return "column"; 
		}
	}
	return "row"; 
}


bool  SuiDesigner$Insp$isSkipAttr(SuiDesigner$Insp *  self, Object *  obj, OrcMetaField *  mf){
	if (Orc$String_startsWith(mf->name, "_") ) {
		return true; 
	}
	SuiDesigner$InspLib *  tmpThis_1 = NULL;
	SuiDesigner$InspLibItem *  libItem = (tmpThis_1 = SuiDesigner$useInspLib() )->getByObject(tmpThis_1, obj) ;
	if (libItem) {
		return false; 
	}
	if (OrcMetaField_isStringRef(mf) ) {
		return false; 
	}
	if (OrcMetaField_isPrimitive(mf) ) {
		return false; 
	}
	if (mf->metaStruct == metaStructOf(SuiCore$Vec2) ) {
		return false; 
	}
	if (mf->metaStruct == metaStructOf(SuiCore$Vec3) ) {
		return false; 
	}
	if (mf->metaStruct == metaStructOf(SuiCore$Vec4) ) {
		return false; 
	}
	if (mf->metaStruct == metaStructOf(SuiCore$Rgba) ) {
		return false; 
	}
	if (mf->metaStruct == metaStructOf(SuiCore$Bezier) ) {
		return false; 
	}
	if (mf->type == OrcMetaType_method) {
		if (Orc$String_startsWith(mf->name, "insp") ) {
			return false; 
		}
	}
	return true; 
}


void  SuiDesigner$Insp$inspValueDefault(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	SuiDesigner$InspLib *  tmpThis_1 = NULL;
	SuiDesigner$InspLibItem *  libItem = (tmpThis_1 = SuiDesigner$useInspLib() )->getByObject(tmpThis_1, obj) ;
	if (libItem) {
		libItem->inspValue(libItem, o, obj, mf, self) ;
		return ; 
	}
	if (self->inspString(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspIntColor(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspInt(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspFloat(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspBool(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspVec2(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspVec3(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspVec4(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspRgba(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspRgbaf(self, o, obj, mf) ) {
		return ; 
	}
	if (self->inspBezier(self, o, obj, mf) ) {
		return ; 
	}
}


bool  SuiDesigner$Insp$inspString(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_681_58*  __var___Block_681_58 = (__var___Block_681_58=NULL,urgc_init_var((void**)&__var___Block_681_58, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_681_58) , __finiBlock___Block_681_58) ));
	__var___Block_681_58->mf = mf;
	urgc_set_field_class(__var___Block_681_58, (void * )offsetof(SuiDesigner$__Block_681_58, self) , self) ;
	if (!OrcMetaField_isStringRef(__var___Block_681_58->mf) ) {
		return false; 
	}
	Orc$String *  s = *((Orc$String ** )OrcMetaField_getPtr(__var___Block_681_58->mf, obj) );
	URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_1 = NULL;
	{
		SuiView$EditText*  __scopeVar_685_8 = SuiView$mkEditText(&tmpReturn_1, o, 0) , *o = __scopeVar_685_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_685_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->padding.left = 4;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setValue(o, s == NULL ? Orc$str(&tmpReturn_2, "")  : s) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_688_31*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_688_31(&tmpReturn_3, __var___Block_681_58) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_692_12 = SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) , *o = __scopeVar_692_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_692_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


bool  SuiDesigner$Insp$inspInt(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_696_55*  __var___Block_696_55 = (__var___Block_696_55=NULL,urgc_init_var((void**)&__var___Block_696_55, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_696_55) , __finiBlock___Block_696_55) ));
	__var___Block_696_55->mf = mf;
	urgc_set_field_class(__var___Block_696_55, (void * )offsetof(SuiDesigner$__Block_696_55, self) , self) ;
	if (!(OrcMetaField_isPrimitive(__var___Block_696_55->mf)  && (OrcMetaField_getType(__var___Block_696_55->mf)  == OrcMetaType_int))) {
		return false; 
	}
	int *  pv = OrcMetaField_getPtr(__var___Block_696_55->mf, obj) ;
	URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_1 = NULL;
	{
		SuiView$EditText*  __scopeVar_704_8 = SuiView$mkEditText(&tmpReturn_1, o, 0) , *o = __scopeVar_704_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_704_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  val = Orc$str((val = NULL,&val), "") ;
		Orc$String$addi(val, *pv) ;
		((SuiCore$View * )o)->padding.left = 4;
		o->setValue(o, val) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_711_31*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_711_31(&tmpReturn_2, __var___Block_696_55) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_719_12 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_719_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_719_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


bool  SuiDesigner$Insp$inspFloat(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_724_57*  __var___Block_724_57 = (__var___Block_724_57=NULL,urgc_init_var((void**)&__var___Block_724_57, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_724_57) , __finiBlock___Block_724_57) ));
	__var___Block_724_57->mf = mf;
	urgc_set_field_class(__var___Block_724_57, (void * )offsetof(SuiDesigner$__Block_724_57, self) , self) ;
	if (!(OrcMetaField_isPrimitive(__var___Block_724_57->mf)  && OrcMetaField_getType(__var___Block_724_57->mf)  == OrcMetaType_float)) {
		return false; 
	}
	float *  pv = OrcMetaField_getPtr(__var___Block_724_57->mf, obj) ;
	URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_1 = NULL;
	{
		SuiView$EditText*  __scopeVar_730_8 = SuiView$mkEditText(&tmpReturn_1, o, 0) , *o = __scopeVar_730_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_730_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  val = Orc$str((val = NULL,&val), "") ;
		Orc$String$addf(val, *pv) ;
		((SuiCore$View * )o)->padding.left = 4;
		o->setValue(o, val) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_737_31*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_737_31(&tmpReturn_2, __var___Block_724_57) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_745_12 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_745_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_745_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


bool  SuiDesigner$Insp$inspBool(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_749_56*  __var___Block_749_56 = (__var___Block_749_56=NULL,urgc_init_var((void**)&__var___Block_749_56, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_749_56) , __finiBlock___Block_749_56) ));
	__var___Block_749_56->mf = mf;
	urgc_set_field_class(__var___Block_749_56, (void * )offsetof(SuiDesigner$__Block_749_56, self) , self) ;
	if (!(OrcMetaField_isPrimitive(__var___Block_749_56->mf)  && OrcMetaField_getType(__var___Block_749_56->mf)  == OrcMetaType_bool)) {
		return false; 
	}
	bool *  pv = ((bool * )OrcMetaField_getPtr(__var___Block_749_56->mf, obj) );
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_755_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )__var___Block_749_56->mf) , *o = __scopeVar_755_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_755_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$Switch*  tmpReturn_2 = NULL;
		{
			SuiView$Switch*  __scopeVar_756_12 = SuiView$mkSwitch(&tmpReturn_2, o, 0) , *o = __scopeVar_756_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_756_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->setChecked(o, *pv) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_758_37*  tmpReturn_3 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$Switch, onCheckedChanged) , __make___Closure_758_37(&tmpReturn_3, __var___Block_749_56) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_763_12 = SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) , *o = __scopeVar_763_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_763_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


bool  SuiDesigner$Insp$inspVec2(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_768_56*  __var___Block_768_56 = (__var___Block_768_56=NULL,urgc_init_var((void**)&__var___Block_768_56, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_768_56) , __finiBlock___Block_768_56) ));
	__var___Block_768_56->mf = mf;
	urgc_set_field_class(__var___Block_768_56, (void * )offsetof(SuiDesigner$__Block_768_56, self) , self) ;
	if (__var___Block_768_56->mf->metaStruct != metaStructOf(SuiCore$Vec2) ) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_771_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )__var___Block_768_56->mf) , *o = __scopeVar_771_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_771_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP SuiDesigner$__Block_771_39*  __var___Block_771_39 = (__var___Block_771_39=NULL,urgc_init_var((void**)&__var___Block_771_39, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_771_39) , __finiBlock___Block_771_39) ));
		__var___Block_771_39->v = *((SuiCore$Vec2 * )OrcMetaField_getPtr(__var___Block_768_56->mf, obj) );
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_2 = NULL;
		{
			SuiView$EditText*  __scopeVar_774_12 = SuiView$mkEditText(&tmpReturn_2, o, 0) , *o = __scopeVar_774_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_774_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_3, "") , __var___Block_771_39->v.x) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff0000) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_781_35*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_781_35(&tmpReturn_4, __var___Block_771_39, __var___Block_768_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_789_16 = SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) , *o = __scopeVar_789_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_789_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_791_12 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_791_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_791_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff00ff00) ;
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_7, "") , __var___Block_771_39->v.y) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_798_35*  tmpReturn_8 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_798_35(&tmpReturn_8, __var___Block_771_39, __var___Block_768_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_807_16 = SuiLayout$layoutLinearCell(&tmpReturn_9, o, 0) , *o = __scopeVar_807_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_807_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_10 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_809_12 = SuiLayout$layoutLinearCell(&tmpReturn_10, o, 0) , *o = __scopeVar_809_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_809_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


bool  SuiDesigner$Insp$inspVec3(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_813_56*  __var___Block_813_56 = (__var___Block_813_56=NULL,urgc_init_var((void**)&__var___Block_813_56, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_813_56) , __finiBlock___Block_813_56) ));
	__var___Block_813_56->mf = mf;
	urgc_set_field_class(__var___Block_813_56, (void * )offsetof(SuiDesigner$__Block_813_56, self) , self) ;
	if (__var___Block_813_56->mf->metaStruct != metaStructOf(SuiCore$Vec3) ) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_816_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )__var___Block_813_56->mf) , *o = __scopeVar_816_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_816_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP SuiDesigner$__Block_816_39*  __var___Block_816_39 = (__var___Block_816_39=NULL,urgc_init_var((void**)&__var___Block_816_39, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_816_39) , __finiBlock___Block_816_39) ));
		__var___Block_816_39->v = *((SuiCore$Vec3 * )OrcMetaField_getPtr(__var___Block_813_56->mf, obj) );
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_2 = NULL;
		{
			SuiView$EditText*  __scopeVar_819_12 = SuiView$mkEditText(&tmpReturn_2, o, 0) , *o = __scopeVar_819_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_819_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_3, "") , __var___Block_816_39->v.x) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff0000) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_826_35*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_826_35(&tmpReturn_4, __var___Block_816_39, __var___Block_813_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_834_16 = SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) , *o = __scopeVar_834_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_834_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_836_12 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_836_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_836_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff00ff00) ;
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_7, "") , __var___Block_816_39->v.y) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_844_35*  tmpReturn_8 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_844_35(&tmpReturn_8, __var___Block_816_39, __var___Block_813_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_853_16 = SuiLayout$layoutLinearCell(&tmpReturn_9, o, 0) , *o = __scopeVar_853_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_853_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_10 = NULL;
		{
			SuiView$EditText*  __scopeVar_855_12 = SuiView$mkEditText(&tmpReturn_10, o, 0) , *o = __scopeVar_855_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_855_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_11, "") , __var___Block_816_39->v.z) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff0000ff) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_862_35*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_862_35(&tmpReturn_12, __var___Block_816_39, __var___Block_813_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_13 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_870_16 = SuiLayout$layoutLinearCell(&tmpReturn_13, o, 0) , *o = __scopeVar_870_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_870_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_14 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_872_12 = SuiLayout$layoutLinearCell(&tmpReturn_14, o, 0) , *o = __scopeVar_872_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_872_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


bool  SuiDesigner$Insp$inspVec4(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_876_56*  __var___Block_876_56 = (__var___Block_876_56=NULL,urgc_init_var((void**)&__var___Block_876_56, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_876_56) , __finiBlock___Block_876_56) ));
	__var___Block_876_56->mf = mf;
	urgc_set_field_class(__var___Block_876_56, (void * )offsetof(SuiDesigner$__Block_876_56, self) , self) ;
	if (__var___Block_876_56->mf->metaStruct != metaStructOf(SuiCore$Vec4) ) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_879_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )__var___Block_876_56->mf) , *o = __scopeVar_879_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_879_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP SuiDesigner$__Block_879_39*  __var___Block_879_39 = (__var___Block_879_39=NULL,urgc_init_var((void**)&__var___Block_879_39, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_879_39) , __finiBlock___Block_879_39) ));
		__var___Block_879_39->v = *((SuiCore$Vec4 * )OrcMetaField_getPtr(__var___Block_876_56->mf, obj) );
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_2 = NULL;
		{
			SuiView$EditText*  __scopeVar_882_12 = SuiView$mkEditText(&tmpReturn_2, o, 0) , *o = __scopeVar_882_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_882_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_3, "") , __var___Block_879_39->v.x) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff0000) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_889_35*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_889_35(&tmpReturn_4, __var___Block_879_39, __var___Block_876_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_897_16 = SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) , *o = __scopeVar_897_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_897_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_899_12 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_899_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_899_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff00ff00) ;
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_7, "") , __var___Block_879_39->v.y) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_906_35*  tmpReturn_8 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_906_35(&tmpReturn_8, __var___Block_879_39, __var___Block_876_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_915_16 = SuiLayout$layoutLinearCell(&tmpReturn_9, o, 0) , *o = __scopeVar_915_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_915_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_10 = NULL;
		{
			SuiView$EditText*  __scopeVar_917_12 = SuiView$mkEditText(&tmpReturn_10, o, 0) , *o = __scopeVar_917_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_917_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_11, "") , __var___Block_879_39->v.z) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff0000ff) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_924_35*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_924_35(&tmpReturn_12, __var___Block_879_39, __var___Block_876_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_13 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_932_16 = SuiLayout$layoutLinearCell(&tmpReturn_13, o, 0) , *o = __scopeVar_932_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_932_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_14 = NULL;
		{
			SuiView$EditText*  __scopeVar_934_12 = SuiView$mkEditText(&tmpReturn_14, o, 0) , *o = __scopeVar_934_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_934_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_15, "") , __var___Block_879_39->v.w) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff00ff) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_940_35*  tmpReturn_16 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_940_35(&tmpReturn_16, __var___Block_879_39, __var___Block_876_56) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_17 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_948_16 = SuiLayout$layoutLinearCell(&tmpReturn_17, o, 0) , *o = __scopeVar_948_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_948_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_18 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_950_12 = SuiLayout$layoutLinearCell(&tmpReturn_18, o, 0) , *o = __scopeVar_950_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_950_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


bool  SuiDesigner$Insp$inspIntColor(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_955_60*  __var___Block_955_60 = (__var___Block_955_60=NULL,urgc_init_var((void**)&__var___Block_955_60, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_955_60) , __finiBlock___Block_955_60) ));
	__var___Block_955_60->mf = mf;
	urgc_set_field_class(__var___Block_955_60, (void * )offsetof(SuiDesigner$__Block_955_60, self) , self) ;
	if (!(OrcMetaField_isPrimitive(__var___Block_955_60->mf)  && (OrcMetaField_getType(__var___Block_955_60->mf)  == OrcMetaType_int) && Orc$String_endsWithIgnoreCase(__var___Block_955_60->mf->name, "color") )) {
		return false; 
	}
	int *  pv = OrcMetaField_getPtr(__var___Block_955_60->mf, obj) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_1 = NULL;
	{
		SuiView$ColorPicker*  __scopeVar_967_8 = SuiView$mkColorPicker(&tmpReturn_1, o, 0) , *o = __scopeVar_967_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_967_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = *pv;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_969_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_969_26(&tmpReturn_2, __var___Block_955_60) ) ;
	}
	return true; 
}


bool  SuiDesigner$Insp$inspRgbaf(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_975_57*  __var___Block_975_57 = (__var___Block_975_57=NULL,urgc_init_var((void**)&__var___Block_975_57, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_975_57) , __finiBlock___Block_975_57) ));
	__var___Block_975_57->mf = mf;
	urgc_set_field_class(__var___Block_975_57, (void * )offsetof(SuiDesigner$__Block_975_57, self) , self) ;
	if (__var___Block_975_57->mf->metaStruct != metaStructOf(SuiCore$Rgbaf) ) {
		return false; 
	}
	SuiCore$Rgbaf v = *((SuiCore$Rgbaf * )OrcMetaField_getPtr(__var___Block_975_57->mf, obj) );
	URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_1 = NULL;
	{
		SuiView$ColorPicker*  __scopeVar_980_8 = SuiView$mkColorPicker(&tmpReturn_1, o, 0) , *o = __scopeVar_980_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_980_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = SuiCore$Rgbaf$toInt(&v) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_982_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_982_26(&tmpReturn_2, __var___Block_975_57) ) ;
	}
	return true; 
}


bool  SuiDesigner$Insp$inspRgba(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_989_56*  __var___Block_989_56 = (__var___Block_989_56=NULL,urgc_init_var((void**)&__var___Block_989_56, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_989_56) , __finiBlock___Block_989_56) ));
	__var___Block_989_56->mf = mf;
	urgc_set_field_class(__var___Block_989_56, (void * )offsetof(SuiDesigner$__Block_989_56, self) , self) ;
	if (__var___Block_989_56->mf->metaStruct != metaStructOf(SuiCore$Rgba) ) {
		return false; 
	}
	SuiCore$Rgba v = *((SuiCore$Rgba * )OrcMetaField_getPtr(__var___Block_989_56->mf, obj) );
	URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_1 = NULL;
	{
		SuiView$ColorPicker*  __scopeVar_994_8 = SuiView$mkColorPicker(&tmpReturn_1, o, 0) , *o = __scopeVar_994_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_994_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = SuiCore$Rgba$toInt(&v) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_996_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_996_26(&tmpReturn_2, __var___Block_989_56) ) ;
	}
	return true; 
}


bool  SuiDesigner$Insp$inspBezier(SuiDesigner$Insp *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf){
	URGC_VAR_CLEANUP SuiDesigner$__Block_1003_58*  __var___Block_1003_58 = (__var___Block_1003_58=NULL,urgc_init_var((void**)&__var___Block_1003_58, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1003_58) , __finiBlock___Block_1003_58) ));
	__var___Block_1003_58->mf = mf;
	urgc_set_field_class(__var___Block_1003_58, (void * )offsetof(SuiDesigner$__Block_1003_58, self) , self) ;
	if (__var___Block_1003_58->mf->metaStruct != metaStructOf(SuiCore$Bezier) ) {
		return false; 
	}
	SuiCore$Bezier v = *((SuiCore$Bezier * )OrcMetaField_getPtr(__var___Block_1003_58->mf, obj) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$BezierEditView*  tmpReturn_1 = NULL;
	{
		SuiDesigner$BezierEditView*  __scopeVar_1007_8 = SuiDesigner$mkBezierEditView(&tmpReturn_1, o, 0) , *o = __scopeVar_1007_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1007_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->setBezier(o, v) ;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->margin, 10) ;
		SuiCore$Inset$setVer(&((SuiCore$View * )o)->margin, 10) ;
		((SuiCore$View * )o)->height = 60;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_1013_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiDesigner$BezierEditView, onChanged) , __make___Closure_1013_26(&tmpReturn_2, __var___Block_1003_58) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_1018_12 = SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) , *o = __scopeVar_1018_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1018_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
	return true; 
}


void  SuiDesigner$Insp$mkFieldName(SuiDesigner$Insp *  self, SuiCore$Node *  o, const char *  name){
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_1023_8 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_1023_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1023_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setText(o, Orc$str(&tmpReturn_2, name) ) ;
		((SuiCore$View * )o)->width = 120;
		((SuiCore$View * )o)->margin.right = 10;
	}
}


void  SuiDesigner$Insp$setAttrDefault(SuiDesigner$Insp *  self, OrcMetaField *  mf, Object *  inspValue){
	Orc$Orc_setField(self->obj, mf, inspValue) ;
}


void  SuiDesigner$Insp$setAttr(SuiDesigner$Insp *  self, OrcMetaField *  mf, Object *  inspValue){
	SuiDesigner$InspAttr *  attr = self->getAttr(self, mf->name) ;
	if (attr) {
		
	}
	else {
		
	}
	if (self->cbSetAttr) {
		(*(self->cbSetAttr))((void * )(self->cbSetAttr), self->obj, mf, inspValue) ;
	}
	else {
		self->setAttrDefault(self, mf, inspValue) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventInspAttrChanged*  evt = (evt=NULL,urgc_init_var_class((void**)&evt, SuiDesigner$EventInspAttrChanged_new(&evt) ));
	urgc_set_field_class(evt, (void * )offsetof(SuiDesigner$EventInspAttrChanged, inspAttr) , attr) ;
	evt->mf = mf;
	urgc_set_field_class(evt, (void * )offsetof(SuiDesigner$EventInspAttrChanged, obj) , self->obj) ;
	urgc_set_field_class(evt, (void * )offsetof(SuiDesigner$EventInspAttrChanged, newValue) , inspValue) ;
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, evt) ;
}




//vtable instance
Vtable_SuiDesigner$InspLibItem _vtable_SuiDesigner$InspLibItem;

// init meta

void SuiDesigner$InspLibItem_initMeta(Vtable_SuiDesigner$InspLibItem *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$InspLibItem, name), true, false, 1);

	orc_metaField_method(&pNext, "inspValue", offsetof(SuiDesigner$InspLibItem, inspValue));
}


// vtable init


Vtable_SuiDesigner$InspLibItem* Vtable_SuiDesigner$InspLibItem_init(Vtable_SuiDesigner$InspLibItem* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspLibItem;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspLibItem_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspLibItem";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspLibItem_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspLibItem_fini(SuiDesigner$InspLibItem *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspLibItem_init_fields(SuiDesigner$InspLibItem *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspLibItem_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspLibItem*)self)->name, Orc$str(&tmpReturn_1, "") );
    }
	((SuiDesigner$InspLibItem*)self)->inspValue = (void*)SuiDesigner$InspLibItem$inspValue;
}

// init function

void SuiDesigner$InspLibItem_init(SuiDesigner$InspLibItem *self, void *pOwner){
    Vtable_SuiDesigner$InspLibItem_init(&_vtable_SuiDesigner$InspLibItem);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspLibItem;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspLibItem_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspLibItem * SuiDesigner$InspLibItem_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspLibItem *self = calloc(1, sizeof(SuiDesigner$InspLibItem));
	
    SuiDesigner$InspLibItem_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspLibItem$inspValue(SuiDesigner$InspLibItem *  self, SuiCore$Node *  o, Object *  obj, OrcMetaField *  mf, SuiDesigner$Insp *  insp){
	
}




//vtable instance
Vtable_SuiDesigner$InspLib _vtable_SuiDesigner$InspLib;

// init meta

void SuiDesigner$InspLib_initMeta(Vtable_SuiDesigner$InspLib *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "nameMap", ((Vtable_Object*)Vtable_Orc$Map_init(0)), offsetof(SuiDesigner$InspLib, nameMap), true, false, 1);

	orc_metaField_method(&pNext, "bind", offsetof(SuiDesigner$InspLib, bind));
	orc_metaField_method(&pNext, "getByObject", offsetof(SuiDesigner$InspLib, getByObject));
	orc_metaField_method(&pNext, "getByVtable", offsetof(SuiDesigner$InspLib, getByVtable));
}


// vtable init


Vtable_SuiDesigner$InspLib* Vtable_SuiDesigner$InspLib_init(Vtable_SuiDesigner$InspLib* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$InspLib;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$InspLib_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$InspLib";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$InspLib_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$InspLib_fini(SuiDesigner$InspLib *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$InspLib_init_fields(SuiDesigner$InspLib *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$InspLib_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$Map*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$InspLib*)self)->nameMap, Orc$Map_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$InspLib*)self)->bind = (void*)SuiDesigner$InspLib$bind;
	((SuiDesigner$InspLib*)self)->getByObject = (void*)SuiDesigner$InspLib$getByObject;
	((SuiDesigner$InspLib*)self)->getByVtable = (void*)SuiDesigner$InspLib$getByVtable;
}

// init function

void SuiDesigner$InspLib_init(SuiDesigner$InspLib *self, void *pOwner){
    Vtable_SuiDesigner$InspLib_init(&_vtable_SuiDesigner$InspLib);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$InspLib;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$InspLib_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$InspLib * SuiDesigner$InspLib_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$InspLib *self = calloc(1, sizeof(SuiDesigner$InspLib));
	
    SuiDesigner$InspLib_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$InspLib$bind(SuiDesigner$InspLib *  self, SuiDesigner$InspLibItem *  item){
	self->nameMap->put(self->nameMap, item->name->str, item) ;
}


SuiDesigner$InspLibItem *  SuiDesigner$InspLib$getByObject(SuiDesigner$InspLib *  self, Object *  obj){
	Vtable_Object *  vt = orc_getVtableByObject(obj) ;
	return self->getByVtable(self, vt) ; 
}


SuiDesigner$InspLibItem *  SuiDesigner$InspLib$getByVtable(SuiDesigner$InspLib *  self, Vtable_Object *  vt){
	SuiDesigner$InspLibItem *  item = (SuiDesigner$InspLibItem * )self->nameMap->get(self->nameMap, vt->className) ;
	return item; 
}



SuiDesigner$InspLib *  SuiDesigner$useInspLib(){
	static URGC_VAR_CLEANUP_CLASS SuiDesigner$InspLib*  lib = NULL;
	if (lib == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$InspLib*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&lib, SuiDesigner$InspLib_new(&tmpNewOwner_1) ) ;
	}
	return lib; 
}


//vtable instance
Vtable_SuiDesigner$TestObjSuper _vtable_SuiDesigner$TestObjSuper;

// init meta

void SuiDesigner$TestObjSuper_initMeta(Vtable_SuiDesigner$TestObjSuper *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "xx", OrcMetaType_int, offsetof(SuiDesigner$TestObjSuper, xx), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "yy", OrcMetaType_int, offsetof(SuiDesigner$TestObjSuper, yy), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "cc", OrcMetaType_int, offsetof(SuiDesigner$TestObjSuper, cc), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "kk", OrcMetaType_int, offsetof(SuiDesigner$TestObjSuper, kk), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "insp", offsetof(SuiDesigner$TestObjSuper, insp));
}


// vtable init


Vtable_SuiDesigner$TestObjSuper* Vtable_SuiDesigner$TestObjSuper_init(Vtable_SuiDesigner$TestObjSuper* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$TestObjSuper;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$TestObjSuper_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$TestObjSuper";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$TestObjSuper_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$TestObjSuper_fini(SuiDesigner$TestObjSuper *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$TestObjSuper_init_fields(SuiDesigner$TestObjSuper *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$TestObjSuper_fini;
	//fields
    {
	((SuiDesigner$TestObjSuper*)self)->xx = 29;
	((SuiDesigner$TestObjSuper*)self)->yy = 29;
	((SuiDesigner$TestObjSuper*)self)->cc = 29;
	((SuiDesigner$TestObjSuper*)self)->kk = 29;
    }
	((SuiDesigner$TestObjSuper*)self)->insp = (void*)SuiDesigner$TestObjSuper$insp;
}

// init function

void SuiDesigner$TestObjSuper_init(SuiDesigner$TestObjSuper *self, void *pOwner){
    Vtable_SuiDesigner$TestObjSuper_init(&_vtable_SuiDesigner$TestObjSuper);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$TestObjSuper;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$TestObjSuper_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$TestObjSuper * SuiDesigner$TestObjSuper_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$TestObjSuper *self = calloc(1, sizeof(SuiDesigner$TestObjSuper));
	
    SuiDesigner$TestObjSuper_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$TestObjSuper$insp(SuiDesigner$TestObjSuper *  self, SuiDesigner$Insp *  insp){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_1) ;
		
	
		o->bind(o, insp, "xx", "group") ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_2 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_2) ;
		
	
		o->bind(o, insp, "yy", "group") ;
	}
}




//vtable instance
Vtable_SuiDesigner$TestObj _vtable_SuiDesigner$TestObj;

// init meta

void SuiDesigner$TestObj_initMeta(Vtable_SuiDesigner$TestObj *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "age", OrcMetaType_int, offsetof(SuiDesigner$TestObj, age), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$TestObj, name), true, false, 1);
	orc_metaField_primitive(&pNext, "value", OrcMetaType_float, offsetof(SuiDesigner$TestObj, value), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "isMale", OrcMetaType_bool, offsetof(SuiDesigner$TestObj, isMale), 0, 0, 0, 0);//bool
	orc_metaField_struct(&pNext, "pos", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner$TestObj, pos), false, false, 0);
	orc_metaField_struct(&pNext, "rotation", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner$TestObj, rotation), false, false, 0);
	orc_metaField_struct(&pNext, "quat", SuiCore$Vec4_getOrInitMetaStruct(), offsetof(SuiDesigner$TestObj, quat), false, false, 0);

	orc_metaField_method(&pNext, "insp1_say", offsetof(SuiDesigner$TestObj, insp1_say));
	orc_metaField_method(&pNext, "insp1_say2", offsetof(SuiDesigner$TestObj, insp1_say2));
	orc_metaField_method(&pNext, "insp0_say2", offsetof(SuiDesigner$TestObj, insp0_say2));
}


// vtable init


Vtable_SuiDesigner$TestObj* Vtable_SuiDesigner$TestObj_init(Vtable_SuiDesigner$TestObj* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$TestObj;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$TestObjSuper_init(&_vtable_SuiDesigner$TestObjSuper);

	// init by super vtable init function
    Vtable_SuiDesigner$TestObjSuper_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$TestObjSuper;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$TestObj_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$TestObj";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$TestObj_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$TestObj_fini(SuiDesigner$TestObj *self){
	//super fini
    SuiDesigner$TestObjSuper_fini((SuiDesigner$TestObjSuper *)self);

    //字段释放


}

// init fields function


void SuiDesigner$TestObj_init_fields(SuiDesigner$TestObj *self){
	//super class
    SuiDesigner$TestObjSuper_init_fields((SuiDesigner$TestObjSuper*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$TestObj_fini;
	//fields
    {
	((SuiDesigner$TestObj*)self)->age = 10;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TestObj*)self)->name, Orc$str(&tmpReturn_1, "hi there") );
	((SuiDesigner$TestObj*)self)->value = 3.4;
	((SuiDesigner$TestObj*)self)->isMale = true;
    }
	((SuiDesigner$TestObjSuper*)self)->insp = (void*)SuiDesigner$TestObj$insp;
	((SuiDesigner$TestObj*)self)->insp1_say = (void*)SuiDesigner$TestObj$insp1_say;
	((SuiDesigner$TestObj*)self)->insp1_say2 = (void*)SuiDesigner$TestObj$insp1_say2;
	((SuiDesigner$TestObj*)self)->insp0_say2 = (void*)SuiDesigner$TestObj$insp0_say2;
}

// init function

void SuiDesigner$TestObj_init(SuiDesigner$TestObj *self, void *pOwner){
    Vtable_SuiDesigner$TestObj_init(&_vtable_SuiDesigner$TestObj);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$TestObj;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$TestObj_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$TestObj * SuiDesigner$TestObj_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$TestObj *self = calloc(1, sizeof(SuiDesigner$TestObj));
	
    SuiDesigner$TestObj_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$TestObj$insp(SuiDesigner$TestObj *  self, SuiDesigner$Insp *  insp){
	SuiDesigner$TestObjSuper$insp(self, insp) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_1) ;
		
	
		o->bind(o, insp, "age", "group") ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_2 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_2) ;
		
	
		o->bind(o, insp, "name", "group") ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_3 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_3) ;
		
	
		o->bind(o, insp, "isMale", NULL) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_4 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_4) ;
		
	
		o->bind(o, insp, "pos", "变换") ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_5 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_5) ;
		
	
		o->bind(o, insp, "rotation", "变换") ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttr*  tmpNewOwner_6 = NULL;
	{
		SuiDesigner$InspAttr*  o = SuiDesigner$InspAttr_new(&tmpNewOwner_6) ;
		
	
		o->bind(o, insp, "quat", "变换") ;
	}
	insp->excludes(insp, "age pos name quat ") ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1171_26*  tmpReturn_7 = NULL;
	urgc_set_field(insp, (void * )offsetof(SuiDesigner$Insp, beforeInsp) , __make___Closure_1171_26(&tmpReturn_7) ) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1176_25*  tmpReturn_8 = NULL;
	urgc_set_field(insp, (void * )offsetof(SuiDesigner$Insp, afterInsp) , __make___Closure_1176_25(&tmpReturn_8) ) ;
}


void  SuiDesigner$TestObj$insp1_say(SuiDesigner$TestObj *  self){
	SuiDialog$Toast_make("hi") ;
	printf("say hi\n") ;
}


void  SuiDesigner$TestObj$insp1_say2(SuiDesigner$TestObj *  self){
	SuiDialog$Toast_make("hi2") ;
	printf("say hi\n") ;
}


void  SuiDesigner$TestObj$insp0_say2(SuiDesigner$TestObj *  self){
	printf("say hi\n") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	SuiDialog$Toast_make(Orc$String$add(Orc$str(&tmpReturn_1, "hi3:") , self->name->str) ->str) ;
}



void  SuiDesigner$Insp_mkVec2(SuiCore$Node *  o, long long  key, SuiCore$Vec2 v, void  (**set)(void *  self, SuiCore$Vec2 nv)){
	URGC_REF_ARG_WITH_CLEANUP(set);

	URGC_VAR_CLEANUP SuiDesigner$__Block_1219_68*  __var___Block_1219_68 = (__var___Block_1219_68=NULL,urgc_init_var((void**)&__var___Block_1219_68, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1219_68) , __finiBlock___Block_1219_68) ));
	urgc_set_field(__var___Block_1219_68, (void * )offsetof(SuiDesigner$__Block_1219_68, set) , set) ;
	__var___Block_1219_68->v = v;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_1220_4 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )key) , *o = __scopeVar_1220_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1220_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_2 = NULL;
		{
			SuiView$EditText*  __scopeVar_1223_8 = SuiView$mkEditText(&tmpReturn_2, o, 0) , *o = __scopeVar_1223_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1223_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_3, "") , __var___Block_1219_68->v.x) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff0000) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1230_31*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1230_31(&tmpReturn_4, __var___Block_1219_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1238_12 = SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) , *o = __scopeVar_1238_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1238_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_1240_8 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_1240_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1240_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff00ff00) ;
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_7, "") , __var___Block_1219_68->v.y) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1248_31*  tmpReturn_8 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1248_31(&tmpReturn_8, __var___Block_1219_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1256_12 = SuiLayout$layoutLinearCell(&tmpReturn_9, o, 0) , *o = __scopeVar_1256_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1256_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_10 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_1259_8 = SuiLayout$layoutLinearCell(&tmpReturn_10, o, 0) , *o = __scopeVar_1259_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1259_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
}

void  SuiDesigner$Insp_mkVec3(SuiCore$Node *  o, long long  key, SuiCore$Vec3 v, void  (**set)(void *  self, SuiCore$Vec3 nv)){
	URGC_REF_ARG_WITH_CLEANUP(set);

	URGC_VAR_CLEANUP SuiDesigner$__Block_1262_68*  __var___Block_1262_68 = (__var___Block_1262_68=NULL,urgc_init_var((void**)&__var___Block_1262_68, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1262_68) , __finiBlock___Block_1262_68) ));
	urgc_set_field(__var___Block_1262_68, (void * )offsetof(SuiDesigner$__Block_1262_68, set) , set) ;
	__var___Block_1262_68->v = v;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_1263_4 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )key) , *o = __scopeVar_1263_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1263_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_2 = NULL;
		{
			SuiView$EditText*  __scopeVar_1266_8 = SuiView$mkEditText(&tmpReturn_2, o, 0) , *o = __scopeVar_1266_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1266_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_3, "") , __var___Block_1262_68->v.x) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff0000) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1273_31*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1273_31(&tmpReturn_4, __var___Block_1262_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1281_12 = SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) , *o = __scopeVar_1281_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1281_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_1283_8 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_1283_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1283_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff00ff00) ;
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_7, "") , __var___Block_1262_68->v.y) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1291_31*  tmpReturn_8 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1291_31(&tmpReturn_8, __var___Block_1262_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1299_12 = SuiLayout$layoutLinearCell(&tmpReturn_9, o, 0) , *o = __scopeVar_1299_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1299_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_10 = NULL;
		{
			SuiView$EditText*  __scopeVar_1301_8 = SuiView$mkEditText(&tmpReturn_10, o, 0) , *o = __scopeVar_1301_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1301_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_11, "") , __var___Block_1262_68->v.z) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff0000ff) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1308_31*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1308_31(&tmpReturn_12, __var___Block_1262_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_13 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1315_12 = SuiLayout$layoutLinearCell(&tmpReturn_13, o, 0) , *o = __scopeVar_1315_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1315_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_14 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_1317_8 = SuiLayout$layoutLinearCell(&tmpReturn_14, o, 0) , *o = __scopeVar_1317_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1317_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
}

void  SuiDesigner$Insp_mkVec4(SuiCore$Node *  o, long long  key, SuiCore$Vec4 v, void  (**set)(void *  self, SuiCore$Vec4 nv)){
	URGC_REF_ARG_WITH_CLEANUP(set);

	URGC_VAR_CLEANUP SuiDesigner$__Block_1320_68*  __var___Block_1320_68 = (__var___Block_1320_68=NULL,urgc_init_var((void**)&__var___Block_1320_68, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1320_68) , __finiBlock___Block_1320_68) ));
	urgc_set_field(__var___Block_1320_68, (void * )offsetof(SuiDesigner$__Block_1320_68, set) , set) ;
	__var___Block_1320_68->v = v;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_1321_4 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )key) , *o = __scopeVar_1321_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1321_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_2 = NULL;
		{
			SuiView$EditText*  __scopeVar_1324_8 = SuiView$mkEditText(&tmpReturn_2, o, 0) , *o = __scopeVar_1324_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1324_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_3, "") , __var___Block_1320_68->v.x) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff0000) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1331_31*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1331_31(&tmpReturn_4, __var___Block_1320_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1339_12 = SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) , *o = __scopeVar_1339_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1339_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_1341_8 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_1341_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1341_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff00ff00) ;
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_7, "") , __var___Block_1320_68->v.y) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1349_31*  tmpReturn_8 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1349_31(&tmpReturn_8, __var___Block_1320_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1357_12 = SuiLayout$layoutLinearCell(&tmpReturn_9, o, 0) , *o = __scopeVar_1357_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1357_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_10 = NULL;
		{
			SuiView$EditText*  __scopeVar_1359_8 = SuiView$mkEditText(&tmpReturn_10, o, 0) , *o = __scopeVar_1359_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1359_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.right = 8;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_11, "") , __var___Block_1320_68->v.z) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff0000ff) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1366_31*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1366_31(&tmpReturn_12, __var___Block_1320_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_13 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1373_12 = SuiLayout$layoutLinearCell(&tmpReturn_13, o, 0) , *o = __scopeVar_1373_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1373_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_14 = NULL;
		{
			SuiView$EditText*  __scopeVar_1375_8 = SuiView$mkEditText(&tmpReturn_14, o, 0) , *o = __scopeVar_1375_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1375_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->padding.left = 4;
			((SuiCore$View * )o)->margin.bottom = 4;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
			o->setValue_notInFocus(o, Orc$String$addf(Orc$str(&tmpReturn_15, "") , __var___Block_1320_68->v.w) ) ;
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff00ff) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1381_31*  tmpReturn_16 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1381_31(&tmpReturn_16, __var___Block_1320_68) ) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_17 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_1388_12 = SuiLayout$layoutLinearCell(&tmpReturn_17, o, 0) , *o = __scopeVar_1388_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1388_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_18 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_1390_8 = SuiLayout$layoutLinearCell(&tmpReturn_18, o, 0) , *o = __scopeVar_1390_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1390_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
	}
}

void  SuiDesigner$testInsp(){
	printf("hi insp\n") ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpNewOwner_2 = NULL;
		{
			SuiView$ScrollArea*  o = SuiView$ScrollArea_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1400_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0;
			win->setRootView(win, o) ;
			((SuiLayout$LayoutLinear * )o)->aiStretch(o) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_1405_12 = SuiLayout$layoutLinear(&tmpReturn_3, o, 0) , *o = __scopeVar_1405_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1405_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP SuiDesigner$__Block_1405_31*  __var___Block_1405_31 = (__var___Block_1405_31=NULL,urgc_init_var((void**)&__var___Block_1405_31, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1405_31) , __finiBlock___Block_1405_31) ));
				SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
				SuiLayout$LayoutLinear *  tmpThis_2 = NULL;
				(tmpThis_1 = (tmpThis_2 = o->column(o) )->jcs(tmpThis_2) )->aiStretch(tmpThis_1) ;
				((SuiCore$View * )o)->backgroundColor = 0x99efefff;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$TestObj*  tmpNewOwner_4 = NULL;
				urgc_set_field_class(__var___Block_1405_31, (void * )offsetof(SuiDesigner$__Block_1405_31, obj) , SuiDesigner$TestObj_new(&tmpNewOwner_4) ) ;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$Insp*  insp = (insp=NULL,urgc_init_var_class((void**)&insp, SuiDesigner$Insp_new(&insp) ));
				insp->insp(insp, o, __var___Block_1405_31->obj) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1423_38*  tmpReturn_5 = NULL;
				urgc_set_field(SuiCore$useEbus() , (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1423_38(&tmpReturn_5, __var___Block_1405_31) ) ;
			}
		}
		o->setTitle(o, "检视器") ;
		o->setSize(o, 640, 480) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}

static void  __finiBlock___Block_258_69(SuiDesigner$__Block_258_69 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_270_69(SuiDesigner$__Block_270_69 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_307_69(SuiDesigner$__Block_307_69 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_339_69(SuiDesigner$__Block_339_69 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_339_69, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_563_49(SuiDesigner$__Block_563_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_563_49, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_681_58(SuiDesigner$__Block_681_58 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_681_58, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_696_55(SuiDesigner$__Block_696_55 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_696_55, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_724_57(SuiDesigner$__Block_724_57 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_724_57, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_749_56(SuiDesigner$__Block_749_56 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_749_56, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_771_39(SuiDesigner$__Block_771_39 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_768_56(SuiDesigner$__Block_768_56 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_768_56, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_816_39(SuiDesigner$__Block_816_39 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_813_56(SuiDesigner$__Block_813_56 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_813_56, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_879_39(SuiDesigner$__Block_879_39 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_876_56(SuiDesigner$__Block_876_56 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_876_56, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_955_60(SuiDesigner$__Block_955_60 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_955_60, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_975_57(SuiDesigner$__Block_975_57 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_975_57, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_989_56(SuiDesigner$__Block_989_56 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_989_56, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1003_58(SuiDesigner$__Block_1003_58 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1003_58, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1219_68(SuiDesigner$__Block_1219_68 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1262_68(SuiDesigner$__Block_1262_68 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1320_68(SuiDesigner$__Block_1320_68 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1405_31(SuiDesigner$__Block_1405_31 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1405_31, obj) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_263_26(SuiDesigner$__Closure_263_26 *  self, int  newcolor){
	URGC_VAR_CLEANUP_CLASS Orc$Integer*  tmpReturn_1 = NULL;
	self->__var___Block_258_69->insp->setAttr(self->__var___Block_258_69->insp, self->__var___Block_258_69->mf, Orc$mkInteger(&tmpReturn_1, newcolor) ) ;
}

static void  __fini___Closure_263_26(SuiDesigner$__Closure_263_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_263_26, __var___Block_258_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_263_26*  __make___Closure_263_26(SuiDesigner$__Closure_263_26 **  __outRef__, SuiDesigner$__Block_258_69 *  __var___Block_258_69){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_263_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_263_26) , __fini___Closure_263_26) ));
	self->invoke = __fn___Closure_263_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_263_26, __var___Block_258_69) , __var___Block_258_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_283_30(SuiDesigner$__Closure_283_30 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$FileChooser*  fc = (fc=NULL,urgc_init_var_class((void**)&fc, SuiDesigner$FileChooser_new(&fc) ));
			fc->use_filterImage(fc) ;
			fc->loadPaths(fc) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_291_42*  tmpReturn_1 = NULL;
			urgc_set_field(fc, (void * )offsetof(SuiDesigner$FileChooser, onChoose) , __make___Closure_291_42(&tmpReturn_1, self->__var___Block_270_69) ) ;
			fc->showWindow(fc) ;
		}
	}
}

static void  __fini___Closure_283_30(SuiDesigner$__Closure_283_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_283_30, __var___Block_270_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_283_30*  __make___Closure_283_30(SuiDesigner$__Closure_283_30 **  __outRef__, SuiDesigner$__Block_270_69 *  __var___Block_270_69){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_283_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_283_30) , __fini___Closure_283_30) ));
	self->invoke = __fn___Closure_283_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_283_30, __var___Block_270_69) , __var___Block_270_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_291_42(SuiDesigner$__Closure_291_42 *  self, Orc$String*  newpath){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newpath);

	self->__var___Block_270_69->insp->setAttr(self->__var___Block_270_69->insp, self->__var___Block_270_69->mf, newpath) ;
}

static void  __fini___Closure_291_42(SuiDesigner$__Closure_291_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_291_42, __var___Block_270_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_291_42*  __make___Closure_291_42(SuiDesigner$__Closure_291_42 **  __outRef__, SuiDesigner$__Block_270_69 *  __var___Block_270_69){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_291_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_291_42) , __fini___Closure_291_42) ));
	self->invoke = __fn___Closure_291_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_291_42, __var___Block_270_69) , __var___Block_270_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_320_28(SuiDesigner$__Closure_320_28 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileChooser*  fc = (fc=NULL,urgc_init_var_class((void**)&fc, SuiDesigner$FileChooser_new(&fc) ));
	Orc$String$set(fc->dir, "./asset") ;
	fc->loadPaths(fc) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_326_34*  tmpReturn_1 = NULL;
	urgc_set_field(fc, (void * )offsetof(SuiDesigner$FileChooser, onChoose) , __make___Closure_326_34(&tmpReturn_1, self->__var___Block_307_69) ) ;
	fc->showWindow(fc) ;
}

static void  __fini___Closure_320_28(SuiDesigner$__Closure_320_28 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_320_28, __var___Block_307_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_320_28*  __make___Closure_320_28(SuiDesigner$__Closure_320_28 **  __outRef__, SuiDesigner$__Block_307_69 *  __var___Block_307_69){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_320_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_320_28) , __fini___Closure_320_28) ));
	self->invoke = __fn___Closure_320_28;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_320_28, __var___Block_307_69) , __var___Block_307_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_326_34(SuiDesigner$__Closure_326_34 *  self, Orc$String*  newpath){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newpath);

	self->__var___Block_307_69->insp->setAttr(self->__var___Block_307_69->insp, self->__var___Block_307_69->mf, newpath) ;
}

static void  __fini___Closure_326_34(SuiDesigner$__Closure_326_34 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_326_34, __var___Block_307_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_326_34*  __make___Closure_326_34(SuiDesigner$__Closure_326_34 **  __outRef__, SuiDesigner$__Block_307_69 *  __var___Block_307_69){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_326_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_326_34) , __fini___Closure_326_34) ));
	self->invoke = __fn___Closure_326_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_326_34, __var___Block_307_69) , __var___Block_307_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_342_26(SuiDesigner$__Closure_342_26 *  self, int  i, Orc$String*  label){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(label);

	int  intv = self->__var___Block_339_69->self->opts->getValueByLabel(self->__var___Block_339_69->self->opts, label->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$Integer*  tmpReturn_1 = NULL;
	self->__var___Block_339_69->insp->setAttr(self->__var___Block_339_69->insp, self->__var___Block_339_69->mf, Orc$mkInteger(&tmpReturn_1, intv) ) ;
}

static void  __fini___Closure_342_26(SuiDesigner$__Closure_342_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_342_26, __var___Block_339_69) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_342_26*  __make___Closure_342_26(SuiDesigner$__Closure_342_26 **  __outRef__, SuiDesigner$__Block_339_69 *  __var___Block_339_69){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_342_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_342_26) , __fini___Closure_342_26) ));
	self->invoke = __fn___Closure_342_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_342_26, __var___Block_339_69) , __var___Block_339_69) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_579_32(SuiDesigner$__Closure_579_32 *  self, SuiCore$MouseEvent *  me){
	void **  ptr = orc_getFieldPtr(self->__var___Block_563_49->self->obj, self->__var___Block_563_49->mf->name) ;
	if (ptr != NULL) {
		void  (*inspFn)(Object *  _self);
		inspFn = *ptr;
		if (inspFn) {
			inspFn(self->__var___Block_563_49->self->obj) ;
		}
	}
}

static void  __fini___Closure_579_32(SuiDesigner$__Closure_579_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_579_32, __var___Block_563_49) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_579_32*  __make___Closure_579_32(SuiDesigner$__Closure_579_32 **  __outRef__, SuiDesigner$__Block_563_49 *  __var___Block_563_49){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_579_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_579_32) , __fini___Closure_579_32) ));
	self->invoke = __fn___Closure_579_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_579_32, __var___Block_563_49) , __var___Block_563_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_688_31(SuiDesigner$__Closure_688_31 *  self, SuiView$EditText *  et){
	self->__var___Block_681_58->self->setAttr(self->__var___Block_681_58->self, self->__var___Block_681_58->mf, et->value) ;
}

static void  __fini___Closure_688_31(SuiDesigner$__Closure_688_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_688_31, __var___Block_681_58) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_688_31*  __make___Closure_688_31(SuiDesigner$__Closure_688_31 **  __outRef__, SuiDesigner$__Block_681_58 *  __var___Block_681_58){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_688_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_688_31) , __fini___Closure_688_31) ));
	self->invoke = __fn___Closure_688_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_688_31, __var___Block_681_58) , __var___Block_681_58) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_711_31(SuiDesigner$__Closure_711_31 *  self, SuiView$EditText *  et){
	printf("onValueChanged:%s\n", et->value->str) ;
	double  nv = atof(et->value->str) ;
	printf("\t  double value:%f\n", nv) ;
	URGC_VAR_CLEANUP_CLASS Orc$Double*  tmpReturn_1 = NULL;
	self->__var___Block_696_55->self->setAttr(self->__var___Block_696_55->self, self->__var___Block_696_55->mf, Orc$mkDouble(&tmpReturn_1, nv) ) ;
}

static void  __fini___Closure_711_31(SuiDesigner$__Closure_711_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_711_31, __var___Block_696_55) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_711_31*  __make___Closure_711_31(SuiDesigner$__Closure_711_31 **  __outRef__, SuiDesigner$__Block_696_55 *  __var___Block_696_55){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_711_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_711_31) , __fini___Closure_711_31) ));
	self->invoke = __fn___Closure_711_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_711_31, __var___Block_696_55) , __var___Block_696_55) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_737_31(SuiDesigner$__Closure_737_31 *  self, SuiView$EditText *  et){
	printf("onValueChanged:%s\n", et->value->str) ;
	double  nv = atof(et->value->str) ;
	printf("\t  double value:%f\n", nv) ;
	URGC_VAR_CLEANUP_CLASS Orc$Double*  tmpReturn_1 = NULL;
	self->__var___Block_724_57->self->setAttr(self->__var___Block_724_57->self, self->__var___Block_724_57->mf, Orc$mkDouble(&tmpReturn_1, nv) ) ;
}

static void  __fini___Closure_737_31(SuiDesigner$__Closure_737_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_737_31, __var___Block_724_57) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_737_31*  __make___Closure_737_31(SuiDesigner$__Closure_737_31 **  __outRef__, SuiDesigner$__Block_724_57 *  __var___Block_724_57){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_737_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_737_31) , __fini___Closure_737_31) ));
	self->invoke = __fn___Closure_737_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_737_31, __var___Block_724_57) , __var___Block_724_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_758_37(SuiDesigner$__Closure_758_37 *  self, SuiView$Switch *  v){
	URGC_VAR_CLEANUP_CLASS Orc$Boolean*  tmpReturn_1 = NULL;
	self->__var___Block_749_56->self->setAttr(self->__var___Block_749_56->self, self->__var___Block_749_56->mf, Orc$mkBoolean(&tmpReturn_1, v->checked) ) ;
}

static void  __fini___Closure_758_37(SuiDesigner$__Closure_758_37 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_758_37, __var___Block_749_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_758_37*  __make___Closure_758_37(SuiDesigner$__Closure_758_37 **  __outRef__, SuiDesigner$__Block_749_56 *  __var___Block_749_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_758_37*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_758_37) , __fini___Closure_758_37) ));
	self->invoke = __fn___Closure_758_37;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_758_37, __var___Block_749_56) , __var___Block_749_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_781_35(SuiDesigner$__Closure_781_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_771_39->v.x, nv) ;
	self->__var___Block_771_39->v.x = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_768_56->self->setAttr(self->__var___Block_768_56->self, self->__var___Block_768_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec2) , &self->__var___Block_771_39->v) ) ;
}

static void  __fini___Closure_781_35(SuiDesigner$__Closure_781_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_781_35, __var___Block_771_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_781_35, __var___Block_768_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_781_35*  __make___Closure_781_35(SuiDesigner$__Closure_781_35 **  __outRef__, SuiDesigner$__Block_771_39 *  __var___Block_771_39, SuiDesigner$__Block_768_56 *  __var___Block_768_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_781_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_781_35) , __fini___Closure_781_35) ));
	self->invoke = __fn___Closure_781_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_781_35, __var___Block_771_39) , __var___Block_771_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_781_35, __var___Block_768_56) , __var___Block_768_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_798_35(SuiDesigner$__Closure_798_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set y:%f=>%f\n", self->__var___Block_771_39->v.y, nv) ;
	self->__var___Block_771_39->v.y = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_768_56->self->setAttr(self->__var___Block_768_56->self, self->__var___Block_768_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec2) , &self->__var___Block_771_39->v) ) ;
}

static void  __fini___Closure_798_35(SuiDesigner$__Closure_798_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_798_35, __var___Block_771_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_798_35, __var___Block_768_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_798_35*  __make___Closure_798_35(SuiDesigner$__Closure_798_35 **  __outRef__, SuiDesigner$__Block_771_39 *  __var___Block_771_39, SuiDesigner$__Block_768_56 *  __var___Block_768_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_798_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_798_35) , __fini___Closure_798_35) ));
	self->invoke = __fn___Closure_798_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_798_35, __var___Block_771_39) , __var___Block_771_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_798_35, __var___Block_768_56) , __var___Block_768_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_826_35(SuiDesigner$__Closure_826_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_816_39->v.x, nv) ;
	self->__var___Block_816_39->v.x = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_813_56->self->setAttr(self->__var___Block_813_56->self, self->__var___Block_813_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec3) , &self->__var___Block_816_39->v) ) ;
}

static void  __fini___Closure_826_35(SuiDesigner$__Closure_826_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_826_35, __var___Block_816_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_826_35, __var___Block_813_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_826_35*  __make___Closure_826_35(SuiDesigner$__Closure_826_35 **  __outRef__, SuiDesigner$__Block_816_39 *  __var___Block_816_39, SuiDesigner$__Block_813_56 *  __var___Block_813_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_826_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_826_35) , __fini___Closure_826_35) ));
	self->invoke = __fn___Closure_826_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_826_35, __var___Block_816_39) , __var___Block_816_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_826_35, __var___Block_813_56) , __var___Block_813_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_844_35(SuiDesigner$__Closure_844_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set y:%f=>%f\n", self->__var___Block_816_39->v.y, nv) ;
	self->__var___Block_816_39->v.y = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_813_56->self->setAttr(self->__var___Block_813_56->self, self->__var___Block_813_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec3) , &self->__var___Block_816_39->v) ) ;
}

static void  __fini___Closure_844_35(SuiDesigner$__Closure_844_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_844_35, __var___Block_816_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_844_35, __var___Block_813_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_844_35*  __make___Closure_844_35(SuiDesigner$__Closure_844_35 **  __outRef__, SuiDesigner$__Block_816_39 *  __var___Block_816_39, SuiDesigner$__Block_813_56 *  __var___Block_813_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_844_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_844_35) , __fini___Closure_844_35) ));
	self->invoke = __fn___Closure_844_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_844_35, __var___Block_816_39) , __var___Block_816_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_844_35, __var___Block_813_56) , __var___Block_813_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_862_35(SuiDesigner$__Closure_862_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_816_39->v.z, nv) ;
	self->__var___Block_816_39->v.z = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_813_56->self->setAttr(self->__var___Block_813_56->self, self->__var___Block_813_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec3) , &self->__var___Block_816_39->v) ) ;
}

static void  __fini___Closure_862_35(SuiDesigner$__Closure_862_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_862_35, __var___Block_816_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_862_35, __var___Block_813_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_862_35*  __make___Closure_862_35(SuiDesigner$__Closure_862_35 **  __outRef__, SuiDesigner$__Block_816_39 *  __var___Block_816_39, SuiDesigner$__Block_813_56 *  __var___Block_813_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_862_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_862_35) , __fini___Closure_862_35) ));
	self->invoke = __fn___Closure_862_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_862_35, __var___Block_816_39) , __var___Block_816_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_862_35, __var___Block_813_56) , __var___Block_813_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_889_35(SuiDesigner$__Closure_889_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_879_39->v.x, nv) ;
	self->__var___Block_879_39->v.x = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_876_56->self->setAttr(self->__var___Block_876_56->self, self->__var___Block_876_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec4) , &self->__var___Block_879_39->v) ) ;
}

static void  __fini___Closure_889_35(SuiDesigner$__Closure_889_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_889_35, __var___Block_879_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_889_35, __var___Block_876_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_889_35*  __make___Closure_889_35(SuiDesigner$__Closure_889_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_889_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_889_35) , __fini___Closure_889_35) ));
	self->invoke = __fn___Closure_889_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_889_35, __var___Block_879_39) , __var___Block_879_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_889_35, __var___Block_876_56) , __var___Block_876_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_906_35(SuiDesigner$__Closure_906_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set y:%f=>%f\n", self->__var___Block_879_39->v.y, nv) ;
	self->__var___Block_879_39->v.y = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_876_56->self->setAttr(self->__var___Block_876_56->self, self->__var___Block_876_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec4) , &self->__var___Block_879_39->v) ) ;
}

static void  __fini___Closure_906_35(SuiDesigner$__Closure_906_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_906_35, __var___Block_879_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_906_35, __var___Block_876_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_906_35*  __make___Closure_906_35(SuiDesigner$__Closure_906_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_906_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_906_35) , __fini___Closure_906_35) ));
	self->invoke = __fn___Closure_906_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_906_35, __var___Block_879_39) , __var___Block_879_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_906_35, __var___Block_876_56) , __var___Block_876_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_924_35(SuiDesigner$__Closure_924_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_879_39->v.x, nv) ;
	self->__var___Block_879_39->v.z = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_876_56->self->setAttr(self->__var___Block_876_56->self, self->__var___Block_876_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec4) , &self->__var___Block_879_39->v) ) ;
}

static void  __fini___Closure_924_35(SuiDesigner$__Closure_924_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_924_35, __var___Block_879_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_924_35, __var___Block_876_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_924_35*  __make___Closure_924_35(SuiDesigner$__Closure_924_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_924_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_924_35) , __fini___Closure_924_35) ));
	self->invoke = __fn___Closure_924_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_924_35, __var___Block_879_39) , __var___Block_879_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_924_35, __var___Block_876_56) , __var___Block_876_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_940_35(SuiDesigner$__Closure_940_35 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_879_39->v.x, nv) ;
	self->__var___Block_879_39->v.w = nv;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_876_56->self->setAttr(self->__var___Block_876_56->self, self->__var___Block_876_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Vec4) , &self->__var___Block_879_39->v) ) ;
}

static void  __fini___Closure_940_35(SuiDesigner$__Closure_940_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_940_35, __var___Block_879_39) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_940_35, __var___Block_876_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_940_35*  __make___Closure_940_35(SuiDesigner$__Closure_940_35 **  __outRef__, SuiDesigner$__Block_879_39 *  __var___Block_879_39, SuiDesigner$__Block_876_56 *  __var___Block_876_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_940_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_940_35) , __fini___Closure_940_35) ));
	self->invoke = __fn___Closure_940_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_940_35, __var___Block_879_39) , __var___Block_879_39) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_940_35, __var___Block_876_56) , __var___Block_876_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_969_26(SuiDesigner$__Closure_969_26 *  self, int  newcolor){
	URGC_VAR_CLEANUP_CLASS Orc$Integer*  tmpReturn_1 = NULL;
	self->__var___Block_955_60->self->setAttr(self->__var___Block_955_60->self, self->__var___Block_955_60->mf, Orc$mkInteger(&tmpReturn_1, newcolor) ) ;
}

static void  __fini___Closure_969_26(SuiDesigner$__Closure_969_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_969_26, __var___Block_955_60) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_969_26*  __make___Closure_969_26(SuiDesigner$__Closure_969_26 **  __outRef__, SuiDesigner$__Block_955_60 *  __var___Block_955_60){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_969_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_969_26) , __fini___Closure_969_26) ));
	self->invoke = __fn___Closure_969_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_969_26, __var___Block_955_60) , __var___Block_955_60) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_982_26(SuiDesigner$__Closure_982_26 *  self, int  newcolor){
	SuiCore$Rgbaf nv = SuiCore$mkRgbafByInt(newcolor) ;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_975_57->self->setAttr(self->__var___Block_975_57->self, self->__var___Block_975_57->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Rgbaf) , &nv) ) ;
}

static void  __fini___Closure_982_26(SuiDesigner$__Closure_982_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_982_26, __var___Block_975_57) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_982_26*  __make___Closure_982_26(SuiDesigner$__Closure_982_26 **  __outRef__, SuiDesigner$__Block_975_57 *  __var___Block_975_57){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_982_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_982_26) , __fini___Closure_982_26) ));
	self->invoke = __fn___Closure_982_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_982_26, __var___Block_975_57) , __var___Block_975_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_996_26(SuiDesigner$__Closure_996_26 *  self, int  newcolor){
	SuiCore$Rgba nv = SuiCore$mkRgbaByInt(newcolor) ;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_989_56->self->setAttr(self->__var___Block_989_56->self, self->__var___Block_989_56->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Rgba) , &nv) ) ;
}

static void  __fini___Closure_996_26(SuiDesigner$__Closure_996_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_996_26, __var___Block_989_56) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_996_26*  __make___Closure_996_26(SuiDesigner$__Closure_996_26 **  __outRef__, SuiDesigner$__Block_989_56 *  __var___Block_989_56){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_996_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_996_26) , __fini___Closure_996_26) ));
	self->invoke = __fn___Closure_996_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_996_26, __var___Block_989_56) , __var___Block_989_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1013_26(SuiDesigner$__Closure_1013_26 *  self, SuiDesigner$BezierEditView *  view){
	SuiCore$Bezier nv = view->getBezier(view) ;
	URGC_VAR_CLEANUP_CLASS Orc$StructObj*  tmpReturn_1 = NULL;
	self->__var___Block_1003_58->self->setAttr(self->__var___Block_1003_58->self, self->__var___Block_1003_58->mf, Orc$mkStructObj(&tmpReturn_1, metaStructOf(SuiCore$Bezier) , &nv) ) ;
}

static void  __fini___Closure_1013_26(SuiDesigner$__Closure_1013_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1013_26, __var___Block_1003_58) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1013_26*  __make___Closure_1013_26(SuiDesigner$__Closure_1013_26 **  __outRef__, SuiDesigner$__Block_1003_58 *  __var___Block_1003_58){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1013_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1013_26) , __fini___Closure_1013_26) ));
	self->invoke = __fn___Closure_1013_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1013_26, __var___Block_1003_58) , __var___Block_1003_58) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1171_26(SuiDesigner$__Closure_1171_26 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_1 = NULL;
	{
		SuiView$DrawButton*  __scopeVar_1172_12 = SuiView$mkDrawButton(&tmpReturn_1, o, 0) , *o = __scopeVar_1172_12;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1172_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_2, "前置按钮") ) ;
	}
}

static void  __fini___Closure_1171_26(SuiDesigner$__Closure_1171_26 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1171_26*  __make___Closure_1171_26(SuiDesigner$__Closure_1171_26 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1171_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1171_26) , __fini___Closure_1171_26) ));
	self->invoke = __fn___Closure_1171_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1176_25(SuiDesigner$__Closure_1176_25 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_1177_12 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_1177_12;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1177_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
		SuiLayout$LayoutLinear *  tmpThis_2 = NULL;
		(tmpThis_1 = (tmpThis_2 = o->row(o) )->jcse(tmpThis_2) )->aic(tmpThis_1) ;
		SuiCore$Inset$setVer(&((SuiCore$View * )o)->padding, 6) ;
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_2 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_1181_16 = SuiView$mkDrawButton(&tmpReturn_2, o, 0) , *o = __scopeVar_1181_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1181_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 100;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_3, "提交") ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_1184_32*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1184_32(&tmpReturn_4) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_5 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_1188_16 = SuiView$mkDrawButton(&tmpReturn_5, o, 0) , *o = __scopeVar_1188_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1188_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 100;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_6, "取消") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_7 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_1192_16 = SuiView$mkDrawButton(&tmpReturn_7, o, 0) , *o = __scopeVar_1192_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1192_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 100;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_8, "上传") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_9 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_1196_16 = SuiView$mkDrawButton(&tmpReturn_9, o, 0) , *o = __scopeVar_1196_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1196_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 100;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_10, "控制") ) ;
		}
	}
}

static void  __fini___Closure_1176_25(SuiDesigner$__Closure_1176_25 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1176_25*  __make___Closure_1176_25(SuiDesigner$__Closure_1176_25 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1176_25*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1176_25) , __fini___Closure_1176_25) ));
	self->invoke = __fn___Closure_1176_25;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1184_32(SuiDesigner$__Closure_1184_32 *  self, SuiCore$MouseEvent *  me){
	SuiDialog$Toast_make("提交") ;
}

static void  __fini___Closure_1184_32(SuiDesigner$__Closure_1184_32 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1184_32*  __make___Closure_1184_32(SuiDesigner$__Closure_1184_32 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1184_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1184_32) , __fini___Closure_1184_32) ));
	self->invoke = __fn___Closure_1184_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1230_31(SuiDesigner$__Closure_1230_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_1219_68->v.x, nv) ;
	self->__var___Block_1219_68->v.x = nv;
	(*(self->__var___Block_1219_68->set))((void * )(self->__var___Block_1219_68->set), self->__var___Block_1219_68->v) ;
}

static void  __fini___Closure_1230_31(SuiDesigner$__Closure_1230_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1230_31, __var___Block_1219_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1230_31*  __make___Closure_1230_31(SuiDesigner$__Closure_1230_31 **  __outRef__, SuiDesigner$__Block_1219_68 *  __var___Block_1219_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1230_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1230_31) , __fini___Closure_1230_31) ));
	self->invoke = __fn___Closure_1230_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1230_31, __var___Block_1219_68) , __var___Block_1219_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1248_31(SuiDesigner$__Closure_1248_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set y:%f=>%f\n", self->__var___Block_1219_68->v.y, nv) ;
	self->__var___Block_1219_68->v.y = nv;
	(*(self->__var___Block_1219_68->set))((void * )(self->__var___Block_1219_68->set), self->__var___Block_1219_68->v) ;
}

static void  __fini___Closure_1248_31(SuiDesigner$__Closure_1248_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1248_31, __var___Block_1219_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1248_31*  __make___Closure_1248_31(SuiDesigner$__Closure_1248_31 **  __outRef__, SuiDesigner$__Block_1219_68 *  __var___Block_1219_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1248_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1248_31) , __fini___Closure_1248_31) ));
	self->invoke = __fn___Closure_1248_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1248_31, __var___Block_1219_68) , __var___Block_1219_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1273_31(SuiDesigner$__Closure_1273_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_1262_68->v.x, nv) ;
	self->__var___Block_1262_68->v.x = nv;
	(*(self->__var___Block_1262_68->set))((void * )(self->__var___Block_1262_68->set), self->__var___Block_1262_68->v) ;
}

static void  __fini___Closure_1273_31(SuiDesigner$__Closure_1273_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1273_31, __var___Block_1262_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1273_31*  __make___Closure_1273_31(SuiDesigner$__Closure_1273_31 **  __outRef__, SuiDesigner$__Block_1262_68 *  __var___Block_1262_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1273_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1273_31) , __fini___Closure_1273_31) ));
	self->invoke = __fn___Closure_1273_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1273_31, __var___Block_1262_68) , __var___Block_1262_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1291_31(SuiDesigner$__Closure_1291_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set y:%f=>%f\n", self->__var___Block_1262_68->v.y, nv) ;
	self->__var___Block_1262_68->v.y = nv;
	(*(self->__var___Block_1262_68->set))((void * )(self->__var___Block_1262_68->set), self->__var___Block_1262_68->v) ;
}

static void  __fini___Closure_1291_31(SuiDesigner$__Closure_1291_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1291_31, __var___Block_1262_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1291_31*  __make___Closure_1291_31(SuiDesigner$__Closure_1291_31 **  __outRef__, SuiDesigner$__Block_1262_68 *  __var___Block_1262_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1291_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1291_31) , __fini___Closure_1291_31) ));
	self->invoke = __fn___Closure_1291_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1291_31, __var___Block_1262_68) , __var___Block_1262_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1308_31(SuiDesigner$__Closure_1308_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_1262_68->v.z, nv) ;
	self->__var___Block_1262_68->v.z = nv;
	(*(self->__var___Block_1262_68->set))((void * )(self->__var___Block_1262_68->set), self->__var___Block_1262_68->v) ;
}

static void  __fini___Closure_1308_31(SuiDesigner$__Closure_1308_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1308_31, __var___Block_1262_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1308_31*  __make___Closure_1308_31(SuiDesigner$__Closure_1308_31 **  __outRef__, SuiDesigner$__Block_1262_68 *  __var___Block_1262_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1308_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1308_31) , __fini___Closure_1308_31) ));
	self->invoke = __fn___Closure_1308_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1308_31, __var___Block_1262_68) , __var___Block_1262_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1331_31(SuiDesigner$__Closure_1331_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_1320_68->v.x, nv) ;
	self->__var___Block_1320_68->v.x = nv;
	(*(self->__var___Block_1320_68->set))((void * )(self->__var___Block_1320_68->set), self->__var___Block_1320_68->v) ;
}

static void  __fini___Closure_1331_31(SuiDesigner$__Closure_1331_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1331_31, __var___Block_1320_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1331_31*  __make___Closure_1331_31(SuiDesigner$__Closure_1331_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1331_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1331_31) , __fini___Closure_1331_31) ));
	self->invoke = __fn___Closure_1331_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1331_31, __var___Block_1320_68) , __var___Block_1320_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1349_31(SuiDesigner$__Closure_1349_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set y:%f=>%f\n", self->__var___Block_1320_68->v.y, nv) ;
	self->__var___Block_1320_68->v.y = nv;
	(*(self->__var___Block_1320_68->set))((void * )(self->__var___Block_1320_68->set), self->__var___Block_1320_68->v) ;
}

static void  __fini___Closure_1349_31(SuiDesigner$__Closure_1349_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1349_31, __var___Block_1320_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1349_31*  __make___Closure_1349_31(SuiDesigner$__Closure_1349_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1349_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1349_31) , __fini___Closure_1349_31) ));
	self->invoke = __fn___Closure_1349_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1349_31, __var___Block_1320_68) , __var___Block_1320_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1366_31(SuiDesigner$__Closure_1366_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set x:%f=>%f\n", self->__var___Block_1320_68->v.z, nv) ;
	self->__var___Block_1320_68->v.z = nv;
	(*(self->__var___Block_1320_68->set))((void * )(self->__var___Block_1320_68->set), self->__var___Block_1320_68->v) ;
}

static void  __fini___Closure_1366_31(SuiDesigner$__Closure_1366_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1366_31, __var___Block_1320_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1366_31*  __make___Closure_1366_31(SuiDesigner$__Closure_1366_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1366_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1366_31) , __fini___Closure_1366_31) ));
	self->invoke = __fn___Closure_1366_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1366_31, __var___Block_1320_68) , __var___Block_1320_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1381_31(SuiDesigner$__Closure_1381_31 *  self, SuiView$EditText *  et){
	double  nv = atof(et->value->str) ;
	printf("set w:%f=>%f\n", self->__var___Block_1320_68->v.x, nv) ;
	self->__var___Block_1320_68->v.w = nv;
	(*(self->__var___Block_1320_68->set))((void * )(self->__var___Block_1320_68->set), self->__var___Block_1320_68->v) ;
}

static void  __fini___Closure_1381_31(SuiDesigner$__Closure_1381_31 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1381_31, __var___Block_1320_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1381_31*  __make___Closure_1381_31(SuiDesigner$__Closure_1381_31 **  __outRef__, SuiDesigner$__Block_1320_68 *  __var___Block_1320_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1381_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1381_31) , __fini___Closure_1381_31) ));
	self->invoke = __fn___Closure_1381_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1381_31, __var___Block_1320_68) , __var___Block_1320_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1423_38(SuiDesigner$__Closure_1423_38 *  self, SuiCore$Event *  e){
	printf("收到事件:%s\n", orc_getVtableByObject(e) ->className) ;
	printf("TestObj:%d %s. value:%f, isMale:%d\n", self->__var___Block_1405_31->obj->age, self->__var___Block_1405_31->obj->name->str, self->__var___Block_1405_31->obj->value, self->__var___Block_1405_31->obj->isMale) ;
	printf("pos:%f,%f\n", self->__var___Block_1405_31->obj->pos.x, self->__var___Block_1405_31->obj->pos.y) ;
	printf("rotation:%f,%f,%f\n", self->__var___Block_1405_31->obj->rotation.x, self->__var___Block_1405_31->obj->rotation.y, self->__var___Block_1405_31->obj->rotation.z) ;
	printf("quat:%f,%f,%f,%f\n", self->__var___Block_1405_31->obj->quat.x, self->__var___Block_1405_31->obj->quat.y, self->__var___Block_1405_31->obj->quat.z, self->__var___Block_1405_31->obj->quat.w) ;
}

static void  __fini___Closure_1423_38(SuiDesigner$__Closure_1423_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1423_38, __var___Block_1405_31) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1423_38*  __make___Closure_1423_38(SuiDesigner$__Closure_1423_38 **  __outRef__, SuiDesigner$__Block_1405_31 *  __var___Block_1405_31){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1423_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1423_38) , __fini___Closure_1423_38) ));
	self->invoke = __fn___Closure_1423_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1423_38, __var___Block_1405_31) , __var___Block_1405_31) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



