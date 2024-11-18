ORG 0H
LJMP MAIN
ORG 100H

MAIN:
CALL QUANT
HERE: SJMP HERE
ORG 130H

QUANT:

// counter
MOV R0, #60H
MOV R1, #70H

LOOP:

//clear carry before every subtraction
CLR C
//below checks if number <10 i.e. <=9. Same goes for below 2 blocks too
MOV A, #09H
SUBB A, @R0
//not carry implies number less than or equal to 9 hence jump to L1 label
JNC L1

CLR C
MOV A, #13H
SUBB A, @R0
JNC L2

CLR C
MOV A, #1DH
SUBB A, @R0
JNC L3
//if carry means number >=30. jump to L4 then
JC L4
CLR C

L1:
//stores 05H i.e. 5 in corresponding memory address. same for below 3 labels too
MOV @R1, #05H
AJMP LCHECK

L2:
MOV @R1, #0FH
AJMP LCHECK

L3:
MOV @R1, #19H
AJMP LCHECK

L4:
MOV @R1, #23H
AJMP LCHECK

LCHECK:
//break loop if it reaches beyond 67H
INC R0
INC R1
CJNE R0, #68H, LOOP

RET

END
