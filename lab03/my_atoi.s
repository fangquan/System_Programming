	.file	"my_atoi.c"
	.text
.globl my_atoi
	.type	my_atoi, @function
my_atoi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
##############################
# DON'T EDIT ABOVE THIS LINE #
##############################
##########################################################################
# atoi                                                                   #
# 8(%ebp) currently holds a pointer to the array of characters (string). #
# Make sure your return value is in the %eax register at the end!        #
##########################################################################

# Write your code here...
	
	movl $0	, %eax
	movl 8(%ebp) ,	%ecx	## address has to be 4 bytes
				## but the contents it extract is one byte
.L2:	
	movzbl  (%ecx)  ,%edx	## forcely take 1 byte, and extend it to 4 bytes.
	cmpl  $48	,%edx	## set the condition codes if %edx less than 48
	jl .L3
	cmpl  $57	,%edx	## set the condition codes if %edx larger than 57	
	jg .L3

	subl  $48       ,%edx
	imull $10       ,%eax
	addl  %edx	,%eax	
	incl  %ecx
		
	jmp .L2

.L3:	
	

# keep looping, when input is between 48 and 57

#Each ASCII char is 1 byte long. How to deal with the 1 byte operation ???
#I need to deal with a few things: (1) increment pointer address; (2) loop. 

##############################
# DON'T EDIT BELOW THIS LINE #
##############################
	movl	-12(%ebp), %esi
	movl	-8(%ebp), %edi
	movl	-4(%ebp), %ebx
	leave
	ret
	.size	my_atoi, .-my_atoi
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
	.section	.note.GNU-stack,"",@progbits
