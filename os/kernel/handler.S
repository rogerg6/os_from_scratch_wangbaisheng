
.text
.code64
.globl timer_handler
.globl pf_handler
.globl system_call
.globl kb_handler

# 有参宏
.macro SAVE_CONTEXT save_rax=1
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    .if \save_rax
    pushq %rax
    .endif
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
.endm

.macro RESTORE_CONTEXT rstore_rax=1
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    .if \rstore_rax
    pop %rax
    .endif
    pop %rcx
    pop %rdx
    pop %rsi
    pop %rdi
.endm

system_call:
    mov %rsp, tss + 20
    mov tss + 4, %rsp

    pushq tss + 20
    SAVE_CONTEXT 0

    call *syscall_table(, %rax, 8)      # *代表跳转到syscall_table中的地址

    RESTORE_CONTEXT 0
    pop %rsp

    sysretq

timer_handler:
    SAVE_CONTEXT

    mov $0x20, %al
    outb %al, $0x20         # 给8259A发送EOI

    call do_timer

    RESTORE_CONTEXT

    iretq

pf_handler:
    SAVE_CONTEXT

    mov %cr2, %rdi
    call do_page_fault

    RESTORE_CONTEXT
    add $8, %rsp                # 跳过栈中的错误码

    iretq

kb_handler:
    SAVE_CONTEXT

    mov $0x20, %al
    outb %al, $0x20         # 给8259A发送EOI

    call process_kb

    RESTORE_CONTEXT

    iretq

