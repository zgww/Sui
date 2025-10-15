package Sgl

#include <stdio.h>
#include <assimp/cimport.h>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Path.orc"
import * from "./Obj3d.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/Color.orc"
import * from "../Sui/View/TreeView.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/SplitterView.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "./Mesh.orc"
import * from "./FboView.orc"
import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Geometry.orc"
import * from "./Material.orc"
import * from "../SuiDesigner/Insp.orc"


struct aiMaterialProperty* assimp_getMaterialPropByName(struct aiMaterial* matl, const char *name){
    for int j = 0; j < matl.mNumProperties; j++{
        struct aiMaterialProperty *prop = matl.mProperties[j]
        if strcmp(prop.mKey.data, name) == 0 {
            return prop;
        }
    }
    return null
}
const char *assimp_getMaterialName(struct aiMaterial* matl){
    struct aiMaterialProperty* prop = assimp_getMaterialPropByName(matl, "?mat.name")
    if prop {
        struct aiString* s = (struct aiString*)prop.mData;
        return s->data;
    }
    return null
}
class AssimpLoader {
    String@ path
    struct aiScene *scene;

    Obj3d@ rootObj3d


    // List<Material>
    List@ materials = new List()

    //融合后的材质。 ModelLoader 可以覆盖材质。
    List@ mergedMaterials = null

    void dtor(){
        if self.scene {
            // 释放资源
            aiReleaseImport(self.scene);
        }
    }

    Obj3d@ buildSglTree(){
        self.buildGeometries()
        self.buildMaterials()

        self.rootObj3d = self.buildNode(null, self.scene.mRootNode, 0, 0)
        return self.rootObj3d
    }
    void buildMaterials(){
        self.materials.clear()
        for int i = 0; i < self.scene.mNumMaterials; i++{
            struct aiMaterial* aimtl = self.scene.mMaterials[i]
            //转为blinn-phong光照模型
            Material@ matl = new Material()
            matl.load("../asset/blinn-phong.matl.json")
            self.materials.add(matl)


            //散射
            Rgbaf clrDiffuse = mkRgbaf0();
            Rgbaf clrEmissive = mkRgbaf0();
            Rgbaf clrAmbient = mkRgbaf0();
            Rgbaf clrSpecular = mkRgbaf0();
            Rgbaf clrTransparent = mkRgbaf0();
            Rgbaf clrReflective = mkRgbaf0();

            int shadingModel = 0
            float matShinpercent = 0.0
            float matShininess = 0.0
            float matRoughnessFactor = 0.0
            float matTransparencyfactor = 0.0
            float matOpacity = 0.0
            float matReflectivity = 0.0
            float matBumpscaling = 0.0
            float matDisplacementscaling = 0.0
            String@ texFile = str("") // 纹理路径
            float texUvTrafo = 0.0//uv transform
            int texUvwSrc = 0 // uv channel . 采用哪一套uv

            //aiGetMaterial系列函数的参数 type/index,只对纹理有用。其他类型的值，都是0

            aiGetMaterialColor(aimtl, "$clr.diffuse", 0, 0, (struct aiColor4D*)&clrDiffuse);
            aiGetMaterialColor(aimtl, "$clr.emissive", 0, 0, (struct aiColor4D*)&clrEmissive);
            aiGetMaterialColor(aimtl, "$clr.ambient", 0, 0, (struct aiColor4D*)&clrAmbient);
            aiGetMaterialColor(aimtl, "$clr.specular", 0, 0, (struct aiColor4D*)&clrSpecular);
            aiGetMaterialColor(aimtl, "$clr.transparent", 0, 0, (struct aiColor4D*)&clrTransparent);
            aiGetMaterialColor(aimtl, "$clr.reflective", 0, 0, (struct aiColor4D*)&clrReflective);

            aiGetMaterialInteger(aimtl, "$mat.shadingm", 0, 0, &shadingModel)
            aiGetMaterialFloat(aimtl, "$mat.shinpercent", 0, 0, &matShinpercent)
            aiGetMaterialFloat(aimtl, "$mat.shininess", 0, 0, &matShininess)
            aiGetMaterialFloat(aimtl, "$mat.roughnessFactor", 0, 0, &matRoughnessFactor)
            aiGetMaterialFloat(aimtl, "$mat.transparencyfactor", 0, 0, &matTransparencyfactor)
            aiGetMaterialFloat(aimtl, "$mat.opacity", 0, 0, &matOpacity)
            aiGetMaterialFloat(aimtl, "$mat.reflectivity", 0, 0, &matReflectivity)
            aiGetMaterialFloat(aimtl, "$mat.bumpscaling", 0, 0, &matBumpscaling)
            aiGetMaterialFloat(aimtl, "$mat.displacementscaling", 0, 0, &matDisplacementscaling)

            //暂只支持一个纹理。。。
            struct aiString aiTexFile;
            aiTexFile.data[0] = 0;
            if AI_SUCCESS == aiGetMaterialString(aimtl, "$tex.file", 1, 0, &aiTexFile){
                texFile = str(aiTexFile.data)
            }

            //应用属性到材质
            matl.setUniformRgbaf("diffuse", clrDiffuse)
            matl.setUniformRgbaf("emissive", clrEmissive)
            matl.setUniformRgbaf("ambient", clrAmbient)
            matl.setUniformRgbaf("specular", clrSpecular)
            matl.setUniformRgbaf("transparent", clrTransparent)
            matl.setUniformRgbaf("reflective", clrReflective)

            matl.setUniform1f("shinpercent", matShinpercent)
            matl.setUniform1f("shininess", matShininess)
            matl.setUniform1f("roughnessFactor", matRoughnessFactor)
            matl.setUniform1f("transparencyfactor", matTransparencyfactor)
            matl.setUniform1f("opacity", matOpacity)
            matl.setUniform1f("reflectivity", matReflectivity)
            matl.setUniform1f("bumpscaling", matBumpscaling)
            matl.setUniform1f("displacementscaling", matDisplacementscaling)

            if texFile.notEmpty() {
                String@ actualPath = Path_resolveRelativeFromFile(texFile.str, self.path.str)
                matl.setUniformTex2dByPath("tex", actualPath.str)
                // matl.setUniformTex2dByPath("tex", "./SpongeBob.png")
                // matl.setUniformTex2dByPath("tex", "engineflare1.jpg")
                // matl.setUniformTex2dByPath("tex", "SpiderTex.jpg")
                // matl.setUniformTex2dByPath("tex", "SpiderTex2.png")
            }
        }
    }

    List@ geometries = new List()
    void buildGeometries(){
        self.geometries.clear()
        for int i = 0; i < self.scene.mNumMeshes; i++{
            struct aiMesh* mesh = self.scene.mMeshes[i]
            Buffer@ vertices = new Buffer();
            Buffer@ normals = new Buffer();
            Buffer@ uvs = new Buffer();
            Buffer@ faces = new Buffer();
            Buffer@ colors = new Buffer();
            
            float scale = 1.0;

            for int i = 0; i < mesh.mNumVertices; i++ {
                // has = true;
                Vec3 v3;
                v3.x = mesh.mVertices[i].x / scale;
                v3.y = mesh.mVertices[i].y / scale;
                v3.z = mesh.mVertices[i].z / scale;

                //目前只支持一套uv, 2个数字
                struct aiVector3D *aiUvs = mesh.mTextureCoords[0]
                if aiUvs != null {
                    uvs.appendFloat2(
                        aiUvs[i].x,
                        aiUvs[i].y,
                    )
                }
                struct aiColor4D *aiColors = mesh.mColors[0]
                if aiColors != null {
                    colors.appendFloat4(
                        aiColors[i].r,
                        aiColors[i].g,
                        aiColors[i].b,
                        aiColors[i].a,
                    )
                }


                Vec3 n;
                n.x = mesh.mNormals[i].x;
                n.y = mesh.mNormals[i].y;
                n.z = mesh.mNormals[i].z;
                vertices.appendVec3(v3)
                normals.appendVec3(v3)
            }

            // 处理索引
            for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
                struct aiFace* face = mesh->mFaces + i;
                for(unsigned int j = 0; j < face.mNumIndices; j++){
                    int idx = face.mIndices[j] ;
                    faces.appendInt(idx);
                }
            }


            Geometry@ g = new Geometry()

            g.setAttrByBuffer("position", vertices, 3)
            g.setAttrByBuffer("normal", normals, 3)
            g.setAttrByBuffer("color", colors, 4)
            g.setAttrByBuffer("uv", uvs, 2)
            g.setIboByBuffer(faces)


            self.geometries.add(g)
        }
    }

    Obj3d@ buildNode(Obj3d* parent, struct aiNode* node, int idx, int deep){
        Obj3d@ ret = null
        if node.mNumMeshes == 0 {
            ret = new Obj3d()
        }
        else {
            Mesh@ mesh = new Mesh()
            //填充mesh
            if node.mNumMeshes > 0 {
                int idx = node.mMeshes[0]
                Geometry* geom = (Geometry*)self.geometries.get(idx)
                mesh.geometry = geom

                struct aiMesh* aimesh = self.scene.mMeshes[idx]

                Material* matl = self.materials.get(aimesh.mMaterialIndex)
                if self.mergedMaterials {
                    matl = self.mergedMaterials.get(aimesh.mMaterialIndex)
                }
                mesh.material = matl

                // new Material()~{
                //     o.load("../asset/basicSolid.matl.json")
                //     mesh.material = o
                // }
            }

            ret = mesh
        }
        if parent {
            parent.appendChild(ret)
        }

        // 递归处理子节点
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            self.buildNode(ret, node->mChildren[i], i, deep+1);
        }
        return ret
    }
    void drawFboView(FboView* fboView){
        if self.rootObj3d {
            self.rootObj3d.draw(fboView.drawCtx)
        }
    }
    void onDragFboView(Drag* d){
        if d.isDragging {
            //旋转
            if self.rootObj3d {
                self.rootObj3d.rotation.y += d.deltaPos.x * 0.01;
                self.rootObj3d.updateWorldTransformAndSubtree()
                printf("旋转模型\n")
            }
        }
    }

    void reactMetaData(Node* o, struct aiMetadata *mMetaData, int deep){
        for int i = 0; i < mMetaData.mNumProperties; i++{
            struct aiString *key = mMetaData.mKeys + i
            struct aiMetadataEntry *value = mMetaData.mValues + i;
            char valueStr[512];
            if value.mType == AI_BOOL {
                sprintf(valueStr, "%d", *((bool*)value.mData))
            }
            else if value.mType == AI_INT32 {
                sprintf(valueStr, "%d", *((int*)value.mData))
            }
            else if value.mType == AI_UINT32 {
                sprintf(valueStr, "%u", *((unsigned int*)value.mData))
            }
            else if value.mType == AI_INT64 {
                sprintf(valueStr, "%lld", *((long long*)value.mData))
            }
            else if value.mType == AI_AIVECTOR3D {
                struct aiVector3D *pv = (struct aiVector3D*)value.mData
                sprintf(valueStr, "Vec3(%f,%f,%f)", pv.x, pv.y, pv.z)
            }
            else if value.mType == AI_UINT64 {
                sprintf(valueStr, "%llu", *((unsigned long long*)value.mData))
            }
            else if value.mType == AI_FLOAT {
                sprintf(valueStr, "%f", *((float*)value.mData))
            }
            else if value.mType == AI_DOUBLE {
                sprintf(valueStr, "%f", *((double *)value.mData))
            }
            else if value.mType == AI_AISTRING {
                struct aiString *ais = (struct aiString*)value.mData
                sprintf(valueStr, "%s", ais.data)
            }
            char tmp[1024];
            sprintf(tmp, "%d %s =%s\n", 
                i, 
                key.data,
                valueStr,
            )
            mkTreeSelfCtrlView(o, ((long long)mMetaData) * 1000 + (long long)key).{
                o.deep = deep
                o.hasKids = true
                mkTextView(o, 0).{
                    o.setText(str(tmp))
                }
            }
        }
    }

    String@ loadMaterialPropertyValueToString(struct aiMaterialProperty* prop){
        char tmp[512];
        tmp[0] = 0;

        if prop.mType == aiPTI_Float {
            for int i = 0; i < prop.mDataLength / 4; i++{
                sprintf(tmp, "%s %f", tmp, *(((float*)prop.mData) + i));
            }
        }
        else if prop.mType == aiPTI_Double {
            for int i = 0; i < prop.mDataLength / 8; i++{
                sprintf(tmp, "%s %f", tmp, *(((double*)prop.mData)) + i);
            }
        }
        else if prop.mType == aiPTI_Integer {
            for int i = 0; i < prop.mDataLength / 4; i++{
                sprintf(tmp, "%s %d", tmp, *(((int*)prop.mData))+i);
            }
        }
        else if prop.mType == aiPTI_String {
            struct aiString* s = (struct aiString*)prop.mData;
            sprintf(tmp, "%s%s", tmp, s->data);
        }
        else if prop.mType == aiPTI_Buffer {
            sprintf(tmp, "ints:");
            for int i = 0; i < prop.mDataLength / 4; i++{
                sprintf(tmp, "%s %d", tmp, *(((int*)prop.mData)) + i);
            }
            sprintf(tmp, "%s floats:", tmp);
            for int i = 0; i < prop.mDataLength / 4; i++{
                sprintf(tmp, "%s %f", tmp, *(((float*)prop.mData)) + i);
            }
        }
        return str(tmp)
    }

    void showWindow(){
        new Window()~{
            Window* win = o
            new LayoutLinear().{
                // o.backgroundColor = 0xff33ff00
                o.aiStretch()
                win.setRootView(o)

                mkFboView(o, 0).{
                    o.drag.onDrag = ^void(Drag*d){
                        self.onDragFboView(d)
                    }
                    o.cbDraw = ^void(FboView* fboView){
                        self.drawFboView(fboView)
                    }
                    layoutLinearCell(o, 0)
                }

                mkSplitterView(o, 0).{}

                mkScrollArea(o, 0).{
                    layoutLinearCell(o, 0)

                    o.column().aiStretch()
                    // o.backgroundColor = 0xffffffff

                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("元数据").addi(self.scene.mMetaData->mNumProperties))
                        }
                    }
                    self.reactMetaData(o, self.scene.mMetaData, 1)
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("材质").addi(self.scene.mNumMaterials))
                        }
                    }
                    for int i = 0; i < self.scene.mNumMaterials; i++{
                        struct aiMaterial *e = self.scene.mMaterials[i]
                        char tmp[1024];
                        sprintf(tmp, "%d %s numProperty=%d\n", 
                            i, 
                            assimp_getMaterialName(e),
                            e.mNumProperties
                        )
                        mkTreeSelfCtrlView(o, (long long)e).{
                            o.deep = 1
                            o.hasKids = true
                            mkTextView(o, 0).{
                                o.setText(str(tmp))
                            }
                        }
                        for int j = 0; j < e.mNumProperties; j++{
                            struct aiMaterialProperty *prop = e.mProperties[j]
                            String@ value = self.loadMaterialPropertyValueToString(prop)
                            sprintf(tmp, "%3d %s semantic:%d, iddx:%d, dataLength:%d type:%d %s", j, prop.mKey.data, prop.mSemantic, prop.mIndex, prop.mDataLength, prop.mType, value.str);
                            // if prop.mType == aiPTI_Float {
                            //     sprintf(tmp, "%s%f", tmp, *((float*)prop.mData));
                            // }
                            // else if prop.mType == aiPTI_Double {
                            //     sprintf(tmp, "%s%f", tmp, *((double*)prop.mData));
                            // }
                            // else if prop.mType == aiPTI_Integer {
                            //     sprintf(tmp, "%s%d", tmp, *((int*)prop.mData));
                            // }
                            // else if prop.mType == aiPTI_String {
                            //     struct aiString* s = (struct aiString*)prop.mData;
                            //     sprintf(tmp, "%s%s", tmp, s->data);
                            // }
                            // printf("\n")
                            mkTreeSelfCtrlView(o, (long long)e).{
                                o.deep = 2
                                o.hasKids = false
                                mkTextView(o, 0).{
                                    o.setText(str(tmp))
                                }
                            }
                        }
                    }
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("动画#").addi(self.scene.mNumAnimations))
                        }
                    }
                    for int i = 0; i < self.scene.mNumAnimations; i++{
                        struct aiAnimation *anim = self.scene.mAnimations[i]
                        char tmp[1024]
                        sprintf(tmp, "%s dura=%f, ticksPs:%f, channels:%d meshChannel:%d  morphChannel:%d\n", 
                            anim.mName.data, anim.mDuration, anim.mTicksPerSecond, 
                            anim.mNumChannels, 
                            anim.mNumMeshChannels, 
                            anim.mNumMorphMeshChannels, 
                        )
                        mkTreeSelfCtrlView(o, (long long)anim).{
                            o.deep = 1
                            o.hasKids = false
                            mkTextView(o, 0).{
                                o.setText(str(tmp))
                            }
                        }
                    }
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("纹理").addi(self.scene.mNumTextures))
                        }
                    }
                    for int i = 0; i < self.scene.mNumTextures; i++{
                        struct aiTexture *tex = self.scene.mTextures[i]
                        char tmp[1024]
                        sprintf(tmp, "%s w=%d, h=%d, achFormatHint=%s\n", 
                            tex.mFilename.data, 
                            tex.mWidth,
                            tex.mHeight,
                            tex.achFormatHint
                        )
                        mkTreeSelfCtrlView(o, (long long)tex).{
                            o.deep = 1
                            o.hasKids = false
                            mkTextView(o, 0).{
                                o.setText(str(tmp))
                            }
                        }
                    }
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("网格").addi(self.scene.mNumMeshes))
                        }
                    }
                    for int i = 0; i < self.scene.mNumMeshes; i++{
                        struct aiMesh *e = self.scene.mMeshes[i]
                        char tmp[1024]
                        sprintf(tmp, "%s type=%d vtx=%d face=%d bones=%d matlIdx=%d animMeshes=%d method=%d, aabb=%f,%f,%f; %f,%f,%f\n", 
                            e.mName.data, 
                            e.mPrimitiveTypes,
                            e.mNumVertices,
                            e.mNumFaces,
                            e.mNumBones,
                            e.mMaterialIndex,
                            e.mNumAnimMeshes,
                            e.mMethod, 
                            e.mAABB.mMin.x,
                            e.mAABB.mMin.y,
                            e.mAABB.mMin.z,
                            e.mAABB.mMax.x,
                            e.mAABB.mMax.y,
                            e.mAABB.mMax.z,
                        )
                        mkTreeSelfCtrlView(o, (long long)e).{
                            o.deep = 1
                            o.hasKids = false
                            mkTextView(o, 0).{
                                o.setText(str(tmp))
                            }
                        }

                    }
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("灯光").addi(self.scene.mNumLights))
                        }
                    }
                    for int i = 0; i < self.scene.mNumLights; i++{
                        struct aiLight *e = self.scene.mLights[i]
                        char tmp[1024];
                        sprintf(tmp, "%s type=%d,%s pos=%f,%f,%f dir=%f,%f,%f up=%f,%f,%f atte=%f,%f,%f, cone=%f,%f size=%f,%f\n", 
                            e.mName.data,
                            e.mType,
                            e.mType == aiLightSource_DIRECTIONAL ? "dir"
                            : e.mType == aiLightSource_POINT ? "point"
                            : e.mType == aiLightSource_SPOT ? "sport"
                            : e.mType == aiLightSource_AMBIENT ? "ambient"
                            : e.mType == aiLightSource_AREA ? "area"
                            : "undef",

                            e.mPosition.x,
                            e.mPosition.y,
                            e.mPosition.z,

                            e.mDirection.x,
                            e.mDirection.y,
                            e.mDirection.z,

                            e.mUp.x,
                            e.mUp.y,
                            e.mUp.z,
                            
                            e.mAttenuationConstant,
                            e.mAttenuationLinear,
                            e.mAttenuationQuadratic,

                            e.mAngleInnerCone,
                            e.mAngleOuterCone,

                            e.mSize.x,
                            e.mSize.y,
                        )
                        mkTreeSelfCtrlView(o, (long long)e).{
                            o.deep = 1
                            o.hasKids = false
                            mkTextView(o, 0).{
                                o.setText(str(tmp))
                            }
                        }
                    }
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("相机").addi(self.scene.mNumCameras))
                        }
                    }
                    for int i = 0; i < self.scene.mNumCameras; i++{
                        struct aiCamera *e = self.scene.mCameras[i]
                        char tmp[1024]
                        sprintf(tmp, "\t%s pos=%f,%f,%f up=%f,%f,%f lookAt=%f,%f,%f fov=%f near=%f far=%f aspect=%f orthorWidth=%f\n", 
                            e.mName.data,

                            e.mPosition.x,
                            e.mPosition.y,
                            e.mPosition.z,

                            e.mUp.x,
                            e.mUp.y,
                            e.mUp.z,

                            e.mLookAt.x,
                            e.mLookAt.y,
                            e.mLookAt.z,
                            
                            e.mHorizontalFOV,
                            e.mClipPlaneNear,
                            e.mClipPlaneFar,
                            e.mAspect,
                            e.mOrthographicWidth,
                        )
                        mkTreeSelfCtrlView(o, (long long)e).{
                            o.deep = 1
                            o.hasKids = false
                            mkTextView(o, 0).{
                                o.setText(str(tmp))
                            }
                        }
                    }
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("骨架").addi(self.scene.mNumSkeletons))
                        }
                    }
                    for int i = 0; i < self.scene.mNumSkeletons; i++{
                        struct aiSkeleton *e = self.scene.mSkeletons[i]
                        char tmp[1024];
                        sprintf(tmp, "%s bone=%d\n", 
                            e.mName.data,
                            e.mNumBones
                        )
                        mkTreeSelfCtrlView(o, (long long)e).{
                            o.deep = 1
                            o.hasKids = false
                            mkTextView(o, 0).{
                                o.setText(str(tmp))
                            }
                        }
                        for int j = 0; j < e.mNumBones; j++{
                            struct aiSkeletonBone* bone = e.mBones[j]
                            sprintf(tmp, "%2d numWeights=%d\n", 
                                j,
                                bone.mNumnWeights
                            )
                            mkTreeSelfCtrlView(o, (long long)e).{
                                o.deep = 2
                                o.hasKids = false
                                mkTextView(o, 0).{
                                    o.setText(str(tmp))
                                }
                            }
                            for int k = 0; k < bone.mNumnWeights; k++{
                                struct aiMesh* mesh = bone.mMeshId
                                struct aiVertexWeight* weight = bone.mWeights+k
                                sprintf(tmp, "%2d mesh=%s weight=%f vtxId=%d\n", k, mesh.mName.data, weight.mWeight, weight.mVertexId);
                                mkTreeSelfCtrlView(o, (long long)e).{
                                    o.deep = 3
                                    o.hasKids = false
                                    mkTextView(o, 0).{
                                        o.setText(str(tmp))
                                    }
                                }
                            }
                        }
                    }
                    mkTreeSelfCtrlView(o, (long long)0).{
                        o.deep = 0
                        o.hasKids = true
                        mkTextView(o, 0).{
                            o.setText(str("节点"))
                        }
                    }

                    self.mkNodeTreeView(o, self.scene.mRootNode, 0, 1)

                    // TreeSelfCtrlView_upate(o)
                }
            }

            o.setTitle(str("预览模型{0}").replaceAll("{0}", self.path.str).str)
            o.setSize(800, 600)
            o.moveToCenter()
            o.show()
        }
    }
    void mkNodeTreeView(Node* o, struct aiNode* node, int idx, int deep){
        String@ meshIds = str("")
        for int i = 0; i < node.mNumMeshes; i++{
            unsigned int meshIndex = node.mMeshes[i]
            meshIds.addi(meshIndex).add(",")
        }
        char tmp[1024];
        sprintf(tmp, "%4d %s nKids=%d, nMesh=%d meshIdxs=%s\n", idx, node.mName.data, node.mNumChildren, node.mNumMeshes, meshIds.str);

        mkTreeSelfCtrlView(o, (long long)node).{
            o.deep = deep
            o.hasKids = node.mNumChildren > 0 || node.mMetaData != null
            mkTextView(o, 0).{
                o.setText(str(tmp))
            }
        }
        if node.mMetaData {
            mkTreeSelfCtrlView(o, (long long)0).{
                o.deep = deep + 1
                o.hasKids = true
                mkTextView(o, 0).{
                    o.setText(str("元数据").addi(self.scene.mMetaData->mNumProperties))
                }
            }
            self.reactMetaData(o, node.mMetaData, deep + 2)
        }
        // 递归处理子节点
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            self.mkNodeTreeView(o, node->mChildren[i], i, deep+1);
        }
    }
    void load(const char *model_path){
        self.path = str(model_path)
        // 加载模型（使用默认后处理）
        struct aiScene* scene = aiImportFile(
            model_path,
            aiProcess_Triangulate       |   // 三角化多边形
            aiProcess_GenNormals        |   // 如果没有法线则生成
            aiProcess_FlipUVs           |   // 根据需要翻转 UV（OpenGL vs DirectX）
            aiProcess_JoinIdenticalVertices | // 合并重复顶点
            0
        );

        printf("assimp 加载模型:%s. scene:%p\n", model_path, scene)
        if !scene {
            const char *err = aiGetErrorString();
            printf("assimp load %s fail. err:%s\n", model_path, err);
            return
        }
        self.scene = scene
        self.printScene()

    }
    void printScene(){
        if self.scene {
            printf("---------------scene[%s; %s] flag:%d, anim:%d, tex:%d, mesh:%d, matl:%d light:%d, cam:%d, ske:%d---------------\n", 
                self.path.str ,
                self.scene.mName.data, 
                self.scene.mFlags,
                self.scene.mNumAnimations,
                self.scene.mNumTextures,
                self.scene.mNumMeshes,
                self.scene.mNumMaterials,
                self.scene.mNumLights,
                self.scene.mNumCameras,
                self.scene.mNumSkeletons,
            )
            printf("---------------animations---------------\n")
            for int i = 0; i < self.scene.mNumAnimations; i++{
                struct aiAnimation *anim = self.scene.mAnimations[i]
                printf("\t%s dura=%f, ticksPs:%f, channels:%d meshChannel:%d  morphChannel:%d\n", 
                    anim.mName.data, anim.mDuration, anim.mTicksPerSecond, 
                    anim.mNumChannels, 
                    anim.mNumMeshChannels, 
                    anim.mNumMorphMeshChannels, 
                )
            }
            printf("---------------textures---------------\n")
            for int i = 0; i < self.scene.mNumTextures; i++{
                struct aiTexture *tex = self.scene.mTextures[i]
                printf("\t%s w=%d, h=%d, achFormatHint=%s\n", 
                    tex.mFilename.data, 
                    tex.mWidth,
                    tex.mHeight,
                    tex.achFormatHint
                )
            }
            printf("---------------meshes---------------\n")
            for int i = 0; i < self.scene.mNumMeshes; i++{
                struct aiMesh *e = self.scene.mMeshes[i]
                printf("\t%s type=%d vtx=%d face=%d bones=%d matlIdx=%d animMeshes=%d method=%d, aabb=%f,%f,%f; %f,%f,%f\n", 
                    e.mName.data, 
                    e.mPrimitiveTypes,
                    e.mNumVertices,
                    e.mNumFaces,
                    e.mNumBones,
                    e.mMaterialIndex,
                    e.mNumAnimMeshes,
                    e.mMethod, 
                    e.mAABB.mMin.x,
                    e.mAABB.mMin.y,
                    e.mAABB.mMin.z,
                    e.mAABB.mMax.x,
                    e.mAABB.mMax.y,
                    e.mAABB.mMax.z,
                )

            }
            printf("---------------materials---------------\n")
            for int i = 0; i < self.scene.mNumMaterials; i++{
                struct aiMaterial *e = self.scene.mMaterials[i]
                printf("\t%d numProperty=%d\n", 
                    i, 
                    e.mNumProperties
                )
                for int j = 0; j < e.mNumProperties; j++{
                    struct aiMaterialProperty *prop = e.mProperties[j]
                    String@ value = self.loadMaterialPropertyValueToString(prop)
                    printf("\t\t%3d %s semantic:%d, iddx:%d, dataLength:%d type:%d %s", j, prop.mKey.data, prop.mSemantic, prop.mIndex, prop.mDataLength, prop.mType, value.str);
                    // if prop.mType == aiPTI_Float {
                    //     printf("%f", *((float*)prop.mData));
                    // }
                    // else if prop.mType == aiPTI_Double {
                    //     printf("%f", *((double*)prop.mData));
                    // }
                    // else if prop.mType == aiPTI_Integer {
                    //     printf("%d", *((int*)prop.mData));
                    // }
                    // else if prop.mType == aiPTI_String {
                    //     struct aiString* s = (struct aiString*)prop.mData;
                    //     printf("%s", s->data);
                    // }
                    printf("\n")
                }
            }
            printf("---------------lights---------------\n")
            for int i = 0; i < self.scene.mNumLights; i++{
                struct aiLight *e = self.scene.mLights[i]
                printf("\t%s type=%d,%s pos=%f,%f,%f dir=%f,%f,%f up=%f,%f,%f atte=%f,%f,%f, cone=%f,%f size=%f,%f\n", 
                    e.mName.data,
                    e.mType,
                    e.mType == aiLightSource_DIRECTIONAL ? "dir"
                    : e.mType == aiLightSource_POINT ? "point"
                    : e.mType == aiLightSource_SPOT ? "sport"
                    : e.mType == aiLightSource_AMBIENT ? "ambient"
                    : e.mType == aiLightSource_AREA ? "area"
                    : "undef",

                    e.mPosition.x,
                    e.mPosition.y,
                    e.mPosition.z,

                    e.mDirection.x,
                    e.mDirection.y,
                    e.mDirection.z,

                    e.mUp.x,
                    e.mUp.y,
                    e.mUp.z,
                    
                    e.mAttenuationConstant,
                    e.mAttenuationLinear,
                    e.mAttenuationQuadratic,

                    e.mAngleInnerCone,
                    e.mAngleOuterCone,

                    e.mSize.x,
                    e.mSize.y,
                )
            }
            printf("---------------cameras---------------\n")
            for int i = 0; i < self.scene.mNumCameras; i++{
                struct aiCamera *e = self.scene.mCameras[i]
                printf("\t%s pos=%f,%f,%f up=%f,%f,%f lookAt=%f,%f,%f fov=%f near=%f far=%f aspect=%f orthorWidth=%f\n", 
                    e.mName.data,

                    e.mPosition.x,
                    e.mPosition.y,
                    e.mPosition.z,

                    e.mUp.x,
                    e.mUp.y,
                    e.mUp.z,

                    e.mLookAt.x,
                    e.mLookAt.y,
                    e.mLookAt.z,
                    
                    e.mHorizontalFOV,
                    e.mClipPlaneNear,
                    e.mClipPlaneFar,
                    e.mAspect,
                    e.mOrthographicWidth,
                )
            }
            printf("---------------skeletons---------------\n")
            for int i = 0; i < self.scene.mNumSkeletons; i++{
                struct aiSkeleton *e = self.scene.mSkeletons[i]
                printf("\t%s bone=%d\n", 
                    e.mName.data,
                    e.mNumBones
                )
                for int j = 0; j < e.mNumBones; j++{
                    struct aiSkeletonBone* bone = e.mBones[j]

                    printf("\t\t%2d numWeights=%d\n", 
                        j,
                        bone.mNumnWeights
                    )
                    for int k = 0; k < bone.mNumnWeights; k++{
                        struct aiMesh* mesh = bone.mMeshId
                        struct aiVertexWeight* weight = bone.mWeights+k
                        printf("\t\t\t%2d mesh=%s weight=%f vtxId=%d\n", k, mesh.mName.data, weight.mWeight, weight.mVertexId);
                    }
                }
            }
            
            
            printf("------------------nodes-----------------\n")
            self.printNode(self.scene.mRootNode, 0, 1)
        }
    }
    void printNode(struct aiNode* node, int idx, int tabCount){
        String@ tab = str("") 
        tab.fillCount("\t", tabCount)
        String@ meshIds = str("")
        for int i = 0; i < node.mNumMeshes; i++{
            unsigned int meshIndex = node.mMeshes[i]
            meshIds.addi(meshIndex).add(",")
        }
        printf("%s%4d %s[nKids=%d, nMesh=%d;%s]\n", tab.str, idx, node.mName.data, node.mNumChildren, node.mNumMeshes, meshIds.str);
        // 递归处理子节点
        for (unsigned int i = 0; i < node->mNumChildren; ++i) {
            self.printNode(node->mChildren[i], i, tabCount+1);
        }

    }

}


// 模型加载器
// 材质的使用
// 加载模型，生成Mesh, geometry直接指定. 材质默认会由模型内部的材质转换得到。
// ModelLoader也提供materialPaths属性, 可以覆盖默认的材质。是list类型， 
// 根据index覆盖
// 如果材质有变化，就同步更新模型子树所使用的材质。
class ModelLoader extends Obj3d {
    Buffer@ vertices = new Buffer();
    Buffer@ normals = new Buffer();
    Buffer@ texCoords = new Buffer();
    Buffer@ faces = new Buffer();

    String@ path
    // Mesh@ mesh = new Mesh()

    Obj3d@ modelRoot
    //List<String>
    List@ materialPaths = new List()
    List@ _materialSlots = new List()
    AssimpLoader@ loader //= new AssimpLoader()

    void insp(Insp@ insp){
        new InspAttrMaterialList()~{o.bind(insp, "materialPaths", null); }
    }
    void ctor(){
        super.ctor()
        // new Material()~{
            // o.load("../asset/basic.matl.json")
            self.materialPaths.add(str("../asset/basic.matl.json"))
            self.materialPaths.add(str("../asset/basic.matl.json"))
            self.materialPaths.add(str("../asset/basic.matl.json"))
            self.materialPaths.add(str("../asset/basic.matl.json"))
        // }
    }
    void setMaterialPaths(List* list){
        self.materialPaths = list
        self.updateMaterialSlots()

        if self.modelRoot != null {//重建树
            self.generateModelRoot()
        }
    }

    void updateMaterialSlots(){
        self._materialSlots.clear()
        if self.loader {
            for int i = 0; i < self.loader.materials.size(); i++{
                //是否有覆盖
                String* path = self.materialPaths.get(i)
                if path {
                    new Material()~{
                        o.load(path.str)
                        self._materialSlots.set(i, o)
                    }
                }
                else {
                    Material* matl = (Material*)self.loader.materials.get(i)
                    self._materialSlots.set(i, matl)
                }
            }
        }
    }
    void onMounted(){
        self.updateMaterialSlots()
        if self.loader {
            self.loader.mergedMaterials = self._materialSlots
        }
        if self.modelRoot == null {
            self.generateModelRoot()
        }
    }
    void generateModelRoot(){
        if self.modelRoot {
            self.modelRoot.removeSelf()
        }
        self.modelRoot = self.loader.buildSglTree()
        self.appendChild(self.modelRoot)
        printNodeTree(self, 0)
    }

    void setPath(String@ path){
        self.path = path

        // 调用加载器加载
        if path {
            AssimpLoader@ l = new AssimpLoader()
            self.loader.load(self.path.str)

            //如果已经生成，说明是修改的。 需要重建
            if self.modelRoot {
                self.generateModelRoot()
            }
        }
    }


}

void test_AssimpLoader () {
    AssimpLoader@ l = new AssimpLoader()
    // l.load("duck.dae")
    // l.load("spider.fbx")
    l.load("spider.obj")
    l.showWindow()
    List@ mtls = new List()
    // l.mergedMaterials = mtls;

    new Material()~{
        o.load("../asset/basic.matl.json")
        mtls.add(o)
        mtls.add(o)
        mtls.add(o)
        mtls.add(o)
    }

    Obj3d@ root = l.buildSglTree()
    printNodeTree(root, 0)
}