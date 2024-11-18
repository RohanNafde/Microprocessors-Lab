ORG 0H
LJMP MAIN
ORG 100H
	
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP

HERE: SJMP HERE
ORG 130H

TAKE_INP:
//4 inputs, loop for that, R2 counter for loop and R3 for LED
MOV R0, #60H
MOV R1, #0FH

LOOP5:

//increment R1 by 16
MOV A, #10H
ADD A, R1
MOV R1, A
//turn on LED
MOV P1, R1

CALL delay_10s
CLR C
//read first 4 MSBs and store multiplying it to F
MOV A, P1
MOV B, #10H
MUL AB
MOV @R0, A

//increment R1 by 16
CLR C
MOV A, #10H
ADD A, R1
MOV R1, A
//turn on LED
MOV P1, R1

CALL delay_10s

//read last 4 LSBs and add to value at r2
CLR C
MOV A, P1
XCHD A, @R0

//increment and check loop
INC R0
CJNE R0, #64H, LOOP5

RET

QUANT_ENC:

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
CJNE R0, #64H, LOOP

RET

LED_DISP:

LOOPINF:

//start from 70H
MOV R0, #70H

LOOPO:

CJNE @R0, #05H, O1
MOV P1, #10H
AJMP LOOPCHECK

O1:
CJNE @R0, #0FH, O2
MOV P1, #20H
AJMP LOOPCHECK

O2:
CJNE @R0, #19H, O3
MOV P1, #40H
AJMP LOOPCHECK

O3:
MOV P1, #80H

LOOPCHECK:
CALL delay_5s
INC R0
CJNE R0, #74H, LOOPO

AJMP LOOPINF

RET

delay_5s:
//use 2 loops since cannot iterate 5000 times using 1 byte

//outer loop counter to 50
MOV R2, #32H

LOOP1:
//initialise inner loop counter to 100
MOV R3, #64H
CLR C

LOOP2:
CALL delay_1ms
//decrease and check till R1 becomes 0, to iterate it 50 times
DJNZ R3, LOOP2

//decrease and check till R0 becomes 0, to iterate it 100 times
DJNZ R2, LOOP1

RET

delay_10s:

//use delay_5s twice
CALL delay_5s
CALL delay_5s

RET

delay_1ms:
push 00h
mov r0, #4
h2: acall delay_250us
djnz r0, h2
pop 00h
ret

delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret

END
