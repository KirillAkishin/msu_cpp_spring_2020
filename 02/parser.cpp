#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <map>

#include "parser.h"

borderCallback onBegin_callback;
borderCallback onEnd_callback;
onNumberCallback onNumber_callback;
onStringCallback onString_callback;

void register_on_begin_callback (borderCallback function){
    onBegin_callback = function ;
}

void register_on_end_callback (borderCallback function){
    onEnd_callback = function ;
}

void register_on_number_callback (onNumberCallback function){
    onNumber_callback = function ;
}

void register_on_string_callback (onStringCallback function){
    onString_callback = function ;
}


void onBegin(){
    if (onBegin_callback != nullptr){
        onBegin_callback();
    }
}

void onEnd(){
    if (onEnd_callback != nullptr){
        onEnd_callback();
    }
}

void onNumber(long long number){
    if (onNumber_callback != nullptr){
        onNumber_callback(number);
    }
}

void onString(char * str){
    if (onString_callback != nullptr){
        onString_callback(str);
    }
}


void parse(const char * text){
    const size_t buffer_size = strlen(text);
    char *word = new char[buffer_size];
    std::stringstream x;       
    x << text;              
    std::string number = "";  
 
    onBegin();
    while (x >> word){
        char tokenCat;
        char c = word[0];
        if (isdigit(c)){
            tokenCat = 'n';
            number = c;
            size_t word_size = strlen(word);
            for (size_t i = 1; i < word_size; i++){
                c = word[i];
                if ( !isdigit(c) && (tokenCat != 's') ) {
                    tokenCat = 's';
                    break;
                }
                number = number + c;
            } 
        } else {
            tokenCat = 's';
        }

        switch (tokenCat)
        {
        case 's':
            onString(word);
            break;
        case 'n':
            onNumber(atoi(number.c_str()));
            break;
        default:
            continue;
        }
    }
    onEnd();
    delete[] word;
}