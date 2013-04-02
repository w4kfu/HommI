BITS 32
org     0x0048B0A0

push    ebp
mov     ebp, esp
sub     esp, 4
push    0x190
call    0x00480A50		; _heap_alloc
mov     [ebp - 4], eax
push    eax
push    0x400
call    dword [0x004D6530]	; GetCurrentDirectory

push    0x00491EA7		; offset PathSound + 7 "\SOUND\"
push    dword [ebp - 4]
call    0x004805F8		; strcat

push    dword [ebp - 4]
push    0x00491EA0		; PathSound
call    0x004805F0		; strcpy

push    dword [ebp - 4]
push    0x400
call    dword [0x004D6530]	; GetCurrentDirectory


push    0x00491D47		; offset PathAnim + 7 "\ANIM\"
push    dword [ebp - 4]
call    0x004805F8		; strcat

push    dword [ebp - 4]
push    0x00491D40		; PathAnim
call    0x004805F0		; strcpy

push    dword [ebp - 4]
call    0x00480880

leave
ret
