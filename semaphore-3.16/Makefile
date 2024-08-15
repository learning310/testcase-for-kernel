KDIR :=../
obj-m := semaphore_test.o
EXTRA_CFLAGS += -fno-pie

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers

