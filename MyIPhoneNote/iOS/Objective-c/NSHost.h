1,what is my IP?

-(NSString *)getAddress {
	
	char iphone_ip[255];
	
    strcpy(iphone_ip,"127.0.0.1"); // if everything fails
	
	NSHost* myhost =[NSHost currentHost];
	
	if (myhost)
	{
		NSString *ad = [myhost address];
		
		if (ad){
			strcpy(iphone_ip,[ad cStringUsingEncoding:NSASCIIStringEncoding]);
			}
	
	return [NSString stringWithFormat:@"%s",iphone_ip];
	
}
