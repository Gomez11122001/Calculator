#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#define LT 218
#define LB 192
#define RT 191
#define RB 217
#define BT 193
#define TT 194
#define LST 195
#define TST 180
#define HL 196
#define VER 179
#define SPACE 32
#define CROSS 197
#define BS 8
#define DIM 7
#define WIDTH 5
#define TOTROWS 25
#define TOTCOLS 80
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define HOME 71
#define END 79
#define PGDN 81
 
int DayOfWeek( int y, int m, int d ) /* returns Day of Week:
0 = Sunday, 1= Monday...
*/
{
static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
y -= m < 3;
return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

void gotoxy(int x,int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void drawbox(void){
	int row;
	int col;
	int ctr1;
	int ctr2;
	int ctr3;
	
	col=(TOTCOLS-((DIM+1)+(DIM*WIDTH)))/2;
	
	row=(TOTROWS-((DIM+1)+(DIM)))/2;
	
	gotoxy(col,row);
	printf("%c",LT);
	
	for(ctr2=0;ctr2<DIM;ctr2++){
		for(ctr1=0;ctr1<WIDTH;ctr1++)
		  printf("%c",HL);
	 printf("%c",TT);	  
	}
	printf("%c%c",BS,RT);
	for(ctr3=0;ctr3<DIM;ctr3++){
		row+=1;
		gotoxy( col,row);
		for(ctr2=0;ctr2<=DIM;ctr2++){
			printf("%c",VER);
	    for(ctr1=0;ctr1<WIDTH;ctr1++)
		    printf("%c",SPACE);
		}
	    row+=1;
	    gotoxy(col,row);
	    printf("%c",LST);
	    for(ctr2=0;ctr2<DIM;ctr2++){
	    	for(ctr1=0;ctr1<WIDTH;ctr1++)
	    	  printf("%c",HL);
	     printf("%c",CROSS);
		}
		printf("%c%c",BS,TST);
		
	}
	gotoxy(col,row);
	printf("%c",LB);
	for(ctr2=0;ctr2<DIM;ctr2++){
		for(ctr1=0;ctr1<WIDTH;ctr1++)
		  printf("%c",HL);
		printf("%c",BT);
		}
		printf("%c%c",BS,RB);
	}
void printHeading(){
	int col;
	int row;
	char dayName[7][4]={"SUN","MON","TUS","WED","THU","FRI","SAT"};
	col=(TOTCOLS-((DIM+1)+(DIM*WIDTH)))/2;
	row=(TOTROWS-((DIM+1)+(DIM)))/2;
	row+=1;
	col+=2;
	
	for(int ctr=0;ctr<DIM;ctr++){
		gotoxy(col+(ctr*(WIDTH+1)),row);
		printf("%s",dayName[ctr]);
	}
}

void calendarPrinter(int month,int year){
	int row;
	int col;
	int dayNum;
	int ctr;
	int monthLast_day;
	char month_name[][10]={"","JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};
	int day_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	 day_in_month [ 2 ] += ( ( (year%4 ==0) && (year % 100 != 0) ) || (year%400==0) ? 1 : 0);
	monthLast_day=day_in_month[month]; 
	
	col = ( TOTCOLS - ( (DIM + 1) + ( DIM * WIDTH )) ) / 2;
    row = ( TOTROWS - ( ( DIM + 1) + (DIM)) ) / 2;
    
    row+=3;
    col+=3;
    gotoxy(32,3);
    printf("%10s , %d",month_name[month],year);
    for(ctr=DayOfWeek(year,month,1),dayNum=1;dayNum <= monthLast_day;dayNum+=1){
    	
         gotoxy( col + (ctr * (WIDTH+1)), row);
         printf("%02d",dayNum );
         ctr+=1;
         if(ctr==DIM){
         	ctr=0;
         	row+=2;
		 }
	}
	

}

void cleaner()
{
    int row;
    int col;

    col = ( TOTCOLS - ( (DIM + 1) + ( DIM * WIDTH )) ) / 2;
    row = ( TOTROWS - ( ( DIM + 1) + (DIM)) ) / 2;
    row+=3;
    col+=3;
    int weekCtr;
    int dayCtr;
    for( weekCtr = 0; weekCtr < DIM; weekCtr += 1, row+=2)
    {
        for( dayCtr = 0; dayCtr < DIM; dayCtr +=1)
        {
            gotoxy(col + (dayCtr * (WIDTH +1)), row);
            printf("  ");

        }
    }
}

int main(){
	  printf("!!!! UP ARROW  is used to change year !!!!\n\n");
	  printf("!!!! SIDE ARROW is used to change month !!!!\n\n");
	 
	
	int key;
	int month;
	int year;
	month=5;
	year=2023;
	drawbox();
	printHeading();
	
     
	 
	do{
	
		 calendarPrinter(month,year);
		  key=getchar();
		  switch(key){
		  	case LEFT:month-=1;break;
		  	case RIGHT: month+=1;break;
		  	case UP: year-=1;break;
		  	case DOWN:year+=1;break;
		  	case HOME:month=1;break;
		  	case PGDN:month=12;
		  	
		  }
		
		  if(month==0){
		  	month=12;
		  	year-1;
		  }
		  else if(month>12){
		  	month=1;
		  	year+=1;
		  }
		  	
		  cleaner();
	}while(key!=END);
	
   return EXIT_SUCCESS;
} 