package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "./Mat.orc"
import * from "./Obj3d.orc"
import * from "./Material.orc"
import * from "./Geometry.orc"
import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Vao.orc"
import * from "./Raycaster.orc"
import * from "./DrawCtx.orc"
import * from "../Orc/List.orc"
import * from "../Orc/String.orc"
import * from "../Orc/Map.orc"
import * from "../Json/Json.orc"


class Billboard extends Obj3d {
    //材质，，含program和opengl开关状态
    Material@ material;
    //顶点数据
    Geometry@ geometry;

    //顶点数据与材质的绑定关系
    Vao@ vao = new Vao();
    Vao@ depthVao = new Vao();

    void tick(DrawCtx *ctx){
        // printf("billboard tick:%lld\n", ctx.dtMs);

        //一直看着
        Vec3 pos = ctx.camera.position
        self.lookAt(pos.x, pos.y, pos.z)
    }
    void draw(DrawCtx *ctx){

        if self.material == null ||
            self.geometry == null {
            return;
        }
        //如果是透明的，就放在最后，按深度排序并绘制
        if ctx.addTransparentObj3dIfIsTransparent(self, self.material){
        }
        else {
            self.drawSelf(ctx)
        }
        self.drawChildren(ctx)
    }
    void drawSelf(DrawCtx *ctx){
        //更新矩阵
        // self.material.model = self._world_transform
        // self.material.view = ctx.camera.view
        // self.material.projection = ctx.camera.projection
        ctx.setMvpToMaterial(self, self.material)
        ctx.setGlobalInfosToMaterial(self.material)

        self.vao.draw(
            self.geometry,
            self.material
        )
    }
    void drawDepth(DrawCtx *ctx){
        Material *matl = ctx.depthMatl

        //更新矩阵
        matl.model = self._world_transform
        matl.view = ctx.camera.view
        matl.projection = ctx.camera.projection
        matl.updateMvp()

        ctx.setGlobalInfosToMaterial(matl)

        self.depthVao.draw(
            self.geometry,
            matl
        )
    }

    bool hitTestSelfByRaycaster(Raycaster* raycaster){
		RayCheckResult r = raycaster.raycastGeometry(self, self.geometry)
        raycaster.result = r;
		return r.succ
	}
}
Billboard@ mkBillboard(void* parent, long long key){
    return (Billboard@)gocNode(
        key?(void*)key:__builtin_return_address(0),
        (Node*)parent, Billboard)
}
