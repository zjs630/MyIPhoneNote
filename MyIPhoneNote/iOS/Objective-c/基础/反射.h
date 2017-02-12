Objective-C 添加了反射（reflection）来扩展c，使用反射来创建对象。
//Without reflection
SomeClass *obj = [[SomeClass alloc] init];
[obj hello];

//With reflection
Class oneClass = NSClassFromString(@"SomeClass");
id obj = [[oneClass alloc] init];

SEL selector = NSSelectorFromString(@"hello");
[obj performSelector:selector withObject:nil];