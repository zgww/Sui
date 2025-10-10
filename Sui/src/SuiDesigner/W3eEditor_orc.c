
#include "W3eEditor_orc.h" 

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
#include "./ChessBgViewCallback_orc.h"
#include "./Theme_orc.h"
#include "./W3e_orc.h"
#include "./InvalidReact_orc.h"
#include "./MenuBarCtrl_orc.h"
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
#include "../Sgl/GeometryRing_orc.h"
#include "../Sgl/GeometryCylinder_orc.h"
#include "../Sgl/GeometryCone_orc.h"
#include "../Sgl/GeometryArrow_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/Skybox_orc.h"
#include "./MdxReader_orc.h"
#include "./SglSceneHierView_orc.h"
#include "./SglEditCtx_orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "./Project_orc.h"
#include "./SglInspectorView_orc.h"
#include "./SglInspView_orc.h"


// static struct 
typedef struct tagSuiDesigner3d$__Block_146_33 SuiDesigner3d$__Block_146_33;

typedef struct tagSuiDesigner3d$__Block_243_47 SuiDesigner3d$__Block_243_47;

typedef struct tagSuiDesigner3d$__Block_523_16 SuiDesigner3d$__Block_523_16;

typedef struct tagSuiDesigner3d$__Block_529_35 SuiDesigner3d$__Block_529_35;

typedef struct tagSuiDesigner3d$__Block_577_43 SuiDesigner3d$__Block_577_43;

typedef struct tagSuiDesigner3d$__Block_858_32 SuiDesigner3d$__Block_858_32;

typedef struct tagSuiDesigner3d$__Block_962_21 SuiDesigner3d$__Block_962_21;

typedef struct tagSuiDesigner3d$__Closure_110_27 SuiDesigner3d$__Closure_110_27;

typedef struct tagSuiDesigner3d$__Closure_134_26 SuiDesigner3d$__Closure_134_26;

typedef struct tagSuiDesigner3d$__Closure_148_42 SuiDesigner3d$__Closure_148_42;

typedef struct tagSuiDesigner3d$__Closure_182_26 SuiDesigner3d$__Closure_182_26;

typedef struct tagSuiDesigner3d$__Closure_379_44 SuiDesigner3d$__Closure_379_44;

typedef struct tagSuiDesigner3d$__Closure_537_51 SuiDesigner3d$__Closure_537_51;

typedef struct tagSuiDesigner3d$__Closure_onActive_538 SuiDesigner3d$__Closure_onActive_538;

typedef struct tagSuiDesigner3d$__Closure_581_44 SuiDesigner3d$__Closure_581_44;

typedef struct tagSuiDesigner3d$__Closure_585_39 SuiDesigner3d$__Closure_585_39;

typedef struct tagSuiDesigner3d$__Closure_595_36 SuiDesigner3d$__Closure_595_36;

typedef struct tagSuiDesigner3d$__Closure_602_36 SuiDesigner3d$__Closure_602_36;

typedef struct tagSuiDesigner3d$__Closure_608_36 SuiDesigner3d$__Closure_608_36;

typedef struct tagSuiDesigner3d$__Closure_615_36 SuiDesigner3d$__Closure_615_36;

typedef struct tagSuiDesigner3d$__Closure_623_36 SuiDesigner3d$__Closure_623_36;

typedef struct tagSuiDesigner3d$__Closure_631_36 SuiDesigner3d$__Closure_631_36;

typedef struct tagSuiDesigner3d$__Closure_638_36 SuiDesigner3d$__Closure_638_36;

typedef struct tagSuiDesigner3d$__Closure_644_36 SuiDesigner3d$__Closure_644_36;

typedef struct tagSuiDesigner3d$__Closure_657_36 SuiDesigner3d$__Closure_657_36;

typedef struct tagSuiDesigner3d$__Closure_672_36 SuiDesigner3d$__Closure_672_36;

typedef struct tagSuiDesigner3d$__Closure_699_49 SuiDesigner3d$__Closure_699_49;

typedef struct tagSuiDesigner3d$__Closure_732_52 SuiDesigner3d$__Closure_732_52;

typedef struct tagSuiDesigner3d$__Closure_862_35 SuiDesigner3d$__Closure_862_35;

typedef struct tagSuiDesigner3d$__Closure_907_32 SuiDesigner3d$__Closure_907_32;

typedef struct tagSuiDesigner3d$__Closure_983_26 SuiDesigner3d$__Closure_983_26;



struct tagSuiDesigner3d$__Block_146_33 {
	SuiDesigner3d$W3eEditor*  self ;
};





struct tagSuiDesigner3d$__Block_243_47 {
	Sgl$Mesh*  m ;
};





struct tagSuiDesigner3d$__Block_523_16 {
	SuiDesigner3d$W3eEditor*  self ;
	SuiDesigner$Theme *  t ;
};





struct tagSuiDesigner3d$__Block_529_35 {
	SuiDesigner$MenuBarCtrl*  group ;
};





struct tagSuiDesigner3d$__Block_577_43 {
	SuiView$MenuButton*  mbutton ;
};





struct tagSuiDesigner3d$__Block_858_32 {
	Sui$Window*  win ;
	void  (**reactMapSetting)(void *  self);
};





struct tagSuiDesigner3d$__Block_962_21 {
	SuiDesigner3d$W3eEditor*  self ;
};





struct tagSuiDesigner3d$__Closure_110_27 {
	void  (*invoke)(SuiDesigner3d$__Closure_110_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_134_26 {
	void  (*invoke)(SuiDesigner3d$__Closure_134_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_148_42 {
	void  (*invoke)(SuiDesigner3d$__Closure_148_42 *  self, Orc$String*  newValue);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_146_33*  __var___Block_146_33 ;
};





struct tagSuiDesigner3d$__Closure_182_26 {
	void  (*invoke)(SuiDesigner3d$__Closure_182_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_379_44 {
	void  (*invoke)(SuiDesigner3d$__Closure_379_44 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_243_47*  __var___Block_243_47 ;
};





struct tagSuiDesigner3d$__Closure_537_51 {
	SuiView$MenuNativeItem*  (*invoke)(SuiDesigner3d$__Closure_537_51 *  self, SuiView$MenuButton *  mbutton);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_523_16*  __var___Block_523_16 ;
};





struct tagSuiDesigner3d$__Closure_onActive_538 {
	void  (*invoke)(SuiDesigner3d$__Closure_onActive_538 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_523_16*  __var___Block_523_16 ;
};





struct tagSuiDesigner3d$__Closure_581_44 {
	void  (*invoke)(SuiDesigner3d$__Closure_581_44 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_529_35*  __var___Block_529_35 ;
	SuiDesigner3d$__Block_577_43*  __var___Block_577_43 ;
};





struct tagSuiDesigner3d$__Closure_585_39 {
	void  (*invoke)(SuiDesigner3d$__Closure_585_39 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_529_35*  __var___Block_529_35 ;
	SuiDesigner3d$__Block_577_43*  __var___Block_577_43 ;
};





struct tagSuiDesigner3d$__Closure_595_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_595_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_602_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_602_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_608_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_608_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_615_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_615_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_623_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_623_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_631_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_631_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_638_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_638_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_523_16*  __var___Block_523_16 ;
};





struct tagSuiDesigner3d$__Closure_644_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_644_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_657_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_657_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_523_16*  __var___Block_523_16 ;
};





struct tagSuiDesigner3d$__Closure_672_36 {
	void  (*invoke)(SuiDesigner3d$__Closure_672_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner3d$__Closure_699_49 {
	void  (*invoke)(SuiDesigner3d$__Closure_699_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_523_16*  __var___Block_523_16 ;
};





struct tagSuiDesigner3d$__Closure_732_52 {
	SuiCore$ViewBase *  (*invoke)(SuiDesigner3d$__Closure_732_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_523_16*  __var___Block_523_16 ;
};





struct tagSuiDesigner3d$__Closure_862_35 {
	void  (*invoke)(SuiDesigner3d$__Closure_862_35 *  self);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_858_32*  __var___Block_858_32 ;
};





struct tagSuiDesigner3d$__Closure_907_32 {
	void  (*invoke)(SuiDesigner3d$__Closure_907_32 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_858_32*  __var___Block_858_32 ;
};





struct tagSuiDesigner3d$__Closure_983_26 {
	void  (*invoke)(SuiDesigner3d$__Closure_983_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner3d$__Block_962_21*  __var___Block_962_21 ;
};





// static function declaration
static void  __finiBlock___Block_146_33(SuiDesigner3d$__Block_146_33 *  self);
static void  __finiBlock___Block_243_47(SuiDesigner3d$__Block_243_47 *  self);
static void  __finiBlock___Block_523_16(SuiDesigner3d$__Block_523_16 *  self);
static void  __finiBlock___Block_529_35(SuiDesigner3d$__Block_529_35 *  self);
static void  __finiBlock___Block_577_43(SuiDesigner3d$__Block_577_43 *  self);
static void  __finiBlock___Block_858_32(SuiDesigner3d$__Block_858_32 *  self);
static void  __finiBlock___Block_962_21(SuiDesigner3d$__Block_962_21 *  self);
static void  __fn___Closure_110_27(SuiDesigner3d$__Closure_110_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_110_27(SuiDesigner3d$__Closure_110_27 *  self);
static SuiDesigner3d$__Closure_110_27*  __make___Closure_110_27(SuiDesigner3d$__Closure_110_27 **  __outRef__);
static void  __fn___Closure_134_26(SuiDesigner3d$__Closure_134_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_134_26(SuiDesigner3d$__Closure_134_26 *  self);
static SuiDesigner3d$__Closure_134_26*  __make___Closure_134_26(SuiDesigner3d$__Closure_134_26 **  __outRef__);
static void  __fn___Closure_148_42(SuiDesigner3d$__Closure_148_42 *  self, Orc$String*  newValue);
static void  __fini___Closure_148_42(SuiDesigner3d$__Closure_148_42 *  self);
static SuiDesigner3d$__Closure_148_42*  __make___Closure_148_42(SuiDesigner3d$__Closure_148_42 **  __outRef__, SuiDesigner3d$__Block_146_33 *  __var___Block_146_33);
static void  __fn___Closure_182_26(SuiDesigner3d$__Closure_182_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_182_26(SuiDesigner3d$__Closure_182_26 *  self);
static SuiDesigner3d$__Closure_182_26*  __make___Closure_182_26(SuiDesigner3d$__Closure_182_26 **  __outRef__);
static void  __fn___Closure_379_44(SuiDesigner3d$__Closure_379_44 *  self, SuiView$Drag *  d);
static void  __fini___Closure_379_44(SuiDesigner3d$__Closure_379_44 *  self);
static SuiDesigner3d$__Closure_379_44*  __make___Closure_379_44(SuiDesigner3d$__Closure_379_44 **  __outRef__, SuiDesigner3d$__Block_243_47 *  __var___Block_243_47);
static SuiView$MenuNativeItem*  __fn___Closure_537_51(SuiView$MenuNativeItem **  __outRef__, SuiDesigner3d$__Closure_537_51 *  self, SuiView$MenuButton *  mbutton);
static void  __fini___Closure_537_51(SuiDesigner3d$__Closure_537_51 *  self);
static SuiDesigner3d$__Closure_537_51*  __make___Closure_537_51(SuiDesigner3d$__Closure_537_51 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16);
static void  __fn___Closure_onActive_538(SuiDesigner3d$__Closure_onActive_538 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_538(SuiDesigner3d$__Closure_onActive_538 *  self);
static SuiDesigner3d$__Closure_onActive_538*  __make___Closure_onActive_538(SuiDesigner3d$__Closure_onActive_538 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16);
static void  __fn___Closure_581_44(SuiDesigner3d$__Closure_581_44 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_581_44(SuiDesigner3d$__Closure_581_44 *  self);
static SuiDesigner3d$__Closure_581_44*  __make___Closure_581_44(SuiDesigner3d$__Closure_581_44 **  __outRef__, SuiDesigner3d$__Block_529_35 *  __var___Block_529_35, SuiDesigner3d$__Block_577_43 *  __var___Block_577_43);
static void  __fn___Closure_585_39(SuiDesigner3d$__Closure_585_39 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_585_39(SuiDesigner3d$__Closure_585_39 *  self);
static SuiDesigner3d$__Closure_585_39*  __make___Closure_585_39(SuiDesigner3d$__Closure_585_39 **  __outRef__, SuiDesigner3d$__Block_529_35 *  __var___Block_529_35, SuiDesigner3d$__Block_577_43 *  __var___Block_577_43);
static void  __fn___Closure_595_36(SuiDesigner3d$__Closure_595_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_595_36(SuiDesigner3d$__Closure_595_36 *  self);
static SuiDesigner3d$__Closure_595_36*  __make___Closure_595_36(SuiDesigner3d$__Closure_595_36 **  __outRef__);
static void  __fn___Closure_602_36(SuiDesigner3d$__Closure_602_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_602_36(SuiDesigner3d$__Closure_602_36 *  self);
static SuiDesigner3d$__Closure_602_36*  __make___Closure_602_36(SuiDesigner3d$__Closure_602_36 **  __outRef__);
static void  __fn___Closure_608_36(SuiDesigner3d$__Closure_608_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_608_36(SuiDesigner3d$__Closure_608_36 *  self);
static SuiDesigner3d$__Closure_608_36*  __make___Closure_608_36(SuiDesigner3d$__Closure_608_36 **  __outRef__);
static void  __fn___Closure_615_36(SuiDesigner3d$__Closure_615_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_615_36(SuiDesigner3d$__Closure_615_36 *  self);
static SuiDesigner3d$__Closure_615_36*  __make___Closure_615_36(SuiDesigner3d$__Closure_615_36 **  __outRef__);
static void  __fn___Closure_623_36(SuiDesigner3d$__Closure_623_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_623_36(SuiDesigner3d$__Closure_623_36 *  self);
static SuiDesigner3d$__Closure_623_36*  __make___Closure_623_36(SuiDesigner3d$__Closure_623_36 **  __outRef__);
static void  __fn___Closure_631_36(SuiDesigner3d$__Closure_631_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_631_36(SuiDesigner3d$__Closure_631_36 *  self);
static SuiDesigner3d$__Closure_631_36*  __make___Closure_631_36(SuiDesigner3d$__Closure_631_36 **  __outRef__);
static void  __fn___Closure_638_36(SuiDesigner3d$__Closure_638_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_638_36(SuiDesigner3d$__Closure_638_36 *  self);
static SuiDesigner3d$__Closure_638_36*  __make___Closure_638_36(SuiDesigner3d$__Closure_638_36 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16);
static void  __fn___Closure_644_36(SuiDesigner3d$__Closure_644_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_644_36(SuiDesigner3d$__Closure_644_36 *  self);
static SuiDesigner3d$__Closure_644_36*  __make___Closure_644_36(SuiDesigner3d$__Closure_644_36 **  __outRef__);
static void  __fn___Closure_657_36(SuiDesigner3d$__Closure_657_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_657_36(SuiDesigner3d$__Closure_657_36 *  self);
static SuiDesigner3d$__Closure_657_36*  __make___Closure_657_36(SuiDesigner3d$__Closure_657_36 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16);
static void  __fn___Closure_672_36(SuiDesigner3d$__Closure_672_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_672_36(SuiDesigner3d$__Closure_672_36 *  self);
static SuiDesigner3d$__Closure_672_36*  __make___Closure_672_36(SuiDesigner3d$__Closure_672_36 **  __outRef__);
static void  __fn___Closure_699_49(SuiDesigner3d$__Closure_699_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
static void  __fini___Closure_699_49(SuiDesigner3d$__Closure_699_49 *  self);
static SuiDesigner3d$__Closure_699_49*  __make___Closure_699_49(SuiDesigner3d$__Closure_699_49 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16);
static SuiCore$ViewBase *  __fn___Closure_732_52(SuiDesigner3d$__Closure_732_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
static void  __fini___Closure_732_52(SuiDesigner3d$__Closure_732_52 *  self);
static SuiDesigner3d$__Closure_732_52*  __make___Closure_732_52(SuiDesigner3d$__Closure_732_52 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16);
static void  __fn___Closure_862_35(SuiDesigner3d$__Closure_862_35 *  self);
static void  __fini___Closure_862_35(SuiDesigner3d$__Closure_862_35 *  self);
static SuiDesigner3d$__Closure_862_35*  __make___Closure_862_35(SuiDesigner3d$__Closure_862_35 **  __outRef__, SuiDesigner3d$__Block_858_32 *  __var___Block_858_32);
static void  __fn___Closure_907_32(SuiDesigner3d$__Closure_907_32 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_907_32(SuiDesigner3d$__Closure_907_32 *  self);
static SuiDesigner3d$__Closure_907_32*  __make___Closure_907_32(SuiDesigner3d$__Closure_907_32 **  __outRef__, SuiDesigner3d$__Block_858_32 *  __var___Block_858_32);
static void  __fn___Closure_983_26(SuiDesigner3d$__Closure_983_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_983_26(SuiDesigner3d$__Closure_983_26 *  self);
static SuiDesigner3d$__Closure_983_26*  __make___Closure_983_26(SuiDesigner3d$__Closure_983_26 **  __outRef__, SuiDesigner3d$__Block_962_21 *  __var___Block_962_21);


static URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  dockLayoutIns = NULL;

//vtable instance
Vtable_SuiDesigner3d$W3eEditor _vtable_SuiDesigner3d$W3eEditor;

// init meta

void SuiDesigner3d$W3eEditor_initMeta(Vtable_SuiDesigner3d$W3eEditor *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_SuiDesigner$SglEditCtx_init(0)), offsetof(SuiDesigner3d$W3eEditor, editCtx), true, false, 1);
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiDesigner3d$W3eEditor, win), true, false, 1);
	orc_metaField_class(&pNext, "imgCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(SuiDesigner3d$W3eEditor, imgCell), true, false, 1);
	orc_metaField_class(&pNext, "previewCell", ((Vtable_Object*)Vtable_SuiLayout$LayoutAlignPositionCell_init(0)), offsetof(SuiDesigner3d$W3eEditor, previewCell), true, false, 1);
	orc_metaField_class(&pNext, "invalidReact", ((Vtable_Object*)Vtable_SuiDesigner$InvalidReact_init(0)), offsetof(SuiDesigner3d$W3eEditor, invalidReact), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d$W3eEditor, path), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner3d$W3eEditor, drag), true, false, 1);
	orc_metaField_class(&pNext, "chessBg", ((Vtable_Object*)Vtable_SuiDesigner$ChessBgViewCallback_init(0)), offsetof(SuiDesigner3d$W3eEditor, chessBg), true, false, 1);
	orc_metaField_class(&pNext, "glPreviewView", ((Vtable_Object*)Vtable_Sgl$MaterialPreviewView_init(0)), offsetof(SuiDesigner3d$W3eEditor, glPreviewView), true, false, 1);
	orc_metaField_class(&pNext, "matl", ((Vtable_Object*)Vtable_Sgl$Material_init(0)), offsetof(SuiDesigner3d$W3eEditor, matl), true, false, 1);
	orc_metaField_class(&pNext, "mesh", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(SuiDesigner3d$W3eEditor, mesh), true, false, 1);
	orc_metaField_class(&pNext, "meshSphere", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(SuiDesigner3d$W3eEditor, meshSphere), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_Sgl$SglSceneView_init(0)), offsetof(SuiDesigner3d$W3eEditor, sceneView), true, false, 1);
	orc_metaField_class(&pNext, "w3e", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$W3e_init(0)), offsetof(SuiDesigner3d$W3eEditor, w3e), true, false, 1);
	orc_metaField_class(&pNext, "geom", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(SuiDesigner3d$W3eEditor, geom), true, false, 1);

	orc_metaField_method(&pNext, "printSceneTree", offsetof(SuiDesigner3d$W3eEditor, printSceneTree));
	orc_metaField_method(&pNext, "reactPreview", offsetof(SuiDesigner3d$W3eEditor, reactPreview));
	orc_metaField_method(&pNext, "showDialog_renameLayer", offsetof(SuiDesigner3d$W3eEditor, showDialog_renameLayer));
	orc_metaField_method(&pNext, "reactScene", offsetof(SuiDesigner3d$W3eEditor, reactScene));
	orc_metaField_method(&pNext, "drawDepthView", offsetof(SuiDesigner3d$W3eEditor, drawDepthView));
	orc_metaField_method(&pNext, "react", offsetof(SuiDesigner3d$W3eEditor, react));
	orc_metaField_method(&pNext, "showWindow_mapSetting", offsetof(SuiDesigner3d$W3eEditor, showWindow_mapSetting));
	orc_metaField_method(&pNext, "onWindowEvent", offsetof(SuiDesigner3d$W3eEditor, onWindowEvent));
	orc_metaField_method(&pNext, "showWindow", offsetof(SuiDesigner3d$W3eEditor, showWindow));
}


// vtable init


Vtable_SuiDesigner3d$W3eEditor* Vtable_SuiDesigner3d$W3eEditor_init(Vtable_SuiDesigner3d$W3eEditor* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d$W3eEditor;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d$W3eEditor_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d$W3eEditor";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d$W3eEditor_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d$W3eEditor_fini(SuiDesigner3d$W3eEditor *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->editCtx);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->win);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->imgCell);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->previewCell);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->invalidReact);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->path);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->chessBg);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->glPreviewView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->matl);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->mesh);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->meshSphere);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->sceneView);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->w3e);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->geom);

}

// init fields function


void SuiDesigner3d$W3eEditor_init_fields(SuiDesigner3d$W3eEditor *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d$W3eEditor_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS SuiDesigner$SglEditCtx*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->editCtx, SuiDesigner$SglEditCtx_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->win, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->imgCell, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->previewCell, NULL);
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InvalidReact*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->invalidReact, SuiDesigner$mkInvalidReact(&tmpReturn_2, self) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->path, Orc$str(&tmpReturn_3, "../build/././a.tilemap.json") );
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->drag, SuiView$Drag_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ChessBgViewCallback*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->chessBg, SuiDesigner$ChessBgViewCallback_new(&tmpNewOwner_5) );
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->glPreviewView, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->matl, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->mesh, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->meshSphere, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->sceneView, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->w3e, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d$W3eEditor*)self)->geom, NULL);
    }
	((SuiDesigner3d$W3eEditor*)self)->printSceneTree = (void*)SuiDesigner3d$W3eEditor$printSceneTree;
	((Object*)self)->ctor = (void*)SuiDesigner3d$W3eEditor$ctor;
	((SuiDesigner3d$W3eEditor*)self)->reactPreview = (void*)SuiDesigner3d$W3eEditor$reactPreview;
	((SuiDesigner3d$W3eEditor*)self)->showDialog_renameLayer = (void*)SuiDesigner3d$W3eEditor$showDialog_renameLayer;
	((SuiDesigner3d$W3eEditor*)self)->reactScene = (void*)SuiDesigner3d$W3eEditor$reactScene;
	((SuiDesigner3d$W3eEditor*)self)->drawDepthView = (void*)SuiDesigner3d$W3eEditor$drawDepthView;
	((SuiDesigner3d$W3eEditor*)self)->react = (void*)SuiDesigner3d$W3eEditor$react;
	((SuiDesigner3d$W3eEditor*)self)->showWindow_mapSetting = (void*)SuiDesigner3d$W3eEditor$showWindow_mapSetting;
	((SuiDesigner3d$W3eEditor*)self)->onWindowEvent = (void*)SuiDesigner3d$W3eEditor$onWindowEvent;
	((SuiDesigner3d$W3eEditor*)self)->showWindow = (void*)SuiDesigner3d$W3eEditor$showWindow;
}

// init function

void SuiDesigner3d$W3eEditor_init(SuiDesigner3d$W3eEditor *self, void *pOwner){
    Vtable_SuiDesigner3d$W3eEditor_init(&_vtable_SuiDesigner3d$W3eEditor);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d$W3eEditor;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d$W3eEditor_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d$W3eEditor * SuiDesigner3d$W3eEditor_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d$W3eEditor *self = calloc(1, sizeof(SuiDesigner3d$W3eEditor));
	
    SuiDesigner3d$W3eEditor_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner3d$W3eEditor$printSceneTree(SuiDesigner3d$W3eEditor *  self){
	
}


void  SuiDesigner3d$W3eEditor$ctor(SuiDesigner3d$W3eEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_110_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_110_27(&tmpReturn_1) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  projectDirPath = (projectDirPath=NULL,urgc_init_var_class((void**)&projectDirPath, Orc$String$add(Orc$Path_dirname(&tmpReturn_2, Orc$Path_getExecutionPath(&tmpReturn_3) ->str) , "/asset/styles") ));
	printf("projectDirPath:%s\n", projectDirPath->str) ;
	SuiDesigner$Project *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_4 = NULL;
	(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_4) )->init(tmpThis_1, projectDirPath->str) ;
}


SuiCore$ViewBase *  SuiDesigner3d$W3eEditor$reactPreview(SuiDesigner3d$W3eEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_128_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_128_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_128_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->chessBg) ;
		URGC_VAR_CLEANUP SuiDesigner3d$__Closure_134_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_134_26(&tmpReturn_2) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_3 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_3, o, 0) ;
		return o; 
	}
}


void  SuiDesigner3d$W3eEditor$showDialog_renameLayer(SuiDesigner3d$W3eEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner3d$__Block_146_33*  __var___Block_146_33 = (__var___Block_146_33=NULL,urgc_init_var((void**)&__var___Block_146_33, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Block_146_33) , __finiBlock___Block_146_33) ));
	urgc_set_field_class(__var___Block_146_33, (void * )offsetof(SuiDesigner3d$__Block_146_33, self) , self) ;
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_148_42*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt("hi", "重命名", __make___Closure_148_42(&tmpReturn_1, __var___Block_146_33) ) ;
}


SuiCore$ViewBase *  SuiDesigner3d$W3eEditor$reactScene(SuiDesigner3d$W3eEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	if (0) {
		URGC_VAR_CLEANUP_CLASS Sgl$MaterialPreviewView*  tmpReturn_1 = NULL;
		{
			Sgl$MaterialPreviewView*  __scopeVar_159_12 = Sgl$mkMaterialPreviewView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_159_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_159_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0x00222222;
			((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
			if (o->matl != self->matl) {
				urgc_set_field_class(o, (void * )offsetof(Sgl$MaterialPreviewView, matl) , self->matl) ;
				o->buildDrawObj(o) ;
			}
			urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, glPreviewView) , o) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_2 = NULL;
			SuiLayout$layoutLinearCell(&tmpReturn_2, o, 0) ;
			return o; 
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_3 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_177_8 = SuiLayout$layoutAlign(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_177_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_177_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		URGC_VAR_CLEANUP SuiDesigner3d$__Closure_182_26*  tmpReturn_4 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_182_26(&tmpReturn_4) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) ;
		if (0) {
			URGC_VAR_CLEANUP_CLASS Sgl$MaterialPreviewView*  tmpReturn_6 = NULL;
			{
				Sgl$MaterialPreviewView*  __scopeVar_190_20 = Sgl$mkMaterialPreviewView(&tmpReturn_6, o, 0) , *o = __scopeVar_190_20;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_190_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
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
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, glPreviewView) , o) ;
				((SuiCore$View * )o)->width = 500;
				((SuiCore$View * )o)->height = 500;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_7 = NULL;
				{
					SuiLayout$LayoutAlignPositionCell*  __scopeVar_223_24 = SuiLayout$layoutAlignPositionCell(&tmpReturn_7, o, 0) , *o = __scopeVar_223_24;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_223_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
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
				Sgl$SglSceneView*  __scopeVar_235_20 = Sgl$mkSglSceneView(&tmpReturn_8, o, 0) , *o = __scopeVar_235_20;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_235_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, sceneView) , o) ;
				((SuiCore$View * )o)->backgroundColor = 0x00ffffff;
				((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
				if (o->matl != self->matl) {
					URGC_VAR_CLEANUP SuiDesigner3d$__Block_243_47*  __var___Block_243_47 = (__var___Block_243_47=NULL,urgc_init_var((void**)&__var___Block_243_47, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Block_243_47) , __finiBlock___Block_243_47) ));
					o->mkBaseScene(o) ;
					self->editCtx->setSceneView(self->editCtx, o) ;
					SuiCore$Emitter *  tmpThis_1 = NULL;
					URGC_VAR_CLEANUP_CLASS SuiDesigner$EventSglSceneChanged*  tmpNewOwner_9 = NULL;
					(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, SuiDesigner$EventSglSceneChanged_new(&tmpNewOwner_9) ) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
					tex->loadImageByPathCstr(tex, "../asset/terrain.png") ;
					URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  dc = (dc=NULL,urgc_init_var_class((void**)&dc, Sgl$DrawCtx_new(&dc) ));
					urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, matl) , dc->depthMatl) ;
					urgc_set_field_class(o, (void * )offsetof(Sgl$SglSceneView, matl) , self->matl) ;
					o->buildDrawObj(o) ;
					URGC_VAR_CLEANUP_CLASS Sgl$GeometryArrow*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryArrow_new(&geom) ));
					((Sgl$Geometry * )geom)->build(geom) ;
					urgc_set_field_class(o->drawObj, (void * )offsetof(Sgl$Draw, geometry) , geom) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_10 = NULL;
					urgc_set_field_class(__var___Block_243_47, (void * )offsetof(SuiDesigner3d$__Block_243_47, m) , Sgl$Mesh_new(&tmpNewOwner_10) ) ;
					urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, meshSphere) , __var___Block_243_47->m) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_11 = NULL;
					urgc_set_field_class(__var___Block_243_47->m, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_11) ) ;
					__var___Block_243_47->m->material->load(__var___Block_243_47->m->material, "../asset/hi.matl.json") ;
					__var___Block_243_47->m->material->setUniformTex2d(__var___Block_243_47->m->material, "tex", tex) ;
					urgc_set_field_class(__var___Block_243_47->m, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
					((Sgl$Obj3d * )__var___Block_243_47->m)->position.y = -50;
					((Sgl$Obj3d * )__var___Block_243_47->m)->position.z = 100;
					((Sgl$Obj3d * )__var___Block_243_47->m)->visible = true;
					((SuiCore$Node * )o->scene)->appendChild(o->scene, __var___Block_243_47->m) ;
					Sgl$Scene *  scene = o->scene;
					Sgl$Draw *  drawObj = o->drawObj;
					URGC_VAR_CLEANUP_CLASS Sgl$PointLight*  tmpNewOwner_12 = NULL;
					{
						Sgl$PointLight*  o = Sgl$PointLight_new(&tmpNewOwner_12) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_300_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						SuiCore$Vec3$set(&((Sgl$Obj3d * )o)->position, -500, 100, 0) ;
						((SuiCore$Node * )scene)->appendChild(scene, o) ;
					}
					URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_13 = NULL;
					{
						Sgl$Mesh*  o = Sgl$Mesh_new(&tmpNewOwner_13) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_309_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						urgc_set_field_class(__var___Block_243_47, (void * )offsetof(SuiDesigner3d$__Block_243_47, m) , o) ;
						URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_14 = NULL;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_14) ) ;
						o->material->load(o->material, "../asset/heightmap.matl.json") ;
						o->material->setUniformTex2d(o->material, "tex", tex) ;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, geometry) , self->geom) ;
						((Sgl$Obj3d * )o)->position.y = 0;
						((SuiCore$Node * )scene)->appendChild(scene, o) ;
					}
					if (0) {
						URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxReader*  mr = (mr=NULL,urgc_init_var_class((void**)&mr, SuiDesigner3d_w3e$MdxReader_new(&mr) ));
						mr->loadByPathCstr(mr, "../asset/Units/Human/Footman/Footman.mdx") ;
						URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MkMdx*  mkMdx = (mkMdx=NULL,urgc_init_var_class((void**)&mkMdx, SuiDesigner3d_w3e$MkMdx_new(&mkMdx) ));
						urgc_set_field_class(mkMdx, (void * )offsetof(SuiDesigner3d_w3e$MkMdx, mr) , mr) ;
						mkMdx->mkSkeleton(mkMdx) ;
						URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpNewOwner_15 = NULL;
						{
							Sgl$Obj3d*  o = Sgl$Obj3d_new(&tmpNewOwner_15) ;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_328_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							if (((SuiCore$Node * )mkMdx->ske)->parent != o) {
								((SuiCore$Node * )o)->appendChild(o, mkMdx->ske) ;
								URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxSeqPlayer*  player = (player=NULL,urgc_init_var_class((void**)&player, SuiDesigner3d_w3e$MdxSeqPlayer_new(&player) ));
								player->init(player, mr) ;
								((SuiCore$Node * )o)->appendChild(o, player) ;
								player->play(player, "Stand - 1") ;
							}
							urgc_set_field_class(__var___Block_243_47, (void * )offsetof(SuiDesigner3d$__Block_243_47, m) , o) ;
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
								URGC_VAR_CLEANUP_CLASS Sgl$SkinMesh*  tmpNewOwner_16 = NULL;
								{
									Sgl$SkinMesh*  o = Sgl$SkinMesh_new(&tmpNewOwner_16) ;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_355_40 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									URGC_VAR_CLEANUP_CLASS Sgl$Material*  material = (material=NULL,urgc_init_var_class((void**)&material, Sgl$Material_new(&material) ));
									material->load(material, "../asset/mdx.matl.json") ;
									URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
									tex->loadImageByPathCstr(tex, Orc$String$add(Orc$str(&tmpReturn_17, "../asset/") , texPath) ->str) ;
									material->setUniformTex2d(material, "tex", tex) ;
									urgc_set_field_class(o, (void * )offsetof(Sgl$SkinMesh, material) , material) ;
									urgc_set_field_class(o, (void * )offsetof(Sgl$SkinMesh, geometry) , geoset->geom) ;
									((SuiCore$Node * )mkMdx->ske)->appendChild(mkMdx->ske, o) ;
								}
							}
						}
					}
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_379_44*  tmpReturn_18 = NULL;
					urgc_set_field(o->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_379_44(&tmpReturn_18, __var___Block_243_47) ) ;
					URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_19 = NULL;
					{
						Sgl$Mesh*  o = Sgl$Mesh_new(&tmpNewOwner_19) ;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_394_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, mesh) , o) ;
						URGC_VAR_CLEANUP_CLASS Sgl$GeometryPlane*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryPlane_new(&geom) ));
						geom->width = 10000;
						geom->height = 10000;
						geom->planeType = 1;
						((Sgl$Geometry * )geom)->build(geom) ;
						URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_20 = NULL;
						urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_20) ) ;
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
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_21 = NULL;
				{
					SuiLayout$LayoutAlignPositionCell*  __scopeVar_448_24 = SuiLayout$layoutAlignPositionCell(&tmpReturn_21, o, 0) , *o = __scopeVar_448_24;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_448_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->left = 0;
					o->top = 0;
					o->right = 0;
					o->bottom = 0;
				}
			}
		}
		return o; 
	}
}


void  SuiDesigner3d$W3eEditor$drawDepthView(SuiDesigner3d$W3eEditor *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  dctx = (dctx=NULL,urgc_init_var_class((void**)&dctx, Sgl$DrawCtx_new(&dctx) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Fbo*  fbo = (fbo=NULL,urgc_init_var_class((void**)&fbo, Sgl$Fbo_new(&fbo) ));
	SuiCore$Frame frame = ((SuiCore$ViewBase * )self->sceneView)->frame;
	fbo->buildWithColorDepthStencilTexture(fbo, (int )frame.width, (int )frame.height, true, true, false) ;
	fbo->setGlDrawBufferNone(fbo) ;
	fbo->startDraw(fbo, 0.2, 0.2, 0.2, 1.0, true, true, true) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  cam = (cam=NULL,urgc_init_var_class((void**)&cam, Sgl$PerspectiveCamera_new(&cam) ));
	cam->target = SuiCore$mkVec3(0, 0, 0) ;
	((Sgl$Obj3d * )cam)->up = SuiCore$mkVec3(0, 1, 0) ;
	cam->fov = 45 / 180.0 * Orc$PI;
	cam->aspect = 1.0;
	cam->nearPlane = 100.1;
	cam->farPlane = 5000;
	SuiCore$Vec3$set(&((Sgl$Obj3d * )cam)->position, -10, 2000, 0.10) ;
	((Sgl$Obj3d * )cam)->updateWorldTransformAndSubtree(cam) ;
	dctx->drawDepth(dctx, self->sceneView->scene, cam) ;
	URGC_VAR_CLEANUP_CLASS Sgl$DepthTexturePreview*  prev = (prev=NULL,urgc_init_var_class((void**)&prev, Sgl$DepthTexturePreview_new(&prev) ));
	prev->init_readPixels(prev, (int )frame.width, (int )frame.height) ;
	fbo->endDraw(fbo) ;
	fbo->setGlDrawBufferDefault(fbo) ;
	Sgl$SglSceneView_showTextureWindow(fbo->tex2d, (int )frame.width, (int )frame.height) ;
	prev->showTextureWindow(prev) ;
	self->mesh->material->setUniformTex2d(self->mesh->material, "shadowMap", fbo->depthTex2d) ;
	self->mesh->material->setUniform1i(self->mesh->material, "hasShadow", 1) ;
	self->mesh->material->setUniformMat4(self->mesh->material, "shadowVp", ((Sgl$Camera * )cam)->calcVp(cam) ) ;
}


void  SuiDesigner3d$W3eEditor$react(SuiDesigner3d$W3eEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner3d$__Block_523_16*  __var___Block_523_16 = (__var___Block_523_16=NULL,urgc_init_var((void**)&__var___Block_523_16, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Block_523_16) , __finiBlock___Block_523_16) ));
	urgc_set_field_class(__var___Block_523_16, (void * )offsetof(SuiDesigner3d$__Block_523_16, self) , self) ;
	printf("react SpriteSheetEditor\n") ;
	__var___Block_523_16->t = SuiDesigner$themeIns() ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_526_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		if (1) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_529_16 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_529_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_529_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP SuiDesigner3d$__Block_529_35*  __var___Block_529_35 = (__var___Block_529_35=NULL,urgc_init_var((void**)&__var___Block_529_35, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Block_529_35) , __finiBlock___Block_529_35) ));
				((SuiCore$View * )o)->backgroundColor = __var___Block_523_16->t->menubar_bg;
				SuiCore$Inset$setAxis(&((SuiCore$View * )o)->padding, 0, 6) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  btnsStr = Orc$str((btnsStr = NULL,&btnsStr), "文件,项目,视图,调试,窗口,帮助") ;
				URGC_VAR_CLEANUP_CLASS Orc$List*  btns = Orc$String$splitByRe((btns = NULL,&btns), btnsStr, ",") ;
				URGC_VAR_CLEANUP_CLASS SuiDesigner$MenuBarCtrl*  tmpNewOwner_2 = NULL;
				urgc_set_field_class(__var___Block_529_35, (void * )offsetof(SuiDesigner3d$__Block_529_35, group) , SuiDesigner$MenuBarCtrl_new(&tmpNewOwner_2) ) ;
				URGC_VAR_CLEANUP SuiDesigner3d$__Closure_537_51*  tmpReturn_3 = NULL;
				urgc_set_field(__var___Block_529_35->group, (void * )offsetof(SuiDesigner$MenuBarCtrl, cbCreateMenuNativeItem) , __make___Closure_537_51(&tmpReturn_3, __var___Block_523_16) ) ;
				for (int  i = 0; i < btns->size(btns) ; i++) {
					Object *  obj = btns->get(btns, i) ;
					URGC_VAR_CLEANUP_CLASS Orc$String*  btn = (btn=NULL,urgc_init_var_class((void**)&btn, (Orc$String* )btns->get(btns, i) ));
					URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  tmpReturn_4 = NULL;
					{
						SuiView$MenuButton*  __scopeVar_577_24 = SuiView$mkMenuButton(&tmpReturn_4, o, i) , *o = __scopeVar_577_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_577_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP SuiDesigner3d$__Block_577_43*  __var___Block_577_43 = (__var___Block_577_43=NULL,urgc_init_var((void**)&__var___Block_577_43, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Block_577_43) , __finiBlock___Block_577_43) ));
						urgc_set_field_class(__var___Block_577_43, (void * )offsetof(SuiDesigner3d$__Block_577_43, mbutton) , o) ;
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuButton, text) , btn) ;
						URGC_VAR_CLEANUP SuiDesigner3d$__Closure_581_44*  tmpReturn_5 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onMouseMove) , __make___Closure_581_44(&tmpReturn_5, __var___Block_529_35, __var___Block_577_43) ) ;
						URGC_VAR_CLEANUP SuiDesigner3d$__Closure_585_39*  tmpReturn_6 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onClick) , __make___Closure_585_39(&tmpReturn_6, __var___Block_529_35, __var___Block_577_43) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_7 = NULL;
			{
				SuiLayout$LayoutLinear*  o = SuiLayout$layoutLinear(&tmpReturn_7, self->win->rootView, 0) ;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_592_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_8 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_593_20 = SuiView$mkDrawButton(&tmpReturn_8, o, 0) , *o = __scopeVar_593_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_593_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_9, "设置") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_595_36*  tmpReturn_10 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_595_36(&tmpReturn_10) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_11 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_600_20 = SuiView$mkDrawButton(&tmpReturn_11, o, 0) , *o = __scopeVar_600_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_600_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_12, "添加tilelayer") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_602_36*  tmpReturn_13 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_602_36(&tmpReturn_13) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_14 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_606_20 = SuiView$mkDrawButton(&tmpReturn_14, o, 0) , *o = __scopeVar_606_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_606_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_15, "添加tileset") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_608_36*  tmpReturn_16 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_608_36(&tmpReturn_16) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_17 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_612_20 = SuiView$mkDrawButton(&tmpReturn_17, o, 0) , *o = __scopeVar_612_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_612_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_18, "创建随机tile") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_615_36*  tmpReturn_19 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_615_36(&tmpReturn_19) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_20 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_620_20 = SuiView$mkDrawButton(&tmpReturn_20, o, 0) , *o = __scopeVar_620_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_620_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_21 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_21, "创建动画tile") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_623_36*  tmpReturn_22 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_623_36(&tmpReturn_22) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_23 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_628_20 = SuiView$mkDrawButton(&tmpReturn_23, o, 0) , *o = __scopeVar_628_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_628_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_24, "创建AutoTile") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_631_36*  tmpReturn_25 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_631_36(&tmpReturn_25) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_26 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_636_20 = SuiView$mkDrawButton(&tmpReturn_26, o, 0) , *o = __scopeVar_636_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_636_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_27 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_27, "打印树") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_638_36*  tmpReturn_28 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_638_36(&tmpReturn_28, __var___Block_523_16) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_29 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_642_20 = SuiView$mkDrawButton(&tmpReturn_29, o, 0) , *o = __scopeVar_642_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_642_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_30, "保存") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_644_36*  tmpReturn_31 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_644_36(&tmpReturn_31) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_32 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_655_20 = SuiView$mkDrawButton(&tmpReturn_32, o, 0) , *o = __scopeVar_655_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_655_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_33 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_33, "加载") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_657_36*  tmpReturn_34 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_657_36(&tmpReturn_34, __var___Block_523_16) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_35 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_670_20 = SuiView$mkDrawButton(&tmpReturn_35, o, 0) , *o = __scopeVar_670_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_670_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_36 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_36, "lala") ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_672_36*  tmpReturn_37 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_672_36(&tmpReturn_37) ) ;
				}
			}
		}
		if (1) {
			URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpReturn_38 = NULL;
			{
				SuiView$DockLayout*  __scopeVar_692_16 = SuiView$dockLayout(&tmpReturn_38, o, 0) , *o = __scopeVar_692_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_692_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_var_class(&dockLayoutIns, o) ;
				((SuiCore$View * )o)->width = 100;
				((SuiCore$View * )o)->height = 20;
				((SuiCore$View * )o)->backgroundColor = 0x30000033;
				if (((SuiCore$Node * )o)->isNewForReact) {
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_699_49*  tmpReturn_39 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemHeadView) , __make___Closure_699_49(&tmpReturn_39, __var___Block_523_16) ) ;
					URGC_VAR_CLEANUP SuiDesigner3d$__Closure_732_52*  tmpReturn_40 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemContentView) , __make___Closure_732_52(&tmpReturn_40, __var___Block_523_16) ) ;
					{
						SuiView$DockItem*  __scopeVar_810_24 = o->root, *o = __scopeVar_810_24;
						
					
						o->isHorizontal = false;
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_41 = NULL;
						{
							SuiView$DockItem*  __scopeVar_813_28 = SuiView$mkDockItemSplitter(&tmpReturn_41, o, NULL, true) , *o = __scopeVar_813_28;
							
						
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_42 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_43 = NULL;
							{
								SuiView$DockItem*  __scopeVar_814_32 = SuiView$mkDockItem(&tmpReturn_42, o, Orc$str(&tmpReturn_43, "hier") ) , *o = __scopeVar_814_32;
								
							
								o->intId = 0;
								o->width = 150;
							}
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_44 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_45 = NULL;
							{
								SuiView$DockItem*  __scopeVar_818_32 = SuiView$mkDockItem(&tmpReturn_44, o, Orc$str(&tmpReturn_45, "scene") ) , *o = __scopeVar_818_32;
								
							
								o->intId = 0;
							}
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_46 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_47 = NULL;
							{
								SuiView$DockItem*  __scopeVar_821_32 = SuiView$mkDockItem(&tmpReturn_46, o, Orc$str(&tmpReturn_47, "inspector") ) , *o = __scopeVar_821_32;
								
							
								o->intId = 0;
								o->width = 150;
							}
						}
						URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_48 = NULL;
						{
							SuiView$DockItem*  __scopeVar_826_28 = SuiView$mkDockItemSplitter(&tmpReturn_48, o, NULL, true) , *o = __scopeVar_826_28;
							
						
							o->width = 150;
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_49 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_50 = NULL;
							{
								SuiView$DockItem*  __scopeVar_828_32 = SuiView$mkDockItem(&tmpReturn_49, o, Orc$str(&tmpReturn_50, "project") ) , *o = __scopeVar_828_32;
								
							
								o->intId = 0;
								o->width = 160;
							}
							URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_51 = NULL;
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_52 = NULL;
							{
								SuiView$DockItem*  __scopeVar_832_32 = SuiView$mkDockItem(&tmpReturn_51, o, Orc$str(&tmpReturn_52, "dir") ) , *o = __scopeVar_832_32;
								
							
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


void  SuiDesigner3d$W3eEditor$showWindow_mapSetting(SuiDesigner3d$W3eEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner3d$__Block_858_32*  __var___Block_858_32 = (__var___Block_858_32=NULL,urgc_init_var((void**)&__var___Block_858_32, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Block_858_32) , __finiBlock___Block_858_32) ));
	urgc_set_field_class(__var___Block_858_32, (void * )offsetof(SuiDesigner3d$__Block_858_32, win) , NULL) ;
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_862_35*  tmpReturn_1 = NULL;
	urgc_set_field(__var___Block_858_32, (void * )offsetof(SuiDesigner3d$__Block_858_32, reactMapSetting) , __make___Closure_862_35(&tmpReturn_1, __var___Block_858_32) ) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_2 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_2) ;
		
	
		urgc_set_field_class(__var___Block_858_32, (void * )offsetof(SuiDesigner3d$__Block_858_32, win) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_3 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_3) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_916_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			__var___Block_858_32->win->setRootView(__var___Block_858_32->win, o) ;
		}
		(*(__var___Block_858_32->reactMapSetting))((void * )(__var___Block_858_32->reactMapSetting)) ;
		o->setTitle(o, "地图设置") ;
		o->setSize(o, 300, 400) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  SuiDesigner3d$W3eEditor$onWindowEvent(SuiDesigner3d$W3eEditor *  self, SuiCore$Event *  e){
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


void  SuiDesigner3d$W3eEditor$showWindow(SuiDesigner3d$W3eEditor *  self){
	URGC_VAR_CLEANUP SuiDesigner3d$__Block_962_21*  __var___Block_962_21 = (__var___Block_962_21=NULL,urgc_init_var((void**)&__var___Block_962_21, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Block_962_21) , __finiBlock___Block_962_21) ));
	urgc_set_field_class(__var___Block_962_21, (void * )offsetof(SuiDesigner3d$__Block_962_21, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, win) , Sui$Window_new(&tmpNewOwner_1) ) ;
	if (1) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$W3e*  w3e = (w3e=NULL,urgc_init_var_class((void**)&w3e, SuiDesigner3d_w3e$W3e_new(&w3e) ));
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, w3e) , w3e) ;
		w3e->load(w3e, "../asset/100.w3e") ;
		URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpReturn_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, geom) , w3e->mkGeometry(&tmpReturn_2, w3e) ) ;
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryHeightMap*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryHeightMap_new(&geom) ));
		geom->buildByPath(geom, "../asset/heightmap.png") ;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, geom) , geom) ;
		w3e->mkGroundTexs(w3e) ;
	}
	{
		Sui$Window*  o = self->win;
		
	
		URGC_VAR_CLEANUP SuiDesigner3d$__Closure_983_26*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_983_26(&tmpReturn_3, __var___Block_962_21) ) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_4 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$W3eEditor, matl) , Sgl$Material_new(&tmpNewOwner_4) ) ;
		self->matl->load(self->matl, "../asset/hi.matl.json") ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_5 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_5) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_990_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
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



static void  __finiBlock___Block_146_33(SuiDesigner3d$__Block_146_33 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$__Block_146_33, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_243_47(SuiDesigner3d$__Block_243_47 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$__Block_243_47, m) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_523_16(SuiDesigner3d$__Block_523_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$__Block_523_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_529_35(SuiDesigner3d$__Block_529_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$__Block_529_35, group) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_577_43(SuiDesigner3d$__Block_577_43 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$__Block_577_43, mbutton) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_858_32(SuiDesigner3d$__Block_858_32 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$__Block_858_32, win) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_962_21(SuiDesigner3d$__Block_962_21 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d$__Block_962_21, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_110_27(SuiDesigner3d$__Closure_110_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("isDragging tileset\n") ;
	}
}

static void  __fini___Closure_110_27(SuiDesigner3d$__Closure_110_27 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_110_27*  __make___Closure_110_27(SuiDesigner3d$__Closure_110_27 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_110_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_110_27) , __fini___Closure_110_27) ));
	self->invoke = __fn___Closure_110_27;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_134_26(SuiDesigner3d$__Closure_134_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	}
}

static void  __fini___Closure_134_26(SuiDesigner3d$__Closure_134_26 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_134_26*  __make___Closure_134_26(SuiDesigner3d$__Closure_134_26 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_134_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_134_26) , __fini___Closure_134_26) ));
	self->invoke = __fn___Closure_134_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_148_42(SuiDesigner3d$__Closure_148_42 *  self, Orc$String*  newValue){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newValue);

	self->__var___Block_146_33->self->invalidReact->invalid(self->__var___Block_146_33->self->invalidReact) ;
}

static void  __fini___Closure_148_42(SuiDesigner3d$__Closure_148_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_148_42, __var___Block_146_33) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_148_42*  __make___Closure_148_42(SuiDesigner3d$__Closure_148_42 **  __outRef__, SuiDesigner3d$__Block_146_33 *  __var___Block_146_33){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_148_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_148_42) , __fini___Closure_148_42) ));
	self->invoke = __fn___Closure_148_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_148_42, __var___Block_146_33) , __var___Block_146_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_182_26(SuiDesigner3d$__Closure_182_26 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
	}
}

static void  __fini___Closure_182_26(SuiDesigner3d$__Closure_182_26 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_182_26*  __make___Closure_182_26(SuiDesigner3d$__Closure_182_26 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_182_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_182_26) , __fini___Closure_182_26) ));
	self->invoke = __fn___Closure_182_26;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_379_44(SuiDesigner3d$__Closure_379_44 *  self, SuiView$Drag *  d){
	if (d->mouseDownButton == 1) {
		((Sgl$Obj3d * )self->__var___Block_243_47->m)->rotation.y += Orc$toRad(d->deltaPos.x) ;
	}
	if (d->mouseDownButton == 2) {
		((Sgl$Obj3d * )self->__var___Block_243_47->m)->rotation.x += Orc$toRad(d->deltaPos.y) ;
	}
	if (d->mouseDownButton == 3) {
		((Sgl$Obj3d * )self->__var___Block_243_47->m)->scale.x = Orc$maxFloat(0.1, ((Sgl$Obj3d * )self->__var___Block_243_47->m)->scale.x + d->deltaPos.x / 100.0) ;
		((Sgl$Obj3d * )self->__var___Block_243_47->m)->scale.y = ((Sgl$Obj3d * )self->__var___Block_243_47->m)->scale.x;
		((Sgl$Obj3d * )self->__var___Block_243_47->m)->scale.z = ((Sgl$Obj3d * )self->__var___Block_243_47->m)->scale.x;
	}
}

static void  __fini___Closure_379_44(SuiDesigner3d$__Closure_379_44 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_379_44, __var___Block_243_47) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_379_44*  __make___Closure_379_44(SuiDesigner3d$__Closure_379_44 **  __outRef__, SuiDesigner3d$__Block_243_47 *  __var___Block_243_47){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_379_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_379_44) , __fini___Closure_379_44) ));
	self->invoke = __fn___Closure_379_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_379_44, __var___Block_243_47) , __var___Block_243_47) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiView$MenuNativeItem*  __fn___Closure_537_51(SuiView$MenuNativeItem **  __outRef__, SuiDesigner3d$__Closure_537_51 *  self, SuiView$MenuButton *  mbutton){
	URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_onActive_538*  tmpReturn_1 = NULL;
	(urgc_set_var(&onActive, __make___Closure_onActive_538(&tmpReturn_1, self->__var___Block_523_16) ) );
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
				SuiView$MenuNativeItem*  __scopeVar_553_32 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "最近打开") , onActive) , *o = __scopeVar_553_32;
				
			
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
			SuiView$mkMenuNativeItem(&tmpReturn_27, o, Orc$str(&tmpReturn_28, "绘制深度图") , onActive) ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_29 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
			SuiView$mkMenuNativeItem(&tmpReturn_29, o, Orc$str(&tmpReturn_30, "退出") , onActive) ;
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, o) ; 
	}
}

static void  __fini___Closure_537_51(SuiDesigner3d$__Closure_537_51 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_537_51, __var___Block_523_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_537_51*  __make___Closure_537_51(SuiDesigner3d$__Closure_537_51 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_537_51*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_537_51) , __fini___Closure_537_51) ));
	self->invoke = __fn___Closure_537_51;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_537_51, __var___Block_523_16) , __var___Block_523_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_538(SuiDesigner3d$__Closure_onActive_538 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu:%s\n", item->label->str) ;
	if (Orc$String$equals(item->label, "退出") ) {
		exit(0) ;
	}
	if (Orc$String$equals(item->label, "绘制深度图") ) {
		self->__var___Block_523_16->self->drawDepthView(self->__var___Block_523_16->self) ;
	}
}

static void  __fini___Closure_onActive_538(SuiDesigner3d$__Closure_onActive_538 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_onActive_538, __var___Block_523_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_onActive_538*  __make___Closure_onActive_538(SuiDesigner3d$__Closure_onActive_538 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_onActive_538*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_onActive_538) , __fini___Closure_onActive_538) ));
	self->invoke = __fn___Closure_onActive_538;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_onActive_538, __var___Block_523_16) , __var___Block_523_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_581_44(SuiDesigner3d$__Closure_581_44 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_529_35->group->onmove(self->__var___Block_529_35->group, self->__var___Block_577_43->mbutton, me) ;
}

static void  __fini___Closure_581_44(SuiDesigner3d$__Closure_581_44 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_581_44, __var___Block_529_35) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_581_44, __var___Block_577_43) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_581_44*  __make___Closure_581_44(SuiDesigner3d$__Closure_581_44 **  __outRef__, SuiDesigner3d$__Block_529_35 *  __var___Block_529_35, SuiDesigner3d$__Block_577_43 *  __var___Block_577_43){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_581_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_581_44) , __fini___Closure_581_44) ));
	self->invoke = __fn___Closure_581_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_581_44, __var___Block_529_35) , __var___Block_529_35) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_581_44, __var___Block_577_43) , __var___Block_577_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_585_39(SuiDesigner3d$__Closure_585_39 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_529_35->group->onclick(self->__var___Block_529_35->group, self->__var___Block_577_43->mbutton, me) ;
}

static void  __fini___Closure_585_39(SuiDesigner3d$__Closure_585_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_585_39, __var___Block_529_35) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_585_39, __var___Block_577_43) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_585_39*  __make___Closure_585_39(SuiDesigner3d$__Closure_585_39 **  __outRef__, SuiDesigner3d$__Block_529_35 *  __var___Block_529_35, SuiDesigner3d$__Block_577_43 *  __var___Block_577_43){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_585_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_585_39) , __fini___Closure_585_39) ));
	self->invoke = __fn___Closure_585_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_585_39, __var___Block_529_35) , __var___Block_529_35) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_585_39, __var___Block_577_43) , __var___Block_577_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_595_36(SuiDesigner3d$__Closure_595_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_595_36(SuiDesigner3d$__Closure_595_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_595_36*  __make___Closure_595_36(SuiDesigner3d$__Closure_595_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_595_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_595_36) , __fini___Closure_595_36) ));
	self->invoke = __fn___Closure_595_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_602_36(SuiDesigner3d$__Closure_602_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_602_36(SuiDesigner3d$__Closure_602_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_602_36*  __make___Closure_602_36(SuiDesigner3d$__Closure_602_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_602_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_602_36) , __fini___Closure_602_36) ));
	self->invoke = __fn___Closure_602_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_608_36(SuiDesigner3d$__Closure_608_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_608_36(SuiDesigner3d$__Closure_608_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_608_36*  __make___Closure_608_36(SuiDesigner3d$__Closure_608_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_608_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_608_36) , __fini___Closure_608_36) ));
	self->invoke = __fn___Closure_608_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_615_36(SuiDesigner3d$__Closure_615_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_615_36(SuiDesigner3d$__Closure_615_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_615_36*  __make___Closure_615_36(SuiDesigner3d$__Closure_615_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_615_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_615_36) , __fini___Closure_615_36) ));
	self->invoke = __fn___Closure_615_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_623_36(SuiDesigner3d$__Closure_623_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_623_36(SuiDesigner3d$__Closure_623_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_623_36*  __make___Closure_623_36(SuiDesigner3d$__Closure_623_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_623_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_623_36) , __fini___Closure_623_36) ));
	self->invoke = __fn___Closure_623_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_631_36(SuiDesigner3d$__Closure_631_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_631_36(SuiDesigner3d$__Closure_631_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_631_36*  __make___Closure_631_36(SuiDesigner3d$__Closure_631_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_631_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_631_36) , __fini___Closure_631_36) ));
	self->invoke = __fn___Closure_631_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_638_36(SuiDesigner3d$__Closure_638_36 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_523_16->self->printSceneTree(self->__var___Block_523_16->self) ;
}

static void  __fini___Closure_638_36(SuiDesigner3d$__Closure_638_36 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_638_36, __var___Block_523_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_638_36*  __make___Closure_638_36(SuiDesigner3d$__Closure_638_36 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_638_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_638_36) , __fini___Closure_638_36) ));
	self->invoke = __fn___Closure_638_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_638_36, __var___Block_523_16) , __var___Block_523_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_644_36(SuiDesigner3d$__Closure_644_36 *  self, SuiCore$MouseEvent *  me){
	SuiDialog$Toast_make("保存成功") ;
}

static void  __fini___Closure_644_36(SuiDesigner3d$__Closure_644_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_644_36*  __make___Closure_644_36(SuiDesigner3d$__Closure_644_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_644_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_644_36) , __fini___Closure_644_36) ));
	self->invoke = __fn___Closure_644_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_657_36(SuiDesigner3d$__Closure_657_36 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_523_16->self->invalidReact->invalid(self->__var___Block_523_16->self->invalidReact) ;
}

static void  __fini___Closure_657_36(SuiDesigner3d$__Closure_657_36 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_657_36, __var___Block_523_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_657_36*  __make___Closure_657_36(SuiDesigner3d$__Closure_657_36 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_657_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_657_36) , __fini___Closure_657_36) ));
	self->invoke = __fn___Closure_657_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_657_36, __var___Block_523_16) , __var___Block_523_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_672_36(SuiDesigner3d$__Closure_672_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_672_36(SuiDesigner3d$__Closure_672_36 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_672_36*  __make___Closure_672_36(SuiDesigner3d$__Closure_672_36 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_672_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_672_36) , __fini___Closure_672_36) ));
	self->invoke = __fn___Closure_672_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_699_49(SuiDesigner3d$__Closure_699_49 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex){
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpItem = (tmpItem=NULL,urgc_init_var_class((void**)&tmpItem, item));
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpDock = (tmpDock=NULL,urgc_init_var_class((void**)&tmpDock, dockLayoutIns));
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_704_28 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_704_28;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_704_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_2, "pointer") ) ;
		o->setText(o, item->id) ;
		o->color = self->__var___Block_523_16->t->dock_head_c;
		((SuiCore$View * )o)->padding.top = 4;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->padding, 8) ;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 0.0f, 0xffaeaeb2) ;
		bool  active = item->parent->tabActiveIndex == kidIndex;
		if (active) {
			((SuiCore$View * )o)->border->t->w = 2.f;
			((SuiCore$View * )o)->border->t->color = self->__var___Block_523_16->t->c_main;
		}
		if (kidIndex < item->parent->children->size(item->parent->children)  - 1) {
			((SuiCore$View * )o)->border->r->w = 1.f;
		}
		((SuiCore$View * )o)->backgroundColor = active ? self->__var___Block_523_16->t->dock_head_bg_active : self->__var___Block_523_16->t->dock_head_bg;
	}
}

static void  __fini___Closure_699_49(SuiDesigner3d$__Closure_699_49 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_699_49, __var___Block_523_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_699_49*  __make___Closure_699_49(SuiDesigner3d$__Closure_699_49 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_699_49*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_699_49) , __fini___Closure_699_49) ));
	self->invoke = __fn___Closure_699_49;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_699_49, __var___Block_523_16) , __var___Block_523_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$ViewBase *  __fn___Closure_732_52(SuiDesigner3d$__Closure_732_52 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o){
	if (Orc$String$equals(item->id, "project") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirTreeView*  tmpReturn_1 = NULL;
		{
			SuiDesigner$AssetDirTreeView*  __scopeVar_734_32 = SuiDesigner$mkAssetDirTreeView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_734_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_734_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_523_16->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "dir") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirView*  tmpReturn_2 = NULL;
		{
			SuiDesigner$AssetDirView*  __scopeVar_740_32 = SuiDesigner$mkAssetDirView(&tmpReturn_2, o, (long long )item) , *o = __scopeVar_740_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_740_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_523_16->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "hier") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SglSceneHierView*  tmpReturn_3 = NULL;
		{
			SuiDesigner$SglSceneHierView*  __scopeVar_746_32 = SuiDesigner$mkSglSceneHierView(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_746_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_746_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$SglSceneHierView, editCtx) , self->__var___Block_523_16->self->editCtx) ;
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "inspector") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SglInspView*  tmpReturn_4 = NULL;
		{
			SuiDesigner$SglInspView*  __scopeVar_754_32 = SuiDesigner$mkSglInspView(&tmpReturn_4, o, (long long )item) , *o = __scopeVar_754_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_754_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$SglInspView, editCtx) , self->__var___Block_523_16->self->editCtx) ;
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_523_16->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "scene") ) {
		return self->__var___Block_523_16->self->reactScene(self->__var___Block_523_16->self, o, item) ; 
	}
	if (Orc$String$equals(item->id, "inspector") ) {
		
	}
	if (Orc$String$equals(item->id, "layers") ) {
		
	}
	if (Orc$String$equals(item->id, "tilesets-list") ) {
		
	}
	if (Orc$String$equals(item->id, "tileset-preview") ) {
		
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_5 = NULL;
	{
		SuiView$TextView*  __scopeVar_786_28 = SuiView$mkTextView(&tmpReturn_5, o, (long long )item) , *o = __scopeVar_786_28;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_786_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
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
			SuiLayout$LayoutLinearCell*  __scopeVar_802_32 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_802_32;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_802_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		return o; 
	}
}

static void  __fini___Closure_732_52(SuiDesigner3d$__Closure_732_52 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_732_52, __var___Block_523_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_732_52*  __make___Closure_732_52(SuiDesigner3d$__Closure_732_52 **  __outRef__, SuiDesigner3d$__Block_523_16 *  __var___Block_523_16){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_732_52*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_732_52) , __fini___Closure_732_52) ));
	self->invoke = __fn___Closure_732_52;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_732_52, __var___Block_523_16) , __var___Block_523_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_862_35(SuiDesigner3d$__Closure_862_35 *  self){
	{
		SuiCore$ViewBase*  o = self->__var___Block_858_32->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_863_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
		{
			SuiView$TextView*  __scopeVar_864_16 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_864_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_864_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			o->setText(o, Orc$str(&tmpReturn_2, "tileWidth:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_3 = NULL;
		{
			SuiView$EditText*  __scopeVar_867_16 = SuiView$mkEditText(&tmpReturn_3, o, 0) , *o = __scopeVar_867_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_867_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
		{
			SuiView$TextView*  __scopeVar_876_16 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_876_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_876_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
			o->setText(o, Orc$str(&tmpReturn_5, "tileHeight:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
		{
			SuiView$EditText*  __scopeVar_879_16 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_879_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_879_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			
		}
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
		{
			SuiView$TextView*  __scopeVar_888_16 = SuiView$mkTextView(&tmpReturn_7, o, 0) , *o = __scopeVar_888_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_888_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
			o->setText(o, Orc$str(&tmpReturn_8, "fps:") ) ;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_9 = NULL;
		{
			SuiView$EditText*  __scopeVar_891_16 = SuiView$mkEditText(&tmpReturn_9, o, 0) , *o = __scopeVar_891_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_891_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			
		}
		URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_10 = NULL;
		{
			SuiView$DrawButton*  __scopeVar_905_16 = SuiView$mkDrawButton(&tmpReturn_10, o, 0) , *o = __scopeVar_905_16;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_905_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_11, "提交") ) ;
			URGC_VAR_CLEANUP SuiDesigner3d$__Closure_907_32*  tmpReturn_12 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_907_32(&tmpReturn_12, self->__var___Block_858_32) ) ;
		}
	}
}

static void  __fini___Closure_862_35(SuiDesigner3d$__Closure_862_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_862_35, __var___Block_858_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_862_35*  __make___Closure_862_35(SuiDesigner3d$__Closure_862_35 **  __outRef__, SuiDesigner3d$__Block_858_32 *  __var___Block_858_32){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_862_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_862_35) , __fini___Closure_862_35) ));
	self->invoke = __fn___Closure_862_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_862_35, __var___Block_858_32) , __var___Block_858_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_907_32(SuiDesigner3d$__Closure_907_32 *  self, SuiCore$MouseEvent *  me){
	(*(self->__var___Block_858_32->reactMapSetting))((void * )(self->__var___Block_858_32->reactMapSetting)) ;
}

static void  __fini___Closure_907_32(SuiDesigner3d$__Closure_907_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_907_32, __var___Block_858_32) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_907_32*  __make___Closure_907_32(SuiDesigner3d$__Closure_907_32 **  __outRef__, SuiDesigner3d$__Block_858_32 *  __var___Block_858_32){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_907_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_907_32) , __fini___Closure_907_32) ));
	self->invoke = __fn___Closure_907_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_907_32, __var___Block_858_32) , __var___Block_858_32) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_983_26(SuiDesigner3d$__Closure_983_26 *  self, SuiCore$Event *  e){
	self->__var___Block_962_21->self->onWindowEvent(self->__var___Block_962_21->self, e) ;
}

static void  __fini___Closure_983_26(SuiDesigner3d$__Closure_983_26 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_983_26, __var___Block_962_21) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner3d$__Closure_983_26*  __make___Closure_983_26(SuiDesigner3d$__Closure_983_26 **  __outRef__, SuiDesigner3d$__Block_962_21 *  __var___Block_962_21){
	URGC_VAR_CLEANUP SuiDesigner3d$__Closure_983_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner3d$__Closure_983_26) , __fini___Closure_983_26) ));
	self->invoke = __fn___Closure_983_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner3d$__Closure_983_26, __var___Block_962_21) , __var___Block_962_21) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



