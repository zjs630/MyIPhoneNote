1,获取当前连接wifi的信息
#import <SystemConfiguration/CaptiveNetwork.h>

- (void)printSSIDInfo{
    CFArrayRef myArray = CNCopySupportedInterfaces();
    if(myArray){
        CFDictionaryRef myDict = CNCopyCurrentNetworkInfo(CFArrayGetValueAtIndex(myArray, 0));
        NSLog(@"%@",myDict);
        if(myDict){
            CFStringRef currentSSID = CFDictionaryGetValue (myDict,kCNNetworkInfoKeySSID );
            NSLog(@"SSID:%@",currentSSID);
            CFRelease(myDict);
        }
        CFRelease(myArray);
    } 
}

结果：
{
    BSSID = "b0:48:7a:19:8:3e";
    SSID = home;
    SSIDDATA = <686f6d65>;
}

bssid 无线路由器的mac地址
ssid 连接的无线网络的名称
