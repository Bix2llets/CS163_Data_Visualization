#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "raylib.h"
#include "appMenu.h"
#include <cstring>

namespace mLib
{
    inline std::string GenerateRandomText(int length) {
        length = GetRandomValue(1, length);
        std::string text;
        for (int i = 0; i < length; i++) {
            text.push_back((GetRandomValue(1, 1000000000) % 26) + 'A');  
        }
        return text;
    }

    inline int GenerateRandomNum(int length) {
        length = GetRandomValue(1, length);
        std::cout << length << std::endl;
        int num = 0;
        for (int i = 0; i < length; i++) {
            num = num * 10 + GetRandomValue(0 + (i == 0), 9);  
        }
        return num;
    }

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
    extern Texture2D diceTexture[6], dice, pause, play, prev, next, forward, backward, expand, collapse;
    inline void Init() {
        mFont = LoadFontEx("assets/Inter-Black.ttf", 30, nullptr, 0);
        row = -1;
        diceTexture[0] = LoadTexture("assets/dice/1_dot.png");
        diceTexture[1] = LoadTexture("assets/dice/2_dots.png");
        diceTexture[2] = LoadTexture("assets/dice/3_dots.png");
        diceTexture[3] = LoadTexture("assets/dice/4_dots.png");
        diceTexture[4] = LoadTexture("assets/dice/5_dots.png");
        diceTexture[5] = LoadTexture("assets/dice/6_dots.png");
        dice = LoadTexture("assets/dice/dice.png");
        pause = LoadTexture("assets/animationButton/pause.png");
        play = LoadTexture("assets/animationButton/play.png");
        prev = LoadTexture("assets/animationButton/prev.png");
        next = LoadTexture("assets/animationButton/next.png");
        forward = LoadTexture("assets/animationButton/forward.png");
        backward = LoadTexture("assets/animationButton/backward.png");
        expand = LoadTexture("assets/animationButton/expand.png");
        collapse = LoadTexture("assets/animationButton/collapse.png");
    }
    extern const std::vector<std::string> TrieInsert;
    extern const std::vector<std::string> TrieSearch;
    extern const std::vector<std::string> TrieDelete;
    extern const std::vector<std::string> TrieDelete2;
    extern const std::vector<std::string> hashInsert;
    extern const std::vector<std::string> hashSearch;
    extern const std::vector<std::string> hashDelete;
    extern const std::vector<std::string> AVLInsert;
    extern const std::vector<std::string> AVLSearch;
    extern const std::vector<std::string> AVLDelete;
    extern const std::vector<std::string> AVLDelete2;
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
                if (index <= 15) {
                    AppMenu::loadCode(TrieDelete);
                    row = index - 12;
                    if (row > 1) row++;
                    AppMenu::setHighlight(&row);
                }
                else {
                    AppMenu::loadCode(TrieDelete2);
                    row = index - 16;
                    row += 3;
                    if (row > 3) row++;
                    AppMenu::setHighlight(&row);
                }
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
            if (index <= 19 ) {
                AppMenu::loadCode(AVLDelete);
                row = index - 14;
                if (row > 1) row++;
                AppMenu::setHighlight(&row);
            }
            else {
                AppMenu::loadCode(AVLDelete2);
                row = index - 20;
                row += 2;
                AppMenu::setHighlight(&row);
            }
        }
    }
}   

#endif // #UTILITY_HPP