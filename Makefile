obj-m += os2.o

build:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm user

load:
	sudo insmod os2.ko
	sudo dmesg -c

unload:
	sudo rmmod os2.ko
	sudo dmesg -c

user:
	g++ *.cpp -o user

