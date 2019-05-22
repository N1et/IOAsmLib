# I/O Assembly lib 
Para o estudo do livro Low-Level Programming, eu precisei fazer uma lib para facilitar a manipulação de entrada/saida. A lib no geral é bem simples, porém é bastante útil. Abaixo as funções que a lib oferece.

## calls
Os argumentos das funções seguem o mesmo padrão das syscalls x86-64. RAX é o registrador de retorno.

| call          | rdi                   | rsi            | rdx            | rax(return)                                   |
|---------------|-----------------------|----------------|----------------|---------------------------------------------|
| exit          | signed int code |                |                |                                             |
| string_length | char \*string          |                |                | int sizeofstring                            |
| print_string  | char \*string          |                |                |                                             |
| print_char    | char ch               |                |                |                                             |
| print_newline |                       |                |                |                                             |
| print_uint    | unsigned int number   |                |                |                                             |
| print_int     | signed int number     |                |                |                                             |
| read_char     |                       |                |                | char ch                                     |
| read_word     | char \*buf             | size_t bufsize |                | 0 - something wrong size_t bufsize - sucess |
| string_equals | char \*string1         | char \*string2  |                |  0 - not equal 1 - equal                    |
| string_copy   | char \*string          | char \*buf      | size_t bufsize |                                             |

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
