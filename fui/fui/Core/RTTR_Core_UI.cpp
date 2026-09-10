#include "Canvas.h"
#include "Event.h"
#include "Image.h"
#include "TimerNode.h"
#include "View.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
	using namespace rttr;

	// Canvas：抽象基类，不注册构造函数（void* data 无法注册为 property，跳过）
	registration::class_<Canvas>("Canvas")
		.method("init", &Canvas::init)
		.method("bindWindow", &Canvas::bindWindow)
		.method("unbindWindow", &Canvas::unbindWindow)
		.method("beginFrame", &Canvas::beginFrame)
		.method("endFrame", &Canvas::endFrame)
		.method("cancelFrame", &Canvas::cancelFrame)
		.method("globalAlpha", &Canvas::globalAlpha)
		.method("stroke", &Canvas::stroke)
		.method("fill", &Canvas::fill)
		.method("strokeColorByInt32", &Canvas::strokeColorByInt32)
		.method("fillColorByInt32", &Canvas::fillColorByInt32)
		.method("fillColor", &Canvas::fillColor)
		.method("strokeColor", &Canvas::strokeColor)
		.method("strokeWidth", &Canvas::strokeWidth)
		.method("shadowColor", &Canvas::shadowColor)
		.method("shadowOffset", &Canvas::shadowOffset)
		.method("shadowBlur", &Canvas::shadowBlur)
		.method("shapeAntiAlias", &Canvas::shapeAntiAlias)
		.method("lineJoin", &Canvas::lineJoin)
		.method("lineCap", &Canvas::lineCap)
		.method("translate", &Canvas::translate)
		.method("scale", &Canvas::scale)
		.method("rotate", &Canvas::rotate)
		.method("skewX", &Canvas::skewX)
		.method("skewY", &Canvas::skewY)
		.method("transform", &Canvas::transform)
		.method("setTransform", &Canvas::setTransform)
		.method("resetTransform", &Canvas::resetTransform)
		.method("currentTransform", &Canvas::currentTransform)
		.method("save", &Canvas::save)
		.method("restore", &Canvas::restore)
		.method("reset", &Canvas::reset)
		.method("scissor", &Canvas::scissor)
		.method("intersectScissor", &Canvas::intersectScissor)
		.method("resetScissor", &Canvas::resetScissor)
		.method("beginPath", &Canvas::beginPath)
		.method("closePath", &Canvas::closePath)
		.method("moveTo", &Canvas::moveTo)
		.method("lineTo", &Canvas::lineTo)
		.method("bezierTo", &Canvas::bezierTo)
		.method("quadTo", &Canvas::quadTo)
		.method("arcTo", &Canvas::arcTo)
		.method("pathWinding", &Canvas::pathWinding)
		.method("arc", &Canvas::arc)
		.method("rect", &Canvas::rect)
		.method("roundRect", &Canvas::roundRect)
		.method("roundRectVarying", &Canvas::roundRectVarying)
		.method("ellipse", &Canvas::ellipse)
		.method("circle", &Canvas::circle)
		.method("fontBlur", &Canvas::fontBlur)
		.method("fontFace", &Canvas::fontFace)
		.method("fontSize", &Canvas::fontSize)
		.method("textLetterSpacing", &Canvas::textLetterSpacing)
		.method("texLineHeight", &Canvas::texLineHeight)
		.method("textAlign", &Canvas::textAlign)
		.method("text", &Canvas::text)
		.method("textBounds", &Canvas::textBounds)
		.method("textMetrics", &Canvas::textMetrics)
		.method("drawImage", &Canvas::drawImage)
		.method("drawImageAtRect", &Canvas::drawImageAtRect)
		.method("linearGradient", &Canvas::linearGradient)
		.method("boxGradient", &Canvas::boxGradient)
		.method("radialGradient", &Canvas::radialGradient)
		.method("imagePattern", &Canvas::imagePattern)
		.method("getInstance", &Canvas::getInstance);

	// TextMetrics：纯数据结构，值类型
	registration::class_<TextMetrics>("TextMetrics")
		.constructor<>()(policy::ctor::as_object)
		.property("ascender", &TextMetrics::ascender)
		.property("descender", &TextMetrics::descender)
		.property("lineh", &TextMetrics::lineh);

	// Event：GC 类型
	registration::class_<Event>("Event")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("name", &Event::name)
		.property("isStopPropagation", &Event::isStopPropagation)
		.method("stopPropagation", &Event::stopPropagation)
		.method("stopImmediatePropagation", &Event::stopImmediatePropagation);

	// Image：GC 类型（void* bitmap 无法注册为 property，跳过）
	registration::class_<Image>("Image")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.property("_img", &Image::_img)
		.method("size", &Image::size)
		.method("width", &Image::width)
		.method("height", &Image::height);

	// TimerNode：GC 类型（继承自 Node）
	registration::class_<TimerNode>("TimerNode")
		.constructor<>()(policy::ctor::as_raw_ptr)
		.method("getClassName", &TimerNode::getClassName);

	// ViewCallback：GC 类型（View 已在 View.cpp 注册，此处不重复）
	// 回调接口基类（全部虚方法、默认空实现，仅通过 Ref<ViewCallback> 使用），按抽象类处理不注册构造函数；
	// 且该类仅含 vptr（8 字节），RTTR 会走小对象变体路径的 placement new，与 GcObj 类作用域 operator new 冲突
	registration::class_<ViewCallback>("ViewCallback")
		.method("cbLayout", &ViewCallback::cbLayout)
		.method("cbDraw", &ViewCallback::cbDraw)
		.method("cbDrawSelf", &ViewCallback::cbDrawSelf)
		.method("afterDrawSelf", &ViewCallback::afterDrawSelf);
}
