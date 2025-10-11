package Sgl

#include <stdio.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "./Obj3d.orc"
import * from "./Mesh.orc"
import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Geometry.orc"
import * from "./Material.orc"

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