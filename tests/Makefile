CC     = g++
o      = main.o uinttest.o
CFLAGS = -Wall -pedantic
ttmath = ..
name   = tests



.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) -I$(ttmath) $<


all: $(name)


$(name): $(o)
	$(CC) -o $(name) $(CFLAGS) -I$(ttmath) $(o)


main.o: main.cpp uinttest.h
uinttest.o: uinttest.cpp uinttest.h


clean:
	rm -f *.o
	rm -f $(name)
	rm -f $(name).exe


