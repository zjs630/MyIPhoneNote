1，将数据持久存储到iPhone，常用的方法有属性列表，对象归档，SQLite3和Core Data。

一：自定义对象的序列化，
1，要实现NSCoding要求的两个函数，initWithCoder() 和encodeWithCoder().
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
- (void)encodeWithCoder:(NSCoder *)coder {
    [coder encodeObject:self.name forKey:@"iName"];
	[coder encodeInt:self.year forKey:@"iYear"];
	[coder encodeBool:self.isRunYue forKey:@"iIsRunYue"];
}
- (id)initWithCoder:(NSCoder *)coder {
	self = [super init];
	if (self != nil) {
        self.name = [coder decodeIntForKey:@"iName"];
		self.year = [coder decodeIntForKey:@"iYear"];
		self.isRunYue = [coder decodeBoolForKey:@"iIsRunYue"];
	}
	return self;
}
@end
2，写入文件
[NSKeyedArchiver archiveRootObject:object toFile:filename];
3，读取。
id obj = [NSKeyedUnarchiver unarchiveObjectWithFile:filename];

