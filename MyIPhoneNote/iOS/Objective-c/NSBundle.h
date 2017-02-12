1,获取应用的名称
NSString *title = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"];
2，获取应用的版本号
NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleVersionKey];
