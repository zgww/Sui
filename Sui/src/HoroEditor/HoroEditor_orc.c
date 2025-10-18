
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
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"
#include "../SuiDesigner/MenuBarCtrl_orc.h"
#include "../SuiDesigner/ToolBase_orc.h"
#include "../SuiDesigner/SglGizmo_orc.h"
#include "../SuiDesigner/RegisterNodes_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Obj3d_orc.h"
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
#include "../Sgl/ModelLoader_orc.h"
#include "../SuiDesigner/MdxReader_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "../SuiDesigner/Project_orc.h"
#include "../SuiDesigner/SglInspectorView_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "./HoroSceneHierView_orc.h"
#include "./Horo3dSceneView_orc.h"
#include "./HoroEditCtx_orc.h"
#include "./HoroInspView_orc.h"
#include "./UiAct_orc.h"
#include "./Horo2dSceneView_orc.h"
#include "./HoroGeometryPreviewView_orc.h"
#include "./HoroIconMgr_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_264_51 HoroEditor$__Block_264_51;

typedef struct tagHoroEditor$__Block_347_30 HoroEditor$__Block_347_30;

typedef struct tagHoroEditor$__Block_350_27 HoroEditor$__Block_350_27;

typedef struct tagHoroEditor$__Block_403_35 HoroEditor$__Block_403_35;

typedef struct tagHoroEditor$__Block_419_33 HoroEditor$__Block_419_33;

typedef struct tagHoroEditor$__Block_758_21 HoroEditor$__Block_758_21;

typedef struct tagHoroEditor$__Closure_212_27 HoroEditor$__Closure_212_27;

typedef struct tagHoroEditor$__Closure_269_26 HoroEditor$__Closure_269_26;

typedef struct tagHoroEditor$__Closure_274_36 HoroEditor$__Closure_274_36;

typedef struct tagHoroEditor$__Closure_317_26 HoroEditor$__Closure_317_26;

typedef struct tagHoroEditor$__Closure_358_43 HoroEditor$__Closure_358_43;

typedef struct tagHoroEditor$__Closure_onActive_359 HoroEditor$__Closure_onActive_359;

typedef struct tagHoroEditor$__Closure_407_36 HoroEditor$__Closure_407_36;

typedef struct tagHoroEditor$__Closure_411_31 HoroEditor$__Closure_411_31;

typedef struct tagHoroEditor$__Closure_428_41 HoroEditor$__Closure_428_41;

typedef struct tagHoroEditor$__Closure_483_44 HoroEditor$__Closure_483_44;

typedef struct tagHoroEditor$__Closure_579_28 HoroEditor$__Closure_579_28;

typedef struct tagHoroEditor$__Closure_585_28 HoroEditor$__Closure_585_28;

typedef struct tagHoroEditor$__Closure_589_43 HoroEditor$__Closure_589_43;

typedef struct tagHoroEditor$__Closure_591_43 HoroEditor$__Closure_591_43;

typedef struct tagHoroEditor$__Closure_592_43 HoroEditor$__Closure_592_43;

typedef struct tagHoroEditor$__Closure_593_43 HoroEditor$__Closure_593_43;

typedef struct tagHoroEditor$__Closure_594_43 HoroEditor$__Closure_594_43;

typedef struct tagHoroEditor$__Closure_595_43 HoroEditor$__Closure_595_43;

typedef struct tagHoroEditor$__Closure_596_43 HoroEditor$__Closure_596_43;

typedef struct tagHoroEditor$__Closure_597_43 HoroEditor$__Closure_597_43;

typedef struct tagHoroEditor$__Closure_598_43 HoroEditor$__Closure_598_43;

typedef struct tagHoroEditor$__Closure_599_43 HoroEditor$__Closure_599_43;

typedef struct tagHoroEditor$__Closure_601_43 HoroEditor$__Closure_601_43;

typedef struct tagHoroEditor$__Closure_602_43 HoroEditor$__Closure_602_43;

typedef struct tagHoroEditor$__Closure_603_43 HoroEditor$__Closure_603_43;

typedef struct tagHoroEditor$__Closure_604_43 HoroEditor$__Closure_604_43;

typedef struct tagHoroEditor$__Closure_605_43 HoroEditor$__Closure_605_43;

typedef struct tagHoroEditor$__Closure_606_43 HoroEditor$__Closure_606_43;

typedef struct tagHoroEditor$__Closure_607_43 HoroEditor$__Closure_607_43;

typedef struct tagHoroEditor$__Closure_608_43 HoroEditor$__Closure_608_43;

typedef struct tagHoroEditor$__Closure_609_43 HoroEditor$__Closure_609_43;

typedef struct tagHoroEditor$__Closure_611_43 HoroEditor$__Closure_611_43;

typedef struct tagHoroEditor$__Closure_612_43 HoroEditor$__Closure_612_43;

typedef struct tagHoroEditor$__Closure_613_43 HoroEditor$__Closure_613_43;

typedef struct tagHoroEditor$__Closure_615_43 HoroEditor$__Closure_615_43;

typedef struct tagHoroEditor$__Closure_617_43 HoroEditor$__Closure_617_43;

typedef struct tagHoroEditor$__Closure_618_43 HoroEditor$__Closure_618_43;

typedef struct tagHoroEditor$__Closure_619_43 HoroEditor$__Closure_619_43;

typedef struct tagHoroEditor$__Closure_620_43 HoroEditor$__Closure_620_43;

typedef struct tagHoroEditor$__Closure_622_43 HoroEditor$__Closure_622_43;

typedef struct tagHoroEditor$__Closure_623_43 HoroEditor$__Closure_623_43;

typedef struct tagHoroEditor$__Closure_624_43 HoroEditor$__Closure_624_43;

typedef struct tagHoroEditor$__Closure_625_43 HoroEditor$__Closure_625_43;

typedef struct tagHoroEditor$__Closure_626_43 HoroEditor$__Closure_626_43;

typedef struct tagHoroEditor$__Closure_627_43 HoroEditor$__Closure_627_43;

typedef struct tagHoroEditor$__Closure_629_43 HoroEditor$__Closure_629_43;

typedef struct tagHoroEditor$__Closure_630_43 HoroEditor$__Closure_630_43;

typedef struct tagHoroEditor$__Closure_631_43 HoroEditor$__Closure_631_43;

typedef struct tagHoroEditor$__Closure_632_43 HoroEditor$__Closure_632_43;

typedef struct tagHoroEditor$__Closure_767_26 HoroEditor$__Closure_767_26;



struct tagHoroEditor$__Block_264_51 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_347_30 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_350_27 {
	SuiDesigner$MenuBarCtrl*  group ;
};





struct tagHoroEditor$__Block_403_35 {
	SuiView$MenuButton*  mbutton ;
};





struct tagHoroEditor$__Block_419_33 {
	SuiDesigner$Theme *  t ;
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_758_21 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Closure_212_27 {
	void  (*invoke)(HoroEditor$__Closure_212_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_269_26 {
	void  (*invoke)(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_264_51*  __var___Block_264_51 ;
};





struct tagHoroEditor$__Closure_274_36 {
	void  (*invoke)(HoroEditor$__Closure_274_36 *  self);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_264_51*  __var___Block_264_51 ;
};





struct tagHoroEditor$__Closure_317_26 {
	void  (*invoke)(HoroEditor$__Closure_317_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_358_43 {
	SuiView$MenuNativeItem*  (*invoke)(HoroEditor$__Closure_358_43 *  self, SuiView$MenuButton *  mbutton);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_347_30*  __var___Block_347_30 ;
};





struct tagHoroEditor$__Closure_onActive_359 {
	void  (*invoke)(HoroEditor$__Closure_onActive_359 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_347_30*  __var___Block_347_30 ;
};





struct tagHoroEditor$__Closure_407_36 {
	void  (*invoke)(HoroEditor$__Closure_407_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_350_27*  __var___Block_350_27 ;
	HoroEditor$__Block_403_35*  __var___Block_403_35 ;
};





struct tagHoroEditor$__Closure_411_31 {
	void  (*invoke)(HoroEditor$__Closure_411_31 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_350_27*  __var___Block_350_27 ;
	HoroEditor$__Block_403_35*  __var___Block_403_35 ;
};





struct tagHoroEditor$__Closure_428_41 {
	void  (*invoke)(HoroEditor$__Closure_428_41 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_419_33*  __var___Block_419_33 ;
};





struct tagHoroEditor$__Closure_483_44 {
	SuiCore$ViewBase *  (*invoke)(HoroEditor$__Closure_483_44 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_419_33*  __var___Block_419_33 ;
};





struct tagHoroEditor$__Closure_579_28 {
	void  (*invoke)(HoroEditor$__Closure_579_28 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_585_28 {
	void  (*invoke)(HoroEditor$__Closure_585_28 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_589_43 {
	void  (*invoke)(HoroEditor$__Closure_589_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_591_43 {
	void  (*invoke)(HoroEditor$__Closure_591_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_592_43 {
	void  (*invoke)(HoroEditor$__Closure_592_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_593_43 {
	void  (*invoke)(HoroEditor$__Closure_593_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_594_43 {
	void  (*invoke)(HoroEditor$__Closure_594_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_595_43 {
	void  (*invoke)(HoroEditor$__Closure_595_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_596_43 {
	void  (*invoke)(HoroEditor$__Closure_596_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_597_43 {
	void  (*invoke)(HoroEditor$__Closure_597_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_598_43 {
	void  (*invoke)(HoroEditor$__Closure_598_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_599_43 {
	void  (*invoke)(HoroEditor$__Closure_599_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_601_43 {
	void  (*invoke)(HoroEditor$__Closure_601_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_602_43 {
	void  (*invoke)(HoroEditor$__Closure_602_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_603_43 {
	void  (*invoke)(HoroEditor$__Closure_603_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_604_43 {
	void  (*invoke)(HoroEditor$__Closure_604_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_605_43 {
	void  (*invoke)(HoroEditor$__Closure_605_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_606_43 {
	void  (*invoke)(HoroEditor$__Closure_606_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_607_43 {
	void  (*invoke)(HoroEditor$__Closure_607_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_608_43 {
	void  (*invoke)(HoroEditor$__Closure_608_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_609_43 {
	void  (*invoke)(HoroEditor$__Closure_609_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_611_43 {
	void  (*invoke)(HoroEditor$__Closure_611_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_612_43 {
	void  (*invoke)(HoroEditor$__Closure_612_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_613_43 {
	void  (*invoke)(HoroEditor$__Closure_613_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_615_43 {
	void  (*invoke)(HoroEditor$__Closure_615_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_617_43 {
	void  (*invoke)(HoroEditor$__Closure_617_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_618_43 {
	void  (*invoke)(HoroEditor$__Closure_618_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_619_43 {
	void  (*invoke)(HoroEditor$__Closure_619_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_620_43 {
	void  (*invoke)(HoroEditor$__Closure_620_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_622_43 {
	void  (*invoke)(HoroEditor$__Closure_622_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_623_43 {
	void  (*invoke)(HoroEditor$__Closure_623_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_624_43 {
	void  (*invoke)(HoroEditor$__Closure_624_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_625_43 {
	void  (*invoke)(HoroEditor$__Closure_625_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_626_43 {
	void  (*invoke)(HoroEditor$__Closure_626_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_627_43 {
	void  (*invoke)(HoroEditor$__Closure_627_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_629_43 {
	void  (*invoke)(HoroEditor$__Closure_629_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_630_43 {
	void  (*invoke)(HoroEditor$__Closure_630_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_631_43 {
	void  (*invoke)(HoroEditor$__Closure_631_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_632_43 {
	void  (*invoke)(HoroEditor$__Closure_632_43 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_767_26 {
	void  (*invoke)(HoroEditor$__Closure_767_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_758_21*  __var___Block_758_21 ;
};





// static function declaration
static void  __finiBlock___Block_264_51(HoroEditor$__Block_264_51 *  self);
static void  __finiBlock___Block_347_30(HoroEditor$__Block_347_30 *  self);
static void  __finiBlock___Block_350_27(HoroEditor$__Block_350_27 *  self);
static void  __finiBlock___Block_403_35(HoroEditor$__Block_403_35 *  self);
static void  __finiBlock___Block_419_33(HoroEditor$__Block_419_33 *  self);
static void  __finiBlock___Block_758_21(HoroEditor$__Block_758_21 *  self);
static void  __fn___Closure_212_27(HoroEditor$__Closure_212_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_212_27(HoroEditor$__Closure_212_27 *  self);
static HoroEditor$__Closure_212_27*  __make___Closure_212_27(HoroEditor$__Closure_212_27 **  __outRef__);
static void  __fn___Closure_269_26(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_269_26(HoroEditor$__Closure_269_26 *  self);
static HoroEditor$__Closure_269_26*  __make___Closure_269_26(HoroEditor$__Closure_269_26 **  __outRef__, HoroEditor$__Block_264_51 *  __var___Block_264_51);
static void  __fn___Closure_274_36(HoroEditor$__Closure_274_36 *  self);
static void  __fini___Closure_274_36(HoroEditor$__Closure_274_36 *  self);
static HoroEditor$__Closure_274_36*  __make___Closure_274_36(HoroEditor$__Closure_274_36 **  __outRef__, HoroEditor$__Block_264_51 *  __var___Block_264_51);
static void  __fn___Closure_317_26(HoroEditor$__Closure_317_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_317_26(HoroEditor$__Closure_317_26 *  self);
static HoroEditor$__Closure_317_26*  __make___Closure_317_26(HoroEditor$__Closure_317_26 **  __outRef__);
static SuiView$MenuNativeItem*  __fn___Closure_358_43(SuiView$MenuNativeItem **  __outRef__, HoroEditor$__Closure_358_43 *  self, SuiView$MenuButton *  mbutton);
static void  __fini___Closure_358_43(HoroEditor$__Closure_358_43 *  self);
static HoroEditor$__Closure_358_43*  __make___Closure_358_43(HoroEditor$__Closure_358_43 **  __outRef__, HoroEditor$__Block_347_30 *  __var___Block_347_30);
static void  __fn___Closure_onActive_359(HoroEditor$__Closure_onActive_359 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_359(HoroEditor$__Closure_onActive_359 *  self);
static HoroEditor$__Closure_onActive_359*  __make___Closure_onActive_359(HoroEditor$__Closure_onActive_359 **  __outRef__, HoroEditor$__Block_347_30 *  __var___Block_347_30);
static void  __fn___Closure_407_36(HoroEditor$__Closure_407_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_407_36(HoroEditor$__Closure_407_36 *  self);
static HoroEditor$__Closure_407_36*  __make___Closure_407_36(HoroEditor$__Closure_407_36 **  __outRef__, HoroEditor$__Block_350_27 *  __var___Block_350_27, HoroEditor$__Block_403_35 *  __var___Block_403_35);
static void  __fn___Closure_411_31(HoroEditor$__Closure_411_31 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_411_31(HoroEditor$__Closure_411_31 *  self);
static HoroEditor$__Closure_411_31*  __make___Closure_411_31(HoroEditor$__Closure_411_31 **  __outRef__, HoroEditor$__Block_350_27 *  __var___Block_350_27, HoroEditor$__Block_403_35 *  __var___Block_403_35);
static void  __fn___Closure_428_41(HoroEditor$__Closure_428_41 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
static void  __fini___Closure_428_41(HoroEditor$__Closure_428_41 *  self);
static HoroEditor$__Closure_428_41*  __make___Closure_428_41(HoroEditor$__Closure_428_41 **  __outRef__, HoroEditor$__Block_419_33 *  __var___Block_419_33);
static SuiCore$ViewBase *  __fn___Closure_483_44(HoroEditor$__Closure_483_44 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
static void  __fini___Closure_483_44(HoroEditor$__Closure_483_44 *  self);
static HoroEditor$__Closure_483_44*  __make___Closure_483_44(HoroEditor$__Closure_483_44 **  __outRef__, HoroEditor$__Block_419_33 *  __var___Block_419_33);
static void  __fn___Closure_579_28(HoroEditor$__Closure_579_28 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_579_28(HoroEditor$__Closure_579_28 *  self);
static HoroEditor$__Closure_579_28*  __make___Closure_579_28(HoroEditor$__Closure_579_28 **  __outRef__);
static void  __fn___Closure_585_28(HoroEditor$__Closure_585_28 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_585_28(HoroEditor$__Closure_585_28 *  self);
static HoroEditor$__Closure_585_28*  __make___Closure_585_28(HoroEditor$__Closure_585_28 **  __outRef__);
static void  __fn___Closure_589_43(HoroEditor$__Closure_589_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_589_43(HoroEditor$__Closure_589_43 *  self);
static HoroEditor$__Closure_589_43*  __make___Closure_589_43(HoroEditor$__Closure_589_43 **  __outRef__);
static void  __fn___Closure_591_43(HoroEditor$__Closure_591_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_591_43(HoroEditor$__Closure_591_43 *  self);
static HoroEditor$__Closure_591_43*  __make___Closure_591_43(HoroEditor$__Closure_591_43 **  __outRef__);
static void  __fn___Closure_592_43(HoroEditor$__Closure_592_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_592_43(HoroEditor$__Closure_592_43 *  self);
static HoroEditor$__Closure_592_43*  __make___Closure_592_43(HoroEditor$__Closure_592_43 **  __outRef__);
static void  __fn___Closure_593_43(HoroEditor$__Closure_593_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_593_43(HoroEditor$__Closure_593_43 *  self);
static HoroEditor$__Closure_593_43*  __make___Closure_593_43(HoroEditor$__Closure_593_43 **  __outRef__);
static void  __fn___Closure_594_43(HoroEditor$__Closure_594_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_594_43(HoroEditor$__Closure_594_43 *  self);
static HoroEditor$__Closure_594_43*  __make___Closure_594_43(HoroEditor$__Closure_594_43 **  __outRef__);
static void  __fn___Closure_595_43(HoroEditor$__Closure_595_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_595_43(HoroEditor$__Closure_595_43 *  self);
static HoroEditor$__Closure_595_43*  __make___Closure_595_43(HoroEditor$__Closure_595_43 **  __outRef__);
static void  __fn___Closure_596_43(HoroEditor$__Closure_596_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_596_43(HoroEditor$__Closure_596_43 *  self);
static HoroEditor$__Closure_596_43*  __make___Closure_596_43(HoroEditor$__Closure_596_43 **  __outRef__);
static void  __fn___Closure_597_43(HoroEditor$__Closure_597_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_597_43(HoroEditor$__Closure_597_43 *  self);
static HoroEditor$__Closure_597_43*  __make___Closure_597_43(HoroEditor$__Closure_597_43 **  __outRef__);
static void  __fn___Closure_598_43(HoroEditor$__Closure_598_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_598_43(HoroEditor$__Closure_598_43 *  self);
static HoroEditor$__Closure_598_43*  __make___Closure_598_43(HoroEditor$__Closure_598_43 **  __outRef__);
static void  __fn___Closure_599_43(HoroEditor$__Closure_599_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_599_43(HoroEditor$__Closure_599_43 *  self);
static HoroEditor$__Closure_599_43*  __make___Closure_599_43(HoroEditor$__Closure_599_43 **  __outRef__);
static void  __fn___Closure_601_43(HoroEditor$__Closure_601_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_601_43(HoroEditor$__Closure_601_43 *  self);
static HoroEditor$__Closure_601_43*  __make___Closure_601_43(HoroEditor$__Closure_601_43 **  __outRef__);
static void  __fn___Closure_602_43(HoroEditor$__Closure_602_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_602_43(HoroEditor$__Closure_602_43 *  self);
static HoroEditor$__Closure_602_43*  __make___Closure_602_43(HoroEditor$__Closure_602_43 **  __outRef__);
static void  __fn___Closure_603_43(HoroEditor$__Closure_603_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_603_43(HoroEditor$__Closure_603_43 *  self);
static HoroEditor$__Closure_603_43*  __make___Closure_603_43(HoroEditor$__Closure_603_43 **  __outRef__);
static void  __fn___Closure_604_43(HoroEditor$__Closure_604_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_604_43(HoroEditor$__Closure_604_43 *  self);
static HoroEditor$__Closure_604_43*  __make___Closure_604_43(HoroEditor$__Closure_604_43 **  __outRef__);
static void  __fn___Closure_605_43(HoroEditor$__Closure_605_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_605_43(HoroEditor$__Closure_605_43 *  self);
static HoroEditor$__Closure_605_43*  __make___Closure_605_43(HoroEditor$__Closure_605_43 **  __outRef__);
static void  __fn___Closure_606_43(HoroEditor$__Closure_606_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_606_43(HoroEditor$__Closure_606_43 *  self);
static HoroEditor$__Closure_606_43*  __make___Closure_606_43(HoroEditor$__Closure_606_43 **  __outRef__);
static void  __fn___Closure_607_43(HoroEditor$__Closure_607_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_607_43(HoroEditor$__Closure_607_43 *  self);
static HoroEditor$__Closure_607_43*  __make___Closure_607_43(HoroEditor$__Closure_607_43 **  __outRef__);
static void  __fn___Closure_608_43(HoroEditor$__Closure_608_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_608_43(HoroEditor$__Closure_608_43 *  self);
static HoroEditor$__Closure_608_43*  __make___Closure_608_43(HoroEditor$__Closure_608_43 **  __outRef__);
static void  __fn___Closure_609_43(HoroEditor$__Closure_609_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_609_43(HoroEditor$__Closure_609_43 *  self);
static HoroEditor$__Closure_609_43*  __make___Closure_609_43(HoroEditor$__Closure_609_43 **  __outRef__);
static void  __fn___Closure_611_43(HoroEditor$__Closure_611_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_611_43(HoroEditor$__Closure_611_43 *  self);
static HoroEditor$__Closure_611_43*  __make___Closure_611_43(HoroEditor$__Closure_611_43 **  __outRef__);
static void  __fn___Closure_612_43(HoroEditor$__Closure_612_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_612_43(HoroEditor$__Closure_612_43 *  self);
static HoroEditor$__Closure_612_43*  __make___Closure_612_43(HoroEditor$__Closure_612_43 **  __outRef__);
static void  __fn___Closure_613_43(HoroEditor$__Closure_613_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_613_43(HoroEditor$__Closure_613_43 *  self);
static HoroEditor$__Closure_613_43*  __make___Closure_613_43(HoroEditor$__Closure_613_43 **  __outRef__);
static void  __fn___Closure_615_43(HoroEditor$__Closure_615_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_615_43(HoroEditor$__Closure_615_43 *  self);
static HoroEditor$__Closure_615_43*  __make___Closure_615_43(HoroEditor$__Closure_615_43 **  __outRef__);
static void  __fn___Closure_617_43(HoroEditor$__Closure_617_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_617_43(HoroEditor$__Closure_617_43 *  self);
static HoroEditor$__Closure_617_43*  __make___Closure_617_43(HoroEditor$__Closure_617_43 **  __outRef__);
static void  __fn___Closure_618_43(HoroEditor$__Closure_618_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_618_43(HoroEditor$__Closure_618_43 *  self);
static HoroEditor$__Closure_618_43*  __make___Closure_618_43(HoroEditor$__Closure_618_43 **  __outRef__);
static void  __fn___Closure_619_43(HoroEditor$__Closure_619_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_619_43(HoroEditor$__Closure_619_43 *  self);
static HoroEditor$__Closure_619_43*  __make___Closure_619_43(HoroEditor$__Closure_619_43 **  __outRef__);
static void  __fn___Closure_620_43(HoroEditor$__Closure_620_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_620_43(HoroEditor$__Closure_620_43 *  self);
static HoroEditor$__Closure_620_43*  __make___Closure_620_43(HoroEditor$__Closure_620_43 **  __outRef__);
static void  __fn___Closure_622_43(HoroEditor$__Closure_622_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_622_43(HoroEditor$__Closure_622_43 *  self);
static HoroEditor$__Closure_622_43*  __make___Closure_622_43(HoroEditor$__Closure_622_43 **  __outRef__);
static void  __fn___Closure_623_43(HoroEditor$__Closure_623_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_623_43(HoroEditor$__Closure_623_43 *  self);
static HoroEditor$__Closure_623_43*  __make___Closure_623_43(HoroEditor$__Closure_623_43 **  __outRef__);
static void  __fn___Closure_624_43(HoroEditor$__Closure_624_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_624_43(HoroEditor$__Closure_624_43 *  self);
static HoroEditor$__Closure_624_43*  __make___Closure_624_43(HoroEditor$__Closure_624_43 **  __outRef__);
static void  __fn___Closure_625_43(HoroEditor$__Closure_625_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_625_43(HoroEditor$__Closure_625_43 *  self);
static HoroEditor$__Closure_625_43*  __make___Closure_625_43(HoroEditor$__Closure_625_43 **  __outRef__);
static void  __fn___Closure_626_43(HoroEditor$__Closure_626_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_626_43(HoroEditor$__Closure_626_43 *  self);
static HoroEditor$__Closure_626_43*  __make___Closure_626_43(HoroEditor$__Closure_626_43 **  __outRef__);
static void  __fn___Closure_627_43(HoroEditor$__Closure_627_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_627_43(HoroEditor$__Closure_627_43 *  self);
static HoroEditor$__Closure_627_43*  __make___Closure_627_43(HoroEditor$__Closure_627_43 **  __outRef__);
static void  __fn___Closure_629_43(HoroEditor$__Closure_629_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_629_43(HoroEditor$__Closure_629_43 *  self);
static HoroEditor$__Closure_629_43*  __make___Closure_629_43(HoroEditor$__Closure_629_43 **  __outRef__);
static void  __fn___Closure_630_43(HoroEditor$__Closure_630_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_630_43(HoroEditor$__Closure_630_43 *  self);
static HoroEditor$__Closure_630_43*  __make___Closure_630_43(HoroEditor$__Closure_630_43 **  __outRef__);
static void  __fn___Closure_631_43(HoroEditor$__Closure_631_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_631_43(HoroEditor$__Closure_631_43 *  self);
static HoroEditor$__Closure_631_43*  __make___Closure_631_43(HoroEditor$__Closure_631_43 **  __outRef__);
static void  __fn___Closure_632_43(HoroEditor$__Closure_632_43 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_632_43(HoroEditor$__Closure_632_43 *  self);
static HoroEditor$__Closure_632_43*  __make___Closure_632_43(HoroEditor$__Closure_632_43 **  __outRef__);
static void  __fn___Closure_767_26(HoroEditor$__Closure_767_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_767_26(HoroEditor$__Closure_767_26 *  self);
static HoroEditor$__Closure_767_26*  __make___Closure_767_26(HoroEditor$__Closure_767_26 **  __outRef__, HoroEditor$__Block_758_21 *  __var___Block_758_21);


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
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditorSceneViewCallback*)self)->horoEditor);

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



static HoroEditor$HoroEditor *  horoEditor = NULL;
HoroEditor$HoroEditor *  HoroEditor$horoEditorIns(){
	return horoEditor; 
}


//vtable instance
Vtable_HoroEditor$HoroEditor _vtable_HoroEditor$HoroEditor;

// init meta

void HoroEditor$HoroEditor_initMeta(Vtable_HoroEditor$HoroEditor *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_HoroEditor$HoroEditCtx_init(0)), offsetof(HoroEditor$HoroEditor, editCtx), true, false, 1);
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(HoroEditor$HoroEditor, win), true, false, 1);
	orc_metaField_class(&pNext, "invalidReact", ((Vtable_Object*)Vtable_SuiDesigner$InvalidReact_init(0)), offsetof(HoroEditor$HoroEditor, invalidReact), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(HoroEditor$HoroEditor, drag), true, false, 1);
	orc_metaField_class(&pNext, "viewCb", ((Vtable_Object*)Vtable_HoroEditor$HoroEditorSceneViewCallback_init(0)), offsetof(HoroEditor$HoroEditor, viewCb), true, false, 1);
	orc_metaField_class(&pNext, "toolMgr", ((Vtable_Object*)Vtable_SuiDesigner$ToolMgr_init(0)), offsetof(HoroEditor$HoroEditor, toolMgr), true, false, 1);
	orc_metaField_class(&pNext, "sglGizmo", ((Vtable_Object*)Vtable_SuiDesigner$SglGizmo_init(0)), offsetof(HoroEditor$HoroEditor, sglGizmo), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_HoroEditor$Horo3dSceneView_init(0)), offsetof(HoroEditor$HoroEditor, sceneView), true, false, 1);
	orc_metaField_class(&pNext, "dirView", ((Vtable_Object*)Vtable_SuiDesigner$AssetDirView_init(0)), offsetof(HoroEditor$HoroEditor, dirView), true, false, 1);
	orc_metaField_class(&pNext, "gizmosView", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(HoroEditor$HoroEditor, gizmosView), true, false, 1);
	orc_metaField_class(&pNext, "outlineFx", ((Vtable_Object*)Vtable_Sgl$OutlineFx_init(0)), offsetof(HoroEditor$HoroEditor, outlineFx), true, false, 1);

	orc_metaField_method(&pNext, "selectByNode", offsetof(HoroEditor$HoroEditor, selectByNode));
	orc_metaField_method(&pNext, "onSceneEvent", offsetof(HoroEditor$HoroEditor, onSceneEvent));
	orc_metaField_method(&pNext, "_afterDrawScene", offsetof(HoroEditor$HoroEditor, _afterDrawScene));
	orc_metaField_method(&pNext, "reactScene_forViewBase", offsetof(HoroEditor$HoroEditor, reactScene_forViewBase));
	orc_metaField_method(&pNext, "reactScene_forObj3d", offsetof(HoroEditor$HoroEditor, reactScene_forObj3d));
	orc_metaField_method(&pNext, "reactScene", offsetof(HoroEditor$HoroEditor, reactScene));
	orc_metaField_method(&pNext, "reactGizmosView", offsetof(HoroEditor$HoroEditor, reactGizmosView));
	orc_metaField_method(&pNext, "reactMenubar", offsetof(HoroEditor$HoroEditor, reactMenubar));
	orc_metaField_method(&pNext, "reactDocklayout", offsetof(HoroEditor$HoroEditor, reactDocklayout));
	orc_metaField_method(&pNext, "reactToolbar", offsetof(HoroEditor$HoroEditor, reactToolbar));
	orc_metaField_method(&pNext, "react", offsetof(HoroEditor$HoroEditor, react));
	orc_metaField_method(&pNext, "onWindowEvent", offsetof(HoroEditor$HoroEditor, onWindowEvent));
	orc_metaField_method(&pNext, "showOutline", offsetof(HoroEditor$HoroEditor, showOutline));
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
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->editCtx);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->win);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->invalidReact);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->drag);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->viewCb);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->toolMgr);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->sglGizmo);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->sceneView);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->dirView);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->gizmosView);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->outlineFx);

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
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InvalidReact*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->invalidReact, SuiDesigner$mkInvalidReact(&tmpReturn_2, self) );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->drag, SuiView$Drag_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroEditorSceneViewCallback*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->viewCb, HoroEditor$HoroEditorSceneViewCallback_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ToolMgr*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->toolMgr, SuiDesigner$ToolMgr_new(&tmpNewOwner_5) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SglGizmo*  tmpNewOwner_6 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->sglGizmo, SuiDesigner$SglGizmo_new(&tmpNewOwner_6) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->sceneView, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->dirView, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->gizmosView, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$OutlineFx*  tmpNewOwner_7 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->outlineFx, Sgl$OutlineFx_new(&tmpNewOwner_7) );
    }
	((HoroEditor$HoroEditor*)self)->selectByNode = (void*)HoroEditor$HoroEditor$selectByNode;
	((HoroEditor$HoroEditor*)self)->onSceneEvent = (void*)HoroEditor$HoroEditor$onSceneEvent;
	((HoroEditor$HoroEditor*)self)->_afterDrawScene = (void*)HoroEditor$HoroEditor$_afterDrawScene;
	((Object*)self)->ctor = (void*)HoroEditor$HoroEditor$ctor;
	((Object*)self)->dtor = (void*)HoroEditor$HoroEditor$dtor;
	((SuiCore$Listener*)self)->onListenerEvent = (void*)HoroEditor$HoroEditor$onListenerEvent;
	((HoroEditor$HoroEditor*)self)->reactScene_forViewBase = (void*)HoroEditor$HoroEditor$reactScene_forViewBase;
	((HoroEditor$HoroEditor*)self)->reactScene_forObj3d = (void*)HoroEditor$HoroEditor$reactScene_forObj3d;
	((HoroEditor$HoroEditor*)self)->reactScene = (void*)HoroEditor$HoroEditor$reactScene;
	((HoroEditor$HoroEditor*)self)->reactGizmosView = (void*)HoroEditor$HoroEditor$reactGizmosView;
	((HoroEditor$HoroEditor*)self)->reactMenubar = (void*)HoroEditor$HoroEditor$reactMenubar;
	((HoroEditor$HoroEditor*)self)->reactDocklayout = (void*)HoroEditor$HoroEditor$reactDocklayout;
	((HoroEditor$HoroEditor*)self)->reactToolbar = (void*)HoroEditor$HoroEditor$reactToolbar;
	((HoroEditor$HoroEditor*)self)->react = (void*)HoroEditor$HoroEditor$react;
	((HoroEditor$HoroEditor*)self)->onWindowEvent = (void*)HoroEditor$HoroEditor$onWindowEvent;
	((HoroEditor$HoroEditor*)self)->showOutline = (void*)HoroEditor$HoroEditor$showOutline;
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
void  HoroEditor$HoroEditor$selectByNode(HoroEditor$HoroEditor *  self, SuiCore$Node *  n){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  vnode = self->editCtx->findANodeByNode((vnode = NULL,&vnode), self->editCtx, n) ;
	self->editCtx->state->setAncestorsOpen(self->editCtx->state, vnode) ;
	self->editCtx->state->setSelected(self->editCtx->state, vnode) ;
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
	SuiDesigner$ANode *  selANode = (SuiDesigner$ANode * )self->editCtx->state->getFirstSelected(self->editCtx->state) ;
	SuiCore$Node *  sel = selANode == NULL ? NULL : selANode->node;
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
	horoEditor = self;
	urgc_set_field_class(self->viewCb, (void * )offsetof(HoroEditor$HoroEditorSceneViewCallback, horoEditor) , self) ;
	urgc_set_field_class(self->toolMgr, (void * )offsetof(SuiDesigner$ToolMgr, editor) , self) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_212_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_212_27(&tmpReturn_1) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  projectDirPath = (projectDirPath=NULL,urgc_init_var_class((void**)&projectDirPath, Orc$String$add(Orc$Path_dirname(&tmpReturn_2, Orc$Path_getExecutionPath(&tmpReturn_3) ->str) , "/../asset/matl") ));
	printf("projectDirPath:%s\n", projectDirPath->str) ;
	SuiDesigner$Project *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_4 = NULL;
	(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_4) )->init(tmpThis_1, projectDirPath->str) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ToolDropModelLoader*  tmpNewOwner_5 = NULL;
	self->toolMgr->setTool(self->toolMgr, SuiDesigner$ToolDropModelLoader_new(&tmpNewOwner_5) ) ;
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
	else if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiDesigner$EventANodeChanged_init(NULL))) {
		SuiDesigner$EventANodeChanged *  e = (SuiDesigner$EventANodeChanged * )e;
		self->invalidReact->invalid(self->invalidReact) ;
	}
}


void  HoroEditor$HoroEditor$reactScene_forViewBase(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiDesigner$ANode *  anode){
	SuiCore$ViewBase *  root = (SuiCore$ViewBase * )anode->node;
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	URGC_VAR_CLEANUP_CLASS HoroEditor$Horo2dSceneView*  tmpReturn_1 = NULL;
	{
		HoroEditor$Horo2dSceneView*  __scopeVar_247_8 = HoroEditor$mkHoro2dSceneView(&tmpReturn_1, o, (long long )anode) , *o = __scopeVar_247_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_247_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(o, (void * )offsetof(HoroEditor$Horo2dSceneView, root) , anode) ;
		urgc_set_field_class(o, (void * )offsetof(HoroEditor$Horo2dSceneView, editor) , self) ;
		((SuiCore$View * )o)->backgroundColor = t->dock_content_bg;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_2 = NULL;
		{
			SuiLayout$LayoutAlignPositionCell*  __scopeVar_252_12 = SuiLayout$layoutAlignPositionCell(&tmpReturn_2, o, 0) , *o = __scopeVar_252_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_252_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->left = 0;
			o->top = 0;
			o->right = 0;
			o->bottom = 0;
		}
	}
}


void  HoroEditor$HoroEditor$reactScene_forObj3d(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiDesigner$ANode *  anode){
	URGC_VAR_CLEANUP HoroEditor$__Block_264_51*  __var___Block_264_51 = (__var___Block_264_51=NULL,urgc_init_var((void**)&__var___Block_264_51, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_264_51) , __finiBlock___Block_264_51) ));
	urgc_set_field_class(__var___Block_264_51, (void * )offsetof(HoroEditor$__Block_264_51, self) , self) ;
	Sgl$Obj3d *  root = (Sgl$Obj3d * )anode->node;
	URGC_VAR_CLEANUP_CLASS HoroEditor$Horo3dSceneView*  tmpReturn_1 = NULL;
	{
		HoroEditor$Horo3dSceneView*  __scopeVar_266_8 = HoroEditor$mkHoro3dSceneView(&tmpReturn_1, o, 0) , *o = __scopeVar_266_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_266_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(o, (void * )offsetof(HoroEditor$Horo3dSceneView, editor) , self) ;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->viewCb) ;
		URGC_VAR_CLEANUP HoroEditor$__Closure_269_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_269_26(&tmpReturn_2, __var___Block_264_51) ) ;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, sceneView) , o) ;
		URGC_VAR_CLEANUP HoroEditor$__Closure_274_36*  tmpReturn_3 = NULL;
		urgc_set_field(o->drawCtx, (void * )offsetof(Sgl$DrawCtx, cbAfterDraw) , __make___Closure_274_36(&tmpReturn_3, __var___Block_264_51) ) ;
		((SuiCore$View * )o)->backgroundColor = 0x00ffffff;
		((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
		if (((SuiCore$Node * )o)->isNewForReact) {
			o->mkBaseScene(o) ;
			self->editCtx->setSceneView(self->editCtx, o) ;
			SuiCore$Emitter *  tmpThis_1 = NULL;
			URGC_VAR_CLEANUP_CLASS HoroEditor$EventHoroSceneChanged*  tmpNewOwner_4 = NULL;
			(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, HoroEditor$EventHoroSceneChanged_new(&tmpNewOwner_4) ) ;
		}
		{
			Sgl$Scene*  __scopeVar_288_12 = o->scene, *o = __scopeVar_288_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_288_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			SuiCore$Node$placeKid((SuiCore$Node * )o, root) ;
		}
		((SuiCore$View * )o)->width = 500;
		((SuiCore$View * )o)->height = 500;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_5 = NULL;
		{
			SuiLayout$LayoutAlignPositionCell*  __scopeVar_296_12 = SuiLayout$layoutAlignPositionCell(&tmpReturn_5, o, 0) , *o = __scopeVar_296_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_296_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->left = 0;
			o->top = 0;
			o->right = 0;
			o->bottom = 0;
		}
		URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_6 = NULL;
		{
			SuiCore$View*  __scopeVar_302_12 = SuiView$mkView(&tmpReturn_6, o, 0) , *o = __scopeVar_302_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_302_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, gizmosView) , o) ;
		}
	}
}


SuiCore$ViewBase *  HoroEditor$HoroEditor$reactScene(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_311_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_311_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_311_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = 0xffefefef;
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		URGC_VAR_CLEANUP HoroEditor$__Closure_317_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_317_26(&tmpReturn_2) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) ;
		{
			URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  root = self->editCtx->getRoot((root = NULL,&root), self->editCtx) ;
			if (root) {
				if (Orc_instanceof((Object*)root->node, (Vtable_Object*)Vtable_SuiCore$ViewBase_init(NULL))) {
					self->reactScene_forViewBase(self, o, root) ;
				}
				else if (Orc_instanceof((Object*)root->node, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
					self->reactScene_forObj3d(self, o, root) ;
				}
			}
		}
		return o; 
	}
}


void  HoroEditor$HoroEditor$reactGizmosView(HoroEditor$HoroEditor *  self){
	{
		SuiCore$View*  o = self->gizmosView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_341_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(self->toolMgr, (void * )offsetof(SuiDesigner$ToolMgr, drawCtx) , self->sceneView->drawCtx) ;
		self->toolMgr->reactGizmosView(self->toolMgr, self->gizmosView) ;
	}
}


void  HoroEditor$HoroEditor$reactMenubar(HoroEditor$HoroEditor *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP HoroEditor$__Block_347_30*  __var___Block_347_30 = (__var___Block_347_30=NULL,urgc_init_var((void**)&__var___Block_347_30, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_347_30) , __finiBlock___Block_347_30) ));
	urgc_set_field_class(__var___Block_347_30, (void * )offsetof(HoroEditor$__Block_347_30, self) , self) ;
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_350_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_350_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_350_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP HoroEditor$__Block_350_27*  __var___Block_350_27 = (__var___Block_350_27=NULL,urgc_init_var((void**)&__var___Block_350_27, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_350_27) , __finiBlock___Block_350_27) ));
		((SuiCore$View * )o)->backgroundColor = t->menubar_bg;
		SuiCore$Inset$setAxis(&((SuiCore$View * )o)->padding, 0, 6) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  btnsStr = Orc$str((btnsStr = NULL,&btnsStr), "文件,项目,视图,调试,窗口,帮助") ;
		URGC_VAR_CLEANUP_CLASS Orc$List*  btns = Orc$String$splitByRe((btns = NULL,&btns), btnsStr, ",") ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$MenuBarCtrl*  tmpNewOwner_2 = NULL;
		urgc_set_field_class(__var___Block_350_27, (void * )offsetof(HoroEditor$__Block_350_27, group) , SuiDesigner$MenuBarCtrl_new(&tmpNewOwner_2) ) ;
		URGC_VAR_CLEANUP HoroEditor$__Closure_358_43*  tmpReturn_3 = NULL;
		urgc_set_field(__var___Block_350_27->group, (void * )offsetof(SuiDesigner$MenuBarCtrl, cbCreateMenuNativeItem) , __make___Closure_358_43(&tmpReturn_3, __var___Block_347_30) ) ;
		for (int  i = 0; i < btns->size(btns) ; i++) {
			Object *  obj = btns->get(btns, i) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  btn = (btn=NULL,urgc_init_var_class((void**)&btn, (Orc$String* )btns->get(btns, i) ));
			URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  tmpReturn_4 = NULL;
			{
				SuiView$MenuButton*  __scopeVar_403_16 = SuiView$mkMenuButton(&tmpReturn_4, o, i) , *o = __scopeVar_403_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_403_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP HoroEditor$__Block_403_35*  __var___Block_403_35 = (__var___Block_403_35=NULL,urgc_init_var((void**)&__var___Block_403_35, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_403_35) , __finiBlock___Block_403_35) ));
				urgc_set_field_class(__var___Block_403_35, (void * )offsetof(HoroEditor$__Block_403_35, mbutton) , o) ;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuButton, text) , btn) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_407_36*  tmpReturn_5 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onMouseMove) , __make___Closure_407_36(&tmpReturn_5, __var___Block_350_27, __var___Block_403_35) ) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_411_31*  tmpReturn_6 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onClick) , __make___Closure_411_31(&tmpReturn_6, __var___Block_350_27, __var___Block_403_35) ) ;
			}
		}
	}
}


void  HoroEditor$HoroEditor$reactDocklayout(HoroEditor$HoroEditor *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP HoroEditor$__Block_419_33*  __var___Block_419_33 = (__var___Block_419_33=NULL,urgc_init_var((void**)&__var___Block_419_33, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_419_33) , __finiBlock___Block_419_33) ));
	urgc_set_field_class(__var___Block_419_33, (void * )offsetof(HoroEditor$__Block_419_33, self) , self) ;
	__var___Block_419_33->t = SuiDesigner$themeIns() ;
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpReturn_1 = NULL;
	{
		SuiView$DockLayout*  __scopeVar_421_8 = SuiView$dockLayout(&tmpReturn_1, o, 0) , *o = __scopeVar_421_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_421_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_var_class(&dockLayoutIns, o) ;
		((SuiCore$View * )o)->width = 100;
		((SuiCore$View * )o)->height = 20;
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP HoroEditor$__Closure_428_41*  tmpReturn_2 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemHeadView) , __make___Closure_428_41(&tmpReturn_2, __var___Block_419_33) ) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_483_44*  tmpReturn_3 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemContentView) , __make___Closure_483_44(&tmpReturn_3, __var___Block_419_33) ) ;
			{
				SuiView$DockItem*  __scopeVar_542_16 = o->root, *o = __scopeVar_542_16;
				
			
				o->isHorizontal = false;
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_4 = NULL;
				{
					SuiView$DockItem*  __scopeVar_545_20 = SuiView$mkDockItemSplitter(&tmpReturn_4, o, NULL, true) , *o = __scopeVar_545_20;
					
				
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_5 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
					{
						SuiView$DockItem*  __scopeVar_546_24 = SuiView$mkDockItem(&tmpReturn_5, o, Orc$str(&tmpReturn_6, "hierarchy") ) , *o = __scopeVar_546_24;
						
					
						o->intId = 0;
						o->width = 200;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_7 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
					{
						SuiView$DockItem*  __scopeVar_550_24 = SuiView$mkDockItem(&tmpReturn_7, o, Orc$str(&tmpReturn_8, "scene") ) , *o = __scopeVar_550_24;
						
					
						o->intId = 0;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_9 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					{
						SuiView$DockItem*  __scopeVar_553_24 = SuiView$mkDockItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "inspector") ) , *o = __scopeVar_553_24;
						
					
						o->intId = 0;
						o->width = 250;
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_11 = NULL;
				{
					SuiView$DockItem*  __scopeVar_558_20 = SuiView$mkDockItemSplitter(&tmpReturn_11, o, NULL, true) , *o = __scopeVar_558_20;
					
				
					o->width = 150;
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_12 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
					{
						SuiView$DockItem*  __scopeVar_560_24 = SuiView$mkDockItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "project") ) , *o = __scopeVar_560_24;
						
					
						o->intId = 0;
						o->width = 160;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_14 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
					{
						SuiView$DockItem*  __scopeVar_564_24 = SuiView$mkDockItem(&tmpReturn_14, o, Orc$str(&tmpReturn_15, "dir") ) , *o = __scopeVar_564_24;
						
					
						o->intId = 0;
					}
				}
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_16 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_16, o, 0) ;
	}
}


void  HoroEditor$HoroEditor$reactToolbar(HoroEditor$HoroEditor *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_575_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_575_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_575_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_2 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_576_12 = SuiView$mkDrawButton(&tmpReturn_2, o, 0) , *o = __scopeVar_576_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_576_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->typePrimary(o) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_3, "Download") ) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_579_28*  tmpReturn_4 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_579_28(&tmpReturn_4) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_5 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_583_12 = SuiView$mkDrawButton(&tmpReturn_5, o, 0) , *o = __scopeVar_583_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_583_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_6, "添加tilelayer") ) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_585_28*  tmpReturn_7 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_585_28(&tmpReturn_7) ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_8 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_589_12 = SuiView$mkDrawButton(&tmpReturn_8, o, 0) , *o = __scopeVar_589_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_589_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_589_43*  tmpReturn_9 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_589_43(&tmpReturn_9) ) ;
			o->isActive = true;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_10, "../asset/icon-light/setting.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_11 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_591_12 = SuiView$mkDrawButton(&tmpReturn_11, o, 0) , *o = __scopeVar_591_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_591_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_591_43*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_591_43(&tmpReturn_12) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_13, "../asset/icon-light/project.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_14 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_592_12 = SuiView$mkDrawButton(&tmpReturn_14, o, 0) , *o = __scopeVar_592_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_592_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_592_43*  tmpReturn_15 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_592_43(&tmpReturn_15) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_16, "../asset/icon-light/open-door.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_17 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_593_12 = SuiView$mkDrawButton(&tmpReturn_17, o, 0) , *o = __scopeVar_593_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_593_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_593_43*  tmpReturn_18 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_593_43(&tmpReturn_18) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_19 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_19, "../asset/icon-light/collapse.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_20 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_594_12 = SuiView$mkDrawButton(&tmpReturn_20, o, 0) , *o = __scopeVar_594_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_594_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_594_43*  tmpReturn_21 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_594_43(&tmpReturn_21) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_22, "../asset/icon-light/expand.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_23 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_595_12 = SuiView$mkDrawButton(&tmpReturn_23, o, 0) , *o = __scopeVar_595_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_595_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_595_43*  tmpReturn_24 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_595_43(&tmpReturn_24) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_25 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_25, "../asset/icon-light/add.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_26 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_596_12 = SuiView$mkDrawButton(&tmpReturn_26, o, 0) , *o = __scopeVar_596_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_596_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_596_43*  tmpReturn_27 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_596_43(&tmpReturn_27) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_28, "../asset/icon-light/delete.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_29 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_597_12 = SuiView$mkDrawButton(&tmpReturn_29, o, 0) , *o = __scopeVar_597_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_597_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_597_43*  tmpReturn_30 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_597_43(&tmpReturn_30) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_31 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_31, "../asset/icon-light/bezier.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_32 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_598_12 = SuiView$mkDrawButton(&tmpReturn_32, o, 0) , *o = __scopeVar_598_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_598_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_598_43*  tmpReturn_33 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_598_43(&tmpReturn_33) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_34 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_34, "../asset/icon-light/user.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_35 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_599_12 = SuiView$mkDrawButton(&tmpReturn_35, o, 0) , *o = __scopeVar_599_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_599_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_599_43*  tmpReturn_36 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_599_43(&tmpReturn_36) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_37 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_37, "../asset/icon-light/shortcut.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_38 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_601_12 = SuiView$mkDrawButton(&tmpReturn_38, o, 0) , *o = __scopeVar_601_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_601_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_601_43*  tmpReturn_39 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_601_43(&tmpReturn_39) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_40 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_40, "../asset/icon-light/file-open.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_41 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_602_12 = SuiView$mkDrawButton(&tmpReturn_41, o, 0) , *o = __scopeVar_602_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_602_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_602_43*  tmpReturn_42 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_602_43(&tmpReturn_42) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_43 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_43, "../asset/icon-light/save.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_44 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_603_12 = SuiView$mkDrawButton(&tmpReturn_44, o, 0) , *o = __scopeVar_603_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_603_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_603_43*  tmpReturn_45 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_603_43(&tmpReturn_45) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_46 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_46, "../asset/icon-light/print.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_47 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_604_12 = SuiView$mkDrawButton(&tmpReturn_47, o, 0) , *o = __scopeVar_604_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_604_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_604_43*  tmpReturn_48 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_604_43(&tmpReturn_48) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_49 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_49, "../asset/icon-light/play.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_50 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_605_12 = SuiView$mkDrawButton(&tmpReturn_50, o, 0) , *o = __scopeVar_605_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_605_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_605_43*  tmpReturn_51 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_605_43(&tmpReturn_51) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_52 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_52, "../asset/icon-light/pause.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_53 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_606_12 = SuiView$mkDrawButton(&tmpReturn_53, o, 0) , *o = __scopeVar_606_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_606_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_606_43*  tmpReturn_54 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_606_43(&tmpReturn_54) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_55 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_55, "../asset/icon-light/apps.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_56 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_607_12 = SuiView$mkDrawButton(&tmpReturn_56, o, 0) , *o = __scopeVar_607_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_607_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_607_43*  tmpReturn_57 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_607_43(&tmpReturn_57) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_58 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_58, "../asset/icon-light/align-left.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_59 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_608_12 = SuiView$mkDrawButton(&tmpReturn_59, o, 0) , *o = __scopeVar_608_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_608_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_608_43*  tmpReturn_60 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_608_43(&tmpReturn_60) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_61 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_61, "../asset/icon-light/align-center.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_62 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_609_12 = SuiView$mkDrawButton(&tmpReturn_62, o, 0) , *o = __scopeVar_609_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_609_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_609_43*  tmpReturn_63 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_609_43(&tmpReturn_63) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_64 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_64, "../asset/icon-light/align-right.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_65 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_611_12 = SuiView$mkDrawButton(&tmpReturn_65, o, 0) , *o = __scopeVar_611_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_611_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_611_43*  tmpReturn_66 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_611_43(&tmpReturn_66) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_67 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_67, "../asset/icon-light/align-top.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_68 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_612_12 = SuiView$mkDrawButton(&tmpReturn_68, o, 0) , *o = __scopeVar_612_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_612_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_612_43*  tmpReturn_69 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_612_43(&tmpReturn_69) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_70 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_70, "../asset/icon-light/align-middle.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_71 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_613_12 = SuiView$mkDrawButton(&tmpReturn_71, o, 0) , *o = __scopeVar_613_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_613_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_613_43*  tmpReturn_72 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_613_43(&tmpReturn_72) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_73 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_73, "../asset/icon-light/align-bottom.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_74 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_615_12 = SuiView$mkDrawButton(&tmpReturn_74, o, 0) , *o = __scopeVar_615_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_615_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_615_43*  tmpReturn_75 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_615_43(&tmpReturn_75) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_76 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_76, "../asset/icon-light/download.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_77 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_617_12 = SuiView$mkDrawButton(&tmpReturn_77, o, 0) , *o = __scopeVar_617_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_617_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_617_43*  tmpReturn_78 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_617_43(&tmpReturn_78) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_79 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_79, "../asset/icon-light/sort-a-to-z.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_80 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_618_12 = SuiView$mkDrawButton(&tmpReturn_80, o, 0) , *o = __scopeVar_618_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_618_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_618_43*  tmpReturn_81 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_618_43(&tmpReturn_81) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_82 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_82, "../asset/icon-light/sort-z-to-a.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_83 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_619_12 = SuiView$mkDrawButton(&tmpReturn_83, o, 0) , *o = __scopeVar_619_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_619_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_619_43*  tmpReturn_84 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_619_43(&tmpReturn_84) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_85 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_85, "../asset/icon-light/filter.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_86 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_620_12 = SuiView$mkDrawButton(&tmpReturn_86, o, 0) , *o = __scopeVar_620_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_620_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_620_43*  tmpReturn_87 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_620_43(&tmpReturn_87) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_88 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_88, "../asset/icon-light/search.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_89 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_622_12 = SuiView$mkDrawButton(&tmpReturn_89, o, 0) , *o = __scopeVar_622_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_622_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_622_43*  tmpReturn_90 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_622_43(&tmpReturn_90) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_91 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_91, "../asset/icon-light/node.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_92 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_623_12 = SuiView$mkDrawButton(&tmpReturn_92, o, 0) , *o = __scopeVar_623_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_623_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_623_43*  tmpReturn_93 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_623_43(&tmpReturn_93) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_94 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_94, "../asset/icon-light/cube.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_95 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_624_12 = SuiView$mkDrawButton(&tmpReturn_95, o, 0) , *o = __scopeVar_624_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_624_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_624_43*  tmpReturn_96 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_624_43(&tmpReturn_96) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_97 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_97, "../asset/icon-light/text-view.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_98 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_625_12 = SuiView$mkDrawButton(&tmpReturn_98, o, 0) , *o = __scopeVar_625_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_625_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_625_43*  tmpReturn_99 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_625_43(&tmpReturn_99) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_100 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_100, "../asset/icon-light/edit-text.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_101 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_626_12 = SuiView$mkDrawButton(&tmpReturn_101, o, 0) , *o = __scopeVar_626_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_626_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_626_43*  tmpReturn_102 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_626_43(&tmpReturn_102) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_103 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_103, "../asset/icon-light/image-view.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_104 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_627_12 = SuiView$mkDrawButton(&tmpReturn_104, o, 0) , *o = __scopeVar_627_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_627_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_627_43*  tmpReturn_105 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_627_43(&tmpReturn_105) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_106 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_106, "../asset/icon-light/button.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_107 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_629_12 = SuiView$mkDrawButton(&tmpReturn_107, o, 0) , *o = __scopeVar_629_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_629_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_629_43*  tmpReturn_108 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_629_43(&tmpReturn_108) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_109 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_109, "../asset/icon-light/directory.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_110 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_630_12 = SuiView$mkDrawButton(&tmpReturn_110, o, 0) , *o = __scopeVar_630_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_630_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_630_43*  tmpReturn_111 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_630_43(&tmpReturn_111) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_112 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_112, "../asset/icon-light/camera.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_113 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_631_12 = SuiView$mkDrawButton(&tmpReturn_113, o, 0) , *o = __scopeVar_631_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_631_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_631_43*  tmpReturn_114 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_631_43(&tmpReturn_114) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_115 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_115, "../asset/icon-light/light.png") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_116 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_632_12 = SuiView$mkDrawButton(&tmpReturn_116, o, 0) , *o = __scopeVar_632_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_632_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP HoroEditor$__Closure_632_43*  tmpReturn_117 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_632_43(&tmpReturn_117) ) ;
			o->normalBg = 0;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_118 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_118, "../asset/icon-light/path.png") ) ;
		}
	}
}


void  HoroEditor$HoroEditor$react(HoroEditor$HoroEditor *  self){
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_641_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		self->reactMenubar(self, o) ;
		self->reactToolbar(self, o) ;
		self->reactDocklayout(self, o) ;
	}
}


void  HoroEditor$HoroEditor$onWindowEvent(HoroEditor$HoroEditor *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$KeyEvent_init(NULL))) {
		SuiCore$KeyEvent *  ke = (SuiCore$KeyEvent * )e;
		printf("2窗口收到键盘消息:%s\n", ke->key->str) ;
		if (self->sceneView && self->sceneView->camera && ke->isKeyDown) {
			if (ke->ctrl) {
				if (Orc$String$equalsIgnoreCase(ke->key, "S") ) {
					HoroEditor$UiAct_savePrefab(self) ;
				}
			}
			else if (ke->shift) {
				if (Orc$String$equalsIgnoreCase(ke->key, "A") ) {
					printf("左旋转\n") ;
					((Sgl$Obj3d * )self->sceneView->camera)->rotation.y += 0.01;
				}
				else if (Orc$String$equalsIgnoreCase(ke->key, "D") ) {
					printf("右旋转\n") ;
					((Sgl$Obj3d * )self->sceneView->camera)->rotation.y -= 0.01;
				}
				else if (Orc$String$equalsIgnoreCase(ke->key, "W") ) {
					printf("左旋转\n") ;
					((Sgl$Obj3d * )self->sceneView->camera)->rotation.x -= 0.01;
				}
				else if (Orc$String$equalsIgnoreCase(ke->key, "S") ) {
					printf("右旋转\n") ;
					((Sgl$Obj3d * )self->sceneView->camera)->rotation.x += 0.01;
				}
			}
			else if (Orc$String$equals(ke->key, "W") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->sceneView->camera, SuiCore$mkVec3(0, 0, -1.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_1, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->sceneView->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "S") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->sceneView->camera, SuiCore$mkVec3(0, 0, 1.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_2, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->sceneView->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "A") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->sceneView->camera, SuiCore$mkVec3(-1, 0, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_3, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->sceneView->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "D") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->sceneView->camera, SuiCore$mkVec3(1, 0, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_4, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->sceneView->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "E") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->sceneView->camera, SuiCore$mkVec3(0, 1, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_5, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->sceneView->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "Q") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->sceneView->camera, SuiCore$mkVec3(0, -1, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_6, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->sceneView->camera)->position, dir) ;
			}
		}
	}
}


void  HoroEditor$HoroEditor$showOutline(HoroEditor$HoroEditor *  self){
	{
		Sgl$DrawCtx*  o = self->sceneView->drawCtx;
		
	
		SuiDesigner$ANode *  selANode = (SuiDesigner$ANode * )self->editCtx->state->getFirstSelected(self->editCtx->state) ;
		SuiCore$Node *  sel = selANode == NULL ? NULL : selANode->node;
		if (Orc_instanceof((Object*)sel, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
			self->outlineFx->updateFbo(self->outlineFx, o->frameSize) ;
			self->outlineFx->drawMask(self->outlineFx, o, (Sgl$Obj3d * )sel) ;
			self->outlineFx->fboEdge->startDraw(self->outlineFx->fboEdge, 0, 0, 0, 0, true, true, true) ;
			self->outlineFx->drawFxQuad(self->outlineFx) ;
			self->outlineFx->fboEdge->endDraw(self->outlineFx->fboEdge) ;
			Sgl$SglSceneView_showTextureWindow(self->outlineFx->fbo->tex2d, SuiCore$Vec2$width(&o->frameSize) , SuiCore$Vec2$height(&o->frameSize) ) ;
			Sgl$SglSceneView_showTextureWindow(self->outlineFx->fboEdge->tex2d, SuiCore$Vec2$width(&o->frameSize) , SuiCore$Vec2$height(&o->frameSize) ) ;
		}
		else {
			SuiDialog$Toast_make("当前未选中Obj3d") ;
		}
	}
}


void  HoroEditor$HoroEditor$showWindow(HoroEditor$HoroEditor *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_758_21*  __var___Block_758_21 = (__var___Block_758_21=NULL,urgc_init_var((void**)&__var___Block_758_21, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_758_21) , __finiBlock___Block_758_21) ));
	urgc_set_field_class(__var___Block_758_21, (void * )offsetof(HoroEditor$__Block_758_21, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, win) , Sui$Window_new(&tmpNewOwner_1) ) ;
	self->outlineFx->init(self->outlineFx) ;
	{
		Sui$Window*  o = self->win;
		
	
		URGC_VAR_CLEANUP HoroEditor$__Closure_767_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_767_26(&tmpReturn_2, __var___Block_758_21) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_3 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_3) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_771_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = SuiDesigner$themeIns() ->bg1;
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
	SuiDesigner$registerNodes() ;
	Orc$Path_setcwd(path) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  abspath = Orc$Path_toAbsolute((abspath = NULL,&abspath), path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  cwd = Orc$Path_getcwd((cwd = NULL,&cwd)) ;
	printf("打开项目。 项目路径为:%s. cwd:%s", abspath->str, cwd->str) ;
	SuiDesigner$Project *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_1) )->init(tmpThis_1, abspath->str) ;
	self->editCtx->openPrefab(self->editCtx, "prefab/3d.prefab.json") ;
	self->showWindow(self) ;
	win->close(win) ;
}



static void  __finiBlock___Block_264_51(HoroEditor$__Block_264_51 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_264_51, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_347_30(HoroEditor$__Block_347_30 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_347_30, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_350_27(HoroEditor$__Block_350_27 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_350_27, group) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_403_35(HoroEditor$__Block_403_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_403_35, mbutton) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_419_33(HoroEditor$__Block_419_33 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_419_33, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_758_21(HoroEditor$__Block_758_21 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_758_21, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_212_27(HoroEditor$__Closure_212_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("isDragging tileset\n") ;
	}
}

static void  __fini___Closure_212_27(HoroEditor$__Closure_212_27 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_212_27*  __make___Closure_212_27(HoroEditor$__Closure_212_27 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_212_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_212_27) , __fini___Closure_212_27) ));
	self->invoke = __fn___Closure_212_27;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_269_26(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e){
	self->__var___Block_264_51->self->onSceneEvent(self->__var___Block_264_51->self, e) ;
}

static void  __fini___Closure_269_26(HoroEditor$__Closure_269_26 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_269_26, __var___Block_264_51) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_269_26*  __make___Closure_269_26(HoroEditor$__Closure_269_26 **  __outRef__, HoroEditor$__Block_264_51 *  __var___Block_264_51){
	URGC_VAR_CLEANUP HoroEditor$__Closure_269_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_269_26) , __fini___Closure_269_26) ));
	self->invoke = __fn___Closure_269_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_269_26, __var___Block_264_51) , __var___Block_264_51) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_274_36(HoroEditor$__Closure_274_36 *  self){
	self->__var___Block_264_51->self->_afterDrawScene(self->__var___Block_264_51->self) ;
}

static void  __fini___Closure_274_36(HoroEditor$__Closure_274_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_274_36, __var___Block_264_51) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_274_36*  __make___Closure_274_36(HoroEditor$__Closure_274_36 **  __outRef__, HoroEditor$__Block_264_51 *  __var___Block_264_51){
	URGC_VAR_CLEANUP HoroEditor$__Closure_274_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_274_36) , __fini___Closure_274_36) ));
	self->invoke = __fn___Closure_274_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_274_36, __var___Block_264_51) , __var___Block_264_51) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_317_26(HoroEditor$__Closure_317_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	}
}

static void  __fini___Closure_317_26(HoroEditor$__Closure_317_26 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_317_26*  __make___Closure_317_26(HoroEditor$__Closure_317_26 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_317_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_317_26) , __fini___Closure_317_26) ));
	self->invoke = __fn___Closure_317_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiView$MenuNativeItem*  __fn___Closure_358_43(SuiView$MenuNativeItem **  __outRef__, HoroEditor$__Closure_358_43 *  self, SuiView$MenuButton *  mbutton){
	URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_359*  tmpReturn_1 = NULL;
	(urgc_set_var(&onActive, __make___Closure_onActive_359(&tmpReturn_1, self->__var___Block_347_30) ) );
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
				SuiView$MenuNativeItem*  __scopeVar_378_24 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "最近打开") , onActive) , *o = __scopeVar_378_24;
				
			
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

static void  __fini___Closure_358_43(HoroEditor$__Closure_358_43 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_358_43, __var___Block_347_30) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_358_43*  __make___Closure_358_43(HoroEditor$__Closure_358_43 **  __outRef__, HoroEditor$__Block_347_30 *  __var___Block_347_30){
	URGC_VAR_CLEANUP HoroEditor$__Closure_358_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_358_43) , __fini___Closure_358_43) ));
	self->invoke = __fn___Closure_358_43;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_358_43, __var___Block_347_30) , __var___Block_347_30) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_359(HoroEditor$__Closure_onActive_359 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu:%s\n", item->label->str) ;
	if (Orc$String$equals(item->label, "退出") ) {
		exit(0) ;
	}
	if (Orc$String$equals(item->label, "Outline") ) {
		self->__var___Block_347_30->self->showOutline(self->__var___Block_347_30->self) ;
	}
	if (Orc$String$equals(item->label, "保存场景") ) {
		HoroEditor$UiAct_savePrefab(self->__var___Block_347_30->self) ;
		return ; 
	}
	SuiDialog$Toast_make(item->label->str) ;
}

static void  __fini___Closure_onActive_359(HoroEditor$__Closure_onActive_359 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_359, __var___Block_347_30) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_onActive_359*  __make___Closure_onActive_359(HoroEditor$__Closure_onActive_359 **  __outRef__, HoroEditor$__Block_347_30 *  __var___Block_347_30){
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_359*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_onActive_359) , __fini___Closure_onActive_359) ));
	self->invoke = __fn___Closure_onActive_359;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_359, __var___Block_347_30) , __var___Block_347_30) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_407_36(HoroEditor$__Closure_407_36 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_350_27->group->onmove(self->__var___Block_350_27->group, self->__var___Block_403_35->mbutton, me) ;
}

static void  __fini___Closure_407_36(HoroEditor$__Closure_407_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_407_36, __var___Block_350_27) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_407_36, __var___Block_403_35) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_407_36*  __make___Closure_407_36(HoroEditor$__Closure_407_36 **  __outRef__, HoroEditor$__Block_350_27 *  __var___Block_350_27, HoroEditor$__Block_403_35 *  __var___Block_403_35){
	URGC_VAR_CLEANUP HoroEditor$__Closure_407_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_407_36) , __fini___Closure_407_36) ));
	self->invoke = __fn___Closure_407_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_407_36, __var___Block_350_27) , __var___Block_350_27) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_407_36, __var___Block_403_35) , __var___Block_403_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_411_31(HoroEditor$__Closure_411_31 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_350_27->group->onclick(self->__var___Block_350_27->group, self->__var___Block_403_35->mbutton, me) ;
}

static void  __fini___Closure_411_31(HoroEditor$__Closure_411_31 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_411_31, __var___Block_350_27) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_411_31, __var___Block_403_35) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_411_31*  __make___Closure_411_31(HoroEditor$__Closure_411_31 **  __outRef__, HoroEditor$__Block_350_27 *  __var___Block_350_27, HoroEditor$__Block_403_35 *  __var___Block_403_35){
	URGC_VAR_CLEANUP HoroEditor$__Closure_411_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_411_31) , __fini___Closure_411_31) ));
	self->invoke = __fn___Closure_411_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_411_31, __var___Block_350_27) , __var___Block_350_27) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_411_31, __var___Block_403_35) , __var___Block_403_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_428_41(HoroEditor$__Closure_428_41 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex){
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpItem = (tmpItem=NULL,urgc_init_var_class((void**)&tmpItem, item));
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpDock = (tmpDock=NULL,urgc_init_var_class((void**)&tmpDock, dockLayoutIns));
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_433_20 = SuiLayout$layoutLinear(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_433_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_433_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 0.0f, 0xffaeaeb2) ;
		bool  active = item->parent->tabActiveIndex == kidIndex;
		if (active) {
			((SuiCore$View * )o)->border->t->w = 1.f;
			((SuiCore$View * )o)->border->t->color = self->__var___Block_419_33->t->c_main;
		}
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->padding, 6) ;
		SuiCore$Inset$setVer(&((SuiCore$View * )o)->padding, 2) ;
		((SuiCore$View * )o)->backgroundColor = active ? self->__var___Block_419_33->t->dock_head_bg_active : self->__var___Block_419_33->t->dock_head_bg;
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_2 = NULL;
		{
			SuiView$ImageView*  __scopeVar_448_24 = SuiView$mkImageView(&tmpReturn_2, o, ((long long )item) + 1) , *o = __scopeVar_448_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_448_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->width = 14;
			((SuiCore$View * )o)->height = 14;
			o->setImageMode(o, SuiView$Fill) ;
			((SuiCore$View * )o)->margin.right = 4;
			if (Orc$String$equals(item->id, "hierarchy") ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				o->setSrc(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_3, "../asset/icon-light/hierarchy.png") ) ;
			}
			else if (Orc$String$equals(item->id, "scene") ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				o->setSrc(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_4, "../asset/icon-light/scene.png") ) ;
			}
			else if (Orc$String$equals(item->id, "inspector") ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				o->setSrc(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_5, "../asset/icon-light/inspector.png") ) ;
			}
			else {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
				o->setSrc(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_6, "../asset/icon-light/directory.png") ) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
		{
			SuiView$TextView*  __scopeVar_466_24 = SuiView$mkTextView(&tmpReturn_7, o, (long long )item) , *o = __scopeVar_466_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_466_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_8, "pointer") ) ;
			o->setText(o, item->id) ;
			o->color = self->__var___Block_419_33->t->dock_head_c;
			o->setFont_size(o, 11) ;
			if (kidIndex < item->parent->children->size(item->parent->children)  - 1) {
				
			}
		}
	}
}

static void  __fini___Closure_428_41(HoroEditor$__Closure_428_41 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_428_41, __var___Block_419_33) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_428_41*  __make___Closure_428_41(HoroEditor$__Closure_428_41 **  __outRef__, HoroEditor$__Block_419_33 *  __var___Block_419_33){
	URGC_VAR_CLEANUP HoroEditor$__Closure_428_41*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_428_41) , __fini___Closure_428_41) ));
	self->invoke = __fn___Closure_428_41;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_428_41, __var___Block_419_33) , __var___Block_419_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$ViewBase *  __fn___Closure_483_44(HoroEditor$__Closure_483_44 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o){
	if (Orc$String$equals(item->id, "project") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirTreeView*  tmpReturn_1 = NULL;
		{
			SuiDesigner$AssetDirTreeView*  __scopeVar_485_24 = SuiDesigner$mkAssetDirTreeView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_485_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_485_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_419_33->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "dir") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirView*  tmpReturn_2 = NULL;
		{
			SuiDesigner$AssetDirView*  __scopeVar_491_24 = SuiDesigner$mkAssetDirView(&tmpReturn_2, o, (long long )item) , *o = __scopeVar_491_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_491_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(self->__var___Block_419_33->self, (void * )offsetof(HoroEditor$HoroEditor, dirView) , o) ;
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_419_33->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "hierarchy") ) {
		URGC_VAR_CLEANUP_CLASS HoroEditor$HoroSceneHierView*  tmpReturn_3 = NULL;
		{
			HoroEditor$HoroSceneHierView*  __scopeVar_498_24 = HoroEditor$mkHoroSceneHierView(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_498_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_498_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(o, (void * )offsetof(HoroEditor$HoroSceneHierView, editCtx) , self->__var___Block_419_33->self->editCtx) ;
			urgc_set_field_class(o, (void * )offsetof(HoroEditor$HoroSceneHierView, editor) , self->__var___Block_419_33->self) ;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "inspector") ) {
		URGC_VAR_CLEANUP_CLASS HoroEditor$HoroInspView*  tmpReturn_4 = NULL;
		{
			HoroEditor$HoroInspView*  __scopeVar_507_24 = HoroEditor$mkHoroInspView(&tmpReturn_4, o, (long long )item) , *o = __scopeVar_507_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_507_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(o, (void * )offsetof(HoroEditor$HoroInspView, editCtx) , self->__var___Block_419_33->self->editCtx) ;
			urgc_set_field_class(o, (void * )offsetof(HoroEditor$HoroInspView, editor) , self->__var___Block_419_33->self) ;
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_419_33->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "scene") ) {
		return self->__var___Block_419_33->self->reactScene(self->__var___Block_419_33->self, o, item) ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_5 = NULL;
	{
		SuiView$TextView*  __scopeVar_518_20 = SuiView$mkTextView(&tmpReturn_5, o, (long long )item) , *o = __scopeVar_518_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_518_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
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
			SuiLayout$LayoutLinearCell*  __scopeVar_534_24 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_534_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_534_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		return o; 
	}
}

static void  __fini___Closure_483_44(HoroEditor$__Closure_483_44 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_483_44, __var___Block_419_33) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_483_44*  __make___Closure_483_44(HoroEditor$__Closure_483_44 **  __outRef__, HoroEditor$__Block_419_33 *  __var___Block_419_33){
	URGC_VAR_CLEANUP HoroEditor$__Closure_483_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_483_44) , __fini___Closure_483_44) ));
	self->invoke = __fn___Closure_483_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_483_44, __var___Block_419_33) , __var___Block_419_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_579_28(HoroEditor$__Closure_579_28 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_579_28(HoroEditor$__Closure_579_28 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_579_28*  __make___Closure_579_28(HoroEditor$__Closure_579_28 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_579_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_579_28) , __fini___Closure_579_28) ));
	self->invoke = __fn___Closure_579_28;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_585_28(HoroEditor$__Closure_585_28 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_585_28(HoroEditor$__Closure_585_28 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_585_28*  __make___Closure_585_28(HoroEditor$__Closure_585_28 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_585_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_585_28) , __fini___Closure_585_28) ));
	self->invoke = __fn___Closure_585_28;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_589_43(HoroEditor$__Closure_589_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi1") ;
}

static void  __fini___Closure_589_43(HoroEditor$__Closure_589_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_589_43*  __make___Closure_589_43(HoroEditor$__Closure_589_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_589_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_589_43) , __fini___Closure_589_43) ));
	self->invoke = __fn___Closure_589_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_591_43(HoroEditor$__Closure_591_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_591_43(HoroEditor$__Closure_591_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_591_43*  __make___Closure_591_43(HoroEditor$__Closure_591_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_591_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_591_43) , __fini___Closure_591_43) ));
	self->invoke = __fn___Closure_591_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_592_43(HoroEditor$__Closure_592_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_592_43(HoroEditor$__Closure_592_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_592_43*  __make___Closure_592_43(HoroEditor$__Closure_592_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_592_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_592_43) , __fini___Closure_592_43) ));
	self->invoke = __fn___Closure_592_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_593_43(HoroEditor$__Closure_593_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_593_43(HoroEditor$__Closure_593_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_593_43*  __make___Closure_593_43(HoroEditor$__Closure_593_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_593_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_593_43) , __fini___Closure_593_43) ));
	self->invoke = __fn___Closure_593_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_594_43(HoroEditor$__Closure_594_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_594_43(HoroEditor$__Closure_594_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_594_43*  __make___Closure_594_43(HoroEditor$__Closure_594_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_594_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_594_43) , __fini___Closure_594_43) ));
	self->invoke = __fn___Closure_594_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_595_43(HoroEditor$__Closure_595_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_595_43(HoroEditor$__Closure_595_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_595_43*  __make___Closure_595_43(HoroEditor$__Closure_595_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_595_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_595_43) , __fini___Closure_595_43) ));
	self->invoke = __fn___Closure_595_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_596_43(HoroEditor$__Closure_596_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_596_43(HoroEditor$__Closure_596_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_596_43*  __make___Closure_596_43(HoroEditor$__Closure_596_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_596_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_596_43) , __fini___Closure_596_43) ));
	self->invoke = __fn___Closure_596_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_597_43(HoroEditor$__Closure_597_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_597_43(HoroEditor$__Closure_597_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_597_43*  __make___Closure_597_43(HoroEditor$__Closure_597_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_597_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_597_43) , __fini___Closure_597_43) ));
	self->invoke = __fn___Closure_597_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_598_43(HoroEditor$__Closure_598_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_598_43(HoroEditor$__Closure_598_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_598_43*  __make___Closure_598_43(HoroEditor$__Closure_598_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_598_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_598_43) , __fini___Closure_598_43) ));
	self->invoke = __fn___Closure_598_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_599_43(HoroEditor$__Closure_599_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_599_43(HoroEditor$__Closure_599_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_599_43*  __make___Closure_599_43(HoroEditor$__Closure_599_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_599_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_599_43) , __fini___Closure_599_43) ));
	self->invoke = __fn___Closure_599_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_601_43(HoroEditor$__Closure_601_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_601_43(HoroEditor$__Closure_601_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_601_43*  __make___Closure_601_43(HoroEditor$__Closure_601_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_601_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_601_43) , __fini___Closure_601_43) ));
	self->invoke = __fn___Closure_601_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_602_43(HoroEditor$__Closure_602_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_602_43(HoroEditor$__Closure_602_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_602_43*  __make___Closure_602_43(HoroEditor$__Closure_602_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_602_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_602_43) , __fini___Closure_602_43) ));
	self->invoke = __fn___Closure_602_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_603_43(HoroEditor$__Closure_603_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_603_43(HoroEditor$__Closure_603_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_603_43*  __make___Closure_603_43(HoroEditor$__Closure_603_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_603_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_603_43) , __fini___Closure_603_43) ));
	self->invoke = __fn___Closure_603_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_604_43(HoroEditor$__Closure_604_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_604_43(HoroEditor$__Closure_604_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_604_43*  __make___Closure_604_43(HoroEditor$__Closure_604_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_604_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_604_43) , __fini___Closure_604_43) ));
	self->invoke = __fn___Closure_604_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_605_43(HoroEditor$__Closure_605_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_605_43(HoroEditor$__Closure_605_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_605_43*  __make___Closure_605_43(HoroEditor$__Closure_605_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_605_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_605_43) , __fini___Closure_605_43) ));
	self->invoke = __fn___Closure_605_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_606_43(HoroEditor$__Closure_606_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_606_43(HoroEditor$__Closure_606_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_606_43*  __make___Closure_606_43(HoroEditor$__Closure_606_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_606_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_606_43) , __fini___Closure_606_43) ));
	self->invoke = __fn___Closure_606_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_607_43(HoroEditor$__Closure_607_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_607_43(HoroEditor$__Closure_607_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_607_43*  __make___Closure_607_43(HoroEditor$__Closure_607_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_607_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_607_43) , __fini___Closure_607_43) ));
	self->invoke = __fn___Closure_607_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_608_43(HoroEditor$__Closure_608_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_608_43(HoroEditor$__Closure_608_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_608_43*  __make___Closure_608_43(HoroEditor$__Closure_608_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_608_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_608_43) , __fini___Closure_608_43) ));
	self->invoke = __fn___Closure_608_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_609_43(HoroEditor$__Closure_609_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_609_43(HoroEditor$__Closure_609_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_609_43*  __make___Closure_609_43(HoroEditor$__Closure_609_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_609_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_609_43) , __fini___Closure_609_43) ));
	self->invoke = __fn___Closure_609_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_611_43(HoroEditor$__Closure_611_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_611_43(HoroEditor$__Closure_611_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_611_43*  __make___Closure_611_43(HoroEditor$__Closure_611_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_611_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_611_43) , __fini___Closure_611_43) ));
	self->invoke = __fn___Closure_611_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_612_43(HoroEditor$__Closure_612_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_612_43(HoroEditor$__Closure_612_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_612_43*  __make___Closure_612_43(HoroEditor$__Closure_612_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_612_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_612_43) , __fini___Closure_612_43) ));
	self->invoke = __fn___Closure_612_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_613_43(HoroEditor$__Closure_613_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_613_43(HoroEditor$__Closure_613_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_613_43*  __make___Closure_613_43(HoroEditor$__Closure_613_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_613_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_613_43) , __fini___Closure_613_43) ));
	self->invoke = __fn___Closure_613_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_615_43(HoroEditor$__Closure_615_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_615_43(HoroEditor$__Closure_615_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_615_43*  __make___Closure_615_43(HoroEditor$__Closure_615_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_615_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_615_43) , __fini___Closure_615_43) ));
	self->invoke = __fn___Closure_615_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_617_43(HoroEditor$__Closure_617_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_617_43(HoroEditor$__Closure_617_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_617_43*  __make___Closure_617_43(HoroEditor$__Closure_617_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_617_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_617_43) , __fini___Closure_617_43) ));
	self->invoke = __fn___Closure_617_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_618_43(HoroEditor$__Closure_618_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_618_43(HoroEditor$__Closure_618_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_618_43*  __make___Closure_618_43(HoroEditor$__Closure_618_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_618_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_618_43) , __fini___Closure_618_43) ));
	self->invoke = __fn___Closure_618_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_619_43(HoroEditor$__Closure_619_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_619_43(HoroEditor$__Closure_619_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_619_43*  __make___Closure_619_43(HoroEditor$__Closure_619_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_619_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_619_43) , __fini___Closure_619_43) ));
	self->invoke = __fn___Closure_619_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_620_43(HoroEditor$__Closure_620_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_620_43(HoroEditor$__Closure_620_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_620_43*  __make___Closure_620_43(HoroEditor$__Closure_620_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_620_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_620_43) , __fini___Closure_620_43) ));
	self->invoke = __fn___Closure_620_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_622_43(HoroEditor$__Closure_622_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_622_43(HoroEditor$__Closure_622_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_622_43*  __make___Closure_622_43(HoroEditor$__Closure_622_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_622_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_622_43) , __fini___Closure_622_43) ));
	self->invoke = __fn___Closure_622_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_623_43(HoroEditor$__Closure_623_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_623_43(HoroEditor$__Closure_623_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_623_43*  __make___Closure_623_43(HoroEditor$__Closure_623_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_623_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_623_43) , __fini___Closure_623_43) ));
	self->invoke = __fn___Closure_623_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_624_43(HoroEditor$__Closure_624_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_624_43(HoroEditor$__Closure_624_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_624_43*  __make___Closure_624_43(HoroEditor$__Closure_624_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_624_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_624_43) , __fini___Closure_624_43) ));
	self->invoke = __fn___Closure_624_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_625_43(HoroEditor$__Closure_625_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_625_43(HoroEditor$__Closure_625_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_625_43*  __make___Closure_625_43(HoroEditor$__Closure_625_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_625_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_625_43) , __fini___Closure_625_43) ));
	self->invoke = __fn___Closure_625_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_626_43(HoroEditor$__Closure_626_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_626_43(HoroEditor$__Closure_626_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_626_43*  __make___Closure_626_43(HoroEditor$__Closure_626_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_626_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_626_43) , __fini___Closure_626_43) ));
	self->invoke = __fn___Closure_626_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_627_43(HoroEditor$__Closure_627_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_627_43(HoroEditor$__Closure_627_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_627_43*  __make___Closure_627_43(HoroEditor$__Closure_627_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_627_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_627_43) , __fini___Closure_627_43) ));
	self->invoke = __fn___Closure_627_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_629_43(HoroEditor$__Closure_629_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_629_43(HoroEditor$__Closure_629_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_629_43*  __make___Closure_629_43(HoroEditor$__Closure_629_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_629_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_629_43) , __fini___Closure_629_43) ));
	self->invoke = __fn___Closure_629_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_630_43(HoroEditor$__Closure_630_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_630_43(HoroEditor$__Closure_630_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_630_43*  __make___Closure_630_43(HoroEditor$__Closure_630_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_630_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_630_43) , __fini___Closure_630_43) ));
	self->invoke = __fn___Closure_630_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_631_43(HoroEditor$__Closure_631_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_631_43(HoroEditor$__Closure_631_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_631_43*  __make___Closure_631_43(HoroEditor$__Closure_631_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_631_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_631_43) , __fini___Closure_631_43) ));
	self->invoke = __fn___Closure_631_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_632_43(HoroEditor$__Closure_632_43 *  self, SuiCore$MouseEvent *  e){
	SuiDialog$Toast_make("hi") ;
}

static void  __fini___Closure_632_43(HoroEditor$__Closure_632_43 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_632_43*  __make___Closure_632_43(HoroEditor$__Closure_632_43 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_632_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_632_43) , __fini___Closure_632_43) ));
	self->invoke = __fn___Closure_632_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_767_26(HoroEditor$__Closure_767_26 *  self, SuiCore$Event *  e){
	self->__var___Block_758_21->self->onWindowEvent(self->__var___Block_758_21->self, e) ;
}

static void  __fini___Closure_767_26(HoroEditor$__Closure_767_26 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_767_26, __var___Block_758_21) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_767_26*  __make___Closure_767_26(HoroEditor$__Closure_767_26 **  __outRef__, HoroEditor$__Block_758_21 *  __var___Block_758_21){
	URGC_VAR_CLEANUP HoroEditor$__Closure_767_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_767_26) , __fini___Closure_767_26) ));
	self->invoke = __fn___Closure_767_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_767_26, __var___Block_758_21) , __var___Block_758_21) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



