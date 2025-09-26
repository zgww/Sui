
package Sgl


#include <stdio.h>

#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "./Vao.orc"
import * from "../Orc/List.orc"
import * from "../Orc/String.orc"
import * from "../Orc/Map.orc"
import * from "../Json/Json.orc"

class Draw {
    //材质，，含program和opengl开关状态
    Material@ material;
    //顶点数据
    Geometry@ geometry;

    //顶点数据与材质的绑定关系
    Vao@ vao;

    // extern void _buildVao()
    bool needBuildVao(){
        return self.material && self.geometry 
        && (!self.vao 
            || 
            ( //关联不一样，也需要重建
                self.vao.material != self.material
                || self.vao.geometry != self.geometry
            )
        )
    }

    bool buildVaoIfNeed(){
        if self.needBuildVao() {
            return self.buildVao()
        }
        return true
    }
    bool buildVao(){
        // if self.needBuildVao() {
        Vao@ vao = new Vao()

        //建立关联
        vao.material = self.material
        vao.geometry = self.geometry

        vao.gen()

        vao.bind()
        bool ok = self.geometry.bindVertexAttribs(self.material)

        if self.geometry.ibo {
            self.geometry.ibo.bind()
        }

        vao.unbind()
        if ok {
            self.vao = vao
        }
        return ok
            // self._buildVao()
        // }
        // return false
    }
    void use(){
        self.buildVaoIfNeed()
        if self.material && self.material.program {
            self.material.program.use()
        }
        if self.vao {
            self.vao.bind()
        }
    }
    extern void draw()

    void buildGeometryByJsonPathCstr(const char *path){
        self.geometry = new Geometry()

        Json@ triJo = Json_parseByPathCstr(path)

        // Buffer@ verBuf = mkBufferFloatByJsonArray(triJo.get("position"))
        // Buffer@ indicesBuf = mkBufferIntByJsonArray(triJo.get("face"))

        List@ keys = triJo.keys()
        printf("load JsonMesh %s\n", path);
        for int i = 0 ; i < keys.size(); i++{
            String* key = (String*)keys.get(i)
            if key.equals("face"){
                Buffer@ indicesBuf = mkBufferIntByJsonArray(triJo.get("face"))
                Vbo@ ibo = new Vbo()
                ibo.elementBuffer(indicesBuf)
                self.geometry.ibo = ibo
                printf("\tload face:%s\n", indicesBuf.toIntString().str);
            }
            else {
                Json@ attrJo = triJo.get(key.str)
                Json@ countJo = attrJo.get("count")
                // Json@ locationJo = attrJo.get("location")

                Json@ dataJo = attrJo.get("data")
                if countJo && dataJo {
                    int count = countJo.asInt()
                    Buffer@ buf = mkBufferFloatByJsonArray(dataJo)
                    printf("\tload %s:%s\n", key.str, buf.toFloatString().str);
                    Vbo@ vbo = new Vbo()
                    vbo.arrayBuffer(buf)
                    vbo.elementCount = count

                    //关联LayoutIndex
                    // if locationJo {
                    //     vbo.vaIndex = locationJo.asInt()
                    // }

                    self.geometry.setAttr(key.str, vbo)
                }
                else {
                    printf("%s无效的顶点属性:%s\n", path, key.str)
                }
            }
        }
    }

}

class ObjLoader {
    Buffer@ vertices = new Buffer();
    Buffer@ normals = new Buffer();
    Buffer@ texCoords = new Buffer();
    Buffer@ faces = new Buffer();

    String@ path = str("")



    void load(const char *path){
        self.path.set(path)
        // self.vertices.appendFloat(0.5)
        // self.vertices.appendFloat(0.9)
        // self.vertices.appendFloat(0)

        // self.vertices.appendFloat(0.5)
        // self.vertices.appendFloat(-0.5)
        // self.vertices.appendFloat(0)

        // self.vertices.appendFloat(-0.5)
        // self.vertices.appendFloat(-0.5)
        // self.vertices.appendFloat(0)

        // self.vertices.appendFloat(-0.5)
        // self.vertices.appendFloat(0.5)
        // self.vertices.appendFloat(0)

        // self.faces.appendInt(0)
        // self.faces.appendInt(1)
        // self.faces.appendInt(3)
        // self.faces.appendInt(1)
        // self.faces.appendInt(2)
        // self.faces.appendInt(3)
        self._load()
    }
    extern void _load();

    Geometry@ buildGeometry(){
        Geometry@ geo = new Geometry()
        if self.vertices.size > 0{
            Vbo@ vbo = new Vbo()
            vbo.elementCount = 3;
            vbo.arrayBuffer(self.vertices)
            geo.setAttr("position", vbo)
            printf("\tload %s:%s\n", "position", self.vertices.toFloatString().str);
        }
        if self.normals.size > 0{
            Vbo@ vbo = new Vbo()
            vbo.elementCount = 3;
            vbo.arrayBuffer(self.normals)
            geo.setAttr("normal", vbo)
        }
        if self.texCoords.size > 0{
            Vbo@ vbo = new Vbo()
            vbo.elementCount = 2;
            vbo.arrayBuffer(self.texCoords)
            geo.setAttr("texCoord", vbo)
        }
        if self.faces.size > 0 {
            geo.ibo = new Vbo()
            geo.ibo.elementBuffer(self.faces)
            printf("\tload face:%s\n", self.faces.toIntString().str);
        }

        return geo
    }
}
