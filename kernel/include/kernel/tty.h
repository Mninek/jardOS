//tty stands for TeleTYpewriter, this header file handles all the classes needed to write to the terminal

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void reset_color();
void terminal_test_print();

#endif