1,- (IBAction)start:(id)sender
{
    pageStillLoading = YES;
    [NSThread detachNewThreadSelector:@selector(loadPageInBackground:)toTarget:self withObject:nil];
    [progress setHidden:NO];
    while (pageStillLoading) {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
    }
    [progress setHidden:YES];
}

这段代码很神奇的，因为他会“暂停”代码运行，而且程序运行不会因为这里有一个while循环而受到影响。在[progress setHidden:NO]执行之后，整个函数想暂停了一样停在循环里面，等loadPageInBackground里面的操作都完成了以后才让[progress setHidden:YES]运行。这样做就显得简介，而且逻辑很清晰。如果你不这样做，你就需要在loadPageInBackground里面表示load完成的地方调用[progress setHidden:YES]，显得代码不紧凑而且容易出错。
那么具体什么是NSRunLoop呢？其实NSRunLoop的本质是一个消息机制的处理模式。如果你对vc++编程有一定了解，在windows中，有一系列很重要的函数SendMessage，PostMessage，GetMessage，这些都是有关消息传递处理的API。但是在你进入到Cocoa的编程世界里面，我不知道你是不是走的太快太匆忙而忽视了这个很重要的问题，Cocoa里面就没有提及到任何关于消息处理的API，开发者从来也没有自己去关心过消息的传递过程，好像一切都是那么自然，像大自然一样自然？在Cocoa里面你再也不用去自己定义WM_COMMAD_XXX这样的宏来标识某个消息，也不用在switch-case里面去对特定的消息做特别的处理。难道是Cocoa里面就没有了消息机制？答案是否定的，只是Apple在设计消息处理的时候采用了一个更加高明的模式，那就是RunLoop。
2,事件和画图周期，处理过程是：操作系统检测到触摸事件后，把该事件放到应用的事件队列，应用首先处理事件队列里最顶部的事件，传递到响应的对象进行处理，然后相应地改变用户界面。
3,运行循环可以有多个输入源，包括Event source,port,timer.
每个线程有它自己的运行循环，可以使用NSRunLoop类管理运行循环。

每一个线程自己的运行循环会永不停息地检测是否有端口（port source）事件，
自定义循环运行事件（custom source）以及定时器事件（timer source）。一旦有事件发生，便会处理，处理完检测下一个事件。

一个NSRunLoop可以用来管理来自窗口系统的触摸和键盘事件，NSPorts,NSTimer,和NSConnection。

一般来说，用户不需要手动创建或者管理NSRunLoop对象，每一个线程包括主线程都会自动地创建一个运行循环。
//每一个线程默认都有一个NSRunloop，主线程是默认开启的，其他线程要手动开启。
4,4个运行循环模式：
NSDefaultRunLoopMode,用于处理除了NSConnection对象的输入源，最常用的。//NSRunLoop.h
NSConnectionReplyMode,用来标识NSConnection对象正在等待回复。//NSConnecton.h
NSModalPanelRunLoopMode,用来处理模态面板的输入源。
NSEventTrackingRunLoopMode,用来处理事件追踪循环。
5,何时使用RunLoop？

//1.使用ports或自定义输入源 与其他线程通讯
//2.在线程中使用定时器
//3.在程序中使用performSelector等方法
//4.让线程周期性执行某个任务

6,常用方法
访问当前运行循环
 +currentRunLoop
-currentMode
-limitDateForMode
-getCFRunLoop

管理计时器
-addTimer:forMode

管理端口：
-addPort:forMode
-removePort:forMode

运行一个循环：
- (void)run; 
- (void)runUntilDate:(NSDate *)limitDate;
- (BOOL)runMode:(NSString *)mode beforeDate:(NSDate *)limitDate;

发送消息
- (void)performSelector:(SEL)aSelector target:(id)target argument:(id)arg order:(NSUInteger)order modes:(NSArray *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(id)arg;
- (void)cancelPerformSelectorsWithTarget:(id)target;


- (void)runUntilDate:(NSDate *)limitDate; //同run方法，增加超时参数limitDate，避免进入无限循环。使用在UI线程（亦即主线程）上，可以达到暂停的效果。在主线程上用，界面会卡死。

- (BOOL)runMode:(NSString *)mode beforeDate:(NSDate *)limitDate; //等待消息处理，好比在PC终端窗口上等待键盘输入。一旦有合适事件（mode相当于定义了事件的类型）被处理了，则立刻返回；类同run方法，如果没有事件处理也立刻返回；有否事件处理由返回布尔值判断。同样limitDate为超时参数。

- (void)acceptInputForMode:(NSString *)mode beforeDate:(NSDate *)limitDate; //似乎和runMode:差不多（测试过是这种结果，但确定是否有其它特殊情况下的不同），没有BOOL返回值。

官网文档也提到run和runUntilDate:会以NSDefaultRunLoopMode参数调用runMode:来处理事件。

当app运行后，iOS系统已经帮助主线程启动一个run loop，而一般线程则需要手动来启动run loop。

使用run loop的一个好处就是避免线程轮询的开销，run loop在无事件处理时可以自动进入睡眠状态，降低CPU的能耗。



[[NSRunLoop mainRunLoop] run]; //主线程永远等待，但让出主线程时间片

[[NSRunLoop mainRunLoop] runUntilDate:[NSDate distantFuture]]; //等同上面调用

[[NSRunLoop mainRunLoop] runUntilDate:[NSDate date]]; //立即返回

[[NSRunLoop mainRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:10.0]]; //主线程等待，但让出主线程时间片，然后过10秒后返回

[[NSRunLoop mainRunLoop] runMode:NSDefaultRunLoopMode beforeDate: [NSDate distantFuture]]; //主线程等待，但让出主线程时间片；有事件到达就返回，比如点击UI等。

[[NSRunLoop mainRunLoop] runMode:NSDefaultRunLoopMode beforeDate: [NSDate date]]; //立即返回

[[NSRunLoop mainRunLoop] runMode:NSDefaultRunLoopMode beforeDate: [NSDate dateWithTimeIntervalSinceNow:10.0]]; //主线程等待，但让出主线程时间片；有事件到达就返回，如果没有则过10秒返回。




7，
实际上，Run loop并不是一项并发机制(例如GCD或操作队列)，因为它并不能并行执行任务。不过在主dispatch/operation队列中，run loop直接配合着任务的执行，它提供了让代码异步执行的一种机制。

Run loop比起操作队列或者GCD来说，更加容易使用，因为通过run loop，开发者不必处理并发中的复杂情况，就能异步的执行任务。

一个run loop总是绑定到某个特定的线程中。main run loop是与主线程相关的，在每一个Cocoa和CocoaTouch程序中，这个main run loop起到核心作用——它负责处理UI时间、计时器，以及其它内核相关事件。无论什么时候使用计时器、NSURLConnection或者调用performSelector:withObject:afterDelay:，run loop都将在后台发挥重要作用——异步任务的执行。

无论什么时候，依赖于run loop使用一个方法，都需要记住一点：run loop可以运行在不同的模式中，每种模式都定义了一组事件，供run loop做出响应——这其实是非常聪明的一种做法：在main run loop中临时处理某些任务。

在iOS中非常典型的一个示例就是滚动，在进行滚动时，run loop并不是运行在默认模式中的，因此，run loop此时并不会做出别的响应，例如，滚动之前在调度一个计时器。一旦滚动停止了，run loop会回到默认模式，并执行添加到队列中的相关事件。如果在滚动时，希望计时器能被触发，需要将其在NSRunLoopCommonModes模式下添加到run loop中。

其实，默认情况下，主线程中总是有一个run loop在运行着，而其它的线程默认情况下，不会有run loop。开发者可以自行为其它的线程添加run loop，只不过很少需要这样做。大多数时候，使用main run loop更加方便。如果有大量的任务不希望在主线程中执行，你可以将其派发到别的队列中。相关内容，Chris写了一篇文章，可以去看看：common background practices。

如果你真需要在别的线程中添加一个run loop，那么不要忘记在run loop中至少添加一个input source。如果run loop中没有input source，那么每次运行这个run loop，都会立即退出。


8
Run Loop和线程的关系：
1. 主线程的run loop默认是启动的，用于接收各种输入sources
2. 对第二线程来说，run loop默认是没有启动的，如果你需要更多的线程交互则可以手动配置和启动，如果线程执行一个长时间已确定的任务则不需要。

Run Loop什么情况下使用：
a. 使用ports 或 input sources 和其他线程通信   // 不了解
b. 在线程中使用timers // 如果不启动run loop，timer的事件是不会响应的
c. 在Cocoa 应用中使用performSelector...方法   // 应该是performSelector...这种方法会启动一个线程并启动run loop吧
d. 让线程执行一个周期性的任务    // 如果不启动run loop， 线程跑完就可能被系统释放了


1.NSRunLoop是IOS消息机制的处理模式
NSRunLoop的主要作用：控制NSRunLoop里面线程的执行和休眠，在有事情做的时候使当前NSRunLoop控制的线程工作，没有事情做让当前NSRunLoop的控制的线程休眠。
2.NSRunLoop 就是一直在循环检测，从线程start到线程end，检测input source(如点击，双击等操作)同步事件，检测time source同步事件，检测到输入源会执行处理函数，首先会产生通知，corefunction向线程添加runloop observers来监听事件，意在监听事件发生时来做处理。

3，runLoop 用于监控线程的一个或多个event sources。当events arrive，系统唤醒这个thread并且dispatches the events to the run loop,然后将这些事件交给你指定的对象处理。//如果没有事件present和将要处理的事件，the run loop 就让这个线程休眠。
    没有必要在你创建的每一个线程中都使用一个run loop。
在主线程中run loop是自动开启的，如果你想创建第二个long-lived线程，你必须自己配置这个线程的run loop。

