
#include "MessageDialog_orc.h" 

#include <stdio.h>
#include "../../Orc/String_orc.h"
#include "../Core/Window_orc.h"
#include "../Core/App_orc.h"
#include "../View/EditText_orc.h"
#include "../Layout/LayoutLinear_orc.h"
#include "../View/Button_orc.h"


// static struct 
typedef struct tagSuiDialog$__Block_20_100 SuiDialog$__Block_20_100;

typedef struct tagSuiDialog$__Block_34_22 SuiDialog$__Block_34_22;

typedef struct tagSuiDialog$__Closure_45_32 SuiDialog$__Closure_45_32;

typedef struct tagSuiDialog$__Closure_57_32 SuiDialog$__Closure_57_32;

typedef struct tagSuiDialog$__Closure_77_45 SuiDialog$__Closure_77_45;



struct tagSuiDialog$__Block_20_100 {
	void  (**onNewValue)(void *  self, Orc$String*  newValue);
	Sui$Window*  win ;
};





struct tagSuiDialog$__Block_34_22 {
	SuiView$EditText*  editText ;
};





struct tagSuiDialog$__Closure_45_32 {
	void  (*invoke)(SuiDialog$__Closure_45_32 *  self);
	Vtable_Object *  vtable ;
	SuiDialog$__Block_20_100*  __var___Block_20_100 ;
	SuiDialog$__Block_34_22*  __var___Block_34_22 ;
};





struct tagSuiDialog$__Closure_57_32 {
	void  (*invoke)(SuiDialog$__Closure_57_32 *  self);
	Vtable_Object *  vtable ;
	SuiDialog$__Block_20_100*  __var___Block_20_100 ;
};





struct tagSuiDialog$__Closure_77_45 {
	void  (*invoke)(SuiDialog$__Closure_77_45 *  self, Orc$String*  nv);
	Vtable_Object *  vtable ;
};





// static function declaration
static void  __finiBlock___Block_20_100(SuiDialog$__Block_20_100 *  self);
static void  __finiBlock___Block_34_22(SuiDialog$__Block_34_22 *  self);
static void  __fn___Closure_45_32(SuiDialog$__Closure_45_32 *  self);
static void  __fini___Closure_45_32(SuiDialog$__Closure_45_32 *  self);
static SuiDialog$__Closure_45_32*  __make___Closure_45_32(SuiDialog$__Closure_45_32 **  __outRef__, SuiDialog$__Block_20_100 *  __var___Block_20_100, SuiDialog$__Block_34_22 *  __var___Block_34_22);
static void  __fn___Closure_57_32(SuiDialog$__Closure_57_32 *  self);
static void  __fini___Closure_57_32(SuiDialog$__Closure_57_32 *  self);
static SuiDialog$__Closure_57_32*  __make___Closure_57_32(SuiDialog$__Closure_57_32 **  __outRef__, SuiDialog$__Block_20_100 *  __var___Block_20_100);
static void  __fn___Closure_77_45(SuiDialog$__Closure_77_45 *  self, Orc$String*  nv);
static void  __fini___Closure_77_45(SuiDialog$__Closure_77_45 *  self);
static SuiDialog$__Closure_77_45*  __make___Closure_77_45(SuiDialog$__Closure_77_45 **  __outRef__);


void  SuiDialog$MessageDialog_prompt(const char *  value, const char *  title, void  (**onNewValue)(void *  self, Orc$String*  newValue)){
	URGC_REF_ARG_WITH_CLEANUP(onNewValue);

	URGC_VAR_CLEANUP SuiDialog$__Block_20_100*  __var___Block_20_100 = (__var___Block_20_100=NULL,urgc_init_var((void**)&__var___Block_20_100, orc_alloc_and_set_deleter(sizeof(SuiDialog$__Block_20_100) , __finiBlock___Block_20_100) ));
	urgc_set_field(__var___Block_20_100, (void * )offsetof(SuiDialog$__Block_20_100, onNewValue) , onNewValue) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(__var___Block_20_100, (void * )offsetof(SuiDialog$__Block_20_100, win) , Sui$Window_new(&tmpNewOwner_1) ) ;
	{
		Sui$Window*  o = __var___Block_20_100->win;
		
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_23_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			Orc$String$set(o->justifyContent, "center") ;
			SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 8) ;
			((SuiCore$View * )o)->backgroundColor = 0xffffffff;
			__var___Block_20_100->win->setRootView(__var___Block_20_100->win, o) ;
		}
		{
			SuiCore$ViewBase*  o = __var___Block_20_100->win->rootView;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_34_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP SuiDialog$__Block_34_22*  __var___Block_34_22 = (__var___Block_34_22=NULL,urgc_init_var((void**)&__var___Block_34_22, orc_alloc_and_set_deleter(sizeof(SuiDialog$__Block_34_22) , __finiBlock___Block_34_22) ));
			urgc_set_field_class(__var___Block_34_22, (void * )offsetof(SuiDialog$__Block_34_22, editText) , NULL) ;
			URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_3 = NULL;
			{
				SuiView$EditText*  __scopeVar_36_12 = SuiView$mkEditText(&tmpReturn_3, o, 0) , *o = __scopeVar_36_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_36_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				urgc_set_field_class(__var___Block_34_22, (void * )offsetof(SuiDialog$__Block_34_22, editText) , o) ;
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
				o->setValue(o, Orc$str(&tmpReturn_4, value) ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_5 = NULL;
			{
				SuiLayout$LayoutLinear*  __scopeVar_40_12 = SuiLayout$layoutLinear(&tmpReturn_5, o, 0) , *o = __scopeVar_40_12;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_40_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				Orc$String$set(o->justifyContent, "center") ;
				SuiCore$Inset$setVer(&((SuiCore$View * )o)->margin, 16) ;
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_6 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_43_16 = SuiView$mkDrawButton(&tmpReturn_6, o, 0) , *o = __scopeVar_43_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_43_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_7, "确认") ) ;
					URGC_VAR_CLEANUP SuiDialog$__Closure_45_32*  tmpReturn_8 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_45_32(&tmpReturn_8, __var___Block_20_100, __var___Block_34_22) ) ;
				}
				URGC_VAR_CLEANUP_CLASS SuiView$DrawButton*  tmpReturn_9 = NULL;
				{
					SuiView$DrawButton*  __scopeVar_55_16 = SuiView$mkDrawButton(&tmpReturn_9, o, 0) , *o = __scopeVar_55_16;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_55_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
					urgc_set_field_class(o, (void * )offsetof(SuiView$DrawButton, text) , Orc$str(&tmpReturn_10, "取消") ) ;
					URGC_VAR_CLEANUP SuiDialog$__Closure_57_32*  tmpReturn_11 = NULL;
					urgc_set_field(o, (void * )offsetof(SuiView$DrawButton, onClick) , __make___Closure_57_32(&tmpReturn_11, __var___Block_20_100) ) ;
				}
			}
		}
		o->setTitle(o, title) ;
		o->setSize(o, 300, 140) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}

void  SuiDialog$testMessageDialog(){
	URGC_VAR_CLEANUP SuiDialog$__Closure_77_45*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_prompt("苍天已死，黄天当立", "请输入", __make___Closure_77_45(&tmpReturn_1) ) ;
	SuiCore$App *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  tmpReturn_2 = NULL;
	(tmpThis_1 = SuiCore$App_use(&tmpReturn_2) )->runEventLoop(tmpThis_1) ;
}

static void  __finiBlock___Block_20_100(SuiDialog$__Block_20_100 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDialog$__Block_20_100, win) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_34_22(SuiDialog$__Block_34_22 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDialog$__Block_34_22, editText) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_45_32(SuiDialog$__Closure_45_32 *  self){
	if (self->__var___Block_20_100->onNewValue) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  nv = (nv=NULL,urgc_init_var_class((void**)&nv, self->__var___Block_34_22->editText->getValue(self->__var___Block_34_22->editText) ));
		(*(self->__var___Block_20_100->onNewValue))((void * )(self->__var___Block_20_100->onNewValue), self->__var___Block_34_22->editText->getValue(self->__var___Block_34_22->editText) ) ;
		self->__var___Block_20_100->win->close(self->__var___Block_20_100->win) ;
	}
}

static void  __fini___Closure_45_32(SuiDialog$__Closure_45_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDialog$__Closure_45_32, __var___Block_20_100) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDialog$__Closure_45_32, __var___Block_34_22) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDialog$__Closure_45_32*  __make___Closure_45_32(SuiDialog$__Closure_45_32 **  __outRef__, SuiDialog$__Block_20_100 *  __var___Block_20_100, SuiDialog$__Block_34_22 *  __var___Block_34_22){
	URGC_VAR_CLEANUP SuiDialog$__Closure_45_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDialog$__Closure_45_32) , __fini___Closure_45_32) ));
	self->invoke = __fn___Closure_45_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDialog$__Closure_45_32, __var___Block_20_100) , __var___Block_20_100) ;
	urgc_set_field(self, (void * )offsetof(SuiDialog$__Closure_45_32, __var___Block_34_22) , __var___Block_34_22) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_57_32(SuiDialog$__Closure_57_32 *  self){
	self->__var___Block_20_100->win->close(self->__var___Block_20_100->win) ;
}

static void  __fini___Closure_57_32(SuiDialog$__Closure_57_32 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDialog$__Closure_57_32, __var___Block_20_100) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDialog$__Closure_57_32*  __make___Closure_57_32(SuiDialog$__Closure_57_32 **  __outRef__, SuiDialog$__Block_20_100 *  __var___Block_20_100){
	URGC_VAR_CLEANUP SuiDialog$__Closure_57_32*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDialog$__Closure_57_32) , __fini___Closure_57_32) ));
	self->invoke = __fn___Closure_57_32;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDialog$__Closure_57_32, __var___Block_20_100) , __var___Block_20_100) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_77_45(SuiDialog$__Closure_77_45 *  self, Orc$String*  nv){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(nv);

	printf("new value:%s\n", nv->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	SuiDialog$MessageDialog_alert(Orc$String$addString(Orc$str(&tmpReturn_1, "新值：") , nv) ->str, "tip") ;
}

static void  __fini___Closure_77_45(SuiDialog$__Closure_77_45 *  self){
	urgc_free_later(self) ;
}

static SuiDialog$__Closure_77_45*  __make___Closure_77_45(SuiDialog$__Closure_77_45 **  __outRef__){
	URGC_VAR_CLEANUP SuiDialog$__Closure_77_45*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDialog$__Closure_77_45) , __fini___Closure_77_45) ));
	self->invoke = __fn___Closure_77_45;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



