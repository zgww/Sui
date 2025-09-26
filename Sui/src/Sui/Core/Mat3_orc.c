
#include "Mat3_orc.h" 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../Orc/Math_orc.h"
#include "./Vec3_orc.h"
#include "../../Sgl/Mat_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* SuiCore$Mat3_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "SuiCore$Mat3", sizeof( SuiCore$Mat3 ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "data", OrcMetaType_float, offsetof(SuiCore$Mat3, data), 0, 0, 1, 1);//float
    }
	return meta;
}
SuiCore$Mat3 *  SuiCore$Mat3$set(SuiCore$Mat3 *  self, float  n11, float  n12, float  n13, float  n21, float  n22, float  n23, float  n31, float  n32, float  n33){
	float *  te = self->data;
	te[0] = n11;
	te[1] = n21;
	te[2] = n31;
	te[3] = n12;
	te[4] = n22;
	te[5] = n32;
	te[6] = n13;
	te[7] = n23;
	te[8] = n33;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$identity(SuiCore$Mat3 *  self){
	SuiCore$Mat3$set(self, 1, 0, 0, 0, 1, 0, 0, 0, 1) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$copy(SuiCore$Mat3 *  self, SuiCore$Mat3 m){
	float *  te = self->data;
	float *  me = m.data;
	te[0] = me[0];
	te[1] = me[1];
	te[2] = me[2];
	te[3] = me[3];
	te[4] = me[4];
	te[5] = me[5];
	te[6] = me[6];
	te[7] = me[7];
	te[8] = me[8];
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$extractBasis(SuiCore$Mat3 *  self, SuiCore$Vec3 xAxis, SuiCore$Vec3 yAxis, SuiCore$Vec3 zAxis){
	SuiCore$Vec3$setFromMatrix3Column(&xAxis, *self, 0) ;
	SuiCore$Vec3$setFromMatrix3Column(&yAxis, *self, 1) ;
	SuiCore$Vec3$setFromMatrix3Column(&zAxis, *self, 2) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$setFromMatrix4(SuiCore$Mat3 *  self, Sgl$Mat m){
	float *  me = m.data;
	SuiCore$Mat3$set(self, me[0], me[4], me[8], me[1], me[5], me[9], me[2], me[6], me[10]) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$multiplyLocal(SuiCore$Mat3 *  self, SuiCore$Mat3 m){
	return SuiCore$Mat3$multiplyMatricesLocal(self, *self, m) ; 
}

SuiCore$Mat3 *  SuiCore$Mat3$premultiplyLocal(SuiCore$Mat3 *  self, SuiCore$Mat3 m){
	return SuiCore$Mat3$multiplyMatricesLocal(self, m, *self) ; 
}

SuiCore$Mat3 *  SuiCore$Mat3$multiplyMatricesLocal(SuiCore$Mat3 *  self, SuiCore$Mat3 a, SuiCore$Mat3 b){
	float *  ae = a.data;
	float *  be = b.data;
	float *  te = self->data;
	float  a11 = ae[0];
	float  a12 = ae[3];
	float  a13 = ae[6];
	float  a21 = ae[1];
	float  a22 = ae[4];
	float  a23 = ae[7];
	float  a31 = ae[2];
	float  a32 = ae[5];
	float  a33 = ae[8];
	float  b11 = be[0];
	float  b12 = be[3];
	float  b13 = be[6];
	float  b21 = be[1];
	float  b22 = be[4];
	float  b23 = be[7];
	float  b31 = be[2];
	float  b32 = be[5];
	float  b33 = be[8];
	te[0] = a11 * b11 + a12 * b21 + a13 * b31;
	te[3] = a11 * b12 + a12 * b22 + a13 * b32;
	te[6] = a11 * b13 + a12 * b23 + a13 * b33;
	te[1] = a21 * b11 + a22 * b21 + a23 * b31;
	te[4] = a21 * b12 + a22 * b22 + a23 * b32;
	te[7] = a21 * b13 + a22 * b23 + a23 * b33;
	te[2] = a31 * b11 + a32 * b21 + a33 * b31;
	te[5] = a31 * b12 + a32 * b22 + a33 * b32;
	te[8] = a31 * b13 + a32 * b23 + a33 * b33;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$multiplyScalarLocal(SuiCore$Mat3 *  self, float  s){
	float *  te = self->data;
	te[0] *= s;
	te[3] *= s;
	te[6] *= s;
	te[1] *= s;
	te[4] *= s;
	te[7] *= s;
	te[2] *= s;
	te[5] *= s;
	te[8] *= s;
	return self; 
}

float  SuiCore$Mat3$determinant(SuiCore$Mat3 *  self){
	float *  te = self->data;
	float  a = te[0];
	float  b = te[1];
	float  c = te[2];
	float  d = te[3];
	float  e = te[4];
	float  f = te[5];
	float  g = te[6];
	float  h = te[7];
	float  i = te[8];
	return a * e * i - a * f * h - b * d * i + b * f * g + c * d * h - c * e * g; 
}

SuiCore$Mat3 *  SuiCore$Mat3$invertLocal(SuiCore$Mat3 *  self){
	float *  te = self->data;
	float  n11 = te[0];
	float  n21 = te[1];
	float  n31 = te[2];
	float  n12 = te[3];
	float  n22 = te[4];
	float  n32 = te[5];
	float  n13 = te[6];
	float  n23 = te[7];
	float  n33 = te[8];
	float  t11 = n33 * n22 - n32 * n23;
	float  t12 = n32 * n13 - n33 * n12;
	float  t13 = n23 * n12 - n22 * n13;
	float  det = n11 * t11 + n21 * t12 + n31 * t13;
	if (Orc$eqFloat(det, 0) ) {
		return SuiCore$Mat3$set(self, 0, 0, 0, 0, 0, 0, 0, 0, 0) ; 
	}
	float  detInv = 1 / det;
	te[0] = t11 * detInv;
	te[1] = (n31 * n23 - n33 * n21) * detInv;
	te[2] = (n32 * n21 - n31 * n22) * detInv;
	te[3] = t12 * detInv;
	te[4] = (n33 * n11 - n31 * n13) * detInv;
	te[5] = (n31 * n12 - n32 * n11) * detInv;
	te[6] = t13 * detInv;
	te[7] = (n21 * n13 - n23 * n11) * detInv;
	te[8] = (n22 * n11 - n21 * n12) * detInv;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$transposeLocal(SuiCore$Mat3 *  self){
	float  tmp;
	float *  m = self->data;
	tmp = m[1];
	m[1] = m[3];
	m[3] = tmp;
	tmp = m[2];
	m[2] = m[6];
	m[6] = tmp;
	tmp = m[5];
	m[5] = m[7];
	m[7] = tmp;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$getNormalMatrix(SuiCore$Mat3 *  self, Sgl$Mat matrix4){
	return SuiCore$Mat3$transposeLocal(SuiCore$Mat3$invertLocal(SuiCore$Mat3$setFromMatrix4(self, matrix4) ) ) ; 
}

SuiCore$Mat3 *  SuiCore$Mat3$transposeIntoArray(SuiCore$Mat3 *  self, float *  r){
	float *  m = self->data;
	r[0] = m[0];
	r[1] = m[3];
	r[2] = m[6];
	r[3] = m[1];
	r[4] = m[4];
	r[5] = m[7];
	r[6] = m[2];
	r[7] = m[5];
	r[8] = m[8];
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$setUvTransform(SuiCore$Mat3 *  self, float  tx, float  ty, float  sx, float  sy, float  rotation, float  cx, float  cy){
	float  c = cos(rotation) ;
	float  s = sin(rotation) ;
	SuiCore$Mat3$set(self, sx * c, sx * s, -sx * (c * cx + s * cy) + cx + tx, -sy * s, sy * c, -sy * (-s * cx + c * cy) + cy + ty, 0, 0, 1) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$scaleLocal(SuiCore$Mat3 *  self, float  sx, float  sy){
	SuiCore$Mat3 _m3;
	SuiCore$Mat3$makeScale(&_m3, sx, sy) ;
	SuiCore$Mat3$premultiplyLocal(self, _m3) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$rotateLocal(SuiCore$Mat3 *  self, float  theta){
	SuiCore$Mat3 _m3;
	SuiCore$Mat3$makeRotation(&_m3, -theta) ;
	SuiCore$Mat3$premultiplyLocal(self, _m3) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$translateLocal(SuiCore$Mat3 *  self, float  tx, float  ty){
	SuiCore$Mat3 _m3;
	SuiCore$Mat3$makeTranslation(&_m3, tx, ty) ;
	SuiCore$Mat3$premultiplyLocal(self, _m3) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$makeTranslation(SuiCore$Mat3 *  self, float  x, float  y){
	SuiCore$Mat3$set(self, 1, 0, x, 0, 1, y, 0, 0, 1) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$makeRotation(SuiCore$Mat3 *  self, float  theta){
	float  c = cos(theta) ;
	float  s = sin(theta) ;
	SuiCore$Mat3$set(self, c, -s, 0, s, c, 0, 0, 0, 1) ;
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$makeScale(SuiCore$Mat3 *  self, float  x, float  y){
	SuiCore$Mat3$set(self, x, 0, 0, 0, y, 0, 0, 0, 1) ;
	return self; 
}

bool  SuiCore$Mat3$equals(SuiCore$Mat3 *  self, SuiCore$Mat3 matrix){
	float *  te = self->data;
	float *  me = matrix.data;
	for (int  i = 0; i < 9; i++) {
		if (!Orc$eqFloat(te[i], me[i]) ) {
			return false; 
		}
	}
	return true; 
}

SuiCore$Mat3 *  SuiCore$Mat3$fromArray(SuiCore$Mat3 *  self, float *  array, int  offset){
	for (int  i = 0; i < 9; i++) {
		self->data[i] = array[i + offset];
	}
	return self; 
}

SuiCore$Mat3 *  SuiCore$Mat3$toArray(SuiCore$Mat3 *  self, float *  array, int  offset){
	float *  te = self->data;
	array[offset] = te[0];
	array[offset + 1] = te[1];
	array[offset + 2] = te[2];
	array[offset + 3] = te[3];
	array[offset + 4] = te[4];
	array[offset + 5] = te[5];
	array[offset + 6] = te[6];
	array[offset + 7] = te[7];
	array[offset + 8] = te[8];
	return array; 
}

SuiCore$Mat3 SuiCore$Mat3$clone(SuiCore$Mat3 *  self){
	return *self; 
}



