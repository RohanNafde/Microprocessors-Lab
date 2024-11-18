ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
CALL BIN
HERE: SJMP HERE
ORG 130H
	
BIN:

//initialise
MOV R6, #60H //start
MOV R7, #67H //end

LOOP:

MID:
//find mid value and store in A

//divide first number by 2
CLR C
MOV A, 06
MOV B, #02
DIV AB
MOV 03, A
MOV 04, B
//divide 2nd number by 2 and add
CLR C
MOV A, 07
MOV B, #02
DIV AB
//ADD A, 03
//MOV R0, A
CLR C
MOV 05, A
//compensation for both odd
MOV A, B
ADD A, 04
CLR C
MOV B, #02
CLR C
DIV AB
CLR C
ADD A, 03
CLR C
ADD A, 05
MOV R0, A

COMPARE:
//compare value at mid with given value
MOV A, @R0
CJNE A, 50H, NOTEQ //50 here is the address where the value to be compared is stored

EQUAL:
MOV 90H, R0 //store location in 90
AJMP TERMINATE

NOTEQ:
JC GREATER
JNC LESS

GREATER:
//comes here if number greater than mid value, change lower bound
CLR C
MOV A, R0
ADD A, #01
MOV R6, A
AJMP CHECKLOOP

LESS:
//comes here if number less than mid value, change upper bound
CLR C
MOV A, R0
SUBB A, #01
MOV R7, A

AJMP CHECKLOOP

CHECKLOOP:
//terminate loop if start=end
MOV A, 06
SUBB A, #01
CJNE A, 07, LOOP

TERMINATE:
MOV A, 90H
CJNE A, #00, LAST
MOV 90H, #0FFH

LAST:

RET

END