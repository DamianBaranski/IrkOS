#include "pic.h"
#include "io.h"

// https://pdos.csail.mit.edu/6.828/2014/readings/hardware/8259A.pdf

#define PIC1_CTRL 0x20 // Primary PIC Command and Status Register
#define PIC2_CTRL 0xA0 // Secondary (Slave) PIC Command and Status Register
#define PIC1_DATA 0x21 // Primary PIC Interrupt Mask Register and Data Register
#define PIC2_DATA                                                              \
  0xA1 // Secondary (Slave) PIC Interrupt Mask Register and Data Register

#define ICW1_IC4                                                               \
  (1 << 0) // If set(1), the PIC expects to recieve IC4 during initialization.
#define ICW1_SNGL                                                              \
  (1 << 1) // If set(1), only one PIC in system. If cleared, PIC is cascaded
           // with slave PICs, and ICW3 must be sent to controller.
#define ICW1_ADI                                                               \
  (1 << 2) // If set (1), CALL address interval is 4, else 8. This is useually
           // ignored by x86, and is default to 0
#define ICW1_LTIM                                                              \
  (1 << 3) // If set (1), Operate in Level Triggered Mode. If Not set (0),
           // Operate in Edge Triggered Mode
#define ICW1_INIT                                                              \
  (1 << 4) // Initialization bit. Set 1 if PIC is to be initialized

#define ICW4_uPM                                                               \
  (1 << 0) // If set (1), it is in 80x86 mode. Cleared if MCS-80/86 mode
#define ICW4_AEOI                                                              \
  (1 << 1) // If set, on the last interrupt acknowledge pulse, controller
           // automatically performs End of Interrupt (EOI) operation
#define ICW4_MS                                                                \
  (1 << 2) // Only use if BUF is set. If set (1), selects buffer master. Cleared
           // if buffer slave.
#define ICW4_BUF (1 << 3) // If set, controller operates in buffered mode
#define ICW4_SFNM                                                              \
  (1 << 4) // Special Fully Nested Mode. Used in systems with a large amount of
           // cascaded controllers.

#define OCW2_L0 (1 << 0) // Interrupt level upon which the controller must react
#define OCW2_L1 (1 << 1) // Interrupt level upon which the controller must react
#define OCW2_L2 (1 << 2) // Interrupt level upon which the controller must react
#define OCW2_EOI (1 << 5) // End of Interrupt (EOI) request
#define OCW2_SL (1 << 6)  // Selection
#define OCW2_R (1 << 7)   // Rotation option

void pic_remap(void) {
  // ICW1 - Begin initialization
  outb(PIC1_CTRL, ICW1_IC4 | ICW1_INIT);
  outb(PIC2_CTRL, ICW1_IC4 | ICW1_INIT);

  // ICW2 - Map IRQ base interrupt numbers
  outb(PIC1_DATA, 0x20);
  outb(PIC2_DATA, 0x28);

  // ICW3 - Set the IR line to connect both PICs
  outb(PIC1_DATA, (1 << 2)); // IR line 2
  outb(PIC2_DATA, (1 << 1)); // IR line 2

  // ICW4 - Set x86 mode
  outb(PIC1_DATA, ICW4_uPM);
  outb(PIC2_DATA, ICW4_uPM);

  // All done. Null out the data registers
  outb(PIC1_DATA, 0);
  outb(PIC2_DATA, 0);
}
