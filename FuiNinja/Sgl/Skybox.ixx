module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:Skybox;

import :Obj3d;
import :Light;
import :DirLight;
import :PointLight;
import :Scene;
import :Camera;
import :Material;
import :Geometry;
import :Tex2d;
import :Vao;
import :DrawCtx;
import :Buffer;


export class Skybox :public Obj3d {
public:
    //材质，，含program和opengl开关状态
    Ref<Material> material{ new Material(), this };
    //顶点数据
    Ref<Geometry> geometry{ nullptr, this };

    Ref<Tex2d> front{ nullptr, this };
    Ref<Tex2d> back{ nullptr, this };
    Ref<Tex2d> left{ nullptr, this };
    Ref<Tex2d> right{ nullptr, this };
    Ref<Tex2d> upTex{ nullptr, this };
    Ref<Tex2d> down{ nullptr, this };

    Ref<Vao> vao{ new Vao(), this };


    Skybox() {
        //this->material.load("../asset/skybox.matl.json");
        this->buildGeometry();

        this->front = mkTex2dByPathCstr("../asset/skybox/front.png");
        this->back = mkTex2dByPathCstr("../asset/skybox/back.png");
        this->left = mkTex2dByPathCstr("../asset/skybox/left.png");
        this->right = mkTex2dByPathCstr("../asset/skybox/right.png");
        this->upTex = mkTex2dByPathCstr("../asset/skybox/up.png");
        this->down = mkTex2dByPathCstr("../asset/skybox/down.png");
    }


    void buildGeometry() {
        auto vtxBuf = Ref(new Buffer());
        auto faceBuf = Ref(new Buffer());
        auto uvBuf = Ref(new Buffer());
        auto texIdxBuf = Ref(new Buffer());

            auto mkPlane = [=](
                float texIdx,
                Vec3 lb,
                Vec3 rb,
                Vec3 rt,
                Vec3 lt
                ) {
                    int idx = vtxBuf->floatSize() / 3;
                        //前
                    vtxBuf->appendVec3(lb);
                    vtxBuf->appendVec3(rb);
                    vtxBuf->appendVec3(rt);
                    vtxBuf->appendVec3(lt);

                    uvBuf->appendFloat3(texIdx, 0, 0);
                    uvBuf->appendFloat3(texIdx, 1, 0);
                    uvBuf->appendFloat3(texIdx, 1, 1);
                    uvBuf->appendFloat3(texIdx, 0, 1);

                    int a = idx;
                    int b = idx + 1;
                    int c = idx + 2;
                    int d = idx + 3;
                    faceBuf->appendInt3(a, b, c);
                    faceBuf->appendInt3(a, c, d);
                };

        float h = 500;
        Vec3 f0 = mkVec3(-h, -h, h);
        Vec3 f1 = mkVec3(h, -h, h);
        Vec3 f2 = mkVec3(h, h, h);
        Vec3 f3 = mkVec3(-h, h, h);

        Vec3 b0 = mkVec3(-h, -h, -h);
        Vec3 b1 = mkVec3(h, -h, -h);
        Vec3 b2 = mkVec3(h, h, -h);
        Vec3 b3 = mkVec3(-h, h, -h);

            //if 0 {
            //    //前
            //    mkPlane(0, f0, f1, f2, f3)
            //        //后
            //        mkPlane(1, b1, b0, b3, b2)
            //        //左
            //        mkPlane(2, b0, f0, f3, b3)
            //        //右
            //        mkPlane(3, f1, b1, b2, f2)
            //        //上
            //        mkPlane(4, f3, f2, b2, b3)
            //        //下
            //        mkPlane(5, b0, b1, f1, f0)
            //}
        if (1) {
            //前
            mkPlane(0, f0, f1, f2, f3);
                //后
            mkPlane(1, b0, b1, b2, b3);
                //左
            mkPlane(2, b0, f0, f3, b3);
                //右
            mkPlane(3, f1, b1, b2, f2);
                //上
            mkPlane(4, f3, f2, b2, b3);
                //下
            mkPlane(5, b0, b1, f1, f0);
        }


        this->geometry = new Geometry();
        {
            auto& o = *this->geometry.get();
            o.setAttrByBuffer("position", vtxBuf, 3);
            o.setAttrByBuffer("idxUv", uvBuf, 3); //texIdx,x,y
            o.setIboByBuffer(faceBuf);
        }
    }

    void draw(DrawCtx* ctx) {
        if (this->material == nullptr ||
            this->geometry == nullptr){
            return;
        }

        this->material->setUniformTex2d("tex[0]", this->front);
        this->material->setUniformTex2d("tex[1]", this->back);
        this->material->setUniformTex2d("tex[2]", this->left);
        this->material->setUniformTex2d("tex[3]", this->right);
        this->material->setUniformTex2d("tex[4]", this->upTex);
        this->material->setUniformTex2d("tex[5]", this->down);

        ctx->setMvpToMaterial(this, this->material);

            //去掉平移,模型等于固定在相机空间零点
        this->material->view.data[12] = 0;
        this->material->view.data[13] = 0;
        this->material->view.data[14] = 0;
        this->material->updateMvp();

        this->vao->draw(this->geometry, this->material);
    }
};