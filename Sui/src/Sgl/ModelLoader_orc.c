
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
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "./Mesh_orc.h"
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

}

// init fields function


void Sgl$AssimpLoader_init_fields(Sgl$AssimpLoader *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)Sgl$AssimpLoader_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->path, NULL);
    }
	((Object*)self)->dtor = (void*)Sgl$AssimpLoader$dtor;
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


void  Sgl$AssimpLoader$showWindow(Sgl$AssimpLoader *  self){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpNewOwner_2 = NULL;
		{
			SuiView$ScrollArea*  o = SuiView$ScrollArea_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_52_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			win->setRootView(win, o) ;
			SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
			(tmpThis_1 = ((SuiLayout$LayoutLinear * )o)->column(o) )->aiStretch(tmpThis_1) ;
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_3 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_58_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_3, o, (long long )0) , *o = __scopeVar_58_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_58_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_4 = NULL;
				{
					SuiView$TextView*  __scopeVar_61_20 = SuiView$mkTextView(&tmpReturn_4, o, 0) , *o = __scopeVar_61_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_61_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_5, "材质") , self->scene->mNumMaterials) ) ;
				}
			}
			for (int  i = 0; i < self->scene->mNumMaterials; i++) {
				struct aiMaterial *  e = self->scene->mMaterials[i];
				char  tmp[1024];
				sprintf(tmp, "%d %s numProperty=%d\n", i, Sgl$assimp_getMaterialName(e) , e->mNumProperties) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_6 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_73_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_6, o, (long long )e) , *o = __scopeVar_73_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_73_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 1;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_7 = NULL;
					{
						SuiView$TextView*  __scopeVar_76_24 = SuiView$mkTextView(&tmpReturn_7, o, 0) , *o = __scopeVar_76_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_76_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_8 = NULL;
						o->setText(o, Orc$str(&tmpReturn_8, tmp) ) ;
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
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_9 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_97_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_9, o, (long long )e) , *o = __scopeVar_97_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_97_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 2;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_10 = NULL;
						{
							SuiView$TextView*  __scopeVar_100_28 = SuiView$mkTextView(&tmpReturn_10, o, 0) , *o = __scopeVar_100_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_100_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
							o->setText(o, Orc$str(&tmpReturn_11, tmp) ) ;
						}
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_12 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_106_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_12, o, (long long )0) , *o = __scopeVar_106_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_106_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_13 = NULL;
				{
					SuiView$TextView*  __scopeVar_109_20 = SuiView$mkTextView(&tmpReturn_13, o, 0) , *o = __scopeVar_109_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_109_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_14, "动画#") , self->scene->mNumAnimations) ) ;
				}
			}
			for (int  i = 0; i < self->scene->mNumAnimations; i++) {
				struct aiAnimation *  anim = self->scene->mAnimations[i];
				char  tmp[1024];
				sprintf(tmp, "%s dura=%f, ticksPs:%f, channels:%d meshChannel:%d  morphChannel:%d\n", anim->mName.data, anim->mDuration, anim->mTicksPerSecond, anim->mNumChannels, anim->mNumMeshChannels, anim->mNumMorphMeshChannels) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_15 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_122_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_15, o, (long long )anim) , *o = __scopeVar_122_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_122_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 1;
					o->hasKids = false;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_16 = NULL;
					{
						SuiView$TextView*  __scopeVar_125_24 = SuiView$mkTextView(&tmpReturn_16, o, 0) , *o = __scopeVar_125_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_125_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
						o->setText(o, Orc$str(&tmpReturn_17, tmp) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_18 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_130_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_18, o, (long long )0) , *o = __scopeVar_130_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_130_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_19 = NULL;
				{
					SuiView$TextView*  __scopeVar_133_20 = SuiView$mkTextView(&tmpReturn_19, o, 0) , *o = __scopeVar_133_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_133_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_20, "纹理") , self->scene->mNumTextures) ) ;
				}
			}
			for (int  i = 0; i < self->scene->mNumTextures; i++) {
				struct aiTexture *  tex = self->scene->mTextures[i];
				char  tmp[1024];
				sprintf(tmp, "%s w=%d, h=%d, achFormatHint=%s\n", tex->mFilename.data, tex->mWidth, tex->mHeight, tex->achFormatHint) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_21 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_146_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_21, o, (long long )tex) , *o = __scopeVar_146_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_146_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 1;
					o->hasKids = false;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_22 = NULL;
					{
						SuiView$TextView*  __scopeVar_149_24 = SuiView$mkTextView(&tmpReturn_22, o, 0) , *o = __scopeVar_149_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_149_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_23 = NULL;
						o->setText(o, Orc$str(&tmpReturn_23, tmp) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_24 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_154_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_24, o, (long long )0) , *o = __scopeVar_154_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_154_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_25 = NULL;
				{
					SuiView$TextView*  __scopeVar_157_20 = SuiView$mkTextView(&tmpReturn_25, o, 0) , *o = __scopeVar_157_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_157_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_26, "网格") , self->scene->mNumMeshes) ) ;
				}
			}
			for (int  i = 0; i < self->scene->mNumMeshes; i++) {
				struct aiMesh *  e = self->scene->mMeshes[i];
				char  tmp[1024];
				sprintf(tmp, "%s type=%d vtx=%d face=%d bones=%d matlIdx=%d animMeshes=%d method=%d, aabb=%f,%f,%f; %f,%f,%f\n", e->mName.data, e->mPrimitiveTypes, e->mNumVertices, e->mNumFaces, e->mNumBones, e->mMaterialIndex, e->mNumAnimMeshes, e->mMethod, e->mAABB.mMin.x, e->mAABB.mMin.y, e->mAABB.mMin.z, e->mAABB.mMax.x, e->mAABB.mMax.y, e->mAABB.mMax.z) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_27 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_180_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_27, o, (long long )e) , *o = __scopeVar_180_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_180_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 1;
					o->hasKids = false;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_28 = NULL;
					{
						SuiView$TextView*  __scopeVar_183_24 = SuiView$mkTextView(&tmpReturn_28, o, 0) , *o = __scopeVar_183_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_183_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_29 = NULL;
						o->setText(o, Orc$str(&tmpReturn_29, tmp) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_30 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_189_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_30, o, (long long )0) , *o = __scopeVar_189_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_189_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_31 = NULL;
				{
					SuiView$TextView*  __scopeVar_192_20 = SuiView$mkTextView(&tmpReturn_31, o, 0) , *o = __scopeVar_192_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_192_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_32 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_32, "灯光") , self->scene->mNumLights) ) ;
				}
			}
			for (int  i = 0; i < self->scene->mNumLights; i++) {
				struct aiLight *  e = self->scene->mLights[i];
				char  tmp[1024];
				sprintf(tmp, "%s type=%d,%s pos=%f,%f,%f dir=%f,%f,%f up=%f,%f,%f atte=%f,%f,%f, cone=%f,%f size=%f,%f\n", e->mName.data, e->mType, e->mType == aiLightSource_DIRECTIONAL ? "dir" : e->mType == aiLightSource_POINT ? "point" : e->mType == aiLightSource_SPOT ? "sport" : e->mType == aiLightSource_AMBIENT ? "ambient" : e->mType == aiLightSource_AREA ? "area" : "undef", e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mDirection.x, e->mDirection.y, e->mDirection.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mAttenuationConstant, e->mAttenuationLinear, e->mAttenuationQuadratic, e->mAngleInnerCone, e->mAngleOuterCone, e->mSize.x, e->mSize.y) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_33 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_231_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_33, o, (long long )e) , *o = __scopeVar_231_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_231_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 1;
					o->hasKids = false;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_34 = NULL;
					{
						SuiView$TextView*  __scopeVar_234_24 = SuiView$mkTextView(&tmpReturn_34, o, 0) , *o = __scopeVar_234_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_234_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_35 = NULL;
						o->setText(o, Orc$str(&tmpReturn_35, tmp) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_36 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_239_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_36, o, (long long )0) , *o = __scopeVar_239_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_239_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_37 = NULL;
				{
					SuiView$TextView*  __scopeVar_242_20 = SuiView$mkTextView(&tmpReturn_37, o, 0) , *o = __scopeVar_242_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_242_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_38 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_38, "相机") , self->scene->mNumCameras) ) ;
				}
			}
			for (int  i = 0; i < self->scene->mNumCameras; i++) {
				struct aiCamera *  e = self->scene->mCameras[i];
				char  tmp[1024];
				sprintf(tmp, "\t%s pos=%f,%f,%f up=%f,%f,%f lookAt=%f,%f,%f fov=%f near=%f far=%f aspect=%f orthorWidth=%f\n", e->mName.data, e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mLookAt.x, e->mLookAt.y, e->mLookAt.z, e->mHorizontalFOV, e->mClipPlaneNear, e->mClipPlaneFar, e->mAspect, e->mOrthographicWidth) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_39 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_270_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_39, o, (long long )e) , *o = __scopeVar_270_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_270_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 1;
					o->hasKids = false;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_40 = NULL;
					{
						SuiView$TextView*  __scopeVar_273_24 = SuiView$mkTextView(&tmpReturn_40, o, 0) , *o = __scopeVar_273_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_273_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_41 = NULL;
						o->setText(o, Orc$str(&tmpReturn_41, tmp) ) ;
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_42 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_278_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_42, o, (long long )0) , *o = __scopeVar_278_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_278_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_43 = NULL;
				{
					SuiView$TextView*  __scopeVar_281_20 = SuiView$mkTextView(&tmpReturn_43, o, 0) , *o = __scopeVar_281_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_281_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_44 = NULL;
					o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_44, "骨架") , self->scene->mNumSkeletons) ) ;
				}
			}
			for (int  i = 0; i < self->scene->mNumSkeletons; i++) {
				struct aiSkeleton *  e = self->scene->mSkeletons[i];
				char  tmp[1024];
				sprintf(tmp, "%s bone=%d\n", e->mName.data, e->mNumBones) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_45 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_292_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_45, o, (long long )e) , *o = __scopeVar_292_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_292_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 1;
					o->hasKids = false;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_46 = NULL;
					{
						SuiView$TextView*  __scopeVar_295_24 = SuiView$mkTextView(&tmpReturn_46, o, 0) , *o = __scopeVar_295_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_295_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_47 = NULL;
						o->setText(o, Orc$str(&tmpReturn_47, tmp) ) ;
					}
				}
				for (int  j = 0; j < e->mNumBones; j++) {
					struct aiSkeletonBone *  bone = e->mBones[j];
					sprintf(tmp, "%2d numWeights=%d\n", j, bone->mNumnWeights) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_48 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_305_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_48, o, (long long )e) , *o = __scopeVar_305_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_305_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 2;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_49 = NULL;
						{
							SuiView$TextView*  __scopeVar_308_28 = SuiView$mkTextView(&tmpReturn_49, o, 0) , *o = __scopeVar_308_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_308_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_50 = NULL;
							o->setText(o, Orc$str(&tmpReturn_50, tmp) ) ;
						}
					}
					for (int  k = 0; k < bone->mNumnWeights; k++) {
						struct aiMesh *  mesh = bone->mMeshId;
						struct aiVertexWeight *  weight = bone->mWeights + k;
						sprintf(tmp, "%2d mesh=%s weight=%f vtxId=%d\n", k, mesh->mName.data, weight->mWeight, weight->mVertexId) ;
						URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_51 = NULL;
						{
							SuiView$TreeSelfCtrlView*  __scopeVar_316_28 = SuiView$mkTreeSelfCtrlView(&tmpReturn_51, o, (long long )e) , *o = __scopeVar_316_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_316_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->deep = 3;
							o->hasKids = false;
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_52 = NULL;
							{
								SuiView$TextView*  __scopeVar_319_32 = SuiView$mkTextView(&tmpReturn_52, o, 0) , *o = __scopeVar_319_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_319_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_53 = NULL;
								o->setText(o, Orc$str(&tmpReturn_53, tmp) ) ;
							}
						}
					}
				}
			}
			URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_54 = NULL;
			{
				SuiView$TreeSelfCtrlView*  __scopeVar_326_16 = SuiView$mkTreeSelfCtrlView(&tmpReturn_54, o, (long long )0) , *o = __scopeVar_326_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_326_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->deep = 0;
				o->hasKids = true;
				URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_55 = NULL;
				{
					SuiView$TextView*  __scopeVar_329_20 = SuiView$mkTextView(&tmpReturn_55, o, 0) , *o = __scopeVar_329_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_329_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_56 = NULL;
					o->setText(o, Orc$str(&tmpReturn_56, "节点") ) ;
				}
			}
			self->mkNodeTreeView(self, o, self->scene->mRootNode, 0, 1) ;
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_57 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_58 = NULL;
		o->setTitle(o, Orc$String$replaceAll(&tmpReturn_57, Orc$str(&tmpReturn_58, "预览模型{0}") , "{0}", self->path->str) ->str) ;
		o->setSize(o, 800, 600) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}


void  Sgl$AssimpLoader$mkNodeTreeView(Sgl$AssimpLoader *  self, SuiCore$Node *  o, struct aiNode *  node, int  idx, int  deep){
	URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_1 = NULL;
	{
		SuiView$TreeSelfCtrlView*  __scopeVar_346_8 = SuiView$mkTreeSelfCtrlView(&tmpReturn_1, o, (long long )node) , *o = __scopeVar_346_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_346_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->deep = deep;
		o->hasKids = node->mNumChildren > 0;
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
		{
			SuiView$TextView*  __scopeVar_349_12 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_349_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_349_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setText(o, Orc$str(&tmpReturn_3, node->mName.data) ) ;
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
}



