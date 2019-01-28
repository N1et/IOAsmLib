%include "lib.inc"

section .text

global _start

_start:
	mov rdi, 12345
	call print_uint
	call print_newline
	mov rdi, -12345
	call print_int
	call print_newline
	call exit
	
