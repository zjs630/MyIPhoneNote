1.从iOS7开始系统提供了两种管理状态栏的方式：
（1）通过UIViewController来管理。（每个view controller都可以拥有不同的状态栏）
（2）通过UIApplication来管理。（一个应用程序的状态栏都有它统一管理）
在iOS7中，默认情况下都是有UIViewController来管理的，
//隐藏状态栏
//Use -[UIViewController prefersStatusBarHidden]
//状态栏风格
//preferredStatusBarStyle

//、、、
2.利用UIApplication来管理状态栏。首先要修改info.plist文件,否则代码设置失效
view controller-based status bar appearance -> NO
