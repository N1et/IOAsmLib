%include "lib.inc"

section .data
	msg0: db "eu quero cafeee", 0
section .text

global _start

_start:
	mov rdi, msg0
	call print_string
	call print_newline
	call exit
	
