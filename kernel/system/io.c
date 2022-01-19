#include <system/io.h>
#include <stdint.h>

uint8_t in8(uint16_t port) {
    uint8_t value;
    __asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

uint16_t in16(uint16_t port) {
    uint16_t value;
    __asm volatile("inw %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

uint32_t in32(uint16_t port) {
    uint32_t value;
    __asm volatile("inl %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

uint8_t out8(uint16_t port, uint8_t value) {
    __asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

uint16_t out16(uint16_t port, uint16_t value) {
    __asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
}

uint32_t out32(uint16_t port, uint32_t value) {
    __asm volatile("outl %0, %1" : : "a"(value), "Nd"(port));
}