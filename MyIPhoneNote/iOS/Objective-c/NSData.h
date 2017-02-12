1,How to convert NSString value to NSData.
	NSString* str= @"0123456789";
	NSData* data=[str dataUsingEncoding:NSUTF8StringEncoding];
	NSLog(@"%@",data);//<30313233 34353637 3839>
	//将NSData转换为NSString
	NSString* aStr = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
	NSLog(@"%@",aStr);//0123456789
2,网络通讯
NSData *data = [[NSData alloc] initWithContentOfURL:rul];
NSData *data = [NSData dataWithContentsOfURL:url];
3,下载图片，保存到document目录下的Icon文件夹下。
NSString *iconFolder = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Icons"];
NSString *iconPath = [iconFolder stringByAppendingFormat:@"/%@.jpg",name];//图片保存的路径和文件名

NSData* iconData = [NSData dataWithContentsOfURL:[NSURL URLWithString:serverPath]];//从网络获取图片
if (iconData) {
	[iconData writeToFile:iconPath atomically:YES];//保存图片
	UIImage *iconImage =[UIImage imageWithData:iconData];//加载图片
}
4,convert the image to NSData object

NSData* data = UIImageJPEGRepresentation(myImage, 1.0);
[data writeToFile:path atomically:YES];
5,将NSData转换为json数据
NSURL *url = [NSURL URLWithString:@"www.xxx.com/xxx"];
NSData *jsonData = [NSData dataWithContentsOfURL:url];
id results = [NSJSONSerialization JSOBObjectWithData:jsonData options:0 error:NULL];
