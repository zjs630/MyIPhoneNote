1,Nodes can also run actions.
actions can move,rotate, and scale nodes and do other things with nodes over time;
2,
a,声明一个动作，
//Here's an action declaration:
CCAction *action = [CCBlink actionWithDuration:10 blinks:20];
action.tag = 234;
b,运行这个动作使节点闪烁//Running the action makes the node blinks
[myNode runAction:action];
c,If you need to access the action at a later time, you get it by its tag:
CCAction *retrievedAction = [myNode getActionByTag:234];
d,停止动作
//You can stop the cation by tag:
[myNode stopActionByTag:234];
//Or you can stop it by pointer:
[myNode stopAction:action];
//Or you can stop all actions running on this node:
[myNode stopAllActions];
3，//判断精灵是否在运行动画
if ([spider numberOfRunningActions] == 0) {
	// 这只蜘蛛没有移动,所以我们可以跳过对它的碰撞测试
	continue;
}
// 得到主角精灵和蜘蛛精灵之间的距离 
float actualDistance = ccpDistance(player.position, spider.position);
// 检查是否两个物体已经碰撞 
if (actualDistance < maxCollisionDistance) {
	//游戏结束
}
1，运行某个动作的方法:
//2秒内移动到某个位置
CCMoveTo *actionTo = [CCMoveTo actionWithDuration: 2 position:ccp(s.width-40, s.height-40)];
[sprite runAction: actionTo];
2，停止某个动作。
//You should never call "[action stop]" manually. 
//Instead, use: "[target stopAction:action];"
3，cocos2d的动作可以分两种。一种是“Instant actions”//即时动作。比如设置节点的visible属性。
另一种是“Interval actions”//时间间隔动作。
4，Repeating Actiongs//重复动作
//例如让某一节点永远的旋转下去，如：永远旋转的轮子。
CCRotateBy *rotateBy = [CCRotateBy actionWithDuration:2 angle:360];//2秒旋转360度
CCRepeatForever *repeat = [CCRepeatForever actionWithAction:rotateBy];
[myNode runAction:repeat];
5,Ease actions
//“舒缓动作”允许你改变在一段时 间内发生的动作效果。
// 我想让myNode在3秒钟之内移动到100,200坐标点 
CCMoveTo* move = [CCMoveTo actionWithDuration:3 position:CGPointMake(100, 200)]; 
// 节点应该慢慢启动,然后在移动过程中减速 
//rate参数是用来决定舒缓 动作的明显程度。此参数只有在大于1的情况下才能看到舒缓动作的效果:
CCEaseInOut* ease = [CCEaseInOut actionWithAction:move rate:4]; 
[myNode runAction:ease];



8，各种基本动作
//变色//红色
CCTintTo* tint1 = [CCTintTo actionWithDuration:4 red:255 green:0 blue:0];
9，根据重力感应，左右移动精灵。

-(void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
	CGPoint pos = player.position; 
	pos.x += acceleration.x * 10; 
	player.position = pos;
}

-(void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
	// 控制减速的速率(值越低=可以更快的改变方向) 
	float deceleration = 0.4f; 
	//加速计敏感度的值越大,主角精灵对加速计的输入就越敏感 
	float sensitivity = 6.0f;
	// 最大速度值 float maxVelocity = 100;
	// 基于当前加速计的加速度调整速度
	playerVelocity.x = playerVelocity.x * deceleration + acceleration.x * sensitivity;
	// 我们必须在两个方向上都限制主角精灵的最大速度值 
	if (playerVelocity.x > maxVelocity) {
		playerVelocity.x = maxVelocity;
	} 
	else if (playerVelocity.x < - maxVelocity) {
		playerVelocity.x = - maxVelocity;
	}
}
