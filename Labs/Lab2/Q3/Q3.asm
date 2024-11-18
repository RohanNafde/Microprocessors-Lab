ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
CALL SORT
HERE: SJMP HERE
ORG 130H
	
SORT:
//initialise R1 such that it acts as a counter i
MOV R1, #00H

//outer loop startes here
OUTERLOOP:
//store input start address in registers as actual values to perform increment operations on
MOV R0, #60H
//increment R1 and compare with 8, since we need loop to run 7 times. go in inner loop if R1<8
INC R1
CJNE R1, #08H, INNERLOOP

//put values in outputs
MOV 70H, 60H
MOV 71H, 61H
MOV 72H, 62H
MOV 73H, 63H
MOV 74H, 64H
MOV 75H, 65H
MOV 76H, 66H
MOV 77H, 67H

RET

//inner loop starts here
INNERLOOP:
//move value in address corresponding to R0 in accumulator, then increment R0
MOV A, @R0
INC R0
//clear carry to avoid BT
CLR C
//compare value of A with the value next to it in the sequence, if more then swap
SUBB A, @R0 //R0 has address of next value
JNC SWP

//check if we need to go back to outer loop, do so if we are at j=8-i, implies value at R0 is 68H-value of R1
OLCHECK:
//clear carry again to avoid BT
CLR C
//subtract 68-i
MOV A, #68H
SUBB A, R1

//use temporary memory space 40H to store R0 value of current address, since address can't be used in CJNE
MOV 40H, R0
CJNE A, 40H, INNERLOOP

//if equal, go to outer loop
AJMP OUTERLOOP

SWP:
//use temporary memory space 06H and 07H to swap value at current and previous address
MOV 06H, @R0
DEC R0
MOV 07H, @R0
MOV @R0, 06H
INC R0
MOV @R0, 07H

//jump to OLCHECK
AJMP OLCHECK

END