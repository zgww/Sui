
typedef struct tagSuiDesigner$FileChooser SuiDesigner$FileChooser;
typedef struct tagVtable_SuiDesigner$FileChooser Vtable_SuiDesigner$FileChooser;


#ifndef define_struct___SuiDesigner__FileChooser_orc_h__
#define define_struct___SuiDesigner__FileChooser_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__FileChooser_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__FileChooser_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__FileChooser_orc_h__
#define __SuiDesigner__FileChooser_orc_h__

//include  importHeadCode
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/Core/Focus_orc.h"
#include "../Sui/Core/App_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/RowWrap_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$FileChooser {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$FileChooser _vtable_SuiDesigner$FileChooser;

// class refc:0
struct tagSuiDesigner$FileChooser {
	Object super; 
	Orc$List*  paths ;
	bool  (**cbFilter)(void *  self, Orc$String *  path);
	void  (**onChoose)(void *  self, Orc$String*  path);
	Orc$String*  dir ;
	Orc$String*  search ;
	void  (*fire_onChoose) (SuiDesigner$FileChooser *  self, Orc$String*  path);
	void  (*use_filterImage) (SuiDesigner$FileChooser *  self);
	void  (*loadPaths) (SuiDesigner$FileChooser *  self);
	Sui$Window*  win ;
	void  (*doSearch) (SuiDesigner$FileChooser *  self);
	bool  (*matchSearch) (SuiDesigner$FileChooser *  self, Orc$String *  path);
	void  (*react) (SuiDesigner$FileChooser *  self);
	void  (*showWindow) (SuiDesigner$FileChooser *  self);
};
Vtable_SuiDesigner$FileChooser* Vtable_SuiDesigner$FileChooser_init(Vtable_SuiDesigner$FileChooser* pvt);
void SuiDesigner$FileChooser_init_fields(SuiDesigner$FileChooser *self);
void SuiDesigner$FileChooser_init(SuiDesigner$FileChooser *self, void *pOwner);
SuiDesigner$FileChooser * SuiDesigner$FileChooser_new(void *pOwner);
void SuiDesigner$FileChooser_fini(SuiDesigner$FileChooser *self);

void  SuiDesigner$FileChooser$fire_onChoose(SuiDesigner$FileChooser *  self, Orc$String*  path);
void  SuiDesigner$FileChooser$use_filterImage(SuiDesigner$FileChooser *  self);
void  SuiDesigner$FileChooser$loadPaths(SuiDesigner$FileChooser *  self);
void  SuiDesigner$FileChooser$doSearch(SuiDesigner$FileChooser *  self);
bool  SuiDesigner$FileChooser$matchSearch(SuiDesigner$FileChooser *  self, Orc$String *  path);
void  SuiDesigner$FileChooser$react(SuiDesigner$FileChooser *  self);
void  SuiDesigner$FileChooser$showWindow(SuiDesigner$FileChooser *  self);




#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
