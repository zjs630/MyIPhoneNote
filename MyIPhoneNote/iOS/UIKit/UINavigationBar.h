1,给系统导航条换背景。好像高度不能改变。

@implementation UINavigationBar(customImage)

-(void)drawRect:(CGRect)rect{
	UIImage *backgroundImage = [UIImage imageNamed:@"nav_top_bg.png"];
	[backgroundImage drawInRect:CGRectMake(0, 0, 320, 44)];
}

@end

2，设置IOS5以上版本的导航条颜色。
NSString *currSysVer = [[UIDevice currentDevice] systemVersion];//当前设备的系统版本
NSString *reqSysVer = @"5.0";//要求的最低版本
BOOL osVersionSupported = ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending);
if (osVersionSupported) {//当前版本不低于最低要求的版本
	[self.navigationController.navigationBar setBackgroundImage:[UIImage imageNamed:@"nav_top_bg.png"] forBarMetrics:UIBarMetricsDefault];
}
3,设置导航栏的title字体样式
self.navigationController.navigationBar.titleTextAttributes = @{UITextAttributeTextColor : HEXCOLOR(0x424d56ff),NSFontAttributeName:[UIFont systemFontOfSize:20.0]};