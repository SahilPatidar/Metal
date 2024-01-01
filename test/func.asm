	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.globl	_main
	.p2align	2
_main:
	.cfi_startproc
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]
	.cfi_def_cfa_offset 32
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #2
Lloh0:
	adrp	x0, l___unnamed_1@PAGE
Lloh1:
	add	x0, x0, l___unnamed_1@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w8, #4
Lloh2:
	adrp	x0, l___unnamed_2@PAGE
Lloh3:
	add	x0, x0, l___unnamed_2@PAGEOFF
	str	x8, [sp]
	bl	_printf
	ldp	x29, x30, [sp, #16]
	mov	w0, wzr
	add	sp, sp, #32
	ret
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc

	.section	__TEXT,__const
	.globl	_t3_v
	.p2align	2, 0x0
_t3_v:
	.long	2
	.long	1
	.long	3
	.long	4

	.section	__TEXT,__cstring,cstring_literals
l___unnamed_1:
	.asciz	"%d\n"

l___unnamed_2:
	.asciz	"%d\n"

.subsections_via_symbols
