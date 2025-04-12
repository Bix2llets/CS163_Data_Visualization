#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "raylib.h"
#include "CodePane.h"
#include <string>
#include <cstring>

namespace mLib
{
    extern Color highlightColor;
    extern Font mFont;
    extern int row;
    extern Texture2D diceTexture[6], dice, pause, play, prev, next, forward, backward, expand, collapse;
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
    void Init();
    std::string GenerateRandomText(int length);
    int GenerateRandomNum(int length);
    void GenerateRandomText(char *text);
    void GenerateRandomNum(char *text);
    void DrawTextAVL(int index);
    void DrawTextTrie(int index);
    void DrawTextHash(int index);
}   

#endif // #UTILITY_HPP