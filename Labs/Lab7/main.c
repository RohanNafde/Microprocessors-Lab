#include <at89c5131.h>
#include "lcd.h"

char password[] = "15A8*D6#";
char char_data[4][4]= {"123A","456B","789C","*0#D"};
char input[8];
int i, column ,row ,access;

void display(char str1[], char str2[]);
char keypress();

void display(char str1[], char str2[])
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	msdelay(4);
	lcd_write_string(str1);
	lcd_cmd(0xC0);
	msdelay(4);
	lcd_write_string(str2);
}

int row_value()
{
	P3 = 0xEF;
	if((P3 & 15) != 15)
		return 0;
	P3 = P3 - 0x10;
	if((P3 & 15) != 15)
		return 1;
	P3 = P3 - 0x20;
	if((P3 & 15) != 15)
		return 2;
	P3 = P3 - 0x40;
	if((P3 & 15) != 15)
		return 3;
}

int column_value()
{
	if(P3 == 7)
		return 0;
	else if(P3 == 11)
		return 1;
	else if(P3 == 13)
		return 2;
	else if(P3 == 14)
		return 3;
}

char keypress()
{
	//take input with 20ms debounce
	start:
	P3 = P3 & 15; //to check last nibble
	while(P3 != 15){} //previous input still there
	while(P3 == 15){} //no input given
	msdelay(20); //debounce delay
	if(P3 == 15)
		goto start; //go to start if no input after debounce
			
	//determine column
	column = column_value();
	
	//determine row
	row = row_value();
	
	return char_data[row][column];
}

void main()
{
	again:
	//initialise
	lcd_init();
	access = 1;
	display("Enter Password:", "");
	//bring cursor to second line
	lcd_cmd(0xC0);
	
	//loop to check password and display entered password on LCD
	for(i=0; i<8; i++)
	{
		//take input
		P3 = 0x0F;
		input[i] = keypress();
		
		//check with that character of password
		if(input[i] != password[i])
			access = 0;
		
		//update character on LCD 2nd line
		lcd_write_char(input[i]);
		lcd_cmd(0x06);
		msdelay(4);
	}
	msdelay(1000);
	
	//display if access granted or not
	if(access == 1)
		display("Correct Password", "Access Granted");
	else
		display("Wrong Password", "Access Denied");
	msdelay(3000);
	goto again;
}