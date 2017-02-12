
最近公司接了一个项目，是海尔公司的，里面有二维码扫描的功能，开源的二维码扫描的sdk 有很多，今天我这里使用的ZBarSDK，一个比较优秀的开源项目，使用起来也很简单。

ZBarSDK是一个开源的SDK，可从这里下载到源码，该SDK实现了识别和读取各种条形码，包括EAN-13/UPC-A, UPC-E, EAN-8, Code 128, Code 39, Interleaved 2 of 5 和 QR Code。

帮助文档：http://zbar.sourceforge.net/iphone/sdkdoc/index.html

Step1.使用ZBarSDK 需要导入的framework

1.AVFoundation.framework

2.CoreMedia.framework

3.CoreVideo.framework

4.QuartzCore.framework

5.libiconv.dylib

Step2.在ViewController.h 导入#import "ZBarSDK.h"

Step3.在ViewController.h 继承 <ZBarReaderDelegate>协议

Step4.写代码：

ViewController.h

#import <UIKit/UIKit.h>
#import "ZBarSDK.h"

@interface ViewController : UIViewController <ZBarReaderDelegate>
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
- (IBAction)scan:(id)sender;
@property (weak, nonatomic) IBOutlet UILabel *label;


@end

ViewController.m

#import "ViewController.h"
#import "ZBarSDK.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)scan:(id)sender {
    
    
    ZBarReaderViewController * reader = [ZBarReaderViewController new];
    reader.readerDelegate = self;
    ZBarImageScanner * scanner = reader.scanner;
    [scanner setSymbology:ZBAR_I25 config:ZBAR_CFG_ENABLE to:0];
    
    reader.showsZBarControls = YES;
    
    [self presentViewController:reader animated:YES completion:nil];
    
    
}


-(void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    id<NSFastEnumeration> results = [info objectForKey:ZBarReaderControllerResults];
    ZBarSymbol * symbol;
    for(symbol in results)
        break;
    
    _imageView.image = [info objectForKey:UIImagePickerControllerOriginalImage];
    
    [picker dismissViewControllerAnimated:YES completion:nil];
    
    _label.text = symbol.data;
}


@end