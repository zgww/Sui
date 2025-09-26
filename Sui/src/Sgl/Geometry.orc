package Sgl

#include <stdlib.h>
#include <stdio.h>
#include "./UnitOpengl.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Program.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Orc/String.orc"


class GeoAttr {
    String@ key;
    Vbo@ vbo;

    extern bool bindVertexAttrib(Material* matl)
}

//管理顶点数据：坐标、颜色 、面
class Geometry {
    // <GeoAttr>
    Map@ attrs = new Map()

    Vbo@ ibo;//面索引缓冲区
    Vbo@ instanceVbo; // 实例化渲染用的vbo

    int version = 1 //通过版本的变化，来识别vao是否需要重建

    void setIboByBuffer(Buffer* buffer){
        self.ibo = new Vbo()
        self.ibo.elementBuffer(buffer)

        self.version++
    }
    void setAttrByBuffer(const char *name, Buffer *buffer, int elementCountPerVertex){
        Vbo@ vbo = new Vbo()
        vbo.arrayBuffer(buffer)
        vbo.elementCount = elementCountPerVertex
        self.setAttr(name, vbo)
    }
    void setIboByInts(int *data, int cnt){
        self.ibo = new Vbo()
        self.ibo.elementBufferData(cnt * 4, data)

        self.version++
    }
    void setIboByShorts(short *data, int cnt){
        int* ints = malloc(cnt * 4);
        for int i = 0; i < cnt; i++{
            ints[i] = data[i];
        }
        self.ibo = new Vbo()
        self.ibo.elementBufferData(cnt * 4, ints)
        free(ints);

        self.version++
    }


    //自动创建或者更新
    void applyAttrByBuffer(const char *name, Buffer *buffer, int elementCountPerVertex){
        GeoAttr* ga = self.getAttr(name)
        if ga != null && ga.vbo.byteSize >= buffer.size {//已存在，空间足够； 更新即可
            ga.vbo.arrayBuffer(buffer)
        }
        else {
            Vbo@ vbo = new Vbo()
            ga = self.setAttr(name, vbo)
            ga.vbo.elementCount = elementCountPerVertex
            ga.vbo.usage = GL_DYNAMIC_DRAW
            ga.vbo.arrayBuffer(buffer)
        }
    }


    void setAttrByFloats(const char *name, float *data, int floatCount, int elementCountPerVertex){
        Vbo@ vbo = new Vbo()
        vbo.arrayBufferData(floatCount * 4, data);
        vbo.elementCount = elementCountPerVertex
        self.setAttr(name, vbo)
    }
    //只要geom里有属性是instance属性，就会开启实例化渲染
    //实例的数量由Vbo计算得出
    //用法：
    // GeometryBox@ geom = new GeometryBox()
    // geom.build()

    // Buffer@ insPos = new Buffer()
    // for int i = 0; i < 1000; i++ {
    //     float x = randRadiusf(1000)
    //     float z = randRadiusf(1000)
    //     // printf("x, z:%f,%f\n", x, z)
    //     insPos.appendFloat3(x, 0, z)
    // }

    // geom.setInstanceAttrByBuffer("insPos", insPos, 3)

    void setInstanceAttrByBuffer(const char *name, Buffer *buffer, int elementCount){
        Vbo@ vbo = new Vbo()
        vbo.arrayBuffer(buffer)
        vbo.elementCount = elementCount
        vbo.divide = 1 // 开启实例化渲染
        self.setAttr(name, vbo)
    }

    GeoAttr* getAttr(const char *key){
        GeoAttr* a = (GeoAttr*)self.attrs.get(key)
        return a;
    }
    GeoAttr* setAttr(const char *key, Vbo@ vbo){
        self.version++//vbo有变化，需要vao重新绑定

        GeoAttr@ a = new GeoAttr()
        a.key = str(key)
        a.vbo = vbo
        if vbo.divide > 0 {
            self.instanceVbo = vbo
        }
        self.attrs.put(key, a)
        return a
    }
    GeoAttr* gocInstanceAttr(const char *key){
        GeoAttr *a = self.gocAttr(key)
        self.instanceVbo = a.vbo
        return a
    }
    GeoAttr* gocAttr(const char *key){
        GeoAttr* a = (GeoAttr*)self.attrs.get(key)
        if a == null {
            Vbo@ vbo = new Vbo()
            a = self.setAttr(key, vbo)
        }
        return a
    }

    // //计算顶点法线
    // void computeVertexNormals(Buffer*){
    // }
    // void normalNormals(){
    //     GeoAttr* normal = self.getAttr("normal")
    //     if normal == null {
    //         return
    //     }
    // }

    bool bindVertexAttribs(Material *matl){
        List@ keys = self.attrs.keys()
        int l = keys.size()
        for int i = 0; i < l; i++{
            String* key = (String*)keys.get(i)
            GeoAttr* ga = (GeoAttr*)self.attrs.get(key.str)
            if ga {
                bool ok = ga.bindVertexAttrib(matl)
                if !ok {
                    return false
                }
            }
        }
        return true
    }
}

// 计算法线。  position的顶点为3 float, face为1 int
Buffer@ Geometry_computeVertexNormals(Buffer *face, Buffer *position){
    float *floats = (float*)position.data
    int *indexes = (int *)face.data
    int floatCount = position.floatSize()
    int indexCount = face.intSize()

    Buffer@ normal = new Buffer()

    //初始化为0
    normal.initSize(position.size)

    float *normals = (float*)normal.data

    //一个面一个面处理
    Vec3 pA
    Vec3 pB
    Vec3 pC

    Vec3 nA
    Vec3 nB
    Vec3 nC

    for int i = 0; i < indexCount; i+= 3{
        int vA = indexes[i] * 3
        int vB = indexes[i+1] * 3
        int vC = indexes[i+2] * 3

        // 取原顶点坐标
        pA.fromArray(floats, vA)
        pB.fromArray(floats, vB)
        pC.fromArray(floats, vC)

        // 叉积求法线
        Vec3 cb = pC.sub(pB)
        Vec3 ab = pA.sub(pB)
        Vec3 nml = cb.cross(ab)

        //取原来的法线
        nA.fromArray(normals, vA)
        nB.fromArray(normals, vB)
        nC.fromArray(normals, vC)


        //法线叠加
        nA.addLocal(nml)
        nB.addLocal(nml)
        nC.addLocal(nml)

        nA.toArray(normals, vA)
        nB.toArray(normals, vB)
        nC.toArray(normals, vC)
    }
    //归一化
    Geometry_normalNormals(normal)

    return normal
}
void Geometry_normalNormals(Buffer *buffer){
    float *floats = (float*)buffer.data
    int floatCount = buffer.floatSize()

    Vec3 v3;
    for int i = 0; i < floatCount; i+=3 {
        v3.x = floats[i]
        v3.y = floats[i+1]
        v3.z = floats[i+2]

        Vec3 r = v3.normal()
        floats[i] = r.x;
        floats[i+1] = r.y;
        floats[i+2] = r.z;
    }
}

void testGeometry(){
    printf("====================test Geometry\n")
    {
        Buffer@ b = new Buffer()
        b.appendFloat3(10, 10, 10)
        b.appendFloat3(20, 20, 20)
        b.appendFloat3(2, 0, 0)
        b.appendFloat3(0, 1, 0)
        b.appendFloat3(0, 0, 1)
        b.appendFloat3(0, 0, 0)

        Geometry_normalNormals(b)
        printf("b:%s\n", b.toFloatString().str)
    }
    {
        Buffer@ b = new Buffer()
        b.appendFloat3(-0.5, -0.5, 0)
        b.appendFloat3( 0.5, -0.5, 0)
        b.appendFloat3( 0.5,  0.5, 0)
        b.appendFloat3(-0.5,  0.5, 0)

        Buffer@ f = new Buffer()
        f.appendInt3(0, 1, 3)
        f.appendInt3(1, 2, 3)
        Buffer@ nmls = Geometry_computeVertexNormals(f, b)

        printf("nmls:%s\n", nmls.toFloatString().str)
    }
}