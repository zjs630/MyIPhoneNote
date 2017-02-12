


Objective-C里面的Key-Value Observing (KVO)机制，非常不错，可以很好的减少代码。关于KVO的学习，可以参考文章：《Key-Value Observing快速入门》：http://www.cocoadev.cn/Objective-C/Key-Value-Observing-Quick-Start-cn.asp
Key-Value Observing（KVO）实现


当观察者为一个对象的属性进行了注册，被观察对象的isa指针被修改的时候，isa指针就会指向一个中间类，而不是真实的类。所以isa指针其实不需要指向实例对象真实的类。所以我们的程序最好不要依赖于isa指针。在调用类的方法的时候，最好要明确对象实例的类名。

熟悉KVO的朋友都知道，只有当我们调用KVC去访问key值的时候KVO才会起作用。所以肯定确定的是，KVO是基于KVC实现的。其实看了上面我们的分析以后，关系KVO的架构的构思也就水到渠成了。

因为KVC的实现机制，可以很容易看到某个KVC操作的Key，而后也很容易的跟观察者注册表中的Key进行匹对。假如访问的Key是被观察的Key，那么我们在内部就可以很容易的到观察者注册表中去找到观察者对象，而后给他发送消息。

Key-value observing is a mechanism that enables an object to be notified directly when a property of another object changes.
KVO是一种机制，它能使一个对象的属性被改变时，直接通知另一个对象。

例如：People类监测File类文件的大小，
//1,创建两个类
File *file = [[File alloc] init];
//File类添加size属性 @property (nonatomic,assign) NSInteger size;
People *p = [[People alloc] init];


//2,注册观察者
[file addObserver:p forKeyPath:@"size" options:NSKeyValueObservingOptionNew context:nil];

//options参数可以设置传递旧值或新值。或者用“|”分割，同时传递新值和旧值。

//3,People类实现观察者
-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context{
    NSLog(@"%@",change);
}

