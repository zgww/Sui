
typedef struct tagSuiDesigner$InvalidReact SuiDesigner$InvalidReact;
typedef struct tagVtable_SuiDesigner$InvalidReact Vtable_SuiDesigner$InvalidReact;


#ifndef define_struct___SuiDesigner__InvalidReact_orc_h__
#define define_struct___SuiDesigner__InvalidReact_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__InvalidReact_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include "../Orc/Orc.h"
#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__InvalidReact_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__InvalidReact_orc_h__
#define __SuiDesigner__InvalidReact_orc_h__

//include  importHeadCode
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/View/DockLayout_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "./ChessBgViewCallback_orc.h"
#include "./Theme_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$InvalidReact {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$InvalidReact _vtable_SuiDesigner$InvalidReact;

// class refc:0
struct tagSuiDesigner$InvalidReact {
	Object super; 
	bool  _reactDirty ;
	void  (**react)(void *  self);
	Object*  target ;
	Orc$String*  reactName ;
	SuiDesigner$InvalidReact *  (*setReactName) (SuiDesigner$InvalidReact *  self, const char *  name);
	void  (*invalid) (SuiDesigner$InvalidReact *  self);
};
Vtable_SuiDesigner$InvalidReact* Vtable_SuiDesigner$InvalidReact_init(Vtable_SuiDesigner$InvalidReact* pvt);
void SuiDesigner$InvalidReact_init_fields(SuiDesigner$InvalidReact *self);
void SuiDesigner$InvalidReact_init(SuiDesigner$InvalidReact *self, void *pOwner);
SuiDesigner$InvalidReact * SuiDesigner$InvalidReact_new(void *pOwner);
void SuiDesigner$InvalidReact_fini(SuiDesigner$InvalidReact *self);

SuiDesigner$InvalidReact *  SuiDesigner$InvalidReact$setReactName(SuiDesigner$InvalidReact *  self, const char *  name);
void  SuiDesigner$InvalidReact$invalid(SuiDesigner$InvalidReact *  self);

SuiDesigner$InvalidReact*  SuiDesigner$mkInvalidReact(SuiDesigner$InvalidReact **  __outRef__, Object*  target);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
