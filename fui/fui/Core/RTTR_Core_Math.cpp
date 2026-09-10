#include "Bezier.h"
#include "BoxShadow.h"
#include "Frustum.h"
#include "Line3.h"
#include "Mat2d.h"
#include "Mat3.h"
#include "Plane.h"
#include "Quat.h"
#include "Radius.h"
#include "Spherical.h"
#include "Triangle.h"
#include "Vec4.h"
#include "Vec2.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Bezier>("Bezier")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Bezier(*)(const Vec2&, const Vec2&, const Vec2&, const Vec2&)>(&mkBezier))
		.property("p0", &Bezier::p0)
		.property("p1", &Bezier::p1)
		.property("p2", &Bezier::p2)
		.property("p3", &Bezier::p3)
		.method("getPoint", &Bezier::getPoint)
		.method("getTangent", &Bezier::getTangent);

	registration::class_<BoxShadow>("BoxShadow")
		.constructor<>()(policy::ctor::as_object)
		.property("dx", &BoxShadow::dx)
		.property("dy", &BoxShadow::dy)
		.property("sigmaX", &BoxShadow::sigmaX)
		.property("sigmaY", &BoxShadow::sigmaY)
		.property("color", &BoxShadow::color);

	registration::class_<Frustum>("Frustum")
		.constructor<>()(policy::ctor::as_object)
		.property("planes", &Frustum::planes)
		.property("points", &Frustum::points)
		.method("toString", &Frustum::toString)
		.method("set", &Frustum::set)
		.method("clone", &Frustum::clone)
		.method("copy", &Frustum::copy)
		.method("setFromProjection", &Frustum::setFromProjection)
		.method("containsPoint", &Frustum::containsPoint)
		.method("intersectsSphere", &Frustum::intersectsSphere)
		.method("intersectsBox", &Frustum::intersectsBox);

	registration::class_<Line3>("Line3")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Line3(*)(const Vec3&, const Vec3&)>(&mkLine3))
		.property("start", &Line3::start)
		.property("end", &Line3::end)
		.method("toString", &Line3::toString)
		.method("set", &Line3::set)
		.method("clone", &Line3::clone)
		.method("copy", &Line3::copy)
		.method("delta", &Line3::delta)
		.method("deltaDirection", &Line3::deltaDirection)
		.method("length", &Line3::length)
		.method("distance", &Line3::distance)
		.method("at", &Line3::at)
		.method("closestPointToPoint", &Line3::closestPointToPoint)
		.method("getCenter", &Line3::getCenter);

	registration::class_<Mat2d>("Mat2d")
		.constructor<>()(policy::ctor::as_object)
		.property("data", &Mat2d::data)
		.method("identity", &Mat2d::identity)
		.method("translate", &Mat2d::translate)
		.method("scale", &Mat2d::scale)
		.method("rotate", &Mat2d::rotate)
		.method("multiply", &Mat2d::multiply)
		.method("premultiply", &Mat2d::premultiply)
		.method("inverse", &Mat2d::inverse)
		.method("inverseNew", &Mat2d::inverseNew)
		.method("transformPoint", &Mat2d::transformPoint);

	registration::class_<Mat3>("Mat3")
		.constructor<>()(policy::ctor::as_object)
		.property("elements", &Mat3::elements)
		.method("set", &Mat3::set)
		.method("identity", &Mat3::identity)
		.method("copy", &Mat3::copy)
		.method("clone", &Mat3::clone)
		.method("multiplyLocal", &Mat3::multiplyLocal)
		.method("premultiplyLocal", &Mat3::premultiplyLocal)
		.method("multiplyMatricesLocal", &Mat3::multiplyMatricesLocal)
		.method("scaleLocal", &Mat3::scaleLocal)
		.method("determinant", &Mat3::determinant)
		.method("invertLocal", &Mat3::invertLocal)
		.method("transposeLocal", &Mat3::transposeLocal)
		.method("applyToVec3", &Mat3::applyToVec3)
		.method("fromArray", &Mat3::fromArray)
		.method("toArray", &Mat3::toArray);

	registration::class_<Plane>("Plane")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Plane(*)(float, float, float, float)>(&mkPlane))
		.property("normal", &Plane::normal)
		.property("constant", &Plane::constant)
		.method("toString", &Plane::toString)
		.method("set", &Plane::set)
		.method("setComponents", &Plane::setComponents)
		.method("setFromNormalAndCoplanarPoint", &Plane::setFromNormalAndCoplanarPoint)
		.method("setFromCoplanarPoints", &Plane::setFromCoplanarPoints)
		.method("clone", &Plane::clone)
		.method("copy", &Plane::copy)
		.method("normalizeLocal", &Plane::normalizeLocal)
		.method("negateLocal", &Plane::negateLocal)
		.method("distanceToPoint", &Plane::distanceToPoint)
		.method("distanceToPointSigned", &Plane::distanceToPointSigned)
		.method("intersectsLine", &Plane::intersectsLine)
		.method("intersectsPlane", &Plane::intersectsPlane)
		.method("coplanarPoint", &Plane::coplanarPoint)
		.method("applyMatrix4Local", &Plane::applyMatrix4Local)
		.method("translateLocal", &Plane::translateLocal)
		.method("equals", &Plane::equals);

	registration::class_<Quat>("Quat")
		.constructor<>()(policy::ctor::as_object)
		.constructor<const Quaternion&>();

	registration::class_<Radius>("Radius")
		.constructor<>()(policy::ctor::as_object)
		.property("tl", &Radius::tl)
		.property("tr", &Radius::tr)
		.property("bl", &Radius::bl)
		.property("br", &Radius::br)
		.method("setAll", &Radius::setAll);

	registration::class_<Spherical>("Spherical")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Spherical(*)(float, float, float)>(&mkSpherical))
		.property("radius", &Spherical::radius)
		.property("phi", &Spherical::phi)
		.property("theta", &Spherical::theta)
		.method("toString", &Spherical::toString)
		.method("set", &Spherical::set)
		.method("clone", &Spherical::clone)
		.method("copy", &Spherical::copy)
		.method("setFromVector3", &Spherical::setFromVector3)
		.method("setFromCartesianCoords", &Spherical::setFromCartesianCoords)
		.method("toVec3", &Spherical::toVec3)
		.method("equals", &Spherical::equals);

	registration::class_<Vec4>("Vec4")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Vec4(*)(float, float, float, float)>(&mkVec4))
		.property("x", &Vec4::x)
		.property("y", &Vec4::y)
		.property("z", &Vec4::z)
		.property("w", &Vec4::w)
		.method("toString", &Vec4::toString)
		.method("set", &Vec4::set)
		.method("setScalar", &Vec4::setScalar)
		.method("clone", &Vec4::clone)
		.method("copy", &Vec4::copy)
		.method("addLocal", &Vec4::addLocal)
		.method("addScalarLocal", &Vec4::addScalarLocal)
		.method("addVectorsLocal", &Vec4::addVectorsLocal)
		.method("subLocal", &Vec4::subLocal)
		.method("subScalarLocal", &Vec4::subScalarLocal)
		.method("subVectorsLocal", &Vec4::subVectorsLocal)
		.method("multiplyScalarLocal", &Vec4::multiplyScalarLocal)
		.method("divideScalarLocal", &Vec4::divideScalarLocal)
		.method("negateLocal", &Vec4::negateLocal)
		.method("dot", &Vec4::dot)
		.method("lengthSq", &Vec4::lengthSq)
		.method("length", &Vec4::length)
		.method("manhattanLength", &Vec4::manhattanLength)
		.method("normalizeLocal", &Vec4::normalizeLocal)
		.method("setLengthLocal", &Vec4::setLengthLocal)
		.method("lerpLocal", &Vec4::lerpLocal)
		.method("equals", &Vec4::equals)
		.method("fromArray", &Vec4::fromArray)
		.method("toArray", &Vec4::toArray)
		.method("applyMat3Local", &Vec4::applyMat3Local);

	registration::class_<IntVec2>("IntVec2")
		.constructor<>()(policy::ctor::as_object)
		.property("x", &IntVec2::x)
		.property("y", &IntVec2::y);

	registration::class_<Triangle>("Triangle")
		.constructor<>()(policy::ctor::as_object)
		.constructor(static_cast<Triangle(*)(const Vec3&, const Vec3&, const Vec3&)>(&mkTriangle))
		.property("a", &Triangle::a)
		.property("b", &Triangle::b)
		.property("c", &Triangle::c)
		.method("toString", &Triangle::toString)
		.method("set", &Triangle::set)
		.method("clone", &Triangle::clone)
		.method("copy", &Triangle::copy)
		.method("area", &Triangle::area)
		.method("midpoint", &Triangle::midpoint)
		.method("normal", &Triangle::normal)
		.method("plane", &Triangle::plane)
		.method("barycoordFromPoint", &Triangle::barycoordFromPoint)
		.method("containsPoint", &Triangle::containsPoint)
		.method("equals", &Triangle::equals);
}
