; ; VERSION 1:
; ; Written by awewsomegamer
; ; 7/5/2022
; ; AX - Current color
; ; BX - Screen ptr
; ; CX - Screen ptr end
; ; DX - Inner place pixel loop counter
; ; I1 - Number of inner loops

; mov ax, 0
; mov bx, 0xB8000

; mov cx, 640
; mul cx, 480
; add cx, 0xB8000

; mov dx, 0
; mov i1, 1

; LOOP:
; 	cmp bx, cx
; 	jge RESET

; 	PLACE_PIXELS:
; 	mov [bx], ax
; 	add bx, 1
; 	add dx, 1

; 	cmp dx, i1
; 	jge PLACE_PIXELS_END

; 	jmp PLACE_PIXELS

; 	PLACE_PIXELS_END:
; 	mov dx, 0
; 	add i1, 1

; 	add ax, 1

; 	cmp ax, 16
; 	jge END_AX_RESET

; 	mov ax, 0

; 	END_AX_RESET:

; 	jmp LOOP

; RESET:
; 	mov bx, 0xB8000
; 	; mov ax, 0

; 	jmp LOOP


; Version 2:

; AX - Current color
; BX - Screen ptr
; CX - Screen ptr end
; DX - Inner place pixel loop counter
; I1 - Number of inner loops

; mov ax, 0
; mov bx, 0xB8000

; mov cx, 640
; mul cx, 480
; add cx, 0xB8000

; mov dx, 0
; mov i1, 1

; LOOP:
; cmp bx, cx
; jge RESET

; PLACE_PIXELS:
; mov [bx], ax
; add bx, 1
; add dx, 1

; cmp dx, i1
; je PLACE_PIXELS_END

; jmp PLACE_PIXELS

; PLACE_PIXELS_END:
; mov dx, 0
; add i1, 1

; add ax, 1

; cmp ax, 17
; jne END_AX_RESET

; mov ax, 0

; END_AX_RESET:

; jmp LOOP

; RESET:
; mov bx, 0xB8000
; mov i1, 1
; ; mov ax, 0

; jmp LOOP

; VERSION 3:
; AX - Current color
; BX - Screen ptr
; CX - Screen ptr end
; DX - Inner place pixel loop counter
; I1 - Number of inner loops
; mov ax, 0
; mov bx, 0xB8000

; mov cx, 640
; mul cx, 480
; add cx, 0xB8000

; mov dx, 0
; mov i1, 25

; LOOP:
; 	cmp bx, cx
; 	jge RESET

; 	PLACE_PIXELS:
; 		mov [bx], ax
; 		add bx, 1
; 		add dx, 1

; 		cmp dx, i1
; 		je PLACE_PIXELS_END

; 		jmp PLACE_PIXELS

; 	PLACE_PIXELS_END:
; 		mov dx, 0
; 		add i1, 1

; 	add ax, 1

; 	cmp ax, 16
; 	jl END_AX_RESET

; 	; mov ax, 0

; 	END_AX_RESET:
; 	add bx, 1

; 	jmp LOOP

; RESET:
; 	mov bx, 0xB8000
; 	mov i1, 25
; 	; mov ax, 0

; 	jmp LOOP

; Version 2
mov ax, 0
mov bx, 0xB8000

mov cx, 640
mul cx, 480
add cx, 0xB8000

mov dx, 0
mov i1, 1

LOOP:
cmp bx, cx
jge RESET

PLACE_PIXELS:
mov [bx], ax
add bx, 1
add dx, 1

cmp dx, i1
je PLACE_PIXELS_END

jmp PLACE_PIXELS

PLACE_PIXELS_END:
mov dx, 0
add i1, 1

add ax, 1

cmp ax, 17
jne END_AX_RESET

mov ax, 0

END_AX_RESET:

jmp LOOP

RESET:
mov bx, 0xB8000
mov i1, 1
; mov ax, 0

jmp LOOP

