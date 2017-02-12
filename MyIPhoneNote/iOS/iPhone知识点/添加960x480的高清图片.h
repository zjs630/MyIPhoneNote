开发时不需要关心高清图片如何处理只要将高清图做一个固定命名，系统就会在iPhone 4 iTouch 4时自动替换。




p.s. 
1. 固定后缀@2x中的x必需小写
2. 如果在命令行下用svn添加bg@2x.png要这样写 svn add bg\@2x.png@, 否则无法添加。

例如: 480x320的图片叫做bg.png, 那么对应的高清图就命名为bg@2x.png就可以了
在代码中设置图片的大小仍为480＊320。而不用设为960＊640。

系统会根据但前设备支持的分辨率加载图片，
若是iTouch 4,系统会加载bg@2x.png。


判断用户设备是否是 iPhone 4 Retina 屏
#define isRetina ([UIScreen instancesRespondToSelector:@selector(currentMode)] ?
CGSizeEqualToSize(CGSizeMake(640, 960),
                  [[UIScreen mainScreen] currentMode].size) : NO)

关于IOS程序设置启动画面以及图标的设备目前主要为：IPhone设备 和IPad设备

IPhone启动画面以及图标的设置

目前IPhone的分辨率为：320X480、640X960、640X1136。

Default.png                    320X480 iPhone 320X480分辨率屏幕默认启动图片。

Default@2x.png             640X960 iPhone 640X960分辨率屏幕默认启动图片。

Default-568h@2x.png    640X1136  iPhone 640X1136分辨率屏幕默认启动图片。

--------------------------------------------------------------------------------------

Icon.png                      57X57       10px   用户AppStore以及iPhone/iPod 中显示 必需

Icon@2x.png              114X114   20px  高清模式

Icon_120.png             120X120   20px  用于iPhone5的高清显示

Icon-Small.png           29X29       20px  用于设置以及Spotlight搜索

Icon-Small@2x.png   58X58      8px     用于Icon-Small.png的高清模式

Icon_80.png   80X80      8px   用于iPhone5在Spotlight搜索

---------------------------------------------------------------------------------------



IPad启动画面以及图标设置

Default-Portrait.png                            768X1024        iPad专用竖向启动画面

Default-Landscape.png                      768X1024        iPad专用横向启动画面

Default-PortraitUpsideDown.png        768X1024        iPad专用竖向启动画面（Home按钮在屏幕上面）

Default-LandscapeLeft.png                768X1024        iPad专用竖向启动画面（Home按钮在屏幕左面）

Default-LandscapeRight.png              768X1024        iPad专用竖向启动画面（Home按钮在屏幕右面）

--------------------------------------------------------------------------------------------

Icon-72.png         72X72       20px       用于在iPad桌面中显示必需

Icon-50.png         50X50       20px      用于iPad中的Spotlight搜索

Icon-29.png         29X29       10px      设置页面

