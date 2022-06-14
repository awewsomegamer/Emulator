call LOAD_BOOT_SECTOR ; Bootloader should be loaded at 0x7000

; Load bootloader's signature into ax
push bx
mov bx, 0x7000
add bx, 510
mov ax, [bx]
pop bx

; Check if signature is valid
cmp bx, [BOOT_SIGNATURE]
je BOOTLOADER_FOUND
jne BOOTLOADER_NOT_FOUND


HANG:
	jmp HANG

LOAD_BOOT_SECTOR:
	mov ax, 0x0
	mov bx, 0x7000
	mov cx, 0x0
	mov dx, 0x1

	int 0x2

	ret

PRINT_STRING:
	mov ax, [bx]
	cmp ax, 0x0
	je PRINT_END
	
	push bx
	mov bx, 0
	int 0x0
	pop bx
	
	add bx, 1
	
	jmp PRINT_STRING

PRINT_END:
	ret

BOOTLOADER_FOUND:
	mov bx, MESSAGE2
	call PRINT_STRING

	jmp 0x7000

BOOTLOADER_NOT_FOUND:
	mov bx, MESSAGE3
	call PRINT_STRING

	jmp HANG

jmp DATA_END

BOOT_SIGNATURE:
	db 0xABCD

MESSAGE:
	ds "Loading boot sector"
	db 0

MESSAGE2:
	ds "Valid boot signature found"
	db 0xA
	ds "Booting..."
	db 0

MESSAGE3:
	ds "Invalid or no boot signature"
	db 0

DATA_END:
	jmp DATA_END
