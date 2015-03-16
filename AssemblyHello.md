#Hello World em ASM

Exemplo de um programa 'Hello World' em assembly, numa arquitetura x86 de 32bits

na plataforma Linux, utilizaremos as syscalls do kernel, write e exit.

```
#Exemplo de "alo mundo" em assembly 32bits, para linux 

#por 

#m0nad /at/ email.com

.data

  str: .string "Alo Mundo\n"

.text

.globl _start

_start:
  mov $0x4, %eax  #numero da syscall write 

  mov $0x1, %ebx  #stdout em ebx

  mov $str, %ecx  #end da str para ecx

  mov $0xa, %edx  #tamanho da string em edx

  int $0x80       #chama o kernel

  mov $0x1, %eax  #syscall exit

  xor %ebx, %ebx  #zera ebx, exit(0);

  int $0x80       #chama o kernel

```

$ as -o asm\_alo\_mundo\_32\_linux.o asm\_alo\_mundo\_32\_linux.s

$ ld asm\_alo\_mundo\_32\_linux.o -o asm\_alo\_mundo\_32\_linux

$ ./asm\_alo\_mundo\_32\_linux

Alo Mundo

$