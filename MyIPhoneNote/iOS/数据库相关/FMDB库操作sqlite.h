今天第一次学习FMDB，实现了增删查改，列几个例子供大家参考
创建，插入，更新和删除:使用executeUpdate方法，而查询则用executeQuery
1.实例化FMDatabase
//paths： ios下Document路径，Document为ios中可读写的文件夹
NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
NSString *documentDirectory = [paths objectAtIndex:0];
//dbPath： 数据库路径，在Document中。
NSString *dbPath = [documentDirectory stringByAppendingPathComponent:@"Test.db"];
//创建数据库实例 db  这里说明下:如果路径中不存在"Test.db"的文件,sqlite会自动创建"Test.db"
FMDatabase *db= [FMDatabase databaseWithPath:dbPath] ;
if (![db open]) {
    NSLog(@"Could not open db.");
    return ;
}

2.创建表
//创建一个名为User的表，有两个字段分别为string类型的Name，integer类型的 Age
[db executeUpdate:@"CREATE TABLE User (Name text,Age integer)"];

3.插入
//插入数据使用OC中的类型 text对应为NSString integer对应为NSNumber的整形
[db executeUpdate:@"INSERT INTO User (Name,Age) VALUES (?,?)",@"张三",[NSNumber numberWithInt:20]];

4.更新
//更新数据 将“张三”更改为“李四”
[db executeUpdate:@"UPDATE User SET Name = ? WHERE Name = ? ",@"李四",@"张三"];

5.删除
//删除数据
[db executeUpdate:@"DELETE FROM User WHERE Name = ?",@"张三"];

6.查询
//返回数据库中第一条满足条件的结果
NSString *aa=[db stringForQuery:@"SELECT Name FROM User WHERE Age = ?",@"20"];
//查询前10条数据
FMResultSet *s = [db executeQuery:@"SELECT * FROM ListTable order by db_id desc limit 0,10"];
//翻页 "select * from ListTable where db_id < 4 order by db_id desc limit 0,2"

//返回全部查询结果
FMResultSet *rs=[db executeQuery:@"SELECT * FROM User"];
rs=[db executeQuery:@"SELECT * FROM User WHERE Age = ?",@"20"];
while ([rs next]){
    NSLog(@"%@ %@",[rs stringForColumn:@"Name"],[rs stringForColumn:@"Age"]);
}
[rs close];




2011-09-17 21:18:28|  分类： 默认分类 |字号 订阅
iPhone应用数据存储Sqlite3第三方框架FMDB是本文要介绍的内容，在iPhone上是采用sqlite进行数据存储是我一种比较习惯性的做法。一般在其他平台也比较习惯用sqlite，比如android。

而iphone上有一些封装好的第三方框架提供使用，更节省了许多时间。如：Sqlitepersistentobjects ，FMDB 。今天查找了这个两个框架，感觉FMDB的风格更符合我的使用，其实两者是各有优点的，只是看个人喜好而已。

以下是FMDB的一些基本使用，FMDB框架其实只是一层很薄的封装，主要的类也就两个：FMDatabase和FMResultSet ；

其中的FMResultSet对象让我想起了android中sqlite的cursor集合啊。

FMDB的github地址是，https://github.com/ccgus/fmdb。

首先得实例化一个FMDatabase对象，这跟 Sqlitepersistentobjects 派生一个子类进行操作是不同。接着打开一个数据库（如果没有会创建一个数据库）

//paths： ios下Document路径，Document为ios中可读写的文件夹     
NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);    
NSString *documentDirectory = [paths objectAtIndex:0];    
//dbPath： 数据库路径，在Document中。     
NSString *dbPath = [documentDirectory stringByAppendingPathComponent:@"Test.db"];    
//创建数据库实例 db  这里说明下:如果路径中不存在"Test.db"的文件,sqlite会自动创建"Test.db"     
FMDatabase *db= [FMDatabase databaseWithPath:dbPath] ;    
if (![db open]) {    
    NSLog(@"Could not open db.");    
    return ;    
}    
//paths： ios下Document路径，Document为ios中可读写的文件夹  
NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);  
NSString *documentDirectory = [paths objectAtIndex:0];  
//dbPath： 数据库路径，在Document中。  
NSString *dbPath = [documentDirectory stringByAppendingPathComponent:@"Test.db"];  
//创建数据库实例 db  这里说明下:如果路径中不存在"Test.db"的文件,sqlite会自动创建"Test.db"  
FMDatabase *db= [FMDatabase databaseWithPath:dbPath] ;  
if (![db open]) {  
    NSLog(@"Could not open db.");  
    return ;  
}    
接下来，我们可以通过这个数据库对象进行操作了。操作主要是update和queries。

首先是创建表。

//创建一个名为User的表，有两个字段分别为string类型的Name，integer类型的 Age   
[db executeUpdate:@"CREATE TABLE User (Name text,Age integer)"];    
//创建一个名为User的表，有两个字段分别为string类型的Name，integer类型的 Age  
[db executeUpdate:@"CREATE TABLE User (Name text,Age integer)"];  
这样我们就有了一张表了。接下我们对表进行操作。插入数据！注意插入的数据使用了通配符，这跟iphone直接使用sqlite借口的绑定变量是一样的，后面的通配符匹配的数据。

//插入数据使用OC中的类型 text对应为NSString integer对应为NSNumber的整形     
[db executeUpdate:@"INSERT INTO User (Name,Age) VALUES (?,?)",@"老婆",[NSNumber numberWithInt:20]]    
//插入数据使用OC中的类型 text对应为NSString integer对应为NSNumber的整形  
[db executeUpdate:@"INSERT INTO User (Name,Age) VALUES (?,?)",@"老婆",[NSNumber numberWithInt:20]]  
接下来是更新数据。

//更新数据 将“老婆”更改为“宝贝”     
[db executeUpdate:@"UPDATE User SET Name = ? WHERE Name = ? ",@"老婆",@"宝贝"];    
//更新数据 将“老婆”更改为“宝贝”  
[db executeUpdate:@"UPDATE User SET Name = ? WHERE Name = ? ",@"老婆",@"宝贝"];  
再接下来，就是删除数据啦。

//删除数据     
[db executeUpdate:@"DELETE FROM User WHERE Name = ?",@"老婆"];    
//删除数据  
[db executeUpdate:@"DELETE FROM User WHERE Name = ?",@"老婆"];  
update的基本操作就这几个，接下来是queries!

//返回数据库中第一条满足条件的结果
NSString *aa=[db stringForQuery:@"SELECT Name FROM User WHERE Age = ?",@"20"];  
这样我们就查询返回了一条数据，那当我们想要查询放返回多条数据怎么办呢？不用愁，之前我就提到了FMDB中的另外一个主要的类，FMResultSet，这是一个结果集！返回多条数据时FMDB会将数据放在这个结果集中，然后我们在对这个结果集进行查询操作！很简单。

FMResultSet *rs=[db executeQuery:@"SELECT * FROM User"];    
rs=[db executeQuery:@"SELECT * FROM User WHERE Age = ?",@"20"];    
while ([rs next]){    
    NSLog(@"%@ %@",[rs stringForColumn:@"Name"],[rs stringForColumn:@"Age"]);    
}    
FMResultSet *rs=[db executeQuery:@"SELECT * FROM User"];  
rs=[db executeQuery:@"SELECT * FROM User WHERE Age = ?",@"20"];  
while ([rs next]){  
    NSLog(@"%@ %@",[rs stringForColumn:@"Name"],[rs stringForColumn:@"Age"]);  
}  
更多的 FMResultSet方法有：

intForColumn:   
longForColumn:   
longLongIntForColumn:   
boolForColumn:   
doubleForColumn:   
stringForColumn:   
dateForColumn:   
dataForColumn:   
dataNoCopyForColumn:   
UTF8StringForColumnIndex:   
objectForColumn:  
具体查看一下类就行了！ 好了，对于FMDB的使用就这样，是不是很简单呢，其实这个些封装sqlite的框架都是万变不离其宗的，只要你掌握了sql就行了！
