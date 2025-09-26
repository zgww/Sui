
typedef struct tagSgl$Program Sgl$Program;
typedef struct tagVtable_Sgl$Program Vtable_Sgl$Program;


#ifndef define_struct___Sgl__Program_orc_h__
#define define_struct___Sgl__Program_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Sgl__Program_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include "./UnitOpengl.h"




#ifdef INCLUDE_ONLY_TYPE___Sgl__Program_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Sgl__Program_orc_h__
#define __Sgl__Program_orc_h__

//include  importHeadCode
#include "../Orc/Path_orc.h"
#include "../Orc/String_orc.h"
#include "../Sui/Core/Timer_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_Sgl$Program {
	Vtable_Object super;
};
//虚表实例
extern Vtable_Sgl$Program _vtable_Sgl$Program;

// class refc:0
struct tagSgl$Program {
	Object super; 
	GLuint id ;
	Orc$String*  vsPath ;
	Orc$String*  fsPath ;
	void  (*use) (Sgl$Program *  self);
	const char *  (*getVsPathCstr) (Sgl$Program *  self);
	const char *  (*getFsPathCstr) (Sgl$Program *  self);
	bool  (*compile) (Sgl$Program *  self, const char *  vs, const char *  fs);
	bool  (*compileByPathCstr) (Sgl$Program *  self, const char *  vsPath, const char *  fsPath);
	void  (*uniform1i) (Sgl$Program *  self, const char *  key, int  i);
	void  (*uniform2f) (Sgl$Program *  self, const char *  key, float  x, float  y);
	void  (*uniform3f) (Sgl$Program *  self, const char *  key, float  x, float  y, float  z);
	void  (*uniform4f) (Sgl$Program *  self, const char *  key, float  x, float  y, float  z, float  w);
	void  (*uniformMatrix4f) (Sgl$Program *  self, const char *  key, float *  data);
	void  (*uniformMatrix4fv) (Sgl$Program *  self, const char *  key, float *  data, int  matrixCnt);
};
Vtable_Sgl$Program* Vtable_Sgl$Program_init(Vtable_Sgl$Program* pvt);
void Sgl$Program_init_fields(Sgl$Program *self);
void Sgl$Program_init(Sgl$Program *self, void *pOwner);
Sgl$Program * Sgl$Program_new(void *pOwner);
void Sgl$Program_fini(Sgl$Program *self);

void  Sgl$Program$dtor(Sgl$Program *  self);
extern void  Sgl$Program$use(Sgl$Program *  self);
const char *  Sgl$Program$getVsPathCstr(Sgl$Program *  self);
const char *  Sgl$Program$getFsPathCstr(Sgl$Program *  self);
extern bool  Sgl$Program$compile(Sgl$Program *  self, const char *  vs, const char *  fs);
bool  Sgl$Program$compileByPathCstr(Sgl$Program *  self, const char *  vsPath, const char *  fsPath);
extern void  Sgl$Program$uniform1i(Sgl$Program *  self, const char *  key, int  i);
extern void  Sgl$Program$uniform2f(Sgl$Program *  self, const char *  key, float  x, float  y);
extern void  Sgl$Program$uniform3f(Sgl$Program *  self, const char *  key, float  x, float  y, float  z);
extern void  Sgl$Program$uniform4f(Sgl$Program *  self, const char *  key, float  x, float  y, float  z, float  w);
void  Sgl$Program$uniformMatrix4f(Sgl$Program *  self, const char *  key, float *  data);
extern void  Sgl$Program$uniformMatrix4fv(Sgl$Program *  self, const char *  key, float *  data, int  matrixCnt);

extern void  Sgl$deleteProgram(GLuint id);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
