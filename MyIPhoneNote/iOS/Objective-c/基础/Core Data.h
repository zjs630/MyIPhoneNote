编译Core Data的程序后，它会自动在Documents文件夹下生成一个与项目名称同名的.sqlite文件。
1,创建新托管对象实例
	theLine = [NSEntityDescription insertNewObjectForEntityForName:@"EntityName" inManagedObjectContext:context];
	