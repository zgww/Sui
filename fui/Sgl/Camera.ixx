module;
#include "Urgc/UrgcIndex.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Vec2.h"
#include "Core/Rect.h"

export module Sgl:Camera;

import :Obj3d;
import :Ray;


//相机提供mvp中的vp矩阵
export class Camera :public Obj3d {
public:
    //w/h都是比例的, 0-1
    Rect viewport = mkRect(0, 0, 1, 1); //x, y, width, height
    Mat view;//视图矩阵
    Mat projection;//投影矩阵


    void onMounted() {
        //sceneGlobal.cameraDirty = true
    }

    Mat calcVp() {
        //更新矩阵
        Mat vp;
        vp.mul(&this->projection, &this->view);

        Vec3 v0 = this->view.mulVec3(mkVec3(0, 0, 0));
        Vec3 v = vp.mulVec3(mkVec3(0, 0, 0));
        return vp;
    }

    void updateProjectionMat() {}

    void updateViewMat() {}
    void updateMat() {
        this->updateProjectionMat();
        this->updateViewMat();
    }

    Ray mkRay(Vec2 ndcPos) {
        Ray r;
        memset(&r, 0, sizeof(Ray));
        return r;
    }
    Vec3 project(Vec3 worldPos) {
        worldPos.applyMatrix4Local(this->view)->applyMatrix4Local(this->projection);
        return worldPos;
    }

    // 反向投影回世界坐标
    Vec3 unproject(Vec3 ndcPos) {
        Mat projectionInverse = this->projection;
        projectionInverse.invertLocal();
        ndcPos.applyMatrix4Local(projectionInverse);
        ndcPos.applyMatrix4Local(this->_world_transform);
        return ndcPos;
    }
    // 反向投影回视图坐标
    Vec3 unprojectToView(Vec3 ndcPos) {
        Mat projectionInverse = this->projection;
        projectionInverse.invertLocal();
        ndcPos.applyMatrix4Local(projectionInverse);
        return ndcPos;
    }
    // 令负z轴朝向目标位置
    void lookAt(float x, float y, float z) {
        this->lookAtByDir(true, x, y, z);
    }
};