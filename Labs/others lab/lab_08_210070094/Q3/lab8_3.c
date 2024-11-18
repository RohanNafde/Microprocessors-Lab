#include <at89c5131.h>
#include "lcd.h"

sbit LED = P3 ^ 6;
sbit LED1 = P3 ^ 5;
int sec, min = 0;

void digit_display(int a)
{
	lcd_write_char((a/10)+48);
	msdelay(4);
	lcd_write_char((a%10)+48);
}
void display_time(int a, int b)
{
	
	lcd_cmd(0xC0);
	msdelay(4);
	digit_display(a);
	msdelay(4);
	lcd_write_char(58);
	msdelay(4);
	digit_display(b);
}

void timer0_isr() interrupt 1
{
	++sec;
	LED1 = ~LED1;
	if(sec == 60)
	{
		sec = 0;
		++min;
	}
	display_time(min, sec);
	//Reload values for TH0 and TL0. Start timer 0.
	TH0 =  0xFF; //Values for Timer 0 TH0
	TL0 =  0xC4; //Values for Timer 0 TL0
	TF0 = 0;     
	TR0 = 1;
}

void timer1_isr() interrupt 3
{
	LED = ~LED;
	//Reload values for TH1 and TL1. Start timer 1.
	TH1 =  0xBE; //Values for Timer 1 TH1
	TL1 =  0xE5; //Values for Timer 1 TL1
	TF1 = 0;
	TR1 = 1;
}

void clock_60(void)
{
	TMOD = 0x10;
	TH1 = 0xBE;
	TL1 = 0xE5;
	ET1 = 1;
	EA  = 1;
	TR1 = 1;
	
}


void main(void)
{
	
	clock_60();
	P1_0 = 1;
	
	P3_4 = 1;
	lcd_init();
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string("Stopwatch :");
	
	
	
	
	TMOD = TMOD | 0x05;
	TH0 = 0xFF;
	TL0 = 0xC4;
	ET0 = 1;
	EA  = 1;
	TR0 = 1;
	
	while(1){
	if(P1_0 == 0)
	{
		EA = 0;
		TR0 = 0;
		TR1 = 0;
	}
	else
	{
		EA = 1;
		TR0 = 1;
		TR1 = 1;
	}
	};
}