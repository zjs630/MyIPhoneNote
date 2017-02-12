Maps is new to the 3.0 SDK. //Maps是SDK 3.0的新东西。
1,创建Map View
#import <MapKit/MapKit.h>

MKMapView *mapView = [[MKMapView alloc] initWithFrame:CGRectMake(0, 0, 320, 460)];

//设置经纬度的代码
//声明坐标 
CLLocationCoordinate2D coordinate;
coordinate.latitude=24.148926;//设置纬度
coordinate.longtitude=124.148926;//设置经度

//设置地图显示范围代码如下：
//声明span
MKCoordinateSpan theSpan;
theSpan.latitudeDelta = 0.1;//设置纬度范围
theSpan.longtitude = 0.1;//设置经度范围

//设置地图显示的中心和范围
//声明范围
MKCoordinateRegion theRegion;
theRegion.center = coordinate;
theRegion.span = theSpan;
mapView.region = theRegion;

mapView.showsUserLocation = YES;//显示用户的位置
mapView.mapType = MKMapTypeSatellite;//设置地图的类型，标准，卫星，混合。
mapView.delegate = self;
[self.view addSubview:mapView];
[mapView release];


//2，添加标注
CLLocationCoordinate2D coordinate1 = {39.8,116};
NSDictionary *address = [NSDictionary dictionaryWithObjectsAndKeys:@"中国123",@"Country", nil];
MKPlacemark *rome = [[MKPlacemark alloc] initWithCoordinate:coordinate1 addressDictionary:address];
[mapView addAnnotation:rome];

2,Callback methods about loading state
- (void)mapViewWillStartLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFinishLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFailLoadingMap:(MKMapView *)mapView withError:(NSError *)error;
3,Callback methods about    region changes//区域改变，放大，缩小
- (void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated;
4，Callback methods to customize and interact with "annotations"
//创建注解试图
- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;
//当一个地图有一些注解试图
- (void)mapView:(MKMapView *)mapView didAddAnnotationViews:(NSArray *)views;
- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;





MapKit框架：
主要提供了四个功能：显示地图、CLLocation和地址之间的转换、支持在地图上做标记（比如标记北京天安门广场）、把一个位置解析成地址（比如我在水立方，想要知道确切的地址信息）。
MKMapView类：主要是完成下述功能：
-------显示地图，比如：显示北京市的地图；
-------提供多种显示方式，比如标准地图格式，卫星地图等；
-------支持地图的放大缩小；
-------支持在地图上做标记，比如标记天安门广场；
-------在地图上显示手机所在的当前位置。
MKMapView类的属性有：
@property MKCoordinateRegin region; //地图所显示的区域
@property CLLocationCoordinate2D centerCoordinate; //经度和纬度确定的中心位置
@property MKMapView mapType; //地图的显示类型，如：卫星地图
@property NSArray *annotations; //地图上的标记
@property MKUserLocation userLocation; //用户位置
@property id <MKMapViewDelegate>delegate; //委托类


装载地图时的回调方法有：
-(void)mapViewWillStartLocationMap:(MKMapView *) mapView; //开始装载地图
-(void)mapViewDidFinishLocationMap:(MKMapView  *)mapView; //结束装载地图
-(void)mapVewDidFailLoadingMap:(MKMapView *)mapView withError:(NSError *)error; //装载失败


当位置发生转变时的回调方法：
-(void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated; //将要更改
-(void)mapView: (MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated; //已经更改














