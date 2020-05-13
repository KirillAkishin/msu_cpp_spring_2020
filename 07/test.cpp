#include <iomanip>
#include <iostream>
#include <vector>

#include "vector.h"


using tcase = int (*)();
std::vector<tcase> testCases = 
    {
        // resize() test
        []() 
        {
            vector<int> vec = {1,2,3};
            vec.resize(6, 42);
            vector<int> answer = {1,2,3,42,42,42};
            if (vec != answer) {
                return 1;
            }
            return 0;
        },
        // pop_back() test
        []() 
        {
            vector<int> vec = {1,2,3};
            vec.pop_back();
            vec.pop_back();
            vector<int> answer = {1};
            if (vec != answer) {
                return 1;
            }
            return 0;
        },
        // push_back() test
        []() 
        {
            vector<char> vec = {'t', 'e'};
            vec.push_back('5');
            vec.push_back('t');
            vector<char> answer = {'t', 'e', '5', 't'};
            if (vec != answer) {
                return 1;
            }
            return 0;
        },
        // erase() test
        []() 
        {
            vector<char> vec = {'t', 'e', 's', 't'};
            vec.erase(vec.begin()+2);
            vector<char> answer = {'t', 'e', 't'};
            if (vec != answer) {
                return 1;
            }
            return 0;
        },
        // strings test
        []() 
        {
            vector<std::string> vec(3, "test_string");
            vec.push_back("new_string");
            vec.resize(6, "empyt_string");
            vector<std::string> answer = {"test_string", "test_string", "test_string",
                                            "new_string", "empyt_string", "empyt_string"};
            if (vec != answer) {
                return 1;
            }
            vec.clear();
            if (!vec.empty()) {
                return 1;
            }
            return 0;
        },
        // iterator test
        []() 
        {
            int i = 5;
            int j = 6;
            Iterator<int> iter1(&i);
            Iterator<int> iter2(&j);
            swap(iter1, iter2);
            iter2 -= 6;
            iter2 = 6 + iter2;
            Iterator<int> answer(&i);
            if (iter2 != answer){
                return 1;
            }
            if (!iter2[1] == *(iter2+1)){
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





