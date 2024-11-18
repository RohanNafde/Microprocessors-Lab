ORG 0H
LJMP MAIN
ORG 100H

MAIN:
CALL FILT
HERE: SJMP HERE
ORG 130H

FILT:
// counter
MOV R0, #60H
MOV R1, #70H

//copy pasted loop concept from lab 3 Q1
LOOP:

//clear carry before every operation
CLR C

//store y of n-3 + y of n-2 + y of n-1 + y of n
//note that 57H 58H and 59H have 0 as said in Q
MOV A, @R0
DEC R0
ADD A, @R0
DEC R0
ADD A, @R0
DEC R0
ADD A, @R0

//increase back R0
INC R0
INC R0
INC R0

//divide by 4
MOV B, #04H
DIV AB
MOV @R1, A

LCHECK:
//break loop if it reaches beyond 67H
INC R0
INC R1
CJNE R0, #68H, LOOP

RET

END