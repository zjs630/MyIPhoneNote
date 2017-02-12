SQL存储过程的概念，优点及语法
整理在学习程序过程之前，先了解下什么是存储过程?为什么要用存储过程，他有那些优点

　　定义：将常用的或很复杂的工作，预先用SQL语句写好并用一个指定的名称存储起来, 那么以后要叫数据库提供与已定义好的存储过程的功能相同的服务时,只需调用execute,即可自动完成命令。

　　讲到这里,可能有人要问：这么说存储过程就是一堆SQL语句而已啊? Microsoft公司为什么还要添加这个技术呢?

　　那么存储过程与一般的SQL语句有什么区别呢?

　　存储过程的优点：

　　1.存储过程只在创造时进行编译，以后每次执行存储过程都不需再重新编译，而一般SQL语句每执行一次就编译一次,所以使用存储过程可提高数据库执行速度。

　　2.当对数据库进行复杂操作时(如对多个表进行Update,Insert,Query,Delete时)，可将此复杂操作用存储过程封装起来与数据库提供的事务处理结合一起使用。

　　3.存储过程可以重复使用,可减少数据库开发人员的工作量

　　4.安全性高,可设定只有某此用户才具有对指定存储过程的使用权

　　存储过程的种类：

　　1.系统存储过程：以sp_开头,用来进行系统的各项设定.取得信息.相关管理工作,

　　如 sp_help就是取得指定对象的相关信息

　　2.扩展存储过程 以XP_开头,用来调用操作系统提供的功能

　　以下为引用的内容：

　　exec master..xp_cmdshell 'ping 10.8.16.1'

　　3.用户自定义的存储过程,这是我们所指的存储过程

　　常用格式

　　以下为引用的内容：

　　Create procedure procedue_name

　　[@parameter data_type][output]

　　[with]{recompile|encryption}

　　as

　　sql_statement

解释:

　　output：表示此参数是可传回的

　　with {recompile|encryption}

　　recompile:表示每次执行此存储过程时都重新编译一次

　　encryption:所创建的存储过程的内容会被加密

　　二、SQL存储过程学习：存储过程的创建

　　表book的内容如下

　　编号　　　　　书名　　　　　　价格

　　001 　　　C语言入门　　　　　$30

　　002 　PowerBuilder报表开发 $52

　　实例1:查询表Book的内容的存储过程

　　create proc query_book
　　as
　　select * from book
　　go
　　exec query_book

　　实例2:加入一笔记录到表book,并查询此表中所有书籍的总金额

　　Create proc insert_book
　　@param1 char(10),@param2 varchar(20),@param3 money,@param4 money output
　　with encryption ---------加密
　　as
　　insert book(编号,书名，价格) Values(@param1,@param2,@param3)
　　select @param4=sum(价格) from book
　　go
执行例子:

　　declare @total_price money
　　exec insert_book '003','Delphi 控件开发指南',$100,@total_price
　　print '总金额为'+convert(varchar,@total_price)
　　go

　　存储过程的3种传回值:

　　1.以Return传回整数

　　2.以output格式传回参数

　　3.Recordset

　　传回值的区别:

　　output和return都可在批次程式中用变量接收,而recordset则传回到执行批次的客户端中