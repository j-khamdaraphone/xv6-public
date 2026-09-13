.code16
.globl start
start:
movb $0x0e, %ah
movw $hello, %si
movb $0,    %bh
movb $7,    %bl

loop:
movb (%si), %al
cmpb $0, %al
je stop
int $0x10
incw %si
jmp loop

stop:
jmp stop

hello:
.string "Hello World!"

.org 0x1fe
.word 0xAA55
