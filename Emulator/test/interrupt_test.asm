MY_LOOP:
	mov ax, 'H'
	int 0
	mov ax, 'e'
	int 0
	mov ax, 'l'
	int 0
	mov ax, 'l'
	int 0
	mov ax, 'o'
	int 0
	mov ax, 0xA
	int 0
	int 0
	mov ax, 0xD
	int 0

	;cmp ax, 55
	;jnc MY_LOOP

;mov ax, 'E'
;int 0
