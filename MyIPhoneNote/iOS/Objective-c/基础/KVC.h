KVC 键值编码的基本概念
1，键值编码是一个用于间接访问对象属性的机制，使用该机制不需要调用存取方法和变量实例就可以访问对象属性。私有的属性也可以访问。
2，键值编码方法在Objective-C非正式协议NSKeyValueCoding中被声明，默认的实现方法由NSObject提供。
3，键值编码支持带有对象值的属性，同时也支持纯数值类型和结构。非对象参数和返回类型会被识别并自动封装/解封。

KVC的基本用户

1，设置和访问
Book *book = [[Book alloc] init];
Author *author = [[Author alloc] init];
[author setValue:@"zjs" forKey:@"_name"];
[book setValue:author forKey:@"_author"];

//键值访问
[book setValue:@"ios book" forKey:@"name"]; //@"name" 为book对象的实例变量，即使是private也可以设置
[book ValueForKey:@"name"]; //取实例变量name的值

//路径访问,用“.”号隔开
[book setValue:@"tom" forKeyPath:@"author.name"];
[book ValueForKeyPath:@"author.name"];

//一对多的关系
如果向NSArray请求一个键值，它实际上会查询数组中的每个对象来找这个键值，然后将查询结果打包到一个新数组返回给你。
NSArray *booksArray = @[book1,book2];
NSArray *newArray = [booksArray ValueForKeyPath:@"name"];//两本书的书名放到数组中返回
2，对数值类型的变量，进行简单运算。 sum,min,max,avg,count
id sum = [booksArray ValueForKeyPath:@"@sum.price"];






Key-Value Coding（KVC）实现分析
KVC运用了一个isa-swizzling技术。isa-swizzling就是类型混合指针机制。KVC主要通过isa-swizzling，来实现其内部查找定位的。isa指针，如其名称所指，（就是is a kind of的意思），指向维护分发表的对象的类。该分发表实际上包含了指向实现类中的方法的指针，和其它数据。

比如说如下的一行KVC的代码：
[site setValue:@"sitename" forKey:@"name"];

就会被编译器处理成：

SEL sel = sel_get_uid ("setValue:forKey:");
IMP method = objc_msg_lookup (site->isa,sel);
method(site, sel, @"sitename", @"name");

首先介绍两个基本概念：

（1）SEL数据类型：它是编译器运行Objective-C里的方法的环境参数。
（2）IMP数据类型：他其实就是一个 编译器内部实现时候的函数指针。当Objective-C编译器去处理实现一个方法的时候，就会指向一个IMP对象，这个对象是C语言表述的类型。

关于如何找到实现函数的指针，可参考文章：《Objective-C如何避免动态绑定，而获得方法地址》：http://www.cocoadev.cn/Objective-C/Get-method-address.asp

这下KVC内部的实现就很清楚的清楚了：一个对象在调用setValue的时候，（1）首先根据方法名找到运行方法的时候所需要的环境参数。（2）他会从自己isa指针结合环境参数，找到具体的方法实现的接口。（3）再直接查找得来的具体的方法实现。






