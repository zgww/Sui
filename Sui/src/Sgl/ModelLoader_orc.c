
#include "ModelLoader_orc.h" 

#include <stdio.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Path_orc.h"
#include "./Obj3d_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Sui/View/TreeView_orc.h"
#include "../Sui/View/Drag_orc.h"
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
#include "../SuiDesigner/Insp_orc.h"


// static struct 
typedef struct tagSgl$__Block_371_21 Sgl$__Block_371_21;

typedef struct tagSgl$__Closure_380_36 Sgl$__Closure_380_36;

typedef struct tagSgl$__Closure_383_31 Sgl$__Closure_383_31;



struct tagSgl$__Block_371_21 {
	Sgl$AssimpLoader*  self ;
};





struct tagSgl$__Closure_380_36 {
	void  (*invoke)(Sgl$__Closure_380_36 *  self, SuiView$Drag *  d);
	Vtable_Object *  vtable ;
	Sgl$__Block_371_21*  __var___Block_371_21 ;
};





struct tagSgl$__Closure_383_31 {
	void  (*invoke)(Sgl$__Closure_383_31 *  self, Sgl$FboView *  fboView);
	Vtable_Object *  vtable ;
	Sgl$__Block_371_21*  __var___Block_371_21 ;
};





// static function declaration
static void  __finiBlock___Block_371_21(Sgl$__Block_371_21 *  self);
static void  __fn___Closure_380_36(Sgl$__Closure_380_36 *  self, SuiView$Drag *  d);
static void  __fini___Closure_380_36(Sgl$__Closure_380_36 *  self);
static Sgl$__Closure_380_36*  __make___Closure_380_36(Sgl$__Closure_380_36 **  __outRef__, Sgl$__Block_371_21 *  __var___Block_371_21);
static void  __fn___Closure_383_31(Sgl$__Closure_383_31 *  self, Sgl$FboView *  fboView);
static void  __fini___Closure_383_31(Sgl$__Closure_383_31 *  self);
static Sgl$__Closure_383_31*  __make___Closure_383_31(Sgl$__Closure_383_31 **  __outRef__, Sgl$__Block_371_21 *  __var___Block_371_21);


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
	orc_metaField_class(&pNext, "rootObj3d", ((Vtable_Object*)Vtable_Sgl$Obj3d_init(0)), offsetof(Sgl$AssimpLoader, rootObj3d), true, false, 1);
	orc_metaField_class(&pNext, "materials", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$AssimpLoader, materials), true, false, 1);
	orc_metaField_class(&pNext, "mergedMaterials", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$AssimpLoader, mergedMaterials), true, false, 1);
	orc_metaField_class(&pNext, "geometries", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$AssimpLoader, geometries), true, false, 1);

	orc_metaField_method(&pNext, "buildSglTree", offsetof(Sgl$AssimpLoader, buildSglTree));
	orc_metaField_method(&pNext, "buildMaterials", offsetof(Sgl$AssimpLoader, buildMaterials));
	orc_metaField_method(&pNext, "buildGeometries", offsetof(Sgl$AssimpLoader, buildGeometries));
	orc_metaField_method(&pNext, "buildNode", offsetof(Sgl$AssimpLoader, buildNode));
	orc_metaField_method(&pNext, "drawFboView", offsetof(Sgl$AssimpLoader, drawFboView));
	orc_metaField_method(&pNext, "onDragFboView", offsetof(Sgl$AssimpLoader, onDragFboView));
	orc_metaField_method(&pNext, "reactMetaData", offsetof(Sgl$AssimpLoader, reactMetaData));
	orc_metaField_method(&pNext, "loadMaterialPropertyValueToString", offsetof(Sgl$AssimpLoader, loadMaterialPropertyValueToString));
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
	urgc_fini_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->rootObj3d);
	urgc_fini_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->materials);
	urgc_fini_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->mergedMaterials);
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
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->rootObj3d, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->materials, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->mergedMaterials, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->geometries, Orc$List_new(&tmpNewOwner_2) );
    }
	((Object*)self)->dtor = (void*)Sgl$AssimpLoader$dtor;
	((Sgl$AssimpLoader*)self)->buildSglTree = (void*)Sgl$AssimpLoader$buildSglTree;
	((Sgl$AssimpLoader*)self)->buildMaterials = (void*)Sgl$AssimpLoader$buildMaterials;
	((Sgl$AssimpLoader*)self)->buildGeometries = (void*)Sgl$AssimpLoader$buildGeometries;
	((Sgl$AssimpLoader*)self)->buildNode = (void*)Sgl$AssimpLoader$buildNode;
	((Sgl$AssimpLoader*)self)->drawFboView = (void*)Sgl$AssimpLoader$drawFboView;
	((Sgl$AssimpLoader*)self)->onDragFboView = (void*)Sgl$AssimpLoader$onDragFboView;
	((Sgl$AssimpLoader*)self)->reactMetaData = (void*)Sgl$AssimpLoader$reactMetaData;
	((Sgl$AssimpLoader*)self)->loadMaterialPropertyValueToString = (void*)Sgl$AssimpLoader$loadMaterialPropertyValueToString;
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
	self->buildGeometries(self) ;
	self->buildMaterials(self) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$AssimpLoader, rootObj3d) , self->buildNode(&tmpReturn_1, self, NULL, self->scene->mRootNode, 0, 0) ) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, self->rootObj3d) ; 
}


void  Sgl$AssimpLoader$buildMaterials(Sgl$AssimpLoader *  self){
	self->materials->clear(self->materials) ;
	for (int  i = 0; i < self->scene->mNumMaterials; i++) {
		struct aiMaterial *  aimtl = self->scene->mMaterials[i];
		URGC_VAR_CLEANUP_CLASS Sgl$Material*  matl = (matl=NULL,urgc_init_var_class((void**)&matl, Sgl$Material_new(&matl) ));
		matl->load(matl, "../asset/blinn-phong.matl.json") ;
		self->materials->add(self->materials, matl) ;
		SuiCore$Rgbaf clrDiffuse = SuiCore$mkRgbaf0() ;
		SuiCore$Rgbaf clrEmissive = SuiCore$mkRgbaf0() ;
		SuiCore$Rgbaf clrAmbient = SuiCore$mkRgbaf0() ;
		SuiCore$Rgbaf clrSpecular = SuiCore$mkRgbaf0() ;
		SuiCore$Rgbaf clrTransparent = SuiCore$mkRgbaf0() ;
		SuiCore$Rgbaf clrReflective = SuiCore$mkRgbaf0() ;
		int  shadingModel = 0;
		float  matShinpercent = 0.0;
		float  matShininess = 0.0;
		float  matRoughnessFactor = 0.0;
		float  matTransparencyfactor = 0.0;
		float  matOpacity = 0.0;
		float  matReflectivity = 0.0;
		float  matBumpscaling = 0.0;
		float  matDisplacementscaling = 0.0;
		URGC_VAR_CLEANUP_CLASS Orc$String*  texFile = Orc$str((texFile = NULL,&texFile), "") ;
		float  texUvTrafo = 0.0;
		int  texUvwSrc = 0;
		aiGetMaterialColor(aimtl, "$clr.diffuse", 0, 0, (struct aiColor4D * )&clrDiffuse) ;
		aiGetMaterialColor(aimtl, "$clr.emissive", 0, 0, (struct aiColor4D * )&clrEmissive) ;
		aiGetMaterialColor(aimtl, "$clr.ambient", 0, 0, (struct aiColor4D * )&clrAmbient) ;
		aiGetMaterialColor(aimtl, "$clr.specular", 0, 0, (struct aiColor4D * )&clrSpecular) ;
		aiGetMaterialColor(aimtl, "$clr.transparent", 0, 0, (struct aiColor4D * )&clrTransparent) ;
		aiGetMaterialColor(aimtl, "$clr.reflective", 0, 0, (struct aiColor4D * )&clrReflective) ;
		aiGetMaterialInteger(aimtl, "$mat.shadingm", 0, 0, &shadingModel) ;
		aiGetMaterialFloat(aimtl, "$mat.shinpercent", 0, 0, &matShinpercent) ;
		aiGetMaterialFloat(aimtl, "$mat.shininess", 0, 0, &matShininess) ;
		aiGetMaterialFloat(aimtl, "$mat.roughnessFactor", 0, 0, &matRoughnessFactor) ;
		aiGetMaterialFloat(aimtl, "$mat.transparencyfactor", 0, 0, &matTransparencyfactor) ;
		aiGetMaterialFloat(aimtl, "$mat.opacity", 0, 0, &matOpacity) ;
		aiGetMaterialFloat(aimtl, "$mat.reflectivity", 0, 0, &matReflectivity) ;
		aiGetMaterialFloat(aimtl, "$mat.bumpscaling", 0, 0, &matBumpscaling) ;
		aiGetMaterialFloat(aimtl, "$mat.displacementscaling", 0, 0, &matDisplacementscaling) ;
		struct aiString aiTexFile;
		aiTexFile.data[0] = 0;
		if (AI_SUCCESS == aiGetMaterialString(aimtl, "$tex.file", 1, 0, &aiTexFile) ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_var_class(&texFile, Orc$str(&tmpReturn_1, aiTexFile.data) ) ;
		}
		if (Orc$String$notEmpty(texFile) ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  actualPath = Orc$Path_resolveRelativeFromFile((actualPath = NULL,&actualPath), texFile->str, self->path->str) ;
			matl->setUniformTex2dByPath(matl, "tex", actualPath->str) ;
		}
	}
}


void  Sgl$AssimpLoader$buildGeometries(Sgl$AssimpLoader *  self){
	self->geometries->clear(self->geometries) ;
	for (int  i = 0; i < self->scene->mNumMeshes; i++) {
		struct aiMesh *  mesh = self->scene->mMeshes[i];
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  vertices = (vertices=NULL,urgc_init_var_class((void**)&vertices, Sgl$Buffer_new(&vertices) ));
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  normals = (normals=NULL,urgc_init_var_class((void**)&normals, Sgl$Buffer_new(&normals) ));
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  faces = (faces=NULL,urgc_init_var_class((void**)&faces, Sgl$Buffer_new(&faces) ));
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  colors = (colors=NULL,urgc_init_var_class((void**)&colors, Sgl$Buffer_new(&colors) ));
		float  scale = 1.0;
		for (int  i = 0; i < mesh->mNumVertices; i++) {
			SuiCore$Vec3 v3;
			v3.x = mesh->mVertices[i].x / scale;
			v3.y = mesh->mVertices[i].y / scale;
			v3.z = mesh->mVertices[i].z / scale;
			struct aiVector3D *  aiUvs = mesh->mTextureCoords[0];
			if (aiUvs != NULL) {
				Sgl$Buffer$appendFloat2(uvs, aiUvs[i].x, aiUvs[i].y) ;
			}
			struct aiColor4D *  aiColors = mesh->mColors[0];
			if (aiColors != NULL) {
				Sgl$Buffer$appendFloat4(colors, aiColors[i].r, aiColors[i].g, aiColors[i].b, aiColors[i].a) ;
			}
			SuiCore$Vec3 n;
			n.x = mesh->mNormals[i].x;
			n.y = mesh->mNormals[i].y;
			n.z = mesh->mNormals[i].z;
			Sgl$Buffer$appendVec3(vertices, v3) ;
			Sgl$Buffer$appendVec3(normals, v3) ;
		}
		for (unsigned int  i = 0; i < mesh->mNumFaces; i++) {
			struct aiFace *  face = mesh->mFaces + i;
			for (unsigned int  j = 0; j < face->mNumIndices; j++) {
				int  idx = face->mIndices[j];
				Sgl$Buffer$appendInt(faces, idx) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  g = (g=NULL,urgc_init_var_class((void**)&g, Sgl$Geometry_new(&g) ));
		g->setAttrByBuffer(g, "position", vertices, 3) ;
		g->setAttrByBuffer(g, "normal", normals, 3) ;
		g->setAttrByBuffer(g, "color", colors, 4) ;
		g->setAttrByBuffer(g, "uv", uvs, 2) ;
		g->setIboByBuffer(g, faces) ;
		self->geometries->add(self->geometries, g) ;
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
		if (node->mNumMeshes > 0) {
			int  idx = node->mMeshes[0];
			Sgl$Geometry *  geom = (Sgl$Geometry * )self->geometries->get(self->geometries, idx) ;
			urgc_set_field_class(mesh, (void * )offsetof(Sgl$Mesh, geometry) , geom) ;
			struct aiMesh *  aimesh = self->scene->mMeshes[idx];
			Sgl$Material *  matl = self->materials->get(self->materials, aimesh->mMaterialIndex) ;
			if (self->mergedMaterials) {
				matl = self->mergedMaterials->get(self->mergedMaterials, aimesh->mMaterialIndex) ;
			}
			urgc_set_field_class(mesh, (void * )offsetof(Sgl$Mesh, material) , matl) ;
		}
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


void  Sgl$AssimpLoader$drawFboView(Sgl$AssimpLoader *  self, Sgl$FboView *  fboView){
	if (self->rootObj3d) {
		self->rootObj3d->draw(self->rootObj3d, fboView->drawCtx) ;
	}
}


void  Sgl$AssimpLoader$onDragFboView(Sgl$AssimpLoader *  self, SuiView$Drag *  d){
	if (d->isDragging) {
		if (self->rootObj3d) {
			self->rootObj3d->rotation.y += d->deltaPos.x * 0.01;
			self->rootObj3d->updateWorldTransformAndSubtree(self->rootObj3d) ;
			printf("旋转模型\n") ;
		}
	}
}


void  Sgl$AssimpLoader$reactMetaData(Sgl$AssimpLoader *  self, SuiCore$Node *  o, struct aiMetadata *  mMetaData, int  deep){
	for (int  i = 0; i < mMetaData->mNumProperties; i++) {
		struct aiString *  key = mMetaData->mKeys + i;
		struct aiMetadataEntry *  value = mMetaData->mValues + i;
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
		URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_1 = NULL;
		{
			SuiView$TreeSelfCtrlView*  __scopeVar_325_12 = SuiView$mkTreeSelfCtrlView(&tmpReturn_1, o, ((long long )mMetaData) * 1000 + (long long )key) , *o = __scopeVar_325_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_325_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->deep = deep;
			o->hasKids = true;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
			{
				SuiView$TextView*  __scopeVar_328_16 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_328_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_328_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				o->setText(o, Orc$str(&tmpReturn_3, tmp) ) ;
			}
		}
	}
}


Orc$String*  Sgl$AssimpLoader$loadMaterialPropertyValueToString(Orc$String **  __outRef__, Sgl$AssimpLoader *  self, struct aiMaterialProperty *  prop){
	char  tmp[512];
	tmp[0] = 0;
	if (prop->mType == aiPTI_Float) {
		for (int  i = 0; i < prop->mDataLength / 4; i++) {
			sprintf(tmp, "%s %f", tmp, *(((float * )prop->mData) + i)) ;
		}
	}
	else if (prop->mType == aiPTI_Double) {
		for (int  i = 0; i < prop->mDataLength / 8; i++) {
			sprintf(tmp, "%s %f", tmp, *(((double * )prop->mData)) + i) ;
		}
	}
	else if (prop->mType == aiPTI_Integer) {
		for (int  i = 0; i < prop->mDataLength / 4; i++) {
			sprintf(tmp, "%s %d", tmp, *(((int * )prop->mData)) + i) ;
		}
	}
	else if (prop->mType == aiPTI_String) {
		struct aiString *  s = (struct aiString * )prop->mData;
		sprintf(tmp, "%s%s", tmp, s->data) ;
	}
	else if (prop->mType == aiPTI_Buffer) {
		sprintf(tmp, "ints:") ;
		for (int  i = 0; i < prop->mDataLength / 4; i++) {
			sprintf(tmp, "%s %d", tmp, *(((int * )prop->mData)) + i) ;
		}
		sprintf(tmp, "%s floats:", tmp) ;
		for (int  i = 0; i < prop->mDataLength / 4; i++) {
			sprintf(tmp, "%s %f", tmp, *(((float * )prop->mData)) + i) ;
		}
	}
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}


void  Sgl$AssimpLoader$showWindow(Sgl$AssimpLoader *  self){
	URGC_VAR_CLEANUP Sgl$__Block_371_21*  __var___Block_371_21 = (__var___Block_371_21=NULL,urgc_init_var((void**)&__var___Block_371_21, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_371_21) , __finiBlock___Block_371_21) ));
	urgc_set_field_class(__var___Block_371_21, (void * )offsetof(Sgl$__Block_371_21, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_374_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->aiStretch(o) ;
			win->setRootView(win, o) ;
			URGC_VAR_CLEANUP_CLASS Sgl$FboView*  tmpReturn_3 = NULL;
			{
				Sgl$FboView*  __scopeVar_379_16 = Sgl$mkFboView(&tmpReturn_3, o, 0) , *o = __scopeVar_379_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_379_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP Sgl$__Closure_380_36*  tmpReturn_4 = NULL;
				urgc_set_field(o->drag, (void * )offsetof(SuiView$Drag, onDrag) , __make___Closure_380_36(&tmpReturn_4, __var___Block_371_21) ) ;
				URGC_VAR_CLEANUP Sgl$__Closure_383_31*  tmpReturn_5 = NULL;
				urgc_set_field(o, (void * )offsetof(Sgl$FboView, cbDraw) , __make___Closure_383_31(&tmpReturn_5, __var___Block_371_21) ) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$SplitterView*  tmpReturn_7 = NULL;
			{
				SuiView$SplitterView*  __scopeVar_389_16 = SuiView$mkSplitterView(&tmpReturn_7, o, 0) , *o = __scopeVar_389_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_389_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_8 = NULL;
			{
				SuiView$ScrollArea*  __scopeVar_391_16 = SuiView$mkScrollArea(&tmpReturn_8, o, 0) , *o = __scopeVar_391_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_391_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_9 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_9, o, 0) ;
				SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
				(tmpThis_1 = ((SuiLayout$LayoutLinear * )o)->column(o) )->aiStretch(tmpThis_1) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_10 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_397_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_10, o, (long long )0) , *o = __scopeVar_397_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_397_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_11 = NULL;
					{
						SuiView$TextView*  __scopeVar_400_24 = SuiView$mkTextView(&tmpReturn_11, o, 0) , *o = __scopeVar_400_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_400_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_12 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_12, "元数据") , self->scene->mMetaData->mNumProperties) ) ;
					}
				}
				self->reactMetaData(self, o, self->scene->mMetaData, 1) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_13 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_405_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_13, o, (long long )0) , *o = __scopeVar_405_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_405_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_14 = NULL;
					{
						SuiView$TextView*  __scopeVar_408_24 = SuiView$mkTextView(&tmpReturn_14, o, 0) , *o = __scopeVar_408_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_408_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_15 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_15, "材质") , self->scene->mNumMaterials) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumMaterials; i++) {
					struct aiMaterial *  e = self->scene->mMaterials[i];
					char  tmp[1024];
					sprintf(tmp, "%d %s numProperty=%d\n", i, Sgl$assimp_getMaterialName(e) , e->mNumProperties) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_16 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_420_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_16, o, (long long )e) , *o = __scopeVar_420_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_420_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = true;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_17 = NULL;
						{
							SuiView$TextView*  __scopeVar_423_28 = SuiView$mkTextView(&tmpReturn_17, o, 0) , *o = __scopeVar_423_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_423_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_18 = NULL;
							o->setText(o, Orc$str(&tmpReturn_18, tmp) ) ;
						}
					}
					for (int  j = 0; j < e->mNumProperties; j++) {
						struct aiMaterialProperty *  prop = e->mProperties[j];
						URGC_VAR_CLEANUP_CLASS Orc$String*  value = self->loadMaterialPropertyValueToString((value = NULL,&value), self, prop) ;
						sprintf(tmp, "%3d %s semantic:%d, iddx:%d, dataLength:%d type:%d %s", j, prop->mKey.data, prop->mSemantic, prop->mIndex, prop->mDataLength, prop->mType, value->str) ;
						URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_19 = NULL;
						{
							SuiView$TreeSelfCtrlView*  __scopeVar_445_28 = SuiView$mkTreeSelfCtrlView(&tmpReturn_19, o, (long long )e) , *o = __scopeVar_445_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_445_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->deep = 2;
							o->hasKids = false;
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_20 = NULL;
							{
								SuiView$TextView*  __scopeVar_448_32 = SuiView$mkTextView(&tmpReturn_20, o, 0) , *o = __scopeVar_448_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_448_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_21 = NULL;
								o->setText(o, Orc$str(&tmpReturn_21, tmp) ) ;
							}
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_22 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_454_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_22, o, (long long )0) , *o = __scopeVar_454_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_454_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_23 = NULL;
					{
						SuiView$TextView*  __scopeVar_457_24 = SuiView$mkTextView(&tmpReturn_23, o, 0) , *o = __scopeVar_457_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_457_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_24 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_24, "动画#") , self->scene->mNumAnimations) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumAnimations; i++) {
					struct aiAnimation *  anim = self->scene->mAnimations[i];
					char  tmp[1024];
					sprintf(tmp, "%s dura=%f, ticksPs:%f, channels:%d meshChannel:%d  morphChannel:%d\n", anim->mName.data, anim->mDuration, anim->mTicksPerSecond, anim->mNumChannels, anim->mNumMeshChannels, anim->mNumMorphMeshChannels) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_25 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_470_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_25, o, (long long )anim) , *o = __scopeVar_470_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_470_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_26 = NULL;
						{
							SuiView$TextView*  __scopeVar_473_28 = SuiView$mkTextView(&tmpReturn_26, o, 0) , *o = __scopeVar_473_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_473_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_27 = NULL;
							o->setText(o, Orc$str(&tmpReturn_27, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_28 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_478_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_28, o, (long long )0) , *o = __scopeVar_478_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_478_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_29 = NULL;
					{
						SuiView$TextView*  __scopeVar_481_24 = SuiView$mkTextView(&tmpReturn_29, o, 0) , *o = __scopeVar_481_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_481_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_30 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_30, "纹理") , self->scene->mNumTextures) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumTextures; i++) {
					struct aiTexture *  tex = self->scene->mTextures[i];
					char  tmp[1024];
					sprintf(tmp, "%s w=%d, h=%d, achFormatHint=%s\n", tex->mFilename.data, tex->mWidth, tex->mHeight, tex->achFormatHint) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_31 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_494_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_31, o, (long long )tex) , *o = __scopeVar_494_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_494_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_32 = NULL;
						{
							SuiView$TextView*  __scopeVar_497_28 = SuiView$mkTextView(&tmpReturn_32, o, 0) , *o = __scopeVar_497_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_497_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_33 = NULL;
							o->setText(o, Orc$str(&tmpReturn_33, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_34 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_502_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_34, o, (long long )0) , *o = __scopeVar_502_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_502_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_35 = NULL;
					{
						SuiView$TextView*  __scopeVar_505_24 = SuiView$mkTextView(&tmpReturn_35, o, 0) , *o = __scopeVar_505_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_505_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_36 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_36, "网格") , self->scene->mNumMeshes) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumMeshes; i++) {
					struct aiMesh *  e = self->scene->mMeshes[i];
					char  tmp[1024];
					sprintf(tmp, "%s type=%d vtx=%d face=%d bones=%d matlIdx=%d animMeshes=%d method=%d, aabb=%f,%f,%f; %f,%f,%f\n", e->mName.data, e->mPrimitiveTypes, e->mNumVertices, e->mNumFaces, e->mNumBones, e->mMaterialIndex, e->mNumAnimMeshes, e->mMethod, e->mAABB.mMin.x, e->mAABB.mMin.y, e->mAABB.mMin.z, e->mAABB.mMax.x, e->mAABB.mMax.y, e->mAABB.mMax.z) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_37 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_528_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_37, o, (long long )e) , *o = __scopeVar_528_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_528_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_38 = NULL;
						{
							SuiView$TextView*  __scopeVar_531_28 = SuiView$mkTextView(&tmpReturn_38, o, 0) , *o = __scopeVar_531_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_531_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_39 = NULL;
							o->setText(o, Orc$str(&tmpReturn_39, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_40 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_537_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_40, o, (long long )0) , *o = __scopeVar_537_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_537_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_41 = NULL;
					{
						SuiView$TextView*  __scopeVar_540_24 = SuiView$mkTextView(&tmpReturn_41, o, 0) , *o = __scopeVar_540_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_540_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_42 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_42, "灯光") , self->scene->mNumLights) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumLights; i++) {
					struct aiLight *  e = self->scene->mLights[i];
					char  tmp[1024];
					sprintf(tmp, "%s type=%d,%s pos=%f,%f,%f dir=%f,%f,%f up=%f,%f,%f atte=%f,%f,%f, cone=%f,%f size=%f,%f\n", e->mName.data, e->mType, e->mType == aiLightSource_DIRECTIONAL ? "dir" : e->mType == aiLightSource_POINT ? "point" : e->mType == aiLightSource_SPOT ? "sport" : e->mType == aiLightSource_AMBIENT ? "ambient" : e->mType == aiLightSource_AREA ? "area" : "undef", e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mDirection.x, e->mDirection.y, e->mDirection.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mAttenuationConstant, e->mAttenuationLinear, e->mAttenuationQuadratic, e->mAngleInnerCone, e->mAngleOuterCone, e->mSize.x, e->mSize.y) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_43 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_579_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_43, o, (long long )e) , *o = __scopeVar_579_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_579_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_44 = NULL;
						{
							SuiView$TextView*  __scopeVar_582_28 = SuiView$mkTextView(&tmpReturn_44, o, 0) , *o = __scopeVar_582_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_582_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_45 = NULL;
							o->setText(o, Orc$str(&tmpReturn_45, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_46 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_587_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_46, o, (long long )0) , *o = __scopeVar_587_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_587_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_47 = NULL;
					{
						SuiView$TextView*  __scopeVar_590_24 = SuiView$mkTextView(&tmpReturn_47, o, 0) , *o = __scopeVar_590_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_590_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_48 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_48, "相机") , self->scene->mNumCameras) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumCameras; i++) {
					struct aiCamera *  e = self->scene->mCameras[i];
					char  tmp[1024];
					sprintf(tmp, "\t%s pos=%f,%f,%f up=%f,%f,%f lookAt=%f,%f,%f fov=%f near=%f far=%f aspect=%f orthorWidth=%f\n", e->mName.data, e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mLookAt.x, e->mLookAt.y, e->mLookAt.z, e->mHorizontalFOV, e->mClipPlaneNear, e->mClipPlaneFar, e->mAspect, e->mOrthographicWidth) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_49 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_618_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_49, o, (long long )e) , *o = __scopeVar_618_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_618_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_50 = NULL;
						{
							SuiView$TextView*  __scopeVar_621_28 = SuiView$mkTextView(&tmpReturn_50, o, 0) , *o = __scopeVar_621_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_621_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_51 = NULL;
							o->setText(o, Orc$str(&tmpReturn_51, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_52 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_626_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_52, o, (long long )0) , *o = __scopeVar_626_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_626_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_53 = NULL;
					{
						SuiView$TextView*  __scopeVar_629_24 = SuiView$mkTextView(&tmpReturn_53, o, 0) , *o = __scopeVar_629_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_629_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_54 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_54, "骨架") , self->scene->mNumSkeletons) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumSkeletons; i++) {
					struct aiSkeleton *  e = self->scene->mSkeletons[i];
					char  tmp[1024];
					sprintf(tmp, "%s bone=%d\n", e->mName.data, e->mNumBones) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_55 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_640_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_55, o, (long long )e) , *o = __scopeVar_640_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_640_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_56 = NULL;
						{
							SuiView$TextView*  __scopeVar_643_28 = SuiView$mkTextView(&tmpReturn_56, o, 0) , *o = __scopeVar_643_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_643_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_57 = NULL;
							o->setText(o, Orc$str(&tmpReturn_57, tmp) ) ;
						}
					}
					for (int  j = 0; j < e->mNumBones; j++) {
						struct aiSkeletonBone *  bone = e->mBones[j];
						sprintf(tmp, "%2d numWeights=%d\n", j, bone->mNumnWeights) ;
						URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_58 = NULL;
						{
							SuiView$TreeSelfCtrlView*  __scopeVar_653_28 = SuiView$mkTreeSelfCtrlView(&tmpReturn_58, o, (long long )e) , *o = __scopeVar_653_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_653_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->deep = 2;
							o->hasKids = false;
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_59 = NULL;
							{
								SuiView$TextView*  __scopeVar_656_32 = SuiView$mkTextView(&tmpReturn_59, o, 0) , *o = __scopeVar_656_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_656_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_60 = NULL;
								o->setText(o, Orc$str(&tmpReturn_60, tmp) ) ;
							}
						}
						for (int  k = 0; k < bone->mNumnWeights; k++) {
							struct aiMesh *  mesh = bone->mMeshId;
							struct aiVertexWeight *  weight = bone->mWeights + k;
							sprintf(tmp, "%2d mesh=%s weight=%f vtxId=%d\n", k, mesh->mName.data, weight->mWeight, weight->mVertexId) ;
							URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_61 = NULL;
							{
								SuiView$TreeSelfCtrlView*  __scopeVar_664_32 = SuiView$mkTreeSelfCtrlView(&tmpReturn_61, o, (long long )e) , *o = __scopeVar_664_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_664_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								o->deep = 3;
								o->hasKids = false;
								URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_62 = NULL;
								{
									SuiView$TextView*  __scopeVar_667_36 = SuiView$mkTextView(&tmpReturn_62, o, 0) , *o = __scopeVar_667_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_667_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_63 = NULL;
									o->setText(o, Orc$str(&tmpReturn_63, tmp) ) ;
								}
							}
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_64 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_674_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_64, o, (long long )0) , *o = __scopeVar_674_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_674_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_65 = NULL;
					{
						SuiView$TextView*  __scopeVar_677_24 = SuiView$mkTextView(&tmpReturn_65, o, 0) , *o = __scopeVar_677_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_677_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_66 = NULL;
						o->setText(o, Orc$str(&tmpReturn_66, "节点") ) ;
					}
				}
				self->mkNodeTreeView(self, o, self->scene->mRootNode, 0, 1) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_67 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_68 = NULL;
		o->setTitle(o, Orc$String$replaceAll(&tmpReturn_67, Orc$str(&tmpReturn_68, "预览模型{0}") , "{0}", self->path->str) ->str) ;
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
		SuiView$TreeSelfCtrlView*  __scopeVar_703_8 = SuiView$mkTreeSelfCtrlView(&tmpReturn_1, o, (long long )node) , *o = __scopeVar_703_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_703_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->deep = deep;
		o->hasKids = node->mNumChildren > 0 || node->mMetaData != NULL;
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
		{
			SuiView$TextView*  __scopeVar_706_12 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_706_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_706_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setText(o, Orc$str(&tmpReturn_3, tmp) ) ;
		}
	}
	if (node->mMetaData) {
		URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_4 = NULL;
		{
			SuiView$TreeSelfCtrlView*  __scopeVar_711_12 = SuiView$mkTreeSelfCtrlView(&tmpReturn_4, o, (long long )0) , *o = __scopeVar_711_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_711_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->deep = deep + 1;
			o->hasKids = true;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_5 = NULL;
			{
				SuiView$TextView*  __scopeVar_714_16 = SuiView$mkTextView(&tmpReturn_5, o, 0) , *o = __scopeVar_714_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_714_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
				o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_6, "元数据") , self->scene->mMetaData->mNumProperties) ) ;
			}
		}
		self->reactMetaData(self, o, node->mMetaData, deep + 2) ;
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
				URGC_VAR_CLEANUP_CLASS Orc$String*  value = self->loadMaterialPropertyValueToString((value = NULL,&value), self, prop) ;
				printf("\t\t%3d %s semantic:%d, iddx:%d, dataLength:%d type:%d %s", j, prop->mKey.data, prop->mSemantic, prop->mIndex, prop->mDataLength, prop->mType, value->str) ;
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



static void  __finiBlock___Block_371_21(Sgl$__Block_371_21 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_371_21, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_380_36(Sgl$__Closure_380_36 *  self, SuiView$Drag *  d){
	self->__var___Block_371_21->self->onDragFboView(self->__var___Block_371_21->self, d) ;
}

static void  __fini___Closure_380_36(Sgl$__Closure_380_36 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_380_36, __var___Block_371_21) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_380_36*  __make___Closure_380_36(Sgl$__Closure_380_36 **  __outRef__, Sgl$__Block_371_21 *  __var___Block_371_21){
	URGC_VAR_CLEANUP Sgl$__Closure_380_36*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_380_36) , __fini___Closure_380_36) ));
	self->invoke = __fn___Closure_380_36;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_380_36, __var___Block_371_21) , __var___Block_371_21) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_383_31(Sgl$__Closure_383_31 *  self, Sgl$FboView *  fboView){
	self->__var___Block_371_21->self->drawFboView(self->__var___Block_371_21->self, fboView) ;
}

static void  __fini___Closure_383_31(Sgl$__Closure_383_31 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_383_31, __var___Block_371_21) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_383_31*  __make___Closure_383_31(Sgl$__Closure_383_31 **  __outRef__, Sgl$__Block_371_21 *  __var___Block_371_21){
	URGC_VAR_CLEANUP Sgl$__Closure_383_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_383_31) , __fini___Closure_383_31) ));
	self->invoke = __fn___Closure_383_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_383_31, __var___Block_371_21) , __var___Block_371_21) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
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
	orc_metaField_class(&pNext, "modelRoot", ((Vtable_Object*)Vtable_Sgl$Obj3d_init(0)), offsetof(Sgl$ModelLoader, modelRoot), true, false, 1);
	orc_metaField_class(&pNext, "materialPaths", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$ModelLoader, materialPaths), true, false, 1);
	orc_metaField_class(&pNext, "_materialSlots", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$ModelLoader, _materialSlots), true, false, 1);
	orc_metaField_class(&pNext, "loader", ((Vtable_Object*)Vtable_Sgl$AssimpLoader_init(0)), offsetof(Sgl$ModelLoader, loader), true, false, 1);

	orc_metaField_method(&pNext, "insp", offsetof(Sgl$ModelLoader, insp));
	orc_metaField_method(&pNext, "setMaterialPaths", offsetof(Sgl$ModelLoader, setMaterialPaths));
	orc_metaField_method(&pNext, "updateMaterialSlots", offsetof(Sgl$ModelLoader, updateMaterialSlots));
	orc_metaField_method(&pNext, "generateModelRoot", offsetof(Sgl$ModelLoader, generateModelRoot));
	orc_metaField_method(&pNext, "setPath", offsetof(Sgl$ModelLoader, setPath));
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
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->modelRoot);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->materialPaths);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->_materialSlots);
	urgc_fini_field_class(self, (void**)&((Sgl$ModelLoader*)self)->loader);

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
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->modelRoot, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->materialPaths, Orc$List_new(&tmpNewOwner_5) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_6 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->_materialSlots, Orc$List_new(&tmpNewOwner_6) );
	urgc_set_field_class(self, (void**)&((Sgl$ModelLoader*)self)->loader, NULL);
    }
	((Sgl$ModelLoader*)self)->insp = (void*)Sgl$ModelLoader$insp;
	((Object*)self)->ctor = (void*)Sgl$ModelLoader$ctor;
	((Sgl$ModelLoader*)self)->setMaterialPaths = (void*)Sgl$ModelLoader$setMaterialPaths;
	((Sgl$ModelLoader*)self)->updateMaterialSlots = (void*)Sgl$ModelLoader$updateMaterialSlots;
	((SuiCore$Node*)self)->onMounted = (void*)Sgl$ModelLoader$onMounted;
	((Sgl$ModelLoader*)self)->generateModelRoot = (void*)Sgl$ModelLoader$generateModelRoot;
	((Sgl$ModelLoader*)self)->setPath = (void*)Sgl$ModelLoader$setPath;
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
void  Sgl$ModelLoader$insp(Sgl$ModelLoader *  self, SuiDesigner$Insp*  insp){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(insp);

	URGC_VAR_CLEANUP_CLASS SuiDesigner$InspAttrMaterialList*  tmpNewOwner_1 = NULL;
	{
		SuiDesigner$InspAttrMaterialList*  o = SuiDesigner$InspAttrMaterialList_new(&tmpNewOwner_1) ;
		
	
		((SuiDesigner$InspAttr * )o)->bind(o, insp, "materialPaths", NULL) ;
	}
}


void  Sgl$ModelLoader$ctor(Sgl$ModelLoader *  self){
	SuiCore$Listener$ctor(self) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	self->materialPaths->add(self->materialPaths, Orc$str(&tmpReturn_1, "../asset/basic.matl.json") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	self->materialPaths->add(self->materialPaths, Orc$str(&tmpReturn_2, "../asset/basic.matl.json") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	self->materialPaths->add(self->materialPaths, Orc$str(&tmpReturn_3, "../asset/basic.matl.json") ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
	self->materialPaths->add(self->materialPaths, Orc$str(&tmpReturn_4, "../asset/basic.matl.json") ) ;
}


void  Sgl$ModelLoader$setMaterialPaths(Sgl$ModelLoader *  self, Orc$List *  list){
	urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, materialPaths) , list) ;
	self->updateMaterialSlots(self) ;
	if (self->modelRoot != NULL) {
		self->generateModelRoot(self) ;
	}
}


void  Sgl$ModelLoader$updateMaterialSlots(Sgl$ModelLoader *  self){
	self->_materialSlots->clear(self->_materialSlots) ;
	if (self->loader) {
		for (int  i = 0; i < self->loader->materials->size(self->loader->materials) ; i++) {
			Orc$String *  path = self->materialPaths->get(self->materialPaths, i) ;
			if (path) {
				URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_1 = NULL;
				{
					Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_1) ;
					
				
					o->load(o, path->str) ;
					self->_materialSlots->set(self->_materialSlots, i, o) ;
				}
			}
			else {
				Sgl$Material *  matl = (Sgl$Material * )self->loader->materials->get(self->loader->materials, i) ;
				self->_materialSlots->set(self->_materialSlots, i, matl) ;
			}
		}
	}
}


void  Sgl$ModelLoader$onMounted(Sgl$ModelLoader *  self){
	self->updateMaterialSlots(self) ;
	if (self->loader) {
		urgc_set_field_class(self->loader, (void * )offsetof(Sgl$AssimpLoader, mergedMaterials) , self->_materialSlots) ;
	}
	if (self->modelRoot == NULL) {
		self->generateModelRoot(self) ;
	}
}


void  Sgl$ModelLoader$generateModelRoot(Sgl$ModelLoader *  self){
	if (self->modelRoot) {
		((SuiCore$Node * )self->modelRoot)->removeSelf(self->modelRoot) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, modelRoot) , self->loader->buildSglTree(&tmpReturn_1, self->loader) ) ;
	((SuiCore$Node * )self)->appendChild(self, self->modelRoot) ;
	SuiCore$printNodeTree(self, 0) ;
}


void  Sgl$ModelLoader$setPath(Sgl$ModelLoader *  self, Orc$String*  path){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(path);

	urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, path) , path) ;
	if (path) {
		URGC_VAR_CLEANUP_CLASS Sgl$AssimpLoader*  l = (l=NULL,urgc_init_var_class((void**)&l, Sgl$AssimpLoader_new(&l) ));
		self->loader->load(self->loader, self->path->str) ;
		if (self->modelRoot) {
			self->generateModelRoot(self) ;
		}
	}
}



void  Sgl$test_AssimpLoader(){
	URGC_VAR_CLEANUP_CLASS Sgl$AssimpLoader*  l = (l=NULL,urgc_init_var_class((void**)&l, Sgl$AssimpLoader_new(&l) ));
	l->load(l, "spider.obj") ;
	l->showWindow(l) ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  mtls = (mtls=NULL,urgc_init_var_class((void**)&mtls, Orc$List_new(&mtls) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_1 = NULL;
	{
		Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_1) ;
		
	
		o->load(o, "../asset/basic.matl.json") ;
		mtls->add(mtls, o) ;
		mtls->add(mtls, o) ;
		mtls->add(mtls, o) ;
		mtls->add(mtls, o) ;
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  root = l->buildSglTree((root = NULL,&root), l) ;
	SuiCore$printNodeTree(root, 0) ;
}



