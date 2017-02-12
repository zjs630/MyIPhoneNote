/*1, 通知提供了一种方便在应用程序中的对象之间传递消息，而不需要对象之间直接引用的方法。
通知发布到通知中心，通知中心的职责是向所有注册的观察着转发通知，而观察者是那些请求被告知某些通知的对象。
a,把对象注册成为一个通知的观察者，代码：*/
[[NSNotificationCenter defaultCenter] addObserver:self 
										 selector:@selector(dosomething:)
											 name:@"myNotification"
										   object:nil];
1,通告机制
通告是一种消息广播，发送给应用程序中所有对通告表达的事件感兴趣的对象。
通告不同与委托的地方在于，通告是在对象执行完成动作之后产生，而不是之前。
收到通告的对象没有机会建议是否要执行动作，
而且对象的通告可以有多个监听者，但是只有一个委托对象。

通告机制相当于设计模式中的观察者模式。

首先创建一个Notification Center， 之后向通告中心注册为XX事件的监听者，
同时指定一个方法，在XX事件发生时，供通告中心调用，当此方法被调用后，说明我们关心的XX事件发生了，我们接受到了通知。
关键代码：
NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
[center addObserver:self
		   selector:@selector(myAction:)
			   name:NSWindowWillCloseNotification
			 object:nil];
-(void) myAction:(NSNotification *)notification{
	//.......
}		
注：若监听的对象被release后，因通告中心不会保持监听者对象，所以通告中心将发消息给不存在的对象。
因此我们要在监听者被回收之前，将此对象从通告中心删除。
[[NSNotificationCenter defaultCenter] removeObserver:self];

2,
// post notification 
[[NSNotificationCenter defaultCenter] postNotificationName:@"notificationName"
													object:self];

//add  Observer  
[[NSNotificationCenter defaultCenter] addObserver:self
										 selector:@selector(action)
											 name:@"notificationName"
										   object:nil];
//remove one notification
[[NSNotificationCenter defaultCenter] removeObserver:self name:@"notificationName" object:nil];

//remove all notification for self
[[NSNotificationCenter defaultCenter] removeObserver:self];

3，通过notification 传递NSString。
NSString *disPlayString=。。。
[[NSNotificationCenter defaultCenter] postNotificationName:@"ShowDigit" object:disPlayString];

接受notification的类添加代码：
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(displayDigit:) name:@"ShowDigit" object:nil];

-(void)displayDigit:(NSNotification *)notify{
	id aa = [notify object];
	[displayView inputDisplay:(NSString *)aa];
}

4，NSNotificationCenter发送消息后，在目标函数和调用函数中，功能执行顺序是同步的，不会创建新的线程。
所以说，NSNotificationCenter在post消息后，会一直调用函数中会一直等待被调用函数执行完全，然后返回控制权到主函数中，再接着执行后面的功能。即：这是一个同步阻塞的操作。
如果要想不等待，直接返回控制权，可以采用NSNotificationQueue。
//http://www.cnblogs.com/xiaouisme/archive/2012/04/06/2434753.html

5,通知中心对消息的分发是“同步的”，也就是说消息在发送到下一个接收者之前需要前一个接收者快速返回，否则就会阻塞下一个接收者接收消息，所以对于长时间的消息处理，需要另外启动一个线程来单独处理接收后的任务，确保在接收到消息后立即返回。

6,这项技术的好处是完全的解耦。另一方面，你失去了类型安全，因为在回调中你得到的是一个通知对象，而不像代理，编译器无法检查通知发送者和接受者之间的类型是否匹配。





