CC=g++
CFLAGS=-Wall -std=c++17 -O2
PROJECT=vector
LIBNAME=lib$(PROJECT).a

all: $(LIBNAME)

$(LIBNAME): $(PROJECT).h  
	ar rc $(LIBNAME) $(PROJECT).h 

clean:
	rm -rf *.o $(LIBNAME) test.exe
	
test: $(LIBNAME) test.exe
	./test.exe $(LIBNAME)

test.exe: test.o $(LIBNAME)
	$(CC) -o test.exe test.o -L -l$(PROJECT)

test.o: test.cpp
	$(CC) -c test.cpp
	
vgcheck: $(LIBNAME) test.exe
	valgrind --tool=memcheck --leak-check=full -s ./test.exe $(LIBNAME)
