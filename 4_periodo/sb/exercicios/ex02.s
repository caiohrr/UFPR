.section .data
        A: .quad 12
        B: .quad 4
        C: .quad 40
        D: .quad 255
        
.section .text
.global _start
_start:
        movq A, %rbx
        movq D, %rdx
        cmp %rbx, %rdx
        jle _end
        addq B, %rbx
        addq C, %rbx
        addq D, %rbx
        movq %rbx, %rdi
        movq $255, %rdx
        cmp %rbx, %rdx
        jge _fim
        movq $255, %rdi
        jmp _fim
        
_end:
        movq $0, %rdi
_fim:
        movq $60, %rax
        syscall

