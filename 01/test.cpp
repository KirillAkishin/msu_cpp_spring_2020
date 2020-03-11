#include <iostream>

#include "allocator.h"

int testCases(char * name){
    int testNumber = 0;

    //T1 - standart work makeAllocator()
    testNumber++;
    makeAllocator(100);
    char* ptr1 = alloc(10);
    if (ptr1 == nullptr){
        return testNumber;
    }

    //T2 - standart work alloc()
    testNumber++;
    char* ptr2 = alloc(20);
    if ((ptr2 - ptr1 != 10) || (ptr2 == nullptr)){
        return testNumber;
    }

    //T3 - standart work reset()
    testNumber++;
    reset();
    ptr2 = alloc(100);
    if ((ptr2 != ptr1) || (ptr2 == nullptr)){
        return testNumber;
    }

    //T4 - buffer overflow
    testNumber++;
    reset();
    ptr1 = alloc(100);
    ptr2 = alloc(1);
    if (ptr2 != nullptr){
        return testNumber;
    }
    ptr1 = alloc(101);
    if (ptr1 != nullptr){
        return testNumber;
    }

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