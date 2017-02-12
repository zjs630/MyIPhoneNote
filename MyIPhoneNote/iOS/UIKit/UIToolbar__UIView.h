

//添加工具栏
//我们分别加了一个图片按钮和文字按钮,以及一个标准模式的系统按钮.当然,也可以自定义,用initWithCustomView:
NSMutableArray *buttons = [[NSMutableArray alloc] init];

UIBarButtomItem *buttonImage = [[UIBarButtomItem alloc] initwithImage:[UIImage imageNamed:@"button.png"]
																Style:UIBarButtomItemStylePlain
															   target:self
															   action:@selector(myselector:)];


UIBarButtonItem *buttonText = [[UIBarButtonItem alloc] initWithTitle:@"title" 
															   style:UIBarButtonItemStyleBordered
															  target:self 
															  action:@selector (myselector:)];

UIBarButtonItem *myBookMarks = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemBookmarks target:self action:@selector(myselector:)];

//how to create fixed space and flexible space bar button items programmatically

UIBarButtonItem *fixed = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil]

UIBarButtonItem *flexible = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]



/*
 目前支持的标准模式
 UIBarButtonSystemItemDone   蓝色文字按钮,标有Done
 UIBarButtonSystemItemCancel 文字按钮,标有Cancel
 UIBarButtonSystemItemEdit   文字按钮,标有Edit
 UIBarButtonSystemItemSave   蓝色文字按钮,Save
 ......................Add   图案按钮,有个符号
 ''''''''''''''''''''''FlexibleSpace 空白,空间大小可用
 ......................fixedSpace   空白占位符
 ......................Compose   图案按钮,有笔和纸的图案
 ......................Reply    图案.回复箭头图案
 ......................Action   图案,动作箭头
 ......................Organize 文件夹及向下箭头图案
 ......................Bookmarks  书签图标
 ......................Search    有个图标
 ......................Refresh   环形刷新图标
 ......................Stop      停止记号X图标
 ......................Camera    照相机图标
 ......................Trash     垃圾桶图标
 ......................Play      播放图标
 ......................Pause     暂停图标
 ......................Rewind    倒带图标
 ......................FastForward 快进图标
 */

[buttons addObject:buttonImage];
[buttons addObject:buttonText];
[buttons addObject:myBookMarks];

UIToolbar *toolbar = [[UIToolbar alloc] init];
[toolbar setItems: buttons animated:YES];

self.navigationItem.titleView = toolbar;

[toolbar sizeToFit]; //调整大小




/*
 工具栏风格
 toolbar.barStyle = UIBarStyleDefault; 默认,灰色背景,白色文字
 .............................BlackOpaque  纯黑色,白色
 .............................BlackTranslucent 透明黑色,白色 
 */




