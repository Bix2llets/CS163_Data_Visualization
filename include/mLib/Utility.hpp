#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "raylib.h"

namespace mLib
{
    inline void GenerateRandomText(char *text) {
        int length = GetRandomValue(1, 10) % 10 + 1;
        for (int i = 0; i < length; i++) {
            text[i] = (GetRandomValue(1, 1000000000) % 26) + 'A';  
        }
        text[length] = '\0'; 
    }
}   

#endif // #UTILITY_HPP