
#pragma once
#include"cJSON.h"
struct MemoryStruct {
    char* memory;
    size_t size;
};
cJSON* getexchangerate(void);