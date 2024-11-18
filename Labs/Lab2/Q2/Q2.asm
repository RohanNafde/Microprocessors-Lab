ORG 0H
LJMP MAIN
ORG 100H

MAIN:
CALL DET
HERE: SJMP HERE
ORG 130H

DET:
//multiply b and c
MOV A, 61H
MOV B, 62H
MUL AB

//store results in R1 - lower bits, and R2 - higher bits
MOV R1, A
MOV R2, B

//multiply a and d
MOV A, 60H
MOV B, 63H
MUL AB

//subtract LSBs
SUBB A, R1
MOV 71H, A

//subtract MSBs
MOV A, B
SUBB A, R2
MOV 70H, A

RET

END