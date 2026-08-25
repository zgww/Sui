module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Vec2.h"
#include "Core/Canvas.h"
#include "Core/Image.h"
#include "Naga/Path.h"

#define NANOVG_GL3
#include "nanovg/nanovg_gl.h"

#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "nanovg/stb_image.h"

#include <vector>

export module Sgl:Tex2d;





void deleteTexture(GLuint id) {
	glDeleteTextures(1, &id);
}
int __nvglCreateImageFromTexId(
	int texId, int w, int h, bool flipY) {
	NVGcontext* vg = (NVGcontext*)Canvas::getInstance()->data;

	int imgId = nvglCreateImageFromHandleGL3(
		vg, texId, w, h,
		NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY | NVG_IMAGE_FLIPY
	);
	return imgId;
}





export class Tex2d : public GcObj {
public:
	GLuint id;

	GLuint wrapS = GL_REPEAT;
	GLuint wrapT = GL_REPEAT;
	GLuint minFilter = GL_LINEAR;//;GL_NEAREST;//GL_TEXTURE_MIN_FILTER;
	GLuint magFilter = GL_LINEAR;//GL_TEXTURE_MIN_FILTER;

	int width = 0;
	int height = 0;
	int format = 4;//GL_RGB|GL_RGBA|GL_RED
	int channelCount = 4;

	//路径。 可能有，也可能没有
	//有的话，才能序列化.
	std::string path = nullptr;

	void setWrapClampToEdge() {
		this->wrapS = GL_CLAMP_TO_EDGE;
		this->wrapT = GL_CLAMP_TO_EDGE;
	}
	void setWrapClampToBorder(int color) {
		this->wrapS = GL_CLAMP_TO_BORDER;
		this->wrapT = GL_CLAMP_TO_BORDER;

		this->bind();
		Rgbaf c = mkRgbafByInt(color);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (float*)&c);
	}

	Tex2d() {
		this->gen();
		this->updateParameters();
	}
	~Tex2d() {
		printf("Tex2d.~dtor. this:%p\n", this);
		if (this->id) {
			GLuint id = this->id;
			//确保在主线程释放
			mkTimerTimeout(CLOSURE([=]() {
				deleteTexture(id);
				}), 0);
		}
	}
	Vec2 Size() {
		return mkVec2(this->width, this->height);
	}

	void updateParameters() {
		this->bind();
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->magFilter);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	}

	void gen() {

		glGenTextures(1, &this->id);
	}
	void bind() {
		glBindTexture(GL_TEXTURE_2D, this->id);
	}
	void unbind() {

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void active(int offset) {
		glActiveTexture(GL_TEXTURE0 + offset);
	}
	void generateMipmap() {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	//分配显存，，并填充像素
	void image2dRgba(unsigned char* buf, int w, int h) {
		this->bind();

		this->width = w;
		this->height = h;
		this->format = GL_RGBA;
		this->channelCount = 4;

		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RGBA,
			w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	}
	//分配显存，，并填充像素
	void image2dRgb(unsigned char* buf, int w, int h) {
		this->bind();

		this->width = w;
		this->height = h;
		this->format = GL_RGB;
		this->channelCount = 3;

		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RGB,
			w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
	}

	//分配显存，，并填充像素.只有8位红色
	void image2dRed8(unsigned char* buf, int w, int h) {
		this->bind();

		this->width = w;
		this->height = h;
		this->format = GL_RED;
		this->channelCount = 1;

		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RED,
			w, h, 0, GL_RED,
			GL_UNSIGNED_BYTE, buf);
	}

	//分配显存,但没有填充
	void initZerosRgb(int w, int h) {
		this->bind();
		this->updateParameters();
		this->image2dRgb(nullptr, w, h);
	}
	void initZerosRed8(int w, int h) {
		this->bind();
		this->updateParameters();
		this->image2dRed8(nullptr, w, h);
	}
	//分配显存,但没有填充
	void initZerosRgba(int w, int h) {
		this->bind();
		this->updateParameters();
		this->image2dRgba(nullptr, w, h);
	}
	//初始化，作为fbo的深度附件
	void initForDepthAttachment(int w, int h) {
		this->bind();

		this->width = w;
		this->height = h;
		this->format = GL_DEPTH_COMPONENT;
		this->channelCount = 4;

		// this->updateParameters(this);

		glTexImage2D(
			GL_TEXTURE_2D, 0,
			GL_DEPTH_COMPONENT, w, h, 0,
			GL_DEPTH_COMPONENT, GL_FLOAT, NULL
		);
	}
	//初始化，作为fbo的stencil附件
	void initForStencilAttachment(int w, int h) {
		this->bind();

		this->width = w;
		this->height = h;
		this->format = GL_STENCIL_INDEX;
		this->channelCount = 4;

		glTexImage2D(
			GL_TEXTURE_2D, 0,
			GL_STENCIL_INDEX, w, h, 0,
			GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL
		);
	}
	void initForDepth32fStencil8Attachment(int w, int h) {
		this->bind();

		this->width = w;
		this->height = h;
		this->format = GL_DEPTH32F_STENCIL8;
		this->channelCount = 4;

		glTexImage2D(
			GL_TEXTURE_2D, 0,
			GL_DEPTH32F_STENCIL8, w, h, 0,
			GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL
		);
	}
	void initForDepth24Stencil8Attachment(int w, int h) {
		this->bind();

		this->width = w;
		this->height = h;
		this->format = GL_DEPTH24_STENCIL8;
		this->channelCount = 4;

		glTexImage2D(
			GL_TEXTURE_2D, 0,
			GL_DEPTH24_STENCIL8, w, h, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
		);
	}

	bool loadImageByPathCstr(const char* path) {
		int width = 0;
		int height = 0;
		int channel = 0;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path, &width, &height, &channel, 0);
		if (data) {
			printf("load image. data:%p,  width:%d, height:%d, ch:%d\n", data, width, height, channel);

			if (channel == 4) {
				// this->active(0)
				this->bind();
					this->updateParameters();
				this->image2dRgba(data, width, height);
				this->unbind();
			}
			else if ( channel == 3) {
				// this->active(0)
				this->bind();
				this->updateParameters();
				this->image2dRgb(data, width, height);
				this->unbind();
			}
			stbi_image_free(data);
			this->path = (path);
			return true;
		}
		printf("\n\t\t加载纹理失败。 path:%s\n\n", path);
		return false;
	}

};

Ref<Tex2d> mkTex2dByPathCstr(const char* path) {
	auto r = Ref(new Tex2d());
	r->loadImageByPathCstr(path);
	return r;
}

Ref<Image> loadImageByTex2d(Tex2d* tex) {
	static Ref<GcMap<Image>> imageMap = nullptr;
	if (!imageMap) {
		imageMap = new GcMap<Image>();
	}

	char key[128];
	sprintf(key, "%d", tex->id);
	// std::string key = str("").addi(tex.id)
	auto  ret = imageMap->get(key);
	if (ret) {
		return ret;
	}

	int imgId = __nvglCreateImageFromTexId(tex->id, tex->width, tex->height, true);

	{
		auto ret = Ref(new Image());
		ret->_img = imgId;
		ret->data = tex;
		imageMap->set(key, ret);
		printf("tex2d image map size:%d\n", imageMap->size());
		return ret;
	}
}
