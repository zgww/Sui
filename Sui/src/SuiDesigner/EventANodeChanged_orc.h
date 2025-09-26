
typedef struct tagSuiDesigner$EventToEbus SuiDesigner$EventToEbus;
typedef struct tagVtable_SuiDesigner$EventToEbus Vtable_SuiDesigner$EventToEbus;
typedef struct tagSuiDesigner$EventANodeChanged SuiDesigner$EventANodeChanged;
typedef struct tagVtable_SuiDesigner$EventANodeChanged Vtable_SuiDesigner$EventANodeChanged;
typedef struct tagSuiDesigner$EventANodeAttrChanged SuiDesigner$EventANodeAttrChanged;
typedef struct tagVtable_SuiDesigner$EventANodeAttrChanged Vtable_SuiDesigner$EventANodeAttrChanged;


#ifndef define_struct___SuiDesigner__EventANodeChanged_orc_h__
#define define_struct___SuiDesigner__EventANodeChanged_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__EventANodeChanged_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>





#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__EventANodeChanged_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__EventANodeChanged_orc_h__
#define __SuiDesigner__EventANodeChanged_orc_h__

//include  importHeadCode
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Emitter_orc.h"
#include "./ANode_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$EventToEbus {
	Vtable_SuiCore$Event super;
};
//虚表实例
extern Vtable_SuiDesigner$EventToEbus _vtable_SuiDesigner$EventToEbus;

// class refc:0
struct tagSuiDesigner$EventToEbus {
	SuiCore$Event super; 
	void  (*emitToEbus) (SuiDesigner$EventToEbus *  self);
};
Vtable_SuiDesigner$EventToEbus* Vtable_SuiDesigner$EventToEbus_init(Vtable_SuiDesigner$EventToEbus* pvt);
void SuiDesigner$EventToEbus_init_fields(SuiDesigner$EventToEbus *self);
void SuiDesigner$EventToEbus_init(SuiDesigner$EventToEbus *self, void *pOwner);
SuiDesigner$EventToEbus * SuiDesigner$EventToEbus_new(void *pOwner);
void SuiDesigner$EventToEbus_fini(SuiDesigner$EventToEbus *self);

void  SuiDesigner$EventToEbus$emitToEbus(SuiDesigner$EventToEbus *  self);


// 虚表
struct tagVtable_SuiDesigner$EventANodeChanged {
	Vtable_SuiDesigner$EventToEbus super;
};
//虚表实例
extern Vtable_SuiDesigner$EventANodeChanged _vtable_SuiDesigner$EventANodeChanged;

// class refc:0
struct tagSuiDesigner$EventANodeChanged {
	SuiDesigner$EventToEbus super; 
	SuiDesigner$ANode*  anode ;
};
Vtable_SuiDesigner$EventANodeChanged* Vtable_SuiDesigner$EventANodeChanged_init(Vtable_SuiDesigner$EventANodeChanged* pvt);
void SuiDesigner$EventANodeChanged_init_fields(SuiDesigner$EventANodeChanged *self);
void SuiDesigner$EventANodeChanged_init(SuiDesigner$EventANodeChanged *self, void *pOwner);
SuiDesigner$EventANodeChanged * SuiDesigner$EventANodeChanged_new(void *pOwner);
void SuiDesigner$EventANodeChanged_fini(SuiDesigner$EventANodeChanged *self);



// 虚表
struct tagVtable_SuiDesigner$EventANodeAttrChanged {
	Vtable_SuiDesigner$EventToEbus super;
};
//虚表实例
extern Vtable_SuiDesigner$EventANodeAttrChanged _vtable_SuiDesigner$EventANodeAttrChanged;

// class refc:0
struct tagSuiDesigner$EventANodeAttrChanged {
	SuiDesigner$EventToEbus super; 
	SuiDesigner$ANode*  anode ;
};
Vtable_SuiDesigner$EventANodeAttrChanged* Vtable_SuiDesigner$EventANodeAttrChanged_init(Vtable_SuiDesigner$EventANodeAttrChanged* pvt);
void SuiDesigner$EventANodeAttrChanged_init_fields(SuiDesigner$EventANodeAttrChanged *self);
void SuiDesigner$EventANodeAttrChanged_init(SuiDesigner$EventANodeAttrChanged *self, void *pOwner);
SuiDesigner$EventANodeAttrChanged * SuiDesigner$EventANodeAttrChanged_new(void *pOwner);
void SuiDesigner$EventANodeAttrChanged_fini(SuiDesigner$EventANodeAttrChanged *self);





#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
