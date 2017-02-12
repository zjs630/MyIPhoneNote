1,设置网页的宽度。
//在iPhone中，我们会用下述代码的方式指定屏幕宽度
<meta name="viewport" content="width=320" /><!--不适应iPad-->

//而在iPad中，则必须用device-width替代具体的宽度像素数。
<meta name="viewport" content="width=device-width" /><!--适应iPad--><meta name="viewport" content="user-scalable=no, width=device-width" />

//我们在设置宽度的同时可以设置可缩放的比例范围
<meta id="viewport" name="viewport" content="width=320; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;" />

<script type="text/javascript" charset="utf-8">
		window.onload = function() {
		  setTimeout(function(){window.scrollTo(0, 1);}, 100);
		}
</script>




2，使用Javascript来检测iPhone/iPod Touch的使用，从而将网页重定向iPhone相关的网页
if((navigator.userAgent.match(/iPhone/i)) || (navigator.userAgent.match(/iPod/i))) {
    if (document.cookie.indexOf("iphone_redirect=false") == -1) {
        window.location = "http://m.espn.go.com/wireless/?iphone&i=COMR";
    }
}
3,默认隐藏工具栏
iPhone的浏览器工具栏会在页面最顶端，卷动网页后才隐藏。这样在加载网页完成后显得很浪费空间，特别是横向屏幕时。我们可以让它自动卷动上去。
<script type="application/x-javascript">
   addEventListener("load", function()
   {
      setTimeout(hideAddressbar, 0);
   }, false);
   function hideAddressbar()
   {
      window.scrollTo(0, 1);
   }
</script>

4,怎么将地址里的%20这种类型的编码方式换成“ ”这种空格类型的编码方式？ 
https://github.com/mwaterfall/MWFeedParser/blob/master/Classes/NSString+HTML.m

