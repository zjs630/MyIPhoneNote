http://www.cnblogs.com/zhulin/archive/2011/07/11/2102793.html
1,iPhone 中的线程应用并不是无节制的，官方给出的资料显示iPhone OS下的主线程的堆栈大小是1M，第二个线程开始都是512KB。
并且该值不能通过编译器开关或线程API函数来更改。
    只有主线程有直接修改UI的能力。
2，Multithreading
//Executing a block on another queue
dispatch_queue_t queue = ...;
dispatch_async(queue,^{});
//Getting the main queue
dispatch_queue_t mainQ = dispatch_get_main_queue();
NSOperationQueue *mainQ = [NSOperationQueue mainQueue];//for object-oriented APIs
//Creating a queue (not the main queue)
dispatch_queue_t otherQ = dispatch_queue_create("name",NULL);
3,调用一个方法on the main queue
//NSObject method ..
- (void) performSelectorOnMainThread:(self)aMethod withObject:(id)object waitUntilDone:(BOOL)vaitUntilDone;
//or
dispatch_async(dispatch_get_main_queue(),^{
    /*call a method*/
});