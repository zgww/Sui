package Sgl


#include <stdio.h>
#include "./UnitOpengl.h"
#include "../Orc/Orc.h"

import * from "./Mat.orc"

import * from "./Program.orc"
import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Path.orc"
import * from "../Orc/Math.orc"
import * from "../Json/Json.orc"
import * from "../Sui/Core/Focus.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Dialog/FileDialog.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/View/Switch.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/Panel.orc"
import * from "../Sui/View/ColorPicker.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Layout/LayoutLinear.orc"

import * from "./Tex2d.orc"
import * from "./Fbo.orc"
import * from "./Draw.orc"
import * from "./Geometry.orc"
import * from "./Buffer.orc"
import * from "./Mat.orc"
import * from "../SuiDesigner/Insp.orc"


class UniformInfo {
    String@ key = str("")

    // int location;

    //0:unknown 1:mat, 2:intValues, 3: floatValues, 4:tex, 5:matArray, 6:color4f
    int kind = -1;

    //intValues|floatValues的个数
    int count = 1;
    Mat mat;
    int intValues[16];
    float floatValues[16]
    int texIndex = 0// glActiveTexture的索引

    Tex2d@ tex
    String@ texPath //纹理是没办法序列化的

    MatArray@ matArray

    // void insp(Insp* insp){
        // insp.cbInsp = ^void(Insp*insp, Node* o){
        //     if self.kind == 4 {
        //     }
        // }
    // }
    void inspAsValue(Insp* insp, Node*o, Material* matl){

        layoutLinear(o, (long long)self).{
            // const char *dir = self.queryAttrDirection(mf)
            o.border.b.set(1, 0x13000000)
            o.row()

            insp.mkFieldName(o, self.key.str)
            // if self.kind ==

            // Rgabf *color = 
            // insp.inspRgbaf(o, self, )
            if self.kind == 6{
                mkColorPicker(o, 0).{
                    o.backgroundColor = mkRgbafByFloat4(self.floatValues).toInt()
                    o.onChanged = ^void (int newcolor){
                        Rgbaf nv = mkRgbafByInt(newcolor)
                        // self.setAttr(mf, mkStructObj(metaStructOf(Rgbaf), &nv))
                    }
                }
            }
            else if self.kind == 3 {
                // insp.mkFieldName(o, "floats")
                if self.count == 2 {
                    Vec2 v = mkVec2(
                        self.floatValues[0], 
                        self.floatValues[1], )
                    Insp_mkVec2(o, 0, v, ^void(Vec2 nv){} );
                }
                else if self.count == 3 {
                    Vec3 v = mkVec3(
                        self.floatValues[0], 
                        self.floatValues[1], 
                        self.floatValues[2], 
                    )
                    Insp_mkVec3(o, 0, v, ^void(Vec3 nv){} );
                }
                else if self.count == 4 {
                    Vec4 v = mkVec4(
                        self.floatValues[0], 
                        self.floatValues[1], 
                        self.floatValues[2], 
                        self.floatValues[3], 
                    )
                    Insp_mkVec4(o, 0, v, ^void(Vec4 nv){} );
                }
            }
            else if self.kind == 4 {
                String@ path = Path_resolveRelativeFromFile(self.texPath.str, matl.path.str)
                mkImageView(o, 0).{
                    o.width = 100
                    o.height = 100
                    o.setImageMode( WrapContent)
                    o.border.setAll(1, 0xff999999)
                    o.setSrc(path)
                    o.cursor.set("pointer")
                    o.cbOnEvent = ^ void(Event *e){
                        if e instanceof MouseEvent {
                            MouseEvent *me = (MouseEvent*)e;
                            if me.button == 1 && me.isClickInBubble(){
                                // Toast_make(str("click image").addString(path).str)
                                String@ tmppath = FileDialog_getFirstOpenFileName(".", "选择图片")
                                if tmppath {
                                    String@ base = Path_toAbsolute(matl.path.str)
                                    String@ rel = Path_relPathToFile(tmppath.str, base.str)
                                    printf("path:%s. rel:%s\n", tmppath.str, rel.str)

                                    matl.setUniformTex2dByPath(self.key.str, tmppath.str)
                                }
                                // FileChooser@ fc = new FileChooser()
                                // fc.use_filterImage()
                                // fc.loadPaths()
                                // fc.onChoose = ^ void(String@ newpath){
                                //     insp.setAttr(mf, newpath)
                                // }
                                // fc.showWindow()
                            }
                        }
                    }
                }
                mkTextView(o, 0).{
                    o.setText(self.texPath)
                }
            }
        }
    }


    void fromJson(Json* jo){
        self.key = jo.getString("key")

        jo.getToInt("kind", &self.kind)
        jo.getToInt("count", &self.count)

        if self.kind == 2 {
            jo.getToInts("intValues", self.intValues, self.count)
        }
        if self.kind == 3 {
            jo.getToFloats("floatValues", self.floatValues, self.count)
        }
        if self.kind == 6 {
            jo.getToFloats("floatValues", self.floatValues, self.count)
        }

        // jo.getToInt("texIndex", &self.texIndex)
        self.texPath = jo.getString("texPath")
    }
    void toJson(Json* jo){
        jo.putString("key", self.key)
        jo.putNumber("kind", self.kind)
        jo.putNumber("count", self.count)
        if self.kind == 2 {
            jo.put("intValues", Json_toJsonNumberArrayByInts(self.intValues, self.count))
        }
        if self.kind == 3 {
            jo.put("floatValues", Json_toJsonNumberArrayByFloats(self.floatValues, self.count))
        }
        if self.kind == 6 {
            jo.put("floatValues", Json_toJsonNumberArrayByFloats(self.floatValues, self.count))
        }
        // jo.putNumber("texIndex", self.texIndex)
        if self.texPath {
            jo.putString("texPath", self.texPath)
        }
    }

    Rgba getColor(){
        if self.kind == 3 {
            Rgba c = mkRgbaByFloat(
                self.floatValues[0],
                self.floatValues[1],
                self.floatValues[2],
                self.count >= 4 ? self.floatValues[3] : 1.0,
            )
            return c
        }
        return mkRgba(0, 0, 0, 0)
    }

    bool updateUniform(Program* program){
        if self.key && self.key.notEmpty() {
            if self.kind == 1 {
                // if self.mat {
                program.uniformMatrix4f(self.key.str, self.mat.data)
                // }
                // else{
                //     return false
                // }
            }
            else if self.kind == 5 {
                // if self.mat {
                program.uniformMatrix4fv(self.key.str, self.matArray.data, self.matArray.size)
                // }
                // else{
                //     return false
                // }
            }
            else if self.kind == 2 {
                if self.count == 1{
                    program.uniform1i(self.key.str, self.intValues[0]);
                }
            }
            else if self.kind == 3 {
                if self.count == 2{
                    program.uniform2f(self.key.str, 
                        self.floatValues[0],
                        self.floatValues[1],
                    );
                }
                else if self.count == 3{
                    program.uniform3f(self.key.str, 
                        self.floatValues[0],
                        self.floatValues[1],
                        self.floatValues[2],
                    );
                }
                else if self.count == 4{
                    program.uniform4f(self.key.str, 
                        self.floatValues[0],
                        self.floatValues[1],
                        self.floatValues[2],
                        self.floatValues[3],
                    );
                }
                else {
                    return false;
                }
            }
            else if self.kind == 4 {
                if self.tex {
                    self.tex.active(self.texIndex)
                    self.tex.bind() //绑定纹理到当前的texIndex中
                    program.uniform1i(self.key.str, self.texIndex);
                }
                else {
                    return false
                }
            }
            else if self.kind == 6 { // color4f
                program.uniform4f(self.key.str, 
                    self.floatValues[0],
                    self.floatValues[1],
                    self.floatValues[2],
                    self.floatValues[3],
                );
            }
            return true
        }
        return false
    }
}
//主类
class Material{
    //材质文件的路径
    String@ path = str("test.matl.json")
    Program@ program

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
    List@ uniforms = new List()

    // Mat@ mvp;
    // Mat@ model;
    // Mat@ ;
    Mat mvp = mkMatIdentity()

    Mat model = mkMatIdentity()
    Mat view = mkMatIdentity()
    Mat projection = mkMatIdentity()

    String@ vsPath = str("a.vs")
    String@ fsPath = str("a.fs")


    void insp(Insp* insp){
        new InspAttrFilePath().{o.bind(insp, "path", null);}
        new InspAttrFilePath().{o.bind(insp, "vsPath", null);}
        new InspAttrFilePath().{o.bind(insp, "fsPath", null);}

        insp.afterInsp = ^void(Insp*insp, Node* o){
            mkPanel2(o, 0).{
                o.title = str("uniforms")

                for int i = 0; i < self.uniforms.size(); i++{
                    UniformInfo* uinfo = (UniformInfo*)self.uniforms.get(i)
                    // // // mkTextView(o, i).{
                    // // //     o.setText(uinfo.key)
                    // // // }
                    // Insp@ curInsp = new Insp()
                    // // curInsp.inspObj(o, uinfo)
                    uinfo.inspAsValue(insp, o, self)
                }

            }
        }
    }
    void insp_hi(){
        Toast_make("hi")
    }


    //预备绘制。。 需要切换开关
    extern void prepareDraw()
    extern void endDraw()

    bool load(const char *path){
        self.path = str(path)



        Json@ jo = Json_parseByPathCstr(path)
        if jo {
            jo.toObject(self)
            
            String@ dirname = Path_dirname(path)
            String@ realVsPath = dirname.clone().add("/").addString(self.vsPath)
            String@ realFsPath = dirname.clone().add("/").addString(self.fsPath)

            self.buildByShaderPathCstr(realVsPath.str, realFsPath.str)
            return true
        }
        return false
    }
    bool saveTo(String* path){
        if path && path.notEmpty(){
            Json@ jo = Json_toJson(self)
            Path_writeText(path.str, jo.dump().str)
            return true
        }
        return false
    }
    bool save(){
        bool b =  self.saveTo(self.path)
        return b
    }

    void fromJson(Json* jo){
        String@ vsPath = jo.getString("vsPath")
        String@ fsPath = jo.getString("fsPath")

        self.vsPath = vsPath
        self.fsPath = fsPath

        // if vsPath && fsPath {
        //     if self.buildByShaderPathCstr(vsPath.str, fsPath.str){
        //     }
        // }


        jo.getToBool("depthTest", &self.depthTest)
        jo.getToBool("depthWrite", &self.depthWrite)
        jo.getToBool("transparent", &self.transparent)
        jo.getToBool("stencilTest", &self.stencilTest)
        jo.getToBool("alphaTest", &self.alphaTest)
        jo.getToBool("scissorTest", &self.scissorTest)
        jo.getToBool("blend", &self.blend)
        jo.getToBool("cullFace", &self.cullFace)
        jo.getToBool("wireframe", &self.wireframe)

        Json@ uniformsJa = jo.get("uniforms")
        if uniformsJa {
            self.uniforms = uniformsJa.toObjectsByVtable(UniformInfo)
        }
    }
    void toJson(Json* jo){
        jo.putBool("depthWrite", self.depthWrite)
        jo.putBool("transparent", self.transparent)

        jo.putBool("depthTest", self.depthTest)
        jo.putBool("stencilTest", self.stencilTest)
        jo.putBool("alphaTest", self.alphaTest)
        jo.putBool("scissorTest", self.scissorTest)
        jo.putBool("blend", self.blend)
        jo.putBool("cullFace", self.cullFace)
        jo.putBool("wireframe", self.wireframe)
        jo.putString("vsPath", self.vsPath)
        jo.putString("fsPath", self.fsPath)
        jo.put("uniforms", Json_toJson(self.uniforms))
    }

    void updateMvp(){
        //更新矩阵
        Mat mv;
        mv.mul(&self.view, &self.model)
        self.mvp.mul(&self.projection, &mv)
    }
    void setMvp(Mat model, Mat view, Mat projection){
        self.model = model
        self.view = view
        self.projection = projection

        //更新矩阵
        self.updateMvp()
    }

    void updateUniforms(){
        // List@ keys = self.uniforms.keys()
        int l = self.uniforms.size()
        int texIndex = 0
        for int i = 0; i < l; i++{
            // String* key = (String*)keys.get(i)
            UniformInfo* ui = (UniformInfo*)self.uniforms.get(i)
            if ui.kind == 4 { // tex
                //自动更新的texIndex
                ui.texIndex = texIndex
                texIndex++
            }
            ui.updateUniform(self.program)
        }

        //更新矩阵
        // Mat mv;
        // mv.mul(&self.view, &self.model)
        // self.mvp.mul(&self.projection, &mv)


        self.program.uniformMatrix4f("model", self.model.data)
        self.program.uniformMatrix4f("view", self.view.data)
        self.program.uniformMatrix4f("projection", self.projection.data)
        self.program.uniformMatrix4f("mvp", self.mvp.data)
    }


    UniformInfo@ getUniformInfo(const char *key){
        int l = self.uniforms.size()
        for int i = 0; i < l; i++{
            UniformInfo* ui = (UniformInfo*)self.uniforms.get(i)
            if ui.key.equals(key){
                return ui
            }
        }
        return null
    }
    UniformInfo@ gocUniformInfo(const char *key){
        int l = self.uniforms.size()
        for int i = 0; i < l; i++{
            UniformInfo* ui = (UniformInfo*)self.uniforms.get(i)
            if ui.key.equals(key){
                return ui
            }
        }
        UniformInfo@ ret= new UniformInfo()
        ret.key.set(key)
        self.uniforms.add(ret)

        return ret;
    }

    // void setLights(List* lights){
    //     // do nothing
    // }

    void setUniformTex2dByPath(const char *key, const char *path){
        String@ base = Path_toAbsolute(self.path.str)
        String@ rel = Path_relPathToFile(path, base.str)

        Tex2d@ tex = new Tex2d()
        tex.loadImageByPathCstr(path)
        UniformInfo* ui = self.setUniformTex2d(key, tex)
        ui.texPath = rel
    }
    UniformInfo* setUniformTex2d(const char *key, Tex2d* tex ){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 4
        ui.tex = tex
        // ui.texIndex = activeIndex
        return ui
    }
    void setUniformMatArray(const char *key, MatArray@ matArray){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 5
        ui.matArray = matArray
    }
    void setUniformMat4(const char *key, Mat mat){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 1
        ui.mat = mat
    }
    void setUniform1i(const char *key, int v){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 2
        ui.count = 1
        ui.intValues[0] = v
    }
    void setUniform1f(const char *key, float v){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 3
        ui.count = 1
        ui.floatValues[0] = v
    }
    void setUniform2f(const char *key, float x, float y){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 3
        ui.count = 2
        ui.floatValues[0] = x
        ui.floatValues[1] = y
    }
    void setUniform3f(const char *key, float x, float y, float z){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 3
        ui.count = 3
        ui.floatValues[0] = x
        ui.floatValues[1] = y
        ui.floatValues[2] = z
    }
    void setUniform4f(const char *key, float x, float y, float z, float w){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 3
        ui.count = 4
        ui.floatValues[0] = x
        ui.floatValues[1] = y
        ui.floatValues[2] = z
        ui.floatValues[3] = w
    }
    void setUniformColor4f(const char *key, float x, float y, float z, float w){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 6
        ui.count = 4
        ui.floatValues[0] = x
        ui.floatValues[1] = y
        ui.floatValues[2] = z
        ui.floatValues[3] = w
    }
    void setUniformColor4fByInt32Color(const char *key, int color){
        Rgbaf c = mkRgbafByInt(color)
        self.setUniformColor4f(
            key, 
            c.r, 
            c.g, 
            c.b, 
            c.a, 
        )
    }
    void setUniformVec2(const char *key, Vec2 v){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 3
        ui.count = 2
        ui.floatValues[0] = v.x
        ui.floatValues[1] = v.y
    }
    void setUniformVec3(const char *key, Vec3 v3){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 3
        ui.count = 3
        ui.floatValues[0] = v3.x
        ui.floatValues[1] = v3.y
        ui.floatValues[2] = v3.z
    }
    void setUniformVec4(const char *key, Vec4 v){
        UniformInfo@ ui = self.gocUniformInfo(key)
        ui.kind = 3
        ui.count = 4
        ui.floatValues[0] = v.x
        ui.floatValues[1] = v.y
        ui.floatValues[2] = v.z
        ui.floatValues[3] = v.w
    }


    bool buildByShaderPathCstr(const char *vsPath, const char *fsPath){
        self.program = new Program()
        // self.vsPath.set(vsPath)
        // self.fsPath.set(fsPath)
        bool ok = self.program.compileByPathCstr(
            vsPath,
            fsPath
            // "../asset/a.vs", 
            // "../asset/a.fs"
        )

        self.shaderMeta = new ShaderMeta()
        self.shaderMeta.parseFsByPathCstr(fsPath)
        self.shaderMeta.parseVsByPathCstr(vsPath)

        //应用默认值
        {
            int l = self.shaderMeta.uniformMetas.size()
            for int i = 0; i < l; i++{
                UniformMeta* um = (UniformMeta*)self.shaderMeta.uniformMetas.get(i)
                if um.defaultValue.notEmpty(){
                    UniformInfo* ui = (UniformInfo*)self.getUniformInfo(um.name.str)
                    if ui { //值已经存在
                        continue
                    }
                    List@ parts = um.defaultValue.splitByRe("\\s+")
                    if um.type.equals("vec2"){
                        if parts.size() >= 2 {
                            String* s0 = (String*)parts.get(0)
                            String* s1 = (String*)parts.get(1)
                            float v0 = s0.toFloat()
                            float v1 = s1.toFloat()
                            self.setUniform2f(um.name.str, 
                                v0, v1
                            )
                        }
                    }
                    else if um.type.equals("vec3"){
                        if parts.size() >= 3 {
                            String* s0 = (String*)parts.get(0)
                            String* s1 = (String*)parts.get(1)
                            String* s2 = (String*)parts.get(2)
                            float v0 = s0.toFloat()
                            float v1 = s1.toFloat()
                            float v2 = s2.toFloat()
                            self.setUniform3f(um.name.str, 
                                v0, v1, v2
                            )
                        }
                    }
                    else if um.type.equals("vec4"){
                        if parts.size() >= 4 {
                            String* s0 = (String*)parts.get(0)
                            String* s1 = (String*)parts.get(1)
                            String* s2 = (String*)parts.get(2)
                            String* s3 = (String*)parts.get(3)
                            float v0 = s0.toFloat()
                            float v1 = s1.toFloat()
                            float v2 = s2.toFloat()
                            float v3 = s3.toFloat()
                            self.setUniform4f(um.name.str, 
                                v0, v1, v2, v3
                            )
                        }
                    }
                }
            }
        }



        // if ok {
        // }

        return ok
    }

    ShaderMeta@ shaderMeta
}


class MaterialInsp {
    Window@ win
    Material@ matl
    // ShaderMeta@ shaderMeta

    bool _reactDirty = false
    void invalidReact(){
        if (self._reactDirty){
            return
        }
        self._reactDirty = true
        requestAnimationFrame(^bool(){
            // printf("\n\n----------------------------------------trigger react done\n\n");
            self._reactDirty = false
            self.react()
            return true
        })
    }

    // void createShaderMeta_ifNeed(){
    //     if !self.shaderMeta && self.matl && (self.matl.fsPath || self.matl.vsPath) {
    //         self.shaderMeta = new ShaderMeta()
    //         self.shaderMeta.parseVsByPathCstr(self.matl.fsPath.str)
    //         self.shaderMeta.parseVsByPathCstr(self.matl.vsPath.str)
    //     }
    // }

    void rowBool(Node*o, const char *key){
        String@ keyStr = str(key)

        // OrcMetaField_getPtr()
        OrcMetaField *mf = orc_getMetaFieldByObject(self.matl, key);
        if !mf {
            return
        }

        layoutLinear(o, (long long)mf).{
            // o.backgroundColor = 0xffff0000
            o.border.b.set(1, 0x33000000)
            mkTextView(o, 0).{ 
                o.width = 100
                o.setText(str(key).add(": ")) 
            }
            mkSwitch(o, 0).{
                bool checked = orc_getFieldInt(self.matl, key)
                o.setChecked(checked) 
                o.onCheckedChanged = ^void(Switch*ins){
                    orc_setFieldInt(self.matl, keyStr.str, ins.checked)
                    // self.matl.depthTest = ins.checked
                    self.invalidReact()
                }
            }
        }
    }
    void rowString(Node*o, const char *key){
        String@ keyStr = str(key)

        // OrcMetaField_getPtr()
        OrcMetaField *mf = orc_getMetaFieldByObject(self.matl, key);
        if !mf {
            return
        }
        if !OrcMetaField_isStringRef(mf) {
            return
        }
        String* value = *((String**)OrcMetaField_getPtr(mf, self.matl));

        layoutLinear(o, (long long)mf).{
            // o.backgroundColor = 0xffff0000
            o.border.b.set(1, 0x33000000)
            mkTextView(o, 0).{ 
                o.width = 100
                o.setText(str(key).add(": ")) 
            }
            mkDrawButton(o, 0).{
                o.text = value ? value : str("null")
            }
            // mkSwitch(o, 0).{
            //     bool checked = orc_getFieldInt(self.matl, key)
            //     o.setChecked(checked) 
            //     o.onCheckedChanged = ^void(Switch*ins){
            //         orc_setFieldInt(self.matl, keyStr.str, ins.checked)
            //         // self.matl.depthTest = ins.checked
            //         self.invalidReact()
            //     }
            // }
        }
    }

    void react(){
        // self.createShaderMeta_ifNeed()


        self.win.rootView.{
            mkScrollArea(o, 0).{
                // o.backgroundColor = 0x33ff00ff

                o.alignItems.set("stretch")
                o.useMinWidthConstraint = true
                // o.useMaxWidthConstraint = true

                layoutLinearCell(o, 0).{}


                layoutLinear(o, 0).{
                    o.direction.set("column")
                    o.alignItems.set("stretch")
                    // o.backgroundColor = 0x33ff0000

                    self.rowString(o, "vsPath")
                    self.rowString(o, "fsPath")
                    self.rowBool(o, "depthTest")
                    self.rowBool(o, "stencilTest")
                    self.rowBool(o, "alphaTest")
                    self.rowBool(o, "scissorTest")
                    self.rowBool(o, "blend")
                    self.rowBool(o, "cullFace")

                    if self.matl.shaderMeta {

                    
                        mkPanel(o, 0).{
                            o.cbRenderTitle = ^void(Node *o){
                                mkTextView(o, 0).{
                                    o.setText(str("shader uniform"))
                                }
                            }
                            o.cbRenderContent = ^void(Node *o){
                                int l = self.matl.shaderMeta.uniformMetas.size()
                                for int i = 0; i < l; i++{
                                    UniformMeta* um = (UniformMeta*)self.matl.shaderMeta.uniformMetas.get(i)
                                    if um.type.equals("mat4"){//不显示矩阵
                                        continue
                                    }

                                    UniformInfo@ ui = self.matl.getUniformInfo(um.name.str)


                                    layoutLinear(o, (long long) ui).{
                                        o.border.b.set(1, 0x33000000)
                                        mkTextView(o, 0).{
                                            o.width = 100
                                            o.cbOnEvent = ^void(Event*e){
                                                if e instanceof MouseEvent {
                                                    MouseEvent *me = (MouseEvent*)e
                                                    if me.button == 3 && me.isClickInBubble(){
                                                        ^void onActive(MenuNativeItem *item){
                                                            Toast_make("HI")
                                                        }
                                                        mkMenuNativeItem(null, str(""), onActive).{
                                                            mkMenuNativeItem(o, str("type:").addString(um.type), onActive).{ }
                                                            mkMenuNativeItem(o, str("default:").addString(um.defaultValue), onActive).{ }

                                                            MenuNative@ n = new MenuNative()
                                                            n.create(o)
                                                            n.showAtMouse()
                                                        }
                                                    }
                                                }
                                            }
                                            // String@ t = str("")
                                            // t.addString(ui.name);
                                            // t.add(" type="); t.addString(ui.type);
                                            // t.add(" editor="); t.addString(ui.editor);
                                            // t.add(" default="); t.addString(ui.defaultValue);
                                            o.setText(um.name)
                                        }
                                        // mkTextView(o, 0).{
                                        //     o.setText(
                                        //         str("type=").addString(ui.type).add(", editor=").addString(ui.editor)
                                        //     )
                                        // }
                                        if um.editor.equals("Color4f"){
                                            mkColorPicker(o, o).{
                                                if ui {
                                                    Rgba c = ui.getColor()
                                                    o.backgroundColor = c.toInt()
                                                }
                                                o.onChanged = ^void(int newcolor){
                                                    Rgbaf c = mkRgbafByInt(newcolor)
                                                    self.matl.setUniform4f(um.name.str, c.r, c.g, c.b, c.a)
                                                    printf("更新颜色:%s\n", c.toString().str);
                                                }
                                            }
                                        }
                                        else if um.editor.equals("Color3f"){
                                            mkColorPicker(o, o).{
                                                if ui {
                                                    Rgba c = ui.getColor()
                                                    o.backgroundColor = c.toInt()
                                                }
                                                o.onChanged = ^void(int newcolor){
                                                    Rgbaf c = mkRgbafByInt(newcolor)
                                                    self.matl.setUniform3f(um.name.str, c.r, c.g, c.b)
                                                    printf("更新颜色:%s\n", c.toString().str);
                                                }
                                            }
                                        }
                                        else if um.type.equals("float"){
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[0])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform1f(um.name.str, 
                                                        et.value.toFloat(),
                                                    )
                                                    printf("更新float:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                        }
                                        else if um.type.equals("vec2"){
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[0])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform2f(um.name.str, 
                                                        et.value.toFloat(),
                                                        ui ? ui.floatValues[1] : 0,
                                                    )
                                                    printf("更新vec2:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[1])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform2f(um.name.str, 
                                                        ui ? ui.floatValues[0]:0,
                                                        et.value.toFloat(),
                                                    )
                                                    printf("更新vec2:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                        }
                                        else if um.type.equals("vec3"){
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[0])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform3f(um.name.str, 
                                                        et.value.toFloat(),
                                                        ui ? ui.floatValues[1] : 0,
                                                        ui ? ui.floatValues[2] : 0,
                                                    )
                                                    printf("更新vec3:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[1])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform3f(um.name.str, 
                                                        ui ? ui.floatValues[0]:0,
                                                        et.value.toFloat(),
                                                        ui?ui.floatValues[2]:0,
                                                    )
                                                    printf("更新vec3:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[2])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform3f(um.name.str, 
                                                        ui ? ui.floatValues[0]:0,
                                                        ui ? ui.floatValues[1]:0,
                                                        et.value.toFloat(),
                                                    )
                                                    printf("更新vec3:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                        }
                                        else if um.type.equals("vec4"){
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[0])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform4f(um.name.str, 
                                                        et.value.toFloat(),
                                                        ui ? ui.floatValues[1] : 0,
                                                        ui ? ui.floatValues[2] : 0,
                                                        ui ? ui.floatValues[3] : 0,
                                                    )
                                                    printf("更新vec4:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[1])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform4f(um.name.str, 
                                                        ui ? ui.floatValues[0]:0,
                                                        et.value.toFloat(),
                                                        ui?ui.floatValues[2]:0,
                                                        ui?ui.floatValues[3]:0,
                                                    )
                                                    printf("更新vec4:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[2])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform4f(um.name.str, 
                                                        ui ? ui.floatValues[0]:0,
                                                        ui ? ui.floatValues[1]:0,
                                                        et.value.toFloat(),
                                                        ui ? ui.floatValues[3]:0,
                                                    )
                                                    printf("更新vec4:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                            mkEditText(o, 0).{
                                                if ui && !insFocus().isFocus(o){
                                                    String@ t = str("")
                                                    t.addf(ui.floatValues[3])
                                                    o.set_value(t,false)
                                                }
                                                o.onValueChanged = ^void(EditText*et){
                                                    self.matl.setUniform4f(um.name.str, 
                                                        ui ? ui.floatValues[0]:0,
                                                        ui ? ui.floatValues[1]:0,
                                                        ui ? ui.floatValues[2]:0,
                                                        et.value.toFloat(),
                                                    )
                                                    printf("更新vec4:%s\n", et.value.str);
                                                }

                                                layoutLinearCell(o, 0)
                                            }
                                        }
                                        else if um.type.equals("sampler2D"){
                                            mkImageView(o, 0).{
                                                o.backgroundColor = 0x11333333
                                                o.margin.setVer(6)
                                                o.width = 60
                                                o.height = 60
                                                o.border.setAll(1, 0x33333333)
                                                o.setImageMode(Contain)
                                                o._img = ui && ui.tex ? loadImageByTex2d(ui.tex):null
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                
                    if 0{
                        mkPanel(o, 0).{
                            o.cbRenderTitle = ^void(Node *o){
                                mkTextView(o, 0).{
                                    o.setText(str("uniform"))
                                }
                            }
                            o.cbRenderContent = ^void(Node *o){

                                int l = self.matl.uniforms.size()
                                for int i = 0; i < l; i++{
                                    UniformInfo* ui = (UniformInfo*)self.matl.uniforms.get(i)

                                    if ui.kind == 4{
                                        layoutLinear(o, (long long) ui).{
                                            o.border.b.set(1, 0x33000000)
                                            mkTextView(o, 0).{
                                                o.width = 100
                                                o.setText(str("").addString(ui.key).add(":"))
                                            }
                                            // mkTextView(o, 0).{
                                            //     o.setText(str("纹理"))
                                            // }
                                            mkImageView(o, 0).{
                                                o.backgroundColor = 0x11333333
                                                o.margin.setVer(6)
                                                o.width = 60
                                                o.height = 60
                                                o.border.setAll(1, 0x33333333)
                                                o.setImageMode(Contain)
                                                o._img = ui.tex ? loadImageByTex2d(ui.tex):null
                                            }
                                        }
                                    }
                                    else {
                                        layoutLinear(o, (long long) ui).{
                                            o.border.b.set(1, 0x33000000)
                                            mkTextView(o, 0).{
                                                o.width = 100
                                                o.setText(str("").addString(ui.key).add(":"))
                                            }
                                            mkColorPicker(o, o).{
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            layoutLinear(o, 0).{
                o.direction.set("column")
                o.alignItems.set("stretch")
                o.border.t.set(1, 0x33666666)
                o.height = 200
                layoutLinear(o, 0).{
                    mkTextView(o, 0).{
                        o.setText(str("预览"))

                        layoutLinearCell(o, 0)
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("选择模型")
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("加载")
                        o.onClick = ^void(MouseEvent *me){
                            Material@ m = new Material()
                            if m.load("test.matl.json"){
                                Toast_make("加载成功")
                            }
                            else {
                                Toast_make("加载失败")
                            }

                            // printf("json:%s\n", jo.toString().str)
                            // self.buildDrawObj()
                        }
                    }
                    mkDrawButton(o, 0).{
                        o.text = str("保存")
                        o.onClick = ^void(MouseEvent *me){
                            // Json@ jo = Json_mkObject()
                            // self.matl.toJson(jo)
                            // Json@ jo = Json_toJson(self.matl)
                            if self.matl.save(){
                                Toast_make("保存成功")
                            } 
                            else {
                                Toast_make("保存失败")
                            }

                            // printf("json:%s\n", jo.toString().str)
                            // self.buildDrawObj()
                        }
                    }
                }

                mkMaterialPreviewView(o, 0).{
                    o.backgroundColor = 0xff222222
                    o.setImageMode(Cover)
                    if o.matl != self.matl {
                        o.matl = self.matl
                        o.buildDrawObj()
                    }
                    self.glPreviewView = o

                    layoutLinearCell(o, 0)
                }
            }
        }
    }

    void showWindow(Material@ matl){
        self.matl = matl

        new Window().{
            self.win = o
            new LayoutLinear().{
                self.win.setRootView(o)
                o.backgroundColor = 0xffffffff
                o.direction.set("column")
                o.alignItems.set("stretch")
                o.padding.setAll(6)
            }
            self.react()

            o.setTitle("材质")
            o.setSize(400, 480)
            o.show()
        }
    }
    MaterialPreviewView@ glPreviewView
}


class UniformMeta {
    String@ name = str("");
    String@ type = str("");
    String@ editor = str("");
    String@ defaultValue = str("");
}
// 解析shader code,得到元信息
class ShaderMeta {
    String@ vsPath 
    String@ vsCode 

    String@ fsPath 
    String@ fsCode 

    // <UniformMeta>
    List@ uniformMetas = new List()

    UniformMeta@ getUniformMeta(const char *name){
        int l = self.uniformMetas.size()
        for int i = 0; i < l; i++ {
            UniformMeta* um = (UniformMeta*)self.uniformMetas.get(i)
            if um.name.equals(name) {
                return um
            }
        }
        return null
    }
    
    void parseCode(String* code){
        if code == null || code.empty() {
            return
        }
        List@ lines = code.splitToLines()

        String@ editor = null
        String@ defaultValue = null

        for int i = 0; i < lines.size(); i++ {
            String* line = (String*)lines.get(i)
            // printf("line %d: %s\n", i, line.str)
            if line.startsWith("//@default ") {
                defaultValue = line.substringByByteStart(11).trim()
            }
            else if line.startsWith("//@editor ") {
                editor = line.substringByByteStart(10).trim()
            }
            else if line.startsWith("uniform "){
                List@ parts = line.splitByRe("\\s+|;")
                if parts.size() >= 3 {
                    String* typeName = (String*)parts.get(1)
                    String* name = (String*)parts.get(2)
                    UniformMeta *oldUm = self.getUniformMeta(name.str)

                    if oldUm {//旧的Uniform已经存在
                        // 旧的uniform的信息也全,不需要覆盖
                        if oldUm.editor.notEmpty() || oldUm.defaultValue.notEmpty()  {
                            defaultValue = null
                            editor = null
                            continue
                        }
                        // 旧的Uniform信息不全,需要删除
                        self.uniformMetas.remove(oldUm)
                        printf("\tremove old uniform: %s\n", name.str)
                    }

                    UniformMeta@ um = new UniformMeta()
                    um.name = name
                    um.type = typeName
                    if editor {
                        um.editor = editor
                    }
                    if defaultValue {
                        um.defaultValue = defaultValue
                    }

                    self.uniformMetas.add(um)

                    defaultValue = null
                    editor = null

                    printf("uniform: %s, type: %s, editor:%s default: %s\n", 
                        um.name.str, 
                        um.type.str, 
                        um.editor.str,
                        um.defaultValue.str)
                }
            }
        }
    }

    void parseFsByPathCstr(const char *path){
        self.fsPath = str(path)
        String@ code = Path_readText(path)
        self.fsCode = code
        self.parseCode(code)
    }
    void parseVsByPathCstr(const char *path){
        self.vsPath = str(path)
        String@ code = Path_readText(path)
        self.vsCode = code
        self.parseCode(code)
    }
}


class MaterialPreviewView extends ImageView {
    Fbo@ fbo 
    Material@ matl
    Draw@ drawObj

    void buildDrawObj(){
        ObjLoader@ loader = new ObjLoader()
        loader.load("../assimp/test/models/OBJ/spider.obj");

        self.drawObj = new Draw()
        self.drawObj.material = self.matl


        self.drawObj.buildGeometryByJsonPathCstr("../asset/TriangleFix.json")


        // self.drawObj.geometry = loader.buildGeometry();

        Material* o = self.matl
        // o.model.scale(0.02, 0.02, 0.02)
        // o.view.lookAt(mkVec3(0, -1000, 2000), mkVec3(0, 0, 0), mkVec3(0, 0, 1))
        o.view.lookAtFake(mkVec3(0, 2000, 1000), mkVec3(0, 0, 0), mkVec3(0, 1, 0))
        o.projection.perspective(45 / 180.0 * 3.1415926, 1.0, 0.1, 10000)

        printf("mk draw succ\n");

        // self.applyModel()

        // self.fbo = new Fbo()
        // self.fbo.buildWithColorDepthStencil(200, 200)
    }

	void draw_self(Canvas* canvas) {

        {
            bool mkFbo = false
            if self.drawObj && self.fbo == null {
                mkFbo = true
            }
            else if self.fbo {
                Vec2 size = self.fbo.getSize()
                if size.x != (int)self.frame.width || size.y != (int)self.frame.height{
                    mkFbo = true
                }
            }
            if mkFbo {
                printf("重建fbo. size:%f,%f\n", self.frame.width, self.frame.height)
                self.fbo = new Fbo()
                self.fbo.buildWithColorDepthStencil((int)self.frame.width, (int)self.frame.height)
            }
        }
        if self.fbo {
            //绘制fbo
            self.fbo.startDraw(0.0, 0.0, 0.0, 1.0, true, true, true)
            self.drawObj.draw()
            self.fbo.endDraw()
            //do draw
            self._img = loadImageByTex2d(self.fbo.tex2d)
        }
        super.draw_self(canvas)

        //绘制opengl
    }
    void onEvent(Event *e){
        if e instanceof MouseEvent {
            MouseEvent *me = (MouseEvent*)e
            if me.isMouseDown {
                self.drag.onDrag = ^void(Drag *d){
                    if d.isDragging{
                        // self.drawObj.material.model.translate(d.deltaPos.x, d.deltaPos.y, 0)
                        if d.mouseDownButton == 1 {//rotate
                            self.rotateY += toRad(d.deltaPos.x)
                            self.applyModel()
                        }
                        if d.mouseDownButton == 3 {//scale
                            self.scale = clampFloat(self.scale + d.deltaPos.x / 10000.0, 0.01, 2.0)
                            self.applyModel()
                        }
                        // self.drawObj.material.model.scale(d.deltaPos.x, 0, 0)
                    }
                }
                self.drag.onMouseDown(me)
            }
        }
    }
    float rotateY = 0
    float scale = 0.02
    void applyModel(){
        if self.drawObj && self.drawObj.material {
            &self.drawObj.material.model.{
                o.identity()
                o.rotateY(self.rotateY)
                o.scale(self.scale, self.scale, self.scale)
            }
        }
    }
    Drag@ drag = new Drag()
}
MaterialPreviewView@ mkMaterialPreviewView(void* parent, long long key){
    void *addr =  __builtin_return_address(0)
    void *sp = key ? (void*)key: addr
    return (MaterialPreviewView@)gocNode(sp, (Node*)parent, MaterialPreviewView)
}

void testMaterialMeta(){
    ShaderMeta@ sm = new ShaderMeta()
    sm.parseVsByPathCstr("../asset/a.vs")
    sm.parseFsByPathCstr("../asset/a.fs")
}
void testInspMaterial(){

    printf("hi insp material\n")
    new Window().{ 
        Window* win = o

        new ScrollArea().{
            // o.backgroundColor = 0xffdfdfdf
            o.backgroundColor = 0xeeefefff
            win.setRootView(o)

            o.aiStretch()

            layoutLinear(o, 0).{

                o.column().jcs().aiStretch()
                o.backgroundColor = 0x99efefff

                // TestObj@ obj = new TestObj()

                Material@ matl = new Material()
                matl.load("../asset/basic.matl.json")

                Insp@ insp = new Insp()
                insp.insp(o, matl)


                // useEbus().cbOnEvent = ^void(Event*e){
                //     printf("收到事件:%s\n", orc_getVtableByObject(e).className)
                //     printf("TestObj:%d %s. value:%f, isMale:%d\n", obj.age, obj.name.str, obj.value, obj.isMale)
                //     printf("pos:%f,%f\n", obj.pos.x, obj.pos.y)
                //     printf("rotation:%f,%f,%f\n", obj.rotation.x, obj.rotation.y, obj.rotation.z)
                //     printf("quat:%f,%f,%f,%f\n", obj.quat.x, obj.quat.y, obj.quat.z, obj.quat.w)
                // }
            }
        }

        // o.borderless = true
        // o.setTransparent()
        o.setTitle("材质")
        o.setSize(640, 480)
        o.moveToCenter()
        o.show()
    }
}