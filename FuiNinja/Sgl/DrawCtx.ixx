module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:DrawCtx;

import :Obj3d;
import :Light;
import :DirLight;
import :PointLight;
import :Scene;
import :Camera;
import :Material;
import :Geometry;

int cmpObj3dDepth(const void* a, const void* b) {
	Obj3d* aobj = (Obj3d*)a;
	Obj3d* bobj = (Obj3d*)b;
	float dz = aobj->_viewPosition.z - bobj->_viewPosition.z;
	return dz <= 0 ? -1 : 0;
}

//渲染上下文
export class DrawCtx : public GcObj {
public:
	std::vector<Light*> lights;
	// List@ cameras = new List()

	Scene* scene;
	Camera* camera;

	Vec2 frameSize = mkVec2(500, 500);

	long long prevTickMs = 0;
	long long dtMs = 0; //两次tick的间隔毫秒
	float dtSec = 0.0;
	float passSec = 0.0;

	Ref<Material> depthMatl{ new Material(), this };
	//Ref<Material> lineMatl = new Material()
	//GeometryLine@ lineGeometry = new GeometryLine()

	std::vector<Obj3d*> transparentObj3ds;

	Ref<Closure<void()>> cbAfterDraw{ nullptr, this };

	DrawCtx() {
		//this->depthmatl->load("../asset/depth.matl->json");
		//this->linematl->load("../asset/line.matl->json");
	}

	void clearDepth() {
		glClearDepth(1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	bool addTransparentObj3dIfIsTransparent(Obj3d* obj3d, Material* matl) {
		if (matl && matl->transparent) {
			this->transparentObj3ds.push_back(obj3d);
			return true;
		}
		return false;
	}

	void drawLineGeometry() {
		//this->lineGeometry.draw(this->lineMatl);
	}
	void mkAxis() {
		{
			////绘制坐标轴
			//this->lineGeometry.{
			//    // x轴
			//    o.color = 0xffff0000
			//        o.moveTo(-100000, 0, 0)
			//        o.lineTo(100000, 0, 0)

			//        // y轴
			//        o.color = 0xff00ff00
			//        o.moveTo(0, -100000, 0)
			//        o.lineTo(0, 100000, 0)

			//        // z轴
			//        o.color = 0xff00a0ff
			//        o.moveTo(0, 0, -100000)
			//        o.lineTo(0, 0, 100000)
			//}
		}
	}

	// void collectCameras(){
	//     if !this->scene {
	//         return;
	//     }
	// }

	void collectLights() {
		if (!this->scene) {
			return;
		}
		// this->_collectLight;
		// Node *n = (Node*)this->scene;
		// n.walk(null, self)
		// Obj3d *o3d = (Obj3d*)this->scene;
		// o3d.walk(null, self)
		this->lights.clear();
		this->scene->walk([=](void* data, Node* n) {
			this->_collectLight(n);
			}, (void*)this);
	}

	void _collectLight(Node* n) {
		if (dynamic_cast<Light*> (n)) {
			this->lights.push_back((Light*)n);
		}
	}

	void tick(Scene* scene) {
		long long nowMs = Time_unixMs();
		this->dtMs = 0;
		this->dtSec = 0;
		if (this->prevTickMs > 0) {
			this->dtMs = nowMs - this->prevTickMs;
			this->dtSec = this->dtMs / 1000.0;
			// printf("nowMs:%lld, prev:%lld\n", nowMs, this->prevTickMs)
		}
		this->passSec += this->dtSec;
		this->prevTickMs = nowMs;
		scene->walkIf([=](void* data, Node* n) {
			return this->tickObj3d(n);
			}, this);
	}
	bool tickObj3d(Node* n) {
		if (dynamic_cast<Obj3d*> (n)) {
			Obj3d* obj3d = (Obj3d*)n;
			if (!obj3d->visible) {
				return false;
			}
			obj3d->tick(this);

			return true;
		}
		return false;
	}

	//绘制深度图，实现阴影要用
	//绘制深度图共用同一个场景， 使用指定的相机。 根据灯光不同，如方向光用正交相机，点光源用
	//透视相机
	//绘制深度图时，通常是共用同一个材质的
	void drawDepth(Scene* scene, Camera* camera) {
		if (scene) {
			this->scene = scene;
			this->camera = camera;

			this->tick(scene);

			this->collectLights();

			//透明度排序
			glViewport(
				(int)(this->camera->viewport.x * this->frameSize.x),
				(int)(this->camera->viewport.y * this->frameSize.y),
				(int)(this->camera->viewport.w * this->frameSize.x),
				(int)(this->camera->viewport.h * this->frameSize.y)
			);

			//更新模型矩阵
			scene->updateWorldTransformAndSubtree();

			//更新相机的矩阵
			this->camera->updateProjectionMat();
			this->camera->updateViewMat();


			//this->depthmatl->view = camera->view;
			//this->depthmatl->projection = camera->projection;

			//scene->walk([=](void *ud, Node *n) {
			//    this->_drawNodeDepth(n);
			//    }
			//    , this);
		}
	}
	void _drawNodeDepth(Node* n) {
		if (dynamic_cast<Obj3d*> (n)) {
			Obj3d* o3d = (Obj3d*)n;

			//this->depthmatl->model = o3d->_world_transform;

			//o3d->drawDepth(this);
		}
	}

	void updateViewport() {
		glViewport(
			(int)(this->camera->viewport.x * this->frameSize.x),
			(int)(this->camera->viewport.y * this->frameSize.y),
			(int)(this->camera->viewport.w * this->frameSize.x),
			(int)(this->camera->viewport.h * this->frameSize.y)
		);
	}

	// [camera]?
	void draw(Scene* scene, Camera* camera) {
		if (!scene) {
			printf("DrawCtx fail. no scene\n");
			return;
		}

		this->scene = scene;
		if (camera) {
			this->camera = camera;
		}
		if (!this->camera) {
			this->camera = scene->findNodeByClass< Camera>();
			if (!this->camera) {
				printf("DrawCtx fail. no camera\n");
				return;
			}
		}

		this->transparentObj3ds.clear();

		this->tick(scene);

		this->collectLights();
		// this->collectCameras()

		this->updateViewport();
		//透明度排序

		//更新模型矩阵
		scene->updateWorldTransformAndSubtree();

		//更新相机的矩阵
		this->camera->updateProjectionMat();
		this->camera->updateViewMat();

		//this->lineGeometry.clear();

			//绘制
		scene->draw(this);
		this->drawTransparentObj3ds();

		if (this->cbAfterDraw) {
			this->cbAfterDraw->invoke();
		}

		// scene.walk(this->_drawNodeDepth, self)

	//this->setMvpToMaterial(nullptr, this->lineMatl);

		// this->lineGeometry.appendVertexAndColor(mkVec3(0,0,0), 0xff0000ff)
		// this->lineGeometry.appendVertexAndColor(mkVec3(400,400,0.5), 0xffff0000)
		// this->lineGeometry.appendVertexAndColor(mkVec3(400,400,0.5), 0xffff0000)
		// this->lineGeometry.appendVertexAndColor(mkVec3(800,-400,0.5), 0xff00ffff)


	}
	void drawTransparentObj3ds() {
		int size = this->transparentObj3ds.size();
		if (size <= 0) {
			return;
		}

		//计算在相机中的位置
		Mat view = this->camera->view;

		for (int i = 0; i < size; i++) {
			Obj3d* obj3d = this->transparentObj3ds[i];
			if (obj3d) {
				Vec3 worldPos = obj3d->localToWorld(mkVec3(0, 0, 0));
				obj3d->_viewPosition = view.mulVec3(worldPos);
			}
		}
		//按深度排序
		qsort(this->transparentObj3ds.data(), size, pointerSize(), cmpObj3dDepth);


		//绘制
		for (int i = 0; i < size; i++) {
			Obj3d* obj3d = this->transparentObj3ds[i];
			if (obj3d) {
				obj3d->drawTransparent(this);
			}
		}
	}
	//设置矩阵
	void setMvpToMaterial(Obj3d* obj3d, Material* material) {
		// if obj3d {
		//     material.model = obj3d._world_transform
		// }
		// else {
		//     material.model = mkMatIdentity() //在世界坐标系下
		// }
		// material.view = this->camera.view
		// material.projection = this->camera.projection

		material->setMvp(
			obj3d ? obj3d->_world_transform : mkMatIdentity(),
			this->camera->view,
			this->camera->projection
		);
	}

	void setGlobalInfosToMaterial(Material* matl) {
		//累计秒数
		//帧间隔
		matl->setUniform4f("time",
			this->passSec,
			this->dtSec,
			0, 0
		);
		this->setLightsToMaterial(matl);

		//测试blinn-phong.fs
		// matl->setUniform3f("lightPos", 100, 150, 0)

		Vec3 viewPos = this->camera->localToWorld(mkVec3(0, 0, 0));
		matl->setUniformVec3("viewPos", viewPos);
		// matl->setUniform1f("ambientStrength", 0.2)
		// matl->setUniform1f("specularStrength", 0.5)
		// matl->setUniform1f("shininess", 32.0)
		// matl->setUniform3f("lightColor", 1, 1, 1)
	}

	//设置灯光信息到材质上
	void setLightsToMaterial(Material* matl) {
		for (int i = 0; i < this->lights.size(); i++) {
			Light* light = (Light*)this->lights[i];
			// light.setToMaterial(matl)
			if (dynamic_cast<PointLight*>(light)) {
				PointLight* pl = (PointLight*)light;
				Rgbaf c = mkRgbafByInt(pl->color);

				//要求使用结构体
				// struct PointLight {
				//     vec3 position
				//     vec3 color
				//     float intensity
				//     float distance
				//     float decay
				// }
				// printf("set light\n")

				Vec3 pos = light->localToWorld(mkVec3(0, 0, 0));
				matl->setUniform3f("pointLight.position", pos.x, pos.y, pos.z);
				matl->setUniform3f("pointLight.color", c.r, c.g, c.b);
				matl->setUniform1f("pointLight.intensity", pl->intensity);
				matl->setUniform1f("pointLight.distance", pl->distance);
				matl->setUniform1f("pointLight.decay", pl->decay);
			}
			else if (dynamic_cast<DirLight*> (light)) {
				DirLight* pl = (DirLight*)light;
				Rgbaf ambient = mkRgbafByInt(pl->ambient);
				Rgbaf diffuse = mkRgbafByInt(pl->diffuse);
				Rgbaf specular = mkRgbafByInt(pl->specular);

				Vec3 pos = light->localToWorld(mkVec3(0, 0, 0));
				pos = pos.scale(-1);
				pos = pos.normalize();
				matl->setUniformVec3("dirLight.direction", pos);//光源->物体
				matl->setUniform3f("dirLight.ambient", ambient.r, ambient.g, ambient.b);
				matl->setUniform3f("dirLight.diffuse", diffuse.r, diffuse.g, diffuse.b);
				matl->setUniform3f("dirLight.specular", specular.r, specular.g, specular.b);
			}

		}
	}
};