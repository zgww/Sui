
#include "Main_orc.h" 

#include <stdio.h>
#include "../Orc/Orc.h"
#include "../../UrgcDll/urgc_api.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/Core/App_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Window_orc.h"


// static struct 


// static function declaration


int  main(){
	urgc_start_process_thread() ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  win = (win=NULL,urgc_init_var_class((void**)&win, Sui$Window_new(&win) ));
	win->setTitle(win, "TestMini") ;
	win->setSize(win, 800, 600) ;
	win->show(win) ;
	SuiCore$App *  tmpThis_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$App*  tmpReturn_1 = NULL;
	(tmpThis_1 = SuiCore$App_use(&tmpReturn_1) )->runEventLoop(tmpThis_1) ;
}



