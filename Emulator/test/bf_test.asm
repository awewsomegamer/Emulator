mov ax, 0 ; Current cell value
mov cx, 0x1000 ; Current cell ptr
mov bx, DATA ; Source ptr

mov bp, PROGRAM_END
add bp, 0x5000
mov sp, bp

LOOP:
	cmp [bx], '+'
	jne END_INC_SEC
	
	add [cx], 1
	jmp COMMON_END_STUB

	END_INC_SEC:

	cmp [bx], '.'
	jne END_PRINT_SEC

	mov ax, [cx]
	int 0

	jmp COMMON_END_STUB
	
	END_PRINT_SEC:

	cmp [bx], '-'
	jne END_DEC_SEC
	cmp [cx], 0
	je END_DEC_SEC

	sub [cx], 1

	jmp COMMON_END_STUB
	END_DEC_SEC:

	cmp [bx], '>'
	jne END_ARROW_RIGHT_SEC

	add cx, 1

	jmp COMMON_END_STUB
	END_ARROW_RIGHT_SEC:

	cmp [bx], '<'
	jne END_ARROW_LEFT_SEC

	sub cx, 1

	jmp COMMON_END_STUB
	END_ARROW_LEFT_SEC:

	COMMON_END_STUB:

	add bx, 1
	cmp [bx], 0
	jmp TERMINATE
	
	jmp LOOP

TERMINATE:
	jmp TERMINATE

DATA:
	; ds "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>" ; H
; 	;ds "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>" ; e
; 	;ds "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++..>" ; l
; 	;ds "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++." ; o

	ds "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."

	db 0

PROGRAM_END:

; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ -> A
