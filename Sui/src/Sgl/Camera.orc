package Sgl

#include <stdio.h>
#include <string.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Rect.orc"
import * from "./Mat.orc"
import * from "./Ray.orc"
import * from "./Obj3d.orc"

import * from "./Scene.orc"



//相机提供mvp中的vp矩阵
class Camera extends Obj3d {
    //w/h都是比例的, 0-1
    Rect viewport = mkRect(0, 0, 1, 1); //x, y, width, height
    Mat view;//视图矩阵
    Mat projection;//投影矩阵


    void onMounted(){
        sceneGlobal.cameraDirty = true
    }

    Mat calcVp(){
        //更新矩阵
        Mat vp;
        vp.mul(&self.projection, &self.view)

        Vec3 v0 = self.view.mulVec3(mkVec3(0, 0, 0))
        Vec3 v = vp.mulVec3(mkVec3(0, 0, 0))
        return vp;
    }

    void updateProjectionMat(){
    }

    void updateViewMat(){
    }
    void updateMat(){
        self.updateProjectionMat()
        self.updateViewMat()
    }

    Ray mkRay(Vec2 ndcPos){
        Ray r
        memset(&r, 0, sizeof(Ray))
        return r
    }
	Vec3 project( Vec3 worldPos ) {
		worldPos.applyMatrix4Local( self.view ).applyMatrix4Local( self.projection );
        return worldPos
	}

    // 反向投影回世界坐标
	Vec3 unproject( Vec3 ndcPos) {
        Mat projectionInverse = self.projection  
        projectionInverse.invertLocal()
		ndcPos.applyMatrix4Local( projectionInverse )
        ndcPos.applyMatrix4Local( self._world_transform);
        return ndcPos
	}
    // 反向投影回视图坐标
    Vec3 unprojectToView(Vec3 ndcPos){
        Mat projectionInverse = self.projection  
        projectionInverse.invertLocal()
		ndcPos.applyMatrix4Local( projectionInverse )
        return ndcPos
    }
    // 令正z轴朝向目标位置
    void lookAt( float x, float y, float z){
        self.lookAtByDir(true, x, y, z)
    }
}