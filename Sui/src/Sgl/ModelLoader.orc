package Sgl

#include <stdio.h>
#include <assimp/cimport.h>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "./Obj3d.orc"
import * from "./Mesh.orc"
import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Geometry.orc"
import * from "./Material.orc"


class AssimpLoader {
    String@ path
    struct aiScene *scene;
    void dtor(){
        if self.scene {
            // 释放资源
            aiReleaseImport(self.scene);
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
                    printf("\t\t%3d %s semantic:%d, iddx:%d, dataLength:%d type:%d ", j, prop.mKey.data, prop.mSemantic, prop.mIndex, prop.mDataLength, prop.mType);
                    if prop.mType == aiPTI_Float {
                        printf("%f", *((float*)prop.mData));
                    }
                    else if prop.mType == aiPTI_Double {
                        printf("%f", *((double*)prop.mData));
                    }
                    else if prop.mType == aiPTI_Integer {
                        printf("%d", *((int*)prop.mData));
                    }
                    else if prop.mType == aiPTI_String {
                        struct aiString* s = (struct aiString*)prop.mData;
                        printf("%s", s->data);
                    }
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
class ModelLoader extends Obj3d {
    Buffer@ vertices = new Buffer();
    Buffer@ normals = new Buffer();
    Buffer@ texCoords = new Buffer();
    Buffer@ faces = new Buffer();

    String@ path
    Mesh@ mesh = new Mesh()

    void setPath(String@ path){
        self.path = path

        // 调用加载器加载
        if path {
            self._load()
            self.mesh.geometry = self.buildGeometry()
            new Material()~{
                o.load("../asset/basic.matl.json")
                self.mesh.material = o
            }
            self.appendChild(self.mesh)
        }
    }


    extern void _load()

    Geometry@ buildGeometry(){
        Geometry@ geo = new Geometry()
        if self.vertices.size > 0{
            Vbo@ vbo = new Vbo()
            vbo.elementCount = 3;
            vbo.arrayBuffer(self.vertices)
            geo.setAttr("position", vbo)
            printf("\tload %s:%s\n", "position", self.vertices.toFloatString().str);
        }
        if self.normals.size > 0{
            Vbo@ vbo = new Vbo()
            vbo.elementCount = 3;
            vbo.arrayBuffer(self.normals)
            geo.setAttr("normal", vbo)
        }
        if self.texCoords.size > 0{
            Vbo@ vbo = new Vbo()
            vbo.elementCount = 2;
            vbo.arrayBuffer(self.texCoords)
            geo.setAttr("texCoord", vbo)
        }
        if self.faces.size > 0 {
            geo.ibo = new Vbo()
            geo.ibo.elementBuffer(self.faces)
            printf("\tload face:%s\n", self.faces.toIntString().str);
        }

        return geo
    }

}

void test_AssimpLoader () {
    AssimpLoader@ l = new AssimpLoader()
    // l.load("duck.dae")
    l.load("spider.fbx")
}