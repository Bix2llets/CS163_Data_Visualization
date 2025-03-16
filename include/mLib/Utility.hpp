#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "raylib.h"

namespace mLib
{
    inline void GenerateRandomText(char *text) {
        int length = GetRandomValue(1, 10) % 5 + 1;
        for (int i = 0; i < length; i++) {
            text[i] = (GetRandomValue(1, 1000000000) % 26) + 'A';  
        }
        text[length] = '\0'; 
    }
    inline void GenerateRandomNum(char *text) {
        int length = GetRandomValue(1, 10) % 3 + 1;
        for (int i = 0; i < length; i++) {
            text[i] = (GetRandomValue(1, 1000000000) % 10) + '0';  
        }
        text[length] = '\0'; 
    }
    extern Font mFont;
    inline void InitFont(const char *path) {
        mFont = LoadFont(path);
    }
    extern const char *TrieInsert[15];
    extern const char *TrieSearch[15];
    extern const char *TrieDelete[15];
    inline void DrawTextTrie(int index) {
        for (int i = 0; i < 12; i ++) DrawRectangle(1200, 300 + 40 * i, 350, 40, Fade(RED, 0.3f));
        if (index <= 5) {
            if (index == 0) DrawRectangle(1200, 300, 350, 40, Fade(GREEN, 0.3f));
            if (index == 1) DrawRectangle(1200, 300 + 40, 350, 40, Fade(GREEN, 0.3f));
            if (index == 2) {
                DrawRectangle(1200, 300 + 120, 350, 40, Fade(GREEN, 0.3f));
                DrawRectangle(1200, 300 + 160, 350, 40, Fade(GREEN, 0.3f));
            }
            if (index == 3) DrawRectangle(1200, 300 + 200 , 350, 40, Fade(GREEN, 0.3f));
            if (index == 4) DrawRectangle(1200, 300 + 240, 350, 40, Fade(GREEN, 0.3f));
            if (index == 5) DrawRectangle(1200, 300 + 280, 350, 40, Fade(GREEN, 0.3f));
            for (int i = 0; i < 12; i++) DrawTextEx(mFont, TrieInsert[i], (Vector2){1200, 300 + 40 * i}, 20, 2, BLACK);
        }
        else
            if (index <= 10) {
                if (index == 6) DrawRectangle(1200, 300, 350, 40, Fade(GREEN, 0.3f));
                if (index == 7) DrawRectangle(1200, 300 + 40, 350, 40, Fade(GREEN, 0.3f));
                if (index == 8) {
                    DrawRectangle(1200, 300 + 120, 350, 40, Fade(GREEN, 0.3f));
                    DrawRectangle(1200, 300 + 160, 350, 40, Fade(GREEN, 0.3f));
                }
                if (index == 9) DrawRectangle(1200, 300 + 200 , 350, 40, Fade(GREEN, 0.3f));
                if (index == 10) DrawRectangle(1200, 300 + 240, 350, 40, Fade(GREEN, 0.3f));
                for (int i = 0; i < 12; i++) DrawTextEx(mFont, TrieSearch[i], (Vector2){1200, 300 + 40 * i}, 20, 2, BLACK);
            }
            else {
                if (index == 11) DrawRectangle(1200, 300, 350, 40, Fade(GREEN, 0.3f));
                if (index == 12) DrawRectangle(1200, 300 + 40, 350, 40, Fade(GREEN, 0.3f));
                if (index == 13) {
                    DrawRectangle(1200, 300 + 120, 350, 40, Fade(GREEN, 0.3f));
                    DrawRectangle(1200, 300 + 160, 350, 40, Fade(GREEN, 0.3f));
                }
                if (index == 14) DrawRectangle(1200, 300 + 200 , 350, 40, Fade(GREEN, 0.3f));
                if (index == 15) DrawRectangle(1200, 300 + 240, 350, 40, Fade(GREEN, 0.3f));
                if (index == 16) DrawRectangle(1200, 300 + 360, 350, 40, Fade(GREEN, 0.3f));
                if (index == 17) DrawRectangle(1200, 300 + 400, 350, 40, Fade(GREEN, 0.3f));
                if (index == 18) DrawRectangle(1200, 300 + 440, 350, 40, Fade(GREEN, 0.3f));
                for (int i = 0; i < 12; i++) DrawTextEx(mFont, TrieDelete[i], (Vector2){1200, 300 + 40 * i}, 20, 2, BLACK);
            }
    }
}   

#endif // #UTILITY_HPP