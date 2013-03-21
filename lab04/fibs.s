.file "fibs.s"					# Linker stuff (you don't need to worry about this)
.text

##################
# fibs_recursive #
##################

.globl fibs_recursive			# Linker stuff
.type	fibs_recursive, @function

fibs_recursive:					# unsigned int fibs_recursive(unsigned int n) {
	# YOUR CODE HERE			#
	pushl %ebp
	movl  %esp, %ebp
	pushl %ebx		## save the callee register, save locally
	pushl %esi
	pushl %edi
	movl 8(%ebp), %ebx	## 8(%ebp) is always the function parameter	
	cmpl $0, %ebx
	je	.Lbase
	cmpl $1, %ebx	
	je	.Lbase
	subl $1, %ebx	
	pushl %ebx		## pushl $para
	call fibs_recursive	## call  func
	movl %eax, %esi		## After the function called, return value will be saved in eax
	subl $1, %ebx		
	pushl %ebx	
	call fibs_recursive
	movl %eax, %edi
	movl %esi, %eax
	addl %edi, %eax 
	jmp .L

.Lbase:
	movl %ebx, %eax		
	movl -4(%ebp), %ebx	## restore ebx, esi, edi after mess. It's kind of a convention
	movl -8(%ebp), %esi	
	movl -12(%ebp), %edi
	leave
	ret							#

.L:
	movl -4(%ebp), %ebx
	movl -8(%ebp), %esi
	movl -12(%ebp), %edi
	leave
	ret
						# }

.size	fibs_recursive, .-fibs_recursive  # Linker stuff

.section	.note.GNU-stack,"",@progbits
