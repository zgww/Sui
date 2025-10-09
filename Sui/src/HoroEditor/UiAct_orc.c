
#include "UiAct_orc.h" 

#include "../Orc/Orc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "./HoroEditCtx_orc.h"
#include "./HoroEditor_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../SuiDesigner/FileItem_orc.h"
#include "../SuiDesigner/Prefab_orc.h"
#include "../SuiDesigner/EventFileItemChanged_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sgl/Obj3d_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/GeometryBox_orc.h"
#include "../Sgl/GeometrySphere_orc.h"
#include "../Sgl/GeometryPlane_orc.h"
#include "../Sgl/GeometryCapsule_orc.h"


// static struct 
typedef struct tagHoroEditor$__Block_38_43 HoroEditor$__Block_38_43;

typedef struct tagHoroEditor$__Block_120_56 HoroEditor$__Block_120_56;

typedef struct tagHoroEditor$__Closure_51_57 HoroEditor$__Closure_51_57;

typedef struct tagHoroEditor$__Closure_121_57 HoroEditor$__Closure_121_57;



struct tagHoroEditor$__Block_38_43 {
	SuiDesigner$FileItem*  parent ;
};





struct tagHoroEditor$__Block_120_56 {
	SuiDesigner$FileItem*  parent ;
	Orc$String*  cmd ;
};





struct tagHoroEditor$__Closure_51_57 {
	void  (*invoke)(HoroEditor$__Closure_51_57 *  self, Orc$String*  newName);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_38_43*  __var___Block_38_43 ;
};





struct tagHoroEditor$__Closure_121_57 {
	void  (*invoke)(HoroEditor$__Closure_121_57 *  self, Orc$String*  newName);
	Vtable_Object *  vtable ;
	HoroEditor$__Block_120_56*  __var___Block_120_56 ;
};





// static function declaration
static void  __finiBlock___Block_38_43(HoroEditor$__Block_38_43 *  self);
static void  __finiBlock___Block_120_56(HoroEditor$__Block_120_56 *  self);
static void  __fn___Closure_51_57(HoroEditor$__Closure_51_57 *  self, Orc$String*  newName);
static void  __fini___Closure_51_57(HoroEditor$__Closure_51_57 *  self);
static HoroEditor$__Closure_51_57*  __make___Closure_51_57(HoroEditor$__Closure_51_57 **  __outRef__, HoroEditor$__Block_38_43 *  __var___Block_38_43);
static void  __fn___Closure_121_57(HoroEditor$__Closure_121_57 *  self, Orc$String*  newName);
static void  __fini___Closure_121_57(HoroEditor$__Closure_121_57 *  self);
static HoroEditor$__Closure_121_57*  __make___Closure_121_57(HoroEditor$__Closure_121_57 **  __outRef__, HoroEditor$__Block_120_56 *  __var___Block_120_56);


void  HoroEditor$UiAct_createPrefab3d(SuiDesigner$FileItem*  parent){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parent);

	URGC_VAR_CLEANUP HoroEditor$__Block_38_43*  __var___Block_38_43 = (__var___Block_38_43=NULL,urgc_init_var((void**)&__var___Block_38_43, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_38_43) , __finiBlock___Block_38_43) ));
	urgc_set_field_class(__var___Block_38_43, (void * )offsetof(HoroEditor$__Block_38_43, parent) , parent) ;
	if (__var___Block_38_43->parent && !__var___Block_38_43->parent->isDirectory) {
		urgc_set_field_class(__var___Block_38_43, (void * )offsetof(HoroEditor$__Block_38_43, parent) , __var___Block_38_43->parent->parent) ;
	}
	if (!__var___Block_38_43->parent) {
		SuiDialog$MessageDialog_alert("未指定父目录", "tip") ;
		return ; 
	}
	URGC_VAR_CLEANUP HoroEditor$__Closure_51_57*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt("新建预制3d.prefab.json", "新建预制3d", __make___Closure_51_57(&tmpReturn_1, __var___Block_38_43) ) ;
}

void  HoroEditor$UiAct_savePrefab(HoroEditor$HoroEditor *  editor){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroEditCtx*  ctx = (ctx=NULL,urgc_init_var_class((void**)&ctx, editor->editCtx));
	if (ctx->prefab) {
		ctx->prefab->save(ctx->prefab) ;
		char  tmp[1000];
		sprintf(tmp, "保存场景%s成功", ctx->prefab->_path->str) ;
		SuiDialog$Toast_make(tmp) ;
	}
}

void  HoroEditor$UiAct_addView(HoroEditor$HoroEditor *  editor, SuiDesigner$ANode*  anode, Orc$String*  viewName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anode);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(viewName);

	if (!anode->node) {
		SuiDialog$Toast_make("node is null") ;
		return ; 
	}
	SuiCore$NodeLib *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$NodeRegisterInfo*  info = (tmpThis_1 = SuiCore$NodeLib_use() )->findByClassName((info = NULL,&info), tmpThis_1, viewName->str) ;
	if (!info) {
		SuiDialog$Toast_make("未找到节点类") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$ANode*  o = SuiDesigner$ANode_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$ANode, tag) , viewName) ;
		anode->appendChild(anode, o) ;
		o->updateSubTreeNodes(o) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_2 = NULL;
		{
			SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_2) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeChanged, anode) , anode) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}

void  HoroEditor$UiAct_createGeometry(SuiDesigner$FileItem*  parent, Orc$String*  cmd){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parent);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(cmd);

	URGC_VAR_CLEANUP HoroEditor$__Block_120_56*  __var___Block_120_56 = (__var___Block_120_56=NULL,urgc_init_var((void**)&__var___Block_120_56, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Block_120_56) , __finiBlock___Block_120_56) ));
	urgc_set_field_class(__var___Block_120_56, (void * )offsetof(HoroEditor$__Block_120_56, cmd) , cmd) ;
	urgc_set_field_class(__var___Block_120_56, (void * )offsetof(HoroEditor$__Block_120_56, parent) , parent) ;
	URGC_VAR_CLEANUP HoroEditor$__Closure_121_57*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt("box.geometry.json", "新建几何体实例", __make___Closure_121_57(&tmpReturn_1, __var___Block_120_56) ) ;
}

static void  __finiBlock___Block_38_43(HoroEditor$__Block_38_43 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_38_43, parent) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_120_56(HoroEditor$__Block_120_56 *  self){
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_120_56, parent) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(HoroEditor$__Block_120_56, cmd) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_51_57(HoroEditor$__Closure_51_57 *  self, Orc$String*  newName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newName);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  path = (path=NULL,urgc_init_var_class((void**)&path, Orc$String$addString(Orc$String$add(Orc$String$clone(&tmpReturn_1, self->__var___Block_38_43->parent->path) , "/") , newName) ));
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Prefab*  prefab = (prefab=NULL,urgc_init_var_class((void**)&prefab, SuiDesigner$Prefab_new(&prefab) ));
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  tmpReturn_2 = NULL;
	urgc_set_field_class(prefab, (void * )offsetof(SuiDesigner$Prefab, root) , SuiDesigner$mkANodeByTag(&tmpReturn_2, Vtable_getClassName(Vtable_Sgl$Obj3d_init(NULL)) ) ) ;
	Json$Json *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = (tmpThis_1 = prefab->toJson(&tmpReturn_3, prefab) )->dump((text = NULL,&text), tmpThis_1) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	SuiDialog$MessageDialog_alert(Orc$String$add(Orc$str(&tmpReturn_4, "新建预制. 路径") , path->str) ->str, "tip") ;
	if (Orc$Path_writeText(path->str, text->str) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		SuiDialog$MessageDialog_alert(Orc$String$add(Orc$str(&tmpReturn_5, "新建预制成功. 路径") , path->str) , "tip") ;
		self->__var___Block_38_43->parent->loadSubtree(self->__var___Block_38_43->parent) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_6 = NULL;
		{
			SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_6) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , self->__var___Block_38_43->parent) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}

static void  __fini___Closure_51_57(HoroEditor$__Closure_51_57 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_51_57, __var___Block_38_43) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_51_57*  __make___Closure_51_57(HoroEditor$__Closure_51_57 **  __outRef__, HoroEditor$__Block_38_43 *  __var___Block_38_43){
	URGC_VAR_CLEANUP HoroEditor$__Closure_51_57*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_51_57) , __fini___Closure_51_57) ));
	self->invoke = __fn___Closure_51_57;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_51_57, __var___Block_38_43) , __var___Block_38_43) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_121_57(HoroEditor$__Closure_121_57 *  self, Orc$String*  newName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newName);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  path = (path=NULL,urgc_init_var_class((void**)&path, Orc$String$addString(Orc$String$add(Orc$String$clone(&tmpReturn_1, self->__var___Block_120_56->parent->path) , "/") , newName) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  geom = NULL;
	if (Orc$String$equals(self->__var___Block_120_56->cmd, "CreateGeometry/Box") ) {
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryBox*  tmpNewOwner_2 = NULL;
		urgc_set_var_class(&geom, Sgl$GeometryBox_new(&tmpNewOwner_2) ) ;
	}
	else if (Orc$String$equals(self->__var___Block_120_56->cmd, "CreateGeometry/Sphere") ) {
		URGC_VAR_CLEANUP_CLASS Sgl$GeometrySphere*  tmpNewOwner_3 = NULL;
		urgc_set_var_class(&geom, Sgl$GeometrySphere_new(&tmpNewOwner_3) ) ;
	}
	else if (Orc$String$equals(self->__var___Block_120_56->cmd, "CreateGeometry/Plane") ) {
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryPlane*  tmpNewOwner_4 = NULL;
		urgc_set_var_class(&geom, Sgl$GeometryPlane_new(&tmpNewOwner_4) ) ;
	}
	else if (Orc$String$equals(self->__var___Block_120_56->cmd, "CreateGeometry/Capsule") ) {
		URGC_VAR_CLEANUP_CLASS Sgl$GeometryCapsule*  tmpNewOwner_5 = NULL;
		urgc_set_var_class(&geom, Sgl$GeometryCapsule_new(&tmpNewOwner_5) ) ;
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_toJson((jo = NULL,&jo), geom) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
	printf(" %s instance at%s:%s", self->__var___Block_120_56->cmd->str, path->str, jo->dump(&tmpReturn_6, jo) ->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
	if (Orc$Path_writeText(path->str, jo->dump(&tmpReturn_7, jo) ->str) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_9 = NULL;
		SuiDialog$Toast_make(Orc$String$replaceAll(&tmpReturn_8, Orc$str(&tmpReturn_9, "保存{0}成功") , "{0}", path->str) ->str) ;
		self->__var___Block_120_56->parent->loadSubtree(self->__var___Block_120_56->parent) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_10 = NULL;
		{
			SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_10) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , self->__var___Block_120_56->parent) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}

static void  __fini___Closure_121_57(HoroEditor$__Closure_121_57 *  self){
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_121_57, __var___Block_120_56) , NULL) ;
	urgc_free_later(self) ;
}

static HoroEditor$__Closure_121_57*  __make___Closure_121_57(HoroEditor$__Closure_121_57 **  __outRef__, HoroEditor$__Block_120_56 *  __var___Block_120_56){
	URGC_VAR_CLEANUP HoroEditor$__Closure_121_57*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(HoroEditor$__Closure_121_57) , __fini___Closure_121_57) ));
	self->invoke = __fn___Closure_121_57;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(HoroEditor$__Closure_121_57, __var___Block_120_56) , __var___Block_120_56) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



