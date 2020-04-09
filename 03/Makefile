CC=g++
CFLAGS=-Wall -std=c++14 -O2
PROJECT=matrix
NAME=lib$(PROJECT).a

all: $(NAME)

$(NAME): $(PROJECT).o
	ar rc $(NAME) $(PROJECT).o

$(PROJECT).o: $(PROJECT).cpp $(PROJECT).h 
	$(CC) $(CFLAGS) -c $(PROJECT).cpp

clean:
	rm -rf *.o $(NAME) test.exe TEST_FILE.txt
	
test: $(NAME) test.exe
	./test.exe $(NAME)

test.exe: test.o $(NAME)
	$(CC) -o test.exe test.o -L. -l$(PROJECT)

test.o: test.cpp
	$(CC) -c test.cpp
	
vgcheck: $(NAME) test.exe
	valgrind --tool=memcheck --leak-check=full -s ./test.exe $(NAME)
