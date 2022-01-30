#include <stdio.h>

#include <kernel/tty.h>
#include <drivers/serial_port.h>
#include <kernel/gdt.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	terminal_test_print();

	serial_printf("Initializing GDT...");
	gdt_init();
	serial_printf("Done!\n");
}