1，多线程容易发生的问题
如：多个线程更新相同的资源会导致数据的不一致（数据竞争）；
线程死锁；
太多线程导致消耗大量内存，引起大量上下文切换，大幅度降低系统的响应性能。
2，多线程的优点
如：避免主线程堵塞；
3,Serial and Concurrent //串行和并行
#if 0
//Serial dispatch queue //先进先出队列。需要一个block执行完之后才能执行。使用一个线程。
dispatch_queue_t queue = dispatch_queue_create("testQueue", DISPATCH_QUEUE_SERIAL);
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
注：通过dispatch_queue_create创建的线程队列一定要用dispatch_release函数释放(ARC中也是这样)。
尼玛，在ARC中用dispatch_release竟然报错了。

4，解决多线程的数据竞争问题，使用Serial dispatch queue，让多个操作顺序串行执行。

5，创建CGD有两种方法，第一种是dispatch_queue_create。第二种是用系统提供的Dispatch queue,main dispatch queue（顺序执行）和 global dispatch queue（并行执行）。
6,改变已经生成的dispatch queue执行顺序,用dispatch_set_target_queue(queue2,queue1)这个函数。
7，dispatch_barrier_async //可在并行队列中顺序执行某个操作
在访问数据库或者文件时，用Serial Dispatch queue(顺序执行)可避免数据竞争问题。
写数据不可与其它的写或者读进行并发操作。如果仅仅是多个线程同时读取一个文件的并行执行，不会有任何问题。
为了高效率的访问，读操作追加到Concurrent Dispatch queue中，写操作追加到Serial Dispatch queue中。

dispatch_queue_t queue = dispatch_queue_create("testQueue", DISPATCH_QUEUE_CONCURRENT);
dispatch_async(queue, readBlock1);
dispatch_async(queue, readBlock2);
dispatch_barrier_async(queue, ^{
    //此处的写操作会在，readBlock1和readBlock2执行完后，才执行。
    NSLog(@"write");
});

8，多线程需要注意的问题，
如果多个线程同时访问和修改同一个资源，就会出现问题。
有一个缓和的方法是取消共享一个资源，保证每一个线程都只操作它自己的资源。当这种完全资源分开的方法不是你的选择的话，考虑下面方法。

a 使用Locks和conditions，能够在某一时间只能有一个线程运行上锁的代码。
b atomic operations are another way to protect and synchronize access to data.