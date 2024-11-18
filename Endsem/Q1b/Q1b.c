#include <at89c5131.h>
#include "lcd.h"

long int i, ans1, t, time, a1, a0, b1, b0, c0, c1, c2, c;
char msg1[16], msg2[16];

void main()
{
	lcd_init();
	
	msg1[0] = 'P';
	msg1[1] = 'r';
	msg1[2] = 'o';
	msg1[3] = 'd';
	msg1[4] = '2';
	msg1[5] = '=';

	msg2[0] = 't';
	msg2[1] = 'i';
	msg2[2] = 'm';
	msg2[3] = 'e';
	msg2[4] = '2';
	msg2[5] = '=';
	
	TMOD = 0x11;
	TL0 = 0x00; //Starting Count value
	TH0 = 0x00;
	TR0 = 1; //Start bit indicates the counting starts
	
	a1 = 29851/10;
	a0 = 29851%10;
	b1 = 11237/10;
	b0 = 11237%10;
	c0 = a0*b0;
	c1 = (a0+a1)*(b0+b1);
	c2 = a1*b1;
	c = c0 + (c1 - c0 - c2)*10 + c2*100;
	
	TR0 = 0; //Stops the timer
	
	t = TH0*256 + TL0;
	time = t/2;
	
	int_to_string1(c, msg1);
	int_to_string2(time, msg2);
	msg2[11] = 'u';
	msg2[12] = 's';
	
	display(msg1, msg2);
	
	while(1);
}