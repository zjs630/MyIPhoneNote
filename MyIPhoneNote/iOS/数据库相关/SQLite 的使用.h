1,创建一个新的数据库。
	在shell或DOS提示符，输入：sqlite3 test.db。／／这将创建一个新的数据库，名为“test.db”
2,创建表并插入数据
begin transaction;
CREATE TABLE person (id INTEGER PRIMARY KEY,name TEXT);
//create table if not exists person(id integer primary key, name text);
INSERT INTO "person"(name) VALUES('ZhangJingshun');
INSERT INTO "person"(name) VALUES('Yu Bing');
INSERT INTO "person"(name) VALUES('Xing Chaomin');
INSERT INTO "person"(name) VALUES('Wang Tao');
INSERT INTO "person"(name) VALUES('Tao Lidong');
COMMIT;

//查看表数据
select * from person;
//删除某条数据
delete from person where name='Wang Tao';
//更新某条数据
update person set name = 'Jingshun' where name = 'ZhangJingshun';
3，删除表
drop table if exists person;
4.shell下常用的命令：
	退出SQL命令：quit or exit
	查看执行的Sql语句：dump
	查看帮助：help
5,打开数据库sqlite3_open()，执行sql语句sqlite3_exec();关闭数据库sqlite3_close();

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
• Open the database
int sqlite3_open(const char *filename, sqlite3 **db);
如：
//打开一个数据库，如果不存在则创建一个数据。
sqlite3 *database;
int result = sqlite3_open("/path/to/database/file",&database);
//如果result结果为SQLITE_OK,则表示数据库打开成功。数据库的路径必须是c字符串传递。

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
• Execute a SQL statement
int sqlite3_exec(sqlite3 *db, const char *sql, int (*callback)(void*,int,char**,char**),void *context, char **error);
// Your callback int callback(void *context, int count,char **values, char **columns);
例：在打开的数据库中，创建一个表
char *errorMsg;
const char *createSQL = "create table if not exists people
						(id integer primary key autoincrement, field_data text)";
int result = sqlite3_exec (database,createSQL,NULL,NULL,&errorMsg);
//函数sqlite3_exec用于不返回数据的命令。它用于执行更新，插入和删除操作。
//进行查询操作需要准备sql语句。
	NSString *query = @"select id,field_data from people";
sqlite3_stmt *statement;
int result = (sqlite3_prepare_v2(database,[query UTF8String],-1,&statement,nil));
//如果result等于SQLITE_OK,则表示语句准备成功，你可以单步调试结果集,取每行的数据
while (sqlite3_step(statement)==SQLITE_ROW){
	int rowNum = sqlite3_column_int(statement,0);
	char *rowData = (char *)sqlite3_column_text(statement, 1);
	NSString *fieldValue = [[NSString alloc] initWithUTF8String:rowData];
	//Do something with the data here
	[fieldValue release];
}
sqlite3_finalize(statement);

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
• Close the database
int sqlite3_close(sqlite3 *db);


6,创建一个使用SQLite3的项目
a,首先要把libsqlite3.dylib添加到项目中。
b,导入头文件#import <sqlite3.h>
	//定义sqlite3 实例变量
	sqlite3 *database;
c,加载数据库中的数据
- (void)viewDidLoad {
    //如果数据库不存在创建一个。若存在直接打开，返回SQLITE_OK，则打开数据库成功。出错，关闭数据库。
    if (sqlite3_open([[self dataFilePath] UTF8String], &database)!= SQLITE_OK) {
        sqlite3_close(database);
        NSAssert(0, @"Failed to open database");
    }
    //如果fields表不存在，则创建一个fields表
    char *errorMsg;
    NSString *createSQL = @"CREATE TABLE IF NOT EXISTS FIELDS (ROW INTEGER PRIMARY KEY, FIELD_DATA TEXT);";
    if (sqlite3_exec (database, [createSQL  UTF8String],
                      NULL, NULL, &errorMsg) != SQLITE_OK) {
        sqlite3_close(database);
        NSAssert1(0, @"Error creating table: %s", errorMsg);
    }
    
    NSString *query = @"SELECT ROW, FIELD_DATA FROM FIELDS ORDER BY ROW";
    sqlite3_stmt *statement;
	//如果Sql语句准备成功，则从结果集中检索数据。
    if (sqlite3_prepare_v2( database, [query UTF8String], -1, &statement, nil) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            int row = sqlite3_column_int(statement, 0);
            char *rowData = (char *)sqlite3_column_text(statement, 1);
            
            NSString *fieldName = [[NSString alloc]
                                   initWithFormat:@"field%d", row];
            NSString *fieldValue = [[NSString alloc]
                                    initWithUTF8String:rowData];
            UITextField *field = [self valueForKey:fieldName];//可以根据其名称检索属性。
            field.text = fieldValue;
            [fieldName release];
            [fieldValue release];
        }
        sqlite3_finalize(statement);
    } 
    
}	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

