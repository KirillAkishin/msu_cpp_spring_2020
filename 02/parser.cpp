#include <iostream>
#include <sstream>
#include <cstring>
#include <map>

#include "parser.h"
char TEST_FILE;

std::map<char, borderCallback>  border_callback_map;
std::map<char, tokenCallback>   token_callback_map;

void register_on_begin_callback (borderCallback function){
    char event = 'b';
    border_callback_map[event] = function ;
}

void register_on_end_callback (borderCallback function){
    char event = 'e';
    border_callback_map[event] = function ;
}

void register_on_number_callback (tokenCallback function){
    char event = 'n';
    token_callback_map[event] = function ;
}

void register_on_string_callback (tokenCallback function){
    char event = 's';
    token_callback_map[event] = function ;
}


void onBegin(){
    if ( border_callback_map.find( 'b' ) != border_callback_map.end() ){
        border_callback_map['b']();
    }}

void onEnd(){
    if ( border_callback_map.find( 'e' ) != border_callback_map.end() ){
        border_callback_map['e']();
    }
}

void onNumber(char * number){
    if ( token_callback_map.find( 'n' ) != token_callback_map.end() ){
        token_callback_map['n'](number);
    }
}

void onString(char * str){
    if ( token_callback_map.find( 's' ) != token_callback_map.end() ){
        token_callback_map['s'](str);
    }
}


void parse(const char * text){
    const int N = strlen(text);
    char word[N] = {};
    std::stringstream x;       
    x << text;                
 
    onBegin();
    while (x >> word){
        char tokenCat;
        char c = word[0];
        if (isdigit(c)){
            tokenCat = 'n';
            for (long unsigned int i = 1; i < strlen(word); i++){
                c = word[i];
                if ( !isdigit(c) && (tokenCat != 's') ) {
                    tokenCat = 's';
                    break;
                }
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
            onNumber(word);
            break;
        default:
            continue;
        }
    }
    onEnd();
}