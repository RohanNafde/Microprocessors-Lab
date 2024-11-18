ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:

//clear LEDs
CLR P1.7
CLR P1.6
CLR P1.5
CLR P1.4

CALL OUTPUT
HERE: SJMP HERE
ORG 130H

OUTPUT:

//take input
SETB P1.0
SETB P1.1
SETB P1.2
SETB P1.3

//check input
MOV A, P1

//compare with 1, if yes, go in SA, if not equal go ahead and check for RE
CJNE A, #01H, REX

//if 1 then output 1 cycle of SA
SA:

//first 1 in P0.7 for T/2
MOV R0, #80
MOV P0, #80H
L1:
ACALL DELAY_25us
DJNZ R0, L1

//then 0 in P0.7 for T/2
MOV R0, #80
MOV P0, #00H
L2:
ACALL DELAY_25us
DJNZ R0, L2

//go to end of function
AJMP END_FXN

REX:

CJNE A, #03H, GAX

RE:

//first 1 in P0.7 for T/2
MOV R0, #70
MOV P0, #80H
L3:
ACALL DELAY_25us
DJNZ R0, L3

//then 0 in P0.7 for T/2
MOV R0, #70
MOV P0, #00H
L4:
ACALL DELAY_25us
DJNZ R0, L4

//go to end of function
AJMP END_FXN

AJMP END_FXN

GAX:

CJNE A, #07H, MAX

GA:

//first 1 in P0.7 for T/2
MOV R0, #62
MOV P0, #80H
L5:
ACALL DELAY_25us
DJNZ R0, L5

//then 0 in P0.7 for T/2
MOV R0, #62
MOV P0, #00H
L6:
ACALL DELAY_25us
DJNZ R0, L6

//go to end of function
AJMP END_FXN

AJMP END_FXN

MAX:

CJNE A, #0FH, END_FXN

MA:

//first 1 in P0.7 for T/2
MOV R0, #59
MOV P0, #80H
L7:
ACALL DELAY_25us
DJNZ R0, L7

//then 0 in P0.7 for T/2
MOV R0, #59
MOV P0, #00H
L8:
ACALL DELAY_25us
DJNZ R0, L8

//go to end of function
AJMP END_FXN

END_FXN:

AJMP OUTPUT

RET

DELAY_25us:
push 00h
mov r0, #19
h1: djnz r0, h1
pop 00h
ret

END