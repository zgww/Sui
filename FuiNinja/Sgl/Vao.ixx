module;
#include "Urgc/UrgcIndex.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"

export module Sgl:Vao;


import :Geometry;
import :Material;

void deleteVertexArray(GLuint id) {
	glDeleteVertexArrays(1, &id);
}
export class Vao : public GcObj {
public:
	//此vao为此材质和geometry服务
	Ref<Material> material{ nullptr, this };
	Ref<Geometry> geometry{ nullptr, this };

	GLuint id = 0;

	// void ctor(){
		// this->gen()
	// }

	int geometryVersion = 0;

	void regen() {
		if (this->id) {
			deleteVertexArray(this->id);
		}
		this->gen();
	}
	~Vao() {
		if (this->id) {
			GLuint id = this->id;
			//确保在主线程释放
			mkTimerTimeout(CLOSURE(
				[=]() {
					deleteVertexArray(id);
				}
			), 0);
		}
	}

	bool isNeedBuild(
		Geometry* geometry,
		Material* material
	) {
		return material && geometry
			&& ( //关联不一样，也需要重建
				this->material != material
				|| this->geometry != geometry
				|| geometry->version != this->geometryVersion //版本有变化，说明需要更新
				);
	}
	bool build(
		Geometry* geometry,
		Material* material
	) {
		if (this->isNeedBuild(geometry, material)) {
			this->regen();//重新生成id

			this->material = material;
			this->geometry = geometry;
			this->material->program->use();

			this->bind();
			bool ok = geometry->bindVertexAttribs(material);

			if (geometry->ibo) {
				geometry->ibo->bind();
			}

			this->geometryVersion = geometry->version;

			this->unbind();

			return ok;
		}
		return true;
	}

	void gen() {
		glGenVertexArrays(1, &this->id);
	}

	void bind() {
		glBindVertexArray(this->id);
	}
	void unbind() {
		glBindVertexArray(0);
	}

	void draw(
		Geometry* geometry,
		Material* matl
	) {
		if (geometry == nullptr || geometry->ibo == nullptr) {
			return;
		}
		this->build(geometry, matl);

		this->material->program->use();

		this->bind();

		this->material->prepareDraw();
		this->material->updateUniforms();

		// this->doDraw()


		   //实例化渲染
		if (geometry->instanceVbo) {
			this->drawInstanced(geometry, matl);
			// glDrawElementsInstanced(
			//     GL_TRIANGLES, 
			//     indexCount, 
			//     GL_UNSIGNED_INT, 
			//     0,
			//     instanceCount);
		}
		else {
			int indexCount = geometry->ibo->calcIndexCount();
			glDrawElements(GL_TRIANGLES,
				indexCount, GL_UNSIGNED_INT, 0);
		}

		this->material->endDraw();

		this->unbind();
	}
	void drawInstanced(
		Geometry* geometry,
		Material* matl
	) {
		int instanceCount = geometry->instanceVbo->calcInstanceCount();
		if (instanceCount > 0) {
			int indexCount = geometry->ibo->calcIndexCount();
			glDrawElementsInstanced(
				GL_TRIANGLES,
				indexCount,
				GL_UNSIGNED_INT,
				0,
				instanceCount);
		}
	}
	// extern void doDraw()
};
