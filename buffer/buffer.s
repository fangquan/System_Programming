
buffer:     file format elf32-i386


Disassembly of section .init:

08048858 <_init>:
 8048858:	55                   	push   %ebp
 8048859:	89 e5                	mov    %esp,%ebp
 804885b:	53                   	push   %ebx
 804885c:	83 ec 04             	sub    $0x4,%esp
 804885f:	e8 00 00 00 00       	call   8048864 <_init+0xc>
 8048864:	5b                   	pop    %ebx
 8048865:	81 c3 84 28 00 00    	add    $0x2884,%ebx
 804886b:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 8048871:	85 d2                	test   %edx,%edx
 8048873:	74 05                	je     804887a <_init+0x22>
 8048875:	e8 9e 00 00 00       	call   8048918 <__gmon_start__@plt>
 804887a:	e8 d1 02 00 00       	call   8048b50 <frame_dummy>
 804887f:	e8 ec 16 00 00       	call   8049f70 <__do_global_ctors_aux>
 8048884:	58                   	pop    %eax
 8048885:	5b                   	pop    %ebx
 8048886:	c9                   	leave 
 8048887:	c3                   	ret    

Disassembly of section .plt:

08048888 <__errno_location@plt-0x10>:
 8048888:	ff 35 ec b0 04 08    	pushl  0x804b0ec
 804888e:	ff 25 f0 b0 04 08    	jmp    *0x804b0f0
 8048894:	00 00                	add    %al,(%eax)
	...

08048898 <__errno_location@plt>:
 8048898:	ff 25 f4 b0 04 08    	jmp    *0x804b0f4
 804889e:	68 00 00 00 00       	push   $0x0
 80488a3:	e9 e0 ff ff ff       	jmp    8048888 <_init+0x30>

080488a8 <sprintf@plt>:
 80488a8:	ff 25 f8 b0 04 08    	jmp    *0x804b0f8
 80488ae:	68 08 00 00 00       	push   $0x8
 80488b3:	e9 d0 ff ff ff       	jmp    8048888 <_init+0x30>

080488b8 <srand@plt>:
 80488b8:	ff 25 fc b0 04 08    	jmp    *0x804b0fc
 80488be:	68 10 00 00 00       	push   $0x10
 80488c3:	e9 c0 ff ff ff       	jmp    8048888 <_init+0x30>

080488c8 <connect@plt>:
 80488c8:	ff 25 00 b1 04 08    	jmp    *0x804b100
 80488ce:	68 18 00 00 00       	push   $0x18
 80488d3:	e9 b0 ff ff ff       	jmp    8048888 <_init+0x30>

080488d8 <mmap@plt>:
 80488d8:	ff 25 04 b1 04 08    	jmp    *0x804b104
 80488de:	68 20 00 00 00       	push   $0x20
 80488e3:	e9 a0 ff ff ff       	jmp    8048888 <_init+0x30>

080488e8 <getpid@plt>:
 80488e8:	ff 25 08 b1 04 08    	jmp    *0x804b108
 80488ee:	68 28 00 00 00       	push   $0x28
 80488f3:	e9 90 ff ff ff       	jmp    8048888 <_init+0x30>

080488f8 <random@plt>:
 80488f8:	ff 25 0c b1 04 08    	jmp    *0x804b10c
 80488fe:	68 30 00 00 00       	push   $0x30
 8048903:	e9 80 ff ff ff       	jmp    8048888 <_init+0x30>

08048908 <signal@plt>:
 8048908:	ff 25 10 b1 04 08    	jmp    *0x804b110
 804890e:	68 38 00 00 00       	push   $0x38
 8048913:	e9 70 ff ff ff       	jmp    8048888 <_init+0x30>

08048918 <__gmon_start__@plt>:
 8048918:	ff 25 14 b1 04 08    	jmp    *0x804b114
 804891e:	68 40 00 00 00       	push   $0x40
 8048923:	e9 60 ff ff ff       	jmp    8048888 <_init+0x30>

08048928 <__isoc99_sscanf@plt>:
 8048928:	ff 25 18 b1 04 08    	jmp    *0x804b118
 804892e:	68 48 00 00 00       	push   $0x48
 8048933:	e9 50 ff ff ff       	jmp    8048888 <_init+0x30>

08048938 <calloc@plt>:
 8048938:	ff 25 1c b1 04 08    	jmp    *0x804b11c
 804893e:	68 50 00 00 00       	push   $0x50
 8048943:	e9 40 ff ff ff       	jmp    8048888 <_init+0x30>

08048948 <write@plt>:
 8048948:	ff 25 20 b1 04 08    	jmp    *0x804b120
 804894e:	68 58 00 00 00       	push   $0x58
 8048953:	e9 30 ff ff ff       	jmp    8048888 <_init+0x30>

08048958 <memset@plt>:
 8048958:	ff 25 24 b1 04 08    	jmp    *0x804b124
 804895e:	68 60 00 00 00       	push   $0x60
 8048963:	e9 20 ff ff ff       	jmp    8048888 <_init+0x30>

08048968 <__libc_start_main@plt>:
 8048968:	ff 25 28 b1 04 08    	jmp    *0x804b128
 804896e:	68 68 00 00 00       	push   $0x68
 8048973:	e9 10 ff ff ff       	jmp    8048888 <_init+0x30>

08048978 <_IO_getc@plt>:
 8048978:	ff 25 2c b1 04 08    	jmp    *0x804b12c
 804897e:	68 70 00 00 00       	push   $0x70
 8048983:	e9 00 ff ff ff       	jmp    8048888 <_init+0x30>

08048988 <read@plt>:
 8048988:	ff 25 30 b1 04 08    	jmp    *0x804b130
 804898e:	68 78 00 00 00       	push   $0x78
 8048993:	e9 f0 fe ff ff       	jmp    8048888 <_init+0x30>

08048998 <socket@plt>:
 8048998:	ff 25 34 b1 04 08    	jmp    *0x804b134
 804899e:	68 80 00 00 00       	push   $0x80
 80489a3:	e9 e0 fe ff ff       	jmp    8048888 <_init+0x30>

080489a8 <bcopy@plt>:
 80489a8:	ff 25 38 b1 04 08    	jmp    *0x804b138
 80489ae:	68 88 00 00 00       	push   $0x88
 80489b3:	e9 d0 fe ff ff       	jmp    8048888 <_init+0x30>

080489b8 <getopt@plt>:
 80489b8:	ff 25 3c b1 04 08    	jmp    *0x804b13c
 80489be:	68 90 00 00 00       	push   $0x90
 80489c3:	e9 c0 fe ff ff       	jmp    8048888 <_init+0x30>

080489c8 <memcpy@plt>:
 80489c8:	ff 25 40 b1 04 08    	jmp    *0x804b140
 80489ce:	68 98 00 00 00       	push   $0x98
 80489d3:	e9 b0 fe ff ff       	jmp    8048888 <_init+0x30>

080489d8 <alarm@plt>:
 80489d8:	ff 25 44 b1 04 08    	jmp    *0x804b144
 80489de:	68 a0 00 00 00       	push   $0xa0
 80489e3:	e9 a0 fe ff ff       	jmp    8048888 <_init+0x30>

080489e8 <strcpy@plt>:
 80489e8:	ff 25 48 b1 04 08    	jmp    *0x804b148
 80489ee:	68 a8 00 00 00       	push   $0xa8
 80489f3:	e9 90 fe ff ff       	jmp    8048888 <_init+0x30>

080489f8 <printf@plt>:
 80489f8:	ff 25 4c b1 04 08    	jmp    *0x804b14c
 80489fe:	68 b0 00 00 00       	push   $0xb0
 8048a03:	e9 80 fe ff ff       	jmp    8048888 <_init+0x30>

08048a08 <strcasecmp@plt>:
 8048a08:	ff 25 50 b1 04 08    	jmp    *0x804b150
 8048a0e:	68 b8 00 00 00       	push   $0xb8
 8048a13:	e9 70 fe ff ff       	jmp    8048888 <_init+0x30>

08048a18 <srandom@plt>:
 8048a18:	ff 25 54 b1 04 08    	jmp    *0x804b154
 8048a1e:	68 c0 00 00 00       	push   $0xc0
 8048a23:	e9 60 fe ff ff       	jmp    8048888 <_init+0x30>

08048a28 <close@plt>:
 8048a28:	ff 25 58 b1 04 08    	jmp    *0x804b158
 8048a2e:	68 c8 00 00 00       	push   $0xc8
 8048a33:	e9 50 fe ff ff       	jmp    8048888 <_init+0x30>

08048a38 <fwrite@plt>:
 8048a38:	ff 25 5c b1 04 08    	jmp    *0x804b15c
 8048a3e:	68 d0 00 00 00       	push   $0xd0
 8048a43:	e9 40 fe ff ff       	jmp    8048888 <_init+0x30>

08048a48 <gethostname@plt>:
 8048a48:	ff 25 60 b1 04 08    	jmp    *0x804b160
 8048a4e:	68 d8 00 00 00       	push   $0xd8
 8048a53:	e9 30 fe ff ff       	jmp    8048888 <_init+0x30>

08048a58 <puts@plt>:
 8048a58:	ff 25 64 b1 04 08    	jmp    *0x804b164
 8048a5e:	68 e0 00 00 00       	push   $0xe0
 8048a63:	e9 20 fe ff ff       	jmp    8048888 <_init+0x30>

08048a68 <rand@plt>:
 8048a68:	ff 25 68 b1 04 08    	jmp    *0x804b168
 8048a6e:	68 e8 00 00 00       	push   $0xe8
 8048a73:	e9 10 fe ff ff       	jmp    8048888 <_init+0x30>

08048a78 <munmap@plt>:
 8048a78:	ff 25 6c b1 04 08    	jmp    *0x804b16c
 8048a7e:	68 f0 00 00 00       	push   $0xf0
 8048a83:	e9 00 fe ff ff       	jmp    8048888 <_init+0x30>

08048a88 <gethostbyname@plt>:
 8048a88:	ff 25 70 b1 04 08    	jmp    *0x804b170
 8048a8e:	68 f8 00 00 00       	push   $0xf8
 8048a93:	e9 f0 fd ff ff       	jmp    8048888 <_init+0x30>

08048a98 <__strdup@plt>:
 8048a98:	ff 25 74 b1 04 08    	jmp    *0x804b174
 8048a9e:	68 00 01 00 00       	push   $0x100
 8048aa3:	e9 e0 fd ff ff       	jmp    8048888 <_init+0x30>

08048aa8 <exit@plt>:
 8048aa8:	ff 25 78 b1 04 08    	jmp    *0x804b178
 8048aae:	68 08 01 00 00       	push   $0x108
 8048ab3:	e9 d0 fd ff ff       	jmp    8048888 <_init+0x30>

Disassembly of section .text:

08048ac0 <_start>:
 8048ac0:	31 ed                	xor    %ebp,%ebp
 8048ac2:	5e                   	pop    %esi
 8048ac3:	89 e1                	mov    %esp,%ecx
 8048ac5:	83 e4 f0             	and    $0xfffffff0,%esp
 8048ac8:	50                   	push   %eax
 8048ac9:	54                   	push   %esp
 8048aca:	52                   	push   %edx
 8048acb:	68 00 9f 04 08       	push   $0x8049f00
 8048ad0:	68 10 9f 04 08       	push   $0x8049f10
 8048ad5:	51                   	push   %ecx
 8048ad6:	56                   	push   %esi
 8048ad7:	68 4b 8f 04 08       	push   $0x8048f4b
 8048adc:	e8 87 fe ff ff       	call   8048968 <__libc_start_main@plt>
 8048ae1:	f4                   	hlt    
 8048ae2:	90                   	nop
 8048ae3:	90                   	nop
 8048ae4:	90                   	nop
 8048ae5:	90                   	nop
 8048ae6:	90                   	nop
 8048ae7:	90                   	nop
 8048ae8:	90                   	nop
 8048ae9:	90                   	nop
 8048aea:	90                   	nop
 8048aeb:	90                   	nop
 8048aec:	90                   	nop
 8048aed:	90                   	nop
 8048aee:	90                   	nop
 8048aef:	90                   	nop

08048af0 <__do_global_dtors_aux>:
 8048af0:	55                   	push   %ebp
 8048af1:	89 e5                	mov    %esp,%ebp
 8048af3:	53                   	push   %ebx
 8048af4:	83 ec 04             	sub    $0x4,%esp
 8048af7:	80 3d e4 c1 04 08 00 	cmpb   $0x0,0x804c1e4
 8048afe:	75 3f                	jne    8048b3f <__do_global_dtors_aux+0x4f>
 8048b00:	a1 e8 c1 04 08       	mov    0x804c1e8,%eax
 8048b05:	bb 0c b0 04 08       	mov    $0x804b00c,%ebx
 8048b0a:	81 eb 08 b0 04 08    	sub    $0x804b008,%ebx
 8048b10:	c1 fb 02             	sar    $0x2,%ebx
 8048b13:	83 eb 01             	sub    $0x1,%ebx
 8048b16:	39 d8                	cmp    %ebx,%eax
 8048b18:	73 1e                	jae    8048b38 <__do_global_dtors_aux+0x48>
 8048b1a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048b20:	83 c0 01             	add    $0x1,%eax
 8048b23:	a3 e8 c1 04 08       	mov    %eax,0x804c1e8
 8048b28:	ff 14 85 08 b0 04 08 	call   *0x804b008(,%eax,4)
 8048b2f:	a1 e8 c1 04 08       	mov    0x804c1e8,%eax
 8048b34:	39 d8                	cmp    %ebx,%eax
 8048b36:	72 e8                	jb     8048b20 <__do_global_dtors_aux+0x30>
 8048b38:	c6 05 e4 c1 04 08 01 	movb   $0x1,0x804c1e4
 8048b3f:	83 c4 04             	add    $0x4,%esp
 8048b42:	5b                   	pop    %ebx
 8048b43:	5d                   	pop    %ebp
 8048b44:	c3                   	ret    
 8048b45:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048b49:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048b50 <frame_dummy>:
 8048b50:	55                   	push   %ebp
 8048b51:	89 e5                	mov    %esp,%ebp
 8048b53:	83 ec 18             	sub    $0x18,%esp
 8048b56:	a1 10 b0 04 08       	mov    0x804b010,%eax
 8048b5b:	85 c0                	test   %eax,%eax
 8048b5d:	74 12                	je     8048b71 <frame_dummy+0x21>
 8048b5f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048b64:	85 c0                	test   %eax,%eax
 8048b66:	74 09                	je     8048b71 <frame_dummy+0x21>
 8048b68:	c7 04 24 10 b0 04 08 	movl   $0x804b010,(%esp)
 8048b6f:	ff d0                	call   *%eax
 8048b71:	c9                   	leave  
 8048b72:	c3                   	ret    
 8048b73:	90                   	nop
 8048b74:	90                   	nop
 8048b75:	90                   	nop
 8048b76:	90                   	nop
 8048b77:	90                   	nop
 8048b78:	90                   	nop
 8048b79:	90                   	nop
 8048b7a:	90                   	nop
 8048b7b:	90                   	nop
 8048b7c:	90                   	nop
 8048b7d:	90                   	nop
 8048b7e:	90                   	nop
 8048b7f:	90                   	nop

08048b80 <usage>:
 8048b80:	55                   	push   %ebp
 8048b81:	89 e5                	mov    %esp,%ebp
 8048b83:	83 ec 18             	sub    $0x18,%esp
 8048b86:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048b8a:	c7 04 24 c0 9f 04 08 	movl   $0x8049fc0,(%esp)
 8048b91:	e8 62 fe ff ff       	call   80489f8 <printf@plt>
 8048b96:	c7 04 24 de 9f 04 08 	movl   $0x8049fde,(%esp)
 8048b9d:	e8 b6 fe ff ff       	call   8048a58 <puts@plt>
 8048ba2:	c7 04 24 f4 9f 04 08 	movl   $0x8049ff4,(%esp)
 8048ba9:	e8 aa fe ff ff       	call   8048a58 <puts@plt>
 8048bae:	c7 04 24 e0 a0 04 08 	movl   $0x804a0e0,(%esp)
 8048bb5:	e8 9e fe ff ff       	call   8048a58 <puts@plt>
 8048bba:	c7 04 24 1c a1 04 08 	movl   $0x804a11c,(%esp)
 8048bc1:	e8 92 fe ff ff       	call   8048a58 <puts@plt>
 8048bc6:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048bcd:	e8 d6 fe ff ff       	call   8048aa8 <exit@plt>

08048bd2 <illegalhandler>:
 8048bd2:	55                   	push   %ebp
 8048bd3:	89 e5                	mov    %esp,%ebp
 8048bd5:	83 ec 18             	sub    $0x18,%esp
 8048bd8:	c7 04 24 44 a1 04 08 	movl   $0x804a144,(%esp)
 8048bdf:	e8 74 fe ff ff       	call   8048a58 <puts@plt>
 8048be4:	c7 04 24 0d a0 04 08 	movl   $0x804a00d,(%esp)
 8048beb:	e8 68 fe ff ff       	call   8048a58 <puts@plt>
 8048bf0:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048bf7:	e8 ac fe ff ff       	call   8048aa8 <exit@plt>

08048bfc <seghandler>:
 8048bfc:	55                   	push   %ebp
 8048bfd:	89 e5                	mov    %esp,%ebp
 8048bff:	83 ec 18             	sub    $0x18,%esp
 8048c02:	c7 04 24 70 a1 04 08 	movl   $0x804a170,(%esp)
 8048c09:	e8 4a fe ff ff       	call   8048a58 <puts@plt>
 8048c0e:	c7 04 24 0d a0 04 08 	movl   $0x804a00d,(%esp)
 8048c15:	e8 3e fe ff ff       	call   8048a58 <puts@plt>
 8048c1a:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c21:	e8 82 fe ff ff       	call   8048aa8 <exit@plt>

08048c26 <bushandler>:
 8048c26:	55                   	push   %ebp
 8048c27:	89 e5                	mov    %esp,%ebp
 8048c29:	83 ec 18             	sub    $0x18,%esp
 8048c2c:	c7 04 24 98 a1 04 08 	movl   $0x804a198,(%esp)
 8048c33:	e8 20 fe ff ff       	call   8048a58 <puts@plt>
 8048c38:	c7 04 24 0d a0 04 08 	movl   $0x804a00d,(%esp)
 8048c3f:	e8 14 fe ff ff       	call   8048a58 <puts@plt>
 8048c44:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c4b:	e8 58 fe ff ff       	call   8048aa8 <exit@plt>

08048c50 <uniqueval>:
 8048c50:	55                   	push   %ebp
 8048c51:	89 e5                	mov    %esp,%ebp
 8048c53:	83 ec 18             	sub    $0x18,%esp
 8048c56:	e8 8d fc ff ff       	call   80488e8 <getpid@plt>
 8048c5b:	89 04 24             	mov    %eax,(%esp)
 8048c5e:	e8 b5 fd ff ff       	call   8048a18 <srandom@plt>
 8048c63:	e8 90 fc ff ff       	call   80488f8 <random@plt>
 8048c68:	c9                   	leave  
 8048c69:	c3                   	ret    

08048c6a <Gets>:
 8048c6a:	55                   	push   %ebp
 8048c6b:	89 e5                	mov    %esp,%ebp
 8048c6d:	57                   	push   %edi
 8048c6e:	56                   	push   %esi
 8048c6f:	53                   	push   %ebx
 8048c70:	83 ec 2c             	sub    $0x2c,%esp
 8048c73:	c7 05 08 c2 04 08 00 	movl   $0x0,0x804c208
 8048c7a:	00 00 00 
 8048c7d:	8b 5d 08             	mov    0x8(%ebp),%ebx
 8048c80:	be 54 a3 04 08       	mov    $0x804a354,%esi
 8048c85:	eb 4d                	jmp    8048cd4 <Gets+0x6a>
 8048c87:	88 45 d8             	mov    %al,-0x28(%ebp)
 8048c8a:	88 03                	mov    %al,(%ebx)
 8048c8c:	a1 08 c2 04 08       	mov    0x804c208,%eax
 8048c91:	3d ff 03 00 00       	cmp    $0x3ff,%eax
 8048c96:	7f 39                	jg     8048cd1 <Gets+0x67>
 8048c98:	8d 14 40             	lea    (%eax,%eax,2),%edx
 8048c9b:	0f b6 4d d8          	movzbl -0x28(%ebp),%ecx
 8048c9f:	c0 e9 04             	shr    $0x4,%cl
 8048ca2:	0f be f9             	movsbl %cl,%edi
 8048ca5:	0f b6 3c 3e          	movzbl (%esi,%edi,1),%edi
 8048ca9:	89 f9                	mov    %edi,%ecx
 8048cab:	88 8a 20 c2 04 08    	mov    %cl,0x804c220(%edx)
 8048cb1:	0f b6 4d d8          	movzbl -0x28(%ebp),%ecx
 8048cb5:	83 e1 0f             	and    $0xf,%ecx
 8048cb8:	0f b6 0c 0e          	movzbl (%esi,%ecx,1),%ecx
 8048cbc:	88 8a 21 c2 04 08    	mov    %cl,0x804c221(%edx)
 8048cc2:	c6 82 22 c2 04 08 20 	movb   $0x20,0x804c222(%edx)
 8048cc9:	83 c0 01             	add    $0x1,%eax
 8048ccc:	a3 08 c2 04 08       	mov    %eax,0x804c208
 8048cd1:	83 c3 01             	add    $0x1,%ebx
 8048cd4:	a1 f8 c1 04 08       	mov    0x804c1f8,%eax
 8048cd9:	89 04 24             	mov    %eax,(%esp)
 8048cdc:	e8 97 fc ff ff       	call   8048978 <_IO_getc@plt>
 8048ce1:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048ce4:	74 05                	je     8048ceb <Gets+0x81>
 8048ce6:	83 f8 0a             	cmp    $0xa,%eax
 8048ce9:	75 9c                	jne    8048c87 <Gets+0x1d>
 8048ceb:	c6 03 00             	movb   $0x0,(%ebx)
 8048cee:	a1 08 c2 04 08       	mov    0x804c208,%eax
 8048cf3:	c6 84 40 20 c2 04 08 	movb   $0x0,0x804c220(%eax,%eax,2)
 8048cfa:	00 
 8048cfb:	8b 45 08             	mov    0x8(%ebp),%eax
 8048cfe:	83 c4 2c             	add    $0x2c,%esp
 8048d01:	5b                   	pop    %ebx
 8048d02:	5e                   	pop    %esi
 8048d03:	5f                   	pop    %edi
 8048d04:	5d                   	pop    %ebp
 8048d05:	c3                   	ret    

08048d06 <getbufn>:
 8048d06:	55                   	push   %ebp
 8048d07:	89 e5                	mov    %esp,%ebp
 8048d09:	81 ec 18 02 00 00    	sub    $0x218,%esp
 8048d0f:	8d 85 f8 fd ff ff    	lea    -0x208(%ebp),%eax
 8048d15:	89 04 24             	mov    %eax,(%esp)
 8048d18:	e8 4d ff ff ff       	call   8048c6a <Gets>
 8048d1d:	b8 01 00 00 00       	mov    $0x1,%eax
 8048d22:	c9                   	leave  
 8048d23:	c3                   	ret    

08048d24 <getbuf>:
 8048d24:	55                   	push   %ebp
 8048d25:	89 e5                	mov    %esp,%ebp
 8048d27:	83 ec 38             	sub    $0x38,%esp
 8048d2a:	8d 45 d8             	lea    -0x28(%ebp),%eax
 8048d2d:	89 04 24             	mov    %eax,(%esp)	
 8048d30:	e8 35 ff ff ff       	call   8048c6a <Gets>
 8048d35:	b8 01 00 00 00       	mov    $0x1,%eax
 8048d3a:	c9                   	leave  
 8048d3b:	c3                   	ret

08048d3c <testn>:
 8048d3c:	55                   	push   %ebp
 8048d3d:	89 e5                	mov    %esp,%ebp
 8048d3f:	83 ec 28             	sub    $0x28,%esp
 8048d42:	c7 45 f4 ef be ad de 	movl   $0xdeadbeef,-0xc(%ebp)
 8048d49:	e8 b8 ff ff ff       	call   8048d06 <getbufn>
 8048d4e:	8b 55 f4             	mov    -0xc(%ebp),%edx
 8048d51:	81 fa ef be ad de    	cmp    $0xdeadbeef,%edx
 8048d57:	74 0e                	je     8048d67 <testn+0x2b>
 8048d59:	c7 04 24 b8 a1 04 08 	movl   $0x804a1b8,(%esp)
 8048d60:	e8 f3 fc ff ff       	call   8048a58 <puts@plt>
 8048d65:	eb 36                	jmp    8048d9d <testn+0x61>
 8048d67:	3b 05 fc c1 04 08    	cmp    0x804c1fc,%eax
 8048d6d:	75 1e                	jne    8048d8d <testn+0x51>
 8048d6f:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048d73:	c7 04 24 e4 a1 04 08 	movl   $0x804a1e4,(%esp)
 8048d7a:	e8 79 fc ff ff       	call   80489f8 <printf@plt>
 8048d7f:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
 8048d86:	e8 85 04 00 00       	call   8049210 <validate>
 8048d8b:	eb 10                	jmp    8048d9d <testn+0x61>
 8048d8d:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048d91:	c7 04 24 23 a0 04 08 	movl   $0x804a023,(%esp)
 8048d98:	e8 5b fc ff ff       	call   80489f8 <printf@plt>
 8048d9d:	c9                   	leave  
 8048d9e:	c3                   	ret    

08048d9f <test>:
 8048d9f:	55                   	push   %ebp
 8048da0:	89 e5                	mov    %esp,%ebp
 8048da2:	53                   	push   %ebx
 8048da3:	83 ec 24             	sub    $0x24,%esp
 8048da6:	e8 a5 fe ff ff       	call   8048c50 <uniqueval>
 8048dab:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048dae:	e8 71 ff ff ff       	call   8048d24 <getbuf>
 8048db3:	89 c3                	mov    %eax,%ebx
 8048db5:	e8 96 fe ff ff       	call   8048c50 <uniqueval>
 8048dba:	8b 55 f4             	mov    -0xc(%ebp),%edx
 8048dbd:	39 d0                	cmp    %edx,%eax
 8048dbf:	74 0e                	je     8048dcf <test+0x30>
 8048dc1:	c7 04 24 b8 a1 04 08 	movl   $0x804a1b8,(%esp)
 8048dc8:	e8 8b fc ff ff       	call   8048a58 <puts@plt>
 8048dcd:	eb 36                	jmp    8048e05 <test+0x66>
 8048dcf:	3b 1d fc c1 04 08    	cmp    0x804c1fc,%ebx
 8048dd5:	75 1e                	jne    8048df5 <test+0x56>
 8048dd7:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8048ddb:	c7 04 24 40 a0 04 08 	movl   $0x804a040,(%esp)
 8048de2:	e8 11 fc ff ff       	call   80489f8 <printf@plt>
 8048de7:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
 8048dee:	e8 1d 04 00 00       	call   8049210 <validate>
 8048df3:	eb 10                	jmp    8048e05 <test+0x66>
 8048df5:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8048df9:	c7 04 24 5d a0 04 08 	movl   $0x804a05d,(%esp)
 8048e00:	e8 f3 fb ff ff       	call   80489f8 <printf@plt>
 8048e05:	83 c4 24             	add    $0x24,%esp
 8048e08:	5b                   	pop    %ebx
 8048e09:	5d                   	pop    %ebp
 8048e0a:	c3                   	ret    

08048e0b <launch>:
 8048e0b:	55                   	push   %ebp
 8048e0c:	89 e5                	mov    %esp,%ebp
 8048e0e:	53                   	push   %ebx
 8048e0f:	83 ec 54             	sub    $0x54,%esp
 8048e12:	89 c3                	mov    %eax,%ebx
 8048e14:	8d 45 b8             	lea    -0x48(%ebp),%eax
 8048e17:	25 f0 3f 00 00       	and    $0x3ff0,%eax
 8048e1c:	8d 54 10 1e          	lea    0x1e(%eax,%edx,1),%edx
 8048e20:	83 e2 f0             	and    $0xfffffff0,%edx
 8048e23:	29 d4                	sub    %edx,%esp
 8048e25:	8d 54 24 1b          	lea    0x1b(%esp),%edx
 8048e29:	83 e2 f0             	and    $0xfffffff0,%edx
 8048e2c:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048e30:	c7 44 24 04 f4 00 00 	movl   $0xf4,0x4(%esp)
 8048e37:	00 
 8048e38:	89 14 24             	mov    %edx,(%esp)
 8048e3b:	e8 18 fb ff ff       	call   8048958 <memset@plt>
 8048e40:	c7 04 24 79 a0 04 08 	movl   $0x804a079,(%esp)
 8048e47:	e8 ac fb ff ff       	call   80489f8 <printf@plt>
 8048e4c:	85 db                	test   %ebx,%ebx
 8048e4e:	74 07                	je     8048e57 <launch+0x4c>
 8048e50:	e8 e7 fe ff ff       	call   8048d3c <testn>
 8048e55:	eb 06                	jmp    8048e5d <launch+0x52>
 8048e57:	90                   	nop
 8048e58:	e8 42 ff ff ff       	call   8048d9f <test>
 8048e5d:	83 3d 00 c2 04 08 00 	cmpl   $0x0,0x804c200
 8048e64:	75 16                	jne    8048e7c <launch+0x71>
 8048e66:	c7 04 24 0d a0 04 08 	movl   $0x804a00d,(%esp)
 8048e6d:	e8 e6 fb ff ff       	call   8048a58 <puts@plt>
 8048e72:	c7 05 00 c2 04 08 00 	movl   $0x0,0x804c200
 8048e79:	00 00 00 
 8048e7c:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 8048e7f:	c9                   	leave  
 8048e80:	c3                   	ret    

08048e81 <launcher>:
 8048e81:	55                   	push   %ebp
 8048e82:	89 e5                	mov    %esp,%ebp
 8048e84:	83 ec 28             	sub    $0x28,%esp
 8048e87:	8b 45 08             	mov    0x8(%ebp),%eax
 8048e8a:	a3 0c c2 04 08       	mov    %eax,0x804c20c
 8048e8f:	8b 45 0c             	mov    0xc(%ebp),%eax
 8048e92:	a3 10 c2 04 08       	mov    %eax,0x804c210
 8048e97:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
 8048e9e:	00 
 8048e9f:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 8048ea6:	00 
 8048ea7:	c7 44 24 0c 32 01 00 	movl   $0x132,0xc(%esp)
 8048eae:	00 
 8048eaf:	c7 44 24 08 07 00 00 	movl   $0x7,0x8(%esp)
 8048eb6:	00 
 8048eb7:	c7 44 24 04 00 00 10 	movl   $0x100000,0x4(%esp)
 8048ebe:	00 
 8048ebf:	c7 04 24 00 60 58 55 	movl   $0x55586000,(%esp)
 8048ec6:	e8 0d fa ff ff       	call   80488d8 <mmap@plt>
 8048ecb:	3d 00 60 58 55       	cmp    $0x55586000,%eax
 8048ed0:	74 31                	je     8048f03 <launcher+0x82>
 8048ed2:	a1 c0 c1 04 08       	mov    0x804c1c0,%eax
 8048ed7:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048edb:	c7 44 24 08 47 00 00 	movl   $0x47,0x8(%esp)
 8048ee2:	00 
 8048ee3:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8048eea:	00 
 8048eeb:	c7 04 24 04 a2 04 08 	movl   $0x804a204,(%esp)
 8048ef2:	e8 41 fb ff ff       	call   8048a38 <fwrite@plt>
 8048ef7:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048efe:	e8 a5 fb ff ff       	call   8048aa8 <exit@plt>
 8048f03:	c7 05 24 ce 04 08 f8 	movl   $0x55685ff8,0x804ce24
 8048f0a:	5f 68 55 
 8048f0d:	ba f8 5f 68 55       	mov    $0x55685ff8,%edx
 8048f12:	89 e0                	mov    %esp,%eax
 8048f14:	89 d4                	mov    %edx,%esp
 8048f16:	89 c2                	mov    %eax,%edx
 8048f18:	89 15 14 c2 04 08    	mov    %edx,0x804c214
 8048f1e:	8b 15 10 c2 04 08    	mov    0x804c210,%edx
 8048f24:	a1 0c c2 04 08       	mov    0x804c20c,%eax
 8048f29:	e8 dd fe ff ff       	call   8048e0b <launch>
 8048f2e:	a1 14 c2 04 08       	mov    0x804c214,%eax
 8048f33:	89 c4                	mov    %eax,%esp
 8048f35:	c7 44 24 04 00 00 10 	movl   $0x100000,0x4(%esp)
 8048f3c:	00 
 8048f3d:	c7 04 24 00 60 58 55 	movl   $0x55586000,(%esp)
 8048f44:	e8 2f fb ff ff       	call   8048a78 <munmap@plt>
 8048f49:	c9                   	leave  
 8048f4a:	c3                   	ret    

08048f4b <main>:
 8048f4b:	55                   	push   %ebp
 8048f4c:	89 e5                	mov    %esp,%ebp
 8048f4e:	83 e4 f0             	and    $0xfffffff0,%esp
 8048f51:	57                   	push   %edi
 8048f52:	56                   	push   %esi
 8048f53:	53                   	push   %ebx
 8048f54:	83 ec 24             	sub    $0x24,%esp
 8048f57:	8b 75 08             	mov    0x8(%ebp),%esi
 8048f5a:	8b 5d 0c             	mov    0xc(%ebp),%ebx
 8048f5d:	c7 44 24 04 fc 8b 04 	movl   $0x8048bfc,0x4(%esp)
 8048f64:	08 
 8048f65:	c7 04 24 0b 00 00 00 	movl   $0xb,(%esp)
 8048f6c:	e8 97 f9 ff ff       	call   8048908 <signal@plt>
 8048f71:	c7 44 24 04 26 8c 04 	movl   $0x8048c26,0x4(%esp)
 8048f78:	08 
 8048f79:	c7 04 24 07 00 00 00 	movl   $0x7,(%esp)
 8048f80:	e8 83 f9 ff ff       	call   8048908 <signal@plt>
 8048f85:	c7 44 24 04 d2 8b 04 	movl   $0x8048bd2,0x4(%esp)
 8048f8c:	08 
 8048f8d:	c7 04 24 04 00 00 00 	movl   $0x4,(%esp)
 8048f94:	e8 6f f9 ff ff       	call   8048908 <signal@plt>
 8048f99:	a1 c4 c1 04 08       	mov    0x804c1c4,%eax
 8048f9e:	a3 f8 c1 04 08       	mov    %eax,0x804c1f8
 8048fa3:	c7 44 24 1c 01 00 00 	movl   $0x1,0x1c(%esp)
 8048faa:	00 
 8048fab:	c7 44 24 18 00 00 00 	movl   $0x0,0x18(%esp)
 8048fb2:	00 
 8048fb3:	bf 18 a3 04 08       	mov    $0x804a318,%edi
 8048fb8:	eb 74                	jmp    804902e <main+0xe3>
 8048fba:	83 e8 67             	sub    $0x67,%eax
 8048fbd:	3c 0e                	cmp    $0xe,%al
 8048fbf:	77 66                	ja     8049027 <main+0xdc>
 8048fc1:	0f b6 c0             	movzbl %al,%eax
 8048fc4:	ff 24 87             	jmp    *(%edi,%eax,4)
 8048fc7:	c7 44 24 1c 05 00 00 	movl   $0x5,0x1c(%esp)
 8048fce:	00 
 8048fcf:	c7 44 24 18 01 00 00 	movl   $0x1,0x18(%esp)
 8048fd6:	00 
 8048fd7:	eb 55                	jmp    804902e <main+0xe3>
 8048fd9:	8b 03                	mov    (%ebx),%eax
 8048fdb:	e8 a0 fb ff ff       	call   8048b80 <usage>
 8048fe0:	eb 4c                	jmp    804902e <main+0xe3>
 8048fe2:	a1 e0 c1 04 08       	mov    0x804c1e0,%eax
 8048fe7:	89 04 24             	mov    %eax,(%esp)
 8048fea:	e8 a9 fa ff ff       	call   8048a98 <__strdup@plt>
 8048fef:	a3 ec c1 04 08       	mov    %eax,0x804c1ec
 8048ff4:	89 04 24             	mov    %eax,(%esp)
 8048ff7:	e8 cd 0e 00 00       	call   8049ec9 <gencookie>
 8048ffc:	a3 fc c1 04 08       	mov    %eax,0x804c1fc
 8049001:	eb 2b                	jmp    804902e <main+0xe3>
 8049003:	c7 04 24 4c a2 04 08 	movl   $0x804a24c,(%esp)
 804900a:	e8 49 fa ff ff       	call   8048a58 <puts@plt>
 804900f:	c7 05 f0 c1 04 08 00 	movl   $0x0,0x804c1f0
 8049016:	00 00 00 
 8049019:	eb 13                	jmp    804902e <main+0xe3>
 804901b:	c7 05 f4 c1 04 08 01 	movl   $0x1,0x804c1f4
 8049022:	00 00 00 
 8049025:	eb 07                	jmp    804902e <main+0xe3>
 8049027:	8b 03                	mov    (%ebx),%eax
 8049029:	e8 52 fb ff ff       	call   8048b80 <usage>
 804902e:	c7 44 24 08 86 a0 04 	movl   $0x804a086,0x8(%esp)
 8049035:	08 
 8049036:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 804903a:	89 34 24             	mov    %esi,(%esp)
 804903d:	e8 76 f9 ff ff       	call   80489b8 <getopt@plt>
 8049042:	3c ff                	cmp    $0xff,%al
 8049044:	0f 85 70 ff ff ff    	jne    8048fba <main+0x6f>
 804904a:	83 3d ec c1 04 08 00 	cmpl   $0x0,0x804c1ec
 8049051:	75 19                	jne    804906c <main+0x121>
 8049053:	8b 03                	mov    (%ebx),%eax
 8049055:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049059:	c7 04 24 74 a2 04 08 	movl   $0x804a274,(%esp)
 8049060:	e8 93 f9 ff ff       	call   80489f8 <printf@plt>
 8049065:	8b 03                	mov    (%ebx),%eax
 8049067:	e8 14 fb ff ff       	call   8048b80 <usage>
 804906c:	e8 e2 02 00 00       	call   8049353 <initialize_bomb>
 8049071:	a1 ec c1 04 08       	mov    0x804c1ec,%eax
 8049076:	89 44 24 04          	mov    %eax,0x4(%esp)
 804907a:	c7 04 24 8d a0 04 08 	movl   $0x804a08d,(%esp)
 8049081:	e8 72 f9 ff ff       	call   80489f8 <printf@plt>
 8049086:	a1 fc c1 04 08       	mov    0x804c1fc,%eax
 804908b:	89 44 24 04          	mov    %eax,0x4(%esp)
 804908f:	c7 04 24 99 a0 04 08 	movl   $0x804a099,(%esp)
 8049096:	e8 5d f9 ff ff       	call   80489f8 <printf@plt>
 804909b:	a1 fc c1 04 08       	mov    0x804c1fc,%eax
 80490a0:	89 04 24             	mov    %eax,(%esp)
 80490a3:	e8 70 f9 ff ff       	call   8048a18 <srandom@plt>
 80490a8:	e8 4b f8 ff ff       	call   80488f8 <random@plt>
 80490ad:	89 c7                	mov    %eax,%edi
 80490af:	81 e7 f0 0f 00 00    	and    $0xff0,%edi
 80490b5:	81 c7 00 01 00 00    	add    $0x100,%edi
 80490bb:	c7 44 24 04 04 00 00 	movl   $0x4,0x4(%esp)
 80490c2:	00 
 80490c3:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 80490c7:	89 04 24             	mov    %eax,(%esp)
 80490ca:	e8 69 f8 ff ff       	call   8048938 <calloc@plt>
 80490cf:	89 c6                	mov    %eax,%esi
 80490d1:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
 80490d7:	83 7c 24 1c 01       	cmpl   $0x1,0x1c(%esp)
 80490dc:	7e 2c                	jle    804910a <main+0x1bf>
 80490de:	bb 01 00 00 00       	mov    $0x1,%ebx
 80490e3:	89 7c 24 14          	mov    %edi,0x14(%esp)
 80490e7:	8b 7c 24 1c          	mov    0x1c(%esp),%edi
 80490eb:	e8 08 f8 ff ff       	call   80488f8 <random@plt>
 80490f0:	25 f0 00 00 00       	and    $0xf0,%eax
 80490f5:	ba 80 00 00 00       	mov    $0x80,%edx
 80490fa:	29 c2                	sub    %eax,%edx
 80490fc:	89 14 9e             	mov    %edx,(%esi,%ebx,4)
 80490ff:	83 c3 01             	add    $0x1,%ebx
 8049102:	39 fb                	cmp    %edi,%ebx
 8049104:	7c e5                	jl     80490eb <main+0x1a0>
 8049106:	8b 7c 24 14          	mov    0x14(%esp),%edi
 804910a:	83 7c 24 1c 00       	cmpl   $0x0,0x1c(%esp)
 804910f:	7e 23                	jle    8049134 <main+0x1e9>
 8049111:	bb 00 00 00 00       	mov    $0x0,%ebx
 8049116:	89 f8                	mov    %edi,%eax
 8049118:	03 04 9e             	add    (%esi,%ebx,4),%eax
 804911b:	89 44 24 04          	mov    %eax,0x4(%esp)
 804911f:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049123:	89 04 24             	mov    %eax,(%esp)
 8049126:	e8 56 fd ff ff       	call   8048e81 <launcher>
 804912b:	83 c3 01             	add    $0x1,%ebx
 804912e:	3b 5c 24 1c          	cmp    0x1c(%esp),%ebx
 8049132:	7c e2                	jl     8049116 <main+0x1cb>
 8049134:	b8 00 00 00 00       	mov    $0x0,%eax
 8049139:	83 c4 24             	add    $0x24,%esp
 804913c:	5b                   	pop    %ebx
 804913d:	5e                   	pop    %esi
 804913e:	5f                   	pop    %edi
 804913f:	89 ec                	mov    %ebp,%esp
 8049141:	5d                   	pop    %ebp
 8049142:	c3                   	ret    

08049143 <happy>:

 8049143:	55                   	push   %ebp
 8049144:	89 e5                	mov    %esp,%ebp
 8049146:	83 ec 18             	sub    $0x18,%esp
 8049149:	a1 04 c2 04 08       	mov    0x804c204,%eax
 804914e:	3b 05 fc c1 04 08    	cmp    0x804c1fc,%eax
 8049154:	75 1e                	jne    8049174 <happy+0x31>
 8049156:	89 44 24 04          	mov    %eax,0x4(%esp)
 804915a:	c7 04 24 a0 a2 04 08 	movl   $0x804a2a0,(%esp)
 8049161:	e8 92 f8 ff ff       	call   80489f8 <printf@plt>
 8049166:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 804916d:	e8 9e 00 00 00       	call   8049210 <validate>
 8049172:	eb 10                	jmp    8049184 <happy+0x41>
 8049174:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049178:	c7 04 24 a7 a0 04 08 	movl   $0x804a0a7,(%esp)
 804917f:	e8 74 f8 ff ff       	call   80489f8 <printf@plt>
 8049184:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 804918b:	e8 18 f9 ff ff       	call   8048aa8 <exit@plt>

08049190 <sleepy>:
 8049190:	55                   	push   %ebp
 8049191:	89 e5                	mov    %esp,%ebp
 8049193:	83 ec 18             	sub    $0x18,%esp
 8049196:	8b 45 08             	mov    0x8(%ebp),%eax
 8049199:	3b 05 fc c1 04 08    	cmp    0x804c1fc,%eax
 804919f:	75 1e                	jne    80491bf <sleepy+0x2f>
 80491a1:	89 44 24 04          	mov    %eax,0x4(%esp)
 80491a5:	c7 04 24 c4 a2 04 08 	movl   $0x804a2c4,(%esp)
 80491ac:	e8 47 f8 ff ff       	call   80489f8 <printf@plt>
 80491b1:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 80491b8:	e8 53 00 00 00       	call   8049210 <validate>
 80491bd:	eb 10                	jmp    80491cf <sleepy+0x3f>
 80491bf:	89 44 24 04          	mov    %eax,0x4(%esp)
 80491c3:	c7 04 24 ec a2 04 08 	movl   $0x804a2ec,(%esp)
 80491ca:	e8 29 f8 ff ff       	call   80489f8 <printf@plt>
 80491cf:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 80491d6:	e8 cd f8 ff ff       	call   8048aa8 <exit@plt>

080491db <dopey>:
 80491db:	55                   	push   %ebp
 80491dc:	89 e5                	mov    %esp,%ebp
 80491de:	83 ec 18             	sub    $0x18,%esp
 80491e1:	c7 04 24 c4 a0 04 08 	movl   $0x804a0c4,(%esp)
 80491e8:	e8 6b f8 ff ff       	call   8048a58 <puts@plt>
 80491ed:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 80491f4:	e8 17 00 00 00       	call   8049210 <validate>
 80491f9:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8049200:	e8 a3 f8 ff ff       	call   8048aa8 <exit@plt>
 8049205:	90                   	nop
 8049206:	90                   	nop
 8049207:	90                   	nop
 8049208:	90                   	nop
 8049209:	90                   	nop
 804920a:	90                   	nop
 804920b:	90                   	nop
 804920c:	90                   	nop
 804920d:	90                   	nop
 804920e:	90                   	nop
 804920f:	90                   	nop

08049210 <validate>:
 8049210:	55                   	push   %ebp
 8049211:	89 e5                	mov    %esp,%ebp
 8049213:	81 ec 28 40 00 00    	sub    $0x4028,%esp
 8049219:	89 5d f8             	mov    %ebx,-0x8(%ebp)
 804921c:	89 7d fc             	mov    %edi,-0x4(%ebp)
 804921f:	8b 5d 08             	mov    0x8(%ebp),%ebx
 8049222:	83 3d ec c1 04 08 00 	cmpl   $0x0,0x804c1ec
 8049229:	75 11                	jne    804923c <validate+0x2c>
 804922b:	c7 04 24 64 a3 04 08 	movl   $0x804a364,(%esp)
 8049232:	e8 21 f8 ff ff       	call   8048a58 <puts@plt>
 8049237:	e9 0d 01 00 00       	jmp    8049349 <validate+0x139>
 804923c:	83 fb 04             	cmp    $0x4,%ebx
 804923f:	76 11                	jbe    8049252 <validate+0x42>
 8049241:	c7 04 24 90 a3 04 08 	movl   $0x804a390,(%esp)
 8049248:	e8 0b f8 ff ff       	call   8048a58 <puts@plt>
 804924d:	e9 f7 00 00 00       	jmp    8049349 <validate+0x139>
 8049252:	c7 05 00 c2 04 08 01 	movl   $0x1,0x804c200
 8049259:	00 00 00 
 804925c:	ba a0 c1 04 08       	mov    $0x804c1a0,%edx
 8049261:	8b 04 9a             	mov    (%edx,%ebx,4),%eax
 8049264:	83 e8 01             	sub    $0x1,%eax
 8049267:	89 04 9a             	mov    %eax,(%edx,%ebx,4)
 804926a:	85 c0                	test   %eax,%eax
 804926c:	7e 11                	jle    804927f <validate+0x6f>
 804926e:	c7 04 24 d3 a4 04 08 	movl   $0x804a4d3,(%esp)
 8049275:	e8 de f7 ff ff       	call   8048a58 <puts@plt>
 804927a:	e9 ca 00 00 00       	jmp    8049349 <validate+0x139>
 804927f:	c7 04 24 de a4 04 08 	movl   $0x804a4de,(%esp)
 8049286:	e8 cd f7 ff ff       	call   8048a58 <puts@plt>
 804928b:	83 3d f0 c1 04 08 00 	cmpl   $0x0,0x804c1f0
 8049292:	0f 84 a5 00 00 00    	je     804933d <validate+0x12d>
 8049298:	bf 20 c2 04 08       	mov    $0x804c220,%edi
 804929d:	b8 00 00 00 00       	mov    $0x0,%eax
 80492a2:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80492a7:	f2 ae                	repnz scas %es:(%edi),%al
 80492a9:	f7 d1                	not    %ecx
 80492ab:	83 c1 1f             	add    $0x1f,%ecx
 80492ae:	81 f9 00 20 00 00    	cmp    $0x2000,%ecx
 80492b4:	76 11                	jbe    80492c7 <validate+0xb7>
 80492b6:	c7 04 24 b8 a3 04 08 	movl   $0x804a3b8,(%esp)
 80492bd:	e8 96 f7 ff ff       	call   8048a58 <puts@plt>
 80492c2:	e9 82 00 00 00       	jmp    8049349 <validate+0x139>
 80492c7:	c7 44 24 10 20 c2 04 	movl   $0x804c220,0x10(%esp)
 80492ce:	08 
 80492cf:	a1 fc c1 04 08       	mov    0x804c1fc,%eax
 80492d4:	89 44 24 0c          	mov    %eax,0xc(%esp)
 80492d8:	89 5c 24 08          	mov    %ebx,0x8(%esp)
 80492dc:	c7 44 24 04 e4 a4 04 	movl   $0x804a4e4,0x4(%esp)
 80492e3:	08 
 80492e4:	8d 9d f8 df ff ff    	lea    -0x2008(%ebp),%ebx
 80492ea:	89 1c 24             	mov    %ebx,(%esp)
 80492ed:	e8 b6 f5 ff ff       	call   80488a8 <sprintf@plt>
 80492f2:	8d 85 f8 bf ff ff    	lea    -0x4008(%ebp),%eax
 80492f8:	89 44 24 0c          	mov    %eax,0xc(%esp)
 80492fc:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8049303:	00 
 8049304:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8049308:	a1 ec c1 04 08       	mov    0x804c1ec,%eax
 804930d:	89 04 24             	mov    %eax,(%esp)
 8049310:	e8 a6 0a 00 00       	call   8049dbb <driver_post>
 8049315:	85 c0                	test   %eax,%eax
 8049317:	75 0e                	jne    8049327 <validate+0x117>
 8049319:	c7 04 24 f0 a3 04 08 	movl   $0x804a3f0,(%esp)
 8049320:	e8 33 f7 ff ff       	call   8048a58 <puts@plt>
 8049325:	eb 16                	jmp    804933d <validate+0x12d>
 8049327:	8d 85 f8 bf ff ff    	lea    -0x4008(%ebp),%eax
 804932d:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049331:	c7 04 24 20 a4 04 08 	movl   $0x804a420,(%esp)
 8049338:	e8 bb f6 ff ff       	call   80489f8 <printf@plt>
 804933d:	c7 04 24 ed a4 04 08 	movl   $0x804a4ed,(%esp)
 8049344:	e8 0f f7 ff ff       	call   8048a58 <puts@plt>
 8049349:	8b 5d f8             	mov    -0x8(%ebp),%ebx
 804934c:	8b 7d fc             	mov    -0x4(%ebp),%edi
 804934f:	89 ec                	mov    %ebp,%esp
 8049351:	5d                   	pop    %ebp
 8049352:	c3                   	ret    

08049353 <initialize_bomb>:
 8049353:	55                   	push   %ebp
 8049354:	89 e5                	mov    %esp,%ebp
 8049356:	57                   	push   %edi
 8049357:	56                   	push   %esi
 8049358:	53                   	push   %ebx
 8049359:	81 ec 1c 24 00 00    	sub    $0x241c,%esp
 804935f:	83 3d f4 c1 04 08 00 	cmpl   $0x0,0x804c1f4
 8049366:	74 0c                	je     8049374 <initialize_bomb+0x21>
 8049368:	c7 04 24 ff ff ff ff 	movl   $0xffffffff,(%esp)
 804936f:	e8 a8 02 00 00       	call   804961c <init_timeout>
 8049374:	83 3d f0 c1 04 08 00 	cmpl   $0x0,0x804c1f0
 804937b:	0f 84 eb 00 00 00    	je     804946c <initialize_bomb+0x119>
 8049381:	c7 44 24 04 00 04 00 	movl   $0x400,0x4(%esp)
 8049388:	00 
 8049389:	8d 85 e8 fb ff ff    	lea    -0x418(%ebp),%eax
 804938f:	89 04 24             	mov    %eax,(%esp)
 8049392:	e8 b1 f6 ff ff       	call   8048a48 <gethostname@plt>
 8049397:	85 c0                	test   %eax,%eax
 8049399:	75 1e                	jne    80493b9 <initialize_bomb+0x66>
 804939b:	a1 a0 b1 04 08       	mov    0x804b1a0,%eax
 80493a0:	bb 00 00 00 00       	mov    $0x0,%ebx
 80493a5:	8d b5 e8 fb ff ff    	lea    -0x418(%ebp),%esi
 80493ab:	bf a0 b1 04 08       	mov    $0x804b1a0,%edi
 80493b0:	85 c0                	test   %eax,%eax
 80493b2:	75 1d                	jne    80493d1 <initialize_bomb+0x7e>
 80493b4:	e9 92 00 00 00       	jmp    804944b <initialize_bomb+0xf8>
 80493b9:	c7 04 24 60 a4 04 08 	movl   $0x804a460,(%esp)
 80493c0:	e8 93 f6 ff ff       	call   8048a58 <puts@plt>
 80493c5:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 80493cc:	e8 d7 f6 ff ff       	call   8048aa8 <exit@plt>
 80493d1:	89 74 24 04          	mov    %esi,0x4(%esp)
 80493d5:	89 04 24             	mov    %eax,(%esp)
 80493d8:	e8 2b f6 ff ff       	call   8048a08 <strcasecmp@plt>
 80493dd:	85 c0                	test   %eax,%eax
 80493df:	74 0c                	je     80493ed <initialize_bomb+0x9a>
 80493e1:	83 c3 01             	add    $0x1,%ebx
 80493e4:	8b 04 9f             	mov    (%edi,%ebx,4),%eax
 80493e7:	85 c0                	test   %eax,%eax
 80493e9:	75 e6                	jne    80493d1 <initialize_bomb+0x7e>
 80493eb:	eb 5e                	jmp    804944b <initialize_bomb+0xf8>
 80493ed:	8d 85 e8 db ff ff    	lea    -0x2418(%ebp),%eax
 80493f3:	89 04 24             	mov    %eax,(%esp)
 80493f6:	e8 85 00 00 00       	call   8049480 <init_driver>
 80493fb:	85 c0                	test   %eax,%eax
 80493fd:	79 6d                	jns    804946c <initialize_bomb+0x119>
 80493ff:	eb 28                	jmp    8049429 <initialize_bomb+0xd6>
 8049401:	bb 00 00 00 00       	mov    $0x0,%ebx
 8049406:	be a0 b1 04 08       	mov    $0x804b1a0,%esi
 804940b:	89 04 24             	mov    %eax,(%esp)
 804940e:	e8 45 f6 ff ff       	call   8048a58 <puts@plt>
 8049413:	83 c3 01             	add    $0x1,%ebx
 8049416:	8b 04 9e             	mov    (%esi,%ebx,4),%eax
 8049419:	85 c0                	test   %eax,%eax
 804941b:	75 ee                	jne    804940b <initialize_bomb+0xb8>
 804941d:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049424:	e8 7f f6 ff ff       	call   8048aa8 <exit@plt>
 8049429:	8d 85 e8 db ff ff    	lea    -0x2418(%ebp),%eax
 804942f:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049433:	c7 04 24 f7 a4 04 08 	movl   $0x804a4f7,(%esp)
 804943a:	e8 b9 f5 ff ff       	call   80489f8 <printf@plt>
 804943f:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049446:	e8 5d f6 ff ff       	call   8048aa8 <exit@plt>
 804944b:	8d 85 e8 fb ff ff    	lea    -0x418(%ebp),%eax
 8049451:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049455:	c7 04 24 98 a4 04 08 	movl   $0x804a498,(%esp)
 804945c:	e8 97 f5 ff ff       	call   80489f8 <printf@plt>
 8049461:	a1 a0 b1 04 08       	mov    0x804b1a0,%eax
 8049466:	85 c0                	test   %eax,%eax
 8049468:	75 97                	jne    8049401 <initialize_bomb+0xae>
 804946a:	eb b1                	jmp    804941d <initialize_bomb+0xca>
 804946c:	81 c4 1c 24 00 00    	add    $0x241c,%esp
 8049472:	5b                   	pop    %ebx
 8049473:	5e                   	pop    %esi
 8049474:	5f                   	pop    %edi
 8049475:	5d                   	pop    %ebp
 8049476:	c3                   	ret    
 8049477:	90                   	nop
 8049478:	90                   	nop
 8049479:	90                   	nop
 804947a:	90                   	nop
 804947b:	90                   	nop
 804947c:	90                   	nop
 804947d:	90                   	nop
 804947e:	90                   	nop
 804947f:	90                   	nop

08049480 <init_driver>:
 8049480:	55                   	push   %ebp
 8049481:	89 e5                	mov    %esp,%ebp
 8049483:	57                   	push   %edi
 8049484:	56                   	push   %esi
 8049485:	53                   	push   %ebx
 8049486:	83 ec 2c             	sub    $0x2c,%esp
 8049489:	8b 7d 08             	mov    0x8(%ebp),%edi
 804948c:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8049493:	00 
 8049494:	c7 04 24 0d 00 00 00 	movl   $0xd,(%esp)
 804949b:	e8 68 f4 ff ff       	call   8048908 <signal@plt>
 80494a0:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 80494a7:	00 
 80494a8:	c7 04 24 1d 00 00 00 	movl   $0x1d,(%esp)
 80494af:	e8 54 f4 ff ff       	call   8048908 <signal@plt>
 80494b4:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 80494bb:	00 
 80494bc:	c7 04 24 1d 00 00 00 	movl   $0x1d,(%esp)
 80494c3:	e8 40 f4 ff ff       	call   8048908 <signal@plt>
 80494c8:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 80494cf:	00 
 80494d0:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 80494d7:	00 
 80494d8:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 80494df:	e8 b4 f4 ff ff       	call   8048998 <socket@plt>
 80494e4:	89 c6                	mov    %eax,%esi
 80494e6:	85 c0                	test   %eax,%eax
 80494e8:	79 4e                	jns    8049538 <init_driver+0xb8>
 80494ea:	c7 07 45 72 72 6f    	movl   $0x6f727245,(%edi)
 80494f0:	c7 47 04 72 3a 20 43 	movl   $0x43203a72,0x4(%edi)
 80494f7:	c7 47 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%edi)
 80494fe:	c7 47 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%edi)
 8049505:	c7 47 10 61 62 6c 65 	movl   $0x656c6261,0x10(%edi)
 804950c:	c7 47 14 20 74 6f 20 	movl   $0x206f7420,0x14(%edi)
 8049513:	c7 47 18 63 72 65 61 	movl   $0x61657263,0x18(%edi)
 804951a:	c7 47 1c 74 65 20 73 	movl   $0x73206574,0x1c(%edi)
 8049521:	c7 47 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%edi)
 8049528:	66 c7 47 24 74 00    	movw   $0x74,0x24(%edi)
 804952e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049533:	e9 dc 00 00 00       	jmp    8049614 <init_driver+0x194>
 8049538:	c7 04 24 23 a5 04 08 	movl   $0x804a523,(%esp)
 804953f:	e8 44 f5 ff ff       	call   8048a88 <gethostbyname@plt>
 8049544:	85 c0                	test   %eax,%eax
 8049546:	75 2a                	jne    8049572 <init_driver+0xf2>
 8049548:	c7 44 24 08 23 a5 04 	movl   $0x804a523,0x8(%esp)
 804954f:	08 
 8049550:	c7 44 24 04 80 a5 04 	movl   $0x804a580,0x4(%esp)
 8049557:	08 
 8049558:	89 3c 24             	mov    %edi,(%esp)
 804955b:	e8 48 f3 ff ff       	call   80488a8 <sprintf@plt>
 8049560:	89 34 24             	mov    %esi,(%esp)
 8049563:	e8 c0 f4 ff ff       	call   8048a28 <close@plt>
 8049568:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804956d:	e9 a2 00 00 00       	jmp    8049614 <init_driver+0x194>
 8049572:	8d 5d d8             	lea    -0x28(%ebp),%ebx
 8049575:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
 804957b:	c7 43 04 00 00 00 00 	movl   $0x0,0x4(%ebx)
 8049582:	c7 43 08 00 00 00 00 	movl   $0x0,0x8(%ebx)
 8049589:	c7 43 0c 00 00 00 00 	movl   $0x0,0xc(%ebx)
 8049590:	66 c7 45 d8 02 00    	movw   $0x2,-0x28(%ebp)
 8049596:	8b 50 0c             	mov    0xc(%eax),%edx
 8049599:	89 54 24 08          	mov    %edx,0x8(%esp)
 804959d:	8d 55 dc             	lea    -0x24(%ebp),%edx
 80495a0:	89 54 24 04          	mov    %edx,0x4(%esp)
 80495a4:	8b 40 10             	mov    0x10(%eax),%eax
 80495a7:	8b 00                	mov    (%eax),%eax
 80495a9:	89 04 24             	mov    %eax,(%esp)
 80495ac:	e8 f7 f3 ff ff       	call   80489a8 <bcopy@plt>
 80495b1:	66 c7 45 da 47 26    	movw   $0x2647,-0x26(%ebp)
 80495b7:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 80495be:	00 
 80495bf:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 80495c3:	89 34 24             	mov    %esi,(%esp)
 80495c6:	e8 fd f2 ff ff       	call   80488c8 <connect@plt>
 80495cb:	85 c0                	test   %eax,%eax
 80495cd:	79 2f                	jns    80495fe <init_driver+0x17e>
 80495cf:	c7 44 24 0c 26 47 00 	movl   $0x4726,0xc(%esp)
 80495d6:	00 
 80495d7:	c7 44 24 08 23 a5 04 	movl   $0x804a523,0x8(%esp)
 80495de:	08 
 80495df:	c7 44 24 04 ac a5 04 	movl   $0x804a5ac,0x4(%esp)
 80495e6:	08 
 80495e7:	89 3c 24             	mov    %edi,(%esp)
 80495ea:	e8 b9 f2 ff ff       	call   80488a8 <sprintf@plt>
 80495ef:	89 34 24             	mov    %esi,(%esp)
 80495f2:	e8 31 f4 ff ff       	call   8048a28 <close@plt>
 80495f7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80495fc:	eb 16                	jmp    8049614 <init_driver+0x194>
 80495fe:	89 34 24             	mov    %esi,(%esp)
 8049601:	e8 22 f4 ff ff       	call   8048a28 <close@plt>
 8049606:	66 c7 07 4f 4b       	movw   $0x4b4f,(%edi)
 804960b:	c6 47 02 00          	movb   $0x0,0x2(%edi)
 804960f:	b8 00 00 00 00       	mov    $0x0,%eax
 8049614:	83 c4 2c             	add    $0x2c,%esp
 8049617:	5b                   	pop    %ebx
 8049618:	5e                   	pop    %esi
 8049619:	5f                   	pop    %edi
 804961a:	5d                   	pop    %ebp
 804961b:	c3                   	ret    

0804961c <init_timeout>:
 804961c:	55                   	push   %ebp
 804961d:	89 e5                	mov    %esp,%ebp
 804961f:	53                   	push   %ebx
 8049620:	83 ec 14             	sub    $0x14,%esp
 8049623:	8b 5d 08             	mov    0x8(%ebp),%ebx
 8049626:	85 db                	test   %ebx,%ebx
 8049628:	74 25                	je     804964f <init_timeout+0x33>
 804962a:	85 db                	test   %ebx,%ebx
 804962c:	79 05                	jns    8049633 <init_timeout+0x17>
 804962e:	bb 05 00 00 00       	mov    $0x5,%ebx
 8049633:	c7 44 24 04 40 9e 04 	movl   $0x8049e40,0x4(%esp)
 804963a:	08 
 804963b:	c7 04 24 0e 00 00 00 	movl   $0xe,(%esp)
 8049642:	e8 c1 f2 ff ff       	call   8048908 <signal@plt>
 8049647:	89 1c 24             	mov    %ebx,(%esp)
 804964a:	e8 89 f3 ff ff       	call   80489d8 <alarm@plt>
 804964f:	83 c4 14             	add    $0x14,%esp
 8049652:	5b                   	pop    %ebx
 8049653:	5d                   	pop    %ebp
 8049654:	c3                   	ret    

08049655 <rio_readlineb>:
 8049655:	55                   	push   %ebp
 8049656:	89 e5                	mov    %esp,%ebp
 8049658:	57                   	push   %edi
 8049659:	56                   	push   %esi
 804965a:	53                   	push   %ebx
 804965b:	83 ec 3c             	sub    $0x3c,%esp
 804965e:	89 c3                	mov    %eax,%ebx
 8049660:	89 4d c8             	mov    %ecx,-0x38(%ebp)
 8049663:	89 55 d0             	mov    %edx,-0x30(%ebp)
 8049666:	83 f9 01             	cmp    $0x1,%ecx
 8049669:	0f 86 c3 00 00 00    	jbe    8049732 <rio_readlineb+0xdd>
 804966f:	8d 78 0c             	lea    0xc(%eax),%edi
 8049672:	89 7d d4             	mov    %edi,-0x2c(%ebp)
 8049675:	c7 45 cc 01 00 00 00 	movl   $0x1,-0x34(%ebp)
 804967c:	eb 3e                	jmp    80496bc <rio_readlineb+0x67>
 804967e:	c7 44 24 08 00 20 00 	movl   $0x2000,0x8(%esp)
 8049685:	00 
 8049686:	89 7c 24 04          	mov    %edi,0x4(%esp)
 804968a:	8b 03                	mov    (%ebx),%eax
 804968c:	89 04 24             	mov    %eax,(%esp)
 804968f:	e8 f4 f2 ff ff       	call   8048988 <read@plt>
 8049694:	89 43 04             	mov    %eax,0x4(%ebx)
 8049697:	85 c0                	test   %eax,%eax
 8049699:	79 11                	jns    80496ac <rio_readlineb+0x57>
 804969b:	e8 f8 f1 ff ff       	call   8048898 <__errno_location@plt>
 80496a0:	83 38 04             	cmpl   $0x4,(%eax)
 80496a3:	74 17                	je     80496bc <rio_readlineb+0x67>
 80496a5:	be ff ff ff ff       	mov    $0xffffffff,%esi
 80496aa:	eb 57                	jmp    8049703 <rio_readlineb+0xae>
 80496ac:	85 c0                	test   %eax,%eax
 80496ae:	66 90                	xchg   %ax,%ax
 80496b0:	0f 84 94 00 00 00    	je     804974a <rio_readlineb+0xf5>
 80496b6:	8b 45 d4             	mov    -0x2c(%ebp),%eax
 80496b9:	89 43 08             	mov    %eax,0x8(%ebx)
 80496bc:	8b 73 04             	mov    0x4(%ebx),%esi
 80496bf:	85 f6                	test   %esi,%esi
 80496c1:	7e bb                	jle    804967e <rio_readlineb+0x29>
 80496c3:	85 f6                	test   %esi,%esi
 80496c5:	0f 85 86 00 00 00    	jne    8049751 <rio_readlineb+0xfc>
 80496cb:	8b 43 08             	mov    0x8(%ebx),%eax
 80496ce:	89 74 24 08          	mov    %esi,0x8(%esp)
 80496d2:	89 44 24 04          	mov    %eax,0x4(%esp)
 80496d6:	8d 55 e7             	lea    -0x19(%ebp),%edx
 80496d9:	89 14 24             	mov    %edx,(%esp)
 80496dc:	e8 e7 f2 ff ff       	call   80489c8 <memcpy@plt>
 80496e1:	01 73 08             	add    %esi,0x8(%ebx)
 80496e4:	29 73 04             	sub    %esi,0x4(%ebx)
 80496e7:	83 fe 01             	cmp    $0x1,%esi
 80496ea:	75 17                	jne    8049703 <rio_readlineb+0xae>
 80496ec:	0f b6 45 e7          	movzbl -0x19(%ebp),%eax
 80496f0:	8b 55 d0             	mov    -0x30(%ebp),%edx
 80496f3:	88 02                	mov    %al,(%edx)
 80496f5:	83 c2 01             	add    $0x1,%edx
 80496f8:	89 55 d0             	mov    %edx,-0x30(%ebp)
 80496fb:	80 7d e7 0a          	cmpb   $0xa,-0x19(%ebp)
 80496ff:	75 21                	jne    8049722 <rio_readlineb+0xcd>
 8049701:	eb 36                	jmp    8049739 <rio_readlineb+0xe4>
 8049703:	8b 45 cc             	mov    -0x34(%ebp),%eax
 8049706:	85 f6                	test   %esi,%esi
 8049708:	74 09                	je     8049713 <rio_readlineb+0xbe>
 804970a:	c7 45 cc ff ff ff ff 	movl   $0xffffffff,-0x34(%ebp)
 8049711:	eb 2c                	jmp    804973f <rio_readlineb+0xea>
 8049713:	83 f8 01             	cmp    $0x1,%eax
 8049716:	75 21                	jne    8049739 <rio_readlineb+0xe4>
 8049718:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%ebp)
 804971f:	90                   	nop
 8049720:	eb 1d                	jmp    804973f <rio_readlineb+0xea>
 8049722:	83 45 cc 01          	addl   $0x1,-0x34(%ebp)
 8049726:	8b 45 cc             	mov    -0x34(%ebp),%eax
 8049729:	39 45 c8             	cmp    %eax,-0x38(%ebp)
 804972c:	77 8e                	ja     80496bc <rio_readlineb+0x67>
 804972e:	66 90                	xchg   %ax,%ax
 8049730:	eb 07                	jmp    8049739 <rio_readlineb+0xe4>
 8049732:	c7 45 cc 01 00 00 00 	movl   $0x1,-0x34(%ebp)
 8049739:	8b 55 d0             	mov    -0x30(%ebp),%edx
 804973c:	c6 02 00             	movb   $0x0,(%edx)
 804973f:	8b 45 cc             	mov    -0x34(%ebp),%eax
 8049742:	83 c4 3c             	add    $0x3c,%esp
 8049745:	5b                   	pop    %ebx
 8049746:	5e                   	pop    %esi
 8049747:	5f                   	pop    %edi
 8049748:	5d                   	pop    %ebp
 8049749:	c3                   	ret    
 804974a:	be 00 00 00 00       	mov    $0x0,%esi
 804974f:	eb b2                	jmp    8049703 <rio_readlineb+0xae>
 8049751:	8b 43 08             	mov    0x8(%ebx),%eax
 8049754:	0f b6 00             	movzbl (%eax),%eax
 8049757:	88 45 e7             	mov    %al,-0x19(%ebp)
 804975a:	83 43 08 01          	addl   $0x1,0x8(%ebx)
 804975e:	83 6b 04 01          	subl   $0x1,0x4(%ebx)
 8049762:	eb 88                	jmp    80496ec <rio_readlineb+0x97>

08049764 <submitr>:
 8049764:	55                   	push   %ebp
 8049765:	89 e5                	mov    %esp,%ebp
 8049767:	57                   	push   %edi
 8049768:	56                   	push   %esi
 8049769:	53                   	push   %ebx
 804976a:	81 ec 6c a0 00 00    	sub    $0xa06c,%esp
 8049770:	8b 75 08             	mov    0x8(%ebp),%esi
 8049773:	c7 85 c8 7f ff ff 00 	movl   $0x0,-0x8038(%ebp)
 804977a:	00 00 00 
 804977d:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8049784:	00 
 8049785:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 804978c:	00 
 804978d:	c7 04 24 02 00 00 00 	movl   $0x2,(%esp)
 8049794:	e8 ff f1 ff ff       	call   8048998 <socket@plt>
 8049799:	89 85 b0 5f ff ff    	mov    %eax,-0xa050(%ebp)
 804979f:	85 c0                	test   %eax,%eax
 80497a1:	79 1b                	jns    80497be <submitr+0x5a>
 80497a3:	b8 d8 a5 04 08       	mov    $0x804a5d8,%eax
 80497a8:	b9 26 00 00 00       	mov    $0x26,%ecx
 80497ad:	8b 7d 20             	mov    0x20(%ebp),%edi
 80497b0:	89 c6                	mov    %eax,%esi
 80497b2:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 80497b4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80497b9:	e9 8b 05 00 00       	jmp    8049d49 <submitr+0x5e5>
 80497be:	89 34 24             	mov    %esi,(%esp)
 80497c1:	e8 c2 f2 ff ff       	call   8048a88 <gethostbyname@plt>
 80497c6:	85 c0                	test   %eax,%eax
 80497c8:	75 2f                	jne    80497f9 <submitr+0x95>
 80497ca:	89 74 24 08          	mov    %esi,0x8(%esp)
 80497ce:	c7 44 24 04 80 a5 04 	movl   $0x804a580,0x4(%esp)
 80497d5:	08 
 80497d6:	8b 45 20             	mov    0x20(%ebp),%eax
 80497d9:	89 04 24             	mov    %eax,(%esp)
 80497dc:	e8 c7 f0 ff ff       	call   80488a8 <sprintf@plt>
 80497e1:	8b 8d b0 5f ff ff    	mov    -0xa050(%ebp),%ecx
 80497e7:	89 0c 24             	mov    %ecx,(%esp)
 80497ea:	e8 39 f2 ff ff       	call   8048a28 <close@plt>
 80497ef:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80497f4:	e9 50 05 00 00       	jmp    8049d49 <submitr+0x5e5>
 80497f9:	8d 5d d8             	lea    -0x28(%ebp),%ebx
 80497fc:	c7 03 00 00 00 00    	movl   $0x0,(%ebx)
 8049802:	c7 43 04 00 00 00 00 	movl   $0x0,0x4(%ebx)
 8049809:	c7 43 08 00 00 00 00 	movl   $0x0,0x8(%ebx)
 8049810:	c7 43 0c 00 00 00 00 	movl   $0x0,0xc(%ebx)
 8049817:	66 c7 45 d8 02 00    	movw   $0x2,-0x28(%ebp)
 804981d:	8b 50 0c             	mov    0xc(%eax),%edx
 8049820:	89 54 24 08          	mov    %edx,0x8(%esp)
 8049824:	8d 55 dc             	lea    -0x24(%ebp),%edx
 8049827:	89 54 24 04          	mov    %edx,0x4(%esp)
 804982b:	8b 40 10             	mov    0x10(%eax),%eax
 804982e:	8b 00                	mov    (%eax),%eax
 8049830:	89 04 24             	mov    %eax,(%esp)
 8049833:	e8 70 f1 ff ff       	call   80489a8 <bcopy@plt>
 8049838:	0f b7 45 0c          	movzwl 0xc(%ebp),%eax
 804983c:	66 c1 c8 08          	ror    $0x8,%ax
 8049840:	66 89 45 da          	mov    %ax,-0x26(%ebp)
 8049844:	c7 44 24 08 10 00 00 	movl   $0x10,0x8(%esp)
 804984b:	00 
 804984c:	89 5c 24 04          	mov    %ebx,0x4(%esp)
 8049850:	8b bd b0 5f ff ff    	mov    -0xa050(%ebp),%edi
 8049856:	89 3c 24             	mov    %edi,(%esp)
 8049859:	e8 6a f0 ff ff       	call   80488c8 <connect@plt>
 804985e:	85 c0                	test   %eax,%eax
 8049860:	79 29                	jns    804988b <submitr+0x127>
 8049862:	89 74 24 08          	mov    %esi,0x8(%esp)
 8049866:	c7 44 24 04 00 a6 04 	movl   $0x804a600,0x4(%esp)
 804986d:	08 
 804986e:	8b 45 20             	mov    0x20(%ebp),%eax
 8049871:	89 04 24             	mov    %eax,(%esp)
 8049874:	e8 2f f0 ff ff       	call   80488a8 <sprintf@plt>
 8049879:	89 3c 24             	mov    %edi,(%esp)
 804987c:	e8 a7 f1 ff ff       	call   8048a28 <close@plt>
 8049881:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049886:	e9 be 04 00 00       	jmp    8049d49 <submitr+0x5e5>
 804988b:	ba ff ff ff ff       	mov    $0xffffffff,%edx
 8049890:	8b 7d 1c             	mov    0x1c(%ebp),%edi
 8049893:	b8 00 00 00 00       	mov    $0x0,%eax
 8049898:	89 d1                	mov    %edx,%ecx
 804989a:	f2 ae                	repnz scas %es:(%edi),%al
 804989c:	89 cb                	mov    %ecx,%ebx
 804989e:	f7 d3                	not    %ebx
 80498a0:	8b 7d 10             	mov    0x10(%ebp),%edi
 80498a3:	89 d1                	mov    %edx,%ecx
 80498a5:	f2 ae                	repnz scas %es:(%edi),%al
 80498a7:	89 8d b4 5f ff ff    	mov    %ecx,-0xa04c(%ebp)
 80498ad:	8b 7d 14             	mov    0x14(%ebp),%edi
 80498b0:	89 d1                	mov    %edx,%ecx
 80498b2:	f2 ae                	repnz scas %es:(%edi),%al
 80498b4:	89 ce                	mov    %ecx,%esi
 80498b6:	f7 d6                	not    %esi
 80498b8:	8b 7d 18             	mov    0x18(%ebp),%edi
 80498bb:	89 d1                	mov    %edx,%ecx
 80498bd:	f2 ae                	repnz scas %es:(%edi),%al
 80498bf:	2b b5 b4 5f ff ff    	sub    -0xa04c(%ebp),%esi
 80498c5:	29 ce                	sub    %ecx,%esi
 80498c7:	8d 44 5b fd          	lea    -0x3(%ebx,%ebx,2),%eax
 80498cb:	8d 44 06 7b          	lea    0x7b(%esi,%eax,1),%eax
 80498cf:	3d 00 20 00 00       	cmp    $0x2000,%eax
 80498d4:	76 7c                	jbe    8049952 <submitr+0x1ee>
 80498d6:	8b 75 20             	mov    0x20(%ebp),%esi
 80498d9:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 80498df:	c7 46 04 72 3a 20 52 	movl   $0x52203a72,0x4(%esi)
 80498e6:	c7 46 08 65 73 75 6c 	movl   $0x6c757365,0x8(%esi)
 80498ed:	c7 46 0c 74 20 73 74 	movl   $0x74732074,0xc(%esi)
 80498f4:	c7 46 10 72 69 6e 67 	movl   $0x676e6972,0x10(%esi)
 80498fb:	c7 46 14 20 74 6f 6f 	movl   $0x6f6f7420,0x14(%esi)
 8049902:	c7 46 18 20 6c 61 72 	movl   $0x72616c20,0x18(%esi)
 8049909:	c7 46 1c 67 65 2e 20 	movl   $0x202e6567,0x1c(%esi)
 8049910:	c7 46 20 49 6e 63 72 	movl   $0x72636e49,0x20(%esi)
 8049917:	c7 46 24 65 61 73 65 	movl   $0x65736165,0x24(%esi)
 804991e:	c7 46 28 20 53 55 42 	movl   $0x42555320,0x28(%esi)
 8049925:	c7 46 2c 4d 49 54 52 	movl   $0x5254494d,0x2c(%esi)
 804992c:	c7 46 30 5f 4d 41 58 	movl   $0x58414d5f,0x30(%esi)
 8049933:	c7 46 34 42 55 46 00 	movl   $0x465542,0x34(%esi)
 804993a:	8b bd b0 5f ff ff    	mov    -0xa050(%ebp),%edi
 8049940:	89 3c 24             	mov    %edi,(%esp)
 8049943:	e8 e0 f0 ff ff       	call   8048a28 <close@plt>
 8049948:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804994d:	e9 f7 03 00 00       	jmp    8049d49 <submitr+0x5e5>
 8049952:	8d 95 cc 9f ff ff    	lea    -0x6034(%ebp),%edx
 8049958:	b9 00 08 00 00       	mov    $0x800,%ecx
 804995d:	b8 00 00 00 00       	mov    $0x0,%eax
 8049962:	89 d7                	mov    %edx,%edi
 8049964:	f3 ab                	rep stos %eax,%es:(%edi)
 8049966:	8b 7d 1c             	mov    0x1c(%ebp),%edi
 8049969:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 804996e:	f2 ae                	repnz scas %es:(%edi),%al
 8049970:	f7 d1                	not    %ecx
 8049972:	89 cf                	mov    %ecx,%edi
 8049974:	83 ef 01             	sub    $0x1,%edi
 8049977:	0f 84 d7 03 00 00    	je     8049d54 <submitr+0x5f0>
 804997d:	89 d6                	mov    %edx,%esi
 804997f:	bb 00 00 00 00       	mov    $0x0,%ebx
 8049984:	89 bd b4 5f ff ff    	mov    %edi,-0xa04c(%ebp)
 804998a:	8b 7d 1c             	mov    0x1c(%ebp),%edi
 804998d:	0f b6 04 1f          	movzbl (%edi,%ebx,1),%eax
 8049991:	3c 2a                	cmp    $0x2a,%al
 8049993:	74 25                	je     80499ba <submitr+0x256>
 8049995:	3c 2d                	cmp    $0x2d,%al
 8049997:	74 21                	je     80499ba <submitr+0x256>
 8049999:	3c 2e                	cmp    $0x2e,%al
 804999b:	74 1d                	je     80499ba <submitr+0x256>
 804999d:	3c 5f                	cmp    $0x5f,%al
 804999f:	90                   	nop
 80499a0:	74 18                	je     80499ba <submitr+0x256>
 80499a2:	8d 50 d0             	lea    -0x30(%eax),%edx
 80499a5:	80 fa 09             	cmp    $0x9,%dl
 80499a8:	76 10                	jbe    80499ba <submitr+0x256>
 80499aa:	8d 50 bf             	lea    -0x41(%eax),%edx
 80499ad:	80 fa 19             	cmp    $0x19,%dl
 80499b0:	76 08                	jbe    80499ba <submitr+0x256>
 80499b2:	8d 50 9f             	lea    -0x61(%eax),%edx
 80499b5:	80 fa 19             	cmp    $0x19,%dl
 80499b8:	77 07                	ja     80499c1 <submitr+0x25d>
 80499ba:	88 06                	mov    %al,(%esi)
 80499bc:	83 c6 01             	add    $0x1,%esi
 80499bf:	eb 55                	jmp    8049a16 <submitr+0x2b2>
 80499c1:	3c 20                	cmp    $0x20,%al
 80499c3:	75 08                	jne    80499cd <submitr+0x269>
 80499c5:	c6 06 2b             	movb   $0x2b,(%esi)
 80499c8:	83 c6 01             	add    $0x1,%esi
 80499cb:	eb 49                	jmp    8049a16 <submitr+0x2b2>
 80499cd:	8d 50 e0             	lea    -0x20(%eax),%edx
 80499d0:	80 fa 5f             	cmp    $0x5f,%dl
 80499d3:	76 04                	jbe    80499d9 <submitr+0x275>
 80499d5:	3c 09                	cmp    $0x9,%al
 80499d7:	75 51                	jne    8049a2a <submitr+0x2c6>
 80499d9:	0f b6 c0             	movzbl %al,%eax
 80499dc:	89 44 24 08          	mov    %eax,0x8(%esp)
 80499e0:	c7 44 24 04 3b a5 04 	movl   $0x804a53b,0x4(%esp)
 80499e7:	08 
 80499e8:	8d 85 c0 5f ff ff    	lea    -0xa040(%ebp),%eax
 80499ee:	89 04 24             	mov    %eax,(%esp)
 80499f1:	e8 b2 ee ff ff       	call   80488a8 <sprintf@plt>
 80499f6:	0f b6 85 c0 5f ff ff 	movzbl -0xa040(%ebp),%eax
 80499fd:	88 06                	mov    %al,(%esi)
 80499ff:	0f b6 85 c1 5f ff ff 	movzbl -0xa03f(%ebp),%eax
 8049a06:	88 46 01             	mov    %al,0x1(%esi)
 8049a09:	0f b6 85 c2 5f ff ff 	movzbl -0xa03e(%ebp),%eax
 8049a10:	88 46 02             	mov    %al,0x2(%esi)
 8049a13:	83 c6 03             	add    $0x3,%esi
 8049a16:	83 c3 01             	add    $0x1,%ebx
 8049a19:	3b 9d b4 5f ff ff    	cmp    -0xa04c(%ebp),%ebx
 8049a1f:	0f 85 68 ff ff ff    	jne    804998d <submitr+0x229>
 8049a25:	e9 2a 03 00 00       	jmp    8049d54 <submitr+0x5f0>
 8049a2a:	b8 28 a6 04 08       	mov    $0x804a628,%eax
 8049a2f:	b9 43 00 00 00       	mov    $0x43,%ecx
 8049a34:	8b 7d 20             	mov    0x20(%ebp),%edi
 8049a37:	89 c6                	mov    %eax,%esi
 8049a39:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 8049a3b:	8b 85 b0 5f ff ff    	mov    -0xa050(%ebp),%eax
 8049a41:	89 04 24             	mov    %eax,(%esp)
 8049a44:	e8 df ef ff ff       	call   8048a28 <close@plt>
 8049a49:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a4e:	e9 f6 02 00 00       	jmp    8049d49 <submitr+0x5e5>
 8049a53:	01 c6                	add    %eax,%esi
 8049a55:	89 5c 24 08          	mov    %ebx,0x8(%esp)
 8049a59:	89 74 24 04          	mov    %esi,0x4(%esp)
 8049a5d:	89 3c 24             	mov    %edi,(%esp)
 8049a60:	e8 e3 ee ff ff       	call   8048948 <write@plt>
 8049a65:	85 c0                	test   %eax,%eax
 8049a67:	7f 0f                	jg     8049a78 <submitr+0x314>
 8049a69:	e8 2a ee ff ff       	call   8048898 <__errno_location@plt>
 8049a6e:	83 38 04             	cmpl   $0x4,(%eax)
 8049a71:	75 13                	jne    8049a86 <submitr+0x322>
 8049a73:	b8 00 00 00 00       	mov    $0x0,%eax
 8049a78:	29 c3                	sub    %eax,%ebx
 8049a7a:	75 d7                	jne    8049a53 <submitr+0x2ef>
 8049a7c:	8b bd b4 5f ff ff    	mov    -0xa04c(%ebp),%edi
 8049a82:	85 ff                	test   %edi,%edi
 8049a84:	79 64                	jns    8049aea <submitr+0x386>
 8049a86:	8b 7d 20             	mov    0x20(%ebp),%edi
 8049a89:	be 6c a6 04 08       	mov    $0x804a66c,%esi
 8049a8e:	b8 2c 00 00 00       	mov    $0x2c,%eax
 8049a93:	f7 c7 01 00 00 00    	test   $0x1,%edi
 8049a99:	74 04                	je     8049a9f <submitr+0x33b>
 8049a9b:	a4                   	movsb  %ds:(%esi),%es:(%edi)
 8049a9c:	83 e8 01             	sub    $0x1,%eax
 8049a9f:	f7 c7 02 00 00 00    	test   $0x2,%edi
 8049aa5:	74 05                	je     8049aac <submitr+0x348>
 8049aa7:	66 a5                	movsw  %ds:(%esi),%es:(%edi)
 8049aa9:	83 e8 02             	sub    $0x2,%eax
 8049aac:	89 c1                	mov    %eax,%ecx
 8049aae:	c1 e9 02             	shr    $0x2,%ecx
 8049ab1:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049ab3:	ba 00 00 00 00       	mov    $0x0,%edx
 8049ab8:	a8 02                	test   $0x2,%al
 8049aba:	74 0b                	je     8049ac7 <submitr+0x363>
 8049abc:	0f b7 0c 16          	movzwl (%esi,%edx,1),%ecx
 8049ac0:	66 89 0c 17          	mov    %cx,(%edi,%edx,1)
 8049ac4:	83 c2 02             	add    $0x2,%edx
 8049ac7:	a8 01                	test   $0x1,%al
 8049ac9:	74 07                	je     8049ad2 <submitr+0x36e>
 8049acb:	0f b6 04 16          	movzbl (%esi,%edx,1),%eax
 8049acf:	88 04 17             	mov    %al,(%edi,%edx,1)
 8049ad2:	8b 8d b0 5f ff ff    	mov    -0xa050(%ebp),%ecx
 8049ad8:	89 0c 24             	mov    %ecx,(%esp)
 8049adb:	e8 48 ef ff ff       	call   8048a28 <close@plt>
 8049ae0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049ae5:	e9 5f 02 00 00       	jmp    8049d49 <submitr+0x5e5>
 8049aea:	8b b5 b0 5f ff ff    	mov    -0xa050(%ebp),%esi
 8049af0:	89 b5 cc df ff ff    	mov    %esi,-0x2034(%ebp)
 8049af6:	c7 85 d0 df ff ff 00 	movl   $0x0,-0x2030(%ebp)
 8049afd:	00 00 00 
 8049b00:	8d 85 cc df ff ff    	lea    -0x2034(%ebp),%eax
 8049b06:	8d 95 d8 df ff ff    	lea    -0x2028(%ebp),%edx
 8049b0c:	89 95 d4 df ff ff    	mov    %edx,-0x202c(%ebp)
 8049b12:	8d 95 cc bf ff ff    	lea    -0x4034(%ebp),%edx
 8049b18:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049b1d:	e8 33 fb ff ff       	call   8049655 <rio_readlineb>
 8049b22:	85 c0                	test   %eax,%eax
 8049b24:	7f 29                	jg     8049b4f <submitr+0x3eb>
 8049b26:	b8 98 a6 04 08       	mov    $0x804a698,%eax
 8049b2b:	b9 36 00 00 00       	mov    $0x36,%ecx
 8049b30:	8b 7d 20             	mov    0x20(%ebp),%edi
 8049b33:	89 c6                	mov    %eax,%esi
 8049b35:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
 8049b37:	8b 85 b0 5f ff ff    	mov    -0xa050(%ebp),%eax
 8049b3d:	89 04 24             	mov    %eax,(%esp)
 8049b40:	e8 e3 ee ff ff       	call   8048a28 <close@plt>
 8049b45:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b4a:	e9 fa 01 00 00       	jmp    8049d49 <submitr+0x5e5>
 8049b4f:	8d bd cc bf ff ff    	lea    -0x4034(%ebp),%edi
 8049b55:	8d 85 c8 5f ff ff    	lea    -0xa038(%ebp),%eax
 8049b5b:	89 44 24 10          	mov    %eax,0x10(%esp)
 8049b5f:	8d 85 c8 7f ff ff    	lea    -0x8038(%ebp),%eax
 8049b65:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049b69:	8d 85 cc 7f ff ff    	lea    -0x8034(%ebp),%eax
 8049b6f:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049b73:	c7 44 24 04 42 a5 04 	movl   $0x804a542,0x4(%esp)
 8049b7a:	08 
 8049b7b:	89 3c 24             	mov    %edi,(%esp)
 8049b7e:	e8 a5 ed ff ff       	call   8048928 <__isoc99_sscanf@plt>
 8049b83:	8b 85 c8 7f ff ff    	mov    -0x8038(%ebp),%eax
 8049b89:	8d 9d cc bf ff ff    	lea    -0x4034(%ebp),%ebx
 8049b8f:	8d b5 cc df ff ff    	lea    -0x2034(%ebp),%esi
 8049b95:	3d c8 00 00 00       	cmp    $0xc8,%eax
 8049b9a:	0f 84 bd 00 00 00    	je     8049c5d <submitr+0x4f9>
 8049ba0:	8d 95 c8 5f ff ff    	lea    -0xa038(%ebp),%edx
 8049ba6:	89 54 24 0c          	mov    %edx,0xc(%esp)
 8049baa:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049bae:	c7 44 24 04 d0 a6 04 	movl   $0x804a6d0,0x4(%esp)
 8049bb5:	08 
 8049bb6:	8b 4d 20             	mov    0x20(%ebp),%ecx
 8049bb9:	89 0c 24             	mov    %ecx,(%esp)
 8049bbc:	e8 e7 ec ff ff       	call   80488a8 <sprintf@plt>
 8049bc1:	8b b5 b0 5f ff ff    	mov    -0xa050(%ebp),%esi
 8049bc7:	89 34 24             	mov    %esi,(%esp)
 8049bca:	e8 59 ee ff ff       	call   8048a28 <close@plt>
 8049bcf:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049bd4:	e9 70 01 00 00       	jmp    8049d49 <submitr+0x5e5>
 8049bd9:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049bde:	89 da                	mov    %ebx,%edx
 8049be0:	89 f0                	mov    %esi,%eax
 8049be2:	e8 6e fa ff ff       	call   8049655 <rio_readlineb>
 8049be7:	85 c0                	test   %eax,%eax
 8049be9:	7f 72                	jg     8049c5d <submitr+0x4f9>
 8049beb:	8b 7d 20             	mov    0x20(%ebp),%edi
 8049bee:	c7 07 45 72 72 6f    	movl   $0x6f727245,(%edi)
 8049bf4:	c7 47 04 72 3a 20 43 	movl   $0x43203a72,0x4(%edi)
 8049bfb:	c7 47 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%edi)
 8049c02:	c7 47 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%edi)
 8049c09:	c7 47 10 61 62 6c 65 	movl   $0x656c6261,0x10(%edi)
 8049c10:	c7 47 14 20 74 6f 20 	movl   $0x206f7420,0x14(%edi)
 8049c17:	c7 47 18 72 65 61 64 	movl   $0x64616572,0x18(%edi)
 8049c1e:	c7 47 1c 20 68 65 61 	movl   $0x61656820,0x1c(%edi)
 8049c25:	c7 47 20 64 65 72 73 	movl   $0x73726564,0x20(%edi)
 8049c2c:	c7 47 24 20 66 72 6f 	movl   $0x6f726620,0x24(%edi)
 8049c33:	c7 47 28 6d 20 73 65 	movl   $0x6573206d,0x28(%edi)
 8049c3a:	c7 47 2c 72 76 65 72 	movl   $0x72657672,0x2c(%edi)
 8049c41:	c6 47 30 00          	movb   $0x0,0x30(%edi)
 8049c45:	8b 85 b0 5f ff ff    	mov    -0xa050(%ebp),%eax
 8049c4b:	89 04 24             	mov    %eax,(%esp)
 8049c4e:	e8 d5 ed ff ff       	call   8048a28 <close@plt>
 8049c53:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049c58:	e9 ec 00 00 00       	jmp    8049d49 <submitr+0x5e5>
 8049c5d:	b8 53 a5 04 08       	mov    $0x804a553,%eax
 8049c62:	0f b6 13             	movzbl (%ebx),%edx
 8049c65:	3a 10                	cmp    (%eax),%dl
 8049c67:	0f 85 6c ff ff ff    	jne    8049bd9 <submitr+0x475>
 8049c6d:	0f b6 53 01          	movzbl 0x1(%ebx),%edx
 8049c71:	3a 50 01             	cmp    0x1(%eax),%dl
 8049c74:	0f 85 5f ff ff ff    	jne    8049bd9 <submitr+0x475>
 8049c7a:	0f b6 53 02          	movzbl 0x2(%ebx),%edx
 8049c7e:	3a 50 02             	cmp    0x2(%eax),%dl
 8049c81:	0f 85 52 ff ff ff    	jne    8049bd9 <submitr+0x475>
 8049c87:	8d 95 cc bf ff ff    	lea    -0x4034(%ebp),%edx
 8049c8d:	8d 85 cc df ff ff    	lea    -0x2034(%ebp),%eax
 8049c93:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049c98:	e8 b8 f9 ff ff       	call   8049655 <rio_readlineb>
 8049c9d:	85 c0                	test   %eax,%eax
 8049c9f:	7f 61                	jg     8049d02 <submitr+0x59e>
 8049ca1:	8b 7d 20             	mov    0x20(%ebp),%edi
 8049ca4:	be 00 a7 04 08       	mov    $0x804a700,%esi
 8049ca9:	b8 38 00 00 00       	mov    $0x38,%eax
 8049cae:	f7 c7 01 00 00 00    	test   $0x1,%edi
 8049cb4:	74 04                	je     8049cba <submitr+0x556>
 8049cb6:	a4                   	movsb  %ds:(%esi),%es:(%edi)
 8049cb7:	83 e8 01             	sub    $0x1,%eax
 8049cba:	f7 c7 02 00 00 00    	test   $0x2,%edi
 8049cc0:	74 05                	je     8049cc7 <submitr+0x563>
 8049cc2:	66 a5                	movsw  %ds:(%esi),%es:(%edi)
 8049cc4:	83 e8 02             	sub    $0x2,%eax
 8049cc7:	89 c1                	mov    %eax,%ecx
 8049cc9:	c1 e9 02             	shr    $0x2,%ecx
 8049ccc:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049cce:	ba 00 00 00 00       	mov    $0x0,%edx
 8049cd3:	a8 02                	test   $0x2,%al
 8049cd5:	74 0b                	je     8049ce2 <submitr+0x57e>
 8049cd7:	0f b7 0c 16          	movzwl (%esi,%edx,1),%ecx
 8049cdb:	66 89 0c 17          	mov    %cx,(%edi,%edx,1)
 8049cdf:	83 c2 02             	add    $0x2,%edx
 8049ce2:	a8 01                	test   $0x1,%al
 8049ce4:	74 07                	je     8049ced <submitr+0x589>
 8049ce6:	0f b6 04 16          	movzbl (%esi,%edx,1),%eax
 8049cea:	88 04 17             	mov    %al,(%edi,%edx,1)
 8049ced:	8b 8d b0 5f ff ff    	mov    -0xa050(%ebp),%ecx
 8049cf3:	89 0c 24             	mov    %ecx,(%esp)
 8049cf6:	e8 2d ed ff ff       	call   8048a28 <close@plt>
 8049cfb:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d00:	eb 47                	jmp    8049d49 <submitr+0x5e5>
 8049d02:	89 7c 24 04          	mov    %edi,0x4(%esp)
 8049d06:	8b 75 20             	mov    0x20(%ebp),%esi
 8049d09:	89 34 24             	mov    %esi,(%esp)
 8049d0c:	e8 d7 ec ff ff       	call   80489e8 <strcpy@plt>
 8049d11:	8b bd b0 5f ff ff    	mov    -0xa050(%ebp),%edi
 8049d17:	89 3c 24             	mov    %edi,(%esp)
 8049d1a:	e8 09 ed ff ff       	call   8048a28 <close@plt>
 8049d1f:	b8 56 a5 04 08       	mov    $0x804a556,%eax
 8049d24:	0f b6 0e             	movzbl (%esi),%ecx
 8049d27:	3a 08                	cmp    (%eax),%cl
 8049d29:	75 19                	jne    8049d44 <submitr+0x5e0>
 8049d2b:	0f b6 4e 01          	movzbl 0x1(%esi),%ecx
 8049d2f:	3a 48 01             	cmp    0x1(%eax),%cl
 8049d32:	75 10                	jne    8049d44 <submitr+0x5e0>
 8049d34:	0f b6 56 02          	movzbl 0x2(%esi),%edx
 8049d38:	3a 50 02             	cmp    0x2(%eax),%dl
 8049d3b:	75 07                	jne    8049d44 <submitr+0x5e0>
 8049d3d:	b8 00 00 00 00       	mov    $0x0,%eax
 8049d42:	eb 05                	jmp    8049d49 <submitr+0x5e5>
 8049d44:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d49:	81 c4 6c a0 00 00    	add    $0xa06c,%esp
 8049d4f:	5b                   	pop    %ebx
 8049d50:	5e                   	pop    %esi
 8049d51:	5f                   	pop    %edi
 8049d52:	5d                   	pop    %ebp
 8049d53:	c3                   	ret    
 8049d54:	8d 85 cc 9f ff ff    	lea    -0x6034(%ebp),%eax
 8049d5a:	89 44 24 14          	mov    %eax,0x14(%esp)
 8049d5e:	8b 45 18             	mov    0x18(%ebp),%eax
 8049d61:	89 44 24 10          	mov    %eax,0x10(%esp)
 8049d65:	8b 4d 14             	mov    0x14(%ebp),%ecx
 8049d68:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 8049d6c:	8b 75 10             	mov    0x10(%ebp),%esi
 8049d6f:	89 74 24 08          	mov    %esi,0x8(%esp)
 8049d73:	c7 44 24 04 38 a7 04 	movl   $0x804a738,0x4(%esp)
 8049d7a:	08 
 8049d7b:	8d bd cc bf ff ff    	lea    -0x4034(%ebp),%edi
 8049d81:	89 3c 24             	mov    %edi,(%esp)
 8049d84:	e8 1f eb ff ff       	call   80488a8 <sprintf@plt>
 8049d89:	b8 00 00 00 00       	mov    $0x0,%eax
 8049d8e:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049d93:	f2 ae                	repnz scas %es:(%edi),%al
 8049d95:	f7 d1                	not    %ecx
 8049d97:	89 cf                	mov    %ecx,%edi
 8049d99:	83 ef 01             	sub    $0x1,%edi
 8049d9c:	0f 84 48 fd ff ff    	je     8049aea <submitr+0x386>
 8049da2:	89 fb                	mov    %edi,%ebx
 8049da4:	8d b5 cc bf ff ff    	lea    -0x4034(%ebp),%esi
 8049daa:	89 bd b4 5f ff ff    	mov    %edi,-0xa04c(%ebp)
 8049db0:	8b bd b0 5f ff ff    	mov    -0xa050(%ebp),%edi
 8049db6:	e9 9a fc ff ff       	jmp    8049a55 <submitr+0x2f1>

08049dbb <driver_post>:
 8049dbb:	55                   	push   %ebp
 8049dbc:	89 e5                	mov    %esp,%ebp
 8049dbe:	53                   	push   %ebx
 8049dbf:	83 ec 24             	sub    $0x24,%esp
 8049dc2:	8b 45 08             	mov    0x8(%ebp),%eax
 8049dc5:	8b 55 0c             	mov    0xc(%ebp),%edx
 8049dc8:	8b 5d 14             	mov    0x14(%ebp),%ebx
 8049dcb:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
 8049dcf:	74 20                	je     8049df1 <driver_post+0x36>
 8049dd1:	89 54 24 04          	mov    %edx,0x4(%esp)
 8049dd5:	c7 04 24 59 a5 04 08 	movl   $0x804a559,(%esp)
 8049ddc:	e8 17 ec ff ff       	call   80489f8 <printf@plt>
 8049de1:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049de6:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049dea:	b8 00 00 00 00       	mov    $0x0,%eax
 8049def:	eb 49                	jmp    8049e3a <driver_post+0x7f>
 8049df1:	85 c0                	test   %eax,%eax
 8049df3:	74 37                	je     8049e2c <driver_post+0x71>
 8049df5:	80 38 00             	cmpb   $0x0,(%eax)
 8049df8:	74 32                	je     8049e2c <driver_post+0x71>
 8049dfa:	89 5c 24 18          	mov    %ebx,0x18(%esp)
 8049dfe:	89 54 24 14          	mov    %edx,0x14(%esp)
 8049e02:	c7 44 24 10 70 a5 04 	movl   $0x804a570,0x10(%esp)
 8049e09:	08 
 8049e0a:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049e0e:	c7 44 24 08 77 a5 04 	movl   $0x804a577,0x8(%esp)
 8049e15:	08 
 8049e16:	c7 44 24 04 26 47 00 	movl   $0x4726,0x4(%esp)
 8049e1d:	00 
 8049e1e:	c7 04 24 23 a5 04 08 	movl   $0x804a523,(%esp)
 8049e25:	e8 3a f9 ff ff       	call   8049764 <submitr>
 8049e2a:	eb 0e                	jmp    8049e3a <driver_post+0x7f>
 8049e2c:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049e31:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049e35:	b8 00 00 00 00       	mov    $0x0,%eax
 8049e3a:	83 c4 24             	add    $0x24,%esp
 8049e3d:	5b                   	pop    %ebx
 8049e3e:	5d                   	pop    %ebp
 8049e3f:	c3                   	ret    

08049e40 <sigalrm_handler>:
 8049e40:	55                   	push   %ebp
 8049e41:	89 e5                	mov    %esp,%ebp
 8049e43:	83 ec 18             	sub    $0x18,%esp
 8049e46:	c7 44 24 04 05 00 00 	movl   $0x5,0x4(%esp)
 8049e4d:	00 
 8049e4e:	c7 04 24 84 a7 04 08 	movl   $0x804a784,(%esp)
 8049e55:	e8 9e eb ff ff       	call   80489f8 <printf@plt>
 8049e5a:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8049e61:	e8 42 ec ff ff       	call   8048aa8 <exit@plt>
 8049e66:	90                   	nop
 8049e67:	90                   	nop

08049e68 <hash>:
 8049e68:	55                   	push   %ebp
 8049e69:	89 e5                	mov    %esp,%ebp
 8049e6b:	8b 4d 08             	mov    0x8(%ebp),%ecx
 8049e6e:	0f b6 11             	movzbl (%ecx),%edx
 8049e71:	b8 00 00 00 00       	mov    $0x0,%eax
 8049e76:	84 d2                	test   %dl,%dl
 8049e78:	74 13                	je     8049e8d <hash+0x25>
 8049e7a:	6b c0 67             	imul   $0x67,%eax,%eax
 8049e7d:	0f be d2             	movsbl %dl,%edx
 8049e80:	8d 04 02             	lea    (%edx,%eax,1),%eax
 8049e83:	83 c1 01             	add    $0x1,%ecx
 8049e86:	0f b6 11             	movzbl (%ecx),%edx
 8049e89:	84 d2                	test   %dl,%dl
 8049e8b:	75 ed                	jne    8049e7a <hash+0x12>
 8049e8d:	5d                   	pop    %ebp
 8049e8e:	c3                   	ret    

08049e8f <check>:
 8049e8f:	55                   	push   %ebp
 8049e90:	89 e5                	mov    %esp,%ebp
 8049e92:	8b 45 08             	mov    0x8(%ebp),%eax
 8049e95:	89 c2                	mov    %eax,%edx
 8049e97:	c1 ea 1c             	shr    $0x1c,%edx
 8049e9a:	85 d2                	test   %edx,%edx
 8049e9c:	74 24                	je     8049ec2 <check+0x33>
 8049e9e:	3c 0a                	cmp    $0xa,%al
 8049ea0:	74 20                	je     8049ec2 <check+0x33>
 8049ea2:	0f b6 d4             	movzbl %ah,%edx
 8049ea5:	83 fa 0a             	cmp    $0xa,%edx
 8049ea8:	74 18                	je     8049ec2 <check+0x33>
 8049eaa:	89 c2                	mov    %eax,%edx
 8049eac:	c1 ea 10             	shr    $0x10,%edx
 8049eaf:	80 fa 0a             	cmp    $0xa,%dl
 8049eb2:	74 0e                	je     8049ec2 <check+0x33>
 8049eb4:	c1 e8 18             	shr    $0x18,%eax
 8049eb7:	83 f8 0a             	cmp    $0xa,%eax
 8049eba:	0f 95 c0             	setne  %al
 8049ebd:	0f b6 c0             	movzbl %al,%eax
 8049ec0:	eb 05                	jmp    8049ec7 <check+0x38>
 8049ec2:	b8 00 00 00 00       	mov    $0x0,%eax
 8049ec7:	5d                   	pop    %ebp
 8049ec8:	c3                   	ret    

08049ec9 <gencookie>:
 8049ec9:	55                   	push   %ebp
 8049eca:	89 e5                	mov    %esp,%ebp
 8049ecc:	53                   	push   %ebx
 8049ecd:	83 ec 14             	sub    $0x14,%esp
 8049ed0:	8b 45 08             	mov    0x8(%ebp),%eax
 8049ed3:	89 04 24             	mov    %eax,(%esp)
 8049ed6:	e8 8d ff ff ff       	call   8049e68 <hash>
 8049edb:	89 04 24             	mov    %eax,(%esp)
 8049ede:	e8 d5 e9 ff ff       	call   80488b8 <srand@plt>
 8049ee3:	e8 80 eb ff ff       	call   8048a68 <rand@plt>
 8049ee8:	89 c3                	mov    %eax,%ebx
 8049eea:	89 04 24             	mov    %eax,(%esp)
 8049eed:	e8 9d ff ff ff       	call   8049e8f <check>
 8049ef2:	85 c0                	test   %eax,%eax
 8049ef4:	74 ed                	je     8049ee3 <gencookie+0x1a>
 8049ef6:	89 d8                	mov    %ebx,%eax
 8049ef8:	83 c4 14             	add    $0x14,%esp
 8049efb:	5b                   	pop    %ebx
 8049efc:	5d                   	pop    %ebp
 8049efd:	c3                   	ret    
 8049efe:	90                   	nop
 8049eff:	90                   	nop

08049f00 <__libc_csu_fini>:
 8049f00:	55                   	push   %ebp
 8049f01:	89 e5                	mov    %esp,%ebp
 8049f03:	5d                   	pop    %ebp
 8049f04:	c3                   	ret    
 8049f05:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8049f09:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08049f10 <__libc_csu_init>:
 8049f10:	55                   	push   %ebp
 8049f11:	89 e5                	mov    %esp,%ebp
 8049f13:	57                   	push   %edi
 8049f14:	56                   	push   %esi
 8049f15:	53                   	push   %ebx
 8049f16:	e8 4f 00 00 00       	call   8049f6a <__i686.get_pc_thunk.bx>
 8049f1b:	81 c3 cd 11 00 00    	add    $0x11cd,%ebx
 8049f21:	83 ec 1c             	sub    $0x1c,%esp
 8049f24:	e8 2f e9 ff ff       	call   8048858 <_init>
 8049f29:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 8049f2f:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 8049f35:	29 c7                	sub    %eax,%edi
 8049f37:	c1 ff 02             	sar    $0x2,%edi
 8049f3a:	85 ff                	test   %edi,%edi
 8049f3c:	74 24                	je     8049f62 <__libc_csu_init+0x52>
 8049f3e:	31 f6                	xor    %esi,%esi
 8049f40:	8b 45 10             	mov    0x10(%ebp),%eax
 8049f43:	89 44 24 08          	mov    %eax,0x8(%esp)
 8049f47:	8b 45 0c             	mov    0xc(%ebp),%eax
 8049f4a:	89 44 24 04          	mov    %eax,0x4(%esp)
 8049f4e:	8b 45 08             	mov    0x8(%ebp),%eax
 8049f51:	89 04 24             	mov    %eax,(%esp)
 8049f54:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 8049f5b:	83 c6 01             	add    $0x1,%esi
 8049f5e:	39 fe                	cmp    %edi,%esi
 8049f60:	72 de                	jb     8049f40 <__libc_csu_init+0x30>
 8049f62:	83 c4 1c             	add    $0x1c,%esp
 8049f65:	5b                   	pop    %ebx
 8049f66:	5e                   	pop    %esi
 8049f67:	5f                   	pop    %edi
 8049f68:	5d                   	pop    %ebp
 8049f69:	c3                   	ret    

08049f6a <__i686.get_pc_thunk.bx>:
 8049f6a:	8b 1c 24             	mov    (%esp),%ebx
 8049f6d:	c3                   	ret    
 8049f6e:	90                   	nop
 8049f6f:	90                   	nop

08049f70 <__do_global_ctors_aux>:
 8049f70:	55                   	push   %ebp
 8049f71:	89 e5                	mov    %esp,%ebp
 8049f73:	53                   	push   %ebx
 8049f74:	83 ec 04             	sub    $0x4,%esp
 8049f77:	a1 00 b0 04 08       	mov    0x804b000,%eax
 8049f7c:	83 f8 ff             	cmp    $0xffffffff,%eax
 8049f7f:	74 13                	je     8049f94 <__do_global_ctors_aux+0x24>
 8049f81:	bb 00 b0 04 08       	mov    $0x804b000,%ebx
 8049f86:	66 90                	xchg   %ax,%ax
 8049f88:	83 eb 04             	sub    $0x4,%ebx
 8049f8b:	ff d0                	call   *%eax
 8049f8d:	8b 03                	mov    (%ebx),%eax
 8049f8f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8049f92:	75 f4                	jne    8049f88 <__do_global_ctors_aux+0x18>
 8049f94:	83 c4 04             	add    $0x4,%esp
 8049f97:	5b                   	pop    %ebx
 8049f98:	5d                   	pop    %ebp
 8049f99:	c3                   	ret    
 8049f9a:	90                   	nop
 8049f9b:	90                   	nop

Disassembly of section .fini:

08049f9c <_fini>:
 8049f9c:	55                   	push   %ebp
 8049f9d:	89 e5                	mov    %esp,%ebp
 8049f9f:	53                   	push   %ebx
 8049fa0:	83 ec 04             	sub    $0x4,%esp
 8049fa3:	e8 00 00 00 00       	call   8049fa8 <_fini+0xc>
 8049fa8:	5b                   	pop    %ebx
 8049fa9:	81 c3 40 11 00 00    	add    $0x1140,%ebx
 8049faf:	e8 3c eb ff ff       	call   8048af0 <__do_global_dtors_aux>
 8049fb4:	59                   	pop    %ecx
 8049fb5:	5b                   	pop    %ebx
 8049fb6:	c9                   	leave  
 8049fb7:	c3                   	ret    
