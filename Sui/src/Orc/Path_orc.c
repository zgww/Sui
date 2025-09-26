
#include "Path_orc.h" 

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "./String_orc.h"
#include "./Math_orc.h"
#include "./List_orc.h"


// static struct 


// static function declaration


Orc$String*  Orc$Path_basename(Orc$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$Path_normal((tmp = NULL,&tmp), s) ;
	int  idx = Orc$String$lastIndexByteOf(tmp, "/") ;
	if (idx == -1) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, s) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String$substringByByteStart((ret = NULL,&ret), tmp, idx + 1) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$Path_dirname(Orc$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$Path_normal((tmp = NULL,&tmp), s) ;
	int  idx = Orc$String$lastIndexByteOf(tmp, "/") ;
	if (idx == -1) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, ".") ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String$substringByByteRange((ret = NULL,&ret), tmp, 0, idx) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$Path_relPathToFile(Orc$String **  __outRef__, const char *  path, const char *  relFilePath){
	URGC_VAR_CLEANUP_CLASS Orc$String*  abspath = Orc$Path_toAbsolute((abspath = NULL,&abspath), path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  absTargetPath = Orc$Path_toAbsolute((absTargetPath = NULL,&absTargetPath), relFilePath) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  parts = Orc$String$splitByRe((parts = NULL,&parts), abspath, "/|\\\\") ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  targetParts = Orc$String$splitByRe((targetParts = NULL,&targetParts), absTargetPath, "/|\\\\") ;
	int  l0 = parts->size(parts) ;
	int  l1 = targetParts->size(targetParts) ;
	int  minl = Orc$minInt(l0, l1) ;
	int  samel = 0;
	for (int  i = 0; i < minl; i++) {
		Orc$String *  a = (Orc$String * )parts->get(parts, i) ;
		Orc$String *  b = (Orc$String * )targetParts->get(targetParts, i) ;
		if (!Orc$String$equalsString(a, b) ) {
			samel = i;
			break;
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$List*  segs = (segs=NULL,urgc_init_var_class((void**)&segs, Orc$List_new(&segs) ));
	for (int  i = samel; i < l1 - 1; i++) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		segs->add(segs, Orc$str(&tmpReturn_1, "..") ) ;
	}
	for (int  i = samel; i < l0; i++) {
		Orc$String *  part = (Orc$String * )parts->get(parts, i) ;
		segs->add(segs, part) ;
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  result = Orc$String_join((result = NULL,&result), segs, "/") ;
	return urgc_set_var_for_return_class((void ** )__outRef__, result) ; 
}

Orc$List*  Orc$Path_splitString(Orc$List **  __outRef__, Orc$String *  p){
	URGC_VAR_CLEANUP_CLASS Orc$List*  parts = Orc$String$splitByRe((parts = NULL,&parts), p, "/|\\\\") ;
	return urgc_set_var_for_return_class((void ** )__outRef__, parts) ; 
}

Orc$String*  Orc$Path_toAbsolute(Orc$String **  __outRef__, const char *  p){
	if (Orc$String_startsWith(p, "/") ) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, p) ) ; 
	}
	if (strlen(p)  >= 2 && p[1] == ':') {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_2, p) ) ; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  abs = Orc$Path_getcwd((abs = NULL,&abs)) ;
	Orc$String$add(Orc$String$add(abs, "/") , p) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  parts = Orc$String$splitByRe((parts = NULL,&parts), abs, "/|\\\\") ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  segs = (segs=NULL,urgc_init_var_class((void**)&segs, Orc$List_new(&segs) ));
	for (int  i = 0; i < parts->size(parts) ; i++) {
		Orc$String *  part = (Orc$String * )parts->get(parts, i) ;
		printf("part:%s\n", part->str) ;
		if (Orc$String$equals(part, ".") ) {
			continue;
		}
		else if (Orc$String$equals(part, "..") ) {
			if (segs->size(segs)  > 0) {
				segs->removeAt(segs, segs->size(segs)  - 1) ;
			}
		}
		else {
			segs->add(segs, part) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String_join((ret = NULL,&ret), segs, "/") ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$Path_normal(Orc$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), s) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  newPath = Orc$String$replaceAllByRe((newPath = NULL,&newPath), ret, "\\\\+", "/") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  newPath2 = Orc$String$replaceAllByRe((newPath2 = NULL,&newPath2), newPath, "^\\./|/\\.$", "") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  newPath3 = Orc$String$replaceAllByRe((newPath3 = NULL,&newPath3), newPath2, "/\\./", "/") ;
	return urgc_set_var_for_return_class((void ** )__outRef__, newPath3) ; 
}

Orc$String*  Orc$Path_withBasename(Orc$String **  __outRef__, const char *  path, const char *  newbasename){
	URGC_VAR_CLEANUP_CLASS Orc$String*  dirname = Orc$Path_dirname((dirname = NULL,&dirname), path) ;
	Orc$String$add(Orc$String$add(dirname, "/") , newbasename) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, dirname) ; 
}

Orc$String*  Orc$Path_withLastExt(Orc$String **  __outRef__, const char *  path, const char *  newExt){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$str((tmp = NULL,&tmp), path) ;
	int  idx = Orc$String$lastIndexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String$substringByByteRange((ret = NULL,&ret), tmp, 0, idx) ;
	Orc$String$add(ret, newExt) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$Path_withExt(Orc$String **  __outRef__, const char *  path, const char *  newExt){
	URGC_VAR_CLEANUP_CLASS Orc$String*  dirname = Orc$Path_dirname((dirname = NULL,&dirname), path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  pureFilename = Orc$Path_pureFilename((pureFilename = NULL,&pureFilename), path) ;
	Orc$String$add(Orc$String$addString(Orc$String$add(dirname, "/") , pureFilename) , newExt) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, dirname) ; 
}

Orc$String*  Orc$Path_filename(Orc$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = Orc$String$lastIndexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String$substringByByteRange((ret = NULL,&ret), tmp, 0, idx) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$Path_pureFilename(Orc$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = Orc$String$indexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String$substringByByteRange((ret = NULL,&ret), tmp, 0, idx) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$Path_ext(Orc$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = Orc$String$lastIndexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String$substringByByteStart((ret = NULL,&ret), tmp, idx) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

Orc$String*  Orc$Path_fullExt(Orc$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = Orc$String$indexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$String$substringByByteStart((ret = NULL,&ret), tmp, idx) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

bool  Orc$Path_isFile(const char *  path){
	bool  ret = Orc$Path_exists(path)  && !Orc$Path_isDirectory(path) ;
	return ret; 
}

Orc$String*  Orc$Path_append(Orc$String **  __outRef__, const char *  path, const char *  path2){
	URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$str((ret = NULL,&ret), path) ;
	Orc$String$add(Orc$String$add(ret, "/") , path2) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

bool  Orc$Path_copyToDir(const char *  src, const char *  dir){
	if (!Orc$Path_isDirectory(dir) ) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  basename = Orc$Path_basename((basename = NULL,&basename), src) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  newPath = Orc$Path_append((newPath = NULL,&newPath), dir, basename->str) ;
	bool  ok = Orc$Path_copyTo(src, newPath->str) ;
	return ok; 
}

bool  Orc$Path_moveToDir(const char *  src, const char *  dir){
	if (!Orc$Path_isDirectory(dir) ) {
		return false; 
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  basename = Orc$Path_basename((basename = NULL,&basename), src) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  newPath = Orc$Path_append((newPath = NULL,&newPath), dir, basename->str) ;
	bool  ok = Orc$Path_rename(src, newPath->str) ;
	return ok; 
}

Orc$String*  Orc$Path_mtimeStr(Orc$String **  __outRef__, const char *  src){
	long long  ms = Orc$Path_mtimeMs(src) ;
	long long  sec = ms / 1000L;
	struct tm *  t = localtime(&sec) ;
	char  buf[100];
	sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = Orc$str((s = NULL,&s), buf) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, s) ; 
}

Orc$List*  Orc$Path_listSubtree(Orc$List **  __outRef__, const char *  path){
	URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
	Orc$Path_listSubtree_toList(path, ret) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}

void  Orc$Path_listSubtree_toList(const char *  path, Orc$List *  outList){
	URGC_VAR_CLEANUP_CLASS Orc$List*  lst = Orc$Path_list((lst = NULL,&lst), path) ;
	int  l = lst->size(lst) ;
	for (int  i = 0; i < l; i++) {
		Orc$String *  curpath = (Orc$String * )lst->get(lst, i) ;
		outList->add(outList, curpath) ;
		if (Orc$Path_isDirectory(curpath->str) ) {
			Orc$Path_listSubtree_toList(curpath->str, outList) ;
		}
	}
}

bool  Orc$Path_isUsualImage(const char *  path){
	return Orc$String_endsWith(path, ".jpg")  || Orc$String_endsWith(path, ".png")  || Orc$String_endsWith(path, ".jpeg") ; 
}

Orc$String*  Orc$Path_resolveRelativeFromFile(Orc$String **  __outRef__, const char *  path, const char *  basefilepath){
	if (path && basefilepath) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmp = Orc$Path_dirname((tmp = NULL,&tmp), basefilepath) ;
		Orc$String$add(Orc$String$add(tmp, "/") , path) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  ret = Orc$Path_normal((ret = NULL,&ret), tmp->str) ;
		return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}

void  Orc$testPath(){
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  bname = Orc$Path_basename((bname = NULL,&bname), "/a/b/csdfjsie") ;
		printf("bname:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  bname = Orc$Path_dirname((bname = NULL,&bname), "/a/b/csdfjsie") ;
		printf("dirname:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  bname = Orc$Path_filename((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("filename:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  bname = Orc$Path_ext((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("ext:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  bname = Orc$Path_pureFilename((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("pure filename:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  bname = Orc$Path_fullExt((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("full ext:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$List*  paths = Orc$Path_list((paths = NULL,&paths), "d:/ws") ;
		for (int  i = 0; i < paths->size(paths) ; i++) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  path = (path=NULL,urgc_init_var_class((void**)&path, (Orc$String* )paths->get(paths, i) ));
			printf("\t%s\n", path->str) ;
		}
	}
	{
		bool  isDir = Orc$Path_isDirectory("/ws") ;
		bool  isFile = Orc$Path_isFile("/ws") ;
		bool  exists = Orc$Path_exists("/ws") ;
		printf("isDir:%d %d, %d\n", isDir, isFile, exists) ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$List*  paths = Orc$Path_listSubtree((paths = NULL,&paths), "./") ;
		for (int  i = 0; i < paths->size(paths) ; i++) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  path = (path=NULL,urgc_init_var_class((void**)&path, (Orc$String* )paths->get(paths, i) ));
			printf("\t%s\n", path->str) ;
		}
	}
	{
		Orc$Path_mkdirs("/ws/a/b/c/d") ;
	}
	{
		URGC_VAR_CLEANUP_CLASS Orc$String*  p = Orc$Path_resolveRelativeFromFile((p = NULL,&p), "a.png", "./a/././../b/c.matl.json") ;
		printf("p:%s\n", p->str) ;
	}
}



