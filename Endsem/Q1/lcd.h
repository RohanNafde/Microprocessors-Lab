/*************************************************
 	lcd.h: Header file for 16x2 LCD interfacing  
**************************************************/

//Functions contained in this header file
void msdelay(unsigned int);																	//fn takes integer value as an input and generates corresponding delay in milli seconds
void lcd_init(void);																				//Initialize LCD
void lcd_cmd(unsigned int i);																//Sends commands to lcd
void lcd_char(unsigned char ch);														//display character on a lcd corresponding to input ascii
void lcd_write_string(unsigned char *s);										//takes pointer of a string which ends with null and display on a lcd 
void int_to_string(unsigned int,unsigned char *temp_string);//convert unsigned int to string of corresponding decimal value 
void display(char str1[], char str2[]);

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
  int_to_string(<integer_value>,<string_ptr>): 
	Converts integer to string of length 5
***********************************************************/	
void int_to_string1(unsigned long int val,unsigned char *temp_str_data)
{	
   // char str_data[4]=0;
	
	  temp_str_data[6]=48+(val/100000000);
	  temp_str_data[7]=48+((val%100000000)/10000000);
	  temp_str_data[8]=48+((val%10000000)/1000000);
	  temp_str_data[9]=48+((val%1000000)/100000);
	  temp_str_data[10]=48+((val%100000)/10000);
	  temp_str_data[11]=48+((val%10000)/1000);
	  temp_str_data[12]=48+((val%1000)/100);
	  temp_str_data[13]=48+((val%100)/10);
	  temp_str_data[14]=48+(val%10);
   // return str_data;
}

void int_to_string2(unsigned long int val,unsigned char *temp_str_data)
{	
   // char str_data[4]=0;
	
	  temp_str_data[6]=48+(val/10000);
	  temp_str_data[7]=48+((val%10000)/1000);
	  temp_str_data[8]=48+((val%1000)/100);
	  temp_str_data[9]=48+((val%100)/10);
	  temp_str_data[10]=48+(val%10);
   // return str_data;
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