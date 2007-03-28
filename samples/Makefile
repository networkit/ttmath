CC     = g++
CFLAGS = -Wall -pedantic -s -O2 -I.. 


.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $<


all: uint int big parser


uint: uint.o
	$(CC) -o uint $(CFLAGS) uint.o

int: int.o
	$(CC) -o int $(CFLAGS) int.o

big: big.o
	$(CC) -o big $(CFLAGS) big.o

parser: parser.o
	$(CC) -o parser $(CFLAGS) parser.o


uint.o:		uint.cpp
int.o:		int.cpp
big.o:		big.cpp
parser.o:	parser.cpp


clean:
	rm -f *.o
	rm -f *.s
	rm -f uint
	rm -f int
	rm -f big
	rm -f parser
# on MS Windows can automatically be added suffixes .exe to the names of output programs
	rm -f *.exe
