
package SuiCore

#include <math.h>
#include "./linmath.h"
#include <stdio.h>
#include <stdlib.h>

import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"
import * from "./Vec3.orc"
import * from "../../Sgl/Mat.orc"



/// 布局上下文
struct Quat {
	float x 
	float y 
	float z 
	float w
}
extension Quat {
	Vec3 toEulerXYZ(){
		Mat m = self.toRotationMat()
		Vec3 r = m.rotationMatrixToEulerXYZ()
		return r
	}
	//转为旋转矩阵
	Mat toRotationMat(){
		Mat m;
		mat4x4_from_quat(m.data, self)
		return m
	}
	String@ toString(){
		char tmp[256]
		sprintf(tmp, "Quat(%f,%f,%f,%f)", self.x, self.y, self.z, self.w)
		return str(tmp)
	}
	void identity(){
		quat_identity((float*)self);
	}
	Quat mul(Quat q){
		Quat r;
		quat_mul((float*)&r, (float*)self, (float*)&q);
		return r;
	}
	Quat conj(){
		Quat r;
		quat_conj((float*)&r, (float*)self);
		return r;
	}
	void setRotate(float angle, Vec3 axis){
		quat_rotate((float*)self, angle, (float*)&axis);
	}
	Vec3 mulVec3(Vec3 v){
		Vec3 r;
		quat_mul_vec3((float*)&r, (float*)self, (float*)&v);
		return r;
	}
	Quat lerp(Quat b, float ratio){
		Quat r;
		r.x = lerpFloat(self.x, b.x, ratio)
		r.y = lerpFloat(self.y, b.y, ratio)
		r.z = lerpFloat(self.z, b.z, ratio)
		r.w = lerpFloat(self.w, b.w, ratio)

		return r
	}
	Quat clone(){
		Quat r;
		r.x = self.x
		r.y = self.y
		r.z = self.z
		r.w = self.w
		return r
	}
	float length() {

		return sqrt( self.x * self.x + self.y * self.y + self.z * self.z + self.w * self.w );

	}
	void normalizeSelf() {
		float l = self.length();

		if ( l == 0 ) {

			self.x = 0;
			self.y = 0;
			self.z = 0;
			self.w = 1;

		} else {

			l = 1 / l;

			self.x = self.x * l;
			self.y = self.y * l;
			self.z = self.z * l;
			self.w = self.w * l;
		}
	}
	Quat slerp(Quat qb, float t){
		Quat r = self.clone();

		if ( t == 0 ) {return r;}
		if ( t == 1 ) {return qb.clone();}

		float x = r.x
		float y = r.y
		float z = r.z
		float w = r.w;

		// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/

		float cosHalfTheta = w * qb.w + x * qb.x + y * qb.y + z * qb.z;

		if ( cosHalfTheta < 0 ) {

			r.w = - qb.w;
			r.x = - qb.x;
			r.y = - qb.y;
			r.z = - qb.z;

			cosHalfTheta = - cosHalfTheta;

		} else {

			r = qb;

		}

		if ( cosHalfTheta >= 1.0 ) {

			r.w = w;
			r.x = x;
			r.y = y;
			r.z = z;

			return r;
		}

		float sqrSinHalfTheta = 1.0 - cosHalfTheta * cosHalfTheta;

		if ( sqrSinHalfTheta <= EPSILON ) {

			float s = 1 - t;
			r.w = s * w + t * r.w;
			r.x = s * x + t * r.x;
			r.y = s * y + t * r.y;
			r.z = s * z + t * r.z;

			r.normalizeSelf();

			return r;

		}

		float sinHalfTheta = sqrt( sqrSinHalfTheta );
		float halfTheta = atan2( sinHalfTheta, cosHalfTheta );
		float ratioA = sin( ( 1 - t ) * halfTheta ) / sinHalfTheta;
		float ratioB = sin( t * halfTheta ) / sinHalfTheta;

		r.w = ( w * ratioA + r.w * ratioB );
		r.x = ( x * ratioA + r.x * ratioB );
		r.y = ( y * ratioA + r.y * ratioB );
		r.z = ( z * ratioA + r.z * ratioB );

		return r;
	}
}