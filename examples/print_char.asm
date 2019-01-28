%include "lib.inc"
section .text
global _start

_start:
	; ----  print char 
	mov rdi, "A"
	call print_char

	mov rdi, "B"
	call print_char

	mov rdi, "C"
	call print_char

	call print_newline
	call exit
