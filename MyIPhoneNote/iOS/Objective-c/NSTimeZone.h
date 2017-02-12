1、设置时区

NSTimeZone *defaultTimeZone = [NSTimeZone defaultTimeZone];
NSTimeZone *tzGMT = [NSTimeZone timeZoneWithName:@"GMT"];
//上面两个时区任意用一个。
[NSTimeZone setDefaultTimeZone:tzGMT];
