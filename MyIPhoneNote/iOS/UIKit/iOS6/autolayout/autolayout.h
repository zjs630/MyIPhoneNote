1,http://www.objc.io/issue-3/advanced-auto-layout-toolbox.html
2，
for (UIView *aView in [yourViewController subviews]) {
    if ([aView hasAmbiguousLayout]) {
        NSLog(@"View Frame %@", NSStringFromCGRect(aView.frame));
        NSLog(@"%@", [aView class]);
        NSLog(@"%@", [aView constraintsAffectingLayoutForAxis:1]);
        NSLog(@"%@", [aView constraintsAffectingLayoutForAxis:0]);
        
        [aView exerciseAmbiguityInLayout];// 添加导致布局不确定的约束
    }
    
    NSArray *constraints = [self.contentView constraintsReferencingView:view];
    for (NSLayoutConstraint *constraint in constraints) [constraint remove];
}


NSArray *constraints = [self constraints];
[self removeConstraints:constraints];