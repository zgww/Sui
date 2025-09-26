
package Sgl

#include <stdio.h>
#include "./UnitOpengl.h"
#include "../nanovg/stb_image.h"

import * from "./Buffer.orc"
import * from "./Vbo.orc"
import * from "./Material.orc"
import * from "./Program.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Orc/String.orc"

import * from "./Geometry.orc"

static struct ImgInfo{
    int width
    int height
    int channel
    unsigned char *data
}


class GeometryHeightMap extends Geometry {

    float incx = 10
    float incz = 10
    float texInc = 1
    float heightScale = 2.0
    float startX = -600
    float startZ = -600

    void dtor(){
        printf("~GeometryHeightMap\n")
    }

    
    float getHeight(ImgInfo* info, int row, int col){
        int idx = row * info.width * info.channel + col * info.channel
        unsigned char r = info.data[idx + 0]
        unsigned char g = info.data[idx + 1]
        unsigned char b = info.data[idx + 2]
        unsigned char a = info.data[idx + 3]
        // if (r < 255 || g < 255 || b < 255 || a < 255){

        // printf("height:%d,%d,%d,%d\n", r, g, b, a)
        // }
        return r * self.heightScale;
    }
    void build(const char *path){
        Buffer@ vtxs = new Buffer()
        // Buffer@ nmls = new Buffer()
        Buffer@ face = new Buffer()
        Buffer@ uvs = new Buffer()

        stbi_set_flip_vertically_on_load(true);
        ImgInfo info;
        info.data = stbi_load("../asset/heightmap.png", 
            &info.width, &info.height, &info.channel, 0);

        printf("png:%d,%d,%d\n", info.width, info.height, info.channel)

        for int row = 0; row < info.height; row++{
            for int col = 0; col < info.width; col++{
                float x = col * self.incx + self.startX
                float z = row * self.incz + self.startZ
                vtxs.appendFloat3(
                    x, 
                    self.getHeight(&info, row, col),
                    z,
                    )
                uvs.appendFloat2(
                    self.texInc * col / (float)info.width,
                    self.texInc * row / (float)info.height,
                )

                //面
                if col < info.width - 1 && row < info.height - 1 {
                    int lt = row * info.width + col
                    int lb = (row + 1) * info.width + col
                    int rb = (row + 1) * info.width + col + 1
                    int rt = row * info.width + col + 1

                    face.appendInt3(lb, rb, rt)
                    face.appendInt3(lb, rt, lt)
                }
            }

        }

        Buffer@ nmls = self.calcNormals(vtxs, info.width, info.height);

        self.setAttrByBuffer("position", vtxs, 3)
        self.setAttrByBuffer("normal", nmls, 3)
        self.setAttrByBuffer("uv", uvs, 2)
        self.setIboByBuffer(face)
    }
    Buffer@ calcNormals(Buffer* vtxs, int width, int height){
        float *posArr = vtxs.data
        Vec3 v0
        Vec3 v1
        Vec3 v2
        Vec3 v3
        Vec3 v4

        Vec3 v12
        Vec3 v23
        Vec3 v34
        Vec3 v41
        Vec3 normal
        Buffer@ nmls = new Buffer()
        nmls.expandCapacity(width * height * 3)

        for int row = 0; row < height; row++{
            for int col = 0; col < width; col++{
                if row > 0 && row < height - 1 && col > 0 && col < width - 1{
                    int i0 = row * width * 3 + col * 3
                    v0.x = posArr[i0]
                    v0.y = posArr[i0 + 1]
                    v0.z = posArr[i0 + 2]

                    int i1 = row*width*3 + (col-1)*3;
                    v1.x = posArr[i1];
                    v1.y = posArr[i1 + 1];
                    v1.z = posArr[i1 + 2];                    
                    v1 = v1.sub(v0);

                    int i2 = (row+1)*width*3 + col*3;
                    v2.x = posArr[i2];
                    v2.y = posArr[i2 + 1];
                    v2.z = posArr[i2 + 2];
                    v2 = v2.sub(v0);

                    int i3 = row * width * 3 + (col+1)*3;
                    v3.x = posArr[i3];
                    v3.y = posArr[i3 + 1];
                    v3.z = posArr[i3 + 2];
                    v3 = v3.sub(v0);

                    int i4 = (row-1)*width*3 + col*3;
                    v4.x = posArr[i4];
                    v4.y = posArr[i4 + 1];
                    v4.z = posArr[i4 + 2];

                    v4 = v4.sub(v0);

                    v12 = v1.cross(v2);
                    v12 = v12.normal();

                    v23 = v2.cross(v3);
                    v23 = v23.normal();

                    v34 = v3.cross(v4);
                    v34 = v34.normal();

                    v41 = v4.cross(v1);
                    v41 = v41.normal();

                    normal = v12.add(v23)
                    normal = normal.add(v34)
                    normal = normal.add(v41);

                    normal = normal.normal();
                    // printf("%d,%d normal:%f,%f,%f\n", col, row, normal.x, normal.y, normal.z)
                } else {
                    normal.x = 0;
                    normal.y = 1;
                    normal.z = 0;
                }
                nmls.appendFloat3(
                    normal.x,
                    normal.y,
                    normal.z,
                )
            }
        }

        return nmls
    }
}


void testHeightMap(){
    GeometryHeightMap@ g = new GeometryHeightMap()
    g.build("../asset/heightmap.png")


    // stbi_set_flip_vertically_on_load(true);
    // int width = 0
    // int height = 0
    // int channel = 0
    // unsigned char *data = stbi_load("../asset/heightmap.png", &width, &height, &channel, 0);
    // printf("png:%d,%d,%d\n", width, height, channel)
}