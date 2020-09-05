>++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<+
+.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-
]<+.

# Hello, World!
Intended ASM Output:

.global main
.data
pc: .asciz "%c"
.bss
buffer: .skip 1000
.text
main:
movq $0, %rdx # init prt

addq $72, %rdx(buffer)
addq $1, %rdx
addq $101, %rdx(buffer)
addq $1, %rdx
addq $108, %rdx(buffer)
addq $1, %rdx
addq $108, %rdx(buffer)
addq $1, %rdx
addq $111, %rdx(buffer)
addq $1, %rdx
addq $44, %rdx(buffer)
addq $1, %rdx
addq $32, %rdx(buffer)
addq $1, %rdx
addq $87, %rdx(buffer)
addq $1, %rdx
addq $111, %rdx(buffer)
addq $1, %rdx
addq $114, %rdx(buffer)
addq $1, %rdx
addq $108, %rdx(buffer)
addq $1, %rdx
addq $100, %rdx(buffer)
addq $1, %rdx
addq $33, %rdx(buffer)
addq $1, %rdx

movq $0, %rax
movq $pc, %rdi
movq %rdx(buffer), %rsi
call printf
