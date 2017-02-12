CoreData multiple conditions
1,
NSPredicate *predicate = [NSPredicate predicateWithFormat:
						  @"(lastName like[cd] %@) AND (birthday > %@)", 
						  lastNameSearchString, birthdaySearchDate];
2、判断邮箱输入的是否正确：

- (BOOL) validateEmail: (NSString *) candidate {
	NSString *emailRegex = @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
	NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", emailRegex];
	return [emailTest evaluateWithObject:candidate];
}
3， 
NSArray *array = [NSArray arrayWithObjects:@"asss jc",@"gg ajb", @"jja", @"jja", @"jja",@"ddd",nil];
NSLog(@"%@",array);
NSPredicate *apredicate = [NSP redicate predicateWithFormat:@"SELF contains[c] 'b'"];//包含b的字符串
NSArray *newArray = [array filteredArrayUsingPredicate:apredicate];
NSLog(@"%@",newArray);
4，Examples
@"uniqueId = %@",[infoDic objectForKey:@"id"]
@"viewed > %@",(NSDate *)date //viewed is a Date attribute in the data mapping
@"whoTook.name = %@",(NSString *)name //Photo search by name
