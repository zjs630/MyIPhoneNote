1，运行某个动作的方法:
//2秒内移动到某个位置
CCMoveTo *actionTo = [CCMoveTo actionWithDuration: 2 position:ccp(s.width-40, s.height-40)];
[sprite runAction: actionTo];
2，停止某个动作。
//You should never call "[action stop]" manually. 
//Instead, use: 
[target stopAction:action];
//or [target stopActionByTag:2];
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