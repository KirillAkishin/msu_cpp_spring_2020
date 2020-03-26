CC=g++
CFLAGS=-Wall -std=c++14 -O2
NAME=libmatrix.a

all: $(NAME)

$(NAME): matrix.o
	ar rc libmatrix.a matrix.o

matrix.o: matrix.cpp matrix.h 
	$(CC) $(CFLAGS) -c matrix.cpp

clean:
	rm -rf *.o $(NAME) test.exe TEST_FILE.txt
	
test: $(NAME) test.exe
	./test.exe $(NAME)

test.exe: test.o libmatrix.a
	$(CC) -o test.exe test.o -L. -lmatrix

test.o: test.cpp
	$(CC) -c test.cpp
	
