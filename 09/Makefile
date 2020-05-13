CC=g++ -std=c++14
CFLAGS=-Wall -O2 -pthread
PROJECT=sort


all: test

test: test.exe
	./test.exe

test.exe: $(PROJECT).o test.o
	$(CC) $(CFLAGS) $(PROJECT).o test.o -o test.exe

test.o: test.cpp
	$(CC) -c test.cpp

$(PROJECT).o: $(PROJECT).cpp $(PROJECT).h
	$(CC) -c $(PROJECT).cpp

clean:
	rm -rf *.o test.exe *.dat