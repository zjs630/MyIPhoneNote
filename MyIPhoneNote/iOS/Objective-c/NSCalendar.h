NSCalendar用法：
-(NSString *) getWeek:(NSDate *) d {
    
    NSCalendar *calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    unsigned units = NSYearCalendarUnit | NSMonthCalendarUnit |  NSDayCalendarUnit | NSWeekdayCalendarUnit;
    NSDateComponents *components = [calendar components:units fromDate:d];
    [calendar release];
    
    switch ([components weekday]) {
        case 2:
            return @"Monday";
            break;
        case 3:
            return @"Tuesday";
            break;
        case 4:
            return @"Wednesday";
            break;
        case 5:
			return @"Thursday";
            break;
        case 6:
            return  @"Friday";
            break;
        case 7:
            return  @"Saturday";
            break;
        case 1:
            return @"Sunday";
            break;
        default:
            return @"No Week";
            break;
    }
	
    // 用components，我们可以读取其他更多的数据。
    
}
