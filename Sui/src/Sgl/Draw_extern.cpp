
#include "./UnitOpengl.h"
#include "./Draw_orc.h"
#include "Orc/Orc.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


static const aiScene* importModel( Assimp::Importer &importer, const std::string& pFile) {
  // Create an instance of the Importer class

  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // probably to request more postprocessing than we do in this example.
  const aiScene* scene = importer.ReadFile( pFile,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);
  auto n = scene->mRootNode;

  // If the import failed, report it
  if (nullptr == scene) {
    // DoTheErrorLogging( importer.GetErrorString());
    // return false;
    return nullptr;
  }
//   std::shared_ptr<aiScene> ret{(aiScene*)scene};
//   return ret;
    return scene;

  // Now we can access the file's contents.
//   DoTheSceneProcessing( scene);

  // We're done. Everything will be cleaned up by the importer destructor
//   return true;
}


struct Vec3 {
    float x;
    float y;
    float z;
};
static std::vector<Vec3> vertices2; 
static std::vector<unsigned int> indices; 

static
void processMesh(Sgl$ObjLoader *  self, aiMesh *mesh, const aiScene *scene)
{
    // static bool has = false;
    // if (has){
    //     return;
    // }
    // vector<Vertex> vertices;
    // vector<unsigned int> indices;
    // vector<Texture> textures;
    float scale = 1.0;

    int numVertices = mesh->mNumVertices;
    int start = Sgl$Buffer$floatSize(self->vertices) / 3;//vertices2.floatSize() / 3;

    for(unsigned int i = 0; i < numVertices; i++)
    {
        // has = true;
        Vec3 v3;
        v3.x = mesh->mVertices[i].x / scale;
        v3.y = mesh->mVertices[i].y / scale;
        v3.z = mesh->mVertices[i].z / scale;
        // printf("\t%f,%f,%f\n", v3.x, v3.y, v3.z);
        // vertices2.push_back(v3);

        Sgl$Buffer$appendFloats(self->vertices, (float*)&v3, 3);
        // Sgl$Buffer$appendFloat(self->vertices, v3.x);
        // Sgl$Buffer$appendFloat(self->vertices, v3.y);
        // Sgl$Buffer$appendFloat(self->vertices, v3.z);

        Vec3 n;
        n.x = mesh->mNormals[i].x;
        n.y = mesh->mNormals[i].y;
        n.z = mesh->mNormals[i].z;
        Sgl$Buffer$appendFloats(self->normals, (float*)&n, 3);

        // Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        // vertices.push_back(vertex);
    }

    // 处理索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            auto idx = face.mIndices[j] + start;
            // indices.push_back(idx);
            Sgl$Buffer$appendInt(self->faces, idx);
            // printf("\t%d,", idx);
        }
        // printf("\n");
    }
    // 处理材质
    if(mesh->mMaterialIndex >= 0)
    {
    }

    // return Mesh(vertices, indices, textures);
}
static void processNode(Sgl$ObjLoader *  self, aiNode* node, const aiScene * scene, int deep){

    for (int i = 0; i < deep; i++){
        printf("\t");
    }
    printf("%s meshs:%d kids:%d meta:%d\n", node->mName.C_Str(), 
        node->mNumMeshes, node->mNumChildren,
        node->mMetaData ?  node->mMetaData->mNumProperties
        : 0
    );
    //元数据
    if (node->mMetaData && node->mMetaData->mNumProperties > 0){
        for (int i = 0; i < node->mMetaData->mNumProperties; i++){
            const aiString* key = nullptr;
            const aiMetadataEntry *entry = nullptr;

            if (node->mMetaData->Get(i, key, entry)){
                for (int i = 0; i < deep + 1; i++){
                    printf("\t");
                }
                printf("%s:", key->C_Str());
                void *data = entry->mData;
                if (entry->mType == AI_BOOL){
                    bool *pbool = (bool*)data;
                    printf("%s", *pbool ? "true":"false");
                }
                else if (entry->mType == AI_INT32){
                    int *pv = (int*)data;
                    printf("%d", *pv);
                }
                else if (entry->mType == AI_UINT64){
                    uint64_t *pv = (uint64_t*)data;
                    printf("%llu", *pv);
                }
                else if (entry->mType == AI_FLOAT){
                    float *pv = (float*)data;
                    printf("%f", *pv);
                }
                else if (entry->mType == AI_DOUBLE){
                    double *pv = (double*)data;
                    printf("%f", *pv);
                }
                else if (entry->mType == AI_AISTRING){
                    aiString *pv = (aiString*)data;
                    printf("%s", pv->C_Str());
                }
                else if (entry->mType == AI_AIVECTOR3D){
                    aiVector3D *pv = (aiVector3D*)data;
                    printf("Vec3(%f,%f,%f)", pv->x, pv->y, pv->z);
                }
                else if (entry->mType == AI_INT64){
                    int64_t *pv = (int64_t*)data;
                    printf("%lld", *pv);
                }
                else if (entry->mType == AI_UINT32){
                    uint32_t *pv = (uint32_t*)data;
                    printf("%u", *pv);
                }
                else {
                    printf("meta?");
                }
                printf("\n");
            }
        }
        printf("\n");
    }
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        processMesh(self, mesh, scene);
        // meshes.push_back();         
    }

    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(self, node->mChildren[i], scene, deep+1);
    }
}
void  Sgl$ObjLoader$_load(Sgl$ObjLoader *  self){
    Assimp::Importer importer;
    auto scene = importModel(importer, self->path->str);

    processNode(self, scene->mRootNode, scene, 0);

    // Vec3 v3 = {0};
    // v3.x = 0.5; v3.y = 0.9; 
    // Sgl$Buffer$appendFloats(self->vertices, (float*)&v3, 3);
    // v3.x = 0.5; v3.y = -0.5; 
    // Sgl$Buffer$appendFloats(self->vertices, (float*)&v3, 3);
    // v3.x = -0.5; v3.y = -0.5; 
    // Sgl$Buffer$appendFloats(self->vertices, (float*)&v3, 3);
    // v3.x = -0.5; v3.y = 0.5; 

    if (0){

        Sgl$Buffer$appendFloat(self->vertices, -0.5);
        Sgl$Buffer$appendFloat(self->vertices, -0.5);
        Sgl$Buffer$appendFloat(self->vertices, 0);

        Sgl$Buffer$appendFloat(self->vertices, 0.5);
        Sgl$Buffer$appendFloat(self->vertices, -0.5);
        Sgl$Buffer$appendFloat(self->vertices, 0);

        Sgl$Buffer$appendFloat(self->vertices, 0.5);
        Sgl$Buffer$appendFloat(self->vertices, 0.8);
        Sgl$Buffer$appendFloat(self->vertices, 0);

        Sgl$Buffer$appendFloat(self->vertices, -0.5);
        Sgl$Buffer$appendFloat(self->vertices, 0.5);
        Sgl$Buffer$appendFloat(self->vertices, 0);

        Sgl$Buffer$appendInt(self->faces, 0);
        Sgl$Buffer$appendInt(self->faces, 1);
        Sgl$Buffer$appendInt(self->faces, 2);

        Sgl$Buffer$appendInt(self->faces, 0);
        Sgl$Buffer$appendInt(self->faces, 2);
        Sgl$Buffer$appendInt(self->faces, 3);
    }
}
void  Sgl$Draw$draw(Sgl$Draw *  self){
    self->use(self);
    self->material->prepareDraw(self->material);
    self->material->updateUniforms(self->material);

    // glDisable(GL_SCISSOR_TEST);

    auto ibo = self->geometry->ibo;
    int indexCount = ibo->calcIndexCount(ibo);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    self->material->endDraw(self->material);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}