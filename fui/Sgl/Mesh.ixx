module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Core/Mat.h"
#include "View/ImageView.h"
#include "View/Drag.h"
#include "Naga/Path.h"
#include "Naga/StrUtil.h"

export module Sgl:Mesh;

import :Fbo;
import :DrawCtx;
import :Scene;
import :Obj3d;
import :PerspectiveCamera;
import :Material;
import :Geometry;
import :Vao;
import :Raycaster;


export class Mesh : public Obj3d {
public:
    //材质，，含program和opengl开关状态
    Ref<Material> material{ nullptr, this };
    //顶点数据
    Ref<Geometry> geometry{ nullptr, this };

    //顶点数据与材质的绑定关系
    Ref<Vao> vao{ new Vao(), this };
    Ref<Vao> depthVao{ new Vao(), this };

    std::string geometryPath;
    std::string materialPath;

    void setMaterialPath(std::string p) {
        if ( !StrUtil_ends_with(p.c_str(), ".matl.json")) {
            printf("not a matl.json file\n");
            return;
        }
        this->materialPath = p;
            if (p != "") {
                this->material = new Material();
                  this->material->load(p.c_str());
            }
            else {
                this->material = nullptr;
            }
    }
    void setGeometryPath(std::string p) {
        this->geometryPath = p;

            //内置的几何体
            // if p.equals("Geometry/Box.geometry.json"){
            //     GeometryBox@ geom = new GeometryBox()
            //     geom.build()
            //     this->geometry = geom
            //     this->material = new Material()
            //     this->material.load("../asset/basic.matl.json")
            // }
            // else if p.equals("Geometry/Sphere.geometry.json"){
            //     GeometrySphere@ geom = new GeometrySphere()
            //     geom.build()
            //     this->geometry = geom
            //     this->material = new Material()
            //     this->material.load("../asset/basic.matl.json")
            // }
            // else if p.equals("Geometry/Plane.geometry.json"){
            //     GeometryPlane@ geom = new GeometryPlane()
            //     geom.build()
            //     this->geometry = geom
            //     this->material = new Material()
            //     this->material.load("../asset/basic.matl.json")
            // }
            // else 
        {
            //Ref<Geometry> geom = HoroGeometry_parseGeometryJson(p.c_str());
            //this->geometry = geom;
            //this->material = new Material();
            //this->material.load("../asset/basic.matl.json");
        }
        //printf("设置几何路径:%s\n", p ? p.c_str() : "null");
    }


    void tick(DrawCtx* ctx) {
        // printf("mesh tick:%lld\n", ctx.dtMs);
    }
    void draw(DrawCtx* ctx) {
        if (this->material == nullptr ||
            this->geometry == nullptr){
            return;
        }
            //如果是透明的，就放在最后，按深度排序并绘制
            if (ctx->addTransparentObj3dIfIsTransparent(this, this->material)) {
            }
            else {
                this->drawSelf(ctx);
            }

            this->drawChildren(ctx);
    }
    void drawSelfRaw(DrawCtx* ctx, Vao* vao, Material* material) {
        //更新矩阵
        // this->material.model = this->_world_transform
        // this->material.view = ctx.camera.view
        // this->material.projection = ctx.camera.projection
        ctx->setMvpToMaterial(this, material);
        ctx->setGlobalInfosToMaterial(material);

            //if (dynamic_cast< GeometryLine*>(this->geometry)) {
            //    GeometryLine* gl = (GeometryLine*)this->geometry;
            //        gl.draw(this->material);
            //        return;
            //}

        vao->draw(
            this->geometry,
            material
        );
    }
    void drawSelf(DrawCtx* ctx) {
        this->drawSelfRaw(ctx, this->vao, this->material);
    }
    void drawDepth(DrawCtx* ctx) {
        //Material* matl = ctx.depthMatl

        //    //更新矩阵
        //    matl.model = this->_world_transform
        //    matl.view = ctx.camera.view
        //    matl.projection = ctx.camera.projection
        //    matl.updateMvp()

        //    ctx.setGlobalInfosToMaterial(matl)

        //    this->depthVao.draw(
        //        this->geometry,
        //        matl
        //    )
    }

    bool hitTestSelfByRaycaster(Raycaster* raycaster) {
        RayCheckResult r = raycaster->raycastGeometry(this, this->geometry);
        raycaster->result = r;
        return r.succ;
    }
};