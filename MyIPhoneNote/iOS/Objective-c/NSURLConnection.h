NSURLConnection同步，异步与SSL  
http://qzc770707.blog.163.com/blog/static/3408275320105249566560/

通常在iPhone里用NSURLConnection做url请求

1.NSURLConnection同步与异步请求
(1)异步请求：
NSMutableData* buf = [[NSMutableData alloc] initWithLength:0];
NSURLConnection* connection = [[NSURLConnection alloc] initWithRequest:req delegate:self];

// 收到响应时, 会触发
- (void)connection:(NSURLConnection *)aConnection didReceiveResponse:(NSURLResponse *)aResponse;
// 可以在里面判断返回结果, 或者处理返回的http头中的信息

// 每收到一次数据, 会调用一次
- (void)connection:(NSURLConnection *)aConn didReceiveData:(NSData *)data;
// 因此一般来说,是
- (void)connection:(NSURLConnection *)aConn didReceiveData:(NSData *)data
{
    [buf appendData:data];
}
// buffer就是前面initWithRequest时同时声明的.

// 网络错误时触发
- (void)connection:(NSURLConnection *)aConn didFailWithError:(NSError *)error;

// 全部数据接收完毕时触发
- (void)connectionDidFinishLoading:(NSURLConnection *)aConn;


(2)同步请求：
/ 初始化請求
NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];        
// 設置URL
[request setURL:[NSURL URLWithString:urlStr]];
// 設置HTTP方法
[request setHTTPMethod:@"GET"];
// 發送同步請求, 這裡得returnData就是返回得數據楽
NSData *returnData = [NSURLConnection sendSynchronousRequest:request 
                                           returningResponse:nil error:nil];
// 釋放對象
[request release];


实例：
NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
NSString *documentDir = [documentPaths objectAtIndex:0];
NSString *tempFileName = [NSString stringWithFormat:@"%@/b",documentDir];
//NSLog(@"%@",tempFileName);

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


//关于同步请求 超时实效问题
//Note that in addition to the initializer you called, you can also call -setTimoutInterval: on an NSMutableURLRequest. The timeout value does indeed work, but any value less than 240 is ignored -- that's the minimum value respected by the iOS framework. If you want to set a lower timeout value, then your only choice is to use an asynchronous request.

//If you want to asynchronously cancel a request (ie, perform the request in the background and allow the foreground UI thread to issue a cancel in response to the user hitting a Cancel or Stop button), then you have to make an asynchronous URL request. There's no way to do it with a synchronous request. For example, you can't even kill a dispatch queue while it is currently executing a block.

//You might want to look at ASIHTTPRequest, which wraps up some of this functionality a bit differently.





2. 注意head请求，如果在head响应中继续请求下一个地址，之后的响应和前一个响应对象的指针地址一样，内容也一样。改为了get请求，解决此问题。还没有更彻底的解决办法。

另外设置setCachePolicy不起作用。
