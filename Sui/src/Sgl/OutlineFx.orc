package Sgl


// import * from "../Sui/Core/Timer.orc"
import * from "../Orc/String.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "./Tex2d.orc"
import * from "./Fbo.orc"
import * from "./Buffer.orc"
import * from "./Obj3d.orc"
import * from "./DrawCtx.orc"
import * from "./Material.orc"
import * from "./Vao.orc"
import * from "./GeometryFullscreenQuad.orc"


// 基于后处理，实现outline 效果
// 流程：
// 指定Obj3d, 绘制到fbo
// 基于边(sdf? 边缘检测?)距离决定颜色的matl 以addtivie的方式绘制到屏幕。 
class OutlineFx {
    Fbo@ fbo 
    Fbo@ fboEdge
    Material@ maskMatl = new Material()
    Material@ drawMatl = new Material()
    Vao@ vao = new Vao()
    Vao@ vaoQuad = new Vao()
    GeometryFullscreenQuad@ fsQuad = new GeometryFullscreenQuad()

    void init(){
        self.maskMatl.load("../asset/outlineMask.matl.json")
        self.drawMatl.load("../asset/outlineDraw.matl.json")
        self.fsQuad.build()
    }

    bool needUpdateFbo(Vec2 targetSize){
        if self.fbo == null {
            return true
        }
        Vec2 size = self.fbo.getSize()

        if !size.equals(targetSize){
            return true
        }
        return false
    }
    void updateFbo(Vec2 size){
        if self.needUpdateFbo(size){
            self.fbo = new Fbo()
            self.fbo.buildWithColorDepthStencilTexture(
                size.width(), size.height(),
                true, 
                false, 
                false
            )
            // self.fbo.tex2d.setWrapClampToEdge()
            self.fbo.tex2d.setWrapClampToBorder(0x00000000)
            self.fbo.tex2d.updateParameters()

            self.fboEdge = new Fbo()
            self.fboEdge.buildWithColorDepthStencilTexture(
                size.width(), size.height(),
                true, 
                false, 
                false
            )

        }
    }
    void drawMask(DrawCtx *ctx, Obj3d* obj3d){
        self.fbo.startDraw(0.0, 0.0, 0.0, 0.0, true, true, true)
        obj3d.drawSelfRaw(ctx, self.vao, self.maskMatl)
        self.fbo.endDraw()
    }
    void drawFxQuad(){
        self.drawMatl.setUniformTex2d("tex", self.fbo.tex2d)
        self.drawMatl.setUniformVec2("texSize", self.fbo.getSize())
        self.vaoQuad.draw(self.fsQuad, self.drawMatl)
    }
    void draw(DrawCtx* ctx, Obj3d* obj3d, Fbo* targetFbo){
        self.updateFbo(ctx.frameSize)

        // self.camera.aspect = fboSize.x / fboSize.y
        // 绘制到fbo
        self.drawMask(ctx, obj3d)

        // 边缘检测，以additive的方式绘制到屏幕
        // self.fboEdge.startDraw(0.0, 0.0, 0.0, 0.0, true, true, true)

        if targetFbo { //目标也是fbo,需要重新绑定
            targetFbo.bind()
        }

        self.drawFxQuad()

        // self.fboEdge.endDraw()
    }

}