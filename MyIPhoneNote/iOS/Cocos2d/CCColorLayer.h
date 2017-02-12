// 将背景色设为紫红色。 
CCColorLayer* colorLayer = [CCColorLayer layerWithColor:ccc4(255, 0, 255, 255)]; 
[self addChild:colorLayer z:0];
如果你熟悉OpenGL的话,你可能会觉得没有必要为了改变背景颜色而添加一个 
单独的层。你可以使用以下OpenGL代码得到相同的效果:
glClearColor(1, 0, 1, 1);


But please test this with your game’s scene transitions first, 
since changing the glClearColor can have an adverse effect 
on scene transitions. For example, when using CCFadeTransition,
the clear color will shine through regardless of the color you 
use to initialize CCFadeTransition.

但是如果你在场景中使用了过渡效果的话,你最好先在游戏里测试一下上述 
OpenGL代码,因为glClearColor对场景过渡效果会产生不好的影响。比如,当 
你使用CCFadeTransition时,不管你用了什么颜色初始化CCFadeTransition, 
glClearColor中使用的颜色都会透过层影响到过渡效果中使用的颜色。