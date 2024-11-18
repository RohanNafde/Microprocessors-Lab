#include <at89c5131.h>
#include "lcd.h"

code unsigned char display_msg1[]="START PROGRAM   ";						
code unsigned char display_msg2[]="FIRST INPUT     ";			
code unsigned char display_msg3[]="NEXT INPUT      ";
code unsigned char display_msg4[]="SORTING...      ";
code unsigned char display_msg5[]="SORTING         ";
code unsigned char display_msg6[]="COMPLETED       ";
code unsigned char display_msg7[]="NUMBER TO BE    ";
code unsigned char display_msg8[]="SEARCHED        ";
code unsigned char display_msg9[]="THE INDEX IS    ";
code unsigned char display_msg10[]="NUMBER         ";
code unsigned char display_msg11[]="NOT FOUND      ";

int a[5] = {0,0,0,0,0};
int i, j, temp;
void swap()
{
	P1_7 = P3_3;
	P1_6 = P3_2;
	P1_5 = P3_1;
	P1_4 = P3_0;
}

void sort()
{
	for(i=0; i<4; i++)
	{
		for(j=0; j<4-i; j++)
		{
			if(a[j]>a[j+1])
			{
				temp = a[j+1];
				a[j+1] = a[j];
				a[j] = temp;
			}
		}
	}
}
void main()
{
	lcd_init();
	ACC = &a;
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);
	msdelay(5000);
	lcd_cmd(0x01);	
	msdelay(4);
	
	lcd_cmd(0x80);
	lcd_write_string(display_msg2);
	msdelay(5000);
	a[0] = P1;
	lcd_cmd(0x01);
	
	lcd_cmd(0x80);
	lcd_write_string(display_msg3);
	msdelay(5000);
	a[1] = P1;
	P3 = a[0];
	swap();
	lcd_cmd(0x01);
	
	lcd_cmd(0x80);
	lcd_write_string(display_msg3);
	msdelay(5000);
	a[2] = P1;
	P3 = a[1];
	swap();
	lcd_cmd(0x01);
	
	lcd_cmd(0x80);
	lcd_write_string(display_msg3);
	msdelay(5000);
	a[3] = P1;
	P3 = a[2];
	swap();
	lcd_cmd(0x01);
	
	lcd_cmd(0x80);
	lcd_write_string(display_msg3);
	msdelay(5000);
	a[4] = P1;
	P3 = a[3];
	swap();
	lcd_cmd(0x01);
	
	P3 = a[4];	
	msdelay(5000);
	lcd_cmd(0x80);
	lcd_write_string(display_msg4);
	
	sort();
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_write_string(display_msg5);
	lcd_cmd(0xC0);
	lcd_write_string(display_msg6);
	
	for(i=0; i<5; i++)
	{
		P3 = a[i];
		swap();
		msdelay(5000);
		P1 = 0x00;
		msdelay(1000);
	}
	
	P1 = 0xFF;
	lcd_cmd(0x01);
	msdelay(4);
	lcd_cmd(0x80);
	lcd_write_string(display_msg7);
	msdelay(4);
	lcd_cmd(0xC0);
	lcd_write_string(display_msg8);
	msdelay(5000);
	for(i = 0; i < 5; i++)
	{
		if(a[i]==P1)
		{
			i = i + 1;
			P3 = i;
			swap();
			lcd_cmd(0x80);
			lcd_write_string(display_msg9);
			while(1);
		}
	}
	P1 = 0xFF;
	lcd_write_string(display_msg10);
	lcd_write_string(display_msg11);

}