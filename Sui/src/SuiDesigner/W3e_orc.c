
#include "W3e_orc.h" 

#include "../Orc/Orc.h"
#include <stdio.h>
#include <math.h>
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


// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner3d_w3e$W3eCorner _vtable_SuiDesigner3d_w3e$W3eCorner;

// init meta

void SuiDesigner3d_w3e$W3eCorner_initMeta(Vtable_SuiDesigner3d_w3e$W3eCorner *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "groundHeight", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$W3eCorner, groundHeight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "waterHeight", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$W3eCorner, waterHeight), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "mapEdge", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$W3eCorner, mapEdge), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "ramp", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$W3eCorner, ramp), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "blight", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$W3eCorner, blight), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "water", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$W3eCorner, water), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "boundary", OrcMetaType_bool, offsetof(SuiDesigner3d_w3e$W3eCorner, boundary), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "groundTexture", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3eCorner, groundTexture), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "cliffVariation", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3eCorner, cliffVariation), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "groundVariation", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3eCorner, groundVariation), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "cliffTexture", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3eCorner, cliffTexture), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "layerHeight", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3eCorner, layerHeight), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "actualGroundHeight", OrcMetaType_float, offsetof(SuiDesigner3d_w3e$W3eCorner, actualGroundHeight), 0, 0, 0, 0);//float

	orc_metaField_method(&pNext, "calcActualGroundHeight", offsetof(SuiDesigner3d_w3e$W3eCorner, calcActualGroundHeight));
	orc_metaField_method(&pNext, "load", offsetof(SuiDesigner3d_w3e$W3eCorner, load));
}


// vtable init


Vtable_SuiDesigner3d_w3e$W3eCorner* Vtable_SuiDesigner3d_w3e$W3eCorner_init(Vtable_SuiDesigner3d_w3e$W3eCorner* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$W3eCorner;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$W3eCorner_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$W3eCorner";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$W3eCorner_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$W3eCorner_fini(SuiDesigner3d_w3e$W3eCorner *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner3d_w3e$W3eCorner_init_fields(SuiDesigner3d_w3e$W3eCorner *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$W3eCorner_fini;
	//fields
    {
	((SuiDesigner3d_w3e$W3eCorner*)self)->groundHeight = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->waterHeight = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->mapEdge = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->ramp = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->blight = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->water = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->boundary = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->groundTexture = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->cliffVariation = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->groundVariation = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->cliffTexture = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->layerHeight = 0;
	((SuiDesigner3d_w3e$W3eCorner*)self)->actualGroundHeight = 0;
    }
	((SuiDesigner3d_w3e$W3eCorner*)self)->calcActualGroundHeight = (void*)SuiDesigner3d_w3e$W3eCorner$calcActualGroundHeight;
	((SuiDesigner3d_w3e$W3eCorner*)self)->load = (void*)SuiDesigner3d_w3e$W3eCorner$load;
}

// init function

void SuiDesigner3d_w3e$W3eCorner_init(SuiDesigner3d_w3e$W3eCorner *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$W3eCorner_init(&_vtable_SuiDesigner3d_w3e$W3eCorner);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$W3eCorner;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$W3eCorner_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$W3eCorner * SuiDesigner3d_w3e$W3eCorner_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$W3eCorner *self = calloc(1, sizeof(SuiDesigner3d_w3e$W3eCorner));
	
    SuiDesigner3d_w3e$W3eCorner_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner3d_w3e$W3eCorner$calcActualGroundHeight(SuiDesigner3d_w3e$W3eCorner *  self){
	self->actualGroundHeight = (self->groundHeight + self->layerHeight - 2) * 128.0;
}


void  SuiDesigner3d_w3e$W3eCorner$load(SuiDesigner3d_w3e$W3eCorner *  self, Sgl$BufferReader *  stream){
	self->groundHeight = (stream->readInt16(stream)  - 8192) / 512.0;
	short  waterAndEdge = stream->readInt16(stream) ;
	short  waterH = (waterAndEdge & 0x3FFF);
	self->waterHeight = ((waterAndEdge & 0x3FFF) - 8192) / 512;
	self->mapEdge = waterAndEdge & 0x4000;
	short  textureAndFlags = stream->readUint8(stream) ;
	self->ramp = textureAndFlags & 0b00010000;
	self->blight = textureAndFlags & 0b00100000;
	self->water = textureAndFlags & 0b01000000;
	self->boundary = textureAndFlags & 0b10000000;
	self->groundTexture = textureAndFlags & 0b00001111;
	unsigned char  variation = stream->readUint8(stream) ;
	self->cliffVariation = (variation & 0b11100000) >> 5;
	self->groundVariation = variation & 0b00011111;
	unsigned char  cliffTextureAndLayer = stream->readUint8(stream) ;
	self->cliffTexture = (cliffTextureAndLayer & 0b11110000) >> 4;
	self->layerHeight = cliffTextureAndLayer & 0b00001111;
	self->calcActualGroundHeight(self) ;
}




//vtable instance
Vtable_SuiDesigner3d_w3e$W3e _vtable_SuiDesigner3d_w3e$W3e;

// init meta

void SuiDesigner3d_w3e$W3e_initMeta(Vtable_SuiDesigner3d_w3e$W3e *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "head", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner3d_w3e$W3e, head), true, false, 1);
	orc_metaField_primitive(&pNext, "version", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3e, version), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "tileset", OrcMetaType_char, offsetof(SuiDesigner3d_w3e$W3e, tileset), 0, 0, 0, 0);//char
	orc_metaField_primitive(&pNext, "haveCustomTileset", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3e, haveCustomTileset), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "groundTilesetCount", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3e, groundTilesetCount), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "groundTilesetNames", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$W3e, groundTilesetNames), true, false, 1);
	orc_metaField_primitive(&pNext, "cliffTilesetCount", OrcMetaType_int, offsetof(SuiDesigner3d_w3e$W3e, cliffTilesetCount), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "cliffTilesetNames", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$W3e, cliffTilesetNames), true, false, 1);
	orc_metaField_struct(&pNext, "mapSize", SuiCore$IntVec2_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$W3e, mapSize), false, false, 0);
	orc_metaField_struct(&pNext, "centerOffset", SuiCore$Vec2_getOrInitMetaStruct(), offsetof(SuiDesigner3d_w3e$W3e, centerOffset), false, false, 0);
	orc_metaField_class(&pNext, "corners", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$W3e, corners), true, false, 1);
	orc_metaField_class(&pNext, "groundTexs", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner3d_w3e$W3e, groundTexs), true, false, 1);

	orc_metaField_method(&pNext, "mkGeometry", offsetof(SuiDesigner3d_w3e$W3e, mkGeometry));
	orc_metaField_method(&pNext, "mkGroundTexs", offsetof(SuiDesigner3d_w3e$W3e, mkGroundTexs));
	orc_metaField_method(&pNext, "setUniformTexs", offsetof(SuiDesigner3d_w3e$W3e, setUniformTexs));
	orc_metaField_method(&pNext, "load", offsetof(SuiDesigner3d_w3e$W3e, load));
}


// vtable init


Vtable_SuiDesigner3d_w3e$W3e* Vtable_SuiDesigner3d_w3e$W3e_init(Vtable_SuiDesigner3d_w3e$W3e* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner3d_w3e$W3e;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner3d_w3e$W3e_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner3d_w3e$W3e";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner3d_w3e$W3e_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner3d_w3e$W3e_fini(SuiDesigner3d_w3e$W3e *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner3d_w3e$W3e_init_fields(SuiDesigner3d_w3e$W3e *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner3d_w3e$W3e_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$W3e*)self)->head, Orc$str(&tmpReturn_1, "") );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$W3e*)self)->groundTilesetNames, Orc$List_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$W3e*)self)->cliffTilesetNames, Orc$List_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$W3e*)self)->corners, Orc$List_new(&tmpNewOwner_4) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_5 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner3d_w3e$W3e*)self)->groundTexs, Orc$List_new(&tmpNewOwner_5) );
    }
	((SuiDesigner3d_w3e$W3e*)self)->mkGeometry = (void*)SuiDesigner3d_w3e$W3e$mkGeometry;
	((SuiDesigner3d_w3e$W3e*)self)->mkGroundTexs = (void*)SuiDesigner3d_w3e$W3e$mkGroundTexs;
	((SuiDesigner3d_w3e$W3e*)self)->setUniformTexs = (void*)SuiDesigner3d_w3e$W3e$setUniformTexs;
	((SuiDesigner3d_w3e$W3e*)self)->load = (void*)SuiDesigner3d_w3e$W3e$load;
}

// init function

void SuiDesigner3d_w3e$W3e_init(SuiDesigner3d_w3e$W3e *self, void *pOwner){
    Vtable_SuiDesigner3d_w3e$W3e_init(&_vtable_SuiDesigner3d_w3e$W3e);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner3d_w3e$W3e;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner3d_w3e$W3e_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner3d_w3e$W3e * SuiDesigner3d_w3e$W3e_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner3d_w3e$W3e *self = calloc(1, sizeof(SuiDesigner3d_w3e$W3e));
	
    SuiDesigner3d_w3e$W3e_init(self, pOwner);
    return self;
}


// class members
Sgl$Geometry*  SuiDesigner3d_w3e$W3e$mkGeometry(Sgl$Geometry **  __outRef__, SuiDesigner3d_w3e$W3e *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = (buf=NULL,urgc_init_var_class((void**)&buf, Sgl$Buffer_new(&buf) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tilesets = (tilesets=NULL,urgc_init_var_class((void**)&tilesets, Sgl$Buffer_new(&tilesets) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv0 = (uv0=NULL,urgc_init_var_class((void**)&uv0, Sgl$Buffer_new(&uv0) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv1 = (uv1=NULL,urgc_init_var_class((void**)&uv1, Sgl$Buffer_new(&uv1) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv2 = (uv2=NULL,urgc_init_var_class((void**)&uv2, Sgl$Buffer_new(&uv2) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv3 = (uv3=NULL,urgc_init_var_class((void**)&uv3, Sgl$Buffer_new(&uv3) ));
	float  tilew = 128.0;
	int  vertIdx = 0;
	int  rows = self->mapSize.y;
	int  cols = self->mapSize.x;
	int  offsetx = -cols / 2 * tilew * 1;
	int  offsety = -rows / 2 * tilew * 1;
	for (int  y = 0; y < self->mapSize.y - 1; y++) {
		for (int  x = 0; x < self->mapSize.x - 1; x++) {
			int  idx = x + y * self->mapSize.x;
			SuiDesigner3d_w3e$W3eCorner *  corner = (SuiDesigner3d_w3e$W3eCorner * )self->corners->get(self->corners, idx) ;
			SuiDesigner3d_w3e$W3eCorner *  corner_rb = (SuiDesigner3d_w3e$W3eCorner * )self->corners->get(self->corners, (x + 1) + (y + 0) * self->mapSize.x) ;
			SuiDesigner3d_w3e$W3eCorner *  corner_rt = (SuiDesigner3d_w3e$W3eCorner * )self->corners->get(self->corners, (x + 1) + (y + 1) * self->mapSize.x) ;
			SuiDesigner3d_w3e$W3eCorner *  corner_lt = (SuiDesigner3d_w3e$W3eCorner * )self->corners->get(self->corners, (x + 0) + (y + 1) * self->mapSize.x) ;
			float  vx = x * tilew + offsetx;
			float  vy = y * tilew + offsety;
			float  rate = 1.0;
			Sgl$Buffer$appendFloat3(buf, vx, vy, corner->actualGroundHeight) ;
			Sgl$Buffer$appendFloat3(buf, vx + tilew * rate, vy, corner_rb->actualGroundHeight) ;
			Sgl$Buffer$appendFloat3(buf, vx + tilew * rate, vy + tilew * rate, corner_rt->actualGroundHeight) ;
			Sgl$Buffer$appendFloat3(buf, vx, vy + tilew * rate, corner_lt->actualGroundHeight) ;
			float  curTilesets[4];
			Sgl$FloatsProxy tilesetsProxy = Sgl$mkFloatsProxy(curTilesets, 4) ;
			Sgl$FloatsProxy$appendFloat4(&tilesetsProxy, corner->groundTexture, corner_rb->groundTexture, corner_rt->groundTexture, corner_lt->groundTexture) ;
			Sgl$FloatsProxy$distinctSelf(&tilesetsProxy) ;
			Sgl$FloatsProxy$fillRemainsByValue(&tilesetsProxy, 17) ;
			Sgl$Floats_bubbleSort(curTilesets, 4, true) ;
			Sgl$Buffer$appendFloats(tilesets, curTilesets, 4) ;
			Sgl$Buffer$appendFloats(tilesets, curTilesets, 4) ;
			Sgl$Buffer$appendFloats(tilesets, curTilesets, 4) ;
			Sgl$Buffer$appendFloats(tilesets, curTilesets, 4) ;
			for (int  i = 0; i < tilesetsProxy.size; i++) {
				float  texture = curTilesets[i];
				int  bit = 0;
				if (texture == corner->groundTexture) {
					bit |= 0b0010;
				}
				if (texture == corner_rb->groundTexture) {
					bit |= 0b0001;
				}
				if (texture == corner_rt->groundTexture) {
					bit |= 0b0100;
				}
				if (texture == corner_lt->groundTexture) {
					bit |= 0b1000;
				}
				int  tilex = (bit % 4);
				int  tiley = (bit / 4);
				float  u = tilex * 0.125;
				float  u1 = u + 0.125;
				float  v1 = 1.0 - tiley * 0.25;
				float  v = v1 - 0.25;
				if (bit == 0 || bit >= 15) {
					int  extx = (corner->groundVariation % 16) % 4;
					int  exty = (corner->groundVariation % 16) / 4;
					u = extx * 0.125 + 0.5;
					u1 = u + 0.125;
					v1 = 1.0 - exty * 0.25;
					v = v1 - 0.25;
				}
				u += 0.001;
				v += 0.001;
				u1 -= 0.001;
				v1 -= 0.001;
				Sgl$Buffer *  uv = uv0;
				if (i == 1) {
					uv = uv1;
				}
				else if (i == 2) {
					uv = uv2;
				}
				else if (i == 3) {
					uv = uv3;
				}
				Sgl$Buffer$appendFloat2(uv, u, v) ;
				Sgl$Buffer$appendFloat2(uv, u1, v) ;
				Sgl$Buffer$appendFloat2(uv, u1, v1) ;
				Sgl$Buffer$appendFloat2(uv, u, v1) ;
			}
			for (int  i = tilesetsProxy.size; i < 4; i++) {
				Sgl$Buffer *  uv = uv0;
				if (i == 1) {
					uv = uv1;
				}
				else if (i == 2) {
					uv = uv2;
				}
				else if (i == 3) {
					uv = uv3;
				}
				Sgl$Buffer$appendFloat2(uv, 0, 0) ;
				Sgl$Buffer$appendFloat2(uv, 0, 0) ;
				Sgl$Buffer$appendFloat2(uv, 0, 0) ;
				Sgl$Buffer$appendFloat2(uv, 0, 0) ;
			}
			if (x < cols - 1 && y < rows - 1) {
				int  lb = vertIdx;
				int  rb = vertIdx + 1;
				int  rt = vertIdx + 2;
				int  lt = vertIdx + 3;
				Sgl$Buffer$appendInt3(face, lb, rb, rt) ;
				Sgl$Buffer$appendInt3(face, lb, rt, lt) ;
			}
			vertIdx += 4;
		}
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Geometry*  r = (r=NULL,urgc_init_var_class((void**)&r, Sgl$Geometry_new(&r) ));
	r->setAttrByBuffer(r, "position", buf, 3) ;
	r->setAttrByBuffer(r, "tilesets", tilesets, 4) ;
	r->setAttrByBuffer(r, "uv0", uv0, 2) ;
	r->setAttrByBuffer(r, "uv1", uv1, 2) ;
	r->setAttrByBuffer(r, "uv2", uv2, 2) ;
	r->setAttrByBuffer(r, "uv3", uv3, 2) ;
	r->setIboByBuffer(r, face) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, r) ; 
}


void  SuiDesigner3d_w3e$W3e$mkGroundTexs(SuiDesigner3d_w3e$W3e *  self){
	for (int  i = 0; i < self->groundTilesetNames->size(self->groundTilesetNames) ; i++) {
		Orc$String *  name = (Orc$String * )self->groundTilesetNames->get(self->groundTilesetNames, i) ;
		URGC_VAR_CLEANUP_CLASS Sgl$Tex2d*  tex = (tex=NULL,urgc_init_var_class((void**)&tex, Sgl$Tex2d_new(&tex) ));
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		URGC_VAR_CLEANUP_CLASS Orc$String*  path = (path=NULL,urgc_init_var_class((void**)&path, Orc$String$add(Orc$String$add(Orc$str(&tmpReturn_1, "../asset/") , name->str) , ".png") ));
		tex->loadImageByPathCstr(tex, path->str) ;
		printf("mkGroundTexs. i:%d, path:%s\n", i, path->str) ;
		self->groundTexs->add(self->groundTexs, tex) ;
	}
}


void  SuiDesigner3d_w3e$W3e$setUniformTexs(SuiDesigner3d_w3e$W3e *  self, Sgl$Material *  matl){
	for (int  i = 0; i < self->groundTexs->size(self->groundTexs) ; i++) {
		Sgl$Tex2d *  tex = self->groundTexs->get(self->groundTexs, i) ;
		URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
		matl->setUniformTex2d(matl, Orc$String$addi(Orc$str(&tmpReturn_1, "tex") , i) ->str, tex) ;
	}
}


void  SuiDesigner3d_w3e$W3e$load(SuiDesigner3d_w3e$W3e *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = Sgl$Buffer_readFile((buf = NULL,&buf), path) ;
	URGC_VAR_CLEANUP_CLASS Sgl$BufferReader*  br = Sgl$mkBufferReader((br = NULL,&br), buf) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner3d_w3e$W3e, head) , br->readString(&tmpReturn_1, br, 4) ) ;
	self->version = br->readInt(br) ;
	self->tileset = br->readByte(br) ;
	self->haveCustomTileset = br->readInt(br) ;
	self->groundTilesetCount = br->readInt(br) ;
	for (int  i = 0; i < self->groundTilesetCount; i++) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  name = br->readString((name = NULL,&name), br, 4) ;
		self->groundTilesetNames->add(self->groundTilesetNames, name) ;
		printf("groundTilesetNames:%s\n", name->str) ;
	}
	self->cliffTilesetCount = br->readInt(br) ;
	for (int  i = 0; i < self->cliffTilesetCount; i++) {
		URGC_VAR_CLEANUP_CLASS Orc$String*  name = br->readString((name = NULL,&name), br, 4) ;
		self->cliffTilesetNames->add(self->cliffTilesetNames, name) ;
	}
	br->readBinary(br, &self->mapSize, sizeof(SuiCore$IntVec2) ) ;
	br->readBinary(br, &self->centerOffset, sizeof(SuiCore$Vec2) ) ;
	for (int  row = 0; row < self->mapSize.y; row++) {
		for (int  col = 0; col < self->mapSize.x; col++) {
			URGC_VAR_CLEANUP_CLASS SuiDesigner3d_w3e$W3eCorner*  corner = (corner=NULL,urgc_init_var_class((void**)&corner, SuiDesigner3d_w3e$W3eCorner_new(&corner) ));
			corner->load(corner, br) ;
			self->corners->add(self->corners, corner) ;
		}
	}
}





