
package SuiCore

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"
import * from "./Mat3.orc"
import * from "./Vec3.orc"
import * from "./Quaternion.orc"
import * from "./Spherical.orc"



/// 布局上下文
struct Euler {
	float x 
	float y 
	float z 
    //XYZ|YXZ|ZXY|ZYX|YZX|XZY
    const char *order
}
const char *Euler_XYZ = "XYZ"
const char *Euler_YXZ = "YXZ"
const char *Euler_ZXY = "ZXY"
const char *Euler_ZYX = "ZYX"
const char *Euler_YZX = "YZX"
const char *Euler_XZY = "XZY"
const char *Euler_Default = "XYZ"

extension Euler {
	bool isXYZ(){
		return strcmp(self.order, "XYZ") == 0
	}
	bool isYXZ(){
		return strcmp(self.order, "YXZ") == 0
	}
	bool isZXY(){
		return strcmp(self.order, "ZXY") == 0
	}
	bool isZYX(){
		return strcmp(self.order, "ZYX") == 0
	}
	bool isYZX(){
		return strcmp(self.order, "YZX") == 0
	}
	bool isXZY(){
		return strcmp(self.order, "XZY") == 0
	}


	Euler* set( float x, float y, float z, const char *order ) {

		self.x = x;
		self.y = y;
		self.z = z;
		self.order = order == null ? Euler_Default : order;

		// self._onChangeCallback();

		return self;

	}

	Euler clone() {
		return *self
	}

	Euler* copy(Euler euler ) {

		self.x = euler.x;
		self.y = euler.y;
		self.z = euler.z;
		self.order = euler.order;

		// self._onChangeCallback();

		return self;

	}

	Euler* setFromRotationMatrix(Mat m, const char * order) {
		if order == null {
			order = Euler_Default
		}

		// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

		float* te = m.data;
		float m11 = te[ 0 ]; float m12 = te[ 4 ]; float m13 = te[ 8 ];
		float m21 = te[ 1 ]; float m22 = te[ 5 ]; float m23 = te[ 9 ];
		float m31 = te[ 2 ]; float m32 = te[ 6 ]; float m33 = te[ 10 ];


			if strcmp(order, "XYZ") {


				self.y = asin( clampFloat( m13, - 1, 1 ) );

				if ( absFloat( m13 ) < 0.9999999 ) {

					self.x = atan2( - m23, m33 );
					self.z = atan2( - m12, m11 );

				} else {

					self.x = atan2( m32, m22 );
					self.z = 0;

				}
			}

			else if strcmp(order,  "YXZ"){

				self.x = asin( - clampFloat( m23, - 1, 1 ) );

				if ( absFloat( m23 ) < 0.9999999 ) {

					self.y = atan2( m13, m33 );
					self.z = atan2( m21, m22 );

				} else {

					self.y = atan2( - m31, m11 );
					self.z = 0;

				}

			}

			else if strcmp(order,  "ZXY"){

				self.x = asin( clampFloat( m32, - 1, 1 ) );

				if ( absFloat( m32 ) < 0.9999999 ) {

					self.y = atan2( - m31, m33 );
					self.z = atan2( - m12, m22 );

				} else {

					self.y = 0;
					self.z = atan2( m21, m11 );

				}

			}

			else if strcmp(order,  "ZYX"){

				self.y = asin( - clampFloat( m31, - 1, 1 ) );

				if ( absFloat( m31 ) < 0.9999999 ) {

					self.x = atan2( m32, m33 );
					self.z = atan2( m21, m11 );

				} else {

					self.x = 0;
					self.z = atan2( - m12, m22 );

				}

			}

			else if strcmp(order,  "YZX"){

				self.z = asin( clampFloat( m21, - 1, 1 ) );

				if ( absFloat( m21 ) < 0.9999999 ) {

					self.x = atan2( - m23, m22 );
					self.y = atan2( - m31, m11 );

				} else {

					self.x = 0;
					self.y = atan2( m13, m33 );

				}

			}

			else if strcmp(order,  "XZY"){

				self.z = asin( - clampFloat( m12, - 1, 1 ) );

				if ( absFloat( m12 ) < 0.9999999 ) {

					self.x = atan2( m32, m22 );
					self.y = atan2( m13, m11 );

				} else {

					self.x = atan2( - m23, m33 );
					self.y = 0;

				}

			}

			else {
				printf( " setFromRotationMatrix() encountered an unknown order::%s ", order );
			}


		self.order = order;

		// if ( update == true ) self._onChangeCallback();

		return self;

	}

	Euler* setFromQuaternion( Quaternion q, const char * order) {
		Mat _matrix;

		_matrix.makeRotationFromQuaternion( q );

		return self.setFromRotationMatrix( _matrix, order);

	}

	Euler* setFromVector3(Vec3 v, const char *order) {

		return self.set( v.x, v.y, v.z, order  );

	}

	// Euler * reorder(const char* newOrder ) {
	// 	// WARNING: self discards revolution information -bhouston
	// 	_quaternion.setFromEuler( self );
	// 	return self.setFromQuaternion( _quaternion, newOrder );
	// }

	bool equals(Euler euler ) {

		return eqFloat(euler.x, self.x)
		  && eqFloat( euler.y, self.y )
		  && eqFloat( euler.z, self.z ) && ( strcmp(euler.order, self.order) == 0 );

	}

	Euler* fromArray( float *array ) {

		self.x = array[ 0 ];
		self.y = array[ 1 ];
		self.z = array[ 2 ];
		// if ( array[ 3 ] !== undefined ) self._order = array[ 3 ];

		// self._onChangeCallback();

		return self;
	}

	float * toArray(float* array , int offset  ) {
		array[ offset ] = self.x;
		array[ offset + 1 ] = self.y;
		array[ offset + 2 ] = self.z;
		// array[ offset + 3 ] = self._order;
		return array;
	}
}