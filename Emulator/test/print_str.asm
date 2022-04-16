mov bx, My_String

Print_Str:
	cmp bx, 0
	je End

	mov ax, [bx] ; Need to implement the [] for registers
	int 0
	
	add bx, 1
	
	jmp Print_Str

End:


My_String:
	ds "Hello World"

; mov ax, 0xAA
; mov bx, ax
; mov cx, [ax]
; mov dx, [0xAA]
