
1,重复有限的次数的动作

- (void) OnRepeat:(id) sender
{
	CGSize s = [[CCDirector sharedDirector] winSize];
	CGPoint p = ccp(s.width/2, 50);
	
	sprite.rotation = 0;
	[sprite setPosition:p];
	
	id ac1 = [CCMoveTo actionWithDuration:2 position:ccp(s.width - 50, s.height - 50)];
	id ac2 = [CCJumpBy actionWithDuration:2 position:ccp(-400, -200) height:30 jumps:5];
	id ac3 = [CCJumpBy actionWithDuration:2 position:ccp(s.width/2, 0) height:20 jumps:3];
	
	id seq = [CCSequence actions:ac1, ac2, ac3, nil];
	
	[sprite runAction:[CCRepeat actionWithAction:seq times:3]];	
	
}
2，无限的重复，
RepeatForever 是从 Action 类直接派生的,因此无法参不序列和同步;自身也无
法反向执行。该类的作用就是无限期执行某个动作戒动作序列,直到被停止。
CGSize s = [[CCDirector sharedDirector] winSize];
CGPoint p = ccp(100, 50);

CCSpriteSheet *mgr = (CCSpriteSheet *)[self getChildByTag:4];

CCAnimation *animation = [CCAnimation animationWithName:@"flight" delay:0.1f];
for(int i=0;i<3;i++) {
	int x= i % 3;
	[animation addFrameWithTexture:mgr.texture rect:CGRectMake(x*32, 0, 31, 30) ];
}		

id action = [CCAnimate actionWithAnimation: animation];

[sprite runAction:[CCRepeatForever actionWithAction:action]];			

ccBezierConfig bezier;		

sprite.rotation = 0;
[sprite setPosition:p];

// bezier.startPosition = ccp(0,0);
bezier.controlPoint_1 = ccp(0, s.height/2);
bezier.controlPoint_2 = ccp(150, s.height/2);
bezier.endPosition = ccp(200,0);

id ac10 = [CCBezierBy actionWithDuration:3 bezier:bezier];
id ac11 = [CCTintBy actionWithDuration:0.5 red:0 green:255 blue:255];

id ac1 = [CCSpawn actions:ac10, [CCRepeat actionWithAction:ac11 times:4], nil];
id ac2 = [CCSpawn actions:[ac10 reverse], [CCRepeat actionWithAction:ac11 times:4], nil];


[sprite runAction:[CCRepeatForever actionWithAction:[CCSequence actions:ac1, ac2,nil]]];

