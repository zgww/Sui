
#include "MainProject_orc.h" 

#include <stdio.h>
#include "./Orc/Orc.h"
#include "../UrgcDll/urgc_api.h"
#include "./Sui/View/Button_orc.h"
#include "./Sui/Core/Image_orc.h"
#include "./Sui/View/ImageView_orc.h"
#include "./Sui/View/TextView_orc.h"
#include "./Sui/View/ScrollArea_orc.h"
#include "./Sui/View/ViewBuilder_orc.h"
#include "./Sui/Core/App_orc.h"
#include "./Sui/Core/Timer_orc.h"
#include "./Sui/Core/Window_orc.h"
#include "./Orc/Time_orc.h"
#include "./Orc/String_orc.h"
#include "./Orc/Path_orc.h"
#include "./Orc/List_orc.h"
#include "./Orc/Map_orc.h"
#include "./Orc/Math_orc.h"
#include "./Sui/Core/Node_orc.h"
#include "./Sui/Core/Emitter_orc.h"
#include "./Sui/Core/Event_orc.h"
#include "./Sui/Core/ViewBase_orc.h"
#include "./Sui/Core/Mouse_orc.h"
#include "./Sui/Core/MouseEvent_orc.h"
#include "./Sui/Core/View_orc.h"
#include "./Sui/Core/Rect_orc.h"
#include "./Sui/Core/Vec2_orc.h"
#include "./Sui/Core/Inset_orc.h"
#include "./Sui/Core/Frame_orc.h"
#include "./Sui/Dialog/MessageDialog_orc.h"
#include "./Sui/Dialog/FileDialog_orc.h"
#include "./Sui/Layout/LayoutLinear_orc.h"
#include "./Sui/Layout/LayoutAlign_orc.h"
#include "./Sui/View/Checkbox_orc.h"
#include "./Sui/View/Switch_orc.h"
#include "./Sui/View/Slider_orc.h"
#include "./Sui/View/ProgressView_orc.h"
#include "./Sui/View/EditText_orc.h"
#include "./Sui/View/TableView_orc.h"
#include "./Sui/View/HoverViewEffect_orc.h"
#include "./Sui/View/ScrollArea_orc.h"
#include "./Sui/View/ColorPalete_orc.h"
#include "./Sui/View/TreeView_orc.h"
#include "./Sui/View/MenuNative_orc.h"
#include "./Sui/View/Select_orc.h"
#include "./Sui/View/DockLayout_orc.h"
#include "./Sui/View/SystemTrayIcon_orc.h"
#include "./SuiDesigner/Asset/FileWatcher_orc.h"
#include "./SuiDesigner/Asset/AssetDirView_orc.h"
#include "./SuiDesigner/Asset/AssetDirTreeView_orc.h"
#include "./SuiDesigner/Serial/BiJson_orc.h"
#include "./SuiDesigner/SceneView_orc.h"
#include "./SuiDesigner/SceneHierView_orc.h"
#include "./SuiDesigner/Inspector_orc.h"
#include "./SuiDesigner/InspectorView_orc.h"
#include "./SuiDesigner/Theme_orc.h"
#include "./SuiDesigner/BezierEditView_orc.h"
#include "./Json/Json_orc.h"
#include "./SuiDesigner/ProjectMgr_orc.h"
#include "./SuiDesignerMain_orc.h"


// static struct 
typedef struct tag__Block_86_49 __Block_86_49;

typedef struct tag__Block_106_71 __Block_106_71;

typedef struct tag__Block_234_49 __Block_234_49;

typedef struct tag__Closure_cb_87 __Closure_cb_87;

typedef struct tag__Closure_123_22 __Closure_123_22;

typedef struct tag__Closure_240_36 __Closure_240_36;

typedef struct tag__Closure_244_31 __Closure_244_31;

typedef struct tag__Closure_330_28 __Closure_330_28;



struct tag__Block_86_49 {
	SuiDesigner$ProjectInfo*  project ;
};





struct tag__Block_106_71 {
	SuiDesigner$ProjectInfo*  project ;
};





struct tag__Block_234_49 {
	Orc$String*  btn ;
};





struct tag__Closure_cb_87 {
	void  (*invoke)(__Closure_cb_87 *  self, SuiView$MenuNativeItem *  item);
	Vtable_Object *  vtable ;
	__Block_86_49*  __var___Block_86_49 ;
};





struct tag__Closure_123_22 {
	void  (*invoke)(__Closure_123_22 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	__Block_106_71*  __var___Block_106_71 ;
};





struct tag__Closure_240_36 {
	void  (*invoke)(__Closure_240_36 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





struct tag__Closure_244_31 {
	void  (*invoke)(__Closure_244_31 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
	__Block_234_49*  __var___Block_234_49 ;
};





struct tag__Closure_330_28 {
	void  (*invoke)(__Closure_330_28 *  self, SuiCore$MouseEvent *  me);
	Vtable_Object *  vtable ;
};





// static function declaration
static void  openProject(SuiDesigner$ProjectInfo*  project);
static void  showProjectMenu(SuiDesigner$ProjectInfo*  project);
static void  renderProjectItemView(SuiCore$Node *  o, SuiDesigner$ProjectInfo*  project, int  i);
static void  load();
static void  save();
static void  renderWindow();
static void  __finiBlock___Block_86_49(__Block_86_49 *  self);
static void  __finiBlock___Block_106_71(__Block_106_71 *  self);
static void  __finiBlock___Block_234_49(__Block_234_49 *  self);
static void  __fn___Closure_cb_87(__Closure_cb_87 *  self, SuiView$MenuNativeItem *  item);
static void  __fini___Closure_cb_87(__Closure_cb_87 *  self);
static __Closure_cb_87*  __make___Closure_cb_87(__Closure_cb_87 **  __outRef__, __Block_86_49 *  __var___Block_86_49);
static void  __fn___Closure_123_22(__Closure_123_22 *  self, SuiCore$Event *  e);
static void  __fini___Closure_123_22(__Closure_123_22 *  self);
static __Closure_123_22*  __make___Closure_123_22(__Closure_123_22 **  __outRef__, __Block_106_71 *  __var___Block_106_71);
static void  __fn___Closure_240_36(__Closure_240_36 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_240_36(__Closure_240_36 *  self);
static __Closure_240_36*  __make___Closure_240_36(__Closure_240_36 **  __outRef__);
static void  __fn___Closure_244_31(__Closure_244_31 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_244_31(__Closure_244_31 *  self);
static __Closure_244_31*  __make___Closure_244_31(__Closure_244_31 **  __outRef__, __Block_234_49 *  __var___Block_234_49);
static void  __fn___Closure_330_28(__Closure_330_28 *  self, SuiCore$MouseEvent *  me);
static void  __fini___Closure_330_28(__Closure_330_28 *  self);
static __Closure_330_28*  __make___Closure_330_28(__Closure_330_28 **  __outRef__);


static URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectMgr*  mgr = NULL;
static URGC_VAR_CLEANUP_CLASS Sui$Window*  win = NULL;
static URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectInfo*  curProject = NULL;
static void  openProject(SuiDesigner$ProjectInfo*  project){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(project);

	if (!win) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmp = (tmp=NULL,urgc_init_var_class((void**)&tmp, win));
	urgc_set_var_class(&win, NULL) ;
	startSuiDesigner() ;
	tmp->close(tmp) ;
	urgc_set_var_class(&tmp, NULL) ;
}

static void  showProjectMenu(SuiDesigner$ProjectInfo*  project){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(project);

	URGC_VAR_CLEANUP __Block_86_49*  __var___Block_86_49 = (__var___Block_86_49=NULL,urgc_init_var((void**)&__var___Block_86_49, orc_alloc_and_set_deleter(sizeof(__Block_86_49) , __finiBlock___Block_86_49) ));
	urgc_set_field_class(__var___Block_86_49, (void * )offsetof(__Block_86_49, project) , project) ;
	URGC_VAR_CLEANUP void  (**cb)(void *  self, SuiView$MenuNativeItem *  item) = NULL;
	URGC_VAR_CLEANUP __Closure_cb_87*  tmpReturn_1 = NULL;
	(urgc_set_var(&cb, __make___Closure_cb_87(&tmpReturn_1, __var___Block_86_49) ) );
	URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_2 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	{
		SuiView$MenuNativeItem*  o = SuiView$mkMenuNativeItem(&tmpReturn_2, NULL, Orc$str(&tmpReturn_3, "") , cb) ;
		
	
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_4 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		SuiView$mkMenuNativeItem(&tmpReturn_4, o, Orc$str(&tmpReturn_5, "Delete") , cb) ;
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNativeItem*  tmpReturn_6 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
		SuiView$mkMenuNativeItem(&tmpReturn_6, o, Orc$str(&tmpReturn_7, "打开") , cb) ;
		URGC_VAR_CLEANUP_CLASS SuiView$MenuNative*  menu = (menu=NULL,urgc_init_var_class((void**)&menu, SuiView$MenuNative_new(&menu) ));
		menu->create(menu, o) ;
		menu->showAtMouse(menu) ;
	}
}

static void  renderProjectItemView(SuiCore$Node *  o, SuiDesigner$ProjectInfo*  project, int  i){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(project);

	URGC_VAR_CLEANUP __Block_106_71*  __var___Block_106_71 = (__var___Block_106_71=NULL,urgc_init_var((void**)&__var___Block_106_71, orc_alloc_and_set_deleter(sizeof(__Block_106_71) , __finiBlock___Block_106_71) ));
	urgc_set_field_class(__var___Block_106_71, (void * )offsetof(__Block_106_71, project) , project) ;
	if (0) {
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_1 = NULL;
		{
			SuiView$TextView*  __scopeVar_108_8 = SuiView$mkTextView(&tmpReturn_1, o, 0) , *o = __scopeVar_108_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_108_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			((SuiCore$View * )o)->height = 100;
			((SuiCore$View * )o)->backgroundColor = i % 2 ? 0x110088ff : 0x11000000;
			o->setText(o, __var___Block_106_71->project->path) ;
		}
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
	{
		SuiLayout$LayoutLinear*  __scopeVar_115_4 = SuiLayout$layoutLinear(&tmpReturn_2, o, i) , *o = __scopeVar_115_4;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_115_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		((SuiCore$View * )o)->margin.top = 6;
		((SuiCore$View * )o)->margin.bottom = 6;
		((SuiCore$View * )o)->margin.left = 6;
		((SuiCore$View * )o)->margin.right = 6;
		Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
		URGC_VAR_CLEANUP __Closure_123_22*  tmpReturn_3 = NULL;
		urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_123_22(&tmpReturn_3, __var___Block_106_71) ) ;
		URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_4 = NULL;
		{
			SuiView$HoverViewEffect*  __scopeVar_147_8 = SuiView$mkHoverViewEffect(&tmpReturn_4, o, 0) , *o = __scopeVar_147_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_147_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->border->setAll(o->border, 0.0, 0x11000000) ;
			o->border->b->set(o->border->b, 1.0, 0x11000000) ;
			o->hoverBorder->setAll(o->hoverBorder, 0.0, 0x11000000) ;
			o->hoverBorder->b->set(o->hoverBorder->b, 1.0, 0x11000000) ;
			o->activeBorder->setAll(o->activeBorder, 0.0, 0x11000000) ;
			o->activeBorder->b->set(o->activeBorder->b, 1.0, 0x51ff0000) ;
			o->backgroundColor = i % 2 == 0 ? 0x00000000 : 0x08000000;
			o->activeBackgroundColor = 0x10000000;
			o->isActive = __var___Block_106_71->project == curProject;
		}
		URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_5 = NULL;
		{
			SuiView$ImageView*  __scopeVar_167_8 = SuiView$mkImageView(&tmpReturn_5, o, 0) , *o = __scopeVar_167_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_167_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->setSrc(o, __var___Block_106_71->project->icon) ;
			((SuiCore$View * )o)->width = 64;
			((SuiCore$View * )o)->height = 64;
			((SuiCore$View * )o)->margin.right = 12;
		}
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_6 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_174_8 = SuiLayout$layoutLinear(&tmpReturn_6, o, i) , *o = __scopeVar_174_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_174_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "start") ;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
			{
				SuiView$TextView*  __scopeVar_178_12 = SuiView$mkTextView(&tmpReturn_7, o, 0) , *o = __scopeVar_178_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_178_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  name = __var___Block_106_71->project->getName((name = NULL,&name), __var___Block_106_71->project) ;
				o->setText(o, name) ;
				o->setFont_size(o, 20) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_8 = NULL;
			{
				SuiView$TextView*  __scopeVar_183_12 = SuiView$mkTextView(&tmpReturn_8, o, 0) , *o = __scopeVar_183_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_183_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->setText(o, __var___Block_106_71->project->path) ;
				o->setFont_size(o, 14) ;
				o->setColor(o, 0xff666666) ;
			}
		}
	}
}

static const char *  path = "./projects.json";
static void  load(){
	if (!Orc$Path_isFile(path) ) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  text = Orc$Path_readText((text = NULL,&text), path) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = Json$Json_parse((jo = NULL,&jo), text->str) ;
	mgr->loadByJson(mgr, jo) ;
}

static void  save(){
	if (!mgr) {
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS Json$Json*  jo = mgr->toJson((jo = NULL,&jo), mgr) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	printf("save:%s\n", jo->dump(&tmpReturn_1, jo) ->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	Orc$Path_writeText(path, jo->dump(&tmpReturn_2, jo) ->str) ;
	SuiDialog$MessageDialog_alert("保存成功", "tip") ;
}

static void  renderWindow(){
	if (!win) {
		return ; 
	}
	SuiDesigner$Theme *  t = SuiDesigner$themeIns() ;
	{
		SuiCore$ViewBase*  o = win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_218_4 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		urgc_set_field_class(o, (void * )offsetof(SuiCore$Node, name) , Orc$str(&tmpReturn_1, "rootDiv") ) ;
		if (1) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_2 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_225_8 = SuiLayout$layoutLinear(&tmpReturn_2, o, 0) , *o = __scopeVar_225_8;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_225_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->backgroundColor = t->menubar_bg;
				SuiCore$Inset$setAxis(&((SuiCore$View * )o)->padding, 0, 6) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  btnsStr = Orc$str((btnsStr = NULL,&btnsStr), "+ Add,- Delete,Import,Clear,Save,Load") ;
				URGC_VAR_CLEANUP_CLASS Orc$List*  btns = Orc$String$splitByRe((btns = NULL,&btns), btnsStr, ",") ;
				for (int  i = 0; i < btns->size(btns) ; i++) {
					URGC_VAR_CLEANUP __Block_234_49*  __var___Block_234_49 = (__var___Block_234_49=NULL,urgc_init_var((void**)&__var___Block_234_49, orc_alloc_and_set_deleter(sizeof(__Block_234_49) , __finiBlock___Block_234_49) ));
					urgc_set_field_class(__var___Block_234_49, (void * )offsetof(__Block_234_49, btn) , (Orc$String* )btns->get(btns, i) ) ;
					URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  tmpReturn_3 = NULL;
					{
						SuiView$MenuButton*  __scopeVar_236_16 = SuiView$mkMenuButton(&tmpReturn_3, o, i) , *o = __scopeVar_236_16;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_236_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS SuiView$MenuButton*  mbutton = (mbutton=NULL,urgc_init_var_class((void**)&mbutton, o));
						urgc_set_field_class(o, (void * )offsetof(SuiView$MenuButton, text) , __var___Block_234_49->btn) ;
						URGC_VAR_CLEANUP __Closure_240_36*  tmpReturn_4 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onMouseMove) , __make___Closure_240_36(&tmpReturn_4) ) ;
						URGC_VAR_CLEANUP __Closure_244_31*  tmpReturn_5 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiView$MenuButton, onClick) , __make___Closure_244_31(&tmpReturn_5, __var___Block_234_49) ) ;
					}
				}
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_6 = NULL;
		{
			SuiView$ScrollArea*  __scopeVar_289_8 = SuiView$mkScrollArea(&tmpReturn_6, o, 0) , *o = __scopeVar_289_8;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_289_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(((SuiLayout$LayoutLinear * )o)->alignItems, "stretch") ;
			o->useMinWidthConstraint = true;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_7 = NULL;
			{
				SuiLayout$LayoutLinearCell*  __scopeVar_296_12 = SuiLayout$layoutLinearCell(&tmpReturn_7, o, 0) , *o = __scopeVar_296_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_296_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->grow = 1.0;
				Orc$String$set(o->alignSelf, "stretch") ;
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_8 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_302_12 = SuiLayout$layoutLinear(&tmpReturn_8, o, 0) , *o = __scopeVar_302_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_302_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				Orc$String$set(o->direction, "column") ;
				Orc$String$set(o->alignItems, "stretch") ;
				SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 6) ;
				for (int  i = 0; i < mgr->projects->size(mgr->projects) ; i++) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectInfo*  project = (project=NULL,urgc_init_var_class((void**)&project, (SuiDesigner$ProjectInfo* )mgr->projects->get(mgr->projects, i) ));
					renderProjectItemView(o, project, i) ;
				}
			}
		}
		if (0) {
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_9 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_320_8 = SuiLayout$layoutLinear(&tmpReturn_9, o, 0) , *o = __scopeVar_320_8;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_320_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				Orc$String$set(o->justifyContent, "center") ;
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_10 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_327_12 = SuiView$mkDrawButton(&tmpReturn_10, o, 0) , *o = __scopeVar_327_12;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_327_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_11, "保存") ) ;
					URGC_VAR_CLEANUP __Closure_330_28*  tmpReturn_12 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_330_28(&tmpReturn_12) ) ;
				}
			}
		}
	}
}

static void  __finiBlock___Block_86_49(__Block_86_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_86_49, project) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_106_71(__Block_106_71 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_106_71, project) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_234_49(__Block_234_49 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_234_49, btn) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_cb_87(__Closure_cb_87 *  self, SuiView$MenuNativeItem *  item){
	if (Orc$String$equals(item->label, "Delete") ) {
		mgr->projects->remove(mgr->projects, self->__var___Block_86_49->project) ;
		renderWindow() ;
	}
	if (Orc$String$equals(item->label, "打开") ) {
		openProject(self->__var___Block_86_49->project) ;
	}
}

static void  __fini___Closure_cb_87(__Closure_cb_87 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_cb_87, __var___Block_86_49) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_cb_87*  __make___Closure_cb_87(__Closure_cb_87 **  __outRef__, __Block_86_49 *  __var___Block_86_49){
	URGC_VAR_CLEANUP __Closure_cb_87*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_cb_87) , __fini___Closure_cb_87) ));
	self->invoke = __fn___Closure_cb_87;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_cb_87, __var___Block_86_49) , __var___Block_86_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_123_22(__Closure_123_22 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->isClickInBubble(me) ) {
			if (me->button == 1) {
				urgc_set_var_class(&curProject, self->__var___Block_106_71->project) ;
				renderWindow() ;
			}
			else if (me->button == 3) {
				showProjectMenu(self->__var___Block_106_71->project) ;
			}
		}
		if (me->isDblClickInBubble(me)  && me->button == 1) {
			openProject(self->__var___Block_106_71->project) ;
		}
	}
}

static void  __fini___Closure_123_22(__Closure_123_22 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_123_22, __var___Block_106_71) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_123_22*  __make___Closure_123_22(__Closure_123_22 **  __outRef__, __Block_106_71 *  __var___Block_106_71){
	URGC_VAR_CLEANUP __Closure_123_22*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_123_22) , __fini___Closure_123_22) ));
	self->invoke = __fn___Closure_123_22;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_123_22, __var___Block_106_71) , __var___Block_106_71) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_240_36(__Closure_240_36 *  self, SuiCore$MouseEvent *  me){
	
}

static void  __fini___Closure_240_36(__Closure_240_36 *  self){
	urgc_free_later(self) ;
}

static __Closure_240_36*  __make___Closure_240_36(__Closure_240_36 **  __outRef__){
	URGC_VAR_CLEANUP __Closure_240_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_240_36) , __fini___Closure_240_36) ));
	self->invoke = __fn___Closure_240_36;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_244_31(__Closure_244_31 *  self, SuiCore$MouseEvent *  me){
	if (Orc$String$endsWith(self->__var___Block_234_49->btn, "+ Add") ) {
		mgr->addTestProject(mgr, "./") ;
		renderWindow() ;
	}
	else if (Orc$String$endsWith(self->__var___Block_234_49->btn, "Clear") ) {
		mgr->projects->clear(mgr->projects) ;
		renderWindow() ;
	}
	else if (Orc$String$endsWith(self->__var___Block_234_49->btn, "Save") ) {
		save() ;
	}
	else if (Orc$String$endsWith(self->__var___Block_234_49->btn, "Load") ) {
		load() ;
		renderWindow() ;
		SuiDialog$MessageDialog_alert("加载成功", "tip") ;
	}
	else if (Orc$String$endsWith(self->__var___Block_234_49->btn, "Delete") ) {
		mgr->projects->remove(mgr->projects, curProject) ;
		renderWindow() ;
	}
	else if (Orc$String$endsWith(self->__var___Block_234_49->btn, "Import") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  dirpath = SuiDialog$fileDialog_getExistingDirectory((dirpath = NULL,&dirpath), "./", "选择项目目录") ;
		if (!dirpath) {
			SuiDialog$MessageDialog_alert("未选择", "提示") ;
		}
		else {
			URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectInfo*  p = (p=NULL,urgc_init_var_class((void**)&p, SuiDesigner$ProjectInfo_new(&p) ));
			urgc_set_field_class(p, (void * )offsetof(SuiDesigner$ProjectInfo, path) , dirpath) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_field_class(p, (void * )offsetof(SuiDesigner$ProjectInfo, version) , Orc$str(&tmpReturn_1, "2.303.0") ) ;
			mgr->projects->add(mgr->projects, p) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
			SuiDialog$MessageDialog_alert(Orc$String$addString(Orc$str(&tmpReturn_2, "选择") , dirpath) ->str, "提示") ;
		}
		renderWindow() ;
	}
	else {
		SuiDialog$MessageDialog_alert(self->__var___Block_234_49->btn->str, "提示") ;
	}
}

static void  __fini___Closure_244_31(__Closure_244_31 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_244_31, __var___Block_234_49) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_244_31*  __make___Closure_244_31(__Closure_244_31 **  __outRef__, __Block_234_49 *  __var___Block_234_49){
	URGC_VAR_CLEANUP __Closure_244_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_244_31) , __fini___Closure_244_31) ));
	self->invoke = __fn___Closure_244_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_244_31, __var___Block_234_49) , __var___Block_234_49) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_330_28(__Closure_330_28 *  self, SuiCore$MouseEvent *  me){
	SuiDialog$MessageDialog_alert("保存", "提示") ;
}

static void  __fini___Closure_330_28(__Closure_330_28 *  self){
	urgc_free_later(self) ;
}

static __Closure_330_28*  __make___Closure_330_28(__Closure_330_28 **  __outRef__){
	URGC_VAR_CLEANUP __Closure_330_28*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_330_28) , __fini___Closure_330_28) ));
	self->invoke = __fn___Closure_330_28;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

Sui$Window*  MainProject_showWindow(Sui$Window **  __outRef__){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ProjectMgr*  tmpNewOwner_1 = NULL;
	urgc_set_var_class(&mgr, SuiDesigner$ProjectMgr_new(&tmpNewOwner_1) ) ;
	load() ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_2 = NULL;
	urgc_set_var_class(&win, Sui$Window_new(&tmpNewOwner_2) ) ;
	win->setSize(win, 300, 300) ;
	{
		Sui$Window*  o = win;
		
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_3 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_3) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_388_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "maxOrStretch") ;
			((SuiCore$View * )o)->backgroundColor = 0xffefefef;
			win->setRootView(win, o) ;
		}
		renderWindow() ;
		o->setTitle(o, "项目") ;
		printf("setTitle\n") ;
		o->setRect(o, 100, 100, 800, 400) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, win) ; 
}



