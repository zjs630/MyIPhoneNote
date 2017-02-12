1,根据索引处理数组对象的时候，一次处理一个索引在有的时候会显得极为不便。如：［array objectAtIndex:0］;
如：处理列表的时候，用户可能一次选择多个列表，这个时候单索引处理就没法完成这一功能。
使用NSIndexSet或者NSMutableIndexSet用户可以创建索引集合，对数组对象进行批处理。

NSMutableArray *names = [NSMutableArray array];
[names addObject:@"zjs"];
[names addObject:@"Mary"];
[names addObject:@"Lili"];
[names addObject:@"sunmeng"];
NSLog(@"%@",names);

NSMutableIndexSet *indexSet=[NSMutableIndexSet indexSet];//创建索引列表
[indexSet addIndex:1];//添加索引1
[indexSet addIndex:3];//添加索引3

NSArray *loves = [names objectsAtIndexes:indexSet];//取出索引指定的对象
NSLog(@"%@",loves);

[names removeObjectsAtIndexes:indexSet];//删除索引指定的对象

NSLog(@"%@",names);

2.NSIndexSet是什么？

NSIndexSet  是个无符号整数集合。集合中的元素不可变的、不可重复。常被用来当作索引使用。就从它字面上理解，就叫做：索引集合。

3.NSIndexSet的一些常用方法。

类方法：

创建一个空的索引集合。
+ (id)indexSet

创建一个索引集合，根据索引值
+ (id)indexSetWithIndex:(NSUInteger)index

创建一个索引集合，根据一个NSRange对象
+ (id)indexSetWithIndexesInRange:(NSRange)indexRange


实例方法：

判断索引集合中是否包含制定的索引值
- (BOOL)containsIndex:(NSUInteger)index

判断索引集合是否包含指定的indexSet
- (BOOL)containsIndexes:(NSIndexSet *)indexSet

判断索引集合是否包含指定的indexRange
- (BOOL)containsIndexesInRange:(NSRange)indexRange

返回索引集合包含的索引数量
- (NSUInteger)count

返回indexRange中包含的索引数量
- (NSUInteger)countOfIndexesInRange:(NSRange)indexRange

枚举NSIndexSet；执行Block操作，在指定的Rang范围内，并使用指定的options方法。
- (void)enumerateIndexesInRange:(NSRange)range options:(NSEnumerationOptions)opts usingBlock:(void (^)(NSUInteger idx, BOOL *stop))block
如果，要枚举的NSIndexSet中不存在Rang中所指定的范围，则跳过。

options参数：
enum {
    NSEnumerationConcurrent = (1UL << 0),
    NSEnumerationReverse = (1UL << 1),
};
typedef NSUInteger NSEnumerationOptions;

NSEnumerationConcurrent
枚举过程中，各个Block是同时开始执行的。这样枚举的完成顺序是不确定的。

NSEnumerationReverse
以反序方式枚举。

例子：


// theTwo中是否包含theOne
BOOL isContains1= [theTwo containsIndexes:theOne];
BOOL isContains2= [theTwo containsIndex:1];
BOOL isContains3= [theTwo containsIndex:9];
// theTwo中是否包含指定的NSMakeRange
BOOL isContains4= [theTwo containsIndexesInRange:NSMakeRange(0,5)];
int theCount=[theTwo count];


// 遍历theTwo，在指定的Range范围内，执行Block方法，利用制定的options方式
// 如果，theTwo中不存在Range中所指定的范围，在theTwo中不存在，则跳过。
[theTwo enumerateIndexesInRange:NSMakeRange(0,8)
                        options:NSEnumerationReverse
                     usingBlock:^(NSUInteger idx, BOOL *stop) {
                         
                         NSLog(@"-------%d",idx);
                         NSLog(@"%@",theTwo);
                     }];