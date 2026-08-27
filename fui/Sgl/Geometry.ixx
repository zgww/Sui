module;
#include "Core/Vec3.h";
#include "Core/Euler.h"
#include "Core/Mat.h"
#include "Core/Quaternion.h"
#include "Core/Plane.h"
#include "GL/glew.h"
#include "GL/wglew.h"

export module Sgl:Geometry;

import :Vbo;

class Material;

class GeoAttr :public GcObj {
public:
    std::string key;
    Ref<Vbo> vbo;

    bool bindVertexAttrib(Material* matl) {
        return false;
    }
};

//管理顶点数据：坐标、颜色 、面
export class Geometry: public GcObj {
public:
    // <GeoAttr>
    Ref<GcMap<GeoAttr>> attrs{ new GcMap<GeoAttr>(), this };


    Ref<Vbo> ibo{ nullptr, this };//面索引缓冲区
    Ref<Vbo> instanceVbo{ nullptr, this }; // 实例化渲染用的vbo

    int version = 1; //通过版本的变化，来识别vao是否需要重建

        // build geom...
        void build() {
    }

    void setIboByBuffer(std::vector<int>& buffer) {
        auto& me = *this;
        me.ibo = new Vbo();
        me.ibo->elementBuffer(buffer);

        me.version++;
    }
    void setAttrByBuffer(const char* name, std::vector<float>& buffer, int elementCountPerVertex) {

        auto& me = *this;
        Ref<Vbo> vbo = new Vbo();
        vbo->arrayBuffer(buffer);
        vbo->elementCount = elementCountPerVertex;
        me.setAttr(name, vbo);
    }
    void setIboByInts(int* data, int cnt) {
        auto& self = *this;
        self.ibo = new Vbo();
        self.ibo->elementBufferData(cnt * 4, data);

        self.version++;
    }
    void setIboByShorts(short* data, int cnt) {
        auto& me = *this;
        int* ints = (int*)malloc(cnt * 4);
        for (int i = 0; i < cnt; i++) {
            ints[i] = data[i];
        }
        me.ibo = new Vbo();
        me.ibo->elementBufferData(cnt * 4, ints);
        free(ints);

        me.version++;
    }


    //自动创建或者更新
    void applyAttrByBuffer(const char* name, std::vector<float>& buffer, int elementCountPerVertex) {
        auto& me = *this;
        GeoAttr* ga = me.getAttr(name);
		if (ga != nullptr && ga->vbo->byteSize >= buffer.size()) {//已存在，空间足够； 更新即可
			ga->vbo->arrayBuffer(buffer);
		}
		else {
			Ref<Vbo> vbo = new Vbo();
			ga = me.setAttr(name, vbo);
			ga->vbo->elementCount = elementCountPerVertex;
			ga->vbo->usage = GL_DYNAMIC_DRAW;
			ga->vbo->arrayBuffer(buffer);
		}
    }


    void setAttrByFloats(const char* name, float* data, int floatCount, int elementCountPerVertex) {
        auto& me = *this;
        Ref<Vbo> vbo = new Vbo();
            vbo->arrayBufferData(floatCount * 4, data);
            vbo->elementCount = elementCountPerVertex;
            me.setAttr(name, vbo);
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

    void setInstanceAttrByBuffer(const char* name, std::vector<float>& buffer, int elementCount) {
        auto& self = *this;
        Ref<Vbo> vbo = new Vbo();
        vbo->arrayBuffer(buffer);
        vbo->elementCount = elementCount;
        vbo->divide = 1; // 开启实例化渲染
        self.setAttr(name, vbo);
    }

    GeoAttr* getAttr(const char* key) {
        auto& self = *this;
        GeoAttr* a = self.attrs->get(key);
        return a;;
    }
    GeoAttr* setAttr(const char* key, Ref<Vbo> vbo) {
        auto& self = *this;
        self.version++;//vbo有变化，需要vao重新绑定

            Ref<GeoAttr> a = new GeoAttr();
        a->key = (key);
        a->vbo = vbo;
        if (vbo->divide > 0) {
            self.instanceVbo = vbo;
        }
        self.attrs->set(key, a);
        return a;
    }
    GeoAttr* gocInstanceAttr(const char* key) {
        auto& self = *this;
        GeoAttr* a = self.gocAttr(key);
        self.instanceVbo = a->vbo;
        return a;
    }
    GeoAttr* gocAttr(const char* key) {
        auto& self = *this;
        GeoAttr* a = self.attrs->get(key);
        if (a == nullptr ) {
            Ref<Vbo> vbo = new Vbo();
            a = self.setAttr(key, vbo);
        }
        return a;
    }

    // //计算顶点法线
    // void computeVertexNormals(Buffer*){
    // }
    // void normalNormals(){
    //     GeoAttr* normal = self.getAttr("normal")
    //     if normal == nullptr {
    //         return
    //     }
    // }

    bool bindVertexAttribs(Material* matl) {
        auto& self = *this;

        for (auto& it : attrs->map) {
            auto key = it.first;
            auto ga = it.second;

            if (ga) {
                bool ok = ga->bindVertexAttrib(matl);
                if (!ok) {
                    return false;
                }
            }
        }


        return true;
    }
};

void Geometry_normalNormals(std::vector<float>& buffer) {
    float* floats = (float*)buffer.data();
    int floatCount = buffer.size();

    Vec3 v3;
    for (int i = 0; i < floatCount; i += 3) {
        v3.x = floats[i];
        v3.y = floats[i + 1];
        v3.z = floats[i + 2];

        Vec3 r = v3.normalize();
        floats[i] = r.x;
        floats[i + 1] = r.y;
        floats[i + 2] = r.z;
    }
}
// 计算法线。  position的顶点为3 float, face为1 int
std::vector<float> Geometry_computeVertexNormals(std::vector<int>& face, std::vector<float>& position) {
    float* floats = (float*)position.data();
    int* indexes = (int*)face.data();
    int floatCount = position.size();
    int indexCount = face.size();

    std::vector<float> normal(position.size());


        //初始化为0
    //normal.initSize(position.size());

    float* normals = (float*)normal.data();

        //一个面一个面处理
    Vec3 pA;
    Vec3 pB;
    Vec3 pC;

    Vec3 nA;
    Vec3 nB;
    Vec3 nC;

        for (int i = 0; i < indexCount; i += 3) {
            int vA = indexes[i] * 3;
            int vB = indexes[i + 1] * 3;
            int vC = indexes[i + 2] * 3;

                // 取原顶点坐标
            pA.fromArray(floats, vA);
            pB.fromArray(floats, vB);
            pC.fromArray(floats, vC);

                // 叉积求法线
            Vec3 cb = pC.sub(pB);
            Vec3 ab = pA.sub(pB);
            Vec3 nml = cb.cross(ab);

                //取原来的法线
            nA.fromArray(normals, vA);
            nB.fromArray(normals, vB);
            nC.fromArray(normals, vC);


                //法线叠加
            nA.addLocal(nml);
            nB.addLocal(nml);
            nC.addLocal(nml);

            nA.toArray(normals, vA);
            nB.toArray(normals, vB);
            nC.toArray(normals, vC);
        }
    //归一化
    Geometry_normalNormals(normal);

    return normal;
}