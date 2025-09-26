
#include "Path_orc.h" 

#include <stdio.h>
#include "./String_orc.h"
#include "./List_orc.h"


// static struct 


// static function declaration


OrcLang$String*  OrcLang$Path_basename(OrcLang$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$Path_normal((tmp = NULL,&tmp), s) ;
	int  idx = tmp->lastIndexByteOf(tmp, "/") ;
	URGC_VAR_CLEANUP OrcLang$String*  ret = tmp->substringByByteStart((ret = NULL,&ret), tmp, idx + 1) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

OrcLang$String*  OrcLang$Path_dirname(OrcLang$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$Path_normal((tmp = NULL,&tmp), s) ;
	int  idx = tmp->lastIndexByteOf(tmp, "/") ;
	URGC_VAR_CLEANUP OrcLang$String*  ret = tmp->substringByByteRange((ret = NULL,&ret), tmp, 0, idx) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

OrcLang$String*  OrcLang$Path_normal(OrcLang$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP OrcLang$String*  ret = OrcLang$str((ret = NULL,&ret), s) ;
	URGC_VAR_CLEANUP OrcLang$String*  newPath = ret->replaceAllByRe((newPath = NULL,&newPath), ret, "\\\\+", "/") ;
	return urgc_set_var_for_return((void ** )__outRef__, newPath) ; 
}

OrcLang$String*  OrcLang$Path_filename(OrcLang$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = tmp->lastIndexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP OrcLang$String*  ret = tmp->substringByByteRange((ret = NULL,&ret), tmp, 0, idx) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

OrcLang$String*  OrcLang$Path_pureFilename(OrcLang$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = tmp->indexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP OrcLang$String*  ret = tmp->substringByByteRange((ret = NULL,&ret), tmp, 0, idx) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

OrcLang$String*  OrcLang$Path_ext(OrcLang$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = tmp->lastIndexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP OrcLang$String*  ret = tmp->substringByByteStart((ret = NULL,&ret), tmp, idx) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

OrcLang$String*  OrcLang$Path_fullExt(OrcLang$String **  __outRef__, const char *  s){
	URGC_VAR_CLEANUP OrcLang$String*  tmp = OrcLang$Path_basename((tmp = NULL,&tmp), s) ;
	int  idx = tmp->indexByteOf(tmp, ".") ;
	URGC_VAR_CLEANUP OrcLang$String*  ret = tmp->substringByByteStart((ret = NULL,&ret), tmp, idx) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

bool  OrcLang$Path_isFile(const char *  path){
	bool  ret = OrcLang$Path_exists(path)  && !OrcLang$Path_isDirectory(path) ;
	return ret; 
}

OrcLang$String*  OrcLang$Path_append(OrcLang$String **  __outRef__, const char *  path, const char *  path2){
	URGC_VAR_CLEANUP OrcLang$String*  ret = OrcLang$str((ret = NULL,&ret), path) ;
	OrcLang$String *  tmpThis_1 = NULL;
	(tmpThis_1 = ret->add(ret, "/") )->add(tmpThis_1, path2) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

bool  OrcLang$Path_copyToDir(const char *  src, const char *  dir){
	if (!OrcLang$Path_isDirectory(dir) ) {
		return false; 
	}
	URGC_VAR_CLEANUP OrcLang$String*  basename = OrcLang$Path_basename((basename = NULL,&basename), src) ;
	URGC_VAR_CLEANUP OrcLang$String*  newPath = OrcLang$Path_append((newPath = NULL,&newPath), dir, basename) ;
	bool  ok = OrcLang$Path_copyTo(src, newPath) ;
	return ok; 
}

bool  OrcLang$Path_moveToDir(const char *  src, const char *  dir){
	if (!OrcLang$Path_isDirectory(dir) ) {
		return false; 
	}
	URGC_VAR_CLEANUP OrcLang$String*  basename = OrcLang$Path_basename((basename = NULL,&basename), src) ;
	URGC_VAR_CLEANUP OrcLang$String*  newPath = OrcLang$Path_append((newPath = NULL,&newPath), dir, basename) ;
	bool  ok = OrcLang$Path_rename(src, newPath->str) ;
	return ok; 
}

OrcLang$List*  OrcLang$Path_listSubtree(OrcLang$List **  __outRef__, const char *  path){
	URGC_VAR_CLEANUP OrcLang$List*  ret = urgc_init_var((void**)&ret, OrcLang$List_new() );
	OrcLang$Path_listSubtree_toList(path, ret) ;
	return urgc_set_var_for_return((void ** )__outRef__, ret) ; 
}

void  OrcLang$Path_listSubtree_toList(const char *  path, OrcLang$List *  outList){
	URGC_VAR_CLEANUP OrcLang$List*  lst = OrcLang$Path_list((lst = NULL,&lst), path) ;
	int  l = lst->size(lst) ;
	for (int  i = 0; i < l; i++) {
		OrcLang$String *  curpath = (OrcLang$String * )lst->get(lst, i) ;
		outList->add(outList, curpath) ;
		if (OrcLang$Path_isDirectory(curpath->str) ) {
			OrcLang$Path_listSubtree_toList(curpath->str, outList) ;
		}
	}
}

void  OrcLang$testPath(){
	{
		URGC_VAR_CLEANUP OrcLang$String*  bname = OrcLang$Path_basename((bname = NULL,&bname), "/a/b/csdfjsie") ;
		printf("bname:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$String*  bname = OrcLang$Path_dirname((bname = NULL,&bname), "/a/b/csdfjsie") ;
		printf("dirname:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$String*  bname = OrcLang$Path_filename((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("filename:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$String*  bname = OrcLang$Path_ext((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("ext:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$String*  bname = OrcLang$Path_pureFilename((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("pure filename:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$String*  bname = OrcLang$Path_fullExt((bname = NULL,&bname), "/a/b/openfile.json.orc") ;
		printf("full ext:%s\n", bname->str) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$List*  paths = OrcLang$Path_list((paths = NULL,&paths), "d:/ws") ;
		for (int  i = 0; i < paths->size(paths) ; i++) {
			URGC_VAR_CLEANUP OrcLang$String*  path = urgc_init_var((void**)&path, (OrcLang$String* )paths->get(paths, i) );
			printf("\t%s\n", path->str) ;
		}
	}
	{
		bool  isDir = OrcLang$Path_isDirectory("/ws") ;
		bool  isFile = OrcLang$Path_isFile("/ws") ;
		bool  exists = OrcLang$Path_exists("/ws") ;
		printf("isDir:%d %d, %d\n", isDir, isFile, exists) ;
	}
	{
		URGC_VAR_CLEANUP OrcLang$List*  paths = OrcLang$Path_listSubtree((paths = NULL,&paths), "./") ;
		for (int  i = 0; i < paths->size(paths) ; i++) {
			URGC_VAR_CLEANUP OrcLang$String*  path = urgc_init_var((void**)&path, (OrcLang$String* )paths->get(paths, i) );
			printf("\t%s\n", path->str) ;
		}
	}
	{
		OrcLang$Path_mkdirs("/ws/a/b/c/d") ;
	}
}



