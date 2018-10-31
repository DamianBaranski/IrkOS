#include "string.h"
#include "types.h"
#include "vga.h"

// https://wiki.osdev.org/Global_Descriptor_Table
// https://en.wikibooks.org/wiki/X86_Assembly/Global_Descriptor_Table

#define FLAGS_GR (1 << 3) // Granularity bit.
                          // If 0 the limit is in 1 B blocks (byte granularity),
// if 1 the limit is in 4 KiB blocks (page granularity).
#define FLAGS_SZ (1 << 2) // Size bit.
// If 0 the selector defines 16 bit protected mode. If 1 it
// defines 32 bit protected mode.

#define ACCESS_PR                                                              \
  (1 << 7) // Present bit. This must be 1 for all valid
           // selectors
#define ACCESS_PRIVL_0 (0 << 5)
#define ACCESS_PRIVL_1 (1 << 5)
#define ACCESS_PRIVL_2 (2 << 5)
#define ACCESS_PRIVL_3 (3 << 5)
#define ACCESS_EX (1 << 3) // Executable bit.
                           // If 1 code in this segment can be executed, ie. a
                           // code selector. If 0 it is a data selector.
#define ACCESS_DC (1 << 2) // Direction bit/Conforming bit.
#define ACCESS_RW (1 << 1) // Readable bit/Writable bit.
#define ACCESS_AC (1 << 0) // Accessed bit.
                           // Just set to 0. The CPU sets this to 1 when the
                           // segment is accessed.
#define GDTSZ 3 // The number of gdt entries

// GDT Descriptor
typedef struct __attribute__((packed)) {
  uint16_t limit; // size
  uint32_t base;  // Offset
} gdtr_t;

// GDT Entry
typedef struct __attribute__((packed)) {
  uint16_t limit_low;
  uint32_t base_low : 24;
  uint8_t access;
  uint8_t limit_high : 4;
  uint8_t flags : 4;
  uint8_t base_high;
} gdt_entry_t;

gdtr_t gdtr;
gdt_entry_t gdt_entry[GDTSZ] = {};

void prepare_gdt_entry(gdt_entry_t *entry, uint32_t base, uint32_t limit,
                       uint8_t access, uint8_t flags) {
  entry->base_low = (base & 0xFFFFFF); // twenty-four younger bits
  entry->base_high = (base >> 24);     // eight older bits
  entry->access = access;
  if (limit > 0xFFFFF) // If limit is greater than 0xFFFFF
  {                    // then use 4kB blocks
    limit = limit >> 12;
    flags |= FLAGS_GR; // Set up the granularity
  }
  entry->flags = flags;
  entry->limit_low = (limit & 0xFFFF);        // sixteen younger bits
  entry->limit_high = ((limit >> 16) & 0x0F); // four older bits
}

void gdt_print(void) {
  kprintf("Gdt: limit: %x\n", gdtr.limit);
  kprintf("Gdt: base: 0x%x\n", gdtr.base);
  for (int i = 0; i < GDTSZ; i++) {
    kprintf("Gdt: entry %d: ", i);
    for (int j = 0; j < sizeof(gdt_entry_t); j++) {
      kprintf("0x%x ", *((uint8_t *)gdt_entry + i * sizeof(gdt_entry_t) + j));
    }
    kprintf("\n");
  }
}

void gdt_init(void) {
  // Prepare GDT Description
  gdtr.limit = sizeof(gdt_entry_t) * GDTSZ - 1;
  gdtr.base = (uint32_t)gdt_entry;

  prepare_gdt_entry(&gdt_entry[0], 0, 0, 0, 0);
  prepare_gdt_entry(&gdt_entry[1], 0, 0xFFFFFFFF,
                    ACCESS_PR | ACCESS_EX | ACCESS_RW | (1 << 4),
                    FLAGS_SZ); // Code
  prepare_gdt_entry(&gdt_entry[2], 0, 0xFFFFFFFF,
                    ACCESS_PR | ACCESS_RW | (1 << 4), FLAGS_SZ); // Data

  gdt_print();

  // load the gdtr registry
  asm("lgdtl (gdtr)");

  // initialize the segments
  asm("   movw $0x10, %ax    \n \
            movw %ax, %ds    \n \
            movw %ax, %es    \n \
            movw %ax, %fs    \n \
            movw %ax, %gs    \n \
            ljmp $0x08, $next    \n \
            next:        \n");
  kprintf("Gdt: initialization completed\n");
}
