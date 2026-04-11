CROSS = arm-none-eabi-
CPU = arm1176jzf-s
OUTPUT_DIR = build

C_FILES = $(wildcard *.c)
C_OBJECTS = $(patsubst %.c,$(OUTPUT_DIR)/%.o,$(C_FILES))

all: clean $(OUTPUT_DIR)/kernel.img

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/boot.o: boot.s | $(OUTPUT_DIR)
	$(CROSS)as -mcpu=$(CPU) -o $@ boot.s

$(OUTPUT_DIR)/context_switch.o: context_switch.s | $(OUTPUT_DIR)
	$(CROSS)as -mcpu=$(CPU) -o $@ context_switch.s

$(OUTPUT_DIR)/%.o: %.c | $(OUTPUT_DIR)
	$(CROSS)gcc -mcpu=$(CPU) -ffreestanding -nostdlib -c $< -o $@

$(OUTPUT_DIR)/kernel.elf: $(OUTPUT_DIR)/boot.o $(OUTPUT_DIR)/context_switch.o $(C_OBJECTS) linker.ld
	$(CROSS)ld -T linker.ld -o $@ $(OUTPUT_DIR)/boot.o -o $@ $(OUTPUT_DIR)/context_switch.o $(C_OBJECTS)

$(OUTPUT_DIR)/kernel.img: $(OUTPUT_DIR)/kernel.elf
	$(CROSS)objcopy $< -O binary $@

clean:
	rm -rf $(OUTPUT_DIR)

debug:
	sudo minicom -b 115200 -D /dev/ttyUSB0

run: all
	qemu-system-arm -M raspi0 -nographic -kernel $(OUTPUT_DIR)/kernel.elf

deploy: all
	sudo mount /dev/sdb1 /mnt
	sudo cp $(OUTPUT_DIR)/kernel.img /mnt/
	sudo cp config.txt /mnt/
	sudo umount /mnt
