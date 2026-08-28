module;
#include "Urgc/UrgcIndex.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Vec2.h"

export module Sgl:Fbo;

import :Tex2d;


// Frame Buffer Object
// 用来做离屏渲染。渲染到纹理的

// fbo可以管理离屏渲染所需要的 目标纹理、、深度缓冲区、、模板缓冲区等
// 用法:

// this->fbo = new Fbo()
// this->fbo.bind()
// {//创建附件
//     颜色附件
//     Ref<Tex2d> colorTex = new Tex2d()
//     colorTex.initZerosRgba(800, 600)
//     this->fbo.attachColorTex2d(colorTex, 0)

//     fboTex = colorTex.id;

//     深度和模板附件
//     Ref<Rbo> rbo = new Rbo()
//     rbo.storageAs_DEPTH24_STENCIL8(800, 600)
//     this->fbo.attachRenderBuffer_asDepthStencil(rbo)
//     printf("FBO status:%d\n", this->fbo.isStatusComplete())
// }
// this->fbo.unbind()



void deleteFrameBuffer(GLuint id) {
	glDeleteFramebuffers(1, &id);
}
void deleteRenderBuffer(GLuint id) {
	glDeleteRenderbuffers(1, &id);
}


// Render buffer object. 专用于fbo.的附件缓冲区，特别：能被着色器
export struct Rbo {
	GLuint id;

	Rbo() {
		gen();
	}
	~Rbo() {
		printf("~Rbo.dtor\n");
		if (id) {
			GLuint id = this->id;
			//确保在主线程释放
			mkTimerTimeout(CLOSURE(
				[=]() {
					deleteRenderBuffer(id);
				}
			), 0);
		}
	}
	void gen() {
		glGenRenderbuffers(1, &this->id);
	}
	void bind() {
		glBindRenderbuffer(GL_RENDERBUFFER, this->id);
	}
	void unbind() {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	void storageAs_DEPTH24_STENCIL8(int w, int h) {
		this->bind();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
	}
};

export class Fbo : public GcObj {
public:
	GLuint id;
	Ref<Tex2d> tex2d{ nullptr, this };
	Ref<Tex2d> depthTex2d{ nullptr, this };
	Ref<Tex2d> stencilTex2d{ nullptr, this };
	Ref<Rbo> depthStencilRbo{ nullptr, this };

	Fbo() {
		gen();
	}
	~Fbo() {
		printf("~Fbo.dtor. %p, %p\n\n", this->tex2d.get(), this->depthTex2d.get());
		if (this->id) {
			GLuint id = this->id;
			//确保在主线程释放
			mkTimerTimeout(CLOSURE(
				[=]() {
					deleteFrameBuffer(id);
				}
			), 0);
		}
	}
	Vec2 getSize() {
		if (this->tex2d) {
			return mkVec2(this->tex2d->width, this->tex2d->height);
		}
		if (this->depthTex2d) {
			return mkVec2(this->depthTex2d->width, this->depthTex2d->height);
		}
		return mkVec2(0, 0);
	}
	void gen() {
		glGenFramebuffers(1, &this->id);
	}
	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, this->id);
	}
	void unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	// fbo是否完整 
	// 附加至少一个缓冲（颜色、深度或模板缓冲）。
	// 至少有一个颜色附件(Attachment)。
	// 所有的附件都必须是完整的（保留了内存）。
	// 每个缓冲都应该有相同的样本数(sample)。
	bool isStatusComplete() {
		auto v = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		bool ok = v == GL_FRAMEBUFFER_COMPLETE;
		return ok;
	}
	int checkStatus() {
		auto v = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		return (int)v;
	}
	const char* statusDesc() {
		auto v = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (v == GL_FRAMEBUFFER_COMPLETE) {
			return "complete";
		}
		if (v == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
			return "incomplete_attachment";
		}
		if (v == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
			return "incomplete_missing_attachment";
		}
		if (v == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER) {
			return "incomplete_draw_buffer";
		}
		if (v == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER) {
			return "incomplete_read_buffer";
		}
		if (v == GL_FRAMEBUFFER_UNSUPPORTED) {
			return "unsupported";
		}
		return "unknown";
	}

	void startDraw(float r, float g, float b, float a, bool clearColor,
		bool clearDepth, bool clearStencil) {
		this->bind();
		auto s = this->getSize();
		int w = s.x;
		int h = s.y;
		glViewport(0, 0, w, h);

		glClearColor(r, g, b, a);

		unsigned int bit = 0;
		if (clearColor) {
			bit |= GL_COLOR_BUFFER_BIT;
		}
		if (clearDepth) {
			bit |= GL_DEPTH_BUFFER_BIT;
		}
		if (clearStencil) {
			bit |= GL_STENCIL_BUFFER_BIT;
		}
		glDisable(GL_SCISSOR_TEST);

		// glClearDepth(0.5);

		glClear(bit);
	}
	void endDraw() {
		this->unbind();
	}

	void setGlDrawBufferNone() {
		glDrawBuffer(GL_NONE);
	}
	void setGlReadBufferNone() {
		glReadBuffer(GL_NONE);
	}

	void setGlDrawBufferDefault() {
		glDrawBuffer(GL_BACK);
	}
	void setGlReadBufferDefault() {
		glReadBuffer(GL_BACK);
	}


	void attachColorTex2d(Tex2d* tex2d, int colorAttachmentIndex) {
		this->tex2d = tex2d;
		this->_attachColorTex2d(tex2d, colorAttachmentIndex);
	}
	void attachDepthTex2d(Tex2d* tex2d) {
		this->depthTex2d = tex2d;
		this->_attachDepthTex2d(tex2d);

	}
	void attachStencilTex2d(Tex2d* tex2d) {
		this->stencilTex2d = tex2d;
		this->_attachStencilTex2d(tex2d);
	}

	void attachRenderBuffer_asDepthStencil(Rbo* rbo) {
		this->depthStencilRbo = rbo;
		this->_attachRenderBuffer_asDepthStencil(rbo);
	}

	//附加目标纹理
	//[colorAttachmentIndex] 是相对于GL_COLOR_ATTACHMENT0的偏移
	void _attachColorTex2d(Tex2d* tex2d, int colorAttachmentIndex) {
		// target：帧缓冲的目标（绘制、读取或者两者皆有）
		// attachment：我们想要附加的附件类型。当前我们正在附加一个颜色附件。注意最后的0意味着我们可以附加多个颜色附件。我们将在之后的教程中提到。
		// textarget：你希望附加的纹理类型
		// texture：要附加的纹理本身
		// level：多级渐远纹理的级别。我们将它保留为0。
		this->bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachmentIndex, GL_TEXTURE_2D,
			tex2d->id,
			0);
		bool ok = this->isStatusComplete();
	}
	void _attachDepthTex2d(Tex2d* tex2d) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
			tex2d->id,
			0);
	}
	void _attachDepthStencilTex2d(Tex2d* tex2d) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
			tex2d->id,
			0);
	}
	void _attachStencilTex2d(Tex2d* tex2d) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
			tex2d->id,
			0);
	}
	void _attachRenderBuffer_asDepthStencil(Rbo* rbo) {
		this->bind();
		glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER, rbo->id);
	}

	void buildWithColorDepth32fStencil8Texture(int w, int h, bool colorTex, bool depthStencilTex) {
		this->bind();
		if (colorTex) {
			Ref<Tex2d> c = new Tex2d();
			c->initZerosRgba(w, h);
			this->attachColorTex2d(c, 0);
		}
		if (depthStencilTex) {
			Ref<Tex2d> c = new Tex2d();
			c->initForDepth32fStencil8Attachment(w, h);
			this->_attachDepthStencilTex2d(c);
			this->depthTex2d = c;
		}
		printf("FBO status:%d. %s %x\n", this->isStatusComplete(), this->statusDesc(), this->checkStatus());
		this->unbind();
	}
	void buildWithColorDepth24Stencil8Texture(int w, int h, bool colorTex, bool depthStencilTex) {
		this->bind();
		if (colorTex) {
			Ref<Tex2d> c = new Tex2d();
			c->initZerosRgba(w, h);
			this->attachColorTex2d(c, 0);
		}
		if (depthStencilTex) {
			Ref<Tex2d> c = new Tex2d();
			c->initForDepth24Stencil8Attachment(w, h);
			this->_attachDepthStencilTex2d(c);
			this->depthTex2d = c;
		}
		printf("FBO status:%d. %s %x\n", this->isStatusComplete(), this->statusDesc(), this->checkStatus());
		this->unbind();
	}
	//注意没办法同时挂载depth/stencil. 如果想同时挂载，请用Depth24Stencil8
	void buildWithColorDepthStencilTexture(int w, int h, bool colorTex, bool depthTex, bool stencilTex) {
		this->bind();
		if (colorTex) {
			Ref<Tex2d> c = new Tex2d();
			c->initZerosRgba(w, h);
			this->attachColorTex2d(c, 0);
		}
		if (depthTex) {
			Ref<Tex2d> c = new Tex2d();
			c->setWrapClampToEdge();
			c->updateParameters();
			c->initForDepthAttachment(w, h);
			this->attachDepthTex2d(c);
		}
		if (stencilTex) {
			Ref<Tex2d> c = new Tex2d();
			c->initForStencilAttachment(w, h);
			this->attachStencilTex2d(c);
			this->stencilTex2d = c;
		}
		printf("FBO status:%d. %s %x\n", this->isStatusComplete(), this->statusDesc(), this->checkStatus());
		this->unbind();
	}

	void buildWithColorDepthStencil(int w, int h) {
		this->bind();

		Ref<Tex2d> colorTex = new Tex2d();
		colorTex->initZerosRgba(w, h);
		this->attachColorTex2d(colorTex, 0);

		Ref<Rbo> rbo = new Rbo();
		rbo->storageAs_DEPTH24_STENCIL8(w, h);
		this->attachRenderBuffer_asDepthStencil(rbo);
		printf("FBO status:%d, %s\n", this->isStatusComplete(), this->statusDesc());

		this->unbind();

	}
};

