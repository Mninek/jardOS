#include <stdio.h>

#include <kernel/tty.h>
#include <drivers/serial_port.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	serial_printf("[FATAL] this is a test for serial output\n");
	serial_printf("[ERROR] this is a test for serial output\n");
	serial_printf("[INFO] this is a test for serial output\n");
	serial_printf("[WARN] this is a test for serial output\n");
	serial_printf("[DEBUG] this is a test for serial output\n");
	terminal_test_print();
}