all: FileHandler.o Lib.o Lib.h
	gcc -o program FileHandler.o Lib.o

FileHandler.o: FileHandler.c Lib.h
	gcc -c FileHandler.c

Lib.o: Lib.c Lib.h
	gcc -c Lib.c
