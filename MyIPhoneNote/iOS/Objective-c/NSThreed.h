1.Threading 
a. Create the new thread:
!   [NSThread detachNewThreadSelector:@selector(myMethod) toTarget:self withObject:nil];

!!  [myObj performSelectorInBackground:@selector(myMethod) withObject:nil];

!!! NSThread *myThread = [[NSThread alloc] initWithTarget:self selector:@selector(myMethod) object:nil];
	[myThread start];

b,Create the method that is called by the new thread:
- (void)myMethod
{
NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
//*** code that should be run in the new thread goes here ***
[pool release];
}

2，//What if you need to do something to the main thread from inside your new thread (for example, show a loading symbol)? 
//在线程里运行主线程里的方法 Use performSelectorOnMainThread.

[self performSelectorOnMainThread:@selector(myMethod) withObject:nil waitUntilDone:false];

UIApplication* app = [UIApplication sharedApplication];
[app performSelectorOnMainThread:@selector(moveToMain) withObject:nil waitUntilDone:FALSE];

3，线程延时1秒
	[NSThread sleepForTimeInterval:1.0];
或者 [NSThread sleepUntilDate:[NSDate dateWithTimeIntervalSinceNow:2.5]];
4. 多线程NSThread用法 ：
//a,不带参数
[NSThread detachNewThreadSelector:@selector(scheduleTask) toTarget:self withObject:nil];
//在使用“引用计数”的内存管理时，一个线程至少得拥有一个autorelease pool对象。在grabage collection可以不必使用。
-(void) scheduleTask {
    //create a pool 
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	//code...
    [pool release];    //release the pool;
}

//b 有参数
[NSThread detachNewThreadSelector:@selector(scheduleTask:) toTarget:self withObject:[NSDate date]];
//注意selector里有冒号。

-(void) scheduleTask:(NSDate *) mdate {

}

5，bug
婚姻树IOS5下崩溃的bug，已经解决。崩溃原因是在新建线程中读取了视图部分的内容（UITextView的text）。

注：只在IOS5 真机中会出现崩溃，模拟器中正常。

//官方文档
//https://developer.apple.com/library/ios/documentation/Cocoa/Conceptual/Multithreading/AboutThreads/AboutThreads.html#//apple_ref/doc/uid/10000057i-CH6-SW2
