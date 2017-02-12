1，plist文件用与存储一小部分的数据，
Arrays,dictionaries,strings,numbers,dates,raw data;
Human-readable XML or binary format
2,什么时候不用Property Lists
•More than a few hundred KB of data,Loading a property list is all-or-nothing
•Complex object graphs
•Custom object types（属性列表的一个缺点是无法将自定义对象序列化到属性列表中）。
3,读写Property Lists
• NSArray and NSDictionary convenience methods
// Writing 
- (BOOL)writeToFile:(NSString *)aPath atomically:(BOOL)flag; 
- (BOOL)writeToURL:(NSURL *)aURL atomically:(BOOL)flag;
// Reading 
- (id)initWithContentsOfFile:(NSString *)aPath; 
- (id)initWithContentsOfURL:(NSURL *)aURL;
//将数组保存到磁盘。注：运行代码后，plist文件保存在，项目根目录/build/Debug目录下。
	NSArray *array = [NSArray arrayWithObjects:@"Foo", [NSNumber numberWithBool:YES],[NSDate dateWithTimeIntervalSinceNow:60],nil]; 
	[array writeToFile:@"MyArray.plist" atomically:YES];//文件保存再根目录下。
//将字典保存到磁盘 Writing a Dictionary to Disk
	NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys: @"Name", @"Evan",
										@"Lecture", [NSNumber numberWithInt:9],nil]; 
	[dict writeToFile:@"MyDict.plist" atomically:YES];
4，NSData和property list相互转换。
// Property list to NSData 
+ (NSData *)dataFromPropertyList:(id)plist
format:(NSPropertyListFormat)format errorDescription:(NSString **)errorString;
// NSData to property list 
+ (id)propertyListFromData:(NSData *)data
mutabilityOption:(NSPropertyListMutabilityOptions)opt format:(NSPropertyListFormat *)format
errorDescription:(NSString **)errorString;
5,读取plist文件，存储到Dictionary。
//读取文件的路径
NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"MyDict" ofType:@"plist"];
//存储到Dictionary
NSDictionary *dictionary = [[NSDictionary alloc] initWithContentsOfFile:plistPath];
//do something then.
[dictionary release];



3.属性列表数据的读写

属性列表是一种数据表示形式，用于封装几种Foundation（及 Core Foundation）的数
据类型，包括字典、数组、字符串、日期、二进制数据、数值及布尔值。属性列表通常
用于存储结构化的配置数据。举例来说，每个Cocoa和iPhone应用程序中都有一个Info.
plist文件，它就是用于存储应用程序本身配置信息的属性列表。

将属性列表对象转换为NSData对象并写入存储代码：

- (BOOL)writeApplicationPlist:(id)plist toFile:(NSString *)fileName {
   NSString *error;
   NSData *pData = [NSPropertyListSerialization dataFromPropertyList:plist
format:NSPropertyListBinaryFormat_v1_0 errorDescription:&error];
   if (!pData) {
       NSLog(@"%@", error);
       return NO;
   }
   return ([self writeApplicationData:pData toFile:(NSString *)fileName]);
}

