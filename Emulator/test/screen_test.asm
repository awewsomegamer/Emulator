; AX register as color
; BX register as screen ptr
; CX end screen ptr

; mov bx, 0xB8000

; mov cx, 640
; mul cx, 480
; add cx, 0xB8000

; LOOP:
; 	mov [bx], ax

; 	cmp ax, 15
; 	call RESET_AX

; 	add ax, 1
; 	add bx, 1

; 	cmp bx, cx
; 	je END

; 	jmp LOOP

; RESET:
; 	mov ax, 0
; 	add bx, 1

; 	jmp LOOP

; END:

; mov ax, 1
; mov bx, 0xB8000

; mov bx, 0xB8000
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1
; mov [bx], ax
; add bx, 1

; mov bx, 0xB8000

; LOOP:
; 	cmp bx, cx
; 	jge END

; 	mov [bx], 1
; 	; add ax, 1

; 	; cmp ax, 16
; 	; jl SKIP

; 	; mov ax, 0

; 	; SKIP:

; 	add bx, 1

; 	jmp LOOP

; END:
; 	jmp END


mov bx, 0xB8000
mov ax, 1

mov cx, 640
mul cx, 480
add cx, 0xB8000

LOOP:
	cmp bx, cx
	je END

	mov [bx], ax

	add bx, 1

	jmp LOOP

END:
	jmp END
	; mov ax, 65
	; int 0
	; mov ax, 0x10
	; int 0

