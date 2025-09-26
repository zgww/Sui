


#ifndef INCLUDE_ONLY_TYPE

// include once e.g.__App_orc_h__
#ifndef __Path_orc_h__
#define __Path_orc_h__

//include  importHeadCode
#include "Orc/Orc.h"
#include <stdlib.h>
#include <stdio.h>
#include "./String_orc.h"
#include "./List_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
OrcLang$String*  OrcLang$Path_basename(OrcLang$String **  __outRef__, const char *  s);
OrcLang$String*  OrcLang$Path_dirname(OrcLang$String **  __outRef__, const char *  s);
OrcLang$String*  OrcLang$Path_normal(OrcLang$String **  __outRef__, const char *  s);
OrcLang$String*  OrcLang$Path_filename(OrcLang$String **  __outRef__, const char *  s);
OrcLang$String*  OrcLang$Path_pureFilename(OrcLang$String **  __outRef__, const char *  s);
OrcLang$String*  OrcLang$Path_ext(OrcLang$String **  __outRef__, const char *  s);
OrcLang$String*  OrcLang$Path_fullExt(OrcLang$String **  __outRef__, const char *  s);
bool  OrcLang$Path_isFile(const char *  path);
bool  OrcLang$Path_isDirectory(const char *  path);
bool  OrcLang$Path_mkdirs(const char *  dirpath);
bool  OrcLang$Path_exists(const char *  path);
OrcLang$String*  OrcLang$Path_append(OrcLang$String **  __outRef__, const char *  path, const char *  path2);
bool  OrcLang$Path_copyToDir(const char *  src, const char *  dir);
bool  OrcLang$Path_moveToDir(const char *  src, const char *  dir);
bool  OrcLang$Path_copyTo(const char *  src, const char *  dst);
bool  OrcLang$Path_rename(const char *  src, const char *  dst);
bool  OrcLang$Path_remove(const char *  src);
bool  OrcLang$Path_removeDir(const char *  src);
bool  OrcLang$Path_removeDirs(const char *  src);
bool  OrcLang$Path_removeFile(const char *  src);
bool  OrcLang$Path_touch(const char *  src);
bool  OrcLang$Path_fopen(const char *  src, const char *  mode);
OrcLang$List*  OrcLang$Path_list(OrcLang$List **  __outRef__, const char *  path);
OrcLang$List*  OrcLang$Path_listSubtree(OrcLang$List **  __outRef__, const char *  path);
void  OrcLang$Path_listSubtree_toList(const char *  path, OrcLang$List *  outList);
OrcLang$String*  OrcLang$Path_getcwd(OrcLang$String **  __outRef__);
void  OrcLang$Path_setcwd(const char *  path);
OrcLang$String*  OrcLang$Path_getExecutionPath(OrcLang$String **  __outRef__);
OrcLang$String*  OrcLang$Path_readText(OrcLang$String **  __outRef__, const char *  path);
void  OrcLang$Path_writeText(const char *  path, const char *  text);
void  OrcLang$testPath();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
