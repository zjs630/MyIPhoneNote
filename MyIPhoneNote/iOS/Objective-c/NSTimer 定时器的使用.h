//http://justsee.iteye.com/blog/1774722 一定要看
//http://book.51cto.com/art/201304/390745.htm

1，什么是NSTimer
　官方给出解释是“A timer provides a way to perform a delayed action or a periodic action. The timer waits until a certain time interval has elapsed and then fires, sending a specified message to a specified object. ” 翻译过来就是timer就是一个能在从现在开始的后面的某一个时刻或者周期性的执行我们指定的方法的对象。

周期性事件和计时器（1）

建立游戏时，您经常会发现每隔一定的时间间隔需要运行一些代码。例如，在动作游戏中，每隔33毫秒左右需要运行代码更新显示，以使得游戏每秒显示30帧。实现这个功能的方法之一是使用计时器。

使用计时器可以每隔一个指定的时间间隔，反复调用对象的一个方法。您可以指定计时器在未来的某个时间调用一次方法，或者按照固定的时间间隔重复。在Scrambler游戏中，您将设置一个计时器每秒钟递减游戏计时器。

在运行循环中计时器不是实时工作的，计时器负责调用时钟，而当触发条件满足时，计时器才会被触发。计时器的工作误差在50~100毫秒之间。因此，对于实时性要求非常高的应用程序，在实现上不应采用计时器的方式。

如果运行循环忙于其他长时间运行的活动，计时器的调用则有可能会被错过。如果重复计时器的触发时间被延迟到与下一个计时器事件同时发生时，计时器指定的方法仅会被运行一次。因此，假定游戏中的计时器应该是每隔一秒被触发一次，但由于某种原因，5秒钟过去了计时器都没有被调用，再被调用时计时器方法也只是运行一次。

如果只是想延迟发送消息一次，可使用performSelector:withObject:afterDelay:方法，而不是使用计时器。

使用计时器的步骤是：创建一个实例，配置其调用特定对象的特定消息，将计时器与运行循环进行关联。使用完计时器后，需要将其设置为无效，使其停止发送计时消息。

使用selector(选择器)指定计时器运行的方法。选择器是一个方法的名称。配置计时器时，如果需要向另一个方法传递一个方法名，可以使用一个已编译的选择器。已编译选择器的类型为SEL。编译器为每个已编译的选择器赋予一个唯一ID。可以将此ID作为SEL对象传递，用它调用对应方法。@selector编译器指令使用方法名称创建SEL对象。在Scrambler游戏中，您将使用@selector指令获取指向timerFired方法的一个SEL已编译选择器类型。然后将该选择器传递给NSTimer对象，告诉计时器在时钟触发时调用timerFired方法。

在当前示例中，使用@selector编译器指令在编译时创建选择器。然而，有一件有趣的事情值得注意一下，您可以使用NSSelectorFromString函数在运行时以字符串的方式创建选择器。通过这种方式，可在运行时根据用户输入调用不同的方法。使用此运行时功能，需要使用respondsToSelector:方法判定对象是否具有要调用选择器的实现。如果没有调用此方法来验证对象是否具有要调用方法的实现，当对象中不存在该方法的实现时，会发生一个运行时错误导致应用程序崩溃。

//一，timer的使用
1，根据时间，设置触发函数。定时器允许我们在给定的时间段之后重复执行一段代码。

+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)ti 
				target:(id)aTarget 
				selector:(SEL)aSelector 
				userInfo:(id)userInfo 
				repeats:(BOOL)yesOrNo;
//下面使用类方法创建定时器,10秒后调用myTimerAction:方法。userInfo参数，
允许我们向定时器传递任何类型的对象。repeats参数设为NO，表示定时器方法只调用一次。
[NSTimer scheduledTimerWithTimeInterval:10.0
							target:self
							selector:@selector(myTimerAction:)
							userInfo:nil
							repeats:YES];
//注意NSTimer会对target对象进行retain。我们需要小心对待这个target的生命周期问题，尤其是重复性的timer。（NSTimer初始化后，self的retainCount加1。 那么，我们需要在释放这个类之前，执行[timer invalidate];否则，不会执行该类的dealloc方法。）
2.延迟调用函数
- (void)performSelector:(SEL)aSelector withObject:(id)anArgument afterDelay:(NSTimeInterval)delay;
如：
//延迟1.5秒调用showButton函数。
[self performSelector:@selector(showButton) withObject:nil afterDelay:1.5];
3.Timers
//This timer will call myMethod every 1 second.
NSTimer *myTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self
							selector:@selector(myMethod) userInfo:nil repeats:YES];
//定时器执行的方法，会在主线程中执行，不会线创建一个新线程。
//To stop a timer, use "invalidate":
[myTimer invalidate]; 
myTimer = nil; // ensures we never invalidate an already invalid Timer

3,给调用方法传递多个参数。
- (void)startMyTimer {
    /* ... Some stuff ... */
    [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(callMyMethod:) userInfo:[NSDictionary dictionaryWithObjectsAndKeys:someValue, @"value1", someOtherValue, @"value2", nil] repeats:YES];
}

- (void)callMyMethod:(NSTimer *)theTimer {
    NSString *value1 = [[theTimer userInfo] objectForKey:@"value1"];
    NSString *value2 = [[theTimer userInfo] objectForKey:@"value2"];
    [self myMethod:value1 setValue2:value2];
}

4,创建稍后才想要运行的定时器
NSTimer * myTimer = [NSTimer timerWithTimeInterval:10 target:self selector:@selector(test) userInfo:nil repeats:NO];
想启动定时器时使用下面的代码：
[[NSRunLoop mainRunLoop] addTimer:myTimer forMode:NSDefaultRunLoopMode];
5,创建未来预定的时间启动定时器
NSTimeInterval secondsPerDay = 24*60*60;
NSDate *tomorrow = [NSDate dateWithTimeIntervalSinceNow:secondsPerDay];
NSTimer *myTimer = [[NSTimer alloc] initWithFireDate:tomorrow interval:10.0 target:self selector:@selector(myTimerAction:) userInfo:nil repeats:NO];


6,测试一段 iPhone 代码运行时间的方法

iPhone 的硬件速度毕竟不比电脑，用户的耐心也是有限的，所以要时刻注意程序的运行时间。这里提供几个获取精确时间的方法

可以使用系统时间，通过格式化 nsstring 获，示例

NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
[formatter setDateFormat:@"YYYYMMddhhmmss"];
NSString *locationString=[formatter stringFromDate: [NSDate date]];


或直接计算代码耗时，示例

NSDate* tmpStartData = [NSDate date];
//You code here...
double deltaTime = [[NSDate date] timeIntervalSinceDate:tmpStartData];
NSLog(@">>>>>>>>>>cost time = %f", deltaTime);


7，NSTimer会是准时触发事件吗

　　答案是否定的，而且有时候你会发现实际的触发时间跟你想象的差距还比较大。NSTimer不是一个实时系统，因此不管是一次性的还是周期性的timer的实际触发事件的时间可能都会跟我们预想的会有出入。差距的大小跟当前我们程序的执行情况有关系，比如可能程序是多线程的，而你的timer只是添加在某一个线程的runloop的某一种指定的runloopmode中，由于多线程通常都是分时执行的，而且每次执行的mode也可能随着实际情况发生变化。

　　假设你添加了一个timer指定2秒后触发某一个事件，但是签好那个时候当前线程在执行一个连续运算(例如大数据块的处理等)，这个时候timer就会延迟到该连续运算执行完以后才会执行。重复性的timer遇到这种情况，如果延迟超过了一个周期，则会和后面的触发进行合并，即在一个周期内只会触发一次。但是不管该timer的触发时间延迟的有多离谱，他后面的timer的触发时间总是倍数于第一次添加timer的间隙。

　　原文如下“A repeating timer reschedules itself based on the scheduled firing time, not the actual firing time. For example, if a timer is scheduled to fire at a particular time and every 5 seconds after that, the scheduled firing time will always fall on the original 5 second time intervals, even if the actual firing time gets delayed. If the firing time is delayed so far that it passes one or more of the scheduled firing times, the timer is fired only once for that time period; the timer is then rescheduled, after firing, for the next scheduled firing time in the future.”

当线程空闲的时候timer的消息触发还是比较准确的，但是在36分12秒开始线程一直忙着做大量运算，知道36分14秒该运算才结束，这个时候timer才触发消息，这个线程繁忙的过程超过了一个周期，但是timer并没有连着触发两次消息，而只是触发了一次。等线程忙完以后后面的消息触发的时间仍然都是整数倍与开始我们指定的时间，这也从侧面证明，timer并不会因为触发延迟而导致后面的触发时间发生延迟。

　　综上: timer不是一种实时的机制，会存在延迟，而且延迟的程度跟当前线程的执行情况有关。
下面是摘抄书上的，
Timer并不保证精确地按照指定的时间间隔执行。由于运行循环函数的工作原理，没有办法保证Timer能搞在精确的时刻运行。Timer在执行一次之后，指定的时间的时间过去之前，是不会再次执行的。这意味着它不会比预计的时间间隔早，而只有可能会晚。通常情况下，实际的时间间隔只比预期晚若干毫秒，但也不能完全依赖于此。如果主运行循环上有长时间运行的方法，那么运行循环就无法在预计的时间启动Timer，直到主循环处理完毕，而这个时候有可能离预期时间已经过去很久了。



8，四、NSTimer为什么要添加到RunLoop中才会有作用

　　前面的例子中我们使用的是一种便利方法，它其实是做了两件事：首先创建一个timer，然后将该timer添加到当前runloop的default mode中。也就是这个便利方法给我们造成了只要创建了timer就可以生效的错觉，我们当然可以自己创建timer，然后手动的把它添加到指定runloop的指定mode中去。

　　NSTimer其实也是一种资源，如果看过多线程变成指引文档的话，我们会发现所有的source如果要起作用，就得加到runloop中去。同理timer这种资源要想起作用，那肯定也需要加到runloop中才会又效喽。如果一个runloop里面不包含任何资源的话，运行该runloop时会立马退出。你可能会说那我们APP的主线程的runloop我们没有往其中添加任何资源，为什么它还好好的运行。我们不添加，不代表框架没有添加，如果有兴趣的话你可以打印一下main thread的runloop，你会发现有很多资源。
　下面我们看一个小例子：

复制代码
- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [self testTimerWithOutShedule];
}

- (void)testTimerWithOutShedule
{
    NSLog(@"Test timer without shedult to runloop");
    SvTestObject *testObject3 = [[SvTestObject alloc] init];
    NSTimer *timer = [[NSTimer alloc] initWithFireDate:[NSDate dateWithTimeIntervalSinceNow:1] interval:1 target:testObject3 selector:@selector(timerAction:) userInfo:nil repeats:NO];
    [testObject3 release];
    NSLog(@"invoke release to testObject3");
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    NSLog(@"SvTimerSample Will resign Avtive!");
}
复制代码
　　这个小例子中我们新建了一个timer，为它指定了有效的target和selector，并指出了1秒后触发该消息，运行结果如下:
　观察发现这个消息永远也不会触发，原因很简单，我们没有将timer添加到runloop中。

　　综上: 必须得把timer添加到runloop中，它才会生效。
9，NSRunLoopCommonModes allows timer event while scrolling in UIScrollView. NSDefaultRunLoopMode prevent timer while scrolling.
