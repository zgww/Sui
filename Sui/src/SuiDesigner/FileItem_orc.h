
typedef struct tagSuiDesigner$FileItem SuiDesigner$FileItem;
typedef struct tagVtable_SuiDesigner$FileItem Vtable_SuiDesigner$FileItem;


#ifndef define_struct___SuiDesigner__FileItem_orc_h__
#define define_struct___SuiDesigner__FileItem_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___SuiDesigner__FileItem_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>




#ifdef INCLUDE_ONLY_TYPE___SuiDesigner__FileItem_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __SuiDesigner__FileItem_orc_h__
#define __SuiDesigner__FileItem_orc_h__

//include  importHeadCode
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "./EventFileItemChanged_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容

// 虚表
struct tagVtable_SuiDesigner$FileItem {
	Vtable_Object super;
};
//虚表实例
extern Vtable_SuiDesigner$FileItem _vtable_SuiDesigner$FileItem;

// class refc:0
struct tagSuiDesigner$FileItem {
	Object super; 
	Orc$String*  filename ;
	Orc$List*  children ;
	Orc$String*  path ;
	SuiDesigner$FileItem*  parent ;
	bool  isDirectory ;
	Orc$List*  subDirectoryChildren ;
	Orc$List*  (*getSubDirectoryChildren) (Orc$List **  __outRef__, SuiDesigner$FileItem *  self);
	bool  (*hasSubDirectory) (SuiDesigner$FileItem *  self);
	void  (*appendChild) (SuiDesigner$FileItem *  self, SuiDesigner$FileItem*  fi);
	void  (*removeChild) (SuiDesigner$FileItem *  self, SuiDesigner$FileItem *  fi);
	void  (*removeSelf) (SuiDesigner$FileItem *  self);
	void  (*setPathByParentPathAndFilename) (SuiDesigner$FileItem *  self, Orc$String*  parentPath, Orc$String*  filename);
	void  (*setPath) (SuiDesigner$FileItem *  self, Orc$String*  path);
	void  (*updatePathByParentPathAndSelfFilename) (SuiDesigner$FileItem *  self);
	void  (*updatePathByParnetPathAndSelfFilename_subtree) (SuiDesigner$FileItem *  self);
	void  (*loadSubtree) (SuiDesigner$FileItem *  self);
	void  (*printTree) (SuiDesigner$FileItem *  self, int  tab);
};
Vtable_SuiDesigner$FileItem* Vtable_SuiDesigner$FileItem_init(Vtable_SuiDesigner$FileItem* pvt);
void SuiDesigner$FileItem_init_fields(SuiDesigner$FileItem *self);
void SuiDesigner$FileItem_init(SuiDesigner$FileItem *self, void *pOwner);
SuiDesigner$FileItem * SuiDesigner$FileItem_new(void *pOwner);
void SuiDesigner$FileItem_fini(SuiDesigner$FileItem *self);

Orc$List*  SuiDesigner$FileItem$getSubDirectoryChildren(Orc$List **  __outRef__, SuiDesigner$FileItem *  self);
bool  SuiDesigner$FileItem$hasSubDirectory(SuiDesigner$FileItem *  self);
void  SuiDesigner$FileItem$appendChild(SuiDesigner$FileItem *  self, SuiDesigner$FileItem*  fi);
void  SuiDesigner$FileItem$removeChild(SuiDesigner$FileItem *  self, SuiDesigner$FileItem *  fi);
void  SuiDesigner$FileItem$removeSelf(SuiDesigner$FileItem *  self);
void  SuiDesigner$FileItem$setPathByParentPathAndFilename(SuiDesigner$FileItem *  self, Orc$String*  parentPath, Orc$String*  filename);
void  SuiDesigner$FileItem$setPath(SuiDesigner$FileItem *  self, Orc$String*  path);
void  SuiDesigner$FileItem$updatePathByParentPathAndSelfFilename(SuiDesigner$FileItem *  self);
void  SuiDesigner$FileItem$updatePathByParnetPathAndSelfFilename_subtree(SuiDesigner$FileItem *  self);
void  SuiDesigner$FileItem$loadSubtree(SuiDesigner$FileItem *  self);
void  SuiDesigner$FileItem$printTree(SuiDesigner$FileItem *  self, int  tab);

SuiDesigner$FileItem*  SuiDesigner$FileItem_loadDirectoryTree(SuiDesigner$FileItem **  __outRef__, const char *  dir);



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
