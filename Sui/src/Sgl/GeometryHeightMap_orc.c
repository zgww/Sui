
#include "GeometryHeightMap_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../nanovg/stb_image.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Json/Json_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$ImgInfo_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$ImgInfo", sizeof( Sgl$ImgInfo ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "width", OrcMetaType_int, offsetof(Sgl$ImgInfo, width), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "height", OrcMetaType_int, offsetof(Sgl$ImgInfo, height), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "channel", OrcMetaType_int, offsetof(Sgl$ImgInfo, channel), 0, 0, 0, 0);//int
		orc_metaField_primitive(&pNext, "data", OrcMetaType_char, offsetof(Sgl$ImgInfo, data), 0, 0, 1, 1);//unsignedchar
    }
	return meta;
}

//vtable instance
Vtable_Sgl$GeometryHeightMap _vtable_Sgl$GeometryHeightMap;

// init meta

void Sgl$GeometryHeightMap_initMeta(Vtable_Sgl$GeometryHeightMap *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "incx", OrcMetaType_float, offsetof(Sgl$GeometryHeightMap, incx), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "incz", OrcMetaType_float, offsetof(Sgl$GeometryHeightMap, incz), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "texInc", OrcMetaType_float, offsetof(Sgl$GeometryHeightMap, texInc), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "heightScale", OrcMetaType_float, offsetof(Sgl$GeometryHeightMap, heightScale), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "startX", OrcMetaType_float, offsetof(Sgl$GeometryHeightMap, startX), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "startY", OrcMetaType_float, offsetof(Sgl$GeometryHeightMap, startY), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "startZ", OrcMetaType_float, offsetof(Sgl$GeometryHeightMap, startZ), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "path", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(Sgl$GeometryHeightMap, path), true, false, 1);

	orc_metaField_method(&pNext, "toJson", offsetof(Sgl$GeometryHeightMap, toJson));
	orc_metaField_method(&pNext, "fromJson", offsetof(Sgl$GeometryHeightMap, fromJson));
	orc_metaField_method(&pNext, "getHeight", offsetof(Sgl$GeometryHeightMap, getHeight));
	orc_metaField_method(&pNext, "buildByPath", offsetof(Sgl$GeometryHeightMap, buildByPath));
	orc_metaField_method(&pNext, "calcNormals", offsetof(Sgl$GeometryHeightMap, calcNormals));
}


// vtable init


Vtable_Sgl$GeometryHeightMap* Vtable_Sgl$GeometryHeightMap_init(Vtable_Sgl$GeometryHeightMap* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryHeightMap;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryHeightMap_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryHeightMap";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryHeightMap_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryHeightMap_fini(Sgl$GeometryHeightMap *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((Sgl$GeometryHeightMap*)self)->path);

}

// init fields function


void Sgl$GeometryHeightMap_init_fields(Sgl$GeometryHeightMap *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryHeightMap_fini;
	//fields
    {
	((Sgl$GeometryHeightMap*)self)->incx = 10;
	((Sgl$GeometryHeightMap*)self)->incz = 10;
	((Sgl$GeometryHeightMap*)self)->texInc = 1;
	((Sgl$GeometryHeightMap*)self)->heightScale = 2.0;
	((Sgl$GeometryHeightMap*)self)->startX = -600;
	((Sgl$GeometryHeightMap*)self)->startY = 0;
	((Sgl$GeometryHeightMap*)self)->startZ = -600;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryHeightMap*)self)->path, NULL);
    }
	((Object*)self)->dtor = (void*)Sgl$GeometryHeightMap$dtor;
	((Sgl$GeometryHeightMap*)self)->toJson = (void*)Sgl$GeometryHeightMap$toJson;
	((Sgl$GeometryHeightMap*)self)->fromJson = (void*)Sgl$GeometryHeightMap$fromJson;
	((Sgl$GeometryHeightMap*)self)->getHeight = (void*)Sgl$GeometryHeightMap$getHeight;
	((Sgl$Geometry*)self)->build = (void*)Sgl$GeometryHeightMap$build;
	((Sgl$GeometryHeightMap*)self)->buildByPath = (void*)Sgl$GeometryHeightMap$buildByPath;
	((Sgl$GeometryHeightMap*)self)->calcNormals = (void*)Sgl$GeometryHeightMap$calcNormals;
}

// init function

void Sgl$GeometryHeightMap_init(Sgl$GeometryHeightMap *self, void *pOwner){
    Vtable_Sgl$GeometryHeightMap_init(&_vtable_Sgl$GeometryHeightMap);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryHeightMap;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryHeightMap_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryHeightMap * Sgl$GeometryHeightMap_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryHeightMap *self = calloc(1, sizeof(Sgl$GeometryHeightMap));
	
    Sgl$GeometryHeightMap_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryHeightMap$dtor(Sgl$GeometryHeightMap *  self){
	printf(".GeometryHeightMap\n") ;
}


void  Sgl$GeometryHeightMap$toJson(Sgl$GeometryHeightMap *  self, Json$Json *  jo){
	jo->putNumber(jo, "incx", self->incx) ;
	jo->putNumber(jo, "incz", self->incz) ;
	jo->putNumber(jo, "texInc", self->texInc) ;
	jo->putNumber(jo, "heightScale", self->heightScale) ;
	jo->putNumber(jo, "startX", self->startX) ;
	jo->putNumber(jo, "startY", self->startY) ;
	jo->putNumber(jo, "startZ", self->startZ) ;
	jo->putString(jo, "path", self->path) ;
}


void  Sgl$GeometryHeightMap$fromJson(Sgl$GeometryHeightMap *  self, Json$Json *  jo){
	jo->getToFloat(jo, "incx", &self->incx) ;
	jo->getToFloat(jo, "incz", &self->incz) ;
	jo->getToFloat(jo, "texInc", &self->texInc) ;
	jo->getToFloat(jo, "heightScale", &self->heightScale) ;
	jo->getToFloat(jo, "startX", &self->startX) ;
	jo->getToFloat(jo, "startY", &self->startY) ;
	jo->getToFloat(jo, "startZ", &self->startZ) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_1 = NULL;
	urgc_set_field_class(self, (void * )offsetof(Sgl$GeometryHeightMap, path) , jo->getString(&tmpReturn_1, jo, "path") ) ;
}


float  Sgl$GeometryHeightMap$getHeight(Sgl$GeometryHeightMap *  self, Sgl$ImgInfo *  info, int  row, int  col){
	int  idx = row * info->width * info->channel + col * info->channel;
	unsigned char  r = info->data[idx + 0];
	unsigned char  g = info->data[idx + 1];
	unsigned char  b = info->data[idx + 2];
	unsigned char  a = info->data[idx + 3];
	return r * self->heightScale + self->startY; 
}


void  Sgl$GeometryHeightMap$build(Sgl$GeometryHeightMap *  self){
	if (self->path) {
		self->buildByPath(self, self->path->str) ;
	}
}


void  Sgl$GeometryHeightMap$buildByPath(Sgl$GeometryHeightMap *  self, const char *  path){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  vtxs = (vtxs=NULL,urgc_init_var_class((void**)&vtxs, Sgl$Buffer_new(&vtxs) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uvs = (uvs=NULL,urgc_init_var_class((void**)&uvs, Sgl$Buffer_new(&uvs) ));
	stbi_set_flip_vertically_on_load(true) ;
	Sgl$ImgInfo info;
	info.data = stbi_load(path, &info.width, &info.height, &info.channel, 0) ;
	stbi_set_flip_vertically_on_load(false) ;
	printf("png:%d,%d,%d\n", info.width, info.height, info.channel) ;
	for (int  row = 0; row < info.height; row++) {
		for (int  col = 0; col < info.width; col++) {
			float  x = col * self->incx + self->startX;
			float  z = row * self->incz + self->startZ;
			Sgl$Buffer$appendFloat3(vtxs, x, self->getHeight(self, &info, row, col) , z) ;
			Sgl$Buffer$appendFloat2(uvs, self->texInc * col / (float )info.width, self->texInc * row / (float )info.height) ;
			if (col < info.width - 1 && row < info.height - 1) {
				int  lt = row * info.width + col;
				int  lb = (row + 1) * info.width + col;
				int  rb = (row + 1) * info.width + col + 1;
				int  rt = row * info.width + col + 1;
				Sgl$Buffer$appendInt3(face, lb, rb, rt) ;
				Sgl$Buffer$appendInt3(face, lb, rt, lt) ;
			}
		}
	}
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = self->calcNormals((nmls = NULL,&nmls), self, vtxs, info.width, info.height) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", vtxs, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", nmls, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uvs, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}


Sgl$Buffer*  Sgl$GeometryHeightMap$calcNormals(Sgl$Buffer **  __outRef__, Sgl$GeometryHeightMap *  self, Sgl$Buffer *  vtxs, int  width, int  height){
	float *  posArr = vtxs->data;
	SuiCore$Vec3 v0;
	SuiCore$Vec3 v1;
	SuiCore$Vec3 v2;
	SuiCore$Vec3 v3;
	SuiCore$Vec3 v4;
	SuiCore$Vec3 v12;
	SuiCore$Vec3 v23;
	SuiCore$Vec3 v34;
	SuiCore$Vec3 v41;
	SuiCore$Vec3 normal;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  nmls = (nmls=NULL,urgc_init_var_class((void**)&nmls, Sgl$Buffer_new(&nmls) ));
	Sgl$Buffer$expandCapacity(nmls, width * height * 3) ;
	for (int  row = 0; row < height; row++) {
		for (int  col = 0; col < width; col++) {
			if (row > 0 && row < height - 1 && col > 0 && col < width - 1) {
				int  i0 = row * width * 3 + col * 3;
				v0.x = posArr[i0];
				v0.y = posArr[i0 + 1];
				v0.z = posArr[i0 + 2];
				int  i1 = row * width * 3 + (col - 1) * 3;
				v1.x = posArr[i1];
				v1.y = posArr[i1 + 1];
				v1.z = posArr[i1 + 2];
				v1 = SuiCore$Vec3$sub(&v1, v0) ;
				int  i2 = (row + 1) * width * 3 + col * 3;
				v2.x = posArr[i2];
				v2.y = posArr[i2 + 1];
				v2.z = posArr[i2 + 2];
				v2 = SuiCore$Vec3$sub(&v2, v0) ;
				int  i3 = row * width * 3 + (col + 1) * 3;
				v3.x = posArr[i3];
				v3.y = posArr[i3 + 1];
				v3.z = posArr[i3 + 2];
				v3 = SuiCore$Vec3$sub(&v3, v0) ;
				int  i4 = (row - 1) * width * 3 + col * 3;
				v4.x = posArr[i4];
				v4.y = posArr[i4 + 1];
				v4.z = posArr[i4 + 2];
				v4 = SuiCore$Vec3$sub(&v4, v0) ;
				v12 = SuiCore$Vec3$cross(&v1, v2) ;
				v12 = SuiCore$Vec3$normal(&v12) ;
				v23 = SuiCore$Vec3$cross(&v2, v3) ;
				v23 = SuiCore$Vec3$normal(&v23) ;
				v34 = SuiCore$Vec3$cross(&v3, v4) ;
				v34 = SuiCore$Vec3$normal(&v34) ;
				v41 = SuiCore$Vec3$cross(&v4, v1) ;
				v41 = SuiCore$Vec3$normal(&v41) ;
				normal = SuiCore$Vec3$add(&v12, v23) ;
				normal = SuiCore$Vec3$add(&normal, v34) ;
				normal = SuiCore$Vec3$add(&normal, v41) ;
				normal = SuiCore$Vec3$normal(&normal) ;
			}
			else {
				normal.x = 0;
				normal.y = 1;
				normal.z = 0;
			}
			Sgl$Buffer$appendFloat3(nmls, normal.x, normal.y, normal.z) ;
		}
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, nmls) ; 
}



void  Sgl$testHeightMap(){
	URGC_VAR_CLEANUP_CLASS Sgl$GeometryHeightMap*  g = (g=NULL,urgc_init_var_class((void**)&g, Sgl$GeometryHeightMap_new(&g) ));
	g->buildByPath(g, "../asset/heightmap.png") ;
}



