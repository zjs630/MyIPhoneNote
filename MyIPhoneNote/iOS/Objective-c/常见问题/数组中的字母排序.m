
NSString *myString = @"qwtsedcba";
//for()
//NSRange range = NSMakeRange(4, 3);//第四个开始去3个字符
//	NSString *bString = [numberString substringWithRange:range];
NSMutableArray *myArray = [[NSMutableArray alloc] init];
for(int n=0;n<[myString length];n++)
{
	NSRange range = NSMakeRange(n, 1);
	NSString *subString = [myString substringWithRange:range];
	[myArray insertObject:subString  atIndex:n];
}

int myCount = [myArray count];
int i,j = 1;
for(j;j<myCount;j++)
{
	i=0;
	for(i;i<myCount-j;i++)
	{
		NSString *a =[myArray objectAtIndex:i];
		NSString *b = [myArray objectAtIndex:++i];
		
		if ([a isGreaterThan:b]) {
			[myArray insertObject:a atIndex:++i];
			i--;
			i--;
			[myArray removeObjectAtIndex:i];
		}
		
	}
	for(NSString *obj in myArray){
		NSLog(@"%@",obj);
	}
	
}
