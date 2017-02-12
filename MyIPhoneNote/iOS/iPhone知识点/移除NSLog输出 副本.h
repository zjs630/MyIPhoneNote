 iphone之发布版本的时候移除NSLog输出的方法。
只需要加入到pch文件中即可，__OPTIMIZE__这个编译选项是发布版本才有的，所以在编译调试版本的时候可以看到Log，而发布版本则没有Log。

#ifndef __OPTIMIZE__
#define NSLog(...) NSLog(__VA_ARGS__)
#else
#define NSLog(...) {}
#endif