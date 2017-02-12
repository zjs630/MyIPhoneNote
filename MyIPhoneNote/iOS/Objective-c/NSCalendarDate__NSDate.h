i） NSCalendarDate

NSCalendarDate对象包含了日期、时间、时区以及一个带有格式的字符串。NSCalederDate从NSDate继承而来。
NSCalendarDate对象基本上是不能被修改的:你无法修改其中的时间和日期。当然你可以修改那个带格式的字符串和时区。
NSCalenderDate对象经常被多个对象共享使用。

+（id）calendarDate        该方法创建并返回了一个本地日期和时间的默认格式的NSCalendarDate对象，它的时区为机器所设置。

+号表示类方法，通过给类而不是对象发送消息来调用。

+（id）dateWithYear:（int）year
month:（unsigned）month
day:（unsigned）day
hour:（unsigned）hour
minute:（unsigned）minute
second:（unsigned）second
timeZone:（NSTimeZone *）aTimeZone

类方法返回一个自动释放对象。

-（NSCalendarDate *）dateByAddingYears:（int）year
months:（int）month
days:（int）day
hours:（int）hour
minutes:（int）minute
seconds:（int）second
这个方法返回和参数指定的 年、月、日、小时、分、秒偏移量的日历对象。

-（int）dayOfCommonEra       这个方法返回从1 A.D到现在的天数。
-（int）dayOfMonth      这个方法返回的是这个月的第几天（1到31）。
-（int）dayOfWeek       这个方法返回一周中的星期几（0到6），0代表星期天。
-（int）dayOfYear         这个方法返回一年中的第几天（1-366）。
-（int）hourOfDay        这个方法返回接收时的小时值（0到23）。
-（int）minuteOfHour  这个方法返回接收时的分钟值（0到59）。
-（int）monthOfYear    这个方法返回一年中的第几个月（1到12）。
-（void）setCalendarFormat:（NSString *）format 这个方法设置接收者的默认的日历格式。日历格式是由一个包含日期转换说明的字符串。

符号             意义
%y           不带公元纪年的年份（00-99）
%Y           带公元纪年的年份（“1990”）
%b           月份的缩写（”Jan“）
%B           月份的全称（”January“）
%m          以数字显示的月份（01-12）
%a           星期几的缩写（”Fri“）
%A           星期几的全称（”Friday“）
%w           以数字显示的星期几（0-6），0为星期天
%d           一月中的第几天（01-31）
%e           和%d一样，只是没有前面的0
%j            一年中的第几天（001-366）
%H          以24小时计量的小时数（00-23）
%I            以12小时计量的小时数（01-12）
%p           本地的A.M./P.M.
%M          分钟数（00-59）
%S           秒数（00-59）
%F           毫秒数（000-999）
%x           本地的日期表示的天
%X           本地的时间表示的时间
%c           %X%x的简短格式，时间和日期的本地格式
%Z           时区名字
%z            小时和分计量的时区和GMT的差值（HHMM）
%%          A%字符

-（NSDate *）laterDate:（NSDate *）anotherDate   这个方法继承至NSDate。将接受者和anotherDate做比较，返回两者中日期靠后的那一个。

-（NSTimeInterval）timeIntervalSinceDate:（NSDate *）anotherDate  这个方法计算接收时与anotherDate之间以秒计量的时间差。如果接收时早于anotherDate，返回值为负数。 NSTimerInterval就是double类型。