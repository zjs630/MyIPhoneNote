1，
//iOS6中废除了viewWillUnload和viewDidUnload两个系统函数，收到内存警告时在didReceiveMemoryWarning中进行相关的处理。

#pragma mark - 内存警告的处理
//此方法6.0以后不会再调用
-(void)viewDidUnload{
    [super viewDidUnload];
    self.settingTableView = nil;
}

-(void)didReceiveMemoryWarning{
    [super didReceiveMemoryWarning];

#if 0
    if (![self isViewLoaded]) {
        return;
        // 这里做好异常处理
    }
    if ([[[UIDevice currentDevice] systemVersion] floatValue]>=6.0) {
        if (self.view.window == nil) {// 是否是正在使用的视图 /* I am not on screen right now */ 
            //此处写viewDidUnload中的，需要nil的代码。
            self.settingTableView = nil;// 如果是weak引用，self.view= nil时，settingTableView指针会自动变为nil。
            
            // 下面这句代码，目的是再次进入时能够重新加载 6.0以后系统不会自动释放self.view
            self.view = nil;
        }
    }
#else
    if([self isViewLoaded] && self.view.window == nil){
        self.view = nil;// 要支持ios5.0就要手动卸载视图
    }
#endif
}



