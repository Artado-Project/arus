MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top

	extern kernel_main
	call kernel_main

   cli
.hang:	hlt
	jmp .hang
.end:

global gdt_flush

gdt_flush:
   mov eax, [esp+4]
   lgdt [eax]

   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush
.flush:
   ret

global idt_flush

idt_flush:
   mov eax, [esp+4]
   lidt [eax]
   ret

%include "interrupt.asm"

%include "irq.asm"