1,此类中，有个方法叫layoutSubviews.在绘制单元格时，这个方法将会自动调用，如我们可以改变一些视图的大小。
2，改变自定义单元格选中的背景色

cell.selectionStyle = UITableViewCellSelectionStyleNone;

- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated{
    if (highlighted) {
        [self setBackgroundColor:HEXCOLOR(0x9fcee7ff)];
    }
    else {
        [self setBackgroundColor:[UIColor clearColor]];
    }
}

3.点击cell上的一个按钮（只实现变色操作）后，执行controller 的tableView:didSelectRowAtIndexPath:方法。
- (void)tapGre:(UIButton *)btn
{
    UITableView *tbView = nil;
    if (iOSVersion()>=7.0) {
        tbView = (UITableView *)self.superview.superview;
    }
    else{
        tbView = (UITableView *)self.superview;
    }
    if (![tbView isKindOfClass:[UITableView class]]) {
        return;
    }
    NSIndexPath *indexPath = [tbView indexPathForCell:self];
    id controller = tbView.delegate;
    if (controller) {
        [controller tableView:tbView didSelectRowAtIndexPath:indexPath];
    }
    
}
4，单元格的重用机制，个人总结。
表格高度400，每个单元格高度100，系统一开始默认会创建4个cell。当你向下滑动的时候，会创建第五个cell。
如果是单元格定高的情况下，系统会一直重用这5个cell，不会创建更多的cell。系统创建的cell个数，永远比展示的cell多一个。
如果是cell高度不定，当一屏幕展示的cell大于5个时，系统会创建新的cell。
如果滑动出去了3个单元格，但目前最下面的单元格，还一直展示，接下来系统会重最近滑动出去的cell。

