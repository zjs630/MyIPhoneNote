1,在CCLayer子类中添加一个Label
a, 创建并初始化一个Label
CCLabel* label = [CCLabel labelWithString:@"Hello World" fontName:@"Marker Felt" fontSize:64];
b,获得窗口的大小
CGSize size = [[CCDirector sharedDirector] winSize];
c，设置Label的位置在屏幕的中间
label.position = ccp(size.with/2,size.height/2);
d,将Label添加到层中
[self addChild:label];

//好像不能用了。
CCLabel在经常改变文字时会让游戏变慢。