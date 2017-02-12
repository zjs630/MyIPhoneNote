/*
 
 
 在printf函数中,符号%x可以显示十六进制格式的整型数。而对于NSLog函数，同样支持printf函数所有的格式和控制符号。而且它还可以支 持%@来打印一个对象。当使用%@时，给对象发送description消息，description方法返回一个字符串来代替%@。

符号                                 显示
%@                                 id
%d，%D，%i                          long
%u，%U                              unsigned long
%hi                                 short
%hu                                 unsigned short
%qi                                 long long
%qu                                 unsigned long long
%x，%X                              16进制打印unsigned long
%o，%O                              8进制打印 unsigned long
%f，%e，%E，%g，%G                   double
%c                                  unsigned char-ASCII 字符
%C                                  unichar-Unicode 字符
%s                                  char* （以空字符结束的ASCII字符组成的字符串）
%S                                  unichar* （以空字符结束的Unicode字符组成的字符串）
%p                                  void* （以0x开头的16进制的地址空间）
%%                                  A%字符

 NSLog的格式如下所示：
 %@ 对象
 %d, %i 整数
 %u 无符整形
 %f 浮点/双字
 %x, %X 二进制整数
 %o 八进制整数
 %zu size_t
 %p 指针
 %e 浮点/双字 （科学计算）
 %g 浮点/双字
 %s C 字符串
 %.*s Pascal字符串
 %c 字符
 %C unichar
 %lld 64位长整数（long long）
 %llu 无符64位长整数
 %Lf 64位双字