CC=g++
CFLAGS=-Wall -std=c++14 -O2
NAME=liballocator.a

all: $(NAME)

$(NAME): allocator.o
	ar rc liballocator.a allocator.o

allocator.o: allocator.cpp allocator.h 
	$(CC) $(CFLAGS) -c allocator.cpp

clean:
	rm -rf *.o $(NAME) test.exe
	
test: $(NAME) test.exe
	./test.exe $(NAME)

test.exe: test.o liballocator.a
	$(CC) -o test.exe test.o -L. -lallocator

test.o: test.cpp
	$(CC) -c test.cpp
	
