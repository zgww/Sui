# FMS 校准接口文档

基础URL: `http://{fms_server}:8900/api/calibration`

所有接口均使用 POST，Content-Type: `application/json`。

---

## 1. X轴迭代校准

```
POST /api/calibration/x-axis-iter
```

**用途**: 到位后自动校准机器人在航点处的X轴偏移。通过 ORB 特征匹配比较参考图与当前相机画面，计算偏移量并控制机器人微调位置。

**请求体**:
```json
{
  "rid": 54,           // 机器人工控机ID (robot_id, 非FMS内部DB id)
  "node_id": "abc123"  // 航点或动作点的UUID (对应WaypointsTree.json中节点的id字段)
}
```

**响应 (成功)**:
```json
{
  "ok": true,
  "calibrated": true,
  "converged": true,
  "message": "X轴校准成功, 偏移量已修正",
  "steps": ["... 各步骤描述 ..."],
  "iterations": [
    {
      "iteration": 1,
      "x_offset_px": 12.5,
      "y_offset_px": 3.2,
      "total_matches": 150,
      "inlier_count": 120,
      "converged": false,
      "move_distance": 0.05
    }
  ],
  "debug_session": "abc123def456"
}
```

**响应 (失败)**:
```json
{
  "ok": false,
  "calibrated": false,
  "converged": false,
  "message": "ORB配准失败: 内点数不足",
  "steps": ["... 各步骤描述 ..."],
  "iterations": [],
  "debug_session": null
}
```

**调用方**: C++ `FmsCalibXAxis` 行为树节点、FMS前端航点树管理页面

**超时**: 建议客户端设置 5 分钟超时（最多10次迭代，每次含PTZ+抓拍+配准+移动）

**错误码**:
| HTTP Status | 含义 |
|-------------|------|
| 200 | 正常（通过 ok/calibrated 字段判断成功） |
| 404 | 机器人或航点不存在 |
| 500 | 服务器内部错误 |

---

## 2. 云台迭代校准

```
POST /api/calibration/ptz-iter
```

**用途**: 云台调整后校准 PTZ 位姿。通过 ORB 匹配参考图（动作点的 `snap_shot_url`）与当前画面，迭代调整 pan/tilt 直到偏移收敛到阈值内。

**请求体**:
```json
{
  "rid": 54,           // 机器人工控机ID (robot_id)
  "node_id": "def456"  // 动作点的UUID (必须是 ActionNode, 需要配置 snap_shot_url 作为参考图)
}
```

**响应 (成功, 已收敛)**:
```json
{
  "ok": true,
  "calibrated": true,
  "converged": true,
  "message": "云台校准成功",
  "steps": [
    "动作点: 低压室应急灯 (ID: 54fe0a85d622...)",
    "参考图: snap_shot_url=http://...",
    "参考图加载成功",
    "── 开始云台校准 (最多8次迭代, 阈值10px) ──",
    "━━━ 第 1 轮 ━━━",
    "等待视频流稳定(5秒)…",
    "抓拍成功",
    "ORB配准完成: x_off=5.2px y_off=1.3px total=5.4px",
    "已收敛 total=5.4px",
    "PTZ修正: pan=68.12→68.14 tilt=-37.57→-37.55 arrived=yes"
  ],
  "iterations": [
    {
      "iteration": 1,
      "x_offset_px": 5.2,
      "y_offset_px": 1.3,
      "total_offset_px": 5.4,
      "total_matches": 200,
      "inlier_count": 180,
      "converged": true,
      "pan_delta": 0.02,
      "tilt_delta": -0.02,
      "ptz_from": {"pan": 68.12, "tilt": -37.57, "zoom": 5.6},
      "ptz_to": {"pan": 68.14, "tilt": -37.55, "zoom": 5.6}
    }
  ],
  "debug_session": "abc123def456",
  "max_iterations": 8,
  "threshold_px": 10.0,
  "ptz_pose": {"pan": 68.14, "tilt": -37.55, "zoom": 5.6}
}
```

**ptz_pose 字段**: 校准后的云台位姿，C++ 行为树写入黑板值。仅在 converged=true 时可靠。

**调用方**: C++ `FmsCalibPtz` 行为树节点、FMS前端航点树管理页面

**超时**: 建议客户端设置 3 分钟超时（最多8次迭代，每次含等待+抓拍+配准+PTZ调整）

---

## 3. 单次配准（不移动）

```
POST /api/calibration/register
```

**用途**: 仅执行 ORB 配准，不控制机器人移动。用于调试、查看偏移量。

**响应**: 同上结构，但不含 `calibrated` 字段，改为 `registered`。

---

## 4. 单次X轴校准

```
POST /api/calibration/x-axis-step
```

**用途**: 执行一次X轴校准（调整PTZ → 抓拍 → ORB配准 → 移动机器人一步）。

---

## 5. 单次云台校准

```
POST /api/calibration/ptz-step
```

**用途**: 执行一次云台校准（等待稳定 → 抓拍 → ORB配准 → 调整PTZ一步）。

---

## C++ 行为树节点使用

### FmsCalibXAxis

```xml
<FmsCalibXAxis waypoint_id="{current_waypoint_uuid}" />
```

- 输入: `waypoint_id` (航点UUID)
- 输出: 无
- 返回: SUCCESS / FAILURE
- 日志标签: `[FMS_CALIB_X]`

### FmsCalibPtz

```xml
<FmsCalibPtz waypoint_id="{current_action_uuid}" ptz_pose="{ptz_pose}" />
```

- 输入: `waypoint_id` (动作点UUID)
- 输出: `ptz_pose` (校准后的PTZ位姿JSON字符串，写入黑板)
- 返回: SUCCESS / FAILURE
- 日志标签: `[FMS_CALIB_PTZ]`

**注册** (在 `bt_factory.cpp` 中):
```cpp
FmsCalibXAxisNode::RegisterNodeType(factory);
FmsCalibPtzNode::RegisterNodeType(factory);
```

---

## rid 参数说明

`rid` 同时接受两种值（后端自动匹配）:
1. **robot_id**: 工控机自身的ID (如 54, 56) — C++ 调用时传入
2. **DB id**: FMS 数据库主键 (如 1, 2) — 前端页面调用时传入

后端查找顺序: 先按 `robot_id` 匹配，再按 `id` 匹配。

---

## 注意事项

1. 校准依赖机器人 HTTP API (cmd 协议) 在线
2. 摄像头抓拍通过 RTSP 子码流 (10秒超时)，工控机离线时快速返回失败
3. 参考图来源:
   - x-axis: OrbRegistration 节点的 `refImageUrl` (本地 navRefImg/xxx.jpg)
   - ptz: ActionNode 的 `snap_shot_url` (HTTP 下载)
4. 调试图片保存到 `data/robot/{db_id}/calib_debug/{session_id}/`
