
#include "Mat_orc.h" 

#include "../Sui/Core/linmath.h"
#include "../Orc/Math_orc.h"
#include "../Sui/Core/Vec3_orc.h"
#include "../Sui/Core/Vec4_orc.h"
#include "../Sui/Core/Mat3_orc.h"
#include "../Sui/Core/Euler_orc.h"
#include "../Sui/Core/Quaternion_orc.h"


// static struct 


// static function declaration



// get or init meta 
MetaStruct* Sgl$Mat_getOrInitMetaStruct(){
    static MetaStruct *meta = NULL;
    if (meta == NULL){
        //init
        orc_initMetaStruct(&meta, "Sgl$Mat", sizeof( Sgl$Mat ));
        OrcMetaField **pNext = &meta->headMetaField;

		orc_metaField_primitive(&pNext, "data", OrcMetaType_float, offsetof(Sgl$Mat, data), 0, 0, 1, 1);//float
    }
	return meta;
}
Sgl$Mat Sgl$mkMatIdentity(){
	Sgl$Mat m;
	Sgl$Mat$identity(&m) ;
	return m; 
}

Sgl$Mat *  Sgl$Mat$set(Sgl$Mat *  self, float  n11, float  n12, float  n13, float  n14, float  n21, float  n22, float  n23, float  n24, float  n31, float  n32, float  n33, float  n34, float  n41, float  n42, float  n43, float  n44){
	float *  te = self->data;
	te[0] = n11;
	te[4] = n12;
	te[8] = n13;
	te[12] = n14;
	te[1] = n21;
	te[5] = n22;
	te[9] = n23;
	te[13] = n24;
	te[2] = n31;
	te[6] = n32;
	te[10] = n33;
	te[14] = n34;
	te[3] = n41;
	te[7] = n42;
	te[11] = n43;
	te[15] = n44;
	return self; 
}

Sgl$Mat Sgl$Mat$clone(Sgl$Mat *  self){
	return *self; 
}

Sgl$Mat *  Sgl$Mat$copy(Sgl$Mat *  self, Sgl$Mat m){
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
	te[9] = me[9];
	te[10] = me[10];
	te[11] = me[11];
	te[12] = me[12];
	te[13] = me[13];
	te[14] = me[14];
	te[15] = me[15];
	return self; 
}

Sgl$Mat *  Sgl$Mat$copyPosition(Sgl$Mat *  self, Sgl$Mat m){
	float *  te = self->data;
	float *  me = m.data;
	te[12] = me[12];
	te[13] = me[13];
	te[14] = me[14];
	return self; 
}

Sgl$Mat *  Sgl$Mat$setFromMatrix3(Sgl$Mat *  self, SuiCore$Mat3 m){
	float *  me = m.data;
	Sgl$Mat$set(self, me[0], me[3], me[6], 0, me[1], me[4], me[7], 0, me[2], me[5], me[8], 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$extractBasis(Sgl$Mat *  self, SuiCore$Vec3 *  xAxis, SuiCore$Vec3 *  yAxis, SuiCore$Vec3 *  zAxis){
	SuiCore$Vec3$setFromMatrixColumn(xAxis, *self, 0) ;
	SuiCore$Vec3$setFromMatrixColumn(yAxis, *self, 1) ;
	SuiCore$Vec3$setFromMatrixColumn(zAxis, *self, 2) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeBasis(Sgl$Mat *  self, SuiCore$Vec3 xAxis, SuiCore$Vec3 yAxis, SuiCore$Vec3 zAxis){
	Sgl$Mat$set(self, xAxis.x, yAxis.x, zAxis.x, 0, xAxis.y, yAxis.y, zAxis.y, 0, xAxis.z, yAxis.z, zAxis.z, 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$extractRotationLocal(Sgl$Mat *  self, Sgl$Mat m){
	float *  te = self->data;
	float *  me = m.data;
	SuiCore$Vec3 _v1;
	float  scaleX = 1 / SuiCore$Vec3$length(SuiCore$Vec3$setFromMatrixColumn(&_v1, m, 0) ) ;
	float  scaleY = 1 / SuiCore$Vec3$length(SuiCore$Vec3$setFromMatrixColumn(&_v1, m, 1) ) ;
	float  scaleZ = 1 / SuiCore$Vec3$length(SuiCore$Vec3$setFromMatrixColumn(&_v1, m, 2) ) ;
	te[0] = me[0] * scaleX;
	te[1] = me[1] * scaleX;
	te[2] = me[2] * scaleX;
	te[3] = 0;
	te[4] = me[4] * scaleY;
	te[5] = me[5] * scaleY;
	te[6] = me[6] * scaleY;
	te[7] = 0;
	te[8] = me[8] * scaleZ;
	te[9] = me[9] * scaleZ;
	te[10] = me[10] * scaleZ;
	te[11] = 0;
	te[12] = 0;
	te[13] = 0;
	te[14] = 0;
	te[15] = 1;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeRotationFromEuler(Sgl$Mat *  self, SuiCore$Euler euler){
	float *  te = self->data;
	float  x = euler.x;
	float  y = euler.y;
	float  z = euler.z;
	float  a = cos(x) ;
	float  b = sin(x) ;
	float  c = cos(y) ;
	float  d = sin(y) ;
	float  e = cos(z) ;
	float  f = sin(z) ;
	if (SuiCore$Euler$isXYZ(&euler) ) {
		float  ae = a * e;
		float  af = a * f;
		float  be = b * e;
		float  bf = b * f;
		te[0] = c * e;
		te[4] = -c * f;
		te[8] = d;
		te[1] = af + be * d;
		te[5] = ae - bf * d;
		te[9] = -b * c;
		te[2] = bf - ae * d;
		te[6] = be + af * d;
		te[10] = a * c;
	}
	else if (SuiCore$Euler$isYXZ(&euler) ) {
		float  ce = c * e;
		float  cf = c * f;
		float  de = d * e;
		float  df = d * f;
		te[0] = ce + df * b;
		te[4] = de * b - cf;
		te[8] = a * d;
		te[1] = a * f;
		te[5] = a * e;
		te[9] = -b;
		te[2] = cf * b - de;
		te[6] = df + ce * b;
		te[10] = a * c;
	}
	else if (SuiCore$Euler$isZXY(&euler) ) {
		float  ce = c * e;
		float  cf = c * f;
		float  de = d * e;
		float  df = d * f;
		te[0] = ce - df * b;
		te[4] = -a * f;
		te[8] = de + cf * b;
		te[1] = cf + de * b;
		te[5] = a * e;
		te[9] = df - ce * b;
		te[2] = -a * d;
		te[6] = b;
		te[10] = a * c;
	}
	else if (SuiCore$Euler$isZYX(&euler) ) {
		float  ae = a * e;
		float  af = a * f;
		float  be = b * e;
		float  bf = b * f;
		te[0] = c * e;
		te[4] = be * d - af;
		te[8] = ae * d + bf;
		te[1] = c * f;
		te[5] = bf * d + ae;
		te[9] = af * d - be;
		te[2] = -d;
		te[6] = b * c;
		te[10] = a * c;
	}
	else if (SuiCore$Euler$isYZX(&euler) ) {
		float  ac = a * c;
		float  ad = a * d;
		float  bc = b * c;
		float  bd = b * d;
		te[0] = c * e;
		te[4] = bd - ac * f;
		te[8] = bc * f + ad;
		te[1] = f;
		te[5] = a * e;
		te[9] = -b * e;
		te[2] = -d * e;
		te[6] = ad * f + bc;
		te[10] = ac - bd * f;
	}
	else if (SuiCore$Euler$isXZY(&euler) ) {
		float  ac = a * c;
		float  ad = a * d;
		float  bc = b * c;
		float  bd = b * d;
		te[0] = c * e;
		te[4] = -f;
		te[8] = d * e;
		te[1] = ac * f + bd;
		te[5] = a * e;
		te[9] = ad * f - bc;
		te[2] = bc * f - ad;
		te[6] = b * e;
		te[10] = bd * f + ac;
	}
	te[3] = 0;
	te[7] = 0;
	te[11] = 0;
	te[12] = 0;
	te[13] = 0;
	te[14] = 0;
	te[15] = 1;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeRotationFromQuaternion(Sgl$Mat *  self, SuiCore$Quaternion q){
	SuiCore$Vec3 _zero = SuiCore$mkVec3(0, 0, 0) ;
	SuiCore$Vec3 _one = SuiCore$mkVec3(1, 1, 1) ;
	return Sgl$Mat$compose(self, _zero, q, _one) ; 
}

Sgl$Mat *  Sgl$Mat$lookAtLocal(Sgl$Mat *  self, SuiCore$Vec3 eye, SuiCore$Vec3 target, SuiCore$Vec3 up){
	Sgl$Mat$identity(self) ;
	SuiCore$Vec3 _z;
	SuiCore$Vec3 _y;
	SuiCore$Vec3 _x;
	float *  te = self->data;
	SuiCore$Vec3$subVectorsLocal(&_z, eye, target) ;
	if (Orc$eqFloat(SuiCore$Vec3$lengthSq(&_z) , 0) ) {
		_z.z = 1;
	}
	SuiCore$Vec3$normalizeLocal(&_z) ;
	SuiCore$Vec3$crossVectorsLocal(&_x, up, _z) ;
	if (Orc$eqFloat(SuiCore$Vec3$lengthSq(&_x) , 0) ) {
		if (Orc$eqFloat(Orc$absFloat(up.z) , 1) ) {
			_z.x += 0.0001;
		}
		else {
			_z.z += 0.0001;
		}
		SuiCore$Vec3$normalizeLocal(&_z) ;
		SuiCore$Vec3$crossVectorsLocal(&_x, up, _z) ;
	}
	SuiCore$Vec3$normalizeLocal(&_x) ;
	SuiCore$Vec3$crossVectorsLocal(&_y, _z, _x) ;
	te[0] = _x.x;
	te[4] = _y.x;
	te[8] = _z.x;
	te[1] = _x.y;
	te[5] = _y.y;
	te[9] = _z.y;
	te[2] = _x.z;
	te[6] = _y.z;
	te[10] = _z.z;
	return self; 
}

Sgl$Mat *  Sgl$Mat$multiplyLocal(Sgl$Mat *  self, Sgl$Mat m){
	return Sgl$Mat$multiplyMatricesLocal(self, *self, m) ; 
}

Sgl$Mat *  Sgl$Mat$premultiplyLocal(Sgl$Mat *  self, Sgl$Mat m){
	return Sgl$Mat$multiplyMatricesLocal(self, m, *self) ; 
}

Sgl$Mat *  Sgl$Mat$multiplyMatricesLocal(Sgl$Mat *  self, Sgl$Mat a, Sgl$Mat b){
	float *  ae = a.data;
	float *  be = b.data;
	float *  te = self->data;
	float  a11 = ae[0];
	float  a12 = ae[4];
	float  a13 = ae[8];
	float  a14 = ae[12];
	float  a21 = ae[1];
	float  a22 = ae[5];
	float  a23 = ae[9];
	float  a24 = ae[13];
	float  a31 = ae[2];
	float  a32 = ae[6];
	float  a33 = ae[10];
	float  a34 = ae[14];
	float  a41 = ae[3];
	float  a42 = ae[7];
	float  a43 = ae[11];
	float  a44 = ae[15];
	float  b11 = be[0];
	float  b12 = be[4];
	float  b13 = be[8];
	float  b14 = be[12];
	float  b21 = be[1];
	float  b22 = be[5];
	float  b23 = be[9];
	float  b24 = be[13];
	float  b31 = be[2];
	float  b32 = be[6];
	float  b33 = be[10];
	float  b34 = be[14];
	float  b41 = be[3];
	float  b42 = be[7];
	float  b43 = be[11];
	float  b44 = be[15];
	te[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
	te[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
	te[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
	te[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;
	te[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
	te[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
	te[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
	te[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;
	te[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
	te[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
	te[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
	te[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;
	te[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
	te[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
	te[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
	te[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;
	return self; 
}

Sgl$Mat *  Sgl$Mat$multiplyScalarLocal(Sgl$Mat *  self, float  s){
	float *  te = self->data;
	te[0] *= s;
	te[4] *= s;
	te[8] *= s;
	te[12] *= s;
	te[1] *= s;
	te[5] *= s;
	te[9] *= s;
	te[13] *= s;
	te[2] *= s;
	te[6] *= s;
	te[10] *= s;
	te[14] *= s;
	te[3] *= s;
	te[7] *= s;
	te[11] *= s;
	te[15] *= s;
	return self; 
}

float  Sgl$Mat$determinant(Sgl$Mat *  self){
	float *  te = self->data;
	float  n11 = te[0];
	float  n12 = te[4];
	float  n13 = te[8];
	float  n14 = te[12];
	float  n21 = te[1];
	float  n22 = te[5];
	float  n23 = te[9];
	float  n24 = te[13];
	float  n31 = te[2];
	float  n32 = te[6];
	float  n33 = te[10];
	float  n34 = te[14];
	float  n41 = te[3];
	float  n42 = te[7];
	float  n43 = te[11];
	float  n44 = te[15];
	return (n41 * (+n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34) + n42 * (+n11 * n23 * n34 - n11 * n24 * n33 + n14 * n21 * n33 - n13 * n21 * n34 + n13 * n24 * n31 - n14 * n23 * n31) + n43 * (+n11 * n24 * n32 - n11 * n22 * n34 - n14 * n21 * n32 + n12 * n21 * n34 + n14 * n22 * n31 - n12 * n24 * n31) + n44 * (-n13 * n22 * n31 - n11 * n23 * n32 + n11 * n22 * n33 + n13 * n21 * n32 - n12 * n21 * n33 + n12 * n23 * n31)); 
}

Sgl$Mat *  Sgl$Mat$transposeLocal(Sgl$Mat *  self){
	float *  te = self->data;
	float  tmp;
	tmp = te[1];
	te[1] = te[4];
	te[4] = tmp;
	tmp = te[2];
	te[2] = te[8];
	te[8] = tmp;
	tmp = te[6];
	te[6] = te[9];
	te[9] = tmp;
	tmp = te[3];
	te[3] = te[12];
	te[12] = tmp;
	tmp = te[7];
	te[7] = te[13];
	te[13] = tmp;
	tmp = te[11];
	te[11] = te[14];
	te[14] = tmp;
	return self; 
}

Sgl$Mat *  Sgl$Mat$setPosition(Sgl$Mat *  self, float  x, float  y, float  z){
	float *  te = self->data;
	te[12] = x;
	te[13] = y;
	te[14] = z;
	return self; 
}

Sgl$Mat *  Sgl$Mat$invertLocal(Sgl$Mat *  self){
	float *  te = self->data;
	float  n11 = te[0];
	float  n21 = te[1];
	float  n31 = te[2];
	float  n41 = te[3];
	float  n12 = te[4];
	float  n22 = te[5];
	float  n32 = te[6];
	float  n42 = te[7];
	float  n13 = te[8];
	float  n23 = te[9];
	float  n33 = te[10];
	float  n43 = te[11];
	float  n14 = te[12];
	float  n24 = te[13];
	float  n34 = te[14];
	float  n44 = te[15];
	float  t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
	float  t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
	float  t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
	float  t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;
	float  det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;
	if (det == 0) {
		return Sgl$Mat$set(self, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) ; 
	}
	float  detInv = 1 / det;
	te[0] = t11 * detInv;
	te[1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * detInv;
	te[2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * detInv;
	te[3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * detInv;
	te[4] = t12 * detInv;
	te[5] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * detInv;
	te[6] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * detInv;
	te[7] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * detInv;
	te[8] = t13 * detInv;
	te[9] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * detInv;
	te[10] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * detInv;
	te[11] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * detInv;
	te[12] = t14 * detInv;
	te[13] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * detInv;
	te[14] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * detInv;
	te[15] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * detInv;
	return self; 
}

Sgl$Mat *  Sgl$Mat$scaleVec3(Sgl$Mat *  self, SuiCore$Vec3 v){
	float *  te = self->data;
	float  x = v.x;
	float  y = v.y;
	float  z = v.z;
	te[0] *= x;
	te[4] *= y;
	te[8] *= z;
	te[1] *= x;
	te[5] *= y;
	te[9] *= z;
	te[2] *= x;
	te[6] *= y;
	te[10] *= z;
	te[3] *= x;
	te[7] *= y;
	te[11] *= z;
	return self; 
}

float  Sgl$Mat$getMaxScaleOnAxis(Sgl$Mat *  self){
	float *  te = self->data;
	float  scaleXSq = te[0] * te[0] + te[1] * te[1] + te[2] * te[2];
	float  scaleYSq = te[4] * te[4] + te[5] * te[5] + te[6] * te[6];
	float  scaleZSq = te[8] * te[8] + te[9] * te[9] + te[10] * te[10];
	return sqrt(Orc$maxFloat3(scaleXSq, scaleYSq, scaleZSq) ) ; 
}

Sgl$Mat *  Sgl$Mat$makeTranslation(Sgl$Mat *  self, float  x, float  y, float  z){
	Sgl$Mat$set(self, 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeRotationX(Sgl$Mat *  self, float  theta){
	float  c = cos(theta) ;
	float  s = sin(theta) ;
	Sgl$Mat$set(self, 1, 0, 0, 0, 0, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeRotationY(Sgl$Mat *  self, float  theta){
	float  c = cos(theta) ;
	float  s = sin(theta) ;
	Sgl$Mat$set(self, c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeRotationZ(Sgl$Mat *  self, float  theta){
	float  c = cos(theta) ;
	float  s = sin(theta) ;
	Sgl$Mat$set(self, c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeRotationAxis(Sgl$Mat *  self, SuiCore$Vec3 axis, float  angle){
	float  c = cos(angle) ;
	float  s = sin(angle) ;
	float  t = 1 - c;
	float  x = axis.x;
	float  y = axis.y;
	float  z = axis.z;
	float  tx = t * x;
	float  ty = t * y;
	Sgl$Mat$set(self, tx * x + c, tx * y - s * z, tx * z + s * y, 0, tx * y + s * z, ty * y + c, ty * z - s * x, 0, tx * z - s * y, ty * z + s * x, t * z * z + c, 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeScale(Sgl$Mat *  self, float  x, float  y, float  z){
	Sgl$Mat$set(self, x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeShear(Sgl$Mat *  self, float  xy, float  xz, float  yx, float  yz, float  zx, float  zy){
	Sgl$Mat$set(self, 1, yx, zx, 0, xy, 1, zy, 0, xz, yz, 1, 0, 0, 0, 0, 1) ;
	return self; 
}

Sgl$Mat *  Sgl$Mat$compose(Sgl$Mat *  self, SuiCore$Vec3 position, SuiCore$Quaternion quaternion, SuiCore$Vec3 scale){
	float *  te = self->data;
	float  x = quaternion.x;
	float  y = quaternion.y;
	float  z = quaternion.z;
	float  w = quaternion.w;
	float  x2 = x + x;
	float  y2 = y + y;
	float  z2 = z + z;
	float  xx = x * x2;
	float  xy = x * y2;
	float  xz = x * z2;
	float  yy = y * y2;
	float  yz = y * z2;
	float  zz = z * z2;
	float  wx = w * x2;
	float  wy = w * y2;
	float  wz = w * z2;
	float  sx = scale.x;
	float  sy = scale.y;
	float  sz = scale.z;
	te[0] = (1 - (yy + zz)) * sx;
	te[1] = (xy + wz) * sx;
	te[2] = (xz - wy) * sx;
	te[3] = 0;
	te[4] = (xy - wz) * sy;
	te[5] = (1 - (xx + zz)) * sy;
	te[6] = (yz + wx) * sy;
	te[7] = 0;
	te[8] = (xz + wy) * sz;
	te[9] = (yz - wx) * sz;
	te[10] = (1 - (xx + yy)) * sz;
	te[11] = 0;
	te[12] = position.x;
	te[13] = position.y;
	te[14] = position.z;
	te[15] = 1;
	return self; 
}

Sgl$Mat *  Sgl$Mat$decompose(Sgl$Mat *  self, SuiCore$Vec3 *  position, SuiCore$Quaternion *  quaternion, SuiCore$Vec3 *  scale){
	float *  te = self->data;
	SuiCore$Vec3 _v1;
	Sgl$Mat _m1;
	float  sx = SuiCore$Vec3$length(SuiCore$Vec3$set(&_v1, te[0], te[1], te[2]) ) ;
	float  sy = SuiCore$Vec3$length(SuiCore$Vec3$set(&_v1, te[4], te[5], te[6]) ) ;
	float  sz = SuiCore$Vec3$length(SuiCore$Vec3$set(&_v1, te[8], te[9], te[10]) ) ;
	float  det = Sgl$Mat$determinant(self) ;
	if (det < 0) {
		sx = -sx;
	}
	position->x = te[12];
	position->y = te[13];
	position->z = te[14];
	Sgl$Mat$copy(&_m1, *self) ;
	float  invSX = 1 / sx;
	float  invSY = 1 / sy;
	float  invSZ = 1 / sz;
	_m1.data[0] *= invSX;
	_m1.data[1] *= invSX;
	_m1.data[2] *= invSX;
	_m1.data[4] *= invSY;
	_m1.data[5] *= invSY;
	_m1.data[6] *= invSY;
	_m1.data[8] *= invSZ;
	_m1.data[9] *= invSZ;
	_m1.data[10] *= invSZ;
	SuiCore$Quaternion$setFromRotationMatrix(quaternion, _m1) ;
	scale->x = sx;
	scale->y = sy;
	scale->z = sz;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makePerspective(Sgl$Mat *  self, float  left, float  right, float  top, float  bottom, float  near, float  far){
	float *  te = self->data;
	float  x = 2 * near / (right - left);
	float  y = 2 * near / (top - bottom);
	float  a = (right + left) / (right - left);
	float  b = (top + bottom) / (top - bottom);
	float  c = -(far + near) / (far - near);
	float  d = -2 * far * near / (far - near);
	te[0] = x;
	te[4] = 0;
	te[8] = a;
	te[12] = 0;
	te[1] = 0;
	te[5] = y;
	te[9] = b;
	te[13] = 0;
	te[2] = 0;
	te[6] = 0;
	te[10] = c;
	te[14] = d;
	te[3] = 0;
	te[7] = 0;
	te[11] = -1;
	te[15] = 0;
	return self; 
}

Sgl$Mat *  Sgl$Mat$makeOrthographic(Sgl$Mat *  self, float  left, float  right, float  top, float  bottom, float  near, float  far){
	float *  te = self->data;
	float  w = 1.0 / (right - left);
	float  h = 1.0 / (top - bottom);
	float  p = 1.0 / (far - near);
	float  x = (right + left) * w;
	float  y = (top + bottom) * h;
	float  z = (far + near) * p;
	te[0] = 2 * w;
	te[4] = 0;
	te[8] = 0;
	te[12] = -x;
	te[1] = 0;
	te[5] = 2 * h;
	te[9] = 0;
	te[13] = -y;
	te[2] = 0;
	te[6] = 0;
	te[10] = -2 * p;
	te[14] = -z;
	te[3] = 0;
	te[7] = 0;
	te[11] = 0;
	te[15] = 1;
	return self; 
}

bool  Sgl$Mat$equals(Sgl$Mat *  self, Sgl$Mat matrix){
	float *  te = self->data;
	float *  me = matrix.data;
	for (int  i = 0; i < 16; i++) {
		if (!Orc$eqFloat(te[i], me[i]) ) {
			return false; 
		}
	}
	return true; 
}

Sgl$Mat *  Sgl$Mat$fromArray(Sgl$Mat *  self, float *  array, int  offset){
	for (int  i = 0; i < 16; i++) {
		self->data[i] = array[i + offset];
	}
	return self; 
}

float *  Sgl$Mat$toArray(Sgl$Mat *  self, float *  array, int  offset){
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
	array[offset + 9] = te[9];
	array[offset + 10] = te[10];
	array[offset + 11] = te[11];
	array[offset + 12] = te[12];
	array[offset + 13] = te[13];
	array[offset + 14] = te[14];
	array[offset + 15] = te[15];
	return array; 
}

SuiCore$Vec3 Sgl$Mat$rotationMatrixToEulerXYZ(Sgl$Mat *  self){
	float *  te = self->data;
	float  m11 = te[0];
	float  m12 = te[4];
	float  m13 = te[8];
	float  m21 = te[1];
	float  m22 = te[5];
	float  m23 = te[9];
	float  m31 = te[2];
	float  m32 = te[6];
	float  m33 = te[10];
	SuiCore$Vec3 r;
	r.y = asin(Orc$clampFloat(m13, -1, 1) ) ;
	if (Orc$absFloat(m13)  < 0.9999999) {
		r.x = atan2(-m23, m33) ;
		r.z = atan2(-m12, m11) ;
	}
	else {
		r.x = atan2(m32, m22) ;
		r.z = 0;
	}
	return r; 
}

void  Sgl$Mat$identity(Sgl$Mat *  self){
	mat4x4_identity((void * )self->data) ;
}

void  Sgl$Mat$rotateX(Sgl$Mat *  self, float  angle){
	mat4x4 bk;
	mat4x4_dup((void * )bk, (void * )self->data) ;
	mat4x4_rotate_X((void * )self->data, (void * )bk, angle) ;
}

void  Sgl$Mat$rotateY(Sgl$Mat *  self, float  angle){
	mat4x4 bk;
	mat4x4_dup((void * )bk, (void * )self->data) ;
	mat4x4_rotate_Y((void * )self->data, (void * )bk, angle) ;
}

void  Sgl$Mat$rotateZ(Sgl$Mat *  self, float  angle){
	mat4x4 bk;
	mat4x4_dup((void * )bk, (void * )self->data) ;
	mat4x4_rotate_Z((void * )self->data, (void * )bk, angle) ;
}

void  Sgl$Mat$rotate(Sgl$Mat *  self, float  x, float  y, float  z, float  angle){
	mat4x4 bk;
	mat4x4_dup((void * )bk, (void * )self->data) ;
	mat4x4_rotate((void * )self->data, (void * )bk, x, y, z, angle) ;
}

void  Sgl$Mat$scale(Sgl$Mat *  self, float  x, float  y, float  z){
	mat4x4 bk;
	mat4x4_dup((void * )bk, (void * )self->data) ;
	mat4x4_scale_aniso((void * )self->data, (void * )bk, x, y, z) ;
}

void  Sgl$Mat$setTranslate(Sgl$Mat *  self, float  x, float  y, float  z){
	mat4x4_translate_in_place((void * )self->data, x, y, z) ;
}

void  Sgl$Mat$translate(Sgl$Mat *  self, float  x, float  y, float  z){
	mat4x4 bk;
	mat4x4_dup((void * )bk, (void * )self->data) ;
	mat4x4 trM;
	mat4x4_translate((void * )trM, x, y, z) ;
	mat4x4_mul((void * )self->data, (void * )bk, (void * )trM) ;
}

Sgl$Mat Sgl$Mat$invert(Sgl$Mat *  self){
	Sgl$Mat c = *self;
	Sgl$Mat$invertLocal(&c) ;
	return c; 
}

void  Sgl$Mat$invertSelf(Sgl$Mat *  self){
	mat4x4 bk;
	mat4x4_dup((void * )bk, (void * )self->data) ;
	mat4x4_invert((void * )self->data, (void * )bk) ;
}

void  Sgl$Mat$frustum(Sgl$Mat *  self, float  left, float  right, float  bottom, float  top, float  near, float  far){
	mat4x4_frustum((void * )self->data, left, right, bottom, top, near, far) ;
}

void  Sgl$Mat$ortho(Sgl$Mat *  self, float  left, float  right, float  bottom, float  top, float  near, float  far){
	mat4x4_ortho((void * )self->data, left, right, bottom, top, near, far) ;
}

void  Sgl$Mat$perspective(Sgl$Mat *  self, float  y_fov, float  aspect, float  near, float  far){
	mat4x4_perspective((void * )self->data, y_fov, aspect, near, far) ;
}

void  Sgl$Mat$mul(Sgl$Mat *  self, Sgl$Mat *  a, Sgl$Mat *  b){
	mat4x4_mul((void * )self->data, (void * )a->data, (void * )b->data) ;
}

void  Sgl$Mat$lookAtFake(Sgl$Mat *  self, SuiCore$Vec3 eye, SuiCore$Vec3 center, SuiCore$Vec3 up){
	vec3 e;
	e[0] = eye.x;
	e[1] = eye.y;
	e[2] = eye.z;
	vec3 c;
	c[0] = center.x;
	c[1] = center.y;
	c[2] = center.z;
	vec3 u;
	u[0] = up.x;
	u[1] = up.y;
	u[2] = up.z;
	mat4x4_look_at((void * )self->data, e, c, u) ;
}

SuiCore$Vec3 Sgl$Mat$mulVec3(Sgl$Mat *  self, SuiCore$Vec3 v){
	SuiCore$Vec4 v4;
	v4.x = v.x;
	v4.y = v.y;
	v4.z = v.z;
	v4.w = 1;
	SuiCore$Vec4 ret4 = Sgl$Mat$mulVec4(self, v4) ;
	SuiCore$Vec3 ret;
	ret.x = ret4.x / ret4.w;
	ret.y = ret4.y / ret4.w;
	ret.z = ret4.z / ret4.w;
	return ret; 
}

SuiCore$Vec4 Sgl$Mat$mulVec4(Sgl$Mat *  self, SuiCore$Vec4 v){
	vec4 v2;
	v2[0] = v.x;
	v2[1] = v.y;
	v2[2] = v.z;
	v2[3] = v.w;
	vec4 result;
	mat4x4_mul_vec4(result, (void * )self->data, v2) ;
	SuiCore$Vec4 ret;
	ret.x = result[0];
	ret.y = result[1];
	ret.z = result[2];
	ret.w = result[3];
	return ret; 
}



