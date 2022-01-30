#ifndef GDT_H
#define GDT_H

#include <stdint.h>

/*
    define first 16 bits of the limit
    define first 16 bits of the base
    define middle 8 bites of base
    define present/priv/type properties (1 byte)
    define other flags + last 4 bits of limit (1byte)
    define last 8 bits of base
*/
typedef struct GDT_descriptor
{
    uint16_t    limit_first_16b;
    uint16_t    base_first_16b;
    uint8_t     base_middle_8b;
    uint8_t     access;
    uint8_t     flags;
    uint8_t     base_last_8b;
} __attribute__((packed)) GDT_descriptor_t;

typedef struct GDT_descriptor_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) GDT_descriptor_ptr_t;

void gdt_init();
void gdt_create_entry(uint32_t limit, uint32_t base, uint8_t access, uint8_t flags, int index);
void gdt_asm_init();

#endif
