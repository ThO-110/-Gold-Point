//#include <stdafx.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include<conio.h>
using namespace std;
typedef struct gameplayer //������ҽṹ��
{
	int name;
	int score;
	float number,b; 
	bool win,fail;
}PLAYER; 

void Game_start(FILE *fp); //��Ϸ�ĳ�ʼ��
void Game_rule(); //��Ϸ����
void Culculate(PLAYER *p,float ave,int num,FILE *fp);//��������÷ֵĺ���

int main()
{
	system("color e3");
	int choice;
	FILE *fp;
	printf("\n &&&&&&&&&&&&&&&&&&&&&&    ��  ��ӭ�����ƽ����Ϸ  ��    &&&&&&&&&&&&&&&&&&&&&& \n");
	printf("                               ����������                                \n");
	while(1)
	{
	fp=fopen("goldgame.txt","w+");
	printf("                       ��  ��      1.��Ϸ����      ��  ��                       ");
	printf("                       ��  ��      2.��ʼ��Ϸ      ��  ��                       ");
	printf("                       ��  ��      3.�˳���Ϸ      ��  ��                       ");
	printf("\n  ����ѡ���ǣ�"); 
	scanf("%d",&choice);
	switch(choice)
	{
	case 1: Game_rule(); break;
	case 2: Game_start(fp); break;
	case 3: exit(0); break;
	default: 
	{
		printf(" ����������������������\n"); 
	break;
	}
	}
}
return 0;
}

	void Game_rule()
	{
		printf("Rule_1:N��ͬѧ��Nͨ������10����ÿ��дһ��0~100֮�����������������0��100)\n");
		printf("Rule_2:��������������ֵ�ƽ��ֵ��Ȼ�����0.618����ν�ƽ�ָ�������õ�Gֵ\n") ;
		printf("Rule_3:�ύ���������G��ȡ����ֵ����ͬѧ�õ�N�֣���G��Զ��ͬѧ�õ���2��,����ͬѧ��0��\n");
	}
	
void Game_start(FILE *fp)
{
	PLAYER *p;
	int i,playernum,gamenum,j;
	int flag=1;
	float sum,ave;
	char choice;
	p=(PLAYER *)malloc(10*sizeof(PLAYER)); //��̬����ṹ������
	printf("�����������������");
	scanf("%d",&playernum);
	if(playernum>10)
	{
		p=(PLAYER *)realloc(p,playernum*sizeof(PLAYER));//�ռ䲻�����Ҫ���ӿռ�
	}
	printf("����������ִΣ�");
	scanf("%d",&gamenum);
	printf("\n");
	for(j=0;j<gamenum;j++)
	{
		printf("��%d�ֱ�����\n",j+1);
		for(i=0,sum=0	;i<playernum;i++)//sum��Ϊ������
		{
			if(flag==1)
			{
				p[i].name=i+1;
				p[i].score=0; 
				p[i].win=0;
				p[i].fail=0;
			} //��ʼ����ֵΪ0
			printf(" ���%d: ",p[i].name);
			scanf("%f",&p[i].number);
			sum+=p[i].number;
		}
		ave=sum/playernum; //����ƽ��ֵ
		ave=(float)(ave*0.618); //����ƽ���ֵ
		printf(" �ƽ��G��ֵΪ��%f\n",ave);
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

	for(i=0;i<num;i++) //ͳ�Ƴ��������ֵ����Сֵ
	{
		p[i].b=(float)fabs(p[i].number-ave); 
		if(max<p[i].b)
		max=p[i].b; 
		if(min>p[i].b)
		min=p[i].b; 
	}

	for(i=0;i<num;i++) //������Ҹ���ɼ�
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
		printf("�ۼƱ����ĵ÷֣�\n");
		for(i=0;i<num;i++) //�����������ɼ�
		printf(" ���%d: %d\n",p[i].name,p[i].score);
		
		while(1)
		{
			printf("�Ƿ���� Y or N : ");
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
