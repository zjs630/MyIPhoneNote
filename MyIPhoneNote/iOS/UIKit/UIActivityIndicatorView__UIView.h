1，创建指示器
UIActivityIndicatorView *activityIndicatorView = [[UIActivityIndicatorView alloc] 
												  initWithFrame:CGRectMake(120,12,25,25)];


activityIndicatorView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
//or UIActivityIndicatorViewStyleWhite or UIActivityIndicatorViewStyleGray
[self addSubview:activityIndicatorView];
[activityIndicatorView release];


#define COOKBOOK_PURPLE_COLOR	[UIColor colorWithRed:0.20392f green:0.19607f blue:0.61176f alpha:1.0f]
#define BARBUTTON(TITLE, SELECTOR) 	[[[UIBarButtonItem alloc] initWithTitle:TITLE style:UIBarButtonItemStylePlain target:self action:SELECTOR] autorelease]

@interface TestBedViewController : UIViewController
{
	IBOutlet UIView *overlay;
}
@property (retain) UIView *overlay;
@end

@implementation TestBedViewController
@synthesize overlay;

- (void) finish
{
	[(UIActivityIndicatorView *)[self.overlay viewWithTag:202] stopAnimating];
	[self.overlay removeFromSuperview];
}

- (void) action: (id) sender
{
	[self.view.window addSubview:self.overlay];
	[(UIActivityIndicatorView *)[self.overlay viewWithTag:202] startAnimating];
	
	[self performSelector:@selector(finish) withObject:nil afterDelay:3.0f];
}

- (void) viewDidLoad
{
	self.navigationController.navigationBar.tintColor = COOKBOOK_PURPLE_COLOR;
	self.navigationItem.rightBarButtonItem = BARBUTTON(@"Action", @selector(action:));
}

- (void) dealloc
{
	self.overlay = nil;
	[super dealloc];
}
@end