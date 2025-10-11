package Sgl

#include <stdio.h>
#include <assimp/cimport.h>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "./Obj3d.orc"
import * from "./Mesh.orc"
import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Geometry.orc"
import * from "./Material.orc"


class AssimpLoader {
    struct aiScene *scene;
    void load(const char *model_path){
        // 加载模型（使用默认后处理）
        struct aiScene* scene = aiImportFile(
            model_path,
            aiProcess_Triangulate       |   // 三角化多边形
            aiProcess_GenNormals        |   // 如果没有法线则生成
            aiProcess_FlipUVs           |   // 根据需要翻转 UV（OpenGL vs DirectX）
            aiProcess_JoinIdenticalVertices // 合并重复顶点
        );

        printf("assimp 加载模型:%s. scene:%p\n", model_path, scene)
        if !scene {
            printf("assimp load %s fail. \n", model_path);
            return
        }

        // 释放资源
        aiReleaseImport(scene);
    }
    void printScene(){

    }

}


// 模型加载器
class ModelLoader extends Obj3d {
    Buffer@ vertices = new Buffer();
    Buffer@ normals = new Buffer();
    Buffer@ texCoords = new Buffer();
    Buffer@ faces = new Buffer();

    String@ path
    Mesh@ mesh = new Mesh()

    void setPath(String@ path){
        self.path = path

        // 调用加载器加载
        if path {
            self._load()
            self.mesh.geometry = self.buildGeometry()
            new Material()~{
                o.load("../asset/basic.matl.json")
                self.mesh.material = o
            }
            self.appendChild(self.mesh)
        }
    }


    extern void _load()

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

void test_AssimpLoader () {
    AssimpLoader@ l = new AssimpLoader()
    l.load("spider.obj")
}