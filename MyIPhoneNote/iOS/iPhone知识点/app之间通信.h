//1,由于ios程序本身采用沙盒结构，比较封闭。各个app间是比较独立的。但是ios还提供了一些app间通信的接口。
可以利用这些接口，做些东西。
1。判断系统里是否安装了某个app。比如新浪微博应用注册了URL scheme为@"weibo"，我们可以通过
[[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"weibo://"]]来判断系统里是否发装了新浪微博。
2。从一个应用里启动另一个应用。可以通过接口
[[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"weibo://"]]来启动微博。
参数要根据微博里规定的方式传递，一般就像http的get方式传参一样。
当然启动以后，自己的应用就会退到后台，想要再切回来，就要在自己的应用里也注册URL scheme。做为回调参数传给微博app。