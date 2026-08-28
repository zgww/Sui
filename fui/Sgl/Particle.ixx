module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Naga/TimeUtil.h"
#include "Core/Vec2.h"
#include "Core/Vec3.h"
#include "Naga/Path.h"

export module Sgl:Particle;

import :Obj3d;
import :Material;
import :Geometry;
import :GeometryRect;
import :Vao;
import :Buffer;
import :DrawCtx;

class ParticleEmitter;


export class Particle : public GcObj {
public:
	float health = 0;
	float tail = 0;
	float gravity = 0;
	Vec3 location;
	Vec3 velocity;
	Vec3 scale;
	int facing = 0; // xyquad?


	void update(float dtInSec) {
		this->health -= dtInSec;

		if (this->health > 0) {
			this->velocity.y -= this->gravity * dtInSec;
			this->location.x += this->velocity.x * dtInSec;
			this->location.y += this->velocity.y * dtInSec;
			this->location.z += this->velocity.z * dtInSec;
		}
	}
};


class ParticleEmitter :public Obj3d {
public:
	std::vector<Particle> particles;
	std::vector<Particle> particlePool;
	// int alive = 0

	float timeMiddle = 0;

	float speed = 100;
	float variation = 50;
	float latitude = 0;
	float gravity = 0;
	float lifeSpan = 2;
	float emissionRate = 3; //每秒发射几个粒子
	float width = 100;
	float length = 100;
	int rows = 0;
	int columns = 0;

	bool emitting = true;
	bool modelSpace = false;
	float currentEmission = 0;

	Mat lookAtCameraMat;
	// 为了让非modelSpace下也受缩放的影响
	Mat worldScaleMatrix;
	Mat noTranslateWorldMatrix;

	Vec3 segmentScaling;


	//材质，，含program和opengl开关状态
	Ref<Material> material{ nullptr, this };
	//顶点数据
	Ref < Geometry> geometry{ nullptr, this };
	//顶点数据与材质的绑定关系
	Ref < Vao> vao{ new Vao(), this };
	Ref < Buffer> insPosBuf{ new Buffer(), this };

	void onMounted() {
		this->build();
	}
	void build() {
		auto r = Ref(new GeometryRect());


		r->build();
		this->geometry = r;

		GeoAttr* attr = this->geometry->gocInstanceAttr("insPos");
		attr->vbo->setInstancedRender(3,
			this->particles.size() //绘制实例数量
		);
		this->material = new Material();
		this->material->load("../asset/particle.matl.json");
	}

	void cleanup() {
	}


	void drawSelf(DrawCtx* ctx) {
		this->updateEmitter(ctx);

		//更新矩阵
		ctx->setMvpToMaterial(this, this->material);

		this->vao->draw(this->geometry, this->material);
	}
	void updateEmitter(DrawCtx* ctx) {
		this->updateEmit(ctx->dtSec); // 更新发射
		this->updateParticles(ctx->dtSec); // 更新粒子的属性和死亡
		this->updateMesh(); // 更新mesh
	}
	//更新当前帧发射数量
	void updateEmission(float dtSec) {
		this->currentEmission += this->emissionRate * dtSec;
	}
	void updateEmit(float dtSec) {
		this->updateEmission(dtSec);
			// printf("currentEmission:%f\n", this->currentEmission)

			//发射粒子
			for (int i = 1; i < this->currentEmission; i++) {
				this->_emit();
			}
		this->currentEmission = fmod(this->currentEmission, 1);
	}
	void updateParticles(float dtSec) {
		for (int i = this->particles.size() - 1; i >= 0; i--) {
			Particle& p = this->particles[i];
			p.update(dtSec);
			if (p.health <= 0) { // dead
				this->particlePool.push_back(p); //回到池
				this->particles.erase(this->particles.begin() + i);
				//this->particles.removeAt(i);
			}
		}
	}
	void updateMesh() {
		if (this->particles.size() > 0) {
			GeoAttr* attr = this->geometry->gocInstanceAttr("insPos");
			attr->vbo->setInstancedRender(3,
				this->particles.size() //绘制实例数量
			);

			this->insPosBuf->clear();

			for (int i = 0; i < this->particles.size(); i++) {
				Particle& p = this->particles[i];
				// p.location.x = randRadiusf(500);
				// p.location.y = randRadiusf(500);
				// p.location.z = randRadiusf(500);

				this->insPosBuf->appendFloat3(
					// 300, 0, 0
					p.location.x,
					p.location.y,
					p.location.z
					);
				// printf("粒子%d:%f,%f,%f\n", i, p.location.x, p.location.y, p.location.z)
			}
			//更新
			attr->vbo->arrayBuffer(this->insPosBuf);
		}
	}

	//发射一个粒子
	void _emit() {
		if (this->emitting) {
			this->createParticle();
		}
		this->currentEmission--;
	}
	void createParticle() {
		Particle p;
		if (this->particlePool.size() > 0) {
			//从池里捞一个
			p = this->particlePool[this->particlePool.size() - 1];
			this->particlePool.erase(this->particlePool.end() - 1);
			//this->particlePool.removeAt(this->particlePool.size() - 1);
		}
		else {
			//p = new Particle();
		}

		// if this->alive >= this->particles.size(){ //没有备用的粒子了
		// }
		// else { // 有备用的粒子
		// }
		this->initParticle(&p);
		//p.init(self);
		// printf("发射粒子。 当前粒子数:%d, 池:%d\n", this->particles.size(), this->particlePool.size())
		this->particles.push_back(p);
	}
	void initParticle(Particle* particle) {
		auto em = this;
		particle->health = em->lifeSpan;
		// this->tail = tail

		particle->gravity = em->gravity;

		particle->scale.copy(em->segmentScaling);
		particle->location.set(
			randRadiusf(em->length),
			0,
			randRadiusf(em->width)
		);
		particle->velocity.set(0, 1, 0);

		// 全局空间
		if (!em->modelSpace) {
			particle->location = em->_world_transform.mulVec3(particle->location);
		}
		else {// 模型空间，也要应用旋转

		}

		// 速度标量
		float velocityLen = em->speed + randRadiusf(em->variation);
		particle->velocity = particle->velocity.scale(velocityLen);
	}
};
