//#include <stdafx.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include<conio.h>
using namespace std;
typedef struct gameplayer //定义玩家结构体
{
	int name;
	int score;
	float number,b; 
	bool win,fail;
}PLAYER; 

void Game_start(FILE *fp); //游戏的初始化
void Game_rule(); //游戏规则
void Culculate(PLAYER *p,float ave,int num,FILE *fp);//计算比赛得分的函数

int main()
{
	system("color e3");
	int choice;
	FILE *fp;
	printf("\n &&&&&&&&&&&&&&&&&&&&&&    ☆  欢迎来到黄金点游戏  ☆    &&&&&&&&&&&&&&&&&&&&&& \n");
	printf("                               ★★★★★★★★★                                \n");
	while(1)
	{
	fp=fopen("goldgame.txt","w+");
	printf("                       ★  ☆      1.游戏规则      ☆  ★                       ");
	printf("                       ★  ☆      2.开始游戏      ☆  ★                       ");
	printf("                       ★  ☆      3.退出游戏      ☆  ★                       ");
	printf("\n  您的选择是："); 
	scanf("%d",&choice);
	switch(choice)
	{
	case 1: Game_rule(); break;
	case 2: Game_start(fp); break;
	case 3: exit(0); break;
	default: 
	{
		printf(" 您的输入有误，请重新输入\n"); 
	break;
	}
	}
}
return 0;
}

	void Game_rule()
	{
		printf("Rule_1:N个同学（N通常大于10），每人写一个0~100之间的有理数（不包括0或100)\n");
		printf("Rule_2:裁判算出所有数字的平均值，然后乘以0.618（所谓黄金分割常数），得到G值\n") ;
		printf("Rule_3:提交的数字最靠近G（取绝对值）的同学得到N分，离G最远的同学得到－2分,其他同学得0分\n");
	}
	
void Game_start(FILE *fp)
{
	PLAYER *p;
	int i,playernum,gamenum,j;
	int flag=1;
	float sum,ave;
	char choice;
	p=(PLAYER *)malloc(10*sizeof(PLAYER)); //动态分配结构体数组
	printf("请输入参与的玩家数：");
	scanf("%d",&playernum);
	if(playernum>10)
	{
		p=(PLAYER *)realloc(p,playernum*sizeof(PLAYER));//空间不足而需要增加空间
	}
	printf("请输入比赛轮次：");
	scanf("%d",&gamenum);
	printf("\n");
	for(j=0;j<gamenum;j++)
	{
		printf("第%d轮比赛：\n",j+1);
		for(i=0,sum=0	;i<playernum;i++)//sum设为总数和
		{
			if(flag==1)
			{
				p[i].name=i+1;
				p[i].score=0; 
				p[i].win=0;
				p[i].fail=0;
			} //初始化初值为0
			printf(" 玩家%d: ",p[i].name);
			scanf("%f",&p[i].number);
			sum+=p[i].number;
		}
		ave=sum/playernum; //计算平均值
		ave=(float)(ave*0.618); //计算黄金点的值
		printf(" 黄金点G的值为：%f\n",ave);
		Culculate(p,ave,playernum,fp); 
		flag=0;
	}

}

void Culculate(PLAYER *p,float ave,int num,FILE *fp)
{
	int i;
	char ch;
	float max=(float)fabs(p[0].number-ave);
	float min=(float)fabs(p[0].number-ave);

	for(i=0;i<num;i++) //统计出本轮最大值，最小值
	{
		p[i].b=(float)fabs(p[i].number-ave); 
		if(max<p[i].b)
		max=p[i].b; 
		if(min>p[i].b)
		min=p[i].b; 
	}

	for(i=0;i<num;i++) //挨个玩家赋予成绩
	{
		if(p[i].b==max) 
		{
			p[i].score-=2; 
		}
		if(p[i].b==min) 
		{
			p[i].score+=num;
		}
	}
		printf("累计比赛的得分：\n");
		for(i=0;i<num;i++) //挨个玩家输出成绩
		printf(" 玩家%d: %d\n",p[i].name,p[i].score);
		
		while(1)
		{
			printf("是否继续 Y or N : ");
			scanf("%c",&ch);
			if(ch=='y'||ch=='Y')
			{
				break;
			}
			else if(ch=='n'||ch=='N') 
			{
				exit(0);
			}
		}		
}
