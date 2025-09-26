
package SuiCore

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

import * from "../../Orc/String.orc"
import * from "../../Orc/Math.orc"
import * from "../../Sgl/Mat.orc"
import type * from "../../Sgl/Sphere.orc"
import type * from "./Mat3.orc"
import type * from "./Plane.orc"
import type * from "./Vec3.orc"
import type * from "./Euler.orc"
import type * from "./Spherical.orc"



// 四元数
struct Quaternion {
    float x
    float y
    float z
    float w
}
extension Quaternion {

	Quaternion* set(float x, float y, float z, float w ) {

		self.x = x;
		self.y = y;
		self.z = z;
		self.w = w;

		// self._onChangeCallback();

		return self;

	}

	Quaternion clone() {
        return *self
		// return new self.constructor( self.x, self.y, self.z, self.w );
	}

	Quaternion* copy(Quaternion quaternion ) {

		self.x = quaternion.x;
		self.y = quaternion.y;
		self.z = quaternion.z;
		self.w = quaternion.w;

		// self._onChangeCallback();

		return self;

	}

	Quaternion* setFromEuler(Euler euler) {

		float x = euler.x
        float y = euler.y
        float z = euler.z
        const char *order = euler.order;

		// http://www.mathworks.com/matlabcentral/fileexchange/
		// 	20696-function-to-convert-between-dcm-euler-angles-quaternions-and-euler-vectors/
		//	content/SpinCalc.m


		float c1 = cos( x / 2.0 );
		float c2 = cos( y / 2.0 );
		float c3 = cos( z / 2.0 );

		float s1 = sin( x / 2.0 );
		float s2 = sin( y / 2.0 );
		float s3 = sin( z / 2.0 );


			if strcmp(order,  "XYZ") == 0 {
				self.x = s1 * c2 * c3 + c1 * s2 * s3;
				self.y = c1 * s2 * c3 - s1 * c2 * s3;
				self.z = c1 * c2 * s3 + s1 * s2 * c3;
				self.w = c1 * c2 * c3 - s1 * s2 * s3;
            }

			else if strcmp(order,  "YXZ") == 0 {
				self.x = s1 * c2 * c3 + c1 * s2 * s3;
				self.y = c1 * s2 * c3 - s1 * c2 * s3;
				self.z = c1 * c2 * s3 - s1 * s2 * c3;
				self.w = c1 * c2 * c3 + s1 * s2 * s3;
            }

			else if strcmp(order,  "ZXY") == 0 {
				self.x = s1 * c2 * c3 - c1 * s2 * s3;
				self.y = c1 * s2 * c3 + s1 * c2 * s3;
				self.z = c1 * c2 * s3 + s1 * s2 * c3;
				self.w = c1 * c2 * c3 - s1 * s2 * s3;
            }

			else if strcmp(order,  "ZYX") == 0 {
				self.x = s1 * c2 * c3 - c1 * s2 * s3;
				self.y = c1 * s2 * c3 + s1 * c2 * s3;
				self.z = c1 * c2 * s3 - s1 * s2 * c3;
				self.w = c1 * c2 * c3 + s1 * s2 * s3;
            }

			else if strcmp(order,  "YZX") == 0 {
				self.x = s1 * c2 * c3 + c1 * s2 * s3;
				self.y = c1 * s2 * c3 + s1 * c2 * s3;
				self.z = c1 * c2 * s3 - s1 * s2 * c3;
				self.w = c1 * c2 * c3 - s1 * s2 * s3;
            }

			else if strcmp(order,  "XZY") == 0 {
				self.x = s1 * c2 * c3 - c1 * s2 * s3;
				self.y = c1 * s2 * c3 - s1 * c2 * s3;
				self.z = c1 * c2 * s3 + s1 * s2 * c3;
				self.w = c1 * c2 * c3 + s1 * s2 * s3;
            }

			else {
				printf( "Quaternion: .setFromEuler() encountered an unknown order: %s" , order );
            }


		// if ( update != false ) self._onChangeCallback();

		return self;

	}

	Quaternion* setFromAxisAngle( Vec3 axis, float angle ) {

		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm

		// assumes axis is normalized

		float halfAngle = angle / 2.0
        float s = sin( halfAngle );

		self.x = axis.x * s;
		self.y = axis.y * s;
		self.z = axis.z * s;
		self.w = cos( halfAngle );

		// self._onChangeCallback();

		return self;

	}
	Vec3 toVec3AsEuler(const char *order){
        Euler e
        e.setFromQuaternion(*self, order == null ? Euler_Default : order)
		Vec3 r
		r.setFromEuler(e)
		return r
	}

	Quaternion* setFromRotationMatrix(Mat m ) {

		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

		// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

		float* te = m.data

        float m11 = te[ 0 ]; float m12 = te[ 4 ]; float m13 = te[ 8 ];
        float m21 = te[ 1 ]; float m22 = te[ 5 ]; float m23 = te[ 9 ];
        float m31 = te[ 2 ]; float m32 = te[ 6 ]; float m33 = te[ 10];

        float trace = m11 + m22 + m33;

		if ( trace > 0 ) {

			float s = 0.5 / sqrt( trace + 1.0 );

			self.w = 0.25 / s;
			self.x = ( m32 - m23 ) * s;
			self.y = ( m13 - m31 ) * s;
			self.z = ( m21 - m12 ) * s;

		} else if ( m11 > m22 && m11 > m33 ) {

			float s = 2.0 * sqrt( 1.0 + m11 - m22 - m33 );

			self.w = ( m32 - m23 ) / s;
			self.x = 0.25 * s;
			self.y = ( m12 + m21 ) / s;
			self.z = ( m13 + m31 ) / s;

		} else if ( m22 > m33 ) {

			float s = 2.0 * sqrt( 1.0 + m22 - m11 - m33 );

			self.w = ( m13 - m31 ) / s;
			self.x = ( m12 + m21 ) / s;
			self.y = 0.25 * s;
			self.z = ( m23 + m32 ) / s;

		} else {

			float s = 2.0 * sqrt( 1.0 + m33 - m11 - m22 );

			self.w = ( m21 - m12 ) / s;
			self.x = ( m13 + m31 ) / s;
			self.y = ( m23 + m32 ) / s;
			self.z = 0.25 * s;

		}

		// self._onChangeCallback();

		return self;

	}

	Quaternion* setFromUnitVectors(Vec3 vFrom, Vec3 vTo ) {

		// assumes direction vectors vFrom and vTo are normalized

		float r = vFrom.dot( vTo ) + 1;

		if ( r < EPSILON ) {

			// vFrom and vTo point in opposite directions

			r = 0;

			if ( absFloat( vFrom.x ) > absFloat( vFrom.z ) ) {

				self.x = - vFrom.y;
				self.y = vFrom.x;
				self.z = 0;
				self.w = r;

			} else {

				self.x = 0;
				self.y = - vFrom.z;
				self.z = vFrom.y;
				self.w = r;

			}

		} else {

			// crossVectors( vFrom, vTo ); // inlined to avoid cyclic dependency on Vector3

			self.x = vFrom.y * vTo.z - vFrom.z * vTo.y;
			self.y = vFrom.z * vTo.x - vFrom.x * vTo.z;
			self.z = vFrom.x * vTo.y - vFrom.y * vTo.x;
			self.w = r;

		}

		return self.normalizeLocal();

	}

	float angleTo( Quaternion q ) {
		return 2 * acos( absFloat( clampFloat( self.dot( q ), - 1, 1 ) ) );
	}

	Quaternion* rotateTowardsLocal( Quaternion q, float step ) {

		float angle = self.angleTo( q );

		if ( angle == 0 ) {return self;}

		float t = minFloat( 1, step / angle );

		self.slerpLocal( q, t );

		return self;

	}

	Quaternion* identity() {
		return self.set( 0, 0, 0, 1 );
	}

	Quaternion* invertLocal() {

		// quaternion is assumed to have unit length

		return self.conjugateLocal();

	}

	Quaternion* conjugateLocal() {

		self.x *= - 1;
		self.y *= - 1;
		self.z *= - 1;

		// self._onChangeCallback();

		return self;

	}

	float dot(Quaternion v ) {
		return self.x * v.x + self.y * v.y + self.z * v.z + self.w * v.w;
	}

	float lengthSq() {

		return self.x * self.x + self.y * self.y + self.z * self.z + self.w * self.w;

	}

	float length() {

		return sqrt( self.x * self.x + self.y * self.y + self.z * self.z + self.w * self.w );

	}

	Quaternion* normalizeLocal() {

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

		// self._onChangeCallback();

		return self;

	}

	Quaternion* multiplyLocal(Quaternion q ) {

		return self.multiplyQuaternionsLocal( *self, q );

	}

	Quaternion* premultiplyLocal(Quaternion q ) {

		return self.multiplyQuaternionsLocal( q, *self );

	}

	Quaternion* multiplyQuaternionsLocal(Quaternion a, Quaternion b ) {

		// from http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/code/index.htm

		float qax = a.x; float qay = a.y; float qaz = a.z; float qaw = a.w;
		float qbx = b.x; float qby = b.y; float qbz = b.z; float qbw = b.w;

		self.x = qax * qbw + qaw * qbx + qay * qbz - qaz * qby;
		self.y = qay * qbw + qaw * qby + qaz * qbx - qax * qbz;
		self.z = qaz * qbw + qaw * qbz + qax * qby - qay * qbx;
		self.w = qaw * qbw - qax * qbx - qay * qby - qaz * qbz;

		// self._onChangeCallback();

		return self;

	}

	Quaternion* slerpLocal(Quaternion qb, float t ) {

		if ( t == 0 ) {return self;}
		if ( t == 1 ) {return self.copy( qb );}

		float x = self.x; 
        float y = self.y;
        float z = self.z;
        float w = self.w;

		// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/

		float cosHalfTheta = w * qb.w + x * qb.x + y * qb.y + z * qb.z;

		if ( cosHalfTheta < 0 ) {

			self.w = - qb.w;
			self.x = - qb.x;
			self.y = - qb.y;
			self.z = - qb.z;

			cosHalfTheta = - cosHalfTheta;

		} else {

			self.copy( qb );

		}

		if ( cosHalfTheta >= 1.0 ) {

			self.w = w;
			self.x = x;
			self.y = y;
			self.z = z;

			return self;

		}

		float sqrSinHalfTheta = 1.0 - cosHalfTheta * cosHalfTheta;

		if ( sqrSinHalfTheta <= EPSILON ) {

			float s = 1 - t;
			self.w = s * w + t * self.w;
			self.x = s * x + t * self.x;
			self.y = s * y + t * self.y;
			self.z = s * z + t * self.z;

			self.normalizeLocal();
			// self._onChangeCallback();

			return self;

		}

		float sinHalfTheta = sqrt( sqrSinHalfTheta );
		float halfTheta = atan2( sinHalfTheta, cosHalfTheta );
		float ratioA = sin( ( 1 - t ) * halfTheta ) / sinHalfTheta
        float ratioB = sin( t * halfTheta ) / sinHalfTheta;

		self.w = ( w * ratioA + self.w * ratioB );
		self.x = ( x * ratioA + self.x * ratioB );
		self.y = ( y * ratioA + self.y * ratioB );
		self.z = ( z * ratioA + self.z * ratioB );

		// self._onChangeCallback();

		return self;

	}

	Quaternion* slerpQuaternionsLocal(Quaternion qa, Quaternion qb, float t ) {

		return self.copy( qa ).slerpLocal( qb, t );

	}

	Quaternion* randomLocal() {

		// Derived from http://planning.cs.uiuc.edu/node198.html
		// Note, self source uses w, x, y, z ordering,
		// so we swap the order below.

		float u1 = random();
		float sqrt1u1 = sqrt( 1 - u1 );
		float sqrtu1 = sqrt( u1 );

		float u2 = 2 * PI * random();

		float u3 = 2 * PI * random();

		return self.set(
			sqrt1u1 * cos( u2 ),
			sqrtu1 * sin( u3 ),
			sqrtu1 * cos( u3 ),
			sqrt1u1 * sin( u2 ),
		);

	}

	bool equals(Quaternion quaternion ) {

		return eqFloat( quaternion.x , self.x ) && eqFloat( quaternion.y , self.y ) 
        && eqFloat( quaternion.z , self.z ) && eqFloat( quaternion.w , self.w );

	}

	Quaternion* fromArray(float* array, int offset  ) {

		self.x = array[ offset ];
		self.y = array[ offset + 1 ];
		self.z = array[ offset + 2 ];
		self.w = array[ offset + 3 ];

		// self._onChangeCallback();

		return self;

	}

	float * toArray( float * array , int offset  ) {

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


}


void Quaternion_slerpFlat( float *dst, int dstOffset, float *src0, int srcOffset0, float* src1, int srcOffset1, float t ) {

    // fuzz-free, array-based Quaternion SLERP operation

    float x0 = src0[ srcOffset0 + 0 ];
    float y0 = src0[ srcOffset0 + 1 ];
    float z0 = src0[ srcOffset0 + 2 ];
    float w0 = src0[ srcOffset0 + 3 ];

    float x1 = src1[ srcOffset1 + 0 ];
    float y1 = src1[ srcOffset1 + 1 ];
    float z1 = src1[ srcOffset1 + 2 ];
    float w1 = src1[ srcOffset1 + 3 ];

    if ( eqFloat(t, 0) ) {

        dst[ dstOffset + 0 ] = x0;
        dst[ dstOffset + 1 ] = y0;
        dst[ dstOffset + 2 ] = z0;
        dst[ dstOffset + 3 ] = w0;
        return;

    }

    if ( eqFloat(t, 1) ) {

        dst[ dstOffset + 0 ] = x1;
        dst[ dstOffset + 1 ] = y1;
        dst[ dstOffset + 2 ] = z1;
        dst[ dstOffset + 3 ] = w1;
        return;

    }

    if ( w0 != w1 || x0 != x1 || y0 != y1 || z0 != z1 ) {

        float s = 1 - t;
        float cosVal = x0 * x1 + y0 * y1 + z0 * z1 + w0 * w1;
        float dir = ( cosVal >= 0 ? 1 : - 1 ),
        float sqrSin = 1 - cosVal * cosVal;

        // Skip the Slerp for tiny steps to avoid numeric problems:
        if ( sqrSin > EPSILON ) {

            float sinVal = sqrt( sqrSin )
            float len = atan2( sinVal, cosVal * dir );

            s = sin( s * len ) / sinVal;
            t = sin( t * len ) / sinVal;

        }

        float tDir = t * dir;

        x0 = x0 * s + x1 * tDir;
        y0 = y0 * s + y1 * tDir;
        z0 = z0 * s + z1 * tDir;
        w0 = w0 * s + w1 * tDir;

        // Normalize in case we just did a lerp:
        if ( s == 1 - t ) {

            float f = 1 / sqrt( x0 * x0 + y0 * y0 + z0 * z0 + w0 * w0 );

            x0 *= f;
            y0 *= f;
            z0 *= f;
            w0 *= f;

        }

    }

    dst[ dstOffset ] = x0;
    dst[ dstOffset + 1 ] = y0;
    dst[ dstOffset + 2 ] = z0;
    dst[ dstOffset + 3 ] = w0;

}

float* Quaternion_multiplyQuaternionsFlat( float *dst, int dstOffset, float *src0, int srcOffset0, float *src1, int srcOffset1 ) {

    float x0 = src0[ srcOffset0 ];
    float y0 = src0[ srcOffset0 + 1 ];
    float z0 = src0[ srcOffset0 + 2 ];
    float w0 = src0[ srcOffset0 + 3 ];

    float x1 = src1[ srcOffset1 ];
    float y1 = src1[ srcOffset1 + 1 ];
    float z1 = src1[ srcOffset1 + 2 ];
    float w1 = src1[ srcOffset1 + 3 ];

    dst[ dstOffset ] = x0 * w1 + w0 * x1 + y0 * z1 - z0 * y1;
    dst[ dstOffset + 1 ] = y0 * w1 + w0 * y1 + z0 * x1 - x0 * z1;
    dst[ dstOffset + 2 ] = z0 * w1 + w0 * z1 + x0 * y1 - y0 * x1;
    dst[ dstOffset + 3 ] = w0 * w1 - x0 * x1 - y0 * y1 - z0 * z1;

    return dst;

}