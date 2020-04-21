// #include <iostream>
#include <cassert>
#include <sstream>

#include "serializer.h"
#include "deserializer.h"


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

int testCases(char * name){
    Data x { 77777777773, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);


    Data y { 7, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    // std::cout << y.a << " " << y.b << " " << y.c <<std::endl;

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    return 0;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("test.exe run incorrectly\n");
        return 0;
    }
    char* name = argv[1];

    printf("\nTesting started...\n");
    int status = testCases(name);
    if (status != 0){
        printf("Test number %i failed\n", status);   
        return 1;
    }
    printf("All tests passed!\n");   
    return 0;
}
