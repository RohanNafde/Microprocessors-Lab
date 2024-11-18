ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
CALL DECRYPT
HERE: SJMP HERE
ORG 130H
	
DECRYPT:

INP:

MOV P1, #0FH
CALL delay_5s
MOV 71H, P1
CALL delay_5s
MOV A, P1
MOV B, #10H
MUL AB
ADD A, 71H
MOV 71H, A

PROCESS:

MOV 73H, 71H
MOV 75H, 71H
//loop counter, should run d-1 times
MOV R0, 72H
DEC R0

LOOP:
CALL SUBR_MUL
CALL SUBR_MOD
DJNZ R0, LOOP

OUTPUT:

MOV R0, #72H
MOV A, #00

//lower bits
XCHD A, @R0
MOV 80H, A

//upper bits display
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

SUBR_MUL:

CLR C
MOV A, 73H
MOV B, 75H
MUL AB
//lower byte
MOV 73H, A
MOV 80H, B
//upper byte
CLR C
MOV B, 75H
MOV A, 74H
MUL AB
//add prev higher bit
MOV R1, 80H
ADD A, R1
MOV 74H, A

RET

SUBR_MOD:

L:
CLR C
//higher bit mod
MOV A, 73H
SUBB A, 70H
MOV 73H, A
MOV A, 74H
SUBB A, #00
MOV 74H, A
JNC L

TERM:
// add extra deducted n back
MOV A, 73H
ADD A, 70H
MOV 73H, A
MOV 74H, #00

RET

END