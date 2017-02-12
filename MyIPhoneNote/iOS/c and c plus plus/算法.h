1，用选择法对10个整数按由大到小顺序排序。
	void sort(int x[],int n)
	{
		int i,j,k,temp;
		for(i=0;i<n-1;i++)
		{
			k=i;
			for(j=i+1;j<n;j++)
				if (x[j]>x[k]){
					k=j;
				}
			if (k!=i) {
				temp=x[i];
				x[i]=x[k];
				x[k]=temp;
			}
			
		}
	}
	int main (int argc, const char * argv[]) {
		//定义一个整型数组
		int a[]={2,4,9,6,8,3,5,7,0,1};
		//用选择法对数组进行排序，
		sort(a,10);
		//输出数组中的数据
		for(int i=0;i<10;i++)
		{
			printf("%d  ",a[i]);
		}
		return 0;
	}
2,将字符串a复制为字符串b。
	//定义一个整型数组
	char a[]="Zhang Jingshun";
	int i;
	char b[20];
	for(i=0;a[i]!='\0';i++)
	{
		b[i]=a[i];
	}
	b[i]='\0';
	for(i=0;b[i]!='\0';i++)
	printf("%c",b[i]);
3,有一分数序列：
	2／1，3／2，5／3，8／5，13／8，21／13，...
	求这个数列的前20项之和。
解：
	main()
	{
		int i,t,n=20;
		float a=2,b=1,s=0;
		for (i=1; i<=n; i++) {
			s=s+a/b;
			t=a;
			a=a+b;//将前一项分子分母的和作为后一项的分子
			b=t;//将前一项的分子作为下一项的分母
		}
		printf("sum=%9.6f\n",s);
	}
4，一球从100m高度自由下落，每次落地后反跳回原高度的一半，再落下。
	求它再第10次落地时，共经过多少米？第10次反弹多高？
解：
	main()
	{
		float sn=100,hn=sn/2;
		int n;
		for (n=2; n<=10; n++) {
			sn=sn+2*hn;
			hn=hn/2;
		}
		printf("第10次落地共经过％fm.\n",sn);
		printf("第10次反弹％fm.\n",hn);
	}
5，猴子吃桃问题。
	猴子第一天摘下若干个桃子，当即吃了一半，还不过瘾，又多吃了一个。第二天早上又将剩下的桃子吃掉一半，又多吃了一个。
	以后每天早上都吃了前一天剩下的一半零一个。到第十天早上再想吃时，见只剩下一个桃子了。求第一天共摘多少个桃子。
解：算法1
	main()
	{
		int day,x1,x2=1;
		for(day=2;day>0;day--){
			x1=(x2+1)*2;
			x2=x1;
		}
		printf("total=%d\n",x1);
	}
	算法2，采用递归调用
	int fac(int day)
	{
		int f;
		if (day>10 || day <1) {
			printf("数据错误！");
		}
		else if(day==10) f=1; //第10天，桃子个数为1
		else f=(fac(day+1)+1)*2;
		//printf("第%d天共有%d个桃子。\n",day,f);
		return f;
	}
	int main (int argc, const char * argv[]) {
		int y,n=1;
		y=fac(n);
		printf("第%d天共有%d个桃子",n,y);
		return 0;
	}
6,打印杨辉三角。
	1
	1    1
	1    2    1
	1    3    3    1
	1    4    6    4    1
	......................
#define N 10
int main () 
{
	int i,j,a[N][N];
	for(i=0;i<N;i++)
	{
		a[i][i]=1;
		a[i][0]=1;
	}
    
	for(i=2;i<N;i++)
		for(j=1;j<=i-1;j++)
			a[i][j]=a[i-1][j-1]+a[i-1][j];
	
	
	for(i=0;i<N;i++)
	{
		for(j=0;j<=i;j++)
			printf("%5d",a[i][j]);
		printf("\n");
	}
	return 0;
}

7，计算两点之间的距离
- (CGFloat)distanceBetweenTwoPoints:(CGPoint)fromPoint toPoint:(CGPoint)toPoint
{
	float x = toPoint.x - fromPoint.x;
	float y = toPoint.y - fromPoint.y; 
	return sqrt(x * x + y * y);
}


















