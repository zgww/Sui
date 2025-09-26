
#include "Material_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Orc/Orc.h"
#include "./Mat_orc.h"
#include "./Program_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Orc/Math_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Focus_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/View/ColorPicker_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "./Tex2d_orc.h"
#include "./Fbo_orc.h"
#include "./Draw_orc.h"
#include "./Geometry_orc.h"
#include "./Buffer_orc.h"
#include "./Mat_orc.h"
#include "../SuiDesigner/Insp_orc.h"


// static struct 
typedef struct tagSgl$__Block_126_35 Sgl$__Block_126_35;

typedef struct tagSgl$__Block_316_25 Sgl$__Block_316_25;

typedef struct tagSgl$__Block_678_23 Sgl$__Block_678_23;

typedef struct tagSgl$__Block_699_41 Sgl$__Block_699_41;

typedef struct tagSgl$__Block_761_16 Sgl$__Block_761_16;

typedef struct tagSgl$__Block_801_57 Sgl$__Block_801_57;

typedef struct tagSgl$__Block_1370_26 Sgl$__Block_1370_26;

typedef struct tagSgl$__Closure_94_34 Sgl$__Closure_94_34;

typedef struct tagSgl$__Closure_106_41 Sgl$__Closure_106_41;

typedef struct tagSgl$__Closure_114_41 Sgl$__Closure_114_41;

typedef struct tagSgl$__Closure_123_41 Sgl$__Closure_123_41;

typedef struct tagSgl$__Closure_135_34 Sgl$__Closure_135_34;

typedef struct tagSgl$__Closure_321_25 Sgl$__Closure_321_25;

typedef struct tagSgl$__Closure_683_30 Sgl$__Closure_683_30;

typedef struct tagSgl$__Closure_718_37 Sgl$__Closure_718_37;

typedef struct tagSgl$__Closure_794_46 Sgl$__Closure_794_46;

typedef struct tagSgl$__Closure_799_48 Sgl$__Closure_799_48;

typedef struct tagSgl$__Closure_814_58 Sgl$__Closure_814_58;

typedef struct tagSgl$__Closure_onActive_818 Sgl$__Closure_onActive_818;

typedef struct tagSgl$__Closure_850_62 Sgl$__Closure_850_62;

typedef struct tagSgl$__Closure_863_62 Sgl$__Closure_863_62;

typedef struct tagSgl$__Closure_877_67 Sgl$__Closure_877_67;

typedef struct tagSgl$__Closure_894_67 Sgl$__Closure_894_67;

typedef struct tagSgl$__Closure_910_67 Sgl$__Closure_910_67;

typedef struct tagSgl$__Closure_928_67 Sgl$__Closure_928_67;

typedef struct tagSgl$__Closure_945_67 Sgl$__Closure_945_67;

typedef struct tagSgl$__Closure_962_67 Sgl$__Closure_962_67;

typedef struct tagSgl$__Closure_981_67 Sgl$__Closure_981_67;

typedef struct tagSgl$__Closure_999_67 Sgl$__Closure_999_67;

typedef struct tagSgl$__Closure_1017_67 Sgl$__Closure_1017_67;

typedef struct tagSgl$__Closure_1035_67 Sgl$__Closure_1035_67;

typedef struct tagSgl$__Closure_1067_46 Sgl$__Closure_1067_46;

typedef struct tagSgl$__Closure_1072_48 Sgl$__Closure_1072_48;

typedef struct tagSgl$__Closure_1132_36 Sgl$__Closure_1132_36;

typedef struct tagSgl$__Closure_1147_36 Sgl$__Closure_1147_36;

typedef struct tagSgl$__Closure_1374_35 Sgl$__Closure_1374_35;



struct tagSgl$__Block_126_35 {
	Orc$String*  path ;
};





struct tagSgl$__Block_316_25 {
	Sgl$Material*  self ;
};





struct tagSgl$__Block_678_23 {
	Sgl$MaterialInsp*  self ;
};





struct tagSgl$__Block_699_41 {
	Sgl$MaterialInsp*  self ;
	Orc$String*  keyStr ;
};





struct tagSgl$__Block_761_16 {
	Sgl$MaterialInsp*  self ;
};





struct tagSgl$__Block_801_57 {
	Sgl$UniformMeta *  um ;
	Sgl$UniformInfo*  ui ;
};





struct tagSgl$__Block_1370_26 {
	Sgl$MaterialPreviewView*  self ;
};





struct tagSgl$__Closure_94_34 {
	void  (*invoke)(Sgl$__Closure_94_34 *  self, int  newcolor);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_106_41 {
	void  (*invoke)(Sgl$__Closure_106_41 *  self, SuiCore$Vec2 nv);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_114_41 {
	void  (*invoke)(Sgl$__Closure_114_41 *  self, SuiCore$Vec3 nv);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_123_41 {
	void  (*invoke)(Sgl$__Closure_123_41 *  self, SuiCore$Vec4 nv);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_135_34 {
	void  (*invoke)(Sgl$__Closure_135_34 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	Sgl$__Block_126_35*  __var___Block_126_35 ;
};





struct tagSgl$__Closure_321_25 {
	void  (*invoke)(Sgl$__Closure_321_25 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
	Sgl$__Block_316_25*  __var___Block_316_25 ;
};





struct tagSgl$__Closure_683_30 {
	bool  (*invoke)(Sgl$__Closure_683_30 *  self);
	Vtable_Object *  vtable ;
	Sgl$__Block_678_23*  __var___Block_678_23 ;
};





struct tagSgl$__Closure_718_37 {
	void  (*invoke)(Sgl$__Closure_718_37 *  self, SuiView$Switch *  ins);
	Vtable_Object *  vtable ;
	Sgl$__Block_699_41*  __var___Block_699_41 ;
};





struct tagSgl$__Closure_794_46 {
	void  (*invoke)(Sgl$__Closure_794_46 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_799_48 {
	void  (*invoke)(Sgl$__Closure_799_48 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
};





struct tagSgl$__Closure_814_58 {
	void  (*invoke)(Sgl$__Closure_814_58 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_onActive_818 {
	void  (*invoke)(Sgl$__Closure_onActive_818 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_850_62 {
	void  (*invoke)(Sgl$__Closure_850_62 *  self, int  newcolor);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_863_62 {
	void  (*invoke)(Sgl$__Closure_863_62 *  self, int  newcolor);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_877_67 {
	void  (*invoke)(Sgl$__Closure_877_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_894_67 {
	void  (*invoke)(Sgl$__Closure_894_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_910_67 {
	void  (*invoke)(Sgl$__Closure_910_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_928_67 {
	void  (*invoke)(Sgl$__Closure_928_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_945_67 {
	void  (*invoke)(Sgl$__Closure_945_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_962_67 {
	void  (*invoke)(Sgl$__Closure_962_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_981_67 {
	void  (*invoke)(Sgl$__Closure_981_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_999_67 {
	void  (*invoke)(Sgl$__Closure_999_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_1017_67 {
	void  (*invoke)(Sgl$__Closure_1017_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_1035_67 {
	void  (*invoke)(Sgl$__Closure_1035_67 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
	Sgl$__Block_801_57*  __var___Block_801_57 ;
};





struct tagSgl$__Closure_1067_46 {
	void  (*invoke)(Sgl$__Closure_1067_46 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_1072_48 {
	void  (*invoke)(Sgl$__Closure_1072_48 *  self, SuiCore$Node *  o);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
};





struct tagSgl$__Closure_1132_36 {
	void  (*invoke)(Sgl$__Closure_1132_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSgl$__Closure_1147_36 {
	void  (*invoke)(Sgl$__Closure_1147_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	Sgl$__Block_761_16*  __var___Block_761_16 ;
};





struct tagSgl$__Closure_1374_35 {
	void  (*invoke)(Sgl$__Closure_1374_35 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	Sgl$__Block_1370_26*  __var___Block_1370_26 ;
};





// static function declaration
static void  __finiBlock___Block_126_35(Sgl$__Block_126_35 *  self);
static void  __finiBlock___Block_316_25(Sgl$__Block_316_25 *  self);
static void  __finiBlock___Block_678_23(Sgl$__Block_678_23 *  self);
static void  __finiBlock___Block_699_41(Sgl$__Block_699_41 *  self);
static void  __finiBlock___Block_761_16(Sgl$__Block_761_16 *  self);
static void  __finiBlock___Block_801_57(Sgl$__Block_801_57 *  self);
static void  __finiBlock___Block_1370_26(Sgl$__Block_1370_26 *  self);
static void  __fn___Closure_94_34(Sgl$__Closure_94_34 *  self, int  newcolor);
static void  __fini___Closure_94_34(Sgl$__Closure_94_34 *  self);
static Sgl$__Closure_94_34*  __make___Closure_94_34(Sgl$__Closure_94_34 **  __outRef__);
static void  __fn___Closure_106_41(Sgl$__Closure_106_41 *  self, SuiCore$Vec2 nv);
static void  __fini___Closure_106_41(Sgl$__Closure_106_41 *  self);
static Sgl$__Closure_106_41*  __make___Closure_106_41(Sgl$__Closure_106_41 **  __outRef__);
static void  __fn___Closure_114_41(Sgl$__Closure_114_41 *  self, SuiCore$Vec3 nv);
static void  __fini___Closure_114_41(Sgl$__Closure_114_41 *  self);
static Sgl$__Closure_114_41*  __make___Closure_114_41(Sgl$__Closure_114_41 **  __outRef__);
static void  __fn___Closure_123_41(Sgl$__Closure_123_41 *  self, SuiCore$Vec4 nv);
static void  __fini___Closure_123_41(Sgl$__Closure_123_41 *  self);
static Sgl$__Closure_123_41*  __make___Closure_123_41(Sgl$__Closure_123_41 **  __outRef__);
static void  __fn___Closure_135_34(Sgl$__Closure_135_34 *  self, SuiCore$Event *  e);
static void  __fini___Closure_135_34(Sgl$__Closure_135_34 *  self);
static Sgl$__Closure_135_34*  __make___Closure_135_34(Sgl$__Closure_135_34 **  __outRef__, Sgl$__Block_126_35 *  __var___Block_126_35);
static void  __fn___Closure_321_25(Sgl$__Closure_321_25 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o);
static void  __fini___Closure_321_25(Sgl$__Closure_321_25 *  self);
static Sgl$__Closure_321_25*  __make___Closure_321_25(Sgl$__Closure_321_25 **  __outRef__, Sgl$__Block_316_25 *  __var___Block_316_25);
static bool  __fn___Closure_683_30(Sgl$__Closure_683_30 *  self);
static void  __fini___Closure_683_30(Sgl$__Closure_683_30 *  self);
static Sgl$__Closure_683_30*  __make___Closure_683_30(Sgl$__Closure_683_30 **  __outRef__, Sgl$__Block_678_23 *  __var___Block_678_23);
static void  __fn___Closure_718_37(Sgl$__Closure_718_37 *  self, SuiView$Switch *  ins);
static void  __fini___Closure_718_37(Sgl$__Closure_718_37 *  self);
static Sgl$__Closure_718_37*  __make___Closure_718_37(Sgl$__Closure_718_37 **  __outRef__, Sgl$__Block_699_41 *  __var___Block_699_41);
static void  __fn___Closure_794_46(Sgl$__Closure_794_46 *  self, SuiCore$Node *  o);
static void  __fini___Closure_794_46(Sgl$__Closure_794_46 *  self);
static Sgl$__Closure_794_46*  __make___Closure_794_46(Sgl$__Closure_794_46 **  __outRef__);
static void  __fn___Closure_799_48(Sgl$__Closure_799_48 *  self, SuiCore$Node *  o);
static void  __fini___Closure_799_48(Sgl$__Closure_799_48 *  self);
static Sgl$__Closure_799_48*  __make___Closure_799_48(Sgl$__Closure_799_48 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16);
static void  __fn___Closure_814_58(Sgl$__Closure_814_58 *  self, SuiCore$Event *  e);
static void  __fini___Closure_814_58(Sgl$__Closure_814_58 *  self);
static Sgl$__Closure_814_58*  __make___Closure_814_58(Sgl$__Closure_814_58 **  __outRef__, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_onActive_818(Sgl$__Closure_onActive_818 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_818(Sgl$__Closure_onActive_818 *  self);
static Sgl$__Closure_onActive_818*  __make___Closure_onActive_818(Sgl$__Closure_onActive_818 **  __outRef__);
static void  __fn___Closure_850_62(Sgl$__Closure_850_62 *  self, int  newcolor);
static void  __fini___Closure_850_62(Sgl$__Closure_850_62 *  self);
static Sgl$__Closure_850_62*  __make___Closure_850_62(Sgl$__Closure_850_62 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_863_62(Sgl$__Closure_863_62 *  self, int  newcolor);
static void  __fini___Closure_863_62(Sgl$__Closure_863_62 *  self);
static Sgl$__Closure_863_62*  __make___Closure_863_62(Sgl$__Closure_863_62 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_877_67(Sgl$__Closure_877_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_877_67(Sgl$__Closure_877_67 *  self);
static Sgl$__Closure_877_67*  __make___Closure_877_67(Sgl$__Closure_877_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_894_67(Sgl$__Closure_894_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_894_67(Sgl$__Closure_894_67 *  self);
static Sgl$__Closure_894_67*  __make___Closure_894_67(Sgl$__Closure_894_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_910_67(Sgl$__Closure_910_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_910_67(Sgl$__Closure_910_67 *  self);
static Sgl$__Closure_910_67*  __make___Closure_910_67(Sgl$__Closure_910_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_928_67(Sgl$__Closure_928_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_928_67(Sgl$__Closure_928_67 *  self);
static Sgl$__Closure_928_67*  __make___Closure_928_67(Sgl$__Closure_928_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_945_67(Sgl$__Closure_945_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_945_67(Sgl$__Closure_945_67 *  self);
static Sgl$__Closure_945_67*  __make___Closure_945_67(Sgl$__Closure_945_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_962_67(Sgl$__Closure_962_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_962_67(Sgl$__Closure_962_67 *  self);
static Sgl$__Closure_962_67*  __make___Closure_962_67(Sgl$__Closure_962_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_981_67(Sgl$__Closure_981_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_981_67(Sgl$__Closure_981_67 *  self);
static Sgl$__Closure_981_67*  __make___Closure_981_67(Sgl$__Closure_981_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_999_67(Sgl$__Closure_999_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_999_67(Sgl$__Closure_999_67 *  self);
static Sgl$__Closure_999_67*  __make___Closure_999_67(Sgl$__Closure_999_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_1017_67(Sgl$__Closure_1017_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1017_67(Sgl$__Closure_1017_67 *  self);
static Sgl$__Closure_1017_67*  __make___Closure_1017_67(Sgl$__Closure_1017_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_1035_67(Sgl$__Closure_1035_67 *  self, SuiView$EditText *  et);
static void  __fini___Closure_1035_67(Sgl$__Closure_1035_67 *  self);
static Sgl$__Closure_1035_67*  __make___Closure_1035_67(Sgl$__Closure_1035_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57);
static void  __fn___Closure_1067_46(Sgl$__Closure_1067_46 *  self, SuiCore$Node *  o);
static void  __fini___Closure_1067_46(Sgl$__Closure_1067_46 *  self);
static Sgl$__Closure_1067_46*  __make___Closure_1067_46(Sgl$__Closure_1067_46 **  __outRef__);
static void  __fn___Closure_1072_48(Sgl$__Closure_1072_48 *  self, SuiCore$Node *  o);
static void  __fini___Closure_1072_48(Sgl$__Closure_1072_48 *  self);
static Sgl$__Closure_1072_48*  __make___Closure_1072_48(Sgl$__Closure_1072_48 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16);
static void  __fn___Closure_1132_36(Sgl$__Closure_1132_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1132_36(Sgl$__Closure_1132_36 *  self);
static Sgl$__Closure_1132_36*  __make___Closure_1132_36(Sgl$__Closure_1132_36 **  __outRef__);
static void  __fn___Closure_1147_36(Sgl$__Closure_1147_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1147_36(Sgl$__Closure_1147_36 *  self);
static Sgl$__Closure_1147_36*  __make___Closure_1147_36(Sgl$__Closure_1147_36 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16);
static void  __fn___Closure_1374_35(Sgl$__Closure_1374_35 *  self, SuiView$Drag *  d);
static void  __fini___Closure_1374_35(Sgl$__Closure_1374_35 *  self);
static Sgl$__Closure_1374_35*  __make___Closure_1374_35(Sgl$__Closure_1374_35 **  __outRef__, Sgl$__Block_1370_26 *  __var___Block_1370_26);



//vtable instance
Vtable_Sgl$UniformInfo _vtable_Sgl$UniformInfo;

// init meta

void Sgl$UniformInfo_initMeta(Vtable_Sgl$UniformInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "key", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$UniformInfo, key), true, false, 1);
	orc_metaField_primitive(&pNext, "kind", OrcMetaType_int, offsetof(Sgl$UniformInfo, kind), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "count", OrcMetaType_int, offsetof(Sgl$UniformInfo, count), 0, 0, 0, 0);//int
	orc_metaField_struct(&pNext, "mat", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$UniformInfo, mat), false, false, 0);
	orc_metaField_primitive(&pNext, "intValues", OrcMetaType_int, offsetof(Sgl$UniformInfo, intValues), 0, 0, 1, 1);//int
	orc_metaField_primitive(&pNext, "floatValues", OrcMetaType_float, offsetof(Sgl$UniformInfo, floatValues), 0, 0, 1, 1);//float
	orc_metaField_primitive(&pNext, "texIndex", OrcMetaType_int, offsetof(Sgl$UniformInfo, texIndex), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "tex", ((Vtable_Object*)Vtable_Sgl$Tex2d_init(0)), offsetof(Sgl$UniformInfo, tex), true, false, 1);
	orc_metaField_class(&pNext, "texPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$UniformInfo, texPath), true, false, 1);
	orc_metaField_class(&pNext, "matArray", ((Vtable_Object*)Vtable_Sgl$MatArray_init(0)), offsetof(Sgl$UniformInfo, matArray), true, false, 1);

	orc_metaField_method(&pNext, "inspAsValue", offsetof(Sgl$UniformInfo, inspAsValue));
	orc_metaField_method(&pNext, "fromJson", offsetof(Sgl$UniformInfo, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(Sgl$UniformInfo, toJson));
	orc_metaField_method(&pNext, "getColor", offsetof(Sgl$UniformInfo, getColor));
	orc_metaField_method(&pNext, "updateUniform", offsetof(Sgl$UniformInfo, updateUniform));
}


// vtable init


Vtable_Sgl$UniformInfo* Vtable_Sgl$UniformInfo_init(Vtable_Sgl$UniformInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$UniformInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$UniformInfo_new;
    ((Vtable_Object*)pvt)->className = "Sgl$UniformInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$UniformInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$UniformInfo_fini(Sgl$UniformInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$UniformInfo_init_fields(Sgl$UniformInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$UniformInfo_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$UniformInfo*)self)->key, Orc$str(&tmpReturn_1, "") );
	((Sgl$UniformInfo*)self)->kind = -1;
	((Sgl$UniformInfo*)self)->count = 1;
	((Sgl$UniformInfo*)self)->texIndex = 0;
	urgc_set_field_class(self, (void**)&((Sgl$UniformInfo*)self)->tex, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$UniformInfo*)self)->texPath, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$UniformInfo*)self)->matArray, NULL);
    }
	((Sgl$UniformInfo*)self)->inspAsValue = (void*)Sgl$UniformInfo$inspAsValue;
	((Sgl$UniformInfo*)self)->fromJson = (void*)Sgl$UniformInfo$fromJson;
	((Sgl$UniformInfo*)self)->toJson = (void*)Sgl$UniformInfo$toJson;
	((Sgl$UniformInfo*)self)->getColor = (void*)Sgl$UniformInfo$getColor;
	((Sgl$UniformInfo*)self)->updateUniform = (void*)Sgl$UniformInfo$updateUniform;
}

// init function

void Sgl$UniformInfo_init(Sgl$UniformInfo *self, void *pOwner){
    Vtable_Sgl$UniformInfo_init(&_vtable_Sgl$UniformInfo);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$UniformInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$UniformInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$UniformInfo * Sgl$UniformInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$UniformInfo *self = calloc(1, sizeof(Sgl$UniformInfo));
	
    Sgl$UniformInfo_init(self, pOwner);
    return self;
}


// class members
void  Sgl$UniformInfo$inspAsValue(Sgl$UniformInfo *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o, Sgl$Material *  matl){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_81_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )self) , *o = __scopeVar_81_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_81_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->border->b->set(((SuiCore$View * )o)->border->b, 1, 0x13000000) ;
		o->row(o) ;
		insp->mkFieldName(insp, o, self->key->str) ;
		if (self->kind == 6) {
			URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_2 = NULL;
			{
				SuiView$ColorPicker*  __scopeVar_92_16 = SuiView$mkColorPicker(&tmpReturn_2, o, 0) , *o = __scopeVar_92_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_92_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				SuiCore$Rgbaf tmpStructThis1;
				((SuiCore$View * )o)->backgroundColor = SuiCore$Rgbaf$toInt((tmpStructThis1 = SuiCore$mkRgbafByFloat4(self->floatValues) ,&tmpStructThis1)) ;
				URGC_VAR_CLEANUP Sgl$__Closure_94_34*  tmpReturn_3 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_94_34(&tmpReturn_3) ) ;
			}
		}
		else if (self->kind == 3) {
			if (self->count == 2) {
				SuiCore$Vec2 v = SuiCore$mkVec2(self->floatValues[0], self->floatValues[1]) ;
				URGC_VAR_CLEANUP Sgl$__Closure_106_41*  tmpReturn_4 = NULL;
				SuiDesigner$Insp_mkVec2(o, 0, v, __make___Closure_106_41(&tmpReturn_4) ) ;
			}
			else if (self->count == 3) {
				SuiCore$Vec3 v = SuiCore$mkVec3(self->floatValues[0], self->floatValues[1], self->floatValues[2]) ;
				URGC_VAR_CLEANUP Sgl$__Closure_114_41*  tmpReturn_5 = NULL;
				SuiDesigner$Insp_mkVec3(o, 0, v, __make___Closure_114_41(&tmpReturn_5) ) ;
			}
			else if (self->count == 4) {
				SuiCore$Vec4 v = SuiCore$mkVec4(self->floatValues[0], self->floatValues[1], self->floatValues[2], self->floatValues[3]) ;
				URGC_VAR_CLEANUP Sgl$__Closure_123_41*  tmpReturn_6 = NULL;
				SuiDesigner$Insp_mkVec4(o, 0, v, __make___Closure_123_41(&tmpReturn_6) ) ;
			}
		}
		else if (self->kind == 4) {
			URGC_VAR_CLEANUP Sgl$__Block_126_35*  __var___Block_126_35 = (__var___Block_126_35=NULL,urgc_init_var((void**)&__var___Block_126_35, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_126_35) , __finiBlock___Block_126_35) ));
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			urgc_set_field_class(__var___Block_126_35, (void * )offsetof(Sgl$__Block_126_35, path) , Orc$Path_resolveRelativeFromFile(&tmpReturn_7, self->texPath->str, matl->path->str) ) ;
			URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_8 = NULL;
			{
				SuiView$ImageView*  __scopeVar_128_16 = SuiView$mkImageView(&tmpReturn_8, o, 0) , *o = __scopeVar_128_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_128_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->width = 100;
				((SuiCore$View * )o)->height = 100;
				o->setImageMode(o, SuiView$WrapContent) ;
				((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0xff999999) ;
				o->setSrc(o, __var___Block_126_35->path) ;
				Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
				URGC_VAR_CLEANUP Sgl$__Closure_135_34*  tmpReturn_9 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_135_34(&tmpReturn_9, __var___Block_126_35) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_10 = NULL;
			{
				SuiView$TextView*  __scopeVar_151_16 = SuiView$mkTextView(&tmpReturn_10, o, 0) , *o = __scopeVar_151_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_151_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->setText(o, self->texPath) ;
			}
		}
	}
}


void  Sgl$UniformInfo$fromJson(Sgl$UniformInfo *  self, Json$Json *  jo){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$UniformInfo, key) , jo->getString(&tmpReturn_1, jo, "key") ) ;
	jo->getToInt(jo, "kind", &self->kind) ;
	jo->getToInt(jo, "count", &self->count) ;
	if (self->kind == 2) {
		jo->getToInts(jo, "intValues", self->intValues, self->count) ;
	}
	if (self->kind == 3) {
		jo->getToFloats(jo, "floatValues", self->floatValues, self->count) ;
	}
	if (self->kind == 6) {
		jo->getToFloats(jo, "floatValues", self->floatValues, self->count) ;
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$UniformInfo, texPath) , jo->getString(&tmpReturn_2, jo, "texPath") ) ;
}


void  Sgl$UniformInfo$toJson(Sgl$UniformInfo *  self, Json$Json *  jo){
	jo->putString(jo, "key", self->key) ;
	jo->putNumber(jo, "kind", self->kind) ;
	jo->putNumber(jo, "count", self->count) ;
	if (self->kind == 2) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
		jo->put(jo, "intValues", Json$Json_toJsonNumberArrayByInts(&tmpReturn_1, self->intValues, self->count) ) ;
	}
	if (self->kind == 3) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
		jo->put(jo, "floatValues", Json$Json_toJsonNumberArrayByFloats(&tmpReturn_2, self->floatValues, self->count) ) ;
	}
	if (self->kind == 6) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
		jo->put(jo, "floatValues", Json$Json_toJsonNumberArrayByFloats(&tmpReturn_3, self->floatValues, self->count) ) ;
	}
	if (self->texPath) {
		jo->putString(jo, "texPath", self->texPath) ;
	}
}


SuiCore$Rgba Sgl$UniformInfo$getColor(Sgl$UniformInfo *  self){
	if (self->kind == 3) {
		SuiCore$Rgba c = SuiCore$mkRgbaByFloat(self->floatValues[0], self->floatValues[1], self->floatValues[2], self->count >= 4 ? self->floatValues[3] : 1.0) ;
		return c; 
	}
	return SuiCore$mkRgba(0, 0, 0, 0) ; 
}


bool  Sgl$UniformInfo$updateUniform(Sgl$UniformInfo *  self, Sgl$Program *  program){
	if (self->key && Orc$String$notEmpty(self->key) ) {
		if (self->kind == 1) {
			program->uniformMatrix4f(program, self->key->str, self->mat.data) ;
		}
		else if (self->kind == 5) {
			program->uniformMatrix4fv(program, self->key->str, self->matArray->data, ((Sgl$StructArrayBase * )self->matArray)->size) ;
		}
		else if (self->kind == 2) {
			if (self->count == 1) {
				program->uniform1i(program, self->key->str, self->intValues[0]) ;
			}
		}
		else if (self->kind == 3) {
			if (self->count == 2) {
				program->uniform2f(program, self->key->str, self->floatValues[0], self->floatValues[1]) ;
			}
			else if (self->count == 3) {
				program->uniform3f(program, self->key->str, self->floatValues[0], self->floatValues[1], self->floatValues[2]) ;
			}
			else if (self->count == 4) {
				program->uniform4f(program, self->key->str, self->floatValues[0], self->floatValues[1], self->floatValues[2], self->floatValues[3]) ;
			}
			else {
				return false; 
			}
		}
		else if (self->kind == 4) {
			if (self->tex) {
				self->tex->active(self->tex, self->texIndex) ;
				self->tex->bind(self->tex) ;
				program->uniform1i(program, self->key->str, self->texIndex) ;
			}
			else {
				return false; 
			}
		}
		else if (self->kind == 6) {
			program->uniform4f(program, self->key->str, self->floatValues[0], self->floatValues[1], self->floatValues[2], self->floatValues[3]) ;
		}
		return true; 
	}
	return false; 
}




//vtable instance
Vtable_Sgl$Material _vtable_Sgl$Material;

// init meta

void Sgl$Material_initMeta(Vtable_Sgl$Material *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Material, path), true, false, 1);
	orc_metaField_class(&pNext, "program", ((Vtable_Object*)Vtable_Sgl$Program_init(0)), offsetof(Sgl$Material, program), true, false, 1);
	orc_metaField_primitive(&pNext, "depthTest", OrcMetaType_bool, offsetof(Sgl$Material, depthTest), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "depthWrite", OrcMetaType_bool, offsetof(Sgl$Material, depthWrite), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "transparent", OrcMetaType_bool, offsetof(Sgl$Material, transparent), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "stencilTest", OrcMetaType_bool, offsetof(Sgl$Material, stencilTest), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "alphaTest", OrcMetaType_bool, offsetof(Sgl$Material, alphaTest), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "scissorTest", OrcMetaType_bool, offsetof(Sgl$Material, scissorTest), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "blend", OrcMetaType_bool, offsetof(Sgl$Material, blend), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "cullFace", OrcMetaType_bool, offsetof(Sgl$Material, cullFace), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "wireframe", OrcMetaType_bool, offsetof(Sgl$Material, wireframe), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "uniforms", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$Material, uniforms), true, false, 1);
	orc_metaField_struct(&pNext, "mvp", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Material, mvp), false, false, 0);
	orc_metaField_struct(&pNext, "model", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Material, model), false, false, 0);
	orc_metaField_struct(&pNext, "view", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Material, view), false, false, 0);
	orc_metaField_struct(&pNext, "projection", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Material, projection), false, false, 0);
	orc_metaField_class(&pNext, "vsPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Material, vsPath), true, false, 1);
	orc_metaField_class(&pNext, "fsPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$Material, fsPath), true, false, 1);
	orc_metaField_class(&pNext, "shaderMeta", ((Vtable_Object*)Vtable_Sgl$ShaderMeta_init(0)), offsetof(Sgl$Material, shaderMeta), true, false, 1);

	orc_metaField_method(&pNext, "insp", offsetof(Sgl$Material, insp));
	orc_metaField_method(&pNext, "insp_hi", offsetof(Sgl$Material, insp_hi));
	orc_metaField_method(&pNext, "prepareDraw", offsetof(Sgl$Material, prepareDraw));
	orc_metaField_method(&pNext, "endDraw", offsetof(Sgl$Material, endDraw));
	orc_metaField_method(&pNext, "load", offsetof(Sgl$Material, load));
	orc_metaField_method(&pNext, "saveTo", offsetof(Sgl$Material, saveTo));
	orc_metaField_method(&pNext, "save", offsetof(Sgl$Material, save));
	orc_metaField_method(&pNext, "fromJson", offsetof(Sgl$Material, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(Sgl$Material, toJson));
	orc_metaField_method(&pNext, "updateMvp", offsetof(Sgl$Material, updateMvp));
	orc_metaField_method(&pNext, "setMvp", offsetof(Sgl$Material, setMvp));
	orc_metaField_method(&pNext, "updateUniforms", offsetof(Sgl$Material, updateUniforms));
	orc_metaField_method(&pNext, "getUniformInfo", offsetof(Sgl$Material, getUniformInfo));
	orc_metaField_method(&pNext, "gocUniformInfo", offsetof(Sgl$Material, gocUniformInfo));
	orc_metaField_method(&pNext, "setUniformTex2d", offsetof(Sgl$Material, setUniformTex2d));
	orc_metaField_method(&pNext, "setUniformMatArray", offsetof(Sgl$Material, setUniformMatArray));
	orc_metaField_method(&pNext, "setUniformMat4", offsetof(Sgl$Material, setUniformMat4));
	orc_metaField_method(&pNext, "setUniform1i", offsetof(Sgl$Material, setUniform1i));
	orc_metaField_method(&pNext, "setUniform1f", offsetof(Sgl$Material, setUniform1f));
	orc_metaField_method(&pNext, "setUniform2f", offsetof(Sgl$Material, setUniform2f));
	orc_metaField_method(&pNext, "setUniform3f", offsetof(Sgl$Material, setUniform3f));
	orc_metaField_method(&pNext, "setUniform4f", offsetof(Sgl$Material, setUniform4f));
	orc_metaField_method(&pNext, "setUniformColor4f", offsetof(Sgl$Material, setUniformColor4f));
	orc_metaField_method(&pNext, "setUniformColor4fByInt32Color", offsetof(Sgl$Material, setUniformColor4fByInt32Color));
	orc_metaField_method(&pNext, "setUniformVec2", offsetof(Sgl$Material, setUniformVec2));
	orc_metaField_method(&pNext, "setUniformVec3", offsetof(Sgl$Material, setUniformVec3));
	orc_metaField_method(&pNext, "setUniformVec4", offsetof(Sgl$Material, setUniformVec4));
	orc_metaField_method(&pNext, "buildByShaderPathCstr", offsetof(Sgl$Material, buildByShaderPathCstr));
}


// vtable init


Vtable_Sgl$Material* Vtable_Sgl$Material_init(Vtable_Sgl$Material* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Material;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Material_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Material";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Material_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Material_fini(Sgl$Material *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$Material_init_fields(Sgl$Material *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$Material_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Material*)self)->path, Orc$str(&tmpReturn_1, "test.matl.json") );
	urgc_set_field_class(self, (void**)&((Sgl$Material*)self)->program, NULL);
	((Sgl$Material*)self)->depthTest = false;
	((Sgl$Material*)self)->depthWrite = true;
	((Sgl$Material*)self)->transparent = false;
	((Sgl$Material*)self)->stencilTest = false;
	((Sgl$Material*)self)->alphaTest = false;
	((Sgl$Material*)self)->scissorTest = false;
	((Sgl$Material*)self)->blend = true;
	((Sgl$Material*)self)->cullFace = false;
	((Sgl$Material*)self)->wireframe = false;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Material*)self)->uniforms, Orc$List_new(&tmpNewOwner_2) );
	((Sgl$Material*)self)->mvp = Sgl$mkMatIdentity() ;
	((Sgl$Material*)self)->model = Sgl$mkMatIdentity() ;
	((Sgl$Material*)self)->view = Sgl$mkMatIdentity() ;
	((Sgl$Material*)self)->projection = Sgl$mkMatIdentity() ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Material*)self)->vsPath, Orc$str(&tmpReturn_3, "a.vs") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Material*)self)->fsPath, Orc$str(&tmpReturn_4, "a.fs") );
	urgc_set_field_class(self, (void**)&((Sgl$Material*)self)->shaderMeta, NULL);
    }
	((Sgl$Material*)self)->insp = (void*)Sgl$Material$insp;
	((Sgl$Material*)self)->insp_hi = (void*)Sgl$Material$insp_hi;
	((Sgl$Material*)self)->prepareDraw = (void*)Sgl$Material$prepareDraw;
	((Sgl$Material*)self)->endDraw = (void*)Sgl$Material$endDraw;
	((Sgl$Material*)self)->load = (void*)Sgl$Material$load;
	((Sgl$Material*)self)->saveTo = (void*)Sgl$Material$saveTo;
	((Sgl$Material*)self)->save = (void*)Sgl$Material$save;
	((Sgl$Material*)self)->fromJson = (void*)Sgl$Material$fromJson;
	((Sgl$Material*)self)->toJson = (void*)Sgl$Material$toJson;
	((Sgl$Material*)self)->updateMvp = (void*)Sgl$Material$updateMvp;
	((Sgl$Material*)self)->setMvp = (void*)Sgl$Material$setMvp;
	((Sgl$Material*)self)->updateUniforms = (void*)Sgl$Material$updateUniforms;
	((Sgl$Material*)self)->getUniformInfo = (void*)Sgl$Material$getUniformInfo;
	((Sgl$Material*)self)->gocUniformInfo = (void*)Sgl$Material$gocUniformInfo;
	((Sgl$Material*)self)->setUniformTex2d = (void*)Sgl$Material$setUniformTex2d;
	((Sgl$Material*)self)->setUniformMatArray = (void*)Sgl$Material$setUniformMatArray;
	((Sgl$Material*)self)->setUniformMat4 = (void*)Sgl$Material$setUniformMat4;
	((Sgl$Material*)self)->setUniform1i = (void*)Sgl$Material$setUniform1i;
	((Sgl$Material*)self)->setUniform1f = (void*)Sgl$Material$setUniform1f;
	((Sgl$Material*)self)->setUniform2f = (void*)Sgl$Material$setUniform2f;
	((Sgl$Material*)self)->setUniform3f = (void*)Sgl$Material$setUniform3f;
	((Sgl$Material*)self)->setUniform4f = (void*)Sgl$Material$setUniform4f;
	((Sgl$Material*)self)->setUniformColor4f = (void*)Sgl$Material$setUniformColor4f;
	((Sgl$Material*)self)->setUniformColor4fByInt32Color = (void*)Sgl$Material$setUniformColor4fByInt32Color;
	((Sgl$Material*)self)->setUniformVec2 = (void*)Sgl$Material$setUniformVec2;
	((Sgl$Material*)self)->setUniformVec3 = (void*)Sgl$Material$setUniformVec3;
	((Sgl$Material*)self)->setUniformVec4 = (void*)Sgl$Material$setUniformVec4;
	((Sgl$Material*)self)->buildByShaderPathCstr = (void*)Sgl$Material$buildByShaderPathCstr;
}

// init function

void Sgl$Material_init(Sgl$Material *self, void *pOwner){
    Vtable_Sgl$Material_init(&_vtable_Sgl$Material);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Material;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Material_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Material * Sgl$Material_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Material *self = calloc(1, sizeof(Sgl$Material));
	
    Sgl$Material_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Material$insp(Sgl$Material *  self, SuiDesigner$Insp *  insp){
	URGC_VAR_CLEANUP Sgl$__Block_316_25*  __var___Block_316_25 = (__var___Block_316_25=NULL,urgc_init_var((void**)&__var___Block_316_25, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_316_25) , __finiBlock___Block_316_25) ));
	urgc_set_field_class(__var___Block_316_25, (void * )offsetof(Sgl$__Block_316_25, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttrFilePath*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$InspAttrFilePath*  o = SuiDesigner$InspAttrFilePath_new(&tmpNewOwner_1) ;
		
	
		((SuiDesigner$InspAttr * )o)->bind(o, insp, "path", NULL) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttrFilePath*  tmpNewOwner_2 = NULL;
	{
		SuiDesigner$InspAttrFilePath*  o = SuiDesigner$InspAttrFilePath_new(&tmpNewOwner_2) ;
		
	
		((SuiDesigner$InspAttr * )o)->bind(o, insp, "vsPath", NULL) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttrFilePath*  tmpNewOwner_3 = NULL;
	{
		SuiDesigner$InspAttrFilePath*  o = SuiDesigner$InspAttrFilePath_new(&tmpNewOwner_3) ;
		
	
		((SuiDesigner$InspAttr * )o)->bind(o, insp, "fsPath", NULL) ;
	}
	URGC_VAR_CLEANUP Sgl$__Closure_321_25*  tmpReturn_4 = NULL;
	urgc_set_field(insp, (void * )offsetof(SuiDesigner$Insp, afterInsp) , __make___Closure_321_25(&tmpReturn_4, __var___Block_316_25) ) ;
}


void  Sgl$Material$insp_hi(Sgl$Material *  self){
	SuiDialog$Toast_make("hi") ;
}


bool  Sgl$Material$load(Sgl$Material *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Material, path) , Orc$str(&tmpReturn_1, path) ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parseByPathCstr((jo = NULL,&jo), path) ;
	if (jo) {
		jo->toObject(jo, self) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  dirname = Orc$Path_dirname((dirname = NULL,&dirname), path) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  realVsPath = (realVsPath=NULL,urgc_init_var_class((void**)&realVsPath, Orc$String$addString(Orc$String$add(Orc$String$clone(&tmpReturn_2, dirname) , "/") , self->vsPath) ));
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  realFsPath = (realFsPath=NULL,urgc_init_var_class((void**)&realFsPath, Orc$String$addString(Orc$String$add(Orc$String$clone(&tmpReturn_3, dirname) , "/") , self->fsPath) ));
		self->buildByShaderPathCstr(self, realVsPath->str, realFsPath->str) ;
		return true; 
	}
	return false; 
}


bool  Sgl$Material$saveTo(Sgl$Material *  self, Orc$String *  path){
	if (path && Orc$String$notEmpty(path) ) {
		URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_toJson((jo = NULL,&jo), self) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		Orc$Path_writeText(path->str, jo->dump(&tmpReturn_1, jo) ->str) ;
		return true; 
	}
	return false; 
}


bool  Sgl$Material$save(Sgl$Material *  self){
	bool  b = self->saveTo(self, self->path) ;
	return b; 
}


void  Sgl$Material$fromJson(Sgl$Material *  self, Json$Json *  jo){
	URGC_VAR_CLEANUP_CLASS Orc$String*  vsPath = jo->getString((vsPath = NULL,&vsPath), jo, "vsPath") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  fsPath = jo->getString((fsPath = NULL,&fsPath), jo, "fsPath") ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Material, vsPath) , vsPath) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Material, fsPath) , fsPath) ;
	jo->getToBool(jo, "depthTest", &self->depthTest) ;
	jo->getToBool(jo, "depthWrite", &self->depthWrite) ;
	jo->getToBool(jo, "transparent", &self->transparent) ;
	jo->getToBool(jo, "stencilTest", &self->stencilTest) ;
	jo->getToBool(jo, "alphaTest", &self->alphaTest) ;
	jo->getToBool(jo, "scissorTest", &self->scissorTest) ;
	jo->getToBool(jo, "blend", &self->blend) ;
	jo->getToBool(jo, "cullFace", &self->cullFace) ;
	jo->getToBool(jo, "wireframe", &self->wireframe) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  uniformsJa = jo->get((uniformsJa = NULL,&uniformsJa), jo, "uniforms") ;
	if (uniformsJa) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$Material, uniforms) , uniformsJa->toObjectsByVtable(&tmpReturn_1, uniformsJa, Vtable_Sgl$UniformInfo_init(NULL)) ) ;
	}
}


void  Sgl$Material$toJson(Sgl$Material *  self, Json$Json *  jo){
	jo->putBool(jo, "depthWrite", self->depthWrite) ;
	jo->putBool(jo, "transparent", self->transparent) ;
	jo->putBool(jo, "depthTest", self->depthTest) ;
	jo->putBool(jo, "stencilTest", self->stencilTest) ;
	jo->putBool(jo, "alphaTest", self->alphaTest) ;
	jo->putBool(jo, "scissorTest", self->scissorTest) ;
	jo->putBool(jo, "blend", self->blend) ;
	jo->putBool(jo, "cullFace", self->cullFace) ;
	jo->putBool(jo, "wireframe", self->wireframe) ;
	jo->putString(jo, "vsPath", self->vsPath) ;
	jo->putString(jo, "fsPath", self->fsPath) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	jo->put(jo, "uniforms", Json$Json_toJson(&tmpReturn_1, self->uniforms) ) ;
}


void  Sgl$Material$updateMvp(Sgl$Material *  self){
	Sgl$Mat mv;
	Sgl$Mat$mul(&mv, &self->view, &self->model) ;
	Sgl$Mat$mul(&self->mvp, &self->projection, &mv) ;
}


void  Sgl$Material$setMvp(Sgl$Material *  self, Sgl$Mat model, Sgl$Mat view, Sgl$Mat projection){
	self->model = model;
	self->view = view;
	self->projection = projection;
	self->updateMvp(self) ;
}


void  Sgl$Material$updateUniforms(Sgl$Material *  self){
	int  l = self->uniforms->size(self->uniforms) ;
	int  texIndex = 0;
	for (int  i = 0; i < l; i++) {
		Sgl$UniformInfo *  ui = (Sgl$UniformInfo * )self->uniforms->get(self->uniforms, i) ;
		if (ui->kind == 4) {
			ui->texIndex = texIndex;
			texIndex++;
		}
		ui->updateUniform(ui, self->program) ;
	}
	self->program->uniformMatrix4f(self->program, "model", self->model.data) ;
	self->program->uniformMatrix4f(self->program, "view", self->view.data) ;
	self->program->uniformMatrix4f(self->program, "projection", self->projection.data) ;
	self->program->uniformMatrix4f(self->program, "mvp", self->mvp.data) ;
}


Sgl$UniformInfo*  Sgl$Material$getUniformInfo(Sgl$UniformInfo **  __outRef__, Sgl$Material *  self, const char *  key){
	int  l = self->uniforms->size(self->uniforms) ;
	for (int  i = 0; i < l; i++) {
		Sgl$UniformInfo *  ui = (Sgl$UniformInfo * )self->uniforms->get(self->uniforms, i) ;
		if (Orc$String$equals(ui->key, key) ) {
			return urgc_set_var_for_return_class((void ** )__outRef__, ui) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


Sgl$UniformInfo*  Sgl$Material$gocUniformInfo(Sgl$UniformInfo **  __outRef__, Sgl$Material *  self, const char *  key){
	int  l = self->uniforms->size(self->uniforms) ;
	for (int  i = 0; i < l; i++) {
		Sgl$UniformInfo *  ui = (Sgl$UniformInfo * )self->uniforms->get(self->uniforms, i) ;
		if (Orc$String$equals(ui->key, key) ) {
			return urgc_set_var_for_return_class((void ** )__outRef__, ui) ; 
		}
	}
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Sgl$UniformInfo_new(&ret) ));
	Orc$String$set(ret->key, key) ;
	self->uniforms->add(self->uniforms, ret) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


void  Sgl$Material$setUniformTex2d(Sgl$Material *  self, const char *  key, Sgl$Tex2d *  tex){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 4;
	urgc_set_field_class(ui, (void * )offsetof(Sgl$UniformInfo, tex) , tex) ;
}


void  Sgl$Material$setUniformMatArray(Sgl$Material *  self, const char *  key, Sgl$MatArray*  matArray){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(matArray);

	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 5;
	urgc_set_field_class(ui, (void * )offsetof(Sgl$UniformInfo, matArray) , matArray) ;
}


void  Sgl$Material$setUniformMat4(Sgl$Material *  self, const char *  key, Sgl$Mat mat){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 1;
	ui->mat = mat;
}


void  Sgl$Material$setUniform1i(Sgl$Material *  self, const char *  key, int  v){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 2;
	ui->count = 1;
	ui->intValues[0] = v;
}


void  Sgl$Material$setUniform1f(Sgl$Material *  self, const char *  key, float  v){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 3;
	ui->count = 1;
	ui->floatValues[0] = v;
}


void  Sgl$Material$setUniform2f(Sgl$Material *  self, const char *  key, float  x, float  y){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 3;
	ui->count = 2;
	ui->floatValues[0] = x;
	ui->floatValues[1] = y;
}


void  Sgl$Material$setUniform3f(Sgl$Material *  self, const char *  key, float  x, float  y, float  z){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 3;
	ui->count = 3;
	ui->floatValues[0] = x;
	ui->floatValues[1] = y;
	ui->floatValues[2] = z;
}


void  Sgl$Material$setUniform4f(Sgl$Material *  self, const char *  key, float  x, float  y, float  z, float  w){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 3;
	ui->count = 4;
	ui->floatValues[0] = x;
	ui->floatValues[1] = y;
	ui->floatValues[2] = z;
	ui->floatValues[3] = w;
}


void  Sgl$Material$setUniformColor4f(Sgl$Material *  self, const char *  key, float  x, float  y, float  z, float  w){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 6;
	ui->count = 4;
	ui->floatValues[0] = x;
	ui->floatValues[1] = y;
	ui->floatValues[2] = z;
	ui->floatValues[3] = w;
}


void  Sgl$Material$setUniformColor4fByInt32Color(Sgl$Material *  self, const char *  key, int  color){
	SuiCore$Rgbaf c = SuiCore$mkRgbafByInt(color) ;
	self->setUniformColor4f(self, key, c.r, c.g, c.b, c.a) ;
}


void  Sgl$Material$setUniformVec2(Sgl$Material *  self, const char *  key, SuiCore$Vec2 v){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 3;
	ui->count = 2;
	ui->floatValues[0] = v.x;
	ui->floatValues[1] = v.y;
}


void  Sgl$Material$setUniformVec3(Sgl$Material *  self, const char *  key, SuiCore$Vec3 v3){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 3;
	ui->count = 3;
	ui->floatValues[0] = v3.x;
	ui->floatValues[1] = v3.y;
	ui->floatValues[2] = v3.z;
}


void  Sgl$Material$setUniformVec4(Sgl$Material *  self, const char *  key, SuiCore$Vec4 v){
	URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  ui = self->gocUniformInfo((ui = NULL,&ui), self, key) ;
	ui->kind = 3;
	ui->count = 4;
	ui->floatValues[0] = v.x;
	ui->floatValues[1] = v.y;
	ui->floatValues[2] = v.z;
	ui->floatValues[3] = v.w;
}


bool  Sgl$Material$buildByShaderPathCstr(Sgl$Material *  self, const char *  vsPath, const char *  fsPath){
	URGC_VAR_CLEANUP_CLASS Sgl$Program*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Material, program) , Sgl$Program_new(&tmpNewOwner_1) ) ;
	bool  ok = self->program->compileByPathCstr(self->program, vsPath, fsPath) ;
	URGC_VAR_CLEANUP_CLASS Sgl$ShaderMeta*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$Material, shaderMeta) , Sgl$ShaderMeta_new(&tmpNewOwner_2) ) ;
	self->shaderMeta->parseFsByPathCstr(self->shaderMeta, fsPath) ;
	self->shaderMeta->parseVsByPathCstr(self->shaderMeta, vsPath) ;
	{
		int  l = self->shaderMeta->uniformMetas->size(self->shaderMeta->uniformMetas) ;
		for (int  i = 0; i < l; i++) {
			Sgl$UniformMeta *  um = (Sgl$UniformMeta * )self->shaderMeta->uniformMetas->get(self->shaderMeta->uniformMetas, i) ;
			if (Orc$String$notEmpty(um->defaultValue) ) {
				URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  tmpReturn_3 = NULL;
				Sgl$UniformInfo *  ui = (Sgl$UniformInfo * )self->getUniformInfo(&tmpReturn_3, self, um->name->str) ;
				if (ui) {
					continue;
				}
				URGC_VAR_CLEANUP_CLASS Orc$List*  parts = Orc$String$splitByRe((parts = NULL,&parts), um->defaultValue, "\\s+") ;
				if (Orc$String$equals(um->type, "vec2") ) {
					if (parts->size(parts)  >= 2) {
						Orc$String *  s0 = (Orc$String * )parts->get(parts, 0) ;
						Orc$String *  s1 = (Orc$String * )parts->get(parts, 1) ;
						float  v0 = Orc$String$toFloat(s0) ;
						float  v1 = Orc$String$toFloat(s1) ;
						self->setUniform2f(self, um->name->str, v0, v1) ;
					}
				}
				else if (Orc$String$equals(um->type, "vec3") ) {
					if (parts->size(parts)  >= 3) {
						Orc$String *  s0 = (Orc$String * )parts->get(parts, 0) ;
						Orc$String *  s1 = (Orc$String * )parts->get(parts, 1) ;
						Orc$String *  s2 = (Orc$String * )parts->get(parts, 2) ;
						float  v0 = Orc$String$toFloat(s0) ;
						float  v1 = Orc$String$toFloat(s1) ;
						float  v2 = Orc$String$toFloat(s2) ;
						self->setUniform3f(self, um->name->str, v0, v1, v2) ;
					}
				}
				else if (Orc$String$equals(um->type, "vec4") ) {
					if (parts->size(parts)  >= 4) {
						Orc$String *  s0 = (Orc$String * )parts->get(parts, 0) ;
						Orc$String *  s1 = (Orc$String * )parts->get(parts, 1) ;
						Orc$String *  s2 = (Orc$String * )parts->get(parts, 2) ;
						Orc$String *  s3 = (Orc$String * )parts->get(parts, 3) ;
						float  v0 = Orc$String$toFloat(s0) ;
						float  v1 = Orc$String$toFloat(s1) ;
						float  v2 = Orc$String$toFloat(s2) ;
						float  v3 = Orc$String$toFloat(s3) ;
						self->setUniform4f(self, um->name->str, v0, v1, v2, v3) ;
					}
				}
			}
		}
	}
	return ok; 
}




//vtable instance
Vtable_Sgl$MaterialInsp _vtable_Sgl$MaterialInsp;

// init meta

void Sgl$MaterialInsp_initMeta(Vtable_Sgl$MaterialInsp *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(Sgl$MaterialInsp, win), true, false, 1);
	orc_metaField_class(&pNext, "matl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$MaterialInsp, matl), true, false, 1);
	orc_metaField_primitive(&pNext, "_reactDirty", OrcMetaType_bool, offsetof(Sgl$MaterialInsp, _reactDirty), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "glPreviewView", ((Vtable_Object*)Vtable_Sgl$MaterialPreviewView_init(0)), offsetof(Sgl$MaterialInsp, glPreviewView), true, false, 1);

	orc_metaField_method(&pNext, "invalidReact", offsetof(Sgl$MaterialInsp, invalidReact));
	orc_metaField_method(&pNext, "rowBool", offsetof(Sgl$MaterialInsp, rowBool));
	orc_metaField_method(&pNext, "rowString", offsetof(Sgl$MaterialInsp, rowString));
	orc_metaField_method(&pNext, "react", offsetof(Sgl$MaterialInsp, react));
	orc_metaField_method(&pNext, "showWindow", offsetof(Sgl$MaterialInsp, showWindow));
}


// vtable init


Vtable_Sgl$MaterialInsp* Vtable_Sgl$MaterialInsp_init(Vtable_Sgl$MaterialInsp* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$MaterialInsp;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$MaterialInsp_new;
    ((Vtable_Object*)pvt)->className = "Sgl$MaterialInsp";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$MaterialInsp_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$MaterialInsp_fini(Sgl$MaterialInsp *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$MaterialInsp_init_fields(Sgl$MaterialInsp *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$MaterialInsp_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$MaterialInsp*)self)->win, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$MaterialInsp*)self)->matl, NULL);
	((Sgl$MaterialInsp*)self)->_reactDirty = false;
	urgc_set_field_class(self, (void**)&((Sgl$MaterialInsp*)self)->glPreviewView, NULL);
    }
	((Sgl$MaterialInsp*)self)->invalidReact = (void*)Sgl$MaterialInsp$invalidReact;
	((Sgl$MaterialInsp*)self)->rowBool = (void*)Sgl$MaterialInsp$rowBool;
	((Sgl$MaterialInsp*)self)->rowString = (void*)Sgl$MaterialInsp$rowString;
	((Sgl$MaterialInsp*)self)->react = (void*)Sgl$MaterialInsp$react;
	((Sgl$MaterialInsp*)self)->showWindow = (void*)Sgl$MaterialInsp$showWindow;
}

// init function

void Sgl$MaterialInsp_init(Sgl$MaterialInsp *self, void *pOwner){
    Vtable_Sgl$MaterialInsp_init(&_vtable_Sgl$MaterialInsp);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$MaterialInsp;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$MaterialInsp_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$MaterialInsp * Sgl$MaterialInsp_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$MaterialInsp *self = calloc(1, sizeof(Sgl$MaterialInsp));
	
    Sgl$MaterialInsp_init(self, pOwner);
    return self;
}


// class members
void  Sgl$MaterialInsp$invalidReact(Sgl$MaterialInsp *  self){
	URGC_VAR_CLEANUP Sgl$__Block_678_23*  __var___Block_678_23 = (__var___Block_678_23=NULL,urgc_init_var((void**)&__var___Block_678_23, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_678_23) , __finiBlock___Block_678_23) ));
	urgc_set_field_class(__var___Block_678_23, (void * )offsetof(Sgl$__Block_678_23, self) , self) ;
	if (self->_reactDirty) {
		return ; 
	}
	self->_reactDirty = true;
	URGC_VAR_CLEANUP Sgl$__Closure_683_30*  tmpReturn_1 = NULL;
	SuiCore$requestAnimationFrame(__make___Closure_683_30(&tmpReturn_1, __var___Block_678_23) ) ;
}


void  Sgl$MaterialInsp$rowBool(Sgl$MaterialInsp *  self, SuiCore$Node *  o, const char *  key){
	URGC_VAR_CLEANUP Sgl$__Block_699_41*  __var___Block_699_41 = (__var___Block_699_41=NULL,urgc_init_var((void**)&__var___Block_699_41, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_699_41) , __finiBlock___Block_699_41) ));
	urgc_set_field_class(__var___Block_699_41, (void * )offsetof(Sgl$__Block_699_41, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(__var___Block_699_41, (void * )offsetof(Sgl$__Block_699_41, keyStr) , Orc$str(&tmpReturn_1, key) ) ;
	OrcMetaField *  mf = orc_getMetaFieldByObject(self->matl, key) ;
	if (!mf) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_708_8 = SuiLayout$layoutLinear(&tmpReturn_2, o, (long long )mf) , *o = __scopeVar_708_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_708_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->border->b->set(((SuiCore$View * )o)->border->b, 1, 0x33000000) ;
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
		{
			SuiView$TextView*  __scopeVar_711_12 = SuiView$mkTextView(&tmpReturn_3, o, 0) , *o = __scopeVar_711_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_711_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 100;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			o->setText(o, Orc$String$add(Orc$str(&tmpReturn_4, key) , ": ") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$Switch*  tmpReturn_5 = NULL;
		{
			SuiView$Switch*  __scopeVar_715_12 = SuiView$mkSwitch(&tmpReturn_5, o, 0) , *o = __scopeVar_715_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_715_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			bool  checked = orc_getFieldInt(self->matl, key) ;
			o->setChecked(o, checked) ;
			URGC_VAR_CLEANUP Sgl$__Closure_718_37*  tmpReturn_6 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$Switch, onCheckedChanged) , __make___Closure_718_37(&tmpReturn_6, __var___Block_699_41) ) ;
		}
	}
}


void  Sgl$MaterialInsp$rowString(Sgl$MaterialInsp *  self, SuiCore$Node *  o, const char *  key){
	URGC_VAR_CLEANUP_CLASS Orc$String*  keyStr = Orc$str((keyStr = NULL,&keyStr), key) ;
	OrcMetaField *  mf = orc_getMetaFieldByObject(self->matl, key) ;
	if (!mf) {
		return ; 
	}
	if (!OrcMetaField_isStringRef(mf) ) {
		return ; 
	}
	Orc$String *  value = *((Orc$String ** )OrcMetaField_getPtr(mf, self->matl) );
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_739_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )mf) , *o = __scopeVar_739_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_739_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->border->b->set(((SuiCore$View * )o)->border->b, 1, 0x33000000) ;
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
		{
			SuiView$TextView*  __scopeVar_742_12 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_742_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_742_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 100;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setText(o, Orc$String$add(Orc$str(&tmpReturn_3, key) , ": ") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_4 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_746_12 = SuiView$mkDrawButton(&tmpReturn_4, o, 0) , *o = __scopeVar_746_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_746_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , value ? value : Orc$str(&tmpReturn_5, "null") ) ;
		}
	}
}


void  Sgl$MaterialInsp$react(Sgl$MaterialInsp *  self){
	URGC_VAR_CLEANUP Sgl$__Block_761_16*  __var___Block_761_16 = (__var___Block_761_16=NULL,urgc_init_var((void**)&__var___Block_761_16, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_761_16) , __finiBlock___Block_761_16) ));
	urgc_set_field_class(__var___Block_761_16, (void * )offsetof(Sgl$__Block_761_16, self) , self) ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_765_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_1 = NULL;
		{
			SuiView$ScrollArea*  __scopeVar_766_12 = SuiView$mkScrollArea(&tmpReturn_1, o, 0) , *o = __scopeVar_766_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_766_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "stretch") ;
			o->useMinWidthConstraint = true;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_773_16 = SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) , *o = __scopeVar_773_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_773_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_776_16 = SuiLayout$layoutLinear(&tmpReturn_3, o, 0) , *o = __scopeVar_776_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_776_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				Orc$String$set(o->direction, "column") ;
				Orc$String$set(o->alignItems, "stretch") ;
				self->rowString(self, o, "vsPath") ;
				self->rowString(self, o, "fsPath") ;
				self->rowBool(self, o, "depthTest") ;
				self->rowBool(self, o, "stencilTest") ;
				self->rowBool(self, o, "alphaTest") ;
				self->rowBool(self, o, "scissorTest") ;
				self->rowBool(self, o, "blend") ;
				self->rowBool(self, o, "cullFace") ;
				if (self->matl->shaderMeta) {
					URGC_VAR_CLEANUP_CLASS SuiView$Panel*  tmpReturn_4 = NULL;
					{
						SuiView$Panel*  __scopeVar_793_24 = SuiView$mkPanel(&tmpReturn_4, o, 0) , *o = __scopeVar_793_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_793_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP Sgl$__Closure_794_46*  tmpReturn_5 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$Panel, cbRenderTitle) , __make___Closure_794_46(&tmpReturn_5) ) ;
						URGC_VAR_CLEANUP Sgl$__Closure_799_48*  tmpReturn_6 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$Panel, cbRenderContent) , __make___Closure_799_48(&tmpReturn_6, __var___Block_761_16) ) ;
					}
				}
				if (0) {
					URGC_VAR_CLEANUP_CLASS SuiView$Panel*  tmpReturn_7 = NULL;
					{
						SuiView$Panel*  __scopeVar_1066_24 = SuiView$mkPanel(&tmpReturn_7, o, 0) , *o = __scopeVar_1066_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1066_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP Sgl$__Closure_1067_46*  tmpReturn_8 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$Panel, cbRenderTitle) , __make___Closure_1067_46(&tmpReturn_8) ) ;
						URGC_VAR_CLEANUP Sgl$__Closure_1072_48*  tmpReturn_9 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$Panel, cbRenderContent) , __make___Closure_1072_48(&tmpReturn_9, __var___Block_761_16) ) ;
					}
				}
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_10 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_1116_12 = SuiLayout$layoutLinear(&tmpReturn_10, o, 0) , *o = __scopeVar_1116_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1116_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			((SuiCore$View * )o)->border->t->set(((SuiCore$View * )o)->border->t, 1, 0x33666666) ;
			((SuiCore$View * )o)->height = 200;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_11 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_1121_16 = SuiLayout$layoutLinear(&tmpReturn_11, o, 0) , *o = __scopeVar_1121_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1121_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_12 = NULL;
				{
					SuiView$TextView*  __scopeVar_1122_20 = SuiView$mkTextView(&tmpReturn_12, o, 0) , *o = __scopeVar_1122_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1122_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
					o->setText(o, Orc$str(&tmpReturn_13, "预览") ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_14 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_14, o, 0) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_15 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_1127_20 = SuiView$mkDrawButton(&tmpReturn_15, o, 0) , *o = __scopeVar_1127_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1127_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_16, "选择模型") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_17 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_1130_20 = SuiView$mkDrawButton(&tmpReturn_17, o, 0) , *o = __scopeVar_1130_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1130_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_18, "加载") ) ;
					URGC_VAR_CLEANUP Sgl$__Closure_1132_36*  tmpReturn_19 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1132_36(&tmpReturn_19) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_20 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_1145_20 = SuiView$mkDrawButton(&tmpReturn_20, o, 0) , *o = __scopeVar_1145_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1145_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_21 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_21, "保存") ) ;
					URGC_VAR_CLEANUP Sgl$__Closure_1147_36*  tmpReturn_22 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1147_36(&tmpReturn_22, __var___Block_761_16) ) ;
				}
			}
			URGC_VAR_CLEANUP_CLASS Sgl$MaterialPreviewView*  tmpReturn_23 = NULL;
			{
				Sgl$MaterialPreviewView*  __scopeVar_1164_16 = Sgl$mkMaterialPreviewView(&tmpReturn_23, o, 0) , *o = __scopeVar_1164_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1164_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->backgroundColor = 0xff222222;
				((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
				if (o->matl != self->matl) {
					urgc_set_field_class(o, (void * )offsetof(Sgl$MaterialPreviewView, matl) , self->matl) ;
					o->buildDrawObj(o) ;
				}
				urgc_set_field_class(self, (void * )offsetof(Sgl$MaterialInsp, glPreviewView) , o) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_24 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_24, o, 0) ;
			}
		}
	}
}


void  Sgl$MaterialInsp$showWindow(Sgl$MaterialInsp *  self, Sgl$Material*  matl){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(matl);

	urgc_set_field_class(self, (void * )offsetof(Sgl$MaterialInsp, matl) , matl) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(self, (void * )offsetof(Sgl$MaterialInsp, win) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1184_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			self->win->setRootView(self->win, o) ;
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 6) ;
		}
		self->react(self) ;
		o->setTitle(o, "材质") ;
		o->setSize(o, 400, 480) ;
		o->show(o) ;
	}
}




//vtable instance
Vtable_Sgl$UniformMeta _vtable_Sgl$UniformMeta;

// init meta

void Sgl$UniformMeta_initMeta(Vtable_Sgl$UniformMeta *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$UniformMeta, name), true, false, 1);
	orc_metaField_class(&pNext, "type", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$UniformMeta, type), true, false, 1);
	orc_metaField_class(&pNext, "editor", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$UniformMeta, editor), true, false, 1);
	orc_metaField_class(&pNext, "defaultValue", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$UniformMeta, defaultValue), true, false, 1);

	
}


// vtable init


Vtable_Sgl$UniformMeta* Vtable_Sgl$UniformMeta_init(Vtable_Sgl$UniformMeta* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$UniformMeta;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$UniformMeta_new;
    ((Vtable_Object*)pvt)->className = "Sgl$UniformMeta";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$UniformMeta_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$UniformMeta_fini(Sgl$UniformMeta *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$UniformMeta_init_fields(Sgl$UniformMeta *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$UniformMeta_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$UniformMeta*)self)->name, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$UniformMeta*)self)->type, Orc$str(&tmpReturn_2, "") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$UniformMeta*)self)->editor, Orc$str(&tmpReturn_3, "") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$UniformMeta*)self)->defaultValue, Orc$str(&tmpReturn_4, "") );
    }
	
}

// init function

void Sgl$UniformMeta_init(Sgl$UniformMeta *self, void *pOwner){
    Vtable_Sgl$UniformMeta_init(&_vtable_Sgl$UniformMeta);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$UniformMeta;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$UniformMeta_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$UniformMeta * Sgl$UniformMeta_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$UniformMeta *self = calloc(1, sizeof(Sgl$UniformMeta));
	
    Sgl$UniformMeta_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_Sgl$ShaderMeta _vtable_Sgl$ShaderMeta;

// init meta

void Sgl$ShaderMeta_initMeta(Vtable_Sgl$ShaderMeta *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "vsPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$ShaderMeta, vsPath), true, false, 1);
	orc_metaField_class(&pNext, "vsCode", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$ShaderMeta, vsCode), true, false, 1);
	orc_metaField_class(&pNext, "fsPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$ShaderMeta, fsPath), true, false, 1);
	orc_metaField_class(&pNext, "fsCode", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$ShaderMeta, fsCode), true, false, 1);
	orc_metaField_class(&pNext, "uniformMetas", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$ShaderMeta, uniformMetas), true, false, 1);

	orc_metaField_method(&pNext, "getUniformMeta", offsetof(Sgl$ShaderMeta, getUniformMeta));
	orc_metaField_method(&pNext, "parseCode", offsetof(Sgl$ShaderMeta, parseCode));
	orc_metaField_method(&pNext, "parseFsByPathCstr", offsetof(Sgl$ShaderMeta, parseFsByPathCstr));
	orc_metaField_method(&pNext, "parseVsByPathCstr", offsetof(Sgl$ShaderMeta, parseVsByPathCstr));
}


// vtable init


Vtable_Sgl$ShaderMeta* Vtable_Sgl$ShaderMeta_init(Vtable_Sgl$ShaderMeta* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$ShaderMeta;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$ShaderMeta_new;
    ((Vtable_Object*)pvt)->className = "Sgl$ShaderMeta";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$ShaderMeta_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$ShaderMeta_fini(Sgl$ShaderMeta *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void Sgl$ShaderMeta_init_fields(Sgl$ShaderMeta *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$ShaderMeta_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$ShaderMeta*)self)->vsPath, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$ShaderMeta*)self)->vsCode, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$ShaderMeta*)self)->fsPath, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$ShaderMeta*)self)->fsCode, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ShaderMeta*)self)->uniformMetas, Orc$List_new(&tmpNewOwner_1) );
    }
	((Sgl$ShaderMeta*)self)->getUniformMeta = (void*)Sgl$ShaderMeta$getUniformMeta;
	((Sgl$ShaderMeta*)self)->parseCode = (void*)Sgl$ShaderMeta$parseCode;
	((Sgl$ShaderMeta*)self)->parseFsByPathCstr = (void*)Sgl$ShaderMeta$parseFsByPathCstr;
	((Sgl$ShaderMeta*)self)->parseVsByPathCstr = (void*)Sgl$ShaderMeta$parseVsByPathCstr;
}

// init function

void Sgl$ShaderMeta_init(Sgl$ShaderMeta *self, void *pOwner){
    Vtable_Sgl$ShaderMeta_init(&_vtable_Sgl$ShaderMeta);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$ShaderMeta;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$ShaderMeta_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$ShaderMeta * Sgl$ShaderMeta_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$ShaderMeta *self = calloc(1, sizeof(Sgl$ShaderMeta));
	
    Sgl$ShaderMeta_init(self, pOwner);
    return self;
}


// class members
Sgl$UniformMeta*  Sgl$ShaderMeta$getUniformMeta(Sgl$UniformMeta **  __outRef__, Sgl$ShaderMeta *  self, const char *  name){
	int  l = self->uniformMetas->size(self->uniformMetas) ;
	for (int  i = 0; i < l; i++) {
		Sgl$UniformMeta *  um = (Sgl$UniformMeta * )self->uniformMetas->get(self->uniformMetas, i) ;
		if (Orc$String$equals(um->name, name) ) {
			return urgc_set_var_for_return_class((void ** )__outRef__, um) ; 
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


void  Sgl$ShaderMeta$parseCode(Sgl$ShaderMeta *  self, Orc$String *  code){
	if (code == NULL || Orc$String$empty(code) ) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  lines = Orc$String$splitToLines((lines = NULL,&lines), code) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  editor = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  defaultValue = NULL;
	for (int  i = 0; i < lines->size(lines) ; i++) {
		Orc$String *  line = (Orc$String * )lines->get(lines, i) ;
		if (Orc$String$startsWith(line, "//@default ") ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			urgc_set_var_class(&defaultValue, Orc$String$trim(&tmpReturn_1, Orc$String$substringByByteStart(&tmpReturn_2, line, 11) ) ) ;
		}
		else if (Orc$String$startsWith(line, "//@editor ") ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			urgc_set_var_class(&editor, Orc$String$trim(&tmpReturn_3, Orc$String$substringByByteStart(&tmpReturn_4, line, 10) ) ) ;
		}
		else if (Orc$String$startsWith(line, "uniform ") ) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  parts = Orc$String$splitByRe((parts = NULL,&parts), line, "\\s+|;") ;
			if (parts->size(parts)  >= 3) {
				Orc$String *  typeName = (Orc$String * )parts->get(parts, 1) ;
				Orc$String *  name = (Orc$String * )parts->get(parts, 2) ;
				URGC_VAR_CLEANUP_CLASS Sgl$UniformMeta*  tmpReturn_5 = NULL;
				Sgl$UniformMeta *  oldUm = self->getUniformMeta(&tmpReturn_5, self, name->str) ;
				if (oldUm) {
					if (Orc$String$notEmpty(oldUm->editor)  || Orc$String$notEmpty(oldUm->defaultValue) ) {
						urgc_set_var_class(&defaultValue, NULL) ;
						urgc_set_var_class(&editor, NULL) ;
						continue;
					}
					self->uniformMetas->remove(self->uniformMetas, oldUm) ;
					printf("\tremove old uniform: %s\n", name->str) ;
				}
				URGC_VAR_CLEANUP_CLASS Sgl$UniformMeta*  um = (um=NULL,urgc_init_var_class((void**)&um, Sgl$UniformMeta_new(&um) ));
				urgc_set_field_class(um, (void * )offsetof(Sgl$UniformMeta, name) , name) ;
				urgc_set_field_class(um, (void * )offsetof(Sgl$UniformMeta, type) , typeName) ;
				if (editor) {
					urgc_set_field_class(um, (void * )offsetof(Sgl$UniformMeta, editor) , editor) ;
				}
				if (defaultValue) {
					urgc_set_field_class(um, (void * )offsetof(Sgl$UniformMeta, defaultValue) , defaultValue) ;
				}
				self->uniformMetas->add(self->uniformMetas, um) ;
				urgc_set_var_class(&defaultValue, NULL) ;
				urgc_set_var_class(&editor, NULL) ;
				printf("uniform: %s, type: %s, editor:%s default: %s\n", um->name->str, um->type->str, um->editor->str, um->defaultValue->str) ;
			}
		}
	}
}


void  Sgl$ShaderMeta$parseFsByPathCstr(Sgl$ShaderMeta *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$ShaderMeta, fsPath) , Orc$str(&tmpReturn_1, path) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  code = Orc$Path_readText((code = NULL,&code), path) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$ShaderMeta, fsCode) , code) ;
	self->parseCode(self, code) ;
}


void  Sgl$ShaderMeta$parseVsByPathCstr(Sgl$ShaderMeta *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$ShaderMeta, vsPath) , Orc$str(&tmpReturn_1, path) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  code = Orc$Path_readText((code = NULL,&code), path) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$ShaderMeta, vsCode) , code) ;
	self->parseCode(self, code) ;
}




//vtable instance
Vtable_Sgl$MaterialPreviewView _vtable_Sgl$MaterialPreviewView;

// init meta

void Sgl$MaterialPreviewView_initMeta(Vtable_Sgl$MaterialPreviewView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(Sgl$MaterialPreviewView, fbo), true, false, 1);
	orc_metaField_class(&pNext, "matl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(Sgl$MaterialPreviewView, matl), true, false, 1);
	orc_metaField_class(&pNext, "drawObj", ((Vtable_Object*)Vtable_Sgl$Draw_init(0)), offsetof(Sgl$MaterialPreviewView, drawObj), true, false, 1);
	orc_metaField_primitive(&pNext, "rotateY", OrcMetaType_float, offsetof(Sgl$MaterialPreviewView, rotateY), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "scale", OrcMetaType_float, offsetof(Sgl$MaterialPreviewView, scale), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(Sgl$MaterialPreviewView, drag), true, false, 1);

	orc_metaField_method(&pNext, "buildDrawObj", offsetof(Sgl$MaterialPreviewView, buildDrawObj));
	orc_metaField_method(&pNext, "applyModel", offsetof(Sgl$MaterialPreviewView, applyModel));
}


// vtable init


Vtable_Sgl$MaterialPreviewView* Vtable_Sgl$MaterialPreviewView_init(Vtable_Sgl$MaterialPreviewView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$MaterialPreviewView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiView$ImageView_init(&_vtable_SuiView$ImageView);

	// init by super vtable init function
    Vtable_SuiView$ImageView_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiView$ImageView;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$MaterialPreviewView_new;
    ((Vtable_Object*)pvt)->className = "Sgl$MaterialPreviewView";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$MaterialPreviewView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$MaterialPreviewView_fini(Sgl$MaterialPreviewView *self){
	//super fini
    SuiView$ImageView_fini((SuiView$ImageView *)self);

    //字段释放


}

// init fields function


void Sgl$MaterialPreviewView_init_fields(Sgl$MaterialPreviewView *self){
	//super class
    SuiView$ImageView_init_fields((SuiView$ImageView*)self);

    ((Object*)self)->fini = (void*)Sgl$MaterialPreviewView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$MaterialPreviewView*)self)->fbo, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$MaterialPreviewView*)self)->matl, NULL);
	urgc_set_field_class(self, (void**)&((Sgl$MaterialPreviewView*)self)->drawObj, NULL);
	((Sgl$MaterialPreviewView*)self)->rotateY = 0;
	((Sgl$MaterialPreviewView*)self)->scale = 0.02;
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$MaterialPreviewView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
    }
	((Sgl$MaterialPreviewView*)self)->buildDrawObj = (void*)Sgl$MaterialPreviewView$buildDrawObj;
	((SuiCore$ViewBase*)self)->draw_self = (void*)Sgl$MaterialPreviewView$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)Sgl$MaterialPreviewView$onEvent;
	((Sgl$MaterialPreviewView*)self)->applyModel = (void*)Sgl$MaterialPreviewView$applyModel;
}

// init function

void Sgl$MaterialPreviewView_init(Sgl$MaterialPreviewView *self, void *pOwner){
    Vtable_Sgl$MaterialPreviewView_init(&_vtable_Sgl$MaterialPreviewView);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$MaterialPreviewView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$MaterialPreviewView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$MaterialPreviewView * Sgl$MaterialPreviewView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$MaterialPreviewView *self = calloc(1, sizeof(Sgl$MaterialPreviewView));
	
    Sgl$MaterialPreviewView_init(self, pOwner);
    return self;
}


// class members
void  Sgl$MaterialPreviewView$buildDrawObj(Sgl$MaterialPreviewView *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$ObjLoader*  loader = (loader=NULL,urgc_init_var_class((void**)&loader, Sgl$ObjLoader_new(&loader) ));
	loader->load(loader, "../assimp/test/models/OBJ/spider.obj") ;
	URGC_VAR_CLEANUP_CLASS Sgl$Draw*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$MaterialPreviewView, drawObj) , Sgl$Draw_new(&tmpNewOwner_1) ) ;
	urgc_set_field_class(self->drawObj, (void * )offsetof(Sgl$Draw, material) , self->matl) ;
	self->drawObj->buildGeometryByJsonPathCstr(self->drawObj, "../asset/TriangleFix.json") ;
	Sgl$Material *  o = self->matl;
	Sgl$Mat$lookAtFake(&o->view, SuiCore$mkVec3(0, 2000, 1000) , SuiCore$mkVec3(0, 0, 0) , SuiCore$mkVec3(0, 1, 0) ) ;
	Sgl$Mat$perspective(&o->projection, 45 / 180.0 * 3.1415926, 1.0, 0.1, 10000) ;
	printf("mk draw succ\n") ;
}


void  Sgl$MaterialPreviewView$draw_self(Sgl$MaterialPreviewView *  self, SuiCore$Canvas *  canvas){
	{
		bool  mkFbo = false;
		if (self->drawObj && self->fbo == NULL) {
			mkFbo = true;
		}
		else if (self->fbo) {
			SuiCore$Vec2 size = self->fbo->getSize(self->fbo) ;
			if (size.x != (int )((SuiCore$ViewBase * )self)->frame.width || size.y != (int )((SuiCore$ViewBase * )self)->frame.height) {
				mkFbo = true;
			}
		}
		if (mkFbo) {
			printf("重建fbo. size:%f,%f\n", ((SuiCore$ViewBase * )self)->frame.width, ((SuiCore$ViewBase * )self)->frame.height) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  tmpNewOwner_1 = NULL;
			urgc_set_field_class(self, (void * )offsetof(Sgl$MaterialPreviewView, fbo) , Sgl$Fbo_new(&tmpNewOwner_1) ) ;
			self->fbo->buildWithColorDepthStencil(self->fbo, (int )((SuiCore$ViewBase * )self)->frame.width, (int )((SuiCore$ViewBase * )self)->frame.height) ;
		}
	}
	if (self->fbo) {
		self->fbo->startDraw(self->fbo, 0.0, 0.0, 0.0, 1.0, true, true, true) ;
		self->drawObj->draw(self->drawObj) ;
		self->fbo->endDraw(self->fbo) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ImageView, _img) , Sgl$loadImageByTex2d(&tmpReturn_2, self->fbo->tex2d) ) ;
	}
	SuiView$ImageView$draw_self(self, canvas) ;
}


void  Sgl$MaterialPreviewView$onEvent(Sgl$MaterialPreviewView *  self, SuiCore$Event *  e){
	URGC_VAR_CLEANUP Sgl$__Block_1370_26*  __var___Block_1370_26 = (__var___Block_1370_26=NULL,urgc_init_var((void**)&__var___Block_1370_26, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_1370_26) , __finiBlock___Block_1370_26) ));
	urgc_set_field_class(__var___Block_1370_26, (void * )offsetof(Sgl$__Block_1370_26, self) , self) ;
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->isMouseDown) {
			URGC_VAR_CLEANUP Sgl$__Closure_1374_35*  tmpReturn_1 = NULL;
			urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_1374_35(&tmpReturn_1, __var___Block_1370_26) ) ;
			self->drag->onMouseDown(self->drag, me) ;
		}
	}
}


void  Sgl$MaterialPreviewView$applyModel(Sgl$MaterialPreviewView *  self){
	if (self->drawObj && self->drawObj->material) {
		{
			Sgl$Mat *  o = &self->drawObj->material->model;
			
		
			Sgl$Mat$identity(o) ;
			Sgl$Mat$rotateY(o, self->rotateY) ;
			Sgl$Mat$scale(o, self->scale, self->scale, self->scale) ;
		}
	}
}



static void  __finiBlock___Block_126_35(Sgl$__Block_126_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_126_35, path) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_316_25(Sgl$__Block_316_25 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_316_25, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_678_23(Sgl$__Block_678_23 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_678_23, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_699_41(Sgl$__Block_699_41 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_699_41, self) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_699_41, keyStr) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_761_16(Sgl$__Block_761_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_761_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_801_57(Sgl$__Block_801_57 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_801_57, ui) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1370_26(Sgl$__Block_1370_26 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_1370_26, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_94_34(Sgl$__Closure_94_34 *  self, int  newcolor){
	SuiCore$Rgbaf nv = SuiCore$mkRgbafByInt(newcolor) ;
}

static void  __fini___Closure_94_34(Sgl$__Closure_94_34 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_94_34*  __make___Closure_94_34(Sgl$__Closure_94_34 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_94_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_94_34) , __fini___Closure_94_34) ));
	self->invoke = __fn___Closure_94_34;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_106_41(Sgl$__Closure_106_41 *  self, SuiCore$Vec2 nv){
	
}

static void  __fini___Closure_106_41(Sgl$__Closure_106_41 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_106_41*  __make___Closure_106_41(Sgl$__Closure_106_41 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_106_41*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_106_41) , __fini___Closure_106_41) ));
	self->invoke = __fn___Closure_106_41;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_114_41(Sgl$__Closure_114_41 *  self, SuiCore$Vec3 nv){
	
}

static void  __fini___Closure_114_41(Sgl$__Closure_114_41 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_114_41*  __make___Closure_114_41(Sgl$__Closure_114_41 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_114_41*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_114_41) , __fini___Closure_114_41) ));
	self->invoke = __fn___Closure_114_41;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_123_41(Sgl$__Closure_123_41 *  self, SuiCore$Vec4 nv){
	
}

static void  __fini___Closure_123_41(Sgl$__Closure_123_41 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_123_41*  __make___Closure_123_41(Sgl$__Closure_123_41 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_123_41*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_123_41) , __fini___Closure_123_41) ));
	self->invoke = __fn___Closure_123_41;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_135_34(Sgl$__Closure_135_34 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			SuiDialog$Toast_make(Orc$String$addString(Orc$str(&tmpReturn_1, "click image") , self->__var___Block_126_35->path) ->str) ;
		}
	}
}

static void  __fini___Closure_135_34(Sgl$__Closure_135_34 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_135_34, __var___Block_126_35) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_135_34*  __make___Closure_135_34(Sgl$__Closure_135_34 **  __outRef__, Sgl$__Block_126_35 *  __var___Block_126_35){
	URGC_VAR_CLEANUP Sgl$__Closure_135_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_135_34) , __fini___Closure_135_34) ));
	self->invoke = __fn___Closure_135_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_135_34, __var___Block_126_35) , __var___Block_126_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_321_25(Sgl$__Closure_321_25 *  self, SuiDesigner$Insp *  insp, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiView$Panel2*  tmpReturn_1 = NULL;
	{
		SuiView$Panel2*  __scopeVar_322_12 = SuiView$mkPanel2(&tmpReturn_1, o, 0) , *o = __scopeVar_322_12;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_322_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiView$Panel2, title) , Orc$str(&tmpReturn_2, "uniforms") ) ;
		for (int  i = 0; i < self->__var___Block_316_25->self->uniforms->size(self->__var___Block_316_25->self->uniforms) ; i++) {
			Sgl$UniformInfo *  uinfo = (Sgl$UniformInfo * )self->__var___Block_316_25->self->uniforms->get(self->__var___Block_316_25->self->uniforms, i) ;
			uinfo->inspAsValue(uinfo, insp, o, self->__var___Block_316_25->self) ;
		}
	}
}

static void  __fini___Closure_321_25(Sgl$__Closure_321_25 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_321_25, __var___Block_316_25) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_321_25*  __make___Closure_321_25(Sgl$__Closure_321_25 **  __outRef__, Sgl$__Block_316_25 *  __var___Block_316_25){
	URGC_VAR_CLEANUP Sgl$__Closure_321_25*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_321_25) , __fini___Closure_321_25) ));
	self->invoke = __fn___Closure_321_25;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_321_25, __var___Block_316_25) , __var___Block_316_25) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_683_30(Sgl$__Closure_683_30 *  self){
	self->__var___Block_678_23->self->_reactDirty = false;
	self->__var___Block_678_23->self->react(self->__var___Block_678_23->self) ;
	return true; 
}

static void  __fini___Closure_683_30(Sgl$__Closure_683_30 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_683_30, __var___Block_678_23) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_683_30*  __make___Closure_683_30(Sgl$__Closure_683_30 **  __outRef__, Sgl$__Block_678_23 *  __var___Block_678_23){
	URGC_VAR_CLEANUP Sgl$__Closure_683_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_683_30) , __fini___Closure_683_30) ));
	self->invoke = __fn___Closure_683_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_683_30, __var___Block_678_23) , __var___Block_678_23) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_718_37(Sgl$__Closure_718_37 *  self, SuiView$Switch *  ins){
	orc_setFieldInt(self->__var___Block_699_41->self->matl, self->__var___Block_699_41->keyStr->str, ins->checked) ;
	self->__var___Block_699_41->self->invalidReact(self->__var___Block_699_41->self) ;
}

static void  __fini___Closure_718_37(Sgl$__Closure_718_37 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_718_37, __var___Block_699_41) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_718_37*  __make___Closure_718_37(Sgl$__Closure_718_37 **  __outRef__, Sgl$__Block_699_41 *  __var___Block_699_41){
	URGC_VAR_CLEANUP Sgl$__Closure_718_37*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_718_37) , __fini___Closure_718_37) ));
	self->invoke = __fn___Closure_718_37;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_718_37, __var___Block_699_41) , __var___Block_699_41) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_794_46(Sgl$__Closure_794_46 *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_795_32 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_795_32;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_795_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setText(o, Orc$str(&tmpReturn_2, "shader uniform") ) ;
	}
}

static void  __fini___Closure_794_46(Sgl$__Closure_794_46 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_794_46*  __make___Closure_794_46(Sgl$__Closure_794_46 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_794_46*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_794_46) , __fini___Closure_794_46) ));
	self->invoke = __fn___Closure_794_46;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_799_48(Sgl$__Closure_799_48 *  self, SuiCore$Node *  o){
	int  l = self->__var___Block_761_16->self->matl->shaderMeta->uniformMetas->size(self->__var___Block_761_16->self->matl->shaderMeta->uniformMetas) ;
	for (int  i = 0; i < l; i++) {
		URGC_VAR_CLEANUP Sgl$__Block_801_57*  __var___Block_801_57 = (__var___Block_801_57=NULL,urgc_init_var((void**)&__var___Block_801_57, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_801_57) , __finiBlock___Block_801_57) ));
		__var___Block_801_57->um = (Sgl$UniformMeta * )self->__var___Block_761_16->self->matl->shaderMeta->uniformMetas->get(self->__var___Block_761_16->self->matl->shaderMeta->uniformMetas, i) ;
		if (Orc$String$equals(__var___Block_801_57->um->type, "mat4") ) {
			continue;
		}
		URGC_VAR_CLEANUP_CLASS Sgl$UniformInfo*  tmpReturn_1 = NULL;
		urgc_set_field_class(__var___Block_801_57, (void * )offsetof(Sgl$__Block_801_57, ui) , self->__var___Block_761_16->self->matl->getUniformInfo(&tmpReturn_1, self->__var___Block_761_16->self->matl, __var___Block_801_57->um->name->str) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_810_36 = SuiLayout$layoutLinear(&tmpReturn_2, o, (long long )__var___Block_801_57->ui) , *o = __scopeVar_810_36;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_810_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->border->b->set(((SuiCore$View * )o)->border->b, 1, 0x33000000) ;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_3 = NULL;
			{
				SuiView$TextView*  __scopeVar_812_40 = SuiView$mkTextView(&tmpReturn_3, o, 0) , *o = __scopeVar_812_40;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_812_40 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->width = 100;
				URGC_VAR_CLEANUP Sgl$__Closure_814_58*  tmpReturn_4 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_814_58(&tmpReturn_4, __var___Block_801_57) ) ;
				o->setText(o, __var___Block_801_57->um->name) ;
			}
			if (Orc$String$equals(__var___Block_801_57->um->editor, "Color4f") ) {
				URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_5 = NULL;
				{
					SuiView$ColorPicker*  __scopeVar_845_44 = SuiView$mkColorPicker(&tmpReturn_5, o, o) , *o = __scopeVar_845_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_845_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					if (__var___Block_801_57->ui) {
						SuiCore$Rgba c = __var___Block_801_57->ui->getColor(__var___Block_801_57->ui) ;
						((SuiCore$View * )o)->backgroundColor = SuiCore$Rgba$toInt(&c) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_850_62*  tmpReturn_6 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_850_62(&tmpReturn_6, self->__var___Block_761_16, __var___Block_801_57) ) ;
				}
			}
			else if (Orc$String$equals(__var___Block_801_57->um->editor, "Color3f") ) {
				URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_7 = NULL;
				{
					SuiView$ColorPicker*  __scopeVar_858_44 = SuiView$mkColorPicker(&tmpReturn_7, o, o) , *o = __scopeVar_858_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_858_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					if (__var___Block_801_57->ui) {
						SuiCore$Rgba c = __var___Block_801_57->ui->getColor(__var___Block_801_57->ui) ;
						((SuiCore$View * )o)->backgroundColor = SuiCore$Rgba$toInt(&c) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_863_62*  tmpReturn_8 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$ColorPicker, onChanged) , __make___Closure_863_62(&tmpReturn_8, self->__var___Block_761_16, __var___Block_801_57) ) ;
				}
			}
			else if (Orc$String$equals(__var___Block_801_57->um->type, "float") ) {
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_9 = NULL;
				{
					SuiView$EditText*  __scopeVar_871_44 = SuiView$mkEditText(&tmpReturn_9, o, 0) , *o = __scopeVar_871_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_871_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_1 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_1 = SuiCore$insFocus() )->isFocus(tmpThis_1, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[0]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_877_67*  tmpReturn_10 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_877_67(&tmpReturn_10, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_11 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_11, o, 0) ;
				}
			}
			else if (Orc$String$equals(__var___Block_801_57->um->type, "vec2") ) {
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_12 = NULL;
				{
					SuiView$EditText*  __scopeVar_888_44 = SuiView$mkEditText(&tmpReturn_12, o, 0) , *o = __scopeVar_888_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_888_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_2 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_2 = SuiCore$insFocus() )->isFocus(tmpThis_2, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[0]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_894_67*  tmpReturn_13 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_894_67(&tmpReturn_13, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_14 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_14, o, 0) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_15 = NULL;
				{
					SuiView$EditText*  __scopeVar_904_44 = SuiView$mkEditText(&tmpReturn_15, o, 0) , *o = __scopeVar_904_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_904_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_3 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_3 = SuiCore$insFocus() )->isFocus(tmpThis_3, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[1]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_910_67*  tmpReturn_16 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_910_67(&tmpReturn_16, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_17 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_17, o, 0) ;
				}
			}
			else if (Orc$String$equals(__var___Block_801_57->um->type, "vec3") ) {
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_18 = NULL;
				{
					SuiView$EditText*  __scopeVar_922_44 = SuiView$mkEditText(&tmpReturn_18, o, 0) , *o = __scopeVar_922_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_922_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_4 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_4 = SuiCore$insFocus() )->isFocus(tmpThis_4, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[0]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_928_67*  tmpReturn_19 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_928_67(&tmpReturn_19, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_20 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_20, o, 0) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_21 = NULL;
				{
					SuiView$EditText*  __scopeVar_939_44 = SuiView$mkEditText(&tmpReturn_21, o, 0) , *o = __scopeVar_939_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_939_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_5 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_5 = SuiCore$insFocus() )->isFocus(tmpThis_5, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[1]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_945_67*  tmpReturn_22 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_945_67(&tmpReturn_22, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_23 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_23, o, 0) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_24 = NULL;
				{
					SuiView$EditText*  __scopeVar_956_44 = SuiView$mkEditText(&tmpReturn_24, o, 0) , *o = __scopeVar_956_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_956_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_6 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_6 = SuiCore$insFocus() )->isFocus(tmpThis_6, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[2]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_962_67*  tmpReturn_25 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_962_67(&tmpReturn_25, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_26 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_26, o, 0) ;
				}
			}
			else if (Orc$String$equals(__var___Block_801_57->um->type, "vec4") ) {
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_27 = NULL;
				{
					SuiView$EditText*  __scopeVar_975_44 = SuiView$mkEditText(&tmpReturn_27, o, 0) , *o = __scopeVar_975_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_975_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_7 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_7 = SuiCore$insFocus() )->isFocus(tmpThis_7, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[0]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_981_67*  tmpReturn_28 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_981_67(&tmpReturn_28, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_29 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_29, o, 0) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_30 = NULL;
				{
					SuiView$EditText*  __scopeVar_993_44 = SuiView$mkEditText(&tmpReturn_30, o, 0) , *o = __scopeVar_993_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_993_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_8 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_8 = SuiCore$insFocus() )->isFocus(tmpThis_8, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[1]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_999_67*  tmpReturn_31 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_999_67(&tmpReturn_31, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_32 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_32, o, 0) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_33 = NULL;
				{
					SuiView$EditText*  __scopeVar_1011_44 = SuiView$mkEditText(&tmpReturn_33, o, 0) , *o = __scopeVar_1011_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1011_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_9 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_9 = SuiCore$insFocus() )->isFocus(tmpThis_9, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[2]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_1017_67*  tmpReturn_34 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1017_67(&tmpReturn_34, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_35 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_35, o, 0) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_36 = NULL;
				{
					SuiView$EditText*  __scopeVar_1029_44 = SuiView$mkEditText(&tmpReturn_36, o, 0) , *o = __scopeVar_1029_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1029_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					SuiCore$Focus *  tmpThis_10 = NULL;
					if (__var___Block_801_57->ui && !(tmpThis_10 = SuiCore$insFocus() )->isFocus(tmpThis_10, o) ) {
						URGC_VAR_CLEANUP_CLASS Orc$String*  t = Orc$str((t = NULL,&t), "") ;
						Orc$String$addf(t, __var___Block_801_57->ui->floatValues[3]) ;
						o->set_value(o, t, false) ;
					}
					URGC_VAR_CLEANUP Sgl$__Closure_1035_67*  tmpReturn_37 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_1035_67(&tmpReturn_37, self->__var___Block_761_16, __var___Block_801_57) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_38 = NULL;
					SuiLayout$layoutLinearCell(&tmpReturn_38, o, 0) ;
				}
			}
			else if (Orc$String$equals(__var___Block_801_57->um->type, "sampler2D") ) {
				URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_39 = NULL;
				{
					SuiView$ImageView*  __scopeVar_1049_44 = SuiView$mkImageView(&tmpReturn_39, o, 0) , *o = __scopeVar_1049_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1049_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->backgroundColor = 0x11333333;
					SuiCore$Inset$setVer(&((SuiCore$View * )o)->margin, 6) ;
					((SuiCore$View * )o)->width = 60;
					((SuiCore$View * )o)->height = 60;
					((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0x33333333) ;
					o->setImageMode(o, SuiView$Contain) ;
					URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_40 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$ImageView, _img) , __var___Block_801_57->ui && __var___Block_801_57->ui->tex ? Sgl$loadImageByTex2d(&tmpReturn_40, __var___Block_801_57->ui->tex)  : NULL) ;
				}
			}
		}
	}
}

static void  __fini___Closure_799_48(Sgl$__Closure_799_48 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_799_48, __var___Block_761_16) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_799_48*  __make___Closure_799_48(Sgl$__Closure_799_48 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16){
	URGC_VAR_CLEANUP Sgl$__Closure_799_48*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_799_48) , __fini___Closure_799_48) ));
	self->invoke = __fn___Closure_799_48;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_799_48, __var___Block_761_16) , __var___Block_761_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_814_58(Sgl$__Closure_814_58 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP Sgl$__Closure_onActive_818*  tmpReturn_1 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_818(&tmpReturn_1) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_822_60 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$String$addString(Orc$str(&tmpReturn_5, "type:") , self->__var___Block_801_57->um->type) , onActive) , *o = __scopeVar_822_60;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_823_60 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$String$addString(Orc$str(&tmpReturn_7, "default:") , self->__var___Block_801_57->um->defaultValue) , onActive) , *o = __scopeVar_823_60;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
				n->create(n, o) ;
				n->showAtMouse(n) ;
			}
		}
	}
}

static void  __fini___Closure_814_58(Sgl$__Closure_814_58 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_814_58, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_814_58*  __make___Closure_814_58(Sgl$__Closure_814_58 **  __outRef__, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_814_58*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_814_58) , __fini___Closure_814_58) ));
	self->invoke = __fn___Closure_814_58;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_814_58, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_818(Sgl$__Closure_onActive_818 *  self, SuiView$MenuNativeItem *  item){
	SuiDialog$Toast_make("HI") ;
}

static void  __fini___Closure_onActive_818(Sgl$__Closure_onActive_818 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_onActive_818*  __make___Closure_onActive_818(Sgl$__Closure_onActive_818 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_onActive_818*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_onActive_818) , __fini___Closure_onActive_818) ));
	self->invoke = __fn___Closure_onActive_818;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_850_62(Sgl$__Closure_850_62 *  self, int  newcolor){
	SuiCore$Rgbaf c = SuiCore$mkRgbafByInt(newcolor) ;
	self->__var___Block_761_16->self->matl->setUniform4f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, c.r, c.g, c.b, c.a) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("更新颜色:%s\n", SuiCore$Rgbaf$toString(&tmpReturn_1, &c) ->str) ;
}

static void  __fini___Closure_850_62(Sgl$__Closure_850_62 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_850_62, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_850_62, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_850_62*  __make___Closure_850_62(Sgl$__Closure_850_62 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_850_62*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_850_62) , __fini___Closure_850_62) ));
	self->invoke = __fn___Closure_850_62;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_850_62, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_850_62, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_863_62(Sgl$__Closure_863_62 *  self, int  newcolor){
	SuiCore$Rgbaf c = SuiCore$mkRgbafByInt(newcolor) ;
	self->__var___Block_761_16->self->matl->setUniform3f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, c.r, c.g, c.b) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("更新颜色:%s\n", SuiCore$Rgbaf$toString(&tmpReturn_1, &c) ->str) ;
}

static void  __fini___Closure_863_62(Sgl$__Closure_863_62 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_863_62, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_863_62, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_863_62*  __make___Closure_863_62(Sgl$__Closure_863_62 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_863_62*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_863_62) , __fini___Closure_863_62) ));
	self->invoke = __fn___Closure_863_62;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_863_62, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_863_62, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_877_67(Sgl$__Closure_877_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform1f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, Orc$String$toFloat(et->value) ) ;
	printf("更新float:%s\n", et->value->str) ;
}

static void  __fini___Closure_877_67(Sgl$__Closure_877_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_877_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_877_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_877_67*  __make___Closure_877_67(Sgl$__Closure_877_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_877_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_877_67) , __fini___Closure_877_67) ));
	self->invoke = __fn___Closure_877_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_877_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_877_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_894_67(Sgl$__Closure_894_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform2f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, Orc$String$toFloat(et->value) , self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[1] : 0) ;
	printf("更新vec2:%s\n", et->value->str) ;
}

static void  __fini___Closure_894_67(Sgl$__Closure_894_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_894_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_894_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_894_67*  __make___Closure_894_67(Sgl$__Closure_894_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_894_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_894_67) , __fini___Closure_894_67) ));
	self->invoke = __fn___Closure_894_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_894_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_894_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_910_67(Sgl$__Closure_910_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform2f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[0] : 0, Orc$String$toFloat(et->value) ) ;
	printf("更新vec2:%s\n", et->value->str) ;
}

static void  __fini___Closure_910_67(Sgl$__Closure_910_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_910_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_910_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_910_67*  __make___Closure_910_67(Sgl$__Closure_910_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_910_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_910_67) , __fini___Closure_910_67) ));
	self->invoke = __fn___Closure_910_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_910_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_910_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_928_67(Sgl$__Closure_928_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform3f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, Orc$String$toFloat(et->value) , self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[1] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[2] : 0) ;
	printf("更新vec3:%s\n", et->value->str) ;
}

static void  __fini___Closure_928_67(Sgl$__Closure_928_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_928_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_928_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_928_67*  __make___Closure_928_67(Sgl$__Closure_928_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_928_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_928_67) , __fini___Closure_928_67) ));
	self->invoke = __fn___Closure_928_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_928_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_928_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_945_67(Sgl$__Closure_945_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform3f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[0] : 0, Orc$String$toFloat(et->value) , self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[2] : 0) ;
	printf("更新vec3:%s\n", et->value->str) ;
}

static void  __fini___Closure_945_67(Sgl$__Closure_945_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_945_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_945_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_945_67*  __make___Closure_945_67(Sgl$__Closure_945_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_945_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_945_67) , __fini___Closure_945_67) ));
	self->invoke = __fn___Closure_945_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_945_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_945_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_962_67(Sgl$__Closure_962_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform3f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[0] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[1] : 0, Orc$String$toFloat(et->value) ) ;
	printf("更新vec3:%s\n", et->value->str) ;
}

static void  __fini___Closure_962_67(Sgl$__Closure_962_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_962_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_962_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_962_67*  __make___Closure_962_67(Sgl$__Closure_962_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_962_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_962_67) , __fini___Closure_962_67) ));
	self->invoke = __fn___Closure_962_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_962_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_962_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_981_67(Sgl$__Closure_981_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform4f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, Orc$String$toFloat(et->value) , self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[1] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[2] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[3] : 0) ;
	printf("更新vec4:%s\n", et->value->str) ;
}

static void  __fini___Closure_981_67(Sgl$__Closure_981_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_981_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_981_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_981_67*  __make___Closure_981_67(Sgl$__Closure_981_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_981_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_981_67) , __fini___Closure_981_67) ));
	self->invoke = __fn___Closure_981_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_981_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_981_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_999_67(Sgl$__Closure_999_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform4f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[0] : 0, Orc$String$toFloat(et->value) , self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[2] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[3] : 0) ;
	printf("更新vec4:%s\n", et->value->str) ;
}

static void  __fini___Closure_999_67(Sgl$__Closure_999_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_999_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_999_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_999_67*  __make___Closure_999_67(Sgl$__Closure_999_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_999_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_999_67) , __fini___Closure_999_67) ));
	self->invoke = __fn___Closure_999_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_999_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_999_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1017_67(Sgl$__Closure_1017_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform4f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[0] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[1] : 0, Orc$String$toFloat(et->value) , self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[3] : 0) ;
	printf("更新vec4:%s\n", et->value->str) ;
}

static void  __fini___Closure_1017_67(Sgl$__Closure_1017_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1017_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1017_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_1017_67*  __make___Closure_1017_67(Sgl$__Closure_1017_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_1017_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_1017_67) , __fini___Closure_1017_67) ));
	self->invoke = __fn___Closure_1017_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1017_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1017_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1035_67(Sgl$__Closure_1035_67 *  self, SuiView$EditText *  et){
	self->__var___Block_761_16->self->matl->setUniform4f(self->__var___Block_761_16->self->matl, self->__var___Block_801_57->um->name->str, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[0] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[1] : 0, self->__var___Block_801_57->ui ? self->__var___Block_801_57->ui->floatValues[2] : 0, Orc$String$toFloat(et->value) ) ;
	printf("更新vec4:%s\n", et->value->str) ;
}

static void  __fini___Closure_1035_67(Sgl$__Closure_1035_67 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1035_67, __var___Block_761_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1035_67, __var___Block_801_57) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_1035_67*  __make___Closure_1035_67(Sgl$__Closure_1035_67 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16, Sgl$__Block_801_57 *  __var___Block_801_57){
	URGC_VAR_CLEANUP Sgl$__Closure_1035_67*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_1035_67) , __fini___Closure_1035_67) ));
	self->invoke = __fn___Closure_1035_67;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1035_67, __var___Block_761_16) , __var___Block_761_16) ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1035_67, __var___Block_801_57) , __var___Block_801_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1067_46(Sgl$__Closure_1067_46 *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_1068_32 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_1068_32;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1068_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		o->setText(o, Orc$str(&tmpReturn_2, "uniform") ) ;
	}
}

static void  __fini___Closure_1067_46(Sgl$__Closure_1067_46 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_1067_46*  __make___Closure_1067_46(Sgl$__Closure_1067_46 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_1067_46*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_1067_46) , __fini___Closure_1067_46) ));
	self->invoke = __fn___Closure_1067_46;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1072_48(Sgl$__Closure_1072_48 *  self, SuiCore$Node *  o){
	int  l = self->__var___Block_761_16->self->matl->uniforms->size(self->__var___Block_761_16->self->matl->uniforms) ;
	for (int  i = 0; i < l; i++) {
		Sgl$UniformInfo *  ui = (Sgl$UniformInfo * )self->__var___Block_761_16->self->matl->uniforms->get(self->__var___Block_761_16->self->matl->uniforms, i) ;
		if (ui->kind == 4) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_1079_40 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )ui) , *o = __scopeVar_1079_40;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1079_40 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->border->b->set(((SuiCore$View * )o)->border->b, 1, 0x33000000) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
				{
					SuiView$TextView*  __scopeVar_1081_44 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_1081_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1081_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->width = 100;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
					o->setText(o, Orc$String$add(Orc$String$addString(Orc$str(&tmpReturn_3, "") , ui->key) , ":") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_4 = NULL;
				{
					SuiView$ImageView*  __scopeVar_1088_44 = SuiView$mkImageView(&tmpReturn_4, o, 0) , *o = __scopeVar_1088_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1088_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->backgroundColor = 0x11333333;
					SuiCore$Inset$setVer(&((SuiCore$View * )o)->margin, 6) ;
					((SuiCore$View * )o)->width = 60;
					((SuiCore$View * )o)->height = 60;
					((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 1, 0x33333333) ;
					o->setImageMode(o, SuiView$Contain) ;
					URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_5 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$ImageView, _img) , ui->tex ? Sgl$loadImageByTex2d(&tmpReturn_5, ui->tex)  : NULL) ;
				}
			}
		}
		else {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_6 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_1100_40 = SuiLayout$layoutLinear(&tmpReturn_6, o, (long long )ui) , *o = __scopeVar_1100_40;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1100_40 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->border->b->set(((SuiCore$View * )o)->border->b, 1, 0x33000000) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
				{
					SuiView$TextView*  __scopeVar_1102_44 = SuiView$mkTextView(&tmpReturn_7, o, 0) , *o = __scopeVar_1102_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1102_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->width = 100;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
					o->setText(o, Orc$String$add(Orc$String$addString(Orc$str(&tmpReturn_8, "") , ui->key) , ":") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$ColorPicker*  tmpReturn_9 = NULL;
				{
					SuiView$ColorPicker*  __scopeVar_1106_44 = SuiView$mkColorPicker(&tmpReturn_9, o, o) , *o = __scopeVar_1106_44;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1106_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					
				}
			}
		}
	}
}

static void  __fini___Closure_1072_48(Sgl$__Closure_1072_48 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1072_48, __var___Block_761_16) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_1072_48*  __make___Closure_1072_48(Sgl$__Closure_1072_48 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16){
	URGC_VAR_CLEANUP Sgl$__Closure_1072_48*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_1072_48) , __fini___Closure_1072_48) ));
	self->invoke = __fn___Closure_1072_48;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1072_48, __var___Block_761_16) , __var___Block_761_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1132_36(Sgl$__Closure_1132_36 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  m = (m=NULL,urgc_init_var_class((void**)&m, Sgl$Material_new(&m) ));
	if (m->load(m, "test.matl.json") ) {
		SuiDialog$Toast_make("加载成功") ;
	}
	else {
		SuiDialog$Toast_make("加载失败") ;
	}
}

static void  __fini___Closure_1132_36(Sgl$__Closure_1132_36 *  self){
	urgc_free_later(self) ;
}

static Sgl$__Closure_1132_36*  __make___Closure_1132_36(Sgl$__Closure_1132_36 **  __outRef__){
	URGC_VAR_CLEANUP Sgl$__Closure_1132_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_1132_36) , __fini___Closure_1132_36) ));
	self->invoke = __fn___Closure_1132_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1147_36(Sgl$__Closure_1147_36 *  self, SuiCore$MouseEvent *  me){
	if (self->__var___Block_761_16->self->matl->save(self->__var___Block_761_16->self->matl) ) {
		SuiDialog$Toast_make("保存成功") ;
	}
	else {
		SuiDialog$Toast_make("保存失败") ;
	}
}

static void  __fini___Closure_1147_36(Sgl$__Closure_1147_36 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1147_36, __var___Block_761_16) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_1147_36*  __make___Closure_1147_36(Sgl$__Closure_1147_36 **  __outRef__, Sgl$__Block_761_16 *  __var___Block_761_16){
	URGC_VAR_CLEANUP Sgl$__Closure_1147_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_1147_36) , __fini___Closure_1147_36) ));
	self->invoke = __fn___Closure_1147_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1147_36, __var___Block_761_16) , __var___Block_761_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1374_35(Sgl$__Closure_1374_35 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		if (d->mouseDownButton == 1) {
			self->__var___Block_1370_26->self->rotateY += Orc$toRad(d->deltaPos.x) ;
			self->__var___Block_1370_26->self->applyModel(self->__var___Block_1370_26->self) ;
		}
		if (d->mouseDownButton == 3) {
			self->__var___Block_1370_26->self->scale = Orc$clampFloat(self->__var___Block_1370_26->self->scale + d->deltaPos.x / 10000.0, 0.01, 2.0) ;
			self->__var___Block_1370_26->self->applyModel(self->__var___Block_1370_26->self) ;
		}
	}
}

static void  __fini___Closure_1374_35(Sgl$__Closure_1374_35 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1374_35, __var___Block_1370_26) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_1374_35*  __make___Closure_1374_35(Sgl$__Closure_1374_35 **  __outRef__, Sgl$__Block_1370_26 *  __var___Block_1370_26){
	URGC_VAR_CLEANUP Sgl$__Closure_1374_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_1374_35) , __fini___Closure_1374_35) ));
	self->invoke = __fn___Closure_1374_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_1374_35, __var___Block_1370_26) , __var___Block_1370_26) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

Sgl$MaterialPreviewView*  Sgl$mkMaterialPreviewView(Sgl$MaterialPreviewView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (Sgl$MaterialPreviewView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_Sgl$MaterialPreviewView_init(NULL)) ) ; 
}

void  Sgl$testMaterialMeta(){
	URGC_VAR_CLEANUP_CLASS Sgl$ShaderMeta*  sm = (sm=NULL,urgc_init_var_class((void**)&sm, Sgl$ShaderMeta_new(&sm) ));
	sm->parseVsByPathCstr(sm, "../asset/a.vs") ;
	sm->parseFsByPathCstr(sm, "../asset/a.fs") ;
}

void  Sgl$testInspMaterial(){
	printf("hi insp material\n") ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpNewOwner_2 = NULL;
		{
			SuiView$ScrollArea*  o = SuiView$ScrollArea_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1422_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0xeeefefff;
			win->setRootView(win, o) ;
			((SuiLayout$LayoutLinear * )o)->aiStretch(o) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_1429_12 = SuiLayout$layoutLinear(&tmpReturn_3, o, 0) , *o = __scopeVar_1429_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1429_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
				SuiLayout$LayoutLinear *  tmpThis_2 = NULL;
				(tmpThis_1 = (tmpThis_2 = o->column(o) )->jcs(tmpThis_2) )->aiStretch(tmpThis_1) ;
				((SuiCore$View * )o)->backgroundColor = 0x99efefff;
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
				matl->load(matl, "../asset/basic.matl.json") ;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$Insp*  insp = (insp=NULL,urgc_init_var_class((void**)&insp, SuiDesigner$Insp_new(&insp) ));
				insp->insp(insp, o, matl) ;
			}
		}
		o->setTitle(o, "材质") ;
		o->setSize(o, 640, 480) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}



