; DOOM entry point
; Copyright (C) 2022 iProgramInCpp

BITS 32

global exit1
global _entry
global g_ebpSave, g_espSave
extern main

; exit(int) function.
exit1:
	push ebp
	mov  ebp, esp
	mov  eax, [ebp + 8]
	jmp _exit
	
; the entry point of the application
_entry:
	; push ebx, edi, and esi, to not break the kernel backend
	push ebx
	push edi
	push esi
	
	; save ebp and esp to restore later when we call exit() or main() returns.
	mov  eax, ebp
	mov  ebx, esp
	mov  [g_ebpSave], eax
	mov  [g_espSave], ebx
	
	; and call our real entry point!
	call main
; if main() returns normally, restore the old esp/ebp anyway just in case
; if exit() was called forcefully, just jump here and it'll save ebp/esp in a good way.
_exit:

	; restore the old esp/ebp.
	mov  ecx, [g_espSave]
	mov  edx, [g_ebpSave]
	mov  esp, ecx
	mov  ebp, edx
	
	; pop esi, edi, and ebx.
	pop  esi
	pop  edi
	pop  ebx
	
	; return!
	ret

section .bss
g_ebpSave RESD 1
g_espSave RESD 1