1，单例的好处是它可以在任何时间任何地点被任何类所调用。它接近于全局类的 
作用,更像一个全局变量。如果你需要在任何地方都能用到某些数据或者方法,
单例是很好的选择。音频就是个很好的例子:因为任何一个类,不管是玩家, 
敌人,菜单按钮,或是过场动画,都可能需要播放声效或者改变背景音乐。
因 此,使用单例来播放音频是很好的选择。同样,如果存在全局的游戏状态,比 
如说玩家军队的大小和每支部队排的数目,你可以把这些信息存到一个单例中, 
把这些信息从一个关卡传到另一个关卡。

2,
Singleton模式主要用来提供全局共享对象，在Objective-C 中通过定义静态全局变量即可轻松实现这一模式。
列表3-2:MyManager类实现单例
//MyManager.h
@interface MyManager : NSObject {
}
+(id)instance;

@end
//MyManager.m
static MyManager *sharedManager = nil; 
+(id) instance {
    @synchronized(self){
        if (sharedManager == nil) {
            sharedManager = [[MyManager alloc] init]; 
        }
    }
    return sharedManager;
}

不过,单例也有不好的方面。因为单例很容易实现,而且可以在任何地方访问 
到,它们可能会被用在不该用的地方。

例如,你可能觉得你的游戏只有一个玩家对象,所以为什么就不能把玩家这个 
类变成单例呢?一切看起来都没有什么问题 – 直到你认识到不管什么时候这 
个玩家进入下一个关卡,这个玩家不仅带着上一关卡的得分,而且还有上一关 
卡的最后一帧动画信息,健康值,和所有已经捡到的物品,并且由于他在离开 
上一关卡的时候还在“狂暴”状态下,在新关卡开始的时候,他还处于之前的 
状态中。
为了解决这个问题,你可能会在类里加入一个重置某些变量的方法。看起来问 
题解决了。但是当你在游戏代码中添加越来越多的功能以后,在转换关卡时, 
你需要维护的变量也会越来越多。最糟糕的是,某天你的朋友建议你为iPad版 
本增加个双人模式。但是你发现你的玩家类是个单例,在任何时候你只能有一 
个玩家对象存在!这可麻烦了:要么你要重写很多代码,或者只能放弃很酷的 
双人模式了。
你越依赖于单例,类似的问题就会越多。在创建任何一个单例类之前,你都要 
考虑是否真的需要单例,是否需求会在不久的将来改变。

A singleton class returns the same instance no matter how many times an application requests it.
You obtain the global instance frome a singleton class through a factory method.else

Several Cocoa framework classes are singletons. They include NSFileManager, NSWorkspace, and, in UIKit, UIApplication and UIAccelerometer. The name of the factory method returning the singleton instance has, by convention, the form sharedClassType. Examples from the Cocoa frameworks are sharedFileManager, sharedColorPanel, and sharedWorkspace.

3，单例的最新写法

static MyClass *myInstance = nil;

+ (instancetype)sharedManager
{
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        myInstance = [[self alloc] init];
    });
    return myInstance;
}


