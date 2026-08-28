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

export module Sgl:Billboard;

import :Fbo;
import :DrawCtx;
import :Scene;
import :Mesh;
import :PerspectiveCamera;
import :PointLight;
import :Material;
import :Raycaster;
import :Geometry;
import :Obj3d;
import :Vao;

export class Billboard :public Obj3d {
public:
	//材质，，含program和opengl开关状态
	Ref<Material > material{ nullptr, this };
	//顶点数据
	Ref < Geometry>geometry{ nullptr, this };

	//顶点数据与材质的绑定关系
	Ref < Vao> vao{ new Vao(), this };
	Ref < Vao> depthVao{ new Vao(), this };

	void tick(DrawCtx* ctx) {
		// printf("billboard tick:%lld\n", ctx->dtMs);

		//一直看着
		Vec3 pos = ctx->camera->position;
		this->lookAt(pos.x, pos.y, pos.z);
	}
	void draw(DrawCtx* ctx) {

		if (this->material == nullptr ||
			this->geometry == nullptr) {
			return;
		}
		//如果是透明的，就放在最后，按深度排序并绘制
		if (ctx->addTransparentObj3dIfIsTransparent(this, this->material)) {
		}
		else {
			this->drawthis(ctx);
		}
		this->drawChildren(ctx);
	}
	void drawthis(DrawCtx* ctx) {
		//更新矩阵
		// this->material.model = this->_world_transform
		// this->material.view = ctx->camera->view
		// this->material.projection = ctx->camera->projection
		ctx->setMvpToMaterial(this, this->material);
		ctx->setGlobalInfosToMaterial(this->material);

		this->vao->draw(
			this->geometry,
			this->material
		);
	}
	//void drawDepth(DrawCtx* ctx) {
	//    Material* matl = ctx->depthMatl

	//        //更新矩阵
	//        matl.model = this->_world_transform
	//        matl.view = ctx->camera->view
	//        matl.projection = ctx->camera->projection
	//        matl.updateMvp()

	//        ctx->setGlobalInfosToMaterial(matl)

	//        this->depthVao.draw(
	//            this->geometry,
	//            matl
	//        )
	//}

	bool hitTestthisByRaycaster(Raycaster* raycaster) {
		RayCheckResult r = raycaster->raycastGeometry(this, this->geometry);
		raycaster->result = r;
		return r.succ;
	}
};