all:
	gcc -Os cc.c -o cc
view:
	./cc
	objdump -D -Mintel,x86-64 -b binary -m i386 o
