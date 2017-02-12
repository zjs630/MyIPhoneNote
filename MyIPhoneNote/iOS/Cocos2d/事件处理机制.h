1，Layer 对象的主要仸务就是响应 iPhone 的用户输入,因此 Cocos2d-iPhone 
引擎的事件处理机制的核心就是如何将系统的 
用户输入(User Input)信息传递给每 Layer 对象。
2，类 TouchDispatcher 是其中负责承上启下的核心类,Cocos2d-iPhone 
引擎通过以下依次 3 个步骤,全面实现了针对用户触摸输入的响应。
1)接管:从系统 iPhoneOS 的标准UIView 获得触摸输入。 
2)分収:按照预先定义好的逻辑分发给各种注册对象。
3)处理:注册对象之间如何协调响应用户的输入。


// 检查是否触摸到的地方是在用户界面元素的区域里面
//使用CGRectContainsPoint方 法来检查接收到的触摸是否落在了uiframe精灵里面,也就是用户界面的区域里 
//面。这是个简单的“点落在边界框中”的检查。
-(bool) isTouchForMe:(CGPoint)touchLocation
{
	CCNode* node = [self getChildByTag:UILayerTagFrameSprite]; 
	return CGRectContainsPoint([node boundingBox], touchLocation);
}

