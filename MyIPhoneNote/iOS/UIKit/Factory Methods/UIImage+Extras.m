
#import "UIImage+Extras.h"


@implementation UIImage (Extras)

//makes a copy at a different size
- (UIImage *)imageByScalingToSize:(CGSize)newSize;
{
    UIGraphicsBeginImageContextWithOptions(newSize, YES, 0.0);
    [self drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;

}

- (UIImage *)imageByApplyingFilterNamed:(NSString *)filterName
{
    UIImage *filteredImage = self;
    
    //Step 1: create CIImage object
    CIImage *inputImage = [CIImage imageWithCGImage:[self CGImage]];
    if (inputImage) {
        //Step 2: get the filter
        CIFilter *filter = [CIFilter filterWithName:filterName];
        //Step 3: provide arguments
        [filter setValue:inputImage forKey:kCIInputImageKey];
        //Step 4:get output image
        CIImage *outputImage = [filter outputImage];
        if (outputImage) {
            filteredImage = [UIImage imageWithCIImage:outputImage];
            if (filteredImage) {
                //Step 5: draw it into a new image
                UIGraphicsBeginImageContextWithOptions(self.size, YES, 0.0);
                [filteredImage drawAtPoint:CGPointZero];
                filteredImage = UIGraphicsGetImageFromCurrentImageContext();
                UIGraphicsEndImageContext();
            }
        }
    }
}


@end