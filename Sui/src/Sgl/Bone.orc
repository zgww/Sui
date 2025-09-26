package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"
import * from "./Buffer.orc"
import * from "./DrawCtx.orc"


//用于骨骼动画
class Bone extends Obj3d {
    Vec3 originPosition; // mdx动画记录的是相对位移

    // 动画矩阵，是每帧计算的. 不能直接用_world_transform. 因为动画矩阵是相对于模型空间的,不是相对于世界的
    Mat animMatrix = mkMatIdentity(); //当前帧的变换矩阵
    //绑定矩阵，是在创建时计算好的
    Mat bindPose = mkMatIdentity();//绑定矩阵的逆矩阵
    //绑定矩阵的逆，是在创建时计算好的
    Mat bindMatrixInverse = mkMatIdentity();//绑定矩阵的逆矩阵
    // 两个矩阵的乘就是offsetMatrix,要传到shader中的

    //最终每个骨骼的offsetMatrix是要放入uniform mat boneMatrix[20]中的， index就是对应的这个数组的下标
    int index = -1//-1 表示未分配index

    // //mdx要用的属性
    int parentId
    int id

    void drawSelf(DrawCtx *ctx){
        Obj3d * p = (Obj3d*)self.parent
        if p instanceof Obj3d {
            Vec3 f = p.localToWorld(mkVec3(0, 0, 0))
            Vec3 t = p.localToWorld(self.position)
            //绘制骨骼
            ctx.lineGeometry.{
                o.color = 0xff00ff00
                
                o.moveTo(f.x, f.y, f.z)
                // o.color = 0xff0000ff
                o.lineTo_color(t.x, t.y, t.z, 0xff0000ff)
            }
        }
    }
}

class Skeleton extends Obj3d {
    MatArray@ offsetMatrixArray = new MatArray()


    void calcBoneMatrixArray(){
        self.offsetMatrixArray.clear()
        CalcData calcData
        calcData.index = 0
        calcData.skeleton = self

        self.walkIf(_walkBoneIf_toCalcBoneMatrix, &calcData)
    }
    void tick(DrawCtx *ctx){
        self.calcBoneMatrixArray()
    }
}
static struct CalcData{
    Skeleton *skeleton
    int index 
}
//遍历skeleton子树,计算offsetMatrix,并附加到Skeleton.offsetMatrixArray
static bool _walkBoneIf_toCalcBoneMatrix(CalcData* calcData, Node *n){
    if n instanceof Bone {
        Bone *bone = (Bone*)n
        bone.index = calcData.index
        calcData.index++


        //计算骨骼矩阵
        Mat modelMatrix 

        bone.updateTransform()
        if n.parent instanceof Bone{//上级不是骨骼
            Bone* parentBone = bone.parent
            modelMatrix.mul(&parentBone.animMatrix, &bone.transform)
        } 
        else { //乘父骨骼的矩阵
            modelMatrix = bone.transform
        }
        bone.animMatrix = modelMatrix

        Mat offsetMatrix 
        offsetMatrix.mul(&modelMatrix, &bone.bindMatrixInverse)

        // calcData.skeleton.offsetMatrixArray.add(offsetMatrix)
        calcData.skeleton.offsetMatrixArray.set(bone.id, offsetMatrix)
        // printf("bone %s:%d, index:%d\n", bone.name.str, bone.id, bone.index);

        return true
    }
    if n instanceof Skeleton {
        return true;
    }
    return false
}