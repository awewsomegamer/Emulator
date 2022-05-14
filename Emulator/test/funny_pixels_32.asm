; mov bp, 0x8000
; mov sp, bp

; push 'A'
; push 'B'

; mov ax, 'Z'

; pop ax
; pop ax


; LOOP:
; 	int 0
; 	jmp LOOP

push 'A'
pop ax

mov i1, 0 ; R
mov i2, 0 ; G
mov i3, 0 ; B

mov bx, 0xB8000 ; Screen buffer

mov cx, 640 ; Screen buffer end
mul cx, 480
mul cx, 4
add cx, 0xB8000

LOOP:
	cmp bx, cx
	je RESET

	mov [bx], i1
	add bx, 1
	mov [bx], i2
	add bx, 1
	mov [bx], i3
	add bx, 1
	mov [bx], 0
	add bx, 1
	
	add i1, 1

	cmp i1, 255
	jle COLOR_RESET_I1_END

	mov i1, 0
	add i2, 1
	
	COLOR_RESET_I1_END:

	cmp i2, 255
	jle COLOR_RESET_I2_END

	mov i2, 0
	add i3, 1
	
	COLOR_RESET_I2_END:

	cmp i3, 255
	jle COLOR_RESET_I3_END

	mov i3, 0
	
	COLOR_RESET_I3_END:

	; add i2, 0
	; add i3, 0

	; cmp i1, 255
	; jle COLOR_RESET_END
	
	; ; mov i1, 0
	; ; mov i2, 0
	; ; mov i3, 0

	; COLOR_RESET_END:

	jmp LOOP

RESET:
	push ax
	mov ax, 0xA
	int 0
	pop ax
	int 0

	mov bx, 0xB8000

	jmp LOOP

; mov bx, 0xB8000
; mov cx, bx
; add cx, 150

; mov [bx], 0xFF
; add bx, 1
; mov [bx], 0xFF
; add bx, 1
; mov [bx], 0xFF
; add bx, 1

; LOOP:
; 	jmp LOOP

; LOOP:
; 	cmp bx, cx
; 	je RESET

; 	jmp LOOP

; RESET:
; 	mov bx, 0xB8000

; 	jmp LOOP
