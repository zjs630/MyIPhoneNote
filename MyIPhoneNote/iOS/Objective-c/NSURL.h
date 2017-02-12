1,通过新的线程下载xml文件保存到本地，并修改本地plist文件的内容。
[NSThread detachNewThreadSelector:@selector(downloadNavigation) toTarget:self withObject:nil];

-(void)downloadNavigation{
	NSURL *categoryURL = [NSURL URLWithString:@"http://downmag2.app-sage.com/iPadBrowser/Navigation.xml"];
	NSData *cateData = [NSData dataWithContentsOfURL:categoryURL];
	if (cateData && [cateData length] > 0) {
		NSString *catePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Navigation.plist"];
		[cateData writeToFile:catePath atomically:YES];
		
		version = serverVersion;//将本地的版本号改为服务器的版本号。
		NSString *searchFilePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Version.plist"];
		NSMutableDictionary *versionDic = [NSMutableDictionary dictionaryWithContentsOfFile:searchFilePath];
		[versionDic setObject:version forKey:@"Version"];//修改版本号
		[versionDic writeToFile:searchFilePath atomically:YES];//保存更改
	}
}

2,调用Safari
NSURL *url = [[NSURL alloc] initWithString:@"http://www.g.cn"];
[[UIApplication sharedApplication] openURL:url];
//例子打开google地图
NSString* addressText = @"1 Queen st, Auckland, NZ";
addressText = [addressText stringByAddingPercentEscapesUsingEncoding: NSASCIIStringEncoding];
NSString* urlText = [NSString stringWithFormat:@"http://maps.google.com/maps?q=%@",addressText];
//NSlog(urlText);
[[UIApplication sharedApplication] openURL:[NSURL URLWithString:urlText]];


3,用Get方式读取网络数据：
// 将网络数读取为字符串
- (NSString *) getDataByURL:(NSString *) url {
    return [[NSString alloc] initWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:[url stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]]] encoding:NSUTF8StringEncoding];
}

//读取网络图片
- (UIImage *) getImageByURL:(NSString *) url {
    return [[UIImage alloc] initWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:[url stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]]]];
}

4,
NSString *string = @"http://www.test.com/a.php?name=中国";
NSURL *url = [NSURL URLWithString:string];//对于含有中文的url地址，返回的NSURL对象为空

//此时应该对url进行编码
NSURL *url = [NSURL URLWithString:[string urlEncoded]];

@implementation NSString (URLMethods)
- (id)urlEncoded {
    CFStringRef cfUrlEncodedString = CFURLCreateStringByAddingPercentEscapes(NULL,
                                                                             (CFStringRef)self,NULL,
                                                                             (CFStringRef)@"!#$%&'()*+,/:;=?@[]",
                                                                             kCFStringEncodingUTF8);
    
    NSString *urlEncoded = [NSString stringWithString:(NSString *)cfUrlEncodedString];
    CFRelease(cfUrlEncodedString);
    return urlEncoded;
}

//对于url解码：
- (id)urlDecoded{
    CFStringRef cfUrlDecodedString =
    CFURLCreateStringByReplacingPercentEscapesUsingEncoding(kCFAllocatorDefault,
                                                            (CFStringRef)self,
                                                            CFSTR(""),
                                                            CFStringConvertNSStringEncodingToEncoding(NSUTF8StringEncoding));
    
    NSString* urlDecoded = [NSString stringWithString:(NSString *)cfUrlDecodedString];
    CFRelease(cfUrlDecodedString);
    return urlDecoded;
}



@end




