
#include "ToolBase_orc.h" 

#include <stdio.h>
#include <string.h>
#include "../Orc/Orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Number_orc.h"
#include "../Orc/Path_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Plane_orc.h"
#include "../Sgl/Ray_orc.h"
#include "../Sgl/Scene_orc.h"
#include "../Sgl/Camera_orc.h"
#include "../Sgl/Raycaster_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Light_orc.h"
#include "../Sgl/SpotLight_orc.h"
#include "../Sgl/PointLight_orc.h"
#include "../Sgl/Mesh_orc.h"
#include "../Sgl/Mat_orc.h"
#include "../Sgl/Billboard_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometryLine_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/PerspectiveCamera_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "./SglEditCtx_orc.h"
#include "./SglGizmo_orc.h"
#include "./ANode_orc.h"
#include "../SuiDesigner/Asset/AssetDirView_orc.h"
#include "../SuiDesigner/FileItem_orc.h"
#include "../HoroEditor/HoroEditor_orc.h"
#include "../HoroEditor/UiAct_orc.h"
#include "../Sgl/ModelLoader_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_152_40 SuiDesigner$__Block_152_40;

typedef struct tagSuiDesigner$__Block_165_57 SuiDesigner$__Block_165_57;

typedef struct tagSuiDesigner$__Block_186_19 SuiDesigner$__Block_186_19;

typedef struct tagSuiDesigner$__Block_260_29 SuiDesigner$__Block_260_29;

typedef struct tagSuiDesigner$__Block_449_37 SuiDesigner$__Block_449_37;

typedef struct tagSuiDesigner$__Closure_154_18 SuiDesigner$__Closure_154_18;

typedef struct tagSuiDesigner$__Closure_168_20 SuiDesigner$__Closure_168_20;

typedef struct tagSuiDesigner$__Closure_188_28 SuiDesigner$__Closure_188_28;

typedef struct tagSuiDesigner$__Closure_cbOnEvent_278 SuiDesigner$__Closure_cbOnEvent_278;

typedef struct tagSuiDesigner$__Closure_472_34 SuiDesigner$__Closure_472_34;

typedef struct tagSuiDesigner$__Closure_498_34 SuiDesigner$__Closure_498_34;



struct tagSuiDesigner$__Block_152_40 {
	SuiDesigner$ToolSelect*  self ;
};





struct tagSuiDesigner$__Block_165_57 {
	SuiDesigner$ToolSelect*  self ;
	char *  mode ;
};





struct tagSuiDesigner$__Block_186_19 {
	SuiDesigner$ToolSelect*  self ;
};





struct tagSuiDesigner$__Block_260_29 {
	SuiDesigner$ToolSelect*  self ;
	bool  dragging ;
};





struct tagSuiDesigner$__Block_449_37 {
	SuiDesigner$ToolMgr*  self ;
	SuiCore$Node *  n ;
};





struct tagSuiDesigner$__Closure_154_18 {
	void  (*invoke)(SuiDesigner$__Closure_154_18 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_152_40*  __var___Block_152_40 ;
};





struct tagSuiDesigner$__Closure_168_20 {
	void  (*invoke)(SuiDesigner$__Closure_168_20 *  self, SuiCore$MouseEvent *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_165_57*  __var___Block_165_57 ;
};





struct tagSuiDesigner$__Closure_188_28 {
	void  (*invoke)(SuiDesigner$__Closure_188_28 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_186_19*  __var___Block_186_19 ;
};





struct tagSuiDesigner$__Closure_cbOnEvent_278 {
	void  (*invoke)(SuiDesigner$__Closure_cbOnEvent_278 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_260_29*  __var___Block_260_29 ;
};





struct tagSuiDesigner$__Closure_472_34 {
	void  (*invoke)(SuiDesigner$__Closure_472_34 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_449_37*  __var___Block_449_37 ;
};





struct tagSuiDesigner$__Closure_498_34 {
	void  (*invoke)(SuiDesigner$__Closure_498_34 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_449_37*  __var___Block_449_37 ;
};





// static function declaration
static void  __finiBlock___Block_152_40(SuiDesigner$__Block_152_40 *  self);
static void  __finiBlock___Block_165_57(SuiDesigner$__Block_165_57 *  self);
static void  __finiBlock___Block_186_19(SuiDesigner$__Block_186_19 *  self);
static void  __finiBlock___Block_260_29(SuiDesigner$__Block_260_29 *  self);
static void  __finiBlock___Block_449_37(SuiDesigner$__Block_449_37 *  self);
static void  __fn___Closure_154_18(SuiDesigner$__Closure_154_18 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_154_18(SuiDesigner$__Closure_154_18 *  self);
static SuiDesigner$__Closure_154_18*  __make___Closure_154_18(SuiDesigner$__Closure_154_18 **  __outRef__, SuiDesigner$__Block_152_40 *  __var___Block_152_40);
static void  __fn___Closure_168_20(SuiDesigner$__Closure_168_20 *  self, SuiCore$MouseEvent *  e);
static void  __fini___Closure_168_20(SuiDesigner$__Closure_168_20 *  self);
static SuiDesigner$__Closure_168_20*  __make___Closure_168_20(SuiDesigner$__Closure_168_20 **  __outRef__, SuiDesigner$__Block_165_57 *  __var___Block_165_57);
static void  __fn___Closure_188_28(SuiDesigner$__Closure_188_28 *  self, SuiView$Drag *  d);
static void  __fini___Closure_188_28(SuiDesigner$__Closure_188_28 *  self);
static SuiDesigner$__Closure_188_28*  __make___Closure_188_28(SuiDesigner$__Closure_188_28 **  __outRef__, SuiDesigner$__Block_186_19 *  __var___Block_186_19);
static void  __fn___Closure_cbOnEvent_278(SuiDesigner$__Closure_cbOnEvent_278 *  self, SuiCore$Event *  e);
static void  __fini___Closure_cbOnEvent_278(SuiDesigner$__Closure_cbOnEvent_278 *  self);
static SuiDesigner$__Closure_cbOnEvent_278*  __make___Closure_cbOnEvent_278(SuiDesigner$__Closure_cbOnEvent_278 **  __outRef__, SuiDesigner$__Block_260_29 *  __var___Block_260_29);
static void  __fn___Closure_472_34(SuiDesigner$__Closure_472_34 *  self, SuiCore$Event *  e);
static void  __fini___Closure_472_34(SuiDesigner$__Closure_472_34 *  self);
static SuiDesigner$__Closure_472_34*  __make___Closure_472_34(SuiDesigner$__Closure_472_34 **  __outRef__, SuiDesigner$__Block_449_37 *  __var___Block_449_37);
static void  __fn___Closure_498_34(SuiDesigner$__Closure_498_34 *  self, SuiCore$Event *  e);
static void  __fini___Closure_498_34(SuiDesigner$__Closure_498_34 *  self);
static SuiDesigner$__Closure_498_34*  __make___Closure_498_34(SuiDesigner$__Closure_498_34 **  __outRef__, SuiDesigner$__Block_449_37 *  __var___Block_449_37);



//vtable instance
Vtable_SuiDesigner$ToolBase _vtable_SuiDesigner$ToolBase;

// init meta

void SuiDesigner$ToolBase_initMeta(Vtable_SuiDesigner$ToolBase *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ToolBase, name), true, false, 1);
	orc_metaField_class(&pNext, "iconPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ToolBase, iconPath), true, false, 1);
	orc_metaField_class(&pNext, "mgr", ((Vtable_Object*)Vtable_SuiDesigner$ToolMgr_init(0)), offsetof(SuiDesigner$ToolBase, mgr), true, false, 1);

	orc_metaField_method(&pNext, "onEnable", offsetof(SuiDesigner$ToolBase, onEnable));
	orc_metaField_method(&pNext, "onDisable", offsetof(SuiDesigner$ToolBase, onDisable));
	orc_metaField_method(&pNext, "reactGizmo", offsetof(SuiDesigner$ToolBase, reactGizmo));
	orc_metaField_method(&pNext, "onEvent", offsetof(SuiDesigner$ToolBase, onEvent));
	orc_metaField_method(&pNext, "draw2d", offsetof(SuiDesigner$ToolBase, draw2d));
	orc_metaField_method(&pNext, "reactGizmosView", offsetof(SuiDesigner$ToolBase, reactGizmosView));
}


// vtable init


Vtable_SuiDesigner$ToolBase* Vtable_SuiDesigner$ToolBase_init(Vtable_SuiDesigner$ToolBase* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ToolBase;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ToolBase_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ToolBase";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ToolBase_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ToolBase_fini(SuiDesigner$ToolBase *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->name);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->iconPath);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->mgr);

}

// init fields function


void SuiDesigner$ToolBase_init_fields(SuiDesigner$ToolBase *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ToolBase_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->name, Orc$str(&tmpReturn_1, "") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->iconPath, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolBase*)self)->mgr, NULL);
    }
	((SuiDesigner$ToolBase*)self)->onEnable = (void*)SuiDesigner$ToolBase$onEnable;
	((SuiDesigner$ToolBase*)self)->onDisable = (void*)SuiDesigner$ToolBase$onDisable;
	((SuiDesigner$ToolBase*)self)->reactGizmo = (void*)SuiDesigner$ToolBase$reactGizmo;
	((SuiDesigner$ToolBase*)self)->onEvent = (void*)SuiDesigner$ToolBase$onEvent;
	((SuiDesigner$ToolBase*)self)->draw2d = (void*)SuiDesigner$ToolBase$draw2d;
	((SuiDesigner$ToolBase*)self)->reactGizmosView = (void*)SuiDesigner$ToolBase$reactGizmosView;
}

// init function

void SuiDesigner$ToolBase_init(SuiDesigner$ToolBase *self, void *pOwner){
    Vtable_SuiDesigner$ToolBase_init(&_vtable_SuiDesigner$ToolBase);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ToolBase;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ToolBase_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ToolBase * SuiDesigner$ToolBase_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ToolBase *self = calloc(1, sizeof(SuiDesigner$ToolBase));
	
    SuiDesigner$ToolBase_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ToolBase$onEnable(SuiDesigner$ToolBase *  self){
	
}


void  SuiDesigner$ToolBase$onDisable(SuiDesigner$ToolBase *  self){
	
}


void  SuiDesigner$ToolBase$reactGizmo(SuiDesigner$ToolBase *  self, Sgl$Obj3d *  gizmoScene){
	
}


void  SuiDesigner$ToolBase$onEvent(SuiDesigner$ToolBase *  self, SuiCore$Event *  e){
	
}


void  SuiDesigner$ToolBase$draw2d(SuiDesigner$ToolBase *  self, SuiCore$Canvas *  canvas){
	
}


void  SuiDesigner$ToolBase$reactGizmosView(SuiDesigner$ToolBase *  self, SuiCore$Node *  o){
	
}




//vtable instance
Vtable_SuiDesigner$ToolDropModelLoader _vtable_SuiDesigner$ToolDropModelLoader;

// init meta

void SuiDesigner$ToolDropModelLoader_initMeta(Vtable_SuiDesigner$ToolDropModelLoader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	

	
}


// vtable init


Vtable_SuiDesigner$ToolDropModelLoader* Vtable_SuiDesigner$ToolDropModelLoader_init(Vtable_SuiDesigner$ToolDropModelLoader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ToolDropModelLoader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$ToolBase_init(&_vtable_SuiDesigner$ToolBase);

	// init by super vtable init function
    Vtable_SuiDesigner$ToolBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$ToolBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ToolDropModelLoader_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ToolDropModelLoader";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ToolDropModelLoader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ToolDropModelLoader_fini(SuiDesigner$ToolDropModelLoader *self){
	//super fini
    SuiDesigner$ToolBase_fini((SuiDesigner$ToolBase *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner$ToolDropModelLoader_init_fields(SuiDesigner$ToolDropModelLoader *self){
	//super class
    SuiDesigner$ToolBase_init_fields((SuiDesigner$ToolBase*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ToolDropModelLoader_fini;
	//fields
    {
	
    }
	((SuiDesigner$ToolBase*)self)->onEvent = (void*)SuiDesigner$ToolDropModelLoader$onEvent;
}

// init function

void SuiDesigner$ToolDropModelLoader_init(SuiDesigner$ToolDropModelLoader *self, void *pOwner){
    Vtable_SuiDesigner$ToolDropModelLoader_init(&_vtable_SuiDesigner$ToolDropModelLoader);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ToolDropModelLoader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ToolDropModelLoader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ToolDropModelLoader * SuiDesigner$ToolDropModelLoader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ToolDropModelLoader *self = calloc(1, sizeof(SuiDesigner$ToolDropModelLoader));
	
    SuiDesigner$ToolDropModelLoader_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ToolDropModelLoader$onEvent(SuiDesigner$ToolDropModelLoader *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			Sgl$Ray ray = ((SuiDesigner$ToolBase * )self)->mgr->camera->mkRay(((SuiDesigner$ToolBase * )self)->mgr->camera, me->ndcPos) ;
			SuiCore$Plane plane;
			Sgl$Mat m;
			Sgl$Mat$identity(&m) ;
			SuiCore$Plane$setByMatrixAndPlaneName(&plane, m, "XZ") ;
			Sgl$IntersectResult r = Sgl$Ray$intersectPlane(&ray, plane) ;
			if (r.succ) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
				printf("drop model at %s\n", SuiCore$Vec3$toString(&tmpReturn_1, &r.point) ->str) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiDesigner$SelectFileItems*  items = (items=NULL,urgc_init_var_class((void**)&items, ((SuiDesigner$ToolBase * )self)->mgr->editor->dirView->selectFileItems));
			SuiDesigner$FileItem *  item = items->getIfOnlyOne(items) ;
			if (item != NULL) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  relpath = Orc$Path_relPathToCwd((relpath = NULL,&relpath), item->path->str) ;
				printf("当前选中的fileitem为:%s; 相对路径为:%s\n", item->path->str, relpath->str) ;
				if (Orc$String$endsWith(item->path, ".obj")  || Orc$String$endsWith(item->path, ".fbx") ) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  anode = HoroEditor$UiAct_addViewToSelectedOrRoot((anode = NULL,&anode), ((SuiDesigner$ToolBase * )self)->mgr->editor, Vtable_getClassName(Vtable_Sgl$ModelLoader_init(NULL)) ) ;
					if (anode) {
						URGC_VAR_CLEANUP_CLASS Orc$StructObj*  positionObj = SuiCore$mkVec3StructObj((positionObj = NULL,&positionObj), r.point) ;
						anode->setAttrValueObject(anode, "position", positionObj) ;
						URGC_VAR_CLEANUP_CLASS Orc$StructObj*  scaleObj = SuiCore$mkVec3StructObj3f((scaleObj = NULL,&scaleObj), 100, 100, 100) ;
						anode->setAttrValueObject(anode, "scale", scaleObj) ;
						anode->setAttrValueObject(anode, "path", relpath) ;
					}
				}
			}
			else {
				printf("当前未选中FileItem\n") ;
			}
		}
	}
}




//vtable instance
Vtable_SuiDesigner$ToolSelect _vtable_SuiDesigner$ToolSelect;

// init meta

void SuiDesigner$ToolSelect_initMeta(Vtable_SuiDesigner$ToolSelect *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "leftPos", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner$ToolSelect, leftPos), false, false, 0);
	orc_metaField_class(&pNext, "drag", ((Vtable_Object*)Vtable_SuiView$Drag_init(0)), offsetof(SuiDesigner$ToolSelect, drag), true, false, 1);
	orc_metaField_class(&pNext, "mode", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ToolSelect, mode), true, false, 1);
	orc_metaField_primitive(&pNext, "spaceWorld", OrcMetaType_bool, offsetof(SuiDesigner$ToolSelect, spaceWorld), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "isModeTranslate", offsetof(SuiDesigner$ToolSelect, isModeTranslate));
	orc_metaField_method(&pNext, "isModeRotate", offsetof(SuiDesigner$ToolSelect, isModeRotate));
	orc_metaField_method(&pNext, "isModeScale", offsetof(SuiDesigner$ToolSelect, isModeScale));
	orc_metaField_method(&pNext, "reactSpaceButton", offsetof(SuiDesigner$ToolSelect, reactSpaceButton));
	orc_metaField_method(&pNext, "reactModeButton", offsetof(SuiDesigner$ToolSelect, reactModeButton));
}


// vtable init


Vtable_SuiDesigner$ToolSelect* Vtable_SuiDesigner$ToolSelect_init(Vtable_SuiDesigner$ToolSelect* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ToolSelect;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner$ToolBase_init(&_vtable_SuiDesigner$ToolBase);

	// init by super vtable init function
    Vtable_SuiDesigner$ToolBase_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner$ToolBase;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ToolSelect_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ToolSelect";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ToolSelect_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ToolSelect_fini(SuiDesigner$ToolSelect *self){
	//super fini
    SuiDesigner$ToolBase_fini((SuiDesigner$ToolBase *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolSelect*)self)->drag);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolSelect*)self)->mode);

}

// init fields function


void SuiDesigner$ToolSelect_init_fields(SuiDesigner$ToolSelect *self){
	//super class
    SuiDesigner$ToolBase_init_fields((SuiDesigner$ToolBase*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ToolSelect_fini;
	//fields
    {
	((SuiDesigner$ToolSelect*)self)->leftPos = SuiCore$mkVec3(-200, 0, -200) ;
	URGC_VAR_CLEANUP_CLASS SuiView$Drag*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolSelect*)self)->drag, SuiView$Drag_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolSelect*)self)->mode, Orc$str(&tmpReturn_2, "translate") );
	((SuiDesigner$ToolSelect*)self)->spaceWorld = false;
    }
	((SuiDesigner$ToolSelect*)self)->isModeTranslate = (void*)SuiDesigner$ToolSelect$isModeTranslate;
	((SuiDesigner$ToolSelect*)self)->isModeRotate = (void*)SuiDesigner$ToolSelect$isModeRotate;
	((SuiDesigner$ToolSelect*)self)->isModeScale = (void*)SuiDesigner$ToolSelect$isModeScale;
	((SuiDesigner$ToolSelect*)self)->reactSpaceButton = (void*)SuiDesigner$ToolSelect$reactSpaceButton;
	((SuiDesigner$ToolSelect*)self)->reactModeButton = (void*)SuiDesigner$ToolSelect$reactModeButton;
	((SuiDesigner$ToolBase*)self)->onEnable = (void*)SuiDesigner$ToolSelect$onEnable;
	((SuiDesigner$ToolBase*)self)->onDisable = (void*)SuiDesigner$ToolSelect$onDisable;
	((SuiDesigner$ToolBase*)self)->draw2d = (void*)SuiDesigner$ToolSelect$draw2d;
	((SuiDesigner$ToolBase*)self)->reactGizmosView = (void*)SuiDesigner$ToolSelect$reactGizmosView;
	((SuiDesigner$ToolBase*)self)->onEvent = (void*)SuiDesigner$ToolSelect$onEvent;
	((SuiDesigner$ToolBase*)self)->reactGizmo = (void*)SuiDesigner$ToolSelect$reactGizmo;
}

// init function

void SuiDesigner$ToolSelect_init(SuiDesigner$ToolSelect *self, void *pOwner){
    Vtable_SuiDesigner$ToolSelect_init(&_vtable_SuiDesigner$ToolSelect);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ToolSelect;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ToolSelect_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ToolSelect * SuiDesigner$ToolSelect_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ToolSelect *self = calloc(1, sizeof(SuiDesigner$ToolSelect));
	
    SuiDesigner$ToolSelect_init(self, pOwner);
    return self;
}


// class members
bool  SuiDesigner$ToolSelect$isModeTranslate(SuiDesigner$ToolSelect *  self){
	return Orc$String$equals(self->mode, "translate") ; 
}


bool  SuiDesigner$ToolSelect$isModeRotate(SuiDesigner$ToolSelect *  self){
	return Orc$String$equals(self->mode, "rotate") ; 
}


bool  SuiDesigner$ToolSelect$isModeScale(SuiDesigner$ToolSelect *  self){
	return Orc$String$equals(self->mode, "scale") ; 
}


void  SuiDesigner$ToolSelect$reactSpaceButton(SuiDesigner$ToolSelect *  self, SuiView$DrawButton *  o){
	URGC_VAR_CLEANUP SuiDesigner$__Block_152_40*  __var___Block_152_40 = (__var___Block_152_40=NULL,urgc_init_var((void**)&__var___Block_152_40, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_152_40) , __finiBlock___Block_152_40) ));
	urgc_set_field_class(__var___Block_152_40, (void * )offsetof(SuiDesigner$__Block_152_40, self) , self) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_154_18*  tmpReturn_1 = NULL;
	urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_154_18(&tmpReturn_1, __var___Block_152_40) ) ;
	o->normalBg = 0;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_2, self->spaceWorld ? "../asset/icon-light/space-world.png" : "../asset/icon-light/space-local.png") ) ;
}


void  SuiDesigner$ToolSelect$reactModeButton(SuiDesigner$ToolSelect *  self, SuiView$DrawButton *  o, const char *  mode){
	URGC_VAR_CLEANUP SuiDesigner$__Block_165_57*  __var___Block_165_57 = (__var___Block_165_57=NULL,urgc_init_var((void**)&__var___Block_165_57, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_165_57) , __finiBlock___Block_165_57) ));
	__var___Block_165_57->mode = mode;
	urgc_set_field_class(__var___Block_165_57, (void * )offsetof(SuiDesigner$__Block_165_57, self) , self) ;
	o->isActive = Orc$String$equals(self->mode, __var___Block_165_57->mode) ;
	o->normalBg = 0;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_168_20*  tmpReturn_1 = NULL;
	urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_168_20(&tmpReturn_1, __var___Block_165_57) ) ;
	if (Orc$strEq(__var___Block_165_57->mode, "translate") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_2, "../asset/icon-light/translate.png") ) ;
	}
	if (Orc$strEq(__var___Block_165_57->mode, "rotate") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_3, "../asset/icon-light/rotate.png") ) ;
	}
	if (Orc$strEq(__var___Block_165_57->mode, "scale") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, src) , Orc$Path_resolveFromExecutionDir(&tmpReturn_4, "../asset/icon-light/scale.png") ) ;
	}
}


void  SuiDesigner$ToolSelect$onEnable(SuiDesigner$ToolSelect *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_186_19*  __var___Block_186_19 = (__var___Block_186_19=NULL,urgc_init_var((void**)&__var___Block_186_19, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_186_19) , __finiBlock___Block_186_19) ));
	urgc_set_field_class(__var___Block_186_19, (void * )offsetof(SuiDesigner$__Block_186_19, self) , self) ;
	printf("onEnable ToolSelect\n.") ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_188_28*  tmpReturn_1 = NULL;
	urgc_set_field(self->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_188_28(&tmpReturn_1, __var___Block_186_19) ) ;
}


void  SuiDesigner$ToolSelect$onDisable(SuiDesigner$ToolSelect *  self){
	printf("onDisable ToolSelect\n.") ;
}


void  SuiDesigner$ToolSelect$draw2d(SuiDesigner$ToolSelect *  self, SuiCore$Canvas *  canvas){
	
}


void  SuiDesigner$ToolSelect$reactGizmosView(SuiDesigner$ToolSelect *  self, SuiCore$Node *  o){
	
}


void  SuiDesigner$ToolSelect$onEvent(SuiDesigner$ToolSelect *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			URGC_VAR_CLEANUP_CLASS Sgl$Raycaster*  raycaster = (raycaster=NULL,urgc_init_var_class((void**)&raycaster, Sgl$Raycaster_new(&raycaster) ));
			raycaster->ray = ((SuiDesigner$ToolBase * )self)->mgr->camera->mkRay(((SuiDesigner$ToolBase * )self)->mgr->camera, me->ndcPos) ;
			Sgl$RayCheckResult r = raycaster->raycastTree(raycaster, ((SuiDesigner$ToolBase * )self)->mgr->scene) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			printf("\n\nToolSelect. ndcPos:%s onClick succ:%d dist:%f, point:%s, name:%s\n", SuiCore$Vec2$toString(&tmpReturn_1, &me->ndcPos) ->str, r.succ, r.distance, SuiCore$Vec3$toString(&tmpReturn_2, &r.point) ->str, r.obj ? ((SuiCore$Node * )r.obj)->name->str : "null") ;
			if (r.succ) {
				((SuiDesigner$ToolBase * )self)->mgr->editor->selectByNode(((SuiDesigner$ToolBase * )self)->mgr->editor, r.obj) ;
				printf("选中对象....") ;
			}
		}
	}
}


void  SuiDesigner$ToolSelect$reactGizmo(SuiDesigner$ToolSelect *  self, Sgl$Obj3d *  o){
	URGC_VAR_CLEANUP SuiDesigner$__Block_260_29*  __var___Block_260_29 = (__var___Block_260_29=NULL,urgc_init_var((void**)&__var___Block_260_29, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_260_29) , __finiBlock___Block_260_29) ));
	urgc_set_field_class(__var___Block_260_29, (void * )offsetof(SuiDesigner$__Block_260_29, self) , self) ;
	__var___Block_260_29->dragging = false;
	URGC_VAR_CLEANUP void  (**cbOnEvent)(void *  self, SuiCore$Event *  e) = NULL;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_278*  tmpReturn_1 = NULL;
	(urgc_set_var(&cbOnEvent, __make___Closure_cbOnEvent_278(&tmpReturn_1, __var___Block_260_29) ) );
	Sgl$Obj3d *  obj3d = ((SuiDesigner$ToolBase * )self)->mgr->selectNode;
	if (Orc_instanceof((Object*)obj3d, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		if (self->isModeTranslate(self) ) {
			URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_2 = NULL;
			SuiDesigner$SglGizmo_translate(&tmpReturn_2, o, 0, obj3d) ;
		}
		else if (self->isModeScale(self) ) {
			URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_3 = NULL;
			SuiDesigner$SglGizmo_scale(&tmpReturn_3, o, 0, obj3d) ;
		}
		else if (self->isModeRotate(self) ) {
			URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_4 = NULL;
			SuiDesigner$SglGizmo_rotate(&tmpReturn_4, o, 0, obj3d) ;
		}
	}
	if (Orc_instanceof((Object*)((SuiDesigner$ToolBase * )self)->mgr->selectNode, (Vtable_Object*)Vtable_Sgl$PerspectiveCamera_init(NULL))) {
		Sgl$PerspectiveCamera *  cam = (Sgl$PerspectiveCamera * )((SuiDesigner$ToolBase * )self)->mgr->selectNode;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_5 = NULL;
		{
			Sgl$Mesh*  __scopeVar_348_12 = Sgl$mkMesh(&tmpReturn_5, o, 0) , *o = __scopeVar_348_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_348_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryLine_new(&geom) ));
				((Sgl$Camera * )cam)->updateProjectionMat(cam) ;
				((Sgl$Camera * )cam)->updateViewMat(cam) ;
				geom->buildCameraHelper(geom, cam) ;
				urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_6 = NULL;
				urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_6) ) ;
				o->material->load(o->material, "../asset/line.matl.json") ;
			}
			((Sgl$Obj3d * )o)->position = ((Sgl$Obj3d * )cam)->localToWorld(cam, SuiCore$mkVec3(0, 0, 0) ) ;
			Sgl$Mat$decompose(&((Sgl$Obj3d * )cam)->_world_transform, &((Sgl$Obj3d * )o)->position, &((Sgl$Obj3d * )o)->quaternion, &((Sgl$Obj3d * )o)->scale) ;
			((Sgl$Obj3d * )o)->rotation = SuiCore$Quaternion$toVec3AsEuler(&((Sgl$Obj3d * )o)->quaternion, NULL) ;
		}
	}
	else if (Orc_instanceof((Object*)((SuiDesigner$ToolBase * )self)->mgr->selectNode, (Vtable_Object*)Vtable_Sgl$SpotLight_init(NULL))) {
		Sgl$SpotLight *  l = (Sgl$SpotLight * )((SuiDesigner$ToolBase * )self)->mgr->selectNode;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_7 = NULL;
		{
			Sgl$Mesh*  __scopeVar_373_12 = Sgl$mkMesh(&tmpReturn_7, o, 0) , *o = __scopeVar_373_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_373_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP_CLASS Sgl$GeometryLine*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometryLine_new(&geom) ));
				geom->buildSpotLightHelper(geom, l) ;
				urgc_set_field(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_8 = NULL;
				urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_8) ) ;
				o->material->load(o->material, "../asset/line.matl.json") ;
			}
			((Sgl$Obj3d * )o)->position = ((Sgl$Obj3d * )l)->localToWorld(l, SuiCore$mkVec3(0, 0, 0) ) ;
		}
	}
	else if (Orc_instanceof((Object*)((SuiDesigner$ToolBase * )self)->mgr->selectNode, (Vtable_Object*)Vtable_Sgl$PointLight_init(NULL))) {
		Sgl$PointLight *  l = (Sgl$PointLight * )((SuiDesigner$ToolBase * )self)->mgr->selectNode;
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpReturn_9 = NULL;
		{
			Sgl$Mesh*  __scopeVar_388_12 = Sgl$mkMesh(&tmpReturn_9, o, 0) , *o = __scopeVar_388_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_388_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			if (((SuiCore$Node * )o)->isNewForReact) {
				URGC_VAR_CLEANUP_CLASS Sgl$GeometrySphere*  geom = (geom=NULL,urgc_init_var_class((void**)&geom, Sgl$GeometrySphere_new(&geom) ));
				geom->radius = l->distance;
				geom->widthSegments = 8;
				geom->heightSegments = 8;
				((Sgl$Geometry * )geom)->build(geom) ;
				urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_10 = NULL;
				urgc_set_field_class(o, (void * )offsetof(Sgl$Mesh, material) , Sgl$Material_new(&tmpNewOwner_10) ) ;
				o->material->load(o->material, "../asset/box.matl.json") ;
				o->material->wireframe = true;
			}
			((Sgl$Obj3d * )o)->position = ((Sgl$Obj3d * )l)->localToWorld(l, SuiCore$mkVec3(0, 0, 0) ) ;
		}
	}
}




//vtable instance
Vtable_SuiDesigner$ToolMgr _vtable_SuiDesigner$ToolMgr;

// init meta

void SuiDesigner$ToolMgr_initMeta(Vtable_SuiDesigner$ToolMgr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "tool", ((Vtable_Object*)Vtable_SuiDesigner$ToolBase_init(0)), offsetof(SuiDesigner$ToolMgr, tool), true, false, 1);
	orc_metaField_class(&pNext, "selectNode", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$ToolMgr, selectNode), true, false, 1);
	orc_metaField_class(&pNext, "scene", ((Vtable_Object*)Vtable_Sgl$Scene_init(0)), offsetof(SuiDesigner$ToolMgr, scene), true, false, 1);
	orc_metaField_class(&pNext, "camera", ((Vtable_Object*)Vtable_Sgl$Camera_init(0)), offsetof(SuiDesigner$ToolMgr, camera), true, false, 1);
	orc_metaField_class(&pNext, "editCtx", ((Vtable_Object*)Vtable_SuiDesigner$SglEditCtx_init(0)), offsetof(SuiDesigner$ToolMgr, editCtx), true, false, 1);
	orc_metaField_class(&pNext, "drawCtx", ((Vtable_Object*)Vtable_Sgl$DrawCtx_init(0)), offsetof(SuiDesigner$ToolMgr, drawCtx), true, false, 1);
	orc_metaField_class(&pNext, "editor", ((Vtable_Object*)Vtable_HoroEditor$HoroEditor_init(0)), offsetof(SuiDesigner$ToolMgr, editor), true, false, 1);
	orc_metaField_class(&pNext, "gizmosView", ((Vtable_Object*)Vtable_SuiCore$Node_init(0)), offsetof(SuiDesigner$ToolMgr, gizmosView), false, true, 1);

	orc_metaField_method(&pNext, "setTool", offsetof(SuiDesigner$ToolMgr, setTool));
	orc_metaField_method(&pNext, "onEvent", offsetof(SuiDesigner$ToolMgr, onEvent));
	orc_metaField_method(&pNext, "reactGizmo", offsetof(SuiDesigner$ToolMgr, reactGizmo));
	orc_metaField_method(&pNext, "_reactGizmosForNode", offsetof(SuiDesigner$ToolMgr, _reactGizmosForNode));
	orc_metaField_method(&pNext, "reactGizmosView", offsetof(SuiDesigner$ToolMgr, reactGizmosView));
	orc_metaField_method(&pNext, "draw2d", offsetof(SuiDesigner$ToolMgr, draw2d));
}


// vtable init


Vtable_SuiDesigner$ToolMgr* Vtable_SuiDesigner$ToolMgr_init(Vtable_SuiDesigner$ToolMgr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ToolMgr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ToolMgr_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ToolMgr";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ToolMgr_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ToolMgr_fini(SuiDesigner$ToolMgr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->tool);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->selectNode);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->scene);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->camera);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->editCtx);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->drawCtx);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->editor);

}

// init fields function


void SuiDesigner$ToolMgr_init_fields(SuiDesigner$ToolMgr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ToolMgr_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->tool, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->selectNode, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->scene, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->camera, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->editCtx, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->drawCtx, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner$ToolMgr*)self)->editor, NULL);
    }
	((SuiDesigner$ToolMgr*)self)->setTool = (void*)SuiDesigner$ToolMgr$setTool;
	((SuiDesigner$ToolMgr*)self)->onEvent = (void*)SuiDesigner$ToolMgr$onEvent;
	((SuiDesigner$ToolMgr*)self)->reactGizmo = (void*)SuiDesigner$ToolMgr$reactGizmo;
	((SuiDesigner$ToolMgr*)self)->_reactGizmosForNode = (void*)SuiDesigner$ToolMgr$_reactGizmosForNode;
	((SuiDesigner$ToolMgr*)self)->reactGizmosView = (void*)SuiDesigner$ToolMgr$reactGizmosView;
	((SuiDesigner$ToolMgr*)self)->draw2d = (void*)SuiDesigner$ToolMgr$draw2d;
}

// init function

void SuiDesigner$ToolMgr_init(SuiDesigner$ToolMgr *self, void *pOwner){
    Vtable_SuiDesigner$ToolMgr_init(&_vtable_SuiDesigner$ToolMgr);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ToolMgr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ToolMgr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ToolMgr * SuiDesigner$ToolMgr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ToolMgr *self = calloc(1, sizeof(SuiDesigner$ToolMgr));
	
    SuiDesigner$ToolMgr_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$ToolMgr$setTool(SuiDesigner$ToolMgr *  self, SuiDesigner$ToolBase *  tool){
	if (self->tool == tool) {
		return ; 
	}
	if (self->tool) {
		self->tool->onDisable(self->tool) ;
	}
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$ToolMgr, tool) , tool) ;
	if (self->tool) {
		urgc_set_field_class(self->tool, (void * )offsetof(SuiDesigner$ToolBase, mgr) , self) ;
		self->tool->onEnable(self->tool) ;
	}
}


void  SuiDesigner$ToolMgr$onEvent(SuiDesigner$ToolMgr *  self, SuiCore$Event *  e){
	if (self->tool) {
		self->tool->onEvent(self->tool, e) ;
	}
}


void  SuiDesigner$ToolMgr$reactGizmo(SuiDesigner$ToolMgr *  self, SuiDesigner$SglGizmo *  gizmoScene){
	if (self->tool) {
		{
			Sgl$Scene*  o = gizmoScene->scene;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_443_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			self->tool->reactGizmo(self->tool, gizmoScene->scene) ;
		}
	}
}


void  SuiDesigner$ToolMgr$_reactGizmosForNode(SuiDesigner$ToolMgr *  self, SuiCore$Node *  n){
	URGC_VAR_CLEANUP SuiDesigner$__Block_449_37*  __var___Block_449_37 = (__var___Block_449_37=NULL,urgc_init_var((void**)&__var___Block_449_37, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_449_37) , __finiBlock___Block_449_37) ));
	__var___Block_449_37->n = n;
	urgc_set_field_class(__var___Block_449_37, (void * )offsetof(SuiDesigner$__Block_449_37, self) , self) ;
	SuiCore$Node *  o = self->gizmosView;
	if (self->drawCtx && __var___Block_449_37->n == self->drawCtx->camera) {
		return ; 
	}
	if (Orc_instanceof((Object*)__var___Block_449_37->n, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		Sgl$Obj3d *  obj3d = (Sgl$Obj3d * )__var___Block_449_37->n;
		if (Orc_instanceof((Object*)__var___Block_449_37->n, (Vtable_Object*)Vtable_Sgl$Light_init(NULL))) {
			URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_1 = NULL;
			{
				SuiView$ImageView*  __scopeVar_458_16 = SuiView$mkImageView(&tmpReturn_1, o, (long long )__var___Block_449_37->n) , *o = __scopeVar_458_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_458_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
				o->setSrc(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_2, "../asset/gizmo/light.png") ) ;
				((SuiCore$View * )o)->width = 32;
				o->setImageMode(o, SuiView$WidthFix) ;
				SuiCore$Vec3 worldPos = obj3d->localToWorld(obj3d, SuiCore$mkVec3(0, 0, 0) ) ;
				SuiCore$Vec3 clientPos = self->camera->project(self->camera, worldPos) ;
				SuiCore$Vec2 clientSize = SuiCore$Frame$getSize(&((SuiCore$ViewBase * )self->editCtx->sceneView)->frame) ;
				((SuiCore$ViewBase * )o)->frame.x = SuiCore$Vec2$width(&clientSize)  * (clientPos.x + 1.0) / 2.0 - ((SuiCore$ViewBase * )o)->frame.width / 2.0;
				((SuiCore$ViewBase * )o)->frame.y = SuiCore$Vec2$height(&clientSize)  * (1.0 - (clientPos.y + 1.0) / 2.0) - ((SuiCore$ViewBase * )o)->frame.height / 2.0;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_472_34*  tmpReturn_3 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_472_34(&tmpReturn_3, __var___Block_449_37) ) ;
			}
		}
		else if (Orc_instanceof((Object*)__var___Block_449_37->n, (Vtable_Object*)Vtable_Sgl$Camera_init(NULL))) {
			URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_4 = NULL;
			{
				SuiView$ImageView*  __scopeVar_485_16 = SuiView$mkImageView(&tmpReturn_4, o, (long long )__var___Block_449_37->n) , *o = __scopeVar_485_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_485_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
				o->setSrc(o, Orc$Path_resolveFromExecutionDir(&tmpReturn_5, "../asset/gizmo/camera.png") ) ;
				((SuiCore$View * )o)->width = 32;
				o->setImageMode(o, SuiView$WidthFix) ;
				SuiCore$Vec3 worldPos = obj3d->localToWorld(obj3d, SuiCore$mkVec3(0, 0, 0) ) ;
				SuiCore$Vec3 clientPos = self->camera->project(self->camera, worldPos) ;
				SuiCore$Vec2 clientSize = SuiCore$Frame$getSize(&((SuiCore$ViewBase * )self->editCtx->sceneView)->frame) ;
				((SuiCore$ViewBase * )o)->frame.x = SuiCore$Vec2$width(&clientSize)  * (clientPos.x + 1.0) / 2.0 - ((SuiCore$ViewBase * )o)->frame.width / 2.0;
				((SuiCore$ViewBase * )o)->frame.y = SuiCore$Vec2$height(&clientSize)  * (1.0 - (clientPos.y + 1.0) / 2.0) - ((SuiCore$ViewBase * )o)->frame.height / 2.0;
				URGC_VAR_CLEANUP SuiDesigner$__Closure_498_34*  tmpReturn_6 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_498_34(&tmpReturn_6, __var___Block_449_37) ) ;
			}
		}
	}
}


void  SuiDesigner$ToolMgr$reactGizmosView(SuiDesigner$ToolMgr *  self, SuiCore$Node *  o){
	self->gizmosView = o;
	SuiCore$Node$walk((SuiCore$Node * )self->scene, self->_reactGizmosForNode, self) ;
	if (self->tool) {
		self->tool->reactGizmosView(self->tool, o) ;
	}
}


void  SuiDesigner$ToolMgr$draw2d(SuiDesigner$ToolMgr *  self, SuiCore$Canvas *  canvas){
	if (self->tool) {
		self->tool->draw2d(self->tool, canvas) ;
	}
}



static void  __finiBlock___Block_152_40(SuiDesigner$__Block_152_40 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_152_40, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_165_57(SuiDesigner$__Block_165_57 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_165_57, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_186_19(SuiDesigner$__Block_186_19 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_186_19, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_260_29(SuiDesigner$__Block_260_29 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_260_29, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_449_37(SuiDesigner$__Block_449_37 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_449_37, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_154_18(SuiDesigner$__Closure_154_18 *  self, SuiCore$MouseEvent *  e){
	self->__var___Block_152_40->self->spaceWorld = !self->__var___Block_152_40->self->spaceWorld;
	((SuiDesigner$ToolBase * )self->__var___Block_152_40->self)->mgr->editor->invalidReact->invalid(((SuiDesigner$ToolBase * )self->__var___Block_152_40->self)->mgr->editor->invalidReact) ;
}

static void  __fini___Closure_154_18(SuiDesigner$__Closure_154_18 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_154_18, __var___Block_152_40) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_154_18*  __make___Closure_154_18(SuiDesigner$__Closure_154_18 **  __outRef__, SuiDesigner$__Block_152_40 *  __var___Block_152_40){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_154_18*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_154_18) , __fini___Closure_154_18) ));
	self->invoke = __fn___Closure_154_18;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_154_18, __var___Block_152_40) , __var___Block_152_40) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_168_20(SuiDesigner$__Closure_168_20 *  self, SuiCore$MouseEvent *  e){
	Orc$String$set(self->__var___Block_165_57->self->mode, self->__var___Block_165_57->mode) ;
	((SuiDesigner$ToolBase * )self->__var___Block_165_57->self)->mgr->editor->invalidReact->invalid(((SuiDesigner$ToolBase * )self->__var___Block_165_57->self)->mgr->editor->invalidReact) ;
}

static void  __fini___Closure_168_20(SuiDesigner$__Closure_168_20 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_168_20, __var___Block_165_57) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_168_20*  __make___Closure_168_20(SuiDesigner$__Closure_168_20 **  __outRef__, SuiDesigner$__Block_165_57 *  __var___Block_165_57){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_168_20*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_168_20) , __fini___Closure_168_20) ));
	self->invoke = __fn___Closure_168_20;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_168_20, __var___Block_165_57) , __var___Block_165_57) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_188_28(SuiDesigner$__Closure_188_28 *  self, SuiView$Drag *  d){
	printf("on drag gizmo left\n") ;
	SuiCore$Vec3$add3fLocal(&self->__var___Block_186_19->self->leftPos, d->deltaPos.x, -d->deltaPos.y, 0) ;
}

static void  __fini___Closure_188_28(SuiDesigner$__Closure_188_28 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_188_28, __var___Block_186_19) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_188_28*  __make___Closure_188_28(SuiDesigner$__Closure_188_28 **  __outRef__, SuiDesigner$__Block_186_19 *  __var___Block_186_19){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_188_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_188_28) , __fini___Closure_188_28) ));
	self->invoke = __fn___Closure_188_28;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_188_28, __var___Block_186_19) , __var___Block_186_19) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_cbOnEvent_278(SuiDesigner$__Closure_cbOnEvent_278 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$ViewEvent_init(NULL))) {
		SuiCore$ViewEvent *  ve = (SuiCore$ViewEvent * )e;
	}
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		self->__var___Block_260_29->self->drag->onMouseDown(self->__var___Block_260_29->self->drag, me) ;
		if (((SuiCore$ViewEvent * )me)->isCapture) {
			printf("box gizmo.cbOnEvent:%s. %s. dragging:%d isCapture:%d\n", e->name->str, ((SuiCore$ViewEvent * )me)->target->name->str, self->__var___Block_260_29->dragging, ((SuiCore$ViewEvent * )me)->isCapture) ;
		}
	}
}

static void  __fini___Closure_cbOnEvent_278(SuiDesigner$__Closure_cbOnEvent_278 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_278, __var___Block_260_29) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_cbOnEvent_278*  __make___Closure_cbOnEvent_278(SuiDesigner$__Closure_cbOnEvent_278 **  __outRef__, SuiDesigner$__Block_260_29 *  __var___Block_260_29){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_cbOnEvent_278*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_cbOnEvent_278) , __fini___Closure_cbOnEvent_278) ));
	self->invoke = __fn___Closure_cbOnEvent_278;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_cbOnEvent_278, __var___Block_260_29) , __var___Block_260_29) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_472_34(SuiDesigner$__Closure_472_34 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClick(me) ) {
			printf("click light\n") ;
			self->__var___Block_449_37->self->editor->selectByNode(self->__var___Block_449_37->self->editor, self->__var___Block_449_37->n) ;
		}
	}
}

static void  __fini___Closure_472_34(SuiDesigner$__Closure_472_34 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_472_34, __var___Block_449_37) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_472_34*  __make___Closure_472_34(SuiDesigner$__Closure_472_34 **  __outRef__, SuiDesigner$__Block_449_37 *  __var___Block_449_37){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_472_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_472_34) , __fini___Closure_472_34) ));
	self->invoke = __fn___Closure_472_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_472_34, __var___Block_449_37) , __var___Block_449_37) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_498_34(SuiDesigner$__Closure_498_34 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClick(me) ) {
			printf("click camera\n") ;
			self->__var___Block_449_37->self->editor->selectByNode(self->__var___Block_449_37->self->editor, self->__var___Block_449_37->n) ;
		}
	}
}

static void  __fini___Closure_498_34(SuiDesigner$__Closure_498_34 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_498_34, __var___Block_449_37) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_498_34*  __make___Closure_498_34(SuiDesigner$__Closure_498_34 **  __outRef__, SuiDesigner$__Block_449_37 *  __var___Block_449_37){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_498_34*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_498_34) , __fini___Closure_498_34) ));
	self->invoke = __fn___Closure_498_34;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_498_34, __var___Block_449_37) , __var___Block_449_37) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



