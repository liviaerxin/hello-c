	.arch armv8-a
	.file	"process.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Parent process with PID: %d\n"
	.align	3
.LC1:
	.string	"Child process with PID: %d\n"
	.align	3
.LC2:
	.string	"Fork failed\n"
	.text
	.align	2
	.global	fork_example
	.type	fork_example, %function
fork_example:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	bl	fork
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 0
	ble	.L2
	bl	getpid
	mov	w1, w0
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L1
.L2:
	ldr	w0, [sp, 28]
	cmp	w0, 0
	bne	.L4
	bl	getpid
	mov	w1, w0
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
	b	.L1
.L4:
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	perror
	mov	w0, 1
	bl	exit
.L1:
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	fork_example, .-fork_example
	.section	.rodata
	.align	3
.LC3:
	.string	"Parent process with PID: %d, x = %d, 0x%p\n"
	.align	3
.LC4:
	.string	"Child process with PID: %d, x = %d, 0x%p\n"
	.text
	.align	2
	.global	fork_example_variable
	.type	fork_example_variable, %function
fork_example_variable:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x1, [x0]
	str	x1, [sp, 24]
	mov	x1, 0
	mov	w0, 5
	str	w0, [sp, 16]
	bl	fork
	str	w0, [sp, 20]
	ldr	w0, [sp, 20]
	cmp	w0, 0
	ble	.L6
	ldr	w0, [sp, 16]
	add	w0, w0, 5
	str	w0, [sp, 16]
	bl	getpid
	mov	w4, w0
	ldr	w0, [sp, 16]
	add	x1, sp, 16
	mov	x3, x1
	mov	w2, w0
	mov	w1, w4
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	printf
	b	.L5
.L6:
	ldr	w0, [sp, 20]
	cmp	w0, 0
	bne	.L8
	ldr	w0, [sp, 16]
	sub	w0, w0, #5
	str	w0, [sp, 16]
	bl	getpid
	mov	w4, w0
	ldr	w0, [sp, 16]
	add	x1, sp, 16
	mov	x3, x1
	mov	w2, w0
	mov	w1, w4
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	printf
	b	.L5
.L8:
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	perror
	mov	w0, 1
	bl	exit
.L5:
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x2, [sp, 24]
	ldr	x1, [x0]
	subs	x2, x2, x1
	mov	x1, 0
	beq	.L9
	bl	__stack_chk_fail
.L9:
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE7:
	.size	fork_example_variable, .-fork_example_variable
	.align	2
	.global	main
	.type	main, %function
main:
.LFB8:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	bl	fork_example_variable
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
