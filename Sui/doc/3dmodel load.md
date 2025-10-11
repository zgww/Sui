# 怎么去加载3d模型

3d模型自己带了节点的。
所以对应到prefab中，也需要有节点对应。
同时，还需要考虑节点挂载的问题。。


# 方案1 
加载时，同时构建出节点树。
实例化时，重用该节点树? 只需要obj3d类型的节点做占位即可


这样子，挂载问题就不需要考虑

# 方案2

prefab中只是个loader节点。
实例化prefab时，现创建模型的节点。该节点不序列化prefab
挂载的节点在序列化和实例化时做特殊处理

loader
    mount Node at model nodeA by name
    mount Node2 at model nodeB by name

# 方案3 [选用,但可暂不实现,只是实现Loader就很容易了]
prefab中只是个loader节点。类似于sui中的outKids的机制
挂载的节点挂载在loader节点下面，由loader节点去放置到正确的子节点下,类似于sui的placeKid by name


但是此方案，怎么在hier中体现 子树呢?

需要在dsl中加入mount的功能?

hier允许显示内部节点，但是置灰，不可改。
节点可以挂载到内部节点上，但是在Prefab实际上挂载在loader上， 附带一个mount属性

方案3还同时支持了 嵌套prefab的挂载问题。两个问题一致了。

# 方案4

类似于Godot的BoneAttachment
BoneAttachment可以指定要同步的骨骼的变换矩阵。 
节点就是普通的节点。挂载到BoneAttachment下，boneAttachment指定要同步的骨骼的名称，让BoneAttachment同步目标骨骼的变换。 这样就达到了挂载的目的


