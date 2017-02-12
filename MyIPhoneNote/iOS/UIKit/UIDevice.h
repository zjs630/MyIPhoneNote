1，比较版本的高低，要求系统版本不低于4.1.
	//获取设备系统的版本
	NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
	NSString *reqSysVer = @"4.1";
	BOOL osVersionSupported = ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending);
	return osVersionSupported;//return yes,表示当前版本不低于4.1
2, 获取设备信息
NSString *modelname = [[UIDevice currentDevice] model];

if ([modelname isEqualToString:@"iPhone"]) {
}

else if ([modelname isEqualToString:@"iPod Touch"]) {

}

else if ([modelname isEqualToString:@"iPhone Simulator"]) {
	
}
3,方向变换


UIDeviceOrientationUnknown  //代表所有的错误或硬件失效

UIDeviceOrientationPortrait // 纵向,竖直向上

UIDeviceOrientationPortraitUpsideDown //纵向,上下颠倒

UIDeviceOrientationLandscapeLeft //横向,设备逆时针旋转

UIDeviceOrientationLandscapeRight //横向,设备顺时针旋转

UIDeviceOrientationFaceUp //设备被平放,正面朝上

UIDeviceOrientationFaceDown //平放,正面朝下

调整方向变化的方法:

-(void) didRotateFromInterfaceOrientation: 
(UIInterfaceOrientation)fromInterfaceOrientation
{
    //处理方向变换后的改变的代码
}
4，区分iPad和iPone
if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
	//add phone controller
}else {
	//add pad controller
}

//例子：判断是否是iPad。
BOOL iPad = (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad);
BOOL iPad = ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad); !
//UIViewController's designated initializer 让你指定一个.xib文件的名字。
因此可以根据设备的不同，指定不同的.xib文件。
NSString *xibName = iPad?@"MyNib-iPad":@"MyNib";
UIViewController *vc = [[UIViewController alloc] initWithNibName:xibName bundle:nil];
... instead of ...
UIViewController *vc = [[UIViewController alloc] init];

5，让某个ViewController支持屏幕旋转
整个程序需要支持横竖屏切换得时候，会比较简单，在每个ViewController 的

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation

方法中，return YES; 就好。

可如果只是要某个VC( = View Controller)支持横竖屏切换呢？单独在那个view controller中像上面那样做是没有效果的。

这个时候我们可以取 UIDevice的 Orientation来判定：

_1、在VC中注册 UIDevice 的 UIDeviceOrientationDidChangeNotification 通知：

NSNotificationCenter *center = [NSNotificationCenter defaultCenter];

[center addObserver:self selector:@selector(doRotate:) name:UIDeviceOrientationDidChangeNotification object:nil];

_2、在自己的 doRotate函数里面处理:

- (void)doRotate:(NSNotification *)notification{
	UIDeviceOrientation deviceOrientation = [[UIDevice currentDevice] orientation];	
	[[UIApplication sharedApplication] setStatusBarOrientation:deviceOrientation];
}

_3.

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation

也是要 return YES;

//横屏切换为竖屏
UIDeviceOrientation deviceOrientation = [[UIDevice currentDevice] orientation];
if (deviceOrientation != UIDeviceOrientationPortrait) {
    [[UIApplication sharedApplication] setStatusBarOrientation:UIDeviceOrientationPortrait];
}
//只支持竖屏
在info.plist文件中修改
Supported interface orientation 为Portrait(bottom home button)
去掉其它选项

6，在ios4.0以后，系统有了对多线程的支持。判断是否是多线程的代码如下：
UIDevice *device = [UIDevice currentDevice];
if(device respondsToSelector:@selector(isMultitaskingSupported)){
    NSLog(@"yes");
}
