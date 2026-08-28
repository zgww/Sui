module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:PixelReader;

import :Buffer;

//读取DEPTH_COMPONENT float类型的深度纹理
export class DepthFloatPixelsReader : public GcObj {
public:
	Ref<Buffer> buffer{ new Buffer(), this };

	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;


	float* read(int x, int y, int w, int h) {
		this->buffer->initSize(w * h * 4);

		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		glReadPixels(x, y, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, this->buffer->data);
		return (float*)this->buffer->data;
	}
};
export class RgbaPixelsReader {
public:
	Ref<Buffer> buffer{ new Buffer(), this };

	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	unsigned char* readFromColorAttachment(int attachmentIndex, int x, int y, int w, int h) {
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		return this->read(x, y, w, h);
	}
	unsigned char* read(int x, int y, int w, int h) {
		this->buffer->initSize(w * h * 4);

		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;

		//一定要注意格式要和源匹配。  
		// 此行之前会失败崩溃.因为纹理的格式不是GL_FLOAT
		// glReadPixels(x, y, w, h, GL_RGBA, GL_FLOAT, 
		//     this->buffer.data)
		glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, this->buffer->data);
		return (unsigned char*)this->buffer->data;
	}
	//上下翻转.因为glReadPixels读出来的图片原点是在左下角
	void flipY() {
		int hh = this->h / 2;
		int rowBytes = this->w * 4;

		for (int y = 0; y < hh; y++) {
			for (int x = 0; x < this->w; x++) {
				int y2 = this->h - 1 - y;
				int a = y * rowBytes + x * 4;
				int b = y2 * rowBytes + x * 4;
				for (int j = 0; j < 4; j++) {
					unsigned char acomp = this->buffer->data[a + j];
					unsigned char bcomp = this->buffer->data[b + j];
					this->buffer->data[a + j] = bcomp;
					this->buffer->data[b + j] = acomp;
				}
			}
		}
	}
};