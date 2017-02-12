1,请求网路xml数据。并保存到Documents目录下。

NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
NSString *documentDir = [documentPaths objectAtIndex:0];
NSString *tempFileName = [NSString stringWithFormat:@"%@/b.xml",documentDir];

NSLog(@"%@",tempFileName);

NSURL *url = [[NSURL alloc] initWithString:@"http://downmag2.app-sage.com/Test/Astro/Day/Taurus.xml"];

NSMutableURLRequest* request = [[NSMutableURLRequest alloc] initWithURL:url
															cachePolicy:NSURLRequestReloadIgnoringCacheData
														timeoutInterval:10];

NSHTTPURLResponse* response = nil;
NSError* error = nil;

NSData* data = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];

if(error != nil || [response statusCode] != 200)
return NO;

[data writeToFile:tempFileName atomically:YES];



2,NSMutableURLRequest timeout interval 不起作用的原因
//=============
NSMutableURLRequest* request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:theURL]
                                                       cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData
                                                   timeoutInterval:10.0];
[request setHTTPMethod:theMethod];

// Ok here
NSLOG(@"timeout: %f", request.timeoutInterval);   // Displays 10.000000

NSString *fullRequestString = @"name=name&value=value";  // not real data
[request setHTTPBody: [fullRequestString dataUsingEncoding:NSASCIIStringEncoding]];

// Timeout changed here, no idea why
NSLOG(@"timeout: %f", request.timeoutInterval);   // Displays 240.000000
[request setTimeoutInterval:10.0];

NSLOG(@"timeout: %f", request.timeoutInterval);   // Displays 240.000000


利用POST方式进行URLConnection，在WWAN连接情况下，在设置了setHTTPBody之后，系统会默认修改timeoutInterval为240s，可能是因为在WWAN（连wifi测试后也一样...）连接时，一个太短的timeout可能会引起一些不必要的问题，所以apple强制把有body信息的post连接的timeout设定为240s。
//最新测试，在ios 6 中，这个10s超时突然起作用了。
想要修改时间三种方式：
1. 改为get方式，如果可以的话。
可以参考前一篇post和get方式连接网络的文章
2. 放在后台另开一条线程运行。
3. 利用NSTimer，写一个计时器，时间到cancel掉connection。
计时器程序如下，

if (needsSeparateTimeout){
    
    SEL sel = @selector(customCancel);
    
    NSMethodSignature* sig = [self methodSignatureForSelector:sel];
    
    NSInvocation* invocation = [NSInvocation invocationWithMethodSignature:sig];
    
    [invocation setTarget:self];
    
    [invocation setSelector:sel];
    
    NSTimer *timer = [NSTimer timerWithTimeInterval:WS_REQUEST_TIMEOUT_INTERVAL invocation:invocation repeats:NO];
    
    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
    
}
In the custom cancel method the connection is cancelled

[super cancel];