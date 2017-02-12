//320X480     480X320    状态栏高 20 像素高   导航栏 工具栏 44像素高
1,隐藏状态栏：
[[UIApplication sharedApplication] setStatusBarHidden: YES animated:NO];//过时了，建议用下面的方法。
即：[application setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
或者直接
- (void)applicationDidFinishLaunching:(UIApplication *)application{
	application.statusBarHidden = YES;
	// [[UIApplication sharedApplication] setStatusBarHidden: YES];
}
或者再程序info.plist文件中添加一选项：
status bar is initially hidden,后面打钩。
2,Display the Network Activity Status Indicator
This is the rotating icon displayed on the iPhone status bar
in the upper left to indicate there is background network
activity taking place.

UIApplication* app = [UIApplication sharedApplication];
app.networkActivityIndicatorVisible = YES; // to stop it, set this to NO

3 状态栏
//首先,要访问UIApplication类,需要使用:
UIApplication *myApp = [UIApplication sharedApplication];
//隐藏状态栏
//[myApp setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];//Use -[UIViewController prefersStatusBarHidden]
//状态栏风格
//[myApp setStatusBarStyle:UIStatusBarStyleBlackOpaque]; //黑色不透明,白色文字
//Default        //默认,白色,黑色文字
//BlackTranslucent //黑色不透明,白色文字

4,通过点击按钮打开一个网址：//调用Safari
//按钮代码
UIButton *weiboButton = [UIButton buttonWithType:UIButtonTypeCustom];
[weiboButton setFrame:CGRectMake(85, 52, 245, 30)];
[weiboButton addTarget:self action:@selector(openWeibo) forControlEvents:UIControlEventTouchUpInside];
[self.view addSubview:weiboButton];
//打开网址代码
-(void)openWeibo{
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://t.sina.com.cn/ipad123"]];
}
5,发起电话呼叫
//以http://和https://开头的URL是与safari关联的，若要进行电话呼叫，需要使用前缀为tel:的协议。
[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"tel://03118805"]];

//调用谷歌地图(Google Maps)
NSString* searchQuery = @"1 Infinite Loop, Cupertino, CA 95014";
searchQuery = [addressText stringByAddingPercentEscapesUsingEncoding: NSUTF8StringEncoding];
NSString* urlString = [NSString stringWithFormat:@"http://maps.google.com/maps?q=%@", searchQuery];
[[UIApplication sharedApplication] openURL:[NSURL URLWithString:urlText]];

//调用邮件客户端(Apple Mail)
[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"mailto://admin@eyecm.com"]];
//调用短信(SMS)
[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"sms:10086"]];

//调用应用商店(AppStore)
NSURL *appStoreUrl = [NSURL URLWithString:@"http://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=99999"];
[[UIApplication sharedApplication] openURL:appStoreUrl];

//iOS拨打电话能返回到app,这种方法发短信不能返回app
UIWebView*callWebview =[[UIWebView alloc] init] ;
// tel:  或者 tel://
NSURL *telURL =[NSURL RLWithString:strPhoneNumber];
[callWebview loadRequest:[NSURLRequest requestWithURL:telURL]];

[self.view addSubview:callWebview];

6，app Icon 显示数字
 [[UIApplication sharedApplication] setApplicationIconBadgeNumber:5];
//
-(void)applicationWillTerminate:(UIApplication *)application{//程序终止
 [[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];//清除数字
}

7，网络活动指示器
当用户使用网络时，应当在iPhone的状态条上放置一个网络指示器，警告用户当前正在进行网络操作。
UIApplication *myApp = [UIApplication sharedApplication];
myApp.networkActivityIndicatorVisible = YES;//禁止设为NO


3.11 应用程序服务
//挂起
-(void) applicationWillResignAction:(UIApplication *) application {
	NSLog(@"About to be suspended");
	//为挂起做准备的代码
	
}

//恢复
-(void)applicationDidBecomeAction:(UIApplication *) application{
	NSLog(@"Become action");
	//为恢复做准备的代码
}

9，在应用程序关闭时，它只是简单的把内存清空，以加快关闭速度。
appdelegate中的dealloc方法永远不会被调用。
如果你需要在程序关闭时执行代码，do it inside the applicationWillTerminate method.
If you target IOS 4 or higher, you should use applicationDidEnterBackground instead.

10、本地通知（类似于push通知）按home键到后台 十秒后触发：
UILocalNotification *notification=[[UILocalNotification alloc] init]; 
if(notification!=nil) {
	NSLog(@">> support local notification");
	NSDate *now=[NSDate new];
	notification.fireDate=[now addTimeInterval:10];
	notification.timeZone=[NSTimeZone defaultTimeZone];
	notification.alertBody=@"该去吃晚饭了！";
	[[UIApplication sharedApplication].scheduleLocalNotification:notification];
}
11,清空本地通知
- (void)applicationDidBecomeActive:(UIApplication *)application{
    [[UIApplication sharedApplication] cancelAllLocalNotifications];//清空所有的本地提醒
}

12,禁止程序运行时自动锁屏 
[[UIApplication sharedApplication] setIdleTimerDisabled:YES]; 

13,保持网络后台运行600秒。
- (void)keepBackgroundNetTask{
    UIApplication *app = [UIApplication sharedApplication];
    __block UIBackgroundTaskIdentifier taskId;
    taskId = [app beginBackgroundTaskWithExpirationHandler:^{
        //NSLog(@"后台任务超时被退出");
        [app endBackgroundTask:taskId];
    }];
    if(taskId == UIBackgroundTaskInvalid){
        //NSLog(@"开启后台任务失败");
        return ;
    }
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        //NSLog(@"后台任务据最长时限还有 %f 秒",app.backgroundTimeRemaining);
        for (int i=0; i<5; i++) {
            [NSThread sleepForTimeInterval:60];
            //NSLog(@"后台任务据最长时限还有 %f 秒",app.backgroundTimeRemaining);
        }        
        //[app endBackgroundTask:taskId];//通知系统后台任务已处理完毕
    });
    
}

14, // 关闭键盘
[[[UIApplication sharedApplication] keyWindow] endEditing:YES];

15,判断设备横竖屏
UIInterfaceOrientation currentOrientation = [UIApplication sharedApplication].statusBarOrientation;
if (currentOrientation == UIInterfaceOrientationLandscapeLeft || currentOrientation == UIInterfaceOrientationLandscapeRight) {//横屏状态
    [self landscapeUI];
}
16.UIApplication是个单例，整个应用程序只有一个UIApplication对象，不能再通过alloc或new创建新的对象，否则程序会崩溃。
“There can only be one UIApplication instance”
