
#include "FileItem_orc.h" 

#include <stdio.h>
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"
#include "./EventFileItemChanged_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$FileItem _vtable_SuiDesigner$FileItem;

// init meta

void SuiDesigner$FileItem_initMeta(Vtable_SuiDesigner$FileItem *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "filename", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$FileItem, filename), true, false, 1);
	orc_metaField_class(&pNext, "children", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$FileItem, children), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$FileItem, path), true, false, 1);
	orc_metaField_class(&pNext, "parent", ((Vtable_Object*)Vtable_SuiDesigner$FileItem_init(0)), offsetof(SuiDesigner$FileItem, parent), true, false, 1);
	orc_metaField_primitive(&pNext, "isDirectory", OrcMetaType_bool, offsetof(SuiDesigner$FileItem, isDirectory), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "subDirectoryChildren", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$FileItem, subDirectoryChildren), true, false, 1);

	orc_metaField_method(&pNext, "getSubDirectoryChildren", offsetof(SuiDesigner$FileItem, getSubDirectoryChildren));
	orc_metaField_method(&pNext, "hasSubDirectory", offsetof(SuiDesigner$FileItem, hasSubDirectory));
	orc_metaField_method(&pNext, "appendChild", offsetof(SuiDesigner$FileItem, appendChild));
	orc_metaField_method(&pNext, "removeChild", offsetof(SuiDesigner$FileItem, removeChild));
	orc_metaField_method(&pNext, "removeSelf", offsetof(SuiDesigner$FileItem, removeSelf));
	orc_metaField_method(&pNext, "setPathByParentPathAndFilename", offsetof(SuiDesigner$FileItem, setPathByParentPathAndFilename));
	orc_metaField_method(&pNext, "setPath", offsetof(SuiDesigner$FileItem, setPath));
	orc_metaField_method(&pNext, "updatePathByParentPathAndSelfFilename", offsetof(SuiDesigner$FileItem, updatePathByParentPathAndSelfFilename));
	orc_metaField_method(&pNext, "updatePathByParnetPathAndSelfFilename_subtree", offsetof(SuiDesigner$FileItem, updatePathByParnetPathAndSelfFilename_subtree));
	orc_metaField_method(&pNext, "loadSubtree", offsetof(SuiDesigner$FileItem, loadSubtree));
	orc_metaField_method(&pNext, "printTree", offsetof(SuiDesigner$FileItem, printTree));
}


// vtable init


Vtable_SuiDesigner$FileItem* Vtable_SuiDesigner$FileItem_init(Vtable_SuiDesigner$FileItem* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$FileItem;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$FileItem_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$FileItem";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$FileItem_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$FileItem_fini(SuiDesigner$FileItem *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$FileItem_init_fields(SuiDesigner$FileItem *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$FileItem_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileItem*)self)->filename, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileItem*)self)->children, Orc$List_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileItem*)self)->path, Orc$str(&tmpReturn_3, "") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileItem*)self)->parent, NULL);
	((SuiDesigner$FileItem*)self)->isDirectory = false;
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileItem*)self)->subDirectoryChildren, NULL);
    }
	((SuiDesigner$FileItem*)self)->getSubDirectoryChildren = (void*)SuiDesigner$FileItem$getSubDirectoryChildren;
	((SuiDesigner$FileItem*)self)->hasSubDirectory = (void*)SuiDesigner$FileItem$hasSubDirectory;
	((SuiDesigner$FileItem*)self)->appendChild = (void*)SuiDesigner$FileItem$appendChild;
	((SuiDesigner$FileItem*)self)->removeChild = (void*)SuiDesigner$FileItem$removeChild;
	((SuiDesigner$FileItem*)self)->removeSelf = (void*)SuiDesigner$FileItem$removeSelf;
	((SuiDesigner$FileItem*)self)->setPathByParentPathAndFilename = (void*)SuiDesigner$FileItem$setPathByParentPathAndFilename;
	((SuiDesigner$FileItem*)self)->setPath = (void*)SuiDesigner$FileItem$setPath;
	((SuiDesigner$FileItem*)self)->updatePathByParentPathAndSelfFilename = (void*)SuiDesigner$FileItem$updatePathByParentPathAndSelfFilename;
	((SuiDesigner$FileItem*)self)->updatePathByParnetPathAndSelfFilename_subtree = (void*)SuiDesigner$FileItem$updatePathByParnetPathAndSelfFilename_subtree;
	((SuiDesigner$FileItem*)self)->loadSubtree = (void*)SuiDesigner$FileItem$loadSubtree;
	((SuiDesigner$FileItem*)self)->printTree = (void*)SuiDesigner$FileItem$printTree;
}

// init function

void SuiDesigner$FileItem_init(SuiDesigner$FileItem *self, void *pOwner){
    Vtable_SuiDesigner$FileItem_init(&_vtable_SuiDesigner$FileItem);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$FileItem;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$FileItem_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$FileItem * SuiDesigner$FileItem_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$FileItem *self = calloc(1, sizeof(SuiDesigner$FileItem));
	
    SuiDesigner$FileItem_init(self, pOwner);
    return self;
}


// class members
Orc$List*  SuiDesigner$FileItem$getSubDirectoryChildren(Orc$List **  __outRef__, SuiDesigner$FileItem *  self){
	if (!self->isDirectory) {
		return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
	}
	if (self->subDirectoryChildren == NULL) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  ret = (ret=NULL,urgc_init_var_class((void**)&ret, Orc$List_new(&ret) ));
		int  l = self->children->size(self->children) ;
		for (int  i = 0; i < l; i++) {
			SuiDesigner$FileItem *  kid = (SuiDesigner$FileItem * )self->children->get(self->children, i) ;
			if (kid && kid->isDirectory) {
				ret->add(ret, kid) ;
			}
		}
		return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, NULL) ; 
}


bool  SuiDesigner$FileItem$hasSubDirectory(SuiDesigner$FileItem *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmp = self->getSubDirectoryChildren((tmp = NULL,&tmp), self) ;
	return tmp != NULL && tmp->size(tmp)  > 0; 
}


void  SuiDesigner$FileItem$appendChild(SuiDesigner$FileItem *  self, SuiDesigner$FileItem*  fi){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(fi);

	fi->removeSelf(fi) ;
	self->children->add(self->children, fi) ;
	urgc_set_field_class(fi, (void * )offsetof(SuiDesigner$FileItem, parent) , self) ;
}


void  SuiDesigner$FileItem$removeChild(SuiDesigner$FileItem *  self, SuiDesigner$FileItem *  fi){
	if (fi->parent == self) {
		self->children->remove(self->children, fi) ;
		urgc_set_field_class(fi, (void * )offsetof(SuiDesigner$FileItem, parent) , NULL) ;
	}
}


void  SuiDesigner$FileItem$removeSelf(SuiDesigner$FileItem *  self){
	if (self->parent) {
		self->parent->removeChild(self->parent, self) ;
	}
}


void  SuiDesigner$FileItem$setPathByParentPathAndFilename(SuiDesigner$FileItem *  self, Orc$String*  parentPath, Orc$String*  filename){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(parentPath);
	URGC_REF_ARG_WITH_CLEANUP_CLASS(filename);

	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  path = (path=NULL,urgc_init_var_class((void**)&path, Orc$String$addString(Orc$String$add(Orc$String$clone(&tmpReturn_1, parentPath) , "/") , filename) ));
	self->setPath(self, path) ;
}


void  SuiDesigner$FileItem$setPath(SuiDesigner$FileItem *  self, Orc$String*  path){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(path);

	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$FileItem, path) , path) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$FileItem, filename) , Orc$Path_basename(&tmpReturn_1, path->str) ) ;
	self->isDirectory = Orc$Path_isDirectory(self->path->str) ;
}


void  SuiDesigner$FileItem$updatePathByParentPathAndSelfFilename(SuiDesigner$FileItem *  self){
	if (self->parent) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$FileItem, path) , Orc$String$addString(Orc$String$add(Orc$str(&tmpReturn_1, self->parent->path->str) , "/") , self->filename) ) ;
	}
}


void  SuiDesigner$FileItem$updatePathByParnetPathAndSelfFilename_subtree(SuiDesigner$FileItem *  self){
	self->updatePathByParentPathAndSelfFilename(self) ;
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiDesigner$FileItem *  fi = (SuiDesigner$FileItem * )self->children->get(self->children, i) ;
		fi->updatePathByParnetPathAndSelfFilename_subtree(fi) ;
	}
}


void  SuiDesigner$FileItem$loadSubtree(SuiDesigner$FileItem *  self){
	if (self->isDirectory) {
		self->children->clear(self->children) ;
		URGC_VAR_CLEANUP_CLASS Orc$List*  paths = Orc$Path_list((paths = NULL,&paths), self->path->str) ;
		int  l = paths->size(paths) ;
		for (int  i = 0; i < l; i++) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  kidPath = (kidPath=NULL,urgc_init_var_class((void**)&kidPath, (Orc$String* )paths->get(paths, i) ));
			URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  kid = (kid=NULL,urgc_init_var_class((void**)&kid, SuiDesigner$FileItem_new(&kid) ));
			kid->setPath(kid, kidPath) ;
			self->appendChild(self, kid) ;
			if (kid->isDirectory) {
				kid->loadSubtree(kid) ;
			}
		}
	}
}


void  SuiDesigner$FileItem$printTree(SuiDesigner$FileItem *  self, int  tab){
	for (int  i = 0; i < tab; i++) {
		printf("\t") ;
	}
	printf("%s :%s dir:%d kids:%d\n", self->path->str, self->filename->str, self->isDirectory, self->children->size(self->children) ) ;
	for (int  i = 0; i < self->children->size(self->children) ; i++) {
		SuiDesigner$FileItem *  fi = (SuiDesigner$FileItem * )self->children->get(self->children, i) ;
		fi->printTree(fi, tab + 1) ;
	}
}



SuiDesigner$FileItem*  SuiDesigner$FileItem_loadDirectoryTree(SuiDesigner$FileItem **  __outRef__, const char *  dir){
	URGC_VAR_CLEANUP_CLASS SuiDesigner$FileItem*  root = (root=NULL,urgc_init_var_class((void**)&root, SuiDesigner$FileItem_new(&root) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	root->setPath(root, Orc$str(&tmpReturn_1, dir) ) ;
	root->loadSubtree(root) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, root) ; 
}



