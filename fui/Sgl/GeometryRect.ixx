module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:GeometryRect;

import :Geometry;
import :Buffer;


export class GeometryRect :public Geometry {
public:
	// float startX = 0
	// float startY = 0
	// float startZ = 0

	float width = 100;
	float height = 100;

	void build() {
		Ref<Buffer> buf = new Buffer();
		Ref < Buffer> normal = new Buffer();
		Ref < Buffer> uv = new Buffer();
		Ref < Buffer> face = new Buffer();


		float startX = -this->width / 2.0;
		float startY = -this->width / 2.0;
		float startZ = 0;

		buf->appendFloat3(startX, startY, startZ);
		normal->appendFloat3(0, 1, 0);
		uv->appendFloat2(0, 0);

		buf->appendFloat3(startX + this->width, startY, startZ);
		normal->appendFloat3(0, 1, 0);
		uv->appendFloat2(1, 0);

		buf->appendFloat3(startX + this->width, startY + this->height, startZ);
		normal->appendFloat3(0, 1, 0);
		uv->appendFloat2(1, 1);

		buf->appendFloat3(startX, startY + this->height, startZ);
		normal->appendFloat3(0, 1, 0);
		uv->appendFloat2(0, 1);

		face->appendInt3(0, 1, 2);
		face->appendInt3(0, 2, 3);

		this->setAttrByBuffer("position", buf, 3);
		this->setAttrByBuffer("normal", normal, 3);
		this->setAttrByBuffer("uv", uv, 2);
		this->setIboByBuffer(face);
	}
};
