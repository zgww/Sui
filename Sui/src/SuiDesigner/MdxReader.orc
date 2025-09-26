package SuiDesigner3d_w3e

//魔兽mdx文件读取

#include "../Orc/Orc.h"
#include "../nanovg/nanovg.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

import * from "../Orc/String.orc"
import * from "../Orc/List.orc"
import * from "../Orc/Map.orc"
import * from "../Orc/Time.orc"
import * from "../Orc/Math.orc"
import * from "../Orc/Path.orc"
import * from "../Json/Json.orc"
import * from "../Sui/Core/Window.orc"
import * from "../Sui/Core/Node.orc"
import * from "../Sui/Core/ViewBase.orc"
import * from "../Sui/Core/View.orc"
import * from "../Sui/Core/Vec3.orc"
import * from "../Sui/Core/Vec4.orc"
import * from "../Sui/Core/Quat.orc"
import * from "../Sui/Core/Vec2.orc"
import * from "../Sui/Core/Rect.orc"
import * from "../Sui/Core/Event.orc"
import * from "../Sui/Core/Image.orc"
import * from "../Sui/Core/Frame.orc"
import * from "../Sui/Core/Mouse.orc"
import * from "../Sui/Core/MouseEvent.orc"
import * from "../Sui/View/TextView.orc"
import * from "../Sui/View/EditText.orc"
import * from "../Sui/View/Button.orc"
import * from "../Sui/View/ImageView.orc"
import * from "../Sui/View/HoverViewEffect.orc"
import * from "../Sui/View/ViewBuilder.orc"
import * from "../Sui/View/ScrollArea.orc"
import * from "../Sui/Dialog/Toast.orc"
import * from "../Sui/Dialog/FileDialog.orc"
import * from "../Sui/Dialog/MessageDialog.orc"
import * from "../Sui/Layout/LayoutLinear.orc"
import * from "../Sui/Layout/LayoutAlign.orc"
import * from "../Sui/View/DockLayout.orc"
import * from "../Sui/View/Drag.orc"
import * from "../Sui/View/MenuNative.orc"
import * from "../Sui/Core/Timer.orc"
import * from "../Sui/Core/Canvas.orc"
import * from "../Sgl/Buffer.orc"
import * from "../SuiDesigner/DrawDegree.orc"
import * from "./ChessBgViewCallback.orc"
import * from "./Theme.orc"
import * from "./InvalidReact.orc"
import * from "./MenuBarCtrl.orc"
import * from "../Sgl/Material.orc"
import * from "../Sgl/Geometry.orc"
import * from "../Sgl/Vbo.orc"
import * from "../Sgl/Tex2d.orc"
import * from "../Sgl/Bone.orc"
import * from "../Sgl/DrawCtx.orc"
import * from "../Sgl/Obj3d.orc"


// 序列播放器
// 步骤：
// 开始
// 更新帧
// 开始：
// 找到序列，设置当前帧为序列开始帧
// 更新帧:
//   遍历骨骼，并更新各个track
class MdxSeqPlayer extends Obj3d{
    // <Sequence>
    List@ seqs = new List()

    // <MdxNode>
    List@ helps = new List()
    // <MdxBone>
    List@ bones = new List()

    //当前播放中的seq
    Sequence@ curSeq
    int frame = 0


    bool play(const char *name){
        Sequence* seq = self.findSeq(name)
        if seq == null {
            return false;
        }
        self.curSeq = seq
        self.frame = seq.startFrame

        return true
    }
    bool isEnd(){
        if self.curSeq == null {
            return false;
        }
        bool b = self.frame > self.curSeq.endFrame
        return b
    }
    void tick(DrawCtx* ctx){
        if 0 || self.curSeq == null {
            return;
        }


        self.frame += ctx.dtMs
        if self.frame > self.curSeq.endFrame {
            if 1 || ! self.curSeq.nonLooping {// 如果是循环
                self.frame = self.curSeq.startFrame
            }
            else{ //越过最后一帧了,不播放了
                return
            }
        }
        // printf("==============================播放帧 %d in [%s, %d,%d]\n", self.frame, self.curSeq.name.str, self.curSeq.startFrame, self.curSeq.endFrame);

        //更新动画
        for int i = 0; i < self.bones.size(); i++{
            MdxBone* bone = (MdxBone*)self.bones.get(i)
            MdxNode *node = bone.node

            self.updateKGTR(node)
            self.updateKGRT(node)
            self.updateKGSC(node)
        }
        //更新动画
        for int i = 0; i < self.helps.size(); i++{
            MdxNode* node = (MdxNode*)self.helps.get(i)

            self.updateKGTR(node)
            self.updateKGRT(node)
            self.updateKGSC(node)
        }
    }
    void updateKGSC(MdxNode *node){
        //缩放
        if node.KGSC {
            TrackValueRange range = node.KGSC.findTrackValueRange(self.frame, self.curSeq)
            if range.left {
                Vec3 pos = range.lerpVec3()
                // printf("B%5d %s 缩放:%s => %s\n", self.frame, node.name.str, range.toString().str, pos.toString().str);
                if node.bone {
                    node.bone.scale = pos
                }
            }
        }
    }
    void updateKGRT(MdxNode *node){
        //旋转
        if node.KGRT {
            TrackValueRange range = node.KGRT.findTrackValueRange(self.frame, self.curSeq)
            if range.left {
                Quat quat = range.lerpQuat()
                Vec3 euler = quat.toEulerXYZ()
                // printf("B%5d %s 旋转:%s => %s %s\n", self.frame, node.name.str, range.toString().str, quat.toString().str, euler.toString().str);
                if node.bone {
                    node.bone.rotation = euler
                }
            }
        }
    }
    void updateKGTR(MdxNode *node){
        //平移
        if node.KGTR {
            TrackValueRange range = node.KGTR.findTrackValueRange(self.frame, self.curSeq)
            if range.left {
                Vec3 pos = range.lerpVec3()

                if node.bone {
                    Vec3 npos = node.bone.originPosition.add(pos)
                    // printf("B%5d %s 平移: %s => %s  final:%s => %s\n", self.frame, node.name.str, range.toString().str, pos.toString().str, 
                    //     node.bone.originPosition.toString().str,
                    //     npos.toString().str);
                    node.bone.position = npos
                }
            }
        }
    }

    Sequence* findSeq(const char *name){
        for int i = 0; i < self.seqs.size(); i++{
            Sequence* seq = (Sequence*)self.seqs.get(i)
            if seq.name.equals(name){
                return seq;
            }
        }
        return null
    }

    void init(MdxReader *r){
        self.seqs = r.seqs
        self.helps = r.helps
        self.bones = r.bones
    }
}
class FaceFX{
    String@ name
    String@ path
}

class LayerTexture {
    int id;
    //<int>
    TrackHeader@ KMTF;
}
enum ShadingFlags {
    ShadingFlags_unshaded = 1,
    ShadingFlags_sphere_environment_map = 2,
    ShadingFlags_unknown1 = 4,
    ShadingFlags_unknown2 = 8,
    ShadingFlags_two_sided = 16,
    ShadingFlags_unfogged = 32,
    ShadingFlags_no_depth_test = 64,
    ShadingFlags_no_depth_set = 128
};
class Layer {
    int blend_mode;
    int shading_flags;
    int texture_animation_id;
    int coord_id;
    float alpha;

    float emissive_gain;
    Vec3 fresnel_color;
    float fresnel_opacity;
    float fresnel_team_color;

    bool hd;

    //<LayerTexture>
    List@ textures = new List();
    // std::vector<LayerTexture> texturess;

    //<float>
    TrackHeader@ KMTA;
    //<float>
    TrackHeader@ KMTE;
    //<Vec3>
    TrackHeader@ KFC3;
    //<float>
    TrackHeader@ KFCA;
    //<float>
    TrackHeader@ KFTC;

}
class MdxMaterial {
    int priority_plane;
    int flags;
    // <Layer>
    List@ layers = new List();
}
struct Extend {
    float bounds_radius;
    Vec3 minimum;
    Vec3 maximum;
}
extension Extend {
    String@ toString(){
        char buf[512];

        sprintf(buf, "Extend(radius=%f, minimum=(%f,%f,%f), maximum=(%f,%f,%f))",
            self.bounds_radius,
            self.minimum.x,
            self.minimum.y,
            self.minimum.z,
            self.maximum.x,
            self.maximum.y,
            self.maximum.z,
        )

        String@ s = str(buf)
        return s;
    }

}

int INVALID_INDEX = -1

class Sequence {
    String@ name = str("")
    float rarity
    float moveSpeed;
    bool nonLooping;
    // IntVec2 interval; //开始帧和结束帧
    int startFrame;
    int endFrame;
    int sync_point
    Extend extend;

    String@ toString(){
        char b[512];
        sprintf(b, "%s; rarity:%f,moveSpeed:%f, nonLooping:%d,frame:%d,%d; syncpoint:%d. %s", 
            self.name.str,
            self.rarity,
            self.moveSpeed,
            self.nonLooping,
            self.startFrame,
            self.endFrame,
            self.sync_point,
            self.extend.toString().str,
        )
        return str(b)
    }
}
class GlobalSeq {
    int duration
    int time;
    int internalGlobalSEquenceId = INVALID_INDEX;
}
class TextureData {
    int replaceableId;
    bool wrapWidth; 
    bool wrapHeight;
    String@ fileName = str("")
    int internalTextureId = INVALID_INDEX;

    String@ _pngPath = str("")

    //统一replaceableId和filename的处理
    const char *getRealPath(){
        if self.fileName.notEmpty(){
            if self._pngPath.empty(){
                self._pngPath =  Path_withExt(self.fileName.str, ".png")
            }
            return self._pngPath.str
        }

        int id = self.replaceableId

        if id == 1{ return  "ReplaceableTextures/TeamColor/TeamColor00.png"}
        if id == 2{ return  "ReplaceableTextures/TeamGlow/TeamGlow00.png"}
        if id == 11{return  "ReplaceableTextures/Cliff/Cliff0.png"}
        if id == 21{return  ""} // Used by all cursor models (HumanCursor, OrcCursor, UndeadCursor, NightElfCursor)
        if id == 31{return  "ReplaceableTextures/LordaeronTree/LordaeronSummerTree.png"}
        if id == 32{return  "ReplaceableTextures/AshenvaleTree/AshenTree.png"}
        if id == 33{return  "ReplaceableTextures/BarrensTree/BarrensTree.png"}
        if id == 34{return  "ReplaceableTextures/NorthrendTree/NorthTree.png"}
        if id == 35{return  "ReplaceableTextures/Mushroom/MushroomTree.png"}
        if id == 36{return  "ReplaceableTextures/RuinsTree/RuinsTree.png"}
        if id == 37{return  "ReplaceableTextures/OutlandMushroomTree/MushroomTree.png"}

        return null
    }
}
class GeosetGroup {
    int matrixListSize;
}
enum ShapeType {
    ShapeType_Box =0 , // 2vertx
    ShapeType_Plane = 1 , // 2vertx
    ShapeType_Sphere =2 , // 1vertx
    ShapeType_Cylinder = 3 , // 2vertx
}
class CornEmitter {
    MdxNode@ node;
}
class CollisionShape {
    MdxNode@ node;
    ShapeType shapeType;
    Vec3 v0;
    Vec3 v1;
    float radius;
}
class MdxBone {
    MdxNode@ node;
    int geoset_id;
    int geoset_animation_id;
};
class MdxLight {

    MdxNode@ node
    int type

    int attenuation_start;
    int attenuation_end;
    Vec3 color;
    float intensity;
    Vec3 ambient_color;
    float ambient_intensity;

    //<TrackInt>
    TrackHeader@ KLAS;
    //<TrackInt>
    TrackHeader@ KLAE;
    //<TrackVec3>
    TrackHeader@ KLAC;
    //<TrackFloat>
    TrackHeader@ KLAI;
    //<TrackFloat>
    TrackHeader@ KLBI;
    //<TrackVec3>
    TrackHeader@ KLBC;
    //<TrackFloat>
    TrackHeader@ KLAV;

}


// enum TrackTag {
// 	KMTF = 'FTMK',
// 	KMTA = 'ATMK',
// 	KTAT = 'TATK',
// 	KTAR = 'RATK',
// 	KTAS = 'SATK',
// 	KGAO = 'OAGK',
// 	KGAC = 'CAGK',
// 	KLAS = 'SALK',
// 	KLAE = 'EALK',
// 	KLAC = 'CALK',
// 	KLAI = 'IALK',
// 	KLBI = 'IBLK',
// 	KLBC = 'CBLK',
// 	KLAV = 'VALK',
// 	KATV = 'VTAK',
// 	KPEE = 'EEPK',
// 	KPEG = 'GEPK',
// 	KPLN = 'NLPK',
// 	KPLT = 'TLPK',
// 	KPEL = 'LEPK',
// 	KPES = 'SEPK',
// 	KPEV = 'VEPK',
// 	KP2S = 'S2PK',
// 	KP2R = 'R2PK',
// 	KP2L = 'L2PK',
// 	KP2G = 'G2PK',
// 	KP2E = 'E2PK',
// 	KP2N = 'N2PK',
// 	KP2W = 'W2PK',
// 	KP2V = 'V2PK',
// 	KRHA = 'AHRK',
// 	KRHB = 'BHRK',
// 	KRAL = 'LARK',
// 	KRCO = 'OCRK',
// 	KRTX = 'XTRK',
// 	KRVS = 'SVRK',
// 	KCTR = 'RTCK',
// 	KTTR = 'RTTK',
// 	KCRL = 'LRCK',
// 	KGTR = 'RTGK',
// 	KGRT = 'TRGK',
// 	KGSC = 'CSGK',
// 	KFC3 = '3CFK',
// 	KFCA = 'ACFK',
// 	KFTC = 'CTFK',
// 	KMTE = 'ETMK'
// };

class TrackValue {
    int frame
    String@ toString(){
        return str("").addi(self.frame)
    }
}

class TrackInt extends TrackValue{
    int value
    int inTan
    int outTan
    String@ toString(){
        char tmp[128]
        sprintf(tmp, "%d|%d", self.frame, self.value)
        return str(tmp)
    }
}
class TrackFloat extends TrackValue {
    float value
    float inTan
    float outTan
    String@ toString(){
        char tmp[128]
        sprintf(tmp, "%d|%f", self.frame, self.value)
        return str(tmp)
    }
}
class TrackVec3 extends TrackValue{
    Vec3 value
    Vec3 inTan
    Vec3 outTan
    String@ toString(){
        char tmp[128]
        sprintf(tmp, "%d|Vec3(%f,%f,%f)", self.frame, self.value.x, self.value.y, self.value.z)
        return str(tmp)
    }
}
class TrackQuat extends TrackValue{
    Quat value
    Quat inTan
    Quat outTan
    String@ toString(){
        char tmp[128]
        sprintf(tmp, "%d|Quat(%f,%f,%f,%f)", self.frame, self.value.x, self.value.y, self.value.z, self.value.w)
        return str(tmp)
    }
}

enum InterpolationType {
    InterpolationType_none = 0,
    InterpolationType_linear = 1,
    InterpolationType_hermite = 2,
    InterpolationType_bezier = 3,
}
struct TrackValueRange {
    TrackValue *left;
    TrackValue *right;
    int frame
    float ratio
}
extension TrackValueRange {
    String@ toString(){
        char tmp[512];
        sprintf(tmp, "[%s, %s, f=%d, t=%f]",
            self.left ? self.left.toString().str: "null",
            self.right ? self.right.toString().str: "null",
            self.frame,
            self.ratio,
        )
        return str(tmp)
    }
    float calcRatio(){
        float r = calcRatio(self.frame, self.left.frame, self.right.frame)
        self.ratio = clampFloat(r, 0, 1)
        return r
    }
    int lerpInt(){
        float ratio = self.calcRatio()
        TrackInt *a = (TrackInt*)self.left
        TrackInt *b = (TrackInt*)self.right
        float val = lerpFloat(a.value, b.value, ratio)
        return (int)val
    }
    int lerpFloat(){
        float ratio = self.calcRatio()
        TrackFloat *a = (TrackFloat*)self.left
        TrackFloat *b = (TrackFloat*)self.right
        float val = lerpFloat(a.value, b.value, ratio)
        return val
    }
    Vec3 lerpVec3(){
        float ratio = self.calcRatio()
        TrackVec3 *a = (TrackVec3*)self.left
        TrackVec3 *b = (TrackVec3*)self.right
        Vec3 val = a.value.lerp(b.value, ratio)
        return val
    }
    Quat slerpQuat(){
        float ratio = self.calcRatio()
        TrackQuat *a = (TrackQuat*)self.left
        TrackQuat *b = (TrackQuat*)self.right
        Quat val = a.value.slerp(b.value, ratio)
        return val
    }
    Quat lerpQuat(){
        float ratio = self.calcRatio()
        TrackQuat *a = (TrackQuat*)self.left
        TrackQuat *b = (TrackQuat*)self.right
        Quat val = a.value.lerp(b.value, ratio)
        return val
    }
}
class TrackHeader {
    InterpolationType interpolationType = InterpolationType_none;
    int globalSeqId = INVALID_INDEX

    List@ tracks = new List()
    int id = INVALID_INDEX

    TrackValue * findNearestLeft(int frame){
        for int i = self.tracks.size() - 1; i >= 0; i--{
            TrackValue *tv = (TrackValue*)self.tracks.get(i)
            if tv.frame <= frame {
                return tv;
            }
        }
        return null
    } 
    TrackValue * findNearestRight(int frame){
        for int i = 0; i < self.tracks.size(); i++{
            TrackValue *tv = (TrackValue*)self.tracks.get(i)
            if tv.frame >= frame {
                return tv;
            }
        }
        return null
    } 

    //在[start,end]之间
    TrackValueRange findTrackValueRange(int frame, Sequence *seq){
        TrackValueRange r;
        memset(&r, 0, sizeof(TrackValueRange))

        TrackValue *left = self.findNearestLeft(frame)
        TrackValue *right = self.findNearestRight(frame)

        r.frame = frame

        r.left = left == null ? right : left
        r.right = right == null ? left : right

        // if left && left.frame <= seq.startFrame {
        //     // 确保不空
        //     r.left = left// == null ? right : left
        // }
        // if right && right.frame >= seq.endFrame {
        //     r.right = right// == null ? left : right
        // }

        if r.left == null {
            r.left = r.right
        }
        if r.right == null {
            r.right = r.left
        }

        return r
    }

}
enum Flags {
    Flags_dont_inherit_translation = 0x1,
    Flags_dont_inherit_rotation = 0x2,
    Flags_dont_inherit_scaling = 0x4,
    Flags_billboarded = 0x8,
    Flags_billboarded_lock_x = 0x10,
    Flags_billboarded_lock_y = 0x20,
    Flags_billboarded_lock_z = 0x40,
    Flags_camera_anchored = 0x80,
    Flags_bone = 0x100,
    Flags_light = 0x200,
    Flags_object = 0x400,
    Flags_attachment = 0x800,
    Flags_emitter = 0x1000,
    Flags_collision_shape = 0x2000,
    Flags_ribbon_emitter = 0x4000,
    // if_particle_emitter : emitter_uses_mdl,
    Flags_unshaded = 0x8000,
    // if_particle_emitter : emitter_uses_tga,
    Flags_sort_primitives_far_z = 0x10000,
    Flags_line_emitter = 0x20000,
    Flags_unfogged = 0x40000,
    Flags_model_space = 0x80000,
    Flags_xy_quad = 0x100000
};

class MdxNode {
    String@ name;
    int id;
    int parentId;
    int flags;
    //平移 track
    TrackHeader@ KGTR;
    //旋转 track
    TrackHeader@ KGRT;
    //缩放 track
    TrackHeader@ KGSC;

    Bone@ bone;
}

class Attachment {
    MdxNode@ node;
    String@ path
    int reserved;
    int attachment_id;

    TrackHeader@ KATV;
}
class EventObject {
    MdxNode@ node;
    int globalSeqId = INVALID_INDEX;
    IntArray@ times = new IntArray()
}
class GeosetAnimation {
    float alpha
    int flags
    Vec3 color; // BGR not RGB
    int geoset_id
    TrackHeader@ KGAO
    TrackHeader@ KGAC
}
class Geoset {
    Geometry@ geom = new Geometry()
    // 每个顶点都在vertexGroups中有个值，表示matrixGroups的索引
    // matrixGroups 对骨骼分组。  数据是几个成一组。
    // matrixIndices指向具体的骨骼索引
    // 例 
    // matrixIndices: [1, 2, 3, 2, 3]
    // matrixGroups: [2, 3]
    // vertexGroups: [0, 0, 1]
    // 表示
    // 根据matrixGroups/MatrixIndices得到有骨骼组: [[1, 2], [3, 2, 3]]
    // 各顶点的骨骼组为 [0, 0, 1]
    // 顶点0 受[1,2]骨骼影响，平均权重
    // 顶点1 受[1,2]骨骼影响，平均权重
    // 顶点2 受[3, 2, 3]骨骼影响，平均权重
    // 一顶点一般最多4个骨骼， 少数有8个骨赂

    //骨骼的objectid
    IntArray@ matrix_indices;
    //对骨骼分组。
    IntArray@ matrix_group;
    //顶点的骨骼组索引数据. 每个顶点都有对应的vretex_group数据，用来关联骨骼组。骨骼组一般是1-4个， 关联具体的bone.objectid
    CharArray@ vertex_groups;

    int material_id 
}

class MdxReader {
    int version = 0
    int unique_tracks = 0;

    // <MdxMaterial>
    List@ matls = new List()
    // <Geoset>
    List@ geosets = new List()
    // <TextureData>
    List@ texs = new List()

    Vec3Array@ pivots
    // <MdxNode>
    List@ helps = new List()
    // <MdxBone>
    List@ bones = new List()

    // <MdxLight>
    List@ lights = new List()

    // <Sequence>
    List@ seqs = new List()

    // 用在一些特别的动画上
    // <GlobalSeq>
    List@ globalSeqs = new List()

    // <GeosetAnimation>
    List@ geosetAnimations = new List()

    // <Attachment>
    List@ attachments = new List()

    // <CornEmitter>
    List@ cornEmitters = new List()

    // <EventObject>
    List@ events = new List()

    // <CollisionShape>
    List@ collisionShapes = new List()

    // <FaceFX>
    List@ faceFxList = new List()

    Vec3Array@ bindPose

    TextureData@ readTextureData(BufferReader *reader){
        TextureData@ r = new TextureData()

        r.replaceableId = reader.readInt()

        r.fileName = reader.readString(256)

        reader.advance(4)

        int flags = reader.readInt()
        r.wrapWidth = flags & 1
        r.wrapHeight = flags & 2

        printf("\t\ttex. replaceableId:%d, fileName:%s, ww:%d, wh:%d, flags:%d. realPath:%s\n",
            r.replaceableId,
            r.fileName.str,
            r.wrapWidth,
            r.wrapHeight,
            flags,
            r.getRealPath(),
        )

        return r
    }
    Sequence@ readSequence(BufferReader *reader){
        Sequence@ r = new Sequence()

        r.name = reader.readString(80)
        r.startFrame = reader.readInt()
        r.endFrame = reader.readInt()
        r.moveSpeed = reader.readFloat()
        r.nonLooping = reader.readInt() == 1
        r.rarity = reader.readFloat()
        r.sync_point = reader.readInt()

        // reader.advance(4)//?what

        r.extend = self.readExtend(reader)

        return r
    }

    Extend readExtend(BufferReader *reader){
        Extend r;
        r.bounds_radius = reader.readFloat()
        r.minimum = reader.readVec3()
        r.maximum = reader.readVec3()
        return r;
    }
    // 灯光
    void readLITE(BufferReader *reader, int size){
        int reader_pos = reader.index - 4
        while reader.index < reader_pos + size {
            MdxLight@ e = new MdxLight()

            self.lights.add(e)


            int node_reader_pos = reader.index
            int inclusive_size = reader.readInt()
            e.node = self.readNode(reader)
            e.type = reader.readInt()
            e.attenuation_start = reader.readFloat()
            e.attenuation_end = reader.readFloat()
            e.color = reader.readVec3()
            e.intensity = reader.readFloat()
            e.ambient_color = reader.readVec3()
            e.ambient_intensity = reader.readFloat()

            while reader.index < node_reader_pos + inclusive_size {
                char tag[5]
                reader.readChars(tag, 4, true)
                printf("\ttag:%s\n", tag)
                if strcmp(tag, "KLAS"){
                    e.KLAS = self.readTrackHeaderInt(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KLAE"){
                    e.KLAE = self.readTrackHeaderInt(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KLAC"){
                    e.KLAC = self.readTrackHeaderVec3(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KLAI"){
                    e.KLAI = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KLBI"){
                    e.KLBI = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KLBC"){
                    e.KLBC = self.readTrackHeaderVec3(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KLAV"){
                    e.KLAV = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                }
                else {
                    printf("\tunknown tag:%s\n", tag)
                }
            }
        }
    }
    //材质
    void readMTLS(BufferReader *reader, int size){
        // List@ seqs = new List()
        int total_size = 0
        while total_size < size{
            int reader_pos = reader.index
            int inclusive_size = reader.readInt()
            total_size += inclusive_size

            MdxMaterial@ e = new MdxMaterial()
            self.matls.add(e)


            e.priority_plane = reader.readInt()
            e.flags = reader.readInt()
            if self.version < 1100 {
                bool is_hd = false
                if self.version == 900 || self.version == 1000 {
                    is_hd = !reader.readString(80).empty()
                }
                self.read_MTLS_texs_pre_v1100(reader, is_hd, e, self.unique_tracks++)

            }
            else {
                self.read_MTLS_texs_post_v1100(reader, e, self.unique_tracks++)
            }
        }
    }
    //旧版
    void read_MTLS_texs_pre_v1100(BufferReader *reader, bool is_hd, MdxMaterial *material, int trackId){
        char tag[5]
        reader.readChars(tag, 4, true)
        printf("\t旧版 tag:%s. is_hd:%d\n", tag, is_hd)

        int layers_count = reader.readInt()
        if is_hd {
            Layer@ layer = new Layer()
            layer.hd = is_hd

            for int i = 0; i < layers_count; i++{
                int reader_pos = reader.index
                int size = reader.readInt()

                // 第一层的属性才有用
                if i > 0 {
                    reader.advance(8)
                    LayerTexture@ layer_texture = new LayerTexture()
                    layer_texture.id = reader.readInt()
                    layer.textures.add(layer_texture)
                    reader.advance(size - 16)
                    continue
                }
                layer.blend_mode = reader.readInt()
                layer.shading_flags = reader.readInt()

                LayerTexture@ layer_texture = new LayerTexture()
                layer_texture.id = reader.readInt()
                layer.textures.add(layer_texture)
                printf("\t\tlayer_texture.id:%d\n", layer_texture.id)

                layer.texture_animation_id = reader.readInt()
                layer.coord_id = reader.readInt()
                layer.alpha = reader.readFloat()

                layer.emissive_gain = reader.readFloat()
                layer.fresnel_color = reader.readVec3()
                layer.fresnel_opacity = reader.readFloat()
                layer.fresnel_team_color = reader.readFloat()

                while reader.index < reader_pos + size {
                    char tag[5]
                    reader.readChars(tag, 4, true)
                    printf("\ttag:%s\n", tag)
                    if strcmp(tag, "KMTF") == 0 {
                        layer_texture.KMTF = self.readTrackHeaderInt(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KMTA") == 0 {
                        layer.KMTA = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KMTE") == 0 {
                        layer.KMTE = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KFC3") == 0 {
                        layer.KFC3 = self.readTrackHeaderVec3(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KFCA") == 0 {
                        layer.KFCA = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KFTC") == 0 {
                        layer.KFTC = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else {
                        printf("\tunknown tag:%s\n", tag)
                    }

                }



            }

        }
        else {
            for int i = 0; i < layers_count; i++{
                int reader_pos = reader.index
                int size = reader.readInt()
                Layer@ layer = new Layer()
                layer.hd = is_hd

                material.layers.add(layer)

                layer.blend_mode = reader.readInt()
                layer.shading_flags = reader.readInt()

                LayerTexture@ layer_texture = new LayerTexture()
                layer_texture.id = reader.readInt()
                layer.textures.add(layer_texture)

                layer.texture_animation_id = reader.readInt()
                layer.coord_id = reader.readInt()
                layer.alpha = reader.readFloat()

                printf("\t\tlayer_texture.id:%d\n", layer_texture.id)
                printf("\t\tlayer.texture_animation_id:%d\n", layer.texture_animation_id)
                printf("\t\tlayer.coord_id:%d\n", layer.coord_id)
                printf("\t\tlayer.alpha:%f\n", layer.alpha)

                if self.version > 800 {
                    layer.emissive_gain = reader.readFloat()
                    layer.fresnel_color = reader.readVec3()
                    layer.fresnel_opacity = reader.readFloat()
                    layer.fresnel_team_color = reader.readFloat()
                }

                while reader.index < reader_pos + size {
                    char tag[5]
                    reader.readChars(tag, 4, true)
                    printf("\ttag:%s\n", tag)
                    if strcmp(tag, "KMTF") == 0 {
                        layer_texture.KMTF = self.readTrackHeaderInt(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KMTA") == 0 {
                        layer.KMTA = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KMTE") == 0 {
                        layer.KMTE = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KFC3") == 0 {
                        layer.KFC3 = self.readTrackHeaderVec3(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KFCA") == 0 {
                        layer.KFCA = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else if strcmp(tag, "KFTC") == 0 {
                        layer.KFTC = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                    }
                    else {
                        printf("\tunknown tag:%s\n", tag)
                    }

                }
            }
        }
    }
    void read_MTLS_texs_post_v1100(BufferReader *reader, MdxMaterial *material, int trackId){
        char tag[5]
        reader.readChars(tag, 4, true)
        printf("\t新版>=v1100 tag:%s\n", tag)

        int layers_count = reader.readInt()
        for int i = 0; i < layers_count; i++{
            int reader_pos = reader.index
            int size = reader.readInt()
            Layer@ layer = new Layer()

            layer.blend_mode = reader.readInt()
            layer.shading_flags = reader.readInt()

            reader.advance(4) // skip texture_id

            layer.texture_animation_id = reader.readInt()
            layer.coord_id = reader.readInt()
            layer.alpha = reader.readFloat()

            layer.emissive_gain = reader.readFloat()
            layer.fresnel_color = reader.readVec3()
            layer.fresnel_opacity = reader.readFloat()
            layer.fresnel_team_color = reader.readFloat()

            layer.hd = reader.readInt()

            int texs = reader.readInt()
            for int j = 0; j < texs; j++{
                LayerTexture@ layer_texture = new LayerTexture()
                layer_texture.id = reader.readInt()
                int slot = reader.readInt()// always a garbage value

                char tag[5]
                reader.readChars(tag, 4, true)
                if strcmp(tag, "KMTF"){
                    layer_texture.KMTF = self.readTrackHeaderInt(reader, self.unique_tracks++)
                }
                else {
                    reader.advance(-4)
                }
                layer.textures.add(layer_texture)
            }

            while reader.index < reader_pos + size { char tag[5]
                reader.readChars(tag, 4, true)
                printf("\ttag:%s\n", tag)
                if strcmp(tag, "KMTA") == 0 {
                    layer.KMTA = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KMTE") == 0 {
                    layer.KMTE = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KFC3") == 0 {
                    layer.KFC3 = self.readTrackHeaderVec3(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KFCA") == 0 {
                    layer.KFCA = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                }
                else if strcmp(tag, "KFTC") == 0 {
                    layer.KFTC = self.readTrackHeaderFloat(reader, self.unique_tracks++)
                }
                else {
                    printf("\tunknown tag:%s\n", tag)
                }
            }
        }
    }
    void readGEOA(BufferReader *reader, int size){
        // List@ seqs = new List()
        int total_size = 0
        while total_size < size{
            int reader_pos = reader.index
            int inclusive_size = reader.readInt()
            total_size += inclusive_size

            GeosetAnimation@ e = new GeosetAnimation()
            self.geosetAnimations.add(e)


            e.alpha = reader.readFloat()
            e.flags = reader.readInt()
            e.color = reader.readVec3()
            e.geoset_id = reader.readInt()

            printf("\talpha:%f\n", e.alpha)
            printf("\tflags:%d\n", e.flags)
            printf("\tcolor:%s\n", e.color.toString().str)
            printf("\tgeoset_id:%d\n", e.geoset_id)

            while reader.index < reader_pos + inclusive_size {
                char tag[5]
                reader.readChars(tag, 4, true)
                printf("\t\ttag:%s\n", tag)

                if strcmp(tag, "KGAO") == 0 {
                    e.KGAO = self.readTrackHeaderFloat(reader, self.unique_tracks)
                    self.unique_tracks++
                }
                else if strcmp(tag, "KGAC") == 0 {
                    e.KGAO = self.readTrackHeaderVec3(reader, self.unique_tracks)
                    self.unique_tracks++
                }
                else {
                    printf("unknown tag:%s\n", tag)
                }
            }
        }
    }
    // List<TextureData>
    List@ readTEXS(BufferReader *reader, int size){
        int total_size = 0
        while total_size < size{
            int subchunk_size = 268
            total_size += subchunk_size
            printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size)
            TextureData@ tex = self.readTextureData(reader)
            self.texs.add(tex)
        }
        return self.texs
    }
    // List<Sequence>
    List@ readSEQS(BufferReader *reader, int size){
        int cnt = size / 132;
        // int total_size = 0
        for int i = 0; i < cnt; i++{
        // while total_size < size{
            // int subchunk_size = reader.readInt()
            // total_size += subchunk_size
            // printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size)
            Sequence@ seq = self.readSequence(reader)
            self.seqs.add(seq)
        }
        return self.seqs
    }
    // List<GlobalSeq>
    List@ readGLBS(BufferReader *reader, int size){
        int cnt = size / 4;
        for int i = 0; i < cnt; i++{
            GlobalSeq@ seq = new GlobalSeq()
            seq.duration = reader.readInt()
            self.globalSeqs.add(seq)
        }
        return self.globalSeqs
    }

    //构建骨骼索引。4个一组，不存在的写0
    IntArray@ mkBoneIndices(IntArray* matrix_group, IntArray* matrix_indices){
        IntArray@ r = new IntArray()
        int offset = 0
        for int i = 0; i < matrix_group.size; i++{
            int cnt = matrix_group.get(i)

            for int j = 0; j < cnt; j++{
                int boneIndex = matrix_indices.get(offset + j)
                r.append(boneIndex)
            }

            //补0
            for int j = 0; j < 4 - cnt; j++{
                r.append(0)
            }

            offset += cnt
        }
        return r
    }
    void readGEOS(BufferReader *reader, int size){
        int total_size = 0
        while total_size < size{
            int subchunk_size = reader.readInt()
            total_size += subchunk_size
            printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size)

            char subname[5];

            Geoset@ geoset = new Geoset()
            Geometry* geom = geoset.geom
            self.geosets.add(geoset)

            // VRTX
            reader.readChars(subname, 4, true)
            int vertex_count = reader.readInt()
            Vec3Array@ vertices = reader.readVec3Array(vertex_count)
            printf("\tsubname:%s. vtx:%d/%d %s\n", subname, vertex_count, vertices.size,
                ""
                // vertices.toString().str
            )
            geom.setAttrByFloats("position", (float*)vertices.data, vertex_count * 3, 3);

            //NRMS
            reader.readChars(subname, 4, true)
            int normal_count = reader.readInt()
            Vec3Array@ normals = reader.readVec3Array(normal_count)
            printf("\tsubname:%s %d\n", subname, normal_count)
            geom.setAttrByFloats("normal", (float*)normals.data, normal_count * 3, 3);


            //PTYP
            reader.readChars(subname, 4, true)
            printf("\tsubname:%s\n", subname)
            int face_type_groups_count = reader.readInt()
            IntArray@ face_type_groups = reader.readIntArray(face_type_groups_count)

            //PCNT
            reader.readChars(subname, 4, true)
            printf("\tsubname:%s\n", subname)
            int face_groups_count = reader.readInt()
            // reader.advance(face_groups_count * 4);
            IntArray@ face_groups = reader.readIntArray(face_groups_count)


            // PVTX ibo?
            reader.readChars(subname, 4, true)
            printf("\tsubname:%s\n", subname)
			int faces_count = reader.readInt();
            // reader.advance(faces_count * 2);
            ShortArray@ faces = reader.readShortArray(faces_count)
            geom.setIboByShorts(faces.data, faces_count);

            //GNDX
            reader.readChars(subname, 4, true)
            printf("\tsubname:%s\n", subname)
            int vertex_groups_count = reader.readInt()
            CharArray@ vertex_groups = reader.readCharArray(vertex_groups_count)
            // reader.advance(vertex_groups_count * 1);
            printf("\tvertex_groups:%s\n", vertex_groups.toString().str);

            //MTGC
            reader.readChars(subname, 4, true)
            printf("\tsubname:%s\n", subname)
            int matrix_group_count = reader.readInt()
            // reader.advance(matrix_group_count * 4);
            IntArray@ matrix_group = reader.readIntArray(matrix_group_count)
            printf("\tmatrix_group:%s", matrix_group.toString().str)

            //MATS  
            reader.readChars(subname, 4, true)
            printf("\tsubname:%s\n", subname)
            int matrix_indices_count = reader.readInt()
            IntArray@ matrix_indices = reader.readIntArray(matrix_indices_count)
            printf("\tmatrix_indices:%s", matrix_indices.toString().str)
            // reader.advance(matrix_indices_count * 4);

            {
                IntArray@ boneIndices = self.mkBoneIndices(matrix_group, matrix_indices)
                printf("boneIndices:\n%s\n", boneIndices.toString().str)
                //生成skinIndex和skinWeight
                Vec4Array@ skinIndex = new Vec4Array()
                Vec4Array@ skinWeight = new Vec4Array()
                for int i = 0; i < vertex_groups.size; i++{
                    char group = vertex_groups.get(i)
                    int offset = group * 4
                    int idx0 = boneIndices.data[offset + 0]
                    int idx1 = boneIndices.data[offset + 1]
                    int idx2 = boneIndices.data[offset + 2]
                    int idx3 = boneIndices.data[offset + 3]
                    skinIndex.add(mkVec4(idx0, idx1, idx2, idx3))
                    int cnt = 0

                    if idx0 != 0 {cnt++}
                    if idx1 != 0 {cnt++}
                    if idx2 != 0 {cnt++}
                    if idx3 != 0 {cnt++}

                    float weight = cnt == 0 ? 1 : 1 / (float)cnt
                    skinWeight.add(mkVec4(
                        cnt >= 1 ? weight : 1.0,
                        cnt >= 2 ? weight : 0.0,
                        cnt >= 3 ? weight : 0.0,
                        cnt >= 4 ? weight : 0.0,
                    ))
                }
                geom.setAttrByFloats("skinIndex", (float*)skinIndex.data, skinIndex.size * 4, 4);
                geom.setAttrByFloats("skinWeight", (float*)skinWeight.data, skinWeight.size * 4, 4);
            }



            int material_id = reader.readInt()
            int selection_group = reader.readInt()
            int selection_flags = reader.readInt()

            geoset.material_id = material_id

            printf("\t\tmaterial_id:%d\n", material_id);
            printf("\t\tselection_group:%d\n", selection_group);
            printf("\t\tselection_flags:%d\n", selection_flags);

            if self.version > 800{
                int lod = reader.readInt()
                String@ lod_name = reader.readString(80)
                printf("\t\tlod:%d\n", lod);
                printf("\t\tlod:%s\n", lod_name.str);
            }
            else {
                int lod = 0
            }
            Extend extend = self.readExtend(reader)
            printf("\t\textend:%s\n", extend.toString().str);
            //各个动画的extend
            int extends_count = reader.readInt()
            for int i = 0; i < extends_count; i++{
                // sequence_extends
                Extend sequence_extend = self.readExtend(reader)
            }

            String@ tag = reader.readString(4)
            printf("\ttag:%s\n", tag.str)
            if tag.equals("TANG"){
                int structure_count = reader.readInt()
                Vec4Array@ tangents = reader.readVec4Array(structure_count)

                tag = reader.readString(4) // SKIN|UVAS
                printf("\ttag:%s\n", tag.str)
            }
            if tag .equals( "SKIN") {
                int skin_count = reader.readInt()
                reader.advance(skin_count * 1);

                tag = reader.readString(4)//UVAS
                printf("\ttag:%s\n", tag.str)
            }

            int texture_coordinate_sets_count = reader.readInt()
            printf("\t\t纹理坐标数:%d\n", texture_coordinate_sets_count)

            for int i = 0; i < texture_coordinate_sets_count; i++{
                reader.advance(4) // UVBS
                int texture_coordinates_count = reader.readInt()

                Vec2Array@ uvs = reader.readVec2Array(texture_coordinates_count)
                if i == 0 {
                    geom.setAttrByFloats("uv", (float*)uvs.data, texture_coordinates_count * 2, 2);
                }
                else {
                    printf("\t\t\t有多套纹理坐标。 忽略\n");
                }

            }

        }

    }
    //Bone 
    void readBONE(BufferReader* reader, int size){
        // int total_size = 0
        int reader_pos = reader.index - 4 
        printf("\tread BONE. reader_pos:%d. size:%d\n", reader_pos, size)
        while reader.index < reader_pos + size{
            MdxBone@ e =new MdxBone()

            self.bones.add(e)

            e.node = self.readNode(reader)
            e.geoset_id = reader.readInt()
            e.geoset_animation_id = reader.readInt()
        }
    }
    //HELP 辅助节点
    void readHELP(BufferReader* reader, int size){
        // int total_size = 0
        int reader_pos = reader.index - 4 
        printf("\tread HELP. reader_pos:%d. size:%d\n", reader_pos, size)
        while reader.index < reader_pos + size{
            MdxNode@ node = self.readNode(reader)
            self.helps.add(node)
        }
    }
    //附件
    void readATCH(BufferReader* reader, int size){
        // int total_size = 0
        int reader_pos = reader.index - 4 
        printf("\tread ATCH. reader_pos:%d. size:%d\n", reader_pos, size)
        while reader.index < reader_pos + size{
            Attachment@ e = new Attachment()
            self.attachments.add(e)

            int node_reader_pos = reader.index
            int inclusive_size = reader.readInt()

            e.node = self.readNode(reader)
            e.path = reader.readString(256)
            e.reserved = reader.readInt()
            e.attachment_id = reader.readInt()

            while reader.index < node_reader_pos + inclusive_size {
                char tag[5]
                reader.readChars(tag, 4, true)
                e.KATV = self.readTrackHeaderFloat(reader, self.unique_tracks)
                self.unique_tracks++

                printf("\t\ttag:%s\n", tag)
                if strcmp(tag, "KATV") == 0{
                }
                else {
                    printf("Unknown tag:%s\n", tag)
                }
            }
        }
    }
    //Corn发射器
    void readCORN(BufferReader* reader, int size){
        // int total_size = 0
        int reader_pos = reader.index - 4 
        printf("\tread CORN. reader_pos:%d. size:%d\n", reader_pos, size)
        while reader.index < reader_pos + size{
            CornEmitter@ e = new CornEmitter()

            self.cornEmitters.add(e)


            int node_reader_pos = reader.index
            int inclusive_size = reader.readInt()


            printf("\tnew CornEmitter\n")
            e.node = self.readNode(reader)

            CharArray@ a = reader.readCharArray(inclusive_size - (reader.index - node_reader_pos))
        }
    }
    //事件
    void readEVTS(BufferReader* reader, int size){
        // int total_size = 0
        int reader_pos = reader.index - 4 
        printf("\tread EVTS. reader_pos:%d. size:%d\n", reader_pos, size)
        while reader.index < reader_pos + size{
            EventObject@ e = new EventObject()
            self.events.add(e)


            printf("\tnew EventObject\n")
            e.node = self.readNode(reader)
            printf("\t name:%s\n", e.node.name.str)
            char tag[5]
            reader.readChars(tag, 4, true)
            printf("\t tag:%s\n", tag)
            int count = reader.readInt()
            e.globalSeqId = reader.readInt()
            printf("\t globalSeqId:%d\n", e.globalSeqId)

            e.times = reader.readIntArray(count)
            printf("\t times:%s\n", e.times.toString().str)
        }
    }
    //碰撞
    void readCLID(BufferReader* reader, int size){
        // int total_size = 0
        int reader_pos = reader.index - 4
        while reader.index < reader_pos + size{
            // int subchunk_size = reader.readInt()
            // total_size += subchunk_size
            // printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size)

            CollisionShape@ shape = new CollisionShape();
            self.collisionShapes.add(shape)


            shape.node = self.readNode(reader)
            shape.shapeType = (ShapeType)reader.readInt()

            printf("\tCollisionShape. name:%s, shapeType:%d\n", shape.node.name.str, shape.shapeType)

            shape.v0 = reader.readVec3()
            printf("\t\t v0:%s\n", shape.v0.toString().str)
            if shape.shapeType != ShapeType_Sphere {
                shape.v1 = reader.readVec3()
                printf("\t\t v1:%s\n", shape.v1.toString().str)
            }
            if shape.shapeType == ShapeType_Sphere
            || shape.shapeType == ShapeType_Cylinder
            {
                shape.radius = reader.readFloat()
                printf("\t\t radius:%f\n", shape.radius)
            }
        }
    }
    TrackHeader@ readTrackHeaderQuat(BufferReader *reader, int track_id){
        int tracks_count = reader.readInt()
        TrackHeader@ r = new TrackHeader()

        r.interpolationType = (InterpolationType)reader.readInt()
        r.globalSeqId = reader.readInt()

        for int i =0 ; i < tracks_count; i++{
            TrackQuat@ tvec = new TrackQuat()
            tvec.frame = reader.readInt()
            tvec.value = reader.readQuat()
            if r.interpolationType == InterpolationType_bezier 
            || r.interpolationType == InterpolationType_hermite {
                tvec.inTan = reader.readQuat()
                tvec.outTan = reader.readQuat()
            }
            r.tracks.add(tvec)
        }

        return r
    }
    TrackHeader@ readTrackHeaderVec3(BufferReader *reader, int track_id){
        int tracks_count = reader.readInt()
        TrackHeader@ r = new TrackHeader()

        r.interpolationType = (InterpolationType)reader.readInt()
        r.globalSeqId = reader.readInt()

        for int i =0 ; i < tracks_count; i++{
            TrackVec3@ tvec = new TrackVec3()
            tvec.frame = reader.readInt()
            tvec.value = reader.readVec3()
            if r.interpolationType == InterpolationType_bezier 
            || r.interpolationType == InterpolationType_hermite {
                tvec.inTan = reader.readVec3()
                tvec.outTan = reader.readVec3()
            }
            r.tracks.add(tvec)
        }

        return r
    }
    TrackHeader@ readTrackHeaderInt(BufferReader *reader, int track_id){
        int tracks_count = reader.readInt()
        TrackHeader@ r = new TrackHeader()

        r.interpolationType = (InterpolationType)reader.readInt()
        r.globalSeqId = reader.readInt()

        for int i =0 ; i < tracks_count; i++{
            TrackInt@ tvec = new TrackInt()
            tvec.frame = reader.readInt()
            tvec.value = reader.readInt()
            if r.interpolationType == InterpolationType_bezier 
            || r.interpolationType == InterpolationType_hermite {
                tvec.inTan = reader.readInt()
                tvec.outTan = reader.readInt()
            }
            r.tracks.add(tvec)
        }

        return r
    }
    TrackHeader@ readTrackHeaderFloat(BufferReader *reader, int track_id){
        int tracks_count = reader.readInt()
        TrackHeader@ r = new TrackHeader()

        r.interpolationType = (InterpolationType)reader.readInt()
        r.globalSeqId = reader.readInt()

        for int i =0 ; i < tracks_count; i++{
            TrackFloat@ tvec = new TrackFloat()
            tvec.frame = reader.readInt()
            tvec.value = reader.readFloat()
            if r.interpolationType == InterpolationType_bezier 
            || r.interpolationType == InterpolationType_hermite {
                tvec.inTan = reader.readFloat()
                tvec.outTan = reader.readFloat()
            }
            r.tracks.add(tvec)
        }
        return r
    }
    MdxNode@ readNode(BufferReader *reader){
        int pos = reader.index
        int inclusive_size = reader.readInt()
        // printf("\t\treadNode. pos:%d, inclusive_Size:%d\n", pos, inclusive_size)
        MdxNode@ n = new MdxNode()
        n.name = reader.readString(80)
        // printf("\t\treadNode. name:%s\n", n.name.str)
        n.id = reader.readInt()
        // printf("\t\treadNode. id:%d\n", n.id)
        n.parentId = reader.readInt()
        // printf("\t\treadNode. parentId:%d\n", n.parentId)
        n.flags = reader.readInt()
        // printf("\t\treadNode. flags:%d. index:%d, remaining:%d\n", n.flags, reader.index, reader.remaining())

        while reader.index < pos + inclusive_size {
            char tag[5];
            reader.readChars(tag, 4, true)
            // printf("\t\treadNode. tag:%s\n", tag)
            if strcmp(tag, "KGTR") == 0{
                n.KGTR = self.readTrackHeaderVec3(reader, self.unique_tracks)
                self.unique_tracks++
            }
            else if strcmp(tag, "KGRT") == 0{
                n.KGRT = self.readTrackHeaderQuat(reader, self.unique_tracks)
                self.unique_tracks++
            }
            else if strcmp(tag, "KGSC") == 0{
                n.KGSC = self.readTrackHeaderVec3(reader, self.unique_tracks)
                self.unique_tracks++
            }
            else {
                printf("unknown tags:%s\n", tag);
            }
        }

        return n
    }

    //PIVOT
    void readPIVT(BufferReader* reader, int size){
        self.pivots = reader.readVec3Array(size / 12)
        printf("\tPIVT:%s\n", 
        ""
        // pivots.toString().str
        )
    }
    //
    void readFAFX(BufferReader* reader, int size){
        for int i = 0; i < size / 340; i++{
            FaceFX@ e = new FaceFX()
            self.faceFxList.add(e)

            e.name = reader.readString(80)
            e.path = reader.readString(260)
            printf("\tfafx. name:%s\n", e.name.str)
            printf("\tfafx. path:%s\n", e.path.str)
        }
        // printf("\tPIVT:%s\n", pivots.toString().str)
    }
    //cameras
    void readCAMS(BufferReader* reader, int size){
        int total_size = 0
        while total_size < size{
            int subchunk_size = reader.readInt()
            total_size += subchunk_size
            printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size)

            reader.advance(subchunk_size - 4)
        }
    }
    //TextureAnimations
    void readTXAN(BufferReader* reader, int size){
        int total_size = 0
        while total_size < size{
            int subchunk_size = reader.readInt()
            total_size += subchunk_size
            printf("\tsub size:%d/%d/%d\n", subchunk_size, total_size, size)

            reader.advance(subchunk_size - 4)
        }
    }
    //BindPose
    void readBPOS(BufferReader* reader, int size){
        int vec3_cnt = reader.readInt()
        self.bindPose = reader.readVec3Array(vec3_cnt)
        printf("BPOS v3 cnt;%d\n", vec3_cnt)
    }



    bool load(BufferReader *reader){
        String@ s = reader.readString(4)
        printf("magic number:%s\n", s.str)
        if !s.equals("MDLX"){
            return false
        }

        //读取块
        while reader.remaining() > 0 {
            char header[5];
            reader.readChars(header, 4, true);
            int size = reader.readInt()
            printf("chunk header:%s, size:%d. remaining:%d\n", header, size, reader.remaining())

            if strcmp(header, "VERS") == 0{
                self.version = reader.readInt()
                printf("\tversion:%d\n", self.version)
            }
            else if strcmp(header, "MODL") == 0{
                String@ name = reader.readString(80)
                String@ animationFilename = reader.readString(260)
                Extend extend = self.readExtend(reader)
                int blend_time = reader.readInt()
                printf("\tname:%s\n", name.str);
                printf("\tanimationFilename:%s\n", animationFilename.str);
                printf("\textend: %s\n", extend.toString().str);
                printf("\tblend_time:%d \n", blend_time)
            }
            else if strcmp(header, "GEOS") == 0{
                self.readGEOS(reader, size)
            }
            else if strcmp(header, "GEOA") == 0{
                self.readGEOA(reader, size)
            }
            else if strcmp(header, "PIVT") == 0{
                self.readPIVT(reader, size)
            }
            else if strcmp(header, "CAMS") == 0{
                self.readCAMS(reader, size)
            }
            else if strcmp(header, "EVTS") == 0{
                self.readEVTS(reader, size)
            }
            else if strcmp(header, "HELP") == 0{
                self.readHELP(reader, size)
            }
            else if strcmp(header, "ATCH") == 0{
                self.readATCH(reader, size)
            }
            else if strcmp(header, "BONE") == 0{
                self.readBONE(reader, size)
            }
            else if strcmp(header, "FAFX") == 0{
                self.readFAFX(reader, size)
            }
            else if strcmp(header, "TEXS") == 0{
                self.readTEXS(reader, size)
            }
            else if strcmp(header, "CLID") == 0{
                self.readCLID(reader, size)
            }
            else if strcmp(header, "CORN") == 0{
                self.readCORN(reader, size)
            }
            else if strcmp(header, "TXAN") == 0{
                self.readTXAN(reader, size)
            }
            else if strcmp(header, "BPOS") == 0{
                self.readBPOS(reader, size)
            }
            else if strcmp(header, "LITE") == 0{
                self.readLITE(reader, size)
            }
            else if strcmp(header, "MTLS") == 0{
                self.readMTLS(reader, size)
            }
            else if strcmp(header, "SEQS") == 0{
                self.readSEQS(reader, size)
            }
            else if strcmp(header, "GLBS") == 0{
                self.readGLBS(reader, size)
            }
            else {
                reader.advance(size) //跳过未知块
            }
        }
        return true
    }
    bool loadByPathCstr(const char *path){
        Buffer@ buf = Buffer_readFile(path)
        BufferReader@ br = mkBufferReader(buf)
        bool ok = self.load(br)
        return ok
    }

    // Geometry@ mkGeometry(){
    //     Geometry@ geom = new Geometry()
    //     Buffer@ vtxs = new Buffer()
    //     Buffer@ nmls = new Buffer()
    //     Buffer@ face = new Buffer()
    //     Buffer@ uvs = new Buffer()



    //     // self.setAttrByBuffer("position", vtxs, 3)
    //     // self.setAttrByBuffer("normal", nmls, 3)
    //     // self.setAttrByBuffer("uv", uvs, 2)
    //     // self.setIboByBuffer(face)
    //     return geom
    // }
}

class MkMdx {
    MdxReader@ mr

    Skeleton@ ske = new Skeleton()


    void mkSkeleton(){
        List@ bones = new List()
        printf("\n========================================mkSkeleton\n")
        List@ roots = new List()
        //创建bone
        for int i = 0; i < self.mr.helps.size(); i++{
            MdxNode* help = self.mr.helps.get(i)

            // printf("help[%d:%d]\n", help.id, help.parentId)
            Bone@ bone = new Bone()
            help.bone = bone

            bone.position = self.mr.pivots.get(help.id)
            if help.parentId != -1{ //pivots是全局坐标,要转为局部坐标
                Vec3 parentPos = self.mr.pivots.get(help.parentId)
                bone.position = bone.position.sub(parentPos)
            }
            bone.originPosition = bone.position

            bones.set(help.id, bone)

            char name[128]
            sprintf(name, "%s;%d:%d; pos:%.2f,%.2f,%.2f", help.name.str, help.id, help.parentId,
                bone.position.x,
                bone.position.y,
                bone.position.z,
            )
            bone.name.set(name)

            bone.parentId = help.parentId
            bone.id = help.id
        }
        //创建bone
        for int i = 0; i < self.mr.bones.size(); i++{
            MdxBone* mdxbone = self.mr.bones.get(i)
            // printf("bone[%d:%d]\n", mdxbone.node.id, mdxbone.node.parentId)

            Bone@ bone = new Bone()
            mdxbone.node.bone = bone



            bone.position = self.mr.pivots.get(mdxbone.node.id)
            if mdxbone.node.parentId != -1{ //pivots是全局坐标,要转为局部坐标
                Vec3 parentPos = self.mr.pivots.get(mdxbone.node.parentId)
                bone.position = bone.position.sub(parentPos)
            }
            bone.originPosition = bone.position
            bones.set(mdxbone.node.id, bone)

            char name[128]
            sprintf(name, "%s;%d:%d; pos:%.2f,%.2f,%.2f", mdxbone.node.name.str, mdxbone.node.id, mdxbone.node.parentId,
                bone.position.x,
                bone.position.y,
                bone.position.z,
            )
            bone.name.set(name)

            bone.parentId = mdxbone.node.parentId
            bone.id = mdxbone.node.id
        }

        //构建父子关系
        for int i = 0; i < self.mr.helps.size(); i++{
            MdxNode* help = self.mr.helps.get(i)
            Bone* bone = (Bone*)bones.get(help.id)
            Bone* parentBone = (Bone*)bones.get(help.parentId)

            if parentBone{
                parentBone.appendChild(bone)
            }
            else {
                roots.add(bone)
            }
        }
        for int i = 0; i < self.mr.bones.size(); i++{
            MdxBone* mdxbone = self.mr.bones.get(i)
            Bone* bone = (Bone*)bones.get(mdxbone.node.id)
            Bone* parentBone = (Bone*)bones.get(mdxbone.node.parentId)
            if parentBone{
                parentBone.appendChild(bone)
            }
            else {
                roots.add(bone)
            }
        }



        for int i = 0; i < roots.size(); i++{
            Bone *root = (Bone*)roots.get(i)
            self.ske.appendChild(root)
        }


        //构建矩阵
        self.ske.updateWorldTransformAndSubtree()

        //构建 bindPoseInverse
        for int i = 0; i < bones.size(); i++{
            Bone* bone = (Bone*)bones.get(i)
            if bone == null {
                continue
            }
            bone.bindPose = bone._world_transform
            bone.bindMatrixInverse = bone.bindPose.invert()
            // printf("%d=>%s\n", i, bone.name.str)
        }

        // printf("bone tree \n")

        printNodeTree(self.ske, 0)
    }
}

void testMdxReader{
    // Buffer@ buf = Buffer_readFile("../asset/Human/Farm/Farm.mdx")
    // printf("buf size:%d\n", buf.size);
    // BufferReader@ br = mkBufferReader(buf)

    MdxReader@ r = new MdxReader()
    r.loadByPathCstr("../asset/Units/Human/Footman/Footman.mdx")
    // r.load(br)
    printf("load complete\n")


    MdxSeqPlayer@ player = new MdxSeqPlayer()
    player.init(r)


    for int i = 0; i < player.seqs.size(); i++{
        Sequence* seq = (Sequence*)player.seqs.get(i)
        printf("seq:%s\n", seq.toString().str)
    }
    Sequence *seq = player.findSeq("Stand - 2")
    printf("complete. seq:%s\n", seq.toString().str)


    player.play("Stand - 1")

    DrawCtx @ctx = new DrawCtx()
    ctx.dtMs = 500
    player.tick(ctx)
    Time_sleepSec(1)

    player.tick(ctx)
    Time_sleepSec(1)
    player.tick(ctx)


    // player.findSeq("")
}