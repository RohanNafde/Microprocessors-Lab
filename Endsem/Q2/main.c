#include <at89c5131.h>
#include "mcp3008.h"  //Driver for interfacing ADC ic MCP3008
#include "serial.c"		

char state, temp;
int quant, index;
char board_name[4][10] = {"8051", "TIVA-C", "Atmega328p", "STM32"};
char disp1[7] = "8051-x ";
char disp2[7] = "TIVA-x ";
char disp3[8] = "AT328-x ";
char disp4[8] = "STM32-x ";
int quantity[4] = {8, 6, 4, 4};
int quantity_max[4] = {8, 6, 4, 4};

void initialize()
{
	transmit_string("Micro-controllers available: ");
	
	disp1[5] = quantity[0] + 48;
	disp2[5] = quantity[1] + 48;
	disp3[6] = quantity[2] + 48;
	disp4[6] = quantity[3] + 48;
	
	transmit_string(disp1);
	transmit_string(disp2);
	transmit_string(disp3);
	transmit_string(disp4);
	
	transmit_string("\r\n");
	transmit_string("Press I for Issue and R for Return");
	transmit_string("\r\n");
	state = receive_char();
}

void Issue()
{
	transmit_string("Enter micro-controller to be borrowed:");
	transmit_string("\r\n");
	temp = receive_char();
	index = temp - 49;
	
	transmit_string("Enter Quantity:");
	transmit_string("\r\n");
	temp = receive_char();
	quant = temp - 48;
	
	if(quantity[index] >= quant)
	{
		transmit_string("Requested micro-controller allocated!");
	transmit_string("\r\n");
		quantity[index] = quantity[index] - quant;
	}
	else
	{
		transmit_string("Requested micro-controller not available...");
		transmit_string("\r\n");
	}
}

void Return()
{
	transmit_string("Enter micro-controller to be returned:");
	transmit_string("\r\n");
	temp = receive_char();
	index = temp - 49;
	
	if(quantity[index] == quantity_max[index])
		transmit_string("You can't return what you don't have...");
	
	else
	{
		transmit_string("Enter Quantity:");
		transmit_string("\r\n");
		temp = receive_char();
		quant = temp - 48;
		
		if(quantity_max[index] >= quantity[index] + quant)
		{
			transmit_string("Returned micro-controller received!");
			transmit_string("\r\n");
			quantity[index] = quantity[index] + quant;
		}
		else
		{
			transmit_string("Returned micro-controller out of bounds...");
			transmit_string("\r\n");
		}
	}
}

void main(void)
{
	spi_init();																					
	uart_init();
	while(1)
	{
		initialize();
		if (state == 'I' || state == 'i')
			Issue();
		if (state == 'R' || state == 'r')
			Return();
  }
}

