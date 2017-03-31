
1-1,首先加载初始化方法、、通过xib文件初始化
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        NSLog(@"initWithNibName-------");
    }
    return self;
    
}
or
//- (instancetype)initWithCoder:(NSCoder *)coder 通过Storyboar首先加载此方法，之后加载awakeFromNib。不会加载init方法
1-2，通过storyboard加载
-(void)awakeFromNib
{
    [super awakeFromNib];
    NSLog(@"awakeFromNib");
}

1-3，
- (void)loadView

2

After instantiation and outlet-setting, viewDidLoad is called This is an exceptionally good place to put a lot of setup code.
- (void)viewDidLoad
{
    [super viewDidLoad]; // always let super have a chance in lifecycle methods
    // do some setup of my MVC
}
But be careful because the geometry of your view (its bounds) is not set yet!
At this point, you can’t be sure you’re on an iPhone 5-sized screen or an iPad or ???.
So do not initialize things that are geometry-dependent here.

3
Just before the view appears on screen,
you get notified (argument is just whether you are appearing instantly or over time via animation)

- (void)viewWillAppear:(BOOL)animated;

Your view will only get “loaded” once, but it might appear and disappear a lot. So don’t put something in this method that really wants to be in viewDidLoad. Otherwise, you might be doing something over and over unnecessarily.
Do something here if things you display are changing while your MVC is off-screen. Later we will use this to optimize performance by waiting until this method
(as opposed to viewDidLoad) to kick off an expensive operation (probably in another thread). View’s geometry is set here, but there are other (better?) places to react to geometry.

4
// Called just before the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.
- (void)viewWillLayoutSubviews NS_AVAILABLE_IOS(5_0);//测试 旋转controller会调用4，5方法。
//可以在这里初始化几何相关的东西，改变大小，位置等。

5
// Called just after the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.
- (void)viewDidLayoutSubviews NS_AVAILABLE_IOS(5_0);

6
- (void)viewDidAppear:(BOOL)animated;


7
And you get notified when you will disappear off screen too This is where you put “remember what’s going on” and cleanup code.
- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated]; // call super in all the viewWill/Did... methods
    // let’s be nice to the user and remember the scroll position they were at ...
    [self rememberScrollPosition]; // we’ll have to implement this, of course
    // do some other clean up now that we’ve been removed from the screen
    [self saveDataToPermanentStore]; // maybe do in did instead?
    // but be careful not to do anything time-consuming here, or app will be sluggish
    // maybe even kick off a thread to do what needs doing here (again, we’ll cover threads later)
}


8，
- (void)viewDidDisappear:(BOOL)animated;


