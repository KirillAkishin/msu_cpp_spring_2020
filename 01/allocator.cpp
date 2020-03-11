#include <cstdio>

char* ptrStart = nullptr;
char* ptrCurr = nullptr;
long unsigned int maxBufSize = 0;

void makeAllocator(size_t maxSize){
    ptrCurr = new char[maxSize];
    ptrStart = ptrCurr;
    maxBufSize = maxSize;
    return;
}

char* alloc(size_t size){
    if (ptrCurr == nullptr){
        return nullptr;
    }
    std::ptrdiff_t filled = ptrCurr - ptrStart;
    if (filled + size > maxBufSize){
        return nullptr;
    }
    char* ptrReturn = ptrCurr;
    ptrCurr += size;
    return ptrReturn;
}

void reset(){
    ptrCurr = ptrStart;
    return;
}

void deleteAllocator(){
    delete[] ptrStart;
    return;
}
