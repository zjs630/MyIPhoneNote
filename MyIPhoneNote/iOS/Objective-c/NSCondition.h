
二、线程的同步与锁
要说明线程的同步与锁，最好的例子可能就是多个窗口同时售票的售票系统了。我们知道在java中，使用synchronized来同步，而iphone虽然没有提供类似java下的synchronized关键字，但提供了NSCondition对象接口。查看NSCondition的接口说明可以看出，NSCondition是iphone下的锁对象，所以我们可以使用NSCondition实现iphone中的线程安全。这是来源于网上的一个例子：
SellTicketsAppDelegate.h 文件
//  SellTicketsAppDelegate.h
import <UIKit/UIKit.h>

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
SellTicketsAppDelegate.m 文件
//  SellTicketsAppDelegate.m
import "SellTicketsAppDelegate.h"

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
        if(tickets > 0){
            [NSThread sleepForTimeInterval:0.5];
            count = 100 - tickets;
            NSLog(@"当前票数是:%d,售出:%d,线程名:%@",tickets,count,[[NSThread currentThread] name]);
            tickets--;
        }else{
            break;
        }
        [ticketsCondition unlock];
    }
}

- (void)dealloc {
	[ticketsThreadone release];
    [ticketsThreadtwo release];
    [ticketsCondition release]; 
    [window release];
    [super dealloc];
}
@end