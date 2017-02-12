1，获得当前的日期和时间。
	NSDate *myDate = [NSDate date];
    NSLog(@" %@",myDate);
2，获得从现在开始24小时后的时间。
	NSTimeInterval secondsPerDay = 24*60*60;
	NSDate *tomorrow = [NSDate dateWithTimeIntervalSinceNow:secondsPerDay];
    NSLog(@" %@",tomorrow);
	/*
	NSDate  *today;
	NSDate *tomorrow;
	today = [NSDate date];
	tomorrow = [NSDate dateWithTimeInterval:(i*24*60*60) sinceDate:today]; //可能有更好的
	*/
3，根据已有的日期创建一个日期。例如：获得昨天的这个时间。
	NSDate *yesterday = [myDate addTimeInterval:-secondsPerDay];
	NSLog(@"Hello, %@",yesterday);
4，比较两个日期是否完全相等。
	BOOL someDate = [tomorrow isEqualToDate:yesterday];//return NO
5,判断一个日期是在另一个日期之前还是之后
	NSDate *earlierDate = [yesterday earlierDate:tomorrow];//return yesterday
	NSDate *laterDate = [yesterday laterDate:tomorrow];//return tomorrow
6,计算两个日期之间相隔多少秒.//NSTimeInterval是double类型，声明的变量其后不加
	NSTimeInterval secondsBetweenDate = [tomorrow timeIntervalSinceDate:myDate];
7,计算现在和将来的一个日期之间相隔多少秒
	NSTimeInterval secondsFromNow = [tomorrow timeIntervalSinceNow];
8.Date format用法：
-(NSString *) getDay:(NSDate *) d {
    NSString *s ;
    NSDateFormatter *format = [[NSDateFormatter alloc] init];
    [format setDateFormat:@"YYYY/MM/dd hh:mm:ss"];
    s = [format stringFromDate:d];
    return s;
}

9，计算代码耗时，示例

NSDate* tmpStartData = [NSDate date];
//You code here...
double deltaTime = [[NSDate date] timeIntervalSinceDate:tmpStartData];
NSLog(@">>>>>>>>>>cost time = %f", deltaTime);

10,NSDate存储的是世界标准时(UTC)，输出时需要根据时区转换为本地时间。
//获取当前日期和时间
NSDate * dt = [NSDate date];

//NSDateFormatter实例
NSDateFormatter *form= [[NSDateFormatter alloc] init];

//NSDateFormatter格式化
[form setDateFormat：@"G yyyy/MM/dd(EEE) K:mm:ss"];

//输出为文本格式
NSString *str = [form stringFromDate：dt];
NSLog(str);//str 变量内容格式为 AD 2010/11/25(Thu) 00:55:15的格式。

// NSDateFormatter alloc内存释放
[form release];

该格式可以指定以下内容:
G: 公元时代，例如AD公元
yy: 年的后2位
yyyy: 完整年
MM: 月，显示为1-12
MMM: 月，显示为英文月份简写,如 Jan
MMMM: 月，显示为英文月份全称，如 Janualy3
dd: 日，2位数表示，如02
d: 日，1-2位显示，如 2
EEE: 简写星期几，如Sun
EEEE: 全写星期几，如Sunday
aa: 上下午，AM/PM
H: 时，24小时制，0-23
K：时，12小时制，0-11
m: 分，1-2位
mm: 分，2位
s: 秒，1-2位
ss: 秒，2位
S: 毫秒

//NSDate常用代码范例
NSDate类用于保存时间值，同时提供了一些方法来处理一些基于秒级别时差(Time Interval)运算和日期之间的早晚比较等。
 
1. 创建或初始化可用以下方法
    用于创建NSDate实例的类方法有
    + (id)date;
    返回当前时间
 
    + (id)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;   
    返回以当前时间为基准，然后过了secs秒的时间
 
    + (id)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secs;
    返回以2001/01/01 GMT为基准，然后过了secs秒的时间
 
+ (id)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;
    返回以1970/01/01 GMT为基准，然后过了secs秒的时间
 
    + (id)distantFuture;
    返回很多年以后的未来的某一天。
    比如你需要一个比现在(Now)晚(大)很长时间的时间值，则可以调用该方法。测试返回了4000/12/31 16:00:00
 
    + (id)distantPast;
    返回很多年以前的某一天。
    比如你需要一个比现在(Now)早(小)大很长时间的时间值，则可以调用该方法。测试返回了公元前0001/12/31 17:00:00
 
    用于创建NSDate实例的实例方法有
    - (id)addTimeInterval:(NSTimeInterval)secs;
    返回以目前的实例中保存的时间为基准，然后过了secs秒的时间
 
    用于初始化NSDate实例的实例方法有
    - (id)init;
    初始化为当前时间。类似date方法
 
    - (id)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secs;
    初始化为以2001/01/01 GMT为基准，然后过了secs秒的时间。类似dateWithTimeIntervalSinceReferenceDate:方法
 
    - (id)initWithTimeInterval:(NSTimeInterval)secs sinceDate:(NSDate *)refDate;
    初始化为以refDate为基准，然后过了secs秒的时间
 
    - (id)initWithTimeIntervalSinceNow:(NSTimeInterval)secs;
    初始化为以当前时间为基准，然后过了secs秒的时间
 
 
2. 日期之间比较可用以下方法
    - (BOOL)isEqualToDate:(NSDate *)otherDate;
    与otherDate比较，相同返回YES
 
    - (NSDate *)earlierDate:(NSDate *)anotherDate;
    与anotherDate比较，返回较早的那个日期
 
    - (NSDate *)laterDate:(NSDate *)anotherDate;
    与anotherDate比较，返回较晚的那个日期
 
    - (NSComparisonResult)compare:(NSDate *)other;
    该方法用于排序时调用:
      . 当实例保存的日期值与anotherDate相同时返回NSOrderedSame
      . 当实例保存的日期值晚于anotherDate时返回NSOrderedDescending
      . 当实例保存的日期值早于anotherDate时返回NSOrderedAscending
 if ([someDate compare:anotherDate] == NSOrderedAscending) {
    // someDate is earlier than anotherDate
}
 
3. 取回时间间隔可用以下方法
    - (NSTimeInterval)timeIntervalSinceDate:(NSDate *)refDate;
    以refDate为基准时间，返回实例保存的时间与refDate的时间间隔
 
    - (NSTimeInterval)timeIntervalSinceNow;
    以当前时间(Now)为基准时间，返回实例保存的时间与当前时间(Now)的时间间隔
 
    - (NSTimeInterval)timeIntervalSince1970;
    以1970/01/01 GMT为基准时间，返回实例保存的时间与1970/01/01 GMT的时间间隔
 
    - (NSTimeInterval)timeIntervalSinceReferenceDate;
    以2001/01/01 GMT为基准时间，返回实例保存的时间与2001/01/01 GMT的时间间隔
 
 
    + (NSTimeInterval)timeIntervalSinceReferenceDate;
    以2001/01/01 GMT为基准时间，返回当前时间(Now)与2001/01/01 GMT的时间间隔
 
 
4. 将时间表示成字符串
    - (NSString *)description;
    以YYYY-MM-DD HH:MM:SS ±HHMM的格式表示时间。
    其中 "±HHMM" 表示与GMT的存在多少小时多少分钟的时区差异。比如，若时区设置在北京，则"±HHMM" 显示为 "+0800"



1.显示当前的时间

//获得一个时间器对象同时在默认模式下根据当前运转循环下安排它的时间
-(void)viewDidLoad{
	
	timer = [NSTimer scheduledTimerWithTimeInterval:(1.0) target:self selector:@selector(time) userInfo:nil repeats:YES];
	[super viewDidLoad];
}



-(void)time{
	
	NSDate *now = [NSDate date]; //获得现在的时间
	
	int hourOfDay = [[now dateWithCalendarFormat:nil timeZone: nil] hourOfDay];
	int minuteOfHour = [[now dateWithCalendarFormat:nil timeZone: nil] minuteOfHour];
	//这两个变量名固定,从日历中获得小时和分钟的数据
	hour.text =[NSString stringWithFormat:@"%d",hourOfDay];
	min.text = [NSString stringWithFormat:@"%d",minuteOfHour];
    
    NSDateFormatter *form= [[NSDateFormatter alloc] init];
	[form setDateFormat:@"yyyy年MM月dd日 K时"];
	NSString *str = [form stringFromDate:now];
	NSLog(@"%@",str);
	[form release];
}


2.获得一个时间计数,貌似秒数的总数

-(IBAction) epoch{
	
	time_t  now;
	time(&now);
	label.text = [NSString  stringWithFormat:@"calling:%d",now];
}

3,计算时间距离

+ (NSString *) getTimeString:(NSTimeInterval) time{
    
    // Calculate distance time string
    //
    
    int distance = [[NSDate date] timeIntervalSince1970] - time;
    NSString *string;
    if (distance < 1){//avoid 0 seconds
        string = @"刚刚";
    }
    else if (distance < 60) {
        string = [NSString stringWithFormat:@"%d秒前", (distance)];
    }
    else if (distance < 3600) {//60 * 60
        distance = distance / 60;
        string = [NSString stringWithFormat:@"%d分钟前", (distance)];
    }  
    else if (distance < 86400) {//60 * 60 * 24
        distance = distance / 3600;
        string = [NSString stringWithFormat:@"%d小时前", (distance)];
    }
    else if (distance < 604800) {//60 * 60 * 24 * 7
        distance = distance / 86400;
        string = [NSString stringWithFormat:@"%d天前", (distance)];
    }
    else if (distance < 2419200) {//60 * 60 * 24 * 7 * 4
        distance = distance / 604800;
        string = [NSString stringWithFormat:@"%d周前", (distance)];
    }
    else {
        static NSDateFormatter *dateFormatter = nil;
        if (dateFormatter == nil) {
            dateFormatter = [[NSDateFormatter alloc] init];
            [dateFormatter setDateFormat:@"yyyy-MM-dd"];
        }
        
        string = [dateFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:(time)]];
        
    }
    return string;
}