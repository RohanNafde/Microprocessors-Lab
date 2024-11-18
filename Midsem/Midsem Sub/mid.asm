ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
MOV 70H, #0D8H
MOV 71H, #0ADH
CALL ENCRYPT
HERE: SJMP HERE
ORG 130H
	
ENCRYPT:
//x in 70h, e in 71h stored
//add 1 to x initially
MOV R0, #01
//initialise d
MOV R1, #00
CLR C

//loop to find d
LOOP:
MOV A, R0
ADD A, 70H
//this adds x each time so that we find d, first iteration stores x+1 in A

//repeated subtraction by e, 
SUBT:
CLR C
//increment d each time we subtract
INC R1
CLR C
SUBB A, 71H
JNC SUBT

//add back one e
ADD A, 71H
//decrement extra inc in R1
DEC R1
MOV R0, A

CJNE A, #00, LOOP

LAST:
MOV 72H, R1

OUTPUT:

MOV R0, #72H
MOV A, #00

//lower bits
XCHD A, @R0
MOV 80H, A
MOV 72H, A

//upper bits display
//MUL A, #01H
MOV P1, A
CALL delay_5s

//0000
MOV P1, #00H
CALL delay_1s

//lower bits display
MOV A, 80H
MOV B, #10H
MUL AB
MOV P1, A
CALL delay_5s

//0000
MOV P1, #00H
CALL delay_1s

AJMP OUTPUT

RET

delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret

delay_50ms:
push 00h
mov r0, #0C8H
h2: acall delay_250us
djnz r0, h2
pop 00h
ret

delay_1s:
push 00h
mov r0, #14H
h3: acall delay_50ms
djnz r0, h3
pop 00h
ret

delay_5s:
push 00h
mov r0, #05H
h4: acall delay_1s
djnz r0, h4
pop 00h
ret

END