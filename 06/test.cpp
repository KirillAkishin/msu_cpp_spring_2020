#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>

#include "format.h"


#define checkEqual(x, y) \
    do { \
        if ((x) != (y)) \
        { \
            return 1; \
        }; \
        return 0; \
    } while(0)

#define checkThrow(x) \
    do { \
        try { (x); } \
        catch (const std::runtime_error&) { return 0; } \
        catch (...) {} \
        return 1; \
    } while(0)

struct Test
{
};

std::ostream& operator<<(std::ostream& out, const Test&)
{
    out << "test";
    return out;
}

const Test test;
using tcase = int (*)();
std::vector<tcase> testCases = 
    {
        []() { checkEqual(format(""), ""); },
        []() { checkEqual(format("1"), "1"); },
        []() { checkEqual(format("{1}", 1, 2), "2"); },
        []() { checkEqual(format("{0}{0}", "a"), "aa"); },
        []() { checkEqual(format("{0}", Test()), "test"); },
        []() { checkEqual(format("{0}", const_cast<Test&>(test)), "test"); },
        []() { checkEqual(format("{0}", test), "test"); },

        []() { checkThrow(format("{", 1)); },
        []() { checkThrow(format("{0", 1)); },
        []() { checkThrow(format("}", 1)); },
        []() { checkThrow(format("{1}", 1)); },
        []() { checkThrow(format("{0}{1}{3}", 1, 2)); },
        []() { checkThrow(format("{0{}", 1)); },
        []() { checkThrow(format("{0a}", 1)); },
        []() { checkThrow(format("0}", 1)); },
        []() { checkThrow(format("{{0}", 1)); },
     };

int main(int argc, char* argv[]){
    if (argc != 1){
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


