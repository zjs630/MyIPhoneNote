#import </usr/include/sqlite3.h>

#define kFilename @"data.sqlite3"

1.打开数据库操作
-(void)openDB {
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);

    NSString *documentsDirectory = [paths objectAtIndex:0];

	NSString *dataFilePath =  [documentsDirectory stringByAppendingPathComponent:kFilename];

	if (sqlite3_open([dataFilePath UTF8String], &database) != SQLITE_OK) {

		sqlite3_close(database);
	
	}

}

2.创建表，结构，类型
- (void)initDB {
		char *errorMsg;

	NSString *sql = @"CREATE TABLE IF NOT EXISTS USER (USER_ID INTEGER PRIMARY KEY,USERNAME TEXT,PASSWORD TEXT);";
	
	if (sqlite3_exec(database, [sql UTF8String], NULL, NULL, &errorMsg) != SQLITE_OK) {
		
		sqlite3_close(database);
	
	}

}

3.执行添加方法

- (void)insertUsername:(NSString *)username insertPassword:(NSString *)password {
	
	[self openDB];//调用打开库
	
	[self initDB];//调用创建表
	char *errorMsg;
	
	char *update = "INSERT OR REPLACE INTO USER (USERNAME,PASSWORD) VALUES (?,?);";//添加语句

	NSString *sql = [NSString stringWithFormat:@"SELECT USERNAME,PASSWORD FROM USER"];//查询语句
		sql = @"DELETE FROM USER;";//删除语句
	sqlite3_stmt *statement;
	
	if (sqlite3_prepare_v2(database, update, -1, &statement, nil) == SQLITE_OK) {
	
		sqlite3_bind_text(statement, 1, [username UTF8String], -1, SQLITE_TRANSIENT);
	
		sqlite3_bind_text(statement, 2, [password UTF8String], -1, SQLITE_TRANSIENT);
		
	}
	
	if (sqlite3_step(statement) != SQLITE_DONE)
		
		NSAssert1(0,@"Error updating table:%s",errorMsg);
		
		sqlite3_finalize(statement);
		
		sqlite3_close(database);
		}
///////////////////////////////////////////////////////////////////////
IPhone数据库操作代码例子

//database operation
打开数据库

-(BOOL) opendatabase{
	
	NSArray *paths =NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *path = [documentsDirectorystringByAppendingPathComponent:@"mydb.sql"];
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
		//bFirstCreate_ = YES;
		 [self createChannelsTable:database_];//在后面实现函数createChannelsTable
		  return YES;
	} else {
		 sqlite3_close(database_);
		 NSLog(@"Error: open database file.");
		 return NO;
	}
	return NO;
}

创建表

- (BOOL) createChannelsTable:(sqlite3*)db{
	char *sql = "CREATE TABLE reports (id integer primary key,stime  text,stitle text,scal   text,sruntime text)";
	sqlite3_stmt *statement;
	if(sqlite3_prepare_v2(db, sql, -1, &statement, nil) != SQLITE_OK) {
		  NSLog(@"Error: failed to prepare statement:create reports table");
		  return NO;
	}
	int success = sqlite3_step(statement);
	sqlite3_finalize(statement);
	if ( success != SQLITE_DONE) {
		 NSLog(@"Error: failed to dehydrate:CREATE TABLE reports");
		 return NO;
	}
	NSLog(@"Create table 'reports' successed.");
	return YES;
}

插入表 

- (BOOL)insertOneChannel:(NSString*)stime mytitle:(NSString*)stitle mycal:(NSString*)scal myruntime:(NSString*)sruntime
{
	
	sqlite3_stmt *statement;
	static char *sql = "INSERT INTO reports (id,stime,stitle,scal,sruntime) VALUES(NULL,?,?,?,?)";
	//问号的个数要和(cid,title,imageData,imageLen)里面字段的个数匹配，代表未知的值，将在下面将值和字段关联。
	int success = sqlite3_prepare_v2(database_, sql, -1, &statement,NULL);
	if (success != SQLITE_OK) {
		 NSLog(@"Error: failed to insert:channels");
		  return NO;
	}
	//这里的数字1，2，3，4代表第几个问号
	//sqlite3_bind_text(statement, 1, stime, -1, SQLITE_TRANSIENT);
	char *p = [stime cStringUsingEncoding:1];
	sqlite3_bind_text(statement, 1, [stime cStringUsingEncoding:1], -1,SQLITE_TRANSIENT);
	sqlite3_bind_text(statement, 2, [stitle cStringUsingEncoding:1], -1,SQLITE_TRANSIENT);
	sqlite3_bind_text(statement, 3, [scal cStringUsingEncoding:1], -1,SQLITE_TRANSIENT);
	sqlite3_bind_text(statement, 4, [sruntime cStringUsingEncoding:1], -1, SQLITE_TRANSIENT);
	
	success = sqlite3_step(statement);
	sqlite3_finalize(statement);
	if (success == SQLITE_ERROR) {
		  NSLog(@"Error: failed to insert into the database with message.");
		 return NO;
	}
	NSLog(@"Insert One Channel#############:id = _");
	return YES;
}

查询表
- (void) getChannels:(NSMutableArray*)fChannels{
	sqlite3_stmt *statement = nil;
	char *sql = "SELECT * FROM reports";
	if (sqlite3_prepare_v2(database_, sql, -1, &statement, NULL) !=SQLITE_OK) {
		 NSLog(@"Error: failed to prepare statement with message:get channels.");
	}
	//查询结果集中一条一条的遍历所有的记录，这里的数字对应的是列值。
	while (sqlite3_step(statement) == SQLITE_ROW) {
		//char* cid = (char*)sqlite3_column_text(statement, 1);
		 char* stime = (char*)sqlite3_column_text(statement, 1);
		 char* stitle =(char*)sqlite3_column_text(statement, 2);
		 char* scal = (char*)sqlite3_column_text(statement, 3);
		 char* sruntime= (char*)sqlite3_column_text(statement, 4);
		
		 //NSString *tmp = [NSString stringWithCString:stitle encoding:1];
		  myreportitem* ri = [[myreportitem alloc] init];
		 ri.mytime = [NSString stringWithCString:stime encoding:1];
		  ri.mytitle = [NSString stringWithCString:stitle encoding:1];
		  ri.mycal = [NSString stringWithCString:scal encoding:1];
		 ri.myruntime = [NSString stringWithCString:sruntime encoding:1];
		
		 [fChannels addObject:ri];
		 [ri release];
	}
	sqlite3_finalize(statement);
}
删除记录
- (void)doClearReport: {
	    
	NSArray *paths =NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	NSString *path = [documentsDirectorystringByAppendingPathComponent:@"mydb.sql"];
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
		 char *sql = "delete from reports";
		  sqlite3_stmt *statement;
		  if(sqlite3_prepare_v2(database_, sql, -1, &statement, nil) !=SQLITE_OK) {
			  NSLog(@"Error: failed to prepare statement:create reports table");
			  return NO;
			  }
		  int success = sqlite3_step(statement);
		 sqlite3_finalize(statement);
		  if ( success != SQLITE_DONE) {
			 NSLog(@"Error: failed to dehydrate:delete TABLE reports");
			 return NO;
			   }
		   NSLog(@"Create table 'reports' successed.");
		
		  sqlite3_close(database_);
		
		   }
	
} 