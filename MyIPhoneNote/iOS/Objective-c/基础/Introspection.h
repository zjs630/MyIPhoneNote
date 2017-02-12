1,在运行时，判断对象属于哪个类。或者判断什么方法可以发送给它。

所有的objects that inherit from NSObject。
     isKindOfClass:returns whether an object is that kind of class (inheritance included)
   isMemberOfClass:returns whether an object is that kind of class (no inheritance)
respondsToSelector:returns whether an object responds to a given method

2，判断一个类，是否是NSString类
if([obj isKindOfClass:[NSString class]]){
    NSLog(@"YES");
}
3,测试某个对象，响应某个方法，用selector（SEL）
if([obj respondsToSelector:@selector(shoot)]){
    [obj shoot];
}
else if ([obj respondsToSelector:@selector(shootAt:)]){
    [obj shootAt:target];
}

