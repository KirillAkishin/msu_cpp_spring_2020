// #include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>

#include "bigint.h"


using tcase = int (*)();
std::vector<tcase> testCases = 
    {
        // 1) add test 
        []() 
        {
            BigInt bint_1 = "-42";
            BigInt bint_2 = "10";
            BigInt result = bint_1 + bint_2;
            BigInt answer = "-32";
            if (result != answer){
                return 1;
            }
            return 0;
        },
        // 2) subtraction test
        []() 
        {
            BigInt bint_1 = "-42";
            BigInt bint_2 = "10";
            BigInt result = bint_1 - bint_2;
            BigInt answer = "-52";
            if (result != answer){
                return 1;
            }
            return 0;
        },
        // 3) less test
        []() 
        {
            BigInt bint_1 = "-42";
            BigInt bint_2 = "10";
            bool result = bint_1 < bint_2;
            bool answer = true;
            if (result != answer){
                return 1;
            }
            return 0;
        },
        // 4) more test
        []() 
        {
            BigInt bint_1 = "-42";
            BigInt bint_2 = "10";
            bool result = bint_1 > bint_2;
            bool answer = false;
            if (result != answer){
                return 1;
            }
            return 0;
        },
        // 5) lesseq test
        []() 
        {
            BigInt bint_1 = "-42";
            BigInt bint_2 = "10";
            bool result = bint_1 <= bint_2;
            bool answer = true;
            if (result != answer){
                return 1;
            }
            bint_1 = "-42";
            bint_2 = "-42";
            result = bint_1 <= bint_2;
            answer = true;
            if (result != answer){
                return 1;
            }
            return 0;
        },
        // 6) moreeq test
        []() 
        {
            BigInt bint_1 = "-42";
            BigInt bint_2 = "10";
            bool result = bint_1 >= bint_2;
            bool answer = false;
            if (result != answer){
                return 1;
            }
            bint_1 = "-42";
            bint_2 = "-42";
            result = bint_1 >= bint_2;
            answer = true;
            if (result != answer){
                return 1;
            }
            return 0;
        },
        // 7) unary minus test
        []() 
        {
            BigInt bint = "-42";
            BigInt result = -bint;
            BigInt answer = "42";
            if (result != answer){
                return 1;
            }
            return 0;
        },
        // 8) output stream
        []() 
        {
            std::stringstream stream;
            BigInt bint = "-42";
            std::string result = "0";        
            stream << bint;
            stream >> result;
            if (result != "-42"){
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
