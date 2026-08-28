#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Core/Mat.h"
#include "View/ImageView.h"
#include "View/Drag.h"
#include "Naga/Path.h"
#include "Naga/StrUtil.h"

export module Sgl:SkinMesh;
import :Obj3d;
import :Buffer;
import :Material;
import :Geometry;
import :Bone;
import :Vao;
import :DrawCtx;

export class SkinMesh :public Obj3d {
public:

    //材质，，含program和opengl开关状态
    Ref<Material> material{ nullptr, this };
    //顶点数据
    Ref<Geometry> geometry{ nullptr, this };
    Ref<Skeleton> skeleton{ nullptr, this };
        Ref<Vao> vao  { new Vao(), this };


    void initRootBoneIfNeed() {
        if (this->skeleton){
            return;
        }
        this->skeleton = this->getAncestorByClass<Skeleton>();
    }

    void onMounted() {
        this->skeleton = nullptr;
    }

    void tick(DrawCtx* ctx) {
        // printf("mesh tick:%lld\n", ctx.dtMs);
    }

    // 顶点属性在geometry中，会自动设置好


    void draw(DrawCtx* ctx) {
        this->initRootBoneIfNeed();
            if (this->skeleton == nullptr){
                return;
            }

            Material* matl = this->material;

            ctx->setMvpToMaterial(this, matl);
            ctx->setGlobalInfosToMaterial(matl);

            matl->setUniformMatArray("boneMatrix", this->skeleton->offsetMatrixArray);

            this->vao->draw(this->geometry, matl);
    }
};