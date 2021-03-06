#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
// Passed running in VS2010
int  snake_node=1;
int  snake_length[50][2]={31,12};
int  snake_head[2]={31,12};
int  food[2];
char snake_direction='s';
int  delay=100; 
int  food_yes=0;
int  snake_life=0;

void gotoxy(int x, int y)
{
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
} 

void hidden()
{
    	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;
	SetConsoleCursorInfo(hOut,&cci);
}
void init()
{
	int i;
	snake_node=1;
	snake_length[0][0]=31;
	snake_length[0][1]=12;
	snake_head[0]=31;
	snake_head[1]=12;
	snake_direction='s';
	delay=100;
	food_yes=0;
	snake_life=0;
	for(i=1;i<50;i++)
	{
		snake_length[i][0]=0;
		snake_length[i][1]=0;
	}
	
}



void update_score()
{
	gotoxy(0,0);
			printf("Score:%d\b\b", snake_node);
			gotoxy(0,1);
			printf("%c%c%c%c%c",30,30,30,30,30);  
	
}

void create_food()
{
	time_t t;
	srand ( (unsigned int)time(NULL) );
	while(1)
	{
		food[0]=rand()%62+1;
		food[1]=rand()%22+1;
		if(food[0]!=snake_head[0]&&food[1]!=snake_head[1])break;
	}
	gotoxy(food[0],food[1]);
	printf("%c", 3);
}

void direction()
{
	char keyhit=0,i;
	while(_kbhit()!=0)
		keyhit=_getch();
	if( ((keyhit=='a') || (keyhit=='d') || (keyhit=='w') || (keyhit=='s')) && (abs(snake_direction/16-keyhit/16)==1) )
		snake_direction=keyhit;
	else if(keyhit==27)exit(0);
}
void state(){
	if(snake_head[0]<1||snake_head[0]>62||snake_head[1]<1||snake_head[1]>22)snake_life=1;

}

void eat()
{
	switch(snake_direction)
		{
			case 'w':	snake_head[1]--;break;
			case 's':	snake_head[1]++;break;
			case 'a':	snake_head[0]--;break;
			case 'd':	snake_head[0]++;break;
		}
	if((food[0]==snake_head[0]) && (food[1]==snake_head[1]) )
	{
		food_yes=1;
		switch(snake_direction)
		{
			case 'w':	snake_head[1]--;break;
			case 's':	snake_head[1]++;break;
			case 'a':	snake_head[0]--;break;
			case 'd':	snake_head[0]++;break;
		}
	}
		
}

void show_snake()
{
		gotoxy(snake_head[0],snake_head[1]);
		printf("%c", 2);
		gotoxy(snake_length[snake_node-1][0],snake_length[snake_node-1][1]);
		printf(" ");
}

void update_maxtrix()
{
	int i;
	if(food_yes!=1)
	{
		for(i=snake_node-1;i>0;i--)
		{
			snake_length[i][0]=snake_length[i-1][0];
			snake_length[i][1]=snake_length[i-1][1];
		}
	}
	else
	{
		snake_node++;
		if(snake_node>3 && delay>100)delay-=30;
		for(i=snake_node-1;i>1;i--)
		{
			snake_length[i][0]=snake_length[i-2][0];
			snake_length[i][1]=snake_length[i-2][1];
		}
		snake_length[1][0]=food[0];
		snake_length[1][1]=food[1];
		food_yes=0;
		create_food();
		
	}
	snake_length[0][0]=snake_head[0];
	snake_length[0][1]=snake_head[1];

		for(i=3;i<snake_node;i++)
     if(snake_length[i][0]==snake_head[0]&&snake_length[i][1]==snake_head[1]){
     {
               
               snake_life=1;
               break;
     }
        }
}

int main()
{
	system("title JY GAME");
	system("mode con cols=62 lines=23");
	system("color E5");

	LOOP:	
			system("cls");
			init();
			hidden();
			create_food();
	while(1)
	{
		int i;
		update_score();
		Sleep(delay);
		direction();
		eat();
		show_snake();
		update_maxtrix();
		state();
		if(snake_life==1)
		{	
			for(i=1;i<snake_node;i++)
			{
				gotoxy(snake_length[i][0],snake_length[i][1]);
				printf(" ");
			}
			gotoxy(food[0],food[1]);
			printf(" ");
			gotoxy(26,10);
			printf("Game over!\n");
			gotoxy(21,11);
			printf("Press y to continue");
			gotoxy(23,12);
			printf(" Press n to exit ");
			while(1)
			{
				i=_getch();
				if(i=='y')goto LOOP;
				else if(i=='n')break;
			}
			break;
		}
	}	
	return 0;
}
