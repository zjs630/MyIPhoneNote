1,取图片的一部分。
 //载入飞船图像集。整个图像集迕载入一次,可以被使用多次,
CCSpriteSheet *mgr = [CCSpriteSheet spriteSheetWithFile:@"flight.png" capacity:5];
[self addChild:mgr z:0 tag:4];

CCSprite *sprite = [CCSprite spriteWithTexture:mgr.texture rect:CGRectMake(0,0,31,30)];//选取一个矩形内的图片作为精灵
sprite.scale = 1.5;
sprite.anchorPoint = ccp(0, 1);//参考点左上角
sprite.position = ccp(0, 480);//位置左上角
[mgr addChild:sprite z:1 tag:5];
2,重复播放几张图片，图片大小31*30
 //载入飞船图像集。整个图像集迕载入一次,可以被使用多次
CCSpriteSheet *mgr = [CCSpriteSheet spriteSheetWithFile:@"flight.png" capacity:5];
[self addChild:mgr z:0 tag:4];
// Add flight
CCSprite *flight = [CCSprite spriteWithTexture:mgr.texture rect:CGRectMake(0,0,31,30)];
flight.position = ccp(160, 30);
flight.scale = 1.6;
[mgr addChild:flight z:1 tag:99];

// 设定动画的每帧的内容
CCAnimation *animation = [CCAnimation animationWithName:@"flight" delay:0.2f];
for(int i=0;i<3;i++) {
	int x= i % 3;
	[animation addFrameWithTexture:mgr.texture rect:CGRectMake(x*32, 0, 31, 30) ];
}		
// 基于动画创建动作。// 主角精灵不断重复动作,实现动态飞行效果
id action = [CCAnimate actionWithAnimation: animation];
[flight runAction:[CCRepeatForever actionWithAction:action]];






