module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Core/Mat.h"
#include "Naga/Path.h"
#include "Naga/StrUtil.h"

export module Sgl:Material;

import :Tex2d;
import :Program;

export class UniformMeta : public GcObj {
public:
	std::string name = ("");
	std::string type = ("");
	std::string editor = ("");
	std::string defaultValue = ("");
};


export class UniformInfo: public GcObj {
public:
	std::string key = ("");

	// int location;

	//0:unknown 1:mat, 2:intValues, 3: floatValues, 4:tex, 5:matArray, 6:color4f
	int kind = -1;

	//intValues|floatValues的个数
	int count = 1;
	Mat mat;
	int intValues[16];
	float floatValues[16];
	int texIndex = 0;// glActiveTexture的索引

	Ref<Tex2d> tex{ nullptr, this };
	std::string texPath; //纹理是没办法序列化的

	//MatArray@ matArray;

		// void insp(Insp* insp){
			// insp.cbInsp = ^void(Insp*insp, Node* o){
			//     if this->kind == 4 {
			//     }
			// }
		// }
	//    void inspAsValue(Insp * insp, Node * o, Material * matl) {

	//    layoutLinear(o, (long long)this).{
	//        // const char *dir = this->queryAttrDirection(mf)
	//        o.border.b.set(1, 0x13000000)
	//            o.row()

	//            insp.mkFieldName(o, this->key.str)
	//            // if this->kind ==

	//            // Rgabf *color = 
	//            // insp.inspRgbaf(o, this, )
	//            if this->kind == 6{
	//                mkColorPicker(o, 0).{
	//                    o.backgroundColor = mkRgbafByFloat4(this->floatValues).toInt()
	//                        o.onChanged = ^ void(int newcolor) {
	//                        Rgbaf nv = mkRgbafByInt(newcolor)
	//                            // this->setAttr(mf, mkStructObj(metaStructOf(Rgbaf), &nv))
	//                    }
	//                }
	//            }
	//            else if this->kind == 3 {
	//                // insp.mkFieldName(o, "floats")
	//                if this->count == 2 {
	//                    Vec2 v = mkVec2(
	//                        this->floatValues[0],
	//                        this->floatValues[1], )
	//                        Insp_mkVec2(o, 0, v, ^ void(Vec2 nv) {});
	//                }
	//                else if this->count == 3 {
	//                    Vec3 v = mkVec3(
	//                        this->floatValues[0],
	//                        this->floatValues[1],
	//                        this->floatValues[2],
	//                        )
	//                        Insp_mkVec3(o, 0, v, ^ void(Vec3 nv) {});
	//                }
	//                else if this->count == 4 {
	//                    Vec4 v = mkVec4(
	//                        this->floatValues[0],
	//                        this->floatValues[1],
	//                        this->floatValues[2],
	//                        this->floatValues[3],
	//                        )
	//                        Insp_mkVec4(o, 0, v, ^ void(Vec4 nv) {});
	//                }
	//            }
	//            else if this->kind == 4 {
	//                std::string path = Path_resolveRelativeFromFile(this->texPath.str, matl.path.str)
	//                    mkImageView(o, 0).{
	//                    o.width = 100
	//                        o.height = 100
	//                        o.setImageMode(WrapContent)
	//                        o.border.setAll(1, 0xff999999)
	//                        o.setSrc(path)
	//                        o.cursor.set("pointer")
	//                        o.cbOnEvent = ^ void(Event * e) {
	//                        if e instanceof MouseEvent {
	//                            MouseEvent* me = (MouseEvent*)e;
	//                            if me.button == 1 && me.isClickInBubble() {
	//                                // Toast_make(("click image").addString(path).str)
	//                                std::string tmppath = FileDialog_getFirstOpenFileName(".", "选择图片")
	//                                    if tmppath {
	//                                        std::string base = Path_toAbsolute(matl.path.str)
	//                                            std::string rel = Path_relPathToFile(tmppath.str, base.str)
	//                                            printf("path:%s. rel:%s\n", tmppath.str, rel.str)

	//                                            matl.setUniformTex2dByPath(this->key.str, tmppath.str)
	//                                    }
	//                                // FileChooser@ fc = new FileChooser()
	//                                // fc.use_filterImage()
	//                                // fc.loadPaths()
	//                                // fc.onChoose = ^ void(std::string newpath){
	//                                //     insp.setAttr(mf, newpath)
	//                                // }
	//                                // fc.showWindow()
	//                            }
	//                        }
	//                    }
	//                }
	//                mkTextView(o, 0).{
	//                    o.setText(this->texPath)
	//                }
	//            }
	//    }
	//}


	//void fromJson(Json* jo) {
	//    this->key = jo.getString("key")

	//        jo.getToInt("kind", &this->kind)
	//        jo.getToInt("count", &this->count)

	//        if this->kind == 2 {
	//            jo.getToInts("intValues", this->intValues, this->count)
	//        }
	//    if this->kind == 3 {
	//        jo.getToFloats("floatValues", this->floatValues, this->count)
	//    }
	//    if this->kind == 6 {
	//        jo.getToFloats("floatValues", this->floatValues, this->count)
	//    }

	//    // jo.getToInt("texIndex", &this->texIndex)
	//    this->texPath = jo.getString("texPath")
	//}
	//void toJson(Json* jo) {
	//    jo.putString("key", this->key)
	//        jo.putNumber("kind", this->kind)
	//        jo.putNumber("count", this->count)
	//        if this->kind == 2 {
	//            jo.put("intValues", Json_toJsonNumberArrayByInts(this->intValues, this->count))
	//        }
	//    if this->kind == 3 {
	//        jo.put("floatValues", Json_toJsonNumberArrayByFloats(this->floatValues, this->count))
	//    }
	//    if this->kind == 6 {
	//        jo.put("floatValues", Json_toJsonNumberArrayByFloats(this->floatValues, this->count))
	//    }
	//    // jo.putNumber("texIndex", this->texIndex)
	//    if this->texPath{
	//        jo.putString("texPath", this->texPath)
	//    }
	//}

	Rgba getColor() {
		if (this->kind == 3) {
			Rgba c = mkRgbaByFloat(
				this->floatValues[0],
				this->floatValues[1],
				this->floatValues[2],
				this->count >= 4 ? this->floatValues[3] : 1.0
			);
			return c;
		}
		return mkRgba(0, 0, 0, 0);
	}

	bool updateUniform(Program* program) {
		if (this->key != "") {
			if (this->kind == 1) {
				// if this->mat {
				program->uniformMatrix4f(this->key.c_str(), this->mat.data);
				// }
				// else{
				//     return false
				// }
			}
			else if (this->kind == 5) {
				// if this->mat {
				//program->uniformMatrix4fv(this->key.c_str(), this->matArray.data, this->matArray.size)
					// }
					// else{
					//     return false
					// }
			}
			else if (this->kind == 2) {
				if (this->count == 1) {
					program->uniform1i(this->key.c_str(), this->intValues[0]);
				}
			}
			else if (this->kind == 3) {
				if (this->count == 1) {
					program->uniform1f(this->key.c_str(),
						this->floatValues[0]
					);
				}
				else if (this->count == 2) {
					program->uniform2f(this->key.c_str(),
						this->floatValues[0],
						this->floatValues[1]
					);
				}
				else if (this->count == 3) {
					program->uniform3f(this->key.c_str(),
						this->floatValues[0],
						this->floatValues[1],
						this->floatValues[2]
					);
				}
				else if (this->count == 4) {
					program->uniform4f(this->key.c_str(),
						this->floatValues[0],
						this->floatValues[1],
						this->floatValues[2],
						this->floatValues[3]
					);
				}
				else {
					return false;
				}
			}
			else if (this->kind == 4) {
				if (this->tex) {
					this->tex->active(this->texIndex);
					this->tex->bind(); //绑定纹理到当前的texIndex中
					program->uniform1i(this->key.c_str(), this->texIndex);
				}
				else {
					return false;
				}
			}
			else if (this->kind == 6) { // color4f
				program->uniform4f(this->key.c_str(),
					this->floatValues[0],
					this->floatValues[1],
					this->floatValues[2],
					this->floatValues[3]
				);
			}
			return true;
		}
		return false;
	}
};


// 解析shader code,得到元信息
export class ShaderMeta : public GcObj {
public:
	std::string vsPath;
	std::string vsCode;

	std::string fsPath;
	std::string fsCode;

	// <UniformMeta>
	Ref<GcList<UniformMeta>> uniformMetas{ new GcList<UniformMeta>(), this };

	UniformMeta* getUniformMeta(const char* name) {
		int l = this->uniformMetas->size();
		for (int i = 0; i < l; i++) {
			UniformMeta* um = (UniformMeta*)this->uniformMetas->get(i);
			if (um->name == name) {
				return um;
			}
		}
		return nullptr;
	}

	void parseCode(std::string code) {
		if (code == "") {
			return;
		}
		//auto lines = Str::splitToLines(code);

		//std::string editor;
		//std::string defaultValue;

		//    for (int i = 0; i < lines.size(); i++) {
		//        auto line = lines[i];
		//            // printf("line %d: %s\n", i, line.str)
		//            if (line.startsWith("//@default ")) {
		//                defaultValue = line.substringByByteStart(11).trim()
		//            }
		//            else if (line.startsWith("//@editor ")) {
		//                editor = line.substringByByteStart(10).trim()
		//            }
		//            else if (line.startsWith("uniform ")) {
		//                List@ parts = line.splitByRe("\\s+|;")
		//                    if (parts.size() >= 3) {
		//                        auto typeName = parts[1];
		//                        auto  name = parts[2];
		//                        UniformMeta* oldUm = this->getUniformMeta(name.c_str());

		//                            if (oldUm) {//旧的Uniform已经存在
		//                                // 旧的uniform的信息也全,不需要覆盖
		//                                if (oldUm->editor != "" || oldUm->defaultValue != "") {
		//                                    defaultValue = nullptr;
		//                                        editor = nullptr;
		//                                        continue;
		//                                }
		//                                // 旧的Uniform信息不全,需要删除
		//                                this->uniformMetas.remove(oldUm);
		//                                printf("\tremove old uniform: %s\n", name.c_str());
		//                            }

		//                        auto  um = Ref(new UniformMeta());
		//                            um->name = name;
		//                            um->type = typeName;
		//                            if (editor) {
		//                                um->editor = editor;
		//                            }
		//                        if (defaultValue != "") {
		//                            um->defaultValue = defaultValue;
		//                        }

		//                        this->uniformMetas->push(um);

		//                        defaultValue = nullptr;
		//                        editor = nullptr;

		//                        printf("uniform: %s, type: %s, editor:%s default: %s\n",
		//                            um.name.str,
		//                            um.type.str,
		//                            um.editor.str,
		//                            um.defaultValue.str);
		//                    }
		//            }
		//    }
	}

	void parseFsByPathCstr(const char* path) {
		this->fsPath = (path);
		std::string code = Path_readText(path);
		this->fsCode = code;
		this->parseCode(code);
	}
	void parseVsByPathCstr(const char* path) {

		this->vsPath = (path);
		std::string code = Path_readText(path);
		this->vsCode = code;
		this->parseCode(code);
	}
};


//主类
export class Material: public GcObj {
public:
	//材质文件的路径
	std::string path = ("test??.matl.json");
	Ref<Program> program{ nullptr, this };

	bool depthTest = false;
	bool depthWrite = true;
	bool transparent = false;
	bool stencilTest = false;
	bool alphaTest = false;
	bool scissorTest = false;

	bool blend = true;
	bool cullFace = false;
	bool wireframe = false; // 线框模式

	// <UniformInfo>
	// Map@ uniforms = new Map()
	Ref<GcList<UniformInfo>> uniforms{ new GcList<UniformInfo>(), this };

	// Mat@ mvp;
	// Mat@ model;
	// Mat@ ;
	Mat mvp = mkMatIdentity();

	Mat model = mkMatIdentity();
	Mat view = mkMatIdentity();
	Mat projection = mkMatIdentity();

	std::string vsPath = ("a.vs");
	std::string fsPath = ("a.fs");


	//void insp(Insp * insp) {
	//    new InspAttrFilePath().{o.bind(insp, "path", null);}
	//    new InspAttrFilePath().{o.bind(insp, "vsPath", null);}
	//    new InspAttrFilePath().{o.bind(insp, "fsPath", null);}

	//    insp.afterInsp = ^ void(Insp * insp, Node * o) {
	//        mkPanel2(o, 0).{
	//            o.title = ("uniforms")

	//                for int i = 0; i < this->uniforms.size(); i++{
	//                    UniformInfo* uinfo = (UniformInfo*)this->uniforms.get(i)
	//                        // // // mkTextView(o, i).{
	//                        // // //     o.setText(uinfo.key)
	//                        // // // }
	//                        // Insp@ curInsp = new Insp()
	//                        // // curInsp.inspObj(o, uinfo)
	//                        uinfo.inspAsValue(insp, o, this)
	//                }

	//        }
	//    }
	//}
	//void insp_hi() {
	//    Toast_make("hi")
	//}


	//预备绘制。。 需要切换开关
	void prepareDraw() {
		// glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// glEnable(GL_DEPTH_TEST);
		// glEnable(GL_STENCIL_TEST);
		// glDisable(GL_CULL_FACE);


		if (this->depthTest) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

		// glDepthMask(false);
		glDepthMask(this->depthWrite);

		if (this->blend) glEnable(GL_BLEND);
		else glDisable(GL_BLEND);


		if (this->stencilTest) glEnable(GL_STENCIL_TEST);
		else glDisable(GL_STENCIL_TEST);

		if (this->alphaTest) glEnable(GL_ALPHA_TEST);
		else glDisable(GL_ALPHA_TEST);

		if (this->scissorTest) glEnable(GL_SCISSOR_TEST);
		else glDisable(GL_SCISSOR_TEST);

		if (this->cullFace) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

		if (this->wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	void endDraw() {
		if (this->wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	//bool load(const char* path) {
	//    this->path = (path)
	//        Json@ jo = Json_parseByPathC(path)
	//        if jo {
	//            jo.toObject(this)

	//                std::string dirname = Path_dirname(path)
	//                std::string realVsPath = dirname.clone().add("/").addString(this->vsPath)
	//                std::string realFsPath = dirname.clone().add("/").addString(this->fsPath)

	//                this->buildByShaderPathC(realVsPath.str, realFsPath.str)
	//                return true
	//        }
	//    return false
	//}
	//bool saveTo(String* path) {
	//    if path&& path.notEmpty() {
	//        Json@ jo = Json_toJson(this)
	//            Path_writeText(path.str, jo.dump().str)
	//            return true
	//    }
	//    return false
	//}
	//bool save() {
	//    bool b = this->saveTo(this->path)
	//        return b
	//}

	//void fromJson(Json* jo) {
	//    std::string vsPath = jo.getString("vsPath")
	//        std::string fsPath = jo.getString("fsPath")

	//        this->vsPath = vsPath
	//        this->fsPath = fsPath

	//        // if vsPath && fsPath {
	//        //     if this->buildByShaderPathC(vsPath.str, fsPath.str){
	//        //     }
	//        // }


	//        jo.getToBool("depthTest", &this->depthTest)
	//        jo.getToBool("depthWrite", &this->depthWrite)
	//        jo.getToBool("transparent", &this->transparent)
	//        jo.getToBool("stencilTest", &this->stencilTest)
	//        jo.getToBool("alphaTest", &this->alphaTest)
	//        jo.getToBool("scissorTest", &this->scissorTest)
	//        jo.getToBool("blend", &this->blend)
	//        jo.getToBool("cullFace", &this->cullFace)
	//        jo.getToBool("wireframe", &this->wireframe)

	//        Json@ uniformsJa = jo.get("uniforms")
	//        if uniformsJa {
	//            this->uniforms = uniformsJa.toObjectsByVtable(UniformInfo)
	//        }
	//}
	//void toJson(Json* jo) {
	//    jo.putBool("depthWrite", this->depthWrite)
	//        jo.putBool("transparent", this->transparent)

	//        jo.putBool("depthTest", this->depthTest)
	//        jo.putBool("stencilTest", this->stencilTest)
	//        jo.putBool("alphaTest", this->alphaTest)
	//        jo.putBool("scissorTest", this->scissorTest)
	//        jo.putBool("blend", this->blend)
	//        jo.putBool("cullFace", this->cullFace)
	//        jo.putBool("wireframe", this->wireframe)
	//        jo.putString("vsPath", this->vsPath)
	//        jo.putString("fsPath", this->fsPath)
	//        jo.put("uniforms", Json_toJson(this->uniforms))
	//}

	void updateMvp() {
		//更新矩阵
		Mat mv;
		mv.mul(&this->view, &this->model);
		this->mvp.mul(&this->projection, &mv);
	}
	void setMvp(Mat model, Mat view, Mat projection) {
		this->model = model;
		this->view = view;
		this->projection = projection;

		//更新矩阵
		this->updateMvp();
	}

	void updateUniforms() {
		// List@ keys = this->uniforms.keys()
		int l = this->uniforms->size();
		int texIndex = 0;
		for (int i = 0; i < l; i++) {
			// String* key = (String*)keys.get(i)
			UniformInfo* ui = this->uniforms->get(i);
			if (ui->kind == 4) { // tex
				//自动更新的texIndex
				ui->texIndex = texIndex;
				texIndex++;
			}
			ui->updateUniform(this->program);
		}

		//更新矩阵
		// Mat mv;
		// mv.mul(&this->view, &this->model)
		// this->mvp.mul(&this->projection, &mv)

		this->program->uniformMatrix4f("model", this->model.data);
		this->program->uniformMatrix4f("view", this->view.data);
		this->program->uniformMatrix4f("projection", this->projection.data);
		this->program->uniformMatrix4f("mvp", this->mvp.data);
	}


	UniformInfo* getUniformInfo(const char* key) {
		int l = this->uniforms->size();
		for (int i = 0; i < l; i++) {
			UniformInfo* ui = (UniformInfo*)this->uniforms->get(i);
			if (ui->key == key) {
				return ui;
			}
		}
		return nullptr;
	}
	UniformInfo* gocUniformInfo(const char* key) {
		int l = this->uniforms->size();
		for (int i = 0; i < l; i++) {
			UniformInfo* ui = (UniformInfo*)this->uniforms->get(i);
			if (ui->key == (key)) {
				return ui;
			}
		}
		auto ret = Ref(new UniformInfo());
		ret->key = (key);
		this->uniforms->push(ret);

		return ret;
	}

	// void setLights(List* lights){
	//     // do nothing
	// }

	void setUniformTex2dByPath(const char* key, const char* path) {
		std::string base = Path_toAbsolute(this->path.c_str());
		std::string rel = Path_relPathToFile(path, base.c_str());

		auto tex = Ref(new Tex2d());
		tex->loadImageByPathCstr(path);
		UniformInfo* ui = this->setUniformTex2d(key, tex);
		ui->texPath = rel;
	}
	UniformInfo* setUniformTex2d(const char* key, Tex2d* tex) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 4;
		ui->tex = tex;
		// ui.texIndex = activeIndex
		return ui;
	}
	//void setUniformMatArray(const char* key, MatArray@ matArray) {
	//    UniformInfo* ui = this->gocUniformInfo(key);
	//    ui->kind = 5;
		//ui->matArray = matArray;
	//}
	void setUniformMat4(const char* key, Mat mat) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 1;
		ui->mat = mat;
	}
	void setUniform1i(const char* key, int v) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 2;
		ui->count = 1;
		ui->intValues[0] = v;
	}
	void setUniform1f(const char* key, float v) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 3;
		ui->count = 1;
		ui->floatValues[0] = v;
	}
	void setUniform2f(const char* key, float x, float y) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 3;
		ui->count = 2;
		ui->floatValues[0] = x;
		ui->floatValues[1] = y;
	}
	void setUniform3f(const char* key, float x, float y, float z) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 3;
		ui->count = 3;
		ui->floatValues[0] = x;
		ui->floatValues[1] = y;
		ui->floatValues[2] = z;
	}
	void setUniform4f(const char* key, float x, float y, float z, float w) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 3;
		ui->count = 4;
		ui->floatValues[0] = x;
		ui->floatValues[1] = y;
		ui->floatValues[2] = z;
		ui->floatValues[3] = w;
	}
	void setUniformRgbaf(const char* key, Rgbaf c) {
		this->setUniformColor4f(key, c.r, c.g, c.b, c.a);
	}
	void setUniformColor4f(const char* key, float x, float y, float z, float w) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 6;
		ui->count = 4;
		ui->floatValues[0] = x;
		ui->floatValues[1] = y;
		ui->floatValues[2] = z;
		ui->floatValues[3] = w;
	}
	void setUniformColor4fByInt32Color(const char* key, int color) {
		Rgbaf c = mkRgbafByInt(color);
		this->setUniformColor4f(
			key,
			c.r,
			c.g,
			c.b,
			c.a
		);
	}
	void setUniformVec2(const char* key, Vec2 v) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 3;
		ui->count = 2;
		ui->floatValues[0] = v.x;
		ui->floatValues[1] = v.y;
	}
	void setUniformVec3(const char* key, Vec3 v3) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 3;
		ui->count = 3;
		ui->floatValues[0] = v3.x;
		ui->floatValues[1] = v3.y;
		ui->floatValues[2] = v3.z;
	}
	void setUniformVec4(const char* key, Vec4 v) {
		UniformInfo* ui = this->gocUniformInfo(key);
		ui->kind = 3;
		ui->count = 4;
		ui->floatValues[0] = v.x;
		ui->floatValues[1] = v.y;
		ui->floatValues[2] = v.z;
		ui->floatValues[3] = v.w;
	}


	bool buildByShaderPathCstr(const char* vsPath, const char* fsPath) {
		this->program = new Program();
		// this->vsPath.set(vsPath)
		// this->fsPath.set(fsPath)
		bool ok = this->program->compileByPathCstr(
			vsPath,
			fsPath
			// "../asset/a.vs", 
			// "../asset/a.fs"
		);

		this->shaderMeta = new ShaderMeta();
		this->shaderMeta->parseFsByPathCstr(fsPath);
		this->shaderMeta->parseVsByPathCstr(vsPath);

		//应用默认值
		{
			int l = this->shaderMeta->uniformMetas->size();
			for (int i = 0; i < l; i++) {
				UniformMeta* um = (UniformMeta*)this->shaderMeta->uniformMetas->get(i);
				if (um->defaultValue != "") {
					UniformInfo* ui = (UniformInfo*)this->getUniformInfo(um->name.c_str());
					if (ui) { //值已经存在
						continue;
					}
					auto parts = Str::splitByRe(um->defaultValue, "\\s+");
					if (um->type == ("vec2")) {
						if (parts.size() >= 2) {
							auto s0 = parts[0];
							auto s1 = parts[1];
							float v0 = atof(s0.c_str());
							float v1 = atof(s1.c_str());
							this->setUniform2f(um->name.c_str(),
								v0, v1
							);
						}
					}
					else if (um->type == ("vec3")) {
						if (parts.size() >= 3) {
							auto s0 = parts[0];
							auto s1 = parts[1];
							auto s2 = parts[2];
							float v0 = atof(s0.c_str());
							float v1 = atof(s1.c_str());
							float v2 = atof(s2.c_str());
							this->setUniform3f(um->name.c_str(),
								v0, v1, v2
							);
						}
					}
					else if (um->type == ("vec4")) {
						if (parts.size() >= 4) {
							auto s0 = parts[0];
							auto s1 = parts[1];
							auto s2 = parts[2];
							auto s3 = parts[3];
							float v0 = atof(s0.c_str());
							float v1 = atof(s1.c_str());
							float v2 = atof(s2.c_str());
							float v3 = atof(s3.c_str());
							this->setUniform4f(um->name.c_str(),
								v0, v1, v2, v3
							);


						}
					}
				}
			}
		}

		// if ok {
		// }

		return ok;
	}

	Ref<ShaderMeta> shaderMeta{ nullptr, this };
};

