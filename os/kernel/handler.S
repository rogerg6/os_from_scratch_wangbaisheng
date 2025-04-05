
.text
.code64
.globl timer_handler

.macro SAVE_CONTEXT
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    pushq %rax
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
.endm

.macro RESTORE_CONTEXT
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rax
    pop %rcx
    pop %rdx
    pop %rsi
    pop %rdi
.endm

timer_handler:
    SAVE_CONTEXT

    mov $0x3f8, %dx
    mov $'Z', %al
    out %al, %dx

    mov $0x20, %al
    outb %al, $0x20         # 给8259A发送EOI

    call do_timer

    RESTORE_CONTEXT

    iretq