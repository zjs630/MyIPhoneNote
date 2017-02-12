
1,------------CLLocation
CLLocation类代表一个位置信息，其中还包括了方向和速度。比如我在长安街188号以5公里/小时的速度往西走。CLLocation具有下面的属性和方法：
@property  CLLocationCoordinate2D coordinate; //以经度和纬度表示的位置信息
@property CLLocationDistance altitude;  //海拔
@property CLLocationAccuracy horizontalAccuracy; //水平精度（如：精确到米）
@property CLLocationAccuracy verticalAccuracy; //垂直精度
@property CLLocationDirection course; //方向
@property CLLocationSpeed speed; //速度
-（NSDate *）timeStamp;
//两个位置之间的距离
-(CLLocationDistance)distanceFromLocation:(CLLocation *)location;

得到用户的位置 用core lacation框架

你利用地址本和地址本图形界面框架来访问用户联系表信息。详细的这些框架的信息，请参阅：Address Book Framework Reference 和 Address Book UI Framework Reference。

2,
CLLocationManager *lacarionManager = [[CLLocationManager alloc] init];//1.创建位置管理器
locationManager.delegate = self;//2.设置委托和请求精度
locationManager.desireAccuracy = kCLLocationAccuracyBest;//单位为米,除了best外还有NearestTenMeters,hundredMeters,kilometers,threeKilometers
locationManager.distanceFilter = 1000.0f;//3.距离筛选器:即移动了多少米后才通知其委托
//或 ...........................  = kCLDistanceFilterNone; //没有筛选器
[locationManager startUpdatingLocation];//4.启动位置管理器


5.获取经纬度,海拔高度
CLLocationDegrees latitude = theLocation.coordinate.latitude;//纬度
CLLocationDegrees longitude = theLocation.coordinate.longitude;//经度
CLLocationDistance altitude = theLocation.altitude;//海平面多少米

6.确定两个CLLocation对象之间的距离:
CLLocationDistance distance = [fromLocation getDistanceFrom:toLocation];

7.获取当前位置的更新
locationManager: didUpdataTolocation: fromLocation:
8.错误通知
locationManager: didFailWithError: 




例子中的.

- (void)viewDidLoad {
    self.locationManager = [[CLLocationManager alloc] init];
    locationManager.delegate = self;      //将我们的控制器作为委托
	locationManager.desiredAccuracy = kCLLocationAccuracyBest;//设置精度
    [locationManager startUpdatingLocation]; //开始更新
}


#pragma mark -
#pragma mark CLLocationManagerDelegate Methods

- (void)locationManager:(CLLocationManager *)manager 
didUpdateToLocation:(CLLocation *)newLocation 
fromLocation:(CLLocation *)oldLocation {
    
    if (startingPoint == nil)               //检查startingPoint是否为nil
        self.startingPoint = newLocation;
		
		NSString *latitudeString = [[NSString alloc] initWithFormat:@"%g°", 
									newLocation.coordinate.latitude];
		latitudeLabel.text = latitudeString;
		[latitudeString release];
    
    NSString *longitudeString = [[NSString alloc] initWithFormat:@"%g°", 
                                 newLocation.coordinate.longitude];
    longitudeLabel.text = longitudeString;
    [longitudeString release];
    
    NSString *horizontalAccuracyString = [[NSString alloc]
                                          initWithFormat:@"%gm", 
                                          newLocation.horizontalAccuracy];
    horizontalAccuracyLabel.text = horizontalAccuracyString;
    [horizontalAccuracyString release];
    
    NSString *altitudeString = [[NSString alloc] initWithFormat:@"%gm", 
                                newLocation.altitude];
    altitudeLabel.text = altitudeString;
    [altitudeString release];
    
    NSString *verticalAccuracyString = [[NSString alloc]
                                        initWithFormat:@"%gm", 
                                        newLocation.verticalAccuracy];
    verticalAccuracyLabel.text = verticalAccuracyString;
    [verticalAccuracyString release];
    
    CLLocationDistance distance = [newLocation
                                   getDistanceFrom:startingPoint];
    NSString *distanceString = [[NSString alloc]
                                initWithFormat:@"%gm", distance];
    distanceTraveledLabel.text = distanceString;
    [distanceString release];
}

- (void)locationManager:(CLLocationManager *)manager 
didFailWithError:(NSError *)error {
    
    NSString *errorType = (error.code == kCLErrorDenied) ? 
    @"Access Denied" : @"Unknown Error";
    UIAlertView *alert = [[UIAlertView alloc] 
                          initWithTitle:@"Error getting Location" 
                          message:errorType 
                          delegate:nil 
                          cancelButtonTitle:@"Okay" 
                          otherButtonTitles:nil];
    [alert show];
    [alert release];
    
}
@end

8，地理位置，用wifi连接网络，采用系统自带的CoreLocation.framework直接获取的坐标，不是太准，以至于解析后的地理位置信息与真是情况偏差挺大。

采用MapKit.framework,获取到的坐标比较精确，不过要加载地图对象。



