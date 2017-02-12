/*精灵是整个游戏开发处理的主要对象，地方的飞机、坦克是系统AI控制的精灵，代表玩家控制的我方飞机也是精灵。
甚至随机飞过的一片云、一只鸟都是精灵。
从技术上讲，精灵就是一个可以不断变化的图片。这些变化包括：
｜  位置移动
｜  旋转（以自身几何中心或以某个屏幕坐标为轴）
｜  放大缩小
｜  运动（按一定时间间隔连续显示一系列图像，形成运动效果）
所谓游戏，就是玩家操作一个或多个人工控制的精灵与一个或者若干个系统控制的敌方精灵进行互动：
紧身肉搏、远程射击、贴近对话等等。

1,加载图像,设为为背景。
	CCSprite *background = [CCSprite spriteWithFile:@"background.png"];
	background.anchorPoint = CGPointZero;//background.anchorPoint = ccp(0.0, 0.0);//设置参考点
	//默认情况下，anchorPoint的属性设置为(0.5,0.5);建议尽可能的采用默认值。//否则可能会引起很多麻烦，比如旋转和缩放。
	background.position = ccp(0,0);//设置位置
	//background.rotation = 90; //设置背景图片顺时针方向旋转90度。
	//background.opacity = 100;//设置图片的不透明度，为0，则完全透明
	background.scale = 0.8;//设置缩放比例
	background.opacity = 100;//设置不透明度
	[self addChild:background z:0 tag:1];