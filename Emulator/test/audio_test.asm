outb 0x4, 0x41
outd 0x6, 440

mov bp, 0x1000
mov sp, bp

; mov ax, 10
; call WAIT

;outd 0x6, 1000 ; Set clock datas (Set frequency of currently selected channel)

sivte 0, TIMER_HANDLER
mov bx, 0

TERMINATE:
	mov ax, 2
	mov bx, 3
	int 1

	jmp TERMINATE

; WAIT:
; 	push bx
; 	mov bx, 3
; 	push ax
; 	mov ax, [TICK]
; 	int 0
; 	pop ax

; 	mov bx, [TICK]
; 	add bx, ax

; 	WAIT_LOOP:
; 		cmp [TICK], bx
; 		je WAIT_END
; 		jmp WAIT_LOOP


; 	WAIT_END:
; 		pop bx

; 		ret

TIMER_HANDLER:
	mov ax, 1
	int 1
	
	iret

TICK:
	db 0x0
