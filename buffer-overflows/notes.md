# Exploiting Buffer Overflows

## Echo server

An echo server is a relatively common application

Echos data back to user

`./echo0`

Works, but what if we send it a lot of stuff?

It seg faults... why?

Because we are overflowing the buffer:

`vim echo0.cpp`

## Buffer Overflows

echo0 allocates 16 bytes on the stack to store our input.

gets is INCREDIBLY INSECURE because it reads and writes input until it encounters a newline
New input methods require a max length and will null terminate the array.

```bash
rm echo0
make echo0
```
Notice the compiler warnings

## Exploiting

How is this exploitable?

### The stack

![](https://miro.medium.com/max/578/1*Io2pbNYn8PeJCpSdNK8O8w.jpeg)

If we continue writing into buffer, eventually we will be overwriting the return address...

How does that help us?

### Returning to an existing function

`vim echo1.cpp`

`./echo1`

What if we set the return address to `give_shell`?

We can't just write in the address, we need to send bytes that equal the address.  This can include unprintable(untypeable) bytes such as `\x00`.  We can't type a null character, but it is a byte we can send to the program.  There are lots of ways to send unprintable characters to programs, but pwntools is probably the best.

### pwntools

A python library to help us exploit vulnerabilities

`vim pwntools_example.py`

`p.sendline()`

`p.recvline()`

### x1.py

`vim x1.py`

`python x1.py`

Wow we have a shell, we can run commands like ls, cat, rm, etc.

## Okay... but what if we don't have `give_shell`?

### Assembly, objdump, gdb, gef

`objdump -d echo1`

Notice `give_shell`

How does this work? mov pointer to string before calling system.

### echo2

`./echo2`

Luckily, we know where our data is being stored.  What if we put shellcode in the buffer, then set the return address to the buffer?

This would work, but we'd still need a pointer to the string `/bin/sh`.  Fortunately, we can just add it to the end of our payload and adjust the pointer in the assembly to our `buffer+offset` to where we have `/bin/sh`

### x2.py

`vim x2.py`

`pwntools.asm` with contents similar to `give_shell` from `echo1`

`python x2.py`

Easy.

# Methods for preventing exploits (and how to bypass them)

Obviously, the best way to prevent exploits is to write unexploitable code.  Don't use fgets and properly handle arbitrarily lengthed user input.

## PIE

A binary is typically compiled with something called PIE - position independent execution.

To make your binaries always load in the same location, `-no-pie` for `g++` (BAD IDEA)

*this is an abstration layer handled by the OS, and PIE needs to be supported/enabled.*

If you can leak a pointer, you can figure out where your binary is loaded and PIE becomes pretty useless...

## Stack canary

One common method of protection against buffer overflows is to use something called a stack canary.  Basically, at runtime, the OS generates a random number.  Then, this number is placed on stack for every function call.  It is right above the return address.  That means, to overwrite the return address, you'll need to overwrite the canary.  Before returning, the compiler adds a check to see if the canary has changed.  If it has, the program does a bunch of complicated stuff without returning, then kills itself.

`./echo1_canary`

To compile without stack canaries, `-fno-stack-protector` for `g++` (BAD IDEA)

If we can read the value of the canary, then we can overwrite it with the known value when executing our overflow.  The check will pass and but we will still have overwritten ret.

This is actually pretty easy to do--If we write up to the canary, but not over, then puts() will leak the value.
*not quite this simple because canaries always start with \0*

## Non executable stack

Nowadays, different sections of memory can be marked r/w/x. The stack is almost always not executable.  

To let your stack be executable: `-z execstack` for `g++` (BAD IDEA)

However, depending on the binary, it may be possible to write shellcode to an executable part of memory, then jump to it.

Alternatively, you can use existing bits of executable code to construct something called a ROP chain.

We can leave this for another time (show pdf if interest)


