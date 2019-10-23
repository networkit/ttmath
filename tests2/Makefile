#CC     = g++6
#CFLAGS = -Wall -pedantic -O3 -s -I.. -Wl,-rpath=/usr/local/lib/gcc6
#CFLAGS = -Wall -pedantic -O3 -DTTMATH_NOASM -s -I.. -Wl,-rpath=/usr/local/lib/gcc6

CC     = clang++
CFLAGS = -Wall -pedantic -O3 -s -I..
#CFLAGS = -Wall -pedantic -O3 -DTTMATH_NOASM -s -I..



.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $<




all: big_64_64 big_64_128 big_64_192 big_64_256 big_64_512 big_64_1024 big_64_2048 big_64_4096 big_128_512 big_256_1024 big_512_2048 big_128_4096






big_64_64: main.cpp
	$(CC) -o big_64_64 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=64 main.cpp

big_64_128: main.cpp
	$(CC) -o big_64_128 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=128 main.cpp

big_64_192: main.cpp
	$(CC) -o big_64_192 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=192 main.cpp

big_64_256: main.cpp
	$(CC) -o big_64_256 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=256 main.cpp

big_64_512: main.cpp
	$(CC) -o big_64_512 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=512 main.cpp

big_64_1024: main.cpp
	$(CC) -o big_64_1024 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=1024 main.cpp

big_64_2048: main.cpp
	$(CC) -o big_64_2048 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=2048 main.cpp

big_64_4096: main.cpp
	$(CC) -o big_64_4096 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=64 -DTTMATH_TEST_BIG_MANTISSA=4096 main.cpp

big_128_512: main.cpp
	$(CC) -o big_128_512 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=128 -DTTMATH_TEST_BIG_MANTISSA=512 main.cpp

big_256_1024: main.cpp
	$(CC) -o big_256_1024 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=256 -DTTMATH_TEST_BIG_MANTISSA=1024 main.cpp

big_512_2048: main.cpp
	$(CC) -o big_512_2048 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=512 -DTTMATH_TEST_BIG_MANTISSA=2048 main.cpp

big_128_4096: main.cpp
	$(CC) -o big_128_4096 -s $(CFLAGS) -DTTMATH_TEST_BIG_EXPONENT=128 -DTTMATH_TEST_BIG_MANTISSA=4096 main.cpp




test: all
	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=64"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_64 "foo" | tee big_64_64.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=128"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_128 "foo" | tee big_64_128.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=192"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_192 "foo" | tee big_64_192.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=256"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_256 "foo" | tee big_64_256.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=512"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_512 "foo" | tee big_64_512.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=1024"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_1024 "foo" | tee big_64_1024.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=2048"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_2048 "foo" | tee big_64_2048.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=64 and mantissa=4096"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_64_4096 "foo" | tee big_64_4096.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=128 and mantissa=512"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_128_512 "foo" | tee big_128_512.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=128 and mantissa=4096"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_128_4096 "foo" | tee big_128_4096.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=256 and mantissa=1024"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_256_1024 "foo" | tee big_256_1024.out

	@echo "****************************************************************************"
	@echo "making tests for exponent=512 and mantissa=2048"
	@echo "****************************************************************************"
	cat tests.txt | xargs -S 4096 -I foo ./big_512_2048 "foo" | tee big_512_2048.out

	./check_files.sh


clean:
	rm -f *.out
	rm -f big_64_64 big_64_128 big_64_192 big_64_256 big_64_512 big_64_1024 big_64_2048 big_64_4096 big_128_512 big_256_1024 big_512_2048 big_128_4096
# on MS Windows suffixes .exe will be automatically added
	rm -f *.exe
