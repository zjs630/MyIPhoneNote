1，获取经纬度
a,导入CoreLocation.framework
导入#import <CoreLocation/CoreLocation.h>
添加 <CLLocationManagerDelegate>协议
b,- (void)viewDidLoad {
    CLLocationManager *locationManager = [[CLLocationManager alloc] init];//创建位置管理对象
    locationManager.delegate = self; //设置委托
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;//设置精确度
    [locationManager startUpdatingLocation];//启动位置管理器//开始更新
    //    [locationManager stopUpdatingLocation];//停止服务
}
c,
- (void)locationManager:(CLLocationManager *)manager 
didUpdateToLocation:(CLLocation *)newLocation 
fromLocation:(CLLocation *)oldLocation {
    
    
    NSTimeInterval howRecent = [newLocation.timestamp timeIntervalSinceNow];
    if(howRecent < -10) return;
    
    if(newLocation.horizontalAccuracy >100) return;
    
    
    if (startingPoint == nil)
        self.startingPoint = newLocation;
    /*
     CLLocationCoordinate2D loc = [newLocation coordinate];
     
     latitude.text = [NSString stringWithFormat: @"%f", loc.latitude];//纬度
     longitude.text = [NSString stringWithFormat: @"%f", loc.longitude];//经度
     altitude.text = [NSString stringWithFormat: @"%f", newLocation.altitude];//海拔高度	 
     */
    /*
     newLocation.coordinate.latitude//纬度
     newLocation.coordinate.longitude//经度
     newLocation.altitude//海拔高度
     newLocation.horizontalAccuracy//
     newLocation.verticalAccuracy//
     */
        //获得移动距离
        CLLocationDistance distance = [newLocation distanceFromLocation:startingPoint];
        NSString *distanceString = [[NSString alloc]
                                    initWithFormat:@"%gm", distance];
        distanceTraveledLabel.text = distanceString;
        [distanceString release];
}
d,stopping the service
[];

2,有3种方式确定位置。//准确度依次递减，定位花费的时间约来越少。准确度越高，约消耗的电量越大,。
a,GPS.//id down to the meter.
b,Wifi
c,Cell Network //默认优先使用蜂窝网络，如果没有此网络，it will go to the WIFI
3，具体通过什么方式定位，要依据你设置的准确度（accuracy）。
so when you tell the locatinManager that you want it accurate within a meter. it will automatically go and use the GPS.

它能很快的找出你在cell network 中的位置，
而它需要多一些的时间去找出在WIFI网络中的位置。
它需要更多的时间找出你在GPS网络中的位置。











