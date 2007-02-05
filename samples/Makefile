CC     = g++
CFLAGS = -Wall -pedantic -s -O2 -I.. 


.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $<


all: uint int


uint: uint.o
	$(CC) -o uint $(CFLAGS) uint.o

int: int.o
	$(CC) -o int $(CFLAGS) int.o


uint.o:		uint.cpp
int.o:		int.cpp


clean:
	rm -f *.o
	rm -f *.s
	rm -f uint
	rm -f int
	rm -f *.exe
