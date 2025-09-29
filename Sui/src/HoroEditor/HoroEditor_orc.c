
#include "HoroEditor_orc.h" 

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
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Mouse_orc.h"
#include "../Sui/Core/KeyEvent_orc.h"
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
#include "../SuiDesigner/ChessBgViewCallback_orc.h"
#include "../SuiDesigner/Theme_orc.h"
#include "../SuiDesigner/W3e_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"
#include "../SuiDesigner/MenuBarCtrl_orc.h"
#include "../SuiDesigner/ToolBase_orc.h"
#include "../SuiDesigner/SglGizmo_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/SkinMesh_orc.h"
#include "../Sgl/Particle_orc.h"
#include "../Sgl/GeometryHeightMap_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryPlane_orc.h"
#include "../Sgl/GeometryRect_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/GeometryCircle_orc.h"
#include "../Sgl/GeometryLine_orc.h"
#include "../Sgl/GeometryRing_orc.h"
#include "../Sgl/GeometryCylinder_orc.h"
#include "../Sgl/GeometryCone_orc.h"
#include "../Sgl/GeometryArrow_orc.h"
#include "../Sgl/Billboard_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Skybox_orc.h"
#include "../Sgl/OutlineFx_orc.h"
#include "../SuiDesigner/MdxReader_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/Project_orc.h"
#include "../SuiDesigner/SglInspectorView_orc.h"
#include "../SuiDesigner/SglInspView_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "./HoroSceneHierView_orc.h"
#include "./HoroEditCtx_orc.h"
#include "./UiAct_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_233_33 HoroEditor$__Block_233_33;

typedef struct tagHoroEditor$__Block_243_49 HoroEditor$__Block_243_49;

typedef struct tagHoroEditor$__Block_337_47 HoroEditor$__Block_337_47;

typedef struct tagHoroEditor$__Block_620_16 HoroEditor$__Block_620_16;

typedef struct tagHoroEditor$__Block_626_35 HoroEditor$__Block_626_35;

typedef struct tagHoroEditor$__Block_680_43 HoroEditor$__Block_680_43;

typedef struct tagHoroEditor$__Block_936_32 HoroEditor$__Block_936_32;

typedef struct tagHoroEditor$__Block_1072_21 HoroEditor$__Block_1072_21;

typedef struct tagHoroEditor$__Closure_187_27 HoroEditor$__Closure_187_27;

typedef struct tagHoroEditor$__Closure_221_26 HoroEditor$__Closure_221_26;

typedef struct tagHoroEditor$__Closure_235_42 HoroEditor$__Closure_235_42;

typedef struct tagHoroEditor$__Closure_269_26 HoroEditor$__Closure_269_26;

typedef struct tagHoroEditor$__Closure_324_38 HoroEditor$__Closure_324_38;

typedef struct tagHoroEditor$__Closure_329_48 HoroEditor$__Closure_329_48;

typedef struct tagHoroEditor$__Closure_514_44 HoroEditor$__Closure_514_44;

typedef struct tagHoroEditor$__Closure_634_51 HoroEditor$__Closure_634_51;

typedef struct tagHoroEditor$__Closure_onActive_635 HoroEditor$__Closure_onActive_635;

typedef struct tagHoroEditor$__Closure_684_44 HoroEditor$__Closure_684_44;

typedef struct tagHoroEditor$__Closure_688_39 HoroEditor$__Closure_688_39;

typedef struct tagHoroEditor$__Closure_698_36 HoroEditor$__Closure_698_36;

typedef struct tagHoroEditor$__Closure_705_36 HoroEditor$__Closure_705_36;

typedef struct tagHoroEditor$__Closure_711_36 HoroEditor$__Closure_711_36;

typedef struct tagHoroEditor$__Closure_718_36 HoroEditor$__Closure_718_36;

typedef struct tagHoroEditor$__Closure_726_36 HoroEditor$__Closure_726_36;

typedef struct tagHoroEditor$__Closure_734_36 HoroEditor$__Closure_734_36;

typedef struct tagHoroEditor$__Closure_741_36 HoroEditor$__Closure_741_36;

typedef struct tagHoroEditor$__Closure_747_36 HoroEditor$__Closure_747_36;

typedef struct tagHoroEditor$__Closure_760_36 HoroEditor$__Closure_760_36;

typedef struct tagHoroEditor$__Closure_775_36 HoroEditor$__Closure_775_36;

typedef struct tagHoroEditor$__Closure_802_49 HoroEditor$__Closure_802_49;

typedef struct tagHoroEditor$__Closure_832_52 HoroEditor$__Closure_832_52;

typedef struct tagHoroEditor$__Closure_940_35 HoroEditor$__Closure_940_35;

typedef struct tagHoroEditor$__Closure_985_32 HoroEditor$__Closure_985_32;

typedef struct tagHoroEditor$__Closure_1104_26 HoroEditor$__Closure_1104_26;



struct tagHoroEditor$__Block_233_33 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_243_49 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_337_47 {
	Sgl$Mesh*  m ;
};





struct tagHoroEditor$__Block_620_16 {
	HoroEditor$HoroEditor*  self ;
	SuiDesigner$Theme *  t ;
};





struct tagHoroEditor$__Block_626_35 {
	SuiDesigner$MenuBarCtrl*  group ;
};





struct tagHoroEditor$__Block_680_43 {
	SuiView$MenuButton*  mbutton ;
};





struct tagHoroEditor$__Block_936_32 {
	Sui$Window*  win ;
	void  (**reactMapSetting)(void *  self);
};





struct tagHoroEditor$__Block_1072_21 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Closure_187_27 {
	void  (*invoke)(HoroEditor$__Closure_187_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_221_26 {
	void  (*invoke)(HoroEditor$__Closure_221_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_235_42 {
	void  (*invoke)(HoroEditor$__Closure_235_42 *  self, Orc$String*  newValue);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_233_33*  __var___Block_233_33 ;
};





struct tagHoroEditor$__Closure_269_26 {
	void  (*invoke)(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_324_38 {
	void  (*invoke)(HoroEditor$__Closure_324_38 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_243_49*  __var___Block_243_49 ;
};





struct tagHoroEditor$__Closure_329_48 {
	void  (*invoke)(HoroEditor$__Closure_329_48 *  self);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_243_49*  __var___Block_243_49 ;
};





struct tagHoroEditor$__Closure_514_44 {
	void  (*invoke)(HoroEditor$__Closure_514_44 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_243_49*  __var___Block_243_49 ;
	HoroEditor$__Block_337_47*  __var___Block_337_47 ;
};





struct tagHoroEditor$__Closure_634_51 {
	SuiView$MenuNativeItem*  (*invoke)(HoroEditor$__Closure_634_51 *  self, SuiView$MenuButton *  mbutton);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_620_16*  __var___Block_620_16 ;
};





struct tagHoroEditor$__Closure_onActive_635 {
	void  (*invoke)(HoroEditor$__Closure_onActive_635 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_620_16*  __var___Block_620_16 ;
};





struct tagHoroEditor$__Closure_684_44 {
	void  (*invoke)(HoroEditor$__Closure_684_44 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_626_35*  __var___Block_626_35 ;
	HoroEditor$__Block_680_43*  __var___Block_680_43 ;
};





struct tagHoroEditor$__Closure_688_39 {
	void  (*invoke)(HoroEditor$__Closure_688_39 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_626_35*  __var___Block_626_35 ;
	HoroEditor$__Block_680_43*  __var___Block_680_43 ;
};





struct tagHoroEditor$__Closure_698_36 {
	void  (*invoke)(HoroEditor$__Closure_698_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_705_36 {
	void  (*invoke)(HoroEditor$__Closure_705_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_711_36 {
	void  (*invoke)(HoroEditor$__Closure_711_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_718_36 {
	void  (*invoke)(HoroEditor$__Closure_718_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_726_36 {
	void  (*invoke)(HoroEditor$__Closure_726_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_734_36 {
	void  (*invoke)(HoroEditor$__Closure_734_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_741_36 {
	void  (*invoke)(HoroEditor$__Closure_741_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_620_16*  __var___Block_620_16 ;
};





struct tagHoroEditor$__Closure_747_36 {
	void  (*invoke)(HoroEditor$__Closure_747_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_760_36 {
	void  (*invoke)(HoroEditor$__Closure_760_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_620_16*  __var___Block_620_16 ;
};





struct tagHoroEditor$__Closure_775_36 {
	void  (*invoke)(HoroEditor$__Closure_775_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_802_49 {
	void  (*invoke)(HoroEditor$__Closure_802_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_620_16*  __var___Block_620_16 ;
};





struct tagHoroEditor$__Closure_832_52 {
	SuiCore$ViewBase *  (*invoke)(HoroEditor$__Closure_832_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_620_16*  __var___Block_620_16 ;
};





struct tagHoroEditor$__Closure_940_35 {
	void  (*invoke)(HoroEditor$__Closure_940_35 *  self);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_936_32*  __var___Block_936_32 ;
};





struct tagHoroEditor$__Closure_985_32 {
	void  (*invoke)(HoroEditor$__Closure_985_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_936_32*  __var___Block_936_32 ;
};





struct tagHoroEditor$__Closure_1104_26 {
	void  (*invoke)(HoroEditor$__Closure_1104_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_1072_21*  __var___Block_1072_21 ;
};





// static function declaration
static void  __finiBlock___Block_233_33(HoroEditor$__Block_233_33 *  self);
static void  __finiBlock___Block_243_49(HoroEditor$__Block_243_49 *  self);
static void  __finiBlock___Block_337_47(HoroEditor$__Block_337_47 *  self);
static void  __finiBlock___Block_620_16(HoroEditor$__Block_620_16 *  self);
static void  __finiBlock___Block_626_35(HoroEditor$__Block_626_35 *  self);
static void  __finiBlock___Block_680_43(HoroEditor$__Block_680_43 *  self);
static void  __finiBlock___Block_936_32(HoroEditor$__Block_936_32 *  self);
static void  __finiBlock___Block_1072_21(HoroEditor$__Block_1072_21 *  self);
static void  __fn___Closure_187_27(HoroEditor$__Closure_187_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_187_27(HoroEditor$__Closure_187_27 *  self);
static HoroEditor$__Closure_187_27*  __make___Closure_187_27(HoroEditor$__Closure_187_27 **  __outRef__);
static void  __fn___Closure_221_26(HoroEditor$__Closure_221_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_221_26(HoroEditor$__Closure_221_26 *  self);
static HoroEditor$__Closure_221_26*  __make___Closure_221_26(HoroEditor$__Closure_221_26 **  __outRef__);
static void  __fn___Closure_235_42(HoroEditor$__Closure_235_42 *  self, Orc$String*  newValue);
static void  __fini___Closure_235_42(HoroEditor$__Closure_235_42 *  self);
static HoroEditor$__Closure_235_42*  __make___Closure_235_42(HoroEditor$__Closure_235_42 **  __outRef__, HoroEditor$__Block_233_33 *  __var___Block_233_33);
static void  __fn___Closure_269_26(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_269_26(HoroEditor$__Closure_269_26 *  self);
static HoroEditor$__Closure_269_26*  __make___Closure_269_26(HoroEditor$__Closure_269_26 **  __outRef__);
static void  __fn___Closure_324_38(HoroEditor$__Closure_324_38 *  self, SuiCore$Event *  e);
static void  __fini___Closure_324_38(HoroEditor$__Closure_324_38 *  self);
static HoroEditor$__Closure_324_38*  __make___Closure_324_38(HoroEditor$__Closure_324_38 **  __outRef__, HoroEditor$__Block_243_49 *  __var___Block_243_49);
static void  __fn___Closure_329_48(HoroEditor$__Closure_329_48 *  self);
static void  __fini___Closure_329_48(HoroEditor$__Closure_329_48 *  self);
static HoroEditor$__Closure_329_48*  __make___Closure_329_48(HoroEditor$__Closure_329_48 **  __outRef__, HoroEditor$__Block_243_49 *  __var___Block_243_49);
static void  __fn___Closure_514_44(HoroEditor$__Closure_514_44 *  self, SuiView$Drag *  d);
static void  __fini___Closure_514_44(HoroEditor$__Closure_514_44 *  self);
static HoroEditor$__Closure_514_44*  __make___Closure_514_44(HoroEditor$__Closure_514_44 **  __outRef__, HoroEditor$__Block_243_49 *  __var___Block_243_49, HoroEditor$__Block_337_47 *  __var___Block_337_47);
static SuiView$MenuNativeItem*  __fn___Closure_634_51(SuiView$MenuNativeItem **  __outRef__, HoroEditor$__Closure_634_51 *  self, SuiView$MenuButton *  mbutton);
static void  __fini___Closure_634_51(HoroEditor$__Closure_634_51 *  self);
static HoroEditor$__Closure_634_51*  __make___Closure_634_51(HoroEditor$__Closure_634_51 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16);
static void  __fn___Closure_onActive_635(HoroEditor$__Closure_onActive_635 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_635(HoroEditor$__Closure_onActive_635 *  self);
static HoroEditor$__Closure_onActive_635*  __make___Closure_onActive_635(HoroEditor$__Closure_onActive_635 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16);
static void  __fn___Closure_684_44(HoroEditor$__Closure_684_44 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_684_44(HoroEditor$__Closure_684_44 *  self);
static HoroEditor$__Closure_684_44*  __make___Closure_684_44(HoroEditor$__Closure_684_44 **  __outRef__, HoroEditor$__Block_626_35 *  __var___Block_626_35, HoroEditor$__Block_680_43 *  __var___Block_680_43);
static void  __fn___Closure_688_39(HoroEditor$__Closure_688_39 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_688_39(HoroEditor$__Closure_688_39 *  self);
static HoroEditor$__Closure_688_39*  __make___Closure_688_39(HoroEditor$__Closure_688_39 **  __outRef__, HoroEditor$__Block_626_35 *  __var___Block_626_35, HoroEditor$__Block_680_43 *  __var___Block_680_43);
static void  __fn___Closure_698_36(HoroEditor$__Closure_698_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_698_36(HoroEditor$__Closure_698_36 *  self);
static HoroEditor$__Closure_698_36*  __make___Closure_698_36(HoroEditor$__Closure_698_36 **  __outRef__);
static void  __fn___Closure_705_36(HoroEditor$__Closure_705_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_705_36(HoroEditor$__Closure_705_36 *  self);
static HoroEditor$__Closure_705_36*  __make___Closure_705_36(HoroEditor$__Closure_705_36 **  __outRef__);
static void  __fn___Closure_711_36(HoroEditor$__Closure_711_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_711_36(HoroEditor$__Closure_711_36 *  self);
static HoroEditor$__Closure_711_36*  __make___Closure_711_36(HoroEditor$__Closure_711_36 **  __outRef__);
static void  __fn___Closure_718_36(HoroEditor$__Closure_718_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_718_36(HoroEditor$__Closure_718_36 *  self);
static HoroEditor$__Closure_718_36*  __make___Closure_718_36(HoroEditor$__Closure_718_36 **  __outRef__);
static void  __fn___Closure_726_36(HoroEditor$__Closure_726_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_726_36(HoroEditor$__Closure_726_36 *  self);
static HoroEditor$__Closure_726_36*  __make___Closure_726_36(HoroEditor$__Closure_726_36 **  __outRef__);
static void  __fn___Closure_734_36(HoroEditor$__Closure_734_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_734_36(HoroEditor$__Closure_734_36 *  self);
static HoroEditor$__Closure_734_36*  __make___Closure_734_36(HoroEditor$__Closure_734_36 **  __outRef__);
static void  __fn___Closure_741_36(HoroEditor$__Closure_741_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_741_36(HoroEditor$__Closure_741_36 *  self);
static HoroEditor$__Closure_741_36*  __make___Closure_741_36(HoroEditor$__Closure_741_36 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16);
static void  __fn___Closure_747_36(HoroEditor$__Closure_747_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_747_36(HoroEditor$__Closure_747_36 *  self);
static HoroEditor$__Closure_747_36*  __make___Closure_747_36(HoroEditor$__Closure_747_36 **  __outRef__);
static void  __fn___Closure_760_36(HoroEditor$__Closure_760_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_760_36(HoroEditor$__Closure_760_36 *  self);
static HoroEditor$__Closure_760_36*  __make___Closure_760_36(HoroEditor$__Closure_760_36 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16);
static void  __fn___Closure_775_36(HoroEditor$__Closure_775_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_775_36(HoroEditor$__Closure_775_36 *  self);
static HoroEditor$__Closure_775_36*  __make___Closure_775_36(HoroEditor$__Closure_775_36 **  __outRef__);
static void  __fn___Closure_802_49(HoroEditor$__Closure_802_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
static void  __fini___Closure_802_49(HoroEditor$__Closure_802_49 *  self);
static HoroEditor$__Closure_802_49*  __make___Closure_802_49(HoroEditor$__Closure_802_49 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16);
static SuiCore$ViewBase *  __fn___Closure_832_52(HoroEditor$__Closure_832_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
static void  __fini___Closure_832_52(HoroEditor$__Closure_832_52 *  self);
static HoroEditor$__Closure_832_52*  __make___Closure_832_52(HoroEditor$__Closure_832_52 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16);
static void  __fn___Closure_940_35(HoroEditor$__Closure_940_35 *  self);
static void  __fini___Closure_940_35(HoroEditor$__Closure_940_35 *  self);
static HoroEditor$__Closure_940_35*  __make___Closure_940_35(HoroEditor$__Closure_940_35 **  __outRef__, HoroEditor$__Block_936_32 *  __var___Block_936_32);
static void  __fn___Closure_985_32(HoroEditor$__Closure_985_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_985_32(HoroEditor$__Closure_985_32 *  self);
static HoroEditor$__Closure_985_32*  __make___Closure_985_32(HoroEditor$__Closure_985_32 **  __outRef__, HoroEditor$__Block_936_32 *  __var___Block_936_32);
static void  __fn___Closure_1104_26(HoroEditor$__Closure_1104_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_1104_26(HoroEditor$__Closure_1104_26 *  self);
static HoroEditor$__Closure_1104_26*  __make___Closure_1104_26(HoroEditor$__Closure_1104_26 **  __outRef__, HoroEditor$__Block_1072_21 *  __var___Block_1072_21);


static URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  dockLayoutIns = NULL;

//vtable instance
Vtable_HoroEditor$HoroEditorSceneViewCallback _vtable_HoroEditor$HoroEditorSceneViewCallback;

// init meta

void HoroEditor$HoroEditorSceneViewCallback_initMeta(Vtable_HoroEditor$HoroEditorSceneViewCallback *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "horoEditor", ((Vtable_Object*)Vtable_HoroEditor$HoroEditor_init(0)), offsetof(HoroEditor$HoroEditorSceneViewCallback, horoEditor), true, false, 1);

	
}


// vtable init


Vtable_HoroEditor$HoroEditorSceneViewCallback* Vtable_HoroEditor$HoroEditorSceneViewCallback_init(Vtable_HoroEditor$HoroEditorSceneViewCallback* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroEditorSceneViewCallback;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$ViewCallback_init(&_vtable_SuiCore$ViewCallback);

	// init by super vtable init function
    Vtable_SuiCore$ViewCallback_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$ViewCallback;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroEditorSceneViewCallback_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroEditorSceneViewCallback";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroEditorSceneViewCallback_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroEditorSceneViewCallback_fini(HoroEditor$HoroEditorSceneViewCallback *self){
	//super fini
    SuiCore$ViewCallback_fini((SuiCore$ViewCallback *)self);

    //字段释放


}

// init fields function


void HoroEditor$HoroEditorSceneViewCallback_init_fields(HoroEditor$HoroEditorSceneViewCallback *self){
	//super class
    SuiCore$ViewCallback_init_fields((SuiCore$ViewCallback*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroEditorSceneViewCallback_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditorSceneViewCallback*)self)->horoEditor, NULL);
    }
	((SuiCore$ViewCallback*)self)->afterDrawSelf = (void*)HoroEditor$HoroEditorSceneViewCallback$afterDrawSelf;
}

// init function

void HoroEditor$HoroEditorSceneViewCallback_init(HoroEditor$HoroEditorSceneViewCallback *self, void *pOwner){
    Vtable_HoroEditor$HoroEditorSceneViewCallback_init(&_vtable_HoroEditor$HoroEditorSceneViewCallback);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroEditorSceneViewCallback;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroEditorSceneViewCallback_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroEditorSceneViewCallback * HoroEditor$HoroEditorSceneViewCallback_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroEditorSceneViewCallback *self = calloc(1, sizeof(HoroEditor$HoroEditorSceneViewCallback));
	
    HoroEditor$HoroEditorSceneViewCallback_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroEditorSceneViewCallback$afterDrawSelf(HoroEditor$HoroEditorSceneViewCallback *  self, SuiCore$View *  div, SuiCore$Canvas *  canvas){
	self->horoEditor->toolMgr->draw2d(self->horoEditor->toolMgr, canvas) ;
}




//vtable instance
Vtable_HoroEditor$HoroEditor _vtable_HoroEditor$HoroEditor;

// init meta

void HoroEditor$HoroEditor_initMeta(Vtable_HoroEditor$HoroEditor *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_HoroEditor$HoroEditCtx_init(0)), offsetof(HoroEditor$HoroEditor, editCtx), true, false, 1);
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(HoroEditor$HoroEditor, win), true, false, 1);
	orc_metaField_class(&pNext, "imgCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(HoroEditor$HoroEditor, imgCell), true, false, 1);
	orc_metaField_class(&pNext, "previewCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(HoroEditor$HoroEditor, previewCell), true, false, 1);
	orc_metaField_class(&pNext, "invalidReact", ((Vtable_Object*)Vtable_SuiDesigner$InvalidReact_init(0)), offsetof(HoroEditor$HoroEditor, invalidReact), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroEditor, path), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(HoroEditor$HoroEditor, drag), true, false, 1);
	orc_metaField_class(&pNext, "viewCb", ((Vtable_Object*)Vtable_HoroEditor$HoroEditorSceneViewCallback_init(0)), offsetof(HoroEditor$HoroEditor, viewCb), true, false, 1);
	orc_metaField_class(&pNext, "toolMgr", ((Vtable_Object*)Vtable_SuiDesigner$ToolMgr_init(0)), offsetof(HoroEditor$HoroEditor, toolMgr), true, false, 1);
	orc_metaField_class(&pNext, "sglGizmo", ((Vtable_Object*)Vtable_SuiDesigner$SglGizmo_init(0)), offsetof(HoroEditor$HoroEditor, sglGizmo), true, false, 1);
	orc_metaField_class(&pNext, "chessBg", ((Vtable_Object*)Vtable_SuiDesigner$ChessBgViewCallback_init(0)), offsetof(HoroEditor$HoroEditor, chessBg), true, false, 1);
	orc_metaField_class(&pNext, "glPreviewView", ((Vtable_Object*)Vtable_Sgl$MaterialPreviewView_init(0)), offsetof(HoroEditor$HoroEditor, glPreviewView), true, false, 1);
	orc_metaField_class(&pNext, "matl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(HoroEditor$HoroEditor, matl), true, false, 1);
	orc_metaField_class(&pNext, "gizmosView", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(HoroEditor$HoroEditor, gizmosView), true, false, 1);
	orc_metaField_class(&pNext, "mesh", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(HoroEditor$HoroEditor, mesh), true, false, 1);
	orc_metaField_class(&pNext, "meshSphere", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(HoroEditor$HoroEditor, meshSphere), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_Sgl$SglSceneView_init(0)), offsetof(HoroEditor$HoroEditor, sceneView), true, false, 1);
	orc_metaField_class(&pNext, "w3e", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$W3e_init(0)), offsetof(HoroEditor$HoroEditor, w3e), true, false, 1);
	orc_metaField_class(&pNext, "geom", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(HoroEditor$HoroEditor, geom), true, false, 1);
	orc_metaField_class(&pNext, "heightmap", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(HoroEditor$HoroEditor, heightmap), true, false, 1);
	orc_metaField_class(&pNext, "outlineFx", ((Vtable_Object*)Vtable_Sgl$OutlineFx_init(0)), offsetof(HoroEditor$HoroEditor, outlineFx), true, false, 1);

	orc_metaField_method(&pNext, "printSceneTree", offsetof(HoroEditor$HoroEditor, printSceneTree));
	orc_metaField_method(&pNext, "onSceneEvent", offsetof(HoroEditor$HoroEditor, onSceneEvent));
	orc_metaField_method(&pNext, "_afterDrawScene", offsetof(HoroEditor$HoroEditor, _afterDrawScene));
	orc_metaField_method(&pNext, "reactPreview", offsetof(HoroEditor$HoroEditor, reactPreview));
	orc_metaField_method(&pNext, "showDialog_renameLayer", offsetof(HoroEditor$HoroEditor, showDialog_renameLayer));
	orc_metaField_method(&pNext, "reactScene", offsetof(HoroEditor$HoroEditor, reactScene));
	orc_metaField_method(&pNext, "reactGizmosView", offsetof(HoroEditor$HoroEditor, reactGizmosView));
	orc_metaField_method(&pNext, "react", offsetof(HoroEditor$HoroEditor, react));
	orc_metaField_method(&pNext, "showWindow_mapSetting", offsetof(HoroEditor$HoroEditor, showWindow_mapSetting));
	orc_metaField_method(&pNext, "onWindowEvent", offsetof(HoroEditor$HoroEditor, onWindowEvent));
	orc_metaField_method(&pNext, "showOutline", offsetof(HoroEditor$HoroEditor, showOutline));
	orc_metaField_method(&pNext, "testShowMatl", offsetof(HoroEditor$HoroEditor, testShowMatl));
	orc_metaField_method(&pNext, "showWindow", offsetof(HoroEditor$HoroEditor, showWindow));
	orc_metaField_method(&pNext, "openProject", offsetof(HoroEditor$HoroEditor, openProject));
}


// vtable init


Vtable_HoroEditor$HoroEditor* Vtable_HoroEditor$HoroEditor_init(Vtable_HoroEditor$HoroEditor* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroEditor;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiCore$Listener_init(&_vtable_SuiCore$Listener);

	// init by super vtable init function
    Vtable_SuiCore$Listener_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiCore$Listener;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroEditor_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroEditor";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroEditor_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroEditor_fini(HoroEditor$HoroEditor *self){
	//super fini
    SuiCore$Listener_fini((SuiCore$Listener *)self);

    //字段释放


}

// init fields function


void HoroEditor$HoroEditor_init_fields(HoroEditor$HoroEditor *self){
	//super class
    SuiCore$Listener_init_fields((SuiCore$Listener*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroEditor_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroEditCtx*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->editCtx, HoroEditor$HoroEditCtx_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->win, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->imgCell, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->previewCell, NULL);
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InvalidReact*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->invalidReact, SuiDesigner$mkInvalidReact(&tmpReturn_2, self) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->path, Orc$str(&tmpReturn_3, "../build/././a.tilemap.json") );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->drag, SuiView$Drag_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroEditorSceneViewCallback*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->viewCb, HoroEditor$HoroEditorSceneViewCallback_new(&tmpNewOwner_5) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ToolMgr*  tmpNewOwner_6 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->toolMgr, SuiDesigner$ToolMgr_new(&tmpNewOwner_6) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SglGizmo*  tmpNewOwner_7 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->sglGizmo, SuiDesigner$SglGizmo_new(&tmpNewOwner_7) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ChessBgViewCallback*  tmpNewOwner_8 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->chessBg, SuiDesigner$ChessBgViewCallback_new(&tmpNewOwner_8) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->glPreviewView, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->matl, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->gizmosView, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->mesh, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->meshSphere, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->sceneView, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->w3e, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->geom, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->heightmap, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$OutlineFx*  tmpNewOwner_9 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->outlineFx, Sgl$OutlineFx_new(&tmpNewOwner_9) );
    }
	((HoroEditor$HoroEditor*)self)->printSceneTree = (void*)HoroEditor$HoroEditor$printSceneTree;
	((HoroEditor$HoroEditor*)self)->onSceneEvent = (void*)HoroEditor$HoroEditor$onSceneEvent;
	((HoroEditor$HoroEditor*)self)->_afterDrawScene = (void*)HoroEditor$HoroEditor$_afterDrawScene;
	((Object*)self)->ctor = (void*)HoroEditor$HoroEditor$ctor;
	((Object*)self)->dtor = (void*)HoroEditor$HoroEditor$dtor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)HoroEditor$HoroEditor$onListenerEvent;
	((HoroEditor$HoroEditor*)self)->reactPreview = (void*)HoroEditor$HoroEditor$reactPreview;
	((HoroEditor$HoroEditor*)self)->showDialog_renameLayer = (void*)HoroEditor$HoroEditor$showDialog_renameLayer;
	((HoroEditor$HoroEditor*)self)->reactScene = (void*)HoroEditor$HoroEditor$reactScene;
	((HoroEditor$HoroEditor*)self)->reactGizmosView = (void*)HoroEditor$HoroEditor$reactGizmosView;
	((HoroEditor$HoroEditor*)self)->react = (void*)HoroEditor$HoroEditor$react;
	((HoroEditor$HoroEditor*)self)->showWindow_mapSetting = (void*)HoroEditor$HoroEditor$showWindow_mapSetting;
	((HoroEditor$HoroEditor*)self)->onWindowEvent = (void*)HoroEditor$HoroEditor$onWindowEvent;
	((HoroEditor$HoroEditor*)self)->showOutline = (void*)HoroEditor$HoroEditor$showOutline;
	((HoroEditor$HoroEditor*)self)->testShowMatl = (void*)HoroEditor$HoroEditor$testShowMatl;
	((HoroEditor$HoroEditor*)self)->showWindow = (void*)HoroEditor$HoroEditor$showWindow;
	((HoroEditor$HoroEditor*)self)->openProject = (void*)HoroEditor$HoroEditor$openProject;
}

// init function

void HoroEditor$HoroEditor_init(HoroEditor$HoroEditor *self, void *pOwner){
    Vtable_HoroEditor$HoroEditor_init(&_vtable_HoroEditor$HoroEditor);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroEditor;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroEditor_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroEditor * HoroEditor$HoroEditor_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroEditor *self = calloc(1, sizeof(HoroEditor$HoroEditor));
	
    HoroEditor$HoroEditor_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroEditor$printSceneTree(HoroEditor$HoroEditor *  self){
	
}


void  HoroEditor$HoroEditor$onSceneEvent(HoroEditor$HoroEditor *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		SuiCore$Rect absRect = ((SuiCore$ViewBase * )self->sceneView)->get_abs_rect(self->sceneView) ;
		SuiCore$Vec2 fboSize = self->sceneView->fbo->getSize(self->sceneView->fbo) ;
		me->ndcPos = SuiCore$mkVec2((me->clientX - absRect.x) / fboSize.x * 2.0 - 1.0, -(me->clientY - SuiCore$Rect$bottom(&absRect) ) / fboSize.y * 2.0 - 1.0) ;
	}
	if (e->isStopPropagation) {
		return ; 
	}
	self->sglGizmo->onEvent(self->sglGizmo, e) ;
	{
		if (e->isStopPropagation) {
			return ; 
		}
		self->toolMgr->onEvent(self->toolMgr, e) ;
	}
}


void  HoroEditor$HoroEditor$_afterDrawScene(HoroEditor$HoroEditor *  self){
	SuiCore$Node *  sel = self->editCtx->state->getFirstSelected(self->editCtx->state) ;
	if (sel && Orc_instanceof((Object*)sel, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		self->outlineFx->draw(self->outlineFx, self->sceneView->drawCtx, sel, self->sceneView->fbo) ;
	}
	urgc_set_field_class(self->toolMgr, (void * )offsetof(SuiDesigner$ToolMgr, scene) , self->sceneView->scene) ;
	urgc_set_field(self->toolMgr, (void * )offsetof(SuiDesigner$ToolMgr, camera) , self->sceneView->camera) ;
	urgc_set_field_class(self->toolMgr, (void * )offsetof(SuiDesigner$ToolMgr, selectNode) , sel) ;
	urgc_set_field(self->toolMgr, (void * )offsetof(SuiDesigner$ToolMgr, editCtx) , self->editCtx) ;
	self->toolMgr->reactGizmo(self->toolMgr, self->sglGizmo) ;
	self->sglGizmo->draw(self->sglGizmo, self->sceneView->drawCtx) ;
	self->reactGizmosView(self) ;
}


void  HoroEditor$HoroEditor$ctor(HoroEditor$HoroEditor *  self){
	urgc_set_field_class(self->viewCb, (void * )offsetof(HoroEditor$HoroEditorSceneViewCallback, horoEditor) , self) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_187_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_187_27(&tmpReturn_1) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  projectDirPath = (projectDirPath=NULL,urgc_init_var_class((void**)&projectDirPath, Orc$String$add(Orc$Path_dirname(&tmpReturn_2, Orc$Path_getExecutionPath(&tmpReturn_3) ->str) , "/../asset/matl") ));
	printf("projectDirPath:%s\n", projectDirPath->str) ;
	SuiDesigner$Project *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_4 = NULL;
	(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_4) )->init(tmpThis_1, projectDirPath->str) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ToolSelect*  tmpNewOwner_5 = NULL;
	self->toolMgr->setTool(self->toolMgr, SuiDesigner$ToolSelect_new(&tmpNewOwner_5) ) ;
	SuiCore$Emitter *  tmpThis_2 = NULL;
	(tmpThis_2 = SuiCore$useEbus() )->addListener(tmpThis_2, self) ;
}


void  HoroEditor$HoroEditor$dtor(HoroEditor$HoroEditor *  self){
	SuiCore$Emitter *  tmpThis_1 = NULL;
	(tmpThis_1 = SuiCore$useEbus() )->removeListener(tmpThis_1, self) ;
}


void  HoroEditor$HoroEditor$onListenerEvent(HoroEditor$HoroEditor *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_HoroEditor$EventHoroSelectedChanged_init(NULL))) {
		self->invalidReact->invalid(self->invalidReact) ;
	}
}


SuiCore$ViewBase *  HoroEditor$HoroEditor$reactPreview(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_215_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_215_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_215_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->chessBg) ;
		URGC_VAR_CLEANUP HoroEditor$__Closure_221_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_221_26(&tmpReturn_2) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) ;
		return o; 
	}
}


void  HoroEditor$HoroEditor$showDialog_renameLayer(HoroEditor$HoroEditor *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_233_33*  __var___Block_233_33 = (__var___Block_233_33=NULL,urgc_init_var((void**)&__var___Block_233_33, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_233_33) , __finiBlock___Block_233_33) ));
	urgc_set_field_class(__var___Block_233_33, (void * )offsetof(HoroEditor$__Block_233_33, self) , self) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_235_42*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt("hi", "重命名", __make___Closure_235_42(&tmpReturn_1, __var___Block_233_33) ) ;
}


SuiCore$ViewBase *  HoroEditor$HoroEditor$reactScene(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP HoroEditor$__Block_243_49*  __var___Block_243_49 = (__var___Block_243_49=NULL,urgc_init_var((void**)&__var___Block_243_49, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_243_49) , __finiBlock___Block_243_49) ));
	urgc_set_field_class(__var___Block_243_49, (void * )offsetof(HoroEditor$__Block_243_49, self) , self) ;
	if (0) {
		URGC_VAR_CLEANUP_CLASS Sgl$MaterialPreviewView*  tmpReturn_1 = NULL;
		{
			Sgl$MaterialPreviewView*  __scopeVar_246_12 = Sgl$mkMaterialPreviewView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_246_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_246_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0x00222222;
			((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
			if (o->matl != self->matl) {
				urgc_set_field_class(o, (void * )offsetof(Sgl$MaterialPreviewView, matl) , self->matl) ;
				o->buildDrawObj(o) ;
			}
			urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, glPreviewView) , o) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
			SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) ;
			return o; 
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_264_8 = SuiLayout$layoutAlign(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_264_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_264_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		URGC_VAR_CLEANUP HoroEditor$__Closure_269_26*  tmpReturn_4 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_269_26(&tmpReturn_4) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) ;
		if (0) {
			URGC_VAR_CLEANUP_CLASS Sgl$MaterialPreviewView*  tmpReturn_6 = NULL;
			{
				Sgl$MaterialPreviewView*  __scopeVar_277_20 = Sgl$mkMaterialPreviewView(&tmpReturn_6, o, 0) , *o = __scopeVar_277_20;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_277_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->backgroundColor = 0x00ffffff;
				((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
				if (o->matl != self->matl) {
					urgc_set_field_class(o, (void * )offsetof(Sgl$MaterialPreviewView, matl) , self->matl) ;
					o->buildDrawObj(o) ;
					urgc_set_field_class(o->drawObj, (void * )offsetof(Sgl$Draw, geometry) , self->geom) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
					tex->loadImageByPathCstr(tex, "../asset/terrain.png") ;
					o->drawObj->material->setUniformTex2d(o->drawObj->material, "tex", tex) ;
				}
				urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, glPreviewView) , o) ;
				((SuiCore$View * )o)->width = 500;
				((SuiCore$View * )o)->height = 500;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_7 = NULL;
				{
					SuiLayout$LayoutAlignPositionCell*  __scopeVar_310_24 = SuiLayout$layoutAlignPositionCell(&tmpReturn_7, o, 0) , *o = __scopeVar_310_24;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_310_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->left = 0;
					o->top = 0;
					o->right = 0;
					o->bottom = 0;
				}
			}
		}
		if (1) {
			URGC_VAR_CLEANUP_CLASS Sgl$SglSceneView*  tmpReturn_8 = NULL;
			{
				Sgl$SglSceneView*  __scopeVar_322_20 = Sgl$mkSglSceneView(&tmpReturn_8, o, 0) , *o = __scopeVar_322_20;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_322_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->viewCb) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_324_38*  tmpReturn_9 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_324_38(&tmpReturn_9, __var___Block_243_49) ) ;
				urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, sceneView) , o) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_329_48*  tmpReturn_10 = NULL;
				urgc_set_field(o->drawCtx, (void * )offsetof(Sgl$DrawCtx, cbAfterDraw) , __make___Closure_329_48(&tmpReturn_10, __var___Block_243_49) ) ;
				((SuiCore$View * )o)->backgroundColor = 0x00ffffff;
				((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
				if (o->matl != self->matl) {
					URGC_VAR_CLEANUP HoroEditor$__Block_337_47*  __var___Block_337_47 = (__var___Block_337_47=NULL,urgc_init_var((void**)&__var___Block_337_47, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_337_47) , __finiBlock___Block_337_47) ));
					o->mkBaseScene(o) ;
					self->editCtx->setSceneView(self->editCtx, o) ;
					SuiCore$Emitter *  tmpThis_1 = NULL;
					URGC_VAR_CLEANUP_CLASS HoroEditor$EventHoroSceneChanged*  tmpNewOwner_11 = NULL;
					(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, HoroEditor$EventHoroSceneChanged_new(&tmpNewOwner_11) ) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
					tex->loadImageByPathCstr(tex, "../asset/terrain.png") ;
					URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  dc = (dc=NULL,urgc_init_var_class((void**)&dc, Sgl$DrawCtx_new(&dc) ));
					urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, matl) , dc->depthMatl) ;
					urgc_set_field_class(o, (void * )offsetof(Sgl$SglSceneView, matl) , self->matl) ;
					o->buildDrawObj(o) ;
					URGC_VAR_CLEANUP_CLASS Sgl$GeometryArrow*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryArrow_new(&geom) ));
					geom->build(geom) ;
					urgc_set_field_class(o->drawObj, (void * )offsetof(Sgl$Draw, geometry) , geom) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_12 = NULL;
					urgc_set_field_class(__var___Block_337_47, (void * )offsetof(HoroEditor$__Block_337_47, m) , Sgl$Mesh_new(&tmpNewOwner_12) ) ;
					urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, meshSphere) , __var___Block_337_47->m) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_13 = NULL;
					urgc_set_field_class(__var___Block_337_47->m, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_13) ) ;
					__var___Block_337_47->m->material->load(__var___Block_337_47->m->material, "../asset/hi.matl.json") ;
					__var___Block_337_47->m->material->setUniformTex2d(__var___Block_337_47->m->material, "tex", tex) ;
					urgc_set_field_class(__var___Block_337_47->m, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
					((Sgl$Obj3d * )__var___Block_337_47->m)->position.y = -50;
					((Sgl$Obj3d * )__var___Block_337_47->m)->position.z = 100;
					((Sgl$Obj3d * )__var___Block_337_47->m)->visible = true;
					((SuiCore$Node * )o->scene)->appendChild(o->scene, __var___Block_337_47->m) ;
					Sgl$Scene *  scene = o->scene;
					Sgl$Draw *  drawObj = o->drawObj;
					URGC_VAR_CLEANUP_CLASS Sgl$PointLight*  tmpNewOwner_14 = NULL;
					{
						Sgl$PointLight*  o = Sgl$PointLight_new(&tmpNewOwner_14) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_394_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						SuiCore$Vec3$set(&((Sgl$Obj3d * )o)->position, -500, 0, 0) ;
						((SuiCore$Node * )scene)->appendChild(scene, o) ;
					}
					URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpCam = NULL;
					URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_15 = NULL;
					{
						Sgl$PerspectiveCamera*  o = Sgl$PerspectiveCamera_new(&tmpNewOwner_15) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_404_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						urgc_set_var_class(&tmpCam, o) ;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$str(&tmpReturn_16, "测试gizmo相机") ) ;
						((Sgl$Camera * )o)->updateProjectionMat(o) ;
						((Sgl$Camera * )o)->updateViewMat(o) ;
						SuiCore$Vec3$set(&((Sgl$Obj3d * )o)->position, -100, -0, 0) ;
						((SuiCore$Node * )scene)->appendChild(scene, o) ;
					}
					URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_17 = NULL;
					{
						Sgl$Mesh*  o = Sgl$Mesh_new(&tmpNewOwner_17) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_424_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						urgc_set_field_class(__var___Block_337_47, (void * )offsetof(HoroEditor$__Block_337_47, m) , o) ;
						URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_18 = NULL;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_18) ) ;
						o->material->load(o->material, "../asset/heightmap.matl.json") ;
						o->material->setUniformTex2d(o->material, "tex", tex) ;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, geometry) , self->geom) ;
						((Sgl$Obj3d * )o)->position.y = 0;
						((SuiCore$Node * )scene)->appendChild(scene, o) ;
						urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, heightmap) , o) ;
					}
					URGC_VAR_CLEANUP_CLASS Sgl$Billboard*  tmpReturn_19 = NULL;
					{
						Sgl$Billboard*  o = Sgl$mkBillboard(&tmpReturn_19, scene, 0) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_438_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$str(&tmpReturn_20, "billboad") ) ;
						URGC_VAR_CLEANUP_CLASS Sgl$GeometryRect*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryRect_new(&geom) ));
						geom->width = 320;
						geom->height = 320;
						geom->build(geom) ;
						URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_21 = NULL;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Billboard, material) , Sgl$Material_new(&tmpNewOwner_21) ) ;
						o->material->load(o->material, "../asset/billboard.matl.json") ;
						URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = Sgl$mkTex2dByPathCstr((tex = NULL,&tex), "../asset/gizmo/camera.png") ;
						o->material->setUniformTex2d(o->material, "tex", tex) ;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Billboard, geometry) , geom) ;
						SuiCore$Vec3$set(&((Sgl$Obj3d * )o)->position, 100, 100, 0) ;
					}
					if (0) {
						URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxReader*  mr = (mr=NULL,urgc_init_var_class((void**)&mr, SuiDesigner3d_w3e$MdxReader_new(&mr) ));
						mr->loadByPathCstr(mr, "../asset/Units/Human/Footman/Footman.mdx") ;
						URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MkMdx*  mkMdx = (mkMdx=NULL,urgc_init_var_class((void**)&mkMdx, SuiDesigner3d_w3e$MkMdx_new(&mkMdx) ));
						urgc_set_field_class(mkMdx, (void * )offsetof(SuiDesigner3d_w3e$MkMdx, mr) , mr) ;
						mkMdx->mkSkeleton(mkMdx) ;
						URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpNewOwner_22 = NULL;
						{
							Sgl$Obj3d*  o = Sgl$Obj3d_new(&tmpNewOwner_22) ;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_463_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							if (((SuiCore$Node * )mkMdx->ske)->parent != o) {
								((SuiCore$Node * )o)->appendChild(o, mkMdx->ske) ;
								URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxSeqPlayer*  player = (player=NULL,urgc_init_var_class((void**)&player, SuiDesigner3d_w3e$MdxSeqPlayer_new(&player) ));
								player->init(player, mr) ;
								((SuiCore$Node * )o)->appendChild(o, player) ;
								player->play(player, "Stand - 1") ;
							}
							urgc_set_field_class(__var___Block_337_47, (void * )offsetof(HoroEditor$__Block_337_47, m) , o) ;
							o->position.y = 0;
							((SuiCore$Node * )scene)->appendChild(scene, o) ;
							Sgl$Obj3d *  parent = o;
							for (int  i = 0; i < mr->geosets->size(mr->geosets) ; i++) {
								SuiDesigner3d_w3e$Geoset *  geoset = (SuiDesigner3d_w3e$Geoset * )mr->geosets->get(mr->geosets, i) ;
								SuiDesigner3d_w3e$MdxMaterial *  mmatl = mr->matls->get(mr->matls, geoset->material_id) ;
								SuiDesigner3d_w3e$Layer *  layer = mmatl->layers->get(mmatl->layers, 0) ;
								SuiDesigner3d_w3e$LayerTexture *  layerTexture = layer->textures->get(layer->textures, 0) ;
								SuiDesigner3d_w3e$TextureData *  texData = mr->texs->get(mr->texs, layerTexture->id) ;
								const char *  texPath = texData->getRealPath(texData) ;
								URGC_VAR_CLEANUP_CLASS Sgl$SkinMesh*  tmpNewOwner_23 = NULL;
								{
									Sgl$SkinMesh*  o = Sgl$SkinMesh_new(&tmpNewOwner_23) ;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_490_40 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									URGC_VAR_CLEANUP_CLASS Sgl$Material*  material = (material=NULL,urgc_init_var_class((void**)&material, Sgl$Material_new(&material) ));
									material->load(material, "../asset/mdx.matl.json") ;
									URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
									tex->loadImageByPathCstr(tex, Orc$String$add(Orc$str(&tmpReturn_24, "../asset/") , texPath) ->str) ;
									material->setUniformTex2d(material, "tex", tex) ;
									urgc_set_field_class(o, (void * )offsetof(Sgl$SkinMesh, material) , material) ;
									urgc_set_field_class(o, (void * )offsetof(Sgl$SkinMesh, geometry) , geoset->geom) ;
									((SuiCore$Node * )mkMdx->ske)->appendChild(mkMdx->ske, o) ;
								}
							}
						}
					}
					URGC_VAR_CLEANUP HoroEditor$__Closure_514_44*  tmpReturn_25 = NULL;
					urgc_set_field(o->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_514_44(&tmpReturn_25, __var___Block_243_49, __var___Block_337_47) ) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_26 = NULL;
					{
						Sgl$Mesh*  o = Sgl$Mesh_new(&tmpNewOwner_26) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_533_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, mesh) , o) ;
						URGC_VAR_CLEANUP_CLASS Sgl$GeometryPlane*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryPlane_new(&geom) ));
						geom->width = 10000;
						geom->height = 10000;
						geom->planeType = 1;
						geom->build(geom) ;
						URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_27 = NULL;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_27) ) ;
						o->material->load(o->material, "../asset/hi.matl.json") ;
						o->material->setUniformTex2d(o->material, "tex", tex) ;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
						((Sgl$Obj3d * )o)->position.y = 10;
						((Sgl$Obj3d * )o)->visible = false;
						((SuiCore$Node * )scene)->appendChild(scene, o) ;
					}
					o->drawObj->material->setUniformTex2d(o->drawObj->material, "tex", tex) ;
				}
				((SuiCore$View * )o)->width = 500;
				((SuiCore$View * )o)->height = 500;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_28 = NULL;
				{
					SuiLayout$LayoutAlignPositionCell*  __scopeVar_587_24 = SuiLayout$layoutAlignPositionCell(&tmpReturn_28, o, 0) , *o = __scopeVar_587_24;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_587_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->left = 0;
					o->top = 0;
					o->right = 0;
					o->bottom = 0;
				}
				URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_29 = NULL;
				{
					SuiCore$View*  __scopeVar_594_24 = SuiView$mkView(&tmpReturn_29, o, 0) , *o = __scopeVar_594_24;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_594_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, gizmosView) , o) ;
				}
			}
		}
		return o; 
	}
}


void  HoroEditor$HoroEditor$reactGizmosView(HoroEditor$HoroEditor *  self){
	{
		SuiCore$View*  o = self->gizmosView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_610_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		self->toolMgr->reactGizmosView(self->toolMgr, self->gizmosView) ;
	}
}


void  HoroEditor$HoroEditor$react(HoroEditor$HoroEditor *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_620_16*  __var___Block_620_16 = (__var___Block_620_16=NULL,urgc_init_var((void**)&__var___Block_620_16, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_620_16) , __finiBlock___Block_620_16) ));
	urgc_set_field_class(__var___Block_620_16, (void * )offsetof(HoroEditor$__Block_620_16, self) , self) ;
	__var___Block_620_16->t = SuiDesigner$themeIns() ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_623_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		if (1) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_626_16 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_626_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_626_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP HoroEditor$__Block_626_35*  __var___Block_626_35 = (__var___Block_626_35=NULL,urgc_init_var((void**)&__var___Block_626_35, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_626_35) , __finiBlock___Block_626_35) ));
				((SuiCore$View * )o)->backgroundColor = __var___Block_620_16->t->menubar_bg;
				SuiCore$Inset$setAxis(&((SuiCore$View * )o)->padding, 0, 6) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  btnsStr = Orc$str((btnsStr = NULL,&btnsStr), "文件,项目,视图,调试,窗口,帮助") ;
				URGC_VAR_CLEANUP_CLASS Orc$List*  btns = Orc$String$splitByRe((btns = NULL,&btns), btnsStr, ",") ;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$MenuBarCtrl*  tmpNewOwner_2 = NULL;
				urgc_set_field_class(__var___Block_626_35, (void * )offsetof(HoroEditor$__Block_626_35, group) , SuiDesigner$MenuBarCtrl_new(&tmpNewOwner_2) ) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_634_51*  tmpReturn_3 = NULL;
				urgc_set_field(__var___Block_626_35->group, (void * )offsetof(SuiDesigner$MenuBarCtrl, cbCreateMenuNativeItem) , __make___Closure_634_51(&tmpReturn_3, __var___Block_620_16) ) ;
				for (int  i = 0; i < btns->size(btns) ; i++) {
					Object *  obj = btns->get(btns, i) ;
					URGC_VAR_CLEANUP_CLASS Orc$String*  btn = (btn=NULL,urgc_init_var_class((void**)&btn, (Orc$String* )btns->get(btns, i) ));
					URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  tmpReturn_4 = NULL;
					{
						SuiView$MenuButton*  __scopeVar_680_24 = SuiView$mkMenuButton(&tmpReturn_4, o, i) , *o = __scopeVar_680_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_680_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP HoroEditor$__Block_680_43*  __var___Block_680_43 = (__var___Block_680_43=NULL,urgc_init_var((void**)&__var___Block_680_43, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_680_43) , __finiBlock___Block_680_43) ));
						urgc_set_field_class(__var___Block_680_43, (void * )offsetof(HoroEditor$__Block_680_43, mbutton) , o) ;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuButton, text) , btn) ;
						URGC_VAR_CLEANUP HoroEditor$__Closure_684_44*  tmpReturn_5 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onMouseMove) , __make___Closure_684_44(&tmpReturn_5, __var___Block_626_35, __var___Block_680_43) ) ;
						URGC_VAR_CLEANUP HoroEditor$__Closure_688_39*  tmpReturn_6 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onClick) , __make___Closure_688_39(&tmpReturn_6, __var___Block_626_35, __var___Block_680_43) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_7 = NULL;
			{
				SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_7, self->win->rootView, 0) ;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_695_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_8 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_696_20 = SuiView$mkDrawButton(&tmpReturn_8, o, 0) , *o = __scopeVar_696_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_696_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_9, "设置") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_698_36*  tmpReturn_10 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_698_36(&tmpReturn_10) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_11 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_703_20 = SuiView$mkDrawButton(&tmpReturn_11, o, 0) , *o = __scopeVar_703_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_703_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_12, "添加tilelayer") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_705_36*  tmpReturn_13 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_705_36(&tmpReturn_13) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_14 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_709_20 = SuiView$mkDrawButton(&tmpReturn_14, o, 0) , *o = __scopeVar_709_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_709_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_15, "添加tileset") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_711_36*  tmpReturn_16 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_711_36(&tmpReturn_16) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_17 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_715_20 = SuiView$mkDrawButton(&tmpReturn_17, o, 0) , *o = __scopeVar_715_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_715_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_18, "创建随机tile") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_718_36*  tmpReturn_19 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_718_36(&tmpReturn_19) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_20 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_723_20 = SuiView$mkDrawButton(&tmpReturn_20, o, 0) , *o = __scopeVar_723_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_723_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_21 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_21, "创建动画tile") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_726_36*  tmpReturn_22 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_726_36(&tmpReturn_22) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_23 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_731_20 = SuiView$mkDrawButton(&tmpReturn_23, o, 0) , *o = __scopeVar_731_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_731_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_24, "创建AutoTile") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_734_36*  tmpReturn_25 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_734_36(&tmpReturn_25) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_26 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_739_20 = SuiView$mkDrawButton(&tmpReturn_26, o, 0) , *o = __scopeVar_739_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_739_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_27 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_27, "打印树") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_741_36*  tmpReturn_28 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_741_36(&tmpReturn_28, __var___Block_620_16) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_29 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_745_20 = SuiView$mkDrawButton(&tmpReturn_29, o, 0) , *o = __scopeVar_745_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_745_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_30, "保存") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_747_36*  tmpReturn_31 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_747_36(&tmpReturn_31) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_32 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_758_20 = SuiView$mkDrawButton(&tmpReturn_32, o, 0) , *o = __scopeVar_758_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_758_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_33 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_33, "加载") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_760_36*  tmpReturn_34 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_760_36(&tmpReturn_34, __var___Block_620_16) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_35 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_773_20 = SuiView$mkDrawButton(&tmpReturn_35, o, 0) , *o = __scopeVar_773_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_773_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_36 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_36, "lala") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_775_36*  tmpReturn_37 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_775_36(&tmpReturn_37) ) ;
				}
			}
		}
		if (1) {
			URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpReturn_38 = NULL;
			{
				SuiView$DockLayout*  __scopeVar_795_16 = SuiView$dockLayout(&tmpReturn_38, o, 0) , *o = __scopeVar_795_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_795_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_var_class(&dockLayoutIns, o) ;
				((SuiCore$View * )o)->width = 100;
				((SuiCore$View * )o)->height = 20;
				((SuiCore$View * )o)->backgroundColor = 0x30000033;
				if (((SuiCore$Node * )o)->isNewForReact) {
					URGC_VAR_CLEANUP HoroEditor$__Closure_802_49*  tmpReturn_39 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemHeadView) , __make___Closure_802_49(&tmpReturn_39, __var___Block_620_16) ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_832_52*  tmpReturn_40 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemContentView) , __make___Closure_832_52(&tmpReturn_40, __var___Block_620_16) ) ;
					{
						SuiView$DockItem*  __scopeVar_888_24 = o->root, *o = __scopeVar_888_24;
						
					
						o->isHorizontal = false;
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_41 = NULL;
						{
							SuiView$DockItem*  __scopeVar_891_28 = SuiView$mkDockItemSplitter(&tmpReturn_41, o, NULL, true) , *o = __scopeVar_891_28;
							
						
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_42 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_43 = NULL;
							{
								SuiView$DockItem*  __scopeVar_892_32 = SuiView$mkDockItem(&tmpReturn_42, o, Orc$str(&tmpReturn_43, "hier") ) , *o = __scopeVar_892_32;
								
							
								o->intId = 0;
								o->width = 150;
							}
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_44 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_45 = NULL;
							{
								SuiView$DockItem*  __scopeVar_896_32 = SuiView$mkDockItem(&tmpReturn_44, o, Orc$str(&tmpReturn_45, "scene") ) , *o = __scopeVar_896_32;
								
							
								o->intId = 0;
							}
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_46 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_47 = NULL;
							{
								SuiView$DockItem*  __scopeVar_899_32 = SuiView$mkDockItem(&tmpReturn_46, o, Orc$str(&tmpReturn_47, "inspector") ) , *o = __scopeVar_899_32;
								
							
								o->intId = 0;
								o->width = 150;
							}
						}
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_48 = NULL;
						{
							SuiView$DockItem*  __scopeVar_904_28 = SuiView$mkDockItemSplitter(&tmpReturn_48, o, NULL, true) , *o = __scopeVar_904_28;
							
						
							o->width = 150;
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_49 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_50 = NULL;
							{
								SuiView$DockItem*  __scopeVar_906_32 = SuiView$mkDockItem(&tmpReturn_49, o, Orc$str(&tmpReturn_50, "project") ) , *o = __scopeVar_906_32;
								
							
								o->intId = 0;
								o->width = 160;
							}
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_51 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_52 = NULL;
							{
								SuiView$DockItem*  __scopeVar_910_32 = SuiView$mkDockItem(&tmpReturn_51, o, Orc$str(&tmpReturn_52, "dir") ) , *o = __scopeVar_910_32;
								
							
								o->intId = 0;
							}
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_53 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_53, o, 0) ;
				{
					
				}
			}
		}
	}
}


void  HoroEditor$HoroEditor$showWindow_mapSetting(HoroEditor$HoroEditor *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_936_32*  __var___Block_936_32 = (__var___Block_936_32=NULL,urgc_init_var((void**)&__var___Block_936_32, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_936_32) , __finiBlock___Block_936_32) ));
	urgc_set_field_class(__var___Block_936_32, (void * )offsetof(HoroEditor$__Block_936_32, win) , NULL) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_940_35*  tmpReturn_1 = NULL;
	urgc_set_field(__var___Block_936_32, (void * )offsetof(HoroEditor$__Block_936_32, reactMapSetting) , __make___Closure_940_35(&tmpReturn_1, __var___Block_936_32) ) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_2 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_2) ;
		
	
		urgc_set_field_class(__var___Block_936_32, (void * )offsetof(HoroEditor$__Block_936_32, win) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_3 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_3) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_994_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			__var___Block_936_32->win->setRootView(__var___Block_936_32->win, o) ;
		}
		(*(__var___Block_936_32->reactMapSetting))((void * )(__var___Block_936_32->reactMapSetting)) ;
		o->setTitle(o, "地图设置") ;
		o->setSize(o, 300, 400) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  HoroEditor$HoroEditor$onWindowEvent(HoroEditor$HoroEditor *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$KeyEvent_init(NULL))) {
		SuiCore$KeyEvent *  ke = (SuiCore$KeyEvent * )e;
		printf("2窗口收到键盘消息:%s\n", ke->key->str) ;
		if (Orc$String$equals(ke->key, "W") ) {
			self->sceneView->camera->moveForward(self->sceneView->camera) ;
		}
		if (Orc$String$equals(ke->key, "S") ) {
			self->sceneView->camera->moveBackward(self->sceneView->camera) ;
		}
		if (Orc$String$equals(ke->key, "A") ) {
			self->sceneView->camera->rotateLeft(self->sceneView->camera) ;
		}
		if (Orc$String$equals(ke->key, "D") ) {
			self->sceneView->camera->rotateRight(self->sceneView->camera) ;
		}
		if (Orc$String$equals(ke->key, "E") ) {
			self->sceneView->camera->rise(self->sceneView->camera) ;
		}
		if (Orc$String$equals(ke->key, "Q") ) {
			self->sceneView->camera->fall(self->sceneView->camera) ;
		}
	}
}


void  HoroEditor$HoroEditor$showOutline(HoroEditor$HoroEditor *  self){
	{
		Sgl$DrawCtx*  o = self->sceneView->drawCtx;
		
	
		self->outlineFx->updateFbo(self->outlineFx, o->frameSize) ;
		self->outlineFx->drawMask(self->outlineFx, o, self->heightmap) ;
		self->outlineFx->fboEdge->startDraw(self->outlineFx->fboEdge, 0, 0, 0, 0, true, true, true) ;
		self->outlineFx->drawFxQuad(self->outlineFx) ;
		self->outlineFx->fboEdge->endDraw(self->outlineFx->fboEdge) ;
		Sgl$SglSceneView_showTextureWindow(self->outlineFx->fbo->tex2d, SuiCore$Vec2$width(&o->frameSize) , SuiCore$Vec2$height(&o->frameSize) ) ;
		Sgl$SglSceneView_showTextureWindow(self->outlineFx->fboEdge->tex2d, SuiCore$Vec2$width(&o->frameSize) , SuiCore$Vec2$height(&o->frameSize) ) ;
	}
}


void  HoroEditor$HoroEditor$testShowMatl(HoroEditor$HoroEditor *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
	matl->load(matl, "../asset/box.matl.json") ;
	URGC_VAR_CLEANUP_CLASS Sgl$MaterialInsp*  tmpNewOwner_1 = NULL;
	{
		Sgl$MaterialInsp*  o = Sgl$MaterialInsp_new(&tmpNewOwner_1) ;
		
	
		o->showWindow(o, matl) ;
	}
}


void  HoroEditor$HoroEditor$showWindow(HoroEditor$HoroEditor *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_1072_21*  __var___Block_1072_21 = (__var___Block_1072_21=NULL,urgc_init_var((void**)&__var___Block_1072_21, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_1072_21) , __finiBlock___Block_1072_21) ));
	urgc_set_field_class(__var___Block_1072_21, (void * )offsetof(HoroEditor$__Block_1072_21, self) , self) ;
	if (0) {
		URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
		self->testShowMatl(self) ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, win) , Sui$Window_new(&tmpNewOwner_1) ) ;
	self->outlineFx->init(self->outlineFx) ;
	if (1) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$W3e*  w3e = (w3e=NULL,urgc_init_var_class((void**)&w3e, SuiDesigner3d_w3e$W3e_new(&w3e) ));
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, w3e) , w3e) ;
		w3e->load(w3e, "../asset/100.w3e") ;
		URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpReturn_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, geom) , w3e->mkGeometry(&tmpReturn_2, w3e) ) ;
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryHeightMap*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryHeightMap_new(&geom) ));
		geom->build(geom, "../asset/heightmap.png") ;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, geom) , geom) ;
		w3e->mkGroundTexs(w3e) ;
	}
	{
		Sui$Window*  o = self->win;
		
	
		URGC_VAR_CLEANUP HoroEditor$__Closure_1104_26*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_1104_26(&tmpReturn_3, __var___Block_1072_21) ) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_4 = NULL;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, matl) , Sgl$Material_new(&tmpNewOwner_4) ) ;
		self->matl->load(self->matl, "../asset/hi.matl.json") ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_5 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_5) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_1111_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			self->win->setRootView(self->win, o) ;
		}
		self->react(self) ;
		o->setTitle(o, "Horo编辑器") ;
		o->setSize(o, 800, 600) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  HoroEditor$HoroEditor$openProject(HoroEditor$HoroEditor *  self, const char *  path){
	Orc$Path_setcwd(path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  abspath = Orc$Path_toAbsolute((abspath = NULL,&abspath), path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  cwd = Orc$Path_getcwd((cwd = NULL,&cwd)) ;
	printf("打开项目。 项目路径为:%s. cwd:%s", abspath->str, cwd->str) ;
	SuiDesigner$Project *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_1) )->init(tmpThis_1, abspath->str) ;
	self->editCtx->openPrefab(self->editCtx, "prefab/button.prefab.json") ;
	self->showWindow(self) ;
}



static void  __finiBlock___Block_233_33(HoroEditor$__Block_233_33 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_233_33, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_243_49(HoroEditor$__Block_243_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_243_49, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_337_47(HoroEditor$__Block_337_47 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_337_47, m) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_620_16(HoroEditor$__Block_620_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_620_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_626_35(HoroEditor$__Block_626_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_626_35, group) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_680_43(HoroEditor$__Block_680_43 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_680_43, mbutton) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_936_32(HoroEditor$__Block_936_32 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_936_32, win) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_1072_21(HoroEditor$__Block_1072_21 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_1072_21, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_187_27(HoroEditor$__Closure_187_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("isDragging tileset\n") ;
	}
}

static void  __fini___Closure_187_27(HoroEditor$__Closure_187_27 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_187_27*  __make___Closure_187_27(HoroEditor$__Closure_187_27 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_187_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_187_27) , __fini___Closure_187_27) ));
	self->invoke = __fn___Closure_187_27;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_221_26(HoroEditor$__Closure_221_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	}
}

static void  __fini___Closure_221_26(HoroEditor$__Closure_221_26 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_221_26*  __make___Closure_221_26(HoroEditor$__Closure_221_26 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_221_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_221_26) , __fini___Closure_221_26) ));
	self->invoke = __fn___Closure_221_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_235_42(HoroEditor$__Closure_235_42 *  self, Orc$String*  newValue){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newValue);

	self->__var___Block_233_33->self->invalidReact->invalid(self->__var___Block_233_33->self->invalidReact) ;
}

static void  __fini___Closure_235_42(HoroEditor$__Closure_235_42 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_235_42, __var___Block_233_33) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_235_42*  __make___Closure_235_42(HoroEditor$__Closure_235_42 **  __outRef__, HoroEditor$__Block_233_33 *  __var___Block_233_33){
	URGC_VAR_CLEANUP HoroEditor$__Closure_235_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_235_42) , __fini___Closure_235_42) ));
	self->invoke = __fn___Closure_235_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_235_42, __var___Block_233_33) , __var___Block_233_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_269_26(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	}
}

static void  __fini___Closure_269_26(HoroEditor$__Closure_269_26 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_269_26*  __make___Closure_269_26(HoroEditor$__Closure_269_26 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_269_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_269_26) , __fini___Closure_269_26) ));
	self->invoke = __fn___Closure_269_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_324_38(HoroEditor$__Closure_324_38 *  self, SuiCore$Event *  e){
	self->__var___Block_243_49->self->onSceneEvent(self->__var___Block_243_49->self, e) ;
}

static void  __fini___Closure_324_38(HoroEditor$__Closure_324_38 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_324_38, __var___Block_243_49) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_324_38*  __make___Closure_324_38(HoroEditor$__Closure_324_38 **  __outRef__, HoroEditor$__Block_243_49 *  __var___Block_243_49){
	URGC_VAR_CLEANUP HoroEditor$__Closure_324_38*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_324_38) , __fini___Closure_324_38) ));
	self->invoke = __fn___Closure_324_38;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_324_38, __var___Block_243_49) , __var___Block_243_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_329_48(HoroEditor$__Closure_329_48 *  self){
	self->__var___Block_243_49->self->_afterDrawScene(self->__var___Block_243_49->self) ;
}

static void  __fini___Closure_329_48(HoroEditor$__Closure_329_48 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_329_48, __var___Block_243_49) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_329_48*  __make___Closure_329_48(HoroEditor$__Closure_329_48 **  __outRef__, HoroEditor$__Block_243_49 *  __var___Block_243_49){
	URGC_VAR_CLEANUP HoroEditor$__Closure_329_48*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_329_48) , __fini___Closure_329_48) ));
	self->invoke = __fn___Closure_329_48;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_329_48, __var___Block_243_49) , __var___Block_243_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_514_44(HoroEditor$__Closure_514_44 *  self, SuiView$Drag *  d){
	if (!d->isDragging) {
		return ; 
	}
	if (d->mouseDownButton == 1) {
		SuiCore$Vec3$add3fLocal(&((Sgl$Obj3d * )self->__var___Block_243_49->self->sceneView->camera)->position, d->deltaPos.x, d->deltaPos.y, 0) ;
	}
	if (d->mouseDownButton == 2) {
		((Sgl$Obj3d * )self->__var___Block_337_47->m)->rotation.x += Orc$toRad(d->deltaPos.y) ;
	}
	if (d->mouseDownButton == 3) {
		((Sgl$Obj3d * )self->__var___Block_337_47->m)->scale.x = Orc$maxFloat(0.1, ((Sgl$Obj3d * )self->__var___Block_337_47->m)->scale.x + d->deltaPos.x / 100.0) ;
		((Sgl$Obj3d * )self->__var___Block_337_47->m)->scale.y = ((Sgl$Obj3d * )self->__var___Block_337_47->m)->scale.x;
		((Sgl$Obj3d * )self->__var___Block_337_47->m)->scale.z = ((Sgl$Obj3d * )self->__var___Block_337_47->m)->scale.x;
	}
}

static void  __fini___Closure_514_44(HoroEditor$__Closure_514_44 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_514_44, __var___Block_243_49) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_514_44, __var___Block_337_47) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_514_44*  __make___Closure_514_44(HoroEditor$__Closure_514_44 **  __outRef__, HoroEditor$__Block_243_49 *  __var___Block_243_49, HoroEditor$__Block_337_47 *  __var___Block_337_47){
	URGC_VAR_CLEANUP HoroEditor$__Closure_514_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_514_44) , __fini___Closure_514_44) ));
	self->invoke = __fn___Closure_514_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_514_44, __var___Block_243_49) , __var___Block_243_49) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_514_44, __var___Block_337_47) , __var___Block_337_47) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiView$MenuNativeItem*  __fn___Closure_634_51(SuiView$MenuNativeItem **  __outRef__, HoroEditor$__Closure_634_51 *  self, SuiView$MenuButton *  mbutton){
	URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_635*  tmpReturn_1 = NULL;
	(urgc_set_var(&onActive, __make___Closure_onActive_635(&tmpReturn_1, self->__var___Block_620_16) ) );
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
	{
		SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, NULL, NULL) ;
		
	
		if (Orc$String$equals(mbutton->text, "文件") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_3 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_3, o, Orc$str(&tmpReturn_4, "新建场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_5 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_5, o, Orc$str(&tmpReturn_6, "打开场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_7 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_7, o, Orc$str(&tmpReturn_8, "保存场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_9 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
			{
				SuiView$MenuNativeItem*  __scopeVar_655_32 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "最近打开") , onActive) , *o = __scopeVar_655_32;
				
			
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_11 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
				SuiView$mkMenuNativeItem(&tmpReturn_11, o, Orc$str(&tmpReturn_12, "场景1") , onActive) ;
				URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_13 = NULL;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
				SuiView$mkMenuNativeItem(&tmpReturn_13, o, Orc$str(&tmpReturn_14, "场景2") , onActive) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_15 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_15, o, Orc$str(&tmpReturn_16, "另存为场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_17 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_17, o, Orc$str(&tmpReturn_18, "保存所有场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_19 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_19, o, Orc$str(&tmpReturn_20, "关闭场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_21 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_21, o, Orc$str(&tmpReturn_22, "重载已保存的场景") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_23 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_23, o, Orc$str(&tmpReturn_24, "设置") , onActive) ;
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_25 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_25, o, Orc$str(&tmpReturn_26, "退出") , onActive) ;
		}
		else if (Orc$String$equals(mbutton->text, "调试") ) {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_27 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_27, o, Orc$str(&tmpReturn_28, "Outline") , onActive) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_29 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_29, o, Orc$str(&tmpReturn_30, "退出") , onActive) ;
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}

static void  __fini___Closure_634_51(HoroEditor$__Closure_634_51 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_634_51, __var___Block_620_16) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_634_51*  __make___Closure_634_51(HoroEditor$__Closure_634_51 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16){
	URGC_VAR_CLEANUP HoroEditor$__Closure_634_51*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_634_51) , __fini___Closure_634_51) ));
	self->invoke = __fn___Closure_634_51;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_634_51, __var___Block_620_16) , __var___Block_620_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_635(HoroEditor$__Closure_onActive_635 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu:%s\n", item->label->str) ;
	if (Orc$String$equals(item->label, "退出") ) {
		exit(0) ;
	}
	if (Orc$String$equals(item->label, "Outline") ) {
		self->__var___Block_620_16->self->showOutline(self->__var___Block_620_16->self) ;
		return ; 
	}
	if (Orc$String$equals(item->label, "保存场景") ) {
		HoroEditor$UiAct_savePrefab(self->__var___Block_620_16->self) ;
		return ; 
	}
	SuiDialog$Toast_make(item->label->str) ;
}

static void  __fini___Closure_onActive_635(HoroEditor$__Closure_onActive_635 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_635, __var___Block_620_16) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_onActive_635*  __make___Closure_onActive_635(HoroEditor$__Closure_onActive_635 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16){
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_635*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_onActive_635) , __fini___Closure_onActive_635) ));
	self->invoke = __fn___Closure_onActive_635;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_635, __var___Block_620_16) , __var___Block_620_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_684_44(HoroEditor$__Closure_684_44 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_626_35->group->onmove(self->__var___Block_626_35->group, self->__var___Block_680_43->mbutton, me) ;
}

static void  __fini___Closure_684_44(HoroEditor$__Closure_684_44 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_684_44, __var___Block_626_35) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_684_44, __var___Block_680_43) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_684_44*  __make___Closure_684_44(HoroEditor$__Closure_684_44 **  __outRef__, HoroEditor$__Block_626_35 *  __var___Block_626_35, HoroEditor$__Block_680_43 *  __var___Block_680_43){
	URGC_VAR_CLEANUP HoroEditor$__Closure_684_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_684_44) , __fini___Closure_684_44) ));
	self->invoke = __fn___Closure_684_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_684_44, __var___Block_626_35) , __var___Block_626_35) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_684_44, __var___Block_680_43) , __var___Block_680_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_688_39(HoroEditor$__Closure_688_39 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_626_35->group->onclick(self->__var___Block_626_35->group, self->__var___Block_680_43->mbutton, me) ;
}

static void  __fini___Closure_688_39(HoroEditor$__Closure_688_39 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_688_39, __var___Block_626_35) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_688_39, __var___Block_680_43) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_688_39*  __make___Closure_688_39(HoroEditor$__Closure_688_39 **  __outRef__, HoroEditor$__Block_626_35 *  __var___Block_626_35, HoroEditor$__Block_680_43 *  __var___Block_680_43){
	URGC_VAR_CLEANUP HoroEditor$__Closure_688_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_688_39) , __fini___Closure_688_39) ));
	self->invoke = __fn___Closure_688_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_688_39, __var___Block_626_35) , __var___Block_626_35) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_688_39, __var___Block_680_43) , __var___Block_680_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_698_36(HoroEditor$__Closure_698_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_698_36(HoroEditor$__Closure_698_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_698_36*  __make___Closure_698_36(HoroEditor$__Closure_698_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_698_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_698_36) , __fini___Closure_698_36) ));
	self->invoke = __fn___Closure_698_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_705_36(HoroEditor$__Closure_705_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_705_36(HoroEditor$__Closure_705_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_705_36*  __make___Closure_705_36(HoroEditor$__Closure_705_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_705_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_705_36) , __fini___Closure_705_36) ));
	self->invoke = __fn___Closure_705_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_711_36(HoroEditor$__Closure_711_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_711_36(HoroEditor$__Closure_711_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_711_36*  __make___Closure_711_36(HoroEditor$__Closure_711_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_711_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_711_36) , __fini___Closure_711_36) ));
	self->invoke = __fn___Closure_711_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_718_36(HoroEditor$__Closure_718_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_718_36(HoroEditor$__Closure_718_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_718_36*  __make___Closure_718_36(HoroEditor$__Closure_718_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_718_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_718_36) , __fini___Closure_718_36) ));
	self->invoke = __fn___Closure_718_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_726_36(HoroEditor$__Closure_726_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_726_36(HoroEditor$__Closure_726_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_726_36*  __make___Closure_726_36(HoroEditor$__Closure_726_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_726_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_726_36) , __fini___Closure_726_36) ));
	self->invoke = __fn___Closure_726_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_734_36(HoroEditor$__Closure_734_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_734_36(HoroEditor$__Closure_734_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_734_36*  __make___Closure_734_36(HoroEditor$__Closure_734_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_734_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_734_36) , __fini___Closure_734_36) ));
	self->invoke = __fn___Closure_734_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_741_36(HoroEditor$__Closure_741_36 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_620_16->self->printSceneTree(self->__var___Block_620_16->self) ;
}

static void  __fini___Closure_741_36(HoroEditor$__Closure_741_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_741_36, __var___Block_620_16) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_741_36*  __make___Closure_741_36(HoroEditor$__Closure_741_36 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16){
	URGC_VAR_CLEANUP HoroEditor$__Closure_741_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_741_36) , __fini___Closure_741_36) ));
	self->invoke = __fn___Closure_741_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_741_36, __var___Block_620_16) , __var___Block_620_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_747_36(HoroEditor$__Closure_747_36 *  self, SuiCore$MouseEvent *  me){
	SuiDialog$Toast_make("保存成功") ;
}

static void  __fini___Closure_747_36(HoroEditor$__Closure_747_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_747_36*  __make___Closure_747_36(HoroEditor$__Closure_747_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_747_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_747_36) , __fini___Closure_747_36) ));
	self->invoke = __fn___Closure_747_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_760_36(HoroEditor$__Closure_760_36 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_620_16->self->invalidReact->invalid(self->__var___Block_620_16->self->invalidReact) ;
}

static void  __fini___Closure_760_36(HoroEditor$__Closure_760_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_760_36, __var___Block_620_16) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_760_36*  __make___Closure_760_36(HoroEditor$__Closure_760_36 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16){
	URGC_VAR_CLEANUP HoroEditor$__Closure_760_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_760_36) , __fini___Closure_760_36) ));
	self->invoke = __fn___Closure_760_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_760_36, __var___Block_620_16) , __var___Block_620_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_775_36(HoroEditor$__Closure_775_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_775_36(HoroEditor$__Closure_775_36 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_775_36*  __make___Closure_775_36(HoroEditor$__Closure_775_36 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_775_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_775_36) , __fini___Closure_775_36) ));
	self->invoke = __fn___Closure_775_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_802_49(HoroEditor$__Closure_802_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex){
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpItem = (tmpItem=NULL,urgc_init_var_class((void**)&tmpItem, item));
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpDock = (tmpDock=NULL,urgc_init_var_class((void**)&tmpDock, dockLayoutIns));
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_807_28 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_807_28;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_807_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_2, "pointer") ) ;
		o->setText(o, item->id) ;
		o->color = self->__var___Block_620_16->t->dock_head_c;
		((SuiCore$View * )o)->padding.top = 4;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->padding, 8) ;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 0.0f, 0xffaeaeb2) ;
		bool  active = item->parent->tabActiveIndex == kidIndex;
		if (active) {
			((SuiCore$View * )o)->border->t->w = 2.f;
			((SuiCore$View * )o)->border->t->color = self->__var___Block_620_16->t->c_main;
		}
		if (kidIndex < item->parent->children->size(item->parent->children)  - 1) {
			((SuiCore$View * )o)->border->r->w = 1.f;
		}
		((SuiCore$View * )o)->backgroundColor = active ? self->__var___Block_620_16->t->dock_head_bg_active : self->__var___Block_620_16->t->dock_head_bg;
	}
}

static void  __fini___Closure_802_49(HoroEditor$__Closure_802_49 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_802_49, __var___Block_620_16) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_802_49*  __make___Closure_802_49(HoroEditor$__Closure_802_49 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16){
	URGC_VAR_CLEANUP HoroEditor$__Closure_802_49*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_802_49) , __fini___Closure_802_49) ));
	self->invoke = __fn___Closure_802_49;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_802_49, __var___Block_620_16) , __var___Block_620_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$ViewBase *  __fn___Closure_832_52(HoroEditor$__Closure_832_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o){
	if (Orc$String$equals(item->id, "project") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirTreeView*  tmpReturn_1 = NULL;
		{
			SuiDesigner$AssetDirTreeView*  __scopeVar_834_32 = SuiDesigner$mkAssetDirTreeView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_834_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_834_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_620_16->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "dir") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirView*  tmpReturn_2 = NULL;
		{
			SuiDesigner$AssetDirView*  __scopeVar_840_32 = SuiDesigner$mkAssetDirView(&tmpReturn_2, o, (long long )item) , *o = __scopeVar_840_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_840_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_620_16->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "hier") ) {
		URGC_VAR_CLEANUP_CLASS HoroEditor$HoroSceneHierView*  tmpReturn_3 = NULL;
		{
			HoroEditor$HoroSceneHierView*  __scopeVar_846_32 = HoroEditor$mkHoroSceneHierView(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_846_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_846_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(o, (void * )offsetof(HoroEditor$HoroSceneHierView, editCtx) , self->__var___Block_620_16->self->editCtx) ;
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "inspector") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SglInspView*  tmpReturn_4 = NULL;
		{
			SuiDesigner$SglInspView*  __scopeVar_854_32 = SuiDesigner$mkSglInspView(&tmpReturn_4, o, (long long )item) , *o = __scopeVar_854_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_854_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field(o, (void * )offsetof(SuiDesigner$SglInspView, editCtx) , self->__var___Block_620_16->self->editCtx) ;
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_620_16->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "scene") ) {
		return self->__var___Block_620_16->self->reactScene(self->__var___Block_620_16->self, o, item) ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_5 = NULL;
	{
		SuiView$TextView*  __scopeVar_864_28 = SuiView$mkTextView(&tmpReturn_5, o, (long long )item) , *o = __scopeVar_864_28;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_864_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->needClip = true;
		printf("render dock content:%d, %s\n", item->intId, item->id->str) ;
		o->setText(o, item->id) ;
		o->font_size = 30;
		o->color = 0xff000000;
		((SuiCore$View * )o)->radius->setAll(((SuiCore$View * )o)->radius, 6) ;
		SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 6) ;
		((SuiCore$View * )o)->backgroundColor = item->intId == 0 ? 0x53ff0000 : item->intId == 1 ? 0x53f0ff00 : item->intId == 2 ? 0x5330ffff : 0x5300ffff;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
		{
			SuiLayout$LayoutLinearCell*  __scopeVar_880_32 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_880_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_880_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		return o; 
	}
}

static void  __fini___Closure_832_52(HoroEditor$__Closure_832_52 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_832_52, __var___Block_620_16) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_832_52*  __make___Closure_832_52(HoroEditor$__Closure_832_52 **  __outRef__, HoroEditor$__Block_620_16 *  __var___Block_620_16){
	URGC_VAR_CLEANUP HoroEditor$__Closure_832_52*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_832_52) , __fini___Closure_832_52) ));
	self->invoke = __fn___Closure_832_52;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_832_52, __var___Block_620_16) , __var___Block_620_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_940_35(HoroEditor$__Closure_940_35 *  self){
	{
		SuiCore$ViewBase*  o = self->__var___Block_936_32->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_941_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
		{
			SuiView$TextView*  __scopeVar_942_16 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_942_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_942_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			o->setText(o, Orc$str(&tmpReturn_2, "tileWidth:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_3 = NULL;
		{
			SuiView$EditText*  __scopeVar_945_16 = SuiView$mkEditText(&tmpReturn_3, o, 0) , *o = __scopeVar_945_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_945_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
		{
			SuiView$TextView*  __scopeVar_954_16 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_954_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_954_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			o->setText(o, Orc$str(&tmpReturn_5, "tileHeight:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_957_16 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_957_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_957_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
		{
			SuiView$TextView*  __scopeVar_966_16 = SuiView$mkTextView(&tmpReturn_7, o, 0) , *o = __scopeVar_966_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_966_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			o->setText(o, Orc$str(&tmpReturn_8, "fps:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_9 = NULL;
		{
			SuiView$EditText*  __scopeVar_969_16 = SuiView$mkEditText(&tmpReturn_9, o, 0) , *o = __scopeVar_969_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_969_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_10 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_983_16 = SuiView$mkDrawButton(&tmpReturn_10, o, 0) , *o = __scopeVar_983_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_983_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_11, "提交") ) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_985_32*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_985_32(&tmpReturn_12, self->__var___Block_936_32) ) ;
		}
	}
}

static void  __fini___Closure_940_35(HoroEditor$__Closure_940_35 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_940_35, __var___Block_936_32) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_940_35*  __make___Closure_940_35(HoroEditor$__Closure_940_35 **  __outRef__, HoroEditor$__Block_936_32 *  __var___Block_936_32){
	URGC_VAR_CLEANUP HoroEditor$__Closure_940_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_940_35) , __fini___Closure_940_35) ));
	self->invoke = __fn___Closure_940_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_940_35, __var___Block_936_32) , __var___Block_936_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_985_32(HoroEditor$__Closure_985_32 *  self, SuiCore$MouseEvent *  me){
	(*(self->__var___Block_936_32->reactMapSetting))((void * )(self->__var___Block_936_32->reactMapSetting)) ;
}

static void  __fini___Closure_985_32(HoroEditor$__Closure_985_32 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_985_32, __var___Block_936_32) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_985_32*  __make___Closure_985_32(HoroEditor$__Closure_985_32 **  __outRef__, HoroEditor$__Block_936_32 *  __var___Block_936_32){
	URGC_VAR_CLEANUP HoroEditor$__Closure_985_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_985_32) , __fini___Closure_985_32) ));
	self->invoke = __fn___Closure_985_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_985_32, __var___Block_936_32) , __var___Block_936_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_1104_26(HoroEditor$__Closure_1104_26 *  self, SuiCore$Event *  e){
	self->__var___Block_1072_21->self->onWindowEvent(self->__var___Block_1072_21->self, e) ;
}

static void  __fini___Closure_1104_26(HoroEditor$__Closure_1104_26 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_1104_26, __var___Block_1072_21) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_1104_26*  __make___Closure_1104_26(HoroEditor$__Closure_1104_26 **  __outRef__, HoroEditor$__Block_1072_21 *  __var___Block_1072_21){
	URGC_VAR_CLEANUP HoroEditor$__Closure_1104_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_1104_26) , __fini___Closure_1104_26) ));
	self->invoke = __fn___Closure_1104_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_1104_26, __var___Block_1072_21) , __var___Block_1072_21) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



