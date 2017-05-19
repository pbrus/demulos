# A simple makefile of the demulos program written in C
# https://github.com/pbrus/demulos

PROG = demulos
OBJ = main.o demulos.o file.o comm.o
LIB = lib/demulos.h lib/file.h lib/comm.h
CC = gcc
CFLAGS = -lm -O2 -Wall

$(PROG) : $(OBJ)
		$(CC) -o $@ $(OBJ) $(CFLAGS)

main.o : src/main.c $(LIB)
		$(CC) -c $< -o $@ $(CFLAGS)

demulos.o : src/demulos.c lib/demulos.h
		$(CC) -c $< -o $@ $(CFLAGS)

file.o : src/file.c lib/file.h
		$(CC) -c $< -o $@ $(CFLAGS)

comm.o : src/comm.c lib/comm.h
		$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean :
		rm -f $(OBJ)
