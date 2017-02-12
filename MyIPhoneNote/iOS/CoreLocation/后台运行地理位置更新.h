1,方法整理:4.后台运行GPS

当程序切换到后台后仍然开始gps 的方法其实很简单
只需要在 info.plist 里加上 "Required background modes" 这个项
然后添加这个项的1个 item "App registers for location updates"

然后你的app 如果在前台开启了 gps ,切到后台后 依然会持续更新gps 信息
调用代理方法. 

在这里要提醒下, 在后台开启gps会持快速续消耗电池
所以更好的方法是吧 在切换到后台后, 把原来高精度的gps 调用换成低精度的,来增加电池寿命

在 applicationDidEnterBackground 中加入
if ([CLLocationManager significantLocationChangeMonitoringAvailable]) 
{
    // Stop normal location updates and start significant location change updates for battery efficiency.
    [[GlobalVariables locationManager] stopUpdatingLocation];
    [[GlobalVariables locationManager] startMonitoringSignificantLocationChanges];
}
else 
{
    NSLog(@"Significant location change monitoring is not available.");
}

在applicationDidBecomeActive 中加入 
if ([CLLocationManager significantLocationChangeMonitoringAvailable]) 
{
    // Stop significant location updates and start normal location updates again since the app is in the forefront.
    [[GlobalVariables locationManager] stopMonitoringSignificantLocationChanges];
    [[GlobalVariables locationManager] startUpdatingLocation];
}
else 
{
    NSLog(@"Significant location change monitoring is not available.");
}










