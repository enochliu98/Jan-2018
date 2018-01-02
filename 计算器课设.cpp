/*********************************
***********************************
***     数据结构期末课程设计     ***
************************************
***     作业名称：多项式计算器   ***
***     使用的数据结构：栈       ***
***     UI：使用easyx实现        ***
***********************************
***     实现功能：               ***
***     1.加减乘除               ***
***     自加，乘方运算           ***
***     2.实数，多位数运算       ***
***     3.图形界面实现           ***
***********************************     
**********************************/


#include<iostream>
#include<stdlib.h>  
#include<stdio.h>  
#include<math.h>  
#include<string.h>  
#include<graphics.h>      // 就是需要引用这个图形库
#include<conio.h>
#include<windows.h>


#define WINSIZEX 401	//窗口大小
#define WINSIZEY 471
#define WINKEYY (WINSIZEY - 1) / 8	//行间距
#define WINKEYX (WINSIZEX - 1) / 4

#define MAX 100
#define TRUE 1

#pragma warning(disable:4996) 
using namespace std;

typedef struct {
	char Str[MAX];/*存储原算术表达式*/
	int Long;
}STR;
struct {
	int x[2];	//对象的左上坐标x和右下坐标x，x[0]表示坐上x、x[1]表示右下x
	int y[2];	//同上
}Pos[25];

char KeyStr[][4] = { { "CE" } ,{ "<-" } ,{ "M" } ,{ "/" }
					 ,{ "(" } ,{ ")" } ,{ "^" },{ "^"}
					 ,{ "7" } ,{ "8" } ,{ "9" } ,{ "*" }
					 ,{ "4" } ,{ "5" } ,{ "6" } ,{ "+" }
					 ,{ "1" } ,{ "2" } ,{ "3" } ,{ "-" }
					 ,{ "00" } ,{ "0" } ,{ "." } ,{ "=" },{ "$" } };
//计算器的按键 

int LastStrPosT = 1;	//LastStrPos表示后缀表达式存的数量
char GetStr[MAX * 5];
char TheLastStr[MAX];	//后缀数组 
float LastV = 0;  //计算结果

void Trans(STR *InStr, char LastStr[]);//将算数表达式（中缀表达式）表达成后缀表达式 
float Compvalue(char LastStrTemp[]);//计算后缀表达式的值 


/*
#中缀表达式（中缀记法）
中缀表达式是一种通用的算术或逻辑公式表示方法，操作符以中缀形式处于操作数的中间。中缀表达式是人们常用的算术表示方法。
虽然人的大脑很容易理解与分析中缀表达式，但对计算机来说中缀表达式却是很复杂的，因此计算表达式的值时，通常需要先将中缀表达式转换为前缀或后缀表达式，然后再进行求值。对计算机来说，计算前缀或后缀表达式的值非常简单。

#前缀表达式（前缀记法、波兰式）
前缀表达式的运算符位于操作数之前
前缀表达式的计算机求值：
从右至左扫描表达式，遇到数字时，将数字压入堆栈，遇到运算符时，弹出栈顶的两个数，用运算符对它们做相应的计算（栈顶元素 op 次顶元素），并将结果入栈；重复上述过程直到表达式最左端，最后运算得出的值即为表达式的结果。
例如前缀表达式“- × + 3 4 5 6”：
(1) 从右至左扫描，将6、5、4、3压入堆栈；
(2) 遇到+运算符，因此弹出3和4（3为栈顶元素，4为次顶元素，注意与后缀表达式做比较），计算出3+4的值，得7，再将7入栈；
(3) 接下来是×运算符，因此弹出7和5，计算出7×5=35，将35入栈；
(4) 最后是-运算符，计算出35-6的值，即29，由此得出最终结果。
可以看出，用计算机计算前缀表达式的值是很容易的。

#后缀表达式（后缀记法、逆波兰式）
后缀表达式与前缀表达式类似，只是运算符位于操作数之后。
后缀表达式的计算机求值：
与前缀表达式类似，只是顺序是从左至右：
从左至右扫描表达式，遇到数字时，将数字压入堆栈，遇到运算符时，弹出栈顶的两个数，用运算符对它们做相应的计算（次顶元素 op?栈顶元素），并将结果入栈；重复上述过程直到表达式最右端，最后运算得出的值即为表达式的结果。
例如后缀表达式“3 4 + 5 × 6 -”：
(1) 从左至右扫描，将3和4压入堆栈；
(2) 遇到+运算符，因此弹出4和3（4为栈顶元素，3为次顶元素，注意与前缀表达式做比较），计算出3+4的值，得7，再将7入栈；
(3) 将5入栈；
(4)?接下来是×运算符，因此弹出5和7，计算出7×5=35，将35入栈；
(5) 将6入栈；
(6) 最后是-运算符，计算出35-6的值，即29，由此得出最终结果。

*/
void Trans(STR *InStr , char LastStr[])
{/*将算术表达式转化为后缀表达式*/

	int i = 1;
	char Stack[MAX];/*作为栈使用*/
	char ChStr = InStr->Str[i];	//用于保存数组里的临时元素
	i++;
	int LastStrPos = 1, StackTop = 0;	//StackTop用于表示栈顶，这个栈没有采用课本上的那种，而是直接把栈顶指向元素 

	while (ChStr != '#'){//#代表算术表达式的结束标志

		cout<<"--------------------------------------------------------------------"<<endl;
		cout<<"符号栈为:  ";
		for(int j=1;j<=StackTop;j++)
			cout<<Stack[j];
		cout<<"              后缀表达式为:  ";
		for(int k=1;k<LastStrPos;k++)
			cout<<LastStr[k];

		cout<<"       ";


	switch (ChStr){
		case'(':		/*判定为左括号*/
			StackTop++; 
			Stack[StackTop] = ChStr;

			cout<<"操作： push（符号栈)   ";
			break;

		case')':		//判定为右括号，则取出遇到左括号之前的所有字符 
			while (Stack[StackTop] != '('){
				LastStr[LastStrPos] = Stack[StackTop]; 
				StackTop--; 
				cout<<"操作： pop（符号栈)   ";
				LastStrPos++;
			}
			StackTop--;		//扔掉（
			cout<<"操作： pop（符号栈)   ";
			break;
		case'+':		//判定为加减号，若遇见栈顶比它小或左括号则入栈，否则就将栈顶出栈 
		case'-':
			while (StackTop != 0 && Stack[StackTop] != '('){
				LastStr[LastStrPos] = Stack[StackTop];
				StackTop--;
				cout<<"操作： pop (符号栈）    ";
				LastStrPos++;
			}
			StackTop++;			//保留（
			Stack[StackTop] = ChStr;
			cout<<"操作： push（符号栈)   ";
			break;

		case'*':		/*判定为乘除号*/
		case'/':
			while (Stack[StackTop] == '*' || Stack[StackTop] == '/'){
				LastStr[LastStrPos] = Stack[StackTop];		//如果栈顶是*或者/弹出，放到后缀数组里
				StackTop--;
				cout<<"操作： pop（符号栈)   ";
				LastStrPos++;
			}
			StackTop++;
			Stack[StackTop] = ChStr;
			cout<<"操作： push（符号栈)   ";
			break;

		case' ':break;		//忽略空格

		default:
			while (ChStr >= '0' && ChStr <= '9' || ChStr == '.'){		//判定为数字，把所有的数字都读进去 
				LastStr[LastStrPos] = ChStr; 
				LastStrPos++;
				ChStr = InStr->Str[i];
				i++;
			}
			i--;
			LastStr[LastStrPos] = ' ';		//输出的时候隔开元素
			LastStrPos++;
		}
		ChStr = InStr->Str[i]; i++;

		cout<<endl;
	}
	while (StackTop != 0){

		cout<<"--------------------------------------------------------------------"<<endl;
		cout<<"符号栈为:  ";
		for(int j=1;j<=StackTop;j++)
			cout<<Stack[j];
		cout<<"              后缀表达式为:  ";
		for(int k=1;k<LastStrPos;k++)
			cout<<LastStr[k];
		cout<<"       ";


		LastStr[LastStrPos] = Stack[StackTop];
		LastStrPos++; 
		StackTop--;
		cout<<"操作： pop（符号栈)   ";
		cout<<endl;

	}

	cout<<"--------------------------------------------------------------------"<<endl;
	cout<<"符号栈为:  ";
	for(int j=1;j<=StackTop;j++)
		cout<<Stack[j];
	cout<<"              后缀表达式为:  ";
	for(int k=1;k<LastStrPos;k++)
		cout<<LastStr[k];
	cout<<"       ";
	cout<<endl;

	LastStr[LastStrPos] = ' ';
	LastStrPosT = LastStrPos;
}

float Compvalue(char LastStrTemp[]){	/*计算后缀表达式的值*/

	float Stack[MAX];		/*作为栈使用*/
	char ChStr;			//临时栈元素
	int  StackTop = 0;		/*LastStrPos为LastStr下标，StackTop为Stack下标*/
	int LastStrPos = 1;

	ChStr = LastStrTemp[LastStrPos];
	LastStrPos++;

	while (ChStr != ' '){

		cout<<"--------------------------------------------------------------------"<<endl;
		cout<<"数字栈为:  ";
		for(int j=1;j<=StackTop;j++)
		cout<<Stack[j]<<" ";
		

		switch (ChStr){
		case'+':
			Stack[StackTop - 1] = Stack[StackTop - 1] + Stack[StackTop];
			StackTop--;
			cout<<"          操作：pop（数字栈)   pop（数字栈)   operate('+')   push(数字栈）";
			break;
		case'-':
			Stack[StackTop - 1] = Stack[StackTop - 1] - Stack[StackTop];
			StackTop--;
			cout<<"          操作：pop（数字栈)   pop（数字栈)   operate('-')    push(数字栈）";
			break;
		case'*':
			Stack[StackTop - 1] = Stack[StackTop - 1] * Stack[StackTop];
			StackTop--;
			cout<<"          操作：pop（数字栈)   pop（数字栈)   operate('*')    push(数字栈）";
			break;
		case'/':
			if (Stack[StackTop] != 0)
				Stack[StackTop - 1] = Stack[StackTop - 1] / Stack[StackTop];
			else{
				exit(0);/*异常退出*/
			}
			StackTop--;
			cout<<"          操作：pop（数字栈)   pop（数字栈)   operate('/')    push(数字栈）";
			break;
		default:
			float a=0.1;
			float NumStr = 0;	//把数字字符转化为数字
			bool FlNum = 0;
			while (ChStr >= '0' && ChStr <= '9' || ChStr == '.'){
				if (ChStr == '.') {
					FlNum = 1;
				}
				else if (!FlNum) {
					NumStr = 10 * NumStr + ChStr - '0';/*将数字字符转化为对应的数值*/
				}
				else if (FlNum) {
					NumStr +=a * (ChStr - '0');	/*计算小数*/
					a=a/10;
				}
				
				ChStr = LastStrTemp[LastStrPos];
				LastStrPos++;
			}
			StackTop++;
			cout<<"     操作： push（数字栈)   ";
			Stack[StackTop] = NumStr;


		
		}
		cout<<endl;
		ChStr = LastStrTemp[LastStrPos];
		LastStrPos++;
	}


	cout<<"--------------------------------------------------------------------"<<endl;
	cout<<"数字栈为:  ";
	for(int j=1;j<=StackTop;j++)
	cout<<Stack[j]<<" ";
	cout<<endl;

	return Stack[StackTop];
}


void GiveStr(char GetString[] , char *TheStr) {
	STR InStr;
	char LastStr[MAX];/*存储后缀表达式*/

	InStr.Long = 0;

	for (int i = 0; i<strlen(GetString); i++) {
		if(GetString[i+1]=='+'&&GetString[i+2]=='+')
		{	
			GetString[i]++;
			InStr.Long++;
		    InStr.Str[InStr.Long] = GetString[i];
		    i+=2;
			continue;
		}
		if(GetString[i+1]=='-'&&GetString[i+2]=='-')
		{	
			GetString[i]--;
			InStr.Long++;
		    InStr.Str[InStr.Long] = GetString[i];
		    i+=2;
			continue;
		}
		if(GetString[i+1]=='^')
		{
			if(GetString[i]<='3')
			{
				GetString[i]=(GetString[i]-'0')*(GetString[i]-'0')+'0';
				InStr.Long++;
				InStr.Str[InStr.Long]=GetString[i];
				i+=2;
			}	
			else if(GetString[i]>='3')
			{
				int pp=(GetString[i]-'0')*(GetString[i]-'0');
				GetString[i]=pp/10+'0';
				GetString[i+1]=pp-10*(GetString[i]-'0')+'0';
				InStr.Long++;
				InStr.Str[InStr.Long]=GetString[i];
				InStr.Long++;
				InStr.Str[InStr.Long]=GetString[i+1];
				i+=2;
			}
			continue;
		}
		InStr.Long++;
		InStr.Str[InStr.Long] = GetString[i];
	}

	cout<<"************************************************************************"<<endl;
	cout<<"************************************************************************"<<endl;
	cout<<"***********                 计算器后台系统                  ************"<<endl;
	cout<<"************************************************************************"<<endl;
	cout<<"************************************************************************"<<endl;
	cout<<"算术表达式为：  ";
	for(i=1;i<=InStr.Long;i++)
		cout<<InStr.Str[i];
	
	cout<<endl;


	InStr.Long++;
	InStr.Str[InStr.Long] = '#';


	cout<<"将算术表达式转化为后缀表达式"<<endl;
	Trans(&InStr, LastStr);
	
	cout<<endl;
	cout<<endl;
	
	cout<<"计算后缀表达式"<<endl;
	LastV = Compvalue(LastStr);
	LastV == (int)LastV ? sprintf(TheStr , "%.0f" , LastV) : sprintf(TheStr, "%.4f", LastV);
}

void InitPos() {//初始化按键位置 
	Pos[0].x[0] = 0; Pos[0].y[0] = 0; Pos[0].x[1] = WINSIZEX; Pos[0].y[1] = WINKEYY  * 2;
	
	int k = 1;
	for (int i = 2; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			Pos[k].x[0] = j * WINKEYX;	//左上xy坐标
			Pos[k].y[0] = i * WINKEYY;

			Pos[k].x[1] = (j + 1) * WINKEYX;	//右下xy坐标
			Pos[k].y[1] = (i + 1) * WINKEYY;
			k++;
		}
	}
}

int JudgePos(int x ,int y) {//用来判断鼠标点击的位置
	if (x > 0 && x < WINSIZEX && y > 0 && y < WINKEYY * 2)	//判断文本输出框
		return 0;
	for (int i = 1; i <= 4; i++) {
		if (x >= Pos[i].x[0] && x <= Pos[i].x[1]) {
			for (int j = i; j <= 24; j += 4) {
				if (y >= Pos[j].y[0] && y <= Pos[j].y[1]) {
					return j;
				}
			}
		}
		
	}
}

/*
nHeight 
指定高度（逻辑单位）。 
nWidth 
字符的平均宽度（逻辑单位）。如果为 0，则比例自适应。 
lpszFace 
字体名称。 
*/
void PrintStr() {
	settextstyle(35, 0, _T("Prestige Elite Std"));	//设置输入字体大小，宽度，文字样式
	outtextxy(7,7,GetStr);
}

void GetKey() {//获得鼠标的输入 
	  /*FlushMouseMsgBuffer 清空鼠标消息缓冲区。 
		GetMouseMsg 获取一个鼠标消息。如果当前鼠标消息队列中没有，就一直等待。 
		MouseHit 检测当前是否有鼠标消息。 
		MOUSEMSG 保存鼠标消息的结构体。 */
	MOUSEMSG Msg;
	RECT r = { 0 , WINKEYY * 2 / 3 , WINSIZEX, WINKEYY * 2 };
	IMAGE ClearImgUp , ClearImgDown;

	int ProPos = 0;	//上一个点击的按钮
	int temp = 0;	//当前点击的按钮
	int InCon = 0;	//输入的字符数
	int TempI = 0;
	float LastStrTemp = LastV;
	char StrTemp[MAX];
	char M_Str[20] = { '/0' };

	FlushMouseMsgBuffer();
	getimage(&ClearImgUp, 1, 1, WINSIZEX , WINKEYY * 2 / 3);	//获得输入区域的截图，用于覆盖原先输入的内容
	getimage(&ClearImgDown, 1, WINKEYY * 2 / 3, WINSIZEX, WINKEYY * 2);	//获得输出区域的截图，用于覆盖原先输入的内容

	while (TRUE) {
		
		Msg = GetMouseMsg();
	
		if (Msg.uMsg) {
			temp = JudgePos(Msg.x, Msg.y);

			switch (Msg.uMsg) {
			case WM_LBUTTONDOWN:
				setlinecolor(RGB(230, 230, 230));
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
				//setfillcolor(RGB(150, 150, 150));
				rectangle(Pos[temp].x[0], Pos[temp].y[0], Pos[temp].x[1], Pos[temp].y[1]);

				switch (temp) {
				
				case 1:
					GetStr[0] = '\0';
					putimage(1, 1, &ClearImgUp);
					putimage(1, WINKEYY * 2 / 3, &ClearImgDown);
					InCon = 0;
					PrintStr();
					break;
				case 2:
					if(InCon > 0)	//判断是否有输入的字符
						GetStr[InCon - 1] = '\0';
					putimage(1, 1, &ClearImgUp);
					InCon--;
					PrintStr();
					break;
				case 3:
					strcat(GetStr, M_Str);
					InCon++;
					PrintStr();
					break;
				case 24:
					settextstyle(50, 0, _T("Prestige Elite Std"));	//设置字体大小，宽度，文字样式
					putimage(1, WINKEYY * 2 / 3, &ClearImgDown);
					GiveStr(GetStr, TheLastStr);
					drawtext(_T(TheLastStr), &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
					break;
				//case 7:
				//case 8:
					break;
				default:
						strcat(GetStr, KeyStr[temp - 1]);
						InCon++;
						PrintStr();
				}
			
				Sleep(50);
				break;
			case WM_RBUTTONDOWN:
				setlinecolor(RGB(230, 230, 230));
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
				rectangle(Pos[temp].x[0], Pos[temp].y[0], Pos[temp].x[1], Pos[temp].y[1]);

				switch (temp) {
				case 3:
					strcpy(M_Str, TheLastStr);
					break;
				}
				break;
			}
		}

		setlinecolor(RGB(230, 230, 230));
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
		//setfillcolor(RGB(210,210,210));
		rectangle(Pos[ProPos].x[0], Pos[ProPos].y[0], Pos[ProPos].x[1], Pos[ProPos].y[1]);

		if (temp != 0) {
			setlinecolor(RGB(200, 200, 200));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
			//setfillcolor(RGB(230, 230, 230));
			rectangle(Pos[temp].x[0], Pos[temp].y[0], Pos[temp].x[1], Pos[temp].y[1]);
			ProPos = temp;
		}
			
	}
}

/*

函数或数据 描述 
FILLSTYLE 填充样式对象。 
getbkcolor 获取当前绘图背景色。 
getbkmode 获取图案填充和文字输出时的背景模式。 
getfillcolor 获取当前填充颜色。 
getfillstyle 获取当前填充样式。 
getlinecolor 获取当前画线颜色。 
getlinestyle 获取当前画线样式。 
getpolyfillmode 获取当前多边形填充模式。 
getrop2 获取前景的二元光栅操作模式。 
LINESTYLE 画线样式对象。 
setbkcolor 设置当前绘图背景色。 
setbkmode 设置图案填充和文字输出时的背景模式。 
setfillcolor 设置当前填充颜色。 
setfillstyle 设置当前填充样式。 
setlinecolor 设置当前画线颜色。 
setlinestyle 设置当前画线样式。 
setpolyfillmode 设置当前多边形填充模式。 
setrop2 设置前景的二元光栅操作模式。 



*/
//输出按键文字
void DrawTe() {
	
	LOGFONT f;
	settextcolor(RGB(20, 20, 20));	//设置字体颜色
	settextstyle(30, 0, _T("Prestige Elite Std"));	//设置字体大小，宽度，文字样式
	setbkmode(TRANSPARENT);				//设置输出背景为透明色
	gettextstyle(&f);                     // 获取当前字体设置
										  // f.lfHeight = 48;                      // 设置文字高度为48
	f.lfWeight=700;									  // _tcscpy(f.lfFaceName, _T("黑体"));    // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式


	for (int i = 0, j = 0; strcmp(KeyStr[i], "$"); i++) {	//循环输出字符数组里的文字
		if (i % 4 == 0 && i != 0) j++;

		outtextxy(WINKEYX / 2.5 + (i % 4) * WINKEYX, WINKEYY * (2 + j) + WINKEYY / 3, _T(KeyStr[i]));	//输出按键文字

	}

}

//绘制按键方块
void DrawWindow() {
	setfillcolor(RGB(230, 230, 230));				//填充颜色
	solidrectangle(0, 0, WINSIZEX, WINKEYY * 2);	//绘制背景区域，画填充矩形（无边框）

	setfillcolor(RGB(255, 255, 255));
	solidrectangle(0, WINKEYY * 2, WINSIZEX, WINSIZEY);	//绘制操作区域

	setfillcolor(RGB(240, 240, 240));
	solidrectangle(WINKEYX * 3, WINKEYY * 3, WINKEYX * 4 , WINSIZEY);	//绘制操作区域
	solidrectangle(0, WINKEYY * 2, WINSIZEX, WINKEYY * 3);	//绘制操作区域

	setlinecolor(RGB(230, 230, 230));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);

	for (int i = 2; i <= 8; i++) {
		line(0, i * WINKEYY, WINSIZEX,  i * WINKEYY);		//画横线
		line((i - 2) * WINKEYX, WINKEYY * 2, (i - 2) * WINKEYX, WINSIZEY);		//画竖线
	}
	line(0, WINKEYY * 2 / 3, WINSIZEX , WINKEYY * 2 / 3);
}

int main()
{
	
	initgraph(WINSIZEX, WINSIZEY,SHOWCONSOLE);   // 创建一个500*600的窗口

	
	DrawWindow();
	DrawTe();
	InitPos();
	GetKey();

	closegraph();		   // 关闭图形库   
	return 0;
}
