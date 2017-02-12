1，在cocos2d中集成了2个physics engines.一个是Chipmunk，另一个是Box2d.
两个引擎的最大区别是:chipmunk is written in c,Box2d is written in C++.
大多数开发者选择Box2d。
2，cocos2d允许你给任意的game object添加your own OpenGL ES code 在任何时候。
3,在cocos2d初始化进程中，常要改的3个事情。
CCDirector *director = [CCDirector sharedDirector];
[director setDeviceOrientation:kCCDeviceOrientationLandscapeLeft];
[director setAnimationInterval:1.0/60];
//动画间隔决定了更新屏幕的频率。在某些时候设置低一点的真频率会更合适，游戏可以稳定保持在这个频率，用户体验会更好些。
//IOS设备不支持超过60帧每秒的频率。如果你想让cocos2d运行在最快的频率下，包动画间隔设置为1.0/60

[director setDisplayFPS:YES];
4, a list of supported device orientations
CCDeviceOrientationPortrait 
CCDeviceOrientationPortraitUpsideDown 
CCDeviceOrientationLandscapeLeft 
CCDeviceOrientationLandscapeRight
