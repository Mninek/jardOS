#include <drivers/serial_port.h>
#include <system/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

static int init_serial() {
   out8(COM1 + 1, 0x00);    // Disable all interrupts
   out8(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   out8(COM1 + 0, 0x05);    // Set divisor to 5 (lo byte) 9600 baud
   out8(COM1 + 1, 0x00);    //                  (hi byte)
   out8(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
   out8(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   out8(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   out8(COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
   out8(COM1 + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
   // Check if serial is faulty (i.e: not same byte as sent)
   if(in8(COM1 + 0) != 0xAE) {
      return 1;
   }
 
   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   out8(COM1 + 4, 0x0F);
   return 0;
} 

// 1 = 0001, 0th bit means data is ready to be read
int serial_received() {
    return in8(COM1+5) & 1; 
}

char read_serial() {
    while (serial_received() == 0);

    return in8(COM1);
}

// 0x20 = 0001 0100.
// bit 4 is set if transmission buffer is empty (we can send info)
// bit 2 us set if there is a break in input data
int is_transmit_empty() {
    return in8(COM1+5) & 0x20; 
}

void write_serial(char a) {
    while (is_transmit_empty() == 0);

    out8(COM1,a);
}


static bool printCharacterSerial(char data) {
	write_serial(data);
	return true;
}

static bool printStringSerial(char* data, size_t length) {
	for (size_t i = 0; i < length; i++)
		!printCharacterSerial(data[i]);
	return true;
}

// prints to the serial port
int serial_printf(const char* restrict format, ...) {
	// all params after format get sent in to parameters
	// these params will be used to inject variables in to the output
	va_list parameters;
	va_start(parameters, format); 
 
	int written = vprintf(format, printCharacterSerial, printStringSerial, parameters);
 
	va_end(parameters);
	return written;
}