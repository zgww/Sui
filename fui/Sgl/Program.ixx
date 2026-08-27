
module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Naga/Path.h"

export module Sgl:Program;


void deleteProgram(GLuint id) {
	//会有bug, 释放可能是在别的线程释放的。。。。。。
	glDeleteProgram(id);
}
//主类
export class Program : public GcObj {
public:
	GLuint id;
	// GLuint vsId;
	// GLuint fsId;

	std::string vsPath;
	std::string fsPath;

	~Program() {
		if (this->id) {
			//printf("hihihi hi iiii22\n");
			GLuint id = this->id;

			//确保在主线程释放
			mkTimerTimeout(CLOSURE([=]() {
				deleteProgram(id);
				}), 0);

			// this->clear()
		}
	}

	void use() {
		glUseProgram(id);
	}

	// extern void clear()

	const char* getVsPathCstr() {
		if (this->vsPath != "") {
			return this->vsPath.c_str();
		}
		return "";
	}
	const char* getFsPathCstr() {
		if (this->fsPath != "") {
			return this->fsPath.c_str();
		}
		return "";
	}

	bool compile(const char* vs, const char* fs) {


			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vs, NULL);
			glCompileShader(vertexShader);


			{
				int  success;
				char infoLog[512];
				glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
					printf("compile vertex shader error:%s\n", infoLog);
					return false;
				}
			}

			unsigned int fragmentShader;
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fs, NULL);
			glCompileShader(fragmentShader);


			{
				int  success;
				char infoLog[512];
				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
					printf("compile fragment shader error:%s\n", infoLog);
					return false;
				}
			}

			unsigned int shaderProgram;
			shaderProgram = glCreateProgram();

			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);

			{
				int  success;
				char infoLog[512];
				glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
					printf("link program error:%s\n", infoLog);
					return false;
				}
			}
			this->id = shaderProgram;
			// this->vsId = vertexShader;
			// this->fsId = fragmentShader;

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return true;
	}
	bool compileByPathCstr(const char* vsPath, const char* fsPath) {
		std::string vs = Path_readText(vsPath);
		std::string fs = Path_readText(fsPath);

		this->vsPath = (vsPath);
		this->fsPath = (fsPath);

		bool ok = this->compile(vs.c_str(), fs.c_str());
		if (!ok) {
			printf("编译shader失败. path:%s/.fs\n", vsPath);
			exit(0);
		}
		return ok;
	}

	void uniform1i(const char* key, int x) {
		int loc = glGetUniformLocation(this->id, key);
		glUniform1i(loc, x);
	}

	void uniform1f(const char* key, float x) {
		int loc = glGetUniformLocation(this->id, key);
		glUniform1f(loc, x);
	}
	void uniform2f(const char* key, float x, float y) {
		int loc = glGetUniformLocation(this->id, key);
		glUniform2f(loc, x, y);
	}
	void uniform3f(const char* key, float x, float y, float z) {
		int loc = glGetUniformLocation(this->id, key);
		glUniform3f(loc, x, y, z);
	}
	void uniform4f(const char* key, float x, float y, float z, float w) {
		int loc = glGetUniformLocation(this->id, key);
		glUniform4f(loc, x, y, z, w);
	}
	void uniformMatrix4f(const char* key, float* data) {
		this->uniformMatrix4fv(key, data, 1);
	}
	void uniformMatrix4fv(const char* key, float* data, int matrixCnt) {
		int loc = glGetUniformLocation(this->id, key);
		if (loc >= 0) {
			glUniformMatrix4fv(loc, matrixCnt, GL_FALSE, data);
		}
	}
};