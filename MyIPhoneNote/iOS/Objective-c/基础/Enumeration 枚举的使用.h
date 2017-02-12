Objective-C允许我们定义自己命名的类型，这种类型叫做枚举。
例如，我们定义一个名为day的枚举类型，包含一周的每一天的名称，
enum day{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};
然后，我们可以把这些值之一赋给该类型的一个变量：
enum day today = Friday;


/* NS_ENUM supports the use of one or two arguments. The first argument is always the integer type used for the values of the enum. The second argument is an optional type name for the macro. When specifying a type name, you must precede the macro with 'typedef' like so:
 
 typedef NS_ENUM(NSInteger, NSComparisonResult) {
 ...
 };
 
 If you do not specify a type name, do not use 'typedef'. For example:
 
 NS_ENUM(NSInteger) {
 ...
 };
 */


//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
以一种高效的方式遍历集合的成员。//Looping through members of a collection in an efficient manner

1,枚举数组中的NSString objects.
NSArray *myArray = ...;
for(NSString *string in myArray){
	double value = [string doubleValue];
}
2,如果NSSet数组中不全是NSString。//in the set is different kinds of objects.
NSSet *mySet = ...;
for(id obj in mySet){
	//do something with obj,but make sure you don't send it a message it does not respond to 
	if([obj isKindOfClass:[NSString class]]){
		//send NSString messages to obj with impunity
	}
}
3,遍历 the keys or values of a dictionary.
NSDictionary *myDictonary = ...;
for(id key in myDictionary){
	//do something with key here
	id value = [myDictionary objectForKey:key];
}
	

1,Looping through members of a collection in an efficient manner

Example:NSArray of NSString objects
NSArray *myArray = ...;
for(NSString *string in myArray){
	double value = [string doubleValue];
}

Example:NSSet of id (could just as easily be an NSArray of id)
NSSet *mySet = ...;
for(id obj in mySet){
	//do something with obj, but make sure you don't send it a message it dose not respond to
	if([obj isKindOfClass:[NSString class]]){
		//send NSString message to obj with impunity
	}
}
2,Looping through the keys or values of a dictionary
Example:
NSDictionary *myDictionary = ...;
for(id key in myDictionary){
	//do something with key here
	id value = [myDictionary objectForKey:key];
	//do something with value here
	
}
