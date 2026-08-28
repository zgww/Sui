module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:Buffer;


//内存里的区域
export class Buffer : public GcObj {
public:
	unsigned char* data = nullptr;
	int size = 0;
	int capacity = 0;
	~Buffer() {
		if (data) {
			free(data);
			data = nullptr;
		}
	}

	// float *floatView(){
	//     return (float*)this->data;
	// }
	void initSize(int size) {
		this->expandCapacity(size);
		this->size = size;
	}

	std::string toFloatString() {
		std::string ret = ("");
		float* tmp = (float*)this->data;
		int l = this->floatSize();
		for (int i = 0; i < l; i++) {
			ret = ret + std::to_string(tmp[i]) + " ";
			//ret.addf(tmp[i]).add(" ");
		}
		return ret;
	}
	std::string toIntString() {
		std::string ret = ("");
		int* tmp = (int*)this->data;
		int l = this->intSize();
		for (int i = 0; i < l; i++) {
			ret = ret + std::to_string(tmp[i]) + " ";
			//ret.addi(tmp[i]).add(" ");
		}
		return ret;
	}
	int doubleSize() {
		return this->size / sizeof(double);
	}
	int floatSize() {
		return this->size / sizeof(float);
	}

	int intSize() {
		return this->size / sizeof(int);
	}

	Buffer* appendBuffer(Buffer* buf) {
		if (buf->data) {
			this->append(buf->data, buf->size);
		}
		return this;
	}

	Buffer* appendChars(char* data, int size) {
		this->append((unsigned char*)data, size);
		return this;
	}
	Buffer* append(unsigned char* data, int size) {
		this->expandIfNeed(size);
		memcpy(this->data + this->size, data, size);
		this->size += size;
		return this;
	}
	Buffer* appendFloat(float v) {
		this->expandIfNeed(4);
		float* p = (float*)(this->data + this->size);
		*p = v;
		this->size += 4;
		return this;
	}
	Buffer* appendFloat4(float a, float b, float c, float d) {
		this->expandIfNeed(16);
		float* p = (float*)(this->data + this->size);
		*p = a;
		*(p + 1) = b;
		*(p + 2) = c;
		*(p + 3) = d;
		this->size += 16;
		return this;
	}
	Buffer* appendVec3(Vec3 v3) {
		this->expandIfNeed(12);
		float* p = (float*)(this->data + this->size);
		*p = v3.x;
		*(p + 1) = v3.y;
		*(p + 2) = v3.z;
		this->size += 12;
		return this;
	}
	Buffer* appendFloat3(float a, float b, float c) {
		this->expandIfNeed(12);
		float* p = (float*)(this->data + this->size);
		*p = a;
		*(p + 1) = b;
		*(p + 2) = c;
		this->size += 12;
		return this;
	}
	Buffer* appendFloat2(float v, float b) {
		this->expandIfNeed(8);
		float* p = (float*)(this->data + this->size);
		*p = v;
		*(p + 1) = b;
		this->size += 8;
		return this;
	}
	Buffer* appendFloats(float* data, int floatCount) {
		this->append((unsigned char*)data, floatCount * 4);
		return this;
	}
	Buffer* appendCstr(char* str) {
		int len = strlen(str);
		this->expandIfNeed(len + 1);//含最后的'\0'. 但是'\0'不计入数量
		memcpy(this->data + this->size, str, len + 1);
		this->size += len;
		return this;
	}
	Buffer* appendInt(int v) {
		this->expandIfNeed(4);
		int* p = (int*)(this->data + this->size);
		*p = v;
		this->size += 4;
		return this;
	}
	Buffer* appendInt3(int a, int b, int c) {
		this->expandIfNeed(12);
		int* p = (int*)(this->data + this->size);
		*p = a;
		*(p + 1) = b;
		*(p + 2) = c;
		this->size += 12;
		return this;
	}
	Buffer* appendInts(int* data, int intCount) {
		this->append((unsigned char*)data, intCount * 4);
		return this;
	}

	void clear() {
		this->size = 0;
	}
	void pop(int count) {
		this->size = maxInt(this->size - count, 0);
	}

	//左闭右开
	bool removeRange(int fromIndex, int to) {
		if (fromIndex < 0) {
			return false;
		}
		if (to > this->size) {
			return false;
		}
		int cnt = to - fromIndex;
		if (cnt == this->size) {
			this->size = 0;
			return true;
		}

		memmove(this->data + fromIndex, this->data + to, this->size - to);

		this->size -= cnt;
		return true;
	}


	void expandIfNeed(int addByteSize) {
		int newSize = this->size + addByteSize;
		if (newSize > this->capacity) {
			int cap = this->capacity * 2;
			if (cap < 10000 && cap >= newSize) {//翻倍增长
				this->expandCapacity(cap);
			}
			else {
				this->expandCapacity(newSize);
			}
		}
	}


	void expandCapacity(int needSize) {
		this->capacity = needSize;
		if (this->data == nullptr) {
			this->data = (unsigned char*)calloc(1, needSize);
			return;
		}
		this->data = (unsigned char*)realloc(this->data, needSize);
	}
};
