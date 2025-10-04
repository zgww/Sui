
typedef struct tagSuiDesigner$Theme SuiDesigner$Theme;
typedef struct tagVtable_SuiDesigner$Theme Vtable_SuiDesigner$Theme;


#ifndef define_struct___SuiDesigner__Theme_orc_h__
#define define_struct___SuiDesigner__Theme_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__Theme_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__Theme_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__Theme_orc_h__
#define __SuiDesigner__Theme_orc_h__

//include  importHeadCode


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$Theme {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$Theme _vtable_SuiDesigner$Theme;

// class refc:1
struct tagSuiDesigner$Theme {
	Object super; 
	int  colorLabel ;
	int  colorDesc ;
	int  textview_color ;
	int  textview_bg ;
	int  textview_fontSize ;
	int  edittext_color ;
	int  edittext_bg ;
	int  edittext_caretColor ;
	int  edittext_fontSize ;
	int  c_main ;
	int  bg1 ;
	int  bg2 ;
	int  menubar_bg ;
	int  toolbar_bg ;
	int  toolbar_menubutton_bg ;
	int  toolbar_menubutton_bg_hover ;
	int  splitLine_c1 ;
	int  splitLine_c2 ;
	int  fs1 ;
	int  fs2 ;
	int  fs3 ;
	int  fs_h1 ;
	int  fs_h2 ;
	int  dock_head_c ;
	int  dock_headbar_bg ;
	int  dock_head_bg ;
	int  dock_head_bg_active ;
	int  dock_content_bg ;
	int  dock_splitterBg ;
	int  dock_splitterBgHover ;
	int  button_bg ;
	int  button_bgHover ;
	int  button_bgActive ;
	int  button_fontSize ;
	int  button_color ;
	int  button_colorHover ;
	int  button_colorActive ;
	int  button_primary_bg ;
	int  button_primary_bgHover ;
	int  button_primary_color ;
	int  hier_color ;
	int  hier_fontSize ;
	int  dirTree_bg ;
	int  dirTree_color ;
	int  dirTree_fontSize ;
	int  dir_bg ;
	int  dir_color ;
	int  dir_fontSize ;
	int  panel_titleColor ;
	int  panel_titleFontSize ;
	int  insp_color ;
	int  insp_fontSize ;
	int  insp_panelTitleColor ;
	int  scrollbar_bg ;
	int  scrollbar_barBg ;
	int  scrollbar_size ;
};
Vtable_SuiDesigner$Theme* Vtable_SuiDesigner$Theme_init(Vtable_SuiDesigner$Theme* pvt);
void SuiDesigner$Theme_init_fields(SuiDesigner$Theme *self);
void SuiDesigner$Theme_init(SuiDesigner$Theme *self, void *pOwner);
SuiDesigner$Theme * SuiDesigner$Theme_new(void *pOwner);
void SuiDesigner$Theme_fini(SuiDesigner$Theme *self);


SuiDesigner$Theme *  SuiDesigner$themeIns();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
