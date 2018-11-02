OBJ_FILES=kernel.o \
	  loader.o \
	  string.o \
	  vga.o \
	  gdt.o \
	  pic.o 

run: kernel.bin
	qemu-system-x86_64 -kernel $<

kernel.bin: $(OBJ_FILES)
	ld -melf_i386 -T linker.ld $^ -o $@

loader.o: loader.s
	nasm -f elf $< -o $@

%.o: %.c
	gcc -c $< -m32 -ffreestanding -fno-stack-protector -o $@


clean:
	rm *.o *.bin
