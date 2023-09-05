.section .data
        arr: .quad 1, 2, 3, 5, 8, 13, 21, 34, 55, 89
        i: .quad 0
        n: 9

.section .text
.global _start
_start:
        movq i, %rax
        movq i, %rdi
        movq n, %rbx
_loop:
        cmp %rax, %rbx
        je _outOfLoop
        and arr(, %rax, $8), $1
        addq $1, %rdi

_impar:
        addq $1, %rax
        jmp _loop

_outOfLoop:
        movq $60, %rax
        syscall

