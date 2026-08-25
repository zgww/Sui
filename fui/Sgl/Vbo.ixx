
module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Naga/Path.h"
#include <vector>

export module Sgl:Vbo;


void deleteBuffer(GLuint id) {
	glDeleteBuffers(1, &id);
}
//Vertex Buffer Object
export class Vbo : public GcObj {
public:
	GLuint id;

	//GL_STATIC_DRAW，GL_STATIC_READ，GL_STATIC_COPY GL_DYNAMIC_DRAW，GL_DYNAMIC_READ，GL_DYNAMIC_COPY GL_STREAM_DRAW，GL_STREAM_READ，GL_STREAM_COPY
	GLuint usage = GL_STATIC_DRAW;

	int byteSize = 0;
	//一个顶点数据有几个数
	int elementCount = 3;
	bool isFloat = true;
	bool isInt = false;
	int vaIndex = 0;// vertexAttribIndex


	int vaCount = 1; // 顶点属性细分数量。 像是mat4, 就占用4个顶点属性槽位。

	int divide = 0; // 实例化渲染要用。 如果开实例化渲染，就需要设置为非0值，一般是1，表示一个实例一份数据
	int drawInstanceCount = -1; //-1表示 自动计算。 >=0的值，表示手动指定实例数量

	//是不是索引数据
	bool isIndices = false;

	//Buffer@ buf;

	void setInstancedRender(int elementCount, int drawInstanceCount) {
		this->elementCount = elementCount;
		this->divide = 1; //启用实例渲染
		this->usage = GL_DYNAMIC_DRAW;
		this->drawInstanceCount = drawInstanceCount; //绘制实例数量
	}

	int calcInstanceCount() {
		//手动指定实例数量
		if (this->drawInstanceCount >= 0) {
			return this->drawInstanceCount;
		}
		if (this->divide > 0 && !this->isIndices) {
			if (this->isFloat || this->isInt) {
				int totalVertexCount = this->byteSize / (this->elementCount * 4);
				return totalVertexCount;
			}
		}
		return 1;
	}
	int calcIndexCount() {
		return this->byteSize / 4;
	}


	void ctor() {
		this->genBuffer();
	}
	~Vbo() {
		if (this->id) {
			GLuint id = this->id;
			//确保在主线程释放
			mkTimerTimeout(CLOSURE([=]() {
				deleteBuffer(id);
				}), 0);
		}
	}

	void bind() {
		if (this->isIndices) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, this->id);
		}
	}

	void genBuffer() {
	}
	// extern void bind();

	void setVertexAttrib() {
		this->bind();

		if (this->isFloat) {
			glVertexAttribPointer(this->vaIndex,
				this->elementCount,
				GL_FLOAT, GL_FALSE, this->elementCount * sizeof(float), (void*)0);
		}
		else if (this->isInt) {
			glVertexAttribPointer(this->vaIndex,
				this->elementCount,
				GL_INT, GL_FALSE, this->elementCount * sizeof(int), (void*)0);
		}
		else {
			printf("!!unknown VertexAttrib type\n");
		}
		if (this->divide > 0) {
			glVertexAttribDivisor(this->vaIndex, this->divide);
		}
		glEnableVertexAttribArray(this->vaIndex);
	}


	void intArrayBuffer(std::vector<float>& buf) {
		this->isInt = true;
		this->isFloat = false;
		this->arrayBufferData(buf.size(), (float*)buf.data());
	}
	void arrayBuffer(std::vector<float>& buf) {
		this->arrayBufferData(buf.size(), (float*)buf.data());
	}
	void elementBuffer(std::vector<int>& buf) {
		this->elementBufferData(buf.size(), (int*)buf.data());
	}

	void arrayBufferData(int byteSize, float* vertices) {
		this->isIndices = false;
		this->byteSize = byteSize;

		glBindBuffer(GL_ARRAY_BUFFER, this->id);

		glBufferData(
			GL_ARRAY_BUFFER,
			byteSize,
			vertices,
			this->usage
		);
	}

	//元素(索引，面)
	void elementBufferData(int byteSize, int* indices) {
		this->isIndices = true;
		this->byteSize = byteSize;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			byteSize,
			indices,
			this->usage
		);
	}

};

