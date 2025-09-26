
package Sgl

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

import * from "../Orc/String.orc"
import * from "../Orc/Math.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Node.orc"
import type * from "./Sphere.orc"
import type * from "./Box3.orc"
import * from "./Mat.orc"
import * from "./Geometry.orc"
import * from "./Ray.orc"
import * from "./Obj3d.orc"
import * from "./Buffer.orc"

struct RayCheckResult {
    bool succ
    float distance
    Vec3 point
    Obj3d * obj
    const char *desc
}
RayCheckResult mkRayCheckResultFail(){
    RayCheckResult r
    memset(&r, 0, sizeof(RayCheckResult))
    return r
}

//光线投射,用来做hitTest
class Raycaster {
    float nearDistance = 1
    float farDistance = 10000
    Ray ray

    //存放结果
    RayCheckResult result

    RayCheckResult raycastTree(Obj3d* root){
        //重置
        self.result = mkRayCheckResultFail()

        self.raycastNode(root)
        // root.walkIf(self._raycastNode, self)
        return self.result
    }
    bool raycastNode(Node* n){
        if n instanceof Obj3d {
            Obj3d *obj3d = (Obj3d*)n
            if obj3d.hitTestSelfByRaycaster(self){ //成功
                return true
            }
            for (int i = 0; i < n.children.size(); i++){
                Node* kid = (Node*)n.children.get(i)
                if self.raycastNode(kid) {//有成功的，就直接退出raycast
                    return true
                }
            }
        }
        return false
    }


    // 取交点
    RayCheckResult checkIntersection(Obj3d* obj, Ray localRay, Vec3 pA, Vec3 pB, Vec3 pC) {

        IntersectResult intersect;

        // if ( material.side === BackSide ) {

        //     intersect = ray.intersectTriangle( pC, pB, pA, true, point );

        // } else {

            intersect = localRay.intersectTriangle( pA, pB, pC, false)//( material.side === FrontSide ));

        // }

        if ( ! intersect.succ) {
            return mkRayCheckResultFail();
        }

        Vec3 _intersectionPointWorld

        _intersectionPointWorld.copy( intersect.point );
        _intersectionPointWorld.applyMatrix4Local( obj._world_transform );

        float distance = self.ray.origin.distanceTo( _intersectionPointWorld );

        if ( distance < self.nearDistance || distance > self.farDistance) {
            return mkRayCheckResultFail();
        }


        RayCheckResult r
        memset(&r, 0, sizeof(RayCheckResult))

        r.succ = true
        r.distance= distance
        r.point = _intersectionPointWorld
        r.obj = obj
        return r
    }


    RayCheckResult raycastGeometry(Obj3d* obj, Geometry* geom){
        if geom.ibo == null {
            return mkRayCheckResultFail()
        }
        GeoAttr* positionAttr = geom.getAttr("position")
        if positionAttr == null {
            mkRayCheckResultFail().{
                o.desc = "no positionAttr";
                return o
            }
        }
        Buffer* buf = positionAttr.vbo.buf;
        if buf == null{
            mkRayCheckResultFail().{
                o.desc = "no positionAttr.vbo.buf";
                return o
            }
        }
        Buffer* idxBuf = geom.ibo.buf;
        if idxBuf == null{
            mkRayCheckResultFail().{
                o.desc = "no ibo.buf";
                return o
            }
        }

        int indexCount = geom.ibo.calcIndexCount()
        // 只支持triangles. 三点成面
        if indexCount % 3  != 0 {
            RayCheckResult r = mkRayCheckResultFail()
            r.desc = "invalid indexCount";
            return r
        }

        int *indexInts = (int*)idxBuf.data;
        float *vtxFloats = (int*)buf.data;
        Vec3 a
        Vec3 b
        Vec3 c
        Ray localRay = self.ray
        localRay.applyMatrix4Local(obj._world_transform.invert())

        for int i = 0; i < indexCount; i+=3 {
            int indexA = indexInts[i]
            int indexB = indexInts[i+1]
            int indexC = indexInts[i+2]

            a.fromArray(vtxFloats, indexA*3)
            b.fromArray(vtxFloats, indexB*3)
            c.fromArray(vtxFloats, indexC*3)

            RayCheckResult r = self.checkIntersection(obj, localRay, a, b, c)
            if r.succ {
                return r
            }
        }

        mkRayCheckResultFail().{
            // o.desc = "no ibo.buf";
            return o
        }
    }

}
