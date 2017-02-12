1，什么情况下不用SQLite?
It doesn't handle multiple writers very well.
(它不能很好的处理多个写操作，当有多个写操作时，它的性能并不高。
不适用与高并发性的数据库操作,但这种事情不会发生在iPhone上)
//SQLite uses reader/writer locks on the entire database file. SQLite 对整个数据库文件使用了读写锁。
//That means if any process is reading from any part of the database, all other processes are prevented from writing any other part of the database. 
//Similarly, if any one process is writing to the database, all other processes are prevented from reading any other part of the database. 
//这意味着如果任何进程读取数据库的任何一个部分，所有其他进程被阻止写数据库的任何其他部分。同样，如果任何一个进程写数据库，所有其他进程无法读取数据库的任何其他部分。
//For many situations, this is not a problem. Each application does its database work quickly and moves on, and no lock lasts for more than a few dozen milliseconds. But there are some applications that require more concurrency, and those applications may need to seek a different solution.
//对于许多情况下，这是没有问题的。每个应用程序的数据库工作迅速，动作上，并没有锁定持续时间超过几十毫秒。但也有一些应用，需要更多的并发，和这些应用程序可能需要寻求不同的解决方案。
Client-server applications


SQLite是基于C的API，在iPhone中的运行速度超级快（在苹果网站上也有一个对比，确实应该是速度最快的）。
SQLite is not designed to replace Oracle.
由于在iPhone3.0上已经支持了Core Data，是苹果一个新的API，并且是基于SQlite的。速度也是非常快吧，信不信由你。所以我们对SQLite仅需要懂一些即可，以下是一些基础信息

//============

首先在FrameWorks  中加入SQLite 的库:  lib/libsqlite3.dylib 

完整路径如下：
/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS3.0.sdk/usr/lib/libsqlite3.dylib

然后包含头文件#import <sqlite3.h>

一般操作：


//=============

//databasePath 数据库路径

//database 数据库名

int n = sqlite3_open([databasePath UTF8String], &database);   //打开数据库

if(n != SQLITE_OK){ //判断数据库是否打开
	
	NSLog(@"can not open the database");
	
	return;
	
}

//执行sql 语句

sqlite3_stmt *stmt;

char *sql = "SELECT TimeDesc FROM tblTime WHERE isActivated=1";  //sql 语句

sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);

int code = sqlite3_step(stmt);



NSMutableArray *arrayData = [[NSMutableArray alloc] init];

NSMutableDictionary *dicTimeDesc  = [[NSMutableDictionary alloc] init];

//把sql 语句的查询结果存储到 NSMutableArray 中

while (code == SQLITE_ROW) {
	
	char *c;
	
	NSString *s;
	
	c = (char *)sqlite3_column_text(stmt, 0);
	
	s = [NSString stringWithUTF8String:c];
	
	[dicTimeDesc setObject:s forKey:@"TimeDesc"];
	
	[s release];
	
	//int n;
	
	//n = sqlite3_column_int(stmt2,0);
	
	[arrayData addObject:dicTimeDesc];
	
	code = sqlite3_step(stmt);
	
}

sqlite3_finalize(stmt); 

sqlite3_close(database);  //关闭数据库



//带参数的sql 语句
sqlite3_stmt *stmt;
char *sql = "SELECT SNo,BrandName,PicFileName,FolderGUID,PicDesc,PicDescLocation,IconSpecName,StyleName,PicFileName_H FROM tblProduct where BrandName = ? order by SNo";
sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);
sqlite3_bind_text(stmt, 1, [brandName UTF8String], -1, SQLITE_TRANSIENT);
//
NSMutableDictionary *d;
char *c;
NSString *s;
//
int code = sqlite3_step(stmt);
while (code == SQLITE_ROW) {
	//sql 语句检索结果
	
}

//=========
//执行事务
@try {
	sqlite3_exec(database,"BEGIN TRANSACTION",0,0,0);  //事务开始
    NSString *s = [[NSString alloc] initWithUTF8String:[要执行的sql 语句  UTF8String]];
    char *sql = (char *) [s UTF8String];
    int r = sqlite3_exec( database, sql , 0, 0, 0 );
    if(r != SQLITE_OK){
		//NSLog(@" sql: %@" ,s);
		//NSLog(@"r = %d",r);
    }
    NSLog(@"updateSql %@",ssql);
    NSLog(@"r = %d",r);
    [s release];
}
@catch (NSException * em) {
    NSLog(@"failed to read %@",[em description]);
}
@finally {
    //NSLog(@"failed to read %@",[e description]);
}
}
int result = sqlite3_exec(database,"COMMIT",0,0,&error); //COMMIT


//==============

//以下内容为网络上摘取的，我没经过验证，可以做为参考

【1】打开数据库，如果没有，那么创建一个

sqlite3* database_;

-(BOOL) open{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *path = [documentsDirectory stringByAppendingPathComponent:@"mydb.sql"];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL find = [fileManager fileExistsAtPath:path];
	
    //找到数据库文件mydb.sql
    if (find) {
        NSLog(@"Database file have already existed.");
        if(sqlite3_open([path UTF8String], &database_) != SQLITE_OK) {
            sqlite3_close(database_);
            NSLog(@"Error: open database file.");
            return NO;
        }
        return YES;
    }
    if(sqlite3_open([path UTF8String], &database_) == SQLITE_OK) {
        bFirstCreate_ = YES;
        [self createChannelsTable:database_];//在后面实现函数createChannelsTable
		
        return YES;
    } else {
        sqlite3_close(database_);
        NSLog(@"Error: open database file.");
        return NO;
    }
    return NO;
}

【2】创建表格

//创建表格，假设有五个字段，（id，cid，title，imageData ，imageLen ）

//说明一下，id为表格的主键，必须有。

//cid，和title都是字符串，imageData是二进制数据，imageLen 是该二进制数据的长度。
- (BOOL) createChannelsTable:(sqlite3*)db{
    char *sql = "CREATE TABLE channels (id integer primary key, \
	cid text, \
	title text, \
	imageData BLOB, \
	imageLen integer)";
    sqlite3_stmt *statement;
    if(sqlite3_prepare_v2(db, sql, -1, &statement, nil) != SQLITE_OK) {
        NSLog(@"Error: failed to prepare statement:create channels table");
        return NO;
    }
    int success = sqlite3_step(statement);
    sqlite3_finalize(statement);
    if ( success != SQLITE_DONE) {
        NSLog(@"Error: failed to dehydrate:CREATE TABLE channels");
        return NO;
    }
    NSLog(@"Create table 'channels' successed.");
    return YES;
}



【3】向表格中插入一条记录

假设channle是一个数据结构体，保存了一条记录的内容。

- (BOOL) insertOneChannel:(Channel*)channel{
    NSData* ImageData = UIImagePNGRepresentation( channel.image_);
    NSInteger Imagelen = [ImageData length];
    sqlite3_stmt *statement;
    static char *sql = "INSERT INTO channels (cid,title,imageData,imageLen)\
	VALUES(?,?,?,?)";
	
    //问号的个数要和(cid,title,imageData,imageLen)里面字段的个数匹配，代表未知的值，将在下面将值和字段关联。
    int success = sqlite3_prepare_v2(database_, sql, -1, &statement, NULL);
    if (success != SQLITE_OK) {
        NSLog(@"Error: failed to insert:channels");
        return NO;
    }
	
	
	//这里的数字1，2，3，4代表第几个问号
    sqlite3_bind_text(statement, 1, [channel.id_ UTF8String], -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, [channel.title_ UTF8String], -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob(statement, 3, [ImageData bytes], Imagelen, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 4, Imagelen);    
	
	
    success = sqlite3_step(statement);
    sqlite3_finalize(statement);
    
    if (success == SQLITE_ERROR) {
        NSLog(@"Error: failed to insert into the database with message.");
        return NO;
    } 
	
	NSLog(@"Insert One Channel#############:id = %@",channel.id_);
    return YES;
}



【4】数据库查询

这里获取表格中所有的记录，放到数组fChannels中。

- (void) getChannels:(NSMutableArray*)fChannels{
    sqlite3_stmt *statement = nil;
    char *sql = "SELECT * FROM channels";
    if (sqlite3_prepare_v2(database_, sql, -1, &statement, NULL) != SQLITE_OK) {
        NSLog(@"Error: failed to prepare statement with message:get channels.");
    }
    //查询结果集中一条一条的遍历所有的记录，这里的数字对应的是列值。
    while (sqlite3_step(statement) == SQLITE_ROW) {
        char* cid       = (char*)sqlite3_column_text(statement, 1);
        char* title     = (char*)sqlite3_column_text(statement, 2);
        Byte* imageData = (Byte*)sqlite3_column_blob(statement, 3);
        int imageLen    = sqlite3_column_int(statement, 4);        
        Channel* channel = [[Channel alloc] init];
        if(cid)
            channel.id_ = [NSString stringWithUTF8String:cid];
        if(title)
            channel.title_ = [NSString stringWithUTF8String:title];
        if(imageData){
            UIImage* image = [UIImage imageWithData:[NSData dataWithBytes:imageData length:imageLen]];
            channel.image_ = image;
        }
		[fChannels addObject:channel];
        [channel release];
    }
    sqlite3_finalize(statement);
}



//===================

打开数据库

sqlite3 *database = NULL; //建立一个sqlite数据库变量

int sqlite3_open(const char *文件名, sqlite3 **db); //那个文件名需要是cString，
//之后那个db对象使用我们建立的database变量

//以下是一个开打的例子：
NSString *fileAddress = [[NSBundle mainBundle] pathForResource:@"预存文件的文件名" ofType:@"db"]; //db是扩展名

if(sqlite3_open([fileAddress UTF8String], &amp;database) == SQLITE_OK) //UTF8String方法转换NSString为cString
执行一个SQLite语句：

int sqlite3_exec(sqlite3 *db, const char *sql, int (*callback)(void*,int,char**,char**), void *context, char **error);
关闭一个数据库：

int sqlite3_close(sqlite3 *db); //这个不用解释了吧
一个响应函数的格式：

int callback(void *context, int count, char **values, char **columns);

