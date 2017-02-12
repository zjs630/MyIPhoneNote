*
用NSValue进行统一存储也不错，NSValue可以包装任何值

NSRect *rect = NSRectMake(1,2,20,30);
NSValue *value = [NSValue valueWithByte:&rect ObjCType:@encode(NSRect)];
[array addObject:value];

NSRect *getRect = [NSValue getValue:&rect];



NSValue
NSValue provides a simple container for a single C or Objective-C data item. It can hold any of the scalar types such as char, int, float, or double, as well as pointers, structures, and object IDs. It lets you add items of such data types to collections such as instances of NSArray and NSSet, which require their elements to be objects. This is particularly useful if you need to put point, size, or rectangle structures (such as NSPoint, CGSize, or NSRect) into a collection.

Generic object wrapper for some non-object, non-primitive data types (i.e. C structs).
e.g. NSValue *edgeInsetsObject = [NSValue valueWithUIEdgeInsets:UIEdgeInsetsMake(1,1,1,1)]
