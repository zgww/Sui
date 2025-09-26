package SuiCore

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"

import * from "./Mat3.orc"
import type * from "./Euler.orc"
import type * from "./Color.orc"
import type * from "./Spherical.orc"



/// 布局上下文
struct Vec3 {
	float x 
	float y 
	float z 
}
extension Vec3 {
	String@ toString(){
		char b[128];
		sprintf(b, "Vec3(%f,%f,%f)", self.x, self.y, self.z)
		return str(b)
	}
	float width(){
		return self.x
	}
	float height(){
		return self.y
	}




	Vec3* set(float x, float y, float z ) {
		// if ( z == undefined ) z = self.z; // sprite.scale.set(x,y)

		self.x = x;
		self.y = y;
		self.z = z;

		return self;

	}

	Vec3* setScalar(float scalar ) {

		self.x = scalar;
		self.y = scalar;
		self.z = scalar;

		return self;

	}

	Vec3* setX( float x ) {

		self.x = x;

		return self;

	}

	Vec3* setY( float y ) {

		self.y = y;

		return self;

	}

	Vec3* setZ( float z ) {

		self.z = z;

		return self;

	}

	Vec3* setComponent(int  index, float value ) {


			if index == 0 { self.x = value; }
			if index == 1 { self.y = value; }
			if index == 2 { self.z = value; }

		return self;

	}

	float getComponent(int  index ) {
			if index == 0 { return self.x  }
			if index == 1 { return self.y  }
			if index == 2 { return self.z  }
			return 0.0
	}

	Vec3 clone() {
		return *self
	}

	Vec3* copy(Vec3 v ) {

		self.x = v.x;
		self.y = v.y;
		self.z = v.z;

		return self;

	}

	Vec3* addLocal(Vec3 v ) {

		self.x += v.x;
		self.y += v.y;
		self.z += v.z;

		return self;

	}

	Vec3* addScalarLocal(float s ) {

		self.x += s;
		self.y += s;
		self.z += s;

		return self;

	}

	Vec3* addVectorsLocal(Vec3 a, Vec3 b ) {

		self.x = a.x + b.x;
		self.y = a.y + b.y;
		self.z = a.z + b.z;

		return self;

	}

	Vec3* addScaledVectorLocal( Vec3 v, float s ) {

		self.x += v.x * s;
		self.y += v.y * s;
		self.z += v.z * s;

		return self;

	}

	Vec3* subLocal(Vec3 v ) {

		self.x -= v.x;
		self.y -= v.y;
		self.z -= v.z;

		return self;

	}

	Vec3* subScalarLocal(float s ) {

		self.x -= s;
		self.y -= s;
		self.z -= s;

		return self;

	}

	Vec3* subVectorsLocal(Vec3 a, Vec3 b ) {

		self.x = a.x - b.x;
		self.y = a.y - b.y;
		self.z = a.z - b.z;

		return self;

	}

	Vec3* multiplyLocal(Vec3 v ) {

		self.x *= v.x;
		self.y *= v.y;
		self.z *= v.z;

		return self;

	}

	Vec3* multiplyScalarLocal(float scalar ) {

		self.x *= scalar;
		self.y *= scalar;
		self.z *= scalar;

		return self;

	}

	Vec3* multiplyVectorsLocal(Vec3 a, Vec3 b ) {

		self.x = a.x * b.x;
		self.y = a.y * b.y;
		self.z = a.z * b.z;

		return self;

	}

	// Vec3* applyEulerLocal( euler ) {

	// 	return self.applyQuaternion( _quaternion.setFromEuler( euler ) );

	// }

	// Vec3* applyAxisAngle( axis, angle ) {

	// 	return self.applyQuaternion( _quaternion.setFromAxisAngle( axis, angle ) );

	// }

	Vec3* applyMatrix3Local(Mat3 m ) {

		float x = self.x
		float y = self.y
		float z = self.z;
		float* e = m.data;

		self.x = e[ 0 ] * x + e[ 3 ] * y + e[ 6 ] * z;
		self.y = e[ 1 ] * x + e[ 4 ] * y + e[ 7 ] * z;
		self.z = e[ 2 ] * x + e[ 5 ] * y + e[ 8 ] * z;

		return self;
	}

	Vec3* applyNormalMatrixLocal(Mat3 m ) {

		return self.applyMatrix3Local( m ).normalizeLocal();

	}

	Vec3 applyMatrix4(Mat m ) {
		Vec3 r = *self
		r.applyMatrix4Local(m)
		return r
	}
	Vec3* applyMatrix4Local(Mat m ) {

		float x = self.x
		float y = self.y
		float z = self.z;
		float* e = m.data;

		float w = 1 / ( e[ 3 ] * x + e[ 7 ] * y + e[ 11 ] * z + e[ 15 ] );

		self.x = ( e[ 0 ] * x + e[ 4 ] * y + e[ 8 ] * z + e[ 12 ] ) * w;
		self.y = ( e[ 1 ] * x + e[ 5 ] * y + e[ 9 ] * z + e[ 13 ] ) * w;
		self.z = ( e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z + e[ 14 ] ) * w;

		return self;

	}

	// Vec3* applyQuaternion( q ) {

	// 	const x = self.x, y = self.y, z = self.z;
	// 	const qx = q.x, qy = q.y, qz = q.z, qw = q.w;

	// 	// calculate quat * vector

	// 	const ix = qw * x + qy * z - qz * y;
	// 	const iy = qw * y + qz * x - qx * z;
	// 	const iz = qw * z + qx * y - qy * x;
	// 	const iw = - qx * x - qy * y - qz * z;

	// 	// calculate result * inverse quat

	// 	self.x = ix * qw + iw * - qx + iy * - qz - iz * - qy;
	// 	self.y = iy * qw + iw * - qy + iz * - qx - ix * - qz;
	// 	self.z = iz * qw + iw * - qz + ix * - qy - iy * - qx;

	// 	return self;

	// }

	// Vec3* project( camera ) {
	// 	return self.applyMatrix4( camera.matrixWorldInverse ).applyMatrix4( camera.projectionMatrix );
	// }

	// Vec3* unproject( camera ) {
	// 	return self.applyMatrix4( camera.projectionMatrixInverse ).applyMatrix4( camera.matrixWorld );
	// }

	Vec3* transformDirectionLocal(Mat m ) {

		// input: THREE.Matrix4 affine matrix
		// vector interpreted as a direction

		float x = self.x
		float y = self.y
		float z = self.z;
		float* e = m.data;

		self.x = e[ 0 ] * x + e[ 4 ] * y + e[ 8 ] * z;
		self.y = e[ 1 ] * x + e[ 5 ] * y + e[ 9 ] * z;
		self.z = e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z;

		return self.normalizeLocal();

	}

	Vec3* divideLocal(Vec3 v ) {

		self.x /= v.x;
		self.y /= v.y;
		self.z /= v.z;

		return self;

	}

	Vec3* divideScalarLocal(float scalar ) {

		return self.multiplyScalarLocal( 1 / scalar );

	}

	Vec3* minLocal(Vec3 v ) {

		self.x = minFloat( self.x, v.x );
		self.y = minFloat( self.y, v.y );
		self.z = minFloat( self.z, v.z );

		return self;

	}

	Vec3* maxLocal(Vec3 v ) {

		self.x = maxFloat( self.x, v.x );
		self.y = maxFloat( self.y, v.y );
		self.z = maxFloat( self.z, v.z );

		return self;

	}


	Vec3* floorLocal() {

		self.x = floor( self.x );
		self.y = floor( self.y );
		self.z = floor( self.z );

		return self;

	}

	Vec3* ceilLocal() {

		self.x = ceil( self.x );
		self.y = ceil( self.y );
		self.z = ceil( self.z );

		return self;

	}

	Vec3* roundLocal() {

		self.x = round( self.x );
		self.y = round( self.y );
		self.z = round( self.z );

		return self;

	}

	Vec3* roundToZeroLocal() {

		self.x = ( self.x < 0.0 ) ? ceil( self.x ) : floor( self.x );
		self.y = ( self.y < 0.0 ) ? ceil( self.y ) : floor( self.y );
		self.z = ( self.z < 0.0 ) ? ceil( self.z ) : floor( self.z );

		return self;

	}

	Vec3* negateLocal() {

		self.x = - self.x;
		self.y = - self.y;
		self.z = - self.z;

		return self;

	}

	float dot(Vec3 v ) {

		return self.x * v.x + self.y * v.y + self.z * v.z;

	}

	// TODO lengthSquared?

	float lengthSq() {

		return self.x * self.x + self.y * self.y + self.z * self.z;

	}

	float length() {

		return sqrt( self.x * self.x + self.y * self.y + self.z * self.z );

	}

	float manhattanLength() {

		return absFloat( self.x ) + absFloat( self.y ) + absFloat( self.z );

	}
	//归一化
	Vec3 normal(){
		float len = self.length()
		if len == 0.0 {
			len = 1
		}
		return self.scale( 1 / len )
	}

	Vec3* normalizeLocal() {

		float l = self.length()
		return self.divideScalarLocal( eqFloat(l, 0) ? 1 : l);

	}

	Vec3* setLength(float length ) {

		return self.normalizeLocal().multiplyScalarLocal( length );

	}

	Vec3 lerp(Vec3 b, float ratio){
		Vec3 r;
		r.x = lerpFloat(self.x, b.x, ratio)
		r.y = lerpFloat(self.y, b.y, ratio)
		r.z = lerpFloat(self.z, b.z, ratio)

		return r
	}
	Vec3* lerpLocal(Vec3 v, float alpha ) {

		self.x += ( v.x - self.x ) * alpha;
		self.y += ( v.y - self.y ) * alpha;
		self.z += ( v.z - self.z ) * alpha;

		return self;

	}

	Vec3* lerpVectorsLocal(Vec3 v1, Vec3 v2, float alpha ) {

		self.x = v1.x + ( v2.x - v1.x ) * alpha;
		self.y = v1.y + ( v2.y - v1.y ) * alpha;
		self.z = v1.z + ( v2.z - v1.z ) * alpha;

		return self;

	}

	//叉积
	Vec3 cross(Vec3 b){
		Vec3 r;
		r.x = self.y * b.z - self.z * b.y;
		r.y = self.z * b.x - self.x * b.z;
		r.z = self.x * b.y - self.y * b.x;
		return r

	}
	Vec3* crossLocal(Vec3 v ) {

		return self.crossVectorsLocal( *self, v );

	}

	Vec3* crossVectorsLocal(Vec3 a, Vec3 b ) {

		float ax = a.x
		float ay = a.y
		float az = a.z;
		float bx = b.x
		float by = b.y
		float bz = b.z;

		self.x = ay * bz - az * by;
		self.y = az * bx - ax * bz;
		self.z = ax * by - ay * bx;

		return self;

	}

	Vec3* projectOnVectorLocal(Vec3 v ) {

		float denominator = v.lengthSq();

		if ( eqFloat(denominator, 0.0) ) {
			return self.set( 0, 0, 0 );
		}

		float scalar = v.dot( *self ) / denominator;

		return self.copy( v ).multiplyScalarLocal( scalar );

	}

	// Vec3* projectOnPlane( planeNormal ) {

	// 	_vector.copy( self ).projectOnVector( planeNormal );

	// 	return self.sub( _vector );
	// }

	Vec3* reflect(Vec3 normal ) {

		// reflect incident vector off plane orthogonal to normal
		// normal is assumed to have unit length
		Vec3 _vector

		return self.subLocal( *(_vector.copy( normal ).multiplyScalarLocal( 2 * self.dot( normal ) ) ));

	}

	float angleTo(Vec3 v ) {

		float denominator = sqrt( self.lengthSq() * v.lengthSq() );

		if ( eqFloat(denominator, 0) ) {
			return PI / 2.0;
		}

		float theta = self.dot( v ) / denominator;

		// clamp, to handle numerical problems

		return acos( clampFloat( theta, - 1, 1 ) );

	}

	float distanceTo(Vec3 v ) {

		return sqrt( self.distanceToSquared( v ) );

	}

	float distanceToSquared(Vec3 v ) {

		float dx = self.x - v.x;
		float dy = self.y - v.y;
		float dz = self.z - v.z;

		return dx * dx + dy * dy + dz * dz;

	}

	float manhattanDistanceTo(Vec3 v ) {

		return absFloat( self.x - v.x ) + absFloat( self.y - v.y ) + absFloat( self.z - v.z );

	}

	Vec3* setFromSphericalLocal(Spherical s ) {
		return self.setFromSphericalCoordsLocal( s.radius, s.phi, s.theta );
	}

	Vec3* setFromSphericalCoordsLocal( float radius, float phi, float theta ) {

		float sinPhiRadius = sin( phi ) * radius;

		self.x = sinPhiRadius * sin( theta );
		self.y = cos( phi ) * radius;
		self.z = sinPhiRadius * cos( theta );

		return self;

	}

	// Vec3* setFromCylindrical( c ) {

	// 	return self.setFromCylindricalCoords( c.radius, c.theta, c.y );

	// }

	// Vec3* setFromCylindricalCoords( radius, theta, y ) {

	// 	self.x = radius * sin( theta );
	// 	self.y = y;
	// 	self.z = radius * cos( theta );

	// 	return self;

	// }

	Vec3* setFromMatrixPosition(Mat m ) {
		float* e = m.data;

		self.x = e[ 12 ];
		self.y = e[ 13 ];
		self.z = e[ 14 ];

		return self;

	}

	Vec3* setFromMatrixScale(Mat m ) {

		float sx = self.setFromMatrixColumn( m, 0 ).length();
		float sy = self.setFromMatrixColumn( m, 1 ).length();
		float sz = self.setFromMatrixColumn( m, 2 ).length();

		self.x = sx;
		self.y = sy;
		self.z = sz;

		return self;

	}

	Vec3* setFromMatrixColumn(Mat m, int index ) {
		return self.fromArray( m.data, index * 4 );
	}

	Vec3* setFromMatrix3Column(Mat3 m, int index ) {
		return self.fromArray( m.data, index * 3 );
	}

	Vec3* setFromEuler(Euler e ) {

		self.x = e.x;
		self.y = e.y;
		self.z = e.z;

		return self;
	}

	Vec3* setFromRgbaf(Rgbaf c ) {

		self.x = c.r;
		self.y = c.g;
		self.z = c.b;

		return self;

	}



	Vec3* fromArray(float* array, int offset  ) {

		self.x = array[ offset ];
		self.y = array[ offset + 1 ];
		self.z = array[ offset + 2 ];

		return self;

	}

	float *toArray( float * array , int offset  ) {

		array[ offset ] = self.x;
		array[ offset + 1 ] = self.y;
		array[ offset + 2 ] = self.z;

		return array;

	}

	// fromBufferAttribute( attribute, index ) {

	// 	self.x = attribute.getX( index );
	// 	self.y = attribute.getY( index );
	// 	self.z = attribute.getZ( index );

	// 	return self;

	// }

	Vec3* randomLocal() {

		self.x = random();
		self.y = random();
		self.z = random();

		return self;

	}

	Vec3* randomDirectionLocal() {

		// Derived from https://mathworld.wolfram.com/SpherePointPicking.html

		float u = ( random() - 0.5 ) * 2;
		float t = random() * PI * 2;
		float f = sqrt( 1 - pow(u, 2) );

		self.x = f * cos( t );
		self.y = f * sin( t );
		self.z = u;

		return self;

	}







	// void dtor(){
	// 	// printf("释放Vec3:%f,%f\n", self.x, self.y)
	// }
	// //垂线
	// Vec3 vertical(){
	// 	Vec3 ret = mkVec3(0,0, 0)
	// 	ret.x = self.x
	// 	ret.y = -self.y
	// 	ret.z = self.z
	// 	return ret
	// }
	
	//缩放
	Vec3 scale(float f){
		Vec3 ret = mkVec3(0,0, 0)
		ret.x = self.x * f
		ret.y = self.y * f
		ret.z = self.z * f
		return ret
	}

	Vec3* add3fLocal(float x, float y, float z){
		self.x += x
		self.y += y
		self.z += z
		return self
	}
	//缩放
	Vec3 add3f(float x, float y, float z){
		Vec3 ret = mkVec3(
			self.x + x,
			self.y + y,
			self.z + z,
		)
		return ret
	}
	Vec3 add(Vec3 b){
		Vec3 ret = mkVec3(0,0, 0)
		ret.x = self.x + b.x;
		ret.y = self.y + b.y;
		ret.z = self.z + b.z;
		return ret
	}

	Vec3 sub(Vec3 b){
		Vec3 ret
		ret.x = self.x - b.x;
		ret.y = self.y - b.y;
		ret.z = self.z - b.z;
		return ret
	}




	void setAll(float v){
		self.x = v
		self.y = v
		self.z = v
	}
	// 	//与正x轴的夹角
	// float radToXAxis() {
	// 	return atan2(self.y, self.x);
	// } 



	// bool hasNan() { 
	// 	return isnan(self.x) || isnan(self.y); 
	// }
	bool equals(Vec3 b){
		return fabsf(self.x - b.x) < 0.00001 
		&&  fabsf(self.y - b.y) < 0.00001
		&&  fabsf(self.z - b.z) < 0.00001
	}



	Vec3* clampLocal(Vec3 min, Vec3 max ) {

		// assumes min < max, componentwise

		self.x = maxFloat( min.x, minFloat( max.x, self.x ) );
		self.y = maxFloat( min.y, minFloat( max.y, self.y ) );
		self.z = maxFloat( min.z, minFloat( max.z, self.z ) );

		return self;

	}

	Vec3* clampScalarLocal(float minVal, float maxVal ) {

		self.x = maxFloat( minVal, minFloat( maxVal, self.x ) );
		self.y = maxFloat( minVal, minFloat( maxVal, self.y ) );
		self.z = maxFloat( minVal, minFloat( maxVal, self.z ) );

		return self;

	}

	Vec3* clampLengthLocal(float min, float max ) {

		float length = self.length();

		return self.divideScalarLocal( eqFloat(length, 0) ?  1: length ).multiplyScalarLocal( maxFloat( min, minFloat( max, length ) ) );

	}



	Vec3 clamp( Vec3 min, Vec3 max ) {

		// assumes min < max, componentwise
		Vec3 r

		r.x = maxFloat( min.x, minFloat( max.x, self.x ) );
		r.y = maxFloat( min.y, minFloat( max.y, self.y ) );
		r.z = maxFloat( min.z, minFloat( max.z, self.z ) );

		return r

	}

	Vec3 clampScalar(float minVal, float maxVal ) {
		Vec3 r

		r.x = maxFloat( minVal, minFloat( maxVal, self.x ) );
		r.y = maxFloat( minVal, minFloat( maxVal, self.y ) );
		r.z = maxFloat( minVal, minFloat( maxVal, self.z ) );

		return r;

	}

	Vec3 clampLength( float min, float max ) {

		float length = self.length();

		Vec3 tmp = self.scale( 1 / (length == 0 ? 1 : length ) )
		return tmp.scale( maxFloat( min, minFloat( max, length ) ) );
	}


}

Vec3 mkVec3(float x, float y, float z){
	Vec3 v 
	v.x = x;
	v.y = y
	v.z = z
	return v;
}


void testVec3(){
	Vec3 v = mkVec3(0,0, 0)
	v.x = 10;
	v.y = 10
	Vec3 b = mkVec3(0,0, 0)
	b.x = 17;
	b.y = 17
	float dis = v.distanceTo(b);	
	printf("dis:%f\n", dis);
	
	float sqrDis = v.distanceToSquared(b)
	printf("sqrdis :%f\n", sqrDis);
 
	printf("equals: %d\n", b.equals(v))
	b.set(10, 10.00001, 0); 
	printf("equals:%d\n", b.equals(v))

	printf("vec3 width:%f, height:%f %f %f\n", 
	v.width(), v.height()
	, b.width(), b.height()
	
	)
}