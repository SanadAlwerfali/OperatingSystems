
cpp-math.o:	file format mach-o 64-bit x86-64

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
      12: 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00    	nopw	%cs:(%rax,%rax)

0000000000000020 <__Z3addff>:
      20: 55                           	pushq	%rbp
      21: 48 89 e5                     	movq	%rsp, %rbp
      24: f3 0f 11 45 fc               	movss	%xmm0, -4(%rbp)
      29: f3 0f 11 4d f8               	movss	%xmm1, -8(%rbp)
      2e: f3 0f 10 45 fc               	movss	-4(%rbp), %xmm0         ## xmm0 = mem[0],zero,zero,zero
      33: f3 0f 58 45 f8               	addss	-8(%rbp), %xmm0
      38: 5d                           	popq	%rbp
      39: c3                           	retq
