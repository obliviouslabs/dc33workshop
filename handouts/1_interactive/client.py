# /// script
# dependencies = [
#   "pwntools",
# ]
# ///

from pwn import *
import time
context.log_level = 'debug'
# r = process("./encrypted_memory_interactive.elf")
# To test with the remove server instead of locally, uncomment the follwoing line:
r = remote("ws.xtrm0.com", 4333)

r.recvuntil("input: ")
r.recvline()
r.sendline("hello")
r.interactive()

