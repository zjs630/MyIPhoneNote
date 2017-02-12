1,场景类是一个抽象的概念，基本上可以看作是层Layer对象的一个容器。
//大多数情况下，场景对象本身不包含任何游戏相关的代码，而且很少被子类话，所以它一般都是在CCLayer对象里通过
//+(id)scene这个静态方法来创建的。

+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	//A CCScene object is always the first node in the scene graph.
	CCScene *scene = [CCScene node];
	//CCLayer* backgroundLayer = [HelloWorldBackground node];//可以添加多个层
//	[scene addChild: backgroundLayer];
	
	// 'layer' is an autorelease object.
	//通常CCScene的子节点都继承自CCLayer。
	HelloWorldLayer *layer = [HelloWorldLayer node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}
2，第一个创建场景的地方是在AppDelegate中applicationDidFinishLaunchiing方法结束处.
用以下方法创建第一个场景。
[[CCDirector sharedDirector] runWithScene:[HelloWorld scene]];
3,//刷新场景
[[CCDirector sharedDirector] replaceScene:[HelloWorld scene]];
//if you run this code in the HelloWorld scene, it will work fine.
//It will create a new instance of HelloWorld and replace the old one.//相当于刷新场景
//不要把self为参数传给replaceScene方法来刷新场景，那样会把程序卡死。

4，在场景切换时，cocos2d does a good job of cleaning up its own memory.
在过渡的过程中，the new scene is created,然后 the transition runs, and only
after the transition has done its job，旧的场景才会被清理出内存。







ddd




