
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
typedef struct tagHoroEditor$__Block_221_51 HoroEditor$__Block_221_51;

typedef struct tagHoroEditor$__Block_298_30 HoroEditor$__Block_298_30;

typedef struct tagHoroEditor$__Block_301_27 HoroEditor$__Block_301_27;

typedef struct tagHoroEditor$__Block_351_35 HoroEditor$__Block_351_35;

typedef struct tagHoroEditor$__Block_367_33 HoroEditor$__Block_367_33;

typedef struct tagHoroEditor$__Block_533_21 HoroEditor$__Block_533_21;

typedef struct tagHoroEditor$__Closure_185_27 HoroEditor$__Closure_185_27;

typedef struct tagHoroEditor$__Closure_225_26 HoroEditor$__Closure_225_26;

typedef struct tagHoroEditor$__Closure_230_36 HoroEditor$__Closure_230_36;

typedef struct tagHoroEditor$__Closure_269_26 HoroEditor$__Closure_269_26;

typedef struct tagHoroEditor$__Closure_309_43 HoroEditor$__Closure_309_43;

typedef struct tagHoroEditor$__Closure_onActive_310 HoroEditor$__Closure_onActive_310;

typedef struct tagHoroEditor$__Closure_355_36 HoroEditor$__Closure_355_36;

typedef struct tagHoroEditor$__Closure_359_31 HoroEditor$__Closure_359_31;

typedef struct tagHoroEditor$__Closure_376_41 HoroEditor$__Closure_376_41;

typedef struct tagHoroEditor$__Closure_406_44 HoroEditor$__Closure_406_44;

typedef struct tagHoroEditor$__Closure_539_26 HoroEditor$__Closure_539_26;



struct tagHoroEditor$__Block_221_51 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_298_30 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_301_27 {
	SuiDesigner$MenuBarCtrl*  group ;
};





struct tagHoroEditor$__Block_351_35 {
	SuiView$MenuButton*  mbutton ;
};





struct tagHoroEditor$__Block_367_33 {
	SuiDesigner$Theme *  t ;
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Block_533_21 {
	HoroEditor$HoroEditor*  self ;
};





struct tagHoroEditor$__Closure_185_27 {
	void  (*invoke)(HoroEditor$__Closure_185_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_225_26 {
	void  (*invoke)(HoroEditor$__Closure_225_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_221_51*  __var___Block_221_51 ;
};





struct tagHoroEditor$__Closure_230_36 {
	void  (*invoke)(HoroEditor$__Closure_230_36 *  self);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_221_51*  __var___Block_221_51 ;
};





struct tagHoroEditor$__Closure_269_26 {
	void  (*invoke)(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
};





struct tagHoroEditor$__Closure_309_43 {
	SuiView$MenuNativeItem*  (*invoke)(HoroEditor$__Closure_309_43 *  self, SuiView$MenuButton *  mbutton);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_298_30*  __var___Block_298_30 ;
};





struct tagHoroEditor$__Closure_onActive_310 {
	void  (*invoke)(HoroEditor$__Closure_onActive_310 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_298_30*  __var___Block_298_30 ;
};





struct tagHoroEditor$__Closure_355_36 {
	void  (*invoke)(HoroEditor$__Closure_355_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_301_27*  __var___Block_301_27 ;
	HoroEditor$__Block_351_35*  __var___Block_351_35 ;
};





struct tagHoroEditor$__Closure_359_31 {
	void  (*invoke)(HoroEditor$__Closure_359_31 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_301_27*  __var___Block_301_27 ;
	HoroEditor$__Block_351_35*  __var___Block_351_35 ;
};





struct tagHoroEditor$__Closure_376_41 {
	void  (*invoke)(HoroEditor$__Closure_376_41 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_367_33*  __var___Block_367_33 ;
};





struct tagHoroEditor$__Closure_406_44 {
	SuiCore$ViewBase *  (*invoke)(HoroEditor$__Closure_406_44 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_367_33*  __var___Block_367_33 ;
};





struct tagHoroEditor$__Closure_539_26 {
	void  (*invoke)(HoroEditor$__Closure_539_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_533_21*  __var___Block_533_21 ;
};





// static function declaration
static void  __finiBlock___Block_221_51(HoroEditor$__Block_221_51 *  self);
static void  __finiBlock___Block_298_30(HoroEditor$__Block_298_30 *  self);
static void  __finiBlock___Block_301_27(HoroEditor$__Block_301_27 *  self);
static void  __finiBlock___Block_351_35(HoroEditor$__Block_351_35 *  self);
static void  __finiBlock___Block_367_33(HoroEditor$__Block_367_33 *  self);
static void  __finiBlock___Block_533_21(HoroEditor$__Block_533_21 *  self);
static void  __fn___Closure_185_27(HoroEditor$__Closure_185_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_185_27(HoroEditor$__Closure_185_27 *  self);
static HoroEditor$__Closure_185_27*  __make___Closure_185_27(HoroEditor$__Closure_185_27 **  __outRef__);
static void  __fn___Closure_225_26(HoroEditor$__Closure_225_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_225_26(HoroEditor$__Closure_225_26 *  self);
static HoroEditor$__Closure_225_26*  __make___Closure_225_26(HoroEditor$__Closure_225_26 **  __outRef__, HoroEditor$__Block_221_51 *  __var___Block_221_51);
static void  __fn___Closure_230_36(HoroEditor$__Closure_230_36 *  self);
static void  __fini___Closure_230_36(HoroEditor$__Closure_230_36 *  self);
static HoroEditor$__Closure_230_36*  __make___Closure_230_36(HoroEditor$__Closure_230_36 **  __outRef__, HoroEditor$__Block_221_51 *  __var___Block_221_51);
static void  __fn___Closure_269_26(HoroEditor$__Closure_269_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_269_26(HoroEditor$__Closure_269_26 *  self);
static HoroEditor$__Closure_269_26*  __make___Closure_269_26(HoroEditor$__Closure_269_26 **  __outRef__);
static SuiView$MenuNativeItem*  __fn___Closure_309_43(SuiView$MenuNativeItem **  __outRef__, HoroEditor$__Closure_309_43 *  self, SuiView$MenuButton *  mbutton);
static void  __fini___Closure_309_43(HoroEditor$__Closure_309_43 *  self);
static HoroEditor$__Closure_309_43*  __make___Closure_309_43(HoroEditor$__Closure_309_43 **  __outRef__, HoroEditor$__Block_298_30 *  __var___Block_298_30);
static void  __fn___Closure_onActive_310(HoroEditor$__Closure_onActive_310 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_onActive_310(HoroEditor$__Closure_onActive_310 *  self);
static HoroEditor$__Closure_onActive_310*  __make___Closure_onActive_310(HoroEditor$__Closure_onActive_310 **  __outRef__, HoroEditor$__Block_298_30 *  __var___Block_298_30);
static void  __fn___Closure_355_36(HoroEditor$__Closure_355_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_355_36(HoroEditor$__Closure_355_36 *  self);
static HoroEditor$__Closure_355_36*  __make___Closure_355_36(HoroEditor$__Closure_355_36 **  __outRef__, HoroEditor$__Block_301_27 *  __var___Block_301_27, HoroEditor$__Block_351_35 *  __var___Block_351_35);
static void  __fn___Closure_359_31(HoroEditor$__Closure_359_31 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_359_31(HoroEditor$__Closure_359_31 *  self);
static HoroEditor$__Closure_359_31*  __make___Closure_359_31(HoroEditor$__Closure_359_31 **  __outRef__, HoroEditor$__Block_301_27 *  __var___Block_301_27, HoroEditor$__Block_351_35 *  __var___Block_351_35);
static void  __fn___Closure_376_41(HoroEditor$__Closure_376_41 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex);
static void  __fini___Closure_376_41(HoroEditor$__Closure_376_41 *  self);
static HoroEditor$__Closure_376_41*  __make___Closure_376_41(HoroEditor$__Closure_376_41 **  __outRef__, HoroEditor$__Block_367_33 *  __var___Block_367_33);
static SuiCore$ViewBase *  __fn___Closure_406_44(HoroEditor$__Closure_406_44 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o);
static void  __fini___Closure_406_44(HoroEditor$__Closure_406_44 *  self);
static HoroEditor$__Closure_406_44*  __make___Closure_406_44(HoroEditor$__Closure_406_44 **  __outRef__, HoroEditor$__Block_367_33 *  __var___Block_367_33);
static void  __fn___Closure_539_26(HoroEditor$__Closure_539_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_539_26(HoroEditor$__Closure_539_26 *  self);
static HoroEditor$__Closure_539_26*  __make___Closure_539_26(HoroEditor$__Closure_539_26 **  __outRef__, HoroEditor$__Block_533_21 *  __var___Block_533_21);


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
	orc_metaField_class(&pNext, "invalidReact", ((Vtable_Object*)Vtable_SuiDesigner$InvalidReact_init(0)), offsetof(HoroEditor$HoroEditor, invalidReact), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(HoroEditor$HoroEditor, drag), true, false, 1);
	orc_metaField_class(&pNext, "viewCb", ((Vtable_Object*)Vtable_HoroEditor$HoroEditorSceneViewCallback_init(0)), offsetof(HoroEditor$HoroEditor, viewCb), true, false, 1);
	orc_metaField_class(&pNext, "toolMgr", ((Vtable_Object*)Vtable_SuiDesigner$ToolMgr_init(0)), offsetof(HoroEditor$HoroEditor, toolMgr), true, false, 1);
	orc_metaField_class(&pNext, "sglGizmo", ((Vtable_Object*)Vtable_SuiDesigner$SglGizmo_init(0)), offsetof(HoroEditor$HoroEditor, sglGizmo), true, false, 1);
	orc_metaField_class(&pNext, "sceneView", ((Vtable_Object*)Vtable_Sgl$SglSceneView_init(0)), offsetof(HoroEditor$HoroEditor, sceneView), true, false, 1);
	orc_metaField_class(&pNext, "gizmosView", ((Vtable_Object*)Vtable_SuiCore$View_init(0)), offsetof(HoroEditor$HoroEditor, gizmosView), true, false, 1);

	orc_metaField_method(&pNext, "onSceneEvent", offsetof(HoroEditor$HoroEditor, onSceneEvent));
	orc_metaField_method(&pNext, "_afterDrawScene", offsetof(HoroEditor$HoroEditor, _afterDrawScene));
	orc_metaField_method(&pNext, "reactScene_forViewBase", offsetof(HoroEditor$HoroEditor, reactScene_forViewBase));
	orc_metaField_method(&pNext, "reactScene_forObj3d", offsetof(HoroEditor$HoroEditor, reactScene_forObj3d));
	orc_metaField_method(&pNext, "reactScene", offsetof(HoroEditor$HoroEditor, reactScene));
	orc_metaField_method(&pNext, "reactGizmosView", offsetof(HoroEditor$HoroEditor, reactGizmosView));
	orc_metaField_method(&pNext, "reactMenubar", offsetof(HoroEditor$HoroEditor, reactMenubar));
	orc_metaField_method(&pNext, "reactDocklayout", offsetof(HoroEditor$HoroEditor, reactDocklayout));
	orc_metaField_method(&pNext, "react", offsetof(HoroEditor$HoroEditor, react));
	orc_metaField_method(&pNext, "onWindowEvent", offsetof(HoroEditor$HoroEditor, onWindowEvent));
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
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroEditor*)self)->gizmosView, NULL);
    }
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
	((HoroEditor$HoroEditor*)self)->react = (void*)HoroEditor$HoroEditor$react;
	((HoroEditor$HoroEditor*)self)->onWindowEvent = (void*)HoroEditor$HoroEditor$onWindowEvent;
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
	URGC_VAR_CLEANUP HoroEditor$__Closure_185_27*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_185_27(&tmpReturn_1) ) ;
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
	else if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiDesigner$EventANodeChanged_init(NULL))) {
		SuiDesigner$EventANodeChanged *  e = (SuiDesigner$EventANodeChanged * )e;
		self->invalidReact->invalid(self->invalidReact) ;
	}
}


void  HoroEditor$HoroEditor$reactScene_forViewBase(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiDesigner$ANode *  anode){
	SuiCore$ViewBase *  root = (SuiCore$ViewBase * )anode->node;
	if (root) {
		SuiCore$Node$placeKid(o, root) ;
	}
}


void  HoroEditor$HoroEditor$reactScene_forObj3d(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiDesigner$ANode *  anode){
	URGC_VAR_CLEANUP HoroEditor$__Block_221_51*  __var___Block_221_51 = (__var___Block_221_51=NULL,urgc_init_var((void**)&__var___Block_221_51, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_221_51) , __finiBlock___Block_221_51) ));
	urgc_set_field_class(__var___Block_221_51, (void * )offsetof(HoroEditor$__Block_221_51, self) , self) ;
	Sgl$Obj3d *  root = (Sgl$Obj3d * )anode->node;
	URGC_VAR_CLEANUP_CLASS Sgl$SglSceneView*  tmpReturn_1 = NULL;
	{
		Sgl$SglSceneView*  __scopeVar_223_8 = Sgl$mkSglSceneView(&tmpReturn_1, o, 0) , *o = __scopeVar_223_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_223_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_field_class(o, (void * )offsetof(SuiCore$View, cb) , self->viewCb) ;
		URGC_VAR_CLEANUP HoroEditor$__Closure_225_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_225_26(&tmpReturn_2, __var___Block_221_51) ) ;
		urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, sceneView) , o) ;
		URGC_VAR_CLEANUP HoroEditor$__Closure_230_36*  tmpReturn_3 = NULL;
		urgc_set_field(o->drawCtx, (void * )offsetof(Sgl$DrawCtx, cbAfterDraw) , __make___Closure_230_36(&tmpReturn_3, __var___Block_221_51) ) ;
		((SuiCore$View * )o)->backgroundColor = 0x00ffffff;
		((SuiView$ImageView * )o)->setImageMode(o, SuiView$Cover) ;
		if (((SuiCore$Node * )o)->isNewForReact) {
			o->mkBaseScene(o) ;
			self->editCtx->setSceneView(self->editCtx, o) ;
			SuiCore$Emitter *  tmpThis_1 = NULL;
			URGC_VAR_CLEANUP_CLASS HoroEditor$EventHoroSceneChanged*  tmpNewOwner_4 = NULL;
			(tmpThis_1 = SuiCore$useEbus() )->emit(tmpThis_1, HoroEditor$EventHoroSceneChanged_new(&tmpNewOwner_4) ) ;
			o->buildDrawObj(o) ;
		}
		((SuiCore$View * )o)->width = 500;
		((SuiCore$View * )o)->height = 500;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_5 = NULL;
		{
			SuiLayout$LayoutAlignPositionCell*  __scopeVar_248_12 = SuiLayout$layoutAlignPositionCell(&tmpReturn_5, o, 0) , *o = __scopeVar_248_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_248_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->left = 0;
			o->top = 0;
			o->right = 0;
			o->bottom = 0;
		}
		URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_6 = NULL;
		{
			SuiCore$View*  __scopeVar_254_12 = SuiView$mkView(&tmpReturn_6, o, 0) , *o = __scopeVar_254_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_254_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, gizmosView) , o) ;
		}
	}
}


SuiCore$ViewBase *  HoroEditor$HoroEditor$reactScene(HoroEditor$HoroEditor *  self, SuiCore$Node *  o, SuiView$DockItem *  item){
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutAlign*  __scopeVar_263_8 = SuiLayout$layoutAlign(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_263_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_263_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = 0xffefefef;
		o->useMaxConstraint = false;
		((SuiCore$View * )o)->needClip = true;
		URGC_VAR_CLEANUP HoroEditor$__Closure_269_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_269_26(&tmpReturn_2) ) ;
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
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_293_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		self->toolMgr->reactGizmosView(self->toolMgr, self->gizmosView) ;
	}
}


void  HoroEditor$HoroEditor$reactMenubar(HoroEditor$HoroEditor *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP HoroEditor$__Block_298_30*  __var___Block_298_30 = (__var___Block_298_30=NULL,urgc_init_var((void**)&__var___Block_298_30, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_298_30) , __finiBlock___Block_298_30) ));
	urgc_set_field_class(__var___Block_298_30, (void * )offsetof(HoroEditor$__Block_298_30, self) , self) ;
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_301_8 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_301_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_301_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP HoroEditor$__Block_301_27*  __var___Block_301_27 = (__var___Block_301_27=NULL,urgc_init_var((void**)&__var___Block_301_27, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_301_27) , __finiBlock___Block_301_27) ));
		((SuiCore$View * )o)->backgroundColor = t->menubar_bg;
		SuiCore$Inset$setAxis(&((SuiCore$View * )o)->padding, 0, 6) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  btnsStr = Orc$str((btnsStr = NULL,&btnsStr), "文件,项目,视图,调试,窗口,帮助") ;
		URGC_VAR_CLEANUP_CLASS Orc$List*  btns = Orc$String$splitByRe((btns = NULL,&btns), btnsStr, ",") ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$MenuBarCtrl*  tmpNewOwner_2 = NULL;
		urgc_set_field_class(__var___Block_301_27, (void * )offsetof(HoroEditor$__Block_301_27, group) , SuiDesigner$MenuBarCtrl_new(&tmpNewOwner_2) ) ;
		URGC_VAR_CLEANUP HoroEditor$__Closure_309_43*  tmpReturn_3 = NULL;
		urgc_set_field(__var___Block_301_27->group, (void * )offsetof(SuiDesigner$MenuBarCtrl, cbCreateMenuNativeItem) , __make___Closure_309_43(&tmpReturn_3, __var___Block_298_30) ) ;
		for (int  i = 0; i < btns->size(btns) ; i++) {
			Object *  obj = btns->get(btns, i) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  btn = (btn=NULL,urgc_init_var_class((void**)&btn, (Orc$String* )btns->get(btns, i) ));
			URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  tmpReturn_4 = NULL;
			{
				SuiView$MenuButton*  __scopeVar_351_16 = SuiView$mkMenuButton(&tmpReturn_4, o, i) , *o = __scopeVar_351_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_351_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP HoroEditor$__Block_351_35*  __var___Block_351_35 = (__var___Block_351_35=NULL,urgc_init_var((void**)&__var___Block_351_35, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_351_35) , __finiBlock___Block_351_35) ));
				urgc_set_field_class(__var___Block_351_35, (void * )offsetof(HoroEditor$__Block_351_35, mbutton) , o) ;
				urgc_set_field_class(o, (void * )offsetof(SuiView$MenuButton, text) , btn) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_355_36*  tmpReturn_5 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onMouseMove) , __make___Closure_355_36(&tmpReturn_5, __var___Block_301_27, __var___Block_351_35) ) ;
				URGC_VAR_CLEANUP HoroEditor$__Closure_359_31*  tmpReturn_6 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onClick) , __make___Closure_359_31(&tmpReturn_6, __var___Block_301_27, __var___Block_351_35) ) ;
			}
		}
	}
}


void  HoroEditor$HoroEditor$reactDocklayout(HoroEditor$HoroEditor *  self, SuiCore$Node *  o){
	URGC_VAR_CLEANUP HoroEditor$__Block_367_33*  __var___Block_367_33 = (__var___Block_367_33=NULL,urgc_init_var((void**)&__var___Block_367_33, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_367_33) , __finiBlock___Block_367_33) ));
	urgc_set_field_class(__var___Block_367_33, (void * )offsetof(HoroEditor$__Block_367_33, self) , self) ;
	__var___Block_367_33->t = SuiDesigner$themeIns() ;
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpReturn_1 = NULL;
	{
		SuiView$DockLayout*  __scopeVar_369_8 = SuiView$dockLayout(&tmpReturn_1, o, 0) , *o = __scopeVar_369_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_369_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		urgc_set_var_class(&dockLayoutIns, o) ;
		((SuiCore$View * )o)->width = 100;
		((SuiCore$View * )o)->height = 20;
		((SuiCore$View * )o)->backgroundColor = 0x30000033;
		if (((SuiCore$Node * )o)->isNewForReact) {
			URGC_VAR_CLEANUP HoroEditor$__Closure_376_41*  tmpReturn_2 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemHeadView) , __make___Closure_376_41(&tmpReturn_2, __var___Block_367_33) ) ;
			URGC_VAR_CLEANUP HoroEditor$__Closure_406_44*  tmpReturn_3 = NULL;
			urgc_set_field(o, (void * )offsetof(SuiView$DockLayout, cbRenderItemContentView) , __make___Closure_406_44(&tmpReturn_3, __var___Block_367_33) ) ;
			{
				SuiView$DockItem*  __scopeVar_463_16 = o->root, *o = __scopeVar_463_16;
				
			
				o->isHorizontal = false;
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_4 = NULL;
				{
					SuiView$DockItem*  __scopeVar_466_20 = SuiView$mkDockItemSplitter(&tmpReturn_4, o, NULL, true) , *o = __scopeVar_466_20;
					
				
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_5 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
					{
						SuiView$DockItem*  __scopeVar_467_24 = SuiView$mkDockItem(&tmpReturn_5, o, Orc$str(&tmpReturn_6, "hier") ) , *o = __scopeVar_467_24;
						
					
						o->intId = 0;
						o->width = 150;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_7 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
					{
						SuiView$DockItem*  __scopeVar_471_24 = SuiView$mkDockItem(&tmpReturn_7, o, Orc$str(&tmpReturn_8, "scene") ) , *o = __scopeVar_471_24;
						
					
						o->intId = 0;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_9 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					{
						SuiView$DockItem*  __scopeVar_474_24 = SuiView$mkDockItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "inspector") ) , *o = __scopeVar_474_24;
						
					
						o->intId = 0;
						o->width = 150;
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_11 = NULL;
				{
					SuiView$DockItem*  __scopeVar_479_20 = SuiView$mkDockItemSplitter(&tmpReturn_11, o, NULL, true) , *o = __scopeVar_479_20;
					
				
					o->width = 150;
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_12 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
					{
						SuiView$DockItem*  __scopeVar_481_24 = SuiView$mkDockItem(&tmpReturn_12, o, Orc$str(&tmpReturn_13, "project") ) , *o = __scopeVar_481_24;
						
					
						o->intId = 0;
						o->width = 160;
					}
					URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpReturn_14 = NULL;
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
					{
						SuiView$DockItem*  __scopeVar_485_24 = SuiView$mkDockItem(&tmpReturn_14, o, Orc$str(&tmpReturn_15, "dir") ) , *o = __scopeVar_485_24;
						
					
						o->intId = 0;
					}
				}
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_16 = NULL;
		SuiLayout$layoutLinearCell(&tmpReturn_16, o, 0) ;
	}
}


void  HoroEditor$HoroEditor$react(HoroEditor$HoroEditor *  self){
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_498_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		self->reactMenubar(self, o) ;
		self->reactDocklayout(self, o) ;
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


void  HoroEditor$HoroEditor$showWindow(HoroEditor$HoroEditor *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_533_21*  __var___Block_533_21 = (__var___Block_533_21=NULL,urgc_init_var((void**)&__var___Block_533_21, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_533_21) , __finiBlock___Block_533_21) ));
	urgc_set_field_class(__var___Block_533_21, (void * )offsetof(HoroEditor$__Block_533_21, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroEditor, win) , Sui$Window_new(&tmpNewOwner_1) ) ;
	{
		Sui$Window*  o = self->win;
		
	
		URGC_VAR_CLEANUP HoroEditor$__Closure_539_26*  tmpReturn_2 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_539_26(&tmpReturn_2, __var___Block_533_21) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_3 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_3) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_543_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
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
	SuiDesigner$registerNodes() ;
	Orc$Path_setcwd(path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  abspath = Orc$Path_toAbsolute((abspath = NULL,&abspath), path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  cwd = Orc$Path_getcwd((cwd = NULL,&cwd)) ;
	printf("打开项目。 项目路径为:%s. cwd:%s", abspath->str, cwd->str) ;
	SuiDesigner$Project *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_1) )->init(tmpThis_1, abspath->str) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	self->editCtx->openPrefab(self->editCtx, "prefab/3d.prefab.json") ;
	self->showWindow(self) ;
	win->close(win) ;
}



static void  __finiBlock___Block_221_51(HoroEditor$__Block_221_51 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_221_51, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_298_30(HoroEditor$__Block_298_30 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_298_30, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_301_27(HoroEditor$__Block_301_27 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_301_27, group) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_351_35(HoroEditor$__Block_351_35 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_351_35, mbutton) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_367_33(HoroEditor$__Block_367_33 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_367_33, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_533_21(HoroEditor$__Block_533_21 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_533_21, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_185_27(HoroEditor$__Closure_185_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("isDragging tileset\n") ;
	}
}

static void  __fini___Closure_185_27(HoroEditor$__Closure_185_27 *  self){
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_185_27*  __make___Closure_185_27(HoroEditor$__Closure_185_27 **  __outRef__){
	URGC_VAR_CLEANUP HoroEditor$__Closure_185_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_185_27) , __fini___Closure_185_27) ));
	self->invoke = __fn___Closure_185_27;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_225_26(HoroEditor$__Closure_225_26 *  self, SuiCore$Event *  e){
	self->__var___Block_221_51->self->onSceneEvent(self->__var___Block_221_51->self, e) ;
}

static void  __fini___Closure_225_26(HoroEditor$__Closure_225_26 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_225_26, __var___Block_221_51) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_225_26*  __make___Closure_225_26(HoroEditor$__Closure_225_26 **  __outRef__, HoroEditor$__Block_221_51 *  __var___Block_221_51){
	URGC_VAR_CLEANUP HoroEditor$__Closure_225_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_225_26) , __fini___Closure_225_26) ));
	self->invoke = __fn___Closure_225_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_225_26, __var___Block_221_51) , __var___Block_221_51) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_230_36(HoroEditor$__Closure_230_36 *  self){
	self->__var___Block_221_51->self->_afterDrawScene(self->__var___Block_221_51->self) ;
}

static void  __fini___Closure_230_36(HoroEditor$__Closure_230_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_230_36, __var___Block_221_51) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_230_36*  __make___Closure_230_36(HoroEditor$__Closure_230_36 **  __outRef__, HoroEditor$__Block_221_51 *  __var___Block_221_51){
	URGC_VAR_CLEANUP HoroEditor$__Closure_230_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_230_36) , __fini___Closure_230_36) ));
	self->invoke = __fn___Closure_230_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_230_36, __var___Block_221_51) , __var___Block_221_51) ;
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

static SuiView$MenuNativeItem*  __fn___Closure_309_43(SuiView$MenuNativeItem **  __outRef__, HoroEditor$__Closure_309_43 *  self, SuiView$MenuButton *  mbutton){
	URGC_VAR_CLEANUP void  (**onActive)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_310*  tmpReturn_1 = NULL;
	(urgc_set_var(&onActive, __make___Closure_onActive_310(&tmpReturn_1, self->__var___Block_298_30) ) );
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
				SuiView$MenuNativeItem*  __scopeVar_326_24 = SuiView$mkMenuNativeItem(&tmpReturn_9, o, Orc$str(&tmpReturn_10, "最近打开") , onActive) , *o = __scopeVar_326_24;
				
			
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

static void  __fini___Closure_309_43(HoroEditor$__Closure_309_43 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_309_43, __var___Block_298_30) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_309_43*  __make___Closure_309_43(HoroEditor$__Closure_309_43 **  __outRef__, HoroEditor$__Block_298_30 *  __var___Block_298_30){
	URGC_VAR_CLEANUP HoroEditor$__Closure_309_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_309_43) , __fini___Closure_309_43) ));
	self->invoke = __fn___Closure_309_43;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_309_43, __var___Block_298_30) , __var___Block_298_30) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_onActive_310(HoroEditor$__Closure_onActive_310 *  self, SuiView$MenuNativeItem *  item){
	printf("\n\n========================================onActive menu:%s\n", item->label->str) ;
	if (Orc$String$equals(item->label, "退出") ) {
		exit(0) ;
	}
	if (Orc$String$equals(item->label, "保存场景") ) {
		HoroEditor$UiAct_savePrefab(self->__var___Block_298_30->self) ;
		return ; 
	}
	SuiDialog$Toast_make(item->label->str) ;
}

static void  __fini___Closure_onActive_310(HoroEditor$__Closure_onActive_310 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_310, __var___Block_298_30) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_onActive_310*  __make___Closure_onActive_310(HoroEditor$__Closure_onActive_310 **  __outRef__, HoroEditor$__Block_298_30 *  __var___Block_298_30){
	URGC_VAR_CLEANUP HoroEditor$__Closure_onActive_310*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_onActive_310) , __fini___Closure_onActive_310) ));
	self->invoke = __fn___Closure_onActive_310;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_onActive_310, __var___Block_298_30) , __var___Block_298_30) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_355_36(HoroEditor$__Closure_355_36 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_301_27->group->onmove(self->__var___Block_301_27->group, self->__var___Block_351_35->mbutton, me) ;
}

static void  __fini___Closure_355_36(HoroEditor$__Closure_355_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_355_36, __var___Block_301_27) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_355_36, __var___Block_351_35) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_355_36*  __make___Closure_355_36(HoroEditor$__Closure_355_36 **  __outRef__, HoroEditor$__Block_301_27 *  __var___Block_301_27, HoroEditor$__Block_351_35 *  __var___Block_351_35){
	URGC_VAR_CLEANUP HoroEditor$__Closure_355_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_355_36) , __fini___Closure_355_36) ));
	self->invoke = __fn___Closure_355_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_355_36, __var___Block_301_27) , __var___Block_301_27) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_355_36, __var___Block_351_35) , __var___Block_351_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_359_31(HoroEditor$__Closure_359_31 *  self, SuiCore$MouseEvent *  me){
	self->__var___Block_301_27->group->onclick(self->__var___Block_301_27->group, self->__var___Block_351_35->mbutton, me) ;
}

static void  __fini___Closure_359_31(HoroEditor$__Closure_359_31 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_359_31, __var___Block_301_27) , NULL) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_359_31, __var___Block_351_35) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_359_31*  __make___Closure_359_31(HoroEditor$__Closure_359_31 **  __outRef__, HoroEditor$__Block_301_27 *  __var___Block_301_27, HoroEditor$__Block_351_35 *  __var___Block_351_35){
	URGC_VAR_CLEANUP HoroEditor$__Closure_359_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_359_31) , __fini___Closure_359_31) ));
	self->invoke = __fn___Closure_359_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_359_31, __var___Block_301_27) , __var___Block_301_27) ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_359_31, __var___Block_351_35) , __var___Block_351_35) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_376_41(HoroEditor$__Closure_376_41 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o, int  kidIndex){
	URGC_VAR_CLEANUP_CLASS SuiView$DockItem*  tmpItem = (tmpItem=NULL,urgc_init_var_class((void**)&tmpItem, item));
	URGC_VAR_CLEANUP_CLASS SuiView$DockLayout*  tmpDock = (tmpDock=NULL,urgc_init_var_class((void**)&tmpDock, dockLayoutIns));
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
	{
		SuiView$TextView*  __scopeVar_381_20 = SuiView$mkTextView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_381_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_381_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$ViewBase, cursor) , Orc$str(&tmpReturn_2, "pointer") ) ;
		o->setText(o, item->id) ;
		o->color = self->__var___Block_367_33->t->dock_head_c;
		((SuiCore$View * )o)->padding.top = 4;
		SuiCore$Inset$setHor(&((SuiCore$View * )o)->padding, 8) ;
		((SuiCore$View * )o)->border->setAll(((SuiCore$View * )o)->border, 0.0f, 0xffaeaeb2) ;
		bool  active = item->parent->tabActiveIndex == kidIndex;
		if (active) {
			((SuiCore$View * )o)->border->t->w = 2.f;
			((SuiCore$View * )o)->border->t->color = self->__var___Block_367_33->t->c_main;
		}
		if (kidIndex < item->parent->children->size(item->parent->children)  - 1) {
			((SuiCore$View * )o)->border->r->w = 1.f;
		}
		((SuiCore$View * )o)->backgroundColor = active ? self->__var___Block_367_33->t->dock_head_bg_active : self->__var___Block_367_33->t->dock_head_bg;
	}
}

static void  __fini___Closure_376_41(HoroEditor$__Closure_376_41 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_376_41, __var___Block_367_33) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_376_41*  __make___Closure_376_41(HoroEditor$__Closure_376_41 **  __outRef__, HoroEditor$__Block_367_33 *  __var___Block_367_33){
	URGC_VAR_CLEANUP HoroEditor$__Closure_376_41*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_376_41) , __fini___Closure_376_41) ));
	self->invoke = __fn___Closure_376_41;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_376_41, __var___Block_367_33) , __var___Block_367_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static SuiCore$ViewBase *  __fn___Closure_406_44(HoroEditor$__Closure_406_44 *  self, SuiView$DockItem *  item, SuiCore$ViewBase *  o){
	if (Orc$String$equals(item->id, "project") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirTreeView*  tmpReturn_1 = NULL;
		{
			SuiDesigner$AssetDirTreeView*  __scopeVar_408_24 = SuiDesigner$mkAssetDirTreeView(&tmpReturn_1, o, (long long )item) , *o = __scopeVar_408_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_408_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_367_33->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "dir") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$AssetDirView*  tmpReturn_2 = NULL;
		{
			SuiDesigner$AssetDirView*  __scopeVar_414_24 = SuiDesigner$mkAssetDirView(&tmpReturn_2, o, (long long )item) , *o = __scopeVar_414_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_414_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_367_33->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "hier") ) {
		URGC_VAR_CLEANUP_CLASS HoroEditor$HoroSceneHierView*  tmpReturn_3 = NULL;
		{
			HoroEditor$HoroSceneHierView*  __scopeVar_420_24 = HoroEditor$mkHoroSceneHierView(&tmpReturn_3, o, (long long )item) , *o = __scopeVar_420_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_420_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field_class(o, (void * )offsetof(HoroEditor$HoroSceneHierView, editCtx) , self->__var___Block_367_33->self->editCtx) ;
			urgc_set_field_class(o, (void * )offsetof(HoroEditor$HoroSceneHierView, editor) , self->__var___Block_367_33->self) ;
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "inspector") ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$SglInspView*  tmpReturn_4 = NULL;
		{
			SuiDesigner$SglInspView*  __scopeVar_429_24 = SuiDesigner$mkSglInspView(&tmpReturn_4, o, (long long )item) , *o = __scopeVar_429_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_429_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			urgc_set_field(o, (void * )offsetof(SuiDesigner$SglInspView, editCtx) , self->__var___Block_367_33->self->editCtx) ;
			((SuiCore$View * )o)->backgroundColor = self->__var___Block_367_33->t->dock_content_bg;
			return o; 
		}
	}
	if (Orc$String$equals(item->id, "scene") ) {
		return self->__var___Block_367_33->self->reactScene(self->__var___Block_367_33->self, o, item) ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_5 = NULL;
	{
		SuiView$TextView*  __scopeVar_439_20 = SuiView$mkTextView(&tmpReturn_5, o, (long long )item) , *o = __scopeVar_439_20;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_439_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
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
			SuiLayout$LayoutLinearCell*  __scopeVar_455_24 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_455_24;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_455_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->grow = 1;
		}
		return o; 
	}
}

static void  __fini___Closure_406_44(HoroEditor$__Closure_406_44 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_406_44, __var___Block_367_33) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_406_44*  __make___Closure_406_44(HoroEditor$__Closure_406_44 **  __outRef__, HoroEditor$__Block_367_33 *  __var___Block_367_33){
	URGC_VAR_CLEANUP HoroEditor$__Closure_406_44*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_406_44) , __fini___Closure_406_44) ));
	self->invoke = __fn___Closure_406_44;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_406_44, __var___Block_367_33) , __var___Block_367_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_539_26(HoroEditor$__Closure_539_26 *  self, SuiCore$Event *  e){
	self->__var___Block_533_21->self->onWindowEvent(self->__var___Block_533_21->self, e) ;
}

static void  __fini___Closure_539_26(HoroEditor$__Closure_539_26 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_539_26, __var___Block_533_21) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_539_26*  __make___Closure_539_26(HoroEditor$__Closure_539_26 **  __outRef__, HoroEditor$__Block_533_21 *  __var___Block_533_21){
	URGC_VAR_CLEANUP HoroEditor$__Closure_539_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_539_26) , __fini___Closure_539_26) ));
	self->invoke = __fn___Closure_539_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_539_26, __var___Block_533_21) , __var___Block_533_21) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



