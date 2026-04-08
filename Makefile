CROSS = arm-none-eabi-
CPU = arm1176jzf-s
OUTPUT_DIR = build
all: kernel.img


create_dir:
	mkdir -p $(OUTPUT_DIR)

boot.o: boot.s create_dir
	$(CROSS)as -mcpu=$(CPU) -o $(OUTPUT_DIR)/boot.o boot.s

kernel.o: kernel.c create_dir
	$(CROSS)gcc -mcpu=$(CPU) -ffreestanding -nostdlib -c kernel.c -o $(OUTPUT_DIR)/kernel.o

kernel.elf: boot.o kernel.o linker.ld
	$(CROSS)ld -T linker.ld -o $(OUTPUT_DIR)/kernel.elf $(OUTPUT_DIR)/boot.o $(OUTPUT_DIR)/kernel.o

kernel.img: kernel.elf
	$(CROSS)objcopy $(OUTPUT_DIR)/kernel.elf -O binary $(OUTPUT_DIR)/kernel.img

clean:
	rm -rf $(OUTPUT_DIR)

deploy:
	sudo mount /dev/sdb1 /mnt
	sudo cp $(OUTPUT_DIR)/kernel.img /mnt/
	sudo umount /mnt
