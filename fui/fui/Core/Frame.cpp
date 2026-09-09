#include "Frame.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
	using namespace rttr;

	registration::class_<Frame>("Frame")
		.constructor<>()(policy::ctor::as_object)
		.property("x", &Frame::x)
		.property("y", &Frame::y)
		.property("width", &Frame::width)
		.property("height", &Frame::height)
		.property("minWidth", &Frame::minWidth)
		.property("minHeight", &Frame::minHeight)
		.property("maxWidth", &Frame::maxWidth)
		.property("maxHeight", &Frame::maxHeight)
		.method("toString", &Frame::toString)
		.method("copy", &Frame::copy)
		.method("toRect", &Frame::toRect)
		.method("getSize", &Frame::getSize)
		.method("getBottom", &Frame::getBottom)
		.method("getRight", &Frame::getRight)
		.method("setRect", &Frame::setRect)
		.method("setPosition", &Frame::setPosition)
		.method("setSize", &Frame::setSize)
		.method("setWidth", &Frame::setWidth)
		.method("setHeight", &Frame::setHeight)
		.method("setMinWidth", &Frame::setMinWidth)
		.method("setMinHeight", &Frame::setMinHeight)
		.method("setMinConstraints", &Frame::setMinConstraints)
		.method("setMaxConstraints", &Frame::setMaxConstraints)
		.method("insetByInset", &Frame::insetByInset)
		.method("outsetByInset", &Frame::outsetByInset)
		.method("isTight", &Frame::isTight)
		.method("isLoose", &Frame::isLoose)
		.method("reset", &Frame::reset);
}
