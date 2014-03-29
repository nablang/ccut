libccut.a: ccut.c ccut.h
	cc -std=c11 -c ccut.c
	ar rcs libccut.a ccut.o

test: example.c ccut.c ccut.h
	cc -std=c11 example.c -L. -lccut
	./a.out
