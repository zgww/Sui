
#include "Main_orc.h" 

#include <stdio.h>
#include "../UrgcDll/urgc_api.h"
#include "Orc/Orc.h"
#include "./Sui/Core/App_orc.h"
#include "./Sui/Core/Window_orc.h"
#include "./Sui/Core/View_orc.h"
#include "./Sui/View/ViewBuilder_orc.h"
#include "./Sui/View/ImageView_orc.h"
#include "./Sui/View/TextView_orc.h"
#include "./Sui/View/EditText_orc.h"
#include "./Sui/View/Button_orc.h"
#include "./Sui/Layout/LayoutLinear_orc.h"
#include "./Sui/Layout/LayoutGrid_orc.h"
#include "./Sui/Layout/RowWrap_orc.h"
#include "./Sui/Layout/LayoutAlign_orc.h"
#include "./Sui/Dialog/Toast_orc.h"
#include "./Orc/String_orc.h"


// static struct 
typedef struct tag__Block_55_10 __Block_55_10;

typedef struct tag__Closure_84_36 __Closure_84_36;

typedef struct tag__Closure_86_43 __Closure_86_43;



struct tag__Block_55_10 {
	SuiCore$App*  app ;
};





struct tag__Closure_84_36 {
	void  (*invoke)(__Closure_84_36 *  self);
	Vtable_Object *  vtable ;
	__Block_55_10*  __var___Block_55_10 ;
};





struct tag__Closure_86_43 {
	void  (*invoke)(__Closure_86_43 *  self, Sui$Window *  win);
	Vtable_Object *  vtable ;
};





// static function declaration
static void  __finiBlock___Block_55_10(__Block_55_10 *  self);
static void  __fn___Closure_84_36(__Closure_84_36 *  self);
static void  __fini___Closure_84_36(__Closure_84_36 *  self);
static __Closure_84_36*  __make___Closure_84_36(__Closure_84_36 **  __outRef__, __Block_55_10 *  __var___Block_55_10);
static void  __fn___Closure_86_43(__Closure_86_43 *  self, Sui$Window *  win);
static void  __fini___Closure_86_43(__Closure_86_43 *  self);
static __Closure_86_43*  __make___Closure_86_43(__Closure_86_43 **  __outRef__);


void  initMain(){
	
}

int  main(){
	URGC_VAR_CLEANUP __Block_55_10*  __var___Block_55_10 = (__var___Block_55_10=NULL,urgc_init_var((void**)&__var___Block_55_10, orc_alloc_and_set_deleter(sizeof(__Block_55_10) , __finiBlock___Block_55_10) ));
	if (1) {
		printf("return \n") ;
		return 0; 
	}
	initMain() ;
	windowInit() ;
	printf("app used0\n") ;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  tmpReturn_1 = NULL;
	urgc_set_field_class(__var___Block_55_10, (void * )offsetof(__Block_55_10, app) , SuiCore$App_use(&tmpReturn_1) ) ;
	printf("app used\n") ;
	if (1) {
		URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
		{
			Sui$Window*  o = win;
			
		
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  ll = (ll=NULL,urgc_init_var_class((void**)&ll, SuiLayout$LayoutLinear_new(&ll) ));
			urgc_set_field(win, (void * )offsetof(Sui$Window, rootView) , ll) ;
			{
				SuiLayout$LayoutLinear*  o = ll;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_76_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				((SuiCore$View * )o)->width = 400;
				((SuiCore$View * )o)->height = 400;
				((SuiCore$View * )o)->backgroundColor = 0x93000000;
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_2 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_82_20 = SuiView$mkDrawButton(&tmpReturn_2, o, 0) , *o = __scopeVar_82_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_82_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_3, "submit") ) ;
					URGC_VAR_CLEANUP __Closure_84_36*  tmpReturn_4 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_84_36(&tmpReturn_4, __var___Block_55_10) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_5 = NULL;
				{
					SuiCore$View*  __scopeVar_91_20 = SuiView$mkView(&tmpReturn_5, o, 0) , *o = __scopeVar_91_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_91_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->backgroundColor = 0xffff0000;
					o->width = 100;
					o->height = 100;
					SuiCore$Inset$setAll(&o->margin, 10) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_6 = NULL;
				{
					SuiView$EditText*  __scopeVar_97_20 = SuiView$mkEditText(&tmpReturn_6, o, 0) , *o = __scopeVar_97_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_97_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->color = 0xff000000;
					((SuiCore$View * )o)->height = 40;
					((SuiCore$View * )o)->backgroundColor = 0x99999999;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_7 = NULL;
				{
					SuiView$ImageView*  __scopeVar_104_20 = SuiView$mkImageView(&tmpReturn_7, o, 0) , *o = __scopeVar_104_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_104_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
					o->setSrc(o, Orc$str(&tmpReturn_8, "./asset/SpongeBob.png") ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_9 = NULL;
				{
					SuiView$TextView*  __scopeVar_107_20 = SuiView$mkTextView(&tmpReturn_9, o, 0) , *o = __scopeVar_107_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_107_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					o->setText(o, Orc$str(&tmpReturn_10, "hi there buzi buzi") ) ;
					((SuiCore$View * )o)->backgroundColor = 0x13ff0000;
				}
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_11 = NULL;
				{
					SuiLayout$LayoutLinear*  __scopeVar_113_20 = SuiLayout$layoutLinear(&tmpReturn_11, o, 0) , *o = __scopeVar_113_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_113_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					Orc$String$set(o->direction, "column") ;
					((SuiCore$View * )o)->backgroundColor = 0x33112233;
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_12 = NULL;
					{
						SuiCore$View*  __scopeVar_116_24 = SuiView$mkView(&tmpReturn_12, o, 0) , *o = __scopeVar_116_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_116_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff00ff00;
						o->width = 80;
						o->height = 80;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_13 = NULL;
					{
						SuiCore$View*  __scopeVar_122_24 = SuiView$mkView(&tmpReturn_13, o, 0) , *o = __scopeVar_122_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_122_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 160;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutGrid*  tmpReturn_14 = NULL;
				{
					SuiLayout$LayoutGrid*  __scopeVar_129_20 = SuiLayout$mkLayoutGrid(&tmpReturn_14, o, 0) , *o = __scopeVar_129_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_129_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->width = 200;
					((SuiCore$View * )o)->height = 200;
					((SuiCore$View * )o)->backgroundColor = 0x33330000;
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_15 = NULL;
					{
						SuiCore$View*  __scopeVar_134_24 = SuiView$mkView(&tmpReturn_15, o, 0) , *o = __scopeVar_134_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_134_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_16 = NULL;
					{
						SuiCore$View*  __scopeVar_140_24 = SuiView$mkView(&tmpReturn_16, o, 0) , *o = __scopeVar_140_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_140_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_17 = NULL;
					{
						SuiCore$View*  __scopeVar_146_24 = SuiView$mkView(&tmpReturn_17, o, 0) , *o = __scopeVar_146_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_146_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_18 = NULL;
					{
						SuiCore$View*  __scopeVar_152_24 = SuiView$mkView(&tmpReturn_18, o, 0) , *o = __scopeVar_152_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_152_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiLayout$RowWrap*  tmpReturn_19 = NULL;
				{
					SuiLayout$RowWrap*  __scopeVar_159_20 = SuiLayout$mkRowWrap(&tmpReturn_19, o, 0) , *o = __scopeVar_159_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_159_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->width = 200;
					((SuiCore$View * )o)->height = 200;
					((SuiCore$View * )o)->backgroundColor = 0x33009900;
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_20 = NULL;
					{
						SuiCore$View*  __scopeVar_164_24 = SuiView$mkView(&tmpReturn_20, o, 0) , *o = __scopeVar_164_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_164_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_21 = NULL;
					{
						SuiCore$View*  __scopeVar_170_24 = SuiView$mkView(&tmpReturn_21, o, 0) , *o = __scopeVar_170_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_170_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_22 = NULL;
					{
						SuiCore$View*  __scopeVar_176_24 = SuiView$mkView(&tmpReturn_22, o, 0) , *o = __scopeVar_176_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_176_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_23 = NULL;
					{
						SuiCore$View*  __scopeVar_182_24 = SuiView$mkView(&tmpReturn_23, o, 0) , *o = __scopeVar_182_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_182_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff0000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlign*  tmpReturn_24 = NULL;
				{
					SuiLayout$LayoutAlign*  __scopeVar_189_20 = SuiLayout$layoutAlign(&tmpReturn_24, o, 0) , *o = __scopeVar_189_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_189_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					((SuiCore$View * )o)->width = 200;
					((SuiCore$View * )o)->height = 200;
					((SuiCore$View * )o)->backgroundColor = 0x33009900;
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_25 = NULL;
					{
						SuiCore$View*  __scopeVar_194_24 = SuiView$mkView(&tmpReturn_25, o, 0) , *o = __scopeVar_194_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_194_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xfffff06f;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
						URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignCell*  tmpReturn_26 = NULL;
						{
							SuiLayout$LayoutAlignCell*  __scopeVar_200_28 = SuiLayout$layoutAlignCell(&tmpReturn_26, o, 0) , *o = __scopeVar_200_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_200_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->setBottomRight(o) ;
						}
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_27 = NULL;
					{
						SuiCore$View*  __scopeVar_204_24 = SuiView$mkView(&tmpReturn_27, o, 0) , *o = __scopeVar_204_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_204_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff6000ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
						URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignCell*  tmpReturn_28 = NULL;
						{
							SuiLayout$LayoutAlignCell*  __scopeVar_210_28 = SuiLayout$layoutAlignCell(&tmpReturn_28, o, 0) , *o = __scopeVar_210_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_210_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->setBottomCenter(o) ;
						}
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_29 = NULL;
					{
						SuiCore$View*  __scopeVar_214_24 = SuiView$mkView(&tmpReturn_29, o, 0) , *o = __scopeVar_214_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_214_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff00ffff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
						URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignCell*  tmpReturn_30 = NULL;
						{
							SuiLayout$LayoutAlignCell*  __scopeVar_220_28 = SuiLayout$layoutAlignCell(&tmpReturn_30, o, 0) , *o = __scopeVar_220_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_220_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->setCenter(o) ;
						}
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_31 = NULL;
					{
						SuiCore$View*  __scopeVar_224_24 = SuiView$mkView(&tmpReturn_31, o, 0) , *o = __scopeVar_224_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_224_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xffff00ff;
						o->width = 60;
						o->height = 60;
						SuiCore$Inset$setAll(&o->margin, 10) ;
						URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_32 = NULL;
						{
							SuiLayout$LayoutAlignPositionCell*  __scopeVar_230_28 = SuiLayout$layoutAlignPositionCell(&tmpReturn_32, o, 0) , *o = __scopeVar_230_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_230_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->left = NAN;
							o->right = -60;
							o->top = 3;
						}
					}
					URGC_VAR_CLEANUP_CLASS SuiCore$View*  tmpReturn_33 = NULL;
					{
						SuiCore$View*  __scopeVar_236_24 = SuiView$mkView(&tmpReturn_33, o, 0) , *o = __scopeVar_236_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_236_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->backgroundColor = 0xff6f009f;
						URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutAlignPositionCell*  tmpReturn_34 = NULL;
						{
							SuiLayout$LayoutAlignPositionCell*  __scopeVar_239_28 = SuiLayout$layoutAlignPositionCell(&tmpReturn_34, o, 0) , *o = __scopeVar_239_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_239_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->left = 10;
							o->right = 150;
							o->top = 30;
							o->bottom = 30;
						}
					}
				}
			}
			o->setTitle(o, "orc机器人") ;
			o->setSize(o, 840, 480) ;
			o->setPos(o, 400, 200) ;
			o->show(o) ;
		}
	}
	__var___Block_55_10->app->runEventLoop(__var___Block_55_10->app) ;
	printf("glewINit:%d\n", 1) ;
	getchar() ;
	return 0; 
}

static void  __finiBlock___Block_55_10(__Block_55_10 *  self){
	urgc_set_field_class(self, (void * )offsetof(__Block_55_10, app) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_84_36(__Closure_84_36 *  self){
	URGC_VAR_CLEANUP __Closure_86_43*  tmpReturn_1 = NULL;
	self->__var___Block_55_10->app->eachWindow(self->__var___Block_55_10->app, __make___Closure_86_43(&tmpReturn_1) ) ;
}

static void  __fini___Closure_84_36(__Closure_84_36 *  self){
	urgc_set_field(self, (void * )offsetof(__Closure_84_36, __var___Block_55_10) , NULL) ;
	urgc_free_later(self) ;
}

static __Closure_84_36*  __make___Closure_84_36(__Closure_84_36 **  __outRef__, __Block_55_10 *  __var___Block_55_10){
	URGC_VAR_CLEANUP __Closure_84_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_84_36) , __fini___Closure_84_36) ));
	self->invoke = __fn___Closure_84_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(__Closure_84_36, __var___Block_55_10) , __var___Block_55_10) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_86_43(__Closure_86_43 *  self, Sui$Window *  win){
	win->rootView->printLayoutTimes(win->rootView, 0) ;
}

static void  __fini___Closure_86_43(__Closure_86_43 *  self){
	urgc_free_later(self) ;
}

static __Closure_86_43*  __make___Closure_86_43(__Closure_86_43 **  __outRef__){
	URGC_VAR_CLEANUP __Closure_86_43*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(__Closure_86_43) , __fini___Closure_86_43) ));
	self->invoke = __fn___Closure_86_43;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



