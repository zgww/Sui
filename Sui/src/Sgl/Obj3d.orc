package Sgl

#include <stdio.h>


import * from "../Sui/Core/Node.orc"
import * from "../Orc/String.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Euler.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/Core/Quaternion.orc"
import * from "./Mat.orc"
import * from "./Ray.orc"
import type * from "./DrawCtx.orc"
import * from "./Raycaster.orc"
import * from "./Material.orc"
import * from "./Vao.orc"


class Obj3d extends Node {
    String@ objid
    Vec3 position
    Vec3 rotation // euler
    Vec3 scale = mkVec3(1.0, 1.0, 1)

    Rgba rgba = mkRgbaByInt(0xffff0000)
    int textColor = 0xff00ff00

    Quaternion quaternion;

    Vec3 _viewPosition

    Vec3 up = mkVec3(0, 1, 0);


    Mat transform = mkMatIdentity();
    Mat _world_transform = mkMatIdentity();

    bool visible = true

    String@ gocId(){

        if (!self.objid){
            self.objid = str("")
            self.objid.addll((long long)self)
        }
        return self.objid
    }

    Vec3 worldToLocal(Vec3 v3){
        Vec4 v4 = mkVec4(v3.x, v3.y, v3.z, 1.0)
        Mat inv = self._world_transform.invert()
        Vec4 ret = inv.mulVec4(v4)
        return mkVec3(ret.x, ret.y, ret.z)
    }

    Vec3 localToWorld(Vec3 v3){
        Vec4 v4 = mkVec4(v3.x, v3.y, v3.z, 1.0)
        Vec4 ret = self._world_transform.mulVec4(v4)
        return mkVec3(ret.x, ret.y, ret.z)
    }

    void updateTransform(){
        // self.transform.identity()
        // self.transform.makeTranslation(self.position.x, self.position.y, self.position.z)
        // // self.transform.setTranslate(self.position.x, self.position.y, self.position.z)
        // self.transform.scale(self.scale.x, self.scale.y, self.scale.z)
        // self.transform.rotateX(self.rotation.x)
        // self.transform.rotateY(self.rotation.y)
        // self.transform.rotateZ(self.rotation.z)


        Quaternion q
        Euler e
        e.set(self.rotation.x, self.rotation.y, self.rotation.z, null)
        q.setFromEuler(e)

        self.transform.compose(self.position, q, self.scale)
    }

    //更新子树矩阵
    void updateWorldTransformAndSubtree(){
        //更新transform
        self.updateTransform()
        // self.transform.identity()
        // self.transform.setTranslate(self.position.x, self.position.y, self.position.z)
        // self.transform.scale(self.scale.x, self.scale.y, self.scale.z)
        // self.transform.rotateX(self.rotation.x)
        // self.transform.rotateY(self.rotation.y)
        // self.transform.rotateZ(self.rotation.z)



        if self.parent && self.parent instanceof Obj3d {
            Obj3d* p = (Obj3d*)self.parent
            self._world_transform.mul(
                &p._world_transform, 
                &self.transform
            )
        }
        else {
            self._world_transform = self.transform
        }
        // Vec3 wpos = self.localToWorld(mkVec3(0, 0, 0))

        self.updateChildrenWorldTransform()
    }
    void updateChildrenWorldTransform(){
        int l = self.getChildrenCount()
        for (int i = 0; i < l; i++) {
            Node* view = self.getChild(i);
            if view instanceof Obj3d {
                Obj3d* obj = (Obj3d*)view;
                if (obj.visible){ //&& view->style.display != DISPLAY_TYPE_NONE) {
                    obj.updateWorldTransformAndSubtree()
                }
            }
        }
    }

    // //收集
    // void collectTransparent(DrawCtx *ctx){
    // }

    void drawDepth(DrawCtx *ctx){
    }
    void draw(DrawCtx *ctx){
        self.drawSelf(ctx)
        self.drawChildren(ctx)
    }
    //在draw中，如果发现material需要在transparent中绘制，就可以调用ctx的方法加入到transparentList中
    void drawTransparent(DrawCtx *ctx){
        self.drawSelf(ctx)
    }

    void drawSelfRaw(DrawCtx* ctx, Vao* vao, Material* matl){
    }
    void drawSelf(DrawCtx *ctx){
    }
    void drawChildren(DrawCtx *ctx){
        int l = self.getChildrenCount()
        for (int i = 0; i < l; i++) {
            Node* view = self.getChild(i);
            if view instanceof Obj3d {
                Obj3d* obj = (Obj3d*)view;
                if (obj.visible){ //&& view->style.display != DISPLAY_TYPE_NONE) {
                    obj.draw(ctx);
                }
            }
        }
    }
    void tick(DrawCtx *ctx){
    }
    //结果放到raycaster.result中
    bool hitTestSelfByRaycaster(Raycaster* raycaster){
        return false
    }

    // 令正z轴朝向目标位置
    void lookAt( float x, float y, float z){
        self.lookAtByDir(false, x, y, z)
    }
}
extension Obj3d {

    //更新世界矩阵，从自己到根结点
    void updateWorldMatrixUptoRoot(){
        self.updateTransform()

        Obj3d *parent = (Obj3d*)self.parent
        if parent != null && parent instanceof Obj3d {
            parent.updateWorldMatrixUptoRoot()
            self._world_transform.multiplyMatricesLocal(parent._world_transform, self.transform)
        }
        else {//说明自己就是根
            self._world_transform.copy(self.transform)
        }
    }

    // 相机以负轴为前方，需要negativeZ=true
    // 普通的obj以正轴为前方
    void lookAtByDir(bool negativeZ, float x, float y, float z){
		Obj3d * parent = (Obj3d*)self.parent;
        if ! (parent instanceof Obj3d) {
            return
        }

		// self.updateWorldMatrix( true, false );

        Vec3 _target = mkVec3(x, y, z)
        Vec3 _position;
		_position.setFromMatrixPosition( self._world_transform );
        Mat _m1

		if negativeZ { // ( this.isCamera || this.isLight ) {

			_m1.lookAtLocal( _position, _target, self.up );

		} else {

        //注意eye和目标点的位置。
            _m1.lookAtLocal( _target, _position, self.up );

		}

		self.quaternion.setFromRotationMatrix( _m1 );

		if ( parent ) {
            Quaternion _q1;

			_m1.extractRotationLocal( parent._world_transform );
			_q1.setFromRotationMatrix( _m1 );
			self.quaternion.premultiplyLocal( *_q1.invertLocal() );

		}
        Euler euler;
        euler.setFromQuaternion(self.quaternion, Euler_Default)
        self.rotation.setFromEuler(euler)
    }
}