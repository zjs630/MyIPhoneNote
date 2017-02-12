
#import <UIKit/UIKit.h>
@interface UIImage(Extras)


//makes a copy at a different size
- (UIImage *)imageByScalingToSize:(CGSize)newSize;


- (UIImage *)imageByApplyingFilterNamed:(NSString *)filterName;


@end