#ifndef ALLOCATOR_H
#define ALLOCATOR_H

using borderCallback = void (*)();
using onNumberCallback = void (*)(long long);
using onStringCallback = void (*)(const char *);

void register_on_begin_callback(borderCallback);
void register_on_end_callback(borderCallback);
void register_on_number_callback(onNumberCallback);
void register_on_string_callback(onStringCallback);

void parse(const char *);

#endif