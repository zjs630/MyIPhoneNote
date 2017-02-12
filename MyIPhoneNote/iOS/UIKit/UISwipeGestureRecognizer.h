1,左滑手势识别
   UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 320, 44)];
   [cell.contentView addSubview:view];
   [view release];
   
   UISwipeGestureRecognizer *recognizer = [[UISwipeGestureRecognizer alloc] init];
   recognizer.direction = UISwipeGestureRecognizerDirectionLeft;
   [recognizer addTarget:self action:@selector(swipe:)];
   [view addGestureRecognizer:recognizer];
   [recognizer release];

-(void)swipe:(UIGestureRecognizer *)rec{
    //    [MyComponentsFactory showMyAlertInfo:@"左滑" forView:self.view];
}

