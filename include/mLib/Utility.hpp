#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "raylib.h"
#include "appMenu.h"
#include <cstring>

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
    extern int row;
    inline void InitFont() {
        mFont = LoadFontEx("assets/Inter-Black.ttf", 30, nullptr, 0);
        row = -1;
    }
    extern const std::vector<std::string> TrieInsert;
    extern const std::vector<std::string> TrieSearch;
    extern const std::vector<std::string> TrieDelete;
    extern const std::vector<std::string> hashInsert;
    extern const std::vector<std::string> hashSearch;
    extern const std::vector<std::string> hashDelete;
    extern const std::vector<std::string> AVLInsert;
    extern const std::vector<std::string> AVLSearch;
    extern const std::vector<std::string> AVLDelete;
    inline void DrawTextTrie(int index) {
        if (index == -1) {
            row = index;
            return;
        }
        if (index <= 5) {
            row = index;
            if (row > 1) row++;
            AppMenu::loadCode(TrieInsert);
            AppMenu::setHighlight(&row);
        }   
        else if (index <= 11) {
                row = index - 6;
                if (row > 1) row++;
                AppMenu::loadCode(TrieSearch);
                AppMenu::setHighlight(&row);
            }
            else {
                row = index - 12;
                if (row > 1) row++;
                if (row > 4) row++;
                if (row > 6) row++;
                AppMenu::loadCode(TrieDelete);
                AppMenu::setHighlight(&row);
            }
    }
    inline void DrawTextHash(int index) {
        if (index == -1) {
            row = index;
            return;
        }
        if (index <= 4) {
            row = index;
            AppMenu::loadCode(hashInsert);
            AppMenu::setHighlight(&row);
        }
        else if (index <= 9) {
                row = index - 5;
                AppMenu::loadCode(hashSearch);
                AppMenu::setHighlight(&row);
            }
        else {
            row = index - 10;
            AppMenu::loadCode(hashDelete);
            AppMenu::setHighlight(&row);
        }
    }
    inline void DrawTextAVL(int index) {
        if (index == -1) {
            row = index;
            return;
        }
        if (index <= 8) {
            AppMenu::loadCode(AVLInsert);
            row = index;
            AppMenu::setHighlight(&row);
        } else if (index <= 13) {
            AppMenu::loadCode(AVLSearch);
            row = index - 9;
            AppMenu::setHighlight(&row);
        }
        else {
            AppMenu::loadCode(AVLDelete);
            row = index - 14;
            if (row > 1) row ++;
            AppMenu::setHighlight(&row);
        }
    }
}   

#endif // #UTILITY_HPP