#include <at89c5131.h>
#include "lcd.h"

unsigned long int i, ans1, t, time, a1, a0, b1, b0, c0, c1, c2, c3, c, a = 29851, b = 11237;
char msg1[16], msg2[16];

void main()
{	
	//initialise LED
	lcd_init();
	
	msg1[0] = 'P';
	msg1[1] = 'r';
	msg1[2] = 'o';
	msg1[3] = 'd';
	msg1[4] = '1';
	msg1[5] = '=';

	msg2[0] = 't';
	msg2[1] = 'i';
	msg2[2] = 'm';
	msg2[3] = 'e';
	msg2[4] = '1';
	msg2[5] = '=';
	
	TMOD = 0x10;
	TL1 = 0x00; //Starting Count value
	TH1 = 0x00;
	TR1 = 1; //Start bit indicates the counting starts
	
	a1 = a/10;
	a0 = a%10;
	b1 = b/10;
	b0 = b%10;
	c0 = a0*b0;
	c1 = a0*b1;
	c2 = a1*b0;
	c3 = a1*b1;
	c = c0 + (c1 + c2)*10 + c3*100;
	
	TR1 = 0; //Stops the timer
	TF1 = 0;
	
	t = TH1*256 + TL1;
	time = t/2;
	
	int_to_string1(c, msg1);
	int_to_string2(time, msg2);
	msg2[11] = 'u';
	msg2[12] = 's';
	
	R0 = time%256;
	R1 = time/256;
	
	display(msg1, msg2);
	
	while(1);
}