#include <at89c5131.h>
/*************************************************
 	lcd.h: Header file for 16x2 LCD interfacing  
**************************************************/

//Functions contained in this header file
void msdelay(unsigned int);																	//fn takes integer value as an input and generates corresponding delay in milli seconds
void lcd_init(void);																				//Initialize LCD
void lcd_cmd(unsigned int i);																//Sends commands to lcd
void lcd_char(unsigned char ch);														//display character on a lcd corresponding to input ascii
void lcd_write_string(unsigned char *s);										//takes pointer of a string which ends with null and display on a lcd 


//Signals to LCD
sbit RS=P0^0;	//Register select
sbit RW=P0^1;	//Read from or write to register
sbit EN=P0^2;	//Enable pin of lcd


//Function definitions
/************************************************
   lcd_init():
	Initializes LCD port and 
	LCD display parameters
************************************************/
void lcd_init(void)
{
	P2=0x00;
	EN=0;
	RS=0;
	RW=0;
	
	lcd_cmd(0x38);	// Function set: 2 Line, 8-bit, 5x7 dots
	msdelay(4);
	lcd_cmd(0x06);	// Entry mode, auto increment with no shift
	msdelay(4);
	lcd_cmd(0x0C);	// Display on, Curson off
	msdelay(4);
	lcd_cmd(0x01);	// LCD clear
	msdelay(4);
	lcd_cmd(0x80);	//Move cursor to Row 1 column 0
}

/**********************************************************
   msdelay(<time_val>): 
	Delay function for delay value <time_val>ms
***********************************************************/	
void msdelay(unsigned int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<382;j++);
	}
}

/**********************************************************
    lcd_cmd(<char command>):
	Sends 8 bit command
	LCD display parameters
***********************************************************/	
void lcd_cmd(unsigned int i)
{
	RS=0;
	RW=0;
	EN=1;
	P2=i;
	msdelay(10);
	EN=0;
}


/**********************************************************
   lcd_write_char(<char data>):
	Sends 8 bit character(ASCII)
	to be printed on LCD
***********************************************************/	
void lcd_write_char(unsigned char ch)
{
	RS=1;
	RW=0;
	EN=1;
	P2=ch;
	msdelay(10);
	EN=0;
}


/***********************************************************
  lcd_write_string(<string pointer>):
	Prints string on LCD. Requires string pointer 
	as input argument.
***********************************************************/	
void lcd_write_string(unsigned char *s)
{
	while(*s!='\0')
	{
		lcd_write_char(*s++);
	}
}

int val = 0;
sbit T0 = P3^4;
sbit LED2 = P3^7;
int sec = 0;
int sec0 = 0;
int sec1 = 0;
int min0 = 0;
int min1 = 0;
int min = 0;
void timer1_isr () interrupt 3
{
   LED2 = ~LED2;
   //Reload values for TH1 and TL1. Start timer 1.
   TH1 = 0xBE;
	TL1 = 0xE5;
	TR1 = 1;
}

void timer0_isr() interrupt 1
{

TH0 = 0xFF;
TL0 = 0xC4;
TR0 = 1;
val = val + 1;
sec = val % 60;
min = val / 60;
sec0 = sec % 10;
sec1 = sec / 10;
min0 = min % 10;
min1 = min / 10;
lcd_cmd(0x80);
lcd_cmd(0x01);
lcd_write_char(min1+48);
lcd_cmd(0x06);
lcd_write_char(min0+48);
lcd_cmd(0x06);
lcd_write_char(sec1+48);
lcd_cmd(0x06);
lcd_write_char(sec0+48);
lcd_cmd(0x06);
}


void main()
{
	lcd_init();
	msdelay(4);
	lcd_cmd(0x80);
	
	
ACC = &val;
T0 = 1;
TMOD = 0x15;
TH0 = 0xFF;
TL0 = 0xC4;
ET0 = 1;
EA = 1;
TR1 = 1;
ET1= 1;
TH1 = 0xBE;
TL1 = 0xE5;
//P3^4 == P3^7;

while(1)
{	
if (P1^0 == 1)
{EA = 1;}
else 
{EA = 0;}
}

}

