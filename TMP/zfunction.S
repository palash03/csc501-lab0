.globl zfunction
zfunction:
push   %ebp
mov    %esp,%ebp
sub    $0x10,%esp
movl   $0xff803fff,-0x4(%ebp)
mov    -0x4(%ebp),%eax
and    %eax,0x8(%ebp)
shll   $0x4,0x8(%ebp)
mov    0x8(%ebp),%eax
leave
ret
