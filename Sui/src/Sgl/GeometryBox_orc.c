
#include "GeometryBox_orc.h" 

#include <stdio.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Program_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Orc/String_orc.h"
#include "../Json/Json_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryBox _vtable_Sgl$GeometryBox;

// init meta

void Sgl$GeometryBox_initMeta(Vtable_Sgl$GeometryBox *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_struct(&pNext, "center", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$GeometryBox, center), false, false, 0);
	orc_metaField_primitive(&pNext, "width", OrcMetaType_float, offsetof(Sgl$GeometryBox, width), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "height", OrcMetaType_float, offsetof(Sgl$GeometryBox, height), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "depth", OrcMetaType_float, offsetof(Sgl$GeometryBox, depth), 0, 0, 0, 0);//float
	orc_metaField_primitive(&pNext, "widthSegments", OrcMetaType_int, offsetof(Sgl$GeometryBox, widthSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "heightSegments", OrcMetaType_int, offsetof(Sgl$GeometryBox, heightSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "depthSegments", OrcMetaType_int, offsetof(Sgl$GeometryBox, depthSegments), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(Sgl$GeometryBox, color), 0, 0, 0, 0);//int

	orc_metaField_method(&pNext, "toJson", offsetof(Sgl$GeometryBox, toJson));
	orc_metaField_method(&pNext, "fromJson", offsetof(Sgl$GeometryBox, fromJson));
	orc_metaField_method(&pNext, "mkPlane", offsetof(Sgl$GeometryBox, mkPlane));
}


// vtable init


Vtable_Sgl$GeometryBox* Vtable_Sgl$GeometryBox_init(Vtable_Sgl$GeometryBox* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryBox;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryBox_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryBox";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryBox_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryBox_fini(Sgl$GeometryBox *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放
	

}

// init fields function


void Sgl$GeometryBox_init_fields(Sgl$GeometryBox *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryBox_fini;
	//fields
    {
	((Sgl$GeometryBox*)self)->width = 100;
	((Sgl$GeometryBox*)self)->height = 100;
	((Sgl$GeometryBox*)self)->depth = 100;
	((Sgl$GeometryBox*)self)->widthSegments = 1;
	((Sgl$GeometryBox*)self)->heightSegments = 1;
	((Sgl$GeometryBox*)self)->depthSegments = 1;
	((Sgl$GeometryBox*)self)->color = 0xffff0000;
    }
	((Sgl$GeometryBox*)self)->toJson = (void*)Sgl$GeometryBox$toJson;
	((Sgl$GeometryBox*)self)->fromJson = (void*)Sgl$GeometryBox$fromJson;
	((Sgl$GeometryBox*)self)->mkPlane = (void*)Sgl$GeometryBox$mkPlane;
	((Sgl$Geometry*)self)->build = (void*)Sgl$GeometryBox$build;
}

// init function

void Sgl$GeometryBox_init(Sgl$GeometryBox *self, void *pOwner){
    Vtable_Sgl$GeometryBox_init(&_vtable_Sgl$GeometryBox);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryBox;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryBox_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryBox * Sgl$GeometryBox_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryBox *self = calloc(1, sizeof(Sgl$GeometryBox));
	
    Sgl$GeometryBox_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryBox$toJson(Sgl$GeometryBox *  self, Json$Json *  jo){
	jo->putNumber(jo, "width", self->width) ;
	jo->putNumber(jo, "height", self->height) ;
	jo->putNumber(jo, "depth", self->depth) ;
	jo->putNumber(jo, "widthSegments", self->widthSegments) ;
	jo->putNumber(jo, "heightSegments", self->heightSegments) ;
	jo->putNumber(jo, "depthSegments", self->depthSegments) ;
	jo->putNumber(jo, "color", self->color) ;
	URGC_VAR_CLEANUP_CLASS Json$Json*  tmpReturn_1 = NULL;
	jo->put(jo, "center", Json$Json_toJsonByMetaStruct(&tmpReturn_1, &self->center, metaStructOf(SuiCore$Vec3) ) ) ;
}


void  Sgl$GeometryBox$fromJson(Sgl$GeometryBox *  self, Json$Json *  jo){
	jo->getToFloat(jo, "width", &self->width) ;
	jo->getToFloat(jo, "height", &self->height) ;
	jo->getToFloat(jo, "depth", &self->depth) ;
	jo->getToInt(jo, "widthSegments", &self->widthSegments) ;
	jo->getToInt(jo, "heightSegments", &self->heightSegments) ;
	jo->getToInt(jo, "depthSegments", &self->depthSegments) ;
	jo->getToInt(jo, "color", &self->color) ;
	jo->getToStruct(jo, "center", &self->center, metaStructOf(SuiCore$Vec3) ) ;
}


void  Sgl$GeometryBox$mkPlane(Sgl$GeometryBox *  self, int  segcols, int  segrows, float  dx, float  dy, SuiCore$Vec3 xfactor, SuiCore$Vec3 yfactor, SuiCore$Vec3 p0, SuiCore$Vec3 normalVec3, Sgl$Buffer *  position, Sgl$Buffer *  normal, Sgl$Buffer *  uv, Sgl$Buffer *  face, Sgl$Buffer *  color){
	int  cols = segcols + 1;
	int  rows = segrows + 1;
	float  stepX = dx / segcols;
	float  stepY = dy / segrows;
	int  startVertIndex = Sgl$Buffer$floatSize(position)  / 3;
	SuiCore$Rgbaf cf = SuiCore$mkRgbafByInt(self->color) ;
	for (int  r = 0; r < rows; r++) {
		for (int  c = 0; c < cols; c++) {
			SuiCore$Vec3 x = SuiCore$Vec3$scale(&xfactor, c * stepX) ;
			SuiCore$Vec3 y = SuiCore$Vec3$scale(&yfactor, r * stepY) ;
			SuiCore$Vec3 pos = SuiCore$Vec3$add(&p0, SuiCore$Vec3$add(&x, y) ) ;
			Sgl$Buffer$appendFloat3(position, pos.x, pos.y, pos.z) ;
			Sgl$Buffer$appendFloat3(normal, normalVec3.x, normalVec3.y, normalVec3.z) ;
			Sgl$Buffer$appendFloat4(color, cf.r, cf.g, cf.b, cf.a) ;
			float  u = c / (float )(segcols);
			float  v = r / (float )segrows;
			Sgl$Buffer$appendFloat2(uv, u, v) ;
			int  lb = startVertIndex + r * cols + c;
			int  rb = lb + 1;
			int  rt = lb + cols + 1;
			int  lt = lb + cols;
			if (r < rows - 1 && c < cols - 1) {
				Sgl$Buffer$appendInt3(face, lb, rb, rt) ;
				Sgl$Buffer$appendInt3(face, lb, rt, lt) ;
			}
		}
	}
}


void  Sgl$GeometryBox$build(Sgl$GeometryBox *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  position = (position=NULL,urgc_init_var_class((void**)&position, Sgl$Buffer_new(&position) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv = (uv=NULL,urgc_init_var_class((void**)&uv, Sgl$Buffer_new(&uv) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  normal = (normal=NULL,urgc_init_var_class((void**)&normal, Sgl$Buffer_new(&normal) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  color = (color=NULL,urgc_init_var_class((void**)&color, Sgl$Buffer_new(&color) ));
	float  startX = self->center.x - self->width / 2.0;
	float  startY = self->center.y - self->height / 2.0;
	float  startZ = self->center.z - self->depth / 2.0;
	float  endX = self->center.x + self->width / 2.0;
	float  endY = self->center.y + self->height / 2.0;
	float  endZ = self->center.z + self->depth / 2.0;
	if (1) {
		self->mkPlane(self, self->widthSegments, self->heightSegments, endX - startX, endY - startY, SuiCore$mkVec3(1, 0, 0) , SuiCore$mkVec3(0, 1, 0) , SuiCore$mkVec3(startX, startY, endZ) , SuiCore$mkVec3(0, 0, 1) , position, normal, uv, face, color) ;
	}
	if (1) {
		self->mkPlane(self, self->depthSegments, self->heightSegments, -endZ + startZ, endY - startY, SuiCore$mkVec3(0, 0, 1) , SuiCore$mkVec3(0, 1, 0) , SuiCore$mkVec3(endX, startY, endZ) , SuiCore$mkVec3(1, 0, 0) , position, normal, uv, face, color) ;
	}
	if (1) {
		self->mkPlane(self, self->widthSegments, self->heightSegments, -endX + startX, endY - startY, SuiCore$mkVec3(1, 0, 0) , SuiCore$mkVec3(0, 1, 0) , SuiCore$mkVec3(endX, startY, startZ) , SuiCore$mkVec3(0, 0, -1) , position, normal, uv, face, color) ;
	}
	if (1) {
		self->mkPlane(self, self->depthSegments, self->heightSegments, endZ - startZ, endY - startY, SuiCore$mkVec3(0, 0, 1) , SuiCore$mkVec3(0, 1, 0) , SuiCore$mkVec3(startX, startY, startZ) , SuiCore$mkVec3(-1, 0, 0) , position, normal, uv, face, color) ;
	}
	if (1) {
		self->mkPlane(self, self->widthSegments, self->depthSegments, endX - startX, endZ - startZ, SuiCore$mkVec3(1, 0, 0) , SuiCore$mkVec3(0, 0, 1) , SuiCore$mkVec3(startX, startY, startZ) , SuiCore$mkVec3(0, -1, 0) , position, normal, uv, face, color) ;
	}
	if (1) {
		self->mkPlane(self, self->widthSegments, self->depthSegments, endX - startX, -endZ + startZ, SuiCore$mkVec3(1, 0, 0) , SuiCore$mkVec3(0, 0, 1) , SuiCore$mkVec3(startX, endY, endZ) , SuiCore$mkVec3(0, 1, 0) , position, normal, uv, face, color) ;
	}
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", position, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", normal, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "color", color, 4) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uv, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}





