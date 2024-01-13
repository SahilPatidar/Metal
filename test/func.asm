	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.globl	_HeapSort_swap
	.p2align	2
_HeapSort_swap:
	.cfi_startproc
	sbfiz	x8, x2, #2, #32
	sbfiz	x9, x1, #2, #32
	ldr	w10, [x0, x8]
	ldr	w11, [x0, x9]
	str	w10, [x0, x9]
	str	w11, [x0, x8]
	ret
	.cfi_endproc

	.globl	_HeapSort_heapify
	.p2align	2
_HeapSort_heapify:
	.cfi_startproc
	stp	x22, x21, [sp, #-48]!
	stp	x20, x19, [sp, #16]
	stp	x29, x30, [sp, #32]
	.cfi_def_cfa_offset 48
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	sxtw	x8, w2
	mov	w19, #1
	bfi	x19, x8, #1, #63
	cmp	w19, w1
	b.ge	LBB1_2
	ldr	w9, [x0, x19, lsl #2]
	ldr	w10, [x0, x8, lsl #2]
	cmp	w9, w10
	b.gt	LBB1_4
LBB1_2:
	sbfiz	x9, x2, #1, #32
	mov	w19, w2
	sxtw	x9, w9
	add	x9, x9, #2
	cmp	w9, w1
	b.ge	LBB1_4
	ldr	w10, [x0, x9, lsl #2]
	ldr	w8, [x0, x8, lsl #2]
	cmp	w10, w8
	csel	w19, w9, w2, gt
LBB1_4:
	cmp	w19, w2
	b.eq	LBB1_6
	mov	w21, w1
	mov	w1, w19
	mov	x20, x0
	bl	_HeapSort_swap
	mov	x0, x20
	mov	w1, w21
	mov	w2, w19
	bl	_HeapSort_heapify
LBB1_6:
	ldp	x29, x30, [sp, #32]
	ldp	x20, x19, [sp, #16]
	ldp	x22, x21, [sp], #48
	ret
	.cfi_endproc

	.globl	_HeapSort_print
	.p2align	2
_HeapSort_print:
	.cfi_startproc
	sub	sp, sp, #80
	stp	x24, x23, [sp, #16]
	stp	x22, x21, [sp, #32]
	stp	x20, x19, [sp, #48]
	stp	x29, x30, [sp, #64]
	.cfi_def_cfa_offset 80
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	mov	x19, x0
	mov	x23, xzr
Lloh0:
	adrp	x20, l___unnamed_1@PAGE
Lloh1:
	add	x20, x20, l___unnamed_1@PAGEOFF
Lloh2:
	adrp	x21, l___unnamed_2@PAGE
Lloh3:
	add	x21, x21, l___unnamed_2@PAGEOFF
	add	x24, x0, #8
Lloh4:
	adrp	x22, l___unnamed_3@PAGE
Lloh5:
	add	x22, x22, l___unnamed_3@PAGEOFF
	cmp	w23, #3
	b.gt	LBB2_2
LBB2_1:
	ldr	w8, [x19, x23, lsl #2]
	mov	x0, x20
	str	x8, [sp]
	bl	_printf
	ldur	w8, [x24, #-4]
	mov	x0, x21
	str	x8, [sp]
	bl	_printf
	ldr	w8, [x24], #8
	mov	x0, x22
	str	x8, [sp]
	bl	_printf
	mov	w0, #10
	bl	_putchar
	add	x23, x23, #1
	cmp	w23, #3
	b.le	LBB2_1
LBB2_2:
	ldp	x29, x30, [sp, #64]
	ldp	x20, x19, [sp, #48]
	ldp	x22, x21, [sp, #32]
	ldp	x24, x23, [sp, #16]
	add	sp, sp, #80
	ret
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc

	.globl	_HeapSort_heap_sort
	.p2align	2
_HeapSort_heap_sort:
	.cfi_startproc
	sub	sp, sp, #48
	stp	x20, x19, [sp, #16]
	stp	x29, x30, [sp, #32]
	.cfi_def_cfa_offset 48
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x0
	mov	w20, wzr
	cmp	w20, #9
	b.gt	LBB3_2
LBB3_1:
	mov	x0, x19
	mov	w1, #10
	mov	w2, w20
	bl	_HeapSort_heapify
	add	w20, w20, #1
	cmp	w20, #9
	b.le	LBB3_1
LBB3_2:
	ldr	w8, [x19, #32]
Lloh6:
	adrp	x0, l___unnamed_4@PAGE
Lloh7:
	add	x0, x0, l___unnamed_4@PAGEOFF
	str	x8, [sp]
	bl	_printf
	mov	w20, wzr
	cmp	w20, #9
	b.gt	LBB3_4
LBB3_3:
	mov	x0, x19
	mov	w1, wzr
	mov	w2, w20
	bl	_HeapSort_swap
	mov	x0, x19
	mov	w1, #10
	mov	w2, w20
	bl	_HeapSort_heapify
	add	w20, w20, #1
	cmp	w20, #9
	b.le	LBB3_3
LBB3_4:
	ldp	x29, x30, [sp, #32]
	ldp	x20, x19, [sp, #16]
	add	sp, sp, #48
	ret
	.loh AdrpAdd	Lloh6, Lloh7
	.cfi_endproc

	.globl	_main
	.p2align	2
_main:
	.cfi_startproc
	sub	sp, sp, #64
	stp	x29, x30, [sp, #48]
	.cfi_def_cfa_offset 64
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	x8, #6
	mov	x9, #10
	add	x0, sp, #8
	movk	x8, #8, lsl #32
	movk	x9, #9, lsl #32
	stp	x8, x9, [sp, #8]
	mov	x8, #5
	mov	x9, #7
	movk	x8, #1, lsl #32
	movk	x9, #2, lsl #32
	stp	x8, x9, [sp, #24]
	mov	x8, #4
	movk	x8, #3, lsl #32
	str	x8, [sp, #40]
	bl	_HeapSort_heap_sort
	add	x0, sp, #8
	bl	_HeapSort_print
	ldp	x29, x30, [sp, #48]
	mov	w0, wzr
	add	sp, sp, #64
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
l___unnamed_1:
	.asciz	"%d - \n"

l___unnamed_2:
	.asciz	"\t\t - %d\n"

l___unnamed_3:
	.asciz	"\t\t - %d\n"

l___unnamed_5:
	.asciz	"\n"

l___unnamed_4:
	.asciz	"%d\n"

.subsections_via_symbols
