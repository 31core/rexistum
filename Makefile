MAKE=make
NASN=nasm
LD=ld
QEMU=qemu-system-i386

ARCH=arch/x86

BINS=$(ARCH)/kernel/_start.bin\
$(ARCH)/kernel/asmfunc.bin
OBJS=init/main.o\
$(ARCH)/kernel/graphics.o\
$(ARCH)/kernel/dsctbl.o\
kernel/string.o

default:
	$(MAKE) -C $(ARCH)/boot
	$(MAKE) -C $(ARCH)/kernel
	$(MAKE) -C kernel
	$(MAKE) -C init
	$(MAKE) image
#系统内核文件
kernel.sys:
	$(LD) -m elf_i386 -e _start -Ttext 0x100000 $(BINS) $(OBJS) -o kernel.sys
#内核镜像
image:kernel.sys
	dd if=$(ARCH)/boot/boot.bin of=hda.img bs=512 count=1
	dd if=$(ARCH)/boot/loader.bin of=hda.img bs=512 seek=1 count=8
	dd if=kernel.sys of=hda.img bs=512 seek=9 count=348

run:
	$(MAKE) default
	$(QEMU) -hda hda.img

clean:
	rm hda.img
	rm kernel.sys
	$(MAKE) -C $(ARCH)/boot clean
	$(MAKE) -C $(ARCH)/kernel clean
	$(MAKE) -C kernel clean
	$(MAKE) -C init clean
	