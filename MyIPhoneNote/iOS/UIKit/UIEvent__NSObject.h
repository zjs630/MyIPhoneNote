1,UIEvent中的重要内容
@property(nonatomic,readonly) NSTimeInterval timestamp;
- (NSSet *)allTouches;
- (NSSet *)touchesForWindow:(UIWindow *)window;
- (NSSet *)touchesForView:(UIView *)view;