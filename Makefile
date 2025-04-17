CROSS_COMPILE = arm-none-eabi-
AS      = $(CROSS_COMPILE)as
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS  = -ffreestanding -O2 -Wall -Wextra -Iinclude/
LDFLAGS = -T linker.ld

SRC     = src
OBJ     = obj

OBJS    = $(OBJ)/boot.o $(OBJ)/kernel.o $(OBJ)/uart.o

all: kernel.elf kernel.img

# Create obj folder if needed
$(OBJ):
	mkdir -p $(OBJ)

# Compile .S file
$(OBJ)/boot.o: $(SRC)/boot.S | $(OBJ)
	$(AS) $< -o $@

# Compile .c files
$(OBJ)/kernel.o: $(SRC)/kernel.c | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ)/uart.o: $(SRC)/uart.c | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

# Link everything into kernel.elf
kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Convert ELF to raw image (if you want to boot on real Pi later)
kernel.img: kernel.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(OBJ) *.elf *.img


