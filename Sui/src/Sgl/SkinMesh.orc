package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"
import * from "./Bone.orc"
import * from "./Geometry.orc"
import * from "./Material.orc"
import * from "./Vao.orc"
import * from "./DrawCtx.orc"


// 骨骼动画
// 顶点坐标是在模型空间
// 每个骨骼都是一个坐标系，或者说矩阵
// 顶点受1-4个骨骼影响，
// 通过变换骨骼，来变换顶点的坐标。 如果受多个骨骼影响，就可以加权
// 顶点需要变换到骨骼空间下，再跟着骨骼进行变换，从而得到变换后的坐标。
// 所以引出bind-pose的作用。
// bind-pose是基本状态下的骨骼姿态，这里说的基本状态也对应着原始的顶点坐标
// inverse(bind-pose)* 顶点坐标，可以变换顶点坐标到骨骼空间
// 再左乘此时动画帧的骨骼全局矩阵，就可以得到顶点的变换后的坐标
// 顶点坐标for-bone-0 = current-animation-bond-mat * inverse(bind-pose) * 顶点坐标
// 顶点坐标 = 顶点坐标for-bone-0 * weight0 + ... + 顶点坐标for-bone-n * weight-n
// 需要注意旋转的插值，可能得用slerp


// shader数据：
// mat boneMatrix[MAX_BONE_CNT] shader中通过uniform 保存每个骨架的bind-pose矩阵和当前帧的矩阵的预乘矩阵
// 顶点属性 vec4 skinIndices 存放骨骼索引
// 顶点属性 vec4 skinWeights 存放骨骼权重 


//一个骨架，可能对应多个SkinMesh, 那要怎么找到骨架呢

//skeleton(not bone)
//  skinmesh
//  skinmesh
//  skinmesh
//  skinmesh
//  skinmesh
//  skinmesh
//  bone
//    bone
//    bone
//    bone
//  bone
//  bone
//  bone
class SkinMesh extends Obj3d {


    //材质，，含program和opengl开关状态
    Material@ material;
    //顶点数据
    Geometry@ geometry;
    Skeleton@ skeleton
    Vao@ vao = new Vao();
    

    void initRootBoneIfNeed(){
        if self.skeleton {
            return
        }
        self.skeleton = self.getAncestorByClass(Skeleton)
    }

    void onMounted(){
        self.skeleton = null
    }

    void tick(DrawCtx *ctx){
        // printf("mesh tick:%lld\n", ctx.dtMs);
    }

    // 顶点属性在geometry中，会自动设置好


    void draw(DrawCtx *ctx){
        self.initRootBoneIfNeed()
        if self.skeleton == null{
            return
        }

        Material *matl = self.material

        ctx.setMvpToMaterial(self, matl)
        ctx.setGlobalInfosToMaterial(matl)

        matl.setUniformMatArray("boneMatrix", self.skeleton.offsetMatrixArray)

        self.vao.draw( self.geometry, matl)
    }
}