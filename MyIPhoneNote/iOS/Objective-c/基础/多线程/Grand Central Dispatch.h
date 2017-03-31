
http://blog.devtang.com/blog/2012/02/22/use-gcd/
http://blog.csdn.net/dztianyu/article/details/19487199

iOS提供了两种任务调度机制，来处理并发性concurrency问题，Operation queues和Grand Central Dispatch。

1.系统提供的dispatch方法

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
Serial and Concurrent //串行和并行
#if 0
//Serial dispatch queue //先进先出队列。需要一个block执行完之后才能执行另一个。使用一个线程。
dispatch_queue_t queue = dispatch_queue_create("testQueue", DISPATCH_QUEUE_SERIAL);
dispatch_async(queue, ^{
    // your code
});
//等价于 dispatch_queue_t queue = dispatch_queue_create("testQueue", NULL);
//注：第一个参数是队列的名称，不建议用NULL，因为调试中，这个名称会出现在崩溃日志中。
#else
//Concurrent dispatch queue //并发执行，没有先后顺序。使用多个线程。
dispatch_queue_t queue = dispatch_queue_create("testQueue", DISPATCH_QUEUE_CONCURRENT);
#endif
dispatch_async(queue, testBlock1);
dispatch_async(queue, testBlock2);
dispatch_async(queue, testBlock3);
dispatch_release(queue);
//注：通过dispatch_queue_create创建的线程队列一定要用dispatch_release函数释放(ARC中也是这样)。//一本书上写的
//尼玛，在ARC中用dispatch_release竟然报错了。

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

GCD的另一个用处是可以让程序在后台较长久的运行。在没有使用GCD时，当app被按home键退出后，app仅有最多5秒钟的时候做一些保存或清理资源的工作。
但是在使用GCD后，app最多有10分钟的时间在后台长久运行。这个时间可以用来做清理本地缓存，发送统计数据等工作。
