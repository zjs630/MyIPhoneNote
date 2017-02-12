1,UIScreen对象代表iPhone的物理屏幕([UIScreen mainScreen])。
此屏幕对象建立视图布局边界与像素空间之间的映射。它返回全屏大小(bounds)或只是应
用程序占用的矩形(applicationFrame)。后面会考虑状态栏以及任何工具栏/导航栏(如果已使用)的大小。
2,两个确定屏幕大小的方法。
	CGRect r = [[ UIScreen mainScreen ] applicationFrame];//返回屏幕的可显示区域。此空间不包括状态栏。
	r.origin.y = 0.0;//改变垂直方向的偏移量。
	//r=0，20，320，460
	
	CGRect rx = [[ UIScreen mainScreen ] bounds];//返回整个屏幕的边界，包括状态缆所占的空间。
	//r=0，0，320，480
3、判断设备是iphone还是iphone4的代码：

#define isRetina ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size) : NO)

#define iPhone5 ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)
