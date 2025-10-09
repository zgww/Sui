
#include "TileEditor_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>
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


// static struct 
typedef struct tagSuiDesigner$__Block_561_15 SuiDesigner$__Block_561_15;

typedef struct tagSuiDesigner$__Block_871_15 SuiDesigner$__Block_871_15;

typedef struct tagSuiDesigner$__Block_1089_15 SuiDesigner$__Block_1089_15;

typedef struct tagSuiDesigner$__Block_1190_45 SuiDesigner$__Block_1190_45;

typedef struct tagSuiDesigner$__Block_1197_57 SuiDesigner$__Block_1197_57;

typedef struct tagSuiDesigner$__Block_1212_64 SuiDesigner$__Block_1212_64;

typedef struct tagSuiDesigner$__Block_1265_50 SuiDesigner$__Block_1265_50;

typedef struct tagSuiDesigner$__Block_1280_62 SuiDesigner$__Block_1280_62;

typedef struct tagSuiDesigner$__Block_1333_49 SuiDesigner$__Block_1333_49;

typedef struct tagSuiDesigner$__Block_1394_53 SuiDesigner$__Block_1394_53;

typedef struct tagSuiDesigner$__Block_1481_63 SuiDesigner$__Block_1481_63;

typedef struct tagSuiDesigner$__Block_1552_68 SuiDesigner$__Block_1552_68;

typedef struct tagSuiDesigner$__Block_1602_87 SuiDesigner$__Block_1602_87;

typedef struct tagSuiDesigner$__Block_1725_63 SuiDesigner$__Block_1725_63;

typedef struct tagSuiDesigner$__Block_1870_16 SuiDesigner$__Block_1870_16;

typedef struct tagSuiDesigner$__Block_2113_32 SuiDesigner$__Block_2113_32;

typedef struct tagSuiDesigner$__Closure_562_27 SuiDesigner$__Closure_562_27;

typedef struct tagSuiDesigner$__Closure_873_27 SuiDesigner$__Closure_873_27;

typedef struct tagSuiDesigner$__Closure_1091_34 SuiDesigner$__Closure_1091_34;

typedef struct tagSuiDesigner$__Closure_1178_26 SuiDesigner$__Closure_1178_26;

typedef struct tagSuiDesigner$__Closure_1192_52 SuiDesigner$__Closure_1192_52;

typedef struct tagSuiDesigner$__Closure_1227_44 SuiDesigner$__Closure_1227_44;

typedef struct tagSuiDesigner$__Closure_onActive_1230 SuiDesigner$__Closure_onActive_1230;

typedef struct tagSuiDesigner$__Closure_1251_40 SuiDesigner$__Closure_1251_40;

typedef struct tagSuiDesigner$__Closure_1295_44 SuiDesigner$__Closure_1295_44;

typedef struct tagSuiDesigner$__Closure_onActive_1298 SuiDesigner$__Closure_onActive_1298;

typedef struct tagSuiDesigner$__Closure_1320_40 SuiDesigner$__Closure_1320_40;

typedef struct tagSuiDesigner$__Closure_1340_26 SuiDesigner$__Closure_1340_26;

typedef struct tagSuiDesigner$__Closure_1401_26 SuiDesigner$__Closure_1401_26;

typedef struct tagSuiDesigner$__Closure_1426_38 SuiDesigner$__Closure_1426_38;

typedef struct tagSuiDesigner$__Closure_1505_56 SuiDesigner$__Closure_1505_56;

typedef struct tagSuiDesigner$__Closure_1578_56 SuiDesigner$__Closure_1578_56;

typedef struct tagSuiDesigner$__Closure_1622_54 SuiDesigner$__Closure_1622_54;

typedef struct tagSuiDesigner$__Closure_onActive_1626 SuiDesigner$__Closure_onActive_1626;

typedef struct tagSuiDesigner$__Closure_1679_54 SuiDesigner$__Closure_1679_54;

typedef struct tagSuiDesigner$__Closure_onActive_1683 SuiDesigner$__Closure_onActive_1683;

typedef struct tagSuiDesigner$__Closure_1736_54 SuiDesigner$__Closure_1736_54;

typedef struct tagSuiDesigner$__Closure_onActive_1740 SuiDesigner$__Closure_onActive_1740;

typedef struct tagSuiDesigner$__Closure_1877_32 SuiDesigner$__Closure_1877_32;

typedef struct tagSuiDesigner$__Closure_1884_32 SuiDesigner$__Closure_1884_32;

typedef struct tagSuiDesigner$__Closure_1890_32 SuiDesigner$__Closure_1890_32;

typedef struct tagSuiDesigner$__Closure_1897_32 SuiDesigner$__Closure_1897_32;

typedef struct tagSuiDesigner$__Closure_1905_32 SuiDesigner$__Closure_1905_32;

typedef struct tagSuiDesigner$__Closure_1913_32 SuiDesigner$__Closure_1913_32;

typedef struct tagSuiDesigner$__Closure_1920_32 SuiDesigner$__Closure_1920_32;

typedef struct tagSuiDesigner$__Closure_1926_32 SuiDesigner$__Closure_1926_32;

typedef struct tagSuiDesigner$__Closure_1939_32 SuiDesigner$__Closure_1939_32;

typedef struct tagSuiDesigner$__Closure_1954_32 SuiDesigner$__Closure_1954_32;

typedef struct tagSuiDesigner$__Closure_1966_45 SuiDesigner$__Closure_1966_45;

typedef struct tagSuiDesigner$__Closure_1999_48 SuiDesigner$__Closure_1999_48;

typedef struct tagSuiDesigner$__Closure_2116_35 SuiDesigner$__Closure_2116_35;

typedef struct tagSuiDesigner$__Closure_2123_39 SuiDesigner$__Closure_2123_39;

typedef struct tagSuiDesigner$__Closure_2135_39 SuiDesigner$__Closure_2135_39;

typedef struct tagSuiDesigner$__Closure_2147_39 SuiDesigner$__Closure_2147_39;

typedef struct tagSuiDesigner$__Closure_2161_32 SuiDesigner$__Closure_2161_32;



struct tagSuiDesigner$__Block_561_15 {
	SuiDesigner$TileMapEditView*  self ;
};





struct tagSuiDesigner$__Block_871_15 {
	SuiDesigner$SceneCtrl*  self ;
};





struct tagSuiDesigner$__Block_1089_15 {
	SuiDesigner$TileEditor*  self ;
};





struct tagSuiDesigner$__Block_1190_45 {
	SuiDesigner$Layer*  layer ;
	SuiDesigner$TileEditor*  self ;
};





struct tagSuiDesigner$__Block_1197_57 {
	SuiDesigner$TileEditor*  self ;
};





struct tagSuiDesigner$__Block_1212_64 {
	SuiDesigner$Tileset *  tileset ;
};





struct tagSuiDesigner$__Block_1265_50 {
	SuiDesigner$TileEditor*  self ;
};





struct tagSuiDesigner$__Block_1280_62 {
	SuiDesigner$Layer *  layer ;
};





struct tagSuiDesigner$__Block_1333_49 {
	SuiDesigner$TileEditor*  self ;
};





struct tagSuiDesigner$__Block_1394_53 {
	SuiDesigner$TileEditor*  self ;
};





struct tagSuiDesigner$__Block_1481_63 {
	SuiCore$Vec2 tilePos ;
};





struct tagSuiDesigner$__Block_1552_68 {
	int  neighborId ;
};





struct tagSuiDesigner$__Block_1602_87 {
	SuiDesigner$SpecialTile*  st ;
};





struct tagSuiDesigner$__Block_1725_63 {
	SuiDesigner$AutoTile*  rt ;
};





struct tagSuiDesigner$__Block_1870_16 {
	SuiDesigner$TileEditor*  self ;
	SuiDesigner$Theme *  t ;
};





struct tagSuiDesigner$__Block_2113_32 {
	Sui$Window*  win ;
	SuiDesigner$TileEditor*  self ;
	void  (**reactMapSetting)(void *  self);
};





struct tagSuiDesigner$__Closure_562_27 {
	void  (*invoke)(SuiDesigner$__Closure_562_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_561_15*  __var___Block_561_15 ;
};





struct tagSuiDesigner$__Closure_873_27 {
	void  (*invoke)(SuiDesigner$__Closure_873_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_871_15*  __var___Block_871_15 ;
};





struct tagSuiDesigner$__Closure_1091_34 {
	void  (*invoke)(SuiDesigner$__Closure_1091_34 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1089_15*  __var___Block_1089_15 ;
};





struct tagSuiDesigner$__Closure_1178_26 {
	void  (*invoke)(SuiDesigner$__Closure_1178_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_1192_52 {
	void  (*invoke)(SuiDesigner$__Closure_1192_52 *  self, Orc$String*  newValue);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1190_45*  __var___Block_1190_45 ;
};





struct tagSuiDesigner$__Closure_1227_44 {
	bool  (*invoke)(SuiDesigner$__Closure_1227_44 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_onActive_1230 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_1230 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_1251_40 {
	void  (*invoke)(SuiDesigner$__Closure_1251_40 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1197_57*  __var___Block_1197_57 ;
	SuiDesigner$__Block_1212_64*  __var___Block_1212_64 ;
};





struct tagSuiDesigner$__Closure_1295_44 {
	bool  (*invoke)(SuiDesigner$__Closure_1295_44 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1265_50*  __var___Block_1265_50 ;
	SuiDesigner$__Block_1280_62*  __var___Block_1280_62 ;
};





struct tagSuiDesigner$__Closure_onActive_1298 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_1298 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1265_50*  __var___Block_1265_50 ;
	SuiDesigner$__Block_1280_62*  __var___Block_1280_62 ;
};





struct tagSuiDesigner$__Closure_1320_40 {
	void  (*invoke)(SuiDesigner$__Closure_1320_40 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1265_50*  __var___Block_1265_50 ;
	SuiDesigner$__Block_1280_62*  __var___Block_1280_62 ;
};





struct tagSuiDesigner$__Closure_1340_26 {
	void  (*invoke)(SuiDesigner$__Closure_1340_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1333_49*  __var___Block_1333_49 ;
};





struct tagSuiDesigner$__Closure_1401_26 {
	void  (*invoke)(SuiDesigner$__Closure_1401_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
};





struct tagSuiDesigner$__Closure_1426_38 {
	void  (*invoke)(SuiDesigner$__Closure_1426_38 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
};





struct tagSuiDesigner$__Closure_1505_56 {
	void  (*invoke)(SuiDesigner$__Closure_1505_56 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1481_63*  __var___Block_1481_63 ;
};





struct tagSuiDesigner$__Closure_1578_56 {
	void  (*invoke)(SuiDesigner$__Closure_1578_56 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1552_68*  __var___Block_1552_68 ;
};





struct tagSuiDesigner$__Closure_1622_54 {
	void  (*invoke)(SuiDesigner$__Closure_1622_54 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1602_87*  __var___Block_1602_87 ;
};





struct tagSuiDesigner$__Closure_onActive_1626 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_1626 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1602_87*  __var___Block_1602_87 ;
};





struct tagSuiDesigner$__Closure_1679_54 {
	void  (*invoke)(SuiDesigner$__Closure_1679_54 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1602_87*  __var___Block_1602_87 ;
};





struct tagSuiDesigner$__Closure_onActive_1683 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_1683 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1602_87*  __var___Block_1602_87 ;
};





struct tagSuiDesigner$__Closure_1736_54 {
	void  (*invoke)(SuiDesigner$__Closure_1736_54 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1602_87*  __var___Block_1602_87 ;
	SuiDesigner$__Block_1725_63*  __var___Block_1725_63 ;
};





struct tagSuiDesigner$__Closure_onActive_1740 {
	void  (*invoke)(SuiDesigner$__Closure_onActive_1740 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1394_53*  __var___Block_1394_53 ;
	SuiDesigner$__Block_1602_87*  __var___Block_1602_87 ;
	SuiDesigner$__Block_1725_63*  __var___Block_1725_63 ;
};





struct tagSuiDesigner$__Closure_1877_32 {
	void  (*invoke)(SuiDesigner$__Closure_1877_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1884_32 {
	void  (*invoke)(SuiDesigner$__Closure_1884_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1890_32 {
	void  (*invoke)(SuiDesigner$__Closure_1890_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1897_32 {
	void  (*invoke)(SuiDesigner$__Closure_1897_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1905_32 {
	void  (*invoke)(SuiDesigner$__Closure_1905_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1913_32 {
	void  (*invoke)(SuiDesigner$__Closure_1913_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1920_32 {
	void  (*invoke)(SuiDesigner$__Closure_1920_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1926_32 {
	void  (*invoke)(SuiDesigner$__Closure_1926_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1939_32 {
	void  (*invoke)(SuiDesigner$__Closure_1939_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1954_32 {
	void  (*invoke)(SuiDesigner$__Closure_1954_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_1966_45 {
	void  (*invoke)(SuiDesigner$__Closure_1966_45 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_1999_48 {
	SuiCore$ViewBase *  (*invoke)(SuiDesigner$__Closure_1999_48 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_1870_16*  __var___Block_1870_16 ;
};





struct tagSuiDesigner$__Closure_2116_35 {
	void  (*invoke)(SuiDesigner$__Closure_2116_35 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_2113_32*  __var___Block_2113_32 ;
};





struct tagSuiDesigner$__Closure_2123_39 {
	void  (*invoke)(SuiDesigner$__Closure_2123_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_2113_32*  __var___Block_2113_32 ;
};





struct tagSuiDesigner$__Closure_2135_39 {
	void  (*invoke)(SuiDesigner$__Closure_2135_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_2113_32*  __var___Block_2113_32 ;
};





struct tagSuiDesigner$__Closure_2147_39 {
	void  (*invoke)(SuiDesigner$__Closure_2147_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_2113_32*  __var___Block_2113_32 ;
};





struct tagSuiDesigner$__Closure_2161_32 {
	void  (*invoke)(SuiDesigner$__Closure_2161_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_2113_32*  __var___Block_2113_32 ;
};





// static function declaration
static SuiCore$Vec2 dissolveCidToGridPos(SuiDesigner$Tileset *  ts, int  cid);
static SuiCore$Vec2 dissolveNeighborIdoGridPos(SuiDesigner$Tileset *  ts, int  nid);
static void  __finiBlock___Block_561_15(SuiDesigner$__Block_561_15 *  self);
static void  __finiBlock___Block_871_15(SuiDesigner$__Block_871_15 *  self);
static void  __finiBlock___Block_1089_15(SuiDesigner$__Block_1089_15 *  self);
static void  __finiBlock___Block_1190_45(SuiDesigner$__Block_1190_45 *  self);
static void  __finiBlock___Block_1197_57(SuiDesigner$__Block_1197_57 *  self);
static void  __finiBlock___Block_1212_64(SuiDesigner$__Block_1212_64 *  self);
static void  __finiBlock___Block_1265_50(SuiDesigner$__Block_1265_50 *  self);
static void  __finiBlock___Block_1280_62(SuiDesigner$__Block_1280_62 *  self);
static void  __finiBlock___Block_1333_49(SuiDesigner$__Block_1333_49 *  self);
static void  __finiBlock___Block_1394_53(SuiDesigner$__Block_1394_53 *  self);
static void  __finiBlock___Block_1481_63(SuiDesigner$__Block_1481_63 *  self);
static void  __finiBlock___Block_1552_68(SuiDesigner$__Block_1552_68 *  self);
static void  __finiBlock___Block_1602_87(SuiDesigner$__Block_1602_87 *  self);
static void  __finiBlock___Block_1725_63(SuiDesigner$__Block_1725_63 *  self);
static void  __finiBlock___Block_1870_16(SuiDesigner$__Block_1870_16 *  self);
static void  __finiBlock___Block_2113_32(SuiDesigner$__Block_2113_32 *  self);
static void  __fn___Closure_562_27(SuiDesigner$__Closure_562_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_562_27(SuiDesigner$__Closure_562_27 *  self);
static SuiDesigner$__Closure_562_27*  __make___Closure_562_27(SuiDesigner$__Closure_562_27 **  __outRef__, SuiDesigner$__Block_561_15 *  __var___Block_561_15);
static void  __fn___Closure_873_27(SuiDesigner$__Closure_873_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_873_27(SuiDesigner$__Closure_873_27 *  self);
static SuiDesigner$__Closure_873_27*  __make___Closure_873_27(SuiDesigner$__Closure_873_27 **  __outRef__, SuiDesigner$__Block_871_15 *  __var___Block_871_15);
static void  __fn___Closure_1091_34(SuiDesigner$__Closure_1091_34 *  self, SuiView$Drag *  d);
static void  __fini___Closure_1091_34(SuiDesigner$__Closure_1091_34 *  self);
static SuiDesigner$__Closure_1091_34*  __make___Closure_1091_34(SuiDesigner$__Closure_1091_34 **  __outRef__, SuiDesigner$__Block_1089_15 *  __var___Block_1089_15);
static void  __fn___Closure_1178_26(SuiDesigner$__Closure_1178_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1178_26(SuiDesigner$__Closure_1178_26 *  self);
static SuiDesigner$__Closure_1178_26*  __make___Closure_1178_26(SuiDesigner$__Closure_1178_26 **  __outRef__);
static void  __fn___Closure_1192_52(SuiDesigner$__Closure_1192_52 *  self, Orc$String*  newValue);
static void  __fini___Closure_1192_52(SuiDesigner$__Closure_1192_52 *  self);
static SuiDesigner$__Closure_1192_52*  __make___Closure_1192_52(SuiDesigner$__Closure_1192_52 **  __outRef__, SuiDesigner$__Block_1190_45 *  __var___Block_1190_45);
static bool  __fn___Closure_1227_44(SuiDesigner$__Closure_1227_44 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1227_44(SuiDesigner$__Closure_1227_44 *  self);
static SuiDesigner$__Closure_1227_44*  __make___Closure_1227_44(SuiDesigner$__Closure_1227_44 **  __outRef__);
static void  __fn___Closure_onActive_1230(SuiDesigner$__Closure_onActive_1230 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_1230(SuiDesigner$__Closure_onActive_1230 *  self);
static SuiDesigner$__Closure_onActive_1230*  __make___Closure_onActive_1230(SuiDesigner$__Closure_onActive_1230 **  __outRef__);
static void  __fn___Closure_1251_40(SuiDesigner$__Closure_1251_40 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1251_40(SuiDesigner$__Closure_1251_40 *  self);
static SuiDesigner$__Closure_1251_40*  __make___Closure_1251_40(SuiDesigner$__Closure_1251_40 **  __outRef__, SuiDesigner$__Block_1197_57 *  __var___Block_1197_57, SuiDesigner$__Block_1212_64 *  __var___Block_1212_64);
static bool  __fn___Closure_1295_44(SuiDesigner$__Closure_1295_44 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1295_44(SuiDesigner$__Closure_1295_44 *  self);
static SuiDesigner$__Closure_1295_44*  __make___Closure_1295_44(SuiDesigner$__Closure_1295_44 **  __outRef__, SuiDesigner$__Block_1265_50 *  __var___Block_1265_50, SuiDesigner$__Block_1280_62 *  __var___Block_1280_62);
static void  __fn___Closure_onActive_1298(SuiDesigner$__Closure_onActive_1298 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_1298(SuiDesigner$__Closure_onActive_1298 *  self);
static SuiDesigner$__Closure_onActive_1298*  __make___Closure_onActive_1298(SuiDesigner$__Closure_onActive_1298 **  __outRef__, SuiDesigner$__Block_1265_50 *  __var___Block_1265_50, SuiDesigner$__Block_1280_62 *  __var___Block_1280_62);
static void  __fn___Closure_1320_40(SuiDesigner$__Closure_1320_40 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1320_40(SuiDesigner$__Closure_1320_40 *  self);
static SuiDesigner$__Closure_1320_40*  __make___Closure_1320_40(SuiDesigner$__Closure_1320_40 **  __outRef__, SuiDesigner$__Block_1265_50 *  __var___Block_1265_50, SuiDesigner$__Block_1280_62 *  __var___Block_1280_62);
static void  __fn___Closure_1340_26(SuiDesigner$__Closure_1340_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1340_26(SuiDesigner$__Closure_1340_26 *  self);
static SuiDesigner$__Closure_1340_26*  __make___Closure_1340_26(SuiDesigner$__Closure_1340_26 **  __outRef__, SuiDesigner$__Block_1333_49 *  __var___Block_1333_49);
static void  __fn___Closure_1401_26(SuiDesigner$__Closure_1401_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1401_26(SuiDesigner$__Closure_1401_26 *  self);
static SuiDesigner$__Closure_1401_26*  __make___Closure_1401_26(SuiDesigner$__Closure_1401_26 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53);
static void  __fn___Closure_1426_38(SuiDesigner$__Closure_1426_38 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1426_38(SuiDesigner$__Closure_1426_38 *  self);
static SuiDesigner$__Closure_1426_38*  __make___Closure_1426_38(SuiDesigner$__Closure_1426_38 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53);
static void  __fn___Closure_1505_56(SuiDesigner$__Closure_1505_56 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1505_56(SuiDesigner$__Closure_1505_56 *  self);
static SuiDesigner$__Closure_1505_56*  __make___Closure_1505_56(SuiDesigner$__Closure_1505_56 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1481_63 *  __var___Block_1481_63);
static void  __fn___Closure_1578_56(SuiDesigner$__Closure_1578_56 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1578_56(SuiDesigner$__Closure_1578_56 *  self);
static SuiDesigner$__Closure_1578_56*  __make___Closure_1578_56(SuiDesigner$__Closure_1578_56 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1552_68 *  __var___Block_1552_68);
static void  __fn___Closure_1622_54(SuiDesigner$__Closure_1622_54 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1622_54(SuiDesigner$__Closure_1622_54 *  self);
static SuiDesigner$__Closure_1622_54*  __make___Closure_1622_54(SuiDesigner$__Closure_1622_54 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87);
static void  __fn___Closure_onActive_1626(SuiDesigner$__Closure_onActive_1626 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_1626(SuiDesigner$__Closure_onActive_1626 *  self);
static SuiDesigner$__Closure_onActive_1626*  __make___Closure_onActive_1626(SuiDesigner$__Closure_onActive_1626 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87);
static void  __fn___Closure_1679_54(SuiDesigner$__Closure_1679_54 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1679_54(SuiDesigner$__Closure_1679_54 *  self);
static SuiDesigner$__Closure_1679_54*  __make___Closure_1679_54(SuiDesigner$__Closure_1679_54 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87);
static void  __fn___Closure_onActive_1683(SuiDesigner$__Closure_onActive_1683 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_1683(SuiDesigner$__Closure_onActive_1683 *  self);
static SuiDesigner$__Closure_onActive_1683*  __make___Closure_onActive_1683(SuiDesigner$__Closure_onActive_1683 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87);
static void  __fn___Closure_1736_54(SuiDesigner$__Closure_1736_54 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1736_54(SuiDesigner$__Closure_1736_54 *  self);
static SuiDesigner$__Closure_1736_54*  __make___Closure_1736_54(SuiDesigner$__Closure_1736_54 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87, SuiDesigner$__Block_1725_63 *  __var___Block_1725_63);
static void  __fn___Closure_onActive_1740(SuiDesigner$__Closure_onActive_1740 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_1740(SuiDesigner$__Closure_onActive_1740 *  self);
static SuiDesigner$__Closure_onActive_1740*  __make___Closure_onActive_1740(SuiDesigner$__Closure_onActive_1740 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87, SuiDesigner$__Block_1725_63 *  __var___Block_1725_63);
static void  __fn___Closure_1877_32(SuiDesigner$__Closure_1877_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1877_32(SuiDesigner$__Closure_1877_32 *  self);
static SuiDesigner$__Closure_1877_32*  __make___Closure_1877_32(SuiDesigner$__Closure_1877_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1884_32(SuiDesigner$__Closure_1884_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1884_32(SuiDesigner$__Closure_1884_32 *  self);
static SuiDesigner$__Closure_1884_32*  __make___Closure_1884_32(SuiDesigner$__Closure_1884_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1890_32(SuiDesigner$__Closure_1890_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1890_32(SuiDesigner$__Closure_1890_32 *  self);
static SuiDesigner$__Closure_1890_32*  __make___Closure_1890_32(SuiDesigner$__Closure_1890_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1897_32(SuiDesigner$__Closure_1897_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1897_32(SuiDesigner$__Closure_1897_32 *  self);
static SuiDesigner$__Closure_1897_32*  __make___Closure_1897_32(SuiDesigner$__Closure_1897_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1905_32(SuiDesigner$__Closure_1905_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1905_32(SuiDesigner$__Closure_1905_32 *  self);
static SuiDesigner$__Closure_1905_32*  __make___Closure_1905_32(SuiDesigner$__Closure_1905_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1913_32(SuiDesigner$__Closure_1913_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1913_32(SuiDesigner$__Closure_1913_32 *  self);
static SuiDesigner$__Closure_1913_32*  __make___Closure_1913_32(SuiDesigner$__Closure_1913_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1920_32(SuiDesigner$__Closure_1920_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1920_32(SuiDesigner$__Closure_1920_32 *  self);
static SuiDesigner$__Closure_1920_32*  __make___Closure_1920_32(SuiDesigner$__Closure_1920_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1926_32(SuiDesigner$__Closure_1926_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1926_32(SuiDesigner$__Closure_1926_32 *  self);
static SuiDesigner$__Closure_1926_32*  __make___Closure_1926_32(SuiDesigner$__Closure_1926_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1939_32(SuiDesigner$__Closure_1939_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1939_32(SuiDesigner$__Closure_1939_32 *  self);
static SuiDesigner$__Closure_1939_32*  __make___Closure_1939_32(SuiDesigner$__Closure_1939_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_1954_32(SuiDesigner$__Closure_1954_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_1954_32(SuiDesigner$__Closure_1954_32 *  self);
static SuiDesigner$__Closure_1954_32*  __make___Closure_1954_32(SuiDesigner$__Closure_1954_32 **  __outRef__);
static void  __fn___Closure_1966_45(SuiDesigner$__Closure_1966_45 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
static void  __fini___Closure_1966_45(SuiDesigner$__Closure_1966_45 *  self);
static SuiDesigner$__Closure_1966_45*  __make___Closure_1966_45(SuiDesigner$__Closure_1966_45 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static SuiCore$ViewBase *  __fn___Closure_1999_48(SuiDesigner$__Closure_1999_48 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
static void  __fini___Closure_1999_48(SuiDesigner$__Closure_1999_48 *  self);
static SuiDesigner$__Closure_1999_48*  __make___Closure_1999_48(SuiDesigner$__Closure_1999_48 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16);
static void  __fn___Closure_2116_35(SuiDesigner$__Closure_2116_35 *  self);
static void  __fini___Closure_2116_35(SuiDesigner$__Closure_2116_35 *  self);
static SuiDesigner$__Closure_2116_35*  __make___Closure_2116_35(SuiDesigner$__Closure_2116_35 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32);
static void  __fn___Closure_2123_39(SuiDesigner$__Closure_2123_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_2123_39(SuiDesigner$__Closure_2123_39 *  self);
static SuiDesigner$__Closure_2123_39*  __make___Closure_2123_39(SuiDesigner$__Closure_2123_39 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32);
static void  __fn___Closure_2135_39(SuiDesigner$__Closure_2135_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_2135_39(SuiDesigner$__Closure_2135_39 *  self);
static SuiDesigner$__Closure_2135_39*  __make___Closure_2135_39(SuiDesigner$__Closure_2135_39 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32);
static void  __fn___Closure_2147_39(SuiDesigner$__Closure_2147_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_2147_39(SuiDesigner$__Closure_2147_39 *  self);
static SuiDesigner$__Closure_2147_39*  __make___Closure_2147_39(SuiDesigner$__Closure_2147_39 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32);
static void  __fn___Closure_2161_32(SuiDesigner$__Closure_2161_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_2161_32(SuiDesigner$__Closure_2161_32 *  self);
static SuiDesigner$__Closure_2161_32*  __make___Closure_2161_32(SuiDesigner$__Closure_2161_32 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32);



//vtable instance
Vtable_SuiDesigner$Tile _vtable_SuiDesigner$Tile;

// init meta

void SuiDesigner$Tile_initMeta(Vtable_SuiDesigner$Tile *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "gid", OrcMetaType_int, offsetof(SuiDesigner$Tile, gid), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiDesigner$Tile* Vtable_SuiDesigner$Tile_init(Vtable_SuiDesigner$Tile* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Tile;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Tile_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Tile";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Tile_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$Tile_fini(SuiDesigner$Tile *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$Tile_init_fields(SuiDesigner$Tile *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Tile_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner$Tile_init(SuiDesigner$Tile *self, void *pOwner){
    Vtable_SuiDesigner$Tile_init(&_vtable_SuiDesigner$Tile);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Tile;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Tile_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Tile * SuiDesigner$Tile_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Tile *self = calloc(1, sizeof(SuiDesigner$Tile));
	
    SuiDesigner$Tile_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner$SpecialTile _vtable_SuiDesigner$SpecialTile;

// init meta

void SuiDesigner$SpecialTile_initMeta(Vtable_SuiDesigner$SpecialTile *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	orc_metaField_method(&pNext, "getGid", offsetof(SuiDesigner$SpecialTile, getGid));
	orc_metaField_method(&pNext, "setTileAtGid", offsetof(SuiDesigner$SpecialTile, setTileAtGid));
}


// vtable init


Vtable_SuiDesigner$SpecialTile* Vtable_SuiDesigner$SpecialTile_init(Vtable_SuiDesigner$SpecialTile* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SpecialTile;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SpecialTile_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SpecialTile";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SpecialTile_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$SpecialTile_fini(SuiDesigner$SpecialTile *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$SpecialTile_init_fields(SuiDesigner$SpecialTile *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SpecialTile_fini;
	//fields
    {
	
    }
	((SuiDesigner$SpecialTile*)self)->getGid = (void*)SuiDesigner$SpecialTile$getGid;
	((SuiDesigner$SpecialTile*)self)->setTileAtGid = (void*)SuiDesigner$SpecialTile$setTileAtGid;
}

// init function

void SuiDesigner$SpecialTile_init(SuiDesigner$SpecialTile *self, void *pOwner){
    Vtable_SuiDesigner$SpecialTile_init(&_vtable_SuiDesigner$SpecialTile);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SpecialTile;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SpecialTile_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SpecialTile * SuiDesigner$SpecialTile_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SpecialTile *self = calloc(1, sizeof(SuiDesigner$SpecialTile));
	
    SuiDesigner$SpecialTile_init(self, pOwner);
    return self;
}


// class members
int  SuiDesigner$SpecialTile$getGid(SuiDesigner$SpecialTile *  self){
	return -1; 
}


void  SuiDesigner$SpecialTile$setTileAtGid(SuiDesigner$SpecialTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex){
	
}




//vtable instance
Vtable_SuiDesigner$RuleInfo _vtable_SuiDesigner$RuleInfo;

// init meta

void SuiDesigner$RuleInfo_initMeta(Vtable_SuiDesigner$RuleInfo *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "gid", OrcMetaType_int, offsetof(SuiDesigner$RuleInfo, gid), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "cid", OrcMetaType_int, offsetof(SuiDesigner$RuleInfo, cid), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "neighborIdArr", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner$RuleInfo, neighborIdArr), true, false, 1);
	orc_metaField_primitive(&pNext, "ruleInt", OrcMetaType_int, offsetof(SuiDesigner$RuleInfo, ruleInt), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "hasByNeighPos", offsetof(SuiDesigner$RuleInfo, hasByNeighPos));
	orc_metaField_method(&pNext, "buildRuleInt", offsetof(SuiDesigner$RuleInfo, buildRuleInt));
}


// vtable init


Vtable_SuiDesigner$RuleInfo* Vtable_SuiDesigner$RuleInfo_init(Vtable_SuiDesigner$RuleInfo* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$RuleInfo;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$RuleInfo_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$RuleInfo";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$RuleInfo_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$RuleInfo_fini(SuiDesigner$RuleInfo *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$RuleInfo*)self)->neighborIdArr);

}

// init fields function


void SuiDesigner$RuleInfo_init_fields(SuiDesigner$RuleInfo *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$RuleInfo_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$RuleInfo*)self)->neighborIdArr, Sgl$IntArray_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$RuleInfo*)self)->hasByNeighPos = (void*)SuiDesigner$RuleInfo$hasByNeighPos;
	((SuiDesigner$RuleInfo*)self)->buildRuleInt = (void*)SuiDesigner$RuleInfo$buildRuleInt;
}

// init function

void SuiDesigner$RuleInfo_init(SuiDesigner$RuleInfo *self, void *pOwner){
    Vtable_SuiDesigner$RuleInfo_init(&_vtable_SuiDesigner$RuleInfo);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$RuleInfo;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$RuleInfo_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$RuleInfo * SuiDesigner$RuleInfo_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$RuleInfo *self = calloc(1, sizeof(SuiDesigner$RuleInfo));
	
    SuiDesigner$RuleInfo_init(self, pOwner);
    return self;
}


// class members
bool  SuiDesigner$RuleInfo$hasByNeighPos(SuiDesigner$RuleInfo *  self, SuiDesigner$Tileset *  ts, int  x, int  y){
	int  nid = ts->cols * 3 * y + x;
	bool  has = Sgl$IntArray$has(self->neighborIdArr, nid) ;
	return has; 
}


void  SuiDesigner$RuleInfo$buildRuleInt(SuiDesigner$RuleInfo *  self, SuiDesigner$Tileset *  ts){
	self->gid = ts->startGid + self->cid;
	SuiCore$Vec2 pos = dissolveCidToGridPos(ts, self->cid) ;
	SuiCore$Vec2 npos = SuiCore$Vec2$scale(&pos, 3) ;
	bool  lt = self->hasByNeighPos(self, ts, npos.x + 0, npos.y + 0) ;
	bool  ct = self->hasByNeighPos(self, ts, npos.x + 1, npos.y + 0) ;
	bool  rt = self->hasByNeighPos(self, ts, npos.x + 2, npos.y + 0) ;
	bool  lm = self->hasByNeighPos(self, ts, npos.x + 0, npos.y + 1) ;
	bool  cm = self->hasByNeighPos(self, ts, npos.x + 1, npos.y + 1) ;
	bool  rm = self->hasByNeighPos(self, ts, npos.x + 2, npos.y + 1) ;
	bool  lb = self->hasByNeighPos(self, ts, npos.x + 0, npos.y + 2) ;
	bool  cb = self->hasByNeighPos(self, ts, npos.x + 1, npos.y + 2) ;
	bool  rb = self->hasByNeighPos(self, ts, npos.x + 1, npos.y + 2) ;
	self->ruleInt = SuiDesigner$RuleInfo_mkRuleInt(lt, ct, rt, lm, cm, rm, lb, cb, rb) ;
}



int  SuiDesigner$RuleInfo_mkRuleInt(bool  lt, bool  ct, bool  rt, bool  lm, bool  cm, bool  rm, bool  lb, bool  cb, bool  rb){
	int  v = 0;
	if (lt) {
		v |= (1 << 0);
	}
	if (ct) {
		v |= (1 << 1);
	}
	if (rt) {
		v |= (1 << 2);
	}
	if (lm) {
		v |= (1 << 3);
	}
	if (cm) {
		v |= (1 << 4);
	}
	if (rm) {
		v |= (1 << 5);
	}
	if (lb) {
		v |= (1 << 6);
	}
	if (cb) {
		v |= (1 << 7);
	}
	if (rb) {
		v |= (1 << 8);
	}
	return v; 
}

static SuiCore$Vec2 dissolveCidToGridPos(SuiDesigner$Tileset *  ts, int  cid){
	int  idx = cid;
	int  c = idx % ts->cols;
	int  r = idx / ts->cols;
	return SuiCore$mkVec2(c, r) ; 
}

static SuiCore$Vec2 dissolveNeighborIdoGridPos(SuiDesigner$Tileset *  ts, int  nid){
	int  idx = nid;
	int  cols = ts->cols * 3;
	int  c = idx % cols;
	int  r = idx / cols;
	return SuiCore$mkVec2(c, r) ; 
}


//vtable instance
Vtable_SuiDesigner$AutoTile _vtable_SuiDesigner$AutoTile;

// init meta

void SuiDesigner$AutoTile_initMeta(Vtable_SuiDesigner$AutoTile *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "gid", OrcMetaType_int, offsetof(SuiDesigner$AutoTile, gid), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "neighborIdArr", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner$AutoTile, neighborIdArr), true, false, 1);
	orc_metaField_class(&pNext, "ruleInfos", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$AutoTile, ruleInfos), true, false, 1);

	orc_metaField_method(&pNext, "neighborIdToCid", offsetof(SuiDesigner$AutoTile, neighborIdToCid));
	orc_metaField_method(&pNext, "neighborIdToGid", offsetof(SuiDesigner$AutoTile, neighborIdToGid));
	orc_metaField_method(&pNext, "isAutoTileByGid", offsetof(SuiDesigner$AutoTile, isAutoTileByGid));
	orc_metaField_method(&pNext, "isAutoTileByLayerPos", offsetof(SuiDesigner$AutoTile, isAutoTileByLayerPos));
	orc_metaField_method(&pNext, "getMatchedRuleGid", offsetof(SuiDesigner$AutoTile, getMatchedRuleGid));
	orc_metaField_method(&pNext, "gocRuleInfoByCid", offsetof(SuiDesigner$AutoTile, gocRuleInfoByCid));
	orc_metaField_method(&pNext, "findRuleInfoByCid", offsetof(SuiDesigner$AutoTile, findRuleInfoByCid));
	orc_metaField_method(&pNext, "buildRuleInfos", offsetof(SuiDesigner$AutoTile, buildRuleInfos));
	orc_metaField_method(&pNext, "mkRuleIntOfTile", offsetof(SuiDesigner$AutoTile, mkRuleIntOfTile));
}


// vtable init


Vtable_SuiDesigner$AutoTile* Vtable_SuiDesigner$AutoTile_init(Vtable_SuiDesigner$AutoTile* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$AutoTile;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$SpecialTile_init(&_vtable_SuiDesigner$SpecialTile);

	// init by super vtable init function
    Vtable_SuiDesigner$SpecialTile_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$SpecialTile;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$AutoTile_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$AutoTile";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$AutoTile_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$AutoTile_fini(SuiDesigner$AutoTile *self){
	//super fini
    SuiDesigner$SpecialTile_fini((SuiDesigner$SpecialTile *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$AutoTile*)self)->neighborIdArr);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$AutoTile*)self)->ruleInfos);

}

// init fields function


void SuiDesigner$AutoTile_init_fields(SuiDesigner$AutoTile *self){
	//super class
    SuiDesigner$SpecialTile_init_fields((SuiDesigner$SpecialTile*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$AutoTile_fini;
	//fields
    {
	((SuiDesigner$AutoTile*)self)->gid = 0;
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$AutoTile*)self)->neighborIdArr, Sgl$IntArray_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$AutoTile*)self)->ruleInfos, Orc$List_new(&tmpNewOwner_2) );
    }
	((SuiDesigner$SpecialTile*)self)->getGid = (void*)SuiDesigner$AutoTile$getGid;
	((SuiDesigner$AutoTile*)self)->neighborIdToCid = (void*)SuiDesigner$AutoTile$neighborIdToCid;
	((SuiDesigner$AutoTile*)self)->neighborIdToGid = (void*)SuiDesigner$AutoTile$neighborIdToGid;
	((SuiDesigner$AutoTile*)self)->isAutoTileByGid = (void*)SuiDesigner$AutoTile$isAutoTileByGid;
	((SuiDesigner$AutoTile*)self)->isAutoTileByLayerPos = (void*)SuiDesigner$AutoTile$isAutoTileByLayerPos;
	((SuiDesigner$SpecialTile*)self)->setTileAtGid = (void*)SuiDesigner$AutoTile$setTileAtGid;
	((SuiDesigner$AutoTile*)self)->getMatchedRuleGid = (void*)SuiDesigner$AutoTile$getMatchedRuleGid;
	((SuiDesigner$AutoTile*)self)->gocRuleInfoByCid = (void*)SuiDesigner$AutoTile$gocRuleInfoByCid;
	((SuiDesigner$AutoTile*)self)->findRuleInfoByCid = (void*)SuiDesigner$AutoTile$findRuleInfoByCid;
	((SuiDesigner$AutoTile*)self)->buildRuleInfos = (void*)SuiDesigner$AutoTile$buildRuleInfos;
	((SuiDesigner$AutoTile*)self)->mkRuleIntOfTile = (void*)SuiDesigner$AutoTile$mkRuleIntOfTile;
}

// init function

void SuiDesigner$AutoTile_init(SuiDesigner$AutoTile *self, void *pOwner){
    Vtable_SuiDesigner$AutoTile_init(&_vtable_SuiDesigner$AutoTile);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$AutoTile;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$AutoTile_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$AutoTile * SuiDesigner$AutoTile_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$AutoTile *self = calloc(1, sizeof(SuiDesigner$AutoTile));
	
    SuiDesigner$AutoTile_init(self, pOwner);
    return self;
}


// class members
int  SuiDesigner$AutoTile$getGid(SuiDesigner$AutoTile *  self){
	return self->gid; 
}


int  SuiDesigner$AutoTile$neighborIdToCid(SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts, int  neighborId){
	SuiCore$Vec2 gridPos = dissolveNeighborIdoGridPos(ts, neighborId) ;
	int  x = gridPos.x / 3;
	int  y = gridPos.y / 3;
	int  cid = y * ts->cols + x;
	return cid; 
}


int  SuiDesigner$AutoTile$neighborIdToGid(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, int  neighborId){
	SuiDesigner$Tileset *  ts = map->findTilesetByGid(map, self->gid) ;
	int  cid = self->neighborIdToCid(self, ts, neighborId) ;
	int  gid = ts->startGid + cid;
	return gid; 
}


bool  SuiDesigner$AutoTile$isAutoTileByGid(SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts, int  gid){
	for (int  i = 0; i < self->neighborIdArr->size; i++) {
		int  nid = self->neighborIdArr->data[i];
		int  curCid = self->neighborIdToCid(self, ts, nid) ;
		int  curGid = ts->startGid + curCid;
		if (gid == curGid) {
			return true; 
		}
	}
	return false; 
}


bool  SuiDesigner$AutoTile$isAutoTileByLayerPos(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  x, int  y){
	if (x < 0 || y < 0 || x >= map->width || y >= map->height) {
		return false; 
	}
	int  idx = x + y * map->width;
	int  gid = layer->data->data[idx];
	int  bIs = self->isAutoTileByGid(self, ts, gid) ;
	return bIs; 
}


void  SuiDesigner$AutoTile$setTileAtGid(SuiDesigner$AutoTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex){
	Sgl$IntArray$set(layer->data, cellIndex, gid) ;
	int  cx = cellIndex % te->map->width;
	int  cy = cellIndex / te->map->width;
	self->buildRuleInfos(self, ts) ;
	for (int  dy = -1; dy <= 1; dy++) {
		for (int  dx = -1; dx <= 1; dx++) {
			int  x = dx + cx;
			int  y = dy + cy;
			int  curCellIndex = y * te->map->width + x;
			int  curGid = layer->data->data[curCellIndex];
			int  actualGid = self->getMatchedRuleGid(self, te->map, layer, ts, curGid, curCellIndex) ;
			Sgl$IntArray$set(layer->data, curCellIndex, actualGid) ;
		}
	}
}


int  SuiDesigner$AutoTile$getMatchedRuleGid(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex){
	int  v = self->mkRuleIntOfTile(self, map, layer, ts, cellIndex) ;
	for (int  i = 0; i < self->ruleInfos->size(self->ruleInfos) ; i++) {
		SuiDesigner$RuleInfo *  info = (SuiDesigner$RuleInfo * )self->ruleInfos->get(self->ruleInfos, i) ;
		if (info->ruleInt == v) {
			return info->gid; 
		}
	}
	return gid; 
}


SuiDesigner$RuleInfo *  SuiDesigner$AutoTile$gocRuleInfoByCid(SuiDesigner$AutoTile *  self, int  cid){
	SuiDesigner$RuleInfo *  info = self->findRuleInfoByCid(self, cid) ;
	if (info == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$RuleInfo*  tmpNewOwner_1 = NULL;
		info = SuiDesigner$RuleInfo_new(&tmpNewOwner_1) ;
		info->cid = cid;
		self->ruleInfos->add(self->ruleInfos, info) ;
	}
	return info; 
}


SuiDesigner$RuleInfo *  SuiDesigner$AutoTile$findRuleInfoByCid(SuiDesigner$AutoTile *  self, int  cid){
	for (int  i = 0; i < self->ruleInfos->size(self->ruleInfos) ; i++) {
		SuiDesigner$RuleInfo *  info = (SuiDesigner$RuleInfo * )self->ruleInfos->get(self->ruleInfos, i) ;
		if (info->cid == cid) {
			return info; 
		}
	}
	return NULL; 
}


void  SuiDesigner$AutoTile$buildRuleInfos(SuiDesigner$AutoTile *  self, SuiDesigner$Tileset *  ts){
	self->ruleInfos->clear(self->ruleInfos) ;
	for (int  i = 0; i < self->neighborIdArr->size; i++) {
		int  neighborId = self->neighborIdArr->data[i];
		int  cid = self->neighborIdToCid(self, ts, neighborId) ;
		SuiDesigner$RuleInfo *  info = self->gocRuleInfoByCid(self, cid) ;
		Sgl$IntArray$append(info->neighborIdArr, neighborId) ;
	}
	for (int  i = 0; i < self->ruleInfos->size(self->ruleInfos) ; i++) {
		SuiDesigner$RuleInfo *  info = (SuiDesigner$RuleInfo * )self->ruleInfos->get(self->ruleInfos, i) ;
		info->buildRuleInt(info, ts) ;
	}
}


int  SuiDesigner$AutoTile$mkRuleIntOfTile(SuiDesigner$AutoTile *  self, SuiDesigner$TileMap *  map, SuiDesigner$TileLayer *  layer, SuiDesigner$Tileset *  ts, int  cellIndex){
	int  x = cellIndex % map->width;
	int  y = cellIndex / map->width;
	int  lt = self->isAutoTileByLayerPos(self, map, layer, ts, x - 1, y - 1) ;
	int  ct = self->isAutoTileByLayerPos(self, map, layer, ts, x - 0, y - 1) ;
	int  rt = self->isAutoTileByLayerPos(self, map, layer, ts, x + 1, y - 1) ;
	int  lm = self->isAutoTileByLayerPos(self, map, layer, ts, x - 1, y - 0) ;
	int  cm = self->isAutoTileByLayerPos(self, map, layer, ts, x - 0, y - 0) ;
	int  rm = self->isAutoTileByLayerPos(self, map, layer, ts, x + 1, y - 0) ;
	int  lb = self->isAutoTileByLayerPos(self, map, layer, ts, x - 1, y + 1) ;
	int  cb = self->isAutoTileByLayerPos(self, map, layer, ts, x - 0, y + 1) ;
	int  rb = self->isAutoTileByLayerPos(self, map, layer, ts, x + 1, y + 1) ;
	int  ret = SuiDesigner$RuleInfo_mkRuleInt(lt, ct, rt, lm, cm, rm, lb, cb, rb) ;
	return ret; 
}




//vtable instance
Vtable_SuiDesigner$RandomTile _vtable_SuiDesigner$RandomTile;

// init meta

void SuiDesigner$RandomTile_initMeta(Vtable_SuiDesigner$RandomTile *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "gidArr", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner$RandomTile, gidArr), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$RandomTile* Vtable_SuiDesigner$RandomTile_init(Vtable_SuiDesigner$RandomTile* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$RandomTile;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$SpecialTile_init(&_vtable_SuiDesigner$SpecialTile);

	// init by super vtable init function
    Vtable_SuiDesigner$SpecialTile_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$SpecialTile;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$RandomTile_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$RandomTile";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$RandomTile_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$RandomTile_fini(SuiDesigner$RandomTile *self){
	//super fini
    SuiDesigner$SpecialTile_fini((SuiDesigner$SpecialTile *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$RandomTile*)self)->gidArr);

}

// init fields function


void SuiDesigner$RandomTile_init_fields(SuiDesigner$RandomTile *self){
	//super class
    SuiDesigner$SpecialTile_init_fields((SuiDesigner$SpecialTile*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$RandomTile_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$RandomTile*)self)->gidArr, Sgl$IntArray_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$SpecialTile*)self)->getGid = (void*)SuiDesigner$RandomTile$getGid;
	((SuiDesigner$SpecialTile*)self)->setTileAtGid = (void*)SuiDesigner$RandomTile$setTileAtGid;
}

// init function

void SuiDesigner$RandomTile_init(SuiDesigner$RandomTile *self, void *pOwner){
    Vtable_SuiDesigner$RandomTile_init(&_vtable_SuiDesigner$RandomTile);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$RandomTile;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$RandomTile_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$RandomTile * SuiDesigner$RandomTile_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$RandomTile *self = calloc(1, sizeof(SuiDesigner$RandomTile));
	
    SuiDesigner$RandomTile_init(self, pOwner);
    return self;
}


// class members
int  SuiDesigner$RandomTile$getGid(SuiDesigner$RandomTile *  self){
	if (self->gidArr->size > 0) {
		return Sgl$IntArray$get(self->gidArr, 0) ; 
	}
	return -1; 
}


void  SuiDesigner$RandomTile$setTileAtGid(SuiDesigner$RandomTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  tileLayer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex){
	int  idx = Orc$randRange(0, self->gidArr->size) ;
	int  actualGid = Sgl$IntArray$get(self->gidArr, idx) ;
	Sgl$IntArray$set(tileLayer->data, cellIndex, actualGid) ;
}




//vtable instance
Vtable_SuiDesigner$AnimTile _vtable_SuiDesigner$AnimTile;

// init meta

void SuiDesigner$AnimTile_initMeta(Vtable_SuiDesigner$AnimTile *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "gidArr", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner$AnimTile, gidArr), true, false, 1);

	orc_metaField_method(&pNext, "getDrawGid", offsetof(SuiDesigner$AnimTile, getDrawGid));
}


// vtable init


Vtable_SuiDesigner$AnimTile* Vtable_SuiDesigner$AnimTile_init(Vtable_SuiDesigner$AnimTile* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$AnimTile;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$SpecialTile_init(&_vtable_SuiDesigner$SpecialTile);

	// init by super vtable init function
    Vtable_SuiDesigner$SpecialTile_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$SpecialTile;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$AnimTile_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$AnimTile";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$AnimTile_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$AnimTile_fini(SuiDesigner$AnimTile *self){
	//super fini
    SuiDesigner$SpecialTile_fini((SuiDesigner$SpecialTile *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$AnimTile*)self)->gidArr);

}

// init fields function


void SuiDesigner$AnimTile_init_fields(SuiDesigner$AnimTile *self){
	//super class
    SuiDesigner$SpecialTile_init_fields((SuiDesigner$SpecialTile*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$AnimTile_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$AnimTile*)self)->gidArr, Sgl$IntArray_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$SpecialTile*)self)->getGid = (void*)SuiDesigner$AnimTile$getGid;
	((SuiDesigner$SpecialTile*)self)->setTileAtGid = (void*)SuiDesigner$AnimTile$setTileAtGid;
	((SuiDesigner$AnimTile*)self)->getDrawGid = (void*)SuiDesigner$AnimTile$getDrawGid;
}

// init function

void SuiDesigner$AnimTile_init(SuiDesigner$AnimTile *self, void *pOwner){
    Vtable_SuiDesigner$AnimTile_init(&_vtable_SuiDesigner$AnimTile);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$AnimTile;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$AnimTile_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$AnimTile * SuiDesigner$AnimTile_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$AnimTile *self = calloc(1, sizeof(SuiDesigner$AnimTile));
	
    SuiDesigner$AnimTile_init(self, pOwner);
    return self;
}


// class members
int  SuiDesigner$AnimTile$getGid(SuiDesigner$AnimTile *  self){
	if (self->gidArr->size > 0) {
		return Sgl$IntArray$get(self->gidArr, 0) ; 
	}
	return -1; 
}


void  SuiDesigner$AnimTile$setTileAtGid(SuiDesigner$AnimTile *  self, SuiDesigner$TileEditor *  te, SuiDesigner$TileLayer *  tileLayer, SuiDesigner$Tileset *  ts, int  gid, int  cellIndex){
	Sgl$IntArray$set(tileLayer->data, cellIndex, gid) ;
}


int  SuiDesigner$AnimTile$getDrawGid(SuiDesigner$AnimTile *  self, int  frameId){
	if (self->gidArr->size > 0) {
		int  idx = frameId % self->gidArr->size;
		return Sgl$IntArray$get(self->gidArr, idx) ; 
	}
	return -1; 
}




//vtable instance
Vtable_SuiDesigner$Tileset _vtable_SuiDesigner$Tileset;

// init meta

void SuiDesigner$Tileset_initMeta(Vtable_SuiDesigner$Tileset *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "imgPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$Tileset, imgPath), true, false, 1);
	orc_metaField_primitive(&pNext, "startGid", OrcMetaType_int, offsetof(SuiDesigner$Tileset, startGid), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "rows", OrcMetaType_int, offsetof(SuiDesigner$Tileset, rows), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "cols", OrcMetaType_int, offsetof(SuiDesigner$Tileset, cols), 0, 0, 0, 0);//int
	orc_metaField_struct(&pNext, "_imgSize", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner$Tileset, _imgSize), false, false, 0);
	orc_metaField_primitive(&pNext, "_tileWidth", OrcMetaType_int, offsetof(SuiDesigner$Tileset, _tileWidth), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "_tileHeight", OrcMetaType_int, offsetof(SuiDesigner$Tileset, _tileHeight), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "specialTiles", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$Tileset, specialTiles), true, false, 1);
	orc_metaField_class(&pNext, "img", ((Vtable_Object*)Vtable_SuiCore$Image_init(0)), offsetof(SuiDesigner$Tileset, img), true, false, 1);

	orc_metaField_method(&pNext, "getSpecialTileAtGid", offsetof(SuiDesigner$Tileset, getSpecialTileAtGid));
	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$Tileset, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$Tileset, toJson));
	orc_metaField_method(&pNext, "calcEndGid", offsetof(SuiDesigner$Tileset, calcEndGid));
	orc_metaField_method(&pNext, "isGidBelong", offsetof(SuiDesigner$Tileset, isGidBelong));
	orc_metaField_method(&pNext, "calcGid", offsetof(SuiDesigner$Tileset, calcGid));
	orc_metaField_method(&pNext, "dissolveGidToGridPos", offsetof(SuiDesigner$Tileset, dissolveGidToGridPos));
	orc_metaField_method(&pNext, "loadImage", offsetof(SuiDesigner$Tileset, loadImage));
	orc_metaField_method(&pNext, "calcRowsCols", offsetof(SuiDesigner$Tileset, calcRowsCols));
}


// vtable init


Vtable_SuiDesigner$Tileset* Vtable_SuiDesigner$Tileset_init(Vtable_SuiDesigner$Tileset* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Tileset;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Tileset_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Tileset";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Tileset_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$Tileset_fini(SuiDesigner$Tileset *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Tileset*)self)->imgPath);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Tileset*)self)->specialTiles);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Tileset*)self)->img);

}

// init fields function


void SuiDesigner$Tileset_init_fields(SuiDesigner$Tileset *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Tileset_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Tileset*)self)->imgPath, Orc$str(&tmpReturn_1, "") );
	((SuiDesigner$Tileset*)self)->startGid = 1000000;
	((SuiDesigner$Tileset*)self)->rows = 1;
	((SuiDesigner$Tileset*)self)->cols = 1;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Tileset*)self)->specialTiles, Orc$List_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$Tileset*)self)->img, NULL);
    }
	((SuiDesigner$Tileset*)self)->getSpecialTileAtGid = (void*)SuiDesigner$Tileset$getSpecialTileAtGid;
	((SuiDesigner$Tileset*)self)->fromJson = (void*)SuiDesigner$Tileset$fromJson;
	((SuiDesigner$Tileset*)self)->toJson = (void*)SuiDesigner$Tileset$toJson;
	((SuiDesigner$Tileset*)self)->calcEndGid = (void*)SuiDesigner$Tileset$calcEndGid;
	((SuiDesigner$Tileset*)self)->isGidBelong = (void*)SuiDesigner$Tileset$isGidBelong;
	((SuiDesigner$Tileset*)self)->calcGid = (void*)SuiDesigner$Tileset$calcGid;
	((SuiDesigner$Tileset*)self)->dissolveGidToGridPos = (void*)SuiDesigner$Tileset$dissolveGidToGridPos;
	((SuiDesigner$Tileset*)self)->loadImage = (void*)SuiDesigner$Tileset$loadImage;
	((SuiDesigner$Tileset*)self)->calcRowsCols = (void*)SuiDesigner$Tileset$calcRowsCols;
}

// init function

void SuiDesigner$Tileset_init(SuiDesigner$Tileset *self, void *pOwner){
    Vtable_SuiDesigner$Tileset_init(&_vtable_SuiDesigner$Tileset);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Tileset;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Tileset_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Tileset * SuiDesigner$Tileset_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Tileset *self = calloc(1, sizeof(SuiDesigner$Tileset));
	
    SuiDesigner$Tileset_init(self, pOwner);
    return self;
}


// class members
SuiDesigner$SpecialTile *  SuiDesigner$Tileset$getSpecialTileAtGid(SuiDesigner$Tileset *  self, int  gid){
	for (int  i = 0; i < self->specialTiles->size(self->specialTiles) ; i++) {
		SuiDesigner$SpecialTile *  st = (SuiDesigner$SpecialTile * )self->specialTiles->get(self->specialTiles, i) ;
		if (st->getGid(st)  == gid) {
			return st; 
		}
	}
	return NULL; 
}


void  SuiDesigner$Tileset$fromJson(SuiDesigner$Tileset *  self, Json$Json *  jo){
	self->rows = jo->getNumber(jo, "rows") ;
	self->cols = jo->getNumber(jo, "cols") ;
	self->startGid = jo->getNumber(jo, "startGid") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Tileset, imgPath) , jo->getString(&tmpReturn_1, jo, "imgPath") ) ;
}


void  SuiDesigner$Tileset$toJson(SuiDesigner$Tileset *  self, Json$Json *  jo){
	jo->putNumber(jo, "rows", self->rows) ;
	jo->putNumber(jo, "cols", self->cols) ;
	jo->putNumber(jo, "startGid", self->startGid) ;
	jo->putString(jo, "imgPath", self->imgPath) ;
}


int  SuiDesigner$Tileset$calcEndGid(SuiDesigner$Tileset *  self){
	int  gid = self->startGid + self->cols * self->rows;
	return gid; 
}


bool  SuiDesigner$Tileset$isGidBelong(SuiDesigner$Tileset *  self, int  gid){
	int  end = self->calcEndGid(self) ;
	return gid >= self->startGid && gid < end; 
}


int  SuiDesigner$Tileset$calcGid(SuiDesigner$Tileset *  self, SuiCore$Vec2 gridPos){
	int  gid = self->startGid + gridPos.y * self->cols + gridPos.x;
	return gid; 
}


SuiCore$Vec2 SuiDesigner$Tileset$dissolveGidToGridPos(SuiDesigner$Tileset *  self, int  gid){
	int  idx = gid - self->startGid;
	int  c = idx % self->cols;
	int  r = idx / self->cols;
	return SuiCore$mkVec2(c, r) ; 
}


SuiCore$Image *  SuiDesigner$Tileset$loadImage(SuiDesigner$Tileset *  self){
	if (self->img == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Tileset, img) , SuiCore$loadImage(&tmpReturn_1, self->imgPath->str) ) ;
	}
	return self->img; 
}


void  SuiDesigner$Tileset$calcRowsCols(SuiDesigner$Tileset *  self, SuiCore$Vec2 imgSize, int  tileWidth, int  tileHeight){
	if (tileWidth <= 0 || tileHeight <= 0) {
		printf("ERROR: tile size is 0\n") ;
		return ; 
	}
	self->_imgSize = imgSize;
	self->_tileWidth = tileWidth;
	self->_tileHeight = tileHeight;
	self->cols = ceil(imgSize.x / (float )tileWidth) ;
	self->rows = ceil(imgSize.y / (float )tileHeight) ;
	printf("calcRowsCols:. size:%f,%f, tile:%d,%d, cols:%d, rows:%d\n", imgSize.x, imgSize.y, tileWidth, tileHeight, self->cols, self->rows) ;
}




//vtable instance
Vtable_SuiDesigner$Layer _vtable_SuiDesigner$Layer;

// init meta

void SuiDesigner$Layer_initMeta(Vtable_SuiDesigner$Layer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$Layer, name), true, false, 1);

	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$Layer, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$Layer, toJson));
}


// vtable init


Vtable_SuiDesigner$Layer* Vtable_SuiDesigner$Layer_init(Vtable_SuiDesigner$Layer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Layer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Layer_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Layer";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Layer_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$Layer_fini(SuiDesigner$Layer *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$Layer*)self)->name);

}

// init fields function


void SuiDesigner$Layer_init_fields(SuiDesigner$Layer *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Layer_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$Layer*)self)->name, Orc$str(&tmpReturn_1, "") );
    }
	((SuiDesigner$Layer*)self)->fromJson = (void*)SuiDesigner$Layer$fromJson;
	((SuiDesigner$Layer*)self)->toJson = (void*)SuiDesigner$Layer$toJson;
}

// init function

void SuiDesigner$Layer_init(SuiDesigner$Layer *self, void *pOwner){
    Vtable_SuiDesigner$Layer_init(&_vtable_SuiDesigner$Layer);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Layer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Layer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Layer * SuiDesigner$Layer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Layer *self = calloc(1, sizeof(SuiDesigner$Layer));
	
    SuiDesigner$Layer_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$Layer$fromJson(SuiDesigner$Layer *  self, Json$Json *  jo){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$Layer, name) , jo->getString(&tmpReturn_1, jo, "name") ) ;
}


void  SuiDesigner$Layer$toJson(SuiDesigner$Layer *  self, Json$Json *  jo){
	jo->putString(jo, "name", self->name) ;
}




//vtable instance
Vtable_SuiDesigner$TileLayer _vtable_SuiDesigner$TileLayer;

// init meta

void SuiDesigner$TileLayer_initMeta(Vtable_SuiDesigner$TileLayer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "data", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner$TileLayer, data), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$TileLayer* Vtable_SuiDesigner$TileLayer_init(Vtable_SuiDesigner$TileLayer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$TileLayer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$Layer_init(&_vtable_SuiDesigner$Layer);

	// init by super vtable init function
    Vtable_SuiDesigner$Layer_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$Layer;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$TileLayer_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$TileLayer";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$TileLayer_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$TileLayer_fini(SuiDesigner$TileLayer *self){
	//super fini
    SuiDesigner$Layer_fini((SuiDesigner$Layer *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileLayer*)self)->data);

}

// init fields function


void SuiDesigner$TileLayer_init_fields(SuiDesigner$TileLayer *self){
	//super class
    SuiDesigner$Layer_init_fields((SuiDesigner$Layer*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$TileLayer_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileLayer*)self)->data, Sgl$IntArray_new(&tmpNewOwner_1) );
    }
	((SuiDesigner$Layer*)self)->fromJson = (void*)SuiDesigner$TileLayer$fromJson;
	((SuiDesigner$Layer*)self)->toJson = (void*)SuiDesigner$TileLayer$toJson;
}

// init function

void SuiDesigner$TileLayer_init(SuiDesigner$TileLayer *self, void *pOwner){
    Vtable_SuiDesigner$TileLayer_init(&_vtable_SuiDesigner$TileLayer);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$TileLayer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$TileLayer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$TileLayer * SuiDesigner$TileLayer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$TileLayer *self = calloc(1, sizeof(SuiDesigner$TileLayer));
	
    SuiDesigner$TileLayer_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$TileLayer$fromJson(SuiDesigner$TileLayer *  self, Json$Json *  jo){
	SuiDesigner$Layer$fromJson(self, jo) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	Sgl$IntArray$fromJson(self->data, jo->get(&tmpReturn_1, jo, "data") ) ;
}


void  SuiDesigner$TileLayer$toJson(SuiDesigner$TileLayer *  self, Json$Json *  jo){
	SuiDesigner$Layer$toJson(self, jo) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	jo->put(jo, "data", Sgl$IntArray$mkJson(&tmpReturn_1, self->data) ) ;
}




//vtable instance
Vtable_SuiDesigner$TileMap _vtable_SuiDesigner$TileMap;

// init meta

void SuiDesigner$TileMap_initMeta(Vtable_SuiDesigner$TileMap *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "fps", OrcMetaType_int, offsetof(SuiDesigner$TileMap, fps), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "width", OrcMetaType_int, offsetof(SuiDesigner$TileMap, width), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "height", OrcMetaType_int, offsetof(SuiDesigner$TileMap, height), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "tileWidth", OrcMetaType_int, offsetof(SuiDesigner$TileMap, tileWidth), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "tileHeight", OrcMetaType_int, offsetof(SuiDesigner$TileMap, tileHeight), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "tilesets", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$TileMap, tilesets), true, false, 1);
	orc_metaField_class(&pNext, "layers", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$TileMap, layers), true, false, 1);

	orc_metaField_method(&pNext, "fromJson", offsetof(SuiDesigner$TileMap, fromJson));
	orc_metaField_method(&pNext, "toJson", offsetof(SuiDesigner$TileMap, toJson));
	orc_metaField_method(&pNext, "findTilesetByGid", offsetof(SuiDesigner$TileMap, findTilesetByGid));
	orc_metaField_method(&pNext, "findFreeStartGid", offsetof(SuiDesigner$TileMap, findFreeStartGid));
}


// vtable init


Vtable_SuiDesigner$TileMap* Vtable_SuiDesigner$TileMap_init(Vtable_SuiDesigner$TileMap* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$TileMap;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$TileMap_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$TileMap";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$TileMap_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$TileMap_fini(SuiDesigner$TileMap *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMap*)self)->tilesets);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMap*)self)->layers);

}

// init fields function


void SuiDesigner$TileMap_init_fields(SuiDesigner$TileMap *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$TileMap_fini;
	//fields
    {
	((SuiDesigner$TileMap*)self)->fps = 2;
	((SuiDesigner$TileMap*)self)->width = 100;
	((SuiDesigner$TileMap*)self)->height = 100;
	((SuiDesigner$TileMap*)self)->tileWidth = 32;
	((SuiDesigner$TileMap*)self)->tileHeight = 32;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMap*)self)->tilesets, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMap*)self)->layers, Orc$List_new(&tmpNewOwner_2) );
    }
	((SuiDesigner$TileMap*)self)->fromJson = (void*)SuiDesigner$TileMap$fromJson;
	((SuiDesigner$TileMap*)self)->toJson = (void*)SuiDesigner$TileMap$toJson;
	((Object*)self)->ctor = (void*)SuiDesigner$TileMap$ctor;
	((SuiDesigner$TileMap*)self)->findTilesetByGid = (void*)SuiDesigner$TileMap$findTilesetByGid;
	((SuiDesigner$TileMap*)self)->findFreeStartGid = (void*)SuiDesigner$TileMap$findFreeStartGid;
}

// init function

void SuiDesigner$TileMap_init(SuiDesigner$TileMap *self, void *pOwner){
    Vtable_SuiDesigner$TileMap_init(&_vtable_SuiDesigner$TileMap);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$TileMap;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$TileMap_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$TileMap * SuiDesigner$TileMap_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$TileMap *self = calloc(1, sizeof(SuiDesigner$TileMap));
	
    SuiDesigner$TileMap_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$TileMap$fromJson(SuiDesigner$TileMap *  self, Json$Json *  jo){
	self->width = jo->getNumber(jo, "width") ;
	self->height = jo->getNumber(jo, "height") ;
	self->tileWidth = jo->getNumber(jo, "tileWidth") ;
	self->tileHeight = jo->getNumber(jo, "tileHeight") ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$TileMap, tilesets) , jo->getObjectsByVtable(&tmpReturn_1, jo, "tilesets", Vtable_SuiDesigner$Tileset_init(NULL)) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$TileMap, layers) , jo->getObjectsByVtable(&tmpReturn_2, jo, "layers", Vtable_SuiDesigner$TileLayer_init(NULL)) ) ;
}


void  SuiDesigner$TileMap$toJson(SuiDesigner$TileMap *  self, Json$Json *  jo){
	jo->putNumber(jo, "width", self->width) ;
	jo->putNumber(jo, "height", self->height) ;
	jo->putNumber(jo, "tileWidth", self->tileWidth) ;
	jo->putNumber(jo, "tileHeight", self->tileHeight) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	jo->put(jo, "tilesets", Json$Json_toJson(&tmpReturn_1, self->tilesets) ) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_2 = NULL;
	jo->put(jo, "layers", Json$Json_toJson(&tmpReturn_2, self->layers) ) ;
}


void  SuiDesigner$TileMap$ctor(SuiDesigner$TileMap *  self){
	{
		URGC_VAR_CLEANUP_CLASS SuiDesigner$Tileset*  layer = (layer=NULL,urgc_init_var_class((void**)&layer, SuiDesigner$Tileset_new(&layer) ));
		Orc$String$set(layer->imgPath, "../asset/DungeonTileset/dungeon.png") ;
		self->tilesets->add(self->tilesets, layer) ;
	}
}


SuiDesigner$Tileset *  SuiDesigner$TileMap$findTilesetByGid(SuiDesigner$TileMap *  self, int  gid){
	int  l = self->tilesets->size(self->tilesets) ;
	for (int  i = 0; i < l; i++) {
		SuiDesigner$Tileset *  ts = (SuiDesigner$Tileset * )self->tilesets->get(self->tilesets, i) ;
		if (ts->isGidBelong(ts, gid) ) {
			return ts; 
		}
	}
	return NULL; 
}


int  SuiDesigner$TileMap$findFreeStartGid(SuiDesigner$TileMap *  self){
	for (int  i = 1; i < 200; i++) {
		int  startGid = i * 1000000;
		bool  found = false;
		for (int  j = 0; j < self->tilesets->size(self->tilesets) ; j++) {
			SuiDesigner$Tileset *  ts = (SuiDesigner$Tileset * )self->tilesets->get(self->tilesets, j) ;
			if (ts->startGid == startGid) {
				found = true;
				break;
			}
		}
		if (!found) {
			return startGid; 
		}
	}
	return -1; 
}




//vtable instance
Vtable_SuiDesigner$ElapsedMs _vtable_SuiDesigner$ElapsedMs;

// init meta

void SuiDesigner$ElapsedMs_initMeta(Vtable_SuiDesigner$ElapsedMs *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "prevMs", OrcMetaType_long_long, offsetof(SuiDesigner$ElapsedMs, prevMs), 0, 0, 0, 0);//longlong
	orc_metaField_primitive(&pNext, "accumMs", OrcMetaType_long_long, offsetof(SuiDesigner$ElapsedMs, accumMs), 0, 0, 0, 0);//longlong

	orc_metaField_method(&pNext, "tick", offsetof(SuiDesigner$ElapsedMs, tick));
	orc_metaField_method(&pNext, "calcFrameIndex", offsetof(SuiDesigner$ElapsedMs, calcFrameIndex));
}


// vtable init


Vtable_SuiDesigner$ElapsedMs* Vtable_SuiDesigner$ElapsedMs_init(Vtable_SuiDesigner$ElapsedMs* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ElapsedMs;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ElapsedMs_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ElapsedMs";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ElapsedMs_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$ElapsedMs_fini(SuiDesigner$ElapsedMs *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$ElapsedMs_init_fields(SuiDesigner$ElapsedMs *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ElapsedMs_fini;
	//fields
    {
	((SuiDesigner$ElapsedMs*)self)->prevMs = 0;
	((SuiDesigner$ElapsedMs*)self)->accumMs = 0;
    }
	((SuiDesigner$ElapsedMs*)self)->tick = (void*)SuiDesigner$ElapsedMs$tick;
	((SuiDesigner$ElapsedMs*)self)->calcFrameIndex = (void*)SuiDesigner$ElapsedMs$calcFrameIndex;
}

// init function

void SuiDesigner$ElapsedMs_init(SuiDesigner$ElapsedMs *self, void *pOwner){
    Vtable_SuiDesigner$ElapsedMs_init(&_vtable_SuiDesigner$ElapsedMs);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ElapsedMs;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ElapsedMs_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ElapsedMs * SuiDesigner$ElapsedMs_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ElapsedMs *self = calloc(1, sizeof(SuiDesigner$ElapsedMs));
	
    SuiDesigner$ElapsedMs_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ElapsedMs$tick(SuiDesigner$ElapsedMs *  self){
	long long  nowMs = Orc$Time_unixMs() ;
	if (self->prevMs == 0) {
		self->accumMs = 0;
	}
	else {
		self->accumMs += nowMs - self->prevMs;
	}
	self->prevMs = nowMs;
}


long long  SuiDesigner$ElapsedMs$calcFrameIndex(SuiDesigner$ElapsedMs *  self, int  fps){
	double  frameIndex = self->accumMs / (1000L / (double )fps);
	return frameIndex; 
}




//vtable instance
Vtable_SuiDesigner$TileMapEditView _vtable_SuiDesigner$TileMapEditView;

// init meta

void SuiDesigner$TileMapEditView_initMeta(Vtable_SuiDesigner$TileMapEditView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "map", ((Vtable_Object*)Vtable_SuiDesigner$TileMap_init(0)), offsetof(SuiDesigner$TileMapEditView, map), true, false, 1);
	orc_metaField_class(&pNext, "viewportView", ((Vtable_Object*)Vtable_SuiCore$ViewBase_init(0)), offsetof(SuiDesigner$TileMapEditView, viewportView), true, false, 1);
	orc_metaField_struct(&pNext, "mousePosInViewport", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner$TileMapEditView, mousePosInViewport), false, false, 0);
	orc_metaField_class(&pNext, "sceneCtrl", ((Vtable_Object*)Vtable_SuiDesigner$SceneCtrl_init(0)), offsetof(SuiDesigner$TileMapEditView, sceneCtrl), true, false, 1);
	orc_metaField_class(&pNext, "tileEditor", ((Vtable_Object*)Vtable_SuiDesigner$TileEditor_init(0)), offsetof(SuiDesigner$TileMapEditView, tileEditor), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$TileMapEditView, drag), true, false, 1);
	orc_metaField_class(&pNext, "elapsedMs", ((Vtable_Object*)Vtable_SuiDesigner$ElapsedMs_init(0)), offsetof(SuiDesigner$TileMapEditView, elapsedMs), true, false, 1);

	orc_metaField_method(&pNext, "getMouseScenePos", offsetof(SuiDesigner$TileMapEditView, getMouseScenePos));
	orc_metaField_method(&pNext, "setTileAtGrid", offsetof(SuiDesigner$TileMapEditView, setTileAtGrid));
	orc_metaField_method(&pNext, "gridPosToCellIndex", offsetof(SuiDesigner$TileMapEditView, gridPosToCellIndex));
	orc_metaField_method(&pNext, "onViewportEvent", offsetof(SuiDesigner$TileMapEditView, onViewportEvent));
	orc_metaField_method(&pNext, "calcMouseGridPos", offsetof(SuiDesigner$TileMapEditView, calcMouseGridPos));
	orc_metaField_method(&pNext, "draw_tileLayer", offsetof(SuiDesigner$TileMapEditView, draw_tileLayer));
	orc_metaField_method(&pNext, "draw_map", offsetof(SuiDesigner$TileMapEditView, draw_map));
}


// vtable init


Vtable_SuiDesigner$TileMapEditView* Vtable_SuiDesigner$TileMapEditView_init(Vtable_SuiDesigner$TileMapEditView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$TileMapEditView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewBase_init(&_vtable_SuiCore$ViewBase);

	// init by super vtable init function
    Vtable_SuiCore$ViewBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$TileMapEditView_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$TileMapEditView";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$TileMapEditView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$TileMapEditView_fini(SuiDesigner$TileMapEditView *self){
	//super fini
    SuiCore$ViewBase_fini((SuiCore$ViewBase *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->map);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->viewportView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->sceneCtrl);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->tileEditor);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->elapsedMs);

}

// init fields function


void SuiDesigner$TileMapEditView_init_fields(SuiDesigner$TileMapEditView *self){
	//super class
    SuiCore$ViewBase_init_fields((SuiCore$ViewBase*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$TileMapEditView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->map, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->viewportView, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->sceneCtrl, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->tileEditor, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ElapsedMs*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileMapEditView*)self)->elapsedMs, SuiDesigner$ElapsedMs_new(&tmpNewOwner_2) );
    }
	((Object*)self)->ctor = (void*)SuiDesigner$TileMapEditView$ctor;
	((SuiDesigner$TileMapEditView*)self)->getMouseScenePos = (void*)SuiDesigner$TileMapEditView$getMouseScenePos;
	((SuiDesigner$TileMapEditView*)self)->setTileAtGrid = (void*)SuiDesigner$TileMapEditView$setTileAtGrid;
	((SuiDesigner$TileMapEditView*)self)->gridPosToCellIndex = (void*)SuiDesigner$TileMapEditView$gridPosToCellIndex;
	((SuiDesigner$TileMapEditView*)self)->onViewportEvent = (void*)SuiDesigner$TileMapEditView$onViewportEvent;
	((SuiDesigner$TileMapEditView*)self)->calcMouseGridPos = (void*)SuiDesigner$TileMapEditView$calcMouseGridPos;
	((SuiDesigner$TileMapEditView*)self)->draw_tileLayer = (void*)SuiDesigner$TileMapEditView$draw_tileLayer;
	((SuiDesigner$TileMapEditView*)self)->draw_map = (void*)SuiDesigner$TileMapEditView$draw_map;
	((SuiCore$ViewBase*)self)->draw_self = (void*)SuiDesigner$TileMapEditView$draw_self;
}

// init function

void SuiDesigner$TileMapEditView_init(SuiDesigner$TileMapEditView *self, void *pOwner){
    Vtable_SuiDesigner$TileMapEditView_init(&_vtable_SuiDesigner$TileMapEditView);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$TileMapEditView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$TileMapEditView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$TileMapEditView * SuiDesigner$TileMapEditView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$TileMapEditView *self = calloc(1, sizeof(SuiDesigner$TileMapEditView));
	
    SuiDesigner$TileMapEditView_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$TileMapEditView$ctor(SuiDesigner$TileMapEditView *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_561_15*  __var___Block_561_15 = (__var___Block_561_15=NULL,urgc_init_var((void**)&__var___Block_561_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_561_15) , __finiBlock___Block_561_15) ));
	urgc_set_field_class(__var___Block_561_15, (void * )offsetof(SuiDesigner$__Block_561_15, self) , self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_562_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_562_27(&tmpReturn_1, __var___Block_561_15) ) ;
}


SuiCore$Vec2 SuiDesigner$TileMapEditView$getMouseScenePos(SuiDesigner$TileMapEditView *  self){
	SuiCore$Vec2 clientPos = SuiCore$Mouse_getPosOfWindow(((SuiCore$Node * )self)->ownerWindow) ;
	self->mousePosInViewport = self->viewportView->worldToLocal(self->viewportView, clientPos.x, clientPos.y) ;
	SuiCore$Vec2 scenePos = self->sceneCtrl->worldToLocal(self->sceneCtrl, self->mousePosInViewport.x, self->mousePosInViewport.y) ;
	return scenePos; 
}


void  SuiDesigner$TileMapEditView$setTileAtGrid(SuiDesigner$TileMapEditView *  self, SuiCore$Vec2 gridPos){
	if (self->tileEditor == NULL || self->tileEditor->curLayer == NULL || self->tileEditor->curTileset == NULL || ((Sgl$StructArrayBase * )self->tileEditor->curTilePosArr)->size == 0) {
		printf("参数异常，无法设置tile\n") ;
		return ; 
	}
	SuiDesigner$Layer *  layer = self->tileEditor->curLayer;
	if (!(Orc_instanceof((Object*)layer, (Vtable_Object*)Vtable_SuiDesigner$TileLayer_init(NULL)))) {
		printf("当前layer不是TileLayer\n") ;
	}
	SuiDesigner$TileLayer *  tileLayer = (SuiDesigner$TileLayer * )layer;
	SuiCore$Vec2 firstPos = self->tileEditor->curTilePosArr->data[0];
	for (int  i = 0; i < ((Sgl$StructArrayBase * )self->tileEditor->curTilePosArr)->size; i++) {
		SuiCore$Vec2 tilePos = self->tileEditor->curTilePosArr->data[i];
		SuiCore$Vec2 offset = SuiCore$Vec2$sub(&tilePos, firstPos) ;
		SuiCore$Vec2 curGridPos = SuiCore$Vec2$add(&gridPos, offset) ;
		int  cellIndex = self->gridPosToCellIndex(self, curGridPos) ;
		if (cellIndex >= 0) {
			int  gid = self->tileEditor->curTileset->calcGid(self->tileEditor->curTileset, tilePos) ;
			SuiDesigner$SpecialTile *  st = self->tileEditor->curTileset->getSpecialTileAtGid(self->tileEditor->curTileset, gid) ;
			if (st) {
				st->setTileAtGid(st, self->tileEditor, tileLayer, self->tileEditor->curTileset, gid, cellIndex) ;
			}
			else {
				printf("set tile: cellIndex:%d, gid:%d\n", cellIndex, gid) ;
				Sgl$IntArray$set(tileLayer->data, cellIndex, gid) ;
			}
		}
	}
}


int  SuiDesigner$TileMapEditView$gridPosToCellIndex(SuiDesigner$TileMapEditView *  self, SuiCore$Vec2 gridPos){
	if (self->tileEditor && self->tileEditor->map) {
		int  idx = self->tileEditor->map->width * gridPos.y + gridPos.x;
		return idx; 
	}
	return -1; 
}


bool  SuiDesigner$TileMapEditView$onViewportEvent(SuiDesigner$TileMapEditView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEnterEvent_init(NULL))) {
		printf("鼠标进入事件\n") ;
		((SuiCore$ViewBase * )self)->setHover(self, true) ;
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseLeaveEvent_init(NULL))) {
		((SuiCore$ViewBase * )self)->setHover(self, false) ;
		printf("鼠标离开事件\n") ;
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (self->viewportView) {
			self->mousePosInViewport = self->viewportView->worldToLocal(self->viewportView, me->clientX, me->clientY) ;
		}
		if (me->button == 1 && me->isMouseDown) {
			self->drag->onMouseDown(self->drag, me) ;
		}
		if (me->button == 1 && me->isClickInBubble(me) ) {
			SuiCore$Vec2 scenePos = self->sceneCtrl->worldToLocal(self->sceneCtrl, self->mousePosInViewport.x, self->mousePosInViewport.y) ;
			SuiCore$Vec2 gridPos = self->calcMouseGridPos(self) ;
			self->setTileAtGrid(self, gridPos) ;
			printf("\nclient pos:%d,%d  down:%d,%d,%d,%d.  mousePosInViewport:%f,%f. scenePos:%f,%f. gridPos:%f,%f\n", me->clientX, me->clientY, me->isMouseDown, me->isMouseUp, me->isMouseMove, me->isWheel, self->mousePosInViewport.x, self->mousePosInViewport.y, scenePos.x, scenePos.y, gridPos.x, gridPos.y) ;
			return true; 
		}
	}
	return false; 
}


SuiCore$Vec2 SuiDesigner$TileMapEditView$calcMouseGridPos(SuiDesigner$TileMapEditView *  self){
	SuiCore$Vec2 pos = self->getMouseScenePos(self) ;
	int  tilew = self->map->tileWidth;
	int  tileh = self->map->tileHeight;
	int  col = pos.x / tilew;
	int  row = pos.y / tileh;
	printf("calcMouseGridPos. pos:%f,%f, tilew:%d,%d, grid:%d,%d\n", pos.x, pos.y, tilew, tileh, col, row) ;
	return SuiCore$mkVec2(col, row) ; 
}


void  SuiDesigner$TileMapEditView$draw_tileLayer(SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas, SuiDesigner$TileLayer *  layer){
	long long  frame = self->elapsedMs->calcFrameIndex(self->elapsedMs, self->map->fps) ;
	int  w = self->map->width;
	int  h = self->map->height;
	int  tilew = self->map->tileWidth;
	int  tileh = self->map->tileHeight;
	for (int  r = 0; r < h; r++) {
		for (int  c = 0; c < w; c++) {
			int  cell = r * self->map->width + c;
			int  gid = Sgl$IntArray$at(layer->data, cell) ;
			if (gid != 0) {
				SuiDesigner$Tileset *  ts = self->map->findTilesetByGid(self->map, gid) ;
				if (ts) {
					int  drawGid = gid;
					SuiDesigner$SpecialTile *  st = ts->getSpecialTileAtGid(ts, gid) ;
					if (st) {
						if (Orc_instanceof((Object*)st, (Vtable_Object*)Vtable_SuiDesigner$AnimTile_init(NULL))) {
							SuiDesigner$AnimTile *  at = (SuiDesigner$AnimTile * )st;
							drawGid = at->getDrawGid(at, frame) ;
						}
					}
					SuiCore$Image *  img = ts->loadImage(ts) ;
					if (img) {
						int  x = c * tilew;
						int  y = r * tileh;
						SuiCore$Vec2 tileGridPos = ts->dissolveGidToGridPos(ts, drawGid) ;
						int  tileX = tileGridPos.x * tilew;
						int  tileY = tileGridPos.y * tileh;
						SuiCore$Canvas$drawImageAtRect(canvas, img, tileX, tileY, tilew, tileh, x, y, tilew, tileh, 1) ;
					}
				}
			}
		}
	}
}


void  SuiDesigner$TileMapEditView$draw_map(SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas){
	if (self->map) {
		self->elapsedMs->tick(self->elapsedMs) ;
		int  l = self->map->layers->size(self->map->layers) ;
		for (int  i = 0; i < l; i++) {
			SuiDesigner$Layer *  layer = (SuiDesigner$Layer * )self->map->layers->get(self->map->layers, i) ;
			if (Orc_instanceof((Object*)layer, (Vtable_Object*)Vtable_SuiDesigner$TileLayer_init(NULL))) {
				self->draw_tileLayer(self, canvas, (SuiDesigner$TileLayer * )layer) ;
			}
		}
	}
}


void  SuiDesigner$TileMapEditView$draw_self(SuiDesigner$TileMapEditView *  self, SuiCore$Canvas *  canvas){
	self->draw_map(self, canvas) ;
	if (self->map) {
		if (((SuiCore$ViewBase * )self)->hover) {
			SuiCore$Vec2 pos = self->getMouseScenePos(self) ;
			if (0) {
				SuiCore$Canvas$beginPath(canvas) ;
				SuiCore$Canvas$moveTo(canvas, pos.x - 10000, pos.y) ;
				SuiCore$Canvas$lineTo(canvas, pos.x + 10000, pos.y) ;
				SuiCore$Canvas$moveTo(canvas, pos.x, pos.y - 10000) ;
				SuiCore$Canvas$lineTo(canvas, pos.x, pos.y + 10000) ;
				SuiCore$Canvas$strokeWidth(canvas, 1) ;
				SuiCore$Canvas$strokeColorByInt32(canvas, 0xffff0000) ;
				SuiCore$Canvas$stroke(canvas) ;
			}
			int  tilew = self->map->tileWidth;
			int  tileh = self->map->tileHeight;
			int  col = pos.x / tilew;
			int  row = pos.y / tileh;
			int  radius = 3;
			{
				SuiCore$Canvas$strokeWidth(canvas, 1) ;
				for (int  r = -radius; r <= radius; r++) {
					int  x = Orc$maxInt(col + -radius, 0)  * tilew;
					int  x2 = Orc$minInt(col + radius, self->map->width)  * tilew;
					int  y = Orc$clampInt(row + r, 0, self->map->height)  * tileh;
					SuiCore$Canvas$beginPath(canvas) ;
					SuiCore$Canvas$strokeColorByInt32(canvas, 0xffff0000) ;
					SuiCore$Canvas$moveTo(canvas, x, y) ;
					SuiCore$Canvas$lineTo(canvas, x2, y) ;
					SuiCore$Canvas$stroke(canvas) ;
				}
				for (int  r = -radius; r <= radius; r++) {
					int  y = Orc$maxInt(row + -radius, 0)  * tileh;
					int  y2 = Orc$minInt(row + radius, self->map->height)  * tileh;
					int  x = Orc$clampInt(col + r, 0, self->map->width)  * tilew;
					SuiCore$Canvas$beginPath(canvas) ;
					SuiCore$Canvas$strokeColorByInt32(canvas, 0xffff0000) ;
					SuiCore$Canvas$moveTo(canvas, x, y) ;
					SuiCore$Canvas$lineTo(canvas, x, y2) ;
					SuiCore$Canvas$stroke(canvas) ;
				}
			}
		}
	}
}



SuiDesigner$TileMapEditView*  SuiDesigner$mkTileMapEditView(SuiDesigner$TileMapEditView **  __outRef__, void *  parent, long long  key){
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (SuiDesigner$TileMapEditView* )SuiView$gocNode(&tmpReturn_1, key ? (void * )key : __builtin_return_address(0) , (SuiCore$Node * )parent, Vtable_SuiDesigner$TileMapEditView_init(NULL)) ) ; 
}


//vtable instance
Vtable_SuiDesigner$SceneViewCb _vtable_SuiDesigner$SceneViewCb;

// init meta

void SuiDesigner$SceneViewCb_initMeta(Vtable_SuiDesigner$SceneViewCb *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "ctrl", ((Vtable_Object*)Vtable_SuiDesigner$SceneCtrl_init(0)), offsetof(SuiDesigner$SceneViewCb, ctrl), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$SceneViewCb* Vtable_SuiDesigner$SceneViewCb_init(Vtable_SuiDesigner$SceneViewCb* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SceneViewCb;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$ChessBgViewCallback_init(&_vtable_SuiDesigner$ChessBgViewCallback);

	// init by super vtable init function
    Vtable_SuiDesigner$ChessBgViewCallback_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$ChessBgViewCallback;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SceneViewCb_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SceneViewCb";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SceneViewCb_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SceneViewCb_fini(SuiDesigner$SceneViewCb *self){
	//super fini
    SuiDesigner$ChessBgViewCallback_fini((SuiDesigner$ChessBgViewCallback *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneViewCb*)self)->ctrl);

}

// init fields function


void SuiDesigner$SceneViewCb_init_fields(SuiDesigner$SceneViewCb *self){
	//super class
    SuiDesigner$ChessBgViewCallback_init_fields((SuiDesigner$ChessBgViewCallback*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SceneViewCb_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneViewCb*)self)->ctrl, NULL);
    }
	((SuiCore$ViewCallback*)self)->afterDrawSelf = (void*)SuiDesigner$SceneViewCb$afterDrawSelf;
}

// init function

void SuiDesigner$SceneViewCb_init(SuiDesigner$SceneViewCb *self, void *pOwner){
    Vtable_SuiDesigner$SceneViewCb_init(&_vtable_SuiDesigner$SceneViewCb);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SceneViewCb;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SceneViewCb_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SceneViewCb * SuiDesigner$SceneViewCb_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SceneViewCb *self = calloc(1, sizeof(SuiDesigner$SceneViewCb));
	
    SuiDesigner$SceneViewCb_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SceneViewCb$afterDrawSelf(SuiDesigner$SceneViewCb *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas){
	if (self->ctrl) {
		SuiCore$Rect r = div->getViewRect(div) ;
		self->ctrl->degree->draw(self->ctrl->degree, canvas, self->ctrl->mat, r.w, r.h, 0, 0) ;
	}
}




//vtable instance
Vtable_SuiDesigner$SceneCtrl _vtable_SuiDesigner$SceneCtrl;

// init meta

void SuiDesigner$SceneCtrl_initMeta(Vtable_SuiDesigner$SceneCtrl *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "_translate", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner$SceneCtrl, _translate), false, false, 0);
	orc_metaField_primitive(&pNext, "_scale", OrcMetaType_float, offsetof(SuiDesigner$SceneCtrl, _scale), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "mat", SuiCore$Mat2d_getOrInitMetaStruct(), offsetof(SuiDesigner$SceneCtrl, mat), false, false, 0);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$SceneCtrl, drag), true, false, 1);
	orc_metaField_class(&pNext, "degree", ((Vtable_Object*)Vtable_SuiDesigner$DrawDegree_init(0)), offsetof(SuiDesigner$SceneCtrl, degree), true, false, 1);
	orc_metaField_class(&pNext, "contentView", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(SuiDesigner$SceneCtrl, contentView), true, false, 1);
	orc_metaField_class(&pNext, "sceneViewCb", ((Vtable_Object*)Vtable_SuiDesigner$SceneViewCb_init(0)), offsetof(SuiDesigner$SceneCtrl, sceneViewCb), true, false, 1);

	orc_metaField_method(&pNext, "onEvent", offsetof(SuiDesigner$SceneCtrl, onEvent));
	orc_metaField_method(&pNext, "setScale", offsetof(SuiDesigner$SceneCtrl, setScale));
	orc_metaField_method(&pNext, "updateMat", offsetof(SuiDesigner$SceneCtrl, updateMat));
	orc_metaField_method(&pNext, "localToWorld", offsetof(SuiDesigner$SceneCtrl, localToWorld));
	orc_metaField_method(&pNext, "worldToLocal", offsetof(SuiDesigner$SceneCtrl, worldToLocal));
	orc_metaField_method(&pNext, "clientToWorld", offsetof(SuiDesigner$SceneCtrl, clientToWorld));
	orc_metaField_method(&pNext, "clientToLocal", offsetof(SuiDesigner$SceneCtrl, clientToLocal));
	orc_metaField_method(&pNext, "translate", offsetof(SuiDesigner$SceneCtrl, translate));
	orc_metaField_method(&pNext, "setTranslate", offsetof(SuiDesigner$SceneCtrl, setTranslate));
	orc_metaField_method(&pNext, "identity", offsetof(SuiDesigner$SceneCtrl, identity));
	orc_metaField_method(&pNext, "performScaleByWheelEventAndSceneView", offsetof(SuiDesigner$SceneCtrl, performScaleByWheelEventAndSceneView));
}


// vtable init


Vtable_SuiDesigner$SceneCtrl* Vtable_SuiDesigner$SceneCtrl_init(Vtable_SuiDesigner$SceneCtrl* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$SceneCtrl;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$SceneCtrl_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$SceneCtrl";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$SceneCtrl_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$SceneCtrl_fini(SuiDesigner$SceneCtrl *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->degree);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->contentView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->sceneViewCb);

}

// init fields function


void SuiDesigner$SceneCtrl_init_fields(SuiDesigner$SceneCtrl *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$SceneCtrl_fini;
	//fields
    {
	((SuiDesigner$SceneCtrl*)self)->_scale = 1;
	((SuiDesigner$SceneCtrl*)self)->mat = SuiCore$mkMat2d() ;
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegree*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->degree, SuiDesigner$DrawDegree_new(&tmpNewOwner_2) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->contentView, NULL);
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SceneViewCb*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$SceneCtrl*)self)->sceneViewCb, SuiDesigner$SceneViewCb_new(&tmpNewOwner_3) );
    }
	((Object*)self)->ctor = (void*)SuiDesigner$SceneCtrl$ctor;
	((SuiDesigner$SceneCtrl*)self)->onEvent = (void*)SuiDesigner$SceneCtrl$onEvent;
	((SuiDesigner$SceneCtrl*)self)->setScale = (void*)SuiDesigner$SceneCtrl$setScale;
	((SuiDesigner$SceneCtrl*)self)->updateMat = (void*)SuiDesigner$SceneCtrl$updateMat;
	((SuiDesigner$SceneCtrl*)self)->localToWorld = (void*)SuiDesigner$SceneCtrl$localToWorld;
	((SuiDesigner$SceneCtrl*)self)->worldToLocal = (void*)SuiDesigner$SceneCtrl$worldToLocal;
	((SuiDesigner$SceneCtrl*)self)->clientToWorld = (void*)SuiDesigner$SceneCtrl$clientToWorld;
	((SuiDesigner$SceneCtrl*)self)->clientToLocal = (void*)SuiDesigner$SceneCtrl$clientToLocal;
	((SuiDesigner$SceneCtrl*)self)->translate = (void*)SuiDesigner$SceneCtrl$translate;
	((SuiDesigner$SceneCtrl*)self)->setTranslate = (void*)SuiDesigner$SceneCtrl$setTranslate;
	((SuiDesigner$SceneCtrl*)self)->identity = (void*)SuiDesigner$SceneCtrl$identity;
	((SuiDesigner$SceneCtrl*)self)->performScaleByWheelEventAndSceneView = (void*)SuiDesigner$SceneCtrl$performScaleByWheelEventAndSceneView;
}

// init function

void SuiDesigner$SceneCtrl_init(SuiDesigner$SceneCtrl *self, void *pOwner){
    Vtable_SuiDesigner$SceneCtrl_init(&_vtable_SuiDesigner$SceneCtrl);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$SceneCtrl;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$SceneCtrl_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$SceneCtrl * SuiDesigner$SceneCtrl_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$SceneCtrl *self = calloc(1, sizeof(SuiDesigner$SceneCtrl));
	
    SuiDesigner$SceneCtrl_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$SceneCtrl$ctor(SuiDesigner$SceneCtrl *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_871_15*  __var___Block_871_15 = (__var___Block_871_15=NULL,urgc_init_var((void**)&__var___Block_871_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_871_15) , __finiBlock___Block_871_15) ));
	urgc_set_field_class(__var___Block_871_15, (void * )offsetof(SuiDesigner$__Block_871_15, self) , self) ;
	urgc_set_field_class(self->sceneViewCb, (void * )offsetof(SuiDesigner$SceneViewCb, ctrl) , self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_873_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_873_27(&tmpReturn_1, __var___Block_871_15) ) ;
}


bool  SuiDesigner$SceneCtrl$onEvent(SuiDesigner$SceneCtrl *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$WheelEvent_init(NULL))) {
		SuiCore$WheelEvent *  we = (SuiCore$WheelEvent * )e;
		if (((SuiCore$ViewEvent * )we)->isCapture) {
			SuiCore$Node *  parent = ((SuiCore$Node * )self->contentView)->parent;
			if (Orc_instanceof((Object*)parent, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
				self->performScaleByWheelEventAndSceneView(self, we, parent) ;
				return true; 
			}
		}
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && ((SuiCore$ViewEvent * )me)->isBubble(me)  && me->isMouseDown) {
			self->drag->onMouseDown(self->drag, me) ;
			return true; 
		}
	}
	return false; 
}


void  SuiDesigner$SceneCtrl$setScale(SuiDesigner$SceneCtrl *  self, float  s){
	self->_scale = s;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneCtrl$updateMat(SuiDesigner$SceneCtrl *  self){
	SuiCore$Mat2d$identity(&self->mat) ;
	SuiCore$Mat2d$translate(&self->mat, self->_translate.x, self->_translate.y, self->_translate.z) ;
	SuiCore$Mat2d$scale(&self->mat, self->_scale, self->_scale, self->_scale) ;
}


SuiCore$Vec2 SuiDesigner$SceneCtrl$localToWorld(SuiDesigner$SceneCtrl *  self, float  x, float  y){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	SuiCore$Vec3 p = SuiCore$Mat2d$transformPoint(&self->mat, x, y, 0.f) ;
	ret.x = p.x;
	ret.y = p.y;
	return ret; 
}


SuiCore$Vec2 SuiDesigner$SceneCtrl$worldToLocal(SuiDesigner$SceneCtrl *  self, float  x, float  y){
	SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0) ;
	SuiCore$Mat2d inv = self->mat;
	SuiCore$Mat2d$inverse(&inv) ;
	SuiCore$Vec3 p = SuiCore$Mat2d$transformPoint(&inv, x, y, 0.f) ;
	ret.x = p.x;
	ret.y = p.y;
	return ret; 
}


SuiCore$Vec2 SuiDesigner$SceneCtrl$clientToWorld(SuiDesigner$SceneCtrl *  self, float  x, float  y){
	if (!self->contentView) {
		return SuiCore$mkVec2(0, 0) ; 
	}
	SuiCore$ViewBase *  viewportView = ((SuiCore$Node * )self->contentView)->parent;
	SuiCore$Vec2 viewPos = viewportView->worldToLocal(viewportView, x, y) ;
	return viewPos; 
}


SuiCore$Vec2 SuiDesigner$SceneCtrl$clientToLocal(SuiDesigner$SceneCtrl *  self, float  x, float  y){
	if (!self->contentView) {
		return SuiCore$mkVec2(0, 0) ; 
	}
	SuiCore$Vec2 worldPos = self->clientToWorld(self, x, y) ;
	SuiCore$Vec2 localPos = self->worldToLocal(self, worldPos.x, worldPos.y) ;
	return localPos; 
}


void  SuiDesigner$SceneCtrl$translate(SuiDesigner$SceneCtrl *  self, float  x, float  y, float  z){
	self->_translate = SuiCore$Vec3$add3f(&self->_translate, x, y, z) ;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneCtrl$setTranslate(SuiDesigner$SceneCtrl *  self, float  x, float  y, float  z){
	SuiCore$Vec3$set(&self->_translate, x, y, z) ;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneCtrl$identity(SuiDesigner$SceneCtrl *  self){
	SuiCore$Vec3$set(&self->_translate, 0, 0, 0) ;
	self->_scale = 1;
	self->updateMat(self) ;
}


void  SuiDesigner$SceneCtrl$performScaleByWheelEventAndSceneView(SuiDesigner$SceneCtrl *  self, SuiCore$WheelEvent *  we, SuiCore$ViewBase *  v){
	SuiCore$Vec2 viewPos = v->worldToLocal(v, ((SuiCore$MouseEvent * )we)->clientX, ((SuiCore$MouseEvent * )we)->clientY) ;
	SuiCore$Mat2d invMat = SuiCore$Mat2d$inverseNew(&self->mat) ;
	SuiCore$Vec3 scenePos = SuiCore$Mat2d$transformPoint(&invMat, viewPos.x, viewPos.y, 0) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$DrawDegreeItem*  opt = self->degree->findAndReturnOffset((opt = NULL,&opt), self->degree, self->_scale, we->deltaY > 0 ? 1 : -1) ;
	urgc_set_field_class(self->degree, (void * )offsetof(SuiDesigner$DrawDegree, curOption) , opt) ;
	self->degree->curScale = opt->value;
	self->setScale(self, opt->value) ;
	SuiCore$Vec3 newViewPos = SuiCore$Mat2d$transformPoint(&self->mat, scenePos.x, scenePos.y, 0) ;
	printf("scale. client:%d,%d, viewPos:%f,%f, scenePos:%f,%f,newViewPos:%f,%f, delta:%f,%f\n", ((SuiCore$MouseEvent * )we)->clientX, ((SuiCore$MouseEvent * )we)->clientY, viewPos.x, viewPos.y, scenePos.x, scenePos.y, newViewPos.x, newViewPos.y, viewPos.x - newViewPos.x, viewPos.y - newViewPos.y) ;
	self->translate(self, viewPos.x - newViewPos.x, viewPos.y - newViewPos.y, 0) ;
	if (self->contentView) {
		((SuiCore$ViewBase * )self->contentView)->transform = self->mat;
	}
	printf("wheel. result:%f opt:%f,degree:%f\n", self->_scale, opt->value, opt->degree) ;
}



static URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  dockLayoutIns = NULL;

//vtable instance
Vtable_SuiDesigner$TileEditor _vtable_SuiDesigner$TileEditor;

// init meta

void SuiDesigner$TileEditor_initMeta(Vtable_SuiDesigner$TileEditor *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiDesigner$TileEditor, win), true, false, 1);
	orc_metaField_class(&pNext, "imgCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(SuiDesigner$TileEditor, imgCell), true, false, 1);
	orc_metaField_class(&pNext, "previewCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(SuiDesigner$TileEditor, previewCell), true, false, 1);
	orc_metaField_class(&pNext, "invalidReact", ((Vtable_Object*)Vtable_SuiDesigner$InvalidReact_init(0)), offsetof(SuiDesigner$TileEditor, invalidReact), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$TileEditor, path), true, false, 1);
	orc_metaField_class(&pNext, "map", ((Vtable_Object*)Vtable_SuiDesigner$TileMap_init(0)), offsetof(SuiDesigner$TileEditor, map), true, false, 1);
	orc_metaField_class(&pNext, "curLayer", ((Vtable_Object*)Vtable_SuiDesigner$Layer_init(0)), offsetof(SuiDesigner$TileEditor, curLayer), true, false, 1);
	orc_metaField_class(&pNext, "curTileset", ((Vtable_Object*)Vtable_SuiDesigner$Tileset_init(0)), offsetof(SuiDesigner$TileEditor, curTileset), true, false, 1);
	orc_metaField_class(&pNext, "editingAutoTile", ((Vtable_Object*)Vtable_SuiDesigner$AutoTile_init(0)), offsetof(SuiDesigner$TileEditor, editingAutoTile), true, false, 1);
	orc_metaField_class(&pNext, "tilesetStatus", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$TileEditor, tilesetStatus), true, false, 1);
	orc_metaField_class(&pNext, "tilesetSceneCtrl", ((Vtable_Object*)Vtable_SuiDesigner$SceneCtrl_init(0)), offsetof(SuiDesigner$TileEditor, tilesetSceneCtrl), true, false, 1);
	orc_metaField_class(&pNext, "sceneCtrl", ((Vtable_Object*)Vtable_SuiDesigner$SceneCtrl_init(0)), offsetof(SuiDesigner$TileEditor, sceneCtrl), true, false, 1);
	orc_metaField_class(&pNext, "tileMapEditView", ((Vtable_Object*)Vtable_SuiDesigner$TileMapEditView_init(0)), offsetof(SuiDesigner$TileEditor, tileMapEditView), true, false, 1);
	orc_metaField_class(&pNext, "curTilePosArr", ((Vtable_Object*)Vtable_Sgl$Vec2Array_init(0)), offsetof(SuiDesigner$TileEditor, curTilePosArr), true, false, 1);
	orc_metaField_class(&pNext, "tilesetDrag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$TileEditor, tilesetDrag), true, false, 1);
	orc_metaField_class(&pNext, "chessBg", ((Vtable_Object*)Vtable_SuiDesigner$ChessBgViewCallback_init(0)), offsetof(SuiDesigner$TileEditor, chessBg), true, false, 1);

	orc_metaField_method(&pNext, "editAutoTile", offsetof(SuiDesigner$TileEditor, editAutoTile));
	orc_metaField_method(&pNext, "printSceneTree", offsetof(SuiDesigner$TileEditor, printSceneTree));
	orc_metaField_method(&pNext, "getFrameIndex", offsetof(SuiDesigner$TileEditor, getFrameIndex));
	orc_metaField_method(&pNext, "ui_addtileset", offsetof(SuiDesigner$TileEditor, ui_addtileset));
	orc_metaField_method(&pNext, "addTileLayer", offsetof(SuiDesigner$TileEditor, addTileLayer));
	orc_metaField_method(&pNext, "delLayer", offsetof(SuiDesigner$TileEditor, delLayer));
	orc_metaField_method(&pNext, "reactPreview", offsetof(SuiDesigner$TileEditor, reactPreview));
	orc_metaField_method(&pNext, "showDialog_renameLayer", offsetof(SuiDesigner$TileEditor, showDialog_renameLayer));
	orc_metaField_method(&pNext, "reactTilesetsNames", offsetof(SuiDesigner$TileEditor, reactTilesetsNames));
	orc_metaField_method(&pNext, "reactLayers", offsetof(SuiDesigner$TileEditor, reactLayers));
	orc_metaField_method(&pNext, "reactScene", offsetof(SuiDesigner$TileEditor, reactScene));
	orc_metaField_method(&pNext, "reactTilesetView", offsetof(SuiDesigner$TileEditor, reactTilesetView));
	orc_metaField_method(&pNext, "ui_createAnimTile", offsetof(SuiDesigner$TileEditor, ui_createAnimTile));
	orc_metaField_method(&pNext, "ui_createRandomTile", offsetof(SuiDesigner$TileEditor, ui_createRandomTile));
	orc_metaField_method(&pNext, "ui_createAutoTile", offsetof(SuiDesigner$TileEditor, ui_createAutoTile));
	orc_metaField_method(&pNext, "react", offsetof(SuiDesigner$TileEditor, react));
	orc_metaField_method(&pNext, "showWindow_mapSetting", offsetof(SuiDesigner$TileEditor, showWindow_mapSetting));
	orc_metaField_method(&pNext, "showWindow", offsetof(SuiDesigner$TileEditor, showWindow));
}


// vtable init


Vtable_SuiDesigner$TileEditor* Vtable_SuiDesigner$TileEditor_init(Vtable_SuiDesigner$TileEditor* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$TileEditor;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$TileEditor_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$TileEditor";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$TileEditor_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$TileEditor_fini(SuiDesigner$TileEditor *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->win);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->imgCell);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->previewCell);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->invalidReact);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->path);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->map);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->curLayer);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->curTileset);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->editingAutoTile);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tilesetStatus);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tilesetSceneCtrl);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->sceneCtrl);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tileMapEditView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->curTilePosArr);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tilesetDrag);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->chessBg);

}

// init fields function


void SuiDesigner$TileEditor_init_fields(SuiDesigner$TileEditor *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$TileEditor_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->win, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->imgCell, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->previewCell, NULL);
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InvalidReact*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->invalidReact, SuiDesigner$mkInvalidReact(&tmpReturn_1, self) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->path, Orc$str(&tmpReturn_2, "../build/././a.tilemap.json") );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$TileMap*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->map, SuiDesigner$TileMap_new(&tmpNewOwner_3) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->curLayer, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->curTileset, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->editingAutoTile, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tilesetStatus, Orc$str(&tmpReturn_4, "tile") );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SceneCtrl*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tilesetSceneCtrl, SuiDesigner$SceneCtrl_new(&tmpNewOwner_5) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SceneCtrl*  tmpNewOwner_6 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->sceneCtrl, SuiDesigner$SceneCtrl_new(&tmpNewOwner_6) );
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tileMapEditView, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Vec2Array*  tmpNewOwner_7 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->curTilePosArr, Sgl$Vec2Array_new(&tmpNewOwner_7) );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_8 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->tilesetDrag, SuiView$Drag_new(&tmpNewOwner_8) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ChessBgViewCallback*  tmpNewOwner_9 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$TileEditor*)self)->chessBg, SuiDesigner$ChessBgViewCallback_new(&tmpNewOwner_9) );
    }
	((SuiDesigner$TileEditor*)self)->editAutoTile = (void*)SuiDesigner$TileEditor$editAutoTile;
	((SuiDesigner$TileEditor*)self)->printSceneTree = (void*)SuiDesigner$TileEditor$printSceneTree;
	((SuiDesigner$TileEditor*)self)->getFrameIndex = (void*)SuiDesigner$TileEditor$getFrameIndex;
	((Object*)self)->ctor = (void*)SuiDesigner$TileEditor$ctor;
	((SuiDesigner$TileEditor*)self)->ui_addtileset = (void*)SuiDesigner$TileEditor$ui_addtileset;
	((SuiDesigner$TileEditor*)self)->addTileLayer = (void*)SuiDesigner$TileEditor$addTileLayer;
	((SuiDesigner$TileEditor*)self)->delLayer = (void*)SuiDesigner$TileEditor$delLayer;
	((SuiDesigner$TileEditor*)self)->reactPreview = (void*)SuiDesigner$TileEditor$reactPreview;
	((SuiDesigner$TileEditor*)self)->showDialog_renameLayer = (void*)SuiDesigner$TileEditor$showDialog_renameLayer;
	((SuiDesigner$TileEditor*)self)->reactTilesetsNames = (void*)SuiDesigner$TileEditor$reactTilesetsNames;
	((SuiDesigner$TileEditor*)self)->reactLayers = (void*)SuiDesigner$TileEditor$reactLayers;
	((SuiDesigner$TileEditor*)self)->reactScene = (void*)SuiDesigner$TileEditor$reactScene;
	((SuiDesigner$TileEditor*)self)->reactTilesetView = (void*)SuiDesigner$TileEditor$reactTilesetView;
	((SuiDesigner$TileEditor*)self)->ui_createAnimTile = (void*)SuiDesigner$TileEditor$ui_createAnimTile;
	((SuiDesigner$TileEditor*)self)->ui_createRandomTile = (void*)SuiDesigner$TileEditor$ui_createRandomTile;
	((SuiDesigner$TileEditor*)self)->ui_createAutoTile = (void*)SuiDesigner$TileEditor$ui_createAutoTile;
	((SuiDesigner$TileEditor*)self)->react = (void*)SuiDesigner$TileEditor$react;
	((SuiDesigner$TileEditor*)self)->showWindow_mapSetting = (void*)SuiDesigner$TileEditor$showWindow_mapSetting;
	((SuiDesigner$TileEditor*)self)->showWindow = (void*)SuiDesigner$TileEditor$showWindow;
}

// init function

void SuiDesigner$TileEditor_init(SuiDesigner$TileEditor *self, void *pOwner){
    Vtable_SuiDesigner$TileEditor_init(&_vtable_SuiDesigner$TileEditor);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$TileEditor;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$TileEditor_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$TileEditor * SuiDesigner$TileEditor_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$TileEditor *self = calloc(1, sizeof(SuiDesigner$TileEditor));
	
    SuiDesigner$TileEditor_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$TileEditor$editAutoTile(SuiDesigner$TileEditor *  self, SuiDesigner$AutoTile *  at){
	if (at) {
		Orc$String$set(self->tilesetStatus, "editingAutoTile") ;
	}
	else {
		Orc$String$set(self->tilesetStatus, "tile") ;
	}
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$TileEditor, editingAutoTile) , at) ;
	self->invalidReact->invalid(self->invalidReact) ;
}


void  SuiDesigner$TileEditor$printSceneTree(SuiDesigner$TileEditor *  self){
	
}


int  SuiDesigner$TileEditor$getFrameIndex(SuiDesigner$TileEditor *  self, int  x, int  y){
	return -1; 
}


void  SuiDesigner$TileEditor$ctor(SuiDesigner$TileEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_1089_15*  __var___Block_1089_15 = (__var___Block_1089_15=NULL,urgc_init_var((void**)&__var___Block_1089_15, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1089_15) , __finiBlock___Block_1089_15) ));
	urgc_set_field_class(__var___Block_1089_15, (void * )offsetof(SuiDesigner$__Block_1089_15, self) , self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1091_34*  tmpReturn_1 = NULL;
	urgc_set_field(self->tilesetDrag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_1091_34(&tmpReturn_1, __var___Block_1089_15) ) ;
}


void  SuiDesigner$TileEditor$ui_addtileset(SuiDesigner$TileEditor *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  abspath = Orc$Path_toAbsolute((abspath = NULL,&abspath), self->path->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("cwd:%s\n", Orc$Path_getcwd(&tmpReturn_1) ->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  paths = SuiDialog$FileDialog_getOpenFileName((paths = NULL,&paths), "./", "选择图片") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	printf("after cwd:%s\n", Orc$Path_getcwd(&tmpReturn_2) ->str) ;
	for (int  i = 0; i < paths->size(paths) ; i++) {
		Orc$String *  s = (Orc$String * )paths->get(paths, i) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  relpath = Orc$Path_relPathToFile((relpath = NULL,&relpath), s->str, abspath->str) ;
		printf("选择了图片:%s, rel:%s\n", s->str, relpath->str) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$Tileset*  ts = (ts=NULL,urgc_init_var_class((void**)&ts, SuiDesigner$Tileset_new(&ts) ));
		Orc$String$set(ts->imgPath, relpath->str) ;
		ts->startGid = self->map->findFreeStartGid(self->map) ;
		self->map->tilesets->add(self->map->tilesets, ts) ;
	}
	self->invalidReact->invalid(self->invalidReact) ;
}


void  SuiDesigner$TileEditor$addTileLayer(SuiDesigner$TileEditor *  self){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$TileLayer*  layer = (layer=NULL,urgc_init_var_class((void**)&layer, SuiDesigner$TileLayer_new(&layer) ));
	Sgl$IntArray$initSize(layer->data, self->map->width * self->map->height) ;
	Orc$String$set(((SuiDesigner$Layer * )layer)->name, "图层") ;
	Orc$String$addi(((SuiDesigner$Layer * )layer)->name, self->map->layers->size(self->map->layers) ) ;
	self->map->layers->add(self->map->layers, layer) ;
	self->invalidReact->invalid(self->invalidReact) ;
}


void  SuiDesigner$TileEditor$delLayer(SuiDesigner$TileEditor *  self, SuiDesigner$Layer *  layer){
	self->map->layers->remove(self->map->layers, layer) ;
	self->invalidReact->invalid(self->invalidReact) ;
}


SuiCore$ViewBase *  SuiDesigner$TileEditor$reactPreview(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_1172_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_1172_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1172_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->chessBg) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_1178_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1178_26(&tmpReturn_2) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) ;
		return o; 
	}
}


void  SuiDesigner$TileEditor$showDialog_renameLayer(SuiDesigner$TileEditor *  self, SuiDesigner$Layer*  layer){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(layer);

	URGC_VAR_CLEANUP SuiDesigner$__Block_1190_45*  __var___Block_1190_45 = (__var___Block_1190_45=NULL,urgc_init_var((void**)&__var___Block_1190_45, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1190_45) , __finiBlock___Block_1190_45) ));
	urgc_set_field_class(__var___Block_1190_45, (void * )offsetof(SuiDesigner$__Block_1190_45, self) , self) ;
	urgc_set_field_class(__var___Block_1190_45, (void * )offsetof(SuiDesigner$__Block_1190_45, layer) , layer) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1192_52*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt(__var___Block_1190_45->layer->name->str, "重命名", __make___Closure_1192_52(&tmpReturn_1, __var___Block_1190_45) ) ;
}


SuiCore$ViewBase *  SuiDesigner$TileEditor$reactTilesetsNames(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_1197_57*  __var___Block_1197_57 = (__var___Block_1197_57=NULL,urgc_init_var((void**)&__var___Block_1197_57, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1197_57) , __finiBlock___Block_1197_57) ));
	urgc_set_field_class(__var___Block_1197_57, (void * )offsetof(SuiDesigner$__Block_1197_57, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_1 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_1198_8 = SuiView$mkScrollArea(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_1198_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1198_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = 0x33ff00ff;
		o->useMinWidthConstraint = true;
		Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "stretch") ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_1207_12 = SuiLayout$layoutLinear(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_1207_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1207_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "maxOrStretch") ;
			for (int  i = 0; i < self->map->tilesets->size(self->map->tilesets) ; i++) {
				URGC_VAR_CLEANUP SuiDesigner$__Block_1212_64*  __var___Block_1212_64 = (__var___Block_1212_64=NULL,urgc_init_var((void**)&__var___Block_1212_64, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1212_64) , __finiBlock___Block_1212_64) ));
				__var___Block_1212_64->tileset = (SuiDesigner$Tileset * )self->map->tilesets->get(self->map->tilesets, i) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
				{
					SuiView$TextView*  __scopeVar_1214_20 = SuiView$mkTextView(&tmpReturn_4, o, (long long )__var___Block_1212_64->tileset) , *o = __scopeVar_1214_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1214_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->setText(o, __var___Block_1212_64->tileset->imgPath) ;
					Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
					URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_5 = NULL;
					{
						SuiView$HoverViewEffect*  __scopeVar_1219_24 = SuiView$mkHoverViewEffect(&tmpReturn_5, o, 0) , *o = __scopeVar_1219_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1219_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->hoverBorder->setAll(o->hoverBorder, 1, 0x00000000) ;
						o->activeBorder->setAll(o->activeBorder, 1, 0x00000000) ;
						o->backgroundColor = i % 2 == 0 ? 0x00ffff00 : 0x33ffffff;
						o->hoverBackgroundColor = 0x33ff0000;
						o->activeBackgroundColor = 0x66ff0000;
						o->isActive = self->curTileset == __var___Block_1212_64->tileset;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_1227_44*  tmpReturn_6 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onHostEvent) , __make___Closure_1227_44(&tmpReturn_6) ) ;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_1251_40*  tmpReturn_7 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onClick) , __make___Closure_1251_40(&tmpReturn_7, __var___Block_1197_57, __var___Block_1212_64) ) ;
					}
				}
			}
		}
		return o; 
	}
}


SuiCore$ViewBase *  SuiDesigner$TileEditor$reactLayers(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_1265_50*  __var___Block_1265_50 = (__var___Block_1265_50=NULL,urgc_init_var((void**)&__var___Block_1265_50, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1265_50) , __finiBlock___Block_1265_50) ));
	urgc_set_field_class(__var___Block_1265_50, (void * )offsetof(SuiDesigner$__Block_1265_50, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_1 = NULL;
	{
		SuiView$ScrollArea*  __scopeVar_1266_8 = SuiView$mkScrollArea(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_1266_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1266_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = 0x33ff00ff;
		o->useMinWidthConstraint = true;
		Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "stretch") ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_1275_12 = SuiLayout$layoutLinear(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_1275_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1275_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "maxOrStretch") ;
			((SuiCore$View * )o)->backgroundColor = 0x33ff00ff;
			for (int  i = 0; i < self->map->layers->size(self->map->layers) ; i++) {
				URGC_VAR_CLEANUP SuiDesigner$__Block_1280_62*  __var___Block_1280_62 = (__var___Block_1280_62=NULL,urgc_init_var((void**)&__var___Block_1280_62, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1280_62) , __finiBlock___Block_1280_62) ));
				__var___Block_1280_62->layer = (SuiDesigner$Layer * )self->map->layers->get(self->map->layers, i) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
				{
					SuiView$TextView*  __scopeVar_1282_20 = SuiView$mkTextView(&tmpReturn_4, o, (long long )__var___Block_1280_62->layer) , *o = __scopeVar_1282_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1282_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->setText(o, __var___Block_1280_62->layer->name) ;
					Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
					URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_5 = NULL;
					{
						SuiView$HoverViewEffect*  __scopeVar_1287_24 = SuiView$mkHoverViewEffect(&tmpReturn_5, o, 0) , *o = __scopeVar_1287_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1287_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->hoverBorder->setAll(o->hoverBorder, 1, 0x00000000) ;
						o->activeBorder->setAll(o->activeBorder, 1, 0x00000000) ;
						o->backgroundColor = i % 2 == 0 ? 0x00ffff00 : 0x33ffffff;
						o->hoverBackgroundColor = 0x33ff0000;
						o->activeBackgroundColor = 0x66ff0000;
						o->isActive = self->curLayer == __var___Block_1280_62->layer;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_1295_44*  tmpReturn_6 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onHostEvent) , __make___Closure_1295_44(&tmpReturn_6, __var___Block_1265_50, __var___Block_1280_62) ) ;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_1320_40*  tmpReturn_7 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onClick) , __make___Closure_1320_40(&tmpReturn_7, __var___Block_1265_50, __var___Block_1280_62) ) ;
					}
				}
			}
		}
		return o; 
	}
}


SuiCore$ViewBase *  SuiDesigner$TileEditor$reactScene(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_1333_49*  __var___Block_1333_49 = (__var___Block_1333_49=NULL,urgc_init_var((void**)&__var___Block_1333_49, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1333_49) , __finiBlock___Block_1333_49) ));
	urgc_set_field_class(__var___Block_1333_49, (void * )offsetof(SuiDesigner$__Block_1333_49, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_1334_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_1334_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1334_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->sceneCtrl->sceneViewCb) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_1340_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1340_26(&tmpReturn_2, __var___Block_1333_49) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_4 = NULL;
		{
			SuiLayout$LayoutAlign*  __scopeVar_1357_12 = SuiLayout$layoutAlign(&tmpReturn_4, o, 0) , *o = __scopeVar_1357_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1357_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->useMaxConstraint = false;
			urgc_set_field_class(self->sceneCtrl, (void * )offsetof(SuiDesigner$SceneCtrl, contentView) , o) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner$TileMapEditView*  tmpReturn_5 = NULL;
			{
				SuiDesigner$TileMapEditView*  __scopeVar_1361_16 = SuiDesigner$mkTileMapEditView(&tmpReturn_5, o, 0) , *o = __scopeVar_1361_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1361_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_field_class(o, (void * )offsetof(SuiDesigner$TileMapEditView, map) , self->map) ;
				urgc_set_field_class(o, (void * )offsetof(SuiDesigner$TileMapEditView, tileEditor) , self) ;
				urgc_set_field_class(o, (void * )offsetof(SuiDesigner$TileMapEditView, sceneCtrl) , self->sceneCtrl) ;
				urgc_set_field_class(o, (void * )offsetof(SuiDesigner$TileMapEditView, viewportView) , (SuiCore$ViewBase * )((SuiCore$Node * )self->sceneCtrl->contentView)->parent) ;
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner$TileEditor, tileMapEditView) , o) ;
			}
		}
		return o; 
	}
}


SuiCore$ViewBase *  SuiDesigner$TileEditor$reactTilesetView(SuiDesigner$TileEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP SuiDesigner$__Block_1394_53*  __var___Block_1394_53 = (__var___Block_1394_53=NULL,urgc_init_var((void**)&__var___Block_1394_53, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1394_53) , __finiBlock___Block_1394_53) ));
	urgc_set_field_class(__var___Block_1394_53, (void * )offsetof(SuiDesigner$__Block_1394_53, self) , self) ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_1395_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_1395_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1395_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) ;
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->tilesetSceneCtrl->sceneViewCb) ;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_1401_26*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1401_26(&tmpReturn_3, __var___Block_1394_53) ) ;
		if (self->curTileset) {
			SuiDesigner$Tileset *  ts = self->curTileset;
			printf("react TilesetView:%s\n", ts->imgPath->str) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_4 = NULL;
			{
				SuiLayout$LayoutAlign*  __scopeVar_1418_16 = SuiLayout$layoutAlign(&tmpReturn_4, o, 0) , *o = __scopeVar_1418_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1418_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->useMaxConstraint = false;
				urgc_set_field_class(self->tilesetSceneCtrl, (void * )offsetof(SuiDesigner$SceneCtrl, contentView) , o) ;
				URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_5 = NULL;
				{
					SuiView$ImageView*  __scopeVar_1422_20 = SuiView$mkImageView(&tmpReturn_5, o, 0) , *o = __scopeVar_1422_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1422_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->setSrc(o, ts->imgPath) ;
					URGC_VAR_CLEANUP SuiDesigner$__Closure_1426_38*  tmpReturn_6 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1426_38(&tmpReturn_6, __var___Block_1394_53) ) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_7 = NULL;
					{
						SuiLayout$LayoutAlignPositionCell*  __scopeVar_1436_24 = SuiLayout$layoutAlignPositionCell(&tmpReturn_7, o, 0) , *o = __scopeVar_1436_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1436_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						
					}
					int  w = o->_img->width(o->_img) ;
					int  h = o->_img->height(o->_img) ;
					((SuiCore$View * )o)->width = w;
					((SuiCore$View * )o)->height = h;
					ts->calcRowsCols(ts, o->_img->size(o->_img) , self->map->tileWidth, self->map->tileHeight) ;
					int  colw = self->map->tileWidth;
					int  rowh = self->map->tileHeight;
					for (int  i = 0; 1 && i <= ts->rows; i++) {
						URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_8 = NULL;
						{
							SuiCore$View*  __scopeVar_1458_28 = SuiView$mkView(&tmpReturn_8, o, 1000 + i) , *o = __scopeVar_1458_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1458_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$String$addi(Orc$str(&tmpReturn_9, "rowLine:") , i) ) ;
							((SuiCore$ViewBase * )o)->frame.y = i * self->map->tileHeight;
							o->backgroundColor = 0xffff0000;
							o->height = 1;
							o->width = w;
						}
					}
					for (int  i = 0; 1 && i <= ts->cols; i++) {
						URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_10 = NULL;
						{
							SuiCore$View*  __scopeVar_1468_28 = SuiView$mkView(&tmpReturn_10, o, 2000 + i) , *o = __scopeVar_1468_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1468_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
							urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$String$addi(Orc$str(&tmpReturn_11, "colLine:") , i) ) ;
							((SuiCore$ViewBase * )o)->frame.x = i * self->map->tileWidth;
							o->backgroundColor = 0xffff0000;
							o->width = 1;
							o->height = h;
						}
					}
					if (Orc$String$equals(self->tilesetStatus, "tile") ) {
						for (int  y = 0; y < ts->rows; y++) {
							for (int  x = 0; x < ts->cols; x++) {
								URGC_VAR_CLEANUP SuiDesigner$__Block_1481_63*  __var___Block_1481_63 = (__var___Block_1481_63=NULL,urgc_init_var((void**)&__var___Block_1481_63, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1481_63) , __finiBlock___Block_1481_63) ));
								__var___Block_1481_63->tilePos = SuiCore$mkVec2(x, y) ;
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
								URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, Orc$String$addi(Orc$String$add(Orc$String$addi(Orc$str(&tmpReturn_12, "cell:") , x) , ",") , y) ));
								URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_13 = NULL;
								{
									SuiCore$View*  __scopeVar_1484_36 = SuiView$mkView(&tmpReturn_13, o, 30000 + y * 100 + x) , *o = __scopeVar_1484_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1484_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , key) ;
									((SuiCore$ViewBase * )o)->frame.x = x * colw;
									((SuiCore$ViewBase * )o)->frame.y = y * rowh;
									o->width = colw;
									o->height = rowh;
									((SuiCore$ViewBase * )o)->frame.width = colw;
									((SuiCore$ViewBase * )o)->frame.height = rowh;
									URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_14 = NULL;
									{
										SuiView$HoverViewEffect*  __scopeVar_1497_40 = SuiView$mkHoverViewEffect(&tmpReturn_14, o, 0) , *o = __scopeVar_1497_40;
										UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1497_40 = ((SuiCore$Node*)o)->__exit__((void*)o);
									
										o->hoverBorder->setAll(o->hoverBorder, 1, 0x00000000) ;
										o->activeBorder->setAll(o->activeBorder, 1, 0x00000000) ;
										o->backgroundColor = 0x00ff0000;
										o->hoverBackgroundColor = 0x33ff0000;
										o->activeBackgroundColor = 0x66ff0000;
										o->isActive = self->curTilePosArr->has(self->curTilePosArr, __var___Block_1481_63->tilePos) ;
										URGC_VAR_CLEANUP SuiDesigner$__Closure_1505_56*  tmpReturn_15 = NULL;
										urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onClick) , __make___Closure_1505_56(&tmpReturn_15, __var___Block_1394_53, __var___Block_1481_63) ) ;
									}
								}
							}
						}
					}
					if (Orc$String$equals(self->tilesetStatus, "editingAutoTile") ) {
						float  cw = colw / 3.0;
						float  ch = rowh / 3.0;
						float  neighborRows = ts->rows * 3;
						float  neighborCols = ts->cols * 3;
						for (int  y = 0; y < neighborRows; y++) {
							for (int  x = 0; x < neighborCols; x++) {
								URGC_VAR_CLEANUP SuiDesigner$__Block_1552_68*  __var___Block_1552_68 = (__var___Block_1552_68=NULL,urgc_init_var((void**)&__var___Block_1552_68, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1552_68) , __finiBlock___Block_1552_68) ));
								SuiCore$Vec2 tilePos = SuiCore$mkVec2(x, y) ;
								__var___Block_1552_68->neighborId = y * neighborCols + x;
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
								URGC_VAR_CLEANUP_CLASS Orc$String*  key = (key=NULL,urgc_init_var_class((void**)&key, Orc$String$addi(Orc$String$add(Orc$String$addi(Orc$str(&tmpReturn_16, "cell:") , x) , ",") , y) ));
								URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_17 = NULL;
								{
									SuiCore$View*  __scopeVar_1557_36 = SuiView$mkView(&tmpReturn_17, o, 30000 + y * 100 + x) , *o = __scopeVar_1557_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1557_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , key) ;
									((SuiCore$ViewBase * )o)->frame.x = x * cw;
									((SuiCore$ViewBase * )o)->frame.y = y * ch;
									o->width = cw;
									o->height = ch;
									((SuiCore$ViewBase * )o)->frame.width = cw;
									((SuiCore$ViewBase * )o)->frame.height = ch;
									URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_18 = NULL;
									{
										SuiView$HoverViewEffect*  __scopeVar_1570_40 = SuiView$mkHoverViewEffect(&tmpReturn_18, o, 0) , *o = __scopeVar_1570_40;
										UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1570_40 = ((SuiCore$Node*)o)->__exit__((void*)o);
									
										o->hoverBorder->setAll(o->hoverBorder, 1, 0x00000000) ;
										o->activeBorder->setAll(o->activeBorder, 1, 0x00000000) ;
										o->backgroundColor = 0x00ff0000;
										o->hoverBackgroundColor = 0x33ff0000;
										o->activeBackgroundColor = 0x66ff0000;
										o->isActive = Sgl$IntArray$has(self->editingAutoTile->neighborIdArr, __var___Block_1552_68->neighborId) ;
										URGC_VAR_CLEANUP SuiDesigner$__Closure_1578_56*  tmpReturn_19 = NULL;
										urgc_set_field(o, (void * )offsetof(SuiView$HoverViewEffect, onClick) , __make___Closure_1578_56(&tmpReturn_19, __var___Block_1394_53, __var___Block_1552_68) ) ;
									}
								}
							}
						}
					}
					{
						for (int  i = 0; i < self->curTileset->specialTiles->size(self->curTileset->specialTiles) ; i++) {
							URGC_VAR_CLEANUP SuiDesigner$__Block_1602_87*  __var___Block_1602_87 = (__var___Block_1602_87=NULL,urgc_init_var((void**)&__var___Block_1602_87, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1602_87) , __finiBlock___Block_1602_87) ));
							urgc_set_field_class(__var___Block_1602_87, (void * )offsetof(SuiDesigner$__Block_1602_87, st) , (SuiDesigner$SpecialTile* )self->curTileset->specialTiles->get(self->curTileset->specialTiles, i) ) ;
							int  gid = __var___Block_1602_87->st->getGid(__var___Block_1602_87->st) ;
							if (gid == -1) {
								continue;
							}
							SuiCore$Vec2 pos = self->curTileset->dissolveGidToGridPos(self->curTileset, gid) ;
							int  x = (int )pos.x;
							int  y = (int )pos.y;
							if (Orc_instanceof((Object*)__var___Block_1602_87->st, (Vtable_Object*)Vtable_SuiDesigner$RandomTile_init(NULL))) {
								SuiDesigner$RandomTile *  rt = (SuiDesigner$RandomTile * )__var___Block_1602_87->st;
								URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_20 = NULL;
								{
									SuiCore$View*  __scopeVar_1613_36 = SuiView$mkView(&tmpReturn_20, o, 40000 + y * 100 + x) , *o = __scopeVar_1613_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1613_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									o->border->setAll(o->border, 1, 0xffffffff) ;
									((SuiCore$ViewBase * )o)->frame.x = x * colw + 3;
									((SuiCore$ViewBase * )o)->frame.y = y * rowh + 3;
									o->width = colw / 4;
									o->height = rowh / 4;
									o->backgroundColor = 0x88ffff00;
									URGC_VAR_CLEANUP SuiDesigner$__Closure_1622_54*  tmpReturn_21 = NULL;
									urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1622_54(&tmpReturn_21, __var___Block_1394_53, __var___Block_1602_87) ) ;
								}
								bool  isActive = self->curTilePosArr->has(self->curTilePosArr, pos) ;
								if (isActive) {
									for (int  j = 1; j < rt->gidArr->size; j++) {
										int  gid = Sgl$IntArray$get(rt->gidArr, j) ;
										SuiCore$Vec2 pos = self->curTileset->dissolveGidToGridPos(self->curTileset, gid) ;
										int  x = (int )pos.x;
										int  y = (int )pos.y;
										URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_22 = NULL;
										{
											SuiCore$View*  __scopeVar_1654_44 = SuiView$mkView(&tmpReturn_22, o, 50000 + y * 100 + x) , *o = __scopeVar_1654_44;
											UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1654_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
										
											((SuiCore$ViewBase * )o)->frame.x = x * colw + 3;
											((SuiCore$ViewBase * )o)->frame.y = y * rowh + 3;
											o->width = 4;
											o->height = 4;
											o->backgroundColor = 0x88ffff00;
										}
									}
								}
							}
							else if (Orc_instanceof((Object*)__var___Block_1602_87->st, (Vtable_Object*)Vtable_SuiDesigner$AnimTile_init(NULL))) {
								SuiDesigner$AnimTile *  rt = (SuiDesigner$AnimTile * )__var___Block_1602_87->st;
								URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_23 = NULL;
								{
									SuiCore$View*  __scopeVar_1670_36 = SuiView$mkView(&tmpReturn_23, o, 40000 + y * 100 + x) , *o = __scopeVar_1670_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1670_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									o->border->setAll(o->border, 1, 0xffffffff) ;
									((SuiCore$ViewBase * )o)->frame.x = x * colw + 3;
									((SuiCore$ViewBase * )o)->frame.y = y * rowh + 3;
									o->width = colw / 4;
									o->height = rowh / 4;
									o->backgroundColor = 0x88ff00ff;
									URGC_VAR_CLEANUP SuiDesigner$__Closure_1679_54*  tmpReturn_24 = NULL;
									urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1679_54(&tmpReturn_24, __var___Block_1394_53, __var___Block_1602_87) ) ;
								}
								bool  isActive = self->curTilePosArr->has(self->curTilePosArr, pos) ;
								if (isActive) {
									for (int  j = 1; j < rt->gidArr->size; j++) {
										int  gid = Sgl$IntArray$get(rt->gidArr, j) ;
										SuiCore$Vec2 pos = self->curTileset->dissolveGidToGridPos(self->curTileset, gid) ;
										int  x = (int )pos.x;
										int  y = (int )pos.y;
										URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_25 = NULL;
										{
											SuiCore$View*  __scopeVar_1711_44 = SuiView$mkView(&tmpReturn_25, o, 50000 + y * 100 + x) , *o = __scopeVar_1711_44;
											UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1711_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
										
											((SuiCore$ViewBase * )o)->frame.x = x * colw + 3;
											((SuiCore$ViewBase * )o)->frame.y = y * rowh + 3;
											o->width = 4;
											o->height = 4;
											o->backgroundColor = 0x88ff00ff;
										}
									}
								}
							}
							else if (Orc_instanceof((Object*)__var___Block_1602_87->st, (Vtable_Object*)Vtable_SuiDesigner$AutoTile_init(NULL))) {
								URGC_VAR_CLEANUP SuiDesigner$__Block_1725_63*  __var___Block_1725_63 = (__var___Block_1725_63=NULL,urgc_init_var((void**)&__var___Block_1725_63, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1725_63) , __finiBlock___Block_1725_63) ));
								urgc_set_field_class(__var___Block_1725_63, (void * )offsetof(SuiDesigner$__Block_1725_63, rt) , (SuiDesigner$AutoTile* )__var___Block_1602_87->st) ;
								URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_26 = NULL;
								{
									SuiCore$View*  __scopeVar_1727_36 = SuiView$mkView(&tmpReturn_26, o, 40000 + y * 100 + x) , *o = __scopeVar_1727_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1727_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									o->border->setAll(o->border, 1, 0xffffffff) ;
									((SuiCore$ViewBase * )o)->frame.x = x * colw + 3;
									((SuiCore$ViewBase * )o)->frame.y = y * rowh + 3;
									o->width = colw / 4;
									o->height = rowh / 4;
									o->backgroundColor = 0x8800ffff;
									URGC_VAR_CLEANUP SuiDesigner$__Closure_1736_54*  tmpReturn_27 = NULL;
									urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1736_54(&tmpReturn_27, __var___Block_1394_53, __var___Block_1602_87, __var___Block_1725_63) ) ;
								}
								bool  isActive = self->curTilePosArr->has(self->curTilePosArr, pos) ;
								if (isActive && Orc$String$equals(self->tilesetStatus, "tile") ) {
									float  cw = colw / 3.0;
									float  ch = rowh / 3.0;
									float  neighborRows = ts->rows * 3;
									float  neighborCols = ts->cols * 3;
									for (int  j = 0; j < __var___Block_1725_63->rt->neighborIdArr->size; j++) {
										int  neighborId = Sgl$IntArray$get(__var___Block_1725_63->rt->neighborIdArr, j) ;
										SuiCore$Vec2 pos = dissolveNeighborIdoGridPos(self->curTileset, neighborId) ;
										int  x = (int )pos.x;
										int  y = (int )pos.y;
										URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_28 = NULL;
										{
											SuiCore$View*  __scopeVar_1785_44 = SuiView$mkView(&tmpReturn_28, o, 50000 + y * 100 + x) , *o = __scopeVar_1785_44;
											UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1785_44 = ((SuiCore$Node*)o)->__exit__((void*)o);
										
											((SuiCore$ViewBase * )o)->frame.x = x * cw;
											((SuiCore$ViewBase * )o)->frame.y = y * ch;
											o->width = cw;
											o->height = ch;
											o->backgroundColor = 0x88ff00ff;
											Orc$String$set(((SuiCore$ViewBase * )o)->hitTestType, "none") ;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return o; 
	}
}


void  SuiDesigner$TileEditor$ui_createAnimTile(SuiDesigner$TileEditor *  self){
	if (self->curTileset == NULL || ((Sgl$StructArrayBase * )self->curTilePosArr)->size == 0) {
		SuiDialog$Toast_make("未选中tile") ;
		return ; 
	}
	if (((Sgl$StructArrayBase * )self->curTilePosArr)->size < 2) {
		SuiDialog$Toast_make("需要选中多个tile") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$AnimTile*  rt = (rt=NULL,urgc_init_var_class((void**)&rt, SuiDesigner$AnimTile_new(&rt) ));
	for (int  i = 0; i < ((Sgl$StructArrayBase * )self->curTilePosArr)->size; i++) {
		SuiCore$Vec2 pos = self->curTilePosArr->get(self->curTilePosArr, i) ;
		int  gid = self->curTileset->calcGid(self->curTileset, pos) ;
		Sgl$IntArray$append(rt->gidArr, gid) ;
	}
	self->curTileset->specialTiles->add(self->curTileset->specialTiles, rt) ;
	self->invalidReact->invalid(self->invalidReact) ;
	SuiDialog$Toast_make("已创建AnimTile") ;
}


void  SuiDesigner$TileEditor$ui_createRandomTile(SuiDesigner$TileEditor *  self){
	if (self->curTileset == NULL || ((Sgl$StructArrayBase * )self->curTilePosArr)->size == 0) {
		SuiDialog$Toast_make("未选中tile") ;
		return ; 
	}
	if (((Sgl$StructArrayBase * )self->curTilePosArr)->size < 2) {
		SuiDialog$Toast_make("需要选中多个tile") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$RandomTile*  rt = (rt=NULL,urgc_init_var_class((void**)&rt, SuiDesigner$RandomTile_new(&rt) ));
	for (int  i = 0; i < ((Sgl$StructArrayBase * )self->curTilePosArr)->size; i++) {
		SuiCore$Vec2 pos = self->curTilePosArr->get(self->curTilePosArr, i) ;
		int  gid = self->curTileset->calcGid(self->curTileset, pos) ;
		Sgl$IntArray$append(rt->gidArr, gid) ;
	}
	self->curTileset->specialTiles->add(self->curTileset->specialTiles, rt) ;
	self->invalidReact->invalid(self->invalidReact) ;
	SuiDialog$Toast_make("已创建RandomTile") ;
}


void  SuiDesigner$TileEditor$ui_createAutoTile(SuiDesigner$TileEditor *  self){
	if (self->curTileset == NULL || ((Sgl$StructArrayBase * )self->curTilePosArr)->size == 0) {
		SuiDialog$Toast_make("未选中tile") ;
		return ; 
	}
	if (((Sgl$StructArrayBase * )self->curTilePosArr)->size != 1) {
		SuiDialog$Toast_make("需要选中1个tile") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$AutoTile*  rt = (rt=NULL,urgc_init_var_class((void**)&rt, SuiDesigner$AutoTile_new(&rt) ));
	SuiCore$Vec2 pos = self->curTilePosArr->get(self->curTilePosArr, 0) ;
	int  gid = self->curTileset->calcGid(self->curTileset, pos) ;
	rt->gid = gid;
	self->curTileset->specialTiles->add(self->curTileset->specialTiles, rt) ;
	self->invalidReact->invalid(self->invalidReact) ;
	SuiDialog$Toast_make("已创建AutoTile") ;
}


void  SuiDesigner$TileEditor$react(SuiDesigner$TileEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_1870_16*  __var___Block_1870_16 = (__var___Block_1870_16=NULL,urgc_init_var((void**)&__var___Block_1870_16, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_1870_16) , __finiBlock___Block_1870_16) ));
	urgc_set_field_class(__var___Block_1870_16, (void * )offsetof(SuiDesigner$__Block_1870_16, self) , self) ;
	printf("react SpriteSheetEditor\n") ;
	__var___Block_1870_16->t = SuiDesigner$themeIns() ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1873_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_1, self->win->rootView, 0) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1874_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_2 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1875_16 = SuiView$mkDrawButton(&tmpReturn_2, o, 0) , *o = __scopeVar_1875_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1875_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_3, "设置") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1877_32*  tmpReturn_4 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1877_32(&tmpReturn_4, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_5 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1882_16 = SuiView$mkDrawButton(&tmpReturn_5, o, 0) , *o = __scopeVar_1882_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1882_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_6, "添加tilelayer") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1884_32*  tmpReturn_7 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1884_32(&tmpReturn_7, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_8 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1888_16 = SuiView$mkDrawButton(&tmpReturn_8, o, 0) , *o = __scopeVar_1888_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1888_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_9, "添加tileset") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1890_32*  tmpReturn_10 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1890_32(&tmpReturn_10, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_11 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1894_16 = SuiView$mkDrawButton(&tmpReturn_11, o, 0) , *o = __scopeVar_1894_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1894_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_12, "创建随机tile") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1897_32*  tmpReturn_13 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1897_32(&tmpReturn_13, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_14 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1902_16 = SuiView$mkDrawButton(&tmpReturn_14, o, 0) , *o = __scopeVar_1902_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1902_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_15, "创建动画tile") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1905_32*  tmpReturn_16 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1905_32(&tmpReturn_16, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_17 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1910_16 = SuiView$mkDrawButton(&tmpReturn_17, o, 0) , *o = __scopeVar_1910_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1910_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_18, "创建AutoTile") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1913_32*  tmpReturn_19 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1913_32(&tmpReturn_19, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_20 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1918_16 = SuiView$mkDrawButton(&tmpReturn_20, o, 0) , *o = __scopeVar_1918_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1918_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_21 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_21, "打印树") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1920_32*  tmpReturn_22 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1920_32(&tmpReturn_22, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_23 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1924_16 = SuiView$mkDrawButton(&tmpReturn_23, o, 0) , *o = __scopeVar_1924_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1924_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_24, "保存") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1926_32*  tmpReturn_25 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1926_32(&tmpReturn_25, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_26 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1937_16 = SuiView$mkDrawButton(&tmpReturn_26, o, 0) , *o = __scopeVar_1937_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1937_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_27 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_27, "加载") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1939_32*  tmpReturn_28 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1939_32(&tmpReturn_28, __var___Block_1870_16) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_29 = NULL;
			{
				SuiView$DrawButton*  __scopeVar_1952_16 = SuiView$mkDrawButton(&tmpReturn_29, o, 0) , *o = __scopeVar_1952_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1952_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
				urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_30, "lala") ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1954_32*  tmpReturn_31 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_1954_32(&tmpReturn_31) ) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpReturn_32 = NULL;
		{
			SuiView$DockLayout*  __scopeVar_1959_12 = SuiView$dockLayout(&tmpReturn_32, o, 0) , *o = __scopeVar_1959_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1959_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_var_class(&dockLayoutIns, o) ;
			((SuiCore$View * )o)->width = 100;
			((SuiCore$View * )o)->height = 20;
			((SuiCore$View * )o)->backgroundColor = 0x30000033;
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1966_45*  tmpReturn_33 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemHeadView) , __make___Closure_1966_45(&tmpReturn_33, __var___Block_1870_16) ) ;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_1999_48*  tmpReturn_34 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemContentView) , __make___Closure_1999_48(&tmpReturn_34, __var___Block_1870_16) ) ;
				{
					SuiView$DockItem*  __scopeVar_2068_20 = o->root, *o = __scopeVar_2068_20;
					
				
					o->isHorizontal = false;
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_35 = NULL;
					{
						SuiView$DockItem*  __scopeVar_2071_24 = SuiView$mkDockItemSplitter(&tmpReturn_35, o, NULL, true) , *o = __scopeVar_2071_24;
						
					
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_36 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_37 = NULL;
						{
							SuiView$DockItem*  __scopeVar_2072_28 = SuiView$mkDockItem(&tmpReturn_36, o, Orc$str(&tmpReturn_37, "layers") ) , *o = __scopeVar_2072_28;
							
						
							o->intId = 0;
							o->width = 150;
						}
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_38 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_39 = NULL;
						{
							SuiView$DockItem*  __scopeVar_2076_28 = SuiView$mkDockItem(&tmpReturn_38, o, Orc$str(&tmpReturn_39, "scene") ) , *o = __scopeVar_2076_28;
							
						
							o->intId = 0;
						}
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_40 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_41 = NULL;
						{
							SuiView$DockItem*  __scopeVar_2079_28 = SuiView$mkDockItem(&tmpReturn_40, o, Orc$str(&tmpReturn_41, "inspector") ) , *o = __scopeVar_2079_28;
							
						
							o->intId = 0;
						}
					}
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_42 = NULL;
					{
						SuiView$DockItem*  __scopeVar_2083_24 = SuiView$mkDockItemSplitter(&tmpReturn_42, o, NULL, true) , *o = __scopeVar_2083_24;
						
					
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_43 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_44 = NULL;
						{
							SuiView$DockItem*  __scopeVar_2084_28 = SuiView$mkDockItem(&tmpReturn_43, o, Orc$str(&tmpReturn_44, "tilesets-list") ) , *o = __scopeVar_2084_28;
							
						
							o->intId = 0;
							o->width = 160;
						}
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_45 = NULL;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_46 = NULL;
						{
							SuiView$DockItem*  __scopeVar_2088_28 = SuiView$mkDockItem(&tmpReturn_45, o, Orc$str(&tmpReturn_46, "tileset-preview") ) , *o = __scopeVar_2088_28;
							
						
							o->intId = 0;
						}
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_47 = NULL;
			SuiLayout$layoutLinearCell(&tmpReturn_47, o, 0) ;
			{
				
			}
		}
	}
}


void  SuiDesigner$TileEditor$showWindow_mapSetting(SuiDesigner$TileEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_2113_32*  __var___Block_2113_32 = (__var___Block_2113_32=NULL,urgc_init_var((void**)&__var___Block_2113_32, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_2113_32) , __finiBlock___Block_2113_32) ));
	urgc_set_field_class(__var___Block_2113_32, (void * )offsetof(SuiDesigner$__Block_2113_32, self) , self) ;
	urgc_set_field_class(__var___Block_2113_32, (void * )offsetof(SuiDesigner$__Block_2113_32, win) , NULL) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_2116_35*  tmpReturn_1 = NULL;
	urgc_set_field(__var___Block_2113_32, (void * )offsetof(SuiDesigner$__Block_2113_32, reactMapSetting) , __make___Closure_2116_35(&tmpReturn_1, __var___Block_2113_32) ) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_2 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_2) ;
		
	
		urgc_set_field_class(__var___Block_2113_32, (void * )offsetof(SuiDesigner$__Block_2113_32, win) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_3 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_3) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2170_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			__var___Block_2113_32->win->setRootView(__var___Block_2113_32->win, o) ;
		}
		(*(__var___Block_2113_32->reactMapSetting))((void * )(__var___Block_2113_32->reactMapSetting)) ;
		o->setTitle(o, "地图设置") ;
		o->setSize(o, 300, 400) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  SuiDesigner$TileEditor$showWindow(SuiDesigner$TileEditor *  self){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$TileEditor, win) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2189_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			self->win->setRootView(self->win, o) ;
		}
		self->react(self) ;
		o->setTitle(o, "瓦片地图编辑器") ;
		o->setSize(o, 800, 600) ;
		o->show(o) ;
	}
}



static void  __finiBlock___Block_561_15(SuiDesigner$__Block_561_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_561_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_871_15(SuiDesigner$__Block_871_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_871_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1089_15(SuiDesigner$__Block_1089_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1089_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1190_45(SuiDesigner$__Block_1190_45 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1190_45, layer) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1190_45, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1197_57(SuiDesigner$__Block_1197_57 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1197_57, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1212_64(SuiDesigner$__Block_1212_64 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1265_50(SuiDesigner$__Block_1265_50 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1265_50, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1280_62(SuiDesigner$__Block_1280_62 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1333_49(SuiDesigner$__Block_1333_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1333_49, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1394_53(SuiDesigner$__Block_1394_53 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1394_53, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1481_63(SuiDesigner$__Block_1481_63 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1552_68(SuiDesigner$__Block_1552_68 *  self){
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1602_87(SuiDesigner$__Block_1602_87 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1602_87, st) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1725_63(SuiDesigner$__Block_1725_63 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1725_63, rt) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1870_16(SuiDesigner$__Block_1870_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_1870_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_2113_32(SuiDesigner$__Block_2113_32 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_2113_32, win) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_2113_32, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_562_27(SuiDesigner$__Closure_562_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("dragging\n") ;
		SuiCore$Vec2 gridPos = self->__var___Block_561_15->self->calcMouseGridPos(self->__var___Block_561_15->self) ;
		self->__var___Block_561_15->self->setTileAtGrid(self->__var___Block_561_15->self, gridPos) ;
	}
}

static void  __fini___Closure_562_27(SuiDesigner$__Closure_562_27 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_562_27, __var___Block_561_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_562_27*  __make___Closure_562_27(SuiDesigner$__Closure_562_27 **  __outRef__, SuiDesigner$__Block_561_15 *  __var___Block_561_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_562_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_562_27) , __fini___Closure_562_27) ));
	self->invoke = __fn___Closure_562_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_562_27, __var___Block_561_15) , __var___Block_561_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_873_27(SuiDesigner$__Closure_873_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		self->__var___Block_871_15->self->translate(self->__var___Block_871_15->self, d->deltaPos.x, d->deltaPos.y, 0) ;
		if (self->__var___Block_871_15->self->contentView) {
			((SuiCore$ViewBase * )self->__var___Block_871_15->self->contentView)->transform = self->__var___Block_871_15->self->mat;
		}
		printf("SceneCtrl.onDragging\n") ;
	}
}

static void  __fini___Closure_873_27(SuiDesigner$__Closure_873_27 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_873_27, __var___Block_871_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_873_27*  __make___Closure_873_27(SuiDesigner$__Closure_873_27 **  __outRef__, SuiDesigner$__Block_871_15 *  __var___Block_871_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_873_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_873_27) , __fini___Closure_873_27) ));
	self->invoke = __fn___Closure_873_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_873_27, __var___Block_871_15) , __var___Block_871_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1091_34(SuiDesigner$__Closure_1091_34 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("isDragging tileset\n") ;
		if (Orc$String$equals(self->__var___Block_1089_15->self->tilesetStatus, "editingAutoTile") ) {
			SuiCore$Vec2 localPos = self->__var___Block_1089_15->self->tilesetSceneCtrl->clientToLocal(self->__var___Block_1089_15->self->tilesetSceneCtrl, d->currentClientPos.x, d->currentClientPos.y) ;
			SuiDesigner$Tileset *  ts = self->__var___Block_1089_15->self->curTileset;
			float  cw = self->__var___Block_1089_15->self->map->tileWidth / 3.0;
			float  ch = self->__var___Block_1089_15->self->map->tileHeight / 3.0;
			int  x = localPos.x / cw;
			int  y = localPos.y / ch;
			int  neighborId = y * ts->cols * 3 + x;
			{
				Sgl$IntArray*  o = self->__var___Block_1089_15->self->editingAutoTile->neighborIdArr;
				
			
				if (!Sgl$IntArray$has(o, neighborId) ) {
					Sgl$IntArray$append(o, neighborId) ;
					printf("add neighborId:%d\n", neighborId) ;
					self->__var___Block_1089_15->self->invalidReact->invalid(self->__var___Block_1089_15->self->invalidReact) ;
				}
				else {
					printf("neighborId exist:%d\n", neighborId) ;
				}
			}
			printf("localPos:%f,%f. grid:%d,%d. neighborIdArr size:%d. nid:%d\n", localPos.x, localPos.y, x, y, self->__var___Block_1089_15->self->editingAutoTile->neighborIdArr->size, neighborId) ;
		}
	}
}

static void  __fini___Closure_1091_34(SuiDesigner$__Closure_1091_34 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1091_34, __var___Block_1089_15) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1091_34*  __make___Closure_1091_34(SuiDesigner$__Closure_1091_34 **  __outRef__, SuiDesigner$__Block_1089_15 *  __var___Block_1089_15){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1091_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1091_34) , __fini___Closure_1091_34) ));
	self->invoke = __fn___Closure_1091_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1091_34, __var___Block_1089_15) , __var___Block_1089_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1178_26(SuiDesigner$__Closure_1178_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	}
}

static void  __fini___Closure_1178_26(SuiDesigner$__Closure_1178_26 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1178_26*  __make___Closure_1178_26(SuiDesigner$__Closure_1178_26 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1178_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1178_26) , __fini___Closure_1178_26) ));
	self->invoke = __fn___Closure_1178_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1192_52(SuiDesigner$__Closure_1192_52 *  self, Orc$String*  newValue){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newValue);

	urgc_set_field_class(self->__var___Block_1190_45->layer, (void * )offsetof(SuiDesigner$Layer, name) , newValue) ;
	self->__var___Block_1190_45->self->invalidReact->invalid(self->__var___Block_1190_45->self->invalidReact) ;
}

static void  __fini___Closure_1192_52(SuiDesigner$__Closure_1192_52 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1192_52, __var___Block_1190_45) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1192_52*  __make___Closure_1192_52(SuiDesigner$__Closure_1192_52 **  __outRef__, SuiDesigner$__Block_1190_45 *  __var___Block_1190_45){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1192_52*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1192_52) , __fini___Closure_1192_52) ));
	self->invoke = __fn___Closure_1192_52;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1192_52, __var___Block_1190_45) , __var___Block_1190_45) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_1227_44(SuiDesigner$__Closure_1227_44 *  self, SuiCore$Event *  e){
	SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	if (me->button == 3 && me->isClickInBubble(me) ) {
		URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1230*  tmpReturn_1 = NULL;
		(urgc_set_var(&onActive, __make___Closure_onActive_1230(&tmpReturn_1) ) );
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		{
			SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
			
		
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_1238_40 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$str(&tmpReturn_5, "重命名") , onActive) , *o = __scopeVar_1238_40;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_1239_40 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "删除") , onActive) , *o = __scopeVar_1239_40;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
			n->create(n, o) ;
			n->showAtMouse(n) ;
		}
		return true; 
	}
	return false; 
}

static void  __fini___Closure_1227_44(SuiDesigner$__Closure_1227_44 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1227_44*  __make___Closure_1227_44(SuiDesigner$__Closure_1227_44 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1227_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1227_44) , __fini___Closure_1227_44) ));
	self->invoke = __fn___Closure_1227_44;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_1230(SuiDesigner$__Closure_onActive_1230 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->cmd, "重命名") ) {
		
	}
	if (Orc$String$equals(item->cmd, "删除") ) {
		
	}
}

static void  __fini___Closure_onActive_1230(SuiDesigner$__Closure_onActive_1230 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_1230*  __make___Closure_onActive_1230(SuiDesigner$__Closure_onActive_1230 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1230*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_1230) , __fini___Closure_onActive_1230) ));
	self->invoke = __fn___Closure_onActive_1230;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1251_40(SuiDesigner$__Closure_1251_40 *  self, SuiCore$MouseEvent *  me){
	urgc_set_field_class(self->__var___Block_1197_57->self, (void * )offsetof(SuiDesigner$TileEditor, curTileset) , self->__var___Block_1212_64->tileset) ;
	self->__var___Block_1197_57->self->invalidReact->invalid(self->__var___Block_1197_57->self->invalidReact) ;
}

static void  __fini___Closure_1251_40(SuiDesigner$__Closure_1251_40 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1251_40, __var___Block_1197_57) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1251_40, __var___Block_1212_64) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1251_40*  __make___Closure_1251_40(SuiDesigner$__Closure_1251_40 **  __outRef__, SuiDesigner$__Block_1197_57 *  __var___Block_1197_57, SuiDesigner$__Block_1212_64 *  __var___Block_1212_64){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1251_40*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1251_40) , __fini___Closure_1251_40) ));
	self->invoke = __fn___Closure_1251_40;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1251_40, __var___Block_1197_57) , __var___Block_1197_57) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1251_40, __var___Block_1212_64) , __var___Block_1212_64) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_1295_44(SuiDesigner$__Closure_1295_44 *  self, SuiCore$Event *  e){
	SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	if (me->button == 3 && me->isClickInBubble(me) ) {
		URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
		URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1298*  tmpReturn_1 = NULL;
		(urgc_set_var(&onActive, __make___Closure_onActive_1298(&tmpReturn_1, self->__var___Block_1265_50, self->__var___Block_1280_62) ) );
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		{
			SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
			
		
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_1307_40 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$str(&tmpReturn_5, "重命名") , onActive) , *o = __scopeVar_1307_40;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_1308_40 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "删除") , onActive) , *o = __scopeVar_1308_40;
				
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
			n->create(n, o) ;
			n->showAtMouse(n) ;
		}
		return true; 
	}
	return false; 
}

static void  __fini___Closure_1295_44(SuiDesigner$__Closure_1295_44 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1295_44, __var___Block_1265_50) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1295_44, __var___Block_1280_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1295_44*  __make___Closure_1295_44(SuiDesigner$__Closure_1295_44 **  __outRef__, SuiDesigner$__Block_1265_50 *  __var___Block_1265_50, SuiDesigner$__Block_1280_62 *  __var___Block_1280_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1295_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1295_44) , __fini___Closure_1295_44) ));
	self->invoke = __fn___Closure_1295_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1295_44, __var___Block_1265_50) , __var___Block_1265_50) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1295_44, __var___Block_1280_62) , __var___Block_1280_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_1298(SuiDesigner$__Closure_onActive_1298 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->cmd, "重命名") ) {
		self->__var___Block_1265_50->self->showDialog_renameLayer(self->__var___Block_1265_50->self, self->__var___Block_1280_62->layer) ;
	}
	if (Orc$String$equals(item->cmd, "删除") ) {
		self->__var___Block_1265_50->self->delLayer(self->__var___Block_1265_50->self, self->__var___Block_1280_62->layer) ;
	}
}

static void  __fini___Closure_onActive_1298(SuiDesigner$__Closure_onActive_1298 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1298, __var___Block_1265_50) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1298, __var___Block_1280_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_1298*  __make___Closure_onActive_1298(SuiDesigner$__Closure_onActive_1298 **  __outRef__, SuiDesigner$__Block_1265_50 *  __var___Block_1265_50, SuiDesigner$__Block_1280_62 *  __var___Block_1280_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1298*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_1298) , __fini___Closure_onActive_1298) ));
	self->invoke = __fn___Closure_onActive_1298;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1298, __var___Block_1265_50) , __var___Block_1265_50) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1298, __var___Block_1280_62) , __var___Block_1280_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1320_40(SuiDesigner$__Closure_1320_40 *  self, SuiCore$MouseEvent *  me){
	urgc_set_field_class(self->__var___Block_1265_50->self, (void * )offsetof(SuiDesigner$TileEditor, curLayer) , self->__var___Block_1280_62->layer) ;
	self->__var___Block_1265_50->self->invalidReact->invalid(self->__var___Block_1265_50->self->invalidReact) ;
}

static void  __fini___Closure_1320_40(SuiDesigner$__Closure_1320_40 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1320_40, __var___Block_1265_50) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1320_40, __var___Block_1280_62) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1320_40*  __make___Closure_1320_40(SuiDesigner$__Closure_1320_40 **  __outRef__, SuiDesigner$__Block_1265_50 *  __var___Block_1265_50, SuiDesigner$__Block_1280_62 *  __var___Block_1280_62){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1320_40*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1320_40) , __fini___Closure_1320_40) ));
	self->invoke = __fn___Closure_1320_40;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1320_40, __var___Block_1265_50) , __var___Block_1265_50) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1320_40, __var___Block_1280_62) , __var___Block_1280_62) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1340_26(SuiDesigner$__Closure_1340_26 *  self, SuiCore$Event *  e){
	if (self->__var___Block_1333_49->self->sceneCtrl->onEvent(self->__var___Block_1333_49->self->sceneCtrl, e) ) {
		return ; 
	}
	if (self->__var___Block_1333_49->self->tileMapEditView) {
		if (self->__var___Block_1333_49->self->tileMapEditView->onViewportEvent(self->__var___Block_1333_49->self->tileMapEditView, e) ) {
			return ; 
		}
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	}
}

static void  __fini___Closure_1340_26(SuiDesigner$__Closure_1340_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1340_26, __var___Block_1333_49) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1340_26*  __make___Closure_1340_26(SuiDesigner$__Closure_1340_26 **  __outRef__, SuiDesigner$__Block_1333_49 *  __var___Block_1333_49){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1340_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1340_26) , __fini___Closure_1340_26) ));
	self->invoke = __fn___Closure_1340_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1340_26, __var___Block_1333_49) , __var___Block_1333_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1401_26(SuiDesigner$__Closure_1401_26 *  self, SuiCore$Event *  e){
	if (self->__var___Block_1394_53->self->tilesetSceneCtrl->onEvent(self->__var___Block_1394_53->self->tilesetSceneCtrl, e) ) {
		return ; 
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && ((SuiCore$ViewEvent * )me)->isBubble(me)  && me->isMouseDown) {
			
		}
	}
}

static void  __fini___Closure_1401_26(SuiDesigner$__Closure_1401_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1401_26, __var___Block_1394_53) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1401_26*  __make___Closure_1401_26(SuiDesigner$__Closure_1401_26 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1401_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1401_26) , __fini___Closure_1401_26) ));
	self->invoke = __fn___Closure_1401_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1401_26, __var___Block_1394_53) , __var___Block_1394_53) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1426_38(SuiDesigner$__Closure_1426_38 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && ((SuiCore$ViewEvent * )me)->isCapture) {
			self->__var___Block_1394_53->self->tilesetDrag->onMouseDown(self->__var___Block_1394_53->self->tilesetDrag, me) ;
		}
	}
}

static void  __fini___Closure_1426_38(SuiDesigner$__Closure_1426_38 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1426_38, __var___Block_1394_53) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1426_38*  __make___Closure_1426_38(SuiDesigner$__Closure_1426_38 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1426_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1426_38) , __fini___Closure_1426_38) ));
	self->invoke = __fn___Closure_1426_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1426_38, __var___Block_1394_53) , __var___Block_1394_53) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1505_56(SuiDesigner$__Closure_1505_56 *  self, SuiCore$MouseEvent *  me){
	if (me->ctrl) {
		if (!self->__var___Block_1394_53->self->curTilePosArr->has(self->__var___Block_1394_53->self->curTilePosArr, self->__var___Block_1481_63->tilePos) ) {
			self->__var___Block_1394_53->self->curTilePosArr->add(self->__var___Block_1394_53->self->curTilePosArr, self->__var___Block_1481_63->tilePos) ;
		}
	}
	else if (me->shift) {
		if (((Sgl$StructArrayBase * )self->__var___Block_1394_53->self->curTilePosArr)->size == 0) {
			self->__var___Block_1394_53->self->curTilePosArr->add(self->__var___Block_1394_53->self->curTilePosArr, self->__var___Block_1481_63->tilePos) ;
		}
		else {
			SuiCore$Vec2 start = self->__var___Block_1394_53->self->curTilePosArr->data[0];
			((Sgl$StructArrayBase * )self->__var___Block_1394_53->self->curTilePosArr)->clear(self->__var___Block_1394_53->self->curTilePosArr) ;
			for (int  y = start.y; y <= self->__var___Block_1481_63->tilePos.y; y++) {
				for (int  x = start.x; x <= self->__var___Block_1481_63->tilePos.x; x++) {
					self->__var___Block_1394_53->self->curTilePosArr->add(self->__var___Block_1394_53->self->curTilePosArr, SuiCore$mkVec2(x, y) ) ;
				}
			}
		}
	}
	else {
		((Sgl$StructArrayBase * )self->__var___Block_1394_53->self->curTilePosArr)->clear(self->__var___Block_1394_53->self->curTilePosArr) ;
		self->__var___Block_1394_53->self->curTilePosArr->add(self->__var___Block_1394_53->self->curTilePosArr, self->__var___Block_1481_63->tilePos) ;
	}
	self->__var___Block_1394_53->self->invalidReact->invalid(self->__var___Block_1394_53->self->invalidReact) ;
}

static void  __fini___Closure_1505_56(SuiDesigner$__Closure_1505_56 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1505_56, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1505_56, __var___Block_1481_63) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1505_56*  __make___Closure_1505_56(SuiDesigner$__Closure_1505_56 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1481_63 *  __var___Block_1481_63){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1505_56*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1505_56) , __fini___Closure_1505_56) ));
	self->invoke = __fn___Closure_1505_56;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1505_56, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1505_56, __var___Block_1481_63) , __var___Block_1481_63) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1578_56(SuiDesigner$__Closure_1578_56 *  self, SuiCore$MouseEvent *  me){
	{
		Sgl$IntArray*  o = self->__var___Block_1394_53->self->editingAutoTile->neighborIdArr;
		
	
		printf("onclick neighbor cell. neighborId:%d\n", self->__var___Block_1552_68->neighborId) ;
		if (Sgl$IntArray$has(o, self->__var___Block_1552_68->neighborId) ) {
			printf(" remove neighbor cell. neighborId:%d\n", self->__var___Block_1552_68->neighborId) ;
			Sgl$IntArray$removeFirst(o, self->__var___Block_1552_68->neighborId) ;
		}
		else {
			printf(" append neighbor cell. neighborId:%d\n", self->__var___Block_1552_68->neighborId) ;
			Sgl$IntArray$append(o, self->__var___Block_1552_68->neighborId) ;
		}
	}
	self->__var___Block_1394_53->self->invalidReact->invalid(self->__var___Block_1394_53->self->invalidReact) ;
}

static void  __fini___Closure_1578_56(SuiDesigner$__Closure_1578_56 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1578_56, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1578_56, __var___Block_1552_68) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1578_56*  __make___Closure_1578_56(SuiDesigner$__Closure_1578_56 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1552_68 *  __var___Block_1552_68){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1578_56*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1578_56) , __fini___Closure_1578_56) ));
	self->invoke = __fn___Closure_1578_56;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1578_56, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1578_56, __var___Block_1552_68) , __var___Block_1552_68) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1622_54(SuiDesigner$__Closure_1622_54 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1626*  tmpReturn_1 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_1626(&tmpReturn_1, self->__var___Block_1394_53, self->__var___Block_1602_87) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_1636_56 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$str(&tmpReturn_5, "删除RandomTile") , onActive) , *o = __scopeVar_1636_56;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
				n->create(n, o) ;
				n->showAtMouse(n) ;
			}
		}
	}
}

static void  __fini___Closure_1622_54(SuiDesigner$__Closure_1622_54 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1622_54, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1622_54, __var___Block_1602_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1622_54*  __make___Closure_1622_54(SuiDesigner$__Closure_1622_54 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1622_54*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1622_54) , __fini___Closure_1622_54) ));
	self->invoke = __fn___Closure_1622_54;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1622_54, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1622_54, __var___Block_1602_87) , __var___Block_1602_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_1626(SuiDesigner$__Closure_onActive_1626 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->cmd, "删除RandomTile") ) {
		self->__var___Block_1394_53->self->curTileset->specialTiles->remove(self->__var___Block_1394_53->self->curTileset->specialTiles, self->__var___Block_1602_87->st) ;
		self->__var___Block_1394_53->self->invalidReact->invalid(self->__var___Block_1394_53->self->invalidReact) ;
		SuiDialog$Toast_make("已删除RandomTile") ;
		return ; 
	}
	SuiDialog$Toast_make(item->cmd->str) ;
}

static void  __fini___Closure_onActive_1626(SuiDesigner$__Closure_onActive_1626 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1626, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1626, __var___Block_1602_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_1626*  __make___Closure_onActive_1626(SuiDesigner$__Closure_onActive_1626 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1626*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_1626) , __fini___Closure_onActive_1626) ));
	self->invoke = __fn___Closure_onActive_1626;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1626, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1626, __var___Block_1602_87) , __var___Block_1602_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1679_54(SuiDesigner$__Closure_1679_54 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1683*  tmpReturn_1 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_1683(&tmpReturn_1, self->__var___Block_1394_53, self->__var___Block_1602_87) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_1693_56 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$str(&tmpReturn_5, "删除AnimTile") , onActive) , *o = __scopeVar_1693_56;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
				n->create(n, o) ;
				n->showAtMouse(n) ;
			}
		}
	}
}

static void  __fini___Closure_1679_54(SuiDesigner$__Closure_1679_54 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1679_54, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1679_54, __var___Block_1602_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1679_54*  __make___Closure_1679_54(SuiDesigner$__Closure_1679_54 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1679_54*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1679_54) , __fini___Closure_1679_54) ));
	self->invoke = __fn___Closure_1679_54;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1679_54, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1679_54, __var___Block_1602_87) , __var___Block_1602_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_1683(SuiDesigner$__Closure_onActive_1683 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->cmd, "删除AnimTile") ) {
		self->__var___Block_1394_53->self->curTileset->specialTiles->remove(self->__var___Block_1394_53->self->curTileset->specialTiles, self->__var___Block_1602_87->st) ;
		self->__var___Block_1394_53->self->invalidReact->invalid(self->__var___Block_1394_53->self->invalidReact) ;
		SuiDialog$Toast_make("已删除AnimTile") ;
		return ; 
	}
	SuiDialog$Toast_make(item->cmd->str) ;
}

static void  __fini___Closure_onActive_1683(SuiDesigner$__Closure_onActive_1683 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1683, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1683, __var___Block_1602_87) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_1683*  __make___Closure_onActive_1683(SuiDesigner$__Closure_onActive_1683 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1683*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_1683) , __fini___Closure_onActive_1683) ));
	self->invoke = __fn___Closure_onActive_1683;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1683, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1683, __var___Block_1602_87) , __var___Block_1602_87) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1736_54(SuiDesigner$__Closure_1736_54 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 3 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1740*  tmpReturn_1 = NULL;
			(urgc_set_var(&onActive, __make___Closure_onActive_1740(&tmpReturn_1, self->__var___Block_1394_53, self->__var___Block_1602_87, self->__var___Block_1725_63) ) );
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			{
				SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , onActive) ;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_1758_56 = SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$str(&tmpReturn_5, "删除AutoTile") , onActive) , *o = __scopeVar_1758_56;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_1759_56 = SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "编辑规则") , onActive) , *o = __scopeVar_1759_56;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_8 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
				{
					SuiView$MenuNativeItem*  __scopeVar_1760_56 = SuiView$mkMenuNativeItem(&tmpReturn_8, o, Orc$str(&tmpReturn_9, "退出编辑规则") , onActive) , *o = __scopeVar_1760_56;
					
				
					
				}
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiView$MenuNative_new(&n) ));
				n->create(n, o) ;
				n->showAtMouse(n) ;
			}
		}
	}
}

static void  __fini___Closure_1736_54(SuiDesigner$__Closure_1736_54 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1736_54, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1736_54, __var___Block_1602_87) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1736_54, __var___Block_1725_63) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1736_54*  __make___Closure_1736_54(SuiDesigner$__Closure_1736_54 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87, SuiDesigner$__Block_1725_63 *  __var___Block_1725_63){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1736_54*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1736_54) , __fini___Closure_1736_54) ));
	self->invoke = __fn___Closure_1736_54;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1736_54, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1736_54, __var___Block_1602_87) , __var___Block_1602_87) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1736_54, __var___Block_1725_63) , __var___Block_1725_63) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_1740(SuiDesigner$__Closure_onActive_1740 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->cmd, "删除AutoTile") ) {
		self->__var___Block_1394_53->self->curTileset->specialTiles->remove(self->__var___Block_1394_53->self->curTileset->specialTiles, self->__var___Block_1602_87->st) ;
		self->__var___Block_1394_53->self->invalidReact->invalid(self->__var___Block_1394_53->self->invalidReact) ;
		SuiDialog$Toast_make("已删除AutoTile") ;
		return ; 
	}
	if (Orc$String$equals(item->cmd, "编辑规则") ) {
		self->__var___Block_1394_53->self->editAutoTile(self->__var___Block_1394_53->self, self->__var___Block_1725_63->rt) ;
		return ; 
	}
	if (Orc$String$equals(item->cmd, "退出编辑规则") ) {
		self->__var___Block_1394_53->self->editAutoTile(self->__var___Block_1394_53->self, NULL) ;
		return ; 
	}
	SuiDialog$Toast_make(item->cmd->str) ;
}

static void  __fini___Closure_onActive_1740(SuiDesigner$__Closure_onActive_1740 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1740, __var___Block_1394_53) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1740, __var___Block_1602_87) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1740, __var___Block_1725_63) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_onActive_1740*  __make___Closure_onActive_1740(SuiDesigner$__Closure_onActive_1740 **  __outRef__, SuiDesigner$__Block_1394_53 *  __var___Block_1394_53, SuiDesigner$__Block_1602_87 *  __var___Block_1602_87, SuiDesigner$__Block_1725_63 *  __var___Block_1725_63){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_onActive_1740*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_onActive_1740) , __fini___Closure_onActive_1740) ));
	self->invoke = __fn___Closure_onActive_1740;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1740, __var___Block_1394_53) , __var___Block_1394_53) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1740, __var___Block_1602_87) , __var___Block_1602_87) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_onActive_1740, __var___Block_1725_63) , __var___Block_1725_63) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1877_32(SuiDesigner$__Closure_1877_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_1870_16->self->showWindow_mapSetting(self->__var___Block_1870_16->self) ;
}

static void  __fini___Closure_1877_32(SuiDesigner$__Closure_1877_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1877_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1877_32*  __make___Closure_1877_32(SuiDesigner$__Closure_1877_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1877_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1877_32) , __fini___Closure_1877_32) ));
	self->invoke = __fn___Closure_1877_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1877_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1884_32(SuiDesigner$__Closure_1884_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_1870_16->self->addTileLayer(self->__var___Block_1870_16->self) ;
}

static void  __fini___Closure_1884_32(SuiDesigner$__Closure_1884_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1884_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1884_32*  __make___Closure_1884_32(SuiDesigner$__Closure_1884_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1884_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1884_32) , __fini___Closure_1884_32) ));
	self->invoke = __fn___Closure_1884_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1884_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1890_32(SuiDesigner$__Closure_1890_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_1870_16->self->ui_addtileset(self->__var___Block_1870_16->self) ;
}

static void  __fini___Closure_1890_32(SuiDesigner$__Closure_1890_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1890_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1890_32*  __make___Closure_1890_32(SuiDesigner$__Closure_1890_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1890_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1890_32) , __fini___Closure_1890_32) ));
	self->invoke = __fn___Closure_1890_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1890_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1897_32(SuiDesigner$__Closure_1897_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_1870_16->self->ui_createRandomTile(self->__var___Block_1870_16->self) ;
}

static void  __fini___Closure_1897_32(SuiDesigner$__Closure_1897_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1897_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1897_32*  __make___Closure_1897_32(SuiDesigner$__Closure_1897_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1897_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1897_32) , __fini___Closure_1897_32) ));
	self->invoke = __fn___Closure_1897_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1897_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1905_32(SuiDesigner$__Closure_1905_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_1870_16->self->ui_createAnimTile(self->__var___Block_1870_16->self) ;
}

static void  __fini___Closure_1905_32(SuiDesigner$__Closure_1905_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1905_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1905_32*  __make___Closure_1905_32(SuiDesigner$__Closure_1905_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1905_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1905_32) , __fini___Closure_1905_32) ));
	self->invoke = __fn___Closure_1905_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1905_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1913_32(SuiDesigner$__Closure_1913_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_1870_16->self->ui_createAutoTile(self->__var___Block_1870_16->self) ;
}

static void  __fini___Closure_1913_32(SuiDesigner$__Closure_1913_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1913_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1913_32*  __make___Closure_1913_32(SuiDesigner$__Closure_1913_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1913_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1913_32) , __fini___Closure_1913_32) ));
	self->invoke = __fn___Closure_1913_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1913_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1920_32(SuiDesigner$__Closure_1920_32 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_1870_16->self->printSceneTree(self->__var___Block_1870_16->self) ;
}

static void  __fini___Closure_1920_32(SuiDesigner$__Closure_1920_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1920_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1920_32*  __make___Closure_1920_32(SuiDesigner$__Closure_1920_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1920_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1920_32) , __fini___Closure_1920_32) ));
	self->invoke = __fn___Closure_1920_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1920_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1926_32(SuiDesigner$__Closure_1926_32 *  self, SuiCore$MouseEvent *  me){
	long long  t0 = Orc$Time_unixMs() ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_toJson((jo = NULL,&jo), self->__var___Block_1870_16->self->map) ;
	long long  t1 = Orc$Time_unixMs() ;
	printf(" toJson ms:%lld\n", t1 - t0) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  json = jo->dump((json = NULL,&json), jo) ;
	Orc$Path_writeText(self->__var___Block_1870_16->self->path->str, json->str) ;
	SuiDialog$Toast_make("保存成功") ;
}

static void  __fini___Closure_1926_32(SuiDesigner$__Closure_1926_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1926_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1926_32*  __make___Closure_1926_32(SuiDesigner$__Closure_1926_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1926_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1926_32) , __fini___Closure_1926_32) ));
	self->invoke = __fn___Closure_1926_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1926_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1939_32(SuiDesigner$__Closure_1939_32 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parseByPathCstr((jo = NULL,&jo), self->__var___Block_1870_16->self->path->str) ;
	printf("加载json完成\n") ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$TileMap*  map = jo->toObjectByVtable((map = NULL,&map), jo, Vtable_SuiDesigner$TileMap_init(NULL)) ;
	urgc_set_field_class(self->__var___Block_1870_16->self, (void * )offsetof(SuiDesigner$TileEditor, map) , map) ;
	self->__var___Block_1870_16->self->invalidReact->invalid(self->__var___Block_1870_16->self->invalidReact) ;
}

static void  __fini___Closure_1939_32(SuiDesigner$__Closure_1939_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1939_32, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1939_32*  __make___Closure_1939_32(SuiDesigner$__Closure_1939_32 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1939_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1939_32) , __fini___Closure_1939_32) ));
	self->invoke = __fn___Closure_1939_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1939_32, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1954_32(SuiDesigner$__Closure_1954_32 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_1954_32(SuiDesigner$__Closure_1954_32 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1954_32*  __make___Closure_1954_32(SuiDesigner$__Closure_1954_32 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1954_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1954_32) , __fini___Closure_1954_32) ));
	self->invoke = __fn___Closure_1954_32;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1966_45(SuiDesigner$__Closure_1966_45 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex){
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpItem = (tmpItem=NULL,urgc_init_var_class((void**)&tmpItem, item));
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpDock = (tmpDock=NULL,urgc_init_var_class((void**)&tmpDock, dockLayoutIns));
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_1971_24 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_1971_24;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1971_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_2, "pointer") ) ;
		o->setText(o, item->id) ;
		o->color = self->__var___Block_1870_16->t->dock_head_c;
		((SuiCore$View * )o)->padding.top = 4;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->padding, 8) ;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 0.0f, 0xffaeaeb2) ;
		bool  active = item->parent->tabActiveIndex == kidIndex;
		if (active) {
			((SuiCore$View * )o)->border->t->w = 2.f;
			((SuiCore$View * )o)->border->t->color = self->__var___Block_1870_16->t->c_main;
		}
		if (kidIndex < item->parent->children->size(item->parent->children)  - 1) {
			((SuiCore$View * )o)->border->r->w = 1.f;
		}
		((SuiCore$View * )o)->backgroundColor = active ? self->__var___Block_1870_16->t->dock_head_bg_active : self->__var___Block_1870_16->t->dock_head_bg;
	}
}

static void  __fini___Closure_1966_45(SuiDesigner$__Closure_1966_45 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1966_45, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1966_45*  __make___Closure_1966_45(SuiDesigner$__Closure_1966_45 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1966_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1966_45) , __fini___Closure_1966_45) ));
	self->invoke = __fn___Closure_1966_45;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1966_45, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$ViewBase *  __fn___Closure_1999_48(SuiDesigner$__Closure_1999_48 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o){
	if (Orc$String$equals(item->id, "scene") ) {
		return self->__var___Block_1870_16->self->reactScene(self->__var___Block_1870_16->self, o, item) ; 
	}
	if (Orc$String$equals(item->id, "inspector") ) {
		return self->__var___Block_1870_16->self->reactPreview(self->__var___Block_1870_16->self, o, item) ; 
	}
	if (Orc$String$equals(item->id, "layers") ) {
		return self->__var___Block_1870_16->self->reactLayers(self->__var___Block_1870_16->self, o, item) ; 
	}
	if (Orc$String$equals(item->id, "tilesets-list") ) {
		return self->__var___Block_1870_16->self->reactTilesetsNames(self->__var___Block_1870_16->self, o, item) ; 
	}
	if (Orc$String$equals(item->id, "tileset-preview") ) {
		return self->__var___Block_1870_16->self->reactTilesetView(self->__var___Block_1870_16->self, o, item) ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_2044_24 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_2044_24;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2044_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
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
			SuiLayout$LayoutLinearCell*  __scopeVar_2060_28 = SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) , *o = __scopeVar_2060_28;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2060_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		return o; 
	}
}

static void  __fini___Closure_1999_48(SuiDesigner$__Closure_1999_48 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1999_48, __var___Block_1870_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_1999_48*  __make___Closure_1999_48(SuiDesigner$__Closure_1999_48 **  __outRef__, SuiDesigner$__Block_1870_16 *  __var___Block_1870_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_1999_48*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_1999_48) , __fini___Closure_1999_48) ));
	self->invoke = __fn___Closure_1999_48;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_1999_48, __var___Block_1870_16) , __var___Block_1870_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_2116_35(SuiDesigner$__Closure_2116_35 *  self){
	{
		SuiCore$ViewBase*  o = self->__var___Block_2113_32->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2117_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
		{
			SuiView$TextView*  __scopeVar_2118_16 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_2118_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2118_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			o->setText(o, Orc$str(&tmpReturn_2, "tileWidth:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_3 = NULL;
		{
			SuiView$EditText*  __scopeVar_2121_16 = SuiView$mkEditText(&tmpReturn_3, o, 0) , *o = __scopeVar_2121_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2121_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			o->setValue_notInFocus(o, Orc$String$addi(Orc$str(&tmpReturn_4, "") , self->__var___Block_2113_32->self->map->tileWidth) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_2123_39*  tmpReturn_5 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_2123_39(&tmpReturn_5, self->__var___Block_2113_32) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_6 = NULL;
		{
			SuiView$TextView*  __scopeVar_2130_16 = SuiView$mkTextView(&tmpReturn_6, o, 0) , *o = __scopeVar_2130_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2130_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			o->setText(o, Orc$str(&tmpReturn_7, "tileHeight:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_8 = NULL;
		{
			SuiView$EditText*  __scopeVar_2133_16 = SuiView$mkEditText(&tmpReturn_8, o, 0) , *o = __scopeVar_2133_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2133_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
			o->setValue_notInFocus(o, Orc$String$addi(Orc$str(&tmpReturn_9, "") , self->__var___Block_2113_32->self->map->tileHeight) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_2135_39*  tmpReturn_10 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_2135_39(&tmpReturn_10, self->__var___Block_2113_32) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_11 = NULL;
		{
			SuiView$TextView*  __scopeVar_2142_16 = SuiView$mkTextView(&tmpReturn_11, o, 0) , *o = __scopeVar_2142_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2142_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
			o->setText(o, Orc$str(&tmpReturn_12, "fps:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_13 = NULL;
		{
			SuiView$EditText*  __scopeVar_2145_16 = SuiView$mkEditText(&tmpReturn_13, o, 0) , *o = __scopeVar_2145_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2145_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
			o->setValue_notInFocus(o, Orc$String$addi(Orc$str(&tmpReturn_14, "") , self->__var___Block_2113_32->self->map->fps) ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_2147_39*  tmpReturn_15 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_2147_39(&tmpReturn_15, self->__var___Block_2113_32) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_16 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_2159_16 = SuiView$mkDrawButton(&tmpReturn_16, o, 0) , *o = __scopeVar_2159_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_2159_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_17, "提交") ) ;
			URGC_VAR_CLEANUP SuiDesigner$__Closure_2161_32*  tmpReturn_18 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_2161_32(&tmpReturn_18, self->__var___Block_2113_32) ) ;
		}
	}
}

static void  __fini___Closure_2116_35(SuiDesigner$__Closure_2116_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2116_35, __var___Block_2113_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_2116_35*  __make___Closure_2116_35(SuiDesigner$__Closure_2116_35 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_2116_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_2116_35) , __fini___Closure_2116_35) ));
	self->invoke = __fn___Closure_2116_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2116_35, __var___Block_2113_32) , __var___Block_2113_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_2123_39(SuiDesigner$__Closure_2123_39 *  self, SuiView$EditText *  et){
	int  rows = Orc$String$toInt(et->value) ;
	self->__var___Block_2113_32->self->map->tileWidth = rows;
	(*(self->__var___Block_2113_32->reactMapSetting))((void * )(self->__var___Block_2113_32->reactMapSetting)) ;
	self->__var___Block_2113_32->self->invalidReact->invalid(self->__var___Block_2113_32->self->invalidReact) ;
}

static void  __fini___Closure_2123_39(SuiDesigner$__Closure_2123_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2123_39, __var___Block_2113_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_2123_39*  __make___Closure_2123_39(SuiDesigner$__Closure_2123_39 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_2123_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_2123_39) , __fini___Closure_2123_39) ));
	self->invoke = __fn___Closure_2123_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2123_39, __var___Block_2113_32) , __var___Block_2113_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_2135_39(SuiDesigner$__Closure_2135_39 *  self, SuiView$EditText *  et){
	int  rows = Orc$String$toInt(et->value) ;
	self->__var___Block_2113_32->self->map->tileHeight = rows;
	(*(self->__var___Block_2113_32->reactMapSetting))((void * )(self->__var___Block_2113_32->reactMapSetting)) ;
	self->__var___Block_2113_32->self->invalidReact->invalid(self->__var___Block_2113_32->self->invalidReact) ;
}

static void  __fini___Closure_2135_39(SuiDesigner$__Closure_2135_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2135_39, __var___Block_2113_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_2135_39*  __make___Closure_2135_39(SuiDesigner$__Closure_2135_39 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_2135_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_2135_39) , __fini___Closure_2135_39) ));
	self->invoke = __fn___Closure_2135_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2135_39, __var___Block_2113_32) , __var___Block_2113_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_2147_39(SuiDesigner$__Closure_2147_39 *  self, SuiView$EditText *  et){
	int  v = Orc$String$toInt(et->value) ;
	self->__var___Block_2113_32->self->map->fps = v;
	(*(self->__var___Block_2113_32->reactMapSetting))((void * )(self->__var___Block_2113_32->reactMapSetting)) ;
	self->__var___Block_2113_32->self->invalidReact->invalid(self->__var___Block_2113_32->self->invalidReact) ;
}

static void  __fini___Closure_2147_39(SuiDesigner$__Closure_2147_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2147_39, __var___Block_2113_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_2147_39*  __make___Closure_2147_39(SuiDesigner$__Closure_2147_39 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_2147_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_2147_39) , __fini___Closure_2147_39) ));
	self->invoke = __fn___Closure_2147_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2147_39, __var___Block_2113_32) , __var___Block_2113_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_2161_32(SuiDesigner$__Closure_2161_32 *  self, SuiCore$MouseEvent *  me){
	(*(self->__var___Block_2113_32->reactMapSetting))((void * )(self->__var___Block_2113_32->reactMapSetting)) ;
}

static void  __fini___Closure_2161_32(SuiDesigner$__Closure_2161_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2161_32, __var___Block_2113_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_2161_32*  __make___Closure_2161_32(SuiDesigner$__Closure_2161_32 **  __outRef__, SuiDesigner$__Block_2113_32 *  __var___Block_2113_32){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_2161_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_2161_32) , __fini___Closure_2161_32) ));
	self->invoke = __fn___Closure_2161_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_2161_32, __var___Block_2113_32) , __var___Block_2113_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



