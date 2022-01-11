#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	unsigned char uc = c;
	if (uc == '\n') {
		terminal_row += 1;
		terminal_column = 0;
	} 
	else if (uc == '\t') {
		terminal_column += 4;
		if (terminal_column > VGA_WIDTH) {
			terminal_column = terminal_column % VGA_WIDTH;
			terminal_row += 1;
		}
	} 
	else {
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}
	
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void reset_color() {
	terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
}

void terminal_test_print() {
	int test = 2;
	char test2 = 'a';
	char* string = "This is a string";
	terminal_setcolor(vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_RED));
	printf("Hi! Line two test and also a test for writing a sentence that is very much too long for a single terminal line so we shall see what happens!\n");
	reset_color();
	printf("Reset color test!\n");
	printf("hexadecimal test %x, %x, %x, %x, %x, %x\n", 10, 11, 12, 13, 14, 15);
	printf("char test %c\n", test2);
	printf("pointer test %p\n", &test);
	printf("pointer test2 %p\n", &test2);
	printf("String test %s\n", "this is a string");
	printf("String test2 %s\n", string);
	for (int i = 0; i < 10; i++){
		printf("scroll test\t%i\n", i);
	}
}