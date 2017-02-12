NSDictionary用来存储相关联的键-值对。字典是无序的。
像NSArray一样，NSDictionary是不可变的。
如果需要在创建之后能够修改内容的字典，
可以使用NSMutableDictionary类。

4.字典中的键通常是字符串对象，but not always.键的值则是
NSDictionary,NSArray,NSString,NSDate,NSData,NSNumber的实例。

通常，每个键-值对（叫做一个条目）
包含了用于键的一个NSString和用于值的一个NSObject。
一个字典中的键必须是唯一的，值不需要是唯一的。

dictionaries are basically a hash table. Look up objects using a key to get a value.

1.创建一个字典
	NSArray *arr1 = [NSArray arrayWithObjects:@"iPhone",@"iPad",nil];
	NSArray *arr2 = [NSArray arrayWithObjects:@"iMac",@"Mac Pro",@"Macbok",@"Macbook Pro",nil];
	NSDictionary *myDict = [[NSDictionary alloc] initWithObjectsAndKeys:arr1,@"mobile",arr2,@"computers",nil];
    NSDictionary * dict = @{@"key1":@"value1", @"key2":@"value2"};//最新定义字典的语法
    NSDictionary * dict = @{};            // 空的字典 等价于 [NSDictionary dictionary]
2.查看一个字典中有多少个元素
	int dictSize = [myDict count];
3,访问字典中的一个值
	NSArray *mobile = [myDict objectForKey:@"mobile"];
    NSArray *mobile = myDict[@"mobile"]; //最新的语法，很不错的

NSDictionary *dic = @{@"a": @{@"b": @"c"}};
NSLog(@"%@",[dic valueForKeyPath:@"a.b"]);//c

NSDictionary *dic = @{@"a": @{@"b": @[@"c",@"d"]}};
NSLog(@"%@",[dic valueForKeyPath:@"a.b"][0]);//c

4,从一个对象获取键
	NSArray *keys = [myDict allKeysForObject:arr1];
5,分别获取字典中的所有键和值
	NSArray *myAllKeys = [myDict allKeys];
	NSArray *myAllvalues = [myDict allValues];
6,像NSArray一样，枚举出所有的内容
	for (id key in myDict) {  
		NSLog(@"mkey: %@, value: %@", key,  
			  [myDict objectForKey:key]);  
	} 
7,如果字典只包含属性列表对象
（NSData, NSDate, NSNumber,NSString, NSArray或NSDictionary），
我们可以将其保存到一个文件中
	NSString *filePath = [[[NSBundle mainBundle] resourcePath]  
						  stringByAppendingPathComponent:@"dict.txt"];  
	BOOL success = [myDict writeToFile:filePath atomically:YES];  
8,可以用一个文件的内容来填充一个字典
	NSDictionary *myDict2 = [NSDictionary dictionaryWithContentsOfFile:filePath]; 
	
10,修改一个字典中已有的对象
	NSString *string2 = @"cccccccccccc"; 
	[myDict2 setObject:string2 forKey:@"media"];

12,删除多个对象
	NSArray *keyArray = [NSArray arrayWithObjects:@"mobile",@"computers",nil];  
	[myDict removeObjectsForKeys:keyArray]; 
13,删除字典的所有对象
[myDict removeAllObjects];
14,字典排序
NSArray *keys = [dict allKeys];

NSArray *sortedArray = [keys sortedArrayUsingSelector:@selector(caseInsensitiveCompare:)];
NSLog(@"%@",sortedArray);

NSString *path=[[NSBundle mainBundle] pathForResource:@"abc" ofType:@"plist"];
//从文件内容创建字典
NSDictionary *dict=[NSDictionary dictionaryWithContentsOfFile:path];

//从字典取出Key对应的Value
self.myname.text=[dict valueForKey:@"Name"];
NSLog(@"%@",[dict valueForKey:@"Name"]);
//改变Key对应的值
[dict setValue:@"Jimmy" forKey:@"Name"];
//将改变后的结果(字典)写入文件(filepath指定路径和文件名)
[dict writeToFile:filepath atomically:YES];

NSMutableDictionary
1,将对象添加到hash table中。//向一个可变的字典添加一个对象
-(void)setObject:(id)anObject forKey:(id)key;//put an object in the hash table.

NSString *string1 = @"AppleTV";  
[myDict2 setObject:string1 forKey:@"media"]; 

2，移除对象 //从字典中删除一个对象
-(void)removedObjectForKey:(id)key;
[myDict removeObjectForKey:@"media"]; 

3,将一个已经存在的字典添加到另一个字典中。//add more keys and values.
-(void)addEntriesFromDictionary:(NSDictionary *)otherDictionary;










	
	
	