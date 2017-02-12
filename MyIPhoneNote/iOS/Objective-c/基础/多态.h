1,多态（polymorphism），指的是通过不同类型的对象使用相同的代码。
多态使得能够开发以下程序：来自不同类的对象可以定义共享相同名称的方法。
多态：相同的方法名称，不同的类。
使不同的类共享相同方法名称的能力称为多态。

例子：
//定义类A
@interface A  : NSObject 
-(void)print;
@end
@implementation
-(void)print{
    NSLog(@"This is class A");
}
@end

//定义类B
@interface B : NSObject 
-(void)print;
@end
@implementation
-(void)print{
    NSLog(@"This is class B");
}
@end

int main(int argc, char *argv[]){
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    A *a = [[[A alloc] init] autorelease];
    B *b = [[[B alloc] init] autorelease];
    [a print];
    [b print];
    [pool drain];
    return 0;
    //相同的方法名，不同的实现方式。//相同的方法名字，不同的类。//同一个方法名，有不同的类实现。我们称之为多态。
}
2，动态类型：能使程序直到执行时才能确定所属的类。
3，动态绑定：能使程序直到执行时才能确定对象调用的实际方法。
//Dynamic binding is determining the method to invoke at runtime instead of at compile time. 
例子
int main(int argc, char *argv[]){
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    id tempObj;
    A *a = [[[A alloc] init] autorelease];
    B *b = [[[B alloc] init] autorelease];
    tempObj = a;
    [tempObj print];//print this is class A
    tempObj = b;
    [tempObj print];//print this is class B
    [b print];
    [pool drain];
    return 0;
    //系统怎么知道要调用哪个print呢？
//    因为Objective-c的运行时环境一直会对“对象属于哪一个类”进行追踪。系统在运行的时候决定调用哪个方法，而不是在编译的时候。
}

//动态绑定在执行的时候容易出错，为了避免这种情况，可以使用Introspection and Protocols。
