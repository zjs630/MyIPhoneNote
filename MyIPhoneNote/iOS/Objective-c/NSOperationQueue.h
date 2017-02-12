NSOperationQueue

Operations are typically scheduled by adding to a queue.
Choose a maximum number of concurrent Operations.//选择一个最大的并发操作数。同时发生的。
Queue runs Operations based on priority and dependencies. 队列操作取决于优先级和依赖性。

getDataQueue = [[NSOperationQueue alloc] init];
[getDataQueue setMaxConcurrentOperationCount:3];


-(void)someAction:(id)sender{
    NSInvocationOperation *operation = [[NSInvocationOperation alloc] initWithTarget:self selector:@selector(doWork) object:nil];
    [getDataQueue addObject:operation];
    [operation release];
}

-(void)doWork{
    
}

//============================================================================================================================
NSOperation 有两个子类：NSInvocationOperation和NSBlockOperation,可以让你不用自己创建NSOperation子类而实现程序的并发运行。
NSInvocationOperation允许你指定一个对象和Selector，作为操作的基础。
NSBlockOperation运行执行一个或者多个代码段来作为操作的基础。
在复杂的情况下，你可能还需要继承NSOperation类，因为这样可以更好的对过程进行掌控。

//============================================================================================================================

NSoperation也是多线程的一种，NSopertaion有2种形式
(1) 并发执行
并发执行你需要重载如下4个方法
//执行任务主函数，线程运行的入口函数
- (void)start 
//是否允许并发，返回YES，允许并发，返回NO不允许。默认返回NO
-(BOOL)isConcurrent 
- (BOOL)isExecuting
//是否已经完成，这个必须要重载，不然放在放在NSOperationQueue里的NSOpertaion不能正常释放。
- (BOOL)isFinished

比如TestNSOperation:NSoperaion 重载上述的4个方法，
声明一个NSOperationQueue, NSOperationQueue *queue = [[[NSOperationQueue alloc ] init] autorelease];
[queue addOperation:testNSoperation];
它会自动调用TestNSOperation里的 start函数，如果需要多个NSOperation,你需要设置queue的一些属性，如果多个NSOperation之间又依赖关系，也可以设置，具体可以参考API 文档。 



(2)非并发执行
-(void)main
只需要重载这个main方法就可以了。  