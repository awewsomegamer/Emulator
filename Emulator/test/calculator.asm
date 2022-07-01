; pseduo code
; "Calculator"
; "First number: "
; number1: input()
; "Second number: "
; number2: input()
; "Operation: "
; operation: input()
; if op == 'whatever'
; then whatever()

mov bp, 0x1000
mov sp, bp

sivte 3, handle_keyboard

mov bx, WELCOME_MESSAGE
call print_string

mov bx, FIRST_NUMBER_MESSAGE
call print_string

mov [CURRENT_BUFFER], NUMBER1
mov [QUERYING_INPUT], 0xFF
call get_input

mov bx, SECOND_NUMBER_MESSAGE
call print_string

mov bx, OPERATION_MESSAGE
call print_string

mov bx, RESULT_MESSAGE
call print_string

; Safe guard for data and functions
TERMINATE:
	jmp TERMINATE

; Print a string
; char* in bx
print_string:
	mov ax, [bx]
	cmp ax, 0
	
	je print_string_end

	push bx
	mov bx, 0
	int 0
	pop bx

	add bx, 1

	jmp print_string

print_string_end:
	ret

; Hang until input is completed
get_input:
	cmp QUERYING_INPUT, 0xFF
	je get_input
	ret

handle_keyboard:
	; Check if reading input
	cmp QUERYING_INPUT, 0xFF
	jne handle_keyboard_end

	; Check if key was released
	ind ax, 0x0
	and ax, 0x00FF0000
	cmp ax, 0x00FF0000
	je handle_keyboard_end

	; Check if return key was pressed
	ind ax, 0x0
	and ax, 0x0000FFFF
	cmp ax, 40
	je handle_keyboard_return

	; Check if backspace key was pressed
	cmp ax, 42
	je handle_keyboard_backspace

	; Make sure that key pressed is >= 30 (key 1)
	cmp ax, 30
	jl handle_keyboard_end
	
	; Make sure that key pressed is <= 38 (key 0)
	cmp ax, 39
	jg handle_keyboard_end

	; Write char to current buffer
	mov [CURRENT_BUFFER], ax
	add CURRENT_BUFFER, 1

	; Print char
	push bx
	int 0
	pop bx

	jmp handle_keyboard_end

	; Handle return
	handle_keyboard_return:

	mov [QUERYING_INPUT], 0x00
	jmp handle_keyboard_end

	; Handle backspace
	handle_keyboard_backspace:
	
	sub CURRENT_BUFFER, 1
	mov [CURRENT_BUFFER], 0x0

	jmp handle_keyboard_end

	handle_keyboard_end:
	ret


; Convert char* in bx to number in ax
string_to_number:
	ret

jmp DATA_END
WELCOME_MESSAGE:
	ds "CALCULATOR"
	db 0xA
	db 0x0

FIRST_NUMBER_MESSAGE:
	ds "FIRST NUMBER: "
	db 0x0

SECOND_NUMBER_MESSAGE:
	db 0xA
	ds "SECOND NUMBER: "
	db 0x0

OPERATION_MESSAGE:
	db 0xA
	ds "OPERATION: "
	db 0x0

RESULT_MESSAGE:
	db 0xA
	ds "THE ANSWER IS: "
	db 0x0

; First number string
NUMBER1:
	db 0x0, 0x0, 0x0

; Second number string
NUMBER2:
	db 0x0, 0x0, 0x0

; Looking (0xFF) or not looking (0x00) for input
QUERYING_INPUT:
	db 0x0

; Pointer of the current number to write
CURRENT_BUFFER:
	db 0x0, 0x0

DATA_END:
