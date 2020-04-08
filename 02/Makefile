CC=g++
CFLAGS=-Wall -std=c++14 -O0
NAME=libparser.a

all: $(NAME)

$(NAME): parser.o
	ar rc libparser.a parser.o

parser.o: parser.cpp parser.h 
	$(CC) $(CFLAGS) -c parser.cpp

clean:
	rm -rf *.o $(NAME) test.exe vgcheck.exe
	
test: $(NAME) test.exe
	./test.exe $(NAME)

test.exe: test.o libparser.a
	$(CC) -o test.exe test.o -L. -lparser

test.o: test.cpp
	$(CC) -c test.cpp

vgcheck: $(NAME) test.exe
	valgrind --tool=memcheck --leak-check=full -s ./test.exe $(NAME)
	
