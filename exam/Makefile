CC=g++ --std=c++14
CFLAGS = -c
NAME = counter

$(NAME).o: $(NAME).cpp $(NAME).h threadPool.h
	$(CC) $(CFLAGS) $(NAME).cpp

test.o: $(NAME).cpp $(NAME).h
	$(CC) $(CFLAGS) test.cpp

test.exe: $(NAME).o test.o
	$(CC) $(NAME).o test.o -o test.exe -lpthread

test: test.exe
	./test.exe

clean:
	rm -rf *.o test.exe