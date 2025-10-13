# transform gizmo


## 区分world/local

缩放只有local


rotate的world/local的区别在于 矩阵乘法的位置。 左乘还是右乘
参考threejs/TransformControl


translate的world/local的区别，在于要怎么对position的增量作旋转。 