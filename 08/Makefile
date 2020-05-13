CC=g++ -std=c++17
CFLAGS=-Wall -O2 -pthread
PROJECT=threadpool

all: test

test: test.exe
	./test.exe

test.exe: $(PROJECT).o test.o
	$(CC) $(CFLAGS) $(PROJECT).o test.o -o test.exe

test.o: test.cpp
	$(CC) -c test.cpp

$(PROJECT).o: $(PROJECT).cpp $(PROJECT).hpp
	$(CC) -c $(PROJECT).cpp

clean:
	rm -rf *.o $(LIBNAME) test.exe

