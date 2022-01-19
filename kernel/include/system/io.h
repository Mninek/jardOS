#include <stdint.h>

#ifndef IO
#define IO
uint8_t in8(uint16_t port);
uint16_t in16(uint16_t port);
uint32_t in32(uint16_t port);
uint8_t out8(uint16_t port, uint8_t value);
uint16_t out16(uint16_t port, uint16_t value);
uint32_t out32(uint16_t port, uint32_t value);
#endif