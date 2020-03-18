#ifndef ALLOCATOR_H
#define ALLOCATOR_H

using borderCallback = void (*)();
using tokenCallback = void (*)(const char *);

void register_on_begin_callback(borderCallback);
void register_on_end_callback(borderCallback);
void register_on_number_callback(tokenCallback);
void register_on_string_callback(tokenCallback);

void parse(const char *);

extern char TEST_FILE; 

#endif