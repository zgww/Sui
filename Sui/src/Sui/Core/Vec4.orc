package SuiCore

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"
import * from "./Mat3.orc"
import * from "./Euler.orc"
import * from "./Color.orc"
import * from "./Spherical.orc"


/// 布局上下文
struct Vec4 {
	float x 
	float y 
	float z 
	float w
}
extension Vec4 {
	float width(){
		return self.x
	}
	float height(){
		return self.y
	}

	Vec4* set( float x, float y, float z, float w ) {

		self.x = x;
		self.y = y;
		self.z = z;
		self.w = w;

		return self;

	}

	Vec4* setScalar(float scalar ) {

		self.x = scalar;
		self.y = scalar;
		self.z = scalar;
		self.w = scalar;

		return self;

	}

	Vec4* setX( float x ) {

		self.x = x;

		return self;

	}

	Vec4* setY( float y ) {

		self.y = y;

		return self;

	}

	Vec4* setZ( float z ) {

		self.z = z;

		return self;

	}

	Vec4* setW( float w ) {

		self.w = w;

		return self;

	}

	Vec4* setComponent( int index, float value ) {


			if index == 0 { self.x = value; }
			if index == 1 { self.y = value; }
			if index == 2 { self.z = value; }
			if index == 3 { self.w = value; }

		return self;

	}

	float getComponent(int index ) {

			if index == 0{ return self.x;}
			if index == 1{ return self.y;}
			if index == 2{ return self.z;}
			if index == 3{ return self.w;}
			return 0.0
	}

	Vec4 clone() {
		return *self
	}

	Vec4* copy(Vec4 v ) {

		self.x = v.x;
		self.y = v.y;
		self.z = v.z;
		self.w = v.w; 

		return self;

	}

	Vec4* addLocal(Vec4 v ) {

		self.x += v.x;
		self.y += v.y;
		self.z += v.z;
		self.w += v.w;

		return self;

	}

	Vec4* addScalarLocal(float s ) {

		self.x += s;
		self.y += s;
		self.z += s;
		self.w += s;

		return self;

	}

	Vec4* addVectorsLocal(Vec4 a, Vec4 b ) {

		self.x = a.x + b.x;
		self.y = a.y + b.y;
		self.z = a.z + b.z;
		self.w = a.w + b.w;

		return self;

	}

	Vec4* addScaledVectorLocal(Vec4 v, float s ) {

		self.x += v.x * s;
		self.y += v.y * s;
		self.z += v.z * s;
		self.w += v.w * s;

		return self;

	}

	Vec4* subLocal(Vec4 v ) {

		self.x -= v.x;
		self.y -= v.y;
		self.z -= v.z;
		self.w -= v.w;

		return self;

	}

	Vec4* subScalarLocal(float s ) {

		self.x -= s;
		self.y -= s;
		self.z -= s;
		self.w -= s;

		return self;

	}

	Vec4* subVectorsLocal(Vec4 a, Vec4 b ) {

		self.x = a.x - b.x;
		self.y = a.y - b.y;
		self.z = a.z - b.z;
		self.w = a.w - b.w;

		return self;

	}

	Vec4* multiplyLocal(Vec4 v ) {

		self.x *= v.x;
		self.y *= v.y;
		self.z *= v.z;
		self.w *= v.w;

		return self;

	}

	Vec4* multiplyScalarLocal(float scalar ) {

		self.x *= scalar;
		self.y *= scalar;
		self.z *= scalar;
		self.w *= scalar;

		return self;

	}

	Vec4* applyMatrix4Local(Mat m ) {

		float x = self.x
		float y = self.y
		float z = self.z
		float w = self.w;
		float* e = m.data;

		self.x = e[ 0 ] * x + e[ 4 ] * y + e[ 8 ] * z + e[ 12 ] * w;
		self.y = e[ 1 ] * x + e[ 5 ] * y + e[ 9 ] * z + e[ 13 ] * w;
		self.z = e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z + e[ 14 ] * w;
		self.w = e[ 3 ] * x + e[ 7 ] * y + e[ 11 ] * z + e[ 15 ] * w;

		return self;

	}

	Vec4* divideScalarLocal(float scalar ) {
		if scalar != 0 {
			return self.multiplyScalarLocal( 1 / scalar );
		}
		return self
	}

	// Vec4* setAxisAngleFromQuaternion( q ) {

	// 	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm

	// 	// q is assumed to be normalized

	// 	self.w = 2 * acos( q.w );

	// 	const s = sqrt( 1 - q.w * q.w );

	// 	if ( s < 0.0001 ) {

	// 		self.x = 1;
	// 		self.y = 0;
	// 		self.z = 0;

	// 	} else {

	// 		self.x = q.x / s;
	// 		self.y = q.y / s;
	// 		self.z = q.z / s;

	// 	}

	// 	return self;

	// }

	Vec4* setAxisAngleFromRotationMatrixLocal(Mat m ) {

		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm

		// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

		float angle
		float x
		float y
		float z; // variables for result
		float epsilon = 0.01		// margin to allow for rounding errors
		float epsilon2 = 0.1		// margin to distinguish between 0 and 180 degrees

		float *te = m.data

		float m11 = te[ 0 ]; float m12 = te[ 4 ]; float m13 = te[ 8 ];
		float m21 = te[ 1 ]; float m22 = te[ 5 ]; float m23 = te[ 9 ];
		float m31 = te[ 2 ]; float m32 = te[ 6 ]; float m33 = te[ 10 ];

		if ( ( absFloat( m12 - m21 ) < epsilon ) &&
		     ( absFloat( m13 - m31 ) < epsilon ) &&
		     ( absFloat( m23 - m32 ) < epsilon ) ) {

			// singularity found
			// first check for identity matrix which must have +1 for all terms
			// in leading diagonal and zero in other terms

			if ( ( absFloat( m12 + m21 ) < epsilon2 ) &&
			     ( absFloat( m13 + m31 ) < epsilon2 ) &&
			     ( absFloat( m23 + m32 ) < epsilon2 ) &&
			     ( absFloat( m11 + m22 + m33 - 3 ) < epsilon2 ) ) {

				// self singularity is identity matrix so angle = 0

				self.set( 1, 0, 0, 0 );

				return self; // zero angle, arbitrary axis

			}

			// otherwise self singularity is angle = 180

			angle = PI;

			float xx = ( m11 + 1 ) / 2.0;
			float yy = ( m22 + 1 ) / 2.0;
			float zz = ( m33 + 1 ) / 2.0;
			float xy = ( m12 + m21 ) / 4.0;
			float xz = ( m13 + m31 ) / 4.0;
			float yz = ( m23 + m32 ) / 4.0;

			if ( ( xx > yy ) && ( xx > zz ) ) {

				// m11 is the largest diagonal term

				if ( xx < epsilon ) {

					x = 0;
					y = 0.707106781;
					z = 0.707106781;

				} else {

					x = sqrt( xx );
					y = xy / x;
					z = xz / x;

				}

			} else if ( yy > zz ) {

				// m22 is the largest diagonal term

				if ( yy < epsilon ) {

					x = 0.707106781;
					y = 0;
					z = 0.707106781;

				} else {

					y = sqrt( yy );
					x = xy / y;
					z = yz / y;

				}

			} else {

				// m33 is the largest diagonal term so base result on self

				if ( zz < epsilon ) {

					x = 0.707106781;
					y = 0.707106781;
					z = 0;

				} else {

					z = sqrt( zz );
					x = xz / z;
					y = yz / z;

				}

			}

			self.set( x, y, z, angle );

			return self; // return 180 deg rotation

		}

		// as we have reached here there are no singularities so we can handle normally

		float s = sqrt( ( m32 - m23 ) * ( m32 - m23 ) +
			( m13 - m31 ) * ( m13 - m31 ) +
			( m21 - m12 ) * ( m21 - m12 ) ); // used to normalize

		if ( absFloat( s ) < 0.001 ) {s = 1};

		// prevent divide by zero, should not happen if matrix is orthogonal and should be
		// caught by singularity test above, but I've left it in just in case

		self.x = ( m32 - m23 ) / s;
		self.y = ( m13 - m31 ) / s;
		self.z = ( m21 - m12 ) / s;
		self.w = acos( ( m11 + m22 + m33 - 1 ) / 2 );

		return self;

	}

	Vec4* minLocal(Vec4 v ) {

		self.x = minFloat( self.x, v.x );
		self.y = minFloat( self.y, v.y );
		self.z = minFloat( self.z, v.z );
		self.w = minFloat( self.w, v.w );

		return self;

	}

	Vec4* maxLocal(Vec4 v ) {

		self.x = maxFloat( self.x, v.x );
		self.y = maxFloat( self.y, v.y );
		self.z = maxFloat( self.z, v.z );
		self.w = maxFloat( self.w, v.w );

		return self;

	}

	Vec4* clampLocal(Vec4 min, Vec4 max ) {

		// assumes min < max, componentwise

		self.x = maxFloat( min.x, minFloat( max.x, self.x ) );
		self.y = maxFloat( min.y, minFloat( max.y, self.y ) );
		self.z = maxFloat( min.z, minFloat( max.z, self.z ) );
		self.w = maxFloat( min.w, minFloat( max.w, self.w ) );

		return self;

	}

	Vec4* clampScalarLocal(float minVal, float maxVal ) {

		self.x = maxFloat( minVal, minFloat( maxVal, self.x ) );
		self.y = maxFloat( minVal, minFloat( maxVal, self.y ) );
		self.z = maxFloat( minVal, minFloat( maxVal, self.z ) );
		self.w = maxFloat( minVal, minFloat( maxVal, self.w ) );

		return self;

	}

	Vec4* clampLengthLocal(float min, float max ) {

		float length = self.length();

		return self.divideScalarLocal( length == 0 ? 1 : length ).multiplyScalarLocal( maxFloat( min, minFloat( max, length ) ) );
	}

	Vec4* floorLocal() {

		self.x = floor( self.x );
		self.y = floor( self.y );
		self.z = floor( self.z );
		self.w = floor( self.w );

		return self;

	}

	Vec4* ceilLocal() {

		self.x = ceil( self.x );
		self.y = ceil( self.y );
		self.z = ceil( self.z );
		self.w = ceil( self.w );

		return self;

	}

	Vec4* roundLocal() {

		self.x = round( self.x );
		self.y = round( self.y );
		self.z = round( self.z );
		self.w = round( self.w );

		return self;

	}

	Vec4* roundToZeroLocal() {

		self.x = ( self.x < 0 ) ? ceil( self.x ) : floor( self.x );
		self.y = ( self.y < 0 ) ? ceil( self.y ) : floor( self.y );
		self.z = ( self.z < 0 ) ? ceil( self.z ) : floor( self.z );
		self.w = ( self.w < 0 ) ? ceil( self.w ) : floor( self.w );

		return self;

	}

	Vec4* negateLocal() {

		self.x = - self.x;
		self.y = - self.y;
		self.z = - self.z;
		self.w = - self.w;

		return self;

	}

	float dot(Vec4 v ) {

		return self.x * v.x + self.y * v.y + self.z * v.z + self.w * v.w;

	}

	float lengthSq() {

		return self.x * self.x + self.y * self.y + self.z * self.z + self.w * self.w;

	}

	float length() {

		return sqrt( self.x * self.x + self.y * self.y + self.z * self.z + self.w * self.w );

	}

	float manhattanLength() {

		return absFloat( self.x ) + absFloat( self.y ) + absFloat( self.z ) + absFloat( self.w );

	}

	//缩放
	Vec4 normal(float f){
		Vec4 ret = mkVec4(0,0, 0, 0)
		ret.x = self.x * f
		ret.y = self.y * f
		ret.z = self.z * f
		ret.w = self.w * f
		return ret
	}
	Vec4* normalizeLocal() {

		float length = self.length()
		return self.divideScalarLocal( eqFloat(length , 0) ? 1: length );

	}

	Vec4* setLengthLocal( float length ) {

		return self.normalizeLocal().multiplyScalarLocal( length );

	}

	Vec4* lerpLocal(Vec4 v, float alpha ) {

		self.x += ( v.x - self.x ) * alpha;
		self.y += ( v.y - self.y ) * alpha;
		self.z += ( v.z - self.z ) * alpha;
		self.w += ( v.w - self.w ) * alpha;

		return self;

	}

	Vec4* lerpVectors(Vec4 v1, Vec4 v2, float alpha ) {

		self.x = v1.x + ( v2.x - v1.x ) * alpha;
		self.y = v1.y + ( v2.y - v1.y ) * alpha;
		self.z = v1.z + ( v2.z - v1.z ) * alpha;
		self.w = v1.w + ( v2.w - v1.w ) * alpha;

		return self;

	}


	Vec4* fromArray(float * array, int offset  ) {

		self.x = array[ offset ];
		self.y = array[ offset + 1 ];
		self.z = array[ offset + 2 ];
		self.w = array[ offset + 3 ];

		return self;
	}

	float* toArray( float *array , int offset  ) {

		array[ offset ] = self.x;
		array[ offset + 1 ] = self.y;
		array[ offset + 2 ] = self.z;
		array[ offset + 3 ] = self.w;

		return array;
	}

	// fromBufferAttribute( attribute, index ) {

	// 	self.x = attribute.getX( index );
	// 	self.y = attribute.getY( index );
	// 	self.z = attribute.getZ( index );
	// 	self.w = attribute.getW( index );

	// 	return self;

	// }

	Vec4* randomLocal() {

		self.x = random();
		self.y = random();
		self.z = random();
		self.w = random();

		return self;

	}



	//缩放
	Vec4 add4f(float x, float y, float z, float w){
		Vec4 ret = mkVec4(
			self.x + x,
			self.y + y,
			self.z + z,
			self.w + w,
		)
		return ret
	}
	Vec4 add(Vec4 b){
		Vec4 ret = mkVec4(0,0, 0, 0)
		ret.x = self.x + b.x;
		ret.y = self.y + b.y;
		ret.z = self.z + b.z;
		ret.w = self.w + b.w;
		return ret
	}
	//缩放
	Vec4 sub(Vec4 b){
		Vec4 ret = mkVec4(0,0, 0, 0)
		ret.x = self.x - b.x;
		ret.y = self.y - b.y;
		ret.z = self.z - b.z;
		ret.w = self.w - b.w;
		return ret
	}

	//距离 的平方
	float distanceToSquared(Vec4 b){
		float dx = b.x - self.x
		float dy = b.y - self.y 
		float dz = b.z - self.z
		float dw = b.w - self.w
       
		return dx * dx + dy * dy + dz * dz + dw * dw
	}
		//缩放
	float distanceTo(Vec4 b){
		float ret = sqrt(self.distanceToSquared(b));
		return ret
	}



	// 	//与正x轴的夹角
	// float radToXAxis() {
	// 	return atan2(self.y, self.x);
	// } 
	
	// bool hasNan() { 
	// 	return isnan(self.x) || isnan(self.y); 
	// }
	bool equals(Vec4 b){
		return fabsf(self.x - b.x) < 0.00001 
		&&  fabsf(self.y - b.y) < 0.00001
		&&  fabsf(self.z - b.z) < 0.00001
		&&  fabsf(self.w - b.w) < 0.00001
	}
}

Vec4 mkVec4(float x, float y, float z, float w){
	Vec4 v 
	v.x = x;
	v.y = y
	v.z = z
	v.w = w
	return v;
}


void testVec4(){
	Vec4 v = mkVec4(0,0, 0, 0)
	v.x = 10;
	v.y = 10
	Vec4 b = mkVec4(0,0, 0, 0)
	b.x = 17;
	b.y = 17
	float dis = v.distanceTo(b);	
	printf("dis:%f\n", dis);
	
	float sqrDis = v.distanceToSquared(b)
	printf("sqrdis :%f\n", sqrDis);
 
	printf("equals: %d\n", b.equals(v))
	b.set(10, 10.00001, 0, 0); 
	printf("equals:%d\n", b.equals(v))

	printf("vec3 width:%f, height:%f %f %f\n", 
	v.width(), v.height()
	, b.width(), b.height()
	
	)
}