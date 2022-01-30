#include <kernel/gdt.h>
#include <drivers/serial_port.h>

// initialized with the number of descriptors
GDT_descriptor_t GDT_Descriptors[4];
GDT_descriptor_ptr_t GDT_descriptor_ptr;

void gdt_init() {
    GDT_descriptor_ptr.limit = (sizeof(GDT_descriptor_t) * 4) - 1;
    GDT_descriptor_ptr.base = (uint32_t)&GDT_Descriptors;
    // create null descriptor
    gdt_create_entry(0,0,0,0,0);

    /*  Create code segment
        limit = 0xFFFFFFFF
        base = 0
        access = 0x9a
            1               present bit
            00              ring bits, determines privilege
            1               type, 1 for code segment
            1               contain code bit
            0               conforming? (can code be run from lower priv segments)
            1               readable?
            0               Accessed. is used by CPU to determine if we are accessed.
        flags = 0xc
            1               granularity forces limit *= 0x10000, so we can spend whole 4GB of memory
            1               32 bits
            0               Long-mode code flag, if 1 descriptor defines 64 bit code segment
            0               reserved
        index = 1
    */
   gdt_create_entry(0xFFFFFFFF, 0, 0x9A, 0xCF, 1);

   /*  Create data segment
        limit = 0xFFFFFFFF
        base = 0
        access = 0x92
            1               present bit
            00              ring bits, determines privilege
            1               type, 1 for code segment
            0               contain code bit
            0               direction? 0 means we expand up, 1 means we expand down
            1               writeable?
            0               Accessed. is used by CPU to determine if we are accessed.
        flags = 0xc
            1               granularity forces limit *= 0x10000, so we can spend whole 4GB of memory
            1               32 bits
            0               Long-mode code flag, if 1 descriptor defines 64 bit code segment
            0               reserved
        index = 2
    */
    gdt_create_entry(0xFFFFFFFF, 0, 0x92, 0xCF, 2);
    gdt_asm_init();
}

/*
    Creates a global descriptor table entry.
    limit -> size of the descriptor
    base -> location of the descriptor
    access -> bit encoded access
    flags -> other flags
    index -> entry in the GDTDescriptors array
*/
void gdt_create_entry(uint32_t limit, uint32_t base, uint8_t access, uint8_t flags, int index) {
    GDT_descriptor_t *descriptor_ptr = &GDT_Descriptors[index];
    descriptor_ptr->limit_first_16b = limit && 0xFFFF;
    descriptor_ptr->base_first_16b = base && 0xFFFF;
    descriptor_ptr->base_middle_8b = (base >> 16) && 0xFF;
    descriptor_ptr->access = access;
    descriptor_ptr->flags = ((limit >> 16) && 0x0F);
    descriptor_ptr->flags |= flags & 0xF0;
    descriptor_ptr->base_last_8b =(base >> 24) && 0xFF;
}

void gdt_asm_init() {
    
    uint32_t gdt_ptr = (uint32_t)(&GDT_descriptor_ptr);

    /*
        Thank you to this homie: https://forum.osdev.org/viewtopic.php?f=1&t=37245
        for letting me avoid writing an assembly file :p 
    */
    __asm volatile("movl %0,%%eax    \n\t"  //load the pointer int eax
                 "lgdt (%%eax)     \n\t"            //Set the CPU GDT pointer to your table

                 //Segments confuse the hell out of me so hopefully this code will make them go away
                 //16 being the offset to the supervisor Data segment in my GDT
                 "movw $0x10, %%ax \n\t"  // load 16 into the ax register
                 "movw  %%ax, %%ds \n\t"   // copy 16  into all of the segment registers
                 "movw  %%ax, %%es \n\t"
                 "movw  %%ax, %%fs \n\t"
                 "movw  %%ax, %%gs \n\t"
                 "movw  %%ax, %%ss \n\t"
                 "ljmp $0x08,$boing%=\n\t"   // apparently this loads the CS segment register with 8
                 // 8 being the offset to the Supervisor code segment in my GDT
                 "boing%=:" : : "r" (gdt_ptr) : "eax"); // tells gcc that %0 = ptr and that I use eax as a temp
}
