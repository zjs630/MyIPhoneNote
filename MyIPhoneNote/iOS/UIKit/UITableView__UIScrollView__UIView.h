1,create a table view
UITableView *tableView = [[UITableView alloc] initWithFrame:CGRectMake(10, 54, 300, 347) style:UITableViewStyleGrouped];

//[tableView setBackgroundColor:[UIColor clearColor]];//定义表视图背景
[tableView setDelegate:self];                       //定义代理
[tableView setDataSource:self];                     //定义数据源

[tableView setRowHeight:44];                                     //定义单元行高
[tableView setBackgroundColor:[UIColor whiteColor]];
//myTableView.showsVerticalScrollIndicator = NO;
//[myTableView setSeparatorStyle:UITableViewCellSeparatorStyleNone]; 取消间隔线
//myTableView.layer.borderWidth = 0;
[self.view addSubview:tableView];
[tableView release];
[tableView.layer setCornerRadius:8];
[tableView.layer setMasksToBounds:YES];

2，创建一个UITableViewController的子类，在此类中控制表格的数据源和委托。
#pragma mark UITableViewDataSource Methods

// return number Of sections in this table
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
}
// Return how many rows in the table
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return [[UIFont	familyNames] count];
}
// Return a cell for the ith row
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
	// Use re-usable cells to minimize the memory load
	static NSString *identifier = @"myIdentifier";
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
	if (cell == nil) {
	cell = [[[UITableViewCell alloc] 
				initWithStyle:UITableViewCellStyleDefault 
				reuseIdentifier:@"myIdentifier"] autorelease];
	//cell.showsReorderControl = YES;//当进入编辑模式时才能显示重新排序控件。
	 }
	// Set up the cell's text,image and detailTextLabel
	cell.textLabel.text = [[UIFont familyNames] objectAtIndex:[indexPath row]];
	cell.imageView.image = [UIImage imageNamed:@"star.png"];
	cell.detailTextLabel.text =@"...";
	cell.textLabel.font =[UIFont boldSystemFontOfSize:50];//设置字体大小
	return cell;
}
//表视图询问是否可以在指定行进行删除和插入操作。
- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView 
           editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    return UITableViewCellEditingStyleNone;//表示不支持插入和删除任何行。
}
//设置行是否可以移动，每一行都将调用此方法。
- (BOOL)tableView:(UITableView *)tableView 
canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
		return YES;
}
#pragma mark UITableViewDelegateMethods
// Respond to user selection
- (NSInteger)tableView:(UITableView *)tableView 
indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath{
    NSUInteger row = [indexPath row];
    return row;//设置缩进
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)newIndexPath{
	//printf("User selected row %d\n", [newIndexPath row] + 1);
	// Update the Navigation Item with the new font//设置导航栏标题的字体
	NSString *fontName = [[UIFont familyNames] objectAtIndex:[newIndexPath row]];
	[(UILabel *)self.navigationItem.titleView setFont:[UIFont fontWithName: fontName size:[UIFont systemFontSize]]];
}
- (CGFloat)tableView:(UITableView *)tableView 
heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 70;//设置行高
}
//点击行提示：行的内容，之后取消行的选中
- (void)tableView:(UITableView *)tableView 
didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSUInteger row = [indexPath row];//获取选中行的标号。
    NSString *rowTitle = [list objectAtIndex:row];//通过选中行的标号来找到数组中对应的值。
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"你单击了行."
                                                    message:[NSString stringWithFormat:@"行中的内容是 %@.", rowTitle]
                                                   delegate:nil 
                                          cancelButtonTitle:@"是的" 
                                          otherButtonTitles:nil];
    [alert show];
    [alert release];
    [tableView deselectRowAtIndexPath:indexPath animated:YES];//取消行的选中。
} 
//删除行
[self.tableView setEditing:YES animated:YES];//打开表格的编辑功能
[self.tableView setEditing:NO animated:YES];//取消编辑功能


// After a row has the minus or plus button invoked (based on the UITableViewCellEditingStyle for the cell), the dataSource must commit the change
- (void)tableView:(UITableView *)tableView 
	commitEditingStyle:(UITableViewCellEditingStyle)editingStyle 
	forRowAtIndexPath:(NSIndexPath *)indexPath
{
	NSUInteger row = [indexPath row];
	[self.list removeObjectAtIndex:row];
	[tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath]
				withRowAnimation:UITableViewRowAnimationFade];//表格淡出
}

3，实现表格行的多选。
if(cell.accessoryType == UITableViewCellAccessoryNOne){
	cell.accessoryType = UITableViewCellAccessoryCheckmark;
}

代码片段：
1.给UITableViewController添加ToolBar。
self.navigationController.toolbarHidden = NO; //默认是隐藏的。
//添加MessageToolBar ，messageToolBar是IBOutlet的一个ToolBar。
self.toolbarItems =  [[[NSMutableArray alloc] initWithArray:self.messageToolBar.items] autorelease]; 
self.navigationController.toolbar.barStyle = self.messageToolBar.barStyle;  
2.后台运行一个方法，如果该方法需要修改UI，为了防止出错，应在主线程里修改UI。
[self performSelectorInBackground:@selector(updateInfo)]; 
在UpdateInfo里如果要修改UI ，
[self performSelectorOnMainThread:@selector(updateUIMethod) withObject:nil waitUntilDone:NO]; 

3，重新加载表格数据。
[tableView reloadData];


Table View  <UITableViewDateSource>
#pragma mark -
#pragma mark Table View Data Source Methods
//指定分区中的行数，默认为1
- (NSInteger)tableView:(UITableView *)tableView 
numberOfRowsInSection:(NSInteger)section
{
	return [self listData count];
}

//设置每一行cell显示的内容
- (UITableViewCell *)tableView:(UITableView *)tableView 
cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
#if 0
	static NSString *SimpleTableIndentifier = @"SimpleTableIndentifier";
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:SimpleTableIndentifier];
	if (cell == nil) {
		cell = [[[UITableViewCell alloc]
				 initWithStyle:UITableViewCellStyleSubtitle
				 reuseIdentifier:SimpleTableIndentifier]
				autorelease];
	}
#else //使用storyboard
    UITableViewCell *cell = [tableView
                             dequeueReusableCellWithIdentifier:@"PlayerCell"];
     UILabel *nameLabel = (UILabel *)[cell viewWithTag:100];  //获取某个控件，自己设置tag
#endif
	UIImage *image = [UIImage imageNamed:@"13.gif"];
	cell.imageView.image = image;

	
    NSUInteger row = [indexPath row];
	cell.textLabel.text = [listData objectAtIndex:row];//设置单元行中的内容。
    cell.textLabel.font = [UIFont boldSystemFontOfSize:20];//设置字体大小。
	if(row < 5)
		cell.detailTextLabel.text = @"Best friends";
    else
        cell.detailTextLabel.text = @"friends";
    return cell;
}
图像：如果设置图像，则它显示在文本的左侧
文本标签：这是单元的主要文本（UITableViewCellStyleDefault 只显示文本标签）
详细文本标签：这是单元的辅助文本，通常用作解释性说明或标签
UITableViewCellStyleSubtitle
UITableViewCellStyleDefault
UITableViewCellStyleValue1
UITableViewCellStyleValue2

<UITableViewDelegate>
#pragma mark -
#pragma mark Table View Delegate Methods
//把每一行缩进级别设置为其行号
- (NSInteger)tableView:(UITableView *)tableView indentationLevelForRowAtIndexPath:(NSIndexPath *)indexPath
{
	NSUInteger row = [indexPath row];
	return row;
}
//获取传递过来的indexPath值
- (NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	NSUInteger row = [indexPath row];//选中的行号。
	if (row == 0) //设置第一行不能被选中。
		return nil;
	return indexPath;
}
 
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	NSUInteger row = [indexPath row];
	NSString *rowValue = [listData objectAtIndex:row];
	NSString *message = [[NSString alloc] initWithFormat:@"You selected %@",rowValue];
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Row Selected"
													message:message
						      delegate:nil
						    cancelButtonTitle:@"Yes, I did!"
						    otherButtonTitles:nil];
	[alert show];
	[alert release];
	[message release];
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
}
4,单元行的右侧添加按钮。
UIButton *sinaButton = [UIButton buttonWithType:UIButtonTypeCustom];
sinaButton.frame = CGRectMake(0.0, 0.0, 42.0, 29.0);
sinaButton.titleLabel.font = [UIFont systemFontOfSize:14];
[sinaButton setBackgroundImage:[UIImage imageNamed:@"weibo_login.PNG"] forState:UIControlStateNormal];
[sinaButton setBackgroundImage:[UIImage imageNamed:@"weibo_login_click.PNG"] forState:UIControlStateHighlighted];
//[sinaButton setTitle:@"Tap" forState:UIControlStateNormal];
[sinaButton addTarget:self action:@selector(weiboButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
cell.accessoryView = sinaButton;

5，UITableView 长按事件

UILongPressGestureRecognizer *lpgr = [[UILongPressGestureRecognizer alloc] initWithTarget:self
                                                                                  action:@selector(longPressed:)];
[lpgr setMinimumPressDuration:1.0];
[_tableViewaddGestureRecognizer:lpgr];
[lpgr release];

-(void)longPressed:(UILongPressGestureRecognizer *)gestureRecognizer{
    
    CGPoint p = [gestureRecognizer locationInView:_tableView]; 
    
    if(gestureRecognizer.state == UIGestureRecognizerStateBegan){
        
        
        NSIndexPath *indexPath = [_tableViewindexPathForRowAtPoint:p]; 
        
        }
        
}
6,UITableView滚动到最底端的时候自动加载数据，就想新浪微博那样   
不需要用户去点击“更多”，当滚动条滚动到最底部时自动加载

tableview也是一种scrollview 当scrollview scroll的时候，可以根据判断条件判断此时的tableview已经滑到了最底端，以下是判断条件 那个scrollview就是tableview
scrollView.contentOffset.y + (scrollView.frame.size.height) > scrollView.contentSize.height
就表示已经到底部了 可以进行在判断条件内执行更多了

在UITableView 委托方法- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
调用加载数据得方法吧

//[speakerTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow: [items count] -1  inSection:0] atScrollPosition:UITableViewScrollPositionBottom animated:NO];
7,禁止选中某一行单元格高亮效果，其实单元格还会选中。
if(row == 2){
    [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
}
8,刷新表格数据时，表格内容滚动到顶部。
[mainTableView setContentOffset:CGPointZero animated:YES]; 

9,
//数据删除.

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath { 
    
    return YES; 
    
} 

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath { 
    
    if (editingStyle == UITableViewCellEditingStyleDelete) { 
        
        [dataArray removeObjectAtIndex:indexPath.row]; 
        
        // Delete the row from the data source. 
        
        [testTableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];     
        
    }    
    
    else if (editingStyle == UITableViewCellEditingStyleInsert) { 
        
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view. 
        
    }    
    
} 

启用上面两个代理,并增加数据删除操作:

[dataArray removeObjectAtIndex:indexPath.row];

在一条数据上向右划动一下.

点Delete.

是不是就成功删除了一条数据呢?

按理说故事讲到这里也就讲完了.但是笔者想延伸一下.注意看图二划动以后的"Delete",你有没有想把这个东东改掉的冲动呢?比如改成:下载?其实很简单,其实下面这个代理方法:

- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath{ 
    
    return @"下载"; 
    
}

10
批量插入，删除，部分更新操作

　　UITableView提供了一个批量操作的特性，这个功能在一次进行多个row或者scetion的删除，插入，获取更新多个cell内容的时候特别好用。所有的批量操作需要包含在beginUpdates和endUpdates块中，否则会出现异常。


- (void)groupEdit:(UIBarButtonItem*)sender
{
    [_tableView beginUpdates];
    
    // first update the data modal
    [_tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:[NSIndexPath indexPathForRow:0 inSection:0]] withRowAnimation:UITableViewRowAnimationTop];
    
    //删除第一行的表格
    [_tableView deleteSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationTop];
    //同时注意删除第一行对应的数据
    [SvTableViewDataModal deleteSectionAtIndex:0];
    
    SvSectionModal *section = [[SvTableViewDataModal sections] objectAtIndex:0];
    [section.cityNames insertObject:@"帝都" atIndex:0];
    [SvTableViewDataModal replaceSectionAtIndex:0 withSection:section];
    
    [_tableView endUpdates];
}
11,//Removing extra separator lines for empty rows in UITableView
- (void) viewDidLoad
{
    [super viewDidLoad];
    self.tableView.tableFooterView = [[[UIView alloc] init] autorelease];
}
12,UITableView segue

The sender of prepareForSegue:sender: is the UITableViewCell!
Use the important method indexPathForCell: to find out the indexPath of the row that’s segueing.
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    NSIndexPath *indexPath = [self.mainTableView indexPathForCell:sender];
    // prepare segue.destinationController to display based on information
    // about my Model corresponding to indexPath.row in indexPath.section
}
