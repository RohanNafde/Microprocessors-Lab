#include <at89c5131.h>
#include "lcd.h"

sbit LED1=P3^7;
int count, temp;
char time[5];

void display_time();

void timer1_isr() interrupt 3
{
	LED1 = ~LED1;
	TH1 = 0xBE;
	TL1 = 0xE5;
	TR1 = 1;
}

void timer0_isr() interrupt 1
{
	TH0 = 0xFF;
	TL0 = 0xC4;
	TR0 = 1;
	count = count + 1;
	display_time();
}

void display_time()
{
	temp = count-1;
	time[0] = temp / 600 + 48;
	temp = temp % 600;
	time[1] = temp / 60 + 48;
	temp = temp % 60;
	time[3] = temp / 10 + 48;
	temp = temp % 10;
	time[4] = temp + 48;
	time[2] = ':';
	display(time, "");
}

void main(void)
{
	lcd_init();
	msdelay(4);
	display("00:00", "");
	count = 0;
	
	TMOD = 0x15;
	TH0 = 0xFF;
	TH1 = 0xBE;
	TL0 = 0xFE;
	TL1 = 0xE5;
	ET0 = 1;
	ET1 = 1;
	EA = 1;
	TR0 = 1;
	TR1 = 1;
	
	while(1)
	{
		if(P1_0 == 0)
			EA = 0;
		else
			EA = 1;
	}
}