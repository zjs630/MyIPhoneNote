
Object wrapper around primitive types like int, float, double, BOOL, enums, etc.
NSNumber *n = [NSNumber numberWithInt:36];
float f = [n floatValue]; // would return 36.0 as a float (i.e. will convert types)
Useful when you want to put these primitive types in a collection (e.g. NSArray or NSDictionary).

1,将整型转换为NSNumber类型之后添加到数组。
NSNumber *yourNumber = [NSNumber numberWithInt:your_int_variable];
NSArray *bb = [NSArray addObject:yourNumber];
2，
NSNumber * number = [NSNumber numberWithInt:1];
NSNumber * number = @1;//最新定义的语法 in iOS 6:@()
3，
  // 整数
  NSNumber *fortyTwo = @42;             // 等价于 [NSNumber numberWithInt:42]
  NSNumber *fortyTwoUnsigned = @42U;    // 等价于 [NSNumber numberWithUnsignedInt:42U]
  NSNumber *fortyTwoLong = @42L;        // 等价于 [NSNumber numberWithLong:42L]
  NSNumber *fortyTwoLongLong = @42LL;   // 等价于 [NSNumber numberWithLongLong:42LL]

  // 浮点数
  NSNumber *piFloat = @3.141592654F;    // 等价于 [NSNumber numberWithFloat:3.141592654F]
  NSNumber *piDouble = @3.1415926535;   // 等价于 [NSNumber numberWithDouble:3.1415926535]

  // 布尔值
  NSNumber *yesNumber = @YES;           // 等价于 [NSNumber numberWithBool:YES]
  NSNumber *noNumber = @NO;             // 等价于 [NSNumber numberWithBool:NO]