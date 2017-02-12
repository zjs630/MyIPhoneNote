有问题的代码：7

1，创建一个NSString,最简单的方法。
	NSString *myString=@"some string"; 
	功能上等同于
	NSString *myString = [[NSString alloc] initWithString:@"some string"];
	//注NSString 类型的字符串，没有采用引用技术机制，所以不需要release来释放内存。
2，创建一个格式化的字符串
	NSString *myString = [NSString stringWithFormat:@"object = %@",someObject]; 
	//%d用来表示整数，%f表示双精度浮点数，%c表示单个字符，%s表示一个字符串，而%@表示对象
3,若拥有的字符串只包含数字，类型转换。
	NSString *myString = @"123456";
	double doubleString = [myString doubleValue];
	float floatString = [myString floatValue];
	int intString = [myString intValue];
	//对于一个字符串"123abc"，intValue方法将返回123。
4,获取一个字符串的长度
	int stringLength = [myString length];
5,比较两个字符串是否相同
	BOOL areEqual = [string1 isEqualToString:string2];
//判断一个字符串是否为空，可用4，5函数判断。
if([str length]>0){}
if([str isEqualToString:@"text"]){}
6，转换字符串大小写
	NSString *myString = @"abcABC";
	NSString *upper = [myString uppercaseString];
	NSString *lower = [myString lowercaseString];
7,截去一个字符串中不需要的字符。例如，要从一个字符串中删除前后的空白
	NSString *myString = @"  one two three   ";  
	NSLog(@"［%@］",myString);
	NSString *trimmed=[myString stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]]; 
	NSLog(@"［%@］",trimmed);
//使用NSString *strUrl = [urlString stringByReplacingOccurrencesOfString:@" " withString:@""];可以去掉所有空格
8，通过一个已有的字符串创建子字符串，即字符串截取。
	NSString *numberString = @"one1two2three";
	//截取前三个字母one。从开始到给定的索引位置
	NSString *aString = [numberString substringToIndex:3];
	//根据位置和长度截取字符串。截取中间的字符串two,
	NSRange range = NSMakeRange(4, 3);//第5个开始取3个字符
	NSString *bString = [numberString substringWithRange:range];
	//截取最后一个单词three //从指定位置直到结尾的字符串。
	NSString *cString = [numberString substringFromIndex:8];
						
9，在一个字符串中查找一个子字符串，返回NSRange//子字符串第一次出现的位置和长度。
	NSRange foundRange = [numberString rangeOfString:@"two"]; 
10,判断一个字符串是否包含一个子字符串：
BOOL found = ([numberString rangeOfString:@"two"].location != NSNotFound);
//return YES,表明包含字符串。
11，组合字符串：
	NSString *string1 = @"one two three";
	NSString *string2 = [string1 stringByAppendingString:@" four"];
12,把一个文件的内容读入到一个字符串中.//注：文件存放在build/Debug目录下
	NSString *fileContents = [NSString stringWithContentsOfFile:@"a.txt"];
	NSLog(@"%@",fileContents);
13,获取一个文件的文件扩展名：
	NSString *fileName = @"myfile.txt";
	NSString *fileExtension = [fileName pathExtension];
	NSLog(@"fileExtension: %@",fileExtension);
	//结果是 fileExtension: txt
14,把一个URL的内容读入到字符串中
	NSURL *url = [NSURL URLWithString:@"www.baidu.com"];
	NSString pageContents = [NSString stringWithContentsOfURL:url];
15，将一个NSString的字符串变为c字符串。
	char *stringPath = [string1 UTF8String];
	或
	char *stringPath = [string1 CString];
    //char *ptr = [string1 cStringUsingEncoding:NSASCIIStringEncoding];
16,将一个c的字符串变为NSString字符串
	char *rowData = 'abc';
	NSString *fieldValue = [[NSString alloc] initWithUTF8String:rowData];
17,格式化字符串的格式符：
	％@，表示对象；%d or %i 带符号的十进制数；%f 表示浮点数；%o 不带符号的8进制数；％s 表示字符串；％u表示不带符号的十进制数；％x 不带符号的十六进制数。
18,向一个字符串中追加字符串。
	//其实是在内存新建了一个存放字符串的空间。原字符串中的内容没有改变，改变的是字符串变量对地址空间的引用。
	int i=5;
	myString = [myString stringByAppendingFormat:@"%d",i];
19,将字符串转化为数组
NSArray *keys = [@"", componentsSepara];
19，操作文件
NSString *path = @"~/learning/file.m";
NSString *myPath = [path stringByStandardizingPath];//将"~/"解析为真实的路径
[myPath lastPathcomponent];//返回文件名:file.m
[myPath pathExtension];//放回扩展名m.
20,字符替换//将空格替换为加号
[urlString stringByReplacingOccurrencesOfString:@" " withString:@"+"]
21,字符串行数统计
NSString *string = @"第一行\n第二行\n第三行";
NSInteger length = [[string componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]] count];
22,判断是否以某个字符串开头
［oneString hasPrefix:@"one"];
23，将一个坐标大小字符串，转换为CGRect类型。//如"5,6,10,10"

-(CGRect)convertFromString:(NSString*)stringValue{
	NSArray *rectArray = [stringValue componentsSeparatedByString:@","];
	if ([rectArray count] == 4) {
		double x = [[rectArray objectAtIndex:0] doubleValue];
		double y = [[rectArray objectAtIndex:1] doubleValue];
		double width = [[rectArray objectAtIndex:2] doubleValue];
		double height = [[rectArray objectAtIndex:3] doubleValue];
		return CGRectMake(x, y, width, height);
	}
	return CGRectMake(0, 0, 0, 0);
}
24,//将字母转换为对应的ASCII码
NSString *yuePu = @"abcdef";
NSRange range;
for (int j=0; j<[yuePu length]; j++) {
	range = NSMakeRange(j, 1);
	int qiu = *[[yuePu substringWithRange:range] UTF8String]; //;//[ 转换为数字或对应的ASCII码];
	NSLog(@"%i=%i",j,qiu);
}
25,将c字符数组转换为NSString对象
char myBottles[] = "my name is zhang jingshun!";
NSString *myName = [NSString stringWithCString:myBottles];
//NSString *name = [[NSString alloc] initWithCString:(const char*)encode_buf encoding:NSASCIIStringEncoding];
将NSString转换为char*的代码：
NSString *blankText = @"my string";
char *ptr = [blankText cStringUsingEncoding:NSASCIIStringEncoding];

26,将网页源代码保存到字符串中
NSURL *url = [NSURL URLWithString:@"http://www.lw521.net"];
NSString *pageData = [NSString stringWithContentsOfURL:url];
27,按行读取文件
NSArray *lines = [[NSString stringWithContentsOfFile:@"test.txt"] componentsSeparatedByString:@"\n"];
NSEnumerator *nse = [lines objectEnumerator];
while(tmp =[nes nextO])
28，判断是否是数字
-(BOOL)isZipCode:(NSString *)zip{
    int value;
    BOOL isZip = YES;
    for (int i=0; i<[zip length]; i++) {
        NSRange range = NSMakeRange(i, 1);
        value =*[[zip substringWithRange:range] UTF8String];
        if (value<48 ||value > 57) {
            isZip = NO;
            break;
        }
        NSLog(@"%d",value);
    }
    return isZip;
}
30,字符串内部换行
NSString *str = @"123\
                456\
                789";
在每行的末尾加"\"

1,创建一个可变字符串
	NSMutableString *song = [[NSMutableString alloc] init];
2,向给定字符串中添加字符串。
	[song appendString:@"ZhangabcJingshun"];
3,将abc替换为空格，首先获取“abc”子串的范围,然后替换字符。
	NSRange range = [song rangeOfString:@"abc"];
	[song replaceCharactersInRange:range withString:" "];
4，在起始位置插入字符。
	[song insertString:@"My name is "];



15、计算字符串的字数
-(int)calculateTextNumber:(NSString *)text
{
	float number = 0.0;
	int index = 0;
	for (index; index < [text length]; index++)
	{
		NSString *protoText = [text substringToIndex:[text length] - index];
		NSString *toChangetext = [text substringToIndex:[text length] -1 -index];
		NSString *charater;
		if([toChangetext length]==0)
		{
			charater = protoText;
		}
		else
		{
			NSRange range = [text rangeOfString:toChangetext];
			charater = [protoText stringByReplacingCharactersInRange:range withString:@""];
		}
		NSLog(charater);
		if([charater lengthOfBytesUsingEncoding:NSUTF8StringEncoding] == 3)
		{
			number++;
		}
		else
		{
			number = number+0.5;
		}
	}
	return ceil(number);
}

//=================================================================================================================================

//

28 分字符串 

NSString *str = @"中国人";
NSLog(str);
NSRange range = {
    0,1
};
for(int i = 0; i<[str length]; i++)
{
    range.location = i;
    NSLog(@"%@",[str substringWithRange:range]);
}

输出结果：
2010-09-28 22:43:09.379 TestTT[946:207] 中国人
2010-09-28 22:43:09.381 TestTT[946:207] 中
2010-09-28 22:43:09.382 TestTT[946:207] 国
2010-09-28 22:43:09.382 TestTT[946:207] 人


*******************************************************************************************
NSString
*******************************************************************************************/
//一、NSString 的一些API


/*----------------创建字符串的方法----------------*/
 
//1、创建常量字符串。
NSString *astring = @"This is a String!";
 
 
//2、创建空字符串，给予赋值。
 
NSString *astring = [[NSString alloc] init];
astring = @"This is a String!";
[astring release];
NSLog(@"astring:%@",astring);
 
 
 
//3、在以上方法中，提升速度:initWithString方法
 
NSString *astring = [[NSString alloc] initWithString:@"This is a String!"];
NSLog(@"astring:%@",astring);
[astring release];
 
 
 
//4、用标准c创建字符串:initWithCString方法
 
char *Cstring = "This is a String!";
NSString *astring = [[NSString alloc] initWithCString:Cstring];
NSLog(@"astring:%@",astring);
[astring release];
 
 
 
//5、创建格式化字符串:占位符（由一个%加一个字符组成）
 
int i = 1;
int j = 2;
NSString *astring = [[NSString alloc] initWithString:[NSString stringWithFormat:@"%d.This is %i string!",i,j]];
NSLog(@"astring:%@",astring);
[astring release];
 
 
 
//6、创建临时字符串
 
NSString *astring;
astring = [NSString stringWithCString:"This is a temporary string"];
NSLog(@"astring:%@",astring);
 
 
 
 
/*----------------从文件读取字符串:initWithContentsOfFile方法----------------*/    
 
NSString *path = @"astring.text";
NSString *astring = [[NSString alloc] initWithContentsOfFile:path];
NSLog(@"astring:%@",astring);
[astring release];
 
 
/*----------------写字符串到文件:writeToFile方法----------------*/    
 
 
NSString *astring = [[NSString alloc] initWithString:@"This is a String!"];
NSLog(@"astring:%@",astring);
NSString *path = @"astring.text";    
[astring writeToFile: path atomically: YES];
[astring release];    
 
 
 
 
/*----------------比较两个字符串----------------*/        
 
//用C比较:strcmp函数
 
char string1[] = "string!";
char string2[] = "string!";
if(strcmp(string1, string2) = = 0)
{
	NSLog(@"1");
}
 
 
 
//isEqualToString方法    
NSString *astring01 = @"This is a String!";
NSString *astring02 = @"This is a String!";
BOOL result = [astring01 isEqualToString:astring02];
NSLog(@"result:%d",result);
 
 
 
 
//compare方法(comparer返回的三种值)    
NSString *astring01 = @"This is a String!";
NSString *astring02 = @"This is a String!";    
BOOL result = [astring01 compare:astring02] = = NSOrderedSame;    
NSLog(@"result:%d",result);    
//NSOrderedSame判断两者内容是否相同
 
 
 
 
NSString *astring01 = @"This is a String!";
NSString *astring02 = @"this is a String!";
BOOL result = [astring01 compare:astring02] = = NSOrderedAscending;    
NSLog(@"result:%d",result);
//NSOrderedAscending判断两对象值的大小(按字母顺序进行比较，astring02大于astring01为真)
 
 
 
NSString *astring01 = @"this is a String!";
NSString *astring02 = @"This is a String!";
BOOL result = [astring01 compare:astring02] = = NSOrderedDescending;    
NSLog(@"result:%d",result);     
//NSOrderedDescending判断两对象值的大小(按字母顺序进行比较，astring02小于astring01为真)
 
 
 
//不考虑大小写比较字符串1
NSString *astring01 = @"this is a String!";
NSString *astring02 = @"This is a String!";
BOOL result = [astring01 caseInsensitiveCompare:astring02] = = NSOrderedSame;    
NSLog(@"result:%d",result);     
//NSOrderedDescending判断两对象值的大小(按字母顺序进行比较，astring02小于astring01为真)
 
 
 
//不考虑大小写比较字符串2
NSString *astring01 = @"this is a String!";
NSString *astring02 = @"This is a String!";
BOOL result = [astring01 compare:astring02
						 options:NSCaseInsensitiveSearch | NSNumericSearch] = = NSOrderedSame;    
NSLog(@"result:%d",result);     
 
//NSCaseInsensitiveSearch:不区分大小写比较 NSLiteralSearch:进行完全比较，区分大小写 NSNumericSearch:比较字符串的字符个数，而不是字符值。
 
 
/*----------------改变字符串的大小写----------------*/    
 
NSString *string1 = @"A String"; 
NSString *string2 = @"String"; 
NSLog(@"string1:%@",[string1 uppercaseString]);//大写
NSLog(@"string2:%@",[string2 lowercaseString]);//小写
NSLog(@"string2:%@",[string2 capitalizedString]);//首字母大小
 
 
/*----------------在串中搜索子串----------------*/        
 
NSString *string1 = @"This is a string";
NSString *string2 = @"string";
NSRange range = [string1 rangeOfString:string2];
int location = range.location;
int leight = range.length;
NSString *astring = [[NSString alloc] initWithString:[NSString stringWithFormat:@"Location:%i,Leight:%i",location,leight]];
NSLog(@"astring:%@",astring);
[astring release];
 
 
/*----------------抽取子串 ----------------*/        
 
//-substringToIndex: 从字符串的开头一直截取到指定的位置，但不包括该位置的字符
NSString *string1 = @"This is a string";
NSString *string2 = [string1 substringToIndex:3];
NSLog(@"string2:%@",string2);
 
 
 
 
//-substringFromIndex: 以指定位置开始（包括指定位置的字符），并包括之后的全部字符
NSString *string1 = @"This is a string";
NSString *string2 = [string1 substringFromIndex:3];
NSLog(@"string2:%@",string2);
 
 
 
 
//-substringWithRange: //按照所给出的位置，长度，任意地从字符串中截取子串
NSString *string1 = @"This is a string";
NSString *string2 = [string1 substringWithRange:NSMakeRange(0, 4)];
NSLog(@"string2:%@",string2);
 
 
//扩展路径
 
NSString *Path = @"~/NSData.txt";
NSString *absolutePath = [Path stringByExpandingTildeInPath];
NSLog(@"absolutePath:%@",absolutePath);
NSLog(@"Path:%@",[absolutePath stringByAbbreviatingWithTildeInPath]);
 
 
 
//文件扩展名
NSString *Path = @"~/NSData.txt";
NSLog(@"Extension:%@",[Path pathExtension]);
 
 
 
 
/*******************************************************************************************
 NSMutableString
 *******************************************************************************************/    
 
/*---------------给字符串分配容量----------------*/
//stringWithCapacity:
NSMutableString *String;
String = [NSMutableString stringWithCapacity:40];
 
 
/*---------------在已有字符串后面添加字符----------------*/    
 
//appendString: and appendFormat:
 
NSMutableString *String1 = [[NSMutableString alloc] initWithString:@"This is a NSMutableString"];
//[String1 appendString:@", I will be adding some character"];
[String1 appendFormat:[NSString stringWithFormat:@", I will be adding some character"]];
NSLog(@"String1:%@",String1);
*/
 
 
/*--------在已有字符串中按照所给出范围和长度删除字符------*/    
/*
 //deleteCharactersInRange:
 NSMutableString *String1 = [[NSMutableString alloc] initWithString:@"This is a NSMutableString"];
 [String1 deleteCharactersInRange:NSMakeRange(0, 5)];
 NSLog(@"String1:%@",String1);
  
  
  
 /*--------在已有字符串后面在所指定的位置中插入给出的字符串------*/
 
//-insertString: atIndex:
NSMutableString *String1 = [[NSMutableString alloc] initWithString:@"This is a NSMutableString"];
[String1 insertString:@"Hi! " atIndex:0];
NSLog(@"String1:%@",String1);
 
 
 
/*--------将已有的空符串换成其它的字符串------*/
 
//-setString:
NSMutableString *String1 = [[NSMutableString alloc] initWithString:@"This is a NSMutableString"];
[String1 setString:@"Hello Word!"];
NSLog(@"String1:%@",String1);
 
 
 
/*--------按照所给出的范围，和字符串替换的原有的字符------*/
 
//-setString:
NSMutableString *String1 = [[NSMutableString alloc] initWithString:@"This is a NSMutableString"];
[String1 replaceCharactersInRange:NSMakeRange(0, 4) withString:@"That"];
NSLog(@"String1:%@",String1);
 
 
 
/*-------------判断字符串内是否还包含别的字符串(前缀，后缀)-------------*/
//01：检查字符串是否以另一个字符串开头- (BOOL) hasPrefix: (NSString *) aString;
NSString *String1 = @"NSStringInformation.txt";
[String1 hasPrefix:@"NSString"] = = 1 ?  NSLog(@"YES") : NSLog(@"NO");
[String1 hasSuffix:@".txt"] = = 1 ?  NSLog(@"YES") : NSLog(@"NO");
 
//02：查找字符串某处是否包含其它字符串 - (NSRange) rangeOfString: (NSString *) aString，这一点前面在串中搜索子串用到过;
 
 
 
/*******************************************************************************************
 NSArray
 *******************************************************************************************/
 
/*---------------------------创建数组------------------------------*/
//NSArray *array = [[NSArray alloc] initWithObjects:
@"One",@"Two",@"Three",@"Four",nil];
 
self.dataArray = array;
[array release];
 
//- (unsigned) Count;数组所包含对象个数；
NSLog(@"self.dataArray cound:%d",[self.dataArray count]);
 
//- (id) objectAtIndex: (unsigned int) index;获取指定索引处的对象;
NSLog(@"self.dataArray cound 2:%@",[self.dataArray objectAtIndex:2]);
 
 
/*--------------------------从一个数组拷贝数据到另一数组(可变数级)----------------------------*/    
 
//arrayWithArray:
//NSArray *array1 = [[NSArray alloc] init];
NSMutableArray *MutableArray = [[NSMutableArray alloc] init];
NSArray *array = [NSArray arrayWithObjects:
				  @"a",@"b",@"c",nil];
NSLog(@"array:%@",array);
MutableArray = [NSMutableArray arrayWithArray:array];
NSLog(@"MutableArray:%@",MutableArray);
 
array1 = [NSArray arrayWithArray:array];
NSLog(@"array1:%@",array1);

//Copy

//id obj;
NSMutableArray *newArray = [[NSMutableArray alloc] init];
NSArray *oldArray = [NSArray arrayWithObjects:
					 @"a",@"b",@"c",@"d",@"e",@"f",@"g",@"h",nil];

NSLog(@"oldArray:%@",oldArray);
for(int i = 0; i < [oldArray count]; i++)
{        
	obj = [[oldArray objectAtIndex:i] copy];
	[newArray addObject: obj];
}
//     
NSLog(@"newArray:%@", newArray);
[newArray release];
 
 
//快速枚举
 
//NSMutableArray *newArray = [[NSMutableArray alloc] init];
NSArray *oldArray = [NSArray arrayWithObjects:
					 @"a",@"b",@"c",@"d",@"e",@"f",@"g",@"h",nil];    
NSLog(@"oldArray:%@",oldArray);
 
for(id obj in oldArray)
{
	[newArray addObject: obj];
}
//     
NSLog(@"newArray:%@", newArray);
[newArray release];    
 
 
//Deep copy
 
//NSMutableArray *newArray = [[NSMutableArray alloc] init];
NSArray *oldArray = [NSArray arrayWithObjects:
					 @"a",@"b",@"c",@"d",@"e",@"f",@"g",@"h",nil];    
NSLog(@"oldArray:%@",oldArray);    
newArray = (NSMutableArray*)CFPropertyListCreateDeepCopy(kCFAllocatorDefault, (CFPropertyListRef)oldArray, kCFPropertyListMutableContainers);
NSLog(@"newArray:%@", newArray);
[newArray release];    
 
 
//Copy and sort
 
//NSMutableArray *newArray = [[NSMutableArray alloc] init];
NSArray *oldArray = [NSArray arrayWithObjects:
					 @"b",@"a",@"e",@"d",@"c",@"f",@"h",@"g",nil];    
NSLog(@"oldArray:%@",oldArray);
NSEnumerator *enumerator;
enumerator = [oldArray objectEnumerator];
id obj;
while(obj = [enumerator nextObject])
{
	[newArray addObject: obj];
}
[newArray sortUsingSelector:@selector(compare:)];
NSLog(@"newArray:%@", newArray);
[newArray release];


/*---------------------------切分数组------------------------------*/
 
//从字符串分割到数组－ componentsSeparatedByString:
NSString *string = [[NSString alloc] initWithString:@"One,Two,Three,Four"];
NSLog(@"string:%@",string);    
NSArray *array = [string componentsSeparatedByString:@","];
NSLog(@"array:%@",array);
[string release];
 
 
//从数组合并元素到字符串- componentsJoinedByString:
NSArray *array = [[NSArray alloc] initWithObjects:@"One",@"Two",@"Three",@"Four",nil];
NSString *string = [array componentsJoinedByString:@","];
NSLog(@"string:%@",string);
 
 
 
/*******************************************************************************************
 NSMutableArray
 *******************************************************************************************/
/*---------------给数组分配容量----------------*/
//NSArray *array;
array = [NSMutableArray arrayWithCapacity:20];
 
 
 
/*--------------在数组末尾添加对象----------------*/
//- (void) addObject: (id) anObject;
//NSMutableArray *array = [NSMutableArray arrayWithObjects:
@"One",@"Two",@"Three",nil];
[array addObject:@"Four"];
NSLog(@"array:%@",array);
 
 
 
/*--------------删除数组中指定索引处对象----------------*/    
//-(void) removeObjectAtIndex: (unsigned) index;    
//NSMutableArray *array = [NSMutableArray arrayWithObjects:
@"One",@"Two",@"Three",nil];
[array removeObjectAtIndex:1];
NSLog(@"array:%@",array);
 
 
 
/*-------------数组枚举---------------*/    
//- (NSEnumerator *)objectEnumerator;从前向后
//NSMutableArray *array = [NSMutableArray arrayWithObjects:
@"One",@"Two",@"Three",nil];
NSEnumerator *enumerator;
enumerator = [array objectEnumerator];
 
id thingie;
while (thingie = [enumerator nextObject]) {
	NSLog(@"thingie:%@",thingie);
}
 
 
//- (NSEnumerator *)reverseObjectEnumerator;从后向前
//NSMutableArray *array = [NSMutableArray arrayWithObjects:
@"One",@"Two",@"Three",nil];
NSEnumerator *enumerator;
enumerator = [array reverseObjectEnumerator];
 
id object;
while (object = [enumerator nextObject]) {
	NSLog(@"object:%@",object);
}
 
 
//快速枚举
//NSMutableArray *array = [NSMutableArray arrayWithObjects:
@"One",@"Two",@"Three",nil];
for(NSString *string in array)
{
	NSLog(@"string:%@",string);
}
 
 
 
/*******************************************************************************************
 NSDictionary
 *******************************************************************************************/
 
/*------------------------------------创建字典------------------------------------*/
//- (id) initWithObjectsAndKeys;
 
//NSDictionary *dictionary = [[NSDictionary alloc] initWithObjectsAndKeys:@"One",@"1",@"Two",@"2",@"Three",@"3",nil];
NSString *string = [dictionary objectForKey:@"One"];
NSLog(@"string:%@",string);
NSLog(@"dictionary:%@",dictionary);
[dictionary release];
 
 
/*******************************************************************************************
 NSMutableDictionary
 *******************************************************************************************/
 
/*------------------------------------创建可变字典------------------------------------*/    
//创建
NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
 
//添加字典
[dictionary setObject:@"One" forKey:@"1"];
[dictionary setObject:@"Two" forKey:@"2"];
[dictionary setObject:@"Three" forKey:@"3"];
[dictionary setObject:@"Four" forKey:@"4"];
NSLog(@"dictionary:%@",dictionary);
 
//删除指定的字典
[dictionary removeObjectForKey:@"3"];
NSLog(@"dictionary:%@",dictionary);
 
 
/*******************************************************************************************
 NSValue（对任何对象进行包装）
 *******************************************************************************************/
 
/*--------------------------------将NSRect放入NSArray中------------------------------------*/    
//将NSRect放入NSArray中
NSMutableArray *array = [[NSMutableArray alloc] init];
NSValue *value;
CGRect rect = CGRectMake(0, 0, 320, 480);    
value = [NSValue valueWithBytes:&rect objCType:@encode(CGRect)];
[array addObject:value];
NSLog(@"array:%@",array);
 
//从Array中提取
value = [array objectAtIndex:0];
[value getValue:&rect];
NSLog(@"value:%@",value);
 
 
/*******************************************************************************************
 从目录搜索扩展名为jpg的文件
 *******************************************************************************************/
 
//NSFileManager *fileManager = [NSFileManager defaultManager];
NSString *home;
home = @"../Users/";
 
NSDirectoryEnumerator *direnum;
direnum = [fileManager enumeratorAtPath: home];
 
NSMutableArray *files = [[NSMutableArray alloc] init];
 
//枚举
NSString *filename;
while (filename = [direnum nextObject]) {
	if([[filename pathExtension] hasSuffix:@"jpg"]){
		[files addObject:filename];
	}
}
 
//快速枚举
//for(NSString *filename in direnum)
//{
//    if([[filename pathExtension] isEqualToString:@"jpg"]){
//        [files addObject:filename];
//    }
//}
NSLog(@"files:%@",files);
 
//枚举
NSEnumerator *filenum;
filenum = [files objectEnumerator];
while (filename = [filenum nextObject]) {
	NSLog(@"filename:%@",filename);
}
 
//快速枚举
//for(id object in files)
//{
//    NSLog(@"object:%@",object);
//}
几个小异议


//2、创建空字符串，给予赋值。
 
NSString *astring = [[NSString alloc] init];
astring=@"This is a String!";
[astring release];
NSLog(@"astring:%@",astring);

貌似这样有问题吧, 最初alloc出来的astring会出现内存泄露.

添加如下两个NSLog来输出astring当前所指向的内存即可看出

NSString *astring = [[NSString alloc] init];
NSLog(@"0x%.8x", astring);
astring=@"This is a String!";
NSLog(@"0x%.8x", astring);
[astring release];
NSLog(@"astring:%@",astring);
 


2009-09-04 18:06:29.024test[15911:20b] 0x30683a2c
2009-09-04 18:06:29.025test[15911:20b] 0x000a10f4
因此是有问题的

--------------------------------------------------------------------------------------------------

4里面, 记得需要指定编码吧
- (id)initWithCString:(const char *)nullTerminatedCString encoding:(NSStringEncoding)encoding;

下面这些已经被放弃了
- (id)initWithCStringNoCopy:(char *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)freeBuffer DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)initWithCString:(const char *)bytes length:(NSUInteger)length DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)initWithCString:(const char *)bytes DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;    
+ (id)stringWithCString:(const char *)bytes length:(NSUInteger)length DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
+ (id)stringWithCString:(const char *)bytes DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

6和4类似

--------------------------------------------------------------------------------------------------

/*---------------在已有字符串后面添加字符----------------*/
[String1 appendFormat:[NSString stringWithFormat:@", I will be adding some character"]];

这里其实就用你注释掉的appendString就好
--------------------------------------------------------------------------------------------------


 
NSMutableArray *MutableArray = [[NSMutableArray alloc] init];
NSArray *array = [NSArray arrayWithObjects:
				  @"a",@"b",@"c",nil];
NSLog(@"array:%@",array);
MutableArray = [NSMutableArray arrayWithArray:array];
NSLog(@"MutableArray:%@",MutableArray);


类似最初提到的, MutableArray = [NSMutableArray arrayWithArray:array]; 这里会出现内存泄露

--------------------------------------------------------------------------------------------------
array1 = [NSArray arrayWithArray:array];
如果是NSArray到NSArray这样做的话, 一般来说, 并非复制, 而只是增加了一次引用计数

--------------------------------------------------------------------------------------------------

//Copy
 
//id obj;
NSMutableArray *newArray = [[NSMutableArray alloc] init];
NSArray *oldArray = [NSArray arrayWithObjects:
					 @"a",@"b",@"c",@"d",@"e",@"f",@"g",@"h",nil];
 
NSLog(@"oldArray:%@",oldArray);
for(int i = 0; i < [oldArray count]; i++)
{        
	obj = [[oldArray objectAtIndex:i] copy];
	[newArray addObject: obj];
}
//     
NSLog(@"newArray:%@", newArray);
[newArray release];


作了copy是需要手动release的, 所以你的这些obj都会被泄露一次
--------------------------------------------------------------------------------------------------


