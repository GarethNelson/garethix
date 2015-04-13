all: initrd.img

initrd.img: make_initrd 
	./make_initrd README.txt README.txt README2.txt README2.txt

make_initrd: make_initrd.c
	gcc make_initrd.c -o make_initrd

clean:
	-rm initrd.img make_initrd

