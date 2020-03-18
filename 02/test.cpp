#include <iostream>

#include "parser.h"

int testCases(char * name){
    int testNumber = 0;
    const char * text = "TEST STRING: 1231 adsd 22wd\n4\t 52d31231231231233!";

    //T1 - standart work
    testNumber++;
    parse(text);

    //T2 - standart work for register_on_begin_callback()
    testNumber++;
    register_on_begin_callback([](){TEST_FILE = 2;});
    parse(text);
    if (TEST_FILE != testNumber)
        return testNumber;
    register_on_begin_callback([](){});

    //T3 - standart work for register_on_end_callback()
    testNumber++;
    register_on_end_callback([](){TEST_FILE = 3;});
    parse(text);
    if (TEST_FILE != testNumber)
        return testNumber;
    register_on_end_callback([](){});

    //T4 - standart work for register_on_number_callback()
    testNumber++;
    register_on_number_callback([](const char * number){TEST_FILE = number[0];});
    parse(text);
    if (TEST_FILE != '4')
        return testNumber;

    //T5 - standart work for register_on_string_callback()
    testNumber++;
    register_on_string_callback([](const char * str){TEST_FILE = str[0];});
    parse(text);
    if (TEST_FILE != '5')
        return testNumber;

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
