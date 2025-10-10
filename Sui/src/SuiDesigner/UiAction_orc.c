
#include "UiAction_orc.h" 

#include "../Orc/Orc.h"
#include "./Asset/AssetDirView_orc.h"
#include "./Asset/AssetDirTreeView_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "./Prefab_orc.h"
#include "./FileItem_orc.h"
#include "../Json/Json_orc.h"
#include "./EventFileItemChanged_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./ANode_orc.h"
#include "./EditCtx_orc.h"
#include "./SceneView_orc.h"
#include "./SceneHierView_orc.h"
#include "./Project_orc.h"
#include "./ChessBgViewCallback_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/SglSceneView_orc.h"
#include "../HoroEditor/HoroEditor_orc.h"
#include "../HoroEditor/HoroGeometryPreviewView_orc.h"
#include "../HoroEditor/HoroEditCtx_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_48_44 SuiDesigner$__Block_48_44;

typedef struct tagSuiDesigner$__Block_82_42 SuiDesigner$__Block_82_42;

typedef struct tagSuiDesigner$__Block_95_47 SuiDesigner$__Block_95_47;

typedef struct tagSuiDesigner$__Block_263_39 SuiDesigner$__Block_263_39;

typedef struct tagSuiDesigner$__Block_492_42 SuiDesigner$__Block_492_42;

typedef struct tagSuiDesigner$__Closure_61_53 SuiDesigner$__Closure_61_53;

typedef struct tagSuiDesigner$__Closure_83_49 SuiDesigner$__Closure_83_49;

typedef struct tagSuiDesigner$__Closure_112_42 SuiDesigner$__Closure_112_42;

typedef struct tagSuiDesigner$__Closure_266_42 SuiDesigner$__Closure_266_42;

typedef struct tagSuiDesigner$__Closure_509_51 SuiDesigner$__Closure_509_51;



struct tagSuiDesigner$__Block_48_44 {
	SuiDesigner$FileItem*  parent ;
};





struct tagSuiDesigner$__Block_82_42 {
	SuiDesigner$FileItem*  fi ;
};





struct tagSuiDesigner$__Block_95_47 {
	SuiDesigner$FileItem*  parent ;
};





struct tagSuiDesigner$__Block_263_39 {
	SuiDesigner$ANode*  anode ;
};





struct tagSuiDesigner$__Block_492_42 {
	SuiDesigner$FileItem*  fi ;
	Orc$String*  vsPath ;
	Orc$String*  fsPath ;
	Orc$String*  basename ;
};





struct tagSuiDesigner$__Closure_61_53 {
	void  (*invoke)(SuiDesigner$__Closure_61_53 *  self, Orc$String*  newName);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_48_44*  __var___Block_48_44 ;
};





struct tagSuiDesigner$__Closure_83_49 {
	void  (*invoke)(SuiDesigner$__Closure_83_49 *  self, Orc$String*  newName);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_82_42*  __var___Block_82_42 ;
};





struct tagSuiDesigner$__Closure_112_42 {
	void  (*invoke)(SuiDesigner$__Closure_112_42 *  self, Orc$String*  newName);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_95_47*  __var___Block_95_47 ;
};





struct tagSuiDesigner$__Closure_266_42 {
	void  (*invoke)(SuiDesigner$__Closure_266_42 *  self, Orc$String*  newName);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_263_39*  __var___Block_263_39 ;
};





struct tagSuiDesigner$__Closure_509_51 {
	void  (*invoke)(SuiDesigner$__Closure_509_51 *  self, Orc$String*  newName);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_492_42*  __var___Block_492_42 ;
};





// static function declaration
static SuiDesigner$ClipboardForANodes*  useClipboardForANodes(SuiDesigner$ClipboardForANodes **  __outRef__);
static void  __finiBlock___Block_48_44(SuiDesigner$__Block_48_44 *  self);
static void  __finiBlock___Block_82_42(SuiDesigner$__Block_82_42 *  self);
static void  __finiBlock___Block_95_47(SuiDesigner$__Block_95_47 *  self);
static void  __finiBlock___Block_263_39(SuiDesigner$__Block_263_39 *  self);
static void  __finiBlock___Block_492_42(SuiDesigner$__Block_492_42 *  self);
static void  __fn___Closure_61_53(SuiDesigner$__Closure_61_53 *  self, Orc$String*  newName);
static void  __fini___Closure_61_53(SuiDesigner$__Closure_61_53 *  self);
static SuiDesigner$__Closure_61_53*  __make___Closure_61_53(SuiDesigner$__Closure_61_53 **  __outRef__, SuiDesigner$__Block_48_44 *  __var___Block_48_44);
static void  __fn___Closure_83_49(SuiDesigner$__Closure_83_49 *  self, Orc$String*  newName);
static void  __fini___Closure_83_49(SuiDesigner$__Closure_83_49 *  self);
static SuiDesigner$__Closure_83_49*  __make___Closure_83_49(SuiDesigner$__Closure_83_49 **  __outRef__, SuiDesigner$__Block_82_42 *  __var___Block_82_42);
static void  __fn___Closure_112_42(SuiDesigner$__Closure_112_42 *  self, Orc$String*  newName);
static void  __fini___Closure_112_42(SuiDesigner$__Closure_112_42 *  self);
static SuiDesigner$__Closure_112_42*  __make___Closure_112_42(SuiDesigner$__Closure_112_42 **  __outRef__, SuiDesigner$__Block_95_47 *  __var___Block_95_47);
static void  __fn___Closure_266_42(SuiDesigner$__Closure_266_42 *  self, Orc$String*  newName);
static void  __fini___Closure_266_42(SuiDesigner$__Closure_266_42 *  self);
static SuiDesigner$__Closure_266_42*  __make___Closure_266_42(SuiDesigner$__Closure_266_42 **  __outRef__, SuiDesigner$__Block_263_39 *  __var___Block_263_39);
static void  __fn___Closure_509_51(SuiDesigner$__Closure_509_51 *  self, Orc$String*  newName);
static void  __fini___Closure_509_51(SuiDesigner$__Closure_509_51 *  self);
static SuiDesigner$__Closure_509_51*  __make___Closure_509_51(SuiDesigner$__Closure_509_51 **  __outRef__, SuiDesigner$__Block_492_42 *  __var___Block_492_42);


void  SuiDesigner$UiAction_createPrefab(SuiDesigner$FileItem*  parent){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parent);

	URGC_VAR_CLEANUP SuiDesigner$__Block_48_44*  __var___Block_48_44 = (__var___Block_48_44=NULL,urgc_init_var((void**)&__var___Block_48_44, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_48_44) , __finiBlock___Block_48_44) ));
	urgc_set_field_class(__var___Block_48_44, (void * )offsetof(SuiDesigner$__Block_48_44, parent) , parent) ;
	if (__var___Block_48_44->parent && !__var___Block_48_44->parent->isDirectory) {
		urgc_set_field_class(__var___Block_48_44, (void * )offsetof(SuiDesigner$__Block_48_44, parent) , __var___Block_48_44->parent->parent) ;
	}
	if (!__var___Block_48_44->parent) {
		SuiDialog$MessageDialog_alert("未指定父目录", "tip") ;
		return ; 
	}
	URGC_VAR_CLEANUP SuiDesigner$__Closure_61_53*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt("新建预制.prefab.json", "新建预制", __make___Closure_61_53(&tmpReturn_1, __var___Block_48_44) ) ;
}

void  SuiDesigner$UiAction_renameFileItem(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP SuiDesigner$__Block_82_42*  __var___Block_82_42 = (__var___Block_82_42=NULL,urgc_init_var((void**)&__var___Block_82_42, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_82_42) , __finiBlock___Block_82_42) ));
	urgc_set_field_class(__var___Block_82_42, (void * )offsetof(SuiDesigner$__Block_82_42, fi) , fi) ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_83_49*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt(__var___Block_82_42->fi->filename->str, "重命名", __make___Closure_83_49(&tmpReturn_1, __var___Block_82_42) ) ;
}

void  SuiDesigner$UiAction_createDirectory(SuiDesigner$FileItem*  parent){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parent);

	URGC_VAR_CLEANUP SuiDesigner$__Block_95_47*  __var___Block_95_47 = (__var___Block_95_47=NULL,urgc_init_var((void**)&__var___Block_95_47, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_95_47) , __finiBlock___Block_95_47) ));
	urgc_set_field_class(__var___Block_95_47, (void * )offsetof(SuiDesigner$__Block_95_47, parent) , parent) ;
	if (true) {
		URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
		{
			Sui$Window*  o = win;
			
		
			o->setTitle(o, "hi") ;
			o->setSize(o, 400, 400) ;
			o->show(o) ;
		}
		return ; 
	}
	if (__var___Block_95_47->parent && !__var___Block_95_47->parent->isDirectory) {
		urgc_set_field_class(__var___Block_95_47, (void * )offsetof(SuiDesigner$__Block_95_47, parent) , __var___Block_95_47->parent->parent) ;
	}
	URGC_VAR_CLEANUP SuiDesigner$__Closure_112_42*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt("新建的目录", "新建目录", __make___Closure_112_42(&tmpReturn_1, __var___Block_95_47) ) ;
}

void  SuiDesigner$UiAction_deleteDirectory(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	if (Orc$Path_removeDirs(fi->path->str) ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_1 = NULL;
		{
			SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_1) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , fi->parent) ;
			fi->removeSelf(fi) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
	else {
		SuiDialog$MessageDialog_alert("删除目录失败", "tip") ;
	}
}

void  SuiDesigner$UiAction_deleteFile(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	if (!fi || !fi->parent) {
		SuiDialog$MessageDialog_alert("删除文件失败,未指定文件或者文件没有父目录", "tip") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	SuiDialog$Toast_make(Orc$String$add(Orc$str(&tmpReturn_1, "删除文件:") , fi->path->str) ->str) ;
	if (Orc$Path_remove(fi->path->str) ) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_2 = NULL;
		{
			SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_2) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , fi->parent) ;
			fi->removeSelf(fi) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
	else {
		SuiDialog$MessageDialog_alert("删除文件失败", "tip") ;
	}
}

void  SuiDesigner$UiAction_delete(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	SuiDialog$Toast_make(Orc$String$addi(Orc$String$add(Orc$String$add(Orc$str(&tmpReturn_1, "删除:") , fi->path->str) , ", 是目录?") , fi->isDirectory) ->str) ;
	if (fi->isDirectory) {
		SuiDesigner$UiAction_deleteDirectory(fi) ;
	}
	else {
		SuiDesigner$UiAction_deleteFile(fi) ;
	}
}

void  SuiDesigner$UiAction_deleteANode(SuiDesigner$ANode*  anode){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anode);

	if (!anode->parent) {
		SuiDialog$MessageDialog_alert_error("无法删除根结点", "tip") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  parent = (parent=NULL,urgc_init_var_class((void**)&parent, anode->parent));
	if (SuiDialog$MessageDialog_confirm("确认删除", "tip") ) {
		anode->removeSelf(anode) ;
		parent->updateSubTreeNodes(parent) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_1 = NULL;
		{
			SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_1) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeChanged, anode) , anode) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}


//vtable instance
Vtable_SuiDesigner$ClipboardForANodes _vtable_SuiDesigner$ClipboardForANodes;

// init meta

void SuiDesigner$ClipboardForANodes_initMeta(Vtable_SuiDesigner$ClipboardForANodes *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "list", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$ClipboardForANodes, list), true, false, 1);
	orc_metaField_class(&pNext, "kind", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$ClipboardForANodes, kind), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner$ClipboardForANodes* Vtable_SuiDesigner$ClipboardForANodes_init(Vtable_SuiDesigner$ClipboardForANodes* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$ClipboardForANodes;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$ClipboardForANodes_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$ClipboardForANodes";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$ClipboardForANodes_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$ClipboardForANodes_fini(SuiDesigner$ClipboardForANodes *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ClipboardForANodes*)self)->list);
	urgc_fini_field_class(self, (void**)&((SuiDesigner$ClipboardForANodes*)self)->kind);

}

// init fields function


void SuiDesigner$ClipboardForANodes_init_fields(SuiDesigner$ClipboardForANodes *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$ClipboardForANodes_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ClipboardForANodes*)self)->list, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$ClipboardForANodes*)self)->kind, Orc$str(&tmpReturn_2, "cut") );
    }
	
}

// init function

void SuiDesigner$ClipboardForANodes_init(SuiDesigner$ClipboardForANodes *self, void *pOwner){
    Vtable_SuiDesigner$ClipboardForANodes_init(&_vtable_SuiDesigner$ClipboardForANodes);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$ClipboardForANodes;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$ClipboardForANodes_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$ClipboardForANodes * SuiDesigner$ClipboardForANodes_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$ClipboardForANodes *self = calloc(1, sizeof(SuiDesigner$ClipboardForANodes));
	
    SuiDesigner$ClipboardForANodes_init(self, pOwner);
    return self;
}


// class members

static SuiDesigner$ClipboardForANodes*  useClipboardForANodes(SuiDesigner$ClipboardForANodes **  __outRef__){
	static URGC_VAR_CLEANUP_CLASS SuiDesigner$ClipboardForANodes*  ins = NULL;
	if (!ins) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ClipboardForANodes*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ins, SuiDesigner$ClipboardForANodes_new(&tmpNewOwner_1) ) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ins) ; 
}

void  SuiDesigner$UiAction_cutANodes(Orc$List*  anodes){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anodes);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$ClipboardForANodes*  clipboard = useClipboardForANodes((clipboard = NULL,&clipboard)) ;
	urgc_set_field_class(clipboard, (void * )offsetof(SuiDesigner$ClipboardForANodes, list) , anodes) ;
	Orc$String$set(clipboard->kind, "cut") ;
	for (int  i = 0; i < anodes->size(anodes) ; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  anode = (anode=NULL,urgc_init_var_class((void**)&anode, (SuiDesigner$ANode* )anodes->get(anodes, i) ));
		anode->removeSelf(anode) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_1) ;
		
	
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

void  SuiDesigner$UiAction_copyANodes(Orc$List*  anodes){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anodes);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$ClipboardForANodes*  clipboard = useClipboardForANodes((clipboard = NULL,&clipboard)) ;
	urgc_set_field_class(clipboard, (void * )offsetof(SuiDesigner$ClipboardForANodes, list) , anodes) ;
	Orc$String$set(clipboard->kind, "copy") ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_1) ;
		
	
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

void  SuiDesigner$UiAction_pasteANodes(SuiDesigner$ANode*  parent){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parent);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$ClipboardForANodes*  clipboard = useClipboardForANodes((clipboard = NULL,&clipboard)) ;
	if (clipboard->list && clipboard->list->size(clipboard->list)  > 0) {
		if (Orc$String$equals(clipboard->kind, "cut") ) {
			for (int  i = 0; i < clipboard->list->size(clipboard->list) ; i++) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  anode = (anode=NULL,urgc_init_var_class((void**)&anode, (SuiDesigner$ANode* )clipboard->list->get(clipboard->list, i) ));
				parent->appendChild(parent, anode) ;
			}
			parent->updateSubTreeNodes(parent) ;
			clipboard->list->clear(clipboard->list) ;
		}
		else if (Orc$String$equals(clipboard->kind, "copy") ) {
			for (int  i = 0; i < clipboard->list->size(clipboard->list) ; i++) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  anode = (anode=NULL,urgc_init_var_class((void**)&anode, (SuiDesigner$ANode* )clipboard->list->get(clipboard->list, i) ));
				URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  newANode = anode->clone((newANode = NULL,&newANode), anode) ;
				parent->appendChild(parent, newANode) ;
			}
			parent->updateSubTreeNodes(parent) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeChanged, anode) , parent) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

void  SuiDesigner$UiAction_renameANode(SuiDesigner$ANode*  anode){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anode);

	URGC_VAR_CLEANUP SuiDesigner$__Block_263_39*  __var___Block_263_39 = (__var___Block_263_39=NULL,urgc_init_var((void**)&__var___Block_263_39, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_263_39) , __finiBlock___Block_263_39) ));
	urgc_set_field_class(__var___Block_263_39, (void * )offsetof(SuiDesigner$__Block_263_39, anode) , anode) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  name = __var___Block_263_39->anode->getAttrStringValueByName((name = NULL,&name), __var___Block_263_39->anode, "name") ;
	URGC_VAR_CLEANUP SuiDesigner$__Closure_266_42*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt(name->str, "重命名", __make___Closure_266_42(&tmpReturn_1, __var___Block_263_39) ) ;
}

void  SuiDesigner$UiAction_locateView(SuiDesigner$ANode*  anode){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anode);

	if (!anode->node) {
		SuiDialog$Toast_make("node is null") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiCore$Node*  n = (n=NULL,urgc_init_var_class((void**)&n, anode->node));
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
	SuiDesigner$SceneView *  sv = SuiDesigner$EditCtx_ins(&tmpReturn_1) ->sceneView;
	SuiCore$ViewBase *  v = SuiCore$Node$getAncestorByClass(n, Vtable_SuiCore$ViewBase_init(NULL)) ;
	SuiCore$Rect svRect = ((SuiCore$ViewBase * )sv)->get_abs_rect(sv) ;
	SuiCore$Vec2 vClientPos = v->localToWorld(v, 0, 0) ;
	SuiCore$Vec2 svCenterPos = SuiCore$Rect$centerPos(&svRect) ;
	SuiCore$Vec2 translate = SuiCore$Vec2$sub(&svCenterPos, vClientPos) ;
	sv->sceneTransform->translate(sv->sceneTransform, translate.x, translate.y, 0) ;
	((SuiCore$ViewBase * )sv)->invalidDraw(sv) ;
}

void  SuiDesigner$UiAction_addView(SuiDesigner$ANode*  anode, Orc$String*  viewName){
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

void  SuiDesigner$UiAction_savePrefab(){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  ctx = SuiDesigner$EditCtx_ins((ctx = NULL,&ctx)) ;
	if (ctx->prefab) {
		ctx->prefab->save(ctx->prefab) ;
	}
}

void  SuiDesigner$UiAction_openFile(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	if (Orc$String$endsWith(fi->path, ".prefab.json") ) {
		HoroEditor$HoroEditCtx *  tmpThis_1 = NULL;
		(tmpThis_1 = HoroEditor$horoEditorIns() ->editCtx)->openPrefab(tmpThis_1, fi->path->str) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_1 = NULL;
		{
			SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_1) ;
			
		
			URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_2 = NULL;
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeChanged, anode) , SuiDesigner$EditCtx_ins(&tmpReturn_2) ->root) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
	if (Orc$String$endsWith(fi->path, "geometry.json") ) {
		URGC_VAR_CLEANUP_CLASS HoroEditor$HoroGeometryPreviewView*  tmpNewOwner_3 = NULL;
		{
			HoroEditor$HoroGeometryPreviewView*  o = HoroEditor$HoroGeometryPreviewView_new(&tmpNewOwner_3) ;
			
		
			o->showWindow(o, fi->path->str) ;
		}
	}
}

void  SuiDesigner$UiAction_closeCurrentPrefab(){
	SuiDesigner$EditCtx *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiDesigner$EditCtx_ins(&tmpReturn_1) )->closeCurrentPrefab(tmpThis_1) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_2 = NULL;
	{
		SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_2) ;
		
	
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EditCtx*  tmpReturn_3 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeChanged, anode) , SuiDesigner$EditCtx_ins(&tmpReturn_3) ->root) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

void  SuiDesigner$UiAction_showImageInNewWindow(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	{
		Sui$Window*  o = win;
		
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpNewOwner_1 = NULL;
		{
			SuiLayout$LayoutAlign*  o = SuiLayout$LayoutAlign_new(&tmpNewOwner_1) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_367_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			win->setRootView(win, o) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner$ChessBgViewCallback*  tmp = (tmp=NULL,urgc_init_var_class((void**)&tmp, SuiDesigner$ChessBgViewCallback_new(&tmp) ));
			urgc_set_field(o, (void * )offsetof(SuiCore$View, cb) , tmp) ;
			URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_2 = NULL;
			{
				SuiView$ImageView*  __scopeVar_379_12 = SuiView$mkImageView(&tmpReturn_2, o, 0) , *o = __scopeVar_379_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_379_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->setSrc(o, fi->path) ;
				o->setImageMode(o, SuiView$Contain) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_3 = NULL;
				{
					SuiLayout$LayoutAlignPositionCell*  __scopeVar_386_16 = SuiLayout$layoutAlignPositionCell(&tmpReturn_3, o, 0) , *o = __scopeVar_386_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_386_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->left = 10;
					o->top = 10;
					o->right = 10;
					o->bottom = 10;
				}
			}
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		o->setTitle(o, Orc$String$addString(Orc$str(&tmpReturn_4, "图片") , fi->path) ->str) ;
		o->setSize(o, 640, 480) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}

void  SuiDesigner$UiAction_showFileInfoInNewWindow(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	{
		Sui$Window*  o = win;
		
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_1 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_1) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_407_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "start") ;
			SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 6) ;
			win->setRootView(win, o) ;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
			{
				SuiView$TextView*  __scopeVar_420_12 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_420_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_420_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  info = Orc$str((info = NULL,&info), "") ;
				long long  mtime = Orc$Path_mtimeMs(fi->path->str) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  mtimeStr = Orc$Path_mtimeStr((mtimeStr = NULL,&mtimeStr), fi->path->str) ;
				Orc$String$add(Orc$String$addString(Orc$String$add(info, "文件名：") , fi->filename) , "\n") ;
				Orc$String$add(Orc$String$addString(Orc$String$add(info, "修改时间：") , mtimeStr) , "\n") ;
				Orc$String$add(Orc$String$addString(Orc$String$add(info, "路径：") , fi->path) , "\n") ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  ext = Orc$Path_fullExt((ext = NULL,&ext), fi->path->str) ;
				Orc$String$add(Orc$String$addString(Orc$String$add(info, "后缀：") , ext) , "\n") ;
				o->setText(o, info) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_3 = NULL;
				{
					SuiLayout$LayoutAlignPositionCell*  __scopeVar_434_16 = SuiLayout$layoutAlignPositionCell(&tmpReturn_3, o, 0) , *o = __scopeVar_434_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_434_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->left = 10;
					o->top = 10;
					o->right = 10;
					o->bottom = 10;
				}
			}
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		o->setTitle(o, Orc$String$addString(Orc$str(&tmpReturn_4, "文件属性") , fi->path) ->str) ;
		o->setSize(o, 640, 480) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}

void  SuiDesigner$UiAction_showFileTextInNewWindow(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	{
		Sui$Window*  o = win;
		
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpNewOwner_1 = NULL;
		{
			SuiLayout$LayoutAlign*  o = SuiLayout$LayoutAlign_new(&tmpNewOwner_1) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_452_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			win->setRootView(win, o) ;
			URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_2 = NULL;
			{
				SuiView$ScrollArea*  __scopeVar_465_12 = SuiView$mkScrollArea(&tmpReturn_2, o, 0) , *o = __scopeVar_465_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_465_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_3 = NULL;
				{
					SuiLayout$LayoutAlignPositionCell*  __scopeVar_467_16 = SuiLayout$layoutAlignPositionCell(&tmpReturn_3, o, 0) , *o = __scopeVar_467_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_467_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->left = 10;
					o->top = 10;
					o->right = 10;
					o->bottom = 10;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
				{
					SuiView$TextView*  __scopeVar_473_16 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_473_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_473_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  text = Orc$Path_readText((text = NULL,&text), fi->path->str) ;
					URGC_VAR_CLEANUP_CLASS Orc$String*  newtext = Orc$String$replaceAll((newtext = NULL,&newtext), text, "\t", "    ") ;
					o->setText(o, newtext) ;
				}
			}
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		o->setTitle(o, Orc$String$addString(Orc$str(&tmpReturn_5, "文件属性") , fi->path) ->str) ;
		o->setSize(o, 640, 480) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}

void  SuiDesigner$UiAction_createMaterial(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP SuiDesigner$__Block_492_42*  __var___Block_492_42 = (__var___Block_492_42=NULL,urgc_init_var((void**)&__var___Block_492_42, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_492_42) , __finiBlock___Block_492_42) ));
	urgc_set_field_class(__var___Block_492_42, (void * )offsetof(SuiDesigner$__Block_492_42, fi) , fi) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(__var___Block_492_42, (void * )offsetof(SuiDesigner$__Block_492_42, basename) , Orc$Path_basename(&tmpReturn_1, __var___Block_492_42->fi->path->str) ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(__var___Block_492_42, (void * )offsetof(SuiDesigner$__Block_492_42, vsPath) , Orc$Path_withExt(&tmpReturn_2, __var___Block_492_42->fi->path->str, ".vs") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(__var___Block_492_42, (void * )offsetof(SuiDesigner$__Block_492_42, fsPath) , Orc$Path_withExt(&tmpReturn_3, __var___Block_492_42->fi->path->str, ".fs") ) ;
	if (!Orc$Path_exists(__var___Block_492_42->vsPath->str) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
		SuiDialog$Toast_make(Orc$String$addString(Orc$str(&tmpReturn_4, ".vs文件不存在:") , __var___Block_492_42->vsPath) ->str) ;
		return ; 
	}
	if (!Orc$Path_exists(__var___Block_492_42->fsPath->str) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		SuiDialog$Toast_make(Orc$String$addString(Orc$str(&tmpReturn_5, ".fs文件不存在:") , __var___Block_492_42->fsPath) ->str) ;
		return ; 
	}
	URGC_VAR_CLEANUP SuiDesigner$__Closure_509_51*  tmpReturn_6 = NULL;
	SuiDialog$MessageDialog_prompt("新建材质.matl.json", "新建预制", __make___Closure_509_51(&tmpReturn_6, __var___Block_492_42) ) ;
}

static void  __finiBlock___Block_48_44(SuiDesigner$__Block_48_44 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_48_44, parent) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_82_42(SuiDesigner$__Block_82_42 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_82_42, fi) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_95_47(SuiDesigner$__Block_95_47 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_95_47, parent) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_263_39(SuiDesigner$__Block_263_39 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_263_39, anode) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_492_42(SuiDesigner$__Block_492_42 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_492_42, fi) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_492_42, vsPath) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_492_42, fsPath) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_492_42, basename) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_61_53(SuiDesigner$__Closure_61_53 *  self, Orc$String*  newName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newName);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  path = (path=NULL,urgc_init_var_class((void**)&path, Orc$String$addString(Orc$String$add(Orc$String$clone(&tmpReturn_1, self->__var___Block_48_44->parent->path) , "/") , newName) ));
	URGC_VAR_CLEANUP_CLASS SuiDesigner$Prefab*  prefab = (prefab=NULL,urgc_init_var_class((void**)&prefab, SuiDesigner$Prefab_new(&prefab) ));
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  tmpReturn_2 = NULL;
	urgc_set_field_class(prefab, (void * )offsetof(SuiDesigner$Prefab, root) , SuiDesigner$mkANodeByTag(&tmpReturn_2, Vtable_getClassName(Vtable_SuiLayout$LayoutLinear_init(NULL)) ) ) ;
	Json$Json *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_3 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = (tmpThis_1 = prefab->toJson(&tmpReturn_3, prefab) )->dump((text = NULL,&text), tmpThis_1) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	SuiDialog$MessageDialog_alert(Orc$String$add(Orc$str(&tmpReturn_4, "新建预制. 路径") , path->str) ->str, "tip") ;
	if (Orc$Path_writeText(path->str, text->str) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		SuiDialog$MessageDialog_alert(Orc$String$add(Orc$str(&tmpReturn_5, "新建预制成功. 路径") , path->str) , "tip") ;
		self->__var___Block_48_44->parent->loadSubtree(self->__var___Block_48_44->parent) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_6 = NULL;
		{
			SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_6) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , self->__var___Block_48_44->parent) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}

static void  __fini___Closure_61_53(SuiDesigner$__Closure_61_53 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_61_53, __var___Block_48_44) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_61_53*  __make___Closure_61_53(SuiDesigner$__Closure_61_53 **  __outRef__, SuiDesigner$__Block_48_44 *  __var___Block_48_44){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_61_53*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_61_53) , __fini___Closure_61_53) ));
	self->invoke = __fn___Closure_61_53;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_61_53, __var___Block_48_44) , __var___Block_48_44) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_83_49(SuiDesigner$__Closure_83_49 *  self, Orc$String*  newName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newName);

	URGC_VAR_CLEANUP_CLASS Orc$String*  newpath = Orc$Path_withBasename((newpath = NULL,&newpath), self->__var___Block_82_42->fi->path->str, newName->str) ;
	Orc$Path_rename(self->__var___Block_82_42->fi->path->str, newpath->str) ;
	urgc_set_field_class(self->__var___Block_82_42->fi, (void * )offsetof(SuiDesigner$FileItem, filename) , newName) ;
	self->__var___Block_82_42->fi->updatePathByParnetPathAndSelfFilename_subtree(self->__var___Block_82_42->fi) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , self->__var___Block_82_42->fi) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

static void  __fini___Closure_83_49(SuiDesigner$__Closure_83_49 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_83_49, __var___Block_82_42) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_83_49*  __make___Closure_83_49(SuiDesigner$__Closure_83_49 **  __outRef__, SuiDesigner$__Block_82_42 *  __var___Block_82_42){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_83_49*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_83_49) , __fini___Closure_83_49) ));
	self->invoke = __fn___Closure_83_49;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_83_49, __var___Block_82_42) , __var___Block_82_42) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_112_42(SuiDesigner$__Closure_112_42 *  self, Orc$String*  newName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newName);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  fi = (fi=NULL,urgc_init_var_class((void**)&fi, SuiDesigner$FileItem_new(&fi) ));
	fi->setPathByParentPathAndFilename(fi, self->__var___Block_95_47->parent->path, newName) ;
	if (Orc$Path_mkdirs(fi->path->str) ) {
		fi->setPath(fi, fi->path) ;
		self->__var___Block_95_47->parent->appendChild(self->__var___Block_95_47->parent, fi) ;
		SuiDesigner$FileItem *  tmpThis_1 = NULL;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$Project*  tmpReturn_1 = NULL;
		(tmpThis_1 = SuiDesigner$Project_ins(&tmpReturn_1) ->dirFileItem)->printTree(tmpThis_1, 0) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_2 = NULL;
		{
			SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_2) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , fi) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}

static void  __fini___Closure_112_42(SuiDesigner$__Closure_112_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_112_42, __var___Block_95_47) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_112_42*  __make___Closure_112_42(SuiDesigner$__Closure_112_42 **  __outRef__, SuiDesigner$__Block_95_47 *  __var___Block_95_47){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_112_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_112_42) , __fini___Closure_112_42) ));
	self->invoke = __fn___Closure_112_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_112_42, __var___Block_95_47) , __var___Block_95_47) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_266_42(SuiDesigner$__Closure_266_42 *  self, Orc$String*  newName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newName);

	URGC_VAR_CLEANUP_CLASS Json$Json*  strJo = Json$Json_mkString((strJo = NULL,&strJo), newName) ;
	self->__var___Block_263_39->anode->setAttr(self->__var___Block_263_39->anode, "name", strJo) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeAttrChanged*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$EventANodeAttrChanged*  o = SuiDesigner$EventANodeAttrChanged_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeAttrChanged, anode) , self->__var___Block_263_39->anode) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

static void  __fini___Closure_266_42(SuiDesigner$__Closure_266_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_266_42, __var___Block_263_39) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_266_42*  __make___Closure_266_42(SuiDesigner$__Closure_266_42 **  __outRef__, SuiDesigner$__Block_263_39 *  __var___Block_263_39){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_266_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_266_42) , __fini___Closure_266_42) ));
	self->invoke = __fn___Closure_266_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_266_42, __var___Block_263_39) , __var___Block_263_39) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_509_51(SuiDesigner$__Closure_509_51 *  self, Orc$String*  newName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(newName);

	URGC_VAR_CLEANUP_CLASS Orc$String*  matlPath = Orc$Path_withBasename((matlPath = NULL,&matlPath), self->__var___Block_492_42->fi->path->str, newName->str) ;
	if (Orc$Path_exists(matlPath->str) ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		SuiDialog$Toast_make(Orc$String$addString(Orc$str(&tmpReturn_1, "材质已存在") , matlPath) ->str) ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
	matl->buildByShaderPathCstr(matl, self->__var___Block_492_42->vsPath->str, self->__var___Block_492_42->fsPath->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(matl, (void * )offsetof(Sgl$Material, vsPath) , Orc$Path_withExt(&tmpReturn_2, self->__var___Block_492_42->basename->str, ".vs") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(matl, (void * )offsetof(Sgl$Material, fsPath) , Orc$Path_withExt(&tmpReturn_3, self->__var___Block_492_42->basename->str, ".fs") ) ;
	matl->saveTo(matl, matlPath) ;
	SuiDialog$Toast_make("材质创建成功") ;
	if (self->__var___Block_492_42->fi->parent) {
		self->__var___Block_492_42->fi->parent->loadSubtree(self->__var___Block_492_42->fi->parent) ;
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$EventFileItemChanged*  tmpNewOwner_4 = NULL;
	{
		SuiDesigner$EventFileItemChanged*  o = SuiDesigner$EventFileItemChanged_new(&tmpNewOwner_4) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventFileItemChanged, fileItem) , self->__var___Block_492_42->fi->parent) ;
		((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
	}
}

static void  __fini___Closure_509_51(SuiDesigner$__Closure_509_51 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_509_51, __var___Block_492_42) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_509_51*  __make___Closure_509_51(SuiDesigner$__Closure_509_51 **  __outRef__, SuiDesigner$__Block_492_42 *  __var___Block_492_42){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_509_51*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_509_51) , __fini___Closure_509_51) ));
	self->invoke = __fn___Closure_509_51;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_509_51, __var___Block_492_42) , __var___Block_492_42) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

void  SuiDesigner$UiAction_showMaterialInspectorWindow(SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
	matl->load(matl, fi->path->str) ;
	URGC_VAR_CLEANUP_CLASS Sgl$MaterialInsp*  tmpNewOwner_1 = NULL;
	{
		Sgl$MaterialInsp*  o = Sgl$MaterialInsp_new(&tmpNewOwner_1) ;
		
	
		o->showWindow(o, matl) ;
	}
}

void  SuiDesigner$UiAction_previewCamera(Sgl$DrawCtx *  ctx, SuiCore$Node *  camera){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS Sgl$SglSceneView*  tmpNewOwner_2 = NULL;
		{
			Sgl$SglSceneView*  o = Sgl$SglSceneView_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_560_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			win->setRootView(win, o) ;
			urgc_set_field(o, (void * )offsetof(Sgl$SglSceneView, scene) , ctx->scene) ;
			urgc_set_field(o, (void * )offsetof(Sgl$SglSceneView, camera) , camera) ;
			o->buildDrawObj(o) ;
		}
		o->setTitle(o, "纹理预览") ;
		o->setSize(o, 640, 480) ;
		o->show(o) ;
	}
}



