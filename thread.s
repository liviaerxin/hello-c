	.arch armv8-a
	.file	"thread.c"
	.text
	.align	2
	.global	print_message
	.type	print_message, %function
print_message:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	x0, [sp, 24]
	ldr	x0, [sp, 24]
	str	x0, [sp, 40]
	ldr	x0, [sp, 40]
	bl	puts
	nop
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	print_message, .-print_message
	.section	.rodata
	.align	3
.LC0:
	.string	"Thread 1: Hello, World!"
	.align	3
.LC1:
	.string	"Thread 2: Goodbye, World!"
	.align	3
.LC2:
	.string	"Main: creating thread %d\n"
	.align	3
.LC3:
	.string	"Error: unable to create thread, %d\n"
	.align	3
.LC4:
	.string	"Main: program completed. Exiting."
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -80]!
	.cfi_def_cfa_offset 80
	.cfi_offset 29, -80
	.cfi_offset 30, -72
	mov	x29, sp
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x1, [x0]
	str	x1, [sp, 72]
	mov	x1, 0
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	str	x0, [sp, 56]
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	str	x0, [sp, 64]
	str	wzr, [sp, 28]
	b	.L3
.L5:
	ldr	w1, [sp, 28]
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
	add	x1, sp, 40
	ldrsw	x0, [sp, 28]
	lsl	x0, x0, 3
	add	x4, x1, x0
	ldrsw	x0, [sp, 28]
	lsl	x0, x0, 3
	add	x1, sp, 56
	ldr	x0, [x1, x0]
	mov	x3, x0
	adrp	x0, print_message
	add	x2, x0, :lo12:print_message
	mov	x1, 0
	mov	x0, x4
	bl	pthread_create
	str	w0, [sp, 36]
	ldr	w0, [sp, 36]
	cmp	w0, 0
	beq	.L4
	ldr	w1, [sp, 36]
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	printf
	mov	w0, 1
	bl	exit
.L4:
	ldr	w0, [sp, 28]
	add	w0, w0, 1
	str	w0, [sp, 28]
.L3:
	ldr	w0, [sp, 28]
	cmp	w0, 1
	ble	.L5
	str	wzr, [sp, 32]
	b	.L6
.L7:
	ldrsw	x0, [sp, 32]
	lsl	x0, x0, 3
	add	x1, sp, 40
	ldr	x0, [x1, x0]
	mov	x1, 0
	bl	pthread_join
	ldr	w0, [sp, 32]
	add	w0, w0, 1
	str	w0, [sp, 32]
.L6:
	ldr	w0, [sp, 32]
	cmp	w0, 1
	ble	.L7
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	puts
	mov	w0, 0
	mov	w1, w0
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x3, [sp, 72]
	ldr	x2, [x0]
	subs	x3, x3, x2
	mov	x2, 0
	beq	.L9
	bl	__stack_chk_fail
.L9:
	mov	w0, w1
	ldp	x29, x30, [sp], 80
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
