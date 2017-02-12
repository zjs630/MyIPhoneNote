1,画三角形

UIBezierPath *path = [[UIBezierPath alloc] init];
[path moveToPoint:CGPointMake(75,10)];
[path addLineToPoint:CGPointMake(160,150)];
[path addLineToPoint:CGPointMake(10,150)];
//Close the path(connects the last point back to the first)
[path closePath];

//Now that the path has been created, we can stroke/fill it
[[UIColor greenColor] setFill];//填充
[[UIColor redColor] setStroke];//描边

path.lineWidth = 2.0;//line width

2，//画圆角矩形
UIBezierPath *roundedRect = [UIBezierPath bezierPathWithRoundedRect:(CGRect)bounds cornerRadius:(CGFloat)radius];
You can use a UIBezierPath to “clip” your drawing [roundedRect addClip]; // this would clip all drawing to be inside the roundedRect

3，//画椭圆
 UIBezierPath *oval = [UIBezierPath bezierPathWithOvalInRect:self.bounds];
//描边
[[UIColor blackColor] setStroke];
[oval stroke];
//填充
[[UIColor whiteColor] setFill];
[oval fill];//or UIRectFill(self.bounds);

注意：先初始化，去掉不需要的部分。

- (void)setup
{
    self.backgroundColor = [UIColor clearColor];
    self.opaque = NO;
    self.contentMode = UIViewContentModeRedraw;
    
}

- (void)awakeFromNib
{
    [self setup];
}

4,画圆
[UIBezierPath bezierPathWithArcCenter:origin
                               radius:20
                           startAngle:-180.0f
                             endAngle:180.0f
                            clockwise:YES];

