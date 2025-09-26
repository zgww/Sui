
typedef struct tagSuiDesigner$Project SuiDesigner$Project;
typedef struct tagVtable_SuiDesigner$Project Vtable_SuiDesigner$Project;


#ifndef define_struct___SuiDesigner__Project_orc_h__
#define define_struct___SuiDesigner__Project_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__Project_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__Project_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__Project_orc_h__
#define __SuiDesigner__Project_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Path_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/RowWrap_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "./FileItem_orc.h"
#include "./UiAction_orc.h"
#include "./EditCtx_orc.h"
#include "./EventANodeChanged_orc.h"
#include "./EventFileItemChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$Project {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Project _vtable_SuiDesigner$Project;

// class refc:0
struct tagSuiDesigner$Project {
	Object super; 
	Orc$String*  projectDir ;
	SuiDesigner$FileItem*  dirFileItem ;
	void  (*init) (SuiDesigner$Project *  self, const char *  projectDir);
};
Vtable_SuiDesigner$Project* Vtable_SuiDesigner$Project_init(Vtable_SuiDesigner$Project* pvt);
void SuiDesigner$Project_init_fields(SuiDesigner$Project *self);
void SuiDesigner$Project_init(SuiDesigner$Project *self, void *pOwner);
SuiDesigner$Project * SuiDesigner$Project_new(void *pOwner);
void SuiDesigner$Project_fini(SuiDesigner$Project *self);

void  SuiDesigner$Project$init(SuiDesigner$Project *  self, const char *  projectDir);

SuiDesigner$Project*  SuiDesigner$Project_ins(SuiDesigner$Project **  __outRef__);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
