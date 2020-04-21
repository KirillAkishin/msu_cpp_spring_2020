CC=g++
CFLAGS=-Wall -std=c++14 -O2
PROJECT=serializer
LIBNAME=lib$(PROJECT).a

all: $(LIBNAME)

$(LIBNAME): serializer.o deserializer.o
	ar rc $(LIBNAME) serializer.o deserializer.o

serializer.o: serializer.cpp serializer.h 
	$(CC) $(CFLAGS) -c serializer.cpp

deserializer.o: deserializer.cpp deserializer.h 
	$(CC) $(CFLAGS) -c deserializer.cpp

clean:
	rm -rf *.o $(LIBNAME) test.exe
	
test: $(LIBNAME) test.exe
	./test.exe $(LIBNAME)

test.exe: test.o $(LIBNAME)
	$(CC) -o test.exe test.o -L. -l$(PROJECT)

test.o: test.cpp
	$(CC) -c test.cpp
	
vgcheck: $(LIBNAME) test.exe
	valgrind --tool=memcheck --leak-check=full -s ./test.exe $(LIBNAME)
