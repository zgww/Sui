package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Euler.orc"
import * from "../Sui/Core/Quaternion.orc"
import * from "../Orc/Math.orc"
import * from "./Camera.orc"
import * from "./Mat.orc"
import * from "./Ray.orc"
import * from "./Obj3d.orc"


class PerspectiveCamera extends Camera {

    //相机投影矩阵的相关参数
    float fov = 45 / 180.0 * PI; // y_fov
    float aspect = 1.0;
    float nearPlane = 300.1;
    float farPlane = 500

    // 视角的相关参数
    Vec3 target = mkVec3(0, 0, 0)
    // Vec3 up = mkVec3(0, 1, 0)

    // Mat view;//视图矩阵
    // Mat projection;//投影矩阵


    //构建投影矩阵
    void updateProjectionMat(){
        self.projection.perspective(
            self.fov,
            self.aspect,
            self.nearPlane,
            self.farPlane,
        )
        // 45 / 180.0 * 3.1415926, 1.0, 0.1, 10000)
    }

    //更新视图矩阵
    void updateViewMat(){
        // Vec3 eye = self.localToWorld(mkVec3(0, 0, 0))
        // //旋转矩阵
        // Mat t
        // t.lookAtLocal(eye, self.target, self.up)
        // t.setPosition(
        //     self.position.x,
        //     self.position.y,
        //     self.position.z,
        // )

        // Quaternion q
        // q.setFromRotationMatrix(t)

        // self.view = t;
        // self.view.invertLocal()

        //view矩阵就是相机模型矩阵的逆矩阵
        self.updateWorldMatrixUptoRoot()
        self.view.copy(self._world_transform).invertLocal()

        // self.view = self._world_transform
        // //view矩阵即camera模型矩阵的逆矩阵
        // self.view.invertLocal()

        // Mat rot
        // rot.lookAtLocal(
        //     worldPos,
        //     self.target,
        //     self.up);

        // Euler euler
        // euler.setFromRotationMatrix(rot, null)

        // self.rotation.setFromEuler(euler)

        // Mat t
        // t.makeTranslation(
        //     self.position.x,
        //     self.position.y,
        //     self.position.z,
        //     )
        // Mat s
        // s.makeScale(
        //     self.scale.x,
        //     self.scale.y,
        //     self.scale.z,
        // )
        // Mat sr
        // // view = t * s * r
        // sr.multiplyMatricesLocal(s, rot)
        // // self.view.multiplyMatricesLocal(t, sr)
        // self.updateTransform()
        // self.view = self.transform
        

        // self.view
        //     .lookAtFake(
        //     worldPos,
        //     self.target,
        //     self.up);

            // mkVec3(0, -1000, 2000), mkVec3(0, 0, 0), mkVec3(0, 0, 1))
    }
    void moveForward(){
        float step = 10
        Vec3 worldPos = self.localToWorld(mkVec3(0, 0, 0))
        Vec3 viewDir = self.target.sub(worldPos)
        viewDir = viewDir.normal()
        viewDir = viewDir.scale(step)

        Vec3 newWorldPos = worldPos.add(viewDir)
        self.position = newWorldPos
        self.target = self.target.add(viewDir)
    }
    void moveBackward(){
        float step = 10
        Vec3 worldPos = self.localToWorld(mkVec3(0, 0, 0))
        Vec3 viewDir = self.target.sub(worldPos)
        viewDir = viewDir.normal()
        viewDir = viewDir.scale(-1 * step)

        Vec3 newWorldPos = worldPos.add(viewDir)
        self.position = newWorldPos
        self.target = self.target.add(viewDir)
    }

    void rotateLeft(){
        self._world_transform = self.view.invert()
        Vec3 localTarget = self.worldToLocal(self.target);
        Mat rot;
        rot.identity()
        rot.rotateY(1.1 / 180.0 * PI)

        Vec3 newLocalTarget = rot.mulVec3(localTarget)
        Vec3 newTarget = self.localToWorld(newLocalTarget)
        self.target = newTarget

    }
    void rotateRight(){
        self._world_transform = self.view.invert()
        Vec3 localTarget = self.worldToLocal(self.target);
        Mat rot;
        rot.identity()
        rot.rotateY(-1.1 / 180.0 * PI)

        Vec3 newLocalTarget = rot.mulVec3(localTarget)
        Vec3 newTarget = self.localToWorld(newLocalTarget)
        self.target = newTarget
    }
    void rise(){
        self.position.y += 10
    }
    void fall(){
        self.position.y -= 10
    }
    Ray mkRay(Vec2 ndcPos){
        Ray r
        r.origin.setFromMatrixPosition( self._world_transform);

        Vec3 wp = self.unproject(
            mkVec3( ndcPos.x, ndcPos.y, 0.5 )
        )
        Vec3 dir = wp.sub(r.origin)
        r.direction = dir.normal()

        // r.direction.set( ndcPos.x, ndcPos.y, 0.5 ) 
            // .unproject( camera ).sub( this.ray.origin ).normalize();
        return r
    }

}