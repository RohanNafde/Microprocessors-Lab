#include <at89c5131.h>
#include "lcd.h"
#include "functions.h"

int i, x, a[5], ind;

void display(char str1[], char str2[]);

void display(char str1[], char str2[])
{
	lcd_cmd(0x01);                          //clear previous display
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(str1);
	lcd_cmd(0xC0);													//Move cursor to 2nd line of LCD
	msdelay(4);
	lcd_write_string(str2);
}

void main()
{
	//initialise LED
	lcd_init();
	
	//program start
	display("START PROGRAM", "");
	msdelay(5000);
	
	//first input
	P1 = 15;
	display("FIRST INPUT", "");
	msdelay(5000);
	a[0] = P1;
	
	//rest inputs
	for(i=1; i<5; i++)
	{
		//display previous input
		P1 = a[i-1] * 16;
		display("NEXT INPUT", "");
		msdelay(5000);
		//clear LEDs
		P1 = 15;
		msdelay(1000);
		a[i] = P1;
	}
	P1 = a[4] * 16;
	
	//sorting message and sort
	display("SORTING", "");
	msdelay(5000);
	
	//clear LEDs and sort
	P1 = 0;
	msdelay(1000);
	display("SORTING", "COMPLETED");
	bubbleSort(a);
	
	//display sorted numbers
	for(i=0; i<5; i++)
	{
		P1 = a[i] * 16;
		msdelay(5000);
		P1 = 0;
		msdelay(1000);
	}
	
	//input number to be searched, turning all LEDs on
	P1 = 255;
	display("NUMBER TO BE", "SEARCHED");
	msdelay(5000);
	x = P1-240;
	display("", "");
	P1 = 0;
	msdelay(1000);
	
	//search number
	ind = search(a, x);
	//index not found
	if(ind == -1)
		display("NUMBER", "NOT FOUND");
	//index found
	else
	{
		display("THE INDEX IS", "");
		P1 = (ind + 1) * 16;
	}
	while(1);
}