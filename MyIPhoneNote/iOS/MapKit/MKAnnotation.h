1,MKAnnotation可以实现在指定的坐标点上添加标记。每一个标记包含3个元素：坐标,标题和子标题。

#import <Foundation/Foundation.h>
#import <MapKit/mapkit.h>
#import <CoreLocation/CoreLocation.h>
@interface MyNotation : NSObject<MKAnnotation>{
    //三个元素
    CLLocationCoordinate2D coordinate;
    NSString *subtitle;
    NSString *title;
}
@property(nonatomic,readonly) CLLocationCoordinate2D coordinate;
@property(nonatomic,copy) NSString *subtitle;
@property(nonatomic,copy) NSString *title;

@end

@implementation MyNotation
@synthesize coordinate,subtitle,title;
-(id)initWithCoords:(CLLocationCoordinate2D) coords{
    self = [super init];
    if (self!=nil) {
        coordinate = coords;
    }
    return self;
}

-(void)dealloc{
    self.title = nil;
    self.subtitle = nil;
    [super dealloc];
}
@end

//给mapView加标记资料

-(void)createMapPoint:(MKMapView *)mapView coordinateX:(double)coorX coordinateY:(double)coorY title:(NSString *)title subtitle:(NSString *)subtitle{
    if (mapView) {
        CLLocationCoordinate2D p1;        //定义坐标变量
        MyNotation *poi;
        if (coorX && coorY) {
            p1.latitude = coorX;
            p1.longitude = coorY;
            
            poi = [[MyNotation alloc] initWithCoords:p1];
            poi.title = title;
            poi.subtitle = subtitle;
            [mapView addAnnotation:poi];
            [poi release];
        }
        
    }
    
}

- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation
{
//方法1，用默认的标记图标
//创建初始化MKPinAnnotationView
/*    MKPinAnnotationView *newAnnotication = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"abc"];
    newAnnotication.pinColor = MKPinAnnotationColorRed;//设置大头针的颜色
    newAnnotication.animatesDrop = YES;//是否动画
    newAnnotication.canShowCallout = YES;//设定点选大头针的气泡试图是否会弹出来。
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
    [btn addTarget:self action:@selector(btnTap:) forControlEvents:UIControlEventTouchUpInside];
    newAnnotication.rightCalloutAccessoryView = btn;
    return newAnnotication;

 */   
//方法2,自定义图片作为标记图标   
    /*
     MKAnnotationView *newAnnoticaton = [[MKAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:@"abc"];
     newAnnotication.image = [UIImage imageNamed:@"icon.png"];
     newAnnotication.canShowCallout = YES;
     return newAnnoticaton;
*/
    
    static NSString* AnnotationIdentifier = @"AnnotationIdentifier";
    MKPinAnnotationView* customPinView = (MKPinAnnotationView *)[mapView dequeueReusableAnnotationViewWithIdentifier:AnnotationIdentifier];
    
    if (!customPinView) {
        customPinView = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:AnnotationIdentifier];
        
        customPinView.pinColor = MKPinAnnotationColorRed;
        customPinView.canShowCallout = YES;
        customPinView.draggable = NO;
        
    } else {
        customPinView.annotation = annotation;
    }
    
    return customPinView;
}



- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation
{
    if ([annotation isKindOfClass:[MKUserLocation class]]) {
        return nil;
    }
    
    static NSString* AnnotationIdentifier = @"AnnotationIdentifier";
    MKPinAnnotationView* customPinView = (MKPinAnnotationView *)[mapView dequeueReusableAnnotationViewWithIdentifier:AnnotationIdentifier];
    
    if (!customPinView) {
        customPinView = [[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:AnnotationIdentifier];
        
        customPinView.pinColor = MKPinAnnotationColorRed;
        customPinView.canShowCallout = YES;
        customPinView.draggable = NO;
        
    } else {
        customPinView.annotation = annotation;
    }
    
    return customPinView;
}

//清楚地图上所有的标注。
for (id<MKAnnotation> annotation in _mapView.annotations) {
    [_mapView removeAnnotation:annotation];
}

MKPlacemark、MKUserLocation和MKReverseGeocoder
在地图上做标记是通过MKPlacemark类来完成的。这个类使用（符合）MKAnnotation协议。MKAnnotation包含了多个属性，如：位置（经纬度，CLLocationCoordinate2D类型）、文字标记信息（NSString类型）等。
MKPlacemark保存了位置（经纬度）和地址（字典类）之间的映射。下面是它的初始化方法：
-(void)initWithCoordinate:(CLLocationCoordinate2D *)coordinate addressDictionary:(NSDictionary *)dictionary;
MKUserLocation就是指手机的当前位置，它是MKAnnotation的一个特别案例（因为MKAnnotation可以是地图上的任何标记，而MKUserLocation只是标记了地图上手机所在的当前位置）。这个类包含了多个属性：手机的位置（类型为CLLocation）、位置文字信息（类型为NSString）等。
MKPlacemark保存了位置（经纬度）和地址之间的映射。那么，有没有工具在这两者之间做转换呢？这就是MKRecerseGeocoder.给定一个位置信息，这个类可以返回相应的地址信息。MKReverseGeocoder的初始化方法为：
-(void)initWithCoodinate:(CLLocationCoordinate2D)coordinate;
下面是MKReverseGeocoder常用的一些属性和方法：
@property id <MKReverseGeocoderDelegate>delegate; //委托
-(void)start; //开始转换
-(void)cancel; //取消转换

回调的方法有：
-(void)reverseGeocoder：(MKReverseGeocoder *) geocoded didFindPlacemark:(MKPlacemark *)placemark;  //转换成功
-(void)reverseGeocoder : (MKReverseGeocoder *)geocoded didFailWithError:(NSError *)error; //转换失败

//更新MKAnnotationView
-(void)mapView:(MKMapView *)sender didSelectAnnotationView:(MKAnnotationView *)aView{
    if([aView.leftCalloutAccessoryView isKindOfClass:[UIImageView class]]){
        UIImageView *imageView = (UIImageView *)aView.leftCalloutAccessoryView;
        imageView.image = //...; if you do this in a GCD queue,be careful views are reused!
    }
}


