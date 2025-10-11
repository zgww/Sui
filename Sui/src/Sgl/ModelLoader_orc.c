
#include "ModelLoader_orc.h" 

#include <stdio.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "./Obj3d_orc.h"
#include "./Mesh_orc.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Geometry_orc.h"
#include "./Material_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$AssimpLoader _vtable_Sgl$AssimpLoader;

// init meta

void Sgl$AssimpLoader_initMeta(Vtable_Sgl$AssimpLoader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$AssimpLoader, path), true, false, 1);
	orc_metaField_plainStruct(&pNext, "scene", sizeof(struct aiScene), offsetof(Sgl$AssimpLoader, scene), false, true, 1);

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
	l->load(l, "spider.fbx") ;
}



