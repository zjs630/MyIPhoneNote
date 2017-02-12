同一个场景里设置多个层作为关卡 如果你有一个复杂的用户界面,并且在关卡转换时不允许重置游戏场景的话, 
你就需要在同一个场景里用不同的层来加载和显示不同的关卡。在转换关卡时, 
你可能会将游戏角色和其它的游戏物体保持在同一个位置。
你可能使用几个变量来保存当前的游戏状态信息和用户界面设置信息,比如说 
仓库里的物品。如果你使用多个场景作为关卡的话,在转换关卡的时候,你就 
需要做很多工作来保存和重置游戏设置,还有重置所有的视觉元素。
这个方式很适合物品寻找类或者冒险类游戏,因为玩家需要在不同的房间之间 移动。
特别是你想在替换关卡内容的过程中使用动画的情况下。
CCMultiplexLayer类可被用于这种方式中。它可以同时包含多个节点,但是任 
意时间里只有一个节点是有效的。
唯一的缺点是你不能在层之间使用过渡效果。因为任意时间里只能有一个 
层是可视的,所以任何过渡效果都是不可能发生的。

使用CCMultiplexLayer类在不同层之间进行转换
CCLayer* layer1 = [CCLayer node]; 
CCLayer* layer2 = [CCLayer node]; 
CCMultiplexLayer* mpLayer = [CCMultiplexLayer layerWithLayers:layer1, layer2, nil];
// 转换到layer2,layer1还是mpLayer的子节点 
[mpLayer switchTo:1];
// 转换到layer1,从mpLayer里移除layer2,并且释放layer2占用的内存 
// 在使用下述方法以后,你不能够再转换回layer2(索引:1)了 
[mpLayer switchToAndReleaseMe:0];