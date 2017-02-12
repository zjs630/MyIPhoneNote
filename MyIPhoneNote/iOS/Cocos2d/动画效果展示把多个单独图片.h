如果你想把一组图片以动画效果展示，首先设置好每一帧的持续时间，
一般在 1/24 秒左右，然后用下面的代码实现动画效果。

-(void) onEnter {
	
	[super onEnter];    
	
	roadSprite=[[Sprite spriteWithFile:@"R00.png"] retain];
	[roadSprite setPosition:ccp(240,160)];
	[self addChild:roadSprite z:5];
	
	Animation* animation = [Animation animationWithName:@"animation" delay:1.0f];
	for( int i=0;i<25;i++)
	{
		
		[animation addFrameWithFilename: [NSString stringWithFormat:@"R%02d.png", i]];
		
	}
	id action1 = [Animate actionWithAnimation: animation];
	[roadSprite runAction:action1];
}