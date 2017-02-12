NSAssert(条件, 错误提示);
不满足条件时，SIGABRT。

断言，  我断定这个地方一定会出问题，出问题时中断，以便修复这个问题。

NSAssert(x!=0,@"x must not be zero");
在表达式“x!=0”不成立时，程序就会抛出异常，并显示自定义的消息"x must not be zero"，
并同时显示出错的文件、代码和调用函数等信息，是一个程序追踪的很好手段。

The call to NSAssert is completely removed in Release builds.
//在最终的发 布版本中,NSAssert将被删除