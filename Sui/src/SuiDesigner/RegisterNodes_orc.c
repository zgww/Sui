
#include "RegisterNodes_orc.h" 

#include <stdio.h>
#include "./Serial/BiJson_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/TableView_orc.h"
#include "../Sui/View/Switch_orc.h"
#include "../Sui/View/Slider_orc.h"
#include "../Sui/View/Select_orc.h"
#include "../Sui/View/Panel_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/ProgressView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutGrid_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/Layout/RowWrap_orc.h"
#include "../Sui/Core/NodeLib_orc.h"


// static struct 


// static function declaration


void  SuiDesigner$registerNodes(){
	URGC_VAR_CLEANUP_CLASS SuiCore$NodeLib*  lib = (lib=NULL,urgc_init_var_class((void**)&lib, SuiCore$NodeLib_use() ));
	lib->registerClass(lib, Vtable_SuiCore$ViewBase_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiCore$View_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$ImageView_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$HoverViewEffect_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$TextView_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$TreeView_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$TableView_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$Switch_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$Select_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$Panel_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$EditText_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$ProgressView_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$ScrollArea_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$Button_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$DrawButton_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiView$MenuButton_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiLayout$LayoutLinear_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiLayout$LayoutGrid_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiLayout$LayoutAlign_init(NULL)) ;
	lib->registerClass(lib, Vtable_SuiLayout$RowWrap_init(NULL)) ;
}



