1，创建一个Command line Utility－－>Foundation Tool项目.
//注：testFile文件要自己创建，放在项目根目录/build/Debug目录下。
	//代码如下：
	NSString *fName = @"testFile";//文件的名称或者是路径
	NSDictionary *attr;
	NSFileManager *fm = [NSFileManager defaultManager];
	//判断文件是否存在
	if ([fm fileExistsAtPath:fName]==NO) {
		NSLog(@"File doesn't exist!");
	}
	//复制文件
	if ([fm copyPath:fName toPath:@"newfile" handler:nil]==NO) {
		NSLog(@"File copy failed!");
	}
	//判断两个文件是否相同
	if ([fm contentsEqualAtPath:fName andPath:@"newfile"]==NO) {
		NSLog(@"Files are not equal!");
	}
	//重新命名文件名
	if ([fm movePath:@"newfile" toPath:@"newfile2" handler:nil]==NO) {
		NSLog(@"File rename failed!");
	}
	//获得文件的大小并显示
	if ((attr = [fm fileAttributesAtPath:@"newfile2" traverseLink:NO])==nil) {
		NSLog(@"Couldn't get file attributes!");
	}
	NSLog(@"File size is %i bytes",[[attr objectForKey:NSFileSize] intValue]);
	//显示文件的内容
	NSLog(@"%@",[NSString stringWithContentsOfFile:@"newfile2" encoding:NSUTF8StringEncoding error:nil]);
2,NSData的使用，读取一个文件的内容，将其写入另一个文件,之后删除原来的文件。
	
NSFileManager *fm = [NSFileManager defaultManager];
	//读取文件newfile2中的内容
	if ([fm fileExistsAtPath:@"newfile2"]==YES) {
			NSData *fileData = [fm contentsAtPath:@"newfile2"];

		//将数据写入要创建的文件newfile3中
		if ([fm createFileAtPath:@"aa/newfile3" contents:fileData attributes:nil]) {
			NSLog(@"写入成功！");
		}
		//删除newfile2文件
		if ([fm removeFileAtPath:@"newfile2" handler:nil]==YES) {
			NSLog(@"删除成功");
		}
		//将新创建的文件移动到根目录下
		if ([fm movePath:@"aa/newfile3" toPath:@"newfile3" handler:nil]==YES) {
			NSLog(@"移动成功！");
		}
		//将移动到根目录的文件newfile3，复制到aa目录下.//??复制成功但是返回NO？？？
		if ([fm copyPath:@"newfile3" toPath:@"aa/newfile3" handler:nil]==YES) {
			NSLog(@"复制成功！");
		}
		//获取当前目录
		NSLog(@"%@",[fm currentDirectoryPath]);
		//创建一个新目录
		[fm createDirectoryAtPath:@"abc" attributes:nil];
		//重新命名或移动目录
		[fm movePath:@"abc" toPath:@"ddd" handler:nil];
		//删除空目录
		[fm removeFileAtPath:@"ddd" handler:nil];
	}
3,判断某个文件是否存在。
	NSString *myBundlePath = [[NSBundle mainBundle] bundlePath];
	NSString *path = [NSString stringWithFormat:@"%@/Info.plist",myBundlePath];
	BOOL fileExists = [[NSFileManager defaultManager] fileExistsAtPath:path];

4,获取Documents目录，并在该目录下创建一个文件，进行读写操作。
a,	//获取Documents目录
方法1,
    #define DOCUMENTS_FOLDER [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"]
    printf("Documents folder is %s\n", [DOCUMENTS_FOLDER UTF8String]);
方法2,
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	//注：上条语句参数说明。参数1，表示我们正在查找Documents目录的路径，参数2，表明搜索限制于我们应用程序的沙盒。在Mac OS X中，表示我们希望该函数查看用户的主目录。
	//我们知道每个iPhone应用程序只有一个Documents目录，因此只返回一条匹配的路径的数组。
	NSString *documentsDirectory = [paths objectAtIndex:0];//取出数组中的第一条数据。
	NSLog(@"%@",documentsDirectory);
B，	//NSString *filename = [documentsDirectory stringByAppendingPathComponent:@"theFile.txt"];
	NSString *filename = [documentsDirectory stringByAppendingString:@"/theFile.txt"];
	NSLog(@"%@",filename);


5,// Basic directories
 NSString *homePath = NSHomeDirectory(); 
 NSString *tmpPath = NSTemporaryDirectory();
6,获取路径的最后一部分，如文件名称（包括扩展名）
	[pathStringName lastPathComponent];
7,得到目录上的文件地址：
NSString *filePath = [documentsDirectory stringByAppendingPathComponent:@"文件名.扩展名"];
8,利用NSFileManager获取文件(文件夹)列表

在开发iPhone程序时，有时候要对文件进行一些操作。而获取某一个目录中的所有文件列表，是基本操作之一。通过下面这段代码，就可以获取一个目录内的文件及文件夹列表。

NSFileManager *fileManager = [NSFileManager defaultManager];
//在这里获取应用程序Documents文件夹里的文件及文件夹列表
NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
NSString *documentDir = [documentPaths objectAtIndex:0];
NSError *error = nil;
NSArray *fileList = [[NSArray alloc] init];
//fileList便是包含有该文件夹下所有文件的文件名及文件夹名的数组
fileList = [fileManager contentsOfDirectoryAtPath:documentDir error:&error];

以下这段代码则可以列出给定一个文件夹里的所有子文件夹名

NSMutableArray *dirArray = [[NSMutableArray alloc] init];
BOOL isDir = NO;
//在上面那段程序中获得的fileList中列出文件夹名
for (NSString *file in fileList) {
	NSString *path = [documentDir stringByAppendingPathComponent:file];
	[fileManager fileExistsAtPath:path isDirectory:(&isDir)];
	if (isDir) {
		[dirArray addObject:file];
	}
	isDir = NO;
}
NSLog(@"Every Thing in the dir:%@",fileList);
NSLog(@"All folders:%@",dirArray);
9,查找家目录下的某个文件夹下的文件名。
NSFileManager *fileManager = [NSFileManager defaultManager];
//在这里获取应用程序Documents文件夹里的文件及文件夹列表
NSString *documentDir = [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"myImages"];
//	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//	NSString *documentDir = [documentPaths objectAtIndex:0];
NSError *error = nil;
NSArray *fileList = [[NSArray alloc] init];
//fileList便是包含有该文件夹下所有文件的文件名及文件夹名的数组
fileList = [fileManager contentsOfDirectoryAtPath:documentDir error:&error];

//判断文件是否存在，若存在输出。
NSFileManager *fm= [NSFileManager defaultManager];
if ([fm fileExistsAtPath:documentDir]!=NO) {
	for(NSString *bb in fileList)
	{
		NSLog(@"name = %@",bb);
	}
}
10,如果Document文件夹下不存在某个文件，将resource中的文件拷贝到Document文件夹下。
NSString *path = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/Navigation.plist"];
if (![[NSFileManager defaultManager] fileExistsAtPath:path]) {
	NSString *embabedPath = [[NSBundle mainBundle] pathForResource:@"Navigation" ofType:@"plist"];
	NSError *error;
	[[NSFileManager defaultManager] copyItemAtPath:embabedPath toPath:path error:&error];
}
NSMutableDictionary *onlineDictioanry = [NSMutableDictionary dictionaryWithContentsOfFile:path];//读取文件


11，每个应用程序都有自己的/Document文件夹，并且应用程序仅能读取各自的/Document中的内容。

12,删除某个路径,及路径下的所有文件和文件夹
[[NSFileManager defaultManager] removeItemAtPath:diskCachePath error:nil];
13,创建路径
if (![[NSFileManager defaultManager] fileExistsAtPath:diskCachePath])
{
    [[NSFileManager defaultManager] createDirectoryAtPath:diskCachePath
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:NULL];
}




  