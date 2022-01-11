#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
 
static bool printCharacter(char data) {
	if (putchar(data) == EOF)
		return false;
	return true;
}

static bool printString(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
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
	% = treated as a single %
*/

int vprintf(const char* format, va_list list) {
	int written = 0;

	for (int i = 0; format[i] != '\0'; i++) {
		char buf[8]; // may need to increase in the future
		if (format[i] == '%') {
			i++;
			switch(format[i]) {
				case 'i':
					int param = va_arg(list, int);
					int len = itoa(param, buf, 10);
					printString(buf, len);
					break;
				default:
					char* implement = "Work in progress";
					printString(implement, strlen(implement));
			}
		} else {
			printCharacter(format[i]);
		}
	}
}
 
int printf(const char* restrict format, ...) {
	// all params after format get sent in to parameters
	// these params will be used to inject variables in to the output
	va_list parameters;
	va_start(parameters, format); 
 
	int written = vprintf(format, parameters);
 
	va_end(parameters);
	return written;
}
