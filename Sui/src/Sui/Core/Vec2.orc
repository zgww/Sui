package SuiCore

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


import * from "../../Orc/Math.orc"
import * from "../../Orc/String.orc"
import * from "./Mat3.orc"


struct IntVec2 {
	int x
	int y
}
/// 布局上下文
struct Vec2 {
	float x 
	float y 
}
extension Vec2 {

	String@ toString(){
		char b[128];
		sprintf(b, "Vec2(%f,%f)", self.x, self.y)
		return str(b)
	}
	float width(){
		return self.x
	}
	float height(){
		return self.y
	}


	Vec2* set( float x, float y ) {
		self.x = x;
		self.y = y;
		return self
	}

	Vec2* setScalar(float scalar ) {
		self.x = scalar;
		self.y = scalar;
		return self
	}

	void setX( float x ) {
		self.x = x;
	}

	void setY( float y ) {
		self.y = y;
	}

	void setComponent(int index, float value ) {
		if index == 0 { self.x = value; }
		else if index == 1 { self.y = value; }
	}

	float getComponent(int index ) {
		if index == 0 { return self.x  }
		else if index == 1 { return self.y }

		return 0.0
	}

	Vec2 clone() {
		return *self
	}

	Vec2* copy(Vec2 v ) {
		self.x = v.x;
		self.y = v.y;
		return self
	}

	Vec2* addLocal(Vec2 v ) {
		self.x += v.x;
		self.y += v.y;
		return self
	}

	Vec2* addScalarLocal(float s ) {
		self.x += s;
		self.y += s;
		return self
	}

	Vec2* addVectorsLocal(Vec2 a, Vec2 b ) {
		self.x = a.x + b.x;
		self.y = a.y + b.y;
		return self
	}

	Vec2* addScaledVectorLocal(Vec2 v, float s ) {
		self.x += v.x * s;
		self.y += v.y * s;
		return self
	}


	Vec2* subLocal(Vec2 v ) {
		self.x -= v.x;
		self.y -= v.y;
		return self
	}

	Vec2* subScalarLocal(float s ) {
		self.x -= s;
		self.y -= s;
		return self
	}

	Vec2* subVectorsLocal(Vec2 a, Vec2 b ) {
		self.x = a.x - b.x;
		self.y = a.y - b.y;
		return self
	}

	Vec2* multiplyLocal(Vec2 v ) {
		self.x *= v.x;
		self.y *= v.y;
		return self
	}

	Vec2* multiplyScalarLocal(float scalar ) {
		self.x *= scalar;
		self.y *= scalar;
		return self
	}

	Vec2* divideLocal(Vec2 v ) {
		self.x /= v.x;
		self.y /= v.y;
		return self
	}

	Vec2* divideScalarLocal(float scalar ) {
		self.multiplyScalarLocal( 1 / scalar );
		return self
	}

	Vec2* applyMatrix3Local(Mat3 m ) {
		float x = self.x;
		float y = self.y;
		float* e = m.data;

		self.x = e[ 0 ] * x + e[ 3 ] * y + e[ 6 ];
		self.y = e[ 1 ] * x + e[ 4 ] * y + e[ 7 ];
		return self
	}

	Vec2* minLocal(Vec2 v ) {
		self.x = minFloat( self.x, v.x );
		self.y = minFloat( self.y, v.y );

		return self
	}

	Vec2* maxLocal(Vec2 v ) {
		self.x = maxFloat( self.x, v.x );
		self.y = maxFloat( self.y, v.y );
		return self
	}




	Vec2* floorLocal() {
		self.x = floorFloat( self.x );
		self.y = floorFloat( self.y );

		return self;
	}

	Vec2* ceilLocal() {

		self.x = ceil( self.x );
		self.y = ceil( self.y );

		return self;

	}

	Vec2* roundLocal() {

		self.x = round( self.x );
		self.y = round( self.y );

		return self;

	}

	Vec2* roundToZeroLocal() {

		self.x = ( self.x < 0 ) ? ceil( self.x ) : floor( self.x );
		self.y = ( self.y < 0 ) ? ceil( self.y ) : floor( self.y );

		return self;

	}

	Vec2* negateLocal() {

		self.x = - self.x;
		self.y = - self.y;

		return self;

	}

	float dot(Vec2 v ) {

		return self.x * v.x + self.y * v.y;

	}

	float cross(Vec2 v ) {
		return self.x * v.y - self.y * v.x;
	}

	float lengthSq() {
		return self.x * self.x + self.y * self.y;
	}

	float length() {
		return sqrt( self.x * self.x + self.y * self.y );
	}

	float anhattanLength() {
		return absFloat( self.x ) + absFloat( self.y );
	}

	Vec2* normalizeLocal() {
		float l = self.length() 
		return self.divideScalarLocal( eqFloat(l, 0) ? 1 : l );
	}

	// //缩放 不对
	// Vec2 normal(float f){
	// 	Vec2 ret = mkVec2(0,0)
	// 	ret.x = self.x * f
	// 	ret.y = self.y * f
	// 	return ret
	// }

	// 返回[0, 2*PI)
	// 0是x轴正方向
	float angle() {

		// computes the angle in radians with respect to the positive x-axis

		float angle = atan2( - self.y, - self.x ) + PI;

		return angle;

	}

	float angleTo(Vec2 v ) {

		float denominator = sqrt( self.lengthSq() * v.lengthSq() );

		if eqFloat( denominator , 0 ) {
			return PI / 2.0;
		}

		float theta = self.dot( v ) / denominator;

		// clamp, to handle numerical problems

		return acos( clampFloat( theta, - 1, 1 ) );
	}

	float distanceTo(Vec2 v ) {

		return sqrt( self.distanceToSquared( v ) );
	}

	float distanceToSquared(Vec2 v ) {

		float dx = self.x - v.x
		float dy = self.y - v.y;
		return dx * dx + dy * dy;

	}

	float manhattanDistanceTo(Vec2 v ) {

		return absFloat( self.x - v.x ) + absFloat( self.y - v.y );

	}

	Vec2* setLengthLocal(float length ) {

		return self.normalizeLocal().multiplyScalarLocal( length );

	}

	Vec2* lerpLocal( Vec2 v, float alpha ) {
		self.x += ( v.x - self.x ) * alpha;
		self.y += ( v.y - self.y ) * alpha;
		return self;
	}

	Vec2* lerpVectorsLocal(Vec2 v1, Vec2 v2, float alpha ) {
		self.x = v1.x + ( v2.x - v1.x ) * alpha;
		self.y = v1.y + ( v2.y - v1.y ) * alpha;
		return self;
	}



	Vec2* fromArray( float *array, int offset ) {
		self.x = array[ offset ];
		self.y = array[ offset + 1 ];
		return self;
	}

	float* toArray(float* array , int offset  ) {
		array[ offset ] = self.x;
		array[ offset + 1 ] = self.y;
		return array;

	}

	// fromBufferAttribute( attribute, index ) {

	// 	self.x = attribute.getX( index );
	// 	self.y = attribute.getY( index );

	// 	return self;

	// }

	Vec2* rotateAroundLocal(Vec2 center, float angle ) {

		float c = cos( angle )
		float s = sin( angle );

		float x = self.x - center.x;
		float y = self.y - center.y;

		self.x = x * c - y * s + center.x;
		self.y = x * s + y * c + center.y;

		return self;

	}

	Vec2* randomLocal() {
		self.x = rand();
		self.y = rand();

		return self;
	}



	// void dtor(){
	// 	// printf("释放Vec2:%f,%f\n", self.x, self.y)
	// }
	//垂线. 什么作用？
	// Vec2 vertical(){
	// 	Vec2 ret = mkVec2(0,0)
	// 	ret.x = self.x
	// 	ret.y = -self.y
	// 	return ret
	// }
	
	//缩放
	Vec2 scale(float f){
		Vec2 ret = mkVec2(0,0)
		ret.x = self.x * f
		ret.y = self.y * f
		return ret
	}

	Vec2* clampLengthLocal(float min, float max ) {
		float length = self.length();

		self.divideScalarLocal( eqFloat(length, 0) ? 1 : length ).multiplyScalarLocal( 
			maxFloat( min, minFloat( max, length ) ) );
		return self
	}
	void clampLocal( Vec2 min, Vec2 max ) {

		// assumes min < max, componentwise


		self.x = maxFloat( min.x, minFloat( max.x, self.x ) );
		self.y = maxFloat( min.y, minFloat( max.y, self.y ) );
	}
	Vec2 clamp( Vec2 min, Vec2 max ) {

		// assumes min < max, componentwise

		Vec2 r

		r.x = maxFloat( min.x, minFloat( max.x, self.x ) );
		r.y = maxFloat( min.y, minFloat( max.y, self.y ) );

		return r;
	}

	Vec2* clampScalarLocal(float minVal, float maxVal ) {

		self.x = maxFloat( minVal, minFloat( maxVal, self.x ) );
		self.y = maxFloat( minVal, minFloat( maxVal, self.y ) );
		return self

	}
	Vec2 clampScalar(float minVal, float maxVal ) {

		Vec2 r
		r.x = maxFloat( minVal, minFloat( maxVal, self.x ) );
		r.y = maxFloat( minVal, minFloat( maxVal, self.y ) );

		return r

	}


	//缩放
	Vec2 add(Vec2 b){
		Vec2 ret = mkVec2(0,0)
		ret.x = self.x + b.x;
		ret.y = self.y + b.y;
		return ret
	}
	//缩放
	Vec2 sub(Vec2 b){
		Vec2 ret = mkVec2(0,0)
		ret.x = self.x - b.x;
		ret.y = self.y - b.y;
		return ret
	}



		//与正x轴的夹角
	float radToXAxis() {
		return atan2(self.y, self.x);
	} 

	// void copyFromVec2(Vec2 *a) {
	// 	self.x = a.x;
	// 	self.y = a.y;
	// }
	
	// bool hasNan() { 
	// 	return isnan(self.x) || isnan(self.y); 
	// }
	bool equals(Vec2 b){
		return fabsf(self.x - b.x) < EPSILON &&  fabsf(self.y - b.y) < EPSILON
	}

}

Vec2 mkVec2(float x, float y){
	Vec2 v 
	v.x = x;
	v.y = y
	return v;
}


void testVec2(){
	Vec2 v = mkVec2(0,0)
	v.x = 10;
	v.y = 10
	Vec2 b = mkVec2(0,0)
	b.x = 17;
	b.y = 17
	float dis = v.distanceTo(b);	
	printf("dis:%f\n", dis);
	
	float sqrDis = v.distanceToSquared(b)
	printf("sqrdis :%f\n", sqrDis);
 
	printf("equals: %d\n", b.equals(v))
	b.set(10, 10.000001); 
	printf("equals:%d\n", b.equals(v))

	printf("vec2 width:%f, height:%f %f %f\n", 
	v.width(), v.height()
	, b.width(), b.height()
	
	)
}