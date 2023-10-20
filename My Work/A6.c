section .text
	global main
	extern printf

main:
	mov	edi, masg
	mov	eax, 0
	call printf

section	.data
	masg db 'Hello, Holberton', 0xa, 0