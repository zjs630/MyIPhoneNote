1,如果一个变量只有几种可能的值，可以定义为枚举类型。
所谓“枚举”是指将变量的值一一列举出来，变量的值只限于列举出来的值的范围。
2，声明枚举类型用enum开头。如：
	enum weekday {
		sun,mon,tue,wed,thu,fri,sat
	};//其中的枚举元素都为常量，只可在定义时为其赋值。c语言编译按定义时的顺序使它们的值为0，1，2，...
3,定义枚举变量。
	enum weekday work1,work2;//work1 or work2 的值只能是枚举元素其中的一个值。
4，还可将2和3和在一起写
enum weekday {
	sun,mon,tue,wed,thu,fri,sat
}work1，work2;
5，为枚举变量赋值，一般只将枚举中的某个元素赋给它。如：
	work1 ＝ fri;
	不能直接将一个整数赋值给枚举变量，需要强制类型转换。如：
	work1 ＝ (enum weekday)2;

6，口袋中由红、黄、蓝、白、黑5种颜色的球若干个，每次从口袋中先后取出3个球，
	问得到3种不同色的球的颜色组合的可能取法。
	int main (int argc, const char * argv[]) {
		enum color {red,yellow,blue,white,black};
		enum color i,j,k,pri;
		int n=0,loop;
		for(i=red;i<=black;i++)
			for(j=red;j<=black;j++)
				if (i!=j) {
					for(k=red;k<=black;k++)
						if ((k!=i)&&(k!=j)) {
							n=n+1;
							printf("%-4d",n);
							for(loop=1;loop<=3;loop++)
							{
								switch (loop) {
									case 1: pri=i; break;
									case 2: pri=j; break;
									case 3: pri=k; break;
									default: break;
								}
								switch (pri) {
									case red: printf("%-10s","red"); break;
									case yellow: printf("%-10s","yellow"); break;
									case blue: printf("%-10s","blue"); break;
									case white: printf("%-10s","white"); break;
									case black: printf("%-10s","black"); break;								
									default: break;
								}
							}
							printf("\n");
						}
					
				}
		return 0;
	}
