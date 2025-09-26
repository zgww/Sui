import { Consts } from "@/PathAnalyse/Consts";
import { Arr } from "../Naga/Arr";
import { Options } from "../Naga/Options";
import * as THREE from "three";
import { SceneTransform } from "@/PathAnalyse/SceneTransform";

/**
 * 画刻度
 */
export class DrawDegree2 {
    options = [
        { value: 0.2, degrees: [500] },
        { value: 0.5, degrees: [100] },
        { value: 0.8, degrees: [80] },
        { value: 1, degrees: [50] },
        { value: 1.2, degrees: [45] },
        { value: 1.4, degrees: [40] },
        { value: 1.6, degrees: [35] },
        { value: 1.8, degrees: [30] },
        { value: 2, degrees: [25] },
        { value: 4, degrees: [10] },
        { value: 6, degrees: [5] },
        { value: 10, degrees: [5] },
        { value: 16, degrees: [2] },
        { value: 26, degrees: [2] },
        // { value: 40, degrees: [1] },
        { value: 60, degrees: [1] },
        // { value: 80, degrees: [1] },
        { value: 100, degrees: [1] },
        { value: 150, degrees: [1] },
        { value: 200, degrees: [1] },
    ];
    /**
     * 预生成中间分段。  更好控制,体验也更好
     */
    levelOptions = [];
    line_len = 10; // 线长
    bg = new THREE.Color('#30313b');
    lineColor = new THREE.Color('#17171c');
    textColor = new THREE.Color('#e6e6e6');
    cur_option = null;
    cur_scale = null;
    font = null;
    font_size = 11;
    textOffset = new THREE.Vector3(4, -3);
    constructor() {
        this.genLevels();
    }
    /**选择最近的缩放级别 */
    chooseNearestLevelByScale(scale) {
        for (let e of this.levelOptions) {
            if (scale <= e.value) {
                return e;
            }
        }
        return Arr.last(this.levelOptions);
    }
    /**
     *
     * @param count 每级生成多少个
     */
    genLevels(count = 4) {
        let opts = [];
        for (let i = 0; i < this.options.length - 1; i++) {
            let cur = this.options[i];
            let next = this.options[i + 1];
            let step = (next.value - cur.value) / count;
            for (let j = cur.value; j < next.value; j += step) {
                opts.push({
                    value: j,
                    degree: cur.degrees[0],
                });
            }
        }
        let last = Arr.last(this.options);
        opts.push({
            value: last.value,
            degree: last.degrees[0],
        });
        this.levelOptions = opts;
        return opts;
    }
    get_cur_option(scale) {
        if (scale == this.cur_scale) {
            if (this.cur_option) {
                return this.cur_option;
            }
        }
        this.cur_scale = scale;
        this.cur_option = Options.in_inc_segment(this.options, scale);
        return this.cur_option;
    }
    set_scale(scale) {
        this.get_cur_option(scale);
        return this;
    }
    /**
     * 计算绘制起点
     * 需要先调用set_scale
     * @param scale
     * @param min
     * @param max
     */
    calc_draw_start(min) {
        let last_degree = Arr.last(this.cur_option.degrees) as number;
        let start = min - (min % last_degree);
        return start;
    }
    draw(c2d, sceneTransform:SceneTransform, start_x, start_y, max, is_hor, mouse_x, mouse_y) {
        if (!this.cur_option){
            return
        }
        let min = is_hor ? start_x : start_y;
        let start = this.calc_draw_start(min);
        let cur = start;
        let degrees = this.cur_option.degrees;
        let len = degrees.length;
        let line_len = this.line_len;
        // // 背景
        // if (this.bg) {
        //     c2d.fillStyle = this.bg.getStyle();
        //     if (is_hor) {
        //         c2d.fillRect(start_x, start_y, max - start_x, this.line_len);
        //     }
        //     else {
        //         c2d.fillRect(start_x, start_y, this.line_len, max - start_y);
        //     }
        // }
        // 刻度线
        // 绘制
        // c2d.strokeStyle = this.lineColor.getStyle();
        this.font = `${(this.font_size)}px Arial`;
        c2d.font = this.font;
        c2d.beginPath();
        c2d.lineWidth = 1
        // c2d.lineWidth = 1 / this.cur_scale;
        c2d.fillStyle = this.textColor.getStyle();
        // console.log('font', this.font)
        let text_offset = 2 ;
        let text_offset_x = 2;
        let hpi = Math.PI / 2;
        let mat = sceneTransform.mat
        let vec3 = new THREE.Vector3()

        let isReverse = false
        if (cur > max){ // 如果y轴翻转了
            // [cur, max] = [max, cur]
            isReverse = true
        }
        for (let i = 0; isReverse ? cur >= max :  cur <= max; i++) {
            if (is_hor) {
                
                vec3.set(cur, start_y, 0)
                vec3.applyMatrix4(mat)

                c2d.moveTo(vec3.x, vec3.y);
                c2d.lineTo(vec3.x, vec3.y + 10);

                c2d.fillText(
                    cur.toFixed(0), 
                    vec3.x + 3, 
                    vec3.y + 10);
            }
            else {
                vec3.set(start_x, cur, 0)
                vec3.applyMatrix4(mat)

                c2d.moveTo(vec3.x, vec3.y);
                c2d.lineTo(vec3.x + 10, vec3.y);
                // c2d.fillText(cur.toFixed(0), start_x, cur - text_offset)
                // c2d.translate(start_x + 3 , cur + text_offset);
                // c2d.fillText(cur.toFixed(0), this.textOffset.x / this.cur_scale, this.textOffset.y / this.cur_scale);
                // c2d.save();
                // c2d.rotate(hpi);
                c2d.fillText(
                    cur.toFixed(0), 
                    vec3.x + 2, 
                    vec3.y + 15);
                // c2d.restore();
            }
            //步进
            let idx = i % len;
            let gap = degrees[idx];
            if (isReverse){
                cur -= gap;
            } else {
                cur += gap;
            }
        }
        c2d.stroke();
        // // 画鼠标位置
        // if (mouse_x != null) {
        //     // 水平
        //     c2d.beginPath();
        //     c2d.moveTo(mouse_x, start_y);
        //     c2d.lineTo(mouse_x, start_y + line_len);
        //     c2d.moveTo(start_x, mouse_y);
        //     c2d.lineTo(start_x + line_len, mouse_y);
        //     c2d.strokeStyle = 'red';
        //     c2d.stroke();
        // }
    }
    drawDegree(c2d:CanvasRenderingContext2D, sceneTransform:SceneTransform, sceneCanvas, curViewPos) {
        let nv2 = sceneTransform.getScenePositionOfViewPos(new THREE.Vector3());
        let rb = sceneTransform.getScenePositionOfViewPos(new THREE.Vector3(sceneCanvas.width, sceneCanvas.height));
        let mousePositionInScene = null;
        //鼠标在范围内
        let box2 = Consts.box2.set(Consts.v2s[0].set(0, 0), Consts.v2s[1].set(sceneCanvas.width, sceneCanvas.height));
        if (curViewPos){
            let viewPosition = curViewPos;
            if (box2.containsPoint(Consts.v2.set(viewPosition.x, viewPosition.y))) {
                mousePositionInScene = sceneTransform.getScenePositionOfViewPos(viewPosition);
            }
        }

        // c2d.fillStyle = 'red'
        // c2d.fillRect(0, 0, 100, 100)

        { //画鼠标位置
            c2d.lineWidth = 1
            c2d.strokeStyle = 'red';

            let len = 20

            // 水平
            c2d.beginPath();
            c2d.moveTo(0, curViewPos.y);
            c2d.lineTo(len, curViewPos.y);

            c2d.moveTo(curViewPos.x, 0);
            c2d.lineTo(curViewPos.x, len);
            c2d.stroke();
        }

        // 不同缩放下，线长也要变
        this.line_len = 20 / sceneTransform.scale.x;



        this.set_scale(sceneTransform.scale.x);

        // c2d.save()
        // c2d.translate(sceneTransform.position.x, sceneTransform.position.y)
        // c2d.scale(sceneTransform.scale.x, sceneTransform.scale.y)
        c2d.strokeStyle = 'red';
        c2d.fillStyle = 'rgba(128, 128, 128, 0.3)'
        c2d.fillRect(0, 0, sceneCanvas.width, 15)
        this.draw(c2d, sceneTransform, nv2.x, nv2.y, rb.x, true, mousePositionInScene?.x, mousePositionInScene?.y);

        c2d.strokeStyle = 'green';
        c2d.fillStyle = 'rgba(128, 128, 128, 0.3)'
        c2d.fillRect(0, 15, 15, sceneCanvas.height)
        this.draw(c2d, sceneTransform, nv2.x, nv2.y, rb.y, false, mousePositionInScene?.x, mousePositionInScene?.y);
        // c2d.restore()
    }
}

