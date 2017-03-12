o      = main.o
CC     = clang++
CFLAGS = -O2 -DTTMATH_CONSTANTSGENERATOR
name   = gen


.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $<


all: $(name)

$(name): $(o)
	$(CC) -o $(name) -s $(CFLAGS) $(o)



main.o: main.cpp


clean:
	rm -f *.o
	rm -f *.s
	rm -f $(name)
	rm -f $(name).exe
