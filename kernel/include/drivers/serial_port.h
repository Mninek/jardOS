#ifndef SERIAL_PORT
#define SERIAL_PORT

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

#include <stdbool.h>
#include <stddef.h>

static int init_serial();

int serial_received();

char read_serial();

int is_transmit_empty();

void write_serial(char a);

static bool printCharacterSerial(char data);

static bool printStringSerial(char* data, size_t length);

int serial_printf(const char* restrict format, ...);

#endif