1，XCode4.0以后，编译器换成了LLVM 编译器 2.0

与以前相比，更加强大：
1.LLVM 编译器是下一带开源的编译技术.完全支持C, Objective-C, 和 C++.
2.LLVM 速度比 GCC快两倍,建立的程序也会运行的更快. 因为它更好的利用现代的芯片的结构.
3.LLVM和Xcode 4完全的整合在一起.包括关键字高亮,代码完整性等全都是由LLVM语法分析器来分析的. 这样可以在编辑的时候就可以很好的了解你的代码.


编译器进化之后，控制台调试命令前缀，也由原来的gdb更改成了lldb，所以当你看到控制台没有gdb而出现lldb的时候，不用惊慌，因为我们以前常用的调试命令依然可以使用：

使用前提：

1.既然是调试命令，理所当然的，程序模式应该选择Debug模式。

2.在Debug模式下，如果你的程序在运行中崩溃（Crash）掉，那么恭喜你，使用lldb调试的机会来了。

符合以上两个条件之后，控制台（即日志输出窗口All Output）会自动打出一个（lldb）命令，你在其后输入bt，回车。

恭喜你，这时Xcode会自动输出最后的一次调用堆栈。


2,如何解决奔溃问题-深入调试
如果你运行这个模拟器，你可以（lldb）提示符后键入以下内容：
(lldb) po $eax
（顺便说一下，你可以切换在Xcode编辑器之间的不同调试，可以通过project schema编辑选项，选择debugger，切换采用gdb或lldb)

po命令代表“打印对象” print object（会不会让你想起.net clr debug中的 ！do !pe=print exception）。符号$ EAX是指CPU寄存器之一。在异常的情况下，该寄存器将包含一个指针的NSException对象。注：$EAX只适用于模拟器，如果你在调试设备，你需要使用寄存器$ R0。
例如，如果键入：
(lldb) po [$eax class]
你也可以看到如下的输出
(id) $2 = 0x01446e84 NSException
数字并不重要，但很明显，你在这里处理与NSException对象。
你可以调用这个对象的任何从NSException方法。例如：
(lldb) po [$eax name]
这会给你异常的名称，在这种情况下NSInvalidArgumentException，
(lldb) po [$eax reason]
这会给你 error message:
(unsigned int) $4 = 114784400 Receiver (<MainViewController: 0x6b60620>) has no
segue with identifier 'ModalSegue'
Note: When you just do “po $eax”, it will call the “description” method on the object and print that, which in this case also gives you the error message.


3, Xcode4 下设置 NSZombieEnabled 的方法：
 
 你可以点击 Xcode4 菜单 Product -> Edit Scheme-> Arguments, 然后将点击”加号”, 将 NSZombieEnabled 参数加到Environment Variables 窗口中, 后面的数值写上 ”YES”.
 
 或者在 Xcode4 菜单 Product -> EditScheme -> Diagnostics 设置窗口中直接勾上Enable ZombieObjects 即可，Xcode 可用 cmd＋shift＋< 进到这个窗口。

最后提醒NSZombieEnabled只能在调试的时候使用，千万不要忘记在产品发布的时候去掉，因为NSZombieEnabled不会真正去释放dealloc对象的内存，一直开启后果可想而知，自重！

