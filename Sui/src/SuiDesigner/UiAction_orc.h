
typedef struct tagSuiDesigner$ClipboardForANodes SuiDesigner$ClipboardForANodes;
typedef struct tagVtable_SuiDesigner$ClipboardForANodes Vtable_SuiDesigner$ClipboardForANodes;


#ifndef define_struct___SuiDesigner__UiAction_orc_h__
#define define_struct___SuiDesigner__UiAction_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__UiAction_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__UiAction_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__UiAction_orc_h__
#define __SuiDesigner__UiAction_orc_h__

//include  importHeadCode
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
#define INCLUDE_ONLY_TYPE
#include "../Sgl/Material_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../Sgl/DrawCtx_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../Sgl/SglSceneView_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../HoroEditor/HoroEditor_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../HoroEditor/HoroGeometryPreviewView_orc.h"
#undef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE
#include "../HoroEditor/HoroEditCtx_orc.h"
#undef INCLUDE_ONLY_TYPE


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
void  SuiDesigner$UiAction_createPrefab(SuiDesigner$FileItem*  parent);
void  SuiDesigner$UiAction_renameFileItem(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_createDirectory(SuiDesigner$FileItem*  parent);
void  SuiDesigner$UiAction_deleteDirectory(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_deleteFile(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_delete(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_deleteANode(SuiDesigner$ANode*  anode);

// 虚表
struct tagVtable_SuiDesigner$ClipboardForANodes {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$ClipboardForANodes _vtable_SuiDesigner$ClipboardForANodes;

// class refc:0
struct tagSuiDesigner$ClipboardForANodes {
	Object super; 
	Orc$List*  list ;
	Orc$String*  kind ;
};
Vtable_SuiDesigner$ClipboardForANodes* Vtable_SuiDesigner$ClipboardForANodes_init(Vtable_SuiDesigner$ClipboardForANodes* pvt);
void SuiDesigner$ClipboardForANodes_init_fields(SuiDesigner$ClipboardForANodes *self);
void SuiDesigner$ClipboardForANodes_init(SuiDesigner$ClipboardForANodes *self, void *pOwner);
SuiDesigner$ClipboardForANodes * SuiDesigner$ClipboardForANodes_new(void *pOwner);
void SuiDesigner$ClipboardForANodes_fini(SuiDesigner$ClipboardForANodes *self);


void  SuiDesigner$UiAction_cutANodes(Orc$List*  anodes);
void  SuiDesigner$UiAction_copyANodes(Orc$List*  anodes);
void  SuiDesigner$UiAction_pasteANodes(SuiDesigner$ANode*  parent);
void  SuiDesigner$UiAction_renameANode(SuiDesigner$ANode*  anode);
void  SuiDesigner$UiAction_locateView(SuiDesigner$ANode*  anode);
void  SuiDesigner$UiAction_addView(SuiDesigner$ANode*  anode, Orc$String*  viewName);
void  SuiDesigner$UiAction_savePrefab();
void  SuiDesigner$UiAction_openFile(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_closeCurrentPrefab();
void  SuiDesigner$UiAction_showImageInNewWindow(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_showFileInfoInNewWindow(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_showFileTextInNewWindow(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_createMaterial(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_showMaterialInspectorWindow(SuiDesigner$FileItem*  fi);
void  SuiDesigner$UiAction_previewCamera(Sgl$DrawCtx *  ctx, SuiCore$Node *  camera);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
