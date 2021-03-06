STACK SEGMENT STACK
	DB 128 DUP(0)
STACK ENDS

DATA SEGMENT
	ARRAY DB 256 DUP(0)
	DATA_t DW ?
	DATA_d DW ?
	DATA_j DW ?
	DATA_i DW ?
DATA ENDS

CODE SEGMENT 'CODE'
INPUT PROC FAR
	MOV AH, 1
	INT 21H
	RET
INPUT ENDP

OUTPUT PROC FAR
	MOV AH, 06H
	INT 21H
	RET
OUTPUT ENDP

MAIN PROC FAR
	ASSUME CS:CODE, DS:DATA, SS:STACK
	MOV BP, OFFSET ARRAY

	MOV DX, 62
	MOV DH, 0
	CALL OUTPUT
	CALL INPUT
	MOV AH, 0
	MOV WORD PTR[BP+0], AX
	MOV CX, WORD PTR[BP+0]
	MOV DATA_t, CX
	MOV CX, DATA_t
	MOV WORD PTR[BP+0], CX
	MOV AX, DATA_t
	SUB AX, 48
	MOV WORD PTR[BP+2], AX
	MOV CX, WORD PTR[BP+2]
	MOV DATA_t, CX
	MOV CX, DATA_t
	MOV WORD PTR[BP+2], CX
	MOV AX, DATA_t
	ADD AX, 1
	MOV WORD PTR[BP+4], AX
	MOV AX, DATA_t
	MOV DX, 0
	MOV CX, 2
	IDIV CX
	MOV WORD PTR[BP+6], AX
	MOV AX, WORD PTR[BP+4]
	SUB AX, WORD PTR[BP+6]
	MOV WORD PTR[BP+4], AX
	MOV CX, WORD PTR[BP+4]
	MOV DATA_i, CX
	MOV CX, DATA_i
	MOV WORD PTR[BP+4], CX
	MOV AX, 3
	MOV CX, 4
	IMUL CX
	MOV WORD PTR[BP+6], AX
	MOV AX, 2
	ADD AX, WORD PTR[BP+6]
	MOV WORD PTR[BP+6], AX
	MOV AX, WORD PTR[BP+6]
	SUB AX, 6
	MOV WORD PTR[BP+6], AX
	MOV CX, WORD PTR[BP+6]
	MOV DATA_j, CX
	MOV CX, DATA_j
	MOV WORD PTR[BP+6], CX
	MOV AX, 2
	MOV CX, 2
	IMUL CX
	MOV WORD PTR[BP+8], AX
	MOV CX, WORD PTR[BP+8]
	MOV DATA_i, CX
	MOV CX, DATA_i
	MOV WORD PTR[BP+8], CX
	MOV AX, DATA_j
	MOV CX, 2
	IMUL CX
	MOV WORD PTR[BP+10], AX
	MOV AX, WORD PTR[BP+10]
	MOV DX, 0
	MOV CX, 4
	IDIV CX
	MOV WORD PTR[BP+10], AX
	MOV AX, WORD PTR[BP+8]
	ADD AX, WORD PTR[BP+10]
	MOV WORD PTR[BP+8], AX
	MOV AX, WORD PTR[BP+8]
	ADD AX, DATA_t
	MOV WORD PTR[BP+8], AX
	MOV AX, WORD PTR[BP+8]
	ADD AX, 97
	MOV WORD PTR[BP+8], AX
	MOV CX, WORD PTR[BP+8]
	MOV DATA_d, CX
	MOV CX, DATA_d
	MOV WORD PTR[BP+8], CX
	MOV DX, 10
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 32
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 100
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 61
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 39
	MOV DH, 0
	CALL OUTPUT
	MOV DX, DATA_d
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 39
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 32
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 58
	MOV DH, 0
	CALL OUTPUT
	MOV DX, 41
	MOV DH, 0
	CALL OUTPUT
	MOV AH, 4CH
	INT 21H
MAIN ENDP
CODE ENDS
END MAIN
