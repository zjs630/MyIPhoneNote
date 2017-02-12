URLSession
NSURLSession是iOS7中新的网络接口,与NSURLConnection是并列的.

当程序在前台时,NSURLSession和NSURLConnection大部分可以互相替代.NSURLSession支持后台网络操作,除非用户强行关闭.

NSURLSession提供的功能:

1> 通过URL将数据下载到内存;

2> 通过URL将数据下载到文件系统;

3> 将数据上传到指定的URL;

4> 在后台完成上述功能.

5> 支持下载,断点续传,后台上传/下载,后台上传/下载任务跟进

对于小型数据,如用户登录,下载小图像,JSON&XML仍然使用NSURLConnection的异步或同步方法即可.

NSURLSession的使用:

使用NSURLSessionConfiguration来配置NSURLSession对象

用NSURLSession对象来启动一个NSURLSessionTask对象

也可以使用系统全局的sharedSession单例来满足大多数的需求

注意：

相比较NSURLConnection的返回处理，NSURLSession提供了灵活的数据返回方式，可以使用简单的block方式来处理返回数据，也可以使用更强大的delegate.

NSURLSessionConfiguration

用于定义和配置NSURLSession对象;

每一个NSURLSession对象都可以设置不同的NSURLSessionConfiguration，从而满足应用内不同类型的网络请求.

NSURLSessionConfiguration的三种类型：

1> defaultSessionConfiguration: 默认的session配置, 类似NSURLConnection的标准配置, 使用硬盘来存储缓存数据.

2> ephemeralSessionConfiguration: 临时的session配置, 与默认配置相比, 这个配置不会将缓存、cookie等存在本地，只会存在内存里，所以当程序退出时，所有的数据都会消失

3> backgroundSessionConfiguration: 后台session配置, 与默认配置类似, 不同的是会在后台开启另一个线程来处理网络数据.

NSURLSessionTask

NSURLSession使用NSURLSessionTask来具体执行网络请求的任务.

NSURLSessionTask支持网络请求的取消、暂停和恢复，比如下载文件暂停之后再恢复就能够自动从上次的进度继续下载 .

NSURLSessionTask还能获取数据的读取进度 .





NSURLSessionTask的三种类型:

1> NSURLSessionDataTask 处理一般的NSData数据对象, 比如通过GET或POST方式从服务器获取JSON或XML返回等等, 但不支持后台获取.

2> NSURLSessionUploadTask 用于上传文件, 支持后台上传 .

3> NSURLSessionDownloadTask 用于下载文件, 支持后台下载 .

通过HTTP PUT方法实现文件上传的步骤

实例化NSMutableURLRequest并指定HTTPMethod为PUT .

设置请求的授权 :

1> 授权字符串格式：用户名:口令 .

2> 授权模式：Basic base64编码的授权字符串 .

3> 为HTTPHeaderField的Authorization赋值 .

文件上传的请求部分


// 1. URLRequest
NSURL *url = [NSURL URLWithString:@"http://localhost/uploads/xxx.png"];
NSMutableURLRequest *requestM = [NSMutableURLRequest requestWithURL:url cachePolicy:0 timeoutInterval:2.0f];
requestM.HTTPMethod = @"PUT";
// 设置用户授权
// 1> 授权字符串(用户名+密码)
NSString *authStr = @"admin:123456";
// 2> BASE 64编码
NSData *authData = [authStr dataUsingEncoding:NSUTF8StringEncoding];
NSString *base64Str = [authData base64EncodedStringWithOptions:0];
NSString *auth = [NSString stringWithFormat:@"BASIC %@", base64Str];
[requestM setValue:auth forHTTPHeaderField:@"Authorization"];
