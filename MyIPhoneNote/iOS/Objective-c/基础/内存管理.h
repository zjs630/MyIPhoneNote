1，将对象添加到任何类型的集合都会使该对象的引用次数增加1（集合的引用计数保持不变），
这就意味着，如果随后释放了添加的对象（仅保留计数减1），
那么数组中仍然保留对该对象的引用，所以对象不会被真正的释放，
从集合中删除对象后，能够使对象的引用计数减1。
2,NSString的内存管理。
a,Think of @"string" as autoreleased
In reality, they are constants, so retain and release have no effect on them.
b,NSString objects are usually sent copy rather than retain
The method copy in NSMutableString returns an NSString, not an NSMutableString.
Of course, you still release it when you are done with it. 
对所有字符串的对象来说，我们通常使用copy，而非retain。NSString 的copy方法非常高效，
内存中常量字符串的空间分配与其它对象不同，它们没有用到引用计数机制，所以不能自己手动释放这些对象。
如：
NSString *bString = @"abc";//这种情况下，字符串储存和管理由系统做，我们不用操心。

NSString *cString = [NSString stringWithFormat:@"my %@", @"life"];//autorelease

NSString *aString = [[NSString alloc] initWithString:@"some string"];//因用了alloc方式，所以需要［aString release］(xcode6编译器，在CommandLineTool创建的工程下，引用计数是一无效的数)
但可变字符串（NSMutableString）还是采用引用计数机制的。

3,内存管理规则摘要
a,发送一条release消息不一定销毁对象，当一个对象的引用计数变为0时，才销毁这个对象。
（release并不直接将对象删除，只是将对象的保留计数-1，如果对象保留计数减为0，则系统自动删除该对象）。
系统通过向对象发送一条dealloc消息来释放它所占用的内存。
b，自动释放池，用于在释放，池本身时，来自动释放池中的对象。每次［pool retain］，系统通过向池中的每一个对象发送一条release消息，来实现这个功能。
同时，系统会向池中每个引用计数为0的对象发送一条dealloc消息来销毁这个对象。
c，如果你的方法中不再需要一个对象，但需要返回它，那么向其发送一条autorelease消息，将它标记为以后释放。消息autorelease并不影响对象的引用计数。
d，无论对象是否添加到自动释放池，应用程序中止时，都会释放程序中对象所占用的内存。
e，如果想要保证在自动释放池被释放时，对象仍然存在，则应显式的保持它。如果对象的引用技术大于收到的autorelease消息数目，则在池被释放时会保留下来。
f，若果使用alloc，new，copy方法（或者使用allocWithZone：、copyWithZone：或mutableCopy方法）直接创建对象，则由你负责释放它。每次retain对象后，
都应release或autorelease它。

4.例子
	NSArray aa=[[NSArray alloc] initWithObjects:@"a",@"b",@"c",nil];
	NSLog(@"%d",[aa retainCount]);//1
	[aa release];//release对象后，对象不会马上释放，它会很快释放。在执行完下一条指令后，才释放。
	NSLog(@"%d",[aa retainCount]);//1 
	aa = nil;
	[aa release];
	NSLog(@"%d",[aa retainCount]);//0
	NSLog(@"%d",[aa retainCount]);//0
5， 内存池是可以嵌套使用的。内存池在内存中是用堆(stack)实现的，最内层的池在堆的最顶端，
所以释放的顺序就是从里到外的。一旦释放了外层的池，内层的池也自动释放了。
内存池使用drain关键字来释放。
6,例，
myImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"512.png"]];
NSLog(@"%d",[myImgView retainCount]);//1
[self.view addSubview:myImgView];
NSLog(@"%d",[myImgView retainCount]);//2
[myImgView release];
NSLog(@"%d",[myImgView retainCount]);//1
[myImgView release];
NSLog(@"%d",[myImgView retainCount]);//1对象已经释放掉理解为0，就好。
7，安全释放
#define SafeRelease(object) if(object != nil) {[object release];object = nil;}

8，You should override dealloc in your class,but Never call it.
Dealloc is called for you when the last owner release.
The one exception about calling it is that you must call[super dealloc] in your dealloc.
9,view memory management
A superview retains its subviews
Once you put a view into the view hierarchy,you can release your ownership if you want.
you send removeFromSuperView to it.Removing a view from the hierarchy immediately causes a release on it.

10，返回一个NSString对象的例子
-(NSString *)nameForStrdent{
	NSString *s;//此处应该改为 NSString *s = nil;
	if (self.view.frame.size.height>100) {
		s=@"zjs";
	}
	else if{
		s = @"ashun";
	}
	return s;
	//if and  if else 
	//if neither of these things are true, we'are going to return instance of an NS string that hasn't been allocated.
	
}

11，[pool release]  和  [pool drain]  有什么区别

在引用计数的方式下，release和drain是一样的，只有在用gc的时候不一样。


苹果官方文档的翻译

In a garbage collected environment, release is a no-op. NSAutoreleasePool therefore provides a drain method that in a reference-counted environment behaves the same as calling release, but which in a garbage collected environment triggers garbage collection (if the memory allocated since the last collection is greater than the current threshold). Typically, therefore, you should use drain rather than release to dispose of an autorelease pool.

在一个garbage collected环境里，release不做任何操作。 NSAutoreleasePool因此提供了一个 drain 方法，它在reference-counted环境中的行为和调用release一样, 但是在一个garbage collected环境中则触发garbage collection动作 (if the memory allocated since the last collection is greater than the current threshold)。 因此通常你应该使用drain而不是release去释放一个autorelease pool。




Installed Memory Is Not Free Memory.//你并不能用到所有安装着的内存

Installed Memory	Available Memory	Memory Warning Threshold
128 MB					35-40 MB					20-25 MB
256 MB					120-150 MB				 80-90 MB 
512 MB					340-370 MB				260-300 MB (estimated)

12,在使用ARC的情况下
NSObject *__weak obj = [NSObject new];//Assigning retained object to weak variablle; object will be released after assignment.
// the newly allocated object has no strong references to it, so it is immediately deallocated and someObject is set to nil.
if (obj == nil) {
    NSLog(@"obj 添加弱引用会，在创建对象后，立刻释放对象");
}
在非ARC的情况下，不能这么用。

13.
//All object are stored in the heap.
所有的对象都保存在堆中


