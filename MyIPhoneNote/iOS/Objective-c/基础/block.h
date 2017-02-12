1,blocks 可以简化enumeration

//枚举字典
NSDictionary *dic = [NSDictionary dictionaryWithObjectsAndKeys:@"a",@"key1",@"b",@"key2",@"c",@"key15", nil];
[dic enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
    NSLog(@"value for key %@ value is %@",key,obj);
    if ([obj isEqualToString:@"key2"]) {
        *stop = YES;//停止枚举
    }
}];

//枚举数组
NSArray *array = @[@"z",@"j",@"s"];
[array enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
    NSLog(@"index:%ld value: %@",idx,obj);
}];
//反序枚举数据
[array enumerateObjectsWithOptions:NSEnumerationReverse usingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
    NSLog(@"index:%ld = %@",idx,obj);
}];

2,block中可以使用在block前定义的本地变量（局部变量），但是不能改变它。除非在变量前加__block(注意是两个下滑线)。如果是instance variable可以改变。
3,//block 语法
blocks是对象，它封装了一段代码，这段代码可以在任何时候执行。
//block 函数声明
void (^simpleBlock)(void);
//block 代码
simpleBlock = ^{//没有参数可以省略^后面的一对儿（）
    NSLog(@"This is a block");
};
//执行block代码
simpleBlock();

可将变量声明和代码部分合并
void (^simpleBlock)(void) = ^{
    NSLog(@"This is a block");
};

4,带参数的block，并且返回值。
例如：计算两个数据的乘积

#if 0
double (^multiplyTwoValues)(double,double);

multiplyTwoValues = ^double(double firstValue, double secondValue){//^后面紧跟的第一个double是返回类型，为了简洁这个返回类型可以省略。
    return firstValue *secondValue;
};
#else
double (^multiplyTwoValues)(double,double) = ^(double firstValue,double secondValue){
    return firstValue * secondValue;
};
#endif
double result = multiplyTwoValues(2,4);
NSLog(@"The result is %f", result);

5,
- (void)testMethod {
    int anInteger = 42;
    void (^testBlock)(void) = ^{
        NSLog(@"Integer is: %i", anInteger);
    };
    testBlock();
}

变量anInteger在block外声明，但是它的值，在block定义的时候已经获取到了。
int anInteger = 42;
void (^testBlock)(void) = ^{
    NSLog(@"Integer is: %i", anInteger);
};
anInteger = 84;
testBlock();
// 结果：Integer is: 42
如果你在调用block时，改变了这个变量，block中的这个变量不受影响。同时你不能改变这个变量的值。

//修改block之外的变量.
默认情况下，在程序块中访问的外部变量是复制过去的，即写操作不对原变量生效。
//如果要改变这个变量。你需要在变量定义时，用__block修饰这个变量。

__block int anInteger = 42;
void (^testBlock)(void) = ^{
    NSLog(@"Integer is: %i", anInteger);
};
anInteger = 84;
testBlock();
// 结果：Integer is: 84
同时也意味着，你可以在block中修改这个变量。
__block int anInteger = 42;
void (^testBlock)(void) = ^{
    NSLog(@"Integer is: %i", anInteger);
    anInteger = 100;
};
testBlock();
NSLog(@"Value of original variable is now: %i", anInteger);
//Integer is: 42
//Value of original variable is now: 100


6，你可以把block当作函数的参数来传递。Blocks常用来做回调函数。
例如你请求一个web服务，因为这个服务可能花很长的时间，你应当显示数据进度，当任务完成后，你在隐藏这个进度显示。
你可以用delegate实现这个功能，但是Blocks make this much easier.

#if 0 //不带参数的

- (IBAction)fetchRemoteInformation:(id)sender {
    [self showProgressIndicator];
    XYZWebTask *task = ...
    //注执行网络任务，不会创建一个新的线程。
    [task beginTaskWithCallbackBlock:^{
        [self hideProgressIndicator];
    }];
}

//此代码写在XYZWebTask类中
- (void)beginTaskWithCallbackBlock:(void (^)(void))callbackBlock {
    ...
    callbackBlock();//执行回调函数，不加此代码，将不进行回调
}
#else //带参数的

- (IBAction)fetchRemoteInformation:(id)sender {
    [self showProgressIndicator];
    XYZWebTask *task = ...
    //注执行网络任务，不会创建一个新的线程。
    [task beginTaskWithCallbackBlock:^(int x,int y){
        [self hideProgressIndicator];
        NSLog(@"%d+%d=%d",x,y,x+y);
    }];
}

//此代码写在XYZWebTask类中
- (void)beginTaskWithCallbackBlock:(void (^)(int,int))callbackBlock {
    ...
    callbackBlock(5,6);//执行回调函数，不加此代码，将不进行回调
}

#endif

7,block 必须是函数参数中的最后一个参数。
- (void)beginTaskWithName:(NSString *)name completion:(void(^)(void))callback;
//调用
[self beginTaskWithName:@"MyTask" completion:^{
    NSLog(@"The task is complete");
}];

8，block 可以简化并发任务，你可以把block添加到一个任务队列里去调用。
//A serial queue only allows one task to execute at a time—the next task in the queue won’t be dequeued and invoked until the previous task has finished.
一个连续的队列，在同一时间，仅允许运行一个任务。队列中的下一个任务不会移除和调用，直到前一个任务完成。
//A concurrent queue invokes as many tasks as it can, without waiting for previous tasks to finish.
并发的队列尽调用尽可能多的任务，不需要等待前一个任务完成。

9，在Operation Queues中使用block。
NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
    NSLog(@"hahha");
    NSLog(@"Block :%@",[NSThread currentThread]);// 会在线程队列的线程中运行此代码。
}];
// 在main queue中运行block任务。
NSOperationQueue *mainQueue = [NSOperationQueue mainQueue];
[mainQueue addOperation:operation];//block中的代码不会立刻执行，会在主线程空闲时执行。

// 在background queue中执行block任务。
NSOperationQueue *queue = [[NSOperationQueue alloc] init];
[queue addOperation:operation];
[queue release];
10,使用Grand Central Dispatch,在Dispatch queues中执行Blocks
你可以创建自己的dispatch queue，或者使用通过GCD自动生成的队列的一个。

如果你想让人物并发执行。你可以获得一个已经存在的queue，通过dispatch_get_global_queue()函数并且制定优先级。
dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

为了dispatch the block to the queue，你可以使用dispatch_async() 或者 dispatch_sync()函数。
//The dispatch_async() function returns immediately, without waiting for the block to be invoked:
dispatch_async(queue, ^{
    NSLog(@"Block for asynchronous execution");
});

//The dispatch_sync() function doesn’t return until the block has completed execution;
dispatch_sync(queue, ^{
    NSLog(@"Block for synchronous execution");
});
you might use it in a situation where a concurrent block needs to wait for another task to complete on the main thread before continuing, 

11,
有时候我们对任务的执行顺序有要求，一个任务必须在另一个任务执行之前完成，这就需要用到Operation的依赖（Dependency）属性。 我们可以为每个Operation设定一些依赖的另外一些Operation，那么如果依赖的Operation没有全部执行完毕，这个 Operation就不会被执行。

[operation addDependency:anotherOperation];
[operation removeDependency:anotherOperation];

//顺序执行队列
NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
    NSLog(@"111");
    sleep(15);
    NSLog(@"333");
    NSLog(@"Block :%@",[NSThread currentThread]);
}];

NSBlockOperation *operation2 = [NSBlockOperation blockOperationWithBlock:^{
    NSLog(@"222");
    sleep(2);
    NSLog(@"Block :%@",[NSThread currentThread]);
}];

NSOperationQueue *mainQueue = [[NSOperationQueue alloc] init];
[mainQueue setMaxConcurrentOperationCount:1];//大于1并发执行
//[operation addDependency:operation2]; //按依赖执行

[mainQueue addOperation:operation];
[mainQueue addOperation:operation2];
[mainQueue release];


12，Memory Cycles Solution
局部变量在Blocks中always strong。block的代码运行完，这个strong pointer 会释放。这个局部变量就不存在了，所以没有问题。
有一种方式是在本地变量前加__weak.
如：__weak MyClass *weakSelf = self;//even though self is strong,weakSelf is weak.
weak means it's not keeping the object in the heap. if no one else is pointing to it,it just goes away, and the wek variable gets set to nil.
对于iOS4.0，要用__unsafe_unretained MyClass *weakSelf = self;

对于非ARC环境中，要用__block MyClass *weakSelf = self;
//被block的应用的对象，retainCount会自动加一，为了打破这种 retain circle，可以在对象前加__block，这样block块就不会维护这个对象了

13，执行block不会创建新的线程。除非创建NSBlockOperation。//个人观点
14,Block retain是无效的，要想保留block生命周期，可以通过copy来实现，记得release
local variables 总是strong引用，对象会保存在heap中。当block执行完后，the strong pointer goes away。
前面加__weak,它不会在heap中保存该对象。如果没有其它对象保持它，它就会释放，变为nil。

15，block可以像对象一样存储在数组中。
@property (nonatomic,strong) NSMutableArray *myBlocks;//array of blocks
//将block存放在数组中
__weak MyClass *weakSelf = self;
[self.myBlocks addObject:^{
    [weakSelf doSomething];//一定要弱引用
}];
//调用数组中的block
void (^doit) (void) = self.myBlocks[0];
doit();

16,Blocks and ARC
blocks最初在栈上创建，如果你想要保持一个block超过目前范围依然可以被使用，你不得不把它复制到堆里通过【copy】或者Block_copy()函数。现在ARC自动实现。
//在block 的属性声明里,我们规定所 有权限定词为 copy 而不是 strong。
如果在 ARC 模式下使用 blocks 并且你想避免捕获 self,推荐使用如下模式:
__weak id weakSelf = self;
block = ^(){
    id strongSelf = weakSelf;
    if (strongSelf != nil )
    {
        // do stuff with strongSelf
    }
};

￼如果你定位到 iOS 4,你不能使用__weak。取代去做:

__block __unsafe_unretained id unsafeSelf = self;

17,如果block引用的局部变量是一个对象，block将会有一个strong pointer指向它，直到block执行完毕。
block可以调用对象的方法，但不能直接给对象赋值。//如:对象为mArry，block内可以[mArray addObject:obj];但不能直接mArray=XX；

