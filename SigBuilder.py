import re


raw = """48 89 5C 24 08    mov     [rsp+arg_0], rbx
OPENGL32:00007FF927696299 48 89 6C 24 10    mov     [rsp+arg_8], rbp
OPENGL32:00007FF92769629E 48 89 74 24 18    mov     [rsp+arg_10], rsi
OPENGL32:00007FF9276962A3 57                push    rdi
OPENGL32:00007FF9276962A4 41 56             push    r14
OPENGL32:00007FF9276962A6 41 57             push    r15
OPENGL32:00007FF9276962A8 48 83 EC 50       sub     rsp, 50h
OPENGL32:00007FF9276962AC 48 8B 2A          mov     rbp, [rdx]
OPENGL32:00007FF9276962AF 4C 8B F9          mov     r15, rcx
OPENGL32:00007FF9276962B2 48 85 ED"""

matches = re.findall(r'([0-9A-F]{2})[ \n\+]{1}', raw)


for match in matches:
	print(f"0x{match}, ", end="")


	