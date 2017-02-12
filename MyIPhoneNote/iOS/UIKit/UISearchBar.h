//1,.在使用UISearchBar时，将背景色设定为clearColor，或者将translucent设为YES，都不能使背景透明，
//经过一番研究，发现了一种超级简单和实用的方法：

[[searchbar.subviews objectAtIndex:0]removeFromSuperview];
背景完全消除了，只剩下搜索框本身了。 