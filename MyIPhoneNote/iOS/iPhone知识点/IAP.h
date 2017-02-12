http://www.cocoachina.com/bbs/read.php?tid-69165-fpage-2.html

In App Purchases（IAP 应用程序內购买）: 完全攻略

第一印象觉得In-App Purchase（简称IAP）非常简单。Apple提供的大量文档应该让开发者很快熟悉地熟悉。那麽，为什麽在你的应用中集成IAP特性就如此令人生厌呢？

这是因为在开发过程中不可避免会出现一些错误。而但这些错误发生的时候，你就抓瞎了。虽然Apple提供了有关IAP的大量文档，但他们并未提及集成IAP的详细步骤。而且对StoreKit集成过程中出现的问题也没有一个核对清单。另外对于为什麽诸如产品ID非法之类的问题也没有提供NSError之类的对象来告诉你原因。

在试用了各种可能的解决方桉后，你只能身心疲惫，彷徨无助。

为了提高你的效率和减少你的痛苦，我觉定利用此文来介绍一下实现IAP的详细步骤。本文很详细，有点长。甚至可能太长了，但不像Apple的文档，它提供了为实现IAP的每一个步骤。

废话少说，我们直入主题吧。


概况
IAP能正常工作的秘诀：分成两个步骤：

创建及提取产品描述
购买产品
第一个步骤是你可能遇到问题的部分。一旦你在代码中成功地获取了产品描述，编写购买产品的代码不过是小菜一碟。

我们先看看步骤1。

创建及提取产品描述
下面是有关创建产品及提取其描述的非常粗略的步骤：

创建唯一的App ID
生成及安装新的provisioning profile文件
在Xcode中更新 bundle ID 及 code signing profile
如果还没做的话，请在iTunes Connect中提交有关你程序的 metadata
如果还没做的话，请在iTunes Connect中提交你程序的二进制码
为IAP添加新产品
编写提取产品描述的代码
等待几小时
提取产品描述的代码非常简单，但其他步骤则很容易错。

注意： 为提取产品描述，你并不需要在iTunes Connect中创建IAP测试用户。



1. 创建唯一的App ID
为支持IAP，你的App ID不能包括通配符（“*”）。为确定你的App Id是否包括通配符，请登录http://developer.apple.com/iphone,在 iPhone Developer Program Portal中选择左边菜单中的 “App IDs”检查你的 App ID。

下面是一个唯一的App ID:

7DW89RZKLY.com.runmonster.runmonsterfree

下面不是一个唯一的 App ID:

7DW89RZKLY.com.runmonster.*

如果你还没有一个唯一的App ID，按如下步骤创建一个：

在developer portal中的 App IDs 部分，选择“New App ID”
填写下列信息：
Display name（显示名）: 选取一个不同的App ID的名称。你不能编辑或删除旧的App ID，所以你必须为你的App ID提供一个新名称以避免溷淆。
Prefix（前缀）: 生成一个新的前缀，或者如果你的程序是通过Keychain Services API分享数据的系列程序中之一的话，则选用已存在的前缀。
Suffix（后缀）: com.companyname.appname (这是通用格式 – 注意没有使用通配符）。
按 “Save”
按 App ID旁的“Configure” 链接
选取 “Enable In App Purchase”选择框
按“Done”
2. 创建一个新的Provisioning Profile文件
在创建了新的App ID后,你需要生成一个指向这个App ID的新provisioning profile。

下面就是令人痛苦的生成和安装新provisioning profile的详细步骤:

在 iPhone Developer Portal中, 选择左边的Provisioning部分
确保你处于Development 标籤下, 按下右上角的 “New Profile”
填入所需信息并指向你刚创建的唯一的App ID
如果你在Actions条目下看到 “Pending”，那麽请按下“Development”标籤标题进行刷新
点击 “Download” 下载新的profile文件
将profile文件拖入到Dock中Xcode图标上进行安装
如果你想在硬盘上保存provisioning profile，那麽你可以按如下步骤手工安装profile：
在Xcode中, 选择 Window > Organizer
选择左边 “Provisioning Profiles” 分类
Ctrl-按下profile > Reveal in Finder
将新profile拖入到 profile Finder 窗口
3. 更新Xcode 设置
在Xcode中安装了 profile 文件后，你需要对使用此provisiong profile的项目进行一些编辑工作：

编辑项目 .plist 文件使其 Bundle ID 与 App ID 匹配。忽略ID开始部分的字母数字序列。例如，在Developer Portal中你的App ID为“7DW89RZKLY.com.runmonster.runmonsterfree”，那麽在Bundle ID中你只需输入“com.runmonster.runmonsterfree” 。
编辑项目的 target 信息以使用新的provisioning profile:
选取 Project > Edit Active Target
选取顶部“Build” 标籤
选取需要的 configuration (通常为 Debug)
在Code Signing Identity中选择新的provisioning profile
在Code Signing Identity之下的行中(可能名为 Any iPhone OS Device)选择新的provisioning profile
4. 添加你的应用程序
如果你的程序已经发表到App Store了，那麽可以略过此步骤。

在你将产品添加到 iTunes Connect之前，你必须添加此产品所需的程序。如果你的程序还没有100%完成也无需担心，你可以先提交具有部分数据的程序，最后再提交真实的程序。

注意: 只有 SKU 和 version（版本）部分是以后不可修改的

登录到 http://developer.apple.com/iphone
点击右边链接进入 iTunes Connect
注意：你必须先登录到developer.apple.com，否则会有不测发生（译者注：具体是什麽不测我也不太清楚，胆大的请自己试一下）
在 iTunes Connect主页点击 “Manage Your Applications”
在右上角点击“Create New Application”
填写程序所需的一切信息。当要求程序二进制码时，请选择稍后上传选项。
5. 提交程序二进制码
Apple的文档中没有任何地方提及详情，但它却是必须的步骤。要成功测IAP功能，你必须提交程序的二进制码。即使你的程序还没有100%完成，你仍然需要提交二进制码。然而，你也可以立即摈弃你的二进制码，使其不会进入审核阶段。

下面这些步骤非常关键，我可是因为少做了某些步骤而度过了一段非常痛苦的时间：

生成App Store发佈版程序
如果你不知怎麽做，请在 iPhone Developer Portal 中点击左方的 Distribution标籤，并选择 “Prepare App” 标籤。然后，根据蓝色链接的指示：
获取iPhone发行许可证
创建并下载在App Store发行所需的iPhone Distribution Provisioning Profile
在Xcode中生成程序的发行版
在iTunes Connect中进入程序页
选择 “Upload Binary”
上传.zip压缩程序
如果你的程序还没有100%完成以进行审核，那麽请点击iTunes Connect中你程序首页中的 “Reject Binary”链接。程序的状态应该更新为 “Developer Rejected”.
不用担心，由于程序的状态是“Developer Rejected”，Apple是不会对其进行审核的。你可以在任何时候提交程序的新版本并使其状态为“Developer Rejected”，这不会对以后程序正式提交的等待时间有任何影响。

6. 添加产品
完成了以上所有步骤后，我们最终可以向iTunes Connect中添加产品了。

确保登录到 http://developer.apple.com/iphone
进入 iTunes Connect 主页
点击 “Manage Your in App Purchases” 链接
点击 “Create New”
选择你的程序
填写下列产品信息：
Reference Name（参考名称）: 产品的通用名称。比如，我使用的是 “Pro Upgrade”。此名称是不允许进行编辑的，它不会显示于App Store中。
Product ID（产品ID）: 你产品的唯一id。通常格式是 com.company.appname.product，但它可以说任何形式。它并不要求以程序的App ID作为前缀。
Type（类型）: 有三种选择
Non-consumable（非消耗品）: 仅需付费一次 (例如你希望将出现从免费版升级为专业版）
Consumable（消耗品）: 每次下载都需要付费
Subscription（预订）: 循环反覆
Price Tier（价格等级）: 产品价格。参见不同等级的价格列表。
Cleared for Sale（等待销售）: 一定要选取此项，否则的话，测试时会发生非法产品ID的错误。
Language to Add（增加的语言）: 选一项。下列两项将出现：
Displayed Name（显示名称）: 用户看到的产品名称。比如我选择 “Upgrade to Pro”。
Description（描述）: 对产品进行描述。此处输入的文本将与Displayed Name 及 Price 一起在你代码中提取 SKProduct时出现。
Screenshot（截屏）: 展示你产品的截屏。儘管屏幕上会显示“提交截屏会触发产品审核过程”之类的文字（个人拙见，这是非常糟糕的设计），你还是可以安全地提交截屏而不会使产品进入审核过程。存储后，选择“Submit with app binary” （随程序二进制码一起提交）选项。是产品与程序二进制绑定在一起，所以在你最后正式提交100%完成的程序二进制码时，产品也会随之提交。
点击 “Save”
7. 编写代码
下面我们开始编写代码对刚加入到iTunes Connect中的产品信息进行提取。我访问产品数据，我们需要使用 StoreKit framework。

注意： StoreKit 无法在模拟器上工作。你必须在真机上进行测试。

1.添加 StoreKit framework 到你的项目中。
2.添加SKProduct引用到你的 .h 文件中：

复制代码
// InAppPurchaseManager.h
#import <StoreKit/StoreKit.h>
#define kInAppPurchaseManagerProductsFetchedNotification @"kInAppPurchaseManagerProductsFetchedNotification"
@interface InAppPurchaseManager : NSObject <SKProductsRequestDelegate>
{
    SKProduct *proUpgradeProduct;
    SKProductsRequest *productsRequest;
}
																   
注意: InAppPurchaseManager 是一个单例类，它处理程序中所有IAP任务。它是本文中的示例程序。 

3.产品请求，并在相应.m文件中实现代理协议： 
复制代码
// InAppPurchaseManager.m
- (void)requestProUpgradeProductData
{
    NSSet *productIdentifiers = [NSSet setWithObject:@"com.runmonster.runmonsterfree.upgradetopro" ];
    productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];
    
    // we will release the request object in the delegate callback
}
#pragma mark -
#pragma mark SKProductsRequestDelegate methods
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSArray *products = response.products;
    proUpgradeProduct = [products count] == 1 ? [[products firstObject] retain] : nil;
    if (proUpgradeProduct)
    {
        NSLog(@"Product title: %@" , proUpgradeProduct.localizedTitle);
        NSLog(@"Product description: %@" , proUpgradeProduct.localizedDescription);
        NSLog(@"Product price: %@" , proUpgradeProduct.price);
        NSLog(@"Product id: %@" , proUpgradeProduct.productIdentifier);
    }
    
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@" , invalidProductId);
    }
    
    // finally release the reqest we alloc/init’ed in requestProUpgradeProductData
    [productsRequest release];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerProductsFetchedNotification object:self userInfo:nil];
}
																   
上面代码有几点需要注意： 

指定产品id时，你必须使用完整产品id。例如，上例中使用 “com.runmonster.runmonsterfree.upgradetopro”。仅使用 “upgradetopro” 将不会正常工作。 
如果在productsRequest:didReceiveResponse:中response.products 为 nil，而你的产品id出现于 response.invalidProductIdentifers 数组中时，那麽请做好心理准备开始一场徒劳的搜索战吧。 StoreKit API没有提供任何帮助，也没有任何指示关于为什麽你的id是无效的。很可爱，不是吗？ 
SKProduct类提供了有关程序标题和描述的本地化版本，但是价格则没有本地化版本。下面是针对此疏忽提供的代码： 
复制代码
// SKProduct+LocalizedPrice.h
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
@interface SKProduct (LocalizedPrice)
@property (nonatomic, readonly) NSString *localizedPrice;
@end

复制代码
// SKProduct+LocalizedPrice.m
#import "SKProduct+LocalizedPrice.h"
@implementation SKProduct (LocalizedPrice)
- (NSString *)localizedPrice
{
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:self.priceLocale];
    NSString *formattedString = [numberFormatter stringFromNumber:self.price];
    [numberFormatter release];
    return formattedString;
}
@end

加入上述代码，测试一下。你应该在控制台窗口中看见产品信息了。然而更大的可能是，你得到了一个无效的产品id。我下一篇文章将介绍怎样对这个问题进行调试。但是，下面的步骤8有可能是阻碍你前进的障碍。 

8. 等待几小时 
遵循了上述所有步骤，但是你的产品仍然是无效的？你是否两次，三次，四次不懈努力地确认你是否遵循了上面提到的每个步骤？你是否已经对网上IAP信息少得可怜而感到绝望？ 

那麽，你应该等待。 

你的产品要进入iTunes Connect使得Apple准备好沙箱环境需要一些时间。对于我而言，我是经过了无数次产品无效错误的绝望。而在24小时后，我没有修改任何一行代码，但产品id变为有效。我认为要使产品发佈到Apple的网络系统需要几个小时的时间，但如果你有时间的话，你可以像我一样等上24个小时。 

购买产品 
至此你应该已经成功地获取了 SKProduct 描述。比较而言，支持购买产品相对简单些。仅需下面三个步骤： 

编写代码支持事务（transaction） 
在iTunes Connect中添加程序测试用户 
在设备中登录你的 iTunes Store 帐号 
购买测试 
我们从编写支持事务所需代码开始。 

1. 编写代码支持事务 
首先注意：你将负责开发产品购买的用户界面。StoreKit 未提供任何与用户界面相关的元素。如果你希望你的购买用户界面与App Store一样，那麽你要自己完成。 

下面所有代码都是有关事务处理的后台部分。这是一个单独的类只有一条简单的API以供外部类（比如view controller）调用进行购买。如果你找到将其集成到你程序的购买部分的方法，那麽我推荐你使用类似方桉。 

首先，需要遵循 SKPaymentTransactionObserver 协议: 
复制代码
// InAppPurchaseManager.h
// add a couple notifications sent out when the transaction completes
#define kInAppPurchaseManagerTransactionFailedNotification @"kInAppPurchaseManagerTransactionFailedNotification"
#define kInAppPurchaseManagerTransactionSucceededNotification @"kInAppPurchaseManagerTransactionSucceededNotification"
…
@interface InAppPurchaseManager : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>
{
…
}
// public methods
- (void)loadStore;
- (BOOL)canMakePurchases;
- (void)purchaseProUpgrade;
@end

上面我们定义了两个新的notification，它们将作为购买事务的结果被发送。在上例中我们仍然使用与获取产品描述同一个InAppPurchaseManager类。 
复制代码
// InAppPurchaseManager.m
#define kInAppPurchaseProUpgradeProductId @"com.runmonster.runmonsterfree.upgradetopro"
…
#pragma -
#pragma Public methods
//
// call this method once on startup
//
- (void)loadStore
{
// restarts any purchases if they were interrupted last time the app was open
[[SKPaymentQueue defaultQueue] addTransactionObserver:self];

// get the product description (defined in early sections)
[self requestProUpgradeProductData];
}
//
// call this before making a purchase
//
- (BOOL)canMakePurchases
{
return [SKPaymentQueue canMakePayments];
}
//
// kick off the upgrade transaction
//
- (void)purchaseProUpgrade
{
SKPayment *payment = [SKPayment paymentWithProductIdentifier:kInAppPurchaseProUpgradeProductId];
[[SKPaymentQueue defaultQueue] addPayment:payment];
}
#pragma -
#pragma Purchase helpers
//
// saves a record of the transaction by storing the receipt to disk
//
- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchaseProUpgradeProductId])
{
// save the transaction receipt to disk
[[NSUserDefaults standardUserDefaults] setValue:transaction.transactionReceipt forKey:@"proUpgradeTransactionReceipt" ];
[[NSUserDefaults standardUserDefaults] synchronize];
}
}
//
// enable pro features
//
- (void)provideContent:(NSString *)productId
{
if ([productId isEqualToString:kInAppPurchaseProUpgradeProductId])
{
// enable the pro features
[[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"isProUpgradePurchased" ];
[[NSUserDefaults standardUserDefaults] synchronize];
}
}
//
// removes the transaction from the queue and posts a notification with the transaction result
//
- (void)finishTransaction:(SKPaymentTransaction *)transaction wasSuccessful:(BOOL)wasSuccessful
{
// remove the transaction from the payment queue.
[[SKPaymentQueue defaultQueue] finishTransaction:transaction];

NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:transaction, @"transaction" , nil];
if (wasSuccessful)
{
// send out a notification that we’ve finished the transaction
[[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionSucceededNotification object:self userInfo:userInfo];
}
else
{
// send out a notification for the failed transaction
[[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionFailedNotification object:self userInfo:userInfo];
}
}
//
// called when the transaction was successful
//
- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
[self recordTransaction:transaction];
[self provideContent:transaction.payment.productIdentifier];
[self finishTransaction:transaction wasSuccessful:YES];
}
//
// called when a transaction has been restored and and successfully completed
//
- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
[self recordTransaction:transaction.originalTransaction];
[self provideContent:transaction.originalTransaction.payment.productIdentifier];
[self finishTransaction:transaction wasSuccessful:YES];
}
//
// called when a transaction has failed
//
- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
if (transaction.error.code != SKErrorPaymentCancelled)
{
// error!
[self finishTransaction:transaction wasSuccessful:NO];
}
else
{
// this is fine, the user just cancelled, so don’t notify
[[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}
}
#pragma mark -
#pragma mark SKPaymentTransactionObserver methods
//
// called when the transaction status is updated
//
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
for (SKPaymentTransaction *transaction in transactions)
{
switch (transaction.transactionState)
{
case SKPaymentTransactionStatePurchased:
[self completeTransaction:transaction];
break;
case SKPaymentTransactionStateFailed:
[self failedTransaction:transaction];
break;
case SKPaymentTransactionStateRestored:
[self restoreTransaction:transaction];
break;
default:
break;
}
}
}

要测试上面的新代码，你还需要编写调用 loadStore, canMakePurchases 以及 purchaseProUpgrade 方法的代码。 

有关上述代码的详细解释，请参考官方 In App Purchase Programming Guide （IAP编程指南） 

上述代码有几个部分是针对我的程序的。例如，在 provideContent:中，NSUserDefaults 中的@”isProUpgradePurchased” BOOL 字段被设定为 YES。程序的其他部分将检查此BOOL值以确定是否需要启动专业版功能。如果你正好也要实现免费升级专业版的功能，那麽你可以使用同样的方法。 

2. 添加测试用户 
为测试上述代码，你需要在 iTunes Connect 中创建测试用户以对IAP功能进行测试。你可以使用测试帐号购买产品而不被Apple收取费用。 

按以下步骤创建测试用户： 

登录到  http://developer.apple.com/iphone 
进入 iTunes Connect 
选择iTunes Connect首页中的 “Manage Users” 
选择 “In App Purchase Test User” 
选择 “Add New User” 
填入用户信息. 所有信息都不必是合法的。建议使用虚假简短的email地址及简短的密码。 
选择 “Save” 
测试时你需要输入这些email地址和密码。 

3. 在你的设备中退出登录 
在进行程序购买功能测试前，你必须在你的设备中退出iTunes Store。遵循以下步骤： 

打开Settings App 
点击 “Store” 行 
点击 “Sign Out” 
4. 购买测试 
现在，终于可以开始进行IAP功能的测试了。测试很简单： 

运行你设备中的程序 
进行购买 
当程序提示输入用户名和密码时，输入参数用户的信息 
如果你使用同一账户进行购买时，系统将提示你已经购买了此产品。按“Yes”就可以再次下载此产品。 

总结 
实现IAP功能比想象的要複杂许多。我可是经过无数痛苦的经历才完成我的程序。希望能够帮助其他开发者减轻他们的痛苦。应用程序內购买



------------------------------------------------------------------------------
In App Purchase 个人使用总结   
http://www.cocoachina.com/bbs/read.php?tid-11357.html
http://www.cocoachina.com/bbs/read.php?tid=38833&keyword=iap
http://www.cocoachina.com/bbs/read.php?tid=75924&keyword=iap


管理提醒: 本帖被 nono 从 iPhone开发 / iPad开发 一般讨论区 移动到本区(2010-03-21)

上一个项目用到了In App Purchase,发现现在大家对这个挺关注的，把上次写的总结贴出来给大家看一下，希望对大家有点帮助!

一 有关如何在程序中加入In APP Purchase 的内容参考下面的连接
http://developer.apple.com/iphone/library/documentation/NetworkingInternet/Conceptual/StoreKitGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40008267-CH1-SW1

二　我的程序具体步骤
1 添加Storekit.Framework,编写自己的storeObsever，用于处理交易，代码如下，其中completeTransaction和failedTransaction两个函数是自定义的用来处理交易成功与失败其它的就都是SKPaymentTransactionObserver这个代理要求的。
代码
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import <StoreKit/SKPaymentTransaction.h>
@interface MyStoreObserver : NSObject < SKPaymentTransactionObserver > {
}
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction;
- (void) completeTransaction: (SKPaymentTransaction *)transaction;
- (void) failedTransaction: (SKPaymentTransaction *)transaction;
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;
-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;
@end

//- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions函数用来更新transactions的状态
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    for (SKPaymentTransaction* transaction in transactions)  {  
       switch (transaction.transactionState)  {  
           case SKPaymentTransactionStatePurchased:  
               [self completeTransaction:transaction];  
               break;  
           case SKPaymentTransactionStateFailed: 
                [self failedTransaction:transaction];  
               break;  
           case SKPaymentTransactionStateRestored: 
                break;  
           default:  
               break;  
       }  
   } 
} 
2　在程序中添加storeObsever,最好在applicationDidFinishLaunching中添加
MyStoreObserver *tempObserver = [[MyStoreObserver alloc] init];  
self.observer = tempObserver;  
[tempObserver release];
[[SKPaymentQueue defaultQueue] addTransactionObserver:self.observer]; 

3 发送付费请求,在相应的类中实现SKProductsRequestDelegate，别忘记定义自己产品的identifier
//请求产品信息 
 #define kMyFeatureIdentifier yourProductIdentifiers  （你自己的产品identifiers)
SKProductsRequest *request= [[SKProductsRequest alloc] initWithProductIdentifiers: 
 [NSSet setWithObject: kMyFeatureIdentifier]]; 
  request.delegate = self;
 [request start];  
 代理方法相关代码,如果请求成功的话就可以发送付费请求  
#pragma mark request delegate
  //!收到产品的消息 
 - (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{  
     SKPayment *payment = [SKPayment paymentWithProductIdentifier:kMyFeatureIdentifier]; 
      [[SKPaymentQueue defaultQueue] addPayment:payment]; 
     [request autorelease];
       }
 - (void)request:(SKRequest *)request didFailWithError:(NSError *)error{  
     UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"Alert" message:[error localizedDescription]  delegate:nil c
                                                ancelButtonTitle:NSLocalizedString(@"Close",nil)  otherButtonTitles:nil];  [alerView show]; [alerView release]; 
 }
 
 ４  接下来就是Apple自己的付费相关处理了，需要做是就是点击按钮来确定付费
 ５ 交易完成后需要向Apple验证这次交易是否成功，要不然没成功就把产品给别人的话，那就亏了，在１中可以看到当交易成功时会调用自定义的completeTransaction函数，在该函数中我们需要验证transactionReceipt 关于验证SKPaymentTransaction的transactionReceipt　transactionReceipt是只有当SKPaymentTransaction完成时，即transactionState 被设置为SKPaymentTransactionStatePurchased 或 SKPaymentTransactionStateRestored时才被创建，因此只有这两种状态下能去验证transactionReceipt
 
 原始思路及具体步骤如下:  
 a 从SKPaymentTranscation的实例中将transactionReceipt转化为NSString   
  NSString *temptransactionReceipt  = [[NSString alloc] initWithData:[mytransaction transactionReceipt] encoding:NSUTF8StringEncoding];
 
 如果用NSLog的方法将其写出来显示如下,里边有很多的‘+’ { "signature" = 
     "AZNZdoggtjbU/wMqZ4SSd3lgkxbWr+/zcV7Oez4io7f5oPMliKlQzWW4vj+FLsVyhjyyuPyTSugJ6m4Hrp+CjdAptGZg4iWExoyE6stltg0EfD8Ezggjg5q04ws74pMZ/0aRgjedua8dCMMqR7C8ZjojfOYU6LrFiK7qbUUiV+inMIIDUzCCAjugAwIBAgIIZRSRTdlYBLUwDQYJKoZIhvcNAQEFBQAwfzELMAkGA1UEBhMCVVMxEzARBgNVBAoMCkFwcGxlIEluYy4xJjAkBgNVBAsMHUFwcGxlIENlcnRpZmljYXRpb24gQXV0aG9yaXR5MTMwMQYDVQQDDCpBcHBsZSBpVHVuZXMgU3RvcmUgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMDkwNjE1MjIwNTU2WhcNMTQwNjE0MjIwNTU2WjBkMSMwIQYDVQQDDBpQdXJjaGFzZVJlY2VpcHRDZXJ0aWZpY2F0ZTEbMBkGA1UECwwSQXBwbGUgaVR1bmVzIFN0b3JlMRMwEQYDVQQKDApBcHBsZSBJbmMuMQswCQYDVQQGEwJVUzCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAytGMXZy3gitJ2JMKFojSDynC/9yYezyn9HBX+u3/3VcpWE2XhcgGKYqNBA1+AewOzrKO774OsokTu4qymEx10ph8UTmsZewB0ESMHBEjF7FN6/HccsQUYC3WagrHnT12HG2Ih0OAm/ZhpWzj0HS4m813LpIyo00sewMvMNL2hkcCAwEAAaNyMHAwDAYDVR0TAQH/BAIwADAfBgNVHSMEGDAWgBQ2HejinYLSARi1MmsO10MLkVhDOjAOBgNVHQ8BAf8EBAMCB4AwHQYDVR0OBBYEFKmDg/IZSMU+ElcIFMzNo36ZXyT1MBAGCiqGSIb3Y2QGBQEEAgUAMA0GCSqGSIb3DQEBBQUAA4IBAQARpJs+O2Y3gL8gHdASkrfZHFpwINd1VcB5VF5LkVpnFz63zylA/3cGIDG91b/d5NIwZjkVt4Bgvd62o/mCbzCsWiNfSKTJVFK1D78BDQoSO2oHTuQuz1BR7xzNHxQZ90zUS6ZX9SC8N3g3A1jEtAyDhZNB+CRBBXLwZdnBUeBsT9QLpjvTnekZcGTnU08zfCjGF3eBJEu9eP6WgexK1xMSp72kEOmYbn6yTi3D4YrcYx4Q3n/57VBP2en8qXWeP5oHDsLTGzLRsWdoB3VxJLrF2ivL8JS8zqC0qyac452pN6xunRuzyyfpaqzQL12BzFEe44xna2byektSbtquA5LNAAAAAA=="; "purchase-info" = "ewoJIml0ZW0taWQiID0gIjMzMDU5OTg4MCI7Cgkib3JpZ2luYWwtdHJhbnNhY3Rpb24taWQiID0gIjEwMDAwMDAwMDAwOTEyNTgiOwoJInB1cmNoYXNlLWRhdGUiID0gIjIwMDktMTAtMTQgMDY6MDY6NTQgRXRjL0dNVCI7CgkicHJvZHVjdC1pZCIgPSAiY29tLnNlbnNreS5jbmFtZXNpZ3B1cmNoYXNlY29uc3VtYWJsZSI7CgkidHJhbnNhY3Rpb24taWQiID0gIjEwMDAwMDAwMDAwOTEyNTgiOwoJInF1YW50aXR5IiA9ICIxIjsKCSJvcmlnaW5hbC1wdXJjaGFzZS1kYXRlIiA9ICIyMDA5LTEwLTE0IDA2OjA2OjU0IEV0Yy9HTVQiOwoJImJpZCIgPSAiY29tLnNlbnNreS5jc2lnbmF0dXJlYXBwIjsKCSJidnJzIiA9ICIxLjAiOwp9"; "pod" = "100"; "signing-status" = "0";}  　 
 b然后通过Post的方法将其提交给服务器,在这里只是将transactionReceipt传给服务器，验证由服务器完成。代码如下，    
  NSString *requestStirng =[NSString stringWithFormat: @"receipt_data=%@",temptransactioReceipt];  
 
 requestStirng = [requestStirng stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]; 
 
  NSData *postData = [NSData dataWithBytes:[requestStirng UTF8String] length:[requestStirng length]]; 
 NSMutableURLRequest *connectionRequest = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:[kURL          stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]]]; 
  [connectionRequest setHTTPMethod:@"POST"];  
 [connectionRequest setTimeoutInterval:120.0]; 
  [connectionRequest setCachePolicy:NSURLRequestUseProtocolCachePolicy]; 
  [connectionRequest setHTTPBody:postData];  
 出现的错误，服务器用传过去的receipt_data向Apple验证，通不过，但将用NSLog的方法在后台写出的temptransactionreceipt向Apple验证能通过  错误原因  对比发现通过URL传给服务器的字符串不能很好的完成urlEncode，在里边出现的+不能自动进行编码转化，因为在Objective-C 中不能将NSString 真正的实现URL encode , 
 解决方法可参考下面的地址  
 http://simonwoodside.com/weblog/2009/4/22/how_to_really_url_encode/ 
  但当我用上面地址给出的方法进行编码后仍不能解决该问题,原因不明 
  解决办法:
 在将transactionReceipt转化成的NSString传给服务器之前先进行转化，将里边的+转换为%2B ， 将步骤a中的代码改为 
  NSString *temptransactionReceipt  = [[NSString alloc] initWithData:[mytransaction transactionReceipt] encoding:NSUTF8StringEncoding]; 
  temptransactionReceipt =  [temptransactionReceipt stringByReplacingOccurrencesOfString:@"+" withString:@"%2B"];  
 
 
 ６　服务器端验证相关代码 其中XML为自定义的一个类，getHeader所做的工作就是把receipt数据Post给Apple然后得到返回的结果返回  
 $url = "https://buy.itunes.apple.com/verifyReceipt";/ $receipt = json_encode(array("receipt-data" => base64_encode($receipt_data)));     
 $response_json = $Xml->getHeader($url, $receipt);    
  $response = json_decode($response_json['content'], true);
 
 getHeader的代码如下  public function getHeader($url, $data)         { 
                        $ch = curl_init(); 
                         $timeout = 300; // set to zero for no timeout  
                      curl_setopt($ch, CURLOPT_URL, $url); 
              //       curl_setopt($ch, CURLOPT_ENCODING, 'gzip'); 
                       curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 1); //post到https 
                       curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
                        curl_setopt($ch, CURLOPT_POST, true); 
                       curl_setopt($ch, CURLOPT_POSTFIELDS, $data);  
                      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);  
                      curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);//跟随页面的跳转
              //       curl_setopt($ch, CURLOPT_HEADER, true); 
                       curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout); 
                        $handles = curl_exec($ch); 
                       $header = curl_getinfo($ch);
                        curl_close($ch); 
                       $header['content'] = $handles; 
                       return $header; 
             } 
 