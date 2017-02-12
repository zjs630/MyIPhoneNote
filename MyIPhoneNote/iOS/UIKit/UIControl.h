

第十章 UIKit的设计

10.1 UIControl

//属性
enabled //一般默认都是可用的,要禁用时改成NO

selected //

UIControlContentVerticalAlignmentCenter   //控件自身的位置,这里是位于中间

UIControlContentHorizontalAlignmentCenter  //文本的位置


//通知事件,根据控件发生的事件进行什么动作

[myControl addTarget:myDelegate action:@selector(myMethod:) forControlEvents:UIControlEventValueChanged ];

控件可发生的事件包括:
UIControlEventTouchDown  //单击按下
UIControlEventTouchDownRepeat  //多触点按下,即按下多于一个手指时
UIControlEventTouchDragInside  //当一次触摸在控件窗口内拖动时
UIControlEventTouchDragOutside  //当一次触摸在控件的窗口外拖动时
UIControlEventTouchDragEnter   //当一次触摸从控件的窗口外拖动到内部时,发送事件通知
UIControlEventTouchDragExit    //                 内部拖动到外部时
UIControlEventTouchUpInside    //通知所有发生在控件内的触摸抬起事件
UIControlEventTouchUpOutside   //...........控件之外的.....
UIControlEventTouchCancel      //所有触摸取消事件,如被电话打断,或放太多手指而被取消
UIControlEventTouchValueChanged  //当控件的值改变时
UIControlEventEditingDidBegin  //当文本控件开始编辑时
UIControlEventEditingChanged   //当控件的文本被改变时
UIControlEventEditingDidEnd  //当文本控件结束编辑时
UIControlEventEditingDidEndOnExit  //当文本控件通过按下回车结束编辑时
UIControlEventAllTouchEvents       //所有的触摸时
UIControlEventAllEditingEvents     //所有关于文本编辑的事件
UIControlEventAllEvents             //所有的事件


//获得控件的所有指定动作的列表
NSSet *myActions = [myControl allTargets];


//分段控件UISegmentedControl 的三种风格:
UISegmentedControlStyleBar 小按钮,适合导航栏,这种的话还可以用tintColor设置色彩
UISegmentedControlStylePlain  有灰边的大白按钮,适合偏好设置单元
UISegmentedControlStyleBordered  黑边的大白按钮,适适合表格单元


//给分段按钮添加片段

[segmentedControl insertSegmentWithTitle:@"one" atIndex:0 animated:NO];

//删除片段
[segmentedControl removeSegentAtIndex:1 animated:YES];
[segmentedControl removeAllSegments];

//给片段设置标题
[segmentedControl setTitle:@"one" forSegment: 0];


//显示控件
[parentView addSubview:segmentedControl];  //添加到父视图
self.navigationItem.titleView = segmentedControl; //添加到导航栏




//开关的位置
BOOL switchPosition = switch.on;
设置on为打开开关
[switch setOn:YES animated:YES];



//滑块
设置最大最小值:
slider minimumValue:0.0;
slider maximumValue:100.0;	

要让滑块拖动时事件同时也发生:
slider.continuous = YES;



//按钮




//分组表视图的设计

//加上引索条的方法:
-(NSArray *) sectionIndexTitlesForTableView:(UITableVIew *)tableView;

//数据源包括的方法如下:
numberOfSectionsInTableView
numberOfRowsInSection
cellForRowAtIndexPath

titleForHeaderInSection
heightForRowAtIndexPath
sectionIndexTitlesForTableView //返回一个所有部分的标题的数组,用来构建索引条
sectionForSectionIndexTitle  //索引标题和段落编号之间的关联,当点击该索引时,屏幕上定位到该段落





10.4 活动指示器和进度条  //UIActivityIndicatorView,UIProgressView

//菊花添加到视图或cell上的方法
[tableCell addSubview:activityIndicator];

//菊花启动和停止动画的方法
[activityIndicator startAnimating];
[activityIndicator stopAnimating];

//进度条添加到表单元,工具条和其他视图上的方法:
[myToolBar addSubview:progressView];
//设置值
progressView.progress = 0.5;

//网络活动指示器,当链接到网络时用,设置方法
UIApplication *myApp = [UIApplication sharedApplication];
myApp.networkActivityIndicatorVisible = YES;








