Xcode编译WebApps找不到js的错误解决办法

使用Xcode做WebApps时，使用UIWebview来调用一个页面，有时会遇到问题，其一就是编译的时候出现黄色感叹号的Warning，js文件都报错：warning: no rule to process file '$(PROJECT_DIR)/jquery-1.8.1.min.js' of type sourcecode.javascript for architecture i386
错误原因是：js和html等资源文件加入到project的时候，Xcode错误的将js文件都放到了编译源代码（Compile Sources）文件夹，以为js代码也需要“被编译”。
解决的办法：将Targets ->Build Phases-> Compile Sources 中的js文件拖拽到Copy Bundle Resource即可
知识点：
Copy Bundle Resources：是指生成的product的.app内将包含哪些资源文件。通过Copy Bundle Resources中内容的不同设置, 我们可以让不同的product包含不同的资源, 包括程序的主图标等, 而不是把XCode的工程中列出的资源一股脑的包含进去
Compile Sources：是指将有哪些源代码被编译
Link Binary With Libraries：是指编译过程中会引用哪些库文件

另转：Xcode编译错误和警告汇总
1、error: macro names must be identifiers YourProject_prefix.pch
　　原因: 因为你弄脏了预处理器宏，在它处于<Multiple Values>的时候修改了它
　　解决方法: Configiration选择All Configirations，清空它 然后分别重新定义你的Debug,Release,Distributin预处理器宏吧
2、warning: no rule to process file '$(PROJECT_DIR)/LoadingView.h' of type sourcecode.c.h for architecture armv6
　　原因： Target里Compile Sources里含有头文件 了，那里面不需要头文件
　　解决方法: 从Target里Compile Sources里删除头文件