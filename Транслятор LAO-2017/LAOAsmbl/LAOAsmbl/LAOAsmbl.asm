.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	ExitProcess PROTO :DWORD

	includelib ../Debug/LAOLib.lib
	consoles PROTO :DWORD
	consolen PROTO :DWORD
	sum PROTO :DWORD, :DWORD

.stack 4096
.const
	literal0 DWORD 5
	literal1 DWORD 1
	literal2 DWORD 5
	literal3 DWORD 8
	literal4 DWORD 10
	literal5 BYTE "k", 0
	literal6 DWORD 0
	literal7 BYTE "less0", 0
	literal8 BYTE "more0", 0
	literal9 BYTE "first", 0
	literal10 BYTE "second", 0
	literal11 DWORD 2
	literal12 DWORD 2
	literal13 DWORD 0
.data
	craz0 DWORD ?
	ient DWORD ?
	tent DWORD ?
	kent DWORD ?
	v DWORD ?
	s DWORD ?

.code
razn PROC braz0:DWORD, araz0:DWORD
push araz0
push braz0
pop ebx
pop eax
sub eax, ebx
push eax
pop craz0

	mov eax, craz0
	ret
razn ENDP

main PROC
push literal0
pop ient

push literal1
push literal2
push literal3
pop eax
pop ebx
mul ebx
push eax
pop eax
pop ebx
add eax, ebx
push eax
push literal4
pop eax
pop ebx
add eax, ebx
push eax
pop tent

push ient
push tent
call razn
push eax
pop kent

	push offset literal5
call consoles
	push kent
call consolen
mov eax, ient
cmp eax, literal6
jb less0
ja more0
less0:
	push offset literal7
call consoles
jmp flag0
more0:
	push offset literal8
call consoles
flag0:
push offset literal9
pop v

	push offset literal10
call consoles
push literal11
push literal12
call sum
push eax
pop s

	push s
call consolen
push 0
call ExitProcess
main ENDP
end main