
#include "Keyboard_orc.h" 

#include <stdio.h>
#include "./KeyEvent_orc.h"
#include "./Window_orc.h"
#include "./App_orc.h"
#include "../../Orc/String_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$KeyboardData_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$KeyboardData", sizeof( SuiCore$KeyboardData ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "char_code", OrcMetaType_int, offsetof(SuiCore$KeyboardData, char_code), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "key", OrcMetaType_char, offsetof(SuiCore$KeyboardData, key), 0, 0, 1, 1);//char
		orc_metaField_primitive(&pNext, "windowId", OrcMetaType_long_long, offsetof(SuiCore$KeyboardData, windowId), 0, 0, 0, 0);//longlong
		orc_metaField_primitive(&pNext, "isKeyDown", OrcMetaType_bool, offsetof(SuiCore$KeyboardData, isKeyDown), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "isKeyUp", OrcMetaType_bool, offsetof(SuiCore$KeyboardData, isKeyUp), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "shift", OrcMetaType_bool, offsetof(SuiCore$KeyboardData, shift), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "ctrl", OrcMetaType_bool, offsetof(SuiCore$KeyboardData, ctrl), 0, 0, 0, 0);//bool
		orc_metaField_primitive(&pNext, "alt", OrcMetaType_bool, offsetof(SuiCore$KeyboardData, alt), 0, 0, 0, 0);//bool
    }
	return meta;
}
SuiCore$KeyEvent*  SuiCore$newKeyEvent_fromKeyboardData(SuiCore$KeyEvent **  __outRef__, SuiCore$KeyboardData *  kd){
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  app = SuiCore$App_use((app = NULL,&app)) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, app->findWindowById(app, kd->windowId) ));
	URGC_VAR_CLEANUP_CLASS SuiCore$KeyEvent*  ke = (ke=NULL,urgc_init_var_class((void**)&ke, SuiCore$KeyEvent_new(&ke) ));
	ke->char_code = kd->char_code;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(ke, (void * )offsetof(SuiCore$KeyEvent, key) , Orc$str(&tmpReturn_1, kd->key) ) ;
	urgc_set_field_class(ke, (void * )offsetof(SuiCore$KeyEvent, window) , win) ;
	ke->isKeyDown = kd->isKeyDown;
	ke->isKeyUp = kd->isKeyUp;
	ke->shift = kd->shift;
	ke->ctrl = kd->ctrl;
	ke->alt = kd->alt;
	return urgc_set_var_for_return_class((void ** )__outRef__, ke) ; 
}

void  SuiCore$Keyboard_onKeyDown(SuiCore$KeyboardData *  kd){
	SuiCore$printKeyboardData(kd) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$KeyEvent*  ke = SuiCore$newKeyEvent_fromKeyboardData((ke = NULL,&ke), kd) ;
	ke->dispatch(ke) ;
}

void  SuiCore$Keyboard_onKeyUp(SuiCore$KeyboardData *  kd){
	SuiCore$printKeyboardData(kd) ;
	URGC_VAR_CLEANUP_CLASS SuiCore$KeyEvent*  ke = SuiCore$newKeyEvent_fromKeyboardData((ke = NULL,&ke), kd) ;
	ke->dispatch(ke) ;
}

void  SuiCore$printKeyboardData(SuiCore$KeyboardData *  kd){
	printf("KeyboardData. char_code:%d, key:%s, windowId:%lld, isKeyDown:%d, isKeyUp:%d, shift:%d, ctrl:%d, alt:%d\n", kd->char_code, kd->key, kd->windowId, kd->isKeyDown, kd->isKeyUp, kd->shift, kd->ctrl, kd->alt) ;
}



