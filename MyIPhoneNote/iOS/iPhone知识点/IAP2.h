https://developer.apple.com/in-app-purchase/
http://www.2cto.com/kf/201212/180489.html

1，Manage In-App Purchase
如果程序没有添加IAP，会显示No In-App Purchases have been set up for this app. To set one up, click Create New.
点击Create new，
（1），Select Type

//选择你要创建的IAP类型。Select the In-App Purchase type you want to create.

In-App Purchase lets you sell a variety of items directly within your free or paid app, including premium content, virtual goods, and subscriptions. And just like apps you sell on the App Store, you receive 70% of the purchase price.

In-App Purchases中，有两种类型的是最经常使用的

Consumables. 消耗品。购买的物品，可以被使用。用完了就没有了，再用需要再次购买，可以购买多次。比如游戏中的子弹，人物的生命值，鱼吃的食物等，通常作为消耗品。

Non-Consumables.非消耗品（购买一次，永久使用，不会过期）。比如一些装备，或者软件从免费版升级为专业版

Auto-Renewable Subscriptions
Auto-renewable Subscriptions allow the user to purchase updating and dynamic content for a set duration of time. Subscriptions renew automatically unless the user opts out, such as magazine subscriptions.


Free Subscription 免费订阅
Free subscriptions are a way for developers to put free subscription content in Newsstand. Once a user signs up for a free subscription, it will be available on all devices associated with the user’s Apple ID. Note that free subscriptions do not expire and can only be offered in Newsstand-enabled apps.


Non-Renewing Subscription
Non-Renewing Subscriptions allow the sale of services with a limited duration. Non-Renewing Subscriptions must be used for In-App Purchases that offer time-based access to static content. Examples include a one week subscription to voice guidance feature within a navigation app or an annual subscription to online catalog of archived video or audio.



2,注意问题， My problem: My device was jailbroken and had Cydia on it. I restored the device to factory defaults (Not jailbroken) and it worked the first time and returned the product ID no problem.
必须真机测试，越狱的机器也不行。只能在iOS 3.0的系统访问。

How do I create a product identifier?

The In-App Purchases form is used to generate In-App Purchase products. It contains a Product ID field that must be filled. Use this field to specify the product identifier for your product. Follow the steps below to create a product identifier:

Log in to iTunes Connect, then navigate to the Manage Your Applications module present in the home page.
iTunes Connect takes you to the Manage Your Apps page, which contains a list of all your applications. Select the application for which you want to create In-App Purchase products, then click on the Manage In-App Purchases button in the ensuing page for this application, then on the Create button in the next page.
Select a type for your In-App Purchase product. iTunes Connect takes you to the In-App Purchases form, which contains a Save button. Fill out the Product ID as well as all the other fields present in that form.













In-App Purchases中，有两种类型的是最经常使用的

Consumables. 消耗品。购买的物品，可以被使用。用完了就没有了，再用需要再次购买，可以购买多次。比如游戏中的子弹，人物的生命值，鱼吃的食物等，通常作为消耗品。

Non-Consumables.非消耗品（购买一次，永久使用，不会过期）。比如一些装备，或者软件从免费版升级为专业版


1. 创建唯一的App ID
为支持IAP，你的App ID不能包括通配符（“*”）。
2. 创建一个新的Provisioning Profile文件
3. 更新Xcode 设置
4. 添加你的应用程序
5. 添加产品
你的产品要进入iTunes Connect使得Apple准备好沙箱环境需要一些时间。
6,编码
7，测试
要完成Manage your contracts, tax, and banking information









注意：（1）要实现IAP必须填写，Contracts, Tax, and Banking Information
（2）Configure your App ID for In-App Purchase.
use com.tt139.ttquanzi rather than com.tt139.*
(3)Create test user accounts.


