1,画圆
-(void)drawCircleAtPoint:(CGPoint)p withRadius:(CGFloat)radius inContext:(CGContextRef)context{
    UIGraphicsPushContext(context);
    CGContextBeginPath(context);
    CGContextAddArc(context, p.x, p.y, radius, 0, 2*M_PI, YES);
    //    CGContextSetStrokeColorWithColor(context, [[UIColor blueColor] CGColor]);
    CGContextStrokePath(context);
    UIGraphicsPopContext();
}
-(void)drawRect:(CGRect)rect{
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGPoint midPoint;
    midPoint.x = self.bounds.size.width/2;
    midPoint.y = self.bounds.size.height/2;
    
    CGFloat radius = self.bounds.size.width/2-20;
    
    CGContextSetLineWidth(context, 5);
    [[UIColor greenColor] setStroke];
    [self drawCircleAtPoint:midPoint withRadius:radius inContext:context];
}
2，画曲线
-(void)drawRect:(CGRect)rect{
    CGContextRef context = UIGraphicsGetCurrentContext();

    CGPoint mouthStart = CGPointMake(0, 0);
    CGPoint mouthEnd = CGPointMake(120, 0);

    CGPoint mouthCP1 = CGPointMake(40, 40);
    CGPoint mouthCP2 = CGPointMake(80, 40);

    CGContextBeginPath(context);
    CGContextMoveToPoint(context, mouthStart.x, mouthStart.y);
    CGContextAddCurveToPoint(context, mouthCP1.x, mouthCP1.y, mouthCP2.x, mouthCP2.y, mouthEnd.x, mouthEnd.y);
    CGContextStrokePath(context);
}

3，画虚线

CGContextRef context =UIGraphicsGetCurrentContext();
CGContextBeginPath(context);
CGContextSetLineWidth(context, 2.0);
CGContextSetStrokeColorWithColor(context, [UIColorwhiteColor].CGColor);
float lengths[] = {10,10};
CGContextSetLineDash(context, 0, lengths,2);
CGContextMoveToPoint(context, 10.0, 20.0);
CGContextAddLineToPoint(context, 310.0,20.0);
CGContextStrokePath(context);
//CGContextClosePath(context);

