outb 0x4, 0x41
outd 0x6, 440

; mov ax, 10
; call WAIT

;outd 0x6, 1000 ; Set clock datas (Set frequency of currently selected channel)

sivte 0, TIMER_HANDLER

mov ax, 0

TERMINATE:
	mov bx, 0
	int 1
	; add ax, 1

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
	; mov ax, 'A'
	; mov bx, 0
	; int 1

	; add [TICK], 1

	ret

TICK:
	db 0x0