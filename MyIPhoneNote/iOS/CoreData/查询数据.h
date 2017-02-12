//
//  查询数据.h
//  MyIPhoneNote
//
//  Created by ZhangJingshun on 2016/10/26.
//  Copyright © 2016年 天天飞度. All rights reserved.
//

#ifndef _____h
#define _____h
------------------------------ 插入 ---------------------------------------------
---------------------------------------------------------------------------------

Entity *en = [NSEntityDescription insertNewObjectForEntityForName:@"Employee" inManagedObjectContext:self.context];
en.name = @"zjs";
en.age = 31;
en.height = 171;
NSError *error = nil;
[self.context save:&error];
if (!error) {
    NSLog(@"success add");
}else{
    NSLog(@"%@",error);
}

------------------------------ 查询 ---------------------------------------------
---------------------------------------------------------------------------------

// 查询
NSFetchRequest *request = [NSFetchRequest fetchRequestWithEntityName:@"Employee"];

//模糊查询
// 1.查询以wang开头员工
//NSPredicate *pre = [NSPredicate predicateWithFormat:@"name BEGINSWITH %@",@"wang"];

// 2.以si 结尾
//NSPredicate *pre = [NSPredicate predicateWithFormat:@"name ENDSWITH %@",@"si"];

// 3.名字包含 g
//NSPredicate *pre = [NSPredicate predicateWithFormat:@"name CONTAINS %@",@"g"];

// 4.like 以si结尾
NSPredicate *pre = [NSPredicate predicateWithFormat:@"name like %@",@"li*"];
request.predicate = pre;



------------------------------ 排序 ---------------------------------------------
---------------------------------------------------------------------------------

NSSortDescriptor *sort = [NSSortDescriptor sortDescriptorWithKey:@"height" ascending:NO];
request.sortDescriptors = @[sort];


------------------------------ 分页  ---------------------------------------------
---------------------------------------------------------------------------------
request.fetchLimit = 5
request.fetchOffset = 10
------------------------------ 删除张三  -----------------------------------------
---------------------------------------------------------------------------------
//1.查找张三
NSFetchRequest *request = [NSFetchRequest fetchRequestWithEntityName:@"Employee"];
NSPredicate *pre = [NSPredicate predicateWithFormat:@"name=%@",@"zhangsan"];
request.predicate = pre;

//2.删除张三
NSArray *emps = [self.context executeFetchRequest:request error:nil];
for(Employee *emp in emps){
    [self.context deleteObject:emp];
}
//3.用context同步数据库
//所有的操作暂时都是在内存里的，调用save同步到数据库
[self.context save:nil];
------------------------------ 修改张三  -----------------------------------------
---------------------------------------------------------------------------------
//1.查找张三
NSFetchRequest *request = [NSFetchRequest fetchRequestWithEntityName:@"Employee"];
NSPredicate *pre = [NSPredicate predicateWithFormat:@"name=%@",@"zhangsan"];
request.predicate = pre;

NSArray *emps = [self.context executeFetchRequest:request error:nil];
//2.更新
if(emps.count == 1){
    Employee *yee = emps[0];
    yee.heigt = 29;
}
//3.同步保存数据
[self.context save:nil];

#endif /* _____h */
