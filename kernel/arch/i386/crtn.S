.section .init
	/* gcc will nicely put the contents of crtend.o's .init section here. */
	popl %ebp /* ebp refers to stop of stack*/
	ret

.section .fini
	/* gcc will nicely put the contents of crtend.o's .fini section here. */
	popl %ebp
	ret