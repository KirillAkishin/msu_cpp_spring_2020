#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "parser.h"


int testCases(char * name){
    int testNumber = 0;
    const char * text = "TEST STRING: 1231 adsd 22wd\n4\t 52d31231231231233!";
    std::ofstream oFile ( "TEST_FILE.txt" ) ; 
    std::string textFromFile;
    std::string line;
    std::ifstream fin;

    //T1 - standart work
    testNumber++;
    parse(text);

    //T2 - standart work for register_on_begin_callback()
    testNumber++;
    register_on_begin_callback([](){
        std::ofstream fout("TEST_FILE.txt"); 
        fout << 2; 
        fout.close(); 
    });
    parse(text);
    fin.open("TEST_FILE.txt");
    if (fin.is_open())
    {
        while (getline(fin, line))
            textFromFile = textFromFile + line;   
    }
    fin.close();  
    if (textFromFile != "2")
        return testNumber;
    register_on_begin_callback([](){});
    textFromFile = "";

    //T3 - standart work for register_on_end_callback()
    testNumber++;
    register_on_end_callback([](){
        std::ofstream fout("TEST_FILE.txt"); 
        fout << 3; 
        fout.close(); 
    });
    parse(text);
    fin.open("TEST_FILE.txt");
    if (fin.is_open())
    {
        while (getline(fin, line)){
            textFromFile = textFromFile + line;   
        }
    }
    fin.close();  
    if (textFromFile != "3")
        return testNumber;
    register_on_end_callback([](){});
    textFromFile = "";
    
    //T4 - standart work for register_on_number_callback()
    testNumber++;
    register_on_number_callback([](long long number){
        std::ofstream fout("TEST_FILE.txt"); 
        fout << number; 
        fout.close(); 
    });
    parse(text);
    fin.open("TEST_FILE.txt");
    if (fin.is_open())
    {
        while (getline(fin, line)){
            textFromFile = textFromFile + line;   
        }
    }
    fin.close();  
    if (textFromFile != "4")
        return testNumber;
    register_on_number_callback([](long long x){});
    textFromFile = "";

    //T5 - standart work for register_on_string_callback()
    testNumber++;
    register_on_string_callback([](const char * str){
        std::ofstream fout("TEST_FILE.txt"); 
        fout << str; 
        fout.close(); 
    });
    parse(text);
    fin.open("TEST_FILE.txt");
    if (fin.is_open())
    {
        while (getline(fin, line)){
            textFromFile = textFromFile + line;   
        }
    }
    fin.close();  
    if (textFromFile != "52d31231231231233!")
        return testNumber;
    register_on_string_callback([](const char * x){});
    textFromFile = "";

    remove( "TEST_FILE.txt" );
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
