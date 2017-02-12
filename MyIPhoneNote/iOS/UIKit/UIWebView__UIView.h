//An internet browser in a UIView 
//Not just for displaying HTML(though it's good at that)
//Also can be used to display PDF's and other comples documents.

1,Three ways to load up HTML
    -(void)loadRequest:(NSURLRequest *)request;

	-(void)loadHTMLString:(NSString *)string baseURL:(NSURL *)baseURL;
	
	-(void)loadData:(NSData *)data
		   MIMEType:(NSString *)MiMEtype
   textEncodingName:(NSString *)encodingName;

1.Web view 加载URL页面。
CGRect webFrame = CGRectMake(0.0, 0.0, 320.0, 460.0);
UIWebView *webView = [[UIWebView alloc] initWithFrame:webFrame];
//[webView setBackgroundColor:[UIColor whiteColor]];
//自动缩放适应屏幕 webView.scalesPageToFit = YES;
NSURL *url = [NSURL URLWithString:@"http://www.google.com"];
NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
[webView loadRequest:requestObj];
[webView setDelegate:self];
[self addSubview:webView];
[webView release];

2,UIWebView加载本地Html文件。
NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"html"];
[myWebView loadData:[NSData dataWithContentsOfFile:path] MIMEType:@"text/html" textEncodingName:@"utf-8" baseURL:nil];

//ios 6 加载doc pdf文件
NSString *path = [[NSBundle mainBundle] pathForResource:docName ofType:nil];
NSURL *url = [NSURL fileURLWithPath:path];
NSURLRequest *request = [NSURLRequest requestWithURL:url];
[myWebView loadRequest:request];

3.web视图
UIWebView类使您可以将一个微型web浏览器集成到应用程序的用户界面上。
web视图通过其关联的委托对象提供有关网页何时被装载、及装载过程是否发生错误的
信息。web委托是指实现一个或多个UIWebViewDelegate协议方法的对象。您可以通过实
现委托方法来响应装载错误或处理一些与装载有关的其它任务。

4，向webView中的网页添加文本
NSString *js = [NSString stringWithFormat:@"var test = document.getElementById('testDiv');test.innerHTML = 'text from Objective C : %@';",obcText];
[myWebView stringByEvaluatingJavaScriptFromString:js];
                             
                             
涉及到互联网的 iPhone 应用里往往要抓取网页的<title>内容，您可以用 UIWebView，加载完成后执行 javascript 取得 html 的 title
self.title = [_webView stringByEvaluatingJavaScriptFromString:@"document.title"];

当然如果只是取<title> 内容，你可以不把 UIWebView show 出来，用完直接release好了。

另,可以用webview或者用nsurlconnection，webview可以用字符串或者javascript解析，connection可以用字符串解析，而且速度要比webview快，如果不加载网页，建议用connection连接url，然后用nsdata类型接受数据，再转化为nsstring.最后来截取你想显示的数据。

5,uiwebview中显示乱码的问题
 //自定义一个编码方式 
 NSStringEncoding enc=CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
 //将字符串按上面的编码方式转换编码
 NSString *theStr =[[NSString alloc] initWithBytes:[thedata bytes]length:thedata.length encoding:enc];
                             
6,
If you want to get the content without the html tags from the web page (html document) ,
then use this code inside the UIWebViewDidfinishLoading delegate method.
 
 NSString *myText = [webView stringByEvaluatingJavaScriptFromString:@"document.documentElement.textContent"];
                             
7,UIWebView打开txt乱码的解决方案:                             
//http://blog.csdn.net/dnj630/article/details/7298116

txt分带编码和不带编码两种，带编码的如UTF-8格式txt，不带编码的如ANSI格式txt。

带编码的用NSString的stringWithContentsOfFile可读出，不带的，我们依次尝试GBK和GB18030编码。                            

以下是从网络加载txt文件:
NSURL *url = [NSURL URLWithString:stringUrl];
NSData *data =[[NSData alloc] initWithContentsOfURL:url];
NSString* theStr = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
if (theStr == nil) {
    NSStringEncoding enc2=CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
    //将字符串按上面的编码方式转换编码
    theStr =[[NSString alloc] initWithBytes:[data bytes] length:data.length encoding:enc2];
}
if (theStr == nil) {
    NSStringEncoding enc3=CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGBK_95);
    theStr =[[NSString alloc] initWithBytes:[data bytes] length:data.length encoding:enc3];
}
NSString *theStr2 = [YJMyClassMethod stringToHtmlEncode:theStr];
[webView loadHTMLString:theStr2 baseURL:nil];
[data release];
[theStr release];




8,1.UIWebView播放方式。

UIWebView是一个功能强大的控件，这里介绍下播放gif动画的实现方法，代码如下

NSString *path = [[NSBundle mainBundle] pathForResource:@"main" ofType:@"gif"];
NSData *gifData = [NSData dataWithContentsOfFile:path];
UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
[webView loadData:gifData MIMEType:@"image/gif" textEncodingName:nil baseURL:nil];
[self.view addSubview:webView];
[webView release];

以上代码可以很容易的实现gif动画的播放，不过不能实现获取gif动画播放结束的时间动作，至少我还没有找到，如果各位朋友有此方法，请留言告知。

//关于push的一个例子
                             
                             
                             
#pragma mark delegate
                             
                             
//获得数据后,把数据嫁到保存的数据实例中
-(void) connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
[receiveData  appendData:data];
}

-(void) connection:(NSURLConnection *)connection didReceiveResponse:(NSHTTPURLResponse *) response
{
[receiveData setLength:8];
}


-(void)connection:(NSURLConnection *) didFailWithError:(NSError *) error
{
UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"Error" message:[error localizedDescription] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
[myAlert show];
[myAlert release];
}






-(void) connectionDidFinishLoading:(NSURLConnection *)connection
{
NSString *results = [[NSString alloc] initWithBytes:[receiveData bytes] 
                 length:[receiveData length] 
               encoding:NSASCIIStringEncoding];
[resultsView loadHTMLString:results baseURL:[NSURL URLWithString:baseURL]];
[results release];
}



-(void) viewDidLoad
{
CGRect resultsFrame = CGRectMake (10,10,200,300);
resultsView = [[UIWebView alloc] initWithFrame:resultsFrame];
[self.view addSubview:resultsView];

// 构建URL
baseURL = @"http://baidu.com";
NSString *urlString = [baseURL stringByAppendingString:@"/index.php"];
NSURL *url = [NSURL URLWithString:urlString];


//获得数据,新建一个url请求,由给的url初始化,同时指定url从原加载,没有缓存,超时为30秒
receiveData = [[NSMutableData alloc]initWithData:nil];
NSMutableURLRequest *req = [[NSMutableURLRequest alloc] initWithURL:url cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:30.0];

//开始设置req请求,请求的方法为POST,设置与页面包含的表单文件匹配的key值对,
[req setHTTPMethod:@"POST"];
[req setHTTPBody:[@"search = iphone"dataUsingEncoding:NSISOLatin1StringEncoding]];

NSURLConnection *conn = [[NSURLConnection alloc] initWithRequest:req delegate:self];

[req release];
[conn release];


}


                             

