#include <stdio.h>

#include <kernel/tty.h>
#include <drivers/serial_port.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	serial_printf("this is a test for serial output\n");
	terminal_test_print();
}