mov bx, My_String

Print_Str:
	mov ax, [bx]

	cmp ax, 0
	je End

	int 0
	
	add bx, 1
	
	jmp Print_Str

End:
	mov ax, 0xA
	int 0
	int 0

My_String:
	ds "Hello World"
