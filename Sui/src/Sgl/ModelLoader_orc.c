
#include "ModelLoader_orc.h" 

#include <stdio.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "./Obj3d_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Node_orc.h"
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
#include "../SuiDesigner/Insp_orc.h"


// static struct 
typedef struct tagSgl$__Block_206_21 Sgl$__Block_206_21;

typedef struct tagSgl$__Closure_215_31 Sgl$__Closure_215_31;



struct tagSgl$__Block_206_21 {
	Sgl$AssimpLoader*  self ;
};





struct tagSgl$__Closure_215_31 {
	void  (*invoke)(Sgl$__Closure_215_31 *  self, Sgl$FboView *  fboView);
	Vtable_Object *  vtable ;
	Sgl$__Block_206_21*  __var___Block_206_21 ;
};





// static function declaration
static void  __finiBlock___Block_206_21(Sgl$__Block_206_21 *  self);
static void  __fn___Closure_215_31(Sgl$__Closure_215_31 *  self, Sgl$FboView *  fboView);
static void  __fini___Closure_215_31(Sgl$__Closure_215_31 *  self);
static Sgl$__Closure_215_31*  __make___Closure_215_31(Sgl$__Closure_215_31 **  __outRef__, Sgl$__Block_206_21 *  __var___Block_206_21);


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
	orc_metaField_class(&pNext, "geometries", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(Sgl$AssimpLoader, geometries), true, false, 1);

	orc_metaField_method(&pNext, "buildSglTree", offsetof(Sgl$AssimpLoader, buildSglTree));
	orc_metaField_method(&pNext, "buildGeometries", offsetof(Sgl$AssimpLoader, buildGeometries));
	orc_metaField_method(&pNext, "buildNode", offsetof(Sgl$AssimpLoader, buildNode));
	orc_metaField_method(&pNext, "drawFboView", offsetof(Sgl$AssimpLoader, drawFboView));
	orc_metaField_method(&pNext, "reactMetaData", offsetof(Sgl$AssimpLoader, reactMetaData));
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
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$AssimpLoader*)self)->geometries, Orc$List_new(&tmpNewOwner_2) );
    }
	((Object*)self)->dtor = (void*)Sgl$AssimpLoader$dtor;
	((Sgl$AssimpLoader*)self)->buildSglTree = (void*)Sgl$AssimpLoader$buildSglTree;
	((Sgl$AssimpLoader*)self)->buildGeometries = (void*)Sgl$AssimpLoader$buildGeometries;
	((Sgl$AssimpLoader*)self)->buildNode = (void*)Sgl$AssimpLoader$buildNode;
	((Sgl$AssimpLoader*)self)->drawFboView = (void*)Sgl$AssimpLoader$drawFboView;
	((Sgl$AssimpLoader*)self)->reactMetaData = (void*)Sgl$AssimpLoader$reactMetaData;
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
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$AssimpLoader, rootObj3d) , self->buildNode(&tmpReturn_1, self, NULL, self->scene->mRootNode, 0, 0) ) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, self->rootObj3d) ; 
}


void  Sgl$AssimpLoader$buildGeometries(Sgl$AssimpLoader *  self){
	self->geometries->clear(self->geometries) ;
	for (int  i = 0; i < self->scene->mNumMeshes; i++) {
		struct aiMesh *  mesh = self->scene->mMeshes[i];
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  vertices = (vertices=NULL,urgc_init_var_class((void**)&vertices, Sgl$Buffer_new(&vertices) ));
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  normals = (normals=NULL,urgc_init_var_class((void**)&normals, Sgl$Buffer_new(&normals) ));
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
		URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  faces = (faces=NULL,urgc_init_var_class((void**)&faces, Sgl$Buffer_new(&faces) ));
		float  scale = 1.0;
		for (int  i = 0; i < mesh->mNumVertices; i++) {
			SuiCore$Vec3 v3;
			v3.x = mesh->mVertices[i].x / scale;
			v3.y = mesh->mVertices[i].y / scale;
			v3.z = mesh->mVertices[i].z / scale;
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
			URGC_VAR_CLEANUP_CLASS Sgl$Material*  tmpNewOwner_2 = NULL;
			{
				Sgl$Material*  o = Sgl$Material_new(&tmpNewOwner_2) ;
				
			
				o->load(o, "../asset/basic.matl.json") ;
				urgc_set_field_class(mesh, (void * )offsetof(Sgl$Mesh, material) , o) ;
			}
		}
		urgc_set_var_class(&ret, mesh) ;
	}
	if (parent) {
		((SuiCore$Node * )parent)->appendChild(parent, ret) ;
	}
	for (unsigned int  i = 0; i < node->mNumChildren; ++i) {
		URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_3 = NULL;
		self->buildNode(&tmpReturn_3, self, ret, node->mChildren[i], i, deep + 1) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, ret) ; 
}


void  Sgl$AssimpLoader$drawFboView(Sgl$AssimpLoader *  self, Sgl$FboView *  fboView){
	if (self->rootObj3d) {
		self->rootObj3d->draw(self->rootObj3d, fboView->drawCtx) ;
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
			SuiView$TreeSelfCtrlView*  __scopeVar_195_12 = SuiView$mkTreeSelfCtrlView(&tmpReturn_1, o, ((long long )mMetaData) * 1000 + (long long )key) , *o = __scopeVar_195_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_195_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->deep = deep;
			o->hasKids = true;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
			{
				SuiView$TextView*  __scopeVar_198_16 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_198_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_198_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				o->setText(o, Orc$str(&tmpReturn_3, tmp) ) ;
			}
		}
	}
}


void  Sgl$AssimpLoader$showWindow(Sgl$AssimpLoader *  self){
	URGC_VAR_CLEANUP Sgl$__Block_206_21*  __var___Block_206_21 = (__var___Block_206_21=NULL,urgc_init_var((void**)&__var___Block_206_21, orc_alloc_and_set_deleter(sizeof(Sgl$__Block_206_21) , __finiBlock___Block_206_21) ));
	urgc_set_field_class(__var___Block_206_21, (void * )offsetof(Sgl$__Block_206_21, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_209_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->aiStretch(o) ;
			win->setRootView(win, o) ;
			URGC_VAR_CLEANUP_CLASS Sgl$FboView*  tmpReturn_3 = NULL;
			{
				Sgl$FboView*  __scopeVar_214_16 = Sgl$mkFboView(&tmpReturn_3, o, 0) , *o = __scopeVar_214_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_214_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP Sgl$__Closure_215_31*  tmpReturn_4 = NULL;
				urgc_set_field(o, (void * )offsetof(Sgl$FboView, cbDraw) , __make___Closure_215_31(&tmpReturn_4, __var___Block_206_21) ) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_5 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_5, o, 0) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$SplitterView*  tmpReturn_6 = NULL;
			{
				SuiView$SplitterView*  __scopeVar_221_16 = SuiView$mkSplitterView(&tmpReturn_6, o, 0) , *o = __scopeVar_221_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_221_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				
			}
			URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_7 = NULL;
			{
				SuiView$ScrollArea*  __scopeVar_223_16 = SuiView$mkScrollArea(&tmpReturn_7, o, 0) , *o = __scopeVar_223_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_223_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_8 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_8, o, 0) ;
				SuiLayout$LayoutLinear *  tmpThis_1 = NULL;
				(tmpThis_1 = ((SuiLayout$LayoutLinear * )o)->column(o) )->aiStretch(tmpThis_1) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_9 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_229_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_9, o, (long long )0) , *o = __scopeVar_229_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_229_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_10 = NULL;
					{
						SuiView$TextView*  __scopeVar_232_24 = SuiView$mkTextView(&tmpReturn_10, o, 0) , *o = __scopeVar_232_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_232_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_11 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_11, "元数据") , self->scene->mMetaData->mNumProperties) ) ;
					}
				}
				self->reactMetaData(self, o, self->scene->mMetaData, 1) ;
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_12 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_237_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_12, o, (long long )0) , *o = __scopeVar_237_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_237_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_13 = NULL;
					{
						SuiView$TextView*  __scopeVar_240_24 = SuiView$mkTextView(&tmpReturn_13, o, 0) , *o = __scopeVar_240_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_240_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_14 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_14, "材质") , self->scene->mNumMaterials) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumMaterials; i++) {
					struct aiMaterial *  e = self->scene->mMaterials[i];
					char  tmp[1024];
					sprintf(tmp, "%d %s numProperty=%d\n", i, Sgl$assimp_getMaterialName(e) , e->mNumProperties) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_15 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_252_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_15, o, (long long )e) , *o = __scopeVar_252_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_252_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = true;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_16 = NULL;
						{
							SuiView$TextView*  __scopeVar_255_28 = SuiView$mkTextView(&tmpReturn_16, o, 0) , *o = __scopeVar_255_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_255_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_17 = NULL;
							o->setText(o, Orc$str(&tmpReturn_17, tmp) ) ;
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
						URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_18 = NULL;
						{
							SuiView$TreeSelfCtrlView*  __scopeVar_276_28 = SuiView$mkTreeSelfCtrlView(&tmpReturn_18, o, (long long )e) , *o = __scopeVar_276_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_276_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->deep = 2;
							o->hasKids = false;
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_19 = NULL;
							{
								SuiView$TextView*  __scopeVar_279_32 = SuiView$mkTextView(&tmpReturn_19, o, 0) , *o = __scopeVar_279_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_279_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_20 = NULL;
								o->setText(o, Orc$str(&tmpReturn_20, tmp) ) ;
							}
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_21 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_285_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_21, o, (long long )0) , *o = __scopeVar_285_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_285_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_22 = NULL;
					{
						SuiView$TextView*  __scopeVar_288_24 = SuiView$mkTextView(&tmpReturn_22, o, 0) , *o = __scopeVar_288_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_288_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_23 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_23, "动画#") , self->scene->mNumAnimations) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumAnimations; i++) {
					struct aiAnimation *  anim = self->scene->mAnimations[i];
					char  tmp[1024];
					sprintf(tmp, "%s dura=%f, ticksPs:%f, channels:%d meshChannel:%d  morphChannel:%d\n", anim->mName.data, anim->mDuration, anim->mTicksPerSecond, anim->mNumChannels, anim->mNumMeshChannels, anim->mNumMorphMeshChannels) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_24 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_301_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_24, o, (long long )anim) , *o = __scopeVar_301_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_301_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_25 = NULL;
						{
							SuiView$TextView*  __scopeVar_304_28 = SuiView$mkTextView(&tmpReturn_25, o, 0) , *o = __scopeVar_304_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_304_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_26 = NULL;
							o->setText(o, Orc$str(&tmpReturn_26, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_27 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_309_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_27, o, (long long )0) , *o = __scopeVar_309_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_309_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_28 = NULL;
					{
						SuiView$TextView*  __scopeVar_312_24 = SuiView$mkTextView(&tmpReturn_28, o, 0) , *o = __scopeVar_312_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_312_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_29 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_29, "纹理") , self->scene->mNumTextures) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumTextures; i++) {
					struct aiTexture *  tex = self->scene->mTextures[i];
					char  tmp[1024];
					sprintf(tmp, "%s w=%d, h=%d, achFormatHint=%s\n", tex->mFilename.data, tex->mWidth, tex->mHeight, tex->achFormatHint) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_30 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_325_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_30, o, (long long )tex) , *o = __scopeVar_325_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_325_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_31 = NULL;
						{
							SuiView$TextView*  __scopeVar_328_28 = SuiView$mkTextView(&tmpReturn_31, o, 0) , *o = __scopeVar_328_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_328_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_32 = NULL;
							o->setText(o, Orc$str(&tmpReturn_32, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_33 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_333_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_33, o, (long long )0) , *o = __scopeVar_333_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_333_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_34 = NULL;
					{
						SuiView$TextView*  __scopeVar_336_24 = SuiView$mkTextView(&tmpReturn_34, o, 0) , *o = __scopeVar_336_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_336_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_35 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_35, "网格") , self->scene->mNumMeshes) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumMeshes; i++) {
					struct aiMesh *  e = self->scene->mMeshes[i];
					char  tmp[1024];
					sprintf(tmp, "%s type=%d vtx=%d face=%d bones=%d matlIdx=%d animMeshes=%d method=%d, aabb=%f,%f,%f; %f,%f,%f\n", e->mName.data, e->mPrimitiveTypes, e->mNumVertices, e->mNumFaces, e->mNumBones, e->mMaterialIndex, e->mNumAnimMeshes, e->mMethod, e->mAABB.mMin.x, e->mAABB.mMin.y, e->mAABB.mMin.z, e->mAABB.mMax.x, e->mAABB.mMax.y, e->mAABB.mMax.z) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_36 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_359_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_36, o, (long long )e) , *o = __scopeVar_359_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_359_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_37 = NULL;
						{
							SuiView$TextView*  __scopeVar_362_28 = SuiView$mkTextView(&tmpReturn_37, o, 0) , *o = __scopeVar_362_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_362_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_38 = NULL;
							o->setText(o, Orc$str(&tmpReturn_38, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_39 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_368_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_39, o, (long long )0) , *o = __scopeVar_368_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_368_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_40 = NULL;
					{
						SuiView$TextView*  __scopeVar_371_24 = SuiView$mkTextView(&tmpReturn_40, o, 0) , *o = __scopeVar_371_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_371_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_41 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_41, "灯光") , self->scene->mNumLights) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumLights; i++) {
					struct aiLight *  e = self->scene->mLights[i];
					char  tmp[1024];
					sprintf(tmp, "%s type=%d,%s pos=%f,%f,%f dir=%f,%f,%f up=%f,%f,%f atte=%f,%f,%f, cone=%f,%f size=%f,%f\n", e->mName.data, e->mType, e->mType == aiLightSource_DIRECTIONAL ? "dir" : e->mType == aiLightSource_POINT ? "point" : e->mType == aiLightSource_SPOT ? "sport" : e->mType == aiLightSource_AMBIENT ? "ambient" : e->mType == aiLightSource_AREA ? "area" : "undef", e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mDirection.x, e->mDirection.y, e->mDirection.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mAttenuationConstant, e->mAttenuationLinear, e->mAttenuationQuadratic, e->mAngleInnerCone, e->mAngleOuterCone, e->mSize.x, e->mSize.y) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_42 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_410_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_42, o, (long long )e) , *o = __scopeVar_410_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_410_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_43 = NULL;
						{
							SuiView$TextView*  __scopeVar_413_28 = SuiView$mkTextView(&tmpReturn_43, o, 0) , *o = __scopeVar_413_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_413_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_44 = NULL;
							o->setText(o, Orc$str(&tmpReturn_44, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_45 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_418_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_45, o, (long long )0) , *o = __scopeVar_418_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_418_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_46 = NULL;
					{
						SuiView$TextView*  __scopeVar_421_24 = SuiView$mkTextView(&tmpReturn_46, o, 0) , *o = __scopeVar_421_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_421_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_47 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_47, "相机") , self->scene->mNumCameras) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumCameras; i++) {
					struct aiCamera *  e = self->scene->mCameras[i];
					char  tmp[1024];
					sprintf(tmp, "\t%s pos=%f,%f,%f up=%f,%f,%f lookAt=%f,%f,%f fov=%f near=%f far=%f aspect=%f orthorWidth=%f\n", e->mName.data, e->mPosition.x, e->mPosition.y, e->mPosition.z, e->mUp.x, e->mUp.y, e->mUp.z, e->mLookAt.x, e->mLookAt.y, e->mLookAt.z, e->mHorizontalFOV, e->mClipPlaneNear, e->mClipPlaneFar, e->mAspect, e->mOrthographicWidth) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_48 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_449_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_48, o, (long long )e) , *o = __scopeVar_449_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_449_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_49 = NULL;
						{
							SuiView$TextView*  __scopeVar_452_28 = SuiView$mkTextView(&tmpReturn_49, o, 0) , *o = __scopeVar_452_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_452_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_50 = NULL;
							o->setText(o, Orc$str(&tmpReturn_50, tmp) ) ;
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_51 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_457_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_51, o, (long long )0) , *o = __scopeVar_457_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_457_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_52 = NULL;
					{
						SuiView$TextView*  __scopeVar_460_24 = SuiView$mkTextView(&tmpReturn_52, o, 0) , *o = __scopeVar_460_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_460_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_53 = NULL;
						o->setText(o, Orc$String$addi(Orc$str(&tmpReturn_53, "骨架") , self->scene->mNumSkeletons) ) ;
					}
				}
				for (int  i = 0; i < self->scene->mNumSkeletons; i++) {
					struct aiSkeleton *  e = self->scene->mSkeletons[i];
					char  tmp[1024];
					sprintf(tmp, "%s bone=%d\n", e->mName.data, e->mNumBones) ;
					URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_54 = NULL;
					{
						SuiView$TreeSelfCtrlView*  __scopeVar_471_24 = SuiView$mkTreeSelfCtrlView(&tmpReturn_54, o, (long long )e) , *o = __scopeVar_471_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_471_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						o->deep = 1;
						o->hasKids = false;
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_55 = NULL;
						{
							SuiView$TextView*  __scopeVar_474_28 = SuiView$mkTextView(&tmpReturn_55, o, 0) , *o = __scopeVar_474_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_474_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_56 = NULL;
							o->setText(o, Orc$str(&tmpReturn_56, tmp) ) ;
						}
					}
					for (int  j = 0; j < e->mNumBones; j++) {
						struct aiSkeletonBone *  bone = e->mBones[j];
						sprintf(tmp, "%2d numWeights=%d\n", j, bone->mNumnWeights) ;
						URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_57 = NULL;
						{
							SuiView$TreeSelfCtrlView*  __scopeVar_484_28 = SuiView$mkTreeSelfCtrlView(&tmpReturn_57, o, (long long )e) , *o = __scopeVar_484_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_484_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->deep = 2;
							o->hasKids = false;
							URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_58 = NULL;
							{
								SuiView$TextView*  __scopeVar_487_32 = SuiView$mkTextView(&tmpReturn_58, o, 0) , *o = __scopeVar_487_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_487_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_59 = NULL;
								o->setText(o, Orc$str(&tmpReturn_59, tmp) ) ;
							}
						}
						for (int  k = 0; k < bone->mNumnWeights; k++) {
							struct aiMesh *  mesh = bone->mMeshId;
							struct aiVertexWeight *  weight = bone->mWeights + k;
							sprintf(tmp, "%2d mesh=%s weight=%f vtxId=%d\n", k, mesh->mName.data, weight->mWeight, weight->mVertexId) ;
							URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_60 = NULL;
							{
								SuiView$TreeSelfCtrlView*  __scopeVar_495_32 = SuiView$mkTreeSelfCtrlView(&tmpReturn_60, o, (long long )e) , *o = __scopeVar_495_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_495_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								o->deep = 3;
								o->hasKids = false;
								URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_61 = NULL;
								{
									SuiView$TextView*  __scopeVar_498_36 = SuiView$mkTextView(&tmpReturn_61, o, 0) , *o = __scopeVar_498_36;
									UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_498_36 = ((SuiCore$Node*)o)->__exit__((void*)o);
								
									URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_62 = NULL;
									o->setText(o, Orc$str(&tmpReturn_62, tmp) ) ;
								}
							}
						}
					}
				}
				URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_63 = NULL;
				{
					SuiView$TreeSelfCtrlView*  __scopeVar_505_20 = SuiView$mkTreeSelfCtrlView(&tmpReturn_63, o, (long long )0) , *o = __scopeVar_505_20;
					UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_505_20 = ((SuiCore$Node*)o)->__exit__((void*)o);
				
					o->deep = 0;
					o->hasKids = true;
					URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_64 = NULL;
					{
						SuiView$TextView*  __scopeVar_508_24 = SuiView$mkTextView(&tmpReturn_64, o, 0) , *o = __scopeVar_508_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_508_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_65 = NULL;
						o->setText(o, Orc$str(&tmpReturn_65, "节点") ) ;
					}
				}
				self->mkNodeTreeView(self, o, self->scene->mRootNode, 0, 1) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_66 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_67 = NULL;
		o->setTitle(o, Orc$String$replaceAll(&tmpReturn_66, Orc$str(&tmpReturn_67, "预览模型{0}") , "{0}", self->path->str) ->str) ;
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
		SuiView$TreeSelfCtrlView*  __scopeVar_534_8 = SuiView$mkTreeSelfCtrlView(&tmpReturn_1, o, (long long )node) , *o = __scopeVar_534_8;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_534_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		o->deep = deep;
		o->hasKids = node->mNumChildren > 0 || node->mMetaData != NULL;
		URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
		{
			SuiView$TextView*  __scopeVar_537_12 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_537_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_537_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			o->setText(o, Orc$str(&tmpReturn_3, tmp) ) ;
		}
	}
	if (node->mMetaData) {
		URGC_VAR_CLEANUP_CLASS SuiView$TreeSelfCtrlView*  tmpReturn_4 = NULL;
		{
			SuiView$TreeSelfCtrlView*  __scopeVar_542_12 = SuiView$mkTreeSelfCtrlView(&tmpReturn_4, o, (long long )0) , *o = __scopeVar_542_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_542_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->deep = deep + 1;
			o->hasKids = true;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_5 = NULL;
			{
				SuiView$TextView*  __scopeVar_545_16 = SuiView$mkTextView(&tmpReturn_5, o, 0) , *o = __scopeVar_545_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_545_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
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



static void  __finiBlock___Block_206_21(Sgl$__Block_206_21 *  self){
	urgc_set_field_class(self, (void * )offsetof(Sgl$__Block_206_21, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_215_31(Sgl$__Closure_215_31 *  self, Sgl$FboView *  fboView){
	self->__var___Block_206_21->self->drawFboView(self->__var___Block_206_21->self, fboView) ;
}

static void  __fini___Closure_215_31(Sgl$__Closure_215_31 *  self){
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_215_31, __var___Block_206_21) , NULL) ;
	urgc_free_later(self) ;
}

static Sgl$__Closure_215_31*  __make___Closure_215_31(Sgl$__Closure_215_31 **  __outRef__, Sgl$__Block_206_21 *  __var___Block_206_21){
	URGC_VAR_CLEANUP Sgl$__Closure_215_31*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(Sgl$__Closure_215_31) , __fini___Closure_215_31) ));
	self->invoke = __fn___Closure_215_31;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(Sgl$__Closure_215_31, __var___Block_206_21) , __var___Block_206_21) ;
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
	orc_metaField_method(&pNext, "setPath", offsetof(Sgl$ModelLoader, setPath));
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
	((Sgl$ModelLoader*)self)->setPath = (void*)Sgl$ModelLoader$setPath;
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
}


void  Sgl$ModelLoader$setMaterialPaths(Sgl$ModelLoader *  self, Orc$List *  list){
	urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, materialPaths) , list) ;
	self->updateMaterialSlots(self) ;
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
}


void  Sgl$ModelLoader$setPath(Sgl$ModelLoader *  self, Orc$String*  path){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(path);

	urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, path) , path) ;
	if (path) {
		URGC_VAR_CLEANUP_CLASS Sgl$AssimpLoader*  l = (l=NULL,urgc_init_var_class((void**)&l, Sgl$AssimpLoader_new(&l) ));
		urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, loader) , l) ;
		l->load(l, self->path->str) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  tmpReturn_1 = NULL;
		urgc_set_field_class(self, (void * )offsetof(Sgl$ModelLoader, modelRoot) , l->buildSglTree(&tmpReturn_1, l) ) ;
		((SuiCore$Node * )self)->appendChild(self, self->modelRoot) ;
		SuiCore$printNodeTree(self, 0) ;
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
	l->showWindow(l) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Obj3d*  root = l->buildSglTree((root = NULL,&root), l) ;
	SuiCore$printNodeTree(root, 0) ;
}



