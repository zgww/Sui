
typedef struct tagSuiDesigner$EventFileItemChanged SuiDesigner$EventFileItemChanged;
typedef struct tagVtable_SuiDesigner$EventFileItemChanged Vtable_SuiDesigner$EventFileItemChanged;


#ifndef define_struct___SuiDesigner__EventFileItemChanged_orc_h__
#define define_struct___SuiDesigner__EventFileItemChanged_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__EventFileItemChanged_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__EventFileItemChanged_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__EventFileItemChanged_orc_h__
#define __SuiDesigner__EventFileItemChanged_orc_h__

//include  importHeadCode
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "./FileItem_orc.h"
#include "./EventANodeChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$EventFileItemChanged {
	Vtable_SuiDesigner$EventToEbus super;
};
//虚表实例
extern Vtable_SuiDesigner$EventFileItemChanged _vtable_SuiDesigner$EventFileItemChanged;

// class refc:0
struct tagSuiDesigner$EventFileItemChanged {
	SuiDesigner$EventToEbus super; 
	SuiDesigner$FileItem*  fileItem ;
};
Vtable_SuiDesigner$EventFileItemChanged* Vtable_SuiDesigner$EventFileItemChanged_init(Vtable_SuiDesigner$EventFileItemChanged* pvt);
void SuiDesigner$EventFileItemChanged_init_fields(SuiDesigner$EventFileItemChanged *self);
void SuiDesigner$EventFileItemChanged_init(SuiDesigner$EventFileItemChanged *self, void *pOwner);
SuiDesigner$EventFileItemChanged * SuiDesigner$EventFileItemChanged_new(void *pOwner);
void SuiDesigner$EventFileItemChanged_fini(SuiDesigner$EventFileItemChanged *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
