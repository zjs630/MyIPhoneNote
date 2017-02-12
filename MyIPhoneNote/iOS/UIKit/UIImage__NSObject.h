1,加载图片的方式
a,Create by name.
//Looks in your Resources folder from Xcode for a file with the given name 
UIImage *image = [UIImage imageNamed:@"a.png"];
b,Create width data
从应用程序的程序包中装载一个图像代码：
NSString* imagePath = [[NSBundle mainBundle] pathForResource:@"myImage" ofType:@"png"];
UIImage* myImageObj = [[UIImage alloc] initWithContentsOfFile:imagePath];// From the file system

或者
UIImage *image = [[UIImage alloc] initWithData:(NSData *)data];
//使用包含网页对象的图像
NSURL *url = [NSURL URLWithString:@"http://oeinlly.com/data/covers/1982753.gif"];
NSData *imageData = [NSData dataWithContentsOfURL:url];
UIImage *image = [UIImage imageWithData:imageData];

//使用Core Graphics
UIImage *image = [UIImage imageWithCGImage:myCGImageRef];


2,在某一具体位置显示图像。
- (void)drawRect:(CGRect)rect//只有在视图初次绘制时才会调用
{
	// Draw the image
	[anImage drawAtPoint:CGPointMake(10, 10)];
	//[anImage drawInRect:CGRectMake(0,0,10, 10)];
}
//要强制进行更新可以使用以下方法
[myView setNeedsDisplay];
[myView setNeedsDisplayInRect:redrawThisRect];

3,UIImage imageNamed和UIImage imageWithContentsOfFile的区别
UIImage imageNamed将为这个图像提供缓存，所以如果你再次需要同一图像时，图像将被从内部缓存而
不是从资源中加载。而坏消息也是iPhone将为此图像提供缓存。这样如果图片过多就好出现内存泄露的现象。
UIImage imageWithContentsOfFile将不提供缓存。 


4.引用图片,即把图片载入图片视图
UIImage *seven = [UIImage imageNamed:@"seven.png"];

UIImageView *sevenView = [[UIImageView alloc] initWithImage:seven];


注意: 以上第一行这个方法适合于图片很少的时候用,图片多时最好用下面的方法
推荐使用
NSString *path = [[NSBundle mainBundle] pathForResource:@"icon" ofType:@"png"];
myImage = [UIImage imageWithContentsOfFile:path];

5,设置图片的旋转方向
myImage.imageOrientation = UIImageOrientationUp;

6,绘制图案//在视图区域重复绘制改图案
[myImage drawAsPatternInRect:rect];

5.这段“许靖昕”先生分享的代码将示范如何缩小 UIImage

@implementation UIImage (Extras)  
#pragma mark -  
#pragma mark Scale and crop image  
- (UIImage*)imageByScalingAndCroppingForSize:(CGSize)targetSize  
{  
	UIImage *sourceImage = self;  
	UIImage *newImage = nil;          
	CGSize imageSize = sourceImage.size;  
	CGFloat width = imageSize.width;  
	CGFloat height = imageSize.height;  
	CGFloat targetWidth = targetSize.width;  
	CGFloat targetHeight = targetSize.height;  
	CGFloat scaleFactor = 0.0;  
	CGFloat scaledWidth = targetWidth;  
	CGFloat scaledHeight = targetHeight;  
	CGPoint thumbnailPoint = CGPointMake(0.0,0.0);  
	if (CGSizeEqualToSize(imageSize, targetSize) == NO)   
	{  
        CGFloat widthFactor = targetWidth / width;  
        CGFloat heightFactor = targetHeight / height;  
        if (widthFactor > heightFactor)   
			scaleFactor = widthFactor; // scale to fit height  
        else  
			scaleFactor = heightFactor; // scale to fit width  
        scaledWidth  = width * scaleFactor;  
        scaledHeight = height * scaleFactor;  
        // center the image  
        if (widthFactor > heightFactor)  
		{  
			thumbnailPoint.y = (targetHeight - scaledHeight) * 0.5;   
		}  
        else   
			if (widthFactor < heightFactor)  
			{  
				thumbnailPoint.x = (targetWidth - scaledWidth) * 0.5;  
			}  
	}         
	UIGraphicsBeginImageContext(targetSize); // this will crop  
	CGRect thumbnailRect = CGRectZero;  
	thumbnailRect.origin = thumbnailPoint;  
	thumbnailRect.size.width  = scaledWidth;  
	thumbnailRect.size.height = scaledHeight;  
	[sourceImage drawInRect:thumbnailRect];  
	newImage = UIGraphicsGetImageFromCurrentImageContext();  
	if(newImage == nil)   
        NSLog(@"could not scale image");  
	//pop the context to get back to the default  
	UIGraphicsEndImageContext();  
	return newImage;  
}  

//方法2，
- ()
@end

6，如果在程序中想对某张图片进行处理的话（得到某张图片的一部分）可一用以下代码：

UIImage *image = [UIImage imageNamed:filename];
CGImageRef imageRef = image.CGImage;
CGRect rect = CGRectMake(origin.x, origin.y ,size.width, size.height);
CGImageRef imageRefRect = CGImageCreateWithImageInRect(imageRef, rect);
UIImage *imageRect = [[UIImage alloc] initWithCGImage:imageRefRect];

7,UIImage保存到文件，PNG／JPEG自适应
+ (BOOL)writeImage:(UIImage*)image toFileAtPath:(NSString*)aPath{
    if ((image == nil) || (aPath == nil) || ([aPathisEqualToString:@""]))
        return NO;
    @try
    {
        NSData *imageData = nil;
        NSString *ext = [aPath pathExtension];
        if ([ext isEqualToString:@"png"]){
            imageData = UIImagePNGRepresentation(image);   
            //[UIImagePNGRepresentation(image) writeToFile:pngPath atomically:YES];  
        }
        else{
            // the rest, we write to jpeg
            // 0. best, 1. lost. about compress.
            imageData = UIImageJPEGRepresentation(image,0);    
        }
        if ((imageData == nil) || ([imageData length] <= 0))
            return NO;
        
        [imageData writeToFile:aPath atomically:YES];      
        
        return YES;
    }
    @catch (NSException *e)
    {
        NSLog(@"create thumbnail exception.");
    }
    
    return NO;
}
