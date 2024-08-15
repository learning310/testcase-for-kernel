ifneq ($(KERNELRELEASE),)
obj-m :=qemu_pci_serial.o
else
KDIR := ../

EXTRA_CFLAGS = -g -O0 -ggdb

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers

endif

