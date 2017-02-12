
动画就是让精灵自身的连续执行一段影像,形成模拟运动的效果:行走时的精灵状
态、打斗时的状态等。
1,有限的重复次数。
- (void) OnAnimation:(id) sender
{
	CCSpriteSheet *mgr = (CCSpriteSheet *)[self getChildByTag:4];
	
	CCAnimation *animation = [CCAnimation animationWithName:@"flight" delay:0.2f];
	// 每帧的内容定义。
	for(int i=0;i<3;i++) {
		int x= i % 3;
		[animation addFrameWithTexture:mgr.texture rect: CGRectMake(x*32, 0, 31, 30) ];
	}		
	
	id action = [CCAnimate actionWithAnimation: animation];
	[sprite runAction:[CCRepeat actionWithAction:action times:10]];		
	
}
