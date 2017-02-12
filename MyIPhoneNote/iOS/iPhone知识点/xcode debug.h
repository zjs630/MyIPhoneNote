1，在运行程序时出现崩溃，但控制台没有显示出具体的原因和位置。
	解决方法：在Groups&Files文件夹中，展开Executables,查看执行程序的get info
	在Variables to be set in the environment中，添加Name:NSZombieEnabled,Value:YES;
	注意打对钩。
	
	
2,How do I link all the Objective-C classes in a static library?

Set the Other Linker Flags build setting to -ObjC. 
If that doesn’t bring in all the classes, set it to -all_load.

3,Xcode debug 命令
http://blog.csdn.net/likendsl/article/details/7576549

符合以上两个条件之后，控制台（即日志输出窗口All Output）会自动打出一个（lldb）命令，你在其后输入bt，回车。

命令                        解释
break NUM               在指定的行上设置断点。
bt                      显示所有的调用栈帧。该命令可用来显示函数的调用顺序。
clear                   删除设置在特定源文件、特定行上的断点。其用法为：clear FILENAME:NUM。
continue                继续执行正在调试的程序。该命令用在程序由于处理信号或断点而
                        导致停止运行时。
display EXPR            每次程序停止后显示表达式的值。表达式由程序定义的变量组成。
file FILE               装载指定的可执行文件进行调试。
help NAME               显示指定命令的帮助信息。
info break              显示当前断点清单，包括到达断点处的次数等。
info files              显示被调试文件的详细信息。
info func               显示所有的函数名称。
info local              显示当函数中的局部变量信息。
info prog               显示被调试程序的执行状态。
info var                显示所有的全局和静态变量名称。
kill                    终止正被调试的程序。
list                    显示源代码段。
make                    在不退出 gdb 的情况下运行 make 工具。
next                    在不单步执行进入其他函数的情况下，向前执行一行源代码。
print EXPR              显示表达式 EXPR 的值。

print-object            打印一个对象
print (int) name      打印一个类型
print-object [artist description]   调用一个函数
set artist = @"test"    设置变量值
whatis                      查看变理的数据类型
   调试快捷键：
                  continue    :    option + command + P
                  step Into   :     shift + command + I
                  step Over :      shift + command + O
                  step Out   :      shift + command + T
  在Xcode中有两种运行程序的方法：Run->run  (快捷键：command + R)， 不用调试器运行程序；
                                       Run->Go(Debug)或者Run->Debug(快捷键：command+Y)，使用调试器运行程序。

1. 文件

CMD + N: 新文件
CMD + SHIFT + N: 新项目
CMD + O: 打开
CMD + S: 保存
CMD + SHIFT + S: 另存为
CMD + W: 关闭窗口
CMD + SHIFT + W: 关闭文件

2. 编辑

CMD + [: 左缩进
       CMD + ]: 右缩进

CMD + CTRL + LEFT: 折叠
CMD + CTRL + RIGHT: 取消折叠
CMD + CTRL + TOP: 折叠全部函数
CMD + CTRL + BOTTOM: 取消全部函数折叠
CTRL + U: 取消全部折叠

CMD + D: 添加书签
CMD + /: 注释或取消注释

CTRL + .: 参数提示
ESC: 自动提示列表

3. 调试

CMD + \: 设置或取消断点
CMD + OPT + \: 允许或禁用当前断点
CMD + OPT + B: 查看全部断点

CMD + RETURN: 编译并运行（根据设置决定是否启用断点）
CMD + R: 编译并运行（不触发断点）
CMD + Y: 编译并调试（触发断点）
CMD + SHIFT + RETURN: 终止运行或调试

CMD + B: 编译
CMD + SHIFT + K: 清理

4. 窗体

CMD + SHIFT + B: 编译窗口
CMD + SHIFT + Y: 调试代码窗口
CMD + SHIFT + R: 调试控制台
CMD + SHIFT + E: 主编辑窗口调整

5. 帮助

CMD + OPT + ?: 开发手册
CMD + CTRL + ?: 快速帮助
下面也是一些有用的快捷键(转自http://www.cppblog.com/brucejini/archive/2010/12/24/137367.html)
             
             Command + Shift + E ：扩展编辑器
             Command + [ ：左移代码块
                        Command + ] ：右移代码块
             Tab ：接受代码提示
             Esc ：显示代码提示菜单
             Ctrl + . （句点）：循环浏览代码提示
             Shift + Ctrl + . （句点）：反向循环浏览代码提示
             Ctrl + / ：移动到代码提示中的下一个占位符
             Command + Ctrl + S ：创建快照
             Ctrl + F ：前移光标
             Ctrl + B ：后移光标
             Ctrl + P ：移动光标到上一行
             Ctrl + N：移动光标到下一行
             Ctrl + A : 移动光标到本行行首
             Ctrl + E : 移动光标到本行行尾 --杨过注：这二个太有用了，刚开始用XCode，一直奇怪为啥Home与End键为啥不能直接定位到行首、行尾？
             Ctrl + T ：交换光标左右两边的字符
             Ctrl + D：删除光标右边的字符
             Ctrl + K ：删除本行
             Ctrl + L : 将插入点置于窗口正中
             Command + Alt + D：显示open quickly 窗口
             Command + Alt + 上方向键 ：打开配套文件
             Command + D ：添加书签
             Option + 双击：在文档中搜索
             Command + Y ：以调试方式运行程序
             Command + Alt + P ： 继续（在调试中）
             Command + Alt + 0 ：跳过
             Command + Alt + I ：跳入
             Command + Alt + T ：跳出
6,解决EXC_BAD_ACCESS错误的一种方法--NSZombieEnabled
http://blog.csdn.net/likendsl/article/details/7566305

 如何设置 NSZombieEnabled 呢，在 Xcode3 和 Xcode4 下设置不一样，Xcode4 下设置很简单。
 Xcode3 下 NSZombieEnabled 设置方法如下：
 
 1.   在XCode左边那个Groups& Files栏中找到Executables，双击其中的一项，或者右键Get Info；
 2.  切换到Arguments 
 3.  这里一共有两个框，在下面那个Variables to be set in theenvironment:点+号添加一项，Name里填NSZombieEnabled，Value填Yes，要保证前面的钩是选中的。
 
 Xcode4 下设置 NSZombieEnabled 的方法：
 
 你可以点击 Xcode4 菜单 Product -> Edit Scheme-> Arguments, 然后将点击”加号”, 将 NSZombieEnabled 参数加到Environment Variables 窗口中, 后面的数值写上 ”YES”.
 
 或者在 Xcode4 菜单 Product -> EditScheme -> Diagnostics 设置窗口中直接勾上Enable ZombieObjects 即可，Xcode 可用 cmd＋shift＋< 进到这个窗口。

最后提醒NSZombieEnabled只能在调试的时候使用，千万不要忘记在产品发布的时候去掉，因为NSZombieEnabled不会真正去释放dealloc对象的内存，一直开启后果可想而知，自重！

