1,加载UIViewController子类MyHelloWorld的nib文件。
方法一：以代码为主
a,//引用类(应用程序委托类).h文件中定义一个子类的对象,添加属性方法。
MyHelloWorld *myHelloWorld;
@property (nonatomic, retain) IBOutlet MyHelloWorld *myHelloWorld;
b,//引用类.m文件中
@synthesize myHelloWorld;
- (void)applicationDidFinishLaunching:(UIApplication *)application {    
	
    // Override point for customization after application launch
	MyHelloWorld *ctrl =[[MyHelloWorld alloc] initWithNibName:@"MyHelloWorld" bundle:[NSBundle mainBundle]];
    self.myHelloWorld = ctrl;
    [ctrl release];
	[window addSubview:myHelloWorld.view];
    [window makeKeyAndVisible];
}
之后，[myHelloWorld release];
c,创建一个UIViewController子类，带nib文件，名称为MyHelloWorld.
方法2，通过IB设置
a,//引用类(应用程序委托类).h文件中定义一个子类的对象,添加属性方法。
MyHelloWorld *myHelloWorld;
@property (nonatomic, retain) IBOutlet MyHelloWorld *myHelloWorld;
b,//引用类.m文件中
#import MyHelloWorld;
@synthesize myHelloWorld;
- (void)applicationDidFinishLaunching:(UIApplication *)application {    
	
    // Override point for customization after application launch
	[window addSubview:myHelloWorld.view];
    [window makeKeyAndVisible];
}
之后，[myHelloWorld release];
c,创建一个UIViewController子类，带nib文件，名称为MyHelloWorld.
d,打开MainWindow.xib文件，往窗口中拖入一个View Controller控件，修改类名为：MyHelloWorld.
之后将应用程序委托与MyHelloWorld视图控制器控件产生连接。

2,实现自定义的状态栏（遮盖状态栏）：
CGRect frame = {{0, 0}, {320, 20}};
UIWindow* wd = [[UIWindow alloc] initWithFrame:frame];
[wd setBackgroundColor:[UIColor clearColor]];
[wd setWindowLevel:UIWindowLevelStatusBar];
frame = CGRectMake(100, 0, 30, 20);
UIImageView* img = [[UIImageView alloc] initWithFrame:frame];
[img setContentMode:UIViewContentModeCenter];
[img setImage:[UIImage imageNamed:@"00_0103.png"]];
[wd addSubview:img];
[wd makeKeyAndVisible];
[UIView beginAnimations:nil context:nil];
[UIView setAnimationDuration:2];
frame.origin.x += 150;
[img setFrame:frame];
[UIView commitAnimations];

3,windowLevel,接受者的窗口等级，默认值为0。窗口等级标识每个窗口的前后位置，0标示该窗口位置在最前面，数值大于0就标示该窗口叠在其他窗口后面。iphone默认只包含一个窗口实例，并且窗口的等级始终为0.

4,获取顶层窗口
UIWindow *appWindow = [UIApplication sharedApplication].windows[0];












