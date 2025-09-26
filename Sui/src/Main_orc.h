


#ifndef define_struct_____Main_orc_h__
#define define_struct_____Main_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE_____Main_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include "../UrgcDll/urgc_api.h"
#include "Orc/Orc.h"




#ifdef INCLUDE_ONLY_TYPE_____Main_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef ____Main_orc_h__
#define ____Main_orc_h__

//include  importHeadCode
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


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
extern void  windowInit();
void  initMain();
int  main();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
