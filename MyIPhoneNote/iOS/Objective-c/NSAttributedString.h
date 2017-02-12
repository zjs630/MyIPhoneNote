1,
- (void)drawRect:(CGRect)rect
{
    UIFont *font = [UIFont systemFontOfSize:50];
    
    NSShadow *shadow = [[NSShadow alloc] init];
    shadow.shadowColor = [UIColor blackColor];
    shadow.shadowBlurRadius = 0.0;
    shadow.shadowOffset = CGSizeMake(0.0, 2.0);
    
    NSDictionary *attributes = @{NSShadowAttributeName          : shadow,
                                 NSForegroundColorAttributeName : [UIColor yellowColor],
                                 NSFontAttributeName            : font};
    
    NSAttributedString *attributedText = [[NSAttributedString alloc] initWithString:@"this has shadows" attributes:attributes];
    
    [attributedText drawInRect:rect];
}

2,设置价格为红色

NSString *text = @"现价：¥888";

// Define general attributes for the entire text
NSDictionary *attribs = @{
                          NSForegroundColorAttributeName: self.myLabel.textColor,
                          NSFontAttributeName: self.myLabel.font
                          };
NSMutableAttributedString *attributedText =
[[NSMutableAttributedString alloc] initWithString:text
                                       attributes:attribs];

// Red text attributes
UIColor *redColor = [UIColor redColor];
NSRange redTextRange = NSMakeRange(3, [text length]-3);

[attributedText setAttributes:@{NSForegroundColorAttributeName:redColor}
                        range:redTextRange];
self.myLabel.attributedText = attributedText;

3，设置删除线。
NSString *redText = @"原价：¥9888";
NSMutableAttributedString *ats = [[NSMutableAttributedString alloc] initWithString:redText attributes:@{NSStrikethroughStyleAttributeName:
                                                                                                            [NSNumber numberWithInteger:NSUnderlineStyleSingle]}];
self.myLabel2.attributedText = ats;


