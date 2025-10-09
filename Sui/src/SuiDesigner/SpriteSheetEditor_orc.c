
#include "SpriteSheetEditor_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
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


// static struct 
typedef struct tagSuiDesigner$__Block_48_15 SuiDesigner$__Block_48_15;

typedef struct tagSuiDesigner$__Block_274_15 SuiDesigner$__Block_274_15;

typedef struct tagSuiDesigner$__Block_329_51 SuiDesigner$__Block_329_51;

typedef struct tagSuiDesigner$__Block_364_49 SuiDesigner$__Block_364_49;

typedef struct tagSuiDesigner$__Block_371_53 SuiDesigner$__Block_371_53;

typedef struct tagSuiDesigner$__Block_385_62 SuiDesigner$__Block_385_62;

typedef struct tagSuiDesigner$__Block_435_49 SuiDesigner$__Block_435_49;

typedef struct tagSuiDesigner$__Block_551_16 SuiDesigner$__Block_551_16;

typedef struct tagSuiDesigner$__Closure_49_37 SuiDesigner$__Closure_49_37;

typedef struct tagSuiDesigner$__Closure_275_27 SuiDesigner$__Closure_275_27;

typedef struct tagSuiDesigner$__Closure_283_34 SuiDesigner$__Closure_283_34;

typedef struct tagSuiDesigner$__Closure_291_33 SuiDesigner$__Closure_291_33;

typedef struct tagSuiDesigner$__Closure_336_26 SuiDesigner$__Closure_336_26;

typedef struct tagSuiDesigner$__Closure_366_51 SuiDesigner$__Closure_366_51;

typedef struct tagSuiDesigner$__Closure_401_44 SuiDesigner$__Closure_401_44;

typedef struct tagSuiDesigner$__Closure_onActive_404 SuiDesigner$__Closure_onActive_404;

typedef struct tagSuiDesigner$__Closure_422_40 SuiDesigner$__Closure_422_40;

typedef struct tagSuiDesigner$__Closure_442_26 SuiDesigner$__Closure_442_26;

typedef struct tagSuiDesigner$__Closure_561_39 SuiDesigner$__Closure_561_39;

typedef struct tagSuiDesigner$__Closure_573_39 SuiDesigner$__Closure_573_39;

typedef struct tagSuiDesigner$__Closure_585_39 SuiDesigner$__Closure_585_39;

typedef struct tagSuiDesigner$__Closure_594_32 SuiDesigner$__Closure_594_32;

typedef struct tagSuiDesigner$__Closure_605_32 SuiDesigner$__Closure_605_32;

typedef struct tagSuiDesigner$__Closure_611_32 SuiDesigner$__Closure_611_32;

typedef struct tagSuiDesigner$__Closure_617_32 SuiDesigner$__Closure_617_32;

typedef struct tagSuiDesigner$__Closure_623_32 SuiDesigner$__Closure_623_32;

typedef struct tagSuiDesigner$__Closure_633_32 SuiDesigner$__Closure_633_32;

typedef struct tagSuiDesigner$__Closure_652_45 SuiDesigner$__Closure_652_45;

typedef struct tagSuiDesigner$__Closure_685_48 SuiDesigner$__Closure_685_48;



struct tagSuiDesigner$__Block_48_15 {
	SuiDesigner$SpriteSheetPlayerView*  self ;
};





struct tagSuiDesigner$__Block_274_15 {
	SuiDesigner$SpriteSheetEditor*  self ;
};





struct tagSuiDesigner$__Block_329_51 {
	SuiDesigner$SpriteSheetEditor*  self ;
};





struct tagSuiDesigner$__Block_364_49 {
	SuiDesigner$SpriteSheetAnim*  anim ;
	SuiDesigner$SpriteSheetEditor*  self ;
};





struct tagSuiDesigner$__Block_371_53 {
	SuiDesigner$SpriteSheetEditor*  self ;
};





struct tagSuiDesigner$__Block_385_62 {
	SuiDesigner$SpriteSheetAnim*  anim ;
};





struct tagSuiDesigner$__Block_435_49 {
	SuiDesigner$SpriteSheetEditor*  self ;
};





struct tagSuiDesigner$__Block_551_16 {
	SuiDesigner$SpriteSheetEditor*  self ;
	SuiDesigner$Theme *  t ;
};





struct tagSuiDesigner$__Closure_49_37 {
	void  (*invoke)(SuiDesigner$__Closure_49_37 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_48_15*  __var___Block_48_15 ;
};





struct tagSuiDesigner$__Closure_275_27 {
	void  (*invoke)(SuiDesigner$__Closure_275_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_274_15*  __var___Block_274_15 ;
};





struct tagSuiDesigner$__Closure_283_34 {
	void  (*invoke)(SuiDesigner$__Closure_283_34 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_274_15*  __var___Block_274_15 ;
};





struct tagSuiDesigner$__Closure_291_33 {
	void  (*invoke)(SuiDesigner$__Closure_291_33 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_274_15*  __var___Block_274_15 ;
};





struct tagSuiDesigner$__Closure_336_26 {
	void  (*invoke)(SuiDesigner$__Closure_336_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_329_51*  __var___Block_329_51 ;
};





struct tagSuiDesigner$__Closure_366_51 {
	void  (*invoke)(SuiDesigner$__Closure_366_51 *  self, Orc$String*  newValue);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_364_49*  __var___Block_364_49 ;
};





struct tagSuiDesigner$__Closure_401_44 {
	bool  (*invoke)(SuiDesigner$__Closure_401_44 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_371_53*  __var___Block_371_53 ;
	SuiDesigner$__Block_385_62*  __var___Block_385_62 ;
};





struct tagSuiDesigner$__Closure_onActive_404 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_404 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_371_53*  __var___Block_371_53 ;
	SuiDesigner$__Block_385_62*  __var___Block_385_62 ;
};





struct tagSuiDesigner$__Closure_422_40 {
	void  (*invoke)(SuiDesigner$__Closure_422_40 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_371_53*  __var___Block_371_53 ;
	SuiDesigner$__Block_385_62*  __var___Block_385_62 ;
};





struct tagSuiDesigner$__Closure_442_26 {
	void  (*invoke)(SuiDesigner$__Closure_442_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_435_49*  __var___Block_435_49 ;
};





struct tagSuiDesigner$__Closure_561_39 {
	void  (*invoke)(SuiDesigner$__Closure_561_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_573_39 {
	void  (*invoke)(SuiDesigner$__Closure_573_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_585_39 {
	void  (*invoke)(SuiDesigner$__Closure_585_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_594_32 {
	void  (*invoke)(SuiDesigner$__Closure_594_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_605_32 {
	void  (*invoke)(SuiDesigner$__Closure_605_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_611_32 {
	void  (*invoke)(SuiDesigner$__Closure_611_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_617_32 {
	void  (*invoke)(SuiDesigner$__Closure_617_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_623_32 {
	void  (*invoke)(SuiDesigner$__Closure_623_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_633_32 {
	void  (*invoke)(SuiDesigner$__Closure_633_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_652_45 {
	void  (*invoke)(SuiDesigner$__Closure_652_45 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





struct tagSuiDesigner$__Closure_685_48 {
	SuiCore$ViewBase *  (*invoke)(SuiDesigner$__Closure_685_48 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_551_16*  __var___Block_551_16 ;
};





// static function declaration
static void  __finiBlock___Block_48_15(SuiDesigner$__Block_48_15 *  self);
static void  __finiBlock___Block_274_15(SuiDesigner$__Block_274_15 *  self);
static void  __finiBlock___Block_329_51(SuiDesigner$__Block_329_51 *  self);
static void  __finiBlock___Block_364_49(SuiDesigner$__Block_364_49 *  self);
static void  __finiBlock___Block_371_53(SuiDesigner$__Block_371_53 *  self);
static void  __finiBlock___Block_385_62(SuiDesigner$__Block_385_62 *  self);
static void  __finiBlock___Block_435_49(SuiDesigner$__Block_435_49 *  self);
static void  __finiBlock___Block_551_16(SuiDesigner$__Block_551_16 *  self);
static void  __fn___Closure_49_37(SuiDesigner$__Closure_49_37 *  self);
static void  __fini___Closure_49_37(SuiDesigner$__Closure_49_37 *  self);
static SuiDesigner$__Closure_49_37*  __make___Closure_49_37(SuiDesigner$__Closure_49_37 **  __outRef__, SuiDesigner$__Block_48_15 *  __var___Block_48_15);
static void  __fn___Closure_275_27(SuiDesigner$__Closure_275_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_275_27(SuiDesigner$__Closure_275_27 *  self);
static SuiDesigner$__Closure_275_27*  __make___Closure_275_27(SuiDesigner$__Closure_275_27 **  __outRef__, SuiDesigner$__Block_274_15 *  __var___Block_274_15);
static void  __fn___Closure_283_34(SuiDesigner$__Closure_283_34 *  self, SuiView$Drag *  d);
static void  __fini___Closure_283_34(SuiDesigner$__Closure_283_34 *  self);
static SuiDesigner$__Closure_283_34*  __make___Closure_283_34(SuiDesigner$__Closure_283_34 **  __outRef__, SuiDesigner$__Block_274_15 *  __var___Block_274_15);
static void  __fn___Closure_291_33(SuiDesigner$__Closure_291_33 *  self, SuiView$Drag *  d);
static void  __fini___Closure_291_33(SuiDesigner$__Closure_291_33 *  self);
static SuiDesigner$__Closure_291_33*  __make___Closure_291_33(SuiDesigner$__Closure_291_33 **  __outRef__, SuiDesigner$__Block_274_15 *  __var___Block_274_15);
static void  __fn___Closure_336_26(SuiDesigner$__Closure_336_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_336_26(SuiDesigner$__Closure_336_26 *  self);
static SuiDesigner$__Closure_336_26*  __make___Closure_336_26(SuiDesigner$__Closure_336_26 **  __outRef__, SuiDesigner$__Block_329_51 *  __var___Block_329_51);
static void  __fn___Closure_366_51(SuiDesigner$__Closure_366_51 *  self, Orc$String*  newValue);
static void  __fini___Closure_366_51(SuiDesigner$__Closure_366_51 *  self);
static SuiDesigner$__Closure_366_51*  __make___Closure_366_51(SuiDesigner$__Closure_366_51 **  __outRef__, SuiDesigner$__Block_364_49 *  __var___Block_364_49);
static bool  __fn___Closure_401_44(SuiDesigner$__Closure_401_44 *  self, SuiCore$Event *  e);
static void  __fini___Closure_401_44(SuiDesigner$__Closure_401_44 *  self);
static SuiDesigner$__Closure_401_44*  __make___Closure_401_44(SuiDesigner$__Closure_401_44 **  __outRef__, SuiDesigner$__Block_371_53 *  __var___Block_371_53, SuiDesigner$__Block_385_62 *  __var___Block_385_62);
static void  __fn___Closure_onActive_404(SuiDesigner$__Closure_onActive_404 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_404(SuiDesigner$__Closure_onActive_404 *  self);
static SuiDesigner$__Closure_onActive_404*  __make___Closure_onActive_404(SuiDesigner$__Closure_onActive_404 **  __outRef__, SuiDesigner$__Block_371_53 *  __var___Block_371_53, SuiDesigner$__Block_385_62 *  __var___Block_385_62);
static void  __fn___Closure_422_40(SuiDesigner$__Closure_422_40 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_422_40(SuiDesigner$__Closure_422_40 *  self);
static SuiDesigner$__Closure_422_40*  __make___Closure_422_40(SuiDesigner$__Closure_422_40 **  __outRef__, SuiDesigner$__Block_371_53 *  __var___Block_371_53, SuiDesigner$__Block_385_62 *  __var___Block_385_62);
static void  __fn___Closure_442_26(SuiDesigner$__Closure_442_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_442_26(SuiDesigner$__Closure_442_26 *  self);
static SuiDesigner$__Closure_442_26*  __make___Closure_442_26(SuiDesigner$__Closure_442_26 **  __outRef__, SuiDesigner$__Block_435_49 *  __var___Block_435_49);
static void  __fn___Closure_561_39(SuiDesigner$__Closure_561_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_561_39(SuiDesigner$__Closure_561_39 *  self);
static SuiDesigner$__Closure_561_39*  __make___Closure_561_39(SuiDesigner$__Closure_561_39 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_573_39(SuiDesigner$__Closure_573_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_573_39(SuiDesigner$__Closure_573_39 *  self);
static SuiDesigner$__Closure_573_39*  __make___Closure_573_39(SuiDesigner$__Closure_573_39 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_585_39(SuiDesigner$__Closure_585_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_585_39(SuiDesigner$__Closure_585_39 *  self);
static SuiDesigner$__Closure_585_39*  __make___Closure_585_39(SuiDesigner$__Closure_585_39 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_594_32(SuiDesigner$__Closure_594_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_594_32(SuiDesigner$__Closure_594_32 *  self);
static SuiDesigner$__Closure_594_32*  __make___Closure_594_32(SuiDesigner$__Closure_594_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_605_32(SuiDesigner$__Closure_605_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_605_32(SuiDesigner$__Closure_605_32 *  self);
static SuiDesigner$__Closure_605_32*  __make___Closure_605_32(SuiDesigner$__Closure_605_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_611_32(SuiDesigner$__Closure_611_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_611_32(SuiDesigner$__Closure_611_32 *  self);
static SuiDesigner$__Closure_611_32*  __make___Closure_611_32(SuiDesigner$__Closure_611_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_617_32(SuiDesigner$__Closure_617_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_617_32(SuiDesigner$__Closure_617_32 *  self);
static SuiDesigner$__Closure_617_32*  __make___Closure_617_32(SuiDesigner$__Closure_617_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_623_32(SuiDesigner$__Closure_623_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_623_32(SuiDesigner$__Closure_623_32 *  self);
static SuiDesigner$__Closure_623_32*  __make___Closure_623_32(SuiDesigner$__Closure_623_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_633_32(SuiDesigner$__Closure_633_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_633_32(SuiDesigner$__Closure_633_32 *  self);
static SuiDesigner$__Closure_633_32*  __make___Closure_633_32(SuiDesigner$__Closure_633_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static void  __fn___Closure_652_45(SuiDesigner$__Closure_652_45 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
static void  __fini___Closure_652_45(SuiDesigner$__Closure_652_45 *  self);
static SuiDesigner$__Closure_652_45*  __make___Closure_652_45(SuiDesigner$__Closure_652_45 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);
static SuiCore$ViewBase *  __fn___Closure_685_48(SuiDesigner$__Closure_685_48 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
static void  __fini___Closure_685_48(SuiDesigner$__Closure_685_48 *  self);
static SuiDesigner$__Closure_685_48*  __make___Closure_685_48(SuiDesigner$__Closure_685_48 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16);


static URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  dockLayoutIns = NULL;

//vtable instance
Vtable_SuiDesigner$SpriteSheetPlayerView _vtable_SuiDesigner$SpriteSheetPlayerView;

// init meta

void SuiDesigner$SpriteSheetPlayerView_initMeta(Vtable_SuiDesigner$SpriteSheetPlayerView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "coordIndex", OrcMetaType_int, offsetof(SuiDesigner$SpriteSheetPlayerView, coordIndex), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "timer", ((Vtable_Object*)Vtable_SuiCore$Timer_init(0)), offsetof(SuiDesigner$SpriteSheetPlayerView, timer), true, false, 1);
	orc_metaField_class(&pNext, "_img", ((Vtable_Object*)Vtable_SuiCore$Image_init(0)), offsetof(SuiDesigner$SpriteSheetPlayerView, _img), true, false, 1);
	orc_metaField_class(&pNext, "src", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$SpriteSheetPlayerView, src), true, false, 1);
	orc_metaField_class(&pNext, "animName", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$SpriteSheetPlayerView, animName), true, false, 1);
	orc_metaField_class(&pNext, "_anim", ((Vtable_Object*)Vtable_SuiDesigner$SpriteSheetAnim_init(0)), offsetof(SuiDesigner$SpriteSheetPlayerView, _anim), true, false, 1);
	orc_metaField_class(&pNext, "info", ((Vtable_Object*)Vtable_SuiDesigner$SpriteSheetInfo_init(0)), offsetof(SuiDesigner$SpriteSheetPlayerView, info), true, false, 1);

	orc_metaField_method(&pNext, "setSrc", offsetof(SuiDesigner$SpriteSheetPlayerView, setSrc));
	orc_metaField_method(&pNext, "_isImageValid", offsetof(SuiDesigner$SpriteSheetPlayerView, _isImageValid));
	orc_metaField_method(&pNext, "updateAnim", offsetof(SuiDesigner$SpriteSheetPlayerView, updateAnim));
	orc_metaField_method(&pNext, "setAnimName", offsetof(SuiDesigner$SpriteSheetPlayerView, setAnimName));
}


// vtable init


Vtable_SuiDesigner$SpriteSheetPlayerView* Vtable_SuiDesigner$SpriteSheetPlayerView_init(Vtable_SuiDesigner$SpriteSheetPlayerView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SpriteSheetPlayerView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$View_init(&_vtable_SuiCore$View);

	// init by super vtable init function
    Vtable_SuiCore$View_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$View;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SpriteSheetPlayerView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SpriteSheetPlayerView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SpriteSheetPlayerView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SpriteSheetPlayerView_fini(SuiDesigner$SpriteSheetPlayerView *self){
	//super fini
    SuiCore$View_fini((SuiCore$View *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->timer);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->_img);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->src);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->animName);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->_anim);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->info);

}

// init fields function


void SuiDesigner$SpriteSheetPlayerView_init_fields(SuiDesigner$SpriteSheetPlayerView *self){
	//super class
    SuiCore$View_init_fields((SuiCore$View*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SpriteSheetPlayerView_fini;
	//fields
    {
	((SuiDesigner$SpriteSheetPlayerView*)self)->coordIndex = 0;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->timer, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->_img, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->src, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->animName, Orc$str(&tmpReturn_2, "") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->_anim, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetPlayerView*)self)->info, NULL);
    }
	((Object*)self)->ctor = (void*)SuiDesigner$SpriteSheetPlayerView$ctor;
	((SuiCore$Node*)self)->onMounted = (void*)SuiDesigner$SpriteSheetPlayerView$onMounted;
	((SuiCore$Node*)self)->onUnmounting = (void*)SuiDesigner$SpriteSheetPlayerView$onUnmounting;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiDesigner$SpriteSheetPlayerView$draw_self;
	((SuiDesigner$SpriteSheetPlayerView*)self)->setSrc = (void*)SuiDesigner$SpriteSheetPlayerView$setSrc;
	((SuiDesigner$SpriteSheetPlayerView*)self)->_isImageValid = (void*)SuiDesigner$SpriteSheetPlayerView$_isImageValid;
	((SuiDesigner$SpriteSheetPlayerView*)self)->updateAnim = (void*)SuiDesigner$SpriteSheetPlayerView$updateAnim;
	((SuiDesigner$SpriteSheetPlayerView*)self)->setAnimName = (void*)SuiDesigner$SpriteSheetPlayerView$setAnimName;
}

// init function

void SuiDesigner$SpriteSheetPlayerView_init(SuiDesigner$SpriteSheetPlayerView *self, void *pOwner){
    Vtable_SuiDesigner$SpriteSheetPlayerView_init(&_vtable_SuiDesigner$SpriteSheetPlayerView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SpriteSheetPlayerView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SpriteSheetPlayerView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SpriteSheetPlayerView * SuiDesigner$SpriteSheetPlayerView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SpriteSheetPlayerView *self = calloc(1, sizeof(SuiDesigner$SpriteSheetPlayerView));
	
    SuiDesigner$SpriteSheetPlayerView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SpriteSheetPlayerView$ctor(SuiDesigner$SpriteSheetPlayerView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_48_15*  __var___Block_48_15 = (__var___Block_48_15=NULL,urgc_init_var((void**)&__var___Block_48_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_48_15) , __finiBlock___Block_48_15) ));
	urgc_set_field_class(__var___Block_48_15, (void * )offsetof(SuiDesigner$__Block_48_15, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_49_37*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, timer) , SuiCore$mkTimerInterval(&tmpReturn_1, __make___Closure_49_37(&tmpReturn_2, __var___Block_48_15) , 100) ) ;
}


void  SuiDesigner$SpriteSheetPlayerView$onMounted(SuiDesigner$SpriteSheetPlayerView *  self){
	SuiCore$Node$onMounted(self) ;
}


void  SuiDesigner$SpriteSheetPlayerView$onUnmounting(SuiDesigner$SpriteSheetPlayerView *  self){
	SuiCore$Node$onUnmounting(self) ;
	self->timer->cancel(self->timer) ;
}


void  SuiDesigner$SpriteSheetPlayerView$draw_self(SuiDesigner$SpriteSheetPlayerView *  self, SuiCore$Canvas *  canvas){
	SuiCore$View$draw_self(self, canvas) ;
	if (self->info && self->_anim && self->_anim->coords->size(self->_anim->coords)  > 0 && self->_isImageValid(self) ) {
		int  w = self->_img->width(self->_img) ;
		int  h = self->_img->height(self->_img) ;
		int  rowh = h / self->info->rows;
		int  colw = w / self->info->cols;
		self->coordIndex = self->coordIndex % self->_anim->coords->size(self->_anim->coords) ;
		SuiDesigner$SpriteSheetFrameCoord *  coord = (SuiDesigner$SpriteSheetFrameCoord * )self->_anim->coords->get(self->_anim->coords, self->coordIndex) ;
		int  x = coord->x * colw;
		int  y = coord->y * rowh;
		SuiView$drawImage_atRect(canvas, self->_img, x, y, colw, rowh, 0, 0, colw, rowh) ;
		SuiCore$Canvas$fill(canvas) ;
	}
}


void  SuiDesigner$SpriteSheetPlayerView$setSrc(SuiDesigner$SpriteSheetPlayerView *  self, Orc$String*  src){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(src);

	if (self->src && src && Orc$String$equals(self->src, src->str) ) {
		return ; 
	}
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, src) , src) ;
	if (src) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, _img) , SuiCore$loadImage(&tmpReturn_1, src->str) ) ;
	}
	else {
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, _img) , NULL) ;
	}
}


bool  SuiDesigner$SpriteSheetPlayerView$_isImageValid(SuiDesigner$SpriteSheetPlayerView *  self){
	return self->_img != NULL; 
}


void  SuiDesigner$SpriteSheetPlayerView$updateAnim(SuiDesigner$SpriteSheetPlayerView *  self){
	if (self->info) {
		if (Orc$String$empty(self->animName) ) {
			if (self->_anim != NULL) {
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, _anim) , NULL) ;
			}
			return ; 
		}
		if (self->_anim == NULL || !Orc$String$equals(self->animName, self->_anim->name->str) ) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$SpriteSheetAnim*  tmpReturn_1 = NULL;
			urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, _anim) , self->info->getAnimByName(&tmpReturn_1, self->info, self->animName->str) ) ;
		}
	}
	else {
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, _anim) , NULL) ;
	}
}


void  SuiDesigner$SpriteSheetPlayerView$setAnimName(SuiDesigner$SpriteSheetPlayerView *  self, Orc$String*  animName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(animName);

	if (self->animName && animName && Orc$String$equals(animName, self->animName->str) ) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, animName) , animName == NULL ? Orc$str(&tmpReturn_1, "")  : animName) ;
	self->updateAnim(self) ;
}



SuiDesigner$SpriteSheetPlayerView*  SuiDesigner$mkSpriteSheetPlayerView(SuiDesigner$SpriteSheetPlayerView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$SpriteSheetPlayerView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_SuiDesigner$SpriteSheetPlayerView_init(NULL)) ) ; 
}


//vtable instance
Vtable_SuiDesigner$SpriteSheetFrameCoord _vtable_SuiDesigner$SpriteSheetFrameCoord;

// init meta

void SuiDesigner$SpriteSheetFrameCoord_initMeta(Vtable_SuiDesigner$SpriteSheetFrameCoord *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "x", OrcMetaType_int, offsetof(SuiDesigner$SpriteSheetFrameCoord, x), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "y", OrcMetaType_int, offsetof(SuiDesigner$SpriteSheetFrameCoord, y), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$SpriteSheetFrameCoord, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$SpriteSheetFrameCoord, toJson));
}


// vtable init


Vtable_SuiDesigner$SpriteSheetFrameCoord* Vtable_SuiDesigner$SpriteSheetFrameCoord_init(Vtable_SuiDesigner$SpriteSheetFrameCoord* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SpriteSheetFrameCoord;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SpriteSheetFrameCoord_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SpriteSheetFrameCoord";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SpriteSheetFrameCoord_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$SpriteSheetFrameCoord_fini(SuiDesigner$SpriteSheetFrameCoord *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$SpriteSheetFrameCoord_init_fields(SuiDesigner$SpriteSheetFrameCoord *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SpriteSheetFrameCoord_fini;
	//fields
    {
	((SuiDesigner$SpriteSheetFrameCoord*)self)->x = 0;
	((SuiDesigner$SpriteSheetFrameCoord*)self)->y = 0;
    }
	((SuiDesigner$SpriteSheetFrameCoord*)self)->fromJson = (void*)SuiDesigner$SpriteSheetFrameCoord$fromJson;
	((SuiDesigner$SpriteSheetFrameCoord*)self)->toJson = (void*)SuiDesigner$SpriteSheetFrameCoord$toJson;
}

// init function

void SuiDesigner$SpriteSheetFrameCoord_init(SuiDesigner$SpriteSheetFrameCoord *self, void *pOwner){
    Vtable_SuiDesigner$SpriteSheetFrameCoord_init(&_vtable_SuiDesigner$SpriteSheetFrameCoord);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SpriteSheetFrameCoord;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SpriteSheetFrameCoord_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SpriteSheetFrameCoord * SuiDesigner$SpriteSheetFrameCoord_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SpriteSheetFrameCoord *self = calloc(1, sizeof(SuiDesigner$SpriteSheetFrameCoord));
	
    SuiDesigner$SpriteSheetFrameCoord_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SpriteSheetFrameCoord$fromJson(SuiDesigner$SpriteSheetFrameCoord *  self, Json$Json *  jo){
	self->x = jo->getInt(jo, "x") ;
	self->y = jo->getInt(jo, "y") ;
}


void  SuiDesigner$SpriteSheetFrameCoord$toJson(SuiDesigner$SpriteSheetFrameCoord *  self, Json$Json *  jo){
	jo->putNumber(jo, "x", self->x) ;
	jo->putNumber(jo, "y", self->y) ;
}




//vtable instance
Vtable_SuiDesigner$SpriteSheetAnim _vtable_SuiDesigner$SpriteSheetAnim;

// init meta

void SuiDesigner$SpriteSheetAnim_initMeta(Vtable_SuiDesigner$SpriteSheetAnim *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$SpriteSheetAnim, name), true, false, 1);
	orc_metaField_class(&pNext, "coords", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$SpriteSheetAnim, coords), true, false, 1);

	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$SpriteSheetAnim, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$SpriteSheetAnim, toJson));
	orc_metaField_method(&pNext, "getIndexOfFrame", offsetof(SuiDesigner$SpriteSheetAnim, getIndexOfFrame));
	orc_metaField_method(&pNext, "addFrame", offsetof(SuiDesigner$SpriteSheetAnim, addFrame));
	orc_metaField_method(&pNext, "removeFrame", offsetof(SuiDesigner$SpriteSheetAnim, removeFrame));
}


// vtable init


Vtable_SuiDesigner$SpriteSheetAnim* Vtable_SuiDesigner$SpriteSheetAnim_init(Vtable_SuiDesigner$SpriteSheetAnim* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SpriteSheetAnim;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SpriteSheetAnim_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SpriteSheetAnim";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SpriteSheetAnim_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SpriteSheetAnim_fini(SuiDesigner$SpriteSheetAnim *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetAnim*)self)->name);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetAnim*)self)->coords);

}

// init fields function


void SuiDesigner$SpriteSheetAnim_init_fields(SuiDesigner$SpriteSheetAnim *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SpriteSheetAnim_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetAnim*)self)->name, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetAnim*)self)->coords, Orc$List_new(&tmpNewOwner_2) );
    }
	((SuiDesigner$SpriteSheetAnim*)self)->fromJson = (void*)SuiDesigner$SpriteSheetAnim$fromJson;
	((SuiDesigner$SpriteSheetAnim*)self)->toJson = (void*)SuiDesigner$SpriteSheetAnim$toJson;
	((SuiDesigner$SpriteSheetAnim*)self)->getIndexOfFrame = (void*)SuiDesigner$SpriteSheetAnim$getIndexOfFrame;
	((SuiDesigner$SpriteSheetAnim*)self)->addFrame = (void*)SuiDesigner$SpriteSheetAnim$addFrame;
	((SuiDesigner$SpriteSheetAnim*)self)->removeFrame = (void*)SuiDesigner$SpriteSheetAnim$removeFrame;
}

// init function

void SuiDesigner$SpriteSheetAnim_init(SuiDesigner$SpriteSheetAnim *self, void *pOwner){
    Vtable_SuiDesigner$SpriteSheetAnim_init(&_vtable_SuiDesigner$SpriteSheetAnim);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SpriteSheetAnim;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SpriteSheetAnim_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SpriteSheetAnim * SuiDesigner$SpriteSheetAnim_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SpriteSheetAnim *self = calloc(1, sizeof(SuiDesigner$SpriteSheetAnim));
	
    SuiDesigner$SpriteSheetAnim_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SpriteSheetAnim$fromJson(SuiDesigner$SpriteSheetAnim *  self, Json$Json *  jo){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetAnim, name) , jo->getString(&tmpReturn_1, jo, "name") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetAnim, coords) , jo->getObjectsByVtable(&tmpReturn_2, jo, "coords", Vtable_SuiDesigner$SpriteSheetFrameCoord_init(NULL)) ) ;
}


void  SuiDesigner$SpriteSheetAnim$toJson(SuiDesigner$SpriteSheetAnim *  self, Json$Json *  jo){
	jo->putString(jo, "name", self->name) ;
	jo->putObject(jo, "coords", self->coords) ;
}


int  SuiDesigner$SpriteSheetAnim$getIndexOfFrame(SuiDesigner$SpriteSheetAnim *  self, int  x, int  y){
	for (int  i = 0; i < self->coords->size(self->coords) ; i++) {
		SuiDesigner$SpriteSheetFrameCoord *  e = (SuiDesigner$SpriteSheetFrameCoord * )self->coords->get(self->coords, i) ;
		if (e->x == x && e->y == y) {
			return i; 
		}
	}
	return -1; 
}


void  SuiDesigner$SpriteSheetAnim$addFrame(SuiDesigner$SpriteSheetAnim *  self, int  x, int  y){
	int  idx = self->getIndexOfFrame(self, x, y) ;
	if (idx == -1) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SpriteSheetFrameCoord*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner$SpriteSheetFrameCoord_new(&e) ));
		e->x = x;
		e->y = y;
		self->coords->add(self->coords, e) ;
	}
}


void  SuiDesigner$SpriteSheetAnim$removeFrame(SuiDesigner$SpriteSheetAnim *  self, int  x, int  y){
	for (int  i = 0; i < self->coords->size(self->coords) ; i++) {
		SuiDesigner$SpriteSheetFrameCoord *  e = (SuiDesigner$SpriteSheetFrameCoord * )self->coords->get(self->coords, i) ;
		if (e->x == x && e->y == y) {
			self->coords->removeAt(self->coords, i) ;
			i--;
		}
	}
}




//vtable instance
Vtable_SuiDesigner$SpriteSheetInfo _vtable_SuiDesigner$SpriteSheetInfo;

// init meta

void SuiDesigner$SpriteSheetInfo_initMeta(Vtable_SuiDesigner$SpriteSheetInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "fps", OrcMetaType_float, offsetof(SuiDesigner$SpriteSheetInfo, fps), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "rows", OrcMetaType_int, offsetof(SuiDesigner$SpriteSheetInfo, rows), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "cols", OrcMetaType_int, offsetof(SuiDesigner$SpriteSheetInfo, cols), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "anims", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$SpriteSheetInfo, anims), true, false, 1);

	orc_metaField_method(&pNext, "getAnimByName", offsetof(SuiDesigner$SpriteSheetInfo, getAnimByName));
	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$SpriteSheetInfo, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$SpriteSheetInfo, toJson));
}


// vtable init


Vtable_SuiDesigner$SpriteSheetInfo* Vtable_SuiDesigner$SpriteSheetInfo_init(Vtable_SuiDesigner$SpriteSheetInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SpriteSheetInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SpriteSheetInfo_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SpriteSheetInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SpriteSheetInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SpriteSheetInfo_fini(SuiDesigner$SpriteSheetInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetInfo*)self)->anims);

}

// init fields function


void SuiDesigner$SpriteSheetInfo_init_fields(SuiDesigner$SpriteSheetInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SpriteSheetInfo_fini;
	//fields
    {
	((SuiDesigner$SpriteSheetInfo*)self)->fps = 10;
	((SuiDesigner$SpriteSheetInfo*)self)->rows = 9;
	((SuiDesigner$SpriteSheetInfo*)self)->cols = 8;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetInfo*)self)->anims, Orc$List_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$SpriteSheetInfo*)self)->getAnimByName = (void*)SuiDesigner$SpriteSheetInfo$getAnimByName;
	((SuiDesigner$SpriteSheetInfo*)self)->fromJson = (void*)SuiDesigner$SpriteSheetInfo$fromJson;
	((SuiDesigner$SpriteSheetInfo*)self)->toJson = (void*)SuiDesigner$SpriteSheetInfo$toJson;
}

// init function

void SuiDesigner$SpriteSheetInfo_init(SuiDesigner$SpriteSheetInfo *self, void *pOwner){
    Vtable_SuiDesigner$SpriteSheetInfo_init(&_vtable_SuiDesigner$SpriteSheetInfo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SpriteSheetInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SpriteSheetInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SpriteSheetInfo * SuiDesigner$SpriteSheetInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SpriteSheetInfo *self = calloc(1, sizeof(SuiDesigner$SpriteSheetInfo));
	
    SuiDesigner$SpriteSheetInfo_init(self, pOwner);
    return self;
}


// class members
SuiDesigner$SpriteSheetAnim*  SuiDesigner$SpriteSheetInfo$getAnimByName(SuiDesigner$SpriteSheetAnim **  __outRef__, SuiDesigner$SpriteSheetInfo *  self, const char *  name){
	for (int  i = 0; i < self->anims->size(self->anims) ; i++) {
		SuiDesigner$SpriteSheetAnim *  anim = (SuiDesigner$SpriteSheetAnim * )self->anims->get(self->anims, i) ;
		if (Orc$String$equals(anim->name, name) ) {
			return urgc_set_var_for_return_class((void ** )__outRef__, anim) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


void  SuiDesigner$SpriteSheetInfo$fromJson(SuiDesigner$SpriteSheetInfo *  self, Json$Json *  jo){
	self->fps = jo->getNumber(jo, "fps") ;
	self->rows = jo->getInt(jo, "rows") ;
	self->cols = jo->getInt(jo, "cols") ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetInfo, anims) , jo->getObjectsByVtable(&tmpReturn_1, jo, "anims", Vtable_SuiDesigner$SpriteSheetAnim_init(NULL)) ) ;
}


void  SuiDesigner$SpriteSheetInfo$toJson(SuiDesigner$SpriteSheetInfo *  self, Json$Json *  jo){
	jo->putNumber(jo, "fps", self->fps) ;
	jo->putNumber(jo, "rows", self->rows) ;
	jo->putNumber(jo, "cols", self->cols) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	jo->put(jo, "anims", Json$Json_toJson(&tmpReturn_1, self->anims) ) ;
}




//vtable instance
Vtable_SuiDesigner$SpriteSheetEditor _vtable_SuiDesigner$SpriteSheetEditor;

// init meta

void SuiDesigner$SpriteSheetEditor_initMeta(Vtable_SuiDesigner$SpriteSheetEditor *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, win), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, drag), true, false, 1);
	orc_metaField_class(&pNext, "dragPreview", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, dragPreview), true, false, 1);
	orc_metaField_class(&pNext, "dragChoose", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, dragChoose), true, false, 1);
	orc_metaField_class(&pNext, "imgCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, imgCell), true, false, 1);
	orc_metaField_class(&pNext, "previewCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, previewCell), true, false, 1);
	orc_metaField_class(&pNext, "invalidReact", ((Vtable_Object*)Vtable_SuiDesigner$InvalidReact_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, invalidReact), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, path), true, false, 1);
	orc_metaField_class(&pNext, "info", ((Vtable_Object*)Vtable_SuiDesigner$SpriteSheetInfo_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, info), true, false, 1);
	orc_metaField_class(&pNext, "curAnim", ((Vtable_Object*)Vtable_SuiDesigner$SpriteSheetAnim_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, curAnim), true, false, 1);
	orc_metaField_class(&pNext, "sceneImageView", ((Vtable_Object*)Vtable_SuiView$ImageView_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, sceneImageView), true, false, 1);
	orc_metaField_class(&pNext, "playerView", ((Vtable_Object*)Vtable_SuiDesigner$SpriteSheetPlayerView_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, playerView), true, false, 1);
	orc_metaField_class(&pNext, "chessBg", ((Vtable_Object*)Vtable_SuiDesigner$ChessBgViewCallback_init(0)), offsetof(SuiDesigner$SpriteSheetEditor, chessBg), true, false, 1);

	orc_metaField_method(&pNext, "printSceneTree", offsetof(SuiDesigner$SpriteSheetEditor, printSceneTree));
	orc_metaField_method(&pNext, "getFrameIndex", offsetof(SuiDesigner$SpriteSheetEditor, getFrameIndex));
	orc_metaField_method(&pNext, "removeCurAnim", offsetof(SuiDesigner$SpriteSheetEditor, removeCurAnim));
	orc_metaField_method(&pNext, "reactPreview", offsetof(SuiDesigner$SpriteSheetEditor, reactPreview));
	orc_metaField_method(&pNext, "showDialog_rename", offsetof(SuiDesigner$SpriteSheetEditor, showDialog_rename));
	orc_metaField_method(&pNext, "reactAnimNames", offsetof(SuiDesigner$SpriteSheetEditor, reactAnimNames));
	orc_metaField_method(&pNext, "reactScene", offsetof(SuiDesigner$SpriteSheetEditor, reactScene));
	orc_metaField_method(&pNext, "react", offsetof(SuiDesigner$SpriteSheetEditor, react));
	orc_metaField_method(&pNext, "playCurAnim", offsetof(SuiDesigner$SpriteSheetEditor, playCurAnim));
	orc_metaField_method(&pNext, "showWindow", offsetof(SuiDesigner$SpriteSheetEditor, showWindow));
}


// vtable init


Vtable_SuiDesigner$SpriteSheetEditor* Vtable_SuiDesigner$SpriteSheetEditor_init(Vtable_SuiDesigner$SpriteSheetEditor* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SpriteSheetEditor;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SpriteSheetEditor_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SpriteSheetEditor";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SpriteSheetEditor_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SpriteSheetEditor_fini(SuiDesigner$SpriteSheetEditor *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->win);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->dragPreview);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->dragChoose);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->imgCell);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->previewCell);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->invalidReact);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->path);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->info);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->curAnim);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->sceneImageView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->playerView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->chessBg);

}

// init fields function


void SuiDesigner$SpriteSheetEditor_init_fields(SuiDesigner$SpriteSheetEditor *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SpriteSheetEditor_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->win, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->dragPreview, SuiView$Drag_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->dragChoose, SuiView$Drag_new(&tmpNewOwner_3) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->imgCell, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->previewCell, NULL);
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InvalidReact*  tmpReturn_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->invalidReact, SuiDesigner$mkInvalidReact(&tmpReturn_4, self) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->path, Orc$str(&tmpReturn_5, "a.spriteSheet.json") );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SpriteSheetInfo*  tmpNewOwner_6 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->info, SuiDesigner$SpriteSheetInfo_new(&tmpNewOwner_6) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->curAnim, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->sceneImageView, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->playerView, NULL);
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ChessBgViewCallback*  tmpNewOwner_7 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SpriteSheetEditor*)self)->chessBg, SuiDesigner$ChessBgViewCallback_new(&tmpNewOwner_7) );
    }
	((SuiDesigner$SpriteSheetEditor*)self)->printSceneTree = (void*)SuiDesigner$SpriteSheetEditor$printSceneTree;
	((SuiDesigner$SpriteSheetEditor*)self)->getFrameIndex = (void*)SuiDesigner$SpriteSheetEditor$getFrameIndex;
	((Object*)self)->ctor = (void*)SuiDesigner$SpriteSheetEditor$ctor;
	((SuiDesigner$SpriteSheetEditor*)self)->removeCurAnim = (void*)SuiDesigner$SpriteSheetEditor$removeCurAnim;
	((SuiDesigner$SpriteSheetEditor*)self)->reactPreview = (void*)SuiDesigner$SpriteSheetEditor$reactPreview;
	((SuiDesigner$SpriteSheetEditor*)self)->showDialog_rename = (void*)SuiDesigner$SpriteSheetEditor$showDialog_rename;
	((SuiDesigner$SpriteSheetEditor*)self)->reactAnimNames = (void*)SuiDesigner$SpriteSheetEditor$reactAnimNames;
	((SuiDesigner$SpriteSheetEditor*)self)->reactScene = (void*)SuiDesigner$SpriteSheetEditor$reactScene;
	((SuiDesigner$SpriteSheetEditor*)self)->react = (void*)SuiDesigner$SpriteSheetEditor$react;
	((SuiDesigner$SpriteSheetEditor*)self)->playCurAnim = (void*)SuiDesigner$SpriteSheetEditor$playCurAnim;
	((SuiDesigner$SpriteSheetEditor*)self)->showWindow = (void*)SuiDesigner$SpriteSheetEditor$showWindow;
}

// init function

void SuiDesigner$SpriteSheetEditor_init(SuiDesigner$SpriteSheetEditor *self, void *pOwner){
    Vtable_SuiDesigner$SpriteSheetEditor_init(&_vtable_SuiDesigner$SpriteSheetEditor);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SpriteSheetEditor;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SpriteSheetEditor_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SpriteSheetEditor * SuiDesigner$SpriteSheetEditor_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SpriteSheetEditor *self = calloc(1, sizeof(SuiDesigner$SpriteSheetEditor));
	
    SuiDesigner$SpriteSheetEditor_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SpriteSheetEditor$printSceneTree(SuiDesigner$SpriteSheetEditor *  self){
	SuiCore$printNodeTree(self->sceneImageView, 0) ;
}


int  SuiDesigner$SpriteSheetEditor$getFrameIndex(SuiDesigner$SpriteSheetEditor *  self, int  x, int  y){
	if (self->curAnim) {
		int  idx = self->curAnim->getIndexOfFrame(self->curAnim, x, y) ;
		return idx; 
	}
	return -1; 
}


void  SuiDesigner$SpriteSheetEditor$ctor(SuiDesigner$SpriteSheetEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_274_15*  __var___Block_274_15 = (__var___Block_274_15=NULL,urgc_init_var((void**)&__var___Block_274_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_274_15) , __finiBlock___Block_274_15) ));
	urgc_set_field_class(__var___Block_274_15, (void * )offsetof(SuiDesigner$__Block_274_15, self) , self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_275_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_275_27(&tmpReturn_1, __var___Block_274_15) ) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_283_34*  tmpReturn_2 = NULL;
	urgc_set_field(self->dragPreview, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_283_34(&tmpReturn_2, __var___Block_274_15) ) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_291_33*  tmpReturn_3 = NULL;
	urgc_set_field(self->dragChoose, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_291_33(&tmpReturn_3, __var___Block_274_15) ) ;
}


void  SuiDesigner$SpriteSheetEditor$removeCurAnim(SuiDesigner$SpriteSheetEditor *  self){
	if (self->curAnim) {
		int  index = self->info->anims->indexOf(self->info->anims, self->curAnim) ;
		self->info->anims->remove(self->info->anims, self->curAnim) ;
		index = Orc$minInt(index, self->info->anims->size(self->info->anims)  - 1) ;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, curAnim) , self->info->anims->get(self->info->anims, index) ) ;
		self->invalidReact->invalid(self->invalidReact) ;
	}
}


SuiCore$ViewBase *  SuiDesigner$SpriteSheetEditor$reactPreview(SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_329_51*  __var___Block_329_51 = (__var___Block_329_51=NULL,urgc_init_var((void**)&__var___Block_329_51, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_329_51) , __finiBlock___Block_329_51) ));
	urgc_set_field_class(__var___Block_329_51, (void * )offsetof(SuiDesigner$__Block_329_51, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_330_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_330_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_330_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->chessBg) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_336_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_336_26(&tmpReturn_2, __var___Block_329_51) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SpriteSheetPlayerView*  tmpReturn_4 = NULL;
		{
			SuiDesigner$SpriteSheetPlayerView*  __scopeVar_348_12 = SuiDesigner$mkSpriteSheetPlayerView(&tmpReturn_4, o, 0) , *o = __scopeVar_348_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_348_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			o->setSrc(o, Orc$str(&tmpReturn_5, "../asset/AnimationSheet_Character.png") ) ;
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$SpriteSheetPlayerView, info) , self->info) ;
			o->setAnimName(o, self->curAnim ? self->curAnim->name : NULL) ;
			urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, playerView) , o) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_6 = NULL;
			{
				SuiLayout$LayoutAlignPositionCell*  __scopeVar_355_16 = SuiLayout$layoutAlignPositionCell(&tmpReturn_6, o, 0) , *o = __scopeVar_355_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_355_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, previewCell) , o) ;
			}
		}
		return o; 
	}
}


void  SuiDesigner$SpriteSheetEditor$showDialog_rename(SuiDesigner$SpriteSheetEditor *  self, SuiDesigner$SpriteSheetAnim*  anim){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anim);

	URGC_VAR_CLEANUP SuiDesigner$__Block_364_49*  __var___Block_364_49 = (__var___Block_364_49=NULL,urgc_init_var((void**)&__var___Block_364_49, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_364_49) , __finiBlock___Block_364_49) ));
	urgc_set_field_class(__var___Block_364_49, (void * )offsetof(SuiDesigner$__Block_364_49, self) , self) ;
	urgc_set_field_class(__var___Block_364_49, (void * )offsetof(SuiDesigner$__Block_364_49, anim) , anim) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_366_51*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt(__var___Block_364_49->anim->name->str, "重命名", __make___Closure_366_51(&tmpReturn_1, __var___Block_364_49) ) ;
}


SuiCore$ViewBase *  SuiDesigner$SpriteSheetEditor$reactAnimNames(SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_371_53*  __var___Block_371_53 = (__var___Block_371_53=NULL,urgc_init_var((void**)&__var___Block_371_53, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_371_53) , __finiBlock___Block_371_53) ));
	urgc_set_field_class(__var___Block_371_53, (void * )offsetof(SuiDesigner$__Block_371_53, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_1 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_372_8 = SuiView$mkScrollArea(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_372_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_372_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMinWidthConstraint = true;
		Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "stretch") ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_380_12 = SuiLayout$layoutLinear(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_380_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_380_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "maxOrStretch") ;
			((SuiCore$View * )o)->backgroundColor = 0x33ffff00;
			for (int  i = 0; i < self->info->anims->size(self->info->anims) ; i++) {
				URGC_VAR_CLEANUP SuiDesigner$__Block_385_62*  __var___Block_385_62 = (__var___Block_385_62=NULL,urgc_init_var((void**)&__var___Block_385_62, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_385_62) , __finiBlock___Block_385_62) ));
				urgc_set_field_class(__var___Block_385_62, (void * )offsetof(SuiDesigner$__Block_385_62, anim) , (SuiDesigner$SpriteSheetAnim* )self->info->anims->get(self->info->anims, i) ) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
				{
					SuiView$TextView*  __scopeVar_388_20 = SuiView$mkTextView(&tmpReturn_4, o, (long long )__var___Block_385_62->anim) , *o = __scopeVar_388_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_388_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->setText(o, __var___Block_385_62->anim->name) ;
					Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
					URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_5 = NULL;
					{
						SuiView$HoverViewEffect*  __scopeVar_393_24 = SuiView$mkHoverViewEffect(&tmpReturn_5, o, 0) , *o = __scopeVar_393_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_393_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->hoverBorder->setAll(o->hoverBorder, 1, 0x00000000) ;
						o->activeBorder->setAll(o->activeBorder, 1, 0x00000000) ;
						o->backgroundColor = i % 2 == 0 ? 0x00ffff00 : 0x33ffffff;
						o->hoverBackgroundColor = 0x33ff0000;
						o->activeBackgroundColor = 0x66ff0000;
						o->isActive = self->curAnim == __var___Block_385_62->anim;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_401_44*  tmpReturn_6 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onHostEvent) , __make___Closure_401_44(&tmpReturn_6, __var___Block_371_53, __var___Block_385_62) ) ;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_422_40*  tmpReturn_7 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onClick) , __make___Closure_422_40(&tmpReturn_7, __var___Block_371_53, __var___Block_385_62) ) ;
					}
				}
			}
		}
		return o; 
	}
}


SuiCore$ViewBase *  SuiDesigner$SpriteSheetEditor$reactScene(SuiDesigner$SpriteSheetEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_435_49*  __var___Block_435_49 = (__var___Block_435_49=NULL,urgc_init_var((void**)&__var___Block_435_49, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_435_49) , __finiBlock___Block_435_49) ));
	urgc_set_field_class(__var___Block_435_49, (void * )offsetof(SuiDesigner$__Block_435_49, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_436_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_436_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_436_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->chessBg) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_442_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_442_26(&tmpReturn_2, __var___Block_435_49) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) ;
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_4 = NULL;
		{
			SuiView$ImageView*  __scopeVar_458_12 = SuiView$mkImageView(&tmpReturn_4, o, 0) , *o = __scopeVar_458_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_458_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xffff0000) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			o->setSrc(o, Orc$str(&tmpReturn_5, "../asset/AnimationSheet_Character.png") ) ;
			urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, sceneImageView) , o) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_6 = NULL;
			{
				SuiLayout$LayoutAlignPositionCell*  __scopeVar_465_16 = SuiLayout$layoutAlignPositionCell(&tmpReturn_6, o, 0) , *o = __scopeVar_465_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_465_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, imgCell) , o) ;
			}
			int  w = o->_img->width(o->_img) ;
			int  h = o->_img->height(o->_img) ;
			int  rowh = h / self->info->rows;
			int  colw = w / self->info->cols;
			for (int  i = 0; i < self->info->rows; i++) {
				URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_7 = NULL;
				{
					SuiCore$View*  __scopeVar_478_20 = SuiView$mkView(&tmpReturn_7, o, 1000 + i) , *o = __scopeVar_478_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_478_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$String$addi(Orc$str(&tmpReturn_8, "rowLine:") , i) ) ;
					((SuiCore$ViewBase * )o)->frame.y = i * rowh;
					o->backgroundColor = 0xffff0000;
					o->height = 1;
					o->width = w;
				}
			}
			for (int  i = 0; i < self->info->cols; i++) {
				URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_9 = NULL;
				{
					SuiCore$View*  __scopeVar_488_20 = SuiView$mkView(&tmpReturn_9, o, 2000 + i) , *o = __scopeVar_488_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_488_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$String$addi(Orc$str(&tmpReturn_10, "colLine:") , i) ) ;
					((SuiCore$ViewBase * )o)->frame.x = i * colw;
					o->backgroundColor = 0xffff0000;
					o->width = 1;
					o->height = h;
				}
			}
			for (int  y = 0; y < self->info->rows; y++) {
				for (int  x = 0; x < self->info->cols; x++) {
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_11 = NULL;
					{
						SuiCore$View*  __scopeVar_499_24 = SuiView$mkView(&tmpReturn_11, o, 30000 + y * 100 + x) , *o = __scopeVar_499_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_499_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$String$addi(Orc$String$add(Orc$String$addi(Orc$str(&tmpReturn_12, "cell:") , x) , ",") , y) ) ;
						((SuiCore$ViewBase * )o)->frame.x = x * colw;
						((SuiCore$ViewBase * )o)->frame.y = y * rowh;
						o->width = colw;
						o->height = rowh;
						((SuiCore$ViewBase * )o)->frame.width = colw;
						((SuiCore$ViewBase * )o)->frame.height = rowh;
						int  frameIndex = self->getFrameIndex(self, x, y) ;
						URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_13 = NULL;
						{
							SuiView$HoverViewEffect*  __scopeVar_513_28 = SuiView$mkHoverViewEffect(&tmpReturn_13, o, 0) , *o = __scopeVar_513_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_513_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->hoverBorder->setAll(o->hoverBorder, 1, 0x00000000) ;
							o->activeBorder->setAll(o->activeBorder, 1, 0x00000000) ;
							o->backgroundColor = 0x00ff0000;
							o->hoverBackgroundColor = 0x33ff0000;
							o->activeBackgroundColor = 0x66ff0000;
							o->isActive = frameIndex != -1;
						}
						if (frameIndex != -1) {
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_14 = NULL;
							{
								SuiView$TextView*  __scopeVar_527_32 = SuiView$mkTextView(&tmpReturn_14, o, 0) , *o = __scopeVar_527_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_527_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								((SuiCore$ViewBase * )o)->frame.x = 0;
								((SuiCore$ViewBase * )o)->frame.y = 0;
								((SuiCore$View * )o)->width = colw;
								((SuiCore$View * )o)->height = rowh;
								Orc$String$set(o->text_align, "center") ;
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
								o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_15, "") , frameIndex) ) ;
								o->color = 0xffffffff;
								Orc$String$set(((SuiCore$ViewBase * )o)->hitTestType, "none") ;
							}
						}
					}
				}
			}
		}
		return o; 
	}
}


void  SuiDesigner$SpriteSheetEditor$react(SuiDesigner$SpriteSheetEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_551_16*  __var___Block_551_16 = (__var___Block_551_16=NULL,urgc_init_var((void**)&__var___Block_551_16, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_551_16) , __finiBlock___Block_551_16) ));
	urgc_set_field_class(__var___Block_551_16, (void * )offsetof(SuiDesigner$__Block_551_16, self) , self) ;
	printf("react SpriteSheetEditor\n") ;
	__var___Block_551_16->t = SuiDesigner$themeIns() ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_554_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_1, self->win->rootView, 0) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_555_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
			{
				SuiView$TextView*  __scopeVar_556_16 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_556_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_556_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				o->setText(o, Orc$str(&tmpReturn_3, "rows:") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_4 = NULL;
			{
				SuiView$EditText*  __scopeVar_559_16 = SuiView$mkEditText(&tmpReturn_4, o, 0) , *o = __scopeVar_559_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_559_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				o->setValue_notInFocus(o, Orc$String$addi(Orc$str(&tmpReturn_5, "") , self->info->rows) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_561_39*  tmpReturn_6 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_561_39(&tmpReturn_6, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
			{
				SuiView$TextView*  __scopeVar_568_16 = SuiView$mkTextView(&tmpReturn_7, o, 0) , *o = __scopeVar_568_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_568_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
				o->setText(o, Orc$str(&tmpReturn_8, "cols:") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_9 = NULL;
			{
				SuiView$EditText*  __scopeVar_571_16 = SuiView$mkEditText(&tmpReturn_9, o, 0) , *o = __scopeVar_571_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_571_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
				o->setValue_notInFocus(o, Orc$String$addi(Orc$str(&tmpReturn_10, "") , self->info->cols) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_573_39*  tmpReturn_11 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_573_39(&tmpReturn_11, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_12 = NULL;
			{
				SuiView$TextView*  __scopeVar_580_16 = SuiView$mkTextView(&tmpReturn_12, o, 0) , *o = __scopeVar_580_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_580_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
				o->setText(o, Orc$str(&tmpReturn_13, "fps:") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_14 = NULL;
			{
				SuiView$EditText*  __scopeVar_583_16 = SuiView$mkEditText(&tmpReturn_14, o, 0) , *o = __scopeVar_583_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_583_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
				o->setValue_notInFocus(o, Orc$String$addi(Orc$str(&tmpReturn_15, "") , self->info->fps) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_585_39*  tmpReturn_16 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_585_39(&tmpReturn_16, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_17 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_592_16 = SuiView$mkDrawButton(&tmpReturn_17, o, 0) , *o = __scopeVar_592_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_592_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_18, "添加动画") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_594_32*  tmpReturn_19 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_594_32(&tmpReturn_19, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_20 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_602_16 = SuiView$mkDrawButton(&tmpReturn_20, o, 0) , *o = __scopeVar_602_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_602_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_21 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_21, "删除动画") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_605_32*  tmpReturn_22 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_605_32(&tmpReturn_22, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_23 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_609_16 = SuiView$mkDrawButton(&tmpReturn_23, o, 0) , *o = __scopeVar_609_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_609_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_24, "打印树") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_611_32*  tmpReturn_25 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_611_32(&tmpReturn_25, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_26 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_615_16 = SuiView$mkDrawButton(&tmpReturn_26, o, 0) , *o = __scopeVar_615_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_615_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_27 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_27, "播放动画") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_617_32*  tmpReturn_28 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_617_32(&tmpReturn_28, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_29 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_621_16 = SuiView$mkDrawButton(&tmpReturn_29, o, 0) , *o = __scopeVar_621_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_621_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_30, "保存") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_623_32*  tmpReturn_31 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_623_32(&tmpReturn_31, __var___Block_551_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_32 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_631_16 = SuiView$mkDrawButton(&tmpReturn_32, o, 0) , *o = __scopeVar_631_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_631_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_33 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_33, "加载") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_633_32*  tmpReturn_34 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_633_32(&tmpReturn_34, __var___Block_551_16) ) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpReturn_35 = NULL;
		{
			SuiView$DockLayout*  __scopeVar_645_12 = SuiView$dockLayout(&tmpReturn_35, o, 0) , *o = __scopeVar_645_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_645_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_var_class(&dockLayoutIns, o) ;
			((SuiCore$View * )o)->width = 100;
			((SuiCore$View * )o)->height = 20;
			((SuiCore$View * )o)->backgroundColor = 0x30000033;
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP SuiDesigner$__Closure_652_45*  tmpReturn_36 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemHeadView) , __make___Closure_652_45(&tmpReturn_36, __var___Block_551_16) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_685_48*  tmpReturn_37 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemContentView) , __make___Closure_685_48(&tmpReturn_37, __var___Block_551_16) ) ;
				SuiView$DockItem *  root = o->root;
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_38 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_39 = NULL;
				{
					SuiView$DockItem*  o = SuiView$mkDockItem(&tmpReturn_38, root, Orc$str(&tmpReturn_39, "anim-names") ) ;
					
				
					o->intId = 0;
					o->width = 150;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_40 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_41 = NULL;
				{
					SuiView$DockItem*  o = SuiView$mkDockItem(&tmpReturn_40, root, Orc$str(&tmpReturn_41, "image-view") ) ;
					
				
					o->intId = 0;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_42 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_43 = NULL;
				{
					SuiView$DockItem*  o = SuiView$mkDockItem(&tmpReturn_42, root, Orc$str(&tmpReturn_43, "preview") ) ;
					
				
					o->intId = 0;
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_44 = NULL;
			SuiLayout$layoutLinearCell(&tmpReturn_44, o, 0) ;
			{
				
			}
		}
	}
}


void  SuiDesigner$SpriteSheetEditor$playCurAnim(SuiDesigner$SpriteSheetEditor *  self){
	
}


void  SuiDesigner$SpriteSheetEditor$showWindow(SuiDesigner$SpriteSheetEditor *  self){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, win) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_784_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			self->win->setRootView(self->win, o) ;
		}
		self->react(self) ;
		o->setTitle(o, "精灵表动画编辑器") ;
		o->setSize(o, 800, 600) ;
		o->show(o) ;
	}
}



static void  __finiBlock___Block_48_15(SuiDesigner$__Block_48_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_48_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_274_15(SuiDesigner$__Block_274_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_274_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_329_51(SuiDesigner$__Block_329_51 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_329_51, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_364_49(SuiDesigner$__Block_364_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_364_49, anim) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_364_49, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_371_53(SuiDesigner$__Block_371_53 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_371_53, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_385_62(SuiDesigner$__Block_385_62 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_385_62, anim) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_435_49(SuiDesigner$__Block_435_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_435_49, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_551_16(SuiDesigner$__Block_551_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_551_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_49_37(SuiDesigner$__Closure_49_37 *  self){
	printf("anim tick ms:%lld\n", Orc$Time_unixMs() ) ;
	if (self->__var___Block_48_15->self->info && self->__var___Block_48_15->self->info->fps > 0) {
		self->__var___Block_48_15->self->timer->intervalMs = 1000 / self->__var___Block_48_15->self->info->fps;
	}
	else {
		self->__var___Block_48_15->self->timer->intervalMs = 100;
	}
	self->__var___Block_48_15->self->coordIndex++;
	((SuiCore$ViewBase * )self->__var___Block_48_15->self)->invalidDraw(self->__var___Block_48_15->self) ;
}

static void  __fini___Closure_49_37(SuiDesigner$__Closure_49_37 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_49_37, __var___Block_48_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_49_37*  __make___Closure_49_37(SuiDesigner$__Closure_49_37 **  __outRef__, SuiDesigner$__Block_48_15 *  __var___Block_48_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_49_37*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_49_37) , __fini___Closure_49_37) ));
	self->invoke = __fn___Closure_49_37;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_49_37, __var___Block_48_15) , __var___Block_48_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_275_27(SuiDesigner$__Closure_275_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		self->__var___Block_274_15->self->imgCell->left += d->deltaPos.x;
		self->__var___Block_274_15->self->imgCell->top += d->deltaPos.y;
		self->__var___Block_274_15->self->invalidReact->invalid(self->__var___Block_274_15->self->invalidReact) ;
	}
}

static void  __fini___Closure_275_27(SuiDesigner$__Closure_275_27 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_275_27, __var___Block_274_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_275_27*  __make___Closure_275_27(SuiDesigner$__Closure_275_27 **  __outRef__, SuiDesigner$__Block_274_15 *  __var___Block_274_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_275_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_275_27) , __fini___Closure_275_27) ));
	self->invoke = __fn___Closure_275_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_275_27, __var___Block_274_15) , __var___Block_274_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_283_34(SuiDesigner$__Closure_283_34 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		self->__var___Block_274_15->self->previewCell->left += d->deltaPos.x;
		self->__var___Block_274_15->self->previewCell->top += d->deltaPos.y;
		self->__var___Block_274_15->self->invalidReact->invalid(self->__var___Block_274_15->self->invalidReact) ;
	}
}

static void  __fini___Closure_283_34(SuiDesigner$__Closure_283_34 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_283_34, __var___Block_274_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_283_34*  __make___Closure_283_34(SuiDesigner$__Closure_283_34 **  __outRef__, SuiDesigner$__Block_274_15 *  __var___Block_274_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_283_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_283_34) , __fini___Closure_283_34) ));
	self->invoke = __fn___Closure_283_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_283_34, __var___Block_274_15) , __var___Block_274_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_291_33(SuiDesigner$__Closure_291_33 *  self, SuiView$Drag *  d){
	if (d->isDragStart || d->isDragging) {
		if (self->__var___Block_274_15->self->sceneImageView) {
			SuiCore$ViewBase *  vb = ((SuiCore$ViewBase * )self->__var___Block_274_15->self->sceneImageView)->hitTest(self->__var___Block_274_15->self->sceneImageView, d->currentClientPos.x, d->currentClientPos.y) ;
			if (Orc_instanceof((Object*)vb, (Vtable_Object*)Vtable_SuiCore$View_init(NULL)) && Orc$String$startsWith(((SuiCore$Node * )vb)->name, "cell:") ) {
				int  x = 0;
				int  y = 0;
				sscanf(((SuiCore$Node * )vb)->name->str, "cell:%d,%d", &x, &y) ;
				printf("hover cell:%s. x,y:%d,%d\n", ((SuiCore$Node * )vb)->name->str, x, y) ;
				if (self->__var___Block_274_15->self->curAnim) {
					if (d->mouseEvent->ctrl) {
						self->__var___Block_274_15->self->curAnim->removeFrame(self->__var___Block_274_15->self->curAnim, x, y) ;
					}
					else {
						self->__var___Block_274_15->self->curAnim->addFrame(self->__var___Block_274_15->self->curAnim, x, y) ;
					}
					self->__var___Block_274_15->self->invalidReact->invalid(self->__var___Block_274_15->self->invalidReact) ;
				}
			}
		}
	}
}

static void  __fini___Closure_291_33(SuiDesigner$__Closure_291_33 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_291_33, __var___Block_274_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_291_33*  __make___Closure_291_33(SuiDesigner$__Closure_291_33 **  __outRef__, SuiDesigner$__Block_274_15 *  __var___Block_274_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_291_33*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_291_33) , __fini___Closure_291_33) ));
	self->invoke = __fn___Closure_291_33;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_291_33, __var___Block_274_15) , __var___Block_274_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_336_26(SuiDesigner$__Closure_336_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && ((SuiCore$ViewEvent * )me)->isBubble(me)  && me->isMouseDown) {
			self->__var___Block_329_51->self->dragPreview->onMouseDown(self->__var___Block_329_51->self->dragPreview, me) ;
		}
	}
}

static void  __fini___Closure_336_26(SuiDesigner$__Closure_336_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_336_26, __var___Block_329_51) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_336_26*  __make___Closure_336_26(SuiDesigner$__Closure_336_26 **  __outRef__, SuiDesigner$__Block_329_51 *  __var___Block_329_51){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_336_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_336_26) , __fini___Closure_336_26) ));
	self->invoke = __fn___Closure_336_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_336_26, __var___Block_329_51) , __var___Block_329_51) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_366_51(SuiDesigner$__Closure_366_51 *  self, Orc$String*  newValue){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newValue);

	urgc_set_field_class(self->__var___Block_364_49->anim, (void * )offsetof(SuiDesigner$SpriteSheetAnim, name) , newValue) ;
	self->__var___Block_364_49->self->invalidReact->invalid(self->__var___Block_364_49->self->invalidReact) ;
}

static void  __fini___Closure_366_51(SuiDesigner$__Closure_366_51 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_366_51, __var___Block_364_49) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_366_51*  __make___Closure_366_51(SuiDesigner$__Closure_366_51 **  __outRef__, SuiDesigner$__Block_364_49 *  __var___Block_364_49){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_366_51*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_366_51) , __fini___Closure_366_51) ));
	self->invoke = __fn___Closure_366_51;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_366_51, __var___Block_364_49) , __var___Block_364_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_401_44(SuiDesigner$__Closure_401_44 *  self, SuiCore$Event *  e){
	SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	if (me->button == 3 && me->isClickInBubble(me) ) {
		URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_404*  tmpReturn_1 = NULL;
		(urgc_set_var(&onActive, __make___Closure_onActive_404(&tmpReturn_1, self->__var___Block_371_53, self->__var___Block_385_62) ) );
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		{
			SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
			
		
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_410_40 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$str(&tmpReturn_5, "重命名") , onActive) , *o = __scopeVar_410_40;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
			n->create(n, o) ;
			n->showAtMouse(n) ;
		}
		return true; 
	}
	return false; 
}

static void  __fini___Closure_401_44(SuiDesigner$__Closure_401_44 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_401_44, __var___Block_371_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_401_44, __var___Block_385_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_401_44*  __make___Closure_401_44(SuiDesigner$__Closure_401_44 **  __outRef__, SuiDesigner$__Block_371_53 *  __var___Block_371_53, SuiDesigner$__Block_385_62 *  __var___Block_385_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_401_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_401_44) , __fini___Closure_401_44) ));
	self->invoke = __fn___Closure_401_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_401_44, __var___Block_371_53) , __var___Block_371_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_401_44, __var___Block_385_62) , __var___Block_385_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_404(SuiDesigner$__Closure_onActive_404 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->cmd, "重命名") ) {
		self->__var___Block_371_53->self->showDialog_rename(self->__var___Block_371_53->self, self->__var___Block_385_62->anim) ;
	}
}

static void  __fini___Closure_onActive_404(SuiDesigner$__Closure_onActive_404 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_404, __var___Block_371_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_404, __var___Block_385_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_404*  __make___Closure_onActive_404(SuiDesigner$__Closure_onActive_404 **  __outRef__, SuiDesigner$__Block_371_53 *  __var___Block_371_53, SuiDesigner$__Block_385_62 *  __var___Block_385_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_404*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_404) , __fini___Closure_onActive_404) ));
	self->invoke = __fn___Closure_onActive_404;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_404, __var___Block_371_53) , __var___Block_371_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_404, __var___Block_385_62) , __var___Block_385_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_422_40(SuiDesigner$__Closure_422_40 *  self, SuiCore$MouseEvent *  me){
	urgc_set_field_class(self->__var___Block_371_53->self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, curAnim) , self->__var___Block_385_62->anim) ;
	self->__var___Block_371_53->self->invalidReact->invalid(self->__var___Block_371_53->self->invalidReact) ;
}

static void  __fini___Closure_422_40(SuiDesigner$__Closure_422_40 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_422_40, __var___Block_371_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_422_40, __var___Block_385_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_422_40*  __make___Closure_422_40(SuiDesigner$__Closure_422_40 **  __outRef__, SuiDesigner$__Block_371_53 *  __var___Block_371_53, SuiDesigner$__Block_385_62 *  __var___Block_385_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_422_40*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_422_40) , __fini___Closure_422_40) ));
	self->invoke = __fn___Closure_422_40;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_422_40, __var___Block_371_53) , __var___Block_371_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_422_40, __var___Block_385_62) , __var___Block_385_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_442_26(SuiDesigner$__Closure_442_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && ((SuiCore$ViewEvent * )me)->isBubble(me)  && me->isMouseDown) {
			self->__var___Block_435_49->self->drag->onMouseDown(self->__var___Block_435_49->self->drag, me) ;
		}
		if (me->button == 1 && ((SuiCore$ViewEvent * )me)->isBubble(me)  && me->isMouseDown) {
			self->__var___Block_435_49->self->dragChoose->onMouseDown(self->__var___Block_435_49->self->dragChoose, me) ;
		}
	}
}

static void  __fini___Closure_442_26(SuiDesigner$__Closure_442_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_442_26, __var___Block_435_49) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_442_26*  __make___Closure_442_26(SuiDesigner$__Closure_442_26 **  __outRef__, SuiDesigner$__Block_435_49 *  __var___Block_435_49){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_442_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_442_26) , __fini___Closure_442_26) ));
	self->invoke = __fn___Closure_442_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_442_26, __var___Block_435_49) , __var___Block_435_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_561_39(SuiDesigner$__Closure_561_39 *  self, SuiView$EditText *  et){
	int  rows = Orc$String$toInt(et->value) ;
	self->__var___Block_551_16->self->info->rows = rows;
	self->__var___Block_551_16->self->invalidReact->invalid(self->__var___Block_551_16->self->invalidReact) ;
}

static void  __fini___Closure_561_39(SuiDesigner$__Closure_561_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_561_39, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_561_39*  __make___Closure_561_39(SuiDesigner$__Closure_561_39 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_561_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_561_39) , __fini___Closure_561_39) ));
	self->invoke = __fn___Closure_561_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_561_39, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_573_39(SuiDesigner$__Closure_573_39 *  self, SuiView$EditText *  et){
	int  v = Orc$String$toInt(et->value) ;
	self->__var___Block_551_16->self->info->cols = v;
	self->__var___Block_551_16->self->invalidReact->invalid(self->__var___Block_551_16->self->invalidReact) ;
}

static void  __fini___Closure_573_39(SuiDesigner$__Closure_573_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_573_39, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_573_39*  __make___Closure_573_39(SuiDesigner$__Closure_573_39 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_573_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_573_39) , __fini___Closure_573_39) ));
	self->invoke = __fn___Closure_573_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_573_39, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_585_39(SuiDesigner$__Closure_585_39 *  self, SuiView$EditText *  et){
	int  v = Orc$String$toFloat(et->value) ;
	self->__var___Block_551_16->self->info->fps = v;
	self->__var___Block_551_16->self->invalidReact->invalid(self->__var___Block_551_16->self->invalidReact) ;
}

static void  __fini___Closure_585_39(SuiDesigner$__Closure_585_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_585_39, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_585_39*  __make___Closure_585_39(SuiDesigner$__Closure_585_39 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_585_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_585_39) , __fini___Closure_585_39) ));
	self->invoke = __fn___Closure_585_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_585_39, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_594_32(SuiDesigner$__Closure_594_32 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SpriteSheetAnim*  anim = (anim=NULL,urgc_init_var_class((void**)&anim, SuiDesigner$SpriteSheetAnim_new(&anim) ));
	Orc$String$set(anim->name, "新建动画") ;
	self->__var___Block_551_16->self->info->anims->add(self->__var___Block_551_16->self->info->anims, anim) ;
	self->__var___Block_551_16->self->invalidReact->invalid(self->__var___Block_551_16->self->invalidReact) ;
}

static void  __fini___Closure_594_32(SuiDesigner$__Closure_594_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_594_32, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_594_32*  __make___Closure_594_32(SuiDesigner$__Closure_594_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_594_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_594_32) , __fini___Closure_594_32) ));
	self->invoke = __fn___Closure_594_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_594_32, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_605_32(SuiDesigner$__Closure_605_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_551_16->self->removeCurAnim(self->__var___Block_551_16->self) ;
}

static void  __fini___Closure_605_32(SuiDesigner$__Closure_605_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_605_32, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_605_32*  __make___Closure_605_32(SuiDesigner$__Closure_605_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_605_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_605_32) , __fini___Closure_605_32) ));
	self->invoke = __fn___Closure_605_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_605_32, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_611_32(SuiDesigner$__Closure_611_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_551_16->self->printSceneTree(self->__var___Block_551_16->self) ;
}

static void  __fini___Closure_611_32(SuiDesigner$__Closure_611_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_611_32, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_611_32*  __make___Closure_611_32(SuiDesigner$__Closure_611_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_611_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_611_32) , __fini___Closure_611_32) ));
	self->invoke = __fn___Closure_611_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_611_32, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_617_32(SuiDesigner$__Closure_617_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_551_16->self->playCurAnim(self->__var___Block_551_16->self) ;
}

static void  __fini___Closure_617_32(SuiDesigner$__Closure_617_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_617_32, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_617_32*  __make___Closure_617_32(SuiDesigner$__Closure_617_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_617_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_617_32) , __fini___Closure_617_32) ));
	self->invoke = __fn___Closure_617_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_617_32, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_623_32(SuiDesigner$__Closure_623_32 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_toJson((jo = NULL,&jo), self->__var___Block_551_16->self->info) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = jo->dump((s = NULL,&s), jo) ;
	printf("jo:%s\n", s->str) ;
	Orc$Path_writeText(self->__var___Block_551_16->self->path->str, s->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	SuiDialog$Toast_make(Orc$String$addString(Orc$str(&tmpReturn_1, "保存成功:") , self->__var___Block_551_16->self->path) ->str) ;
}

static void  __fini___Closure_623_32(SuiDesigner$__Closure_623_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_623_32, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_623_32*  __make___Closure_623_32(SuiDesigner$__Closure_623_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_623_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_623_32) , __fini___Closure_623_32) ));
	self->invoke = __fn___Closure_623_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_623_32, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_633_32(SuiDesigner$__Closure_633_32 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parseByPathCstr((jo = NULL,&jo), self->__var___Block_551_16->self->path->str) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SpriteSheetInfo*  info = jo->toObjectByVtable((info = NULL,&info), jo, Vtable_SuiDesigner$SpriteSheetInfo_init(NULL)) ;
	urgc_set_field_class(self->__var___Block_551_16->self, (void * )offsetof(SuiDesigner$SpriteSheetEditor, info) , info) ;
	self->__var___Block_551_16->self->invalidReact->invalid(self->__var___Block_551_16->self->invalidReact) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  newjo = Json$Json_toJson((newjo = NULL,&newjo), info) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("new jo:%s\n", newjo->dump(&tmpReturn_1, newjo) ->str) ;
}

static void  __fini___Closure_633_32(SuiDesigner$__Closure_633_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_633_32, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_633_32*  __make___Closure_633_32(SuiDesigner$__Closure_633_32 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_633_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_633_32) , __fini___Closure_633_32) ));
	self->invoke = __fn___Closure_633_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_633_32, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_652_45(SuiDesigner$__Closure_652_45 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex){
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpItem = (tmpItem=NULL,urgc_init_var_class((void**)&tmpItem, item));
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpDock = (tmpDock=NULL,urgc_init_var_class((void**)&tmpDock, dockLayoutIns));
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_657_24 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_657_24;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_657_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_2, "pointer") ) ;
		o->setText(o, item->id) ;
		o->color = self->__var___Block_551_16->t->dock_head_c;
		((SuiCore$View * )o)->padding.top = 4;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->padding, 8) ;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 0.0f, 0xffaeaeb2) ;
		bool  active = item->parent->tabActiveIndex == kidIndex;
		if (active) {
			((SuiCore$View * )o)->border->t->w = 2.f;
			((SuiCore$View * )o)->border->t->color = self->__var___Block_551_16->t->c_main;
		}
		if (kidIndex < item->parent->children->size(item->parent->children)  - 1) {
			((SuiCore$View * )o)->border->r->w = 1.f;
		}
		((SuiCore$View * )o)->backgroundColor = active ? self->__var___Block_551_16->t->dock_head_bg_active : self->__var___Block_551_16->t->dock_head_bg;
	}
}

static void  __fini___Closure_652_45(SuiDesigner$__Closure_652_45 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_652_45, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_652_45*  __make___Closure_652_45(SuiDesigner$__Closure_652_45 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_652_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_652_45) , __fini___Closure_652_45) ));
	self->invoke = __fn___Closure_652_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_652_45, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$ViewBase *  __fn___Closure_685_48(SuiDesigner$__Closure_685_48 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o){
	if (Orc$String$equals(item->id, "image-view") ) {
		return self->__var___Block_551_16->self->reactScene(self->__var___Block_551_16->self, o, item) ; 
	}
	if (Orc$String$equals(item->id, "preview") ) {
		return self->__var___Block_551_16->self->reactPreview(self->__var___Block_551_16->self, o, item) ; 
	}
	if (Orc$String$equals(item->id, "anim-names") ) {
		return self->__var___Block_551_16->self->reactAnimNames(self->__var___Block_551_16->self, o, item) ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_724_24 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_724_24;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_724_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->needClip = true;
		printf("render dock content:%d, %s\n", item->intId, item->id->str) ;
		o->setText(o, item->id) ;
		o->font_size = 30;
		o->color = 0xff000000;
		((SuiCore$View * )o)->radius->setAll(((SuiCore$View * )o)->radius, 6) ;
		SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 6) ;
		((SuiCore$View * )o)->backgroundColor = item->intId == 0 ? 0x53ff0000 : item->intId == 1 ? 0x53f0ff00 : item->intId == 2 ? 0x5330ffff : 0x5300ffff;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_740_28 = SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) , *o = __scopeVar_740_28;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_740_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		return o; 
	}
}

static void  __fini___Closure_685_48(SuiDesigner$__Closure_685_48 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_685_48, __var___Block_551_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_685_48*  __make___Closure_685_48(SuiDesigner$__Closure_685_48 **  __outRef__, SuiDesigner$__Block_551_16 *  __var___Block_551_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_685_48*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_685_48) , __fini___Closure_685_48) ));
	self->invoke = __fn___Closure_685_48;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_685_48, __var___Block_551_16) , __var___Block_551_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



