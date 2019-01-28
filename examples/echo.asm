%include "lib.inc"
section .bss
	buf: resb 1024

section .text
	
global _start


_start:
	mov rdi, buf
	mov rsi, 1024
	call read_word
	
	mov rdi, buf
	call print_string
	call print_newline
	
	call exit
	
