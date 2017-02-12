JSON 
1,object 是一个无序的name/value值对。
name/value pairs 都放在{}中。
name/value 中间用分号：隔开。每一个member(键值对)，用逗号分开。
例如：
{ "name":"zjs",
    "age":26,
    "isBoy":true,
    "photo":null,
    "assignments":["a","b","c"]
}
2，array. An array is an ordered collection of values(数组是有序的值集合).
value 都放在[]中。
values are separated by comma（逗号）。
例如：["zjs",26];
3，value 可以是string,number,object,array,true,false,null.

JSON对应的Objective-c类型.
null -> NSNull
string -> NSString
array -> NSMutableArray
object -> NSMutableDictionary
true -> NSNumber's -numberWithBool:YES
false -> NSNumber's -numberWithBool:NO
integer up to 19 digits -> NSNumber's -numberWithLongLong:
all other numbers -> NSDecimalNumber


1，SBJson( 原json-framework重命名为SBJson，避免与苹果公司的json.framework冲突)。
注意：
//如果你复制SBJson库文件到项目中，要引用库中的某些文件时，与以前不同的是，将"JSON.h" 改为"SBJson.h".
//如果ios系统，用的是静态库。JSON.framework变为libsbjson-ios.a。此时要将<SBJson/SBJson.h>导入到代码中。

2,Reading a JSON string to Foundation objects.
#import <JSON/JSON.h>
//get a JSon string from the cloud
NSString *jsonString =...;

//Top level may be an NSDictionary or an NSArray
id object = [jsonString JSonValue];

3,Writing a JSON string form Foundation objects
//Create some data in your app
NSDictionary *dic = ...;

//Convert into a JSON string fefore sending to the cloud
jsonString = [dictionary JSONRepresentation];
