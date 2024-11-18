#include <at89c5131.h>
#include "lcd.h"			//Driver for interfacing lcd 
#include "mcp3008.h"  //Driver for interfacing ADC ic MCP3008
#include "serial.c"		

char account_num,state;
int amt,amt_d1,amt_d2,ret_again=0;
int balance_1 = 100;
int balance_2 = 100;
int num_5,num_1;
int acc_num;
char acc_num2;
char name[4] = {'0','0','0','0'};
char balance_string[4] = {'0','0','0','0'};
char act_bal[4] = {'0','0','0','0'};
char num5_string_double[2] = {'0','0'};
char num5_string_single[1] = {'0'};
char num1_string_single[1] = {'0'};

void initialize(){
	transmit_string("Press A for Account display and W for withdrawing cash");
	transmit_string("\r\n");
	state = receive_char();
}

void display_info(char* a, int balance){
	int_to_string(balance,balance_string);
	transmit_string("Account Holder: ");
	transmit_string(a);
	transmit_string("\r\n");
	transmit_string("Account Balance: ");
	transmit_string(balance_string);
	transmit_string("\r\n");
}

void transaction(int amt, int acc_num2){
	if(acc_num2 == 1){
		if(amt > balance_1){
			transmit_string("Insuffcient Funds");
			return;
		}
		else{
			num_5 = amt/5;
			num_1 = amt%5;
			balance_1 -= amt;
			transmit_string("Remaining Balance: ");
			int_to_string(balance_1 * 100,act_bal);
			transmit_string(act_bal);
			transmit_string("\r\n");
			transmit_string("500 Notes: ");
			if(num_5 > 9){
				int_to_string(num_5,num5_string_double);
				transmit_string(num5_string_double);
			}
			else{
				int_to_string(num_5,num5_string_single);
				transmit_string(num5_string_single);
			}
			transmit_string(", 100 Notes: ");
			int_to_string(num_1,num1_string_single);
			transmit_string(num1_string_single);
		}
	}
	else if(acc_num == 2){
		if(amt > balance_2){
			transmit_string("Insuffcient Funds");
			ret_again = 1;
			return;
		}
		else{
			num_5 = amt/5;
			num_1 = amt%5;
			balance_2 -= amt;
			transmit_string("Remaining Balance: ");
			int_to_string(balance_2 * 100,act_bal);
			transmit_string(act_bal);
			transmit_string("\r\n");
			transmit_string("500 Notes: ");
			if(num_5 > 9){
				int_to_string(num_5,num5_string_double);
				transmit_string(num5_string_double);
			}
			else{
				int_to_string(num_5,num5_string_single);
				transmit_string(num5_string_single);
			}
			transmit_string(", 100 Notes: ");
			int_to_string(num_1,num1_string_single);
			transmit_string(num1_string_single);
		}
	}
}

void account_info_display(char acc_num){
	if(acc_num == '1'){
		name[0] = "S";
		name[1] = "i";
		name[2] = "t";
		name[3] = "a";
		display_info(name,balance_1);
	}
	else if(acc_num == '2'){
		name[0] = "G";
		name[1] = "i";
		name[2] = "t";
		name[3] = "a";
		display_info(name,balance_2);
	}
	else{
		transmit_string("No such account, please enter valid details");
	}
	initialize();
}

void withdraw_info(){
	transmit_string("Withdraw state, enter account number");
	transmit_string("\r\n");
	acc_num2 = receive_char();
	account_info_display(acc_num2);
	transmit_string("Enter Amount, in hundreds");
	transmit_string("\r\n");
	amt_d1 = receive_char();
	amt_d2 = receive_char();
	if(!(47 < amt_d1 && 58 > amt_d1) || !(47 < amt_d2 && 58 > amt_d2)){
		transmit_string("Invalid Amount");
		initialize();
		return;
	}
	amt = amt_d1*10 + amt_d2;
	transaction(amt,acc_num2);
}

void main(void)
{
	spi_init();																					
	uart_init();
	
	initialize();
	while(1){
		if (state == "A" || state == "a"){
			transmit_string("Hello, Please enter Account Number");
			transmit_string("\r\n");
			account_num = receive_char();
			account_info_display(account_num);
		}
		if (state == "W" || state == "w"){
			withdraw_info();
		}
  }
}

