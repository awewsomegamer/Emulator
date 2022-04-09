mov dx, 'A'
mov ax, dx

LOOP:
	cmp ax, 'Z'
	jg END

	int 0

	add ax, 1

	jmp LOOP

END:
	;nop
	mov ax, 0xA
	int 0
	mov ax, dx

	cmp cx, 5
	jg E
	add cx, 1
	
	jmp LOOP

E:
	;nop
	mov ax, 'B'
	int 0
	sub ax, 'A'
	add ax, 1
	mul ax, 2
	add ax, 'A'
	int 0

	mov ax, 0xA
	int 0
