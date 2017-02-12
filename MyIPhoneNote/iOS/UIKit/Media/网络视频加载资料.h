你的以上5步应该没有问题，不过ios播放器播不了本地的.m3u8，视频流文件。
m3u8只支持http协议的远程播放。正为这事愁呢。
现在想在应用程序里搭建服务器，来播放本地的m3u8。但没有头绪

使用一个uiwebview加载一个视频网页，然后在回调方法中
- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    
    NSString *lJs = @"document.documentElement.innerHTML";
    NSString *lHtml = [webView stringByEvaluatingJavaScriptFromString:lJs];
    NSLog(@"html内容:%@",lHtml1);
    
    // NSString *lJs2 = @"(document.getElementsByTagName(\"video\")[0]).getElementsByTagName(\"source\")[0].src";  //qiyi
    NSString *lJs2 = @"(document.getElementsByTagName(\"video\")[0]).src";  // youku,tudou,ku6 ,souhu
    NSString *lm3u8 = [webView stringByEvaluatingJavaScriptFromString:lJs2];
    NSLog(@"video source:%@",lm3u8);
}

拿去试试吧，youku、tudou、ku6、qiyi都一个没问题的

19 楼：
发表于: 2012-02-28 09:39   发自: Web Page 只看该作者   小 中 大
下载到本地不能直接播放的，需要建立一个本地的httpserver 然后构造一个http的url播放

回 19楼(heiby) 的帖子
终于有人回答了，太感谢了。
建一个本地的httpserver是指自己搭个后台server吗？  还是在我app里面起一个后台线程，然后当做httpserver？

腾讯视频iphone 版它的离线下载是怎么做的？ 你觉得它保存是什么数据？ 应该不是本地的m3u8吧，因为它在没有联网的情况下可以播放本地视频。
21 楼：
发表于: 2012-02-28 10:04   发自: Web Page 只看该作者   小 中 大
m3u8是直播类型的，腾讯和奇艺等都是点播类型的，点播是在服务端是以mp4文件的形式存在，m3u8是有专门的直播软件把节目源采集过来转换出来的，是直播类型的流媒体，如果要通过appstore审核必须符合可变码流技术。