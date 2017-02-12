1,// http://www.cnbluebox.com/?p=255

循环引用retain cycle

循环引用指两个对象相互强引用了对方，即retain了对方，从而导致谁也释放不了谁的内存泄露问题。如声明一个delegate时一般用assign而不能用retain或strong，因为你一旦那么做了，很大可能引起循环引用。在以往的项目中，我几次用动态内存检查发现了循环引用导致的内存泄露。

这里讲的是block的循环引用问题，因为block在拷贝到堆上的时候，会retain其引用的外部变量，那么如果block中如果引用了他的宿主对象，那很有可能引起循环引用，如：

self.myblock = ^{
    
    [self doSomething];
};
为测试循环引用，写了些测试代码用于避免循环引用的方法，如下，（只有arc的，懒得做非arc测试了）


- (void)dealloc
{
    
    NSLog(@"no cycle retain");
}

- (id)init
{
    self = [super init];
    if (self) {
        
#if TestCycleRetainCase1
        
        //会循环引用
        self.myblock = ^{
            
            [self doSomething];
        };
#elif TestCycleRetainCase2
        
        //会循环引用
        __block TestCycleRetain *weakSelf = self;
        self.myblock = ^{
            
            [weakSelf doSomething];
        };
        
#elif TestCycleRetainCase3
        
        //不会循环引用
        __weak TestCycleRetain *weakSelf = self;
        self.myblock = ^{
            
            [weakSelf doSomething];
        };
        
#elif TestCycleRetainCase4
        
        //不会循环引用
        __unsafe_unretained TestCycleRetain *weakSelf = self;
        self.myblock = ^{
            
            [weakSelf doSomething];
        };
        
#endif
        
        NSLog(@"myblock is %@", self.myblock);
        
    }
    return self;
}

- (void)doSomething
{
    NSLog(@"do Something");
}

int main(int argc, char *argv[]) {
    @autoreleasepool {
        TestCycleRetain* obj = [[TestCycleRetain alloc] init];
        obj = nil;
        return 0;
    }
}
经过上面的测试发现，在加了__weak和__unsafe_unretained的变量引入后，TestCycleRetain方法可以正常执行dealloc方法，而不转换和用__block转换的变量都会引起循环引用。
因此防止循环引用的方法如下：
__unsafe_unretained TestCycleRetain *weakSelf = self;

