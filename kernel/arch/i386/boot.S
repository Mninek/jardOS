# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries (4KB)
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot. This plus magic and flags MUST be 32 bit unsigned int equal to 0

# Declare a header as in the Multiboot Standard.
# section is basically like a data class, so we are just creating the multiboot 'class' that the bootloader will look for and setting the values
# accordingly
.section .multiboot
.align 4 # 4 byte aligned -> 32 bit
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread. Multiboot standard does not define the value of esp (stack pointer)
# bss = blocking starting symbol
.section .bss
.align 16 # stacks have a 16 byte alignment on x86 as per System V ABI Standard
stack_bottom: # bottom stack symbol
.skip 16384 # 16 KiB stack provided to the kernel
stack_top: # top stack symbol

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	/* 
		set the stack pointer (esp) to top of stack (since it grows downard on x86 machines)
	*/
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli # clear interrupt flag, basically disables interrupts 
1:	hlt # halt instructions, wait for next interrupt to arrive, but since its disabled this will lock the computer 
	jmp 1b # jump to hlt instruction (1b is 1 before), just incase some interrupt does get through
.size _start, . - _start