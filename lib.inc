; exit
; print_string
; print_char
; print_newline
; print_uint
; print_int
; read_char
; read_word
; parse_uint
; parse_int
; string_equals
; string_copy

SECTION .text

; exit func
; args: 
; rdi - exit code

exit: 
	mov rax, 60 ; sys_exit
	syscall

; string_length
; args:
; rdi - string pointer
; return: 
; rax - size of string
; registers used: rax
string_length:  
	xor rax, rax 

.loop:
	cmp byte [rdi+rax], 0
	je .break
	inc rax
	jmp .loop

.break:
	ret

; print_string
; args:
; rdi - string pointer
; used: rdx, rax
print_string:
	push rdx
	push rax
	call	string_length
	mov rsi, rdi
	mov rdx, rax ; size_t
	mov rax, 1 ; sys_write
	mov rdi, 1 ; stdout
	syscall
	pop rax
	pop rdx
	ret

; print_char
; args:
; rdi - a caracter code
; used: rdi, rdx, rax
print_char:
	push rsi
	push rax
	push rdx
	push rdi
	mov rsi, rsp ; char to *char
	mov rax, 1 ; sys_write
	mov rdx, 1 ; size_t, 1 byte
	mov rdi, 1 ; stdout
	syscall
	pop rdi
	pop rdx
	pop rax
	pop rsi 
	ret

; print_newline
; print 0xa="\n"
; used: rdi
print_newline:
	push rdi
	mov rdi, 0x0a
	call print_char
	pop rdi
	ret
; print_uint
; rdi - decimal number
; used: rsi, rax, rcx, rdi
print_uint:
	push rsi
	push rax
	push rcx
	push rdi
	xor rsi, rsi ; counter
	mov rax, rdi 
	mov rcx, 10 ; divisor
.loop:
	xor rdx, rdx
	div rcx
	push rdx
	inc rsi
	cmp rax, 0
	jnz .loop

.reverse:
	pop rax
	dec rsi
	add rax, 48
	mov rdi, rax
	call print_char
	cmp rsi, 0
	jnz .reverse
	pop rdi
	pop rcx
	pop rax
	pop rsi
	ret

; print_int
; rdi - decimal number
; used: rdi
print_int:
	test rdi, rdi
	js .int
	call print_uint
	ret

.int:
	push rdi
	mov rdi, '-'
	call print_char
	pop rdi
	neg rdi
	call print_uint
	ret
	
; read_char
; used: rax, rdi, rsi, rdx
; return char in rax
read_char:
	push rdi
	push rsi
	push rdx
	push 0 
	mov rax, 0
	mov rdi, 0
	mov rsi, rsp
	mov rdx, 1
	syscall
	pop rax
	pop rdx
	pop rsi
	pop rdi
	ret 

; read_word
; rdi - buffer address
; rsi - size buffer
; used: rcx, rdx, rax
; return rax 
; 0 - word > size buffer
; address - sucess 
read_word:
	xor rdx, rdx
	mov rcx, rsi

.loop:
	push rcx
	call read_char
	pop rcx
	cmp al, 0x20
	je .loop
	cmp al, 0x9
	je .loop
	cmp al, 0x10
	je .loop
	cmp al, 0x0a
	je .finsh
	inc rdx

	cmp rdx, rcx
	ja .cnl

	mov BYTE [rdi+rdx-1], al
	jmp .loop


.finsh:
	mov rax, rdi
	ret
.cnl:
	xor rax, rax
	ret


; parse_uint
; rdi - str pointer
parse_uint:
   push rcx
   xor rcx, rcx ; counter
   xor rbx, rbx ;
   mov rax, 10
.loop:
   mov sil, [rdi+rcx]
   cmp sil, 48
   jb .end
   cmp sil, 57
   ja .end
   inc rcx
   push rax
   sub rsi, 48
   mul rbx
   add rax, rsi
   mov rbx, rax
   pop rax
   jmp .loop


.end:
   mov rax, rbx
   mov rdx, rcx
   pop rcx
   ret
; parse_int
; rdi - str pointer
parse_int:
   mov al, [rdi]
   cmp al, '-'
   je .sig
   jmp parse_uint

.sig:
   inc rdi
   call parse_uint
   neg rax
   inc rdx
   ret

; string_equals
; rdi - str1
; rsi - str2
; used: rdx, rax, rbx, rcx
; return rax

string_equals:
   push rdx
   push rbx
   push rcx
   xor rdx, rdx
   mov rax, rdi
   call .sum
   mov rbx, rdx

   xor rdx, rdx
   mov rax, rsi
   call .sum
   mov rcx, rdx

   cmp rbx, rcx
   pop rcx
   pop rbx
   pop rdx
   je .r1
   mov rax, 0
   ret

.r1:
   mov rax, 1
   ret

.sum:
   mov cl, [rax]
   add rdx, rcx
   cmp cl, 0
   jz .end
   inc rax
   jmp .sum

.end:
   ret
; string_copy
; rdi - string pointer
; rsi - buffer src
; rdx - size buffer src
string_copy:
   push rcx
   call string_length
   cmp rax, rdx
   xor rax, rax
   ja .end
   mov rax, rsi 
   xor rcx, rcx ; counter
	
.loop:
   mov bl, [rdi+rcx]
   cmp bl, 0 
   je .end
   mov BYTE [rsi+rcx], bl
   inc rcx
   jmp .loop

.end:
   pop rcx
   ret



	
