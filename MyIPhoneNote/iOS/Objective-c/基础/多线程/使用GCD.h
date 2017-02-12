http://blog.devtang.com/blog/2012/02/22/use-gcd/
http://blog.csdn.net/dztianyu/article/details/19487199

iOS提供了两种任务调度机制，来处理并发性concurrency问题，Operation queues和Grand Central Dispatch。


1,什么是GCD
Grand Central Dispatch (GCD)是Apple开发的一个多核编程的解决方法。该方法在Mac OS X 10.6雪豹中首次推出，
并随后被引入到了iOS4.0中。GCD是一个替代诸如NSThread, NSOperationQueue, NSInvocationOperation等技术
的很高效和强大的技术，它看起来象就其它语言的闭包(Closure)一样，但苹果把它叫做blocks。
//设计用来发挥多核处理器的能力。

2
系统提供的dispatch方法

为了方便地使用GCD，苹果提供了一些方法方便我们将block放在主线程 或 后台线程执行，或者延后执行。使用的例子如下：
//  后台执行：
dispatch_async(dispatch_get_global_queue(0, 0), ^{
    // something
    //第一个参数 可以设置优先级，共四个。
});
// 主线程执行：
dispatch_async(dispatch_get_main_queue(), ^{
    // something
});

// 一次性执行：
static dispatch_once_t onceToken;
dispatch_once(&onceToken, ^{
    // code to be executed once
    //该代码在多线程中执行，可以保证百分百安全。常用在单例中。
    //之前的单例代码，在大多数情况下也是安全的。但在多核cpu中，在更在更新表示是否初始化成功的标志变量是读取，就有可能多次执行初始化处理。
});
// 延迟2秒执行：
double delayInSeconds = 2.0;
dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
    // code to be executed on the main queue after delay
    //此代码并不一定是2秒后执行处理，而是2秒后用dispatch_async函数追加Block到主线程队列。//
});

//dispatch_queue_t 也可以自己定义，
//如要要自定义queue，可以用dispatch_queue_create方法，示例如下：
dispatch_queue_t urls_queue = dispatch_queue_create("blog.devtang.com", NULL);
dispatch_async(urls_queue, ^{
    // your code
});
dispatch_release(urls_queue);

//另外，GCD还有一些高级用法，例如让后台2个线程并行执行，然后等2个线程都结束后，再汇总执行结果。
//这个可以用dispatch_group, dispatch_group_async 和 dispatch_group_notify来实现，示例如下：

dispatch_group_t group = dispatch_group_create();
dispatch_group_async(group, dispatch_get_global_queue(0,0), ^{
    // 并行执行的线程一
});
dispatch_group_async(group, dispatch_get_global_queue(0,0), ^{
    // 并行执行的线程二
});
dispatch_group_notify(group, dispatch_get_global_queue(0,0), ^{
    // 汇总结果
});


后台运行

GCD的另一个用处是可以让程序在后台较长久的运行。在没有使用GCD时，当app被按home键退出后，app仅有最多5秒钟的时候做一些保存或清理资源的工作。但是在使用GCD后，app最多有10分钟的时间在后台长久运行。这个时间可以用来做清理本地缓存，发送统计数据等工作。

总结

总体来说，GCD能够极大地方便开发者进行多线程编程。如果你的app不需要支持iOS4.0以下的系统，那么就应该尽量使用GCD来处理后台线程和UI线程的交互。