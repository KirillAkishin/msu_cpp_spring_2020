// #include <iostream>
#include <cassert>
#include <sstream>
#include <vector>

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

struct anotherData
{
    bool a;
    uint64_t b;
    uint64_t c;
    bool d;
    bool e;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, e);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c, d, e);
    }
};


using tcase = int (*)();
std::vector<tcase> testCases = 
    {
        []() 
        {
            //standard case
            Data x { 1, true, 2 };
            std::stringstream stream;
            Serializer serializer(stream);
            serializer.save(x);

            Data y { 0, false, 0 };
            Deserializer deserializer(stream);
            const Error err = deserializer.load(y);

            // std::cout << y.a << " " << y.b << " " << y.c <<std::endl;
            if ((err != Error::NoError) || 
                (x.a != y.a) ||
                (x.b != y.b) ||
                (x.c != y.c) )
                {
                    return 1;
                }
            return 0;
        },
        []() 
        {
            //deserializer from stream
            std::stringstream stream;
            stream << '1' << ' ';
            stream << "false" << ' ';
            stream << "23";

            Data y { 0, true, 0 };
            Deserializer deserializer(stream);
            const Error err = deserializer.load(y);

            // std::cout << y.a << " " << y.b << " " << y.c <<std::endl;
            if ((err != Error::NoError) || 
                (1 != y.a) ||
                (false != y.b) ||
                (23 != y.c) )
                {
                    return 1;
                }
            return 0;
        },
        []() 
        {
            //corrupted bool
            std::stringstream stream;
            stream << '1' << ' ';
            stream << "1" << ' ';
            stream << '2';

            Data y { 0, false, 0 };
            Deserializer deserializer(stream);
            const Error err = deserializer.load(y);

            // std::cout << y.a << " " << y.b << " " << y.c <<std::endl;
            if (err != Error::CorruptedArchive)
                {
                    return 1;
                }
            return 0;
        },
        []()
        {
            //corrupted uint64_t (1)
            std::stringstream stream;
            stream << '1' << ' ';
            stream << "true" << ' ';
            stream << "-2";

            Data y { 0, false, 0 };
            Deserializer deserializer(stream);
            const Error err = deserializer.load(y);

            // std::cout << y.a << " " << y.b << " " << y.c <<std::endl;
            if (err != Error::CorruptedArchive)
                {
                    return 1;
                }
            return 0;
        },
        []()
        {
            //corrupted uint64_t (2)
            std::stringstream stream;
            stream << '1' << ' ';
            stream << "true" << ' ';
            stream << "broken_format";

            Data y { 0, false, 0 };
            Deserializer deserializer(stream);
            const Error err = deserializer.load(y);

            // std::cout << y.a << " " << y.b << " " << y.c <<std::endl;
            if (err != Error::CorruptedArchive)
                {
                    return 1;
                }
            return 0;
        },
        []()
        {
            //anotherData test
            anotherData x { true, 1, 2, false, true };
            std::stringstream stream;
            Serializer serializer(stream);
            serializer.save(x);

            anotherData y { false, 0, 0, false, false };
            Deserializer deserializer(stream);
            const Error err = deserializer.load(y);

            if ((err != Error::NoError) ||
                (x.a != y.a) ||
                (x.b != y.b) ||
                (x.c != y.c) ||
                (x.d != y.d) ||
                (x.e != y.e))
                {
                    return 1;
                }
            return 0;
        },
    };

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("test.exe run incorrectly\n");
        return 1;
    }

    printf("\nTesting started...\n");
    int testCounter = 0;
    int status;
    for (auto& func : testCases)
    {
        testCounter++;
        status = func();
        if (status != 0)
        {
            printf("Test number (%i) failed with status: %i\n", testCounter, status);   
            return 1;
        }
    }
    printf("All tests passed!\n");   
    return 0;
}
