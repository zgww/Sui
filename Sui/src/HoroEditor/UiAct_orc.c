
#include "UiAct_orc.h" 

#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "./HoroEditCtx_orc.h"
#include "./HoroEditor_orc.h"
#include "../SuiDesigner/ANode_orc.h"
#include "../SuiDesigner/EventANodeChanged_orc.h"
#include "../Sui/Core/NodeLib_orc.h"
#include "../Sui/Dialog/Toast_orc.h"


// static struct 


// static function declaration


void  HoroEditor$UiAct_savePrefab(HoroEditor$HoroEditor *  editor){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroEditCtx*  ctx = (ctx=NULL,urgc_init_var_class((void**)&ctx, editor->editCtx));
	if (ctx->prefab) {
		ctx->prefab->save(ctx->prefab) ;
	}
}

void  HoroEditor$UiAct_addView(HoroEditor$HoroEditor *  editor, SuiDesigner$ANode*  anode, Orc$String*  viewName){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(anode);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(viewName);

	if (!anode->node) {
		SuiDialog$Toast_make("node is null") ;
		return ; 
	}
	SuiCore$NodeLib *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$NodeRegisterInfo*  info = (tmpThis_1 = SuiCore$NodeLib_use() )->findByClassName((info = NULL,&info), tmpThis_1, viewName->str) ;
	if (!info) {
		SuiDialog$Toast_make("未找到节点类") ;
		return ; 
	}
	URGC_VAR_CLEANUP_CLASS SuiDesigner$ANode*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$ANode*  o = SuiDesigner$ANode_new(&tmpNewOwner_1) ;
		
	
		urgc_set_field_class(o, (void * )offsetof(SuiDesigner$ANode, tag) , viewName) ;
		anode->appendChild(anode, o) ;
		o->updateSubTreeNodes(o) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner$EventANodeChanged*  tmpNewOwner_2 = NULL;
		{
			SuiDesigner$EventANodeChanged*  o = SuiDesigner$EventANodeChanged_new(&tmpNewOwner_2) ;
			
		
			urgc_set_field_class(o, (void * )offsetof(SuiDesigner$EventANodeChanged, anode) , anode) ;
			((SuiDesigner$EventToEbus * )o)->emitToEbus(o) ;
		}
	}
}



