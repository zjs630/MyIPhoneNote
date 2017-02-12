1，将数据持久存储到iPhone，常用的方法有属性列表，对象归档，SQLite3和Core Data。



NSUserDefaults数据被持久化到文件系统中，而没有存储到内存中。Lightweight storage of Property Lists.
It's basically an NSDictionary that persists between launches of your application.

//Every time you call this you'll get the same instance.
1，读写用户偏好
//
NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
//读取
NSInteger age = [userDefaults integerForKey:@"age"];
//写入
NSInteger age = 30;
[userDefaults setInteger:age forKey:@"age"];
//[[NSUserDefaults standardUserDefaults] setInteger:age forKey:@"age"];
//删除
[userDefaults removeObjectForKey:@"age"];
//同步
[userDefaults synchronize];
//Always remember to write the defaults out after each batch fo changes!
//If you don't synchronize, your data will not be getting saved.
//[[NSUserDefaults standardUserDefaults] synchronize];//同步

2,存储NSData实例
//存档
UIColor myColor = [UIColor blueColor];
NSData *colorData = [NSKeyedArchiver archivedDataWithRootObject:myColor];
[prefs setObject:colorData forKey:@"myColor"];
//解档
NSData *colorData = [prefs objectForKey:@"myColor"];
UIColor myColor = [NSKeyedUNarchiver unarchiveObjectWithData:colorData];


3,Sample methods;
-(void)setKouble:(double)aDouble forKey:(NSString *)key;
-(NSInteger)integerForKey:(NSString *)key;//NSInteger is a typedef to 32 or 64 bit int 
-(void)setObject:(id)obj forKey:(NSString *)key;//obj must be a Property List 
-(NSArray *)arrayForKey:(NSString *)key;// will return nil if value for key is not NSArray





NSUserDefaults数据存储的位置

NSUserDefaults用于保存iPhone程序的数据，使用非常方便。

那么这些数据最终存放在什么地方呢？存放于一个plist文件中。这个文件位于

<UUID for your App>\Library\Preferences\<your App"s bundle ID>.plist




1,得到用户的首选语言
-(NSString *)getUserDefaultSystem{
    //在缺省值中找到AppleLanguages, 返回值是一个数组
    NSArray *currentlanguages =[[NSUserDefaults standardUserDefaults] objectForKey:@"AppleLanguages"];
    //在得到的数组中的第一个项就是用户的首选语言了
    NSString *preferredLang = [currentlanguages objectAtIndex:0];
    NSLog(@"system language: = %@",preferredLang);
    return preferredLang;
}


2,NSUserDefaults读取和写入自定义对象 收藏
NSUserDefaults可以存取一些短小的信息。
比如存入再读出一个字符串到NSUserDefaults：
view plaincopy to clipboardprint?
NSString *string = [NSString stringWithString @"hahaha"];  
NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];  
[ud setObject:string forKey:@"myKey"];  
NSString *value;  
value = [ud objectForKey:"myKey"];  
 
但是并不是所有的东西都能往里放的。NSUserDefaults只支持： NSString, NSNumber, NSDate, NSArray, NSDictionary.
如果把一个自定义的类存到一个NSArray里，然后再存到NSUserDefaults里也是不能成功的。不信可以试试，如果你成功的请告诉我。
那怎么办呢？
我找到的方法是，让这个自定义类实现<NSCoding>协议中的- (id) initWithCoder: (NSCoder *)coder方法和- (void) encodeWithCoder: (NSCoder *)coder方法（obj-c的协议protocol就是java的接口interface，就是C++的纯虚函数），然后把该自定义的类对象编码到 NSData中，再从NSUserDefaults中进行读取。
粘代码：
假设有这样一个简单的类对象
view plaincopy to clipboardprint?
@interface BusinessCard : NSObject <NSCoding>{  
    NSString *_firstName;  
    NSString *_lastName;  
}  
@property (nonatomic, retain) NSString *_firstName;  
@property (nonatomic, retain) NSString *_lastName;  
@end;  
  
@implementation BusinessCard  
@synthesize _firstName, _lastName;  
- (void)dealloc{  
    [_firstName release];  
    [_lastName release];  
    [super dealloc];  
}  
- (id) initWithCoder: (NSCoder *)coder  
{  
    if (self = [super init])  
    {  
        self._firstName = [coder decodeObjectForKey:@"_firstName"];  
        self._lastName = [coder decodeObjectForKey:@"_lastName"];  
    }  
    return self;  
}  
- (void) encodeWithCoder: (NSCoder *)coder  
{  
    [coder encodeObject:_firstName forKey:@"_firstName"];  
    [coder encodeObject:_lastName forKey:@"_lastName"];  
      
}  
  
@end  
 
然后再存取时通过NSData做载体：
view plaincopy to clipboardprint?
BusinessCard *bc = [[BusinessCard alloc] init];  
NSUserDefaults *ud = [NSUserDefaults standardUserDefaults];  
NSData *udObject = [NSKeyedArchiver archivedDataWithRootObject:bc];  
[ud setObject:udObject forKey:@"myBusinessCard"];  
[bc release];  
udObject = nil;  
udObject = [ud objectForKey:@"myBusinessCard"];  
bc = [NSKeyedUnarchiver unarchiveObjectWithData:udObject] ;  
  
      
      
 
以上的代码时由另一个程序中截取的，没有测试过，但意思就是这样了。
如果一个自定义类中由另一个自定义类对象，那么所有嵌套的类都要实现<NSCoding>。



创建一个user defaults方法有多个，最简单得快速创建方法:
   NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];

添加数据到 user defaults:
   [accountDefaults setObject:nameField.text forKey:UserDefaultNameKey];
也可以添加基本数据类型int, float, bool等，有相应得方法
   [accountDefaults setBool:YES forKey:UserDefaultBoolKey];

从user defaults中获取数据:
   [accountDefaults objectForKey:NCUserDefaultNameKey]
  
 [accountDefaults boolForKey: UserDefaultBoolKey];

要点： NSUserDefaults非常好用，并不需要用户在程序中设置NSUserDefaults的全局变量，需要在哪里使用NSUserDefaults的数据，那么就在哪里创建一个NSUserDefaults对象，然后进行读或者写操作。
     针对同一个关键字对应的对象或者数据，可以对它进行重写，重写之后关键字就对应新的对象或者数据，旧的对象或者数据会被自动清理。



－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

7. 用户缺省值NSUserDefaults读取：
//得到用户缺省值
NSUserDefaults *defs = [NSUserDefaults standardUserDefaults];

//在缺省值中找到AppleLanguages, 返回值是一个数组
NSArray* languages = [defs objectForKey:@"AppleLanguages"];
NSLog(@"all language语言 is %@", languages);

//在得到的数组中的第一个项就是用户的首选语言了
NSLog(@"首选语言 is %@",[languages objectAtIndex:0]);  

8，
How to print values in NSUserDefaults to the NSLog?
Solution
NSUserDefaults is basically kind of hashmap(dictionary) that stores the keys and values.
In order to print all the keys do the follow:
NSLog(@"%@", [[[NSUserDefaults standardUserDefaults] dictionaryRepresentation] allKeys]);

In order to print both the keys & values do the follow:
NSLog(@"%@", [[NSUserDefaults standardUserDefaults] dictionaryRepresentation]);
