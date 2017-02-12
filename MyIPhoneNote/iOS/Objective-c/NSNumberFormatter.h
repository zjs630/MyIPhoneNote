1,	
NSNumberFormatter *f2 = [[NSNumberFormatter alloc] init];
[f2 setMaximumFractionDigits:3];//设置小数点后的有效位数。3，代表小数点后最多有3位数字。若用科学计数发表示，则代表小数点后最多有两位有效数字。
[f2 setNumberStyle:NSNumberFormatterNoStyle];//设置类型

NSString *formattedNumberString = [f2 stringFromNumber:[NSNumber numberWithDouble:122344.4002]];
NSLog(@"formattedNumberString : %@", formattedNumberString);
//可以去掉末位的0

Here are the different formatter styles, and the result when converting [NSNumber numberWithDouble:123.4] into an NSString.
NSNumberFormatterNoStyle (123)
NSNumberFormatterDecimalStyle (123.4)
NSNumberFormatterCurrencyStyle ($123.40)
NSNumberFormatterPercentStyle (12,340%)
NSNumberFormatterScientificStyle (1.234E2)
NSNumberFormatterSpellOutStyle (one hundred and twenty-three point four)