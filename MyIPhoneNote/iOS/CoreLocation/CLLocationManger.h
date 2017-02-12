1,allow you to get the current location of the user.
if ([CLLocationManager locationServicesEnabled]) {//locationServicesEnabled class method of CLLocationManager is available in sdk 4.0 and later.
    CLLocationManager *myLocationManager = [[CLLocationManager alloc] init];
    myLocationManager.delegate = self;
    myLocationManager.purpose = @"To provide functionality based on user's current location";
    [myLocationManager startUpdatingLocation];
    
}
else{
    NSLog(@"Location services are not enabled");
}
