
c-math.o:	file format mach-o 64-bit x86-64

Disassembly of section __TEXT,__text:

0000000000000000 <_add>:
       0: 55                           	pushq	%rbp
       1: 48 89 e5                     	movq	%rsp, %rbp
       4: 89 7d fc                     	movl	%edi, -4(%rbp)
       7: 89 75 f8                     	movl	%esi, -8(%rbp)
       a: 8b 45 fc                     	movl	-4(%rbp), %eax
       d: 03 45 f8                     	addl	-8(%rbp), %eax
      10: 5d                           	popq	%rbp
      11: c3                           	retq
