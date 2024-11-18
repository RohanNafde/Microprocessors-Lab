// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
//store 61H in R1
MOV R1, #61H

//call functions
CALL MODADD
CALL MODSUB
HERE: SJMP HERE
ORG 130H
	
MODADD:
//modulo of value taken since we need modulo at end
MOV A, 70H
MOV B, R1
DIV AB
MOV R2, B

//modulo of value taken since we need modulo at end
MOV A, 71H
MOV B, R1
DIV AB
MOV A, R2
ADD A, B

MOV B, R1

DIV AB
MOV 72H, B
RET

MODSUB:
//modulo of value taken since we need modulo at end
MOV A, 70H
MOV B, R1
DIV AB
MOV R2, B

//modulo of value taken since we need modulo at end
MOV A, 71H
MOV B, R1
DIV AB
MOV A, R2
SUBB A, B

//This addition necessary to compensate for negative numbers else value overshoots to FF-number and gives wrong answer
ADD A, R1
DIV AB
MOV 73H, B
RET

END
