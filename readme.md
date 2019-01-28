# I/O Assembly lib 
Para o estudo do livro Low-Level Programming, eu precisei fazer uma lib para facilitar a manipulação de entrada/saida. A lib no geral é bem simples, porém é bastante útil. Abaixo as funções que a lib oferece.

## calls
- exit
- print char
- print string
- print new line (\n)
- print uint (int unsigned)
- print int (int signed)
- read char 
- read word
- parse uint (int unsigned)
- parse int (int singned)
- string equals
- string copy

## Examples

### print_number.asm
```asm
%include "lib.inc"

section .text

global _start

_start:
	mov rdi, 12345
	call print_uint ; int unsigned
	call print_newline
	mov rdi, -12345
	call print_int ; int signed
	call print_newline 
	call exit
 ```
