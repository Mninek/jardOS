#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
 
static bool printCharacter(char data) {
	if (putchar(data) == EOF)
		return false;
	return true;
}

static bool printString(char* data, size_t length) {
	for (size_t i = 0; i < length; i++)
		if (!printCharacter(data[i]))
			return false;
	return true;
}

/*
	c = character
	d = signed int
	f = float
	i = unsigned int
	p = pointer
	u = unsignted int
	x = hexadecimal
	% = treated as a single %
*/

int vprintf(const char* format, bool (*printCharacterPointer)(char), bool (*printStringPointer)(char*, size_t), va_list list) {
	int written = 0;

	for (int i = 0; format[i] != '\0'; i++) {
		char buf[256]; // may need to increase in the future
		if (format[i] == '%') {
			i++;
			int param = 0;
			int len = 0;
			switch(format[i]) {
				case 'i':
					param = va_arg(list, int);
					len = itoa(param, buf, 10);
					printStringPointer(buf, len);
					break;
				case 'x':
					param = va_arg(list, int);
					len = itoa(param, buf, 16);
					printStringPointer(buf, len);
					break;
				case 'c':
					char char_param = va_arg(list, int);
					len = 1;
					printCharacterPointer(char_param);
					break;
				case 'p':
					char* ptr = va_arg(list, char*);
					uint64_t converted_ptr = (uint64_t)ptr;
					len = itoa(converted_ptr, buf, 16);
					printStringPointer("0x", 2);
					int zeroes = 0;

					while (len + zeroes < 8) {
						printCharacterPointer('0');
						zeroes += 1;
					}
					printStringPointer(buf, len);
					written += zeroes;
					break;
				case 's':
					char* string = va_arg(list, char*);
					len = strlen(string);
					printStringPointer(string, len);
					break;
				default:
					char* implement = "Work in progress";
					printStringPointer(implement, strlen(implement));

				written += len;
			}
		} else {
			printCharacterPointer(format[i]);
			written += 1;
		}
	}
}

int printf(const char* restrict format, ...) {
	// all params after format get sent in to parameters
	// these params will be used to inject variables in to the output
	va_list parameters;
	va_start(parameters, format); 
 
	int written = vprintf(format, printCharacter, printString, parameters);
 
	va_end(parameters);
	return written;
}
