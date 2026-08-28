module;

#include "GL/glew.h"
#include "GL/wglew.h"
#include "Core/Timer.h"
#include "Core/Color.h"
#include "Core/Mat.h"
#include "View/ImageView.h"
#include "View/Drag.h"
#include "Naga/Path.h"
#include "Naga/StrUtil.h"

export module Sgl:FboView;

import :Fbo;
import :DrawCtx;
import :Scene;
import :Mesh;
import :PerspectiveCamera;
import :PointLight;



export class FboView : public ImageView {
public:
    Ref < Fbo> fbo{ nullptr, this };
    Ref < DrawCtx> drawCtx = new DrawCtx();
        Ref<Scene> scene{ nullptr, this };
        Ref < PerspectiveCamera> camera{ nullptr, this };

        Ref < Mesh> groundGrid{ new Mesh(), this };
        Ref < Drag> drag  { new Drag(), this };
        Ref<Closure<void(FboView * s)>> cbDraw{ nullptr, this };

        void dragOrbit(Drag * d) {
            Euler e;
            e.setFromVector3(this->camera->rotation, nullptr);

            e.reorder("YXZ");
            e.y += d->deltaPos.x * 0.001;
            e.x += d->deltaPos.y * 0.001;
            e.reorder("XYZ");

            this->camera->rotation.setFromEuler(e);
    }

    FboView() {
        this->mkBaseScene();

        this->drag->onDrag = CLOSURE(
            [=](Drag* d) {
                if (d->isDragging) {
                    printf("dragging scene\n");
                        this->dragOrbit(d);
                        // this->camera.rotation.y += d.deltaPos.x * 0.001
                        // this->camera.rotation.x += d.deltaPos.y * 0.001
                }
            });

        //{

        //    GeometryPlane@ geom = new GeometryPlane()
        //        geom.planeType = 1
        //        geom.width = 10000
        //        geom.height = 10000
        //        geom.widthSegments = 100
        //        geom.heightSegments = 100
        //        geom.build()

        //        this->groundGrid.geometry = geom

        //        Material@ matl = new Material()
        //        matl.load(Path_resolveFromExecutionDir("../asset/basic.matl.json").str)
        //        this->groundGrid.material = matl
        //}

    }


    void draw_self(Canvas* canvas) {
        if (this->frame.width <= 0 || this->frame.height <= 0) {
            return;
        }
        if (1) {
            bool mkFbo = false;
                if (this->fbo == nullptr){
                    mkFbo = true;
                }
                else if (this->fbo) {
                    Vec2 size = this->fbo->getSize();
                    if (size.x != (int)this->frame.width || size.y != (int)this->frame.height) {
                        mkFbo = true;
                    }
                }
                    if (mkFbo) {
                        printf("重建fbo. size:%f,%f\n", this->frame.width, this->frame.height);
                        this->fbo = new Fbo();
                        this->fbo->buildWithColorDepthStencilTexture(
                            (int)this->frame.width, (int)this->frame.height,
                            true,
                            true,
                            false
                        );
                    }
        }
        this->backgroundColor = 0xff00ff00;
            if (this->fbo){
                Vec2 fboSize = this->fbo->getSize();
                this->camera->aspect = fboSize.x / fboSize.y;
                //绘制fbo
                this->fbo->startDraw(0.0, 0.0, 0.0, 1.0, true, true, true);

                this->drawCtx->frameSize = fboSize;
                this->drawCtx->draw(this->scene, this->camera);

                // this->mesh.draw(this->drawCtx)

                if (this->cbDraw ){
                    this->cbDraw->invoke(this);
                }
                this->groundGrid->draw(this->drawCtx);

                this->fbo->endDraw();

                this->_img = loadImageByTex2d(this->fbo->tex2d);
            }
            ImageView::draw_self(canvas);

    }

    void onEvent(Event* e) {
        if ( dynamic_cast< MouseEvent *>(e)){
            MouseEvent* me = (MouseEvent*)e;
                if (me->button == 1 && me->isMouseDown && me->isBubble()) {
                    this->drag->onMouseDown(me);
                }
        }
    }
    void mkBaseScene() {
        this->scene = new Scene();
        this->camera = new PerspectiveCamera();

            // Initialize camera with default values
            // this->camera.target = mkVec3(0, 0, 0)
        this->camera->up = mkVec3(0, 1, 0);
        this->camera->fov = 45 / 180.0 * PI;
        this->camera->aspect = 1.0;
        this->camera->nearPlane = 100.1;
        this->camera->farPlane = 5000;

            // Position camera
            // this->camera.position = mkVec3(100, 300, 500)
        this->camera->position = mkVec3(100, 500, 500);

        this->camera->updateWorldMatrixUptoRoot();
        this->camera->lookAt(0, 0, 0);


            // Update camera matrices; 不用调。在draw时会调
            // this->camera.updateProjectionMat()
            // this->camera.updateViewMat()

            // Add camera to scene
        this->scene->appendChild(this->camera);
            // this->scene.appendChild(this->mesh)

            //添加灯

            // {
            //     DirLight@ l = new DirLight()
            //     l.position.set(0, 10, 0)
            //     this->scene.appendChild(l)
            // }
        {
            auto o = Ref(new PointLight());
            o->position.set(300, 300, 300);
            this->scene->appendChild(o);
        }

        printf("Base scene and camera initialized\n");
    }
};




