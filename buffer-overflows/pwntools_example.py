from pwn import *

p = process("./echo1")

p.recvuntil("0x")

addr = int(p.recvline(keepends=False), 16)

print "Pointer address:" + hex(addr)



