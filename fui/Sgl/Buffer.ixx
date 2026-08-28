module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Mat.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:Buffer;


//结构体数组，基类
export class StructArrayBase : public GcObj {
public:
	//元素数
	int size = 0;
	int capacity = 0;
	int elementSize = 1;

	~StructArrayBase() {
		void** pdata = this->getPtrData();
		if (pdata != nullptr && (*pdata) != nullptr) {
			void* data = *pdata;
			free(data);
			*pdata = nullptr;
			// self.data = null
		}
	}
	//需要继承
	virtual void** getPtrData() {
		return nullptr;
	}

	//需要继承
	virtual char* getRaw() {
		return NULL;
	}

	virtual bool equalsRaw(char* a, char* b) {
		for (int j = 0; j < elementSize; j++) {
			if (b[j] != a[j]) {
				return false;
			}
		}
		return true;
	}

	//去除重复
	virtual void distinct() {
		char* raw = getRaw();
		for (int i = 0; i < this->size; i++) {
			char* ele = raw + (i * this->elementSize);

			for (int j = this->size - 1; j >= i + 1; j++) {
				char* b = raw + (i * this->elementSize);
				if (equalsRaw(ele, b)) { //需要去掉
					// memmove()
					memmove(b, b + elementSize, (size - 1 - j) * elementSize);
					this->size--;
				}
			}
		}
	}

	virtual bool hasByRaw(char* data) {
		char* raw = this->getRaw();
		for (int i = 0; i < this->size; i++) {
			char* ele = raw + (i * this->elementSize);
			bool eq = true;
			for (int j = 0; j < this->elementSize; j++) {
				if (ele[j] != data[j]) {
					eq = false;
					break;
				}
			}
			if (eq) {
				return true;
			}
		}
		return false;
	}
	virtual char* getPtrRawAtElement(int index) {
		return getRaw() + index * elementSize;
	}
	virtual void setRawAtElement(int index, char* data) {
		char* p = getRaw() + index * elementSize;
		memcpy(p, data, elementSize);
	}
	virtual void setByPtr(int index, void* data) {
		char* p = getRaw() + index * elementSize;
		memcpy(p, data, elementSize);
	}
	virtual void appendByCount(void* data, int count) {
		expandIfNeed(count);
		memcpy(getRaw() + size * elementSize, data, count * elementSize);
		size += count;
	}
	virtual void clear() {
		size = 0;
	}
	//扩展，直到size >= toSize
	virtual void expandToSize(int toSize) {
		if (size < toSize) {
			expandIfNeed(toSize - size);
			size = toSize;
		}
	}
	virtual void expandIfNeed(int addEleSize) {
		int newSize = size + addEleSize;
		if (newSize > capacity) {
			int cap = maxInt(capacity * 2, 32);
			// printf("cap:%d, self.cap:%d, newSize:%d\n", cap, self.capacity, newSize)
			if (capacity < 1000 && cap >= newSize) {//翻倍增长
				expandCapacity(cap);
			}
			else {

				int exp = maxInt(addEleSize, 10240);
				int toCap = size + exp;
				expandCapacity(toCap);
			}
		}
	}
	virtual void expandCapacity(int needSize) {
		if (needSize > capacity) {
			// printf("expandCapacity:%d\n", needSize)
			capacity = needSize;
			void** pp = getPtrData();
			if (*pp == nullptr) {
				*pp = calloc(1, needSize * elementSize);
				return;
			}
			*pp = realloc(*pp, needSize * elementSize);
		}
	}
};

export class MatArray :public StructArrayBase {
public:
	Mat* data;

	MatArray() {
		elementSize = sizeof(Mat);
	}

	virtual void** getPtrData() {
		return (void**)(&this->data);
	}

	//需要继承
	virtual char* getRaw() {
		return (char*)this->data;
	}
	virtual Mat get(int i) {
		if (i >= this->size) {
			Mat m;
			m.identity();
			return m;
		}
		return this->data[i];
	}
	virtual bool set(int i, Mat v) {
		if (i >= this->size) {
			this->expandToSize(i + 1);
		}
		if (i < this->size) {
			this->data[i] = v;
			return true;
		}
		return false;
	}
	virtual void add(Mat v) {
		this->expandIfNeed(1);
		this->data[this->size] = v;
		this->size++;
	}
	virtual bool has(Mat v) {
		return this->hasByRaw((char*)&v);
	}
};

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
