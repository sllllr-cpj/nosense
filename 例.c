#include"SDHF.h"

void 函数指针() {
	//函数指针的声明、赋值与调用

	int (*funcPtr)(int, int); // 声明指向返回int且接受两个int参数的函数的指针
	//返回类型 (*指针名)(参数类型列表)

	funcPtr = function;
	funcPtr = &function; //函数名隐式转换为地址，可省略取地址符。

	int result = funcPtr(3, 4);    // 直接调用
    /**int**/result = (*funcPtr)(3, 4); // 解引用调用（两种方式等价）
}

void qsort函数学习()//在stdlib.h里
//qsort通过快速排序算法对数组进行排序，而比较函数的作用是告诉排序算法两个元素的相对顺序；比较函数会返回一个整数值
//比较函数的返回值决定了元素的排列顺序。如果返回负数，第一个元素会被放在前面；返回正数则相反。比如，如果比较函数是a - b，那么升序排序；如果是b - a，就是降序排序。
{
	int a[10] = { 0 };//定义任意类型的数组

	qsort(a, 10, sizeof(a[0]), compar);//参数为:数组名（地址），数组大小，每个元素占用的字节数，比较函数的指针，用于定义排序规则（需用户自己实现）

}

int compar(const void* a, const void* b)//比较函数的两个参数是指向数组中两个元素的指针(与qsort搭配使用)
{
	int x = *(const int*)a; // 转换为实际类型;若为字符串型，则用strcmp，直接返回strcmp(const void* a, const void* b)
	int y = *(const int*)b;
	return x - y; // 升序规则
	//若为降序规则就返回y-x
}

void 条件判断语句简化() {
//括号内语句即实现了遍历，也实现了类似(*q!='\0')的条件判断;因为当*q为'a'时,整个表达式的值就是'a'当*q为'\0'时，整个表达式的值就是'\0'，循环终止
	int a[] = { 0 };
	int b[] = { 0 };

	int* p = a, * q = b;

	while (*p++ = *q++)
	{
		;
	}
	//'\0'的ASCII码值为0
	//许多条件判断语句都可以简化，例如if(a!=0&&b!=0)可简化为if(a&&b)
}

void strerror函数学习() {
//strerror会返回一个指针;使用时在括号内接收一个整数，常用errno：
	//errno是一个全局错误变量，须包含errno.h头文件，当C语言的库函数在程序执行过程中发生错误，就会把对应错误的错误码（0、1、2...）赋给errno
	//而strerror就是将错误码解释成对应错误的函数

	char* str = strerror(errno);
}

void 局部静态变量() {

	//对于需要记忆功能的函数，有时需要用到局部静态变量(在自定义函数内部定义的静态变量)
	static int a = 3;//初始化只在程序开始时执行一次，以后再被调用都不会再执行初始化
	a++;
	printf("%d\n", a);
	/**main函数中**/
		//function();--此时会输出4
		//function();--此时会输出5
}

void memcpy函数学习() {
	//memcpy函数的参数为(void*dest,void*src,size_t num)即(被修改对象指针，源对象指针，修改的字节数)
	//memcpy是在内存上对数据进行复制操作，可复制字符串、数组、结构体等任意数据结构
	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	int b[10] = { 0 };
	/**例**/

	int *p=memcpy(b, a, sizeof(b));//memcpy会返回dest的指针(void*)
	//同时需要注意，memcpy不能处理存在内存重叠情况的复制，如memcpy(a[0],a[2],5),因memcpy默认从前向后复制，会存在数据覆盖导致复制结果出错，应使用memmove
}//另外，须注意memcpy的参数是void*类型的指针，要记得强制类型转换

void memmove函数学习() {
	//memmove的参数与memcpy的参数完全相同，都为(void*dst,void*src,size_t num)
	//memmove的实现原理在内存不重叠时基本与memcpy相同，但在内存重叠时会增加条件判断，根据dest与src的相对位置选择前-后或后-前，正确实现复制
	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	int b[10] = { 0 };
	/**例**/

	int* p = memmove(b, a, sizeof(b));//memmove会返回dest的指针(void*)
}//另外，须注意memmove的参数是void*类型的指针，要记得强制类型转换

void 结构体内存对齐学习() {
	//结构体的第一个成员会放在与结构体变量偏移量为0的地址处
	//其他成员要放在偏移量为对齐数整数倍的地址处
	//对齐数为编译器默认对齐数与成员大小的较小值（vs的默认对齐数为8）
	//可以通过预处理命令修改默认对齐数--#pragma pack(想要的对齐数);#pragma pack()是取消修改命令

	typedef struct Stu {
		char a;//对齐数为1
		int b;//对齐数为4
		char c;//对齐数为1
	}S;
	//结构体的大小为最大对齐数的整数倍，若不足则补足
	S s;
	printf("%d\n", (int)sizeof(s));//此时会输出12，即结构体变量大小为12个字节
	//若存在嵌套结构体，则嵌套结构体对齐到自身最大对齐数的整数倍地址处，结构体整体大小就是所有对齐数的整数倍
	//小字节成员放在一起可以节省一些空间
}

void 位段（位域）学习() {
//位段是结构体的一种，目的是节省空间，位段的成员类型必须全部相同，且成员类型只能为整形（包括unsigned int或long/short）；char也可，因为char是按照ASCII码存放

	typedef struct SS {
		int a : 2;//冒号后的数字是表示这个成员的表示需要几个比特位；如我认为成员a将只表示0、1、2、3四种数字时，我只用两个比特位就可以全部表示
		int b : 5;
		int c : 10;
		int d : 30;//注意冒号后的数字不能超过成员类型一般所占的比特位，如int类型的成员不超过32，char类型的成员不超过8
	}S;
	S s = { 0 };
	printf("%d\n", (int)sizeof(s));//此时会输出8
	//位段的内存开辟方式是根据成员类型，如int则一次性开辟4个字节即32个比特位，如char则一次性开辟1个字节即8个比特位
	//位段一般不可移植，因为在不同编译器或操作系统中，成员在内存中从左向右或从右向左存放，存放前一个位段后剩下的空间利用与否都没有规定（C标准）
	//因此，各个编译器在内存中会对位段有不同的操作
}

void 枚举学习() {
	//枚举与结构体一样都是一种类型
	//枚举类型的成员一般是星期、月份、颜色等这种可以穷举的对象
	//枚举类型的成员成为枚举常量，一旦初始化不可更改
	typedef enum oricolor {
		green,//默认值为0，往下递增1，可以为每个成员初始化，但要从小到大
		red,
		blue
	}COLOR;
	/**main函数**/
	printf("%d %d %d", green, red, blue);//此时输出0 1 2
	COLOR s = red;//定义枚举变量
}//枚举可取代#define

void 内存存储（大小端字节序问题）() {

	//int a = 0x11223344
	// 低地址--------------------------------------------高地址
	//...[][][][44][33][22][11][][][][][][][][][][][][][][][][][][]...--小端字节序存储模式（低字节存放低地址）
	//...[][][][11][22][33][44][][][][][][][][][][][][][][][][][][]...--大端字节序存储模式（高字节存放低地址）
}//整形（包括char）在内存中的存放

void 联合体（共用体）学习() {
	//联合体也是一种自定义类型，特点是所有成员公用一块内存空间
	//联合体大小至少是最大成员的大小
	//当最大成员大小不是最大对齐数的整数倍时，会对齐到最大对齐数的整数倍
	//联合体的成员不能同时使用
	typedef union XX {
		int a;
		char b;
	}X;
	/**main函数**/
	X x;
	printf("%d\n", (int)sizeof(x));//此时会输出4
}
