; mov ax, 0 ; Current cell value
; mov cx, 0x1000 ; Current cell ptr
; mov bx, DATA ; Source ptr

; mov bp, PROGRAM_END
; add bp, 0x5000
; mov bp, 0x1000
; mov sp, bp

; mov i1, 0
; mov i2, 0

; Draw pixel
; mov i1, 10
; shl i1, 16
; or i1, 10

; mov i2, 0x0000FF00
; int 1

; Successfully set interrupt (27/5/2022)
sivte 2, KEY_INTERRUPT

LOOP:
	call FUNNY

	jmp LOOP

KEY_INTERRUPT:
	mov ax, 'A'
	int 0

	ret

; LOOP:
; 	cmp [bx], '+'
; 	jne END_INC_SEC
	
; 	add [cx], 1
; 	jmp COMMON_END_STUB

; 	END_INC_SEC:

; 	cmp [bx], '.'
; 	jne END_PRINT_SEC

; 	mov ax, [cx]
; 	int 0

; 	jmp COMMON_END_STUB
	
; 	END_PRINT_SEC:

; 	cmp [bx], '-'
; 	jne END_DEC_SEC
; 	cmp [cx], 0
; 	je END_DEC_SEC

; 	sub [cx], 1

; 	jmp COMMON_END_STUB
; 	END_DEC_SEC:

; 	cmp [bx], '>'
; 	jne END_ARROW_RIGHT_SEC

; 	add cx, 1

; 	jmp COMMON_END_STUB
; 	END_ARROW_RIGHT_SEC:

; 	cmp [bx], '<'
; 	jne END_ARROW_LEFT_SEC

; 	sub cx, 1

; 	jmp COMMON_END_STUB
; 	END_ARROW_LEFT_SEC:

; 	COMMON_END_STUB:

; 	add bx, 1
; 	cmp [bx], 0
; 	je TERMINATE
	
; 	jmp LOOP

; TERMINATE:
; 	jmp TERMINATE

; DATA:
; 	; ds "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>" ; H
; 	; ds "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>" ; e
; 	; ds "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++..>" ; l
; 	; ds "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++." ; o
; 	ds "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++<.>.."

; 	db 0

; PROGRAM_END:

; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ -> A
