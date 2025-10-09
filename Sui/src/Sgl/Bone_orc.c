
#include "Bone_orc.h" 

#include <stdio.h>
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "./Mat_orc.h"
#include "./Obj3d_orc.h"
#include "./Buffer_orc.h"
#include "./DrawCtx_orc.h"


// static struct 


// static function declaration
static bool  _walkBoneIf_toCalcBoneMatrix(Sgl$CalcData *  calcData, SuiCore$Node *  n);



//vtable instance
Vtable_Sgl$Bone _vtable_Sgl$Bone;

// init meta

void Sgl$Bone_initMeta(Vtable_Sgl$Bone *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "originPosition", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$Bone, originPosition), false, false, 0);
	orc_metaField_struct(&pNext, "animMatrix", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Bone, animMatrix), false, false, 0);
	orc_metaField_struct(&pNext, "bindPose", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Bone, bindPose), false, false, 0);
	orc_metaField_struct(&pNext, "bindMatrixInverse", Sgl$Mat_getOrInitMetaStruct(), offsetof(Sgl$Bone, bindMatrixInverse), false, false, 0);
	orc_metaField_primitive(&pNext, "index", OrcMetaType_int, offsetof(Sgl$Bone, index), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "parentId", OrcMetaType_int, offsetof(Sgl$Bone, parentId), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "id", OrcMetaType_int, offsetof(Sgl$Bone, id), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_Sgl$Bone* Vtable_Sgl$Bone_init(Vtable_Sgl$Bone* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Bone;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Bone_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Bone";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Bone_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Bone_fini(Sgl$Bone *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	

}

// init fields function


void Sgl$Bone_init_fields(Sgl$Bone *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Bone_fini;
	//fields
    {
	((Sgl$Bone*)self)->animMatrix = Sgl$mkMatIdentity() ;
	((Sgl$Bone*)self)->bindPose = Sgl$mkMatIdentity() ;
	((Sgl$Bone*)self)->bindMatrixInverse = Sgl$mkMatIdentity() ;
	((Sgl$Bone*)self)->index = -1;
    }
	((Sgl$Obj3d*)self)->drawSelf = (void*)Sgl$Bone$drawSelf;
}

// init function

void Sgl$Bone_init(Sgl$Bone *self, void *pOwner){
    Vtable_Sgl$Bone_init(&_vtable_Sgl$Bone);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Bone;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Bone_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Bone * Sgl$Bone_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Bone *self = calloc(1, sizeof(Sgl$Bone));
	
    Sgl$Bone_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Bone$drawSelf(Sgl$Bone *  self, Sgl$DrawCtx *  ctx){
	Sgl$Obj3d *  p = (Sgl$Obj3d * )((SuiCore$Node * )self)->parent;
	if (Orc_instanceof((Object*)p, (Vtable_Object*)Vtable_Sgl$Obj3d_init(NULL))) {
		SuiCore$Vec3 f = p->localToWorld(p, SuiCore$mkVec3(0, 0, 0) ) ;
		SuiCore$Vec3 t = p->localToWorld(p, ((Sgl$Obj3d * )self)->position) ;
		{
			Sgl$GeometryLine*  o = ctx->lineGeometry;
			
		
			o->color = 0xff00ff00;
			o->moveTo(o, f.x, f.y, f.z) ;
			o->lineTo_color(o, t.x, t.y, t.z, 0xff0000ff) ;
		}
	}
}




//vtable instance
Vtable_Sgl$Skeleton _vtable_Sgl$Skeleton;

// init meta

void Sgl$Skeleton_initMeta(Vtable_Sgl$Skeleton *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "offsetMatrixArray", ((Vtable_Object*)Vtable_Sgl$MatArray_init(0)), offsetof(Sgl$Skeleton, offsetMatrixArray), true, false, 1);

	orc_metaField_method(&pNext, "calcBoneMatrixArray", offsetof(Sgl$Skeleton, calcBoneMatrixArray));
}


// vtable init


Vtable_Sgl$Skeleton* Vtable_Sgl$Skeleton_init(Vtable_Sgl$Skeleton* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$Skeleton;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$Skeleton_new;
    ((Vtable_Object*)pvt)->className = "Sgl$Skeleton";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$Skeleton_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$Skeleton_fini(Sgl$Skeleton *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$Skeleton*)self)->offsetMatrixArray);

}

// init fields function


void Sgl$Skeleton_init_fields(Sgl$Skeleton *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)Sgl$Skeleton_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$MatArray*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$Skeleton*)self)->offsetMatrixArray, Sgl$MatArray_new(&tmpNewOwner_1) );
    }
	((Sgl$Skeleton*)self)->calcBoneMatrixArray = (void*)Sgl$Skeleton$calcBoneMatrixArray;
	((Sgl$Obj3d*)self)->tick = (void*)Sgl$Skeleton$tick;
}

// init function

void Sgl$Skeleton_init(Sgl$Skeleton *self, void *pOwner){
    Vtable_Sgl$Skeleton_init(&_vtable_Sgl$Skeleton);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$Skeleton;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$Skeleton_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$Skeleton * Sgl$Skeleton_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$Skeleton *self = calloc(1, sizeof(Sgl$Skeleton));
	
    Sgl$Skeleton_init(self, pOwner);
    return self;
}


// class members
void  Sgl$Skeleton$calcBoneMatrixArray(Sgl$Skeleton *  self){
	((Sgl$StructArrayBase * )self->offsetMatrixArray)->clear(self->offsetMatrixArray) ;
	Sgl$CalcData calcData;
	calcData.index = 0;
	calcData.skeleton = self;
	SuiCore$Node$walkIf((SuiCore$Node * )self, _walkBoneIf_toCalcBoneMatrix, &calcData) ;
}


void  Sgl$Skeleton$tick(Sgl$Skeleton *  self, Sgl$DrawCtx *  ctx){
	self->calcBoneMatrixArray(self) ;
}




// get or init meta 
MetaStruct* Sgl$CalcData_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$CalcData", sizeof( Sgl$CalcData ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_class(&pNext, "skeleton", ((Vtable_Object*)Vtable_Sgl$Skeleton_init(0)), offsetof(Sgl$CalcData, skeleton), false, true, 1);
		orc_metaField_primitive(&pNext, "index", OrcMetaType_int, offsetof(Sgl$CalcData, index), 0, 0, 0, 0);//int
    }
	return meta;
}
static bool  _walkBoneIf_toCalcBoneMatrix(Sgl$CalcData *  calcData, SuiCore$Node *  n){
	if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Bone_init(NULL))) {
		Sgl$Bone *  bone = (Sgl$Bone * )n;
		bone->index = calcData->index;
		calcData->index++;
		Sgl$Mat modelMatrix;
		((Sgl$Obj3d * )bone)->updateTransform(bone) ;
		if (Orc_instanceof((Object*)n->parent, (Vtable_Object*)Vtable_Sgl$Bone_init(NULL))) {
			Sgl$Bone *  parentBone = ((SuiCore$Node * )bone)->parent;
			Sgl$Mat$mul(&modelMatrix, &parentBone->animMatrix, &((Sgl$Obj3d * )bone)->transform) ;
		}
		else {
			modelMatrix = ((Sgl$Obj3d * )bone)->transform;
		}
		bone->animMatrix = modelMatrix;
		Sgl$Mat offsetMatrix;
		Sgl$Mat$mul(&offsetMatrix, &modelMatrix, &bone->bindMatrixInverse) ;
		calcData->skeleton->offsetMatrixArray->set(calcData->skeleton->offsetMatrixArray, bone->id, offsetMatrix) ;
		return true; 
	}
	if (Orc_instanceof((Object*)n, (Vtable_Object*)Vtable_Sgl$Skeleton_init(NULL))) {
		return true; 
	}
	return false; 
}



