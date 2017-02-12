1,步骤

Textkit是iOS7新推出的类库，其实是在之前推出的CoreText上的封装，有了这个TextKit，以后不用再拿着CoreText来做累活了，根据苹果的说法，他们开发了两年多才完成，而且他们在开发时候也将表情混排作为一个使用案例进行研究，所以要实现表情混排将会非常容易。
TextKit并没有新增的类，他是在原有的文本显示控件上的封装，可以使用平时我们最喜欢使用的UILabel，UITextField，UITextView里面就可以使用了。

1.NSAtrributedString
这是所有TextKit的载体，所有的信息都会输入到NSAttributedString里面，然后将这个String输入到Text控件里面就可以显示了。
2.NSTextAttachment
iOS7新增的类，作为文本的附件，可以放文件，可以放数据，以 NSAttachmentAttributeName这个key放入NSAttributedString里面，在表情混排这里，我们将放入image。

3.重载NSTextAttachment
本来是可以直接使用NSTextAttachment，但是我们需要根据文字大小来改变表情图片的大小，于是我们需要重载NSTextAttachment，NSTextAttachment实现了NSTextAttachmentContainer，可以给我们改变返回的图像，图像的大小。
重载NSTextAttachment代码：
@interface MMTextAttachment : NSTextAttachment
{
}
@end
@implementation MMTextAttachment
//I want my emoticon has the same size with line's height
- (CGRect)attachmentBoundsForTextContainer:(NSTextContainer *)textContainer proposedLineFragment:(CGRect)lineFrag glyphPosition:(CGPoint)position characterIndex:(NSUInteger)charIndex
{
    return CGRectMake( 0 , 0 , lineFrag.size.height , lineFrag.size.height );
    
}
@end

4.
NSMutableAttributedString * string = [[ NSMutableAttributedStringalloc ] initWithString:@"123456789101112"  attributes:nil ] ;

MMTextAttachment * textAttachment = [[ MMTextAttachment alloc ] initWithData:nil ofType:nil ] ;
UIImage * smileImage = [ UIImage imageNamed:@"a.jpg" ]  ;  //my emoticon image named a.jpg
textAttachment.image = smileImage ;

NSAttributedString * textAttachmentString = [ NSAttributedString attributedStringWithAttachment:textAttachment ] ;

[ string insertAttributedString:textAttachmentString atIndex:6 ] ;
_textView.attributedText = string ;
