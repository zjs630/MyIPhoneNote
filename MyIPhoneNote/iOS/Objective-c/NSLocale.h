



//get the language & country code
NSLocale *currentLocale = [NSLocale currentLocale];

NSLog(@"Language Code is %@", [currentLocale objectForKey:NSLocaleLanguageCode]);    
NSLog(@"Country Code is %@", [currentLocale objectForKey:NSLocaleCountryCode]);    

