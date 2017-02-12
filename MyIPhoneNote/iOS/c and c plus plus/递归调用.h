1，在调用一个函数的过程中，又出现直接或间接地调用函数本身。称为函数的递归调用。
函数调用自身，这个过程叫递归。
2，用递归法求n！。
	float fac(int n)
	{
		float f;
		if (n<0) {
			NSLog(@"data error!");
		}
		else if(n==0 || n==1) f=1;
		else f=fac(n-1)*n;
		return f;
	}
	int main (int argc, const char * argv[]) {
		int n=10;
		float y;
		y=fac(n);
		printf("%d!=%.0f",n,y);
		return 0;
	}
3,Hanoi塔问题。

void move(char x,char y){printf("%c-->%c,",x,y);}
void hanoi(int n,char one,char two,char three)
{
	if (n==1) {
		move(one,three);//将A座上一个盘子移动到C座。
	}
	else {
		hanoi(n-1,one,three,two);//将A座n－1个盘子移动到B座，借助C
		move(one,three);//将A座上一个盘子移动到C座。
		hanoi(n-1,two,one,three);//将B座上n-1个盘子移动到C座上，借助A
	}
	
}
int main()
{
	hanoi(2,'A','B','C');
}