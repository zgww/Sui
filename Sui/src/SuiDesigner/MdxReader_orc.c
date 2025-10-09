
#include "MdxReader_orc.h" 

#include "../Orc/Orc.h"
#include "../nanovg/nanovg.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Time_orc.h"
#include "../Orc/Math_orc.h"
#include "../Orc/Path_orc.h"
#include "../Json/Json_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/Node_orc.h"
#include "../Sui/Core/ViewBase_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Quat_orc.h"
#include "../Sui/Core/Vec2_orc.h"
#include "../Sui/Core/Rect_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/Image_orc.h"
#include "../Sui/Core/Frame_orc.h"
#include "../Sui/Core/Mouse_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/View/ViewBuilder_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Sui/Dialog/FileDialog_orc.h"
#include "../Sui/Dialog/MessageDialog_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/LayoutAlign_orc.h"
#include "../Sui/View/DockLayout_orc.h"
#include "../Sui/View/Drag_orc.h"
#include "../Sui/View/MenuNative_orc.h"
#include "../Sui/Core/Timer_orc.h"
#include "../Sui/Core/Canvas_orc.h"
#include "../Sgl/Buffer_orc.h"
#include "../SuiDesigner/DrawDegree_orc.h"
#include "./ChessBgViewCallback_orc.h"
#include "./Theme_orc.h"
#include "./InvalidReact_orc.h"
#include "./MenuBarCtrl_orc.h"
#include "../Sgl/Material_orc.h"
#include "../Sgl/Geometry_orc.h"
#include "../Sgl/Vbo_orc.h"
#include "../Sgl/Tex2d_orc.h"
#include "../Sgl/Bone_orc.h"
#include "../Sgl/DrawCtx_orc.h"
#include "../Sgl/Obj3d_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner3d_w3e$MdxSeqPlayer _vtable_SuiDesigner3d_w3e$MdxSeqPlayer;

// init meta

void SuiDesigner3d_w3e$MdxSeqPlayer_initMeta(Vtable_SuiDesigner3d_w3e$MdxSeqPlayer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "seqs", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, seqs), true, false, 1);
	orc_metaField_class(&pNext, "helps", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, helps), true, false, 1);
	orc_metaField_class(&pNext, "bones", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, bones), true, false, 1);
	orc_metaField_class(&pNext, "curSeq", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$Sequence_init(0)), offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, curSeq), true, false, 1);
	orc_metaField_primitive(&pNext, "frame", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, frame), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "play", offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, play));
	orc_metaField_method(&pNext, "isEnd", offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, isEnd));
	orc_metaField_method(&pNext, "updateKGSC", offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, updateKGSC));
	orc_metaField_method(&pNext, "updateKGRT", offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, updateKGRT));
	orc_metaField_method(&pNext, "updateKGTR", offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, updateKGTR));
	orc_metaField_method(&pNext, "findSeq", offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, findSeq));
	orc_metaField_method(&pNext, "init", offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, init));
}


// vtable init


Vtable_SuiDesigner3d_w3e$MdxSeqPlayer* Vtable_SuiDesigner3d_w3e$MdxSeqPlayer_init(Vtable_SuiDesigner3d_w3e$MdxSeqPlayer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$MdxSeqPlayer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Obj3d_init(&_vtable_Sgl$Obj3d);

	// init by super vtable init function
    Vtable_Sgl$Obj3d_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Obj3d;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$MdxSeqPlayer_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$MdxSeqPlayer";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$MdxSeqPlayer_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$MdxSeqPlayer_fini(SuiDesigner3d_w3e$MdxSeqPlayer *self){
	//super fini
    Sgl$Obj3d_fini((Sgl$Obj3d *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->seqs);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->helps);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->bones);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->curSeq);

}

// init fields function


void SuiDesigner3d_w3e$MdxSeqPlayer_init_fields(SuiDesigner3d_w3e$MdxSeqPlayer *self){
	//super class
    Sgl$Obj3d_init_fields((Sgl$Obj3d*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$MdxSeqPlayer_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->seqs, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->helps, Orc$List_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->bones, Orc$List_new(&tmpNewOwner_3) );
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->curSeq, NULL);
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->frame = 0;
    }
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->play = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$play;
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->isEnd = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$isEnd;
	((Sgl$Obj3d*)self)->tick = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$tick;
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->updateKGSC = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$updateKGSC;
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->updateKGRT = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$updateKGRT;
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->updateKGTR = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$updateKGTR;
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->findSeq = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$findSeq;
	((SuiDesigner3d_w3e$MdxSeqPlayer*)self)->init = (void*)SuiDesigner3d_w3e$MdxSeqPlayer$init;
}

// init function

void SuiDesigner3d_w3e$MdxSeqPlayer_init(SuiDesigner3d_w3e$MdxSeqPlayer *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$MdxSeqPlayer_init(&_vtable_SuiDesigner3d_w3e$MdxSeqPlayer);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$MdxSeqPlayer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$MdxSeqPlayer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$MdxSeqPlayer * SuiDesigner3d_w3e$MdxSeqPlayer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$MdxSeqPlayer *self = calloc(1, sizeof(SuiDesigner3d_w3e$MdxSeqPlayer));
	
    SuiDesigner3d_w3e$MdxSeqPlayer_init(self, pOwner);
    return self;
}


// class members
bool  SuiDesigner3d_w3e$MdxSeqPlayer$play(SuiDesigner3d_w3e$MdxSeqPlayer *  self, const char *  name){
	SuiDesigner3d_w3e$Sequence *  seq = self->findSeq(self, name) ;
	if (seq == NULL) {
		return false; 
	}
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, curSeq) , seq) ;
	self->frame = seq->startFrame;
	return true; 
}


bool  SuiDesigner3d_w3e$MdxSeqPlayer$isEnd(SuiDesigner3d_w3e$MdxSeqPlayer *  self){
	if (self->curSeq == NULL) {
		return false; 
	}
	bool  b = self->frame > self->curSeq->endFrame;
	return b; 
}


void  SuiDesigner3d_w3e$MdxSeqPlayer$tick(SuiDesigner3d_w3e$MdxSeqPlayer *  self, Sgl$DrawCtx *  ctx){
	if (0 || self->curSeq == NULL) {
		return ; 
	}
	self->frame += ctx->dtMs;
	if (self->frame > self->curSeq->endFrame) {
		if (1 || !self->curSeq->nonLooping) {
			self->frame = self->curSeq->startFrame;
		}
		else {
			return ; 
		}
	}
	for (int  i = 0; i < self->bones->size(self->bones) ; i++) {
		SuiDesigner3d_w3e$MdxBone *  bone = (SuiDesigner3d_w3e$MdxBone * )self->bones->get(self->bones, i) ;
		SuiDesigner3d_w3e$MdxNode *  node = bone->node;
		self->updateKGTR(self, node) ;
		self->updateKGRT(self, node) ;
		self->updateKGSC(self, node) ;
	}
	for (int  i = 0; i < self->helps->size(self->helps) ; i++) {
		SuiDesigner3d_w3e$MdxNode *  node = (SuiDesigner3d_w3e$MdxNode * )self->helps->get(self->helps, i) ;
		self->updateKGTR(self, node) ;
		self->updateKGRT(self, node) ;
		self->updateKGSC(self, node) ;
	}
}


void  SuiDesigner3d_w3e$MdxSeqPlayer$updateKGSC(SuiDesigner3d_w3e$MdxSeqPlayer *  self, SuiDesigner3d_w3e$MdxNode *  node){
	if (node->KGSC) {
		SuiDesigner3d_w3e$TrackValueRange range = node->KGSC->findTrackValueRange(node->KGSC, self->frame, self->curSeq) ;
		if (range.left) {
			SuiCore$Vec3 pos = SuiDesigner3d_w3e$TrackValueRange$lerpVec3(&range) ;
			if (node->bone) {
				((Sgl$Obj3d * )node->bone)->scale = pos;
			}
		}
	}
}


void  SuiDesigner3d_w3e$MdxSeqPlayer$updateKGRT(SuiDesigner3d_w3e$MdxSeqPlayer *  self, SuiDesigner3d_w3e$MdxNode *  node){
	if (node->KGRT) {
		SuiDesigner3d_w3e$TrackValueRange range = node->KGRT->findTrackValueRange(node->KGRT, self->frame, self->curSeq) ;
		if (range.left) {
			SuiCore$Quat quat = SuiDesigner3d_w3e$TrackValueRange$lerpQuat(&range) ;
			SuiCore$Vec3 euler = SuiCore$Quat$toEulerXYZ(&quat) ;
			if (node->bone) {
				((Sgl$Obj3d * )node->bone)->rotation = euler;
			}
		}
	}
}


void  SuiDesigner3d_w3e$MdxSeqPlayer$updateKGTR(SuiDesigner3d_w3e$MdxSeqPlayer *  self, SuiDesigner3d_w3e$MdxNode *  node){
	if (node->KGTR) {
		SuiDesigner3d_w3e$TrackValueRange range = node->KGTR->findTrackValueRange(node->KGTR, self->frame, self->curSeq) ;
		if (range.left) {
			SuiCore$Vec3 pos = SuiDesigner3d_w3e$TrackValueRange$lerpVec3(&range) ;
			if (node->bone) {
				SuiCore$Vec3 npos = SuiCore$Vec3$add(&node->bone->originPosition, pos) ;
				((Sgl$Obj3d * )node->bone)->position = npos;
			}
		}
	}
}


SuiDesigner3d_w3e$Sequence *  SuiDesigner3d_w3e$MdxSeqPlayer$findSeq(SuiDesigner3d_w3e$MdxSeqPlayer *  self, const char *  name){
	for (int  i = 0; i < self->seqs->size(self->seqs) ; i++) {
		SuiDesigner3d_w3e$Sequence *  seq = (SuiDesigner3d_w3e$Sequence * )self->seqs->get(self->seqs, i) ;
		if (Orc$String$equals(seq->name, name) ) {
			return seq; 
		}
	}
	return NULL; 
}


void  SuiDesigner3d_w3e$MdxSeqPlayer$init(SuiDesigner3d_w3e$MdxSeqPlayer *  self, SuiDesigner3d_w3e$MdxReader *  r){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, seqs) , r->seqs) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, helps) , r->helps) ;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$MdxSeqPlayer, bones) , r->bones) ;
}




//vtable instance
Vtable_SuiDesigner3d_w3e$FaceFX _vtable_SuiDesigner3d_w3e$FaceFX;

// init meta

void SuiDesigner3d_w3e$FaceFX_initMeta(Vtable_SuiDesigner3d_w3e$FaceFX *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$FaceFX, name), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$FaceFX, path), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$FaceFX* Vtable_SuiDesigner3d_w3e$FaceFX_init(Vtable_SuiDesigner3d_w3e$FaceFX* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$FaceFX;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$FaceFX_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$FaceFX";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$FaceFX_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$FaceFX_fini(SuiDesigner3d_w3e$FaceFX *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$FaceFX*)self)->name);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$FaceFX*)self)->path);

}

// init fields function


void SuiDesigner3d_w3e$FaceFX_init_fields(SuiDesigner3d_w3e$FaceFX *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$FaceFX_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$FaceFX*)self)->name, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$FaceFX*)self)->path, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$FaceFX_init(SuiDesigner3d_w3e$FaceFX *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$FaceFX_init(&_vtable_SuiDesigner3d_w3e$FaceFX);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$FaceFX;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$FaceFX_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$FaceFX * SuiDesigner3d_w3e$FaceFX_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$FaceFX *self = calloc(1, sizeof(SuiDesigner3d_w3e$FaceFX));
	
    SuiDesigner3d_w3e$FaceFX_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$LayerTexture _vtable_SuiDesigner3d_w3e$LayerTexture;

// init meta

void SuiDesigner3d_w3e$LayerTexture_initMeta(Vtable_SuiDesigner3d_w3e$LayerTexture *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$LayerTexture, id), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "KMTF", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$LayerTexture, KMTF), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$LayerTexture* Vtable_SuiDesigner3d_w3e$LayerTexture_init(Vtable_SuiDesigner3d_w3e$LayerTexture* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$LayerTexture;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$LayerTexture_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$LayerTexture";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$LayerTexture_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$LayerTexture_fini(SuiDesigner3d_w3e$LayerTexture *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$LayerTexture*)self)->KMTF);

}

// init fields function


void SuiDesigner3d_w3e$LayerTexture_init_fields(SuiDesigner3d_w3e$LayerTexture *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$LayerTexture_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$LayerTexture*)self)->KMTF, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$LayerTexture_init(SuiDesigner3d_w3e$LayerTexture *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$LayerTexture_init(&_vtable_SuiDesigner3d_w3e$LayerTexture);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$LayerTexture;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$LayerTexture_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$LayerTexture * SuiDesigner3d_w3e$LayerTexture_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$LayerTexture *self = calloc(1, sizeof(SuiDesigner3d_w3e$LayerTexture));
	
    SuiDesigner3d_w3e$LayerTexture_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$Layer _vtable_SuiDesigner3d_w3e$Layer;

// init meta

void SuiDesigner3d_w3e$Layer_initMeta(Vtable_SuiDesigner3d_w3e$Layer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "blend_mode", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Layer, blend_mode), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "shading_flags", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Layer, shading_flags), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "texture_animation_id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Layer, texture_animation_id), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "coord_id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Layer, coord_id), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "alpha", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$Layer, alpha), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "emissive_gain", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$Layer, emissive_gain), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "fresnel_color", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$Layer, fresnel_color), false, false, 0);
	orc_metaField_primitive(&pNext, "fresnel_opacity", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$Layer, fresnel_opacity), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "fresnel_team_color", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$Layer, fresnel_team_color), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "hd", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$Layer, hd), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "textures", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$Layer, textures), true, false, 1);
	orc_metaField_class(&pNext, "KMTA", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$Layer, KMTA), true, false, 1);
	orc_metaField_class(&pNext, "KMTE", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$Layer, KMTE), true, false, 1);
	orc_metaField_class(&pNext, "KFC3", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$Layer, KFC3), true, false, 1);
	orc_metaField_class(&pNext, "KFCA", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$Layer, KFCA), true, false, 1);
	orc_metaField_class(&pNext, "KFTC", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$Layer, KFTC), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$Layer* Vtable_SuiDesigner3d_w3e$Layer_init(Vtable_SuiDesigner3d_w3e$Layer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$Layer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$Layer_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$Layer";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$Layer_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$Layer_fini(SuiDesigner3d_w3e$Layer *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->textures);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KMTA);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KMTE);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KFC3);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KFCA);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KFTC);

}

// init fields function


void SuiDesigner3d_w3e$Layer_init_fields(SuiDesigner3d_w3e$Layer *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$Layer_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->textures, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KMTA, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KMTE, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KFC3, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KFCA, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Layer*)self)->KFTC, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$Layer_init(SuiDesigner3d_w3e$Layer *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$Layer_init(&_vtable_SuiDesigner3d_w3e$Layer);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$Layer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$Layer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$Layer * SuiDesigner3d_w3e$Layer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$Layer *self = calloc(1, sizeof(SuiDesigner3d_w3e$Layer));
	
    SuiDesigner3d_w3e$Layer_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$MdxMaterial _vtable_SuiDesigner3d_w3e$MdxMaterial;

// init meta

void SuiDesigner3d_w3e$MdxMaterial_initMeta(Vtable_SuiDesigner3d_w3e$MdxMaterial *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "priority_plane", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxMaterial, priority_plane), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "flags", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxMaterial, flags), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "layers", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxMaterial, layers), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$MdxMaterial* Vtable_SuiDesigner3d_w3e$MdxMaterial_init(Vtable_SuiDesigner3d_w3e$MdxMaterial* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$MdxMaterial;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$MdxMaterial_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$MdxMaterial";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$MdxMaterial_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$MdxMaterial_fini(SuiDesigner3d_w3e$MdxMaterial *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxMaterial*)self)->layers);

}

// init fields function


void SuiDesigner3d_w3e$MdxMaterial_init_fields(SuiDesigner3d_w3e$MdxMaterial *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$MdxMaterial_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxMaterial*)self)->layers, Orc$List_new(&tmpNewOwner_1) );
    }
	
}

// init function

void SuiDesigner3d_w3e$MdxMaterial_init(SuiDesigner3d_w3e$MdxMaterial *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$MdxMaterial_init(&_vtable_SuiDesigner3d_w3e$MdxMaterial);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$MdxMaterial;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$MdxMaterial_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$MdxMaterial * SuiDesigner3d_w3e$MdxMaterial_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$MdxMaterial *self = calloc(1, sizeof(SuiDesigner3d_w3e$MdxMaterial));
	
    SuiDesigner3d_w3e$MdxMaterial_init(self, pOwner);
    return self;
}


// class members


// get or init meta 
MetaStruct* SuiDesigner3d_w3e$Extend_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiDesigner3d_w3e$Extend", sizeof( SuiDesigner3d_w3e$Extend ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "bounds_radius", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$Extend, bounds_radius), 0, 0, 0, 0);//float
		orc_metaField_struct(&pNext, "minimum", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$Extend, minimum), false, false, 0);
		orc_metaField_struct(&pNext, "maximum", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$Extend, maximum), false, false, 0);
    }
	return meta;
}
Orc$String*  SuiDesigner3d_w3e$Extend$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$Extend *  self){
	char  buf[512];
	sprintf(buf, "Extend(radius=%f, minimum=(%f,%f,%f), maximum=(%f,%f,%f))", self->bounds_radius, self->minimum.x, self->minimum.y, self->minimum.z, self->maximum.x, self->maximum.y, self->maximum.z) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = Orc$str((s = NULL,&s), buf) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, s) ; 
}

int  SuiDesigner3d_w3e$INVALID_INDEX = -1;

//vtable instance
Vtable_SuiDesigner3d_w3e$Sequence _vtable_SuiDesigner3d_w3e$Sequence;

// init meta

void SuiDesigner3d_w3e$Sequence_initMeta(Vtable_SuiDesigner3d_w3e$Sequence *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$Sequence, name), true, false, 1);
	orc_metaField_primitive(&pNext, "rarity", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$Sequence, rarity), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "moveSpeed", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$Sequence, moveSpeed), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "nonLooping", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$Sequence, nonLooping), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "startFrame", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Sequence, startFrame), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "endFrame", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Sequence, endFrame), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "sync_point", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Sequence, sync_point), 0, 0, 0, 0);//int
	orc_metaField_struct(&pNext, "extend", SuiDesigner3d_w3e$Extend_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$Sequence, extend), false, false, 0);

	orc_metaField_method(&pNext, "toString", offsetof(SuiDesigner3d_w3e$Sequence, toString));
}


// vtable init


Vtable_SuiDesigner3d_w3e$Sequence* Vtable_SuiDesigner3d_w3e$Sequence_init(Vtable_SuiDesigner3d_w3e$Sequence* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$Sequence;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$Sequence_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$Sequence";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$Sequence_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$Sequence_fini(SuiDesigner3d_w3e$Sequence *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Sequence*)self)->name);

}

// init fields function


void SuiDesigner3d_w3e$Sequence_init_fields(SuiDesigner3d_w3e$Sequence *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$Sequence_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Sequence*)self)->name, Orc$str(&tmpReturn_1, "") );
    }
	((SuiDesigner3d_w3e$Sequence*)self)->toString = (void*)SuiDesigner3d_w3e$Sequence$toString;
}

// init function

void SuiDesigner3d_w3e$Sequence_init(SuiDesigner3d_w3e$Sequence *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$Sequence_init(&_vtable_SuiDesigner3d_w3e$Sequence);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$Sequence;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$Sequence_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$Sequence * SuiDesigner3d_w3e$Sequence_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$Sequence *self = calloc(1, sizeof(SuiDesigner3d_w3e$Sequence));
	
    SuiDesigner3d_w3e$Sequence_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiDesigner3d_w3e$Sequence$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$Sequence *  self){
	char  b[512];
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	sprintf(b, "%s; rarity:%f,moveSpeed:%f, nonLooping:%d,frame:%d,%d; syncpoint:%d. %s", self->name->str, self->rarity, self->moveSpeed, self->nonLooping, self->startFrame, self->endFrame, self->sync_point, SuiDesigner3d_w3e$Extend$toString(&tmpReturn_1, &self->extend) ->str) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_2, b) ) ; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$GlobalSeq _vtable_SuiDesigner3d_w3e$GlobalSeq;

// init meta

void SuiDesigner3d_w3e$GlobalSeq_initMeta(Vtable_SuiDesigner3d_w3e$GlobalSeq *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "duration", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$GlobalSeq, duration), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "time", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$GlobalSeq, time), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "internalGlobalSEquenceId", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$GlobalSeq, internalGlobalSEquenceId), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$GlobalSeq* Vtable_SuiDesigner3d_w3e$GlobalSeq_init(Vtable_SuiDesigner3d_w3e$GlobalSeq* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$GlobalSeq;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$GlobalSeq_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$GlobalSeq";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$GlobalSeq_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$GlobalSeq_fini(SuiDesigner3d_w3e$GlobalSeq *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner3d_w3e$GlobalSeq_init_fields(SuiDesigner3d_w3e$GlobalSeq *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$GlobalSeq_fini;
	//fields
    {
	((SuiDesigner3d_w3e$GlobalSeq*)self)->internalGlobalSEquenceId = SuiDesigner3d_w3e$INVALID_INDEX;
    }
	
}

// init function

void SuiDesigner3d_w3e$GlobalSeq_init(SuiDesigner3d_w3e$GlobalSeq *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$GlobalSeq_init(&_vtable_SuiDesigner3d_w3e$GlobalSeq);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$GlobalSeq;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$GlobalSeq_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$GlobalSeq * SuiDesigner3d_w3e$GlobalSeq_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$GlobalSeq *self = calloc(1, sizeof(SuiDesigner3d_w3e$GlobalSeq));
	
    SuiDesigner3d_w3e$GlobalSeq_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$TextureData _vtable_SuiDesigner3d_w3e$TextureData;

// init meta

void SuiDesigner3d_w3e$TextureData_initMeta(Vtable_SuiDesigner3d_w3e$TextureData *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "replaceableId", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TextureData, replaceableId), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "wrapWidth", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$TextureData, wrapWidth), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "wrapHeight", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$TextureData, wrapHeight), 0, 0, 0, 0);//bool
	orc_metaField_class(&pNext, "fileName", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$TextureData, fileName), true, false, 1);
	orc_metaField_primitive(&pNext, "internalTextureId", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TextureData, internalTextureId), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "_pngPath", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$TextureData, _pngPath), true, false, 1);

	orc_metaField_method(&pNext, "getRealPath", offsetof(SuiDesigner3d_w3e$TextureData, getRealPath));
}


// vtable init


Vtable_SuiDesigner3d_w3e$TextureData* Vtable_SuiDesigner3d_w3e$TextureData_init(Vtable_SuiDesigner3d_w3e$TextureData* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$TextureData;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$TextureData_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$TextureData";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$TextureData_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$TextureData_fini(SuiDesigner3d_w3e$TextureData *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$TextureData*)self)->fileName);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$TextureData*)self)->_pngPath);

}

// init fields function


void SuiDesigner3d_w3e$TextureData_init_fields(SuiDesigner3d_w3e$TextureData *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$TextureData_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$TextureData*)self)->fileName, Orc$str(&tmpReturn_1, "") );
	((SuiDesigner3d_w3e$TextureData*)self)->internalTextureId = SuiDesigner3d_w3e$INVALID_INDEX;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$TextureData*)self)->_pngPath, Orc$str(&tmpReturn_2, "") );
    }
	((SuiDesigner3d_w3e$TextureData*)self)->getRealPath = (void*)SuiDesigner3d_w3e$TextureData$getRealPath;
}

// init function

void SuiDesigner3d_w3e$TextureData_init(SuiDesigner3d_w3e$TextureData *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$TextureData_init(&_vtable_SuiDesigner3d_w3e$TextureData);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$TextureData;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$TextureData_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$TextureData * SuiDesigner3d_w3e$TextureData_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$TextureData *self = calloc(1, sizeof(SuiDesigner3d_w3e$TextureData));
	
    SuiDesigner3d_w3e$TextureData_init(self, pOwner);
    return self;
}


// class members
const char *  SuiDesigner3d_w3e$TextureData$getRealPath(SuiDesigner3d_w3e$TextureData *  self){
	if (Orc$String$notEmpty(self->fileName) ) {
		if (Orc$String$empty(self->_pngPath) ) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$TextureData, _pngPath) , Orc$Path_withExt(&tmpReturn_1, self->fileName->str, ".png") ) ;
		}
		return self->_pngPath->str; 
	}
	int  id = self->replaceableId;
	if (id == 1) {
		return "ReplaceableTextures/TeamColor/TeamColor00.png"; 
	}
	if (id == 2) {
		return "ReplaceableTextures/TeamGlow/TeamGlow00.png"; 
	}
	if (id == 11) {
		return "ReplaceableTextures/Cliff/Cliff0.png"; 
	}
	if (id == 21) {
		return ""; 
	}
	if (id == 31) {
		return "ReplaceableTextures/LordaeronTree/LordaeronSummerTree.png"; 
	}
	if (id == 32) {
		return "ReplaceableTextures/AshenvaleTree/AshenTree.png"; 
	}
	if (id == 33) {
		return "ReplaceableTextures/BarrensTree/BarrensTree.png"; 
	}
	if (id == 34) {
		return "ReplaceableTextures/NorthrendTree/NorthTree.png"; 
	}
	if (id == 35) {
		return "ReplaceableTextures/Mushroom/MushroomTree.png"; 
	}
	if (id == 36) {
		return "ReplaceableTextures/RuinsTree/RuinsTree.png"; 
	}
	if (id == 37) {
		return "ReplaceableTextures/OutlandMushroomTree/MushroomTree.png"; 
	}
	return NULL; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$GeosetGroup _vtable_SuiDesigner3d_w3e$GeosetGroup;

// init meta

void SuiDesigner3d_w3e$GeosetGroup_initMeta(Vtable_SuiDesigner3d_w3e$GeosetGroup *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "matrixListSize", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$GeosetGroup, matrixListSize), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$GeosetGroup* Vtable_SuiDesigner3d_w3e$GeosetGroup_init(Vtable_SuiDesigner3d_w3e$GeosetGroup* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$GeosetGroup;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$GeosetGroup_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$GeosetGroup";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$GeosetGroup_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$GeosetGroup_fini(SuiDesigner3d_w3e$GeosetGroup *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner3d_w3e$GeosetGroup_init_fields(SuiDesigner3d_w3e$GeosetGroup *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$GeosetGroup_fini;
	//fields
    {
	
    }
	
}

// init function

void SuiDesigner3d_w3e$GeosetGroup_init(SuiDesigner3d_w3e$GeosetGroup *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$GeosetGroup_init(&_vtable_SuiDesigner3d_w3e$GeosetGroup);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$GeosetGroup;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$GeosetGroup_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$GeosetGroup * SuiDesigner3d_w3e$GeosetGroup_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$GeosetGroup *self = calloc(1, sizeof(SuiDesigner3d_w3e$GeosetGroup));
	
    SuiDesigner3d_w3e$GeosetGroup_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$CornEmitter _vtable_SuiDesigner3d_w3e$CornEmitter;

// init meta

void SuiDesigner3d_w3e$CornEmitter_initMeta(Vtable_SuiDesigner3d_w3e$CornEmitter *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "node", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$MdxNode_init(0)), offsetof(SuiDesigner3d_w3e$CornEmitter, node), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$CornEmitter* Vtable_SuiDesigner3d_w3e$CornEmitter_init(Vtable_SuiDesigner3d_w3e$CornEmitter* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$CornEmitter;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$CornEmitter_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$CornEmitter";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$CornEmitter_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$CornEmitter_fini(SuiDesigner3d_w3e$CornEmitter *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$CornEmitter*)self)->node);

}

// init fields function


void SuiDesigner3d_w3e$CornEmitter_init_fields(SuiDesigner3d_w3e$CornEmitter *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$CornEmitter_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$CornEmitter*)self)->node, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$CornEmitter_init(SuiDesigner3d_w3e$CornEmitter *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$CornEmitter_init(&_vtable_SuiDesigner3d_w3e$CornEmitter);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$CornEmitter;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$CornEmitter_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$CornEmitter * SuiDesigner3d_w3e$CornEmitter_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$CornEmitter *self = calloc(1, sizeof(SuiDesigner3d_w3e$CornEmitter));
	
    SuiDesigner3d_w3e$CornEmitter_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$CollisionShape _vtable_SuiDesigner3d_w3e$CollisionShape;

// init meta

void SuiDesigner3d_w3e$CollisionShape_initMeta(Vtable_SuiDesigner3d_w3e$CollisionShape *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "node", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$MdxNode_init(0)), offsetof(SuiDesigner3d_w3e$CollisionShape, node), true, false, 1);
	orc_metaField_struct(&pNext, "v0", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$CollisionShape, v0), false, false, 0);
	orc_metaField_struct(&pNext, "v1", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$CollisionShape, v1), false, false, 0);
	orc_metaField_primitive(&pNext, "radius", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$CollisionShape, radius), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$CollisionShape* Vtable_SuiDesigner3d_w3e$CollisionShape_init(Vtable_SuiDesigner3d_w3e$CollisionShape* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$CollisionShape;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$CollisionShape_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$CollisionShape";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$CollisionShape_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$CollisionShape_fini(SuiDesigner3d_w3e$CollisionShape *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$CollisionShape*)self)->node);

}

// init fields function


void SuiDesigner3d_w3e$CollisionShape_init_fields(SuiDesigner3d_w3e$CollisionShape *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$CollisionShape_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$CollisionShape*)self)->node, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$CollisionShape_init(SuiDesigner3d_w3e$CollisionShape *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$CollisionShape_init(&_vtable_SuiDesigner3d_w3e$CollisionShape);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$CollisionShape;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$CollisionShape_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$CollisionShape * SuiDesigner3d_w3e$CollisionShape_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$CollisionShape *self = calloc(1, sizeof(SuiDesigner3d_w3e$CollisionShape));
	
    SuiDesigner3d_w3e$CollisionShape_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$MdxBone _vtable_SuiDesigner3d_w3e$MdxBone;

// init meta

void SuiDesigner3d_w3e$MdxBone_initMeta(Vtable_SuiDesigner3d_w3e$MdxBone *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "node", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$MdxNode_init(0)), offsetof(SuiDesigner3d_w3e$MdxBone, node), true, false, 1);
	orc_metaField_primitive(&pNext, "geoset_id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxBone, geoset_id), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "geoset_animation_id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxBone, geoset_animation_id), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$MdxBone* Vtable_SuiDesigner3d_w3e$MdxBone_init(Vtable_SuiDesigner3d_w3e$MdxBone* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$MdxBone;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$MdxBone_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$MdxBone";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$MdxBone_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$MdxBone_fini(SuiDesigner3d_w3e$MdxBone *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxBone*)self)->node);

}

// init fields function


void SuiDesigner3d_w3e$MdxBone_init_fields(SuiDesigner3d_w3e$MdxBone *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$MdxBone_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxBone*)self)->node, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$MdxBone_init(SuiDesigner3d_w3e$MdxBone *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$MdxBone_init(&_vtable_SuiDesigner3d_w3e$MdxBone);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$MdxBone;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$MdxBone_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$MdxBone * SuiDesigner3d_w3e$MdxBone_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$MdxBone *self = calloc(1, sizeof(SuiDesigner3d_w3e$MdxBone));
	
    SuiDesigner3d_w3e$MdxBone_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$MdxLight _vtable_SuiDesigner3d_w3e$MdxLight;

// init meta

void SuiDesigner3d_w3e$MdxLight_initMeta(Vtable_SuiDesigner3d_w3e$MdxLight *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "node", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$MdxNode_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, node), true, false, 1);
	orc_metaField_primitive(&pNext, "type", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxLight, type), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "attenuation_start", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxLight, attenuation_start), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "attenuation_end", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxLight, attenuation_end), 0, 0, 0, 0);//int
	orc_metaField_struct(&pNext, "color", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$MdxLight, color), false, false, 0);
	orc_metaField_primitive(&pNext, "intensity", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$MdxLight, intensity), 0, 0, 0, 0);//float
	orc_metaField_struct(&pNext, "ambient_color", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$MdxLight, ambient_color), false, false, 0);
	orc_metaField_primitive(&pNext, "ambient_intensity", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$MdxLight, ambient_intensity), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "KLAS", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, KLAS), true, false, 1);
	orc_metaField_class(&pNext, "KLAE", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, KLAE), true, false, 1);
	orc_metaField_class(&pNext, "KLAC", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, KLAC), true, false, 1);
	orc_metaField_class(&pNext, "KLAI", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, KLAI), true, false, 1);
	orc_metaField_class(&pNext, "KLBI", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, KLBI), true, false, 1);
	orc_metaField_class(&pNext, "KLBC", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, KLBC), true, false, 1);
	orc_metaField_class(&pNext, "KLAV", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxLight, KLAV), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$MdxLight* Vtable_SuiDesigner3d_w3e$MdxLight_init(Vtable_SuiDesigner3d_w3e$MdxLight* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$MdxLight;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$MdxLight_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$MdxLight";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$MdxLight_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$MdxLight_fini(SuiDesigner3d_w3e$MdxLight *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->node);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAS);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAE);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAC);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAI);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLBI);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLBC);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAV);

}

// init fields function


void SuiDesigner3d_w3e$MdxLight_init_fields(SuiDesigner3d_w3e$MdxLight *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$MdxLight_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->node, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAS, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAE, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAC, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAI, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLBI, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLBC, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxLight*)self)->KLAV, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$MdxLight_init(SuiDesigner3d_w3e$MdxLight *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$MdxLight_init(&_vtable_SuiDesigner3d_w3e$MdxLight);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$MdxLight;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$MdxLight_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$MdxLight * SuiDesigner3d_w3e$MdxLight_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$MdxLight *self = calloc(1, sizeof(SuiDesigner3d_w3e$MdxLight));
	
    SuiDesigner3d_w3e$MdxLight_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$TrackValue _vtable_SuiDesigner3d_w3e$TrackValue;

// init meta

void SuiDesigner3d_w3e$TrackValue_initMeta(Vtable_SuiDesigner3d_w3e$TrackValue *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "frame", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TrackValue, frame), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "toString", offsetof(SuiDesigner3d_w3e$TrackValue, toString));
}


// vtable init


Vtable_SuiDesigner3d_w3e$TrackValue* Vtable_SuiDesigner3d_w3e$TrackValue_init(Vtable_SuiDesigner3d_w3e$TrackValue* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$TrackValue;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$TrackValue_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$TrackValue";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$TrackValue_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$TrackValue_fini(SuiDesigner3d_w3e$TrackValue *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner3d_w3e$TrackValue_init_fields(SuiDesigner3d_w3e$TrackValue *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$TrackValue_fini;
	//fields
    {
	
    }
	((SuiDesigner3d_w3e$TrackValue*)self)->toString = (void*)SuiDesigner3d_w3e$TrackValue$toString;
}

// init function

void SuiDesigner3d_w3e$TrackValue_init(SuiDesigner3d_w3e$TrackValue *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$TrackValue_init(&_vtable_SuiDesigner3d_w3e$TrackValue);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$TrackValue;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$TrackValue_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$TrackValue * SuiDesigner3d_w3e$TrackValue_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$TrackValue *self = calloc(1, sizeof(SuiDesigner3d_w3e$TrackValue));
	
    SuiDesigner3d_w3e$TrackValue_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiDesigner3d_w3e$TrackValue$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$TrackValue *  self){
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$String$addi(Orc$str(&tmpReturn_1, "") , self->frame) ) ; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$TrackInt _vtable_SuiDesigner3d_w3e$TrackInt;

// init meta

void SuiDesigner3d_w3e$TrackInt_initMeta(Vtable_SuiDesigner3d_w3e$TrackInt *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TrackInt, value), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "inTan", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TrackInt, inTan), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "outTan", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TrackInt, outTan), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$TrackInt* Vtable_SuiDesigner3d_w3e$TrackInt_init(Vtable_SuiDesigner3d_w3e$TrackInt* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$TrackInt;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner3d_w3e$TrackValue_init(&_vtable_SuiDesigner3d_w3e$TrackValue);

	// init by super vtable init function
    Vtable_SuiDesigner3d_w3e$TrackValue_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner3d_w3e$TrackValue;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$TrackInt_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$TrackInt";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$TrackInt_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$TrackInt_fini(SuiDesigner3d_w3e$TrackInt *self){
	//super fini
    SuiDesigner3d_w3e$TrackValue_fini((SuiDesigner3d_w3e$TrackValue *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner3d_w3e$TrackInt_init_fields(SuiDesigner3d_w3e$TrackInt *self){
	//super class
    SuiDesigner3d_w3e$TrackValue_init_fields((SuiDesigner3d_w3e$TrackValue*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$TrackInt_fini;
	//fields
    {
	
    }
	((SuiDesigner3d_w3e$TrackValue*)self)->toString = (void*)SuiDesigner3d_w3e$TrackInt$toString;
}

// init function

void SuiDesigner3d_w3e$TrackInt_init(SuiDesigner3d_w3e$TrackInt *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$TrackInt_init(&_vtable_SuiDesigner3d_w3e$TrackInt);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$TrackInt;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$TrackInt_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$TrackInt * SuiDesigner3d_w3e$TrackInt_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$TrackInt *self = calloc(1, sizeof(SuiDesigner3d_w3e$TrackInt));
	
    SuiDesigner3d_w3e$TrackInt_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiDesigner3d_w3e$TrackInt$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$TrackInt *  self){
	char  tmp[128];
	sprintf(tmp, "%d|%d", ((SuiDesigner3d_w3e$TrackValue * )self)->frame, self->value) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$TrackFloat _vtable_SuiDesigner3d_w3e$TrackFloat;

// init meta

void SuiDesigner3d_w3e$TrackFloat_initMeta(Vtable_SuiDesigner3d_w3e$TrackFloat *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "value", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$TrackFloat, value), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "inTan", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$TrackFloat, inTan), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "outTan", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$TrackFloat, outTan), 0, 0, 0, 0);//float

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$TrackFloat* Vtable_SuiDesigner3d_w3e$TrackFloat_init(Vtable_SuiDesigner3d_w3e$TrackFloat* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$TrackFloat;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner3d_w3e$TrackValue_init(&_vtable_SuiDesigner3d_w3e$TrackValue);

	// init by super vtable init function
    Vtable_SuiDesigner3d_w3e$TrackValue_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner3d_w3e$TrackValue;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$TrackFloat_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$TrackFloat";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$TrackFloat_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$TrackFloat_fini(SuiDesigner3d_w3e$TrackFloat *self){
	//super fini
    SuiDesigner3d_w3e$TrackValue_fini((SuiDesigner3d_w3e$TrackValue *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner3d_w3e$TrackFloat_init_fields(SuiDesigner3d_w3e$TrackFloat *self){
	//super class
    SuiDesigner3d_w3e$TrackValue_init_fields((SuiDesigner3d_w3e$TrackValue*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$TrackFloat_fini;
	//fields
    {
	
    }
	((SuiDesigner3d_w3e$TrackValue*)self)->toString = (void*)SuiDesigner3d_w3e$TrackFloat$toString;
}

// init function

void SuiDesigner3d_w3e$TrackFloat_init(SuiDesigner3d_w3e$TrackFloat *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$TrackFloat_init(&_vtable_SuiDesigner3d_w3e$TrackFloat);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$TrackFloat;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$TrackFloat_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$TrackFloat * SuiDesigner3d_w3e$TrackFloat_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$TrackFloat *self = calloc(1, sizeof(SuiDesigner3d_w3e$TrackFloat));
	
    SuiDesigner3d_w3e$TrackFloat_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiDesigner3d_w3e$TrackFloat$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$TrackFloat *  self){
	char  tmp[128];
	sprintf(tmp, "%d|%f", ((SuiDesigner3d_w3e$TrackValue * )self)->frame, self->value) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$TrackVec3 _vtable_SuiDesigner3d_w3e$TrackVec3;

// init meta

void SuiDesigner3d_w3e$TrackVec3_initMeta(Vtable_SuiDesigner3d_w3e$TrackVec3 *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "value", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$TrackVec3, value), false, false, 0);
	orc_metaField_struct(&pNext, "inTan", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$TrackVec3, inTan), false, false, 0);
	orc_metaField_struct(&pNext, "outTan", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$TrackVec3, outTan), false, false, 0);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$TrackVec3* Vtable_SuiDesigner3d_w3e$TrackVec3_init(Vtable_SuiDesigner3d_w3e$TrackVec3* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$TrackVec3;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner3d_w3e$TrackValue_init(&_vtable_SuiDesigner3d_w3e$TrackValue);

	// init by super vtable init function
    Vtable_SuiDesigner3d_w3e$TrackValue_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner3d_w3e$TrackValue;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$TrackVec3_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$TrackVec3";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$TrackVec3_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$TrackVec3_fini(SuiDesigner3d_w3e$TrackVec3 *self){
	//super fini
    SuiDesigner3d_w3e$TrackValue_fini((SuiDesigner3d_w3e$TrackValue *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner3d_w3e$TrackVec3_init_fields(SuiDesigner3d_w3e$TrackVec3 *self){
	//super class
    SuiDesigner3d_w3e$TrackValue_init_fields((SuiDesigner3d_w3e$TrackValue*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$TrackVec3_fini;
	//fields
    {
	
    }
	((SuiDesigner3d_w3e$TrackValue*)self)->toString = (void*)SuiDesigner3d_w3e$TrackVec3$toString;
}

// init function

void SuiDesigner3d_w3e$TrackVec3_init(SuiDesigner3d_w3e$TrackVec3 *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$TrackVec3_init(&_vtable_SuiDesigner3d_w3e$TrackVec3);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$TrackVec3;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$TrackVec3_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$TrackVec3 * SuiDesigner3d_w3e$TrackVec3_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$TrackVec3 *self = calloc(1, sizeof(SuiDesigner3d_w3e$TrackVec3));
	
    SuiDesigner3d_w3e$TrackVec3_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiDesigner3d_w3e$TrackVec3$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$TrackVec3 *  self){
	char  tmp[128];
	sprintf(tmp, "%d|Vec3(%f,%f,%f)", ((SuiDesigner3d_w3e$TrackValue * )self)->frame, self->value.x, self->value.y, self->value.z) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$TrackQuat _vtable_SuiDesigner3d_w3e$TrackQuat;

// init meta

void SuiDesigner3d_w3e$TrackQuat_initMeta(Vtable_SuiDesigner3d_w3e$TrackQuat *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "value", SuiCore$Quat_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$TrackQuat, value), false, false, 0);
	orc_metaField_struct(&pNext, "inTan", SuiCore$Quat_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$TrackQuat, inTan), false, false, 0);
	orc_metaField_struct(&pNext, "outTan", SuiCore$Quat_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$TrackQuat, outTan), false, false, 0);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$TrackQuat* Vtable_SuiDesigner3d_w3e$TrackQuat_init(Vtable_SuiDesigner3d_w3e$TrackQuat* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$TrackQuat;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_SuiDesigner3d_w3e$TrackValue_init(&_vtable_SuiDesigner3d_w3e$TrackValue);

	// init by super vtable init function
    Vtable_SuiDesigner3d_w3e$TrackValue_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_SuiDesigner3d_w3e$TrackValue;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$TrackQuat_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$TrackQuat";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$TrackQuat_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$TrackQuat_fini(SuiDesigner3d_w3e$TrackQuat *self){
	//super fini
    SuiDesigner3d_w3e$TrackValue_fini((SuiDesigner3d_w3e$TrackValue *)self);

    //字段释放
	

}

// init fields function


void SuiDesigner3d_w3e$TrackQuat_init_fields(SuiDesigner3d_w3e$TrackQuat *self){
	//super class
    SuiDesigner3d_w3e$TrackValue_init_fields((SuiDesigner3d_w3e$TrackValue*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$TrackQuat_fini;
	//fields
    {
	
    }
	((SuiDesigner3d_w3e$TrackValue*)self)->toString = (void*)SuiDesigner3d_w3e$TrackQuat$toString;
}

// init function

void SuiDesigner3d_w3e$TrackQuat_init(SuiDesigner3d_w3e$TrackQuat *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$TrackQuat_init(&_vtable_SuiDesigner3d_w3e$TrackQuat);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$TrackQuat;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$TrackQuat_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$TrackQuat * SuiDesigner3d_w3e$TrackQuat_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$TrackQuat *self = calloc(1, sizeof(SuiDesigner3d_w3e$TrackQuat));
	
    SuiDesigner3d_w3e$TrackQuat_init(self, pOwner);
    return self;
}


// class members
Orc$String*  SuiDesigner3d_w3e$TrackQuat$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$TrackQuat *  self){
	char  tmp[128];
	sprintf(tmp, "%d|Quat(%f,%f,%f,%f)", ((SuiDesigner3d_w3e$TrackValue * )self)->frame, self->value.x, self->value.y, self->value.z, self->value.w) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_1, tmp) ) ; 
}




// get or init meta 
MetaStruct* SuiDesigner3d_w3e$TrackValueRange_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiDesigner3d_w3e$TrackValueRange", sizeof( SuiDesigner3d_w3e$TrackValueRange ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_class(&pNext, "left", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackValue_init(0)), offsetof(SuiDesigner3d_w3e$TrackValueRange, left), false, true, 1);
		orc_metaField_class(&pNext, "right", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackValue_init(0)), offsetof(SuiDesigner3d_w3e$TrackValueRange, right), false, true, 1);
		orc_metaField_primitive(&pNext, "frame", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TrackValueRange, frame), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "ratio", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$TrackValueRange, ratio), 0, 0, 0, 0);//float
    }
	return meta;
}
Orc$String*  SuiDesigner3d_w3e$TrackValueRange$toString(Orc$String **  __outRef__, SuiDesigner3d_w3e$TrackValueRange *  self){
	char  tmp[512];
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	sprintf(tmp, "[%s, %s, f=%d, t=%f]", self->left ? self->left->toString(&tmpReturn_1, self->left) ->str : "null", self->right ? self->right->toString(&tmpReturn_2, self->right) ->str : "null", self->frame, self->ratio) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	return urgc_set_var_for_return_class((void ** )__outRef__, Orc$str(&tmpReturn_3, tmp) ) ; 
}

float  SuiDesigner3d_w3e$TrackValueRange$calcRatio(SuiDesigner3d_w3e$TrackValueRange *  self){
	float  r = Orc$calcRatio(self->frame, self->left->frame, self->right->frame) ;
	self->ratio = Orc$clampFloat(r, 0, 1) ;
	return r; 
}

int  SuiDesigner3d_w3e$TrackValueRange$lerpInt(SuiDesigner3d_w3e$TrackValueRange *  self){
	float  ratio = SuiDesigner3d_w3e$TrackValueRange$calcRatio(self) ;
	SuiDesigner3d_w3e$TrackInt *  a = (SuiDesigner3d_w3e$TrackInt * )self->left;
	SuiDesigner3d_w3e$TrackInt *  b = (SuiDesigner3d_w3e$TrackInt * )self->right;
	float  val = Orc$lerpFloat(a->value, b->value, ratio) ;
	return (int )val; 
}

int  SuiDesigner3d_w3e$TrackValueRange$lerpFloat(SuiDesigner3d_w3e$TrackValueRange *  self){
	float  ratio = SuiDesigner3d_w3e$TrackValueRange$calcRatio(self) ;
	SuiDesigner3d_w3e$TrackFloat *  a = (SuiDesigner3d_w3e$TrackFloat * )self->left;
	SuiDesigner3d_w3e$TrackFloat *  b = (SuiDesigner3d_w3e$TrackFloat * )self->right;
	float  val = Orc$lerpFloat(a->value, b->value, ratio) ;
	return val; 
}

SuiCore$Vec3 SuiDesigner3d_w3e$TrackValueRange$lerpVec3(SuiDesigner3d_w3e$TrackValueRange *  self){
	float  ratio = SuiDesigner3d_w3e$TrackValueRange$calcRatio(self) ;
	SuiDesigner3d_w3e$TrackVec3 *  a = (SuiDesigner3d_w3e$TrackVec3 * )self->left;
	SuiDesigner3d_w3e$TrackVec3 *  b = (SuiDesigner3d_w3e$TrackVec3 * )self->right;
	SuiCore$Vec3 val = SuiCore$Vec3$lerp(&a->value, b->value, ratio) ;
	return val; 
}

SuiCore$Quat SuiDesigner3d_w3e$TrackValueRange$slerpQuat(SuiDesigner3d_w3e$TrackValueRange *  self){
	float  ratio = SuiDesigner3d_w3e$TrackValueRange$calcRatio(self) ;
	SuiDesigner3d_w3e$TrackQuat *  a = (SuiDesigner3d_w3e$TrackQuat * )self->left;
	SuiDesigner3d_w3e$TrackQuat *  b = (SuiDesigner3d_w3e$TrackQuat * )self->right;
	SuiCore$Quat val = SuiCore$Quat$slerp(&a->value, b->value, ratio) ;
	return val; 
}

SuiCore$Quat SuiDesigner3d_w3e$TrackValueRange$lerpQuat(SuiDesigner3d_w3e$TrackValueRange *  self){
	float  ratio = SuiDesigner3d_w3e$TrackValueRange$calcRatio(self) ;
	SuiDesigner3d_w3e$TrackQuat *  a = (SuiDesigner3d_w3e$TrackQuat * )self->left;
	SuiDesigner3d_w3e$TrackQuat *  b = (SuiDesigner3d_w3e$TrackQuat * )self->right;
	SuiCore$Quat val = SuiCore$Quat$lerp(&a->value, b->value, ratio) ;
	return val; 
}


//vtable instance
Vtable_SuiDesigner3d_w3e$TrackHeader _vtable_SuiDesigner3d_w3e$TrackHeader;

// init meta

void SuiDesigner3d_w3e$TrackHeader_initMeta(Vtable_SuiDesigner3d_w3e$TrackHeader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "globalSeqId", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TrackHeader, globalSeqId), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "tracks", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$TrackHeader, tracks), true, false, 1);
	orc_metaField_primitive(&pNext, "id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$TrackHeader, id), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "findNearestLeft", offsetof(SuiDesigner3d_w3e$TrackHeader, findNearestLeft));
	orc_metaField_method(&pNext, "findNearestRight", offsetof(SuiDesigner3d_w3e$TrackHeader, findNearestRight));
	orc_metaField_method(&pNext, "findTrackValueRange", offsetof(SuiDesigner3d_w3e$TrackHeader, findTrackValueRange));
}


// vtable init


Vtable_SuiDesigner3d_w3e$TrackHeader* Vtable_SuiDesigner3d_w3e$TrackHeader_init(Vtable_SuiDesigner3d_w3e$TrackHeader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$TrackHeader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$TrackHeader_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$TrackHeader";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$TrackHeader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$TrackHeader_fini(SuiDesigner3d_w3e$TrackHeader *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$TrackHeader*)self)->tracks);

}

// init fields function


void SuiDesigner3d_w3e$TrackHeader_init_fields(SuiDesigner3d_w3e$TrackHeader *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$TrackHeader_fini;
	//fields
    {
	((SuiDesigner3d_w3e$TrackHeader*)self)->interpolationType = SuiDesigner3d_w3e$InterpolationType_none;
	((SuiDesigner3d_w3e$TrackHeader*)self)->globalSeqId = SuiDesigner3d_w3e$INVALID_INDEX;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$TrackHeader*)self)->tracks, Orc$List_new(&tmpNewOwner_1) );
	((SuiDesigner3d_w3e$TrackHeader*)self)->id = SuiDesigner3d_w3e$INVALID_INDEX;
    }
	((SuiDesigner3d_w3e$TrackHeader*)self)->findNearestLeft = (void*)SuiDesigner3d_w3e$TrackHeader$findNearestLeft;
	((SuiDesigner3d_w3e$TrackHeader*)self)->findNearestRight = (void*)SuiDesigner3d_w3e$TrackHeader$findNearestRight;
	((SuiDesigner3d_w3e$TrackHeader*)self)->findTrackValueRange = (void*)SuiDesigner3d_w3e$TrackHeader$findTrackValueRange;
}

// init function

void SuiDesigner3d_w3e$TrackHeader_init(SuiDesigner3d_w3e$TrackHeader *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$TrackHeader_init(&_vtable_SuiDesigner3d_w3e$TrackHeader);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$TrackHeader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$TrackHeader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$TrackHeader * SuiDesigner3d_w3e$TrackHeader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$TrackHeader *self = calloc(1, sizeof(SuiDesigner3d_w3e$TrackHeader));
	
    SuiDesigner3d_w3e$TrackHeader_init(self, pOwner);
    return self;
}


// class members
SuiDesigner3d_w3e$TrackValue *  SuiDesigner3d_w3e$TrackHeader$findNearestLeft(SuiDesigner3d_w3e$TrackHeader *  self, int  frame){
	for (int  i = self->tracks->size(self->tracks)  - 1; i >= 0; i--) {
		SuiDesigner3d_w3e$TrackValue *  tv = (SuiDesigner3d_w3e$TrackValue * )self->tracks->get(self->tracks, i) ;
		if (tv->frame <= frame) {
			return tv; 
		}
	}
	return NULL; 
}


SuiDesigner3d_w3e$TrackValue *  SuiDesigner3d_w3e$TrackHeader$findNearestRight(SuiDesigner3d_w3e$TrackHeader *  self, int  frame){
	for (int  i = 0; i < self->tracks->size(self->tracks) ; i++) {
		SuiDesigner3d_w3e$TrackValue *  tv = (SuiDesigner3d_w3e$TrackValue * )self->tracks->get(self->tracks, i) ;
		if (tv->frame >= frame) {
			return tv; 
		}
	}
	return NULL; 
}


SuiDesigner3d_w3e$TrackValueRange SuiDesigner3d_w3e$TrackHeader$findTrackValueRange(SuiDesigner3d_w3e$TrackHeader *  self, int  frame, SuiDesigner3d_w3e$Sequence *  seq){
	SuiDesigner3d_w3e$TrackValueRange r;
	memset(&r, 0, sizeof(SuiDesigner3d_w3e$TrackValueRange) ) ;
	SuiDesigner3d_w3e$TrackValue *  left = self->findNearestLeft(self, frame) ;
	SuiDesigner3d_w3e$TrackValue *  right = self->findNearestRight(self, frame) ;
	r.frame = frame;
	r.left = left == NULL ? right : left;
	r.right = right == NULL ? left : right;
	if (r.left == NULL) {
		r.left = r.right;
	}
	if (r.right == NULL) {
		r.right = r.left;
	}
	return r; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$MdxNode _vtable_SuiDesigner3d_w3e$MdxNode;

// init meta

void SuiDesigner3d_w3e$MdxNode_initMeta(Vtable_SuiDesigner3d_w3e$MdxNode *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$MdxNode, name), true, false, 1);
	orc_metaField_primitive(&pNext, "id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxNode, id), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "parentId", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxNode, parentId), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "flags", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxNode, flags), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "KGTR", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxNode, KGTR), true, false, 1);
	orc_metaField_class(&pNext, "KGRT", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxNode, KGRT), true, false, 1);
	orc_metaField_class(&pNext, "KGSC", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$MdxNode, KGSC), true, false, 1);
	orc_metaField_class(&pNext, "bone", ((Vtable_Object*)Vtable_Sgl$Bone_init(0)), offsetof(SuiDesigner3d_w3e$MdxNode, bone), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$MdxNode* Vtable_SuiDesigner3d_w3e$MdxNode_init(Vtable_SuiDesigner3d_w3e$MdxNode* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$MdxNode;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$MdxNode_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$MdxNode";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$MdxNode_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$MdxNode_fini(SuiDesigner3d_w3e$MdxNode *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->name);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->KGTR);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->KGRT);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->KGSC);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->bone);

}

// init fields function


void SuiDesigner3d_w3e$MdxNode_init_fields(SuiDesigner3d_w3e$MdxNode *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$MdxNode_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->name, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->KGTR, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->KGRT, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->KGSC, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxNode*)self)->bone, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$MdxNode_init(SuiDesigner3d_w3e$MdxNode *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$MdxNode_init(&_vtable_SuiDesigner3d_w3e$MdxNode);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$MdxNode;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$MdxNode_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$MdxNode * SuiDesigner3d_w3e$MdxNode_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$MdxNode *self = calloc(1, sizeof(SuiDesigner3d_w3e$MdxNode));
	
    SuiDesigner3d_w3e$MdxNode_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$Attachment _vtable_SuiDesigner3d_w3e$Attachment;

// init meta

void SuiDesigner3d_w3e$Attachment_initMeta(Vtable_SuiDesigner3d_w3e$Attachment *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "node", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$MdxNode_init(0)), offsetof(SuiDesigner3d_w3e$Attachment, node), true, false, 1);
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$Attachment, path), true, false, 1);
	orc_metaField_primitive(&pNext, "reserved", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Attachment, reserved), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "attachment_id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Attachment, attachment_id), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "KATV", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$Attachment, KATV), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$Attachment* Vtable_SuiDesigner3d_w3e$Attachment_init(Vtable_SuiDesigner3d_w3e$Attachment* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$Attachment;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$Attachment_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$Attachment";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$Attachment_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$Attachment_fini(SuiDesigner3d_w3e$Attachment *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Attachment*)self)->node);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Attachment*)self)->path);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Attachment*)self)->KATV);

}

// init fields function


void SuiDesigner3d_w3e$Attachment_init_fields(SuiDesigner3d_w3e$Attachment *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$Attachment_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Attachment*)self)->node, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Attachment*)self)->path, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Attachment*)self)->KATV, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$Attachment_init(SuiDesigner3d_w3e$Attachment *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$Attachment_init(&_vtable_SuiDesigner3d_w3e$Attachment);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$Attachment;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$Attachment_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$Attachment * SuiDesigner3d_w3e$Attachment_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$Attachment *self = calloc(1, sizeof(SuiDesigner3d_w3e$Attachment));
	
    SuiDesigner3d_w3e$Attachment_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$EventObject _vtable_SuiDesigner3d_w3e$EventObject;

// init meta

void SuiDesigner3d_w3e$EventObject_initMeta(Vtable_SuiDesigner3d_w3e$EventObject *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "node", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$MdxNode_init(0)), offsetof(SuiDesigner3d_w3e$EventObject, node), true, false, 1);
	orc_metaField_primitive(&pNext, "globalSeqId", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$EventObject, globalSeqId), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "times", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner3d_w3e$EventObject, times), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$EventObject* Vtable_SuiDesigner3d_w3e$EventObject_init(Vtable_SuiDesigner3d_w3e$EventObject* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$EventObject;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$EventObject_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$EventObject";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$EventObject_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$EventObject_fini(SuiDesigner3d_w3e$EventObject *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$EventObject*)self)->node);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$EventObject*)self)->times);

}

// init fields function


void SuiDesigner3d_w3e$EventObject_init_fields(SuiDesigner3d_w3e$EventObject *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$EventObject_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$EventObject*)self)->node, NULL);
	((SuiDesigner3d_w3e$EventObject*)self)->globalSeqId = SuiDesigner3d_w3e$INVALID_INDEX;
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$EventObject*)self)->times, Sgl$IntArray_new(&tmpNewOwner_1) );
    }
	
}

// init function

void SuiDesigner3d_w3e$EventObject_init(SuiDesigner3d_w3e$EventObject *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$EventObject_init(&_vtable_SuiDesigner3d_w3e$EventObject);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$EventObject;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$EventObject_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$EventObject * SuiDesigner3d_w3e$EventObject_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$EventObject *self = calloc(1, sizeof(SuiDesigner3d_w3e$EventObject));
	
    SuiDesigner3d_w3e$EventObject_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$GeosetAnimation _vtable_SuiDesigner3d_w3e$GeosetAnimation;

// init meta

void SuiDesigner3d_w3e$GeosetAnimation_initMeta(Vtable_SuiDesigner3d_w3e$GeosetAnimation *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "alpha", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$GeosetAnimation, alpha), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "flags", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$GeosetAnimation, flags), 0, 0, 0, 0);//int
	orc_metaField_struct(&pNext, "color", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$GeosetAnimation, color), false, false, 0);
	orc_metaField_primitive(&pNext, "geoset_id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$GeosetAnimation, geoset_id), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "KGAO", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$GeosetAnimation, KGAO), true, false, 1);
	orc_metaField_class(&pNext, "KGAC", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$TrackHeader_init(0)), offsetof(SuiDesigner3d_w3e$GeosetAnimation, KGAC), true, false, 1);

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$GeosetAnimation* Vtable_SuiDesigner3d_w3e$GeosetAnimation_init(Vtable_SuiDesigner3d_w3e$GeosetAnimation* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$GeosetAnimation;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$GeosetAnimation_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$GeosetAnimation";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$GeosetAnimation_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$GeosetAnimation_fini(SuiDesigner3d_w3e$GeosetAnimation *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$GeosetAnimation*)self)->KGAO);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$GeosetAnimation*)self)->KGAC);

}

// init fields function


void SuiDesigner3d_w3e$GeosetAnimation_init_fields(SuiDesigner3d_w3e$GeosetAnimation *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$GeosetAnimation_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$GeosetAnimation*)self)->KGAO, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$GeosetAnimation*)self)->KGAC, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$GeosetAnimation_init(SuiDesigner3d_w3e$GeosetAnimation *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$GeosetAnimation_init(&_vtable_SuiDesigner3d_w3e$GeosetAnimation);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$GeosetAnimation;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$GeosetAnimation_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$GeosetAnimation * SuiDesigner3d_w3e$GeosetAnimation_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$GeosetAnimation *self = calloc(1, sizeof(SuiDesigner3d_w3e$GeosetAnimation));
	
    SuiDesigner3d_w3e$GeosetAnimation_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$Geoset _vtable_SuiDesigner3d_w3e$Geoset;

// init meta

void SuiDesigner3d_w3e$Geoset_initMeta(Vtable_SuiDesigner3d_w3e$Geoset *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "geom", ((Vtable_Object*)Vtable_Sgl$Geometry_init(0)), offsetof(SuiDesigner3d_w3e$Geoset, geom), true, false, 1);
	orc_metaField_class(&pNext, "matrix_indices", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner3d_w3e$Geoset, matrix_indices), true, false, 1);
	orc_metaField_class(&pNext, "matrix_group", ((Vtable_Object*)Vtable_Sgl$IntArray_init(0)), offsetof(SuiDesigner3d_w3e$Geoset, matrix_group), true, false, 1);
	orc_metaField_class(&pNext, "vertex_groups", ((Vtable_Object*)Vtable_Sgl$CharArray_init(0)), offsetof(SuiDesigner3d_w3e$Geoset, vertex_groups), true, false, 1);
	orc_metaField_primitive(&pNext, "material_id", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$Geoset, material_id), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiDesigner3d_w3e$Geoset* Vtable_SuiDesigner3d_w3e$Geoset_init(Vtable_SuiDesigner3d_w3e$Geoset* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$Geoset;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$Geoset_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$Geoset";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$Geoset_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$Geoset_fini(SuiDesigner3d_w3e$Geoset *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->geom);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->matrix_indices);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->matrix_group);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->vertex_groups);

}

// init fields function


void SuiDesigner3d_w3e$Geoset_init_fields(SuiDesigner3d_w3e$Geoset *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$Geoset_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->geom, Sgl$Geometry_new(&tmpNewOwner_1) );
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->matrix_indices, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->matrix_group, NULL);
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$Geoset*)self)->vertex_groups, NULL);
    }
	
}

// init function

void SuiDesigner3d_w3e$Geoset_init(SuiDesigner3d_w3e$Geoset *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$Geoset_init(&_vtable_SuiDesigner3d_w3e$Geoset);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$Geoset;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$Geoset_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$Geoset * SuiDesigner3d_w3e$Geoset_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$Geoset *self = calloc(1, sizeof(SuiDesigner3d_w3e$Geoset));
	
    SuiDesigner3d_w3e$Geoset_init(self, pOwner);
    return self;
}


// class members


//vtable instance
Vtable_SuiDesigner3d_w3e$MdxReader _vtable_SuiDesigner3d_w3e$MdxReader;

// init meta

void SuiDesigner3d_w3e$MdxReader_initMeta(Vtable_SuiDesigner3d_w3e$MdxReader *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "version", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxReader, version), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "unique_tracks", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$MdxReader, unique_tracks), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "matls", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, matls), true, false, 1);
	orc_metaField_class(&pNext, "geosets", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, geosets), true, false, 1);
	orc_metaField_class(&pNext, "texs", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, texs), true, false, 1);
	orc_metaField_class(&pNext, "pivots", ((Vtable_Object*)Vtable_Sgl$Vec3Array_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, pivots), true, false, 1);
	orc_metaField_class(&pNext, "helps", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, helps), true, false, 1);
	orc_metaField_class(&pNext, "bones", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, bones), true, false, 1);
	orc_metaField_class(&pNext, "lights", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, lights), true, false, 1);
	orc_metaField_class(&pNext, "seqs", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, seqs), true, false, 1);
	orc_metaField_class(&pNext, "globalSeqs", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, globalSeqs), true, false, 1);
	orc_metaField_class(&pNext, "geosetAnimations", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, geosetAnimations), true, false, 1);
	orc_metaField_class(&pNext, "attachments", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, attachments), true, false, 1);
	orc_metaField_class(&pNext, "cornEmitters", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, cornEmitters), true, false, 1);
	orc_metaField_class(&pNext, "events", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, events), true, false, 1);
	orc_metaField_class(&pNext, "collisionShapes", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, collisionShapes), true, false, 1);
	orc_metaField_class(&pNext, "faceFxList", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, faceFxList), true, false, 1);
	orc_metaField_class(&pNext, "bindPose", ((Vtable_Object*)Vtable_Sgl$Vec3Array_init(0)), offsetof(SuiDesigner3d_w3e$MdxReader, bindPose), true, false, 1);

	orc_metaField_method(&pNext, "readTextureData", offsetof(SuiDesigner3d_w3e$MdxReader, readTextureData));
	orc_metaField_method(&pNext, "readSequence", offsetof(SuiDesigner3d_w3e$MdxReader, readSequence));
	orc_metaField_method(&pNext, "readExtend", offsetof(SuiDesigner3d_w3e$MdxReader, readExtend));
	orc_metaField_method(&pNext, "readLITE", offsetof(SuiDesigner3d_w3e$MdxReader, readLITE));
	orc_metaField_method(&pNext, "readMTLS", offsetof(SuiDesigner3d_w3e$MdxReader, readMTLS));
	orc_metaField_method(&pNext, "read_MTLS_texs_pre_v1100", offsetof(SuiDesigner3d_w3e$MdxReader, read_MTLS_texs_pre_v1100));
	orc_metaField_method(&pNext, "read_MTLS_texs_post_v1100", offsetof(SuiDesigner3d_w3e$MdxReader, read_MTLS_texs_post_v1100));
	orc_metaField_method(&pNext, "readGEOA", offsetof(SuiDesigner3d_w3e$MdxReader, readGEOA));
	orc_metaField_method(&pNext, "readTEXS", offsetof(SuiDesigner3d_w3e$MdxReader, readTEXS));
	orc_metaField_method(&pNext, "readSEQS", offsetof(SuiDesigner3d_w3e$MdxReader, readSEQS));
	orc_metaField_method(&pNext, "readGLBS", offsetof(SuiDesigner3d_w3e$MdxReader, readGLBS));
	orc_metaField_method(&pNext, "mkBoneIndices", offsetof(SuiDesigner3d_w3e$MdxReader, mkBoneIndices));
	orc_metaField_method(&pNext, "readGEOS", offsetof(SuiDesigner3d_w3e$MdxReader, readGEOS));
	orc_metaField_method(&pNext, "readBONE", offsetof(SuiDesigner3d_w3e$MdxReader, readBONE));
	orc_metaField_method(&pNext, "readHELP", offsetof(SuiDesigner3d_w3e$MdxReader, readHELP));
	orc_metaField_method(&pNext, "readATCH", offsetof(SuiDesigner3d_w3e$MdxReader, readATCH));
	orc_metaField_method(&pNext, "readCORN", offsetof(SuiDesigner3d_w3e$MdxReader, readCORN));
	orc_metaField_method(&pNext, "readEVTS", offsetof(SuiDesigner3d_w3e$MdxReader, readEVTS));
	orc_metaField_method(&pNext, "readCLID", offsetof(SuiDesigner3d_w3e$MdxReader, readCLID));
	orc_metaField_method(&pNext, "readTrackHeaderQuat", offsetof(SuiDesigner3d_w3e$MdxReader, readTrackHeaderQuat));
	orc_metaField_method(&pNext, "readTrackHeaderVec3", offsetof(SuiDesigner3d_w3e$MdxReader, readTrackHeaderVec3));
	orc_metaField_method(&pNext, "readTrackHeaderInt", offsetof(SuiDesigner3d_w3e$MdxReader, readTrackHeaderInt));
	orc_metaField_method(&pNext, "readTrackHeaderFloat", offsetof(SuiDesigner3d_w3e$MdxReader, readTrackHeaderFloat));
	orc_metaField_method(&pNext, "readNode", offsetof(SuiDesigner3d_w3e$MdxReader, readNode));
	orc_metaField_method(&pNext, "readPIVT", offsetof(SuiDesigner3d_w3e$MdxReader, readPIVT));
	orc_metaField_method(&pNext, "readFAFX", offsetof(SuiDesigner3d_w3e$MdxReader, readFAFX));
	orc_metaField_method(&pNext, "readCAMS", offsetof(SuiDesigner3d_w3e$MdxReader, readCAMS));
	orc_metaField_method(&pNext, "readTXAN", offsetof(SuiDesigner3d_w3e$MdxReader, readTXAN));
	orc_metaField_method(&pNext, "readBPOS", offsetof(SuiDesigner3d_w3e$MdxReader, readBPOS));
	orc_metaField_method(&pNext, "load", offsetof(SuiDesigner3d_w3e$MdxReader, load));
	orc_metaField_method(&pNext, "loadByPathCstr", offsetof(SuiDesigner3d_w3e$MdxReader, loadByPathCstr));
}


// vtable init


Vtable_SuiDesigner3d_w3e$MdxReader* Vtable_SuiDesigner3d_w3e$MdxReader_init(Vtable_SuiDesigner3d_w3e$MdxReader* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$MdxReader;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$MdxReader_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$MdxReader";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$MdxReader_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$MdxReader_fini(SuiDesigner3d_w3e$MdxReader *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->matls);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->geosets);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->texs);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->pivots);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->helps);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->bones);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->lights);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->seqs);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->globalSeqs);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->geosetAnimations);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->attachments);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->cornEmitters);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->events);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->collisionShapes);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->faceFxList);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->bindPose);

}

// init fields function


void SuiDesigner3d_w3e$MdxReader_init_fields(SuiDesigner3d_w3e$MdxReader *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$MdxReader_fini;
	//fields
    {
	((SuiDesigner3d_w3e$MdxReader*)self)->version = 0;
	((SuiDesigner3d_w3e$MdxReader*)self)->unique_tracks = 0;
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->matls, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->geosets, Orc$List_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->texs, Orc$List_new(&tmpNewOwner_3) );
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->pivots, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->helps, Orc$List_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->bones, Orc$List_new(&tmpNewOwner_5) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_6 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->lights, Orc$List_new(&tmpNewOwner_6) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_7 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->seqs, Orc$List_new(&tmpNewOwner_7) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_8 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->globalSeqs, Orc$List_new(&tmpNewOwner_8) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_9 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->geosetAnimations, Orc$List_new(&tmpNewOwner_9) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_10 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->attachments, Orc$List_new(&tmpNewOwner_10) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_11 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->cornEmitters, Orc$List_new(&tmpNewOwner_11) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_12 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->events, Orc$List_new(&tmpNewOwner_12) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_13 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->collisionShapes, Orc$List_new(&tmpNewOwner_13) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_14 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->faceFxList, Orc$List_new(&tmpNewOwner_14) );
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MdxReader*)self)->bindPose, NULL);
    }
	((SuiDesigner3d_w3e$MdxReader*)self)->readTextureData = (void*)SuiDesigner3d_w3e$MdxReader$readTextureData;
	((SuiDesigner3d_w3e$MdxReader*)self)->readSequence = (void*)SuiDesigner3d_w3e$MdxReader$readSequence;
	((SuiDesigner3d_w3e$MdxReader*)self)->readExtend = (void*)SuiDesigner3d_w3e$MdxReader$readExtend;
	((SuiDesigner3d_w3e$MdxReader*)self)->readLITE = (void*)SuiDesigner3d_w3e$MdxReader$readLITE;
	((SuiDesigner3d_w3e$MdxReader*)self)->readMTLS = (void*)SuiDesigner3d_w3e$MdxReader$readMTLS;
	((SuiDesigner3d_w3e$MdxReader*)self)->read_MTLS_texs_pre_v1100 = (void*)SuiDesigner3d_w3e$MdxReader$read_MTLS_texs_pre_v1100;
	((SuiDesigner3d_w3e$MdxReader*)self)->read_MTLS_texs_post_v1100 = (void*)SuiDesigner3d_w3e$MdxReader$read_MTLS_texs_post_v1100;
	((SuiDesigner3d_w3e$MdxReader*)self)->readGEOA = (void*)SuiDesigner3d_w3e$MdxReader$readGEOA;
	((SuiDesigner3d_w3e$MdxReader*)self)->readTEXS = (void*)SuiDesigner3d_w3e$MdxReader$readTEXS;
	((SuiDesigner3d_w3e$MdxReader*)self)->readSEQS = (void*)SuiDesigner3d_w3e$MdxReader$readSEQS;
	((SuiDesigner3d_w3e$MdxReader*)self)->readGLBS = (void*)SuiDesigner3d_w3e$MdxReader$readGLBS;
	((SuiDesigner3d_w3e$MdxReader*)self)->mkBoneIndices = (void*)SuiDesigner3d_w3e$MdxReader$mkBoneIndices;
	((SuiDesigner3d_w3e$MdxReader*)self)->readGEOS = (void*)SuiDesigner3d_w3e$MdxReader$readGEOS;
	((SuiDesigner3d_w3e$MdxReader*)self)->readBONE = (void*)SuiDesigner3d_w3e$MdxReader$readBONE;
	((SuiDesigner3d_w3e$MdxReader*)self)->readHELP = (void*)SuiDesigner3d_w3e$MdxReader$readHELP;
	((SuiDesigner3d_w3e$MdxReader*)self)->readATCH = (void*)SuiDesigner3d_w3e$MdxReader$readATCH;
	((SuiDesigner3d_w3e$MdxReader*)self)->readCORN = (void*)SuiDesigner3d_w3e$MdxReader$readCORN;
	((SuiDesigner3d_w3e$MdxReader*)self)->readEVTS = (void*)SuiDesigner3d_w3e$MdxReader$readEVTS;
	((SuiDesigner3d_w3e$MdxReader*)self)->readCLID = (void*)SuiDesigner3d_w3e$MdxReader$readCLID;
	((SuiDesigner3d_w3e$MdxReader*)self)->readTrackHeaderQuat = (void*)SuiDesigner3d_w3e$MdxReader$readTrackHeaderQuat;
	((SuiDesigner3d_w3e$MdxReader*)self)->readTrackHeaderVec3 = (void*)SuiDesigner3d_w3e$MdxReader$readTrackHeaderVec3;
	((SuiDesigner3d_w3e$MdxReader*)self)->readTrackHeaderInt = (void*)SuiDesigner3d_w3e$MdxReader$readTrackHeaderInt;
	((SuiDesigner3d_w3e$MdxReader*)self)->readTrackHeaderFloat = (void*)SuiDesigner3d_w3e$MdxReader$readTrackHeaderFloat;
	((SuiDesigner3d_w3e$MdxReader*)self)->readNode = (void*)SuiDesigner3d_w3e$MdxReader$readNode;
	((SuiDesigner3d_w3e$MdxReader*)self)->readPIVT = (void*)SuiDesigner3d_w3e$MdxReader$readPIVT;
	((SuiDesigner3d_w3e$MdxReader*)self)->readFAFX = (void*)SuiDesigner3d_w3e$MdxReader$readFAFX;
	((SuiDesigner3d_w3e$MdxReader*)self)->readCAMS = (void*)SuiDesigner3d_w3e$MdxReader$readCAMS;
	((SuiDesigner3d_w3e$MdxReader*)self)->readTXAN = (void*)SuiDesigner3d_w3e$MdxReader$readTXAN;
	((SuiDesigner3d_w3e$MdxReader*)self)->readBPOS = (void*)SuiDesigner3d_w3e$MdxReader$readBPOS;
	((SuiDesigner3d_w3e$MdxReader*)self)->load = (void*)SuiDesigner3d_w3e$MdxReader$load;
	((SuiDesigner3d_w3e$MdxReader*)self)->loadByPathCstr = (void*)SuiDesigner3d_w3e$MdxReader$loadByPathCstr;
}

// init function

void SuiDesigner3d_w3e$MdxReader_init(SuiDesigner3d_w3e$MdxReader *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$MdxReader_init(&_vtable_SuiDesigner3d_w3e$MdxReader);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$MdxReader;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$MdxReader_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$MdxReader * SuiDesigner3d_w3e$MdxReader_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$MdxReader *self = calloc(1, sizeof(SuiDesigner3d_w3e$MdxReader));
	
    SuiDesigner3d_w3e$MdxReader_init(self, pOwner);
    return self;
}


// class members
SuiDesigner3d_w3e$TextureData*  SuiDesigner3d_w3e$MdxReader$readTextureData(SuiDesigner3d_w3e$TextureData **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader){
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TextureData*  r = (r=NULL,urgc_init_var_class((void**)&r, SuiDesigner3d_w3e$TextureData_new(&r) ));
	r->replaceableId = reader->readInt(reader) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(r, (void * )offsetof(SuiDesigner3d_w3e$TextureData, fileName) , reader->readString(&tmpReturn_1, reader, 256) ) ;
	reader->advance(reader, 4) ;
	int  flags = reader->readInt(reader) ;
	r->wrapWidth = flags & 1;
	r->wrapHeight = flags & 2;
	printf("\t\ttex. replaceableId:%d, fileName:%s, ww:%d, wh:%d, flags:%d. realPath:%s\n", r->replaceableId, r->fileName->str, r->wrapWidth, r->wrapHeight, flags, r->getRealPath(r) ) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


SuiDesigner3d_w3e$Sequence*  SuiDesigner3d_w3e$MdxReader$readSequence(SuiDesigner3d_w3e$Sequence **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader){
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$Sequence*  r = (r=NULL,urgc_init_var_class((void**)&r, SuiDesigner3d_w3e$Sequence_new(&r) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(r, (void * )offsetof(SuiDesigner3d_w3e$Sequence, name) , reader->readString(&tmpReturn_1, reader, 80) ) ;
	r->startFrame = reader->readInt(reader) ;
	r->endFrame = reader->readInt(reader) ;
	r->moveSpeed = reader->readFloat(reader) ;
	r->nonLooping = reader->readInt(reader)  == 1;
	r->rarity = reader->readFloat(reader) ;
	r->sync_point = reader->readInt(reader) ;
	r->extend = self->readExtend(self, reader) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


SuiDesigner3d_w3e$Extend SuiDesigner3d_w3e$MdxReader$readExtend(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader){
	SuiDesigner3d_w3e$Extend r;
	r.bounds_radius = reader->readFloat(reader) ;
	r.minimum = reader->readVec3(reader) ;
	r.maximum = reader->readVec3(reader) ;
	return r; 
}


void  SuiDesigner3d_w3e$MdxReader$readLITE(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  reader_pos = reader->index - 4;
	while (reader->index < reader_pos + size) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxLight*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$MdxLight_new(&e) ));
		self->lights->add(self->lights, e) ;
		int  node_reader_pos = reader->index;
		int  inclusive_size = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  tmpReturn_1 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, node) , self->readNode(&tmpReturn_1, self, reader) ) ;
		e->type = reader->readInt(reader) ;
		e->attenuation_start = reader->readFloat(reader) ;
		e->attenuation_end = reader->readFloat(reader) ;
		e->color = reader->readVec3(reader) ;
		e->intensity = reader->readFloat(reader) ;
		e->ambient_color = reader->readVec3(reader) ;
		e->ambient_intensity = reader->readFloat(reader) ;
		while (reader->index < node_reader_pos + inclusive_size) {
			char  tag[5];
			reader->readChars(reader, tag, 4, true) ;
			printf("\ttag:%s\n", tag) ;
			if (strcmp(tag, "KLAS") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_2 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, KLAS) , self->readTrackHeaderInt(&tmpReturn_2, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KLAE") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_3 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, KLAE) , self->readTrackHeaderInt(&tmpReturn_3, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KLAC") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_4 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, KLAC) , self->readTrackHeaderVec3(&tmpReturn_4, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KLAI") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_5 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, KLAI) , self->readTrackHeaderFloat(&tmpReturn_5, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KLBI") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_6 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, KLBI) , self->readTrackHeaderFloat(&tmpReturn_6, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KLBC") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_7 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, KLBC) , self->readTrackHeaderVec3(&tmpReturn_7, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KLAV") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_8 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxLight, KLAV) , self->readTrackHeaderFloat(&tmpReturn_8, self, reader, self->unique_tracks++) ) ;
			}
			else {
				printf("\tunknown tag:%s\n", tag) ;
			}
		}
	}
}


void  SuiDesigner3d_w3e$MdxReader$readMTLS(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  total_size = 0;
	while (total_size < size) {
		int  reader_pos = reader->index;
		int  inclusive_size = reader->readInt(reader) ;
		total_size += inclusive_size;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxMaterial*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$MdxMaterial_new(&e) ));
		self->matls->add(self->matls, e) ;
		e->priority_plane = reader->readInt(reader) ;
		e->flags = reader->readInt(reader) ;
		if (self->version < 1100) {
			bool  is_hd = false;
			if (self->version == 900 || self->version == 1000) {
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
				is_hd = !Orc$String$empty(reader->readString(&tmpReturn_1, reader, 80) ) ;
			}
			self->read_MTLS_texs_pre_v1100(self, reader, is_hd, e, self->unique_tracks++) ;
		}
		else {
			self->read_MTLS_texs_post_v1100(self, reader, e, self->unique_tracks++) ;
		}
	}
}


void  SuiDesigner3d_w3e$MdxReader$read_MTLS_texs_pre_v1100(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, bool  is_hd, SuiDesigner3d_w3e$MdxMaterial *  material, int  trackId){
	char  tag[5];
	reader->readChars(reader, tag, 4, true) ;
	printf("\t旧版 tag:%s. is_hd:%d\n", tag, is_hd) ;
	int  layers_count = reader->readInt(reader) ;
	if (is_hd) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$Layer*  layer = (layer=NULL,urgc_init_var_class((void**)&layer, SuiDesigner3d_w3e$Layer_new(&layer) ));
		layer->hd = is_hd;
		for (int  i = 0; i < layers_count; i++) {
			int  reader_pos = reader->index;
			int  size = reader->readInt(reader) ;
			if (i > 0) {
				reader->advance(reader, 8) ;
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$LayerTexture*  layer_texture = (layer_texture=NULL,urgc_init_var_class((void**)&layer_texture, SuiDesigner3d_w3e$LayerTexture_new(&layer_texture) ));
				layer_texture->id = reader->readInt(reader) ;
				layer->textures->add(layer->textures, layer_texture) ;
				reader->advance(reader, size - 16) ;
				continue;
			}
			layer->blend_mode = reader->readInt(reader) ;
			layer->shading_flags = reader->readInt(reader) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$LayerTexture*  layer_texture = (layer_texture=NULL,urgc_init_var_class((void**)&layer_texture, SuiDesigner3d_w3e$LayerTexture_new(&layer_texture) ));
			layer_texture->id = reader->readInt(reader) ;
			layer->textures->add(layer->textures, layer_texture) ;
			printf("\t\tlayer_texture.id:%d\n", layer_texture->id) ;
			layer->texture_animation_id = reader->readInt(reader) ;
			layer->coord_id = reader->readInt(reader) ;
			layer->alpha = reader->readFloat(reader) ;
			layer->emissive_gain = reader->readFloat(reader) ;
			layer->fresnel_color = reader->readVec3(reader) ;
			layer->fresnel_opacity = reader->readFloat(reader) ;
			layer->fresnel_team_color = reader->readFloat(reader) ;
			while (reader->index < reader_pos + size) {
				char  tag[5];
				reader->readChars(reader, tag, 4, true) ;
				printf("\ttag:%s\n", tag) ;
				if (strcmp(tag, "KMTF")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_1 = NULL;
					urgc_set_field_class(layer_texture, (void * )offsetof(SuiDesigner3d_w3e$LayerTexture, KMTF) , self->readTrackHeaderInt(&tmpReturn_1, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KMTA")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_2 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KMTA) , self->readTrackHeaderFloat(&tmpReturn_2, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KMTE")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_3 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KMTE) , self->readTrackHeaderFloat(&tmpReturn_3, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KFC3")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_4 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFC3) , self->readTrackHeaderVec3(&tmpReturn_4, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KFCA")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_5 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFCA) , self->readTrackHeaderFloat(&tmpReturn_5, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KFTC")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_6 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFTC) , self->readTrackHeaderFloat(&tmpReturn_6, self, reader, self->unique_tracks++) ) ;
				}
				else {
					printf("\tunknown tag:%s\n", tag) ;
				}
			}
		}
	}
	else {
		for (int  i = 0; i < layers_count; i++) {
			int  reader_pos = reader->index;
			int  size = reader->readInt(reader) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$Layer*  layer = (layer=NULL,urgc_init_var_class((void**)&layer, SuiDesigner3d_w3e$Layer_new(&layer) ));
			layer->hd = is_hd;
			material->layers->add(material->layers, layer) ;
			layer->blend_mode = reader->readInt(reader) ;
			layer->shading_flags = reader->readInt(reader) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$LayerTexture*  layer_texture = (layer_texture=NULL,urgc_init_var_class((void**)&layer_texture, SuiDesigner3d_w3e$LayerTexture_new(&layer_texture) ));
			layer_texture->id = reader->readInt(reader) ;
			layer->textures->add(layer->textures, layer_texture) ;
			layer->texture_animation_id = reader->readInt(reader) ;
			layer->coord_id = reader->readInt(reader) ;
			layer->alpha = reader->readFloat(reader) ;
			printf("\t\tlayer_texture.id:%d\n", layer_texture->id) ;
			printf("\t\tlayer.texture_animation_id:%d\n", layer->texture_animation_id) ;
			printf("\t\tlayer.coord_id:%d\n", layer->coord_id) ;
			printf("\t\tlayer.alpha:%f\n", layer->alpha) ;
			if (self->version > 800) {
				layer->emissive_gain = reader->readFloat(reader) ;
				layer->fresnel_color = reader->readVec3(reader) ;
				layer->fresnel_opacity = reader->readFloat(reader) ;
				layer->fresnel_team_color = reader->readFloat(reader) ;
			}
			while (reader->index < reader_pos + size) {
				char  tag[5];
				reader->readChars(reader, tag, 4, true) ;
				printf("\ttag:%s\n", tag) ;
				if (strcmp(tag, "KMTF")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_7 = NULL;
					urgc_set_field_class(layer_texture, (void * )offsetof(SuiDesigner3d_w3e$LayerTexture, KMTF) , self->readTrackHeaderInt(&tmpReturn_7, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KMTA")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_8 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KMTA) , self->readTrackHeaderFloat(&tmpReturn_8, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KMTE")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_9 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KMTE) , self->readTrackHeaderFloat(&tmpReturn_9, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KFC3")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_10 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFC3) , self->readTrackHeaderVec3(&tmpReturn_10, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KFCA")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_11 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFCA) , self->readTrackHeaderFloat(&tmpReturn_11, self, reader, self->unique_tracks++) ) ;
				}
				else if (strcmp(tag, "KFTC")  == 0) {
					URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_12 = NULL;
					urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFTC) , self->readTrackHeaderFloat(&tmpReturn_12, self, reader, self->unique_tracks++) ) ;
				}
				else {
					printf("\tunknown tag:%s\n", tag) ;
				}
			}
		}
	}
}


void  SuiDesigner3d_w3e$MdxReader$read_MTLS_texs_post_v1100(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, SuiDesigner3d_w3e$MdxMaterial *  material, int  trackId){
	char  tag[5];
	reader->readChars(reader, tag, 4, true) ;
	printf("\t新版>=v1100 tag:%s\n", tag) ;
	int  layers_count = reader->readInt(reader) ;
	for (int  i = 0; i < layers_count; i++) {
		int  reader_pos = reader->index;
		int  size = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$Layer*  layer = (layer=NULL,urgc_init_var_class((void**)&layer, SuiDesigner3d_w3e$Layer_new(&layer) ));
		layer->blend_mode = reader->readInt(reader) ;
		layer->shading_flags = reader->readInt(reader) ;
		reader->advance(reader, 4) ;
		layer->texture_animation_id = reader->readInt(reader) ;
		layer->coord_id = reader->readInt(reader) ;
		layer->alpha = reader->readFloat(reader) ;
		layer->emissive_gain = reader->readFloat(reader) ;
		layer->fresnel_color = reader->readVec3(reader) ;
		layer->fresnel_opacity = reader->readFloat(reader) ;
		layer->fresnel_team_color = reader->readFloat(reader) ;
		layer->hd = reader->readInt(reader) ;
		int  texs = reader->readInt(reader) ;
		for (int  j = 0; j < texs; j++) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$LayerTexture*  layer_texture = (layer_texture=NULL,urgc_init_var_class((void**)&layer_texture, SuiDesigner3d_w3e$LayerTexture_new(&layer_texture) ));
			layer_texture->id = reader->readInt(reader) ;
			int  slot = reader->readInt(reader) ;
			char  tag[5];
			reader->readChars(reader, tag, 4, true) ;
			if (strcmp(tag, "KMTF") ) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_1 = NULL;
				urgc_set_field_class(layer_texture, (void * )offsetof(SuiDesigner3d_w3e$LayerTexture, KMTF) , self->readTrackHeaderInt(&tmpReturn_1, self, reader, self->unique_tracks++) ) ;
			}
			else {
				reader->advance(reader, -4) ;
			}
			layer->textures->add(layer->textures, layer_texture) ;
		}
		while (reader->index < reader_pos + size) {
			char  tag[5];
			reader->readChars(reader, tag, 4, true) ;
			printf("\ttag:%s\n", tag) ;
			if (strcmp(tag, "KMTA")  == 0) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_2 = NULL;
				urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KMTA) , self->readTrackHeaderFloat(&tmpReturn_2, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KMTE")  == 0) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_3 = NULL;
				urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KMTE) , self->readTrackHeaderFloat(&tmpReturn_3, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KFC3")  == 0) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_4 = NULL;
				urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFC3) , self->readTrackHeaderVec3(&tmpReturn_4, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KFCA")  == 0) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_5 = NULL;
				urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFCA) , self->readTrackHeaderFloat(&tmpReturn_5, self, reader, self->unique_tracks++) ) ;
			}
			else if (strcmp(tag, "KFTC")  == 0) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_6 = NULL;
				urgc_set_field_class(layer, (void * )offsetof(SuiDesigner3d_w3e$Layer, KFTC) , self->readTrackHeaderFloat(&tmpReturn_6, self, reader, self->unique_tracks++) ) ;
			}
			else {
				printf("\tunknown tag:%s\n", tag) ;
			}
		}
	}
}


void  SuiDesigner3d_w3e$MdxReader$readGEOA(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  total_size = 0;
	while (total_size < size) {
		int  reader_pos = reader->index;
		int  inclusive_size = reader->readInt(reader) ;
		total_size += inclusive_size;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$GeosetAnimation*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$GeosetAnimation_new(&e) ));
		self->geosetAnimations->add(self->geosetAnimations, e) ;
		e->alpha = reader->readFloat(reader) ;
		e->flags = reader->readInt(reader) ;
		e->color = reader->readVec3(reader) ;
		e->geoset_id = reader->readInt(reader) ;
		printf("\talpha:%f\n", e->alpha) ;
		printf("\tflags:%d\n", e->flags) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("\tcolor:%s\n", SuiCore$Vec3$toString(&tmpReturn_1, &e->color) ->str) ;
		printf("\tgeoset_id:%d\n", e->geoset_id) ;
		while (reader->index < reader_pos + inclusive_size) {
			char  tag[5];
			reader->readChars(reader, tag, 4, true) ;
			printf("\t\ttag:%s\n", tag) ;
			if (strcmp(tag, "KGAO")  == 0) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_2 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$GeosetAnimation, KGAO) , self->readTrackHeaderFloat(&tmpReturn_2, self, reader, self->unique_tracks) ) ;
				self->unique_tracks++;
			}
			else if (strcmp(tag, "KGAC")  == 0) {
				URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_3 = NULL;
				urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$GeosetAnimation, KGAO) , self->readTrackHeaderVec3(&tmpReturn_3, self, reader, self->unique_tracks) ) ;
				self->unique_tracks++;
			}
			else {
				printf("unknown tag:%s\n", tag) ;
			}
		}
	}
}


Orc$List*  SuiDesigner3d_w3e$MdxReader$readTEXS(Orc$List **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  total_size = 0;
	while (total_size < size) {
		int  subchunk_size = 268;
		total_size += subchunk_size;
		printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TextureData*  tex = self->readTextureData((tex = NULL,&tex), self, reader) ;
		self->texs->add(self->texs, tex) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, self->texs) ; 
}


Orc$List*  SuiDesigner3d_w3e$MdxReader$readSEQS(Orc$List **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  cnt = size / 132;
	for (int  i = 0; i < cnt; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$Sequence*  seq = self->readSequence((seq = NULL,&seq), self, reader) ;
		self->seqs->add(self->seqs, seq) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, self->seqs) ; 
}


Orc$List*  SuiDesigner3d_w3e$MdxReader$readGLBS(Orc$List **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  cnt = size / 4;
	for (int  i = 0; i < cnt; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$GlobalSeq*  seq = (seq=NULL,urgc_init_var_class((void**)&seq, SuiDesigner3d_w3e$GlobalSeq_new(&seq) ));
		seq->duration = reader->readInt(reader) ;
		self->globalSeqs->add(self->globalSeqs, seq) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, self->globalSeqs) ; 
}


Sgl$IntArray*  SuiDesigner3d_w3e$MdxReader$mkBoneIndices(Sgl$IntArray **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$IntArray *  matrix_group, Sgl$IntArray *  matrix_indices){
	URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$IntArray_new(&r) ));
	int  offset = 0;
	for (int  i = 0; i < matrix_group->size; i++) {
		int  cnt = Sgl$IntArray$get(matrix_group, i) ;
		for (int  j = 0; j < cnt; j++) {
			int  boneIndex = Sgl$IntArray$get(matrix_indices, offset + j) ;
			Sgl$IntArray$append(r, boneIndex) ;
		}
		for (int  j = 0; j < 4 - cnt; j++) {
			Sgl$IntArray$append(r, 0) ;
		}
		offset += cnt;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


void  SuiDesigner3d_w3e$MdxReader$readGEOS(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  total_size = 0;
	while (total_size < size) {
		int  subchunk_size = reader->readInt(reader) ;
		total_size += subchunk_size;
		printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size) ;
		char  subname[5];
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$Geoset*  geoset = (geoset=NULL,urgc_init_var_class((void**)&geoset, SuiDesigner3d_w3e$Geoset_new(&geoset) ));
		Sgl$Geometry *  geom = geoset->geom;
		self->geosets->add(self->geosets, geoset) ;
		reader->readChars(reader, subname, 4, true) ;
		int  vertex_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Vec3Array*  vertices = reader->readVec3Array((vertices = NULL,&vertices), reader, vertex_count) ;
		printf("\tsubname:%s. vtx:%d/%d %s\n", subname, vertex_count, ((Sgl$StructArrayBase * )vertices)->size, "") ;
		geom->setAttrByFloats(geom, "position", (float * )vertices->data, vertex_count * 3, 3) ;
		reader->readChars(reader, subname, 4, true) ;
		int  normal_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Vec3Array*  normals = reader->readVec3Array((normals = NULL,&normals), reader, normal_count) ;
		printf("\tsubname:%s %d\n", subname, normal_count) ;
		geom->setAttrByFloats(geom, "normal", (float * )normals->data, normal_count * 3, 3) ;
		reader->readChars(reader, subname, 4, true) ;
		printf("\tsubname:%s\n", subname) ;
		int  face_type_groups_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  face_type_groups = reader->readIntArray((face_type_groups = NULL,&face_type_groups), reader, face_type_groups_count) ;
		reader->readChars(reader, subname, 4, true) ;
		printf("\tsubname:%s\n", subname) ;
		int  face_groups_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  face_groups = reader->readIntArray((face_groups = NULL,&face_groups), reader, face_groups_count) ;
		reader->readChars(reader, subname, 4, true) ;
		printf("\tsubname:%s\n", subname) ;
		int  faces_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$ShortArray*  faces = reader->readShortArray((faces = NULL,&faces), reader, faces_count) ;
		geom->setIboByShorts(geom, faces->data, faces_count) ;
		reader->readChars(reader, subname, 4, true) ;
		printf("\tsubname:%s\n", subname) ;
		int  vertex_groups_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$CharArray*  vertex_groups = reader->readCharArray((vertex_groups = NULL,&vertex_groups), reader, vertex_groups_count) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("\tvertex_groups:%s\n", vertex_groups->toString(&tmpReturn_1, vertex_groups) ->str) ;
		reader->readChars(reader, subname, 4, true) ;
		printf("\tsubname:%s\n", subname) ;
		int  matrix_group_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  matrix_group = reader->readIntArray((matrix_group = NULL,&matrix_group), reader, matrix_group_count) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		printf("\tmatrix_group:%s", Sgl$IntArray$toString(&tmpReturn_2, matrix_group) ->str) ;
		reader->readChars(reader, subname, 4, true) ;
		printf("\tsubname:%s\n", subname) ;
		int  matrix_indices_count = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  matrix_indices = reader->readIntArray((matrix_indices = NULL,&matrix_indices), reader, matrix_indices_count) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		printf("\tmatrix_indices:%s", Sgl$IntArray$toString(&tmpReturn_3, matrix_indices) ->str) ;
		{
			URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  boneIndices = self->mkBoneIndices((boneIndices = NULL,&boneIndices), self, matrix_group, matrix_indices) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_4 = NULL;
			printf("boneIndices:\n%s\n", Sgl$IntArray$toString(&tmpReturn_4, boneIndices) ->str) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Vec4Array*  skinIndex = (skinIndex=NULL,urgc_init_var_class((void**)&skinIndex, Sgl$Vec4Array_new(&skinIndex) ));
			URGC_VAR_CLEANUP_CLASS Sgl$Vec4Array*  skinWeight = (skinWeight=NULL,urgc_init_var_class((void**)&skinWeight, Sgl$Vec4Array_new(&skinWeight) ));
			for (int  i = 0; i < ((Sgl$StructArrayBase * )vertex_groups)->size; i++) {
				char  group = vertex_groups->get(vertex_groups, i) ;
				int  offset = group * 4;
				int  idx0 = boneIndices->data[offset + 0];
				int  idx1 = boneIndices->data[offset + 1];
				int  idx2 = boneIndices->data[offset + 2];
				int  idx3 = boneIndices->data[offset + 3];
				skinIndex->add(skinIndex, SuiCore$mkVec4(idx0, idx1, idx2, idx3) ) ;
				int  cnt = 0;
				if (idx0 != 0) {
					cnt++;
				}
				if (idx1 != 0) {
					cnt++;
				}
				if (idx2 != 0) {
					cnt++;
				}
				if (idx3 != 0) {
					cnt++;
				}
				float  weight = cnt == 0 ? 1 : 1 / (float )cnt;
				skinWeight->add(skinWeight, SuiCore$mkVec4(cnt >= 1 ? weight : 1.0, cnt >= 2 ? weight : 0.0, cnt >= 3 ? weight : 0.0, cnt >= 4 ? weight : 0.0) ) ;
			}
			geom->setAttrByFloats(geom, "skinIndex", (float * )skinIndex->data, ((Sgl$StructArrayBase * )skinIndex)->size * 4, 4) ;
			geom->setAttrByFloats(geom, "skinWeight", (float * )skinWeight->data, ((Sgl$StructArrayBase * )skinWeight)->size * 4, 4) ;
		}
		int  material_id = reader->readInt(reader) ;
		int  selection_group = reader->readInt(reader) ;
		int  selection_flags = reader->readInt(reader) ;
		geoset->material_id = material_id;
		printf("\t\tmaterial_id:%d\n", material_id) ;
		printf("\t\tselection_group:%d\n", selection_group) ;
		printf("\t\tselection_flags:%d\n", selection_flags) ;
		if (self->version > 800) {
			int  lod = reader->readInt(reader) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  lod_name = reader->readString((lod_name = NULL,&lod_name), reader, 80) ;
			printf("\t\tlod:%d\n", lod) ;
			printf("\t\tlod:%s\n", lod_name->str) ;
		}
		else {
			int  lod = 0;
		}
		SuiDesigner3d_w3e$Extend extend = self->readExtend(self, reader) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_5 = NULL;
		printf("\t\textend:%s\n", SuiDesigner3d_w3e$Extend$toString(&tmpReturn_5, &extend) ->str) ;
		int  extends_count = reader->readInt(reader) ;
		for (int  i = 0; i < extends_count; i++) {
			SuiDesigner3d_w3e$Extend sequence_extend = self->readExtend(self, reader) ;
		}
		URGC_VAR_CLEANUP_CLASS Orc$String*  tag = reader->readString((tag = NULL,&tag), reader, 4) ;
		printf("\ttag:%s\n", tag->str) ;
		if (Orc$String$equals(tag, "TANG") ) {
			int  structure_count = reader->readInt(reader) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Vec4Array*  tangents = reader->readVec4Array((tangents = NULL,&tangents), reader, structure_count) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_6 = NULL;
			urgc_set_var_class(&tag, reader->readString(&tmpReturn_6, reader, 4) ) ;
			printf("\ttag:%s\n", tag->str) ;
		}
		if (Orc$String$equals(tag, "SKIN") ) {
			int  skin_count = reader->readInt(reader) ;
			reader->advance(reader, skin_count * 1) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_7 = NULL;
			urgc_set_var_class(&tag, reader->readString(&tmpReturn_7, reader, 4) ) ;
			printf("\ttag:%s\n", tag->str) ;
		}
		int  texture_coordinate_sets_count = reader->readInt(reader) ;
		printf("\t\t纹理坐标数:%d\n", texture_coordinate_sets_count) ;
		for (int  i = 0; i < texture_coordinate_sets_count; i++) {
			reader->advance(reader, 4) ;
			int  texture_coordinates_count = reader->readInt(reader) ;
			URGC_VAR_CLEANUP_CLASS Sgl$Vec2Array*  uvs = reader->readVec2Array((uvs = NULL,&uvs), reader, texture_coordinates_count) ;
			if (i == 0) {
				geom->setAttrByFloats(geom, "uv", (float * )uvs->data, texture_coordinates_count * 2, 2) ;
			}
			else {
				printf("\t\t\t有多套纹理坐标。 忽略\n") ;
			}
		}
	}
}


void  SuiDesigner3d_w3e$MdxReader$readBONE(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  reader_pos = reader->index - 4;
	printf("\tread BONE. reader_pos:%d. size:%d\n", reader_pos, size) ;
	while (reader->index < reader_pos + size) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxBone*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$MdxBone_new(&e) ));
		self->bones->add(self->bones, e) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  tmpReturn_1 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$MdxBone, node) , self->readNode(&tmpReturn_1, self, reader) ) ;
		e->geoset_id = reader->readInt(reader) ;
		e->geoset_animation_id = reader->readInt(reader) ;
	}
}


void  SuiDesigner3d_w3e$MdxReader$readHELP(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  reader_pos = reader->index - 4;
	printf("\tread HELP. reader_pos:%d. size:%d\n", reader_pos, size) ;
	while (reader->index < reader_pos + size) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  node = self->readNode((node = NULL,&node), self, reader) ;
		self->helps->add(self->helps, node) ;
	}
}


void  SuiDesigner3d_w3e$MdxReader$readATCH(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  reader_pos = reader->index - 4;
	printf("\tread ATCH. reader_pos:%d. size:%d\n", reader_pos, size) ;
	while (reader->index < reader_pos + size) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$Attachment*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$Attachment_new(&e) ));
		self->attachments->add(self->attachments, e) ;
		int  node_reader_pos = reader->index;
		int  inclusive_size = reader->readInt(reader) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  tmpReturn_1 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$Attachment, node) , self->readNode(&tmpReturn_1, self, reader) ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$Attachment, path) , reader->readString(&tmpReturn_2, reader, 256) ) ;
		e->reserved = reader->readInt(reader) ;
		e->attachment_id = reader->readInt(reader) ;
		while (reader->index < node_reader_pos + inclusive_size) {
			char  tag[5];
			reader->readChars(reader, tag, 4, true) ;
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_3 = NULL;
			urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$Attachment, KATV) , self->readTrackHeaderFloat(&tmpReturn_3, self, reader, self->unique_tracks) ) ;
			self->unique_tracks++;
			printf("\t\ttag:%s\n", tag) ;
			if (strcmp(tag, "KATV")  == 0) {
				
			}
			else {
				printf("Unknown tag:%s\n", tag) ;
			}
		}
	}
}


void  SuiDesigner3d_w3e$MdxReader$readCORN(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  reader_pos = reader->index - 4;
	printf("\tread CORN. reader_pos:%d. size:%d\n", reader_pos, size) ;
	while (reader->index < reader_pos + size) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$CornEmitter*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$CornEmitter_new(&e) ));
		self->cornEmitters->add(self->cornEmitters, e) ;
		int  node_reader_pos = reader->index;
		int  inclusive_size = reader->readInt(reader) ;
		printf("\tnew CornEmitter\n") ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  tmpReturn_1 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$CornEmitter, node) , self->readNode(&tmpReturn_1, self, reader) ) ;
		URGC_VAR_CLEANUP_CLASS Sgl$CharArray*  a = reader->readCharArray((a = NULL,&a), reader, inclusive_size - (reader->index - node_reader_pos)) ;
	}
}


void  SuiDesigner3d_w3e$MdxReader$readEVTS(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  reader_pos = reader->index - 4;
	printf("\tread EVTS. reader_pos:%d. size:%d\n", reader_pos, size) ;
	while (reader->index < reader_pos + size) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$EventObject*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$EventObject_new(&e) ));
		self->events->add(self->events, e) ;
		printf("\tnew EventObject\n") ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  tmpReturn_1 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$EventObject, node) , self->readNode(&tmpReturn_1, self, reader) ) ;
		printf("\t name:%s\n", e->node->name->str) ;
		char  tag[5];
		reader->readChars(reader, tag, 4, true) ;
		printf("\t tag:%s\n", tag) ;
		int  count = reader->readInt(reader) ;
		e->globalSeqId = reader->readInt(reader) ;
		printf("\t globalSeqId:%d\n", e->globalSeqId) ;
		URGC_VAR_CLEANUP_CLASS Sgl$IntArray*  tmpReturn_2 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$EventObject, times) , reader->readIntArray(&tmpReturn_2, reader, count) ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
		printf("\t times:%s\n", Sgl$IntArray$toString(&tmpReturn_3, e->times) ->str) ;
	}
}


void  SuiDesigner3d_w3e$MdxReader$readCLID(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  reader_pos = reader->index - 4;
	while (reader->index < reader_pos + size) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$CollisionShape*  shape = (shape=NULL,urgc_init_var_class((void**)&shape, SuiDesigner3d_w3e$CollisionShape_new(&shape) ));
		self->collisionShapes->add(self->collisionShapes, shape) ;
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  tmpReturn_1 = NULL;
		urgc_set_field_class(shape, (void * )offsetof(SuiDesigner3d_w3e$CollisionShape, node) , self->readNode(&tmpReturn_1, self, reader) ) ;
		shape->shapeType = (SuiDesigner3d_w3e$ShapeType)reader->readInt(reader) ;
		printf("\tCollisionShape. name:%s, shapeType:%d\n", shape->node->name->str, shape->shapeType) ;
		shape->v0 = reader->readVec3(reader) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		printf("\t\t v0:%s\n", SuiCore$Vec3$toString(&tmpReturn_2, &shape->v0) ->str) ;
		if (shape->shapeType != SuiDesigner3d_w3e$ShapeType_Sphere) {
			shape->v1 = reader->readVec3(reader) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
			printf("\t\t v1:%s\n", SuiCore$Vec3$toString(&tmpReturn_3, &shape->v1) ->str) ;
		}
		if (shape->shapeType == SuiDesigner3d_w3e$ShapeType_Sphere || shape->shapeType == SuiDesigner3d_w3e$ShapeType_Cylinder) {
			shape->radius = reader->readFloat(reader) ;
			printf("\t\t radius:%f\n", shape->radius) ;
		}
	}
}


SuiDesigner3d_w3e$TrackHeader*  SuiDesigner3d_w3e$MdxReader$readTrackHeaderQuat(SuiDesigner3d_w3e$TrackHeader **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  track_id){
	int  tracks_count = reader->readInt(reader) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  r = (r=NULL,urgc_init_var_class((void**)&r, SuiDesigner3d_w3e$TrackHeader_new(&r) ));
	r->interpolationType = (SuiDesigner3d_w3e$InterpolationType)reader->readInt(reader) ;
	r->globalSeqId = reader->readInt(reader) ;
	for (int  i = 0; i < tracks_count; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackQuat*  tvec = (tvec=NULL,urgc_init_var_class((void**)&tvec, SuiDesigner3d_w3e$TrackQuat_new(&tvec) ));
		((SuiDesigner3d_w3e$TrackValue * )tvec)->frame = reader->readInt(reader) ;
		tvec->value = reader->readQuat(reader) ;
		if (r->interpolationType == SuiDesigner3d_w3e$InterpolationType_bezier || r->interpolationType == SuiDesigner3d_w3e$InterpolationType_hermite) {
			tvec->inTan = reader->readQuat(reader) ;
			tvec->outTan = reader->readQuat(reader) ;
		}
		r->tracks->add(r->tracks, tvec) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


SuiDesigner3d_w3e$TrackHeader*  SuiDesigner3d_w3e$MdxReader$readTrackHeaderVec3(SuiDesigner3d_w3e$TrackHeader **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  track_id){
	int  tracks_count = reader->readInt(reader) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  r = (r=NULL,urgc_init_var_class((void**)&r, SuiDesigner3d_w3e$TrackHeader_new(&r) ));
	r->interpolationType = (SuiDesigner3d_w3e$InterpolationType)reader->readInt(reader) ;
	r->globalSeqId = reader->readInt(reader) ;
	for (int  i = 0; i < tracks_count; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackVec3*  tvec = (tvec=NULL,urgc_init_var_class((void**)&tvec, SuiDesigner3d_w3e$TrackVec3_new(&tvec) ));
		((SuiDesigner3d_w3e$TrackValue * )tvec)->frame = reader->readInt(reader) ;
		tvec->value = reader->readVec3(reader) ;
		if (r->interpolationType == SuiDesigner3d_w3e$InterpolationType_bezier || r->interpolationType == SuiDesigner3d_w3e$InterpolationType_hermite) {
			tvec->inTan = reader->readVec3(reader) ;
			tvec->outTan = reader->readVec3(reader) ;
		}
		r->tracks->add(r->tracks, tvec) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


SuiDesigner3d_w3e$TrackHeader*  SuiDesigner3d_w3e$MdxReader$readTrackHeaderInt(SuiDesigner3d_w3e$TrackHeader **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  track_id){
	int  tracks_count = reader->readInt(reader) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  r = (r=NULL,urgc_init_var_class((void**)&r, SuiDesigner3d_w3e$TrackHeader_new(&r) ));
	r->interpolationType = (SuiDesigner3d_w3e$InterpolationType)reader->readInt(reader) ;
	r->globalSeqId = reader->readInt(reader) ;
	for (int  i = 0; i < tracks_count; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackInt*  tvec = (tvec=NULL,urgc_init_var_class((void**)&tvec, SuiDesigner3d_w3e$TrackInt_new(&tvec) ));
		((SuiDesigner3d_w3e$TrackValue * )tvec)->frame = reader->readInt(reader) ;
		tvec->value = reader->readInt(reader) ;
		if (r->interpolationType == SuiDesigner3d_w3e$InterpolationType_bezier || r->interpolationType == SuiDesigner3d_w3e$InterpolationType_hermite) {
			tvec->inTan = reader->readInt(reader) ;
			tvec->outTan = reader->readInt(reader) ;
		}
		r->tracks->add(r->tracks, tvec) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


SuiDesigner3d_w3e$TrackHeader*  SuiDesigner3d_w3e$MdxReader$readTrackHeaderFloat(SuiDesigner3d_w3e$TrackHeader **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  track_id){
	int  tracks_count = reader->readInt(reader) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  r = (r=NULL,urgc_init_var_class((void**)&r, SuiDesigner3d_w3e$TrackHeader_new(&r) ));
	r->interpolationType = (SuiDesigner3d_w3e$InterpolationType)reader->readInt(reader) ;
	r->globalSeqId = reader->readInt(reader) ;
	for (int  i = 0; i < tracks_count; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackFloat*  tvec = (tvec=NULL,urgc_init_var_class((void**)&tvec, SuiDesigner3d_w3e$TrackFloat_new(&tvec) ));
		((SuiDesigner3d_w3e$TrackValue * )tvec)->frame = reader->readInt(reader) ;
		tvec->value = reader->readFloat(reader) ;
		if (r->interpolationType == SuiDesigner3d_w3e$InterpolationType_bezier || r->interpolationType == SuiDesigner3d_w3e$InterpolationType_hermite) {
			tvec->inTan = reader->readFloat(reader) ;
			tvec->outTan = reader->readFloat(reader) ;
		}
		r->tracks->add(r->tracks, tvec) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


SuiDesigner3d_w3e$MdxNode*  SuiDesigner3d_w3e$MdxReader$readNode(SuiDesigner3d_w3e$MdxNode **  __outRef__, SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader){
	int  pos = reader->index;
	int  inclusive_size = reader->readInt(reader) ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxNode*  n = (n=NULL,urgc_init_var_class((void**)&n, SuiDesigner3d_w3e$MdxNode_new(&n) ));
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(n, (void * )offsetof(SuiDesigner3d_w3e$MdxNode, name) , reader->readString(&tmpReturn_1, reader, 80) ) ;
	n->id = reader->readInt(reader) ;
	n->parentId = reader->readInt(reader) ;
	n->flags = reader->readInt(reader) ;
	while (reader->index < pos + inclusive_size) {
		char  tag[5];
		reader->readChars(reader, tag, 4, true) ;
		if (strcmp(tag, "KGTR")  == 0) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_2 = NULL;
			urgc_set_field_class(n, (void * )offsetof(SuiDesigner3d_w3e$MdxNode, KGTR) , self->readTrackHeaderVec3(&tmpReturn_2, self, reader, self->unique_tracks) ) ;
			self->unique_tracks++;
		}
		else if (strcmp(tag, "KGRT")  == 0) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_3 = NULL;
			urgc_set_field_class(n, (void * )offsetof(SuiDesigner3d_w3e$MdxNode, KGRT) , self->readTrackHeaderQuat(&tmpReturn_3, self, reader, self->unique_tracks) ) ;
			self->unique_tracks++;
		}
		else if (strcmp(tag, "KGSC")  == 0) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$TrackHeader*  tmpReturn_4 = NULL;
			urgc_set_field_class(n, (void * )offsetof(SuiDesigner3d_w3e$MdxNode, KGSC) , self->readTrackHeaderVec3(&tmpReturn_4, self, reader, self->unique_tracks) ) ;
			self->unique_tracks++;
		}
		else {
			printf("unknown tags:%s\n", tag) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, n) ; 
}


void  SuiDesigner3d_w3e$MdxReader$readPIVT(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	URGC_VAR_CLEANUP_CLASS Sgl$Vec3Array*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$MdxReader, pivots) , reader->readVec3Array(&tmpReturn_1, reader, size / 12) ) ;
	printf("\tPIVT:%s\n", "") ;
}


void  SuiDesigner3d_w3e$MdxReader$readFAFX(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	for (int  i = 0; i < size / 340; i++) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$FaceFX*  e = (e=NULL,urgc_init_var_class((void**)&e, SuiDesigner3d_w3e$FaceFX_new(&e) ));
		self->faceFxList->add(self->faceFxList, e) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$FaceFX, name) , reader->readString(&tmpReturn_1, reader, 80) ) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
		urgc_set_field_class(e, (void * )offsetof(SuiDesigner3d_w3e$FaceFX, path) , reader->readString(&tmpReturn_2, reader, 260) ) ;
		printf("\tfafx. name:%s\n", e->name->str) ;
		printf("\tfafx. path:%s\n", e->path->str) ;
	}
}


void  SuiDesigner3d_w3e$MdxReader$readCAMS(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  total_size = 0;
	while (total_size < size) {
		int  subchunk_size = reader->readInt(reader) ;
		total_size += subchunk_size;
		printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size) ;
		reader->advance(reader, subchunk_size - 4) ;
	}
}


void  SuiDesigner3d_w3e$MdxReader$readTXAN(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  total_size = 0;
	while (total_size < size) {
		int  subchunk_size = reader->readInt(reader) ;
		total_size += subchunk_size;
		printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size) ;
		reader->advance(reader, subchunk_size - 4) ;
	}
}


void  SuiDesigner3d_w3e$MdxReader$readBPOS(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader, int  size){
	int  vec3_cnt = reader->readInt(reader) ;
	URGC_VAR_CLEANUP_CLASS Sgl$Vec3Array*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$MdxReader, bindPose) , reader->readVec3Array(&tmpReturn_1, reader, vec3_cnt) ) ;
	printf("BPOS v3 cnt;%d\n", vec3_cnt) ;
}


bool  SuiDesigner3d_w3e$MdxReader$load(SuiDesigner3d_w3e$MdxReader *  self, Sgl$BufferReader *  reader){
	URGC_VAR_CLEANUP_CLASS Orc$String*  s = reader->readString((s = NULL,&s), reader, 4) ;
	printf("magic number:%s\n", s->str) ;
	if (!Orc$String$equals(s, "MDLX") ) {
		return false; 
	}
	while (reader->remaining(reader)  > 0) {
		char  header[5];
		reader->readChars(reader, header, 4, true) ;
		int  size = reader->readInt(reader) ;
		printf("chunk header:%s, size:%d. remaining:%d\n", header, size, reader->remaining(reader) ) ;
		if (strcmp(header, "VERS")  == 0) {
			self->version = reader->readInt(reader) ;
			printf("\tversion:%d\n", self->version) ;
		}
		else if (strcmp(header, "MODL")  == 0) {
			URGC_VAR_CLEANUP_CLASS Orc$String*  name = reader->readString((name = NULL,&name), reader, 80) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  animationFilename = reader->readString((animationFilename = NULL,&animationFilename), reader, 260) ;
			SuiDesigner3d_w3e$Extend extend = self->readExtend(self, reader) ;
			int  blend_time = reader->readInt(reader) ;
			printf("\tname:%s\n", name->str) ;
			printf("\tanimationFilename:%s\n", animationFilename->str) ;
			URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
			printf("\textend: %s\n", SuiDesigner3d_w3e$Extend$toString(&tmpReturn_1, &extend) ->str) ;
			printf("\tblend_time:%d \n", blend_time) ;
		}
		else if (strcmp(header, "GEOS")  == 0) {
			self->readGEOS(self, reader, size) ;
		}
		else if (strcmp(header, "GEOA")  == 0) {
			self->readGEOA(self, reader, size) ;
		}
		else if (strcmp(header, "PIVT")  == 0) {
			self->readPIVT(self, reader, size) ;
		}
		else if (strcmp(header, "CAMS")  == 0) {
			self->readCAMS(self, reader, size) ;
		}
		else if (strcmp(header, "EVTS")  == 0) {
			self->readEVTS(self, reader, size) ;
		}
		else if (strcmp(header, "HELP")  == 0) {
			self->readHELP(self, reader, size) ;
		}
		else if (strcmp(header, "ATCH")  == 0) {
			self->readATCH(self, reader, size) ;
		}
		else if (strcmp(header, "BONE")  == 0) {
			self->readBONE(self, reader, size) ;
		}
		else if (strcmp(header, "FAFX")  == 0) {
			self->readFAFX(self, reader, size) ;
		}
		else if (strcmp(header, "TEXS")  == 0) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_2 = NULL;
			self->readTEXS(&tmpReturn_2, self, reader, size) ;
		}
		else if (strcmp(header, "CLID")  == 0) {
			self->readCLID(self, reader, size) ;
		}
		else if (strcmp(header, "CORN")  == 0) {
			self->readCORN(self, reader, size) ;
		}
		else if (strcmp(header, "TXAN")  == 0) {
			self->readTXAN(self, reader, size) ;
		}
		else if (strcmp(header, "BPOS")  == 0) {
			self->readBPOS(self, reader, size) ;
		}
		else if (strcmp(header, "LITE")  == 0) {
			self->readLITE(self, reader, size) ;
		}
		else if (strcmp(header, "MTLS")  == 0) {
			self->readMTLS(self, reader, size) ;
		}
		else if (strcmp(header, "SEQS")  == 0) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_3 = NULL;
			self->readSEQS(&tmpReturn_3, self, reader, size) ;
		}
		else if (strcmp(header, "GLBS")  == 0) {
			URGC_VAR_CLEANUP_CLASS Orc$List*  tmpReturn_4 = NULL;
			self->readGLBS(&tmpReturn_4, self, reader, size) ;
		}
		else {
			reader->advance(reader, size) ;
		}
	}
	return true; 
}


bool  SuiDesigner3d_w3e$MdxReader$loadByPathCstr(SuiDesigner3d_w3e$MdxReader *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = Sgl$Buffer_readFile((buf = NULL,&buf), path) ;
	URGC_VAR_CLEANUP_CLASS Sgl$BufferReader*  br = Sgl$mkBufferReader((br = NULL,&br), buf) ;
	bool  ok = self->load(self, br) ;
	return ok; 
}




//vtable instance
Vtable_SuiDesigner3d_w3e$MkMdx _vtable_SuiDesigner3d_w3e$MkMdx;

// init meta

void SuiDesigner3d_w3e$MkMdx_initMeta(Vtable_SuiDesigner3d_w3e$MkMdx *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "mr", ((Vtable_Object*)Vtable_SuiDesigner3d_w3e$MdxReader_init(0)), offsetof(SuiDesigner3d_w3e$MkMdx, mr), true, false, 1);
	orc_metaField_class(&pNext, "ske", ((Vtable_Object*)Vtable_Sgl$Skeleton_init(0)), offsetof(SuiDesigner3d_w3e$MkMdx, ske), true, false, 1);

	orc_metaField_method(&pNext, "mkSkeleton", offsetof(SuiDesigner3d_w3e$MkMdx, mkSkeleton));
}


// vtable init


Vtable_SuiDesigner3d_w3e$MkMdx* Vtable_SuiDesigner3d_w3e$MkMdx_init(Vtable_SuiDesigner3d_w3e$MkMdx* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$MkMdx;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$MkMdx_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$MkMdx";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$MkMdx_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$MkMdx_fini(SuiDesigner3d_w3e$MkMdx *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MkMdx*)self)->mr);
	urgc_fini_field_class(self, (void**)&((SuiDesigner3d_w3e$MkMdx*)self)->ske);

}

// init fields function


void SuiDesigner3d_w3e$MkMdx_init_fields(SuiDesigner3d_w3e$MkMdx *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$MkMdx_fini;
	//fields
    {
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MkMdx*)self)->mr, NULL);
	URGC_VAR_CLEANUP_CLASS Sgl$Skeleton*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$MkMdx*)self)->ske, Sgl$Skeleton_new(&tmpNewOwner_1) );
    }
	((SuiDesigner3d_w3e$MkMdx*)self)->mkSkeleton = (void*)SuiDesigner3d_w3e$MkMdx$mkSkeleton;
}

// init function

void SuiDesigner3d_w3e$MkMdx_init(SuiDesigner3d_w3e$MkMdx *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$MkMdx_init(&_vtable_SuiDesigner3d_w3e$MkMdx);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$MkMdx;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$MkMdx_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$MkMdx * SuiDesigner3d_w3e$MkMdx_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$MkMdx *self = calloc(1, sizeof(SuiDesigner3d_w3e$MkMdx));
	
    SuiDesigner3d_w3e$MkMdx_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner3d_w3e$MkMdx$mkSkeleton(SuiDesigner3d_w3e$MkMdx *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  bones = (bones=NULL,urgc_init_var_class((void**)&bones, Orc$List_new(&bones) ));
	printf("\n========================================mkSkeleton\n") ;
	URGC_VAR_CLEANUP_CLASS Orc$List*  roots = (roots=NULL,urgc_init_var_class((void**)&roots, Orc$List_new(&roots) ));
	for (int  i = 0; i < self->mr->helps->size(self->mr->helps) ; i++) {
		SuiDesigner3d_w3e$MdxNode *  help = self->mr->helps->get(self->mr->helps, i) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Bone*  bone = (bone=NULL,urgc_init_var_class((void**)&bone, Sgl$Bone_new(&bone) ));
		urgc_set_field_class(help, (void * )offsetof(SuiDesigner3d_w3e$MdxNode, bone) , bone) ;
		((Sgl$Obj3d * )bone)->position = self->mr->pivots->get(self->mr->pivots, help->id) ;
		if (help->parentId != -1) {
			SuiCore$Vec3 parentPos = self->mr->pivots->get(self->mr->pivots, help->parentId) ;
			((Sgl$Obj3d * )bone)->position = SuiCore$Vec3$sub(&((Sgl$Obj3d * )bone)->position, parentPos) ;
		}
		bone->originPosition = ((Sgl$Obj3d * )bone)->position;
		bones->set(bones, help->id, bone) ;
		char  name[128];
		sprintf(name, "%s;%d:%d; pos:%.2f,%.2f,%.2f", help->name->str, help->id, help->parentId, ((Sgl$Obj3d * )bone)->position.x, ((Sgl$Obj3d * )bone)->position.y, ((Sgl$Obj3d * )bone)->position.z) ;
		Orc$String$set(((SuiCore$Node * )bone)->name, name) ;
		bone->parentId = help->parentId;
		bone->id = help->id;
	}
	for (int  i = 0; i < self->mr->bones->size(self->mr->bones) ; i++) {
		SuiDesigner3d_w3e$MdxBone *  mdxbone = self->mr->bones->get(self->mr->bones, i) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Bone*  bone = (bone=NULL,urgc_init_var_class((void**)&bone, Sgl$Bone_new(&bone) ));
		urgc_set_field_class(mdxbone->node, (void * )offsetof(SuiDesigner3d_w3e$MdxNode, bone) , bone) ;
		((Sgl$Obj3d * )bone)->position = self->mr->pivots->get(self->mr->pivots, mdxbone->node->id) ;
		if (mdxbone->node->parentId != -1) {
			SuiCore$Vec3 parentPos = self->mr->pivots->get(self->mr->pivots, mdxbone->node->parentId) ;
			((Sgl$Obj3d * )bone)->position = SuiCore$Vec3$sub(&((Sgl$Obj3d * )bone)->position, parentPos) ;
		}
		bone->originPosition = ((Sgl$Obj3d * )bone)->position;
		bones->set(bones, mdxbone->node->id, bone) ;
		char  name[128];
		sprintf(name, "%s;%d:%d; pos:%.2f,%.2f,%.2f", mdxbone->node->name->str, mdxbone->node->id, mdxbone->node->parentId, ((Sgl$Obj3d * )bone)->position.x, ((Sgl$Obj3d * )bone)->position.y, ((Sgl$Obj3d * )bone)->position.z) ;
		Orc$String$set(((SuiCore$Node * )bone)->name, name) ;
		bone->parentId = mdxbone->node->parentId;
		bone->id = mdxbone->node->id;
	}
	for (int  i = 0; i < self->mr->helps->size(self->mr->helps) ; i++) {
		SuiDesigner3d_w3e$MdxNode *  help = self->mr->helps->get(self->mr->helps, i) ;
		Sgl$Bone *  bone = (Sgl$Bone * )bones->get(bones, help->id) ;
		Sgl$Bone *  parentBone = (Sgl$Bone * )bones->get(bones, help->parentId) ;
		if (parentBone) {
			((SuiCore$Node * )parentBone)->appendChild(parentBone, bone) ;
		}
		else {
			roots->add(roots, bone) ;
		}
	}
	for (int  i = 0; i < self->mr->bones->size(self->mr->bones) ; i++) {
		SuiDesigner3d_w3e$MdxBone *  mdxbone = self->mr->bones->get(self->mr->bones, i) ;
		Sgl$Bone *  bone = (Sgl$Bone * )bones->get(bones, mdxbone->node->id) ;
		Sgl$Bone *  parentBone = (Sgl$Bone * )bones->get(bones, mdxbone->node->parentId) ;
		if (parentBone) {
			((SuiCore$Node * )parentBone)->appendChild(parentBone, bone) ;
		}
		else {
			roots->add(roots, bone) ;
		}
	}
	for (int  i = 0; i < roots->size(roots) ; i++) {
		Sgl$Bone *  root = (Sgl$Bone * )roots->get(roots, i) ;
		((SuiCore$Node * )self->ske)->appendChild(self->ske, root) ;
	}
	((Sgl$Obj3d * )self->ske)->updateWorldTransformAndSubtree(self->ske) ;
	for (int  i = 0; i < bones->size(bones) ; i++) {
		Sgl$Bone *  bone = (Sgl$Bone * )bones->get(bones, i) ;
		if (bone == NULL) {
			continue;
		}
		bone->bindPose = ((Sgl$Obj3d * )bone)->_world_transform;
		bone->bindMatrixInverse = Sgl$Mat$invert(&bone->bindPose) ;
	}
	SuiCore$printNodeTree(self->ske, 0) ;
}



void  SuiDesigner3d_w3e$testMdxReader(){
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxReader*  r = (r=NULL,urgc_init_var_class((void**)&r, SuiDesigner3d_w3e$MdxReader_new(&r) ));
	r->loadByPathCstr(r, "../asset/Units/Human/Footman/Footman.mdx") ;
	printf("load complete\n") ;
	URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$MdxSeqPlayer*  player = (player=NULL,urgc_init_var_class((void**)&player, SuiDesigner3d_w3e$MdxSeqPlayer_new(&player) ));
	player->init(player, r) ;
	for (int  i = 0; i < player->seqs->size(player->seqs) ; i++) {
		SuiDesigner3d_w3e$Sequence *  seq = (SuiDesigner3d_w3e$Sequence * )player->seqs->get(player->seqs, i) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		printf("seq:%s\n", seq->toString(&tmpReturn_1, seq) ->str) ;
	}
	SuiDesigner3d_w3e$Sequence *  seq = player->findSeq(player, "Stand - 2") ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	printf("complete. seq:%s\n", seq->toString(&tmpReturn_2, seq) ->str) ;
	player->play(player, "Stand - 1") ;
	URGC_VAR_CLEANUP_CLASS Sgl$DrawCtx*  ctx = (ctx=NULL,urgc_init_var_class((void**)&ctx, Sgl$DrawCtx_new(&ctx) ));
	ctx->dtMs = 500;
	((Sgl$Obj3d * )player)->tick(player, ctx) ;
	Orc$Time_sleepSec(1) ;
	((Sgl$Obj3d * )player)->tick(player, ctx) ;
	Orc$Time_sleepSec(1) ;
	((Sgl$Obj3d * )player)->tick(player, ctx) ;
}



