
#include "GeometryLine_orc.h" 

#include <stdio.h>
#include <math.h>
#include "./UnitOpengl.h"
#include "./Buffer_orc.h"
#include "./Vbo_orc.h"
#include "./Material_orc.h"
#include "./Camera_orc.h"
#include "./Mat_orc.h"
#include "./Program_orc.h"
#include "./SpotLight_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Color_orc.h"
#include "../Orc/String_orc.h"
#include "./Geometry_orc.h"


// static struct 


// static function declaration



//vtable instance
Vtable_Sgl$GeometryLine _vtable_Sgl$GeometryLine;

// init meta

void Sgl$GeometryLine_initMeta(Vtable_Sgl$GeometryLine *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "lineWidth", OrcMetaType_float, offsetof(Sgl$GeometryLine, lineWidth), 0, 0, 0, 0);//float
	orc_metaField_class(&pNext, "vtxBuf", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryLine, vtxBuf), true, false, 1);
	orc_metaField_class(&pNext, "colorBuf", ((Vtable_Object*)Vtable_Sgl$Buffer_init(0)), offsetof(Sgl$GeometryLine, colorBuf), true, false, 1);
	orc_metaField_primitive(&pNext, "color", OrcMetaType_int, offsetof(Sgl$GeometryLine, color), 0, 0, 0, 0);//int
	orc_metaField_struct(&pNext, "lastVtx", SuiCore$Vec3_getOrInitMetaStruct(), offsetof(Sgl$GeometryLine, lastVtx), false, false, 0);
	orc_metaField_primitive(&pNext, "hasLastVtx", OrcMetaType_bool, offsetof(Sgl$GeometryLine, hasLastVtx), 0, 0, 0, 0);//bool

	orc_metaField_method(&pNext, "clear", offsetof(Sgl$GeometryLine, clear));
	orc_metaField_method(&pNext, "moveToVec3_color", offsetof(Sgl$GeometryLine, moveToVec3_color));
	orc_metaField_method(&pNext, "moveToVec3", offsetof(Sgl$GeometryLine, moveToVec3));
	orc_metaField_method(&pNext, "lineToVec3", offsetof(Sgl$GeometryLine, lineToVec3));
	orc_metaField_method(&pNext, "lineToVec3_color", offsetof(Sgl$GeometryLine, lineToVec3_color));
	orc_metaField_method(&pNext, "moveTo_color", offsetof(Sgl$GeometryLine, moveTo_color));
	orc_metaField_method(&pNext, "moveTo", offsetof(Sgl$GeometryLine, moveTo));
	orc_metaField_method(&pNext, "lineTo", offsetof(Sgl$GeometryLine, lineTo));
	orc_metaField_method(&pNext, "lineTo_color", offsetof(Sgl$GeometryLine, lineTo_color));
	orc_metaField_method(&pNext, "appendVertex", offsetof(Sgl$GeometryLine, appendVertex));
	orc_metaField_method(&pNext, "appendVertexAndColor", offsetof(Sgl$GeometryLine, appendVertexAndColor));
	orc_metaField_method(&pNext, "updateBuffer", offsetof(Sgl$GeometryLine, updateBuffer));
	orc_metaField_method(&pNext, "draw", offsetof(Sgl$GeometryLine, draw));
	orc_metaField_method(&pNext, "build", offsetof(Sgl$GeometryLine, build));
	orc_metaField_method(&pNext, "buildSpotLightHelper", offsetof(Sgl$GeometryLine, buildSpotLightHelper));
	orc_metaField_method(&pNext, "buildCameraHelper", offsetof(Sgl$GeometryLine, buildCameraHelper));
}


// vtable init


Vtable_Sgl$GeometryLine* Vtable_Sgl$GeometryLine_init(Vtable_Sgl$GeometryLine* pvt){
    if (pvt == NULL){
        pvt = &_vtable_Sgl$GeometryLine;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Sgl$Geometry_init(&_vtable_Sgl$Geometry);

	// init by super vtable init function
    Vtable_Sgl$Geometry_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Sgl$Geometry;
    ((Vtable_Object*)pvt)->make = (void*)&Sgl$GeometryLine_new;
    ((Vtable_Object*)pvt)->className = "Sgl$GeometryLine";

    ((Vtable_Object*)pvt)->initMeta = (void*)Sgl$GeometryLine_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void Sgl$GeometryLine_fini(Sgl$GeometryLine *self){
	//super fini
    Sgl$Geometry_fini((Sgl$Geometry *)self);

    //字段释放


}

// init fields function


void Sgl$GeometryLine_init_fields(Sgl$GeometryLine *self){
	//super class
    Sgl$Geometry_init_fields((Sgl$Geometry*)self);

    ((Object*)self)->fini = (void*)Sgl$GeometryLine_fini;
	//fields
    {
	((Sgl$GeometryLine*)self)->lineWidth = 1.0;
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryLine*)self)->vtxBuf, Sgl$Buffer_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((Sgl$GeometryLine*)self)->colorBuf, Sgl$Buffer_new(&tmpNewOwner_2) );
	((Sgl$GeometryLine*)self)->color = 0xffff0000;
	((Sgl$GeometryLine*)self)->hasLastVtx = false;
    }
	((Sgl$GeometryLine*)self)->clear = (void*)Sgl$GeometryLine$clear;
	((Sgl$GeometryLine*)self)->moveToVec3_color = (void*)Sgl$GeometryLine$moveToVec3_color;
	((Sgl$GeometryLine*)self)->moveToVec3 = (void*)Sgl$GeometryLine$moveToVec3;
	((Sgl$GeometryLine*)self)->lineToVec3 = (void*)Sgl$GeometryLine$lineToVec3;
	((Sgl$GeometryLine*)self)->lineToVec3_color = (void*)Sgl$GeometryLine$lineToVec3_color;
	((Sgl$GeometryLine*)self)->moveTo_color = (void*)Sgl$GeometryLine$moveTo_color;
	((Sgl$GeometryLine*)self)->moveTo = (void*)Sgl$GeometryLine$moveTo;
	((Sgl$GeometryLine*)self)->lineTo = (void*)Sgl$GeometryLine$lineTo;
	((Sgl$GeometryLine*)self)->lineTo_color = (void*)Sgl$GeometryLine$lineTo_color;
	((Sgl$GeometryLine*)self)->appendVertex = (void*)Sgl$GeometryLine$appendVertex;
	((Sgl$GeometryLine*)self)->appendVertexAndColor = (void*)Sgl$GeometryLine$appendVertexAndColor;
	((Sgl$GeometryLine*)self)->updateBuffer = (void*)Sgl$GeometryLine$updateBuffer;
	((Sgl$GeometryLine*)self)->draw = (void*)Sgl$GeometryLine$draw;
	((Sgl$GeometryLine*)self)->build = (void*)Sgl$GeometryLine$build;
	((Sgl$GeometryLine*)self)->buildSpotLightHelper = (void*)Sgl$GeometryLine$buildSpotLightHelper;
	((Sgl$GeometryLine*)self)->buildCameraHelper = (void*)Sgl$GeometryLine$buildCameraHelper;
}

// init function

void Sgl$GeometryLine_init(Sgl$GeometryLine *self, void *pOwner){
    Vtable_Sgl$GeometryLine_init(&_vtable_Sgl$GeometryLine);

    ((Object*)self)->vtable = (void*)&_vtable_Sgl$GeometryLine;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    Sgl$GeometryLine_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
Sgl$GeometryLine * Sgl$GeometryLine_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    Sgl$GeometryLine *self = calloc(1, sizeof(Sgl$GeometryLine));
	
    Sgl$GeometryLine_init(self, pOwner);
    return self;
}


// class members
void  Sgl$GeometryLine$clear(Sgl$GeometryLine *  self){
	Sgl$Buffer$clear(self->vtxBuf) ;
	Sgl$Buffer$clear(self->colorBuf) ;
}


void  Sgl$GeometryLine$moveToVec3_color(Sgl$GeometryLine *  self, SuiCore$Vec3 v, int  color){
	self->moveToVec3(self, v) ;
	self->color = color;
}


void  Sgl$GeometryLine$moveToVec3(Sgl$GeometryLine *  self, SuiCore$Vec3 v){
	self->moveTo(self, v.x, v.y, v.z) ;
}


void  Sgl$GeometryLine$lineToVec3(Sgl$GeometryLine *  self, SuiCore$Vec3 v){
	self->lineTo(self, v.x, v.y, v.z) ;
}


void  Sgl$GeometryLine$lineToVec3_color(Sgl$GeometryLine *  self, SuiCore$Vec3 v, int  color){
	self->lineTo_color(self, v.x, v.y, v.z, color) ;
}


void  Sgl$GeometryLine$moveTo_color(Sgl$GeometryLine *  self, float  x, float  y, float  z, int  color){
	self->moveTo(self, x, y, z) ;
	self->color = color;
}


void  Sgl$GeometryLine$moveTo(Sgl$GeometryLine *  self, float  x, float  y, float  z){
	self->hasLastVtx = true;
	{
		SuiCore$Vec3 *  o = &self->lastVtx;
		
	
		o->x = x;
		o->y = y;
		o->z = z;
	}
}


void  Sgl$GeometryLine$lineTo(Sgl$GeometryLine *  self, float  x, float  y, float  z){
	self->appendVertexAndColor(self, self->lastVtx, self->color) ;
	self->lastVtx = SuiCore$mkVec3(x, y, z) ;
	self->appendVertexAndColor(self, self->lastVtx, self->color) ;
}


void  Sgl$GeometryLine$lineTo_color(Sgl$GeometryLine *  self, float  x, float  y, float  z, int  color){
	self->appendVertexAndColor(self, self->lastVtx, self->color) ;
	self->lastVtx = SuiCore$mkVec3(x, y, z) ;
	self->color = color;
	self->appendVertexAndColor(self, self->lastVtx, self->color) ;
}


void  Sgl$GeometryLine$appendVertex(Sgl$GeometryLine *  self, SuiCore$Vec3 pos){
	self->appendVertexAndColor(self, pos, self->color) ;
}


void  Sgl$GeometryLine$appendVertexAndColor(Sgl$GeometryLine *  self, SuiCore$Vec3 pos, int  color){
	SuiCore$Rgbaf c = SuiCore$mkRgbafByInt(color) ;
	self->color = color;
	Sgl$Buffer$appendFloat3(self->vtxBuf, pos.x, pos.y, pos.z) ;
	Sgl$Buffer$appendFloat4(self->colorBuf, c.r, c.g, c.b, c.a) ;
}


void  Sgl$GeometryLine$updateBuffer(Sgl$GeometryLine *  self){
	((Sgl$Geometry * )self)->applyAttrByBuffer(self, "position", self->vtxBuf, 3) ;
	((Sgl$Geometry * )self)->applyAttrByBuffer(self, "color", self->colorBuf, 4) ;
}


void  Sgl$GeometryLine$draw(Sgl$GeometryLine *  self, Sgl$Material *  matl){
	self->updateBuffer(self) ;
	matl->program->use(matl->program) ;
	matl->prepareDraw(matl) ;
	matl->updateUniforms(matl) ;
	((Sgl$Geometry * )self)->bindVertexAttribs(self, matl) ;
	glLineWidth(self->lineWidth) ;
	glDrawArrays(GL_LINES, 0, Sgl$Buffer$floatSize(self->vtxBuf)  / 3) ;
	matl->endDraw(matl) ;
}


void  Sgl$GeometryLine$build(Sgl$GeometryLine *  self){
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  buf = (buf=NULL,urgc_init_var_class((void**)&buf, Sgl$Buffer_new(&buf) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  normal = (normal=NULL,urgc_init_var_class((void**)&normal, Sgl$Buffer_new(&normal) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  uv = (uv=NULL,urgc_init_var_class((void**)&uv, Sgl$Buffer_new(&uv) ));
	URGC_VAR_CLEANUP_CLASS Sgl$Buffer*  face = (face=NULL,urgc_init_var_class((void**)&face, Sgl$Buffer_new(&face) ));
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "position", buf, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "normal", normal, 3) ;
	((Sgl$Geometry * )self)->setAttrByBuffer(self, "uv", uv, 2) ;
	((Sgl$Geometry * )self)->setIboByBuffer(self, face) ;
}


void  Sgl$GeometryLine$buildSpotLightHelper(Sgl$GeometryLine *  self, Sgl$SpotLight *  sl){
	self->clear(self) ;
	float  l = sl->distance;
	float  w = l * tan(sl->angle) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineTo_color(self, 0, -l, 0, 0xffff0000) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineTo_color(self, w, -l, 0, 0xffff0000) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineTo_color(self, -w, -l, 0, 0xffff0000) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineTo_color(self, 0, -l, w, 0xffff0000) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineTo_color(self, 0, -l, -w, 0xffff0000) ;
}


void  Sgl$GeometryLine$buildCameraHelper(Sgl$GeometryLine *  self, Sgl$Camera *  camera){
	self->clear(self) ;
	float  w = 1;
	float  h = 1;
	SuiCore$Vec3 c = camera->unprojectToView(camera, SuiCore$mkVec3(0, 0, -1) ) ;
	SuiCore$Vec3 t = camera->unprojectToView(camera, SuiCore$mkVec3(0, 0, 1) ) ;
	SuiCore$Vec3 n1 = camera->unprojectToView(camera, SuiCore$mkVec3(-w, -h, -1) ) ;
	SuiCore$Vec3 n2 = camera->unprojectToView(camera, SuiCore$mkVec3(w, -h, -1) ) ;
	SuiCore$Vec3 n3 = camera->unprojectToView(camera, SuiCore$mkVec3(-w, h, -1) ) ;
	SuiCore$Vec3 n4 = camera->unprojectToView(camera, SuiCore$mkVec3(w, h, -1) ) ;
	SuiCore$Vec3 f1 = camera->unprojectToView(camera, SuiCore$mkVec3(-w, -h, 1) ) ;
	SuiCore$Vec3 f2 = camera->unprojectToView(camera, SuiCore$mkVec3(w, -h, 1) ) ;
	SuiCore$Vec3 f3 = camera->unprojectToView(camera, SuiCore$mkVec3(-w, h, 1) ) ;
	SuiCore$Vec3 f4 = camera->unprojectToView(camera, SuiCore$mkVec3(w, h, 1) ) ;
	SuiCore$Vec3 u1 = camera->unprojectToView(camera, SuiCore$mkVec3(w * 0.7, h * 1.1, -1) ) ;
	SuiCore$Vec3 u2 = camera->unprojectToView(camera, SuiCore$mkVec3(-w * 0.7, h * 1.1, -1) ) ;
	SuiCore$Vec3 u3 = camera->unprojectToView(camera, SuiCore$mkVec3(0, h * 2, -1) ) ;
	SuiCore$Vec3 cf1 = camera->unprojectToView(camera, SuiCore$mkVec3(-w, 0, 1) ) ;
	SuiCore$Vec3 cf2 = camera->unprojectToView(camera, SuiCore$mkVec3(w, 0, 1) ) ;
	SuiCore$Vec3 cf3 = camera->unprojectToView(camera, SuiCore$mkVec3(0, -h, 1) ) ;
	SuiCore$Vec3 cf4 = camera->unprojectToView(camera, SuiCore$mkVec3(0, h, 1) ) ;
	SuiCore$Vec3 cn1 = camera->unprojectToView(camera, SuiCore$mkVec3(-w, 0, -1) ) ;
	SuiCore$Vec3 cn2 = camera->unprojectToView(camera, SuiCore$mkVec3(w, 0, -1) ) ;
	SuiCore$Vec3 cn3 = camera->unprojectToView(camera, SuiCore$mkVec3(0, -h, -1) ) ;
	SuiCore$Vec3 cn4 = camera->unprojectToView(camera, SuiCore$mkVec3(0, h, -1) ) ;
	self->color = 0xffffffff;
	self->moveTo(self, 0, 0, 0) ;
	self->lineToVec3(self, n1) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineToVec3(self, n2) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineToVec3(self, n3) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineToVec3(self, n4) ;
	self->moveToVec3(self, n1) ;
	self->lineToVec3(self, n2) ;
	self->moveToVec3(self, n2) ;
	self->lineToVec3(self, n4) ;
	self->moveToVec3(self, n3) ;
	self->lineToVec3(self, n4) ;
	self->moveToVec3(self, n1) ;
	self->lineToVec3(self, n3) ;
	self->moveToVec3(self, n1) ;
	self->lineToVec3(self, f1) ;
	self->moveToVec3(self, n2) ;
	self->lineToVec3(self, f2) ;
	self->moveToVec3(self, n3) ;
	self->lineToVec3(self, f3) ;
	self->moveToVec3(self, n4) ;
	self->lineToVec3(self, f4) ;
	self->moveToVec3(self, f1) ;
	self->lineToVec3(self, f2) ;
	self->moveToVec3(self, f2) ;
	self->lineToVec3(self, f4) ;
	self->moveToVec3(self, f3) ;
	self->lineToVec3(self, f4) ;
	self->moveToVec3(self, f1) ;
	self->lineToVec3(self, f3) ;
	self->moveTo(self, 0, 0, 0) ;
	self->lineToVec3(self, t) ;
	self->moveToVec3(self, cf1) ;
	self->lineToVec3(self, cf2) ;
	self->moveToVec3(self, cf3) ;
	self->lineToVec3(self, cf4) ;
	self->moveToVec3(self, cn1) ;
	self->lineToVec3(self, cn2) ;
	self->moveToVec3(self, cn3) ;
	self->lineToVec3(self, cn4) ;
}





