run: kernel.bin
	qemu-system-x86_64 -kernel $<

kernel.bin: kernel.o loader.o memory.o vga.o
	ld -melf_i386 -T linker.ld $^ -o $@

memory.o: memory.c
	gcc -c $< -m32 -ffreestanding -o $@

vga.o: vga.c
	gcc -c $< -m32 -ffreestanding -o $@

kernel.o: kernel.c
	gcc -c $< -m32 -ffreestanding -o $@

loader.o: loader.s
	nasm -f elf $< -o $@

clean:
	rm *.o *.bin
