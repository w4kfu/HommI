The game requires that you have inserted CD-ROM of HOMM_I in order to produce the path to ANIM and SOUND folders, it's really annoying to put a CD-ROM each time for playing the game.

At the end of section .text there is enough place to make a patch.

.text:0048B200                 dd 380h dup(?)

Offset : 0x8A4A0

## Patch function

### Useful function

	00480A50 ; int __cdecl _heap_alloc(SIZE_T dwBytes)

	00480880 ; void __cdecl free(void *Memory)

	004805F8 ; char *__cdecl strcat(char *Dest, const char *Source)

	004805F0 ; char *__cdecl strcpy(char *Dest, const char *Source)

### ASM Code

	BITS 32
	org     0x0048B0A0

	push    ebp
	mov     ebp, esp
	sub     esp, 4
	push    0x190
	call    0x00480A50              ; _heap_alloc
	mov     [ebp - 4], eax
	push    eax
	push    0x400
	call    dword [0x004D6530]      ; GetCurrentDirectory

	push    0x00491EA7              ; offset PathSound + 7 "\SOUND\"
	push    dword [ebp - 4]
	call    0x004805F8              ; strcat

	push    dword [ebp - 4]
	push    0x00491EA0              ; PathSound
	call    0x004805F0              ; strcpy

	push    dword [ebp - 4]
	push    0x400
	call    dword [0x004D6530]      ; GetCurrentDirectory


	push    0x00491D47              ; offset PathAnim + 7 "\ANIM\"
	push    dword [ebp - 4]
	call    0x004805F8              ; strcat

	push    dword [ebp - 4]
	push    0x00491D40              ; PathAnim
	call    0x004805F0              ; strcpy

	push    dword [ebp - 4]
	call    0x00480880

	leave
	ret

Nasm compil :

	nasm -f bin patch.S

### HEROES.EXE PATCH

Replace :

	.text:004500C4                 cmp     [ebp+var_4], 2
	.text:004500C8                 jnz     loc_4500F0

by :

	.text:004500C4                 call    sub_48B0A0
	.text:004500C9                 jmp     short loc_4500F0
