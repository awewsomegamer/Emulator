mov bx, FIRST_EQUATION
call PRINT_STRING

mov ax, 5+10
mov bx, 3
int 1

mov ax, 0xA
mov bx, 0
int 1

mov bx, SECOND_EQUATION
call PRINT_STRING

mov ax, 5*10
mov bx, 3
int 1

mov ax, 0xA
mov bx, 0
int 1

mov bx, THIRD_EQUATION
call PRINT_STRING

mov ax, 10-5
mov bx, 3
int 1

mov ax, 0xA
mov bx, 0
int 1

mov bx, FOURTH_EQUATION
call PRINT_STRING

mov ax, 10/5
mov bx, 3
int 1

mov ax, 0xA
mov bx, 0
int 1


TERMINATE:
	jmp TERMINATE

PRINT_STRING:
	mov ax, [bx]
	cmp ax, 0
	je PRINT_STRING_END

	push bx
	mov bx, 0
	int 1
	pop bx

	add bx, 1

	jmp PRINT_STRING

PRINT_STRING_END:
	ret



jmp DATA_END

FIRST_EQUATION:
	ds "5 + 10 = "
	db 0x0

SECOND_EQUATION:
	ds "5 * 10 = "
	db 0x0

THIRD_EQUATION:
	ds "10 - 5 = "
	db 0x0

FOURTH_EQUATION:
	ds "10 / 5 = "
	db 0x0

DATA_END:
