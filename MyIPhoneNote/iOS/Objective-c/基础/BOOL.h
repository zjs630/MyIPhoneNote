1，BOOL 只能是YES或NO，如果是0，为NO，非零，为YES（负数也为yes）。
2，设置属性
@property(nonatomic) BOOL isYES;//这种类型的属性（primitive types），没有存储在heap中，不需要用strong或者weak修饰。
