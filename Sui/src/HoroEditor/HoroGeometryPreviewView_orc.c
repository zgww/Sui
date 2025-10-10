
#include "HoroGeometryPreviewView_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Number_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Fbo_orc.h"
#include "../Sgl/Draw_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/GeometryPlane_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryCapsule_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/GeometryHeightMap_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/DirLight_orc.h"
#include "../Sgl/PixelsReader_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/SplitterView_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Image_orc.h"
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
#include "../Sui/Core/KeyEvent_orc.h"
#include "./HoroEditor_orc.h"
#include "./UiAct_orc.h"
#include "../SuiDesigner/Theme_orc.h"
#include "../SuiDesigner/Insp_orc.h"
#include "../SuiDesigner/InvalidReact_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_86_15 HoroEditor$__Block_86_15;

typedef struct tagHoroEditor$__Block_133_22 HoroEditor$__Block_133_22;

typedef struct tagHoroEditor$__Block_186_37 HoroEditor$__Block_186_37;

typedef struct tagHoroEditor$__Closure_94_33 HoroEditor$__Closure_94_33;

typedef struct tagHoroEditor$__Closure_102_27 HoroEditor$__Closure_102_27;

typedef struct tagHoroEditor$__Closure_158_36 HoroEditor$__Closure_158_36;

typedef struct tagHoroEditor$__Closure_166_36 HoroEditor$__Closure_166_36;

typedef struct tagHoroEditor$__Closure_199_26 HoroEditor$__Closure_199_26;



struct tagHoroEditor$__Block_86_15 {
	HoroEditor$HoroGeometryPreviewView*  self ;
};





struct tagHoroEditor$__Block_133_22 {
	HoroEditor$HoroGeometryPreviewView*  self ;
};





struct tagHoroEditor$__Block_186_37 {
	HoroEditor$HoroGeometryPreviewView*  self ;
};





struct tagHoroEditor$__Closure_94_33 {
	void  (*invoke)(HoroEditor$__Closure_94_33 *  self, Object *  obj, OrcMetaField *  mf, Object *  inspValue);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_86_15*  __var___Block_86_15 ;
};





struct tagHoroEditor$__Closure_102_27 {
	void  (*invoke)(HoroEditor$__Closure_102_27 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_86_15*  __var___Block_86_15 ;
};





struct tagHoroEditor$__Closure_158_36 {
	void  (*invoke)(HoroEditor$__Closure_158_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_133_22*  __var___Block_133_22 ;
};





struct tagHoroEditor$__Closure_166_36 {
	void  (*invoke)(HoroEditor$__Closure_166_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_133_22*  __var___Block_133_22 ;
};





struct tagHoroEditor$__Closure_199_26 {
	void  (*invoke)(HoroEditor$__Closure_199_26 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_186_37*  __var___Block_186_37 ;
};





// static function declaration
static void  __finiBlock___Block_86_15(HoroEditor$__Block_86_15 *  self);
static void  __finiBlock___Block_133_22(HoroEditor$__Block_133_22 *  self);
static void  __finiBlock___Block_186_37(HoroEditor$__Block_186_37 *  self);
static void  __fn___Closure_94_33(HoroEditor$__Closure_94_33 *  self, Object *  obj, OrcMetaField *  mf, Object *  inspValue);
static void  __fini___Closure_94_33(HoroEditor$__Closure_94_33 *  self);
static HoroEditor$__Closure_94_33*  __make___Closure_94_33(HoroEditor$__Closure_94_33 **  __outRef__, HoroEditor$__Block_86_15 *  __var___Block_86_15);
static void  __fn___Closure_102_27(HoroEditor$__Closure_102_27 *  self, SuiView$Drag *  d);
static void  __fini___Closure_102_27(HoroEditor$__Closure_102_27 *  self);
static HoroEditor$__Closure_102_27*  __make___Closure_102_27(HoroEditor$__Closure_102_27 **  __outRef__, HoroEditor$__Block_86_15 *  __var___Block_86_15);
static void  __fn___Closure_158_36(HoroEditor$__Closure_158_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_158_36(HoroEditor$__Closure_158_36 *  self);
static HoroEditor$__Closure_158_36*  __make___Closure_158_36(HoroEditor$__Closure_158_36 **  __outRef__, HoroEditor$__Block_133_22 *  __var___Block_133_22);
static void  __fn___Closure_166_36(HoroEditor$__Closure_166_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_166_36(HoroEditor$__Closure_166_36 *  self);
static HoroEditor$__Closure_166_36*  __make___Closure_166_36(HoroEditor$__Closure_166_36 **  __outRef__, HoroEditor$__Block_133_22 *  __var___Block_133_22);
static void  __fn___Closure_199_26(HoroEditor$__Closure_199_26 *  self, SuiCore$Event *  e);
static void  __fini___Closure_199_26(HoroEditor$__Closure_199_26 *  self);
static HoroEditor$__Closure_199_26*  __make___Closure_199_26(HoroEditor$__Closure_199_26 **  __outRef__, HoroEditor$__Block_186_37 *  __var___Block_186_37);



//vtable instance
Vtable_HoroEditor$HoroGeometryPreviewView _vtable_HoroEditor$HoroGeometryPreviewView;

// init meta

void HoroEditor$HoroGeometryPreviewView_initMeta(Vtable_HoroEditor$HoroGeometryPreviewView *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, win), true, false, 1);
	orc_metaField_class(&pNext, "fbo", ((Vtable_Object*)Vtable_Sgl$Fbo_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, fbo), true, false, 1);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, camera), true, false, 1);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, drag), true, false, 1);
	orc_metaField_class(&pNext, "_invalid", ((Vtable_Object*)Vtable_SuiDesigner$InvalidReact_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, _invalid), true, false, 1);
	orc_metaField_class(&pNext, "groundGrid", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, groundGrid), true, false, 1);
	orc_metaField_class(&pNext, "inspObj", ((Vtable_Object*)Vtable_SuiDesigner$Insp_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, inspObj), true, false, 1);
	orc_metaField_class(&pNext, "mesh", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, mesh), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(HoroEditor$HoroGeometryPreviewView, path), true, false, 1);

	orc_metaField_method(&pNext, "reactWindow", offsetof(HoroEditor$HoroGeometryPreviewView, reactWindow));
	orc_metaField_method(&pNext, "showWindow", offsetof(HoroEditor$HoroGeometryPreviewView, showWindow));
	orc_metaField_method(&pNext, "onWindowEvent", offsetof(HoroEditor$HoroGeometryPreviewView, onWindowEvent));
	orc_metaField_method(&pNext, "mkBaseScene", offsetof(HoroEditor$HoroGeometryPreviewView, mkBaseScene));
}


// vtable init


Vtable_HoroEditor$HoroGeometryPreviewView* Vtable_HoroEditor$HoroGeometryPreviewView_init(Vtable_HoroEditor$HoroGeometryPreviewView* pvt){
    if (pvt == NULL){
        pvt = &_vtable_HoroEditor$HoroGeometryPreviewView;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiView$ImageView_init(&_vtable_SuiView$ImageView);

	// init by super vtable init function
    Vtable_SuiView$ImageView_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiView$ImageView;
    ((Vtable_Object*)pvt)->make = (void*)&HoroEditor$HoroGeometryPreviewView_new;
    ((Vtable_Object*)pvt)->className = "HoroEditor$HoroGeometryPreviewView";

    ((Vtable_Object*)pvt)->initMeta = (void*)HoroEditor$HoroGeometryPreviewView_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void HoroEditor$HoroGeometryPreviewView_fini(HoroEditor$HoroGeometryPreviewView *self){
	//super fini
    SuiView$ImageView_fini((SuiView$ImageView *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->win);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->fbo);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->scene);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->camera);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->drag);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->_invalid);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->groundGrid);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->inspObj);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->mesh);
	urgc_fini_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->path);

}

// init fields function


void HoroEditor$HoroGeometryPreviewView_init_fields(HoroEditor$HoroGeometryPreviewView *self){
	//super class
    SuiView$ImageView_init_fields((SuiView$ImageView*)self);

    ((Object*)self)->fini = (void*)HoroEditor$HoroGeometryPreviewView_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->win, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->fbo, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->drawCtx, Sgl$DrawCtx_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->camera, NULL);
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->drag, SuiView$Drag_new(&tmpNewOwner_2) );
	SuiDesigner$InvalidReact *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$InvalidReact*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->_invalid, (tmpThis_1 = SuiDesigner$InvalidReact_new(&tmpNewOwner_3) )->bind(tmpThis_1, self, "reactWindow") );
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->groundGrid, Sgl$Mesh_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Insp*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->inspObj, SuiDesigner$Insp_new(&tmpNewOwner_5) );
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_6 = NULL;
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->mesh, Sgl$Mesh_new(&tmpNewOwner_6) );
	urgc_set_field_class(self, (void**)&((HoroEditor$HoroGeometryPreviewView*)self)->path, NULL);
    }
	((Object*)self)->ctor = (void*)HoroEditor$HoroGeometryPreviewView$ctor;
	((Object*)self)->dtor = (void*)HoroEditor$HoroGeometryPreviewView$dtor;
	((HoroEditor$HoroGeometryPreviewView*)self)->reactWindow = (void*)HoroEditor$HoroGeometryPreviewView$reactWindow;
	((HoroEditor$HoroGeometryPreviewView*)self)->showWindow = (void*)HoroEditor$HoroGeometryPreviewView$showWindow;
	((HoroEditor$HoroGeometryPreviewView*)self)->onWindowEvent = (void*)HoroEditor$HoroGeometryPreviewView$onWindowEvent;
	((SuiCore$ViewBase*)self)->draw_self = (void*)HoroEditor$HoroGeometryPreviewView$draw_self;
	((SuiCore$Emitter*)self)->onEvent = (void*)HoroEditor$HoroGeometryPreviewView$onEvent;
	((HoroEditor$HoroGeometryPreviewView*)self)->mkBaseScene = (void*)HoroEditor$HoroGeometryPreviewView$mkBaseScene;
}

// init function

void HoroEditor$HoroGeometryPreviewView_init(HoroEditor$HoroGeometryPreviewView *self, void *pOwner){
    Vtable_HoroEditor$HoroGeometryPreviewView_init(&_vtable_HoroEditor$HoroGeometryPreviewView);

    ((Object*)self)->vtable = (void*)&_vtable_HoroEditor$HoroGeometryPreviewView;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    HoroEditor$HoroGeometryPreviewView_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
HoroEditor$HoroGeometryPreviewView * HoroEditor$HoroGeometryPreviewView_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    HoroEditor$HoroGeometryPreviewView *self = calloc(1, sizeof(HoroEditor$HoroGeometryPreviewView));
	
    HoroEditor$HoroGeometryPreviewView_init(self, pOwner);
    return self;
}


// class members
void  HoroEditor$HoroGeometryPreviewView$ctor(HoroEditor$HoroGeometryPreviewView *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_86_15*  __var___Block_86_15 = (__var___Block_86_15=NULL,urgc_init_var((void**)&__var___Block_86_15, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_86_15) , __finiBlock___Block_86_15) ));
	urgc_set_field_class(__var___Block_86_15, (void * )offsetof(HoroEditor$__Block_86_15, self) , self) ;
	SuiCore$Listener$ctor(self) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	matl->load(matl, Orc$Path_resolveFromExecutionDir(&tmpReturn_1, "../asset/basic.matl.json") ->str) ;
	urgc_set_field_class(self->mesh, (void * )offsetof(Sgl$Mesh, material) , matl) ;
	self->mkBaseScene(self) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_94_33*  tmpReturn_2 = NULL;
	urgc_set_field(self->inspObj, (void * )offsetof(SuiDesigner$Insp, cbSetAttr) , __make___Closure_94_33(&tmpReturn_2, __var___Block_86_15) ) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_102_27*  tmpReturn_3 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_102_27(&tmpReturn_3, __var___Block_86_15) ) ;
	{
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryPlane*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryPlane_new(&geom) ));
		geom->planeType = 1;
		geom->width = 10000;
		geom->height = 10000;
		geom->widthSegments = 100;
		geom->heightSegments = 100;
		((Sgl$Geometry * )geom)->build(geom) ;
		urgc_set_field_class(self->groundGrid, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		matl->load(matl, Orc$Path_resolveFromExecutionDir(&tmpReturn_4, "../asset/basic.matl.json") ->str) ;
		urgc_set_field_class(self->groundGrid, (void * )offsetof(Sgl$Mesh, material) , matl) ;
	}
}


void  HoroEditor$HoroGeometryPreviewView$dtor(HoroEditor$HoroGeometryPreviewView *  self){
	printf(".....HoroGeometryPreviewView\n\n") ;
}


void  HoroEditor$HoroGeometryPreviewView$reactWindow(HoroEditor$HoroGeometryPreviewView *  self){
	URGC_VAR_CLEANUP HoroEditor$__Block_133_22*  __var___Block_133_22 = (__var___Block_133_22=NULL,urgc_init_var((void**)&__var___Block_133_22, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_133_22) , __finiBlock___Block_133_22) ));
	urgc_set_field_class(__var___Block_133_22, (void * )offsetof(HoroEditor$__Block_133_22, self) , self) ;
	printf("reactWindow========================================\n") ;
	SuiLayout$LayoutLinear *  ll = (SuiLayout$LayoutLinear * )self->win->rootView;
	{
		SuiLayout$LayoutLinear *  o = ll;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_136_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->backgroundColor = SuiDesigner$themeIns() ->bg1;
		Orc$String$set(o->direction, "row") ;
		Orc$String$set(o->alignItems, "stretch") ;
		SuiCore$Node$placeKid((SuiCore$Node * )o, self) ;
		{
			HoroEditor$HoroGeometryPreviewView *  o = self;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_142_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_1 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_143_16 = SuiLayout$layoutLinearCell(&tmpReturn_1, o, 0) , *o = __scopeVar_143_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_143_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 2;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$SplitterView*  tmpReturn_2 = NULL;
		{
			SuiView$SplitterView*  __scopeVar_146_12 = SuiView$mkSplitterView(&tmpReturn_2, o, 0) , *o = __scopeVar_146_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_146_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_3 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_148_12 = SuiLayout$layoutLinear(&tmpReturn_3, o, 0) , *o = __scopeVar_148_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_148_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->column(o) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
			SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) ;
			if (self->mesh->geometry) {
				self->inspObj->insp(self->inspObj, o, self->mesh->geometry) ;
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_5 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_154_20 = SuiView$mkDrawButton(&tmpReturn_5, o, 0) , *o = __scopeVar_154_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_154_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
					{
						SuiLayout$LayoutLinearCell*  __scopeVar_155_24 = SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) , *o = __scopeVar_155_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_155_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->grow = 0;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinearCell, alignSelf) , Orc$str(&tmpReturn_7, "stretch") ) ;
					}
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_8, "print") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_158_36*  tmpReturn_9 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_158_36(&tmpReturn_9, __var___Block_133_22) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_10 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_162_20 = SuiView$mkDrawButton(&tmpReturn_10, o, 0) , *o = __scopeVar_162_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_162_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_11 = NULL;
					{
						SuiLayout$LayoutLinearCell*  __scopeVar_163_24 = SuiLayout$layoutLinearCell(&tmpReturn_11, o, 0) , *o = __scopeVar_163_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_163_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->grow = 0;
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
						urgc_set_field_class(o, (void * )offsetof(SuiLayout$LayoutLinearCell, alignSelf) , Orc$str(&tmpReturn_12, "stretch") ) ;
					}
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_13, "保存") ) ;
					URGC_VAR_CLEANUP HoroEditor$__Closure_166_36*  tmpReturn_14 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_166_36(&tmpReturn_14, __var___Block_133_22) ) ;
				}
			}
			else {
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_15 = NULL;
				{
					SuiView$TextView*  __scopeVar_176_20 = SuiView$mkTextView(&tmpReturn_15, o, 0) , *o = __scopeVar_176_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_176_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
					o->setText(o, Orc$str(&tmpReturn_16, "Create Geometry Instance fail") ) ;
				}
			}
		}
	}
}


void  HoroEditor$HoroGeometryPreviewView$showWindow(HoroEditor$HoroGeometryPreviewView *  self, const char *  path){
	URGC_VAR_CLEANUP HoroEditor$__Block_186_37*  __var___Block_186_37 = (__var___Block_186_37=NULL,urgc_init_var((void**)&__var___Block_186_37, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_186_37) , __finiBlock___Block_186_37) ));
	urgc_set_field_class(__var___Block_186_37, (void * )offsetof(HoroEditor$__Block_186_37, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryPreviewView, path) , Orc$str(&tmpReturn_1, path) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  geom = HoroEditor$HoroGeometry_parseGeometryJson((geom = NULL,&geom), path) ;
	if (!geom) {
		SuiDialog$Toast_make("not geometry.json file") ;
		return ; 
	}
	urgc_set_field_class(self->mesh, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryPreviewView, win) , Sui$Window_new(&tmpNewOwner_2) ) ;
	{
		Sui$Window*  o = self->win;
		
	
		URGC_VAR_CLEANUP HoroEditor$__Closure_199_26*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_199_26(&tmpReturn_3, __var___Block_186_37) ) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_4 = NULL;
		self->win->setRootView(self->win, SuiLayout$LayoutLinear_new(&tmpNewOwner_4) ) ;
		self->reactWindow(self) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
		o->setTitle(o, Orc$String$replaceAll(&tmpReturn_5, Orc$str(&tmpReturn_6, "预览几何体{0}") , "{0}", path) ->str) ;
		o->setSize(o, 800, 600) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  HoroEditor$HoroGeometryPreviewView$onWindowEvent(HoroEditor$HoroGeometryPreviewView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$KeyEvent_init(NULL))) {
		SuiCore$KeyEvent *  ke = (SuiCore$KeyEvent * )e;
		printf("2窗口收到键盘消息:%s\n", ke->key->str) ;
		if (self->camera && ke->isKeyDown) {
			if (ke->ctrl) {
				if (Orc$String$equalsIgnoreCase(ke->key, "S") ) {
					HoroEditor$UiAct_savePrefab(self) ;
				}
			}
			else if (ke->shift) {
				if (Orc$String$equalsIgnoreCase(ke->key, "A") ) {
					printf("左旋转\n") ;
					((Sgl$Obj3d * )self->camera)->rotation.y += 0.01;
				}
				else if (Orc$String$equalsIgnoreCase(ke->key, "D") ) {
					printf("右旋转\n") ;
					((Sgl$Obj3d * )self->camera)->rotation.y -= 0.01;
				}
				else if (Orc$String$equalsIgnoreCase(ke->key, "W") ) {
					printf("左旋转\n") ;
					((Sgl$Obj3d * )self->camera)->rotation.x -= 0.01;
				}
				else if (Orc$String$equalsIgnoreCase(ke->key, "S") ) {
					printf("右旋转\n") ;
					((Sgl$Obj3d * )self->camera)->rotation.x += 0.01;
				}
			}
			else if (Orc$String$equals(ke->key, "W") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->camera, SuiCore$mkVec3(0, 0, -1.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_1, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "S") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->camera, SuiCore$mkVec3(0, 0, 1.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_2, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "A") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->camera, SuiCore$mkVec3(-1, 0, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_3, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "D") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->camera, SuiCore$mkVec3(1, 0, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_4, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "E") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->camera, SuiCore$mkVec3(0, 1, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_5, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->camera)->position, dir) ;
			}
			else if (Orc$String$equals(ke->key, "Q") ) {
				SuiCore$Vec3 dir = Sgl$Obj3d$applyRotationToVec3((Sgl$Obj3d * )self->camera, SuiCore$mkVec3(0, -1, 0.0) ) ;
				SuiCore$Vec3$multiplyScalarLocal(&dir, 10) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
				printf("apply dir:%s\n", SuiCore$Vec3$toString(&tmpReturn_6, &dir) ->str) ;
				SuiCore$Vec3$addLocal(&((Sgl$Obj3d * )self->camera)->position, dir) ;
			}
		}
	}
}


void  HoroEditor$HoroGeometryPreviewView$draw_self(HoroEditor$HoroGeometryPreviewView *  self, SuiCore$Canvas *  canvas){
	{
		bool  mkFbo = false;
		if (self->fbo == NULL) {
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
			urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryPreviewView, fbo) , Sgl$Fbo_new(&tmpNewOwner_1) ) ;
			self->fbo->buildWithColorDepthStencilTexture(self->fbo, (int )((SuiCore$ViewBase * )self)->frame.width, (int )((SuiCore$ViewBase * )self)->frame.height, true, true, false) ;
		}
	}
	if (self->fbo) {
		SuiCore$Vec2 fboSize = self->fbo->getSize(self->fbo) ;
		self->camera->aspect = fboSize.x / fboSize.y;
		self->fbo->startDraw(self->fbo, 0.0, 0.0, 0.0, 1.0, true, true, true) ;
		self->drawCtx->frameSize = fboSize;
		self->drawCtx->draw(self->drawCtx, self->scene, self->camera) ;
		self->fbo->endDraw(self->fbo) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Image*  tmpReturn_2 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiView$ImageView, _img) , Sgl$loadImageByTex2d(&tmpReturn_2, self->fbo->tex2d) ) ;
	}
	SuiView$ImageView$draw_self(self, canvas) ;
}


void  HoroEditor$HoroGeometryPreviewView$onEvent(HoroEditor$HoroGeometryPreviewView *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isMouseDown && ((SuiCore$ViewEvent * )me)->isBubble(me) ) {
			self->drag->onMouseDown(self->drag, me) ;
		}
	}
}


void  HoroEditor$HoroGeometryPreviewView$mkBaseScene(HoroEditor$HoroGeometryPreviewView *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Scene*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryPreviewView, scene) , Sgl$Scene_new(&tmpNewOwner_1) ) ;
	URGC_VAR_CLEANUP_CLASS Sgl$PerspectiveCamera*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$HoroGeometryPreviewView, camera) , Sgl$PerspectiveCamera_new(&tmpNewOwner_2) ) ;
	((Sgl$Obj3d * )self->camera)->up = SuiCore$mkVec3(0, 1, 0) ;
	self->camera->fov = 45 / 180.0 * Orc$PI;
	self->camera->aspect = 1.0;
	self->camera->nearPlane = 100.1;
	self->camera->farPlane = 5000;
	((Sgl$Obj3d * )self->camera)->position = SuiCore$mkVec3(100, 0, 1000) ;
	Sgl$Obj3d$updateWorldMatrixUptoRoot((Sgl$Obj3d * )self->camera) ;
	((Sgl$Obj3d * )self->camera)->lookAt(self->camera, 0, 0, 0) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, self->camera) ;
	((SuiCore$Node * )self->scene)->appendChild(self->scene, self->mesh) ;
	printf("Base scene and camera initialized\n") ;
}



static void  __finiBlock___Block_86_15(HoroEditor$__Block_86_15 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_86_15, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_133_22(HoroEditor$__Block_133_22 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_133_22, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_186_37(HoroEditor$__Block_186_37 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_186_37, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_94_33(HoroEditor$__Closure_94_33 *  self, Object *  obj, OrcMetaField *  mf, Object *  inspValue){
	Orc$Orc_setField(obj, mf, inspValue) ;
	self->__var___Block_86_15->self->mesh->geometry->version++;
	self->__var___Block_86_15->self->mesh->geometry->build(self->__var___Block_86_15->self->mesh->geometry) ;
	self->__var___Block_86_15->self->_invalid->invalid(self->__var___Block_86_15->self->_invalid) ;
}

static void  __fini___Closure_94_33(HoroEditor$__Closure_94_33 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_94_33, __var___Block_86_15) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_94_33*  __make___Closure_94_33(HoroEditor$__Closure_94_33 **  __outRef__, HoroEditor$__Block_86_15 *  __var___Block_86_15){
	URGC_VAR_CLEANUP HoroEditor$__Closure_94_33*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_94_33) , __fini___Closure_94_33) ));
	self->invoke = __fn___Closure_94_33;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_94_33, __var___Block_86_15) , __var___Block_86_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_102_27(HoroEditor$__Closure_102_27 *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		printf("dragging scene\n") ;
		((Sgl$Obj3d * )self->__var___Block_86_15->self->camera)->rotation.y += d->deltaPos.x * 0.001;
		((Sgl$Obj3d * )self->__var___Block_86_15->self->camera)->rotation.x += d->deltaPos.y * 0.001;
	}
}

static void  __fini___Closure_102_27(HoroEditor$__Closure_102_27 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_102_27, __var___Block_86_15) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_102_27*  __make___Closure_102_27(HoroEditor$__Closure_102_27 **  __outRef__, HoroEditor$__Block_86_15 *  __var___Block_86_15){
	URGC_VAR_CLEANUP HoroEditor$__Closure_102_27*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_102_27) , __fini___Closure_102_27) ));
	self->invoke = __fn___Closure_102_27;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_102_27, __var___Block_86_15) , __var___Block_86_15) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_158_36(HoroEditor$__Closure_158_36 *  self, SuiCore$MouseEvent *  me){
	SuiCore$printNodeTree(self->__var___Block_133_22->self, 0) ;
}

static void  __fini___Closure_158_36(HoroEditor$__Closure_158_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_158_36, __var___Block_133_22) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_158_36*  __make___Closure_158_36(HoroEditor$__Closure_158_36 **  __outRef__, HoroEditor$__Block_133_22 *  __var___Block_133_22){
	URGC_VAR_CLEANUP HoroEditor$__Closure_158_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_158_36) , __fini___Closure_158_36) ));
	self->invoke = __fn___Closure_158_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_158_36, __var___Block_133_22) , __var___Block_133_22) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_166_36(HoroEditor$__Closure_166_36 *  self, SuiCore$MouseEvent *  me){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_toJson((jo = NULL,&jo), self->__var___Block_133_22->self->mesh->geometry) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("save geometry:%s\n", jo->dump(&tmpReturn_1, jo) ->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	if (Orc$Path_writeText(self->__var___Block_133_22->self->path->str, jo->dump(&tmpReturn_2, jo) ->str) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		SuiDialog$Toast_make(Orc$String$replaceAll(&tmpReturn_3, Orc$str(&tmpReturn_4, "保存成功:{0}") , "{0}", self->__var___Block_133_22->self->path->str) ->str) ;
	}
}

static void  __fini___Closure_166_36(HoroEditor$__Closure_166_36 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_166_36, __var___Block_133_22) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_166_36*  __make___Closure_166_36(HoroEditor$__Closure_166_36 **  __outRef__, HoroEditor$__Block_133_22 *  __var___Block_133_22){
	URGC_VAR_CLEANUP HoroEditor$__Closure_166_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_166_36) , __fini___Closure_166_36) ));
	self->invoke = __fn___Closure_166_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_166_36, __var___Block_133_22) , __var___Block_133_22) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_199_26(HoroEditor$__Closure_199_26 *  self, SuiCore$Event *  e){
	self->__var___Block_186_37->self->onWindowEvent(self->__var___Block_186_37->self, e) ;
}

static void  __fini___Closure_199_26(HoroEditor$__Closure_199_26 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_199_26, __var___Block_186_37) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_199_26*  __make___Closure_199_26(HoroEditor$__Closure_199_26 **  __outRef__, HoroEditor$__Block_186_37 *  __var___Block_186_37){
	URGC_VAR_CLEANUP HoroEditor$__Closure_199_26*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_199_26) , __fini___Closure_199_26) ));
	self->invoke = __fn___Closure_199_26;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_199_26, __var___Block_186_37) , __var___Block_186_37) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

Orc$PointerArray*  HoroEditor$HoroGeometry_getGeometryVtables(Orc$PointerArray **  __outRef__){
	URGC_VAR_CLEANUP_CLASS Orc$PointerArray*  vts = (vts=NULL,urgc_init_var_class((void**)&vts, Orc$PointerArray_new(&vts) ));
	vts->add(vts, Vtable_Sgl$GeometryBox_init(NULL)) ;
	vts->add(vts, Vtable_Sgl$GeometrySphere_init(NULL)) ;
	vts->add(vts, Vtable_Sgl$GeometryPlane_init(NULL)) ;
	vts->add(vts, Vtable_Sgl$GeometryCapsule_init(NULL)) ;
	vts->add(vts, Vtable_Sgl$GeometryHeightMap_init(NULL)) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, vts) ; 
}

Sgl$Geometry*  HoroEditor$HoroGeometry_parseGeometryJson(Sgl$Geometry **  __outRef__, const char *  path){
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parseByPathCstr((jo = NULL,&jo), path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("loadjson %s :%s\n", path, jo->dump(&tmpReturn_1, jo) ->str) ;
	if (!jo || jo->isNull(jo) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		SuiDialog$Toast_make(Orc$String$replaceAll(&tmpReturn_2, Orc$str(&tmpReturn_3, "打开文件{}失败") , "{}", path) ->str) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$PointerArray*  vts = HoroEditor$HoroGeometry_getGeometryVtables((vts = NULL,&vts)) ;
	URGC_VAR_CLEANUP_CLASS Object*  tmpReturn_4 = NULL;
	Object *  obj = jo->toObjectByVtables(&tmpReturn_4, jo, vts) ;
	if (Orc_instanceof((Object*)obj, (Vtable_Object*)Vtable_Sgl$Geometry_init(NULL))) {
		URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, (Sgl$Geometry* )obj));
		geom->build(geom) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, obj) ; 
	}
	SuiDialog$Toast_make("not geometry.json file") ;
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}

HoroEditor$HoroGeometryPreviewView*  HoroEditor$mkHoroGeometryPreviewView(HoroEditor$HoroGeometryPreviewView **  __outRef__, void *  parent, long long  key){
	void *  addr = __builtin_return_address(0) ;
	void *  sp = key ? (void * )key : addr;
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, (HoroEditor$HoroGeometryPreviewView* )SuiView$gocNode(&tmpReturn_1, sp, (SuiCore$Node * )parent, Vtable_HoroEditor$HoroGeometryPreviewView_init(NULL)) ) ; 
}



