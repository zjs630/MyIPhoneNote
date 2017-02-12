1,CCNode is the parent class for all other node classed,including the two
most fundamental ones:CCScene and CCLayer.
2,
1 To create a new node: // 生成一个新的节点 :
CCNode* childNode = [CCNode node];

2 To add the new node as child: //将新节点添加为子节点:
[myNode addChild:childNode z:0 tag:123];
//z参数决定了the draw order of the node.
The node with the lowest z value is drawn first;//拥有最小Z值的节点会首先被绘制。
The one with the highest z value is draw last;//拥有最大Z值的节点最后一个被绘制。
If multiple nodes have the same z value, they are simply drawn in the order they were added.
//他们的绘 制顺序将由他们的添加顺序来决定。
3 To retrieve the child node: // 获取子节点:
CCNode* retrievedNode = [myNode getChildByTag:123];
//如果有多个节点拥有相同的tag数值,getChildByTag将把找到的第一个节
//点返回。其它节点将不能够再被访问。所以你要确保为你的节点指定独有的tag
//数值。

4 To remove the child node by tag; cleanup will also stop any running actions:
//通过tag删除子节点;cleanup会停止任何运行中的动作:
[myNode removeChildByTag:123 cleanup:YES];

5 To remove the node if you have a pointer to it: 
//通过节点指针删除节点:
[myNode removeChild:retrievedNode];

6 To remove every child of the node: 
//删除一个节点的所有子节点:
[myNode removeAllChildrenWithCleanup:YES];

7 To remove myNode from its parent: 
//从myNode的父节点删除myNode:
[myNode removeFromParentAndCleanup:YES];
