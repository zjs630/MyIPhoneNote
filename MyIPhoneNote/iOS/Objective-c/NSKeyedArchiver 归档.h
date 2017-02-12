1，归档是指用某种格式来保存一个或多个对象，以便以后还原这些对象的过程。
	通常这个过程包括将（多个）对象写入文件，以便以后读回该对象。
	常用的归档方法：属性列表和带键值的编码。
2，使用xml属性列表进行归档
a,将一个字典存储到文件中。
	NSDictionary *myDic = [NSDictionary dictionaryWithObjectsAndKeys:@"ZhangJIngshun",@"name1",@"LiSiban",@"name2",@"WangWu",@"name3",nil];
	[myDic writeToFile:@"plist" atomically:YES];
b,读取字典的归档文件
	NSDictionary *myDic2 = [NSDictionary dictionaryWithContentsOfFile:@"plist"];
	for(NSString *key in myDic2)
	{
		NSLog(@"key: %@ value: %@",key,[myDic2 objectForKey:key]);
	}
3,使用NSKeyedArchiver归档。将各种类型的文件存储到文件中。
a,将一个字典通过归档的方式写入文件中。
[NSKeyedArchiver archiveRootObject:myDic toFile:@"myDic.archive"];
b,读取归档的文件。
	NSDictionary *myDic2 = [NSKeyedUnarchiver unarchiveObjectWithFile:@"myDic.archive"];
	for(NSString *key in myDic2)
	{
		NSLog(@"key: %@ value: %@",key,[myDic2 objectForKey:key]);
	}



//=============================


2. NSCoding协议声明的两个方法

1.将对象编码到归档中
-(void) encodeWithCoder:(NSCoder *)encoder {
	
	[encoder encodeObject:foo forKey: kFooKey];
	[encoder encodeObject:bar forkey: kFooKey];
	[encoder encodeInt:someInt forKey: kSomeIntKey];
}



2.对象归档

2.1 对归档解码来创建一个新对象
-(void) initWithCoder:(NSCoder *) decoder {
	
	if (self = [super init ]) {
		self.foo = [decoder decodeObjectForKey:kFooKey];
		self.bar = [decoder decodeObjectForKey: kBarKey];
		self.someInt = [decoder decodeObjectForKey: kSomeIntKey];
	}
	return self;
}


2.2. 实现NSCopying

//复制对象的方法,对象被隐形保留,并没被释放出
-(id)copyWithZone:(NSZone *)zone {
	MyClass *copy = [[[self class] allocWithZone:zone] init];
	copy.foo = [self.foo copyWithZone:zone];
	copy.bar = [self.bar copyWithZone:zone];
	copy.someInt = self.someInt;
	
	return copy;
}

//以上的三个方法后,我们创建的对象数据都可以进行归档了.

//这时候,程序将终止时的方法可改成
-(void) applicationWillTerminate:(NSNotification *) notification {
	
	MyClass *myClass = [[MyClass alloc] init];
	
	myClass.field1 = field1.text;
	myClass.field2 = field2.text;
	
	NSMutableArray *data = [[NSMutableArray alloc] init ];
	NSKeyedArchiver *archiver = [[NSKeyedArchiver alloc] initForWritingWithMutableData:data];
	
	[archiver encodeObject: myClass forKey: kDataKey];
	[archiver finishEncoding];
    
	[data writeToFile:[self dataFilePath] atomically: YES];
}














