


#ifndef define_struct___Orc__Path_orc_h__
#define define_struct___Orc__Path_orc_h__


#ifdef INCLUDE_ONLY_TYPE
#define INCLUDE_ONLY_TYPE___Orc__Path_orc_h__
#endif

#include "Orc/Orc.h"
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <time.h>




#ifdef INCLUDE_ONLY_TYPE___Orc__Path_orc_h__
#define INCLUDE_ONLY_TYPE
#endif


#endif

#ifndef INCLUDE_ONLY_TYPE


// include once e.g.__App_orc_h__
#ifndef __Orc__Path_orc_h__
#define __Orc__Path_orc_h__

//include  importHeadCode
#include "./String_orc.h"
#include "./Math_orc.h"
#include "./List_orc.h"


#ifdef __cplusplus
extern "C"{
#endif

//代码内容
Orc$String*  Orc$Path_basename(Orc$String **  __outRef__, const char *  s);
Orc$String*  Orc$Path_dirname(Orc$String **  __outRef__, const char *  s);
Orc$String*  Orc$Path_relPathToFile(Orc$String **  __outRef__, const char *  path, const char *  relFilePath);
Orc$List*  Orc$Path_splitString(Orc$List **  __outRef__, Orc$String *  p);
Orc$String*  Orc$Path_toAbsolute(Orc$String **  __outRef__, const char *  p);
Orc$String*  Orc$Path_normal(Orc$String **  __outRef__, const char *  s);
Orc$String*  Orc$Path_withBasename(Orc$String **  __outRef__, const char *  path, const char *  newbasename);
Orc$String*  Orc$Path_withLastExt(Orc$String **  __outRef__, const char *  path, const char *  newExt);
Orc$String*  Orc$Path_withExt(Orc$String **  __outRef__, const char *  path, const char *  newExt);
Orc$String*  Orc$Path_filename(Orc$String **  __outRef__, const char *  s);
Orc$String*  Orc$Path_pureFilename(Orc$String **  __outRef__, const char *  s);
Orc$String*  Orc$Path_ext(Orc$String **  __outRef__, const char *  s);
Orc$String*  Orc$Path_fullExt(Orc$String **  __outRef__, const char *  s);
bool  Orc$Path_isFile(const char *  path);
extern bool  Orc$Path_isDirectory(const char *  path);
extern bool  Orc$Path_mkdirs(const char *  dirpath);
extern bool  Orc$Path_exists(const char *  path);
Orc$String*  Orc$Path_append(Orc$String **  __outRef__, const char *  path, const char *  path2);
bool  Orc$Path_copyToDir(const char *  src, const char *  dir);
bool  Orc$Path_moveToDir(const char *  src, const char *  dir);
extern long long  Orc$Path_mtimeMs(const char *  src);
Orc$String*  Orc$Path_mtimeStr(Orc$String **  __outRef__, const char *  src);
extern bool  Orc$Path_copyTo(const char *  src, const char *  dst);
extern bool  Orc$Path_rename(const char *  src, const char *  dst);
extern bool  Orc$Path_remove(const char *  src);
extern bool  Orc$Path_removeDir(const char *  src);
extern bool  Orc$Path_removeDirs(const char *  src);
extern bool  Orc$Path_removeFile(const char *  src);
extern bool  Orc$Path_touch(const char *  src);
extern bool  Orc$Path_fopen(const char *  src, const char *  mode);
extern Orc$List*  Orc$Path_list(Orc$List **  __outRef__, const char *  path);
Orc$List*  Orc$Path_listSubtree(Orc$List **  __outRef__, const char *  path);
void  Orc$Path_listSubtree_toList(const char *  path, Orc$List *  outList);
extern Orc$String*  Orc$Path_getcwd(Orc$String **  __outRef__);
extern void  Orc$Path_setcwd(const char *  path);
extern Orc$String*  Orc$Path_getExecutionPath(Orc$String **  __outRef__);
Orc$String*  Orc$Path_resolveFromExecutionDir(Orc$String **  __outRef__, const char *  path);
extern Orc$String*  Orc$Path_readText(Orc$String **  __outRef__, const char *  path);
extern bool  Orc$Path_writeText(const char *  path, const char *  text);
bool  Orc$Path_isUsualImage(const char *  path);
Orc$String*  Orc$Path_resolveRelativeFromFile(Orc$String **  __outRef__, const char *  path, const char *  basefilepath);
void  Orc$testPath();



#ifdef __cplusplus
}
#endif // ___cplusplus

#endif // include once

#endif // INCLUDE_ONLY_TYPE
