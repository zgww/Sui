
#include "ModelLoader_orc.h" 

#include <stdio.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "./Obj3d_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/SplitterView_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "./Mesh_orc.h"
#include "./FboView_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"


// static struct 


// static function declaration


struct aiMaterialProperty *  Sgl$assimp_getMaterialPropByName(struct aiMaterial *  matl, const char *  name){
	for (int  j = 0; j < matl->mNumProperties; j++) {
		struct aiMaterialProperty *  prop = matl->mProperties[j];
		if (strcmp(prop->mKey.data, name)  == 0) {
			return prop; 
		}
	}
	return NULL; 
}

const char *  Sgl$assimp_getMaterialName(struct aiMaterial *  matl){
	struct aiMaterialProperty *  prop = Sgl$assimp_getMaterialPropByName(matl, "?mat.name") ;
	if (prop) {
		struct aiString *  s = (struct aiString * )prop->mData;
		return s->data; 
	}
	return NULL; 
}


//vtable instance
Vtable_Sgl$AssimpLoader _vtable_Sgl$AssimpLoader;

// init meta

void Sgl$AssimpLoader_initMeta(Vtable_Sgl$AssimpLoader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$AssimpLoader, path), true, false, 1);
	orc_metaField_plainStruct(&pNext, "scene", sizeof(struct aiScene), offsetof(Sgl$AssimpLoader, scene), false, true, 1);
	orc_metaField_class(&pNext, "geometries", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$AssimpLoader, geometries), true, false, 1);

	orc_metaField_method(&pNext, "buildSglTree", offsetof(Sgl$AssimpLoader, buildSglTree));
	orc_metaField_method(&pNext, "buildGeometries", offsetof(Sgl$AssimpLoader, buildGeometries));
	orc_metaField_method(&pNext, "buildNode", offsetof(Sgl$AssimpLoader, buildNode));
	orc_metaField_method(&pNext, "showWindow", offsetof(Sgl$AssimpLoader, showWindow));
	orc_metaField_method(&pNext, "mkNodeTreeView", offsetof(Sgl$AssimpLoader, mkNodeTreeView));
	orc_metaField_method(&pNext, "load", offsetof(Sgl$AssimpLoader, load));
	orc_metaField_method(&pNext, "printScene", offsetof(Sgl$AssimpLoader, printScene));
	orc_metaField_method(&pNext, "printNode", offsetof(Sgl$AssimpLoader, printNode));
}


// vtable init


Vtable_Sgl$AssimpLoader* Vtable_Sgl$AssimpLoader_init(Vtable_Sgl$AssimpLoader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$AssimpLoader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$AssimpLoader_new;
    ((Vtable_Object*)pvt)->className = "Sgl$AssimpLoader";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$AssimpLoader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$AssimpLoader_fini(Sgl$AssimpLoader *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->path);
	urgc_fini_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->geometries);

}

// init fields function


void Sgl$AssimpLoader_init_fields(Sgl$AssimpLoader *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$AssimpLoader_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->path, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->geometries, Orc$List_new(&tmpNewOwner_1) );
    }
	((Object*)self)->dtor = (void*)Sgl$AssimpLoader$dtor;
	((Sgl$AssimpLoader*)self)->buildSglTree = (void*)Sgl$AssimpLoader$buildSglTree;
	((Sgl$AssimpLoader*)self)->buildGeometries = (void*)Sgl$AssimpLoader$buildGeometries;
	((Sgl$AssimpLoader*)self)->buildNode = (void*)Sgl$AssimpLoader$buildNode;
	((Sgl$AssimpLoader*)self)->showWindow = (void*)Sgl$AssimpLoader$showWindow;
	((Sgl$AssimpLoader*)self)->mkNodeTreeView = (void*)Sgl$AssimpLoader$mkNodeTreeView;
	((Sgl$AssimpLoader*)self)->load = (void*)Sgl$AssimpLoader$load;
	((Sgl$AssimpLoader*)self)->printScene = (void*)Sgl$AssimpLoader$printScene;
	((Sgl$AssimpLoader*)self)->printNode = (void*)Sgl$AssimpLoader$printNode;
}

// init function

void Sgl$AssimpLoader_init(Sgl$AssimpLoader *self, void *pOwner){
    Vtable_Sgl$AssimpLoader_init(&_vtable_Sgl$AssimpLoader);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$AssimpLoader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$AssimpLoader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$AssimpLoader * Sgl$AssimpLoader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$AssimpLoader *self = calloc(1, sizeof(Sgl$AssimpLoader));
	
    Sgl$AssimpLoader_init(self, pOwner);
    return self;
}


// class members
void  Sgl$AssimpLoader$dtor(Sgl$AssimpLoader *  self){
	if (self->scene) {
		aiReleaseImport(self->scene) ;
	}
}


Sgl$Obj3d*  Sgl$AssimpLoader$buildSglTree(Sgl$Obj3d **  __outRef__, Sgl$AssimpLoader *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, self->buildNode(&tmpReturn_1, self, NULL, self->scene->mRootNode, 0, 0) ) ; 
}


void  Sgl$AssimpLoader$buildGeometries(Sgl$AssimpLoader *  self){
	for (int  i = 0; i < self->scene->mNumMeshes; i++) {
		struct aiMesh *  mesh = self->scene->mMeshes[i];
	}
}


Sgl$Obj3d*  Sgl$AssimpLoader$buildNode(Sgl$Obj3d **  __outRef__, Sgl$AssimpLoader *  self, Sgl$Obj3d *  parent, struct aiNode *  node, int  idx, int  deep){
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  ret = NULL;
	if (node->mNumMeshes == 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&ret, Sgl$Obj3d_new(&tmpNewOwner_1) ) ;
	}
	else {
		URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  mesh = (mesh=NULL,urgc_init_var_class((void**)&mesh, Sgl$Mesh_new(&mesh) ));
		urgc_set_var_class(&ret, mesh) ;
	}
	if (parent) {
		((SuiCore$Node * )parent)->appendChild(parent, ret) ;
	}
	for (unsigned int  i = 0; i < node->mNumChildren; ++i) {
		URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_2 = NULL;
		self->buildNode(&tmpReturn_2, self, ret, node->mChildren[i], i, deep + 1) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


void  Sgl$AssimpLoader$showWindow(Sgl$AssimpLoader *  self){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_89_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->aiStretch(o) ;
			win->setRootView(win, o) ;
			URGC_VAR_CLEANUP_CLASS Sgl$FboView*  tmpReturn_3 = NULL;
			{
				Sgl$FboView*  __scopeVar_94_16 = Sgl$mkFboView(&tmpReturn_3, o, 0) , *o = __scopeVar_94_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_94_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_4 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_4, o, 0) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$SplitterView*  tmpReturn_5 = NULL;
			{
				SuiView$SplitterView*  __scopeVar_98_16 = SuiView$mkSplitterView(&tmpReturn_5, o, 0) , *o = __scopeVar_98_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_98_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_6 = NULL;
			{
				SuiView$ScrollArea*  __scopeVar_100_16 = SuiView$mkScrollArea(&tmpReturn_6, o, 0) , *o = __scopeVar_100_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_100_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_7 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_7, o, 0) ;
				SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
				(tmpThis_1 = ((SuiLayout$LayoutLinear * )o)->column(o) )->aiStretch(tmpThis_1) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_8 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_106_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_8, o, (long long )0) , *o = __scopeVar_106_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_106_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_9 = NULL;
					{
						SuiView$TextView*  __scopeVar_109_24 = SuiView$mkTextView(&tmpReturn_9, o, 0) , *o = __scopeVar_109_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_109_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_10 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_10, "元数据") , self->scene->mMetaData->mNumProperties) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mMetaData->mNumProperties; i++) {
					struct aiString *  key = self->scene->mMetaData->mKeys + i;
					struct aiMetadataEntry *  value = self->scene->mMetaData->mValues + i;
					char  valueStr[512];
					if (value->mType == AI_BOOL) {
						sprintf(valueStr, "%d", *((bool * )value->mData)) ;
					}
					else if (value->mType == AI_INT32) {
						sprintf(valueStr, "%d", *((int * )value->mData)) ;
					}
					else if (value->mType == AI_UINT32) {
						sprintf(valueStr, "%u", *((unsigned int * )value->mData)) ;
					}
					else if (value->mType == AI_INT64) {
						sprintf(valueStr, "%lld", *((long long * )value->mData)) ;
					}
					else if (value->mType == AI_AIVECTOR3D) {
						struct aiVector3D *  pv = (struct aiVector3D * )value->mData;
						sprintf(valueStr, "Vec3(%f,%f,%f)", pv->x, pv->y, pv->z) ;
					}
					else if (value->mType == AI_UINT64) {
						sprintf(valueStr, "%llu", *((unsigned long long * )value->mData)) ;
					}
					else if (value->mType == AI_FLOAT) {
						sprintf(valueStr, "%f", *((float * )value->mData)) ;
					}
					else if (value->mType == AI_DOUBLE) {
						sprintf(valueStr, "%f", *((double * )value->mData)) ;
					}
					else if (value->mType == AI_AISTRING) {
						struct aiString *  ais = (struct aiString * )value->mData;
						sprintf(valueStr, "%s", ais->data) ;
					}
					char  tmp[1024];
					sprintf(tmp, "%d %s =%s\n", i, key->data, valueStr) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_11 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_152_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_11, o, (long long )key) , *o = __scopeVar_152_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_152_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = true;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_12 = NULL;
						{
							SuiView$TextView*  __scopeVar_155_28 = SuiView$mkTextView(&tmpReturn_12, o, 0) , *o = __scopeVar_155_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_155_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_13 = NULL;
							o->setText(o, Orc$str(&tmpReturn_13, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_14 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_160_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_14, o, (long long )0) , *o = __scopeVar_160_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_160_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_15 = NULL;
					{
						SuiView$TextView*  __scopeVar_163_24 = SuiView$mkTextView(&tmpReturn_15, o, 0) , *o = __scopeVar_163_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_163_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_16 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_16, "材质") , self->scene->mNumMaterials) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumMaterials; i++) {
					struct aiMaterial *  e = self->scene->mMaterials[i];
					char  tmp[1024];
					sprintf(tmp, "%d %s numProperty=%d\n", i, Sgl$assimp_getMaterialName(e) , e->mNumProperties) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_17 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_175_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_17, o, (long long )e) , *o = __scopeVar_175_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_175_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = true;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_18 = NULL;
						{
							SuiView$TextView*  __scopeVar_178_28 = SuiView$mkTextView(&tmpReturn_18, o, 0) , *o = __scopeVar_178_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_178_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_19 = NULL;
							o->setText(o, Orc$str(&tmpReturn_19, tmp) ) ;
						}
					}
					for (int  j = 0; j < e->mNumProperties; j++) {
						struct aiMaterialProperty *  prop = e->mProperties[j];
						sprintf(tmp, "%3d %s semantic:%d, iddx:%d, dataLength:%d type:%d ", j, prop->mKey.data, prop->mSemantic, prop->mIndex, prop->mDataLength, prop->mType) ;
						if (prop->mType == aiPTI_Float) {
							sprintf(tmp, "%s%f", tmp, *((float * )prop->mData)) ;
						}
						else if (prop->mType == aiPTI_Double) {
							sprintf(tmp, "%s%f", tmp, *((double * )prop->mData)) ;
						}
						else if (prop->mType == aiPTI_Integer) {
							sprintf(tmp, "%s%d", tmp, *((int * )prop->mData)) ;
						}
						else if (prop->mType == aiPTI_String) {
							struct aiString *  s = (struct aiString * )prop->mData;
							sprintf(tmp, "%s%s", tmp, s->data) ;
						}
						URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_20 = NULL;
						{
							SuiView$TreeSelfCtrlView*  __scopeVar_199_28 = SuiView$mkTreeSelfCtrlView(&tmpReturn_20, o, (long long )e) , *o = __scopeVar_199_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_199_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->deep = 2;
							o->hasKids = false;
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_21 = NULL;
							{
								SuiView$TextView*  __scopeVar_202_32 = SuiView$mkTextView(&tmpReturn_21, o, 0) , *o = __scopeVar_202_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_202_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_22 = NULL;
								o->setText(o, Orc$str(&tmpReturn_22, tmp) ) ;
							}
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_23 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_208_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_23, o, (long long )0) , *o = __scopeVar_208_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_208_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_24 = NULL;
					{
						SuiView$TextView*  __scopeVar_211_24 = SuiView$mkTextView(&tmpReturn_24, o, 0) , *o = __scopeVar_211_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_211_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_25 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_25, "动画#") , self->scene->mNumAnimations) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumAnimations; i++) {
					struct aiAnimation *  anim = self->scene->mAnimations[i];
					char  tmp[1024];
					sprintf(tmp, "%s dura=%f, ticksPs:%f, channels:%d meshChannel:%d  morphChannel:%d\n", anim->mName.data, anim->mDuration, anim->mTicksPerSecond, anim->mNumChannels, anim->mNumMeshChannels, anim->mNumMorphMeshChannels) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_26 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_224_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_26, o, (long long )anim) , *o = __scopeVar_224_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_224_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_27 = NULL;
						{
							SuiView$TextView*  __scopeVar_227_28 = SuiView$mkTextView(&tmpReturn_27, o, 0) , *o = __scopeVar_227_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_227_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_28 = NULL;
							o->setText(o, Orc$str(&tmpReturn_28, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_29 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_232_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_29, o, (long long )0) , *o = __scopeVar_232_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_232_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_30 = NULL;
					{
						SuiView$TextView*  __scopeVar_235_24 = SuiView$mkTextView(&tmpReturn_30, o, 0) , *o = __scopeVar_235_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_235_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_31 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_31, "纹理") , self->scene->mNumTextures) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumTextures; i++) {
					struct aiTexture *  tex = self->scene->mTextures[i];
					char  tmp[1024];
					sprintf(tmp, "%s w=%d, h=%d, achFormatHint=%s\n", tex->mFilename.data, tex->mWidth, tex->mHeight, tex->achFormatHint) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_32 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_248_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_32, o, (long long )tex) , *o = __scopeVar_248_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_248_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_33 = NULL;
						{
							SuiView$TextView*  __scopeVar_251_28 = SuiView$mkTextView(&tmpReturn_33, o, 0) , *o = __scopeVar_251_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_251_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_34 = NULL;
							o->setText(o, Orc$str(&tmpReturn_34, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_35 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_256_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_35, o, (long long )0) , *o = __scopeVar_256_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_256_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_36 = NULL;
					{
						SuiView$TextView*  __scopeVar_259_24 = SuiView$mkTextView(&tmpReturn_36, o, 0) , *o = __scopeVar_259_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_259_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_37 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_37, "网格") , self->scene->mNumMeshes) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumMeshes; i++) {
					struct aiMesh *  e = self->scene->mMeshes[i];
					char  tmp[1024];
					sprintf(tmp, "%s type=%d vtx=%d face=%d bones=%d matlIdx=%d animMeshes=%d method=%d, aabb=%f,%f,%f; %f,%f,%f\n", e->mName.data, e->mPrimitiveTypes, e->mNumVertices, e->mNumFaces, e->mNumBones, e->mMaterialIndex, e->mNumAnimMeshes, e->mMethod, e->mAABB.mMin.x, e->mAABB.mMin.y, e->mAABB.mMin.z, e->mAABB.mMax.x, e->mAABB.mMax.y, e->mAABB.mMax.z) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_38 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_282_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_38, o, (long long )e) , *o = __scopeVar_282_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_282_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_39 = NULL;
						{
							SuiView$TextView*  __scopeVar_285_28 = SuiView$mkTextView(&tmpReturn_39, o, 0) , *o = __scopeVar_285_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_285_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_40 = NULL;
							o->setText(o, Orc$str(&tmpReturn_40, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_41 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_291_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_41, o, (long long )0) , *o = __scopeVar_291_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_291_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_42 = NULL;
					{
						SuiView$TextView*  __scopeVar_294_24 = SuiView$mkTextView(&tmpReturn_42, o, 0) , *o = __scopeVar_294_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_294_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_43 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_43, "灯光") , self->scene->mNumLights) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumLights; i++) {
					struct aiLight *  e = self->scene->mLights[i];
					char  tmp[1024];
					sprintf(tmp, "%s type=%d,%s pos=%f,%f,%f dir=%f,%f,%f up=%f,%f,%f atte=%f,%f,%f, cone=%f,%f size=%f,%f\n", e->mName.data, e->mType, e->mType == aiLightSource_DIRECTIONAL ? "dir" : e->mType == aiLightSource_POINT ? "point" : e->mType == aiLightSource_SPOT ? "sport" : e->mType == aiLightSource_AMBIENT ? "ambient" : e->mType == aiLightSource_AREA ? "area" : "undef", e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mDirection.x, e->mDirection.y, e->mDirection.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mAttenuationConstant, e->mAttenuationLinear, e->mAttenuationQuadratic, e->mAngleInnerCone, e->mAngleOuterCone, e->mSize.x, e->mSize.y) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_44 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_333_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_44, o, (long long )e) , *o = __scopeVar_333_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_333_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_45 = NULL;
						{
							SuiView$TextView*  __scopeVar_336_28 = SuiView$mkTextView(&tmpReturn_45, o, 0) , *o = __scopeVar_336_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_336_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_46 = NULL;
							o->setText(o, Orc$str(&tmpReturn_46, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_47 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_341_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_47, o, (long long )0) , *o = __scopeVar_341_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_341_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_48 = NULL;
					{
						SuiView$TextView*  __scopeVar_344_24 = SuiView$mkTextView(&tmpReturn_48, o, 0) , *o = __scopeVar_344_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_344_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_49 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_49, "相机") , self->scene->mNumCameras) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumCameras; i++) {
					struct aiCamera *  e = self->scene->mCameras[i];
					char  tmp[1024];
					sprintf(tmp, "\t%s pos=%f,%f,%f up=%f,%f,%f lookAt=%f,%f,%f fov=%f near=%f far=%f aspect=%f orthorWidth=%f\n", e->mName.data, e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mLookAt.x, e->mLookAt.y, e->mLookAt.z, e->mHorizontalFOV, e->mClipPlaneNear, e->mClipPlaneFar, e->mAspect, e->mOrthographicWidth) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_50 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_372_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_50, o, (long long )e) , *o = __scopeVar_372_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_372_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_51 = NULL;
						{
							SuiView$TextView*  __scopeVar_375_28 = SuiView$mkTextView(&tmpReturn_51, o, 0) , *o = __scopeVar_375_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_375_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_52 = NULL;
							o->setText(o, Orc$str(&tmpReturn_52, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_53 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_380_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_53, o, (long long )0) , *o = __scopeVar_380_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_380_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_54 = NULL;
					{
						SuiView$TextView*  __scopeVar_383_24 = SuiView$mkTextView(&tmpReturn_54, o, 0) , *o = __scopeVar_383_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_383_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_55 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_55, "骨架") , self->scene->mNumSkeletons) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumSkeletons; i++) {
					struct aiSkeleton *  e = self->scene->mSkeletons[i];
					char  tmp[1024];
					sprintf(tmp, "%s bone=%d\n", e->mName.data, e->mNumBones) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_56 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_394_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_56, o, (long long )e) , *o = __scopeVar_394_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_394_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_57 = NULL;
						{
							SuiView$TextView*  __scopeVar_397_28 = SuiView$mkTextView(&tmpReturn_57, o, 0) , *o = __scopeVar_397_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_397_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_58 = NULL;
							o->setText(o, Orc$str(&tmpReturn_58, tmp) ) ;
						}
					}
					for (int  j = 0; j < e->mNumBones; j++) {
						struct aiSkeletonBone *  bone = e->mBones[j];
						sprintf(tmp, "%2d numWeights=%d\n", j, bone->mNumnWeights) ;
						URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_59 = NULL;
						{
							SuiView$TreeSelfCtrlView*  __scopeVar_407_28 = SuiView$mkTreeSelfCtrlView(&tmpReturn_59, o, (long long )e) , *o = __scopeVar_407_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_407_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->deep = 2;
							o->hasKids = false;
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_60 = NULL;
							{
								SuiView$TextView*  __scopeVar_410_32 = SuiView$mkTextView(&tmpReturn_60, o, 0) , *o = __scopeVar_410_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_410_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_61 = NULL;
								o->setText(o, Orc$str(&tmpReturn_61, tmp) ) ;
							}
						}
						for (int  k = 0; k < bone->mNumnWeights; k++) {
							struct aiMesh *  mesh = bone->mMeshId;
							struct aiVertexWeight *  weight = bone->mWeights + k;
							sprintf(tmp, "%2d mesh=%s weight=%f vtxId=%d\n", k, mesh->mName.data, weight->mWeight, weight->mVertexId) ;
							URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_62 = NULL;
							{
								SuiView$TreeSelfCtrlView*  __scopeVar_418_32 = SuiView$mkTreeSelfCtrlView(&tmpReturn_62, o, (long long )e) , *o = __scopeVar_418_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_418_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								o->deep = 3;
								o->hasKids = false;
								URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_63 = NULL;
								{
									SuiView$TextView*  __scopeVar_421_36 = SuiView$mkTextView(&tmpReturn_63, o, 0) , *o = __scopeVar_421_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_421_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_64 = NULL;
									o->setText(o, Orc$str(&tmpReturn_64, tmp) ) ;
								}
							}
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_65 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_428_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_65, o, (long long )0) , *o = __scopeVar_428_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_428_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_66 = NULL;
					{
						SuiView$TextView*  __scopeVar_431_24 = SuiView$mkTextView(&tmpReturn_66, o, 0) , *o = __scopeVar_431_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_431_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_67 = NULL;
						o->setText(o, Orc$str(&tmpReturn_67, "节点") ) ;
					}
				}
				self->mkNodeTreeView(self, o, self->scene->mRootNode, 0, 1) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_68 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_69 = NULL;
		o->setTitle(o, Orc$String$replaceAll(&tmpReturn_68, Orc$str(&tmpReturn_69, "预览模型{0}") , "{0}", self->path->str) ->str) ;
		o->setSize(o, 800, 600) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  Sgl$AssimpLoader$mkNodeTreeView(Sgl$AssimpLoader *  self, SuiCore$Node *  o, struct aiNode *  node, int  idx, int  deep){
	URGC_VAR_CLEANUP_CLASS Orc$String*  meshIds = Orc$str((meshIds = NULL,&meshIds), "") ;
	for (int  i = 0; i < node->mNumMeshes; i++) {
		unsigned int  meshIndex = node->mMeshes[i];
		Orc$String$add(Orc$String$addi(meshIds, meshIndex) , ",") ;
	}
	char  tmp[1024];
	sprintf(tmp, "%4d %s nKids=%d, nMesh=%d meshIdxs=%s\n", idx, node->mName.data, node->mNumChildren, node->mNumMeshes, meshIds->str) ;
	URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_1 = NULL;
	{
		SuiView$TreeSelfCtrlView*  __scopeVar_457_8 = SuiView$mkTreeSelfCtrlView(&tmpReturn_1, o, (long long )node) , *o = __scopeVar_457_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_457_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->deep = deep;
		o->hasKids = node->mNumChildren > 0;
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
		{
			SuiView$TextView*  __scopeVar_460_12 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_460_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_460_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setText(o, Orc$str(&tmpReturn_3, tmp) ) ;
		}
	}
	for (unsigned int  i = 0; i < node->mNumChildren; ++i) {
		self->mkNodeTreeView(self, o, node->mChildren[i], i, deep + 1) ;
	}
}


void  Sgl$AssimpLoader$load(Sgl$AssimpLoader *  self, const char *  model_path){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$AssimpLoader, path) , Orc$str(&tmpReturn_1, model_path) ) ;
	struct aiScene *  scene = aiImportFile(model_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | 0) ;
	printf("assimp 加载模型:%s. scene:%p\n", model_path, scene) ;
	if (!scene) {
		const char *  err = aiGetErrorString() ;
		printf("assimp load %s fail. err:%s\n", model_path, err) ;
		return ; 
	}
	self->scene = scene;
	self->printScene(self) ;
}


void  Sgl$AssimpLoader$printScene(Sgl$AssimpLoader *  self){
	if (self->scene) {
		printf("---------------scene[%s; %s] flag:%d, anim:%d, tex:%d, mesh:%d, matl:%d light:%d, cam:%d, ske:%d---------------\n", self->path->str, self->scene->mName.data, self->scene->mFlags, self->scene->mNumAnimations, self->scene->mNumTextures, self->scene->mNumMeshes, self->scene->mNumMaterials, self->scene->mNumLights, self->scene->mNumCameras, self->scene->mNumSkeletons) ;
		printf("---------------animations---------------\n") ;
		for (int  i = 0; i < self->scene->mNumAnimations; i++) {
			struct aiAnimation *  anim = self->scene->mAnimations[i];
			printf("\t%s dura=%f, ticksPs:%f, channels:%d meshChannel:%d  morphChannel:%d\n", anim->mName.data, anim->mDuration, anim->mTicksPerSecond, anim->mNumChannels, anim->mNumMeshChannels, anim->mNumMorphMeshChannels) ;
		}
		printf("---------------textures---------------\n") ;
		for (int  i = 0; i < self->scene->mNumTextures; i++) {
			struct aiTexture *  tex = self->scene->mTextures[i];
			printf("\t%s w=%d, h=%d, achFormatHint=%s\n", tex->mFilename.data, tex->mWidth, tex->mHeight, tex->achFormatHint) ;
		}
		printf("---------------meshes---------------\n") ;
		for (int  i = 0; i < self->scene->mNumMeshes; i++) {
			struct aiMesh *  e = self->scene->mMeshes[i];
			printf("\t%s type=%d vtx=%d face=%d bones=%d matlIdx=%d animMeshes=%d method=%d, aabb=%f,%f,%f; %f,%f,%f\n", e->mName.data, e->mPrimitiveTypes, e->mNumVertices, e->mNumFaces, e->mNumBones, e->mMaterialIndex, e->mNumAnimMeshes, e->mMethod, e->mAABB.mMin.x, e->mAABB.mMin.y, e->mAABB.mMin.z, e->mAABB.mMax.x, e->mAABB.mMax.y, e->mAABB.mMax.z) ;
		}
		printf("---------------materials---------------\n") ;
		for (int  i = 0; i < self->scene->mNumMaterials; i++) {
			struct aiMaterial *  e = self->scene->mMaterials[i];
			printf("\t%d numProperty=%d\n", i, e->mNumProperties) ;
			for (int  j = 0; j < e->mNumProperties; j++) {
				struct aiMaterialProperty *  prop = e->mProperties[j];
				printf("\t\t%3d %s semantic:%d, iddx:%d, dataLength:%d type:%d ", j, prop->mKey.data, prop->mSemantic, prop->mIndex, prop->mDataLength, prop->mType) ;
				if (prop->mType == aiPTI_Float) {
					printf("%f", *((float * )prop->mData)) ;
				}
				else if (prop->mType == aiPTI_Double) {
					printf("%f", *((double * )prop->mData)) ;
				}
				else if (prop->mType == aiPTI_Integer) {
					printf("%d", *((int * )prop->mData)) ;
				}
				else if (prop->mType == aiPTI_String) {
					struct aiString *  s = (struct aiString * )prop->mData;
					printf("%s", s->data) ;
				}
				printf("\n") ;
			}
		}
		printf("---------------lights---------------\n") ;
		for (int  i = 0; i < self->scene->mNumLights; i++) {
			struct aiLight *  e = self->scene->mLights[i];
			printf("\t%s type=%d,%s pos=%f,%f,%f dir=%f,%f,%f up=%f,%f,%f atte=%f,%f,%f, cone=%f,%f size=%f,%f\n", e->mName.data, e->mType, e->mType == aiLightSource_DIRECTIONAL ? "dir" : e->mType == aiLightSource_POINT ? "point" : e->mType == aiLightSource_SPOT ? "sport" : e->mType == aiLightSource_AMBIENT ? "ambient" : e->mType == aiLightSource_AREA ? "area" : "undef", e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mDirection.x, e->mDirection.y, e->mDirection.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mAttenuationConstant, e->mAttenuationLinear, e->mAttenuationQuadratic, e->mAngleInnerCone, e->mAngleOuterCone, e->mSize.x, e->mSize.y) ;
		}
		printf("---------------cameras---------------\n") ;
		for (int  i = 0; i < self->scene->mNumCameras; i++) {
			struct aiCamera *  e = self->scene->mCameras[i];
			printf("\t%s pos=%f,%f,%f up=%f,%f,%f lookAt=%f,%f,%f fov=%f near=%f far=%f aspect=%f orthorWidth=%f\n", e->mName.data, e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mLookAt.x, e->mLookAt.y, e->mLookAt.z, e->mHorizontalFOV, e->mClipPlaneNear, e->mClipPlaneFar, e->mAspect, e->mOrthographicWidth) ;
		}
		printf("---------------skeletons---------------\n") ;
		for (int  i = 0; i < self->scene->mNumSkeletons; i++) {
			struct aiSkeleton *  e = self->scene->mSkeletons[i];
			printf("\t%s bone=%d\n", e->mName.data, e->mNumBones) ;
			for (int  j = 0; j < e->mNumBones; j++) {
				struct aiSkeletonBone *  bone = e->mBones[j];
				printf("\t\t%2d numWeights=%d\n", j, bone->mNumnWeights) ;
				for (int  k = 0; k < bone->mNumnWeights; k++) {
					struct aiMesh *  mesh = bone->mMeshId;
					struct aiVertexWeight *  weight = bone->mWeights + k;
					printf("\t\t\t%2d mesh=%s weight=%f vtxId=%d\n", k, mesh->mName.data, weight->mWeight, weight->mVertexId) ;
				}
			}
		}
		printf("------------------nodes-----------------\n") ;
		self->printNode(self, self->scene->mRootNode, 0, 1) ;
	}
}


void  Sgl$AssimpLoader$printNode(Sgl$AssimpLoader *  self, struct aiNode *  node, int  idx, int  tabCount){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tab = Orc$str((tab = NULL,&tab), "") ;
	Orc$String$fillCount(tab, "\t", tabCount) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  meshIds = Orc$str((meshIds = NULL,&meshIds), "") ;
	for (int  i = 0; i < node->mNumMeshes; i++) {
		unsigned int  meshIndex = node->mMeshes[i];
		Orc$String$add(Orc$String$addi(meshIds, meshIndex) , ",") ;
	}
	printf("%s%4d %s[nKids=%d, nMesh=%d;%s]\n", tab->str, idx, node->mName.data, node->mNumChildren, node->mNumMeshes, meshIds->str) ;
	for (unsigned int  i = 0; i < node->mNumChildren; ++i) {
		self->printNode(self, node->mChildren[i], i, tabCount + 1) ;
	}
}




//vtable instance
Vtable_Sgl$ModelLoader _vtable_Sgl$ModelLoader;

// init meta

void Sgl$ModelLoader_initMeta(Vtable_Sgl$ModelLoader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "vertices", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, vertices), true, false, 1);
	orc_metaField_class(&pNext, "normals", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, normals), true, false, 1);
	orc_metaField_class(&pNext, "texCoords", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, texCoords), true, false, 1);
	orc_metaField_class(&pNext, "faces", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$ModelLoader, faces), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$ModelLoader, path), true, false, 1);
	orc_metaField_class(&pNext, "mesh", ((Vtable_Object*)Vtable_Sgl$Mesh_init(0)), offsetof(Sgl$ModelLoader, mesh), true, false, 1);

	orc_metaField_method(&pNext, "setPath", offsetof(Sgl$ModelLoader, setPath));
	orc_metaField_method(&pNext, "_load", offsetof(Sgl$ModelLoader, _load));
	orc_metaField_method(&pNext, "buildGeometry", offsetof(Sgl$ModelLoader, buildGeometry));
}


// vtable init


Vtable_Sgl$ModelLoader* Vtable_Sgl$ModelLoader_init(Vtable_Sgl$ModelLoader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$ModelLoader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$ModelLoader_new;
    ((Vtable_Object*)pvt)->className = "Sgl$ModelLoader";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$ModelLoader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$ModelLoader_fini(Sgl$ModelLoader *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->vertices);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->normals);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->texCoords);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->faces);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->path);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->mesh);

}

// init fields function


void Sgl$ModelLoader_init_fields(Sgl$ModelLoader *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$ModelLoader_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->vertices, Sgl$Buffer_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->normals, Sgl$Buffer_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->texCoords, Sgl$Buffer_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->faces, Sgl$Buffer_new(&tmpNewOwner_4) );
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->path, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Mesh*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->mesh, Sgl$Mesh_new(&tmpNewOwner_5) );
    }
	((Sgl$ModelLoader*)self)->setPath = (void*)Sgl$ModelLoader$setPath;
	((Sgl$ModelLoader*)self)->_load = (void*)Sgl$ModelLoader$_load;
	((Sgl$ModelLoader*)self)->buildGeometry = (void*)Sgl$ModelLoader$buildGeometry;
}

// init function

void Sgl$ModelLoader_init(Sgl$ModelLoader *self, void *pOwner){
    Vtable_Sgl$ModelLoader_init(&_vtable_Sgl$ModelLoader);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$ModelLoader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$ModelLoader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$ModelLoader * Sgl$ModelLoader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$ModelLoader *self = calloc(1, sizeof(Sgl$ModelLoader));
	
    Sgl$ModelLoader_init(self, pOwner);
    return self;
}


// class members
void  Sgl$ModelLoader$setPath(Sgl$ModelLoader *  self, Orc$String*  path){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(path);

	urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, path) , path) ;
	if (path) {
		self->_load(self) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpReturn_1 = NULL;
		urgc_set_field_class(self->mesh, (void * )offsetof(Sgl$Mesh, geometry) , self->buildGeometry(&tmpReturn_1, self) ) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
		{
			Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_2) ;
			
		
			o->load(o, "../asset/basic.matl.json") ;
			urgc_set_field_class(self->mesh, (void * )offsetof(Sgl$Mesh, material) , o) ;
		}
		((SuiCore$Node * )self)->appendChild(self, self->mesh) ;
	}
}


Sgl$Geometry*  Sgl$ModelLoader$buildGeometry(Sgl$Geometry **  __outRef__, Sgl$ModelLoader *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  geo = (geo=NULL,urgc_init_var_class((void**)&geo, Sgl$Geometry_new(&geo) ));
	if (self->vertices->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		vbo->elementCount = 3;
		vbo->arrayBuffer(vbo, self->vertices) ;
		geo->setAttr(geo, "position", vbo) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("\tload %s:%s\n", "position", Sgl$Buffer$toFloatString(&tmpReturn_1, self->vertices) ->str) ;
	}
	if (self->normals->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		vbo->elementCount = 3;
		vbo->arrayBuffer(vbo, self->normals) ;
		geo->setAttr(geo, "normal", vbo) ;
	}
	if (self->texCoords->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  vbo = (vbo=NULL,urgc_init_var_class((void**)&vbo, Sgl$Vbo_new(&vbo) ));
		vbo->elementCount = 2;
		vbo->arrayBuffer(vbo, self->texCoords) ;
		geo->setAttr(geo, "texCoord", vbo) ;
	}
	if (self->faces->size > 0) {
		URGC_VAR_CLEANUP_CLASS Sgl$Vbo*  tmpNewOwner_2 = NULL;
		urgc_set_field_class(geo, (void * )offsetof(Sgl$Geometry, ibo) , Sgl$Vbo_new(&tmpNewOwner_2) ) ;
		geo->ibo->elementBuffer(geo->ibo, self->faces) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		printf("\tload face:%s\n", Sgl$Buffer$toIntString(&tmpReturn_3, self->faces) ->str) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, geo) ; 
}



void  Sgl$test_AssimpLoader(){
	URGC_VAR_CLEANUP_CLASS Sgl$AssimpLoader*  l = (l=NULL,urgc_init_var_class((void**)&l, Sgl$AssimpLoader_new(&l) ));
	l->load(l, "spider.obj") ;
	l->showWindow(l) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  root = l->buildSglTree((root = NULL,&root), l) ;
	SuiCore$printNodeTree(root, 0) ;
}



