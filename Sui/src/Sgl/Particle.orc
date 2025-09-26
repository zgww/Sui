package Sgl


#include <stdio.h>
#include <math.h>

import * from "./Obj3d.orc"

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "./Mat.orc"
import * from "./DrawCtx.orc"
import * from "./Vao.orc"
import * from "./Buffer.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "./GeometryRect.orc"


class Particle {
    float health = 0
    float tail = 0
    float gravity = 0
    Vec3 location
    Vec3 velocity
    Vec3 scale
    int facing = 0 // xyquad?
}

extension Particle {
    void init(ParticleEmitter *em){
        self.health = em.lifeSpan
        // self.tail = tail

        self.gravity = em.gravity

        self.scale.copy( em.segmentScaling)
        self.location.set(
            randRadiusf(em.length),
            0,
            randRadiusf(em.width),
        )
        self.velocity.set(0, 1, 0)

        // 全局空间
        if !em.modelSpace {
            self.location = em._world_transform.mulVec3(self.location)
        }
        else {// 模型空间，也要应用旋转

        }

        // 速度标量
        float velocityLen = em.speed + randRadiusf(em.variation)
        self.velocity = self.velocity.scale(velocityLen)
    }
    void update(float dtInSec){
        self.health -= dtInSec

        if self.health > 0 {
            self.velocity.y -= self.gravity * dtInSec
            self.location.x += self.velocity.x * dtInSec
            self.location.y += self.velocity.y * dtInSec
            self.location.z += self.velocity.z * dtInSec
        }
    }
}

class ParticleEmitter extends Obj3d{
    List@ particles = new List()
    List@ particlePool = new List()
    // int alive = 0

    float timeMiddle = 0

    float speed = 100
    float variation = 50
    float latitude = 0
    float gravity = 0
    float lifeSpan = 2
    float emissionRate = 3 //每秒发射几个粒子
    float width = 100
    float length = 100
    int rows = 0
    int columns = 0

    bool emitting = true
    bool modelSpace = false
    float currentEmission = 0

    Mat lookAtCameraMat
    // 为了让非modelSpace下也受缩放的影响
    Mat worldScaleMatrix
    Mat noTranslateWorldMatrix

    Vec3 segmentScaling


    //材质，，含program和opengl开关状态
    Material@ material;
    //顶点数据
    Geometry@ geometry 
    //顶点数据与材质的绑定关系
    Vao@ vao = new Vao();
    Buffer@ insPosBuf = new Buffer()

    void onMounted(){
        self.build()
    }
    void build(){
        new GeometryRect().{
            o.build()
            self.geometry = o

            GeoAttr *attr = self.geometry.gocInstanceAttr("insPos")
            attr.vbo.setInstancedRender(3, 
                self.particles.size() //绘制实例数量
            )
        }
        self.material = new Material()
        self.material.load("../asset/particle.matl.json")
    }

    void cleanup(){
    }


    void drawSelf(DrawCtx *ctx){
        self.updateEmitter(ctx)

        //更新矩阵
        ctx.setMvpToMaterial(self, self.material)

        self.vao.draw(self.geometry, self.material)
    }
    void updateEmitter(DrawCtx *ctx){
        self.updateEmit(ctx.dtSec) // 更新发射
        self.updateParticles(ctx.dtSec) // 更新粒子的属性和死亡
        self.updateMesh() // 更新mesh
    }
    //更新当前帧发射数量
    void updateEmission(float dtSec){
        self.currentEmission += self.emissionRate * dtSec 
    }
    void updateEmit(float dtSec){
        self.updateEmission(dtSec)
        // printf("currentEmission:%f\n", self.currentEmission)

        //发射粒子
        for int i = 1; i < self.currentEmission; i++{
            self._emit()
        }
        self.currentEmission = fmod(self.currentEmission , 1)
    }
    void updateParticles(float dtSec){
        for int i = self.particles.size() - 1; i >= 0; i --{
            Particle* p = (Particle*)self.particles.get(i)
            p.update(dtSec)
            if p.health <= 0 { // dead
                self.particlePool.add(p) //回到池
                self.particles.removeAt(i)
            }
        }
    }
    void updateMesh(){
        if self.particles.size() > 0{
            GeoAttr *attr = self.geometry.gocInstanceAttr("insPos")
            attr.vbo.setInstancedRender(3, 
                self.particles.size() //绘制实例数量
            )

            self.insPosBuf.clear()

            for int i = 0; i < self.particles.size(); i++{
                Particle* p = (Particle*)self.particles.get(i)
                // p.location.x = randRadiusf(500);
                // p.location.y = randRadiusf(500);
                // p.location.z = randRadiusf(500);

                self.insPosBuf.appendFloat3(
                    // 300, 0, 0
                    p.location.x,
                    p.location.y,
                    p.location.z,
                )
                // printf("粒子%d:%f,%f,%f\n", i, p.location.x, p.location.y, p.location.z)
            }
            //更新
            attr.vbo.arrayBuffer(self.insPosBuf)
        }
    }

    //发射一个粒子
    void _emit(){
        if self.emitting {
            self.createParticle()
        }
        self.currentEmission--
    }
    void createParticle(){
        Particle@ p = null
        if self.particlePool.size() > 0{
            //从池里捞一个
            p = self.particlePool.last()
            self.particlePool.removeAt(self.particlePool.size() - 1)
        }
        else {
            p = new Particle()
        }

        // if self.alive >= self.particles.size(){ //没有备用的粒子了
        // }
        // else { // 有备用的粒子
        // }
        p.init(self)
        // printf("发射粒子。 当前粒子数:%d, 池:%d\n", self.particles.size(), self.particlePool.size())
        self.particles.add(p)
    }
}