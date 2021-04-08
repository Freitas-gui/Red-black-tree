all:teste

teste:	main.o RBT.o
	gcc -o teste main.o RBT.o

main.o: main.c RBT.h
	gcc -c main.c

RBT.o: RBT.c RBT.h
	gcc -c RBT.c

clean:
	rm main.o RBT.o teste
