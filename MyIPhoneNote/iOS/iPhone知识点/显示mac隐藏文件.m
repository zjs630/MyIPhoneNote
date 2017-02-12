Mac系统隐藏文件（Finder）的两种方法

mac系统的Finder中默认是不显示隐藏文件的，搜索也搜不到。下面介绍两种显示和隐藏文件的办法。
打开终端，通过下面的两行命令可以控制是否显示隐藏文件，注意大小写：
显示Mac隐藏文件的命令：
1
defaults write com.apple.finder AppleShowAllFiles -bool true
隐藏Mac隐藏文件的命令：
1
defaults write com.apple.finder AppleShowAllFiles -bool false
键入相应命令后回车，然后关闭终端并重启Finder后才能生效。
另外还有一条终端命令可以直接控制文件或文件夹的显隐：
隐藏文件/文件夹命令：
1
chflags hidden (文件/文件夹的相对或绝对路径)
例如输入：
1
chflags hidden /Users/jiguang/Desktop/test
就可以隐藏桌面上的test文件夹
显示文件/文件夹命令：
1
chflags nohidden (文件/文件夹的相对或绝对路径)
例如输入：
1
chflags nohidden /Users/jiguang/Desktop/test
就可以显示刚才隐藏掉的test文件夹了。
这两种方法都只是设置Finder中的文件的显隐的，对于会使用终端的同学就不管用了。