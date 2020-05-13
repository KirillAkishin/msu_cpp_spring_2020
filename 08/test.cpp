 #include "threadpool.hpp"
 #include <iostream>


using tcase = int (*)();
std::vector<tcase> testCases = 
    {
        []() 
        {
            ThreadPool pool(8);
            int a = 42;
            auto task1 = [a](int c) { return a*c; };
            auto res = pool.exec(task1,2);
            int answer = 84;
            if (res.get() != answer){
                return 1;
            }
            return 0;
        },
        []() 
        {
            ThreadPool pool(8);
            int a = 42;
            int b = -10;
            auto task2 = [a,b]() { return a + b; };            
            auto res = pool.exec(task2);
            int answer = 32;
            if (res.get() != answer){
                return 1;
            }
            return 0;
        },
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


