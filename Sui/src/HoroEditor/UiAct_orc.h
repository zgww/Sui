


#ifndef define_struct___HoroEditor__UiAct_orc_h__
#define define_struct___HoroEditor__UiAct_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___HoroEditor__UiAct_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___HoroEditor__UiAct_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __HoroEditor__UiAct_orc_h__
#define __HoroEditor__UiAct_orc_h__

//include  importHeadCode
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


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
void  HoroEditor$UiAct_createPrefab3d(SuiDesigner$FileItem*  parent);
void  HoroEditor$UiAct_savePrefab(HoroEditor$HoroEditor *  editor);
void  HoroEditor$UiAct_addView(HoroEditor$HoroEditor *  editor, SuiDesigner$ANode*  anode, Orc$String*  viewName);
void  HoroEditor$UiAct_createGeometry(SuiDesigner$FileItem*  parent, Orc$String*  cmd);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
