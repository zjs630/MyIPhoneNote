1，将数据持久存储到iPhone，常用的方法有属性列表，对象归档，SQLite3和Core Data。

对象归档，是另一种形式的序列化，可以将自定义的对象写入到文件中。

一：自定义对象的序列化，
1，要实现NSCoding协议中声明的两个方法，initWithCoder() 和encodeWithCoder().
//NScoping（copy协议是为了模型数据可以复制，对于归档而言，不是必须要实现）
@interface BirthdayData : NSObject <NSCoding>{
	NSString *name;
	int year;
	BOOL isRunYue;//是否闰月
	
}
@property(nonatomic,copy) NSString *name;
@property(nonatomic) int year;
@property(nonatomic) BOOL isRunYue;

#import "BirthdayData.h"
@implementation BirthdayData
@synthesize name,year,isRunYue;
-(id)init{
	if (self = [super init]) {
	}
	return self;
}

//将对象写入到文件中。//编码
- (void)encodeWithCoder:(NSCoder *)coder {
    [coder encodeObject:self.name forKey:@"iName"];//key可以自己定，但编码和解码处的key要保持一直。
	[coder encodeInt:self.year forKey:@"iYear"];
	[coder encodeBool:self.isRunYue forKey:@"iIsRunYue"];
}

//将文件中数据读入到对象中。//解码
- (id)initWithCoder:(NSCoder *)coder {
	self = [super init];
	if (self != nil) {
        self.name = [coder decodeIntForKey:@"iName"];
		self.year = [coder decodeIntForKey:@"iYear"];
		self.isRunYue = [coder decodeBoolForKey:@"iIsRunYue"];
	}
	return self;
}

#pragma mark- NSCopying

-(id)copyWithZone:(NSZone *)zone{
    Student *copy = [[[self class] allocWithZone:zone] init];
    copy.name = [self.name copyWithZone:zone];
    copy.age = self.age;
    copy.weight = self.weight;
    copy.hobby = [self.hobby copyWithZone:zone];
    copy.others = [self.others copyWithZone:zone];
    
    return copy;
}

@end
2，写入文件
[NSKeyedArchiver archiveRootObject:object toFile:filename];
3，读取。
id obj = [NSKeyedUnarchiver unarchiveObjectWithFile:filename];

