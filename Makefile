obj-m := kworm.o

all:
	make -C $(shell echo $$WSLKERN) M=$(PWD) modules

clean:
	make -C $(shell echo $$WSLKERN) M=$(PWD) clean

bear:
	make clean ; bear -- make

