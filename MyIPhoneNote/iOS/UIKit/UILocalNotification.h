1.显示本地通知
+(void)showLocalNotification:(NSString *)text{
    UILocalNotification *notification=[[UILocalNotification alloc] init];
    notification.timeZone=[NSTimeZone defaultTimeZone];
    notification.repeatInterval=NSDayCalendarUnit;//设置重复提醒间隔
    notification.applicationIconBadgeNumber = [UIApplication sharedApplication].applicationIconBadgeNumber + 1;
    notification.alertAction = NSLocalizedString(@"显示", nil);
    notification.fireDate=[[NSDate date] dateByAddingTimeInterval:1];
    notification.alertBody=text;
    //设置提醒声音为默认的声音
    //notification.soundName=UILocalNotificationDefaultSoundName;
    [notification setSoundName:@"abc.caf"];

    [[UIApplication sharedApplication] scheduleLocalNotification:notification];
}
2,
iOS 程序启动时总会调用application:didFinishLaunchingWithOptions:，其中第二个参数launchOptions为NSDictionary类型的对象，里面存储有此程序启动的原因。

//若用户直接启动，lauchOptions内无数据;
//若由其他应用程序通过openURL:启动，则UIApplicationLaunchOptionsURLKey对应的对象为启动URL（NSURL）,UIApplicationLaunchOptionsSourceApplicationKey对应启动的源应用程序的bundle ID (NSString)；
//若由本地通知启动，则UIApplicationLaunchOptionsLocalNotificationKey对应的是为启动应用程序的的本地通知对象(UILocalNotification)；
//若由远程通知启动，则UIApplicationLaunchOptionsRemoteNotificationKey对应的是启动应用程序的的远程通知信息userInfo（NSDictionary）；
//其他key还有UIApplicationLaunchOptionsAnnotationKey,UIApplicationLaunchOptionsLocationKey,
//UIApplicationLaunchOptionsNewsstandDownloadsKey。
如果要在启动时，做出一些区分，那就需要在下面的代码做处理。
比如：您的应用可以被某个其它应用调起（作为该应用的子应用），要实现单点登录，那就需要在启动代码的地方做出合理的验证，并跳过登录。

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSURL *url = [options objectForKey:UIApplicationLaunchOptionsURLKey];
    if(url)
    {
    }
    NSString *bundleId = [options objectForKey:UIApplicationLaunchOptionsSourceApplicationKey];
    if(bundleId)
    {
    }
    UILocalNotification * localNotify = [options objectForKey:UIApplicationLaunchOptionsLocalNotificationKey];
    if(localNotify)
    {
        NSDictionary* infoDic = localNotif.userInfo;
    }
    NSDictionary * userInfo = [options objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey];
    if(userInfo)
    {
    }
    
//    UIApplicationState state = [application applicationState];
//    if (state == UIApplicationStateInactive) {
//        NSDictionary *dic = [notification.userInfo objectForKey:@"datanew"];
//    }

}

如果此时你的客户端 软件仍在打开，则会调用
- (void)application:(UIApplication *)app didReceiveLocalNotification:(UILocalNotification *)notif
{
    NSDictionary* infoDic = localNotif.userInfo;

}

3,//在程序中取消已经设定的通知的方法了：

NSString *myIDToCancel = @"some_id_to_cancel";
UILocalNotification *notificationToCancel=nil;
for(UILocalNotification *aNotif in [[UIApplication sharedApplication] scheduledLocalNotifications])
{
    if([aNotif.userInfo objectForKey:@"ID"] isEqualToString:myIDToCancel])
    {
        notificationToCancel=aNotif;
        break;
    }
}
[[UIApplication sharedApplication] cancelLocalNotification:notificationToCancel];

