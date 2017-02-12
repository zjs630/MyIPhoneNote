Ordered collection of objects.
Immutable. That’s right, once you create the array, you cannot add or remove objects.
All objects in the array are held onto strongly.

问题：10。对字符串排序
NSArray的使用。
1,创建数组，使用NSArray类。//添加到数组的对象的列表以nil结束。
	NSArray *myArray1 = [[NSArray alloc] initWithObjects:@"one",@"two",@"three",nil];
	NSArray *myArray1 = [NSArray arrayWithObjects:@"one",@"two",@"three",nil];
    NSArray *array = @[@"one", @"two"];//最新定义数组的语法
    NSArray * array = @[]; // 空数组 等价于 [NSArray array]
    id xx = @[@"a",@"b",@"c"][2]; //表示返回数组中的第2+1个对象（@"c"）；

2,从已有的数组创建一个数组.
	NSArray *myArray2 = [NSArray arrayWithArray:myArray1];
3,创建一个数组，它只包含一个已有数组的一部分：
	NSRange range = NSMakeRange(0, 2);
	NSArray *subArray = [myArray1 subarrayWithRange:range];
	for(NSString *bString in subArray)
		NSLog(@"%@",bString);
4,获取一个数组的长度
int arrayLength = [myArray1 count];
5,访问数组中特定位置的一个对象
NSString *myString = [myArray1 objectAtIndex:0];//如果数组中没有对象，that will raise an exception. that will crash. 
6,查看一个数组是否包含一个指定对象
BOOL isInArray = [myArray1 containsObject:@"one"];
7,得到一个对象在数组中的位置
	int index = [myArray1 indexOfObject:@"two"];
8,遍历一个数组中的值
	for(NSString *obj in myArray1){
		NSLog(@"%@",obj);
#if 0
        double value = [obj doubleValue];//crash here当obj不是NSString时。
#else
        // do something with obj, but make sure you don’t send it a message it does not respond to
        if ([obj isKindOfClass:[NSString class]]) {
            ￼// send NSString messages to obj with no worries
        }
#endif
	}

//xcode对于iOS4.0以上的系统，支持用block来遍历元素了。用block来遍历字典可以简化代码的编写，建议大家都使用上这个新特性。
  __block BOOL result = NO;
 [myArray1 enumerateObjectsUsingBlock:^(NSString *obj, NSUInteger idx, BOOL *stop) {
     NSString *mediaType = (NSString *)obj;
     if ([mediaType isEqualToString:paramMediaType]) {
         result = YES;
         *stop = YES;
     }
 }];

9,反向遍历一个数组的值
	for(NSString *bString in [myArray1 reverseObjectEnumerator])
	NSLog(@"%@",bString);
10,对字符串数组排序
NSArray *array = [NSArray arrayWithObjects:@"c",@"b", @"a",nil];
NSLog(@"%@",array);
NSArray *sortedArray = [array sortedArrayUsingSelector:@selector(caseInsensitiveCompare:)];
NSLog(@"%@",sortedArray);
11,对数组进行排序
NSArray *sorted = [myArray1 sortedArrayUsingSelector:@selector(compare:)];
12,把CGPoint放入数组的过程：
NSArray *array=[NSArray arrayWithObjects:NSStringFromCGPoint(0.0f,0.0f),NSStringFromCGPoint(0.0f,0.0f),nil];
从数组中取值的过程：
CGPoint point=CGPointFromNSString（[array objectAtIndex:2]）;
13,对字符串的截取操作。按照“|”实现分割，去掉后面的数字只要前面部分
NSString *s = @"哈根达斯,4223|帝王蟹,3717|三文鱼,3255|提拉米苏,2733|生蚝,1860|烤鳗,1451|生鱼片,1430|龙虾色拉,1252|北极贝,1230|鲍鱼片,772|芒果冰沙,730|烤鳗鱼,706|龙虾沙拉,692|海鲜泡饭,600|冰淇淋,508|芒果汁,499|鲍片,357|佛跳墙,308|鲍鱼,295|HGDS,262 ";
    NSMutableArray *array = [[s componentsSeparatedByString:@"|"]retain];
    NSMutableArray *mutablearray = [[NSMutableArray alloc] init];
    int i = 0;
    for(i; i<[array count]; i++)
    {
        NSString *s1 = [array objectAtIndex:i];
        NSArray *a = [s1 componentsSeparatedByString:@","];
        [mutablearray addObject:[a objectAtIndex:0]];
    }
    for(i =0 ; i<[mutablearray count]; i++)
    {
        NSLog([NSString stringWithFormat:@"%@",[mutablearray objectAtIndex:i]]);
    } 
14，让数组中的每一个对象执行一个方法。
-(void)makeObjectsPerformSelector:(SEL)aSelector;
//You give it a selector and it'll make all of the objects in the array perform that selector.
NSArray *fighters = ...;
[fighters makeObjectsPerformSelector:@selector(fly:)];
15.数组中的最后一个对象。
-(id)lastObject;//it returns nil if there are no objects in the array(convenient)
//last object is a good way to kind of get the object form the end of it.
16,数组元素的过滤
NSArray *array = [NSArray arrayWithObjects:@"asss jc",@"gg ajb", @"jja",nil];
NSLog(@"%@",array);
NSPredicate *apredicate = [NSPredicate predicateWithFormat:@"SELF beginswith[c] 'a'"];
//NSPredicate *apredicate = [NSPredicate predicateWithFormat:@"SELF contains[c] 'a'"];
//NSPredicate *apredicate = [NSPredicate predicateWithFormat:@"SELF like j*"];
NSArray *newArray = [array filteredArrayUsingPredicate:apredicate];
NSLog(@"%@",newArray);


//NSMutableArray inherits all of NSArray’s methods.
NSMutableArray的使用
1，创建可变数组
	NSMutableArray *myArray = [[NSMutableArray alloc] initWithObjects:@"one",@"two",@"three",nil];
2，在开始处添加一个对象
	[myArray insertObject:@"first" atIndex:0];
//可以用它来将对象添加到数组的中间。在原来位置的元素会依次向后移。
3.替换数组中特定位置的一个对象
	[myArray replaceObjectAtIndex:0 withObject:@"second"];
4,删除一个对象
	[myArray removeObject:@"second"];
5,删除特定位置的一个对象
	[myArray removeObjectAtIndex:0];//删除第一个对象
6,删除几个对象：
	NSRange range = NSMakeRange(0, 2);
	[myArray removeObjectsInRange:range];//删除前两个对象
7,删除数组中的所有对象
	[myArray removeAllObjects];
8,为可变数组赋空值
NSMutableArray tires = [[NSMutableArray alloc] init];
int i;
for(i=0;i<4;i++)
{
	[tires addObject:[NSNull null]];
}
9,往数组中添加对象
-(void)addObject:(id)anObject;
//That adds an object at the end of the array.它会使数组的长度增加，并且把对象添加到最后。

//////////////////////////////////////////////
//定义NSString类型的数组//在类外定义
static NSString *actionNames[] = {
	@"EaseIn",
	@"EaseOut",
	@"EaseInOut",
	@"EaseSineIn",
	@"EaseSineOut",
	@"Speed" };
1,确定数组中元素的个数
int actCount = sizeof(actionNames) / sizeof(actionNames[0]) ;
2,输出数组中的元素
for(int i=0; i<actCount; i++)
{
	NSString *aName = actionNames[i];
	NSLog(@"%@",aName);
}



