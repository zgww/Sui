
#include "UiAct_orc.h" 

#include "./HoroEditCtx_orc.h"
#include "./HoroEditor_orc.h"


// static struct 


// static function declaration


void  HoroEditor$UiAct_savePrefab(HoroEditor$HoroEditor *  editor){
	URGC_VAR_CLEANUP_CLASS HoroEditor$HoroEditCtx*  ctx = (ctx=NULL,urgc_init_var_class((void**)&ctx, editor->editCtx));
	if (ctx->prefab) {
		ctx->prefab->save(ctx->prefab) ;
	}
}



