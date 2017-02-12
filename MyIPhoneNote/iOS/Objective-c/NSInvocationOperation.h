多线程之NSInvocationOperation
多线程编程是防止主线程堵塞，增加运行效率等等的最佳方法。而原始的多线程方法存在很多的毛病，包括线程锁死等。在Cocoa中，Apple提供了NSOperation这个类，提供了一个优秀的多线程编程方法。
本次介绍NSOperation的子集，简易方法的NSInvocationOperation：
@implementation MyCustomClass
- (void)launchTaskWithData:(id)data
{
    //创建一个NSInvocationOperation对象，并初始化到方法
    //在这里，selector参数后的值是你想在另外一个线程中运行的方法（函数，Method）
    //在这里，object后的值是想传递给前面方法的数据
    NSInvocationOperation* theOp = [[NSInvocationOperation alloc] initWithTarget:self
																		selector:@selector(myTaskMethod:) object:data];
	
    // 下面将我们建立的操作“Operation”加入到本地程序的共享队列中（加入后方法就会立刻被执行）
    // 更多的时候是由我们自己建立“操作”队列
    [[MyAppDelegate sharedOperationQueue] addOperation:theOp];
}

// 这个是真正运行在另外一个线程的“方法”
- (void)myTaskMethod:(id)data
{
    // Perform the task.
}

@end
一个NSOperationQueue 操作队列，就相当于一个线程管理器，而非一个线程。因为你可以设置这个线程管理器内可以并行运行的的线程数量等等。下面是建立并初始化一个操作队列：

@interface MyViewController : UIViewController {
	
    NSOperationQueue *operationQueue;
    //在头文件中声明该队列
}
@end

@implementation MyViewController

- (id)init 
{
    self = [super init];
    if (self) {
        operationQueue = [[NSOperationQueue alloc] init]; //初始化操作队列
        [operationQueue setMaxConcurrentOperationCount:1];
        //在这里限定了该队列只同时运行一个线程
        //这个队列已经可以使用了
    }
    return self;
}

- (void)dealloc
{
    [operationQueue release];
    [super dealloc];
}

@end简单介绍之后，其实可以发现这种方法是非常简单的。很多的时候我们使用多线程仅仅是为了防止主线程堵塞，而NSInvocationOperation就是最简单的多线程编程，在iPhone编程中是经常被用到的。



///////////////////////////////////////////////////////////////////////////////////////////////////
 在主线程里加入一个loading画面……
{
	[window addSubview:view_loading];
	[NSThread detachNewThreadSelector:@selector(init_backup:) toTarget:self withObject:nil];
}
可以通过performSelectorOhMainThread更新UI元素，比如设置进度条等等。最后消除loading画面，载入主View。
- (void)init_backup:(id)sender
{
	 NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	 // ...
	int i = status;
	[self performSelectorOnMainThread:@selector(show_loading:) withObject:[NSNumber numberWithInt:i] waitUntil Done:NO];
	
	[view_loading removeFromSuperview];
	[window addSubview:tabcontroller_main.view];
	[pool release];
}

///////////////////////////////////////////////////////

利用iphone的多线程实现和线程同步

从接口的定义中可以知道，NSThread和大多数iphone的接口对象一样，有两种方式可以初始化：

一种使用initWithTarget :(id)target selector:(SEL)selector object:(id)argument，但需要负责在对象的retain count为0时调用对象的release方法清理对象。

另一种则使用所谓的convenient method,这个方便接口就是detachNewThreadSelector，这个方法可以直接生成一个线程并启动它，而且无需为线程的清理负责。

#import <UIKit/UIKit.h>
@interface SellTicketsAppDelegate : NSObject <UIApplicationDelegate> {
    int tickets;
    int count;
    NSThread* ticketsThreadone;
    NSThread* ticketsThreadtwo;
    NSCondition* ticketsCondition;
    UIWindow *window;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@end

然后在实现中添加如下代码：
//  SellTicketsAppDelegate.m
//  SellTickets
//
//  Created by sun dfsun2009 on 09-11-10.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//
#import "SellTicketsAppDelegate.h"
@implementation SellTicketsAppDelegate
@synthesize window;
- (void)applicationDidFinishLaunching:(UIApplication *)application {
    tickets = 100;
    count = 0;
    // 锁对象
    ticketCondition = [[NSCondition alloc] init];
    ticketsThreadone = [[NSThread alloc] initWithTarget:self selector:@selector(run) object:nil];
    [ticketsThreadone setName:@"Thread-1"];
    [ticketsThreadone start];
    ticketsThreadtwo = [[NSThread alloc] initWithTarget:self selector:@selector(run) object:nil];
    [ticketsThreadtwo setName:@"Thread-2"];
    [ticketsThreadtwo start];
    //[NSThread detachNewThreadSelector:@selector(run) toTarget:self withObject:nil];
    // Override point for customization after application launch
    [window makeKeyAndVisible];
}
- (void)run{
    while (TRUE) {
        // 上锁
        [ticketsCondition lock];
        if(tickets > 0)
        {
            [NSThread sleepForTimeInterval:0.5];
            count = 100 - tickets;
            NSLog(@"当前票数是:%d,售出:%d,线程名:%@",tickets,count,[[NSThread currentThread] name]);
            tickets--;
        }else
        {
            break;
        }
        [ticketsCondition unlock];
    }
}
-         (void)dealloc {
    [ticketsThreadone release];
    [ticketsThreadtwo release];
    [ticketsCondition release];
    [window release];
    [super dealloc];
}
@end

-------------------------------------------------------------------------------------
// 定义
#import <UIKit/UIKit.h>

@interface ThreadSyncSampleViewController : UIViewController {
	int _threadCount;
	NSCondition *_myCondition;
}

@end

//实现文件如下:

#import "ThreadSyncSampleViewController.h"

@implementation ThreadSyncSampleViewController

/*
 // The designated initializer. Override to perform setup that is required before the view is loaded.
 - (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
 if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
 // Custom initialization
 }
 return self;
 }
 */

/*
 // Implement loadView to create a view hierarchy programmatically, without using a nib.
 - (void)loadView {
 }
 */

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	//
	//_myCondition = nil;
	//
	_myCondition = [[NSCondition alloc] init];
	//
	NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:30 
													  target:self
													selector:@selector(threadTester)
													userInfo:nil
													 repeats:YES];
	[timer fire];
	
}


- (void)threadTester{
	[_myCondition lock];
	
	_threadCount = -2;
	//如果有n个要等待的thread，这里置成 -n
	[_myCondition unlock];
	//
	NSLog(@"");
	NSLog(@"------------------------------------------------------------------------------");
	[NSThread detachNewThreadSelector:@selector(threadOne) toTarget:self withObject:nil];
	[NSThread detachNewThreadSelector:@selector(threadTwo) toTarget:self withObject:nil];
	[NSThread detachNewThreadSelector:@selector(threadThree) toTarget:self withObject:nil];
	return;
}

- (void)threadOne{
	NSLog(@"@@@ In thread 111111 start.");
	[_myCondition lock];
	
	int n = rand()%5 + 1;
	NSLog(@"@@@ Thread 111111 Will sleep %d seconds ,now _threadCount is : %d",n,_threadCount);
	sleep(n);
	//[NSThread sleepForTimeInterval:n];
	_threadCount ++ ;
	NSLog(@"@@@ Thread 111111 has sleep %d seconds ,now _threadCount is : %d",n,_threadCount);
	[_myCondition signal];
	NSLog(@"@@@ Thread 1111111 has signaled ,now _threadCount is : %d",_threadCount);
	[_myCondition unlock];
	NSLog(@"@@@ In thread one complete.");
	[NSThread exit];
	return;
}

- (void)threadTwo{
	NSLog(@"### In thread 2222222 start.");
	[_myCondition lock];
	
	int n = rand()%5 + 1;
	NSLog(@"### Thread 2222222 Will sleep %d seconds ,now _threadCount is : %d",n,_threadCount);
	sleep(n);
	//   [NSThread sleepForTimeInterval:n];
	_threadCount ++ ;
	NSLog(@"### Thread 2222222 has sleep %d seconds ,now _threadCount is : %d",n,_threadCount);
	[_myCondition signal];
	NSLog(@"### Thread 2222222 has signaled ,now _threadCount is : %d",_threadCount);
	[_myCondition unlock];
	//_threadCount ++ ;
	NSLog(@"### In thread 2222222 complete.");
	[NSThread exit];
	return;
}

- (void)threadThree{
	NSLog(@"<<< In thread 333333 start.");
	[_myCondition lock];
	while (_threadCount < 0) {
		[_myCondition wait];
	}
	NSLog(@"<<< In thread 333333 ,_threadCount now is %d ,will start work.",_threadCount);
	[_myCondition unlock];
	NSLog(@"<<< In thread 333333 complete.");
	[NSThread exit];
	return;
}

/*
 // Override to allow orientations other than the default portrait orientation.
 - (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
 // Return YES for supported orientations
 return (interfaceOrientation == UIInterfaceOrientationPortrait);
 }
 */

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}


- (void)dealloc {
	[_myCondition release];
    [super dealloc];
}

@end